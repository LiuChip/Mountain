#include "frameless_titlebar.h"
#include "toolbar.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QStyle>
#include <QPainter>
#include <QTimer>
#include <QApplication>
#include <QMenu>
#include <QListView>
#include <QStandardItemModel>
#include <QFrame>
#include <QEvent>
#include <QMouseEvent>

namespace {
// 生成单色透明背景图标
static QIcon makeIcon(int w, int h, std::function<void(QPainter&)> drawFn) {
    QPixmap pm(w, h); pm.fill(Qt::transparent); QPainter p(&pm); p.setRenderHint(QPainter::Antialiasing,false); drawFn(p); p.end(); return QIcon(pm);
}
}

//==================== 构造 & UI ====================
frameless_titlebar::frameless_titlebar(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("frameless_titlebar");
    setFixedHeight(30);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    initUi();
    setupActions();
    setupWindowButtons();
    connectSignals();
    if (window()) window()->installEventFilter(this);
    qApp->installEventFilter(this);
    QTimer::singleShot(0, this, &frameless_titlebar::updateMaximizeIcon);
}

frameless_titlebar::~frameless_titlebar() {}

void frameless_titlebar::initUi()
{
    auto *root = new QHBoxLayout(this);
    root->setContentsMargins(6,0,0,0);
    root->setSpacing(0);

    mIconLabel = new QLabel(this);
    mIconLabel->setFixedSize(18,18);
    mIconLabel->setScaledContents(true);
    mIconLabel->setPixmap(QPixmap(":/icon/icon/icon_white.png"));
    root->addWidget(mIconLabel);
    root->addSpacing(6);

    auto *centerWrap = new QWidget(this);
    auto *centerLay = new QHBoxLayout(centerWrap);
    centerLay->setContentsMargins(0,0,0,0);
    centerLay->setSpacing(8);

    mToolbar = new Toolbar(centerWrap);
    mToolbar->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    centerLay->addWidget(mToolbar, 0);

    mSearchEdit = new QLineEdit(centerWrap);
    mSearchEdit->setPlaceholderText(QString());
    mSearchEdit->setClearButtonEnabled(false);
    mSearchEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    mSearchEdit->setFixedHeight(22);
    mSearchEdit->setObjectName("searchLineEdit");
    mSearchEdit->setStyleSheet(
        "QLineEdit#searchLineEdit{background:#2d2d2d;"
        "border:1px solid #3c3c3c;border-radius:4px;padding-left:22px;"
        "color:#e0e0e0;font-size:12px;}"
        "QLineEdit#searchLineEdit:hover{background:#323232;}"
        "QLineEdit#searchLineEdit:focus{background:#1e1e1e;border:1px solid #007acc;color:#ffffff;}"
    );
    centerLay->addWidget(mSearchEdit, 1);

    root->addWidget(centerWrap, 1);

    auto *winBtnWrap = new QWidget(this);
    auto *winLay = new QHBoxLayout(winBtnWrap);
    winLay->setContentsMargins(0,0,0,0);
    winLay->setSpacing(0);
    mMinBtn = new QPushButton(winBtnWrap);
    mMaxBtn = new QPushButton(winBtnWrap);
    mCloseBtn = new QPushButton(winBtnWrap);

    QList<QPushButton*> list { mMinBtn, mMaxBtn, mCloseBtn };
    for (auto *b : list) {
        b->setFlat(true);
        b->setCursor(Qt::ArrowCursor);
        b->setFixedSize(46,30);
        b->setIconSize(QSize(46,30)); // 让 QIcon 占满按钮以便自绘居中
        b->setStyleSheet("QPushButton{border:0;padding:0;background:transparent;color:#dcdcdc;}"
                         "QPushButton:hover{background:rgba(255,255,255,0.08);color:#ffffff;}"
                         "QPushButton:pressed{background:rgba(255,255,255,0.16);}"
                         "QPushButton:disabled{color:#666666;}");
    }
    mCloseBtn->setStyleSheet("QPushButton{border:0;padding:0;background:transparent;color:#dcdcdc;}"
                             "QPushButton:hover{background:rgba(232,17,35,0.90);color:#ffffff;}" 
                             "QPushButton:pressed{background:rgba(232,17,35,1.00);}" 
                             "QPushButton:disabled{color:#666666;}");

    winLay->addWidget(mMinBtn); winLay->addWidget(mMaxBtn); winLay->addWidget(mCloseBtn);
    root->addWidget(winBtnWrap, 0);

    // 命令面板
    mCommandPopup = new QFrame(nullptr, Qt::Popup | Qt::FramelessWindowHint);
    mCommandPopup->setObjectName("commandPalette");
    auto *popupLay = new QVBoxLayout(mCommandPopup);
    popupLay->setContentsMargins(8,8,8,8); popupLay->setSpacing(6);
    auto *edit = new QLineEdit(mCommandPopup); edit->setPlaceholderText(QStringLiteral("输入命令"));
    edit->setStyleSheet("QLineEdit{background:#1e1e1e;color:#fff;border:1px solid #404040;border-radius:4px;height:26px;padding:0 6px;font-size:12px;}"
                        "QLineEdit:focus{border:1px solid #007acc;}");
    popupLay->addWidget(edit);
    auto *view = new QListView(mCommandPopup); view->setStyleSheet("QListView{background:#252526;color:#ddd;border:1px solid #404040;border-radius:4px;font-size:12px;}"
                        "QListView::item{height:22px;padding:0 8px;}" "QListView::item:selected{background:#094771;color:#fff;}");
    popupLay->addWidget(view, 1);
    auto *model = new QStandardItemModel(view); for (int i=0;i<15;++i){ auto *it=new QStandardItem(QStringLiteral("示例命令 %1").arg(i+1)); model->appendRow(it);} view->setModel(model);
}

//==================== 菜单动作 ====================
void frameless_titlebar::setupActions()
{
    if (!mToolbar) return;
    mToolbar->addAction(QIcon(), QStringLiteral("文件(&F)"));
    mToolbar->addAction(QIcon(), QStringLiteral("编辑(&E)"));
    mToolbar->addAction(QIcon(), QStringLiteral("选择(&S)"));
    mToolbar->addAction(QIcon(), QStringLiteral("查看(&V)"));
    mToolbar->addAction(QIcon(), QStringLiteral("转到(&G)"));
    mToolbar->addAction(QIcon(), QStringLiteral("运行(&R)"));
    mToolbar->addAction(QIcon(), QStringLiteral("终端(&T)"));
    mToolbar->addAction(QIcon(), QStringLiteral("帮助(&H)"));
}

//==================== 自绘图标 ====================
QIcon frameless_titlebar::makeMinIcon() const {
    return makeIcon(46,30,[](QPainter &p){ p.setPen(QPen(QColor(220,220,220),1)); p.drawLine(16,15,30,15); });
}
QIcon frameless_titlebar::makeMaxIcon(bool maximized) const {
    return makeIcon(46,30,[maximized](QPainter &p){ p.setPen(QPen(QColor(220,220,220),1)); if(!maximized){ QRect r(18,10,10,10); p.drawRect(r); } else { QRect r1(19,11,10,10); QRect r2(17,9,10,10); p.drawRect(r2); p.fillRect(QRect(r2.topLeft()+QPoint(1,1), QSize(r2.width()-1,3)), Qt::transparent); p.drawRect(r1); } });
}
QIcon frameless_titlebar::makeCloseIcon() const {
    return makeIcon(46,30,[](QPainter &p){ p.setPen(QPen(QColor(220,220,220),1)); p.drawLine(18,12,28,22); p.drawLine(28,12,18,22); });
}

void frameless_titlebar::setupWindowButtons()
{ updateMaximizeIcon(); }

void frameless_titlebar::updateMaximizeIcon()
{
    if (!mMaxBtn) return;
    bool maximized = window() && window()->isMaximized();
    if (mMinBtn) mMinBtn->setIcon(makeMinIcon());
    mMaxBtn->setIcon(makeMaxIcon(maximized));
    if (mCloseBtn) mCloseBtn->setIcon(makeCloseIcon());
    mMaxBtn->setToolTip(maximized ? QStringLiteral("还原") : QStringLiteral("最大化"));
}

//==================== 信号连接 ====================
void frameless_titlebar::connectSignals()
{
    connect(mMinBtn, &QPushButton::clicked, this, [this]{ if (window()) window()->showMinimized(); });
    connect(mMaxBtn, &QPushButton::clicked, this, [this]{ if (!window()) return; window()->isMaximized()?window()->showNormal():window()->showMaximized(); updateMaximizeIcon(); });
    connect(mCloseBtn, &QPushButton::clicked, this, [this]{ if (window()) window()->close(); });
    connect(mSearchEdit, &QLineEdit::returnPressed, this, &frameless_titlebar::showCommandPalette);
    connect(mSearchEdit, &QLineEdit::selectionChanged, this, &frameless_titlebar::showCommandPalette);
}

//==================== 命令面板 ====================
void frameless_titlebar::showCommandPalette()
{ if (!mCommandPopup||mCommandPopup->isVisible()) return; QPoint g = mapToGlobal(QPoint(width()/2 - 250, height())); mCommandPopup->resize(500,360); mCommandPopup->move(g); mCommandPopup->show(); }
void frameless_titlebar::hideCommandPalette(){ if (mCommandPopup) mCommandPopup->hide(); }

//==================== 事件过滤 ====================
bool frameless_titlebar::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == window() && event->type() == QEvent::WindowStateChange) { updateMaximizeIcon(); }
    if (obj == qApp && event->type() == QEvent::MouseButtonPress) {
        if (mCommandPopup && mCommandPopup->isVisible()) {
            auto *me = static_cast<QMouseEvent*>(event);
            if (!mCommandPopup->geometry().contains(me->globalPosition().toPoint())) hideCommandPalette();
        }
    }
    return QWidget::eventFilter(obj, event);
}

//==================== 绘制 ×====================
void frameless_titlebar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.fillRect(rect(), QColor(30,30,30));
    if (mSearchEdit && mSearchEdit->text().isEmpty() && !mSearchEdit->hasFocus()) {
        const QRect r = mSearchEdit->geometry();
        p.setRenderHint(QPainter::Antialiasing,true);
        QPoint center = r.topLeft() + QPoint(10, r.height()/2);
        p.setPen(QPen(QColor(200,200,200,180),1));
        p.drawEllipse(center,5,5); p.drawLine(center+QPoint(4,4), center+QPoint(8,8));
        p.setPen(QColor(200,200,200,180)); p.setFont(QFont("Microsoft YaHei",10));
        p.drawText(r.adjusted(20,0,0,0), Qt::AlignVCenter|Qt::AlignLeft, QStringLiteral("搜索"));
    }
}


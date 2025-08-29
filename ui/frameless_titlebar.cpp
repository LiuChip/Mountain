#include "frameless_titlebar.h"
#include "ui_frameless_titlebar.h"
#include <QStyle>
#include <QTimer>
#include <QPainter>
#include <QImage>
#include "toolbar.h"

namespace {
    // 将标准图标转为指定颜色（这里用白色），保持原透明度
    QIcon tintedStandardIcon(QWidget* w, QStyle::StandardPixmap sp, const QColor& color, const QSize& size)
    {
        const QIcon base = w->style()->standardIcon(sp);
        QPixmap pm = base.pixmap(size, QIcon::Normal, QIcon::Off);
        if (pm.isNull())
            return base;

        QImage img = pm.toImage().convertToFormat(QImage::Format_ARGB32_Premultiplied);
        QPainter p(&img);
        p.setCompositionMode(QPainter::CompositionMode_SourceIn);
        p.fillRect(img.rect(), color);
        p.end();
        return QIcon(QPixmap::fromImage(img));
    }
}

frameless_titlebar::frameless_titlebar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::frameless_titlebar)
{
    ui->setupUi(this);

    // 在中间布局中加入工具栏，并设置拉伸因子
    auto *toolbar = new Toolbar(this);
    // 添加常见菜单
    toolbar->addAction(QIcon(), QStringLiteral("\u6587\u4ef6(&F)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u7f16\u8f91(&E)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u9009\u62e9(&S)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u67e5\u770b(&V)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u8f6c\u5230(&G)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u8fd0\u884c(&R)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u7ec8\u7aef(&T)"));
    toolbar->addAction(QIcon(), QStringLiteral("\u5e2e\u52a9(&H)"));

    ui->toolbarLayout->insertWidget(0, toolbar); // 左侧

    // 让搜索框在中间扩展，工具栏保持最小所需宽度
    ui->lineEdit->setMinimumWidth(240);
    ui->lineEdit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    // 顶层三个区域的伸展：中间区域占据剩余
    auto *hl = ui->horizontalLayout_2;
    if (hl) {
        hl->setStretch(0, 0); // 图标
        hl->setStretch(1, 1); // 中间
        hl->setStretch(2, 0); // 右侧窗口按钮
    }
    // 中间区域内部：0=toolbar, 1=lineEdit
    ui->toolbarLayout->setStretch(0, 0);
    ui->toolbarLayout->setStretch(1, 1);

    // 顶部栏目标高度 30（与 general.cpp 保持一致）
    const int titleBarH = 30;

    // 从样式获取 Windows 风格的标题栏按钮/图标尺寸，获取不到则回退
    int pmBtnW = style()->pixelMetric(QStyle::PM_TitleBarButtonSize, nullptr, this);
    if (pmBtnW <= 0) pmBtnW = 46; // 常见 Windows 标题栏按钮宽度
    const int pmIcon = style()->pixelMetric(QStyle::PM_TitleBarButtonIconSize, nullptr, this);
    const int iconEdge = pmIcon > 0 ? pmIcon : 12;

    // 设置三个按钮的固定大小（宽度使用样式建议，高度跟随标题栏）
    ui->minimizeButton->setFixedSize(pmBtnW, titleBarH);
    ui->maximizeButton->setFixedSize(pmBtnW, titleBarH);
    ui->exitButton->setFixedSize(pmBtnW, titleBarH);

    // 设置图标（使用白色单色）与图标尺寸与平台一致
    const QSize iconSz(iconEdge, iconEdge);
    const QColor white(Qt::white);

    auto updateMaxIcon = [this, iconSz, white] {
        const bool maximized = this->window()->isMaximized();
        ui->maximizeButton->setIcon(tintedStandardIcon(this,
            maximized ? QStyle::SP_TitleBarNormalButton : QStyle::SP_TitleBarMaxButton,
            white, iconSz));
        ui->maximizeButton->setToolTip(maximized ? "\u8fd8\u539f" : "\u6700\u5927\u5316");
    };

    ui->minimizeButton->setIcon(tintedStandardIcon(this, QStyle::SP_TitleBarMinButton, white, iconSz));
    ui->exitButton->setIcon(tintedStandardIcon(this, QStyle::SP_TitleBarCloseButton, white, iconSz));
    updateMaxIcon();

    ui->minimizeButton->setIconSize(iconSz);
    ui->maximizeButton->setIconSize(iconSz);
    ui->exitButton->setIconSize(iconSz);

    // 让按钮扁平、去内边距，图标居中；关闭键悬停红底
    auto styleButton = [](QPushButton* b) {
        b->setFlat(true);
        b->setCursor(Qt::ArrowCursor);
        b->setStyleSheet(
            "QPushButton{padding:0;border:0;background:transparent;}"
            "QPushButton:hover{background-color:rgba(255,255,255,0.08);}"
            "QPushButton:pressed{background-color:rgba(255,255,255,0.16);}" 
        );
    };
    styleButton(ui->minimizeButton);
    styleButton(ui->maximizeButton);
    ui->exitButton->setFlat(true);
    ui->exitButton->setCursor(Qt::ArrowCursor);
    ui->exitButton->setStyleSheet(
        "QPushButton{padding:0;border:0;background:transparent;}"
        "QPushButton:hover{background-color:rgba(232,17,35,0.90);}" 
        "QPushButton:pressed{background-color:rgba(232,17,35,1.00);}" 
    );

    // 连接信号
    slots_and_signals();

    // 首次显示后校准一次最大化图标（防止外部状态切换）
    QTimer::singleShot(0, this, updateMaxIcon);
}

frameless_titlebar::~frameless_titlebar()
{
    delete ui;
}

void frameless_titlebar::slots_and_signals()
{
    connect(ui->minimizeButton, &QPushButton::clicked, this, [this]() {
        this->window()->showMinimized();
        ui->minimizeButton->setToolTip("\u6700\u5c0f\u5316");
    });

    connect(ui->maximizeButton, &QPushButton::clicked, this, [this]() {
        if (this->window()->isMaximized()) {
            this->window()->showNormal();
        } else {
            this->window()->showMaximized();
        }
        // 点击后更新图标与提示
        const int pmIcon = style()->pixelMetric(QStyle::PM_TitleBarButtonIconSize, nullptr, this);
        const QSize iconSz(pmIcon > 0 ? pmIcon : 12, pmIcon > 0 ? pmIcon : 12);
        const QColor white(Qt::white);
        ui->maximizeButton->setIcon(tintedStandardIcon(this,
            this->window()->isMaximized() ? QStyle::SP_TitleBarNormalButton : QStyle::SP_TitleBarMaxButton,
            white, iconSz));
        ui->maximizeButton->setToolTip(this->window()->isMaximized() ? "\u8fd8\u539f" : "\u6700\u5927\u5316");
    });

    connect(ui->exitButton, &QPushButton::clicked, this, [this]() {
        ui->exitButton->setToolTip("\u5173\u95ed");
        this->window()->close();
    });
}


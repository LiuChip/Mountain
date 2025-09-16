#include "toolbar.h"
#include <QStyle>
#include <QApplication>
#include <QSpacerItem>

static const char* kDarkMenuQss =
    "QMenu{background:#252526;border:1px solid #3c3c3c;color:#dcdcdc;font-size:12px;}"
//     "QMenu::separator{height:1px;background:#3c3c3c;margin:4px 0;}"
//     "QMenu::item{padding:4px 26px 4px 24px;}"
    "QMenu::item:selected{background:#094771;color:#ffffff;}"
    "QMenu::item:disabled{color:#555;}"
    "QMenu::icon{margin-left:4px;margin-right:8px;}";


void Toolbar::applyDarkMenuStyle(QMenu* menu) {
    if (menu) menu->setStyleSheet(kDarkMenuQss);
}

Toolbar::Toolbar(QWidget* parent) : QWidget(parent) {
    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mLayout->setSpacing(6);

    mOverflowMenu = new QMenu(this);
    applyDarkMenuStyle(mOverflowMenu);
    mOverflowButton = new QToolButton(this);
    mOverflowButton->setText("...");
    mOverflowButton->setPopupMode(QToolButton::InstantPopup);
    mOverflowButton->setMenu(mOverflowMenu);
    mOverflowButton->setVisible(false);
    mOverflowButton->setAutoRaise(true);
    // 深色标题栏下的文本与悬停样式
    mOverflowButton->setStyleSheet(
        "QToolButton{padding:0 8px;font-size:12px;color:#dcdcdc;}"
        "QToolButton:hover{background:rgba(255,255,255,0.07);color:#ffffff;}"
        "QToolButton:pressed{background:rgba(255,255,255,0.14);}"
    );

    auto spacer = new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    mLayout->addItem(spacer);
    mLayout->addWidget(mOverflowButton);
}

QAction* Toolbar::addAction(const QIcon& icon, const QString& text, QObject* recv, const char* slot) {
    auto* act = new QAction(icon, text, this);
    if (recv && slot)
        QObject::connect(act, SIGNAL(triggered()), recv, slot);
    addAction(act);
    return act;
}

QAction* Toolbar::addMenu(const QIcon& icon, const QString& text, QMenu* menu) {
    auto* act = new QAction(icon, text, this);
    act->setMenu(menu);
    applyDarkMenuStyle(menu);
    addAction(act);
    return act;
}

void Toolbar::addAction(QAction* action) {
    if (!action)
        return;
    if (action->parent() != this)
        action->setParent(this);
    mActions.push_back(action);

    auto* btn = new QToolButton(this);
    btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
    btn->setAutoRaise(true);
    btn->setDefaultAction(action);
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn->setCursor(Qt::ArrowCursor);
    btn->setStyleSheet(
        "QToolButton{padding:0 8px;font-size:12px;color:#dcdcdc;}"
        "QToolButton:hover{background:rgba(255,255,255,0.07);color:#ffffff;}"
        "QToolButton:pressed{background:rgba(255,255,255,0.14);}"
        "QToolButton:disabled{color:#666666;}"
    );

    if (action->menu()) {
        btn->setMenu(action->menu());
        btn->setPopupMode(QToolButton::InstantPopup);
        applyDarkMenuStyle(action->menu());
    }

    int insertIndex = qMax(0, mLayout->count() - 2);
    mLayout->insertWidget(insertIndex, btn);
    mButtons.push_back(btn);

    updateOverflow();
}

void Toolbar::clear() {
    for (auto* b : mButtons) {
        mLayout->removeWidget(b);
        b->deleteLater();
    }
    mButtons.clear();
    qDeleteAll(mActions);
    mActions.clear();
    mOverflowMenu->clear();
    mOverflowButton->setVisible(false);
}

void Toolbar::rebuildButtonsFromActions() {
    for (auto* b : mButtons) {
        mLayout->removeWidget(b);
        b->deleteLater();
    }
    mButtons.clear();

    for (auto* act : mActions) {
        auto* btn = new QToolButton(this);
        btn->setToolButtonStyle(Qt::ToolButtonTextOnly);
        btn->setAutoRaise(true);
        btn->setDefaultAction(act);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        btn->setStyleSheet(
            "QToolButton{padding:0 8px;font-size:12px;color:#dcdcdc;}"
            "QToolButton:hover{background:rgba(255,255,255,0.07);color:#ffffff;}"
            "QToolButton:pressed{background:rgba(255,255,255,0.14);}"
            "QToolButton:disabled{color:#666666;}"
        );
        if (act->menu()) {
            btn->setMenu(act->menu());
            btn->setPopupMode(QToolButton::InstantPopup);
            applyDarkMenuStyle(act->menu());
        }
        int insertIndex = qMax(0, mLayout->count() - 2);
        mLayout->insertWidget(insertIndex, btn);
        mButtons.push_back(btn);
    }
}

void Toolbar::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);
    updateOverflow();
}

void Toolbar::updateOverflow() {
    if (!mOverflowButton)
        return;

    for (auto* b : mButtons) b->setVisible(true);
    mOverflowMenu->clear();

    int avail = width();
    int need = 0;
    QVector<int> w(mButtons.size());
    for (int i = 0; i < mButtons.size(); ++i) {
        const int wi = mButtons[i]->sizeHint().width();
        w[i] = wi;
        need += wi;
        if (i > 0)
            need += mLayout->spacing();
    }

    int overflowW = mOverflowButton->sizeHint().width();

    if (need + overflowW <= avail) {
        mOverflowButton->setVisible(false);
        mLastVisibleCount = mButtons.size();
        return;
    }

    mOverflowButton->setVisible(true);

    int used = 0;
    int lastVisible = -1;
    for (int i = 0; i < mButtons.size(); ++i) {
        int nextUsed = used + w[i] + (i > 0 ? mLayout->spacing() : 0);
        if (nextUsed + overflowW <= avail) {
            lastVisible = i;
            used = nextUsed;
        } else {
            break;
        }
    }

    mLastVisibleCount = lastVisible + 1;

    for (int i = 0; i < mButtons.size(); ++i) {
        bool vis = (i <= lastVisible);
        mButtons[i]->setVisible(vis);
        if (!vis) {
            mOverflowMenu->addAction(mActions[i]);
        }
    }

    if (mLastVisibleCount == 0) {
        mOverflowButton->setText(QString::fromUtf8("\u2261"));
    } else {
        mOverflowButton->setText("...");
    }
}

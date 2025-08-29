#include "toolbar.h"
#include <QStyle>
#include <QApplication>
#include <QSpacerItem>

Toolbar::Toolbar(QWidget* parent) : QWidget(parent) {
    mLayout = new QHBoxLayout(this);
    mLayout->setContentsMargins(0, 0, 0, 0);
    mLayout->setSpacing(4);

    mOverflowMenu = new QMenu(this);
    mOverflowButton = new QToolButton(this);
    mOverflowButton->setText("...");
    mOverflowButton->setPopupMode(QToolButton::InstantPopup);
    mOverflowButton->setMenu(mOverflowMenu);
    mOverflowButton->setVisible(false);

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

// 新增：添加菜单
QAction* Toolbar::addMenu(const QIcon& icon, const QString& text, QMenu* menu) {
    auto* act = new QAction(icon, text, this);
    act->setMenu(menu); // 重要：把菜单挂在 QAction 上
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
    btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    btn->setAutoRaise(true);
    btn->setDefaultAction(action);
    btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    // 若该 action 带菜单，则配置为下拉按钮
    if (action->menu()) {
        btn->setMenu(action->menu());
        btn->setPopupMode(QToolButton::InstantPopup); // 或 MenuButtonPopup
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
        btn->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btn->setAutoRaise(true);
        btn->setDefaultAction(act);
        btn->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

        if (act->menu()) {
            btn->setMenu(act->menu());
            btn->setPopupMode(QToolButton::InstantPopup);
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

    for (int i = 0; i < mButtons.size(); ++i) {
        bool vis = (i <= lastVisible);
        mButtons[i]->setVisible(vis);
        if (!vis) {
            // 如果该 action 挂了菜单，添加到溢出菜单时会显示为子菜单
            mOverflowMenu->addAction(mActions[i]);
        }
    }
}

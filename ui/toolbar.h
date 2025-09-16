#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <QObject>
#include <QWidget>
#include <QToolButton>
#include <QMenu>
#include <QHBoxLayout>
#include <QAction>
#include <QLabel>
#include <QIcon>
#include <QResizeEvent>
#include <QVector>

// 简易 VS / VSCode 风格菜单条：左到右若溢出则使用 "..."；若一个也放不下则使用 "≡" 汉堡按钮
class Toolbar : public QWidget
{
    Q_OBJECT
public:
    explicit Toolbar(QWidget* parent = nullptr);

    QAction* addAction(const QIcon& icon, const QString& text, QObject* recv = nullptr, const char* slot = nullptr);
    void addAction(QAction* action);
    QAction* addMenu(const QIcon& icon, const QString& text, QMenu* menu);
    void clear();

    int visibleButtonCount() const { return mLastVisibleCount; }
    int totalActionCount()  const { return mActions.size(); }

    static void applyDarkMenuStyle(QMenu* menu); // 统一暗色样式

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void rebuildButtonsFromActions();
    void updateOverflow();

private:
    QHBoxLayout* mLayout { nullptr };
    QVector<QAction*> mActions;
    QVector<QToolButton*> mButtons; // 与 mActions 一一对应
    QToolButton* mOverflowButton { nullptr }; // 既做溢出又做汉堡
    QMenu* mOverflowMenu { nullptr };
    int mLastVisibleCount { 0 }; // 最近一次 layout 中正常显示的按钮数量
};

#endif // TOOLBAR_H

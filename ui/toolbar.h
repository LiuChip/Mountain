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

class Toolbar : public QWidget
{
    Q_OBJECT
public:
    explicit Toolbar(QWidget* parent = nullptr);

    // 便捷添加 Action（带图标/文本）
    QAction* addAction(const QIcon& icon, const QString& text, QObject* recv = nullptr, const char* slot = nullptr);
    // 添加已有 Action
    void addAction(QAction* action);

    // 新增：添加菜单（返回关联的 QAction，便于后续启用/禁用）
    QAction* addMenu(const QIcon& icon, const QString& text, QMenu* menu);

    // 清空
    void clear();

protected:
    void resizeEvent(QResizeEvent* event) override;

private:
    void rebuildButtonsFromActions();
    void updateOverflow();

private:
    QHBoxLayout* mLayout { nullptr };
    QVector<QAction*> mActions;
    QVector<QToolButton*> mButtons; // 与 mActions 一一对应
    QToolButton* mOverflowButton { nullptr };
    QMenu* mOverflowMenu { nullptr };
};

#endif // TOOLBAR_H

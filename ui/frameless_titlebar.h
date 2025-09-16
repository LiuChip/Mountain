#ifndef FRAMELESS_TITLEBAR_H
#define FRAMELESS_TITLEBAR_H

#include <QWidget>
#include <QPointer>

class QLabel;
class QLineEdit;
class QPushButton;
class Toolbar;
class QFrame;

// 全自绘/自布局 VS / VSCode 风格无边框标题栏（仅 UI 草稿，不含平台嵌入实现）
class frameless_titlebar : public QWidget
{
    Q_OBJECT
public:
    explicit frameless_titlebar(QWidget *parent = nullptr);
    ~frameless_titlebar();

protected:
    void paintEvent(QPaintEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override; // 处理搜索框/窗口状态/全局点击

private:
    void initUi(); // （保留：仍使用代码方式加入 Toolbar 与自绘图标）
    void setupActions();
    void setupWindowButtons();
    void connectSignals();
    void updateMaximizeIcon();
    void showCommandPalette();
    void hideCommandPalette();

    QIcon makeMinIcon() const; // 细线自绘图标
    QIcon makeMaxIcon(bool maximized) const; // 包含还原
    QIcon makeCloseIcon() const;

private:
    QPointer<QLabel> mIconLabel;
    QPointer<Toolbar> mToolbar;
    QPointer<QLineEdit> mSearchEdit;
    QPointer<QPushButton> mMinBtn;
    QPointer<QPushButton> mMaxBtn;
    QPointer<QPushButton> mCloseBtn;
    QPointer<QFrame> mCommandPopup; // 模拟 VSCode 命令面板
};

#endif // FRAMELESS_TITLEBAR_H

#ifndef FRAMELESS_TITLEBAR_H
#define FRAMELESS_TITLEBAR_H

#include <QWidget>

namespace Ui {
class frameless_titlebar;
}

class frameless_titlebar : public QWidget
{
    Q_OBJECT

public:
    explicit frameless_titlebar(QWidget *parent = nullptr);
    ~frameless_titlebar();

private:
    Ui::frameless_titlebar *ui;
    void slots_and_signals();
};

#endif // FRAMELESS_TITLEBAR_H

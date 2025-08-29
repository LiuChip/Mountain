#ifndef GENERAL_H
#define GENERAL_H

#include <QWidget>
#include "ui/frameless_titlebar.h"
#include "ui/mainwindow.h"


namespace Ui {
class general;
}

class general : public QWidget
{
    Q_OBJECT

public:
    explicit general(QWidget *parent = nullptr);
    ~general();

protected:
    void resizeEvent(QResizeEvent* e) override;

private:
    Ui::general *ui;
    frameless_titlebar* titlebar = nullptr;
    MainWindow* mainwindow = nullptr;

    void updateWindowMask();
};

#endif // GENERAL_H

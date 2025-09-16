/********************************************************************************
** Form generated from reading UI file 'frameless_titlebar.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMELESS_TITLEBAR_H
#define UI_FRAMELESS_TITLEBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_frameless_titlebar
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *iconLayout;
    QLabel *icon;
    QHBoxLayout *toolbarLayout;
    QLineEdit *lineEdit;
    QHBoxLayout *buttonLayout;
    QPushButton *minimizeButton;
    QPushButton *maximizeButton;
    QPushButton *exitButton;

    void setupUi(QWidget *frameless_titlebar)
    {
        if (frameless_titlebar->objectName().isEmpty())
            frameless_titlebar->setObjectName("frameless_titlebar");
        frameless_titlebar->resize(1128, 30);
        frameless_titlebar->setMinimumSize(QSize(0, 30));
        frameless_titlebar->setMaximumSize(QSize(16777215, 30));
        frameless_titlebar->setStyleSheet(QString::fromUtf8("QWidget#frameless_titlebar{background:#1e1e1e;}\n"
"QLineEdit#lineEdit{background:#2d2d2d;border:1px solid #3c3c3c;border-radius:4px;padding-left:22px;color:#e0e0e0;font-size:12px;}\n"
"QLineEdit#lineEdit:hover{background:#323232;}\n"
"QLineEdit#lineEdit:focus{background:#1e1e1e;border:1px solid #007acc;color:#ffffff;}\n"
"QPushButton#minimizeButton,QPushButton#maximizeButton,QPushButton#exitButton{border:0;padding:0;background:transparent;color:#dcdcdc;}\n"
"QPushButton#minimizeButton:hover,QPushButton#maximizeButton:hover{background:rgba(255,255,255,0.08);color:#ffffff;}\n"
"QPushButton#minimizeButton:pressed,QPushButton#maximizeButton:pressed{background:rgba(255,255,255,0.16);}\n"
"QPushButton#exitButton:hover{background:rgba(232,17,35,0.90);color:#ffffff;}\n"
"QPushButton#exitButton:pressed{background:rgba(232,17,35,1.00);}\n"
"QMenu{background:#252526;border:1px solid #3c3c3c;color:#dcdcdc;font-size:12px;}\n"
"QMenu::separator{height:1px;background:#3c3c3c;margin:4px 0;}\n"
"QMenu::item{padding:4px 26px 4"
                        "px 24px;}\n"
"QMenu::item:selected{background:#094771;color:#ffffff;}\n"
"QMenu::item:disabled{color:#555;}\n"
"QMenu::icon{margin-left:4px;margin-right:8px;}"));
        horizontalLayout_2 = new QHBoxLayout(frameless_titlebar);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(6, 0, 0, 0);
        iconLayout = new QHBoxLayout();
        iconLayout->setSpacing(0);
        iconLayout->setObjectName("iconLayout");
        iconLayout->setContentsMargins(0, -1, -1, -1);
        icon = new QLabel(frameless_titlebar);
        icon->setObjectName("icon");
        icon->setMinimumSize(QSize(18, 18));
        icon->setMaximumSize(QSize(18, 18));
        icon->setPixmap(QPixmap(QString::fromUtf8(":/icon/icon/icon_white.png")));
        icon->setScaledContents(true);

        iconLayout->addWidget(icon, 0, Qt::AlignmentFlag::AlignLeft);


        horizontalLayout_2->addLayout(iconLayout);

        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setSpacing(8);
        toolbarLayout->setObjectName("toolbarLayout");
        lineEdit = new QLineEdit(frameless_titlebar);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setMinimumSize(QSize(240, 22));
        lineEdit->setMaximumSize(QSize(600, 16777215));

        toolbarLayout->addWidget(lineEdit);


        horizontalLayout_2->addLayout(toolbarLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(0);
        buttonLayout->setObjectName("buttonLayout");
        minimizeButton = new QPushButton(frameless_titlebar);
        minimizeButton->setObjectName("minimizeButton");
        minimizeButton->setMinimumSize(QSize(46, 30));
        minimizeButton->setMaximumSize(QSize(46, 30));

        buttonLayout->addWidget(minimizeButton);

        maximizeButton = new QPushButton(frameless_titlebar);
        maximizeButton->setObjectName("maximizeButton");
        maximizeButton->setMinimumSize(QSize(46, 30));
        maximizeButton->setMaximumSize(QSize(46, 30));

        buttonLayout->addWidget(maximizeButton);

        exitButton = new QPushButton(frameless_titlebar);
        exitButton->setObjectName("exitButton");
        exitButton->setMinimumSize(QSize(46, 30));
        exitButton->setMaximumSize(QSize(46, 30));

        buttonLayout->addWidget(exitButton);


        horizontalLayout_2->addLayout(buttonLayout);


        retranslateUi(frameless_titlebar);

        QMetaObject::connectSlotsByName(frameless_titlebar);
    } // setupUi

    void retranslateUi(QWidget *frameless_titlebar)
    {
        frameless_titlebar->setWindowTitle(QCoreApplication::translate("frameless_titlebar", "Form", nullptr));
        icon->setText(QString());
        lineEdit->setText(QString());
        minimizeButton->setText(QString());
        maximizeButton->setText(QString());
        exitButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class frameless_titlebar: public Ui_frameless_titlebar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMELESS_TITLEBAR_H

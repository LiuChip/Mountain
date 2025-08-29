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
        horizontalLayout_2 = new QHBoxLayout(frameless_titlebar);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        iconLayout = new QHBoxLayout();
        iconLayout->setSpacing(0);
        iconLayout->setObjectName("iconLayout");
        iconLayout->setContentsMargins(4, -1, -1, -1);
        icon = new QLabel(frameless_titlebar);
        icon->setObjectName("icon");
        icon->setMaximumSize(QSize(15, 15));
        icon->setPixmap(QPixmap(QString::fromUtf8(":/icon/icon/icon_white.png")));
        icon->setScaledContents(true);

        iconLayout->addWidget(icon, 0, Qt::AlignmentFlag::AlignLeft);


        horizontalLayout_2->addLayout(iconLayout);

        toolbarLayout = new QHBoxLayout();
        toolbarLayout->setSpacing(0);
        toolbarLayout->setObjectName("toolbarLayout");
        lineEdit = new QLineEdit(frameless_titlebar);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setStyleSheet(QString::fromUtf8("border-radius:5px;\n"
""));

        toolbarLayout->addWidget(lineEdit);


        horizontalLayout_2->addLayout(toolbarLayout);

        buttonLayout = new QHBoxLayout();
        buttonLayout->setSpacing(0);
        buttonLayout->setObjectName("buttonLayout");
        minimizeButton = new QPushButton(frameless_titlebar);
        minimizeButton->setObjectName("minimizeButton");
        minimizeButton->setMinimumSize(QSize(0, 20));
        minimizeButton->setMaximumSize(QSize(16777215, 20));
        minimizeButton->setStyleSheet(QString::fromUtf8(""));

        buttonLayout->addWidget(minimizeButton);

        maximizeButton = new QPushButton(frameless_titlebar);
        maximizeButton->setObjectName("maximizeButton");
        maximizeButton->setMinimumSize(QSize(0, 20));
        maximizeButton->setMaximumSize(QSize(16777215, 20));

        buttonLayout->addWidget(maximizeButton);

        exitButton = new QPushButton(frameless_titlebar);
        exitButton->setObjectName("exitButton");
        exitButton->setMinimumSize(QSize(0, 20));
        exitButton->setMaximumSize(QSize(16777215, 20));

        buttonLayout->addWidget(exitButton);


        horizontalLayout_2->addLayout(buttonLayout);


        retranslateUi(frameless_titlebar);

        QMetaObject::connectSlotsByName(frameless_titlebar);
    } // setupUi

    void retranslateUi(QWidget *frameless_titlebar)
    {
        frameless_titlebar->setWindowTitle(QCoreApplication::translate("frameless_titlebar", "Form", nullptr));
        icon->setText(QString());
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

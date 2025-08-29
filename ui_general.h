/********************************************************************************
** Form generated from reading UI file 'general.ui'
**
** Created by: Qt User Interface Compiler version 6.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERAL_H
#define UI_GENERAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_general
{
public:
    QVBoxLayout *verticalLayout_5;
    QWidget *mainwindow_widget;
    QVBoxLayout *verticalLayout_4;
    QWidget *titlebar_widget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *basicLayout;
    QWidget *content_widget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *contentVLayout;

    void setupUi(QWidget *general)
    {
        if (general->objectName().isEmpty())
            general->setObjectName("general");
        general->resize(871, 537);
        general->setStyleSheet(QString::fromUtf8(""));
        verticalLayout_5 = new QVBoxLayout(general);
        verticalLayout_5->setObjectName("verticalLayout_5");
        mainwindow_widget = new QWidget(general);
        mainwindow_widget->setObjectName("mainwindow_widget");
        verticalLayout_4 = new QVBoxLayout(mainwindow_widget);
        verticalLayout_4->setObjectName("verticalLayout_4");
        titlebar_widget = new QWidget(mainwindow_widget);
        titlebar_widget->setObjectName("titlebar_widget");
        titlebar_widget->setMaximumSize(QSize(16777215, 30));
        titlebar_widget->setStyleSheet(QString::fromUtf8("background: black"));
        verticalLayout_3 = new QVBoxLayout(titlebar_widget);
        verticalLayout_3->setObjectName("verticalLayout_3");
        basicLayout = new QHBoxLayout();
        basicLayout->setSpacing(0);
        basicLayout->setObjectName("basicLayout");

        verticalLayout_3->addLayout(basicLayout);


        verticalLayout_4->addWidget(titlebar_widget);

        content_widget = new QWidget(mainwindow_widget);
        content_widget->setObjectName("content_widget");
        verticalLayout_2 = new QVBoxLayout(content_widget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        contentVLayout = new QVBoxLayout();
        contentVLayout->setObjectName("contentVLayout");

        verticalLayout_2->addLayout(contentVLayout);


        verticalLayout_4->addWidget(content_widget);


        verticalLayout_5->addWidget(mainwindow_widget);


        retranslateUi(general);

        QMetaObject::connectSlotsByName(general);
    } // setupUi

    void retranslateUi(QWidget *general)
    {
        general->setWindowTitle(QCoreApplication::translate("general", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class general: public Ui_general {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERAL_H

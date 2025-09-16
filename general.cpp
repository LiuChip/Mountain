#include "general.h"
#include "ui_general.h"
#include "ui/frameless_titlebar.h"
#include "ui/mainwindow.h"
#include <QTimer>
#include <QDebug>
#include <QPainterPath>

general::general(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::general)
{
    ui->setupUi(this);

    // 顶层与中间容器布局：去掉默认 9px 边距与 6px 间距
    ui->verticalLayout_5->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_5->setSpacing(0);
    ui->verticalLayout_4->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_4->setSpacing(0);

    // 标题栏容器自身
    ui->titlebar_widget->setFixedHeight(30); // 改为 30
    ui->verticalLayout_3->setContentsMargins(0, 0, 0, 0);
    ui->verticalLayout_3->setSpacing(0);
    ui->basicLayout->setContentsMargins(0, 0, 0, 0);
    ui->basicLayout->setSpacing(0);

    // 内容区布局也清零，避免黑条与内容之间留缝
    ui->contentVLayout->setContentsMargins(0, 0, 0, 0);
    ui->contentVLayout->setSpacing(0);

    // 加入自定义标题栏与内容
    titlebar = new frameless_titlebar(ui->titlebar_widget);
    titlebar->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed); // 横向占满
    ui->basicLayout->addWidget(titlebar);

    mainwindow = new MainWindow(ui->content_widget);
    ui->contentVLayout->addWidget(mainwindow);

    // 无边框 + 系统菜单 + 最小化/最大化按钮
    this->setWindowFlags(Qt::FramelessWindowHint
                         | Qt::WindowSystemMenuHint
                         | Qt::WindowMinMaxButtonsHint);

    // 首帧后按当前几何更新一次圆角/遮罩
    QTimer::singleShot(0, this, [this] { updateWindowMask(); });
}

general::~general()
{
    delete ui;
}

void general::resizeEvent(QResizeEvent* e)
{
    QWidget::resizeEvent(e);
    updateWindowMask();
}

void general::updateWindowMask()
{
    // 最大化/全屏时不做圆角，避免被裁剪；正常状态应用圆角
    if (isMaximized() || isFullScreen()) {
        setMask(QRegion());
        return;
    }

    const int radius = 7; // 圆角半径
    QPainterPath path;
    path.addRoundedRect(rect(), radius, radius);
    setMask(QRegion(path.toFillPolygon().toPolygon()));
}

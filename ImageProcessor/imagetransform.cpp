#include "imagetransform.h"
#include <QPixmap>
#include <QDebug>

ImageTransform::ImageTransform(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);
    leftLayout = new QVBoxLayout();

    // 鏡像選項
    mirrorGroup = new QGroupBox(QStringLiteral("鏡射"), this);
    groupLayout = new QVBoxLayout(mirrorGroup);

    hCheckBox = new QCheckBox(QStringLiteral("水平"), mirrorGroup);
    vCheckBox = new QCheckBox(QStringLiteral("垂直"), mirrorGroup);
    mirrorButton = new QPushButton(QStringLiteral("執行"), mirrorGroup);

    groupLayout->addWidget(hCheckBox);
    groupLayout->addWidget(vCheckBox);
    groupLayout->addWidget(mirrorButton);

    mirrorGroup->setLayout(groupLayout);
    leftLayout->addWidget(mirrorGroup);

    // 旋轉控制
    rotateDial = new QDial(this);
    rotateDial->setRange(0, 360);  // 設定旋轉角度範圍
    rotateDial->setNotchesVisible(true);

    leftLayout->addWidget(rotateDial);

    // Spacer
    vSpacer = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);
    leftLayout->addItem(vSpacer);

    mainLayout->addLayout(leftLayout);

    // 圖像顯示區域
    inWin = new QLabel(this);
    inWin->setScaledContents(true);

    QPixmap initPixmap(300, 200);
    initPixmap.fill(QColor(255, 255, 255)); // 初始化為白色
    inWin->setPixmap(initPixmap);
    inWin->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    mainLayout->addWidget(inWin);

    // 信號槽連接
    connect(mirrorButton, &QPushButton::clicked, this, &ImageTransform::mirroredImage);
    connect(rotateDial, &QDial::valueChanged, this, &ImageTransform::rotatedImage);
}

ImageTransform::~ImageTransform()
{
}

void ImageTransform::mirroredImage()
{
    if (srcImg.isNull()) {
        qDebug() << "源影像為空，無法執行鏡像操作！";
        return;
    }

    bool horizontal = hCheckBox->isChecked();
    bool vertical = vCheckBox->isChecked();

    dstImg = srcImg.mirrored(horizontal, vertical);
    inWin->setPixmap(QPixmap::fromImage(dstImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTransform::rotatedImage()
{
    if (srcImg.isNull()) {
        qDebug() << "源影像為空，無法執行旋轉操作！";
        return;
    }

    QTransform transform;
    int angle = rotateDial->value();
    transform.rotate(angle);

    dstImg = srcImg.transformed(transform);
    inWin->setPixmap(QPixmap::fromImage(dstImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

void ImageTransform::setTransformedImage(const QImage &image)
{
    if (image.isNull()) {
        qDebug() << "提供的影像為空！";
        return;
    }

    srcImg = image;
    dstImg = srcImg;
    inWin->setPixmap(QPixmap::fromImage(srcImg).scaled(inWin->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
}

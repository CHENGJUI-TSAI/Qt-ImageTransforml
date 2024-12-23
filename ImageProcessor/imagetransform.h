#ifndef IMAGETRANSFORM_H
#define IMAGETRANSFORM_H

#include <QWidget>
#include <QLabel>
#include <QGroupBox>
#include <QCheckBox>
#include <QPushButton>
#include <QDial>
#include <QSpacerItem>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QImage>

class ImageTransform : public QWidget
{
    Q_OBJECT

public:
    ImageTransform(QWidget *parent = nullptr);
    ~ImageTransform();

    // 用於設定原始影像
    void setTransformedImage(const QImage &image);

    QLabel *inWin;
    QGroupBox *mirrorGroup;
    QCheckBox *hCheckBox;
    QCheckBox *vCheckBox;
    QPushButton *mirrorButton;
    QDial *rotateDial;
    QSpacerItem *vSpacer;
    QHBoxLayout *mainLayout;
    QVBoxLayout *groupLayout;
    QVBoxLayout *leftLayout;
    QImage srcImg;  // 原始影像
    QImage dstImg;  // 處理後影像

private slots:
    void mirroredImage();  // 鏡像處理
    void rotatedImage();   // 旋轉處理
};

#endif // IMAGETRANSFORM_H

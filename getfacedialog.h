#ifndef GETFACEDIALOG_H
#define GETFACEDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QCheckBox>
#include "ImgOrganizer/FaceDetection/FaceDetector.h"
#include "ImgOrganizer/FaceDetection/FacesCropped.h"
#include <QImageReader>

namespace Ui {
class GetFaceDialog;
}

class GetFaceDialog : public QDialog
{
    Q_OBJECT

public:
    explicit GetFaceDialog(QWidget *parent = nullptr);

    ~GetFaceDialog();
signals:
    void chosenLabels(std::vector<std::wstring>);

private:
    void addOption(std::wstring x);
    void toggleHidden(bool flg);
    Ui::GetFaceDialog *ui;
    std::vector<QCheckBox *> m_options;
    std::wstring m_newLabel;
    static FacesCropped m_cropper;
    static FaceDetector m_detector;// = FaceDetector::loadFromYAML();

};

#endif // GETFACEDIALOG_H

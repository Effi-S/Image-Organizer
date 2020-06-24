#include "getfacedialog.h"
#include "ui_getfacedialog.h"

#include <QFileDialog>
#include <QMessageBox>

FacesCropped GetFaceDialog::m_cropper;
FaceDetector GetFaceDialog::m_detector= FaceDetector::loadFromYAML();

GetFaceDialog::GetFaceDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GetFaceDialog)
{


//        std::cout << ui->splitter->sizes()[0] <<std::endl;
//    ui->splitter->setSizes(QList<int>() <<2* this->height()/3 << this->height()/3 );
    ui->setupUi(this);
    toggleHidden(true);

    // -- initializing options
    for(auto x: FaceDetector::getUserLabels())
         addOption(x);

    // -- new label requested
    connect(ui->pushButton_enter , &QPushButton::pressed , this, [=](){
        m_newLabel = ui->lineEdit_label->text().toStdWString();
        toggleHidden(false);
    });

    // -- new label from webcam request
   connect(ui->pushButton_fromWebCam,&QPushButton::pressed, this, [&](){
         std::vector<cv::Mat> faces = m_cropper.readfromWebCam();
         if(faces.size() < 8 ) {
             QMessageBox::warning(this, "Warning", "Could not connect to Webcam");
             return;

         }
         m_detector.addTrainingSet(faces, m_newLabel);
         m_detector.save();
         addOption(m_newLabel);
         toggleHidden(true);
   });

    //-- new label from files requested.
   connect(ui->pushButton_fromFile, &QPushButton::pressed, this, [&](){
            QStringList imgPathList = QFileDialog::getOpenFileNames(this , "Choose face images (min 8)");

            if(imgPathList.size() < 8 ) {
                QMessageBox::warning(this, "Warning", "Need at least 8 images..");
                return;

            }
            for (auto imgPath: imgPathList) {
                auto file = QFile(imgPath);
                QString imageFormat = QImageReader::imageFormat(imgPath);

                if(!file.exists() || imageFormat.size() == 0) {
                    QMessageBox::warning(this, "Warning", "Cannot Open:"+ imgPath);
                    return;
                }
            }
             std::vector<cv::Mat> imgVec;
             for(auto str: imgPathList)
                  imgVec.push_back(MyUtils::unicodeImgRead(str.toStdWString()));

             std::wstring new_label = m_newLabel;

             m_detector.addTrainingSet(imgVec, new_label);
             m_detector.save();
             addOption(m_newLabel);
             toggleHidden(true);

   });

   //--  connect button box (for when ok pressed).
   connect(ui->buttonBox, &QDialogButtonBox::accepted , this, [&](){
       std::vector<std::wstring> chosen;
       for(auto& box: m_options )
           if(box->isChecked())
               chosen.push_back(box->text().toStdWString());
       emit chosenLabels(chosen);
   });
}

GetFaceDialog::~GetFaceDialog()
{
    delete ui;
}

void GetFaceDialog::addOption(std::wstring x)
{
    auto checkBox = new QCheckBox(this);
    checkBox->setText(QString::fromStdWString(x));
    ui->radioLayout->addWidget(checkBox);
    m_options.push_back(checkBox);
}

void GetFaceDialog::toggleHidden( bool flg)
{
    ui->pushButton_fromFile->setHidden(flg);
    ui->pushButton_fromWebCam->setHidden(flg);
    ui->label_2->setHidden(flg);
    ui->label_4->setHidden(!flg);
    ui->lineEdit_label->setHidden(!flg);
    ui->pushButton_enter->setHidden(!flg);
}

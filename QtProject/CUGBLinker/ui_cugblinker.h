/********************************************************************************
** Form generated from reading UI file 'cugblinker.ui'
**
** Created: Tue Mar 16 21:56:53 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUGBLINKER_H
#define UI_CUGBLINKER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "deletecombobox.h"
#include "paintwidget.h"
#include "splitbutton.h"

QT_BEGIN_NAMESPACE

class Ui_CUGBLinker
{
public:
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *linkerTab;
    QGridLayout *gridLayout_3;
    QGroupBox *grpAccount;
    QGridLayout *gridLayout_2;
    QLabel *lblAccount;
    DeleteComboBox *cboAccount;
    QRadioButton *rdoRangeIn;
    QRadioButton *rdoRangeOut;
    QLabel *lblPassword;
    QLineEdit *txtPassword;
    QCheckBox *chkSavePassword;
    QCheckBox *chkStartOS;
    QCheckBox *chkAutoCon;
    QGroupBox *grpInfo;
    QVBoxLayout *verticalLayout_2;
    QTextEdit *txtInfo;
    QPushButton *btnConnect;
    SplitButton *btnDisCon;
    QWidget *trafficTab;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *grpSpeed;
    QVBoxLayout *verticalLayout_4;
    PaintWidget *paintWidget;
    QGroupBox *grpSettings;
    QGridLayout *gridLayout;
    QFrame *frame;
    QCheckBox *chkShowTip;
    QSpinBox *spnMaxTraffic;
    QCheckBox *chkAutoDis;
    QLabel *lblNIC;
    QLabel *lblCurNIC;
    QProgressBar *proTraffic;

    void setupUi(QDialog *CUGBLinker)
    {
        if (CUGBLinker->objectName().isEmpty())
            CUGBLinker->setObjectName(QString::fromUtf8("CUGBLinker"));
        CUGBLinker->resize(300, 350);
        CUGBLinker->setMinimumSize(QSize(300, 350));
        CUGBLinker->setMaximumSize(QSize(300, 350));
        QIcon icon;
        icon.addFile(QString::fromUtf8("E:/Documents/Visual Studio 2008/Projects/CUGBLinker/CUGBLinker/res/CUGBLinker.ico"), QSize(), QIcon::Normal, QIcon::Off);
        CUGBLinker->setWindowIcon(icon);
        verticalLayout = new QVBoxLayout(CUGBLinker);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        tabWidget = new QTabWidget(CUGBLinker);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        linkerTab = new QWidget();
        linkerTab->setObjectName(QString::fromUtf8("linkerTab"));
        gridLayout_3 = new QGridLayout(linkerTab);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        grpAccount = new QGroupBox(linkerTab);
        grpAccount->setObjectName(QString::fromUtf8("grpAccount"));
        grpAccount->setCheckable(false);
        gridLayout_2 = new QGridLayout(grpAccount);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_2->setContentsMargins(-1, -1, 6, -1);
        lblAccount = new QLabel(grpAccount);
        lblAccount->setObjectName(QString::fromUtf8("lblAccount"));

        gridLayout_2->addWidget(lblAccount, 0, 0, 1, 1);

        cboAccount = new DeleteComboBox(grpAccount);
        cboAccount->setObjectName(QString::fromUtf8("cboAccount"));
        cboAccount->setEditable(true);

        gridLayout_2->addWidget(cboAccount, 0, 1, 1, 1);

        rdoRangeIn = new QRadioButton(grpAccount);
        rdoRangeIn->setObjectName(QString::fromUtf8("rdoRangeIn"));
        rdoRangeIn->setChecked(true);

        gridLayout_2->addWidget(rdoRangeIn, 0, 2, 1, 1);

        rdoRangeOut = new QRadioButton(grpAccount);
        rdoRangeOut->setObjectName(QString::fromUtf8("rdoRangeOut"));

        gridLayout_2->addWidget(rdoRangeOut, 0, 3, 1, 1);

        lblPassword = new QLabel(grpAccount);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));

        gridLayout_2->addWidget(lblPassword, 1, 0, 1, 1);

        txtPassword = new QLineEdit(grpAccount);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(txtPassword, 1, 1, 1, 1);

        chkSavePassword = new QCheckBox(grpAccount);
        chkSavePassword->setObjectName(QString::fromUtf8("chkSavePassword"));

        gridLayout_2->addWidget(chkSavePassword, 1, 2, 1, 2);

        chkStartOS = new QCheckBox(grpAccount);
        chkStartOS->setObjectName(QString::fromUtf8("chkStartOS"));

        gridLayout_2->addWidget(chkStartOS, 2, 0, 1, 2);

        chkAutoCon = new QCheckBox(grpAccount);
        chkAutoCon->setObjectName(QString::fromUtf8("chkAutoCon"));

        gridLayout_2->addWidget(chkAutoCon, 2, 2, 1, 2);


        gridLayout_3->addWidget(grpAccount, 0, 0, 1, 4);

        grpInfo = new QGroupBox(linkerTab);
        grpInfo->setObjectName(QString::fromUtf8("grpInfo"));
        verticalLayout_2 = new QVBoxLayout(grpInfo);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(15, 5, 5, 5);
        txtInfo = new QTextEdit(grpInfo);
        txtInfo->setObjectName(QString::fromUtf8("txtInfo"));
        txtInfo->setFrameShape(QFrame::NoFrame);
        txtInfo->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        txtInfo->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        txtInfo->setReadOnly(true);

        verticalLayout_2->addWidget(txtInfo);


        gridLayout_3->addWidget(grpInfo, 1, 0, 1, 4);

        btnConnect = new QPushButton(linkerTab);
        btnConnect->setObjectName(QString::fromUtf8("btnConnect"));
        btnConnect->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(btnConnect, 2, 0, 1, 2);

        btnDisCon = new SplitButton(linkerTab);
        btnDisCon->setObjectName(QString::fromUtf8("btnDisCon"));
        btnDisCon->setMinimumSize(QSize(0, 30));

        gridLayout_3->addWidget(btnDisCon, 2, 2, 1, 2);

        tabWidget->addTab(linkerTab, QString());
        trafficTab = new QWidget();
        trafficTab->setObjectName(QString::fromUtf8("trafficTab"));
        verticalLayout_3 = new QVBoxLayout(trafficTab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        grpSpeed = new QGroupBox(trafficTab);
        grpSpeed->setObjectName(QString::fromUtf8("grpSpeed"));
        verticalLayout_4 = new QVBoxLayout(grpSpeed);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        paintWidget = new PaintWidget(grpSpeed);
        paintWidget->setObjectName(QString::fromUtf8("paintWidget"));

        verticalLayout_4->addWidget(paintWidget);


        verticalLayout_3->addWidget(grpSpeed);

        grpSettings = new QGroupBox(trafficTab);
        grpSettings->setObjectName(QString::fromUtf8("grpSettings"));
        gridLayout = new QGridLayout(grpSettings);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame = new QFrame(grpSettings);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setMinimumSize(QSize(0, 25));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        chkShowTip = new QCheckBox(frame);
        chkShowTip->setObjectName(QString::fromUtf8("chkShowTip"));
        chkShowTip->setGeometry(QRect(0, 6, 221, 16));
        chkShowTip->setBaseSize(QSize(0, 0));
        spnMaxTraffic = new QSpinBox(frame);
        spnMaxTraffic->setObjectName(QString::fromUtf8("spnMaxTraffic"));
        spnMaxTraffic->setGeometry(QRect(80, 4, 55, 20));
        spnMaxTraffic->setAlignment(Qt::AlignCenter);
        spnMaxTraffic->setMinimum(15);
        spnMaxTraffic->setMaximum(100000);
        spnMaxTraffic->setSingleStep(10);
        spnMaxTraffic->setValue(2000);

        gridLayout->addWidget(frame, 1, 0, 1, 2);

        chkAutoDis = new QCheckBox(grpSettings);
        chkAutoDis->setObjectName(QString::fromUtf8("chkAutoDis"));

        gridLayout->addWidget(chkAutoDis, 2, 0, 1, 2);

        lblNIC = new QLabel(grpSettings);
        lblNIC->setObjectName(QString::fromUtf8("lblNIC"));
        lblNIC->setMinimumSize(QSize(0, 20));
        lblNIC->setMaximumSize(QSize(55, 16777215));

        gridLayout->addWidget(lblNIC, 3, 0, 1, 1);

        lblCurNIC = new QLabel(grpSettings);
        lblCurNIC->setObjectName(QString::fromUtf8("lblCurNIC"));
        QFont font;
        font.setUnderline(true);
        lblCurNIC->setFont(font);
        lblCurNIC->setCursor(QCursor(Qt::PointingHandCursor));

        gridLayout->addWidget(lblCurNIC, 3, 1, 1, 1);

        proTraffic = new QProgressBar(grpSettings);
        proTraffic->setObjectName(QString::fromUtf8("proTraffic"));
        proTraffic->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("System"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        proTraffic->setFont(font1);
        proTraffic->setMaximum(14);
        proTraffic->setValue(14);
        proTraffic->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(proTraffic, 0, 0, 1, 2);


        verticalLayout_3->addWidget(grpSettings);

        tabWidget->addTab(trafficTab, QString());

        verticalLayout->addWidget(tabWidget);

        QWidget::setTabOrder(cboAccount, txtPassword);
        QWidget::setTabOrder(txtPassword, rdoRangeIn);
        QWidget::setTabOrder(rdoRangeIn, rdoRangeOut);
        QWidget::setTabOrder(rdoRangeOut, chkSavePassword);
        QWidget::setTabOrder(chkSavePassword, chkAutoCon);
        QWidget::setTabOrder(chkAutoCon, chkStartOS);
        QWidget::setTabOrder(chkStartOS, btnConnect);
        QWidget::setTabOrder(btnConnect, btnDisCon);
        QWidget::setTabOrder(btnDisCon, tabWidget);
        QWidget::setTabOrder(tabWidget, chkShowTip);
        QWidget::setTabOrder(chkShowTip, spnMaxTraffic);
        QWidget::setTabOrder(spnMaxTraffic, chkAutoDis);
        QWidget::setTabOrder(chkAutoDis, txtInfo);

        retranslateUi(CUGBLinker);
        QObject::connect(spnMaxTraffic, SIGNAL(valueChanged(int)), proTraffic, SLOT(setMaximum(int)));
        QObject::connect(btnConnect, SIGNAL(clicked()), CUGBLinker, SLOT(onConnect()));
        QObject::connect(btnDisCon, SIGNAL(clicked()), CUGBLinker, SLOT(onDisconnect()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(CUGBLinker);
    } // setupUi

    void retranslateUi(QDialog *CUGBLinker)
    {
        CUGBLinker->setWindowTitle(QApplication::translate("CUGBLinker", "CUGBLinker", 0, QApplication::UnicodeUTF8));
        grpAccount->setTitle(QApplication::translate("CUGBLinker", "\345\270\220\345\217\267\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        lblAccount->setText(QApplication::translate("CUGBLinker", "\345\270\220\345\217\267:", 0, QApplication::UnicodeUTF8));
        cboAccount->clear();
        cboAccount->insertItems(0, QStringList()
         << QApplication::translate("CUGBLinker", "1234567890", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("CUGBLinker", "080520s", 0, QApplication::UnicodeUTF8)
        );
        rdoRangeIn->setText(QApplication::translate("CUGBLinker", "\345\233\275\345\206\205", 0, QApplication::UnicodeUTF8));
        rdoRangeOut->setText(QApplication::translate("CUGBLinker", "\345\233\275\345\244\226", 0, QApplication::UnicodeUTF8));
        lblPassword->setText(QApplication::translate("CUGBLinker", "\345\257\206\347\240\201:", 0, QApplication::UnicodeUTF8));
        chkSavePassword->setText(QApplication::translate("CUGBLinker", "\344\277\235\345\255\230\345\257\206\347\240\201", 0, QApplication::UnicodeUTF8));
        chkStartOS->setText(QApplication::translate("CUGBLinker", "\351\232\217\347\263\273\347\273\237\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        chkAutoCon->setText(QApplication::translate("CUGBLinker", "\350\207\252\345\212\250\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        grpInfo->setTitle(QApplication::translate("CUGBLinker", "\350\277\236\346\216\245\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        txtInfo->setHtml(QApplication::translate("CUGBLinker", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"></p></body></html>", 0, QApplication::UnicodeUTF8));
        btnConnect->setText(QApplication::translate("CUGBLinker", "\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        btnDisCon->setText(QApplication::translate("CUGBLinker", "\346\226\255\345\274\200", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(linkerTab), QApplication::translate("CUGBLinker", "\347\275\221\345\205\263\350\277\236\346\216\245", 0, QApplication::UnicodeUTF8));
        grpSpeed->setTitle(QApplication::translate("CUGBLinker", "\347\275\221\351\200\237\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
        grpSettings->setTitle(QApplication::translate("CUGBLinker", "\347\233\270\345\205\263\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        chkShowTip->setText(QApplication::translate("CUGBLinker", "\345\275\223\346\265\201\351\207\217\350\266\205\350\277\207          MB \346\227\266\346\217\220\351\206\222\346\210\221", 0, QApplication::UnicodeUTF8));
        chkAutoDis->setText(QApplication::translate("CUGBLinker", "\345\271\266\350\207\252\345\212\250\346\226\255\347\275\221", 0, QApplication::UnicodeUTF8));
        lblNIC->setText(QApplication::translate("CUGBLinker", "\345\275\223\345\211\215\347\275\221\345\215\241:", 0, QApplication::UnicodeUTF8));
        lblCurNIC->setText(QApplication::translate("CUGBLinker", "NULL", 0, QApplication::UnicodeUTF8));
        proTraffic->setFormat(QApplication::translate("CUGBLinker", "%v/%m(%p%)", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(trafficTab), QApplication::translate("CUGBLinker", "\346\265\201\351\207\217\344\277\241\346\201\257", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class CUGBLinker: public Ui_CUGBLinker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUGBLINKER_H

#include "uimw.h"



void UIMW::setupUi(QMainWindow *MainWindow)
{

    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QStringLiteral("MainWindow"));
    MainWindow->resize(window_W, window_H);
    actionInsert_Plot = new QAction(MainWindow);
    actionInsert_Plot->setObjectName(QStringLiteral("actionInsert_Plot"));
    actionSave_Document = new QAction(MainWindow);
    actionSave_Document->setObjectName(QStringLiteral("actionSave_Document"));
    centralWidget = new QWidget(MainWindow);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(20, 20, 20, 20);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    MainWindow->setCentralWidget(centralWidget);
    statusBar = new QStatusBar(MainWindow);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    MainWindow->setStatusBar(statusBar);

    retranslateUi(MainWindow);

    m_deviceBox = new QComboBox();
    const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();
    m_deviceBox->addItem(defaultDeviceInfo.deviceName(), qVariantFromValue(defaultDeviceInfo));
    for (auto &deviceInfo: QAudioDeviceInfo::availableDevices(QAudio::AudioOutput)) {
        if (deviceInfo != defaultDeviceInfo)
            m_deviceBox->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
    }


    m_suspendResumeButton = new QPushButton();

    m_volumeLabel = new QLabel;
    m_volumeLabel->setText("Volume:");
    m_volumeSlider = new QSlider(Qt::Horizontal);
    m_volumeSlider->setMinimum(0);
    m_volumeSlider->setMaximum(100);
    m_volumeSlider->setSingleStep(10);



    gridLayout->addWidget(m_suspendResumeButton, 5, 0,1,3);
    gridLayout->addWidget(m_deviceBox, 6, 0,1,3);
    gridLayout->addWidget(m_volumeLabel, 7, 0,1,3);
    gridLayout->addWidget(m_volumeSlider, 8, 0,1,3);


    QMetaObject::connectSlotsByName(MainWindow);
}

void UIMW::addPlot(QMainWindow *MainWindow, QString label){

    if(plot_num<6){

        plot[plot_num] = new QCustomPlot(centralWidget);
        plot[plot_num]->setObjectName(QStringLiteral("plot"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(plot[0]->sizePolicy().hasHeightForWidth());
        plot[plot_num]->setSizePolicy(sizePolicy);
        plot[plot_num]->xAxis->setBasePen(QPen(Qt::white, 1));
        plot[plot_num]->yAxis->setBasePen(QPen(Qt::white, 1));
        plot[plot_num]->xAxis->setTickPen(QPen(Qt::white, 1));
        plot[plot_num]->yAxis->setTickPen(QPen(Qt::white, 1));
        plot[plot_num]->xAxis->setSubTickPen(QPen(Qt::white, 1));
        plot[plot_num]->yAxis->setSubTickPen(QPen(Qt::white, 1));
        plot[plot_num]->xAxis->setTickLabelColor(Qt::white);
        plot[plot_num]->yAxis->setTickLabelColor(Qt::white);
        plot[plot_num]->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        plot[plot_num]->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        plot[plot_num]->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        plot[plot_num]->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        plot[plot_num]->xAxis->grid()->setSubGridVisible(true);
        plot[plot_num]->yAxis->grid()->setSubGridVisible(true);
        plot[plot_num]->xAxis->grid()->setZeroLinePen(Qt::NoPen);
        plot[plot_num]->yAxis->grid()->setZeroLinePen(Qt::NoPen);
        plot[plot_num]->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        plot[plot_num]->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        plot[plot_num]->setBackground(plotGradient);
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        plot[plot_num]->axisRect()->setBackground(axisRectGradient);

        graphlabel[plot_num]= new QLabel;
        graphlabel[plot_num]->setText(label);

        if(plot_num < 3){
            gridLayout->addWidget(graphlabel[plot_num], 0, plot_num, 1, 1);
            gridLayout->addWidget(plot[plot_num], 1, plot_num, 1, 1);
        }else{
            gridLayout->addWidget(graphlabel[plot_num], 3, (plot_num-3), 1, 1);
            gridLayout->addWidget(plot[plot_num], 4, (plot_num-3), 1, 1);
        }

        if(plot_num>0){
            window_W *=1.3;
            if(plot_num == 3){
                window_H *=2;
            }
            MainWindow->resize(window_W,window_H);
        }
        plot_num++;
    }else{
        qWarning( "Too many graphs, cannot render more!" );

    }
}

int UIMW::getPlotInx(){
    return plot_num-1;
}

void UIMW::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Graph", nullptr));
    actionInsert_Plot->setText(QApplication::translate("MainWindow", "Insert Plot", nullptr));
    actionSave_Document->setText(QApplication::translate("MainWindow", "Save Document...", nullptr));
}

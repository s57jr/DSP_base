
#include "mainwindow.h"
#include "uimw.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  m_pushTimer(new QTimer(this)),
  ui(new Ui::MainWindow)

{
  this->move(100,100);

  auBuf = new audioBuffer(static_cast<int>(pow(2,19)));


  ui->setupUi(this);


  connect(ui->m_deviceBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::deviceChanged);
  connect(ui->m_suspendResumeButton, &QPushButton::clicked, this, &MainWindow::toggleSuspendResume);
  connect(ui->m_volumeSlider, &QSlider::valueChanged, this, &MainWindow::volumeChanged);

  initializeAudio(QAudioDeviceInfo::defaultOutputDevice());
  toggleMode();


}

MainWindow::~MainWindow()
{
  m_pushTimer->stop();
  delete ui;
}


void MainWindow::Plot(QString label,QVector<double> x, QVector<double> y)
{
  ui->addPlot(this, label);
  int plotnum = ui->getPlotInx();

  // The following plot[0] setup is mostly taken from the plot[0] demos:
  ui->plot[plotnum]->addGraph();
  ui->plot[plotnum]->graph()->setPen(QPen(Qt::green));
  ui->plot[plotnum]->graph()->setBrush(QBrush(QColor(0, 255, 0, 50)));
  ui->plot[plotnum]->graph()->setData(x, y);
  ui->plot[plotnum]->axisRect()->setupFullAxesBox(true);
  ui->plot[plotnum]->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

  double min = *std::min_element(y.constBegin(), y.constEnd());
  double max = *std::max_element(y.constBegin(), y.constEnd());

  ui->plot[plotnum]->xAxis->setRange(0 , static_cast<int>(x.length()));

  ui->plot[plotnum]->yAxis->setRange(min, max);

}


void MainWindow::Plot(QString label,QVector<float> x, QVector<float> y)
{
    QVector<double> x1(x.size()),y1(y.size());

    for(int i=0;i<x.size();i++){
        x1[i]=static_cast<double>(x[i]);
    }
    for(int i=0;i<y.size();i++){
        y1[i]=static_cast<double>(y[i]);
    }
    Plot(label, x1, y1);
}

void MainWindow::initializeAudio(const QAudioDeviceInfo &deviceInfo)
{

    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);


    if (!deviceInfo.isFormatSupported(format)) {
        qWarning() << "Default format not supported - trying to use nearest";
        format = deviceInfo.nearestFormat(format);
    }


    m_audioOutput.reset(new QAudioOutput(deviceInfo, format));

    qreal initialVolume = QAudio::convertVolume(m_audioOutput->volume(),
                                                QAudio::LinearVolumeScale,
                                                QAudio::LogarithmicVolumeScale);
    ui->m_volumeSlider->setValue(qRound(initialVolume * 100));


    toggleMode();

}

void MainWindow::deviceChanged(int index)
{
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
    initializeAudio(ui->m_deviceBox->itemData(index).value<QAudioDeviceInfo>());
}

void MainWindow::volumeChanged(int value)
{
    qreal linearVolume = QAudio::convertVolume(value / qreal(100),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    m_audioOutput->setVolume(linearVolume);
}


void MainWindow::toggleMode()
{
    m_pushTimer->stop();
    m_audioOutput->stop();
    toggleSuspendResume();


    auto io = m_audioOutput->start();
    m_pushTimer->disconnect();

    connect(m_pushTimer, &QTimer::timeout, [this, io]() {
        if (m_audioOutput->state() == QAudio::StoppedState)
            return;

        double data[44100];

        for(int i=0;i<44100;i++){
            data[i] = sin(2*M_PI*800*i/44100.0);
        }

        if(auBuf->bytesFree() > 44100*2){
            auBuf->writeData(data,44100);
        }

        QByteArray buffer(32768, 0);
        int chunks = m_audioOutput->bytesFree() / m_audioOutput->periodSize();
        while (chunks) {
           const qint64 len = auBuf->readData(buffer.data(), m_audioOutput->periodSize());
           if (len)
               io->write(buffer.data(), len);
           if (len != m_audioOutput->periodSize())
               break;
           --chunks;
        }
    });

    m_pushTimer->start(20);


}

void MainWindow::toggleSuspendResume()
{
    if (m_audioOutput->state() == QAudio::SuspendedState || m_audioOutput->state() == QAudio::StoppedState) {
        m_audioOutput->resume();
        ui->m_suspendResumeButton->setText(tr("Suspend recording"));
    } else if (m_audioOutput->state() == QAudio::ActiveState) {
        m_audioOutput->suspend();
        ui->m_suspendResumeButton->setText(tr("Resume playback"));
    } else if (m_audioOutput->state() == QAudio::IdleState) {
        // no-op
    }
}


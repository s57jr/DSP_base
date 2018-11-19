

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioOutput>


#include <iostream>
#include "../qcustomplot/qcustomplot.h"
#include "audiobuffer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  void Plot(QString label, QVector<double> x, QVector<double> y);
  void Plot(QString label, QVector<float> x, QVector<float> y);

  audioBuffer *auBuf=nullptr;

private:

  QTimer *m_pushTimer = nullptr;

  Ui::MainWindow *ui;
  QAudioFormat format;
  QScopedPointer<QAudioOutput> m_audioOutput;

    void initializeAudio(const QAudioDeviceInfo &deviceInfo);

private slots:
    void toggleMode();
    void toggleSuspendResume();
    void deviceChanged(int index);
    void volumeChanged(int);
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifdef _MSC_VER //just for MSVC
   #pragma warning (push)
   #pragma warning (disable: 4068)
      #include <ogdf/fileformats/GraphIO.h>
   #pragma warning (pop)
#elif ...// other compilers
#endif

#include <QMainWindow>
#include <axisform.h>
#include <tmachine.h>
#include <tfiletograph.h>

#include <QtSvg/QSvgWidget>
#include <QtSvg/QtSvg>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_graphBox_currentIndexChanged(int index);

    void resizeEvent(QResizeEvent* event);

    void on_timeAxisOpen_clicked();

    void on_crWayButton_clicked();

    void paramsChanged();

private:
    Ui::MainWindow *ui;
    AxisForm *axisForm;
    QString openFilesPath;
    TMachine *MVS;
    QSvgWidget *svgWGT;
    TFileToGraph *Converter;
    QStringList filenames;
    QStringList files;

};

#endif // MAINWINDOW_H

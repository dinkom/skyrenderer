#include <QtGui>
#include <QMainWindow>
#include "controls.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private slots:
    void about();

private:
    QMenu *menu;
    QToolBar *toolBar;
    QWidget *mainFrame;
    QVBoxLayout *layout;
    Controls *controls;
};

#include <QtGui>
#include <QFormLayout>
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>

class Controls : public QWidget
{
    Q_OBJECT

public:
    Controls();

private slots:
    void render();

private:
    QFormLayout *layout;
    QLabel *rayleighLabel;
    QSpinBox *rayleigh;
    QLabel *mieLabel;
    QSpinBox *mie;
    QLabel *angleLabel;
    QSpinBox *angle;
    QLabel *status;
    QPushButton *renderButton;
};

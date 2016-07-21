#ifndef STRINGS_H
#define STRINGS_H
#include "strings.h"
#endif

#include "render.cpp"
#include "controls.h"
#include <QFileDialog>
#include <QMessageBox>
#include <ctime>

Controls::Controls()
{
    ControlValues *controlValues = new ControlValues;
    int spinBoxWidth = 250, btnWidth = 260, btnHeight = 50;
    layout = new QFormLayout(this);

    rayleighLabel = new QLabel;
    rayleighLabel->setText(SkyStrings::rayleighLabel());
    rayleighLabel->setToolTip(SkyStrings::rayleighTooltip());

    rayleigh = new QSpinBox;
    rayleigh->setMaximum(controlValues->maxRayleigh);
    rayleigh->setMinimum(controlValues->minRayleigh);
    rayleigh->setValue(controlValues->defaultRayleigh);
    rayleigh->setFixedWidth(spinBoxWidth);

    mieLabel = new QLabel;
    mieLabel->setText(SkyStrings::mieLabel());
    mieLabel->setToolTip(SkyStrings::mieTooltip());

    mie = new QSpinBox;
    mie->setMaximum(controlValues->maxMie);
    mie->setMinimum(controlValues->minMie);
    mie->setValue(controlValues->defaultMie);
    mie->setFixedWidth(spinBoxWidth);

    angleLabel = new QLabel;
    angleLabel->setText(SkyStrings::angleLabel());

    angle = new QSpinBox;
    angle->setMaximum(controlValues->maxAngle);
    angle->setMinimum(controlValues->minAngle);
    angle->setValue(controlValues->defaultAngle);
    angle->setFixedWidth(spinBoxWidth);

    status = new QLabel;
    status->setText(SkyStrings::selectValues());
    status->setStyleSheet(SkyStrings::blueTextColor());

    renderButton = new QPushButton(SkyStrings::renderButtonText());
    renderButton->setFixedSize(btnWidth, btnHeight);

    layout->addWidget(rayleighLabel);
    layout->addWidget(rayleigh);
    layout->addWidget(mieLabel);
    layout->addWidget(mie);
    layout->addWidget(angleLabel);
    layout->addWidget(angle);
    layout->addWidget(status);
    layout->addWidget(renderButton);

    connect(renderButton, SIGNAL(clicked()), this, SLOT(render()));
}

void Controls::render()
{
    status->setText(SkyStrings::rendering());
    status->setStyleSheet(SkyStrings::blueTextColor());
    QMessageBox *message;
    QString filename = QFileDialog::getSaveFileName(this,
             SkyStrings::whereToSave(), SkyStrings::defaultFileName(),
             SkyStrings::filenameFilter());
    if (filename.isEmpty()) {
        message = new QMessageBox;
        message->setText(SkyStrings::filenameWarning());
        message->show();
        status->setText(SkyStrings::selectValues());
        return;
    }
    renderButton->setEnabled(false);
    float t = clock();
    float angle_user = angle->value();
    int rs = rayleigh->value();
    int ms = mie->value();
    float calculated_angle = angle_user / 128 * M_PI * 0.6;
    renderImage<float>(Vec3<float>(0, cos(calculated_angle), -sin(calculated_angle)), filename, rs, ms);
    float seconds = (clock() - t)/float(CLOCKS_PER_SEC);
    QString time_spent_rendering = SkyStrings::finishedIn() + QString::number(seconds, 'f', 2) + SkyStrings::seconds();
    status->setText(time_spent_rendering);
    status->setStyleSheet(SkyStrings::greenTextColor());
    renderButton->setEnabled(true);
}


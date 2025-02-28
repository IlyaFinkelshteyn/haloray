#include "renderButton.h"
#include <QString>

RenderButton::RenderButton(QWidget *parent)
    : QPushButton(parent), mRendering(false)
{
    const QString renderText = tr("Render");
    const QString stopText = tr("Stop");

    setText(renderText);
    setStyleSheet("font: bold;");
    setMinimumHeight(100);

    connect(this, &RenderButton::clicked, [this, renderText, stopText]() {
        if (mRendering)
            this->setText(renderText);
        else
            this->setText(stopText);
        mRendering = !mRendering;
    });
}

#include "view.h"
#include "ui_view.h"
#include <QKeyEvent>
#include <QDebug>

View::View(QWidget *parent)
    : QWidget{parent},
      mView(new Ui::View)
{
    mView->setupUi(this);
    QObject::connect(mView->mButton0, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton1, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton2, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton3, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton4, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton5, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton6, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton7, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton8, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButton9, &QPushButton::clicked, this, &View::buttonPressed);

    QObject::connect(mView->mButtonDot, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonClear, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonModulo, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonDivide, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonMinus, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonAdd, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonEquals, &QPushButton::clicked, this, &View::buttonPressed);
    QObject::connect(mView->mButtonMultiply, &QPushButton::clicked, this, &View::buttonPressed);
}

void View::keyPressEvent(QKeyEvent *event)
{
    if ((event->key() >= Qt::Key_0) && (event->key() <= Qt::Key_9))
    {
        QString val = QString::number(event->key() - Qt::Key_0);
        emit valuePressed(val);
    }
    else if(event->key() == Qt::Key_Plus)
    {
        emit valuePressed("+");
    }
    else if(event->key() == Qt::Key_Minus)
    {
        emit valuePressed("-");
    }
    else if(event->key() == 42)
    {
        emit valuePressed("*");
    }
    else if(event->key() == 47)
    {
        emit valuePressed("/");
    }
    else if(event->key() == Qt::Key_Percent)
    {
        emit valuePressed("%");
    }
    else if(event->key() == Qt::Key_Period)
    {
        emit valuePressed(".");
    }
    else if(event->key() == Qt::Key_Enter)
    {
        emit resultNeeded();
    }
    else if(event->key() == Qt::Key_Escape)
    {
        emit clearPressed();
    }

    QWidget::keyPressEvent(event);
}

void View::buttonPressed()
{
    QString buttonText = static_cast<QPushButton*>(sender())->text().toUpper();
    if(buttonText == "CE")
    {
        emit clearPressed();
    }
    else if (buttonText == "=")
    {
        emit resultNeeded();
    }
    else
    {
        emit valuePressed(buttonText);
    }
}

View::~View()
{
    delete mView;
}

void View::updateDisplay(const QString &text)
{
    mView->mLabelResult->setText(text);
}

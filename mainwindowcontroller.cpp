#include "mainwindowcontroller.h"
#include <QJSEngine>
#include <QDebug>
MainWindowController::MainWindowController(QWidget *parent)
    : QMainWindow(parent),
      mView(new View(this)),
      mJSEngine(new QJSEngine(this))
{
    setCentralWidget(mView);

    QObject::connect(mView, &View::resultNeeded, this, &MainWindowController::calculateResult);
    QObject::connect(mView, &View::valuePressed, this, [this](const QString &val) {
        mCurrentExpression += val;
        mView->updateDisplay(mCurrentExpression);
    });
    QObject::connect(mView, &View::clearPressed, this, [this](){
        mCurrentExpression.clear();
        mView->updateDisplay("");
    });

    this->setMaximumSize(mView->maximumSize());
}

MainWindowController::~MainWindowController()
{
}

void MainWindowController::calculateResult()
{
    if(mCurrentExpression.isEmpty())
    {
        return;
    }

    auto val = mJSEngine->evaluate(mCurrentExpression);
    if(val.isError())
    {
        updateError(val.errorType());
    }
    else
    {
        mView->updateDisplay(QString::number(val.toNumber()));
    }
    mCurrentExpression.clear();
}

void MainWindowController::updateError(QJSValue::ErrorType errorType)
{
    switch(errorType)
    {
        case QJSValue::NoError:
            break;

        case QJSValue::GenericError:
            mView->updateDisplay("GenericError");
            break;

        case QJSValue::EvalError:
            mView->updateDisplay("EvalError");
            break;

        case QJSValue::RangeError:
            mView->updateDisplay("RangeError");
            break;

        case QJSValue::ReferenceError:
            mView->updateDisplay("ReferenceError");
            break;

        case QJSValue::SyntaxError:
            mView->updateDisplay("SyntaxError");
            break;

        case QJSValue::TypeError:
            mView->updateDisplay("TypeError");
            break;

        case QJSValue::URIError:
            mView->updateDisplay("URIError");
            break;

        default:
            break;
    }
}


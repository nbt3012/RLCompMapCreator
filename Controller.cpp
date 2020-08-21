#include "Controller.h"

Controller::Controller(QString outputFile, QObject *parent) : QObject(parent),
    output(outputFile)
{

}

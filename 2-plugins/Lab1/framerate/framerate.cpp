#include "framerate.h"
#include "glwidget.h"

void Framerate::printFPS()
{
    cout << frames << endl;
    frames = 0;
}

void Framerate::preFrame()
{
	
}

void Framerate::postFrame()
{
	frames++;
}

void Framerate::onPluginLoad()
{
    frames=0;
    QTimer *frameTimer=new QTimer(this);
    connect(frameTimer, SIGNAL(timeout()), this, SLOT(printFPS()));
    frameTimer->start(1000);
}

#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "plugin.h" 

class Framerate: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void preFrame();
	 void postFrame();
     void onPluginLoad();

  private:
      int frames;

  public slots:
      void printFPS();
};

#endif

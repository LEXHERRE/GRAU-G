#ifndef _OCCUPANCY_H
#define _OCCUPANCY_H

#include "plugin.h" 

class Occupancy: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
};

#endif

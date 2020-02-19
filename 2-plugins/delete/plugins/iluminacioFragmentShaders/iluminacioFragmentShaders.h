#ifndef _ILUMINACIOFRAGMENTSHADERS_H
#define _ILUMINACIOFRAGMENTSHADERS_H

#include "plugin.h"
#include <QGLShader>
#include <QGLShaderProgram>

class IluminacioFragmentShaders: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin")
	Q_INTERFACES(Plugin)

  public:
	 void onPluginLoad();
	 void preFrame();
	 void postFrame();

   private:
       QOpenGLShaderProgram* program;
       QOpenGLShader *fs, *vs;
       
       Vector lightAmbient;
       Vector lightDiffuse;
       Vector lightSpecular;
       QVector4D lightPosition;
       
       Vector materialAmbient;
       Vector materialDiffuse;
       Vector materialSpecular;
       float materialShininess;
};

#endif

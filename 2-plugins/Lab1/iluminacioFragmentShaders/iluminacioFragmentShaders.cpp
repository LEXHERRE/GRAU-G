#include "iluminacioFragmentShaders.h"
#include "glwidget.h"

void IluminacioFragmentShaders::onPluginLoad()
{
	QString vs_src =
	"#version 330 core\n"
	"layout (location = 0) in vec3 vertex;"
	"layout (location = 1) in vec3 normal;"
	"out vec3 vertexF;"
	"out vec3 normalF;"
	"uniform mat4 modelViewProjectionMatrix;"
	"void main(){"
		"normalF = normal;"
		"vertexF = vertex;"
		"gl_Position = modelViewProjectionMatrix * vec4(vertex, 1.0);}";
	vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vs -> compileSourceCode(vs_src);
	cout << "VS log: " << vs -> log().toStdString() << endl;
	
    QString fs_src =
	"#version 330 core\n"
	"in vec3 vertexF;"
	"in vec3 normalF;"
	"out vec4 fragColor;"
	"uniform mat4 modelViewMatrix;"
	"uniform mat3 normalMatrix;"
	"uniform vec4 matAmbient, matDiffuse, matSpecular;"
	"uniform float matShininess;"
	"uniform vec4 lightAmbient, lightDiffuse, lightSpecular, lightPosition;"
	"vec4 light(vec3 N, vec3 V, vec3 L){"
		"N = normalize(N);"
		"V = normalize(V);"
		"L = normalize(L);"
		"vec3 R = normalize(2.0 * dot(N,L) * N-L);"
		"float NdotL = max(0.0, dot(N,L));"
		"float RdotV = max(0.0, dot(R,V));"
		"float Idiff = NdotL;"
		"float Ispec = 0;"
		"if (NdotL > 0) Ispec = pow(RdotV, matShininess);"
		"return matAmbient * lightAmbient +"
				"matDiffuse * lightDiffuse * Idiff +"
				"matSpecular * lightSpecular * Ispec;}"
	"void main(){"
		"vec3 P = (modelViewMatrix * vec4(vertexF, 1.0)).xyz;"
		"vec3 N = normalize(normalMatrix * normalF);"
		"vec3 V = -P;"
		"vec3 L = (lightPosition.xyz - P);"
		"fragColor = light(N, V, L);}";
		
	fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;
    
    
    lightAmbient = Vector(0.1,0.1,0.1);
    lightDiffuse = Vector(1,1,1);
    lightSpecular = Vector(1,1,1);

    lightPosition = QVector4D(0,0,0,1);
    
    materialAmbient = Vector(0.8, 0.8, 0.6);
    materialDiffuse = Vector(0.8, 0.8, 0.6);
    materialSpecular = Vector(1.0, 1.0, 1.0);
    materialShininess = 64.0;
}

void IluminacioFragmentShaders::preFrame()
{
    // bind shader and define uniforms
	program->bind();
    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    program->setUniformValue("modelViewMatrix", camera()->viewMatrix());
	program->setUniformValue("normalMatrix", camera()->viewMatrix().normalMatrix());
	program->setUniformValue("matAmbient", QVector4D(materialAmbient,1));
	program->setUniformValue("matDiffuse", QVector4D(materialDiffuse,1));
	program->setUniformValue("matSpecular", QVector4D(materialSpecular,1));
	program->setUniformValue("matShininess", materialShininess);
	program->setUniformValue("lightAmbient", QVector4D(lightAmbient,1));
	program->setUniformValue("lightDiffuse", QVector4D(lightDiffuse,1));
	program->setUniformValue("lightSpecular", QVector4D(lightSpecular,1));
	program->setUniformValue("lightPosition", lightPosition);
}

void IluminacioFragmentShaders::postFrame()
{
    // unbind shader
    program->release();
}

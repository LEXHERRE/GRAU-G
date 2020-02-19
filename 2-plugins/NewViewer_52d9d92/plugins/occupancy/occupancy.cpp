#include "occupancy.h"
#include "glwidget.h"

void Occupancy::onPluginLoad()
{
    Scene* scn = scene();
    float volum = 0;
    
    const Object& obj = scn->objects()[0];
    int nfaces = obj.faces().size();
    for (int i = 0; i<nfaces; ++i) {
        const Face& face = obj.faces()[i];
        //int V1 = obj.vertices()[face.vertexIndex(0)];
        //int V2 = obj.vertices()[face.vertexIndex(1)];
        //int V3 = obj.vertices()[face.vertexIndex(2)];
        //Point C = (V1+V2+V3)/3;
        
        QVector3D N = face.normal();
        //QVector3D v1 = V2-V1;
        //QVector3D v2 = V3-V1;
        //float A = mod(crossProduct(v1,v2))/2;
        //volum += (C.x * N.x * A)
    }
    
    
    float volumCapsa=0;    
    QVector3D b = obj.boundingBox().max()-obj.boundingBox().min();
    volumCapsa = b.x() * b.y() * b.z();
    
    cout << "Volum: " << volum << endl;
    cout << "Volum Capsa: " << volumCapsa << endl;
    cout << "Occupancy: " << volum/volumCapsa << endl;
}

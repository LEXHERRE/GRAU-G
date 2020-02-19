#include "modelInfo1.h"
#include "glwidget.h"

void ModelInfo1::printModelInfo(){
    Scene* scn = scene();
	int nObj = scn->objects().size();
    int nPol = 0, nVer = 0, nTri = 0;
    
    for (int i = 0; i<nObj; ++i) {
        const Object& obj = scn->objects()[i];
        int nfaces = obj.faces().size();
        nPol += nfaces;
        for (int j = 0; j<nfaces; ++j) {
            const Face& face = obj.faces()[j];
            nVer += face.numVertices();
            if (face.numVertices()%3 == 0) ++nTri;
        }
    }
    
    cout << "INFO:" << endl;
    cout << " - Num objectes: " << nObj << endl;
    cout << " - Num polígons: " << nPol << endl;
    cout << " - Num vèrtexs: " << nVer << endl;
    cout << " - Num triangles: " << nTri << endl;
    if (nPol!=0) cout << " - Percentatge de triangles: " << double(nTri/nPol) * 100 << '%' << endl;
    else cout << " - Percentatge de triangles: NULL" << endl;
}

void ModelInfo1::onPluginLoad()
{
    printModelInfo();
}

void ModelInfo1::onObjectAdd()
{
    printModelInfo();
}

void ModelInfo1::onObjectLoad()
{
    printModelInfo();
}

void ModelInfo1::onSceneClear()
{
    printModelInfo();
}

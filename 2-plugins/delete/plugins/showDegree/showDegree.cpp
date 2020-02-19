#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
    const Object &obj = scene()->objects()[0];
    const int nCares = obj.faces().size();
    const int nVertexCares = nCares*3; // cada cara te 3 vertex (trianges)
    const int nVertex = obj.vertices().size();
    grauMig = double(nVertexCares)/nVertex;
}

void ShowDegree::postFrame()
{
    painter.begin(glwidget());
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);
    //painter.setPen(QColor(255,0,0));

    painter.drawText(5, 20, QString("%1").arg(grauMig));
    painter.end();
}

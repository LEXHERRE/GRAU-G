#include "drawSmooth.h"
#include "glwidget.h"
#include <cassert>
#include <cmath>

DrawSmooth::~DrawSmooth() {
  cleanUp();
}

void DrawSmooth::onSceneClear()
{
    cleanUp();
}

void DrawSmooth::cleanUp()
{
  GLWidget &g = *glwidget();
  
  g.glDeleteBuffers(coordBuffers.size(),  &coordBuffers[0]);
  g.glDeleteBuffers(normalBuffers.size(), &normalBuffers[0]);
  g.glDeleteBuffers(stBuffers.size(),  &stBuffers[0]);
  g.glDeleteBuffers(colorBuffers.size(),  &colorBuffers[0]);
  g.glDeleteBuffers(indexBuffers.size(),  &indexBuffers[0]);
  
  g.glDeleteVertexArrays(VAOs.size(), &VAOs[0]);
  
  coordBuffers.clear();
  normalBuffers.clear();
  stBuffers.clear();
  colorBuffers.clear();
  indexBuffers.clear();
  VAOs.clear();
  
  numIndices.clear();
}

bool DrawSmooth::drawObject(int i)
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  
  g.glBindVertexArray(VAOs[i]);
  g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*)0);
  g.glBindVertexArray(0);
  
  return true;
}

bool DrawSmooth::drawScene()
{
  GLWidget &g = *glwidget();
  g.makeCurrent();
  
  for(unsigned int i=0; i<VAOs.size(); i++){ // for each buffer (that is, for each object)
	g.glBindVertexArray(VAOs[i]);
    g.glDrawElements(GL_TRIANGLES, numIndices[i], GL_UNSIGNED_INT, (GLvoid*)0);
    //drawObject(i);
  }
  g.glBindVertexArray(0);
  
  return true;
}

void DrawSmooth::onPluginLoad()
{
  for(unsigned int i=0; i<scene()->objects().size(); i++)
    addVBO(i);
}

void DrawSmooth::onObjectAdd()
{
  addVBO( scene()->objects().size() - 1 );
}

void DrawSmooth::addVBO(unsigned int currentObject)
{
  const Object& obj = scene()->objects()[currentObject];
  // DELETEME //unsigned int numvertices = obj.faces().size()*3;  // it's all triangles...
  vector<float> vertices; // (x,y,z)    Final size: 3*number of corners
  vector<float> normals;  // (nx,ny,nz) Final size: 3*number of corners
  vector<float> colors;   // (r, g, b)  Final size: 3*number of corners
  vector<float> texCoords;// (s, t)     Final size: 2*number of corners
  vector<int> indices;   // (r, g, b)  Final size: 3*number of triangles
  auto verts = obj.vertices();
  // DELETEME //auto Ns = obj.vertNormals();
  // DELETEME //auto texcords = obj.vertTexCoords();

  vector<Vector> VN(obj.vertices().size(), Vector(0,0,0));
  vector<int> VC(obj.vertices().size(), 0); 
  
  for (auto&& f: obj.faces()) {
      const Vector &N=f.normal().normalized();
      for (int i=0; i<(int)f.numVertices(); ++i){
          VN[f.vertexIndex(i)]+=N;
          ++VC[f.vertexIndex(i)];
      }
  }
  
  for (int i=0; i<(int)verts.size(); ++i) {
    Vector N=VN[i]/VC[i];
    const Point &P=verts[i].coord();
    vertices.push_back(P.x()); vertices.push_back(P.y()); vertices.push_back(P.z());
    normals.push_back(N.x()); normals.push_back(N.y()); normals.push_back(N.z());
    float r=obj.boundingBox().radius();
    float s=Vector::dotProduct((1.0/r)*Vector(1,0,1), P);
    float t=Vector::dotProduct((1.0/r)*Vector(0,1,0), P);
//     if ((int)verts.size()==81) {    // plane: special case for /assig models
//       s=0.5f*(P.x()+1.0);
//       t=0.5f*(P.y()+1.0);
//     }
//     if ((int)verts.size()==386) {   // cube: special case for /assig models
//       s=Vector::dotProduct((1.0/2.0)*Vector(1,0,1), P);
//       t=Vector::dotProduct((1.0/2.0)*Vector(0,1,0), P);
//     }
    texCoords.push_back(s);
    texCoords.push_back(t);
    colors.push_back(abs(N.x()));
    colors.push_back(abs(N.y()));
    colors.push_back(abs(N.z()));
  }
  
  for (auto&& f: obj.faces()) {
    for (int i=0; i<(int)f.numVertices(); ++i) 
      indices.push_back(f.vertexIndex(i));
  }

  assert(vertices.size() == 3*verts.size());
  assert(normals.size() == 3*verts.size());
  assert(colors.size() == 3*verts.size());
  assert(texCoords.size() == 2*verts.size());
  assert(indices.size() == 3*obj.faces().size());
  
  // Step 2: Create VAO and empty buffers (coords, normals, ...)
  GLWidget& g = *glwidget();
  
  GLuint VAO;
  g.glGenVertexArrays(1, &VAO);
  VAOs.push_back(VAO);
  g.glBindVertexArray(VAO);
  
  GLuint coordBufferID;
  g.glGenBuffers(1, &coordBufferID);
  coordBuffers.push_back(coordBufferID);
  
  GLuint normalBufferID;
  g.glGenBuffers(1, &normalBufferID);
  normalBuffers.push_back(normalBufferID);
  
  GLuint stBufferID;
  g.glGenBuffers(1, &stBufferID);
  stBuffers.push_back(stBufferID);
  
  GLuint colorBufferID;
  g.glGenBuffers(1, &colorBufferID);
  colorBuffers.push_back(colorBufferID);
  
  GLuint indexBufferID;
  g.glGenBuffers(1, &indexBufferID);
  indexBuffers.push_back(indexBufferID);
  
  numIndices.push_back(indices.size());
  
  // Step 3: Define VBO data (coords, normals, ...)
  g.glBindBuffer(GL_ARRAY_BUFFER, coordBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*vertices.size(), &vertices[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); 
  g.glEnableVertexAttribArray(0);

  g.glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*normals.size(), &normals[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(1);

  g.glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*colors.size(), &colors[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(2);

  g.glBindBuffer(GL_ARRAY_BUFFER, stBufferID);
  g.glBufferData(GL_ARRAY_BUFFER, sizeof(float)*texCoords.size(), &texCoords[0], GL_STATIC_DRAW);
  g.glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
  g.glEnableVertexAttribArray(3);
  
  g.glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
  g.glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*indices.size(), &indices[0], GL_STATIC_DRAW);
  
  g.glBindBuffer(GL_ARRAY_BUFFER,0);
  g.glBindVertexArray(0);
}

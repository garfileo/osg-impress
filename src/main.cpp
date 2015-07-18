#include <osg/Node>
#include <osg/Group>
#include <osg/Geode>
#include <osg/Geometry>
#include <osgViewer/Viewer>
#include <osg/PositionAttitudeTransform>
#include <osgGA/TrackballManipulator>

using namespace osg;

float myTimer = 0;

const int CHILDREN = 10;
PositionAttitudeTransform *transform[CHILDREN];

Group * startupScene()
{
	// vertex array
	Vec3Array *vertexArray = new Vec3Array();
	vertexArray->push_back(Vec3(-1, -1, 0)); // front left 
	vertexArray->push_back(Vec3(+1, -1, 0)); // front right 
	vertexArray->push_back(Vec3(+1, +1, 0)); // back right 
	vertexArray->push_back(Vec3(-1, +1, 0)); // back left 
	vertexArray->push_back(Vec3( 0,  0, sqrt(2))); // peak
	vertexArray->push_back(Vec3( 0,  0, -sqrt(2))); // lower peak

	// face array
	// give indices of vertices in counter-clockwise order
	DrawElementsUInt *faceArray = new DrawElementsUInt(PrimitiveSet::TRIANGLES, 0);
	faceArray->push_back(0); // face 0
	faceArray->push_back(1);
	faceArray->push_back(4);
	faceArray->push_back(1); // face 1
	faceArray->push_back(2);
	faceArray->push_back(4);
	faceArray->push_back(2); // face 2
	faceArray->push_back(3);
	faceArray->push_back(4);
	faceArray->push_back(3); // face 3
	faceArray->push_back(0);
	faceArray->push_back(4);
	faceArray->push_back(0); // face 4
	faceArray->push_back(5);
	faceArray->push_back(1);
	faceArray->push_back(2); // face 5
	faceArray->push_back(1);
	faceArray->push_back(5);
	faceArray->push_back(3); // face 6
	faceArray->push_back(2);
	faceArray->push_back(5);
	faceArray->push_back(0); // face 7
	faceArray->push_back(3);
	faceArray->push_back(5);

	// vertex color array
	Vec4Array *colorArray = new Vec4Array();
	colorArray->push_back(Vec4(1.0f, 0.0f, 0.0f, 1.0f) ); //index 0 red
	colorArray->push_back(Vec4(0.0f, 1.0f, 0.0f, 1.0f) ); //index 1 green
	colorArray->push_back(Vec4(0.0f, 0.0f, 1.0f, 1.0f) ); //index 2 blue
	colorArray->push_back(Vec4(1.0f, 0.0f, 1.0f, 1.0f) ); //index 3 purple
	colorArray->push_back(Vec4(1.0f, 1.0f, 1.0f, 1.0f) ); //index 4 white

	// color index
	TemplateIndexArray<unsigned int, Array::UIntArrayType, 5, 4> *colorIndexArray;
	colorIndexArray = new TemplateIndexArray<unsigned int, Array::UIntArrayType, 5, 4>();
	colorIndexArray->push_back(0); // vertex 0 assigned color array element 0
	colorIndexArray->push_back(1); // vertex 1 assigned color array element 1
	colorIndexArray->push_back(2); // vertex 2 assigned color array element 2
	colorIndexArray->push_back(3); // vertex 3 assigned color array element 3
	colorIndexArray->push_back(4); // vertex 4 assigned color array element 4
	colorIndexArray->push_back(4); // vertex 5 assigned color array element 4

        Geometry *geometry = new Geometry();
	geometry->setVertexArray(vertexArray);
	geometry->setColorArray(colorArray);
	geometry->setColorBinding(Geometry::BIND_PER_VERTEX);
	geometry->addPrimitiveSet(faceArray);

	Geode *pyramidObject = new Geode();
	pyramidObject->addDrawable(geometry);

	Group *root = new Group();

	for (int i = 0; i < CHILDREN; i++) {
		transform[i] = new PositionAttitudeTransform;
		transform[i]->setPosition(Vec3(0,0,0));
		transform[i]->addChild(pyramidObject);

		root->addChild(transform[i]);
	}

	return root;
}

void update(float dt) {
	// keep track of the time
	myTimer += dt;

	int a = 3;
	int b = 4;
	double ro = ((b - 1)/b) * (PI / 2);

	// static geo in the middle
	transform[0]->setPosition(Vec3(0, 0, CHILDREN/2));

	for (int i = 1; i < CHILDREN; i++) {
		transform[i]->setPosition(Vec3(sin(a * myTimer*i + ro) * (10 + i), sin(b * myTimer*i) * (10 + i), i));
	}
}

int main() {
	Group *scene = startupScene();

	osgViewer::Viewer viewer;
	viewer.setSceneData(scene);
	viewer.setCameraManipulator(new osgGA::TrackballManipulator());
	viewer.realize();

	while (!viewer.done()) {		
		viewer.frame();
		update(0.005); // do the update advancing 5ms
	} 

	return 0;
}

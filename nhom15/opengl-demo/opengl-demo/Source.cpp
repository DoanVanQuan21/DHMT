#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float xyzw[4];
	float rgba[4];
	float normal[4];
} Vertex;
//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3
	// Mảng dữ liệu
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0.75f, 0.75f, 0.75f, 0.75f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0.75f, 0.75f, 0.75f, 0.75f },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0.75f, 0.75f, 0.75f, 0.75f },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0.5f, 0.5f, 0.5f, 0.5f },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 1.0f, 0.0f, 0.0f, 1.0f },{ 0, 0,-1, 0 } }
};
// ----------------------------------------

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].xyzw);
const size_t NormalOffset = sizeof(Vertices[0].xyzw) + sizeof(Vertices[1].rgba);

int CurrentWidth = 1200,
CurrentHeight = 1000;

class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp,
ghe_cpp,
quaytr2_cpp,
vtgheda_cpp,
vtco_cpp,
vtden_cpp,
instance;
int
model_mat_location,
view_mat_location,
projection_mat_location;

float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

float qtruc = 0.0f, qtro2=0.0f, tttro2=0.0f;


bool
translated = false,
rotated = false,
scaled = false;

// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
void cube(float x = 1.0f, float y = 1.0f, float z = 1.0f)
{
	instance = scale(vec3(x, y, z));
	mat4 model = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
float trans_x = 0, trans_y = 0, trans_z = 0;
float xoay_y = 0, xoay_z = 0;
/*Tạo hình*/
#pragma region Cai cua

void nendat() {
	////thanh tren
	//mvstack.push(model_mat_cpp);
	//instance = translate(vec3(0, 0.45f, 0)) * scale(vec3(0.5f, 0.1f, 0.05f));
	//mat4 model_tren = model_mat_cpp * instance;
	//glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tren.m);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
	////thanh duoi
	//mvstack.push(model_mat_cpp);
	//instance = translate(vec3(0, -0.45f, 0)) * scale(vec3(0.5f, 0.1f, 0.05f));
	//mat4 model_duoi = model_mat_cpp * instance;
	//glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_duoi.m);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
	////thanh trai
	//mvstack.push(model_mat_cpp);
	//instance = translate(vec3(-0.3, 0, 0)) * scale(vec3(0.1f, 1, 0.05f));
	//mat4 model_trai = model_mat_cpp * instance;
	//glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_trai.m);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
	////thanh phai
	//mvstack.push(model_mat_cpp);
	//instance = translate(vec3(0.3, 0, 0)) * scale(vec3(0.1f, 1, 0.05f));
	//mat4 model_phai = model_mat_cpp * instance;
	//glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_phai.m);
	//glDrawArrays(GL_TRIANGLES, 0, 36);
	//model_mat_cpp = mvstack.pop();
	//thanh giua
	mvstack.push(model_mat_cpp);
	instance = scale(vec3(5.0f, 0.05f, 5.0f));
	mat4 model_giua = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_giua.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}
void hangrao() {
	//trai
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(2.5, 0.15, 0)) * scale(vec3(0.05f, 0.3f, 5.0f));
	mat4 model_rao_trai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_rao_trai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//phai
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-2.5, 0.15, 0)) * scale(vec3(0.05f, 0.3f, 5.0f));
	mat4 model_rao_phai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_rao_phai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//sau
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.0, 0.15, -2.5)) * scale(vec3(5.0f, 0.3f, 0.05f));
	mat4 model_rao_sau = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_rao_sau.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//truoctrai
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.5, 0.15, 2.5)) * scale(vec3(1.0f, 0.3f, 0.05f));
	mat4 model_rao_truoct = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_rao_truoct.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//truocphai
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.5, 0.15, 2.5)) * scale(vec3(1.0f, 0.3f, 0.05f));
	mat4 model_rao_truocp = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_rao_truocp.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void nentro1() {
	//nentro1
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 0.06, -1.8)) * scale(vec3(1.0f, 0.05f, 1.0f));
	mat4 model_nentro1 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_nentro1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//trục tro chơi
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 1.26, -1.8)) * scale(vec3(0.2f, 2.5f, 0.2f));
	mat4 model_tructro1 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tructro1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}
void ghetro1() {
	//ghetruoc
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 0.3, -1.8)) * scale(vec3(0.5f, 0.1f, 0.5f));
	mat4 model_ghetruoc = ghe_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghetruoc.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//tua
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 0.4, -1.8)) * scale(vec3(0.3f, 0.1f, 0.3f));
	mat4 model_tua = ghe_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tua.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}


void nentro2() {
	//nentro1
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0.06, 0)) * scale(vec3(1.0f, 0.05f, 1.0f));
	mat4 model_nentro1 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_nentro1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//trục tro chơi
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 1.26, 0)) * scale(vec3(0.2f, 2.5f, 0.2f));
	mat4 model_tructro1 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tructro1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void thanhquaytro2() {
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0.5, 0)) * scale(vec3(1.5f, 0.05f, 0.05f));
	mat4 model_tructro1 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tructro1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0.5, 0)) * scale(vec3(0.05f, 0.05f, 1.5f));
	mat4 model_tro2 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_tro2.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//ghe trai

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.75, 0.5, 0)) * scale(vec3(0.05f, 0.3f, 0.2f));
	mat4 model_ghe1 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.8, 0.35, 0)) * scale(vec3(0.2f, 0.05f, 0.2f));
	mat4 model_ghe11 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe11.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//ghephai
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-0.75, 0.5, 0)) * scale(vec3(0.05f, 0.3f, 0.2f));
	mat4 model_ghe2 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe2.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-0.8, 0.35, 0)) * scale(vec3(0.2f, 0.05f, 0.2f));
	mat4 model_ghe22 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe22.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//ghetruoc
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0.5, 0.75)) * scale(vec3(0.2f, 0.3f, 0.05f));
	mat4 model_ghe3 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe3.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.0, 0.35, 0.8)) * scale(vec3(0.2f, 0.05f, 0.2f));
	mat4 model_ghe33 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe33.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//ghesau
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.0, 0.5, -0.75)) * scale(vec3(0.2f, 0.3f, 0.05f));
	mat4 model_ghe4 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe4.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0.0, 0.35, -0.8)) * scale(vec3(0.2f, 0.05f, 0.2f));
	mat4 model_ghe44 = quaytr2_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe44.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void quaybanhang() {
	//nentro1
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 0.06, 1.5)) * scale(vec3(1.6f, 0.05f, 1.5f));
	mat4 model_nentro3 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_nentro3.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
	//trục tro chơi
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.7, 0.2, 2)) * scale(vec3(1.2f, 0.4f, 0.2f));
	mat4 model_ray1 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ray1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.7, 0.2, 1)) * scale(vec3(1.2f, 0.4f, 0.2f));
	mat4 model_ray2 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ray2.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(2.3, 0.5, 1.5)) * scale(vec3(0.05f, 1.0f, 1.0f));
	mat4 model_ray3 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ray3.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.1, 0.2, 1.5)) * scale(vec3(0.15f, 0.4f, 1.2f));
	mat4 model_ray4 = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ray4.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//MAI
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 1.0, 1.5)) * scale(vec3(1.6f, 0.05f, 1.5f));
	mat4 model_mai = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mai.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	

}

void co() {
	//cờ
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.6, 1.2, 1.5)) * scale(vec3(0.03f, 0.3f, 0.03f));
	mat4 model_co1 = vtco_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_co1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(1.45, 1.3, 1.5)) * scale(vec3(0.3f, 0.15f, 0.03f));
	mat4 model_laco1 = vtco_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_laco1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void cotden() {
	//cờ
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0, 0)) * scale(vec3(0.03f, 1.5f, 0.03f));
	mat4 model_co1 = vtden_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_co1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(0, 0.75, 0)) * scale(vec3(0.1f, 0.1f, 0.1f));
	mat4 model_laco1 = vtden_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_laco1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

void gheda() {
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.95, 0.4, 0)) * scale(vec3(0.05f, 0.3f, 0.5f));
	mat4 model_ghe1 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.85, 0.25, 0)) * scale(vec3(0.25f, 0.05f, 0.5f));
	mat4 model_ghe11 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_ghe11.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	//changhe
	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.95, 0.1, 0.23)) * scale(vec3(0.05f, 0.25f, 0.05f));
	mat4 model_changhe1 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_changhe1.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.75, 0.1, 0.23)) * scale(vec3(0.05f, 0.25f, 0.05f));
	mat4 model_changhe2 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_changhe2.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.95, 0.1, -0.23)) * scale(vec3(0.05f, 0.25f, 0.05f));
	mat4 model_changhe3 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_changhe3.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();

	mvstack.push(model_mat_cpp);
	instance = translate(vec3(-1.75, 0.1, -0.23)) * scale(vec3(0.05f, 0.25f, 0.05f));
	mat4 model_changhe4 = vtgheda_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_changhe4.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}
void taohinh() {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(trans_x, trans_y, trans_z)) * rotate_y(xoay_y) * translate(vec3(-0.35, 0, 0));
	nendat();

	model_mat_cpp = model_mat_cpp * rotate_z(xoay_z);
	hangrao();

	model_mat_cpp = model_mat_cpp ;
	nentro1();

	ghe_cpp = model_mat_cpp * translate(vec3(0, qtruc, 0));
	ghetro1();

	nentro2();

	quaytr2_cpp = model_mat_cpp * rotate_y(qtro2) * translate(vec3(0, tttro2, 0));
	thanhquaytro2();

	quaybanhang();

	vtgheda_cpp =  model_mat_cpp * translate(vec3(-0.1, 0, -2));
	gheda();

	vtgheda_cpp = model_mat_cpp * translate(vec3(-0.1, 0, 0));
	gheda();

	vtgheda_cpp = model_mat_cpp * translate(vec3(-0.1, 0, 2));
	gheda();

	vtgheda_cpp = model_mat_cpp * translate(vec3(0.2, 0, -0.5)) * rotate_y(-90);
	gheda();


	vtco_cpp = model_mat_cpp * translate(vec3(0, 0, 0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, 0.9));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, 0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, -0.9));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, -1.8));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, -2.7));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-4.1, -0.8, -3.6));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-3.8, -0.8, -4.0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-2.9, -0.8, -4.0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-2.0, -0.8, -4.0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-1.1, -0.8, -4.0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(-0.2, -0.8, -4.0));
	co();

	vtco_cpp = model_mat_cpp * translate(vec3(0.7, -0.8, -4.0));
	co();

	vtden_cpp = model_mat_cpp * translate(vec3(-2.4, 0.75, -2.4));
	cotden();

	vtden_cpp = model_mat_cpp * translate(vec3(2.4, 0.75, -2.4));
	cotden();

	vtden_cpp = model_mat_cpp * translate(vec3(2.4, 0.75, 2.4));
	cotden();
	model_mat_cpp = mvstack.pop();
}



// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);	// position
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset); //color
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset); //normal

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------


float	cam_speed = 0.05f,
cam_rot_speed = 1.0f,
cam_pos[] = { 0.0f, 0.0f, 3.0f },
cam_x = 0.0f,
cam_y = 0.0f,
cam_z = 0.0f;
void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	vec3	eye(0.0f, 2.0f, 2.0f),
		at(0.0f, 0.0f, 0.0f),
		up(0.0f, 1.0f, 0.0f);
	mat4 T = translate(vec3(-cam_pos[0], -cam_pos[1], -cam_pos[2]));

	//mat4 R = rotate_x(-cam_x);
	mat4 R = rotate_y(-cam_y);
	//mat4 R = rotate_z(-cam_z);

	view_mat_cpp = T * R * lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.001f,
		zfar = 10.0f,
		fov = 100.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);


	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	taohinh();
	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
bool kt1;
bool b1 =false;

bool kt2;
bool b2 = false;
void IdleFunc(void)
{
	/*Alpha += 0.05f;
	if (Alpha& gt; 360.0f) {
		Alpha -= 360.0f;
	}*/
	
	if (qtruc <= 2.2 && kt1 == false && b1 == true) {
		
		qtruc += 0.0003f;
		if (qtruc >= 2.2)
			kt1 = true;
	}
	if (kt1) {
		qtruc -= 0.0005f;
		if (qtruc <= 0)
		{
			kt1 = false;
		}
	}

	if (tttro2 <= 2 && kt2 == false && b2 == true) {

		tttro2 += 0.0003f;
		qtro2 += 1;
		if (tttro2 >= 2)
			kt2 = true;
	}
	if (kt2) {
		tttro2 -= 0.0005f;
		qtro2 -= 1;
		if (tttro2 <= 0)
		{
			kt2 = false;
		}
	}
	
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case '1':
		b1 = true;
		break;
	case '2':
		b1 = false;
		break;

	case '3':
		b2 = true;
		break;
	case '4':
		b2 = false;
		break;
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] += 0.05f;
		translated = true;
		break;
	case 'q':
		if (xoay_y <= 90)
			xoay_y += 5;
		break;
	case 'Q':
		if (xoay_y >= 0)
			xoay_y -= 5;
		break;
	case 'a':
		cam_pos[0] -= cam_speed;
		break;
	case 'A':
		cam_pos[0] -= cam_speed;
		break;

	case 'd':
		cam_pos[0] += cam_speed;
		break;
	case 'D':
		cam_pos[0] += cam_speed;
		break;

		// dịch theo trục z
	case 'w':
		cam_pos[2] -= cam_speed;
		break;
	case 'W':
		cam_pos[2] -= cam_speed;
		break;

	case 's':
		cam_pos[2] += cam_speed;
		break;
	case 'S':
		cam_pos[2] += cam_speed;
		break;
	}
}
// ----------------------------------------

	// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("khu vui choi");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutCloseFunc(CloseFunc);

	glutMainLoop();
	return 0;
}



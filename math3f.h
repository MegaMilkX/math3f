////////////////////////////////////////////
//Header only math lib
////////////////////////////////////////////

//
float qrsqrt(const float &n)
{
	long i;
	float x2, y;
	const float threehalves = 1.5f;

	x2 = n * 0.5f;
	y = n;
	i = *(long*)&y;
	i = 0x5f3759df - (i >> 1);
	y = *(float*)&i;

	y = y * (threehalves - (x2 * y * y));

	return y;
}

float qsqrt(const float &n)
{
	return n * qrsqrt(n);
}

///////////////////////////////////////////////
//Vectors
///////////////////////////////////////////////

//types
struct vec4f
{
	vec4f() : x(0), y(0), z(0), w(0) {}
	vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
	float length() const { return qsqrt(x*x + y*y + z*z + w*w); }
	union { float x, r; };
	union { float y, g; };
	union { float z, b; };
	union { float w, a; };
	float operator[](const int &i) const {
		return *((&x) + i);}
	float& operator[](const int &i){
		return *((&x) + i);}
};

struct vec3f
{
	vec3f() : x(0), y(0), z(0){}
	vec3f(float x, float y, float z) : x(x), y(y), z(z){}
	vec3f(const vec4f& v) : x(v.x), y(v.y), z(v.z){}
	float length() const {return qsqrt(x*x + y*y + z*z);}
	union { float x, r; };
	union { float y, g; };
	union { float z, b; };
	float operator[](const int &i) const {
		return *((&x) + i);}
	float& operator[](const int &i){
		return *((&x) + i);}
};

//Operators
//addition and substraction
vec3f operator+(const vec3f &a, const vec3f &b){
	return vec3f(a.x + b.x, a.y + b.y, a.z + b.z);}
vec4f operator+(const vec4f &a, const vec4f &b){
	return vec4f(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);}

vec3f operator+=(vec3f &a, const vec3f &b){
	return a = a + b;}
vec4f operator+=(vec4f &a, const vec4f &b){
	return a = a + b;}

vec3f operator-(const vec3f &a, const vec3f &b){
	return vec3f(a.x - b.x, a.y - b.y, a.z - b.z);}
vec4f operator-(const vec4f &a, const vec4f &b){
	return vec4f(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);}

vec3f operator-=(vec3f &a, const vec3f &b){
	return a = a - b;}
vec4f operator-=(vec4f &a, const vec4f &b){
	return a = a - b;}

vec3f operator-(const vec3f &a){
	return vec3f(-a.x, -a.y, -a.z);}
vec4f operator-(const vec4f &a){
	return vec4f(-a.x, -a.y, -a.z, -a.w);}

//multiplication and division
vec3f operator*(const vec3f &a, const float &f){
	return vec3f(a.x * f, a.y * f, a.z * f);}

vec3f operator*(const float &f, const vec3f &a){
	return vec3f(a.x * f, a.y * f, a.z * f);}

vec3f operator*=(vec3f &a, const float &f){
	return a = a*f;}

vec3f operator/(const vec3f &a, const float &f){
	return vec3f(a.x / f, a.y / f, a.z / f);}
vec4f operator/(const vec4f &a, const float &f){
	return vec4f(a.x / f, a.y / f, a.z / f, a.w / f);}

vec3f operator/=(vec3f &a, const float &f){
	return a / f;}

//
float dot(const vec3f &a, const vec3f &b){
	return a.x * b.x + a.y * b.y + a.z * b.z;}

vec3f cross(const vec3f &a, const vec3f &b){
	return vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);}

vec3f normalize(const vec3f &a){
	return a / a.length();}

vec4f normalize(const vec4f &a){
	return a / a.length();}


///////////////////////////////////////////////
//Matrices
//Column-major, for easier use with opengl
///////////////////////////////////////////////

struct mat3f
{
	mat3f(float xx, float xy, float xz,
		float yx, float yy, float yz,
		float zx, float zy, float zz)
	{
		v[0].x = xx; v[0].y = xy; v[0].z = xz;
		v[1].x = yx; v[1].y = yy; v[1].z = yz;
		v[2].x = zx; v[2].y = zy; v[2].z = zz;
	}
	vec3f operator[](const int &i) const {
		return v[i];}
	vec3f& operator[](const int &i){
		return v[i];}
private:
	vec3f v[3];
};

struct mat4f
{
	mat4f(){}
	vec4f operator[](const int &i) const {
		return v[i];}
	vec4f& operator[](const int &i){
		return v[i];}
private:
	vec4f v[4];
};

mat4f operator+(const mat4f &m0, const mat4f &m1){
	mat4f m;
	for (int i = 0; i < 4; i++)
		m[i] = m0[i] + m1[i];
	return m;}

mat3f operator*(const mat3f &m0, const mat3f &m1){
	mat3f m;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				m[i][j] += m0[k][j] * m1[i][k];
	return m;
}

mat4f operator*(const mat4f &m0, const mat4f &m1){
	mat4f m;
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			for (int k = 0; k < 4; k++)
				m[i][j] += m0[k][j] * m1[i][k];
	return m;}

//Rewrite these to be more cache-friendly
vec4f operator*(const mat4f &m, const vec4f &v)
{
	vec4f r;
	for (int i = 0; i < 4; i++)
		for (int k = 0; k < 4; k++)
			r[i] += m[k][i] * v[k];
	return r;
}

//Taking vec3 as vec4 and assuming v.w is zero
//so it transforms as a direction vector
vec3f operator*(const mat4f &m, const vec3f &v)
{
	vec3f r;
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++)
			r[i] += m[k][i] * v[k];
	return r;
}

vec3f operator*(const mat3f &m, const vec3f &v)
{
	vec3f r;
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++)
			r[i] += m[k][i] * v[k];
	return r;
}

//
mat3f transpose(const mat3f &m)
{
	//TODO
	return mat3f();
}

mat4f transpose(const mat4f &m)
{
	//TODO
	return mat4f();
}

///////////////////////////////////////////////
//Quaternion
///////////////////////////////////////////////

typedef vec4f quat;

quat operator*(const quat &q0, const quat &q1)
{
	return quat((q0.w * q1.x + q1.w * q0.x) + (q0.y * q1.z - q1.y * q0.z),
				(q0.w * q1.y + q1.w * q0.y) + (q1.x * q0.z - q0.x * q1.z), //Inverted, since y axis rotation is inverted
				(q0.w * q1.z + q1.w * q0.z) + (q0.x * q1.y - q1.x * q0.y),
				(q1.w * q0.w) - (q1.x * q0.x) - (q1.y * q0.y) - (q1.z * q0.z));
}

vec3f rotate(const quat &q, const vec3f &v)
{
	//TODO
}

quat angleAxis(const float &a, const vec3f &axis)
{
	float s = sin(a * 0.5f);
	return quat(axis.x * s, axis.y * s, axis.z * s, cos(a*0.5f));
}

///////////////////////////////////////////////
//Conversion
///////////////////////////////////////////////
mat3f toMat3(const quat &q)
{
	mat3f m = { 1 - 2 * q.y * q.y - 2 * q.z * q.z,			q.z * 2 * q.w + 2 * q.x * q.y,			-q.y * 2 * q.w + 2 * q.x * q.z,
				
				-q.z * 2 * q.w + 2 * q.x * q.y,				1 - 2 * q.x * q.x - 2 * q.z * q.z,		q.x * 2 * q.w + 2 * q.y * q.z,

				q.y * 2 * q.w + 2 * q.x * q.z,				-q.x * 2 * q.w + 2 * q.y * q.z,			1 - 2 * q.x * q.x - 2 * q.y * q.y };
	return m;
}
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
struct vec3f
{
	vec3f() : x(0), y(0), z(0){}
	vec3f(float x, float y, float z) : x(x), y(y), z(z){}
	float length() const {return qsqrt(x*x + y*y + z*z);}
	union { float x, r; };
	union { float y, g; };
	union { float z, b; };
	float operator[](const int &i) const {
		return *((&x) + i);}
	float& operator[](const int &i){
		return *((&x) + i);}
};

struct vec4f
{
	vec4f() : x(0), y(0), z(0), w(0) {}
	vec4f(float x, float y, float z, float w) : x(x), y(y), z(z), w(w){}
	union { float x, r; };
	union { float y, g; };
	union { float z, b; };
	union { float w, a; };
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

vec3f operator/=(vec3f &a, const float &f){
	return a / f;}

//
float dot(const vec3f &a, const vec3f &b){
	return a.x * b.x + a.y * b.y + a.z * b.z;}

vec3f cross(const vec3f &a, const vec3f &b){
	return vec3f(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);}

vec3f normalize(const vec3f &a){
	return a / a.length();}


///////////////////////////////////////////////
//Matrices
//Column-major, for easier use with opengl
///////////////////////////////////////////////

struct mat3f
{
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


///////////////////////////////////////////////
//Conversion
///////////////////////////////////////////////
mat3f toMat3(quat q)
{
	//TODO
}
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
	float operator[](const int &i){
		return *((&x) + i);}
};

struct vec4f
{
	//TODO
	float x, y, z, w;
};


//Operators
//addition and substraction
vec3f operator+(const vec3f &a, const vec3f &b){
	return vec3f(a.x + b.x, a.y + b.y, a.z + b.z);}

vec3f operator+=(vec3f &a, const vec3f &b){
	return a + b;}

vec3f operator-(const vec3f &a, const vec3f &b){
	return vec3f(a.x - b.x, a.y - b.y, a.z - b.z);}

vec3f operator-=(vec3f &a, const vec3f &b){
	return a - b;}

vec3f operator-(const vec3f &a){
	return vec3f(-a.x, -a.y, -a.z);}

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
///////////////////////////////////////////////

struct mat3f
{
	vec3f operator[](const int &i){
		return v[i];}
private:
	vec3f v[3];
};

struct mat4f
{

private:
	vec4f v[4];
};


///////////////////////////////////////////////
//Quaternion
///////////////////////////////////////////////

struct quat
{
	float x, y, z, w;
};
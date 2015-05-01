////////////////////////////////////////////
//Header only math lib
////////////////////////////////////////////

//Thanks, Carmack!
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

float sqrt(const float &n)
{
	return n * qrsqrt(n);
}

//Types
struct vec3f
{
	vec3f(float x, float y, float z) : x(x), y(y), z(z){}
	float length(){return sqrt(x*x + y*y + z*z);}
	float x, y, z;
};


///////////////////////////////////////////////
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

///////////////////////////////////////////////
//
float dot(vec3f a, vec3f b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

vec3f cross(vec3f a, vec3f b)
{
	return vec3f(0, 0, 0);
}

//
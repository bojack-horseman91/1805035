#include "points3D.h"

points3D::points3D(double x, double y, double z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

points3D::points3D() {
  this->x = 0;
  this->y = 0;
  this->z = 0;
}

void points3D::print(int yx) {
  std::cout << yx << " :" << this->x << " " << this->y << " " << this->z << std::endl;
}

points3D points3D::operator+(const points3D &p) {
  points3D temp;
  temp.x = this->x + p.x;
  temp.y = this->y + p.y;
  temp.z = this->z + p.z;
  return temp;
}

points3D points3D::operator-(const points3D &p) {
  points3D temp;
  temp.x = this->x - p.x;
  temp.y = this->y - p.y;
  temp.z = this->z - p.z;
  return temp;
}

points3D points3D::operator*(const double &p) {
  points3D temp;
  temp.x = this->x * p;
  temp.y = this->y * p;
  temp.z = this->z * p;
  return temp;
}
//translate
points3D points3D::translate(const points3D &other) const {
  points3D result;
  result.x = x + other.x;
  result.y = y + other.y;
  result.z = z + other.z;
  return result;
}
//dot product
double points3D::dot(const points3D &other) const {
  return x * other.x + y * other.y + z * other.z;
}

points3D points3D::operator/(const double &p) {
  points3D temp;
  temp.x = this->x / p;
  temp.y = this->y / p;
  temp.z = this->z / p;
  return temp;
}
points3D points3D::operator+=(const points3D& p) {
  this->x += p.x;
  this->y += p.y;
  this->z += p.z;
  points3D temp(this->x, this->y, this->z);
  return temp;
}
//negation of a vector
points3D points3D::operator-() const {
  points3D temp;
  temp.x = -x;
  temp.y = -y;
  temp.z = -z;
  return temp;
}

points3D points3D::cross(const points3D &other) const {
  points3D result;
  result.x = y * other.z - z * other.y;
  result.y = z * other.x - x * other.z;
  result.z = x * other.y - y * other.x;
  return result;
}

float points3D::length() const {
  return sqrt(x * x + y * y + z * z);
}

points3D points3D::normalize() const {
  float len = length();
  points3D result;
  result.x = x / len;
  result.y = y / len;
  result.z = z / len;
  return result;
}

points3D points3D::scaled(float scaleFactor) const {
  points3D result;
  result.x = x * scaleFactor;
  result.y = y * scaleFactor;
  result.z = z * scaleFactor;
  return result;
}

points3D points3D::operator=(const points3D &p) {
  points3D temp;
  temp.x = p.x;
  temp.y = p.y;
  temp.z = p.z;
  this->x = temp.x;
  this->y = temp.y;
  this->z = temp.z;
  return temp;
}

//input stream
std::istream &operator>>(std::istream &in, points3D &p) {
  in >> p.x >> p.y >> p.z;
  return in;
}
//output stream
std::ostream &operator<<(std::ostream &out, points3D &p) {
  out << p.x << " " << p.y << " " << p.z;
  return out;
}
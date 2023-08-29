#ifndef POINTS3D_H
#define POINTS3D_H

#include <cmath>
#include <iostream>

class points3D {
public:
  double x, y, z;

  points3D(double x, double y, double z);
  points3D();

  void print(int yx);
  points3D operator+(const points3D &p);
  points3D operator-(const points3D &p);
  points3D operator*(const double &p);
  points3D operator/(const double &p);
  points3D cross(const points3D &other) const;
  float length() const;
  points3D normalize() const;
  points3D scaled(float scaleFactor) const;
  points3D operator=(const points3D &p);
  points3D operator+=(const points3D &p);
  //negation of a vector
  points3D operator-() const;
  double dot(const points3D &other) const;
  points3D translate(const points3D &other) const;
  //input stream
  friend std::istream &operator>>(std::istream &in, points3D &p);
  //output stream
  friend std::ostream &operator<<(std::ostream &out, points3D &p);
};

#endif  // POINTS3D_H

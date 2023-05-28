#ifndef GEOMETRICCURVESLIBRARY_H
#define GEOMETRICCURVESLIBRARY_H

#include <string>
#include <memory>

using namespace std;

namespace GCurLib
{

class Error
{
public:
    Error(const string & mess, double val = 0.0);
    Error(string && mess, double val = 0.0);
    string m_mess;
};

class vector3
{
public:
    double x;
    double y;
    double z;
    vector3(double x_, double y_, double z_)
    {
        x = x_;
        y = y_;
        z = z_;
    }
    vector3()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
};

vector3 && operator+(const vector3 & lhs, const vector3 & rhs);
vector3 && operator-(const vector3 & lhs, const vector3 & rhs);

class Curve3
{
public:
    Curve3();
    Curve3(double x_, double y_, double z_);
    explicit Curve3(const vector3 & position);
    explicit Curve3(vector3 && position);
    virtual vector3 pointAt(double t) const { return m_position; };
    virtual vector3 derivative1At(double t) const { return vector3(); };
    virtual ~Curve3() {};
protected:
    vector3 m_position;
};

class Circle: public Curve3
{
public:
    Circle(const double radius, const vector3 & pos = vector3());
    double radius() { return m_radius; }
    virtual vector3 pointAt(double t) const override;
    virtual vector3 derivative1At(double t) const override;
protected:
    double m_radius;
};

class Ellipse: public Curve3
{
public:
    Ellipse(const double radiusA, const double radiusB, const vector3 & pos = vector3());
    virtual vector3 pointAt(double t) const override;
    virtual vector3 derivative1At(double t) const override;
private:
    double m_radiusA;
    double m_radiusB;
};

class Helix: public Circle
{
public:
    Helix(const double radius, const double step, const vector3 & pos = vector3());
    virtual vector3 pointAt(double t) const override;
    virtual vector3 derivative1At(double t) const override;
private:
    double m_step;
};

bool isLess(shared_ptr<Curve3> l, shared_ptr<Curve3> r);

} //namespace GCurLib

#endif // GEOMETRICCURVESLIBRARY_H

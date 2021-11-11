#include "core.h"
#include "Sphere.h"

cs::Sphere::Sphere(const Vec3& origin, float radius)
    :
    m_origin(origin),
    m_radius(radius)
{
}

cs::Sphere::Sphere(const Sphere& lVal)
    :
    m_origin(lVal.m_origin),
    m_radius(lVal.m_radius)
{
}

cs::Sphere& cs::Sphere::operator=(const Sphere& lVal)
{
    m_origin = lVal.m_origin;
    m_radius = lVal.m_radius;

    return *this;
}

bool cs::Sphere::operator==(const Sphere& lVal) const
{
    return m_origin == lVal.m_origin && m_radius == lVal.m_radius;
}

bool cs::Sphere::operator!=(const Sphere& lVal) const
{
    return m_origin != lVal.m_origin || m_radius != lVal.m_radius;
}

const cs::Vec3& cs::Sphere::GetOrigin() const
{
    return m_origin;
}

float cs::Sphere::GetRadius() const
{
    return m_radius;
}

void cs::Sphere::SetOrigin(const Vec3& origin)
{
    m_origin = origin;
}

void cs::Sphere::SetRadius(float radius)
{
    m_radius = radius;
}

bool cs::Sphere::Contains(const Vec3& point) const
{
    return (point - m_origin).Length3Sq() < (m_radius * m_radius);
}

bool cs::Sphere::Intersection(const Line3& line, float& t, bool first, bool cullBack) const
{
    Vec3 relative = m_origin - line.GetOrigin();

    float tClosest = relative.Dot3(line.GetDirection());

    float lSq = relative.Length3Sq();
    float rSq = m_radius * m_radius;
    float mSq = lSq - tClosest * tClosest; // Closest distance squared

    if ((tClosest < 0 && lSq > rSq) || mSq > rSq)
    {
        return false;
    }

    float q = std::sqrtf(rSq - mSq);

    if (first && (!cullBack || lSq > rSq))
    {
        t = tClosest - q;
    }
    else
    {
        t = tClosest + q;
    }
    
    return true;
}

bool cs::Sphere::Intersection(const Line3& line, Vec3& out, bool first, bool cullBack) const
{
    float t;

    if (!Intersection(line, t, first, cullBack))
    {
        return false;
    }

    out = line(t);
    
    return true;
}

bool cs::Sphere::Raycast(const Line3& line, float& out) const
{
    float t;

    if (Intersection(line, t, true, true))
    {
        out = t;
        return true;
    }

    return false;
}

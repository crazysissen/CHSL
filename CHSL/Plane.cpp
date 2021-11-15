#include "core.h"
#include "Plane.h"

#include <fstream>

cs::Plane::Plane(Vec3 origin, Vec3 normal)
    :
    m_origin(origin),
    m_normal(normal),
    m_d(0.0f)
{
    UpdateD();

    if (normal.x == 0 && normal.y == 0 && normal.z == 0)
    {
        throw ExceptionGeneral(__FILE__, __FUNCTION__, __LINE__, "Invalid Plane intialization with normal == { 0, 0, 0 }.");
    }
}

cs::Plane::Plane(Vec3 origin, Vec3 v1, Vec3 v2)
    :
    Plane(origin, v1.Cross(v2))
{
}

cs::Plane::Plane(const Plane& lVal)
    :
    m_origin(lVal.m_origin),
    m_normal(lVal.m_normal),
    m_d(lVal.m_d)
{
}

cs::Plane& cs::Plane::operator=(const Plane& lVal)
{
    m_origin = lVal.m_origin;
    m_normal = lVal.m_normal;
    m_d = lVal.m_d;

    return *this;
}

bool cs::Plane::operator==(const Plane& lVal) const
{
    return m_origin == lVal.m_origin && m_normal == lVal.m_normal;
}

bool cs::Plane::operator!=(const Plane& lVal) const
{
    return m_origin != lVal.m_origin || m_normal != lVal.m_normal;
}

const cs::Vec3& cs::Plane::GetOrigin() const
{
    return m_origin;
}

const cs::Vec3& cs::Plane::GetNormal() const
{
    return m_normal;
}

void cs::Plane::SetOrigin(const Vec3& origin)
{
    m_origin = origin;

    UpdateD();
}

void cs::Plane::SetNormal(const Vec3& normal)
{
    m_normal = normal;

    UpdateD();
}

bool cs::Plane::Equivalent(const Plane& plane) const
{
    return Contains(plane.m_origin) && m_origin.Parallel3(plane.m_normal);
}

bool cs::Plane::Contains(const Vec3& vector) const
{
    return m_normal.Dot3(vector) - m_d == 0;
}

bool cs::Plane::Contains(const Line3& line) const
{
    return Contains(line.GetOrigin()) && m_normal.Dot3(line.GetDirection()) == 0;
}

bool cs::Plane::Parallel(const Plane& plane) const
{
    return m_normal.Parallel3(plane.m_normal);
}

bool cs::Plane::Parallel(const Line3& line) const
{
    return m_normal.Dot3(line.GetDirection()) == 0;
}

bool cs::Plane::Perpendicular(const Line3& line) const
{
    return m_normal.Parallel3(line.GetDirection());
}

bool cs::Plane::Intersection(const Line3& line, float& t) const
{
    if (Parallel(line))
    {
        return false;
    }

    t = (-m_d - m_normal.Dot3(line.GetOrigin())) / (m_normal.Dot3(line.GetDirection()));

    return true;
}

bool cs::Plane::Intersection(const Line3& line, Vec3& out) const
{
    float t;

    if (!Intersection(line, t))
    {
        return false;
    }

    out = line(t);

    return true;
}

bool cs::Plane::Intersection(const Plane& plane, Line3& out) const
{
    if (Parallel(plane))
    {
        return false;
    }

    Vec3 origin;
    Vec3 direction;

    direction = m_normal.Cross(plane.m_normal);

    if (m_normal.Parallel3(Vec3(0, 0, 1)))
    {
        float inv = 1.0f / m_normal.z;

        if (plane.m_normal.Parallel3(Vec3(0, 1, 0)))
        {
            // The line intersects the yz plane
            origin.x = 0; 
            origin.y = (m_d * plane.m_normal.z * inv - plane.m_d) / (plane.m_normal.y - m_normal.y * plane.m_normal.z * inv);
            origin.z = (-m_d - m_normal.y * origin.y) * inv;
        }

        // The line intersects the xz plane
        origin.y = 0;
        origin.x = (m_d * plane.m_normal.z * inv - plane.m_d) / (plane.m_normal.x - m_normal.x * plane.m_normal.z * inv);
        origin.z = (-m_d - m_normal.x * origin.x) * inv;
    }
    else
    {
        float inv = 1.0f / m_normal.x;

        // The line intersects the xy plane
        origin.z = 0;
        origin.y = (m_d * plane.m_normal.x * inv - plane.m_d) / (plane.m_normal.y - m_normal.y * plane.m_normal.x * inv);
        origin.x = (-m_d - m_normal.y * origin.y) * inv;
    }

    out = Line3(origin, direction);

    return true;
}

bool cs::Plane::Raycast(const Line3& line, HitInfo& out) const
{
    float t;

    if (Intersection(line, t) && t > 0 && line.GetDirection().Dot3(m_normal) < 0)
    {
        out.t = t;
        out.normal = m_normal;
        return true;
    }

    return false;
}

void cs::Plane::UpdateD()
{
    m_d = -m_origin.Dot3(m_normal);
}

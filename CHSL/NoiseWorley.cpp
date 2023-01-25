
#include "core.h"

#include "NoiseWorley.h"

cs::NoiseWorley::NoiseWorley(unsigned int seed, unsigned int xSize)
	:
	savedPositionsCount(GRID_CLUSTER_RADIUS),
	cellCount(xSize),
	savedPositions(new Vec3[savedPositionsCount]),
	cellLocalPositions(new Vec3[cellCount]),
	currentCenter({ -10, -10, -10 }),
	d(DimensionFirst),
	s(seed),
	xs(xSize), ys(1), zs(1)
{
	cs::Random r(seed);

	for (uint x = 0; x < xSize; ++x)
	{
		cellLocalPositions[x] = { x + r.Getf(), 0, 0 };
	}
}

cs::NoiseWorley::NoiseWorley(unsigned int seed, unsigned int xSize, unsigned int ySize)
	:
	savedPositionsCount(GRID_CLUSTER_RADIUS * GRID_CLUSTER_RADIUS),
	cellCount(xSize * ySize),
	savedPositions(new Vec3[savedPositionsCount]),
	cellLocalPositions(new Vec3[cellCount]),
	currentCenter({ -10, -10, -10 }),
	d(DimensionSecond),
	s(seed),
	xs(xSize), ys(ySize), zs(1)
{
	cs::Random r(seed);

	for (uint y = 0; y < ySize; ++y)
	{
		for (uint x = 0; x < xSize; ++x)
		{
			cellLocalPositions[x + y * xSize] = { x + r.Getf(), y + r.Getf(), 0 };
		}
	}
}

cs::NoiseWorley::NoiseWorley(unsigned int seed, unsigned int xSize, unsigned int ySize, unsigned int zSize)
	:
	savedPositionsCount(GRID_CLUSTER_RADIUS * GRID_CLUSTER_RADIUS * GRID_CLUSTER_RADIUS),
	cellCount(xSize * ySize * zSize),
	savedPositions(new Vec3[savedPositionsCount]),
	cellLocalPositions(new Vec3[cellCount]),
	currentCenter({ -10, -10, -10 }),
	d(DimensionThird),
	s(seed),
	xs(xSize), ys(ySize), zs(zSize)
{
	cs::Random r(seed);

	for (uint z = 0; z < zSize; ++z)
	{
		for (uint y = 0; y < ySize; ++y)
		{
			for (uint x = 0; x < xSize; ++x)
			{
				cellLocalPositions[x + y * xSize + z * xSize * ySize] = { x + r.Getf(), y + r.Getf(), z + r.Getf() };
			}
		}
	}
}

cs::NoiseWorley::~NoiseWorley()
{
	delete[](savedPositions);
	delete[](cellLocalPositions);
}

float cs::NoiseWorley::Gen1D(float x)
{
	Point3 coord((int)x, 0, 0);
	int r = (int)GRID_CLUSTER_RADIUS, i(0);

	if (coord != currentCenter)
	{
		for (int localX = -r; localX < r + 1; ++localX)
		{
			Point3 localCoord = Point3(coord.x + localX, 0, 0) - currentCenter;

			savedPositions[i] = cellLocalPositions[cs::iwrap(localCoord.x, 0, xs - 1)] + (Vec3)localCoord;

			++i;
		}

		currentCenter = coord;
	}

	return GetClosestCurrentDistance(savedPositionsCount, x, 0, 0);
}

float cs::NoiseWorley::Gen2D(float x, float y)
{
	if (d != DimensionSecond)
	{
		return Gen1D(x);
	}

	Point3 coord((int)x, (int)y, 0);
	int r = GRID_CLUSTER_RADIUS, i(0);

	if (coord != currentCenter)
	{
		currentCenter = coord;

		for (int localY = -r; localY < r + 1; ++localY)
		{
			for (int localX = -r; localX < r + 1; ++localX)
			{
				Point3 localCoord = Point3(coord.x + localX, coord.y + localY, 0) - currentCenter;

				savedPositions[i] = cellLocalPositions[
					cs::iwrap(localCoord.x, 0, xs - 1) +
					cs::iwrap(localCoord.y, 0, ys - 1) * xs] + 
					(Vec3)localCoord;

				++i;
			}
		}
	}

	return GetClosestCurrentDistance(savedPositionsCount, x, y, 0);
}

float cs::NoiseWorley::Gen3D(float x, float y, float z)
{
	if (d != DimensionThird)
	{
		return Gen2D(x, y);
	}

	Point3 coord(
		(x < 0 || x >= xs) ? cs::iwrap((int)x, 0, xs - 1) : (int)x,
		(y < 0 || y >= ys) ? cs::iwrap((int)y, 0, ys - 1) : (int)y,
		(z < 0 || z >= zs) ? cs::iwrap((int)z, 0, zs - 1) : (int)z);

	int r = GRID_CLUSTER_RADIUS / 2, i(0);

	if (coord != currentCenter)
	{
		currentCenter = coord;

		int x = coord.x, y = coord.y, z = coord.z;

		for (int localZ = -r; localZ < r + 1; ++localZ)
		{
			for (int localY = -r; localY < r + 1; ++localY)
			{
				for (int localX = -r; localX < r + 1; ++localX)
				{
					int lx = x + localX, ly = y + localY, lz = z + localZ;

					savedPositions[i] = cellLocalPositions[
						(lx < 0 || lx >= (int)xs ?
							cs::iwrap(lx, 0, xs - 1) : lx) +
						(ly < 0 || ly >= (int)ys ?
							cs::iwrap(ly, 0, ys - 1) : ly) * xs +
						(lz < 0 || lz >= (int)zs ?
							cs::iwrap(lz, 0, zs - 1) : lz) * xs * ys]/* +
						(Vec3)localCoord*/;

					++i;
				}
			}
		}
	}

	return GetClosestCurrentDistance(savedPositionsCount, x, y, z);
}

float cs::NoiseWorley::GetClosestCurrentDistance(int count, float x, float y, float z)
{
	float closestDistance = 100;

	for (int j = 0; j < count; ++j)
	{
		Vec3 diff(x - savedPositions[j].x, y - savedPositions[j].y, z - savedPositions[j].z);
		float currentDistance = diff.LengthSq();
		if (currentDistance < closestDistance)
		{
			closestDistance = currentDistance;
		}
	}

	return 1 / (/*std::sqrtf*/(closestDistance * 2) + 1);
}

//Vec3 cs::NoiseWorley::GetPoint(Point3 coord)
//{
//	Origin
//
//	if (d == dimension::First)
//	{
//		return 
//	}
//
//	if (d == dimension::Second)
//	{
//
//		return;
//	}
//}


// Struct

//cs::NoiseWorley::GridStruct::GridStruct()
//	:
//	origin({ -100, -100, -100 }),
//	currentCells(nullptr)
//{
//}
//
//cs::NoiseWorley::GridStruct::GridStruct(uint& size, Point3& o, dimension::D& d, uint& seed)
//	:
//	origin(o),
//	currentCells(new Vec3[size])
//{
//	Gen(size, o, d, seed);
//}
//
//cs::NoiseWorley::GridStruct::~GridStruct()
//{
//	delete[](currentCells);
//}

//void cs::NoiseWorley::GridStruct::Gen(uint& size, Point3& o, dimension::D& d, uint& seed)
//{
//	static float* transposedSeed = new float();
//
//	*transposedSeed = (o.x * 0.1) + (o.y * 0.001f) + (o.z * 0.00001f);
//
//	//Random r1(*(reinterpret_cast<uint*>(transposedSeed)) ^ seed), r(r1.GetUnsigned());
//	srand(*transposedSeed);
//
//	if (currentlyUpdating)
//	{
//		currentlyUpdating = false;
//	}
//
//	auto getR = []()
//	{
//		static const double f = 1.0f / ((double)RAND_MAX);
//		return (float)(f * rand());
//	};
//
//	switch (d)
//	{
//	case cs::dimension::First:
//		for (uint i = 0; i < size; ++i)
//		{
//			currentCells[i] = Vec3(/*r.Getf()*/getR(), 0, 0);
//		}
//		break;
//
//	case cs::dimension::Second:
//		for (uint i = 0; i < size; ++i)
//		{
//			currentCells[i] = Vec3(/*r.Getf()*/getR(), /*r.Getf()*/getR(), 0);
//		}
//		break;
//
//	case cs::dimension::Third:
//		for (uint i = 0; i < size; ++i)
//		{
//			currentCells[i] = Vec3(/*r.Getf()*/getR(), /*r.Getf()*/getR(), /*r.Getf()*/getR());
//		}
//		break;
//	}
//}

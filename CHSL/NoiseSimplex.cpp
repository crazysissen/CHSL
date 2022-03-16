#include "core.h"

#include <ctime>

#include "NoiseSimplex.h"
#include "Random.h"



int mod(int x, int m)
{
	int a = x % m;
	return a < 0 ? a + m : a;
}



cs::NoiseSimplex::NoiseSimplex()
	:
	permutations(new byte[PERM_COUNT])
{
	PerlinGenMatrix();
}

cs::NoiseSimplex::NoiseSimplex(uint seed)
	:
	permutations(new byte[PERM_COUNT])
{
	PerlinGenMatrix(seed);
}

cs::NoiseSimplex::NoiseSimplex(byte* permMatrix, bool copy) // Use memory address of given matrix
	:
	permutations(copy ? new byte[PERM_COUNT] : permMatrix)
{
	if (copy)
	{
		PerlinGenMatrix(permMatrix, true);
	}
}

cs::NoiseSimplex::~NoiseSimplex()
{
	delete[] permutations;
}

void cs::NoiseSimplex::PerlinGenMatrix()
{
	cs::Random r;
	r.FillBytes(permutations, PERM_COUNT);
}

void cs::NoiseSimplex::PerlinGenMatrix(uint seed)
{
	cs::Random r(seed);
	r.FillBytes(permutations, PERM_COUNT);
}

void cs::NoiseSimplex::PerlinGenMatrix(byte* permMatrix, bool copy) // Replaces or copies matrix memory address with given matrix
{
	if (copy)
	{
		memcpy(permutations, permMatrix, PERM_COUNT);
		return;
	}

	delete[] permutations;
	permutations = permMatrix;
}

float cs::NoiseSimplex::Gen1D(float x)
{
	int index = cs::floor(x); // REPLACED FLOOR WITH CAST
	float localX = x - index;

	// Factor 0.395 scales the range to precisely - 1-> 1
	return 0.395f * (
		std::powf(1.0f - localX * localX, 4) * Gradient(permutations[index & 0xff], localX) +
		std::powf(1 - (localX * localX - 2 * localX + 1), 4) * Gradient(permutations[(index + 1) & 0xff], localX - 1));
}

float cs::NoiseSimplex::Gen2D(float x, float y)
{
	const float F2 = 0.366025403f; // F2 = 0.5*(sqrt(3.0)-1.0)
	const float G2 = 0.211324865f; // G2 = (3.0-Math.sqrt(3.0))/6.0

	float n0, n1, n2; // Noise contributions from the three corners

	// Skew the input space to determine which simplex cell we're in
	float s = (x + y) * F2; // Hairy factor for 2D
	int i = cs::floor(x + s);
	int j = cs::floor(y + s);

	float t = (i + j) * G2;
	float x0 = x - (i - t); // The x,y distances from the cell origin
	float y0 = y - (j - t);

	// For the 2D case, the simplex shape is an equilateral triangle.
	// Determine which simplex we are in.
	int i1, j1; // Offsets for second (middle) corner of simplex in (i,j) coords
	if (x0 > y0) 
	{ i1 = 1; j1 = 0; } // lower triangle, XY order: (0,0)->(1,0)->(1,1)
	else 
	{ i1 = 0; j1 = 1; } // upper triangle, YX order: (0,0)->(0,1)->(1,1)

	// A step of (1,0) in (i,j) means a step of (1-c,-c) in (x,y), and
	// a step of (0,1) in (i,j) means a step of (-c,1-c) in (x,y), where
	// c = (3-sqrt(3))/6

	float x1 = x0 - i1 + G2; // Offsets for middle corner in (x,y) unskewed coords
	float y1 = y0 - j1 + G2;
	float x2 = x0 - 1.0f + 2.0f * G2; // Offsets for last corner in (x,y) unskewed coords
	float y2 = y0 - 1.0f + 2.0f * G2;

	// Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
	int ii = imod(i, 256);
	int jj = imod(j, 256);

	// Calculate the contribution from the three corners
	float t0 = 0.5f - x0 * x0 - y0 * y0;
	if (t0 < 0.0f) n0 = 0.0f;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * Gradient(permutations[ii + permutations[jj]], x0, y0);
	}

	float t1 = 0.5f - x1 * x1 - y1 * y1;
	if (t1 < 0.0f) n1 = 0.0f;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * Gradient(permutations[ii + i1 + permutations[jj + j1]], x1, y1);
	}

	float t2 = 0.5f - x2 * x2 - y2 * y2;
	if (t2 < 0.0f) n2 = 0.0f;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * Gradient(permutations[ii + 1 + permutations[jj + 1]], x2, y2);
	}

	// Result RESCALED to the range [0 -> 1]
	return 20.0f * (n0 + n1 + n2) + 0.5f;
}

float cs::NoiseSimplex::Gen3D(float x, float y, float z)
{
	// Simple skewing factors for the 3D case
	const float F3 = 0.333333333f;
	const float G3 = 0.166666667f;

	float n0, n1, n2, n3; // Noise contributions from the four corners

	// Skew the input space to determine which simplex cell we're in
	float s = (x + y + z) * F3; // Very nice and simple skew factor for 3D
	float xs = x + s;
	float ys = y + s;
	float zs = z + s;
	int i = cs::floor(xs);
	int j = cs::floor(ys);
	int k = cs::floor(zs);

	float t = (i + j + k) * G3;
	float X0 = i - t; // Unskew the cell origin back to (x,y,z) space
	float Y0 = j - t;
	float Z0 = k - t;
	float x0 = x - X0; // The x,y,z distances from the cell origin
	float y0 = y - Y0;
	float z0 = z - Z0;

	// For the 3D case, the simplex shape is a slightly irregular tetrahedron.
	// Determine which simplex we are in.
	int i1, j1, k1; // Offsets for second corner of simplex in (i,j,k) coords
	int i2, j2, k2; // Offsets for third corner of simplex in (i,j,k) coords

	/* This code would benefit from a backport from the GLSL version! */
	if (x0 >= y0)
	{
		if (y0 >= z0)
		{
			i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 1; k2 = 0;
		} // X Y Z order
		else if (x0 >= z0) { i1 = 1; j1 = 0; k1 = 0; i2 = 1; j2 = 0; k2 = 1; } // X Z Y order
		else { i1 = 0; j1 = 0; k1 = 1; i2 = 1; j2 = 0; k2 = 1; } // Z X Y order
	}
	else
	{ // x0<y0
		if (y0 < z0) { i1 = 0; j1 = 0; k1 = 1; i2 = 0; j2 = 1; k2 = 1; } // Z Y X order
		else if (x0 < z0) { i1 = 0; j1 = 1; k1 = 0; i2 = 0; j2 = 1; k2 = 1; } // Y Z X order
		else { i1 = 0; j1 = 1; k1 = 0; i2 = 1; j2 = 1; k2 = 0; } // Y X Z order
	}

	// A step of (1,0,0) in (i,j,k) means a step of (1-c,-c,-c) in (x,y,z),
	// a step of (0,1,0) in (i,j,k) means a step of (-c,1-c,-c) in (x,y,z), and
	// a step of (0,0,1) in (i,j,k) means a step of (-c,-c,1-c) in (x,y,z), where
	// c = 1/6.

	float x1 = x0 - i1 + G3; // Offsets for second corner in (x,y,z) coords
	float y1 = y0 - j1 + G3;
	float z1 = z0 - k1 + G3;
	float x2 = x0 - i2 + 2.0f * G3; // Offsets for third corner in (x,y,z) coords
	float y2 = y0 - j2 + 2.0f * G3;
	float z2 = z0 - k2 + 2.0f * G3;
	float x3 = x0 - 1.0f + 3.0f * G3; // Offsets for last corner in (x,y,z) coords
	float y3 = y0 - 1.0f + 3.0f * G3;
	float z3 = z0 - 1.0f + 3.0f * G3;

	// Wrap the integer indices at 256, to avoid indexing perm[] out of bounds
	int ii = imod(i, 256);
	int jj = imod(j, 256);
	int kk = imod(k, 256);

	// Calculate the contribution from the four corners
	float t0 = 0.6f - x0 * x0 - y0 * y0 - z0 * z0;
	if (t0 < 0.0f) n0 = 0.0f;
	else
	{
		t0 *= t0;
		n0 = t0 * t0 * Gradient(permutations[ii + permutations[jj + permutations[kk]]], x0, y0, z0);
	}

	float t1 = 0.6f - x1 * x1 - y1 * y1 - z1 * z1;
	if (t1 < 0.0f) n1 = 0.0f;
	else
	{
		t1 *= t1;
		n1 = t1 * t1 * Gradient(permutations[ii + i1 + permutations[jj + j1 + permutations[kk + k1]]], x1, y1, z1);
	}

	float t2 = 0.6f - x2 * x2 - y2 * y2 - z2 * z2;
	if (t2 < 0.0f) n2 = 0.0f;
	else
	{
		t2 *= t2;
		n2 = t2 * t2 * Gradient(permutations[ii + i2 + permutations[jj + j2 + permutations[kk + k2]]], x2, y2, z2);
	}

	float t3 = 0.6f - x3 * x3 - y3 * y3 - z3 * z3;
	if (t3 < 0.0f) n3 = 0.0f;
	else
	{
		t3 *= t3;
		n3 = t3 * t3 * Gradient(permutations[ii + 1 + permutations[jj + 1 + permutations[kk + 1]]], x3, y3, z3);
	}

	// CHANGED TO [0 -> 1]
	return 0.5f + 16.0f * (n0 + n1 + n2 + n3);
}

float cs::NoiseSimplex::Gradient(byte permHash, float x)
{
	int hash = permHash & 15;

	return 
		((1.0f + (hash & 7)) * x) 
		* ((hash & 8) != 0 ? -1.0f : 1.0f);
}

float cs::NoiseSimplex::Gradient(byte permHash, float x, float y)
{
	int hash = permHash & 7;

	return 
		(hash < 4 ? x : y) 
		* ((hash & 1) != 0 ? -1.0f : 1.0f) +

		(hash < 4 ? y : x) 
		* ((hash & 2) != 0 ? -2.0f : 2.0f);
}

float cs::NoiseSimplex::Gradient(byte permHash, float x, float y, float z)
{
	int hash = permHash & 15;     // Convert low 4 bits of hash code into 12 simple

	return 
		((hash & 1) != 0 ? -1 : 1) * 
		(hash < 8 ? x : y) + 
		
		((hash & 2) != 0 ? -1 : 1) * 
		(hash < 4 ? y : hash == 12 || hash == 14 ? x : z);
}

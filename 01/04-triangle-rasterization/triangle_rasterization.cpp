#include "triangle_rasterization.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::TriangleRasterization::TriangleRasterization(unsigned short width, unsigned short height, std::string obj_file) : cg::Projections(width, height, obj_file)
{
}

cg::TriangleRasterization::~TriangleRasterization()
{
}

void cg::TriangleRasterization::DrawTriangle(face face)
{
	float x_min = std::min(std::min(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_min = std::min(std::min(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);
	float x_max = std::max(std::max(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_max = std::max(std::max(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);

	for (float x = x_min; x <= x_max; x += 1.f) {
		for (float y = y_min; y <= y_max; y += 1.f) {
			float2 point{ x, y };

			float e0 = EdgeFunction(face.vertexes[1].xy(), face.vertexes[0].xy(), point);
			float e1 = EdgeFunction(face.vertexes[2].xy(), face.vertexes[1].xy(), point);
			float e2 = EdgeFunction(face.vertexes[0].xy(), face.vertexes[2].xy(), point);

			if (e0 >= 0.0f && e1 >= 0.0f && e2 >= 0.0f) {
				SetPixel(round(x), round(y), PixelShader(point));
			}
		}
	}

	DrawLine(face.vertexes[0].x, face.vertexes[0].y, face.vertexes[1].x, face.vertexes[1].y, color(255, 0, 0));
	DrawLine(face.vertexes[1].x, face.vertexes[1].y, face.vertexes[2].x, face.vertexes[2].y, color(0, 255, 0));
	DrawLine(face.vertexes[2].x, face.vertexes[2].y, face.vertexes[0].x, face.vertexes[0].y, color(0, 0, 255));
}

float cg::TriangleRasterization::EdgeFunction(float2 a, float2 b, float2 c)
{
	return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

cg::color cg::TriangleRasterization::PixelShader(float2 coordinates) {
	return color(0, 120, 200);
}

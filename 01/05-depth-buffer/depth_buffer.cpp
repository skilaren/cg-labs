#include "depth_buffer.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include <iostream>


cg::ZCulling::ZCulling(unsigned short width, unsigned short height, std::string obj_file) : TriangleRasterization(width, height, obj_file)
{
	depth_buffer.reserve(static_cast<size_t>(width * height));
}

cg::ZCulling::~ZCulling()
{
}

void cg::ZCulling::Clear()
{
	depth_buffer.clear();
	frame_buffer.resize(static_cast<size_t>(width * height));
	depth_buffer.resize(static_cast<size_t>(width * height), 1.f);
}

void cg::ZCulling::DrawTriangle(face face)
{
	float x_min = std::min(std::min(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_min = std::min(std::min(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);
	float x_max = std::max(std::max(face.vertexes[0].x, face.vertexes[1].x), face.vertexes[2].x);
	float y_max = std::max(std::max(face.vertexes[0].y, face.vertexes[1].y), face.vertexes[2].y);

	bool ccw = false;
	float direction = ccw ? -1.f : 1.f;
	float area = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), face.vertexes[2].xy());

	for (float x = x_min; x <= x_max; x += 1.f) {
		for (float y = y_min; y <= y_max; y += 1.f) {
			float2 point{ x, y };

			float e0 = direction * EdgeFunction(face.vertexes[0].xy(), face.vertexes[1].xy(), point);
			float e1 = direction * EdgeFunction(face.vertexes[1].xy(), face.vertexes[2].xy(), point);
			float e2 = direction * EdgeFunction(face.vertexes[2].xy(), face.vertexes[0].xy(), point);

			if (e0 >= 0.0f && e1 >= 0.0f && e2 >= 0.0f) {
				float3 bary{ e1 / area, e2 / area, e0 / area };
				float z = bary.x * face.vertexes[0].z + bary.y * face.vertexes[1].z + bary.z * face.vertexes[2].z;
				SetPixel(round(x), round(y), PixelShader(point, bary), z);
			}
		}
	}
	/*
	DrawLine(face.vertexes[0].x, face.vertexes[0].y, face.vertexes[1].x, face.vertexes[1].y, color(255, 0, 0));
	DrawLine(face.vertexes[1].x, face.vertexes[1].y, face.vertexes[2].x, face.vertexes[2].y, color(0, 255, 0));
	DrawLine(face.vertexes[2].x, face.vertexes[2].y, face.vertexes[0].x, face.vertexes[0].y, color(0, 0, 255));
	*/
}

void cg::ZCulling::SetPixel(unsigned short x, unsigned short y, color color, float z)
{
	if (depth_buffer[y * width + x] > z) {
		frame_buffer[y * width + x] = color;
		depth_buffer[y * width + x] = z;
	}
}



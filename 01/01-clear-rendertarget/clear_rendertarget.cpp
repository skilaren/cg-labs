#include "clear_rendertarget.h"

#define STBI_MSC_SECURE_CRT
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdexcept>


cg::ClearRenderTarget::ClearRenderTarget(unsigned short width, unsigned short height):
    width(width),
    height(height)
{
    frame_buffer.reserve(static_cast<size_t>(width * height));
}

cg::ClearRenderTarget::~ClearRenderTarget()
{
    frame_buffer.clear();
}

void cg::ClearRenderTarget::Clear()
{
    for (unsigned x = 0; x < width; x++) {
        for (unsigned y = 0; y < height; y++) {
            SetPixel(x, y, color());
        }
    }
}

void cg::ClearRenderTarget::Save(std::string filename) const
{
    int result = stbi_write_png(filename.c_str(), width, height, 3, frame_buffer.data(), width * sizeof(color));

    if (result != 1) {
        throw::std::runtime_error("Can not write png image.");
    }
}

void cg::ClearRenderTarget::SetPixel(unsigned short x, unsigned short y, color color)
{
    frame_buffer[y * width + x] = color;
}

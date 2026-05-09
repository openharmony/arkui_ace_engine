/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "image/image_filter.h"

#include <algorithm>
#include <numeric>
#include <cmath>
#include <random>

namespace Self::UI {

ColorRGB ColorHSL::ToRGB() const
{
    auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0.0f) {
            t += 1.0f;
        }
        if (t > 1.0f) {
            t -= 1.0f;
        }
        if (t < 1.0f / 6.0f) {
            return p + (q - p) * 6.0f * t;
        }
        if (t < 1.0f / 2.0f) {
            return q;
        }
        if (t < 2.0f / 3.0f) {
            return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
        }
        return p;
    };

    float hNorm = h / 360.0f;
    while (hNorm > 1.0f) {
        hNorm -= 1.0f;
    }
    while (hNorm < 0.0f) {
        hNorm += 1.0f;
    }
    if (s == 0.0f) {
        return ColorRGB(l, l, l);
    }

    float q = l < 0.5f ? l * (1.0f + s) : l + s - l * s;
    float p = 2.0f * l - q;
    
    return ColorRGB(
        hue2rgb(p, q, hNorm + 1.0f / 3.0f),
        hue2rgb(p, q, hNorm),
        hue2rgb(p, q, hNorm - 1.0f / 3.0f)
    );
}

ColorHSL ColorHSL::FromRGB(const ColorRGB& rgb)
{
    float maxVal = std::max({rgb.r, rgb.g, rgb.b});
    float minVal = std::min({rgb.r, rgb.g, rgb.b});
    float delta = maxVal - minVal;

    ColorHSL hsl;
    hsl.l = (maxVal + minVal) / 2.0f;

    if (delta == 0.0f) {
        hsl.h = 0.0f;
        hsl.s = 0.0f;
    } else {
        hsl.s = hsl.l > 0.5f ? delta / (2.0f - maxVal - minVal) : delta / (maxVal + minVal);
        
        if (maxVal == rgb.r) {
            hsl.h = 60.0f * fmod(((rgb.g - rgb.b) / delta), 6.0f);
        } else if (maxVal == rgb.g) {
            hsl.h = 60.0f * (((rgb.b - rgb.r) / delta) + 2.0f);
        } else {
            hsl.h = 60.0f * (((rgb.r - rgb.g) / delta) + 4.0f);
        }
    }

    if (hsl.h < 0.0f) {
        hsl.h += 360.0f;
    }
    return hsl;
}

ColorRGB ColorHSV::ToRGB() const
{
    float c = v * s;
    float hNorm = h / 60.0f;
    float x = c * (1.0f - std::abs(fmod(hNorm, 2.0f) - 1.0f));
    float m = v - c;

    ColorRGB rgb;
    int32_t sector = static_cast<int32_t>(hNorm) % 6;
    
    switch (sector) {
        case 0:
            rgb = ColorRGB(c, x, 0.0f);
            break;
        case 1:
            rgb = ColorRGB(x, c, 0.0f);
            break;
        case 2:
            rgb = ColorRGB(0.0f, c, x);
            break;
        case 3:
            rgb = ColorRGB(0.0f, x, c);
            break;
        case 4:
            rgb = ColorRGB(x, 0.0f, c);
            break;
        case 5:
            rgb = ColorRGB(c, 0.0f, x);
            break;
        default:
            rgb = ColorRGB(0.0f, 0.0f, 0.0f);
            break;
    }

    return ColorRGB(rgb.r + m, rgb.g + m, rgb.b + m);
}

ColorHSV ColorHSV::FromRGB(const ColorRGB& rgb)
{
    float maxVal = std::max({rgb.r, rgb.g, rgb.b});
    float minVal = std::min({rgb.r, rgb.g, rgb.b});
    float delta = maxVal - minVal;

    ColorHSV hsv;
    hsv.v = maxVal;

    if (delta == 0.0f) {
        hsv.h = 0.0f;
        hsv.s = 0.0f;
    } else {
        hsv.s = delta / maxVal;
        
        if (maxVal == rgb.r) {
            hsv.h = 60.0f * fmod(((rgb.g - rgb.b) / delta), 6.0f);
        } else if (maxVal == rgb.g) {
            hsv.h = 60.0f * (((rgb.b - rgb.r) / delta) + 2.0f);
        } else {
            hsv.h = 60.0f * (((rgb.r - rgb.g) / delta) + 4.0f);
        }
    }

    if (hsv.h < 0.0f) {
        hsv.h += 360.0f;
    }
    return hsv;
}

ColorRGB ColorCMYK::ToRGB() const
{
    float r = 1.0f - std::min(1.0f, c + k);
    float g = 1.0f - std::min(1.0f, m + k);
    float b = 1.0f - std::min(1.0f, y + k);
    return ColorRGB(r, g, b);
}

ColorCMYK ColorCMYK::FromRGB(const ColorRGB& rgb)
{
    float k = 1.0f - std::max({rgb.r, rgb.g, rgb.b});
    
    if (k == 1.0f) {
        return ColorCMYK(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    float c = (1.0f - rgb.r - k) / (1.0f - k);
    float m = (1.0f - rgb.g - k) / (1.0f - k);
    float y = (1.0f - rgb.b - k) / (1.0f - k);
    
    return ColorCMYK(c, m, y, k);
}

std::shared_ptr<ImageFilter> ImageFilter::Create(FilterType type, const FilterParams& params)
{
    return std::make_shared<ImageFilter>(type, params);
}

KernelMatrix ImageFilter::CreateBlurKernel(int32_t radius)
{
    int32_t size = radius * 2 + 1;
    std::vector<float> data(size * size, 1.0f);
    return KernelMatrix(size, size, data, static_cast<float>(size * size), 0.0f);
}

KernelMatrix ImageFilter::CreateGaussianKernel(int32_t radius, float sigma)
{
    int32_t size = radius * 2 + 1;
    std::vector<float> data(size * size);
    
    if (sigma <= 0.0f) {
        sigma = static_cast<float>(radius) / 2.0f;
    }
    
    float twoSigmaSquare = 2.0f * sigma * sigma;
    float sum = 0.0f;
    
    for (int32_t y = -radius; y <= radius; y++) {
        for (int32_t x = -radius; x <= radius; x++) {
            float distance = static_cast<float>(x * x + y * y);
            float value = exp(-distance / twoSigmaSquare);
            data[(y + radius) * size + (x + radius)] = value;
            sum += value;
        }
    }
    
    for (float& val : data) {
        val /= sum;
    }
    
    return KernelMatrix(size, size, data, 1.0f, 0.0f);
}

KernelMatrix ImageFilter::CreateSharpenKernel(float amount)
{
    std::vector<float> data = {
        0.0f, -1.0f * amount, 0.0f,
        -1.0f * amount, 4.0f * amount + 1.0f, -1.0f * amount,
        0.0f, -1.0f * amount, 0.0f
    };
    return KernelMatrix(3, 3, data, 1.0f, 0.0f);
}

KernelMatrix ImageFilter::CreateEdgeDetectKernel()
{
    std::vector<float> data = {
        -1.0f, -1.0f, -1.0f,
        -1.0f,  8.0f, -1.0f,
        -1.0f, -1.0f, -1.0f
    };
    return KernelMatrix(3, 3, data, 1.0f, 0.0f);
}

KernelMatrix ImageFilter::CreateEmbossKernel(float strength)
{
    std::vector<float> data = {
        -2.0f * strength, -1.0f * strength, 0.0f,
        -1.0f * strength, 1.0f, 1.0f * strength,
        0.0f, 1.0f * strength, 2.0f * strength
    };
    return KernelMatrix(3, 3, data, 1.0f, 128.0f);
}

KernelMatrix ImageFilter::CreateSobelKernel(bool horizontal)
{
    if (horizontal) {
        std::vector<float> data = {
            -1.0f, -2.0f, -1.0f,
             0.0f,  0.0f,  0.0f,
             1.0f,  2.0f,  1.0f
        };
        return KernelMatrix(3, 3, data, 1.0f, 0.0f);
    } else {
        std::vector<float> data = {
            -1.0f, 0.0f, 1.0f,
            -2.0f, 0.0f, 2.0f,
            -1.0f, 0.0f, 1.0f
        };
        return KernelMatrix(3, 3, data, 1.0f, 0.0f);
    }
}

KernelMatrix ImageFilter::CreateLaplacianKernel()
{
    std::vector<float> data = {
        0.0f,  1.0f, 0.0f,
        1.0f, -4.0f, 1.0f,
        0.0f,  1.0f, 0.0f
    };
    return KernelMatrix(3, 3, data, 1.0f, 0.0f);
}

KernelMatrix ImageFilter::CreatePrewittKernel(bool horizontal)
{
    if (horizontal) {
        std::vector<float> data = {
            -1.0f, -1.0f, -1.0f,
             0.0f,  0.0f,  0.0f,
             1.0f,  1.0f,  1.0f
        };
        return KernelMatrix(3, 3, data, 1.0f, 0.0f);
    } else {
        std::vector<float> data = {
            -1.0f, 0.0f, 1.0f,
            -1.0f, 0.0f, 1.0f,
            -1.0f, 0.0f, 1.0f
        };
        return KernelMatrix(3, 3, data, 1.0f, 0.0f);
    }
}

KernelMatrix ImageFilter::CreateBoxBlurKernel(int32_t size)
{
    std::vector<float> data(size * size, 1.0f);
    return KernelMatrix(size, size, data, static_cast<float>(size * size), 0.0f);
}

KernelMatrix ImageFilter::CreateMotionBlurKernel(int32_t length, float angle)
{
    std::vector<float> data(length * length, 0.0f);
    
    float radians = angle * M_PI / 180.0f;
    float dx = cos(radians);
    float dy = sin(radians);
    
    int32_t center = length / 2;
    for (int32_t i = 0; i < length; i++) {
        int32_t x = static_cast<int32_t>(center + (i - center) * dx);
        int32_t y = static_cast<int32_t>(center + (i - center) * dy);
        if (x >= 0 && x < length && y >= 0 && y < length) {
            data[y * length + x] = 1.0f;
        }
    }
    
    return KernelMatrix(length, length, data, static_cast<float>(length), 0.0f);
}

ColorRGBA ImageFilter::Grayscale(const ColorRGBA& color)
{
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    return ColorRGBA(gray, gray, gray, color.a);
}

ColorRGBA ImageFilter::Sepia(const ColorRGBA& color)
{
    float r = std::min(1.0f, 0.393f * color.r + 0.769f * color.g + 0.189f * color.b);
    float g = std::min(1.0f, 0.349f * color.r + 0.686f * color.g + 0.168f * color.b);
    float b = std::min(1.0f, 0.272f * color.r + 0.534f * color.g + 0.131f * color.b);
    return ColorRGBA(r, g, b, color.a);
}

ColorRGBA ImageFilter::Invert(const ColorRGBA& color)
{
    return ColorRGBA(1.0f - color.r, 1.0f - color.g, 1.0f - color.b, color.a);
}

ColorRGBA ImageFilter::Brightness(const ColorRGBA& color, float amount)
{
    return ColorRGBA(
        color.r + amount,
        color.g + amount,
        color.b + amount,
        color.a
    ).Clamp();
}

ColorRGBA ImageFilter::Contrast(const ColorRGBA& color, float amount)
{
    return ColorRGBA(
        (color.r - 0.5f) * amount + 0.5f,
        (color.g - 0.5f) * amount + 0.5f,
        (color.b - 0.5f) * amount + 0.5f,
        color.a
    ).Clamp();
}

ColorRGBA ImageFilter::Saturate(const ColorRGBA& color, float amount)
{
    ColorHSL hsl = ColorHSL::FromRGB(ColorRGB(color.r, color.g, color.b));
    hsl.s = std::max(0.0f, std::min(1.0f, hsl.s * amount));
    ColorRGB rgb = hsl.ToRGB();
    return ColorRGBA(rgb.r, rgb.g, rgb.b, color.a);
}

ColorRGBA ImageFilter::HueRotate(const ColorRGBA& color, float degrees)
{
    ColorHSL hsl = ColorHSL::FromRGB(ColorRGB(color.r, color.g, color.b));
    hsl.h = fmod(hsl.h + degrees, 360.0f);
    if (hsl.h < 0.0f) {
        hsl.h += 360.0f;
    }
    ColorRGB rgb = hsl.ToRGB();
    return ColorRGBA(rgb.r, rgb.g, rgb.b, color.a);
}

ColorRGBA ImageFilter::Threshold(const ColorRGBA& color, float threshold)
{
    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
    float value = gray >= threshold ? 1.0f : 0.0f;
    return ColorRGBA(value, value, value, color.a);
}

ColorRGBA ImageFilter::Posterize(const ColorRGBA& color, int32_t levels)
{
    if (levels < 2) {
        levels = 2;
    }
    float step = 1.0f / static_cast<float>(levels - 1);
    auto quantize = [step, levels](float value) -> float {
        int32_t level = static_cast<int32_t>(value * (levels - 1));
        return static_cast<float>(level) * step;
    };
    return ColorRGBA(
        quantize(color.r),
        quantize(color.g),
        quantize(color.b),
        color.a
    );
}

ColorRGBA ImageFilter::Solarize(const ColorRGBA& color, float threshold)
{
    auto solarize = [threshold](float value) -> float {
        return value > threshold ? 1.0f - value : value;
    };
    return ColorRGBA(
        solarize(color.r),
        solarize(color.g),
        solarize(color.b),
        color.a
    );
}

ColorRGB ImageFilter::ApplyColorMatrix(const ColorRGB& color, const std::vector<float>& matrix)
{
    if (matrix.size() < 9) {
        return color;
    }
    return ColorRGB(
        matrix[0] * color.r + matrix[1] * color.g + matrix[2] * color.b,
        matrix[3] * color.r + matrix[4] * color.g + matrix[5] * color.b,
        matrix[6] * color.r + matrix[7] * color.g + matrix[8] * color.b
    ).Clamp();
}

ColorRGBA ImageFilter::ConvolvePixel(const std::vector<ColorRGBA>& neighborhood, const KernelMatrix& kernel)
{
    if (!kernel.IsValid() || neighborhood.size() != kernel.data.size()) {
        return ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
    
    for (size_t i = 0; i < neighborhood.size(); i++) {
        float weight = kernel.data[i];
        r += neighborhood[i].r * weight;
        g += neighborhood[i].g * weight;
        b += neighborhood[i].b * weight;
        a += neighborhood[i].a * weight;
    }
    
    if (kernel.divisor != 0.0f && kernel.divisor != 1.0f) {
        r /= kernel.divisor;
        g /= kernel.divisor;
        b /= kernel.divisor;
        a /= kernel.divisor;
    }
    
    r += kernel.offset / 255.0f;
    g += kernel.offset / 255.0f;
    b += kernel.offset / 255.0f;
    
    return ColorRGBA(r, g, b, a).Clamp();
}

std::string ImageFilter::GetName() const
{
    switch (type_) {
        case FilterType::NONE: return "None";
        case FilterType::BLUR: return "Blur";
        case FilterType::SHARPEN: return "Sharpen";
        case FilterType::EDGE_DETECT: return "Edge Detect";
        case FilterType::EMBOSS: return "Emboss";
        case FilterType::GRAYSCALE: return "Grayscale";
        case FilterType::SEPIA: return "Sepia";
        case FilterType::INVERT: return "Invert";
        case FilterType::BRIGHTNESS: return "Brightness";
        case FilterType::CONTRAST: return "Contrast";
        case FilterType::SATURATION: return "Saturation";
        case FilterType::HUE_ROTATE: return "Hue Rotate";
        case FilterType::GAUSSIAN_BLUR: return "Gaussian Blur";
        case FilterType::BOX_BLUR: return "Box Blur";
        case FilterType::MOTION_BLUR: return "Motion Blur";
        case FilterType::BILATERAL_FILTER: return "Bilateral Filter";
        case FilterType::MEDIAN_FILTER: return "Median Filter";
        case FilterType::SOBEL: return "Sobel";
        case FilterType::LAPLACIAN: return "Laplacian";
        case FilterType::PREWITT: return "Prewitt";
        case FilterType::DILATION: return "Dilation";
        case FilterType::EROSION: return "Erosion";
        case FilterType::THRESHOLD: return "Threshold";
        case FilterType::POSTERIZE: return "Posterize";
        case FilterType::SOLARIZE: return "Solarize";
        case FilterType::VIGNETTE: return "Vignette";
        case FilterType::PIXELATE: return "Pixelate";
        case FilterType::HALFTONE: return "Halftone";
        case FilterType::DITHER: return "Dither";
        case FilterType::COLOR_MATRIX: return "Color Matrix";
        case FilterType::CONVOLUTION: return "Convolution";
        default: return "Unknown";
    }
}

std::string ImageFilter::ToString() const
{
    return "ImageFilter{type=" + GetName() + 
           ", intensity=" + std::to_string(params_.intensity) + "}";
}

ColorRGBA ImageFilter::GetPixel(uint8_t* pixelData, int32_t x, int32_t y,
                                int32_t width, int32_t height, int32_t stride) const
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
    }
    
    uint8_t* pixel = pixelData + y * stride + x * 4;
    return ColorRGBA(
        pixel[0] / 255.0f,
        pixel[1] / 255.0f,
        pixel[2] / 255.0f,
        pixel[3] / 255.0f
    );
}

void ImageFilter::SetPixel(uint8_t* pixelData, int32_t x, int32_t y,
                           int32_t stride, const ColorRGBA& color) const
{
    uint8_t* pixel = pixelData + y * stride + x * 4;
    pixel[0] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.r * 255.0f)));
    pixel[1] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.g * 255.0f)));
    pixel[2] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.b * 255.0f)));
    pixel[3] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.a * 255.0f)));
}

bool ImageFilter::Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    if (!pixelData || width <= 0 || height <= 0 || stride <= 0) {
        return false;
    }

    switch (type_) {
        case FilterType::BLUR:
            return ApplyBlur(pixelData, width, height, stride);
        case FilterType::SHARPEN:
            return ApplySharpen(pixelData, width, height, stride);
        case FilterType::EDGE_DETECT:
            return ApplyEdgeDetect(pixelData, width, height, stride);
        case FilterType::EMBOSS:
            return ApplyEmboss(pixelData, width, height, stride);
        case FilterType::GRAYSCALE:
            return ApplyGrayscale(pixelData, width, height, stride);
        case FilterType::SEPIA:
            return ApplySepia(pixelData, width, height, stride);
        case FilterType::INVERT:
            return ApplyInvert(pixelData, width, height, stride);
        case FilterType::BRIGHTNESS:
            return ApplyBrightness(pixelData, width, height, stride);
        case FilterType::CONTRAST:
            return ApplyContrast(pixelData, width, height, stride);
        case FilterType::SATURATION:
            return ApplySaturation(pixelData, width, height, stride);
        case FilterType::HUE_ROTATE:
            return ApplyHueRotate(pixelData, width, height, stride);
        case FilterType::GAUSSIAN_BLUR:
            return ApplyGaussianBlur(pixelData, width, height, stride);
        case FilterType::BOX_BLUR:
            return ApplyBoxBlur(pixelData, width, height, stride);
        case FilterType::MOTION_BLUR:
            return ApplyMotionBlur(pixelData, width, height, stride);
        case FilterType::MEDIAN_FILTER:
            return ApplyMedianFilter(pixelData, width, height, stride);
        case FilterType::SOBEL:
            return ApplySobel(pixelData, width, height, stride);
        case FilterType::LAPLACIAN:
            return ApplyLaplacian(pixelData, width, height, stride);
        case FilterType::PREWITT:
            return ApplyPrewitt(pixelData, width, height, stride);
        case FilterType::DILATION:
            return ApplyDilation(pixelData, width, height, stride);
        case FilterType::EROSION:
            return ApplyErosion(pixelData, width, height, stride);
        case FilterType::THRESHOLD:
            return ApplyThreshold(pixelData, width, height, stride);
        case FilterType::POSTERIZE:
            return ApplyPosterize(pixelData, width, height, stride);
        case FilterType::SOLARIZE:
            return ApplySolarize(pixelData, width, height, stride);
        case FilterType::VIGNETTE:
            return ApplyVignette(pixelData, width, height, stride);
        case FilterType::PIXELATE:
            return ApplyPixelate(pixelData, width, height, stride);
        case FilterType::HALFTONE:
            return ApplyHalftone(pixelData, width, height, stride);
        case FilterType::CONVOLUTION:
            return ApplyConvolution(pixelData, width, height, stride);
        case FilterType::NONE:
        default:
            return true;
    }
}

bool ImageFilter::Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height)
{
    return Apply(pixelData.data(), width, height, width * 4);
}

bool ImageFilter::ApplyBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t radius = static_cast<int32_t>(params_.radius);
    if (radius < 1) {
        radius = 1;
    }
    auto kernel = CreateBlurKernel(radius);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplySharpen(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernel = CreateSharpenKernel(params_.intensity);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyEdgeDetect(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernel = CreateEdgeDetectKernel();
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyEmboss(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernel = CreateEmbossKernel(params_.intensity);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyGrayscale(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA gray = Grayscale(color);
            SetPixel(pixelData, x, y, stride, gray);
        }
    }
    return true;
}

bool ImageFilter::ApplySepia(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA sepiaColor = Sepia(color);
            SetPixel(pixelData, x, y, stride, sepiaColor);
        }
    }
    return true;
}

bool ImageFilter::ApplyInvert(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA inverted = Invert(color);
            SetPixel(pixelData, x, y, stride, inverted);
        }
    }
    return true;
}

bool ImageFilter::ApplyBrightness(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA adjusted = Brightness(color, params_.brightness);
            SetPixel(pixelData, x, y, stride, adjusted);
        }
    }
    return true;
}

bool ImageFilter::ApplyContrast(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA adjusted = Contrast(color, params_.contrast);
            SetPixel(pixelData, x, y, stride, adjusted);
        }
    }
    return true;
}

bool ImageFilter::ApplySaturation(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA adjusted = Saturate(color, params_.saturation);
            SetPixel(pixelData, x, y, stride, adjusted);
        }
    }
    return true;
}

bool ImageFilter::ApplyHueRotate(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA adjusted = HueRotate(color, params_.hue);
            SetPixel(pixelData, x, y, stride, adjusted);
        }
    }
    return true;
}

bool ImageFilter::ApplyGaussianBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t radius = static_cast<int32_t>(params_.radius);
    if (radius < 1) {
        radius = 1;
    }
    auto kernel = CreateGaussianKernel(radius, params_.intensity);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyBoxBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t size = static_cast<int32_t>(params_.radius);
    if (size < 1) {
        size = 3;
    }
    if (size % 2 == 0) {
        size++;
    }
    auto kernel = CreateBoxBlurKernel(size);
    std::vector<uint8_t> temp(stride * height);
    
    int32_t radius = size / 2;
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyMotionBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t length = static_cast<int32_t>(params_.radius);
    if (length < 3) {
        length = 3;
    }
    if (length % 2 == 0) {
        length++;
    }
    auto kernel = CreateMotionBlurKernel(length, params_.hue);
    std::vector<uint8_t> temp(stride * height);
    
    int32_t radius = length / 2;
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyMedianFilter(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t radius = static_cast<int32_t>(params_.radius);
    if (radius < 1) {
        radius = 1;
    }
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<float> rVals, gVals, bVals, aVals;
            
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    rVals.push_back(color.r);
                    gVals.push_back(color.g);
                    bVals.push_back(color.b);
                    aVals.push_back(color.a);
                }
            }
            
            size_t mid = rVals.size() / 2;
            std::nth_element(rVals.begin(), rVals.begin() + mid, rVals.end());
            std::nth_element(gVals.begin(), gVals.begin() + mid, gVals.end());
            std::nth_element(bVals.begin(), bVals.begin() + mid, bVals.end());
            std::nth_element(aVals.begin(), aVals.begin() + mid, aVals.end());
            
            ColorRGBA result(rVals[mid], gVals[mid], bVals[mid], aVals[mid]);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplySobel(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernelX = CreateSobelKernel(true);
    auto kernelY = CreateSobelKernel(false);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
                    neighborhood.push_back(ColorRGBA(gray, gray, gray, 1.0f));
                }
            }
            
            ColorRGBA gx = ConvolvePixel(neighborhood, kernelX);
            ColorRGBA gy = ConvolvePixel(neighborhood, kernelY);
            
            float magnitude = sqrt(gx.r * gx.r + gy.r * gy.r);
            ColorRGBA result(magnitude, magnitude, magnitude, 1.0f);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyLaplacian(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernel = CreateLaplacianKernel();
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
                    neighborhood.push_back(ColorRGBA(gray, gray, gray, 1.0f));
                }
            }
            
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            float absVal = std::abs(result.r);
            result = ColorRGBA(absVal, absVal, absVal, 1.0f);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyPrewitt(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    auto kernelX = CreatePrewittKernel(true);
    auto kernelY = CreatePrewittKernel(false);
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -1; ky <= 1; ky++) {
                for (int32_t kx = -1; kx <= 1; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
                    neighborhood.push_back(ColorRGBA(gray, gray, gray, 1.0f));
                }
            }
            
            ColorRGBA gx = ConvolvePixel(neighborhood, kernelX);
            ColorRGBA gy = ConvolvePixel(neighborhood, kernelY);
            
            float magnitude = sqrt(gx.r * gx.r + gy.r * gy.r);
            ColorRGBA result(magnitude, magnitude, magnitude, 1.0f);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyDilation(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t radius = static_cast<int32_t>(params_.radius);
    if (radius < 1) {
        radius = 1;
    }
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float maxR = 0.0f, maxG = 0.0f, maxB = 0.0f, maxA = 0.0f;
            
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    maxR = std::max(maxR, color.r);
                    maxG = std::max(maxG, color.g);
                    maxB = std::max(maxB, color.b);
                    maxA = std::max(maxA, color.a);
                }
            }
            
            SetPixel(temp.data(), x, y, stride, ColorRGBA(maxR, maxG, maxB, maxA));
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyErosion(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t radius = static_cast<int32_t>(params_.radius);
    if (radius < 1) {
        radius = 1;
    }
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float minR = 1.0f, minG = 1.0f, minB = 1.0f, minA = 1.0f;
            
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    ColorRGBA color = GetPixel(pixelData, nx, ny, width, height, stride);
                    minR = std::min(minR, color.r);
                    minG = std::min(minG, color.g);
                    minB = std::min(minB, color.b);
                    minA = std::min(minA, color.a);
                }
            }
            
            SetPixel(temp.data(), x, y, stride, ColorRGBA(minR, minG, minB, minA));
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyThreshold(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA result = Threshold(color, params_.threshold);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    return true;
}

bool ImageFilter::ApplyPosterize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t levels = static_cast<int32_t>(params_.intensity);
    if (levels < 2) {
        levels = 2;
    }
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA result = Posterize(color, levels);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    return true;
}

bool ImageFilter::ApplySolarize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA result = Solarize(color, params_.threshold);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    return true;
}

bool ImageFilter::ApplyVignette(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    float centerX = static_cast<float>(width) / 2.0f;
    float centerY = static_cast<float>(height) / 2.0f;
    float maxDist = sqrt(centerX * centerX + centerY * centerY);
    float intensity = params_.intensity;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = sqrt(dx * dx + dy * dy);
            float vignette = 1.0f - (dist / maxDist) * intensity;
            vignette = std::max(0.0f, std::min(1.0f, vignette));
            
            ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
            ColorRGBA result(color.r * vignette, color.g * vignette, color.b * vignette, color.a);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    return true;
}

bool ImageFilter::ApplyPixelate(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t blockSize = static_cast<int32_t>(params_.radius);
    if (blockSize < 1) {
        blockSize = 1;
    }
    std::vector<uint8_t> temp(stride * height);
    
    for (int32_t by = 0; by < height; by += blockSize) {
        for (int32_t bx = 0; bx < width; bx += blockSize) {
            float sumR = 0.0f, sumG = 0.0f, sumB = 0.0f, sumA = 0.0f;
            int32_t count = 0;
            
            for (int32_t y = by; y < std::min(by + blockSize, height); y++) {
                for (int32_t x = bx; x < std::min(bx + blockSize, width); x++) {
                    ColorRGBA color = GetPixel(pixelData, x, y, width, height, stride);
                    sumR += color.r;
                    sumG += color.g;
                    sumB += color.b;
                    sumA += color.a;
                    count++;
                }
            }
            
            if (count > 0) {
                ColorRGBA avg(sumR / count, sumG / count, sumB / count, sumA / count);
                for (int32_t y = by; y < std::min(by + blockSize, height); y++) {
                    for (int32_t x = bx; x < std::min(bx + blockSize, width); x++) {
                        SetPixel(temp.data(), x, y, stride, avg);
                    }
                }
            }
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyHalftone(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    int32_t dotSize = static_cast<int32_t>(params_.radius);
    if (dotSize < 2) {
        dotSize = 2;
    }
    std::vector<uint8_t> temp(stride * height, 255);
    
    for (int32_t by = 0; by < height; by += dotSize) {
        for (int32_t bx = 0; bx < width; bx += dotSize) {
            ColorRGBA color = GetPixel(pixelData, bx, by, width, height, stride);
            float gray = 0.299f * color.r + 0.587f * color.g + 0.114f * color.b;
            
            float radius = (1.0f - gray) * (dotSize / 2.0f);
            int32_t cx = bx + dotSize / 2;
            int32_t cy = by + dotSize / 2;
            
            for (int32_t y = by; y < std::min(by + dotSize, height); y++) {
                for (int32_t x = bx; x < std::min(bx + dotSize, width); x++) {
                    float dx = x - cx;
                    float dy = y - cy;
                    float dist = sqrt(dx * dx + dy * dy);
                    
                    if (dist <= radius) {
                        SetPixel(temp.data(), x, y, stride, ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f));
                    }
                }
            }
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

bool ImageFilter::ApplyConvolution(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    if (params_.kernel.empty()) {
        return false;
    }
    int32_t kernelSize = static_cast<int32_t>(sqrt(params_.kernel.size()));
    if (kernelSize * kernelSize != static_cast<int32_t>(params_.kernel.size())) {
        return false;
    }
    if (kernelSize % 2 == 0) {
        return false;
    }
    KernelMatrix kernel(kernelSize, kernelSize, params_.kernel, 1.0f, 0.0f);
    std::vector<uint8_t> temp(stride * height);
    
    int32_t radius = kernelSize / 2;
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            std::vector<ColorRGBA> neighborhood;
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    neighborhood.push_back(GetPixel(pixelData, nx, ny, width, height, stride));
                }
            }
            ColorRGBA result = ConvolvePixel(neighborhood, kernel);
            SetPixel(temp.data(), x, y, stride, result);
        }
    }
    
    std::memcpy_s(pixelData, temp.data(), stride * height);
    return true;
}

ColorRGBA ImageFilter::ApplyToPixel(const ColorRGBA& color) const
{
    switch (type_) {
        case FilterType::GRAYSCALE:
            return Grayscale(color);
        case FilterType::SEPIA:
            return Sepia(color);
        case FilterType::INVERT:
            return Invert(color);
        case FilterType::BRIGHTNESS:
            return Brightness(color, params_.brightness);
        case FilterType::CONTRAST:
            return Contrast(color, params_.contrast);
        case FilterType::SATURATION:
            return Saturate(color, params_.saturation);
        case FilterType::HUE_ROTATE:
            return HueRotate(color, params_.hue);
        case FilterType::THRESHOLD:
            return Threshold(color, params_.threshold);
        case FilterType::POSTERIZE:
            return Posterize(color, static_cast<int32_t>(params_.intensity));
        case FilterType::SOLARIZE:
            return Solarize(color, params_.threshold);
        case FilterType::COLOR_MATRIX:
            if (params_.colorMatrix.size() >= 9) {
                ColorRGB rgb = ApplyColorMatrix(color.ToRGB(), params_.colorMatrix);
                return ColorRGBA(rgb.r, rgb.g, rgb.b, color.a);
            }
            return color;
        default:
            return color;
    }
}

void ImageFilterChain::AddFilter(std::shared_ptr<ImageFilter> filter)
{
    if (filter) {
        filters_.push_back(filter);
    }
}

void ImageFilterChain::AddFilter(FilterType type, const FilterParams& params)
{
    filters_.push_back(ImageFilter::Create(type, params));
}

void ImageFilterChain::RemoveFilter(int32_t index)
{
    if (index >= 0 && index < static_cast<int32_t>(filters_.size())) {
        filters_.erase(filters_.begin() + index);
    }
}

void ImageFilterChain::ClearFilters()
{
    filters_.clear();
}

bool ImageFilterChain::Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (auto& filter : filters_) {
        if (!filter->Apply(pixelData, width, height, stride)) {
            return false;
        }
    }
    return true;
}

bool ImageFilterChain::Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height)
{
    return Apply(pixelData.data(), width, height, width * 4);
}

std::shared_ptr<ImageFilter> ImageFilterChain::GetFilter(int32_t index) const
{
    if (index >= 0 && index < static_cast<int32_t>(filters_.size())) {
        return filters_[index];
    }
    return nullptr;
}

std::string ImageFilterChain::ToString() const
{
    std::string result = "ImageFilterChain{filters=[";
    for (size_t i = 0; i < filters_.size(); i++) {
        result += filters_[i]->GetName();
        if (i < filters_.size() - 1) {
            result += ", ";
        }
    }
    result += "]}";
    return result;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateVintage()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::SEPIA);
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.1f});
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = -0.05f});
    chain->AddFilter(FilterType::VIGNETTE, FilterParams{.intensity = 0.3f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateDramatic()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.5f});
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 1.3f});
    chain->AddFilter(FilterType::SHARPEN, FilterParams{.intensity = 0.5f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateCold()
{
    auto chain = std::make_shared<ImageFilterChain>();
    FilterParams hueParams;
    hueParams.hue = -15.0f;
    chain->AddFilter(FilterType::HUE_ROTATE, hueParams);
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 0.9f});
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = 0.05f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateWarm()
{
    auto chain = std::make_shared<ImageFilterChain>();
    FilterParams hueParams;
    hueParams.hue = 15.0f;
    chain->AddFilter(FilterType::HUE_ROTATE, hueParams);
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 1.1f});
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = 0.05f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateFilmNoir()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::GRAYSCALE);
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.4f});
    chain->AddFilter(FilterType::VIGNETTE, FilterParams{.intensity = 0.5f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreatePopArt()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::POSTERIZE, FilterParams{.intensity = 4.0f});
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 2.0f});
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.3f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateDreamy()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::GAUSSIAN_BLUR, FilterParams{.radius = 2.0f});
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = 0.1f});
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 0.8f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateHDR()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.2f});
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 1.4f});
    chain->AddFilter(FilterType::SHARPEN, FilterParams{.intensity = 0.3f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateSketch()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::GRAYSCALE);
    chain->AddFilter(FilterType::SOBEL);
    chain->AddFilter(FilterType::INVERT);
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.5f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateOilPaint()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::PIXELATE, FilterParams{.radius = 3.0f});
    chain->AddFilter(FilterType::GAUSSIAN_BLUR, FilterParams{.radius = 1.0f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateWatercolor()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::MEDIAN_FILTER, FilterParams{.radius = 3.0f});
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 0.7f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateComicBook()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::POSTERIZE, FilterParams{.intensity = 6.0f});
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.2f});
    chain->AddFilter(FilterType::SHARPEN, FilterParams{.intensity = 0.8f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateNeon()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::EDGE_DETECT);
    chain->AddFilter(FilterType::INVERT);
    chain->AddFilter(FilterType::SATURATION, FilterParams{.saturation = 2.0f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateRetro()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::SEPIA);
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = -0.1f});
    chain->AddFilter(FilterType::VIGNETTE, FilterParams{.intensity = 0.4f});
    return chain;
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::CreateNoir()
{
    auto chain = std::make_shared<ImageFilterChain>();
    chain->AddFilter(FilterType::GRAYSCALE);
    chain->AddFilter(FilterType::CONTRAST, FilterParams{.contrast = 1.6f});
    chain->AddFilter(FilterType::BRIGHTNESS, FilterParams{.brightness = -0.1f});
    chain->AddFilter(FilterType::VIGNETTE, FilterParams{.intensity = 0.6f});
    return chain;
}

std::vector<std::string> ImageFilterPreset::GetPresetNames()
{
    return {
        "vintage", "dramatic", "cold", "warm", "film_noir",
        "pop_art", "dreamy", "hdr", "sketch", "oil_paint",
        "watercolor", "comic_book", "neon", "retro", "noir"
    };
}

std::shared_ptr<ImageFilterChain> ImageFilterPreset::GetPresetByName(const std::string& name)
{
    if (name == "vintage") {
        return CreateVintage();
    }
    if (name == "dramatic") {
        return CreateDramatic();
    }
    if (name == "cold") {
        return CreateCold();
    }
    if (name == "warm") {
        return CreateWarm();
    }
    if (name == "film_noir") {
        return CreateFilmNoir();
    }
    if (name == "pop_art") {
        return CreatePopArt();
    }
    if (name == "dreamy") {
        return CreateDreamy();
    }
    if (name == "hdr") {
        return CreateHDR();
    }
    if (name == "sketch") {
        return CreateSketch();
    }
    if (name == "oil_paint") {
        return CreateOilPaint();
    }
    if (name == "watercolor") {
        return CreateWatercolor();
    }
    if (name == "comic_book") {
        return CreateComicBook();
    }
    if (name == "neon") {
        return CreateNeon();
    }
    if (name == "retro") {
        return CreateRetro();
    }
    if (name == "noir") {
        return CreateNoir();
    }
    return std::make_shared<ImageFilterChain>();
}

} // namespace Self::UI

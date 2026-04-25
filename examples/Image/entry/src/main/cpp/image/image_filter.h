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

#ifndef CAPI_IMAGE_FILTER_H
#define CAPI_IMAGE_FILTER_H

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

#include "image/pixel_map.h"
#include "utils/log.h"

namespace Self::UI {

enum class FilterType {
    NONE = 0,
    BLUR = 1,
    SHARPEN = 2,
    EDGE_DETECT = 3,
    EMBOSS = 4,
    GRAYSCALE = 5,
    SEPIA = 6,
    INVERT = 7,
    BRIGHTNESS = 8,
    CONTRAST = 9,
    SATURATION = 10,
    HUE_ROTATE = 11,
    GAUSSIAN_BLUR = 12,
    BOX_BLUR = 13,
    MOTION_BLUR = 14,
    BILATERAL_FILTER = 15,
    MEDIAN_FILTER = 16,
    SOBEL = 17,
    LAPLACIAN = 18,
    PREWITT = 19,
    DILATION = 20,
    EROSION = 21,
    THRESHOLD = 22,
    POSTERIZE = 23,
    SOLARIZE = 24,
    VIGNETTE = 25,
    PIXELATE = 26,
    HALFTONE = 27,
    DITHER = 28,
    COLOR_MATRIX = 29,
    CONVOLUTION = 30
};

struct FilterParams {
    float intensity = 1.0f;
    float radius = 1.0f;
    float threshold = 0.5f;
    float brightness = 0.0f;
    float contrast = 1.0f;
    float saturation = 1.0f;
    float hue = 0.0f;
    int32_t iterations = 1;
    bool invertAlpha = false;
    std::vector<float> kernel;
    std::vector<float> colorMatrix;
};

struct ColorRGB {
    float r;
    float g;
    float b;
    
    ColorRGB() : r(0.0f), g(0.0f), b(0.0f) {}
    ColorRGB(float red, float green, float blue) : r(red), g(green), b(blue) {}
    
    ColorRGB Clamp() const {
        return ColorRGB(
            std::max(0.0f, std::min(1.0f, r)),
            std::max(0.0f, std::min(1.0f, g)),
            std::max(0.0f, std::min(1.0f, b))
        );
    }
    
    ColorRGB operator+(const ColorRGB& other) const {
        return ColorRGB(r + other.r, g + other.g, b + other.b);
    }
    
    ColorRGB operator-(const ColorRGB& other) const {
        return ColorRGB(r - other.r, g - other.g, b - other.b);
    }
    
    ColorRGB operator*(float scalar) const {
        return ColorRGB(r * scalar, g * scalar, b * scalar);
    }
    
    std::string ToString() const {
        return "RGB(" + std::to_string(r) + ", " + std::to_string(g) + ", " + std::to_string(b) + ")";
    }
};

struct ColorRGBA {
    float r;
    float g;
    float b;
    float a;
    
    ColorRGBA() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    ColorRGBA(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
    
    ColorRGB ToRGB() const {
        return ColorRGB(r, g, b);
    }
    
    ColorRGBA Clamp() const {
        return ColorRGBA(
            std::max(0.0f, std::min(1.0f, r)),
            std::max(0.0f, std::min(1.0f, g)),
            std::max(0.0f, std::min(1.0f, b)),
            std::max(0.0f, std::min(1.0f, a))
        );
    }
    
    ColorRGBA operator+(const ColorRGBA& other) const {
        return ColorRGBA(r + other.r, g + other.g, b + other.b, a + other.a);
    }
    
    ColorRGBA operator*(float scalar) const {
        return ColorRGBA(r * scalar, g * scalar, b * scalar, a * scalar);
    }
    
    std::string ToString() const {
        return "RGBA(" + std::to_string(r) + ", " + std::to_string(g) + ", " + 
               std::to_string(b) + ", " + std::to_string(a) + ")";
    }
};

struct ColorHSL {
    float h;
    float s;
    float l;
    
    ColorHSL() : h(0.0f), s(0.0f), l(0.0f) {}
    ColorHSL(float hue, float saturation, float lightness)
        : h(hue), s(saturation), l(lightness) {}
    
    ColorRGB ToRGB() const;
    static ColorHSL FromRGB(const ColorRGB& rgb);
    
    ColorHSL Clamp() const {
        return ColorHSL(
            std::fmod(h, 360.0f),
            std::max(0.0f, std::min(1.0f, s)),
            std::max(0.0f, std::min(1.0f, l))
        );
    }
    
    std::string ToString() const {
        return "HSL(" + std::to_string(h) + ", " + std::to_string(s) + ", " + std::to_string(l) + ")";
    }
};

struct ColorHSV {
    float h;
    float s;
    float v;
    
    ColorHSV() : h(0.0f), s(0.0f), v(0.0f) {}
    ColorHSV(float hue, float saturation, float value)
        : h(hue), s(saturation), v(value) {}
    
    ColorRGB ToRGB() const;
    static ColorHSV FromRGB(const ColorRGB& rgb);
    
    ColorHSV Clamp() const {
        return ColorHSV(
            std::fmod(h, 360.0f),
            std::max(0.0f, std::min(1.0f, s)),
            std::max(0.0f, std::min(1.0f, v))
        );
    }
    
    std::string ToString() const {
        return "HSV(" + std::to_string(h) + ", " + std::to_string(s) + ", " + std::to_string(v) + ")";
    }
};

struct ColorCMYK {
    float c;
    float m;
    float y;
    float k;
    
    ColorCMYK() : c(0.0f), m(0.0f), y(0.0f), k(0.0f) {}
    ColorCMYK(float cyan, float magenta, float yellow, float black)
        : c(cyan), m(magenta), y(yellow), k(black) {}
    
    ColorRGB ToRGB() const;
    static ColorCMYK FromRGB(const ColorRGB& rgb);
    
    ColorCMYK Clamp() const {
        return ColorCMYK(
            std::max(0.0f, std::min(1.0f, c)),
            std::max(0.0f, std::min(1.0f, m)),
            std::max(0.0f, std::min(1.0f, y)),
            std::max(0.0f, std::min(1.0f, k))
        );
    }
    
    std::string ToString() const {
        return "CMYK(" + std::to_string(c) + ", " + std::to_string(m) + ", " + 
               std::to_string(y) + ", " + std::to_string(k) + ")";
    }
};

struct KernelMatrix {
    int32_t width;
    int32_t height;
    std::vector<float> data;
    float divisor;
    float offset;
    
    KernelMatrix() : width(0), height(0), divisor(1.0f), offset(0.0f) {}
    
    KernelMatrix(int32_t w, int32_t h, const std::vector<float>& d, 
                 float div = 1.0f, float off = 0.0f)
        : width(w), height(h), data(d), divisor(div), offset(off) {}
    
    float At(int32_t x, int32_t y) const {
        if (x < 0 || x >= width || y < 0 || y >= height) {
            return 0.0f;
        }
        return data[y * width + x];
    }
    
    void SetAt(int32_t x, int32_t y, float value) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            data[y * width + x] = value;
        }
    }
    
    void Normalize() {
        float sum = 0.0f;
        for (float val : data) {
            sum += val;
        }
        if (sum != 0.0f) {
            divisor = sum;
        }
    }
    
    bool IsValid() const {
        return width > 0 && height > 0 && 
               static_cast<int32_t>(data.size()) == width * height;
    }
    
    std::string ToString() const {
        std::string result = "Kernel(" + std::to_string(width) + "x" + 
                             std::to_string(height) + "):\n";
        for (int32_t y = 0; y < height; y++) {
            result += "[";
            for (int32_t x = 0; x < width; x++) {
                result += std::to_string(data[y * width + x]);
                if (x < width - 1) result += ", ";
            }
            result += "]\n";
        }
        return result;
    }
};

class ImageFilter {
public:
    ImageFilter() : type_(FilterType::NONE), params_() {}
    explicit ImageFilter(FilterType type, const FilterParams& params = FilterParams())
        : type_(type), params_(params) {}
    
    ~ImageFilter() = default;
    
    static std::shared_ptr<ImageFilter> Create(FilterType type, const FilterParams& params = FilterParams());
    
    FilterType GetType() const { return type_; }
    FilterParams GetParams() const { return params_; }
    void SetParams(const FilterParams& params) { params_ = params; }
    
    bool Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height);
    
    ColorRGBA ApplyToPixel(const ColorRGBA& color) const;
    
    static KernelMatrix CreateBlurKernel(int32_t radius);
    static KernelMatrix CreateGaussianKernel(int32_t radius, float sigma = 0.0f);
    static KernelMatrix CreateSharpenKernel(float amount = 1.0f);
    static KernelMatrix CreateEdgeDetectKernel();
    static KernelMatrix CreateEmbossKernel(float strength = 1.0f);
    static KernelMatrix CreateSobelKernel(bool horizontal);
    static KernelMatrix CreateLaplacianKernel();
    static KernelMatrix CreatePrewittKernel(bool horizontal);
    static KernelMatrix CreateBoxBlurKernel(int32_t size);
    static KernelMatrix CreateMotionBlurKernel(int32_t length, float angle);
    
    static ColorRGBA Grayscale(const ColorRGBA& color);
    static ColorRGBA Sepia(const ColorRGBA& color);
    static ColorRGBA Invert(const ColorRGBA& color);
    static ColorRGBA Brightness(const ColorRGBA& color, float amount);
    static ColorRGBA Contrast(const ColorRGBA& color, float amount);
    static ColorRGBA Saturate(const ColorRGBA& color, float amount);
    static ColorRGBA HueRotate(const ColorRGBA& color, float degrees);
    static ColorRGBA Threshold(const ColorRGBA& color, float threshold);
    static ColorRGBA Posterize(const ColorRGBA& color, int32_t levels);
    static ColorRGBA Solarize(const ColorRGBA& color, float threshold);
    
    static ColorRGB ApplyColorMatrix(const ColorRGB& color, const std::vector<float>& matrix);
    static ColorRGBA ConvolvePixel(const std::vector<ColorRGBA>& neighborhood, 
                                   const KernelMatrix& kernel);
    
    std::string GetName() const;
    std::string ToString() const;
    
private:
    bool ApplyBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySharpen(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyEdgeDetect(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyEmboss(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyGrayscale(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySepia(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyInvert(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyBrightness(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyContrast(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySaturation(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyHueRotate(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyGaussianBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyBoxBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyMotionBlur(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyMedianFilter(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySobel(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyLaplacian(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyPrewitt(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyDilation(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyErosion(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyThreshold(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyPosterize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySolarize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyVignette(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyPixelate(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyHalftone(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyConvolution(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    
    ColorRGBA GetPixel(uint8_t* pixelData, int32_t x, int32_t y, 
                       int32_t width, int32_t height, int32_t stride) const;
    void SetPixel(uint8_t* pixelData, int32_t x, int32_t y, 
                  int32_t stride, const ColorRGBA& color) const;
    
    FilterType type_;
    FilterParams params_;
};

class ImageFilterChain {
public:
    ImageFilterChain() {}
    ~ImageFilterChain() = default;
    
    void AddFilter(std::shared_ptr<ImageFilter> filter);
    void AddFilter(FilterType type, const FilterParams& params = FilterParams());
    void RemoveFilter(int32_t index);
    void ClearFilters();
    
    bool Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height);
    
    int32_t GetFilterCount() const { return static_cast<int32_t>(filters_.size()); }
    std::shared_ptr<ImageFilter> GetFilter(int32_t index) const;
    
    std::string ToString() const;
    
private:
    std::vector<std::shared_ptr<ImageFilter>> filters_;
};

class ImageFilterPreset {
public:
    static std::shared_ptr<ImageFilterChain> CreateVintage();
    static std::shared_ptr<ImageFilterChain> CreateDramatic();
    static std::shared_ptr<ImageFilterChain> CreateCold();
    static std::shared_ptr<ImageFilterChain> CreateWarm();
    static std::shared_ptr<ImageFilterChain> CreateFilmNoir();
    static std::shared_ptr<ImageFilterChain> CreatePopArt();
    static std::shared_ptr<ImageFilterChain> CreateDreamy();
    static std::shared_ptr<ImageFilterChain> CreateHDR();
    static std::shared_ptr<ImageFilterChain> CreateSketch();
    static std::shared_ptr<ImageFilterChain> CreateOilPaint();
    static std::shared_ptr<ImageFilterChain> CreateWatercolor();
    static std::shared_ptr<ImageFilterChain> CreateComicBook();
    static std::shared_ptr<ImageFilterChain> CreateNeon();
    static std::shared_ptr<ImageFilterChain> CreateRetro();
    static std::shared_ptr<ImageFilterChain> CreateNoir();
    
    static std::vector<std::string> GetPresetNames();
    static std::shared_ptr<ImageFilterChain> GetPresetByName(const std::string& name);
};

} // namespace Self::UI

#endif // CAPI_IMAGE_FILTER_H

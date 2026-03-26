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

#ifndef CAPI_IMAGE_EFFECT_H
#define CAPI_IMAGE_EFFECT_H

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

namespace Self::UI {

enum class EffectType {
    NONE = 0,
    SHADOW = 1,
    GLOW = 2,
    BLUR = 3,
    REFLECTION = 4,
    GRADIENT_OVERLAY = 5,
    NOISE = 6,
    VIGNETTE = 7,
    BORDER = 8,
    OUTER_GLOW = 9,
    INNER_GLOW = 10,
    BEVEL = 11,
    EMBOSS_EFFECT = 12,
    ENGRAVE = 13,
    STAMP = 14,
    WATERMARK = 15,
    FRAME = 16,
    MIRROR = 17,
    TILE = 18,
    KALEIDOSCOPE = 19,
    FISHEYE = 20,
    SPHERIZE = 21,
    PINCH = 22,
    BULGE = 23,
    TWIRL = 24,
    WAVE = 25,
    RIPPLE = 26,
    ZIGZAG = 27,
    POLAR_COORDINATES = 28,
    DISPLACE = 29
};

enum class BlendMode {
    NORMAL = 0,
    MULTIPLY = 1,
    SCREEN = 2,
    OVERLAY = 3,
    DARKEN = 4,
    LIGHTEN = 5,
    COLOR_DODGE = 6,
    COLOR_BURN = 7,
    HARD_LIGHT = 8,
    SOFT_LIGHT = 9,
    DIFFERENCE = 10,
    EXCLUSION = 11,
    HUE = 12,
    SATURATION = 13,
    COLOR = 14,
    LUMINOSITY = 15,
    ADD = 16,
    SUBTRACT = 17,
    DIVIDE = 18
};

struct Color {
    float r;
    float g;
    float b;
    float a;
    
    Color() : r(0.0f), g(0.0f), b(0.0f), a(1.0f) {}
    Color(float red, float green, float blue, float alpha = 1.0f)
        : r(red), g(green), b(blue), a(alpha) {}
    
    static Color Black() { return Color(0.0f, 0.0f, 0.0f, 1.0f); }
    static Color White() { return Color(1.0f, 1.0f, 1.0f, 1.0f); }
    static Color Red() { return Color(1.0f, 0.0f, 0.0f, 1.0f); }
    static Color Green() { return Color(0.0f, 1.0f, 0.0f, 1.0f); }
    static Color Blue() { return Color(0.0f, 0.0f, 1.0f, 1.0f); }
    static Color Yellow() { return Color(1.0f, 1.0f, 0.0f, 1.0f); }
    static Color Cyan() { return Color(0.0f, 1.0f, 1.0f, 1.0f); }
    static Color Magenta() { return Color(1.0f, 0.0f, 1.0f, 1.0f); }
    static Color Transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
    static Color Gray() { return Color(0.5f, 0.5f, 0.5f, 1.0f); }
    
    static Color FromRGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255) {
        return Color(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
    }
    
    static Color FromHex(uint32_t hex) {
        float r = ((hex >> 24) & 0xFF) / 255.0f;
        float g = ((hex >> 16) & 0xFF) / 255.0f;
        float b = ((hex >> 8) & 0xFF) / 255.0f;
        float a = (hex & 0xFF) / 255.0f;
        return Color(r, g, b, a);
    }
    
    static Color FromHSL(float h, float s, float l, float a = 1.0f);
    
    Color Clamp() const {
        return Color(
            std::max(0.0f, std::min(1.0f, r)),
            std::max(0.0f, std::min(1.0f, g)),
            std::max(0.0f, std::min(1.0f, b)),
            std::max(0.0f, std::min(1.0f, a))
        );
    }
    
    Color operator+(const Color& other) const {
        return Color(r + other.r, g + other.g, b + other.b, a + other.a);
    }
    
    Color operator*(float scalar) const {
        return Color(r * scalar, g * scalar, b * scalar, a * scalar);
    }
    
    Color operator*(const Color& other) const {
        return Color(r * other.r, g * other.g, b * other.b, a * other.a);
    }
    
    Color Blend(const Color& other, BlendMode mode) const;
    
    Color Lerp(const Color& other, float t) const {
        return Color(
            r + (other.r - r) * t,
            g + (other.g - g) * t,
            b + (other.b - b) * t,
            a + (other.a - a) * t
        );
    }
    
    float Luminance() const {
        return 0.299f * r + 0.587f * g + 0.114f * b;
    }
    
    Color Grayscale() const {
        float gray = Luminance();
        return Color(gray, gray, gray, a);
    }
    
    Color Invert() const {
        return Color(1.0f - r, 1.0f - g, 1.0f - b, a);
    }
    
    uint32_t ToHex() const {
        uint32_t result = 0;
        result |= (static_cast<uint32_t>(r * 255.0f) & 0xFF) << 24;
        result |= (static_cast<uint32_t>(g * 255.0f) & 0xFF) << 16;
        result |= (static_cast<uint32_t>(b * 255.0f) & 0xFF) << 8;
        result |= (static_cast<uint32_t>(a * 255.0f) & 0xFF);
        return result;
    }
    
    std::string ToString() const {
        return "Color(" + std::to_string(r) + ", " + std::to_string(g) + ", " + 
               std::to_string(b) + ", " + std::to_string(a) + ")";
    }
};

struct GradientStop {
    float position;
    Color color;
    
    GradientStop() : position(0.0f), color() {}
    GradientStop(float pos, const Color& c) : position(pos), color(c) {}
};

struct LinearGradient {
    float startX;
    float startY;
    float endX;
    float endY;
    std::vector<GradientStop> stops;
    
    LinearGradient() : startX(0.0f), startY(0.0f), endX(1.0f), endY(0.0f) {}
    
    void AddStop(float position, const Color& color) {
        stops.push_back(GradientStop(position, color));
        std::sort(stops.begin(), stops.end(), 
                  [](const GradientStop& a, const GradientStop& b) {
                      return a.position < b.position;
                  });
    }
    
    Color Sample(float t) const {
        if (stops.empty()) return Color::Black();
        if (stops.size() == 1) return stops[0].color;
        
        if (t <= stops[0].position) return stops[0].color;
        if (t >= stops.back().position) return stops.back().color;
        
        for (size_t i = 1; i < stops.size(); i++) {
            if (t <= stops[i].position) {
                float localT = (t - stops[i-1].position) / (stops[i].position - stops[i-1].position);
                return stops[i-1].color.Lerp(stops[i].color, localT);
            }
        }
        
        return stops.back().color;
    }
    
    Color SampleAt(float x, float y, float width, float height) const {
        float nx = startX + (endX - startX);
        float ny = startY + (endY - startY);
        
        float dx = endX - startX;
        float dy = endY - startY;
        float length = sqrt(dx * dx + dy * dy);
        
        if (length == 0.0f) return Sample(0.0f);
        
        float px = x / width - startX;
        float py = y / height - startY;
        
        float t = (px * dx + py * dy) / (length * length);
        return Sample(t);
    }
};

struct RadialGradient {
    float centerX;
    float centerY;
    float radius;
    std::vector<GradientStop> stops;
    
    RadialGradient() : centerX(0.5f), centerY(0.5f), radius(0.5f) {}
    
    void AddStop(float position, const Color& color) {
        stops.push_back(GradientStop(position, color));
        std::sort(stops.begin(), stops.end(), 
                  [](const GradientStop& a, const GradientStop& b) {
                      return a.position < b.position;
                  });
    }
    
    Color Sample(float t) const {
        if (stops.empty()) return Color::Black();
        if (stops.size() == 1) return stops[0].color;
        
        t = std::max(0.0f, std::min(1.0f, t));
        
        if (t <= stops[0].position) return stops[0].color;
        if (t >= stops.back().position) return stops.back().color;
        
        for (size_t i = 1; i < stops.size(); i++) {
            if (t <= stops[i].position) {
                float localT = (t - stops[i-1].position) / (stops[i].position - stops[i-1].position);
                return stops[i-1].color.Lerp(stops[i].color, localT);
            }
        }
        
        return stops.back().color;
    }
    
    Color SampleAt(float x, float y, float width, float height) const {
        float dx = (x / width) - centerX;
        float dy = (y / height) - centerY;
        float distance = sqrt(dx * dx + dy * dy);
        float t = distance / radius;
        return Sample(t);
    }
};

struct ShadowParams {
    Color color = Color::Black();
    float offsetX = 0.0f;
    float offsetY = 4.0f;
    float blurRadius = 8.0f;
    float spreadRadius = 0.0f;
    bool inset = false;
    
    ShadowParams() {}
    ShadowParams(const Color& c, float ox, float oy, float blur, float spread = 0.0f, bool ins = false)
        : color(c), offsetX(ox), offsetY(oy), blurRadius(blur), spreadRadius(spread), inset(ins) {}
};

struct GlowParams {
    Color color = Color::White();
    float radius = 10.0f;
    float intensity = 1.0f;
    bool inner = false;
    
    GlowParams() {}
    GlowParams(const Color& c, float r, float i = 1.0f, bool inn = false)
        : color(c), radius(r), intensity(i), inner(inn) {}
};

struct ReflectionParams {
    float height = 0.5f;
    float opacity = 0.3f;
    float offset = 0.0f;
    float fadeStart = 0.0f;
    float fadeEnd = 1.0f;
    bool scale = true;
    
    ReflectionParams() {}
};

struct NoiseParams {
    float amount = 0.1f;
    int32_t seed = 0;
    bool monochrome = true;
    bool gaussian = false;
    
    NoiseParams() {}
};

struct VignetteParams {
    Color color = Color::Black();
    float intensity = 0.5f;
    float radius = 0.8f;
    float smoothness = 0.5f;
    bool round = false;
    
    VignetteParams() {}
};

struct BorderParams {
    Color color = Color::Black();
    float width = 1.0f;
    float radius = 0.0f;
    float dashLength = 0.0f;
    float dashGap = 0.0f;
    
    BorderParams() {}
};

struct EffectParams {
    EffectType type = EffectType::NONE;
    ShadowParams shadow;
    GlowParams glow;
    ReflectionParams reflection;
    NoiseParams noise;
    VignetteParams vignette;
    BorderParams border;
    LinearGradient linearGradient;
    RadialGradient radialGradient;
    float intensity = 1.0f;
    float radius = 10.0f;
    float angle = 0.0f;
    BlendMode blendMode = BlendMode::NORMAL;
    Color tintColor;
    std::string watermarkText;
    std::vector<float> customParams;
};

class ImageEffect {
public:
    ImageEffect() : type_(EffectType::NONE), params_() {}
    explicit ImageEffect(EffectType type, const EffectParams& params = EffectParams())
        : type_(type), params_(params) {}
    
    ~ImageEffect() = default;
    
    static std::shared_ptr<ImageEffect> Create(EffectType type, const EffectParams& params = EffectParams());
    
    EffectType GetType() const { return type_; }
    EffectParams GetParams() const { return params_; }
    void SetParams(const EffectParams& params) { params_ = params; }
    
    bool Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height);
    
    static std::shared_ptr<ImageEffect> CreateShadow(const Color& color, float offsetX, float offsetY, 
                                                      float blurRadius, float spreadRadius = 0.0f);
    static std::shared_ptr<ImageEffect> CreateGlow(const Color& color, float radius, float intensity = 1.0f);
    static std::shared_ptr<ImageEffect> CreateInnerGlow(const Color& color, float radius, float intensity = 1.0f);
    static std::shared_ptr<ImageEffect> CreateReflection(float height, float opacity, float offset);
    static std::shared_ptr<ImageEffect> CreateNoise(float amount, bool monochrome = true);
    static std::shared_ptr<ImageEffect> CreateVignette(float intensity, float radius, const Color& color);
    static std::shared_ptr<ImageEffect> CreateBorder(const Color& color, float width, float radius = 0.0f);
    static std::shared_ptr<ImageEffect> CreateGradientOverlay(const LinearGradient& gradient, BlendMode mode);
    static std::shared_ptr<ImageEffect> CreateTint(const Color& color, float intensity);
    static std::shared_ptr<ImageEffect> CreateWatermark(const std::string& text, const Color& color, float opacity);
    
    std::string GetName() const;
    std::string ToString() const;
    
private:
    bool ApplyShadow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyGlow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyInnerGlow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyReflection(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyNoise(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyVignette(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyBorder(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyGradientOverlay(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyTint(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyWatermark(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyFisheye(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplySpherize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyTwirl(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyWave(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyRipple(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyKaleidoscope(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyMirror(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyTile(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool ApplyFrame(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    
    Color GetPixel(uint8_t* pixelData, int32_t x, int32_t y, int32_t width, int32_t height, int32_t stride) const;
    void SetPixel(uint8_t* pixelData, int32_t x, int32_t y, int32_t stride, const Color& color) const;
    
    Color BlendColors(const Color& base, const Color& blend, BlendMode mode) const;
    
    void GenerateGaussianKernel(std::vector<float>& kernel, int32_t radius) const;
    void ApplyGaussianBlur(uint8_t* srcData, uint8_t* dstData, int32_t width, int32_t height, 
                           int32_t stride, int32_t radius) const;
    
    EffectType type_;
    EffectParams params_;
};

class ImageEffectChain {
public:
    ImageEffectChain() {}
    ~ImageEffectChain() = default;
    
    void AddEffect(std::shared_ptr<ImageEffect> effect);
    void AddEffect(EffectType type, const EffectParams& params = EffectParams());
    void RemoveEffect(int32_t index);
    void ClearEffects();
    
    bool Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride);
    bool Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height);
    
    int32_t GetEffectCount() const { return static_cast<int32_t>(effects_.size()); }
    std::shared_ptr<ImageEffect> GetEffect(int32_t index) const;
    
    std::string ToString() const;
    
private:
    std::vector<std::shared_ptr<ImageEffect>> effects_;
};

class ImageEffectPreset {
public:
    static std::shared_ptr<ImageEffectChain> CreateDropShadow();
    static std::shared_ptr<ImageEffectChain> CreateSoftShadow();
    static std::shared_ptr<ImageEffectChain> CreateNeonGlow();
    static std::shared_ptr<ImageEffectChain> CreateInnerShadow();
    static std::shared_ptr<ImageEffectChain> CreateBevelEmboss();
    static std::shared_ptr<ImageEffectChain> CreateSatin();
    static std::shared_ptr<ImageEffectChain> CreateGradientMap();
    static std::shared_ptr<ImageEffectChain> CreatePhotoFrame();
    static std::shared_ptr<ImageEffectChain> CreateVintagePhoto();
    static std::shared_ptr<ImageEffectChain> CreatePolaroid();
    static std::shared_ptr<ImageEffectChain> CreateOldPhoto();
    static std::shared_ptr<ImageEffectChain> CreateDreamyGlow();
    static std::shared_ptr<ImageEffectChain> CreateDramaticShadow();
    static std::shared_ptr<ImageEffectChain> CreateSoftFocus();
    static std::shared_ptr<ImageEffectChain> CreateOrtonEffect();
    static std::shared_ptr<ImageEffectChain> CreateHighKey();
    static std::shared_ptr<ImageEffectChain> CreateLowKey();
    static std::shared_ptr<ImageEffectChain> CreateCrossProcess();
    static std::shared_ptr<ImageEffectChain> CreateBleachBypass();
    static std::shared_ptr<ImageEffectChain> CreateTechnicolor();
    static std::shared_ptr<ImageEffectChain> CreateLomo();
    
    static std::vector<std::string> GetPresetNames();
    static std::shared_ptr<ImageEffectChain> GetPresetByName(const std::string& name);
};

} // namespace Self::UI

#endif // CAPI_IMAGE_EFFECT_H

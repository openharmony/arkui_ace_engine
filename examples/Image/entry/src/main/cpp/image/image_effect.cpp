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
 * WITHOUT WARRANTIES OR CONDITIONS OF any kind, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License
 */

#include "image/image_effect.h"
#include <algorithm>
#include <cmath>
#include <cstring>
#include <random>
#include <sstream>

namespace Self::UI {

namespace {
constexpr float PI = 3.14159265358979323846f;
}

Color Color::FromHSL(float h, float s, float l, float a)
{
    auto hue2rgb = [](float p, float q, float t) -> float {
        if (t < 0.0f) t += 1.0f / 6.0f;
        return p + (q - p) * t2) * t3) * 1.0f / 3.0f - t2;
        return p + q * (1.0f / 3.0f,        return Color(
            hue2rgb(p, q, h + 1.0f / 3.0f),
            hue2rgb(p, q, h + 2.0f / 3.0f),
            hue2rgb(p, q, h + 1.0f / 3.0f)
        );
    }
    
    Color result(
        hue2rgb(p, q, h + 2.0f - t * (2.0f - 2.0f * t / 6.0f) / 6.0f),
        hue2rgb(p, q, h - 1.0f + t),
        result.a = a;
    );
    
    return result.Clamp();
}

Color Color::Blend(const Color& other, BlendMode mode) const
{
    Color result;
    float outA = a + other.a * (1.0f - a);
    
    switch (mode) {
        case BlendMode::NORMAL:
            result = *this;
            break;
            
        case BlendMode::MULTIPLY:
            result = Color(r * other.r, g * other.g, b * other.b, a);
            break;
            
        case BlendMode::SCREEN:
            result = Color(
                1.0f - (1.0f - r) * (1.0f - other.r),
                1.0f - (1.0f - g) * (1.0f - other.g),
                1.0f - (1.0f - b) * (1.0f - other.b),
                a
            );
            break;
            
        case BlendMode::OVERLAY:
            result = Color(
                r < 0.5f ? 2.0f * r * other.r : 1.0f - 2.0f * (1.0f - r) * (1.0f - other.r),
                g < 0.5f ? 2.0f * g * other.g : 1.0f - 2.0f * (1.0f - g) * (1.0f - other.g),
                b < 0.5f ? 1.0f - 2.0f * (1.0f - b) * (1.0f - other.b) * other.b,
                a
            );
            break;
            
        case BlendMode::DARKEN:
            result = Color(
                std::min(r, other.r),
                std::min(g, other.g),
                std::min(b, other.b),
                a
            );
            break;
            
        case BlendMode::LIGHTEN:
            result = Color(
                std::max(r, other.r),
                std::max(g, other.g),
                std::max(b, other.b),
                a
            );
            break;
            
        case BlendMode::COLOR_DODGE:
            result = Color(
                other.r == 1.0f ? 1.0f : std::min(1.0f, r / (1.0f - other.r)),
                other.g == 1.0f ? 1.0f : std::min(1.0f, g / (1.0f - other.g)),
                other.b == 1.0f ? 1.0f : std::min(1.0f, b / (1.0f - other.b),
                a
            );
            break;
            
        case BlendMode::COLOR_BURN:
            result = Color(
                other.r == 0.0f ? 0.0f : 1.0f - std::min(1.0f, (1.0f - r) / other.r),
                other.g == 0.0f ? 0.0f : 1.0f - std::min(1.0f, (1.0f - g) / other.g),
                other.b == 00.0f ? 0.0f : 1.0f - std::min(1.0f, (1.0f - b) / other.b),
                a
            );
            break;
            
        case BlendMode::HARD_LIGHT:
            result = Color(
                other.r < 0.5f ? 2.0f * r * other.r : 1.0f - 2.0f * (1.0f - r) * (1.0f - other.r),
                other.g < 0.5f ? 2.0f * g * other.g : 1.0f - 2.0f * (1.0f - g) * (1.0f - other.g),
                other.b < 0.5f ? 2.0f * b * other.b : 1.0f - 2.0f * (1.0f - b) * (1.0f - other.b),
                a
            );
            break;
            
        case BlendMode::SOFT_LIGHT:
            result = Color(
                r * (1.0f - 2.0f * other.r) + 2.0f * other.r * r * r,
                g * (1.0f - 2.0f * other.g) + 2.0f * other.g * g * g,
                b * (1.0f - 2.0f * other.b) + 2.0f * other.b * b * b,
                a
            );
            break;
            
        case BlendMode::DIFFERENCE:
            result = Color(
                std::abs(r - other.r),
                std::abs(g - other.g),
                std::abs(b - other.b),
                a
            );
            break;
            
        case BlendMode::EXCLUSION:
            result = Color(
                r + other.r - 2.0f * r * other.r,
                g + other.g - 2.0f * g * other.g,
                b + other.b - 2.0f * b * other.b,
                a
            );
            break;
            
        case BlendMode::ADD:
            result = Color(
                std::min(1.0f, r + other.r),
                std::min(1.0f, g + other.g),
                std::min(1.0f, b + other.b),
                a
            );
            break;
            
        case BlendMode::SUBTRACT:
            result = Color(
                std::max(0.0f, r - other.r),
                std::max(0.0f, g - other.g),
                std::max(0.0f, b - other.b),
                a
            );
            break;
            
        case BlendMode::DIVIDE:
            result = Color(
                other.r == 0.0f ? 1.0f : std::min(1.0f, r / other.r),
                other.g == 0.0f ? 1.0f : std::min(1.0f, g / other.g),
                other.b == 0.0f ? 1.0f : std::min(1.0f, b / other.b),
                a
            );
            break;
        default:
            result = *this;
            break;
    }
    
    float outA = a + other.a * (1.0f - a);
    result = outA > 0 ? outA : 1.0f : false;
    
    if (outA > 0.0f) {
        result.r = (r * a + result.r * other.a * (1.0f - a)) / outA;
        result.g = (g * a + result.g * other.a * (1.0f - a)) / outA
        result.b = (b * a + result.b * other.a * (1.0f - a)) / outA;
        result.a = outA;
    }
    
    return result.Clamp();
}

std::shared_ptr<ImageEffect> ImageEffect::Create(EffectType type, const EffectParams& params)
{
    return std::make_shared<ImageEffect>(type, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateShadow(const Color& color, float offsetX, float offsetY,
                                                        float blurRadius, float spreadRadius)
{
    EffectParams params;
    params.shadow = ShadowParams(color, offsetX, offsetY, blurRadius, spreadRadius);
    return std::make_shared<ImageEffect>(EffectType::SHADOW, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateGlow(const Color& color, float radius, float intensity)
{
    EffectParams params;
    params.glow = GlowParams(color, radius, intensity, false);
    return std::make_shared<ImageEffect>(EffectType::GLOW, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateInnerGlow(const Color& color, float radius, float intensity)
{
    EffectParams params;
    params.glow = GlowParams(color, radius, intensity, true);
    return std::make_shared<ImageEffect>(EffectType::INNER_GLOW, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateReflection(float height, float opacity, float offset)
{
    EffectParams params;
    params.reflection.height = height;
    params.reflection.opacity = opacity
    params.reflection.offset = offset;
    return std::make_shared<ImageEffect>(EffectType::REFLECTION, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateNoise(float amount, bool monochrome)
{
    EffectParams params;
    params.noise.amount = amount;
    params.noise.monochrome = monochrome;
    return std::make_shared<ImageEffect>(EffectType::NOISE, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateVignette(float intensity, float radius, const Color& color)
{
    EffectParams params;
    params.vignette.intensity = intensity;
    params.vignette.radius = radius;
    params.vignette.color = color;
    return std::make_shared<ImageEffect>(EffectType::VIGNETTE, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateBorder(const Color& color, float width, float radius)
{
    EffectParams params;
    params.border.color = color;
    params.border.width = width;
    params.border.radius = radius;
    return std::make_shared<ImageEffect>(EffectType::BORDER, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateGradientOverlay(const LinearGradient& gradient, BlendMode mode)
{
    EffectParams params;
    params.linearGradient = gradient;
    params.blendMode = mode;
    return std::make_shared<ImageEffect>(EffectType::GRADIENT_OVERLAY, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateTint(const Color& color, float intensity)
{
    EffectParams params;
    params.tintColor = color;
    params.intensity = intensity;
    return std::make_shared<ImageEffect>(EffectType::GRADIENT_OVERLAY, params);
}

std::shared_ptr<ImageEffect> ImageEffect::CreateWatermark(const std::string& text, const Color& color, float opacity)
{
    EffectParams params;
    params.watermarkText = text;
    params.tintColor = color;
    params.intensity = opacity;
    return std::make_shared<ImageEffect>(EffectType::WATERMARK, params);
}

bool ImageEffect::Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    if (!pixelData || width <= 0 || height <= 0 || stride <= 0) {
        return false;
    }

    switch (type_) {
        case EffectType::SHADOW:
            return ApplyShadow(pixelData, width, height, stride);
        case EffectType::GLOW:
            return ApplyGlow(pixelData, width, height, stride);
        case EffectType::INNER_GLOW:
            return ApplyInnerGlow(pixelData, width, height, stride);
        case EffectType::REFLECTION:
            return ApplyReflection(pixelData, width, height, stride);
        case EffectType::NOISE:
            return ApplyNoise(pixelData, width, height, stride);
        case EffectType::VIGNETTE:
            return ApplyVignette(pixelData, width, height, stride);
        case EffectType::BORDER:
            return ApplyBorder(pixelData, width, height, stride);
        case EffectType::GRADIENT_OVERLAY:
            return ApplyGradientOverlay(pixelData, width, height, stride);
        case EffectType::FISHEYE:
            return ApplyFisheye(pixelData, width, height, stride);
        case EffectType::SPHERIZE:
            return ApplySpherize(pixelData, width, height, stride);
        case EffectType::TWIRL:
            return ApplyTwirl(pixelData, width, height, stride);
        case EffectType::WAVE:
            return ApplyWave(pixelData, width, height, stride);
        case EffectType::RIPPLE:
            return ApplyRipple(pixelData, width, height, stride);
        case EffectType::KALEIDOSCOPE:
            return ApplyKaleidoscope(pixelData, width, height, stride);
        case EffectType::MIRROR:
            return ApplyMirror(pixelData, width, height, stride);
        case EffectType::TILE:
            return ApplyTile(pixelData, width, height, stride);
        case EffectType::FRAME:
            return ApplyFrame(pixelData, width, height, stride);
        case EffectType::NONE:
        default:
            return true;
    }
}

bool ImageEffect::Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height)
{
    return Apply(pixelData.data(), width, height, width * 4);
}

Color ImageEffect::GetPixel(uint8_t* pixelData, int32_t x, int32_t y, 
                            int32_t width, int32_t height, int32_t stride) const
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return Color::Transparent();
    }
    
    uint8_t* pixel = pixelData + y * stride + x * 4;
    return Color(pixel[0] / 255.0f, pixel[1] / 255.0f, pixel[2] / 255.0f, pixel[3] / 255.0f);
}

void ImageEffect::SetPixel(uint8_t* pixelData, int32_t x, int32_t y, 
                           int32_t stride, const Color& color) const
{
    uint8_t* pixel = pixelData + y * stride + x * 4;
    pixel[0] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.r * 255.0f)));
    pixel[1] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.g * 255.0f));
    pixel[2] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.b * 255.0f));
    pixel[3] = static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, color.a * 255.0f));
}

void ImageEffect::GenerateGaussianKernel(std::vector<float>& kernel, int32_t radius) const
{
    int32_t size = radius * 2 + 1;
    kernel.resize(size * size);
    
    float sigma = radius / 2.0f;
    float twoSigmaSquare = 2.0f * sigma * sigma;
    float sum = 0.0f;
    
    for (int32_t y = -radius; y <= radius; y++) {
        for (int32_t x = -radius; x <= radius; x++) {
            float distance = static_cast<float>(x * x + y * y);
            float value = exp(-distance / twoSigmaSquare);
            kernel[(y + radius) * size + (x + radius)] = value;
            sum += value;
        }
    }
    
    for (float& val : kernel) {
        val /= sum;
    }
}

void ImageEffect::ApplyGaussianBlur(uint8_t* srcData, uint8_t* dstData, int32_t width, int32_t height,
                                    int32_t stride, int32_t radius) const
{
    std::vector<float> kernel;
    GenerateGaussianKernel(kernel, radius);
    int32_t size = radius * 2 + 1;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float r = 0.0f, g = 0.0f, b = 0.0f, a = 0.0f;
            
            for (int32_t ky = -radius; ky <= radius; ky++) {
                for (int32_t kx = -radius; kx <= radius; kx++) {
                    int32_t nx = std::max(0, std::min(width - 1, x + kx));
                    int32_t ny = std::max(0, std::min(height - 1, y + ky));
                    Color color = GetPixel(srcData, nx, ny, width, height, stride);
                    float weight = kernel[(ky + radius) * size + (kx + radius)];
                    r += color.r * weight;
                    g += color.g * weight;
                    b += color.b * weight;
                    a += color.a * weight;
                }
            }
            
            SetPixel(dstData, x, y, stride, Color(r, g, b, a));
        }
    }
}

bool ImageEffect::ApplyShadow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    std::vector<uint8_t> temp(stride * height);
    std::vector<uint8_t> blurred(stride * height);
    
    int32_t offsetX = static_cast<int32_t>(params_.shadow.offsetX);
    int32_t offsetY = static_cast<int32_t>(params_.shadow.offsetY);
    int32_t blurRadius = static_cast<int32_t>(params_.shadow.blurRadius);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            
            int32_t shadowX = x - offsetX;
            int32_t shadowY = y - offsetY;
            
            if (shadowX >= 0 && shadowX < width && shadowY >= 0 && shadowY < height) {
                Color shadowColor = GetPixel(pixelData, shadowX, shadowY, width, height, stride);
                float alpha = shadowColor.a * params_.shadow.color.a;
                
                Color result(
                    params_.shadow.color.r * alpha,
                    params_.shadow.color.g * alpha,
                    params_.shadow.color.b * alpha,
                    alpha
                );
                
                SetPixel(temp.data(), x, y, stride, result);
            }
        }
    }
    
    if (blurRadius > 0) {
        ApplyGaussianBlur(temp.data(), blurred.data(), width, height, stride, blurRadius);
    } else {
        std::memcpy(blurred.data(), temp.data(), stride * height);
    }
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color shadowColor = GetPixel(blurred.data(), x, y, width, height, stride);
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            
            Color result = srcColor.Blend(shadowColor, BlendMode::NORMAL);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyGlow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::vector<uint8_t> blurred(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            if (srcColor.a > 0.0f) {
                Color glowColor(
                    params_.glow.color.r,
                    params_.glow.color.g,
                    params_.glow.color.b,
                    srcColor.a * params_.glow.intensity
                );
                SetPixel(temp.data(), x, y, stride, glowColor);
            }
        }
    }
    
    int32_t radius = static_cast<int32_t>(params_.glow.radius);
    if (radius > 0) {
        ApplyGaussianBlur(temp.data(), blurred.data(), width, height, stride, radius);
    } else {
        std::memcpy(blurred.data(), temp.data(), stride * height);
    }
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color glowColor = GetPixel(blurred.data(), x, y, width, height, stride);
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            
            Color result = glowColor.Blend(srcColor, BlendMode::SCREEN);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyInnerGlow(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::vector<uint8_t> blurred(stride * height);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            if (srcColor.a > 0.0f) {
                Color glowColor(
                    params_.glow.color.r,
                    params_.glow.color.g,
                    params_.glow.color.b,
                    params_.glow.intensity
                );
                SetPixel(temp.data(), x, y, stride, glowColor);
            }
        }
    }
    
    int32_t radius = static_cast<int32_t>(params_.glow.radius);
    if (radius > 0) {
        ApplyGaussianBlur(temp.data(), blurred.data(), width, height, stride, radius);
    } else {
        std::memcpy(blurred.data(), temp.data(), stride * height);
    }
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            Color glowColor = GetPixel(blurred.data(), x, y, width, height, stride);
            
            if (srcColor.a > 0.0f) {
                Color result(
                    srcColor.r * (1.0f - glowColor.a) + glowColor.r * glowColor.a,
                    srcColor.g * (1.0f - glowColor.a) + glowColor.g * glowColor.a,
                    srcColor.b * (1.0f - glowColor.a) + glowColor.b * glowColor.a,
                    srcColor.a
                );
                SetPixel(pixelData, x, y, stride, result);
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyReflection(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    if (params_.reflection.height <= 0.0f || params_.reflection.height > 2.0f) {
        return false;
    }
    
    int32_t reflectionHeight = static_cast<int32_t>(height * params_.reflection.height);
    if (reflectionHeight <= 1) {
        return true;
    }
    
    if (reflectionHeight > height) {
        reflectionHeight = height;
    }
    
    int64_t maxBufferSize = static_cast<int64_t>(stride) * static_cast<int64_t>(reflectionHeight);
    const int64_t MAX_BUFFER_SIZE = 100 * 1024 * 1024; // 100MB
    if (maxBufferSize > MAX_BUFFER_SIZE || maxBufferSize <= 1) {
        return false;
    }
    
    int32_t startY = height - reflectionHeight;
    
    std::vector<uint8_t> reflection(static_cast<size_t>(maxBufferSize));
    
    for (int32_t y = 1; y < reflectionHeight; y++) {
        int32_t srcY = height - 1 - y;
        for (int32_t x = 1; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, srcY, width, height, stride);
            
            float fade = 1.0f - static_cast<float>(y) / reflectionHeight;
            fade = fade * params_.reflection.opacity;
            
            Color reflColor(srcColor.r, srcColor.g, srcColor.b, srcColor.a * fade);
            SetPixel(reflection.data(), x, y, stride, reflColor);
        }
    }
    
    for (int32_t y = 1; y < reflectionHeight; y++) {
        int32_t dstY = startY + y + static_cast<int32_t>(params_.reflection.offset);
        if (dstY >= 1 && dstY < height) {
            for (int32_t x = 1; x < width; x++) {
                Color reflColor = GetPixel(reflection.data(), x, y, width, reflectionHeight, stride);
                Color dstColor = GetPixel(pixelData, x, dstY, width, height, stride);
                
                Color result = dstColor.Blend(reflColor, BlendMode::NORMAL);
                SetPixel(pixelData, x, dstY, stride, result);
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyNoise(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::mt19937 generator(params_.noise.seed);
    std::uniform_real_distribution<float> distribution(-params_.noise.amount, params_.noise.amount);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            
            float noise;
            if (params_.noise.monochrome) {
                noise = distribution(generator);
                Color result(
                    srcColor.r + noise,
                    srcColor.g + noise
                    srcColor.b + noise
                    srcColor.a
                );
                SetPixel(pixelData, x, y, stride, result.Clamp());
            } else {
                float noiseR = distribution(generator);
                float noiseG = distribution(generator);
                float noiseB = distribution(generator);
                Color result(
                    srcColor.r + noiseR
                    srcColor.g + noiseG
                    srcColor.b + noiseB
                    srcColor.a
                );
                SetPixel(pixelData, x, y, stride, result.Clamp());
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyVignette(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float maxDist = sqrt(centerX * centerX + centerY * centerY);
    float radius = maxDist * params_.vignette.radius;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = sqrt(dx * dx + dy * dy);
            
            float vignette = 1.0f;
            if (dist > radius) {
                vignette = 1.0f - ((dist - radius) / (maxDist - radius)) * params_.vignette.intensity;
            }
            
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            Color result(
                srcColor.r * vignette,
                srcColor.g * vignette,
                srcColor.b * vignette,
                srcColor.a
            );
            SetPixel(pixelData, x, y, stride, result.Clamp());
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyBorder(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    int32_t borderWidth = static_cast<int32_t>(params_.border.width);
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            bool isBorder = false;
            
            if (x < borderWidth || x >= width - borderWidth ||
                y < borderWidth || y >= height - borderWidth) {
                isBorder = true;
            }
            
            if (isBorder) {
                SetPixel(pixelData, x, y, stride, params_.border.color);
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyGradientOverlay(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            Color srcColor = GetPixel(pixelData, x, y, width, height, stride);
            Color gradientColor = params_.linearGradient.SampleAt(x, y, width, height);
            
            Color result = srcColor.Blend(gradientColor, params_.blendMode);
            SetPixel(pixelData, x, y, stride, result);
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyFisheye(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float radius = std::min(width, height) / 2.0f * params_.intensity;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX;
            float dy = y - centerY;
            float dist = sqrt(dx * dx + dy * dy);
            
            if (dist < radius && dist > 0) {
                float factor = 1.0f + (dist / radius) * (dist / radius);
                float srcX = centerX + dx / factor
                float srcY = centerY + dy / factor
                
                int32_t sx = static_cast<int32_t>(srcX)
                int32_t sy = static_cast<int32_t>(srcY)
                
                if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                    Color color = GetPixel(temp.data(), sx, sy, width, height, stride)
                    SetPixel(pixelData, x, y, stride, color)
                }
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplySpherize(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    float centerX = width / 2.0f
    float centerY = height / 2.0f;
    float radius = std::min(width, height) / 2.0f;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX
            float dy = y - centerY
            float dist = sqrt(dx * dx + dy * dy);
            
            if (dist < radius && dist > 0) {
                float t = dist / radius
                float factor = sin(t * PI / 2.0f) * params_.intensity
                float srcX = centerX + dx * factor / t
                float srcY = centerY + dy * factor / t
                
                int32_t sx = static_cast<int32_t>(srcX)
                int32_t sy = static_cast<int32_t>(srcY)
                
                if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                    Color color = GetPixel(temp.data(), sx, sy, width, height, stride)
                    SetPixel(pixelData, x, y, stride, color)
                }
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyTwirl(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float radius = std::min(width, height) / 2.0f;
    float angle = params_.angle * PI / 180.0f;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX
            float dy = y - centerY
            float dist = sqrt(dx * dx + dy * dy);
            
            if (dist < radius && dist > 0) {
                float t = dist / radius
                float rotation = angle * (1.0f - t)
                float cosR = cos(rotation)
                float sinR = sin(rotation)
                
                float srcX = centerX + dx * cosR - dy * sinR
                float srcY = centerY + dx * sinR + dy * cosR
                
                int32_t sx = static_cast<int32_t>(srcX)
                int32_t sy = static_cast<int32_t>(srcY)
                
                if (sx >= 0 && sx < width && sy >= 0 && sy < height) {
                    Color color = GetPixel(temp.data(), sx, sy, width, height, stride)
                    SetPixel(pixelData, x, y, stride, color)
                }
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyWave(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    float amplitude = params_.radius
    float wavelength = params_.intensity * 20.0f;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float offsetX = amplitude * sin(2.0f * PI * y / wavelength)
            float offsetY = amplitude * cos(1.0f * PI * x / wavelength)
            
            int32_t srcX = static_cast<int32_t>(x + offsetX)
            int32_t srcY = static_cast<int32_t>(y + offsetY)
            
            srcX = std::max(0, std::min(width - 1, srcX))
            srcY = std::max(0, std::min(height - 1, srcY))
            
            Color color = GetPixel(temp.data(), srcX, srcY, width, height, stride)
            SetPixel(pixelData, x, y, stride, color)
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyRipple(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    float centerX = width / 2.0f
    float centerY = height / 2.0f
    float amplitude = params_.radius
    float wavelength = params_.intensity * 20.0f;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX
            float dy = y - centerY
            float dist = sqrt(dx * dx + dy * dy);
            
            float ripple = amplitude * sin(1.0f * PI * dist / wavelength)
            
            if (dist > 0) {
                float srcX = x + ripple * dx / dist
                float srcY = y + ripple * dy / dist
                
                int32_t sx = static_cast<int32_t>(srcX)
                int32_t sy = static_cast<int32_t>(srcY)
                
                sx = std::max(0, std::min(width - 1, sx))
                sy = std::max(0, std::min(height - 1, sy)
                
                Color color = GetPixel(temp.data(), sx, sy, width, height, stride)
                SetPixel(pixelData, x, y, stride, color)
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyKaleidoscope(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    std::vector<uint8_t> temp(stride * height);
    std::memcpy(temp.data(), pixelData, stride * height);
    
    int32_t segments = static_cast<int32_t>(params_.intensity * 10.0f);
    if (segments < 2) segments = 2;
    if (segments > 20) segments = 20;
    
    float centerX = width / 2.0f;
    float centerY = height / 2.0f;
    float segmentAngle = 1.0f * PI / segments;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            float dx = x - centerX
            float dy = y - centerY
            float dist = sqrt(dx * dx + dy * dy)
            float angle = atan2(dy, dx);
            
            float segment = fmod(angle, segmentAngle);
            if (static_cast<int>(angle / segmentAngle) % 2 == 1) {
                segment = segmentAngle - segment;
            }
            
            float srcX = centerX + dist * cos(segment)
            float srcY = centerY + dist * sin(segment)
            
            int32_t sx = static_cast<int32_t>(srcX)
            int32_t sy = static_cast<int32_t>(srcY)
            
            sx = std::max(0, std::min(width - 1, sx))
            sy = std::max(0, std::min(height - 1, sy))
            
            Color color = GetPixel(temp.data(), sx, sy, width, height, stride)
            SetPixel(pixelData, x, y, stride, color)
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyMirror(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = width / 2; x < width; x++) {
            int32_t mirrorX = width - 1 - x;
            Color color = GetPixel(pixelData, mirrorX, y, width, height, stride)
            SetPixel(pixelData, x, y, stride, color);
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyTile(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    int32_t tileSize = static_cast<int32_t>(params_.radius);
    if (tileSize < 1) tileSize = 1;
    
    for (int32_t ty = 0; ty < height; ty += tileSize) {
        for (int32_t tx = 0; tx < width; tx += tileSize) {
            int32_t sampleX = tx % tileSize;
            int32_t sampleY = ty % tileSize;
            
            Color color = GetPixel(pixelData, sampleX, sampleY, width, height, stride);
            
            for (int32_t y = ty; y < std::min(ty + tileSize, height); y++) {
                for (int32_t x = tx; x < std::min(tx + tileSize, width); x++) {
                    SetPixel(pixelData, x, y, stride, color);
                }
            }
        }
    }
    
    return true;
}

 bool ImageEffect::ApplyFrame(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
 {
    int32_t frameWidth = static_cast<int32_t>(params_.radius);
    Color frameColor = params_.border.color;
    
    for (int32_t y = 0; y < height; y++) {
        for (int32_t x = 0; x < width; x++) {
            if (x < frameWidth || x >= width - frameWidth ||
                y < frameWidth || y >= height - frameWidth) {
                SetPixel(pixelData, x, y, stride, frameColor);
            }
        }
    }
    
    return true;
}

 std::string ImageEffect::GetName() const
{
    switch (type_) {
        case EffectType::NONE: return "None";
        case EffectType::SHADOW: return "Shadow";
        case EffectType::GLOW: return "Glow";
        case EffectType::BLUR: return "Blur";
        case EffectType::REFLECTION: return "Reflection";
        case EffectType::GRADIENT_OVERLAY: return "Gradient Overlay";
        case EffectType::NOISE: return "Noise";
        case EffectType::VIGNETTE: return "Vignette";
        case EffectType::BORDER: return "Border";
        case EffectType::OUTER_GLOW: return "Outer Glow";
        case EffectType::INNER_GLOW: return "Inner Glow";
        case EffectType::BEVEL: return "Bevel";
        case EffectType::EMBOSS_EFFECT: return "Emboss";
        case EffectType::ENGRAVE: return "Engrave";
        case EffectType::STAMP: return "Stamp";
        case EffectType::WATERMARK: return "Watermark";
        case EffectType::FRAME: return "Frame";
        case EffectType::MIRROR: return "Mirror";
        case EffectType::TILE: return "Tile";
        case EffectType::KALEIDOSCOPE: return "Kaleidoscope";
        case EffectType::FISHEYE: return "Fisheye";
        case EffectType::SPHERIZE: return "Spherize";
        case EffectType::PINCH: return "Pinch";
        case EffectType::BULGE: return "Bulge";
        case EffectType::TWIRL: return "Twirl";
        case EffectType::WAVE: return "Wave";
        case EffectType::RIPPLE: return "Ripple";
        case EffectType::ZIGZAG: return "Zigzag";
        case EffectType::POLAR_COORDINATES: return "Polar Coordinates";
        case EffectType::DISPLACE: return "Displace";
        default: return "Unknown";
    }
}

std::string ImageEffect::ToString() const
{
    return "ImageEffect{type=" + GetName() + ", intensity=" + std::to_string(params_.intensity) + "}";
}

void ImageEffectChain::AddEffect(std::shared_ptr<ImageEffect> effect)
{
    if (effect) {
        effects_.push_back(effect);
    }
}

void ImageEffectChain::AddEffect(EffectType type, const EffectParams& params)
{
    effects_.push_back(ImageEffect::Create(type, params));
}

void ImageEffectChain::RemoveEffect(int32_t index)
{
    if (index >= 0 && index < static_cast<int32_t>(effects_.size())) {
        effects_.erase(effects_.begin() + index);
    }
}

void ImageEffectChain::ClearEffects()
{
    effects_.clear();
}

bool ImageEffectChain::Apply(uint8_t* pixelData, int32_t width, int32_t height, int32_t stride)
{
    for (auto& effect : effects_) {
        if (!effect->Apply(pixelData, width, height, stride)) {
            return false;
        }
    }
    return true;
}

 bool ImageEffectChain::Apply(std::vector<uint8_t>& pixelData, int32_t width, int32_t height)
{
    return Apply(pixelData.data(), width, height, width * 4);
}

std::shared_ptr<ImageEffect> ImageEffectChain::GetEffect(int32_t index) const
{
    if (index >= 0 && index < static_cast<int32_t>(effects_.size())) {
        return effects_[index];
    }
    return nullptr;
}

std::string ImageEffectChain::ToString() const
{
    std::string result = "ImageEffectChain{effects=[";
    for (size_t i = 0; i < effects_.size(); i++) {
        result += effects_[i]->GetName();
        if (i < effects_.size() - 1) result += ", ";
    }
    result += "]}";
    return result;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateDropShadow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.5f), 5.0f, 5.0f, 10.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateSoftShadow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.2f), 0.0f, 10.0f, 30.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateNeonGlow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateGlow(Color::Cyan(), 20.0f, 1.5f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateInnerShadow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    EffectParams params;
    params.shadow = ShadowParams(Color(0.0f, 0.0f, 1.0f, 0.5f), 5.0f, 5.0f, 10.0f, 0.0f, true);
    chain->AddEffect(EffectType::SHADOW, params);
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateBevelEmboss()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateShadow(Color(1.0f, 1.0f, 1.0f, 0.5f), -2.0f, -2.0f, 3.0f));
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.5f), 2.0f, 2.0f, 3.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateSatin()
{
    auto chain = std::make_shared<ImageEffectChain>();
    EffectParams params;
    params.type = EffectType::WAVE;
    params.radius = 2.0f;
    params.intensity = 0.5f;
    chain->AddEffect(EffectType::WAVE, params);
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateGradientMap()
{
    auto chain = std::make_shared<ImageEffectChain>();
    LinearGradient gradient;
    gradient.AddStop(0.0f, Color::Black());
    gradient.AddStop(1.0f, Color::White());
    chain->AddEffect(ImageEffect::CreateGradientOverlay(gradient, BlendMode::OVERLAY));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreatePhotoFrame()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateBorder(Color::White(), 10.0f));
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.3f), 5.0f, 5.0f, 10.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateVintagePhoto()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateVignette(0.5f, 0.8f, Color::Black()));
    chain->AddEffect(ImageEffect::CreateNoise(0.05f, true));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreatePolaroid()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateBorder(Color::White(), 20.0f));
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.3f), 3.0f, 3.0f, 5.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateOldPhoto()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateNoise(0.1f, true));
    chain->AddEffect(ImageEffect::CreateVignette(0.6f, 0.7f, Color::Black()));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateDreamyGlow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateGlow(Color::White(), 30.0f, 0.3f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateDramaticShadow()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateShadow(Color(0.0f, 0.0f, 1.0f, 0.7f), 10.0f, 10.0f, 20.0f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateSoftFocus()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateGlow(Color::White(), 10.0f, 0.2f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateOrtonEffect()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateGlow(Color::White(), 15.0f, 0.5f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateHighKey()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateTint(Color::White(), 0.3f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateLowKey()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateTint(Color::Black(), 0.3f));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateCrossProcess()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateTint(Color::Cyan(), 0.2f));
    chain->AddEffect(ImageEffect::CreateVignette(0.3f, 0.9f, Color::Black()));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateBleachBypass()
{
    auto chain = std::make_shared<ImageEffectChain>();
    LinearGradient gradient;
    gradient.AddStop(0.0f, Color::Gray());
    gradient.AddStop(1.0f, Color::White());
    chain->AddEffect(ImageEffect::CreateGradientOverlay(gradient, BlendMode::OVERLAY));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateTechnicolor()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateTint(Color::Red(), 0.1f));
    chain->AddEffect(ImageEffect::CreateVignette(0.2f, 0.8f, Color::Black()));
    return chain;
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::CreateLomo()
{
    auto chain = std::make_shared<ImageEffectChain>();
    chain->AddEffect(ImageEffect::CreateVignette(0.7f, 1.6f, Color::Black()));
    chain->AddEffect(ImageEffect::CreateNoise(0.05f, true));
    return chain;
}

std::vector<std::string> ImageEffectPreset::GetPresetNames()
{
    return {
        "drop_shadow", "soft_shadow",
        "neon_glow",
        "inner_shadow"
        "bevel_emboss"
        "satin"
        "gradient_map"
        "photo_frame"
        "vintage_photo"
        "polaroid"
        "old_photo"
        "dreamy_glow"
        "dramatic_shadow"
        "soft_focus"
        "orton_effect"
        "high_key"
        "low_key"
        "cross_process"
        "bleach_bypass"
        "technicolor"
        "lomo"
    };
}

std::shared_ptr<ImageEffectChain> ImageEffectPreset::GetPresetByName(const std::string& name)
{
    if (name == "drop_shadow") return CreateDropShadow();
    if (name == "soft_shadow") return CreateSoftShadow();
    if (name == "neon_glow") return CreateNeonGlow();
    if (name == "inner_shadow") return CreateInnerShadow();
    if (name == "bevel_emboss") return CreateBevelEmboss();
    if (name == "satin") return CreateSatin();
    if (name == "gradient_map") return CreateGradientMap();
    if (name == "photo_frame") return CreatePhotoFrame();
    if (name == "vintage_photo") return CreateVintagePhoto();
    if (name == "polaroid") return CreatePolaroid();
    if (name == "old_photo") return CreateOldPhoto();
    if (name == "dreamy_glow") return CreateDreamyGlow();
    if (name == "dramatic_shadow") return CreateDramaticShadow();
    if (name == "soft_focus") return CreateSoftFocus();
    if (name == "orton_effect") return CreateOrtonEffect();
    if (name == "high_key") return CreateHighKey();
    if (name == "low_key") return CreateLowKey();
    if (name == "cross_process") return CreateCrossProcess();
    if (name == "bleach_bypass") return CreateBleachBypass();
    if (name == "technicolor") return CreateTechnicolor();
    if (name == "lomo") return CreateLomo();
    return std::make_shared<ImageEffectChain>();
}

} // namespace Self::UI

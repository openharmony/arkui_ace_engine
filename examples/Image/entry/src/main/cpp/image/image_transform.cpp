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

#include "image/image_transform.h"

#include <algorithm>
#include <cmath>
#include <cstring>

namespace Self::UI {

std::shared_ptr<ImageTransform> ImageTransform::Create()
{
    return std::make_shared<ImageTransform>();
}

std::shared_ptr<ImageTransform> ImageTransform::Create(const TransformParams& params)
{
    return std::make_shared<ImageTransform>(params);
}

bool ImageTransform::Transform(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                               uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride)
{
    if (!srcData || !dstData || srcWidth <= 0 || srcHeight <= 0 || dstWidth <= 0 || dstHeight <= 0) {
        return false;
    }
    
    Matrix3x3 matrix = ComputeTransformMatrix(srcWidth, srcHeight, dstWidth, dstHeight);
    Matrix3x3 inverse = matrix.Inverse();
    
    for (int32_t y = 0; y < dstHeight; y++) {
        for (int32_t x = 0; x < dstWidth; x++) {
            Point2D srcPoint = inverse.Transform(Point2D(x + 0.5f, y + 0.5f));
            uint8_t pixel[4];
            pixel[0] = SamplePixel(srcData, srcWidth, srcHeight, srcStride, 
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[1] = SamplePixel(srcData + 1, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[2] = SamplePixel(srcData + 2, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[3] = SamplePixel(srcData + 3, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            SetPixel(dstData, dstStride, x, y, pixel);
        }
    }
    
    return true;
}

bool ImageTransform::Scale(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                           uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                           float scaleX, float scaleY, InterpolationMode mode)
{
    TransformParams params;
    params.type = TransformType::SCALE;
    params.scaleX = scaleX;
    params.scaleY = scaleY;
    params.interpolation = mode;
    SetParams(params);
    
    return Transform(srcData, srcWidth, srcHeight, srcStride, dstData, dstWidth, dstHeight, dstStride);
}

bool ImageTransform::Rotate(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                            uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                            float angle, float pivotX, float pivotY)
{
    TransformParams params;
    params.type = TransformType::ROTATE;
    params.rotation = angle;
    params.pivotX = pivotX;
    params.pivotY = pivotY;
    params.interpolation = InterpolationMode::BILINEAR;
    SetParams(params);
    
    return Transform(srcData, srcWidth, srcHeight, srcStride, dstData, dstWidth, dstHeight, dstStride);
}

bool ImageTransform::Flip(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                          uint8_t* dstData, int32_t dstStride, bool horizontal, bool vertical)
{
    if (!srcData || !dstData) return false;
    
    for (int32_t y = 0; y < srcHeight; y++) {
        int32_t srcY = vertical ? (srcHeight - 1 - y) : y;
        for (int32_t x = 0; x < srcWidth; x++) {
            int32_t srcX = horizontal ? (srcWidth - 1 - x) : x;
            
            uint8_t* srcPixel = srcData + srcY * srcStride + srcX * 4;
            uint8_t* dstPixel = dstData + y * dstStride + x * 4;
            
            dstPixel[0] = srcPixel[0];
            dstPixel[1] = srcPixel[1];
            dstPixel[2] = srcPixel[2];
            dstPixel[3] = srcPixel[3];
        }
    }
    
    return true;
}

bool ImageTransform::Crop(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                          uint8_t* dstData, int32_t dstStride, const Rect& cropRect)
{
    if (!srcData || !dstData) return false;
    
    int32_t startX = static_cast<int32_t>(cropRect.x);
    int32_t startY = static_cast<int32_t>(cropRect.y);
    int32_t cropWidth = static_cast<int32_t>(cropRect.width);
    int32_t cropHeight = static_cast<int32_t>(cropRect.height);
    
    startX = std::max(0, std::min(startX, srcWidth - 1));
    startY = std::max(0, std::min(startY, srcHeight - 1));
    cropWidth = std::min(cropWidth, srcWidth - startX);
    cropHeight = std::min(cropHeight, srcHeight - startY);
    
    for (int32_t y = 0; y < cropHeight; y++) {
        uint8_t* srcRow = srcData + (startY + y) * srcStride + startX * 4;
        uint8_t* dstRow = dstData + y * dstStride;
        std::memcpy(dstRow, srcRow, cropWidth * 4);
    }
    
    return true;
}

bool ImageTransform::Translate(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                               uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                               float tx, float ty)
{
    TransformParams params;
    params.type = TransformType::TRANSLATE;
    params.translateX = tx;
    params.translateY = ty;
    params.edgeMode = EdgeMode::BACKGROUND;
    SetParams(params);
    
    return Transform(srcData, srcWidth, srcHeight, srcStride, dstData, dstWidth, dstHeight, dstStride);
}

bool ImageTransform::Skew(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                          uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                          float skewX, float skewY)
{
    TransformParams params;
    params.type = TransformType::SKEW;
    params.skewX = skewX;
    params.skewY = skewY;
    params.interpolation = InterpolationMode::BILINEAR;
    SetParams(params);
    
    return Transform(srcData, srcWidth, srcHeight, srcStride, dstData, dstWidth, dstHeight, dstStride);
}

bool ImageTransform::PerspectiveTransform(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                                          uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                                          const std::vector<Point2D>& srcPoints, const std::vector<Point2D>& dstPoints)
{
    if (srcPoints.size() != 4 || dstPoints.size() != 4) return false;
    
    Matrix3x3 matrix = ComputePerspectiveMatrix(srcPoints, dstPoints);
    
    return ApplyMatrix(srcData, srcWidth, srcHeight, srcStride, dstData, dstWidth, dstHeight, dstStride, matrix);
}

bool ImageTransform::ApplyMatrix(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                                 uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                                 const Matrix3x3& matrix)
{
    if (!srcData || !dstData) return false;
    
    Matrix3x3 inverse = matrix.Inverse();
    
    for (int32_t y = 0; y < dstHeight; y++) {
        for (int32_t x = 0; x < dstWidth; x++) {
            Point2D srcPoint = inverse.Transform(Point2D(x + 0.5f, y + 0.5f));
            uint8_t pixel[4];
            pixel[0] = SamplePixel(srcData, srcWidth, srcHeight, srcStride, 
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[1] = SamplePixel(srcData + 1, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[2] = SamplePixel(srcData + 2, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            pixel[3] = SamplePixel(srcData + 3, srcWidth, srcHeight, srcStride,
                                   srcPoint.x, srcPoint.y, params_.interpolation, params_.edgeMode);
            SetPixel(dstData, dstStride, x, y, pixel);
        }
    }
    
    return true;
}

Matrix3x3 ImageTransform::ComputeTransformMatrix(int32_t srcWidth, int32_t srcHeight,
                                                  int32_t dstWidth, int32_t dstHeight) const
{
    Matrix3x3 result = Matrix3x3::Identity();
    
    float centerX = srcWidth * params_.pivotX;
    float centerY = srcHeight * params_.pivotY;
    
    switch (params_.type) {
        case TransformType::SCALE:
            result = Matrix3x3::Scale(params_.scaleX, params_.scaleY);
            break;
            
        case TransformType::ROTATE: {
            float radians = params_.rotation * M_PI / 180.0f;
            Matrix3x3 toOrigin = Matrix3x3::Translate(-centerX, -centerY);
            Matrix3x3 rotation = Matrix3x3::Rotate(radians);
            Matrix3x3 fromOrigin = Matrix3x3::Translate(centerX, centerY);
            result = toOrigin * rotation * fromOrigin;
            break;
        }
        
        case TransformType::TRANSLATE:
            result = Matrix3x3::Translate(params_.translateX, params_.translateY);
            break;
            
        case TransformType::SKEW: {
            float skewXRad = params_.skewX * M_PI / 180.0f;
            float skewYRad = params_.skewY * M_PI / 180.0f;
            result = Matrix3x3::Skew(skewXRad, skewYRad);
            break;
        }
        
        case TransformType::FLIP: {
            float scaleX = params_.flipHorizontal ? -1.0f : 1.0f;
            float scaleY = params_.flipVertical ? -1.0f : 1.0f;
            Matrix3x3 toOrigin = Matrix3x3::Translate(-centerX, -centerY);
            Matrix3x3 scale = Matrix3x3::Scale(scaleX, scaleY);
            Matrix3x3 fromOrigin = Matrix3x3::Translate(centerX, centerY);
            result = toOrigin * scale * fromOrigin;
            break;
        }
        
        case TransformType::AFFINE:
        case TransformType::MATRIX:
            result = params_.customMatrix;
            break;
            
        default:
            break;
    }
    
    return result;
}

Size ImageTransform::CalculateTransformedSize(int32_t srcWidth, int32_t srcHeight, const TransformParams& params)
{
    switch (params.type) {
        case TransformType::SCALE:
            return Size(srcWidth * params.scaleX, srcHeight * params.scaleY);
            
        case TransformType::CROP:
            return Size(params.cropRect.width, params.cropRect.height);
            
        case TransformType::ROTATE: {
            float radians = params.rotation * M_PI / 180.0f;
            float c = std::abs(cos(radians));
            float s = std::abs(sin(radians));
            float newWidth = srcWidth * c + srcHeight * s;
            float newHeight = srcWidth * s + srcHeight * c;
            return Size(newWidth, newHeight);
        }
        
        default:
            return Size(srcWidth, srcHeight);
    }
}

Rect ImageTransform::CalculateBoundingBox(int32_t srcWidth, int32_t srcHeight, const Matrix3x3& matrix)
{
    Point2D corners[4] = {
        Point2D(0, 0),
        Point2D(srcWidth, 0),
        Point2D(srcWidth, srcHeight),
        Point2D(0, srcHeight)
    };
    
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();
    
    for (int i = 0; i < 4; i++) {
        Point2D transformed = matrix.Transform(corners[i]);
        minX = std::min(minX, transformed.x);
        minY = std::min(minY, transformed.y);
        maxX = std::max(maxX, transformed.x);
        maxY = std::max(maxY, transformed.y);
    }
    
    return Rect(minX, minY, maxX - minX, maxY - minY);
}

uint8_t ImageTransform::SamplePixel(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                                    float x, float y, InterpolationMode mode, EdgeMode edgeMode)
{
    switch (mode) {
        case InterpolationMode::NEAREST:
            return SampleNearest(data, width, height, stride, x, y, edgeMode);
        case InterpolationMode::BILINEAR:
            return SampleBilinear(data, width, height, stride, x, y, edgeMode);
        case InterpolationMode::BICUBIC:
            return SampleBicubic(data, width, height, stride, x, y, edgeMode);
        default:
            return SampleBilinear(data, width, height, stride, x, y, edgeMode);
    }
}

uint8_t ImageTransform::SampleNearest(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                                      float x, float y, EdgeMode edgeMode)
{
    int32_t ix = static_cast<int32_t>(std::round(x));
    int32_t iy = static_cast<int32_t>(std::round(y));
    
    switch (edgeMode) {
        case EdgeMode::CLAMP:
            ix = std::max(0, std::min(ix, width - 1));
            iy = std::max(0, std::min(iy, height - 1));
            break;
        case EdgeMode::WRAP:
            ix = ((ix % width) + width) % width;
            iy = ((iy % height) + height) % height;
            break;
        case EdgeMode::MIRROR:
            ix = std::abs(ix);
            iy = std::abs(iy);
            if (ix >= width) ix = 2 * width - ix - 1;
            if (iy >= height) iy = 2 * height - iy - 1;
            break;
        case EdgeMode::TRANSPARENT:
        case EdgeMode::BACKGROUND:
            if (ix < 0 || ix >= width || iy < 0 || iy >= height) {
                return 0;
            }
            break;
    }
    
    return data[iy * stride + ix * 4];
}

uint8_t ImageTransform::SampleBilinear(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                                       float x, float y, EdgeMode edgeMode)
{
    int32_t x0 = static_cast<int32_t>(std::floor(x));
    int32_t y0 = static_cast<int32_t>(std::floor(y));
    int32_t x1 = x0 + 1;
    int32_t y1 = y0 + 1;
    
    float dx = x - x0;
    float dy = y - y0;
    
    auto getPixel = [&](int32_t px, int32_t py) -> uint8_t {
        switch (edgeMode) {
            case EdgeMode::CLAMP:
                px = std::max(0, std::min(px, width - 1));
                py = std::max(0, std::min(py, height - 1));
                break;
            case EdgeMode::WRAP:
                px = ((px % width) + width) % width;
                py = ((py % height) + height) % height;
                break;
            case EdgeMode::MIRROR:
                px = std::abs(px);
                py = std::abs(py);
                if (px >= width) px = 2 * width - px - 1;
                if (py >= height) py = 2 * height - py - 1;
                break;
            case EdgeMode::TRANSPARENT:
            case EdgeMode::BACKGROUND:
                if (px < 0 || px >= width || py < 0 || py >= height) {
                    return 0;
                }
                break;
        }
        return data[py * stride + px * 4];
    };
    
    float v00 = getPixel(x0, y0);
    float v10 = getPixel(x1, y0);
    float v01 = getPixel(x0, y1);
    float v11 = getPixel(x1, y1);
    
    float v0 = v00 * (1.0f - dx) + v10 * dx;
    float v1 = v01 * (1.0f - dx) + v11 * dx;
    float v = v0 * (1.0f - dy) + v1 * dy;
    
    return static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, v)));
}

uint8_t ImageTransform::SampleBicubic(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                                      float x, float y, EdgeMode edgeMode)
{
    auto cubicWeight = [](float t) -> float {
        float a = -0.5f;
        float t2 = t * t;
        float t3 = t2 * t;
        
        if (t < 1.0f) {
            return (a + 2.0f) * t3 - (a + 3.0f) * t2 + 1.0f;
        } else if (t < 2.0f) {
            return a * t3 - 5.0f * a * t2 + 8.0f * a * t - 4.0f * a;
        }
        return 0.0f;
    };
    
    int32_t ix = static_cast<int32_t>(std::floor(x));
    int32_t iy = static_cast<int32_t>(std::floor(y));
    float dx = x - ix;
    float dy = y - iy;
    
    float result = 0.0f;
    float weightSum = 0.0f;
    
    auto getPixel = [&](int32_t px, int32_t py) -> uint8_t {
        switch (edgeMode) {
            case EdgeMode::CLAMP:
                px = std::max(0, std::min(px, width - 1));
                py = std::max(0, std::min(py, height - 1));
                break;
            case EdgeMode::WRAP:
                px = ((px % width) + width) % width;
                py = ((py % height) + height) % height;
                break;
            case EdgeMode::MIRROR:
                px = std::abs(px);
                py = std::abs(py);
                if (px >= width) px = 2 * width - px - 1;
                if (py >= height) py = 2 * height - py - 1;
                break;
            case EdgeMode::TRANSPARENT:
            case EdgeMode::BACKGROUND:
                if (px < 0 || px >= width || py < 0 || py >= height) {
                    return 0;
                }
                break;
        }
        return data[py * stride + px * 4];
    };
    
    for (int32_t j = -1; j <= 2; j++) {
        for (int32_t i = -1; i <= 2; i++) {
            float weight = cubicWeight(std::abs(dx - i)) * cubicWeight(std::abs(dy - j));
            result += getPixel(ix + i, iy + j) * weight;
            weightSum += weight;
        }
    }
    
    if (weightSum > 0.0f) {
        result /= weightSum;
    }
    
    return static_cast<uint8_t>(std::max(0.0f, std::min(255.0f, result)));
}

void ImageTransform::GetPixel(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                              int32_t x, int32_t y, uint8_t* pixel, EdgeMode edgeMode)
{
    if (x < 0 || x >= width || y < 0 || y >= height) {
        switch (edgeMode) {
            case EdgeMode::TRANSPARENT:
                pixel[0] = pixel[1] = pixel[2] = pixel[3] = 0;
                break;
            case EdgeMode::BACKGROUND:
                pixel[0] = backgroundColor_[0];
                pixel[1] = backgroundColor_[1];
                pixel[2] = backgroundColor_[2];
                pixel[3] = backgroundColor_[3];
                break;
            default:
                x = std::max(0, std::min(x, width - 1));
                y = std::max(0, std::min(y, height - 1));
                break;
        }
    }
    
    uint8_t* srcPixel = data + y * stride + x * 4;
    pixel[0] = srcPixel[0];
    pixel[1] = srcPixel[1];
    pixel[2] = srcPixel[2];
    pixel[3] = srcPixel[3];
}

void ImageTransform::SetPixel(uint8_t* data, int32_t stride, int32_t x, int32_t y, const uint8_t* pixel)
{
    uint8_t* dstPixel = data + y * stride + x * 4;
    dstPixel[0] = pixel[0];
    dstPixel[1] = pixel[1];
    dstPixel[2] = pixel[2];
    dstPixel[3] = pixel[3];
}

Matrix3x3 ImageTransform::ComputePerspectiveMatrix(const std::vector<Point2D>& srcPoints,
                                                    const std::vector<Point2D>& dstPoints)
{
    if (srcPoints.size() != 4 || dstPoints.size() != 4) {
        return Matrix3x3::Identity();
    }
    
    float sx0 = srcPoints[0].x, sy0 = srcPoints[0].y;
    float sx1 = srcPoints[1].x, sy1 = srcPoints[1].y;
    float sx2 = srcPoints[2].x, sy2 = srcPoints[2].y;
    float sx3 = srcPoints[3].x, sy3 = srcPoints[3].y;
    
    float dx0 = dstPoints[0].x, dy0 = dstPoints[0].y;
    float dx1 = dstPoints[1].x, dy1 = dstPoints[1].y;
    float dx2 = dstPoints[2].x, dy2 = dstPoints[2].y;
    float dx3 = dstPoints[3].x, dy3 = dstPoints[3].y;
    
    float A[8][9] = {
        {sx0, sy0, 1, 0, 0, 0, -dx0*sx0, -dx0*sy0, dx0},
        {0, 0, 0, sx0, sy0, 1, -dy0*sx0, -dy0*sy0, dy0},
        {sx1, sy1, 1, 0, 0, 0, -dx1*sx1, -dx1*sy1, dx1},
        {0, 0, 0, sx1, sy1, 1, -dy1*sx1, -dy1*sy1, dy1},
        {sx2, sy2, 1, 0, 0, 0, -dx2*sx2, -dx2*sy2, dx2},
        {0, 0, 0, sx2, sy2, 1, -dy2*sx2, -dy2*sy2, dy2},
        {sx3, sy3, 1, 0, 0, 0, -dx3*sx3, -dx3*sy3, dx3},
        {0, 0, 0, sx3, sy3, 1, -dy3*sx3, -dy3*sy3, dy3}
    };
    
    for (int i = 0; i < 8; i++) {
        float maxVal = std::abs(A[i][i]);
        int maxRow = i;
        for (int k = i + 1; k < 8; k++) {
            if (std::abs(A[k][i]) > maxVal) {
                maxVal = std::abs(A[k][i]);
                maxRow = k;
            }
        }
        
        for (int k = i; k < 9; k++) {
            float tmp = A[maxRow][k];
            A[maxRow][k] = A[i][k];
            A[i][k] = tmp;
        }
        
        for (int k = i + 1; k < 8; k++) {
            float factor = A[k][i] / A[i][i];
            for (int j = i; j < 9; j++) {
                A[k][j] -= factor * A[i][j];
            }
        }
    }
    
    float h[8];
    for (int i = 7; i >= 0; i--) {
        h[i] = A[i][8];
        for (int j = i + 1; j < 8; j++) {
            h[i] -= A[i][j] * h[j];
        }
        h[i] /= A[i][i];
    }
    
    Matrix3x3 result;
    result.m[0][0] = h[0]; result.m[0][1] = h[1]; result.m[0][2] = h[2];
    result.m[1][0] = h[3]; result.m[1][1] = h[4]; result.m[1][2] = h[5];
    result.m[2][0] = h[6]; result.m[2][1] = h[7]; result.m[2][2] = 1.0f;
    
    return result;
}

std::string ImageTransform::GetName() const
{
    switch (params_.type) {
        case TransformType::NONE: return "None";
        case TransformType::SCALE: return "Scale";
        case TransformType::ROTATE: return "Rotate";
        case TransformType::TRANSLATE: return "Translate";
        case TransformType::SKEW: return "Skew";
        case TransformType::FLIP: return "Flip";
        case TransformType::CROP: return "Crop";
        case TransformType::PERSPECTIVE: return "Perspective";
        case TransformType::AFFINE: return "Affine";
        case TransformType::MATRIX: return "Matrix";
        default: return "Unknown";
    }
}

std::string ImageTransform::ToString() const
{
    return "ImageTransform{type=" + GetName() + "}";
}

void ImageTransformChain::AddTransform(std::shared_ptr<ImageTransform> transform)
{
    if (transform) {
        transforms_.push_back(transform);
    }
}

void ImageTransformChain::AddTransform(const TransformParams& params)
{
    transforms_.push_back(ImageTransform::Create(params));
}

void ImageTransformChain::RemoveTransform(int32_t index)
{
    if (index >= 0 && index < static_cast<int32_t>(transforms_.size())) {
        transforms_.erase(transforms_.begin() + index);
    }
}

void ImageTransformChain::ClearTransforms()
{
    transforms_.clear();
}

bool ImageTransformChain::Execute(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                                  uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride)
{
    if (transforms_.empty()) {
        std::memcpy(dstData, srcData, srcHeight * srcStride);
        return true;
    }
    
    std::vector<uint8_t> tempBuffer1(srcHeight * srcStride);
    std::vector<uint8_t> tempBuffer2(srcHeight * srcStride);
    std::memcpy(tempBuffer1.data(), srcData, srcHeight * srcStride);
    
    uint8_t* currentSrc = tempBuffer1.data();
    uint8_t* currentDst = tempBuffer2.data();
    int32_t currentWidth = srcWidth;
    int32_t currentHeight = srcHeight;
    int32_t currentStride = srcStride;
    
    for (size_t i = 0; i < transforms_.size(); i++) {
        auto& transform = transforms_[i];
        Size nextSize = ImageTransform::CalculateTransformedSize(currentWidth, currentHeight, transform->GetParams());
        
        int32_t nextWidth = static_cast<int32_t>(nextSize.width);
        int32_t nextHeight = static_cast<int32_t>(nextSize.height);
        int32_t nextStride = nextWidth * 4;
        
        if (i == transforms_.size() - 1) {
            if (!transform->Transform(currentSrc, currentWidth, currentHeight, currentStride,
                                      dstData, dstWidth, dstHeight, dstStride)) {
                return false;
            }
        } else {
            tempBuffer2.resize(nextHeight * nextStride);
            if (!transform->Transform(currentSrc, currentWidth, currentHeight, currentStride,
                                      currentDst, nextWidth, nextHeight, nextStride)) {
                return false;
            }
            std::swap(currentSrc, currentDst);
            currentWidth = nextWidth;
            currentHeight = nextHeight;
            currentStride = nextStride;
        }
    }
    
    return true;
}

std::shared_ptr<ImageTransform> ImageTransformChain::GetTransform(int32_t index) const
{
    if (index >= 0 && index < static_cast<int32_t>(transforms_.size())) {
        return transforms_[index];
    }
    return nullptr;
}

Size ImageTransformChain::CalculateFinalSize(int32_t srcWidth, int32_t srcHeight) const
{
    Size result(srcWidth, srcHeight);
    for (const auto& transform : transforms_) {
        result = ImageTransform::CalculateTransformedSize(
            static_cast<int32_t>(result.width), 
            static_cast<int32_t>(result.height), 
            transform->GetParams());
    }
    return result;
}

std::string ImageTransformChain::ToString() const
{
    std::string result = "ImageTransformChain{transforms=[";
    for (size_t i = 0; i < transforms_.size(); i++) {
        result += transforms_[i]->GetName();
        if (i < transforms_.size() - 1) result += ", ";
    }
    result += "]}";
    return result;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateRotate90()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::ROTATE;
    params.rotation = 90.0f;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateRotate180()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::ROTATE;
    params.rotation = 180.0f;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateRotate270()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::ROTATE;
    params.rotation = 270.0f;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateFlipHorizontal()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::FLIP;
    params.flipHorizontal = true;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateFlipVertical()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::FLIP;
    params.flipVertical = true;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateScaleToFit(int32_t targetWidth, int32_t targetHeight)
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::SCALE;
    params.scaleX = static_cast<float>(targetWidth);
    params.scaleY = static_cast<float>(targetHeight);
    params.interpolation = InterpolationMode::BILINEAR;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateScaleToFill(int32_t targetWidth, int32_t targetHeight)
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::SCALE;
    params.scaleX = static_cast<float>(targetWidth);
    params.scaleY = static_cast<float>(targetHeight);
    params.interpolation = InterpolationMode::BILINEAR;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateCenterCrop(int32_t targetWidth, int32_t targetHeight)
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::CROP;
    params.cropRect = Rect(0, 0, targetWidth, targetHeight);
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateThumbnail(int32_t maxSize)
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::SCALE;
    params.scaleX = static_cast<float>(maxSize);
    params.scaleY = static_cast<float>(maxSize);
    params.interpolation = InterpolationMode::BILINEAR;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreatePerspectiveCorrection()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::PERSPECTIVE;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateMirrorEffect()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::FLIP;
    params.flipHorizontal = true;
    chain->AddTransform(params);
    return chain;
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::CreateTiltShift()
{
    auto chain = std::make_shared<ImageTransformChain>();
    TransformParams params;
    params.type = TransformType::SKEW;
    params.skewX = 5.0f;
    params.skewY = 0.0f;
    chain->AddTransform(params);
    return chain;
}

std::vector<std::string> ImageTransformPreset::GetPresetNames()
{
    return {
        "rotate_90", "rotate_180", "rotate_270",
        "flip_horizontal", "flip_vertical",
        "scale_to_fit", "scale_to_fill",
        "center_crop", "thumbnail",
        "perspective_correction", "mirror_effect", "tilt_shift"
    };
}

std::shared_ptr<ImageTransformChain> ImageTransformPreset::GetPresetByName(const std::string& name)
{
    if (name == "rotate_90") return CreateRotate90();
    if (name == "rotate_180") return CreateRotate180();
    if (name == "rotate_270") return CreateRotate270();
    if (name == "flip_horizontal") return CreateFlipHorizontal();
    if (name == "flip_vertical") return CreateFlipVertical();
    if (name == "scale_to_fit") return CreateScaleToFit(100, 100);
    if (name == "scale_to_fill") return CreateScaleToFill(100, 100);
    if (name == "center_crop") return CreateCenterCrop(100, 100);
    if (name == "thumbnail") return CreateThumbnail(100);
    if (name == "perspective_correction") return CreatePerspectiveCorrection();
    if (name == "mirror_effect") return CreateMirrorEffect();
    if (name == "tilt_shift") return CreateTiltShift();
    return std::make_shared<ImageTransformChain>();
}

} // namespace Self::UI

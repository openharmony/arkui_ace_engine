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

#ifndef CAPI_IMAGE_TRANSFORM_H
#define CAPI_IMAGE_TRANSFORM_H

#include <memory>
#include <vector>
#include <string>
#include <functional>
#include <cmath>

namespace Self::UI {

enum class TransformType {
    NONE = 0,
    SCALE = 1,
    ROTATE = 2,
    TRANSLATE = 3,
    SKEW = 4,
    FLIP = 5,
    CROP = 6,
    PERSPECTIVE = 7,
    AFFINE = 8,
    MATRIX = 9
};

enum class InterpolationMode {
    NEAREST = 0,
    BILINEAR = 1,
    BICUBIC = 2,
    LANCZOS = 3,
    BOX = 4,
    HAMMING = 5
};

enum class EdgeMode {
    CLAMP = 0,
    WRAP = 1,
    MIRROR = 2,
    TRANSPARENT = 3,
    BACKGROUND = 4
};

struct Point2D {
    float x;
    float y;
    
    Point2D() : x(0.0f), y(0.0f) {}
    Point2D(float px, float py) : x(px), y(py) {}
    
    Point2D operator+(const Point2D& other) const {
        return Point2D(x + other.x, y + other.y);
    }
    
    Point2D operator-(const Point2D& other) const {
        return Point2D(x - other.x, y - other.y);
    }
    
    Point2D operator*(float scalar) const {
        return Point2D(x * scalar, y * scalar);
    }
    
    float Distance(const Point2D& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
    
    float Length() const {
        return sqrt(x * x + y * y);
    }
    
    Point2D Normalize() const {
        float len = Length();
        if (len > 0.0f) {
            return Point2D(x / len, y / len);
        }
        return Point2D(0.0f, 0.0f);
    }
    
    std::string ToString() const {
        return "Point2D(" + std::to_string(x) + ", " + std::to_string(y) + ")";
    }
};

struct Point3D {
    float x;
    float y;
    float z;
    
    Point3D() : x(0.0f), y(0.0f), z(0.0f) {}
    Point3D(float px, float py, float pz) : x(px), y(py), z(pz) {}
    
    Point3D operator+(const Point3D& other) const {
        return Point3D(x + other.x, y + other.y, z + other.z);
    }
    
    Point3D operator-(const Point3D& other) const {
        return Point3D(x - other.x, y - other.y, z - other.z);
    }
    
    Point3D operator*(float scalar) const {
        return Point3D(x * scalar, y * scalar, z * scalar);
    }
    
    float Distance(const Point3D& other) const {
        float dx = x - other.x;
        float dy = y - other.y;
        float dz = z - other.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
    
    float Length() const {
        return sqrt(x * x + y * y + z * z);
    }
    
    Point3D Normalize() const {
        float len = Length();
        if (len > 0.0f) {
            return Point3D(x / len, y / len, z / len);
        }
        return Point3D(0.0f, 0.0f, 0.0f);
    }
    
    std::string ToString() const {
        return "Point3D(" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")";
    }
};

struct Rect {
    float x;
    float y;
    float width;
    float height;
    
    Rect() : x(0.0f), y(0.0f), width(0.0f), height(0.0f) {}
    Rect(float px, float py, float w, float h) : x(px), y(py), width(w), height(h) {}
    
    bool Contains(const Point2D& point) const {
        return point.x >= x && point.x <= x + width &&
               point.y >= y && point.y <= y + height;
    }
    
    bool Intersects(const Rect& other) const {
        return x < other.x + other.width && x + width > other.x &&
               y < other.y + other.height && y + height > other.y;
    }
    
    Rect Intersection(const Rect& other) const {
        if (!Intersects(other)) return Rect();
        
        float left = std::max(x, other.x);
        float top = std::max(y, other.y);
        float right = std::min(x + width, other.x + other.width);
        float bottom = std::min(y + height, other.y + other.height);
        
        return Rect(left, top, right - left, bottom - top);
    }
    
    Rect Union(const Rect& other) const {
        float left = std::min(x, other.x);
        float top = std::min(y, other.y);
        float right = std::max(x + width, other.x + other.width);
        float bottom = std::max(y + height, other.y + other.height);
        
        return Rect(left, top, right - left, bottom - top);
    }
    
    Point2D Center() const {
        return Point2D(x + width / 2.0f, y + height / 2.0f);
    }
    
    float Area() const {
        return width * height;
    }
    
    bool IsEmpty() const {
        return width <= 0.0f || height <= 0.0f;
    }
    
    std::string ToString() const {
        return "Rect(" + std::to_string(x) + ", " + std::to_string(y) + ", " +
               std::to_string(width) + ", " + std::to_string(height) + ")";
    }
};

struct Size {
    float width;
    float height;
    
    Size() : width(0.0f), height(0.0f) {}
    Size(float w, float h) : width(w), height(h) {}
    
    float Area() const {
        return width * height;
    }
    
    float AspectRatio() const {
        if (height == 0.0f) return 0.0f;
        return width / height;
    }
    
    bool IsEmpty() const {
        return width <= 0.0f || height <= 0.0f;
    }
    
    Size Scale(float factor) const {
        return Size(width * factor, height * factor);
    }
    
    Size ScaleToFit(const Size& target, bool maintainAspect = true) const {
        if (IsEmpty() || target.IsEmpty()) return Size();
        
        if (!maintainAspect) {
            return target;
        }
        
        float scaleX = target.width / width;
        float scaleY = target.height / height;
        float scale = std::min(scaleX, scaleY);
        
        return Scale(scale);
    }
    
    Size ScaleToFill(const Size& target) const {
        if (IsEmpty() || target.IsEmpty()) return Size();
        
        float scaleX = target.width / width;
        float scaleY = target.height / height;
        float scale = std::max(scaleX, scaleY);
        
        return Scale(scale);
    }
    
    std::string ToString() const {
        return "Size(" + std::to_string(width) + ", " + std::to_string(height) + ")";
    }
};

struct Matrix3x3 {
    float m[3][3];
    
    Matrix3x3() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = (i == j) ? 1.0f : 0.0f;
            }
        }
    }
    
    static Matrix3x3 Identity() {
        return Matrix3x3();
    }
    
    static Matrix3x3 Zero() {
        Matrix3x3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = 0.0f;
            }
        }
        return result;
    }
    
    Matrix3x3 operator*(const Matrix3x3& other) const {
        Matrix3x3 result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.m[i][j] = 0.0f;
                for (int k = 0; k < 3; k++) {
                    result.m[i][j] += m[i][k] * other.m[k][j];
                }
            }
        }
        return result;
    }
    
    Point2D Transform(const Point2D& point) const {
        float x = m[0][0] * point.x + m[0][1] * point.y + m[0][2];
        float y = m[1][0] * point.x + m[1][1] * point.y + m[1][2];
        float w = m[2][0] * point.x + m[2][1] * point.y + m[2][2];
        
        if (w != 0.0f) {
            return Point2D(x / w, y / w);
        }
        return Point2D(x, y);
    }
    
    float Determinant() const {
        return m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
               m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
               m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
    }
    
    Matrix3x3 Inverse() const {
        float det = Determinant();
        if (det == 0.0f) return Identity();
        
        Matrix3x3 result;
        result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) / det;
        result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) / det;
        result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) / det;
        result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) / det;
        result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) / det;
        result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) / det;
        result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) / det;
        result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) / det;
        result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) / det;
        
        return result;
    }
    
    static Matrix3x3 Scale(float sx, float sy) {
        Matrix3x3 result;
        result.m[0][0] = sx;
        result.m[1][1] = sy;
        return result;
    }
    
    static Matrix3x3 Rotate(float angle) {
        Matrix3x3 result;
        float c = cos(angle);
        float s = sin(angle);
        result.m[0][0] = c;
        result.m[0][1] = -s;
        result.m[1][0] = s;
        result.m[1][1] = c;
        return result;
    }
    
    static Matrix3x3 Translate(float tx, float ty) {
        Matrix3x3 result;
        result.m[0][2] = tx;
        result.m[1][2] = ty;
        return result;
    }
    
    static Matrix3x3 Skew(float skewX, float skewY) {
        Matrix3x3 result;
        result.m[0][1] = tan(skewX);
        result.m[1][0] = tan(skewY);
        return result;
    }
    
    std::string ToString() const {
        std::string result = "Matrix3x3[\n";
        for (int i = 0; i < 3; i++) {
            result += "  [";
            for (int j = 0; j < 3; j++) {
                result += std::to_string(m[i][j]);
                if (j < 2) result += ", ";
            }
            result += "]\n";
        }
        result += "]";
        return result;
    }
};

struct TransformParams {
    TransformType type = TransformType::NONE;
    float scaleX = 1.0f;
    float scaleY = 1.0f;
    float rotation = 0.0f;
    float translateX = 0.0f;
    float translateY = 0.0f;
    float skewX = 0.0f;
    float skewY = 0.0f;
    float pivotX = 0.5f;
    float pivotY = 0.5f;
    Rect cropRect;
    bool flipHorizontal = false;
    bool flipVertical = false;
    InterpolationMode interpolation = InterpolationMode::BILINEAR;
    EdgeMode edgeMode = EdgeMode::CLAMP;
    uint8_t backgroundColor[4] = {0, 0, 0, 0};
    std::vector<Point2D> perspectivePoints;
    Matrix3x3 customMatrix;
};

class ImageTransform {
public:
    ImageTransform() : params_() {}
    explicit ImageTransform(const TransformParams& params) : params_(params) {}
    ~ImageTransform() = default;
    
    static std::shared_ptr<ImageTransform> Create();
    static std::shared_ptr<ImageTransform> Create(const TransformParams& params);
    
    void SetParams(const TransformParams& params) { params_ = params; }
    TransformParams GetParams() const { return params_; }
    
    bool Transform(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                   uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride);
    
    bool Scale(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
               uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
               float scaleX, float scaleY, InterpolationMode mode = InterpolationMode::BILINEAR);
    
    bool Rotate(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                float angle, float pivotX = 0.5f, float pivotY = 0.5f);
    
    bool Flip(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
              uint8_t* dstData, int32_t dstStride, bool horizontal, bool vertical);
    
    bool Crop(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
              uint8_t* dstData, int32_t dstStride, const Rect& cropRect);
    
    bool Translate(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                   uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                   float tx, float ty);
    
    bool Skew(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
              uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
              float skewX, float skewY);
    
    bool PerspectiveTransform(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                              uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                              const std::vector<Point2D>& srcPoints, const std::vector<Point2D>& dstPoints);
    
    bool ApplyMatrix(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                     uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride,
                     const Matrix3x3& matrix);
    
    Matrix3x3 ComputeTransformMatrix(int32_t srcWidth, int32_t srcHeight,
                                     int32_t dstWidth, int32_t dstHeight) const;
    
    static Size CalculateTransformedSize(int32_t srcWidth, int32_t srcHeight, const TransformParams& params);
    static Rect CalculateBoundingBox(int32_t srcWidth, int32_t srcHeight, const Matrix3x3& matrix);
    
    std::string GetName() const;
    std::string ToString() const;
    
private:
    uint8_t SamplePixel(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                        float x, float y, InterpolationMode mode, EdgeMode edgeMode);
    
    uint8_t SampleNearest(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                          float x, float y, EdgeMode edgeMode);
    
    uint8_t SampleBilinear(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                           float x, float y, EdgeMode edgeMode);
    
    uint8_t SampleBicubic(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                          float x, float y, EdgeMode edgeMode);
    
    void GetPixel(uint8_t* data, int32_t width, int32_t height, int32_t stride,
                  int32_t x, int32_t y, uint8_t* pixel, EdgeMode edgeMode);
    
    void SetPixel(uint8_t* data, int32_t stride, int32_t x, int32_t y, const uint8_t* pixel);
    
    static Matrix3x3 ComputePerspectiveMatrix(const std::vector<Point2D>& srcPoints,
                                              const std::vector<Point2D>& dstPoints);
    
    TransformParams params_;
};

class ImageTransformChain {
public:
    ImageTransformChain() {}
    ~ImageTransformChain() = default;
    
    void AddTransform(std::shared_ptr<ImageTransform> transform);
    void AddTransform(const TransformParams& params);
    void RemoveTransform(int32_t index);
    void ClearTransforms();
    
    bool Execute(uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride,
                 uint8_t* dstData, int32_t dstWidth, int32_t dstHeight, int32_t dstStride);
    
    std::shared_ptr<std::vector<uint8_t>> ExecuteWithBuffer(
        uint8_t* srcData, int32_t srcWidth, int32_t srcHeight, int32_t srcStride);
    
    int32_t GetTransformCount() const { return static_cast<int32_t>(transforms_.size()); }
    std::shared_ptr<ImageTransform> GetTransform(int32_t index) const;
    
    Size CalculateFinalSize(int32_t srcWidth, int32_t srcHeight) const;
    
    std::string ToString() const;
    
private:
    std::vector<std::shared_ptr<ImageTransform>> transforms_;
};

class ImageTransformPreset {
public:
    static std::shared_ptr<ImageTransformChain> CreateRotate90();
    static std::shared_ptr<ImageTransformChain> CreateRotate180();
    static std::shared_ptr<ImageTransformChain> CreateRotate270();
    static std::shared_ptr<ImageTransformChain> CreateFlipHorizontal();
    static std::shared_ptr<ImageTransformChain> CreateFlipVertical();
    static std::shared_ptr<ImageTransformChain> CreateScaleToFit(int32_t targetWidth, int32_t targetHeight);
    static std::shared_ptr<ImageTransformChain> CreateScaleToFill(int32_t targetWidth, int32_t targetHeight);
    static std::shared_ptr<ImageTransformChain> CreateCenterCrop(int32_t targetWidth, int32_t targetHeight);
    static std::shared_ptr<ImageTransformChain> CreateThumbnail(int32_t maxSize);
    static std::shared_ptr<ImageTransformChain> CreatePerspectiveCorrection();
    static std::shared_ptr<ImageTransformChain> CreateMirrorEffect();
    static std::shared_ptr<ImageTransformChain> CreateTiltShift();
    
    static std::vector<std::string> GetPresetNames();
    static std::shared_ptr<ImageTransformChain> GetPresetByName(const std::string& name);
};

} // namespace Self::UI

#endif // CAPI_IMAGE_TRANSFORM_H

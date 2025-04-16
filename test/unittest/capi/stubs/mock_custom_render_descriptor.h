/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#ifndef CAPI_STUBS_MOCK_CUSTOM_RENDER_DESCRIPTOR_H
#define CAPI_STUBS_MOCK_CUSTOM_RENDER_DESCRIPTOR_H
#include <string>
#include <vector>
#include <memory>

namespace OHOS::Render3D {
enum class AnimationState : uint8_t {
    PLAY,
    PAUSE,
    STOP,
};
enum class BackgroundType : uint8_t {
    CUBE_MAP,
    TRANSPARENT,
};
enum class SurfaceType : uint8_t {
    UNDEFINE,
    SURFACE_WINDOW, // bufferqueue dss
    SURFACE_TEXTURE, // bufferqueue texture
    SURFACE_BUFFER, // no buffer queue
};
enum class LightType : uint8_t {
    INVALID = 0,
    DIRECTIONAL = 1,
    POINT = 2,
    SPOT = 3
};
struct CustomRenderDescriptor {
public:
    CustomRenderDescriptor(const std::string& rngUri, bool needsFrameCallback) : rngUri(rngUri),
        needsFrameCallback(needsFrameCallback) {};
    ~CustomRenderDescriptor() = default;
    std::string GetUri()
    {
        return rngUri;
    }
    bool NeedsFrameCallback()
    {
        return needsFrameCallback;
    }
private:
    std::string rngUri;
    bool needsFrameCallback = false;
};
class GLTFAnimation {
public:
    ~GLTFAnimation() = default;

    const std::string& GetName() const { return name_; }
    AnimationState GetState() const { return state_; }
    int GetRepeatCount() const { return repeatCount_; }
    float GetSpeed() const { return speed_; }
    float GetDuration() const { return duration_; }
    bool GetReverse() const { return reverse_; }
private:
    std::string name_ = "";
    AnimationState state_ = AnimationState::PLAY;
    int repeatCount_ = -1;
    float speed_ = 1.0;
    float duration_ = -1.0;
    bool reverse_ = false;
};
class Vec3 {
public:
    Vec3() {}
    Vec3(float x, float y, float z) : xx(x), yy(y), zz(z) {}
    float GetX() const { return xx; }
    float GetY() const { return yy; }
    float GetZ() const { return zz; }
    void SetX(float x) { xx = x; }
    void SetY(float y) { yy = y; }
    void SetZ(float z) { zz = z; }
private:
    union {
        struct {
            float xx = 0.0f;
            float yy = 0.0f;
            float zz = 0.0f;
        };
        float data[3];
    };
};
class Geometry {
public:
    Geometry(std::string name, Vec3& position, bool castShadows = false, bool receiveShadows = false) : name_(name),
        position_(position), castShadows_(castShadows), receiveShadows_(receiveShadows) {};
    ~Geometry() = default;
    virtual int32_t GetType() const = 0;
    virtual bool Equals(const Geometry& obj) const
    {
        return GetType() == obj.GetType() &&
               GetName() == obj.GetName() &&
               CastShadows() == obj.CastShadows() &&
               ReceiveShadows() == obj.ReceiveShadows() &&
               IsEqual(obj);
    }
    bool PositionEquals(const Geometry& obj)
    {
        return GetPosition().GetX() == obj.GetPosition().GetX() &&
               GetPosition().GetY() == obj.GetPosition().GetY() &&
               GetPosition().GetZ() == obj.GetPosition().GetZ();
    }
    std::string GetName() const
    {
        return name_;
    }
    const Vec3& GetPosition() const
    {
        return position_;
    }
    bool CastShadows() const
    {
        return castShadows_;
    }
    bool ReceiveShadows() const
    {
        return receiveShadows_;
    }
protected:
    virtual bool IsEqual(const Geometry& obj) const = 0;
private:
    std::string name_;
    Vec3 position_;
    bool castShadows_ { false };
    bool receiveShadows_ { false };
};

enum GeometryType {
    CUBE,
    SPHARE,
    CONE,
};
enum class PointerEventType {
    PRESSED,
    RELEASED,
    CANCELLED,
    MOVED,
    SCROLL,
};
struct PointerEvent {
    PointerEventType eventType { PointerEventType::RELEASED };
    int pointerId {};
    int buttonIndex {};
    float x {};
    float y {};
    float deltaX {};
    float deltaY {};
};
class Position {
public:
    Position() = default;
    ~Position() = default;

    void SetPosition(const OHOS::Render3D::Vec3& vec)
    {
        pos_ = vec;
    }
    void SetDistance(const float distance)
    {
        distance_ = distance;
    }
    void SetIsAngular(bool isAngular)
    {
        isAngular_ = isAngular;
    }
    const Vec3& GetPosition() const
    {
        return pos_;
    }
    float GetX() const
    {
        return pos_.GetX();
    }
    float GetY() const
    {
        return pos_.GetY();
    }
    float GetZ() const
    {
        return pos_.GetZ();
    }
    float GetDistance() const
    {
        return distance_;
    }
    bool GetIsAngular() const
    {
        return isAngular_;
    }
private:
    OHOS::Render3D::Vec3 pos_ { 0.0f, 0.0f, 4.0f };
    float distance_ { 0.0f };
    bool isAngular_ = false;
};
class Quaternion {
public:
    Quaternion() {}
    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    float GetX() const
    {
        return x;
    }
    float GetY() const
    {
        return y;
    }
    float GetZ() const
    {
        return z;
    }
    float GetW() const
    {
        return w;
    }
    void SetX(float x)
    {
        this->x = x;
    }
    void SetY(float y)
    {
        this->y = y;
    }
    void SetZ(float z)
    {
        this->z = z;
    }
    void SetW(float w)
    {
        this->w = w;
    }
    bool operator==(const Quaternion& other) const
    {
        return (x == other.x) && (y == other.y) && (z == other.z) && (w == other.w);
    }

private:
    union {
        struct {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4] { 0.0f, 0.0f, 0.0f, 0.0f } ;
    };
};
struct TextureInfo {
    uint32_t width = 0U;
    uint32_t height = 0U;
    uint32_t textureId = 0U;
    void* nativeWindow = nullptr;
    float widthScale = 1.0f;
    float heightScale = 1.0f;
    float customRatio = 0.1f;
    bool recreateWindow = true;
};

struct WindowChangeInfo {
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    float scale = 1.0f;
    float widthScale = 1.0f;
    float heightScale = 1.0f;
    bool recreateWindow = true;
    SurfaceType surfaceType = SurfaceType::SURFACE_TEXTURE;
    uint32_t transformType = 0; // TransformHint
};

struct HapInfo {
    std::string hapPath = "";
    std::string bundleName = "";
    std::string moduleName = "";
};
struct PlatformData {
    /** Core root path */
    std::string coreRootPath;
    /** Application root path */
    std::string appRootPath;
    /** Application plugin path */
    std::string appPluginPath;
    // hapInfo
    HapInfo hapInfo;
};
class __attribute__((visibility("default"))) WidgetAdapter {
public:
    explicit WidgetAdapter(uint32_t key);
    virtual ~WidgetAdapter();
    void DeInitEngine();
    WidgetAdapter(const WidgetAdapter&) = delete;
    WidgetAdapter& operator=(const WidgetAdapter&) = delete;

    bool Initialize() { return true; }
    bool OnWindowChange(const TextureInfo& textureInfo) { return true; }

    bool SetupCameraTransform(const OHOS::Render3D::Position& position, const OHOS::Render3D::Vec3& lookAt,
        const OHOS::Render3D::Vec3& up, const OHOS::Render3D::Quaternion& rotation)  { return true; }
    bool SetupCameraViewProjection(float zNear, float zFar, float fovDegrees) { return true; }
    bool SetupCameraViewport(uint32_t width, uint32_t height) { return true; }

    bool OnTouchEvent(const PointerEvent& event) { return true; }
    bool NeedsRepaint() { return true; }

    bool DrawFrame() { return true; }
    bool UpdateGeometries(const std::vector<std::shared_ptr<Geometry>>& shapes) { return true; }
    bool UpdateGLTFAnimations(const std::vector<std::shared_ptr<GLTFAnimation>>& animations) { return true; }

    bool UpdateLights() { return true; }
    bool UpdateCustomRender(const std::shared_ptr<CustomRenderDescriptor>& customRender) { return true; }
    bool UpdateShaderPath(const std::string& shaderPath) { return true; }
    bool UpdateImageTexturePaths(const std::vector<std::string>& imageTextures) { return true; }
    bool UpdateShaderInputBuffer() { return true; }
    bool LoadSceneModel(const std::string& scene) { return true; }
    bool LoadEnvModel(const std::string& enviroment, BackgroundType type) { return true; }
    bool UnloadSceneModel() { return true; }
    bool UnloadEnvModel() { return true; }

private:
    uint32_t key_;
};

class __attribute__((visibility("default"))) TextureLayer {
public:
    explicit TextureLayer(int32_t key);
    virtual ~TextureLayer();

    virtual void DestroyRenderTarget() {}
    virtual TextureInfo GetTextureInfo()
    {
        TextureInfo tx;
        return tx;
    }

    virtual void SetParent() {}
    virtual TextureInfo OnWindowChange(const WindowChangeInfo& windowChangeInfo)
    {
        TextureInfo tx;
        return tx;
    }

protected:
    TextureLayer() = default;

private:
    std::shared_ptr<TextureLayer> textureLayer_;
};
} // namespace name
#endif // CAPI_STUBS_MOCK_CUSTOM_RENDER_DESCRIPTOR_H
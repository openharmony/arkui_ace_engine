/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef RENDER_SERVICE_CLIENT_CORE_ANIMATION_RS_PARTICLE_PARAMS_H
#define RENDER_SERVICE_CLIENT_CORE_ANIMATION_RS_PARTICLE_PARAMS_H

#include <cstdint>
#include <memory>

namespace OHOS::Rosen {
class RSColor;
class RSImage;
class RSShader;
class RSTransitionEffect;
class RectF {
public:
    RectF(float left, float top, float width, float height) : left_(left), top_(top), width_(width), height_(height) {}

    float GetLeft() const
    {
        return left_;
    }

    float GetTop() const
    {
        return top_;
    }

    float GetWidth() const
    {
        return width_;
    }

    float GetHeight() const
    {
        return height_;
    }

private:
    float left_ = 0.0f;
    float top_ = 0.0f;
    float width_ = 0.0f;
    float height_ = 0.0f;
};

enum class SHADOW_COLOR_STRATEGY : uint8_t;
enum class RSUIFirstSwitch : uint8_t;

template<typename T>
class Range {};

template<typename T>
class ParticleParaType {};

class ParticleAcceleration {};
class ParticleColorParaType {};
class ParticleParams {};
class EmitterConfig {};
class ParticleVelocity {};

class Vector4f {
public:
    constexpr Vector4f(float, float, float, float) {}
};
} // namespace OHOS::Rosen

#endif // RENDER_SERVICE_CLIENT_CORE_ANIMATION_RS_PARTICLE_PARAMS_H

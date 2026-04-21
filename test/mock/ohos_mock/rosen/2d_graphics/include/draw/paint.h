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

#ifndef PAINT_H
#define PAINT_H

#include <memory>

#include "draw/brush.h"
#include "draw/pen.h"

#include "effect/blender.h"
#include "effect/color_space.h"
#include "effect/shader_effect.h"

namespace OHOS {
namespace Rosen {
namespace Drawing {
class Paint {
public:
    constexpr static scalar DEFAULT_MITER_VAL = 4.0f;

    Paint() noexcept;
    Paint(const Paint& other) noexcept;
    Paint(const Color& c, std::shared_ptr<ColorSpace> colorSpace = nullptr) noexcept;
    Paint& operator=(const Paint& other);
    ~Paint() {};

    static bool CanCombinePaint(const Paint& pen, const Paint& brush);
    void AttachBrush(const Brush& brush);
    void AttachPen(const Pen& pen);

    enum PaintStyle : uint8_t {
        PAINT_NONE = 0x00,
        PAINT_FILL = 0x01,
        PAINT_STROKE = 0x02,
        PAINT_FILL_STROKE = 0x03
    };

    void SetStyle(const PaintStyle& style);
    PaintStyle GetStyle() const { return style_; }
    bool IsValid() const { return style_ != PaintStyle::PAINT_NONE; }
    bool HasStrokeStyle() const;

    void SetColor(const Color& c);
    void SetARGB(int a, int r, int g, int b);
    void SetColor(const Color4f& cf, std::shared_ptr<ColorSpace> colorSpace = nullptr);
    const Color& GetColor() const { return color_; }
    const Color4f& GetColor4f() { return color_.GetColor4f(); }
    const std::shared_ptr<ColorSpace> GetColorSpace() const { return colorSpace_; }
    const ColorSpace* GetColorSpacePtr() const { return colorSpace_.get(); }

    void SetAlpha(uint32_t a);
    void SetAlphaF(scalar a);
    inline uint32_t GetAlpha() const { return color_.GetAlpha(); }
    inline scalar GetAlphaF() const { return color_.GetAlphaF(); }

    void SetWidth(scalar width);
    scalar GetWidth() const { return width_; }

    void SetMiterLimit(scalar limit);
    scalar GetMiterLimit() const { return miterLimit_; }

    void SetCapStyle(Pen::CapStyle cs);
    Pen::CapStyle GetCapStyle() const { return cap_; }

    void SetJoinStyle(Pen::JoinStyle js);
    Pen::JoinStyle GetJoinStyle() const { return join_; }

    void SetBlendMode(BlendMode mode);
    BlendMode GetBlendMode() const { return blendMode_; }

    void SetFilter(const Filter& filter);
    const Filter GetFilter() const { return filter_; }
    bool HasFilter() const { return hasFilter_; }

    void SetShaderEffect(std::shared_ptr<ShaderEffect> e);
    const std::shared_ptr<ShaderEffect> GetShaderEffect() const { return shaderEffect_; }
    const ShaderEffect* GetShaderEffectPtr() const { return shaderEffect_.get(); }

    void SetPathEffect(std::shared_ptr<PathEffect> e);
    const std::shared_ptr<PathEffect> GetPathEffect() const { return pathEffect_; }
    const PathEffect* GetPathEffectPtr() const { return pathEffect_.get(); }

    void SetBlender(std::shared_ptr<Blender> blender);

    void SetBlenderEnabled(bool blenderEnabled);
    bool GetBlenderEnabled() const { return blenderEnabled_; };;

    void SetAntiAlias(bool aa);
    bool IsAntiAlias() const { return antiAlias_; }

    void Reset();
    void Disable();

    friend bool operator==(const Paint& p1, const Paint& p2);
    friend bool operator!=(const Paint& p1, const Paint& p2);

    void Dump(std::string& out) const;

private:
    bool antiAlias_ = false;
    bool blenderEnabled_ = true;
    bool hasFilter_ = false;
    PaintStyle style_ = PaintStyle::PAINT_NONE;
    BlendMode blendMode_ = BlendMode::SRC_OVER;
    scalar width_ = 0.0f;
    scalar miterLimit_ = DEFAULT_MITER_VAL; // default as 4.0f
    Pen::JoinStyle join_ = Pen::JoinStyle::DEFAULT_JOIN;
    Pen::CapStyle cap_ = Pen::CapStyle::DEFAULT_CAP;

    std::shared_ptr<ColorSpace> colorSpace_ = nullptr;
    std::shared_ptr<ShaderEffect> shaderEffect_ = nullptr;
    std::shared_ptr<PathEffect> pathEffect_ = nullptr;

    Color color_ = Color::COLOR_BLACK;
    Filter filter_;
};
} // namespace Drawing
} // namespace Rosen
} // namespace OHOS
#endif // PAINT_H

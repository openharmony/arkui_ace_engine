/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_GRADIENT_STYLE_MODIFIER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_GRADIENT_STYLE_MODIFIER_H

#include <cstdint>
#include <memory>
#include <optional>
#include <vector>

#include "common/rs_vector4.h"
#if defined(MODIFIER_NG)
#include "render_service_client/core/modifier_ng/custom/rs_background_style_modifier.h"
#endif

#include "base/geometry/dimension.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/render/adapter/rosen_modifier_adapter.h"

namespace OHOS::Ace::NG {
class RosenRenderContext;
class ColorAnimatableArithmetic : public Rosen::RSAnimatableArithmetic<ColorAnimatableArithmetic> {
public:
    ColorAnimatableArithmetic() = default;
    explicit ColorAnimatableArithmetic(const Gradient& gradient);

    ColorAnimatableArithmetic Add(const ColorAnimatableArithmetic& value) const override;
    ColorAnimatableArithmetic Minus(const ColorAnimatableArithmetic& value) const override;
    ColorAnimatableArithmetic Multiply(const float scale) const override;
    bool IsEqual(const ColorAnimatableArithmetic& value) const override;
    const std::vector<Color>& GetColors() const
    {
        return colors_;
    }

    void PaddingColors(size_t size, const Color& defaultColor)
    {
        auto color = colors_.size() == 0 ? defaultColor : colors_.back();
        colors_.insert(colors_.end(), size, color);
    }

private:
    std::vector<Color> colors_;
};

class ColorStopAnimatableArithmetic : public Rosen::RSAnimatableArithmetic<ColorStopAnimatableArithmetic> {
public:
    ColorStopAnimatableArithmetic() = default;
    explicit ColorStopAnimatableArithmetic(const Gradient& gradient);

    ColorStopAnimatableArithmetic Add(const ColorStopAnimatableArithmetic& value) const override;
    ColorStopAnimatableArithmetic Minus(const ColorStopAnimatableArithmetic& value) const override;
    ColorStopAnimatableArithmetic Multiply(const float scale) const override;
    bool IsEqual(const ColorStopAnimatableArithmetic& value) const override;
    const std::vector<Dimension>& GetColorStops() const
    {
        return colorStops_;
    }

    void PaddingColorStops(size_t size, const Dimension& dimension)
    {
        colorStops_.insert(colorStops_.end(), size, dimension);
    }

private:
    std::vector<Dimension> colorStops_;
};

#if defined(MODIFIER_NG)
using RSBackgroundStyleModifier = Rosen::ModifierNG::RSBackgroundStyleModifier;
#else
using RSBackgroundStyleModifier = Rosen::RSBackgroundStyleModifier;
#endif

class [[deprecated]] GradientStyleModifier : public RSBackgroundStyleModifier {
public:
    explicit GradientStyleModifier(const WeakPtr<RosenRenderContext>& context) : renderContext_(context) {}
    ~GradientStyleModifier() override = default;

    void Draw(RSDrawingContext& context) const override;
#ifndef USE_ROSEN_DRAWING
    void PaintGradient(SkCanvas& canvas, const SizeF& frameSize) const;
#else
    void PaintGradient(RSCanvas& canvas, const SizeF& frameSize) const;
#endif

    Gradient GetGradient() const;
    void SetGradient(const Gradient& gradient);
    void PaddingColors(ColorAnimatableArithmetic& colors, bool repeat);
    void PaddingColorStops(ColorStopAnimatableArithmetic& colorStops, bool repeat);
    void SetSizeF(const SizeF& size);

private:
    WeakPtr<RosenRenderContext> renderContext_;
    // Animatable
    std::shared_ptr<Rosen::RSAnimatableProperty<ColorAnimatableArithmetic>> colors_;
    std::shared_ptr<Rosen::RSAnimatableProperty<ColorStopAnimatableArithmetic>> colorStops_;
    std::shared_ptr<Rosen::RSAnimatableProperty<Rosen::Vector2f>> sizeF_;
    // No animatable
    std::shared_ptr<Rosen::RSProperty<Gradient>> gradient_;
    ColorSpace colorSpace_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_GRADIENT_STYLE_MODIFIER_H

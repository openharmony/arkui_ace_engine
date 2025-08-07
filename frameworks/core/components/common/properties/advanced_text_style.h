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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_STYLE_H
#include "ui/base/ace_type.h"

#include "core/components/common/properties/decoration.h"
#include "frameworks/base/geometry/ng/point_t.h"
#include "frameworks/core/components_ng/pattern/symbol/symbol_effect_options.h"

namespace OHOS::Ace {
struct FontForegroudGradiantColor {
    std::vector<NG::PointF> points;
    std::vector<float> scalars;
    std::vector<Color> colors;

    bool IsValid() const
    {
        // 2 points including begin and end
        return points.size() == 2 && scalars.size() == colors.size();
    }

    bool operator==(const FontForegroudGradiantColor& fontForegroudGradiantColor) const
    {
        auto isScalarEq = true;
        if (scalars.size() != fontForegroudGradiantColor.scalars.size()) {
            isScalarEq = false;
        }
        for (size_t i = 0; i < scalars.size() && isScalarEq; i++) {
            isScalarEq = NearEqual(scalars[i], fontForegroudGradiantColor.scalars[i]);
        }
        return isScalarEq && (points == fontForegroudGradiantColor.points) &&
               (colors == fontForegroudGradiantColor.colors);
    }
};

class AdvancedTextStyle : public AceType {
    DECLARE_ACE_TYPE(AdvancedTextStyle, AceType);

public:
    void SetGradient(const std::optional<Gradient>& gradient)
    {
        gradient_ = gradient;
    }

    const std::optional<Gradient>& GetGradient() const
    {
        return gradient_;
    }

    void SetFontForegroudGradiantColor(const std::optional<FontForegroudGradiantColor>& gradiantColor)
    {
        fontForegroudGradiantColor_ = gradiantColor;
    }

    const std::optional<FontForegroudGradiantColor>& GetFontForegroudGradiantColor() const
    {
        return fontForegroudGradiantColor_;
    }

private:
    std::optional<Gradient> gradient_;
    // for ai option's gradient color
    std::optional<FontForegroudGradiantColor> fontForegroudGradiantColor_;
};

class SymbolTextStyle : public AceType {
    DECLARE_ACE_TYPE(SymbolTextStyle, AceType);

public:

    void SetInnerSymbolEffectOptions(const std::optional<NG::SymbolEffectOptions>& symbolEffectOptions)
    {
        symbolEffectOptions_ = symbolEffectOptions;
    }

    const std::optional<NG::SymbolEffectOptions>& GetInnerSymbolEffectOptions() const
    {
        return symbolEffectOptions_;
    }

    void SetInnerSymbolShadowProp(const std::optional<SymbolShadow>& symbolShadow)
    {
        symbolShadowProp_ = symbolShadow;
    }

    const std::optional<SymbolShadow>& GetInnerSymbolShadowProp() const
    {
        return symbolShadowProp_;
    }
private:
    // for symbol
    std::optional<NG::SymbolEffectOptions> symbolEffectOptions_;
    std::optional<SymbolShadow> symbolShadowProp_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_ADVANCED_TEXT_STYLE_H
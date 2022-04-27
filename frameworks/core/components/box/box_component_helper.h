/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H

#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"

// Helper class for updating of the attributes for Box Component
// Used by RenderBox and by JSViewAbstract

namespace OHOS::Ace {
class BoxComponentHelper {
public:
    static void SetBorderColor(
        const RefPtr<Decoration> decoration, const Color& color, const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetColor(color);
        decoration->SetBorder(border);
    }

    static void SetBorderColor(const RefPtr<Decoration> decoration, const Color& colorLeft, const Color& colorRight,
        const Color& colorTop, const Color& colorBottom, const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetLeftColor(colorLeft, option);
        border.SetRightColor(colorRight, option);
        border.SetTopColor(colorTop, option);
        border.SetBottomColor(colorBottom, option);
        decoration->SetBorder(border);
    }

    static Color GetBorderColor(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Color();
        }
        return decoration->GetBorder().Left().GetColor();
    }

    static Color GetBorderColorLeft(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Color();
        }
        return decoration->GetBorder().Left().GetColor();
    }

    static Color GetBorderColorRight(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Color();
        }
        return decoration->GetBorder().Right().GetColor();
    }

    static Color GetBorderColorTop(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Color();
        }
        return decoration->GetBorder().Top().GetColor();
    }

    static Color GetBorderColorBottom(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Color();
        }
        return decoration->GetBorder().Bottom().GetColor();
    }

    static void SetBorderRadius(
        const RefPtr<Decoration> decoration, const Dimension& radius, const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetBorderRadius(Radius(AnimatableDimension(radius, option)));
        decoration->SetBorder(border);
    }

    static void SetBorderRadius(const RefPtr<Decoration> decoration, const Dimension& radiusTopLeft,
        const Dimension& radiusTopRight, const Dimension& radiusBottomLeft, const Dimension& radiusBottomRight,
        const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetTopLeftRadius(Radius(AnimatableDimension(radiusTopLeft, option)));
        border.SetTopRightRadius(Radius(AnimatableDimension(radiusTopRight, option)));
        border.SetBottomLeftRadius(Radius(AnimatableDimension(radiusBottomLeft, option)));
        border.SetBottomRightRadius(Radius(AnimatableDimension(radiusBottomRight, option)));
        decoration->SetBorder(border);
    }

    static Radius GetBorderRadius(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Radius(0.0);
        }
        Border border = decoration->GetBorder();
        if (!border.HasRadius()) {
            return Radius(0.0);
        }
        return border.TopLeftRadius();
    }

    static Radius GetBorderRadiusTopLeft(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Radius(0.0);
        }
        Border border = decoration->GetBorder();
        if (!border.HasRadius()) {
            return Radius(0.0);
        }
        return border.TopLeftRadius();
    }

    static Radius GetBorderRadiusTopRight(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Radius(0.0);
        }
        Border border = decoration->GetBorder();
        if (!border.HasRadius()) {
            return Radius(0.0);
        }
        return border.TopRightRadius();
    }

    static Radius GetBorderRadiusBottomLeft(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Radius(0.0);
        }
        Border border = decoration->GetBorder();
        if (!border.HasRadius()) {
            return Radius(0.0);
        }
        return border.BottomLeftRadius();
    }

    static Radius GetBorderRadiusBottomRight(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Radius(0.0);
        }
        Border border = decoration->GetBorder();
        if (!border.HasRadius()) {
            return Radius(0.0);
        }
        return border.BottomRightRadius();
    }

    static void SetBorderStyle(const RefPtr<Decoration> decoration, const BorderStyle& style)
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetStyle(style);
        decoration->SetBorder(border);
    }

    static void SetBorderStyle(const RefPtr<Decoration> decoration, const BorderStyle& styleLeft,
        const BorderStyle& styleRight, const BorderStyle& styleTop, const BorderStyle& styleBottom)
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetLeftStyle(styleLeft);
        border.SetRightStyle(styleRight);
        border.SetTopStyle(styleTop);
        border.SetBottomStyle(styleBottom);
        decoration->SetBorder(border);
    }

    static BorderStyle GetBorderStyle(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return BorderStyle::NONE;
        }
        Border border = decoration->GetBorder();
        return border.Left().GetBorderStyle();
    }

    static BorderStyle GetBorderStyleLeft(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return BorderStyle::NONE;
        }
        Border border = decoration->GetBorder();
        return border.Left().GetBorderStyle();
    }

    static BorderStyle GetBorderStyleRight(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return BorderStyle::NONE;
        }
        Border border = decoration->GetBorder();
        return border.Right().GetBorderStyle();
    }

    static BorderStyle GetBorderStyleTop(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return BorderStyle::NONE;
        }
        Border border = decoration->GetBorder();
        return border.Top().GetBorderStyle();
    }

    static BorderStyle GetBorderStyleBottom(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return BorderStyle::NONE;
        }
        Border border = decoration->GetBorder();
        return border.Bottom().GetBorderStyle();
    }

    static void SetBorderWidth(
        const RefPtr<Decoration> decoration, const Dimension& width, const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetWidth(width, option);
        decoration->SetBorder(border);
    }

    static void SetBorderWidth(const RefPtr<Decoration> decoration, const Dimension& left, const Dimension& right,
        const Dimension& top, const Dimension& bottom, const AnimationOption& option = AnimationOption())
    {
        if (!decoration) {
            return;
        }
        Border border = decoration->GetBorder();
        border.SetLeftWidth(left, option);
        border.SetRightWidth(right, option);
        border.SetTopWidth(top, option);
        border.SetBottomWidth(bottom, option);
        decoration->SetBorder(border);
    }

    static Dimension GetBorderWidth(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Dimension(0);
        }
        return decoration->GetBorder().Left().GetWidth();
    }

    static Dimension GetBorderLeftWidth(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Dimension(0);
        }
        return decoration->GetBorder().Left().GetWidth();
    }

    static Dimension GetBorderRightWidth(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Dimension(0);
        }
        return decoration->GetBorder().Right().GetWidth();
    }

    static Dimension GetBorderTopWidth(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Dimension(0);
        }
        return decoration->GetBorder().Top().GetWidth();
    }

    static Dimension GetBorderBottomWidth(const RefPtr<Decoration> decoration)
    {
        if (decoration == nullptr) {
            return Dimension(0);
        }
        return decoration->GetBorder().Bottom().GetWidth();
    }
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BOX_BOX_COMPONENT_HELPER_H

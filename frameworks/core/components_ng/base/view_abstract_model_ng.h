/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

#include <utility>

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewAbstractModelNG : public ViewAbstractModel {
public:
    ~ViewAbstractModelNG() override = default;

    void SetWidth(const Dimension& width) override
    {
        ViewAbstract::SetWidth(NG::CalcLength(width));
    }

    void SetHeight(const Dimension& height) override
    {
        ViewAbstract::SetHeight(NG::CalcLength(height));
    }

    void SetMinWidth(const Dimension& minWidth) override
    {
        ViewAbstract::SetMinWidth(NG::CalcLength(minWidth));
    }

    void SetMinHeight(const Dimension& minHeight) override
    {
        ViewAbstract::SetMinHeight(NG::CalcLength(minHeight));
    }

    void SetMaxWidth(const Dimension& maxWidth) override
    {
        ViewAbstract::SetMaxWidth(NG::CalcLength(maxWidth));
    }

    void SetMaxHeight(const Dimension& maxHeight) override
    {
        ViewAbstract::SetMaxHeight(NG::CalcLength(maxHeight));
    }

    void SetBackgroundColor(const Color& color) override
    {
        ViewAbstract::SetBackgroundColor(color);
    }

    void SetBackgroundImage(const std::string& src, RefPtr<ThemeConstants> themeConstant) override
    {
        ViewAbstract::SetBackgroundImage(src);
    }

    void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) override
    {
        ViewAbstract::SetBackgroundImageRepeat(imageRepeat);
    }

    void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) override
    {
        ViewAbstract::SetBackgroundImageSize(bgImgSize);
    }

    void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) override
    {
        ViewAbstract::SetBackgroundImagePosition(bgImgPosition);
    }

    void SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle) override
    {
        ViewAbstract::SetBackgroundBlurStyle(bgBlurStyle);
    }

    void SetPadding(const Dimension& value) override
    {
        ViewAbstract::SetPadding(NG::CalcLength(value));
    }

    void SetPaddings(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right) override
    {
        NG::PaddingProperty paddings;
        paddings.top = NG::CalcLength(top);
        paddings.bottom = NG::CalcLength(bottom);
        paddings.left = NG::CalcLength(left);
        paddings.right = NG::CalcLength(right);
        ViewAbstract::SetPadding(paddings);
    }

    void SetMargin(const Dimension& value) override
    {
        ViewAbstract::SetMargin(NG::CalcLength(value));
    }

    void SetMargins(
        const Dimension& top, const Dimension& bottom, const Dimension& left, const Dimension& right) override
    {
        NG::MarginProperty margins;
        margins.top = NG::CalcLength(top);
        margins.bottom = NG::CalcLength(bottom);
        margins.left = NG::CalcLength(left);
        margins.right = NG::CalcLength(right);
        ViewAbstract::SetMargin(margins);
    }

    void SetBorderRadius(const Dimension& value) override
    {
        ViewAbstract::SetBorderRadius(value);
    }

    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override
    {
        NG::BorderRadiusProperty borderRadius;
        borderRadius.radiusTopLeft = radiusTopLeft;
        borderRadius.radiusTopRight = radiusTopRight;
        borderRadius.radiusBottomLeft = radiusBottomLeft;
        borderRadius.radiusBottomRight = radiusBottomRight;
        ViewAbstract::SetBorderRadius(borderRadius);
    }

    void SetBorderColor(const Color& value) override
    {
        ViewAbstract::SetBorderColor(value);
    }
    void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override
    {
        NG::BorderColorProperty borderColors;
        borderColors.leftColor = colorLeft;
        borderColors.rightColor = colorRight;
        borderColors.topColor = colorTop;
        borderColors.bottomColor = colorBottom;
        ViewAbstract::SetBorderColor(borderColors);
    }

    void SetBorderWidth(const Dimension& value) override
    {
        ViewAbstract::SetBorderWidth(value);
    }

    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override
    {
        NG::BorderWidthProperty borderWidth;
        borderWidth.leftDimen = left;
        borderWidth.rightDimen = right;
        borderWidth.topDimen = top;
        borderWidth.bottomDimen = bottom;
        ViewAbstract::SetBorderWidth(borderWidth);
    }

    void SetBorderStyle(const BorderStyle& value) override
    {
        ViewAbstract::SetBorderStyle(value);
    }

    void SetBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override
    {
        NG::BorderStyleProperty borderStyles;
        borderStyles.styleLeft = styleLeft;
        borderStyles.styleRight = styleRight;
        borderStyles.styleTop = styleTop;
        borderStyles.styleBottom = styleBottom;
        ViewAbstract::SetBorderStyle(borderStyles);
    }

    void SetLayoutPriority(int32_t priority) override {}

    void SetLayoutWeight(int32_t value) override
    {
        ViewAbstract::SetLayoutWeight(value);
    }

    void SetAspectRatio(float ratio) override
    {
        ViewAbstract::SetAspectRatio(ratio);
    }

    void SetAlign(const Alignment& alignment) override
    {
        ViewAbstract::SetAlign(alignment);
    }

    void SetPosition(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetPosition({ x, y });
    }

    void SetOffset(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::SetOffset({ x, y });
    }

    void MarkAnchor(const Dimension& x, const Dimension& y) override
    {
        ViewAbstract::MarkAnchor({ x, y });
    }

    void SetScale(float x, float y, float z) override
    {
        VectorF scale(x, y);
        ViewAbstract::SetScale(scale);
    }

    void SetPivot(const Dimension& x, const Dimension& y) override
    {
        DimensionOffset center(x, y);
        ViewAbstract::SetPivot(center);
    }

    void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) override
    {
        ViewAbstract::SetTranslate(NG::Vector3F(x.ConvertToPx(), y.ConvertToPx(), z.ConvertToPx()));
    }

    void SetRotate(float x, float y, float z, float angle) override
    {
        ViewAbstract::SetRotate(NG::Vector4F(x, y, z, angle));
    }

    void SetTransformMatrix(const std::vector<float>& matrix) override
    {
        NG::ViewAbstract::SetTransformMatrix(
            Matrix4(matrix[0], matrix[4], matrix[8], matrix[12], matrix[1], matrix[5], matrix[9], matrix[13], matrix[2],
                matrix[6], matrix[10], matrix[14], matrix[3], matrix[7], matrix[11], matrix[15]));
    }

    void SetOpacity(double opacity) override
    {
        ViewAbstract::SetOpacity(opacity);
    }

    void SetTransition(const NG::TransitionOptions& transitionOptions) override
    {
        ViewAbstract::SetTransition(transitionOptions);
    }

    void SetOverlay(const std::string& text, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY) override
    {}

    void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) override
    {
        ViewAbstract::SetVisibility(visible);
    }

    void SetSharedTransition(const SharedTransitionOption& option) override {}

    void SetGeometryTransition(const std::string& id) override {}

    void SetFlexBasis(const Dimension& value) override
    {
        ViewAbstract::SetFlexBasis(value);
    }

    void SetAlignSelf(FlexAlign value) override
    {
        ViewAbstract::SetAlignSelf(value);
    }

    void SetFlexShrink(float value) override
    {
        ViewAbstract::SetFlexShrink(value);
    }

    void SetFlexGrow(float value) override
    {
        ViewAbstract::SetFlexGrow(value);
    }

    void SetDisplayIndex(int32_t value) override
    {
        ViewAbstract::SetDisplayIndex(value);
    }

    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) override
    {
        ViewAbstract::SetOnClick(std::move(tapEventFunc));
    }

    void SetOnTouch(TouchEventFunc&& touchEventFunc) override
    {
        ViewAbstract::SetOnTouch(std::move(touchEventFunc));
    }

    void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) override
    {
        ViewAbstract::SetOnKeyEvent(std::move(onKeyCallback));
    }

    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override
    {
        ViewAbstract::SetOnMouse(std::move(onMouseEventFunc));
    }

    void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) override
    {
        ViewAbstract::SetOnHover(std::move(onHoverEventFunc));
    }

    void SetOnDelete(std::function<void()>&& onDeleteCallback) override {}

    void SetOnAppear(std::function<void()>&& onAppearCallback) override
    {
        ViewAbstract::SetOnAppear(std::move(onAppearCallback));
    }

    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override
    {
        ViewAbstract::SetOnDisappear(std::move(onDisAppearCallback));
    }

    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override {}

    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override {}

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override
    {
        ViewAbstract::SetResponseRegion(responseRegion);
    }

    void SetEnabled(bool enabled) override
    {
        ViewAbstract::SetEnabled(enabled);
    }

    void SetTouchable(bool touchable) override
    {
        ViewAbstract::SetTouchable(touchable);
    }

    void SetFocusable(bool focusable) override
    {
        ViewAbstract::SetFocusable(focusable);
    }

    void SetFocusNode(bool focus) override {}
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

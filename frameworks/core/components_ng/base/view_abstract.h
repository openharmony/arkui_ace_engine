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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H

#include <cstdint>
#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/offset.h"
#include "base/memory/referenced.h"
#include "core/common/container.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/property/gradient_property.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ViewAbstract {
public:
    static void SetWidth(const CalcLength& width);
    static void SetHeight(const CalcLength& height);
    static void SetMinWidth(const CalcLength& minWidth);
    static void SetMinHeight(const CalcLength& minHeight);
    static void SetMaxWidth(const CalcLength& maxWidth);
    static void SetMaxHeight(const CalcLength& maxHeight);

    static void SetAspectRatio(float ratio);
    static void SetLayoutWeight(int32_t value);

    static void SetBackgroundColor(const Color& color);
    static void SetBackgroundImage(const std::string& src);
    static void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat);
    static void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize);
    static void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition);
    static void SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle);
    static void SetPadding(const CalcLength& value);
    static void SetPadding(const PaddingProperty& value);
    static void SetBorderRadius(const BorderRadiusProperty& value);
    static void SetBorderRadius(const Dimension& value);
    static void SetBorderColor(const Color& value);
    static void SetBorderColor(const BorderColorProperty& value);
    static void SetBorderWidth(const Dimension& value);
    static void SetBorderWidth(const BorderWidthProperty& value);
    static void SetBorderStyle(const BorderStyle& value);
    static void SetBorderStyle(const BorderStyleProperty& value);
    static void SetOpacity(double opacity);

    // decoration
    static void SetBackdropBlur(const Dimension& radius);
    static void SetFrontBlur(const Dimension& radius);
    static void SetBackShadow(const Shadow& shadow);
    static void SetLinearGradient(const NG::Gradient& gradient);

    // layout
    static void SetAlign(Alignment alignment);
    static void SetVisibility(VisibleType visible);

    // position
    static void SetPosition(const OffsetT<Dimension>& value);
    static void SetOffset(const OffsetT<Dimension>& value);
    static void MarkAnchor(const OffsetT<Dimension>& value);

    // render position
    static void SetZIndex(int32_t value);

    // transform
    static void SetScale(const NG::VectorF& value);
    static void SetPivot(const DimensionOffset& value);
    static void SetTranslate(const NG::Vector3F& value);
    static void SetRotate(const NG::Vector4F& value);

    // event
    static void SetOnClick(GestureEventFunc&& clickEventFunc);
    static void SetOnTouch(TouchEventFunc&& touchEventFunc);
    static void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc);
    static void SetOnHover(OnHoverEventFunc&& onHoverEventFunc);
    static void SetHoverEffect(HoverEffectType hoverEffect);
    static void SetFocusType(FocusType type);
    static void SetFocusable(bool focusable);
    static void SetOnFocus(OnFocusFunc&& onFocusCallback);
    static void SetOnBlur(OnBlurFunc&& onBlurCallback);
    static void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback);
    static void SetOnAppear(std::function<void()>&& onAppear);
    static void SetOnDisappear(std::function<void()>&& onDisappear);
    static void SetOnAreaChanged(
        std::function<void(const RectF& oldRect, const OffsetF& oldOrigin, const RectF& rect, const OffsetF& origin)>&&
            onAreaChanged);

    // flex properties
    static void SetAlignSelf(int32_t value);
    static void SetFlexShrink(float value);
    static void SetFlexGrow(float value);
    static void SetDisplayIndex(float value);

    // Bind properties
    static void BindPopup(const RefPtr<PopupParam>& param);
    // inspector
    static void SetInspectorId(const std::string& inspectorId);
    // transition
    static void SetTransition(const TransitionOptions& options);

    static void Pop();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H

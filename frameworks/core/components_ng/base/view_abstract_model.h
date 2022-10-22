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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"

namespace OHOS::Ace {

using ClickEventFunc = std::function<void(const ClickInfo* info)>;
using RemoteCallback = std::function<void(const BaseEventInfo* info)>;

class ACE_EXPORT ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    // basic size
    virtual void SetWidth(const Dimension& width) = 0;
    virtual void SetHeight(const Dimension& height) = 0;
    virtual void SetMinWidth(const Dimension& minWidth) = 0;
    virtual void SetMinHeight(const Dimension& minHeight) = 0;
    virtual void SetMaxWidth(const Dimension& maxWidth) = 0;
    virtual void SetMaxHeight(const Dimension& maxHeight) = 0;

    // box props
    virtual void SetBackgroundColor(const Color& color) = 0;
    virtual void SetBackgroundImage(const std::string& src, RefPtr<ThemeConstants> themeConstant) = 0;
    virtual void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) = 0;
    virtual void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) = 0;
    virtual void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) = 0;
    virtual void SetBackgroundBlurStyle(const BlurStyle& bgBlurStyle) = 0;
    virtual void SetPadding(const Dimension& value) = 0;
    virtual void SetPaddings(const std::optional<Dimension>& top, const std::optional<Dimension>& bottom,
        const std::optional<Dimension>& left, const std::optional<Dimension>& right) = 0;
    virtual void SetMargin(const Dimension& value) = 0;
    virtual void SetMargins(const std::optional<Dimension>& top, const std::optional<Dimension>& bottom,
        const std::optional<Dimension>& left, const std::optional<Dimension>& right) = 0;
    virtual void SetBorderRadius(const Dimension& value) = 0;
    virtual void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) = 0;
    virtual void SetBorderColor(const Color& value) = 0;
    virtual void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) = 0;
    virtual void SetBorderWidth(const Dimension& value) = 0;
    virtual void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) = 0;
    virtual void SetBorderStyle(const BorderStyle& value) = 0;
    virtual void SetBorderStyle(const std::optional<BorderStyle>& styleLeft,
        const std::optional<BorderStyle>& styleRight, const std::optional<BorderStyle>& styleTop,
        const std::optional<BorderStyle>& styleBottom) = 0;
    virtual void SetBorderImage(const RefPtr<BorderImage>& borderImage, uint8_t bitset) = 0;
    virtual void SetBorderImageGradient(const NG::Gradient& gradient) = 0;

    // layout
    virtual void SetLayoutPriority(int32_t priority) = 0;
    virtual void SetLayoutWeight(int32_t value) = 0;
    virtual void SetLayoutDirection(TextDirection value) = 0;
    virtual void SetAspectRatio(float ratio) = 0;
    virtual void SetAlign(const Alignment& alignment) = 0;
    virtual void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) = 0;
    virtual void SetUseAlign(
        AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset) = 0;
    virtual void SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset,
        const RefPtr<GridContainerInfo>& info, GridSizeType type = GridSizeType::UNDEFINED) = 0;
    virtual void SetZIndex(int32_t value) = 0;

    // position
    virtual void SetPosition(const Dimension& x, const Dimension& y) = 0;
    virtual void SetOffset(const Dimension& x, const Dimension& y) = 0;
    virtual void MarkAnchor(const Dimension& x, const Dimension& y) = 0;

    // transforms
    virtual void SetScale(float x, float y, float z) = 0;
    virtual void SetPivot(const Dimension& x, const Dimension& y) = 0;
    virtual void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetRotate(float x, float y, float z, float angle) = 0;
    virtual void SetTransformMatrix(const std::vector<float>& matrix) = 0;

    // display props
    virtual void SetOpacity(double opacity, bool passThrough = false) = 0;
    virtual void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) = 0;
    virtual void SetOverlay(const std::string& text, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY) = 0;
    virtual void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) = 0;
    virtual void SetSharedTransition(const SharedTransitionOption& option) = 0;
    virtual void SetGeometryTransition(const std::string& id) = 0;
    virtual void SetMotionPath(const MotionPathOption& option) = 0;

    // flex props
    virtual void SetFlexBasis(const Dimension& value) = 0;
    virtual void SetAlignSelf(FlexAlign value) = 0;
    virtual void SetFlexShrink(float value) = 0;
    virtual void SetFlexGrow(float value) = 0;
    virtual void SetDisplayIndex(int32_t value) = 0;

    // gradient
    virtual void SetLinearGradient(const NG::Gradient& gradient) = 0;
    virtual void SetSweepGradient(const NG::Gradient& gradient) = 0;
    virtual void SetRadialGradient(const NG::Gradient& gradient) = 0;

    // clip
    virtual void SetClipShape(const RefPtr<BasicShape>& shape) = 0;
    virtual void SetClipEdge(bool isClip) = 0;

    // effects
    virtual void SetMask(const RefPtr<BasicShape>& shape) = 0;
    virtual void SetBackdropBlur(const Dimension& radius) = 0;
    virtual void SetFrontBlur(const Dimension& radius) = 0;
    virtual void SetBackShadow(const std::vector<Shadow>& shadows) = 0;
    virtual void SetColorBlend(const Color& value) = 0;
    virtual void SetWindowBlur(float progress, WindowBlurStyle blurStyle) = 0;
    virtual void SetBrightness(const Dimension& value) = 0;
    virtual void SetGrayScale(const Dimension& value) = 0;
    virtual void SetContrast(const Dimension& value) = 0;
    virtual void SetSaturate(const Dimension& value) = 0;
    virtual void SetSepia(const Dimension& value) = 0;
    virtual void SetInvert(const Dimension& value) = 0;
    virtual void SetHueRotate(float value) = 0;

    // event
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) = 0;
    virtual void SetOnTouch(TouchEventFunc&& touchEventFunc) = 0;
    virtual void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) = 0;
    virtual void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) = 0;
    virtual void SetOnHover(OnHoverEventFunc&& onHoverEventFunc) = 0;
    virtual void SetOnDelete(std::function<void()>&& onDeleteCallback) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) = 0;
    virtual void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) = 0;
    virtual void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) = 0;
    virtual void SetOnFocus(OnFocusFunc&& onFocusCallback) = 0;
    virtual void SetOnBlur(OnBlurFunc&& onBlurCallback) = 0;
    virtual void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) = 0;
    virtual void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) = 0;
    virtual void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) = 0;
    virtual void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) = 0;
    virtual void SetOnDrop(NG::OnDragDropFunc&& onDrop) = 0;

    // interact
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) = 0;
    virtual void SetEnabled(bool enabled) = 0;
    virtual void SetTouchable(bool touchable) = 0;
    virtual void SetFocusable(bool focusable) = 0;
    virtual void SetFocusNode(bool focus) = 0;
    virtual void SetTabIndex(int32_t index) = 0;
    virtual void SetFocusOnTouch(bool isSet) = 0;
    virtual void SetDefaultFocus(bool isSet) = 0;
    virtual void SetGroupDefaultFocus(bool isSet) = 0;
    virtual void SetInspectorId(const std::string& inspectorId) = 0;
    virtual void SetRestoreId(int32_t restoreId) = 0;
    virtual void SetDebugLine(const std::string& line) = 0;
    virtual void SetHoverEffect(HoverEffectType hoverEffect) = 0;
    virtual void SetHitTestMode(NG::HitTestMode hitTestMode) = 0;

    // accessibility
    virtual void SetAccessibilityGroup(bool accessible) = 0;
    virtual void SetAccessibilityText(const std::string& text) = 0;
    virtual void SetAccessibilityDescription(const std::string& description) = 0;
    virtual void SetAccessibilityImportance(const std::string& importance) = 0;

private:
    static std::unique_ptr<ViewAbstractModel> instance_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

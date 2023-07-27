/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
#include <mutex>
#include <optional>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/memory/ace_type.h"
#include "base/utils/macros.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/event/touch_event.h"
#include "core/gestures/gesture_info.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {

using ClickEventFunc = std::function<void(const ClickInfo* info)>;
using RemoteCallback = std::function<void(const BaseEventInfo* info)>;
using OnNewDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>;

enum class ResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONG_PRESS,
};

class ACE_FORCE_EXPORT ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    // basic size
    virtual void SetWidth(const CalcDimension& width) = 0;
    virtual void SetHeight(const CalcDimension& height) = 0;
    virtual void ClearWidthOrHeight(bool isWidth) = 0;
    virtual void SetMinWidth(const CalcDimension& minWidth) = 0;
    virtual void SetMinHeight(const CalcDimension& minHeight) = 0;
    virtual void SetMaxWidth(const CalcDimension& maxWidth) = 0;
    virtual void SetMaxHeight(const CalcDimension& maxHeight) = 0;
    virtual void ResetMinSize(bool resetWidth) = 0;
    virtual void ResetMaxSize(bool resetWidth) = 0;

    // box props
    virtual void SetBackgroundColor(const Color& color) = 0;
    virtual void SetBackgroundImage(const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) = 0;
    virtual void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) = 0;
    virtual void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) = 0;
    virtual void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) = 0;
    virtual void SetBackgroundBlurStyle(const BlurStyleOption& bgBlurStyle) = 0;
    virtual void SetBackgroundEffect(const EffectOption& effectOption) {}
    virtual void SetForegroundBlurStyle(const BlurStyleOption& fgBlurStyle) {}
    virtual void SetSphericalEffect(double radio) {}
    virtual void SetPixelStretchEffect(PixStretchEffectOption& option) {}
    virtual void SetLightUpEffect(double radio) {}

    virtual void SetPadding(const CalcDimension& value) = 0;
    virtual void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) = 0;
    virtual void SetMargin(const CalcDimension& value) = 0;
    virtual void SetMargins(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) = 0;
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
    virtual void SetGrid(
        std::optional<uint32_t> span, std::optional<int32_t> offset, GridSizeType type = GridSizeType::UNDEFINED) = 0;
    virtual void SetZIndex(int32_t value) = 0;

    // position
    virtual void SetPosition(const Dimension& x, const Dimension& y) = 0;
    virtual void SetOffset(const Dimension& x, const Dimension& y) = 0;
    virtual void MarkAnchor(const Dimension& x, const Dimension& y) = 0;

    // transforms
    virtual void SetScale(float x, float y, float z) = 0;
    virtual void SetPivot(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetRotate(float x, float y, float z, float angle, float perspective = 0.0f) = 0;
    virtual void SetTransformMatrix(const std::vector<float>& matrix) = 0;

    // display props
    virtual void SetOpacity(double opacity, bool passThrough = false) = 0;
    virtual void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) = 0;
    virtual void SetChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect, bool passThrough = false) = 0;
    virtual void SetOverlay(const std::string& text, const std::function<void()>&& buildFunc,
        const std::optional<Alignment>& align, const std::optional<Dimension>& offsetX,
        const std::optional<Dimension>& offsetY) = 0;
    virtual void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) = 0;
    virtual void SetSharedTransition(
        const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option) = 0;
    virtual void SetGeometryTransition(const std::string& id, bool followWithoutTransition = false) = 0;
    virtual void SetMotionPath(const MotionPathOption& option) = 0;
    virtual void SetRenderGroup(bool isRenderGroup) = 0;
    virtual void SetRenderFit(RenderFit renderFit) = 0;

    // flex props
    virtual void SetFlexBasis(const Dimension& value) = 0;
    virtual void SetAlignSelf(FlexAlign value) = 0;
    virtual void SetFlexShrink(float value) = 0;
    virtual void SetFlexGrow(float value) = 0;
    virtual void SetDisplayIndex(int32_t value) = 0;
    virtual void ResetFlexShrink() = 0;

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
    virtual void SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara) = 0;

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
    virtual void SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue) = 0;
    virtual void SetUseEffect(bool useEffect) = 0;

    // event
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc) = 0;
    virtual void SetOnTouch(TouchEventFunc&& touchEventFunc) = 0;
    virtual void SetOnKeyEvent(OnKeyCallbackFunc&& onKeyCallback) = 0;
    virtual void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) = 0;
    virtual void SetOnHover(OnHoverFunc&& onHoverEventFunc) = 0;
    virtual void SetOnDelete(std::function<void()>&& onDeleteCallback) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) = 0;
    virtual void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) = 0;
    virtual void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) = 0;
    virtual void SetOnFocus(OnFocusFunc&& onFocusCallback) = 0;
    virtual void SetOnBlur(OnBlurFunc&& onBlurCallback) = 0;
    virtual void SetDraggable(bool draggable) = 0;
    virtual void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) = 0;
    virtual void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) = 0;
    virtual void SetOnDragEnd(OnNewDragFunc&& onDragEnd) = 0;
    virtual void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) = 0;
    virtual void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) = 0;
    virtual void SetOnDrop(NG::OnDragDropFunc&& onDrop) = 0;
    virtual void SetAllowDrop(const std::set<std::string>& allowDrop) = 0;
    virtual void SetOnVisibleChange(
        std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratios) = 0;
    virtual void SetOnAreaChanged(
        std::function<void(const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)>&&
            onAreaChanged) = 0;

    // Disable event when the param is undefined.
    virtual void DisableOnClick() = 0;
    virtual void DisableOnTouch() = 0;
    virtual void DisableOnKeyEvent() = 0;
    virtual void DisableOnHover() = 0;
    virtual void DisableOnMouse() = 0;
    virtual void DisableOnAppear() = 0;
    virtual void DisableOnDisAppear() = 0;
    virtual void DisableOnAreaChange() = 0;
    virtual void DisableOnFocus() = 0;
    virtual void DisableOnBlur() = 0;

    // interact
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) = 0;
    virtual void SetMouseResponseRegion(const std::vector<DimensionRect>& responseRegion) {};
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
    virtual void SetKeyboardShortcut(const std::string& value, const std::vector<ModifierKey>& keys,
        std::function<void()>&& onKeyboardShortcutAction) = 0;

    // obscured
    virtual void SetObscured(const std::vector<ObscuredReasons>& reasons) = 0;

    // background
    virtual void BindBackground(std::function<void()>&& buildFunc, const Alignment& align) = 0;

    // popup and menu
    virtual void BindPopup(const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode) = 0;
    virtual void BindMenu(
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const NG::MenuParam& menuParam) = 0;
    virtual void BindContextMenu(
        ResponseType type, std::function<void()>& buildFunc, const NG::MenuParam& menuParam) = 0;
    virtual void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear) = 0;
    virtual void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear) = 0;

    // accessibility
    virtual void SetAccessibilityGroup(bool accessible) = 0;
    virtual void SetAccessibilityText(const std::string& text) = 0;
    virtual void SetAccessibilityDescription(const std::string& description) = 0;
    virtual void SetAccessibilityImportance(const std::string& importance) = 0;

    // progress mask
    virtual void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>& progress) = 0;
    // foregroundColor
    virtual void SetForegroundColor(const Color& color) = 0;
    virtual void SetForegroundColorStrategy(const ForegroundColorStrategy& strategy) = 0;

    // custom animation properties
    virtual void CreateAnimatablePropertyFloat(const std::string& propertyName, float value,
        const std::function<void(float)>& onCallbackEvent) = 0;
    virtual void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value) = 0;

    virtual void CreateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<NG::CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<NG::CustomAnimatableArithmetic>&)>& onCallbackEvent) = 0;
    virtual void UpdateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<NG::CustomAnimatableArithmetic>& value) = 0;
    virtual void UpdateSafeAreaExpandOpts(const NG::SafeAreaExpandOpts& opts) = 0;
private:
    static std::unique_ptr<ViewAbstractModel> instance_;
    static std::mutex mutex_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

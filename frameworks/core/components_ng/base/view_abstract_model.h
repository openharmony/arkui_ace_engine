/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/blend_mode.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/focus_box.h"
#include "core/components_ng/event/focus_event_handler.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/overlay/content_cover_param.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/sheet_style.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/property/transition_property.h"
#include "core/components_ng/property/layout_policy_property.h"
#include "core/event/ace_events.h"
#include "core/event/key_event.h"
#include "core/event/mouse_event.h"
#include "core/gestures/gesture_info.h"
#include "core/image/image_source_info.h"

namespace OHOS::Ace {

using ClickEventFunc = std::function<void(const ClickInfo* info)>;
using RemoteCallback = std::function<void(const BaseEventInfo* info)>;
using OnNewDragFunc = std::function<void(const RefPtr<OHOS::Ace::DragEvent>&)>;
using BiasPair = std::pair<float, float>;
enum class ResponseType : int32_t {
    RIGHT_CLICK = 0,
    LONG_PRESS,
};
class SpanString;
enum PopupType { POPUPTYPE_TEXTCOLOR, POPUPTYPE_POPUPCOLOR, POPUPTYPE_MASKCOLOR };
enum PopupOptionsType {
    POPUP_OPTIONTYPE_WIDTH,
    POPUP_OPTIONTYPE_ARROWWIDTH,
    POPUP_OPTIONTYPE_ARROWHEIGHT,
    POPUP_OPTIONTYPE_RADIUS,
    POPUP_OPTIONTYPE_OUTLINEWIDTH,
    POPUP_OPTIONTYPE_BORDERWIDTH,
    POPUP_OPTIONTYPE_OFFSETDX,
    POPUP_OPTIONTYPE_OFFSETDY,
};
class ACE_FORCE_EXPORT ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    virtual void CreateWithForegroundColorResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithOuterBorderColorResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithOuterBorderRadiusResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithLightColorResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void CreateWithOuterBorderWidthResourceObj(const RefPtr<ResourceObject>& resObj) {};
    virtual void ResetResObj(const std::string& key) {};
    
    // basic size
    virtual void SetWidth(const CalcDimension& width) = 0;
    virtual void SetWidth(const RefPtr<ResourceObject>& resObj) {}
    virtual void SetHeight(const CalcDimension& height) = 0;
    virtual void UpdateLayoutPolicyProperty(const LayoutCalPolicy layoutPolicy, bool isWidth) = 0;
    virtual void SetHeight(const RefPtr<ResourceObject>& resObj) {}
    virtual void ClearWidthOrHeight(bool isWidth) = 0;
    virtual void SetMinWidth(const CalcDimension& minWidth) = 0;
    virtual void SetMinWidth(const RefPtr<ResourceObject>& resObj) {}
    virtual void SetMinHeight(const CalcDimension& minHeight) = 0;
    virtual void SetMinHeight(const RefPtr<ResourceObject>& resObj) {}
    virtual void SetMaxWidth(const CalcDimension& maxWidth) = 0;
    virtual void SetMaxWidth(const RefPtr<ResourceObject>& resObj) {}
    virtual void SetMaxHeight(const CalcDimension& maxHeight) = 0;
    virtual void SetMaxHeight(const RefPtr<ResourceObject>& resObj) {}
    virtual void ResetMinSize(bool resetWidth) = 0;
    virtual void ResetMaxSize(bool resetWidth) = 0;

    // box props
    virtual void SetBackgroundColor(const Color& color) = 0;
    virtual void SetBackgroundColorWithResourceObj(const Color& color, const RefPtr<ResourceObject>& resObj) = 0;
    virtual void SetBackgroundImage(const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) = 0;
    virtual void SetBackgroundImageWithResourceObj(
        const RefPtr<ResourceObject>& resObj, const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) = 0;
    virtual void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) = 0;
    virtual void SetBackgroundImageSize(BackgroundImageSize& bgImgSize) = 0;
    virtual void SetBackgroundImageSizeUpdateFunc(
        BackgroundImageSize& bgImgSize, const RefPtr<ResourceObject>& resObj, const std::string direction) = 0;
    virtual void SetBackgroundImagePosition(BackgroundImagePosition& bgImgPosition) = 0;
    virtual void ClearResObj(const std::string resObjName) = 0;
    virtual void SetBackgroundBlurStyle(
        const BlurStyleOption& bgBlurStyle, const SysOptions& sysOptions = SysOptions()) = 0;
    virtual void SetBackgroundEffect(const EffectOption& effectOption, const SysOptions& sysOptions = SysOptions()) {}
    virtual void SetBackgroundImageSyncMode(bool syncMode) {}
    virtual void SetBackgroundImageResizableSlice(ImageResizableSlice& slice) = 0;
    virtual void SetForegroundBlurStyle(const BlurStyleOption& fgBlurStyle, const SysOptions& sysOptions = SysOptions())
    {}
    virtual void SetForegroundEffect(float radius) {}
    virtual void SetSphericalEffect(double radio) {}
    virtual void SetPixelStretchEffect(PixStretchEffectOption& option) {}
    virtual void SetLightUpEffect(double radio) {}

    virtual void SetPadding(const CalcDimension& value) = 0;
    virtual void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) = 0;
    virtual void SetPaddings(const NG::PaddingProperty& paddings) = 0;
    virtual void SetPadding(const RefPtr<ResourceObject>& resObj) {}
    virtual void SetMargin(const CalcDimension& value) = 0;
    virtual void SetMargins(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) = 0;
    virtual void SetMargins(const NG::MarginProperty& margins) = 0;
    virtual void SetMargin(const RefPtr<ResourceObject>& resObj) {}
    virtual void ResetSafeAreaPadding() = 0;
    virtual void SetSafeAreaPadding(const CalcDimension& value) = 0;
    virtual void SetSafeAreaPaddings(const NG::PaddingProperty& paddings) = 0;
    virtual void SetSafeAreaPaddings(const std::optional<CalcDimension>& top,
        const std::optional<CalcDimension>& bottom, const std::optional<CalcDimension>& left,
        const std::optional<CalcDimension>& right) = 0;
    virtual void SetBorderRadius(const Dimension& value) = 0;
    virtual void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) = 0;
    virtual void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) = 0;
    virtual void SetBorderRadius(const RefPtr<ResourceObject>& resobj) {}
    virtual void SetBorderColor(const Color& value) = 0;
    virtual void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) = 0;
    virtual void SetBorderColor(const NG::BorderColorProperty& borderColors) = 0;
    virtual void SetBorderColor(const RefPtr<ResourceObject>& resobj) {}
    virtual void SetBorderWidth(const Dimension& value) = 0;
    virtual void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) = 0;
    virtual void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom, bool isLocalized) = 0;
    virtual void SetBorderWidth(const RefPtr<ResourceObject>& resobj) {}
    virtual void SetBorderWidth(const NG::BorderWidthProperty& value) {}
    virtual void SetBorderStyle(const BorderStyle& value) = 0;
    virtual void SetBorderStyle(const std::optional<BorderStyle>& styleLeft,
        const std::optional<BorderStyle>& styleRight, const std::optional<BorderStyle>& styleTop,
        const std::optional<BorderStyle>& styleBottom) = 0;
    virtual void SetDashGap(const Dimension& value) {}
    virtual void SetDashGap(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) {}
    virtual void SetDashGap(const NG::BorderWidthProperty& value) {}
    virtual void SetDashWidth(const Dimension& value) {}
    virtual void SetDashWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) {}
    virtual void SetDashWidth(const NG::BorderWidthProperty& value) {}
    virtual void SetBorderImage(const RefPtr<BorderImage>& borderImage, uint8_t bitset) = 0;
    virtual void SetBorderImageGradient(const NG::Gradient& gradient) = 0;

    // visual
    virtual void SetVisualEffect(const OHOS::Rosen::VisualEffect* visualEffect) {};
    virtual void SetBackgroundFilter(const OHOS::Rosen::Filter* backgroundFilter) {};
    virtual void SetForegroundFilter(const OHOS::Rosen::Filter* foregroundFilter) {};
    virtual void SetCompositingFilter(const OHOS::Rosen::Filter* compositingFilter) {};
    virtual void SetBrightnessBlender(const OHOS::Rosen::BrightnessBlender* brightnessBlender) {};

    // outerBorder
    virtual void SetOuterBorderRadius(const Dimension& value) = 0;
    virtual void SetOuterBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) = 0;
    virtual void SetOuterBorderRadius(const NG::BorderRadiusProperty& borderRadius) = 0;
    virtual void SetOuterBorderColor(const Color& value) = 0;
    virtual void SetOuterBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) = 0;
    virtual void SetOuterBorderColor(const NG::BorderColorProperty& borderColors) = 0;
    virtual void SetOuterBorderWidth(const Dimension& value) = 0;
    virtual void SetOuterBorderWidthNew(const NG::BorderWidthProperty& property) = 0;
    virtual void SetOuterBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) = 0;
    virtual void SetOuterBorderStyle(const BorderStyle& value) = 0;
    virtual void SetOuterBorderStyle(const std::optional<BorderStyle>& styleLeft,
        const std::optional<BorderStyle>& styleRight, const std::optional<BorderStyle>& styleTop,
        const std::optional<BorderStyle>& styleBottom) = 0;

    // layout
    virtual void SetLayoutPriority(int32_t priority) = 0;
    virtual void SetLayoutWeight(float value) = 0;
    virtual void SetChainWeight(const NG::ChainWeightPair& value) = 0;
    virtual void SetPixelRound(uint16_t value) = 0;
    virtual void SetLayoutDirection(TextDirection value) = 0;
    virtual void SetAspectRatio(float ratio) = 0;
    virtual void ResetAspectRatio() = 0;
    virtual void SetAlign(const Alignment& alignment) = 0;
    virtual void SetAlign(const std::string& localizedAlignment) = 0;
    virtual void SetLayoutGravity(const Alignment& alignment) = 0;
    virtual void SetIsMirrorable(const bool& isMirrorable) = 0;
    virtual void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) = 0;
    virtual void SetChainStyle(const ChainInfo& chainInfo) = 0;
    virtual void SetBias(const BiasPair& biasPair) = 0;
    virtual void SetUseAlign(
        AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset) = 0;
    virtual void SetGrid(
        std::optional<uint32_t> span, std::optional<int32_t> offset, GridSizeType type = GridSizeType::UNDEFINED) = 0;
    virtual void SetZIndex(int32_t value) = 0;

    // position
    virtual void SetPosition(const Dimension& x, const Dimension& y) = 0;
    virtual void SetPosition(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) {}
    virtual void SetOffset(const Dimension& x, const Dimension& y) = 0;
    virtual void SetOffset(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) {}
    virtual void SetPositionEdges(const EdgesParam& value) {};
    virtual void SetOffsetEdges(const EdgesParam& value) {};
    virtual void MarkAnchor(const Dimension& x, const Dimension& y) = 0;
    virtual void MarkAnchor(const Dimension& x, const Dimension& y,
        const RefPtr<ResourceObject>& xresObj, const RefPtr<ResourceObject>& yresObj) {}
    virtual void ResetPosition() {};

    // transforms
    virtual void SetScale(float x, float y, float z) = 0;
    virtual void SetPivot(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) = 0;
    virtual void SetRotate(float x, float y, float z, float angle, float perspective = 0.0f) = 0;
    virtual void SetRotateAngle(float x, float y, float z, float perspective = 0.0f) = 0;
    virtual void SetTransformMatrix(const std::vector<float>& matrix) = 0;
    virtual void SetTransform3DMatrix(const std::vector<float>& matrix) = 0;

    // display props
    virtual void SetOpacity(double opacity, bool passThrough = false) = 0;
    virtual void CreateWithOpacityResourceObj(const RefPtr<ResourceObject>& resobj) {};
    virtual void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) = 0;
    virtual void CleanTransition() {};
    virtual void SetChainedTransition(
        const RefPtr<NG::ChainedTransitionEffect>& effect, NG::TransitionFinishCallback&& finishCallback = nullptr) = 0;
    virtual void SetOverlay(const std::string& text, std::function<void()>&& buildFunc,
        const RefPtr<NG::FrameNode>& contentNode, const std::optional<Alignment>& align,
        const std::optional<Dimension>& offsetX, const std::optional<Dimension>& offsetY, NG::OverlayType type) = 0;
    virtual void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) = 0;
    virtual void SetSharedTransition(
        const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option) = 0;
    virtual void SetGeometryTransition(const std::string& id,
        bool followWithoutTransition = false, bool doRegisterSharedTransition = true) = 0;
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
    virtual void SetBackdropBlur(
        const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions = SysOptions()) = 0;
    virtual void SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara) = 0;

    virtual void SetDynamicDim(float DimDegree) = 0;
    virtual void SetDynamicLightUp(float rate, float lightUpDegree) = 0;
    virtual void SetBgDynamicBrightness(const BrightnessOption& brightnessOption) = 0;
    virtual void SetFgDynamicBrightness(const BrightnessOption& brightnessOption) = 0;

    virtual void SetFrontBlur(
        const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions = SysOptions()) = 0;
    virtual void SetMotionBlur(const MotionBlurOption& motionBlurOption) {}
    virtual void SetBackShadow(const std::vector<Shadow>& shadows) = 0;
    virtual void SetBlendMode(BlendMode blendMode) = 0;
    virtual void SetBlendApplyType(BlendApplyType blendApplyType) = 0;
    virtual void SetColorBlend(const Color& value) = 0;
    virtual void CreateWithColorBlendResourceObj(const RefPtr<ResourceObject>& resobj) {};
    virtual void SetWindowBlur(float progress, WindowBlurStyle blurStyle) = 0;
    virtual void SetBrightness(const Dimension& value) = 0;
    virtual void SetGrayScale(const Dimension& value) = 0;
    virtual void SetContrast(const Dimension& value) = 0;
    virtual void SetSaturate(const Dimension& value) = 0;
    virtual void SetSepia(const Dimension& value) = 0;
    virtual void SetInvert(const InvertVariant& value) = 0;
    virtual void SetSystemBarEffect(bool systemBarEffect) = 0;
    virtual void SetHueRotate(float value) = 0;
    virtual void SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue) = 0;
    virtual void SetUseEffect(bool useEffect, EffectType effectType) = 0;
    virtual void SetUseShadowBatching(bool useShadowBatching) = 0;
    virtual void SetFreeze(bool freeze) = 0;

    // event
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
        double distanceThreshold = std::numeric_limits<double>::infinity()) = 0;
    virtual void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
        Dimension distanceThreshold) = 0;
    virtual void SetOnGestureJudgeBegin(NG::GestureJudgeFunc&& gestureJudgeFunc) = 0;
    virtual void SetOnTouchIntercept(NG::TouchInterceptFunc&& touchInterceptFunc) = 0;
    virtual void SetShouldBuiltInRecognizerParallelWith(
        NG::ShouldBuiltInRecognizerParallelWithFunc&& shouldBuiltInRecognizerParallelWithFunc) = 0;
    virtual void SetOnGestureRecognizerJudgeBegin(
        NG::GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc, bool exposeInnerGestureFlag) = 0;
    virtual void SetOnTouchTestDone(NG::TouchTestDoneCallback&& touchTestDoneCallback) = 0;
    virtual void SetOnTouch(TouchEventFunc&& touchEventFunc) = 0;
    virtual void SetOnKeyEvent(OnKeyConsumeFunc&& onKeyCallback) = 0;
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void SetOnCrownEvent(OnCrownCallbackFunc&& onCrownCallback) = 0;
#endif
    virtual void SetOnKeyPreIme(OnKeyConsumeFunc&& onKeyCallback) {}
    virtual void SetOnKeyEventDispatch(OnKeyEventDispatchFunc&& onKeyCallback) {}
    virtual void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) = 0;
    virtual void SetOnAxisEvent(OnAxisEventFunc&& onAxisEventFunc) = 0;
    virtual void SetOnHover(OnHoverFunc&& onHoverEventFunc) = 0;
    virtual void SetOnHoverMove(OnHoverMoveFunc&& onHoverMoveEventFunc) = 0;
    virtual void SetOnAccessibilityHover(OnAccessibilityHoverFunc&& onAccessibilityHoverEventFunc) = 0;
    virtual void SetOnDelete(std::function<void()>&& onDeleteCallback) = 0;
    virtual void SetOnAppear(std::function<void()>&& onAppearCallback) = 0;
    virtual void SetOnAttach(std::function<void()>&& onAttachCallback) = 0;
    virtual void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) = 0;
    virtual void SetOnDetach(std::function<void()>&& onDetachCallback) = 0;
    virtual void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) = 0;
    virtual void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) = 0;
    virtual void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) = 0;
    virtual void SetOnFocus(OnFocusFunc&& onFocusCallback) = 0;
    virtual void SetOnBlur(OnBlurFunc&& onBlurCallback) = 0;
    virtual void SetOnFocusAxisEvent(OnFocusAxisEventFunc&& onFocusAxisCallback) = 0;
    virtual void SetDraggable(bool draggable) = 0;
    virtual void SetDragPreviewOptions(const NG::DragPreviewOption& previewOption) = 0;
    virtual void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) = 0;
    virtual void SetOnPreDrag(NG::OnPreDragFunc&& onPreDrag) = 0;
    virtual void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) = 0;
    virtual void SetOnDragSpringLoading(NG::OnDrapDropSpringLoadingFunc&& onDragSpringLoading) = 0;
    virtual void SetOnDragSpringLoadingConfiguration(
        const RefPtr<NG::DragSpringLoadingConfiguration>& dragSpringLoadingConfiguration) = 0;
    virtual void SetOnDragEnd(OnNewDragFunc&& onDragEnd) = 0;
    virtual void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) = 0;
    virtual void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) = 0;
    virtual void SetOnDrop(NG::OnDragDropFunc&& onDrop) = 0;
    virtual void SetAllowDrop(const std::set<std::string>& allowDrop) = 0;
    virtual void SetDrawModifier(const RefPtr<NG::DrawModifier>& drawModifier) = 0;
    virtual void SetDragPreview(const NG::DragDropInfo& info) = 0;
    virtual void SetOnVisibleChange(
        std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratios) = 0;
    virtual void SetOnVisibleAreaApproximateChange(const std::function<void(bool, double)>&& onVisibleChange,
        const std::vector<double>& ratioList, int32_t expectedUpdateInterval) = 0;
    virtual void SetOnAreaChanged(
        std::function<void(const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)>&&
            onAreaChanged) = 0;
    virtual void SetOnSizeChanged(
        std::function<void(const NG::RectF& oldRect, const NG::RectF& rect)>&& onSizeChanged) = 0;
    virtual void* GetFrameNode() = 0;

    // Disable event when the param is undefined.
    virtual void DisableOnClick() = 0;
    virtual void DisableOnTouch() = 0;
    virtual void DisableOnKeyEvent() = 0;
    virtual void DisableOnKeyPreIme() {}
    virtual void DisableOnKeyEventDispatch() {}
    virtual void DisableOnHover() = 0;
    virtual void DisableOnHoverMove() = 0;
    virtual void DisableOnAccessibilityHover() = 0;
    virtual void DisableOnMouse() = 0;
    virtual void DisableOnAppear() = 0;
    virtual void DisableOnDisAppear() = 0;
    virtual void DisableOnAttach() = 0;
    virtual void DisableOnDetach() = 0;
    virtual void DisableOnAreaChange() = 0;
    virtual void DisableOnFocus() = 0;
    virtual void DisableOnBlur() = 0;
    virtual void DisableOnFocusAxisEvent() = 0;
    virtual void DisableOnAxisEvent() = 0;
#ifdef SUPPORT_DIGITAL_CROWN
    virtual void DisableOnCrownEvent() = 0;
#endif

    // interact
    virtual void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) = 0;
    virtual void SetMouseResponseRegion(const std::vector<DimensionRect>& responseRegion) {}
    virtual void SetEnabled(bool enabled) = 0;
    virtual void SetTouchable(bool touchable) = 0;
    virtual void SetFocusable(bool focusable) = 0;
    virtual void SetTabStop(bool tabStop) {}
    virtual void SetFocusNode(bool focus) = 0;
    virtual void SetTabIndex(int32_t index) = 0;
    virtual void SetFocusOnTouch(bool isSet) = 0;
    virtual void SetDefaultFocus(bool isSet) = 0;
    virtual void SetGroupDefaultFocus(bool isSet) = 0;
    virtual void SetNextFocus(NG::FocusIntension key, std::string& nextFocus) {}
    virtual void ResetNextFocus() {}
    virtual void SetFocusBoxStyle(const NG::FocusBoxStyle& style) {}
    virtual void SetFocusBoxStyleUpdateFunc(
        NG::FocusBoxStyle& style, const RefPtr<ResourceObject>& resObj, const std::string& property) {}
    virtual void SetFocusScopeId(const std::string& focusScopeId, bool isGroup, bool arrowKeyStepOut) {}
    virtual void SetFocusScopePriority(const std::string& focusScopeId, const uint32_t focusPriority) {}
    virtual void SetInspectorId(const std::string& inspectorId) = 0;
    virtual void SetAutoEventParam(const std::string& param) {}
    virtual void SetRestoreId(int32_t restoreId) = 0;
    virtual void SetDebugLine(const std::string& line) = 0;
    virtual void SetHoverEffect(HoverEffectType hoverEffect) = 0;
    virtual void SetHitTestMode(NG::HitTestMode hitTestMode) = 0;
    virtual void SetOnTouchTestFunc(NG::OnChildTouchTestFunc&& onChildTouchTest) = 0;
    virtual void SetKeyboardShortcut(const std::string& value, const std::vector<ModifierKey>& keys,
        std::function<void()>&& onKeyboardShortcutAction) = 0;
    virtual void SetMonopolizeEvents(bool monopolizeEvents) = 0;
    virtual void NotifyDragStartRequest(DragStartRequestStatus dragStatus) {}
    virtual void SetDragEventStrictReportingEnabled(bool dragEventStrictReportingEnabled) = 0;
    virtual void EnableDropDisallowedBadge(bool enableDropDisallowedBadge) = 0;
    virtual int32_t CancelDataLoading(const std::string& key) = 0;
    virtual void SetDisableDataPrefetch(bool disableDataPrefetch);
    virtual void SetDisallowDropForcedly(bool isDisallowDropForcedly) {}
    // obscured
    virtual void SetObscured(const std::vector<ObscuredReasons>& reasons) = 0;
    virtual void SetPrivacySensitive(bool flag) = 0;

    // toolbar
    virtual void SetToolbarBuilder(std::function<void()>&& buildFunc) = 0;

    // background
    virtual void BindBackground(std::function<void()>&& buildFunc, const Alignment& align) = 0;
    virtual void SetBackground(std::function<void()>&& buildFunc) = 0;
    virtual void SetBackgroundAlign(const Alignment& align) = 0;
    virtual void SetCustomBackgroundColor(const Color& color) = 0;
    virtual void SetCustomBackgroundColorWithResourceObj(const Color& color, const RefPtr<ResourceObject>& resObj) = 0;
    virtual void SetBackgroundIgnoresLayoutSafeAreaEdges(const uint32_t edges) = 0;
    virtual void SetIsTransitionBackground(bool val) = 0;
    virtual void SetIsBuilderBackground(bool val) = 0;

    // popup and menu
    virtual void BindPopup(const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode) = 0;
    virtual void BindTips(const RefPtr<PopupParam>& param, const RefPtr<SpanString>& spanString) = 0;
    virtual int32_t OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) = 0;
    virtual int32_t UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) = 0;
    virtual int32_t ClosePopup(const RefPtr<NG::UINode>& customNode) = 0;
    virtual int32_t GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) = 0;
    virtual void DismissPopup() = 0;
    virtual int32_t OpenMenu(
        NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId) = 0;
    virtual int32_t UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode) = 0;
    virtual int32_t CloseMenu(const RefPtr<NG::UINode>& customNode) = 0;
    virtual void BindMenu(
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const NG::MenuParam& menuParam) = 0;
    virtual void BindContextMenu(ResponseType type, std::function<void()>& buildFunc, const NG::MenuParam& menuParam,
        std::function<void()>& previewBuildFunc) = 0;
    virtual void BindDragWithContextMenuParams(const NG::MenuParam& menuParam) = 0;
    virtual void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, const NG::ContentCoverParam& contentCoverParam) = 0;
    virtual void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle,
        std::function<void()>&& onAppear, std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack) = 0;
    virtual void DismissContentCover() = 0;
    virtual void DismissSheet() = 0;
    virtual void SheetSpringBack() = 0;
    virtual void DismissDialog() {};

    // accessibility
    virtual void SetAccessibilityGroup(bool accessible) = 0;
    virtual void SetAccessibilityText(const std::string& text) = 0;
    virtual void SetAccessibilityTextHint(const std::string& text) = 0;
    virtual void SetAccessibilityDescription(const std::string& description) = 0;
    virtual void SetAccessibilityImportance(const std::string& importance) = 0;
    virtual void SetAccessibilityVirtualNode(std::function<void()>&& buildFunc) = 0;
    virtual void SetAccessibilitySelected(bool selected, bool resetValue) = 0;
    virtual void SetAccessibilityChecked(bool checked, bool resetValue) = 0;
    virtual void SetAccessibilityTextPreferred(bool accessibilityTextPreferred) = 0;
    virtual void SetAccessibilityNextFocusId(const std::string& nextFocusId) = 0;
    virtual void SetAccessibilityRole(const std::string& role, bool resetValue) = 0;
    virtual void SetOnAccessibilityFocus(NG::OnAccessibilityFocusCallbackImpl&& onAccessibilityFocusCallbackImpl) = 0;
    virtual void SetOnAccessibilityActionIntercept(
        NG::ActionAccessibilityActionIntercept&& onActionAccessibilityActionIntercept) = 0;
    virtual void SetOnAccessibilityHoverTransparent(TouchEventFunc&& touchEventFunc) = 0;
    virtual void ResetOnAccessibilityFocus() = 0;
    virtual void SetAccessibilityDefaultFocus(bool isFocus) = 0;
    virtual void SetAccessibilityUseSamePage(const std::string& pageMode) = 0;
    virtual void SetAccessibilityScrollTriggerable(bool triggerable, bool resetValue) = 0;
    virtual void SetAccessibilityFocusDrawLevel(int32_t drawLevel) = 0;

    // progress mask
    virtual void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>& progress) = 0;
    // foregroundColor
    virtual void SetForegroundColor(const Color& color) = 0;
    virtual void SetForegroundColorStrategy(const ForegroundColorStrategy& strategy) = 0;

    // custom animation properties
    virtual void CreateAnimatablePropertyFloat(
        const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent) = 0;
    virtual void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value) = 0;

    virtual void CreateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<NG::CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<NG::CustomAnimatableArithmetic>&)>& onCallbackEvent) = 0;
    virtual void UpdateAnimatableArithmeticProperty(
        const std::string& propertyName, RefPtr<NG::CustomAnimatableArithmetic>& value) = 0;
    virtual void UpdateSafeAreaExpandOpts(const NG::SafeAreaExpandOpts& opts) = 0;
    virtual void UpdateIgnoreLayoutSafeAreaOpts(const NG::IgnoreLayoutSafeAreaOpts& opts) = 0;

    // global light
    virtual void SetLightPosition(
        const CalcDimension& positionX, const CalcDimension& positionY, const CalcDimension& positionZ) = 0;
    virtual void SetLightPosition(const NG::TranslateOptions& options) = 0;
    virtual void SetLightIntensity(const float value) = 0;
    virtual void SetLightColor(const Color& value) = 0;
    virtual void SetLightIlluminated(const uint32_t value) = 0;
    virtual void SetIlluminatedBorderWidth(const Dimension& value) = 0;
    virtual void SetBloom(const float value) = 0;
    virtual void SetPositionLocalizedEdges(bool needLocalized) = 0;
    virtual void SetMarkAnchorStart(Dimension& markAnchorStart) = 0;
    virtual void ResetMarkAnchorStart() = 0;
    virtual void SetOffsetLocalizedEdges(bool needLocalized) = 0;
    virtual void CreateWithResourceObj(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& resourceObj, const PopupType& type) = 0;
    virtual void CreateWithResourceObj(
        const RefPtr<NG::FrameNode>& frameNode, const RefPtr<ResourceObject>& resourceObj) = 0;
    virtual void RemoveResObj(const std::string& key) {};
    virtual void CreateWithResourceObj(const RefPtr<NG::FrameNode>& frameNode,
        const RefPtr<ResourceObject>& resourceObj, const PopupOptionsType& type) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

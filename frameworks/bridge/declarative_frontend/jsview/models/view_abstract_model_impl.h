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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H

#include "base/utils/macros.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/property/progress_mask_property.h"

namespace OHOS::Ace {
class SpanString;
}

namespace OHOS::Ace::Framework {

class ViewAbstractModelImpl : public ViewAbstractModel {
public:
    ~ViewAbstractModelImpl() override = default;

    static void SwapBackBorder(const RefPtr<Decoration>& decoration);
    static OnDragFunc ToDragFunc(NG::OnDragStartFunc&& onDragStart);

    void SetWidth(const CalcDimension& width) override;
    void SetHeight(const CalcDimension& height) override;
    void ClearWidthOrHeight(bool isWidth) override {};
    void SetMinWidth(const CalcDimension& minWidth) override;
    void SetMinHeight(const CalcDimension& minHeight) override;
    void SetMaxWidth(const CalcDimension& maxWidth) override;
    void SetMaxHeight(const CalcDimension& maxHeight) override;
    void ResetMinSize(bool resetWidth) override {};
    void ResetMaxSize(bool resetWidth) override {};

    void SetBackgroundColor(const Color& color) override;
    void SetBackgroundImage(const ImageSourceInfo& src, RefPtr<ThemeConstants> themeConstant) override;
    void SetBackgroundImageRepeat(const ImageRepeat& imageRepeat) override;
    void SetBackgroundImageSize(const BackgroundImageSize& bgImgSize) override;
    void SetBackgroundImagePosition(const BackgroundImagePosition& bgImgPosition) override;
    void SetBackgroundBlurStyle(const BlurStyleOption& bgBlurStyle, const SysOptions& sysOptions) override;
    void SetPadding(const CalcDimension& value) override;
    void SetPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override;
    void SetSafeAreaPadding(const CalcDimension& value) override {}
    void SetSafeAreaPaddings(const NG::PaddingProperty& paddings) override {}
    void SetSafeAreaPaddings(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override
    {}
    void ResetSafeAreaPadding() override {}
    void SetMargin(const CalcDimension& value) override;
    void SetMargins(const std::optional<CalcDimension>& top, const std::optional<CalcDimension>& bottom,
        const std::optional<CalcDimension>& left, const std::optional<CalcDimension>& right) override;
    void SetBorderRadius(const Dimension& value) override;
    void SetBorderRadius(const std::optional<Dimension>& radiusTopLeft, const std::optional<Dimension>& radiusTopRight,
        const std::optional<Dimension>& radiusBottomLeft, const std::optional<Dimension>& radiusBottomRight) override;
    void SetBorderColor(const Color& value) override;
    void SetBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override;
    void SetBorderWidth(const Dimension& value) override;
    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override;
    void SetBorderStyle(const BorderStyle& value) override;
    void SetBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override;
    void SetBorderImage(const RefPtr<BorderImage>& borderImage, uint8_t bitset) override;
    void SetBorderImageGradient(const NG::Gradient& gradient) override;

    void SetOuterBorderRadius(const Dimension& value) override {}
    void SetOuterBorderRadius(const std::optional<Dimension>& radiusTopLeft,
        const std::optional<Dimension>& radiusTopRight, const std::optional<Dimension>& radiusBottomLeft,
        const std::optional<Dimension>& radiusBottomRight) override {}
    void SetOuterBorderRadius(const NG::BorderRadiusProperty& borderRadius) override {}
    void SetOuterBorderColor(const Color& value) override {}
    void SetOuterBorderColor(const std::optional<Color>& colorLeft, const std::optional<Color>& colorRight,
        const std::optional<Color>& colorTop, const std::optional<Color>& colorBottom) override {}
    void SetOuterBorderColor(const NG::BorderColorProperty& borderColors) override {}
    void SetOuterBorderWidth(const Dimension& value) override {}
    void SetOuterBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom) override {}
    void SetOuterBorderStyle(const BorderStyle& value) override {}
    void SetOuterBorderStyle(const std::optional<BorderStyle>& styleLeft, const std::optional<BorderStyle>& styleRight,
        const std::optional<BorderStyle>& styleTop, const std::optional<BorderStyle>& styleBottom) override {}

    void SetLayoutPriority(int32_t priority) override;
    void SetPixelRound(uint16_t value) override;
    void SetLayoutWeight(float value) override;
    void SetChainWeight(const NG::ChainWeightPair& value) override {};
    void SetLayoutDirection(TextDirection value) override;
    void SetAspectRatio(float ratio) override;
    void ResetAspectRatio() override {};
    void SetAlign(const Alignment& alignment) override;
    void SetAlignRules(const std::map<AlignDirection, AlignRule>& alignRules) override;
    void SetChainStyle(const ChainInfo& chainInfo) override {}
    void SetBias(const BiasPair& biasPair) override {}
    void SetUseAlign(
        AlignDeclarationPtr declaration, AlignDeclaration::Edge edge, const std::optional<Dimension>& offset) override;
    void SetGrid(std::optional<uint32_t> span, std::optional<int32_t> offset,
        GridSizeType type = GridSizeType::UNDEFINED) override;
    void SetZIndex(int32_t value) override;

    void SetPosition(const Dimension& x, const Dimension& y) override;
    void SetOffset(const Dimension& x, const Dimension& y) override;
    void MarkAnchor(const Dimension& x, const Dimension& y) override;
    void SetPaddings(const NG::PaddingProperty& paddings) override {};
    void SetMargins(const NG::MarginProperty& margins) override {};
    void SetBorderRadius(const NG::BorderRadiusProperty& borderRadius) override {};
    void SetBorderColor(const NG::BorderColorProperty& borderColors) override {};
    void SetBorderWidth(const std::optional<Dimension>& left, const std::optional<Dimension>& right,
        const std::optional<Dimension>& top, const std::optional<Dimension>& bottom, bool isLocalized) override {};
    void SetScale(float x, float y, float z) override;
    void SetPivot(const Dimension& x, const Dimension& y, const Dimension& z) override;
    void SetTranslate(const Dimension& x, const Dimension& y, const Dimension& z) override;
    void SetRotate(float x, float y, float z, float angle, float perspective = 0.0f) override;
    void SetTransformMatrix(const std::vector<float>& matrix) override;

    void SetOpacity(double opacity, bool passThrough = false) override;
    void SetTransition(const NG::TransitionOptions& transitionOptions, bool passThrough = false) override;
    void SetChainedTransition(const RefPtr<NG::ChainedTransitionEffect>& effect,
        NG::TransitionFinishCallback&& finishCallback = nullptr) override
    {}
    void SetOverlay(
        const std::string& text, std::function<void()> &&buildFunc, const RefPtr<NG::FrameNode>& contentNode,
        const std::optional<Alignment>& align, const std::optional<Dimension>& offsetX,
        const std::optional<Dimension>& offsetY, NG::OverlayType type) override;
    void SetVisibility(VisibleType visible, std::function<void(int32_t)>&& changeEventFunc) override;
    void SetSharedTransition(
        const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option) override;
    void SetGeometryTransition(
        const std::string& id, bool followWithoutTransition = false, bool doRegisterSharedTransition = true) override;
    void SetMotionPath(const MotionPathOption& option) override;
    void SetRenderGroup(bool isRenderGroup) override {}
    void SetRenderFit(RenderFit renderFit) override {}

    void SetFlexBasis(const Dimension& value) override;
    void SetAlignSelf(FlexAlign value) override;
    void SetFlexShrink(float value) override;
    void SetFlexGrow(float value) override;
    void SetDisplayIndex(int32_t value) override;
    void ResetFlexShrink() override {};

    void SetLinearGradient(const NG::Gradient& gradient) override;
    void SetSweepGradient(const NG::Gradient& gradient) override;
    void SetRadialGradient(const NG::Gradient& gradient) override;

    void SetClipShape(const RefPtr<BasicShape>& shape) override;
    void SetClipEdge(bool isClip) override;
    void SetMask(const RefPtr<BasicShape>& shape) override;

    void SetBackdropBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override;
    void SetLinearGradientBlur(NG::LinearGradientBlurPara blurPara) override {};
    void SetDynamicDim(float DimDegree) override {};
    void SetDynamicLightUp(float rate, float lightUpDegree) override {};
    void SetBgDynamicBrightness(const BrightnessOption& brightnessOption) override {};
    void SetFgDynamicBrightness(const BrightnessOption& brightnessOption) override {};
    void SetFrontBlur(const Dimension& radius, const BlurOption& blurOption, const SysOptions& sysOptions) override;
    void SetBackShadow(const std::vector<Shadow>& shadows) override;
    void SetBlendMode(BlendMode blendMode) override;
    void SetBlendApplyType(BlendApplyType blendApplyType) override;
    void SetColorBlend(const Color& value) override;
    void SetWindowBlur(float progress, WindowBlurStyle blurStyle) override;
    void SetBrightness(const Dimension& value) override;
    void SetGrayScale(const Dimension& value) override;
    void SetContrast(const Dimension& value) override;
    void SetSaturate(const Dimension& value) override;
    void SetSepia(const Dimension& value) override;
    void SetInvert(const InvertVariant& invert) override;
    void SetSystemBarEffect(bool) override {};
    void SetHueRotate(float value) override;
    void SetUseEffect(bool, EffectType) override {}
    void SetUseShadowBatching(bool) override {}
    void SetFreeze(bool) override {}

    void SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue) override {}
    void SetOnClick(GestureEventFunc&& tapEventFunc, ClickEventFunc&& clickEventFunc,
        double distanceThreshold) override;
    void SetOnGestureJudgeBegin(NG::GestureJudgeFunc&& gestureJudgeFunc) override {}
    void SetOnTouchIntercept(NG::TouchInterceptFunc&& touchInterceptFunc) override {}
    void SetShouldBuiltInRecognizerParallelWith(
        NG::ShouldBuiltInRecognizerParallelWithFunc&& shouldBuiltInRecognizerParallelWithFunc) override
    {}
    void SetOnGestureRecognizerJudgeBegin(
        NG::GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc, bool exposeInnerGestureFlag) override {}
    void SetOnTouch(TouchEventFunc&& touchEventFunc) override;
    void SetOnKeyEvent(OnKeyConsumeFunc&& onKeyCallback) override;
#ifdef SUPPORT_DIGITAL_CROWN
    void SetOnCrownEvent(OnCrownCallbackFunc&& onCrownCallback) override {};
#endif
    void SetOnMouse(OnMouseEventFunc&& onMouseEventFunc) override;
    void SetOnAxisEvent(OnAxisEventFunc&& onAxisEventFunc) override;
    void SetOnHover(OnHoverFunc&& onHoverEventFunc) override;
    void SetOnHoverMove(OnHoverMoveFunc&& onHoverMoveEventFunc) override;
    void SetOnAccessibilityHover(OnAccessibilityHoverFunc&& onAccessibilityHoverEventFunc) override {};
    void SetOnDelete(std::function<void()>&& onDeleteCallback) override;
    void SetOnAppear(std::function<void()>&& onAppearCallback) override;
    void SetOnAttach(std::function<void()>&& onAttachCallback) override {}
    void SetOnDisAppear(std::function<void()>&& onDisAppearCallback) override;
    void SetOnDetach(std::function<void()>&& onDetachCallback) override {}
    void SetOnAccessibility(std::function<void(const std::string&)>&& onAccessibilityCallback) override;
    void SetOnRemoteMessage(RemoteCallback&& onRemoteCallback) override;
    void SetOnFocusMove(std::function<void(int32_t)>&& onFocusMoveCallback) override;
    void SetOnFocus(OnFocusFunc&& onFocusCallback) override;
    void SetOnBlur(OnBlurFunc&& onBlurCallback) override;
    void SetOnFocusAxisEvent(OnFocusAxisEventFunc&& onFocusAxisCallback) override {}
    void SetDraggable(bool draggable) override {}
    void SetDragPreviewOptions(const NG::DragPreviewOption& previewOption) override {};
    void SetOnDragStart(NG::OnDragStartFunc&& onDragStart) override;
    void SetOnPreDrag(NG::OnPreDragFunc&& onPreDrag) override;
    void SetOnDragEnd(OnNewDragFunc&& onDragEnd) override;
    void SetOnDragEnter(NG::OnDragDropFunc&& onDragEnter) override;
    void SetOnDragLeave(NG::OnDragDropFunc&& onDragLeave) override;
    void SetOnDragMove(NG::OnDragDropFunc&& onDragMove) override;
    void SetOnDrop(NG::OnDragDropFunc&& onDrop) override;
    void SetOnVisibleChange(
        std::function<void(bool, double)>&& onVisibleChange, const std::vector<double>& ratios) override;
    void SetOnVisibleAreaApproximateChange(const std::function<void(bool, double)>&& onVisibleChange,
        const std::vector<double>& ratioList, int32_t expectedUpdateInterval) override {};
    void SetOnAreaChanged(
        std::function<void(const Rect& oldRect, const Offset& oldOrigin, const Rect& rect, const Offset& origin)>&&
            onAreaChanged) override;
    void SetOnSizeChanged(
        std::function<void(const NG::RectF& oldRect, const NG::RectF& rect)>&& onSizeChanged) override {};

    void SetResponseRegion(const std::vector<DimensionRect>& responseRegion) override;
    void SetEnabled(bool enabled) override;
    void SetTouchable(bool touchable) override;
    void SetFocusable(bool focusable) override;
    void SetFocusNode(bool focus) override;
    void SetTabIndex(int32_t index) override;
    void SetFocusOnTouch(bool isSet) override;
    void SetDefaultFocus(bool isSet) override;
    void SetGroupDefaultFocus(bool isSet) override;
    void SetInspectorId(const std::string& inspectorId) override;
    void SetRestoreId(int32_t restoreId) override;
    void SetDebugLine(const std::string& line) override;
    void SetHoverEffect(HoverEffectType hoverEffect) override;
    void SetHitTestMode(NG::HitTestMode hitTestMode) override;
    void SetOnTouchTestFunc(NG::OnChildTouchTestFunc&& onChildTouchTest) override {};
    void SetKeyboardShortcut(const std::string& value, const std::vector<ModifierKey>& keys,
        std::function<void()>&& onKeyboardShortcutAction) override {};
    void SetObscured(const std::vector<ObscuredReasons>& reasons) override {};
    void SetPrivacySensitive(bool flag) override {};
    void SetMonopolizeEvents(bool monopolizeEvents) override {};

    // Disable event.
    void DisableOnClick() override {};
    void DisableOnTouch() override {};
    void DisableOnKeyEvent() override {};
#ifdef SUPPORT_DIGITAL_CROWN
    void DisableOnCrownEvent() override {};
#endif
    void DisableOnHover() override {};
    void DisableOnHoverMove() override {};
    void DisableOnAccessibilityHover() override {};
    void DisableOnMouse() override {};
    void DisableOnAxisEvent() override {};
    void DisableOnAppear() override {};
    void DisableOnDisAppear() override {};
    void DisableOnAttach() override {};
    void DisableOnDetach() override {};
    void DisableOnAreaChange() override {};
    void DisableOnFocus() override {};
    void DisableOnBlur() override {};
    void DisableOnFocusAxisEvent() override {};

    void BindBackground(std::function<void()>&& buildFunc, const Alignment& align) override;
    void BindPopup(const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode) override;
    void BindTips(const RefPtr<PopupParam>& param, const RefPtr<OHOS::Ace::SpanString>& sapnString) override;
    int32_t OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    int32_t UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    int32_t ClosePopup(const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    int32_t GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    void DismissPopup() override {}

    void BindMenu(std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc,
        const NG::MenuParam& menuParam) override;

    void BindContextMenu(ResponseType type, std::function<void()>& buildFunc, const NG::MenuParam& menuParam,
        std::function<void()>& previewBuildFunc) override;

    int32_t OpenMenu(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode, const int32_t& targetId) override
    {
        return 0;
    };
    int32_t UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    int32_t CloseMenu(const RefPtr<NG::UINode>& customNode) override
    {
        return 0;
    };
    void BindDragWithContextMenuParams(const NG::MenuParam& menuParam) override {};
    void BindContentCover(bool isShow, std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc, NG::ModalStyle& modalStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, const NG::ContentCoverParam& contentCoverParam) override
    {}
    void BindSheet(bool isShow, std::function<void(const std::string&)>&& callback, std::function<void()>&& buildFunc,
        std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss, std::function<void()>&& onWillAppear,
        std::function<void()>&& onWillDisappear, std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack) override
    {}
    void DismissSheet() override {}
    void DismissContentCover() override {}
    void SheetSpringBack() override {}

    void SetAccessibilityGroup(bool accessible) override;
    void SetAccessibilityText(const std::string& text) override;
    void SetAccessibilityTextHint(const std::string& text) override;
    void SetAccessibilityDescription(const std::string& description) override;
    void SetAccessibilityImportance(const std::string& importance) override;
    void SetAccessibilityVirtualNode(std::function<void()>&& buildFunc) override;
    void SetAccessibilitySelected(bool selected, bool resetValue) override;
    void SetAccessibilityChecked(bool checked, bool resetValue) override;
    void SetAccessibilityTextPreferred(bool accessibilityTextPreferred) override;
    void SetAccessibilityNextFocusId(const std::string& nextFocusId) override;
    void SetAccessibilityRole(const std::string& role, bool resetValue) override;
    void SetOnAccessibilityFocus(NG::OnAccessibilityFocusCallbackImpl&& onAccessibilityFocusCallbackImpl) override;
    void ResetOnAccessibilityFocus() override;
    void SetAccessibilityDefaultFocus(bool isFocus) override;
    void SetAccessibilityUseSamePage(const std::string& pageMode) override;
    void SetAccessibilityScrollTriggerable(bool triggerable, bool resetValue) override;
    void SetAccessibilityFocusDrawLevel(int32_t drawLevel) override;

    void SetProgressMask(const RefPtr<NG::ProgressMaskProperty>& progress) override {}
    void SetForegroundColor(const Color& color) override {}
    void SetForegroundColorStrategy(const ForegroundColorStrategy& strategy) override {}
    void SetDrawModifier(const RefPtr<NG::DrawModifier>& drawModifier) override {}
    void* GetFrameNode() override { return nullptr; }
    void SetAllowDrop(const std::set<std::string>& allowDrop) override {}
    void SetDragPreview(const NG::DragDropInfo& info) override {}

    void CreateAnimatablePropertyFloat(const std::string& propertyName, float value,
        const std::function<void(float)>& onCallbackEvent) override {};
    void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value) override {};

    void CreateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<NG::CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<NG::CustomAnimatableArithmetic>&)>& onCallbackEvent) override {};
    void UpdateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<NG::CustomAnimatableArithmetic>& value) override {};
    void UpdateSafeAreaExpandOpts(const NG::SafeAreaExpandOpts& opts) override {};
    void SetDragEventStrictReportingEnabled(bool dragEventStrictReportingEnabled) override {};
    int32_t CancelDataLoading(const std::string& key) override { return 0; };
    void SetDisableDataPrefetch(bool disableDataPrefetch) override {};
    void SetBackgroundImageResizableSlice(const ImageResizableSlice& Slice) override {};
    // global light
    void SetLightPosition(
        const CalcDimension& positionX, const CalcDimension& positionY, const CalcDimension& positionZ) override {};
    void SetLightIntensity(const float value) override {};
    void SetLightColor(const Color& value) override {};
    void SetLightIlluminated(const uint32_t value) override {};
    void SetIlluminatedBorderWidth(const Dimension& value) override {};
    void SetBloom(const float value) override {};
    void SetPositionLocalizedEdges(bool needLocalized) override {};
    void SetMarkAnchorStart(Dimension& markAnchorStart) override {};
    void ResetMarkAnchorStart() override {};
    void SetOffsetLocalizedEdges(bool needLocalized) override {};
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIEW_ABSTRACT_MODEL_IMPL_H

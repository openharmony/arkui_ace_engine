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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H

#include <cstdint>
#include <functional>

#include "base/geometry/dimension.h"
#include "base/geometry/matrix4.h"
#include "base/geometry/ng/offset_t.h"
#include "base/geometry/ng/rect_t.h"
#include "base/geometry/ng/vector.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/layout/grid_layout_info.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/motion_path_option.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/popup_param.h"
#include "core/components/common/properties/shared_transition_option.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/menu/menu_pattern.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/gradient_property.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/progress_mask_property.h"
#include "core/components_ng/property/transition_property.h"

namespace OHOS::Ace::NG {
struct OptionParam {
    std::string value;
    std::string icon;
    bool enabled = true;
    std::function<void()> action;

    OptionParam() = default;
    OptionParam(const std::string &valueParam, const std::string &iconParam, const std::function<void()> &actionParam)
        : value(valueParam), icon(iconParam), enabled(true), action(actionParam)
    {}
    OptionParam(const std::string &valueParam, const std::string &iconParam, bool enabledParam,
        const std::function<void()> &actionParam)
        : value(valueParam), icon(iconParam), enabled(enabledParam), action(actionParam)
    {}
    OptionParam(const std::string &valueParam, const std::function<void()> &actionParam)
        : value(valueParam), icon(""), enabled(true), action(actionParam)
    {}

    ~OptionParam() = default;
};

struct MenuParam {
    std::string title;
    OffsetF positionOffset;
    bool setShow = false;
    bool isShow = false;
    std::function<void(const std::string&)> onStateChange;
    std::optional<Placement> placement;
    std::function<void()> onAppear;
    std::function<void()> onDisappear;
    std::function<void()> aboutToAppear;
    std::function<void()> aboutToDisappear;
    std::optional<bool> enableArrow;
    std::optional<Dimension> arrowOffset;
    bool isAboveApps = false;
    bool isShowInSubWindow = false;
    MenuType type = MenuType::MENU;
    MenuPreviewMode previewMode = MenuPreviewMode::NONE;
    MenuPreviewAnimationOptions previewAnimationOptions;
    std::optional<EffectOption> backgroundEffectOption;
    std::optional<Color> backgroundColor;
    std::optional<int32_t> backgroundBlurStyle;
};

class ACE_FORCE_EXPORT ViewAbstract {
public:
    static void SetWidth(const CalcLength &width);
    static void SetHeight(const CalcLength &height);
    static void ClearWidthOrHeight(bool isWidth);
    static void SetMinWidth(const CalcLength &minWidth);
    static void SetMinHeight(const CalcLength &minHeight);
    static void SetMaxWidth(const CalcLength &maxWidth);
    static void SetMaxHeight(const CalcLength &maxHeight);
    static void ResetMinSize(bool resetWidth);
    static void ResetMaxSize(bool resetWidth);

    static void SetAspectRatio(float ratio);
    static void ResetAspectRatio();
    static void SetLayoutWeight(int32_t value);
    static void SetPixelRound(uint8_t value);
    static void SetLayoutDirection(TextDirection value);

    static void SetBackgroundColor(const Color &color);
    static void SetBackgroundImage(const ImageSourceInfo &src);
    static void SetBackgroundImageRepeat(const ImageRepeat &imageRepeat);
    static void SetBackgroundImageSize(const BackgroundImageSize &bgImgSize);
    static void SetBackgroundImagePosition(const BackgroundImagePosition &bgImgPosition);
    static void SetBackgroundBlurStyle(const BlurStyleOption &bgBlurStyle);
    static void SetBackgroundEffect(const EffectOption &effectOption);
    static void SetForegroundBlurStyle(const BlurStyleOption &fgBlurStyle);
    static void SetSphericalEffect(double radio);
    static void SetPixelStretchEffect(PixStretchEffectOption &option);
    static void SetLightUpEffect(double radio);
    static void SetPadding(const CalcLength &value);
    static void SetPadding(const PaddingProperty &value);
    static void SetMargin(const CalcLength &value);
    static void SetMargin(const PaddingProperty &value);
    static void SetBorderRadius(const BorderRadiusProperty &value);
    static void SetBorderRadius(const Dimension &value);
    static void SetBorderColor(const Color &value);
    static void SetBorderColor(const BorderColorProperty &value);
    static void SetBorderWidth(const Dimension &value);
    static void SetBorderWidth(const BorderWidthProperty &value);
    static void SetBorderStyle(const BorderStyle &value);
    static void SetBorderStyle(const BorderStyleProperty &value);
    static void SetOpacity(double opacity);
    static void SetAllowDrop(const std::set<std::string> &allowDrop);
    static void SetDragPreview(const NG::DragDropInfo& info);

    static void SetBorderImage(const RefPtr<BorderImage> &borderImage);
    static void SetBorderImageSource(const std::string &bdImageSrc);

    // outer border
    static void SetOuterBorderRadius(const BorderRadiusProperty& value);
    static void SetOuterBorderRadius(const Dimension& value);
    static void SetOuterBorderColor(const Color& value);
    static void SetOuterBorderColor(const BorderColorProperty& value);
    static void SetOuterBorderWidth(const Dimension& value);
    static void SetOuterBorderWidth(const BorderWidthProperty& value);
    static void SetOuterBorderStyle(const BorderStyle& value);
    static void SetOuterBorderStyle(const BorderStyleProperty& value);

    static void SetHasBorderImageSlice(bool tag);
    static void SetHasBorderImageWidth(bool tag);
    static void SetHasBorderImageOutset(bool tag);
    static void SetHasBorderImageRepeat(bool tag);
    static void SetBorderImageGradient(const NG::Gradient &gradient);

    // customBackground
    static void SetBackgroundAlign(const Alignment &align);

    // decoration
    static void SetBackdropBlur(const Dimension &radius, const BlurOption &blurOption);
    static void SetLinearGradientBlur(const NG::LinearGradientBlurPara& blurPara);
    static void SetDynamicLightUp(float rate, float lightUpDegree);
    static void SetFrontBlur(const Dimension &radius, const BlurOption &blurOption);
    static void SetBackShadow(const Shadow &shadow);
    static void SetBlendMode(BlendMode blendMode);
    static void SetBlendApplyType(BlendApplyType blendApplyType);

    // graphics
    static void SetBrightness(const Dimension &value);
    static void SetGrayScale(const Dimension &value);
    static void SetContrast(const Dimension &value);
    static void SetSaturate(const Dimension &value);
    static void SetSepia(const Dimension &value);
    static void SetInvert(const InvertVariant &value);
    static void SetHueRotate(float value);
    static void SetColorBlend(const Color &value);
    static void SetSystemBarEffect(bool systemBarEffect);

    // gradient
    static void SetLinearGradient(const NG::Gradient &gradient);
    static void SetSweepGradient(const NG::Gradient &gradient);
    static void SetRadialGradient(const NG::Gradient &gradient);

    // layout
    static void SetAlign(Alignment alignment);
    static void SetAlignRules(const std::map<AlignDirection, AlignRule> &alignRules);
    static void SetBias(const BiasPair& biasPair);
    static void SetVisibility(VisibleType visible);
    static void SetGrid(std::optional<int32_t> span, std::optional<int32_t> offset,
        GridSizeType type = GridSizeType::UNDEFINED);

    // position
    static void SetPosition(const OffsetT<Dimension> &value);
    static void SetOffset(const OffsetT<Dimension> &value);
    static void MarkAnchor(const OffsetT<Dimension> &value);

    // render position
    static void SetZIndex(int32_t value);
    // renderGroup
    static void SetRenderGroup(bool isRenderGroup);
    // renderFit, i.e. gravity
    static void SetRenderFit(RenderFit renderFit);

    // transform
    static void SetScale(const NG::VectorF &value);
    static void SetPivot(const DimensionOffset &value);
    static void SetTranslate(const NG::TranslateOptions &value);
    static void SetRotate(const NG::Vector5F &value);

    static void SetTransformMatrix(const Matrix4 &matrix);

    // event
    static void SetOnClick(GestureEventFunc &&clickEventFunc);
    static void SetOnGestureJudgeBegin(GestureJudgeFunc &&gestureJudgeFunc);
    static void SetOnTouch(TouchEventFunc &&touchEventFunc);
    static void SetOnMouse(OnMouseEventFunc &&onMouseEventFunc);
    static void SetOnHover(OnHoverFunc &&onHoverEventFunc);
    static void SetHoverEffect(HoverEffectType hoverEffect);
    static void SetHoverEffectAuto(HoverEffectType hoverEffect);
    static void SetEnabled(bool enabled);
    static void SetFocusable(bool focusable);
    static void SetOnFocus(OnFocusFunc &&onFocusCallback);
    static void SetOnBlur(OnBlurFunc &&onBlurCallback);
    static void SetOnKeyEvent(OnKeyCallbackFunc &&onKeyCallback);
    static void SetTabIndex(int32_t index);
    static void SetFocusOnTouch(bool isSet);
    static void SetDefaultFocus(bool isSet);
    static void SetGroupDefaultFocus(bool isSet);
    static void SetOnAppear(std::function<void()> &&onAppear);
    static void SetOnDisappear(std::function<void()> &&onDisappear);
    static void SetOnAreaChanged(std::function<void(const RectF &oldRect, const OffsetF &oldOrigin, const RectF &rect,
        const OffsetF &origin)> &&onAreaChanged);
    static void SetOnVisibleChange(std::function<void(bool, double)> &&onVisibleChange,
        const std::vector<double> &ratioList);
    static void SetResponseRegion(const std::vector<DimensionRect> &responseRegion);
    static void SetMouseResponseRegion(const std::vector<DimensionRect> &mouseResponseRegion);
    static void SetTouchable(bool touchable);
    static void SetHitTestMode(HitTestMode hitTestMode);
    static void SetOnTouchTestFunc(NG::OnChildTouchTestFunc&& onChildTouchTest);
    static void SetDraggable(bool draggable);
    static void SetDragPreviewOptions(const DragPreviewOption& previewOption);
    static void SetOnDragStart(
        std::function<DragDropInfo(const RefPtr<OHOS::Ace::DragEvent> &, const std::string &)> &&onDragStart);
    static void SetOnDragEnter(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent> &, const std::string &)> &&onDragEnter);
    static void SetOnDragLeave(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent> &, const std::string &)> &&onDragLeave);
    static void SetOnDragMove(
        std::function<void(const RefPtr<OHOS::Ace::DragEvent> &, const std::string &)> &&onDragMove);
    static void SetOnDrop(std::function<void(const RefPtr<OHOS::Ace::DragEvent> &, const std::string &)> &&onDrop);

    static void SetOnDragEnd(std::function<void(const RefPtr<OHOS::Ace::DragEvent> &)> &&onDragEnd);
    static void SetMonopolizeEvents(bool monopolizeEvents);

    // flex properties
    static void SetAlignSelf(FlexAlign value);
    static void SetFlexShrink(float value);
    static void ResetFlexShrink();
    static void SetFlexGrow(float value);
    static void SetFlexBasis(const Dimension &value);
    static void SetDisplayIndex(int32_t value);
    static void SetKeyboardShortcut(const std::string &value, const std::vector<ModifierKey> &keys,
        std::function<void()> &&onKeyboardShortcutAction);
    // obscured
    static void SetObscured(const std::vector<ObscuredReasons> &reasons);

    // Bind properties
    static void BindPopup(const RefPtr<PopupParam> &param, const RefPtr<FrameNode> &targetNode,
        const RefPtr<UINode> &customNode);
    static void BindMenuWithItems(std::vector<OptionParam> &&params, const RefPtr<FrameNode> &targetNode,
        const NG::OffsetF &offset, const MenuParam &menuParam);
    static void BindMenuWithCustomNode(const RefPtr<UINode> &customNode, const RefPtr<FrameNode> &targetNode,
        const NG::OffsetF &offset, const MenuParam &menuParam, const RefPtr<UINode> &previewCustomNode = nullptr);
    static void ShowMenu(
        int32_t targetId, const NG::OffsetF& offset, bool isShowInSubWindow, bool isContextMenu = false);
    // inspector
    static void SetInspectorId(const std::string &inspectorId);
    // auto event param
    static void SetAutoEventParam(const std::string& param);
    // restore
    static void SetRestoreId(int32_t restoreId);
    // inspector debugLine
    static void SetDebugLine(const std::string &line);
    // transition
    static void SetTransition(const TransitionOptions &options);
    static void SetChainedTransition(const RefPtr<NG::ChainedTransitionEffect> &effect);
    // sharedTransition
    static void SetSharedTransition(const std::string &shareId, const std::shared_ptr<SharedTransitionOption> &option);
    // geometryTransition
    static void SetGeometryTransition(const std::string &id, bool followWithoutTransition = false);
    // clip and mask
    static void SetClipShape(const RefPtr<BasicShape> &basicShape);
    static void SetClipEdge(bool isClip);
    static void SetMask(const RefPtr<BasicShape> &basicShape);
    // overlay
    static void SetOverlay(const NG::OverlayOptions &overlay);
    // motionPath
    static void SetMotionPath(const MotionPathOption &motionPath);
    // progress mask
    static void SetProgressMask(const RefPtr<ProgressMaskProperty> &progress);

    static void Pop();

    // Disable event
    static void DisableOnClick();
    static void DisableOnTouch();
    static void DisableOnKeyEvent();
    static void DisableOnHover();
    static void DisableOnMouse();
    static void DisableOnAppear();
    static void DisableOnDisAppear();
    static void DisableOnAreaChange();
    static void DisableOnFocus();
    static void DisableOnBlur();

    // useEffect
    static void SetUseEffect(bool useEffect);

    // useShadowBatching
    static void SetUseShadowBatching(bool useShadowBatching);

    // foregroundColor
    static void SetForegroundColor(const Color& color);
    static void SetForegroundColorStrategy(const ForegroundColorStrategy& strategy);

    // clickEffect
    static void SetClickEffectLevel(const ClickEffectLevel& level, float scaleValue);

    // custom animatable property
    static void CreateAnimatablePropertyFloat(
        const std::string& propertyName, float value, const std::function<void(float)>& onCallbackEvent);
    static void UpdateAnimatablePropertyFloat(const std::string& propertyName, float value);
    static void CreateAnimatableArithmeticProperty(const std::string& propertyName,
        RefPtr<CustomAnimatableArithmetic>& value,
        std::function<void(const RefPtr<CustomAnimatableArithmetic>&)>& onCallbackEvent);
    static void UpdateAnimatableArithmeticProperty(
        const std::string& propertyName, RefPtr<CustomAnimatableArithmetic>& value);
    static void UpdateSafeAreaExpandOpts(const SafeAreaExpandOpts& opts);

    // global light
    static void SetLightPosition(
        const CalcDimension& positionX, const CalcDimension& positionY, const CalcDimension& positionZ);
    static void SetLightIntensity(float value);
    static void SetLightIlluminated(uint32_t value);
    static void SetIlluminatedBorderWidth(const Dimension& value);
    static void SetBloom(float value);

    static void SetBackgroundColor(FrameNode* frameNode, const Color& color);
    static void SetWidth(FrameNode* frameNode, const CalcLength& width);
    static void SetHeight(FrameNode* frameNode, const CalcLength& height);
    static void ClearWidthOrHeight(FrameNode* frameNode, bool isWidth);
    static void SetBorderRadius(FrameNode* frameNode, const BorderRadiusProperty& value);
    static void SetBorderRadius(FrameNode* frameNode, const Dimension& value);
    static void SetBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value);
    static void SetBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetBorderColor(FrameNode* frameNode, const BorderColorProperty& value);
    static void SetBorderColor(FrameNode* frameNode, const Color& value);
    static void SetOuterBorderColor(FrameNode* frameNode, const Color& value);
    static void SetOuterBorderColor(FrameNode* frameNode, const BorderColorProperty& value);
    static void SetOuterBorderRadius(FrameNode* frameNode, const Dimension& value);
    static void SetOuterBorderRadius(FrameNode* frameNode, const BorderRadiusProperty& value);
    static void SetOuterBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetOuterBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value);
    static void SetOuterBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value);
    static void SetOuterBorderStyle(FrameNode* frameNode, const BorderStyle& value);
    static void SetBorderStyle(FrameNode* frameNode, const BorderStyle& value);
    static void SetBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value);
    static void SetBackShadow(FrameNode* frameNode, const Shadow& shadow);
    static void SetPosition(FrameNode* frameNode, const OffsetT<Dimension>& value);
    static void SetTransformMatrix(FrameNode* frameNode, const Matrix4& matrix);
    static void SetHitTestMode(FrameNode* frameNode, HitTestMode hitTestMode);
    static void SetOpacity(FrameNode* frameNode, double opacity);
    static void SetZIndex(FrameNode* frameNode, int32_t value);
    static void SetAlign(FrameNode* frameNode, Alignment alignment);
    static void SetBackdropBlur(FrameNode* frameNode, const Dimension& radius);
    static void SetInvert(FrameNode* frameNode, const InvertVariant& invert);
    static void SetSepia(FrameNode* frameNode, const Dimension& sepia);
    static void SetSaturate(FrameNode* frameNode, const Dimension& saturate);
    static void SetColorBlend(FrameNode* frameNode, const Color& colorBlend);
    static void SetGrayScale(FrameNode* frameNode, const Dimension& grayScale);
    static void SetContrast(FrameNode* frameNode, const Dimension& contrast);
    static void SetBrightness(FrameNode* frameNode, const Dimension& brightness);
    static void SetFrontBlur(FrameNode* frameNode, const Dimension& radius);
    static void SetHueRotate(FrameNode* frameNode, float hueRotate);
    static void SetLinearGradient(FrameNode* frameNode, const NG::Gradient& gradient);
    static void SetSweepGradient(FrameNode* frameNode, const NG::Gradient& gradient);
    static void SetRadialGradient(FrameNode* frameNode, const NG::Gradient& gradient);
    static void SetOverlay(FrameNode* frameNode, const NG::OverlayOptions& overlay);
    static void SetBorderImage(FrameNode* frameNode, const RefPtr<BorderImage>& borderImage);
    static void SetBorderImageSource(FrameNode* frameNode, const std::string& bdImageSrc);
    static void SetHasBorderImageSlice(FrameNode* frameNode, bool tag);
    static void SetHasBorderImageWidth(FrameNode* frameNode, bool tag);
    static void SetHasBorderImageOutset(FrameNode* frameNode, bool tag);
    static void SetHasBorderImageRepeat(FrameNode* frameNode, bool tag);
    static void SetBorderImageGradient(FrameNode* frameNode, const NG::Gradient& gradient);
    static void SetForegroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& fgBlurStyle);
    static void SetLinearGradientBlur(FrameNode* frameNode, const NG::LinearGradientBlurPara& blurPara);
    static void SetBackgroundBlurStyle(FrameNode* frameNode, const BlurStyleOption& bgBlurStyle);
    static void SetBackgroundImagePosition(FrameNode* frameNode, const BackgroundImagePosition& bgImgPosition);
    static void SetBackgroundImageSize(FrameNode* frameNode, const BackgroundImageSize& bgImgSize);
    static void SetBackgroundImage(FrameNode* frameNode, const ImageSourceInfo& src);
    static void SetBackgroundImageRepeat(FrameNode* frameNode, const ImageRepeat& imageRepeat);
    static void SetTranslate(FrameNode* frameNode, const NG::TranslateOptions& value);
    static void SetScale(FrameNode* frameNode, const NG::VectorF& value);
    static void SetPivot(FrameNode* frameNode, const DimensionOffset& value);
    static void SetGeometryTransition(FrameNode* frameNode, const std::string& id, bool followWithoutTransition);
    static void SetRotate(FrameNode* frameNode, const NG::Vector5F& value);
    static void SetClipEdge(FrameNode* frameNode, bool isClip);
    static void SetClipShape(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape);
    static void SetPixelStretchEffect(FrameNode* frameNode, PixStretchEffectOption& option);
    static void SetLightUpEffect(FrameNode* frameNode, double radio);
    static void SetSphericalEffect(FrameNode* frameNode, double radio);
    static void SetRenderGroup(FrameNode* frameNode, bool isRenderGroup);
    static void SetRenderFit(FrameNode* frameNode, RenderFit renderFit);
    static void SetUseEffect(FrameNode* frameNode, bool useEffect);
    static void SetForegroundColor(FrameNode* frameNode, const Color& color);
    static void SetForegroundColorStrategy(FrameNode* frameNode, const ForegroundColorStrategy& strategy);
    static void SetMotionPath(FrameNode* frameNode, const MotionPathOption& motionPath);
    static void SetFocusOnTouch(FrameNode* frameNode, bool isSet);
    static void SetGroupDefaultFocus(FrameNode* frameNode, bool isSet);
    static void SetFocusable(FrameNode* frameNode, bool focusable);
    static void SetTouchable(FrameNode* frameNode, bool touchable);
    static void SetDefaultFocus(FrameNode* frameNode, bool isSet);
    static void SetDisplayIndex(FrameNode* frameNode, int32_t value);
    static void SetOffset(FrameNode* frameNode, const OffsetT<Dimension>& value);
    static void MarkAnchor(FrameNode* frameNode, const OffsetT<Dimension>& value);
    static void SetVisibility(FrameNode* frameNode, VisibleType visible);
    static void SetMargin(FrameNode* frameNode, const CalcLength& value);
    static void SetMargin(FrameNode* frameNode, const PaddingProperty& value);
    static void SetPadding(FrameNode* frameNode, const CalcLength& value);
    static void SetPadding(FrameNode* frameNode, const PaddingProperty& value);
    static void SetLayoutDirection(FrameNode* frameNode, TextDirection value);
    static void UpdateSafeAreaExpandOpts(FrameNode* frameNode, const SafeAreaExpandOpts& opts);
    static void SetAspectRatio(FrameNode* frameNode, float ratio);
    static void SetAlignSelf(FrameNode* frameNode, FlexAlign value);
    static void SetFlexBasis(FrameNode* frameNode, const Dimension& value);
    static void ResetFlexShrink(FrameNode* frameNode);
    static void SetFlexShrink(FrameNode* frameNode, float value);
    static void SetFlexGrow(FrameNode* frameNode, float value);
    static void SetLayoutWeight(FrameNode* frameNode, int32_t value);
    static void ResetMaxSize(FrameNode* frameNode, bool resetWidth);
    static void ResetMinSize(FrameNode* frameNode, bool resetWidth);
    static void SetMinWidth(FrameNode* frameNode, const CalcLength& minWidth);
    static void SetMaxWidth(FrameNode* frameNode, const CalcLength& maxWidth);
    static void SetMinHeight(FrameNode* frameNode, const CalcLength& minHeight);
    static void SetMaxHeight(FrameNode* frameNode, const CalcLength& maxHeight);
    static void SetAlignRules(FrameNode* frameNode, const std::map<AlignDirection, AlignRule>& alignRules);
    static void SetGrid(FrameNode* frameNode, std::optional<int32_t> span, std::optional<int32_t> offset,
        GridSizeType type = GridSizeType::UNDEFINED);
    static void ResetAspectRatio(FrameNode* frameNode);
    static void SetAllowDrop(FrameNode* frameNode, const std::set<std::string>& allowDrop);
    static void SetInspectorId(FrameNode* frameNode, const std::string& inspectorId);
    static void SetRestoreId(FrameNode* frameNode, int32_t restoreId);
    static void SetTabIndex(FrameNode* frameNode, int32_t index);
    static void SetObscured(FrameNode* frameNode, const std::vector<ObscuredReasons>& reasons);
    static void SetBackgroundEffect(FrameNode* frameNode, const EffectOption &effectOption);
    static void SetDynamicLightUp(FrameNode* frameNode, float rate, float lightUpDegree);
    static void SetDragPreviewOptions(FrameNode* frameNode, const DragPreviewOption& previewOption);
    static void SetResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& responseRegion);
    static void SetMouseResponseRegion(FrameNode* frameNode, const std::vector<DimensionRect>& mouseResponseRegion);
    static void SetSharedTransition(
        FrameNode* frameNode, const std::string& shareId, const std::shared_ptr<SharedTransitionOption>& option);
    static void SetTransition(FrameNode* frameNode, const TransitionOptions& options);
    static void SetChainedTransition(FrameNode* frameNode, const RefPtr<NG::ChainedTransitionEffect>& effect);
    static void SetMask(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape);
    static void SetProgressMask(FrameNode* frameNode, const RefPtr<ProgressMaskProperty>& progress);
    static void SetEnabled(FrameNode* frameNode, bool enabled);
    static void SetUseShadowBatching(FrameNode* frameNode, bool useShadowBatching);
    static void SetBlendMode(FrameNode* frameNode, BlendMode blendMode);
    static void SetBlendApplyType(FrameNode* frameNode, BlendApplyType blendApplyType);
    static void SetMonopolizeEvents(FrameNode* frameNode, bool monopolizeEvents);
    static void SetDraggable(FrameNode* frameNode, bool draggable);
    static void SetHoverEffect(FrameNode* frameNode, HoverEffectType hoverEffect);
    static void SetClickEffectLevel(FrameNode* frameNode, const ClickEffectLevel& level, float scaleValue);
    static void SetKeyboardShortcut(FrameNode* frameNode, const std::string& value,
        const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction);

    static void SetOnFocus(FrameNode* frameNode, OnFocusFunc &&onFocusCallback);
    static void SetOnBlur(FrameNode* frameNode, OnBlurFunc &&onBlurCallback);
private:
    static void AddDragFrameNodeToManager();
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_H

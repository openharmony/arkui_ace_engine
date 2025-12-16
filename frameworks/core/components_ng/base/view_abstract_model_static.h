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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H

#include <optional>
#include <utility>
#include "view_abstract.h"

#include "base/geometry/dimension_offset.h"
#include "base/geometry/ng/vector.h"
#include "base/geometry/offset.h"
#include "base/geometry/rect.h"
#include "base/memory/ace_type.h"
#include "base/subwindow/subwindow_manager.h"
#include "base/utils/noncopyable.h"
#include "base/utils/utils.h"
#include "core/components/common/layout/position_param.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/common/properties/border_image.h"
#include "core/components_ng/base/modifier.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/property/border_property.h"
#include "core/components_ng/property/calc_length.h"
#include "core/components_ng/property/measure_property.h"
#include "core/components_ng/property/measure_utils.h"
#include "core/components_ng/property/overlay_property.h"
#include "core/components_ng/property/property.h"
#include "core/image/image_source_info.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Rosen {
    class BrightnessBlender;
}

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT ViewAbstractModelStatic {
public:
    static void SetWidth(FrameNode* frameNode, const CalcDimension& width)
    {
        if (width.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetWidth(frameNode, NG::CalcLength(width.CalcValue()));
        } else if (width.Unit() == DimensionUnit::NONE) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
        } else {
            ViewAbstract::SetWidth(frameNode, NG::CalcLength(width));
        }
    }

    static void UpdateLayoutPolicyProperty(FrameNode* frameNode, const LayoutCalPolicy layoutPolicy, bool isWidth)
    {
        ViewAbstract::UpdateLayoutPolicyProperty(frameNode, layoutPolicy, isWidth);
    }

    static void SetHeight(FrameNode* frameNode, const CalcDimension& height)
    {
        if (height.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetHeight(frameNode, NG::CalcLength(height.CalcValue()));
        } else if (height.Unit() == DimensionUnit::NONE) {
            ViewAbstract::ClearWidthOrHeight(frameNode, true);
        } else {
            ViewAbstract::SetHeight(frameNode, NG::CalcLength(height));
        }
    }

    static void SetMinWidth(FrameNode* frameNode, const CalcDimension& minWidth)
    {
        if (minWidth.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinWidth(frameNode, NG::CalcLength(minWidth.CalcValue()));
        } else {
            ViewAbstract::SetMinWidth(frameNode, NG::CalcLength(minWidth));
        }
    }

    static void SetMinHeight(FrameNode* frameNode, const CalcDimension& minHeight)
    {
        if (minHeight.Unit() == DimensionUnit::CALC) {
            ViewAbstract::SetMinHeight(frameNode, NG::CalcLength(minHeight.CalcValue()));
        } else {
            ViewAbstract::SetMinHeight(frameNode, NG::CalcLength(minHeight));
        }
    }

    static int32_t GetWindowWidthBreakpoint()
    {
        return ViewAbstract::GetWindowWidthBreakpoint();
    }

    static int32_t GetWindowHeightBreakpoint()
    {
        return ViewAbstract::GetWindowHeightBreakpoint();
    }

    static void SetOpacity(FrameNode* frameNode, const std::optional<double>& opacity)
    {
        ViewAbstract::SetOpacity(frameNode, opacity.value_or(1));
    }
    static void BindMenuTouch(FrameNode* targetNode, const RefPtr<GestureEventHub>& gestrueHub);

    static RefPtr<PipelineContext> GetSheetContext(NG::SheetStyle& sheetStyle);
    static bool CreatePropertyAnimation(FrameNode* frameNode, AnimationPropertyType property,
        const std::vector<float>& startValue, const std::vector<float>& endValue, const AnimationOption& option);
    static bool CancelPropertyAnimations(
        FrameNode* frameNode, const std::vector<AnimationPropertyType>& properties);
    static std::vector<float> GetRenderNodePropertyValue(FrameNode* frameNode, AnimationPropertyType property);
    static void DismissSheetStatic();
    static void DismissContentCoverStatic();
    static void SheetSpringBackStatic();
    static void SetAccessibilityTextHint(FrameNode* frameNode, const std::string& text);
    static void SetBackShadow(FrameNode *frameNode, const std::vector<Shadow>& shadows);
    static void SetLightPosition(FrameNode* frameNode, const std::optional<CalcDimension>& positionX,
        const std::optional<CalcDimension>& positionY, const std::optional<CalcDimension>& positionZ);
    static void SetLightIntensity(FrameNode* frameNode, const std::optional<float>& value);
    static void SetLightIlluminated(FrameNode *frameNode, const std::optional<uint32_t>& value,
        const RefPtr<ThemeConstants>& themeConstants);
    static void SetIlluminatedBorderWidth(FrameNode* frameNode, const Dimension& value);
    static void SetLightColor(FrameNode* frameNode, const std::optional<Color>& value);
    static void SetBloom(FrameNode *frameNode, const std::optional<float>& value,
        const RefPtr<ThemeConstants>& themeConstants);

    static void SetChainStyle(FrameNode* frameNode, const ChainInfo& chainInfo)
    {
        ViewAbstract::SetChainStyle(frameNode, chainInfo);
    }
    static void SetChainWeight(FrameNode* frameNode, const ChainWeightPair& value)
    {
        ViewAbstract::SetChainWeight(frameNode, value);
    }

    static void BindPopup(const RefPtr<FrameNode>& targetNode,
        const RefPtr<PopupParam>& param, const RefPtr<AceType>& customNode)
    {
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindPopup(param, targetNode, AceType::DynamicCast<UINode>(customNode));
    }

    static void BindTips(FrameNode* targetNode, const RefPtr<PopupParam>& param, const RefPtr<SpanString>& spanString)
    {
        CHECK_NULL_VOID(targetNode);
        ViewAbstract::BindTips(param, AceType::Claim(targetNode), spanString);
    }

    static int32_t OpenPopup(const RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode)
    {
        return ViewAbstract::OpenPopup(param, customNode);
    }

    static int32_t GetPopupParam(RefPtr<PopupParam>& param, const RefPtr<NG::UINode>& customNode)
    {
        return ViewAbstract::GetPopupParam(param, customNode);
    }

    static int32_t UpdatePopup(const RefPtr<PopupParam>& param, const RefPtr<UINode>& customNode)
    {
        return ViewAbstract::UpdatePopup(param, customNode);
    }

    static int32_t ClosePopup(const RefPtr<UINode>& customNode)
    {
        return ViewAbstract::ClosePopup(customNode);
    }

    static int32_t OpenMenu(NG::MenuParam param, const RefPtr<NG::UINode>& customNode, const int32_t& targetId)
    {
        return ViewAbstract::OpenMenu(param, customNode, targetId);
    }

    static int32_t GetMenuParam(NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode);

    static int32_t UpdateMenu(const NG::MenuParam& menuParam, const RefPtr<NG::UINode>& customNode)
    {
        return ViewAbstract::UpdateMenu(menuParam, customNode);
    }

    static int32_t CloseMenu(const RefPtr<UINode>& customNode)
    {
        return ViewAbstract::CloseMenu(customNode);
    }

    static void SetAccessibilityVirtualNode(FrameNode* frameNode, std::function<RefPtr<NG::UINode>()>&& buildFunc);
    static void SetAccessibilityDefaultFocus(FrameNode* frameNode, bool isFocus);
    static void SetAccessibilityUseSamePage(FrameNode* frameNode, const std::string& pageMode);

    static void DisableOnAccessibilityHover(FrameNode* frameNode);
    static void SetOnAccessibilityHover(FrameNode* frameNode, OnAccessibilityHoverFunc &&onAccessibilityHoverEventFunc);
    static void BindMenu(FrameNode* frameNode,
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam);
    static void BindMenuGesture(FrameNode* frameNode,
        std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc, const MenuParam& menuParam);
    static void BindContextMenuStatic(const RefPtr<FrameNode>& targetNode, ResponseType type,
        std::function<void()>&& buildFunc, NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    static void BindDragWithContextMenuParamsStatic(FrameNode* targetNode, const NG::MenuParam& menuParam);

    static void BindContentCover(FrameNode* targetNode, bool isShow,
        std::function<void(const std::string&)>&& callback, std::function<RefPtr<UINode>()>&& buildFunc,
        NG::ModalStyle& modalStyle, std::function<void()>&& onAppear, std::function<void()>&& onDisappear,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        const NG::ContentCoverParam& contentCoverParam);

    static void BindSheet(FrameNode* frameNode, bool isShow,
        std::function<void(const std::string&)>&& callback,
        std::function<void()>&& buildFunc,
        std::function<void()>&& titleBuildFunc, NG::SheetStyle& sheetStyle, std::function<void()>&& onAppear,
        std::function<void()>&& onDisappear, std::function<void()>&& shouldDismiss,
        std::function<void(const int32_t info)>&& onWillDismiss,
        std::function<void()>&& onWillAppear, std::function<void()>&& onWillDisappear,
        std::function<void(const float)>&& onHeightDidChange,
        std::function<void(const float)>&& onDetentsDidChange,
        std::function<void(const float)>&& onWidthDidChange,
        std::function<void(const float)>&& onTypeDidChange, std::function<void()>&& sheetSpringBack);

    static void SetForegroundBlurStyle(FrameNode* frameNode,
        const std::optional<BlurStyleOption>& fgBlurStyle, const std::optional<SysOptions>& sysOptions)
    {
        ViewAbstract::SetForegroundBlurStyle(frameNode, fgBlurStyle.value_or(BlurStyleOption()),
            sysOptions.value_or(DEFAULT_SYS_OPTIONS));
    }

    static void SetBackgroundBlurStyle(
        FrameNode* frameNode, const BlurStyleOption& bgBlurStyle, const std::optional<SysOptions>& sysOptions)
    {
        ViewAbstract::SetBackgroundBlurStyle(frameNode, bgBlurStyle,
            sysOptions.value_or(DEFAULT_SYS_OPTIONS));
    }

    static void SetBackgroundEffect(FrameNode* frameNode,
        const std::optional<EffectOption>& effectOption, const std::optional<SysOptions>& sysOptions);

    static void SetTranslate(FrameNode* frameNode, const NG::TranslateOptions& value);

    static void SetGeometryTransition(FrameNode* frameNode, const std::string& id,
        bool followWithoutTransition, bool doRegisterSharedTransition);

    static void SetFrontBlur(FrameNode* frameNode, const std::optional<float>& radius,
        const std::optional<BlurOption>& blurOption, const std::optional<SysOptions>& sysOptions)
    {
        Dimension radiusPX(radius.value_or(0.0f), DimensionUnit::PX);
        ViewAbstract::SetFrontBlur(frameNode, radiusPX, blurOption.value_or(BlurOption()),
            sysOptions.value_or(DEFAULT_SYS_OPTIONS));
    }

    static void SetTabStop(FrameNode* frameNode, const std::optional<bool>& value)
    {
        ViewAbstract::SetTabStop(frameNode, value.value_or(false));
    }

    static void SetVisualEffect(FrameNode* frameNode, const OHOS::Rosen::VisualEffect* visualEffect);
    static void SetBackgroundFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* backgroundFilter);
    static void SetForegroundFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* foregroundFilter);
    static void SetCompositingFilter(FrameNode* frameNode, const OHOS::Rosen::Filter* compositingFilter);
    static void SetBrightnessBlender(FrameNode* frameNode, const OHOS::Rosen::BrightnessBlender* brightnessBlender);

    static void BindBackground(FrameNode* frameNode,
        std::function<RefPtr<UINode>()>&& buildFunc, const std::optional<Alignment>& align);
    static void ResetBackground(FrameNode* frameNode);
    static void SetFlexGrow(FrameNode* frameNode, float value);
    static void SetFlexShrink(FrameNode* frameNode, float value);
    static void ResetFlexShrink(FrameNode* frameNode);
    static void SetFlexBasis(FrameNode* frameNode, const std::optional<Dimension>& optValue);
    static void SetPadding(FrameNode* frameNode, const std::optional<PaddingProperty>& value);
    static void SetMargin(FrameNode* frameNode, const std::optional<PaddingProperty>& value);
    static void SetAspectRatio(FrameNode* frameNode, float ratio);
    static void ResetAspectRatio(FrameNode* frameNode);
    static void SetLayoutWeight(FrameNode* frameNode, float value);
    static void SetAlignSelf(FrameNode* frameNode, FlexAlign value);
    static void SetLayoutGravity(FrameNode* frameNode, Alignment value);
    static void SetLayoutDirection(FrameNode* frameNode, TextDirection value);
    static void SetBorderStyle(FrameNode *frameNode, const BorderStyleProperty& value);
    static void SetBorderWidth(FrameNode *frameNode, const BorderWidthProperty& value);
    static void SetBorderColor(FrameNode *frameNode, const BorderColorProperty& value);
    static void SetBorderRadius(FrameNode *frameNode, const BorderRadiusProperty& value);
    static void SetRenderStrategy(FrameNode* frameNode, const RenderStrategy& type);
    static void SetBorderImage(FrameNode* frameNode, const RefPtr<BorderImage>& boderImage, uint8_t bitset);
    static void SetBorderImageSource(FrameNode* frameNode, const std::string& imageSrc, const std::string& bundleName,
        const std::string& moduleName);
    static void SetDashGap(FrameNode *frameNode, const BorderWidthProperty& value);
    static void SetDashWidth(FrameNode *frameNode, const BorderWidthProperty& value);
    static void SetAlign(FrameNode* frameNode, Alignment alignment);
    static void SetAlign(FrameNode* frameNode, std::string localizedAlignment);
    static void SetPosition(FrameNode* frameNode, const OffsetT<Dimension>& value);
    static void SetPositionEdges(FrameNode* frameNode, const EdgesParam& value);
    static void SetPositionLocalizedEdges(FrameNode* frameNode, bool needLocalized);
    static void SetTransform3DMatrix(FrameNode* frameNode, const Matrix4& matrix);
    static void SetMarkAnchorStart(FrameNode* frameNode, const std::optional<Dimension>& markAnchorStart);
    static void MarkAnchor(FrameNode* frameNode, const std::optional<OffsetT<Dimension>>& value);
    static void ResetMarkAnchorStart(FrameNode* frameNode);
    static void SetOffset(FrameNode* frameNode, const OffsetT<Dimension>& value);
    static void SetOffsetEdges(FrameNode* frameNode, const EdgesParam& value);
    static void SetOffsetLocalizedEdges(FrameNode* frameNode, bool needLocalized);
    static void UpdateSafeAreaExpandOpts(FrameNode* frameNode, const SafeAreaExpandOpts& opts);
    static void UpdateIgnoreLayoutSafeAreaOpts(FrameNode* frameNode, const IgnoreLayoutSafeAreaOpts& opts);
    static void SetAlignRules(FrameNode* frameNode,
        const std::optional<std::map<AlignDirection, AlignRule>>& alignRules);
    static void SetBias(FrameNode* frameNode, const std::optional<BiasPair>& biasPair);
    static void SetBias(FrameNode* frameNode, const std::optional<float>& horizontal,
        const std::optional<float>& vertical);
    static void SetKeyboardShortcut(FrameNode* frameNode, const std::string& value,
        const std::vector<ModifierKey>& keys, std::function<void()>&& onKeyboardShortcutAction);
    static void SetPixelRound(FrameNode* frameNode, uint16_t value);
    static void SetMaxWidth(FrameNode* frameNode, const CalcDimension& minWidth);
    static void SetMaxHeight(FrameNode* frameNode, const CalcDimension& minHeight);
    static void SetDisplayIndex(FrameNode* frameNode, int32_t value);
    static void SetBackgroundColor(FrameNode *frameNode, const std::optional<Color>& color);
    static void SetPivot(FrameNode* frameNode, const std::optional<DimensionOffset>& optValue);
    static void SetRotate(FrameNode* frameNode, const std::vector<std::optional<float>>& value);
    static void SetRotateAngle(FrameNode* frameNode, const std::vector<std::optional<float>>& value);
    static void SetBackdropBlur(FrameNode* frameNode, const std::optional<Dimension>& radius,
        const std::optional<BlurOption> &blurOption, const SysOptions& sysOptions = SysOptions());
    static void SetClipEdge(FrameNode* frameNode, std::optional<bool> isClip);
    static void SetTransformMatrix(FrameNode* frameNode, const std::optional<Matrix4>& matrix);
    static void SetLinearGradientBlur(FrameNode *frameNode,
        const std::optional<NG::LinearGradientBlurPara>& blurPara);
    static void SetRenderFit(FrameNode* frameNode, const std::optional<RenderFit>& renderFit);
    static void SetForegroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void SetForegroundColorStrategy(FrameNode* frameNode,
        const std::optional<ForegroundColorStrategy>& strategy);
    static void SetForegroundEffect(FrameNode* frameNode, const std::optional<float>& radius);
    static void SetBlendMode(FrameNode* frameNode, const std::optional<BlendMode>& blendMode);
    static void SetFocusBoxStyle(FrameNode* frameNode, const std::optional<NG::FocusBoxStyle>& style);
    static void SetFocusScopeId(FrameNode* frameNode, const std::optional<std::string>& focusScopeId,
        const std::optional<bool>& isGroup, const std::optional<bool>& arrowKeyStepOut);
    static void SetFocusScopePriority(FrameNode* frameNode, const std::optional<std::string>& focusScopeId,
        const std::optional<uint32_t>& focusPriority);
    static void SetGrayScale(FrameNode* frameNode, const std::optional<Dimension>& grayScale);
    static void SetColorBlend(FrameNode* frameNode, const std::optional<Color>& colorBlend);
    static void SetUseShadowBatching(FrameNode* frameNode, std::optional<bool> useShadowBatching);
    static void SetUseEffect(
        FrameNode* frameNode, const std::optional<bool>& useEffectOpt, const std::optional<EffectType>& effectTypeOpt);
    static void SetInvert(FrameNode* frameNode, const std::optional<InvertVariant>& invertOpt);
    static void SetDrawModifier(FrameNode* frameNode, const RefPtr<NG::DrawModifier>& drawModifier);
    static void SetFreeze(FrameNode* frameNode, std::optional<bool> freeze);
    static void SetClickEffectLevel(FrameNode* frameNode,
        const std::optional<ClickEffectLevel>& level, std::optional<float> scaleValue);
    static void SetBrightness(FrameNode* frameNode, const std::optional<Dimension>& brightness);
    static void SetContrast(FrameNode* frameNode, const std::optional<Dimension>& contrast);
    static void SetSphericalEffect(FrameNode* frameNode, const std::optional<double> radio);
    static void SetLightUpEffect(FrameNode* frameNode, const std::optional<double> radio);
    static void SetPixelStretchEffect(FrameNode* frameNode,
        const std::optional<PixStretchEffectOption>& option);
    static void SetBlendApplyType(FrameNode* frameNode, const std::optional<BlendApplyType>& blendApplyType);
    static void SetPrivacySensitive(FrameNode* frameNode, const std::optional<bool>& flag);
    static void SetOnTouchTestFunc(FrameNode* frameNode, NG::OnChildTouchTestFunc&& onChildTouchTest);
    static void SetOnGestureRecognizerJudgeBegin(
        FrameNode* frameNode, GestureRecognizerJudgeFunc&& gestureRecognizerJudgeFunc, bool innerGestureFlag = false);
    static void SetOuterBorderWidth(FrameNode* frameNode, const BorderWidthProperty& value);
    static void SetOuterBorderRadius(FrameNode* frameNode, const BorderRadiusProperty& value);
    static void SetOuterBorderColor(FrameNode* frameNode, const BorderColorProperty& value);
    static void SetOuterBorderStyle(FrameNode* frameNode, const BorderStyleProperty& value);
    static void SetAllowDrop(FrameNode* frameNode, const std::optional<std::set<std::string>>& allowDrop);
    static void SetDragPreview(FrameNode* frameNode, const std::optional<DragDropInfo>& DragDropInfo);
    static void SetBackgroundImage(FrameNode* frameNode, const std::optional<ImageSourceInfo>& src);
    static void SetBackgroundImageRepeat(FrameNode* frameNode, const std::optional<ImageRepeat>& imageRepeat);
    static void SetBackgroundImageSyncMode(FrameNode* frameNode, bool syncMode);
    static void SetClipShape(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape);
    static void SetMask(FrameNode* frameNode, const RefPtr<BasicShape>& basicShape);
    static void SetBackgroundImagePosition(FrameNode* frameNode, BackgroundImagePosition& bgImgPosition, bool isReset);
    static void ResetOverlay(FrameNode* frameNode);
    static constexpr SysOptions DEFAULT_SYS_OPTIONS = {
        .disableSystemAdaptation = false
    };
    static void SetSystemBarEffect(FrameNode* frameNode, bool systemBarEffect);

private:
    static bool CheckMenuIsShow(
        const MenuParam& menuParam, int32_t targetId, const RefPtr<FrameNode>& targetNode,  bool isBuildFuncNull);
    static void RegisterContextMenuKeyEvent(
        const RefPtr<FrameNode>& targetNode, std::function<void()>& buildFunc, const MenuParam& menuParam);
    static void CreateCustomMenuWithPreview(FrameNode* targetNode,
        std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
    static void BindContextMenuSingle(FrameNode* targetNode,
        std::function<void()>&& buildFunc, const MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
};


// multi thread function start
void SetBackgroundEffectMultiThread(FrameNode* frameNode,
    const std::optional<EffectOption>& effectOption, const std::optional<SysOptions>& sysOptions);
void SetTranslateMultiThread(FrameNode* frameNode, const NG::TranslateOptions& value);
void SetGeometryTransitionMultiThread(FrameNode* frameNode, const std::string& id,
    bool followWithoutTransition, bool doRegisterSharedTransition);
void BindMenuMultiThread(FrameNode* frameNode, std::vector<NG::OptionParam>&& params, std::function<void()>&& buildFunc,
    const MenuParam& menuParam);
void BindContextMenuStaticMultiThread(const RefPtr<FrameNode>& targetNode, ResponseType type,
    std::function<void()>&& buildFunc, NG::MenuParam& menuParam, std::function<void()>&& previewBuildFunc);
// multi thread function end
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_STATIC_H

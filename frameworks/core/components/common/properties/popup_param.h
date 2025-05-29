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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_POPUP_PARAM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_POPUP_PARAM_H

#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "core/common/resource/resource_object.h"
#include "core/components/common/properties/border.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/edge.h"
#include "core/components/common/properties/placement.h"
#include "core/components/common/properties/text_style.h"
#include "core/components_ng/event/click_event.h"
#include "core/components_ng/property/transition_property.h"
#include "core/event/ace_event_handler.h"
#include "core/event/touch_event.h"

namespace OHOS::Ace {

using ComposeId = std::string;

struct ButtonProperties {
    bool showButton = false;
    std::string value;
    EventMarker actionId;
    //  touchFunc used in Declarative mode.
    TouchEventFunc touchFunc;
    RefPtr<NG::ClickEvent> action; // button click action
};

struct PopupGradientColor {
    Color gradientColor;
    double gradientNumber;
};

struct PopupLinearGradientProperties {
    GradientDirection popupDirection;
    std::vector<PopupGradientColor> gradientColors;
};

enum class PopupKeyboardAvoidMode {
    DEFAULT,
    NONE
};

enum class TipsAnchorType {
    TARGET = 0, // anchor to target node
    CURSOR = 1  // anchor to cursor position
};

using StateChangeFunc = std::function<void(const std::string&)>;
using OnWillDismiss = std::function<void(int32_t)>;
class PopupParam : public AceType {
    DECLARE_ACE_TYPE(PopupParam, AceType)

public:
    PopupParam() = default;
    ~PopupParam() override = default;

    void SetIsShow(bool isShow)
    {
        isShow_ = isShow;
    }

    bool IsShow() const
    {
        return isShow_;
    }

    void SetHasAction(bool hasAction)
    {
        hasAction_ = hasAction;
    }

    bool HasAction() const
    {
        return hasAction_;
    }

    void SetPlacement(const Placement& placement)
    {
        placement_ = placement;
    }

    void SetMaskColor(const Color& maskColor)
    {
        maskColor_ = maskColor;
        isMaskColorSetted_ = true;
    }

    void SetBackgroundColor(const Color& backgroundColor)
    {
        backgroundColor_ = backgroundColor;
        isBackgroundColorSetted_ = true;
    }

    void SetOnVisibilityChange(const EventMarker& onVisibilityChange)
    {
        onVisibilityChange_ = onVisibilityChange;
    }

    Placement GetPlacement() const
    {
        return placement_;
    }

    void SetAppearingTime(int32_t appearingTime)
    {
        appearingTime_ = appearingTime;
    }

    int32_t GetAppearingTime() const
    {
        return appearingTime_;
    }

    void SetDisappearingTime(int32_t disappearingTime)
    {
        disappearingTime_ = disappearingTime;
    }

    int32_t GetDisappearingTime() const
    {
        return disappearingTime_;
    }

    void SetAppearingTimeWithContinuousOperation(int32_t appearingTimeWithContinuousOperation)
    {
        appearingTimeWithContinuousOperation_ = appearingTimeWithContinuousOperation;
    }

    int32_t GetAppearingTimeWithContinuousOperation() const
    {
        return appearingTimeWithContinuousOperation_;
    }

    void SetDisappearingTimeWithContinuousOperation(int32_t disappearingTimeWithContinuousOperation)
    {
        disappearingTimeWithContinuousOperation_ = disappearingTimeWithContinuousOperation;
    }

    int32_t GetDisappearingTimeWithContinuousOperation() const
    {
        return disappearingTimeWithContinuousOperation_;
    }

    const Color& GetMaskColor() const
    {
        return maskColor_;
    }

    const Color& GetBackgroundColor() const
    {
        return backgroundColor_;
    }

    const EventMarker& GetOnVisibilityChange() const
    {
        return onVisibilityChange_;
    }

    const Edge& GetMargin() const
    {
        return margin_;
    }

    void SetMargin(const Edge& margin)
    {
        margin_ = margin;
    }

    const Edge& GetTargetMargin() const
    {
        return targetMargin_;
    }

    void SetTargetMargin(const Edge& targetMargin)
    {
        targetMargin_ = targetMargin;
    }

    const Edge& GetPadding() const
    {
        return padding_;
    }

    void SetPadding(const Edge& padding)
    {
        padding_ = padding;
    }

    const Border& GetBorder() const
    {
        return border_;
    }

    void SetBorder(const Border& border)
    {
        border_ = border;
    }

    const std::optional<Dimension>& GetArrowOffset() const
    {
        return arrowOffset_;
    }

    void SetArrowOffset(const std::optional<Dimension>& arrowOffset)
    {
        arrowOffset_ = arrowOffset;
    }

    const ComposeId& GetTargetId() const
    {
        return targetId_;
    }

    void SetTargetId(const ComposeId& targetId)
    {
        targetId_ = targetId;
    }

    bool IsMaskColorSetted() const
    {
        return isMaskColorSetted_;
    }

    bool IsBackgroundColorSetted() const
    {
        return isBackgroundColorSetted_;
    }

    bool EnableArrow() const
    {
        return enableArrow_;
    }

    void SetEnableArrow(bool enableArrow)
    {
        enableArrow_ = enableArrow;
    }

    bool HasEnableHoverMode() const
    {
        return enableHoverMode_.has_value();
    }

    bool EnableHoverMode() const
    {
        return enableHoverMode_.value_or(false);
    }

    void SetEnableHoverMode(bool enableHoverMode)
    {
        enableHoverMode_ = enableHoverMode;
    }

    bool IsBlockEvent() const
    {
        return blockEvent_;
    }

    void SetBlockEvent(bool blockEvent)
    {
        blockEvent_ = blockEvent;
    }

    bool IsUseCustom() const
    {
        return useCustom_;
    }

    void SetUseCustomComponent(bool useCustom)
    {
        useCustom_ = useCustom;
    }

    const std::optional<Dimension>& GetTargetSpace() const
    {
        return targetSpace_;
    }

    const std::optional<Dimension>& GetChildWidth() const
    {
        return childwidth_;
    }

    void SetTargetSpace(const Dimension& targetSpace)
    {
        targetSpace_ = targetSpace;
    }

    void SetChildWidth(const Dimension& childWidth)
    {
        childwidth_ = childWidth;
    }

    void SetMessage(const std::string& msg)
    {
        message_ = msg;
    }

    std::string GetMessage() const
    {
        return message_;
    }

    StateChangeFunc GetOnStateChange()
    {
        return onStateChange_;
    }

    void SetOnStateChange(StateChangeFunc&& onStateChange)
    {
        onStateChange_ = onStateChange;
    }

    void SetPrimaryButtonProperties(const ButtonProperties& prop)
    {
        primaryButtonProperties_ = prop;
    }

    void SetSecondaryButtonProperties(const ButtonProperties& prop)
    {
        secondaryButtonProperties_ = prop;
    }

    const ButtonProperties& GetPrimaryButtonProperties() const
    {
        return primaryButtonProperties_;
    }

    const ButtonProperties& GetSecondaryButtonProperties() const
    {
        return secondaryButtonProperties_;
    }

    void SetShowInSubWindow(bool isShowInSubWindow)
    {
        isShowInSubWindow_ = isShowInSubWindow;
    }

    bool IsShowInSubWindow() const
    {
        return isShowInSubWindow_;
    }

    void SetTargetSize(const Size& targetSize)
    {
        targetSize_ = targetSize;
    }

    const Size& GetTargetSize() const
    {
        return targetSize_;
    }

    void SetTargetOffset(const Offset& targetOffset)
    {
        targetOffset_ = targetOffset;
    }

    const Offset& GetTargetOffset() const
    {
        return targetOffset_;
    }

    void SetTextColor(const Color& textColor)
    {
        textColor_ = textColor;
    }

    const std::optional<Color>& GetTextColor() const
    {
        return textColor_;
    }

    void SetFontSize(const Dimension& fontSize)
    {
        fontSize_ = fontSize;
    }

    const std::optional<Dimension>& GetFontSize() const
    {
        return fontSize_;
    }

    void SetFontWeight(const FontWeight& fontWeight)
    {
        fontWeight_ = fontWeight;
    }

    const std::optional<FontWeight>& GetFontWeight() const
    {
        return fontWeight_;
    }

    void SetFontStyle(const FontStyle& fontStyle)
    {
        fontStyle_ = fontStyle;
    }

    const std::optional<FontStyle>& GetFontStyle() const
    {
        return fontStyle_;
    }

    const std::optional<Dimension>& GetArrowWidth() const
    {
        return arrowWidth_;
    }

    void SetArrowWidth(const Dimension& arrowWidth)
    {
        arrowWidth_ = arrowWidth;
    }

    const std::optional<Dimension>& GetArrowHeight() const
    {
        return arrowHeight_;
    }

    void SetArrowHeight(const Dimension& arrowHeight)
    {
        arrowHeight_ = arrowHeight;
    }

    const std::optional<Dimension>& GetRadius() const
    {
        return radius_;
    }

    void SetRadius(const Dimension& radius)
    {
        radius_ = radius;
    }

    void SetShadow(const Shadow& shadow)
    {
        shadow_ = shadow;
    }

    const std::optional<Shadow>& GetShadow() const
    {
        return shadow_;
    }

    void SetErrorArrowWidth(bool setErrorArrowWidth)
    {
        setErrorArrowWidth_ = setErrorArrowWidth;
    }

    bool GetErrorArrowWidth() const
    {
        return setErrorArrowWidth_;
    }

    void SetErrorArrowHeight(bool setErrorArrowHeight)
    {
        setErrorArrowHeight_ = setErrorArrowHeight;
    }

    bool GetErrorArrowHeight() const
    {
        return setErrorArrowHeight_;
    }

    void SetErrorRadius(bool setErrorRadius)
    {
        setErrorRadius_ = setErrorRadius;
    }

    bool GetErrorRadius() const
    {
        return setErrorRadius_;
    }

    void SetFocusable(bool focusable)
    {
        focusable_ = focusable;
    }

    bool GetFocusable() const
    {
        return focusable_;
    }

    void SetBlurStyle(const BlurStyle& blurStyle)
    {
        blurStyle_ = blurStyle;
    }

    BlurStyle GetBlurStyle() const
    {
        return blurStyle_;
    }

    void SetInteractiveDismiss(bool interactiveDismiss)
    {
        interactiveDismiss_ = interactiveDismiss;
    }

    bool GetInteractiveDismiss() const
    {
        return interactiveDismiss_;
    }

    void SetOnWillDismiss(const OnWillDismiss&& onWillDismiss)
    {
        onWillDismiss_ = std::move(onWillDismiss);
    }

    OnWillDismiss GetOnWillDismiss() const
    {
        return onWillDismiss_;
    }
    void SetHasTransition(bool hasTransition)
    {
        hasTransition_ = hasTransition;
    }

    bool GetHasTransition() const
    {
        return hasTransition_;
    }

    void SetTransitionEffects(const RefPtr<NG::ChainedTransitionEffect>& transitionEffects)
    {
        transitionEffects_ = transitionEffects;
    }

    const RefPtr<NG::ChainedTransitionEffect> GetTransitionEffects() const
    {
        return transitionEffects_;
    }

    void SetIsCaretMode (bool isCaretMode)
    {
        isCaretMode_ = isCaretMode;
    }

    bool IsCaretMode() const
    {
        return isCaretMode_;
    }

    void SetKeyBoardAvoidMode (PopupKeyboardAvoidMode keyboardAvoidMode)
    {
        keyboardAvoidMode_ = keyboardAvoidMode;
    }

    PopupKeyboardAvoidMode GetKeyBoardAvoidMode() const
    {
        return keyboardAvoidMode_;
    }

    StateChangeFunc GetDoubleBindCallback()
    {
        return doubleBindCallback_;
    }

    void SetDoubleBindCallback(StateChangeFunc&& callback)
    {
        doubleBindCallback_ = callback;
    }

    void SetFollowTransformOfTarget (bool followTransformOfTarget)
    {
        followTransformOfTarget_ = followTransformOfTarget;
    }

    bool IsFollowTransformOfTarget() const
    {
        return followTransformOfTarget_;
    }

    std::optional<bool> GetIsPartialUpdate() const
    {
        return isPartialUpdate_;
    }

    void SetIsPartialUpdate(bool isPartialUpdate)
    {
        isPartialUpdate_ = isPartialUpdate;
    }

    void SetTipsFlag(bool isTips)
    {
        isTips_ = isTips;
    }

    bool IsTips() const
    {
        return isTips_;
    }
    void SetOutlineLinearGradient(const PopupLinearGradientProperties& outlineLinearGradient)
    {
        outlineLinearGradient_ = outlineLinearGradient;
    }

    const PopupLinearGradientProperties& GetOutlineLinearGradient() const
    {
        return outlineLinearGradient_;
    }

    void SetOutlineWidth(const std::optional<Dimension>& outlineWidth)
    {
        outlineWidth_ = outlineWidth;
    }

    const std::optional<Dimension>& GetOutlineWidth() const
    {
        return outlineWidth_;
    }

    void SetInnerBorderLinearGradient(const PopupLinearGradientProperties& innerBorderLinearGradient)
    {
        innerBorderLinearGradient_ = innerBorderLinearGradient;
    }

    const PopupLinearGradientProperties& GetInnerBorderLinearGradient() const
    {
        return innerBorderLinearGradient_;
    }

    void SetInnerBorderWidth(const std::optional<Dimension>& innerBorderWidth)
    {
        innerBorderWidth_ = innerBorderWidth;
    }

    const std::optional<Dimension>& GetInnerBorderWidth() const
    {
        return innerBorderWidth_;
    }

    void SetTextColorResourceObject(RefPtr<ResourceObject>& obj)
    {
        resourceTextColorObj_ = obj;
    }

    const RefPtr<ResourceObject>& GetTextColorResourceObject()
    {
        return resourceTextColorObj_;
    }

    void SetPopupColorResourceObject(RefPtr<ResourceObject>& obj)
    {
        resourcePopupColorObj_ = obj;
    }

    const RefPtr<ResourceObject>& GetPopupColorResourceObject()
    {
        return resourcePopupColorObj_;
    }

    void SetMaskColorResourceObject(RefPtr<ResourceObject>& obj)
    {
        resourceMaskColorObj_ = obj;
    }

    const RefPtr<ResourceObject>& GetMaskColorResourceObject()
    {
        return resourceMaskColorObj_;
    }

    void SetMasResourceObject(RefPtr<ResourceObject>& obj)
    {
        resourceMaskObj_ = obj;
    }

    const RefPtr<ResourceObject>& GetMasResourceObject()
    {
        return resourceMaskObj_;
    }

    void SetAnchorType(TipsAnchorType anchorType)
    {
        anchorType_ = anchorType;
        if (anchorType == TipsAnchorType::CURSOR) {
            enableArrow_ = false;
            placement_ = Placement::BOTTOM_LEFT;
        }
    }

    TipsAnchorType GetAnchorType() const
    {
        return anchorType_;
    }

private:
    bool isShow_ = true;
    bool hasAction_ = false;
    bool enableArrow_ = true;
    bool isMaskColorSetted_ = false;
    bool isBackgroundColorSetted_ = false;
    bool useCustom_ = false;
    bool isShowInSubWindow_ = false;
    bool blockEvent_ = true;
    bool setErrorArrowWidth_ = false;
    bool setErrorArrowHeight_ = false;
    bool setErrorRadius_ = false;
    bool focusable_ = false;
    bool interactiveDismiss_ = true;
    bool isCaretMode_ = true;
    std::optional<bool> enableHoverMode_ = std::nullopt;
    bool followTransformOfTarget_ = false;
    bool isTips_ = false;
    TipsAnchorType anchorType_ = TipsAnchorType::TARGET;
    int32_t appearingTime_ = 700;
    int32_t disappearingTime_ = 300;
    int32_t appearingTimeWithContinuousOperation_ = 300;
    int32_t disappearingTimeWithContinuousOperation_ = 0;
    std::optional<bool> isPartialUpdate_;
    Color maskColor_;
    Color backgroundColor_;
    Placement placement_ = Placement::BOTTOM;
    BlurStyle blurStyle_ = BlurStyle::COMPONENT_ULTRA_THICK;
    EventMarker onVisibilityChange_;
    Edge padding_;
    Edge margin_;
    Edge targetMargin_;
    Border border_;
    std::optional<Dimension> arrowOffset_;
    ComposeId targetId_;
    std::optional<Dimension> targetSpace_;
    std::optional<Dimension> childwidth_;
    std::string message_;
    Offset targetOffset_;
    Size targetSize_;
    std::optional<FontWeight> fontWeight_;
    std::optional<Color> textColor_;
    std::optional<Dimension> fontSize_;
    std::optional<FontStyle> fontStyle_;

    std::optional<Dimension> arrowWidth_;
    std::optional<Dimension> arrowHeight_;
    std::optional<Dimension> radius_;
    std::optional<Shadow> shadow_;
    // Used in NG mode
    StateChangeFunc onStateChange_;
    ButtonProperties primaryButtonProperties_;   // first button.
    ButtonProperties secondaryButtonProperties_; // second button.
    OnWillDismiss onWillDismiss_;
    bool hasTransition_ = false;
    RefPtr<NG::ChainedTransitionEffect> transitionEffects_ = nullptr;
    StateChangeFunc doubleBindCallback_;
    PopupKeyboardAvoidMode keyboardAvoidMode_ = PopupKeyboardAvoidMode::NONE;
    std::optional<Dimension> outlineWidth_;
    std::optional<Dimension> innerBorderWidth_;
    PopupLinearGradientProperties outlineLinearGradient_;
    PopupLinearGradientProperties innerBorderLinearGradient_;
    RefPtr<ResourceObject> resourceTextColorObj_;
    RefPtr<ResourceObject> resourcePopupColorObj_;
    RefPtr<ResourceObject> resourceMaskColorObj_;
    RefPtr<ResourceObject> resourceMaskObj_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_BASE_PROPERTIES_POPUP_PARAM_H

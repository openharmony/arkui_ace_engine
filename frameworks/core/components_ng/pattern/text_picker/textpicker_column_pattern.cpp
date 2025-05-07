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

#include "core/components_ng/pattern/text_picker/textpicker_column_pattern.h"

#include <cstdint>
#include <cstdlib>

#include "adapter/ohos/entrance/picker/picker_haptic_factory.h"
#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "core/common/container.h"
#include "core/common/font_manager.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/button/button_layout_property.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension FONT_SIZE = Dimension(2.0);
const Dimension FOCUS_SIZE = Dimension(1.0);
const float MOVE_DISTANCE = 5.0f;
const double MOVE_THRESHOLD = Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE) ? 2.0 : 1.0;
constexpr float FONTWEIGHT = 0.5f;
constexpr float FONT_SIZE_PERCENT = 1.0f;
constexpr int32_t HOVER_ANIMATION_DURATION = 40;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr size_t MIXTURE_CHILD_COUNT = 2;
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const Dimension ICON_SIZE = 24.0_vp;
const Dimension ICON_TEXT_SPACE = 8.0_vp;
const std::vector<std::string> FONT_FAMILY_DEFAULT = { "sans-serif" };
const std::string MEASURE_STRING = "TEST";
const int32_t HALF_NUMBER = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
const double CURVE_MOVE_THRESHOLD = 0.5;
constexpr char PICKER_DRAG_SCENE[] = "picker_drag_scene";
const uint32_t NEXT_COLOUM_DIFF = 1;
} // namespace

void TextPickerColumnPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto hub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    tossAnimationController_->SetPipelineContext(context);
    tossAnimationController_->SetColumn(AceType::WeakClaim(this));
    overscroller_.SetColumn(AceType::WeakClaim(this));
    jumpInterval_ = pickerTheme->GetJumpInterval().ConvertToPx();
    CreateAnimation();
    InitPanEvent(gestureHub);
    host->GetRenderContext()->SetClipToFrame(true);
    InitHapticController(host);
    RegisterWindowStateChangedCallback();
}

void TextPickerColumnPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    UnregisterWindowStateChangedCallback(frameNode);
}

bool TextPickerColumnPattern::OnDirtyLayoutWrapperSwap(
    const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config)
{
    bool isChange =
        config.frameSizeChange || config.frameOffsetChange || config.contentSizeChange || config.contentOffsetChange;

    CHECK_NULL_RETURN(isChange, false);
    CHECK_NULL_RETURN(dirty, false);
    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto layoutAlgorithm = DynamicCast<TextPickerLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithm, false);
    halfDisplayCounts_ = layoutAlgorithm->GetHalfDisplayCounts();
    return true;
}

void TextPickerColumnPattern::OnModifyDone()
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(theme);
    pressColor_ = theme->GetPressColor();
    hoverColor_ = theme->GetHoverColor();
    useButtonFocusArea_ = theme->NeedButtonFocusAreaType();
    InitTextFadeOut();
    InitSelectorButtonProperties(theme);
    InitMouseAndPressEvent();
    SetAccessibilityAction();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (optionProperties_.size() <= 0) {
        dividerSpacing_ = pipeline->NormalizeToPx(theme->GetDividerSpacing());
        gradientHeight_ = static_cast<float>(pipeline->NormalizeToPx(theme->GetGradientHeight()));

        auto showCount = GetShowOptionCount();
        auto midIndex = showCount / HALF_NUMBER;
        uint32_t childIndex = 0;
        while (childIndex < showCount) {
            TextPickerOptionProperty prop;
            InitTextHeightAndFontHeight(childIndex, midIndex, prop);
            optionProperties_.emplace_back(prop);
            childIndex++;
        }
        SetOptionShiftDistance();
    }
    InitHapticController(host);
}

void TextPickerColumnPattern::InitHapticController(const RefPtr<FrameNode>& host)
{
    CHECK_NULL_VOID(host);
    if (host->LessThanAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN)) {
        return;
    }
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto textPickerPattern = parentNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(textPickerPattern);
    if (textPickerPattern->GetIsEnableHaptic()) {
        isEnableHaptic_ = true;
        if (!hapticController_) {
            auto context = parentNode->GetContext();
            CHECK_NULL_VOID(context);
            context->AddAfterLayoutTask([weak = WeakClaim(this)]() {
                auto pattern = weak.Upgrade();
                CHECK_NULL_VOID(pattern);
                pattern->hapticController_ = PickerAudioHapticFactory::GetInstance();
            });
        }
    } else {
        isEnableHaptic_ = false;
        if (hapticController_) {
            hapticController_->Stop();
        }
    }
}

void TextPickerColumnPattern::RegisterWindowStateChangedCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddWindowStateChangedCallback(host->GetId());
}

void TextPickerColumnPattern::UnregisterWindowStateChangedCallback(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
}

void TextPickerColumnPattern::OnWindowHide()
{
    isShow_ = false;
    if (hapticController_) {
        hapticController_->Stop();
    }
}

void TextPickerColumnPattern::StopHapticController()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
}

void TextPickerColumnPattern::OnWindowShow()
{
    isShow_ = true;
}

void TextPickerColumnPattern::OnMiddleButtonTouchDown()
{
    PlayPressAnimation(pressColor_);
}

void TextPickerColumnPattern::OnMiddleButtonTouchMove()
{
    PlayPressAnimation(Color::TRANSPARENT);
}

void TextPickerColumnPattern::OnMiddleButtonTouchUp()
{
    PlayPressAnimation(isHover_ ? GetButtonHoverColor() : buttonBgColor_);

    if (useButtonFocusArea_) {
        FlushCurrentOptions();
    }
}

void TextPickerColumnPattern::InitSelectorButtonProperties(const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    if (useButtonFocusArea_) {
        buttonDefaultBgColor_ = pickerTheme->GetSelectorItemNormalBgColor();
        buttonFocusBgColor_ = pickerTheme->GetSelectorItemFocusBgColor();
        buttonDefaultBorderColor_ = pickerTheme->GetSelectorItemBorderColor();
        buttonFocusBorderColor_ = pickerTheme->GetSelectorItemFocusBorderColor();
        selectorTextFocusColor_ = pickerTheme->GetOptionStyle(true, true).GetTextColor();
        pressColor_ = buttonDefaultBgColor_.BlendColor(pickerTheme->GetPressColor());
        hoverColor_ = buttonDefaultBgColor_.BlendColor(pickerTheme->GetHoverColor());

        buttonFocusBorderWidth_ = pickerTheme->GetSelectorItemFocusBorderWidth();
        buttonDefaultBorderWidth_ = pickerTheme->GetSelectorItemBorderWidth();
    }
}

const Color& TextPickerColumnPattern::GetButtonHoverColor() const
{
    return useButtonFocusArea_ && isFocusColumn_ ? buttonFocusBgColor_ : hoverColor_;
}

void TextPickerColumnPattern::UpdateColumnButtonFocusState(bool haveFocus, bool needMarkDirty)
{
    auto isInitUpdate = isFirstTimeUpdateButtonProps_ && !haveFocus;
    auto isFocusChanged = isFocusColumn_ != haveFocus;

    if (isFocusChanged || isInitUpdate) {
        isFocusColumn_ = haveFocus;
        UpdateSelectorButtonProps(isFocusColumn_, needMarkDirty);
    }
    if (isFocusChanged) {
        FlushCurrentOptions();
    }
    if (isInitUpdate) {
        isFirstTimeUpdateButtonProps_ = false;
    }
}

void TextPickerColumnPattern::UpdateSelectorButtonProps(bool haveFocus, bool needMarkDirty)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blend = host->GetParent();
    CHECK_NULL_VOID(blend);
    auto stack = blend->GetParent();
    CHECK_NULL_VOID(stack);
    auto buttonNode = DynamicCast<FrameNode>(stack->GetFirstChild());
    CHECK_NULL_VOID(buttonNode);
    auto buttonLayoutProperty = buttonNode->GetLayoutProperty<ButtonLayoutProperty>();
    CHECK_NULL_VOID(buttonLayoutProperty);
    auto renderContext = buttonNode->GetRenderContext();
    CHECK_NULL_VOID(renderContext);

    BorderWidthProperty borderWidth;
    BorderColorProperty borderColor;

    if (haveFocus) {
        buttonBgColor_ = buttonFocusBgColor_;
        borderWidth.SetBorderWidth(buttonFocusBorderWidth_);
        borderColor.SetColor(buttonFocusBorderColor_);
    } else {
        buttonBgColor_ = buttonDefaultBgColor_;
        borderWidth.SetBorderWidth(buttonDefaultBorderWidth_);
        borderColor.SetColor(buttonDefaultBorderColor_);
    }

    buttonLayoutProperty->UpdateBorderWidth(borderWidth);
    renderContext->UpdateBorderColor(borderColor);
    renderContext->UpdateBackgroundColor(buttonBgColor_);

    if (needMarkDirty) {
        buttonNode->MarkModifyDone();
        buttonNode->MarkDirtyNode();
    }
}

void TextPickerColumnPattern::UpdateTextAreaPadding(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (useButtonFocusArea_) {
        auto padding = pickerTheme->GetSelectorItemSpace();
        PaddingProperty defaultPadding = { CalcLength(padding), CalcLength(padding),
            CalcLength(0.0_vp), CalcLength(0.0_vp) };
        textLayoutProperty->UpdatePadding(defaultPadding);
    }
}

void TextPickerColumnPattern::InitTextFadeOut()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContextRefPtr();
    CHECK_NULL_VOID(context);
    auto textTheme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(textTheme);
    isTextFadeOut_ = textTheme->GetIsTextFadeout();
}

void TextPickerColumnPattern::UpdateTextOverflow(bool isSel, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    if (isTextFadeOut_) {
        textLayoutProperty->UpdateTextOverflow(TextOverflow::MARQUEE);
        textLayoutProperty->UpdateTextMarqueeStartPolicy(MarqueeStartPolicy::DEFAULT);
        textLayoutProperty->UpdateTextMarqueeFadeout(true);
        textLayoutProperty->UpdateTextMarqueeStart(isSel && (isFocusColumn_ || isHover_));
    }
}

int32_t TextPickerColumnPattern::GetMiddleButtonIndex()
{
    return GetShowOptionCount() / 2;
}

RefPtr<TouchEventImpl> TextPickerColumnPattern::CreateItemTouchEventListener()
{
    auto toss = GetToss();
    CHECK_NULL_RETURN(toss, nullptr);
    auto touchCallback = [weak = WeakClaim(this), toss](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        auto isToss = pattern->GetTossStatus();
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (isToss) {
                pattern->touchBreak_ = true;
                pattern->animationBreak_ = true;
                pattern->clickBreak_ = true;
                auto TossEndPosition = toss->GetTossEndPosition();
                pattern->SetYLast(TossEndPosition);
                toss->StopTossAnimation();
                pattern->StopHapticController();
            } else {
                pattern->animationBreak_ = false;
                pattern->clickBreak_ = false;
            }
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
            pattern->touchBreak_ = false;
            if (pattern->animationBreak_) {
                pattern->PlayResetAnimation();
                pattern->yOffset_ = 0.0;
            }
        }
    };
    auto listener = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
    return listener;
}

RefPtr<ClickEvent> TextPickerColumnPattern::CreateItemClickEventListener(RefPtr<EventParam> param)
{
    auto clickEventHandler = [param, weak = WeakClaim(this)](const GestureEvent& /* info */) {
        auto pattern = weak.Upgrade();
        pattern->OnAroundButtonClick(param);
    };

    auto listener = AceType::MakeRefPtr<NG::ClickEvent>(clickEventHandler);
    return listener;
}

RefPtr<InputEvent> TextPickerColumnPattern::CreateMouseHoverEventListener(RefPtr<EventParam> param)
{
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        if (pattern) {
            pattern->HandleMouseEvent(isHover);
        }
    };
    auto hoverEventListener = MakeRefPtr<InputEvent>(std::move(mouseTask));
    return hoverEventListener;
}

void TextPickerColumnPattern::ParseTouchListener()
{
    auto touchCallback = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().empty()) {
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->SetLocalDownDistance(info.GetTouches().front().GetLocalLocation().GetDistance());
            pattern->OnMiddleButtonTouchDown();
            pattern->SetSelectedMark(true);
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP ||
            info.GetTouches().front().GetTouchType() == TouchType::CANCEL) {
            pattern->OnMiddleButtonTouchUp();
            pattern->SetLocalDownDistance(0.0f);
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::MOVE) {
            if (std::abs(info.GetTouches().front().GetLocalLocation().GetDistance() - pattern->GetLocalDownDistance()) >
                MOVE_DISTANCE) {
                pattern->OnMiddleButtonTouchUp();
            }
        }
    };
    touchListener_ = MakeRefPtr<TouchEventImpl>(std::move(touchCallback));
}

void TextPickerColumnPattern::ParseMouseEvent()
{
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(isHover);
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
}

void TextPickerColumnPattern::InitMouseAndPressEvent()
{
    if (mouseEvent_ || touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnEventHub = host->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(columnEventHub);
    RefPtr<TouchEventImpl> touchListener = CreateItemTouchEventListener();
    CHECK_NULL_VOID(touchListener);
    auto columnGesture = columnEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(columnGesture);
    columnGesture->AddTouchEvent(touchListener);
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    RefPtr<FrameNode> middleChild = nullptr;
    auto midSize = childSize / 2;
    middleChild = DynamicCast<FrameNode>(host->GetChildAtIndex(midSize));
    CHECK_NULL_VOID(middleChild);
    auto eventHub = middleChild->GetOrCreateEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    ParseMouseEvent();
    inputHub->AddOnHoverEvent(mouseEvent_);
    auto gesture = middleChild->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    ParseTouchListener();
    gesture->AddTouchEvent(touchListener_);
    int32_t i = 0;
    for (const auto& child : host->GetChildren()) {
        RefPtr<FrameNode> childNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        RefPtr<EventParam> param = MakeRefPtr<EventParam>();
        param->instance = childNode;
        param->itemIndex = i;
        param->itemTotalCounts = childSize;
        auto eventHub = childNode->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_VOID(eventHub);
        if (i != midSize) {
            RefPtr<ClickEvent> clickListener = CreateItemClickEventListener(param);
            CHECK_NULL_VOID(clickListener);
            auto gesture = eventHub->GetOrCreateGestureEventHub();
            CHECK_NULL_VOID(gesture);
            gesture->AddClickEvent(clickListener);
        }
        i++;
    }
}

void TextPickerColumnPattern::HandleMouseEvent(bool isHover)
{
    PlayPressAnimation(isHover ? GetButtonHoverColor() : buttonBgColor_);
    auto needUpdate = isHover_ != isHover;
    isHover_ = isHover;

    if (useButtonFocusArea_ && needUpdate) {
        FlushCurrentOptions();
    }
}

void TextPickerColumnPattern::SetButtonBackgroundColor(const Color& pressColor)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    CHECK_EQUAL_VOID(pickerTheme->IsCircleDial(), true);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blend = host->GetParent();
    CHECK_NULL_VOID(blend);
    auto stack = blend->GetParent();
    CHECK_NULL_VOID(stack);
    auto buttonNode = DynamicCast<FrameNode>(stack->GetFirstChild());
    auto renderContext = buttonNode->GetRenderContext();
    renderContext->UpdateBackgroundColor(pressColor);
    buttonNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void TextPickerColumnPattern::PlayPressAnimation(const Color& pressColor)
{
    AnimationOption option = AnimationOption();
    option.SetDuration(HOVER_ANIMATION_DURATION);
    option.SetFillMode(FillMode::FORWARDS);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), pressColor]() {
        auto picker = weak.Upgrade();
        if (picker) {
            picker->SetButtonBackgroundColor(pressColor);
        }
    });
}

uint32_t TextPickerColumnPattern::GetShowOptionCount() const
{
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, 0);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_RETURN(pickerTheme, 0);
    auto showCount = pickerTheme->GetShowOptionCount() + BUFFER_NODE_NUMBER;
    return showCount;
}

void TextPickerColumnPattern::ResetOptionPropertyHeight()
{
    if (needOptionPropertyHeightReset_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto blendNode = DynamicCast<FrameNode>(host->GetParent());
        CHECK_NULL_VOID(blendNode);
        auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
        CHECK_NULL_VOID(stackNode);
        auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
        CHECK_NULL_VOID(parentNode);
        auto textPickerLayoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
        CHECK_NULL_VOID(textPickerLayoutProperty);
        bool isDefaultPickerItemHeight_ = false;
        if (textPickerLayoutProperty->HasDefaultPickerItemHeight()) {
            auto defaultPickerItemHeightValue = textPickerLayoutProperty->GetDefaultPickerItemHeightValue();
            isDefaultPickerItemHeight_ = LessOrEqual(defaultPickerItemHeightValue.Value(), 0.0) ? false : true;
        }
        if (isDefaultPickerItemHeight_) {
            auto pickerItemHeight = 0.0;
            auto pattern = parentNode->GetPattern<TextPickerPattern>();
            CHECK_NULL_VOID(pattern);
            pickerItemHeight =
                pattern->GetResizeFlag() ? pattern->GetResizePickerItemHeight() : pattern->GetDefaultPickerItemHeight();
            int32_t itemCounts = static_cast<int32_t>(GetShowOptionCount());
            for (int32_t i = 0; i < itemCounts; i++) {
                TextPickerOptionProperty& prop = optionProperties_[i];
                prop.height = pickerItemHeight;
            }
            SetOptionShiftDistance();
        }
        needOptionPropertyHeightReset_ = false;
    }
}

void TextPickerColumnPattern::InitTextFontFamily()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto pipeline = parentNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pattern = parentNode->GetPattern<TextPickerPattern>();
    CHECK_NULL_VOID(pattern);
    auto textPickerLayoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);
    hasUserDefinedDisappearFontFamily_ = pattern->GetHasUserDefinedDisappearFontFamily();
    hasUserDefinedNormalFontFamily_ = pattern->GetHasUserDefinedNormalFontFamily();
    hasUserDefinedSelectedFontFamily_ = pattern->GetHasUserDefinedSelectedFontFamily();
    auto fontManager = pipeline->GetFontManager();
    CHECK_NULL_VOID(fontManager);
    if (!(fontManager->GetAppCustomFont().empty())) {
        hasAppCustomFont_ = true;
    }
    auto appCustomFontFamily = Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont());
    if (hasAppCustomFont_ && !hasUserDefinedDisappearFontFamily_) {
        textPickerLayoutProperty->UpdateDisappearFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedNormalFontFamily_) {
        textPickerLayoutProperty->UpdateFontFamily(appCustomFontFamily);
    }
    if (hasAppCustomFont_ && !hasUserDefinedSelectedFontFamily_) {
        textPickerLayoutProperty->UpdateSelectedFontFamily(appCustomFontFamily);
    }
}

void TextPickerColumnPattern::FlushCurrentOptions(
    bool isDown, bool isUpdateTextContentOnly, bool isDirectlyClear, bool isUpdateAnimationProperties)
{
    ResetOptionPropertyHeight();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto textPickerLayoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);

    InitTextFontFamily();

    if (!isUpdateTextContentOnly) {
        animationProperties_.clear();
    }
    if (columnKind_ == TEXT) {
        FlushCurrentTextOptions(textPickerLayoutProperty, isUpdateTextContentOnly, isDirectlyClear);
    } else if (columnKind_ == ICON) {
        FlushCurrentImageOptions();
    } else if (columnKind_ == MIXTURE) {
        FlushCurrentMixtureOptions(textPickerLayoutProperty, isUpdateTextContentOnly);
    }
    if (isUpdateTextContentOnly && isUpdateAnimationProperties) {
        FlushAnimationTextProperties(isDown);
    }
}

void TextPickerColumnPattern::ClearCurrentTextOptions(const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
    bool isUpdateTextContentOnly, bool isDirectlyClear)
{
    if (isDirectlyClear) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto child = host->GetChildren();
        for (auto iter = child.begin(); iter != child.end(); iter++) {
            auto textNode = DynamicCast<FrameNode>(*iter);
            CHECK_NULL_VOID(textNode);
            auto textPattern = textNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(textPattern);
            auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            textLayoutProperty->UpdateContent(u"");
            textNode->GetRenderContext()->SetClipToFrame(true);
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        selectedIndex_ = 0;
    }
}

void TextPickerColumnPattern::FlushCurrentTextOptions(const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty,
    bool isUpdateTextContentOnly, bool isDirectlyClear)
{
    ClearCurrentTextOptions(textPickerLayoutProperty, isUpdateTextContentOnly, isDirectlyClear);
    uint32_t totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return;
    }
    uint32_t currentIndex = GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t showCount = GetShowOptionCount();
    auto middleIndex = showCount / 2; // the center option is selected.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - middleIndex) % totalOptionCount;
        RangeContent optionValue = options_[optionIndex];
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(middleIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        auto textNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(textNode);
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        UpdateTextOverflow(index == middleIndex, textLayoutProperty);
        if (!isUpdateTextContentOnly) {
            UpdatePickerTextProperties(textLayoutProperty, textPickerLayoutProperty, index, middleIndex, showCount);
        }
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent(u"");
        } else {
            textLayoutProperty->UpdateContent(optionValue.text_);
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        }
        UpdateTextAccessibilityProperty(virtualIndex, iter, virtualIndexValidate);
        textNode->GetRenderContext()->SetClipToFrame(true);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
    selectedIndex_ = currentIndex;
}

void TextPickerColumnPattern::UpdateTextAccessibilityProperty(
    int32_t virtualIndex, std::list<RefPtr<UINode>>::iterator& iter, bool virtualIndexValidate)
{
    auto textNode = DynamicCast<FrameNode>(*(iter));
    CHECK_NULL_VOID(textNode);
    auto accessibilityProperty = textNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    if (!NotLoopOptions() || virtualIndexValidate) {
        accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::AUTO);
        return;
    }
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    auto isFocus = accessibilityProperty->GetAccessibilityFocusState();
    if (virtualIndex == -1 && isFocus) {
        auto nextTextNode = DynamicCast<FrameNode>(*(++iter));
        if (nextTextNode) {
            nextTextNode->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
        }
        --iter;
    } else if (virtualIndex == static_cast<int32_t>(GetOptionCount()) && isFocus) {
        auto preTextNode = DynamicCast<FrameNode>(*(--iter));
        if (preTextNode) {
            preTextNode->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
        }
        ++iter;
    }
}

void TextPickerColumnPattern::FlushCurrentImageOptions()
{
    uint32_t totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return;
    }
    uint32_t currentIndex = GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t showCount = GetShowOptionCount();
    auto middleIndex = showCount / 2; // the center option is selected.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - middleIndex) % totalOptionCount;
        RangeContent optionValue = options_[optionIndex];
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(middleIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        auto rangeNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(rangeNode);
        auto iconNode = DynamicCast<FrameNode>(rangeNode->GetFirstChild());
        CHECK_NULL_VOID(iconNode);
        auto iconPattern = iconNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(iconPattern);
        auto iconLayoutProperty = iconPattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(iconLayoutProperty);
        CalcSize idealSize = { CalcSize(CalcLength(ICON_SIZE), CalcLength(ICON_SIZE)) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        iconLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
        if (NotLoopOptions() && !virtualIndexValidate) {
            iconLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
        } else {
            iconLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            iconLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(optionValue.icon_));
        }
        UpdateTextAccessibilityProperty(virtualIndex, iter, virtualIndexValidate);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        rangeNode->GetRenderContext()->SetClipToFrame(true);
        rangeNode->MarkModifyDone();
        rangeNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
    selectedIndex_ = currentIndex;
}

void TextPickerColumnPattern::FlushCurrentMixtureOptions(
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, bool isUpdateTextContentOnly)
{
    uint32_t totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return;
    }
    uint32_t currentIndex = GetCurrentIndex();
    currentIndex = currentIndex % totalOptionCount;
    uint32_t showCount = GetShowOptionCount();
    auto middleIndex = showCount / 2; // the center option is selected.
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        uint32_t optionIndex = (totalOptionCount + currentIndex + index - middleIndex) % totalOptionCount;
        RangeContent optionValue = options_[optionIndex];
        int32_t diffIndex = static_cast<int32_t>(index) - static_cast<int32_t>(middleIndex);
        int32_t virtualIndex = static_cast<int32_t>(currentIndex) + diffIndex;
        bool virtualIndexValidate = virtualIndex >= 0 && virtualIndex < static_cast<int32_t>(totalOptionCount);
        auto linearLayoutNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(linearLayoutNode);
        auto children = linearLayoutNode->GetChildren();
        if (children.size() != MIXTURE_CHILD_COUNT) {
            continue;
        }
        auto iconNode = DynamicCast<FrameNode>(linearLayoutNode->GetFirstChild());
        auto iconPattern = iconNode->GetPattern<ImagePattern>();
        CHECK_NULL_VOID(iconPattern);
        iconPattern->SetSyncLoad(true);
        auto iconLayoutProperty = iconPattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(iconLayoutProperty);
        auto iconLayoutDirection = iconLayoutProperty->GetNonAutoLayoutDirection();
        CalcSize idealSize = { CalcSize(CalcLength(ICON_SIZE), CalcLength(ICON_SIZE)) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        iconLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
        MarginProperty margin;
        margin.right = CalcLength(ICON_TEXT_SPACE);
        bool isRtl = AceApplicationInfo::GetInstance().IsRightToLeft();
        if (isRtl || iconLayoutDirection == TextDirection::RTL) {
            margin.left = CalcLength(ICON_TEXT_SPACE);
        }
        iconLayoutProperty->UpdateMargin(margin);

        auto textNode = DynamicCast<FrameNode>(linearLayoutNode->GetLastChild());
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        UpdateTextOverflow(index == middleIndex, textLayoutProperty);
        if (!isUpdateTextContentOnly) {
            UpdatePickerTextProperties(textLayoutProperty, textPickerLayoutProperty, index, middleIndex, showCount);
        }
        if (NotLoopOptions() && !virtualIndexValidate) {
            iconLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
            textLayoutProperty->UpdateContent(u"");
        } else {
            textLayoutProperty->UpdateContent(optionValue.text_);
            iconLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            iconLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(optionValue.icon_));
        }
        UpdateTextAccessibilityProperty(virtualIndex, iter, virtualIndexValidate);
        iconNode->MarkModifyDone();
        iconNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);

        linearLayoutNode->GetRenderContext()->SetClipToFrame(true);
        linearLayoutNode->MarkModifyDone();
        linearLayoutNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
    selectedIndex_ = currentIndex;
}

void TextPickerColumnPattern::FlushAnimationTextProperties(bool isDown)
{
    const size_t size = animationProperties_.size();
    if (size == 0) {
        return;
    }
    if (isDown) {
        for (size_t i = 0; i < size; i++) {
            if (i > 0) {
                animationProperties_[i - 1].upFontSize = animationProperties_[i].upFontSize;
                animationProperties_[i - 1].fontSize = animationProperties_[i].fontSize;
                animationProperties_[i - 1].downFontSize = animationProperties_[i].downFontSize;
                animationProperties_[i - 1].upColor = animationProperties_[i].upColor;
                animationProperties_[i - 1].currentColor = animationProperties_[i].currentColor;
                animationProperties_[i - 1].downColor = animationProperties_[i].downColor;
            }
            if (i + 1 == size) {
                animationProperties_[i].upFontSize = animationProperties_[i].fontSize;
                animationProperties_[i].fontSize = animationProperties_[i].fontSize * 0.5;
                animationProperties_[i].downFontSize = Dimension();
                animationProperties_[i].upColor = animationProperties_[i].currentColor;
                auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
                animationProperties_[i].currentColor =
                    colorEvaluator->Evaluate(Color(), animationProperties_[i].currentColor, 0.5);
                animationProperties_[i].downColor = Color();
            }
        }
    } else {
        for (size_t i = size - 1;; i--) {
            if (i == 0) {
                animationProperties_[i].upFontSize = Dimension();
                animationProperties_[i].downFontSize = animationProperties_[i].fontSize;
                animationProperties_[i].fontSize = animationProperties_[i].fontSize * 0.5;
                animationProperties_[i].upColor = Color();
                animationProperties_[i].downColor = animationProperties_[i].currentColor;
                auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
                animationProperties_[i].currentColor =
                    colorEvaluator->Evaluate(Color(), animationProperties_[i].currentColor, 0.5);
                break;
            } else {
                animationProperties_[i].upFontSize = animationProperties_[i - 1].upFontSize;
                animationProperties_[i].fontSize = animationProperties_[i - 1].fontSize;
                animationProperties_[i].downFontSize = animationProperties_[i - 1].downFontSize;
                animationProperties_[i].upColor = animationProperties_[i - 1].upColor;
                animationProperties_[i].currentColor = animationProperties_[i - 1].currentColor;
                animationProperties_[i].downColor = animationProperties_[i - 1].downColor;
            }
        }
    }
}

void TextPickerColumnPattern::UpdateDisappearTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(textPickerLayoutProperty->GetDisappearColor().value_or(
        pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (textPickerLayoutProperty->HasDisappearFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetDisappearFontSize().value());
        textLayoutProperty->UpdateAdaptMaxFontSize(Dimension());
        textLayoutProperty->UpdateAdaptMinFontSize(Dimension());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(normalOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(false, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(textPickerLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    auto fontFamilyVector = textPickerLayoutProperty->GetDisappearFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies());
    textLayoutProperty->UpdateFontFamily(fontFamilyVector.empty() ? FONT_FAMILY_DEFAULT : fontFamilyVector);
    textLayoutProperty->UpdateItalicFontStyle(textPickerLayoutProperty->GetDisappearFontStyle().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TextPickerColumnPattern::UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    textLayoutProperty->UpdateTextColor(
        textPickerLayoutProperty->GetColor().value_or(pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (textPickerLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetFontSize().value());
        textLayoutProperty->UpdateAdaptMaxFontSize(Dimension());
        textLayoutProperty->UpdateAdaptMinFontSize(Dimension());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(focusOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize() - FOCUS_SIZE);
    }
    textLayoutProperty->UpdateFontWeight(
        textPickerLayoutProperty->GetWeight().value_or(pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    auto fontFamilyVector = textPickerLayoutProperty->GetFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies());
    textLayoutProperty->UpdateFontFamily(fontFamilyVector.empty() ? FONT_FAMILY_DEFAULT : fontFamilyVector);
    textLayoutProperty->UpdateItalicFontStyle(
        textPickerLayoutProperty->GetFontStyle().value_or(pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TextPickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty)
{
    UpdateTextAreaPadding(pickerTheme, textLayoutProperty);
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();

    if (pickerTheme->IsCircleDial() && !isUserSetSelectColor_) {
        if (selectedMarkPaint_) {
            textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(true, true).GetTextColor());
        } else {
            textLayoutProperty->UpdateTextColor(pickerTheme->GetOptionStyle(false, false).GetTextColor());
        }
    } else {
        textLayoutProperty->UpdateTextColor(textPickerLayoutProperty->GetSelectedColor().value_or(
            pickerTheme->GetOptionStyle(true, false).GetTextColor()));
    }

    if (textPickerLayoutProperty->HasSelectedFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetSelectedFontSize().value());
        textLayoutProperty->UpdateAdaptMaxFontSize(Dimension());
        textLayoutProperty->UpdateAdaptMinFontSize(Dimension());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(selectedOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(textPickerLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight()));
    auto fontFamilyVector = textPickerLayoutProperty->GetSelectedFontFamily().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontFamilies());
    textLayoutProperty->UpdateFontFamily(fontFamilyVector.empty() ? FONT_FAMILY_DEFAULT : fontFamilyVector);
    textLayoutProperty->UpdateItalicFontStyle(textPickerLayoutProperty->GetSelectedFontStyle().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontStyle()));
}

void TextPickerColumnPattern::UpdateDefaultTextProperties(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, uint32_t currentIndex, uint32_t middleIndex)
{
    CHECK_NULL_VOID(textLayoutProperty);
    CHECK_NULL_VOID(textPickerLayoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto theme = context->GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    auto textStyle = theme->GetTextStyle();
    textLayoutProperty->UpdateFontSize(
        textPickerLayoutProperty->GetDefaultFontSize().value_or(textStyle.GetFontSize()));
    textLayoutProperty->UpdateFontWeight(
        textPickerLayoutProperty->GetDefaultWeight().value_or(textStyle.GetFontWeight()));
    textLayoutProperty->UpdateTextColor(textPickerLayoutProperty->GetDefaultColor().value_or(textStyle.GetTextColor()));
    textLayoutProperty->UpdateFontFamily(
        textPickerLayoutProperty->GetDefaultFontFamily().value_or(textStyle.GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(
        textPickerLayoutProperty->GetDefaultFontStyle().value_or(textStyle.GetFontStyle()));
    textLayoutProperty->UpdateAdaptMinFontSize(textPickerLayoutProperty->GetDefaultMinFontSize().value_or(Dimension()));
    textLayoutProperty->UpdateAdaptMaxFontSize(textPickerLayoutProperty->GetDefaultMaxFontSize().value_or(Dimension()));
    if (textPickerLayoutProperty->GetDefaultTextOverflow().has_value() &&
        textPickerLayoutProperty->GetDefaultTextOverflow().value() != TextOverflow::MARQUEE) {
        textLayoutProperty->UpdateTextOverflow(textPickerLayoutProperty->GetDefaultTextOverflow().value());
    } else {
        textLayoutProperty->UpdateTextOverflow(textStyle.GetTextOverflow());
    }
    textLayoutProperty->UpdateHeightAdaptivePolicy(TextHeightAdaptivePolicy::MIN_FONT_SIZE_FIRST);
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateAlignment(Alignment::CENTER);

    CHECK_EQUAL_VOID(optionProperties_.empty(), true);
    InitTextHeightAndFontHeight(currentIndex, middleIndex, optionProperties_[currentIndex]);

    bool isLandscape = static_cast<int32_t>(GetShowOptionCount()) == OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER;
    SetOptionShiftDistanceByIndex(currentIndex, isLandscape);
}

void TextPickerColumnPattern::AddAnimationTextProperties(
    uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    TextProperties properties{};
    if (textLayoutProperty->HasFontSize()) {
        MeasureContext measureContext;
        measureContext.textContent = MEASURE_STRING;
        measureContext.fontSize = textLayoutProperty->GetFontSize().value();
        if (textLayoutProperty->HasFontFamily()) {
            auto fontFamilyVector = textLayoutProperty->GetFontFamily().value();
            if (fontFamilyVector.empty()) {
                measureContext.fontFamily = FONT_FAMILY_DEFAULT[0];
            } else {
                measureContext.fontFamily = fontFamilyVector[0];
            }
        } else {
            measureContext.fontFamily = FONT_FAMILY_DEFAULT[0];
        }
        auto size = MeasureUtil::MeasureTextSize(measureContext);
        if (!optionProperties_.empty()) {
            optionProperties_[currentIndex].fontheight = size.Height();
            if (optionProperties_[currentIndex].fontheight > optionProperties_[currentIndex].height) {
                optionProperties_[currentIndex].fontheight = optionProperties_[currentIndex].height;
            }
        }
        bool isLandscape = static_cast<int32_t>(GetShowOptionCount()) ==
                           (OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER);
        SetOptionShiftDistanceByIndex(currentIndex, isLandscape);
        properties.fontSize = Dimension(textLayoutProperty->GetFontSize().value().ConvertToPx());
    }
    if (textLayoutProperty->HasTextColor()) {
        properties.currentColor = textLayoutProperty->GetTextColor().value();
    }
    if (textLayoutProperty->HasFontWeight()) {
        properties.fontWeight = textLayoutProperty->GetFontWeight().value();
    }
    if (currentIndex > 0) {
        properties.upFontSize = animationProperties_[currentIndex - 1].fontSize;
        animationProperties_[currentIndex - 1].downFontSize = properties.fontSize;

        properties.upColor = animationProperties_[currentIndex - 1].currentColor;
        animationProperties_[currentIndex - 1].downColor = properties.currentColor;

        properties.upFontWeight = animationProperties_[currentIndex - 1].fontWeight;
        animationProperties_[currentIndex - 1].downFontWeight = properties.fontWeight;
    }
    animationProperties_.emplace_back(properties);
}

void TextPickerColumnPattern::UpdatePickerTextProperties(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, uint32_t currentIndex, uint32_t middleIndex,
    uint32_t showCount)
{
    if (textPickerLayoutProperty && textPickerLayoutProperty->GetDisableTextStyleAnimation().value_or(false)) {
        UpdateDefaultTextProperties(textLayoutProperty, textPickerLayoutProperty, currentIndex, middleIndex);
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(pickerTheme);
    if (currentIndex == middleIndex) {
        UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, textPickerLayoutProperty);
        textLayoutProperty->UpdateAlignment(Alignment::CENTER);
    } else if ((currentIndex == middleIndex + 1) || (currentIndex == middleIndex - 1)) {
        UpdateCandidateTextProperties(pickerTheme, textLayoutProperty, textPickerLayoutProperty);
    } else {
        UpdateDisappearTextProperties(pickerTheme, textLayoutProperty, textPickerLayoutProperty);
    }
    if (currentIndex < middleIndex) {
        textLayoutProperty->UpdateAlignment(Alignment::TOP_CENTER);
    } else if (currentIndex > middleIndex) {
        textLayoutProperty->UpdateAlignment(Alignment::BOTTOM_CENTER);
    }
    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextOverflow(isTextFadeOut_ ? TextOverflow::MARQUEE : TextOverflow::CLIP);
    AddAnimationTextProperties(currentIndex, textLayoutProperty);
}

void TextPickerColumnPattern::SetSelectColor(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const Color& startColor, const Color& endColor, const float& percent, bool isEqual)
{
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    Color updateColor = colorEvaluator->Evaluate(startColor, endColor, percent);
    textLayoutProperty->UpdateTextColor(updateColor);
}

void TextPickerColumnPattern::TextPropertiesLinearAnimation(const RefPtr<TextLayoutProperty>& textLayoutProperty,
    uint32_t idx, uint32_t showCount, bool isDown, double scaleSize)
{
    uint32_t deltaIdx = static_cast<uint32_t>(GetOverScrollDeltaIndex());
    auto index = idx;
    bool isEqual = false;
    if (GreatNotEqual(scrollDelta_, 0.0f)) {
        index = index + deltaIdx;
    } else {
        if (index < deltaIdx) {
            return;
        }
        index = index - deltaIdx;
    }
    auto percent = distancePercent_ - deltaIdx;
    auto scale = scaleSize - deltaIdx;

    if (index >= animationProperties_.size()) {
        return;
    }
    Dimension startFontSize = animationProperties_[index].fontSize;
    Color startColor = animationProperties_[index].currentColor;
    if ((!index && isDown) || ((index == (showCount - 1)) && !isDown)) {
        textLayoutProperty->UpdateFontSize(startFontSize);
        textLayoutProperty->UpdateTextColor(startColor);
        return;
    }
    Dimension endFontSize;
    Color endColor;
    if (GreatNotEqual(scrollDelta_, 0.0)) {
        endFontSize = animationProperties_[index].downFontSize;
        endColor = animationProperties_[index].downColor;
        if (GreatOrEqual(scale, FONTWEIGHT)) {
            textLayoutProperty->UpdateFontWeight(animationProperties_[index].downFontWeight);
        }
    } else {
        endFontSize = animationProperties_[index].upFontSize;
        endColor = animationProperties_[index].upColor;
        if (GreatOrEqual(scale, FONTWEIGHT)) {
            textLayoutProperty->UpdateFontWeight(animationProperties_[index].upFontWeight);
        }
    }
    Dimension updateSize = LinearFontSize(startFontSize, endFontSize, percent);
    textLayoutProperty->UpdateFontSize(updateSize);
    isEqual = (idx == (showCount / PICKER_SELECT_AVERAGE));
    SetSelectColor(textLayoutProperty, startColor, endColor, percent, isEqual);
    if (scale < FONTWEIGHT) {
        textLayoutProperty->UpdateFontWeight(animationProperties_[index].fontWeight);
    }
}

int32_t TextPickerColumnPattern::GetOverScrollDeltaIndex() const
{
    auto deltaIdx = 0;
    if (NotLoopOptions() && overscroller_.IsOverScroll()) {
        auto midIndex = GetShowOptionCount() / HALF_NUMBER;
        auto shiftDistance = optionProperties_[midIndex].nextDistance;
        for (auto idx = midIndex; idx < GetShowOptionCount(); idx++) {
            if (shiftDistance > std::abs(scrollDelta_)) {
                break;
            }
            shiftDistance += optionProperties_[idx].nextDistance;
            deltaIdx++;
        }
    }
    return deltaIdx;
}

void TextPickerColumnPattern::UpdateTextPropertiesLinear(bool isDown, double scale)
{
    if (columnKind_ == ICON) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    uint32_t showCount = GetShowOptionCount();
    auto middleIndex = showCount / 2;
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        auto rangeNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(rangeNode);
        RefPtr<TextLayoutProperty> textLayoutProperty;
        if (columnKind_ == TEXT) {
            auto textPattern = rangeNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(textPattern);
            textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            UpdateTextOverflow(index == middleIndex, textLayoutProperty);
            TextPropertiesLinearAnimation(textLayoutProperty, index, showCount, isDown, scale);
        } else if (columnKind_ == MIXTURE) {
            auto children = rangeNode->GetChildren();
            if (children.size() != MIXTURE_CHILD_COUNT) {
                continue;
            }
            auto textNode = DynamicCast<FrameNode>(rangeNode->GetLastChild());
            auto textPattern = textNode->GetPattern<TextPattern>();
            textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            UpdateTextOverflow(index == middleIndex, textLayoutProperty);
            TextPropertiesLinearAnimation(textLayoutProperty, index, showCount, isDown, scale);
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        rangeNode->MarkModifyDone();
        rangeNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
}

Dimension TextPickerColumnPattern::LinearFontSize(
    const Dimension& startFontSize, const Dimension& endFontSize, double percent)
{
    if (percent > FONT_SIZE_PERCENT) {
        return startFontSize + (endFontSize - startFontSize);
    } else {
        return startFontSize + (endFontSize - startFontSize) * std::abs(percent);
    }
}

void TextPickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!panEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (event.GetInputEventType() == InputEventType::AXIS && event.GetSourceTool() == SourceTool::MOUSE) {
            return;
        }
        pattern->HandleDragStart(event);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->SetMainVelocity(event.GetMainVelocity());
        pattern->HandleDragMove(event);
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetInputEventType() == InputEventType::AXIS && info.GetSourceTool() == SourceTool::MOUSE) {
            return;
        }
        pattern->SetMainVelocity(info.GetMainVelocity());
        pattern->HandleDragEnd();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleDragEnd();
    };
    PanDirection panDirection;
    panDirection.type = PanDirection::VERTICAL;
    panEvent_ = MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, DEFAULT_PAN_DISTANCE.ConvertToPx() },
        { SourceTool::PEN, DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, distanceMap);
}

RefPtr<TextPickerLayoutProperty> TextPickerColumnPattern::GetParentLayout() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(blendNode, nullptr);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, nullptr);

    auto property = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    return property;
}

void TextPickerColumnPattern::HandleDragStart(const GestureEvent& event)
{
    SetSelectedMark();
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY = event.GetGlobalPoint().GetY();
    toss->SetStart(offsetY);
    yLast_ = offsetY;
    overscroller_.SetStart(offsetY);
    pressed_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.GetMainVelocity(), SceneStatus::START);
    // AccessibilityEventType::SCROLL_START

    if (animation_) {
        AnimationUtils::StopAnimation(animation_);
    }

    if (NotLoopOptions() && reboundAnimation_) {
        AnimationUtils::StopAnimation(reboundAnimation_);
        isReboundInProgress_ = false;
        overscroller_.ResetVelocity();
        overscroller_.SetOverScroll(scrollDelta_);
    }
}

void TextPickerColumnPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetFingerList().size() > 1) {
        return;
    }
    if (event.GetInputEventType() == InputEventType::AXIS && event.GetSourceTool() == SourceTool::MOUSE) {
        if (InnerHandleScroll(LessNotEqual(event.GetDelta().GetY(), 0.0), true)) {
            HandleScrollStopEventCallback(true);
        }
        return;
    }
    animationBreak_ = false;
    CHECK_NULL_VOID(pressed_);
    CHECK_NULL_VOID(GetHost());
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY =
        event.GetGlobalPoint().GetY() + (event.GetInputEventType() == InputEventType::AXIS ? event.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, MOVE_THRESHOLD)) { // if changing less than MOVE_THRESHOLD, no need to handle
        StopHapticController();
        return;
    }
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.GetMainVelocity(), SceneStatus::RUNNING);
}

void TextPickerColumnPattern::HandleDragEnd()
{
    if (hapticController_) {
        hapticController_->Stop();
        isHapticPlayOnce_ = false;
    }
    pressed_ = false;
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (NotLoopOptions()) {
        frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
        if (overscroller_.IsOverScroll()) { // Start rebound animation. Higher priority than fling
            CreateReboundAnimation(overscroller_.GetOverScroll(), 0.0);
            HandleScrollStopEventCallback(true);
            return;
        }
    }
    if (toss->Play()) { // Start fling animation
        frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
        // AccessibilityEventType::SCROLL_END
        return;
    }
    yOffset_ = 0.0;
    yLast_ = 0.0;
    if (!animationCreated_) {
        ScrollOption(0.0);
        return;
    }
    int32_t middleIndex = static_cast<int32_t>(GetShowOptionCount()) / HALF_NUMBER;
    ScrollDirection dir = GreatNotEqual(scrollDelta_, 0.0) ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                      : optionProperties_[middleIndex].nextDistance;
    auto shiftThreshold = shiftDistance / HALF_NUMBER;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == ScrollDirection::UP ? -1 : 1);
        if (NearZero(scrollDelta_)) {
            HandleScrollStopEventCallback(true);
        }
    }
    CreateAnimation(scrollDelta_, 0.0);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
    if (!NearZero(scrollDelta_)) {
        HandleScrollStopEventCallback(true);
    }
    // AccessibilityEventType::SCROLL_END
}

void TextPickerColumnPattern::CreateAnimation()
{
    CHECK_NULL_VOID(!animationCreated_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto propertyCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->ScrollOption(value);
    };
    scrollProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(propertyCallback));
    renderContext->AttachNodeAnimatableProperty(scrollProperty_);

    auto aroundClickCallback = [weak = AceType::WeakClaim(this)](float value) {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->UpdateColumnChildPosition(value);
    };
    aroundClickProperty_ = AceType::MakeRefPtr<NodeAnimatablePropertyFloat>(0.0, std::move(aroundClickCallback));
    renderContext->AttachNodeAnimatableProperty(aroundClickProperty_);
    animationCreated_ = true;
}

void TextPickerColumnPattern::CreateAnimation(double from, double to)
{
    AnimationOption option;
    option.SetCurve(Curves::FAST_OUT_SLOW_IN);
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    AnimationUtils::Animate(option, [weak = AceType::WeakClaim(this), to]() {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->scrollProperty_->Set(to);
    });
}

void TextPickerColumnPattern::CreateReboundAnimation(double from, double to)
{
    isReboundInProgress_ = true;
    AnimationOption option;
    option.SetCurve(overscroller_.GetReboundCurve());
    option.SetDuration(CLICK_ANIMATION_DURATION);
    scrollProperty_->Set(from);
    reboundAnimation_ = AnimationUtils::StartAnimation(option, [weak = AceType::WeakClaim(this), to]() {
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        column->scrollProperty_->Set(to);
    }, [weak = AceType::WeakClaim(this)]() { // On Finish
        auto column = weak.Upgrade();
        CHECK_NULL_VOID(column);
        if (column->isReboundInProgress_) {
            column->isReboundInProgress_ = false;
            column->overscroller_.Reset();
            column->yLast_ = 0.0;
            column->yOffset_ = 0.0;
        }
    });
}

void TextPickerColumnPattern::HandleEnterSelectedArea(double scrollDelta, float shiftDistance, ScrollDirection dir)
{
    auto shiftThreshold = shiftDistance / HALF_NUMBER;
    uint32_t totalOptionCount = GetOptionCount();
    uint32_t currentEnterIndex = GetCurrentIndex();
    auto isOverScroll = NotLoopOptions() && overscroller_.IsOverScroll();
    if (totalOptionCount == 0) {
        return;
    }
    if (dir == ScrollDirection::UP) {
        currentEnterIndex = (totalOptionCount + currentEnterIndex + 1) % totalOptionCount;
    } else {
        auto totalCountAndIndex = totalOptionCount + currentEnterIndex;
        currentEnterIndex = (totalCountAndIndex ? totalCountAndIndex - 1 : 0) % totalOptionCount;
    }
    bool isDragReverse = false;
    if (GreatNotEqual(std::abs(enterDelta_), std::abs(scrollDelta))) {
        isDragReverse = true;
    }
    enterDelta_ = (NearEqual(scrollDelta, shiftDistance)) ? 0.0 : scrollDelta;
    if (GreatOrEqual(std::abs(scrollDelta), std::abs(shiftThreshold)) && GetEnterIndex() != currentEnterIndex &&
        !isOverScroll) {
        SetEnterIndex(currentEnterIndex);
        HandleEnterSelectedAreaEventCallback(true);
    }
    if (isDragReverse && LessOrEqual(std::abs(scrollDelta), std::abs(shiftThreshold)) &&
        GetEnterIndex() != GetCurrentIndex() && !isOverScroll) {
        SetEnterIndex(GetCurrentIndex());
        HandleEnterSelectedAreaEventCallback(true);
    }
}

void TextPickerColumnPattern::ScrollOption(double delta)
{
    scrollDelta_ = delta;
    auto midIndex = GetShowOptionCount() / HALF_NUMBER;
    ScrollDirection dir = GreatNotEqual(delta, 0.0) ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                      : optionProperties_[midIndex].nextDistance;
    HandleEnterSelectedArea(scrollDelta_, shiftDistance, dir);
    distancePercent_ = delta / shiftDistance;
    auto textLinearPercent = 0.0;
    textLinearPercent = (std::abs(delta)) / (optionProperties_[midIndex].height);
    UpdateTextPropertiesLinear(LessNotEqual(delta, 0.0), textLinearPercent);
    CalcAlgorithmOffset(dir, distancePercent_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void TextPickerColumnPattern::ResetAlgorithmOffset()
{
    algorithmOffset_.clear();

    uint32_t counts = GetShowOptionCount();
    for (uint32_t i = 0; i < counts; i++) {
        algorithmOffset_.emplace_back(0.0);
    }
}

void TextPickerColumnPattern::UpdateScrollDelta(double delta)
{
    SetCurrentOffset(delta);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
}

void TextPickerColumnPattern::CalcAlgorithmOffset(ScrollDirection dir, double distancePercent)
{
    algorithmOffset_.clear();

    uint32_t counts = GetShowOptionCount();

    for (uint32_t i = 0; i < counts; i++) {
        auto distance = (dir == ScrollDirection::UP) ? optionProperties_[i].prevDistance
                                                     : optionProperties_[i].nextDistance;
        auto val  = std::trunc(distance * distancePercent);
        algorithmOffset_.emplace_back(static_cast<int32_t>(val));
    }
}

double TextPickerColumnPattern::GetShiftDistance(int32_t index, ScrollDirection dir)
{
    if (optionProperties_.empty()) {
        return 0.0;
    }
    int32_t optionCounts = static_cast<int32_t>(GetShowOptionCount());
    if (optionCounts == 0) {
        return 0.0;
    }
    int32_t nextIndex = 0;
    auto isDown = dir == ScrollDirection::DOWN;
    nextIndex = isDown ? (optionCounts + index + 1) % optionCounts : (optionCounts + index - 1) % optionCounts;
    double distance = 0.0;
    switch (static_cast<OptionIndex>(index)) {
        case OptionIndex::COLUMN_INDEX_0: // first
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[index].height);
            break;
        case OptionIndex::COLUMN_INDEX_1:
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[nextIndex].height);
            break;
        case OptionIndex::COLUMN_INDEX_2:
            distance = GetUpCandidateDistance(index, nextIndex, dir);
            break;

        case OptionIndex::COLUMN_INDEX_3:
            distance = GetSelectedDistance(index, nextIndex, dir);
            break;

        case OptionIndex::COLUMN_INDEX_4:
            distance = GetDownCandidateDistance(index, nextIndex, dir);
            break;
        case OptionIndex::COLUMN_INDEX_5:
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[nextIndex].height);
            break;
        case OptionIndex::COLUMN_INDEX_6: // last
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[nextIndex].height);
            break;
        default:
            break;
    }

    return distance;
}

bool TextPickerColumnPattern::IsDisableTextStyleAnimation() const
{
    RefPtr<TextPickerLayoutProperty> layout = GetParentLayout();
    CHECK_NULL_RETURN(layout, false);
    return layout->GetDisableTextStyleAnimation().value_or(false);
}

double TextPickerColumnPattern::GetSelectedDistance(int32_t index, int32_t nextIndex, ScrollDirection dir)
{
    double distance = 0.0;
    double val = 0.0;
    if (columnKind_ == TEXT && !IsDisableTextStyleAnimation()) {
        if (GreatOrEqual(optionProperties_[nextIndex].fontheight, optionProperties_[nextIndex].height)) {
            distance = (dir == ScrollDirection::UP) ?
                - optionProperties_[nextIndex].height : optionProperties_[index].height;
        } else {
            val = optionProperties_[index].height / HALF_NUMBER + optionProperties_[nextIndex].height -
                  optionProperties_[nextIndex].fontheight / HALF_NUMBER;
            val = std::round(val);
            distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
        }
    } else {
        val = std::round((optionProperties_[index].height + optionProperties_[nextIndex].height) / HALF_NUMBER);
        distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
    }
    return distance;
}

double TextPickerColumnPattern::GetUpCandidateDistance(int32_t index, int32_t nextIndex, ScrollDirection dir)
{
    double distance = 0.0;
    double val = 0.0;
    // the index of last element in optionProperties_. return -1 while the arraySize equals 0.
    auto maxIndex = static_cast<int32_t>(optionProperties_.size()) - 1;
    auto minIndex = 0;
    if (index > maxIndex || index < minIndex || nextIndex > maxIndex || nextIndex < minIndex) {
        return distance;
    }
    if (columnKind_ == TEXT && !IsDisableTextStyleAnimation()) {
        if (dir == ScrollDirection::UP) {
            distance = -optionProperties_[nextIndex].height;
        } else {
            val = optionProperties_[index].height +
                  (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
            distance = std::round(val);
        }
    } else {
        val = std::round((optionProperties_[index].height + optionProperties_[nextIndex].height) / HALF_NUMBER);
        distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
    }
    return distance;
}

double TextPickerColumnPattern::GetDownCandidateDistance(int32_t index, int32_t nextIndex, ScrollDirection dir)
{
    double distance = 0.0;
    double val = 0.0;
    if (columnKind_ == TEXT && !IsDisableTextStyleAnimation()) {
        if (dir == ScrollDirection::DOWN) {
            distance = optionProperties_[index].height;
        } else {
            val = optionProperties_[index].height +
                  (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
            if (GreatNotEqual(optionProperties_[nextIndex].fontheight, optionProperties_[index].height)) {
                val = val + (optionProperties_[nextIndex].fontheight - optionProperties_[index].height);
            }
            distance = - std::round(val);
        }
    } else {
        val = std::round((optionProperties_[index].height + optionProperties_[nextIndex].height) / HALF_NUMBER);
        distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
    }
    return distance;
}

double TextPickerColumnPattern::GetShiftDistanceForLandscape(int32_t index, ScrollDirection dir)
{
    int32_t optionCounts = static_cast<int32_t>(GetShowOptionCount());
    if (optionCounts == 0) {
        return 0.0;
    }
    int32_t nextIndex = 0;
    auto isDown = dir == ScrollDirection::DOWN;
    nextIndex = isDown ? (optionCounts + index + 1) % optionCounts : (optionCounts + index - 1) % optionCounts;
    double distance = 0.0;
    switch (static_cast<OptionIndex>(index)) {
        case OptionIndex::COLUMN_INDEX_0:
            distance = GetUpCandidateDistance(index, nextIndex, dir);
            break;

        case OptionIndex::COLUMN_INDEX_1:
            distance = GetSelectedDistance(index, nextIndex, dir);
            break;

        case OptionIndex::COLUMN_INDEX_2:
            distance = GetDownCandidateDistance(index, nextIndex, dir);
            break;
        default:
            break;
    }

    return distance;
}

void TextPickerColumnPattern::SetOptionShiftDistanceByIndex(int32_t index, const bool isLandscape)
{
    CHECK_EQUAL_VOID(optionProperties_.empty(), true);
    TextPickerOptionProperty& prop = optionProperties_[index];
    if (isLandscape) {
        prop.prevDistance = GetShiftDistanceForLandscape(index, ScrollDirection::UP);
        prop.nextDistance = GetShiftDistanceForLandscape(index, ScrollDirection::DOWN);
    } else {
        prop.prevDistance = GetShiftDistance(index, ScrollDirection::UP);
        prop.nextDistance = GetShiftDistance(index, ScrollDirection::DOWN);
    }
}

void TextPickerColumnPattern::SetOptionShiftDistance()
{
    int32_t itemCounts = static_cast<int32_t>(GetShowOptionCount());
    bool isLandscape = itemCounts == OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER;
    for (int32_t i = 0; i < itemCounts; i++) {
        SetOptionShiftDistanceByIndex(i, isLandscape);
    }
}

void TextPickerColumnPattern::UpdateToss(double offsetY)
{
    UpdateColumnChildPosition(offsetY);
}

void TextPickerColumnPattern::TossStoped()
{
    yOffset_ = 0.0;
    yLast_ = 0.0;
    ScrollOption(0.0);
}

void TextPickerColumnPattern::TossAnimationStoped()
{
    if (hapticController_) {
        hapticController_->Stop();
    }
    yLast_ = 0.0;
    ScrollOption(0.0);
}

std::string TextPickerColumnPattern::GetSelectedObject(bool isColumnChange, int32_t status) const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, "");
    auto value = GetOption(GetSelected());
    auto index = GetSelected();
    if (isColumnChange) {
        value = GetCurrentText();
        index = GetCurrentIndex();
    }

    auto context = host->GetContext();
    CHECK_NULL_RETURN(context, "");

    if (context->GetIsDeclarative()) {
        return std::string("{\"value\":") + "\"" + value + "\"" + ",\"index\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    } else {
        return std::string("{\"newValue\":") + "\"" + value + "\"" + ",\"newSelected\":" + std::to_string(index) +
               ",\"status\":" + std::to_string(status) + "}";
    }
}

void TextPickerColumnPattern::ResetTotalDelta()
{
    totalDragDelta_ = 0.0;
}

bool TextPickerColumnPattern::SpringCurveTailMoveProcess(bool useRebound, double& dragDelta)
{
    if (useRebound) {
        return false;
    }
    auto toss = GetToss();
    if (toss && toss->GetTossPlaying()) {
        if (std::abs(dragDelta) < CURVE_MOVE_THRESHOLD) {
            dragDelta = dragDelta > 0 ? CURVE_MOVE_THRESHOLD : -CURVE_MOVE_THRESHOLD;
        }
        totalDragDelta_ += dragDelta;
        if (std::abs(totalDragDelta_) >= std::abs(toss->GetTossEndPosition())) {
            dragDelta -= (totalDragDelta_ - toss->GetTossEndPosition());
            ResetTotalDelta();
            return true;
        }
    }
    return false;
}

void TextPickerColumnPattern::SpringCurveTailEndProcess(bool useRebound, bool stopMove)
{
    if (useRebound || !stopMove) {
        return;
    }
    auto toss = GetToss();
    if (toss) {
        toss->SetTossPlaying(false);
        toss->StopTossAnimation();
    }
}

void TextPickerColumnPattern::UpdateColumnChildPosition(double offsetY)
{
    double dragDelta = offsetY - yLast_;
    auto midIndex = GetShowOptionCount() / HALF_NUMBER;
    ScrollDirection dir = GreatNotEqual(dragDelta, 0.0) ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                      : optionProperties_[midIndex].nextDistance;
    auto useRebound = NotLoopOptions();
    auto stopMove = SpringCurveTailMoveProcess(useRebound, dragDelta);
    offsetCurSet_ = 0.0;

    if (hapticController_ && isShow_) {
        if (isEnableHaptic_ && !isHapticPlayOnce_) {
            hapticController_->HandleDelta(dragDelta);
        }
    }
    // the abs of drag delta is less than jump interval.
    dragDelta = GetDragDeltaLessThanJumpInterval(offsetY, dragDelta, useRebound, shiftDistance);

    // Set options position
    ScrollOption(dragDelta);
    offsetCurSet_ = dragDelta;
    yOffset_ = dragDelta;
    yLast_ = offsetY;

    if (useRebound && !pressed_ && isTossStatus_ && !isReboundInProgress_ && overscroller_.IsOverScroll()) {
        overscroller_.UpdateTossSpring(offsetY);
        if (overscroller_.ShouldStartRebound()) {
            auto toss = GetToss();
            CHECK_NULL_VOID(toss);
            toss->StopTossAnimation(); // Stop fling animation and start rebound animation implicitly
            StopHapticController();
        }
    }
    SpringCurveTailEndProcess(useRebound, stopMove);
}

double TextPickerColumnPattern::GetDragDeltaLessThanJumpInterval(
    double offsetY, float originalDragDelta, bool useRebound, float shiftDistance)
{
    double dragDelta = originalDragDelta + yOffset_;
    auto isOverScroll = useRebound && overscroller_.IsOverScroll();
    if (NearEqual(std::abs(dragDelta), std::abs(shiftDistance)) && !NearZero(dragDelta)) {
        dragDelta = std::abs(dragDelta) / dragDelta * std::abs(shiftDistance);
    }
    if ((std::abs(dragDelta) >= std::abs(shiftDistance)) && !isOverScroll) {
        int32_t shiftDistanceCount = static_cast<int>(std::abs(dragDelta) / std::abs(shiftDistance));
        double additionalShift = dragDelta - shiftDistanceCount * shiftDistance;
        if (GreatNotEqual(std::abs(additionalShift), std::abs(dragDelta))) {
            additionalShift = dragDelta + shiftDistanceCount * shiftDistance;
        }
        for (int32_t i = 0; i < shiftDistanceCount; i++) {
            ScrollOption(shiftDistance);
            InnerHandleScroll(dragDelta < 0, true, false);
        }
        dragDelta = additionalShift;
        if (NearZero(dragDelta)) {
            HandleScrollStopEventCallback(true);
        }
    }
    if (useRebound && !isReboundInProgress_) {
        if (overscroller_.ApplyCurrentOffset(yLast_, offsetY, dragDelta)) {
            dragDelta =
                overscroller_.IsBackOverScroll() ? overscroller_.GetBackScroll() : overscroller_.GetOverScroll();
        }
    }
    return dragDelta;
}

bool TextPickerColumnPattern::CanMove(bool isDown) const
{
    if (!NotLoopOptions()) {
        return true;
    }
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    int totalOptionCount = static_cast<int>(GetOptionCount());
    int currentIndex = static_cast<int>(GetCurrentIndex());
    int nextVirtualIndex = isDown ? currentIndex + 1 : currentIndex - 1;
    return nextVirtualIndex >= 0 && nextVirtualIndex < totalOptionCount;
}

bool TextPickerColumnPattern::NotLoopOptions() const
{
    RefPtr<TextPickerLayoutProperty> layout = GetParentLayout();
    CHECK_NULL_RETURN(layout, false);
    bool canLoop = layout->GetCanLoop().value_or(true);
    return !canLoop;
}

bool TextPickerColumnPattern::InnerHandleScroll(
    bool isDown, bool isUpdatePropertiesOnly, bool isUpdateAnimationProperties)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }

    if (NotLoopOptions() && ((isDown && currentIndex_ == totalOptionCount - 1) || (!isDown && currentIndex_ == 0))) {
        return false;
    }

    uint32_t currentIndex = GetCurrentIndex();
    if (isDown) {
        currentIndex = (totalOptionCount + currentIndex + 1) % totalOptionCount; // index add one
    } else {
        auto totalCountAndIndex = totalOptionCount + currentIndex;
        currentIndex = (totalCountAndIndex ? totalCountAndIndex - 1 : 0) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    if (hapticController_ && isEnableHaptic_) {
        hapticController_->PlayOnce();
    }
    FlushCurrentOptions(isDown, isUpdatePropertiesOnly, isUpdateAnimationProperties);
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    host->OnAccessibilityEvent(AccessibilityEventType::TEXT_CHANGE);
    return true;
}

bool TextPickerColumnPattern::OnKeyEvent(const KeyEvent& event)
{
    if (event.action != KeyAction::DOWN) {
        return false;
    }
    if (event.code == KeyCode::KEY_DPAD_UP || event.code == KeyCode::KEY_DPAD_DOWN ||
        event.code == KeyCode::KEY_DPAD_LEFT || event.code == KeyCode::KEY_DPAD_RIGHT) {
        HandleDirectionKey(event.code);
        return true;
    }
    return false;
}

bool TextPickerColumnPattern::HandleDirectionKey(KeyCode code)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto currentIndex = GetCurrentIndex();
    auto totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }
    if (code == KeyCode::KEY_DPAD_UP) {
        auto totalCountAndIndex = totalOptionCount + currentIndex;
        SetCurrentIndex((totalCountAndIndex ? totalCountAndIndex - 1 : 0) % totalOptionCount);
        FlushCurrentOptions();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        SetCurrentIndex((totalOptionCount + currentIndex + 1) % totalOptionCount);
        FlushCurrentOptions(true);
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    return false;
}
void TextPickerColumnPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->animationCreated_);
        if (!pattern->CanMove(true)) {
            return;
        }
        pattern->InnerHandleScroll(true);
        pattern->CreateAnimation(0.0 - pattern->jumpInterval_, 0.0);
        pattern->HandleScrollStopEventCallback(true);
        // AccessibilityEventType::SCROLL_END
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->animationCreated_);
        if (!pattern->CanMove(false)) {
            return;
        }
        pattern->InnerHandleScroll(false);
        pattern->CreateAnimation(pattern->jumpInterval_, 0.0);
        pattern->HandleScrollStopEventCallback(true);
        // AccessibilityEventType::SCROLL_END
    });
}

void TextPickerColumnPattern::OnAroundButtonClick(RefPtr<EventParam> param)
{
    if (clickBreak_) {
        return;
    }
    int32_t middleIndex = static_cast<int32_t>(GetShowOptionCount()) / HALF_NUMBER;
    int32_t step = param->itemIndex - middleIndex;
    if (step != 0) {
        if (animation_) {
            AnimationUtils::StopAnimation(animation_);
            yOffset_ = 0.0;
        }

        StopHapticController();
        isHapticPlayOnce_ = true;
        int32_t index = static_cast<int32_t>(currentIndex_) + step;
        auto overFirst = index < 0 && step < 0;
        auto overLast =
            index > static_cast<int32_t>(GetOptionCount() ? GetOptionCount() - 1 : 0) && step > 0;
        if (NotLoopOptions() && (overscroller_.IsOverScroll() || overFirst || overLast)) {
            return;
        }

        double distance =
            (step > 0 ? optionProperties_[middleIndex].prevDistance : optionProperties_[middleIndex].nextDistance) *
            std::abs(step);
        AnimationOption option;
        option.SetCurve(Curves::FAST_OUT_SLOW_IN);
        option.SetDuration(CLICK_ANIMATION_DURATION);
        yLast_ = 0.0;
        aroundClickProperty_->Set(0.0);
        animation_ = AnimationUtils::StartAnimation(option, [weak = AceType::WeakClaim(this), step, distance]() {
            auto column = weak.Upgrade();
            CHECK_NULL_VOID(column);
            column->aroundClickProperty_->Set(step > 0 ? 0.0 - std::abs(distance) : std::abs(distance));
        });
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContext();
        CHECK_NULL_VOID(pipeline);
        pipeline->RequestFrame();
    }
    SetSelectedMark();
}

void TextPickerColumnPattern::PlayResetAnimation()
{
    int32_t middleIndex = static_cast<int32_t>(GetShowOptionCount()) / HALF_NUMBER;
    ScrollDirection dir = GreatNotEqual(scrollDelta_, 0.0) ? ScrollDirection::DOWN : ScrollDirection::UP;
    double shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                        : optionProperties_[middleIndex].nextDistance;
    double shiftThreshold = shiftDistance / HALF_NUMBER;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == ScrollDirection::UP ? -1 : 1);
        if (NearZero(scrollDelta_)) {
            HandleScrollStopEventCallback(true);
        }
    }
    CreateAnimation(scrollDelta_, 0.0);
    if (!NearZero(scrollDelta_)) {
        HandleScrollStopEventCallback(true);
    }
}

void TextPickerColumnPattern::SetCanLoop(bool isLoop)
{
    if (isLoop_ == isLoop) {
        return;
    }

    isLoop_ = isLoop;
    if (overscroller_.IsOverScroll()) {
        overscroller_.Reset();
        isReboundInProgress_ = false;
        yOffset_ = 0.0;
        ScrollOption(0.0);
    }

    if (!isLoop && isTossStatus_) {
        auto toss = GetToss();
        CHECK_NULL_VOID(toss);
        overscroller_.SetLoopTossOffset(toss->GetTossOffset());
    }
}

void TextPickerColumnPattern::SetSelectedMarkListener(std::function<void(int& selectedColumnId)>& listener)
{
    focusedListerner_ = listener;
    if (!circleUtils_) {
        circleUtils_ = new PickerColumnPatternCircleUtils<TextPickerColumnPattern>();
    }
}

void TextPickerColumnPattern::SetSelectedMarkId(const int strColumnId)
{
    selectedColumnId_ = strColumnId;
}

void TextPickerColumnPattern::SetSelectedMark(bool focus, bool notify, bool reRender)
{
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    if (pickerTheme->IsCircleDial()) {
        CHECK_NULL_VOID(circleUtils_);
        circleUtils_->SetSelectedMark(this, pickerTheme, focus, notify, reRender);
    }
}

void TextPickerColumnPattern::SetSelectedMarkPaint(bool paint)
{
    selectedMarkPaint_ = paint;
}

void TextPickerColumnPattern::UpdateSelectedTextColor(const RefPtr<PickerTheme>& pickerTheme)
{
    UpdateAnimationColor(pickerTheme);

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    auto&& child = host->GetChildren();
    auto iter = child.begin();
    CHECK_NULL_VOID(iter != child.end());
    std::advance (iter, GetShowOptionCount() / PICKER_SELECT_AVERAGE);
    CHECK_NULL_VOID(iter != child.end());
    auto textNode = DynamicCast<FrameNode>(*iter);
    CHECK_NULL_VOID(textNode);
    auto textPattern = textNode->GetPattern<TextPattern>();
    CHECK_NULL_VOID(textPattern);
    auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);

    UpdateSelectedTextProperties(pickerTheme, textLayoutProperty, layoutProperty);

    textNode->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
    host->MarkDirtyNode(PROPERTY_UPDATE_DIFF);
}

void TextPickerColumnPattern::UpdateUserSetSelectColor()
{
    isUserSetSelectColor_ = true;
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto pickerTheme = pipeline->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    UpdateSelectedTextColor(pickerTheme);
}

void TextPickerColumnPattern::UpdateAnimationColor(const RefPtr<PickerTheme>& pickerTheme)
{
    CHECK_NULL_VOID(pickerTheme);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto blendNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(blendNode);
    auto stackNode = DynamicCast<FrameNode>(blendNode->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto layoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    Color color;

    if (pickerTheme->IsCircleDial() && !isUserSetSelectColor_) {
        if (selectedMarkPaint_) {
            color = pickerTheme->GetOptionStyle(true, true).GetTextColor();
        } else {
            color = pickerTheme->GetOptionStyle(false, false).GetTextColor();
        }
    } else {
        color = layoutProperty->GetSelectedColor().value_or(
            pickerTheme->GetOptionStyle(true, false).GetTextColor());
    }

    uint32_t middleIndex = GetShowOptionCount() / PICKER_SELECT_AVERAGE;
    if (middleIndex - NEXT_COLOUM_DIFF >= 0 && animationProperties_.size() > middleIndex) {
        animationProperties_[middleIndex - NEXT_COLOUM_DIFF].downColor = color;
        animationProperties_[middleIndex + NEXT_COLOUM_DIFF].upColor = color;
        animationProperties_[middleIndex].currentColor = color;
    }
}

void TextPickerColumnPattern::InitTextHeightAndFontHeight(uint32_t childIndex, uint32_t midIndex,
                                                          TextPickerOptionProperty &prop)
{
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<PickerTheme>();

    MeasureContext measureContext;
    measureContext.textContent = MEASURE_STRING;
    measureContext.fontFamily = FONT_FAMILY_DEFAULT[0];

    if (childIndex == midIndex) {
        measureContext.fontSize = theme->GetOptionStyle(true, false).GetFontSize();
    } else if ((childIndex == (midIndex + 1)) || (childIndex == (midIndex - 1))) {
        measureContext.fontSize = theme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    } else {
        measureContext.fontSize = theme->GetOptionStyle(false, false).GetFontSize();
    }

    Size size = MeasureUtil::MeasureTextSize(measureContext);
    prop.fontheight = size.Height();
    prop.height = (childIndex == midIndex) ? dividerSpacing_ : gradientHeight_;
}

#ifdef SUPPORT_DIGITAL_CROWN
int32_t& TextPickerColumnPattern::GetSelectedColumnId()
{
    return selectedColumnId_;
}

bool TextPickerColumnPattern::IsCrownEventEnded()
{
    return isCrownEventEnded_;
}

int32_t TextPickerColumnPattern::GetDigitalCrownSensitivity()
{
    if (crownSensitivity_ == INVALID_CROWNSENSITIVITY) {
        auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
        CHECK_NULL_RETURN(pipeline, DEFAULT_CROWNSENSITIVITY);
        auto pickerTheme = pipeline->GetTheme<PickerTheme>();
        CHECK_NULL_RETURN(pickerTheme, DEFAULT_CROWNSENSITIVITY);
        crownSensitivity_ = pickerTheme->GetDigitalCrownSensitivity();
    }

    return crownSensitivity_;
}

void TextPickerColumnPattern::SetDigitalCrownSensitivity(int32_t crownSensitivity)
{
    crownSensitivity_ = crownSensitivity;
}

bool TextPickerColumnPattern::OnCrownEvent(const CrownEvent& event)
{
    CHECK_NULL_RETURN(circleUtils_, false);
    return circleUtils_->OnCrownEvent(this, event);
}

void TextPickerColumnPattern::HandleCrownBeginEvent(const CrownEvent& event)
{
    auto toss = GetToss();
    CHECK_NULL_VOID(toss);
    auto offsetY = 0.0;
    toss->SetStart(offsetY);
    yLast_ = offsetY;
    overscroller_.SetStart(offsetY);
    pressed_ = true;
    isCrownEventEnded_ = false;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, yLast_, SceneStatus::START);

    if (animation_) {
        AnimationUtils::StopAnimation(animation_);
    }

    if (NotLoopOptions() && reboundAnimation_) {
        AnimationUtils::StopAnimation(reboundAnimation_);
        isReboundInProgress_ = false;
        overscroller_.ResetVelocity();
        overscroller_.SetOverScroll(scrollDelta_);
    }
}

void TextPickerColumnPattern::HandleCrownMoveEvent(const CrownEvent& event)
{
    SetMainVelocity(event.angularVelocity);
    animationBreak_ = false;
    isCrownEventEnded_ = false;
    CHECK_NULL_VOID(pressed_);
    auto toss = GetToss();
    CHECK_NULL_VOID(toss);
    CHECK_NULL_VOID(circleUtils_);
    auto offsetY = circleUtils_->GetCrownRotatePx(event, GetDigitalCrownSensitivity());
    offsetY += yLast_;
    if (NearEqual(offsetY, yLast_, MOVE_THRESHOLD)) { // if changing less than MOVE_THRESHOLD, no need to handle
        return;
    }
    toss->SetEnd(offsetY);
    UpdateColumnChildPosition(offsetY);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::RUNNING);
}

void TextPickerColumnPattern::HandleCrownEndEvent(const CrownEvent& event)
{
    SetMainVelocity(event.angularVelocity);
    pressed_ = false;
    isCrownEventEnded_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (NotLoopOptions()) {
        frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
        if (overscroller_.IsOverScroll()) { // Start rebound animation. Higher priority than fling
            CreateReboundAnimation(overscroller_.GetOverScroll(), 0.0);
            StopHapticController();
            return;
        }
    }

    yOffset_ = 0.0;
    yLast_ = 0.0;
    if (!animationCreated_) {
        ScrollOption(0.0);
        return;
    }

    ScrollDirection dir = GreatNotEqual(scrollDelta_, 0.0f) ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto middleIndex = static_cast<int32_t>(GetShowOptionCount()) / HALF_NUMBER;
    auto shiftDistance = (dir == ScrollDirection::DOWN) ? optionProperties_[middleIndex].nextDistance
                                                        : optionProperties_[middleIndex].prevDistance;
    auto shiftThreshold = shiftDistance / HALF_NUMBER;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == ScrollDirection::UP ? -1 : 1);
    }
    CreateAnimation(scrollDelta_, 0.0);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
    StopHapticController();
}
#endif

} // namespace OHOS::Ace::NG

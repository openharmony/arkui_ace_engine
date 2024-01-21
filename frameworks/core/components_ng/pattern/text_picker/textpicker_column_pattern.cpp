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

#include "base/geometry/dimension.h"
#include "base/geometry/ng/size_t.h"
#include "base/utils/measure_util.h"
#include "base/utils/utils.h"
#include "core/components/picker/picker_theme.h"
#include "core/components_ng/base/frame_scene_status.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text_picker/textpicker_event_hub.h"
#include "core/components_ng/pattern/text_picker/textpicker_layout_property.h"
#include "core/components_ng/pattern/text_picker/textpicker_pattern.h"
#include "core/components_ng/pattern/text_picker/toss_animation_controller.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {
namespace {
const Dimension FONT_SIZE = Dimension(2.0);
const Dimension FOCUS_SIZE = Dimension(1.0);
const float MOVE_DISTANCE = 5.0f;
constexpr float FONTWEIGHT = 0.5f;
constexpr float FONT_SIZE_PERCENT = 1.0f;
constexpr int32_t HOVER_ANIMATION_DURATION = 40;
constexpr int32_t CLICK_ANIMATION_DURATION = 300;
constexpr size_t MIXTURE_CHILD_COUNT = 2;
const uint32_t OPTION_COUNT_PHONE_LANDSCAPE = 3;
const Dimension ICON_SIZE = 24.0_vp;
const Dimension ICON_TEXT_SPACE = 8.0_vp;
const std::string REGULAR_FONT_FAMILY = "sans-serif";
const std::string MEASURE_STRING = "TEST";
const int32_t HALF_NUMBER = 2;
const int32_t BUFFER_NODE_NUMBER = 2;
constexpr char PICKER_DRAG_SCENE[] = "picker_drag_scene";
} // namespace

void TextPickerColumnPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
    CHECK_NULL_VOID(pickerTheme);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    tossAnimationController_->SetPipelineContext(context);
    tossAnimationController_->SetColumn(AceType::WeakClaim(this));
    jumpInterval_ = pickerTheme->GetJumpInterval().ConvertToPx();
    CreateAnimation();
    InitPanEvent(gestureHub);
    host->GetRenderContext()->SetClipToFrame(true);
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
    auto theme = pipeline->GetTheme<PickerTheme>();
    pressColor_ = theme->GetPressColor();
    hoverColor_ = theme->GetHoverColor();
    auto showCount = GetShowOptionCount();
    InitMouseAndPressEvent();
    SetAccessibilityAction();
    if (optionProperties_.size() <= 0) {
        auto midIndex = showCount / HALF_NUMBER;
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        dividerSpacing_ = pipeline->NormalizeToPx(theme->GetDividerSpacing());
        gradientHeight_ = static_cast<float>(pipeline->NormalizeToPx(theme->GetGradientHeight()));
        MeasureContext measureContext;
        measureContext.textContent = MEASURE_STRING;
        uint32_t childIndex = 0;
        TextPickerOptionProperty prop;
        while (childIndex < showCount) {
            if (childIndex == midIndex) {
                auto selectedOptionSize = theme->GetOptionStyle(true, false).GetFontSize();
                measureContext.fontSize = selectedOptionSize;
                measureContext.fontFamily = REGULAR_FONT_FAMILY;
            } else if ((childIndex == (midIndex + 1)) || (childIndex == (midIndex - 1))) {
                auto focusOptionSize = theme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
                measureContext.fontSize = focusOptionSize;
                measureContext.fontFamily = REGULAR_FONT_FAMILY;
            } else {
                auto normalOptionSize = theme->GetOptionStyle(false, false).GetFontSize();
                measureContext.fontSize = normalOptionSize;
                measureContext.fontFamily = REGULAR_FONT_FAMILY;
            }
            if (childIndex == midIndex) {
                prop.height = dividerSpacing_;
            } else {
                prop.height = gradientHeight_;
            }
            Size size = MeasureUtil::MeasureTextSize(measureContext);
            prop.fontheight = size.Height();
            optionProperties_.emplace_back(prop);
            childIndex++;
        }
        SetOptionShiftDistance();
    }
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
    PlayPressAnimation(Color::TRANSPARENT);
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
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            if (isToss) {
                pattern->touchBreak_ = true;
                pattern->animationBreak_ = true;
                pattern->clickBreak_ = true;
                auto TossEndPosition = toss->GetTossEndPosition();
                pattern->SetYLast(TossEndPosition);
                toss->StopTossAnimation();
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

void TextPickerColumnPattern::InitMouseAndPressEvent()
{
    if (mouseEvent_ || touchListener_) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto columnEventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(columnEventHub);
    RefPtr<TouchEventImpl> touchListener = CreateItemTouchEventListener();
    CHECK_NULL_VOID(touchListener);
    auto columnGesture = columnEventHub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(columnGesture);
    columnGesture->AddTouchEvent(touchListener);
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto childSize = static_cast<int32_t>(host->GetChildren().size());
    RefPtr<FrameNode> middleChild = nullptr;
    auto midSize = childSize / 2;
    middleChild = DynamicCast<FrameNode>(host->GetChildAtIndex(midSize));
    CHECK_NULL_VOID(middleChild);
    auto eventHub = middleChild->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto inputHub = eventHub->GetOrCreateInputEventHub();
    auto mouseTask = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(isHover);
    };
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseTask));
    inputHub->AddOnHoverEvent(mouseEvent_);
    auto gesture = middleChild->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gesture);
    auto touchCallback = [weak = WeakClaim(this), toss](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (info.GetTouches().front().GetTouchType() == TouchType::DOWN) {
            pattern->SetLocalDownDistance(info.GetTouches().front().GetLocalLocation().GetDistance());
            pattern->OnMiddleButtonTouchDown();
            return;
        }
        if (info.GetTouches().front().GetTouchType() == TouchType::UP) {
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
    gesture->AddTouchEvent(touchListener_);
    int32_t i = 0;
    for (const auto& child : host->GetChildren()) {
        RefPtr<FrameNode> childNode = DynamicCast<FrameNode>(child);
        CHECK_NULL_VOID(childNode);
        RefPtr<EventParam> param = MakeRefPtr<EventParam>();
        param->instance = childNode;
        param->itemIndex = i;
        param->itemTotalCounts = childSize;
        auto eventHub = childNode->GetEventHub<EventHub>();
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
    if (isHover) {
        PlayPressAnimation(hoverColor_);
    } else {
        PlayPressAnimation(Color::TRANSPARENT);
    }
}

void TextPickerColumnPattern::SetButtonBackgroundColor(const Color& pressColor)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto stack = host->GetParent();
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
        auto stackNode = DynamicCast<FrameNode>(host->GetParent());
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

void TextPickerColumnPattern::FlushCurrentOptions(
    bool isDown, bool isUpateTextContentOnly, bool isDirectlyClear, bool isUpdateAnimationProperties)
{
    ResetOptionPropertyHeight();

    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto stackNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_VOID(stackNode);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_VOID(parentNode);
    auto textPickerLayoutProperty = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    CHECK_NULL_VOID(textPickerLayoutProperty);

    if (!isUpateTextContentOnly) {
        animationProperties_.clear();
    }
    if (columnkind_ == TEXT) {
        FlushCurrentTextOptions(textPickerLayoutProperty, isUpateTextContentOnly, isDirectlyClear);
    } else if (columnkind_ == ICON) {
        FlushCurrentImageOptions();
    } else if (columnkind_ == MIXTURE) {
        FlushCurrentMixtureOptions(textPickerLayoutProperty, isUpateTextContentOnly);
    }
    if (isUpateTextContentOnly && isUpdateAnimationProperties) {
        FlushAnimationTextProperties(isDown);
    }
}

void TextPickerColumnPattern::ClearCurrentTextOptions(
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, bool isUpateTextContentOnly, bool isDirectlyClear)
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
            textLayoutProperty->UpdateContent("");
            textNode->GetRenderContext()->SetClipToFrame(true);
            textNode->MarkModifyDone();
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
        selectedIndex_ = 0;
    }
}

void TextPickerColumnPattern::FlushCurrentTextOptions(
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, bool isUpateTextContentOnly, bool isDirectlyClear)
{
    ClearCurrentTextOptions(textPickerLayoutProperty, isUpateTextContentOnly, isDirectlyClear);
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
        if (!isUpateTextContentOnly) {
            UpdatePickerTextProperties(textLayoutProperty, textPickerLayoutProperty, index, middleIndex, showCount);
        }
        if (NotLoopOptions() && !virtualIndexValidate) {
            textLayoutProperty->UpdateContent("");
        } else {
            textLayoutProperty->UpdateContent(optionValue.text_);
            textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);
        }
        textNode->GetRenderContext()->SetClipToFrame(true);
        textNode->MarkModifyDone();
        textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        iter++;
    }
    selectedIndex_ = currentIndex;
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
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty, bool isUpateTextContentOnly)
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
        auto iconLayoutProperty = iconPattern->GetLayoutProperty<ImageLayoutProperty>();
        CHECK_NULL_VOID(iconLayoutProperty);
        CalcSize idealSize = { CalcSize(CalcLength(ICON_SIZE), CalcLength(ICON_SIZE)) };
        MeasureProperty layoutConstraint;
        layoutConstraint.selfIdealSize = idealSize;
        iconLayoutProperty->UpdateCalcLayoutProperty(layoutConstraint);
        MarginProperty margin;
        margin.right = CalcLength(ICON_TEXT_SPACE);
        iconLayoutProperty->UpdateMargin(margin);

        auto textNode = DynamicCast<FrameNode>(linearLayoutNode->GetLastChild());
        auto textPattern = textNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(textPattern);
        auto textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(textLayoutProperty);
        if (!isUpateTextContentOnly) {
            UpdatePickerTextProperties(textLayoutProperty, textPickerLayoutProperty, index, middleIndex, showCount);
        }
        if (NotLoopOptions() && !virtualIndexValidate) {
            iconLayoutProperty->UpdateVisibility(VisibleType::INVISIBLE);
            textLayoutProperty->UpdateContent("");
        } else {
            textLayoutProperty->UpdateContent(optionValue.text_);
            iconLayoutProperty->UpdateVisibility(VisibleType::VISIBLE);
            iconLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(optionValue.icon_));
        }
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
    if (!animationProperties_.size()) {
        return;
    }
    if (isDown) {
        for (size_t i = 0; i < animationProperties_.size(); i++) {
            if (i > 0) {
                animationProperties_[i - 1].upFontSize = animationProperties_[i].upFontSize;
                animationProperties_[i - 1].fontSize = animationProperties_[i].fontSize;
                animationProperties_[i - 1].downFontSize = animationProperties_[i].downFontSize;

                animationProperties_[i - 1].upColor = animationProperties_[i].upColor;
                animationProperties_[i - 1].currentColor = animationProperties_[i].currentColor;
                animationProperties_[i - 1].downColor = animationProperties_[i].downColor;
            }
            if (i == (animationProperties_.size() - 1)) {
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
        for (size_t i = animationProperties_.size() - 1;; i--) {
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
    auto normalOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(textPickerLayoutProperty->GetDisappearColor().value_or(
        pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (textPickerLayoutProperty->HasDisappearFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetDisappearFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(normalOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(false, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(textPickerLayoutProperty->GetDisappearWeight().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(textPickerLayoutProperty->GetDisappearFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(textPickerLayoutProperty->GetDisappearFontStyle().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TextPickerColumnPattern::UpdateCandidateTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty)
{
    auto focusOptionSize = pickerTheme->GetOptionStyle(false, false).GetFontSize() + FONT_SIZE;
    textLayoutProperty->UpdateTextColor(
        textPickerLayoutProperty->GetColor().value_or(pickerTheme->GetOptionStyle(false, false).GetTextColor()));
    if (textPickerLayoutProperty->HasFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(focusOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(
            pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize() - FOCUS_SIZE);
    }
    textLayoutProperty->UpdateFontWeight(
        textPickerLayoutProperty->GetWeight().value_or(pickerTheme->GetOptionStyle(false, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(textPickerLayoutProperty->GetFontFamily().value_or(
        pickerTheme->GetOptionStyle(false, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(
        textPickerLayoutProperty->GetFontStyle().value_or(pickerTheme->GetOptionStyle(false, false).GetFontStyle()));
}

void TextPickerColumnPattern::UpdateSelectedTextProperties(const RefPtr<PickerTheme>& pickerTheme,
    const RefPtr<TextLayoutProperty>& textLayoutProperty,
    const RefPtr<TextPickerLayoutProperty>& textPickerLayoutProperty)
{
    auto selectedOptionSize = pickerTheme->GetOptionStyle(true, false).GetFontSize();
    textLayoutProperty->UpdateTextColor(
        textPickerLayoutProperty->GetSelectedColor().value_or(pickerTheme->GetOptionStyle(true, false).GetTextColor()));
    if (textPickerLayoutProperty->HasSelectedFontSize()) {
        textLayoutProperty->UpdateFontSize(textPickerLayoutProperty->GetSelectedFontSize().value());
    } else {
        textLayoutProperty->UpdateAdaptMaxFontSize(selectedOptionSize);
        textLayoutProperty->UpdateAdaptMinFontSize(pickerTheme->GetOptionStyle(true, false).GetAdaptMinFontSize());
    }
    textLayoutProperty->UpdateFontWeight(textPickerLayoutProperty->GetSelectedWeight().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontWeight()));
    textLayoutProperty->UpdateFontFamily(textPickerLayoutProperty->GetSelectedFontFamily().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontFamilies()));
    textLayoutProperty->UpdateItalicFontStyle(textPickerLayoutProperty->GetSelectedFontStyle().value_or(
        pickerTheme->GetOptionStyle(true, false).GetFontStyle()));
}

void TextPickerColumnPattern::AddAnimationTextProperties(
    uint32_t currentIndex, const RefPtr<TextLayoutProperty>& textLayoutProperty)
{
    TextProperties properties{};
    if (textLayoutProperty->HasFontSize()) {
        MeasureContext measureContext;
        measureContext.textContent = MEASURE_STRING;
        measureContext.fontSize = textLayoutProperty->GetFontSize().value();
        auto size = MeasureUtil::MeasureTextSize(measureContext);
        if (!optionProperties_.empty()) {
            optionProperties_[currentIndex].fontheight = size.Height();
            if (optionProperties_[currentIndex].fontheight > optionProperties_[currentIndex].height) {
                optionProperties_[currentIndex].fontheight = optionProperties_[currentIndex].height;
            }
        }
        SetOptionShiftDistance();
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto pickerTheme = context->GetTheme<PickerTheme>();
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
    AddAnimationTextProperties(currentIndex, textLayoutProperty);
}

void TextPickerColumnPattern::TextPropertiesLinearAnimation(
    const RefPtr<TextLayoutProperty>& textLayoutProperty, uint32_t index, uint32_t showCount, bool isDown, double scale)
{
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
    if (!isDown) {
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
    Dimension updateSize = LinearFontSize(startFontSize, endFontSize, distancePercent_);
    textLayoutProperty->UpdateFontSize(updateSize);
    auto colorEvaluator = AceType::MakeRefPtr<LinearEvaluator<Color>>();
    Color updateColor = colorEvaluator->Evaluate(startColor, endColor, distancePercent_);
    textLayoutProperty->UpdateTextColor(updateColor);
    if (scale < FONTWEIGHT) {
        textLayoutProperty->UpdateFontWeight(animationProperties_[index].fontWeight);
    }
}

void TextPickerColumnPattern::UpdateTextPropertiesLinear(bool isDown, double scale)
{
    if (columnkind_ == ICON) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    uint32_t showCount = GetShowOptionCount();
    auto child = host->GetChildren();
    auto iter = child.begin();
    if (child.size() != showCount) {
        return;
    }
    for (uint32_t index = 0; index < showCount; index++) {
        auto rangeNode = DynamicCast<FrameNode>(*iter);
        CHECK_NULL_VOID(rangeNode);
        RefPtr<TextLayoutProperty> textLayoutProperty;
        if (columnkind_ == TEXT) {
            auto textPattern = rangeNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(textPattern);
            textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
            TextPropertiesLinearAnimation(textLayoutProperty, index, showCount, isDown, scale);
        } else if (columnkind_ == MIXTURE) {
            auto children = rangeNode->GetChildren();
            if (children.size() != MIXTURE_CHILD_COUNT) {
                continue;
            }
            auto textNode = DynamicCast<FrameNode>(rangeNode->GetLastChild());
            auto textPattern = textNode->GetPattern<TextPattern>();
            textLayoutProperty = textPattern->GetLayoutProperty<TextLayoutProperty>();
            CHECK_NULL_VOID(textLayoutProperty);
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
        return startFontSize + (endFontSize - startFontSize) * percent;
    }
}

void TextPickerColumnPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    CHECK_NULL_VOID(!panEvent_);
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& event) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
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
    gestureHub->AddPanEvent(panEvent_, panDirection, DEFAULT_PAN_FINGER, DEFAULT_PAN_DISTANCE);
}

RefPtr<TextPickerLayoutProperty> TextPickerColumnPattern::GetParentLayout() const
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto stackNode = DynamicCast<FrameNode>(host->GetParent());
    CHECK_NULL_RETURN(stackNode, nullptr);
    auto parentNode = DynamicCast<FrameNode>(stackNode->GetParent());
    CHECK_NULL_RETURN(parentNode, nullptr);

    auto property = parentNode->GetLayoutProperty<TextPickerLayoutProperty>();
    return property;
}

void TextPickerColumnPattern::HandleDragStart(const GestureEvent& event)
{
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY = event.GetGlobalPoint().GetY();
    toss->SetStart(offsetY);
    yLast_ = offsetY;
    pressed_ = true;
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, event.GetMainVelocity(), SceneStatus::START);
    // AccessibilityEventType::SCROLL_START
}

void TextPickerColumnPattern::HandleDragMove(const GestureEvent& event)
{
    if (event.GetFingerList().size() > 1) {
        return;
    }
    if (event.GetInputEventType() == InputEventType::AXIS && event.GetSourceTool() == SourceTool::MOUSE) {
        InnerHandleScroll(LessNotEqual(event.GetDelta().GetY(), 0.0), true);
        return;
    }
    animationBreak_ = false;
    CHECK_NULL_VOID(pressed_);
    CHECK_NULL_VOID(GetHost());
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto offsetY =
        event.GetGlobalPoint().GetY() + (event.GetInputEventType() == InputEventType::AXIS ? event.GetOffsetY() : 0.0);
    if (NearEqual(offsetY, yLast_, 1.0)) { // if changing less than 1.0, no need to handle
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
    pressed_ = false;
    CHECK_NULL_VOID(GetToss());
    auto toss = GetToss();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (!NotLoopOptions() && toss->Play()) {
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
    ScrollDirection dir = scrollDelta_ > 0.0 ? ScrollDirection::DOWN : ScrollDirection::UP;
    int32_t middleIndex = GetShowOptionCount() / HALF_NUMBER;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                      : optionProperties_[middleIndex].nextDistance;
    auto shiftThreshold = shiftDistance / HALF_NUMBER;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == ScrollDirection::UP ? -1 : 1);
    }
    CreateAnimation(scrollDelta_, 0.0);
    frameNode->AddFRCSceneInfo(PICKER_DRAG_SCENE, mainVelocity_, SceneStatus::END);
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
        if (value > 0) {
            column->UpdateColumnChildPosition(std::ceil(value));
        } else {
            column->UpdateColumnChildPosition(std::floor(value));
        }
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

void TextPickerColumnPattern::ScrollOption(double delta)
{
    scrollDelta_ = delta;
    auto midIndex = GetShowOptionCount() / HALF_NUMBER;
    ScrollDirection dir = delta > 0.0 ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                      : optionProperties_[midIndex].nextDistance;
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
        double distance =
            (dir == ScrollDirection::UP) ? optionProperties_[i].prevDistance : optionProperties_[i].nextDistance;
        algorithmOffset_.emplace_back(static_cast<int32_t>(distance * distancePercent));
    }
}

double TextPickerColumnPattern::GetShiftDistance(int32_t index, ScrollDirection dir)
{
    int32_t optionCounts = GetShowOptionCount();
    if (optionCounts == 0) {
        return 0.0;
    }
    int32_t nextIndex = 0;
    auto isDown = dir == ScrollDirection::DOWN;
    nextIndex = isDown ? (optionCounts + index + 1) % optionCounts : (optionCounts + index - 1) % optionCounts;
    double distance = 0.0;
    double val = 0.0;
    switch (static_cast<OptionIndex>(index)) {
        case OptionIndex::COLUMN_INDEX_0: // first
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[index].height);
            break;
        case OptionIndex::COLUMN_INDEX_1:
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[index].height);
            break;
        case OptionIndex::COLUMN_INDEX_2:
            if (dir == ScrollDirection::UP) {
                distance = -optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
                distance = std::ceil(val);
            }
            break;

        case OptionIndex::COLUMN_INDEX_3:
            val = optionProperties_[index].height / HALF_NUMBER + optionProperties_[nextIndex].height -
                  optionProperties_[nextIndex].fontheight / HALF_NUMBER;
            distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
            distance = std::floor(distance);
            break;
        case OptionIndex::COLUMN_INDEX_4:
            if (dir == ScrollDirection::DOWN) {
                distance = optionProperties_[nextIndex].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
                distance = std::ceil(0.0f - val);
            }
            break;
        case OptionIndex::COLUMN_INDEX_5:
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[index].height);
            break;
        case OptionIndex::COLUMN_INDEX_6: // last
            distance = (dir == ScrollDirection::DOWN) ? optionProperties_[index].height
                                                      : (0.0 - optionProperties_[index].height);
            break;
        default:
            break;
    }

    return distance;
}

double TextPickerColumnPattern::GetShiftDistanceForLandscape(int32_t index, ScrollDirection dir)
{
    int32_t optionCounts = GetShowOptionCount();
    if (optionCounts == 0) {
        return 0.0;
    }
    int32_t nextIndex = 0;
    auto isDown = dir == ScrollDirection::DOWN;
    nextIndex = isDown ? (optionCounts + index + 1) % optionCounts : (optionCounts + index - 1) % optionCounts;
    double distance = 0.0;
    double val = 0.0;
    switch (static_cast<OptionIndex>(index)) {
        case OptionIndex::COLUMN_INDEX_0:
            if (dir == ScrollDirection::UP) {
                distance = 0.0 - optionProperties_[index].height;
            } else {
                distance =
                    optionProperties_[index].height +
                    (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
            }
            break;

        case OptionIndex::COLUMN_INDEX_1:
            val = optionProperties_[index].height / HALF_NUMBER + optionProperties_[nextIndex].height -
                  optionProperties_[nextIndex].fontheight / HALF_NUMBER;
            distance = (dir == ScrollDirection::DOWN) ? val : (0.0 - val);
            distance = std::floor(distance);
            break;

        case OptionIndex::COLUMN_INDEX_2:
            if (dir == ScrollDirection::DOWN) {
                distance = optionProperties_[index].height;
            } else {
                val = optionProperties_[index].height +
                      (optionProperties_[nextIndex].height - optionProperties_[nextIndex].fontheight) / HALF_NUMBER;
                distance = 0.0 - val;
            }
            break;
        default:
            break;
    }

    return distance;
}

void TextPickerColumnPattern::SetOptionShiftDistance()
{
    int32_t itemCounts = GetShowOptionCount();
    bool isLanscape = itemCounts == OPTION_COUNT_PHONE_LANDSCAPE + BUFFER_NODE_NUMBER;
    for (int32_t i = 0; i < itemCounts; i++) {
        TextPickerOptionProperty& prop = optionProperties_[i];
        if (isLanscape) {
            prop.prevDistance = GetShiftDistanceForLandscape(i, ScrollDirection::UP);
            prop.nextDistance = GetShiftDistanceForLandscape(i, ScrollDirection::DOWN);
        } else {
            prop.prevDistance = GetShiftDistance(i, ScrollDirection::UP);
            prop.nextDistance = GetShiftDistance(i, ScrollDirection::DOWN);
        }
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
    yLast_ = 0.0;
}

void TextPickerColumnPattern::UpdateFinishToss(double offsetY)
{
    int32_t dragDelta = offsetY - yLast_;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    auto midIndex = GetShowOptionCount() / HALF_NUMBER;
    ScrollDirection dir = dragDelta > 0.0 ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                      : optionProperties_[midIndex].nextDistance;
    ScrollOption(shiftDistance);
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

void TextPickerColumnPattern::UpdateColumnChildPosition(double offsetY, bool isUpatePropertiesOnly)
{
    int32_t dragDelta = offsetY - yLast_;
    yLast_ = offsetY;
    if (!CanMove(LessNotEqual(dragDelta, 0))) {
        return;
    }
    offsetCurSet_ = 0.0;
    auto midIndex = GetShowOptionCount() / HALF_NUMBER;
    ScrollDirection dir = dragDelta > 0.0 ? ScrollDirection::DOWN : ScrollDirection::UP;
    auto shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[midIndex].prevDistance
                                                      : optionProperties_[midIndex].nextDistance;
    // the abs of drag delta is less than jump interval.
    dragDelta = dragDelta + yOffset_;
    if (GreatOrEqual(std::abs(dragDelta), std::abs(shiftDistance))) {
        InnerHandleScroll(LessNotEqual(dragDelta, 0.0), true, false);
        dragDelta = dragDelta % static_cast<int>(std::abs(shiftDistance));
    }
    // update selected option
    ScrollOption(dragDelta);
    offsetCurSet_ = dragDelta;
    yOffset_ = dragDelta;
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
    bool canLoop = layout->GetCanLoop().value();
    return !canLoop;
}

bool TextPickerColumnPattern::InnerHandleScroll(
    bool isDown, bool isUpatePropertiesOnly, bool isUpdateAnimationProperties)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }

    uint32_t currentIndex = GetCurrentIndex();
    if (isDown) {
        currentIndex = (totalOptionCount + currentIndex + 1) % totalOptionCount; // index add one
    } else {
        currentIndex = (totalOptionCount + currentIndex - 1) % totalOptionCount; // index reduce one
    }
    SetCurrentIndex(currentIndex);
    FlushCurrentOptions(isDown, isUpatePropertiesOnly, isUpdateAnimationProperties);
    HandleChangeCallback(isDown, true);
    HandleEventCallback(true);

    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
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
    auto currernIndex = GetCurrentIndex();
    auto totalOptionCount = GetOptionCount();
    if (totalOptionCount == 0) {
        return false;
    }
    if (code == KeyCode::KEY_DPAD_UP) {
        SetCurrentIndex((totalOptionCount + currernIndex - 1) % totalOptionCount);
        FlushCurrentOptions();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        return true;
    }
    if (code == KeyCode::KEY_DPAD_DOWN) {
        SetCurrentIndex((totalOptionCount + currernIndex + 1) % totalOptionCount);
        FlushCurrentOptions();
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
        // AccessibilityEventType::SCROLL_END
    });
}

void TextPickerColumnPattern::OnAroundButtonClick(RefPtr<EventParam> param)
{
    if (clickBreak_) {
        return;
    }
    int32_t middleIndex = GetShowOptionCount() / HALF_NUMBER;
    int32_t step = param->itemIndex - middleIndex;
    if (step != 0) {
        if (animation_) {
            AnimationUtils::StopAnimation(animation_);
            yLast_ = 0.0;
            yOffset_ = 0.0;
        }
        double distance =
            (step > 0 ? optionProperties_[middleIndex].prevDistance : optionProperties_[middleIndex].nextDistance) *
            std::abs(step);
        AnimationOption option;
        option.SetCurve(Curves::FAST_OUT_SLOW_IN);
        option.SetDuration(CLICK_ANIMATION_DURATION);
        aroundClickProperty_->Set(0.0);
        animation_ = AnimationUtils::StartAnimation(option, [weak = AceType::WeakClaim(this), step, distance]() {
            auto column = weak.Upgrade();
            CHECK_NULL_VOID(column);
            column->aroundClickProperty_->Set(step > 0 ? 0.0 - std::abs(distance) : std::abs(distance));
        });
    }
}

void TextPickerColumnPattern::PlayResetAnimation()
{
    ScrollDirection dir = scrollDelta_ > 0.0 ? ScrollDirection::DOWN : ScrollDirection::UP;
    int32_t middleIndex = static_cast<int32_t>(GetShowOptionCount()) / HALF_NUMBER;
    double shiftDistance = (dir == ScrollDirection::UP) ? optionProperties_[middleIndex].prevDistance
                                                        : optionProperties_[middleIndex].nextDistance;
    double shiftThreshold = shiftDistance / HALF_NUMBER;
    if (std::abs(scrollDelta_) >= std::abs(shiftThreshold)) {
        InnerHandleScroll(LessNotEqual(scrollDelta_, 0.0), true, false);
        scrollDelta_ = scrollDelta_ - std::abs(shiftDistance) * (dir == ScrollDirection::UP ? -1 : 1);
    }

    CreateAnimation(scrollDelta_, 0.0);
}
} // namespace OHOS::Ace::NG

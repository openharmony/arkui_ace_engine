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
 
#include "core/components_ng/pattern/slider/slider_pattern.h"

#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/utils/utils.h"
#include "base/utils/utf_helper.h"
#include "core/common/container.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/pipeline_base.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
constexpr float HALF = 0.5;
constexpr float SLIDER_MIN = .0f;
constexpr float SLIDER_MAX = 100.0f;
constexpr Dimension BUBBLE_TO_SLIDER_DISTANCE = 10.0_vp;
constexpr Dimension FORM_PAN_DISTANCE = 1.0_vp;
constexpr double DEFAULT_SLIP_FACTOR = 50.0;
constexpr double SLIP_FACTOR_COEFFICIENT = 1.07;
constexpr uint64_t SCREEN_READ_SENDEVENT_TIMESTAMP = 400;
const std::string STR_SCREEN_READ_SENDEVENT = "ArkUISliderSendAccessibilityValueEvent";

bool GetReverseValue(RefPtr<SliderLayoutProperty> layoutProperty)
{
    auto reverse = layoutProperty->GetReverseValue(false);
    auto direction = layoutProperty->GetLayoutDirection();
    auto axis = layoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    if (direction == TextDirection::AUTO && axis == Axis::HORIZONTAL) {
        return AceApplicationInfo::GetInstance().IsRightToLeft() ? !reverse : reverse;
    }
    return direction == TextDirection::RTL ? !reverse : reverse;
}
} // namespace

void SliderPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto inputEventHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    auto layoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    layoutProperty->UpdateAlignment(Alignment::CENTER);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    showTips_ = sliderPaintProperty->GetShowTips().value_or(false);
    sliderInteractionMode_ =
        sliderPaintProperty->GetSliderInteractionModeValue(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK);
    minResponse_ = sliderPaintProperty->GetMinResponsiveDistance().value_or(0.0f);
    if (!panMoveFlag_) {
        UpdateToValidValue();
    }
    UpdateBlock();
    InitClickEvent(gestureHub);
    InitTouchEvent(gestureHub);
    InitPanEvent(gestureHub);
    InitMouseEvent(inputEventHub);
    auto focusHub = hub->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
    InitializeBubble();
    HandleEnabled();
    SetAccessibilityAction();
    InitAccessibilityHoverEvent();
    AccessibilityVirtualNodeRenderTask();
    InitSliderAccessibilityEnabledRegister();
    InitOrRefreshSlipFactor();
}

void SliderPattern::HandleEnabled()
{
    if (UseContentModifier()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto originalOpacity = renderContext->GetOpacityValue(1.0f);
    if (enabled) {
        renderContext->OnOpacityUpdate(originalOpacity);
        return;
    }
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto alpha = theme->GetDisabledAlpha();
    renderContext->OnOpacityUpdate(alpha * originalOpacity);
}

void SliderPattern::InitAccessibilityHoverEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetOrCreateInputEventHub();
    eventHub->SetAccessibilityHoverEvent([weak = WeakClaim(this)](bool isHover, AccessibilityHoverInfo& info) {
        auto slider = weak.Upgrade();
        CHECK_NULL_VOID(slider);
        slider->HandleAccessibilityHoverEvent(isHover, info);
    });
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this)](bool focus) {
        if (focus) {
            auto slider = weak.Upgrade();
            CHECK_NULL_VOID(slider);
            slider->HandleSliderOnAccessibilityFocusCallback();
        }
    });
}

void SliderPattern::HandleSliderOnAccessibilityFocusCallback()
{
    for (const auto& pointNode : pointAccessibilityNodeVec_) {
        pointNode->GetAccessibilityProperty<AccessibilityProperty>()->SetAccessibilityLevel(
            AccessibilityProperty::Level::NO_STR);
    }
}

class SliderAccessibilitySAObserverCallback : public AccessibilitySAObserverCallback {
public:
    SliderAccessibilitySAObserverCallback(
        const WeakPtr<SliderPattern> &weakSliderPattern, int64_t accessibilityId)
        : AccessibilitySAObserverCallback(accessibilityId), weakSliderPattern_(weakSliderPattern)
    {}

    ~SliderAccessibilitySAObserverCallback() override = default;

    bool OnState(bool state) override
    {
        auto sliderPattern = weakSliderPattern_.Upgrade();
        CHECK_NULL_RETURN(sliderPattern, false);
        if (state) {
            sliderPattern->InitAccessibilityVirtualNodeTask();
        }
        return true;
    }
private:
    WeakPtr<SliderPattern> weakSliderPattern_;
};

void SliderPattern::InitSliderAccessibilityEnabledRegister()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextRefPtr();
    CHECK_NULL_VOID(pipeline);
    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilitySAObserverCallback_ = std::make_shared<SliderAccessibilitySAObserverCallback>(
        WeakClaim(this), host->GetAccessibilityId());
    accessibilityManager->RegisterAccessibilitySAObserverCallback(host->GetAccessibilityId(),
        accessibilitySAObserverCallback_);
}

void SliderPattern::InitAccessibilityVirtualNodeTask()
{
    if (!isInitAccessibilityVirtualNode_ && CheckCreateAccessibilityVirtualNode()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask(
            [weak = WeakClaim(this)]() {
                auto sliderPattern = weak.Upgrade();
                CHECK_NULL_VOID(sliderPattern);
                sliderPattern->isInitAccessibilityVirtualNode_ = sliderPattern->InitAccessibilityVirtualNode();
            });
    }
}

void SliderPattern::HandleAccessibilityHoverEvent(bool isHover, const AccessibilityHoverInfo& info)
{
    auto accessibilityHoverAction = info.GetActionType();
    if (isHover && (accessibilityHoverAction == AccessibilityHoverAction::HOVER_ENTER ||
                       accessibilityHoverAction == AccessibilityHoverAction::HOVER_MOVE)) {
        for (const auto& pointNode : pointAccessibilityNodeVec_) {
            pointNode->GetAccessibilityProperty<AccessibilityProperty>()->SetAccessibilityLevel(
                AccessibilityProperty::Level::YES_STR);
        }
    } else if (!isHover) {
        auto host = GetHost();
        auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
        accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);
    }
}

void SliderPattern::AccessibilityVirtualNodeRenderTask()
{
    if (isInitAccessibilityVirtualNode_ && CheckCreateAccessibilityVirtualNode()) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto pipeline = host->GetContextRefPtr();
        CHECK_NULL_VOID(pipeline);
        pipeline->AddAfterRenderTask([weak = WeakClaim(this)]() {
            auto sliderPattern = weak.Upgrade();
            CHECK_NULL_VOID(sliderPattern);
            sliderPattern->ModifyAccessibilityVirtualNode();
        });
    }
}

bool SliderPattern::CheckCreateAccessibilityVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    bool isShowSteps = sliderPaintProperty->GetShowStepsValue(false);
    if (!AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || UseContentModifier() || !isShowSteps) {
        return false;
    }
    return true;
}

bool SliderPattern::InitAccessibilityVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    parentAccessibilityNode_ = FrameNode::CreateFrameNode(V2::ROW_ETS_TAG,
        ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<LinearLayoutPattern>(true));
    CHECK_NULL_RETURN(parentAccessibilityNode_, false);
    auto parentNodeContext = parentAccessibilityNode_->GetRenderContext();
    CHECK_NULL_RETURN(parentNodeContext, false);
    parentNodeContext->UpdatePosition(OffsetT(Dimension(0.0f), Dimension(0.0f)));
    AddStepPointsAccessibilityVirtualNode();
    UpdateStepAccessibilityVirtualNode();
    UpdateParentNodeSize();
    parentAccessibilityNode_->SetAccessibilityNodeVirtual();
    parentAccessibilityNode_->SetAccessibilityVirtualNodeParent(AceType::DynamicCast<NG::UINode>(host));
    parentAccessibilityNode_->SetFirstAccessibilityVirtualNode();

    FrameNode::ProcessOffscreenNode(parentAccessibilityNode_);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SaveAccessibilityVirtualNode(parentAccessibilityNode_);
    accessibilityProperty->SetAccessibilityText(" ");
    ModifyAccessibilityVirtualNode();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    return true;
}

void SliderPattern::UpdateParentNodeSize()
{
    auto pointCount = pointAccessibilityNodeEventVec_.size();
    if (pointCount > 0) {
        auto pointSize = GetStepPointAccessibilityVirtualNodeSize();
        auto rowWidth = pointSize.Width();
        auto rowHeight = pointSize.Height();
        if (direction_ == Axis::HORIZONTAL) {
            rowWidth = rowWidth * pointCount;
        } else {
            rowHeight = rowHeight * pointCount;
        }
        CHECK_NULL_VOID(parentAccessibilityNode_);
        auto rowProperty = parentAccessibilityNode_->GetLayoutProperty<LinearLayoutProperty>();
        CHECK_NULL_VOID(rowProperty);
        rowProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(rowWidth), CalcLength(rowHeight)));
    }
}

void SliderPattern::ModifyAccessibilityVirtualNode()
{
    if (pointAccessibilityNodeVec_.empty()) {
        return;
    }
    UpdateStepPointsAccessibilityVirtualNodeSelected();
    auto host = GetHost();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SliderPattern::AddStepPointsAccessibilityVirtualNode()
{
    CHECK_NULL_VOID(parentAccessibilityNode_);
    CHECK_NULL_VOID(sliderContentModifier_);
    parentAccessibilityNode_->GetRenderContext()->ClearChildren();
    pointAccessibilityNodeVec_.clear();
    pointAccessibilityNodeEventVec_.clear();
    for (uint32_t i = 0; i < sliderContentModifier_->GetStepPointVec().size(); i++) {
        auto pointNode = FrameNode::CreateFrameNode(
            V2::TEXT_ETS_TAG, ElementRegister::GetInstance()->MakeUniqueId(), AceType::MakeRefPtr<TextPattern>());
        parentAccessibilityNode_->AddChild(pointNode);
        pointAccessibilityNodeVec_.emplace_back(pointNode);
        pointAccessibilityNodeEventVec_.emplace_back(nullptr);
    }
}

void SliderPattern::UpdateStepAccessibilityVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(parentAccessibilityNode_);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    if (pointAccessibilityNodeVec_.empty() || NearZero(step)) {
        return;
    }
    auto pointSize = GetStepPointAccessibilityVirtualNodeSize();
    auto pointOffsetWidth = pointSize.Width() * HALF;
    auto pointOffsetHeight = pointSize.Height() * HALF;
    uint32_t pointCount = pointAccessibilityNodeVec_.size();
    auto min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    auto max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    const std::vector<PointF>& stepPointVec = sliderContentModifier_->GetStepPointVec();
    if (pointCount != stepPointVec.size()) {
        return;
    }
    for (uint32_t i = 0; i < pointCount; i++) {
        std::string txt = GetPointAccessibilityTxt(i, step, min, max);
        SetStepPointAccessibilityVirtualNode(pointAccessibilityNodeVec_[i], pointSize,
            PointF(stepPointVec[i].GetX() - pointOffsetWidth, stepPointVec[i].GetY() - pointOffsetHeight), txt);
    }
    parentAccessibilityNode_->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

std::string SliderPattern::GetPointAccessibilityTxt(uint32_t pointIndex, float step, float min, float max)
{
    auto pointValue = min + pointIndex * step;
    pointValue = std::round(std::clamp(pointValue, min, max) * 100.0f);
    std::string str = std::to_string(pointValue / 100.0f);
    size_t pos = str.find('.');
    if (pos != std::string::npos) {
        str.erase(str.find_last_not_of('0') + 1);
        if (str.back() == '.') {
            str.pop_back();
        }
    }
    return str;
}

void SliderPattern::SetStepPointAccessibilityVirtualNode(
    const RefPtr<FrameNode>& pointNode, const SizeF& size, const PointF& point, const std::string& txt)
{
    CHECK_NULL_VOID(pointNode);
    auto pointNodeProperty = pointNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(pointNodeProperty);
    pointNodeProperty->UpdateUserDefinedIdealSize(CalcSize(CalcLength(size.Width()), CalcLength(size.Height())));
    pointNodeProperty->UpdateContent(txt);
    auto pointNodeContext = pointNode->GetRenderContext();
    CHECK_NULL_VOID(pointNodeContext);
    pointNodeContext->UpdatePosition(OffsetT(Dimension(point.GetX()), Dimension(point.GetY())));
    auto pointAccessibilityProperty = pointNode->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(pointAccessibilityProperty);
    pointAccessibilityProperty->SetAccessibilityText(txt);

    pointAccessibilityProperty->SetOnAccessibilityFocusCallback([weak = WeakClaim(this)](bool focus) {
        if (focus) {
            auto slider = weak.Upgrade();
            CHECK_NULL_VOID(slider);
            slider->HandleTextOnAccessibilityFocusCallback();
        }
    });
}

void SliderPattern::HandleTextOnAccessibilityFocusCallback()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    accessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::NO_STR);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::UpdateStepPointsAccessibilityVirtualNodeSelected()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    CHECK_NULL_VOID(parentAccessibilityNode_);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    uint32_t pointCount = pointAccessibilityNodeVec_.size();
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    if (pointAccessibilityNodeVec_.empty() || NearZero(step)) {
        return;
    }
    uint32_t rangeFromPointIndex = 0;
    uint32_t rangeToPointIndex = pointCount;
    uint32_t currentStepIndex = GetCurrentStepIndex();
    auto reverse = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>());
    if (sliderPaintProperty->GetValidSlideRange().has_value()) {
        auto range = sliderPaintProperty->GetValidSlideRange().value();
        rangeFromPointIndex = range->GetFromValue() / step;
        rangeToPointIndex = range->GetToValue() / step;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto selectedTxt = theme->GetSelectedTxt();
    auto unSelectedTxt = theme->GetUnselectedTxt();
    auto unSelectedDesc = theme->GetUnselectedDesc();
    auto disabledDesc = theme->GetDisabelDesc();
    for (uint32_t i = 0; i < pointCount; i++) {
        RefPtr<FrameNode>& pointNode = pointAccessibilityNodeVec_[i];
        auto pointAccessibilityProperty = pointNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        pointAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);

        auto pointNodeProperty = pointNode->GetLayoutProperty<TextLayoutProperty>();
        CHECK_NULL_VOID(pointNodeProperty);
        auto valueTxt = UtfUtils::Str16ToStr8(pointNodeProperty->GetContent().value_or(u""));
        if (currentStepIndex == i) {
            pointAccessibilityProperty->SetAccessibilityText(selectedTxt + valueTxt);
            pointAccessibilityProperty->SetAccessibilityDescription(" ");
            SetStepPointsAccessibilityVirtualNodeEvent(pointNode, i, false, reverse);
        } else if (i >= rangeFromPointIndex && i <= rangeToPointIndex) {
            pointAccessibilityProperty->SetAccessibilityText(unSelectedTxt + valueTxt);
            pointAccessibilityProperty->SetAccessibilityDescription(unSelectedDesc);
            SetStepPointsAccessibilityVirtualNodeEvent(pointNode, i, true, reverse);
        } else {
            pointAccessibilityProperty->SetAccessibilityText(unSelectedTxt + valueTxt);
            pointAccessibilityProperty->SetAccessibilityDescription(disabledDesc);
        }
    }
}

void SliderPattern::SetStepPointsAccessibilityVirtualNodeEvent(
    const RefPtr<FrameNode>& pointNode, uint32_t index, bool isClickAbled, bool reverse)
{
    CHECK_NULL_VOID(pointNode);
    auto gestureHub = pointNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (isClickAbled && !pointAccessibilityNodeEventVec_[index]) {
        auto clickHandle = [weak = WeakClaim(this), index, reverse](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireChangeEvent(SliderChangeMode::Begin);
            auto offsetStep = index - pattern->GetCurrentStepIndex();
            pattern->MoveStep(reverse ? -offsetStep : offsetStep);
            pattern->FireChangeEvent(SliderChangeMode::End);
            if (pattern->showTips_) {
                pattern->bubbleFlag_ = true;
                pattern->InitializeBubble();
            }
            pattern->PaintFocusState();
        };
        gestureHub->SetUserOnClick(clickHandle);
        pointAccessibilityNodeEventVec_[index] = clickHandle;
    } else if (!isClickAbled && pointAccessibilityNodeEventVec_[index]) {
        gestureHub->ClearUserOnClick();
        pointAccessibilityNodeEventVec_[index] = nullptr;
    }
}

uint32_t SliderPattern::GetCurrentStepIndex()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    const float step = sliderPaintProperty->GetStep().value_or(1.0f);
    const float currentValue = sliderPaintProperty->GetValueValue(value_);
    const double min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    if (NearZero(step)) {
        return 0;
    }
    return static_cast<uint32_t>(std::round((currentValue - min) / step));
}

SizeF SliderPattern::GetStepPointAccessibilityVirtualNodeSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, SizeF());
    auto pointCount = pointAccessibilityNodeEventVec_.size();
    if (pointCount <= 1) {
        return SizeF();
    }
    float pointNodeHeight = sliderLength_ / (pointCount - 1);
    float pointNodeWidth = pointNodeHeight;
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_RETURN(geometryNode, SizeF());
    auto& hostContent = geometryNode->GetContent();
    CHECK_NULL_RETURN(hostContent, SizeF());
    if (direction_ == Axis::HORIZONTAL) {
        pointNodeHeight = hostContent->GetRect().Height();
    } else {
        pointNodeWidth = hostContent->GetRect().Width();
    }
    return SizeF(pointNodeWidth, pointNodeHeight);
}

void SliderPattern::CalcSliderValue()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    value_ = sliderPaintProperty->GetValue().value_or(min);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    CancelExceptionValue(min, max, step);
    valueRatio_ = (value_ - min) / (max - min);
}

void SliderPattern::CancelExceptionValue(float& min, float& max, float& step)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    if (GreatOrEqual(min, max)) {
        min = SLIDER_MIN;
        max = SLIDER_MAX;
        sliderPaintProperty->UpdateMin(min);
        sliderPaintProperty->UpdateMax(max);
    }
    if (LessOrEqual(step, 0.0) || step > max - min) {
        step = 1;
        sliderPaintProperty->UpdateStep(step);
    }
    if (value_ < min || value_ > max) {
        value_ = std::clamp(value_, min, max);
        sliderPaintProperty->UpdateValue(value_);
        auto context = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(context);
        context->AddAfterRenderTask([weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireChangeEvent(SliderChangeMode::End);
        });
    }
}

bool SliderPattern::OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, bool skipMeasure, bool /*skipLayout*/)
{
    if (skipMeasure || dirty->SkipMeasureContent()) {
        return false;
    }

    auto layoutAlgorithmWrapper = DynamicCast<LayoutAlgorithmWrapper>(dirty->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(layoutAlgorithmWrapper, false);
    auto sliderLayoutAlgorithm = DynamicCast<SliderLayoutAlgorithm>(layoutAlgorithmWrapper->GetLayoutAlgorithm());
    CHECK_NULL_RETURN(sliderLayoutAlgorithm, false);
    trackThickness_ = sliderLayoutAlgorithm->GetTrackThickness();
    blockSize_ = sliderLayoutAlgorithm->GetBlockSize();
    blockHotSize_ = sliderLayoutAlgorithm->GetBlockHotSize();
    return UpdateParameters();
}

bool SliderPattern::UpdateParameters()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, false);
    std::optional<SizeF> contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize.has_value(), false);
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? contentSize.value().Width()
                       : contentSize.value().Height();

    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, false);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, false);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    Dimension hotBlockShadowWidth = sliderMode == SliderModel::SliderMode::OUTSET
                                        ? theme->GetOutsetHotBlockShadowWidth()
                                        : theme->GetInsetHotBlockShadowWidth();

    auto direction = sliderLayoutProperty->GetDirectionValue(Axis::HORIZONTAL);
    auto blockLength = direction == Axis::HORIZONTAL ? blockSize_.Width() : blockSize_.Height();

    hotBlockShadowWidth_ = static_cast<float>(hotBlockShadowWidth.ConvertToPx());
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        borderBlank_ = std::max(trackThickness_, blockLength + hotBlockShadowWidth_ / HALF);
    } else if (sliderMode == SliderModel::SliderMode::INSET) {
        borderBlank_ = trackThickness_ + hotBlockShadowWidth_ / HALF;
    } else {
        borderBlank_ = 0;
    }
    // slider track length
    sliderLength_ = length >= borderBlank_ ? length - borderBlank_ : 1;
    borderBlank_ = (length - sliderLength_) * HALF;

    return true;
}

void SliderPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    if (type == WindowSizeChangeReason::ROTATION &&
        Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
        SetSkipGestureEvents();
    }
}

void SliderPattern::InitClickEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (clickListener_) {
        return;
    }
    auto clickCallback = [](const GestureEvent& info) {};
    clickListener_ = MakeRefPtr<ClickEvent>(std::move(clickCallback));
    gestureHub->AddClickEvent(clickListener_);
}

void SliderPattern::InitTouchEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (UseContentModifier()) {
        if (touchEvent_) {
            gestureHub->RemoveTouchEvent(touchEvent_);
            touchEvent_ = nullptr;
        }
        return;
    }
    if (touchEvent_) {
        return;
    }
    auto touchTask = [weak = WeakClaim(this)](const TouchEventInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleTouchEvent(info);
    };
    gestureHub->RemoveTouchEvent(touchEvent_);
    touchEvent_ = MakeRefPtr<TouchEventImpl>(std::move(touchTask));
    gestureHub->AddTouchEvent(touchEvent_);
}

bool SliderPattern::AtMousePanArea(const Offset& offsetInFrame)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, false);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, false);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    auto contentOffset = content->GetRect().GetOffset();
    auto offset = Offset(offsetInFrame.GetX() - contentOffset.GetX(), offsetInFrame.GetY() - contentOffset.GetY());
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, false);
    auto blockType = paintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT);
    if (sliderMode == SliderModel::SliderMode::NONE) {
        float sideHotSizeX = blockHotSize_.Width() * HALF;
        float sideHotSizeY = blockHotSize_.Height() * HALF;
        return !(circleCenter_.GetX() - sideHotSizeX > offset.GetX() ||
                 circleCenter_.GetY() - sideHotSizeY > offset.GetY() ||
                 circleCenter_.GetX() + sideHotSizeX < offset.GetX() ||
                 circleCenter_.GetY() + sideHotSizeY < offset.GetY());
    } else if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
        double distanceCircle = std::min(blockSize_.Width(), blockSize_.Height()) * HALF + hotBlockShadowWidth_;
        auto diffX = circleCenter_.GetX() - offset.GetX();
        auto diffY = circleCenter_.GetY() - offset.GetY();
        return diffX * diffX + diffY * diffY <= distanceCircle * distanceCircle;
    } else {
        float sideHotSizeX = blockSize_.Width() * HALF;
        float sideHotSizeY = blockSize_.Height() * HALF;
        return !(circleCenter_.GetX() - sideHotSizeX > offset.GetX() ||
                 circleCenter_.GetY() - sideHotSizeY > offset.GetY() ||
                 circleCenter_.GetX() + sideHotSizeX < offset.GetX() ||
                 circleCenter_.GetY() + sideHotSizeY < offset.GetY());
    }
}

bool SliderPattern::AtTouchPanArea(const Offset& offsetInFrame)
{
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, false);
    auto contentOffset = content->GetRect().GetOffset();
    auto offset = Offset(offsetInFrame.GetX() - contentOffset.GetX(), offsetInFrame.GetY() - contentOffset.GetY());
    float sideHotSizeX = blockHotSize_.Width() * HALF;
    float sideHotSizeY = blockHotSize_.Height() * HALF;
    return !(circleCenter_.GetX() - sideHotSizeX > offset.GetX() ||
        circleCenter_.GetY() - sideHotSizeY > offset.GetY() ||
        circleCenter_.GetX() + sideHotSizeX < offset.GetX() ||
        circleCenter_.GetY() + sideHotSizeY < offset.GetY());
}

bool SliderPattern::AtPanArea(const Offset& offset, const SourceType& sourceType)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, false);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    if (sliderPaintProperty->GetSliderInteractionModeValue(SliderModelNG::SliderInteraction::SLIDE_AND_CLICK) ==
        SliderModelNG::SliderInteraction::SLIDE_AND_CLICK &&
        (sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT) !=
        SliderModelNG::BlockStyleType::DEFAULT ||
        sliderMode == SliderModel::SliderMode::NONE)) {
        return false;
    }
    bool flag = false;
    switch (sourceType) {
        case SourceType::MOUSE:
            flag = AtMousePanArea(offset);
            break;
        case SourceType::TOUCH:
            flag = AtTouchPanArea(offset);
            break;
        case SourceType::NONE:
        default:
            break;
    }
    return flag;
}

void SliderPattern::HandleTouchEvent(const TouchEventInfo& info)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle touch event");
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    auto touchInfo = touchList.front();
    auto touchType = touchInfo.GetTouchType();
    if (touchType == TouchType::DOWN) {
        ResetSkipGestureEvents();
        if (fingerId_ != -1) {
            return;
        }
        fingerId_ = touchInfo.GetFingerId();
        HandleTouchDown(touchInfo.GetLocalLocation(), info.GetSourceDevice());
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        ResetSkipGestureEvents();
        if (fingerId_ != touchInfo.GetFingerId()) {
            return;
        }
        HandleTouchUp(touchInfo.GetLocalLocation(), info.GetSourceDevice());
        fingerId_ = -1;
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandleTouchDown(const Offset& location, SourceType sourceType)
{
    axisFlag_ = false;
    if (sliderInteractionMode_ == SliderModelNG::SliderInteraction::SLIDE_AND_CLICK) {
        allowDragEvents_ = true;
        if (!AtPanArea(location, sourceType)) {
            UpdateValueByLocalLocation(location);
        }
    } else if (sliderInteractionMode_ == SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP) {
        lastTouchLocation_ = location;
    }
    if (showTips_) {
        bubbleFlag_ = true;
        UpdateBubble();
    }
    mousePressedFlag_ = true;
    FireChangeEvent(SliderChangeMode::Begin);
    OpenTranslateAnimation(SliderStatus::CLICK);
}

void SliderPattern::HandleTouchUp(const Offset& location, SourceType sourceType)
{
    if (sliderInteractionMode_ == SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP &&
        lastTouchLocation_.has_value() && lastTouchLocation_.value() == location) {
        allowDragEvents_ = true;
        if (!AtPanArea(location, sourceType)) {
            UpdateValueByLocalLocation(location);
        }
        UpdateToValidValue();
        FireChangeEvent(SliderChangeMode::Click);
    } else {
        UpdateToValidValue();
    }
    if (bubbleFlag_ && !isFocusActive_) {
        bubbleFlag_ = false;
    }
    mousePressedFlag_ = false;
    if (sliderInteractionMode_ != SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP) {
        FireChangeEvent(SliderChangeMode::Click);
    }
    isTouchUpFlag_ = true;
    FireChangeEvent(SliderChangeMode::End);
    CloseTranslateAnimation();
}

void SliderPattern::InitializeBubble()
{
    CHECK_NULL_VOID(showTips_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto sliderTheme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(sliderTheme);
    valueRatio_ = std::clamp(valueRatio_, 0.0f, 1.0f);
    std::string content = std::to_string(static_cast<int>(std::round(valueRatio_ * 100.0f))) + '%';
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    sliderPaintProperty->UpdatePadding(sliderTheme->GetTipTextPadding());
    sliderPaintProperty->UpdateTipColor(sliderTheme->GetTipColor());
    sliderPaintProperty->UpdateTextColor(sliderTheme->GetTipTextColor());
    sliderPaintProperty->UpdateFontSize(sliderTheme->GetTipFontSize());
    sliderPaintProperty->UpdateContent(content);
}

void SliderPattern::HandlingGestureStart(const GestureEvent& info)
{
    eventSourceDevice_ = info.GetSourceDevice();
    eventLocalLocation_ = info.GetLocalLocation();
    allowDragEvents_ = (sliderInteractionMode_ != SliderModelNG::SliderInteraction::SLIDE_ONLY ||
                        AtPanArea(eventLocalLocation_, eventSourceDevice_));
    if (info.GetInputEventType() != InputEventType::AXIS) {
        minResponseStartValue_ = value_;
        isMinResponseExceedFlag_ = false;
        if (allowDragEvents_ && isMinResponseExceed(eventLocalLocation_)) {
            UpdateValueByLocalLocation(eventLocalLocation_);
            UpdateBubble();
        }
    }
    panMoveFlag_ = allowDragEvents_;
    if (panMoveFlag_) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->OnAccessibilityEvent(AccessibilityEventType::REQUEST_FOCUS);
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandlingGestureEvent(const GestureEvent& info)
{
    if (info.GetInputEventType() == InputEventType::AXIS) {
        auto reverse = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>());
        if (info.GetSourceTool() == SourceTool::MOUSE) {
            auto offset = NearZero(info.GetOffsetX()) ? info.GetOffsetY() : info.GetOffsetX();
            if (direction_ == Axis::HORIZONTAL) {
                offset > 0.0 ? MoveStep(1) : MoveStep(-1);
            } else {
                reverse ? (offset > 0.0 ? MoveStep(1) : MoveStep(-1)) : (offset > 0.0 ? MoveStep(-1) : MoveStep(1));
            }
        } else {
            auto offset = (direction_ == Axis::HORIZONTAL ? info.GetOffsetX() : info.GetOffsetY()) - axisOffset_;
            auto slipfactor = slipfactor_ > 0 ? slipfactor_ : DEFAULT_SLIP_FACTOR;
            if (std::abs(offset) > slipfactor) {
                auto stepCount = static_cast<int32_t>(offset / slipfactor);
                MoveStep(reverse ? -stepCount : stepCount);
                axisOffset_ += slipfactor * stepCount;
            }
        }
        if (hotFlag_) {
            axisFlag_ = true;
        }
        if (showTips_ && axisFlag_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
    } else {
        auto fingerList = info.GetFingerList();
        panMoveFlag_ = false;
        if (fingerList.size() > 0) {
            for (auto fingerInfo : fingerList) {
                if (fingerInfo.fingerId_ == fingerId_) {
                    if (allowDragEvents_ && isMinResponseExceed(fingerInfo.localLocation_)) {
                        UpdateValueByLocalLocation(fingerInfo.localLocation_);
                        UpdateBubble();
                        panMoveFlag_ = true;
                        UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
                    }
                }
            }
        } else {
            if (allowDragEvents_ && isMinResponseExceed(info.GetLocalLocation())) {
                UpdateValueByLocalLocation(info.GetLocalLocation());
                UpdateBubble();
                panMoveFlag_ = true;
                UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
            }
        }
    }
}

void SliderPattern::HandledGestureEvent()
{
    panMoveFlag_ = false;
    axisOffset_ = 0.0;
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

OffsetF SliderPattern::CalculateGlobalSafeOffset()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, OffsetF());
    auto overlayGlobalOffset = host->GetPaintRectOffset();
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, OffsetF());
    auto safeAreaManger = pipelineContext->GetSafeAreaManager();
    CHECK_NULL_RETURN(safeAreaManger, OffsetF());
    auto top = safeAreaManger->GetSystemSafeArea().top_.Length();
    overlayGlobalOffset.SetY(overlayGlobalOffset.GetY() - top);
    auto windowWrapperOffset = safeAreaManger->GetWindowWrapperOffset();
    overlayGlobalOffset -= windowWrapperOffset;
    return overlayGlobalOffset;
}

bool SliderPattern::isMinResponseExceed(const std::optional<Offset>& localLocation)
{
    if (isMinResponseExceedFlag_) {
        return true;
    }
    if (LessOrEqual(minResponse_, 0.0f)) {
        isMinResponseExceedFlag_ = true;
        return true;
    }
    CHECK_NULL_RETURN(allowDragEvents_, false);
    CHECK_NULL_RETURN(localLocation.has_value(), false);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, false);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, false);
    auto contentOffset = content->GetRect().GetOffset();
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? static_cast<float>(localLocation->GetX() - contentOffset.GetX())
                       : static_cast<float>(localLocation->GetY() - contentOffset.GetY());
    float touchLength =
        GetReverseValue(sliderLayoutProperty) ? borderBlank_ + sliderLength_ - length : length - borderBlank_;
    float min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    float max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    CHECK_NULL_RETURN(GreatNotEqual(sliderLength_, 0.0f), false);
    float valueRatio = touchLength / sliderLength_;
    float value = valueRatio * (max - min) + min;
    if (GreatOrEqual(std::abs(minResponseStartValue_ - value), minResponse_)) {
        isMinResponseExceedFlag_ = true;
        return true;
    }
    return false;
}

void SliderPattern::UpdateValueByLocalLocation(const std::optional<Offset>& localLocation)
{
    CHECK_NULL_VOID(localLocation.has_value());
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    const auto& content = host->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    float length = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL
                       ? static_cast<float>(localLocation->GetX() - contentOffset.GetX())
                       : static_cast<float>(localLocation->GetY() - contentOffset.GetY());
    float touchLength =
        GetReverseValue(sliderLayoutProperty) ? borderBlank_ + sliderLength_ - length : length - borderBlank_;
    float min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    float max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    touchLength = std::clamp(touchLength, 0.0f, sliderLength_);
    CHECK_NULL_VOID(sliderLength_ != 0);
    valueRatio_ = touchLength / sliderLength_;
    auto stepRatio = sliderPaintProperty->GetStepRatio();
    CHECK_NULL_VOID(stepRatio != 0);
    valueRatio_ = NearEqual(valueRatio_, 1) ? 1 : std::round(valueRatio_ / stepRatio) * stepRatio;

    float oldValue = value_;
    value_ = NearEqual(valueRatio_, 1) ? max : (std::round(valueRatio_ / stepRatio) * step + min);
    value_ = std::clamp(value_, min, max);
    sliderPaintProperty->UpdateValue(value_);
    valueChangeFlag_ = !NearEqual(oldValue, value_);
    UpdateCircleCenterOffset();
}

void SliderPattern::UpdateToValidValue()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);

    float min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    float max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    float oldValue = value_;
    auto value = sliderPaintProperty->GetValueValue(value_);
    value_ = GetValueInValidRange(sliderPaintProperty, value, min, max);
    valueRatio_ = (value_ - min) / (max - min);
    sliderPaintProperty->UpdateValue(value_);
    valueChangeFlag_ = !NearEqual(oldValue, value_);
    UpdateCircleCenterOffset();
    UpdateBubble();
}

float SliderPattern::GetValueInValidRange(
    const RefPtr<SliderPaintProperty>& paintProperty, float value, float min, float max)
{
    CHECK_NULL_RETURN(paintProperty, value);
    if (paintProperty->GetValidSlideRange().has_value()) {
        auto range = paintProperty->GetValidSlideRange().value();
        if (range->HasValidValues()) {
            auto fromValue = range->GetFromValue();
            auto toValue = range->GetToValue();
            float step = paintProperty->GetStepRatio() * (max - min);
            if (NearEqual(step, 0.0f)) {
                step = 1.0f;
            }
            auto toValueCorrection = NearEqual(toValue - step * std::floor(toValue / step), 0) ? 0 : 1;
            fromValue = LessOrEqual(fromValue, min) ? min : std::floor(fromValue / step) * step;
            toValue = GreatOrEqual(toValue, max) ? max : (std::floor(toValue / step) + toValueCorrection) * step;
            return LessNotEqual(value, fromValue) ? fromValue : GreatNotEqual(value, toValue) ? toValue : value;
        }
    }
    return value;
}

void SliderPattern::UpdateTipsValue()
{
    CHECK_NULL_VOID(valueChangeFlag_);
    CHECK_NULL_VOID(showTips_);
    CHECK_NULL_VOID(bubbleFlag_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    valueRatio_ = std::clamp(valueRatio_, 0.0f, 1.0f);
    std::string content = std::to_string(static_cast<int>(std::round(valueRatio_ * 100.0f))) + '%';
    frameNode->GetPaintProperty<SliderPaintProperty>()->UpdateContent(content);
}

void SliderPattern::UpdateCircleCenterOffset()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto contentSize = GetHostContentSize();
    CHECK_NULL_VOID(contentSize.has_value());
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto touchLength = valueRatio_ * sliderLength_;
    auto touchOffset = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>())
                           ? sliderLength_ - touchLength + borderBlank_
                           : touchLength + borderBlank_;
    if (sliderPaintProperty->GetDirection().value_or(Axis::HORIZONTAL) == Axis::HORIZONTAL) {
        circleCenter_.SetX(touchOffset);
        circleCenter_.SetY(contentSize->Height() * HALF);
    } else {
        circleCenter_.SetX(contentSize->Width() * HALF);
        circleCenter_.SetY(touchOffset);
    }
}

void SliderPattern::UpdateBubble()
{
    CHECK_NULL_VOID(bubbleFlag_);
    // update the tip value according to the slider value, update the tip position according to current block position
    UpdateTipsValue();
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::InitPanEvent(const RefPtr<GestureEventHub>& gestureHub)
{
    if (UseContentModifier()) {
        if (panEvent_) {
            gestureHub->RemovePanEvent(panEvent_);
            panEvent_ = nullptr;
        }
        return;
    }
    if (direction_ == GetDirection() && panEvent_) return;
    direction_ = GetDirection();
   
    if (panEvent_) {
        gestureHub->RemovePanEvent(panEvent_);
    }
    panEvent_ = CreatePanEvent();

    PanDirection panDirection;
    panDirection.type = direction_ == Axis::HORIZONTAL ? PanDirection::HORIZONTAL : PanDirection::VERTICAL;
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    gestureHub->AddPanEvent(panEvent_, panDirection, 1,
        pipeline->IsFormRender() ? FORM_PAN_DISTANCE : DEFAULT_PAN_DISTANCE, pipeline->IsFormRender());
}

RefPtr<PanEvent> SliderPattern::CreatePanEvent()
{
    auto actionStartTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle action start");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandlingGestureStart(info);
        if (info.GetInputEventType() == InputEventType::AXIS) {
            pattern->FireChangeEvent(SliderChangeMode::Begin);
        }
        pattern->OpenTranslateAnimation(SliderStatus::MOVE);
    };
    auto actionUpdateTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle action update");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        if (!pattern->IsSkipGestureEvents()) {
            pattern->HandlingGestureEvent(info);
            pattern->FireChangeEvent(SliderChangeMode::Moving);
            pattern->OpenTranslateAnimation(SliderStatus::MOVE);
        }
    };
    auto actionEndTask = [weak = WeakClaim(this)](const GestureEvent& info) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle action end");
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandledGestureEvent();
        if (info.GetInputEventType() == InputEventType::AXIS) {
            pattern->FireChangeEvent(SliderChangeMode::End);
        }
        pattern->CloseTranslateAnimation();
    };
    auto actionCancelTask = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandledGestureEvent();
        pattern->FireChangeEvent(SliderChangeMode::End);
        pattern->axisFlag_ = false;
        pattern->CloseTranslateAnimation();
    };
    return MakeRefPtr<PanEvent>(
        std::move(actionStartTask), std::move(actionUpdateTask), std::move(actionEndTask), std::move(actionCancelTask));
}

void SliderPattern::InitOnKeyEvent(const RefPtr<FocusHub>& focusHub)
{
    if (UseContentModifier()) {
        focusHub->SetInnerFocusPaintRectCallback(nullptr);
        focusHub->SetOnKeyEventInternal(nullptr);
        focusHub->SetOnFocusInternal(nullptr);
        focusHub->SetOnBlurInternal(nullptr);
        return;
    }
    auto getInnerPaintRectCallback = [wp = WeakClaim(this)](RoundRect& paintRect) {
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->GetInnerFocusPaintRect(paintRect);
    };
    focusHub->SetInnerFocusPaintRectCallback(getInnerPaintRectCallback);

    auto onKeyEvent = [wp = WeakClaim(this)](const KeyEvent& event) -> bool {
        auto pattern = wp.Upgrade();
        CHECK_NULL_RETURN(pattern, false);
        return pattern->OnKeyEvent(event);
    };
    focusHub->SetOnKeyEventInternal(std::move(onKeyEvent));

    auto onFocus = [wp = WeakClaim(this)]() {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider on focus");
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->focusFlag_ = true;
        pattern->UpdateTipState();
        pattern->UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
        pattern->AddIsFocusActiveUpdateEvent();
    };
    focusHub->SetOnFocusInternal(std::move(onFocus));

    auto onBlur = [wp = WeakClaim(this)]() {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider on blur");
        auto pattern = wp.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->focusFlag_ = false;
        pattern->UpdateTipState();
        pattern->UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
        pattern->RemoveIsFocusActiveUpdateEvent();
    };
    focusHub->SetOnBlurInternal(std::move(onBlur));
}

void SliderPattern::GetInnerFocusPaintRect(RoundRect& paintRect)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        GetOutsetInnerFocusPaintRect(paintRect);
    } else {
        GetInsetAndNoneInnerFocusPaintRect(paintRect);
    }
}

void SliderPattern::GetOutsetInnerFocusPaintRect(RoundRect& paintRect)
{
    UpdateCircleCenterOffset();
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto contentOffset = content->GetRect().GetOffset();
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    auto halfWidth = blockSize_.Width() * HALF + static_cast<float>(focusDistance.ConvertToPx());
    auto halfHeight = blockSize_.Height() * HALF + static_cast<float>(focusDistance.ConvertToPx());
    paintRect.SetRect(RectF(circleCenter_.GetX() - halfWidth + contentOffset.GetX(),
        circleCenter_.GetY() - halfHeight + contentOffset.GetY(), halfWidth / HALF, halfHeight / HALF));
    paintRect.SetCornerRadius(focusDistance.ConvertToPx());
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto blockType = paintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT);
    if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
        auto focusRadius =
            std::min(blockSize_.Width(), blockSize_.Height()) * HALF + static_cast<float>(focusDistance.ConvertToPx());
        paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
            circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
        paintRect.SetCornerRadius(focusRadius);
    } else if (blockType == SliderModelNG::BlockStyleType::SHAPE) {
        auto shape = paintProperty->GetBlockShape();
        if (shape.has_value() && shape.value()->GetBasicShapeType() == BasicShapeType::CIRCLE) {
            auto circle = DynamicCast<Circle>(shape.value());
            CHECK_NULL_VOID(circle);
            float focusRadius;
            if (circle->GetRadius().IsValid()) {
                focusRadius = circle->GetRadius().ConvertToPx() + focusDistance.ConvertToPx();
            } else {
                focusRadius = std::min(circle->GetWidth().ConvertToPx(), circle->GetHeight().ConvertToPx()) * HALF +
                              focusDistance.ConvertToPx();
            }
            paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
                circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
            paintRect.SetCornerRadius(focusRadius);
        }
    }
}

void SliderPattern::GetInsetAndNoneInnerFocusPaintRect(RoundRect& paintRect)
{
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    const auto& content = frameNode->GetGeometryNode()->GetContent();
    CHECK_NULL_VOID(content);
    auto theme = PipelineBase::GetCurrentContext()->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto sliderLayoutProperty = frameNode->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    // use content area
    float offsetX = content->GetRect().GetX();
    float offsetY = content->GetRect().GetY();
    float width = content->GetRect().Width();
    float height = content->GetRect().Height();
    float focusRadius = trackThickness_ * HALF + static_cast<float>(focusDistance.ConvertToPx());
    auto paintProperty = frameNode->GetPaintProperty<SliderPaintProperty>();
    if (paintProperty && paintProperty->GetTrackBorderRadius().has_value()) {
        focusRadius = static_cast<float>(paintProperty->GetTrackBorderRadius().value().ConvertToPx()) +
                      static_cast<float>(focusDistance.ConvertToPx());
    }
    if (direction_ == Axis::HORIZONTAL) {
        if (sliderMode == SliderModel::SliderMode::INSET) {
            offsetX += borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
            width = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        } else {
            offsetX -= static_cast<float>(focusDistance.ConvertToPx());
            width += static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        }
        offsetY += (height - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        height = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
    } else {
        offsetX += (width - trackThickness_) * HALF - static_cast<float>(focusDistance.ConvertToPx());
        width = trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        if (sliderMode == SliderModel::SliderMode::INSET) {
            offsetY += borderBlank_ - trackThickness_ * HALF - static_cast<float>(focusDistance.ConvertToPx());
            height = sliderLength_ + trackThickness_ + static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        } else {
            offsetY -= static_cast<float>(focusDistance.ConvertToPx());
            height += static_cast<float>(focusDistance.ConvertToPx()) / HALF;
        }
    }
    paintRect.SetRect(RectF(offsetX, offsetY, width, height));
    paintRect.SetCornerRadius(focusRadius);
}

void SliderPattern::PaintFocusState()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RoundRect focusRect;
    GetInnerFocusPaintRect(focusRect);

    auto focusHub = host->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->PaintInnerFocusState(focusRect);

    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

bool SliderPattern::OnKeyEvent(const KeyEvent& event)
{
    auto reverse = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>());
    if (event.action == KeyAction::DOWN) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider on key event %{public}d", event.code);
        if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_LEFT) ||
            (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_UP)) {
            FireChangeEvent(SliderChangeMode::Begin);
            reverse ? MoveStep(1) : MoveStep(-1);
            FireChangeEvent(SliderChangeMode::End);
            if (showTips_) {
                InitializeBubble();
            }
            PaintFocusState();
            return true;
        }
        if ((direction_ == Axis::HORIZONTAL && event.code == KeyCode::KEY_DPAD_RIGHT) ||
            (direction_ == Axis::VERTICAL && event.code == KeyCode::KEY_DPAD_DOWN)) {
            FireChangeEvent(SliderChangeMode::Begin);
            reverse ? MoveStep(-1) : MoveStep(1);
            FireChangeEvent(SliderChangeMode::End);
            if (showTips_) {
                InitializeBubble();
            }
            PaintFocusState();
            return true;
        }
    }
    return false;
}

bool SliderPattern::MoveStep(int32_t stepCount)
{
    // stepCount > 0, slider value increases, block moves in the direction of growth
    auto host = GetHost();
    CHECK_NULL_RETURN(host, false);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, false);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    float min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    float max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    if (NearZero(step)) {
        return false;
    }
    float nextValue = value_ + static_cast<float>(stepCount) * step;
    auto oldStep = (value_ - min) / step;
    if (!NearEqual(oldStep, std::round(oldStep))) {
        if (stepCount > 0) {
            nextValue = std::floor((nextValue - min) / step) * step + min;
        } else {
            nextValue = std::ceil((nextValue - min) / step) * step + min;
        }
    }
    auto validSlideRange = sliderPaintProperty->GetValidSlideRange();
    if (validSlideRange.has_value() && validSlideRange.value()->HasValidValues()) {
        nextValue =
            std::clamp(nextValue, validSlideRange.value()->GetFromValue(), validSlideRange.value()->GetToValue());
    } else {
        nextValue = std::clamp(nextValue, min, max);
    }
    if (NearEqual(nextValue, value_)) {
        return false;
    }
    value_ = nextValue;
    sliderPaintProperty->UpdateValue(value_);
    valueRatio_ = (value_ - min) / (max - min);
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    return true;
}

void SliderPattern::InitMouseEvent(const RefPtr<InputEventHub>& inputEventHub)
{
    if (UseContentModifier()) {
        if (hoverEvent_) {
            inputEventHub->RemoveOnHoverEvent(hoverEvent_);
            hoverEvent_ = nullptr;
        }
        if (mouseEvent_) {
            inputEventHub->RemoveOnMouseEvent(mouseEvent_);
            mouseEvent_ = nullptr;
        }
        return;
    }
    auto hoverEvent = [weak = WeakClaim(this)](bool isHover) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleHoverEvent(isHover);
    };
    if (hoverEvent_) {
        inputEventHub->RemoveOnHoverEvent(hoverEvent_);
    }
    hoverEvent_ = MakeRefPtr<InputEvent>(std::move(hoverEvent));
    inputEventHub->AddOnHoverEvent(hoverEvent_);

    auto mouseEvent = [weak = WeakClaim(this)](MouseInfo& info) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->HandleMouseEvent(info);
    };
    if (mouseEvent_) {
        inputEventHub->RemoveOnMouseEvent(mouseEvent_);
    }
    mouseEvent_ = MakeRefPtr<InputEvent>(std::move(mouseEvent));
    inputEventHub->AddOnMouseEvent(mouseEvent_);
}

void SliderPattern::HandleHoverEvent(bool isHover)
{
    hotFlag_ = isHover;
    mouseHoverFlag_ = mouseHoverFlag_ && isHover;
    if (!mouseHoverFlag_) {
        axisFlag_ = false;
    }
    if (!mouseHoverFlag_ && !axisFlag_ && !isFocusActive_ && !mousePressedFlag_) {
        bubbleFlag_ = false;
    }
    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::HandleMouseEvent(const MouseInfo& info)
{
    UpdateCircleCenterOffset();
    // MouseInfo's LocalLocation is relative to the frame area, circleCenter_ is relative to the content area
    mouseHoverFlag_ = AtMousePanArea(info.GetLocalLocation());
    if (mouseHoverFlag_) {
        if (showTips_) {
            bubbleFlag_ = true;
            InitializeBubble();
        }
    }
    // when mouse hovers over slider, distinguish between hover block and Wheel operation.
    if (!mouseHoverFlag_ && !axisFlag_ && !isFocusActive_ && !mousePressedFlag_) {
        bubbleFlag_ = false;
    }

    UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::FireChangeEvent(int32_t mode)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider fire change %{public}d %{public}f", mode, value_);
    auto sliderEventHub = GetEventHub<SliderEventHub>();
    CHECK_NULL_VOID(sliderEventHub);
    if ((mode == SliderChangeMode::Click || mode == SliderChangeMode::Moving) &&
        NearEqual(value_, sliderEventHub->GetValue())) {
        return;
    }
    sliderEventHub->FireChangeEvent(static_cast<float>(value_), mode);
    valueChangeFlag_ = false;
    SendAccessibilityValueEvent(mode);
}

void SliderPattern::SendAccessibilityValueEvent(int32_t mode)
{
    accessibilityValue_ = value_;
    auto currentTime = GetMilliseconds();
    if (currentTime - lastSendPostValueTime_ < SCREEN_READ_SENDEVENT_TIMESTAMP && !isTouchUpFlag_) {
        return;
    }
    isTouchUpFlag_ = false;
    lastSendPostValueTime_ = currentTime;
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto taskExecutor = pipeline->GetTaskExecutor();
    CHECK_NULL_VOID(taskExecutor);
    taskExecutor->PostDelayedTask(
        [weak = WeakClaim(this)]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            auto host = pattern->GetHost();
            CHECK_NULL_VOID(host);
            host->OnAccessibilityEvent(AccessibilityEventType::COMPONENT_CHANGE);
        },
        TaskExecutor::TaskType::UI, SCREEN_READ_SENDEVENT_TIMESTAMP, STR_SCREEN_READ_SENDEVENT);
}

void SliderPattern::UpdateMarkDirtyNode(const PropertyChangeFlag& Flag)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(Flag);
}

Axis SliderPattern::GetDirection() const
{
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, Axis::HORIZONTAL);
    return sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
}

RefPtr<AccessibilityProperty> SliderPattern::CreateAccessibilityProperty()
{
    return MakeRefPtr<SliderAccessibilityProperty>();
}

SliderContentModifier::Parameters SliderPattern::UpdateContentParameters()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, SliderContentModifier::Parameters());
    auto pipeline = GetContext();
    CHECK_NULL_RETURN(pipeline, SliderContentModifier::Parameters());
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_RETURN(theme, SliderContentModifier::Parameters());
    auto stepRatio = paintProperty->GetStepRatio();
    SliderContentModifier::Parameters parameters { trackThickness_, blockSize_, stepRatio, hotBlockShadowWidth_,
        mouseHoverFlag_, mousePressedFlag_ };
    auto contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize, SliderContentModifier::Parameters());
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, SliderContentModifier::Parameters());
    auto contentOffset = content->GetRect().GetOffset();
    // Distance between slide track and Content boundary
    auto centerWidth = direction_ == Axis::HORIZONTAL ? contentSize->Height() : contentSize->Width();
    centerWidth *= HALF;
    parameters.selectColor = paintProperty->GetSelectColor().value_or(theme->GetTrackSelectedColor());

    Gradient defaultValue = SliderModelNG::CreateSolidGradient(theme->GetTrackBgColor());
    parameters.trackBackgroundColor = paintProperty->GetTrackBackgroundColor().value_or(defaultValue);
    parameters.blockColor = paintProperty->GetBlockColor().value_or(theme->GetBlockColor());

    UpdateParameters();
    GetSelectPosition(parameters, centerWidth, contentOffset);
    GetBackgroundPosition(parameters, centerWidth, contentOffset);
    GetCirclePosition(parameters, centerWidth, contentOffset);
    UpdateCircleCenterOffset();
    return parameters;
}

void SliderPattern::GetSelectPosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    float sliderSelectLength = std::clamp(sliderLength_ * valueRatio_, 0.0f, sliderLength_);
    PointF start;
    PointF end;
    if (!GetReverseValue(GetLayoutProperty<SliderLayoutProperty>())) {
        start = direction_ == Axis::HORIZONTAL ? PointF(offset.GetX() + borderBlank_, offset.GetY() + centerWidth)
                                               : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_);
        end = direction_ == Axis::HORIZONTAL
                  ? PointF(offset.GetX() + borderBlank_ + sliderSelectLength, offset.GetY() + centerWidth)
                  : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderSelectLength);
    } else {
        start = direction_ == Axis::HORIZONTAL
                    ? PointF(offset.GetX() + borderBlank_ + sliderLength_, offset.GetY() + centerWidth)
                    : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_);
        end =
            direction_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + borderBlank_ + sliderLength_ - sliderSelectLength, offset.GetY() + centerWidth) :
                PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_ - sliderSelectLength);
    }
    parameters.selectStart = start;
    parameters.selectEnd = end;
}

void SliderPattern::GetBackgroundPosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    auto startPointX = offset.GetX();
    auto startPointY = offset.GetY();
    auto start = direction_ == Axis::HORIZONTAL ? PointF(startPointX + borderBlank_, startPointY + centerWidth)
                                                : PointF(startPointX + centerWidth, startPointY + borderBlank_);
    auto end = direction_ == Axis::HORIZONTAL
                   ? PointF(startPointX + borderBlank_ + sliderLength_, startPointY + centerWidth)
                   : PointF(startPointX + centerWidth, startPointY + borderBlank_ + sliderLength_);
    parameters.backStart = start;
    parameters.backEnd = end;
}

void SliderPattern::GetCirclePosition(
    SliderContentModifier::Parameters& parameters, float centerWidth, const OffsetF& offset)
{
    float sliderSelectLength = std::clamp(sliderLength_ * valueRatio_, 0.0f, sliderLength_);
    PointF center;
    if (!GetReverseValue(GetLayoutProperty<SliderLayoutProperty>())) {
        center = direction_ == Axis::HORIZONTAL
                     ? PointF(offset.GetX() + borderBlank_ + sliderSelectLength, offset.GetY() + centerWidth)
                     : PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderSelectLength);
    } else {
        center =
            direction_ == Axis::HORIZONTAL ?
                PointF(offset.GetX() + borderBlank_ + sliderLength_ - sliderSelectLength, offset.GetY() + centerWidth) :
                PointF(offset.GetX() + centerWidth, offset.GetY() + borderBlank_ + sliderLength_ - sliderSelectLength);
    }
    parameters.circleCenter = center;
}

void SliderPattern::UpdateBlock()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderMode = sliderLayoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
    if (sliderPaintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT) ==
        SliderModelNG::BlockStyleType::IMAGE && sliderMode != SliderModel::SliderMode::NONE) {
        if (imageFrameNode_ == nullptr) {
            auto imageId = ElementRegister::GetInstance()->MakeUniqueId();
            imageFrameNode_ =
                FrameNode::CreateFrameNode(V2::IMAGE_ETS_TAG, imageId, AceType::MakeRefPtr<ImagePattern>());
            imageFrameNode_->MountToParent(host);
        }
        if (imageFrameNode_ != nullptr) {
            auto imageLayoutProperty = DynamicCast<ImageLayoutProperty>(imageFrameNode_->GetLayoutProperty());
            CHECK_NULL_VOID(imageLayoutProperty);
            imageLayoutProperty->UpdateImageSourceInfo(ImageSourceInfo(sliderPaintProperty->GetBlockImageValue(""),
                sliderPaintProperty->GetBlockImageBundleNameValue(""),
                sliderPaintProperty->GetBlockImageModuleNameValue("")));
            imageLayoutProperty->UpdateImageFit(ImageFit::COVER);
            imageLayoutProperty->UpdateAutoResize(true);
            imageFrameNode_->MarkModifyDone();
        }
    } else {
        if (imageFrameNode_ != nullptr) {
            host->RemoveChild(imageFrameNode_);
            imageFrameNode_ = nullptr;
        }
    }
}

std::string SliderPattern::ProvideRestoreInfo()
{
    auto jsonObj = JsonUtil::Create(true);
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, "");
    jsonObj->Put("value", sliderPaintProperty->GetValue().value_or(0.0f));
    return jsonObj->ToString();
}

void SliderPattern::OnRestoreInfo(const std::string& restoreInfo)
{
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto info = JsonUtil::ParseJsonString(restoreInfo);
    if (!info->IsValid() || !info->IsObject()) {
        return;
    }
    auto jsonValue = info->GetValue("value");
    sliderPaintProperty->UpdateValue(jsonValue->GetDouble());
    OnModifyDone();
}

void SliderPattern::LayoutImageNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SliderPattern::UpdateImagePositionX(float centerX)
{
    CHECK_NULL_VOID(imageFrameNode_);
    auto renderContext = imageFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = imageFrameNode_->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto offset = geometryNode->GetMarginFrameOffset();
    offset.SetX(centerX - blockSize_.Width() * HALF);
    geometryNode->SetMarginFrameOffset(offset);
    renderContext->SavePaintRect();
    renderContext->SyncGeometryProperties(nullptr);
}

void SliderPattern::UpdateImagePositionY(float centerY)
{
    CHECK_NULL_VOID(imageFrameNode_);
    auto renderContext = imageFrameNode_->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    auto geometryNode = imageFrameNode_->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);

    auto offset = geometryNode->GetMarginFrameOffset();
    offset.SetY(centerY - blockSize_.Height() * HALF);
    geometryNode->SetMarginFrameOffset(offset);
    renderContext->SavePaintRect();
    renderContext->SyncGeometryProperties(nullptr);
}

void SliderPattern::OpenTranslateAnimation(SliderStatus status)
{
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetAnimatorStatus(status);
}

void SliderPattern::CloseTranslateAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetAnimatorStatus(SliderStatus::DEFAULT);
}

std::pair<OffsetF, float> SliderPattern::GetBubbleVertexPosition(
    const OffsetF& blockCenter, float trackThickness, const SizeF& blockSize)
{
    OffsetF bubbleVertex = blockCenter;
    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    float vertexOffsetFromBlock = 0;
    if (!sliderLayoutProperty) {
        return std::pair<OffsetF, float>();
    }
    auto sliderMode = sliderLayoutProperty->GetSliderModeValue(SliderModel::SliderMode::OUTSET);
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        if (direction_ == Axis::HORIZONTAL) {
            vertexOffsetFromBlock = blockSize.Height() * HALF + BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx();
            bubbleVertex.AddY(0 - vertexOffsetFromBlock);
        } else {
            vertexOffsetFromBlock = blockSize.Width() * HALF + BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx();
            bubbleVertex.AddX(0 - vertexOffsetFromBlock);
        }
    } else {
        vertexOffsetFromBlock = trackThickness * HALF + BUBBLE_TO_SLIDER_DISTANCE.ConvertToPx();
        if (direction_ == Axis::HORIZONTAL) {
            bubbleVertex.AddY(0 - vertexOffsetFromBlock);
        } else {
            bubbleVertex.AddX(0 - vertexOffsetFromBlock);
        }
    }
    return std::pair<OffsetF, float>(bubbleVertex, vertexOffsetFromBlock);
}

void SliderPattern::SetAccessibilityAction()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SetActionScrollForward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireChangeEvent(SliderChangeMode::Begin);
        pattern->MoveStep(1);
        pattern->FireChangeEvent(SliderChangeMode::End);

        if (pattern->showTips_) {
            pattern->bubbleFlag_ = true;
            pattern->InitializeBubble();
        }
        pattern->PaintFocusState();
    });

    accessibilityProperty->SetActionScrollBackward([weakPtr = WeakClaim(this)]() {
        const auto& pattern = weakPtr.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->FireChangeEvent(SliderChangeMode::Begin);
        pattern->MoveStep(-1);
        pattern->FireChangeEvent(SliderChangeMode::End);

        if (pattern->showTips_) {
            pattern->bubbleFlag_ = true;
            pattern->InitializeBubble();
        }
        pattern->PaintFocusState();
    });
}

void SliderPattern::SetSliderValue(double value, int32_t mode)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(eventHub);
    auto enabled = eventHub->IsEnabled();
    if (!enabled) {
        return;
    }
    UpdateValue(value);
    FireChangeEvent(mode);
    OnModifyDone();
}

void SliderPattern::UpdateValue(float value)
{
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider update value %{public}d %{public}f", panMoveFlag_, value_);
    if (!panMoveFlag_) {
        auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
        CHECK_NULL_VOID(sliderPaintProperty);
        sliderPaintProperty->UpdateValue(value);
    }
    CalcSliderValue();
    FireBuilder();
}

void SliderPattern::OnAttachToFrameNode()
{
    RegisterVisibleAreaChange();
}

void SliderPattern::StartAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    if (sliderContentModifier_->GetVisible()) {
        return;
    }
    if (IsSliderVisible()) {
        sliderContentModifier_->SetVisible(true);
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SliderPattern::StopAnimation()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    if (!sliderContentModifier_->GetVisible()) {
        return;
    }
    sliderContentModifier_->SetVisible(false);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
}

void SliderPattern::RegisterVisibleAreaChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }

    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->isVisibleArea_ = visible;
        visible ? pattern->StartAnimation() : pattern->StopAnimation();
    };
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    std::vector<double> ratioList = {0.0};
    pipeline->AddVisibleAreaChangeNode(host, ratioList, callback, false, true);
    pipeline->AddWindowStateChangedCallback(host->GetId());
    pipeline->AddWindowSizeChangeCallback(host->GetId());
    hasVisibleChangeRegistered_ = true;
    auto renderContext = host->GetRenderContext();
    CHECK_NULL_VOID(renderContext);
    renderContext->SetAlphaOffscreen(true);
}

void SliderPattern::OnWindowHide()
{
    isShow_ = false;
    StopAnimation();
}

void SliderPattern::OnWindowShow()
{
    isShow_ = true;
    StartAnimation();
}

bool SliderPattern::IsSliderVisible()
{
    return isVisibleArea_ && isShow_;
}

void SliderPattern::UpdateTipState()
{
    if (focusFlag_) {
        auto context = GetContext();
        CHECK_NULL_VOID(context);
        isFocusActive_ = context->GetIsFocusActive();
    } else {
        isFocusActive_ = false;
    }

    bool showBubble = false;
    if (showTips_ && focusFlag_) {
        showBubble = isFocusActive_ || mousePressedFlag_;
    }
    if (showBubble != bubbleFlag_) {
        bubbleFlag_ = showBubble;
        UpdateBubble();
    }
}

void SliderPattern::OnIsFocusActiveUpdate(bool isFocusActive)
{
    if (!focusFlag_) {
        return;
    }
    isFocusActive_ = isFocusActive;
    bool showBubble = false;
    if (showTips_) {
        showBubble = isFocusActive_ || mousePressedFlag_;
    }
    if (showBubble != bubbleFlag_) {
        bubbleFlag_ = showBubble;
        UpdateBubble();
        UpdateMarkDirtyNode(PROPERTY_UPDATE_RENDER);
    }
}

void SliderPattern::AddIsFocusActiveUpdateEvent()
{
    if (!isFocusActiveUpdateEvent_) {
        isFocusActiveUpdateEvent_ = [weak = WeakClaim(this)](bool isFocusAcitve) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->OnIsFocusActiveUpdate(isFocusAcitve);
        };
    }

    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void SliderPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto pipline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(GetHost());
}

void SliderPattern::FireBuilder()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (!makeFunc_.has_value()) {
        host->RemoveChildAndReturnIndex(contentModifierNode_);
        contentModifierNode_ = nullptr;
        host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
        return;
    }
    auto node = BuildContentModifierNode();
    if (contentModifierNode_ == node) {
        return;
    }
    host->RemoveChildAndReturnIndex(contentModifierNode_);
    contentModifierNode_ = node;
    CHECK_NULL_VOID(contentModifierNode_);
    host->AddChild(contentModifierNode_, 0);
    host->MarkNeedFrameFlushDirty(PROPERTY_UPDATE_MEASURE);
}

RefPtr<FrameNode> SliderPattern::BuildContentModifierNode()
{
    if (!makeFunc_.has_value()) {
        return nullptr;
    }
    auto sliderPaintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, nullptr);
    auto min = sliderPaintProperty->GetMin().value_or(0.0f);
    auto max = sliderPaintProperty->GetMax().value_or(100.0f);
    auto step = sliderPaintProperty->GetStep().value_or(1.0f);
    auto value = sliderPaintProperty->GetValue().value_or(min);
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    auto eventHub = host->GetEventHub<EventHub>();
    CHECK_NULL_RETURN(eventHub, nullptr);
    auto enabled = eventHub->IsEnabled();
    SliderConfiguration sliderConfiguration(value, min, max, step, enabled);
    return (makeFunc_.value())(sliderConfiguration);
}

void SliderPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    hasVisibleChangeRegistered_ = false;

    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(frameNode->GetAccessibilityId());
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "Slider OnDetachFromFrameNode OK");
}

void SliderPattern::InitOrRefreshSlipFactor()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    float min = sliderPaintProperty->GetMin().value_or(0.0f);
    float max = sliderPaintProperty->GetMax().value_or(100.0f);
    float step = sliderPaintProperty->GetStep().value_or(1.0f);
    if (step == 0) {
        return;
    }
    auto totalStepCount = static_cast<int32_t>((max - min) / step) + 1;
    if (NearZero(totalStepCount)) {
        return;
    }
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto sliderPPI = theme->GetSliderPPI();
    slipfactor_ = sliderPPI * SLIP_FACTOR_COEFFICIENT / totalStepCount;
}
} // namespace OHOS::Ace::NG

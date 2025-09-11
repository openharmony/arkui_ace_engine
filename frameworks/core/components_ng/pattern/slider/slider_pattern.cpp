/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#include "base/log/dump_log.h"
#include "base/geometry/ng/point_t.h"
#include "base/geometry/ng/size_t.h"
#include "base/geometry/offset.h"
#include "base/i18n/localization.h"
#include "base/log/log_wrapper.h"
#include "base/utils/multi_thread.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/container.h"
#include "core/common/vibrator/vibrator_utils.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/theme/app_theme.h"
#include "core/components_ng/pattern/image/image_layout_property.h"
#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/slider/slider_accessibility_property.h"
#include "core/components_ng/pattern/slider/slider_layout_property.h"
#include "core/components_ng/pattern/slider/slider_paint_property.h"
#include "core/components_ng/pattern/slider/slider_style.h"
#include "core/components_ng/pattern/slider/slider_custom_content_options.h"
#include "core/components_ng/pattern/stack/stack_pattern.h"
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
constexpr Dimension PAN_MOVE_DISTANCE = 5.0_vp;
constexpr double DEFAULT_SLIP_FACTOR = 50.0;
constexpr double SLIP_FACTOR_COEFFICIENT = 1.07;
constexpr uint64_t SCREEN_READ_SENDEVENT_TIMESTAMP = 100;
constexpr int32_t NONE_POINT_OFFSET = 2;
constexpr int32_t STEP_POINT_OFFSET = 1;
const std::string STR_SCREEN_READ_SENDEVENT = "ArkUISliderSendAccessibilityValueEvent";
const std::string SLIDER_EFFECT_ID_NAME = "haptic.slide";
#ifdef SUPPORT_DIGITAL_CROWN
constexpr float CROWN_SENSITIVITY_LOW = 0.5f;
constexpr float CROWN_SENSITIVITY_MEDIUM = 1.0f;
constexpr float CROWN_SENSITIVITY_HIGH = 2.0f;
constexpr int64_t CROWN_TIME_THRESH = 30;
constexpr char CROWN_VIBRATOR_WEAK[] = "watchhaptic.feedback.crown.strength2";
#endif

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

inline std::string ToString(const bool boolean)
{
    return std::string(boolean ? "true" : "false");
}

inline std::string ToString(const SliderModel::SliderMode& mode)
{
    const LinearEnumMapNode<SliderModel::SliderMode, std::string> table[] = {
        { SliderModel::SliderMode::OUTSET, "OUTSET" },
        { SliderModel::SliderMode::INSET, "INSET" },
        { SliderModel::SliderMode::NONE, "NONE" },
        { SliderModel::SliderMode::CAPSULE, "CAPSULE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), mode);
    return iter != -1 ? table[iter].value : "";
}

inline std::string ToString(const Axis& direction)
{
    const LinearEnumMapNode<Axis, std::string> table[] = {
        { Axis::VERTICAL, "VERTICAL" },
        { Axis::HORIZONTAL, "HORIZONTAL" },
        { Axis::FREE, "FREE" },
        { Axis::NONE, "NONE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), direction);
    return iter != -1 ? table[iter].value : "";
}

inline std::string ToString(const SliderModel::BlockStyleType& type)
{
    const LinearEnumMapNode<SliderModel::BlockStyleType, std::string> table[] = {
        { SliderModel::BlockStyleType::DEFAULT, "DEFAULT" },
        { SliderModel::BlockStyleType::IMAGE, "IMAGE" },
        { SliderModel::BlockStyleType::SHAPE, "SHAPE" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), type);
    return iter != -1 ? table[iter].value : "";
}

inline std::string ToString(const SliderModel::SliderInteraction& interaction)
{
    const LinearEnumMapNode<SliderModel::SliderInteraction, std::string> table[] = {
        { SliderModel::SliderInteraction::SLIDE_AND_CLICK, "SLIDE_AND_CLICK" },
        { SliderModel::SliderInteraction::SLIDE_ONLY, "SLIDE_ONLY" },
        { SliderModel::SliderInteraction::SLIDE_AND_CLICK_UP, "SLIDE_AND_CLICK_UP" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), interaction);
    return iter != -1 ? table[iter].value : "";
}

inline std::string ToString(const BasicShapeType& type)
{
    const LinearEnumMapNode<BasicShapeType, std::string> table[] = {
        { BasicShapeType::NONE, "NONE" },  { BasicShapeType::INSET, "INSET" },
        { BasicShapeType::CIRCLE, "CIRCLE" }, { BasicShapeType::ELLIPSE, "ELLIPSE" },
        { BasicShapeType::POLYGON, "POLYGON" }, { BasicShapeType::PATH, "PATH" },
        { BasicShapeType::RECT, "RECT" },
    };
    auto iter = BinarySearchFindIndex(table, ArraySize(table), type);
    return iter != -1 ? table[iter].value : "";
}
} // namespace

void SliderPattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    FireBuilder();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
    InitSliderEnds();
    UpdateBlock();
    InitializeBubble();
    SetAccessibilityAction();
    InitAccessibilityHoverEvent();
    AccessibilityVirtualNodeRenderTask();
    InitSliderAccessibilityEnabledRegister();
    InitOrRefreshSlipFactor();
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto callback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->InitEvent();
    };
    context->AddBuildFinishCallBack(callback);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    InitPanEvent(gestureHub);
}

void SliderPattern::InitEvent()
{
    RegisterVisibleAreaChange();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto hub = host->GetEventHub<EventHub>();
    CHECK_NULL_VOID(hub);
    auto gestureHub = hub->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    auto inputEventHub = hub->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(inputEventHub);
    InitClickEvent(gestureHub);
    InitTouchEvent(gestureHub);
    InitMouseEvent(inputEventHub);
    auto focusHub = hub->GetFocusHub();
    CHECK_NULL_VOID(focusHub);
    InitOnKeyEvent(focusHub);
#ifdef SUPPORT_DIGITAL_CROWN
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    crownSensitivity_ = sliderPaintProperty->GetDigitalCrownSensitivity().value_or(CrownSensitivity::MEDIUM);
    InitDigitalCrownEvent(focusHub);
#endif
}

void SliderPattern::InitSliderEnds()
{
    auto callback = [weak = WeakClaim(this)]() {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        CHECK_NULL_VOID(pattern->sliderContentModifier_);
        pattern->stepPoints_ = pattern->sliderContentModifier_->GetStepPointVec();
        pattern->blockStart_ = pattern->sliderContentModifier_->GetBlockBackStart();
        pattern->blockEnd_ = pattern->sliderContentModifier_->GetBlockBackEnd();
        if (pattern->HasPrefix()) {
            pattern->UpdatePrefixPosition();
        }

        if (pattern->HasPrefix()) {
            pattern->UpdateSuffixPosition();
        }
    };
    if (prefixNodeStack_) {
        prefixNodeStack_->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    if (suffixNodeStack_) {
        suffixNodeStack_->MarkDirtyNode(
            PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->RegisterStepPointCallback(std::move(callback));
}

void SliderPattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipeline);
    auto sliderTheme = pipeline->GetTheme<SliderTheme>(GetThemeScopeId());
    CHECK_NULL_VOID(sliderTheme);
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (!paintProperty->GetBlockColorSetByUser().value_or(false)) {
        paintProperty->UpdateBlockColor(sliderTheme->GetBlockColor());
    }
    if (!paintProperty->GetTrackBackgroundColorSetByUser().value_or(false)) {
        Gradient defaultValue = SliderModelNG::CreateSolidGradient(sliderTheme->GetTrackBgColor());
        paintProperty->UpdateTrackBackgroundColor(defaultValue);
        paintProperty->UpdateTrackBackgroundIsResourceColor(true);
    }
    if (!paintProperty->GetSelectColorSetByUser().value_or(false)) {
        paintProperty->UpdateSelectColor(sliderTheme->GetTrackSelectedColor());
        paintProperty->UpdateSelectIsResourceColor(true);
    }
    host->MarkDirtyNode();
}

void SliderPattern::PlayHapticFeedback(bool isShowSteps)
{
    if (!isEnableHaptic_) {
        return;
    }
    if (isShowSteps) {
        VibratorUtils::StartViratorDirectly(SLIDER_EFFECT_ID_NAME);
    }
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
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto level = accessibilityProperty->GetAccessibilityLevel();
    auto eventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    if (level == AccessibilityProperty::Level::NO_STR || level == AccessibilityProperty::Level::NO_HIDE_DESCENDANTS) {
        ClearSliderVirtualNode();
        return;
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
        } else {
            sliderPattern->SetBubbleFlag(false);
            auto sliderContentModifier = sliderPattern->GetSliderContentModifier();
            CHECK_NULL_RETURN(sliderContentModifier, false);
            sliderContentModifier->SetIsHovered(false);
            auto host = sliderPattern->GetHost();
            CHECK_NULL_RETURN(host, false);
            host->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
        }
        sliderPattern->SetIsAccessibilityOn(state);
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
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_RETURN(accessibilityProperty, false);
    auto level = accessibilityProperty->GetAccessibilityLevel();
    if (!AceApplicationInfo::GetInstance().IsAccessibilityEnabled() || UseContentModifier() || !isShowSteps ||
        (level == AccessibilityProperty::Level::NO_STR) ||
        (level == AccessibilityProperty::Level::NO_HIDE_DESCENDANTS)) {
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
    if (pointAccessibilityNodeVec_.empty()) {
        return false;
    }
    UpdateStepPointsAccessibilityVirtualNodeSelected();
    host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    CHECK_NULL_RETURN(sliderContentModifier_, false);
    if (sliderContentModifier_) {
        sliderContentModifier_->SetUpdateAccessibilityCallback([weak = WeakClaim(this)]() {
            auto sliderPattern = weak.Upgrade();
            CHECK_NULL_VOID(sliderPattern);
            sliderPattern->UpdateStepAccessibilityVirtualNode();
            sliderPattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
        });
    }
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
    UpdateStepAccessibilityVirtualNode();
    UpdateStepPointsAccessibilityVirtualNodeSelected();
    auto host = GetHost();
    CHECK_NULL_VOID(host);
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
            PointF(stepPointVec[i].GetX() - pointOffsetWidth, stepPointVec[i].GetY() - pointOffsetHeight), txt, i);
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
    const RefPtr<FrameNode>& pointNode, const SizeF& size, const PointF& point, const std::string& txt, uint32_t index)
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
        CHECK_NULL_VOID(range);
        rangeFromPointIndex = range->GetFromValue() / step;
        rangeToPointIndex = range->GetToValue() / step;
    }
    auto pipeline = GetContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetTheme<SliderTheme>();
    CHECK_NULL_VOID(theme);
    auto unSelectedDesc = theme->GetUnselectedDesc();
    auto disabledDesc = theme->GetDisabelDesc();
    uint32_t indexPrefix = 0;
    uint32_t indexSuffix = static_cast<int32_t>(pointAccessibilityNodeVec_.size()) - STEP_POINT_OFFSET;
    SliderModel::SliderShowStepOptions optionsMap =
        sliderPaintProperty->GetSliderShowStepOptions().value_or(SliderModel::SliderShowStepOptions ());
    for (uint32_t i = 0; i < pointCount; i++) {
        auto isDisabledDesc = false;
        bool isClickAbled = true;
        RefPtr<FrameNode>& pointNode = pointAccessibilityNodeVec_[i];
        auto pointAccessibilityProperty = pointNode->GetAccessibilityProperty<TextAccessibilityProperty>();
        pointAccessibilityProperty->SetAccessibilityLevel(AccessibilityProperty::Level::YES_STR);

        if (currentStepIndex == i) {
            pointAccessibilityProperty->SetSelected(true);
            pointAccessibilityProperty->SetAccessibilityDescription(" ");
            isClickAbled = false;
        } else if (i >= rangeFromPointIndex && i <= rangeToPointIndex) {
            pointAccessibilityProperty->SetSelected(false);
            pointAccessibilityProperty->SetAccessibilityDescription(unSelectedDesc);
        } else {
            pointAccessibilityProperty->SetSelected(false);
            pointAccessibilityProperty->SetAccessibilityDescription(disabledDesc);
            isDisabledDesc = true;
        }
        UpdateStepPointsAccessibilityText(pointNode, i, optionsMap);

        if (i == indexPrefix && HasPrefix()) {
            if (!prefixAccessibilityoptions_.accessibilityText.empty()) {
                pointAccessibilityProperty->SetAccessibilityText(prefixAccessibilityoptions_.accessibilityText);
            }
            if (!prefixAccessibilityoptions_.accessibilityDescription.empty()) {
                pointAccessibilityProperty->SetAccessibilityDescription(
                    prefixAccessibilityoptions_.accessibilityDescription);
            }
            pointAccessibilityProperty->SetAccessibilityLevel(prefixAccessibilityoptions_.accessibilityLevel);
            pointAccessibilityProperty->SetAccessibilityGroup(prefixAccessibilityoptions_.accessibilityGroup);
        }

        if (i == indexSuffix && HasSuffix()) {
            if (!suffixAccessibilityoptions_.accessibilityText.empty()) {
                pointAccessibilityProperty->SetAccessibilityText(suffixAccessibilityoptions_.accessibilityText);
            }
            if (!suffixAccessibilityoptions_.accessibilityDescription.empty()) {
                pointAccessibilityProperty->SetAccessibilityDescription(
                    suffixAccessibilityoptions_.accessibilityDescription);
            }
            pointAccessibilityProperty->SetAccessibilityLevel(suffixAccessibilityoptions_.accessibilityLevel);
            pointAccessibilityProperty->SetAccessibilityGroup(suffixAccessibilityoptions_.accessibilityGroup);
        }

        SetStepPointsAccessibilityVirtualNodeEvent(pointNode, i, isClickAbled, reverse, isDisabledDesc);
    }
}

void SliderPattern::SetStepPointsAccessibilityVirtualNodeEvent(
    const RefPtr<FrameNode>& pointNode, uint32_t index, bool isClickAbled, bool reverse, bool isDisabledDesc)
{
    if (isDisabledDesc) {
        return;
    }
    CHECK_NULL_VOID(pointNode);
    auto gestureHub = pointNode->GetOrCreateGestureEventHub();
    CHECK_NULL_VOID(gestureHub);
    if (isClickAbled && !pointAccessibilityNodeEventVec_[index]) {
        auto clickHandle = [weak = WeakClaim(this), index, reverse](GestureEvent& info) {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            pattern->FireChangeEvent(SliderChangeMode::Begin);
            auto offsetStep = pattern->GetOffsetStepIndex(index);
            pattern->MoveStep(offsetStep);
            pattern->FireChangeEvent(SliderChangeMode::End);
            if (pattern->showTips_) {
                pattern->bubbleFlag_ = true;
                pattern->InitializeBubble();
            }
            pattern->PaintFocusState();
            pattern->UpdateStepPointsAccessibilityVirtualNodeSelected();
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
    return static_cast<uint32_t>(std::ceil((currentValue - min) / step));
}

int32_t SliderPattern::GetOffsetStepIndex(uint32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(sliderPaintProperty, 0);
    const float step = sliderPaintProperty->GetStep().value_or(1.0f);
    const float currentValue = sliderPaintProperty->GetValueValue(value_);
    const double min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    if (NearZero(step)) {
        return 0;
    }
    auto stepIndex = static_cast<int32_t>(std::ceil((currentValue - min) / step));
    auto diffValue = stepIndex * step + min - currentValue;
    int32_t offsetStepIndex = static_cast<int32_t>(index) - stepIndex;
    if (NearZero(diffValue) || offsetStepIndex <= 0) {
        return offsetStepIndex;
    } else {
        return offsetStepIndex + 1;
    }
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
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto context = host->GetContext();
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
    return UpdateParameters();
}

void SliderPattern::ClearSliderVirtualNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    pointAccessibilityNodeVec_.clear();
    pointAccessibilityNodeEventVec_.clear();
    isInitAccessibilityVirtualNode_ = false;
    auto accessibilityProperty = host->GetAccessibilityProperty<AccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    accessibilityProperty->SaveAccessibilityVirtualNode(nullptr);
    auto eventHub = host->GetOrCreateInputEventHub();
    CHECK_NULL_VOID(eventHub);
    eventHub->ClearUserOnAccessibilityHover();
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
    if (sliderMode_ != sliderMode && isAccessibilityOn_) {
        ClearSliderVirtualNode();
        InitAccessibilityVirtualNodeTask();
        InitAccessibilityHoverEvent();
        sliderMode_ = sliderMode;
    }
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

void SliderPattern::UpdateSliderComponentColor(const Color& color, const SliderColorType sliderColorType,
    const Gradient& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto* pipelineContext = host->GetContextWithCheck();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange()) {
        switch (sliderColorType) {
            case SliderColorType::BLOCK_COLOR:
                paintProperty->UpdateBlockColor(color);
                break;
            case SliderColorType::TRACK_COLOR:
                paintProperty->UpdateTrackBackgroundColor(value);
                paintProperty->UpdateTrackBackgroundIsResourceColor(true);
                break;
            case SliderColorType::SELECT_COLOR:
                paintProperty->UpdateSelectColor(color);
                paintProperty->UpdateSelectGradientColor(value);
                paintProperty->UpdateSelectIsResourceColor(true);
                break;
            case SliderColorType::BLOCK_BORDER_COLOR:
                paintProperty->UpdateBlockBorderColor(color);
                break;
            case SliderColorType::STEP_COLOR:
                paintProperty->UpdateStepColor(color);
                break;
        }
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SliderPattern::UpdateSliderComponentMedia()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);

    if (pipelineContext->IsSystmColorChange()) {
        UpdateBlock();
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SliderPattern::UpdateSliderComponentString(const bool isShowTips, const std::string& value)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (pipelineContext->IsSystmColorChange()) {
        paintProperty->UpdateShowTips(isShowTips);
        paintProperty->UpdateCustomContent(value);
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void SliderPattern::OnWindowSizeChanged(int32_t width, int32_t height, WindowSizeChangeReason type)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    if (type == WindowSizeChangeReason::ROTATION &&
        host->GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWELVE)) {
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
    auto touchList = info.GetChangedTouches();
    CHECK_NULL_VOID(!touchList.empty());
    auto touchInfo = touchList.front();
    auto touchType = touchInfo.GetTouchType();
    if (touchType == TouchType::DOWN) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle touchDown");
        ResetSkipGestureEvents();
        if (fingerId_ != -1) {
            return;
        }
        fingerId_ = touchInfo.GetFingerId();
        HandleTouchDown(touchInfo.GetLocalLocation(), info.GetSourceDevice());
    } else if (touchType == TouchType::UP || touchType == TouchType::CANCEL) {
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider handle touchUp, isVisibleArea:%{public}d, isShow:%{public}d",
            isVisibleArea_, isShow_);
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
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetIsPressed(true);
}

bool NeedFireClickEvent(const Offset& downLocation, const Offset& upLocation)
{
    auto diff = downLocation - upLocation;
    return diff.GetDistance() < PAN_MOVE_DISTANCE.ConvertToPx();
}

void SliderPattern::HandleTouchUp(const Offset& location, SourceType sourceType)
{
    if (sliderInteractionMode_ == SliderModelNG::SliderInteraction::SLIDE_AND_CLICK_UP &&
        lastTouchLocation_.has_value() && NeedFireClickEvent(lastTouchLocation_.value(), location)) {
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
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetIsPressed(false);
}

void SliderPattern::InitializeBubble()
{
    CHECK_NULL_VOID(showTips_);
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto sliderTheme = pipeline->GetTheme<SliderTheme>(GetThemeScopeId());
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
    auto overlayGlobalOffset = host->GetPaintRectOffset(false, true);
    auto pipelineContext = host->GetContext();
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
    auto geometryNode = host->GetGeometryNode();
    CHECK_NULL_VOID(geometryNode);
    const auto& content = geometryNode->GetContent();
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
    bool isShowSteps = sliderPaintProperty->GetShowStepsValue(false);
    if (valueChangeFlag_) {
        PlayHapticFeedback(isShowSteps);
    }
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
        CHECK_NULL_RETURN(range, value);
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
    auto direction = GetDirection();
    if (direction_ != direction && isInitAccessibilityVirtualNode_) {
        ClearSliderVirtualNode();
        InitAccessibilityVirtualNodeTask();
        InitAccessibilityHoverEvent();
    }
    direction_ = direction;

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
    PanDistanceMap distanceMap = { { SourceTool::UNKNOWN, pipeline->IsFormRender() ? FORM_PAN_DISTANCE.ConvertToPx() :
        DEFAULT_PAN_DISTANCE.ConvertToPx() }, { SourceTool::PEN, pipeline->IsFormRender() ?
        FORM_PAN_DISTANCE.ConvertToPx() : DEFAULT_PEN_PAN_DISTANCE.ConvertToPx() } };
    gestureHub->AddPanEvent(panEvent_, panDirection, 1, distanceMap);
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

    auto onFocus = [wp = WeakClaim(this)](FocusReason reason) {
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
    CHECK_NULL_VOID(theme);
    auto appTheme = PipelineBase::GetCurrentContext()->GetTheme<AppTheme>();
    CHECK_NULL_VOID(appTheme);
    auto paintWidth = appTheme->GetFocusWidthVp();
    auto focusSideDistance = theme->GetFocusSideDistance();
    auto focusDistance = paintWidth * HALF + focusSideDistance;
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);
    auto blockType = paintProperty->GetBlockTypeValue(SliderModelNG::BlockStyleType::DEFAULT);
    if (!theme->ShowFocusFrame()) {
        auto halfWidth = blockSize_.Width() * HALF + static_cast<float>(focusDistance.ConvertToPx());
        auto halfHeight = blockSize_.Height() * HALF + static_cast<float>(focusDistance.ConvertToPx());
        paintRect.SetRect(RectF(circleCenter_.GetX() - halfWidth + contentOffset.GetX(),
            circleCenter_.GetY() - halfHeight + contentOffset.GetY(), halfWidth / HALF, halfHeight / HALF));
        paintRect.SetCornerRadius(focusDistance.ConvertToPx());
        if (blockType == SliderModelNG::BlockStyleType::DEFAULT) {
            auto focusRadius = std::min(blockSize_.Width(), blockSize_.Height()) * HALF +
                               static_cast<float>(focusDistance.ConvertToPx());
            paintRect.SetRect(RectF(circleCenter_.GetX() - focusRadius + contentOffset.GetX(),
                circleCenter_.GetY() - focusRadius + contentOffset.GetY(), focusRadius / HALF, focusRadius / HALF));
            paintRect.SetCornerRadius(focusRadius);
        }
    }
    if (blockType == SliderModelNG::BlockStyleType::SHAPE) {
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
    UpdatePaintRect(theme, sliderMode, paintRect, RectF(offsetX, offsetY, width, height), focusRadius);
}

void SliderPattern::UpdatePaintRect(RefPtr<SliderTheme> theme, SliderModel::SliderMode& sliderMode,
    RoundRect& paintRect, const RectF& rect, float rectRadius)
{
    if (theme->ShowFocusFrame()) {
        if (sliderMode == SliderModel::SliderMode::INSET) {
            paintRect.SetRect(rect);
            paintRect.SetCornerRadius(rectRadius);
        }
    } else {
        paintRect.SetRect(rect);
        paintRect.SetCornerRadius(rectRadius);
    }
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
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetIsHovered(true);
    if (!mouseHoverFlag_) {
        axisFlag_ = false;
        sliderContentModifier_->SetIsHovered(false);
    }
    if (!mouseHoverFlag_ && !axisFlag_ && !isFocusActive_ && !mousePressedFlag_) {
        bubbleFlag_ = false;
        sliderContentModifier_->SetIsHovered(false);
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
            CHECK_NULL_VOID(sliderContentModifier_);
            sliderContentModifier_->SetIsHovered(true);
        }
    }
    // when mouse hovers over slider, distinguish between hover block and Wheel operation.
    if (!mouseHoverFlag_ && !axisFlag_ && !isFocusActive_ && !mousePressedFlag_) {
        bubbleFlag_ = false;
        CHECK_NULL_VOID(sliderContentModifier_);
        sliderContentModifier_->SetIsHovered(false);
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

#ifdef SUPPORT_DIGITAL_CROWN
double SliderPattern::GetCrownRotatePx(const CrownEvent& event) const
{
    double px = -event.degree * crownDisplayControlRatio_;
    switch (crownSensitivity_) {
        case CrownSensitivity::LOW:
            px *= CROWN_SENSITIVITY_LOW;
            break;
        case CrownSensitivity::MEDIUM:
            px *= CROWN_SENSITIVITY_MEDIUM;
            break;
        case CrownSensitivity::HIGH:
            px *= CROWN_SENSITIVITY_HIGH;
            break;
        default:
            break;
    }
    return px;
}

void SliderPattern::HandleCrownAction(double mainDelta)
{
    CHECK_NULL_VOID(sliderLength_ != 0);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    float min = sliderPaintProperty->GetMin().value_or(SLIDER_MIN);
    float max = sliderPaintProperty->GetMax().value_or(SLIDER_MAX);
    crownMovingLength_ += mainDelta;
    crownMovingLength_ = std::clamp(crownMovingLength_, 0.0, static_cast<double>(sliderLength_));
    valueRatio_ = crownMovingLength_ / sliderLength_;
    auto stepRatio = sliderPaintProperty->GetStepRatio();
    CHECK_NULL_VOID(stepRatio != 0);
    valueRatio_ = NearEqual(valueRatio_, 1) ? 1 : std::round(valueRatio_ / stepRatio) * stepRatio;
    float oldValue = value_;
    value_ = std::clamp(valueRatio_ * (max - min) + min, min, max);
    sliderPaintProperty->UpdateValue(value_);
    valueChangeFlag_ = !NearEqual(oldValue, value_);
    UpdateCircleCenterOffset();
    reachBoundary_ = NearEqual(value_, min) || NearEqual(value_, max);
    if (showTips_) {
        bubbleFlag_ = true;
        UpdateBubble();
    }
}

void SliderPattern::StartVibrateFeedback()
{
    timeStampCur_ = GetCurrentTimestamp();
    if (!reachBoundary_ && (timeStampCur_ - timeStampPre_ >= CROWN_TIME_THRESH)) {
        VibratorUtils::StartVibraFeedback(CROWN_VIBRATOR_WEAK);
        TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "slider StartVibrateFeedback %{public}s", CROWN_VIBRATOR_WEAK);
        timeStampPre_ = timeStampCur_;
    }
}
#endif

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
    auto theme = pipeline->GetTheme<SliderTheme>(GetThemeScopeId());
    CHECK_NULL_RETURN(theme, SliderContentModifier::Parameters());
    auto stepRatio = paintProperty->GetStepRatio();
    SliderContentModifier::Parameters parameters { trackThickness_, blockSize_, stepRatio, hotBlockShadowWidth_,
        mouseHoverFlag_, mousePressedFlag_, PointF(), PointF(), PointF(), PointF(), PointF(), Gradient(),
        Gradient(), Gradient(), Color::TRANSPARENT };
    auto contentSize = GetHostContentSize();
    CHECK_NULL_RETURN(contentSize, SliderContentModifier::Parameters());
    const auto& content = GetHost()->GetGeometryNode()->GetContent();
    CHECK_NULL_RETURN(content, SliderContentModifier::Parameters());
    auto contentOffset = content->GetRect().GetOffset();
    // Distance between slide track and Content boundary
    auto centerWidth = direction_ == Axis::HORIZONTAL ? contentSize->Height() : contentSize->Width();
    centerWidth *= HALF;

    auto sliderLayoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_RETURN(sliderLayoutProperty, SliderContentModifier::Parameters());
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    Color trackColor = theme->GetTrackSelectedColor();
    if (sliderMode == SliderModel::SliderMode::OUTSET) {
        trackColor = theme->GetOutsetModeSelectedTrackColor();
    }
    if (sliderMode == SliderModel::SliderMode::NONE) {
        trackColor = theme->GetNoneModeSelectedTrackColor();
    }
    Gradient defaultSelectGradientColor = SliderModelNG::CreateSolidGradient(theme->GetTrackSelectedColor());
    parameters.selectGradientColor = paintProperty->GetSelectGradientColor().value_or(defaultSelectGradientColor);
    Gradient defaultValue = SliderModelNG::CreateSolidGradient(theme->GetTrackBgColor());
    parameters.trackBackgroundColor = paintProperty->GetTrackBackgroundColor().value_or(defaultValue);
    parameters.blockColor = paintProperty->GetBlockColor();
    parameters.blockGradientColor = paintProperty->GetBlockGradientColor();
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
    CHECK_NULL_VOID(info);
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

void SliderPattern::UpdateImagePosition(const PointF& imageCenter)
{
    CHECK_NULL_VOID(imageFrameNode_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->AddAfterModifierTask([weakNode = WeakPtr(imageFrameNode_), imageCenter, blocksize = blockSize_]() {
        auto imageNode = weakNode.Upgrade();
        CHECK_NULL_VOID(imageNode);
        const auto& renderContext = imageNode->GetRenderContext();
        CHECK_NULL_VOID(renderContext);
        const auto& geometryNode = imageNode->GetGeometryNode();
        CHECK_NULL_VOID(geometryNode);
        auto offset = geometryNode->GetMarginFrameOffset();
        offset.SetX(imageCenter.GetX() - blocksize.Width() * HALF);
        offset.SetY(imageCenter.GetY() - blocksize.Height() * HALF);
        geometryNode->SetMarginFrameOffset(offset);
        renderContext->SavePaintRect();
        renderContext->SyncGeometryProperties(nullptr);
    });
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

void SliderPattern::UpdatePrefixPosition()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto prefixNodeStackContext = prefixNodeStack_->GetRenderContext();
    CHECK_NULL_VOID(prefixNodeStackContext);

    auto reverse = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>());
    PointF block = { 0.0f, 0.0f };
    float noneOffset = 50.0f;
    float outsetOffset = 0.0f;
    Dimension offsetWidth = 12.0_vp;
    outsetOffset_ = static_cast<float>(offsetWidth.ConvertToPx())/HALF;
    if (reverse) {
        block = blockEnd_;
        noneOffset = -noneOffset;
        outsetOffset = -outsetOffset_;
    } else {
        block = blockStart_;
        outsetOffset = outsetOffset_;
    }
    bool isShowSteps = sliderPaintProperty->GetShowStepsValue(false);
    if (!isShowSteps) {
        UpdateEndsNotShowStepsPosition(prefixPosition_, block, prefixSize_, noneOffset, outsetOffset);
    } else {
        UpdateEndsIsShowStepsPosition(prefixPosition_, block, prefixSize_, outsetOffset, side_);
    }
    prefixNodeStackContext->UpdatePosition(OffsetT(
        Dimension(prefixPosition_.GetX(), DimensionUnit::PX), Dimension(prefixPosition_.GetY(), DimensionUnit::PX)));

    prefixNodeStack_->MarkDirtyNode(
        PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SliderPattern::UpdateSuffixPosition()
{
    CHECK_NULL_VOID(sliderContentModifier_);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderPaintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(sliderPaintProperty);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto suffixNodeStackContext = suffixNodeStack_->GetRenderContext();
    CHECK_NULL_VOID(suffixNodeStackContext);
    auto reverse = GetReverseValue(GetLayoutProperty<SliderLayoutProperty>());

    PointF block = { 0.0f, 0.0f };
    float noneOffset = -50.0f;
    float outsetOffset = 0.0f;
    Dimension offsetWidth = 12.0_vp;
    outsetOffset_ = static_cast<float>(offsetWidth.ConvertToPx())/HALF;
    if (reverse) {
        block = blockStart_;
        noneOffset = -noneOffset;
        outsetOffset = outsetOffset_;
    } else {
        block = blockEnd_;
        outsetOffset = -outsetOffset_;
    }
    bool isShowSteps = sliderPaintProperty->GetShowStepsValue(false);
    if (!isShowSteps) {
        UpdateEndsNotShowStepsPosition(suffixPosition_, block, suffixSize_, noneOffset, outsetOffset);
    } else {
        UpdateEndsIsShowStepsPosition(suffixPosition_, block, suffixSize_, outsetOffset, !side_);
    }
    suffixNodeStackContext->UpdatePosition(OffsetT(
        Dimension(suffixPosition_.GetX(), DimensionUnit::PX), Dimension(suffixPosition_.GetY(), DimensionUnit::PX)));

    suffixNodeStack_->MarkDirtyNode(
        PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_RENDER | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
}

void SliderPattern::UpdateEndsNotShowStepsPosition(
    PointF& EndsPosition, PointF& block, SizeF& endsSize, float noneOffset, float outsetOffset)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    auto axis = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);
    float halfWidth = endsSize.Width() * HALF;
    float halfHeight = endsSize.Height() * HALF;

    if (axis == Axis::HORIZONTAL) {
        float xOffset = (sliderMode == SliderModel::SliderMode::OUTSET) ? -outsetOffset
                        : (sliderMode == SliderModel::SliderMode::NONE) ? noneOffset : 0;
        EndsPosition.SetX(block.GetX() - halfWidth + xOffset);
        EndsPosition.SetY(block.GetY() - halfHeight);
    }

    else {
        float yOffset = (sliderMode == SliderModel::SliderMode::OUTSET) ? -outsetOffset
                        : (sliderMode == SliderModel::SliderMode::NONE) ? noneOffset : 0;
        EndsPosition.SetY(block.GetY() - halfHeight + yOffset);
        EndsPosition.SetX(block.GetX() - halfWidth);
    }
}

void SliderPattern::UpdateEndsIsShowStepsPosition(
    PointF& EndsPosition, PointF& block, SizeF& endsSize, float outsetOffset, bool side)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto sliderLayoutProperty = host->GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(sliderLayoutProperty);
    auto sliderMode = sliderLayoutProperty->GetSliderMode().value_or(SliderModel::SliderMode::OUTSET);
    auto axis = sliderLayoutProperty->GetDirection().value_or(Axis::HORIZONTAL);

    int32_t noneModePoint = 1;
    int32_t stepModePoint = 0;
    if (!side) {
        noneModePoint = static_cast<int32_t>(stepPoints_.size()) - NONE_POINT_OFFSET;
        stepModePoint = static_cast<int32_t>(stepPoints_.size()) - STEP_POINT_OFFSET;
    }

    if (stepPoints_.size() < 1) {
        return;
    }
    if (sliderMode == SliderModel::SliderMode::NONE) {
        EndsPosition.SetX(stepPoints_[noneModePoint].GetX() - endsSize.Width() * HALF);
        EndsPosition.SetY(stepPoints_[noneModePoint].GetY() - endsSize.Height() * HALF);
    } else if (sliderMode == SliderModel::SliderMode::OUTSET) {
        if (axis == Axis::HORIZONTAL) {
            EndsPosition.SetX(stepPoints_[stepModePoint].GetX() - endsSize.Width() * HALF - outsetOffset);
            EndsPosition.SetY(stepPoints_[stepModePoint].GetY() - endsSize.Height() * HALF);
        } else {
            EndsPosition.SetX(stepPoints_[stepModePoint].GetX() - endsSize.Width() * HALF);
            EndsPosition.SetY(stepPoints_[stepModePoint].GetY() - endsSize.Height() * HALF - outsetOffset);
        }
    } else {
        EndsPosition.SetX(stepPoints_[stepModePoint].GetX() - endsSize.Width() * HALF);
        EndsPosition.SetY(stepPoints_[stepModePoint].GetY() - endsSize.Height() * HALF);
    }
}

void SliderPattern::SetPrefix(const RefPtr<NG::UINode>& prefix, const NG::SliderPrefixOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto prefixFrameNode = DynamicCast<FrameNode>(prefix);
    if (!prefixFrameNode) {
        return;
    }
    if (!prefixNodeStack_) {
        prefixNodeStack_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
        host->AddChild(prefixNodeStack_, 1);
        prefixNodeStack_->AddChild(prefixFrameNode);
        prefixNodeStack_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    prefix->SetActive(false);
    prefixAccessibilityoptions_ = options;

    prefix_ = prefix;
}

void SliderPattern::SetSuffix(const RefPtr<NG::UINode>& suffix, const NG::SliderSuffixOptions& options)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto suffixFrameNode = DynamicCast<FrameNode>(suffix);
    if (!suffixFrameNode) {
        return;
    }
    if (!suffixNodeStack_) {
        suffixNodeStack_ = FrameNode::GetOrCreateFrameNode(V2::STACK_ETS_TAG,
            ElementRegister::GetInstance()->MakeUniqueId(), []() { return AceType::MakeRefPtr<StackPattern>(); });
        host->AddChild(suffixNodeStack_, 1);
        suffixNodeStack_->AddChild(suffixFrameNode);
        suffixNodeStack_->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT | PROPERTY_UPDATE_MEASURE_SELF_AND_CHILD);
    }
    suffix->SetActive(false);
    suffixAccessibilityoptions_ = options;

    suffix_ = suffix;
}

void SliderPattern::ResetPrefix()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    prefix_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
}

void SliderPattern::ResetSuffix()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    suffix_.Reset();
    host->MarkDirtyNode(PROPERTY_UPDATE_LAYOUT);
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
    auto host = GetHost();
    FREE_NODE_CHECK(host, UpdateValue, host);
    CalcSliderValue();
    FireBuilder();
}

void SliderPattern::OnAttachToFrameNode()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnAttachToFrameNode);
}

void SliderPattern::OnAttachToMainTree()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnAttachToMainTree);
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
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetIsFocused(isFocusActive_);
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
    CHECK_NULL_VOID(sliderContentModifier_);
    sliderContentModifier_->SetIsFocused(isFocusActive);
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
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipline = host->GetContext();
    CHECK_NULL_VOID(pipline);
    pipline->AddIsFocusActiveUpdateEvent(GetHost(), isFocusActiveUpdateEvent_);
}

void SliderPattern::RemoveIsFocusActiveUpdateEvent()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipline = host->GetContext();
    CHECK_NULL_VOID(pipline);
    pipline->RemoveIsFocusActiveUpdateEvent(host);
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

void SliderPattern::RemoveCallbackOnDetach(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    pipeline->RemoveVisibleAreaChangeNode(frameNode->GetId());
    pipeline->RemoveWindowStateChangedCallback(frameNode->GetId());
    pipeline->RemoveWindowSizeChangeCallback(frameNode->GetId());
    hasVisibleChangeRegistered_ = false;

    auto accessibilityManager = pipeline->GetAccessibilityManager();
    CHECK_NULL_VOID(accessibilityManager);
    accessibilityManager->DeregisterAccessibilitySAObserverCallback(frameNode->GetAccessibilityId());
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT, "Slider RemoveCallbackOnDetach OK");
}

void SliderPattern::OnDetachFromFrameNode(FrameNode* frameNode)
{
    THREAD_SAFE_NODE_CHECK(frameNode, OnDetachFromFrameNode);
    RemoveCallbackOnDetach(frameNode);
}

void SliderPattern::OnDetachFromMainTree()
{
    auto host = GetHost();
    THREAD_SAFE_NODE_CHECK(host, OnDetachFromMainTree, host);
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

bool SliderPattern::OnThemeScopeUpdate(int32_t themeScopeId)
{
    bool result = false;
    auto host = GetHost();
    CHECK_NULL_RETURN(host, result);
    auto paintProperty = host->GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_RETURN(paintProperty, result);
    result = !paintProperty->HasBlockColor() ||
        !paintProperty->HasTrackBackgroundColor() ||
        !paintProperty->HasSelectColor() ||
        !paintProperty->HasStepColor();
    return result;
}

void SliderPattern::DumpInfo()
{
    auto paintProperty = GetPaintProperty<SliderPaintProperty>();
    CHECK_NULL_VOID(paintProperty);

    if (paintProperty->HasValue()) {
        DumpLog::GetInstance().AddDesc("Value: " + std::to_string(paintProperty->GetValue().value()));
    }
    if (paintProperty->HasMin()) {
        DumpLog::GetInstance().AddDesc("Min: " + std::to_string(paintProperty->GetMin().value()));
    }
    if (paintProperty->HasMax()) {
        DumpLog::GetInstance().AddDesc("Max: " + std::to_string(paintProperty->GetMax().value()));
    }
    if (paintProperty->HasStep()) {
        DumpLog::GetInstance().AddDesc("Step: " + std::to_string(paintProperty->GetStep().value()));
    }
    if (paintProperty->HasSliderMode()) {
        DumpLog::GetInstance().AddDesc("Style: " + ToString(paintProperty->GetSliderMode().value()));
    }
    if (paintProperty->HasDirection()) {
        DumpLog::GetInstance().AddDesc("Direction: " + ToString(paintProperty->GetDirection().value()));
    }
    if (paintProperty->HasReverse()) {
        DumpLog::GetInstance().AddDesc("Reverse: " + ToString(paintProperty->GetReverse().value()));
    }
    if (paintProperty->HasBlockColor()) {
        DumpLog::GetInstance().AddDesc("BlockColor: " + paintProperty->GetBlockColor().value().ToString());
    }
    if (paintProperty->HasBlockGradientColor()) {
        std::vector<GradientColor> gradientColors = paintProperty->GetBlockGradientColor().value().GetColors();
        std::ostringstream oss;
        for (const auto& gradientColor : gradientColors) {
            oss << gradientColor.GetLinearColor().ToColor().ToString() << " ";
        }
        DumpLog::GetInstance().AddDesc("BlockLinearGradientColor: " + oss.str());
    }
    if (paintProperty->HasTrackBackgroundColor()) {
        std::vector<GradientColor> gradientColors = paintProperty->GetTrackBackgroundColor().value().GetColors();
        std::ostringstream oss;
        for (const auto& gradientColor : gradientColors) {
            oss << gradientColor.GetLinearColor().ToColor().ToString() << " ";
        }
        DumpLog::GetInstance().AddDesc("TrackBackgroundColor: " + oss.str());
    }
    if (paintProperty->HasSelectColor()) {
        DumpLog::GetInstance().AddDesc("SelectColor: " + paintProperty->GetSelectColor().value().ToString());
    }
    if (paintProperty->HasMinResponsiveDistance()) {
        DumpLog::GetInstance().AddDesc(
            "MinResponsiveDistance: " + std::to_string(paintProperty->GetMinResponsiveDistance().value()));
    }
    if (paintProperty->HasShowSteps()) {
        DumpLog::GetInstance().AddDesc("ShowSteps: " + ToString(paintProperty->GetShowSteps().value()));
    }
    if (paintProperty->HasShowTips()) {
        DumpLog::GetInstance().AddDesc("ShowTips: " + ToString(paintProperty->GetShowTips().value()));
    }

    DumpSubInfo(paintProperty);
}

void SliderPattern::DumpSubInfo(RefPtr<SliderPaintProperty> paintProperty)
{
    auto layoutProperty = GetLayoutProperty<SliderLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);

    if (layoutProperty->HasThickness()) {
        DumpLog::GetInstance().AddDesc("Thickness: " + layoutProperty->GetThickness().value().ToString());
    }
    if (paintProperty->HasBlockBorderColor()) {
        DumpLog::GetInstance().AddDesc("BlockBorderColor: " + paintProperty->GetBlockBorderColor().value().ToString());
    }
    if (paintProperty->HasBlockBorderWidth()) {
        DumpLog::GetInstance().AddDesc("BlockBorderWidth: " + paintProperty->GetBlockBorderWidth().value().ToString());
    }
    if (paintProperty->HasStepColor()) {
        DumpLog::GetInstance().AddDesc("StepColor: " + paintProperty->GetStepColor().value().ToString());
    }
    if (paintProperty->HasStepSize()) {
        DumpLog::GetInstance().AddDesc("StepSize: " + paintProperty->GetStepSize().value().ToString());
    }
    if (paintProperty->HasTrackBorderRadius()) {
        DumpLog::GetInstance().AddDesc(
            "TrackBorderRadius: " + paintProperty->GetTrackBorderRadius().value().ToString());
    }
    if (paintProperty->HasSelectedBorderRadius()) {
        DumpLog::GetInstance().AddDesc(
            "SelectedBorderRadius: " + paintProperty->GetSelectedBorderRadius().value().ToString());
    }
    if (layoutProperty->HasBlockSize()) {
        SizeT<Dimension> size = layoutProperty->GetBlockSize().value();
        std::stringstream ss;
        ss << "[" << size.Width().ToString() << " x " << size.Height().ToString() << "]";
        DumpLog::GetInstance().AddDesc("BlockSize: " + ss.str());
    }
    if (paintProperty->HasBlockType()) {
        DumpLog::GetInstance().AddDesc("BlockType: " + ToString(paintProperty->GetBlockType().value()));
    }
    if (paintProperty->HasBlockImage()) {
        DumpLog::GetInstance().AddDesc("BlockImage: " + paintProperty->GetBlockImage().value());
    }
    if (paintProperty->HasBlockShape()) {
        DumpLog::GetInstance().AddDesc(
            "BlockShape: " + ToString(paintProperty->GetBlockShape().value()->GetBasicShapeType()));
    }
    if (paintProperty->HasSliderInteractionMode()) {
        DumpLog::GetInstance().AddDesc(
            "SliderInteractionMode: " + ToString(paintProperty->GetSliderInteractionMode().value()));
    }
    if (paintProperty->HasValidSlideRange()) {
        DumpLog::GetInstance().AddDesc("SlideRange: " + paintProperty->GetValidSlideRange().value()->ToString());
    }
}

void SliderPattern::UpdateStepPointsAccessibilityText(
    RefPtr<FrameNode>& node, uint32_t nodeIndex, SliderModel::SliderShowStepOptions& options)
{
    CHECK_NULL_VOID(node);
    auto accessibilityProperty = node->GetAccessibilityProperty<TextAccessibilityProperty>();
    CHECK_NULL_VOID(accessibilityProperty);
    auto nodeProperty = node->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(nodeProperty);
    auto text = UtfUtils::Str16ToStr8(nodeProperty->GetContent().value_or(u""));
    if (options.find(nodeIndex) != options.end()) {
        text = options[nodeIndex];
    }
    accessibilityProperty->SetAccessibilityText(text);
    TAG_LOGD(AceLogTag::ACE_SELECT_COMPONENT,
        "Update step point, index:%{public}u, accessibility text:%{public}s.", nodeIndex, text.c_str());
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/linear_indicator/linear_indicator_pattern.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/progress/progress_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/pattern/linear_indicator/linear_indicator_accessibility_property.h"

namespace OHOS::Ace::NG {

RefPtr<LayoutProperty> LinearIndicatorPattern::CreateLayoutProperty()
{
    auto property = MakeRefPtr<LinearIndicatorLayoutProperty>();
    if (theme_) {
        property->UpdatePadding({ CalcLength(theme_->GetPaddingLeft()), CalcLength(theme_->GetPaddingRight()),
            CalcLength(theme_->GetPaddingTop()), CalcLength(theme_->GetPaddingBottom()) });
        property->UpdateSpace(theme_->GetDefaultSpace());
        property->UpdateUserDefinedIdealSize(CalcSize(std::nullopt, CalcLength(theme_->GetDefaultHeight())));
    }
    return property;
}

void LinearIndicatorPattern::OnModifyDone()
{
    LinearLayoutPattern::OnModifyDone();
    UpdateProgressNode();
    RegisterVisibleChange();
}

void LinearIndicatorPattern::UpdateProgressNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    RefPtr<LinearIndicatorLayoutProperty> layoutProperty = GetLayoutProperty<LinearIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    CHECK_NULL_VOID(theme_);
    std::size_t oldCount = GetProgressSize();
    std::size_t newCount = layoutProperty->GetProgressCountValue(theme_->GetDefaultProgressCount());
    if (oldCount > newCount) {
        for (std::size_t i = oldCount; i > newCount; --i) {
            host->RemoveChildAtIndex(i - 1);
        }
        oldCount = newCount;
    }
    if (IsChangeLayoutPropertyAndUpdate(layoutProperty)) {
        for (std::size_t i = 0; i < oldCount; ++i) {
            UpdateProgressNodeAtIndex(i);
        }
    }
    for (std::size_t i = oldCount; i < newCount; ++i) {
        AddProgressNode();
    }
    controller_->UpdateProgressSize(newCount);
    controller_->Loop(layoutProperty->GetLoopValue(theme_->GetDefaultLoop()));
}

bool LinearIndicatorPattern::IsChangeLayoutPropertyAndUpdate(RefPtr<LinearIndicatorLayoutProperty> layoutProperty)
{
    bool ret = false;
    CHECK_NULL_RETURN(layoutProperty, ret);
    CHECK_NULL_RETURN(theme_, ret);

    Dimension strokeWidth = layoutProperty->GetStrokeWidthValue(theme_->GetDefaultStrokeWidth());
    Dimension strokeRadius = layoutProperty->GetStrokeRadiusValue(theme_->GetDefaultStrokeRadius());
    Color trackBackgroundColor = layoutProperty->GetTrackBackgroundColorValue(theme_->GetTrackBackgroundColor());
    Color trackColor = layoutProperty->GetTrackColorValue(theme_->GetTrackColor());
    TextDirection direction = layoutProperty->GetLayoutDirection();

    float progressWidth = .0f;
    if (CalcProgressWidth(progressWidth) && GreatNotEqual(strokeWidth.ConvertToPx(), progressWidth)) {
        strokeWidth = Dimension(progressWidth, DimensionUnit::PX);
    }
    if (strokeWidth != strokeWidth_) {
        strokeWidth_ = strokeWidth;
        ret = true;
    }
    if (strokeRadius != strokeRadius_) {
        strokeRadius_ = strokeRadius;
        ret = true;
    }
    if (trackBackgroundColor != trackBackgroundColor_) {
        trackBackgroundColor_ = trackBackgroundColor;
        ret = true;
    }
    if (trackColor != trackColor_) {
        trackColor_ = trackColor;
        ret = true;
    }
    if (direction != direction_) {
        direction_ = direction;
        ret = true;
    }
    return ret;
}

void LinearIndicatorPattern::UpdateProgressNodeAtIndex(std::size_t index)
{
    auto progressNode = GetProgressNode(index);
    CHECK_NULL_VOID(progressNode);
    auto progressPaintProperty = progressNode->GetPaintProperty<NG::ProgressPaintProperty>();
    CHECK_NULL_VOID(progressPaintProperty);
    auto progressLayoutProperty = progressNode->GetLayoutProperty<ProgressLayoutProperty>();
    CHECK_NULL_VOID(progressLayoutProperty);
    progressPaintProperty->UpdateColor(trackColor_);
    progressPaintProperty->UpdateBackgroundColor(trackBackgroundColor_);
    progressLayoutProperty->UpdateStrokeWidth(strokeWidth_);
    progressPaintProperty->UpdateStrokeRadius(strokeRadius_);
    progressLayoutProperty->UpdateLayoutDirection(direction_);
    progressNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
}

void LinearIndicatorPattern::AddProgressNode()
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto progressNodeId = ElementRegister::GetInstance()->MakeUniqueId();
    auto progressNode = FrameNode::GetOrCreateFrameNode(
        V2::PROGRESS_ETS_TAG, progressNodeId, []() { return AceType::MakeRefPtr<ProgressPattern>(); });
    auto progressPaintProperty = progressNode->GetPaintProperty<NG::ProgressPaintProperty>();
    auto progressLayoutProperty = progressNode->GetLayoutProperty<ProgressLayoutProperty>();
    progressPaintProperty->UpdateColor(trackColor_);
    progressPaintProperty->UpdateBackgroundColor(trackBackgroundColor_);
    progressPaintProperty->UpdateEnableSmoothEffect(false);
    progressLayoutProperty->UpdateLayoutWeight(1);
    progressLayoutProperty->UpdateStrokeWidth(strokeWidth_);
    progressPaintProperty->UpdateStrokeRadius(strokeRadius_);
    progressLayoutProperty->UpdateLayoutDirection(direction_);
    host->AddChild(progressNode);
}

std::size_t LinearIndicatorPattern::GetProgressSize()
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, 0);
    return host->GetChildren().size();
}

RefPtr<FrameNode> LinearIndicatorPattern::GetProgressNode(int32_t index)
{
    auto host = GetHost();
    CHECK_NULL_RETURN(host, nullptr);
    return AceType::DynamicCast<FrameNode>(host->GetChildAtIndex(index));
}

void LinearIndicatorPattern::RegisterVisibleChange()
{
    if (hasVisibleChangeRegistered_) {
        return;
    }
    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto host = GetHost();
    CHECK_NULL_VOID(host);

    auto callback = [weak = WeakClaim(this)](bool visible, double ratio) {
        auto pattern = weak.Upgrade();
        CHECK_NULL_VOID(pattern);
        pattern->VisibleChange(visible);
    };
    std::vector<double> ratioList = { 0.0 };
    pipeline->AddVisibleAreaChangeNode(host, ratioList, std::move(callback), false);
    hasVisibleChangeRegistered_ = true;
}

void LinearIndicatorPattern::VisibleChange(bool visible)
{
    if (visible) {
        if (isVisibleChangePause_) {
            isVisibleChangePause_ = false;
            controller_->Start(controller_->TotalAnimationTime(), controller_->TotalIntervalTime());
        }
    } else {
        if (controller_->IsRuning()) {
            isVisibleChangePause_ = true;
            controller_->Pause();
        }
    }
}

bool LinearIndicatorPattern::CalcProgressWidth(float& progressWidth)
{
    CHECK_NULL_RETURN(theme_, false);
    auto layoutProperty = GetLayoutProperty<LinearIndicatorLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);

    auto contentSize = GetHostFrameSize();
    CHECK_NULL_RETURN(contentSize, false);

    float width = contentSize->Width();
    if (NearZero(width)) {
        return false;
    }
    std::size_t progressCount = layoutProperty->GetProgressCount().value_or(theme_->GetDefaultProgressCount());
    if (progressCount == 0) {
        return false;
    }

    PaddingPropertyF padding = layoutProperty->CreatePaddingAndBorder();
    float leftPadding = padding.left.value_or(theme_->GetPaddingLeft().ConvertToPx());
    float rightPadding = padding.right.value_or(theme_->GetPaddingRight().ConvertToPx());
    float space = layoutProperty->GetSpace().value_or(theme_->GetDefaultSpace()).ConvertToPx();

    float ret = (width - leftPadding - rightPadding - (space * (progressCount - 1))) / progressCount;
    progressWidth = std::clamp(ret, .0f, width);
    return true;
}

void LinearIndicatorPattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<LinearIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);

    DumpLog::GetInstance().AddDesc(std::string("indicatorStyle.space"),
        layoutProperty->GetSpaceValue(theme->GetDefaultSpace()).ToString().c_str());
    DumpLog::GetInstance().AddDesc(std::string("indicatorStyle.strokeWidth"),
        layoutProperty->GetStrokeWidthValue(theme->GetDefaultStrokeWidth()).ToString().c_str());
    DumpLog::GetInstance().AddDesc(std::string("indicatorStyle.strokeRadius"),
        layoutProperty->GetStrokeRadiusValue(theme->GetDefaultStrokeRadius()).ToString().c_str());
    DumpLog::GetInstance().AddDesc(std::string("indicatorStyle.trackBackgroundColor"),
        layoutProperty->GetTrackBackgroundColorValue(theme->GetTrackBackgroundColor()).ColorToString().c_str());
    DumpLog::GetInstance().AddDesc(std::string("indicatorStyle.trackColor"),
        layoutProperty->GetTrackColorValue(theme->GetTrackColor()).ColorToString().c_str());

    DumpLog::GetInstance().AddDesc(
        std::string("indicatorLoop"), layoutProperty->GetLoopValue(theme->GetDefaultLoop()) ? "True" : "False");
    DumpLog::GetInstance().AddDesc(
        std::string("count"), layoutProperty->GetProgressCountValue(theme->GetDefaultProgressCount()));
}

void LinearIndicatorPattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<LinearIndicatorLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto theme = pipeline->GetThemeManager()->GetTheme<NG::LinearIndicatorTheme>();
    CHECK_NULL_VOID(theme);
    json->Put("indicatorStyle.space", layoutProperty->GetSpaceValue(theme->GetDefaultSpace()).ToString().c_str());
    json->Put("indicatorStyle.strokeWidth",
        layoutProperty->GetStrokeWidthValue(theme->GetDefaultStrokeWidth()).ToString().c_str());
    json->Put("indicatorStyle.strokeRadius",
        layoutProperty->GetStrokeRadiusValue(theme->GetDefaultStrokeRadius()).ToString().c_str());
    json->Put("indicatorStyle.trackBackgroundColor",
        layoutProperty->GetTrackBackgroundColorValue(theme->GetTrackBackgroundColor()).ColorToString().c_str());
    json->Put("indicatorStyle.trackColor",
        layoutProperty->GetTrackColorValue(theme->GetTrackColor()).ColorToString().c_str());

    json->Put("indicatorLoop", layoutProperty->GetLoopValue(theme->GetDefaultLoop()) ? "True" : "False");
    json->Put("count", layoutProperty->GetProgressCountValue(theme->GetDefaultProgressCount()));
}

RefPtr<AccessibilityProperty> LinearIndicatorPattern::CreateAccessibilityProperty()
{
    return MakeRefPtr<LinearIndicatorAccessibilityProperty>();
}
} // namespace OHOS::Ace::NG

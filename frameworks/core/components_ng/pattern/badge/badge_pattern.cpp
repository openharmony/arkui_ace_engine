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

#include "core/components_ng/pattern/badge/badge_pattern.h"

#include "core/components/badge/badge_theme.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_v2/inspector/utils.h"

namespace OHOS::Ace::NG {

void BadgePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        return;
    }

    auto needCreateText = false;
    auto lastFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back());
    if (lastFrameNode) {
        needCreateText = lastFrameNode->GetId() != textNodeId_;
    } else {
        auto lastUINode = AceType::DynamicCast<UINode>(frameNode->GetChildren().back());
        CHECK_NULL_VOID(lastUINode);
        needCreateText = true;
    }
    if (needCreateText) {
        textNodeId_ = ElementRegister::GetInstance()->MakeUniqueId();
        lastFrameNode = FrameNode::GetOrCreateFrameNode(
            V2::TEXT_ETS_TAG, textNodeId_, []() { return AceType::MakeRefPtr<TextPattern>(); });
        CHECK_NULL_VOID(lastFrameNode);
        lastFrameNode->MountToParent(frameNode);
    }

    auto textLayoutProperty = lastFrameNode->GetLayoutProperty<TextLayoutProperty>();
    CHECK_NULL_VOID(textLayoutProperty);
    auto layoutProperty = frameNode->GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    bool badgeVisible = false;
    if (badgeCount.has_value()) {
        if (badgeCount.value() > 0) {
            const int32_t maxCountNum = 99;
            auto badgeMaxCount = layoutProperty->GetBadgeMaxCount().value_or(maxCountNum);
            auto maxCount = badgeMaxCount;
            auto content = std::to_string(badgeCount.value());
            if (badgeCount.value() > maxCount) {
                content = std::to_string(maxCount) + "+";
            }
            textLayoutProperty->UpdateContent(content);
            TAG_LOGD(AceLogTag::ACE_BADGE, "BadgeContent: %{public}s", content.c_str());
            badgeVisible = true;
        } else {
            textLayoutProperty->ResetContent();
        }
    }

    if (layoutProperty->GetBadgeFontWeight().has_value()) {
        textLayoutProperty->UpdateFontWeight(layoutProperty->GetBadgeFontWeightValue());
    }

    if (badgeValue.has_value()) {
        textLayoutProperty->UpdateContent(badgeValue.value());
        if (badgeValue.value().empty()) {
            TAG_LOGI(AceLogTag::ACE_BADGE, "Badge content is empty");
            textLayoutProperty->UpdateContent(u" ");
        }
        badgeVisible = true;
    }
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);
    Dimension width = layoutProperty->GetBadgeBorderWidthValue(badgeTheme->GetBadgeBorderWidth());
    Dimension outerWidth = layoutProperty->GetBadgeOuterBorderWidthValue(badgeTheme->GetBadgeOuterBorderWidth());
    if (LessOrEqual(circleSize->ConvertToPx(), 0)) {
        badgeVisible = true;
        width.Reset();
        outerWidth.Reset();
    }
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    textLayoutProperty->UpdateTextColor(badgeTextColor.value_or(badgeTheme->GetBadgeTextColor()));

    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    if (badgeFontSize.has_value()) {
        textLayoutProperty->UpdateFontSize(badgeFontSize.value());
    }

    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);

    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(width);
    textLayoutProperty->UpdateBorderWidth(borderWidth);
    auto badgeColor = layoutProperty->GetBadgeColorValue(badgeTheme->GetBadgeColor());
    auto textRenderContext = lastFrameNode->GetRenderContext();
    CHECK_NULL_VOID(textRenderContext);
    textRenderContext->SetVisible(badgeVisible);
    textRenderContext->UpdateBackgroundColor(badgeColor);
    BorderWidthProperty outerBorderWidth;
    outerBorderWidth.SetBorderWidth(outerWidth);
    textLayoutProperty->UpdateOuterBorderWidth(outerBorderWidth);
    textRenderContext->UpdateOuterBorderWidth(outerBorderWidth);

    Color color = layoutProperty->GetBadgeBorderColorValue(badgeTheme->GetBadgeBorderColor());
    BorderColorProperty borderColor;
    borderColor.SetColor(color);
    textRenderContext->UpdateBorderColor(borderColor);

    BorderColorProperty outerBorderColor;
    Color outColor = layoutProperty->GetBadgeOuterBorderColorValue(badgeTheme->GetBadgeOuterBorderColor());
    outerBorderColor.SetColor(outColor);
    textRenderContext->UpdateOuterBorderColor(outerBorderColor);
    lastFrameNode->MarkModifyDone();
}

void BadgePattern::BorderDumpInfo()
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeBorderColor = layoutProperty->GetBadgeBorderColor();
    auto badgeBorderWidth = layoutProperty->GetBadgeBorderWidth();
    auto badgeOuterBorderColor = layoutProperty->GetBadgeOuterBorderColor();
    auto badgeOuterBorderWidth = layoutProperty->GetBadgeOuterBorderWidth();

    if (badgeBorderColor.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("badgeBorderColor: ").append(badgeBorderColor.value().ToString()));
    }
    if (badgeBorderWidth.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("badgeBorderWidth: ").append(badgeBorderWidth.value().ToString()));
    }
    if (badgeOuterBorderColor.has_value()) {
        DumpLog::GetInstance().AddDesc(
            std::string("badgeOuterBorderColor: ").append(badgeOuterBorderColor.value().ToString()));
    }
    if (badgeOuterBorderWidth.has_value()) {
        DumpLog::GetInstance().AddDesc(
            std::string("badgeOuterBorderWidth: ").append(badgeOuterBorderWidth.value().ToString()));
    }
}

void BadgePattern::BorderDumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeBorderColor = layoutProperty->GetBadgeBorderColor();
    auto badgeBorderWidth = layoutProperty->GetBadgeBorderWidth();
    auto badgeOuterBorderColor = layoutProperty->GetBadgeOuterBorderColor();
    auto badgeOuterBorderWidth = layoutProperty->GetBadgeOuterBorderWidth();

    if (badgeBorderColor.has_value()) {
        json->Put("badgeBorderColor", badgeBorderColor.value().ToString().c_str());
    }
    if (badgeBorderWidth.has_value()) {
        json->Put("badgeBorderWidth", badgeBorderWidth.value().ToString().c_str());
    }
    if (badgeOuterBorderColor.has_value()) {
        json->Put("badgeOuterBorderColor", badgeOuterBorderColor.value().ToString().c_str());
    }
    if (badgeOuterBorderWidth.has_value()) {
        json->Put("badgeOuterBorderWidth", badgeOuterBorderWidth.value().ToString().c_str());
    }
}

void BadgePattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    auto badgePosition = layoutProperty->GetBadgePosition();
    auto badgeColor = layoutProperty->GetBadgeColor();
    auto badgeFontWeight = layoutProperty->GetBadgeFontWeight();
    if (badgeCount.has_value()) {
        const int32_t maxCountNum = 99;
        auto badgeMaxCount = layoutProperty->GetBadgeMaxCount().value_or(maxCountNum);
        DumpLog::GetInstance().AddDesc(std::string("badgeCount: ").append(std::to_string(badgeCount.value())));
        DumpLog::GetInstance().AddDesc(std::string("badgeMaxCount: ").append(std::to_string(badgeMaxCount)));
    }
    if (badgeValue.has_value()) {
        if (badgeValue.value().empty()) {
            DumpLog::GetInstance().AddDesc(std::string("badgeValue is empty"));
        } else {
            DumpLog::GetInstance().AddDesc(std::string("badgeValue: ").append(badgeValue.value()));
        }
    }
    if (badgePosition.has_value()) {
        auto badgePositionString = layoutProperty->GetBadgePositionString(badgePosition.value());
        DumpLog::GetInstance().AddDesc(std::string("badgePosition: ").append(badgePositionString));
    }
    if (badgeTextColor.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("badgeTextColor: ").append(badgeTextColor.value().ToString()));
    }
    if (circleSize.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("circleSize: ").append(std::to_string(circleSize->ConvertToPx())));
    }
    if (badgeFontSize.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("badgeFontSize: ").append(badgeFontSize.value().ToString()));
    }
    if (badgeColor.has_value()) {
        DumpLog::GetInstance().AddDesc(std::string("badgeColor: ").append(badgeColor.value().ToString()));
    }
    if (badgeFontWeight.has_value()) {
        DumpLog::GetInstance().AddDesc(
            std::string("badgeFontWeight: ").append(V2::ConvertWrapFontWeightToStirng(badgeFontWeight.value())));
    }
    BorderDumpInfo();
}

void BadgePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    auto badgePosition = layoutProperty->GetBadgePosition();
    auto badgeColor = layoutProperty->GetBadgeColor();
    auto badgeFontWeight = layoutProperty->GetBadgeFontWeight();
    if (badgeCount.has_value()) {
        const int32_t maxCountNum = 99;
        auto badgeMaxCount = layoutProperty->GetBadgeMaxCount().value_or(maxCountNum);
        json->Put("badgeCount", std::to_string(badgeCount.value()).c_str());
        json->Put("badgeMaxCount", std::to_string(badgeMaxCount).c_str());
    }
    if (badgeValue.has_value()) {
        if (badgeValue.value().empty()) {
            json->Put("badgeValue", "");
        } else {
            json->Put("badgeValue", badgeValue.value().c_str());
        }
    }
    if (badgePosition.has_value()) {
        auto badgePositionString = layoutProperty->GetBadgePositionString(badgePosition.value());
        json->Put("badgePosition", badgePositionString.c_str());
    }
    if (badgeTextColor.has_value()) {
        json->Put("badgeTextColor", badgeTextColor.value().ToString().c_str());
    }
    if (circleSize.has_value()) {
        json->Put("circleSize", std::to_string(circleSize->ConvertToPx()).c_str());
    }
    if (badgeFontSize.has_value()) {
        json->Put("badgeFontSize", badgeFontSize.value().ToString().c_str());
    }
    if (badgeColor.has_value()) {
        json->Put("badgeColor", badgeColor.value().ToString().c_str());
    }
    if (badgeFontWeight.has_value()) {
        json->Put("badgeFontWeight", V2::ConvertWrapFontWeightToStirng(badgeFontWeight.value()).c_str());
    }
    BorderDumpInfo(json);
}

void BadgePattern::DumpSimplifyInfo(std::shared_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    if (badgeCount.has_value()) {
        const int32_t maxCountNum = 99;
        auto badgeMaxCount = layoutProperty->GetBadgeMaxCount().value_or(maxCountNum);
        if (badgeCount.value() != 0) {
            json->Put("BadgeCount", std::to_string(badgeCount.value()).c_str());
        }
        if (badgeMaxCount != 0) {
            json->Put("BadgeMaxCount", std::to_string(badgeMaxCount).c_str());
        }
    }
    if (badgeValue.has_value() && !badgeValue.value().empty()) {
        json->Put("BadgeValue", badgeValue.value().c_str());
    }
    if (badgeTextColor.has_value() && badgeTextColor.value() != Color::BLACK) {
        json->Put("BadgeTextColor", badgeTextColor.value().ToString().c_str());
    }
    if (circleSize && circleSize != Dimension(0.0, circleSize->Unit())) {
        json->Put("CircleSize", std::to_string(circleSize->ConvertToPx()).c_str());
    }
    if (badgeFontSize.has_value() && badgeFontSize.value() != Dimension(0.0, badgeFontSize.value().Unit())) {
        json->Put("BadgeFontSize", badgeFontSize.value().ToString().c_str());
    }
}

void BadgePattern::UpdateBadgeValue(const std::string& badgeValue, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeValue(badgeValue);
    }
}

void BadgePattern::UpdateColor(const Color& color, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeTextColor(color);
    }
}

void BadgePattern::UpdateBadgeColor(const Color& badgeColor, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeColor(badgeColor);
    }
}

void BadgePattern::UpdateBorderColor(const Color& borderColor, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeBorderColor(borderColor);
    }
}

void BadgePattern::UpdateOuterBorderColor(const Color& outerBorderColor, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeOuterBorderColor(outerBorderColor);
    }
}

void BadgePattern::UpdateFontWeight(FontWeight fontWeight, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeFontWeight(fontWeight);
    }
    if (host->GetRerenderable()) {
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void BadgePattern::UpdateFontSize(const CalcDimension& fontSize, bool isDefaultFontSize, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeFontSize(fontSize);
        auto originFontSizeFlag = layoutProperty->GetFontSizeIsDefault();
        auto originBadgeSize = layoutProperty->GetBadgeSizeIsDefault();
        if (originFontSizeFlag != isDefaultFontSize) {
            layoutProperty->SetIsDefault(isDefaultFontSize, originBadgeSize);
        }
    }
}

void BadgePattern::UpdateBadgeCircleSize(
    const CalcDimension& badgeCircleSize, bool isDefaultBadgeSize, bool isFirstLoad)
{
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        auto originFontSizeFlag = layoutProperty->GetFontSizeIsDefault();
        auto originBadgeSize = layoutProperty->GetBadgeSizeIsDefault();
        layoutProperty->UpdateBadgeCircleSize(badgeCircleSize);
        if (originBadgeSize != isDefaultBadgeSize) {
            layoutProperty->SetIsDefault(originFontSizeFlag, isDefaultBadgeSize);
        }
    }
}

void BadgePattern::OnColorModeChange(uint32_t colorMode)
{
    Pattern::OnColorModeChange(colorMode);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (host->GetRerenderable()) {
        host->MarkModifyDone();
        host->MarkDirtyNode(PROPERTY_UPDATE_MEASURE_SELF);
    }
}

void BadgePattern::UpdateBadgePositionX(const CalcDimension& positionX, bool isFirstLoad)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgePositionX(positionX);
    }
}

void BadgePattern::UpdateBadgePositionY(const CalcDimension& positionY, bool isFirstLoad)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgePositionY(positionY);
    }
}

void BadgePattern::UpdateBorderWidth(const CalcDimension& borderWidth, bool isFirstLoad)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeBorderWidth(borderWidth);
    }
}

void BadgePattern::UpdateOuterBorderWidth(const CalcDimension& outerBorderWidth, bool isFirstLoad)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipelineContext = host->GetContext();
    CHECK_NULL_VOID(pipelineContext);
    if (pipelineContext->IsSystmColorChange() || isFirstLoad) {
        layoutProperty->UpdateBadgeOuterBorderWidth(outerBorderWidth);
    }
}

void BadgePattern::OnColorConfigurationUpdate()
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto host = GetHost();
    CHECK_NULL_VOID(host);
    auto pipeline = host->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (!layoutProperty->GetBadgePositionXByuser().value_or(false)) {
        UpdateBadgePositionX(badgeTheme->GetBadgePositionX());
    }
    if (!layoutProperty->GetBadgePositionYByuser().value_or(false)) {
        UpdateBadgePositionY(badgeTheme->GetBadgePositionY());
    }
    if (!layoutProperty->GetBadgeFontSizeByuser().value_or(false)) {
        UpdateFontSize(badgeTheme->GetBadgeFontSize(), true);
    }

    if (!layoutProperty->GetBadgeCircleSizeByuser().value_or(false)) {
        UpdateBadgeCircleSize(badgeTheme->GetBadgeCircleSize(), true);
    }
    if (!layoutProperty->GetBadgeOuterBorderColorByuser().value_or(false)) {
        UpdateOuterBorderColor(badgeTheme->GetBadgeOuterBorderColor());
    }
    if (!layoutProperty->GetBadgeBorderColorByuser().value_or(false)) {
        UpdateBorderColor(badgeTheme->GetBadgeBorderColor());
    }
    if (!layoutProperty->GetBadgeBorderWidthByuser().value_or(false)) {
        UpdateBorderWidth(badgeTheme->GetBadgeBorderWidth());
    }
    if (!layoutProperty->GetBadgeOuterBorderWidthByuser().value_or(false)) {
        UpdateOuterBorderWidth(badgeTheme->GetBadgeOuterBorderWidth());
    }
    if (!layoutProperty->GetBadgeTextColorByuser().value_or(false)) {
        UpdateColor(badgeTheme->GetBadgeTextColor());
    }
    if (!layoutProperty->GetBadgeColorByuser().value_or(false)) {
        UpdateBadgeColor(badgeTheme->GetBadgeColor());
    }
}
} // namespace OHOS::Ace::NG

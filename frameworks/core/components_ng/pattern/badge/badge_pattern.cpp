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

namespace OHOS::Ace::NG {

void BadgePattern::OnModifyDone()
{
    Pattern::OnModifyDone();
    auto frameNode = GetHost();
    CHECK_NULL_VOID(frameNode);
    if (frameNode->GetChildren().empty()) {
        return;
    }

    auto lastFrameNode = AceType::DynamicCast<FrameNode>(frameNode->GetChildren().back());
    CHECK_NULL_VOID(lastFrameNode);
    if (lastFrameNode->GetId() != textNodeId_) {
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
            if (badgeCount.value() > maxCount) {
                badgeCount.value() = maxCount;
                textLayoutProperty->UpdateContent(std::to_string(badgeCount.value()) + "+");
            } else {
                textLayoutProperty->UpdateContent(std::to_string(badgeCount.value()));
            }
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
            textLayoutProperty->UpdateContent(" ");
        }
        badgeVisible = true;
    }
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto pipeline = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto badgeTheme = pipeline->GetTheme<BadgeTheme>();
    CHECK_NULL_VOID(badgeTheme);
    Dimension width = layoutProperty->GetBadgeBorderWidthValue(badgeTheme->GetBadgeBorderWidth());
    if (LessOrEqual(circleSize->ConvertToPx(), 0)) {
        badgeVisible = true;
        width.Reset();
    }
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    textLayoutProperty->UpdateTextColor(badgeTextColor.value());

    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
    if (badgeFontSize.has_value()) {
        textLayoutProperty->UpdateFontSize(badgeFontSize.value());
    }

    textLayoutProperty->UpdateMaxLines(1);
    textLayoutProperty->UpdateTextAlign(TextAlign::CENTER);

    BorderWidthProperty borderWidth;
    borderWidth.SetBorderWidth(width);
    textLayoutProperty->UpdateBorderWidth(borderWidth);
    auto badgeColor = layoutProperty->GetBadgeColorValue();
    auto textRenderContext = lastFrameNode->GetRenderContext();
    textRenderContext->SetVisible(badgeVisible);
    textRenderContext->UpdateBackgroundColor(badgeColor);

    Color color = layoutProperty->GetBadgeBorderColorValue(badgeTheme->GetBadgeBorderColor());
    BorderColorProperty borderColor;
    borderColor.SetColor(color);
    textRenderContext->UpdateBorderColor(borderColor);
    lastFrameNode->MarkModifyDone();
}

void BadgePattern::DumpInfo()
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
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
    DumpLog::GetInstance().AddDesc(std::string("badgeTextColor: ").append(badgeTextColor.value().ToString()));
    DumpLog::GetInstance().AddDesc(std::string("circleSize: ").append(std::to_string(circleSize->ConvertToPx())));
    DumpLog::GetInstance().AddDesc(std::string("badgeFontSize: ").append(badgeFontSize.value().ToString()));
}

void BadgePattern::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    auto layoutProperty = GetLayoutProperty<BadgeLayoutProperty>();
    auto badgeCount = layoutProperty->GetBadgeCount();
    auto badgeValue = layoutProperty->GetBadgeValue();
    auto circleSize = layoutProperty->GetBadgeCircleSize();
    auto badgeTextColor = layoutProperty->GetBadgeTextColor();
    auto badgeFontSize = layoutProperty->GetBadgeFontSize();
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
    json->Put("badgeTextColor", badgeTextColor.value().ToString().c_str());
    json->Put("circleSize", std::to_string(circleSize->ConvertToPx()).c_str());
    json->Put("badgeFontSize", badgeFontSize.value().ToString().c_str());
}
} // namespace OHOS::Ace::NG

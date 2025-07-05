/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/divider/divider_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/pattern/divider/divider_pattern.h"

namespace OHOS::Ace::NG {

void DividerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::DIVIDER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });
    stack->Push(frameNode);
}

RefPtr<FrameNode> DividerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::DIVIDER_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<DividerPattern>(); });

    return frameNode;
}

void DividerModelNG::Vertical(bool value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DividerLayoutProperty, Vertical, value);
}

void DividerModelNG::DividerColor(const Color& value)
{
    ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, value);
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, true);
    }
}

void DividerModelNG::ResetResObj(const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto dividerPattern = frameNode->GetPattern<DividerPattern>();
    CHECK_NULL_VOID(dividerPattern);
    dividerPattern->RemoveResObj(key);
}

void DividerModelNG::DividerColor(const RefPtr<ResourceObject>& resObj)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);

    auto dividerPattern = frameNode->GetPattern<DividerPattern>();
    CHECK_NULL_VOID(dividerPattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto dividerPattern = frameNode->GetPattern<DividerPattern>();
        CHECK_NULL_VOID(dividerPattern);
        std::string dividerColor = dividerPattern->GetResCacheMapByKey("divider.color");
        Color result;
        if (dividerColor.empty()) {
            ResourceParseUtils::ParseResColor(resObj, result);
            dividerPattern->AddResCache("divider.color", result.ColorToString());
        } else {
            result = Color::ColorFromString(dividerColor);
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, result, frameNode);
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, true, frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    updateFunc(resObj);
    dividerPattern->AddResObj("divider.color", resObj, std::move(updateFunc));
}

void DividerModelNG::StrokeWidth(const Dimension& value)
{
    ACE_UPDATE_LAYOUT_PROPERTY(DividerLayoutProperty, StrokeWidth, value);
}

void DividerModelNG::LineCap(const Ace::LineCap& value)
{
    ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, LineCap, value);
}

void DividerModelNG::StrokeWidth(FrameNode* frameNode, std::optional<Dimension> valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(DividerLayoutProperty, StrokeWidth, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_LAYOUT_PROPERTY(DividerLayoutProperty, StrokeWidth, frameNode);
    }
}

void DividerModelNG::LineCap(FrameNode* frameNode, const std::optional<enum LineCap> valueOpt)
{
    if (valueOpt) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, LineCap, valueOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DividerRenderProperty, LineCap, frameNode);
    }
}

void DividerModelNG::SetDividerColor(FrameNode* frameNode, std::optional<Color> colorOpt, bool isSetByTheme)
{
    if (colorOpt) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, colorOpt.value(), frameNode);
    } else {
        ACE_RESET_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, frameNode);
    }
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, isSetByTheme, frameNode);
    }
}

void DividerModelNG::SetDividerColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj, bool isSetByTheme)
{
    CHECK_NULL_VOID(frameNode);
    auto dividerPattern = frameNode->GetPattern<DividerPattern>();
    CHECK_NULL_VOID(dividerPattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto dividerPattern = frameNode->GetPattern<DividerPattern>();
        CHECK_NULL_VOID(dividerPattern);
        std::string dividerColor = dividerPattern->GetResCacheMapByKey("divider.color");
        Color result;
        if (dividerColor.empty()) {
            ResourceParseUtils::ParseResColor(resObj, result);
            dividerPattern->AddResCache("divider.color", result.ColorToString());
        } else {
            result = Color::ColorFromString(dividerColor);
        }
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColor, result, frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_RENDER);
    };
    updateFunc(resObj);
    dividerPattern->AddResObj("divider.color", resObj, std::move(updateFunc));
    ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, isSetByTheme, frameNode);
}

void DividerModelNG::ResetResObj(FrameNode* frameNode, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto dividerPattern = frameNode->GetPattern<DividerPattern>();
    CHECK_NULL_VOID(dividerPattern);
    dividerPattern->RemoveResObj(key);
}

void DividerModelNG::SetVertical(FrameNode* frameNode, const bool& value)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(DividerLayoutProperty, Vertical, value, frameNode);
}

void DividerModelNG::ResetDividerColor()
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, false);
    }
    ACE_RESET_PAINT_PROPERTY_WITH_FLAG(DividerRenderProperty, DividerColor, PROPERTY_UPDATE_RENDER);
}

void DividerModelNG::ResetDividerColor(FrameNode* frameNode)
{
    if (SystemProperties::ConfigChangePerform()) {
        ACE_UPDATE_NODE_PAINT_PROPERTY(DividerRenderProperty, DividerColorSetByUser, false, frameNode);
    }
    ACE_RESET_NODE_PAINT_PROPERTY_WITH_FLAG(DividerRenderProperty, DividerColor, PROPERTY_UPDATE_RENDER, frameNode);
}
} // namespace OHOS::Ace::NG
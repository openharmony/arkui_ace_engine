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

#include "core/components_ng/pattern/relative_container/relative_container_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/relative_container/relative_container_pattern.h"

namespace OHOS::Ace::NG {
void RelativeContainerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    int32_t nodeId = stack->ClaimNodeId();
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    ViewStackProcessor::GetInstance()->Push(frameNode);
}

void RelativeContainerModelNG::SetBarrier(const std::vector<BarrierInfo>& barrierInfo)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    ACE_UPDATE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Barrier, barrierInfo);
}

void RelativeContainerModelNG::SetGuideline(const std::vector<GuidelineInfo>& guidelineInfo)
{
    if (!ViewStackProcessor::GetInstance()->IsCurrentVisualStateProcess()) {
        return;
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<OHOS::Ace::NG::RelativeContainerPattern>();
        CHECK_NULL_VOID(pattern);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [guidelineInfo, weak = AceType::WeakClaim(frameNode)](
                                const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            std::vector<GuidelineInfo> &guidelineInfoValue = const_cast<std::vector<GuidelineInfo> &>(guidelineInfo);
            for (size_t i = 0; i < guidelineInfoValue.size(); i++) {
                guidelineInfoValue[i].ReloadResources();
            }
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Guideline, guidelineInfoValue, frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        pattern->AddResObj("relativeContainer.guideLine", resObj, std::move(updateFunc));
    }
    ACE_UPDATE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Guideline, guidelineInfo);
}

void RelativeContainerModelNG::ResetResObj(const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<OHOS::Ace::NG::RelativeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

RefPtr<FrameNode> RelativeContainerModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::RELATIVE_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<OHOS::Ace::NG::RelativeContainerPattern>(); });
    CHECK_NULL_RETURN(frameNode, frameNode);
    return frameNode;
}

void RelativeContainerModelNG::SetBarrier(FrameNode* frameNode, const std::vector<BarrierInfo>& barrierInfo)
{
    CHECK_NULL_VOID(frameNode);
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Barrier, barrierInfo, frameNode);
}

void RelativeContainerModelNG::SetGuideline(FrameNode* frameNode, const std::vector<GuidelineInfo>& guidelineInfo)
{
    CHECK_NULL_VOID(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern<OHOS::Ace::NG::RelativeContainerPattern>();
        CHECK_NULL_VOID(pattern);
        RefPtr<ResourceObject> resObj = AceType::MakeRefPtr<ResourceObject>("", "", -1);
        auto&& updateFunc = [guidelineInfo, weak = AceType::WeakClaim(frameNode)](
                                const RefPtr<ResourceObject>& resObj) {
            auto frameNode = weak.Upgrade();
            CHECK_NULL_VOID(frameNode);
            std::vector<GuidelineInfo>& guidelineInfoValue = const_cast<std::vector<GuidelineInfo>&>(guidelineInfo);
            for (size_t i = 0; i < guidelineInfoValue.size(); i++) {
                guidelineInfoValue[i].ReloadResources();
            }
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Guideline, guidelineInfoValue, frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        };
        pattern->AddResObj("relativeContainer.guideLine", resObj, std::move(updateFunc));
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Guideline, guidelineInfo, frameNode);
}

void RelativeContainerModelNG::ResetResObj(FrameNode* frameNode, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<OHOS::Ace::NG::RelativeContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void RelativeContainerModelNG::SetPositionResObj(
    const RefPtr<ResourceObject>& ResObj, GuidelineInfo& guidelineInfoItem, const std::string key)
{
    if (SystemProperties::ConfigChangePerform() && ResObj) {
        auto&& updateFunc = [key](const RefPtr<ResourceObject>& resObj, GuidelineInfo& guidelineInfo) {
            CalcDimension result;
            ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
            if (key == "relativeContainer.guideLine.position.start") {
                guidelineInfo.start = result;
            } else if (key == "relativeContainer.guideLine.position.end") {
                guidelineInfo.end = result;
            }
        };
        guidelineInfoItem.AddResource(key, ResObj, std::move(updateFunc));
    }
}

std::vector<BarrierInfo> RelativeContainerModelNG::GetBarrier(FrameNode* frameNode)
{
    std::vector<BarrierInfo> value;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(RelativeContainerLayoutProperty, Barrier, value, frameNode, value);
    return value;
}

std::vector<GuidelineInfo> RelativeContainerModelNG::GetGuideline(FrameNode* frameNode)
{
    std::vector<GuidelineInfo> value;
    CHECK_NULL_RETURN(frameNode, value);
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(
        RelativeContainerLayoutProperty, Guideline, value, frameNode, value);
    return value;
}

void RelativeContainerModelNG::ResetGuideline(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Guideline, frameNode);
}

void RelativeContainerModelNG::ResetBarrier(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    ACE_RESET_NODE_LAYOUT_PROPERTY(RelativeContainerLayoutProperty, Barrier, frameNode);
}
} // namespace OHOS::Ace::NG
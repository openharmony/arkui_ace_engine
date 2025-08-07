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

#include "core/components_ng/pattern/linear_layout/column_model_ng.h"

#include "core/common/resource/resource_parse_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"

namespace OHOS::Ace::NG {

void ColumnModelNG::Create(const std::optional<Dimension>& space, AlignDeclaration*, const std::string&)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::COLUMN_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, FlexDirection, FlexDirection::COLUMN);

    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, space.value());
    }
}

void ColumnModelNG::Create(const RefPtr<ResourceObject>& spaceResObj, AlignDeclaration*, const std::string&)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::COLUMN_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, FlexDirection, FlexDirection::COLUMN);

    CHECK_NULL_VOID(spaceResObj);
    auto pattern = frameNode->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(AceType::RawPtr(frameNode))](
        const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<LinearLayoutPattern>();
        CHECK_NULL_VOID(pattern);
        std::string columnString = pattern->GetResCacheMapByKey("column.space");
        CalcDimension value;
        if (columnString.empty()) {
            ResourceParseUtils::ParseResDimensionVp(resObj, value);
            pattern->AddResCache("column.space", value.ToString());
        } else {
            value = StringUtils::StringToCalcDimension(columnString);
        }
        if (GreatOrEqual(value.Value(), 0.0)) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, value, frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        }
    };
    pattern->AddResObj("column.space", spaceResObj, std::move(updateFunc));
    CalcDimension value;
    ResourceParseUtils::ParseResDimensionVp(spaceResObj, value);
    if (GreatOrEqual(value.Value(), 0.0)) {
        ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, value);
    }
}

void ColumnModelNG::SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space)
{
    CHECK_NULL_VOID(space);
    if (GreatOrEqual(space->Value(), 0.0)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, space.value(), frameNode);
    } else {
        LOGE("Column: the space value is illegal due to space is less than zero");
    }
}

void ColumnModelNG::SetSpace(FrameNode* frameNode, const RefPtr<ResourceObject>& spaceResObj)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {
        auto frameNode = weak.Upgrade();
        CHECK_NULL_VOID(frameNode);
        auto pattern = frameNode->GetPattern<LinearLayoutPattern>();
        CHECK_NULL_VOID(pattern);
        std::string columnString = pattern->GetResCacheMapByKey("column.space");
        CalcDimension value;
        if (columnString.empty()) {
            ResourceParseUtils::ParseResDimensionVp(resObj, value);
            pattern->AddResCache("column.space", value.ToString());
        } else {
            value = StringUtils::StringToCalcDimension(columnString);
        }
        if (GreatOrEqual(value.Value(), 0.0)) {
            ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, value, frameNode);
            frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        } else {
            ACE_RESET_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, frameNode);
        }
    };
    pattern->AddResObj("column.space", spaceResObj, std::move(updateFunc));
    CalcDimension value;
    ResourceParseUtils::ParseResDimensionVp(spaceResObj, value);
    if (GreatOrEqual(value.Value(), 0.0)) {
        ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, Space, value, frameNode);
    }
}

RefPtr<FrameNode> ColumnModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FrameNode::CreateFrameNode(
        V2::COLUMN_ETS_TAG, nodeId, AceType::MakeRefPtr<LinearLayoutPattern>(true));
    auto castLinearLayoutProperty = frameNode->GetLayoutProperty<LinearLayoutProperty>();
    if (castLinearLayoutProperty) {
        castLinearLayoutProperty->UpdateFlexDirection(FlexDirection::COLUMN);
    }
    return frameNode;
}

void ColumnModelNG::ResetResObj(FrameNode* frameNode, const std::string& key)
{
    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<LinearLayoutPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->RemoveResObj(key);
}

void ColumnModelNG::SetAlignItems(FlexAlign flexAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, flexAlign);
}

void ColumnModelNG::SetJustifyContent(FlexAlign flexAlign)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, flexAlign);
}

void ColumnModelNG::SetIsReverse(bool isReverse)
{
    ACE_UPDATE_LAYOUT_PROPERTY(FlexLayoutProperty, IsReverse, isReverse);
}

void ColumnModelNG::SetIsReverse(FrameNode* frameNode, bool isReverse)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FlexLayoutProperty, IsReverse, isReverse, frameNode);
}

void ColumnModelNG::SetJustifyContent(FrameNode* frameNode, FlexAlign flexAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, MainAxisAlign, flexAlign, frameNode);
}

void ColumnModelNG::SetAlignItems(FrameNode* frameNode, FlexAlign flexAlign)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(LinearLayoutProperty, CrossAxisAlign, flexAlign, frameNode);
}

FlexAlign ColumnModelNG::GetJustifyContent(FrameNode* frameNode)
{
    FlexAlign value = FlexAlign::AUTO;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(LinearLayoutProperty, MainAxisAlign, value, frameNode, value);
    return value;
}

FlexAlign ColumnModelNG::GetAlignItems(FrameNode* frameNode)
{
    FlexAlign value = FlexAlign::CENTER;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(LinearLayoutProperty, CrossAxisAlign, value, frameNode, value);
    return value;
}
} // namespace OHOS::Ace::NG

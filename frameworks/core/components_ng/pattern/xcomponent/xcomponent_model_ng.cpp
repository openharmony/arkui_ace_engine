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

#include "core/components_ng/pattern/xcomponent/xcomponent_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_event_hub.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_layout_property.h"
#include "core/components_ng/pattern/xcomponent/xcomponent_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {
void XComponentModelNG::Create(const std::string& id, XComponentType type, const std::string& libraryname,
    const std::shared_ptr<InnerXComponentController>& xcomponentController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::XCOMPONENT_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, nodeId, [id, type, libraryname, xcomponentController]() {
            return AceType::MakeRefPtr<XComponentPattern>(id, type, libraryname, xcomponentController);
        });
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(XComponentLayoutProperty, XComponentType, type);
}

RefPtr<AceType> XComponentModelNG::Create(int32_t nodeId, float width, float height, const std::string& id,
    XComponentType type, const std::string& libraryname,
    const std::shared_ptr<InnerXComponentController>& xcomponentController)
{
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::XCOMPONENT_ETS_TAG, nodeId);
    auto calcWidth = CalcLength(width, DimensionUnit::VP);
    auto calcHeight = CalcLength(height, DimensionUnit::VP);
    auto frameNode = FrameNode::GetOrCreateFrameNode(
        V2::XCOMPONENT_ETS_TAG, nodeId, [id, type, libraryname, xcomponentController, calcWidth, calcHeight]() {
            return AceType::MakeRefPtr<XComponentPattern>(id, type, libraryname, xcomponentController,
                calcWidth.GetDimension().ConvertToPx(), calcHeight.GetDimension().ConvertToPx());
        });

    CHECK_NULL_RETURN(frameNode, nullptr);
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    if (layoutProperty) {
        layoutProperty->UpdateXComponentType(type);
        layoutProperty->UpdateUserDefinedIdealSize(CalcSize(calcWidth, calcHeight));
    }
    return frameNode;
}

XComponentType XComponentModelNG::GetTypeImpl(const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, XComponentType::UNKNOWN);
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, XComponentType::UNKNOWN);
    return layoutProperty->GetXComponentTypeValue();
}

XComponentType XComponentModelNG::GetType()
{
    return GetTypeImpl(ViewStackProcessor::GetInstance()->GetMainFrameNode());
}

void XComponentModelNG::SetSoPath(const std::string& soPath)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto type = GetTypeImpl(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    auto xcPattern = AceType::DynamicCast<XComponentPattern>(frameNode->GetPattern());
    CHECK_NULL_VOID(xcPattern);
    xcPattern->SetSoPath(soPath);
}

void XComponentModelNG::SetOnLoad(LoadEvent&& onLoad)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto type = GetTypeImpl(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnLoad(std::move(onLoad));
}

void XComponentModelNG::SetOnDestroy(DestroyEvent&& onDestroy)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto type = GetTypeImpl(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestroy(std::move(onDestroy));
}

void XComponentModelNG::RegisterOnCreate(const RefPtr<AceType>& node, LoadEvent&& onLoad)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    if (!layoutProperty || layoutProperty->GetXComponentTypeValue() == XComponentType::COMPONENT) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnLoad(std::move(onLoad));
}

void XComponentModelNG::RegisterOnDestroy(const RefPtr<AceType>& node, DestroyEvent&& onDestroy)
{
    auto frameNode = AceType::DynamicCast<NG::FrameNode>(node);
    CHECK_NULL_VOID(frameNode);
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    if (!layoutProperty || layoutProperty->GetXComponentTypeValue() == XComponentType::COMPONENT) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnDestroy(std::move(onDestroy));
}

bool XComponentModelNG::IsTexture()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_RETURN(frameNode, false);
    return GetTypeImpl(frameNode) == XComponentType::TEXTURE;
}

void XComponentModelNG::SetDetachCallback(DetachCallback&& onDetach)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto type = GetTypeImpl(frameNode);
    if (type == XComponentType::COMPONENT || type == XComponentType::NODE) {
        return;
    }
    auto eventHub = frameNode->GetEventHub<XComponentEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetDetachEvent(std::move(onDetach));
}

bool XComponentModelNG::IsTexture(FrameNode *frameNode)
{
    auto layoutProperty = frameNode->GetLayoutProperty<XComponentLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, false);
    return layoutProperty->GetXComponentTypeValue() == XComponentType::TEXTURE;
}
} // namespace OHOS::Ace::NG

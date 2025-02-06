/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "ui/properties/property.h"

#include "interfaces/inner_api/ace_kit/src/view/frame_node_impl.h"
#include "ui/base/ace_type.h"
#include "ui/base/referenced.h"
#include "ui/base/utils/utils.h"
#include "ui/view/frame_node.h"

#include "core/components_ng/property/property.h"

namespace OHOS::Ace::Kit {

AceNode* GetNodePtr(const WeakPtr<FrameNode>& weak)
{
    auto node = weak.Upgrade();
    auto frameNode = AceType::DynamicCast<FrameNodeImpl>(node);
    CHECK_NULL_RETURN(frameNode, nullptr);
    auto nodePtr = frameNode->GetAceNodePtr();
    return nodePtr;
}

void Property::CleanDirty()
{
    auto* node = GetNodePtr(host_);
    CHECK_NULL_VOID(node);
    auto paintProp = node->GetPaintProperty<NG::Property>();
    paintProp->CleanDirty();
    auto layoutProp = node->GetLayoutProperty();
    layoutProp->CleanDirty();
}

void Property::UpdateRender()
{
    auto node = host_.Upgrade();
    CHECK_NULL_VOID(node);
    node->MarkDirtyNode(NG::PROPERTY_UPDATE_RENDER);
    UpdatePaintFlag(NG::PROPERTY_UPDATE_RENDER);
}

void Property::UpdateMeasure(bool onlySelf)
{
    UpdateLayoutFlag(onlySelf ? NG::PROPERTY_UPDATE_MEASURE_SELF : NG::PROPERTY_UPDATE_MEASURE);
}

void Property::UpdatePaintFlag(NG::PropertyChangeFlag propertyChangeFlag)
{
    auto* node = GetNodePtr(host_);
    CHECK_NULL_VOID(node);
    auto paintProp = node->GetPaintProperty<NG::Property>();
    paintProp->UpdatePropertyChangeFlag(propertyChangeFlag);
}

void Property::UpdateLayoutFlag(NG::PropertyChangeFlag propertyChangeFlag)
{
    auto* node = GetNodePtr(host_);
    CHECK_NULL_VOID(node);
    auto layoutProp = node->GetLayoutProperty();
    layoutProp->UpdatePropertyChangeFlag(propertyChangeFlag);
}

void Property::SetHost(const WeakPtr<FrameNode>& host)
{
    host_ = host;
}

} // namespace OHOS::Ace::Kit

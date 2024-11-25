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

#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_ng/base/view_abstract.h"

namespace OHOS::Ace::NG {
RefPtr<FrameNode> FormModelNG::CreateFrameNode(int32_t nodeId)
{
    auto frameNode = FormNode::GetOrCreateFormNode(
        V2::FORM_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<FormPattern>(); });
    return frameNode;
}

void FormModelNG::AllowUpdate(FrameNode* frameNode, bool allowUpdate)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.allowUpdate = allowUpdate;
    property->UpdateRequestFormInfo(formInfo);
}

void FormModelNG::SetVisibility(FrameNode* frameNode, VisibleType visible)
{
    CHECK_NULL_VOID(frameNode);
    auto formPattern = frameNode->GetPattern<FormPattern>();
    CHECK_NULL_VOID(formPattern);
    auto isLoaded = formPattern->GetIsLoaded();
    auto layoutProperty = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(layoutProperty);
    if (isLoaded || visible != VisibleType::VISIBLE) {
        layoutProperty->UpdateVisibility(visible, true);
    } else {
        layoutProperty->UpdateVisibility(VisibleType::INVISIBLE, true);
    }
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FormLayoutProperty, VisibleType, visible, frameNode);
}

void FormModelNG::SetDimension(FrameNode* frameNode, int32_t dimension)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.dimension = dimension;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FormLayoutProperty, RequestFormInfo, formInfo, frameNode);
}

void FormModelNG::SetModuleName(FrameNode* frameNode, const std::string& moduleName)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.moduleName = moduleName;
    property->UpdateRequestFormInfo(formInfo);
}

void FormModelNG::SetSize(FrameNode* frameNode, const Dimension& width, const Dimension& height)
{
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.width = width;
    formInfo.height = height;
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(FormLayoutProperty, RequestFormInfo, formInfo, frameNode);
}
} // namespace OHOS::Ace::NG
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

#include "core/components_ng/pattern/form/form_view.h"

#include <optional>

#include "base/geometry/dimension.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/form/form_layout_property.h"
#include "core/components_ng/pattern/form/form_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

RefPtr<FormNode> FormView::GetOrCreateFormNode(
    const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator)
{
    auto formNode = ElementRegister::GetInstance()->GetSpecificItemById<FormNode>(nodeId);
    if (formNode) {
        if (formNode->GetTag() == tag) {
            return formNode;
        }
        ElementRegister::GetInstance()->RemoveItemSilently(nodeId);
        auto parent = formNode->GetParent();
        if (parent) {
            parent->RemoveChild(formNode);
        }
    }

    auto pattern = patternCreator ? patternCreator() : AceType::MakeRefPtr<Pattern>();
    formNode = AceType::MakeRefPtr<FormNode>(tag, nodeId, pattern, false);
    formNode->InitializePatternAndContext();
    ElementRegister::GetInstance()->AddUINode(formNode);
    return formNode;
}

void FormView::Create(const RequestFormInfo& formInfo)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = GetOrCreateFormNode(
        V2::FORM_ETS_TAG, stack->ClaimNodeId(), []() { return AceType::MakeRefPtr<FormPattern>(); });
    stack->Push(frameNode);

    ACE_UPDATE_LAYOUT_PROPERTY(FormLayoutProperty, RequestFormInfo, formInfo);
}

void FormView::SetSize(const Dimension& width, const Dimension& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.width = width;
    formInfo.height = height;
    property->UpdateRequestFormInfo(formInfo);
    property->UpdateCalcSelfIdealSize(CalcSize(NG::CalcLength(width), NG::CalcLength(height)));
}

void FormView::SetDimension(int32_t dimension)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto property = frameNode->GetLayoutProperty<FormLayoutProperty>();
    CHECK_NULL_VOID(property);
    if (!property->HasRequestFormInfo()) {
        return;
    }
    auto formInfo = property->GetRequestFormInfoValue();
    formInfo.dimension = dimension;
    property->UpdateRequestFormInfo(formInfo);
}

void FormView::SetAllowUpdate(bool allowUpdate)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

void FormView::SetVisible(VisibleType visible)
{
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Visibility, visible);
}

void FormView::SetModuleName(const std::string& moduleName)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
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

void FormView::SetOnAcquired(FormCallback&& onAcquired)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnAcquired(std::move(onAcquired));
}

void FormView::SetOnError(FormCallback&& onOnError)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnError(std::move(onOnError));
}

void FormView::SetOnUninstall(FormCallback&& onUninstall)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnUninstall(std::move(onUninstall));
}

void FormView::SetOnRouter(FormCallback&& onRouter)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<FormEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnRouter(std::move(onRouter));
}

} // namespace OHOS::Ace::NG

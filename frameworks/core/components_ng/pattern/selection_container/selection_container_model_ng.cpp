/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/selection_container/selection_container_model_ng.h"

#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/selection_container/selection_container_layout_property.h"
#include "core/components_ng/pattern/selection_container/selection_container_event_hub.h"
#include "core/components_ng/pattern/selection_container/selection_container_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

void SelectionContainerModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto nodeId = stack->ClaimNodeId();
    ACE_UINODE_TRACE(nodeId);
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::SELECTION_CONTAINER_ETS_TAG, nodeId);
    auto frameNode = FrameNode::GetOrCreateFrameNode(V2::SELECTION_CONTAINER_ETS_TAG, nodeId,
        []() { return AceType::MakeRefPtr<SelectionContainerPattern>(); });
    frameNode->SetSelectionContainerId(nodeId);
    stack->Push(frameNode);
    ACE_UPDATE_LAYOUT_PROPERTY(LayoutProperty, Alignment, Alignment::CENTER);
    frameNode->SetExclusiveEventForChild(true);

    auto pipeline = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto selectOverlayManager = pipeline->GetSelectOverlayManager();
    CHECK_NULL_VOID(selectOverlayManager);
    auto selectionContainerManager = selectOverlayManager->GetSelectionContainerManager();
    CHECK_NULL_VOID(selectionContainerManager);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    selectionContainerManager->RegisterSelectionContainer(nodeId, pattern);
    frameNode->AddNodeDestroyCallback("SelectionContainerManager",
        [weakManager = WeakPtr<SelectionContainerManager>(selectionContainerManager), selectionContainerId = nodeId]() {
            auto manager = weakManager.Upgrade();
            CHECK_NULL_VOID(manager);
            manager->UnregisterSelectionContainer(selectionContainerId);
        });
}

void SelectionContainerModelNG::SetCopyOption(CopyOptions copyOption)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetCopyOption(frameNode, copyOption);
}

void SelectionContainerModelNG::SetCopyOption(FrameNode* frameNode, CopyOptions copyOption)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, CopyOption, copyOption, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkContainerPropertyUpdate(static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION));
}

void SelectionContainerModelNG::SetEnableHapticFeedback(bool isEnabled)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetEnableHapticFeedback(frameNode, isEnabled);
}

void SelectionContainerModelNG::SetEnableHapticFeedback(FrameNode* frameNode, bool isEnabled)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(isEnabled);
    pattern->MarkContainerPropertyUpdate(
        static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK));
}

void SelectionContainerModelNG::SetTextJoinStyle(SelectionContainerTextJoinStyle style)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetTextJoinStyle(frameNode, style);
}

void SelectionContainerModelNG::SetTextJoinStyle(FrameNode* frameNode, SelectionContainerTextJoinStyle style)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextJoinStyle(style);
}

void SelectionContainerModelNG::SetCaretColor(const Color& caretColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetCaretColor(frameNode, caretColor);
}

void SelectionContainerModelNG::SetCaretColor(FrameNode* frameNode, const Color& caretColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, CaretColor, caretColor, frameNode);
}

void SelectionContainerModelNG::ResetCaretColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetCaretColor(frameNode);
}

void SelectionContainerModelNG::ResetCaretColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, CaretColor, frameNode);
}

void SelectionContainerModelNG::SetSelectedBackgroundColor(const Color& selectedBackgroundColor)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetSelectedBackgroundColor(frameNode, selectedBackgroundColor);
}

void SelectionContainerModelNG::SetSelectedBackgroundColor(FrameNode* frameNode, const Color& selectedBackgroundColor)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, SelectedBackgroundColor, selectedBackgroundColor,
        frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkContainerPropertyUpdate(
        static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR));
}

void SelectionContainerModelNG::ResetSelectedBackgroundColor()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetSelectedBackgroundColor(frameNode);
}

void SelectionContainerModelNG::ResetSelectedBackgroundColor(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, SelectedBackgroundColor, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkContainerPropertyUpdate(
        static_cast<uint32_t>(SelectionContainerPropertyChange::SELECTED_BACKGROUND_COLOR));
}

void SelectionContainerModelNG::ResetCopyOption()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetCopyOption(frameNode);
}

void SelectionContainerModelNG::ResetCopyOption(FrameNode* frameNode)
{
    ACE_RESET_NODE_LAYOUT_PROPERTY(SelectionContainerLayoutProperty, CopyOption, frameNode);
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->MarkContainerPropertyUpdate(static_cast<uint32_t>(SelectionContainerPropertyChange::COPY_OPTION));
}

void SelectionContainerModelNG::ResetEnableHapticFeedback()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetEnableHapticFeedback(frameNode);
}

void SelectionContainerModelNG::ResetEnableHapticFeedback(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetEnableHapticFeedback(true);
    pattern->MarkContainerPropertyUpdate(
        static_cast<uint32_t>(SelectionContainerPropertyChange::ENABLE_HAPTIC_FEEDBACK));
}

void SelectionContainerModelNG::ResetTextJoinStyle()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    ResetTextJoinStyle(frameNode);
}

void SelectionContainerModelNG::ResetTextJoinStyle(FrameNode* frameNode)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetTextJoinStyle(SelectionContainerTextJoinStyle::NEWLINE);
}
void SelectionContainerModelNG::SetOnWillCopy(std::function<bool(const std::u16string&)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnWillCopy(frameNode, std::move(func));
}

void SelectionContainerModelNG::SetOnWillCopy(FrameNode* frameNode, std::function<bool(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnWillCopy(std::move(func));
}

void SelectionContainerModelNG::SetOnCopy(std::function<void(const std::u16string&)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnCopy(frameNode, std::move(func));
}

void SelectionContainerModelNG::SetOnCopy(FrameNode* frameNode, std::function<void(const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnCopy(std::move(func));
}

void SelectionContainerModelNG::SetOnTextSelectionChange(
    std::function<void(const std::vector<std::u16string>&)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetOnTextSelectionChange(frameNode, std::move(func));
}

void SelectionContainerModelNG::SetOnTextSelectionChange(
    FrameNode* frameNode, std::function<void(const std::vector<std::u16string>&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto eventHub = frameNode->GetEventHub<SelectionContainerEventHub>();
    CHECK_NULL_VOID(eventHub);
    eventHub->SetOnTextSelectionChange(std::move(func));
}

void SelectionContainerModelNG::SetSelectionMenuOptions(const NG::OnCreateMenuCallback&& onCreateMenuCallback,
    const NG::OnMenuItemClickCallback&& onMenuItemClick, const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetSelectionMenuOptions(frameNode,
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
}

void SelectionContainerModelNG::SetSelectionMenuOptions(FrameNode* frameNode,
    const NG::OnCreateMenuCallback&& onCreateMenuCallback,
    const NG::OnMenuItemClickCallback&& onMenuItemClick,
    const NG::OnPrepareMenuCallback&& onPrepareMenuCallback)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->OnSelectionMenuOptionsUpdate(
        std::move(onCreateMenuCallback), std::move(onMenuItemClick), std::move(onPrepareMenuCallback));
}

void SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(
    std::function<bool(const NG::MenuItemParam&, const std::u16string&)>&& func)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    SetSelectionMenuItemClickWithTextCallback(frameNode, std::move(func));
}

void SelectionContainerModelNG::SetSelectionMenuItemClickWithTextCallback(FrameNode* frameNode,
    std::function<bool(const NG::MenuItemParam&, const std::u16string&)>&& func)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSelectionMenuItemClickWithTextCallback(std::move(func));
}

void SelectionContainerModelNG::BindSelectionMenu(TextSpanType spanType, TextResponseType responseType,
    std::function<void()>& menuBuilder, const SelectMenuParam& menuParam)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    BindSelectionMenu(frameNode, spanType, responseType, menuBuilder, menuParam);
}

void SelectionContainerModelNG::BindSelectionMenu(FrameNode* frameNode, TextSpanType spanType,
    TextResponseType responseType, std::function<void()>& menuBuilder, const SelectMenuParam& menuParam)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<SelectionContainerPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->BindSelectionMenu(spanType, responseType, menuBuilder, menuParam);
}

} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/models/list_item_model_impl.h"

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/view_abstract_model_impl.h"
#include "core/components_v2/list/list_item_component.h"

namespace OHOS::Ace::Framework {

void ListItemModelImpl::Create(bool isCreateArc)
{
    auto listItemComponent = AceType::MakeRefPtr<V2::ListItemComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(listItemComponent);
    ViewStackProcessor::GetInstance()->Push(listItemComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
}

void ListItemModelImpl::Create(
    std::function<void(int32_t)>&& deepRenderFunc, V2::ListItemStyle listItemStyle, bool isCreateArc)
{
    auto listItemComponent = AceType::MakeRefPtr<V2::ListItemComponent>();
    ViewStackProcessor::GetInstance()->ClaimElementId(listItemComponent);
    V2::DeepRenderFunc listItemDeepRenderFunc = [jsDeepRenderFunc = std::move(deepRenderFunc),
                                                    elmtId = listItemComponent->GetElementId()]() -> RefPtr<Component> {
        ACE_SCOPED_TRACE("JSListItem::ExecuteDeepRender");

        jsDeepRenderFunc(elmtId);
        RefPtr<Component> component = ViewStackProcessor::GetInstance()->Finish();
        ACE_DCHECK(AceType::DynamicCast<V2::ListItemComponent>(component) != nullptr);
        return component;
    }; // listItemDeepRenderFunc lambda

    listItemComponent->SetDeepRenderFunc(listItemDeepRenderFunc);
    ViewStackProcessor::GetInstance()->Push(listItemComponent);
    JSInteractableView::SetFocusable(true);
    JSInteractableView::SetFocusNode(true);
}

void ListItemModelImpl::SetBorderRadius(const Dimension& borderRadius)
{
    JSViewSetProperty(&V2::ListItemComponent::SetBorderRadius, borderRadius);
}

void ListItemModelImpl::SetType(const std::string& type)
{
    JSViewSetProperty(&V2::ListItemComponent::SetType, type);
}

void ListItemModelImpl::SetIsLazyCreating(bool isLazy)
{
    JSViewSetProperty(&V2::ListItemComponent::SetIsLazyCreating, isLazy);
}

void ListItemModelImpl::SetSticky(V2::StickyMode stickyMode)
{
    JSViewSetProperty(&V2::ListItemComponent::SetSticky, stickyMode);
}

void ListItemModelImpl::SetEditMode(uint32_t editMode)
{
    JSViewSetProperty(&V2::ListItemComponent::SetEditMode, editMode);
    if ((V2::EditMode::MOVABLE & editMode) == 0) {
        auto* stack = ViewStackProcessor::GetInstance();
        auto box = stack->GetBoxComponent();
        box->SetEnableDragStart(false);
    }
}

void ListItemModelImpl::SetSelectable(bool selectable)
{
    JSViewSetProperty(&V2::ListItemComponent::SetSelectable, selectable);
}

void ListItemModelImpl::SetSwiperAction(std::function<void()>&& startAction, std::function<void()>&& endAction,
    [[maybe_unused]] OnOffsetChangeFunc&& onOffsetChangeFunc, V2::SwipeEdgeEffect edgeEffect, NG::FrameNode* node)
{
    auto listItem = AceType::DynamicCast<V2::ListItemComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
    if (!listItem) {
        LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<V2::ListItemComponent>());
        return;
    }
    if (startAction) {
        ScopedViewStackProcessor builderViewStackProcessor;
        startAction();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItem->SetSwiperStartComponent(customComponent);
    }
    if (endAction) {
        ScopedViewStackProcessor builderViewStackProcessor;
        endAction();
        RefPtr<Component> customComponent = ViewStackProcessor::GetInstance()->Finish();
        listItem->SetSwiperEndComponent(customComponent);
    }
    listItem->SetEdgeEffect(edgeEffect);
}

void ListItemModelImpl::SetSelectCallback(OnSelectFunc&& selectCallback)
{
    JSViewSetProperty(&V2::ListItemComponent::SetOnSelectId, std::move(selectCallback));
}

void ListItemModelImpl::SetDeleteArea(std::function<void()>&& builderAction, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea, NG::FrameNode* node) {};

void ListItemModelImpl::SetOnDragStart(NG::OnDragStartFunc&& onDragStart)
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOnDragStartId(ViewAbstractModelImpl::ToDragFunc(std::move(onDragStart)));
    JSViewSetProperty(&V2::ListItemComponent::MarkIsDragStart, true);
}

void ListItemModelImpl::SetDeleteAreaWithFrameNode(const RefPtr<NG::UINode>& builderComponent, OnDeleteEvent&& onDelete,
    OnEnterDeleteAreaEvent&& onEnterDeleteArea, OnExitDeleteAreaEvent&& onExitDeleteArea,
    OnStateChangedEvent&& onStateChange, const Dimension& length, bool isStartArea, NG::FrameNode* node) {};

} // namespace OHOS::Ace::Framework

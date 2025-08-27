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

#include "core/interfaces/native/node/node_adapter_impl.h"

#include "core/components_ng/syntax/lazy_for_each_node.h"

struct _ArkUINodeAdapter {
    OHOS::Ace::RefPtr<OHOS::Ace::NG::NativeLazyForEachBuilder> builder;
    OHOS::Ace::RefPtr<OHOS::Ace::NG::LazyForEachNode> node;
};

namespace OHOS::Ace::NG {

void NativeLazyForEachBuilder::RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener)
{
    listener_ = RawPtr(listener);
    if (!receiver_) {
        return;
    }
    ArkUINodeAdapterEvent event { .type = ON_ATTACH_TO_NODE };
    event.extraParam = reinterpret_cast<intptr_t>(userData_);
    auto lazyForEachNode = DynamicCast<LazyForEachNode>(listener);
    if (lazyForEachNode) {
        auto parent = lazyForEachNode->GetParent();
        if (parent) {
            event.handle = reinterpret_cast<ArkUINodeHandle>(RawPtr(parent));
        }
    }
    receiver_(&event);
}

void NativeLazyForEachBuilder::UnregisterDataChangeListener(V2::DataChangeListener* listener)
{
    listener_ = nullptr;
    if (!receiver_) {
        return;
    }
    ArkUINodeAdapterEvent event { .type = ON_DETACH_FROM_NODE };
    event.extraParam = reinterpret_cast<intptr_t>(userData_);
    receiver_(&event);
}

int32_t NativeLazyForEachBuilder::OnGetTotalCount()
{
    return totalCount_;
}

LazyForEachChild NativeLazyForEachBuilder::OnGetChildByIndex(
    int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems)
{
    LazyForEachChild child;
    if (!receiver_) {
        return child;
    }
    ArkUINodeAdapterEvent getIdevent { .index = index, .idSet = false, .type = ON_GET_NODE_ID, .nodeSet = false };
    getIdevent.extraParam = reinterpret_cast<intptr_t>(userData_);
    receiver_(&getIdevent);
    std::string idStr;
    if (getIdevent.idSet) {
        idStr = std::to_string(getIdevent.id);
    } else {
        idStr = std::to_string(index);
    }
    child.first = idStr;
    const auto& itemIter = cachedItems.find(idStr);
    if (itemIter != cachedItems.end()) {
        child.second = itemIter->second.second;
        cachedItems.erase(itemIter);
        // For not change C-API receiver
        if (needUpdateEvent_) {
            getIdevent.type = ON_UPDATE_NODE;
            getIdevent.handle = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(child.second));
            if (!getIdevent.idSet) {
                getIdevent.id = index;
            }
            receiver_(&getIdevent);
        }
        FlushDirtyPropertyNodes(child.second);
        return child;
    }
    ArkUINodeAdapterEvent getChildEvent {
        .index = index, .id = getIdevent.id, .idSet = false, .type = ON_ADD_NODE_TO_ADAPTER, .nodeSet = false
    };
    getChildEvent.extraParam = reinterpret_cast<intptr_t>(userData_);
    receiver_(&getChildEvent);
    if (getChildEvent.nodeSet) {
        child.second = Claim(reinterpret_cast<UINode*>(getChildEvent.handle));
    }
    FlushDirtyPropertyNodes(child.second);
    return child;
}

void NativeLazyForEachBuilder::FlushDirtyPropertyNodes(const RefPtr<UINode>& node)
{
    CHECK_NULL_VOID(node);
    auto context = node->GetContext();
    CHECK_NULL_VOID(context);
    context->FlushDirtyPropertyNodes();
}

void NativeLazyForEachBuilder::OnItemDeleted(UINode* node, const std::string& key)
{
    if (!receiver_) {
        return;
    }
    ArkUINodeAdapterEvent event {
        .id = StringUtils::StringToInt(key), .idSet = false, .type = ON_REMOVE_NODE_FROM_ADAPTER, .nodeSet = false
    };
    event.extraParam = reinterpret_cast<intptr_t>(userData_);
    event.handle = reinterpret_cast<ArkUINodeHandle>(node);
    receiver_(&event);
}

ArkUI_Int32 NativeLazyForEachBuilder::GetAllItem(ArkUINodeHandle** items, ArkUI_Uint32* size)
{
    std::vector<UINode*> childList;
    GetAllItems(childList);
    *size = childList.size();
    *items = new ArkUINodeHandle[*size];
    for (uint32_t i = 0; i < *size; i++) {
        (*items)[i] = reinterpret_cast<ArkUINodeHandle>(childList[i]);
    }
    return ERROR_CODE_NO_ERROR;
}

UINodeAdapter::UINodeAdapter(ArkUINodeAdapterHandle handle) : handle_(handle)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->SetUserData(this);
    handle_->builder->SetReceiver([](ArkUINodeAdapterEvent* event) {
        CHECK_NULL_VOID(event);
        auto adapter = reinterpret_cast<UINodeAdapter*>(event->extraParam);
        if (adapter != nullptr) {
            adapter->OnEventReceived(event);
        }
    });
    handle_->builder->SetNeedUpdateEvent(true);
}

UINodeAdapter::~UINodeAdapter()
{
    if (handle_ != nullptr) {
        delete handle_;
        handle_ = nullptr;
    }
}

void UINodeAdapter::OnEventReceived(ArkUINodeAdapterEvent* event)
{
    switch (event->type) {
        case ON_ATTACH_TO_NODE:
            if (attachToNodeFunc_) {
                attachToNodeFunc_(event->handle);
            }
            break;
        case ON_DETACH_FROM_NODE:
            if (detachFromNodeFunc_) {
                detachFromNodeFunc_();
            }
            break;
        case ON_GET_NODE_ID:
            if (getChildIdFunc_) {
                auto id = getChildIdFunc_(event->index);
                event->idSet = true;
                event->id = id;
            }
            break;
        case ON_ADD_NODE_TO_ADAPTER:
            if (createNewChildFunc_) {
                auto handle = createNewChildFunc_(event->index);
                event->nodeSet = true;
                event->handle = handle;
            }
            break;
        case ON_REMOVE_NODE_FROM_ADAPTER:
            if (disposeChildFunc_) {
                disposeChildFunc_(event->handle, event->id);
            }
            break;
        case ON_UPDATE_NODE:
            if (updateChildFunc_) {
                updateChildFunc_(event->handle, event->id);
            }
            break;
        default:
            break;
    }
}

void UINodeAdapter::SetTotalNodeCount(uint32_t count)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->SetNodeTotalCount(count);
}

uint32_t UINodeAdapter::GetTotalNodeCount() const
{
    CHECK_NULL_RETURN(handle_, 0);
    CHECK_NULL_RETURN(handle_->builder, 0);
    return handle_->builder->GetNodeTotalCount();
}

void UINodeAdapter::NotifyItemReloaded()
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->NotifyItemReloaded();
}

void UINodeAdapter::NotifyItemChanged(uint32_t start, uint32_t count)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->NotifyItemChanged(start, count);
}

void UINodeAdapter::NotifyItemInserted(uint32_t start, uint32_t count)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->NotifyItemInserted(start, count);
}

void UINodeAdapter::NotifyItemMoved(uint32_t from, uint32_t to)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->NotifyItemMoved(from, to);
}

void UINodeAdapter::NotifyItemRemoved(uint32_t start, uint32_t count)
{
    CHECK_NULL_VOID(handle_);
    CHECK_NULL_VOID(handle_->builder);
    handle_->builder->NotifyItemRemoved(start, count);
}

std::vector<ArkUINodeHandle> UINodeAdapter::GetAllItems()
{
    std::vector<ArkUINodeHandle> items;
    CHECK_NULL_RETURN(handle_, items);
    CHECK_NULL_RETURN(handle_->builder, items);
    
    ArkUINodeHandle* itemArray = nullptr;
    uint32_t size = 0;
    handle_->builder->GetAllItem(&itemArray, &size);
    for (uint32_t i = 0; i < size; i++) {
        items.push_back(itemArray[i]);
    }
    if (itemArray != nullptr) {
        delete[] itemArray;
    }
    return items;
}

} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NodeAdapter {
namespace {

ArkUINodeAdapterHandle Create()
{
    auto* adapter = new _ArkUINodeAdapter { .builder = AceType::MakeRefPtr<NG::NativeLazyForEachBuilder>() };
    adapter->builder->SetHostHandle(adapter);
    return adapter;
}

void Dispose(ArkUINodeAdapterHandle handle)
{
    if (!handle) {
        return;
    }
    if (handle->node) {
        const auto& parent = handle->node->GetParent();
        if (parent) {
            parent->RemoveChild(handle->node);
        }
    }
    if (handle->builder) {
        handle->builder->SetHostHandle(nullptr);
    }
    delete handle;
}

ArkUI_Int32 SetTotalNodeCount(ArkUINodeAdapterHandle handle, ArkUI_Uint32 size)
{
    if (handle) {
        handle->builder->SetNodeTotalCount(size);
        return ERROR_CODE_NO_ERROR;
    }
    return ERROR_CODE_PARAM_INVALID;
}

ArkUI_Uint32 GetTotalNodeCount(ArkUINodeAdapterHandle handle)
{
    if (handle) {
        return handle->builder->GetNodeTotalCount();
    }
    return 0;
}

ArkUI_Int32 RegisterEventReceiver(
    ArkUINodeAdapterHandle handle, void* userData, void (*receiver)(ArkUINodeAdapterEvent* event))
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    handle->builder->SetUserData(userData);
    handle->builder->SetReceiver(receiver);
    return ERROR_CODE_NO_ERROR;
}

void UnregisterEventReceiver(ArkUINodeAdapterHandle handle)
{
    if (!handle) {
        return;
    }
    handle->builder->SetUserData(nullptr);
    handle->builder->SetReceiver(nullptr);
}

ArkUI_Int32 NotifyItemReloaded(ArkUINodeAdapterHandle handle)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->NotifyItemReloaded();
}

ArkUI_Int32 NotifyItemChanged(ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->NotifyItemChanged(startPosition, itemCount);
}

ArkUI_Int32 NotifyItemRemoved(ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->NotifyItemRemoved(startPosition, itemCount);
}

ArkUI_Int32 NotifyItemInserted(ArkUINodeAdapterHandle handle, ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->NotifyItemInserted(startPosition, itemCount);
}

ArkUI_Int32 NotifyItemMoved(ArkUINodeAdapterHandle handle, ArkUI_Uint32 from, ArkUI_Uint32 to)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->NotifyItemMoved(from, to);
}

ArkUI_Int32 GetAllItem(ArkUINodeAdapterHandle handle, ArkUINodeHandle** items, ArkUI_Uint32* size)
{
    if (!handle) {
        return ERROR_CODE_PARAM_INVALID;
    }
    return handle->builder->GetAllItem(items, size);
}

int32_t GetLazyForEachChildIndex(const RefPtr<NG::UINode>& node)
{
    int32_t index = 0;
    for (const auto& iter : node->GetChildren()) {
        if (AceType::InstanceOf<NG::LazyForEachNode>(iter)) {
            return index;
        }
        index++;
    }
    return -1;
}

ArkUI_Bool AttachHostNode(ArkUINodeAdapterHandle handle, ArkUINodeHandle host)
{
    CHECK_NULL_RETURN(handle, true);
    CHECK_NULL_RETURN(host, true);
    auto* uiNode = reinterpret_cast<NG::UINode*>(host);
    // A NodeAdapter only allows binding to one LazyForEach
    if (GetLazyForEachChildIndex(Referenced::Claim(uiNode)) != -1) {
        return false;
    }
    if (!handle->node) {
        handle->node =
            NG::LazyForEachNode::CreateLazyForEachNode(ElementRegister::GetInstance()->MakeUniqueId(), handle->builder);
    }
    if (AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        auto* frameNode = reinterpret_cast<NG::FrameNode*>(uiNode);
        if (frameNode->GetPattern()->OnAttachAdapter(Referenced::Claim(frameNode), handle->node)) {
            return true;
        } else if (frameNode->GetFirstChild() == nullptr) {
            uiNode->AddChild(handle->node);
            return true;
        }
    }
    return false;
}

void DetachHostNode(ArkUINodeHandle host)
{
    CHECK_NULL_VOID(host);
    auto* uiNode = reinterpret_cast<NG::UINode*>(host);
    if (!AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        return;
    }
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(uiNode);
    // Component overload unbinding method, unbind LazyForEach according to your own specifications
    if (frameNode->GetPattern()->DetachHostNodeAdapter(Referenced::Claim(frameNode))) {
        return;
    }
    int32_t index = 0;
    // The default first node is LazyForEach. If the LazyForEach node is not unbound
    if (!AceType::InstanceOf<NG::LazyForEachNode>(uiNode->GetChildAtIndex(0))) {
        index = GetLazyForEachChildIndex(Referenced::Claim(uiNode));
    }
    if (index == -1) {
        return;
    }
    const auto& child = AceType::DynamicCast<NG::LazyForEachNode>(uiNode->GetChildAtIndex(index));
    CHECK_NULL_VOID(child);
    uiNode->RemoveChild(child);
    const auto& builder = AceType::DynamicCast<NG::NativeLazyForEachBuilder>(child->GetBuilder());
    CHECK_NULL_VOID(builder);
    auto handle = builder->GetHostHandle();
    CHECK_NULL_VOID(handle);
    handle->node = nullptr;
}

ArkUINodeAdapterHandle GetNodeAdapter(ArkUINodeHandle host)
{
    CHECK_NULL_RETURN(host, nullptr);
    auto* uiNode = reinterpret_cast<NG::UINode*>(host);
    if (!AceType::InstanceOf<NG::FrameNode>(uiNode)) {
        return nullptr;
    }
    ArkUINodeAdapterHandle handle = nullptr;
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(uiNode);
    if (frameNode->GetPattern()->GetNodeAdapterComponent(handle, Referenced::Claim(frameNode))) {
        return handle;
    }
    int32_t index = 0;
    // The default first node is LazyForEach. If the LazyForEach node is not unbound
    if (!AceType::InstanceOf<NG::LazyForEachNode>(uiNode->GetChildAtIndex(0))) {
        index = GetLazyForEachChildIndex(Referenced::Claim(uiNode));
    }
    if (index == -1) {
        return nullptr;
    }
    const auto& child = AceType::DynamicCast<NG::LazyForEachNode>(uiNode->GetChildAtIndex(index));
    CHECK_NULL_RETURN(child, nullptr);
    const auto& builder = AceType::DynamicCast<NG::NativeLazyForEachBuilder>(child->GetBuilder());
    CHECK_NULL_RETURN(builder, nullptr);
    return builder->GetHostHandle();
}

ArkUI_CharPtr GetNodeTypeInNodeAdapter(ArkUINodeAdapterHandle handle)
{
    CHECK_NULL_RETURN(handle, "");
    CHECK_NULL_RETURN(handle->node, "");
    static std::string nodeType = handle->node->GetTag();
    return nodeType.c_str();
}

void FireArkUIObjectLifecycleCallback(void* data, ArkUINodeAdapterHandle handle)
{
    CHECK_NULL_VOID(data);
    CHECK_NULL_VOID(handle);
    CHECK_NULL_VOID(handle->node);
    auto context = handle->node->GetContext();
    CHECK_NULL_VOID(context);
    context->FireArkUIObjectLifecycleCallback(data);
}
} // namespace

const ArkUINodeAdapterAPI* GetNodeAdapterAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUINodeAdapterAPI impl {
        .create = Create,
        .dispose = Dispose,
        .setTotalNodeCount = SetTotalNodeCount,
        .getTotalNodeCount = GetTotalNodeCount,
        .registerEventReceiver = RegisterEventReceiver,
        .unregisterEventReceiver = UnregisterEventReceiver,
        .notifyItemReloaded = NotifyItemReloaded,
        .notifyItemChanged = NotifyItemChanged,
        .notifyItemRemoved = NotifyItemRemoved,
        .notifyItemInserted = NotifyItemInserted,
        .notifyItemMoved = NotifyItemMoved,
        .getAllItem = GetAllItem,
        .attachHostNode = AttachHostNode,
        .detachHostNode = DetachHostNode,
        .getNodeAdapter = GetNodeAdapter,
        .getNodeType = GetNodeTypeInNodeAdapter,
        .fireArkUIObjectLifecycleCallback = FireArkUIObjectLifecycleCallback
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

const CJUINodeAdapterAPI* GetCJUINodeAdapterAPI()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUINodeAdapterAPI impl {
        .create = Create,
        .dispose = Dispose,
        .setTotalNodeCount = SetTotalNodeCount,
        .getTotalNodeCount = GetTotalNodeCount,
        .registerEventReceiver = RegisterEventReceiver,
        .unregisterEventReceiver = UnregisterEventReceiver,
        .notifyItemReloaded = NotifyItemReloaded,
        .notifyItemChanged = NotifyItemChanged,
        .notifyItemRemoved = NotifyItemRemoved,
        .notifyItemInserted = NotifyItemInserted,
        .notifyItemMoved = NotifyItemMoved,
        .getAllItem = GetAllItem,
        .attachHostNode = AttachHostNode,
        .detachHostNode = DetachHostNode,
        .getNodeAdapter = GetNodeAdapter
    };
    CHECK_INITIALIZED_FIELDS_END(impl, 0, 0, 0); // don't move this line
    return &impl;
}

} // namespace OHOS::Ace::NodeAdapter

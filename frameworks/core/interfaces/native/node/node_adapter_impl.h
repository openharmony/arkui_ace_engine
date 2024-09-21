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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_ADAPTER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_ADAPTER_IMPL_H

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

#include "base/error/error_code.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_builder.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"

namespace OHOS::Ace::NG {
class NativeLazyForEachBuilder : public LazyForEachBuilder {
    DECLARE_ACE_TYPE(NativeLazyForEachBuilder, LazyForEachBuilder)
public:
    // used in ArkTS side.
    void ReleaseChildGroupById(const std::string& id) override {}

    void RegisterDataChangeListener(const RefPtr<V2::DataChangeListener>& listener) override;

    void UnregisterDataChangeListener(V2::DataChangeListener* listener) override;

    void SetNodeTotalCount(ArkUI_Uint32 nodeCount)
    {
        totalCount_ = nodeCount;
    }

    ArkUI_Uint32 GetNodeTotalCount() const
    {
        return totalCount_;
    }

    void SetUserData(void* userData)
    {
        userData_ = userData;
    }

    void SetReceiver(void (*receiver)(ArkUINodeAdapterEvent* event))
    {
        receiver_ = receiver;
    }

    ArkUI_Int32 NotifyItemReloaded()
    {
        if (listener_) {
            listener_->OnDataReloaded();
            return ERROR_CODE_NO_ERROR;
        }
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR;
    }

    ArkUI_Int32 NotifyItemChanged(ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
    {
        if (listener_) {
            listener_->OnDataBulkChanged(startPosition, itemCount);
            return ERROR_CODE_NO_ERROR;
        }
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR;
    }

    ArkUI_Int32 NotifyItemRemoved(ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
    {
        if (listener_) {
            listener_->OnDataBulkDeleted(startPosition, itemCount);
            return ERROR_CODE_NO_ERROR;
        }
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR;
    }
    ArkUI_Int32 NotifyItemInserted(ArkUI_Uint32 startPosition, ArkUI_Uint32 itemCount)
    {
        if (listener_) {
            listener_->OnDataBulkAdded(startPosition, itemCount);
            return ERROR_CODE_NO_ERROR;
        }
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR;
    }
    ArkUI_Int32 NotifyItemMoved(ArkUI_Uint32 from, ArkUI_Uint32 to)
    {
        if (listener_) {
            listener_->OnDataMoveToNewPlace(from, to);
            return ERROR_CODE_NO_ERROR;
        }
        return ERROR_CODE_NATIVE_IMPL_NODE_ADAPTER_NO_LISTENER_ERROR;
    }

    // should manager the array memory.
    ArkUI_Int32 GetAllItem(ArkUINodeHandle** items, ArkUI_Uint32* size);

    void SetHostHandle(ArkUINodeAdapterHandle handle)
    {
        handle_ = handle;
    }

    ArkUINodeAdapterHandle GetHostHandle() const
    {
        return handle_;
    }

    void SetNeedUpdateEvent(bool needUpdateEvent)
    {
        needUpdateEvent_ = needUpdateEvent;
    }

protected:
    int32_t OnGetTotalCount() override;

    LazyForEachChild OnGetChildByIndex(
        int32_t index, std::unordered_map<std::string, LazyForEachCacheChild>& cachedItems) override;

    void OnItemDeleted(UINode* node, const std::string& key) override;

    bool DeleteExpiringItemImmediately() override
    {
        return true;
    }

    // used in ArkTS side for tabs.
    LazyForEachChild OnGetChildByIndexNew(int32_t index, std::map<int32_t, LazyForEachChild>& cachedItems,
        std::unordered_map<std::string, LazyForEachCacheChild>& expiringItems) override
    {
        return {};
    }

    // used in ArkTS side for tabs.
    void OnExpandChildrenOnInitialInNG() override {}

    // used in ArkTS side.
    void NotifyDataChanged(size_t index, const RefPtr<UINode>& lazyForEachNode, bool isRebuild) override {}

    // used in ArkTS side.
    void NotifyDataDeleted(const RefPtr<UINode>& lazyForEachNode, size_t index, bool removeIds) override {}

    // used in ArkTS side.
    void NotifyDataAdded(size_t index) override {}

    // used in ArkTS side.
    void KeepRemovedItemInCache(
        NG::LazyForEachChild node, std::unordered_map<std::string, NG::LazyForEachCacheChild>& cachedItems) override
    {}

    void FlushDirtyPropertyNodes(const RefPtr<UINode>& node);

private:
    V2::DataChangeListener* listener_;
    uint32_t totalCount_ = 0;
    void* userData_ = nullptr;
    void (*receiver_)(ArkUINodeAdapterEvent* event) = nullptr;
    bool needUpdateEvent_ = false;
    ArkUINodeAdapterHandle handle_ = nullptr;
};

class UINodeAdapter : public AceType {
public:
    explicit UINodeAdapter(ArkUINodeAdapterHandle handle);
    ~UINodeAdapter() override;

    void OnEventReceived(ArkUINodeAdapterEvent* event);

    void SetOnAttachToNodeFunc(std::function<void(ArkUINodeHandle)>&& func)
    {
        attachToNodeFunc_ = func;
    }

    void SetOnDetachFromNodeFunc(std::function<void()>&& func)
    {
        detachFromNodeFunc_ = func;
    }

    void SetOnGetChildIdFunc(std::function<int32_t(uint32_t)>&& func)
    {
        getChildIdFunc_ = func;
    }

    void SetOnCreateNewChild(std::function<ArkUINodeHandle(uint32_t)>&& func)
    {
        createNewChildFunc_ = func;
    }

    void SetOnDisposeChild(std::function<void(ArkUINodeHandle, int32_t)>&& func)
    {
        disposeChildFunc_ = func;
    }

    void SetOnUpdateChind(std::function<void(ArkUINodeHandle, int32_t)>&& func)
    {
        updateChildFunc_ = func;
    }

    ArkUINodeAdapterHandle GetHandle() const
    {
        return handle_;
    }

    void SetTotalNodeCount(uint32_t count);
    uint32_t GetTotalNodeCount() const;
    void NotifyItemReloaded();
    void NotifyItemChanged(uint32_t start, uint32_t count);
    void NotifyItemRemoved(uint32_t start, uint32_t count);
    void NotifyItemInserted(uint32_t start, uint32_t count);
    void NotifyItemMoved(uint32_t from, uint32_t to);
    std::vector<ArkUINodeHandle> GetAllItems();

private:
    ArkUINodeAdapterHandle handle_;
    std::function<void(ArkUINodeHandle)> attachToNodeFunc_;
    std::function<void()> detachFromNodeFunc_;
    std::function<int32_t(uint32_t)> getChildIdFunc_;
    std::function<ArkUINodeHandle(uint32_t)> createNewChildFunc_;
    std::function<void(ArkUINodeHandle, int32_t)> disposeChildFunc_;
    std::function<void(ArkUINodeHandle, int32_t)> updateChildFunc_;
};

} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NodeAdapter {
const ArkUINodeAdapterAPI* GetNodeAdapterAPI();
const CJUINodeAdapterAPI* GetCJUINodeAdapterAPI();
} // namespace OHOS::Ace::NodeAdapter
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_ADAPTER_IMPL_H

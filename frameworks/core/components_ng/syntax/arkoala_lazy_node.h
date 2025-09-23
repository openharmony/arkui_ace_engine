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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H
#include <cstdint>
#include <functional>

#include "base/utils/unique_valued_map.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

/**
 * @brief Backend node representation to access and manage lazy items in Arkoala frontend
 *
 */
class ArkoalaLazyNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(ArkoalaLazyNode, ForEachBaseNode);

public:
    explicit ArkoalaLazyNode(int32_t id) : ForEachBaseNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, id) {}

    using CreateItemCb = std::function<RefPtr<UINode>(int32_t)>;
    using UpdateRangeCb = std::function<void(int32_t, int32_t)>;

    void SetTotalCount(int32_t value)
    {
        totalCount_ = value;
    }

    void SetCallbacks(CreateItemCb create, UpdateRangeCb update)
    {
        createItem_ = std::move(create);
        updateRange_ = std::move(update);
    }

    void MoveData(int32_t from, int32_t to) final
    {
        items_.Swap(from, to);
    }

    RefPtr<FrameNode> GetFrameNode(int32_t index) final;

    RefPtr<UINode> GetChildByIndex(int32_t index);

    RefPtr<UINode> GetFrameChildByIndex(uint32_t index, bool needBuild, bool isCache, bool addToRenderTree) override;

    void DoRemoveChildInRenderTree(uint32_t index, bool isAll) final
    {
        LOGI("Koala lazyForEach: doRemove called %u. Not implemented", index);
    }
    void DoSetActiveChildRange(int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache) final;

    bool IsAtomicNode() const final
    {
        return false;
    }

    int32_t FrameCount() const final
    {
        return totalCount_;
    }

    void RecycleItems(int32_t from, int32_t to) final
    {
        /* not implemented yet */
    }

    void OnDataChange(int32_t changeIndex, int32_t count, NotificationType type);

private:
    UniqueValuedMap<int32_t, WeakPtr<UINode>, WeakPtr<UINode>::Hash> items_;
    CreateItemCb createItem_;
    UpdateRangeCb updateRange_;
    int32_t totalCount_ = 0;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_LAZY_NODE_H

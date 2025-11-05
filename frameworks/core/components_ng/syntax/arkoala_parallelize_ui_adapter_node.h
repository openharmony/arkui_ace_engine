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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_PARALLELIZE_UI_ADAPTER_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_PARALLELIZE_UI_ADAPTER_NODE_H
#include <cstdint>
#include <functional>

#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/unique_valued_map.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ParallelizeUIAdapterNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(ParallelizeUIAdapterNode, ForEachBaseNode);

public:
    explicit ParallelizeUIAdapterNode(int32_t nodeId) : ForEachBaseNode(V2::JS_LAZY_FOR_EACH_ETS_TAG, nodeId) {}

    ~ParallelizeUIAdapterNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void FlushUpdateAndMarkDirty() override {}

    void MoveData(int32_t from, int32_t to) override {}

    RefPtr<FrameNode> GetFrameNode(int32_t index) override
    {
        return nullptr;
    }

    void Reset();

    int32_t FrameCount() const override;


    void RegisterCallback(std::function<int32_t()>&& getCount,
        std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)>&& registerCallback)
    {
        getCount_ = std::move(getCount);
        registerCallback_ = std::move(registerCallback);
    }

    RefPtr<UINode> GetFrameChildByIndex(
        uint32_t index, bool needBuild, bool isCache = false, bool addToRenderTree = false) override;

    const std::list<RefPtr<UINode>>& GetChildren(bool notDetach = false) const override;

    void DoSetActiveChildRange(
        int32_t start, int32_t end, int32_t cacheStart, int32_t cacheEnd, bool showCache = false) override;
private:
    std::function<int32_t()> getCount_;
    std::function<ArkUINodeHandle(int32_t, int32_t, int32_t)> registerCallback_;

    mutable std::list<RefPtr<UINode>> children_;
    std::map<int32_t, RefPtr<UINode>> childMap_;
    int32_t start_ = 0;
    int32_t end_ = 0;

    ACE_DISALLOW_COPY_AND_MOVE(ParallelizeUIAdapterNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_SYNTAX_ARKOALA_PARALLELIZE_UI_ADAPTER_NODE_H

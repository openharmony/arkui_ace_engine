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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_NODE_H

#include <cstdint>
#include <list>
#include <string>
#include <type_traits>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/for_each_base_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RepeatNode : public ForEachBaseNode {
    DECLARE_ACE_TYPE(RepeatNode, ForEachBaseNode);

public:
    static RefPtr<RepeatNode> GetOrCreateRepeatNode(int32_t nodeId);

    explicit RepeatNode(int32_t nodeId) : ForEachBaseNode(V2::JS_REPEAT_ETS_TAG, nodeId) {}

    ~RepeatNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void CreateTempItems();

    // RepeatNode only
    void FinishRepeatRender(std::list<int32_t>& removedElmtId);

    void FlushUpdateAndMarkDirty() override;

    // RepeatNode only
    void MoveChild(uint32_t fromIndex);

    const std::list<std::string>& GetTempIds() const
    {
        return tempIds_;
    }

    void SetIds(std::list<std::string>&& ids)
    {
        ids_ = std::move(ids);
    }

    void ReuseChild(uint32_t index);
    void RecycleChild(uint32_t index);

    void AfterAddChild();
    void SetOnMove(std::function<void(int32_t, int32_t)>&& onMove);
    void SetItemDragHandler(std::function<void(int32_t)>&& onLongPress, std::function<void(int32_t)>&& onDragStart,
        std::function<void(int32_t, int32_t)>&& onMoveThrough, std::function<void(int32_t)>&& onDrop);

    void MoveData(int32_t from, int32_t to) override;
    RefPtr<FrameNode> GetFrameNode(int32_t index) override;
    void InitDragManager(const RefPtr<UINode>& childNode);
    void InitAllChildrenDragManager(bool init);

private:
    std::list<std::string> ids_;
    int32_t from_ = -1;
    int32_t to_ = -1;

    // temp items use to compare each update.
    std::list<std::string> tempIds_;
    std::list<RefPtr<UINode>> tempChildren_;

    // RepeatNode only
    std::vector<RefPtr<UINode>> tempChildrenOfRepeat_;

    ACE_DISALLOW_COPY_AND_MOVE(RepeatNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_REPEAT_NODE_H

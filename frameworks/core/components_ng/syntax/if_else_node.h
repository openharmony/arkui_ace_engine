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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_NODE_H

#include <cstdint>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT IfElseNode : public UINode {
    DECLARE_ACE_TYPE(IfElseNode, UINode);

public:
    static RefPtr<IfElseNode> GetOrCreateIfElseNode(int32_t nodeId);

    explicit IfElseNode(int32_t nodeId) : UINode(V2::JS_IF_ELSE_ETS_TAG, nodeId) {}
    ~IfElseNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void SetBranchId(int32_t value, std::list<int32_t>& removedElmtId);

    int32_t GetBranchId() const
    {
        return branchId_;
    }

    void FlushUpdateAndMarkDirty() override;

    bool TryRetake(const std::string& id);

private:

    // uniquely identifies branches within if elseif else construct:
    // if() { branch } else if () { branch } else { branch}
    // -1 means uninitialized, before first rerender
    int32_t branchId_ = -1;

    // set by CompareBranchId
    // unset by FlushUpdateAndMarkDirty
    bool branchIdChanged_ = false;

    ACE_DISALLOW_COPY_AND_MOVE(IfElseNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_IF_ELSE_NODE_H

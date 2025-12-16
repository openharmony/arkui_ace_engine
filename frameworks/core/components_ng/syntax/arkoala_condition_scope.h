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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_CONDITION_SCOPE_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_CONDITION_SCOPE_NODE_H

#include <cstdint>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ConditionScopeNode : public UINode {
    DECLARE_ACE_TYPE(ConditionScopeNode, UINode);

public:
    explicit ConditionScopeNode(int32_t nodeId);
    ~ConditionScopeNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    bool IsSyntaxNode() const override
    {
        return true;
    }

    void AddChild(const RefPtr<UINode>& child, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false,
        bool addDefaultTransition = false, bool addModalUiextension = false) override;

    void FlushUpdateAndMarkDirty() override;

private:
    ACE_DISALLOW_COPY_AND_MOVE(ConditionScopeNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_CONDITION_SCOPE_NODE_H

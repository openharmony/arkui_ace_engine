/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_DUMMY_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_DUMMY_NODE_H

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/ui_node.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT RecycleDummyNode : public UINode {
    DECLARE_ACE_TYPE(RecycleDummyNode, UINode);

public:
    static RefPtr<RecycleDummyNode> CreateRecycleDummyNode(int32_t nodeId = -1);
    static RefPtr<AceType> WrapRecycleDummyNode(const RefPtr<AceType>& customNode, int32_t nodeId = -1);
    explicit RecycleDummyNode(int32_t nodeId);
    ~RecycleDummyNode() override;
    bool IsAtomicNode() const override
    {
        return true;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_RECYCLE_VIEW_RECYCLE_DUMMY_NODE_H

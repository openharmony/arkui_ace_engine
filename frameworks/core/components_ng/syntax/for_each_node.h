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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H

#include <cstdint>
#include <list>
#include <string>
#include <type_traits>

#include "base/utils/macros.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ForEachNode : public UINode {
    DECLARE_ACE_TYPE(ForEachNode, UINode);

public:
    static RefPtr<ForEachNode> GetOrCreateForEachNode(int32_t nodeId);

    explicit ForEachNode(int32_t nodeId) : UINode(V2::JS_FOR_EACH_ETS_TAG, nodeId) {}
    ~ForEachNode() override = default;

    bool IsAtomicNode() const override
    {
        return false;
    }

    void CreateTempItems();

    void CompareAndUpdateChildren();

    void FlushUpdateAndMarkDirty() override;

    const std::list<std::string>& GetTempIds() const
    {
        return tempIds_;
    }

    void SetIds(std::list<std::string>&& ids)
    {
        ids_ = std::move(ids);
    }

private:
    std::list<std::string> ids_;

    // temp items use to compare each update.
    std::list<std::string> tempIds_;
    std::list<RefPtr<UINode>> tempChildren_;

    ACE_DISALLOW_COPY_AND_MOVE(ForEachNode);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOR_EACH_NODE_H

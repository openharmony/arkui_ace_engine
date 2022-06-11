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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_FOR_EACH_BUILDER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_FOR_EACH_BUILDER_H

#include <unordered_map>

#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ForEachBuilder : public UiNodeId {
    DECLARE_ACE_TYPE(ForEachBuilder, UiNodeId)
public:
    ForEachBuilder() = default;
    ~ForEachBuilder() override = default;

    int32_t GetTotalCount()
    {
        return OnGetTotalCount();
    }

    RefPtr<FrameNode> GetChildByIndex(int32_t index);

protected:
    virtual int32_t OnGetTotalCount() = 0;
    virtual std::pair<std::string, RefPtr<FrameNode>> OnGetChildByIndex(int32_t index) = 0;

private:
    // [index : [key, frameNode]]
    std::unordered_map<int32_t, std::pair<std::string, RefPtr<FrameNode>>> cachedItems_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_SYNTAX_FOREACH_FOR_EACH_BUILDER_H

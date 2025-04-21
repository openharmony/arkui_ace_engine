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
#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_REC_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_REC_NODE_H

#include <string>
#include <vector>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"

namespace OHOS::Ace::NG {
class ACE_FORCE_EXPORT RecNode : public virtual AceType {
    DECLARE_ACE_TYPE(RecNode, AceType);

public:
    inline uint64_t GetSelfId()
    {
        return selfId_;
    }
    inline void SetSelfId(uint64_t selfId)
    {
        selfId_ = selfId;
    }
    inline int32_t GetNodeId()
    {
        return nodeId_;
    }
    inline void SetNodeId(int32_t id)
    {
        nodeId_ = id;
    }
    inline const std::string& GetName()
    {
        return name_;
    }
    inline void SetName(const std::string& name)
    {
        name_ = name;
    }
    inline const std::string& GetDebugLine()
    {
        return debugLine_;
    }
    inline void SetDebugLine(const std::string& debugline)
    {
        debugLine_ = debugline;
    }
    inline int32_t GetParentId()
    {
        return parentId_;
    }
    inline void SetParentId(int32_t id)
    {
        parentId_ = id;
    }

private:
    uint64_t selfId_ = 0;
    int32_t nodeId_ = 0;
    std::string name_;
    std::string debugLine_;
    int32_t parentId_ = -1;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_BASE_REC_NODE_H
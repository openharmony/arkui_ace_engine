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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_NODE_ID_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_NODE_ID_H

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT UiNodeId : public virtual AceType {
    DECLARE_ACE_TYPE(UiNodeId, AceType)

public:
    UiNodeId() = default;
    ~UiNodeId() override = default;

    uint32_t GetRootId() const
    {
        return hostRootId_;
    }

    uint32_t GetPageId() const
    {
        return hostPageId_;
    }

    // TODO: SetHostRootId step on create node.
    void SetHostRootId(uint32_t id)
    {
        hostRootId_ = id;
    }

    // TODO: SetHostPageId step on mount to page.
    void SetHostPageId(uint32_t id)
    {
        hostPageId_ = id;
    }

    void SetSlotId(uint32_t id)
    {
        slotId_ = id;
    }

    uint32_t GetSlotId() const
    {
        return slotId_;
    }

private:
    uint32_t hostRootId_ = 0;
    uint32_t hostPageId_ = 0;
    uint32_t slotId_ = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_PIPELINE_NG_UI_NODE_ID_H

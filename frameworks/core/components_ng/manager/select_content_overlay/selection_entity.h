/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_ENTITY_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_ENTITY_H

#include <string>

#include "base/memory/ace_type.h"
#include "base/utils/macros.h"

namespace OHOS::Ace::NG {

class FrameNode;

class ACE_EXPORT SelectionEntity : public virtual AceType {
    DECLARE_ACE_TYPE(SelectionEntity, AceType);

public:
    SelectionEntity() = default;
    ~SelectionEntity() override = default;

    virtual std::u16string GetSelectionText() = 0;
    virtual RefPtr<FrameNode> GetHostNode() const = 0;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_MANAGER_SELECT_CONTENT_OVERLAY_SELECTION_ENTITY_H

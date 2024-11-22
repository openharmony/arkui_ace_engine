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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FOLDER_STACK_MODEL_H

#include <memory>
#include <mutex>
#include <optional>
#include <string>

#include "base/geometry/dimension.h"
#include "base/utils/macros.h"
#include "core/components/common/layout/align_declaration.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components_ng/pattern/folder_stack/folder_stack_event_info.h"

namespace OHOS::Ace {
class ACE_EXPORT FolderStackModel {
public:
    static FolderStackModel* GetInstance();
    virtual ~FolderStackModel() = default;
    virtual void SetOnFolderStateChange(std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange) = 0;
    virtual void Create(const std::vector<std::string>& itemId) = 0;
    virtual void Create() = 0;
    virtual void SetAlignment(Alignment alignment) = 0;
    virtual void SetEnableAnimation(bool IsEnableAnimation) = 0;
    virtual void SetAutoHalfFold(bool IsAutoHalfFold) = 0;
    virtual void SetOnHoverStatusChange(std::function<void(const NG::FolderEventInfo& folderEventInfo)>&& onChange) = 0;
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_FOLDER_STACK_FOLDER_STACK_MODEL_H

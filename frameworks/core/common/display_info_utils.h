/**
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DISPLAY_INFO_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DISPLAY_INFO_UTILS_H

#include "base/memory/referenced.h"
#include "core/common/display_info.h"

namespace OHOS::Ace {

class ACE_FORCE_EXPORT DisplayInfoUtils final {
public:
    static DisplayInfoUtils& GetInstance();
    RefPtr<DisplayInfo> GetDisplayInfo();
    void InitIsFoldable();
    bool IsFoldable();
    FoldStatus GetCurrentFoldStatus();

private:
    RefPtr<DisplayInfo> displayInfo_ = AceType::MakeRefPtr<DisplayInfo>();
    bool hasInitIsFoldable = false;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_BASE_UTILS_DISPLAY_INFO_UTILS_H

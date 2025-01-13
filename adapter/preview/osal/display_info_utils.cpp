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

#include "core/common/display_info_utils.h"

#include "core/common/display_info.h"
#include "window_display.h"

namespace OHOS::Previewer {
    class PreviewerDisplay;
}
namespace OHOS::Ace {
DisplayInfoUtils& DisplayInfoUtils::GetInstance()
{
    static DisplayInfoUtils instance;
    return instance;
}

RefPtr<DisplayInfo> DisplayInfoUtils::GetDisplayInfo(int32_t displayId)
{
    return AceType::MakeRefPtr<DisplayInfo>();
}

void DisplayInfoUtils::InitIsFoldable() {}

bool DisplayInfoUtils::IsFoldable()
{
    hasInitIsFoldable = true;
    return OHOS::Previewer::PreviewerDisplay::GetInstance().IsFoldable();
}

FoldStatus DisplayInfoUtils::GetCurrentFoldStatus()
{
    auto dmFoldStatus = OHOS::Previewer::PreviewerDisplay::GetInstance().GetFoldStatus();
    CHECK_NULL_RETURN(displayInfo_, FoldStatus::UNKNOWN);
    displayInfo_->SetFoldStatus(static_cast<FoldStatus>(static_cast<uint32_t>(dmFoldStatus)));
    return displayInfo_->GetFoldStatus();
}
} // namespace OHOS::Ace::DisplayInfoUtils

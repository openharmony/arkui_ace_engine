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

#include "adapter/ohos/entrance/window/foldable_window_ohos.h"

#include "dm/display_manager.h"

namespace OHOS::Ace {
RefPtr<FoldableWindow> FoldableWindow::CreateFoldableWindow(int32_t instanceId)
{
    return AceType::MakeRefPtr<FoldableWindowOhos>(instanceId);
}

FoldableWindowOhos::FoldableWindowOhos(int32_t instanceId)
{
    SetFoldableWindowId(windowId_);
}

bool FoldableWindowOhos::IsFoldExpand()
{
    auto foldStatus = Rosen::DisplayManager::GetInstance().GetFoldStatus();
    if ((foldStatus == Rosen::FoldStatus::EXPAND) || (foldStatus == Rosen::FoldStatus::HALF_FOLD)) {
        return true;
    } else {
        return false;
    }
}
} // namespace OHOS::Ace
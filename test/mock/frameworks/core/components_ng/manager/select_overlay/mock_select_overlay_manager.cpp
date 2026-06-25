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

#include "core/components_ng/manager/select_overlay/select_overlay_manager.h"

namespace OHOS::Ace::NG {
SelectOverlayManager::~SelectOverlayManager() = default;

void SelectOverlayManager::OnFontChanged() {}

int32_t SelectOverlayManager::GetTextSelectionHolderId()
{
    return -1;
}

void SelectOverlayManager::MarkDirty(PropertyChangeFlag flag)
{
    (void)flag;
}

bool SelectOverlayManager::ResetSelectionAndDestroySelectOverlay(bool isBackPressed, bool animation)
{
    (void)isBackPressed;
    (void)animation;
    return false;
}
RefPtr<SelectOverlayProxy> SelectOverlayManager::CreateAndShowSelectOverlay(
    const SelectOverlayInfo&, const WeakPtr<SelectionHost>&, bool)
{
    return nullptr;
}
} // namespace OHOS::Ace::NG

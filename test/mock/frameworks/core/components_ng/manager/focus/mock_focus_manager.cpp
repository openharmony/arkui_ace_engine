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

#include "core/components_ng/manager/focus/focus_manager.h"

#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

FocusManager::FocusManager(const RefPtr<PipelineContext>& pipeline): pipeline_(pipeline)
{}

void FocusManager::DumpFocusManager() {}

void FocusManager::WindowFocus(bool isFocus)
{
    (void)isFocus;
}

void FocusManager::WindowFocusMoveEnd() {}

bool FocusManager::SetIsFocusActive(bool isFocusActive, FocusActiveReason reason, bool autoFocusInactive)
{
    if (reason == FocusActiveReason::USE_API) {
        autoFocusInactive_ = autoFocusInactive;
    }
    if (isFocusActive_ == isFocusActive) {
        return false;
    }
    if (!isFocusActive && reason == FocusActiveReason::POINTER_EVENT && !autoFocusInactive_) {
        return false;
    }
    isFocusActive_ = isFocusActive;
    return true;
}

bool FocusManager::IsModalFocusViewStackValid()
{
    return true;
}
} // namespace OHOS::Ace::NG

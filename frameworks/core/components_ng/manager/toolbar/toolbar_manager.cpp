/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "toolbar_manager.h"

namespace OHOS::Ace::NG {
void ToolbarManager::SetSideBarInfo(const ToolbarInfo& info)
{
    sideBarInfo_ = info;
    OnChange();
}

void ToolbarManager::SetSideBarDividerInfo(const ToolbarInfo& info)
{
    sideBarDividerInfo_ = info;
    OnChange();
}

void ToolbarManager::SetNavBarInfo(const ToolbarInfo& info)
{
    navBarInfo_ = info;
    OnChange();
}

void ToolbarManager::SetNavBarDividerInfo(const ToolbarInfo& info)
{
    navBarDividerInfo_ = info;
    OnChange();
}

void ToolbarManager::SetNavDestInfo(const ToolbarInfo& info)
{
    navDestInfo_ = info;
    OnChange();
}

void ToolbarManager::SetToolBarChangeCallback(const std::function<void()>&& callback)
{
    onChangeCallbackFuncs_.emplace_back(std::move(callback));
}

void ToolbarManager::OnChange()
{
    for (auto onChangeCallbackFuncCopy : onChangeCallbackFuncs_) {
        if (onChangeCallbackFuncCopy) {
            onChangeCallbackFuncCopy();
        }
    }
}

void ToolbarManager::SetModifyDoneCallback(const std::function<void()>&& callback)
{
    modifyDoneCallbackFuncs_.emplace_back(std::move(callback));
}

void ToolbarManager::OnToolBarManagerModifyDone()
{
    for (auto modifyDoneCallbackFuncCopy : modifyDoneCallbackFuncs_) {
        if (modifyDoneCallbackFuncCopy) {
            modifyDoneCallbackFuncCopy();
        }
    }
}

void ToolbarManager::SetSideBarColorChangeCallback(
    const std::function<void(const Color&, const Color&, const BlurStyle&)>&& callback)
{
    sideBarColorChangeCallbackFunc_ = std::move(callback);
}

void ToolbarManager::OnChangeSideBarColor()
{
    auto sideBarColorChangeCallbackFuncCopy = sideBarColorChangeCallbackFunc_;
    if (sideBarColorChangeCallbackFuncCopy) {
        sideBarColorChangeCallbackFuncCopy(sideBarBgColor_, sideBarContainerBgColor_, sideBarBlurStyle_);
    }
}
} // namespace OHOS::Ace::NG
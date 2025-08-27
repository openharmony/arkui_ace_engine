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

#include "core/pipeline/container_window_manager.h"

#include "core/common/page_viewport_config.h"

namespace OHOS::Ace {
RefPtr<PageViewportConfig> WindowManager::GetCurrentViewportConfig()
{
    if (getCurrentViewportConfigCallback_) {
        return getCurrentViewportConfigCallback_();
    }
    return nullptr;
}

RefPtr<PageViewportConfig> WindowManager::GetTargetViewportConfig(
    std::optional<Orientation> orientation, std::optional<bool> enableStatusBar,
    std::optional<bool> statusBarAnimation, std::optional<bool> enableNavIndicator)
{
    if (getTargetViewportConfigCallback_) {
        return getTargetViewportConfigCallback_(
            orientation, enableStatusBar, statusBarAnimation, enableNavIndicator);
    }
    return nullptr;
}
} // namespace OHOS::Ace

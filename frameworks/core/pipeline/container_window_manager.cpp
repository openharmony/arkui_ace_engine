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
bool WindowManager::GetPageViewportConfig(
    const PageViewportConfigParams& currentParams, RefPtr<PageViewportConfig>& currentConfig,
    const PageViewportConfigParams& targetParams, RefPtr<PageViewportConfig>& targetConfig)
{
    if (getPageViewportConfigCallback_) {
        return getPageViewportConfigCallback_(currentParams, currentConfig, targetParams, targetConfig);
    }
    return false;
}
} // namespace OHOS::Ace

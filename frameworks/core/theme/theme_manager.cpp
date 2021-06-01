/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "core/theme/theme_manager.h"

#include "core/theme/theme_constants.h"

namespace OHOS::Ace {

ThemeManager::ThemeManager() {}

ThemeManager& ThemeManager::GetInstance()
{
    static auto instance = new ThemeManager();
    return *instance;
}

const RefPtr<Theme> ThemeManager::GetTheme(const ComposeId&, ThemeType type)
{
    if (!globalTheme_) {
        std::lock_guard<std::mutex> lock(themeMutex_);
        if (!globalTheme_) {
            globalTheme_ = AppTheme::Builder().Build();
        }
    }
    if (type == AppTheme::TypeId()) {
        return globalTheme_;
    }
    return globalTheme_->GetTheme(type);
}

} // namespace OHOS::Ace
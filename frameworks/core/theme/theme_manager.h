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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_THEME_THEME_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_THEME_THEME_MANAGER_H

#include <mutex>

#include "base/memory/ace_type.h"
#include "core/pipeline/base/composed_component.h"
#include "core/theme/app_theme.h"
#include "core/theme/theme.h"

namespace OHOS::Ace {

class ACE_EXPORT ThemeManager final {
public:
    ~ThemeManager() = default;
    static ThemeManager& GetInstance();

    const RefPtr<Theme> GetTheme(const ComposeId& id, ThemeType type);

    template<typename T>
    RefPtr<T> GetTheme(const ComposeId& id)
    {
        return AceType::DynamicCast<T>(GetTheme(id, T::TypeId()));
    }

private:
    ThemeManager();
    RefPtr<AppTheme> globalTheme_;
    std::mutex themeMutex_;

    ACE_DISALLOW_COPY_AND_MOVE(ThemeManager);
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_THEME_THEME_MANAGER_H

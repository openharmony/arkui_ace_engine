/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "base/geometry/dimension.h"
#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "core/components/theme/theme.h"
#include "core/components/theme/theme_manager.h"

namespace OHOS::Ace {

class ProgressTheme : public Theme {
    DECLARE_ACE_TYPE(ProgressTheme, Theme)
public:
    ProgressTheme() = default;
    ~ProgressTheme() override = default;

    Dimension GetTrackWidth() const
    {
        return dimension_;
    }

private:
    Dimension dimension_;
};

RefPtr<Theme> ThemeManager::GetTheme(ThemeType type)
{
    LOGE("ThemeManager::GetTheme create ProgressTheme");
    return AceType::MakeRefPtr<ProgressTheme>();
}

} // namespace OHOS::Ace
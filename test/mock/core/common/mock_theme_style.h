/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ARKUI_ACE_ENGINE_TEST_MOCK_CORE_COMMON_MOCK_THEME_STYLE_H
#define FOUNDATION_ARKUI_ACE_ENGINE_TEST_MOCK_CORE_COMMON_MOCK_THEME_STYLE_H

#include "core/components/theme/theme_style.h"

namespace OHOS::Ace {
class MockThemeStyle : public ThemeStyle {
public:
    static RefPtr<ThemeStyle> GetInstance()
    {
        static RefPtr<ThemeStyle> instance = AceType::MakeRefPtr<ThemeStyle>();
        return instance;
    }
};
}
#endif // FOUNDATION_ARKUI_ACE_ENGINE_TEST_MOCK_CORE_COMMON_MOCK_THEME_STYLE_H

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

#include "ui/base/utils/utils.h"
#include "ui/view/theme/theme_factory.h"
#include "ui/view/theme/theme_style.h"
#include "interfaces/inner_api/ace_kit/src/view/theme/theme_style_impl.h"

#include "core/common/container.h"
#include "core/components/theme/theme_manager.h"
#include "core/pipeline/pipeline_base.h"

namespace OHOS::Ace::Kit {
static RefPtr<Ace::ThemeManager> GetThemeManager()
{
    auto container = Ace::Container::Current();
    CHECK_NULL_RETURN(container, nullptr);

    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);

    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager;
}

bool ThemeFactory::CreateTheme(Ace::ThemeType type, BuildFunc func)
{
    auto themeManager = GetThemeManager();
    CHECK_NULL_RETURN(themeManager, false);
    themeManager->RegisterThemeKit(type, func);
    return true;
}

RefPtr<ThemeStyle> ThemeFactory::GetThemeStyle(const std::string& patternName,
    std::optional<std::string> bundleName, std::optional<std::string> moduleName)
{
    if (patternName.empty()) {
        return nullptr;
    }

    auto themeManager = GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);

    auto themeConstant = (bundleName.has_value() && moduleName.has_value()) ?
        themeManager->GetThemeConstants(bundleName.value_or(""), moduleName.value_or("")) :
        themeManager->GetThemeConstants();

    return AceType::MakeRefPtr<ThemeStyleImpl>(themeConstant->GetPatternByName(patternName));
}

RefPtr<Ace::Theme> ThemeFactory::GetTheme(Ace::ThemeType type)
{
    auto themeManager = GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme(type);
}

} // namespace OHOS::Ace::Kit

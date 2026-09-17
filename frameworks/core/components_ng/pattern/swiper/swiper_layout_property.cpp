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
#include "core/components_ng/pattern/swiper/swiper_layout_property.h"

#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "core/components_ng/token_theme/token_theme_storage.h"

namespace OHOS::Ace::NG {
void SwiperLayoutProperty::WithThemeValueCheck(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY_SIX)) {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto themeScopeId = host->GetThemeScopeId();
        if (themeScopeId == 0) {
            auto defaultTheme = TokenThemeStorage::GetInstance()->GetDefaultTheme();
            if (!defaultTheme) {
                return;
            }
        }
        auto theme = host->GetTheme<SwiperIndicatorTheme>(true);
        CHECK_NULL_VOID(theme);

        auto pattern = host->GetPattern<SwiperPattern>();
        CHECK_NULL_VOID(pattern);
        auto arrowParams = pattern->GetSwiperArrowParameters();
        CHECK_NULL_VOID(arrowParams);

        if (arrowParams->parametersByUser.find("arrowColor") == arrowParams->parametersByUser.end()) {
            json->Replace("arrowColor", theme->GetSmallArrowColor().ColorToString().c_str());
        }
        if (arrowParams->parametersByUser.find("backgroundColor") == arrowParams->parametersByUser.end()) {
            json->Replace("arrowBackgroundColor", theme->GetBigArrowBackgroundColor().ColorToString().c_str());
        }
    }
}
} // namespace OHOS::Ace::NG

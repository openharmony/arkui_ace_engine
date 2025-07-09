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

#include "ui/view/theme/token_theme.h"

#include "frameworks/core/common/container.h"
#include "frameworks/core/pipeline_ng/pipeline_context.h"
namespace OHOS::Ace {
bool TokenTheme::IsDarkMode()
{
    auto pipelineContext = OHOS::Ace::NG::PipelineContext::GetCurrentContext();
    if (pipelineContext) {
        auto localMode = pipelineContext->GetLocalColorMode();
        auto systemMode = OHOS::Ace::Container::CurrentColorMode();
        auto mode = (localMode == OHOS::Ace::ColorMode::COLOR_MODE_UNDEFINED) ? systemMode : localMode;
        return mode == OHOS::Ace::ColorMode::DARK;
    }
    // fallback
    return OHOS::Ace::Container::CurrentColorMode() == OHOS::Ace::ColorMode::DARK;
}
} // namespace OHOS::Ace

/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_UTILS_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_UTILS_H

#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/interfaces/cjui/cjui_api.h"
#include "core/components/theme/theme_manager.h"
#include "core/pipeline/pipeline_base.h"

inline ArkUINodeHandle nodePtr(void* ptr)
{
    return reinterpret_cast<ArkUINodeHandle>(ptr);
}

constexpr int32_t INVALID_FONT_STYLE = -1;
constexpr int32_t INVALID_COLOR_VALUE = -1;

namespace OHOS::Ace::NG {

namespace NodeModifier {
    const ArkUIStateModifier* GetUIStateModifier();
    const CJUIStateModifier* GetCJUIStateModifier();
}

template<typename T> OHOS::Ace::RefPtr<T> GetTheme()
{
    auto pipelineContext = OHOS::Ace::PipelineBase::GetCurrentContextSafely();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<T>();
}
}

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_INTERFACES_NODE_UTILS_H

/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_UTILS
#define FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_UTILS

#include <iostream>
#include <memory>
#include "core/components/search/search_theme.h"
#include "core/components/text_field/textfield_theme.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "compatible/components/text_field/text_field_component.h"

namespace OHOS::Ace::Framework {

class ACE_EXPORT TextFieldUtils {
public:
    static void SetCopyOption(const CopyOptions& copyOptions)
    {
        auto component =
            AceType::DynamicCast<TextFieldComponent>(ViewStackProcessor::GetInstance()->GetMainComponent());
        if (!component) {
            LOGW("Failed to get '%{public}s' in view stack", AceType::TypeName<TextFieldComponent>());
            return;
        }
        (component.GetRawPtr()->*(&TextFieldComponent::SetCopyOption))(
            std::forward<decltype(copyOptions)>(copyOptions));
    }

    template<typename T>
    static RefPtr<T> GetTheme()
    {
        auto container = Container::Current();
        CHECK_NULL_RETURN(container, nullptr);
        auto pipelineContext = container->GetPipelineContext();
        CHECK_NULL_RETURN(pipelineContext, nullptr);
        auto themeManager = pipelineContext->GetThemeManager();
        CHECK_NULL_RETURN(themeManager, nullptr);
        auto node = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        return node ? themeManager->GetTheme<T>(node->GetThemeScopeId()) : themeManager->GetTheme<T>();
    }
};

} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_COMPATIBLE_COMPONENTS_TEXT_FIELD_TEXT_FIELD_UTILS
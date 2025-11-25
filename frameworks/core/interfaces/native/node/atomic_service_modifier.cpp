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
#include "core/interfaces/native/node/atomic_service_modifier.h"

#include "interfaces/native/native_type.h"
#include "core/common/container.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/app_bar/app_bar_view.h"
#include "core/components_ng/pattern/app_bar/atomic_service_pattern.h"

namespace OHOS::Ace::NG {
ArkUI_Int32 SetMenuBarVisible(ArkUIContext* context, ArkUI_Bool visible)
{
    CHECK_NULL_RETURN(context, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    ContainerScope scope(context->id);
    auto container = Container::GetContainer(context->id);
    CHECK_NULL_RETURN(container, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    if (!pipelineContext->GetInstallationFree()) {
        return ARKUI_ERROR_CODE_UI_CONTEXT_INVALID;
    }
    auto appbar = container->GetAppBar();
    CHECK_NULL_RETURN(appbar, ARKUI_ERROR_CODE_UI_CONTEXT_INVALID);
    appbar->SetMenuBarVisible(visible);
    return ARKUI_ERROR_CODE_NO_ERROR;
}

namespace NodeModifier {
const ArkUIAtomicServiceModifier* GetAtomicServiceModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIAtomicServiceModifier modifier = {
        .setMenuBarVisible = SetMenuBarVisible
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

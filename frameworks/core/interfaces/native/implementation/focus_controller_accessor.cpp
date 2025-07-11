/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/base/frame_node.h"
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace FocusControllerAccessor {
void RequestFocusImpl(const Ark_String* key)
{
    CHECK_NULL_VOID(key);
    auto convKey = Converter::Convert<std::string>(*key);
    bool isSyncRequest = true;
    auto pipeline = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipeline);
    auto focusManager = pipeline->GetOrCreateFocusManager();
    CHECK_NULL_VOID(focusManager);

    auto focusCallback = [](NG::RequestFocusResult result) {
        switch (result) {
            case NG::RequestFocusResult::NON_FOCUSABLE:
                LOGE("This component is not focusable. %{public}d", ERROR_CODE_NON_FOCUSABLE);
                break;
            case NG::RequestFocusResult::NON_FOCUSABLE_ANCESTOR:
                LOGE("This component has unfocusable ancestor. %{public}d", ERROR_CODE_NON_FOCUSABLE_ANCESTOR);
                break;
            case NG::RequestFocusResult::NON_EXIST:
                LOGE("The component doesn't exist, is currently invisible, or has been disabled. %{public}d",
                    ERROR_CODE_NON_EXIST);
                break;
            default:
                LOGE("An internal error occurred. %{public}d", ERROR_CODE_INTERNAL_ERROR);
                break;
        }
    };

    focusManager->SetRequestFocusCallback(focusCallback);
    pipeline->RequestFocus(convKey, isSyncRequest);
    focusManager->ResetRequestFocusCallback();
}
} // FocusControllerAccessor
const GENERATED_ArkUIFocusControllerAccessor* GetFocusControllerAccessor()
{
    static const GENERATED_ArkUIFocusControllerAccessor FocusControllerAccessorImpl {
        FocusControllerAccessor::RequestFocusImpl,
    };
    return &FocusControllerAccessorImpl;
}

}

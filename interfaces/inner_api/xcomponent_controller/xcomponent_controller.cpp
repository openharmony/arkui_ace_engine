/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "xcomponent_controller.h"

#include "js_native_api.h"
#include "js_native_api_types.h"
#include "jsnapi.h"
#include "napi/native_common.h"
#include "native_engine/impl/ark/ark_native_engine.h"
#include "bridge/declarative_frontend/jsview/js_xcomponent_controller.h"

namespace OHOS::Ace {
std::shared_ptr<XComponentController> XComponentController::GetXComponentControllerFromNapiValue(napi_value napiValue)
{
    auto localRef = NapiValueToLocalValue(napiValue);
    if (localRef->IsNull()) {
        return nullptr;
    }
    auto* jsXComponentController =
        static_cast<Framework::JSXComponentController*>(Local<panda::ObjectRef>(localRef)->GetNativePointerField(0));
    if (!jsXComponentController) {
        return nullptr;
    }
    return jsXComponentController->GetController();
}
} // namespace OHOS::Ace

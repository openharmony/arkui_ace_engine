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

#include "frameworks/bridge/declarative_frontend/engine/functions/js_xcomponent_onload_function.h"

#if defined(XCOMPONENT_SUPPORTED)
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent_controller_binding.h"
#endif
#include "frameworks/bridge/declarative_frontend/jsview/js_xcomponent.h"

namespace OHOS::Ace::Framework {

void JsXComponentOnloadFunction::ExecuteNew(const std::vector<std::string>& keys, const std::string& param)
{
    JSRef<JSVal> jsVal;
    if (keys.size() > 1) {
#if defined(XCOMPONENT_SUPPORTED)
        auto vm = const_cast<EcmaVM*>(jsFunction_->GetEcmaVM());
        Local<JSValueRef> localVal;
        auto result = XComponentClient::GetInstance().GetJSVal(vm, keys[1], localVal);
        if (result) {
            jsVal = JSRef<JSVal>::Make(JsiValue(localVal));
        }
        RefPtr<JSXComponentController> controller =
            XComponentClient::GetInstance().GetControllerFromJSXComponentControllersMap(keys[1]);
        if (result && controller) {
            auto* bindingController = static_cast<JSXComponentControllerBinding*>(Referenced::RawPtr(controller));
            if (bindingController) {
                bindingController->SetXComponentContext(jsVal);
            }
        }
#endif
    }
    ExecuteJS(1, &jsVal);
}

} // namespace OHOS::Ace::Framework

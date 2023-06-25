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

#include "bridge/declarative_frontend/jsview/js_ui_extension.h"

#include <functional>
#include <string>

#include "core/components_ng/pattern/ui_extension/ui_extension_model.h"
#include "core/components_ng/pattern/ui_extension/ui_extension_model_ng.h"

namespace OHOS::Ace {
std::unique_ptr<UIExtensionModel> UIExtensionModel::instance_ = nullptr;
std::mutex UIExtensionModel::mutex_;

UIExtensionModel* UIExtensionModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::UIExtensionModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::UIExtensionModelNG());
            } else {
                return nullptr;
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
void JSUIExtension::JSBind(BindingTarget globalObj)
{
    JSClass<JSUIExtension>::Declare("UIExtensionComponent");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSUIExtension>::StaticMethod("create", &JSUIExtension::Create, opt);
    JSClass<JSUIExtension>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSUIExtension::Create(const JSCallbackInfo& info)
{
    if (!info[0]->IsObject()) {
        return;
    }

    auto want = JSRef<JSObject>::Cast(info[0]);
    if (want->GetProperty("bundleName")->IsNull() || want->GetProperty("bundleName")->IsUndefined() ||
        want->GetProperty("abilityName")->IsNull() || want->GetProperty("abilityName")->IsUndefined()) {
        return;
    }
    std::string bundleName = want->GetProperty("bundleName")->ToString();
    std::string abilityName = want->GetProperty("abilityName")->ToString();

    UIExtensionModel::GetInstance()->Create(bundleName, abilityName);
}
} // namespace OHOS::Ace::Framework

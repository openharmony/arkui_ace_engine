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

#include "frameworks/bridge/declarative_frontend/jsview/js_form_link.h"

#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/form_link/form_link_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<FormLinkModel> FormLinkModel::instance_ = nullptr;
std::mutex FormLinkModel::mutex_;

FormLinkModel* FormLinkModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::FormLinkModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::FormLinkModelNG());
            } else {
                instance_.reset(nullptr);
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

void JSFormLink::Create(const JSCallbackInfo& info)
{
    if (!Container::IsInFormContainer()) {
        APP_LOGW("[Engine Log] FormLink only support in form widget.");
    }
    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }
    auto action = info[0]->ToString();
    FormLinkModel::GetInstance()->Create(action);
}

void JSFormLink::JSBind(BindingTarget globalObj)
{
    JSClass<JSFormLink>::Declare("FormLink");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSFormLink>::StaticMethod("create", &JSFormLink::Create, opt);

    JSClass<JSFormLink>::InheritAndBind<JSViewAbstract>(globalObj);
}

} // namespace OHOS::Ace::Framework

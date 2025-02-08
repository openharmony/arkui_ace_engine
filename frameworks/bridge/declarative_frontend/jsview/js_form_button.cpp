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

#include "frameworks/bridge/declarative_frontend/jsview/js_form_button.h"

#include "base/log/ace_trace.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/jsview/models/form_model_impl.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/form_button/form_button_model.h"
#include "core/components_ng/pattern/form_button/form_button_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"

namespace OHOS::Ace {

FormButtonModel* FormButtonModel::GetInstance()
{
    static NG::FormButtonModelNG instance;
    return &instance;
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const static std::array<Alignment, 9> ALIGNMENT_ARR { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };

void JSFormButton::JSBind(BindingTarget globalObj)
{
    JSClass<JSFormButton>::Declare("FormButton");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSFormButton>::StaticMethod("create", &JSFormButton::Create, opt);
    JSClass<JSFormButton>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSFormButton::Create(const JSCallbackInfo& info)
{
    Alignment alignment = Alignment::CENTER;
    if (info.Length() == 0 || !info[0]->IsObject()) {
        return;
    }
    auto action = info[0]->ToString();
    RequestFormInfo formInfo;

    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> stackAlign = obj->GetProperty("alignContent");
        JSRef<JSVal> bundleName = obj->GetProperty("bundleName");
        JSRef<JSVal> abilityName = obj->GetProperty("abilityName");
        JSRef<JSVal> dimension = obj->GetProperty("dimension");
        JSRef<JSVal> name = obj->GetProperty("name");
        JSRef<JSVal> moduleName = obj->GetProperty("moduleName");

        formInfo.cardName = name->ToString();
        formInfo.bundleName = bundleName->ToString();
        formInfo.abilityName = abilityName->ToString();
        formInfo.moduleName = moduleName->ToString();
        if (!dimension->IsNull() && !dimension->IsEmpty()) {
            formInfo.dimension = dimension->ToNumber<int32_t>();
        }

        if (stackAlign->IsNumber()) {
            int32_t value = stackAlign->ToNumber<int32_t>();
            if (value >= 0 && value < static_cast<int>(ALIGNMENT_ARR.size())) {
                alignment = ALIGNMENT_ARR[value];
            } else {
                FormButtonModel::GetInstance()->Create(action, formInfo);
                return;
            }
        } else {
            FormButtonModel::GetInstance()->Create(action, formInfo);
            return;
        }
    } else {
        FormButtonModel::GetInstance()->Create(action, formInfo);
        return;
    }

    FormButtonModel::GetInstance()->Create(alignment, action, formInfo);
}

} // namespace OHOS::Ace::Framework
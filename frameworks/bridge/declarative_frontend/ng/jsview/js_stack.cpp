/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_stack.h"

#include "base/log/ace_trace.h"
#include "core/common/container.h"
#include "core/components_ng/pattern/stack/stack_view.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"

namespace OHOS::Ace::Framework {

const static std::array<Alignment, 9> ALIGNMENT_ARR { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };

void JSStack::SetStackFit(int value) {}

void JSStack::SetOverflow(int value) {}

void JSStack::SetAlignment(int value)
{
    if (value < 0 || value > 8) {
        return;
    }
    Alignment alignment = ALIGNMENT_ARR[value];
}

void JSStack::SetWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    SetWidth(info[0]);
}

void JSStack::SetWidth(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsWidth(jsValue);
}

void JSStack::SetHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 arguments");
        return;
    }

    SetHeight(info[0]);
}

void JSStack::SetHeight(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsHeight(jsValue);
}

void JSStack::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have atleast 1 arguments");
        return;
    }

    if (!info[0]->IsObject()) {
        LOGE("arg is not Object or String.");
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    SetWidth(sizeObj->GetProperty("width"));
    SetHeight(sizeObj->GetProperty("height"));
}

void JSStack::Create(const JSCallbackInfo& info)
{
    Alignment alignment = Alignment::CENTER;

    if (info.Length() > 0 && info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> stackAlign = obj->GetProperty("alignContent");
        if (stackAlign->IsNumber()) {
            int32_t value = stackAlign->ToNumber<int32_t>();
            alignment = (value >= 0 && value < static_cast<int>(ALIGNMENT_ARR.size())) ? ALIGNMENT_ARR[value]
                                                                                       : Alignment::CENTER;
        }
    }
    NG::StackView::Create(alignment);
}

} // namespace OHOS::Ace::Framework

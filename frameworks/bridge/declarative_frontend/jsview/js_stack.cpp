/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "base/log/log_wrapper.h"
#include "core/common/container.h"
#include "frameworks/bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "frameworks/bridge/declarative_frontend/jsview/models/stack_model_impl.h"
#include "frameworks/core/components_ng/pattern/stack/stack_model_ng.h"

namespace OHOS::Ace {
StackModel* StackModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::StackModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::StackModelNG instance;
        return &instance;
    } else {
        static Framework::StackModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {

#define SET_ALIGNMENT(info, name)                        \
    do {                                                 \
        Alignment alignment = Alignment::TOP_LEFT;       \
        if (!GetAlignment(info, alignment)) {            \
            break;                                       \
        }                                                \
        StackModel::GetInstance()->Set##name(alignment); \
    } while (false)

const static std::array<Alignment, 9> ALIGNMENT_ARR { Alignment::TOP_LEFT, Alignment::TOP_CENTER, Alignment::TOP_RIGHT,
    Alignment::CENTER_LEFT, Alignment::CENTER, Alignment::CENTER_RIGHT, Alignment::BOTTOM_LEFT,
    Alignment::BOTTOM_CENTER, Alignment::BOTTOM_RIGHT };

void JSStack::SetStackFit(int value)
{
    if (value >= static_cast<int>(StackFit::KEEP) && value <= static_cast<int>(StackFit::FIRST_CHILD)) {
        StackModel::GetInstance()->SetStackFit(static_cast<StackFit>(value));
    }
}

void JSStack::SetOverflow(int value)
{
    if (value >= static_cast<int>(Overflow::CLIP) && value <= static_cast<int>(Overflow::OBSERVABLE)) {
        StackModel::GetInstance()->SetOverflow(static_cast<Overflow>(value));
    }
}

bool GetAlignment(const JSCallbackInfo& info, Alignment& alignment)
{
    if (info.Length() != 1 || !info[0]->IsNumber()) {
        StackModel::GetInstance()->SetAlignment(Alignment::CENTER);
        return false;
    }
    auto value = info[0]->ToNumber<size_t>();
    alignment = Alignment::TOP_LEFT;

    switch (value) {
        case 0:
            alignment = Alignment::TOP_LEFT;
            break;
        case 1:
            alignment = Alignment::TOP_CENTER;
            break;
        case 2:
            alignment = Alignment::TOP_RIGHT;
            break;
        case 3:
            alignment = Alignment::CENTER_LEFT;
            break;
        case 4:
            alignment = Alignment::CENTER;
            break;
        case 5:
            alignment = Alignment::CENTER_RIGHT;
            break;
        case 6:
            alignment = Alignment::BOTTOM_LEFT;
            break;
        case 7:
            alignment = Alignment::BOTTOM_CENTER;
            break;
        case 8:
            alignment = Alignment::BOTTOM_RIGHT;
            break;
        default:
            return false;
    }
    return true;
}

void JSStack::SetAlignment(const JSCallbackInfo& info)
{
    SET_ALIGNMENT(info, Alignment);
}

void JSStack::SetWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    SetWidth(info[0]);
}

void JSStack::SetWidth(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsWidth(jsValue);
    StackModel::GetInstance()->SetHasWidth();
}

void JSStack::SetHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    SetHeight(info[0]);
}

void JSStack::SetHeight(const JSRef<JSVal>& jsValue)
{
    JSViewAbstract::JsHeight(jsValue);
    StackModel::GetInstance()->SetHasHeight();
}

void JSStack::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
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
            if (value >= 0 && value < static_cast<int>(ALIGNMENT_ARR.size())) {
                alignment = ALIGNMENT_ARR[value];
            } else {
                StackModel::GetInstance()->Create();
                return;
            }
        } else {
            StackModel::GetInstance()->Create();
            return;
        }
    } else {
        StackModel::GetInstance()->Create();
        return;
    }

    StackModel::GetInstance()->Create(alignment);
}

void JSStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSStack>::Declare("Stack");

    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSStack>::StaticMethod("create", &JSStack::Create, opt);
    JSClass<JSStack>::StaticMethod("stackFit", &JSStack::SetStackFit, opt);
    JSClass<JSStack>::StaticMethod("overflow", &JSStack::SetOverflow, opt);
    JSClass<JSStack>::StaticMethod("align", &JSStack::SetAlignment, opt);
    JSClass<JSStack>::StaticMethod("alignContent", &JSStack::SetAlignment, opt);
    JSClass<JSStack>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSStack>::StaticMethod("width", SetWidth);
    JSClass<JSStack>::StaticMethod("height", SetHeight);
    JSClass<JSStack>::StaticMethod("size", SetSize);
    JSClass<JSStack>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSStack>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSStack>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSStack>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSStack>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSStack>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSStack>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSStack>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSStack>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSStack>::StaticMethod("pointLight", &JSViewAbstract::JsPointLight, opt);
    JSClass<JSStack>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework

/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_foreach.h"

#include <string>

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/functions/js_foreach_function.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components/foreach/for_each_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/syntax/for_each.h"
#include "core/components_part_upd/foreach/foreach_component.h"
#include "core/components_part_upd/foreach/foreach_element.h"
#include "core/components_v2/common/element_proxy.h"

namespace OHOS::Ace::Framework {

void JSForEach::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUsePartialUpdate()) {
        if (Container::IsCurrentUseNewPipeline()) {
            CreateForPartialUpdateNG();
        } else {
            CreateForPartialUpdate();
        }
        return;
    }

    if (info.Length() < 4 || !info[2]->IsObject() || !info[3]->IsFunction() ||
        (!info[0]->IsNumber() && !info[0]->IsString()) || info[1]->IsUndefined() || !info[1]->IsObject()) {
        LOGE("invalid arguments for ForEach");
        return;
    }

    JSRef<JSObject> jsArray = JSRef<JSObject>::Cast(info[2]);
    JSRef<JSVal> jsViewMapperFunc = info[3];
    JSRef<JSVal> jsIdentityMapperFunc;
    RefPtr<JsForEachFunction> jsForEachFunction;
    if (info.Length() > 4 && info[4]->IsFunction()) {
        jsIdentityMapperFunc = info[4];
        jsForEachFunction = AceType::MakeRefPtr<JsForEachFunction>(
            jsArray, JSRef<JSFunc>::Cast(jsIdentityMapperFunc), JSRef<JSFunc>::Cast(jsViewMapperFunc));
    } else {
        jsForEachFunction = AceType::MakeRefPtr<JsForEachFunction>(jsArray, JSRef<JSFunc>::Cast(jsViewMapperFunc));
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ForEachFunc forEachFunc = { [jsForEachFunction]() { return jsForEachFunction->ExecuteIdentityMapper(); },
            [jsForEachFunction](int32_t index) { jsForEachFunction->ExecuteBuilderForIndex(index); } };
        NG::ForEach::Create(forEachFunc);
        return;
    }

    auto* viewStack = ViewStackProcessor::GetInstance();
    std::string viewId = viewStack->ProcessViewId(info[0]->ToString());
    viewStack->Push(AceType::MakeRefPtr<ForEachComponent>(viewId, "ForEach"));

    std::vector<std::string> keys = jsForEachFunction->ExecuteIdentityMapper();
    for (size_t i = 0; i < keys.size(); i++) {
        keys[i].insert(0, "-");
        keys[i].insert(0, info[0]->ToString());
        viewStack->PushKey(keys[i]);

        viewStack->Push(AceType::MakeRefPtr<MultiComposedComponent>(viewStack->GetKey(), "ForEachItem"));
        jsForEachFunction->ExecuteBuilderForIndex(i);
        viewStack->PopContainer();

        viewStack->PopKey();
    }
}

void JSForEach::CreateForPartialUpdate()
{
    // create ForEachComponent and push to stack
    const auto elmtId = ViewStackProcessor::GetInstance()->ClaimElementId();
    const auto elmtIdS = std::to_string(elmtId);
    auto forEachComponent = AceType::MakeRefPtr<OHOS::Ace::PartUpd::ForEachComponent>(elmtIdS, "ForEach");
    forEachComponent->SetElementId(elmtId);
    ViewStackProcessor::GetInstance()->Push(forEachComponent);
}

void JSForEach::CreateForPartialUpdateNG()
{
    // create ForEachComponent and push to stack
    NG::ForEach::Create();
}

void JSForEach::Pop()
{
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ViewStackProcessor::GetInstance()->PopContainer();
        return;
    }
    ViewStackProcessor::GetInstance()->PopContainer();
}

// signature
// elmtId : number
// idList : string[]
// returns bool, true on success
void JSForEach::GetIdArray(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("JSForEach::GetIdArray");
    if ((info.Length() != 2) || !info[1]->IsArray() || info[0]->IsString()) {
        LOGE("Invalid arguments for ForEach.GetIdArray");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }

    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[1]);
    if (jsArr->Length() > 0) {
        LOGE("JS Array must be empty!");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }

    const auto elmtId = info[0]->ToNumber<int32_t>();
    std::list<std::string> cppList;
    if (Container::IsCurrentUseNewPipeline()) {
        cppList = NG::ForEach::GetCurrentIdList(elmtId);
    } else {
        cppList = OHOS::Ace::V2::ForEachElementLookup::GetIdArray(elmtId);
    }

    size_t index = 0;
    for (const auto& id : cppList) {
        LOGD("  array id %{public}d - '%{public}s'", static_cast<int32_t>(index), id.c_str());
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(id.c_str())));
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(index > 0)));
}

// signature
// elmtId : number
// idList : string[]
// no return value
void JSForEach::SetIdArray(const JSCallbackInfo& info)
{
    ACE_SCOPED_TRACE("JSForEach::SetIdArray");

    if ((info.Length() != 2) || !info[1]->IsArray() || info[0]->IsString()) {
        LOGE("Invalid arguments for ForEach.SetIdArray");
        return;
    }

    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[1]);
    std::list<std::string> newIdArr;

    for (size_t i = 0; i < jsArr->Length(); i++) {
        JSRef<JSVal> strId = jsArr->GetValueAt(i);
        std::string value = strId->ToString();
        LOGD("JSForEach::SetIdArray %{public}d - value '%{public}s'", static_cast<int32_t>(i), value.c_str());
        newIdArr.insert(newIdArr.end(), value);
    }

    if (Container::IsCurrentUseNewPipeline()) {
        NG::ForEach::SetNewIds(std::move(newIdArr));
        return;
    }

    auto* stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<PartUpd::ForEachComponent>(stack->GetMainComponent());
    component->SetIdArray(newIdArr);

    // re-render case
    // children of IfElement will be replaced
    // mark them as removed in ElementRegistry
    auto forEachElement =
        ElementRegister::GetInstance()->GetSpecificItemById<PartUpd::ForEachElement>(component->GetElementId());
    if (!forEachElement) {
        // first render case
        return;
    }

    forEachElement->RemoveUnusedChildElementsFromRegistery(newIdArr);
}

// signature is
// id: string | number
// parentView : JSView
void JSForEach::CreateNewChildStart(const JSCallbackInfo& info)
{
    if ((info.Length() != 2) || !info[1]->IsObject() || (!info[0]->IsNumber() && !info[0]->IsString())) {
        LOGE("Invalid arguments for ForEach.CreateNewChildStart");
        return;
    }

    const auto id = info[0]->ToString();
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ForEach::CreateNewChildStart(id);
        return;
    }

    LOGD("Start create child with array id %{public}s.", id.c_str());
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PushKey(id);
    const auto stacksKey = stack->GetKey();
    stack->Push(AceType::MakeRefPtr<MultiComposedComponent>(stacksKey, "ForEachItem"));
}

// signature is
// id: string | number
// parentView : JSView
void JSForEach::CreateNewChildFinish(const JSCallbackInfo& info)
{
    if ((info.Length() != 2) || !info[1]->IsObject() || (!info[0]->IsNumber() && !info[0]->IsString())) {
        LOGE("Invalid arguments for ForEach.CreateNewChildFinish");
        return;
    }

    const auto id = info[0]->ToString();
    if (Container::IsCurrentUseNewPipeline()) {
        NG::ForEach::CreateNewChildFinish(id);
        return;
    }

    LOGD("Finish create child with array id %{public}s.", id.c_str());
    auto* stack = ViewStackProcessor::GetInstance();
    stack->PopKey();
    stack->PopContainer();
}

void JSForEach::JSBind(BindingTarget globalObj)
{
    JSClass<JSForEach>::Declare("ForEach");
    JSClass<JSForEach>::StaticMethod("create", &JSForEach::Create);
    JSClass<JSForEach>::StaticMethod("pop", &JSForEach::Pop);
    JSClass<JSForEach>::StaticMethod("getIdArray", &JSForEach::GetIdArray);
    JSClass<JSForEach>::StaticMethod("setIdArray", &JSForEach::SetIdArray);
    JSClass<JSForEach>::StaticMethod("createNewChildStart", &JSForEach::CreateNewChildStart);
    JSClass<JSForEach>::StaticMethod("createNewChildFinish", &JSForEach::CreateNewChildFinish);
    JSClass<JSForEach>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework

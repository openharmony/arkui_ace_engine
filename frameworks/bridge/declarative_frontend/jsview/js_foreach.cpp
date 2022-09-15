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
#include "core/components_ng/syntax/for_each_model_ng.h"
#include "bridge/declarative_frontend/jsview/models/for_each_model_impl.h"
#include "bridge/declarative_frontend/engine/functions/js_foreach_function.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"


namespace OHOS::Ace {

std::unique_ptr<ForEachModel> ForEachModel::instance = nullptr;

ForEachModel* ForEachModel::GetInstance()
{
    if (!instance) {
        if (Container::IsCurrentUseNewPipeline()) {
            instance.reset(new NG::ForEachModelNG());
        } else {
            instance.reset(new Framework::ForEachModelImpl());
        }
    }
    return instance.get();
}
} // namespace OHOS::Ace


namespace OHOS::Ace::Framework {

// Create(...)
// NG:       no params
// Classic:  cmpilerGenId, array, itemGenFunc, idGenFunction
void JSForEach::Create(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        ForEachModel::GetInstance()->Create();
        return;
    }

    if (info.Length() < 4 || !info[2]->IsObject() || !info[3]->IsFunction() ||
        (!info[0]->IsNumber() && !info[0]->IsString()) || info[1]->IsUndefined() || !info[1]->IsObject()) {
        LOGE("Invalid arguments for ForEach");
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

        OHOS::Ace::ForEachFunc forEachFunc = { [jsForEachFunction]() { return jsForEachFunction->ExecuteIdentityMapper(); },
            [jsForEachFunction](int32_t index) { jsForEachFunction->ExecuteBuilderForIndex(index); } };
        ForEachModel::GetInstance()->Create(info[0]->ToString(), forEachFunc);
    }

void JSForEach::Pop()
{
    ForEachModel::GetInstance()->Pop();
}

// partial update / NG only
// signature
// nodeId/elmtId : number
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
    std::list<std::string> cppList =  ForEachModel::GetInstance()->GetCurrentIdList(elmtId);
    
    size_t index = 0;
    for (const auto& id : cppList) {
        LOGD("  array id %{public}d - '%{public}s'", static_cast<int32_t>(index), id.c_str());
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(id.c_str())));
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(index > 0)));
}

// partial update / NG only
// signature
// nodeId/elmtId : number   // FIXME, not used!
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

        ForEachModel::GetInstance()->SetNewIds(std::move(newIdArr));
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
        ForEachModel::GetInstance()->CreateNewChildStart(id);
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
    ForEachModel::GetInstance()->CreateNewChildFinish(id);
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

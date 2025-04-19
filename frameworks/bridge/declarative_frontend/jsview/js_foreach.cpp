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
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/for_each_model_impl.h"
#include "bridge/declarative_frontend/engine/functions/js_foreach_function.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_model.h"


namespace OHOS::Ace {
ForEachModel* ForEachModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::ForEachModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::ForEachModelNG instance;
        return &instance;
    } else {
        static Framework::ForEachModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace {

enum {
    PARAM_ELMT_ID = 0,
    PARAM_JS_ARRAY = 1,
    PARAM_DIFF_ID = 2,
    PARAM_DUPLICATE_ID = 3,
    PARAM_DELETE_ID = 4,
    PARAM_ID_ARRAY_LENGTH = 5,
};
} // namespace

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
        TAG_LOGW(AceLogTag::ACE_FOREACH, "Invalid arguments for ForEach");
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

    OHOS::Ace::ForEachFunc forEachFunc = {
        [jsForEachFunction]() { return jsForEachFunction->ExecuteIdentityMapper(); },
        [jsForEachFunction](int32_t index) { jsForEachFunction->ExecuteBuilderForIndex(index); } };
    ForEachModel::GetInstance()->Create(info[0]->ToString(), forEachFunc);
}

void JSForEach::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSForEach][pop]", &JSForEach::Pop);
    }
    ForEachModel::GetInstance()->Pop();
}

// partial update / NG only
// signature
// nodeId/elmtId : number
// idList : string[]
// returns bool, true on success
void JSForEach::GetIdArray(const JSCallbackInfo& info)
{
    if ((info.Length() != 2) || !info[1]->IsArray() || info[0]->IsString()) {
        TAG_LOGW(AceLogTag::ACE_FOREACH, "Invalid arguments for ForEach.GetIdArray");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }

    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[1]);
    if (jsArr->Length() > 0) {
        TAG_LOGW(AceLogTag::ACE_FOREACH, "JS Array must be empty!");
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    if (!info[0]->IsNumber()) {
        return;
    }
    const auto elmtId = info[0]->ToNumber<int32_t>();
    std::list<std::string> idList =  ForEachModel::GetInstance()->GetCurrentIdList(elmtId);

    size_t index = 0;
    for (const auto& id : idList) {
        jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(id.c_str())));
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(index > 0)));
}

// Partial update / NG only
// Gets idList as a input and stores it.
// Fill diffIds with new indexes as an output.
// Fill duplicateIds with duplica IDs detected.
// nodeId/elmtId : number
// idList : string[]
// diffIds : number[]
// duplicateIds : number[]
// no return value
void JSForEach::SetIdArray(const JSCallbackInfo& info)
{
    if (info.Length() != PARAM_ID_ARRAY_LENGTH || !info[PARAM_ELMT_ID]->IsNumber() ||
        !info[PARAM_JS_ARRAY]->IsArray() || !info[PARAM_DIFF_ID]->IsArray() ||
        !info[PARAM_DUPLICATE_ID]->IsArray() || !info[PARAM_DELETE_ID]->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_FOREACH, "Invalid arguments for ForEach.SetIdArray");
        return;
    }

    const auto elmtId = info[PARAM_ELMT_ID]->ToNumber<int32_t>();
    JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[PARAM_JS_ARRAY]);
    JSRef<JSArray> diffIds = JSRef<JSArray>::Cast(info[PARAM_DIFF_ID]);
    JSRef<JSArray> duplicateIds = JSRef<JSArray>::Cast(info[PARAM_DUPLICATE_ID]);
    std::list<std::string> newIdArr;

    if (diffIds->Length() > 0 || duplicateIds->Length() > 0) {
        TAG_LOGW(AceLogTag::ACE_FOREACH, "Invalid arguments for ForEach.SetIdArray output arrays must be empty!");
        return;
    }

    const std::list<std::string>& previousIDList = ForEachModel::GetInstance()->GetCurrentIdList(elmtId);
    std::unordered_set<std::string> oldIdsSet(previousIDList.begin(), previousIDList.end());
    std::unordered_set<std::string> newIds;

    size_t diffIndx = 0;
    size_t duplicateIndx = 0;
    for (size_t i = 0; i < jsArr->Length(); i++) {
        JSRef<JSVal> strId = jsArr->GetValueAt(i);
        // Save return value of insert to know was it duplicate...
        std::pair<std::unordered_set<std::string>::iterator, bool> ret = newIds.insert(strId->ToString());
        // Duplicate Id detected. Will return index of those to caller.
        if (!ret.second) {
            duplicateIds->SetValueAt(duplicateIndx++, JSRef<JSVal>::Make(ToJSValue(i)));
        } else {
            // ID was not duplicate. Accept it.
            newIdArr.emplace_back(*ret.first);
            // Check was ID previously available or totally new one.
            if (oldIdsSet.find(*ret.first) == oldIdsSet.end()) {
                // Populate output diff array with this index that was not in old array.
                diffIds->SetValueAt(diffIndx++, JSRef<JSVal>::Make(ToJSValue(i)));
            }
        }
    }
    ForEachModel::GetInstance()->SetNewIds(std::move(newIdArr));

    std::list<int32_t> removedElmtIds;
    ForEachModel::GetInstance()->SetRemovedElmtIds(removedElmtIds);

    if (removedElmtIds.size()) {
        JSRef<JSArray> jsArr = JSRef<JSArray>::Cast(info[PARAM_DELETE_ID]);
        size_t index = jsArr->Length();

        for (const auto& rmElmtId : removedElmtIds) {
            jsArr->SetValueAt(index++, JSRef<JSVal>::Make(ToJSValue(rmElmtId)));
        }
    }
}

// signature is
// id: string | number
// parentView : JSView
void JSForEach::CreateNewChildStart(const JSCallbackInfo& info)
{
    if ((info.Length() != 2) || !info[1]->IsObject() || (!info[0]->IsNumber() && !info[0]->IsString())) {
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
        return;
    }

    const auto id = info[0]->ToString();
    ForEachModel::GetInstance()->CreateNewChildFinish(id);
}

void JSForEach::OnMove(const JSCallbackInfo& info)
{
    if (info[0]->IsFunction()) {
        auto context = info.GetExecutionContext();
        auto onMove = [execCtx = context, func = JSRef<JSFunc>::Cast(info[0])](int32_t from, int32_t to) {
            auto params = ConvertToJSValues(from, to);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
        ForEachModel::GetInstance()->OnMove(std::move(onMove));
        if ((info.Length() > 1) && info[1]->IsObject()) {
            JsParseItemDragEventHandler(context, info[1]);
        } else {
            ForEachModel::GetInstance()->SetItemDragHandler(nullptr, nullptr, nullptr, nullptr);
        }
    } else {
        ForEachModel::GetInstance()->OnMove(nullptr);
        ForEachModel::GetInstance()->SetItemDragHandler(nullptr, nullptr, nullptr, nullptr);
    }
}

void JSForEach::JsParseItemDragEventHandler(const JsiExecutionContext& context, const JSRef<JSVal>& jsValue)
{
    auto itemDragEventObj = JSRef<JSObject>::Cast(jsValue);

    auto onLongPress = itemDragEventObj->GetProperty("onLongPress");
    std::function<void(int32_t)> onLongPressCallback;
    if (onLongPress->IsFunction()) {
        onLongPressCallback = [execCtx = context, func = JSRef<JSFunc>::Cast(onLongPress)](int32_t index) {
            auto params = ConvertToJSValues(index);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
    }

    auto onDragStart = itemDragEventObj->GetProperty("onDragStart");
    std::function<void(int32_t)> onDragStartCallback;
    if (onDragStart->IsFunction()) {
        onDragStartCallback = [execCtx = context, func = JSRef<JSFunc>::Cast(onDragStart)](int32_t index) {
            auto params = ConvertToJSValues(index);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
    }

    auto onMoveThrough = itemDragEventObj->GetProperty("onMoveThrough");
    std::function<void(int32_t, int32_t)> onMoveThroughCallback;
    if (onMoveThrough->IsFunction()) {
        onMoveThroughCallback = [execCtx = context, func = JSRef<JSFunc>::Cast(onMoveThrough)](
                                    int32_t from, int32_t to) {
            auto params = ConvertToJSValues(from, to);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
    }

    auto onDrop = itemDragEventObj->GetProperty("onDrop");
    std::function<void(int32_t)> onDropCallback;
    if (onDrop->IsFunction()) {
        onDropCallback = [execCtx = context, func = JSRef<JSFunc>::Cast(onDrop)](int32_t index) {
            auto params = ConvertToJSValues(index);
            func->Call(JSRef<JSObject>(), params.size(), params.data());
        };
    }
    ForEachModel::GetInstance()->SetItemDragHandler(std::move(onLongPressCallback), std::move(onDragStartCallback),
        std::move(onMoveThroughCallback), std::move(onDropCallback));
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
    JSClass<JSForEach>::StaticMethod("onMove", &JSForEach::OnMove);
    JSClass<JSForEach>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework

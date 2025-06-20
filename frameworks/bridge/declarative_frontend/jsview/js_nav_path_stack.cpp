/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_nav_path_stack.h"

#include "base/log/ace_scoring_log.h"
#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/engine/js_ref_ptr.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/pattern/navigation/navigation_pattern.h"
#include "core/components_ng/pattern/navigation/navigation_group_node.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "interfaces/napi/kits/utils/napi_utils.h"

namespace OHOS::Ace::Framework {
namespace {
constexpr char JS_NAV_PATH_STACK_CLASS_NAME[] = "NavPathStack";
constexpr char JS_SET_NATIVESTACK_FUNC[] = "setNativeStack";
constexpr char JS_NAV_PATH_ARRAY_NAME[] = "pathArray";
constexpr char JS_NAV_PATH_ANIMATE_NAME[] = "animated";
constexpr char JS_NAV_PATH_ISREPLACE_NAME[] = "isReplace";

constexpr char JS_NAV_PATH_ISFORCESET_NAME[] = "isForceSet";
constexpr char JS_NAV_PATH_NAME_NAME[] = "name";
constexpr char JS_NAV_PATH_PARAM_NAME[] = "param";
constexpr char JS_NAV_PATH_ONPOP_NAME[] = "onPop";
constexpr char JS_NAV_PATH_ISENTRY_NAME[] = "isEntry";
constexpr char JS_NAV_PATH_NAVDESTINATIONID_NAME[] = "navDestinationId";
constexpr int32_t ARGC_COUNT_THREE = 3;
}

void JSNavPathStack::JSBind(BindingTarget globalObj)
{
    JSClass<JSNavPathStack>::Declare("NativeNavPathStack");
    JSClass<JSNavPathStack>::Method("onStateChanged", &JSNavPathStack::OnStateChanged);
    JSClass<JSNavPathStack>::CustomMethod("onPopCallback", &JSNavPathStack::OnPopCallback);
    JSClass<JSNavPathStack>::CustomMethod("getPathStack", &JSNavPathStack::GetPathStack);
    JSClass<JSNavPathStack>::CustomMethod("setPathStack", &JSNavPathStack::SetPathStack);
    JSClass<JSNavPathStack>::CustomMethod("isHomeName", &JSNavPathStack::IsHomeName);
    JSClass<JSNavPathStack>::Bind(globalObj, &JSNavPathStack::Constructor, &JSNavPathStack::Destructor);
}

void JSNavPathStack::Constructor(const JSCallbackInfo& info)
{
    auto stack = Referenced::MakeRefPtr<JSNavPathStack>();
    stack->IncRefCount();
    info.SetReturnValue(Referenced::RawPtr(stack));
}

void JSNavPathStack::Destructor(JSNavPathStack* stack)
{
    if (stack != nullptr) {
        stack->DecRefCount();
    }
}

JSRef<JSObject> JSNavPathStack::CreateNewNavPathStackJSObject()
{
    JSRef<JSObject> empty;
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, empty);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, empty);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return empty;
    }
    napi_value constructor;
    ret = napi_get_named_property(env, global, JS_NAV_PATH_STACK_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return empty;
    }

    napi_value obj;
    ret = napi_new_instance(env, constructor, 0, nullptr, &obj);
    if (ret != napi_ok) {
        return empty;
    }

    JSRef<JSVal> value = JsConverter::ConvertNapiValueToJsVal(obj);
    if (!value->IsObject()) {
        return empty;
    }

    return JSRef<JSObject>::Cast(value);
}

void JSNavPathStack::SetNativeNavPathStack(JSRef<JSObject> jsStack, JSRef<JSObject> nativeStack)
{
    if (jsStack->IsEmpty() || nativeStack->IsEmpty()) {
        return;
    }

    auto property = jsStack->GetProperty(JS_SET_NATIVESTACK_FUNC);
    if (!property->IsFunction()) {
        return;
    }

    auto setNativeStackFunc = JSRef<JSFunc>::Cast(property);
    JSRef<JSVal> params[1];
    params[0] = JSRef<JSVal>::Cast(nativeStack);
    setNativeStackFunc->Call(jsStack, 1, params);
}

bool JSNavPathStack::CheckIsValid(JSValueWrapper object)
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, false);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, false);
    auto env = reinterpret_cast<napi_env>(nativeEngine);

    napi_value global;
    napi_status ret = napi_get_global(env, &global);
    if (ret != napi_ok) {
        return false;
    }
    napi_value constructor;
    ret = napi_get_named_property(env, global, JS_NAV_PATH_STACK_CLASS_NAME, &constructor);
    if (ret != napi_ok) {
        return false;
    }
    bool isInstance = false;
    ScopeRAII scope(reinterpret_cast<napi_env>(nativeEngine));
    napi_value stack = nativeEngine->ValueToNapiValue(object);
    napi_instanceof(env, stack, constructor, &isInstance);
    return isInstance;
}

void JSNavPathStack::GetPathStack(const JSCallbackInfo& info)
{
    JSRef<JSArray> empty;
    if (info.Length() < 1) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "invalid input length");
        info.SetReturnValue(empty);
        return;
    }
    if (!info[0]->IsObject()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "invalid input params navPathStack");
        info.SetReturnValue(empty);
        return;
    }
    auto navPathStack = JSRef<JSObject>::Cast(info[0]);
    if (navPathStack->IsEmpty() || navPathStack->IsUndefined()) {
        info.SetReturnValue(empty);
        return;
    }
    auto pathArrayValue = navPathStack->GetProperty(JS_NAV_PATH_ARRAY_NAME);
    if (pathArrayValue->IsEmpty() || !pathArrayValue->IsArray()) {
        info.SetReturnValue(empty);
        return;
    }
    auto pathArray = JSRef<JSArray>::Cast(pathArrayValue);
    auto arrayLength = pathArray->Length();
    JSRef<JSArray> copyInfo = JSRef<JSArray>::New(arrayLength);
    for (size_t index = 0; index < arrayLength; index++) {
        CopyPathInfo(pathArray, copyInfo, index);
    }
    info.SetReturnValue(std::move(copyInfo));
    return;
}

void JSNavPathStack::CopyPathInfo(const JSRef<JSArray>& origin, JSRef<JSArray>& dest, size_t index)
{
    auto indexedValue = origin->GetValueAt(index);
    if (!indexedValue->IsObject()) {
        return;
    }
    auto originObj = JSRef<JSObject>::Cast(indexedValue);
    if (originObj->IsEmpty() || originObj->IsUndefined()) {
        return;
    }
    auto dstObj = JSRef<JSObject>::New();
    auto name = originObj->GetProperty(JS_NAV_PATH_NAME_NAME);
    auto param = originObj->GetProperty(JS_NAV_PATH_PARAM_NAME);
    auto onPop = originObj->GetProperty(JS_NAV_PATH_ONPOP_NAME);
    auto isEntry = originObj->GetProperty(JS_NAV_PATH_ISENTRY_NAME);
    auto id = originObj->GetProperty(JS_NAV_PATH_NAVDESTINATIONID_NAME);
    dstObj->SetPropertyObject(JS_NAV_PATH_NAME_NAME, name);
    dstObj->SetPropertyObject(JS_NAV_PATH_PARAM_NAME, param);
    dstObj->SetPropertyObject(JS_NAV_PATH_ONPOP_NAME, onPop);
    dstObj->SetPropertyObject(JS_NAV_PATH_ISENTRY_NAME, isEntry);
    dstObj->SetPropertyObject(JS_NAV_PATH_NAVDESTINATIONID_NAME, id);
    dest->SetValueAt(index, dstObj);
}

void JSNavPathStack::SetPathStack(const JSCallbackInfo& info)
{
    if (info.Length() < ARGC_COUNT_THREE) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "invalid input length");
        return;
    }
    if (!info[0]->IsObject()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "invalid input params navPathStack");
        return;
    }
    auto navPathStack = JSRef<JSObject>::Cast(info[0]);
    if (!info[1]->IsArray()) {
        TAG_LOGI(AceLogTag::ACE_NAVIGATION, "invalid input params navPathArray");
        return;
    }
    auto setPathArray = JSRef<JSArray>::Cast(info[1]);
    auto animated = info[2];
    if (navPathStack->IsEmpty() || navPathStack->IsUndefined()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "navpathStack is invalid");
        return;
    }
    auto curPathArrayValue = navPathStack->GetProperty(JS_NAV_PATH_ARRAY_NAME);
    if (curPathArrayValue->IsEmpty() || !curPathArrayValue->IsArray()) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "current navpathInfo is invalid");
        return;
    }
    auto curPathArray = JSRef<JSArray>::Cast(curPathArrayValue);
    if (setPathArray->IsEmpty() || !setPathArray->IsArray()) {
        TAG_LOGW(AceLogTag::ACE_NAVIGATION, "invalid pathInfo is set");
        return;
    }
    auto setPathLength = setPathArray->Length();

    JSRef<JSArray> newPathArray = JSRef<JSArray>::New(setPathLength);
    for (size_t index = 0; index < setPathLength; index++) {
        /**
         * step1. copy user set path info.
         * step2. check if name and id is valid or not.
         * step3. if valid, find existing node that name and id is same, and update param info;
         *  otherwise, set id as undefined.
         * step4. set isForceSet flag as true.
         */
        auto indexedValue = setPathArray->GetValueAt(index);
        if (!indexedValue->IsObject()) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "value at index %{public}zu in set navPathArray is invalid", index);
            continue;
        }
        auto setPathInfo = JSRef<JSObject>::Cast(indexedValue);
        JSRef<JSObject> pathInfo = JSRef<JSObject>::Make(setPathInfo.Get());
        auto navDestinationId = setPathInfo->GetProperty(JS_NAV_PATH_NAVDESTINATIONID_NAME);
        auto name = setPathInfo->GetProperty(JS_NAV_PATH_NAME_NAME);
        if (!navDestinationId->IsEmpty() && navDestinationId->IsString() &&
            !name->IsEmpty() && name->IsString()) {
            auto navIdStr = navDestinationId->ToString();
            auto nameStr = name->ToString();
            bool findInCurArray = FindNavInfoInPreArray(pathInfo, curPathArray, navIdStr, nameStr);
            if (findInCurArray) {
                auto param = setPathInfo->GetProperty(JS_NAV_PATH_PARAM_NAME);
                auto onPop = setPathInfo->GetProperty(JS_NAV_PATH_ONPOP_NAME);
                auto isEntry = setPathInfo->GetProperty(JS_NAV_PATH_ISENTRY_NAME);
                pathInfo->SetPropertyObject(JS_NAV_PATH_PARAM_NAME, param);
                pathInfo->SetPropertyObject(JS_NAV_PATH_ONPOP_NAME, onPop);
                pathInfo->SetPropertyObject(JS_NAV_PATH_ISENTRY_NAME, isEntry);
            }
        }
        pathInfo->SetProperty<bool>(JS_NAV_PATH_ISFORCESET_NAME, true);
        newPathArray->SetValueAt(index, pathInfo);
    }
    navPathStack->SetPropertyObject(JS_NAV_PATH_ARRAY_NAME, std::move(newPathArray));
    bool finalAnimate = true;
    if (!animated->IsEmpty() && animated->IsBoolean()) {
        finalAnimate = animated->ToBoolean();
    }
    navPathStack->SetProperty<bool>(JS_NAV_PATH_ANIMATE_NAME, finalAnimate);
    navPathStack->SetProperty<uint32_t>(JS_NAV_PATH_ISREPLACE_NAME, 0);
    TAG_LOGI(AceLogTag::ACE_NAVIGATION, "set path stack, new size :%{public}zu, animated %{public}d",
        setPathLength, finalAnimate);
    OnStateChanged();
}

void JSNavPathStack::IsHomeName(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsString() || !isHomeNameCallback_) {
        info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(false)));
        return;
    }
    auto name = info[0]->ToString();
    bool isHomeName = isHomeNameCallback_(name);
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(isHomeName)));
}

bool JSNavPathStack::FindNavInfoInPreArray(
    JSRef<JSObject>& destInfo, JSRef<JSArray>& originArray, std::string& navIdStr, std::string& nameStr)
{
    auto curPathLength = originArray->Length();
    for (size_t i = 0; i < curPathLength; i++) {
        auto indexedValue = originArray->GetValueAt(i);
        if (!indexedValue->IsObject()) {
            TAG_LOGI(AceLogTag::ACE_NAVIGATION, "value at index %{public}zu in pre navPathArray is invalid", i);
            continue;
        }
        auto curPathInfo = JSRef<JSObject>::Cast(indexedValue);
        auto curNavDestinationId = curPathInfo->GetProperty(JS_NAV_PATH_NAVDESTINATIONID_NAME);
        std::string curNavIdStr;
        if (!curNavDestinationId->IsEmpty() && curNavDestinationId->IsString()) {
            curNavIdStr = curNavDestinationId->ToString();
        }
        auto curName = curPathInfo->GetProperty(JS_NAV_PATH_NAME_NAME);
        std::string curNameStr;
        if (!curName->IsEmpty() && curName->IsString()) {
            curNameStr = curName->ToString();
        }
        if (navIdStr == curNavIdStr && nameStr == curNameStr) {
            destInfo = JSRef<JSObject>::Make(curPathInfo.Get());
            return true;
        }
    }
    destInfo->SetPropertyObject(JS_NAV_PATH_NAVDESTINATIONID_NAME, JsiValue::Undefined());
    return false;
}

void JSNavPathStack::OnPopCallback(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (onPopCallback_) {
        onPopCallback_(info[0]);
    }
}
} // namespace OHOS::Ace::Framework

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
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_container_modal_view_register.h"

#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/custom/custom_title_node.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_value_conversions.h"

namespace OHOS::Ace::Framework {

void BindingCustomBaseFromJS(
    const JSRef<JSObject> object, const EcmaVM* vm, const RefPtr<NG::CustomTitleNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto id = ContainerScope::CurrentId();
    const JSRef<JSVal> onWindowFocused = object->GetProperty("onWindowFocused");
    if (onWindowFocused->IsFunction()) {
        JSRef<JSFunc> jsOnWindowFocusedFunc = JSRef<JSFunc>::Cast(onWindowFocused);
        auto callback = [obj = object, jsFunc = jsOnWindowFocusedFunc, id]() {
            ContainerScope scope(id);
            jsFunc->Call(obj);
        };
        customNode->SetOnWindowFocusedCallback(callback);
    }

    const JSRef<JSVal> onWindowUnfocused = object->GetProperty("onWindowUnfocused");
    if (onWindowUnfocused->IsFunction()) {
        JSRef<JSFunc> jsOnWindowUnfocusedFunc = JSRef<JSFunc>::Cast(onWindowUnfocused);
        auto callback = [obj = object, jsFunc = jsOnWindowUnfocusedFunc, id]() {
            ContainerScope scope(id);
            jsFunc->Call(obj);
        };
        customNode->SetOnWindowUnfocusedCallback(callback);
    }
}

void BindingCustomTitleFromJS(
    const JSRef<JSObject> object, const EcmaVM* vm, const RefPtr<NG::CustomTitleNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto id = ContainerScope::CurrentId();
    const JSRef<JSVal> setAppTitle = object->GetProperty("setAppTitle");
    if (setAppTitle->IsFunction()) {
        JSRef<JSFunc> jsSetAppTitleFunc = JSRef<JSFunc>::Cast(setAppTitle);
        auto callback = [obj = object, jsFunc = jsSetAppTitleFunc, id, vm](const std::string& title) {
            ContainerScope scope(id);
            CHECK_NULL_VOID(vm);
            JSRef<JSVal> param = JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, title));
            jsFunc->Call(obj, 1, &param);
        };
        customNode->SetAppTitleCallback(callback);
    }
#ifdef PIXEL_MAP_SUPPORTED
    const JSRef<JSVal> setAppIcon = object->GetProperty("setAppIcon");
    if (setAppIcon->IsFunction()) {
        JSRef<JSFunc> jsSetAppIconFunc = JSRef<JSFunc>::Cast(setAppIcon);
        auto callback = [obj = object, jsFunc = jsSetAppIconFunc, id](const RefPtr<PixelMap>& icon) {
            ContainerScope scope(id);
            JSRef<JSVal> param = ConvertPixmap(icon);
            jsFunc->Call(obj, 1, &param);
        };
        customNode->SetAppIconCallback(callback);
    }
#endif
}

void BindingCustomButtonFromJS(
    const JSRef<JSObject> object, const EcmaVM* vm, const RefPtr<NG::CustomTitleNode>& customNode)
{
    CHECK_NULL_VOID(customNode);
    auto id = ContainerScope::CurrentId();
    const JSRef<JSVal> setCustomCallback = object->GetProperty("setCustomCallback");
    if (setCustomCallback->IsFunction()) {
        JSRef<JSFunc> jsSetCustomCallbackFunc = JSRef<JSFunc>::Cast(setCustomCallback);
        auto callback = [obj = object, jsFunc = jsSetCustomCallbackFunc, id, vm](
                            const std::string& eventName, const std::string& param) {
            ContainerScope scope(id);
            CHECK_NULL_VOID(vm);
            JSRef<JSVal> jsEventName = JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, eventName));
            JSRef<JSVal> jsParam = JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, param));
            JSRef<JSVal> paramArray[2] = { jsEventName, jsParam };
            jsFunc->Call(obj, 2, paramArray);
        };
        customNode->SetCustomCallback(callback);
    }
}

void AddCustomTitleBarComponent(const panda::Local<panda::ObjectRef>& obj)
{
    const auto object = JSRef<JSObject>::Make(obj);
    const EcmaVM* vm = object->GetEcmaVM();
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(vm, 0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }
    auto uiNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode(true));
    CHECK_NULL_VOID(uiNode);
    auto customNode = AceType::DynamicCast<NG::CustomTitleNode>(uiNode);
    CHECK_NULL_VOID(customNode);

    BindingCustomBaseFromJS(object, vm, customNode);
    BindingCustomTitleFromJS(object, vm, customNode);
    BindingCustomButtonFromJS(object, vm, customNode);
    NG::ViewStackProcessor::GetInstance()->SetCustomTitleNode(customNode);
}

void AddCustomWindowMaskComponent(const panda::Local<panda::ObjectRef>& obj)
{
    const auto object = JSRef<JSObject>::Make(obj);
    const EcmaVM* vm = object->GetEcmaVM();
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(vm, 0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }

    auto uiNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode(true));
    CHECK_NULL_VOID(uiNode);
    NG::ViewStackProcessor::GetInstance()->SetCustomWindowMaskNode(uiNode);
}

void AddCustomButtonComponent(const panda::Local<panda::ObjectRef>& obj)
{
    const auto object = JSRef<JSObject>::Make(obj);
    const EcmaVM* vm = object->GetEcmaVM();
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(vm, 0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }
    auto uiNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode(true));
    CHECK_NULL_VOID(uiNode);
    auto customNode = AceType::DynamicCast<NG::CustomTitleNode>(uiNode);
    CHECK_NULL_VOID(customNode);
    BindingCustomBaseFromJS(object, vm, customNode);
    BindingCustomButtonFromJS(object, vm, customNode);
    NG::ViewStackProcessor::GetInstance()->SetCustomButtonNode(customNode);
}

panda::Local<panda::JSValueRef> JsLoadCustomTitleBar(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    AddCustomTitleBarComponent(obj);

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsLoadCustomWindowMask(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    AddCustomWindowMaskComponent(obj);

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsLoadCustomButton(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    AddCustomButtonComponent(obj);

    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::Framework

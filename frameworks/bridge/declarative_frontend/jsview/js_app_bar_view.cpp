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

#include "frameworks/bridge/declarative_frontend/jsview/js_app_bar_view.h"

#include <cstdint>

#include "ui/base/utils/utils.h"

#include "base/memory/ace_type.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_common_bridge.h"
#include "core/common/ace_engine.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/container_modal/enhance/container_modal_pattern_enhance.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::Framework {
namespace {
const std::string EVENT_NAME_CUSTOM_APP_BAR_MENU_CLICK = "arkui_custom_app_bar_menu_click";
const std::string EVENT_NAME_CUSTOM_APP_BAR_CLOSE_CLICK = "arkui_custom_app_bar_close_click";
const std::string EVENT_NAME_CUSTOM_APP_BAR_DID_BUILD = "arkui_custom_app_bar_did_build";
const std::string EVENT_NAME_CUSTOM_APP_BAR_CREATE_SERVICE_PANEL = "arkui_custom_app_bar_create_service_panel";

constexpr int32_t SERVICE_PANEL_PARAM_COUNT = 2;
constexpr int32_t PARAM_FIRST = 1;

static std::map<std::string, std::function<void(const JSCallbackInfo& info)>> nativeFucMap_;
} // namespace

void JSAppBar::OnMenuClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "JSAppBar OnMenuClick");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->OnMenuClick();
}

void JSAppBar::OnCloseClick(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "JSAppBar OnCloseClick");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->OnCloseClick();
}

void JSAppBar::OnDidBuild(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "JSAppBar OnDidBuild");
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->AddContentToJSContainer();
}

void JSAppBar::OnCreateServicePanel(const JSCallbackInfo& info)
{
    TAG_LOGI(AceLogTag::ACE_APPBAR, "JSAppBar OnCreateServicePanel");

    if (info.Length() < SERVICE_PANEL_PARAM_COUNT) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar OnCreateServicePanel param erro");
        return;
    }
    if (!info[PARAM_FIRST]->IsObject()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar OnCreateServicePanel last param erro");
        return;
    }
    JSRef<JSObject> jsObject = JSRef<JSObject>::Cast(info[PARAM_FIRST]);
    auto bundleName = GetStringValueFromJSObject(jsObject, "bundleName");
    if (bundleName.empty()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar GetStringValueFromJSObject bundleName param is error");
        return;
    }

    auto abilityName = GetStringValueFromJSObject(jsObject, "abilityName");
    if (abilityName.empty()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar GetStringValueFromJSObject abilityName param is error");
        return;
    }

    auto jsParams = jsObject->GetProperty("params");
    if (!jsParams->IsArray()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar GetStringValueFromJSObject jsParams is error");
        return;
    }
    JSRef<JSArray> jsParamsArray = JSRef<JSArray>::Cast(jsParams);
    std::map<std::string, std::string> params;
    GetParamsFromJSArray(jsParamsArray, params);
    if (params.empty()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar GetStringValueFromJSObject paramsMap param is error");
        return;
    }
    auto container = Container::Current();
    CHECK_NULL_VOID(container);
    auto appBar = container->GetAppBar();
    CHECK_NULL_VOID(appBar);
    appBar->CreateServicePanel(bundleName, abilityName, params);
}

std::string JSAppBar::GetStringValueFromJSObject(const JSRef<JSObject>& object, const char* prop)
{
    auto jsValue = object->GetProperty(prop);
    if (!jsValue->IsString()) {
        return "";
    }
    return jsValue->ToString();
}

void JSAppBar::GetParamsFromJSArray(const JSRef<JSArray>& jsArray, std::map<std::string, std::string>& params)
{
    int length = static_cast<int>(jsArray->Length());
    for (int i = 0; i < length; i++) {
        JSRef<JSVal> jsValue = jsArray->GetValueAt(i);
        if (!jsValue->IsString()) {
            continue;
        }
        auto pair = jsValue->ToString();
        size_t colonPos = pair.find(':');
        if (colonPos == std::string::npos) {
            continue;
        }
        std::string key = pair.substr(0, colonPos);
        std::string value = pair.substr(colonPos + 1);
        if (key.empty() || value.empty()) {
            continue;
        }
        params[key] = value;
    }
}

void JSAppBar::CallNative(const JSCallbackInfo& info)
{
    nativeFucMap_ = {
        { EVENT_NAME_CUSTOM_APP_BAR_MENU_CLICK, JSAppBar::OnMenuClick },
        { EVENT_NAME_CUSTOM_APP_BAR_CLOSE_CLICK, JSAppBar::OnCloseClick },
        { EVENT_NAME_CUSTOM_APP_BAR_DID_BUILD, JSAppBar::OnDidBuild },
        { EVENT_NAME_CUSTOM_APP_BAR_CREATE_SERVICE_PANEL, JSAppBar::OnCreateServicePanel },
    };

    if (info.Length() < 1) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar callNative param erro");
        return;
    }
    if (!info[0]->IsString()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar callNative first param erro");
        return;
    }
    std::string eventName = info[0]->ToString();
    TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar callNative eventName = %{public}s", eventName.c_str());
    auto it = nativeFucMap_.find(eventName);
    if (it == nativeFucMap_.end()) {
        TAG_LOGI(AceLogTag::ACE_APPBAR, "appbar Event not found: %{public}s", eventName.c_str());
        return;
    }
    it->second(info);
}

void JSAppBar::JSBind(BindingTarget globalObj)
{
    JSClass<JSAppBar>::Declare("ContainerAppBar");
    JSClass<JSAppBar>::StaticMethod("callNative", &JSAppBar::CallNative);
    JSClass<JSAppBar>::InheritAndBind<JSContainerBase>(globalObj);
}
} // namespace OHOS::Ace::Framework

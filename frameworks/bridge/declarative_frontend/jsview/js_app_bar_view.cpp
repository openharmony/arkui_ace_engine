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

void JSAppBar::CallNative(const JSCallbackInfo& info)
{
    nativeFucMap_ = {
        { EVENT_NAME_CUSTOM_APP_BAR_MENU_CLICK, JSAppBar::OnMenuClick },
        { EVENT_NAME_CUSTOM_APP_BAR_CLOSE_CLICK, JSAppBar::OnCloseClick },
        { EVENT_NAME_CUSTOM_APP_BAR_DID_BUILD, JSAppBar::OnDidBuild },
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

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

#include "frameworks/bridge/declarative_frontend/jsview/js_interactable_view.h"

#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/jsview/js_pan_handler.h"
#include "bridge/declarative_frontend/jsview/js_touch_handler.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/gestures/click_recognizer.h"
#include "core/pipeline/base/single_child.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

namespace OHOS::Ace::Framework {

void JSInteractableView::JsOnTouch(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnTouch");
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnTouch callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnTouch();
        return;
    }
    if (!args[0]->IsFunction()) {
        LOGW("the info is not touch function");
        return;
    }
    RefPtr<JsTouchFunction> jsOnTouchFunc = AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onTouch = [execCtx = args.GetExecutionContext(), func = std::move(jsOnTouchFunc)](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onTouch");
        func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnTouch(std::move(onTouch));
}

void JSInteractableView::JsOnKey(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnKey");
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnKey callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnKeyEvent();
        return;
    }
    if (!args[0]->IsFunction()) {
        LOGE("OnKeyEvent args need a function.");
        return;
    }
    RefPtr<JsKeyFunction> JsOnKeyEvent = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    auto onKeyEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEvent)](KeyEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onKey");
        func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(onKeyEvent));
}

void JSInteractableView::JsOnHover(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnHover");
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnHover callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnHover();
        return;
    }
    if (!info[0]->IsFunction()) {
        LOGE("the param is not a function");
        return;
    }
    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc)](
                       bool isHover, HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHover");
        func->HoverExecute(isHover, hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnHover(std::move(onHover));
}

void JSInteractableView::JsOnPan(const JSCallbackInfo& args)
{
    LOGD("JSInteractableView JsOnPan");
    if (args[0]->IsObject()) {
        // TODO: JSPanHandler should support ng build
#ifndef NG_BUILD
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
        JSPanHandler* handler = obj->Unwrap<JSPanHandler>();
        if (handler) {
            handler->CreateComponent(args);
        }
#endif
    }
}

void JSInteractableView::JsOnDelete(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnDelete");
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDeleteFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onDelete = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDeleteFunc)]() {
            LOGD("onDelete callback");
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDelete");
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnDelete(std::move(onDelete));
    }
}

void JSInteractableView::JsTouchable(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetTouchable(info[0]->ToBoolean());
    }
}

void JSInteractableView::JsOnClick(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnClick");
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnClick callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!info[0]->IsFunction()) {
        LOGW("the info is not click function");
        return;
    }
    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(info);
    };

    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc](const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        func->Execute(*info);
    };

    ViewAbstractModel::GetInstance()->SetOnClick(std::move(onTap), std::move(onClick));
}

void JSInteractableView::SetFocusable(bool focusable)
{
    ViewAbstractModel::GetInstance()->SetFocusable(focusable);
}

void JSInteractableView::SetFocusNode(bool isFocusNode)
{
    ViewAbstractModel::GetInstance()->SetFocusNode(isFocusNode);
}

void JSInteractableView::JsOnAppear(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnAppear");
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnAppear callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnAppear();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGI("About to call JsOnAppear method on js");
            ACE_SCORING_EVENT("onAppear");
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnAppear(std::move(onAppear));
    }
}

void JSInteractableView::JsOnDisAppear(const JSCallbackInfo& info)
{
    LOGD("JSInteractableView JsOnDisAppear");
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        LOGD("JsOnDisAppear callback is undefined");
        ViewAbstractModel::GetInstance()->DisableOnDisAppear();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            LOGD("Start to call JsOnDisAppear method on js");
            ACE_SCORING_EVENT("onDisAppear");
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnDisAppear(std::move(onDisappear));
    }
}

void JSInteractableView::JsOnAccessibility(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        LOGE("info[0] is not a function.");
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    auto onAccessibility = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAccessibility");
        func->Execute({ "eventType" }, param);
    };
    ViewAbstractModel::GetInstance()->SetOnAccessibility(std::move(onAccessibility));
}

void JSInteractableView::JsCommonRemoteMessage(const JSCallbackInfo& info)
{
    if (info.Length() != 0 && info[0]->IsObject()) {
        RemoteCallback remoteCallback;
        JsRemoteMessage(info, remoteCallback);
        ViewAbstractModel::GetInstance()->SetOnRemoteMessage(std::move(remoteCallback));
    }
}

void JSInteractableView::JsRemoteMessage(const JSCallbackInfo& info, RemoteCallback& remoteCallback)
{
    if (info.Length() == 0 || !info[0]->IsObject()) {
        LOGE("RemoteMessage JSCallbackInfo param is empty or type is not Object.");
        return;
    }

    auto eventCallback = GetRemoteMessageEventCallback(info);
    remoteCallback = [func = std::move(eventCallback)](const BaseEventInfo* info) {
        auto touchInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
        if (touchInfo && touchInfo->GetType().compare("onClick") == 0) {
            func();
        }
    };
}

std::function<void()> JSInteractableView::GetRemoteMessageEventCallback(const JSCallbackInfo& info)
{
    auto obj = JSRef<JSObject>::Cast(info[0]);
    auto actionValue = obj->GetProperty("action");
    std::string action;
    if (actionValue->IsString()) {
        action = actionValue->ToString();
    }
    auto abilityValue = obj->GetProperty("ability");
    std::string ability;
    if (abilityValue->IsString()) {
        ability = abilityValue->ToString();
    }
    auto paramsObj = obj->GetProperty("params");
    std::string params;
    if (paramsObj->IsObject()) {
        params = paramsObj->ToString();
    }
    auto eventCallback = [action, ability, params]() {
        LOGE("JSInteractableView::JsRemoteMessage. eventMarker");
        if (action.compare("message") == 0) {
            // onCall
        } else if (action.compare("route") == 0) {
            // startAbility
#ifdef PLUGIN_COMPONENT_SUPPORTED
            std::vector<std::string> strList;
            SplitString(ability, '/', strList);
            if (strList.size() <= 1) {
                LOGE("App bundleName or abilityName is empty.");
                return;
            }
            int32_t result = PluginManager::GetInstance().StartAbility(strList[0], strList[1], params);
            if (result != 0) {
                LOGE("JSInteractableView::JsRemoteMessage: Failed to start the APP %{public}s.", ability.c_str());
            }
#else
            LOGE("JSInteractableView::JsRemoteMessage: Unsupported Windows and Mac platforms to start APP.");
#endif
        } else {
            LOGE("action's name is not message or route.");
        }
    };

    return eventCallback;
}

void JSInteractableView::SplitString(const std::string& str, char tag, std::vector<std::string>& strList)
{
    std::string subStr;
    for (size_t i = 0; i < str.length(); i++) {
        if (tag == str[i]) {
            if (!subStr.empty()) {
                strList.push_back(subStr);
                subStr.clear();
            }
        } else {
            subStr.push_back(str[i]);
        }
    }
    if (!subStr.empty()) {
        strList.push_back(subStr);
    }
}
} // namespace OHOS::Ace::Framework

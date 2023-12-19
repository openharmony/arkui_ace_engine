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
#include "core/components_ng/base/view_stack_processor.h"
#include "core/gestures/click_recognizer.h"
#include "core/pipeline/base/single_child.h"
#include "core/pipeline/pipeline_context.h"

#ifdef PLUGIN_COMPONENT_SUPPORTED
#include "core/common/plugin_manager.h"
#endif

namespace OHOS::Ace::Framework {

void JSInteractableView::JsOnTouch(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnTouch();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsTouchFunction> jsOnTouchFunc = AceType::MakeRefPtr<JsTouchFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onTouch = [execCtx = args.GetExecutionContext(), func = std::move(jsOnTouchFunc), node = frameNode](
                       TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onTouch");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnTouch(std::move(onTouch));
}

void JSInteractableView::JsOnKey(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnKeyEvent();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsKeyFunction> JsOnKeyEvent = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onKeyEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEvent), node = frameNode](
                          KeyEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onKey");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(onKeyEvent));
}

void JSInteractableView::JsOnHover(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnHover();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsHoverFunction> jsOnHoverFunc = AceType::MakeRefPtr<JsHoverFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onHover = [execCtx = info.GetExecutionContext(), func = std::move(jsOnHoverFunc), node = frameNode](
                       bool isHover, HoverInfo& hoverInfo) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onHover");
        PipelineContext::SetCallBackNode(node);
        func->HoverExecute(isHover, hoverInfo);
    };
    ViewAbstractModel::GetInstance()->SetOnHover(std::move(onHover));
}

void JSInteractableView::JsOnPan(const JSCallbackInfo& args)
{
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
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDeleteFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onDelete = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDeleteFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDelete");
            PipelineContext::SetCallBackNode(node);
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

void JSInteractableView::JsMonopolizeEvents(const JSCallbackInfo& info)
{
    if (info[0]->IsBoolean()) {
        ViewAbstractModel::GetInstance()->SetMonopolizeEvents(info[0]->ToBoolean());
    }
}

void JSInteractableView::JsOnClick(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!info[0]->IsFunction()) {
        return;
    }
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = frameNode](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
    };
    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = frameNode](
                       const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
    };

    ViewAbstractModel::GetInstance()->SetOnClick(std::move(onTap), std::move(onClick));
    auto focusHub = NG::ViewStackProcessor::GetInstance()->GetOrCreateMainFrameNodeFocusHub();
    CHECK_NULL_VOID(focusHub);
    focusHub->SetFocusable(true, false);
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
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAppear();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onAppear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAppearFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnAppear(std::move(onAppear));
    }
}

void JSInteractableView::JsOnDisAppear(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnDisAppear();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDisAppearFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
        auto onDisappear = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDisAppearFunc),
                               node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDisAppear");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnDisAppear(std::move(onDisappear));
    }
}

void JSInteractableView::JsOnAccessibility(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    auto onAccessibility = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = frameNode](
                               const std::string& param) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onAccessibility");
        PipelineContext::SetCallBackNode(node);

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
    if (!info[0]->IsObject()) {
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
        if (action.compare("message") == 0) {
            // onCall
        } else if (action.compare("route") == 0) {
            // startAbility
#ifdef PLUGIN_COMPONENT_SUPPORTED
            std::vector<std::string> strList;
            SplitString(ability, '/', strList);
            if (strList.size() <= 1) {
                return;
            }
            int32_t result = PluginManager::GetInstance().StartAbility(strList[0], strList[1], params);
            if (result != 0) {
                LOGW("Failed to start the APP %{public}s.", ability.c_str());
            }
#else
            LOGW("Unsupported Windows and Mac platforms to start APP.");
#endif
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

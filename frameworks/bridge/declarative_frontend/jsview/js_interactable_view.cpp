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
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#endif

#include "base/log/ace_scoring_log.h"
#include "base/log/log_wrapper.h"
#include "base/utils/utf_helper.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_hover_function.h"
#include "bridge/declarative_frontend/engine/functions/js_key_function.h"
#include "bridge/declarative_frontend/engine/js_execution_scope_defines.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_frame_node_bridge.h"
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
    EcmaVM* vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto jsOnTouchFunc = JSRef<JSFunc>::Cast(args[0]);
    if (jsOnTouchFunc->IsEmpty()) {
        return;
    }
    auto jsOnTouchFuncLocalHandle = jsOnTouchFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onTouch = [vm, execCtx = args.GetExecutionContext(),
                       func = panda::CopyableGlobal(vm, jsOnTouchFuncLocalHandle),
                       node = frameNode](TouchEventInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onTouch");
        PipelineContext::SetCallBackNode(node);
        auto eventObj = NG::FrameNodeBridge::CreateTouchEventInfo(vm, info);
        panda::Local<panda::JSValueRef> params[1] = { eventObj };
        func->Call(vm, func.ToLocal(), params, 1);
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onKeyEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEvent), node = frameNode](
                          KeyEventInfo& info) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("onKey");
        PipelineContext::SetCallBackNode(node);
        auto ret = func->ExecuteWithValue(info);
        return ret->IsBoolean() ? ret->ToBoolean() : false;
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEvent(std::move(onKeyEvent));
}

void JSInteractableView::JsOnKeyPreIme(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined()) {
        ViewAbstractModel::GetInstance()->DisableOnKeyPreIme();
        return;
    }
    if (!args[0]->IsFunction()) {
        return;
    }
    RefPtr<JsKeyFunction> JsOnPreImeEvent = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onPreImeEvent = [execCtx = args.GetExecutionContext(), func = std::move(JsOnPreImeEvent), node = frameNode](
                          KeyEventInfo& info) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("onKeyPreIme");
        PipelineContext::SetCallBackNode(node);
        auto ret = func->ExecuteWithValue(info);
        return ret->IsBoolean() ? ret->ToBoolean() : false;
    };
    ViewAbstractModel::GetInstance()->SetOnKeyPreIme(std::move(onPreImeEvent));
}

void JSInteractableView::JsOnKeyEventDispatch(const JSCallbackInfo& args)
{
    if (args[0]->IsUndefined() || !args[0]->IsFunction()) {
        ViewAbstractModel::GetInstance()->DisableOnKeyEventDispatch();
        return;
    }
    RefPtr<JsKeyFunction> JsOnKeyEventDispatch = AceType::MakeRefPtr<JsKeyFunction>(JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onKeyEventDispatch = [execCtx = args.GetExecutionContext(), func = std::move(JsOnKeyEventDispatch),
                             node = frameNode](KeyEventInfo& keyEvent) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, false);
        ACE_SCORING_EVENT("onKeyEventDispatch");
        PipelineContext::SetCallBackNode(node);
        auto ret = func->ExecuteWithValue(keyEvent);
        return ret->IsBoolean() ? ret->ToBoolean() : false;
    };
    ViewAbstractModel::GetInstance()->SetOnKeyEventDispatch(std::move(onKeyEventDispatch));
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
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    } else {
        ViewAbstractModel::GetInstance()->SetMonopolizeEvents(false);
    }
}

void JSInteractableView::JsOnClick(const JSCallbackInfo& info)
{
    JSRef<JSVal> jsOnClickVal = info[0];
    if (jsOnClickVal->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnClick();
        return;
    }
    if (!jsOnClickVal->IsFunction()) {
        return;
    }
    auto frameNode = NG::ViewStackProcessor::GetInstance()->GetMainFrameNode();
    WeakPtr<NG::FrameNode> weak = AceType::WeakClaim(frameNode);
    auto jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(jsOnClickVal));
    auto onTap = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = weak](GestureEvent& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        ReportClickEvent(node);
#endif
    };
    auto onClick = [execCtx = info.GetExecutionContext(), func = jsOnClickFunc, node = weak](
                       const ClickInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*info);
#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
        ReportClickEvent(node);
#endif
    };

    double distanceThreshold = std::numeric_limits<double>::infinity();
    if (info.Length() > 1 && info[1]->IsNumber()) {
        distanceThreshold = info[1]->ToNumber<double>();
        distanceThreshold = Dimension(distanceThreshold, DimensionUnit::VP).ConvertToPx();
    }

    ViewAbstractModel::GetInstance()->SetOnClick(std::move(onTap), std::move(onClick), distanceThreshold);
    CHECK_NULL_VOID(frameNode);
    auto focusHub = frameNode->GetOrCreateFocusHub();
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
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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

void JSInteractableView::JsOnAttach(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnAttach();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnAttachFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onAttach = [execCtx = info.GetExecutionContext(), func = std::move(jsOnAttachFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onAttach");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnAttach(std::move(onAttach));
    }
}

void JSInteractableView::JsOnDetach(const JSCallbackInfo& info)
{
    if (info[0]->IsUndefined() && IsDisableEventVersion()) {
        ViewAbstractModel::GetInstance()->DisableOnDetach();
        return;
    }
    if (info[0]->IsFunction()) {
        RefPtr<JsFunction> jsOnDetachFunc =
            AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onDetach = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDetachFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("onDetach");
            PipelineContext::SetCallBackNode(node);
            func->Execute();
        };
        ViewAbstractModel::GetInstance()->SetOnDetach(std::move(onDetach));
    }
}

void JSInteractableView::JsOnAccessibility(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
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
    JSRef<JSVal> arg = info[0];
    if (!arg->IsObject()) {
        return []() {};
    }
    auto obj = JSRef<JSObject>::Cast(arg);
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

#if !defined(PREVIEW) && defined(OHOS_PLATFORM)
void JSInteractableView::ReportClickEvent(const WeakPtr<NG::FrameNode>& node, const std::u16string text)
{
    if (UiSessionManager::GetInstance().GetClickEventRegistered()) {
        auto data = JsonUtil::Create();
        data->Put("event", "onClick");
        std::u16string content = text;
        if (!node.Invalid()) {
            data->Put("id", node.GetRawPtr()->GetId());
            auto children = node.GetRawPtr()->GetChildren();
            if (!children.empty()) {
                node.GetRawPtr()->GetContainerComponentText(content);
            }
            data->Put("text", UtfUtils::Str16ToStr8(content).data());
            data->Put("position", node.GetRawPtr()->GetGeometryNode()->GetFrameRect().ToString().data());
        }
        UiSessionManager::GetInstance().ReportClickEvent(data->ToString());
    }
}
#endif

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

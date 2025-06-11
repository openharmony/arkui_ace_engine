/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_bridge.h"

#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_navigation_utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_navigation_stack.h"
#include "bridge/declarative_frontend/jsview/js_navigation_utils.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/navigation/navigation_declaration.h"
#include "core/components_ng/pattern/navigation/navigation_model_data.h"
#include "core/components_ng/pattern/navigation/navigation_model_ng.h"
#include "frameworks/bridge/declarative_frontend/engine/functions/js_navigation_function.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"
namespace OHOS::Ace::NG {} // namespace OHOS::Ace::NG
namespace OHOS::Ace::NG {
constexpr int NUM_0 = 0;
constexpr int NUM_1 = 1;
constexpr int NUM_2 = 2;
constexpr int32_t MIN_INFO_LENGTH = 2;
constexpr int32_t NAVIGATION_ANIMATION_TIMEOUT = 1000; // ms
constexpr char MORE_BUTTON_OPTIONS_PROPERTY[] = "moreButtonOptions";

ArkUINativeModuleValue NavigationBridge::SetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    const int32_t argsNum = 2; // 2: parameter index
    Local<JSValueRef> animatedArg = runtimeCallInfo->GetCallArgRef(argsNum);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool hide = false;
    bool animated = false;
    if (!hideArg->IsNull() && !hideArg->IsUndefined() && hideArg->IsBoolean()) {
        hide = hideArg->ToBoolean(vm)->Value();
    }
    if (!animatedArg->IsNull() && !animatedArg->IsUndefined() && animatedArg->IsBoolean()) {
        animated = animatedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getNavigationModifier()->setHideToolBar(nativeNode, hide, animated);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideToolBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetOnTitleModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getNavigationModifier()->resetOnTitleModeChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(NG::NavigationTitleMode)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                                NG::NavigationTitleMode titleMode) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::IntegerRef::New(vm, static_cast<int32_t>(titleMode)) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    std::function<void(const BaseEventInfo*)> eventInfoFunc = [vm, func = callback, frameNode](
                                                                  const BaseEventInfo* baseInfo) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        auto eventInfo = TypeInfoHelper::DynamicCast<NavigationTitleModeChangeEvent>(baseInfo);
        if (!eventInfo) {
            return;
        }
        auto titleMode = eventInfo->IsMiniBar() ? static_cast<int32_t>(NavigationTitleMode::MINI)
                                                : static_cast<int32_t>(NavigationTitleMode::FULL);
        func(static_cast<NG::NavigationTitleMode>(titleMode));
    };
    nodeModifiers->getNavigationModifier()->setOnTitleModeChange(
        nativeNode, reinterpret_cast<void*>(&callback), reinterpret_cast<void*>(&eventInfoFunc));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetOnTitleModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getNavigationModifier()->resetOnTitleModeChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetOnNavigationModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getNavigationModifier()->resetOnNavigationModeChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(NG::NavigationMode)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](
                                                           NG::NavigationMode modechange) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::IntegerRef::New(vm, static_cast<int32_t>(modechange)) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    nodeModifiers->getNavigationModifier()->setOnNavigationModeChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetOnNavigationModeChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getNavigationModifier()->resetOnNavigationModeChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetCustomNavContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    using namespace OHOS::Ace::Framework;
    JsiCallbackInfo info = JsiCallbackInfo(runtimeCallInfo);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (info.Length() != 2) { // 2: Array length
        return panda::JSValueRef::Undefined(vm);
    }
    if (!info[1]->IsObject()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto transitionObj = JSRef<JSObject>::Cast(info[1]);
    if (transitionObj->IsUndefined() || !info[1]->IsFunction()) {
        return panda::JSValueRef::Undefined(vm);
    }
    ParseCustomContentTransition(transitionObj, info);
    nodeModifiers->getNavigationModifier()->setNavigationIsCustomAnimation(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetCustomNavContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    return panda::JSValueRef::Undefined(vm);
}

void NavigationBridge::ParseCustomContentTransition(
    const Framework::JSRef<Framework::JSObject>& transitionObj, const Framework::JsiCallbackInfo& info)
{
    using namespace OHOS::Ace::Framework;
    auto jsFunc = AceType::MakeRefPtr<JsNavigationFunction>(JSRef<JSFunc>::Cast(transitionObj));
    auto executor = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc)](
                        RefPtr<NG::NavDestinationContext> from, RefPtr<NG::NavDestinationContext> to,
                        NG::NavigationOperation operation) -> NG::NavigationTransition {
        NG::NavigationTransition transition;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, transition);
        auto ret = func->Execute(from, to, operation);
        if (!ret->IsObject()) {
            return transition.isValid = false, transition;
        }
        auto transObj = JSRef<JSObject>::Cast(ret);
        if (auto interactive = transObj->GetProperty("isInteractive"); interactive->IsBoolean()) {
            transition.interactive = interactive->ToBoolean();
        }
        if (auto timeout = transObj->GetProperty("timeout"); timeout->IsNumber()) {
            transition.timeout = timeout->ToNumber<int32_t>();
            transition.timeout = transition.interactive ? transition.timeout :
                (transition.timeout < 0 ? NAVIGATION_ANIMATION_TIMEOUT : transition.timeout);
        }
        if (auto transitionCtx = transObj->GetProperty("transition"); transitionCtx->IsFunction()) {
            transition.transition = [execCtx, func = AceType::MakeRefPtr<JsNavigationFunction>(
                JSRef<JSFunc>::Cast(transitionCtx))](const RefPtr<NG::NavigationTransitionProxy>& proxy) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("transition");
                func->Execute(proxy);
            };
        }
        if (auto endCb = transObj->GetProperty("onTransitionEnd"); endCb->IsFunction()) {
            transition.endCallback = [execCtx, func = AceType::MakeRefPtr<JsFunction>(
                JSRef<JSObject>(), JSRef<JSFunc>::Cast(endCb))](bool success) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onTransitionEnded");
                JSRef<JSVal> args[] = { JSRef<JSVal>::Make(ToJSValue(success)) };
                func->ExecuteJS(1, args);
            };
        }
        return transition;
    };
    NavigationModel::GetInstance()->SetCustomTransition(executor);
}

ArkUINativeModuleValue NavigationBridge::SetToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIBarItem> toolbarItems;
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (valueArg->IsArray(vm) || valueArg->IsObject(vm)) {
        NativeNavigationUtils::ParseBarItems(vm, valueArg, toolbarItems);
        nodeModifiers->getNavigationModifier()->setToolBar(
            nativeNode, toolbarItems.data(), toolbarItems.size());
    } else if (valueArg->IsUndefined()) {
        toolbarItems = {};
        nodeModifiers->getNavigationModifier()->setToolBar(
            nativeNode, toolbarItems.data(), toolbarItems.size());
    } else {
        nodeModifiers->getNavigationModifier()->resetToolBar(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetToolBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getNavigationModifier()->resetToolBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void ParseToolBarItems(const JsiCallbackInfo& info, std::list<RefPtr<AceType>>& items)
{
    using namespace OHOS::Ace::Framework;
    if (info[1]->IsUndefined() || !info[1]->IsArray()) {
        return;
    }
    JSRef<JSArray> jsArray = JSRef<JSArray>::Cast(info[1]);
    auto length = jsArray->Length();
    for (size_t i = 0; i < length; i++) {
        auto item = jsArray->GetValueAt(i);
        if (!item->IsObject()) {
            continue;
        }
        auto itemObject = JSRef<JSObject>::Cast(item);
        auto toolBarItem = AceType::MakeRefPtr<ToolBarItem>();
        auto itemValueObject = itemObject->GetProperty("value");
        if (itemValueObject->IsString()) {
            toolBarItem->value = itemValueObject->ToString();
        }
        auto itemIconObject = itemObject->GetProperty("icon");
        std::string icon;
        Framework::JSViewAbstract::ParseJsMedia(itemIconObject, icon);
        toolBarItem->icon = icon;
        auto itemActionValue = itemObject->GetProperty("action");
        if (itemActionValue->IsFunction()) {
            auto onClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            toolBarItem->action =
                EventMarker([func = std::move(onClickFunc), node = targetNode, execCtx = info.GetExecutionContext()]() {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("Navigation.toolBarItemClick");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute();
                });
            auto onClickWithParamFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(itemActionValue));
            toolBarItem->actionWithParam =
                EventMarker([func = std::move(onClickWithParamFunc), node = targetNode,
                                execCtx = info.GetExecutionContext()](const BaseEventInfo* info) {
                    JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                    ACE_SCORING_EVENT("Navigation.menuItemButtonClick");
                    PipelineContext::SetCallBackNode(node);
                    func->Execute();
                });
        }
        items.push_back(toolBarItem);
    }
}

ArkUINativeModuleValue NavigationBridge::SetToolBarConfiguration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(firstArg->ToNativePointer(vm)->Value());
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    using namespace OHOS::Ace::Framework;
    JsiCallbackInfo info = JsiCallbackInfo(runtimeCallInfo);
    bool hideText = false;
    JSNavigationUtils::ParseHideToolBarText(info, hideText);
    NavigationModel::GetInstance()->SetHideItemText(hideText);
    if (info[1]->IsUndefined() || info[1]->IsArray()) {
        if (NavigationModel::GetInstance()->NeedSetItems()) {
            std::vector<NG::BarItem> toolbarItems = {};
            if (!info[1]->IsUndefined()) {
                auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
                JSNavigationUtils::ParseToolbarItemsConfiguration(
                    targetNode, info, JSRef<JSArray>::Cast(info[1]), toolbarItems);
            }
            NG::MoreButtonOptions toolbarMoreButtonOptions;
            if (info.Length() > MIN_INFO_LENGTH && info[NUM_2]->IsObject()) {
                auto optObj = JSRef<JSObject>::Cast(info[NUM_2]);
                auto moreButtonProperty = optObj->GetProperty(MORE_BUTTON_OPTIONS_PROPERTY);
                JSNavigationUtils::ParseToolBarMoreButtonOptions(moreButtonProperty, toolbarMoreButtonOptions);
            }
            if (SystemProperties::ConfigChangePerform()) {
                NavigationModel::GetInstance()->SetToolbarConfiguration(
                    std::move(toolbarItems), std::move(toolbarMoreButtonOptions));
            } else {
                NavigationModel::GetInstance()->SetToolbarMorebuttonOptions(std::move(toolbarMoreButtonOptions));
                NavigationModel::GetInstance()->SetToolbarConfiguration(std::move(toolbarItems));
            }
        } else {
            std::list<RefPtr<AceType>> items;
            NavigationModel::GetInstance()->GetToolBarItems(items);
            ParseToolBarItems(info, items);
        }
    } else if (info[1]->IsObject()) {
        auto builderFuncParam = JSRef<JSObject>::Cast(info[1])->GetProperty("builder");
        if (builderFuncParam->IsFunction()) {
            ViewStackModel::GetInstance()->NewScope();
            JsFunction jsBuilderFunc(builderFuncParam);
            jsBuilderFunc.Execute();
            auto customNode = ViewStackModel::GetInstance()->Finish();
            NavigationModel::GetInstance()->SetCustomToolBar(customNode);
        }
    }
    NG::NavigationToolbarOptions options;
    JSNavigationUtils::ParseToolbarOptions(info, options);
    NavigationModel::GetInstance()->SetToolbarOptions(std::move(options));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetToolBarConfiguration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetOnNavBarStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        nodeModifiers->getNavigationModifier()->resetOnNavBarStateChange(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(bool)> callback = [vm, frameNode, func = panda::CopyableGlobal(vm, func)](bool isNavBarStatus) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(AceType::WeakClaim(frameNode));
        panda::Local<panda::JSValueRef> params[1] = { panda::BooleanRef::New(vm, isNavBarStatus) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    nodeModifiers->getNavigationModifier()->setOnNavBarStateChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetOnNavBarStateChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::NativePointerRef::New(vm, nullptr));
    nodeModifiers->getNavigationModifier()->resetOnNavBarStateChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    int32_t value;
    if (valueArg->IsNull() || valueArg->IsUndefined() || !ArkTSUtils::ParseJsInteger(vm, valueArg, value)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetTitleMode(nativeNode);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->setTitleMode(nativeNode, value);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetTitleMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetTitleMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setHideBackButton(nativeNode, hide);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetHideBackButton(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideBackButton(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideBackButton(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> subtitleArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (subtitleArg->IsString(vm)) {
        std::string subtitle = subtitleArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getNavigationModifier()->setSubtitle(nativeNode, subtitle.c_str());
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetSubtitle(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetSubtitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetSubtitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (hideArg->IsBoolean()) {
        bool hide = hideArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setHideNavBar(nativeNode, hide);
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetHideNavBar(nativeNode);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideNavBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetHideNavBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetUsrNavigationMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t value = valueArg->Uint32Value(vm);
    GetArkUINodeModifiers()->getNavigationModifier()->setUsrNavigationMode(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetUsrNavigationMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetUsrNavigationMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> hideArg = runtimeCallInfo->GetCallArgRef(1);
    const int32_t argsNum = 2; // 2: parameter index
    Local<JSValueRef> animatedArg = runtimeCallInfo->GetCallArgRef(argsNum);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    bool hide = false;
    bool animated = false;
    if (!hideArg->IsNull() && !hideArg->IsUndefined() && hideArg->IsBoolean()) {
        hide = hideArg->ToBoolean(vm)->Value();
    }
    if (!animatedArg->IsNull() && !animatedArg->IsUndefined() && animatedArg->IsBoolean()) {
        animated = animatedArg->ToBoolean(vm)->Value();
    }
    GetArkUINodeModifiers()->getNavigationModifier()->setNavHideTitleBar(nativeNode, hide, animated);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetHideTitleBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavHideTitleBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetEnableModeChangeAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (enableArg->IsBoolean()) {
        bool isEnable = enableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setEnableModeChangeAnimation(nativeNode, isEnable);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getNavigationModifier()->setEnableModeChangeAnimation(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetEnableModeChangeAnimation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetEnableModeChangeAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetSplitPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    if (info[1]->IsObject()) {
        JSRef<JSObject> contentObject = JSRef<JSObject>::Cast(info[1]);
        JSRef<JSVal> builderNodeParam = contentObject->GetProperty("builderNode_");
        if (builderNodeParam->IsObject()) {
            JSRef<JSObject> builderNodeObject = JSRef<JSObject>::Cast(builderNodeParam);
            JSRef<JSVal> nodeptr = builderNodeObject->GetProperty("nodePtr_");
            if (!nodeptr.IsEmpty()) {
                auto node = nodePtr(nodeptr->GetLocalHandle()->ToNativePointer(vm)->Value());
                GetArkUINodeModifiers()->getNavigationModifier()->setSplitPlaceholder(nativeNode, node);
                return panda::JSValueRef::Undefined(vm);
            }
        }
    }
    GetArkUINodeModifiers()->getNavigationModifier()->resetSplitPlaceholder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetSplitPlaceholder(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetSplitPlaceholder(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (valueArg->IsUndefined() || !valueArg->IsNumber()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarPosition(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t value = valueArg->Int32Value(vm);
    GetArkUINodeModifiers()->getNavigationModifier()->setNavBarPosition(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    RefPtr<ResourceObject> navBarWidthResObj;
    if (jsValue->IsNull() || jsValue->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width, navBarWidthResObj)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarWidth(nativeNode);
    } else {
        auto widthRawPtr = AceType::RawPtr(navBarWidthResObj);
        GetArkUINodeModifiers()->getNavigationModifier()->setNavBarWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()), widthRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);
    if (jsValue->IsNull() || jsValue->IsUndefined() || !jsValue->IsArray(vm)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
        GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    auto rangeArray = panda::Local<panda::ArrayRef>(jsValue);
    auto minNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 0);
    CalcDimension minWidth;
    RefPtr<ResourceObject> minNavBarWidthResObj;
    if (minNavBarWidth->IsNull() || minNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, minNavBarWidth, minWidth, minNavBarWidthResObj)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
    } else {
        auto minNavBarWidthRawPtr = AceType::RawPtr(minNavBarWidthResObj);
        GetArkUINodeModifiers()->getNavigationModifier()->setMinNavBarWidth(
            nativeNode, minWidth.Value(), static_cast<int>(minWidth.Unit()), minNavBarWidthRawPtr);
    }
    auto maxNavBarWidth = panda::ArrayRef::GetValueAt(vm, rangeArray, 1);
    CalcDimension maxWidth;
    RefPtr<ResourceObject> maxNavBarWidthResObj;
    if (maxNavBarWidth->IsNull() || maxNavBarWidth->IsUndefined() ||
        !ArkTSUtils::ParseJsDimensionVp(vm, maxNavBarWidth, maxWidth, maxNavBarWidthResObj)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
    } else {
        auto maxNavBarWidthRawPtr = AceType::RawPtr(maxNavBarWidthResObj);
        GetArkUINodeModifiers()->getNavigationModifier()->setMaxNavBarWidth(
            nativeNode, maxWidth.Value(), static_cast<int>(maxWidth.Unit()), maxNavBarWidthRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetNavBarWidthRange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetMinNavBarWidth(nativeNode);
    GetArkUINodeModifiers()->getNavigationModifier()->resetMaxNavBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(1);

    CalcDimension width;
    RefPtr<ResourceObject> minContentWidthResObj;
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width,
        minContentWidthResObj)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetMinContentWidth(nativeNode);
    } else {
        auto widthRawPtr = AceType::RawPtr(minContentWidthResObj);
        GetArkUINodeModifiers()->getNavigationModifier()->setMinContentWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()), widthRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetMinContentWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetMinContentWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);

    Framework::JsiCallbackInfo info = Framework::JsiCallbackInfo(runtimeCallInfo);
    std::string src;
    RefPtr<ResourceObject> backButtonIconResObj;
    auto noPixMap = Framework::JSViewAbstract::ParseJsMedia(info[1], src, backButtonIconResObj);
    auto isValidImage = false;
    RefPtr<PixelMap> pixMap = nullptr;
#if defined(PIXEL_MAP_SUPPORTED)
    if (!noPixMap) {
        pixMap = CreatePixelMapFromNapiValue(info[1]);
    }
#endif
    if (noPixMap || pixMap != nullptr) {
        isValidImage = true;
    }
    std::string bundleName;
    std::string moduleName;
    Framework::JSViewAbstract::GetJsMediaBundleInfo(info[1], bundleName, moduleName);
    NG::ImageOption imageOption;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    auto isSymbol = info[1]->IsObject() && src.empty() && pixMap == nullptr;
    if (isSymbol) {
        Framework::JSViewAbstract::SetSymbolOptionApply(info, iconSymbol, info[1]);
    }
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = isValidImage;
    if (!SystemProperties::ConfigChangePerform()) {
        NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap);
    } else {
        NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, imageOption, pixMap, backButtonIconResObj);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetBackButtonIcon(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    bool noPixMap = false;
    NG::ImageOption imageOption;
    imageOption.noPixMap = noPixMap;
    imageOption.isValidImage = false;
    RefPtr<PixelMap> pixMap = nullptr;
    std::function<void(WeakPtr<NG::FrameNode>)> iconSymbol = nullptr;
    std::string src;
    NavigationModelNG::SetBackButtonIcon(frameNode, iconSymbol, src, imageOption, pixMap);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo *runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(NUM_2);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    std::string typeCppStr;
    std::string edgesCppStr;
    if (secondArg->IsString(vm)) {
        typeCppStr = secondArg->ToString(vm)->ToString(vm);
    } else {
        //type system
        typeCppStr = "0";
    }

    if (thirdArg->IsString(vm)) {
        edgesCppStr = thirdArg->ToString(vm)->ToString(vm);
    } else {
        //edge top and bottom
        edgesCppStr = "0|1";
    }
    const char* typeStr = typeCppStr.c_str();
    const char* edgesStr = edgesCppStr.c_str();
    GetArkUINodeModifiers()->getNavigationModifier()->setNavIgnoreLayoutSafeArea(nativeNode, typeStr, edgesStr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetIgnoreLayoutSafeArea(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavIgnoreLayoutSafeArea(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> titleArg = runtimeCallInfo->GetCallArgRef(1);
    Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(2);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::string title;
    std::string subtitle;
    bool hasMain = false;
    bool hasSub = false;
    RefPtr<ResourceObject> titleResObj;
    RefPtr<ResourceObject> subtitleResObj;
    if (ArkTSUtils::ParseJsString(vm, titleArg, title, titleResObj)) {
        // Resource and string type.
        subtitle = "";
        hasMain = true;
        hasSub = false;
    } else if (titleArg->IsObject(vm)) {
        // NavigationCommonTitle
        auto obj = titleArg->ToObject(vm);
        auto main = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "main"));
        auto sub = obj->Get(vm, panda::StringRef::NewFromUtf8(vm, "sub"));
        hasMain = ArkTSUtils::ParseJsString(vm, main, title, titleResObj);
        hasSub = ArkTSUtils::ParseJsString(vm, sub, subtitle, subtitleResObj);
        // NavigationCustomTitle or CustomBuilder is not supported
    } else {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavTitle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    ArkUINavigationTitlebarOptions options;
    if (optionsArg->IsObject(vm)) {
        NativeNavigationUtils::ParseTitleOptions(vm, optionsArg, options);
    }
    ArkUINavigationTitleInfo titleInfo = { hasSub, hasMain, subtitle.c_str(), title.c_str() };
    auto titleRawPtr = AceType::RawPtr(titleResObj);
    auto subtitleRawPtr = AceType::RawPtr(subtitleResObj);
    GetArkUINodeModifiers()->getNavigationModifier()->setNavTitle(nativeNode, titleInfo, options,
        titleRawPtr, subtitleRawPtr);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetTitle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavTitle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> menusArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    std::vector<ArkUIBarItem> menuItems;
    if (menusArg->IsArray(vm)) {
        NativeNavigationUtils::ParseBarItems(vm, menusArg, menuItems);
        GetArkUINodeModifiers()->getNavigationModifier()->setNavMenus(nativeNode, menuItems.data(), menuItems.size());
        // get action and symbolModifier single
        auto actionSendFunc = GetArkUINodeModifiers()->getNavigationModifier()->setNavMenuItemAction;
        auto symbolSendFunc = GetArkUINodeModifiers()->getNavigationModifier()->setNavMenuItemSymbol;
        NativeNavigationUtils::ParseAndSendFunctionParam(runtimeCallInfo, menusArg, actionSendFunc, symbolSendFunc);
    } else if (menusArg->IsUndefined()) {
        menuItems = {};
        GetArkUINodeModifiers()->getNavigationModifier()->setNavMenus(nativeNode, menuItems.data(), menuItems.size());
    } else if (menusArg->IsObject(vm)) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetNavMenus(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetMenus(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetNavMenus(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> recoverableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (recoverableArg->IsNull() || recoverableArg->IsUndefined() || !recoverableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetRecoverable(nativeNode);
    } else {
        bool recoverable = recoverableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setRecoverable(nativeNode, recoverable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetRecoverable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetRecoverable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetEnableDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> enableDragBarArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (enableDragBarArg->IsNull() || enableDragBarArg->IsUndefined() || !enableDragBarArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetEnableDragBar(nativeNode);
    } else {
        bool enableDragBar = enableDragBarArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setEnableDragBar(nativeNode, enableDragBar);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetEnableDragBar(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetEnableDragBar(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetEnableToolBarAdaptation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> enableArg = runtimeCallInfo->GetCallArgRef(1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    if (enableArg->IsNull() || enableArg->IsUndefined() || !enableArg->IsBoolean()) {
        GetArkUINodeModifiers()->getNavigationModifier()->resetEnableToolBarAdaptation(nativeNode);
    } else {
        bool enable = enableArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getNavigationModifier()->setEnableToolBarAdaptation(nativeNode, enable);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetEnableToolBarAdaptation(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getNavigationModifier()->resetEnableToolBarAdaptation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::SetSystemBarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    Local<JSValueRef> styleArg = runtimeCallInfo->GetCallArgRef(NUM_1);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    if (styleArg->IsNull() || styleArg->IsUndefined()) {
        nodeModifiers->getNavigationModifier()->resetSystemBarStyle(nativeNode);
    } else {
        std::string value;
        ArkTSUtils::ParseJsString(vm, styleArg, value);
        auto color = Color::FromString(value);
        nodeModifiers->getNavigationModifier()->setSystemBarStyle(nativeNode, color.GetValue());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue NavigationBridge::ResetSystemBarStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(NUM_0);
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    auto nodeModifiers = GetArkUINodeModifiers();
    CHECK_NULL_RETURN(nodeModifiers, panda::JSValueRef::Undefined(vm));
    nodeModifiers->getNavigationModifier()->resetSystemBarStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG

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

#include "core/components_ng/pattern/tabs/bridge/arkts_native_tabs_bridge.h"

#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_utils_bridge.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_utils.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/base/view_abstract_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper/bridge/arkts_native_swiper_bridge.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"
#include "frameworks/bridge/common/utils/utils.h"
#include "frameworks/core/components_ng/pattern/tabs/tabs_controller.h"
#include "frameworks/core/components/tab_bar/tabs_event.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#ifndef NG_BUILD
#include "compatible/components/tab_bar/modifier/tab_modifier_api.h"
#include "core/common/dynamic_module_helper.h"
#endif

namespace OHOS::Ace::NG {
constexpr int SIZE_OF_FIVE = 5;
constexpr int SIZE_OF_THREE = 3;
constexpr int SIZE_OF_VALUES = 2;
constexpr int TABS_ARG_INDEX_0 = 0;
constexpr int TABS_ARG_INDEX_1 = 1;
constexpr int TABS_ARG_INDEX_2 = 2;
constexpr int TABS_ARG_INDEX_3 = 3;
constexpr int TABS_ARG_INDEX_4 = 4;
constexpr int TABS_ARG_INDEX_5 = 5;
constexpr int TABS_ARG_INDEX_6 = 6;
constexpr int TABS_ARG_INDEX_7 = 7;
constexpr int TABS_ARG_INDEX_8 = 8;
constexpr int TABS_ARG_INDEX_9 = 9;
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
constexpr int32_t DEFAULT_COLUMN = -1;
constexpr int REMAINDER = 2;
constexpr int TABBARMODE_SCROLLABLE = 1;
constexpr int32_t DEFAULT_CUSTOM_ANIMATION_TIMEOUT = 1000;
constexpr int ANIMATION_CURVE_TYPE_DEFAULT = 0;
constexpr int ANIMATION_CURVE_TYPE_STR = 1;
constexpr int ANIMATION_CURVE_TYPE_FUNC = 2;
constexpr int PARAM_COUNT_FOUR = 4;
constexpr int32_t DEFAULT_TABS_CACHE_MODE = static_cast<int32_t>(TabsCacheMode::CACHE_BOTH_SIDE);
constexpr int32_t MAX_TABS_CACHE_MODE = static_cast<int32_t>(TabsCacheMode::CACHE_LATEST_SWITCHED);
constexpr int32_t DEFAULT_TAB_BAR_POSITION = static_cast<int32_t>(BarPosition::START);
constexpr int32_t MAX_TAB_BAR_POSITION = static_cast<int32_t>(BarPosition::END);
namespace {
constexpr int NUM_2 = 2;
#ifndef NG_BUILD
const ArkUIInnerTabsModifier* GetTabsInnerModifier()
{
    static const ArkUIInnerTabsModifier* cachedModifier = nullptr;
    if (cachedModifier == nullptr) {
        auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("tabs");
        CHECK_NULL_RETURN(loader, nullptr);
        cachedModifier = reinterpret_cast<const ArkUIInnerTabsModifier*>(loader->GetCustomModifier());
    }
    return cachedModifier;
}

void TrySetInitialIndex(const RefPtr<AceType>& tabController, int32_t index)
{
    CHECK_NULL_VOID(tabController);
    CHECK_EQUAL_VOID(Container::IsCurrentUseNewPipeline(), true);
    auto modifier = GetTabsInnerModifier();
    CHECK_NULL_VOID(modifier);
    modifier->setInitialIndex(tabController, index);
}
#endif

struct TabsResourceObjParam {
    TabJsResType jsResourceType;
    ResourceObject* resourceObj = nullptr;
};

constexpr char DOM_ANIMATION_TIMING_FUNCTION_CUSTOM[] = "customCallback";

const UiMaterial* CreateUiMaterialFromNativeValue(EcmaVM* vm, const Local<JSValueRef>& value)
{
    CHECK_NULL_RETURN(vm, nullptr);
    CHECK_NULL_RETURN(!value->IsNull() && !value->IsUndefined() && value->IsNativePointer(vm), nullptr);
    return static_cast<UiMaterial*>(value->ToNativePointer(vm)->Value());
}

void PopTabsBridge()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSTabs][pop]", &PopTabsBridge);
    }
    GetArkUINodeModifiers()->getTabsModifier()->popTabs();
}

ArkUINativeModuleValue FinishTabContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    auto thisObj = runtimeCallInfo->GetThisRef();
    CHECK_NULL_RETURN(thisObj->IsObject(vm), panda::JSValueRef::Undefined(vm));
    auto object = thisObj->ToObject(vm);
    CHECK_NULL_RETURN(object->GetNativePointerFieldCount(vm) > 0, panda::JSValueRef::Undefined(vm));
    auto* strongRef = static_cast<NG::NativeStrongRef*>(object->GetNativePointerField(vm, 0));
    CHECK_NULL_RETURN(strongRef, panda::JSValueRef::Undefined(vm));
    auto* proxy = static_cast<TabContentTransitionProxy*>(strongRef->RawPtr());
    CHECK_NULL_RETURN(proxy, panda::JSValueRef::Undefined(vm));
    proxy->FinishTransition();
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::ObjectRef> CreateTabContentTransitionProxyObject(
    EcmaVM* vm, const RefPtr<TabContentTransitionProxy>& proxy)
{
    auto proxyObj = panda::ObjectRef::New(vm);
    CHECK_NULL_RETURN(proxy, proxyObj);
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "from"), panda::NumberRef::New(vm, proxy->GetFromIndex()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "to"), panda::NumberRef::New(vm, proxy->GetToIndex()));
    proxyObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "finishTransition"),
        panda::FunctionRef::New(vm, FinishTabContentTransition));
    proxyObj->SetNativePointerFieldCount(vm, 1);
    auto* strongRef = new NG::NativeStrongRef(proxy);
    proxyObj->SetNativePointerField(vm, 0, strongRef, &NG::DestructorInterceptor<NG::NativeStrongRef>);
    return proxyObj;
}

void ParseTabsCreateIndexObject(EcmaVM* vm, const Local<JSValueRef>& changeEventVal)
{
    CHECK_NULL_VOID(vm);
    CHECK_NULL_VOID(!changeEventVal->IsNull() && !changeEventVal->IsUndefined() && changeEventVal->IsFunction(vm));
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    panda::Local<panda::FunctionRef> funcRef = changeEventVal->ToObject(vm);
    WeakPtr<FrameNode> targetNode = AceType::WeakClaim(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    std::function<void(const BaseEventInfo*)> onChangeEvent =
        [func = panda::CopyableGlobal(vm, funcRef), node = targetNode](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "ParseTabsIndexObject execute onChange event failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        panda::Local<panda::JSValueRef> args[1];
        args[0] = panda::NumberRef::New(vm, tabsInfo->GetIndex());
        auto result = func->Call(vm, func.ToLocal(), args, 1);
        ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnChange(nativeNode, reinterpret_cast<void*>(&onChangeEvent));
}

void SetCreateBarModifier(EcmaVM* vm, const Local<JSValueRef>& jsValue)
{
    if (jsValue->IsNull() || jsValue->IsUndefined() || !jsValue->IsObject(vm)) {
        return;
    }
    auto obj = jsValue->ToObject(vm);
    auto val = ArkTSUtils::GetProperty(vm, obj, "barModifier");
    if (val->IsNull() || val->IsUndefined() || !val->IsObject(vm)) {
        return;
    }
    auto nativeNode = reinterpret_cast<ArkUINodeHandle>(ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto globalObj = panda::JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applyCommonModifierToNode"));
    std::function<void(WeakPtr<FrameNode>)> onApply;
    if (globalFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> funcRef = globalFunc->ToObject(vm);
        onApply = [func = panda::CopyableGlobal(vm, funcRef), modifierParam = panda::CopyableGlobal(vm, val)](
                      WeakPtr<FrameNode> frameNode) {
            auto node = frameNode.Upgrade();
            CHECK_NULL_VOID(node);
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            panda::Local<panda::JSValueRef> args[NUM_2];
            args[0] = modifierParam.ToLocal();
            args[1] = panda::NativePointerRef::New(vm, AceType::RawPtr(node));
            PipelineContext::SetCallBackNode(node);
            auto result = func->Call(vm, func.ToLocal(), args, 2);
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        };
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsBarModifier(
        nativeNode, reinterpret_cast<void*>(&onApply));
}

void GetAnimationCurveInfo(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Uint32& type, std::string& aniTimFunc,
    std::function<float(float)>& customCallBack)
{
    type = ANIMATION_CURVE_TYPE_DEFAULT;
    aniTimFunc.clear();
    customCallBack = nullptr;
    CHECK_NULL_VOID(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_VOID(vm);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (!valueArg->IsObject(vm)) {
        return;
    }
    auto object = valueArg->ToObject(vm);
    auto onCallBack = ArkTSUtils::GetProperty(vm, object, "__curveCustomFunc");
    if (!onCallBack->IsNull() && !onCallBack->IsUndefined() && onCallBack->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> funcRef = onCallBack->ToObject(vm);
        customCallBack = [func = panda::CopyableGlobal(vm, funcRef), id = Container::CurrentId(), isJsView](
                              float time) -> float {
            ContainerScope scope(id);
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            panda::Local<panda::JSValueRef> args[1];
            args[0] = panda::NumberRef::New(vm, time);
            auto result = func->Call(vm, func.ToLocal(), args, 1);
            auto resultValue = result->IsNumber() ? result->ToNumber(vm)->Value() : 1.0f;
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
            return resultValue;
        };
    }
    auto jsCurveString = ArkTSUtils::GetProperty(vm, object, "__curveString");
    if (!jsCurveString->IsNull() && !jsCurveString->IsUndefined() && jsCurveString->IsString(vm)) {
        aniTimFunc = jsCurveString->ToString(vm)->ToString(vm);
        if (aniTimFunc == DOM_ANIMATION_TIMING_FUNCTION_CUSTOM && customCallBack) {
            type = ANIMATION_CURVE_TYPE_FUNC;
        } else if (aniTimFunc != DOM_ANIMATION_TIMING_FUNCTION_CUSTOM) {
            type = ANIMATION_CURVE_TYPE_STR;
        }
    }
}
} // namespace

void TabsBridge::RegisterTabsAttributes(panda::Local<panda::ObjectRef> object, panda::EcmaVM* vm)
{
    const char* functionNames[] = {
        "create", "pop", "setTabBarMode", "setScrollableBarModeOptions", "resetScrollableBarModeOptions",
        "setBarGridAlign", "resetBarGridAlign", "resetTabBarMode", "setDivider", "resetDivider", "setFadingEdge",
        "resetFadingEdge", "setTabOnUnselected", "resetTabOnUnselected", "setTabsOnContentDidScroll",
        "resetTabsOnContentDidScroll", "setBarBackgroundColor", "resetBarBackgroundColor",
        "setBarBackgroundBlurStyle", "resetBarBackgroundBlurStyle", "setBarBackgroundEffect",
        "resetBarBackgroundEffect", "setBarOverlap", "resetBarOverlap", "setIsVertical", "resetIsVertical",
        "setTabBarPosition", "resetTabBarPosition", "setTabsOptionsIndex", "resetTabsOptionsIndex",
        "setTabsOptionsController", "resetTabsOptionsController", "setTabsOptionsBarModifier",
        "resetTabsOptionsBarModifier", "setScrollable", "resetScrollable", "setTabBarWidth", "resetTabBarWidth",
        "setTabBarHeight", "resetTabBarHeight", "setBarAdaptiveHeight", "resetBarAdaptiveHeight",
        "setAnimationCurve", "resetAnimationCurve", "setNoMinHeightLimit", "resetNoMinHeightLimit",
        "setAnimationDuration", "resetAnimationDuration", "setBarPosition", "resetBarPosition", "setTabClip",
        "resetTabClip", "setTabEdgeEffect", "resetTabEdgeEffect", "setNestedScroll", "resetNestedScroll",
        "setTabPageFlipMode", "resetTabPageFlipMode", "setWidthAuto", "resetWidthAuto", "setHeightAuto",
        "resetHeightAuto", "setAnimateMode", "resetAnimateMode", "setTabsOnSelected", "resetTabsOnSelected",
        "setCachedMaxCount", "resetCachedMaxCount", "setTabsOnChange", "resetTabsOnChange",
        "setTabsOnTabBarClick", "resetTabsOnTabBarClick", "setTabsOnAnimationStart",
        "resetTabsOnAnimationStart", "setTabsOnAnimationEnd", "resetTabsOnAnimationEnd", "setTabsOnGestureSwipe",
        "resetTabsOnGestureSwipe", "setTabsOnContentWillChange", "resetTabsOnContentWillChange",
        "setTabsCustomContentTransition", "resetTabsCustomContentTransition", "setTabsBarFloatingStyle",
        "resetTabsBarFloatingStyle"
    };
    Local<JSValueRef> functionValues[] = {
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::Create),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::Pop),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetScrollableBarModeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetScrollableBarModeOptions),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarGridAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarGridAlign),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetDivider),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetFadingEdge),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetFadingEdge),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabOnUnselected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabOnUnselected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetOnContentDidScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetOnContentDidScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundColor),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundBlurStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarBackgroundEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarBackgroundEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarOverlap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarOverlap),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetIsVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetIsVertical),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOptionsIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOptionsIndex),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOptionsController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOptionsController),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOptionsBarModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOptionsBarModifier),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetScrollable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetScrollable),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarWidth),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabBarHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabBarHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarAdaptiveHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarAdaptiveHeight),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetAnimationCurve),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetAnimationCurve),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetNoMinHeightLimit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetNoMinHeightLimit),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetAnimationDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetAnimationDuration),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetBarPosition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabClip),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabClip),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabEdgeEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabEdgeEffect),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetNestedScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetNestedScroll),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabPageFlipMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabPageFlipMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetWidthAuto),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetWidthAuto),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetHeightAuto),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetHeightAuto),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetAnimateMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetAnimateMode),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnSelected),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetCachedMaxCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetCachedMaxCount),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnTabBarClick),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnTabBarClick),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnAnimationStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnAnimationStart),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnAnimationEnd),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnAnimationEnd),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnGestureSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnGestureSwipe),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsOnContentWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsOnContentWillChange),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsCustomContentTransition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsCustomContentTransition),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::SetTabsBarFloatingStyle),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), TabsBridge::ResetTabsBarFloatingStyle),
    };
    auto tabs = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(functionNames), functionNames, functionValues);
    object->Set(vm, panda::StringRef::NewFromUtf8(vm, "tabs"), tabs);
}

ArkUINativeModuleValue TabsBridge::Create(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    BarPosition barPosition = BarPosition::START;
    RefPtr<AceType> tabController;
    RefPtr<TabsControllerNG> tabsController = AceType::MakeRefPtr<TabsControllerNG>();
    int32_t index = -1;
    Local<JSValueRef> changeEventVal = panda::JSValueRef::Undefined(vm);
    auto jsValue = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    if (!jsValue.IsNull() && !jsValue->IsUndefined() && jsValue->IsObject(vm)) {
        auto obj = jsValue->ToObject(vm);
        auto val = ArkTSUtils::GetProperty(vm, obj, "barPosition");
        if (!val.IsNull() && !val->IsUndefined() && val->IsNumber()) {
            auto barPositionVal = val->Int32Value(vm);
            if (barPositionVal >= DEFAULT_TAB_BAR_POSITION && barPositionVal <= MAX_TAB_BAR_POSITION) {
                barPosition = static_cast<BarPosition>(barPositionVal);
            }
        }
        auto controller = ArkTSUtils::GetProperty(vm, obj, "controller");
        if (!controller.IsNull() && !controller->IsUndefined() && controller->IsObject(vm)) {
            auto* jsTabsController =
                static_cast<Framework::JSTabsController*>(controller->ToObject(vm)->GetNativePointerField(vm, 0));
            if (jsTabsController) {
                jsTabsController->SetInstanceId(Container::CurrentId());
                tabController = jsTabsController->GetController();
                jsTabsController->SetControllerHandle(tabsController);
            }
        }
        auto indexVal = ArkTSUtils::GetProperty(vm, obj, "index");
        if (!indexVal.IsNull() && !indexVal->IsUndefined() && indexVal->IsNumber()) {
            index = indexVal->Int32Value(vm);
            index = index < 0 ? 0 : index;
            if (!tabController) {
                tabController = Framework::JSTabsController::CreateController();
            }
#ifndef NG_BUILD
            TrySetInitialIndex(tabController, index);
#endif
            changeEventVal = ArkTSUtils::GetProperty(vm, obj, "$index");
        } else if (!indexVal.IsNull() && !indexVal->IsUndefined() && indexVal->IsObject(vm)) {
            auto indexObj = indexVal->ToObject(vm);
            auto indexValueProperty = ArkTSUtils::GetProperty(vm, indexObj, "value");
            if (!indexValueProperty.IsNull() && !indexValueProperty->IsUndefined() && indexValueProperty->IsNumber()) {
                index = indexValueProperty->Int32Value(vm);
                index = index < 0 ? 0 : index;
            }
            changeEventVal = ArkTSUtils::GetProperty(vm, indexObj, "changeEvent");
        }
    }
    GetArkUINodeModifiers()->getTabsModifier()->createTabs(static_cast<int32_t>(barPosition), index,
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabsController)),
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabController)));
    ParseTabsCreateIndexObject(vm, changeEventVal);
    SetCreateBarModifier(vm, jsValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::Pop(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    PopTabsBridge();
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

ArkUINativeModuleValue TabsBridge::SetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        Local<JSValueRef> barModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
        Local<JSValueRef> optionsArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
        TabBarMode barMode = TabBarMode::FIXED;
        if (argc < TABS_ARG_INDEX_2) {
            GetArkUINodeModifiers()->getTabsModifier()->setTabBarMode(nativeNode, static_cast<int32_t>(barMode));
            return panda::JSValueRef::Undefined(vm);
        }
        if (!barModeArg.IsNull() && !barModeArg->IsUndefined() && barModeArg->IsString(vm)) {
            barMode = Framework::ConvertStrToTabBarMode(barModeArg->ToString(vm)->ToString(vm));
        }
        if (barMode == TabBarMode::SCROLLABLE) {
            if (argc > TABS_ARG_INDEX_2 && optionsArg->IsObject(vm)) {
                auto optionsObject = optionsArg->ToObject(vm);
                auto marginArg = optionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "margin"));
                auto nonScrollableLayoutStyleArg =
                    optionsObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "nonScrollableLayoutStyle"));
                CalcDimension margin(0.0, DimensionUnit::VP);
                RefPtr<ResourceObject> marginResObj;
                if (marginArg.IsNull() || marginArg->IsUndefined() ||
                    !ArkTSUtils::ParseJsDimensionVp(vm, marginArg, margin, marginResObj) || Negative(margin.Value()) ||
                    margin.Unit() == DimensionUnit::PERCENT) {
                    margin = Dimension(0.0, DimensionUnit::VP);
                    marginResObj.Reset();
                }
                int32_t barModeStyle = -1;
                int32_t layoutStyle = -1;
                RefPtr<ResourceObject> nullResObj;
                if (!nonScrollableLayoutStyleArg.IsNull() && !nonScrollableLayoutStyleArg->IsUndefined() &&
                    ArkTSUtils::ConvertFromJSValue(vm, nonScrollableLayoutStyleArg, layoutStyle, nullResObj) &&
                    layoutStyle >= static_cast<int32_t>(LayoutStyle::ALWAYS_CENTER) &&
                    layoutStyle <= static_cast<int32_t>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
                    barModeStyle = layoutStyle;
                }
                GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
                    nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
                TabsResourceObjParam param { TabJsResType::SCROLLABLE_BAR_MARGIN, AceType::RawPtr(marginResObj) };
                GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &param);
            } else {
                GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
            }
        }
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarMode(nativeNode, static_cast<int32_t>(barMode));
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> barModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> marginArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> nonScrollableLayoutStyleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);

    if (barModeArg->IsNull() || barModeArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    TabBarMode barMode = TabBarMode::FIXED;
    barMode = Framework::ConvertStrToTabBarMode(barModeArg->ToString(vm)->ToString(vm));
    int32_t tabBarMode = static_cast<int32_t>(barMode);
    GetArkUINodeModifiers()->getTabsModifier()->setTabBarMode(nativeNode, tabBarMode);

    GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(nativeNode, nullptr);
    if (tabBarMode == TABBARMODE_SCROLLABLE) {
        if (marginArg->IsNull() || marginArg->IsUndefined() || nonScrollableLayoutStyleArg->IsNull() ||
            nonScrollableLayoutStyleArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        int barModeStyle = nonScrollableLayoutStyleArg->Int32Value(vm);
        CalcDimension margin(0.0, DimensionUnit::VP);
        RefPtr<ResourceObject> marginResObj;
        if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, margin, marginResObj)) {
            margin.Reset();
        }

        GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
            nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
        GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(
            nativeNode, AceType::RawPtr(marginResObj));
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        Local<JSValueRef> optionsArg = secondArg;
        if (optionsArg.IsNull() || optionsArg->IsUndefined() || !optionsArg->IsObject(vm)) {
            GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        auto optionsObject = optionsArg->ToObject(vm);
        auto marginArg = ArkTSUtils::GetProperty(vm, optionsObject, "margin");
        auto nonScrollableLayoutStyleArg = ArkTSUtils::GetProperty(vm, optionsObject, "nonScrollableLayoutStyle");
        CalcDimension margin(0.0, DimensionUnit::VP);
        RefPtr<ResourceObject> marginResObj;
        if (marginArg.IsNull() || marginArg->IsUndefined() ||
            !ArkTSUtils::ParseJsDimensionVp(vm, marginArg, margin, marginResObj) || Negative(margin.Value()) ||
            margin.Unit() == DimensionUnit::PERCENT) {
            margin = Dimension(0.0, DimensionUnit::VP);
            marginResObj.Reset();
        }
        int32_t barModeStyle = -1;
        int32_t layoutStyle = -1;
        if (!nonScrollableLayoutStyleArg.IsNull() && !nonScrollableLayoutStyleArg->IsUndefined() &&
            ArkTSUtils::ParseJsInt32(vm, nonScrollableLayoutStyleArg, layoutStyle) &&
            layoutStyle >= static_cast<int32_t>(LayoutStyle::ALWAYS_CENTER) &&
            layoutStyle <= static_cast<int32_t>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
            barModeStyle = layoutStyle;
        }
        GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
            nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
        TabsResourceObjParam param { TabJsResType::SCROLLABLE_BAR_MARGIN, AceType::RawPtr(marginResObj) };
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &param);
        return panda::JSValueRef::Undefined(vm);
    }

    if (thirdArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int barModeStyle = thirdArg->Int32Value(vm);

    CalcDimension margin(0.0, DimensionUnit::VP);
    RefPtr<ResourceObject> marginResObj;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, secondArg, margin, marginResObj)) {
        margin.Reset();
    }

    GetArkUINodeModifiers()->getTabsModifier()->setScrollableBarModeOptions(
        nativeNode, margin.Value(), static_cast<int>(margin.Unit()), barModeStyle);
    GetArkUINodeModifiers()->getTabsModifier()->createScrollableBarModeOptionsWithResourceObj(
        nativeNode, AceType::RawPtr(marginResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetScrollableBarModeOptions(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetScrollableBarModeOptions(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        BarGridColumnOptions columnOption;
        RefPtr<ResourceObject> columnGutterResObj;
        RefPtr<ResourceObject> columnMarginResObj;
        Local<JSValueRef> gridAlignArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
        if (runtimeCallInfo->GetArgsNumber() > TABS_ARG_INDEX_1 && !gridAlignArg->IsNull() &&
            !gridAlignArg->IsUndefined() && gridAlignArg->IsObject(vm)) {
            auto gridAlignObject = gridAlignArg->ToObject(vm);
            auto smArg = gridAlignObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "sm"));
            auto mdArg = gridAlignObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "md"));
            auto lgArg = gridAlignObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "lg"));
            auto gutterArg = gridAlignObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "gutter"));
            auto marginArg = gridAlignObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "margin"));
            if (!smArg.IsNull() && !smArg->IsUndefined() && smArg->IsNumber() &&
                smArg->Int32Value(vm) >= 0 && smArg->Int32Value(vm) <= SM_COLUMN_NUM &&
                smArg->Int32Value(vm) % REMAINDER == 0) {
                columnOption.sm = smArg->Int32Value(vm);
            }
            if (!mdArg.IsNull() && !mdArg->IsUndefined() && mdArg->IsNumber() &&
                mdArg->Int32Value(vm) >= 0 && mdArg->Int32Value(vm) <= MD_COLUMN_NUM &&
                mdArg->Int32Value(vm) % REMAINDER == 0) {
                columnOption.md = mdArg->Int32Value(vm);
            }
            if (!lgArg.IsNull() && !lgArg->IsUndefined() && lgArg->IsNumber() &&
                lgArg->Int32Value(vm) >= 0 && lgArg->Int32Value(vm) <= LG_COLUMN_NUM &&
                lgArg->Int32Value(vm) % REMAINDER == 0) {
                columnOption.lg = lgArg->Int32Value(vm);
            }
            CalcDimension columnGutter;
            if (!gutterArg.IsNull() && !gutterArg->IsUndefined() &&
                ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, columnGutter, columnGutterResObj) &&
                NonNegative(columnGutter.Value()) && columnGutter.Unit() != DimensionUnit::PERCENT) {
                columnOption.gutter = columnGutter;
            }
            CalcDimension columnMargin;
            if (!marginArg.IsNull() && !marginArg->IsUndefined() &&
                ArkTSUtils::ParseJsDimensionVp(vm, marginArg, columnMargin, columnMarginResObj) &&
                NonNegative(columnMargin.Value()) && columnMargin.Unit() != DimensionUnit::PERCENT) {
                columnOption.margin = columnMargin;
            }
        }
        ArkUI_Float32 values[SIZE_OF_VALUES] = { static_cast<ArkUI_Float32>(columnOption.gutter.Value()),
            static_cast<ArkUI_Float32>(columnOption.margin.Value()) };
        int unitsAndColumn[SIZE_OF_FIVE] = { static_cast<int>(columnOption.gutter.Unit()),
            static_cast<int>(columnOption.margin.Unit()), columnOption.sm, columnOption.md, columnOption.lg };
        GetArkUINodeModifiers()->getTabsModifier()->setBarGridAlign(
            nativeNode, values, SIZE_OF_VALUES, unitsAndColumn, SIZE_OF_FIVE);
        TabsResourceObjParam gutterParam { TabJsResType::BAR_GRID_GUTTER, AceType::RawPtr(columnGutterResObj) };
        TabsResourceObjParam marginParam { TabJsResType::BAR_GRID_MARGIN, AceType::RawPtr(columnMarginResObj) };
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &gutterParam);
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &marginParam);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> smArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> mdArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> lgArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> gutterArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    Local<JSValueRef> marginArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));

    int32_t sm = DEFAULT_COLUMN;
    int32_t md = DEFAULT_COLUMN;
    int32_t lg = DEFAULT_COLUMN;
    if (smArg->IsNumber() && smArg->Int32Value(vm) >= 0 && smArg->Int32Value(vm) <= SM_COLUMN_NUM &&
        smArg->Int32Value(vm) % REMAINDER == 0) {
        sm = smArg->Int32Value(vm);
    }
    if (mdArg->IsNumber() && mdArg->Int32Value(vm) >= 0 && mdArg->Int32Value(vm) <= MD_COLUMN_NUM &&
        mdArg->Int32Value(vm) % REMAINDER == 0) {
        md = mdArg->Int32Value(vm);
    }
    if (lgArg->IsNumber() && lgArg->Int32Value(vm) >= 0 && lgArg->Int32Value(vm) <= LG_COLUMN_NUM &&
        lgArg->Int32Value(vm) % REMAINDER == 0) {
        lg = lgArg->Int32Value(vm);
    }

    CalcDimension columnGutter;
    CalcDimension columnMargin;
    RefPtr<ResourceObject> columnGutterResObj;
    RefPtr<ResourceObject> columnMarginResObj;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, gutterArg, columnGutter, columnGutterResObj) ||
        !NonNegative(columnGutter.Value()) ||
        columnGutter.Unit() == DimensionUnit::PERCENT) {
        columnGutter.Reset();
    }
    if (!ArkTSUtils::ParseJsDimensionVp(vm, marginArg, columnMargin, columnMarginResObj) ||
        !NonNegative(columnMargin.Value()) ||
        columnMargin.Unit() == DimensionUnit::PERCENT) {
        columnMargin.Reset();
    }

    ArkUI_Float32 values[SIZE_OF_VALUES] = { static_cast<ArkUI_Float32>(columnGutter.Value()),
        static_cast<ArkUI_Float32>(columnMargin.Value()) };
    int unitsAndColumn[SIZE_OF_FIVE] = { static_cast<int>(columnGutter.Unit()), static_cast<int>(columnMargin.Unit()),
        sm, md, lg };

    GetArkUINodeModifiers()->getTabsModifier()->setBarGridAlign(
        nativeNode, values, SIZE_OF_VALUES, unitsAndColumn, SIZE_OF_FIVE);
    GetArkUINodeModifiers()->getTabsModifier()->createBarGridAlignWithResourceObj(
        nativeNode, AceType::RawPtr(columnGutterResObj), AceType::RawPtr(columnMarginResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarGridAlign(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarGridAlign(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
        auto tabTheme = frameNode->GetTheme<TabTheme>(true);
        CHECK_NULL_RETURN(tabTheme, panda::NativePointerRef::New(vm, nullptr));
        TabsItemDivider divider;
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        CalcDimension dividerStrokeWidth(0.0, DimensionUnit::VP);
        CalcDimension dividerStartMargin(0.0, DimensionUnit::VP);
        CalcDimension dividerEndMargin(0.0, DimensionUnit::VP);
        RefPtr<ResourceObject> strokeWidthResObj;
        RefPtr<ResourceObject> colorResObj;
        RefPtr<ResourceObject> startMarginResObj;
        RefPtr<ResourceObject> endMarginResObj;
        if (argc > TABS_ARG_INDEX_1) {
            auto dividerInfo = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
            Local<panda::ObjectRef> dividerObject = panda::ObjectRef::New(vm);
            bool isDividerObject = false;
            if (!dividerInfo.IsNull() && !dividerInfo->IsUndefined()) {
                if (dividerInfo->IsObject(vm)) {
                    dividerObject = dividerInfo->ToObject(vm);
                    isDividerObject = true;
                }
            }
            if (dividerInfo->IsNull()) {
                divider.isNull = true;
            } else {
                auto dividerStrokeWidthArg = dividerObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "strokeWidth"));
                auto colorArg = dividerObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "color"));
                auto dividerStartMarginArg = dividerObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "startMargin"));
                auto dividerEndMarginArg = dividerObject->Get(vm, panda::StringRef::NewFromUtf8(vm, "endMargin"));
                if (!isDividerObject || dividerStrokeWidthArg.IsNull() || dividerStrokeWidthArg->IsUndefined() ||
                    !ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArg, dividerStrokeWidth, strokeWidthResObj) ||
                    dividerStrokeWidth.Value() < 0.0f || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
                    divider.strokeWidth.Reset();
                } else {
                    divider.strokeWidth = dividerStrokeWidth;
                }
                Color colorObj;
                if (!isDividerObject || colorArg.IsNull() || colorArg->IsUndefined() ||
                    !ArkTSUtils::ParseJsColorAlpha(
                        vm, colorArg, colorObj, colorResObj, ArkTSUtils::MakeNativeNodeInfo(nativeNode))) {
                    divider.color = tabTheme->GetDividerColor();
                    GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, false);
                } else {
                    divider.color = colorObj;
                    GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, true);
                }
                if (!isDividerObject || dividerStartMarginArg.IsNull() || dividerStartMarginArg->IsUndefined() ||
                    !ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArg, dividerStartMargin, startMarginResObj) ||
                    dividerStartMargin.Value() < 0.0f || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
                    divider.startMargin.Reset();
                } else {
                    divider.startMargin = dividerStartMargin;
                }
                if (!isDividerObject || dividerEndMarginArg.IsNull() || dividerEndMarginArg->IsUndefined() ||
                    !ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArg, dividerEndMargin, endMarginResObj) ||
                    dividerEndMargin.Value() < 0.0f || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
                    divider.endMargin.Reset();
                } else {
                    divider.endMargin = dividerEndMargin;
                }
            }
        }
        uint32_t size = SIZE_OF_THREE;
        ArkUI_Float32 values[size];
        int32_t units[size];
        values[TABS_ARG_INDEX_0] = static_cast<ArkUI_Float32>(divider.strokeWidth.Value());
        values[TABS_ARG_INDEX_1] = static_cast<ArkUI_Float32>(divider.startMargin.Value());
        values[TABS_ARG_INDEX_2] = static_cast<ArkUI_Float32>(divider.endMargin.Value());
        units[TABS_ARG_INDEX_0] = static_cast<int32_t>(divider.strokeWidth.Unit());
        units[TABS_ARG_INDEX_1] = static_cast<int32_t>(divider.startMargin.Unit());
        units[TABS_ARG_INDEX_2] = static_cast<int32_t>(divider.endMargin.Unit());
        if (divider.isNull) {
            GetArkUINodeModifiers()->getTabsModifier()->resetDivider(nativeNode);
        } else {
            GetArkUINodeModifiers()->getTabsModifier()->setDivider(
                nativeNode, divider.color.GetValue(), values, units, size);
        }
        TabsResourceObjParam strokeWidthParam { TabJsResType::DIVIDER_STROKE_WIDTH,
            AceType::RawPtr(strokeWidthResObj) };
        TabsResourceObjParam colorParam { TabJsResType::DIVIDER_COLOR, AceType::RawPtr(colorResObj) };
        TabsResourceObjParam startMarginParam { TabJsResType::DIVIDER_START_MARGIN,
            AceType::RawPtr(startMarginResObj) };
        TabsResourceObjParam endMarginParam { TabJsResType::DIVIDER_END_MARGIN, AceType::RawPtr(endMarginResObj) };
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &strokeWidthParam);
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &colorParam);
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &startMarginParam);
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &endMarginParam);
        return panda::JSValueRef::Undefined(vm);
    }
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> dividerStrokeWidthArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> dividerStartMarginArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> dividerEndMarginArgs = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    auto isDividerStrokeWidthArgsInvalid = dividerStrokeWidthArgs->IsNull() || dividerStrokeWidthArgs->IsUndefined();
    auto isDividerStartMarginArgsInvalid = dividerStartMarginArgs->IsNull() || dividerStartMarginArgs->IsUndefined();
    auto isDividerEndMarginArgsInvalid = dividerEndMarginArgs->IsNull() || dividerEndMarginArgs->IsUndefined();
    auto isColorArgInvalid = colorArg->IsNull() || colorArg->IsUndefined();
    if (isDividerStrokeWidthArgsInvalid && isDividerStartMarginArgsInvalid && isDividerEndMarginArgsInvalid &&
        isColorArgInvalid) {
        GetArkUINodeModifiers()->getTabsModifier()->resetDivider(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    uint32_t color;
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::NativePointerRef::New(vm, nullptr));
    auto tabTheme = frameNode->GetTheme<TabTheme>(true);
    CHECK_NULL_RETURN(tabTheme, panda::NativePointerRef::New(vm, nullptr));

    RefPtr<ResourceObject> strokeWidthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;
    if (isDividerStrokeWidthArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStrokeWidthArgs, dividerStrokeWidth, strokeWidthResObj) ||
        LessNotEqual(dividerStrokeWidth.Value(), 0.0f) || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
        dividerStrokeWidth.Reset();
    }
    Color colorObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (isColorArgInvalid || !ArkTSUtils::ParseJsColorAlpha(vm, colorArg, colorObj, colorResObj, nodeInfo)) {
        color = tabTheme->GetDividerColor().GetValue();
        GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, false);
    } else {
        color = colorObj.GetValue();
        GetArkUINodeModifiers()->getTabsModifier()->setDividerColorByUser(nativeNode, true);
    }
    if (isDividerStartMarginArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerStartMarginArgs, dividerStartMargin, startMarginResObj) ||
        LessNotEqual(dividerStartMargin.Value(), 0.0f) || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
        dividerStartMargin.Reset();
    }
    if (isDividerEndMarginArgsInvalid ||
        !ArkTSUtils::ParseJsDimensionVp(vm, dividerEndMarginArgs, dividerEndMargin, endMarginResObj) ||
        LessNotEqual(dividerEndMargin.Value(), 0.0f) || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
        dividerEndMargin.Reset();
    }
    uint32_t size = SIZE_OF_THREE;
    ArkUI_Float32 values[size];
    int32_t units[size];
    values[TABS_ARG_INDEX_0] = static_cast<ArkUI_Float32>(dividerStrokeWidth.Value());
    values[TABS_ARG_INDEX_1] = static_cast<ArkUI_Float32>(dividerStartMargin.Value());
    values[TABS_ARG_INDEX_2] = static_cast<ArkUI_Float32>(dividerEndMargin.Value());
    units[TABS_ARG_INDEX_0] = static_cast<int32_t>(dividerStrokeWidth.Unit());
    units[TABS_ARG_INDEX_1] = static_cast<int32_t>(dividerStartMargin.Unit());
    units[TABS_ARG_INDEX_2] = static_cast<int32_t>(dividerEndMargin.Unit());
    GetArkUINodeModifiers()->getTabsModifier()->setDivider(nativeNode, color, values, units, size);
    GetArkUINodeModifiers()->getTabsModifier()->createDividerWithResourceObj(nativeNode,
        AceType::RawPtr(strokeWidthResObj), AceType::RawPtr(colorResObj), AceType::RawPtr(startMarginResObj),
        AceType::RawPtr(endMarginResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetDivider(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetDivider(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool fadingEdge = true;
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc > TABS_ARG_INDEX_1 && !secondArg.IsNull() && !secondArg->IsUndefined()) {
            RefPtr<ResourceObject> resObj;
            ParseJsBoolForSwiper(vm, secondArg, fadingEdge, resObj);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setFadingEdge(nativeNode, fadingEdge);
        return panda::JSValueRef::Undefined(vm);
    }
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetFadingEdge(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool fadingEdge = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setFadingEdge(nativeNode, fadingEdge);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetFadingEdge(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetFadingEdge(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg.IsNull() || callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabOnUnselected(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback = [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs  OnUnselected callback execute failed.");
            return;
        }
        if (isJsView) {
            ACE_SCORING_EVENT("Tabs.onUnselected");
            ACE_SCOPED_TRACE("Tabs.onUnselected index %d", tabsInfo->GetIndex());
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, tabsInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabOnUnselected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabOnUnselected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabOnUnselected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (isJsView) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < TABS_ARG_INDEX_2) {
            return panda::JSValueRef::Undefined(vm);
        }
    }
    if (!callbackArg->IsFunction(vm)) {
        if (callbackArg->IsUndefined()) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentDidScroll(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, int32_t, float_t, float_t)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), isJsView](
        int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::NumberRef> selectedIndexParam = panda::NumberRef::New(vm, selectedIndex);
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
        panda::Local<panda::NumberRef> positionParam = panda::NumberRef::New(vm, position);
        panda::Local<panda::NumberRef> mainAxisLengthParam = panda::NumberRef::New(vm, mainAxisLength);
        panda::Local<panda::JSValueRef> params[PARAM_COUNT_FOUR] = { selectedIndexParam, indexParam,
            positionParam, mainAxisLengthParam };
        auto result = func->Call(vm, func.ToLocal(), params, PARAM_COUNT_FOUR);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnContentDidScroll(nativeNode,
        reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetOnContentDidScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentDidScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        Color color = Color::BLACK.BlendOpacity(0.0f);
        RefPtr<ResourceObject> backgroundColorResObj;
        if (!secondArg.IsNull() && !secondArg->IsUndefined()) {
            bool parseResult = ArkTSUtils::ConvertFromJSValue(vm, secondArg, color, backgroundColorResObj);
            GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundColorByUser(nativeNode, parseResult);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundColor(nativeNode, color.GetValue());
        if (SystemProperties::ConfigChangePerform()) {
            GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundColorWithResourceObj(
                nativeNode, AceType::RawPtr(backgroundColorResObj));
        }
        return panda::JSValueRef::Undefined(vm);
    }
    Color color;
    RefPtr<ResourceObject> backgroundColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColorAlpha(vm, secondArg, color, backgroundColorResObj, nodeInfo)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundColor(nativeNode);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundColor(nativeNode, color.GetValue());
        auto bgColorRawPtr = AceType::RawPtr(backgroundColorResObj);
        GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundColorWithResourceObj(nativeNode, bgColorRawPtr);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundColor(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundColor(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

bool ParseJsInt32(const EcmaVM *vm, const Local<JSValueRef> &value, int32_t &result)
{
    if (value->IsNumber()) {
        result = value->Int32Value(vm);
        return true;
    }
    if (value->IsString(vm)) {
        result = StringUtils::StringToInt(value->ToString(vm)->ToString(vm));
        return true;
    }

    return false;
}

ArkUITabBarBackgroundBlurStyle ConvertBlurStyleOption(const BlurStyleOption& option)
{
    return { static_cast<ArkUI_Int32>(option.blurStyle), static_cast<ArkUI_Int32>(option.colorMode),
        static_cast<ArkUI_Int32>(option.adaptiveColor), static_cast<ArkUI_Float32>(option.scale),
        option.blurOption.grayscale.data(), static_cast<ArkUI_Int32>(option.blurOption.grayscale.size()),
        static_cast<ArkUI_Int32>(option.policy), option.inactiveColor.GetValue(), option.isValidColor,
        static_cast<ArkUI_Int32>(option.blurType) };
}

ArkUITabBarBackgroundEffect ConvertEffectOption(const EffectOption& option)
{
    return { static_cast<ArkUI_Float32>(option.radius.Value()), static_cast<ArkUI_Float32>(option.saturation),
        static_cast<ArkUI_Float32>(option.brightness), option.color.GetValue(),
        static_cast<ArkUI_Int32>(option.adaptiveColor), option.blurOption.grayscale.data(),
        static_cast<ArkUI_Int32>(option.blurOption.grayscale.size()), static_cast<ArkUI_Int32>(option.policy),
        static_cast<ArkUI_Int32>(option.blurType), option.isValidColor, option.inactiveColor.GetValue() };
}

RefPtr<ResourceObject> SetBarBackgroundBlurStyleParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Bool& isValidColor,
    Color& inactiveColor, ArkUI_Int32& policy, ArkUI_Int32& blurType, ArkUINodeHandle nativeNode)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_6);
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_7);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_8);
    RefPtr<ResourceObject> inactiveColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, inactiveColorResObj, nodeInfo)) {
        isValidColor = true;
    }
    ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }
    return inactiveColorResObj;
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> blurStyleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> colorModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> adaptiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> scaleArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    Local<JSValueRef> blurOptionsArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() <= TABS_ARG_INDEX_1) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        BlurStyleOption styleOption;
        if (!blurStyleArg.IsNull() && !blurStyleArg->IsUndefined() && blurStyleArg->IsNumber()) {
            auto blurStyle = blurStyleArg->Int32Value(vm);
            if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
                blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
                styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
            }
        }
        RefPtr<ResourceObject> inactiveColorResObj;
        if (runtimeCallInfo->GetArgsNumber() > TABS_ARG_INDEX_2 && !colorModeArg.IsNull() &&
            !colorModeArg->IsUndefined() && colorModeArg->IsObject(vm)) {
            ArkTSUtils::ParseBlurStyleOption(vm, colorModeArg, styleOption);
            if (SystemProperties::ConfigChangePerform()) {
                ArkTSUtils::ParseJsColor(vm, ArkTSUtils::GetProperty(vm, colorModeArg, "inactiveColor"),
                    styleOption.inactiveColor, inactiveColorResObj);
            }
        }
        auto arkStyleOption = ConvertBlurStyleOption(styleOption);
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundBlurStyle(nativeNode, &arkStyleOption);
        TabsResourceObjParam param { TabJsResType::BlurStyle_INACTIVE_COLOR, AceType::RawPtr(inactiveColorResObj) };
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &param);
        return panda::JSValueRef::Undefined(vm);
    }
    BlurOption blurOption;
    ArkUITabBarBackgroundBlurStyle styleOption = { static_cast<int32_t>(BlurStyle::NO_MATERIAL),
        static_cast<int32_t>(ThemeColorMode::SYSTEM), static_cast<int32_t>(AdaptiveColor::DEFAULT), 1.0,
        blurOption.grayscale.data(), static_cast<ArkUI_Int32>(blurOption.grayscale.size()),
        static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE), Color::TRANSPARENT.GetValue(), false,
        static_cast<int32_t>(BlurType::WITHIN_WINDOW) };
    if (blurStyleArg->IsNumber()) {
        styleOption.blurStyle = blurStyleArg->Int32Value(vm);
    }
    bool isHasOptions = !(colorModeArg->IsUndefined() && adaptiveColorArg->IsUndefined() && scaleArg->IsUndefined() &&
                          blurOptionsArg->IsUndefined());
    if (isHasOptions) {
        ParseJsInt32(vm, colorModeArg, styleOption.colorMode);
        ParseJsInt32(vm, adaptiveColorArg, styleOption.adaptiveColor);
        if (scaleArg->IsNumber()) {
            styleOption.scale = scaleArg->ToNumber(vm)->Value();
        }
        if (blurOptionsArg->IsArray(vm)) {
            Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(blurOptionsArg);
            auto grey1 = params->GetValueAt(vm, blurOptionsArg, 0)->Uint32Value(vm);
            auto grey2 = params->GetValueAt(vm, blurOptionsArg, 1)->Uint32Value(vm);
            std::vector<float> greyVec = { 0.0f, 0.0f };
            greyVec[0] = grey1;
            greyVec[1] = grey2;
            blurOption.grayscale = greyVec;
            styleOption.blurValues = blurOption.grayscale.data();
            styleOption.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
        }
    }
    Color inactiveColor = Color::TRANSPARENT;
    auto inactiveColorResObj = SetBarBackgroundBlurStyleParam(
        runtimeCallInfo, styleOption.isValidColor, inactiveColor, styleOption.policy, styleOption.blurType, nativeNode);
    styleOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundBlurStyle(nativeNode, &styleOption);
    GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundBlurStyleWithResourceObj(
        nativeNode, AceType::RawPtr(inactiveColorResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundBlurStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundBlurStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

RefPtr<ResourceObject> SetBarBackgroundEffectParam(ArkUIRuntimeCallInfo* runtimeCallInfo, ArkUI_Int32& policy,
    ArkUI_Int32& blurType, Color& inactiveColor, ArkUI_Bool& isValidColor, ArkUINodeHandle nativeNode)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> policyArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_7);
    Local<JSValueRef> inactiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_8);
    Local<JSValueRef> typeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_9);
    ParseJsInt32(vm, policyArg, policy);
    if (policy < static_cast<int32_t>(BlurStyleActivePolicy::FOLLOWS_WINDOW_ACTIVE_STATE) ||
        policy > static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_INACTIVE)) {
        policy = static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE);
    }
    ParseJsInt32(vm, typeArg, blurType);
    if (blurType < static_cast<int32_t>(BlurType::WITHIN_WINDOW) ||
        blurType > static_cast<int32_t>(BlurType::BEHIND_WINDOW)) {
        blurType = static_cast<int32_t>(BlurType::WITHIN_WINDOW);
    }
    RefPtr<ResourceObject> inactiveColorResObj;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (ArkTSUtils::ParseJsColor(vm, inactiveColorArg, inactiveColor, inactiveColorResObj, nodeInfo)) {
        isValidColor = true;
    }
    return inactiveColorResObj;
}

void SetAdaptiveColorAndBlurOptionParam(ArkUIRuntimeCallInfo* runtimeCallInfo, AdaptiveColor& adaptiveColor,
    BlurOption& blurOption)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    Local<JSValueRef> adaptiveColorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_5);
    Local<JSValueRef> blurOptionsArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_6);
    auto adaptiveColorValue = static_cast<int32_t>(AdaptiveColor::DEFAULT);
    if (adaptiveColorArg->IsNumber()) {
        adaptiveColorValue = adaptiveColorArg->Int32Value(vm);
        if (adaptiveColorValue >= static_cast<int32_t>(AdaptiveColor::DEFAULT) &&
            adaptiveColorValue <= static_cast<int32_t>(AdaptiveColor::AVERAGE)) {
            adaptiveColor = static_cast<AdaptiveColor>(adaptiveColorValue);
        }
    }
    if (blurOptionsArg->IsArray(vm)) {
        Local<panda::ArrayRef> params = static_cast<Local<panda::ArrayRef>>(blurOptionsArg);
        auto grey1 = params->GetValueAt(vm, blurOptionsArg, 0)->Uint32Value(vm);
        auto grey2 = params->GetValueAt(vm, blurOptionsArg, 1)->Uint32Value(vm);
        std::vector<float> greyVec = {0.0f, 0.0f};
        greyVec[0] = grey1;
        greyVec[1] = grey2;
        blurOption.grayscale = greyVec;
    }
}

void SetSaturationAndBrightnessEffectOptionParam(const EcmaVM* vm, const Local<JSValueRef>& saturationArg,
    const Local<JSValueRef>& brightnessArg, ArkUITabBarBackgroundEffect& effectOption)
{
    if (saturationArg->IsNumber()) {
        effectOption.saturation = saturationArg->ToNumber(vm)->Value();
        effectOption.saturation = (effectOption.saturation > 0.0f || NearZero(effectOption.saturation)) ?
                                    effectOption.saturation : 1.0f;
    }
    if (brightnessArg->IsNumber()) {
        effectOption.brightness = brightnessArg->ToNumber(vm)->Value();
        effectOption.brightness = (effectOption.brightness > 0.0f || NearZero(effectOption.brightness)) ?
                                    effectOption.brightness : 1.0f;
    }
}

ArkUINativeModuleValue TabsBridge::SetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> frameNodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> radiusArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> saturationArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    Local<JSValueRef> brightnessArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_3);
    Local<JSValueRef> colorArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_4);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, frameNodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(frameNodeArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() == TABS_ARG_INDEX_1) {
            return panda::JSValueRef::Undefined(vm);
        }
        auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
        CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
        EffectOption option;
        RefPtr<ResourceObject> colorResObj;
        RefPtr<ResourceObject> inactiveColorResObj;
        if (!radiusArg.IsNull() && !radiusArg->IsUndefined() && radiusArg->IsObject(vm)) {
            ArkTSUtils::ParseEffectOption(vm, radiusArg, option);
            if (SystemProperties::ConfigChangePerform()) {
                ArkTSUtils::ParseJsColor(
                    vm, ArkTSUtils::GetProperty(vm, radiusArg, "color"), option.color, colorResObj);
                ArkTSUtils::ParseJsColor(vm, ArkTSUtils::GetProperty(vm, radiusArg, "inactiveColor"),
                    option.inactiveColor, inactiveColorResObj);
            }
        }
        auto arkEffectOption = ConvertEffectOption(option);
        GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundEffect(nativeNode, &arkEffectOption);
        TabsResourceObjParam paramColor { TabJsResType::COLOR, AceType::RawPtr(colorResObj) };
        TabsResourceObjParam paramInactiveColor { TabJsResType::INACTIVE_COLOR, AceType::RawPtr(inactiveColorResObj) };
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &paramColor);
        GetArkUINodeModifiers()->getTabsModifier()->createWithResourceObj(nativeNode, &paramInactiveColor);
        return panda::JSValueRef::Undefined(vm);
    }
    BlurOption blurOption;
    ArkUITabBarBackgroundEffect effectOption = { 0.0f, 1.0f, 1.0f, Color::TRANSPARENT.GetValue(),
        static_cast<int32_t>(AdaptiveColor::DEFAULT), blurOption.grayscale.data(),
        static_cast<int32_t>(blurOption.grayscale.size()),
        static_cast<int32_t>(BlurStyleActivePolicy::ALWAYS_ACTIVE), static_cast<int32_t>(BlurType::WITHIN_WINDOW),
        false, Color::TRANSPARENT.GetValue() };
    CalcDimension radius;
    if (!ArkTSUtils::ParseJsDimensionVp(vm, radiusArg, radius) || LessNotEqual(radius.Value(), 0.0f)) {
        radius.SetValue(0.0f);
    }
    effectOption.radius = static_cast<ArkUI_Float32>(radius.Value());
    SetSaturationAndBrightnessEffectOptionParam(vm, saturationArg, brightnessArg, effectOption);
    RefPtr<ResourceObject> colorResObj;
    Color color = Color::TRANSPARENT;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    if (!ArkTSUtils::ParseJsColor(vm, colorArg, color, colorResObj, nodeInfo)) {
        color.SetValue(Color::TRANSPARENT.GetValue());
    }
    effectOption.color = color.GetValue();
    auto adaptiveColor = AdaptiveColor::DEFAULT;
    SetAdaptiveColorAndBlurOptionParam(runtimeCallInfo, adaptiveColor, blurOption);
    effectOption.adaptiveColor = static_cast<ArkUI_Int32>(adaptiveColor);
    effectOption.blurValues = blurOption.grayscale.data();
    effectOption.blurValuesSize = static_cast<ArkUI_Int32>(blurOption.grayscale.size());
    Color inactiveColor = Color::TRANSPARENT;
    auto inactiveColorResObj = SetBarBackgroundEffectParam(runtimeCallInfo, effectOption.policy, effectOption.blurType,
        inactiveColor, effectOption.isValidColor, nativeNode);
    effectOption.inactiveColor = inactiveColor.GetValue();
    GetArkUINodeModifiers()->getTabsModifier()->setBarBackgroundEffect(nativeNode, &effectOption);
    GetArkUINodeModifiers()->getTabsModifier()->createBarBackgroundEffectWithResourceObj(nativeNode,
        AceType::RawPtr(colorResObj), AceType::RawPtr(inactiveColorResObj));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarBackgroundEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarBackgroundEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> overlapArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool overlap = false;
        if (!overlapArg.IsNull() && !overlapArg->IsUndefined()) {
            RefPtr<ResourceObject> resObj;
            ParseJsBoolForSwiper(vm, overlapArg, overlap, resObj);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setBarOverlap(nativeNode, overlap);
        return panda::JSValueRef::Undefined(vm);
    }
    if (overlapArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetBarOverlap(nativeNode);
    } else {
        bool overlap = overlapArg->ToBoolean(vm)->Value();
        GetArkUINodeModifiers()->getTabsModifier()->setBarOverlap(nativeNode, overlap);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarOverlap(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarOverlap(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::SetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> isVerticalArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool isVertical = false;
        if (!isVerticalArg.IsNull() && !isVerticalArg->IsUndefined() && isVerticalArg->IsBoolean()) {
            isVertical = isVerticalArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getTabsModifier()->setIsVertical(nativeNode, isVertical);
        return panda::JSValueRef::Undefined(vm);
    }
    if (isVerticalArg->IsNull() || isVerticalArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetIsVertical(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    bool isVertical = isVerticalArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setIsVertical(nativeNode, isVertical);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetIsVertical(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetIsVertical(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> barValArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        int32_t barVal = DEFAULT_TAB_BAR_POSITION;
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc > TABS_ARG_INDEX_1 && !barValArg.IsNull() && !barValArg->IsUndefined() && barValArg->IsNumber()) {
            auto barPositionVal = barValArg->Int32Value(vm);
            if (barPositionVal >= DEFAULT_TAB_BAR_POSITION && barPositionVal <= MAX_TAB_BAR_POSITION) {
                barVal = barPositionVal;
            }
        }
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
        return panda::JSValueRef::Undefined(vm);
    }
    if (barValArg->IsNull() || barValArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    } else {
        int32_t barVal = barValArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
    }

    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> indexValArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (indexValArg->IsNull() || indexValArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsIndex(nativeNode);
    } else {
        int32_t indexVal = indexValArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsIndex(nativeNode, indexVal);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsIndex(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsIndex(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);

    Local<JSValueRef> controllerArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle tabsController = nullptr;
    if (!controllerArg->IsNull() && !controllerArg->IsUndefined() && controllerArg->IsNativePointer(vm)) {
        tabsController = nodePtr(controllerArg->ToNativePointer(vm)->Value());
    }
    if (!isJsView) {
        GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsController(nativeNode, tabsController);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsController(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    RefPtr<NG::TabsControllerNG> tabsController = AceType::MakeRefPtr<NG::TabsControllerNG>();
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsController(nativeNode,
        reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(tabsController)));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOptionsBarModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, nodeArg, vm), true, panda::JSValueRef::Undefined(vm));
    std::function<void(WeakPtr<NG::FrameNode>)> onApply;
    auto modifierVal = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    bool isJsView = ArkTSUtils::IsJsView(nodeArg, vm);
    if (!modifierVal->IsNull() && !modifierVal->IsUndefined() && modifierVal->IsObject(vm)) {
        auto globalObj = panda::JSNApi::GetGlobalObject(vm);
        auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applyCommonModifierToNode"));
        if (globalFunc->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> funcRef = globalFunc->ToObject(vm);
            onApply = [func = panda::CopyableGlobal(vm, funcRef),
                          modifierParam = panda::CopyableGlobal(vm, modifierVal),
                          isJsView](WeakPtr<NG::FrameNode> frameNode) {
                auto node = frameNode.Upgrade();
                CHECK_NULL_VOID(node);
                auto vm = func.GetEcmaVM();
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                panda::Local<panda::JSValueRef> args[NUM_2];
                args[0] = modifierParam.ToLocal();
                args[1] = panda::NativePointerRef::New(vm, AceType::RawPtr(node));
                PipelineContext::SetCallBackNode(node);
                auto result = func->Call(vm, func.ToLocal(), args, 2);
                if (isJsView) {
                    ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
                }
            };
        }
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOptionsBarModifier(
        nativeNode, reinterpret_cast<void*>(&onApply));
    return panda::JSValueRef::Undefined(runtimeCallInfo->GetVM());
}

ArkUINativeModuleValue TabsBridge::ResetTabsOptionsBarModifier(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOptionsBarModifier(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> scrollableArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        bool scrollable = true;
        if (!scrollableArg.IsNull() && !scrollableArg->IsUndefined() && scrollableArg->IsBoolean()) {
            scrollable = scrollableArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getTabsModifier()->setScrollable(nativeNode, scrollable);
        return undefinedRes;
    }

    if (scrollableArg->IsNull() || scrollableArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetScrollable(nativeNode);
        return undefinedRes;
    }

    bool scrollable = scrollableArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setScrollable(nativeNode, scrollable);
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetScrollable(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetScrollable(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension width;
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    RefPtr<ResourceObject> widthResObj;
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (jsValue.IsNull() || jsValue->IsUndefined()) {
            return undefinedRes;
        }
        width = Dimension(-1.0, DimensionUnit::VP);
        GetArkUINodeModifiers()->getTabsModifier()->createTabBarWidthWithResourceObj(nativeNode, nullptr);
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width, widthResObj)) {
                GetArkUINodeModifiers()->getTabsModifier()->setTabBarWidth(
                    nativeNode, width.Value(), static_cast<int>(width.Unit()));
                return undefinedRes;
            }
        } else {
            ArkTSUtils::ParseJsDimensionVp(vm, jsValue, width, widthResObj);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarWidth(
            nativeNode, width.Value(), static_cast<int>(width.Unit()));
        GetArkUINodeModifiers()->getTabsModifier()->createTabBarWidthWithResourceObj(
            nativeNode, AceType::RawPtr(widthResObj));
        return undefinedRes;
    }
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, width,
        widthResObj)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarWidth(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarWidth(
        nativeNode, width.Value(), static_cast<int>(width.Unit()));
    auto widthRawPtr = AceType::RawPtr(widthResObj);
    GetArkUINodeModifiers()->getTabsModifier()->createTabBarWidthWithResourceObj(nativeNode, widthRawPtr);
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarWidth(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarWidth(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> jsValue = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> noMinHeightLimitArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    CalcDimension height = Dimension(-1.0, DimensionUnit::VP);
    ArkUINativeModuleValue undefinedRes = panda::JSValueRef::Undefined(vm);

    RefPtr<ResourceObject> heightResObj;
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc < TABS_ARG_INDEX_2) {
            return undefinedRes;
        }
        bool adaptiveHeight = false;
        bool noMinHeightLimit = false;
        if (argc == TABS_ARG_INDEX_3 && !noMinHeightLimitArg.IsNull() && !noMinHeightLimitArg->IsUndefined() &&
            noMinHeightLimitArg->IsBoolean()) {
            noMinHeightLimit = noMinHeightLimitArg->ToBoolean(vm)->Value();
        }
        GetArkUINodeModifiers()->getTabsModifier()->createTabBarHeightWithResourceObj(nativeNode, nullptr);
        if (!jsValue.IsNull() && !jsValue->IsUndefined() && jsValue->IsString(vm) &&
            jsValue->ToString(vm)->ToString(vm) == "auto") {
            adaptiveHeight = true;
        } else if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (!ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height, heightResObj)) {
                height = Dimension(-1.0, DimensionUnit::VP);
            }
        } else {
            ArkTSUtils::ParseJsDimensionVp(vm, jsValue, height, heightResObj);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setBarAdaptiveHeight(nativeNode, adaptiveHeight);
        GetArkUINodeModifiers()->getTabsModifier()->setNoMinHeightLimit(nativeNode, noMinHeightLimit);
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarHeight(
            nativeNode, height.Value(), static_cast<int>(height.Unit()));
        GetArkUINodeModifiers()->getTabsModifier()->createTabBarHeightWithResourceObj(
            nativeNode, AceType::RawPtr(heightResObj));
        return undefinedRes;
    }
    if (jsValue->IsNull() || jsValue->IsUndefined() || !ArkTSUtils::ParseJsDimensionVpNG(vm, jsValue, height,
        heightResObj)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabBarHeight(nativeNode);
        return undefinedRes;
    }

    GetArkUINodeModifiers()->getTabsModifier()->setTabBarHeight(
        nativeNode, height.Value(), static_cast<int>(height.Unit()));
    auto heightRawPtr = AceType::RawPtr(heightResObj);
    GetArkUINodeModifiers()->getTabsModifier()->createTabBarHeightWithResourceObj(nativeNode, heightRawPtr);
    return undefinedRes;
}

ArkUINativeModuleValue TabsBridge::ResetTabBarHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool value = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setBarAdaptiveHeight(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarAdaptiveHeight(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetBarAdaptiveHeight(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimationCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (valueArg->IsString(vm)) {
        std::string curve = valueArg->ToString(vm)->ToString(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setAnimationCurve(nativeNode,
            ANIMATION_CURVE_TYPE_STR, curve.c_str(), nullptr);
    } else if (valueArg->IsObject(vm)) {
        ArkUI_Uint32 type = ANIMATION_CURVE_TYPE_DEFAULT;
        std::string aniTimFunc;
        std::function<float(float)> customCallBack = nullptr;
        GetAnimationCurveInfo(runtimeCallInfo, type, aniTimFunc, customCallBack);
        GetArkUINodeModifiers()->getTabsModifier()->setAnimationCurve(nativeNode,
            type, aniTimFunc.c_str(), reinterpret_cast<void*>(&customCallBack));
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimationCurve(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimationCurve(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimationCurve(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetNoMinHeightLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    bool value = secondArg->ToBoolean(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setNoMinHeightLimit(nativeNode, value);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetNoMinHeightLimit(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetNoMinHeightLimit(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> durationArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        uint32_t argc = runtimeCallInfo->GetArgsNumber();
        if (argc <= TABS_ARG_INDEX_1) {
            GetArkUINodeModifiers()->getTabsModifier()->setAnimationDuration(nativeNode, -1);
            return panda::JSValueRef::Undefined(vm);
        }
        if ((!durationArg.IsNull() && !durationArg->IsUndefined() && !durationArg->IsNumber()) ||
            (durationArg.IsNull() && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
            GetArkUINodeModifiers()->getTabsModifier()->setAnimationDuration(nativeNode, -1);
            return panda::JSValueRef::Undefined(vm);
        }
        float duration = durationArg->IsNumber() ? static_cast<int32_t>(durationArg->ToNumber(vm)->Value()) : 0;
        GetArkUINodeModifiers()->getTabsModifier()->setAnimationDuration(nativeNode, duration);
        return panda::JSValueRef::Undefined(vm);
    }
    if (durationArg->IsNull() || durationArg->IsUndefined()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimationDuration(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    float duration = durationArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setAnimationDuration(nativeNode, duration);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimationDuration(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimationDuration(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        int32_t barVal = DEFAULT_TAB_BAR_POSITION;
        if (runtimeCallInfo->GetArgsNumber() > TABS_ARG_INDEX_1 && !secondArg.IsNull() && !secondArg->IsUndefined() &&
            secondArg->IsNumber()) {
            auto barPositionVal = secondArg->Int32Value(vm);
            if (barPositionVal >= DEFAULT_TAB_BAR_POSITION && barPositionVal <= MAX_TAB_BAR_POSITION) {
                barVal = barPositionVal;
            }
        }
        GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t barVal = secondArg->ToNumber(vm)->Value();
    GetArkUINodeModifiers()->getTabsModifier()->setTabBarPosition(nativeNode, barVal);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetBarPosition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabBarPosition(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> clipArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if ((!clipArg.IsNull() && !clipArg->IsUndefined() && clipArg->IsObject(vm)) ||
            !Container::IsCurrentUseNewPipeline()) {
            CommonBridge::SetClip(runtimeCallInfo);
            return panda::JSValueRef::Undefined(vm);
        }
        if (!clipArg.IsNull() && !clipArg->IsUndefined() && clipArg->IsBoolean()) {
            GetArkUINodeModifiers()->getTabsModifier()->setTabClip(nativeNode, clipArg->ToBoolean(vm)->Value());
        }
        return panda::JSValueRef::Undefined(vm);
    }
    if (!clipArg->IsNull() && !clipArg->IsUndefined() && clipArg->IsObject(vm)) {
        CommonBridge::SetClip(runtimeCallInfo);
    } else if (!clipArg->IsNull() && !clipArg->IsUndefined() && clipArg->IsBoolean()) {
        GetArkUINodeModifiers()->getTabsModifier()->setTabClip(nativeNode, clipArg->ToBoolean(vm)->Value());
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabClip(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabClip(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));

    int32_t effect = static_cast<int32_t>(EdgeEffect::SPRING);
    if (secondArg->IsUndefined() || secondArg->IsNull()) {
        effect = static_cast<int32_t>(EdgeEffect::SPRING);
    } else {
        effect = secondArg->Int32Value(vm);
    }
    if (effect < static_cast<int32_t>(EdgeEffect::SPRING) || effect > static_cast<int32_t>(EdgeEffect::NONE)) {
        effect = static_cast<int32_t>(EdgeEffect::SPRING);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabEdgeEffect(nativeNode, effect);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabEdgeEffect(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabEdgeEffect(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (!valueArg->IsNull() && !valueArg->IsUndefined() &&valueArg->IsNumber()) {
        int32_t index = valueArg->Int32Value(vm);
        int32_t values[1] = { 0 };
        if (index < static_cast<int32_t>(NestedScrollMode::SELF_ONLY) ||
            index > static_cast<int32_t>(NestedScrollMode::SELF_FIRST)) {
                index = 0;
        }
        values[0] = index;
        GetArkUINodeModifiers()->getTabsModifier()->setTabsNestedScroll(nativeNode, &values);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsNestedScroll(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetNestedScroll(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsNestedScroll(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> valueArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        int32_t pageFlipMode = 0;
        if (!valueArg.IsNull() && !valueArg->IsUndefined() && valueArg->IsNumber()) {
            ArkTSUtils::ParseJsInt32(vm, valueArg, pageFlipMode);
        }
        GetArkUINodeModifiers()->getTabsModifier()->setTabPageFlipMode(nativeNode, pageFlipMode);
        return panda::JSValueRef::Undefined(vm);
    }
    if (valueArg->IsNumber()) {
        int32_t pageFlipMode = valueArg->Int32Value(vm);
        GetArkUINodeModifiers()->getTabsModifier()->setTabPageFlipMode(nativeNode, pageFlipMode);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabPageFlipMode(nativeNode);
    }
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabPageFlipMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabPageFlipMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() < TABS_ARG_INDEX_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        CommonBridge::SetWidth(runtimeCallInfo);
        if (!secondArg.IsNull() && !secondArg->IsUndefined() && secondArg->IsString(vm) &&
            secondArg->ToString(vm)->ToString(vm) == "auto") {
            GetArkUINodeModifiers()->getTabsModifier()->setTabWidthAuto(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getTabsModifier()->resetTabWidthAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension width;
    ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, width);
    if (width.Unit() == DimensionUnit::AUTO) {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->setTabWidthAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        CommonBridge::SetWidth(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->resetTabWidthAuto(nativeNode);
    }
    CommonBridge::SetWidth(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetWidthAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetWidth(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabWidthAuto(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() < TABS_ARG_INDEX_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        CommonBridge::SetHeight(runtimeCallInfo);
        if (!secondArg.IsNull() && !secondArg->IsUndefined() && secondArg->IsString(vm) &&
            secondArg->ToString(vm)->ToString(vm) == "auto") {
            GetArkUINodeModifiers()->getTabsModifier()->setTabHeightAuto(nativeNode);
            return panda::JSValueRef::Undefined(vm);
        }
        GetArkUINodeModifiers()->getTabsModifier()->resetTabHeightAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }

    CalcDimension height;
    ArkTSUtils::ParseJsDimensionVpNG(vm, secondArg, height);
    if (height.Unit() == DimensionUnit::AUTO) {
        CommonBridge::SetHeight(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->setTabHeightAuto(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    } else {
        CommonBridge::SetHeight(runtimeCallInfo);
        GetArkUINodeModifiers()->getTabsModifier()->resetTabHeightAuto(nativeNode);
    }
    CommonBridge::SetHeight(runtimeCallInfo);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetHeightAuto(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    CommonBridge::ResetHeight(runtimeCallInfo);
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabHeightAuto(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> animateModeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        uint32_t animateModeValue = static_cast<uint32_t>(TabAnimateMode::CONTENT_FIRST);
        if (!animateModeArg.IsNull() && !animateModeArg->IsUndefined() && animateModeArg->IsNumber()) {
            auto parsedMode = animateModeArg->Uint32Value(vm);
            if (parsedMode < static_cast<uint32_t>(TabAnimateMode::MAX_VALUE)) {
                animateModeValue = parsedMode;
            }
        }
        GetArkUINodeModifiers()->getTabsModifier()->setAnimateMode(nativeNode, animateModeValue);
        return panda::JSValueRef::Undefined(vm);
    }
    if (!animateModeArg->IsNumber()) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    uint32_t animateModeValue = animateModeArg->Uint32Value(vm);
    if (animateModeValue >= static_cast<uint32_t>(TabAnimateMode::MAX_VALUE)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setAnimateMode(nativeNode, animateModeValue);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetAnimateMode(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetAnimateMode(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnSelected(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onSelected callback execute failed.");
            return;
        }
        if (isJsView) {
            ACE_SCORING_EVENT("Tabs.onSelected");
            ACE_SCOPED_TRACE("Tabs.onSelected index %d", tabsInfo->GetIndex());
        }
        panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, tabsInfo->GetIndex());
        panda::Local<panda::JSValueRef> params[1] = { indexParam }; // 1: Array length
        auto result = func->Call(vm, func.ToLocal(), params, 1); // 1: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnSelected(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnSelected(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnSelected(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetCachedMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> countArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    Local<JSValueRef> modeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_2);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    if (ArkTSUtils::IsJsView(firstArg, vm)) {
        if (runtimeCallInfo->GetArgsNumber() < TABS_ARG_INDEX_2) {
            return panda::JSValueRef::Undefined(vm);
        }
        std::optional<int32_t> count;
        if (!countArg.IsNull() && !countArg->IsUndefined() && countArg->IsNumber()) {
            auto parsedCount = countArg->Int32Value(vm);
            if (parsedCount >= 0) {
                count = parsedCount;
            }
        }
        int32_t mode = DEFAULT_TABS_CACHE_MODE;
        if (!modeArg.IsNull() && !modeArg->IsUndefined() && modeArg->IsNumber()) {
            auto parsedMode = modeArg->Int32Value(vm);
            if (parsedMode >= DEFAULT_TABS_CACHE_MODE && parsedMode <= MAX_TABS_CACHE_MODE) {
                mode = parsedMode;
            }
        }
        if (count.has_value()) {
            GetArkUINodeModifiers()->getTabsModifier()->setCachedMaxCount(nativeNode, count.value(), mode);
        } else {
            GetArkUINodeModifiers()->getTabsModifier()->resetCachedMaxCount(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    int32_t count = 0;
    if (countArg->IsNumber() && countArg->Int32Value(vm) >= 0) {
        count = countArg->Int32Value(vm);
    } else {
        GetArkUINodeModifiers()->getTabsModifier()->resetCachedMaxCount(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t mode = 0;
    if (modeArg->IsNumber()) {
        mode = modeArg->Int32Value(vm);
    }
    GetArkUINodeModifiers()->getTabsModifier()->setCachedMaxCount(nativeNode, count, mode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetCachedMaxCount(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::NativePointerRef::New(vm, nullptr));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetCachedMaxCount(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::SetTabsOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(const BaseEventInfo* info)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onChange callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChange");
        ACE_SCOPED_TRACE("Tabs.onChange index %d", tabsInfo->GetIndex());
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, tabsInfo->GetIndex()) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnChange(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnTabBarClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnTabBarClick(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(const BaseEventInfo* info)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView](const BaseEventInfo* info) {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "Tabs onTabBarClick callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onTabBarClick");
        PipelineContext::SetCallBackNode(frameWeakNode);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, tabsInfo->GetIndex()) };
        auto result = func->Call(vm, func.ToLocal(), params, 1);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                "event", "Tabs.onTabBarClick", ComponentEventType::COMPONENT_EVENT_SWIPER);
        }
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnTabBarClick(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnTabBarClick(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnTabBarClick(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationStart(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, int32_t, const AnimationCallbackInfo&)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), isJsView](
            int32_t index, int32_t targetIndex, const AnimationCallbackInfo& extraInfo) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(frameWeakNode);
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            panda::Local<panda::NumberRef> targetIndexParam = panda::NumberRef::New(vm, targetIndex);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, extraInfo.currentOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, extraInfo.targetOffset.value_or(0.0f)),
                panda::NumberRef::New(vm, extraInfo.velocity.value_or(0.0f)) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[3] = { indexParam, targetIndexParam,
                eventObject };                         // 3: Array length
            auto result = func->Call(vm, func.ToLocal(), params, 3); // 3: Array length
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnAnimationStart(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}
ArkUINativeModuleValue TabsBridge::ResetTabsOnAnimationStart(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationStart(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsUndefined() || callbackArg->IsNull() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationEnd(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), isJsView](
        int32_t index, const AnimationCallbackInfo& extraInfo) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(frameWeakNode);
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            float current = extraInfo.currentOffset.value_or(0.0f);
            float target = isJsView ? extraInfo.targetOffset.value_or(0.0f) : 0;
            float velocity = isJsView ? extraInfo.velocity.value_or(0.0f) : 0;

            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, current), panda::NumberRef::New(vm, target),
                panda::NumberRef::New(vm, velocity) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
            auto result = func->Call(vm, func.ToLocal(), params, 2);                 // 2: Array length
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
                UiSessionManager::GetInstance()->ReportComponentChangeEvent(
                    "event", "Tabs.onAnimationEnd", ComponentEventType::COMPONENT_EVENT_SWIPER);
            }
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnAnimationEnd(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnAnimationEnd(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnAnimationEnd(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnGestureSwipe(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);

    std::function<void(int32_t, const AnimationCallbackInfo&)> callback =
        [frameWeakNode = AceType::WeakClaim(frameNode), func = panda::CopyableGlobal(vm, func), isJsView](
        int32_t index, const AnimationCallbackInfo& extraInfo) {
            auto vm = func.GetEcmaVM();
            panda::LocalScope pandaScope(vm);
            panda::TryCatch trycatch(vm);
            PipelineContext::SetCallBackNode(frameWeakNode);
            panda::Local<panda::NumberRef> indexParam = panda::NumberRef::New(vm, index);
            const char* keys[] = { "currentOffset", "targetOffset", "velocity" };
            if (isJsView) {
                ACE_SCORING_EVENT("Tabs.onGestureSwipe");
            }
            float current = extraInfo.currentOffset.value_or(0.0f);
            float target = isJsView ? extraInfo.targetOffset.value_or(0.0f) : 0;
            float velocity = isJsView ? extraInfo.velocity.value_or(0.0f) : 0;
            Local<JSValueRef> values[] = { panda::NumberRef::New(vm, current), panda::NumberRef::New(vm, target),
                panda::NumberRef::New(vm, velocity) };
            auto eventObject = panda::ObjectRef::NewWithNamedProperties(vm, ArraySize(keys), keys, values);
            panda::Local<panda::JSValueRef> params[2] = { indexParam, eventObject }; // 2: Array length
            auto result = func->Call(vm, func.ToLocal(), params, 2);                 // 2: Array length
            if (isJsView) {
                ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
            }
        };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnGestureSwipe(nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnGestureSwipe(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnGestureSwipe(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsOnContentWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    Local<JSValueRef> callbackArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    auto frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    if (callbackArg->IsNull() || callbackArg->IsUndefined() || !callbackArg->IsFunction(vm)) {
        if (!isJsView) {
            GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentWillChange(nativeNode);
        }
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::FunctionRef> func = callbackArg->ToObject(vm);
    std::function<bool(int32_t, int32_t)> callback = [frameWeakNode = AceType::WeakClaim(frameNode),
        func = panda::CopyableGlobal(vm, func), isJsView](int32_t currentIndex, int32_t comingIndex) -> bool {
        auto vm = func.GetEcmaVM();
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        PipelineContext::SetCallBackNode(frameWeakNode);
        if (isJsView) {
            ACE_SCORING_EVENT("Tabs.onContentWillChange");
        }

        panda::Local<panda::NumberRef> currentIndexParam = panda::NumberRef::New(vm, currentIndex);
        panda::Local<panda::NumberRef> comingIndexParam = panda::NumberRef::New(vm, comingIndex);
        // 2: Array length
        panda::Local<panda::JSValueRef> params[2] = { currentIndexParam, comingIndexParam };
        auto result = func->Call(vm, func.ToLocal(), params, 2); // 2: Array length
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
        }
        if (result->IsBoolean()) {
            return result->ToBoolean(vm)->Value();
        }
        return isJsView ? true : false;
    };
    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnContentWillChange(
        nativeNode, reinterpret_cast<void*>(&callback));
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsOnContentWillChange(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsOnContentWillChange(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::SetTabsCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    bool isJsView = ArkTSUtils::IsJsView(firstArg, vm);
    if (runtimeCallInfo->GetArgsNumber() != 2) { // 2: Array length
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> transitionArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (transitionArg->IsNull() || transitionArg->IsUndefined() || !transitionArg->IsFunction(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsIsCustomAnimation(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    ParseCustomContentTransition(vm, nativeNode, transitionArg, isJsView);

    GetArkUINodeModifiers()->getTabsModifier()->setTabsIsCustomAnimation(nativeNode, true);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsCustomContentTransition(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> nodeArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(nodeArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(nodeArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsIsCustomAnimation(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}

void TabsBridge::ParseCustomContentTransition(
    EcmaVM* vm, ArkUINodeHandle nativeNode, const Local<JSValueRef>& transitionFunc, bool isJsView)
{
    panda::Local<panda::FunctionRef> funcRef = transitionFunc->ToObject(vm);
    TabsCustomAnimationEvent onCustomAnimation = [vm, func = panda::CopyableGlobal(vm, funcRef), isJsView](
                                                     int32_t from, int32_t to) -> TabContentAnimatedTransition {
        TabContentAnimatedTransition transitionInfo;
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        Local<JSValueRef> params[2] = { panda::NumberRef::New(vm, from), panda::NumberRef::New(vm, to) };
        auto ret = func->Call(vm, func.ToLocal(), params, 2);
        if (isJsView) {
            ArkTSUtils::HandleCallbackJobs(vm, trycatch, ret);
        }
        if (ret->IsNull() || ret->IsUndefined() || !ret->IsObject(vm)) {
            return transitionInfo;
        }

        auto transitionObj = ret->ToObject(vm);
        auto timeoutProperty = ArkTSUtils::GetProperty(vm, transitionObj, "timeout");
        transitionInfo.timeout = DEFAULT_CUSTOM_ANIMATION_TIMEOUT;
        if (!timeoutProperty->IsNull() && !timeoutProperty->IsUndefined() && timeoutProperty->IsNumber()) {
            auto timeout = timeoutProperty->Int32Value(vm);
            transitionInfo.timeout = timeout < 0 ? DEFAULT_CUSTOM_ANIMATION_TIMEOUT : timeout;
        }

        auto transition = ArkTSUtils::GetProperty(vm, transitionObj, "transition");
        if (!transition->IsNull() && !transition->IsUndefined() && transition->IsFunction(vm)) {
            panda::Local<panda::FunctionRef> transitionFuncRef = transition->ToObject(vm);
            auto onTransition = [vm, func = panda::CopyableGlobal(vm, transitionFuncRef), isJsView](
                                    const RefPtr<TabContentTransitionProxy>& proxy) {
                ACE_SCORING_EVENT("onTransition");
                panda::LocalScope pandaScope(vm);
                panda::TryCatch trycatch(vm);
                auto proxyObj = CreateTabContentTransitionProxyObject(vm, proxy);
                Local<JSValueRef> params[1] = { proxyObj };
                auto result = func->Call(vm, func.ToLocal(), params, 1);
                if (isJsView) {
                    ArkTSUtils::HandleCallbackJobs(vm, trycatch, result);
                }
            };

            transitionInfo.transition = std::move(onTransition);
        }

        return transitionInfo;
    };

    GetArkUINodeModifiers()->getTabsModifier()->setTabsOnCustomAnimation(nativeNode, &onCustomAnimation);
}

std::optional<Dimension> TabsBridge::ParseBarFloatingDimension(
    EcmaVM* vm, Local<JSValueRef> value, RefPtr<ResourceObject>& resObj)
{
    CalcDimension dimension;
    auto parseOk = ArkTSUtils::ParseJsDimensionVp(vm, value, dimension, resObj);
    if (parseOk) {
        return dimension;
    } else {
        return std::nullopt;
    }
    return dimension;
}

ArkUINativeModuleValue TabsBridge::SetTabsBarFloatingStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    ArkUINodeHandle nativeNode = nullptr;
    CHECK_NE_RETURN(ArkTSUtils::GetNativeNode(nativeNode, firstArg, vm), true, panda::JSValueRef::Undefined(vm));
    auto* frameNode = reinterpret_cast<FrameNode*>(nativeNode);
    using namespace OHOS::Ace::Framework;
    CHECK_NULL_RETURN(frameNode, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> param = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_1);
    if (!param->IsObject(vm)) {
        GetArkUINodeModifiers()->getTabsModifier()->resetTabsBarFloatingStyle(nativeNode);
        return panda::JSValueRef::Undefined(vm);
    }
    BarFloatingStyleParameters parameters;
    auto paramObject = param->ToObject(vm);

    RefPtr<ResourceObject> smallBarWidthObj;
    RefPtr<ResourceObject> mediumBarWidthObj;
    RefPtr<ResourceObject> largeBarWidthObj;
    RefPtr<ResourceObject> barSideMarginObj;
    RefPtr<ResourceObject> barBottomMarginObj;
    RefPtr<ResourceObject> maskColorObj;
    RefPtr<ResourceObject> maskHeightObj;

    auto barWidthVal = ArkTSUtils::GetProperty(vm, paramObject, "barWidth");
    if (barWidthVal->IsObject(vm)) {
        auto barWidthObject = barWidthVal->ToObject(vm);
        parameters.smallBarWidth = ParseBarFloatingDimension(
            vm, ArkTSUtils::GetProperty(vm, barWidthObject, "smallBarWidth"), smallBarWidthObj);
        parameters.mediumBarWidth = ParseBarFloatingDimension(
            vm, ArkTSUtils::GetProperty(vm, barWidthObject, "mediumBarWidth"), mediumBarWidthObj);
        parameters.largeBarWidth = ParseBarFloatingDimension(
            vm, ArkTSUtils::GetProperty(vm, barWidthObject, "largeBarWidth"), largeBarWidthObj);
    }

    parameters.barSideMargin =
        ParseBarFloatingDimension(vm, ArkTSUtils::GetProperty(vm, paramObject, "barSideMargin"), barSideMarginObj);
    parameters.barBottomMargin =
        ParseBarFloatingDimension(vm, ArkTSUtils::GetProperty(vm, paramObject, "barBottomMargin"), barBottomMarginObj);
    Color colorVal;
    auto nodeInfo = ArkTSUtils::MakeNativeNodeInfo(nativeNode);
    bool parseOk = ArkTSUtils::ParseJsColorAlpha(
        vm, ArkTSUtils::GetProperty(vm, paramObject, "maskColor"), colorVal, maskColorObj, nodeInfo);
    if (parseOk) {
        parameters.maskColor = colorVal;
    } else {
        parameters.maskColor = std::nullopt;
    }
    parameters.maskHeight =
        ParseBarFloatingDimension(vm, ArkTSUtils::GetProperty(vm, paramObject, "maskHeight"), maskHeightObj);

    if (ArkTSUtils::GetProperty(vm, paramObject, "adaptToHandedness")->IsBoolean()) {
        parameters.adaptToHandedness =
            ArkTSUtils::GetProperty(vm, paramObject, "adaptToHandedness")->ToBoolean(vm)->Value();
    }

    auto systemMaterialVal = ArkTSUtils::GetProperty(vm, paramObject, "systemMaterial");
    const auto* material = CreateUiMaterialFromNativeValue(vm, systemMaterialVal);
    if (material) {
        parameters.systemMaterial = material->Copy();
    }

    if (SystemProperties::ConfigChangePerform()) {
        parameters.smallBarWidthObject = smallBarWidthObj;
        parameters.mediumBarWidthObject = mediumBarWidthObj;
        parameters.largeBarWidthObject = largeBarWidthObj;
        parameters.barSideMarginObject = barSideMarginObj;
        parameters.barBottomMarginObject = barBottomMarginObj;
        parameters.maskColorObject = maskColorObj;
        parameters.maskHeightObject = maskHeightObj;
    }
    GetArkUINodeModifiers()->getTabsModifier()->setTabsBarFloatingStyle(nativeNode, &parameters);
    return panda::JSValueRef::Undefined(vm);
}

ArkUINativeModuleValue TabsBridge::ResetTabsBarFloatingStyle(ArkUIRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    CHECK_NULL_RETURN(vm, panda::JSValueRef::Undefined(vm));
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(TABS_ARG_INDEX_0);
    CHECK_NULL_RETURN(firstArg->IsNativePointer(vm), panda::JSValueRef::Undefined(vm));
    auto nativeNode = nodePtr(firstArg->ToNativePointer(vm)->Value());
    GetArkUINodeModifiers()->getTabsModifier()->resetTabsBarFloatingStyle(nativeNode);
    return panda::JSValueRef::Undefined(vm);
}
} // namespace OHOS::Ace::NG

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

#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_view_register.h"

#include "base/error/error_code.h"
#include "base/geometry/ng/size_t.h"
#include "base/i18n/localization.h"
#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/card_frontend/card_frontend_declarative.h"
#include "bridge/card_frontend/form_frontend_declarative.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/declarative_frontend/declarative_frontend.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/engine/js_object_template.h"
#include "bridge/declarative_frontend/engine/jsi/nativeModule/arkts_native_api_bridge.h"
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "bridge/declarative_frontend/jsview/canvas/js_canvas_image_data.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/card_scope.h"
#include "core/components/container_modal/container_modal_constants.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_container_app_bar_register.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_container_modal_view_register.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/jsi_object_template.h"

namespace OHOS::Ace::Framework {
namespace {
static constexpr uint32_t PARAM_SIZE_ONE   = 1;
static constexpr uint32_t PARAM_SIZE_TWO   = 2;
static constexpr uint32_t PARAM_SIZE_THREE = 3;
static constexpr uint32_t PARAM_TRHEE_INDEX = 2;
constexpr int FUNC_SET_CREATE_ARG_LEN = 2;
}

JSRef<JSVal> CreateJsObjectFromJsonValue(const EcmaVM* vm, const std::unique_ptr<JsonValue>& jsonValue)
{
    if (jsonValue->IsBool()) {
        return JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, jsonValue->GetBool()));
    } else if (jsonValue->IsNumber()) {
        return JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, jsonValue->GetDouble()));
    } else if (jsonValue->IsString()) {
        return JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, jsonValue->GetString()));
    } else if (jsonValue->IsArray()) {
        JSRef<JSArray> array = JSRef<JSArray>::New();
        int32_t size = jsonValue->GetArraySize();
        for (int32_t i = 0; i < size; ++i) {
            std::unique_ptr<JsonValue> item = jsonValue->GetArrayItem(i);
            array->SetValueAt(i, CreateJsObjectFromJsonValue(vm, item));
        }
        return array;
    } else if (jsonValue->IsObject()) {
        JSRef<JSObject> object = JSRef<JSObject>::New();
        std::unique_ptr<JsonValue> child = jsonValue->GetChild();
        while (child && child->IsValid()) {
            const std::string& key = child->GetKey();
            object->SetPropertyObject(key.c_str(), CreateJsObjectFromJsonValue(vm, child));
            child = child->GetNext();
        }
        return object;
    } else if (jsonValue->IsNull()) {
        return JSRef<JSVal>::Make(panda::JSValueRef::Null(vm));
    } else {
        return JSRef<JSVal>::Make(panda::JSValueRef::Undefined(vm));
    }
}

void RegisterCardUpdateCallback(int64_t cardId, const panda::Local<panda::ObjectRef>& obj)
{
    JSRef<JSObject> object = JSRef<JSObject>::Make(obj);
    JSRef<JSVal> storageValue = object->GetProperty("localStorage_");
    if (!storageValue->IsObject()) {
        return;
    }

    JSRef<JSObject> storage = JSRef<JSObject>::Cast(storageValue);
    JSRef<JSVal> setOrCreateVal = storage->GetProperty("setOrCreate");
    if (!setOrCreateVal->IsFunction()) {
        return;
    }

    JSRef<JSFunc> setOrCreate = JSRef<JSFunc>::Cast(setOrCreateVal);
    auto id = ContainerScope::CurrentId();
    auto callback = [storage, setOrCreate, id](const std::string& data) {
        ContainerScope scope(id);
        const EcmaVM* vm = storage->GetEcmaVM();
        CHECK_NULL_VOID(vm);
        TAG_LOGI(AceLogTag::ACE_FORM, "setOrCreate, dataList length: %{public}zu", data.length());
        std::unique_ptr<JsonValue> jsonRoot = JsonUtil::ParseJsonString(data);
        CHECK_NULL_VOID(jsonRoot);
        auto child = jsonRoot->GetChild();
        if (!child || !child->IsValid()) {
            return;
        }

        while (child && child->IsValid()) {
            const std::string& key = child->GetKey();
            JSRef<JSVal> args[] = {
                JSRef<JSVal>::Make(JsiValueConvertor::toJsiValueWithVM(vm, key)),
                CreateJsObjectFromJsonValue(vm, child),
            };
            setOrCreate->Call(storage, FUNC_SET_CREATE_ARG_LEN, args);
            child = child->GetNext();
        }
    };

    auto container = Container::Current();
    if (container->IsFRSCardContainer() || container->IsDynamicRender()) {
        auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_VOID(frontEnd);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->SetUpdateCardDataCallback(callback);
        delegate->UpdatePageDataImmediately();
    } else {
        auto frontEnd = AceType::DynamicCast<CardFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_VOID(frontEnd);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->SetUpdateCardDataCallback(callback);
        delegate->UpdatePageDataImmediately();
    }
}

void SetFormCallbacks(RefPtr<Container> container, JSView* view)
{
    auto pipeline = container->GetPipelineContext();
    if (pipeline != nullptr) {
        pipeline->SetOnFormRecycleCallback([weak = Referenced::WeakClaim(view)]() {
            auto view = weak.Upgrade();
            std::string statusData;
            if (view) {
                statusData = view->FireOnFormRecycle();
            } else {
                LOGE("view is null");
            }
            return statusData;
        });

        pipeline->SetOnFormRecoverCallback([weak = Referenced::WeakClaim(view)](const std::string& statusData) {
            auto view = weak.Upgrade();
            if (view) {
                view->FireOnFormRecover(statusData);
            } else {
                LOGE("view is null");
            }
        });
    } else {
        LOGE("execute SetOnFormRecycleCallback and SetOnFormRecoverCallback failed due to pipeline is null");
    }
}

void UpdatePageLifeCycleFunctions(RefPtr<NG::FrameNode> pageNode, JSView* view)
{
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->SetOnPageShow([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnShow();
        }
    });
    pagePattern->SetOnPageHide([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            view->FireOnHide();
        }
    });
    pagePattern->SetOnBackPressed([weak = Referenced::WeakClaim(view)]() {
        auto view = weak.Upgrade();
        if (view) {
            return view->FireOnBackPress();
        }
        return false;
    });
}

void UpdateCardRootComponent(const EcmaVM* vm, const panda::Local<panda::ObjectRef>& obj)
{
    auto* view = JsiObjectTemplate::GetNativeView(obj, vm);
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return;
    }

    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        // Set Partial Update
        Container::SetCurrentUsePartialUpdate(!view->isFullUpdate());

        auto cardId = CardScope::CurrentId();
        view->SetCardId(cardId);

        RegisterCardUpdateCallback(cardId, obj);

        RefPtr<NG::PageRouterManager> pageRouterManager;

        if (container->IsFRSCardContainer() || container->IsDynamicRender()) {
            auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_VOID(frontEnd);
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_VOID(delegate);
            pageRouterManager = delegate->GetPageRouterManager();
        } else {
            auto frontEnd = AceType::DynamicCast<CardFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_VOID(frontEnd);
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_VOID(delegate);
            pageRouterManager = delegate->GetPageRouterManager();
        }
        CHECK_NULL_VOID(pageRouterManager);
        auto pageNode = pageRouterManager->GetCurrentPageNode();
        CHECK_NULL_VOID(pageNode);

        auto pageRootNode = AceType::DynamicCast<NG::UINode>(view->CreateViewNode());
        CHECK_NULL_VOID(pageRootNode);
        pageRootNode->MountToParent(pageNode);

        SetFormCallbacks(container, view);
        UpdatePageLifeCycleFunctions(pageNode, view);
    }
}

panda::Local<panda::JSValueRef> JsLoadDocument(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    LocalScope scope(vm);
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (container && container->IsDynamicRender()) {
        LOGD("load dynamic component card");
        panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
        UpdateCardRootComponent(vm, obj);
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Global<panda::ObjectRef> obj(vm, Local<panda::ObjectRef>(firstArg));
    JsiDeclarativeEngine::SetEntryObject(obj);
#if defined(PREVIEW)
    panda::Global<panda::ObjectRef> rootView(vm, obj->ToObject(vm));
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    arkRuntime->AddRootView(rootView);
#endif

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsRegisterNamedRoute(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    // will need three arguments
    if (argc != 3) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsFunction(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
#ifdef DYNAMIC_COMPONENT_SUPPORT
    auto container = Container::Current();
    if (container && container->IsDynamicRender()) {
        LOGD("load dynamic component card through named route");
        panda::Local<panda::FunctionRef> objSupplier = firstArg;
        std::vector<Local<JSValueRef>> argv;
        auto obj = objSupplier->Call(vm, JSNApi::GetGlobalObject(vm), argv.data(), 0);
        UpdateCardRootComponent(vm, obj->ToObject(vm));
        return panda::JSValueRef::Undefined(vm);
    }
#endif
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    if (!thirdArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    JsiDeclarativeEngine::AddToNamedRouterMap(vm,
        panda::Global<panda::FunctionRef>(vm, Local<panda::FunctionRef>(firstArg)),
        secondArg->ToString(vm)->ToString(vm), thirdArg->ToObject(vm));

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsNavigationRegister(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM *vm = runtimeCallInfo->GetVM();
    auto argsNum = runtimeCallInfo->GetArgsNumber();
    const uint8_t maxArgSize = 2;
    if (argsNum != maxArgSize) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "builder param is invalid: argsNum: %{public}d", argsNum);
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> nameProp = runtimeCallInfo->GetCallArgRef(0);
    if (!nameProp->IsString(vm)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "name is invalid");
        return panda::JSValueRef::Undefined(vm);
    }
    std::string name = nameProp->ToString(vm)->ToString(vm);
    Local<JSValueRef> builderProp = runtimeCallInfo->GetCallArgRef(1);
    if (!builderProp->IsObject(vm)) {
        TAG_LOGE(AceLogTag::ACE_NAVIGATION, "get builder object failed: %{public}s", name.c_str());
        return panda::JSValueRef::Undefined(vm);
    }
    JsiDeclarativeEngine::AddToNavigationBuilderMap(name,
        panda::Global<panda::ObjectRef>(vm, Local<panda::ObjectRef>(builderProp)));
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JSPostCardAction(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
#if defined(PREVIEW)
    LOGW("[Engine Log] The postCardAction interface in the Previewer is a mocked implementation and"
"may behave differently than an real device.");
    return panda::JSValueRef::Undefined(vm);
#endif
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc > 2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    auto* view = JsiObjectTemplate::GetNativeView(obj, vm);
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto value = panda::JSON::Stringify(vm, secondArg);
    if (!value->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto valueStr = panda::Local<panda::StringRef>(value);
    auto action = valueStr->ToString(vm);

#if !defined(NG_BUILD)
    int64_t cardId = view->GetCardId();
    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        if (container->IsFRSCardContainer()) {
            auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_RETURN(frontEnd, panda::JSValueRef::Undefined(vm));
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_RETURN(delegate, panda::JSValueRef::Undefined(vm));
            delegate->FireCardAction(action);
        } else {
            auto frontEnd = AceType::DynamicCast<CardFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_RETURN(frontEnd, panda::JSValueRef::Undefined(vm));
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_RETURN(delegate, panda::JSValueRef::Undefined(vm));
            delegate->FireCardAction(action);
        }
    }
#endif
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsLoadEtsCard(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc > 2) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    UpdateCardRootComponent(vm, obj);

    return panda::JSValueRef::Undefined(vm);
}

#if defined(PREVIEW)
panda::Local<panda::JSValueRef> JsPreviewerComponent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    std::string requiredComponentName = arkRuntime->GetRequiredComponent();
    panda::Global<panda::ObjectRef> obj = arkRuntime->GetPreviewComponent(vm, requiredComponentName);
    if (obj->IsUndefined()) {
        return panda::JSValueRef::Undefined(vm);
    }
    UpdateRootComponent(vm, obj.ToLocal());

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetPreviewComponentFlag(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    bool isComponentPreview = arkRuntime->GetPreviewFlag();
    if (!isComponentPreview) {
        return panda::JSValueRef::False(vm);
    }
    return panda::JSValueRef::True(vm);
}

panda::Local<panda::JSValueRef> JsStorePreviewComponents(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<NumberRef> componentNum = firstArg->ToNumber(vm);
    uint32_t numOfComponent = componentNum->Value();
    for (uint32_t index = 1; index <= numOfComponent * 2; index++) { // 2: each component pass two args, name and itself
        Local<JSValueRef> componentName = runtimeCallInfo->GetCallArgRef(index);
        if (!componentName->IsString(vm)) {
            return panda::JSValueRef::Undefined(vm);
        }
        std::string name = componentName->ToString(vm)->ToString(vm);
        Local<JSValueRef> componentObj = runtimeCallInfo->GetCallArgRef(++index);
        if (componentObj->IsUndefined()) {
            return panda::JSValueRef::Undefined(vm);
        }
        panda::Global<panda::ObjectRef> obj(vm, componentObj->ToObject(vm));
        arkRuntime->AddPreviewComponent(name, obj);
    }

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetRootView(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return arkRuntime->GetRootView().ToLocal();
}
#endif

panda::Local<panda::JSValueRef> JsDumpMemoryStats(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetI18nResource(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    if (argc != 2 && argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    std::vector<std::string> splitStr;
    std::string str = firstArg->ToString(vm)->ToString(vm);
    StringUtils::SplitStr(str, ".", splitStr);
    if (splitStr.size() != 2) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto targetStringKey = splitStr[0];
    auto targetStringKeyValue = splitStr[1];
    auto resultStrJson = JsiDeclarativeEngineInstance::GetI18nStringResource(targetStringKey, targetStringKeyValue);
    auto resultStr = resultStrJson->GetString();
    if (argc == 1) {
        return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
    }

    panda::LocalScope scope(vm);
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (secondArg->IsArray(vm)) {
        auto arrayVal = panda::Local<panda::ArrayRef>(secondArg);
        auto len = arrayVal->Length(vm);
        std::vector<std::string> arrayResult;
        for (auto i = 0U; i < len; i++) {
            auto subItemVal = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
            if (!subItemVal->IsString(vm)) {
                arrayResult.emplace_back(std::string());
                continue;
            }
            auto itemVal = panda::Local<panda::StringRef>(subItemVal);
            arrayResult.emplace_back(itemVal->ToString(vm));
        }
        ReplacePlaceHolderArray(resultStr, arrayResult);
    } else if (secondArg->IsObject(vm)) {
        auto value = panda::JSON::Stringify(vm, secondArg);
        if (value->IsString(vm)) {
            auto valueStr = panda::Local<panda::StringRef>(value);
            std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(valueStr->ToString(vm));
            ReplacePlaceHolder(resultStr, argsPtr);
        }
    } else if (secondArg->IsNumber()) {
        double count = secondArg->ToNumber(vm)->Value();
        auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
        if (!pluralChoice.empty()) {
            resultStr = ParserPluralResource(resultStrJson, pluralChoice, str);
        }
    }

    return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
}

panda::Local<panda::JSValueRef> JsGetMediaResource(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    std::string targetMediaFileName = firstArg->ToString(vm)->ToString(vm);
    std::string filePath = JsiDeclarativeEngineInstance::GetMediaResource(targetMediaFileName);
    return panda::StringRef::NewFromUtf8(vm, filePath.c_str());
}

RefPtr<FrontendDelegate> JsGetFrontendDelegate()
{
    auto engine = EngineHelper::GetEngine(Container::CurrentId());
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        return nullptr;
    }
    return engineInstance->GetDelegate();
}

panda::Local<panda::JSValueRef> JsGetInspectorNodes(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    auto nodeInfos = accessibilityManager->DumpComposedElementsToJson();
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos->ToString().c_str()));
}

panda::Local<panda::JSValueRef> JsGetInspectorNodeById(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = OHOS::Ace::AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    if (!accessibilityManager) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = firstArg->Int32Value(vm);
    auto nodeInfo = accessibilityManager->DumpComposedElementToJson(intValue);
    if (nodeInfo == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfo->ToString().c_str()));
}

panda::Local<panda::JSValueRef> JsGetInspectorTree(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }

    if (container->IsUseNewPipeline()) {
        auto nodeInfos = NG::Inspector::GetInspector(false);
        return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str()));
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeInfos = V2::Inspector::GetInspectorTree(pipelineContext);
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str()));
#else
    return panda::JSValueRef::Undefined(vm);
#endif
}

panda::Local<panda::JSValueRef> JsGetFilteredInspectorTree(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto container = Container::Current();
    if (!container) {
        LOGE("container is null");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (argc > PARAM_SIZE_ONE) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param count");
        return panda::StringRef::NewFromUtf8(vm, "");
    }

    NG::InspectorFilter filter;
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc == PARAM_SIZE_ONE) {
        if (!firstArg->IsArray(vm)) {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
            return panda::StringRef::NewFromUtf8(vm, "");
        }
        auto arrayVal = panda::Local<panda::ArrayRef>(firstArg);
        auto len = arrayVal->Length(vm);
        for (auto i = 0U; i < len; i++) {
            auto subItemVal = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
            if (!subItemVal->IsString(vm)) {
                JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
                return panda::StringRef::NewFromUtf8(vm, "");
            }
            auto itemVal = panda::Local<panda::StringRef>(subItemVal);
            filter.AddFilterAttr(itemVal->ToString(vm));
        }
    }
    bool needThrow = false;
    auto nodeInfos = NG::Inspector::GetInspector(false, filter, needThrow);
    if (needThrow) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "get inspector failed");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    return panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str());
}

panda::Local<panda::JSValueRef> JsGetFilteredInspectorTreeById(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto container = Container::Current();
    if (!container) {
        LOGE("container is null");
        return panda::StringRef::NewFromUtf8(vm, "");
    }

    auto argc = runtimeCallInfo->GetArgsNumber();
    if (argc < PARAM_SIZE_TWO || argc > PARAM_SIZE_THREE) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param count");
        return panda::StringRef::NewFromUtf8(vm, "");
    }

    NG::InspectorFilter filter;
    // get component id
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString(vm)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    std::string key = firstArg->ToString(vm)->ToString(vm);
    filter.SetFilterID(key);

    // get depth
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    int32_t depth = secondArg->Int32Value(vm);
    if (depth < 0) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid filter depth");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    filter.SetFilterDepth(depth);

    // get inspecotr filter list
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(PARAM_TRHEE_INDEX);
    if (argc == PARAM_SIZE_THREE) {
        if (!thirdArg->IsArray(vm)) {
            JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
            return panda::StringRef::NewFromUtf8(vm, "");
        }
        auto arrayVal = panda::Local<panda::ArrayRef>(thirdArg);
        auto len = arrayVal->Length(vm);
        for (auto i = 0U; i < len; i++) {
            auto subItemVal = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
            if (!subItemVal->IsString(vm)) {
                JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "invalid param type");
                return panda::StringRef::NewFromUtf8(vm, "");
            }
            auto itemVal = panda::Local<panda::StringRef>(subItemVal);
            filter.AddFilterAttr(itemVal->ToString(vm));
        }
    }
    bool needThrow = false;
    auto nodeInfos = NG::Inspector::GetInspector(false, filter, needThrow);
    if (needThrow) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "get inspector failed");
        return panda::StringRef::NewFromUtf8(vm, "");
    }
    return panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str());
}

panda::Local<panda::JSValueRef> JsGetInspectorByKey(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string key = firstArg->ToString(vm)->ToString(vm);
    if (container->IsUseNewPipeline()) {
        auto resultStr = NG::Inspector::GetInspectorNodeByKey(key);
        return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto resultStr = V2::Inspector::GetInspectorNodeByKey(pipelineContext, key);
    return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
#else
    return panda::JSValueRef::Undefined(vm);
#endif
}

panda::Local<panda::JSValueRef> JsSendEventByKey(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 3 || !firstArg->IsString(vm)) { // 3: arg numbers
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }

    std::string key = firstArg->ToString(vm)->ToString(vm);
    auto action = runtimeCallInfo->GetCallArgRef(1)->Int32Value(vm);
    auto params = runtimeCallInfo->GetCallArgRef(2)->ToString(vm)->ToString(vm);
    if (container->IsUseNewPipeline()) {
        auto result = NG::Inspector::SendEventByKey(key, action, params);
        return panda::BooleanRef::New(vm, result);
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto result = V2::Inspector::SendEventByKey(pipelineContext, key, action, params);
    return panda::BooleanRef::New(vm, result);
#else
    return panda::JSValueRef::Undefined(vm);
#endif
}

static TouchEvent GetTouchPointFromJS(const JsiObject& value)
{
    TouchEvent touchPoint;

    auto type = value->GetProperty("type");
    touchPoint.type = static_cast<TouchType>(type->ToNumber<int32_t>());

    auto id = value->GetProperty("id");
    touchPoint.id = id->ToNumber<int32_t>();

    auto x = value->GetProperty("x");
    touchPoint.x = x->ToNumber<float>();

    auto y = value->GetProperty("y");
    touchPoint.y = y->ToNumber<float>();

    touchPoint.time = std::chrono::high_resolution_clock::now();

    return touchPoint;
}

panda::Local<panda::JSValueRef> JsSendTouchEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    TouchEvent touchPoint = GetTouchPointFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, touchPoint]() { pipelineContext->OnTouchEvent(touchPoint); },
        TaskExecutor::TaskType::UI, "ArkUIJsSendTouchEvent");
    return panda::BooleanRef::New(vm, result);
}

static KeyEvent GetKeyEventFromJS(const JsiObject& value)
{
    auto type = value->GetProperty("type");
    auto action = static_cast<KeyAction>(type->ToNumber<int32_t>());

    auto jsKeyCode = value->GetProperty("keyCode");
    auto code = static_cast<KeyCode>(jsKeyCode->ToNumber<int32_t>());

    KeyEvent keyEvent(code, action);

    auto jsKeySource = value->GetProperty("keySource");
    keyEvent.sourceType = static_cast<SourceType>(jsKeySource->ToNumber<int32_t>());

    auto jsDeviceId = value->GetProperty("deviceId");
    keyEvent.deviceId = jsDeviceId->ToNumber<int32_t>();

    auto jsMetaKey = value->GetProperty("metaKey");
    keyEvent.metaKey = jsMetaKey->ToNumber<int32_t>();

    auto jsTimestamp = value->GetProperty("timestamp");
    auto timeStamp = jsTimestamp->ToNumber<int64_t>();
    keyEvent.SetTimeStamp(timeStamp);

    auto jsUnicode = value->GetProperty("unicode");
    keyEvent.unicode = jsUnicode->ToNumber<uint32_t>();

    return keyEvent;
}

panda::Local<panda::JSValueRef> JsSendKeyEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    KeyEvent keyEvent = GetKeyEventFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, keyEvent]() { pipelineContext->OnNonPointerEvent(keyEvent); },
        TaskExecutor::TaskType::UI, "ArkUIJsSendKeyEvent");
    return panda::BooleanRef::New(vm, result);
}

static MouseEvent GetMouseEventFromJS(const JsiObject& value)
{
    MouseEvent mouseEvent;

    auto action = value->GetProperty("action");
    mouseEvent.action = static_cast<MouseAction>(action->ToNumber<int32_t>());

    auto button = value->GetProperty("button");
    mouseEvent.button = static_cast<MouseButton>(button->ToNumber<int32_t>());

    auto x = value->GetProperty("x");
    mouseEvent.x = x->ToNumber<float>();
    mouseEvent.deltaX = mouseEvent.x;

    auto y = value->GetProperty("y");
    mouseEvent.y = y->ToNumber<float>();
    mouseEvent.deltaY = mouseEvent.y;

    mouseEvent.time = std::chrono::high_resolution_clock::now();
    mouseEvent.sourceType = SourceType::MOUSE;
    return mouseEvent;
}

panda::Local<panda::JSValueRef> JsSendMouseEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope{Container::CurrentIdSafely()};
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    MouseEvent mouseEvent = GetMouseEventFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, mouseEvent]() { pipelineContext->OnMouseEvent(mouseEvent); },
        TaskExecutor::TaskType::UI, "ArkUIJsSendMouseEvent");
    return panda::BooleanRef::New(vm, result);
}

panda::Local<panda::JSValueRef> Vp2Px(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }

    double vpValue = firstArg->ToNumber(vm)->Value();
    double density = PipelineBase::GetCurrentDensity();
    double pxValue = vpValue * density;
    return panda::NumberRef::New(vm, pxValue);
}

panda::Local<panda::JSValueRef> Px2Vp(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = firstArg->ToNumber(vm)->Value();
    double vpValue = pxValue / density;

    return panda::NumberRef::New(vm, vpValue);
}

panda::Local<panda::JSValueRef> Fp2Px(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }

    double density = PipelineBase::GetCurrentDensity();
    double fpValue = firstArg->ToNumber(vm)->Value();

    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double pxValue = fpValue * density * fontScale;
    return panda::NumberRef::New(vm, pxValue);
}

panda::Local<panda::JSValueRef> Px2Fp(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    double density = PipelineBase::GetCurrentDensity();
    if (NearZero(density)) {
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = firstArg->ToNumber(vm)->Value();
    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    double fontScale = 1.0;
    if (pipelineContext) {
        fontScale = pipelineContext->GetFontScale();
    }
    double ratio = density * fontScale;
    double fpValue = pxValue / ratio;
    return panda::NumberRef::New(vm, fpValue);
}

panda::Local<panda::JSValueRef> Lpx2Px(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, panda::JSValueRef::Undefined(vm));
    auto width = window->GetCurrentWindowRect().Width();

    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, panda::JSValueRef::Undefined(vm));
    auto windowConfig = frontend->GetWindowConfig();
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        width -= 2 * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }

    double lpxValue = firstArg->ToNumber(vm)->Value();
    double pxValue = lpxValue * windowConfig.designWidthScale;
    return panda::NumberRef::New(vm, pxValue);
}

panda::Local<panda::JSValueRef> Px2Lpx(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto window = container->GetWindow();
    CHECK_NULL_RETURN(window, panda::JSValueRef::Undefined(vm));
    auto width = window->GetCurrentWindowRect().Width();

    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, panda::JSValueRef::Undefined(vm));
    auto windowConfig = frontend->GetWindowConfig();
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext && pipelineContext->IsContainerModalVisible()) {
        width -= 2 * (CONTAINER_BORDER_WIDTH + CONTENT_PADDING).ConvertToPx();
    }
    if (!windowConfig.autoDesignWidth) {
        windowConfig.UpdateDesignWidthScale(width);
    }
    
    double pxValue = firstArg->ToNumber(vm)->Value();
    double lpxValue = pxValue / windowConfig.designWidthScale;
    return panda::NumberRef::New(vm, lpxValue);
}

panda::Local<panda::JSValueRef> SetAppBackgroundColor(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string backgroundColorStr = firstArg->ToString(vm)->ToString(vm);
    auto container = Container::Current();
    if (!container) {
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext) {
        pipelineContext->SetAppBgColor(Color::FromString(backgroundColorStr));
    }
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> RequestFocus(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsString(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    std::string inspectorKey = firstArg->ToString(vm)->ToString(vm);

    bool result = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::BooleanRef::New(vm, result));
    if (!pipelineContext->GetTaskExecutor()) {
        return panda::BooleanRef::New(vm, result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI, "ArkUIJsRequestFocus");
    return panda::BooleanRef::New(vm, result);
}

panda::Local<panda::JSValueRef> SetCursor(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    uint32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsNumber()) {
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = firstArg->Int32Value(vm);

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    if (!pipelineContext->GetTaskExecutor()) {
        return panda::JSValueRef::Undefined(vm);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, intValue]() { pipelineContext->SetCursor(intValue); },
        TaskExecutor::TaskType::UI, "ArkUIJsSetCursor");
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> RestoreDefault(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    if (vm == nullptr) {
        return panda::JSValueRef::Undefined(vm);
    }

    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::JSValueRef::Undefined(vm));
    if (!pipelineContext->GetTaskExecutor()) {
        return panda::JSValueRef::Undefined(vm);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext]() { pipelineContext->RestoreDefault(); },
        TaskExecutor::TaskType::UI, "ArkUIJsRestoreDefault");
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JSHandleUncaughtException(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    ContainerScope scope(Container::CurrentIdSafely());
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto engine = EngineHelper::GetCurrentEngineSafely();
    CHECK_NULL_RETURN(engine, panda::JSValueRef::Undefined(vm));
    auto nativeEngine = engine->GetNativeEngine();
    auto arkNativeEngine = static_cast<ArkNativeEngine*>(nativeEngine);
    CHECK_NULL_RETURN(arkNativeEngine, panda::JSValueRef::Undefined(vm));
    NapiUncaughtExceptionCallback callback = arkNativeEngine->GetNapiUncaughtExceptionCallback();
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject(vm)) {
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<panda::ObjectRef> exception = firstArg->ToObject(vm);
    callback(arkNativeEngine->ArkValueToNapiValue(reinterpret_cast<napi_env>(arkNativeEngine), exception));
    return panda::JSValueRef::Undefined(vm);
}

#ifdef FORM_SUPPORTED
void JsRegisterFormViews(
    BindingTarget globalObj, const std::unordered_set<std::string>& formModuleList, bool isReload, void* nativeEngine)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return;
    }
    if (isReload) {
        JsBindFormViews(globalObj, formModuleList, nativeEngine, isReload);
        return;
    }
    auto vm = runtime->GetEcmaVm();
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadEtsCard"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadEtsCard));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "postCardAction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSPostCardAction));
#if defined(PREVIEW)
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "previewComponent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsPreviewerComponent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPreviewComponentFlag"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetPreviewComponentFlag));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "storePreviewComponents"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsStorePreviewComponents));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "GetRootView"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetRootView));
#endif
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "dumpMemoryStats"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsDumpMemoryStats));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$s"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetI18nResource));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$m"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetMediaResource));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodes"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodes));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodeById));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorTree"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorTree));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorByKey));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFilteredInspectorTree"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetFilteredInspectorTree));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFilteredInspectorTreeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetFilteredInspectorTreeById));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendEventByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendEventByKey));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendTouchEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendTouchEvent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendKeyEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendKeyEvent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendMouseEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendMouseEvent));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "vp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Vp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2vp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Vp));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "fp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Fp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2fp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Fp));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "lpx2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Lpx2Px));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2lpx"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Lpx));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAppBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetAppBackgroundColor));
    globalObj->Set(vm,
        panda::StringRef::NewFromUtf8(vm, "_arkUIUncaughtPromiseError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSHandleUncaughtException));

    JsBindFormViews(globalObj, formModuleList, nativeEngine);

    JSObjectTemplate toggleType;
    toggleType.Constant("Checkbox", 0);
    toggleType.Constant("Switch", 1);
    toggleType.Constant("Button", 2); // 2 means index of constant

    JSObjectTemplate refreshStatus;
    refreshStatus.Constant("Inactive", 0);
    refreshStatus.Constant("Drag", 1);
    refreshStatus.Constant("OverDrag", 2);
    refreshStatus.Constant("Refresh", 3); // 3 means index of constant
    refreshStatus.Constant("Done", 4);    // 4 means index of constant

    JSObjectTemplate mainAxisAlign;
    mainAxisAlign.Constant("Start", 1);
    mainAxisAlign.Constant("Center", 2);       // 2 means index of constant
    mainAxisAlign.Constant("End", 3);          // 3 means index of constant
    mainAxisAlign.Constant("SpaceBetween", 6); // 6 means index of constant
    mainAxisAlign.Constant("SpaceAround", 7);  // 7 means index of constant

    JSObjectTemplate crossAxisAlign;
    crossAxisAlign.Constant("Start", 1);

    crossAxisAlign.Constant("Center", 2);  // 2 means index of constant
    crossAxisAlign.Constant("End", 3);     // 3 means index of constant
    crossAxisAlign.Constant("Stretch", 4); // 4 means index of constant

    JSObjectTemplate direction;
    direction.Constant("Horizontal", 0);
    direction.Constant("Vertical", 1);

    JSObjectTemplate loadingProgressStyle;
    loadingProgressStyle.Constant("Default", 1);
    loadingProgressStyle.Constant("Circular", 2); // 2 means index of constant
    loadingProgressStyle.Constant("Orbital", 3);  // 3 means index of constant

    JSObjectTemplate progressStyle;
    progressStyle.Constant("Linear", 0);
    progressStyle.Constant("Ring", 1);      // 1 means index of constant
    progressStyle.Constant("Eclipse", 2);   // 2 means index of constant
    progressStyle.Constant("ScaleRing", 3); // 3 means index of constant
    progressStyle.Constant("Capsule", 4);   // 4 means index of constant

    JSObjectTemplate stackFit;
    stackFit.Constant("Keep", 0);
    stackFit.Constant("Stretch", 1);
    stackFit.Constant("Inherit", 2);    // 2 means index of constant
    stackFit.Constant("FirstChild", 3); // 3 means index of constant

    JSObjectTemplate overflow;
    overflow.Constant("Clip", 0);
    overflow.Constant("Observable", 1);

    JSObjectTemplate alignment;
    alignment.Constant("TopLeft", 0);
    alignment.Constant("TopCenter", 1);
    alignment.Constant("TopRight", 2);     // 2 means index of constant
    alignment.Constant("CenterLeft", 3);   // 3 means index of constant
    alignment.Constant("Center", 4);       // 4 means index of constant
    alignment.Constant("CenterRight", 5);  // 5 means index of constant
    alignment.Constant("BottomLeft", 6);   // 6 means index of constant
    alignment.Constant("BottomCenter", 7); // 7 means index of constant
    alignment.Constant("BottomRight", 8);  // 8 means index of constant

    JSObjectTemplate sliderStyle;
    sliderStyle.Constant("OutSet", 0);
    sliderStyle.Constant("InSet", 1);
    sliderStyle.Constant("NONE", 2);

    JSObjectTemplate datePickerMode;
    datePickerMode.Constant("DATE", static_cast<int>(DatePickerMode::DATE));
    datePickerMode.Constant("YEAR_AND_MONTH", static_cast<int>(DatePickerMode::YEAR_AND_MONTH));
    datePickerMode.Constant("MONTH_AND_DAY", static_cast<int>(DatePickerMode::MONTH_AND_DAY));

    JSObjectTemplate sliderChangeMode;
    sliderChangeMode.Constant("Begin", 0);
    sliderChangeMode.Constant("Moving", 1);
    sliderChangeMode.Constant("End", 2); // 2 means index of constant

    JSObjectTemplate pickerStyle;
    pickerStyle.Constant("Inline", 0);
    pickerStyle.Constant("Block", 1);
    pickerStyle.Constant("Fade", 2); // 2 means index of constant

    JSObjectTemplate buttonType;
    buttonType.Constant("Normal", (int)ButtonType::NORMAL);
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);
    buttonType.Constant("Arc", (int)ButtonType::ARC);
    buttonType.Constant("ROUNDED_RECTANGLE", (int)ButtonType::ROUNDED_RECTANGLE);

    JSObjectTemplate iconPosition;
    iconPosition.Constant("Start", 0);
    iconPosition.Constant("End", 1);

    JSObjectTemplate badgePosition;
    badgePosition.Constant("RightTop", 0);
    badgePosition.Constant("Right", 1);
    badgePosition.Constant("Left", 2); // 2 means index of constant

    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "MainAxisAlign"), *mainAxisAlign);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "CrossAxisAlign"), *crossAxisAlign);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Direction"), *direction);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "StackFit"), *stackFit);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Align"), *alignment);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Overflow"), *overflow);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ButtonType"), *buttonType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "LoadingProgressStyle"), *loadingProgressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ProgressStyle"), *progressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ToggleType"), *toggleType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "RefreshStatus"), *refreshStatus);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderStyle"), *sliderStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "DatePickerMode"), *datePickerMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderChangeMode"), *sliderChangeMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "IconPosition"), *iconPosition);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "PickerStyle"), *pickerStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "BadgePosition"), *badgePosition);
}
#endif

void JsRegisterViews(BindingTarget globalObj, void* nativeEngine)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return;
    }
    auto vm = runtime->GetEcmaVm();
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadDocument"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadDocument));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadEtsCard"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadEtsCard));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "postCardAction"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSPostCardAction));
#if defined(PREVIEW)
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "previewComponent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsPreviewerComponent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getPreviewComponentFlag"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetPreviewComponentFlag));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "storePreviewComponents"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsStorePreviewComponents));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "GetRootView"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetRootView));
#endif
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "dumpMemoryStats"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsDumpMemoryStats));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$s"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetI18nResource));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "$m"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetMediaResource));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodes"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodes));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorNodeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorNodeById));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorTree"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorTree));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getInspectorByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetInspectorByKey));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFilteredInspectorTree"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetFilteredInspectorTree));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getFilteredInspectorTreeById"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsGetFilteredInspectorTreeById));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendEventByKey"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendEventByKey));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendTouchEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendTouchEvent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendKeyEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendKeyEvent));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "sendMouseEvent"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsSendMouseEvent));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "vp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Vp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2vp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Vp));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "fp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Fp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2fp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Fp));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "lpx2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Lpx2Px));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2lpx"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Lpx));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "setAppBgColor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetAppBackgroundColor));
    globalObj->Set(vm,
        panda::StringRef::NewFromUtf8(vm, "_arkUIUncaughtPromiseError"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JSHandleUncaughtException));

    BindingTarget focusControlObj = panda::ObjectRef::New(const_cast<panda::EcmaVM*>(vm));
    focusControlObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "requestFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RequestFocus));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "focusControl"), focusControlObj);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerNamedRoute"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsRegisterNamedRoute));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "NavigationBuilderRegister"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsNavigationRegister));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "getArkUINativeModule"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), NG::ArkUINativeModule::GetArkUINativeModule));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadCustomTitleBar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadCustomTitleBar));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadCustomTitleButton"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadCustomButton));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadCustomAppbar"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadCustomAppBar));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "loadCustomWindowMask"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsLoadCustomWindowMask));

    BindingTarget cursorControlObj = panda::ObjectRef::New(const_cast<panda::EcmaVM*>(vm));
    cursorControlObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "setCursor"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), SetCursor));
    cursorControlObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "restoreDefault"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RestoreDefault));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "cursorControl"), cursorControlObj);
    JsBindViews(globalObj, nativeEngine);

    JSObjectTemplate toggleType;
    toggleType.Constant("Checkbox", 0);
    toggleType.Constant("Switch", 1);
    toggleType.Constant("Button", 2); // 2 means index of constant

    JSObjectTemplate refreshStatus;
    refreshStatus.Constant("Inactive", 0);
    refreshStatus.Constant("Drag", 1);
    refreshStatus.Constant("OverDrag", 2);
    refreshStatus.Constant("Refresh", 3); // 3 means index of constant
    refreshStatus.Constant("Done", 4);    // 4 means index of constant

    JSObjectTemplate mainAxisAlign;
    mainAxisAlign.Constant("Start", 1);
    mainAxisAlign.Constant("Center", 2);       // 2 means index of constant
    mainAxisAlign.Constant("End", 3);          // 3 means index of constant
    mainAxisAlign.Constant("SpaceBetween", 6); // 6 means index of constant
    mainAxisAlign.Constant("SpaceAround", 7);  // 7 means index of constant

    JSObjectTemplate crossAxisAlign;
    crossAxisAlign.Constant("Start", 1);

    crossAxisAlign.Constant("Center", 2);  // 2 means index of constant
    crossAxisAlign.Constant("End", 3);     // 3 means index of constant
    crossAxisAlign.Constant("Stretch", 4); // 4 means index of constant

    JSObjectTemplate direction;
    direction.Constant("Horizontal", 0);
    direction.Constant("Vertical", 1);

    JSObjectTemplate loadingProgressStyle;
    loadingProgressStyle.Constant("Default", 1);
    loadingProgressStyle.Constant("Circular", 2); // 2 means index of constant
    loadingProgressStyle.Constant("Orbital", 3);  // 3 means index of constant

    JSObjectTemplate progressStyle;
    progressStyle.Constant("Linear", 0);
    progressStyle.Constant("Ring", 1);      // 1 means index of constant
    progressStyle.Constant("Eclipse", 2);   // 2 means index of constant
    progressStyle.Constant("ScaleRing", 3); // 3 means index of constant
    progressStyle.Constant("Capsule", 4);   // 4 means index of constant

    JSObjectTemplate stackFit;
    stackFit.Constant("Keep", 0);
    stackFit.Constant("Stretch", 1);
    stackFit.Constant("Inherit", 2);    // 2 means index of constant
    stackFit.Constant("FirstChild", 3); // 3 means index of constant

    JSObjectTemplate overflow;
    overflow.Constant("Clip", 0);
    overflow.Constant("Observable", 1);

    JSObjectTemplate alignment;
    alignment.Constant("TopLeft", 0);
    alignment.Constant("TopCenter", 1);
    alignment.Constant("TopRight", 2);     // 2 means index of constant
    alignment.Constant("CenterLeft", 3);   // 3 means index of constant
    alignment.Constant("Center", 4);       // 4 means index of constant
    alignment.Constant("CenterRight", 5);  // 5 means index of constant
    alignment.Constant("BottomLeft", 6);   // 6 means index of constant
    alignment.Constant("BottomCenter", 7); // 7 means index of constant
    alignment.Constant("BottomRight", 8);  // 8 means index of constant

    JSObjectTemplate sliderStyle;
    sliderStyle.Constant("OutSet", 0);
    sliderStyle.Constant("InSet", 1);
    sliderStyle.Constant("NONE", 2);

    JSObjectTemplate datePickerMode;
    datePickerMode.Constant("DATE", static_cast<int>(DatePickerMode::DATE));
    datePickerMode.Constant("YEAR_AND_MONTH", static_cast<int>(DatePickerMode::YEAR_AND_MONTH));
    datePickerMode.Constant("MONTH_AND_DAY", static_cast<int>(DatePickerMode::MONTH_AND_DAY));

    JSObjectTemplate sliderChangeMode;
    sliderChangeMode.Constant("Begin", 0);
    sliderChangeMode.Constant("Moving", 1);
    sliderChangeMode.Constant("End", 2);   // 2 means index of constant
    sliderChangeMode.Constant("Click", 3); // 3 means index of constant

    JSObjectTemplate pickerStyle;
    pickerStyle.Constant("Inline", 0);
    pickerStyle.Constant("Block", 1);
    pickerStyle.Constant("Fade", 2); // 2 means index of constant

    JSObjectTemplate buttonType;
    buttonType.Constant("Normal", (int)ButtonType::NORMAL);
    buttonType.Constant("Capsule", (int)ButtonType::CAPSULE);
    buttonType.Constant("Circle", (int)ButtonType::CIRCLE);
    buttonType.Constant("Arc", (int)ButtonType::ARC);
    buttonType.Constant("ROUNDED_RECTANGLE", (int)ButtonType::ROUNDED_RECTANGLE);

    JSObjectTemplate iconPosition;
    iconPosition.Constant("Start", 0);
    iconPosition.Constant("End", 1);

    JSObjectTemplate badgePosition;
    badgePosition.Constant("RightTop", 0);
    badgePosition.Constant("Right", 1);
    badgePosition.Constant("Left", 2); // 2 means index of constant

    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "MainAxisAlign"), *mainAxisAlign);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "CrossAxisAlign"), *crossAxisAlign);

    auto container = Container::Current();
    if (container == nullptr || !container->IsDynamicRender()) {
        globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Direction"), *direction);
    }

    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "StackFit"), *stackFit);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Align"), *alignment);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "Overflow"), *overflow);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ButtonType"), *buttonType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "LoadingProgressStyle"), *loadingProgressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ProgressStyle"), *progressStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "ToggleType"), *toggleType);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "RefreshStatus"), *refreshStatus);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderStyle"), *sliderStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "DatePickerMode"), *datePickerMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderChangeMode"), *sliderChangeMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "IconPosition"), *iconPosition);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "PickerStyle"), *pickerStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "BadgePosition"), *badgePosition);
}

void JsRegisterWorkerViews(BindingTarget globalObj, void* nativeEngine)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return;
    }
    auto vm = runtime->GetEcmaVm();
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "vp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Vp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2vp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Vp));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "fp2px"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Fp2Px));
    globalObj->Set(
        vm, panda::StringRef::NewFromUtf8(vm, "px2fp"), panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Fp));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "lpx2px"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Lpx2Px));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "px2lpx"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), Px2Lpx));
    JsBindWorkerViews(globalObj, nativeEngine);
}

} // namespace OHOS::Ace::Framework

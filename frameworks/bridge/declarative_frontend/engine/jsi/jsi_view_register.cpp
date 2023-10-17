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
#include "bridge/declarative_frontend/frontend_delegate_declarative.h"
#include "bridge/declarative_frontend/interfaces/profiler/js_profiler.h"
#include "bridge/declarative_frontend/jsview/js_canvas_image_data.h"
#include "bridge/js_frontend/engine/jsi/ark_js_runtime.h"
#include "core/common/card_scope.h"
#include "core/common/container.h"
#include "core/components_ng/base/inspector.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/components_v2/inspector/inspector.h"

namespace OHOS::Ace::Framework {

constexpr int FUNC_SET_CREATE_ARG_LEN = 2;

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
        LOGE("RegisterCardUpdateCallback: can not get property 'localStorage_'!");
        return;
    }

    JSRef<JSObject> storage = JSRef<JSObject>::Cast(storageValue);
    JSRef<JSVal> setOrCreateVal = storage->GetProperty("setOrCreate");
    if (!setOrCreateVal->IsFunction()) {
        LOGE("RegisterCardUpdateCallback: can not get property 'setOrCreate'!");
        return;
    }

    JSRef<JSFunc> setOrCreate = JSRef<JSFunc>::Cast(setOrCreateVal);
    auto id = ContainerScope::CurrentId();
    auto callback = [storage, setOrCreate, id](const std::string& data) {
        ContainerScope scope(id);
        const EcmaVM* vm = storage->GetEcmaVM();
        CHECK_NULL_VOID(vm);
        std::unique_ptr<JsonValue> jsonRoot = JsonUtil::ParseJsonString(data);
        CHECK_NULL_VOID(jsonRoot);
        auto child = jsonRoot->GetChild();
        if (!child || !child->IsValid()) {
            LOGE("update card data error");
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
    if (container->IsFRSCardContainer()) {
        LOGI("RegisterCardUpdateCallback:Run Card In FRS");
        auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_VOID(frontEnd);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->SetUpdateCardDataCallback(callback);
        delegate->UpdatePageDataImmediately();
    } else {
        LOGI("RegisterCardUpdateCallback:Run Card In Host");
        auto frontEnd = AceType::DynamicCast<CardFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
        CHECK_NULL_VOID(frontEnd);
        auto delegate = frontEnd->GetDelegate();
        CHECK_NULL_VOID(delegate);
        delegate->SetUpdateCardDataCallback(callback);
        delegate->UpdatePageDataImmediately();
    }
}

void UpdateCardRootComponent(const panda::Local<panda::ObjectRef>& obj)
{
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        LOGE("UpdateCardRootComponent: argument provided is not a View!");
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

        if (container->IsFRSCardContainer()) {
            LOGI("Run Card In FRS");
            auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_VOID(frontEnd);
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_VOID(delegate);
            pageRouterManager = delegate->GetPageRouterManager();
        } else {
            LOGI("Run Card In Host");
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

        // update page life cycle function.
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
        return;
    } else {
        LOGE("eTSCard only support NG structure");
    }
}

panda::Local<panda::JSValueRef> JsLoadDocument(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("Load Document start");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject()) {
        LOGE("The arg is wrong, value must be object");
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
#if defined(PREVIEW)
    panda::Global<panda::ObjectRef> rootView(vm, obj->ToObject(vm));
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    arkRuntime->AddRootView(rootView);
#endif
    UpdateRootComponent(obj);

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsRegisterNamedRoute(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("Register NamedRoute start");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    // will need three arguments
    if (argc != 3) {
        LOGE("The arg is wrong, must have three arguments");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsFunction()) {
        LOGE("The arg is wrong, value must be function");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsString()) {
        LOGE("The arg is wrong, value must be string");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> thirdArg = runtimeCallInfo->GetCallArgRef(2);
    if (!thirdArg->IsObject()) {
        LOGE("The arg is wrong, value must be object");
        return panda::JSValueRef::Undefined(vm);
    }

    auto engine = EngineHelper::GetEngine(Container::CurrentId());
    CHECK_NULL_RETURN(engine, panda::JSValueRef::Undefined(vm));
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    CHECK_NULL_RETURN(jsiEngine, panda::JSValueRef::Undefined(vm));

    jsiEngine->AddToNamedRouterMap(panda::Global<panda::FunctionRef>(vm, Local<panda::FunctionRef>(firstArg)),
        secondArg->ToString(vm)->ToString(), thirdArg->ToObject(vm));

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
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc > 2) {
        LOGE("The arg is wrong, must have no more than two argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject()) {
        LOGE("The arg is wrong, value must be IsObject");
        return panda::JSValueRef::Undefined(vm);
    }

    Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
    if (!secondArg->IsObject()) {
        LOGE("The arg is wrong, value must be object");
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    auto* view = static_cast<JSView*>(obj->GetNativePointerField(0));
    if (!view && !static_cast<JSViewPartialUpdate*>(view) && !static_cast<JSViewFullUpdate*>(view)) {
        LOGE("JSPostCardAction: argument provided is not a View!");
        return panda::JSValueRef::Undefined(vm);
    }

    auto value = panda::JSON::Stringify(vm, secondArg);
    if (!value->IsString()) {
        LOGE("The second arg is wrong");
        return panda::JSValueRef::Undefined(vm);
    }
    auto valueStr = panda::Local<panda::StringRef>(value);
    auto action = valueStr->ToString();

#if !defined(NG_BUILD)
    int64_t cardId = view->GetCardId();
    auto container = Container::Current();
    if (container && container->IsUseNewPipeline()) {
        if (container->IsFRSCardContainer()) {
            LOGE("Form PostCardAction in FRS");
            auto frontEnd = AceType::DynamicCast<FormFrontendDeclarative>(container->GetCardFrontend(cardId).Upgrade());
            CHECK_NULL_RETURN(frontEnd, panda::JSValueRef::Undefined(vm));
            auto delegate = frontEnd->GetDelegate();
            CHECK_NULL_RETURN(delegate, panda::JSValueRef::Undefined(vm));
            delegate->FireCardAction(action);
        } else {
            LOGE("Form PostCardAction in HOST");
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
    LOGI("Load eTS Card start");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc > 2) {
        LOGE("The arg is wrong, must have no more than two argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsObject()) {
        LOGE("The arg is wrong, value must be object");
        return panda::JSValueRef::Undefined(vm);
    }

    panda::Local<panda::ObjectRef> obj = firstArg->ToObject(vm);
    UpdateCardRootComponent(obj);

    return panda::JSValueRef::Undefined(vm);
}

#if defined(PREVIEW)
panda::Local<panda::JSValueRef> JsPreviewerComponent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("PreviewerComponent start");
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    std::string requiredComponentName = arkRuntime->GetRequiredComponent();
    panda::Global<panda::ObjectRef> obj = arkRuntime->GetPreviewComponent(vm, requiredComponentName);
    if (obj->IsUndefined()) {
        LOGE("Get PreviewComponent object from map failed");
        return panda::JSValueRef::Undefined(vm);
    }
    UpdateRootComponent(obj.ToLocal());

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetPreviewComponentFlag(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("Get PreviewComponentFlag start");
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
    LOGD("Store PreviewerComponents start");
    EcmaVM* vm = runtimeCallInfo->GetVM();

    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The first value must be a number when calling JsStorePreviewComponents");
        return panda::JSValueRef::Undefined(vm);
    }
    panda::Local<NumberRef> componentNum = firstArg->ToNumber(vm);
    uint32_t numOfComponent = componentNum->Value();
    for (uint32_t index = 1; index <= numOfComponent * 2; index++) { // 2: each component pass two args, name and itself
        Local<JSValueRef> componentName = runtimeCallInfo->GetCallArgRef(index);
        if (!componentName->IsString()) {
            LOGE("The %{private}d componentName passed by StorePreviewComponents is not a string", index);
            return panda::JSValueRef::Undefined(vm);
        }
        std::string name = componentName->ToString(vm)->ToString();
        Local<JSValueRef> componentObj = runtimeCallInfo->GetCallArgRef(++index);
        if (componentObj->IsUndefined()) {
            LOGE("The %{private}d component passed by StorePreviewComponents is undefined", index);
            return panda::JSValueRef::Undefined(vm);
        }
        panda::Global<panda::ObjectRef> obj(vm, componentObj->ToObject(vm));
        arkRuntime->AddPreviewComponent(name, obj);
    }

    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetRootView(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("JsGetRootView");
    auto runtime = JsiDeclarativeEngineInstance::GetCurrentRuntime();
    shared_ptr<ArkJSRuntime> arkRuntime = std::static_pointer_cast<ArkJSRuntime>(runtime);
    return arkRuntime->GetRootView().ToLocal();
}
#endif

panda::Local<panda::JSValueRef> JsDumpMemoryStats(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("dumpMemoryStats: Not Implemented for ARK. UnSupported");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    return panda::JSValueRef::Undefined(vm);
}

panda::Local<panda::JSValueRef> JsGetI18nResource(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("JsGetI18nResource");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    if (argc != 2 && argc != 1) {
        LOGE("The arg is wrong, it is supposed to have one or two arguments");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString()) {
        LOGE("The arg is wrong, value must be string");
        return panda::JSValueRef::Undefined(vm);
    }

    std::vector<std::string> splitStr;
    std::string str = firstArg->ToString(vm)->ToString();
    StringUtils::SplitStr(str, ".", splitStr);
    if (splitStr.size() != 2) {
        LOGE("input string res value must can be split by dot");
        return panda::JSValueRef::Undefined(vm);
    }

    auto targetStringKey = splitStr[0];
    auto targetStringKeyValue = splitStr[1];
    auto resultStrJson = JsiDeclarativeEngineInstance::GetI18nStringResource(targetStringKey, targetStringKeyValue);
    auto resultStr = resultStrJson->GetString();
    if (argc == 2) {
        panda::LocalScope scope(vm);
        Local<JSValueRef> secondArg = runtimeCallInfo->GetCallArgRef(1);
        if (secondArg->IsArray(vm)) {
            auto arrayVal = panda::Local<panda::ArrayRef>(secondArg);
            auto len = arrayVal->Length(vm);
            std::vector<std::string> arrayResult;
            for (auto i = 0U; i < len; i++) {
                auto subItemVal = panda::ArrayRef::GetValueAt(vm, arrayVal, i);
                if (!subItemVal->IsString()) {
                    arrayResult.emplace_back(std::string());
                    continue;
                }
                auto itemVal = panda::Local<panda::StringRef>(subItemVal);
                arrayResult.emplace_back(itemVal->ToString());
            }
            ReplacePlaceHolderArray(resultStr, arrayResult);
        } else if (secondArg->IsObject()) {
            auto value = panda::JSON::Stringify(vm, secondArg);
            if (value->IsString()) {
                auto valueStr = panda::Local<panda::StringRef>(value);
                std::unique_ptr<JsonValue> argsPtr = JsonUtil::ParseJsonString(valueStr->ToString());
                ReplacePlaceHolder(resultStr, argsPtr);
            }
        } else if (secondArg->IsNumber()) {
            double count = secondArg->ToNumber(vm)->Value();
            auto pluralChoice = Localization::GetInstance()->PluralRulesFormat(count);
            if (!pluralChoice.empty()) {
                resultStr = ParserPluralResource(resultStrJson, pluralChoice, str);
            }
        }
    }

    return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
}

panda::Local<panda::JSValueRef> JsGetMediaResource(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    LOGD("JsGetMediaResource");
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString()) {
        LOGE("The arg is wrong, value must be string");
        return panda::JSValueRef::Undefined(vm);
    }

    std::string targetMediaFileName = firstArg->ToString(vm)->ToString();
    std::string filePath = JsiDeclarativeEngineInstance::GetMediaResource(targetMediaFileName);
    return panda::StringRef::NewFromUtf8(vm, filePath.c_str());
}

RefPtr<FrontendDelegate> JsGetFrontendDelegate()
{
    auto engine = EngineHelper::GetEngine(Container::CurrentId());
    auto jsiEngine = AceType::DynamicCast<JsiDeclarativeEngine>(engine);
    if (!jsiEngine) {
        LOGE("jsiEngine is null");
        return nullptr;
    }
    auto engineInstance = jsiEngine->GetEngineInstance();
    if (engineInstance == nullptr) {
        LOGE("engineInstance is null!");
        return nullptr;
    }
    return engineInstance->GetDelegate();
}

panda::Local<panda::JSValueRef> JsGetInspectorNodes(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        LOGE("declarativeDelegate is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    auto nodeInfos = accessibilityManager->DumpComposedElementsToJson();
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos->ToString().c_str()));
}

panda::Local<panda::JSValueRef> JsGetInspectorNodeById(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsNumber()) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    auto declarativeDelegate = OHOS::Ace::AceType::DynamicCast<FrontendDelegateDeclarative>(JsGetFrontendDelegate());
    if (!declarativeDelegate) {
        LOGE("declarativeDelegate is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    auto accessibilityManager = declarativeDelegate->GetJSAccessibilityManager();
    if (!accessibilityManager) {
        LOGE("accessibilityManager is null!");
        return panda::JSValueRef::Undefined(vm);
    }
    int32_t intValue = firstArg->Int32Value(vm);
    auto nodeInfo = accessibilityManager->DumpComposedElementToJson(intValue);
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfo->ToString().c_str()));
}

panda::Local<panda::JSValueRef> JsGetInspectorTree(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }

    if (container->IsUseNewPipeline()) {
        auto nodeInfos = NG::Inspector::GetInspector();
        return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str()));
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        LOGE("pipeline is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto nodeInfos = V2::Inspector::GetInspectorTree(pipelineContext);
    return panda::JSON::Parse(vm, panda::StringRef::NewFromUtf8(vm, nodeInfos.c_str()));
#else
    return panda::JSValueRef::Undefined(vm);
#endif
}

panda::Local<panda::JSValueRef> JsGetInspectorByKey(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsString()) {
        LOGE("The arg is wrong, must have one string argument");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    std::string key = firstArg->ToString(vm)->ToString();
    if (container->IsUseNewPipeline()) {
        auto resultStr = NG::Inspector::GetInspectorNodeByKey(key);
        return panda::StringRef::NewFromUtf8(vm, resultStr.c_str());
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        LOGE("pipelineContext==nullptr");
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 3 || !firstArg->IsString()) { // 3: arg numbers
        LOGE("The arg is wrong, must have one string argument");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }

    std::string key = firstArg->ToString(vm)->ToString();
    auto action = runtimeCallInfo->GetCallArgRef(1)->Int32Value(vm);
    auto params = runtimeCallInfo->GetCallArgRef(2)->ToString(vm)->ToString();
    if (container->IsUseNewPipeline()) {
        auto result = NG::Inspector::SendEventByKey(key, action, params);
        return panda::BooleanRef::New(vm, result);
    }
#if !defined(NG_BUILD)
    auto pipelineContext = AceType::DynamicCast<PipelineContext>(container->GetPipelineContext());
    if (pipelineContext == nullptr) {
        LOGE("pipelineContext==nullptr");
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject()) {
        LOGE("The arg is wrong, must have one object argument");
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        LOGE("pipelineContext==nullptr");
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    TouchEvent touchPoint = GetTouchPointFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, touchPoint]() { pipelineContext->OnTouchEvent(touchPoint); }, TaskExecutor::TaskType::UI);
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

    return keyEvent;
}

panda::Local<panda::JSValueRef> JsSendKeyEvent(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject()) {
        LOGE("The arg is wrong, must have one object argument");
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        LOGE("pipelineContext==nullptr");
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    KeyEvent keyEvent = GetKeyEventFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, keyEvent]() { pipelineContext->OnKeyEvent(keyEvent); }, TaskExecutor::TaskType::UI);
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    auto argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsObject()) {
        LOGE("The arg is wrong, must have one object argument");
        return panda::JSValueRef::Undefined(vm);
    }

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
        return panda::JSValueRef::Undefined(vm);
    }
    auto pipelineContext = container->GetPipelineContext();
    if (pipelineContext == nullptr) {
        LOGE("pipelineContext==nullptr");
        return panda::JSValueRef::Undefined(vm);
    }
    JsiObject obj(firstArg);
    MouseEvent mouseEvent = GetMouseEventFromJS(obj);
    auto result = pipelineContext->GetTaskExecutor()->PostTask(
        [pipelineContext, mouseEvent]() { pipelineContext->OnMouseEvent(mouseEvent); }, TaskExecutor::TaskType::UI);
    return panda::BooleanRef::New(vm, result);
}

panda::Local<panda::JSValueRef> Vp2Px(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }

    double vpValue = firstArg->ToNumber(vm)->Value();
    double density = SystemProperties::GetResolution();
    double pxValue = vpValue * density;
    return panda::NumberRef::New(vm, pxValue);
}

panda::Local<panda::JSValueRef> Px2Vp(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    double density = SystemProperties::GetResolution();
    if (NearZero(density)) {
        LOGE("The density cannot be zero");
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = firstArg->ToNumber(vm)->Value();
    double vpValue = pxValue / density;

    return panda::NumberRef::New(vm, vpValue);
}

panda::Local<panda::JSValueRef> Fp2Px(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }

    double density = SystemProperties::GetResolution();
    double fpValue = firstArg->ToNumber(vm)->Value();

    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    double density = SystemProperties::GetResolution();
    if (NearZero(density)) {
        LOGE("The density cannot be zero");
        return panda::JSValueRef::Undefined(vm);
    }

    double pxValue = firstArg->ToNumber(vm)->Value();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, panda::JSValueRef::Undefined(vm));
    auto windowConfig = frontend->GetWindowConfig();
    double lpxValue = firstArg->ToNumber(vm)->Value();
    double pxValue = lpxValue * windowConfig.GetDesignWidthScale(SystemProperties::GetDeviceWidth());
    return panda::NumberRef::New(vm, pxValue);
}

panda::Local<panda::JSValueRef> Px2Lpx(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsNumber()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, panda::JSValueRef::Undefined(vm));
    auto frontend = container->GetFrontend();
    CHECK_NULL_RETURN(frontend, panda::JSValueRef::Undefined(vm));
    auto windowConfig = frontend->GetWindowConfig();
    double pxValue = firstArg->ToNumber(vm)->Value();
    double lpxValue = pxValue / windowConfig.GetDesignWidthScale(SystemProperties::GetDeviceWidth());
    return panda::NumberRef::New(vm, lpxValue);
}

panda::Local<panda::JSValueRef> SetAppBackgroundColor(panda::JsiRuntimeCallInfo* runtimeCallInfo)
{
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (argc != 1) {
        LOGE("The arg is wrong, must have one argument");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (!firstArg->IsString()) {
        LOGE("The arg is wrong, value must be number");
        return panda::JSValueRef::Undefined(vm);
    }
    std::string backgroundColorStr = firstArg->ToString(vm)->ToString();
    auto container = Container::Current();
    if (!container) {
        LOGW("container is null");
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
    EcmaVM* vm = runtimeCallInfo->GetVM();
    int32_t argc = runtimeCallInfo->GetArgsNumber();
    if (vm == nullptr) {
        LOGE("The EcmaVM is null");
        return panda::JSValueRef::Undefined(vm);
    }
    Local<JSValueRef> firstArg = runtimeCallInfo->GetCallArgRef(0);
    if (argc < 1 || !firstArg->IsString()) {
        LOGE("The arg is wrong, must have one object argument");
        return panda::JSValueRef::Undefined(vm);
    }
    std::string inspectorKey = firstArg->ToString(vm)->ToString();

    bool result = false;
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, panda::BooleanRef::New(vm, result));
    if (!pipelineContext->GetTaskExecutor()) {
        LOGE("pipelineContext's task excutor is null");
        return panda::BooleanRef::New(vm, result);
    }
    pipelineContext->GetTaskExecutor()->PostSyncTask(
        [pipelineContext, inspectorKey, &result]() { result = pipelineContext->RequestFocus(inspectorKey); },
        TaskExecutor::TaskType::UI);
    return panda::BooleanRef::New(vm, result);
}

#ifdef FORM_SUPPORTED
void JsRegisterFormViews(BindingTarget globalObj, const std::unordered_set<std::string>& formModuleList, bool isReload)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        LOGE("JsRegisterViews can't find runtime");
        return;
    }
    if (isReload) {
        JsBindFormViews(globalObj, formModuleList, isReload);
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

    JsBindFormViews(globalObj, formModuleList);

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
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderChangeMode"), *sliderChangeMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "IconPosition"), *iconPosition);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "PickerStyle"), *pickerStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "BadgePosition"), *badgePosition);
    LOGD("View classes and jsCreateDocument, registerObservableObject functions registered.");
}
#endif

void JsRegisterViews(BindingTarget globalObj)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        LOGE("JsRegisterViews can't find runtime");
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

    BindingTarget focusControlObj = panda::ObjectRef::New(const_cast<panda::EcmaVM*>(vm));
    focusControlObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "requestFocus"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), RequestFocus));
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "focusControl"), focusControlObj);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "registerNamedRoute"),
        panda::FunctionRef::New(const_cast<panda::EcmaVM*>(vm), JsRegisterNamedRoute));

    JsBindViews(globalObj);

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
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "SliderChangeMode"), *sliderChangeMode);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "IconPosition"), *iconPosition);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "PickerStyle"), *pickerStyle);
    globalObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "BadgePosition"), *badgePosition);
    LOGD("View classes and jsCreateDocument, registerObservableObject functions registered.");
}

} // namespace OHOS::Ace::Framework

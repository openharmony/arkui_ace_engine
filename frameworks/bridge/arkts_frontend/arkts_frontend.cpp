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
#include "bridge/arkts_frontend/arkts_frontend.h"

#include <ani.h>
#include "interfaces/inner_api/ace/constants.h"
#include "ui/base/utils/utils.h"

#include "bridge/arkts_frontend/entry/arkts_entry_loader.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/base/subwindow/subwindow_manager.h"
#include "bridge/arkts_frontend/ani_context_module.h"
#include "utils/ani_utils.h"

namespace OHOS::Ace {
UIContentErrorCode ArktsFrontend::RunPage(
    const std::shared_ptr<std::vector<uint8_t>>& content, const std::string& params)
{
    return UIContentErrorCode::NO_ERRORS;
}

namespace {
/* copied from arkcompiler_ets_frontend vmloader.cc*/
struct AppInfo {
    const char* className;
    const char* createMethodName;
    const char* createMethodSig;
    const char* startMethodName;
    const char* startMethodSig;
    const char* enterMethodName;
    const char* enterMethodSig;
    const char* emitEventMethodName;
    const char* emitEventMethodSig;
    const char* checkCallbackMethodName;
    const char* checkCallbackEventMethodSig;
    const char* handleMessageMethodName;
    const char* handleMessageMethodSig;
    const char* registerNativeModule;
    const char* registerNativeModuleSig;
};
/* copied from arkcompiler_ets_frontend vmloader.cc*/
const AppInfo KOALA_APP_INFO = {
    "arkui.ArkUIEntry.Application",
    "createApplication",
    "C{std.core.String}C{std.core.String}zC{std.core.String}C{arkui.UserView.UserView}"
    "C{arkui.component.customComponent.EntryPoint}:C{arkui.ArkUIEntry.Application}",
    "start",
    "z:l",
    "enter",
    "iil:z",
    "emitEvent",
    "iiii:",
    "checkCallbacks",
    ":",
    "handleMessage",
    "liC{std.core.String}:z",
    "registerNativeModulePreloader",
    ":",
};

std::string GetErrorProperty(ani_env* aniEnv, ani_error aniError, const char* property)
{
    TAG_LOGD(AceLogTag::ACE_SUB_WINDOW, "called");
    std::string propertyValue;
    ani_status status = ANI_ERROR;
    ani_type errorType = nullptr;
    if ((status = aniEnv->Object_GetType(aniError, &errorType)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Object_GetType failed, status : %{public}d", status);
        return propertyValue;
    }
    auto errorClass = static_cast<ani_class>(errorType);
    ani_method getterMethod = nullptr;
    if ((status = aniEnv->Class_FindMethod(errorClass, property, nullptr, &getterMethod)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Class_FindMethod failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_ref aniRef = nullptr;
    if ((status = aniEnv->Object_CallMethod_Ref(aniError, getterMethod, &aniRef)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "Object_CallMethod_Ref failed, status : %{public}d", status);
        return propertyValue;
    }
    ani_string aniString = reinterpret_cast<ani_string>(aniRef);
    ani_size sz {};
    if ((status = aniEnv->String_GetUTF8Size(aniString, &sz)) != ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "String_GetUTF8Size failed, status : %{public}d", status);
        return propertyValue;
    }
    propertyValue.resize(sz + 1);
    if ((status = aniEnv->String_GetUTF8SubString(
        aniString, 0, sz, propertyValue.data(), propertyValue.size(), &sz))!= ANI_OK) {
        TAG_LOGE(AceLogTag::ACE_SUB_WINDOW, "String_GetUTF8SubString failed, status : %{public}d", status);
        return propertyValue;
    }
    propertyValue.resize(sz);
    return propertyValue;
}

void RunArkoalaEventLoop(ani_env* env, ani_ref app)
{
    ani_boolean errorExists;
    env->ExistUnhandledError(&errorExists);
    ani_status status;
    ani_class appClass;
    if ((status = env->FindClass(KOALA_APP_INFO.className, &appClass)) != ANI_OK) {
        ani_error aniError;
        env->GetUnhandledError(&aniError);
        env->ResetError();
        std::string errorMsg = GetErrorProperty(env, aniError, "<get>message");
        std::string errorName = GetErrorProperty(env, aniError, "<get>name");
        std::string errorStack = GetErrorProperty(env, aniError, "<get>stack");
        LOGE("[%{public}s] Cannot load main class %{public}s, status: %{public}d, \nerrorMsg: %{public}s, \nerrorName: "
             "%{public}s, \nerrorStack: %{public}s",
            __func__, KOALA_APP_INFO.className, status, errorMsg.c_str(), errorName.c_str(), errorStack.c_str());
        return;
    }

    ani_method enter = nullptr;
    if (env->Class_FindMethod(appClass, KOALA_APP_INFO.enterMethodName, KOALA_APP_INFO.enterMethodSig, &enter) !=
        ANI_OK) {
        LOGE("[%{public}s] Cannot find enter method %{public}s", __func__, KOALA_APP_INFO.enterMethodName);
        // TryEmitError(env);
        return;
    }

    ani_int arg0 = 0;
    ani_int arg1 = 0;
    ani_boolean result;
    if (env->Object_CallMethod_Boolean(static_cast<ani_object>(app), enter, &result, arg0, arg1, nullptr) != ANI_OK) {
        LOGE("[%{public}s] Call enter method failed", __func__);
        return;
    }
}

// fire all arkoala callbacks at the tail of vsync (PipelineContext::FlushVsync)
void FireAllArkoalaAsyncEvents(ani_env* env, ani_ref app)
{
    ani_class appClass;
    ANI_CALL(env, FindClass(KOALA_APP_INFO.className, &appClass), return);

    ani_method checkCallbacks = nullptr;
    ANI_CALL(env,
        Class_FindMethod(appClass, KOALA_APP_INFO.checkCallbackMethodName, KOALA_APP_INFO.checkCallbackEventMethodSig,
            &checkCallbacks),
        return);

    ANI_CALL(env, Object_CallMethod_Void(static_cast<ani_object>(app), checkCallbacks), return);
}
} // namespace

ArktsFrontend::ArktsFrontend(void* runtime)
{
    auto* env = reinterpret_cast<ani_env*>(runtime);
    if (!env) {
        LOGW("ArktsFrontend AniEnv is invalid!");
        return;
    }
    type_ = FrontendType::ARK_TS;
    env->GetVM(&vm_);
}

ani_object LegacyLoadPage(ani_env* env)
{
    do {
        ani_status state;
        ani_ref linkerRef;
        if ((state = static_cast<ani_status>(Ani::AniUtils::GetNearestNonBootRuntimeLinker(env, linkerRef))) !=
            ANI_OK) {
            LOGE("Get getNearestNonBootRuntimeLinker failed, %{public}d", state);
            break;
        }

        std::string entryPath = "entry.src.main.ets.pages.Index.ComExampleTrivialApplication";
        ani_string entryClassStr;
        env->String_NewUTF8(entryPath.c_str(), entryPath.length(), &entryClassStr);
        ani_class entryClass = nullptr;
        ani_ref entryClassRef = nullptr;

        ani_class cls = nullptr;
        if ((state = env->FindClass("std.core.RuntimeLinker", &cls)) != ANI_OK) {
            LOGE("FindClass RuntimeLinker failed, %{public}d", state);
            break;
        }

        ani_method loadClassMethod;
        if ((state = env->Class_FindMethod(cls, "loadClass", "C{std.core.String}C{std.core.Boolean}:C{std.core.Class}",
                 &loadClassMethod)) != ANI_OK) {
            LOGE("Class_FindMethod loadClass failed, %{public}d", state);
            break;
        }

        ani_object isInit;
        if ((state = static_cast<ani_status>(Ani::AniUtils::CreateAniBoolean(env, false, isInit))) != ANI_OK) {
            LOGE("Create Boolean object failed, %{public}d", state);
            break;
        }

        if ((state = env->Object_CallMethod_Ref(
                 (ani_object)linkerRef, loadClassMethod, &entryClassRef, entryClassStr, isInit)) != ANI_OK) {
            LOGE("Object_CallMethod_Ref loadClassMethod failed");
            ani_error errorInfo;
            env->GetUnhandledError(&errorInfo);
            env->ResetError();
            break;
        }
        entryClass = static_cast<ani_class>(entryClassRef);

        ani_method entryMethod = nullptr;
        if (env->Class_FindMethod(entryClass, "<ctor>", ":", &entryMethod) != ANI_OK) {
            LOGE("Class_FindMethod ctor failed");
            break;
        }

        ani_object entryObject = nullptr;
        if (env->Object_New(entryClass, entryMethod, &entryObject) != ANI_OK) {
            LOGE("Object_New AbcRuntimeLinker failed");
            break;
        }
        return entryObject;
    } while (false);
    return nullptr;
}

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, UIContentErrorCode::INVALID_URL);

    ani_class appClass;
    EntryLoader entryLoader(url, env);

    pageRouterManager_ = NG::PageRouterManagerFactory::CreateManager();

    if (env->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
        LOGE("Cannot load main class %{public}s", KOALA_APP_INFO.className);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_static_method create;
    if (env->Class_FindStaticMethod(
            appClass, KOALA_APP_INFO.createMethodName, KOALA_APP_INFO.createMethodSig, &create) != ANI_OK) {
        LOGE("Cannot find create method %{public}s", KOALA_APP_INFO.createMethodName);
        return UIContentErrorCode::INVALID_URL;
    }

    ani_string aniUrl;
    env->String_NewUTF8(url.c_str(), url.size(), &aniUrl);
    ani_string aniParams;
    env->String_NewUTF8(params.c_str(), params.size(), &aniParams);

    ani_ref appLocal;
    ani_ref optionalEntry;
    env->GetUndefined(&optionalEntry);
    auto entryPointObj = url == "__INTEROP__" ? nullptr : entryLoader.GetPageEntryObj();
    auto legacyEntryPointObj = url == "__INTEROP__" ? nullptr : LegacyLoadPage(env);
    std::string moduleName = Container::Current()->GetModuleName();
    ani_string module;
    env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &module);
    if (env->Class_CallStaticMethod_Ref(appClass, create, &appLocal, aniUrl, aniParams, false, module,
            legacyEntryPointObj ? legacyEntryPointObj : optionalEntry,
            entryPointObj ? entryPointObj : optionalEntry) != ANI_OK) {
        LOGE("createApplication returned null");
        return UIContentErrorCode::INVALID_URL;
    }

    env->GlobalReference_Create(appLocal, &app_);

    if (taskExecutor_ == nullptr) {
        LOGE("taskExecutor is nullptr");
        return UIContentErrorCode::NULL_POINTER;
    }
    taskExecutor_->PostTask([weak = WeakClaim(this)]() {
        auto frontend = weak.Upgrade();
        CHECK_NULL_VOID(frontend);
        auto* env = Ani::AniUtils::GetAniEnv(frontend->GetVM());
        CHECK_NULL_VOID(env);
        ani_class appClass;
        if (env->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
            LOGE("Cannot load main class %{public}s", KOALA_APP_INFO.className);
            return;
        }

        ani_method start;
        if (env->Class_FindMethod(appClass, KOALA_APP_INFO.startMethodName, KOALA_APP_INFO.startMethodSig, &start) !=
            ANI_OK) {
            LOGE("find start method returned null");
            return;
        }

        ani_long result;
        if (env->Object_CallMethod_Long(static_cast<ani_object>(frontend->GetApp()), start, &result, ANI_FALSE) !=
            ANI_OK) {
            LOGE("call start method returned null");
            return;
        }
        }, TaskExecutor::TaskType::JS, "ArkUIRunPageUrl");

    // TODO: init event loop
    CHECK_NULL_RETURN(pipeline_, UIContentErrorCode::NULL_POINTER);
    pipeline_->SetVsyncListener([vm = vm_, app = app_]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        RunArkoalaEventLoop(env, app);
    });

    // register one hook method to pipeline, which will be called at the tail of vsync
    pipeline_->SetAsyncEventsHookListener([vm = vm_, app = app_]() {
        auto* env = Ani::AniUtils::GetAniEnv(vm);
        FireAllArkoalaAsyncEvents(env, app);
    });

    return UIContentErrorCode::NO_ERRORS;
}

void ArktsFrontend::AttachPipelineContext(const RefPtr<PipelineBase>& context)
{
    pipeline_ = DynamicCast<NG::PipelineContext>(context);
    if (accessibilityManager_) {
        accessibilityManager_->SetPipelineContext(context);
        accessibilityManager_->InitializeCallback();
    }
}

void ArktsFrontend::AttachSubPipelineContext(const RefPtr<PipelineBase>& context)
{
    if (!context) {
        return;
    }
    accessibilityManager_->AddSubPipelineContext(context);
    accessibilityManager_->RegisterSubWindowInteractionOperation(context->GetWindowId());
}

ani_ref ArktsFrontend::GetSharedStorage(int32_t id)
{
    int32_t currentInstance = id;
    if (currentInstance >= MIN_SUBCONTAINER_ID && currentInstance < MIN_PLUGIN_SUBCONTAINER_ID) {
        currentInstance = SubwindowManager::GetInstance()->GetParentContainerId(currentInstance);
    }
    auto it = storageMap_.find(currentInstance);
    if (it == storageMap_.end()) {
        LOGW("LocalStorage with ID %{public}d not found!", currentInstance);
        return nullptr;
    }
    return reinterpret_cast<ani_ref>(it->second);
}

void ArktsFrontend::Destroy()
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    env->GlobalReference_Delete(app_);
    app_ = nullptr;
    handleMessageMethod_ = nullptr;
}

ani_object ArktsFrontend::GetUIContext(int32_t instanceId)
{
    ani_object result = nullptr;
    ani_status status;

    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, result);

    ani_class uiContextClass;
    if ((status = env->FindClass("arkui.base.UIContextUtil.UIContextUtil", &uiContextClass)) != ANI_OK) {
        LOGE("FindClass UIContext failed, %{public}d", status);
        return result;
    }
    ani_ref aniRef = nullptr;
    if ((status = env->Class_CallStaticMethodByName_Ref(uiContextClass, "getOrCreateUIContextById",
        "i:C{@ohos.arkui.UIContext.UIContext}", &aniRef, instanceId)) != ANI_OK) {
        LOGE("Class_CallStaticMethodByName_Ref failed, %{public}d", status);
        return result;
    }
    result = reinterpret_cast<ani_object>(aniRef);
    return result;
}

void* ArktsFrontend::GetEnv()
{
    return Ani::AniUtils::GetAniEnv(vm_);
}

ani_ref ArktsFrontend::GetApp()
{
    return app_;
}

ani_vm *ArktsFrontend::GetVM()
{
    return vm_;
}

void ArktsFrontend::PushExtender(
    const PageRouterOptions& options, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = options.url;
    routerPageInfo.params = options.params;
    routerPageInfo.recoverable = options.recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(options.routerMode);
    routerPageInfo.errorCallback = options.errorCallback;
    routerPageInfo.isNamedRouterMode = options.isNamedRouterMode;
    pageRouterManager_->PushExtender(routerPageInfo, std::move(finishCallback), jsNode);
}

void ArktsFrontend::PushNamedRouteExtender(
    const PageRouterOptions& options, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = options.url;
    routerPageInfo.params = options.params;
    routerPageInfo.recoverable = options.recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(options.routerMode);
    routerPageInfo.errorCallback = options.errorCallback;
    routerPageInfo.isNamedRouterMode = options.isNamedRouterMode;
    pageRouterManager_->PushNamedRouteExtender(routerPageInfo, std::move(finishCallback), jsNode);
}

void ArktsFrontend::ReplaceExtender(
    const PageRouterOptions& options, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = options.url;
    routerPageInfo.params = options.params;
    routerPageInfo.recoverable = options.recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(options.routerMode);
    routerPageInfo.errorCallback = options.errorCallback;
    routerPageInfo.isNamedRouterMode = options.isNamedRouterMode;
    pageRouterManager_->ReplaceExtender(routerPageInfo, std::move(finishCallback), jsNode);
}

void ArktsFrontend::ReplaceNamedRouteExtender(
    const PageRouterOptions& options, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = options.url;
    routerPageInfo.params = options.params;
    routerPageInfo.recoverable = options.recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(options.routerMode);
    routerPageInfo.errorCallback = options.errorCallback;
    routerPageInfo.isNamedRouterMode = options.isNamedRouterMode;
    pageRouterManager_->ReplaceNamedRouteExtender(routerPageInfo, std::move(finishCallback), jsNode);
}

void ArktsFrontend::RunPageExtender(
    const PageRouterOptions& options, const std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = options.url;
    routerPageInfo.params = options.params;
    routerPageInfo.recoverable = options.recoverable;
    routerPageInfo.routerMode = static_cast<NG::RouterMode>(options.routerMode);
    routerPageInfo.errorCallback = options.errorCallback;
    routerPageInfo.isNamedRouterMode = options.isNamedRouterMode;
    pageRouterManager_->RunPageExtender(routerPageInfo, std::move(finishCallback), jsNode);
}

void ArktsFrontend::BackExtender(const std::string& url, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    pageRouterManager_->BackWithTargetExtender(routerPageInfo);
}

void ArktsFrontend::BackToIndexExtender(int32_t index, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->BackToIndexWithTargetExtender(index, params);
}

void ArktsFrontend::ClearExtender()
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->Clear();
}

void ArktsFrontend::ShowAlertBeforeBackPageExtender(const std::string& url)
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto dialogCallback = [](int32_t callbackType) {};
    pageRouterManager_->EnableAlertBeforeBackPage(url, std::move(dialogCallback));
}

void ArktsFrontend::HideAlertBeforeBackPageExtender()
{
    CHECK_NULL_VOID(pageRouterManager_);
    pageRouterManager_->DisableAlertBeforeBackPage();
}

bool ArktsFrontend::OnBackPressed()
{
    CHECK_NULL_RETURN(pageRouterManager_, false);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_RETURN(pageNode, false);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_RETURN(pagePattern, false);
    if (pagePattern->OnBackPressed()) {
        return true;
    }
    return pageRouterManager_->Pop();
}

void ArktsFrontend::OnShow()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnShow(true);
}

void ArktsFrontend::OnHide()
{
    CHECK_NULL_VOID(pageRouterManager_);
    auto pageNode = pageRouterManager_->GetCurrentPageNode();
    CHECK_NULL_VOID(pageNode);
    auto pagePattern = pageNode->GetPattern<NG::PagePattern>();
    CHECK_NULL_VOID(pagePattern);
    pagePattern->OnHide(true);
}

void ArktsFrontend::OpenStateMgmtInterop()
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);

    ani_status state;

    static const char* moduleName = "arkui.component.interop";
    ani_module interopModule;
    state = env->FindModule(moduleName, &interopModule);
    if (state != ANI_OK) {
        LOGE("Cannot find module arkui.component.interop %{public}d", state);
        return;
    }

    ani_function fn;
    state = env->Module_FindFunction(interopModule, "openInterop", ":", &fn);
    if (state != ANI_OK) {
        LOGE("Cannot find function openInterop in module %{public}d", state);
    }

    state = env->Function_Call_Void(fn);
    if (state != ANI_OK) {
        LOGE("Function_Call openInterop failed %{public}d", state);
    }
    return;
}

napi_value ArktsFrontend::GetContextValue()
{
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, nullptr);
    auto type = container->GetFrontendType();
    if (type == FrontendType::STATIC_HYBRID_DYNAMIC && container->GetSubFrontend()) {
        // support 1.1 call getUIContext when STATIC_HYBRID_DYNAMIC
        return container->GetSubFrontend()->GetContextValue();
    } else {
        return nullptr; // Default behavior
    }
}

bool ArktsFrontend::HandleMessage(void *frameNode, int32_t type, const std::string& param)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    CHECK_NULL_RETURN(app_, false);
    CHECK_NULL_RETURN(frameNode, false);
    ani_status status = ANI_ERROR;
    if (handleMessageMethod_ == nullptr) {
        ani_class appClass;
        if ((status = env->FindClass(KOALA_APP_INFO.className, &appClass)) != ANI_OK) {
            LOGE("Call handleMessage failed due to FindClass failed, status : %{public}d", status);
            return false;
        }

        ani_method handleMessageMethod = nullptr;
        if ((status = env->Class_FindMethod(appClass, KOALA_APP_INFO.handleMessageMethodName,
            KOALA_APP_INFO.handleMessageMethodSig, &handleMessageMethod)) != ANI_OK) {
            LOGE("Call handleMessage failed due to Class_FindMethod failed, status : %{public}d", status);
            return false;
        }

        handleMessageMethod_ = handleMessageMethod;
    }

    ani_long ptrAni = reinterpret_cast<ani_long>(frameNode);
    ani_int typeAni = type;
    ani_string paramStr;
    env->String_NewUTF8(param.c_str(), param.length(), &paramStr);
    ani_boolean result;
    if ((status = env->Object_CallMethod_Boolean(static_cast<ani_object>(app_),
        handleMessageMethod_, &result, ptrAni, typeAni, paramStr)) != ANI_OK) {
        LOGE("Call handleMessage failed, status: %{public}d", status);
        return false;
    }

    return result == ANI_TRUE;
}

void ArktsFrontend::SetHostContext(int32_t instanceId, ani_ref* context)
{
    Framework::AniContextModule::AddAniContext(instanceId, context);
}

ani_ref* ArktsFrontend::GetHostContext(int32_t instanceId)
{
    return Framework::AniContextModule::GetAniContext(instanceId);
}

void ArktsFrontend::NotifyArkoalaConfigurationChange()
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(app_);
    ani_status status;
    if ((status = env->Object_CallMethodByName_Void((ani_object)app_, "notifyConfigurationChange", ":")) != ANI_OK) {
        LOGE("Call notifyConfigurationChange error");
        return;
    }
}

void ArktsFrontend::InitXBarProxy()
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    ani_class appClass;
    if (env->FindClass("C{arkui.XBarProxy.XBarProxy}", &appClass) != ANI_OK) {
        LOGE("Cannot load main class arkui.XBarProxy.XBarProxy");
        return;
    }
    ani_static_method create;
    if (env->Class_FindStaticMethod(appClass, "initializeXBarProxy", ":", &create) != ANI_OK) {
        LOGE("Cannot find create methodinitializeXBarProxy");
        return;
    }

    ani_ref result;
    if (env->Class_CallStaticMethod_Void(appClass, create, &result) != ANI_OK) {
        LOGE("initializeXBarProxy returned null");
    }
}

void* ArktsFrontend::preloadArkTSRuntime = nullptr;
void ArktsFrontend::PreloadAceModule(void* aniEnv)
{
    ArktsFrontend::preloadArkTSRuntime = aniEnv;

    auto* env = reinterpret_cast<ani_env*>(aniEnv);
    ani_class appClass;
    if (env->FindClass(KOALA_APP_INFO.className, &appClass) != ANI_OK) {
        LOGE("PreloadAceModule: Cannot load main class %{public}s", KOALA_APP_INFO.className);
        return;
    }

    ani_static_method create;
    if (env->Class_FindStaticMethod(
        appClass, KOALA_APP_INFO.registerNativeModule, KOALA_APP_INFO.registerNativeModuleSig, &create) != ANI_OK) {
        LOGE("PreloadAceModule: Cannot find method %{public}s", KOALA_APP_INFO.registerNativeModule);
        return;
    }

    ani_ref appLocal;
    env->Class_CallStaticMethod_Void(appClass, create, &appLocal);
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_PreloadAceArkTSModule(void* aniEnv)
{
    ArktsFrontend::PreloadAceModule(aniEnv);
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_GetArkTSRuntime()
{
    return ArktsFrontend::preloadArkTSRuntime;
}

ani_ref CreateStorageReference(void* runtime, void* storage)
{
    ani_ref ref = nullptr;
    if (runtime && storage) {
        auto* env = reinterpret_cast<ani_env*>(runtime);
        env->GlobalReference_Create(reinterpret_cast<ani_ref>(storage), &ref);
        if (!ref) {
            return nullptr;
        }
    }
    return ref;
}

void DeleteStorageReference(void* runtime, void* storage)
{
    if (runtime && storage) {
        auto* env = reinterpret_cast<ani_env*>(runtime);
        env->GlobalReference_Delete(reinterpret_cast<ani_object>(storage));
    }
}

extern "C" ACE_FORCE_EXPORT Frontend* OHOS_ACE_CreateArktsFrontend(void* runtime) {
    if (!runtime) {
        LOGE("runtime is nullptr.");
        return nullptr;
    }
    return static_cast<Frontend*>(new ArktsFrontend(runtime));
}

extern "C" ACE_FORCE_EXPORT void* OHOS_ACE_CreateAniReference(void* runtime, void* storage) {
    if (!runtime || !storage) {
        return nullptr;
    }
    return static_cast<void*>(CreateStorageReference(runtime, storage));
}

extern "C" ACE_FORCE_EXPORT void OHOS_ACE_DeleteAniReference(void* runtime, void* storage) {
    if (!runtime || !storage) {
        return;
    }
    DeleteStorageReference(runtime, storage);
}
} // namespace OHOS::Ace

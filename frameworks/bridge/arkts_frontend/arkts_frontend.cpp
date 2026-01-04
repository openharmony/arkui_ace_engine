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
#include "base/utils/system_properties.h"
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
    const char* constructorParamClassName;
    const char* constructorParamCtorMethod;
    const char* constructorParamSig;
};
/* copied from arkcompiler_ets_frontend vmloader.cc*/
const AppInfo KOALA_APP_INFO = {
    "arkui.ArkUIEntry.Application",
    "createApplication",
    "C{arkui.ArkUIEntry.ApplicationConstructorParam}:C{arkui.ArkUIEntry.Application}",
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
    "arkui.ArkUIEntry.ApplicationConstructorParam",
    "<ctor>",
    "C{std.core.String}C{std.core.String}C{std.core.String}zC{std.core.String}C{arkui.UserView.UserView}"
    "C{arkui.component.customComponent.EntryPoint}z:",
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

bool ParseRouterStateInfo(ani_env* env, ani_ref result, RouterStateInfo& state)
{
    ani_double index;
    ani_status status;
    ani_object stateObj = static_cast<ani_object>(result);
    if ((status = env->Object_GetPropertyByName_Double(stateObj, "index", &index)) != ANI_OK) {
        LOGE("AceRouter failed to get index of InnerRouterState, status:%{public}d", status);
        return false;
    }
    ani_ref nameRef;
    if ((status = env->Object_GetPropertyByName_Ref(stateObj, "name", &nameRef)) != ANI_OK) {
        LOGE("AceRouter failed to get name of InnerRouterState, status:%{public}d", status);
        return false;
    }
    ani_ref pathRef;
    if ((status = env->Object_GetPropertyByName_Ref(stateObj, "path", &pathRef)) != ANI_OK) {
        LOGE("AceRouter failed to get path of InnerRouterState, status:%{public}d", status);
        return false;
    }
    ani_ref paramsRef;
    if ((status = env->Object_GetPropertyByName_Ref(stateObj, "params", &paramsRef)) != ANI_OK) {
        LOGE("AceRouter failed to get params of InnerRouterState, status:%{public}d", status);
        return false;
    }
    state.index = (int32_t)index;
    state.name = Ani::AniUtils::ANIStringToStdString(env, static_cast<ani_string>(nameRef));
    state.path = Ani::AniUtils::ANIStringToStdString(env, static_cast<ani_string>(pathRef));
    state.params = Ani::AniUtils::ANIStringToStdString(env, static_cast<ani_string>(paramsRef));
    return true;
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
        if ((state = env->FindClass("Lstd/core/RuntimeLinker;", &cls)) != ANI_OK) {
            LOGE("FindClass RuntimeLinker failed, %{public}d", state);
            break;
        }

        ani_method loadClassMethod;
        if ((state = env->Class_FindMethod(cls, "loadClass", "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;",
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
        if (env->Class_FindMethod(entryClass, "<ctor>", ":V", &entryMethod) != ANI_OK) {
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

bool ArktsFrontend::Initialize(FrontendType type, const RefPtr<TaskExecutor>& taskExecutor)
{
    taskExecutor_ = taskExecutor;

    auto mediaQueryCallback = [weakEngine = AceType::WeakClaim(this)](
                                        const std::string& callbackId, const std::string& args) {
        auto arktsFrontend = weakEngine.Upgrade();
        if (!arktsFrontend) {
            return;
        }
        arktsFrontend->CallbackMediaQuery(callbackId, args);
    };
    SetMediaQueryCallback(std::move(mediaQueryCallback));

    auto navigationLoadCallback = [weakFront = WeakClaim(this)](
        const std::string bundleName, const std::string& moduleName, const std::string& pageSourceFile,
        bool isSingleton) -> int32_t {
        auto frontend = weakFront.Upgrade();
        CHECK_NULL_RETURN(frontend, -1);
        return frontend->LoadNavDestinationPage(bundleName, moduleName, pageSourceFile, isSingleton) ? 0 : -1;
    };
    auto container = Container::Current();
    if (container) {
        auto navigationRoute = container->GetNavigationRoute();
        if (navigationRoute) {
            navigationRoute->SetLoadPageCallback(std::move(navigationLoadCallback));
        }
    }

    return true;
}

bool ArktsFrontend::GetNavigationRegisterClassName(const std::string& pageSourceFile, std::string& className)
{
    /**
     * Example:
     * from pageSourceFile: @normalized:N&&&entry/src/main/ets/pages/MyPage&
     * to className: entry.src.main.ets.pages.MyPage.__NavigationBuilderRegisterClass
     */
    LOGI("AceNavigation get registerClassName with source: %{public}s", pageSourceFile.c_str());
    auto it = pageSourceFile.rfind('&');
    if (it == std::string::npos) {
        return false;
    }
    std::string tempClassName = pageSourceFile.substr(0, it);
    it = tempClassName.rfind('&');
    if (it == std::string::npos) {
        return false;
    }
    tempClassName = tempClassName.substr(it + 1);
    if (tempClassName.empty()) {
        return false;
    }
    tempClassName += "/__NavigationBuilderRegisterClass";
    std::replace(tempClassName.begin(), tempClassName.end(), '/', '.');
    className = tempClassName;
    return true;
}

bool ArktsFrontend::LoadNavDestinationPage(const std::string bundleName, const std::string& moduleName,
    const std::string& pageSourceFile, bool isSingleton)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    std::string className;
    if (!GetNavigationRegisterClassName(pageSourceFile, className)) {
        return false;
    }
    LOGI("AceNavigation registerClassName: %{public}s", className.c_str());
    if (!linkerRef_) {
        LOGW("AceNavigation no RuntimeLinker found.");
        return false;
    }
    ani_status status;
    ani_string classNameStr;
    if ((status = env->String_NewUTF8(className.c_str(), className.length(), &classNameStr)) != ANI_OK) {
        LOGW("AceNavigation create className failed, %{public}d", status);
        return false;
    }
    ani_class linkerCls = nullptr;
    if ((status = env->FindClass("Lstd/core/RuntimeLinker;", &linkerCls)) != ANI_OK) {
        LOGW("AceNavigation find RuntimeLinker failed, %{public}d", status);
        return false;
    }
    ani_method loadClassMethod;
    if ((status = env->Class_FindMethod(linkerCls, "loadClass",
        "Lstd/core/String;Lstd/core/Boolean;:Lstd/core/Class;", &loadClassMethod)) != ANI_OK) {
        LOGW("AceNavigation find loadClass failed, %{public}d", status);
        return false;
    }
    ani_object isInit;
    if ((status = static_cast<ani_status>(Ani::AniUtils::CreateAniBoolean(env, true, isInit))) != ANI_OK) {
        LOGW("AceNavigation create Boolean object failed, %{public}d", status);
        return false;
    }
    ani_ref registerClassRef = nullptr;
    if ((status = env->Object_CallMethod_Ref(
        (ani_object)linkerRef_, loadClassMethod, &registerClassRef, classNameStr, isInit)) != ANI_OK) {
        LOGW("AceNavigation loadClassMethod failed, %{public}d", status);
        ani_error errorInfo;
        env->GetUnhandledError(&errorInfo);
        env->ResetError();
        return false;
    }
    ani_class registerClass = static_cast<ani_class>(registerClassRef);
    ani_static_field staticField;
    if ((status = env->Class_FindStaticField(registerClass, "staticBlockTriggerField", &staticField)) != ANI_OK) {
        LOGW("AceNavigation find static Field failed, %{public}d", status);
        return false;
    }
    ani_boolean staticFieldValue;
    if ((status = env->Class_GetStaticField_Boolean(registerClass, staticField, &staticFieldValue)) != ANI_OK) {
        LOGW("AceNavigation get static Field value failed, %{public}d", status);
        return false;
    }
    return true;
}

bool ArktsFrontend::GetNearestNonBootRuntimeLinker()
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    ani_status status;
    ani_ref linkerRef;
    if ((status = static_cast<ani_status>(Ani::AniUtils::GetNearestNonBootRuntimeLinker(env, linkerRef))) != ANI_OK) {
        LOGW("getNearestNonBootRuntimeLinker failed, %{public}d", status);
        return false;
    }
    if ((status = env->GlobalReference_Create((ani_object)linkerRef, &linkerRef_)) != ANI_OK) {
        LOGW("create RuntimeLinker global Reference failed, %{public}d", status);
        return false;
    }
    if (!linkerRef_) {
        LOGW("get invalid RuntimeLinker!");
        return false;
    }
    return true;
}

UIContentErrorCode ArktsFrontend::RunPage(const std::string& url, const std::string& params)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, UIContentErrorCode::INVALID_URL);

    ani_class appClass;
    EntryLoader entryLoader(url, env);
    GetNearestNonBootRuntimeLinker();
    if (!pageRouterManager_) {
        pageRouterManager_ = NG::PageRouterManagerFactory::CreateManager();
    }

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
    ani_string aniName;
    env->String_NewUTF8("", 0, &aniName);

    ani_ref appLocal;
    ani_ref optionalEntry;
    env->GetUndefined(&optionalEntry);
    auto entryPointObj = url == "__INTEROP__" ? nullptr : entryLoader.GetPageEntryObj();
    auto legacyEntryPointObj = url == "__INTEROP__" ? nullptr : LegacyLoadPage(env);
    auto currentContainer = Container::Current();
    CHECK_NULL_RETURN(currentContainer, UIContentErrorCode::NULL_POINTER);
    std::string moduleName = currentContainer->GetModuleName();
    ani_string module;
    env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &module);
    ani_boolean enableDebug = ani_boolean(SystemProperties::GetDebugEnabled());
    ani_class appConstructorParamClass;
    if (env->FindClass(KOALA_APP_INFO.constructorParamClassName, &appConstructorParamClass) != ANI_OK) {
        LOGE("Cannot load class %{public}s", KOALA_APP_INFO.constructorParamClassName);
        return UIContentErrorCode::INVALID_URL;
    }
    ani_method paramConstructor;
    if (env->Class_FindMethod(appConstructorParamClass, KOALA_APP_INFO.constructorParamCtorMethod,
        KOALA_APP_INFO.constructorParamSig, &paramConstructor) != ANI_OK) {
        LOGE("Cannot find create method %{public}s", KOALA_APP_INFO.constructorParamCtorMethod);
        return UIContentErrorCode::INVALID_URL;
    }
    ani_object param;
    if (env->Object_New(appConstructorParamClass, paramConstructor, &param, aniUrl, aniParams, aniName, false, module,
        legacyEntryPointObj ? legacyEntryPointObj : optionalEntry, entryPointObj ? entryPointObj : optionalEntry,
        enableDebug) != ANI_OK) {
        LOGE("Fail to create ApplicationConstructorParam");
        return UIContentErrorCode::INVALID_URL;
    }
    if (env->Class_CallStaticMethod_Ref(appClass, create, &appLocal, param) != ANI_OK) {
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

UIContentErrorCode ArktsFrontend::RunPageByNamedRouter(const std::string& name, const std::string& params)
{
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, UIContentErrorCode::INVALID_URL);
    ani_class appClass;
    GetNearestNonBootRuntimeLinker();
    if (!pageRouterManager_) {
        pageRouterManager_ = NG::PageRouterManagerFactory::CreateManager();
    }
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
    env->String_NewUTF8("", 0, &aniUrl);
    ani_string aniParams;
    env->String_NewUTF8(params.c_str(), params.size(), &aniParams);
    ani_string aniName;
    env->String_NewUTF8(name.c_str(), name.size(), &aniName);
    ani_ref appLocal;
    ani_ref optionalEntry;
    env->GetUndefined(&optionalEntry);
    auto currentContainer = Container::Current();
    CHECK_NULL_RETURN(currentContainer, UIContentErrorCode::NULL_POINTER);
    std::string moduleName = currentContainer->GetModuleName();
    ani_string module;
    env->String_NewUTF8(moduleName.c_str(), moduleName.size(), &module);
    ani_boolean enableDebug = ani_boolean(SystemProperties::GetDebugEnabled());
    ani_class appConstructorParamClass;
    if (env->FindClass(KOALA_APP_INFO.constructorParamClassName, &appConstructorParamClass) != ANI_OK) {
        LOGE("Cannot load class %{public}s", KOALA_APP_INFO.constructorParamClassName);
        return UIContentErrorCode::INVALID_URL;
    }
    ani_method paramConstructor;
    if (env->Class_FindMethod(appConstructorParamClass, KOALA_APP_INFO.constructorParamCtorMethod,
        KOALA_APP_INFO.constructorParamSig, &paramConstructor) != ANI_OK) {
        LOGE("Cannot find create method %{public}s", KOALA_APP_INFO.constructorParamCtorMethod);
        return UIContentErrorCode::INVALID_URL;
    }
    ani_object param;
    if (env->Object_New(appConstructorParamClass, paramConstructor, &param, aniUrl, aniParams, aniName, false, module,
        optionalEntry, optionalEntry, enableDebug) != ANI_OK) {
        LOGE("Fail to create ApplicationConstructorParam");
        return UIContentErrorCode::INVALID_URL;
    }
    if (env->Class_CallStaticMethod_Ref(appClass, create, &appLocal, param) != ANI_OK) {
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

void* ArktsFrontend::PushExtender(const std::string& url, const std::string& params, bool recoverable,
    std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    auto pageNode = pageRouterManager_->PushExtender(routerPageInfo, std::move(finishCallback), jsNode);
    return pageNode.GetRawPtr();
}

void ArktsFrontend::PushNamedRouteExtender(
    const PageRouterOptions& options, std::function<void()>&& finishCallback, void* jsNode)
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

void* ArktsFrontend::CreateDynamicExtender(const std::string& url, bool recoverable)
{
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    auto subFrontend = subFrontend_.Upgrade();
    CHECK_NULL_RETURN(subFrontend, nullptr);
    auto pageId = pageRouterManager_->GenerateNextPageId();
    isUseSubFrontendManagerNeeded_ = true;
    auto* pageNode = subFrontend->CreateDynamicPage(pageId, url, "", recoverable);
    isUseSubFrontendManagerNeeded_ = false;
    CHECK_NULL_RETURN(pageNode, nullptr);
    return pageNode;
}

void* ArktsFrontend::PushDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
    std::function<void()>&& finishCallback, void* pageNodeRawPtr)
{
    CHECK_NULL_RETURN(pageNodeRawPtr, nullptr);
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    auto pageNode = AceType::WeakClaim(static_cast<NG::FrameNode*>(pageNodeRawPtr)).Upgrade();
    CHECK_NULL_RETURN(pageNode, nullptr);
    if (pageNode->RefCount() != 2) {
        LOGE("AceRouter pageNode for PushDynamicExtender has wrong RefCount: %{public}d", pageNode->RefCount());
    }
    if (pageNode->RefCount() > 1) {
        pageNode->DecRefCount();
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    pageNode = pageRouterManager_->PushDynamicExtender(
        routerPageInfo, std::move(finishCallback), pageNode);
    return pageNodeRawPtr;
}

void* ArktsFrontend::ReplaceDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
        std::function<void()>&& finishCallback, void* pageNodeRawPtr)
{
    CHECK_NULL_RETURN(pageNodeRawPtr, nullptr);
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    auto pageNode = AceType::WeakClaim(static_cast<NG::FrameNode*>(pageNodeRawPtr)).Upgrade();
    CHECK_NULL_RETURN(pageNode, nullptr);
    if (pageNode->RefCount() != 2) {
        LOGE("AceRouter pageNode for ReplaceDynamicExtender has wrong RefCount: %{public}d", pageNode->RefCount());
    }
    if (pageNode->RefCount() > 1) {
        pageNode->DecRefCount();
    }
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    pageNode = pageRouterManager_->ReplaceDynamicExtender(
        routerPageInfo, std::move(finishCallback), pageNode);
    return pageNodeRawPtr;
}

void ArktsFrontend::PushFromDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
    const std::function<void(const std::string&, int32_t)>& callback, uint32_t routerMode)
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(linkerRef_);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return;
    }
    ani_static_method pushFromDynamicMethod;
    const char* methodName = "pushFromDynamic";
    const char* methodMangling = "iC{std.core.String}C{std.core.String}C{std.core.RuntimeLinker}:";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &pushFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return;
    }
    ani_string urlStr;
    if ((status = env->String_NewUTF8(url.c_str(), url.size(), &urlStr)) != ANI_OK) {
        LOGE("AceRouter failed to create url string, status:%{public}d", status);
        return;
    }
    ani_string paramStr;
    if ((status = env->String_NewUTF8(params.c_str(), params.size(), &paramStr)) != ANI_OK) {
        LOGE("AceRouter failed to create params string, status:%{public}d", status);
        return;
    }
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Void(routerUtilCls, pushFromDynamicMethod,
        static_cast<ani_int>(instanceId), urlStr, paramStr, (ani_object)linkerRef_)) != ANI_OK) {
        LOGE("AceRouter failed to call pushFromDynamic, status:%{public}d", status);
        return;
    }
}

void ArktsFrontend::ReplaceFromDynamicExtender(const std::string& url, const std::string& params, bool recoverable,
    const std::function<void(const std::string&, int32_t)>& callback, uint32_t routerMode)
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(linkerRef_);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return;
    }
    ani_static_method replaceFromDynamicMethod;
    const char* methodName = "replaceFromDynamic";
    const char* methodMangling = "iC{std.core.String}C{std.core.String}C{std.core.RuntimeLinker}:";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &replaceFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return;
    }
    ani_string urlStr;
    if ((status = env->String_NewUTF8(url.c_str(), url.size(), &urlStr)) != ANI_OK) {
        LOGE("AceRouter failed to create url string, status:%{public}d", status);
        return;
    }
    ani_string paramStr;
    if ((status = env->String_NewUTF8(params.c_str(), params.size(), &paramStr)) != ANI_OK) {
        LOGE("AceRouter failed to create params string, status:%{public}d", status);
        return;
    }
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Void(routerUtilCls, replaceFromDynamicMethod,
        static_cast<ani_int>(instanceId), urlStr, paramStr, (ani_object)linkerRef_)) != ANI_OK) {
        LOGE("AceRouter failed to call replaceFromDynamic, status:%{public}d", status);
        return;
    }
}

void ArktsFrontend::BackFromDynamicExtender(const std::string& url, const std::string& params)
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(linkerRef_);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return;
    }
    ani_static_method backFromDynamicMethod;
    const char* methodName = "backFromDynamic";
    const char* methodMangling = "iC{std.core.String}C{std.core.String}C{std.core.RuntimeLinker}:";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &backFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return;
    }
    ani_string urlStr;
    if ((status = env->String_NewUTF8(url.c_str(), url.size(), &urlStr)) != ANI_OK) {
        LOGE("AceRouter failed to create url string, status:%{public}d", status);
        return;
    }
    ani_string paramStr;
    if ((status = env->String_NewUTF8(params.c_str(), params.size(), &paramStr)) != ANI_OK) {
        LOGE("AceRouter failed to create params string, status:%{public}d", status);
        return;
    }
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Void(routerUtilCls, backFromDynamicMethod,
        static_cast<ani_int>(instanceId), urlStr, paramStr, (ani_object)linkerRef_)) != ANI_OK) {
        LOGE("AceRouter failed to call backFromDynamic, status:%{public}d", status);
        return;
    }
}

void ArktsFrontend::ClearFromDynamicExtender()
{
    CHECK_NULL_VOID(vm_);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_VOID(env);
    CHECK_NULL_VOID(linkerRef_);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return;
    }
    ani_static_method clearFromDynamicMethod;
    const char* methodName = "clearFromDynamic";
    const char* methodMangling = "iC{std.core.RuntimeLinker}:";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &clearFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return;
    }
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Void(routerUtilCls, clearFromDynamicMethod,
        static_cast<ani_int>(instanceId), (ani_object)linkerRef_)) != ANI_OK) {
        LOGE("AceRouter failed to call clearFromDynamic, status:%{public}d", status);
        return;
    }
}

int32_t ArktsFrontend::GetLengthFromDynamicExtender()
{
    CHECK_NULL_RETURN(vm_, 0);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, 0);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return 0;
    }
    ani_static_method getLengthFromDynamicMethod;
    const char* methodName = "getLengthFromDynamic";
    const char* methodMangling = "i:C{std.core.String}";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getLengthFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return 0;
    }
    ani_ref resultStr;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Ref(routerUtilCls, getLengthFromDynamicMethod,
        &resultStr, static_cast<ani_int>(instanceId))) != ANI_OK) {
        LOGE("AceRouter failed to call getLengthFromDynamic, status:%{public}d", status);
        return 0;
    }
    auto lengthStr = Ani::AniUtils::ANIStringToStdString(env, reinterpret_cast<ani_string>(resultStr));
    int32_t length = std::atoi(lengthStr.c_str());
    return length;
}

int32_t ArktsFrontend::GetStackSizeFromDynamicExtender()
{
    CHECK_NULL_RETURN(vm_, 0);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, 0);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return 0;
    }
    ani_static_method getStackSizeFromDynamicMethod;
    const char* methodName = "getStackSizeFromDynamic";
    const char* methodMangling = "i:i";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getStackSizeFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return 0;
    }
    ani_int result;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Int(routerUtilCls, getStackSizeFromDynamicMethod,
        &result, static_cast<ani_int>(instanceId))) != ANI_OK) {
        LOGE("AceRouter failed to call getStackSizeFromDynamic, status:%{public}d", status);
        return 0;
    }
    return static_cast<int>(result);
}

std::string ArktsFrontend::GetParamsFromDynamicExtender()
{
    CHECK_NULL_RETURN(vm_, "");
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, "");
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return "";
    }
    ani_static_method getParamsFromDynamicMethod;
    const char* methodName = "getParamsFromDynamic";
    const char* methodMangling = "i:C{std.core.String}";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getParamsFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return "";
    }
    ani_ref resultStr;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Ref(routerUtilCls, getParamsFromDynamicMethod,
        &resultStr, static_cast<ani_int>(instanceId))) != ANI_OK) {
        LOGE("AceRouter failed to call %{public}s, status:%{public}d", methodName, status);
        return "";
    }
    auto paramsStr = Ani::AniUtils::ANIStringToStdString(env, reinterpret_cast<ani_string>(resultStr));
    return paramsStr;
}

bool ArktsFrontend::GetStateByUrlFromDynamicExtender(const std::string& url, std::vector<RouterStateInfo>& stateArray)
{
    CHECK_NULL_RETURN(vm_, false);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return false;
    }
    ani_static_method getStateByUrlFromDynamicMethod;
    const char* methodName = "getStateByUrlFromDynamic";
    const char* methodMangling = "iC{std.core.String}:C{std.core.Array}";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getStateByUrlFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_string urlStr;
    if ((status = env->String_NewUTF8(url.c_str(), url.size(), &urlStr)) != ANI_OK) {
        LOGE("AceRouter failed to create url string, status:%{public}d", status);
        return false;
    }
    ani_ref resultArray;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Ref(routerUtilCls, getStateByUrlFromDynamicMethod,
        &resultArray, static_cast<ani_int>(instanceId), urlStr)) != ANI_OK) {
        LOGE("AceRouter failed to call %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_size stateCount = 0;
    if ((status = env->Array_GetLength(static_cast<ani_array>(resultArray), &stateCount)) != ANI_OK) {
        LOGE("AceRouter failed to get Array length, status:%{public}d", status);
        return false;
    }
    std::vector<RouterStateInfo> tempStates;
    for (ani_size idx = 0; idx < stateCount; ++idx) {
        ani_ref result;
        if ((status = env->Array_Get(static_cast<ani_array>(resultArray), idx, &result)) != ANI_OK) {
            LOGE("AceRouter failed to get Array item[%{public}d], status:%{public}d", (int32_t)idx, status);
            return false;
        }
        RouterStateInfo state;
        if (!ParseRouterStateInfo(env, result, state)) {
            return false;
        }
        tempStates.push_back(state);
    }
    std::swap(tempStates, stateArray);
    LOGE("AceRouter GetStateByUrlFromDynamicExtender 2");
    return true;
}

bool ArktsFrontend::GetStateByIndexFromDynamicExtender(int32_t index, RouterStateInfo& state)
{
    CHECK_NULL_RETURN(vm_, false);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return false;
    }
    ani_static_method getStateByIndexFromDynamicMethod;
    const char* methodName = "getStateByIndexFromDynamic";
    const char* methodMangling = "ii:C{arkui.base.Router.InnerRouterState}";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getStateByIndexFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_ref result;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Ref(routerUtilCls, getStateByIndexFromDynamicMethod,
        &result, static_cast<ani_int>(instanceId), static_cast<ani_int>(index))) != ANI_OK) {
        LOGE("AceRouter failed to call %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_boolean isUndefined;
    if ((status = env->Reference_IsUndefined(result, &isUndefined)) != ANI_OK) {
        LOGE("AceRouter failed to call Reference_IsUndefined, status:%{public}d", status);
        return false;
    }
    if (isUndefined) {
        LOGE("AceRouter GetStateByIndexFromDynamicExtender 1");
        return false;
    }
    LOGE("AceRouter GetStateByIndexFromDynamicExtender 2");
    return ParseRouterStateInfo(env, result, state);
}

bool ArktsFrontend::GetStateFromDynamicExtender(RouterStateInfo& state)
{
    CHECK_NULL_RETURN(vm_, false);
    auto* env = Ani::AniUtils::GetAniEnv(vm_);
    CHECK_NULL_RETURN(env, false);
    ani_status status;
    ani_class routerUtilCls;
    const char* clsMangling = "arkui.base.Router.RouterUtil";
    if ((status = env->FindClass(clsMangling, &routerUtilCls)) != ANI_OK) {
        LOGE("AceRouter Cannot find class: %{public}s, status:%{public}d", clsMangling, status);
        return false;
    }
    ani_static_method getStateFromDynamicMethod;
    const char* methodName = "getStateFromDynamic";
    const char* methodMangling = "i:C{arkui.base.Router.InnerRouterState}";
    if ((status = env->Class_FindStaticMethod(
        routerUtilCls, methodName, methodMangling, &getStateFromDynamicMethod)) != ANI_OK) {
        LOGE("AceRouter Cannot find method: %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_ref result;
    auto instanceId = Container::CurrentIdSafely();
    if ((status = env->Class_CallStaticMethod_Ref(routerUtilCls, getStateFromDynamicMethod,
        &result, static_cast<ani_int>(instanceId))) != ANI_OK) {
        LOGE("AceRouter failed to call %{public}s, status:%{public}d", methodName, status);
        return false;
    }
    ani_boolean isUndefined;
    if ((status = env->Reference_IsUndefined(result, &isUndefined)) != ANI_OK) {
        LOGE("AceRouter failed to call Reference_IsUndefined, status:%{public}d", status);
        return false;
    }
    if (isUndefined) {
        return false;
    }
    return ParseRouterStateInfo(env, result, state);
}

int32_t ArktsFrontend::GetCurrentPageIndex() const
{
    CHECK_NULL_RETURN(pageRouterManager_, -1);
    return pageRouterManager_->GetCurrentPageIndex();
}

void* ArktsFrontend::ReplaceExtender(const std::string& url, const std::string& params, bool recoverable,
    std::function<void()>&& enterFinishCallback, void* jsNode)
{
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    auto pageNode = pageRouterManager_->ReplaceExtender(routerPageInfo, std::move(enterFinishCallback), jsNode);
    return pageNode.GetRawPtr();
}

void ArktsFrontend::ReplaceNamedRouteExtender(
    const PageRouterOptions& options, std::function<void()>&& finishCallback, void* jsNode)
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

void* ArktsFrontend::RunPageExtender(const std::string& url, const std::string& params, bool recoverable,
    std::function<void()>&& finishCallback, void* jsNode)
{
    CHECK_NULL_RETURN(pageRouterManager_, nullptr);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    routerPageInfo.recoverable = recoverable;
    auto pageNode = pageRouterManager_->RunPageExtender(routerPageInfo, std::move(finishCallback), jsNode);
    return pageNode.GetRawPtr();
}

void ArktsFrontend::BackExtender(const std::string& url, const std::string& params)
{
    CHECK_NULL_VOID(pageRouterManager_);
    NG::RouterPageInfo routerPageInfo;
    routerPageInfo.url = url;
    routerPageInfo.params = params;
    pageRouterManager_->BackWithTarget(routerPageInfo);
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

    static const char* moduleName = "Larkui/component/interop;";
    ani_module interopModule;
    state = env->FindModule(moduleName, &interopModule);
    if (state != ANI_OK) {
        LOGE("Cannot find module arkui.component.interop %{public}d", state);
        return;
    }

    ani_function fn;
    state = env->Module_FindFunction(interopModule, "openInterop", ":V", &fn);
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
    std::shared_ptr<ani_ref> shared_ptr(context);
    Framework::AniContextModule::AddAniContext(instanceId, shared_ptr);
}

ani_ref* ArktsFrontend::GetHostContext()
{
    return Framework::AniContextModule::GetAniContext().get();
}

void ArktsFrontend::NotifyArkoalaConfigurationChange(bool isNeedUpdate)
{
    if (!isNeedUpdate) {
        return;
    }
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

void ArktsFrontend::OnLayoutChildrenCompleted(const std::string& componentId)
{
    auto iter = layoutChildrenCallbacks_.find(componentId);
    if (iter == layoutChildrenCallbacks_.end()) {
        return;
    }
    if (taskExecutor_ == nullptr) {
        return;
    }
    auto&& observer = iter->second;
    taskExecutor_->PostTask([observer] { (*observer)(); }, TaskExecutor::TaskType::JS, "ArkUIDrawChildrenCompleted");
}

bool ArktsFrontend::IsLayoutChildrenCallbackFuncExist(const std::string& componentId)
{
    auto iter = layoutChildrenCallbacks_.find(componentId);
    if (iter == layoutChildrenCallbacks_.end()) {
        return false;
    }
    return iter->second->HasCallback();
}

void ArktsFrontend::OnLayoutCompleted(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutCallbacks_.find(uniqueId);
    if (iter == uniqueIdLayoutCallbacks_.end()) {
        return;
    }
    if (taskExecutor_ == nullptr) {
        return;
    }
    auto&& observer = iter->second;
    taskExecutor_->PostTask([observer] { (*observer)(); }, TaskExecutor::TaskType::JS, "ArkUILayoutCompleted");
}

void ArktsFrontend::OnDrawCompleted(int32_t uniqueId)
{
    auto iter = uniqueIdDrawCallbacks_.find(uniqueId);
    if (iter == uniqueIdDrawCallbacks_.end()) {
        return;
    }
    if (taskExecutor_ == nullptr) {
        return;
    }
    auto&& observer = iter->second;
    taskExecutor_->PostTask([observer] { (*observer)(); }, TaskExecutor::TaskType::JS, "ArkUIDrawCompleted");
}

void ArktsFrontend::OnDrawChildrenCompleted(int32_t uniqueId)
{
    auto iter = uniqueIdDrawChildrenCallbacks_.find(uniqueId);
    if (iter == uniqueIdDrawChildrenCallbacks_.end()) {
        return;
    }
    if (taskExecutor_ == nullptr) {
        return;
    }
    auto&& observer = iter->second;
    taskExecutor_->PostTask([observer] { (*observer)(); }, TaskExecutor::TaskType::JS, "ArkUIDrawChildrenCompleted");
}

void ArktsFrontend::OnLayoutChildrenCompleted(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutChildrenCallbacks_.find(uniqueId);
    if (iter == uniqueIdLayoutChildrenCallbacks_.end()) {
        return;
    }
    if (taskExecutor_ == nullptr) {
        return;
    }
    auto&& observer = iter->second;
    taskExecutor_->PostTask([observer] { (*observer)(); }, TaskExecutor::TaskType::JS, "ArkUIDrawChildrenCompleted");
}

bool ArktsFrontend::IsDrawChildrenCallbackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdDrawChildrenCallbacks_.find(uniqueId);
    if (iter == uniqueIdDrawChildrenCallbacks_.end()) {
        return false;
    }
    return iter->second->HasCallback();
}

bool ArktsFrontend::IsLayoutChildrenCallbackFuncExist(int32_t uniqueId)
{
    auto iter = uniqueIdLayoutChildrenCallbacks_.find(uniqueId);
    if (iter == uniqueIdLayoutChildrenCallbacks_.end()) {
        return false;
    }
    return iter->second->HasCallback();
}

void ArktsFrontend::RegisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenFunc, const std::string& componentId)
{
    layoutChildrenCallbacks_[componentId] = layoutChildrenFunc;
}

void ArktsFrontend::RegisterLayoutInspectorCallback(const RefPtr<InspectorEvent>& layoutFunc, int32_t uniqueId)
{
    uniqueIdLayoutCallbacks_[uniqueId] = layoutFunc;
}

void ArktsFrontend::RegisterDrawInspectorCallback(const RefPtr<InspectorEvent>& drawFunc, int32_t uniqueId)
{
    uniqueIdDrawCallbacks_[uniqueId] = drawFunc;
}

void ArktsFrontend::RegisterDrawChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& drawChildrenFunc, int32_t uniqueId)
{
    uniqueIdDrawChildrenCallbacks_[uniqueId] = drawChildrenFunc;
}

void ArktsFrontend::RegisterLayoutChildrenInspectorCallback(
    const RefPtr<InspectorEvent>& layoutChildrenFunc, int32_t uniqueId)
{
    uniqueIdLayoutChildrenCallbacks_[uniqueId] = layoutChildrenFunc;
}

void ArktsFrontend::UnregisterLayoutChildrenInspectorCallback(const std::string& componentId)
{
    layoutChildrenCallbacks_.erase(componentId);
}

void ArktsFrontend::UnregisterLayoutInspectorCallback(int32_t uniqueId)
{
    uniqueIdLayoutCallbacks_.erase(uniqueId);
}

void ArktsFrontend::UnregisterDrawInspectorCallback(int32_t uniqueId)
{
    uniqueIdDrawCallbacks_.erase(uniqueId);
}

void ArktsFrontend::UnregisterDrawChildrenInspectorCallback(const int32_t uniqueId)
{
    uniqueIdDrawChildrenCallbacks_.erase(uniqueId);
}

void ArktsFrontend::UnregisterLayoutChildrenInspectorCallback(const int32_t uniqueId)
{
    uniqueIdLayoutChildrenCallbacks_.erase(uniqueId);
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

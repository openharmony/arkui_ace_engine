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

#include "core/components_ng/pattern/patternlock/patternlock_napi.h"

#include "base/utils/utils.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/common_napi_utils/common_napi_utils.h"
#include "core/components_ng/pattern/patternlock/pattern_lock_controller.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"
#include "core/components_v2/pattern_lock/pattern_lock_theme.h"

extern const char _binary_arkui_patternlock_js_start[];
extern const char _binary_arkui_patternlock_abc_start[];
#if !defined(IOS_PLATFORM)
extern const char _binary_arkui_patternlock_js_end[];
extern const char _binary_arkui_patternlock_abc_end[];
#else
extern const char* _binary_arkui_patternlock_js_end;
extern const char* _binary_arkui_patternlock_abc_end;
#endif

namespace OHOS::Ace {
namespace {
static constexpr const size_t MAX_ARG_NUM = 10;
} // namespace
std::unique_ptr<PatternLockModel> PatternLockModel::instance_ = nullptr;
std::mutex PatternLockModel::mutex_;

template<typename T>
RefPtr<T> GetTheme()
{
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, nullptr);
    auto themeManager = pipelineContext->GetThemeManager();
    CHECK_NULL_RETURN(themeManager, nullptr);
    return themeManager->GetTheme<T>();
}

PatternLockModel* PatternLockModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::PatternLockModelNG());
        }
    }
    return instance_.get();
}

bool AutoResetResult(napi_env env, napi_value value)
{
    bool autoReset = true;
    napi_valuetype valueType = CommonNapiUtils::GetValueType(env, value);
    if (valueType == napi_boolean) {
        autoReset = CommonNapiUtils::GetBool(env, value);
    }

    return autoReset;
}

napi_value Create(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    PatternLockController* wrapper = nullptr;
    napi_unwrap(env, argv[0], (void**)&wrapper);
    auto controller = PatternLockModel::GetInstance()->Create();
    if (controller) {
        wrapper->SetController(controller);
    }
    return CommonNapiUtils::CreateNull(env);
}

napi_value SideLength(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    CalcDimension sideLength;
    if (!CommonNapiUtils::GetDimensionResult(env, argv[0], sideLength)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        sideLength = patternLockTheme->GetSideLength();
    }
    PatternLockModel::GetInstance()->SetSideLength(sideLength);
    return CommonNapiUtils::CreateNull(env);
}

napi_value CircleRadius(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    CalcDimension radius;
    if (!CommonNapiUtils::GetDimensionResult(env, argv[0], radius) || radius.IsNonPositive()) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        radius = patternLockTheme->GetCircleRadius();
    }
    PatternLockModel::GetInstance()->SetCircleRadius(radius);
    return CommonNapiUtils::CreateNull(env);
}

napi_value PathStrokeWidth(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    CalcDimension lineWidth;
    if (!CommonNapiUtils::GetDimensionResult(env, argv[0], lineWidth)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        lineWidth = patternLockTheme->GetPathStrokeWidth();
    }
    PatternLockModel::GetInstance()->SetStrokeWidth(lineWidth);
    return CommonNapiUtils::CreateNull(env);
}

napi_value ActiveColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "PatternLockModelNapi activeColor wrong number of arguments");

    Color activeColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], activeColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        activeColor = patternLockTheme->GetActiveColor();
    }
    PatternLockModel::GetInstance()->SetActiveColor(activeColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value SelectedColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "PatternLockModelNapi selectedColor Wrong number of arguments");

    Color selectedColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], selectedColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        selectedColor = patternLockTheme->GetSelectedColor();
    }
    PatternLockModel::GetInstance()->SetSelectedColor(selectedColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value PathColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "PatternLockModelNapi pathColor Wrong number of arguments");

    Color pathColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], pathColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        pathColor = patternLockTheme->GetPathColor();
    }
    PatternLockModel::GetInstance()->SetPathColor(pathColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value RegularColor(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "PatternLockModelNapi regularColor Wrong number of arguments");
    Color regularColor;
    if (!CommonNapiUtils::ParseColor(env, argv[0], regularColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_RETURN(patternLockTheme, CommonNapiUtils::CreateNull(env));
        regularColor = patternLockTheme->GetRegularColor();
    }
    PatternLockModel::GetInstance()->SetRegularColor(regularColor);
    return CommonNapiUtils::CreateNull(env);
}

napi_value AutoReset(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "PatternLockModelNapi autoReset Wrong number of arguments");

    bool autoReset = AutoResetResult(env, argv[0]);
    PatternLockModel::GetInstance()->SetAutoReset(autoReset);
    return CommonNapiUtils::CreateNull(env);
}

napi_value OnPatternComplete(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    napi_ref callback = nullptr;
    napi_valuetype valuetype;
    NAPI_CALL(env, napi_typeof(env, argv[0], &valuetype));
    NAPI_ASSERT(env, valuetype == napi_function, "Wrong argument type. Function expected.");
    auto asyncEvent = std::make_shared<NapiAsyncEvnet>(env, argv[0]);
    auto onComplete = [asyncEvent](const BaseEventInfo* info) {
        napi_value arrayValue;
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(info);
        CHECK_NULL_VOID(eventInfo);
        arrayValue = CommonNapiUtils::CreateArray(asyncEvent->GetEnv());
        std::vector<int> arr = eventInfo->GetInput();
        for (size_t i = 0; i < arr.size(); i++) {
            CommonNapiUtils::SetSelementToArray(
                asyncEvent->GetEnv(), arrayValue, i, CommonNapiUtils::CreateInt32(asyncEvent->GetEnv(), arr.at(i)));
        }
        napi_value argv[1] = { arrayValue };
        asyncEvent->Call(1, argv);
    };
    PatternLockModel::GetInstance()->SetPatternComplete(std::move(onComplete));
    return CommonNapiUtils::CreateNull(env);
}

napi_value Reset(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, NULL));
    PatternLockController* wrapper = nullptr;
    napi_unwrap(env, thisVar, (void**)&wrapper);
    if (wrapper == nullptr) {
        return CommonNapiUtils::CreateNull(env);
    }
    wrapper->Reset();
    return CommonNapiUtils::CreateNull(env);
}

napi_value PatternLockControllerConstructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    auto wrapper = new (std::nothrow) PatternLockController();
    if (wrapper == nullptr) {
        return CommonNapiUtils::CreateNull(env);
    }
    napi_wrap(
        env, thisVar, wrapper,
        [](napi_env env, void* data, void* hint) {
            auto* wrapper = reinterpret_cast<PatternLockController*>(data);
            delete wrapper;
            wrapper = nullptr;
        },
        nullptr, nullptr);
    return thisVar;
}

napi_value Init(napi_env env, napi_value exports)
{
    static napi_property_descriptor desc[] = { DECLARE_NAPI_FUNCTION("create", Create),
        DECLARE_NAPI_FUNCTION("sideLength", SideLength), DECLARE_NAPI_FUNCTION("circleRadius", CircleRadius),
        DECLARE_NAPI_FUNCTION("pathStrokeWidth", PathStrokeWidth), DECLARE_NAPI_FUNCTION("activeColor", ActiveColor),
        DECLARE_NAPI_FUNCTION("selectedColor", SelectedColor), DECLARE_NAPI_FUNCTION("pathColor", PathColor),
        DECLARE_NAPI_FUNCTION("regularColor", RegularColor), DECLARE_NAPI_FUNCTION("autoReset", AutoReset),
        DECLARE_NAPI_FUNCTION("onPatternComplete", OnPatternComplete) };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value InitController(napi_env env, napi_value exports)
{
    napi_value patternLockControllerClass = nullptr;
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("reset", Reset),
    };
    NAPI_CALL(env, napi_define_class(env, "PatternLockController", NAPI_AUTO_LENGTH, PatternLockControllerConstructor,
                       nullptr, sizeof(properties) / sizeof(*properties), properties, &patternLockControllerClass));
    NAPI_CALL(env, napi_set_named_property(env, exports, "PatternLockController", patternLockControllerClass));
    return exports;
}
} // namespace OHOS::Ace

extern "C" __attribute__((visibility("default"))) void NAPI_arkui_patternlock_GetJSCode(const char** buf, int* bufLen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_patternlock_js_start;
    }

    if (bufLen != nullptr) {
        *bufLen = _binary_arkui_patternlock_js_end - _binary_arkui_patternlock_js_start;
    }
}

// arkui_patternlock JS register
extern "C" __attribute__((visibility("default"))) void NAPI_arkui_patternlock_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_patternlock_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_patternlock_abc_end - _binary_arkui_patternlock_abc_start;
    }
}

static napi_module_with_js modules = {
    .nm_filename = "arkui/libpatternlock.z.so/arkui_patternlock.js",
    .nm_version = 1,
    .nm_flags = 0,
    .nm_register_func = OHOS::Ace::Init,
    .nm_modname = "arkui.patternlock",
    .nm_priv = ((void*)0),
    .nm_get_abc_code = NAPI_arkui_patternlock_GetABCCode,
    .nm_get_js_code = NAPI_arkui_patternlock_GetJSCode,
};

static napi_module patternLockControllerModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OHOS::Ace::InitController,
    .nm_modname = "arkui.patternlockcontroller",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterModule()
{
    napi_module_register(&patternLockControllerModule);
    napi_module_with_js_register(&modules);
}

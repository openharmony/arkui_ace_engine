/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include <memory>
#include <string>

#include "animator_option.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "napi/native_api.h"
#include "napi/native_engine/native_value.h"
#include "napi/native_node_api.h"

#include "base/log/log.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "bridge/common/utils/utils.h"
#include "core/animation/animator.h"
#include "core/animation/curve.h"
#include "core/animation/curve_animation.h"

namespace OHOS::Ace::Napi {

static void ParseString(napi_env env, napi_value propertyNapi, std::string& property)
{
    if (propertyNapi != nullptr) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, propertyNapi, &valueType);
        if (valueType == napi_undefined) {
            NapiThrow(env, "Required input parameters are missing.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        } else if (valueType != napi_string) {
            NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        }
        auto nativeProperty = reinterpret_cast<NativeValue*>(propertyNapi);
        auto resultProperty = nativeProperty->ToString();
        auto nativeStringProperty =
            reinterpret_cast<NativeString*>(resultProperty->GetInterface(NativeString::INTERFACE_ID));
        size_t propertyLen = nativeStringProperty->GetLength() + 1;
        std::unique_ptr<char[]> propertyString = std::make_unique<char[]>(propertyLen);
        size_t retLen = 0;
        napi_get_value_string_utf8(env, propertyNapi, propertyString.get(), propertyLen, &retLen);
        property = propertyString.get();
    }
}

static void ParseInt(napi_env env, napi_value propertyNapi, int32_t& property)
{
    if (propertyNapi != nullptr) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, propertyNapi, &valueType);
        if (valueType == napi_undefined) {
            NapiThrow(env, "Required input parameters are missing.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        } else if (valueType != napi_number) {
            NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        }
        napi_get_value_int32(env, propertyNapi, &property);
    }
}

static void ParseDouble(napi_env env, napi_value propertyNapi, double& property)
{
    if (propertyNapi != nullptr) {
        napi_valuetype valueType = napi_undefined;
        napi_typeof(env, propertyNapi, &valueType);
        if (valueType == napi_undefined) {
            NapiThrow(env, "Required input parameters are missing.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        } else if (valueType != napi_number) {
            NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
            return;
        }
        napi_get_value_double(env, propertyNapi, &property);
    }
}

static FillMode StringToFillMode(const std::string& fillMode)
{
    if (fillMode.compare("forwards") == 0) {
        return FillMode::FORWARDS;
    } else if (fillMode.compare("backwards") == 0) {
        return FillMode::BACKWARDS;
    } else if (fillMode.compare("both") == 0) {
        return FillMode::BOTH;
    } else {
        return FillMode::NONE;
    }
}

static AnimationDirection StringToAnimationDirection(const std::string& direction)
{
    if (direction.compare("alternate") == 0) {
        return AnimationDirection::ALTERNATE;
    } else if (direction.compare("reverse") == 0) {
        return AnimationDirection::REVERSE;
    } else if (direction.compare("alternate-reverse") == 0) {
        return AnimationDirection::ALTERNATE_REVERSE;
    } else {
        return AnimationDirection::NORMAL;
    }
}

static void ParseAnimatorOption(napi_env env, napi_callback_info info, std::shared_ptr<AnimatorOption>& option)
{
    LOGI("JsAnimator: ParseAnimatorOption");
    size_t argc = 1;
    napi_value argv;
    napi_get_cb_info(env, info, &argc, &argv, NULL, NULL);
    if (argc != 1) {
        NapiThrow(env, "The number of parameters must be equal to 1.", Framework::ERROR_CODE_PARAM_INVALID);
        return;
    }
    napi_value durationNapi = nullptr;
    napi_value easingNapi = nullptr;
    napi_value delayNapi = nullptr;
    napi_value fillNapi = nullptr;
    napi_value directionNapi = nullptr;
    napi_value iterationsNapi = nullptr;
    napi_value beginNapi = nullptr;
    napi_value endNapi = nullptr;
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv, &valueType);
    if (valueType == napi_object) {
        napi_get_named_property(env, argv, "duration", &durationNapi);
        napi_get_named_property(env, argv, "easing", &easingNapi);
        napi_get_named_property(env, argv, "delay", &delayNapi);
        napi_get_named_property(env, argv, "fill", &fillNapi);
        napi_get_named_property(env, argv, "direction", &directionNapi);
        napi_get_named_property(env, argv, "iterations", &iterationsNapi);
        napi_get_named_property(env, argv, "begin", &beginNapi);
        napi_get_named_property(env, argv, "end", &endNapi);
    } else {
        NapiThrow(env, "The type of parameters is incorrect.", Framework::ERROR_CODE_PARAM_INVALID);
        return;
    }

    int32_t duration = 0;
    int32_t delay = 0;
    int32_t iterations = 0;
    double begin = 0.0;
    double end = 0.0;
    std::string easing = "ease";
    std::string fill = "none";
    std::string direction = "normal";
    ParseString(env, easingNapi, easing);
    ParseString(env, fillNapi, fill);
    ParseString(env, directionNapi, direction);
    ParseInt(env, durationNapi, duration);
    ParseInt(env, delayNapi, delay);
    ParseInt(env, iterationsNapi, iterations);
    ParseDouble(env, beginNapi, begin);
    ParseDouble(env, endNapi, end);
    option->duration = duration;
    option->delay = delay;
    option->iterations = iterations;
    option->begin = begin;
    option->end = end;
    option->easing = easing;
    option->fill = fill;
    option->direction = direction;
}

static RefPtr<Animator> GetAnimatorInResult(napi_env env, napi_callback_info info)
{
    AnimatorResult* animatorResult = nullptr;
    napi_value thisVar;
    napi_get_cb_info(env, info, NULL, NULL, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        return nullptr;
    }
    return animatorResult->GetAnimator();
}

static napi_value JSReset(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSReset");
    AnimatorResult* animatorResult = nullptr;
    napi_value thisVar;
    napi_get_cb_info(env, info, NULL, NULL, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        NapiThrow(env, "Internal error. Unwrap animator result is failed.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        LOGE("Option is null in AnimatorResult");
        NapiThrow(env, "Internal error. Option is null in AnimatorResult.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    ParseAnimatorOption(env, info, option);
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        LOGW("animator is null");
        NapiThrow(env, "Internal error. Animator is null in AnimatorResult.", Framework::ERROR_CODE_INTERNAL_ERROR);
        return nullptr;
    }
    animator->ClearInterpolators();
    animator->ResetIsReverse();
    animatorResult->ApplyOption();
    napi_ref onframeRef = animatorResult->GetOnframeRef();
    if (onframeRef) {
        auto curve = Framework::CreateCurve(option->easing);
        auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(option->begin, option->end, curve);
        animation->AddListener([env, onframeRef](double value) {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            if (scope == nullptr) {
                LOGW("JsAnimator: open handle scope failed");
                return;
            }
            napi_value ret = nullptr;
            napi_value valueNapi = nullptr;
            napi_value onframe = nullptr;
            auto result = napi_get_reference_value(env, onframeRef, &onframe);
            if (result != napi_ok || onframe == nullptr) {
                LOGW("JsAnimator: get onframe in callback failed");
                napi_close_handle_scope(env, scope);
                return;
            }
            napi_create_double(env, value, &valueNapi);
            napi_call_function(env, nullptr, onframe, 1, &valueNapi, &ret);
            napi_close_handle_scope(env, scope);
        });
        animator->AddInterpolator(animation);
    }
    napi_value result;
    napi_get_null(env, &result);
    return result;
}

// since API 9 deprecated
static napi_value JSUpdate(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSUpdate");
    return JSReset(env, info);
}

static napi_value JSPlay(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSPlay");
    auto animator = GetAnimatorInResult(env, info);
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    if (!animator->HasScheduler()) {
        animator->AttachSchedulerOnContainer();
    }
    animator->Play();
    napi_value result = nullptr;
    napi_get_null(env, &result);
    return result;
}

static napi_value JSFinish(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSFinish");
    auto animator = GetAnimatorInResult(env, info);
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    animator->Finish();
    napi_value result = nullptr;
    napi_get_null(env, &result);
    return result;
}

static napi_value JSPause(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSPause");
    auto animator = GetAnimatorInResult(env, info);
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    animator->Pause();
    napi_value result;
    napi_get_null(env, &result);
    return result;
}

static napi_value JSCancel(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSCancel");
    auto animator = GetAnimatorInResult(env, info);
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    animator->Cancel();
    napi_value result;
    napi_get_null(env, &result);
    return result;
}

static napi_value JSReverse(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSReverse");
    auto animator = GetAnimatorInResult(env, info);
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    if (!animator->HasScheduler()) {
        animator->AttachSchedulerOnContainer();
    }
    animator->Reverse();
    napi_value result;
    napi_get_null(env, &result);
    return result;
}

static napi_value SetOnframe(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: SetOnframe");
    AnimatorResult* animatorResult = nullptr;
    size_t argc = 1;
    napi_value thisVar = nullptr;
    napi_value onframe = nullptr;
    napi_get_cb_info(env, info, &argc, &onframe, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        return nullptr;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        LOGE("option is null");
        return nullptr;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    animator->ClearInterpolators();
    auto curve = Framework::CreateCurve(option->easing);
    auto animation = AceType::MakeRefPtr<CurveAnimation<double>>(option->begin, option->end, curve);
    // convert onframe function to reference
    napi_ref onframeRef = animatorResult->GetOnframeRef();
    if (onframeRef) {
        uint32_t count = 0;
        napi_reference_unref(env, onframeRef, &count);
    }
    napi_create_reference(env, onframe, 1, &onframeRef);
    animatorResult->SetOnframeRef(onframeRef);
    animation->AddListener([env, onframeRef](double value) {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            LOGW("JsAnimator: open handle scope failed");
            return;
        }
        napi_value ret = nullptr;
        napi_value valueNapi = nullptr;
        napi_value onframe = nullptr;
        auto result = napi_get_reference_value(env, onframeRef, &onframe);
        if (result != napi_ok || onframe == nullptr) {
            LOGW("JsAnimator: get onframe in callback failed");
            napi_close_handle_scope(env, scope);
            return;
        }
        napi_create_double(env, value, &valueNapi);
        napi_call_function(env, nullptr, onframe, 1, &valueNapi, &ret);
        napi_close_handle_scope(env, scope);
    });
    animator->AddInterpolator(animation);
    if (!animator->HasScheduler()) {
        animator->AttachSchedulerOnContainer();
    }
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;
}

static napi_value SetOnfinish(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: SetOnfinish");
    AnimatorResult* animatorResult = nullptr;
    size_t argc = 1;
    napi_value thisVar = nullptr;
    napi_value onfinish = nullptr;
    napi_get_cb_info(env, info, &argc, &onfinish, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        return nullptr;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        LOGE("option is null");
        return nullptr;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    // convert onfinish function to reference
    napi_ref onfinishRef = animatorResult->GetOnfinishRef();
    if (onfinishRef) {
        uint32_t count = 0;
        napi_reference_unref(env, onfinishRef, &count);
    }
    napi_create_reference(env, onfinish, 1, &onfinishRef);
    animatorResult->SetOnfinishRef(onfinishRef);
    animator->ClearStopListeners();
    animator->AddStopListener([env, onfinishRef] {
        LOGI("JsAnimator: onfinish");
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            LOGW("JsAnimator: open handle scope failed");
            return;
        }
        napi_value ret = nullptr;
        napi_value onfinish = nullptr;
        auto result = napi_get_reference_value(env, onfinishRef, &onfinish);
        if (result != napi_ok || onfinish == nullptr) {
            LOGW("JsAnimator: get onfinish in callback failed");
            napi_close_handle_scope(env, scope);
            return;
        }
        napi_call_function(env, NULL, onfinish, 0, NULL, &ret);
        napi_close_handle_scope(env, scope);
    });
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;
}

static napi_value SetOncancel(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: SetOncancel");
    AnimatorResult* animatorResult = nullptr;
    size_t argc = 1;
    napi_value thisVar = nullptr;
    napi_value oncancel = nullptr;
    napi_get_cb_info(env, info, &argc, &oncancel, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        return nullptr;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        LOGE("option is null");
        return nullptr;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    // convert oncancel function to reference
    napi_ref oncancelRef = animatorResult->GetOncancelRef();
    if (oncancelRef) {
        uint32_t count = 0;
        napi_reference_unref(env, oncancelRef, &count);
    }
    napi_create_reference(env, oncancel, 1, &oncancelRef);
    animatorResult->SetOncancelRef(oncancelRef);
    animator->ClearIdleListeners();
    animator->AddIdleListener([env, oncancelRef] {
        LOGI("JsAnimator: oncancel");
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            LOGW("JsAnimator: open handle scope failed");
            return;
        }
        napi_value ret = nullptr;
        napi_value oncancel = nullptr;
        auto result = napi_get_reference_value(env, oncancelRef, &oncancel);
        if (result != napi_ok || oncancel == nullptr) {
            LOGW("JsAnimator: get oncancel in callback failed");
            napi_close_handle_scope(env, scope);
            return;
        }
        napi_call_function(env, NULL, oncancel, 0, NULL, &ret);
        napi_close_handle_scope(env, scope);
    });
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;
}

static napi_value SetOnrepeat(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: SetOnrepeat");
    AnimatorResult* animatorResult = nullptr;
    size_t argc = 1;
    napi_value thisVar = nullptr;
    napi_value onrepeat = nullptr;
    napi_get_cb_info(env, info, &argc, &onrepeat, &thisVar, NULL);
    napi_unwrap(env, thisVar, (void**)&animatorResult);
    if (!animatorResult) {
        LOGE("unwrap animator result is failed");
        return nullptr;
    }
    auto option = animatorResult->GetAnimatorOption();
    if (!option) {
        LOGE("option is null");
        return nullptr;
    }
    auto animator = animatorResult->GetAnimator();
    if (!animator) {
        LOGE("animator is null");
        return nullptr;
    }
    // convert onrepeat function to reference
    napi_ref onrepeatRef = animatorResult->GetOnrepeatRef();
    if (onrepeatRef) {
        uint32_t count = 0;
        napi_reference_unref(env, onrepeatRef, &count);
    }
    napi_create_reference(env, onrepeat, 1, &onrepeatRef);
    animatorResult->SetOnrepeatRef(onrepeatRef);
    animator->ClearRepeatListeners();
    animator->AddRepeatListener([env, onrepeatRef] {
        LOGI("JsAnimator: onrepeat");
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        if (scope == nullptr) {
            LOGW("JsAnimator: open handle scope failed");
            return;
        }
        napi_value ret = nullptr;
        napi_value onrepeat = nullptr;
        auto result = napi_get_reference_value(env, onrepeatRef, &onrepeat);
        if (result != napi_ok || onrepeat == nullptr) {
            LOGW("JsAnimator: get onrepeat in callback failed");
            napi_close_handle_scope(env, scope);
            return;
        }
        napi_call_function(env, NULL, onrepeat, 0, NULL, &ret);
        napi_close_handle_scope(env, scope);
    });
    napi_value undefined;
    napi_get_undefined(env, &undefined);
    return undefined;
}

static napi_value JSCreate(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSCreate");
    auto option = std::make_shared<AnimatorOption>();
    ParseAnimatorOption(env, info, option);
    auto animator = AceType::MakeRefPtr<Animator>();
    animator->AttachSchedulerOnContainer();
    AnimatorResult* animatorResult = new AnimatorResult(animator, option);
    napi_value jsAnimator = nullptr;
    napi_create_object(env, &jsAnimator);
    napi_wrap(
        env, jsAnimator, animatorResult,
        [](napi_env env, void* data, void* hint) {
            AnimatorResult* animatorResult = (AnimatorResult*)data;
            // release four references(onFunc) before releasing animatorResult
            napi_ref onframeRef = animatorResult->GetOnframeRef();
            napi_ref onfinishRef = animatorResult->GetOnfinishRef();
            napi_ref oncancelRef = animatorResult->GetOncancelRef();
            napi_ref onrepeatRef = animatorResult->GetOnrepeatRef();
            if (onframeRef != nullptr) {
                napi_delete_reference(env, onframeRef);
            }
            if (onfinishRef != nullptr) {
                napi_delete_reference(env, onfinishRef);
            }
            if (oncancelRef != nullptr) {
                napi_delete_reference(env, oncancelRef);
            }
            if (onrepeatRef != nullptr) {
                napi_delete_reference(env, onrepeatRef);
            }
            delete animatorResult;
        },
        nullptr, nullptr);
    napi_property_descriptor resultFuncs[] = {
        DECLARE_NAPI_FUNCTION("update", JSUpdate),
        DECLARE_NAPI_FUNCTION("reset", JSReset),
        DECLARE_NAPI_FUNCTION("play", JSPlay),
        DECLARE_NAPI_FUNCTION("finish", JSFinish),
        DECLARE_NAPI_FUNCTION("pause", JSPause),
        DECLARE_NAPI_FUNCTION("cancel", JSCancel),
        DECLARE_NAPI_FUNCTION("reverse", JSReverse),
        DECLARE_NAPI_SETTER("onframe", SetOnframe),
        DECLARE_NAPI_SETTER("onfinish", SetOnfinish),
        DECLARE_NAPI_SETTER("oncancel", SetOncancel),
        DECLARE_NAPI_SETTER("onrepeat", SetOnrepeat),
    };

    NAPI_CALL(env, napi_define_properties(env, jsAnimator, sizeof(resultFuncs) / sizeof(resultFuncs[0]), resultFuncs));
    return jsAnimator;
}

// since API 9 deprecated
static napi_value JSCreateAnimator(napi_env env, napi_callback_info info)
{
    LOGI("JsAnimator: JSCreateAnimator");
    return JSCreate(env, info);
}

static napi_value AnimatorExport(napi_env env, napi_value exports)
{
    LOGI("JsAnimator: AnimatorExport");
    napi_property_descriptor animatorDesc[] = {
        DECLARE_NAPI_FUNCTION("create", JSCreate),
        DECLARE_NAPI_FUNCTION("createAnimator", JSCreateAnimator),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(animatorDesc) / sizeof(animatorDesc[0]), animatorDesc));
    return exports;
}

static napi_module animatorModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = AnimatorExport,
    .nm_modname = "animator",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void AnimatorRegister()
{
    napi_module_register(&animatorModule);
}

void AnimatorResult::ApplyOption()
{
    CHECK_NULL_VOID_NOLOG(animator_);
    CHECK_NULL_VOID_NOLOG(option_);
    animator_->SetDuration(option_->duration);
    animator_->SetIteration(option_->iterations);
    animator_->SetStartDelay(option_->delay);
    animator_->SetFillMode(StringToFillMode(option_->fill));
    animator_->SetAnimationDirection(StringToAnimationDirection(option_->direction));
}

} // namespace OHOS::Ace::Napi

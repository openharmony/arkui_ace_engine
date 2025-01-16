/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "arc_swiper_napi.h"

#include "arc_swiper_controller.h"
#include "arc_swiper_indicator.h"
#include "ext_napi_utils.h"

#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_linear_gradient.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

extern const char _binary_arkui_arcswiper_abc_start[];
extern const char _binary_arkui_arcswiper_abc_end[];

namespace OHOS::Ace {
namespace {
static constexpr const size_t MAX_ARG_NUM = 10;
static constexpr const int32_t DEFAULT_DURATION = 400;
static constexpr const int32_t THREE_CLOCK_DIRECTION = 0;
static constexpr const int32_t SIX_CLOCK_DIRECTION = 1;
static constexpr const int32_t NINE_CLOCK_DIRECTION = 2;
} // namespace

std::unique_ptr<SwiperModel> SwiperModel::instance_ = nullptr;
std::mutex SwiperModel::mutex_;

SwiperModel* SwiperModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
            instance_.reset(new NG::SwiperModelNG());
        }
    }
    return instance_.get();
}

napi_value JsCreate(napi_env env, napi_callback_info info)
{
    auto controller = SwiperModel::GetInstance()->Create(true);
    SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::ARC_DOT);

    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    if (argc > 0 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object)) {
        NG::JsArcSwiperController* jsController = nullptr;
        napi_unwrap(env, argv[0], (void**)&jsController);
        if (jsController) {
            jsController->SetController(controller);
        }
    }

    return ExtNapiUtils::CreateNull(env);
}

napi_value JsIndex(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    int32_t index = 0;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_number)) {
        index = ExtNapiUtils::GetCInt32(env, argv[0]);
    }
    index = index < 0 ? 0 : index;
    SwiperModel::GetInstance()->SetIndex(index);

    return ExtNapiUtils::CreateNull(env);
}

SwiperArcDotParameters GetArcDotIndicatorInfo(napi_env env, napi_value value)
{
    SwiperArcDotParameters swiperParameters;
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, swiperParameters);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, swiperParameters);
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, value, (void**)&indicator);

    // parse arcDirection
    swiperParameters.arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    if (indicator && indicator->HasArcDirection()) {
        swiperParameters.arcDirection = indicator->GetArcDirection();
    }
    // parse itemColor
    swiperParameters.itemColor =
        (indicator && indicator->HasItemColor()) ? indicator->GetItemColor() : swiperIndicatorTheme->GetArcItemColor();
    // parse selectedItemColor
    swiperParameters.selectedItemColor = (indicator && indicator->HasSelectedItemColor())
                                             ? indicator->GetSelectedItemColor()
                                             : swiperIndicatorTheme->GetArcSelectedItemColor();
    // parse containerColor
    swiperParameters.containerColor = (indicator && indicator->HasContainerColor())
                                          ? indicator->GetContainerColor()
                                          : swiperIndicatorTheme->GetArcContainerColor();
    // parse maskColor
    swiperParameters.maskColor =
        (indicator && indicator->HasMaskColor()) ? indicator->GetMaskColor() : swiperIndicatorTheme->GetArcMaskColor();

    return swiperParameters;
}

napi_value JsIndicator(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    bool showIndicator = true;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_boolean)) {
        showIndicator = ExtNapiUtils::GetBool(env, argv[0]);
    } else {
        SwiperModel::GetInstance()->SetIndicatorIsBoolean(false);
        SwiperArcDotParameters swiperParameters = GetArcDotIndicatorInfo(env, argv[0]);
        SwiperModel::GetInstance()->SetArcDotIndicatorStyle(swiperParameters);
    }

    SwiperModel::GetInstance()->SetShowIndicator(showIndicator);

    return ExtNapiUtils::CreateNull(env);
}

napi_value JsDuration(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    int32_t duration = DEFAULT_DURATION;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_number)) {
        duration = ExtNapiUtils::GetCInt32(env, argv[0]);
    }
    duration = duration < 0 ? DEFAULT_DURATION : duration;
    SwiperModel::GetInstance()->SetDuration(duration);

    return ExtNapiUtils::CreateNull(env);
}

napi_value JsVertical(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    bool isVertical = false;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_boolean)) {
        isVertical = ExtNapiUtils::GetBool(env, argv[0]);
    }
    SwiperModel::GetInstance()->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);

    return ExtNapiUtils::CreateNull(env);
}

napi_value JsDisableSwipe(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    bool isDisable = false;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_boolean)) {
        isDisable = ExtNapiUtils::GetBool(env, argv[0]);
    }
    SwiperModel::GetInstance()->SetDisableSwipe(isDisable);

    return ExtNapiUtils::CreateNull(env);
}

napi_value JsOnChange(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        return ExtNapiUtils::CreateNull(env);
    }
    auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, argv[0]);
    auto onChange = [asyncEvent](const BaseEventInfo* info) {
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(asyncEvent->GetEnv(), &scope);
        CHECK_NULL_VOID(scope);

        const auto* eventInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!eventInfo) {
            napi_close_handle_scope(asyncEvent->GetEnv(), scope);
            return;
        }
        napi_value arrayValue = ExtNapiUtils::CreateInt32(asyncEvent->GetEnv(), eventInfo->GetIndex());
        napi_value argv[1] = { arrayValue };
        asyncEvent->Call(1, argv);

        napi_close_handle_scope(asyncEvent->GetEnv(), scope);
    };
    SwiperModel::GetInstance()->SetOnChange(std::move(onChange));
    return ExtNapiUtils::CreateNull(env);
}

napi_value GetAnimationInfoJsObject(napi_env env, const AnimationCallbackInfo& info)
{
    napi_value jsObject = ExtNapiUtils::CreateObject(env);

    napi_value currentOffsetValue = ExtNapiUtils::CreateDouble(env, info.currentOffset.value_or(0.0f));
    ExtNapiUtils::SetNamedProperty(env, jsObject, "currentOffset", currentOffsetValue);
    napi_value targetOffsetValue = ExtNapiUtils::CreateDouble(env, info.targetOffset.value_or(0.0f));
    ExtNapiUtils::SetNamedProperty(env, jsObject, "targetOffset", targetOffsetValue);
    napi_value velocityValue = ExtNapiUtils::CreateDouble(env, info.velocity.value_or(0.0f));
    ExtNapiUtils::SetNamedProperty(env, jsObject, "velocity", velocityValue);

    return jsObject;
}

static  RefPtr<SwiperContentTransitionProxy> g_proxy = nullptr;

static napi_value FinishTransition(napi_env env, napi_callback_info info)
{
    void *data = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, nullptr, &data));
    auto proxy = AceType::Claim(reinterpret_cast<SwiperContentTransitionProxy *>(data));
    if (proxy) {
        proxy->FinishTransition();
    }
    data = nullptr;
    g_proxy = nullptr;
    return nullptr;
}

static napi_value GetSwiperContentTransitionProxyJsObject(napi_env env,
                                                          const RefPtr<SwiperContentTransitionProxy>& proxy)
{
    napi_value jsObject = ExtNapiUtils::CreateObject(env);

    napi_value selectedIndex = ExtNapiUtils::CreateInt32(env, proxy->GetSelectedIndex());
    ExtNapiUtils::SetNamedProperty(env, jsObject, "selectedIndex", selectedIndex);
    napi_value index = ExtNapiUtils::CreateInt32(env, proxy->GetIndex());
    ExtNapiUtils::SetNamedProperty(env, jsObject, "index", index);
    napi_value position = ExtNapiUtils::CreateDouble(env, proxy->GetPosition());
    ExtNapiUtils::SetNamedProperty(env, jsObject, "position", position);
    napi_value mainAxisLength = ExtNapiUtils::CreateDouble(env, proxy->GetMainAxisLength());
    ExtNapiUtils::SetNamedProperty(env, jsObject, "mainAxisLength", mainAxisLength);
    const char* funName = "finishTransition";
    napi_value funcValue = nullptr;
    g_proxy = proxy;
    funcValue = ExtNapiUtils::CreateFunction(env, funName, strlen(funName),
                                             FinishTransition, (void*)g_proxy.GetRawPtr());
    ExtNapiUtils::SetNamedProperty(env, jsObject, funName, funcValue);

    return jsObject;
}

napi_value JsOnAnimationStart(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        return ExtNapiUtils::CreateNull(env);
    }
    auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, argv[0]);
    auto onAnimationStart = [asyncEvent](int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
        napi_env env = asyncEvent->GetEnv();
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_VOID(scope);

        napi_value arrayValueOne = ExtNapiUtils::CreateInt32(env, index);
        napi_value arrayValueTwo = ExtNapiUtils::CreateInt32(env, targetIndex);
        napi_value arrayValueThree = GetAnimationInfoJsObject(env, info);

        napi_value argv[3] = { arrayValueOne, arrayValueTwo, arrayValueThree };
        asyncEvent->Call(3, argv);

        napi_close_handle_scope(env, scope);
    };
    SwiperModel::GetInstance()->SetOnAnimationStart(std::move(onAnimationStart));
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsOnAnimationEnd(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        return ExtNapiUtils::CreateNull(env);
    }
    auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, argv[0]);
    auto onAnimationEnd = [asyncEvent](int32_t index, const AnimationCallbackInfo& info) {
        napi_env env = asyncEvent->GetEnv();
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_VOID(scope);

        napi_value arrayValueOne = ExtNapiUtils::CreateInt32(env, index);
        napi_value arrayValueTwo = GetAnimationInfoJsObject(env, info);

        napi_value argv[2] = { arrayValueOne, arrayValueTwo };
        asyncEvent->Call(2, argv);

        napi_close_handle_scope(env, scope);
    };
    SwiperModel::GetInstance()->SetOnAnimationEnd(std::move(onAnimationEnd));
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsOnGestureSwipe(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        return ExtNapiUtils::CreateNull(env);
    }
    auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, argv[0]);
    auto onGestureSwipe = [asyncEvent](int32_t index, const AnimationCallbackInfo& info) {
        napi_env env = asyncEvent->GetEnv();
        napi_handle_scope scope = nullptr;
        napi_open_handle_scope(env, &scope);
        CHECK_NULL_VOID(scope);

        napi_value arrayValueOne = ExtNapiUtils::CreateInt32(env, index);
        napi_value arrayValueTwo = GetAnimationInfoJsObject(env, info);

        napi_value argv[2] = { arrayValueOne, arrayValueTwo };
        asyncEvent->Call(2, argv);

        napi_close_handle_scope(env, scope);
    };
    SwiperModel::GetInstance()->SetOnGestureSwipe(std::move(onGestureSwipe));
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsSetDigitalCrownSensitivity(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    int32_t sensitivity = 1;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_number)) {
        sensitivity = static_cast<int32_t>(ExtNapiUtils::GetCInt32(env, argv[0]));
    }

    SwiperModel::GetInstance()->SetDigitalCrownSensitivity(sensitivity);
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsSetEffectMode(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    EdgeEffect edgeEffect = EdgeEffect::NONE;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_number)) {
        edgeEffect = static_cast<EdgeEffect>(ExtNapiUtils::GetCInt32(env, argv[0]));
    }

    SwiperModel::GetInstance()->SetEdgeEffect(edgeEffect);
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsSetCustomContentTransition(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    if (!ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object)) {
        return ExtNapiUtils::CreateNull(env);
    }

    SwiperContentAnimatedTransition transitionInfo;
    napi_value jsTimeout = ExtNapiUtils::GetNamedProperty(env, argv[0], "timeout");
    if (ExtNapiUtils::CheckTypeForNapiValue(env, jsTimeout, napi_number)) {
        int32_t timeOut = static_cast<int32_t>(ExtNapiUtils::GetCInt32(env, jsTimeout));
        transitionInfo.timeout = timeOut < 0 ? 0 : timeOut;
    } else {
        transitionInfo.timeout = 0;
    }

    napi_value jsTransition = ExtNapiUtils::GetNamedProperty(env, argv[0], "transition");
    if (ExtNapiUtils::CheckTypeForNapiValue(env, jsTransition, napi_function)) {
        auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, jsTransition);
        auto onTransition = [asyncEvent](const RefPtr<SwiperContentTransitionProxy>& proxy) {
            napi_env env = asyncEvent->GetEnv();
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(env, &scope);
            CHECK_NULL_VOID(scope);

            napi_value arrayValueOne = GetSwiperContentTransitionProxyJsObject(env, proxy);
            napi_value argv[1] = { arrayValueOne };
            asyncEvent->Call(1, argv);
            napi_close_handle_scope(env, scope);
        };
        transitionInfo.transition = std::move(onTransition);
    }
    SwiperModel::GetInstance()->SetCustomContentTransition(transitionInfo);
    return ExtNapiUtils::CreateNull(env);
}

napi_value JsSetDisableTransitionAnimation(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");

    bool isDisable = false;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_boolean)) {
        isDisable = ExtNapiUtils::GetBool(env, argv[0]);
    }
    SwiperModel::GetInstance()->SetDisableTransitionAnimation(isDisable);

    return ExtNapiUtils::CreateNull(env);
}

napi_value ShowNext(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, NULL));
    NG::JsArcSwiperController* controller = nullptr;
    napi_unwrap(env, thisVar, (void**)&controller);
    napi_value objectValue = ExtNapiUtils::CreateNull(env);
    CHECK_NULL_RETURN(controller, objectValue);
    controller->ShowNext();
    return objectValue;
}

napi_value ShowPrevious(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, NULL));
    NG::JsArcSwiperController* controller = nullptr;
    napi_unwrap(env, thisVar, (void**)&controller);
    napi_value objectValue = ExtNapiUtils::CreateNull(env);
    CHECK_NULL_RETURN(controller, objectValue);
    controller->ShowPrevious();
    return objectValue;
}

napi_value FinishAnimation(napi_env env, napi_callback_info info)
{
    size_t argc = MAX_ARG_NUM;
    napi_value thisVal = nullptr;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVal, nullptr));
    NG::JsArcSwiperController* controller = nullptr;
    napi_unwrap(env, thisVal, (void**)&controller);
    napi_value objectValue = ExtNapiUtils::CreateNull(env);
    CHECK_NULL_RETURN(controller, objectValue);

    CommonFunc onFinish = nullptr;
    if (argc > 0 && ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_function)) {
        auto asyncEvent = std::make_shared<NapiAsyncEvent>(env, argv[0]);
        onFinish = [asyncEvent]() {
            napi_handle_scope scope = nullptr;
            napi_open_handle_scope(asyncEvent->GetEnv(), &scope);
            CHECK_NULL_VOID(scope);
            asyncEvent->Call(0, nullptr);
            napi_close_handle_scope(asyncEvent->GetEnv(), scope);
        };
    }
    controller->FinishAnimation(onFinish);

    return objectValue;
}

napi_value ArcSwiperControllerConstructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    auto controller = AceType::MakeRefPtr<NG::JsArcSwiperController>();
    CHECK_NULL_RETURN(controller, ExtNapiUtils::CreateNull(env));
    controller->IncRefCount();
    napi_wrap(
        env, thisVar, AceType::RawPtr(controller),
        [](napi_env env, void* data, void* hint) {
            auto* controller = reinterpret_cast<NG::JsArcSwiperController*>(data);
            controller->DecRefCount();
        },
        nullptr, nullptr);
    return thisVar;
}

napi_value ArcDotIndicatorConstructor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr));
    auto indicator = AceType::MakeRefPtr<NG::JsArcSwiperIndicator>();
    CHECK_NULL_RETURN(indicator, ExtNapiUtils::CreateNull(env));
    indicator->IncRefCount();
    napi_wrap(
        env, thisVar, AceType::RawPtr(indicator),
        [](napi_env env, void* data, void* hint) {
            auto* indicator = reinterpret_cast<NG::JsArcSwiperIndicator*>(data);
            indicator->DecRefCount();
        },
        nullptr, nullptr);
    return thisVar;
}

napi_value SetArcDirection(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, thisVar, (void**)&indicator);
    CHECK_NULL_RETURN(indicator, thisVar);
    SwiperArcDirection arcDirection = SwiperArcDirection::SIX_CLOCK_DIRECTION;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_number)) {
        arcDirection = static_cast<SwiperArcDirection>(ExtNapiUtils::GetCInt32(env, argv[0]));
    }
    indicator->SetArcDirection(arcDirection);
    return thisVar;
}

napi_value SetItemColor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, thisVar, (void**)&indicator);
    CHECK_NULL_RETURN(indicator, thisVar);

    Color colorVal;
    if (ExtNapiUtils::ParseColor(env, argv[0], colorVal)) {
        indicator->SetItemColor(colorVal);
    } else {
        indicator->ResetItemColor();
    }
    return thisVar;
}

napi_value SetSelectedItemColor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, thisVar, (void**)&indicator);
    CHECK_NULL_RETURN(indicator, thisVar);

    Color colorVal;
    if (ExtNapiUtils::ParseColor(env, argv[0], colorVal)) {
        indicator->SetSelectedItemColor(colorVal);
    } else {
        indicator->ResetSelectedItemColor();
    }
    return thisVar;
}

napi_value SetBackgroundColor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, thisVar, (void**)&indicator);
    CHECK_NULL_RETURN(indicator, thisVar);

    Color colorVal;
    if (ExtNapiUtils::ParseColor(env, argv[0], colorVal)) {
        indicator->SetContainerColor(colorVal);
    } else {
        indicator->ResetContainerColor();
    }
    return thisVar;
}

bool ConvertGradientColor(napi_env env, napi_value value, NG::Gradient& gradient)
{
    auto jsValue = Framework::JsConverter::ConvertNapiValueToJsVal(value);
    Framework::JSLinearGradient* jsLinearGradient =
        Framework::JSRef<Framework::JSObject>::Cast(jsValue)->Unwrap<Framework::JSLinearGradient>();

    if (!jsLinearGradient || jsLinearGradient->GetGradient().empty()) {
        return false;
    }

    size_t size = jsLinearGradient->GetGradient().size();
    if (size == 1) {
        // If there is only one color, then this color is used for both the begin and end side.
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().front().first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().front().second);
        gradient.AddColor(gradientColor);
        gradient.AddColor(gradientColor);
        return true;
    }

    for (size_t colorIndex = 0; colorIndex < size; colorIndex++) {
        NG::GradientColor gradientColor;
        gradientColor.SetLinearColor(LinearColor(jsLinearGradient->GetGradient().at(colorIndex).first));
        gradientColor.SetDimension(jsLinearGradient->GetGradient().at(colorIndex).second);
        gradient.AddColor(gradientColor);
    }
    return true;
}

napi_value SetMaskColor(napi_env env, napi_callback_info info)
{
    napi_value thisVar = nullptr;
    size_t argc = MAX_ARG_NUM;
    napi_value argv[MAX_ARG_NUM] = { nullptr };
    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 1, "Wrong number of arguments");
    NG::JsArcSwiperIndicator* indicator = nullptr;
    napi_unwrap(env, thisVar, (void**)&indicator);
    CHECK_NULL_RETURN(indicator, thisVar);

    NG::Gradient gradient;
    if (ExtNapiUtils::CheckTypeForNapiValue(env, argv[0], napi_object) &&
        ConvertGradientColor(env, argv[0], gradient)) {
        indicator->SetMaskColor(gradient);
    } else {
        indicator->ResetMaskColor();
    }

    return thisVar;
}

napi_value InitArcSwiper(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("create", JsCreate),
        DECLARE_NAPI_FUNCTION("index", JsIndex),
        DECLARE_NAPI_FUNCTION("indicator", JsIndicator),
        DECLARE_NAPI_FUNCTION("duration", JsDuration),
        DECLARE_NAPI_FUNCTION("vertical", JsVertical),
        DECLARE_NAPI_FUNCTION("disableSwipe", JsDisableSwipe),
        DECLARE_NAPI_FUNCTION("onChange", JsOnChange),
        DECLARE_NAPI_FUNCTION("onAnimationStart", JsOnAnimationStart),
        DECLARE_NAPI_FUNCTION("onAnimationEnd", JsOnAnimationEnd),
        DECLARE_NAPI_FUNCTION("onGestureSwipe", JsOnGestureSwipe),
        DECLARE_NAPI_FUNCTION("digitalCrownSensitivity", JsSetDigitalCrownSensitivity),
        DECLARE_NAPI_FUNCTION("effectMode", JsSetEffectMode),
        DECLARE_NAPI_FUNCTION("customContentTransition", JsSetCustomContentTransition),
        DECLARE_NAPI_FUNCTION("disableTransitionAnimation", JsSetDisableTransitionAnimation),
    };
    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value InitArcDotIndicator(napi_env env, napi_value exports)
{
    napi_value arcDotIndicatorClass = nullptr;
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("arcDirection", SetArcDirection),
        DECLARE_NAPI_FUNCTION("itemColor", SetItemColor),
        DECLARE_NAPI_FUNCTION("selectedItemColor", SetSelectedItemColor),
        DECLARE_NAPI_FUNCTION("backgroundColor", SetBackgroundColor),
        DECLARE_NAPI_FUNCTION("maskColor", SetMaskColor),
    };

    NAPI_CALL(env, napi_define_class(env, "ArcDotIndicator", NAPI_AUTO_LENGTH, ArcDotIndicatorConstructor, nullptr,
                       sizeof(desc) / sizeof(desc[0]), desc, &arcDotIndicatorClass));
    NAPI_CALL(env, napi_set_named_property(env, exports, "ArcDotIndicator", arcDotIndicatorClass));
    return exports;
}

napi_value InitArcDirection(napi_env env, napi_value exports)
{
    napi_value arcDirection = nullptr;
    napi_create_object(env, &arcDirection);
    napi_value prop = ExtNapiUtils::CreateInt32(env, THREE_CLOCK_DIRECTION);
    napi_set_named_property(env, arcDirection, "THREE_CLOCK_DIRECTION", prop);
    prop = ExtNapiUtils::CreateInt32(env, SIX_CLOCK_DIRECTION);
    napi_set_named_property(env, arcDirection, "SIX_CLOCK_DIRECTION", prop);
    prop = ExtNapiUtils::CreateInt32(env, NINE_CLOCK_DIRECTION);
    napi_set_named_property(env, arcDirection, "NINE_CLOCK_DIRECTION", prop);

    NAPI_CALL(env, napi_set_named_property(env, exports, "ArcDirection", arcDirection));
    return exports;
}

napi_value InitController(napi_env env, napi_value exports)
{
    napi_value arcSwiperControllerClass = nullptr;
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("showNext", ShowNext),
        DECLARE_NAPI_FUNCTION("showPrevious", ShowPrevious),
        DECLARE_NAPI_FUNCTION("finishAnimation", FinishAnimation),
    };

    NAPI_CALL(env, napi_define_class(env, "ArcSwiperController", NAPI_AUTO_LENGTH, ArcSwiperControllerConstructor,
                       nullptr, sizeof(desc) / sizeof(desc[0]), desc, &arcSwiperControllerClass));
    NAPI_CALL(env, napi_set_named_property(env, exports, "ArcSwiperController", arcSwiperControllerClass));
    return exports;
}

napi_value ExportArcSwiper(napi_env env, napi_value exports)
{
    InitArcSwiper(env, exports);
    InitController(env, exports);
    InitArcDotIndicator(env, exports);
    InitArcDirection(env, exports);

    return exports;
}

} // namespace OHOS::Ace

extern "C" ACE_FORCE_EXPORT void NAPI_arkui_ArcSwiper_GetABCCode(const char** buf, int* buflen)
{
    if (buf != nullptr) {
        *buf = _binary_arkui_arcswiper_abc_start;
    }
    if (buflen != nullptr) {
        *buflen = _binary_arkui_arcswiper_abc_end - _binary_arkui_arcswiper_abc_start;
    }
}

static napi_module arcSwiperModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = OHOS::Ace::ExportArcSwiper,
    .nm_modname = "arkui.ArcSwiper",
    .nm_priv = ((void*)0),
    .reserved = { 0 },
};

extern "C" __attribute__((constructor)) void RegisterArcSwiperModule()
{
    napi_module_register(&arcSwiperModule);
}

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

#include "gesture_observer_listener.h"

#include "interfaces/inner_api/ace_kit/include/ui/base/utils/utils.h"
#include "interfaces/napi/kits/utils/napi_utils.h"
#include "js_native_api.h"
#include "js_native_api_types.h"
#include "native_engine/impl/ark/ark_native_engine.h"

#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "core/components_ng/gestures/recognizers/click_recognizer.h"
#include "core/components_ng/gestures/recognizers/gesture_recognizer.h"
#include "core/components_ng/gestures/recognizers/long_press_recognizer.h"
#include "core/components_ng/gestures/recognizers/multi_fingers_recognizer.h"
#include "core/components_ng/gestures/recognizers/pan_recognizer.h"
#include "core/components_ng/gestures/recognizers/pinch_recognizer.h"
#include "core/components_ng/gestures/recognizers/rotation_recognizer.h"
#include "core/components_ng/gestures/recognizers/swipe_recognizer.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/swiper/swiper_pattern.h"
#include "ace_engine/interfaces/napi/kits/observer/gesture/gesture_observer_listener.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr char GET_TAG[] = "getTag";
constexpr char GET_TYPE[] = "getType";
constexpr char IS_BUILT_IN[] = "isBuiltIn";
constexpr char SET_ENABLED[] = "setEnabled";
constexpr char IS_ENABLED[] = "isEnabled";
constexpr char GET_STATE[] = "getState";
constexpr char GET_EVENT_TARGET_INFO[] = "getEventTargetInfo";
constexpr char IS_VALID[] = "isValid";
constexpr char GET_ID[] = "getId";
constexpr char IS_BEGIN[] = "isBegin";
constexpr char IS_END[] = "isEnd";
constexpr char GET_FINGER_COUNT[] = "getFingerCount";
constexpr char IS_FINGER_COUNT_LIMIT[] = "isFingerCountLimit";
constexpr char GET_DIRECTION[] = "getDirection";
constexpr char GET_DISTANCE[] = "getDistance";
constexpr char GET_DISTANCE_MAP[] = "getDistanceMap";
constexpr char GET_PANGESTURE_OPTIONS[] = "getPanGestureOptions";
constexpr char SET_DIRECTION[] = "setDirection";
constexpr char SET_DISTANCE[] = "setDistance";
constexpr char SET_FINGERS[] = "setFingers";
constexpr char GET_TAP_COUNT[] = "getTapCount";
constexpr char IS_REPEAT[] = "isRepeat";
constexpr char GET_DURATION[] = "getDuration";
constexpr char GET_ANGLE[] = "getAngle";
constexpr char GET_VELOCITY_THRESHOLD[] = "getVelocityThreshold";

constexpr int32_t PARAM_SIZE_ZERO = 0;
constexpr int32_t PARAM_SIZE_ONE = 1;
constexpr int32_t PARAM_SIZE_TWO = 2;
constexpr Dimension DEFAULT_PAN_DISTANCE = 5.0_vp;
constexpr double DEFAULT_DISTANCE = 5;
constexpr int32_t DEFAULT_PAN_FINGER = 1;
constexpr int32_t DEFAULT_MAX_PAN_FINGERS = 10;

enum class RecognizerType { MULTI_FINGERS, PAN };

struct MultiFingersRecognizerWrapper {
    double distance = 0.0;
    uint32_t direction = PanDirection::ALL;
    RecognizerType type = RecognizerType::MULTI_FINGERS;
    RefPtr<NG::MultiFingersRecognizer> recognizer;
};

struct PanRecognizerWrapper {
    RefPtr<NG::PanRecognizer> recognizer = nullptr;
    RefPtr<PanGestureOption> panGestureOption = nullptr;
    RecognizerType type = RecognizerType::PAN;
};

struct EventTargetInfoWrapper {
    std::string inspectorId = "";
    WeakPtr<NG::Pattern> weakPattern = nullptr;
    EventTargetInfoWrapper(std::string inspectorId, WeakPtr<NG::Pattern> pattern)
        : inspectorId(inspectorId), weakPattern(std::move(pattern))
    {}

    bool IsBegin() const
    {
        auto pattern = weakPattern.Upgrade();
        if (!pattern) {
            return false;
        }
        auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
        if (scrollablePattern) {
            return scrollablePattern->IsAtTop();
        }
        auto swiperPattern = AceType::DynamicCast<NG::SwiperPattern>(pattern);
        if (swiperPattern) {
            return swiperPattern->IsAtStart();
        }
        return false;
    }

    bool IsEnd() const
    {
        auto pattern = weakPattern.Upgrade();
        if (!pattern) {
            return false;
        }
        auto scrollablePattern = AceType::DynamicCast<NG::ScrollablePattern>(pattern);
        if (scrollablePattern) {
            return scrollablePattern->IsAtBottom();
        }
        auto swiperPattern = AceType::DynamicCast<NG::SwiperPattern>(pattern);
        if (swiperPattern) {
            return swiperPattern->IsAtEnd();
        }
        return false;
    }
};

MultiFingersRecognizerWrapper* GetCurrentMultiFingersRecognizerWrapper(
    napi_env env, napi_callback_info info, size_t* argc = nullptr, napi_value* argv = nullptr)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, argc, argv, &thisVar, nullptr));

    void* rawWrapper = nullptr;
    napi_status unwrapStatus = napi_unwrap(env, thisVar, &rawWrapper);
    if (unwrapStatus != napi_ok) {
        return nullptr;
    }
    auto* wrapper = static_cast<MultiFingersRecognizerWrapper*>(rawWrapper);
    return (wrapper && wrapper->type == RecognizerType::MULTI_FINGERS && wrapper->recognizer) ? wrapper : nullptr;
}

PanRecognizerWrapper* GetCurrentPanRecognizerWrapper(
    napi_env env, napi_callback_info info, size_t* argc = nullptr, napi_value* argv = nullptr)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, argc, argv, &thisVar, nullptr));

    void* rawWrapper = nullptr;
    const napi_status unwrapStatus = napi_unwrap(env, thisVar, &rawWrapper);
    if (unwrapStatus != napi_ok) {
        return nullptr;
    }

    auto* wrapper = static_cast<PanRecognizerWrapper*>(rawWrapper);
    if (!wrapper || wrapper->type != RecognizerType::PAN || !wrapper->recognizer || !wrapper->panGestureOption) {
        return nullptr;
    }

    return wrapper;
}

EventTargetInfoWrapper* GetEventTargetInfoWrapper(
    napi_env env, napi_callback_info info, size_t* argc = nullptr, napi_value* argv = nullptr)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, argc, argv, &thisVar, nullptr));

    void* rawWrapper = nullptr;
    napi_status unwrapStatus = napi_unwrap(env, thisVar, &rawWrapper);
    if (unwrapStatus != napi_ok) {
        return nullptr;
    }
    auto* wrapper = static_cast<EventTargetInfoWrapper*>(rawWrapper);
    return wrapper;
}

void ParsePanDirection(napi_env env, napi_value value, PanDirection& panDirection)
{
    uint32_t typeValue;
    napi_get_value_uint32(env, value, &typeValue);
    switch (typeValue) {
        case static_cast<uint32_t>(PanDirection::NONE):
            panDirection.type = PanDirection::NONE;
            return;
        case static_cast<uint32_t>(PanDirection::LEFT):
            panDirection.type = PanDirection::LEFT;
            return;
        case static_cast<uint32_t>(PanDirection::RIGHT):
            panDirection.type = PanDirection::RIGHT;
            return;
        case static_cast<uint32_t>(PanDirection::HORIZONTAL):
            panDirection.type = PanDirection::HORIZONTAL;
            return;
        case static_cast<uint32_t>(PanDirection::UP):
            panDirection.type = PanDirection::UP;
            return;
        case static_cast<uint32_t>(PanDirection::DOWN):
            panDirection.type = PanDirection::DOWN;
            return;
        case static_cast<uint32_t>(PanDirection::VERTICAL):
            panDirection.type = PanDirection::VERTICAL;
            return;
        case static_cast<uint32_t>(PanDirection::ALL):
            panDirection.type = PanDirection::ALL;
            return;
        default:
            panDirection.type = PanDirection::ALL;
            return;
    }
}

static napi_value GetTag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->recognizer->GetGestureInfo();
    if (!gestureInfo) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    if (gestureInfo->GetTag().has_value()) {
        std::string tag = gestureInfo->GetTag().value();
        napi_create_string_utf8(env, tag.c_str(), NAPI_AUTO_LENGTH, &result);
    } else {
        napi_get_undefined(env, &result);
    }
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetType(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->recognizer->GetGestureInfo();
    if (!gestureInfo) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_create_int32(env, static_cast<int32_t>(gestureInfo->GetRecognizerType()), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsBuiltIn(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->recognizer->GetGestureInfo();
    if (!gestureInfo) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_get_boolean(env, gestureInfo->IsSystemGesture(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value SetEnabled(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv[PARAM_SIZE_ONE] = { nullptr };
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info, &argc, argv);
    if (!current || !current->recognizer) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    napi_valuetype valueType = napi_undefined;
    if (napi_typeof(env, argv[PARAM_SIZE_ZERO], &valueType)) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (valueType != napi_boolean) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    bool isEnabled = false;
    napi_get_value_bool(env, argv[PARAM_SIZE_ZERO], &isEnabled);
    current->recognizer->SetEnabled(isEnabled);
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value IsEnabled(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->recognizer->IsEnabled(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static GestureRecognizerState ConvertRefereeState(NG::RefereeState state)
{
    switch (state) {
        case NG::RefereeState::READY:
            return GestureRecognizerState::READY;
        case NG::RefereeState::DETECTING:
            return GestureRecognizerState::DETECTING;
        case NG::RefereeState::PENDING:
            return GestureRecognizerState::PENDING;
        case NG::RefereeState::PENDING_BLOCKED:
        case NG::RefereeState::SUCCEED_BLOCKED:
            return GestureRecognizerState::BLOCKED;
        case NG::RefereeState::SUCCEED:
            return GestureRecognizerState::SUCCEED;
        case NG::RefereeState::FAIL:
            return GestureRecognizerState::FAIL;
        default:
            return GestureRecognizerState::UNKNOWN;
    }
}

static napi_value GetState(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_int32(env, static_cast<int32_t>(ConvertRefereeState(current->recognizer->GetRefereeState())), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetId(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    EventTargetInfoWrapper* wrapper = GetEventTargetInfoWrapper(env, info);
    if (!wrapper) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value result = nullptr;
    napi_create_string_utf8(env, wrapper->inspectorId.c_str(), NAPI_AUTO_LENGTH, &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsBegin(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    EventTargetInfoWrapper* wrapper = GetEventTargetInfoWrapper(env, info);
    if (!wrapper) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, wrapper->IsBegin(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsEnd(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    EventTargetInfoWrapper* wrapper = GetEventTargetInfoWrapper(env, info);
    if (!wrapper) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, wrapper->IsEnd(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value CreateEventTargetInfo(
    napi_env env, const RefPtr<NG::Pattern>& pattern, const std::string& inspectorId)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    napi_value result = nullptr;
    napi_create_object(env, &result);

    auto* wrapper = new EventTargetInfoWrapper(std::move(inspectorId), pattern);
    auto status = napi_wrap(
        env, result, wrapper,
        [](napi_env env, void* data, void* hint) {
            auto* wrapper = static_cast<EventTargetInfoWrapper*>(data);
            if (wrapper) {
                delete wrapper;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("Failed to wrap native object");
        delete wrapper;
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value funcValue = nullptr;
    napi_create_function(env, GET_ID, NAPI_AUTO_LENGTH, GetId, nullptr, &funcValue);
    napi_set_named_property(env, result, GET_ID, funcValue);
    if (pattern) {
        napi_create_function(env, IS_BEGIN, NAPI_AUTO_LENGTH, IsBegin, nullptr, &funcValue);
        napi_set_named_property(env, result, IS_BEGIN, funcValue);
        napi_create_function(env, IS_END, NAPI_AUTO_LENGTH, IsEnd, nullptr, &funcValue);
        napi_set_named_property(env, result, IS_END, funcValue);
    }
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetEventTargetInfo(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_object(env, &result);
    auto attachNode = current->recognizer->GetAttachedNode().Upgrade();
    if (!attachNode) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::Pattern> pattern = nullptr;
    auto scrollablePattern = attachNode->GetPattern<NG::ScrollablePattern>();
    if (scrollablePattern) {
        pattern = scrollablePattern;
    }
    auto swiperPattern = attachNode->GetPattern<NG::SwiperPattern>();
    if (swiperPattern) {
        pattern = swiperPattern;
    }
    result = CreateEventTargetInfo(env, pattern, attachNode->GetInspectorIdValue(""));
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsValid(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->recognizer->IsInResponseLinkRecognizers(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetFingerCount(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_int32(env, static_cast<int32_t>(current->recognizer->GetFingers()), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsFingerCountLimit(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->recognizer->GetLimitFingerCount(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetDistance(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    auto context = PipelineContext::GetCurrentContextSafely();
    if (!context) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value thisArg;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    double distance = DEFAULT_DISTANCE;
    PanRecognizerWrapper* wrapper = nullptr;
    napi_status unwrapStatus = napi_unwrap(env, thisArg, reinterpret_cast<void**>(&wrapper));
    if (unwrapStatus == napi_ok && wrapper && wrapper->type == RecognizerType::PAN && wrapper->panGestureOption) {
        distance = wrapper->panGestureOption->GetDistance();
    } else {
        MultiFingersRecognizerWrapper* multiFingersRecognizerWrapper = nullptr;
        napi_status status = napi_unwrap(env, thisArg, reinterpret_cast<void**>(&multiFingersRecognizerWrapper));
        if (status == napi_ok && multiFingersRecognizerWrapper && multiFingersRecognizerWrapper->recognizer) {
            if (auto recognizer =
                    AceType::DynamicCast<NG::PinchRecognizer>(multiFingersRecognizerWrapper->recognizer)) {
                distance = recognizer->GetDistance();
            }
            if (auto recognizer = AceType::DynamicCast<NG::PanRecognizer>(multiFingersRecognizerWrapper->recognizer)) {
                distance = multiFingersRecognizerWrapper->distance;
            }
        }
    }

    napi_value napiDistance = nullptr;
    napi_create_double(
        env, RoundToMaxPrecision(context->ConvertPxToVp(Dimension(distance, DimensionUnit::PX))), &napiDistance);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, napiDistance, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetDirection(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    napi_value thisArg;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    PanRecognizerWrapper* wrapper = nullptr;
    auto status = napi_unwrap(env, thisArg, reinterpret_cast<void**>(&wrapper));
    uint32_t type = PanDirection::ALL;
    if (status == napi_ok && wrapper && wrapper->type == RecognizerType::PAN && wrapper->panGestureOption) {
        type = wrapper->panGestureOption->GetDirection().type;
    } else {
        MultiFingersRecognizerWrapper* multiFingersRecognizerWrapper = nullptr;
        napi_unwrap(env, thisArg, reinterpret_cast<void**>(&multiFingersRecognizerWrapper));
        if (multiFingersRecognizerWrapper && multiFingersRecognizerWrapper->recognizer) {
            if (auto recognizer = AceType::DynamicCast<NG::PanRecognizer>(multiFingersRecognizerWrapper->recognizer)) {
                type = multiFingersRecognizerWrapper->direction;
            }
        }
    }
    napi_value napiDirection = nullptr;
    napi_create_uint32(env, type, &napiDirection);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, napiDirection, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetSwipeDirection(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto recognizer = AceType::DynamicCast<NG::SwipeRecognizer>(current->recognizer);
    if (!recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value napiDirection = nullptr;
    napi_create_uint32(env, recognizer->GetDirection().type, &napiDirection);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, napiDirection, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetDistanceMap(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto recognizer = AceType::DynamicCast<NG::PanRecognizer>(current->recognizer);
    if (!recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto panDistanceMap = recognizer->GetDistanceMap();
    auto context = PipelineContext::GetCurrentContextSafely();
    if (!context) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value globalObj = nullptr;
    napi_value nativeMap = nullptr;
    napi_value constructor = nullptr;
    napi_get_global(env, &globalObj);
    napi_get_named_property(env, globalObj, "Map", &constructor);
    napi_new_instance(env, constructor, 0, NULL, &nativeMap);
    napi_value setFunc = nullptr;
    napi_get_named_property(env, nativeMap, "set", &setFunc);
    napi_value result;
    for (const auto& item : panDistanceMap) {
        double distance = context->ConvertPxToVp(item.second);
        double roundedDistance = RoundToMaxPrecision(distance);
        napi_value key;
        napi_value value;
        napi_create_int32(env, static_cast<int32_t>(item.first), &key);
        napi_create_double(env, roundedDistance, &value);
        napi_value argv[] = { key, value };
        napi_call_function(env, nativeMap, setFunc, PARAM_SIZE_TWO, argv, &result);
    }
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, nativeMap, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value SetDirection(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv[PARAM_SIZE_ONE] = { nullptr };

    PanRecognizerWrapper* wrapper = GetCurrentPanRecognizerWrapper(env, info, &argc, argv);
    if (!wrapper) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (!wrapper->panGestureOption) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    PanDirection panDirection;
    if (argc != PARAM_SIZE_ONE || !GestureObserverListener::MatchValueType(env, argv[PARAM_SIZE_ZERO], napi_number)) {
        panDirection.type = PanDirection::ALL;
    } else {
        ParsePanDirection(env, argv[PARAM_SIZE_ZERO], panDirection);
    }

    wrapper->panGestureOption->SetDirection(panDirection);
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value SetDistance(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv[PARAM_SIZE_ONE] = { nullptr };

    PanRecognizerWrapper* wrapper = GetCurrentPanRecognizerWrapper(env, info, &argc, argv);
    if (!wrapper) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (!wrapper->panGestureOption) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (argc != PARAM_SIZE_ONE || !GestureObserverListener::MatchValueType(env, argv[PARAM_SIZE_ZERO], napi_number)) {
        wrapper->panGestureOption->SetDistance(DEFAULT_PAN_DISTANCE.ConvertToPx());
    } else {
        double distance;
        napi_get_value_double(env, argv[PARAM_SIZE_ZERO], &distance);
        if (LessNotEqual(distance, 0.0)) {
            wrapper->panGestureOption->SetDistance(DEFAULT_PAN_DISTANCE.ConvertToPx());
        } else {
            wrapper->panGestureOption->SetDistance(Dimension(distance, DimensionUnit::VP).ConvertToPx());
        }
    }
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value SetFingers(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv[PARAM_SIZE_ONE] = { nullptr };

    PanRecognizerWrapper* wrapper = GetCurrentPanRecognizerWrapper(env, info, &argc, argv);
    if (!wrapper) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (!wrapper->panGestureOption) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (argc != PARAM_SIZE_ONE || !GestureObserverListener::MatchValueType(env, argv[PARAM_SIZE_ZERO], napi_number)) {
        wrapper->panGestureOption->SetFingers(DEFAULT_PAN_FINGER);
    } else {
        int32_t fingers;
        napi_get_value_int32(env, argv[PARAM_SIZE_ZERO], &fingers);
        fingers = fingers <= DEFAULT_PAN_FINGER ? DEFAULT_PAN_FINGER : fingers;
        fingers = fingers > DEFAULT_MAX_PAN_FINGERS ? DEFAULT_PAN_FINGER : fingers;
        wrapper->panGestureOption->SetFingers(DEFAULT_PAN_FINGER);
    }
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value GetTapCount(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::ClickRecognizer> tapRecognizer = AceType::DynamicCast<NG::ClickRecognizer>(current->recognizer);
    if (!tapRecognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value count = nullptr;
    napi_create_uint32(env, static_cast<uint32_t>(tapRecognizer->GetCount()), &count);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, count, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsRepeat(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::LongPressRecognizer> longPressRecognizer =
        AceType::DynamicCast<NG::LongPressRecognizer>(current->recognizer);
    if (!longPressRecognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, longPressRecognizer->GetIsRepeat(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetDuration(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::LongPressRecognizer> longPressRecognizer =
        AceType::DynamicCast<NG::LongPressRecognizer>(current->recognizer);
    if (!longPressRecognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value count = nullptr;
    napi_create_int32(env, longPressRecognizer->GetDuration(), &count);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, count, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetAngle(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::RotationRecognizer> rotationRecognizer =
        AceType::DynamicCast<NG::RotationRecognizer>(current->recognizer);
    if (!rotationRecognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value angle = nullptr;
    napi_create_double(env, rotationRecognizer->GetAngle(), &angle);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, angle, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetVelocityThreshold(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));
    MultiFingersRecognizerWrapper* current = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!current || !current->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    RefPtr<NG::SwipeRecognizer> swipeRecognizer = AceType::DynamicCast<NG::SwipeRecognizer>(current->recognizer);
    if (!swipeRecognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto context = PipelineContext::GetCurrentContextSafely();
    if (!context) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value speed = nullptr;
    napi_create_double(env,
        RoundToMaxPrecision(context->ConvertPxToVp(Dimension(swipeRecognizer->GetSpeed(), DimensionUnit::PX))), &speed);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, speed, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

RefPtr<PanGestureOption> CreatePanGestureOption(const RefPtr<NG::PanRecognizer>& panRecognizer)
{
    auto panGestureOption = AceType::MakeRefPtr<PanGestureOption>();
    panGestureOption->SetFingers(panRecognizer->GetFingers());
    panGestureOption->SetDistance(panRecognizer->GetDistance());
    panGestureOption->SetDirection(panRecognizer->GetDirection());
    return panGestureOption;
}

bool WrapPanGestureOption(napi_env env, napi_value result, const RefPtr<NG::PanRecognizer>& panRecognizer,
    const RefPtr<PanGestureOption>& panGestureOption)
{
    auto* wrapper = new PanRecognizerWrapper { panRecognizer, panGestureOption };
    auto status = napi_wrap(
        env, result, wrapper,
        [](napi_env env, void* data, void* hint) {
            auto* current = static_cast<PanRecognizerWrapper*>(data);
            if (current) {
                delete current;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("Failed to wrap native object");
        delete wrapper;
        return false;
    }
    return true;
}

void BindPanGestureFunctions(napi_env env, napi_value result)
{
    const std::vector<std::pair<const char*, napi_callback>> functions = { { GET_DIRECTION, GetDirection },
        { GET_DISTANCE, GetDistance }, { SET_DIRECTION, SetDirection }, { SET_DISTANCE, SetDistance },
        { SET_FINGERS, SetFingers } };

    for (const auto& [name, func] : functions) {
        napi_value funcValue = nullptr;
        napi_create_function(env, name, NAPI_AUTO_LENGTH, func, nullptr, &funcValue);
        napi_set_named_property(env, result, name, funcValue);
    }
}

static napi_value CreatePanGestureOptionsObject(napi_env env, MultiFingersRecognizerWrapper* wrapper)
{
    auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(wrapper->recognizer);
    if (!panRecognizer) {
        return nullptr;
    }

    napi_value result = nullptr;
    napi_create_object(env, &result);

    auto panGestureOption = CreatePanGestureOption(panRecognizer);
    if (!WrapPanGestureOption(env, result, panRecognizer, panGestureOption)) {
        return nullptr;
    }

    BindPanGestureFunctions(env, result);
    return result;
}

static napi_value GetPanGestureOptions(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_escapable_handle_scope(env, &scope));

    auto* wrapper = GetCurrentMultiFingersRecognizerWrapper(env, info);
    if (!wrapper || !wrapper->recognizer) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value result = CreatePanGestureOptionsObject(env, wrapper);
    if (!result) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_value escapedResult = nullptr;
    napi_escape_handle(env, scope, result, &escapedResult);
    napi_close_escapable_handle_scope(env, scope);
    return escapedResult;
}

void BindCommonFunctions(napi_env env, napi_value objValue)
{
    const std::vector<std::pair<const char*, napi_callback>> functions = { { GET_TAG, GetTag }, { GET_TYPE, GetType },
        { IS_BUILT_IN, IsBuiltIn }, { SET_ENABLED, SetEnabled }, { IS_ENABLED, IsEnabled }, { GET_STATE, GetState },
        { GET_EVENT_TARGET_INFO, GetEventTargetInfo }, { IS_VALID, IsValid }, { GET_FINGER_COUNT, GetFingerCount },
        { IS_FINGER_COUNT_LIMIT, IsFingerCountLimit } };

    for (const auto& [name, func] : functions) {
        napi_value funcValue = nullptr;
        napi_create_function(env, name, NAPI_AUTO_LENGTH, func, nullptr, &funcValue);
        napi_set_named_property(env, objValue, name, funcValue);
    }
}

bool WrapRecognizer(napi_env env, napi_value objValue, MultiFingersRecognizerWrapper* wrapper)
{
    auto status = napi_wrap(
        env, objValue, wrapper,
        [](napi_env env, void* data, void* hint) {
            auto* current = static_cast<MultiFingersRecognizerWrapper*>(data);
            if (current) {
                delete current;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("napi_wrap failed");
        return false;
    }
    return true;
}

void BindRecognizerSpecificFunctions(napi_env env, napi_value objValue, NG::GestureListenerType gestureListenerType)
{
    static const std::unordered_map<NG::GestureListenerType, std::vector<std::pair<const char*, napi_callback>>>
        typeFunctions = { { NG::GestureListenerType::PAN,
                              { { GET_PANGESTURE_OPTIONS, GetPanGestureOptions }, { GET_DIRECTION, GetDirection },
                                  { GET_DISTANCE, GetDistance }, { GET_DISTANCE_MAP, GetDistanceMap } } },
            { NG::GestureListenerType::PINCH, { { GET_DISTANCE, GetDistance } } },
            { NG::GestureListenerType::TAP, { { GET_TAP_COUNT, GetTapCount } } },
            { NG::GestureListenerType::LONG_PRESS, { { IS_REPEAT, IsRepeat }, { GET_DURATION, GetDuration } } },
            { NG::GestureListenerType::ROTATION, { { GET_ANGLE, GetAngle } } },
            { NG::GestureListenerType::SWIPE,
                { { GET_VELOCITY_THRESHOLD, GetVelocityThreshold }, { GET_DIRECTION, GetSwipeDirection } } } };

    auto it = typeFunctions.find(gestureListenerType);
    if (it == typeFunctions.end()) {
        return;
    }

    for (const auto& [name, func] : it->second) {
        napi_value funcValue = nullptr;
        napi_create_function(env, name, NAPI_AUTO_LENGTH, func, nullptr, &funcValue);
        napi_set_named_property(env, objValue, name, funcValue);
    }
}

MultiFingersRecognizerWrapper* CreateMultiFingersWrapper(const RefPtr<NG::MultiFingersRecognizer>& recognizer)
{
    auto* wrapper = new MultiFingersRecognizerWrapper();
    wrapper->recognizer = recognizer;

    if (auto panRecognizer = AceType::DynamicCast<NG::PanRecognizer>(recognizer)) {
        wrapper->distance = panRecognizer->GetDistance();
        wrapper->direction = panRecognizer->GetDirection().type;
    }
    return wrapper;
}
} // namespace

void GestureObserverListener::AddGestureRecognizerInfo(napi_env env, napi_value objValueGestureRecognizer,
    const RefPtr<NG::NGGestureRecognizer>& current, NG::GestureListenerType gestureListenerType)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_open_handle_scope(env, &scope));

    auto multiFingersRecognizer = AceType::DynamicCast<NG::MultiFingersRecognizer>(current);
    if (!multiFingersRecognizer) {
        napi_close_handle_scope(env, scope);
        return;
    }

    auto* wrapper = CreateMultiFingersWrapper(multiFingersRecognizer);
    if (!wrapper) {
        napi_close_handle_scope(env, scope);
        return;
    }

    if (!WrapRecognizer(env, objValueGestureRecognizer, wrapper)) {
        delete wrapper;
    }

    BindCommonFunctions(env, objValueGestureRecognizer);
    CreateRecognizerObject(env, objValueGestureRecognizer, current, gestureListenerType);
    napi_close_handle_scope(env, scope);
}

void GestureObserverListener::CreateRecognizerObject(napi_env env, napi_value objValue,
    const RefPtr<NG::NGGestureRecognizer>& current, NG::GestureListenerType gestureListenerType)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL_RETURN_VOID(env, napi_open_handle_scope(env, &scope));

    auto gestureInfo = current->GetGestureInfo();
    if (!gestureInfo) {
        napi_close_handle_scope(env, scope);
        return;
    }

    BindRecognizerSpecificFunctions(env, objValue, gestureListenerType);
    napi_close_handle_scope(env, scope);
}

bool GestureObserverListener::MatchValueType(napi_env env, napi_value value, napi_valuetype targetType)
{
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, value, &valueType);
    return valueType == targetType;
}

} // namespace OHOS::Ace::Napi

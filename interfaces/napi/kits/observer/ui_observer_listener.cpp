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

#include "ui_observer_listener.h"
#include "js_native_api.h"
#include "core/event/ace_events.h"

namespace OHOS::Ace::Napi {
namespace {
constexpr char NAV_BAR[] = "navBar";
constexpr char GET_TAG[] = "getTag";
constexpr char GET_TYPE[] = "getType";
constexpr char IS_BUILT_IN[] = "isBuiltIn";
constexpr char SET_ENABLED[] = "setEnabled";
constexpr char IS_ENABLED[] = "isEnabled";
constexpr char GET_STATE[] = "getState";
constexpr char GET_EVENT_TARGET_INFO[] = "getEventTargetInfo";
constexpr char IS_VALID[] = "isValid";
constexpr char GET_ID[] = "getId";
constexpr char GET_MODIFIER_KEY_STATE[] = "getModifierKeyState";
constexpr char GET_FINGER_COUNT[] = "getFingerCount";
constexpr char IS_FINGER_COUNT_LIMIT[] = "isFingerCountLimit";
constexpr char GET_DIRECTION[] = "getDirection";
constexpr char GET_DISTANCE[] = "getDistance";
constexpr char GET_PANGESTURE_OPTIONS[] = "getPanGestureOptions";
constexpr char SET_DIRECTION[] = "setDirection";
constexpr char SET_DISTANCE[] = "setDistance";
constexpr char SET_FINGERS[] = "setFingers";
constexpr int32_t PARAM_SIZE_ZERO = 0;
constexpr int32_t PARAM_SIZE_ONE = 1;
constexpr int32_t PARAM_SIZE_TWO = 2;
constexpr int32_t PARAM_SIZE_THREE = 3;
constexpr int32_t PARAM_SIZE_SIX = 6;

static NG::PanRecognizer* GetCurrentGestureRecognizer(
    napi_env env, napi_callback_info info, size_t* argc = nullptr, napi_value* argv = nullptr)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, argc, argv, &thisVar, nullptr));

    NG::PanRecognizer* current = nullptr;
    napi_unwrap(env, thisVar, (void**)&current);
    CHECK_NULL_RETURN(current, nullptr);
    return current;
}

static napi_value GetTag(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->GetGestureInfo();
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
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->GetGestureInfo();
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
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    auto gestureInfo = current->GetGestureInfo();
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
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv[PARAM_SIZE_ONE] = { nullptr };
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info, &argc, argv);
    if (!current) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    napi_valuetype valueType = napi_undefined;
    NAPI_CALL(env, napi_typeof(env, argv[PARAM_SIZE_ZERO], &valueType));
    NAPI_ASSERT(env, (valueType == napi_boolean), "Invalid arguments");
    bool isEnabled = false;
    napi_get_value_bool(env, argv[PARAM_SIZE_ZERO], &isEnabled);
    current->SetEnabled(isEnabled);
    napi_close_handle_scope(env, scope);
    return nullptr;
}

static napi_value IsEnabled(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->IsEnabled(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetState(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_int32(env, static_cast<int32_t>(current->GetRefereeState()), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetId(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    void* data = nullptr;
    napi_get_cb_info(env, info, nullptr, nullptr, nullptr, &data);
    auto inspectorId = static_cast<std::string*>(data);
    CHECK_NULL_RETURN(inspectorId, nullptr);
    napi_create_string_utf8(env, (*inspectorId).c_str(), NAPI_AUTO_LENGTH, &result);
    return result;
}

static napi_value GetEventTargetInfo(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_object(env, &result);
    napi_value funcValue = nullptr;
    auto attactNode = current->GetAttachedNode().Upgrade();
    if (!attactNode) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto inspectorId = std::make_unique<std::string>(attactNode->GetInspectorIdValue(""));
    auto* rawPtr = inspectorId.release();
    status = napi_wrap(
        env, result, rawPtr,
        [](napi_env env, void* data, void* hint) {
            auto origin = static_cast<std::string*>(data);
            if (origin) {
                delete origin;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("napi_wrap failed");
        delete rawPtr;
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    napi_create_function(env, GET_ID, 0, GetId, rawPtr, &funcValue);
    napi_set_named_property(env, result, GET_ID, funcValue);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsValid(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->IsInResponseLinkRecognizers(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value GetFingerCount(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_create_int32(env, static_cast<int32_t>(current->GetFingers()), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

static napi_value IsFingerCountLimit(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_get_boolean(env, current->GetLimitFingerCount(), &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

struct PanRecognizerWrapper {
    NG::PanRecognizer* recognizer;
};

static napi_value GetDistance(napi_env env, napi_callback_info info)
{
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value thisArg;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    PanRecognizerWrapper* wrapper = nullptr;
    napi_unwrap(env, thisArg, reinterpret_cast<void**>(&wrapper));
    CHECK_NULL_RETURN(wrapper, nullptr);
    auto current = wrapper->recognizer;
    CHECK_NULL_RETURN(current, nullptr);
    napi_value napiDistance = nullptr;
    napi_create_double(env, current->GetDistance() / scale, &napiDistance);
    return napiDistance;
}

static napi_value GetDirection(napi_env env, napi_callback_info info)
{
    napi_value thisArg;
    napi_get_cb_info(env, info, nullptr, nullptr, &thisArg, nullptr);
    PanRecognizerWrapper* wrapper = nullptr;
    napi_unwrap(env, thisArg, reinterpret_cast<void**>(&wrapper));
    CHECK_NULL_RETURN(wrapper, nullptr);
    auto current = wrapper->recognizer;
    CHECK_NULL_RETURN(current, nullptr);
    napi_value napiDirection = nullptr;
    napi_create_uint32(env, static_cast<uint32_t>(current->GetDirection().type), &napiDirection);
    return napiDirection;
}

static napi_value GetPanGestureOptions(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    NG::PanRecognizer* current = GetCurrentGestureRecognizer(env, info);
    if (!current) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    napi_value result = nullptr;
    napi_value funcValue = nullptr;
    napi_create_object(env, &result);

    PanRecognizerWrapper* wrapper = new PanRecognizerWrapper { current };
    status = napi_wrap(
        env, result, wrapper,
        [](napi_env env, void* data, void* hint) {
            auto castData = reinterpret_cast<PanRecognizerWrapper*>(data);
            if (castData) {
                delete castData;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("Failed to wrap native object");
        delete wrapper;
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    auto setDirection = [](napi_env env, napi_callback_info info) -> napi_value { return nullptr; };
    auto setDistance = [](napi_env env, napi_callback_info info) -> napi_value { return nullptr; };
    auto setFingers = [](napi_env env, napi_callback_info info) -> napi_value { return nullptr; };
    napi_create_function(env, GET_DIRECTION, NAPI_AUTO_LENGTH, GetDirection, nullptr, &funcValue);
    napi_set_named_property(env, result, GET_DIRECTION, funcValue);
    napi_create_function(env, GET_DISTANCE, NAPI_AUTO_LENGTH, GetDistance, nullptr, &funcValue);
    napi_set_named_property(env, result, GET_DISTANCE, funcValue);
    napi_create_function(env, SET_DIRECTION, NAPI_AUTO_LENGTH, setDirection, nullptr, &funcValue);
    napi_set_named_property(env, result, SET_DIRECTION, funcValue);
    napi_create_function(env, SET_DISTANCE, NAPI_AUTO_LENGTH, setDistance, nullptr, &funcValue);
    napi_set_named_property(env, result, SET_DISTANCE, funcValue);
    napi_create_function(env, SET_FINGERS, NAPI_AUTO_LENGTH, setFingers, nullptr, &funcValue);
    napi_set_named_property(env, result, SET_FINGERS, funcValue);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}

bool CheckKeysPressed(const std::vector<KeyCode>& pressedKeyCodes, std::vector<std::string>& checkKeyCodes)
{
    auto hasKeyCode = [pressedKeyCodes](const KeyCode& keyCode) -> bool {
        auto it = std::find(pressedKeyCodes.begin(), pressedKeyCodes.end(), keyCode);
        return it != pressedKeyCodes.end();
    };
    for (auto& checkKeyCode : checkKeyCodes) {
        if (checkKeyCode == "ctrl") {
            if (!hasKeyCode(KeyCode::KEY_CTRL_LEFT) && !hasKeyCode(KeyCode::KEY_CTRL_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "shift") {
            if (!hasKeyCode(KeyCode::KEY_SHIFT_LEFT) && !hasKeyCode(KeyCode::KEY_SHIFT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "alt") {
            if (!hasKeyCode(KeyCode::KEY_ALT_LEFT) && !hasKeyCode(KeyCode::KEY_ALT_RIGHT)) {
                return false;
            }
        } else if (checkKeyCode == "fn") {
            if (!hasKeyCode(KeyCode::KEY_FN)) {
                return false;
            }
        } else {
            return false;
        }
    }
    return true;
}

size_t GetParamLen(napi_env env, napi_value param)
{
    size_t buffSize = 0;
    napi_status status = napi_get_value_string_utf8(env, param, nullptr, 0, &buffSize);
    if (status != napi_ok || buffSize == 0) {
        return 0;
    }
    return buffSize;
}

bool CheckAndParseStr(napi_env env, napi_value arg, std::string& recv)
{
    if (arg == nullptr) {
        return false;
    }

    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, arg, &valueType);
    if (valueType != napi_string) {
        return false;
    }

    size_t msgLen = GetParamLen(env, arg) + 1;
    std::unique_ptr<char[]> message = std::make_unique<char[]>(msgLen);
    size_t ret = 0;
    if (napi_get_value_string_utf8(env, arg, message.get(), msgLen, &ret) != napi_ok) {
        return false;
    }

    recv = message.get();
    return true;
}

static GestureEvent* GetBaseEventInfo(
    napi_env env, napi_callback_info info, size_t* argc = nullptr, napi_value* argv = nullptr)
{
    napi_value thisVar = nullptr;
    NAPI_CALL(env, napi_get_cb_info(env, info, argc, argv, &thisVar, nullptr));

    GestureEvent* baseEventInfo = nullptr;
    napi_status status = napi_unwrap(env, thisVar, (void**)&baseEventInfo);
    if (status != napi_ok) {
        LOGE("Failed to unwrap native object");
        return nullptr;
    }
    CHECK_NULL_RETURN(baseEventInfo, nullptr);
    return baseEventInfo;
}

static napi_value GetModifierKeyState(napi_env env, napi_callback_info info)
{
    napi_escapable_handle_scope scope = nullptr;
    auto status = napi_open_escapable_handle_scope(env, &scope);
    if (status != napi_ok) {
        return nullptr;
    }
    size_t argc = PARAM_SIZE_ONE;
    napi_value argv = nullptr;
    GestureEvent* gestureEventInfo = GetBaseEventInfo(env, info, &argc, &argv);
    if (!gestureEventInfo) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }

    bool ret = false;
    status = napi_is_array(env, argv, &ret);
    if (status != napi_ok) {
        napi_close_escapable_handle_scope(env, scope);
        return nullptr;
    }
    auto pressedKeyCodes = gestureEventInfo->GetPressedKeyCodes();
    bool checkRet = false;
    uint32_t length = 0;
    std::string checkedKeyCode;
    std::vector<std::string> checkedKeyCodes;
    std::vector<std::string> validKeyCodes = { "ctrl", "shift", "alt", "fn" };
    napi_get_array_length(env, argv, &length);

    for (uint32_t i = 0; i < length; ++i) {
        napi_value element = nullptr;
        napi_get_element(env, argv, i, &element);
        std::string errMsg;
        if (CheckAndParseStr(env, element, checkedKeyCode)) {
            auto it = std::find(validKeyCodes.begin(), validKeyCodes.end(), checkedKeyCode);
            if (it != validKeyCodes.end()) {
                checkedKeyCodes.emplace_back(checkedKeyCode);
            }
        }
    }
    checkRet = CheckKeysPressed(pressedKeyCodes, checkedKeyCodes);
    napi_value result = nullptr;
    napi_get_boolean(env, checkRet, &result);
    napi_value newResult = nullptr;
    napi_escape_handle(env, scope, result, &newResult);
    napi_close_escapable_handle_scope(env, scope);
    return newResult;
}
}

void UIObserverListener::OnNavigationStateChange(const NG::NavDestinationInfo& info)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value argv[] = { CreateNavDestinationInfoObj(info) };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnScrollEventStateChange(
    const std::string& id, int32_t uniqueId, NG::ScrollEventType eventType, float offset)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle scrollEvent state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value scrollId = nullptr;
    napi_value frameNodeId = nullptr;
    napi_value scrollEventType = nullptr;
    napi_value scrollOffset = nullptr;
    napi_create_string_utf8(env_, id.c_str(), id.length(), &scrollId);
    napi_create_int32(env_, uniqueId, &frameNodeId);
    napi_create_int32(env_, static_cast<int32_t>(eventType), &scrollEventType);
    napi_create_double(env_, offset, &scrollOffset);
    napi_set_named_property(env_, objValue, "id", scrollId);
    napi_set_named_property(env_, objValue, "uniqueId", frameNodeId);
    napi_set_named_property(env_, objValue, "scrollEvent", scrollEventType);
    napi_set_named_property(env_, objValue, "offset", scrollOffset);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnRouterPageStateChange(const NG::RouterPageInfoNG& pageInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle router page state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiCtx = pageInfo.context;
    napi_value napiIndex = nullptr;
    napi_value napiName = nullptr;
    napi_value napiPath = nullptr;
    napi_value napiState = nullptr;
    napi_value napiPageId = nullptr;
    napi_create_int32(env_, pageInfo.index, &napiIndex);
    napi_create_string_utf8(env_, pageInfo.name.c_str(), pageInfo.name.length(), &napiName);
    napi_create_string_utf8(env_, pageInfo.path.c_str(), pageInfo.path.length(), &napiPath);
    napi_create_int32(env_, static_cast<int32_t>(pageInfo.state), &napiState);
    napi_create_string_utf8(env_, pageInfo.pageId.c_str(), pageInfo.pageId.length(), &napiPageId);
    napi_set_named_property(env_, objValue, "context", napiCtx);
    napi_set_named_property(env_, objValue, "index", napiIndex);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "path", napiPath);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_set_named_property(env_, objValue, "pageId", napiPageId);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDensityChange(double density)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiDensity = nullptr;
    napi_create_double(env_, density, &napiDensity);
    napi_set_named_property(env_, objValue, "density", napiDensity);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDrawOrLayout()
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER, "Handle draw or layout failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnNavDestinationSwitch(const NG::NavDestinationSwitchInfo& switchInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle navDestination switch failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value argv[] = { CreateNavDestinationSwitchInfoObj(switchInfo) };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

napi_value UIObserverListener::CreateNavDestinationSwitchInfoObj(const NG::NavDestinationSwitchInfo& switchInfo)
{
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiOperation = nullptr;
    napi_value napiFrom = nullptr;
    if (switchInfo.from.has_value()) {
        napiFrom = CreateNavDestinationInfoObj(switchInfo.from.value());
    } else {
        napi_create_string_utf8(env_, NAV_BAR, NAPI_AUTO_LENGTH, &napiFrom);
    }
    napi_value napiTo = nullptr;
    if (switchInfo.to.has_value()) {
        napiTo = CreateNavDestinationInfoObj(switchInfo.to.value());
    } else {
        napi_create_string_utf8(env_, NAV_BAR, NAPI_AUTO_LENGTH, &napiTo);
    }
    napi_create_int32(env_, static_cast<int32_t>(switchInfo.operation), &napiOperation);
    napi_set_named_property(env_, objValue, "context", switchInfo.context);
    napi_set_named_property(env_, objValue, "from", napiFrom);
    napi_set_named_property(env_, objValue, "to", napiTo);
    napi_set_named_property(env_, objValue, "operation", napiOperation);
    return objValue;
}

void UIObserverListener::OnWillClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<NG::FrameNode> frameNode)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    
    napi_value objValueClickEvent = nullptr;
    napi_create_object(env_, &objValueClickEvent);

    AddBaseEventInfo(objValueClickEvent, clickInfo);
    AddGestureEventInfoOne(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoTwo(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoThree(objValueClickEvent, gestureEventInfo);
    AddClickEventInfoOne(objValueClickEvent, clickInfo);
    AddClickEventInfoTwo(objValueClickEvent, clickInfo);

    napi_value objValueFrameNode = nullptr;
    napi_create_object(env_, &objValueFrameNode);

    auto container = Container::Current();
    if (container == nullptr) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto frontEnd = container->GetFrontend();
    if (frontEnd == nullptr) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto nodeId = frameNode->GetId();
    objValueFrameNode = frontEnd->GetFrameNodeValueByNodeId(nodeId);

    napi_value argv[] = { objValueClickEvent, objValueFrameNode };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_TWO, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnDidClick(
    const GestureEvent& gestureEventInfo, const ClickInfo& clickInfo, const RefPtr<NG::FrameNode> frameNode)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle density change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    
    napi_value objValueClickEvent = nullptr;
    napi_create_object(env_, &objValueClickEvent);

    AddBaseEventInfo(objValueClickEvent, clickInfo);
    AddGestureEventInfoOne(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoTwo(objValueClickEvent, gestureEventInfo);
    AddGestureEventInfoThree(objValueClickEvent, gestureEventInfo);
    AddClickEventInfoOne(objValueClickEvent, clickInfo);
    AddClickEventInfoTwo(objValueClickEvent, clickInfo);

    napi_value objValueFrameNode = nullptr;
    napi_create_object(env_, &objValueFrameNode);

    auto container = Container::Current();
    if (container == nullptr) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto frontEnd = container->GetFrontend();
    if (frontEnd == nullptr) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto nodeId = frameNode->GetId();
    objValueFrameNode = frontEnd->GetFrameNodeValueByNodeId(nodeId);

    napi_value argv[] = { objValueClickEvent, objValueFrameNode };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_TWO, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnPanGestureStateChange(const GestureEvent& gestureEventInfo,
    const RefPtr<NG::PanRecognizer>& current, const RefPtr<NG::FrameNode> frameNode)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER, "Handle pan gesture change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);

    napi_value objValueGestureEvent = nullptr;
    napi_create_object(env_, &objValueGestureEvent);
    napi_value objValueGestureRecognizer = nullptr;
    napi_create_object(env_, &objValueGestureRecognizer);

    AddBaseEventInfo(objValueGestureEvent, gestureEventInfo);
    AddGestureEventInfoOne(objValueGestureEvent, gestureEventInfo);
    AddGestureEventInfoTwo(objValueGestureEvent, gestureEventInfo);
    AddGestureEventInfoThree(objValueGestureEvent, gestureEventInfo);
    AddGestureEventInfoFour(objValueGestureEvent, gestureEventInfo);
    AddTargetObject(objValueGestureEvent, gestureEventInfo);
    AddGestureRecognizerInfo(objValueGestureRecognizer, current);
    
    napi_value objValueFrameNode = nullptr;
    napi_create_object(env_, &objValueFrameNode);

    auto container = Container::Current();
    if (!container) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto frontEnd = container->GetFrontend();
    if (!frontEnd) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    auto nodeId = frameNode->GetId();
    objValueFrameNode = frontEnd->GetFrameNodeValueByNodeId(nodeId);

    napi_value argv[] = { objValueGestureEvent, objValueGestureRecognizer, objValueFrameNode };
    napi_call_function(env_, nullptr, callback, PARAM_SIZE_THREE, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::OnTabContentStateChange(const NG::TabContentInfo& tabContentInfo)
{
    if (!env_ || !callback_) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER,
            "Handle tabContent state change failed, runtime or callback function invalid!");
        return;
    }
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    napi_value objValue = nullptr;
    napi_value param1 = nullptr;
    napi_value param2 = nullptr;
    napi_value param3 = nullptr;
    napi_value param4 = nullptr;
    napi_value param5 = nullptr;
    napi_value param6 = nullptr;
    napi_create_string_utf8(env_, tabContentInfo.tabContentId.c_str(), tabContentInfo.tabContentId.length(), &param1);
    napi_create_int32(env_, tabContentInfo.tabContentUniqueId, &param2);
    napi_create_int32(env_, static_cast<int32_t>(tabContentInfo.state), &param3);
    napi_create_int32(env_, tabContentInfo.index, &param4);
    napi_create_string_utf8(env_, tabContentInfo.id.c_str(), tabContentInfo.id.length(), &param5);
    napi_create_int32(env_, tabContentInfo.uniqueId, &param6);
    const char *keys[] = {
        "tabContentId",
        "tabContentUniqueId",
        "state",
        "index",
        "id",
        "uniqueId",
    };
    const napi_value values[] = {
        param1,
        param2,
        param3,
        param4,
        param5,
        param6,
    };
    napi_create_object_with_named_properties(env_, &objValue, PARAM_SIZE_SIX, keys, values);
    napi_value argv[] = { objValue };
    napi_call_function(env_, nullptr, callback, 1, argv, nullptr);
    napi_close_handle_scope(env_, scope);
}

napi_valuetype UIObserverListener::GetValueType(napi_env env, napi_value value)
{
    if (value == nullptr) {
        return napi_undefined;
    }

    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, value, &valueType), napi_undefined);
    return valueType;
}

napi_value UIObserverListener::GetNamedProperty(napi_env env, napi_value object, const std::string& propertyName)
{
    if (GetValueType(env, object) != napi_object) {
        napi_value undefined = nullptr;
        NAPI_CALL(env, napi_get_undefined(env, &undefined));
        return undefined;
    }

    napi_value value = nullptr;
    NAPI_CALL(env, napi_get_named_property(env, object, propertyName.c_str(), &value));
    return value;
}

void UIObserverListener::AddBaseEventInfo(napi_value objValueEvent, const BaseEventInfo& baseEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value napiTimeStamp = nullptr;
    napi_value napiSource = nullptr;
    napi_value napiPressure = nullptr;
    napi_value napiTiltX = nullptr;
    napi_value napiTiltY = nullptr;
    napi_value napiSourceTool = nullptr;

    napi_create_double(env_,
        static_cast<double>(baseEventInfo.GetTimeStamp().time_since_epoch().count()), &napiTimeStamp);
    napi_create_double(env_, static_cast<int32_t>(baseEventInfo.GetSourceDevice()), &napiSource);
    napi_create_double(env_, baseEventInfo.GetForce(), &napiPressure);
    if (baseEventInfo.GetTiltX().has_value()) {
        napi_create_double(env_, baseEventInfo.GetTiltX().value(), &napiTiltX);
    }
    if (baseEventInfo.GetTiltY().has_value()) {
        napi_create_double(env_, baseEventInfo.GetTiltY().value(), &napiTiltY);
    }
    napi_create_double(env_, static_cast<int32_t>(baseEventInfo.GetSourceTool()), &napiSourceTool);

    napi_set_named_property(env_, objValueEvent, "timestamp", napiTimeStamp);
    napi_set_named_property(env_, objValueEvent, "source", napiSource);
    napi_set_named_property(env_, objValueEvent, "pressure", napiPressure);
    napi_set_named_property(env_, objValueEvent, "tiltX", napiTiltX);
    napi_set_named_property(env_, objValueEvent, "tiltY", napiTiltY);
    napi_set_named_property(env_, objValueEvent, "sourceTool", napiSourceTool);

    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoOne(napi_value objValueEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiRepeat = GetNamedProperty(env_, objValueEvent, "repeat");
    if (GetValueType(env_, napiRepeat) != napi_null) {
        napi_get_boolean(env_, gestureEventInfo.GetRepeat(), &napiRepeat);
        napi_set_named_property(env_, objValueEvent, "repeat", napiRepeat);
    }
    napi_value napiOffsetX = GetNamedProperty(env_, objValueEvent, "offsetX");
    if (GetValueType(env_, napiOffsetX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetOffsetX() / scale, &napiOffsetX);
        napi_set_named_property(env_, objValueEvent, "offsetX", napiOffsetX);
    }
    napi_value napiOffsetY = GetNamedProperty(env_, objValueEvent, "offsetY");
    if (GetValueType(env_, napiOffsetY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetOffsetY() / scale, &napiOffsetY);
        napi_set_named_property(env_, objValueEvent, "offsetY", napiOffsetY);
    }
    napi_value napiScale = GetNamedProperty(env_, objValueEvent, "scale");
    if (GetValueType(env_, napiScale) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetScale(), &napiScale);
        napi_set_named_property(env_, objValueEvent, "scale", napiScale);
    }
    napi_value napiAngle = GetNamedProperty(env_, objValueEvent, "angle");
    if (GetValueType(env_, napiAngle) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetAngle() / scale, &napiAngle);
        napi_set_named_property(env_, objValueEvent, "angle", napiAngle);
    }
    napi_value napiSpeed = GetNamedProperty(env_, objValueEvent, "speed");
    if (GetValueType(env_, napiSpeed) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetSpeed() / scale, &napiSpeed);
        napi_set_named_property(env_, objValueEvent, "speed", napiSpeed);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoTwo(napi_value objValueEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiGlobalX = GetNamedProperty(env_, objValueEvent, "globalX");
    if (GetValueType(env_, napiGlobalX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetGlobalLocation().GetX() / scale, &napiGlobalX);
        napi_set_named_property(env_, objValueEvent, "globalX", napiGlobalX);
    }
    napi_value napiGlobalY = GetNamedProperty(env_, objValueEvent, "globalY");
    if (GetValueType(env_, napiGlobalY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetGlobalLocation().GetY() / scale, &napiGlobalY);
        napi_set_named_property(env_, objValueEvent, "globalY", napiGlobalY);
    }
    napi_value napiLocalX = GetNamedProperty(env_, objValueEvent, "localX");
    if (GetValueType(env_, napiLocalX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetLocalLocation().GetX() / scale, &napiLocalX);
        napi_set_named_property(env_, objValueEvent, "localX", napiLocalX);
    }
    napi_value napiLocalY = GetNamedProperty(env_, objValueEvent, "localY");
    if (GetValueType(env_, napiLocalY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetLocalLocation().GetY() / scale, &napiLocalY);
        napi_set_named_property(env_, objValueEvent, "localY", napiLocalY);
    }
    napi_value napiPinchCenterX = GetNamedProperty(env_, objValueEvent, "pinchCenterX");
    if (GetValueType(env_, napiPinchCenterX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetPinchCenter().GetX() / scale, &napiPinchCenterX);
        napi_set_named_property(env_, objValueEvent, "pinchCenterX", napiPinchCenterX);
    }
    napi_value napiPinchCenterY = GetNamedProperty(env_, objValueEvent, "pinchCenterY");
    if (GetValueType(env_, napiPinchCenterY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetPinchCenter().GetY() / scale, &napiPinchCenterY);
        napi_set_named_property(env_, objValueEvent, "pinchCenterY", napiPinchCenterY);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoThree(napi_value objValueEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiVelocityX = GetNamedProperty(env_, objValueEvent, "velocityX");
    if (GetValueType(env_, napiVelocityX) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityX() / scale, &napiVelocityX);
        napi_set_named_property(env_, objValueEvent, "velocityX", napiVelocityX);
    }
    napi_value napiVelocityY = GetNamedProperty(env_, objValueEvent, "velocityY");
    if (GetValueType(env_, napiVelocityY) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityY() / scale, &napiVelocityY);
        napi_set_named_property(env_, objValueEvent, "velocityY", napiVelocityY);
    }
    napi_value napiVelocity = GetNamedProperty(env_, objValueEvent, "velocity");
    if (GetValueType(env_, napiVelocity) != napi_null) {
        napi_create_double(env_, gestureEventInfo.GetVelocity().GetVelocityValue() / scale, &napiVelocity);
        napi_set_named_property(env_, objValueEvent, "velocity", napiVelocity);
    }
    napi_value napiAxisHorizontal = nullptr;
    napi_value napiAxisVertical = nullptr;
    napi_value napiDeviceId = nullptr;
    napi_value napiTargetDisplayId = nullptr;
    napi_create_double(env_, gestureEventInfo.GetHorizontalAxis(), &napiAxisHorizontal);
    napi_set_named_property(env_, objValueEvent, "axisHorizontal", napiAxisHorizontal);
    napi_create_double(env_, gestureEventInfo.GetVerticalAxis(), &napiAxisVertical);
    napi_set_named_property(env_, objValueEvent, "axisVertical", napiAxisVertical);
    napi_create_double(env_, gestureEventInfo.GetDeviceId(), &napiDeviceId);
    napi_set_named_property(env_, objValueEvent, "deviceId", napiDeviceId);
    napi_create_double(env_, gestureEventInfo.GetTargetDisplayId(), &napiTargetDisplayId);
    napi_set_named_property(env_, objValueEvent, "targetDisplayId", napiTargetDisplayId);
    AddFingerListInfo(objValueEvent, gestureEventInfo);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddFingerListInfo(napi_value objValueClickEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    const std::list<FingerInfo>& fingerList = gestureEventInfo.GetFingerList();
    napi_value napiFingerList = nullptr;
    napi_create_array(env_, &napiFingerList);
    bool isArray = false;
    if (napi_is_array(env_, napiFingerList, &isArray) != napi_ok || !isArray) {
        napi_close_handle_scope(env_, scope);
        return;
    }
    int32_t index = 0;
    if (fingerList.size() > 0) {
        for (auto finger : fingerList) {
            napi_value napiFinger = nullptr;
            napi_create_object(env_, &napiFinger);
            AddFingerObjectInfo(napiFinger, finger);
            napi_set_element(env_, napiFingerList, index++, napiFinger);
        }
    }
    napi_set_named_property(env_, objValueClickEvent, "fingerList", napiFingerList);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddFingerObjectInfo(napi_value napiFinger, const FingerInfo& finger)
{
    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    napi_value napiId = nullptr;
    napi_create_double(env_, finger.fingerId_, &napiId);
    napi_set_named_property(env_, napiFinger, "id", napiId);
    napi_value napiHand = nullptr;
    napi_create_int32(env_, finger.operatingHand_, &napiHand);
    napi_set_named_property(env_, napiFinger, "hand", napiHand);
    const OHOS::Ace::Offset& globalLocation = finger.globalLocation_;
    const OHOS::Ace::Offset& localLocation = finger.localLocation_;
    const OHOS::Ace::Offset& screenLocaltion = finger.screenLocation_;
    napi_value napiGlobalX = nullptr;
    napi_create_double(env_, globalLocation.GetX() / scale, &napiGlobalX);
    napi_set_named_property(env_, napiFinger, "globalX", napiGlobalX);
    napi_value napiGlobalY = nullptr;
    napi_create_double(env_, globalLocation.GetY() / scale, &napiGlobalY);
    napi_set_named_property(env_, napiFinger, "globalY", napiGlobalY);
    napi_value napiLocalX = nullptr;
    napi_create_double(env_, localLocation.GetX() / scale, &napiLocalX);
    napi_set_named_property(env_, napiFinger, "localX", napiLocalX);
    napi_value napiLocalY = nullptr;
    napi_create_double(env_, localLocation.GetY() / scale, &napiLocalY);
    napi_set_named_property(env_, napiFinger, "localY", napiLocalY);
    napi_value napiDisplayX = nullptr;
    napi_create_double(env_, screenLocaltion.GetX() / scale, &napiDisplayX);
    napi_set_named_property(env_, napiFinger, "displayX", napiDisplayX);
    napi_value napiDisplayY = nullptr;
    napi_create_double(env_, screenLocaltion.GetY() / scale, &napiDisplayY);
    napi_set_named_property(env_, napiFinger, "displayY", napiDisplayY);
}

void UIObserverListener::AddClickEventInfoOne(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    Offset globalOffset = clickInfo.GetGlobalLocation();
    Offset screenOffset = clickInfo.GetScreenLocation();
    napi_value napiDisplayX = GetNamedProperty(env_, objValueClickEvent, "displayX");
    if (GetValueType(env_, napiDisplayX) != napi_null) {
        napi_create_double(env_, screenOffset.GetX() / scale, &napiDisplayX);
        napi_set_named_property(env_, objValueClickEvent, "displayX", napiDisplayX);
    }
    napi_value napiDisplayY = GetNamedProperty(env_, objValueClickEvent, "displayY");
    if (GetValueType(env_, napiDisplayY) != napi_null) {
        napi_create_double(env_, screenOffset.GetY() / scale, &napiDisplayY);
        napi_set_named_property(env_, objValueClickEvent, "displayY", napiDisplayY);
    }
    napi_value napiWindowX = GetNamedProperty(env_, objValueClickEvent, "windowX");
    if (GetValueType(env_, napiWindowX) != napi_null) {
        napi_create_double(env_, globalOffset.GetX() / scale, &napiWindowX);
        napi_set_named_property(env_, objValueClickEvent, "windowX", napiWindowX);
    }
    napi_value napiWindowY = GetNamedProperty(env_, objValueClickEvent, "windowY");
    if (GetValueType(env_, napiWindowY) != napi_null) {
        napi_create_double(env_, globalOffset.GetY() / scale, &napiWindowY);
        napi_set_named_property(env_, objValueClickEvent, "windowY", napiWindowY);
    }
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddClickEventInfoTwo(napi_value objValueClickEvent, const ClickInfo& clickInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    double scale = Dimension(1.0, DimensionUnit::VP).ConvertToPx();
    if (NearZero(scale)) {
        scale = 1.0;
    }
    Offset globalOffset = clickInfo.GetGlobalLocation();
    Offset localOffset = clickInfo.GetLocalLocation();
    napi_value napiScreenX = GetNamedProperty(env_, objValueClickEvent, "screenX");
    if (GetValueType(env_, napiScreenX) != napi_null) {
        napi_create_double(env_, globalOffset.GetX() / scale, &napiScreenX);
        napi_set_named_property(env_, objValueClickEvent, "screenX", napiScreenX);
    }
    napi_value napiScreenY = GetNamedProperty(env_, objValueClickEvent, "screenY");
    if (GetValueType(env_, napiScreenY) != napi_null) {
        napi_create_double(env_, globalOffset.GetY() / scale, &napiScreenY);
        napi_set_named_property(env_, objValueClickEvent, "screenY", napiScreenY);
    }
    napi_value napiX = GetNamedProperty(env_, objValueClickEvent, "x");
    if (GetValueType(env_, napiX) != napi_null) {
        napi_create_double(env_, localOffset.GetX() / scale, &napiX);
        napi_set_named_property(env_, objValueClickEvent, "x", napiX);
    }
    napi_value napiY = GetNamedProperty(env_, objValueClickEvent, "y");
    if (GetValueType(env_, napiY) != napi_null) {
        napi_create_double(env_, localOffset.GetY() / scale, &napiY);
        napi_set_named_property(env_, objValueClickEvent, "y", napiY);
    }
    AddTargetObject(objValueClickEvent, clickInfo);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureEventInfoFour(napi_value objValueEvent, const GestureEvent& gestureEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    std::unique_ptr<GestureEvent> infoHolder = std::make_unique<GestureEvent>(gestureEventInfo);
    auto* info = infoHolder.release();
    status = napi_wrap(
        env_, objValueEvent, info,
        [](napi_env env, void* data, void* hint) {
            GestureEvent* info = reinterpret_cast<GestureEvent*>(data);
            if (info != nullptr) {
                delete info;
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("napi_wrap failed");
        delete info;
        napi_close_handle_scope(env_, scope);
        return;
    }
    napi_value funcValue = nullptr;
    napi_create_function(env_, GET_MODIFIER_KEY_STATE, 0, GetModifierKeyState, nullptr, &funcValue);
    napi_set_named_property(env_, objValueEvent, GET_MODIFIER_KEY_STATE, funcValue);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddGestureRecognizerInfo(
    napi_value objValueGestureRecognizer, const RefPtr<NG::PanRecognizer>& current)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }
    current->IncRefCount();
    status = napi_wrap(
        env_, objValueGestureRecognizer, AceType::RawPtr(current),
        [](napi_env env, void* data, void* hint) {
            NG::PanRecognizer* current = reinterpret_cast<NG::PanRecognizer*>(data);
            if (current != nullptr) {
                current->DecRefCount();
            }
        },
        nullptr, nullptr);
    if (status != napi_ok) {
        LOGE("napi_wrap failed");
        current->DecRefCount();
        napi_close_handle_scope(env_, scope);
        return;
    }

    napi_value funcValue = nullptr;
    napi_create_function(env_, GET_TAG, 0, GetTag, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_TAG, funcValue);
    napi_create_function(env_, GET_TYPE, 0, GetType, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_TYPE, funcValue);
    napi_create_function(env_, IS_BUILT_IN, 0, IsBuiltIn, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, IS_BUILT_IN, funcValue);
    napi_create_function(env_, SET_ENABLED, 0, SetEnabled, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, SET_ENABLED, funcValue);
    napi_create_function(env_, IS_ENABLED, 0, IsEnabled, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, IS_ENABLED, funcValue);
    napi_create_function(env_, GET_STATE, 0, GetState, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_STATE, funcValue);
    napi_create_function(env_, GET_EVENT_TARGET_INFO, 0, GetEventTargetInfo, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_EVENT_TARGET_INFO, funcValue);
    napi_create_function(env_, IS_VALID, 0, IsValid, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, IS_VALID, funcValue);
    napi_create_function(env_, GET_FINGER_COUNT, 0, GetFingerCount, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_FINGER_COUNT, funcValue);
    napi_create_function(env_, IS_FINGER_COUNT_LIMIT, 0, IsFingerCountLimit, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, IS_FINGER_COUNT_LIMIT, funcValue);
    napi_create_function(env_, GET_PANGESTURE_OPTIONS, 0, GetPanGestureOptions, nullptr, &funcValue);
    napi_set_named_property(env_, objValueGestureRecognizer, GET_PANGESTURE_OPTIONS, funcValue);
    napi_close_handle_scope(env_, scope);
}

void UIObserverListener::AddTargetObject(napi_value objValueEvent, const BaseEventInfo& baseEventInfo)
{
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env_, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value napiTargetObject = nullptr;
    napi_create_object(env_, &napiTargetObject);
    const auto& localOffset = baseEventInfo.GetTarget().area.GetOffset();
    const auto& origin = baseEventInfo.GetTarget().origin;

    napi_value napiOffset = nullptr;
    napi_create_object(env_, &napiOffset);
    napi_value napiX = nullptr;
    napi_create_double(env_, localOffset.GetX().ConvertToVp(), &napiX);
    napi_set_named_property(env_, napiOffset, "x", napiX);
    napi_value napiY = nullptr;
    napi_create_double(env_, localOffset.GetY().ConvertToVp(), &napiY);
    napi_set_named_property(env_, napiOffset, "y", napiY);
    napi_set_named_property(env_, napiTargetObject, "position", napiOffset);

    napi_value napiGlobalOffset = nullptr;
    napi_create_object(env_, &napiGlobalOffset);
    napi_value napiGlobalX = nullptr;
    napi_create_double(env_, localOffset.GetX().ConvertToVp() + origin.GetX().ConvertToVp(),
        &napiGlobalX);
    napi_set_named_property(env_, napiGlobalOffset, "x", napiGlobalX);
    napi_value napiGlobalY = nullptr;
    napi_create_double(env_, localOffset.GetY().ConvertToVp() + origin.GetY().ConvertToVp(),
        &napiGlobalY);
    napi_set_named_property(env_, napiGlobalOffset, "y", napiGlobalY);
    napi_set_named_property(env_, napiTargetObject, "globalPosition", napiGlobalOffset);

    napi_value napiArea = nullptr;
    napi_create_object(env_, &napiArea);
    napi_value napiWidth = nullptr;
    napi_create_double(env_, baseEventInfo.GetTarget().area.GetWidth().ConvertToVp(), &napiWidth);
    napi_set_named_property(env_, napiArea, "width", napiWidth);
    napi_value napiHeight = nullptr;
    napi_create_double(env_, baseEventInfo.GetTarget().area.GetHeight().ConvertToVp(), &napiHeight);
    napi_set_named_property(env_, napiArea, "height", napiHeight);
    napi_set_named_property(env_, napiTargetObject, "area", napiArea);
    napi_value id = nullptr;
    napi_create_string_utf8(env_, baseEventInfo.GetTarget().id.c_str(), NAPI_AUTO_LENGTH, &id);
    napi_set_named_property(env_, napiTargetObject, "id", id);

    napi_set_named_property(env_, objValueEvent, "target", napiTargetObject);
    napi_close_handle_scope(env_, scope);
}

napi_value UIObserverListener::CreateNavDestinationInfoObj(const NG::NavDestinationInfo& info)
{
    napi_value objValue = nullptr;
    napi_create_object(env_, &objValue);
    napi_value napiNavId = nullptr;
    napi_value napiName = nullptr;
    napi_value napiState = nullptr;
    napi_value napiIdx = nullptr;
    napi_value napiNavDesId = nullptr;
    napi_create_string_utf8(env_, info.navigationId.c_str(), info.navigationId.length(), &napiNavId);
    napi_create_string_utf8(env_, info.name.c_str(), info.name.length(), &napiName);
    napi_create_int32(env_, static_cast<int32_t>(info.state), &napiState);
    napi_create_int32(env_, info.index, &napiIdx);
    napi_create_string_utf8(env_, info.navDestinationId.c_str(), info.navDestinationId.length(), &napiNavDesId);
    napi_set_named_property(env_, objValue, "navigationId", napiNavId);
    napi_set_named_property(env_, objValue, "name", napiName);
    napi_set_named_property(env_, objValue, "state", napiState);
    napi_set_named_property(env_, objValue, "index", napiIdx);
    napi_set_named_property(env_, objValue, "param", info.param);
    napi_set_named_property(env_, objValue, "navDestinationId", napiNavDesId);
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_FIFTEEN)) {
        napi_value napiMode = nullptr;
        napi_value napiUniqueId = nullptr;
        napi_create_int32(env_, static_cast<int32_t>(info.mode), &napiMode);
        napi_create_int32(env_, static_cast<int32_t>(info.uniqueId), &napiUniqueId);
        napi_set_named_property(env_, objValue, "mode", napiMode);
        napi_set_named_property(env_, objValue, "uniqueId", napiUniqueId);
    }
    return objValue;
}

napi_value UIObserverListener::GetNapiCallback()
{
    napi_value callback = nullptr;
    napi_get_reference_value(env_, callback_, &callback);
    return callback;
}

bool UIObserverListener::NapiEqual(napi_value cb)
{
    bool isEquals = false;
    napi_strict_equals(env_, cb, GetNapiCallback(), &isEquals);
    return isEquals;
}
} // namespace OHOS::Ace::Napi

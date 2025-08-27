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

#include "gesture_observer.h"

#include "gesture_observer_listener.h"
#include "interfaces/napi/kits/observer/ui_observer_listener.h"

#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::Napi {

constexpr napi_status NAPI_ERR = napi_status::napi_generic_failure;
constexpr size_t ARG_COUNT_ONE = 1;
constexpr size_t ARG_COUNT_TWO = 2;
constexpr size_t ARG_COUNT_THREE = 3;

constexpr uint32_t WILL_START = 0;
constexpr uint32_t WILL_END = 1;

static constexpr size_t PARAM_INDEX_ZERO = 0;
static constexpr size_t PARAM_INDEX_ONE = 1;
static constexpr size_t PARAM_INDEX_TWO = 2;

std::unordered_map<NG::GestureListenerType,
    std::unordered_map<NG::GestureActionPhase, std::list<std::shared_ptr<UIObserverListener>>>>
    GestureObserver::GestureObserverListeners_;
std::mutex GestureObserver::mutex_;

bool GestureObserver::isGestureHandleFuncSetted_ = false;

bool ParseGestureListenerType(napi_env env, napi_value value, NG::GestureListenerType& outType)
{
    if (!GestureObserverListener::MatchValueType(env, value, napi_number)) {
        return false;
    }

    uint32_t typeValue;
    napi_get_value_uint32(env, value, &typeValue);

    switch (typeValue) {
        case static_cast<uint32_t>(NG::GestureListenerType::TAP):
        case static_cast<uint32_t>(NG::GestureListenerType::LONG_PRESS):
        case static_cast<uint32_t>(NG::GestureListenerType::PAN):
        case static_cast<uint32_t>(NG::GestureListenerType::PINCH):
        case static_cast<uint32_t>(NG::GestureListenerType::SWIPE):
        case static_cast<uint32_t>(NG::GestureListenerType::ROTATION):
            outType = static_cast<NG::GestureListenerType>(typeValue);
            return true;
        default:
            return false;
    }
}

bool ParseGestureActionPhase(
    napi_env env, napi_value value, NG::GestureActionPhase& outPhase, NG::GestureListenerType gestureListenerType)
{
    if (!GestureObserverListener::MatchValueType(env, value, napi_number)) {
        return false;
    }

    uint32_t phaseValue;
    napi_get_value_uint32(env, value, &phaseValue);
    switch (phaseValue) {
        case static_cast<uint32_t>(NG::GestureActionPhase::WILL_START):
            outPhase = static_cast<NG::GestureActionPhase>(phaseValue);
            return true;
        case static_cast<uint32_t>(NG::GestureActionPhase::WILL_END):
            if (gestureListenerType == NG::GestureListenerType::TAP ||
                gestureListenerType == NG::GestureListenerType::SWIPE) {
                return false;
            }
            outPhase = static_cast<NG::GestureActionPhase>(phaseValue);
            return true;
        default:
            return false;
    }
}

bool ParseActionPhasesArray(napi_env env, napi_value arrayValue, std::unordered_set<NG::GestureActionPhase>& outPhases,
    NG::GestureListenerType gestureListenerType)
{
    bool isArray;
    napi_is_array(env, arrayValue, &isArray);
    if (!isArray) {
        return false;
    }

    uint32_t arrayLength;
    napi_get_array_length(env, arrayValue, &arrayLength);
    for (uint32_t i = 0; i < arrayLength; ++i) {
        napi_value element;
        napi_get_element(env, arrayValue, i, &element);

        NG::GestureActionPhase phase;
        if (!ParseGestureActionPhase(env, element, phase, gestureListenerType)) {
            continue;
        }
        outPhases.insert(phase);
    }
    return !outPhases.empty();
}

bool ParseGestureObserverConfigs(napi_env env, napi_value configValue,
    std::unordered_set<NG::GestureActionPhase>& outPhase, NG::GestureListenerType gestureListenerType)
{
    napi_valuetype valueType;
    napi_typeof(env, configValue, &valueType);
    if (valueType != napi_object) {
        return false;
    }

    napi_value actionPhasesValue;
    napi_status status = napi_get_named_property(env, configValue, "actionPhases", &actionPhasesValue);
    if (status != napi_ok) {
        return false;
    }

    if (!ParseActionPhasesArray(env, actionPhasesValue, outPhase, gestureListenerType)) {
        return false;
    }
    return true;
}

napi_value AddGestureListenerType(napi_env env)
{
    napi_value gestureListenerType = nullptr;
    napi_value prop = nullptr;
    NAPI_CALL(env, napi_create_object(env, &gestureListenerType));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::TAP), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "TAP", prop));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::LONG_PRESS), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "LONG_PRESS", prop));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::PAN), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "PAN", prop));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::PINCH), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "PINCH", prop));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::SWIPE), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "SWIPE", prop));
    NAPI_CALL(env, napi_create_uint32(env, static_cast<uint32_t>(NG::GestureListenerType::ROTATION), &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureListenerType, "ROTATION", prop));
    return gestureListenerType;
}

napi_value AddGestureActionPhase(napi_env env)
{
    napi_value gestureActionPhase = nullptr;
    napi_value prop = nullptr;
    NAPI_CALL(env, napi_create_object(env, &gestureActionPhase));
    NAPI_CALL(env, napi_create_uint32(env, WILL_START, &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureActionPhase, "WILL_START", prop));
    NAPI_CALL(env, napi_create_uint32(env, WILL_END, &prop));
    NAPI_CALL(env, napi_set_named_property(env, gestureActionPhase, "WILL_END", prop));
    return gestureActionPhase;
}

napi_status GestureObserver::DefineGestureObserver(napi_env env, napi_value exports)
{
    napi_property_descriptor gestureObserverDesc[] = {
        DECLARE_NAPI_FUNCTION("addGlobalGestureListener", AddGlobalGestureListener),
        DECLARE_NAPI_FUNCTION("removeGlobalGestureListener", RemoveGlobalGestureListener),
        DECLARE_NAPI_PROPERTY("GestureListenerType", AddGestureListenerType(env)),
        DECLARE_NAPI_PROPERTY("GestureActionPhase", AddGestureActionPhase(env)),
    };
    NAPI_CALL_BASE(env,
        napi_define_properties(
            env, exports, sizeof(gestureObserverDesc) / sizeof(gestureObserverDesc[0]), gestureObserverDesc),
        NAPI_ERR);
    return napi_ok;
}

napi_value GestureObserver::AddGlobalGestureListener(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = ARG_COUNT_THREE;
    napi_value argv[ARG_COUNT_THREE] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc != ARG_COUNT_THREE) {
        napi_close_handle_scope(env, scope);
        LOGE("Invalid arguments");
        return nullptr;
    }
    NG::GestureListenerType gestureListenerType;
    if (!ParseGestureListenerType(env, argv[PARAM_INDEX_ZERO], gestureListenerType)) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    std::unordered_set<NG::GestureActionPhase> outPhases;
    if (!ParseGestureObserverConfigs(env, argv[PARAM_INDEX_ONE], outPhases, gestureListenerType)) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }

    if (!isGestureHandleFuncSetted_) {
        NG::UIObserverHandler::GetInstance().SetHandleGestureHandleFunc(&HandleGestureAccept);
        isGestureHandleFuncSetted_ = true;
    }

    auto listener = std::make_shared<UIObserverListener>(env, argv[PARAM_INDEX_TWO]);
    RegisterGlobalGestureListener(gestureListenerType, outPhases, listener);
    napi_close_handle_scope(env, scope);
    return nullptr;
}

napi_value GestureObserver::RemoveGlobalGestureListener(napi_env env, napi_callback_info info)
{
    napi_handle_scope scope = nullptr;
    NAPI_CALL(env, napi_open_handle_scope(env, &scope));
    size_t argc = ARG_COUNT_TWO;
    napi_value argv[ARG_COUNT_TWO] = { nullptr };
    napi_get_cb_info(env, info, &argc, argv, nullptr, nullptr);
    if (argc != ARG_COUNT_ONE && argc != ARG_COUNT_TWO) {
        napi_close_handle_scope(env, scope);
        LOGE("Invalid arguments");
        return nullptr;
    }
    NG::GestureListenerType gestureListenerType;
    if (!ParseGestureListenerType(env, argv[PARAM_INDEX_ZERO], gestureListenerType)) {
        napi_close_handle_scope(env, scope);
        return nullptr;
    }
    if (argc == ARG_COUNT_ONE) {
        UnRegisterGlobalGestureListener(gestureListenerType, nullptr);
    }
    if (argc == ARG_COUNT_TWO && GestureObserverListener::MatchValueType(env, argv[PARAM_INDEX_ONE], napi_function)) {
        UnRegisterGlobalGestureListener(gestureListenerType, argv[PARAM_INDEX_ONE]);
    }
    napi_close_handle_scope(env, scope);
    return nullptr;
}

void GestureObserver::RegisterGlobalGestureListener(NG::GestureListenerType gestureListenerType,
    const std::unordered_set<NG::GestureActionPhase>& outPhase, const std::shared_ptr<UIObserverListener>& listener)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = GestureObserverListeners_.find(gestureListenerType);
    if (iter == GestureObserverListeners_.end()) {
        std::unordered_map<NG::GestureActionPhase, std::list<std::shared_ptr<UIObserverListener>>> phaseMap;
        for (const auto& phase : outPhase) {
            phaseMap.emplace(phase, std::list<std::shared_ptr<UIObserverListener>>({ listener }));
        }
        GestureObserverListeners_.emplace(gestureListenerType, std::move(phaseMap));
        return;
    }
    auto& holder = iter->second;
    for (const auto& phase : outPhase) {
        auto phaseIter = holder.find(phase);
        if (phaseIter == holder.end()) {
            holder.emplace(phase, std::list<std::shared_ptr<UIObserverListener>> { listener });
        } else {
            auto& listenerList = phaseIter->second;
            if (std::find(listenerList.begin(), listenerList.end(), listener) != listenerList.end()) {
                continue;
            }
            listenerList.emplace_back(listener);
        }
    }
}

void GestureObserver::UnRegisterGlobalGestureListener(NG::GestureListenerType gestureListenerType, napi_value callback)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = GestureObserverListeners_.find(gestureListenerType);
    if (iter == GestureObserverListeners_.end()) {
        return;
    }
    auto& phaseMap = iter->second;
    if (callback == nullptr) {
        phaseMap.clear();
        return;
    }

    for (auto phaseIter = phaseMap.begin(); phaseIter != phaseMap.end();) {
        auto& listenerList = phaseIter->second;
        listenerList.erase(
            std::remove_if(
                listenerList.begin(),
                listenerList.end(),
                [callback](const std::shared_ptr<UIObserverListener>& registeredListener) {
                    return registeredListener->NapiEqual(callback);
                }),
            listenerList.end()
        );
        if (listenerList.empty()) {
            phaseIter = phaseMap.erase(phaseIter);
        } else {
            ++phaseIter;
        }
    }

    if (phaseMap.empty()) {
        GestureObserverListeners_.erase(iter);
    }
}

void GestureObserver::HandleGestureAccept(NG::GestureListenerType gestureListenerType,
    const GestureEvent& gestureEventInfo, const RefPtr<NG::NGGestureRecognizer>& current,
    const RefPtr<NG::FrameNode>& frameNode, NG::GestureActionPhase phase)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (!current) {
        TAG_LOGW(AceLogTag::ACE_OBSERVER, "Handle gesture accept failed, recognizer is null");
        return;
    }
    auto env = GetCurrentNapiEnv();
    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    auto iter = GestureObserverListeners_.find(gestureListenerType);
    if (iter == GestureObserverListeners_.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    auto& holder = iter->second;
    auto phaseIter = holder.find(phase);
    if (phaseIter == holder.end()) {
        napi_close_handle_scope(env, scope);
        return;
    }
    for (const auto& listener : phaseIter->second) {
        listener->OnGestureStateChange(gestureListenerType, gestureEventInfo, current, frameNode, phase);
    }
    napi_close_handle_scope(env, scope);
}

napi_env GestureObserver::GetCurrentNapiEnv()
{
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_RETURN(engine, nullptr);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    CHECK_NULL_RETURN(nativeEngine, nullptr);
    return reinterpret_cast<napi_env>(nativeEngine);
}
} // namespace OHOS::Ace::Napi

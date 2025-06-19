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

#ifndef FOUNDATION_ACE_INTERFACES_GESTURE_GESTURE_OBSERVER_H
#define FOUNDATION_ACE_INTERFACES_GESTURE_GESTURE_OBSERVER_H

#include <list>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <unordered_set>

#include "napi/native_api.h"

#include "base/memory/ace_type.h"
#include "core/gestures/gesture_event.h"

namespace OHOS::Ace::NG {
enum class GestureListenerType;
enum class GestureActionPhase;
class NGGestureRecognizer;
class FrameNode;
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::Napi {

class UIObserverListener;

class GestureObserver final {
public:
    GestureObserver() = default;
    ~GestureObserver() = default;
    static napi_status DefineGestureObserver(napi_env env, napi_value exports);

private:
    static napi_value AddGlobalGestureListener(napi_env env, napi_callback_info info);
    static napi_value RemoveGlobalGestureListener(napi_env env, napi_callback_info info);
    static void RegisterGlobalGestureListener(NG::GestureListenerType gestureListenerType,
        const std::unordered_set<NG::GestureActionPhase>& outPhase,
        const std::shared_ptr<UIObserverListener>& listener);
    static void UnRegisterGlobalGestureListener(NG::GestureListenerType gestureListenerType, napi_value callback);
    static napi_env GetCurrentNapiEnv();
    static void HandleGestureAccept(NG::GestureListenerType gestureListenerType, const GestureEvent& gestureEventInfo,
        const RefPtr<NG::NGGestureRecognizer>& current, const RefPtr<NG::FrameNode>& frameNode,
        NG::GestureActionPhase phase);

    static std::unordered_map<NG::GestureListenerType,
        std::unordered_map<NG::GestureActionPhase, std::list<std::shared_ptr<UIObserverListener>>>>
        GestureObserverListeners_;
    static bool isGestureHandleFuncSetted_;
    static std::mutex mutex_;
};

} // namespace OHOS::Ace::Napi
#endif // FOUNDATION_ACE_INTERFACES_GESTURE_GESTURE_OBSERVER_H

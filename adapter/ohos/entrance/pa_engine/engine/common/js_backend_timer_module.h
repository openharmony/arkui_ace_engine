/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_TIMER_MODULE_H
#define FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_TIMER_MODULE_H

#include <mutex>
#include <unordered_map>

#include "adapter/ohos/entrance/pa_engine/backend_delegate.h"
#include "base/thread/cancelable_callback.h"
#include "native_engine/native_engine.h"

namespace OHOS::Ace {
struct TimerCallbackNode {
    std::shared_ptr<NativeReference> func;
    std::vector<std::shared_ptr<NativeReference>> params;
    NativeEngine* engine;
};

class JsBackendTimerModule final {
public:
    JsBackendTimerModule() = default;
    ~JsBackendTimerModule() = default;

    static JsBackendTimerModule* GetInstance();
    void InitTimerModule(NativeEngine* engine, const RefPtr<BackendDelegate>& delegate);

    uint32_t AddCallBack(const std::shared_ptr<NativeReference>& func,
        const std::vector<std::shared_ptr<NativeReference>>& params, NativeEngine* engine);
    bool GetCallBackById(uint32_t callbackId, std::shared_ptr<NativeReference>& func,
        std::vector<std::shared_ptr<NativeReference>>& params, NativeEngine** engine);
    void TimerCallback(uint32_t callbackId, int64_t delayTime, bool isInterval);
    void PostTimerCallback(uint32_t callbackId, int64_t delayTime, bool isInterval, bool isFirst, NativeEngine* engine);
    void RemoveTimerCallback(uint32_t callbackId);

private:
    void AddDelegate(NativeEngine* engine, const RefPtr<BackendDelegate>& delegate);
    RefPtr<BackendDelegate> GetDelegateWithoutLock(NativeEngine* engine);

    std::mutex mutex_;
    uint32_t callbackId_ = 0;
    std::unordered_map<uint32_t, TimerCallbackNode> callbackNodeMap_;
    std::unordered_map<uint32_t, CancelableCallback<void()>> timeoutTaskMap_;
    std::unordered_map<NativeEngine*, RefPtr<BackendDelegate>> delegateMap_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_ADAPTER_OHOS_ENTRANCE_PA_ENGINE_ENGINE_COMMON_JS_BACKEND_TIMER_MODULE_H

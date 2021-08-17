/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_COMMON_JS_BACKEND_ENGINE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_COMMON_JS_BACKEND_ENGINE_H

#include <string>

#include "core/common/backend.h"
#include "frameworks/bridge/pa_backend/backend_delegate.h"

namespace OHOS::Ace::Framework {
class JsBackendEngineInstance {
public:
    JsBackendEngineInstance() = default;
    virtual ~JsBackendEngineInstance() = default;
};

class JsBackendEngine : public AceType {
    DECLARE_ACE_TYPE(JsBackendEngine, AceType);

public:
    JsBackendEngine() = default;
    virtual ~JsBackendEngine() = default;

    virtual bool Initialize(const RefPtr<BackendDelegate>& delegate) = 0;

    virtual void LoadJs(const std::string& url) = 0;

    virtual void SetJsMessageDispatcher(const RefPtr<JsMessageDispatcher>& dispatcher) = 0;

    virtual void FireAsyncEvent(const std::string &eventId, const std::string &param) = 0;

    virtual void FireSyncEvent(const std::string &eventId, const std::string &param) = 0;

    virtual void DestroyApplication(const std::string& packageName) = 0;

private:
    std::string instanceName_;
};
} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_PA_BACKEND_ENGINE_COMMON_JS_BACKEND_ENGINE_H

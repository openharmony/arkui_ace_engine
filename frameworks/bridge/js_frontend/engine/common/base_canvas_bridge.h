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

#ifndef FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_BASE_CANVAS_BRIDGE_H
#define FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_BASE_CANVAS_BRIDGE_H

#include <cstdint>
#include "base/memory/ace_type.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"

namespace OHOS::Ace::Framework {
class BaseCanvasBridge : public virtual AceType {
    DECLARE_ACE_TYPE(BaseCanvasBridge, AceType);

public:
    virtual void OnJsEngineDestroy() {}
    virtual int32_t GetBridgeId() const
    {
        return -1;
    }
    virtual shared_ptr<JsValue> GetBridge(const shared_ptr<JsRuntime>& runtime)
    {
        return nullptr;
    }
    virtual void HandleJsContext(const shared_ptr<JsRuntime>& runtime, int32_t id, const std::string& args) {}
    virtual void HandleToDataURL(const shared_ptr<JsRuntime>& runtime, int32_t id, const std::string& args) {}
    virtual const shared_ptr<JsValue>& GetRenderContext() const
    {
        static shared_ptr<JsValue> empty;
        return empty;
    }

    virtual const shared_ptr<JsValue>& GetDataURL() const
    {
        static shared_ptr<JsValue> empty;
        return empty;
    }
};
} // namespace OHOS::Ace::Framework

#endif // FOUNDATION_ACE_FRAMEWORKS_BRIDGE_JS_FRONTEND_ENGINE_COMMON_BASE_CANVAS_BRIDGE_H

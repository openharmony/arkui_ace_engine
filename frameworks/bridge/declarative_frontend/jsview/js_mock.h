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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H

#include "bridge/declarative_frontend/engine/bindings.h"
#include "bridge/declarative_frontend/engine/bindings_defines.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {
class JSMock {
public:
    static void JSBind(BindingTarget globalObj);
    static bool PreloadWorkerRequireNative(const shared_ptr<JsRuntime>& runtime, const shared_ptr<JsValue>& global);
    static bool InitModule(const shared_ptr<JsRuntime>& runtime, shared_ptr<JsValue>& thisObj,
        const std::string& moduleName);
};

class JSMockBaseNode {
public:
    JSMockBaseNode() = default;
    ~JSMockBaseNode() = default;

    static void JSBind(BindingTarget globalObj);
    static void ConstructorCallback(const JSCallbackInfo& info) {}
    static void DestructorCallback(JSMockBaseNode* node) {}
    void FinishUpdateFunc(const JSCallbackInfo& info) {}
    void Create(const JSCallbackInfo& info) {}
    void PostTouchEvent(const JSCallbackInfo& info) {}
    void UpdateStart(const JSCallbackInfo& info) {}
    void UpdateEnd(const JSCallbackInfo& info) {}
    void Dispose(const JSCallbackInfo& info) {}
};

class JSMockViewPU {
public:
    JSMockViewPU() = default;
    ~JSMockViewPU() = default;

    static void JSBind(BindingTarget globalObj, std::string name);
    void Id(const JSCallbackInfo& info) {}
    void UpdateStateVars(const JSCallbackInfo& info) {}
    void AboutToReuseInternal(const JSCallbackInfo& info) {}
    void AboutToRecycleInternal(const JSCallbackInfo& info) {}
    void UpdateDirtyElements(const JSCallbackInfo& info) {}
};

class JSMockScopeUtil {
public:
    JSMockScopeUtil() = default;
    ~JSMockScopeUtil() = default;

    static void JSBind(BindingTarget globalObj);
    static void SyncInstanceId(const JSCallbackInfo& info) {}
    static void RestoreInstanceId(const JSCallbackInfo& info) {}
};

class MockCustomDialogController {
public:
    MockCustomDialogController() = default;
    ~MockCustomDialogController() = default;

    static void JSBind(BindingTarget globalObj);
    void Open(const JSCallbackInfo& info) {}
    void Close(const JSCallbackInfo& info) {}
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_MOCK_H

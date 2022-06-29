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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DISTRIBUTED_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DISTRIBUTED_H

#include "base/memory/referenced.h"
#include "bridge/declarative_frontend/engine/bindings.h"
#include "core/common/storage/storage_proxy.h"
#include "frameworks/bridge/declarative_frontend/engine/js_types.h"

namespace OHOS::Ace::Framework {

class JSDistributed final : public Referenced {
public:
    JSDistributed(const std::string& sessionId) : sessionId_(sessionId) {}

    void Set(const JSCallbackInfo& args);
    void Get(const JSCallbackInfo& args);
    void Delete(const JSCallbackInfo& args);

    static void ConstructorCallback(const JSCallbackInfo& args);
    static void DestructorCallback(JSDistributed* obj);

    static void JSBind(BindingTarget globalObj);

    void Init(const JSRef<JSObject>& object, const std::string& sessionId);

    void OnDataOnChanged(const std::string& key);

    void OnStatusNotify(const std::string& onlineStatus);

private:
    std::string sessionId_;

    JSRef<JSFunc> onDataOnChange_;
    JSRef<JSFunc> onConnected_;
    JSRef<JSObject> object_;
    RefPtr<Storage> storage_;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_JS_DISTRIBUTED_H
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
#ifndef FOUNDATION_ACE_INTERFACE_INNERKITS_INSPECTOR_H
#define FOUNDATION_ACE_INTERFACE_INNERKITS_INSPECTOR_H

#include <cstdint>
#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi { // namespace
using namespace OHOS::Ace::Framework;

enum class CalloutType {
    LAYOUTCALLOUT = 0,
    DRAWCALLOUT,
    DRAWCHILDRENCALLOUT,
    LAYOUTCHILDRENCALLOUT,
    UNKNOW,
};

class ComponentObserver {
public:
    explicit ComponentObserver(const std::string& componentId) : componentId_(componentId) {}
    explicit ComponentObserver(const int32_t uniqueId) : uniqueId_(uniqueId) {}
    ~ComponentObserver() {}

    void Initialize(napi_env env, napi_value thisVar);
    void callUserFunction(napi_env env, std::list<napi_ref>& cbList);
    std::list<napi_ref>::iterator FindCbList(napi_env env, napi_value cb, CalloutType calloutType);
    void NapiSerializer(napi_env& env, napi_value& result);
    void AddCallbackToList(
        napi_value cb, std::list<napi_ref>& cbList, CalloutType calloutType, napi_env env, napi_handle_scope scope);
    void DeleteCallbackFromList(
        size_t argc, std::list<napi_ref>& cbList, CalloutType calloutType, napi_value cb, napi_env env);
    void DeleteLayoutChildrenCallbackFromList(
        size_t argc, std::list<napi_ref>& cbList, CalloutType calloutType, napi_value cb, napi_env env);
    void Destroy(napi_env env);
    void UpdateDrawLayoutChildObserver(bool isClearLayoutObserver, bool isClearDrawObserver);

    RefPtr<InspectorEvent> layoutEvent_;
    RefPtr<InspectorEvent> drawEvent_;
    RefPtr<InspectorEvent> drawChildrenEvent_;
    RefPtr<InspectorEvent> layoutChildrenEvent_;
    std::string componentId_;
    int32_t uniqueId_ = -1;
    std::list<napi_ref> cbLayoutList_;
    std::list<napi_ref> cbDrawList_;
    std::list<napi_ref> cbDrawChildrenList_;
    std::list<napi_ref> cbLayoutChildrenList_;
    int32_t instanceId_ = -1;
    void SetEngine(const RefPtr<Framework::JsEngine>& engine)
    {
        weakEngine_ = engine;
    }

private:
    void FunctionOnLayoutChildren(napi_env& env, napi_value result);
    void FunctionOffLayoutChildren(napi_env& env, napi_value result);
    void FunctionOn(napi_env& env, napi_value result, const char* funName);
    void FunctionOff(napi_env& env, napi_value result, const char* funName);
    WeakPtr<Framework::JsEngine> weakEngine_;
};
} // namespace OHOS::Ace::Napi
#endif

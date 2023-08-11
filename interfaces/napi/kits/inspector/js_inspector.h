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

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"

#include "base/log/log.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/js_frontend/engine/common/js_engine.h"

namespace OHOS::Ace::Napi { // namespace
using namespace OHOS::Ace::Framework;

enum class CalloutType {
    LAYOUTCALLOUT = 0,
    DRAWCALLOUT,
    UNKNOW,
};

class ComponentObserver {
public:
    explicit ComponentObserver(const std::string& componentId) : componentId_(componentId) {}
    ~ComponentObserver()
    {
        if (env_ == nullptr) {
            return;
        }
        for (auto& layoutitem : cbLayoutList_) {
            napi_delete_reference(env_, layoutitem);
        }
        for (auto& drawitem : cbDrawList_) {
            napi_delete_reference(env_, drawitem);
        }
        if (thisVarRef_ != nullptr) {
            napi_delete_reference(env_, thisVarRef_);
        }

        auto jsEngine = EngineHelper::GetCurrentEngine();
        if (!jsEngine) {
            LOGE("get jsEngine failed");
            return;
        }
        jsEngine->UnregisterLayoutInspectorCallback(layoutEvent_, componentId_);
        jsEngine->UnregisterDrawInspectorCallback(drawEvent_, componentId_);
    }

    void Initialize(napi_env env, napi_value thisVar);
    void callUserFunction(std::list<napi_ref>& cbList);
    std::list<napi_ref>::iterator FindCbList(napi_value cb, CalloutType calloutType);
    void NapiSerializer(napi_env& env, napi_value& result);
    void AddCallbackToList(
        napi_value cb, std::list<napi_ref>& cbList, CalloutType calloutType, napi_env env, napi_handle_scope scope);
    void DeleteCallbackFromList(
        size_t argc, std::list<napi_ref>& cbList, CalloutType calloutType, napi_value cb, napi_env env);

    RefPtr<InspectorEvent> layoutEvent_;
    RefPtr<InspectorEvent> drawEvent_;
    std::string componentId_;
    std::list<napi_ref> cbLayoutList_;
    std::list<napi_ref> cbDrawList_;
    napi_ref thisVarRef_ = nullptr;

private:
    void FunctionOn(napi_env& env, napi_value result, const char* funName);
    void FunctionOff(napi_env& env, napi_value result, const char* funName);
    napi_env env_ = nullptr;
};
} // namespace OHOS::Ace::Napi
#endif

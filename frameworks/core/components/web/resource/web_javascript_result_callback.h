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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_RESULT_CALLBACK_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_RESULT_CALLBACK_H

#include <string>
#include <vector>

#include "nweb_javascript_result_callback.h"
#include "nweb_value.h"
#include "core/components/web/resource/web_javascript_value.h"
#include "foundation/arkui/ace_engine/frameworks/base/memory/referenced.h"

namespace OHOS::Ace {
using namespace OHOS::NWeb;

class WebDelegate;

class WebJavaScriptResultCallBack : public NWebJavaScriptResultCallBack {
public:
    WebJavaScriptResultCallBack() = delete;
    WebJavaScriptResultCallBack(const WeakPtr<WebDelegate>& delegate) : webDelegate_(delegate) {}

    ~WebJavaScriptResultCallBack() = default;

    std::shared_ptr<NWebValue> GetJavaScriptResult(std::vector<std::shared_ptr<NWebValue>> args,
        const std::string& method, const std::string& object_name, int32_t routing_id, int32_t object_id) override;

    std::shared_ptr<NWebValue> GetJavaScriptResultFlowbuf(std::vector<std::shared_ptr<NWebValue>> args,
        const std::string& method, const std::string& object_name,
        int fd, int32_t routing_id, int32_t object_id) override;

    bool HasJavaScriptObjectMethods(int32_t object_id, const std::string& method_name) override;

    std::shared_ptr<NWebValue> GetJavaScriptObjectMethods(int32_t object_id) override;

    void RemoveJavaScriptObjectHolder(int32_t holder, int32_t object_id) override;

    void RemoveTransientJavaScriptObject() override;

    void GetJavaScriptResultV2(const std::vector<std::shared_ptr<NWebHapValue>>& args, const std::string& method,
        const std::string& objectName, int32_t routingId, int32_t objectId,
        std::shared_ptr<NWebHapValue> result) override;

    void GetJavaScriptResultFlowbufV2(const std::vector<std::shared_ptr<NWebHapValue>>& args, const std::string& method,
        const std::string& objectName, int fd, int32_t routingId, int32_t objectId,
        std::shared_ptr<NWebHapValue> result) override;

    void GetJavaScriptObjectMethodsV2(int32_t objectId, std::shared_ptr<NWebHapValue> result) override;
    
    using JavaScriptCallBackImpl = std::function<std::shared_ptr<WebJSValue>(
        const std::string& objectName,
        const std::string& objectMethod,
        const std::vector<std::shared_ptr<WebJSValue>>& args)>;

    void SetJavaScriptCallBack(const JavaScriptCallBackImpl&& javaScriptCallBackImpl)
    {
        javaScriptCallBackImpl_ = javaScriptCallBackImpl;
    }

private:
    std::shared_ptr<WebJSValue> GetJavaScriptResult(const std::vector<std::shared_ptr<WebJSValue>>& args,
        const std::string& method, const std::string& object_name);

protected:
    JavaScriptCallBackImpl javaScriptCallBackImpl_;

private:
    WeakPtr<WebDelegate> webDelegate_;
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_WEB_RESOURCE_WEB_JAVASCRIPT_RESULT_CALLBACK_H

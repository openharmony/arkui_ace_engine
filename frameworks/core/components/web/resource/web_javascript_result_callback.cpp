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

#include "core/components/web/resource/web_javascript_result_callback.h"

#include "core/components/web/resource/web_javascript_value.h"
#include "base/log/log.h"

namespace OHOS::Ace {
using namespace OHOS::Ace::Framework;
using namespace OHOS::WebView;
std::condition_variable WebJavaScriptResultCallBack::initCv_;

std::vector<std::shared_ptr<WebJSValue>> GetWebJSValue(const std::vector<std::shared_ptr<WebViewValue>>& args)
{
    std::vector<std::shared_ptr<WebJSValue>> webJSValues;
    for (auto value : args) {
        if (value == nullptr) {
            continue;
        }
        WebViewValue::Type type = value->GetType();
        auto webJsValue = std::make_shared<WebJSValue>(WebJSValue::Type::NONE);
        switch (type) {
            case WebViewValue::Type::INTEGER:
                webJsValue->SetType(WebJSValue::Type::INTEGER);
                webJsValue->SetInt(value->GetInt());
                webJSValues.push_back(webJsValue);
                break;
            case WebViewValue::Type::DOUBLE:
                webJsValue->SetType(WebJSValue::Type::DOUBLE);
                webJsValue->SetDouble(value->GetDouble());
                webJSValues.push_back(webJsValue);
                break;
            case WebViewValue::Type::BOOLEAN:
                webJsValue->SetType(WebJSValue::Type::BOOLEAN);
                webJsValue->SetBoolean(value->GetBoolean());
                webJSValues.push_back(webJsValue);
                break;
            case WebViewValue::Type::STRING:
                webJsValue->SetType(WebJSValue::Type::STRING);
                webJsValue->SetString(value->GetString());
                webJSValues.push_back(webJsValue);
                break;
            case WebViewValue::Type::NONE:
                break;
            default:
                LOGI("WebJavaScriptResultCallBack: jsvalue type not support!");
                break;
        }
    }
    return webJSValues;
}

std::shared_ptr<WebViewValue> GetWebViewValue(const std::shared_ptr<WebJSValue>& webJSValue)
{
    std::shared_ptr<WebViewValue> webViewValue = std::make_shared<WebViewValue>(WebViewValue::Type::NONE);
    WebJSValue::Type type = webJSValue->GetType();
    switch (type) {
        case WebJSValue::Type::INTEGER:
            webViewValue->SetType(WebViewValue::Type::INTEGER);
            webViewValue->SetInt(webJSValue->GetInt());
            break;
        case WebJSValue::Type::DOUBLE:
            webViewValue->SetType(WebViewValue::Type::DOUBLE);
            webViewValue->SetDouble(webJSValue->GetDouble());
            break;
        case WebJSValue::Type::BOOLEAN:
            webViewValue->SetType(WebViewValue::Type::BOOLEAN);
            webViewValue->SetBoolean(webJSValue->GetBoolean());
            break;
        case WebJSValue::Type::STRING:
            webViewValue->SetType(WebViewValue::Type::STRING);
            webViewValue->SetString(webJSValue->GetString());
            break;
        case WebJSValue::Type::NONE:
            break;
        default:
            LOGI("WebJavaScriptResultCallBack: jsvalue type not support!");
            break;
    }
    return webViewValue;
}

std::shared_ptr<WebViewValue> WebJavaScriptResultCallBack::GetJavaScriptResult(
    std::vector<std::shared_ptr<WebViewValue>> args, const std::string &method, const std::string &object_name)
{
    LOGI("GetJavaScriptResult");
    std::shared_ptr<WebJSValue> result;
    auto jsArgs = GetWebJSValue(args);

    auto context = context_.Upgrade();
    context->GetTaskExecutor()->PostTask([webJSCallBack = this, object_name, method, jsArgs, &result] {
        if (webJSCallBack->javaScriptCallBackImpl_) {
            result = webJSCallBack->javaScriptCallBackImpl_(object_name, method, jsArgs);
        }
        initCv_.notify_one();
        }, OHOS::Ace::TaskExecutor::TaskType::JS);

    std::unique_lock<std::mutex> lock(initMtx_);
    constexpr int duration = 5; // wait 5 seconds
    if (initCv_.wait_for(lock, std::chrono::seconds(duration)) ==
        std::cv_status::timeout) {
        return std::make_shared<WebViewValue>(WebViewValue::Type::NONE);
    }

    return GetWebViewValue(result);
}
}
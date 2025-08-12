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

#include "core/components/web/resource/web_delegate.h"
#include "core/components/web/resource/web_javascript_result_callback.h"

namespace OHOS::Ace {
using namespace OHOS::Ace::Framework;
using namespace OHOS::NWeb;

std::shared_ptr<WebJSValue> GetWebJSValueHelper(std::shared_ptr<NWebValue> argument)
{
    if (!argument) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetWebJSValueHelper: argument is null");
        return std::make_shared<WebJSValue>();
    }
    switch (argument->GetType()) {
        case NWebValue::Type::INTEGER:
            return std::make_shared<WebJSValue>(argument->GetInt());
        case NWebValue::Type::DOUBLE:
            return std::make_shared<WebJSValue>(argument->GetDouble());
        case NWebValue::Type::BOOLEAN:
            return std::make_shared<WebJSValue>(argument->GetBoolean());
        case NWebValue::Type::STRING:
            return std::make_shared<WebJSValue>(argument->GetString());
        case NWebValue::Type::LIST: {
            size_t length = argument->GetListValueSize();
            std::vector<WebJSValue> vec;
            for (size_t i = 0; i < length; ++i) {
                auto nPtr = std::make_shared<NWebValue>(argument->GetListValue(i));
                vec.push_back(*GetWebJSValueHelper(nPtr));
            }
            return std::make_shared<WebJSValue>(vec);
        }
        case NWebValue::Type::DICTIONARY: {
            std::map<std::string, WebJSValue> map;
            auto dict = argument->GetDictionaryValue();
            for (auto& item : dict) {
                auto nPtr = std::make_shared<NWebValue>(item.second);
                map[item.first] = *GetWebJSValueHelper(nPtr);
            }
            return std::make_shared<WebJSValue>(map);
        }
        case NWebValue::Type::BINARY: {
            auto size = argument->GetBinaryValueSize();
            auto buff = argument->GetBinaryValue();
            return std::make_shared<WebJSValue>(buff, size);
        }
        case NWebValue::Type::NONE:
            return std::make_shared<WebJSValue>();
        default:
            LOGI("GetWebJSValueHelper: jsvalue type not support!");
            break;
    }
    return std::make_shared<WebJSValue>();
}

std::vector<std::shared_ptr<WebJSValue>> GetWebJSValue(const std::vector<std::shared_ptr<NWebValue>>& args)
{
    std::vector<std::shared_ptr<WebJSValue>> webJSValues;
    for (auto value : args) {
        if (value == nullptr) {
            continue;
        }
        webJSValues.push_back(GetWebJSValueHelper(value));
    }
    return webJSValues;
}

bool GetBasicTypeWebViewValue(const std::shared_ptr<WebJSValue>& webJSValue, std::shared_ptr<NWebValue>& webViewValue)
{
    WebJSValue::Type type = webJSValue->GetType();
    switch (type) {
        case WebJSValue::Type::INTEGER:
            webViewValue->SetType(NWebValue::Type::INTEGER);
            webViewValue->SetInt(webJSValue->GetInt());
            break;
        case WebJSValue::Type::DOUBLE:
            webViewValue->SetType(NWebValue::Type::DOUBLE);
            webViewValue->SetDouble(webJSValue->GetDouble());
            break;
        case WebJSValue::Type::BOOLEAN:
            webViewValue->SetType(NWebValue::Type::BOOLEAN);
            webViewValue->SetBoolean(webJSValue->GetBoolean());
            break;
        case WebJSValue::Type::STRING:
            webViewValue->SetType(NWebValue::Type::STRING);
            webViewValue->SetString(webJSValue->GetString());
            break;
        default:
            return false;
    }
    return true;
}

std::shared_ptr<NWebValue> GetWebViewValue(const std::shared_ptr<WebJSValue>& webJSValue)
{
    if (!webJSValue) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetWebViewValue: webJSValue is null");
        return std::make_shared<NWebValue>(NWebValue::Type::NONE);
    }
    std::shared_ptr<NWebValue> webViewValue = std::make_shared<NWebValue>(NWebValue::Type::NONE);
    WebJSValue::Type type = webJSValue->GetType();
    if (GetBasicTypeWebViewValue(webJSValue, webViewValue)) {
        return webViewValue;
    }
    switch (type) {
        case WebJSValue::Type::LIST: {
            size_t length = webJSValue->GetListValueSize();
            std::vector<NWebValue> vec;
            for (size_t i = 0; i < length; ++i) {
                auto nPtr = std::make_shared<WebJSValue>(webJSValue->GetListValue(i));
                vec.push_back(*GetWebViewValue(nPtr));
            }
            return std::make_shared<NWebValue>(vec);
        }
        case WebJSValue::Type::DICTIONARY: {
            std::map<std::string, NWebValue> map;
            auto dict = webJSValue->GetDictionaryValue();
            for (auto& item : dict) {
                auto nPtr = std::make_shared<WebJSValue>(item.second);
                map[item.first] = *GetWebViewValue(nPtr);
            }
            return std::make_shared<NWebValue>(map);
        }
        case WebJSValue::Type::BINARY: {
            auto size = webJSValue->GetBinaryValueSize();
            auto buff = webJSValue->GetBinaryValue();
            return std::make_shared<NWebValue>(buff, size);
        }
        case WebJSValue::Type::NONE:
            break;
        default:
            LOGI("GetWebViewValue: jsvalue type not support!");
            break;
    }
    return webViewValue;
}

std::shared_ptr<WebJSValue> WebJavaScriptResultCallBack::GetJavaScriptResult(
    const std::vector<std::shared_ptr<WebJSValue>>& args, const std::string& method, const std::string& object_name)
{
    auto delegate = webDelegate_.Upgrade();
    if (!delegate) {
        return nullptr;
    }

    ContainerScope scope(delegate->GetInstanceId());
    std::shared_ptr<WebJSValue> result;

    auto task = Container::CurrentTaskExecutor();
    if (task == nullptr) {
        LOGW("can't get task executor");
        return nullptr;
    }

    task->PostSyncTask(
        [webJSCallBack = this, object_name, method, args, &result] {
            if (webJSCallBack->javaScriptCallBackImpl_) {
                result = webJSCallBack->javaScriptCallBackImpl_(object_name, method, args);
            }
        },
        OHOS::Ace::TaskExecutor::TaskType::JS, "ArkUIWebGetJavaScriptResult");

    return result;
}

std::shared_ptr<NWebValue> WebJavaScriptResultCallBack::GetJavaScriptResult(
    std::vector<std::shared_ptr<NWebValue>> args, const std::string& method, const std::string& object_name,
    int32_t routing_id, int32_t object_id)
{
    // webcontroller not support object, so the object_id and routing_id param is
    // not used
    (void)object_id;
    (void)routing_id;

    std::shared_ptr<WebJSValue> result = GetJavaScriptResult(GetWebJSValue(args), method, object_name);
    return GetWebViewValue(result);
}

std::shared_ptr<NWebValue> WebJavaScriptResultCallBack::GetJavaScriptResultFlowbuf(
    std::vector<std::shared_ptr<NWebValue>> args, const std::string& method, const std::string& object_name,
    int fd, int32_t routing_id, int32_t object_id)
{
    // webcontroller not support object
    // not supported
    (void)object_id;
    (void)routing_id;
    LOGE("Flowbuf is not supported on the decrepted Webcontroller, use Webviewcontroller instead.");
    return std::make_shared<NWebValue>(NWebValue::Type::NONE);
}

bool WebJavaScriptResultCallBack::HasJavaScriptObjectMethods(int32_t object_id, const std::string& method_name)
{
    (void)object_id;
    (void)method_name;
    // webcontroller not support object, so nothing to do
    return false;
}

std::shared_ptr<NWebValue> WebJavaScriptResultCallBack::GetJavaScriptObjectMethods(int32_t object_id)
{
    (void)object_id;
    // webcontroller not support object, so nothing to do
    return std::make_shared<NWebValue>();
}

void WebJavaScriptResultCallBack::RemoveJavaScriptObjectHolder(int32_t holder, int32_t object_id)
{
    (void)holder;
    (void)object_id;
    // webcontroller not support object, so nothing to do
}

void WebJavaScriptResultCallBack::RemoveTransientJavaScriptObject()
{
    // webcontroller not support object, so nothing to do
}

std::shared_ptr<WebJSValue> GetWebJSValueHelperV2(std::shared_ptr<NWebHapValue> argument)
{
    if (!argument) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetWebJSValueHelper: argument is null");
        return std::make_shared<WebJSValue>();
    }

    switch (argument->GetType()) {
        case NWebHapValue::Type::INTEGER:
            return std::make_shared<WebJSValue>(argument->GetInt());
        case NWebHapValue::Type::BOOLEAN:
            return std::make_shared<WebJSValue>(argument->GetBool());
        case NWebHapValue::Type::DOUBLE:
            return std::make_shared<WebJSValue>(argument->GetDouble());
        case NWebHapValue::Type::STRING:
            return std::make_shared<WebJSValue>(argument->GetString());
        case NWebHapValue::Type::BINARY: {
            int length = 0;
            auto buff = argument->GetBinary(length);
            return std::make_shared<WebJSValue>(buff, length);
        }
        case NWebHapValue::Type::LIST: {
            std::vector<WebJSValue> vec;
            auto list = argument->GetListValue();
            for (auto& item : list) {
                vec.push_back(*GetWebJSValueHelperV2(item));
            }
            return std::make_shared<WebJSValue>(vec);
        }
        case NWebHapValue::Type::DICTIONARY: {
            std::map<std::string, WebJSValue> map;
            auto dict = argument->GetDictValue();
            for (auto& item : dict) {
                map[item.first] = *GetWebJSValueHelperV2(item.second);
            }
            return std::make_shared<WebJSValue>(map);
        }
        case NWebHapValue::Type::NONE:
            return std::make_shared<WebJSValue>();
        default:
            LOGI("GetWebJSValueHelper: jsvalue type not support!");
            break;
    }
    return std::make_shared<WebJSValue>();
}

std::vector<std::shared_ptr<WebJSValue>> GetWebJSValueV2(const std::vector<std::shared_ptr<NWebHapValue>>& args)
{
    std::vector<std::shared_ptr<WebJSValue>> webJSValues;
    for (auto value : args) {
        if (value == nullptr) {
            continue;
        }
        webJSValues.push_back(GetWebJSValueHelperV2(value));
    }
    return webJSValues;
}

bool GetBasicTypeWebViewValueV2(
    const std::shared_ptr<WebJSValue>& webJSValue, std::shared_ptr<NWebHapValue>& webHapValue)
{
    WebJSValue::Type type = webJSValue->GetType();
    switch (type) {
        case WebJSValue::Type::NONE:
            webHapValue->SetType(NWebHapValue::Type::NONE);
            break;
        case WebJSValue::Type::INTEGER:
            webHapValue->SetType(NWebHapValue::Type::INTEGER);
            webHapValue->SetInt(webJSValue->GetInt());
            break;
        case WebJSValue::Type::DOUBLE:
            webHapValue->SetType(NWebHapValue::Type::DOUBLE);
            webHapValue->SetDouble(webJSValue->GetDouble());
            break;
        case WebJSValue::Type::BOOLEAN:
            webHapValue->SetType(NWebHapValue::Type::BOOLEAN);
            webHapValue->SetBool(webJSValue->GetBoolean());
            break;
        case WebJSValue::Type::STRING:
            webHapValue->SetType(NWebHapValue::Type::STRING);
            webHapValue->SetString(webJSValue->GetString());
            break;
        case WebJSValue::Type::BINARY:
            webHapValue->SetType(NWebHapValue::Type::BINARY);
            webHapValue->SetBinary(webJSValue->GetBinaryValueSize(), webJSValue->GetBinaryValue());
            break;
        default:
            return false;
    }
    return true;
}

void GetWebViewValueV2(const std::shared_ptr<WebJSValue>& webJSValue, std::shared_ptr<NWebHapValue> webHapValue)
{
    if (!webJSValue) {
        TAG_LOGE(AceLogTag::ACE_WEB, "GetWebViewValue: webJSValue is null");
        return;
    }

    if (!webHapValue) {
        return;
    }

    if (GetBasicTypeWebViewValueV2(webJSValue, webHapValue)) {
        return;
    }

    WebJSValue::Type type = webJSValue->GetType();
    switch (type) {
        case WebJSValue::Type::LIST: {
            webHapValue->SetType(NWebHapValue::Type::LIST);
            size_t length = webJSValue->GetListValueSize();
            for (size_t i = 0; i < length; ++i) {
                GetWebViewValueV2(
                    std::make_shared<WebJSValue>(webJSValue->GetListValue(i)), webHapValue->NewChildValue());
                webHapValue->SaveListChildValue();
            }
            return;
        }
        case WebJSValue::Type::DICTIONARY: {
            webHapValue->SetType(NWebHapValue::Type::DICTIONARY);
            auto dict = webJSValue->GetDictionaryValue();
            for (auto& item : dict) {
                GetWebViewValueV2(std::make_shared<WebJSValue>(item.second), webHapValue->NewChildValue());
                webHapValue->SaveDictChildValue(item.first);
            }
            return;
        }
        default:
            LOGI("GetWebViewValue: jsvalue type not support!");
            break;
    }
}

void WebJavaScriptResultCallBack::GetJavaScriptResultV2(const std::vector<std::shared_ptr<NWebHapValue>>& args,
    const std::string& method, const std::string& objectName, int32_t routingId, int32_t objectId,
    std::shared_ptr<NWebHapValue> result)
{
    // webcontroller not support object, so the object_id and routing_id param is
    // not used
    (void)objectId;
    (void)routingId;

    GetWebViewValueV2(GetJavaScriptResult(GetWebJSValueV2(args), method, objectName), result);
}

void WebJavaScriptResultCallBack::GetJavaScriptResultFlowbufV2(const std::vector<std::shared_ptr<NWebHapValue>>& args,
    const std::string& method, const std::string& objectName, int fd, int32_t routingId, int32_t objectId,
    std::shared_ptr<NWebHapValue> result)
{
    (void)fd;
    (void)args;
    (void)method;
    (void)result;
    (void)objectId;
    (void)routingId;
    (void)objectName;
    // webcontroller not support object, so nothing to do
}

void WebJavaScriptResultCallBack::GetJavaScriptObjectMethodsV2(int32_t objectId, std::shared_ptr<NWebHapValue> result)
{
    (void)result;
    (void)objectId;
    // webcontroller not support object, so nothing to do
}

} // namespace OHOS::Ace

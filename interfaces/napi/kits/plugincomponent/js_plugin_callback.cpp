/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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
#include "js_plugin_callback.h"


#include "js_plugin_callback_mgr.h"
#include "js_plugin_util.h"
#include "js_plugin_want.h"

#include "core/common/ace_engine.h"
#include "core/components/plugin/plugin_component_manager.h"

namespace OHOS::Ace::Napi {
std::atomic_size_t JSPluginCallback::uuid_ = 0;
constexpr int ACE_ARGS_TWO = 2;
constexpr int ACE_ARGS_THREE = 3;
constexpr int ACE_ARGS_FOUR = 4;
constexpr int ACE_PARAM0 = 0;
constexpr int ACE_PARAM1 = 1;
constexpr int ACE_PARAM2 = 2;
constexpr int ACE_PARAM3 = 3;

bool AceJSPluginRequestParam::operator==(const AceJSPluginRequestParam& param) const
{
    AppExecFwk::ElementName leftElement = want_.GetElement();
    AppExecFwk::ElementName rightElement = param.want_.GetElement();
    if (leftElement == rightElement) {
        if (name_ == param.name_ && data_ == param.data_ && jsonPath_ == param.jsonPath_) {
            return true;
        }
    }
    return false;
}

bool AceJSPluginRequestParam::operator!=(const AceJSPluginRequestParam& param) const
{
    return !operator==(param);
}

JSPluginCallback::JSPluginCallback(
    CallBackType eventType, ACECallbackInfo& cbInfo, ACEAsyncJSCallbackInfo* jsCallbackInfo)
    : eventType_(eventType), asyncJSCallbackInfo_(jsCallbackInfo)
{
    uuid_++;
    cbInfo_.env = cbInfo.env;
    cbInfo_.callback = cbInfo.callback;
    cbInfo_.containerId = cbInfo.containerId;
}

JSPluginCallback::~JSPluginCallback()
{
    if (uuid_ > 0) {
        uuid_--;
    }
    DestroyAllResource();
}

void JSPluginCallback::DestroyAllResource(void)
{
    if (cbInfo_.env != nullptr && cbInfo_.callback != nullptr) {
        napi_delete_reference(cbInfo_.env, cbInfo_.callback);
    }
    cbInfo_.env = nullptr;
    cbInfo_.callback = nullptr;
    cbInfo_.containerId = -1;
    asyncJSCallbackInfo_ = nullptr;
}

void JSPluginCallback::SetWant(const AAFwk::Want& want)
{
    want_ = want;
}

AAFwk::Want& JSPluginCallback::GetWant()
{
    return want_;
}

void JSPluginCallback::SetRequestParam(const std::shared_ptr<AceJSPluginRequestParam>& param)
{
    requestParam_ = param;
}

size_t JSPluginCallback::GetID(void)
{
    return uuid_;
}

int32_t JSPluginCallback::GetContainerId()
{
    return cbInfo_.containerId;
}

void JSPluginCallback::SendRequestEventResult(napi_value jsObject)
{
    napi_value jsTemplate = AceGetPropertyValueByPropertyName(cbInfo_.env, jsObject, "template", napi_string);
    napi_value jsData = AceGetPropertyValueByPropertyName(cbInfo_.env, jsObject, "data", napi_object);
    napi_value jsExtraData = AceGetPropertyValueByPropertyName(cbInfo_.env, jsObject, "extraData", napi_object);

    struct MyData {
        AAFwk::Want want;
        std::string strTemplate;
        std::string strDate;
        std::string strExtraData;
    };

    std::shared_ptr<MyData> data = std::make_shared<MyData>();
    data->want = want_;

    if (jsTemplate != nullptr) {
        data->strTemplate = AceUnwrapStringFromJS(cbInfo_.env, jsTemplate);
    }

    if (jsData != nullptr) {
        AceKVObjectToString(cbInfo_.env, jsData, data->strDate);
    }

    if (jsExtraData != nullptr) {
        AceKVObjectToString(cbInfo_.env, jsExtraData, data->strExtraData);
    }

    auto container = AceEngine::Get().GetContainer(cbInfo_.containerId);
    if (!container) {
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }
    taskExecutor->PostTask(
        [data]() {
            PluginComponentManager::GetInstance()->ReturnRequest(
                data->want, data->strTemplate, data->strDate, data->strExtraData);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIPluginReturnRequest");
}

napi_value JSPluginCallback::MakeCallbackParamForRequest(
    const PluginComponentTemplate& pluginTemplate, const std::string& data, const std::string& extraData)
{
    napi_value jsObject = AceCreateJSObject(cbInfo_.env);
    if (jsObject == nullptr) {
        return nullptr;
    }

    std::string dataTmp("{}");
    std::string extraDataTmp("{}");
    if (!data.empty()) {
        dataTmp = data;
    }
    if (!extraData.empty()) {
        extraDataTmp = extraData;
    }

    napi_value jsPluginTemplate = MakePluginTemplateObject(pluginTemplate);
    napi_value jsData = AceStringToKVObject(cbInfo_.env, dataTmp);
    napi_value jsExtraData = AceStringToKVObject(cbInfo_.env, extraDataTmp);

    if (jsData != nullptr) {
        AceSetPropertyValueByPropertyName(cbInfo_.env, jsObject, "componentTemplate", jsPluginTemplate);
    }
    if (jsData != nullptr) {
        AceSetPropertyValueByPropertyName(cbInfo_.env, jsObject, "data", jsData);
    }
    if (jsExtraData != nullptr) {
        AceSetPropertyValueByPropertyName(cbInfo_.env, jsObject, "extraData", jsExtraData);
    }
    return jsObject;
}

napi_value JSPluginCallback::MakePluginTemplateObject(const PluginComponentTemplate& pluginTemplate)
{
    napi_value jsPluginTemplate = AceCreateJSObject(cbInfo_.env);
    if (jsPluginTemplate != nullptr) {
        napi_value jsSource = AceWrapStringToJS(cbInfo_.env, pluginTemplate.GetSource());
        napi_value jsAbility = AceWrapStringToJS(cbInfo_.env, pluginTemplate.GetAbility());

        AceSetPropertyValueByPropertyName(cbInfo_.env, jsPluginTemplate, "source", jsSource);
        AceSetPropertyValueByPropertyName(cbInfo_.env, jsPluginTemplate, "ability", jsAbility);
    }
    return jsPluginTemplate;
}

void JSPluginCallback::OnPushEventInner(const OnPluginUvWorkData* workData)
{
    napi_value jsCallback = nullptr;
    napi_value undefined = nullptr;
    napi_value jsResult = nullptr;
    napi_value callbackParam[ACE_ARGS_FOUR] = { nullptr };
    napi_handle_scope scope = nullptr;
    std::string dataTmp("{}");
    std::string extraDataTmp("{}");
    if (!workData->data.empty()) {
        dataTmp = workData->data;
    }
    if (!workData->extraData.empty()) {
        extraDataTmp = workData->extraData;
    }

    napi_open_handle_scope(cbInfo_.env, &scope);
    if (scope == nullptr) {
        napi_close_handle_scope(cbInfo_.env, scope);
        return;
    }

    PluginComponentTemplate componentTemplate;
    componentTemplate.SetSource(workData->sourceName);
    componentTemplate.SetAbility(workData->abilityName);

    callbackParam[ACE_PARAM0] = AceWrapWant(cbInfo_.env, workData->want);
    callbackParam[ACE_PARAM1] = MakePluginTemplateObject(componentTemplate);
    callbackParam[ACE_PARAM2] = AceStringToKVObject(cbInfo_.env, dataTmp);
    callbackParam[ACE_PARAM3] = AceStringToKVObject(cbInfo_.env, extraDataTmp);

    napi_get_undefined(cbInfo_.env, &undefined);
    napi_get_reference_value(cbInfo_.env, cbInfo_.callback, &jsCallback);
    napi_call_function(cbInfo_.env, undefined, jsCallback, ACE_ARGS_FOUR, callbackParam, &jsResult);
    napi_close_handle_scope(cbInfo_.env, scope);
}

void JSPluginCallback::OnPushEvent(const AAFwk::Want& want, const PluginComponentTemplate& pluginTemplate,
    const std::string& data, const std::string& extraData)
{
    if (cbInfo_.env == nullptr || cbInfo_.callback == nullptr) {
        return;
    }

    auto container = AceEngine::Get().GetContainer(cbInfo_.containerId);
    if (!container) {
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }
    std::weak_ptr<PluginComponentCallBack> weak = weak_from_this();
    taskExecutor->PostTask(
        [weak, want, sourceName = pluginTemplate.GetSource(), abilityName = pluginTemplate.GetAbility(), data,
            extraData]() {
            OnPluginUvWorkData uvWorkData;
            uvWorkData.want = want;
            uvWorkData.sourceName = sourceName;
            uvWorkData.abilityName = abilityName;
            uvWorkData.data = data;
            uvWorkData.extraData = extraData;
            auto callBack = weak.lock();
            if (callBack) {
                auto jsCallback = std::static_pointer_cast<JSPluginCallback>(callBack);
                jsCallback->OnPushEventInner(&uvWorkData);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIPluginPushEventInner");
}

void JSPluginCallback::OnRequestEventInner(const OnPluginUvWorkData* workData)
{
    napi_value jsCallback = nullptr;
    napi_value undefined = nullptr;
    napi_value jsResult = nullptr;
    napi_handle_scope scope = nullptr;
    std::string dataTmp("{}");
    if (!workData->data.empty()) {
        dataTmp = workData->data;
    }

    napi_open_handle_scope(cbInfo_.env, &scope);
    if (scope == nullptr) {
        napi_close_handle_scope(cbInfo_.env, scope);
        return;
    }
    napi_value callbackParam[ACE_ARGS_THREE] = { nullptr };
    callbackParam[ACE_PARAM0] = AceWrapWant(cbInfo_.env, workData->want);
    callbackParam[ACE_PARAM1] = AceWrapStringToJS(cbInfo_.env, workData->name);
    callbackParam[ACE_PARAM2] = AceStringToKVObject(cbInfo_.env, dataTmp);

    napi_get_undefined(cbInfo_.env, &undefined);
    napi_get_reference_value(cbInfo_.env, cbInfo_.callback, &jsCallback);
    napi_call_function(cbInfo_.env, undefined, jsCallback, ACE_ARGS_THREE, callbackParam, &jsResult);

    if (AceIsTypeForNapiValue(cbInfo_.env, jsResult, napi_object)) {
        SendRequestEventResult(jsResult);
    }
    napi_close_handle_scope(cbInfo_.env, scope);
}

void JSPluginCallback::OnRequestEvent(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    if (cbInfo_.env == nullptr || cbInfo_.callback == nullptr) {
        return;
    }

    auto container = AceEngine::Get().GetContainer(cbInfo_.containerId);
    if (!container) {
        return;
    }

    auto taskExecutor = container->GetTaskExecutor();
    if (!taskExecutor) {
        return;
    }

    std::weak_ptr<PluginComponentCallBack> weak = weak_from_this();
    taskExecutor->PostTask(
        [weak, want, name, data]() {
            auto callBack = weak.lock();
            if (callBack) {
                OnPluginUvWorkData uvWorkData;
                uvWorkData.that = callBack.get();
                uvWorkData.want = want;
                uvWorkData.data = data;
                uvWorkData.name = name;

                auto jsCallback = std::static_pointer_cast<JSPluginCallback>(callBack);
                jsCallback->OnRequestEventInner(&uvWorkData);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIPluginRequestEventInner");
}

void JSPluginCallback::OnRequestCallBackInner(const OnPluginUvWorkData* workData)
{
    napi_value jsCallback = nullptr;
    napi_value undefined = nullptr;
    napi_value jsResult = nullptr;
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(cbInfo_.env, &scope);
    if (scope == nullptr) {
        napi_close_handle_scope(cbInfo_.env, scope);
        return;
    }
    PluginComponentTemplate componentTemplate;
    componentTemplate.SetSource(workData->sourceName);
    componentTemplate.SetAbility(workData->abilityName);

    if (cbInfo_.callback != nullptr) {
        napi_value callbackParam[ACE_ARGS_TWO] = { nullptr };
        callbackParam[ACE_PARAM0] = AceGetCallbackErrorValue(cbInfo_.env, 0);
        callbackParam[ACE_PARAM1] = MakeCallbackParamForRequest(componentTemplate, workData->data, workData->extraData);
        napi_get_undefined(cbInfo_.env, &undefined);
        napi_get_reference_value(cbInfo_.env, cbInfo_.callback, &jsCallback);
        napi_call_function(cbInfo_.env, undefined, jsCallback, ACE_ARGS_TWO, callbackParam, &jsResult);
    }
    napi_close_handle_scope(cbInfo_.env, scope);
}

void JSPluginCallback::OnRequestCallBack(
    const PluginComponentTemplate& pluginTemplate, const std::string& data, const std::string& extraData)
{
    JSPluginCallbackMgr::Instance().UnRegisterEvent(GetID());
    if (cbInfo_.env == nullptr) {
        return;
    }

    if (cbInfo_.callback != nullptr) {
        uvWorkData_.that = (void*)this;
        uvWorkData_.sourceName = pluginTemplate.GetSource();
        uvWorkData_.abilityName = pluginTemplate.GetAbility();
        uvWorkData_.data = data;
        uvWorkData_.extraData = extraData;

        if (getpid() != gettid()) {
            struct ResultData {
                JSPluginCallback* context = nullptr;
                std::mutex mtx;
                bool ready = false;
                std::condition_variable cv;
            };

            std::shared_ptr<ResultData> resultData = std::make_shared<ResultData>();
            resultData->context = this;

            auto container = AceEngine::Get().GetContainer(cbInfo_.containerId);
            if (!container) {
                return;
            }

            auto taskExecutor = container->GetTaskExecutor();
            if (!taskExecutor) {
                return;
            }
            taskExecutor->PostTask(
                [resultData]() {
                    resultData->context->OnRequestCallBackInner(&resultData->context->uvWorkData_);

                    {
                        std::unique_lock<std::mutex> lock(resultData->mtx);
                        resultData->ready = true;
                        resultData->cv.notify_all();
                    }
                },
                TaskExecutor::TaskType::JS, "ArkUIPluginRequestCallbackInner");

            {
                std::unique_lock<std::mutex> lock(resultData->mtx);
                if (!resultData->ready) {
                    resultData->cv.wait(lock, [&] { return resultData->ready; });
                }
            }
        } else {
            OnRequestCallBackInner(&uvWorkData_);
        }
    } else {
        if (asyncJSCallbackInfo_) {
            asyncJSCallbackInfo_->requestCallbackData.sourceName = pluginTemplate.GetSource();
            asyncJSCallbackInfo_->requestCallbackData.abilityName = pluginTemplate.GetAbility();
            asyncJSCallbackInfo_->requestCallbackData.data = data;
            asyncJSCallbackInfo_->requestCallbackData.extraData = extraData;
            asyncJSCallbackInfo_->onRequestCallbackOK = true;
        }
    }
}

bool JSPluginCallback::OnEventStrictEquals(CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo)
{
    if (eventType != eventType_) {
        return false;
    }
    AppExecFwk::ElementName leftElement = want.GetElement();
    AppExecFwk::ElementName rightElement = want_.GetElement();
    if (leftElement == rightElement) {
        return AceIsSameFuncFromJS(cbInfo, cbInfo_);
    } else {
        return false;
    }
}

bool JSPluginCallback::RequestStrictEquals(CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo,
    const std::shared_ptr<AceJSPluginRequestParam>& param)
{
    if (eventType != eventType_) {
        return false;
    }
    AppExecFwk::ElementName leftElement = want.GetElement();
    AppExecFwk::ElementName rightElement = want_.GetElement();
    if (!(leftElement == rightElement)) {
        return false;
    }
    if (param == nullptr || requestParam_ == nullptr) {
        return false;
    }
    if (*param != *requestParam_) {
        return false;
    }
    return AceIsSameFuncFromJS(cbInfo, cbInfo_);
}
} // namespace OHOS::Ace::Napi

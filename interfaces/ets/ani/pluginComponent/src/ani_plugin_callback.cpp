/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include <sstream>
#include "ani.h"
#include "ani_common_want.h"
#include "ani_plugin_callback.h"
#include "ani_plugin_callback_mgr.h"
#include "ani_plugin_component_data.h"
#include "ani_plugin_component_util.h"
#include "core/common/ace_engine.h"
#include "core/components/plugin/plugin_component_manager.h"

namespace OHOS::Ace::Ani {
    std::atomic_size_t ANIPluginCallback::uuid_ = 0;
    constexpr char PLUGINCOMPONENT_TEMPLATE_CLASSNAME[] = "L@ohos/pluginComponent/PluginComponentTemplateImpl;";
    
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

ANIPluginCallback::ANIPluginCallback(
    CallBackType eventType, ACECallbackInfo& cbInfo, ACEAsyncJSCallbackInfo* jsCallbackInfo)
    : eventType_(eventType), asyncJSCallbackInfo_(jsCallbackInfo)
{
    uuid_++;
    cbInfo_.env = cbInfo.env;
    cbInfo_.callback = cbInfo.callback;
    cbInfo_.containerId = cbInfo.containerId;
}

ANIPluginCallback::~ANIPluginCallback()
{
    if (uuid_ > 0) {
        uuid_--;
    }
    DestroyAllResource();
}

void ANIPluginCallback::DestroyAllResource(void)
{
    if (cbInfo_.env != nullptr && cbInfo_.callback != nullptr) {
        cbInfo_.env->GlobalReference_Delete(cbInfo_.callback);
    }
    cbInfo_.env = nullptr;
    cbInfo_.callback = nullptr;
    cbInfo_.containerId = -1;
    asyncJSCallbackInfo_ = nullptr;
}

void ANIPluginCallback::SetWant(const AAFwk::Want& want)
{
    want_ = want;
}

AAFwk::Want& ANIPluginCallback::GetWant()
{
    return want_;
}

void ANIPluginCallback::SetRequestParam(const std::shared_ptr<AceJSPluginRequestParam>& param)
{
    requestParam_ = param;
}

size_t ANIPluginCallback::GetID(void)
{
    return uuid_;
}

bool ANIPluginCallback::RequestStrictEquals(CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo,
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
    return AceIsSameFuncFromANI(cbInfo, cbInfo_);
}

int32_t ANIPluginCallback::GetContainerId()
{
    return cbInfo_.containerId;
}

bool ANIPluginCallback::OnEventStrictEquals(CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo)
{
    if (eventType != eventType_) {
        return false;
    }
    AppExecFwk::ElementName leftElement = want.GetElement();
    AppExecFwk::ElementName rightElement = want_.GetElement();
    if (leftElement == rightElement) {
        return AceIsSameFuncFromANI(cbInfo, cbInfo_);
    } else {
        return false;
    }
}

void ANIPluginCallback::OnPushEventInner(const OnPluginUvWorkData* workData)
{
    LOGI("plugin-ani OnPushEventInner start");
    PluginComponentTemplate componentTemplate;
    componentTemplate.SetSource(workData->sourceName);
    componentTemplate.SetAbility(workData->abilityName);
    std::vector<ani_ref> vec;
    auto wantObj = OHOS::AppExecFwk::WrapWant(cbInfo_.env, workData->want);
    vec.push_back(wantObj);
    auto param = MakeCallbackParamForRequestOrPush(componentTemplate, workData->data, workData->extraData);
    vec.push_back(param.pluginTemplateObj);
    vec.push_back(param.aniData);
    vec.push_back(param.aniExtraData);
    ani_ref fnReturnVal;
    auto status = cbInfo_.env->FunctionalObject_Call(reinterpret_cast<ani_fn_object>(cbInfo_.callback),
        vec.size(), vec.data(), &fnReturnVal);
    LOGI("plugin-ani OnPushEventInner end status %{public}d", status);
}

void ANIPluginCallback::OnPushEvent(const AAFwk::Want& want, const PluginComponentTemplate& pluginTemplate,
    const std::string& data, const std::string& extraData)
{
    LOGI("plugin-ani OnPushEvent start");
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
                auto jsCallback = std::static_pointer_cast<ANIPluginCallback>(callBack);
                jsCallback->OnPushEventInner(&uvWorkData);
            }
        },
        TaskExecutor::TaskType::UI, "ArkUIPluginPushEventInner");
}

void ANIPluginCallback::SendRequestEventResult(ani_object aniRef)
{
    if (aniRef == nullptr) {
        LOGE("plugin-ani result of request event is null");
        return;
    }
    struct RequestEventResult {
        AAFwk::Want want;
        std::string strTemplate;
        std::string strData;
        std::string strExtraData;
    };

    std::shared_ptr<RequestEventResult> data = std::make_shared<RequestEventResult>();
    data->want = want_;
    GetAniStringPropertyByName(cbInfo_.env, aniRef, "template", data->strTemplate);
    GetAniKVObjectPropertyByName(cbInfo_.env, aniRef, "data", data->strData);
    GetAniKVObjectPropertyByName(cbInfo_.env, aniRef, "extraData", data->strExtraData);
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
                data->want, data->strTemplate, data->strData, data->strExtraData);
        },
        TaskExecutor::TaskType::BACKGROUND, "ArkUIPluginReturnRequest");
}

void ANIPluginCallback::OnRequestEventInner(const OnPluginUvWorkData* workData)
{
    LOGI("plugin-ani OnRequestEventInner start");
    std::vector<ani_ref> vec;
    auto wantObj = OHOS::AppExecFwk::WrapWant(cbInfo_.env, workData->want);
    vec.push_back(wantObj);
    auto nameAni = AceWrapStringToAni(cbInfo_.env, workData->name);
    vec.push_back(nameAni);
    ani_ref aniData = AceWrapStringToObject(cbInfo_.env, workData->data);
    vec.push_back(aniData);
    ani_ref fnReturnVal;
    cbInfo_.env->FunctionalObject_Call(reinterpret_cast<ani_fn_object>(cbInfo_.callback), vec.size(), vec.data(),
        &fnReturnVal);
    ani_boolean isUndefined = true;
    if (ANI_OK != cbInfo_.env->Reference_IsUndefined(fnReturnVal, &isUndefined) || isUndefined) {
        LOGE("plugin-ani result of request event is null");
        return;
    }
    SendRequestEventResult(reinterpret_cast<ani_object>(fnReturnVal));
}

void ANIPluginCallback::OnRequestEvent(const AAFwk::Want& want, const std::string& name, const std::string& data)
{
    LOGI("plugin-ani OnRequestEvent start");
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
                uvWorkData.want = want;
                uvWorkData.data = data;
                uvWorkData.name = name;
                auto jsCallback = std::static_pointer_cast<ANIPluginCallback>(callBack);
                jsCallback->OnRequestEventInner(&uvWorkData);
            }
        },
        TaskExecutor::TaskType::JS, "ArkUIPluginRequestEventInner");
}

ani_ref ANIPluginCallback::MakePluginTemplateObject(const PluginComponentTemplate& pluginTemplate)
{
    ani_class pluginTemplateCls;
    cbInfo_.env->FindClass(PLUGINCOMPONENT_TEMPLATE_CLASSNAME, &pluginTemplateCls);
    ani_method PTOCtor;
    cbInfo_.env->Class_FindMethod(pluginTemplateCls, "<ctor>", ":V", &PTOCtor);
    ani_object PTOObj;
    cbInfo_.env->Object_New(pluginTemplateCls, PTOCtor, &PTOObj);
    cbInfo_.env->Object_SetPropertyByName_Ref(PTOObj, "source", AceWrapStringToAni(cbInfo_.env,
        pluginTemplate.GetSource()));
    cbInfo_.env->Object_SetPropertyByName_Ref(PTOObj, "ability", AceWrapStringToAni(cbInfo_.env,
        pluginTemplate.GetAbility()));
    return PTOObj;
}

CallbackParamForRequest ANIPluginCallback::MakeCallbackParamForRequestOrPush(
    const PluginComponentTemplate& pluginTemplate, const std::string& data, const std::string& extraData)
{
    ani_ref pluginTemplateObj = MakePluginTemplateObject(pluginTemplate);
    ani_ref aniData = AceWrapStringToObject(cbInfo_.env, data);
    ani_ref aniExtraData = AceWrapStringToObject(cbInfo_.env, extraData);
    CallbackParamForRequest param {
        .pluginTemplateObj = pluginTemplateObj,
        .aniData = aniData,
        .aniExtraData = aniExtraData
    };
    return param;
}

void ANIPluginCallback::OnRequestCallBackInner(const OnPluginUvWorkData* workData)
{
    PluginComponentTemplate componentTemplate;
    componentTemplate.SetSource(workData->sourceName);
    componentTemplate.SetAbility(workData->abilityName);
    std::vector<ani_ref> vec;
    ani_ref fnReturnVal;
    auto param = CreateInt(cbInfo_.env, ani_int(0));
    vec.push_back(param);
    auto paramForRequest = MakeCallbackParamForRequestOrPush(componentTemplate, workData->data, workData->extraData);
    vec.push_back(paramForRequest.pluginTemplateObj);
    vec.push_back(paramForRequest.aniData);
    vec.push_back(paramForRequest.aniExtraData);
    auto fnObj = reinterpret_cast<ani_fn_object>(cbInfo_.callback);
    if (fnObj == nullptr) {
        LOGI("plugin-ani OnRequestCallBackInner fnObj is null");
        return;
    }
    auto status = cbInfo_.env->FunctionalObject_Call(fnObj, vec.size(), vec.data(), &fnReturnVal);
    LOGI("plugin-ani OnRequestCallBackInner execute status %{public}d", status);
    cbInfo_.env->GlobalReference_Delete(cbInfo_.callback);
}

void ANIPluginCallback::OnRequestCallBack(
    const PluginComponentTemplate& pluginTemplate, const std::string& data, const std::string& extraData)
{
    ANIPluginCallbackMgr::Instance().UnRegisterEvent(GetID());
    if (cbInfo_.env == nullptr) {
        return;
    }
    uvWorkData_.sourceName = pluginTemplate.GetSource();
    uvWorkData_.abilityName = pluginTemplate.GetAbility();
    uvWorkData_.data = data;
    uvWorkData_.extraData = extraData;

    if (getpid() != gettid()) {
        struct ResultData {
            ANIPluginCallback* context = nullptr;
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
}
} // namespace OHOS::Ace::Ani
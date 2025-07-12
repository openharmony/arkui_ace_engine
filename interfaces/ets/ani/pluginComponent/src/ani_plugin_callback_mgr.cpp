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
#include "ani_plugin_callback_mgr.h"
#include "core/components/plugin/plugin_component_manager.h"
 
namespace OHOS::Ace::Ani {
ANIPluginCallbackMgr::ANIPluginCallbackMgr() {}

ANIPluginCallbackMgr::~ANIPluginCallbackMgr()
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto iter = eventList_.begin(); iter != eventList_.end(); iter++) {
        if (iter->second != nullptr) {
            PluginComponentManager::GetInstance()->UnregisterCallBack(iter->second->GetWant());
        }
    }
    eventList_.clear();
    asyncJSCallbackInfo_ = nullptr;
}

ANIPluginCallbackMgr& ANIPluginCallbackMgr::Instance(void)
{
    static ANIPluginCallbackMgr gANIPluginCallbackMgr;
    return gANIPluginCallbackMgr;
}

bool ANIPluginCallbackMgr::RegisterOnEvent(
    ani_env* env, CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo)
{
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto iter = eventList_.begin(); iter != eventList_.end(); iter++) {
        if (iter->second->OnEventStrictEquals(eventType, want, cbInfo)) {
            return false;
        }
    }

    std::shared_ptr<PluginComponentCallBack> pPluginComponentCallback =
        std::make_shared<ANIPluginCallback>(eventType, cbInfo, asyncJSCallbackInfo_);
    std::shared_ptr<ANIPluginCallback> jsPluginCallback =
        std::static_pointer_cast<ANIPluginCallback>(pPluginComponentCallback);
    jsPluginCallback->SetWant(want);
    eventList_.insert(std::make_pair(jsPluginCallback->GetID(), jsPluginCallback));
    PluginComponentManager::GetInstance()->RegisterCallBack(want, pPluginComponentCallback, eventType);
    LOGI("plugin-ani %{public}s register %{public}d event finish", want.GetBundle().c_str(), eventType);
    return true;
}

bool ANIPluginCallbackMgr::RegisterRequestEvent(ani_env* env, const AAFwk::Want& want, ACECallbackInfo& cbInfo,
    const std::shared_ptr<AceJSPluginRequestParam>& param)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (param == nullptr) {
        return false;
    }
    for (auto iter = eventList_.begin(); iter != eventList_.end(); iter++) {
        if (iter->second->RequestStrictEquals(CallBackType::RequestCallBack, want, cbInfo, param)) {
            return false;
        }
    }

    std::shared_ptr<ANIPluginCallback> pPluginComponentCallback =
        std::make_shared<ANIPluginCallback>(CallBackType::RequestCallBack, cbInfo, asyncJSCallbackInfo_);
    if (pPluginComponentCallback != nullptr) {
        pPluginComponentCallback->SetWant(want);
        pPluginComponentCallback->SetRequestParam(param);
        eventList_.insert(std::make_pair(pPluginComponentCallback->GetID(), pPluginComponentCallback));
        PluginComponentManager::GetInstance()->RegisterCallBack(
            want, pPluginComponentCallback, CallBackType::RequestCallBack);
        return true;
    } else {
        return false;
    }
}

void ANIPluginCallbackMgr::UnRegisterEvent(size_t key)
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto iter = eventList_.find(key);
    if (iter != eventList_.end()) {
        eventList_.erase(iter);
    }
}
} // namespace OHOS::Ace::Ani
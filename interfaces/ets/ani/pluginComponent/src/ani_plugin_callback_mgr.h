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
#ifndef OHOS_ANI_ACE_PLUGIN_CALLBACK_MGR_H
#define OHOS_ANI_ACE_PLUGIN_CALLBACK_MGR_H

#include <map>
#include <mutex>
#include <string>

#include "ani_plugin_callback.h"
#include "ani_plugin_component_data.h"

namespace OHOS::Ace::Ani {
using namespace OHOS::Ace;

class ANIPluginCallbackMgr final {
public:
    ANIPluginCallbackMgr();
    ~ANIPluginCallbackMgr();

    static ANIPluginCallbackMgr& Instance(void);
    bool RegisterOnEvent(ani_env* env, CallBackType eventType, const AAFwk::Want& want, ACECallbackInfo& cbInfo);
    bool RegisterRequestEvent(ani_env* env, const AAFwk::Want& want, ACECallbackInfo& cbInfo,
        const std::shared_ptr<AceJSPluginRequestParam>& param);
    void UnRegisterEvent(size_t key);

private:
    std::mutex mutex_;
    ACEAsyncJSCallbackInfo* asyncJSCallbackInfo_ = nullptr;
    std::map<size_t, std::shared_ptr<ANIPluginCallback>> eventList_;
};
} // namespace OHOS::Ace::Ani
#endif // OHOS_ANI_ACE_PLUGIN_CALLBACK_MGR_H
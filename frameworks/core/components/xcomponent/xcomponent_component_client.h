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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_CLIENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_CLIENT_H

#include <string>

#include "core/common/container.h"
#include "core/components/xcomponent/xcomponent_component.h"

namespace OHOS::Ace::Framework {
class XComponentComponentClient {
public:
    XComponentComponentClient& operator=(const XComponentComponentClient&) = delete;
    XComponentComponentClient(const XComponentComponentClient&) = delete;
    ~XComponentComponentClient() = default;

    static XComponentComponentClient& GetInstance()
    {
        static XComponentComponentClient instance;
        return instance;
    }

    RefPtr<XComponentComponent> GetXComponentFromXcomponentsMap(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto iter = xcomponentsMap_.find(idWithContainerId);
        if (iter == xcomponentsMap_.end()) {
            LOGE("xcomponent: %s not exists", xcomponentId.c_str());
            return nullptr;
        }
        return AceType::DynamicCast<XComponentComponent>(iter->second.Upgrade());
    }

    void AddXComponentToXcomponentsMap(const std::string& xcomponentId, const RefPtr<XComponentComponent>& component)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto result = xcomponentsMap_.try_emplace(idWithContainerId, component);
        if (!result.second) {
            auto oldXcomponent = result.first->second.Upgrade();
            if (oldXcomponent) {
                oldXcomponent->SetDeleteCallbackToNull();
            }
            result.first->second = component;
        }
    }

    void DeleteFromXcomponentsMapById(const std::string& xcomponentId)
    {
        auto idWithContainerId = xcomponentId + std::to_string(Container::CurrentId());
        auto it = xcomponentsMap_.find(idWithContainerId);
        if (it == xcomponentsMap_.end()) {
            return;
        }
        auto xcomponent = it->second.Upgrade();
        if (xcomponent) {
            xcomponent->SetDeleteCallbackToNull();
        }
        xcomponentsMap_.erase(it);
    }

private:
    XComponentComponentClient() = default;
    std::unordered_map<std::string, WeakPtr<XComponentComponent>> xcomponentsMap_;
};

} // namespace OHOS::Ace::Framework
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_XCOMPONENT_XCOMPONENT_COMPONENT_CLIENT_H
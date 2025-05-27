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

#include "core/components_ng/pattern/pattern.h"
#include "core/common/resource/resource_parse_utils.h"
 
namespace OHOS::Ace::NG {
int32_t Pattern::OnRecvCommand(const std::string& command)
{
    auto json = JsonUtil::ParseJsonString(command);
    if (!json || !json->IsValid() || !json->IsObject()) {
        return RET_FAILED;
    }
    auto event = json->GetString("cmd");
    if (event.compare("click") == 0) {
        auto host = GetHost();
        CHECK_NULL_RETURN(host, RET_FAILED);
        auto eventHub = host->GetOrCreateEventHub<EventHub>();
        CHECK_NULL_RETURN(eventHub, RET_FAILED);
        if (!eventHub->IsEnabled()) {
            return RET_FAILED;
        }
        auto gestureHub = host->GetOrCreateGestureEventHub();
        CHECK_NULL_RETURN(gestureHub, RET_FAILED);
        auto clickEventFunc = gestureHub->GetClickEvent();
        CHECK_NULL_RETURN(clickEventFunc, RET_FAILED);
        GestureEvent info;
        clickEventFunc(info);
        return RET_SUCCESS;
    } else {
        return OnInjectionEvent(command);
    }
    return RET_FAILED;
}

void Pattern::OnColorModeChange(uint32_t colorMode)
{
    if (resourceMgr_) {
        resourceMgr_->ReloadResources();
    }
}

void Pattern::AddResObj(
    const std::string& key,
    const RefPtr<ResourceObject>& resObj,
    std::function<void(const RefPtr<ResourceObject>&)>&& updateFunc)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResource(key, resObj, std::move(updateFunc));
}

void Pattern::AddResCache(const std::string& key, const std::string& value)
{
    if (resourceMgr_ == nullptr) {
        resourceMgr_ = MakeRefPtr<PatternResourceManager>();
    }
    resourceMgr_->AddResCache(key, value);
}

std::string Pattern::GetResCacheMapByKey(const std::string& key)
{
    if (resourceMgr_ == nullptr) {
        return "";
    }
    return resourceMgr_->GetResCacheMapByKey(key);
}

void Pattern::RemoveResObj(const std::string& key)
{
    if (resourceMgr_) {
        resourceMgr_->RemoveResource(key);
        if (resourceMgr_->Empty()) {
            resourceMgr_ = nullptr;
        }
    }
}

void Pattern::UnRegisterResource(const std::string& key)
{
    RemoveResObj(key);
}
} // namespace OHOS::Ace::NG

/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/manager/recoverable/recoverable_manager.h"

#include "base/log/dump_log.h"
#include "core/components_ng/pattern/navigation/navdestination_node_base.h"
#include "core/components_ng/pattern/stage/page_pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

int32_t RecoverableManager::AddRestoreComponent(bool isNavigationType, int32_t pageId, const std::string& componentId,
    std::function<std::string()> saveCallback)
{
    RestoreInfo info;
    info.saveCallback = saveCallback;
    info.componentId = componentId;
    info.callbackId = restoreCallbackId_;
    restoreCallbackId_++;
    auto& restoreInfo = GetRestoreInfo(isNavigationType);
    auto pageIter = restoreInfo.find(pageId);
    if (pageIter == restoreInfo.end()) {
        std::unordered_map<int32_t, RestoreInfo> values;
        values.insert(std::make_pair(info.callbackId, info));
        restoreInfo.insert(std::make_pair(pageId, values));
        return info.callbackId;
    }
    pageIter->second.insert(std::make_pair(info.callbackId, info));
    return info.callbackId;
}

void RecoverableManager::RemoveRestoreComponent(bool isNavigationType, int32_t pageId, int32_t callbackId)
{
    auto& restoreInfo = GetRestoreInfo(isNavigationType);
    auto pageIter = restoreInfo.find(pageId);
    if (pageIter == restoreInfo.end()) {
        return;
    }
    auto& pageInfos = pageIter->second;
    auto callbackIter = pageInfos.find(callbackId);
    if (callbackIter != pageInfos.end()) {
        pageInfos.erase(callbackIter);
    }
    if (pageInfos.size() == 0) {
        restoreInfo.erase(pageIter);
    }
}

bool RecoverableManager::GetRestoreByComponent(
    bool isNavigationType, int32_t pageId, std::string& componentId, std::string& result)
{
    if (!isNavigationType) {
        auto node = FrameNode::GetFrameNodeOnly(V2::PAGE_ETS_TAG, pageId);
        CHECK_NULL_RETURN(node, false);
        auto pagePattern = node->GetPattern<PagePattern>();
        CHECK_NULL_RETURN(pagePattern, false);
        return pagePattern->GetComponentInfo(componentId, result);
    }
    // check is navdestination
    auto node = FrameNode::GetFrameNodeOnly(V2::NAVDESTINATION_VIEW_ETS_TAG, pageId);
    if (!node) {
        node = FrameNode::GetFrameNodeOnly(V2::NAVBAR_ETS_TAG, pageId);
        if (!node) {
            return false;
        }
    }

    auto navdestination = AceType::DynamicCast<NavDestinationNodeBase>(node);
    CHECK_NULL_RETURN(navdestination, false);
    return navdestination->GetComponentInfo(componentId, result);
}

void RecoverableManager::RemoveRestoreByPage(bool isNavigationType, int32_t pageId)
{
    auto& restoreInfo = GetRestoreInfo(isNavigationType);
    auto pageIter = restoreInfo.find(pageId);
    if (pageIter == restoreInfo.end()) {
        return;
    }
    restoreInfo.erase(pageIter);
}

bool RecoverableManager::GetRestoreByPage(bool isNavigationType, int32_t pageId, std::string& result)
{
    auto& restoreInfo = GetRestoreInfo(isNavigationType);
    auto pageIter = restoreInfo.find(pageId);
    if (pageIter == restoreInfo.end()) {
        return false;
    }
    auto info = JsonUtil::CreateArray(true);
    auto componentsInfo = pageIter->second;
    for (auto component : componentsInfo) {
        auto componentRestoreInfo = component.second;
        if (componentRestoreInfo.saveCallback) {
            auto item = JsonUtil::Create();
            item->Put("componentId", componentRestoreInfo.componentId.c_str());
            std::string infoValue = componentRestoreInfo.saveCallback();
            item->Put("info", infoValue.c_str());
            info->Put(item);
        }
    }
    result = info->ToString();
    return true;
}

std::string RecoverableManager::TakeNavigationHomeInfo(const std::string& navigationId)
{
    std::string result;
    auto homeIter = homeNavigationInfo_.find(navigationId);
    if (homeIter == homeNavigationInfo_.end()) {
        return "";
    }
    result = homeIter->second;
    homeNavigationInfo_.erase(homeIter);
    return result;
}

void RecoverableManager::SetNavigationHomeInfo(const std::string& navigationId, const std::string& homeInfo)
{
    homeNavigationInfo_[navigationId] = homeInfo;
}
} // namespace OHOS::Ace::NG

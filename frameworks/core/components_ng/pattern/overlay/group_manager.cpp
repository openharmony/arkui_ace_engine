/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/overlay/group_manager.h"

#include "core/components_ng/pattern/stage/page_event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"

namespace OHOS::Ace::NG {

void GroupManager::AddRadioToGroup(const std::string& group, int32_t radioId)
{
    radioGroupNotify_[group].push_back(radioId);
}

void GroupManager::RemoveRadioFromGroup(const std::string& group, int32_t radioId)
{
    radioGroupNotify_[group].remove(radioId);
}

bool GroupManager::HasRadioId(const std::string& group, int32_t radioId)
{
    auto list = radioGroupNotify_[group];
    auto it = find(list.begin(), list.end(), radioId);
    return it != list.end();
}

void GroupManager::UpdateRadioGroupValue(const std::string& group, int32_t radioId)
{
    const auto& list = radioGroupNotify_[group];
    for (auto&& item : list) {
        if (item == radioId) {
            continue;
        }
        auto node = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(item));
        if (!node) {
            continue;
        }
        auto pattern = node->GetPattern<RadioPattern>();
        if (!pattern) {
            continue;
        }
        pattern->UpdateUncheckStatus(node);
    }
}

void GroupManager::AddCheckBoxToGroup(const std::string& group, const WeakPtr<FrameNode>& checkBoxNode)
{
    checkBoxListMap_[group].push_back(checkBoxNode);
    checkboxChangedMap_[group] = true;
}

void GroupManager::AddCheckBoxGroup(const std::string& group, const WeakPtr<FrameNode>& checkBoxGroupNode)
{
    auto frameNode = checkBoxGroupNode.Upgrade();
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    if (checkBoxGroupMap_[group].Upgrade()) {
        pattern->SetIsAddToMap(false);
    } else {
        pattern->SetIsAddToMap(true);
        checkBoxGroupMap_[group] = frameNode;
    }
}

void GroupManager::RemoveCheckBoxFromGroup(const std::string& group, int32_t checkBoxId)
{
    auto& checkboxList = checkBoxListMap_[group];
    for (auto && item : checkboxList) {
        auto frameNode = item.Upgrade();
        if (frameNode && frameNode->GetId() == checkBoxId) {
            checkboxList.remove(item);
            checkboxChangedMap_[group] = true;
            return;
        }
    }
}

void GroupManager::RemoveCheckBoxGroup(const std::string& group, int32_t checkBoxGroupId)
{
    auto frameNode = checkBoxGroupMap_[group].Upgrade();
    if (frameNode && frameNode->GetId() == checkBoxGroupId) {
        checkBoxGroupMap_.erase(group);
    }
}

std::list<RefPtr<FrameNode>> GroupManager::GetCheckboxList(const std::string& group)
{
    auto checkboxList = checkBoxListMap_[group];
    std::list<RefPtr<FrameNode>> result;
    for (std::list<WeakPtr<FrameNode>>::iterator iter = checkboxList.begin(); iter != checkboxList.end();) {
        auto frameNode = (*iter).Upgrade();
        if (!frameNode) {
            iter = checkboxList.erase(iter);
        } else {
            result.push_back(frameNode);
            ++iter;
        }
    }
    return result;
}

RefPtr<FrameNode> GroupManager::GetCheckboxGroup(const std::string& group)
{
    return checkBoxGroupMap_[group].Upgrade();
}

WeakPtr<GroupManager> GroupManager::GetGroupManager()
{
    WeakPtr<GroupManager> groupManager;
    auto context = PipelineContext::GetCurrentContext();
    CHECK_NULL_RETURN(context, nullptr);
    if (Container::IsInSubContainer()) {
        auto overlayManager = context->GetOverlayManager();
        CHECK_NULL_RETURN(overlayManager, nullptr);
        groupManager = overlayManager->GetGroupManager();
    } else {
        auto stageManager = context->GetStageManager();
        CHECK_NULL_RETURN(stageManager, nullptr);
        auto pageNode = stageManager->GetLastPage();
        CHECK_NULL_RETURN(pageNode, nullptr);
        auto pageEventHub = pageNode->GetEventHub<NG::PageEventHub>();
        CHECK_NULL_RETURN(pageEventHub, nullptr);
        groupManager = pageEventHub->GetGroupManager();
    }
    return groupManager;
}
} // namespace OHOS::Ace::NG

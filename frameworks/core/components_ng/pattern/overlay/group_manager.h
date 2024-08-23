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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_GROUP_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_GROUP_MANAGER_H

#include <cstdint>

#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class GroupManager : public virtual AceType {
    DECLARE_ACE_TYPE(GroupManager, AceType)

public:
    GroupManager() = default;
    ~GroupManager() override = default;

    void AddRadioToGroup(const std::string& group, int32_t radioId);
    void RemoveRadioFromGroup(const std::string& group, int32_t radioId);
    bool HasRadioId(const std::string& group, int32_t radioId);
    void UpdateRadioGroupValue(const std::string& group, int32_t radioId);

    void AddCheckBoxToGroup(const std::string& group, const WeakPtr<FrameNode>& checkBoxNode);
    void RemoveCheckBoxFromGroup(const std::string& group, int32_t checkBoxId);
    void AddCheckBoxGroup(const std::string& group, const WeakPtr<FrameNode>& checkBoxGroupNode);
    void RemoveCheckBoxGroup(const std::string& group, int32_t checkBoxGroupId);
    std::list<RefPtr<FrameNode>> GetCheckboxList(const std::string& group);
    RefPtr<FrameNode> GetCheckboxGroup(const std::string& group);
    bool GetCheckboxGroupIsChange(const std::string& group)
    {
        return checkboxChangedMap_[group];
    };

    void SetCheckboxGroupIsChange(const std::string& group, bool flag)
    {
        checkboxChangedMap_[group] = flag;
    };

    std::string GetLastNavId()
    {
        return lastNavId_.value_or("");
    }

    void SetLastNavId(std::optional<std::string> lastNavId)
    {
        lastNavId_ = lastNavId;
    }

    static WeakPtr<GroupManager> GetGroupManager();

private:
    std::unordered_map<std::string, std::list<int32_t>> radioGroupNotify_;
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> checkBoxListMap_;
    std::unordered_map<std::string, WeakPtr<FrameNode>> checkBoxGroupMap_;
    std::optional<std::string> lastNavId_;
    std::unordered_map<std::string, bool> checkboxChangedMap_;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_GROUP_MANAGER_H

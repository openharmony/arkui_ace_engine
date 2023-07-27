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

#include "core/components_ng/pattern/stage/page_event_hub.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"
#include "core/pipeline/base/element_register.h"
#include "core/pipeline_ng/ui_task_scheduler.h"

namespace OHOS::Ace::NG {

void PageEventHub::AddRadioToGroup(const std::string& group, int32_t radioId)
{
    radioGroupNotify_[group].push_back(radioId);
}

void PageEventHub::RemoveRadioFromGroup(const std::string& group, int32_t radioId)
{
    radioGroupNotify_[group].remove(radioId);
}

bool PageEventHub::HasRadioId(const std::string& group, int32_t radioId)
{
    auto list = radioGroupNotify_[group];
    auto it = find(list.begin(), list.end(), radioId);
    return it != list.end();
}
    
void PageEventHub::UpdateRadioGroupValue(const std::string& group, int32_t radioId)
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

void PageEventHub::AddCheckBoxToGroup(const std::string& group, int32_t checkboxId)
{
    checkBoxGroupNotify_[group].push_back(checkboxId);
}

void PageEventHub::AddCheckBoxGroupToGroup(const std::string& group, int32_t checkBoxId)
{
    auto checkBoxGroupFrameNode = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(checkBoxId));
    CHECK_NULL_VOID(checkBoxGroupFrameNode);
    const auto& list = checkBoxGroupNotify_[group];
    auto pattern = checkBoxGroupFrameNode->GetPattern<CheckBoxGroupPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsAddToMap(true);
    for (auto&& item : list) {
        auto node = DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(item));
        if (!node) {
            continue;
        }
        if (checkBoxId == item) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            pattern->SetIsAddToMap(false);
            return;
        }
    }
    checkBoxGroupNotify_[group].push_back(checkBoxId);
}

void PageEventHub::RemoveCheckBoxFromGroup(const std::string& group, int32_t checkBoxId)
{
    checkBoxGroupNotify_[group].remove(checkBoxId);
}

std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> PageEventHub::GetCheckBoxGroupMap()
{
    std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>> group;
    for (const auto& [name, ids] : checkBoxGroupNotify_) {
        std::list<WeakPtr<FrameNode>> list;
        for (const auto& id : ids) {
            list.emplace_back(DynamicCast<FrameNode>(ElementRegister::GetInstance()->GetNodeById(id)));
        }
        group.emplace(name, std::move(list));
    }
    return group;
}

} // namespace OHOS::Ace::NG

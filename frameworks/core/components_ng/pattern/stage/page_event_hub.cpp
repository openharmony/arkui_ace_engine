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

#include "core/components_ng/pattern/checkbox/checkbox_pattern.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_pattern.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/components_ng/pattern/radio/radio_pattern.h"
#include "core/components_v2/inspector/inspector_constants.h"

namespace OHOS::Ace::NG {

void PageEventHub::AddRadioToGroup(const std::string& group, const RefPtr<FrameNode>& radioFrameNode)
{
    radioGroupNotify_[group].push_back(radioFrameNode);
}

void PageEventHub::RemoveRadioFromGroup(const std::string& group, const RefPtr<FrameNode>& radioFrameNode)
{
    radioGroupNotify_[group].remove(radioFrameNode);
}

void PageEventHub::UpdateRadioGroupValue(const std::string& group, const RefPtr<FrameNode>& radioFrameNode)
{
    const auto& list = radioGroupNotify_[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (node == radioFrameNode) {
            continue;
        }
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

void PageEventHub::AddCheckBoxToGroup(const std::string& group, const RefPtr<FrameNode>& checkBoxFrameNode)
{
    checkBoxGroupNotify_[group].push_back(checkBoxFrameNode);
}

void PageEventHub::AddCheckBoxGroupToGroup(const std::string& group, const RefPtr<FrameNode>& checkBoxGroupFrameNode)
{
    // 判断是否已经存在同名的CheckBoxGroup，如果已经存在，不加入map
    const auto& list = checkBoxGroupNotify_[group];
    for (auto&& item : list) {
        auto node = item.Upgrade();
        if (!node) {
            continue;
        }
        if (node->GetTag() == V2::CHECKBOXGROUP_ETS_TAG) {
            auto pattern = checkBoxGroupFrameNode->GetPattern<CheckBoxGroupPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetIsAddToMap(false);
            return;
        }
    }
    checkBoxGroupNotify_[group].push_back(checkBoxGroupFrameNode);
}

void PageEventHub::RemoveCheckBoxFromGroup(const std::string& group, const RefPtr<FrameNode>& checkBoxFrameNode)
{
    checkBoxGroupNotify_[group].remove(checkBoxFrameNode);
}

} // namespace OHOS::Ace::NG
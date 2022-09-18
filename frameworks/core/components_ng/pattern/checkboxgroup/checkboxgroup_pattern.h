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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H

#include "base/geometry/axis.h"
#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_event_hub.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_layout_algorithm.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_method.h"
#include "core/components_ng/pattern/checkboxgroup/checkboxgroup_paint_property.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class CheckBoxGroupPattern : public Pattern {
    DECLARE_ACE_TYPE(CheckBoxGroupPattern, Pattern);

public:
    CheckBoxGroupPattern() = default;
    ~CheckBoxGroupPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<CheckBoxGroupPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<CheckBoxGroupLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<CheckBoxGroupPaintMethod>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<CheckBoxGroupEventHub>();
    }

    const std::optional<std::string>& GetPreGroup()
    {
        return preGroup_;
    }

    void SetPreGroup(const std::string& group)
    {
        preGroup_ = group;
    }

    bool GetIsAddToMap() const
    {
        return isAddToMap_;
    }

    void SetIsAddToMap(bool isAddToMap)
    {
        isAddToMap_ = isAddToMap;
    }

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void OnClick();

    void UpdateState();
    void UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool select);
    void UpdateRepeatedGroupStatus(const RefPtr<FrameNode>& frameNode, bool select);
    void UpdateCheckBoxStatus(const RefPtr<FrameNode>& checkBoxGroupFrameNode,
        std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap, bool select);
    void UpdateCheckBoxGroupStatusByOtherCheckBox(const RefPtr<FrameNode>& checkBoxGroupFrameNode,
        std::unordered_map<std::string, std::list<WeakPtr<FrameNode>>>& checkBoxGroupMap);

    std::optional<std::string> preGroup_;
    bool isAddToMap_ = true;

    RefPtr<ClickEvent> clickListener_;

    ACE_DISALLOW_COPY_AND_MOVE(CheckBoxGroupPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_CHECKBOXGROUP_CHECKBOXGROUP_PATTERN_H

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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_PATTERN_H

#include "base/memory/referenced.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/pattern/radio/radio_event_hub.h"
#include "core/components_ng/pattern/radio/radio_layout_algorithm.h"
#include "core/components_ng/pattern/radio/radio_paint_method.h"
#include "core/components_ng/pattern/radio/radio_paint_property.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {

class RadioPattern : public Pattern {
    DECLARE_ACE_TYPE(RadioPattern, Pattern);

public:
    RadioPattern() = default;
    ~RadioPattern() override = default;

    bool IsAtomicNode() const override
    {
        return true;
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<RadioPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        return MakeRefPtr<RadioLayoutAlgorithm>();
    }

    RefPtr<NodePaintMethod> CreateNodePaintMethod() override
    {
        return MakeRefPtr<RadioPaintMethod>();
    }

    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& /*dirty*/, const DirtySwapConfig& /*config*/) override
    {
        return true;
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<RadioEventHub>();
    }

    const std::optional<std::string>& GetPreValue()
    {
        return preValue_;
    }

    const std::optional<std::string>& GetPreGroup()
    {
        return preGroup_;
    }

    void SetPreValue(const std::string& value)
    {
        preValue_ = value;
    }

    void SetPreGroup(const std::string& group)
    {
        preGroup_ = group;
    }

    void UpdateUncheckStatus(const RefPtr<FrameNode>& frameNode);

private:
    void OnAttachToFrameNode() override;
    void OnDetachFromFrameNode(FrameNode* frameNode) override;
    void OnModifyDone() override;
    void OnClick();
    void UpdateState();
    void UpdateGroupCheckStatus(const RefPtr<FrameNode>& frameNode, bool check);

    RefPtr<ClickEvent> clickListener_;

    bool preCheck_ = false;
    std::optional<std::string> preValue_;
    std::optional<std::string> preGroup_;

    ACE_DISALLOW_COPY_AND_MOVE(RadioPattern);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_RADIO_RADIO_PATTERN_H

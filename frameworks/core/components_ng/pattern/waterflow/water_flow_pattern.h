/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H

#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"
#include "core/components_ng/pattern/waterflow/water_flow_event_hub.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_info.h"
#include "core/components_ng/pattern/waterflow/water_flow_layout_property.h"
#include "core/components_ng/pattern/waterflow/water_flow_position_controller.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT WaterFlowPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(WaterFlowPattern, ScrollablePattern);

public:
    bool UpdateCurrentOffset(float delta, int32_t source) override;
    bool IsAtTop() const override;
    bool IsAtBottom() const override;
    void UpdateScrollBarOffset() override;

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<WaterFlowLayoutProperty>();
    }

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<WaterFlowEventHub>();
    }
    bool UpdateStartIndex(int32_t index);

    void SetPositionController(RefPtr<WaterFlowPositionController> control);

    void AddFooter(const RefPtr<NG::UINode>& footer)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        if (layoutInfo_.footerIndex_ < 0) {
            layoutInfo_.footerIndex_ = 0;
            host->AddChild(footer);
        } else {
            host->ReplaceChild(host->GetChildAtIndex(layoutInfo_.footerIndex_), footer);
        }
        footer->SetActive(false);
    }

    void ResetLayoutInfo()
    {
        layoutInfo_.Reset();
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;
    void OnAttachToFrameNode() override;
    WaterFlowLayoutInfo layoutInfo_;
    // just for hold WaterFlowPositionController
    RefPtr<WaterFlowPositionController> controller_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_WATERFLOW_WATER_FLOW_PATTERN_H

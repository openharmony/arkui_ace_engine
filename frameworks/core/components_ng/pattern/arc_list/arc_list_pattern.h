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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_PATTERN_H

#include "core/components_ng/pattern/arc_list/arc_list_item_pattern.h"
#include "core/components_ng/pattern/arc_list/arc_list_layout_algorithm.h"
#include "core/components_ng/pattern/arc_list/arc_list_layout_property.h"
#include "core/components_ng/pattern/arc_list/arc_list_position_map.h"
#include "core/components_ng/pattern/list/list_pattern.h"

#ifdef SUPPORT_DIGITAL_CROWN
#include "core/event/crown_event.h"
#endif

namespace OHOS::Ace::NG {

struct ItemSnapInfo {
    float snapLow;
    float snapHigh;
    float moveThreshold;
};

class ArcListPattern : public ListPattern {
    DECLARE_ACE_TYPE(ArcListPattern, ListPattern);

public:
    ArcListPattern();
    ~ArcListPattern() override = default;

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<ArcListLayoutProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override;

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    std::function<bool(int32_t)> GetScrollIndexAbility() override;

    void OnChildrenSizeChanged(std::tuple<int32_t, int32_t, int32_t> change, ListChangeFlag flag) override;

    void AddHeader(const RefPtr<NG::FrameNode>& header)
    {
        auto host = GetHost();
        CHECK_NULL_VOID(host);
        auto prevHeader = header_;
        if (!prevHeader) {
            host->AddChild(header);
        } else if (prevHeader != header) {
            host->ReplaceChild(prevHeader, header);
            host->MarkDirtyNode(PROPERTY_UPDATE_BY_CHILD_REQUEST);
        }
        header_ = header;
    }

    void FixScrollParam(float mainPos, float& correctVelocity, float& finalPos);

#ifdef SUPPORT_DIGITAL_CROWN
    void SetDigitalCrownSensitivity(CrownSensitivity sensitivity)
    {
        crownSensitivity_ = sensitivity;
        CHECK_NULL_VOID(scrollable_);
        scrollable_->SetDigitalCrownSensitivity(crownSensitivity_);
    }
    CrownSensitivity GetDigitalCrownSensitivity()
    {
        return crownSensitivity_;
    }
#endif

protected:
    void SetFriction(double friction) override;
    void HandleScrollBarOutBoundary() override;
    float GetSnapCenterOverScrollPos(float startPos, float prevScroll);
private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    bool ScrollListForFocus(int32_t nextIndex, int32_t curIndex, int32_t nextIndexInGroup) override;

    bool OnScrollCallback(float offset, int32_t source) override;
    void SetEdgeEffectCallback(const RefPtr<ScrollEdgeEffect>& scrollEffect) override;

    bool GetOneItemSnapPosByFinalPos(float mainPos, float finalPos, float& snapPos);
    int32_t GetMidIndex();
    ListItemInfo GetItemDisplayInfo(int32_t index);
    bool GetItemSnapPosition(int32_t nIndex, ItemSnapInfo& snapInfo);

    float FixScrollOffset(float offset, int32_t source);
    void OnScrollVisibleContentChange(const RefPtr<ListEventHub>& listEventHub, bool indexChanged) override {}
    float GetScrollUpdateFriction(float overScroll) override;
    ScrollAlign GetScrollToNodeAlign() override
    {
        return ScrollAlign::CENTER;
    }

    RefPtr<FrameNode> header_ = nullptr;
    int32_t scrollStartMidIndex_ = -1;
    float startHeaderPos_ = 0.0f;
    float headerOffset_ = -1.0f;
    float oldHeaderSize_ = 0.0f;
    float oldFirstItemSize_ = -1.0f;
    bool headerStayNear_ = false;
#ifdef SUPPORT_DIGITAL_CROWN
    CrownSensitivity crownSensitivity_ = CrownSensitivity::MEDIUM;
#endif
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_ARC_LIST_ARC_LIST_PATTERN_H

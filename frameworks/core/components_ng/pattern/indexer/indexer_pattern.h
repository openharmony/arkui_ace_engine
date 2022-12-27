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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_PATTERN_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_INDEXER_INDEXER_PATTERN_H

#include <optional>
#include <stdint.h>

#include "base/memory/referenced.h"
#include "core/components/indexer/indexer_theme.h"
#include "core/components_ng/event/event_hub.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_event_hub.h"
#include "core/components_ng/pattern/indexer/indexer_layout_algorithm.h"
#include "core/components_ng/pattern/indexer/indexer_layout_property.h"
#include "core/components_ng/pattern/indexer/indexer_paint_property.h"
#include "core/components_ng/pattern/pattern.h"

namespace OHOS::Ace::NG {

class IndexerPattern : public Pattern {
    DECLARE_ACE_TYPE(IndexerPattern, Pattern);

public:
    IndexerPattern() = default;
    ~IndexerPattern() override = default;

    RefPtr<EventHub> CreateEventHub() override
    {
        return MakeRefPtr<IndexerEventHub>();
    }

    RefPtr<LayoutProperty> CreateLayoutProperty() override
    {
        return MakeRefPtr<IndexerLayoutProperty>();
    }

    RefPtr<PaintProperty> CreatePaintProperty() override
    {
        return MakeRefPtr<IndexerPaintProperty>();
    }

    RefPtr<LayoutAlgorithm> CreateLayoutAlgorithm() override
    {
        auto indexerLayoutAlgorithm = MakeRefPtr<IndexerLayoutAlgorithm>(itemCount_);
        return indexerLayoutAlgorithm;
    }

    void SetIsTouch(bool isTouch)
    {
        isTouch_ = isTouch;
    }

    const std::vector<std::string>& GetArrayValue()
    {
        return arrayValue_;
    }

    FocusPattern GetFocusPattern() const override
    {
        return { FocusType::NODE, true };
    }

private:
    void OnModifyDone() override;
    bool OnDirtyLayoutWrapperSwap(const RefPtr<LayoutWrapper>& dirty, const DirtySwapConfig& config) override;

    void OnTouchDown(const TouchEventInfo& info);
    void OnTouchUp(const TouchEventInfo& info);
    void MoveIndexByOffset(const Offset& offset);
    bool MoveIndexByStep(int32_t step);
    bool KeyIndexByStep(int32_t step);
    bool MoveIndexBySearch(const std::string& searchStr);
    void ApplyIndexChanged(bool refreshBubble = true);
    void OnSelectChanged();
    int32_t GetSkipChildIndex(int32_t step);
    int32_t GetFocusChildIndex(const std::string& searchStr);
    void SetPositionOfPopupNode(RefPtr<FrameNode>& customNode);

    void InitPanEvent(const RefPtr<GestureEventHub>& gestureHub);
    void InitInputEvent();
    void InitCurrentInputEvent();
    void InitChildInputEvent();
    void InitOnKeyEvent();
    bool OnKeyEvent(const KeyEvent& event);
    void OnHover(bool isHover);
    void OnChildHover(int32_t index, bool isHover);
    void BeginBubbleAnimation(RefPtr<FrameNode> animationNode);
    void ResetStatus();
    void OnKeyEventDisapear();
    void InitBubbleList(
        std::vector<std::string>& currentListData, RefPtr<FrameNode>& parentNode, RefPtr<IndexerTheme>& indexerTheme);
    void AddPopupTouchListener(RefPtr<FrameNode> popupNode);
    void OnPopupTouchDown(const TouchEventInfo& info);
    void AddListItemClickListener(RefPtr<FrameNode>& listItemNode, int32_t index);
    void OnListItemClick(int32_t index);
    void ChangeListItemsBgColor(int32_t clickIndex);
    RefPtr<FrameNode> InitBubbleView();
    bool NeedShowBubble();
    void ShowBubble();
    bool IfSelectIndexValid();
    int32_t GetSelectChildIndex(const Offset& offset);

    RefPtr<TouchEventImpl> touchListener_;
    RefPtr<PanEvent> panEvent_;
    bool isInputEventRegisted_ = false;
    bool isKeyEventRegisted_ = false;
    bool isTouch_ = false;
    bool isHover_ = false;
    bool removePopupNode_ = true;

    std::vector<std::string> arrayValue_;
    int32_t itemCount_ = 0;
    int32_t selected_ = 0;
    bool initialized_ = false;
    int32_t childHoverIndex_ = -1;
    int32_t childFocusIndex_ = -1;
    int32_t childPressIndex_ = -1;
    float itemSizeRender_ = 0.0f;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_PATTERN_H

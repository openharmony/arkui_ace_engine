/*
 * Copyright (c) 2025-2026 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_CONTAINER_EVENT_HUB_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLLABLE_SELECTABLE_CONTAINER_EVENT_HUB_H

#include "core/animation/select_motion.h"
#include "core/components_ng/event/pan_event.h"
#include "core/components_ng/pattern/scrollable/scrollable_pattern.h"

namespace OHOS::Ace::NG {

enum class PreviewBadgeMode {
    NO_BADGE = 0,
    AUTO,
    USER_SET
};

struct PreviewBadge {
    PreviewBadgeMode mode = PreviewBadgeMode::AUTO;
    int32_t count;
};
using GetPreviewBadge = std::function<PreviewBadge()>;
struct EditModeOptions {
    bool enableGatherSelectedItemsAnimation = false;
    GetPreviewBadge getPreviewBadge;
    bool useDefaultMultiSelectStyle = true;
    bool enableFingerMultiSelect = true;
};

class SelectableContainerPattern : public ScrollablePattern {
    DECLARE_ACE_TYPE(SelectableContainerPattern, ScrollablePattern);

public:
    struct SwipeSelectStateKey {
        int32_t index = -1;
        int32_t indexInGroup = -1;

        bool operator<(const SwipeSelectStateKey& other) const
        {
            if (index != other.index) {
                return index < other.index;
            }
            return indexInGroup < other.indexInGroup;
        }

        bool operator==(const SwipeSelectStateKey& other) const
        {
            return index == other.index && indexInGroup == other.indexInGroup;
        }

        bool IsValid() const
        {
            return index >= 0;
        }
    };

    SelectableContainerPattern() = default;
    ~SelectableContainerPattern() override = default;
    virtual std::vector<RefPtr<FrameNode>> GetVisibleSelectedItems() = 0;
    void SetEditModeOptions(const EditModeOptions& editModeOptions)
    {
        editModeOptions_ = editModeOptions;
    }

    EditModeOptions GetEditModeOptions() const
    {
        return editModeOptions_;
    }

    void ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const override;

    void MarkSelectedItems();
    bool ShouldSelectScrollBeStopped();
    void UpdateMouseStart(float offset);

    void SetEnableEditMode(bool enable);
    bool GetEnableEditMode() const;
    void SetEnableEditModeChangeEvent(std::function<void(bool)>&& event)
    {
        enableEditModeChangeEvent_ = std::move(event);
    }
    void SetEnableEditModeBindingEvent(std::function<void(bool)>&& event)
    {
        enableEditModeBindingEvent_ = std::move(event);
    }
    void FireEnableEditModeChangeEvent(bool enable) const
    {
        if (enableEditModeChangeEvent_) {
            enableEditModeChangeEvent_(enable);
        }
        if (enableEditModeBindingEvent_) {
            enableEditModeBindingEvent_(enable);
        }
    }
    bool HasEnableEditModeBinding() const
    {
        return static_cast<bool>(enableEditModeBindingEvent_) ||
               static_cast<bool>(enableEditModeChangeEvent_);
    }
    bool IsDefaultMultiSelectStyleEnabled() const
    {
        return enableEditMode_ && editModeOptions_.useDefaultMultiSelectStyle;
    }

    void InitSwipeSelectEvent();
    void UninitSwipeSelectEvent();
    bool ShouldEnableTwoFingerSelect() const;
    void TryEnterEditModeForSwipeSelect();
    GestureJudgeResult JudgeSwipeSelectGesture(const RefPtr<NG::GestureInfo>& gestureInfo,
        const std::shared_ptr<BaseGestureEvent>& event);
    void HandleSwipeSelectStart(const GestureEvent& info);
    void HandleSwipeSelectUpdate(const GestureEvent& info);
    void HandleSwipeSelectEnd();
    void HandleSwipeSelectCancel();
    void UpdateSwipeSelection();

    virtual bool NeedJudgeWithHotZone()
    {
        return false;
    }

    virtual int32_t GetItemAtPosition(float offsetX, float offsetY) const
    {
        return -1;
    }

    virtual bool IsInEditModeHotZone(const PointF& point) const
    {
        return GetItemAtPosition(point.GetX(), point.GetY()) >= 0;
    }

    virtual void MarkSwipeItemSelected(int32_t index, bool isSelected) {}
    virtual SwipeSelectStateKey GetSwipeSelectStateKeyAtPosition(float offsetX, float offsetY) const
    {
        return { GetItemAtPosition(offsetX, offsetY), -1 };
    }
    virtual SwipeSelectStateKey GetSwipeSelectStateKeyAtIndex(int32_t index) const
    {
        return { index, -1 };
    }
    virtual RefPtr<FrameNode> GetSelectableItemAtIndex(int32_t index) const;
    virtual RefPtr<FrameNode> GetSelectableItemAtStateKey(const SwipeSelectStateKey& stateKey) const
    {
        return GetSelectableItemAtIndex(stateKey.index);
    }
    virtual void MarkSwipeItemSelectedByStateKey(const SwipeSelectStateKey& stateKey, bool isSelected)
    {
        MarkSwipeItemSelected(stateKey.index, isSelected);
    }
    virtual void BuildSwipeSelectStateKeysInRange(const SwipeSelectStateKey& startKey,
        const SwipeSelectStateKey& endKey, std::vector<SwipeSelectStateKey>& keys) const
    {
        if (!startKey.IsValid() || !endKey.IsValid()) {
            return;
        }
        auto rangeStartKey = endKey < startKey ? endKey : startKey;
        auto rangeEndKey = startKey < endKey ? endKey : startKey;
        for (int32_t index = rangeStartKey.index; index <= rangeEndKey.index; ++index) {
            auto stateKey = GetSwipeSelectStateKeyAtIndex(index);
            if (!(stateKey < rangeStartKey) && !(rangeEndKey < stateKey)) {
                keys.emplace_back(stateKey);
            }
        }
    }
    void SwipeSelectAutoScroll(const PointF& globalPoint);
    void StopSwipeSelectAutoScroll();

    virtual void ApplyEditModeToVisibleItems();
    virtual void RemoveEditModeFromItems();

protected:
    virtual void ApplyEditModeToCachedItems(bool enabled) {}
    struct ItemSelectedStatus {
        std::function<void(bool)> onSelected;
        std::function<void(bool)> selectChangeEvent;
        RectF rect;
        bool selected = false;
        void FireSelectChangeEvent(bool isSelected)
        {
            if (selected == isSelected) {
                return;
            }
            selected = isSelected;
            if (onSelected) {
                onSelected(isSelected);
            }
            if (selectChangeEvent) {
                selectChangeEvent(isSelected);
            }
        }
    };
    void InitMouseEvent();
    void UninitMouseEvent();
    void DrawSelectedZone(const RectF& selectedZone);
    void ClearSelectedZone();
    bool multiSelectable_ = false;
    bool isMouseEventInit_ = false;
    OffsetF mouseStartOffset_;
    float selectScrollOffset_ = 0.0f;
    float totalOffsetOfMousePressed_ = 0.0f;
    std::unordered_map<int32_t, ItemSelectedStatus> itemToBeSelected_;
    RefPtr<PanEvent> swipeSelectPanEvent_;

private:
    virtual void MultiSelectWithoutKeyboard(const RectF& selectedZone) {};
    virtual void ClearMultiSelect() {};
    virtual bool IsItemSelected(float offsetX, float offsetY)
    {
        return false;
    }
    void ClearInvisibleItemsSelectedStatus();
    void HandleInvisibleItemsSelectedStatus(const RectF& selectedZone);
    void HandleDragStart(const GestureEvent& info);
    void HandleDragUpdate(const GestureEvent& info);
    void HandleDragEnd();
    void SelectWithScroll();
    RectF ComputeSelectedZone(const OffsetF& startOffset, const OffsetF& endOffset);
    float GetOutOfScrollableOffset() const;
    virtual float GetOffsetWithLimit(float offset) const;
    void LimitMouseEndOffset();
    void UpdateMouseStartOffset();

    enum SelectDirection { SELECT_DOWN, SELECT_UP, SELECT_NONE };
    SelectDirection selectDirection_ = SELECT_NONE;
    bool mousePressed_ = false;
    bool canMultiSelect_ = false;
    OffsetF mouseEndOffset_;
    OffsetF mousePressOffset_;
    OffsetF lastMouseStart_;
    GestureEvent lastMouseMove_;
    RefPtr<SelectMotion> selectMotion_;
    RefPtr<PanEvent> boxSelectPanEvent_;

    EditModeOptions editModeOptions_;
    bool enableEditMode_ = false;
    std::function<void(bool)> enableEditModeChangeEvent_;
    std::function<void(bool)> enableEditModeBindingEvent_;
    enum class SwipeSelectState { INACTIVE, SELECTING, DESELECTING };
    SwipeSelectState swipeSelectState_ = SwipeSelectState::INACTIVE;
    SwipeSelectStateKey swipeStartStateKey_;
    SwipeSelectStateKey swipeCurrentStateKey_;
    std::map<SwipeSelectStateKey, bool> swipeOriginalStates_;
};
} // namespace OHOS::Ace::NG

#endif

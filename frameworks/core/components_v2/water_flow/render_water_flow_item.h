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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_ITEM_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_ITEM_H

#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {
class RenderWaterFlowItem : public RenderNode {
    DECLARE_ACE_TYPE(RenderWaterFlowItem, RenderNode);

public:
    using OnItemLongPressed = std::function<bool(int32_t, const WeakPtr<RenderNode>&)>;
    using OnSelectFunc = std::function<void(bool)>;

    static RefPtr<RenderNode> Create();

    void Update(const RefPtr<Component>& component) override;

    void PerformLayout() override;

    void HandleOnFocus();

    void SetColumnIndex(int32_t columnIndex);
    void SetRowIndex(int32_t rowIndex);
    void SetColumnSpan(int32_t columnSpan);
    void SetRowSpan(int32_t rowSpan);
    void SetForceRebuild(bool forceRebuild)
    {
        forceRebuild_ = forceRebuild;
    }

    bool GetForceRebuild() const
    {
        return forceRebuild_;
    }

    void SetBoundary()
    {
        TakeBoundary();
    }

    int32_t GetColumnSpan() const
    {
        return columnSpan_;
    }

    int32_t GetRowSpan() const
    {
        return rowSpan_;
    }

    void SetIndex(int32_t index)
    {
        index_ = index;
    }

    bool ForceRebuild() const
    {
        return forceRebuild_;
    }

    int32_t GetIndex() const
    {
        return index_;
    }

    bool GetSelectable() const
    {
        return selectable_;
    }

    OnSelectFunc GetOnSelectId() const
    {
        return onSelectId_;
    }

    void MarkIsSelected(bool isSelected)
    {
        isSelected_ = isSelected;
    }

    bool IsSelected() const
    {
        return isSelected_;
    }

    void SetCalSizeNeeded(bool need)
    {
        needCalSize_ = need;
    }

    bool GetCalSizeNeeded() const
    {
        return needCalSize_;
    }

private:
    int32_t index_ = -1;
    int32_t columnSpan_ = 1;
    int32_t rowSpan_ = 1;
    bool forceRebuild_ = false;
    OnSelectFunc onSelectId_;
    bool selectable_ = false;
    bool isSelected_ = false;
    bool needCalSize_ = true;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_WATER_FLOW_RENDER_WATER_FLOW_ITEM_H

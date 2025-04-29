/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H


#include <cstddef>
#include <cstdint>
#include <functional>
#include <optional>
#include <tuple>
#include <queue>

#include "base/geometry/dimension.h"
#include "base/memory/referenced.h"
#include "base/utils/utils.h"
#include "core/components_ng/base/ui_node.h"
#include "core/components_ng/syntax/lazy_for_each_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_node.h"
#include "core/components_ng/syntax/repeat_virtual_scroll_2_node.h"
#include "core/components_ng/pattern/list/list_children_main_size.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"
#include "core/components_ng/property/measure_property.h"


namespace OHOS::Ace::NG {
class ListItemGroupPattern;

struct ListPositionInfo {
    float mainPos;
    float mainSize;
    bool isGroup;
};

enum class ListPosMapUpdate {
    NO_CHANGE = 0,
    UPDATE_ALL_SIZE,
    RE_CALCULATE,
};

class ListPositionMap : public virtual AceType {
    DECLARE_ACE_TYPE(ListPositionMap, AceType)
public:
    ListPositionMap() = default;
    ~ListPositionMap() override = default;

    void UpdatePos(int32_t index, ListPositionInfo posInfo)
    {
        posMap_[index] = posInfo;
    }

    void UpdatePosRange(int32_t startIndex, int32_t endIndex, ListPositionInfo posInfo, float space, int32_t lanes);

    void UpdatePosWithCheck(int32_t index, ListPositionInfo posInfo);

    void ClearPosMap()
    {
        posMap_.clear();
    }

    void MarkDirty(ListChangeFlag flag)
    {
        dirty_ = dirty_ | flag;
    }

    void ClearDirty()
    {
        dirty_ = LIST_NO_CHANGE;
    }

    float GetTotalHeight() const
    {
        return totalHeight_;
    }

    float GetPrevTotalHeight() const
    {
        return prevTotalHeight_;
    }

    ListPosMapUpdate CheckPosMapUpdateRule();

    void UpdatePosMapStart(float delta, float& listCurrentPos, float space,
        int32_t startIndex, float startPos, bool groupAtStart);

    void UpdatePosMapEnd(int32_t prevEndIndex, float space, bool groupAtEnd);

    void CalculateUINode(RefPtr<UINode> node);

    std::optional<bool> GetLazyForEachChildIsGroup(RefPtr<UINode> node);

    void CalculateLazyForEachNode(RefPtr<UINode> node);

    void CalculateFrameNode(RefPtr<FrameNode> frameNode);

    void CalculateListItemNode();

    void CalculateGroupNode();

    void PosMapRecalculate(LayoutWrapper* layoutWrapper);

    void GroupPosMapRecalculate();

    virtual void UpdatePosMap(LayoutWrapper* layoutWrapper, int32_t lanes, float space,
        RefPtr<ListChildrenMainSize>& childrenSize);

    void UpdateGroupPosMap(int32_t totalCount, int32_t lanes, float space,
        RefPtr<ListChildrenMainSize>& childrenSize, float headerSize, float footerSize);

    void UpdateTotalCount(int32_t totalCount);

    float GetPos(int32_t index, float offset = 0.0f)
    {
        return posMap_[index].mainPos - offset;
    }

    float GetGroupLayoutOffset(int32_t startIndex, float startPos)
    {
        return posMap_[startIndex].mainPos - startPos;
    }

    ListPositionInfo GetPositionInfo(int32_t index) const;

    std::pair<int32_t, float> GetStartIndexAndPos() const;

    std::pair<int32_t, float> GetEndIndexAndPos() const;

    void OptimizeBeforeMeasure(int32_t& beginIndex, float& beginPos, const float offset, const float contentSize);

    void SetChainOffsetCallback(std::function<float(int32_t)> func)
    {
        chainOffsetFunc_ = std::move(func);
    }

    int32_t GetRowStartIndex(const int32_t input);

    int32_t GetRowEndIndex(const int32_t input);

    float GetRowHeight(int32_t input);

    std::pair<int32_t, float> GetRowEndIndexAndHeight(const int32_t input);

    void ReversePosMap();
protected:
    RefPtr<ListChildrenMainSize> childrenSize_;
    ListChangeFlag dirty_ = LIST_NO_CHANGE;
    int32_t totalItemCount_ = 0;
    float space_ = 0.0f;
    int32_t lanes_ = -1;

private:
    std::map<int32_t, ListPositionInfo> posMap_;
    std::function<float(int32_t)> chainOffsetFunc_;
    int32_t curLine_ = 0;
    int32_t curIndex_ = 0;
    float totalHeight_ = 0.0f;
    float prevTotalHeight_ = 0.0f;
    float curRowHeight_ = 0.0f;
    float headerSize_ = 0.0f;
    float footerSize_ = 0.0f;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LIST_LIST_POSITION_MAP_H
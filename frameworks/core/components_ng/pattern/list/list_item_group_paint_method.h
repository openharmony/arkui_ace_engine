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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_PAINT_METHOD_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_PAINT_METHOD_H

#include "base/geometry/ng/size_t.h"
#include "base/memory/ace_type.h"
#include "base/memory/referenced.h"
#include "base/utils/macros.h"
#include "base/utils/utils.h"
#include "core/components_ng/render/divider_painter.h"
#include "core/components_ng/render/node_paint_method.h"
#include "core/components_ng/pattern/list/list_item_group_layout_algorithm.h"
#include "core/components_ng/pattern/list/list_item_group_pattern.h"

namespace OHOS::Ace::NG {
struct DividerGroupInfo {
    int32_t lanes = 1;
    float crossSize = 0.0f;
    float mainPadding = 0.0f;
    float crossPadding = 0.0f;
    float constrainStrokeWidth = 0.0f;
    float halfSpaceWidth = 0.0f;
    float startMargin = 0.0f;
    float endMargin = 0.0f;
};

class ACE_EXPORT ListItemGroupPaintMethod : public NodePaintMethod {
    DECLARE_ACE_TYPE(ListItemGroupPaintMethod, NodePaintMethod)
public:
    ListItemGroupPaintMethod(const V2::ItemDivider& divider, const ListItemGroupPaintInfo& listItemGroupPaintInfo,
        ListItemGroupLayoutAlgorithm::PositionMap& itemPosition,
        ListItemGroupLayoutAlgorithm::PositionMap& cachedItemPosition,
        const std::set<int32_t>& pressedItem)
        : divider_(divider), itemPosition_(itemPosition)
    {
        vertical_ = listItemGroupPaintInfo.vertical;
        lanes_ = listItemGroupPaintInfo.lanes;
        spaceWidth_ = listItemGroupPaintInfo.spaceWidth;
        laneGutter_ = listItemGroupPaintInfo.laneGutter;
        totalItemCount_ = listItemGroupPaintInfo.totalItemCount;
        layoutDirection_ = listItemGroupPaintInfo.layoutDirection;
        mainSize_ = listItemGroupPaintInfo.mainSize;
        for (auto& [index, pos] : cachedItemPosition) {
            itemPosition_[index] = pos;
        }
        if (!pressedItem.empty()) {
            for (auto& child : itemPosition_) {
                if (pressedItem.find(child.second.id) != pressedItem.end()) {
                    child.second.isPressed = true;
                }
            }
        }
    }
    ~ListItemGroupPaintMethod() override = default;

    CanvasDrawFunction GetContentDrawFunction(PaintWrapper* paintWrapper) override;

    void PaintDivider(PaintWrapper* paintWrapper, RSCanvas& canvas);

    void DrawDivider(int32_t index, int32_t laneIdx, const DividerGroupInfo& info,
        const DividerPainter& dividerPainter, RSCanvas& canvas);

    void DrawLastLineDivider(int32_t index, int32_t laneIdx, const DividerGroupInfo& info,
        const DividerPainter& dividerPainter, RSCanvas& canvas);

    void UpdateDividerList(const DividerGroupInfo& info, const DividerPainter& dividerPainter, RSCanvas& canvas);

private:
    V2::ItemDivider divider_;
    bool vertical_ = false;
    int32_t lanes_ = 1;
    float spaceWidth_ = 0.0f;
    float laneGutter_ = 0.0f;
    float fSpacingTotal_ = 0.0f;
    ListItemGroupLayoutAlgorithm::PositionMap itemPosition_;
    int32_t totalItemCount_ = 0;
    TextDirection layoutDirection_ = TextDirection::LTR;
    float mainSize_ = 0.0f;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_PAINT_METHOD_H
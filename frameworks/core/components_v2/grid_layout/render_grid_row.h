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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_ROW_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_ROW_H

#include "core/components_v2/grid_layout/grid_container_util_class.h"
#include "core/pipeline/base/component.h"
#include "core/pipeline/base/render_node.h"

namespace OHOS::Ace::V2 {

class RenderGridRow : public RenderNode {
    DECLARE_ACE_TYPE(RenderGridRow, RenderNode);

struct NewLineOffset {
    bool isValid = false;
    int32_t newLineCount = 0;
    int32_t offset = 0;
};

public:
    ~RenderGridRow() override = default;

    static RefPtr<RenderNode> Create();
    static void ParseNewLineForLargeOffset(int32_t childSpan, int32_t childOffset, int32_t restColumnNum,
        int32_t totalColumnNum, NewLineOffset& newLineOffset);

    void Update(const RefPtr<Component>& component) override;
    void PerformLayout() override;
    void LayoutEachChild(double childWidthLimit, double childHeightLimit, double xGetter, GridSizeType sizeType,
        int32_t columnNum);

    void CalculateOffsetOfNewline(const RefPtr<RenderNode>& node, int32_t currentChildSpan, int32_t restColumnNum,
        int32_t totalColumnNum, GridSizeType sizeType, NewLineOffset& newLineOffset) const;
    inline int32_t GetRelativeOffset(const RefPtr<RenderNode>& node, GridSizeType sizeType) const;
    inline int32_t GetGridColSpan(const RefPtr<RenderNode>& node, GridSizeType sizeType) const;
    void FindGridColChild(RefPtr<RenderNode>& node) const;
    GridSizeType GetCurrentSizeType()
    {
        return currentSizeType_;
    }

    GridRowDirection GetDirection() const;
    RefPtr<BreakPoints> GetBreakPoints() const;
    int32_t GetTotalCol() const;
    std::pair<double, double> GetGutter() const;

private:
    RefPtr<Component> gridRowComponent_;
    std::list<RefPtr<RenderNode>> gridColChildren_;
    GridSizeType currentSizeType_ = GridSizeType::UNDEFINED;
};
} // namespace OHOS::Ace::V2
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_V2_GRID_LAYOUT_RENDER_GRID_ROW_H
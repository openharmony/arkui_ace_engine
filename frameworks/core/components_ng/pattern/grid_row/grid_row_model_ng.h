/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_NG_H

#include "core/components_ng/pattern/grid_row/grid_row_model.h"

namespace OHOS::Ace::NG {

constexpr int32_t DEFAULT_COLUMN_NUMBER = 12;

class FrameNode;

class ACE_EXPORT GridRowModelNG : public GridRowModel {
public:
    void Create() override;
    void Create(const RefPtr<V2::GridContainerSize>& col, const RefPtr<V2::Gutter>& gutter,
        const RefPtr<V2::BreakPoints>& breakpoints, V2::GridRowDirection direction) override;
    void SetOnBreakPointChange(std::function<void(const std::string)>&& onChange) override;
    void SetAlignItems(FlexAlign alignItem) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetAlignItems(FrameNode* frameNode, FlexAlign  alignItem);
    static void SetGutter(FrameNode* frameNode, const RefPtr<V2::Gutter>& gutter);
    static void SetColumns(FrameNode* frameNode, const RefPtr<V2::GridContainerSize>& col);
    static void SetBreakpoints(FrameNode* frameNode, const RefPtr<V2::BreakPoints>& breakpoints);
    static void SetDirection(FrameNode* frameNode, const V2::GridRowDirection direction);
    static void SetOnBreakPointChange(FrameNode* frameNode,
        std::function<void(const std::string)>&& onBreakPointChange);
};
} // namespace OHOS::Ace::NG

#endif
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_COL_MODEL_NG_H

#include "core/components_ng/pattern/grid_col/grid_col_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT GridColModelNG : public GridColModel {
public:
    void Create() override;
    void Create(const V2::GridContainerSize& span, const V2::GridContainerSize& offset,
        const V2::GridContainerSize& order) override;
    void SetSpan(const V2::GridContainerSize& span) override;
    void SetOffset(const V2::GridContainerSize& offset) override;
    void SetOrder(const V2::GridContainerSize& order) override;
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSpan(FrameNode* frameNode, const V2::GridContainerSize& span);
    static void SetOffset(FrameNode* frameNode, const V2::GridContainerSize& offset);
    static void SetOrder(FrameNode* frameNode, const V2::GridContainerSize& order);
};
} // namespace OHOS::Ace::NG

#endif
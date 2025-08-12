/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_NG_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_GRID_ROW_MODEL_NG_STATIC_H

#include "core/components_ng/pattern/grid_row/grid_row_model.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT GridRowModelNGStatic : public GridRowModel {
public:
    static void SetAlignItems(FrameNode* frameNode, const std::optional<FlexAlign>& alignItem);
    static void SetDirection(FrameNode* frameNode, const std::optional<V2::GridRowDirection>& direction);
};
} // namespace OHOS::Ace::NG

#endif
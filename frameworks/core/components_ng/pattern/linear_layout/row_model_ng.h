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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H

#include "base/utils/macros.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_layout/row_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT RowModelNG : public RowModel {
public:
    void Create(const std::optional<Dimension>& space, AlignDeclaration*, const std::string& tag) override;
    void SetAlignItems(FlexAlign flexAlign) override;
    void SetJustifyContent(FlexAlign flexAlign) override;
    void SetIsReverse(bool isReverse) override;
    void CreateWithWrap() override {}
    static void SetSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
    static void SetJustifyContent(FrameNode* frameNode, FlexAlign flexAlign);
    static void SetAlignItems(FrameNode* frameNode, FlexAlign flexAlign);
    static void SetIsReverse(FrameNode* frameNode, bool isReverse);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static FlexAlign GetJustifyContent(FrameNode* frameNode);
    static FlexAlign GetAlignItems(FrameNode* frameNode);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_LINEAR_LAYOUT_ROW_MODEL_NG_H

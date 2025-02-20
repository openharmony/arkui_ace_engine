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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_NG_H

#include "core/components_ng/pattern/flex/flex_model.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT FlexModelNG : public FlexModel {
public:
    void CreateFlexRow() override;

    void CreateWrap() override;

    void SetDirection(FlexDirection direction) override;
    void SetWrapDirection(WrapDirection direction) override;

    void SetMainAxisAlign(FlexAlign align) override;
    void SetWrapMainAlignment(WrapAlignment value) override;

    void SetCrossAxisAlign(FlexAlign align) override;
    void SetWrapCrossAlignment(WrapAlignment value) override;

    void SetAlignItems(int32_t value) override;
    void SetWrapAlignment(WrapAlignment value) override;
    void SetMainSpace(const std::optional<Dimension>& space) override;
    void SetCrossSpace(const std::optional<Dimension>& space) override;

    void SetHasHeight() override {};
    void SetHasWidth() override {};
    void SetFlexWidth() override {};
    void SetFlexHeight() override {};

    void SetJustifyContent(int32_t value) override;

    void SetAlignContent(int32_t value) override;
    void SetWidthLayoutPolicy(uint8_t widthLayoutPolicy) override;
    void SetHeightLayoutPolicy(uint8_t heightLayoutPolicy) override;

    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetFlexRow(FrameNode* frameNode);
    static void SetFlexWrap(FrameNode* frameNode);
    static void SetFlexDirection(FrameNode* frameNode, FlexDirection value);
    static void SetFlexWrapDirection(FrameNode* frameNode, WrapDirection value);
    static void SetFlexJustifyContent(FrameNode* frameNode, int32_t value);
    static void SetFlexAlignItems(FrameNode* frameNode, int32_t value);
    static void SetFlexAlignContent(FrameNode* frameNode, int32_t value);
    static void SetWidthLayoutPolicy(FrameNode* frameNode, uint8_t widthLayoutPolicy);
    static void SetHeightLayoutPolicy(FrameNode* frameNode, uint8_t heightLayoutPolicy);

    static int GetFlexWrap(FrameNode* frameNode);
    static int GetFlexDirection(FrameNode* frameNode);
    static int GetFlexJustifyContent(FrameNode* frameNode);
    static int GetFlexAlignItems(FrameNode* frameNode);
    static int GetFlexAlignContent(FrameNode* frameNode);
    static void SetMainSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
    static void SetCrossSpace(FrameNode* frameNode, const std::optional<Dimension>& space);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_FLEX_FLEX_MODEL_NG_H

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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_GROUP_MODEL_NG_H

#include <functional>
#include <memory>

#include "base/geometry/axis.h"
#include "base/geometry/dimension.h"
#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_item_group_model.h"
#include "core/components_v2/list/list_properties.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ListItemGroupModelNG : public ListItemGroupModel {
public:
    void Create(V2::ListItemGroupStyle listItemGroupStyle) override;
    void SetSpace(const Dimension& space) override;
    void SetDivider(const V2::ItemDivider& divider) override;
    void SetHeader(std::function<void()>&& header) override;
    void SetFooter(std::function<void()>&& footer) override;
    RefPtr<ListChildrenMainSize> GetOrCreateListChildrenMainSize() override;
    void SetHeaderComponent(const RefPtr<NG::UINode>& headerComponent) override;
    void SetFooterComponent(const RefPtr<NG::UINode>& footerComponent) override;
    void RemoveHeader() override;
    void RemoveFooter() override;
    void ParseResObjDividerStrokeWidth(const RefPtr<ResourceObject>& resObj) override;
    void ParseResObjDividerColor(const RefPtr<ResourceObject>& resObj) override;
    void ParseResObjDividerStartMargin(const RefPtr<ResourceObject>& resObj) override;
    void ParseResObjDividerEndMargin(const RefPtr<ResourceObject>& resObj) override;
    void SetDividerColorByUser(bool isByUser) override;

    static void SetDivider(FrameNode* frameNode, const V2::ItemDivider& divider);
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetHeader(FrameNode* frameNode, FrameNode* headerNode);
    static void SetFooter(FrameNode* frameNode, FrameNode* footerNode);
    static void SetListChildrenMainSize(
        FrameNode* frameNode, float defaultSize, const std::vector<float>& mainSize);
    static void ResetListChildrenMainSize(FrameNode* frameNode);
    static V2::ItemDivider GetDivider(FrameNode* frameNode);
    static void SetSpace(FrameNode* frameNode, const Dimension& space);
    static void SetStyle(FrameNode* frameNode, V2::ListItemGroupStyle style);
    static void RemoveHeader(FrameNode* frameNode);
    static void RemoveFooter(FrameNode* frameNode);
    static bool HasFooter(FrameNode* frameNode);
    static bool HasHeader(FrameNode* frameNode);
    static void ParseResObjDividerStrokeWidth(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void ParseResObjDividerColor(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void ParseResObjDividerStartMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void ParseResObjDividerEndMargin(FrameNode* frameNode, const RefPtr<ResourceObject>& resObj);
    static void SetDividerColorByUser(FrameNode* frameNode, bool isByUser);
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_ITEM_MODEL_H

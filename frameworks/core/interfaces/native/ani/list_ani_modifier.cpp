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
#include "list_ani_modifier.h"

#include "base/log/log.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/list/list_model_static.h"
#include "core/components_ng/pattern/list/list_item_group_model_static.h"
#include "frameworks/core/interfaces/native/ani/frame_node_peer_impl.h"

namespace OHOS::Ace::NG {
bool UpdateDefaultSizeAndGetNeedSync(ArkUINodeHandle node, double defaultSize)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    const auto& nodeTag = frameNode->GetHostTag();
    auto listChildrenMainSize = V2::LIST_ETS_TAG == nodeTag ?
        NG::ListModelStatic::GetOrCreateListChildrenMainSize(frameNode) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    CHECK_NULL_RETURN(listChildrenMainSize, false);
    listChildrenMainSize->UpdateDefaultSize(Dimension(defaultSize, DimensionUnit::VP).ConvertToPx());
    return listChildrenMainSize->NeedSync();
}

void SyncChildrenSize(ArkUINodeHandle node, double size)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    auto listChildrenMainSize = V2::LIST_ETS_TAG == nodeTag ?
        NG::ListModelStatic::GetOrCreateListChildrenMainSize(frameNode) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    CHECK_NULL_VOID(listChildrenMainSize);
    float parseSize = Negative(size) ? -1.0f : Dimension(size, DimensionUnit::VP).ConvertToPx();
    listChildrenMainSize->SyncChildrenSize(parseSize);
}

void NotifyChange(ArkUINodeHandle node, ArkUI_Int32 start,
    ArkUI_Int32 deleteCount, std::vector<float>& newSizeArr)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    auto listChildrenMainSize = V2::LIST_ETS_TAG == nodeTag ?
        NG::ListModelStatic::GetOrCreateListChildrenMainSize(frameNode) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    CHECK_NULL_VOID(listChildrenMainSize);
    for (float& size : newSizeArr) {
        if (Negative(size)) {
            size = -1.0f;
        } else {
            size = Dimension(size, DimensionUnit::VP).ConvertToPx();
        }
    }
    listChildrenMainSize->ChangeData(start, deleteCount, newSizeArr);
}

void ResizeChildrenSize(ArkUINodeHandle node, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    auto listChildrenMainSize = V2::LIST_ETS_TAG == nodeTag ?
        NG::ListModelStatic::GetOrCreateListChildrenMainSize(frameNode) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    CHECK_NULL_VOID(listChildrenMainSize);
    listChildrenMainSize->ResizeChildrenSize(size);
}

void SyncChildrenSizeOver(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    auto listChildrenMainSize = V2::LIST_ETS_TAG == nodeTag ?
        NG::ListModelStatic::GetOrCreateListChildrenMainSize(frameNode) :
        NG::ListItemGroupModelStatic::GetOrCreateListChildrenMainSize(frameNode);
    CHECK_NULL_VOID(listChildrenMainSize);
    listChildrenMainSize->SyncChildrenSizeOver();
}

void ResetListChildrenMainSize(ArkUINodeHandle node)
{
    auto *frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto& nodeTag = frameNode->GetHostTag();
    V2::LIST_ETS_TAG == nodeTag ? NG::ListModelStatic::ResetListChildrenMainSize(frameNode)
                                : NG::ListItemGroupModelStatic::ResetListChildrenMainSize(frameNode);
}

const ArkUIAniListModifier* GetArkUIAniListModifier()
{
    static const ArkUIAniListModifier impl = {
        .updateDefaultSizeAndGetNeedSync = OHOS::Ace::NG::UpdateDefaultSizeAndGetNeedSync,
        .syncChildrenSize = OHOS::Ace::NG::SyncChildrenSize,
        .notifyChange = OHOS::Ace::NG::NotifyChange,
        .resizeChildrenSize = OHOS::Ace::NG::ResizeChildrenSize,
        .syncChildrenSizeOver = OHOS::Ace::NG::SyncChildrenSizeOver,
        .resetListChildrenMainSize = OHOS::Ace::NG::ResetListChildrenMainSize,
    };
    return &impl;
}
} // namespace OHOS::Ace::NG

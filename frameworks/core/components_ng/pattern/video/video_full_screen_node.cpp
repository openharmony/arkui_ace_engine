/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/video/video_full_screen_node.h"

#include "core/components_ng/pattern/image/image_pattern.h"
#include "core/components_ng/pattern/linear_layout/linear_layout_pattern.h"
#include "core/components_ng/pattern/video/video_full_screen_pattern.h"

namespace OHOS::Ace::NG {
void VideoFullScreenNode::InitVideoFullScreenNode(const RefPtr<VideoNode>& video)
{
    CHECK_NULL_VOID(video);
    if (video->HasMediaColumnNode()) {
        auto mediaColumnId = GetMediaColumnId();
        auto mediaColumNode = FrameNode::GetOrCreateFrameNode(
            V2::COLUMN_ETS_TAG, mediaColumnId, []() { return AceType::MakeRefPtr<LinearLayoutPattern>(true); });
        CHECK_NULL_VOID(mediaColumNode);
        AddChild(mediaColumNode);
    }
    if (video->HasPreviewImageNode()) {
        int32_t imageId = ElementRegister::GetInstance()->MakeUniqueId();
        auto previewNode = FrameNode::GetOrCreateFrameNode(
            V2::IMAGE_ETS_TAG, imageId, []() { return AceType::MakeRefPtr<ImagePattern>(); });
        CHECK_NULL_VOID(previewNode);
        AddChild(previewNode);
    }
    if (video->HasControllerRowNode()) {
        int32_t controlRowId = GetControllerRowId();
        auto fullScreenPattern = AceType::DynamicCast<VideoFullScreenPattern>(GetPattern());
        CHECK_NULL_VOID(fullScreenPattern);
        auto controlRowNode = fullScreenPattern->CreateControlBar(controlRowId);
        CHECK_NULL_VOID(controlRowNode);
        AddChild(controlRowNode);
    }
}

RefPtr<VideoFullScreenNode> VideoFullScreenNode::CreateFullScreenNode(
    const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern)
{
    auto fullScreenNode = AceType::MakeRefPtr<VideoFullScreenNode>(tag, nodeId, pattern, false);
    ElementRegister::GetInstance()->AddUINode(fullScreenNode);
    fullScreenNode->InitializePatternAndContext();
    return fullScreenNode;
}
} // namespace OHOS::Ace::NG
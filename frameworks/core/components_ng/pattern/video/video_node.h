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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_NODE_H

#include <optional>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_pattern.h"

namespace OHOS::Ace::NG {

constexpr int32_t PREVIEW_IMAGE_INDEX = 1;
constexpr int32_t CONTROLLER_ROW_INDEX = 2;
constexpr int32_t MEDIA_COLUMN_INDEX = 0;

class ACE_EXPORT VideoNode : public FrameNode {
    DECLARE_ACE_TYPE(VideoNode, FrameNode);

public:
    VideoNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~VideoNode() override = default;

    bool HasControllerRowNode() const
    {
        return controllerRowId_.has_value();
    }

    bool HasPreviewImageNode() const
    {
        return previewImageId_.has_value();
    }

    bool HasMediaColumnNode() const
    {
        return mediaColumnId_.has_value();
    }

    int32_t GetControllerRowId()
    {
        if (!controllerRowId_.has_value()) {
            controllerRowId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return controllerRowId_.value();
    }

    int32_t GetPreviewImageId()
    {
        if (!previewImageId_.has_value()) {
            previewImageId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return previewImageId_.value();
    }

    int32_t GetMediaColumnId()
    {
        if (!mediaColumnId_.has_value()) {
            mediaColumnId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return mediaColumnId_.value();
    }

    // Get the preview image node, please check null first.
    RefPtr<UINode> GetPreviewImage()
    {
        // If the index >= size, it will return null.
        return GetChildAtIndex(PREVIEW_IMAGE_INDEX);
    }

    // Get the controller row node, please check null first.
    RefPtr<UINode> GetControllerRow()
    {
        // If the index >= size, it will return null.
        return GetChildAtIndex(CONTROLLER_ROW_INDEX);
    }

    RefPtr<UINode> GetMediaColumn()
    {
        return GetChildAtIndex(MEDIA_COLUMN_INDEX);
    }

    static RefPtr<VideoNode> GetOrCreateVideoNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

private:
    std::optional<int32_t> previewImageId_;
    std::optional<int32_t> controllerRowId_;
    std::optional<int32_t> mediaColumnId_;
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_NODE_H

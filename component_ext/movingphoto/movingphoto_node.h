/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NODE_H
#define COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NODE_H

#include "movingphoto_pattern.h"
#include "core/components_ng/base/frame_node.h"

namespace OHOS::Ace::NG {

constexpr int32_t VIDEO_NODE_INDEX = 0;
constexpr int32_t IMAGE_NODE_INDEX = 1;

class ACE_EXPORT MovingPhotoNode : public FrameNode {
    DECLARE_ACE_TYPE(MovingPhotoNode, FrameNode);

public:
    MovingPhotoNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        : FrameNode(tag, nodeId, pattern, isRoot)
    {}
    ~MovingPhotoNode() override = default;

    static RefPtr<MovingPhotoNode> GetOrCreateMovingPhotoNode(
        const std::string& tag, int32_t nodeId, const std::function<RefPtr<Pattern>(void)>& patternCreator);

    int32_t GetImageId()
    {
        if (!imageId_.has_value()) {
            imageId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return imageId_.value();
    }

    RefPtr<UINode> GetImage()
    {
        return GetChildAtIndex(IMAGE_NODE_INDEX);
    }

    bool HasImageNode()
    {
        return imageId_.has_value();
    }

    int32_t GetVideoId()
    {
        if (!videoId_.has_value()) {
            videoId_ = ElementRegister::GetInstance()->MakeUniqueId();
        }
        return videoId_.value();
    }

    RefPtr<UINode> GetVideo()
    {
        return GetChildAtIndex(VIDEO_NODE_INDEX);
    }

    bool HasVideoNode()
    {
        return videoId_.has_value();
    }

private:
    std::optional<int32_t> imageId_;
    std::optional<int32_t> videoId_;
};
} // namespace OHOS::Ace::NG
#endif // COMPONENT_EXT_MOVING_PHOTO_MOVING_PHOTO_NODE_H
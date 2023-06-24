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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_FULL_SCREEN_NODE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_FULL_SCREEN_NODE_H

#include <optional>

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_node.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT VideoFullScreenNode : public VideoNode {
    DECLARE_ACE_TYPE(VideoFullScreenNode, VideoNode);

public:
    VideoFullScreenNode(const std::string& tag, int32_t nodeId, const RefPtr<Pattern>& pattern, bool isRoot = false)
        :VideoNode(tag, nodeId, pattern, isRoot) {}
    
    ~VideoFullScreenNode() override = default;

    void InitVideoFullScreenNode(const RefPtr<VideoNode>& videoNode);

    static RefPtr<VideoFullScreenNode> CreateFullScreenNode(const std::string& tag, int32_t nodeId,
        const RefPtr<Pattern>& pattern);

private:
    void InitVideoParam(const RefPtr<VideoNode>& video);
};
}
#endif
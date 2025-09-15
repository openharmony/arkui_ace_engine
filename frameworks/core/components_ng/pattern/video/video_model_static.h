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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_MODEL_STATIC_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_MODEL_STATIC_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT VideoModelStatic {
public:
    static RefPtr<FrameNode> CreateFrameNode(int32_t nodeId);
    static void SetSrc(FrameNode* frameNode,
        const std::string& src, const std::string& bundleName, const std::string& moduleName);
    static void SetShowFirstFrame(FrameNode* frameNode, bool showFirstFrame);
    static void SetProgressRate(FrameNode* frameNode, double progressRate);
    static void SetPosterSourceInfo(FrameNode* frameNode, const ImageSourceInfo& posterSourceInfo);
    static void SetVideoController(FrameNode* frameNode, const RefPtr<VideoControllerV2>& videoController);
    static void SetObjectFit(FrameNode* frameNode, std::optional<ImageFit> objectFit);
    static void SetSurfaceBackgroundColor(FrameNode* frameNode, const std::optional<Color>& color);
    static void EnableAnalyzer(FrameNode* frameNode, bool enable);
    static void SetOnStart(FrameNode* frameNode, VideoEventFunc&& onStart);
    static void SetOnPause(FrameNode* frameNode, VideoEventFunc&& onPause);
    static void SetOnFinish(FrameNode* frameNode, VideoEventFunc&& onFinish);
    static void SetOnFullScreenChange(FrameNode* frameNode, VideoEventFunc&& onFullScreenChange);
    static void SetOnPrepared(FrameNode* frameNode, VideoEventFunc&& onPrepared);
    static void SetOnSeeking(FrameNode* frameNode, VideoEventFunc&& onSeeking);
    static void SetOnSeeked(FrameNode* frameNode, VideoEventFunc&& onSeeked);
    static void SetOnUpdate(FrameNode* frameNode, VideoEventFunc&& onUpdate);
    static void SetOnError(FrameNode* frameNode, VideoEventFunc&& onError);
    static void SetOnStop(FrameNode* frameNode, VideoEventFunc&& onStop);
    static void SetPosterSourceByPixelMap(FrameNode* frameNode, RefPtr<PixelMap>& pixMap);
};
} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_VIDEO_VIDEO_MODEL_STATIC_H

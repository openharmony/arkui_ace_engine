/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_NG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_NG_H

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/video/video_model.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT VideoModelNG : public OHOS::Ace::VideoModel {
public:
    void Create(const RefPtr<VideoControllerV2>& videoController) override;
    void SetSrc(const std::string& src, const std::string& bundleName, const std::string& moduleName) override;
    void SetProgressRate(double progressRate) override;
    void SetPosterSourceInfo(const std::string& posterUrl, const std::string &bundleName,
        const std::string &moduleName) override;
    void SetPosterSourceByPixelMap(RefPtr<PixelMap>& pixMap) override;
    void SetMuted(bool muted) override;
    void SetAutoPlay(bool autoPlay) override;
    void SetControls(bool controls) override;
    void SetObjectFit(ImageFit objectFit) override;
    void SetLoop(bool loop) override;
    void SetSurfaceBackgroundColor(Color color) override;

    void SetOnStart(VideoEventFunc&& onStart) override;
    void SetOnPause(VideoEventFunc&& onPause) override;
    void SetOnFinish(VideoEventFunc&& onFinish) override;
    void SetOnError(VideoEventFunc&& onError) override;
    void SetOnPrepared(VideoEventFunc&& onPrepared) override;
    void SetOnSeeking(VideoEventFunc&& onSeeking) override;
    void SetOnSeeked(VideoEventFunc&& onSeeked) override;
    void SetOnUpdate(VideoEventFunc&& onUpdate) override;
    void SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange) override;
    void SetOnStop(VideoEventFunc&& onStop) override;
    void EnableAnalyzer(bool enable) override;
    void SetImageAnalyzerConfig(void* config) override;
    void SetImageAIOptions(void *options) override;
    static void SetAutoPlay(FrameNode* frameNode, bool autoPlay);
    static void SetControls(FrameNode* frameNode, bool controls);
    static void SetObjectFit(FrameNode* frameNode, ImageFit objectFit);
    static void SetLoop(FrameNode* frameNode, bool loop);
    static void SetMuted(FrameNode* frameNode, bool muted);
private:
    void AddDragFrameNodeToManager() const;
};

} // namespace OHOS::Ace::NG
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_NG_H

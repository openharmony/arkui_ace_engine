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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_H

#include <mutex>

#include "base/image/pixel_map.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/video/video_controller_v2.h"

namespace OHOS::Ace {
using VideoEventFunc = std::function<void(const std::string&)>;
class ACE_FORCE_EXPORT VideoModel {
public:
    static VideoModel* GetInstance();
    virtual ~VideoModel() = default;

    virtual void Create(const RefPtr<VideoControllerV2>& videoController) = 0;
    virtual void SetSrc(const std::string& src, const std::string& bundleName, const std::string& moduleName) = 0;
    virtual void SetShowFirstFrame(bool showFirstFrame) {}
    virtual void SetProgressRate(double progressRate) = 0;
    virtual void SetPosterSourceInfo(const std::string& posterUrl, const std::string &bundleName,
        const std::string &moduleName) = 0;
    virtual void SetPosterSourceByPixelMap(RefPtr<PixelMap>& pixMap) = 0;
    virtual void SetMuted(bool muted) = 0;
    virtual void SetAutoPlay(bool autoPlay) = 0;
    virtual void SetControls(bool controls) = 0;
    virtual void SetObjectFit(ImageFit objectFit) = 0;
    virtual void SetLoop(bool loop) = 0;
    virtual void SetSurfaceBackgroundColor(Color color) {}
    virtual void SetShortcutKeyEnabled(bool isEnableShortcutKey) {}

    virtual void SetOnStart(VideoEventFunc&& onStart) = 0;
    virtual void SetOnPause(VideoEventFunc&& onPause) = 0;
    virtual void SetOnFinish(VideoEventFunc&& onFinish) = 0;
    virtual void SetOnError(VideoEventFunc&& onError) = 0;
    virtual void SetOnPrepared(VideoEventFunc&& onPrepared) = 0;
    virtual void SetOnSeeking(VideoEventFunc&& onSeeking) = 0;
    virtual void SetOnSeeked(VideoEventFunc&& onSeeked) = 0;
    virtual void SetOnUpdate(VideoEventFunc&& onUpdate) = 0;
    virtual void SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange) = 0;
    virtual void SetOnStop(VideoEventFunc&& onStop) {};
    virtual void EnableAnalyzer(bool enable) {}
    virtual void SetImageAnalyzerConfig(void* config) {}
    virtual void SetImageAIOptions(void* options) {}
};
} // namespace OHOS::Ace
#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_MODEL_H

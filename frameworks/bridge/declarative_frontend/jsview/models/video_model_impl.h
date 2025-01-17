/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIDEO_MODEL_IMPL_H
#define FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIDEO_MODEL_IMPL_H

#include "core/components_ng/pattern/video/video_model.h"

namespace OHOS::Ace::Framework {

class VideoModelImpl : public OHOS::Ace::VideoModel {
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

    void SetOnStart(VideoEventFunc&& onStart) override;
    void SetOnPause(VideoEventFunc&& onPause) override;
    void SetOnFinish(VideoEventFunc&& onFinish) override;
    void SetOnError(VideoEventFunc&& onError) override;
    void SetOnPrepared(VideoEventFunc&& onPrepared) override;
    void SetOnSeeking(VideoEventFunc&& onSeeking) override;
    void SetOnSeeked(VideoEventFunc&& onSeeked) override;
    void SetOnUpdate(VideoEventFunc&& onUpdate) override;
    void SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange) override;
};

} // namespace OHOS::Ace::Framework
#endif // FRAMEWORKS_BRIDGE_DECLARATIVE_FRONTEND_JS_VIEW_MODELS_VIDEO_MODEL_IMPL_H

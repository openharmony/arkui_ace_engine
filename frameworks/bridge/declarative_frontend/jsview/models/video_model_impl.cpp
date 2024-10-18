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

#include "bridge/declarative_frontend/jsview/models/video_model_impl.h"

#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/components/video/video_component_v2.h"

namespace OHOS::Ace::Framework {

void VideoModelImpl::Create(const RefPtr<VideoControllerV2>& videoController)
{
    auto* stack = ViewStackProcessor::GetInstance();
    auto videoComponent = AceType::MakeRefPtr<OHOS::Ace::VideoComponentV2>();
    videoComponent->SetSaveComponentEvent([videoComponent](std::unordered_map<std::string, RefPtr<Component>> map) {
        videoComponent->SetGestureComponentMap(std::move(map));
    });
    if (AceApplicationInfo::GetInstance().IsRightToLeft()) {
        videoComponent->SetTextDirection(TextDirection::RTL);
    }

    ViewStackProcessor::GetInstance()->ClaimElementId(videoComponent);
    ViewStackProcessor::GetInstance()->Push(videoComponent);

    if (videoController) {
        videoComponent->SetVideoControllerV2(videoController);
    }
    stack->GetFlexItemComponent();
}

void VideoModelImpl::SetSrc(const std::string& src, const std::string& /* bundleName */,
    const std::string& /*moduleName */)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetSrc(src);
}

void VideoModelImpl::SetProgressRate(double progressRate)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetSpeed(static_cast<float>(progressRate));
}

void VideoModelImpl::SetPosterSourceInfo(const std::string& posterUrl, const std::string &bundleName,
    const std::string &moduleName)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetPoster(posterUrl);
}

void VideoModelImpl::SetPosterSourceByPixelMap(RefPtr<PixelMap>& pixMap)
{
    LOGW("Pixelmap is not supported.");
}

void VideoModelImpl::SetMuted(bool muted)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetMute(muted);
}

void VideoModelImpl::SetAutoPlay(bool autoPlay)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetAutoPlay(autoPlay);
}

void VideoModelImpl::SetControls(bool controls)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetNeedControls(controls);
}

void VideoModelImpl::SetObjectFit(ImageFit objectFit)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetFit(objectFit);
}

void VideoModelImpl::SetLoop(bool loop)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetLoop(loop);
}

void VideoModelImpl::SetOnStart(VideoEventFunc&& onStart)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetStartEventId(
        EventMarker([func = std::move(onStart)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnPause(VideoEventFunc&& onPause)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetPauseEventId(
        EventMarker([func = std::move(onPause)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnFinish(VideoEventFunc&& onFinish)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetFinishEventId(
        EventMarker([func = std::move(onFinish)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnError(VideoEventFunc&& onError)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetErrorEventId(
        EventMarker([func = std::move(onError)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnPrepared(VideoEventFunc&& onPrepared)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetPreparedEventId(
        EventMarker([func = std::move(onPrepared)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnSeeking(VideoEventFunc&& onSeeking)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetSeekingEventId(
        EventMarker([func = std::move(onSeeking)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnSeeked(VideoEventFunc&& onSeeked)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetSeekedEventId(
        EventMarker([func = std::move(onSeeked)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnUpdate(VideoEventFunc&& onUpdate)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetTimeUpdateEventId(
        EventMarker([func = std::move(onUpdate)](const std::string& param) { func(param); }));
}

void VideoModelImpl::SetOnFullScreenChange(VideoEventFunc&& onFullScreenChange)
{
    auto videoComponent = AceType::DynamicCast<VideoComponentV2>(ViewStackProcessor::GetInstance()->GetMainComponent());
    CHECK_NULL_VOID(videoComponent);
    videoComponent->SetFullscreenChangeEventId(
        EventMarker([func = std::move(onFullScreenChange)](const std::string& param) { func(param); }));
}
} // namespace OHOS::Ace::Framework

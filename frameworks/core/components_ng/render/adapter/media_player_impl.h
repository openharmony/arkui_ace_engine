/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MEDIA_PLAYER_IMPL_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MEDIA_PLAYER_IMPL_H

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/video/resource/player.h"
#include "core/components_ng/render/media_player.h"
#include "core/components_ng/render/render_surface.h"

namespace OHOS::Ace::NG {
class MediaPlayerImpl : public MediaPlayer, public ExtSurfaceCallbackInterface {
    DECLARE_ACE_TYPE(MediaPlayerImpl, NG::MediaPlayer)
public:
    MediaPlayerImpl() = default;
    ~MediaPlayerImpl() override;

    void CreateMediaPlayer() override;
    void ResetMediaPlayer() override;
    bool IsMediaPlayerValid() override;
    void SetVolume(float leftVolume, float rightVolume) override;
    bool SetSource(const std::string& src, const std::string& bundleName, const std::string& moduleName) override;
    void SetRenderSurface(const RefPtr<RenderSurface>& renderSurface) override;
    void RegisterMediaPlayerEvent(PositionUpdatedEvent&& positionUpdatedEvent, StateChangedEvent&& stateChangedEvent,
        CommonEvent&& errorEvent, CommonEvent&& resolutionChangeEvent, CommonEvent&& startRenderFrameEvent) override;
    void RegisterTextureEvent(TextureRefreshEnVent&& textureRefreshEvent) override;
    int32_t GetDuration(int32_t& duration) override;
    int32_t GetVideoWidth() override;
    int32_t GetVideoHeight() override;
    int32_t SetLooping(bool loop) override;
    int32_t SetPlaybackSpeed(float speed) override;
    int32_t SetSurface() override;
    int32_t PrepareAsync() override;
    bool IsPlaying() override;
    int32_t Play() override;
    int32_t Pause() override;
    int32_t Stop() override;
    int32_t Seek(int32_t mSeconds, OHOS::Ace::SeekMode mode) override;
    int32_t FullScreenChange(bool isFullScreen) override;

    void ProcessSurfaceCreate() override;
    void ProcessSurfaceChange(int32_t width, int32_t height) override;
    void ProcessSurfaceDestroy() override {}
    void ProcessTextureRefresh(int32_t instanceId, int64_t textureId) override;

private:
    void InitListener();

    RefPtr<Player> player_;
    WeakPtr<RenderSurface> renderSurface_;
    PositionUpdatedEvent positionUpdateCallback_;
    StateChangedEvent stateChangeCallback_;
    CommonEvent errorCallback_;
    CommonEvent resolutionChangeCallback_;
    CommonEvent startRenderFrameCallback_;
    TextureRefreshEnVent textureRefreshCallback_;

    ACE_DISALLOW_COPY_AND_MOVE(MediaPlayerImpl);
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_RENDER_ADAPTER_MEDIA_PLAYER_IMPL_H

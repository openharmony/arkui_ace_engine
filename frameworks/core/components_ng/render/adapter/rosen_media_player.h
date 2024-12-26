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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MEDIA_PLAYER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MEDIA_PLAYER_H

#include "player.h"
#include "surface.h"
#include "window.h"

#include "base/memory/referenced.h"
#include "base/utils/noncopyable.h"
#include "core/components/video/media_player_callback.h"
#include "core/components_ng/render/adapter/rosen_render_surface.h"
#include "core/components_ng/render/media_player.h"

namespace OHOS::Ace::NG {
class RosenMediaPlayer : public MediaPlayer {
    DECLARE_ACE_TYPE(RosenMediaPlayer, NG::MediaPlayer)
public:
    RosenMediaPlayer() = default;
    ~RosenMediaPlayer() override;

    void CreateMediaPlayer() override;
    void ResetMediaPlayer() override;
    bool IsMediaPlayerValid() override;
    void SetVolume(float leftVolume, float rightVolume) override;
    void SetMediaMuted(int32_t type, bool isMuted) override;
    bool SetSource(const std::string& src, const std::string& bundleName, const std::string& moduleName) override;
    bool SetSourceByFd(int32_t fd) override;
    void SetRenderSurface(const RefPtr<RenderSurface>& renderSurface) override;
    void RegisterMediaPlayerEvent(PositionUpdatedEvent&& positionUpdatedEvent, StateChangedEvent&& stateChangedEvent,
        CommonEvent&& errorEvent, CommonEvent&& resolutionChangeEvent, CommonEvent&& startRenderFrameEvent) override;
    void RegisterMediaPlayerSeekDoneEvent(SeekDoneEvent&& seekDoneEvent) override;
    int32_t GetDuration(int32_t& duration) override;
    int32_t GetVideoWidth() override;
    int32_t GetVideoHeight() override;
    int32_t SetLooping(bool loop) override;
    int32_t SetPlaybackSpeed(float speed) override;
    int32_t SetSurface() override;
    int32_t SetRenderFirstFrame(bool display) override;
    int32_t PrepareAsync() override;
    bool IsPlaying() override;
    int32_t Play() override;
    int32_t Pause() override;
    int32_t Stop() override;
    int32_t Seek(int32_t mSeconds, OHOS::Ace::SeekMode mode) override;
    int32_t SetPlayRange(int64_t startTime, int64_t endTime) override;
    int32_t SetParameter(const std::string& key, int64_t value) override;

private:
    // Interim programme
    bool SetMediaSource(std::string& filePath, int32_t& fd, bool& useFd, const std::string& bundleName = "",
        const std::string& moduleName = "");
    bool MediaPlay(const std::string& filePath);
    bool RawFilePlay(const std::string& filePath);
    bool RelativePathPlay(const std::string& filePath);
    bool RawFileWithModuleInfoPlay(const std::string& src, const std::string& bundleName,
        const std::string& moduleName);
    bool GetResourceId(const std::string& path, uint32_t& resId);
    bool GetResourceId(const std::string& uri, std::string& path) const;

    std::shared_ptr<OHOS::Media::Player> mediaPlayer_ = nullptr;
    std::shared_ptr<MediaPlayerCallback> mediaPlayerCallback_ = nullptr;
    WeakPtr<NG::RosenRenderSurface> renderSurface_ = nullptr;

    ACE_DISALLOW_COPY_AND_MOVE(RosenMediaPlayer);
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PAINTS_ADAPTER_ROSEN_MEDIA_PLAYER_H

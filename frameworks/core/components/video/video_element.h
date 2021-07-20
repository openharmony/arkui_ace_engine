/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_ELEMENT_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_ELEMENT_H

#include "core/components/common/properties/edge.h"
#include "core/components/multimodal/render_multimodal.h"
#include "core/components/slider/slider_theme.h"
#include "core/components/video/resource/player.h"
#include "core/components/video/resource/texture.h"
#include "core/components/video/video_component.h"
#include "core/components/video/video_theme.h"
#include "core/focus/focus_node.h"
#include "core/pipeline/base/render_element.h"

namespace OHOS::Ace {

constexpr double VIDEO_CHILD_COMMON_FLEX_GROW = 1.0;
constexpr double VIDEO_CHILD_COMMON_FLEX_SHRINK = 1.0;
constexpr double VIDEO_CHILD_COMMON_FLEX_BASIS = 0.0;
constexpr uint32_t VIDEO_SEEK_STEP = 5;

class VideoElement : public RenderElement, public FocusNode {
    DECLARE_ACE_TYPE(VideoElement, RenderElement, FocusNode);

public:
    using EventCallback = std::function<void(const std::string&)>;
    using FullscreenEvent = std::function<RefPtr<Component>(bool, const WeakPtr<Player>&, const WeakPtr<Texture>&)>;
    using ErrorCallback = std::function<void(const std::string&, const std::string&)>;

    VideoElement() = default;
    ~VideoElement() override;

    void SetNewComponent(const RefPtr<Component>& newComponent) override;
    void Prepare(const WeakPtr<Element>& parent) override;
    void PerformBuild() override;
    void Dump() override;

    void Start();
    void Pause();
    void SetCurrentTime(uint32_t currentPos);
    void FullScreen();
    void ExitFullScreen();
    void SetVolume(float volume);

private:
    void OnError(const std::string& errorId, const std::string& param);
    void OnPrepared(
        uint32_t width, uint32_t height, bool isPlaying, uint32_t duration, uint32_t currentPos, bool needFireEvent);
    void OnPlayerStatus(bool isPlaying);
    void OnCurrentTimeChange(uint32_t currentPos);
    void OnCompletion();
    void OnStartBtnClick();
    void OnFullScreenBtnClick();
    void OnSliderChange(const std::string& param);
    void OnSliderMoving(const std::string& param);
    void IntTimeToText(uint32_t time, std::string& timeText);
    void InitEvent(const RefPtr<VideoComponent>& videoComponent);
    void SetMethodCall(const RefPtr<VideoComponent>& videoComponent);
    void SetRespondChildEvent();
    void CreatePlatformResource();
    void CreatePlayer(int64_t id, ErrorCallback&& errorCallback);
    void ReleasePlatformResource();
    void UpdataChild(const RefPtr<Component>& childComponent);
    void InitStatus(const RefPtr<VideoComponent>& videoComponent);
    void InitListener();
    void ResetStatus();
    bool OnKeyEvent(const KeyEvent& keyEvent) override;
    void OnKeyLeft();
    void OnKeyRight();
    void OnTextureRefresh();
    void HiddenChange(bool hidden);
    void OnTextureSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight);

    const RefPtr<Component> CreateChild();
    const RefPtr<Component> CreatePoster();
    const RefPtr<Component> CreateControl();
    const RefPtr<Component> CreateCurrentText();
    const RefPtr<Component> CreateDurationText();
    const RefPtr<Component> CreateSlider();
    const RefPtr<Component> CreatePlayBtn();
    const RefPtr<Component> CreateFullScreenBtn();
    const RefPtr<Component> CreateErrorText(const std::string& errorMsg);
    const RefPtr<Component> SetPadding(const RefPtr<Component>& component, Edge&& edge);

    void PrepareMultiModalEvent();
    bool SubscribeMultiModal();
    bool UnSubscribeMultiModal();

    bool isSubscribeMultimodal_ = false;
    RefPtr<VideoTheme> theme_;
    RefPtr<SliderTheme> sliderTheme_;
    RefPtr<Player> player_;
    RefPtr<Texture> texture_;
    bool isExternalResource_ = false;

    ImageFit imageFit_ { ImageFit::CONTAIN };

    bool needControls_ = true;
    bool isAutoPlay_ = false;
    bool isMute_ = false;
    std::string src_;
    std::string poster_;
    uint32_t duration_ = 0;
    uint32_t currentPos_ = 0;
    bool isPlaying_ = false;
    bool pastPlayingStatus_ = false; // Record the player status before dragging the progress bar.
    bool isReady_ = false;
    bool isFullScreen_ = false;
    bool isInitialState_ = true; // Initial state is true. Play or seek will set it to true.
    bool isError_ = false;
    bool isElementPrepared_ = false;
    double videoWidth_ = 0.0;
    double videoHeight_ = 0.0;
    std::string durationText_;
    std::string currentPosText_;
    TextDirection textDirection_ = TextDirection::LTR;

    EventMarker shieldId_; // Shield the event on the control bar.
    EventMarker startBtnClickId_;
    EventMarker fullscreenBtnClickId_;
    EventMarker sliderMovedCallbackId_;
    EventMarker sliderMovingCallbackId_;
    EventCallback onPrepared_;
    EventCallback onStart_;
    EventCallback onPause_;
    EventCallback onFinish_;
    EventCallback onError_;
    EventCallback onSeeking_;
    EventCallback onSeeked_;
    EventCallback onTimeUpdate_;
    EventCallback onFullScreenChange_;

    // multimodal required param
    MultimodalEventCallback multimodalEventFullscreen_;
    MultimodalEventCallback multimodalEventFullscreenExit_;
    MultimodalEventCallback multimodalEventPlay_;
    MultimodalEventCallback multimodalEventPause_;
    WeakPtr<MultiModalScene> multiModalScene_;
    VoiceEvent playVoiceEvent_;
    VoiceEvent pauseVoiceEvent_;
    VoiceEvent fullscreenVoiceEvent_;
    VoiceEvent exitFullscreenVoiceEvent_;

    FullscreenEvent fullscreenEvent_;
};

} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_VIDEO_VIDEO_ELEMENT_H

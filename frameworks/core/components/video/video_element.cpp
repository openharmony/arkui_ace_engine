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

#include "core/components/video/video_element.h"

#include <algorithm>
#include <iomanip>
#include <sstream>

#include "base/i18n/localization.h"
#include "base/json/json_util.h"
#include "base/log/dump_log.h"
#include "base/log/log.h"
#include "base/resource/internal_resource.h"
#include "base/utils/utils.h"
#include "core/components/align/align_component.h"
#include "core/components/box/box_component.h"
#include "core/components/button/button_component.h"
#include "core/components/flex/flex_component.h"
#include "core/components/flex/flex_item_component.h"
#include "core/components/gesture_listener/gesture_listener_component.h"
#include "core/components/image/image_component.h"
#include "core/components/padding/padding_component.h"
#include "core/components/slider/slider_component.h"
#include "core/components/stage/stage_element.h"
#include "core/components/text/text_component.h"
#include "core/components/theme/theme_manager.h"
#include "core/components/video/render_texture.h"
#include "core/event/ace_event_helper.h"
#include "core/event/back_end_event_manager.h"
#include "core/pipeline/base/composed_component.h"
#include "core/pipeline/pipeline_context.h"

namespace OHOS::Ace {
namespace {

const char* PLAY_LABEL = "play";
const char* PAUSE_LABEL = "pause";
const char* FULLSCREEN_LABEL = "fullscreen";
const char* EXIT_FULLSCREEN_LABEL = "exitFullscreen";

} // namespace

VideoElement::~VideoElement()
{
    if (!startBtnClickId_.IsEmpty()) {
        BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(startBtnClickId_);
    }

    if (!sliderMovedCallbackId_.IsEmpty()) {
        BackEndEventManager<void(const std::string&)>::GetInstance().RemoveBackEndEvent(sliderMovedCallbackId_);
    }

    if (!sliderMovingCallbackId_.IsEmpty()) {
        BackEndEventManager<void(const std::string&)>::GetInstance().RemoveBackEndEvent(sliderMovingCallbackId_);
    }

    if (!fullscreenBtnClickId_.IsEmpty()) {
        BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(fullscreenBtnClickId_);
    }

    if (!shieldId_.IsEmpty()) {
        BackEndEventManager<void()>::GetInstance().RemoveBackEndEvent(startBtnClickId_);
    }

    if (!isExternalResource_) {
        if (isFullScreen_) {
            ExitFullScreen();
        }
        UnSubscribeMultiModal();
    } else {
        if (player_) {
            player_->PopListener();
        }
    }
    ReleasePlatformResource();
}

void VideoElement::PerformBuild()
{
    RefPtr<VideoComponent> videoComponent = AceType::DynamicCast<VideoComponent>(component_);

    if (videoComponent == nullptr) {
        return;
    }
    const auto& child = children_.empty() ? nullptr : children_.front();
    UpdateChild(child, videoComponent->GetChild());
}

void VideoElement::InitStatus(const RefPtr<VideoComponent>& videoComponent)
{
    imageFit_ = videoComponent->GetFit();
    needControls_ = videoComponent->NeedControls();
    isAutoPlay_ = videoComponent->IsAutoPlay();
    isMute_ = videoComponent->IsMute();
    src_ = videoComponent->GetSrc();
    poster_ = videoComponent->GetPoster();
    isFullScreen_ = videoComponent->IsFullscreen();

    if (!videoComponent->GetPlayer().Invalid() && !videoComponent->GetTexture().Invalid()) {
        player_ = videoComponent->GetPlayer().Upgrade();
        texture_ = videoComponent->GetTexture().Upgrade();

        if (player_ && texture_) {
            isExternalResource_ = true;
            videoComponent->SetPlayer(nullptr);
            videoComponent->SetTexture(nullptr);
            InitListener();
        }
    }
}

void VideoElement::ResetStatus()
{
    needControls_ = true;
    isAutoPlay_ = false;
    isMute_ = false;
    duration_ = 0;
    currentPos_ = 0;
    isPlaying_ = false;
    isReady_ = false;
    isInitialState_ = true;
    isError_ = false;
    videoWidth_ = 0.0;
    videoHeight_ = 0.0;
    durationText_ = Localization::GetInstance()->FormatDuration(0);
    currentPosText_ = Localization::GetInstance()->FormatDuration(0);
}

void VideoElement::Prepare(const WeakPtr<Element>& parent)
{
    auto themeManager = GetThemeManager();
    if (!themeManager) {
        return;
    }
    auto videoComponent = AceType::DynamicCast<VideoComponent>(component_);
    theme_ = themeManager->GetTheme<VideoTheme>();
    sliderTheme_ = themeManager->GetTheme<SliderTheme>();
    if (videoComponent) {
        textDirection_ = videoComponent->GetTextDirection();

        ResetStatus();
        InitStatus(videoComponent);
        InitEvent(videoComponent);
        SetRespondChildEvent();
        if (!isExternalResource_) {
            SetMethodCall(videoComponent);
            CreatePlatformResource();
            PrepareMultiModalEvent();
            SubscribeMultiModal();
        }
        videoComponent->SetChild(CreateChild());
        fullscreenEvent_ = videoComponent->GetFullscreenEvent();
    }

    RenderElement::Prepare(parent);
    if (renderNode_) {
        auto renderTexture = AceType::DynamicCast<RenderTexture>(renderNode_);
        if (renderTexture) {
            renderTexture->SetHiddenChangeEvent([weak = WeakClaim(this)](bool hidden) {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->HiddenChange(hidden);
                }
            });
            renderTexture->SetTextureSizeChange(
                [weak = WeakClaim(this)](int64_t textureId, int32_t textureWidth, int32_t textureHeight) {
                    auto videoElement = weak.Upgrade();
                    if (videoElement) {
                        videoElement->OnTextureSize(textureId, textureWidth, textureHeight);
                    }
                });
        }
    }
    isElementPrepared_ = true;
}

void VideoElement::OnTextureSize(int64_t textureId, int32_t textureWidth, int32_t textureHeight)
{
    if (texture_) {
        texture_->OnSize(textureId, textureWidth, textureHeight);
    }
}

void VideoElement::HiddenChange(bool hidden)
{
    if (isPlaying_ && hidden && player_) {
        pastPlayingStatus_ = isPlaying_;
        Pause();
        return;
    }

    if (!hidden && pastPlayingStatus_) {
        isPlaying_ = !pastPlayingStatus_;
        pastPlayingStatus_ = false;
        Start();
    }
}

void VideoElement::PrepareMultiModalEvent()
{
    if (!multimodalEventFullscreen_) {
        multimodalEventFullscreen_ = [weak = WeakClaim(this)](const AceMultimodalEvent&) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->FullScreen();
            }
        };
    }

    if (!multimodalEventPause_) {
        multimodalEventPause_ = [weak = WeakClaim(this)](const AceMultimodalEvent&) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->Pause();
            }
        };
    }

    if (!multimodalEventPlay_) {
        multimodalEventPlay_ = [weak = WeakClaim(this)](const AceMultimodalEvent&) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->Start();
            }
        };
    }

    if (!multimodalEventFullscreenExit_) {
        multimodalEventFullscreenExit_ = [weak = WeakClaim(this)](const AceMultimodalEvent&) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->ExitFullScreen();
            }
        };
    };
}

bool VideoElement::SubscribeMultiModal()
{
    if (isSubscribeMultimodal_) {
        return true;
    }
    if (multiModalScene_.Invalid()) {
        const auto pipelineContext = GetContext().Upgrade();
        if (!pipelineContext) {
            LOGW("the pipeline context is null");
            return false;
        }
        const auto multimodalManager = pipelineContext->GetMultiModalManager();
        if (!multimodalManager) {
            LOGW("the multimodal manager is null");
            return false;
        }
        const auto scene = multimodalManager->GetCurrentMultiModalScene();
        if (!scene) {
            return false;
        }

        playVoiceEvent_ = VoiceEvent(PLAY_LABEL, SceneLabel::VIDEO);
        scene->SubscribeVoiceEvent(playVoiceEvent_, multimodalEventPlay_);

        pauseVoiceEvent_ = VoiceEvent(PAUSE_LABEL, SceneLabel::VIDEO);
        scene->SubscribeVoiceEvent(pauseVoiceEvent_, multimodalEventPause_);

        fullscreenVoiceEvent_ = VoiceEvent(FULLSCREEN_LABEL, SceneLabel::VIDEO);
        scene->SubscribeVoiceEvent(fullscreenVoiceEvent_, multimodalEventFullscreen_);

        exitFullscreenVoiceEvent_ = VoiceEvent(EXIT_FULLSCREEN_LABEL, SceneLabel::VIDEO);
        scene->SubscribeVoiceEvent(exitFullscreenVoiceEvent_, multimodalEventFullscreenExit_);
        multiModalScene_ = scene;
        isSubscribeMultimodal_ = true;
    }
    return true;
}

bool VideoElement::UnSubscribeMultiModal()
{
    if (!isSubscribeMultimodal_) {
        return true;
    }
    auto multiModalScene = multiModalScene_.Upgrade();
    if (!multiModalScene) {
        LOGE("fail to destroy multimodal event due to multiModalScene is null");
        return false;
    }
    if (!playVoiceEvent_.GetVoiceContent().empty()) {
        multiModalScene->UnSubscribeVoiceEvent(playVoiceEvent_);
    }
    if (!pauseVoiceEvent_.GetVoiceContent().empty()) {
        multiModalScene->UnSubscribeVoiceEvent(pauseVoiceEvent_);
    }
    if (!exitFullscreenVoiceEvent_.GetVoiceContent().empty()) {
        multiModalScene->UnSubscribeVoiceEvent(exitFullscreenVoiceEvent_);
    }
    if (!fullscreenVoiceEvent_.GetVoiceContent().empty()) {
        multiModalScene->UnSubscribeVoiceEvent(fullscreenVoiceEvent_);
    }
    isSubscribeMultimodal_ = false;
    return true;
}

void VideoElement::SetNewComponent(const RefPtr<Component>& newComponent)
{
    if (newComponent == nullptr || !isElementPrepared_) {
        Element::SetNewComponent(newComponent);
        return;
    }
    auto videoComponent = AceType::DynamicCast<VideoComponent>(newComponent);
    if (videoComponent) {
        if (src_ == videoComponent->GetSrc()) {
            if (isError_) {
                return;
            }
            InitStatus(videoComponent);

            // When the video is in the initial state and the attribute is auto play, start playing.
            if (isInitialState_ && isAutoPlay_) {
                Start();
            }
            if (isMute_) {
                SetVolume(0.0f);
            } else {
                SetVolume(1.0f);
            }
        } else {
            ResetStatus();
            InitStatus(videoComponent);
            CreatePlatformResource();
        }
        if (texture_) {
            videoComponent->SetTextureId(texture_->GetId());
            videoComponent->SetSrcWidth(videoWidth_);
            videoComponent->SetSrcHeight(videoHeight_);
            videoComponent->SetFit(imageFit_);
        }
        videoComponent->SetChild(CreateChild());

        Element::SetNewComponent(videoComponent);
    }
}

void VideoElement::InitEvent(const RefPtr<VideoComponent>& videoComponent)
{
    if (!videoComponent->GetPreparedEventId().IsEmpty()) {
        onPrepared_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetPreparedEventId(), context_);
    }

    if (!videoComponent->GetFinishEventId().IsEmpty()) {
        onFinish_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetFinishEventId(), context_);
    }

    if (!videoComponent->GetErrorEventId().IsEmpty()) {
        onError_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetErrorEventId(), context_);
    }

    if (!videoComponent->GetTimeUpdateEventId().IsEmpty()) {
        onTimeUpdate_ =
            AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetTimeUpdateEventId(), context_);
    }

    if (!videoComponent->GetStartEventId().IsEmpty()) {
        onStart_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetStartEventId(), context_);
    }

    if (!videoComponent->GetPauseEventId().IsEmpty()) {
        onPause_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetPauseEventId(), context_);
    }

    if (!videoComponent->GetSeekingEventId().IsEmpty()) {
        onSeeking_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetSeekingEventId(), context_);
    }

    if (!videoComponent->GetSeekedEventId().IsEmpty()) {
        onSeeked_ = AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetSeekedEventId(), context_);
    }

    if (!videoComponent->GetFullscreenChangeEventId().IsEmpty()) {
        onFullScreenChange_ =
            AceAsyncEvent<void(const std::string&)>::Create(videoComponent->GetFullscreenChangeEventId(), context_);
    }
}

void VideoElement::SetMethodCall(const RefPtr<VideoComponent>& videoComponent)
{
    auto videoController = videoComponent->GetVideoController();
    if (videoController) {
        auto context = context_.Upgrade();
        if (!context) {
            return;
        }
        auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
        videoController->SetStartImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->Start();
                }
            });
        });
        videoController->SetPausetImpl([weak = WeakClaim(this), uiTaskExecutor]() {
            uiTaskExecutor.PostTask([weak]() {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->Pause();
                }
            });
        });
        videoController->SetSeekToImpl([weak = WeakClaim(this), uiTaskExecutor](uint32_t pos) {
            uiTaskExecutor.PostTask([weak, pos]() {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->SetCurrentTime(pos);
                }
            });
        });
        videoController->SetRequestFullscreenImpl([weak = WeakClaim(this), uiTaskExecutor](bool isPortrait) {
            uiTaskExecutor.PostTask([weak, isPortrait]() {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->FullScreen();
                }
            });
        });
        videoController->SetExitFullscreenImpl([weak = WeakClaim(this), uiTaskExecutor](bool isSync) {
            if (isSync) {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->ExitFullScreen();
                }
                return;
            }
            uiTaskExecutor.PostTask([weak]() {
                auto videoElement = weak.Upgrade();
                if (videoElement) {
                    videoElement->ExitFullScreen();
                }
            });
        });
    }
}

void VideoElement::SetRespondChildEvent()
{
    shieldId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
    startBtnClickId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
    BackEndEventManager<void()>::GetInstance().BindBackendEvent(startBtnClickId_, [weak = WeakClaim(this)]() {
        auto videoElement = weak.Upgrade();
        if (videoElement) {
            videoElement->OnStartBtnClick();
        }
    });
    sliderMovedCallbackId_ = BackEndEventManager<void(const std::string&)>::GetInstance().GetAvailableMarker();
    BackEndEventManager<void(const std::string&)>::GetInstance().BindBackendEvent(
        sliderMovedCallbackId_, [weak = WeakClaim(this)](const std::string& param) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->OnSliderChange(param);
            }
        });
    sliderMovingCallbackId_ = BackEndEventManager<void(const std::string&)>::GetInstance().GetAvailableMarker();
    BackEndEventManager<void(const std::string&)>::GetInstance().BindBackendEvent(
        sliderMovingCallbackId_, [weak = WeakClaim(this)](const std::string& param) {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->OnSliderMoving(param);
            }
        });
    fullscreenBtnClickId_ = BackEndEventManager<void()>::GetInstance().GetAvailableMarker();
    BackEndEventManager<void()>::GetInstance().BindBackendEvent(fullscreenBtnClickId_, [weak = WeakClaim(this)]() {
        auto videoElement = weak.Upgrade();
        if (videoElement) {
            videoElement->OnFullScreenBtnClick();
        }
    });
}

void VideoElement::CreatePlatformResource()
{
    ReleasePlatformResource();

    auto context = context_.Upgrade();
    if (!context) {
        return;
    }
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);

    auto errorCallback = [weak = WeakClaim(this), uiTaskExecutor](
                             const std::string& errorId, const std::string& param) {
        uiTaskExecutor.PostTask([weak, errorId, param] {
            auto videoElement = weak.Upgrade();
            if (videoElement) {
                videoElement->OnError(errorId, param);
            }
        });
    };
    texture_ = AceType::MakeRefPtr<Texture>(context_, errorCallback);

    texture_->Create([weak = WeakClaim(this), errorCallback](int64_t id) mutable {
        auto videoElement = weak.Upgrade();
        if (videoElement) {
            videoElement->CreatePlayer(id, std::move(errorCallback));
        }
    });
}

void VideoElement::CreatePlayer(int64_t id, ErrorCallback&& errorCallback)
{
    player_ = AceType::MakeRefPtr<Player>(id, src_, context_, std::move(errorCallback));
    player_->SetMute(isMute_);
    player_->SetAutoPlay(isAutoPlay_);
    InitListener();
    player_->Create(nullptr);
}

void VideoElement::InitListener()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    auto videoElement = WeakClaim(this);
    if (!isExternalResource_) {
        auto onTextureRefresh = [videoElement, uiTaskExecutor]() {
            uiTaskExecutor.PostSyncTask([&videoElement] {
                auto video = videoElement.Upgrade();
                if (video) {
                    video->OnTextureRefresh();
                }
            });
        };
        texture_->SetRefreshListener(onTextureRefresh);
    }

    auto onPrepared = [videoElement, uiTaskExecutor](uint32_t width, uint32_t height, bool isPlaying, uint32_t duration,
                          uint32_t currentPos, bool needFireEvent) {
        uiTaskExecutor.PostSyncTask([&videoElement, width, height, isPlaying, duration, currentPos, needFireEvent] {
            auto video = videoElement.Upgrade();
            if (video) {
                video->OnPrepared(width, height, isPlaying, duration, currentPos, needFireEvent);
            }
        });
    };

    auto onPlayerStatus = [videoElement, uiTaskExecutor](bool isPlaying) {
        uiTaskExecutor.PostSyncTask([&videoElement, isPlaying] {
            auto video = videoElement.Upgrade();
            if (video) {
                video->OnPlayerStatus(isPlaying);
            }
        });
    };

    auto onCurrentTimeChange = [videoElement, uiTaskExecutor](uint32_t currentPos) {
        uiTaskExecutor.PostSyncTask([&videoElement, currentPos] {
            auto video = videoElement.Upgrade();
            if (video) {
                video->OnCurrentTimeChange(currentPos);
            }
        });
    };

    auto onCompletion = [videoElement, uiTaskExecutor] {
        uiTaskExecutor.PostSyncTask([&videoElement] {
            auto video = videoElement.Upgrade();
            if (video) {
                video->OnCompletion();
            }
        });
    };

    player_->AddPreparedListener(onPrepared);
    player_->AddPlayStatusListener(onPlayerStatus);
    player_->AddCurrentPosListener(onCurrentTimeChange);
    player_->AddCompletionListener(onCompletion);
}

void VideoElement::ReleasePlatformResource()
{
    auto context = context_.Upgrade();
    if (!context) {
        return;
    }

    // Reusing texture will cause a problem that last frame of last video will be display.
    if (texture_) {
        auto platformTaskExecutor =
            SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::PLATFORM);

        // Release player first.
        if (player_) {
            if (!isExternalResource_) {
                player_->Stop();
                player_->Release();
            }

            if (platformTaskExecutor.IsRunOnCurrentThread()) {
                player_.Reset();
            } else {
                // Make sure it's destroyed when it's release task done.
                platformTaskExecutor.PostTask([player = player_]() {});
            }
        }

        if (platformTaskExecutor.IsRunOnCurrentThread()) {
            if (!isExternalResource_) {
                texture_->Release();
            }
            texture_.Reset();
        } else {
            if (!isExternalResource_) {
#if defined(ENABLE_NATIVE_VIEW)
                texture_->Release();
            }
            // Make sure it's destroyed when it's release task done.
            platformTaskExecutor.PostTask([texture = texture_]() {});
#else
                auto gpuTaskExecutor =
                    SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::GPU);
                // Release texture after paint.
                gpuTaskExecutor.PostTask([texture = texture_, platformTaskExecutor]() {
                    texture->Release();
                    // Make sure it's destroyed when it's release task done.
                    platformTaskExecutor.PostTask([texture]() {});
                });
            } else {
                // Make sure it's destroyed when it's release task done.
                platformTaskExecutor.PostTask([texture = texture_]() {});
            }
#endif
        }
    }
}

void VideoElement::UpdataChild(const RefPtr<Component>& childComponent)
{
    const auto& child = children_.empty() ? nullptr : children_.front();
    UpdateChild(child, childComponent);
}

void VideoElement::OnError(const std::string& errorId, const std::string& param)
{
    isError_ = true;
    std::string errorcode = Localization::GetInstance()->GetErrorDescription(errorId);
    UpdataChild(CreateErrorText(errorcode));

    if (onError_) {
        std::string param = std::string("\"error\",{").append("}");
        onError_(param);
    }
}

void VideoElement::OnPrepared(
    uint32_t width, uint32_t height, bool isPlaying, uint32_t duration, uint32_t currentPos, bool needFireEvent)
{
    isPlaying_ = isPlaying;
    isReady_ = true;
    videoWidth_ = width;
    videoHeight_ = height;
    duration_ = duration;
    currentPos_ = currentPos;

    IntTimeToText(duration_, durationText_);
    IntTimeToText(currentPos_, currentPosText_);

    auto video = AceType::MakeRefPtr<VideoComponent>();
    video->SetTextureId(texture_->GetId());
    video->SetSrcWidth(videoWidth_);
    video->SetSrcHeight(videoHeight_);
    video->SetFit(imageFit_);

    if (isPlaying || currentPos != 0) {
        isInitialState_ = false;
    }

    if (renderNode_ != nullptr) {
        renderNode_->Update(video);
    }
    UpdataChild(CreateChild());

    if (needFireEvent && onPrepared_) {
        std::string param =
            std::string("\"prepared\",{\"duration\":").append(std::to_string(duration_)).append("}");
        onPrepared_(param);
    }
}

void VideoElement::OnPlayerStatus(bool isPlaying)
{
    if (isInitialState_) {
        isInitialState_ = !isPlaying;
    }

    isPlaying_ = isPlaying;
    if (!isFullScreen_ || isExternalResource_) {
        UpdataChild(CreateChild());
    }

    if (isPlaying) {
        if (onStart_) {
            std::string param = std::string("\"start\",{").append("}");
            onStart_(param);
        }
    } else {
        if (onPause_) {
            std::string param = std::string("\"pause\",{").append("}");
            onPause_(param);
        }
    }
}

void VideoElement::OnCurrentTimeChange(uint32_t currentPos)
{
    isInitialState_ = isInitialState_ ? currentPos == 0 : false;
    IntTimeToText(currentPos, currentPosText_);
    currentPos_ = currentPos;

    UpdataChild(CreateChild());

    if (onTimeUpdate_) {
        std::string param =
            std::string("\"timeupdate\",{\"currenttime\":").append(std::to_string(currentPos)).append("}");
        onTimeUpdate_(param);
    }
}

void VideoElement::OnCompletion()
{
    currentPos_ = duration_;
    IntTimeToText(currentPos_, currentPosText_);

    isPlaying_ = false;
    UpdataChild(CreateChild());

    if (onFinish_) {
        std::string param = std::string("\"finish\",{").append("}");
        onFinish_(param);
    }
}

const RefPtr<Component> VideoElement::CreateErrorText(const std::string& errorMsg)
{
    auto text = AceType::MakeRefPtr<TextComponent>(errorMsg);
    text->SetTextStyle(theme_->GetErrorTextStyle());
    text->SetTextDirection(textDirection_);

    std::list<RefPtr<Component>> childrenAlign;
    childrenAlign.emplace_back(text);

    return AceType::MakeRefPtr<AlignComponent>(childrenAlign, Alignment::TOP_CENTER);
}

const RefPtr<Component> VideoElement::CreateCurrentText()
{
    auto textPos = AceType::MakeRefPtr<TextComponent>(currentPosText_);
    textPos->SetTextStyle(theme_->GetTimeTextStyle());
    return textPos;
}

const RefPtr<Component> VideoElement::CreateDurationText()
{
    auto textDuration = AceType::MakeRefPtr<TextComponent>(durationText_);
    textDuration->SetTextStyle(theme_->GetTimeTextStyle());
    return textDuration;
}

const RefPtr<Component> VideoElement::CreateSlider()
{
    auto slider = AceType::MakeRefPtr<SliderComponent>(currentPos_, 1.0, 0.0, duration_);
    slider->InitStyle(sliderTheme_);
    slider->SetOnMoveEndEventId(sliderMovedCallbackId_);
    slider->SetOnMovingEventId(sliderMovingCallbackId_);
    slider->SetTextDirection(textDirection_);
    return slider;
}

const RefPtr<Component> VideoElement::CreatePlayBtn()
{
    auto imageIcon = InternalResource::ResourceId::PLAY_SVG;

    if (pastPlayingStatus_ || isPlaying_) {
        imageIcon = InternalResource::ResourceId::PAUSE_SVG;
    }

    auto image = AceType::MakeRefPtr<ImageComponent>(imageIcon);
    const Size& btnSize = theme_->GetBtnSize();
    image->SetWidth(Dimension(btnSize.Width()));
    image->SetHeight(Dimension(btnSize.Height()));
    image->SetTextDirection(textDirection_);
    image->SetMatchTextDirection(true);
    std::list<RefPtr<Component>> btnChildren;
    btnChildren.emplace_back(image);

    auto button = AceType::MakeRefPtr<ButtonComponent>(btnChildren);
    button->SetWidth(Dimension(btnSize.Width()));
    button->SetHeight(Dimension(btnSize.Height()));
    button->SetType(ButtonType::ICON);
    button->SetClickedEventId(startBtnClickId_);

    return button;
}

const RefPtr<Component> VideoElement::CreateFullScreenBtn()
{
    auto imageIcon = InternalResource::ResourceId::FULLSCREEN_SVG;

    if (isFullScreen_) {
        imageIcon = InternalResource::ResourceId::QUIT_FULLSCREEN_SVG;
    }

    auto image = AceType::MakeRefPtr<ImageComponent>(imageIcon);
    const Size& btnSize = theme_->GetBtnSize();
    image->SetWidth(Dimension(btnSize.Width()));
    image->SetHeight(Dimension(btnSize.Height()));
    image->SetTextDirection(textDirection_);
    image->SetMatchTextDirection(true);

    std::list<RefPtr<Component>> btnChildren;
    btnChildren.emplace_back(image);

    auto button = AceType::MakeRefPtr<ButtonComponent>(btnChildren);
    button->SetWidth(Dimension(btnSize.Width()));
    button->SetHeight(Dimension(btnSize.Height()));
    button->SetType(ButtonType::ICON);
    button->SetClickedEventId(fullscreenBtnClickId_);
    return button;
}

const RefPtr<Component> VideoElement::SetPadding(const RefPtr<Component>& component, Edge&& edge)
{
    auto paddingComponent = AceType::MakeRefPtr<PaddingComponent>();
    paddingComponent->SetPadding(std::move(edge));
    paddingComponent->SetChild(component);

    return paddingComponent;
}

const RefPtr<Component> VideoElement::CreateControl()
{
    std::list<RefPtr<Component>> rowChildren;

    rowChildren.emplace_back(SetPadding(CreatePlayBtn(), Edge(theme_->GetBtnEdge())));

    rowChildren.emplace_back(SetPadding(CreateCurrentText(), Edge(theme_->GetTextEdge())));

    rowChildren.emplace_back(
        AceType::MakeRefPtr<FlexItemComponent>(VIDEO_CHILD_COMMON_FLEX_GROW, VIDEO_CHILD_COMMON_FLEX_SHRINK,
            VIDEO_CHILD_COMMON_FLEX_BASIS, SetPadding(CreateSlider(), Edge(theme_->GetSliderEdge()))));

    rowChildren.emplace_back(SetPadding(CreateDurationText(), Edge(theme_->GetTextEdge())));

    rowChildren.emplace_back(SetPadding(CreateFullScreenBtn(), Edge(theme_->GetBtnEdge())));

    auto decoration = AceType::MakeRefPtr<Decoration>();
    decoration->SetBackgroundColor(theme_->GetBkgColor());
    auto box = AceType::MakeRefPtr<BoxComponent>();
    box->SetBackDecoration(decoration);
    auto row = AceType::MakeRefPtr<RowComponent>(FlexAlign::CENTER, FlexAlign::CENTER, rowChildren);
    row->SetTextDirection(textDirection_);
    box->SetChild(row);

    auto gestureListener = AceType::MakeRefPtr<GestureListenerComponent>(box);
    gestureListener->SetOnClickId(shieldId_);
    gestureListener->SetOnLongPressId(shieldId_);

    return gestureListener;
}

const RefPtr<Component> VideoElement::CreatePoster()
{
    auto image = AceType::MakeRefPtr<ImageComponent>(poster_);
    image->SetImageFit(imageFit_);
    image->SetFitMaxSize(true);

    std::list<RefPtr<Component>> childrenAlign;
    childrenAlign.emplace_back(image);

    auto gestureListener = AceType::MakeRefPtr<GestureListenerComponent>(
        AceType::MakeRefPtr<AlignComponent>(childrenAlign, Alignment::CENTER));
    gestureListener->SetOnClickId(shieldId_);
    gestureListener->SetOnLongPressId(shieldId_);
    return gestureListener;
}

const RefPtr<Component> VideoElement::CreateChild()
{
    RefPtr<Component> child;
    if (isInitialState_ && !poster_.empty()) {
        std::list<RefPtr<Component>> columnChildren;
        columnChildren.emplace_back(AceType::MakeRefPtr<FlexItemComponent>(VIDEO_CHILD_COMMON_FLEX_GROW,
            VIDEO_CHILD_COMMON_FLEX_SHRINK, VIDEO_CHILD_COMMON_FLEX_BASIS, CreatePoster()));
        if (needControls_) {
            columnChildren.emplace_back(CreateControl());
        }
        child = AceType::MakeRefPtr<ColumnComponent>(FlexAlign::FLEX_END, FlexAlign::SPACE_AROUND, columnChildren);
    } else if (needControls_) {
        std::list<RefPtr<Component>> childrenAlign;
        childrenAlign.emplace_back(CreateControl());
        child = AceType::MakeRefPtr<AlignComponent>(childrenAlign, Alignment::BOTTOM_RIGHT);
    }

    if (child) {
        auto display = AceType::MakeRefPtr<DisplayComponent>(child);
        if (!display) {
            LOGE("Create display component failed. display is null.");
            return display;
        }
        auto textureRender = GetRenderNode();
        if (!textureRender) {
            return display;
        }
        auto displayRender = AceType::DynamicCast<RenderDisplay>(textureRender->GetFirstChild());
        if (!displayRender) {
            return display;
        }
        uint8_t opacity = displayRender->GetOpacity();
        display->SetOpacity(opacity * 1.0 / UINT8_MAX);
        return display;
    } else {
        return child;
    }
}

void VideoElement::OnStartBtnClick()
{
    if (isPlaying_) {
        Pause();
    } else {
        Start();
    }
}

void VideoElement::OnFullScreenBtnClick()
{
    if (!isFullScreen_) {
        FullScreen();
    } else {
        ExitFullScreen();
    }
}

void VideoElement::OnSliderChange(const std::string& param)
{
    size_t pos = param.find("\"value\":");
    if (pos != std::string::npos) {
        if (pastPlayingStatus_) {
            isPlaying_ = false;
            Start();
            pastPlayingStatus_ = false;
        }
        std::stringstream ss;
        uint32_t value = 0;

        ss << param.substr(pos + 8); // Need to add the length of "\"value\":".
        ss >> value;

        SetCurrentTime(value);
        if (onSeeked_) {
            std::string param = std::string("\"seeked\",{\"currenttime\":").append(std::to_string(value)).append("}");
            onSeeked_(param);
        }
    }
}

void VideoElement::OnSliderMoving(const std::string& param)
{
    size_t pos = param.find("\"value\":");
    if (pos != std::string::npos) {
        if (isPlaying_ && !pastPlayingStatus_) {
            Pause();
            pastPlayingStatus_ = true;
        }
        std::stringstream ss;
        uint32_t value = 0;

        // Need to add the length of "\"value\":".
        if (param.size() > (pos + 8)) {
            ss << param.substr(pos + 8);
            ss >> value;
        }

        SetCurrentTime(value);
        if (onSeeking_) {
            std::string param = std::string("\"seeking\",{\"currenttime\":").append(std::to_string(value)).append("}");
            onSeeking_(param);
        }
    }
}

void VideoElement::IntTimeToText(uint32_t time, std::string& timeText)
{
    // Whether the duration is longer than 1 hour.
    bool needShowHour = duration_ > 3600;
    timeText = Localization::GetInstance()->FormatDuration(time, needShowHour);
}

void VideoElement::Start()
{
    if (!isPlaying_ && player_) {
        player_->Start();
    }
}

void VideoElement::Pause()
{
    if (isPlaying_ && player_) {
        player_->Pause();
    }
}

void VideoElement::SetCurrentTime(uint32_t currentPos)
{
    if (currentPos >= 0 && currentPos < duration_ && player_) {
        player_->SeekTo(currentPos);
    }
}

void VideoElement::FullScreen()
{
    if (!isFullScreen_ && !isError_) {
        if (fullscreenEvent_) {
            auto component = AceType::DynamicCast<ComposedComponent>(fullscreenEvent_(true, player_, texture_));
            if (component) {
                auto context = context_.Upgrade();
                if (!context) {
                    return;
                }

                auto stackElement = context->GetLastStack();
                if (!stackElement) {
                    return;
                }

                // add fullscreen component cover component
                stackElement->PushComponent(AceType::MakeRefPtr<ComposedComponent>(component->GetId() + "fullscreen",
                                                component->GetName() + "fullscreen", component->GetChild()),
                    true);

                isFullScreen_ = true;
                if (onFullScreenChange_) {
                    std::string param = std::string("\"fullscreenchange\",{\"fullscreen\":")
                                            .append(std::to_string(isFullScreen_))
                                            .append("}");
                    onFullScreenChange_(param);
                }
            }
        }
    }
}

void VideoElement::ExitFullScreen()
{
    if (fullscreenEvent_) {
        fullscreenEvent_(false, nullptr, nullptr);
    }

    if (!isExternalResource_ && isFullScreen_) {
        auto context = context_.Upgrade();
        if (!context) {
            return;
        }

        auto stackElement = context->GetLastStack();
        if (!stackElement) {
            return;
        }
        stackElement->PopComponent(true);
        isFullScreen_ = false;
        if (onFullScreenChange_) {
            std::string param =
                std::string("\"fullscreenchange\",{\"fullscreen\":").append(std::to_string(isFullScreen_)).append("}");
            onFullScreenChange_(param);
        }
        if (renderNode_) {
            renderNode_->MarkNeedLayout();
        }
    }
}

void VideoElement::SetVolume(float volume)
{
    if (player_) {
        player_->SetVolume(volume);
    }
}

void VideoElement::Dump()
{
    if (texture_) {
        DumpLog::GetInstance().AddDesc("texture:", texture_->GetHashCode());
    }
    if (player_) {
        DumpLog::GetInstance().AddDesc("player:", player_->GetHashCode());
    }
    DumpLog::GetInstance().AddDesc("isError:", isError_);
    DumpLog::GetInstance().AddDesc("poster:", poster_);
    DumpLog::GetInstance().AddDesc("isInitialState_:", isInitialState_);
    DumpLog::GetInstance().AddDesc("videoWidth:", videoWidth_);
    DumpLog::GetInstance().AddDesc("videoHeight:", videoHeight_);
    DumpLog::GetInstance().AddDesc("isReady:", isReady_);
    DumpLog::GetInstance().AddDesc("src:", src_);
    DumpLog::GetInstance().AddDesc("isAutoPlay:", isAutoPlay_);
    DumpLog::GetInstance().AddDesc("needControls:", needControls_);
    DumpLog::GetInstance().AddDesc("isMute:", isMute_);
}

bool VideoElement::OnKeyEvent(const KeyEvent& keyEvent)
{
    if (keyEvent.action != KeyAction::UP) {
        return false;
    }
    switch (keyEvent.code) {
        case KeyCode::KEYBOARD_BACK:
        case KeyCode::KEYBOARD_ESCAPE: {
            if (isFullScreen_) {
                ExitFullScreen();
                return true;
            }
            break;
        }
        case KeyCode::KEYBOARD_ENTER: {
            if (!isFullScreen_) {
                FullScreen();
            } else {
                OnStartBtnClick();
            }
            return true;
        }
        case KeyCode::TV_CONTROL_MEDIA_PLAY: {
            OnStartBtnClick();
            return true;
        }
        case KeyCode::TV_CONTROL_LEFT: {
            if (isFullScreen_) {
                OnKeyLeft();
                if (!isPlaying_) {
                    Start();
                }
                return true;
            }
            break;
        }
        case KeyCode::TV_CONTROL_RIGHT: {
            if (isFullScreen_) {
                OnKeyRight();
                if (!isPlaying_) {
                    Start();
                }
                return true;
            }
            break;
        }
        default:
            break;
    }
    return false;
}

void VideoElement::OnKeyLeft()
{
    SetCurrentTime(currentPos_ > VIDEO_SEEK_STEP ? currentPos_ - VIDEO_SEEK_STEP : 0);
}

void VideoElement::OnKeyRight()
{
    if (currentPos_ + VIDEO_SEEK_STEP < duration_) {
        SetCurrentTime(currentPos_ + VIDEO_SEEK_STEP);
    }
}

void VideoElement::OnTextureRefresh()
{
    auto context = context_.Upgrade();
    if (context) {
        context->MarkForcedRefresh();
    }
}

} // namespace OHOS::Ace

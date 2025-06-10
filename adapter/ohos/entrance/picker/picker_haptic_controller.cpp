/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "adapter/ohos/entrance/picker/picker_haptic_controller.h"
#include "core/common/vibrator/vibrator_utils.h"

namespace OHOS::Ace::NG {
namespace {
using std::chrono_literals::operator""s;
using std::chrono_literals::operator""ms;
const std::string AUDIO_TEST_URI = "/system/etc/arkui/timepicker.ogg";
const std::string EFFECT_ID_NAME = "haptic.slide";
constexpr size_t SPEED_THRESHOLD = 1560;
constexpr size_t TREND_COUNT = 3;
#ifdef SUPPORT_DIGITAL_CROWN
constexpr char CROWN_VIBRATOR_WEAK[] = "watchhaptic.feedback.crown.strength2";
#else
constexpr size_t SPEED_MAX = 5000;
constexpr std::chrono::milliseconds DEFAULT_DELAY(40);
constexpr std::chrono::milliseconds EXTENDED_DELAY(50);
#endif
constexpr size_t SPEED_PLAY_ONCE = 0;
} // namespace

PickerHapticController::PickerHapticController(const std::string& uri, const std::string& effectId) noexcept
{
    std::string effectiveUri = uri.empty() ? AUDIO_TEST_URI : uri;
    std::string effectiveEffectId = effectId.empty() ? EFFECT_ID_NAME : effectId;
    audioHapticManager_ = Media::AudioHapticManagerFactory::CreateAudioHapticManager();
    if (audioHapticManager_) {
        effectSourceId_ = audioHapticManager_->RegisterSourceWithEffectId(effectiveUri, effectiveEffectId);
        Media::AudioLatencyMode latencyMode = Media::AudioLatencyMode::AUDIO_LATENCY_MODE_FAST;
        audioHapticManager_->SetAudioLatencyMode(effectSourceId_, latencyMode);
        AudioStandard::StreamUsage streamUsage = AudioStandard::StreamUsage::STREAM_USAGE_NOTIFICATION;
        audioHapticManager_->SetStreamUsage(effectSourceId_, streamUsage);
        Media::AudioHapticPlayerOptions options;
        options.muteAudio = false;
        options.muteHaptics = false;
        options.parallelPlayFlag = true;
        effectAudioHapticPlayer_ = audioHapticManager_->CreatePlayer(effectSourceId_, options);
        if (effectAudioHapticPlayer_) {
            effectAudioHapticPlayer_->Prepare();
        }
        auto audioSystemMgr = AudioStandard::AudioSystemManager::GetInstance();
        audioGroupMngr_ = audioSystemMgr->GetGroupManager(AudioStandard::DEFAULT_VOLUME_GROUP_ID);
        InitPlayThread();
    }
}

PickerHapticController::~PickerHapticController() noexcept
{
    ThreadRelease();
    if (effectAudioHapticPlayer_) {
        effectAudioHapticPlayer_->Stop();
    }
    if (effectAudioHapticPlayer_) {
        effectAudioHapticPlayer_->Release();
    }
    if (audioHapticManager_) {
        audioHapticManager_->UnregisterSource(effectSourceId_);
    }
}

void PickerHapticController::ThreadRelease()
{
    if (playThread_) {
        {
            std::lock_guard<std::recursive_mutex> guard(threadMutex_);
            playThreadStatus_ = ThreadStatus::NONE;
        }
        threadCv_.notify_one();
        playThread_ = nullptr;
    }
    playThreadStatus_ = ThreadStatus::NONE;
}

bool PickerHapticController::IsThreadReady()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::READY;
}

bool PickerHapticController::IsThreadPlaying()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::PLAYING;
}

bool PickerHapticController::IsThreadPlayOnce()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::PLAY_ONCE;
}

bool PickerHapticController::IsThreadNone()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::NONE;
}

void PickerHapticController::InitPlayThread()
{
    ThreadRelease();
    playThreadStatus_ = ThreadStatus::START;
    playThread_ = std::make_unique<std::thread>(&PickerHapticController::ThreadLoop, this);
    if (playThread_) {
        playThread_->detach();
        playThreadStatus_ = ThreadStatus::READY;
    } else {
        playThreadStatus_ = ThreadStatus::NONE;
    }
}

void PickerHapticController::ThreadLoop()
{
    while (!IsThreadNone()) {
        {
            std::unique_lock<std::recursive_mutex> lock(threadMutex_);
            threadCv_.wait(lock, [this]() { return IsThreadPlaying() || IsThreadPlayOnce(); });
            if (IsThreadNone()) {
                return;
            }
        }
#ifdef SUPPORT_DIGITAL_CROWN
        playThreadStatus_ = ThreadStatus::READY;
        VibratorUtils::StartVibraFeedback(CROWN_VIBRATOR_WEAK);
#else
        CHECK_NULL_VOID(audioGroupMngr_);
        CHECK_NULL_VOID(effectAudioHapticPlayer_);
        isInHapticLoop_ = true;
        auto vol = audioGroupMngr_->GetVolume(AudioStandard::AudioVolumeType::STREAM_RING);
        auto userVolume = audioGroupMngr_->GetSystemVolumeInDb(
            AudioStandard::AudioVolumeType::STREAM_RING, vol, AudioStandard::DEVICE_TYPE_SPEAKER);

        // Set different volumes for different sliding speeds:
        float maxVolume = 0.6f + 0.4f * userVolume;
        float volume = 0.6f + (maxVolume - 0.6f) * ((static_cast<float>(absSpeedInMm_) - SPEED_THRESHOLD) /
                                                       (SPEED_MAX - SPEED_THRESHOLD));
        volume = std::clamp(volume, 0.6f, 1.f);

        // Different vibration parameters for different sliding speeds:
        float haptic = absSpeedInMm_ * 0.01f + 50.f;
        haptic = std::clamp(haptic, 50.f, 98.f);
        effectAudioHapticPlayer_->SetVolume(volume);
        effectAudioHapticPlayer_->SetHapticIntensity(haptic);
        effectAudioHapticPlayer_->Start();

        {
            auto startTime = std::chrono::high_resolution_clock::now();
            std::unique_lock<std::recursive_mutex> lock(threadMutex_);
            std::chrono::milliseconds delayTime = DEFAULT_DELAY;
            if (IsThreadPlayOnce() && isLoopReadyToStop_) { // 50ms delay after 40ms loop ends
                delayTime = EXTENDED_DELAY;
            }
            threadCv_.wait_until(lock, startTime + delayTime);
            if (IsThreadPlayOnce() || isLoopReadyToStop_) {
                playThreadStatus_ = ThreadStatus::READY;
            }
        }
        isInHapticLoop_ = false;
#endif
    }
}

void PickerHapticController::Play(size_t speed)
{
    if (!playThread_) {
        InitPlayThread();
    }
    bool needNotify = !IsThreadPlaying() && !IsThreadPlayOnce();
    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        absSpeedInMm_ = speed;
        playThreadStatus_ = ThreadStatus::PLAYING;
    }
    if (needNotify) {
        threadCv_.notify_one();
    }
}

void PickerHapticController::PlayOnce()
{
    if (IsThreadPlaying()) {
        return;
    }
    if (!playThread_) {
        InitPlayThread();
    }

    bool needNotify = !IsThreadPlaying() && !IsThreadPlayOnce();
    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        playThreadStatus_ = ThreadStatus::PLAY_ONCE;
        absSpeedInMm_ = SPEED_PLAY_ONCE;
    }
    if (needNotify) {
        threadCv_.notify_one();
    }
#ifndef SUPPORT_DIGITAL_CROWN
    isHapticCanLoopPlay_ = true;
#endif
}

void PickerHapticController::Stop()
{
    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        playThreadStatus_ = ThreadStatus::READY;
    }
    threadCv_.notify_one();
    lastHandleDeltaTime_ = 0;
}

void PickerHapticController::HandleDelta(double dy)
{
#ifndef SUPPORT_DIGITAL_CROWN
    uint64_t currentTime = GetMilliseconds();
    uint64_t intervalTime = currentTime - lastHandleDeltaTime_;
    CHECK_EQUAL_VOID(intervalTime, 0);

    lastHandleDeltaTime_ = currentTime;
    auto scrollSpeed = std::abs(ConvertPxToMillimeters(dy) / intervalTime) * 1000;
    if (scrollSpeed > SPEED_MAX) {
        scrollSpeed = SPEED_MAX;
    }
    recentSpeeds_.push_back(scrollSpeed);
    if (recentSpeeds_.size() > TREND_COUNT) {
        recentSpeeds_.pop_front();
    }

    if (!isInHapticLoop_ && isLoopReadyToStop_) {
        // play haptic after 40ms 1oop
        isLoopReadyToStop_ = false;
        playThreadStatus_ = ThreadStatus::READY;
        PlayOnce();
    } else if (isHapticCanLoopPlay_ && GetPlayStatus() == 1) { // 40ms 1oop
        Play(scrollSpeed);
    } else if (GetPlayStatus() == -1 && IsThreadPlaying() && !isLoopReadyToStop_) {
        // judging the time of next haptic after 40ms loop ends
        isLoopReadyToStop_ = true;
        isHapticCanLoopPlay_ = false;
        recentSpeeds_.clear();
        absSpeedInMm_ = scrollSpeed;
    }
#endif
}

double PickerHapticController::ConvertPxToMillimeters(double px) const
{
    auto& manager = ScreenSystemManager::GetInstance();
    return px / manager.GetDensity();
}

size_t PickerHapticController::GetCurrentSpeedInMm()
{
    double velocityInPixels = velocityTracker_.GetVelocity().GetVelocityY();
    return std::abs(ConvertPxToMillimeters(velocityInPixels));
}

int8_t PickerHapticController::GetPlayStatus()
{
    if (recentSpeeds_.size() < TREND_COUNT) {
        return 0;
    }
    bool allAbove = true;
    bool allBelow = true;
    for (size_t i = 0; i < TREND_COUNT; ++i) {
        const double speed = recentSpeeds_[i];
        if (speed <= SPEED_THRESHOLD) {
            allAbove = false;
        }
        if (speed >= SPEED_THRESHOLD) {
            allBelow = false;
        }
    }
    return allAbove ? 1 : (allBelow ? -1 : 0); // 1 : play  -1 : playnoce  0 : other
}
} // namespace OHOS::Ace::NG

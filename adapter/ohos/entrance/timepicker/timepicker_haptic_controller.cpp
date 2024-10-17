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

#include "adapter/ohos/entrance/timepicker/timepicker_haptic_controller.h"

namespace OHOS::Ace::NG {
namespace {
const std::string AUDIO_TEST_URI = "/system/etc/arkui/timepicker.ogg";
const std::string EFFECT_ID_NAME = "haptic.clock.timer";
constexpr size_t SPEED_THRESHOLD_156_MM_PER_SEC = 156;
constexpr size_t SPEED_PLAY_ONCE_5_MM_PER_SEC = 5;
} // namespace

TimePickerHapticController::TimePickerHapticController() noexcept
{
    audioHapticManager_ = Media::AudioHapticManagerFactory::CreateAudioHapticManager();
    if (audioHapticManager_) {
        effectSourceId_ = audioHapticManager_->RegisterSourceWithEffectId(AUDIO_TEST_URI, EFFECT_ID_NAME);
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

TimePickerHapticController::~TimePickerHapticController() noexcept
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

void TimePickerHapticController::ThreadRelease()
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

bool TimePickerHapticController::IsThreadReady()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::READY;
}

bool TimePickerHapticController::IsThreadPlaying()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::PLAYING;
}

bool TimePickerHapticController::IsThreadPlayOnce()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::PLAY_ONCE;
}

bool TimePickerHapticController::IsThreadNone()
{
    std::lock_guard<std::recursive_mutex> guard(threadMutex_);
    return playThreadStatus_ == ThreadStatus::NONE;
}

void TimePickerHapticController::InitPlayThread()
{
    ThreadRelease();
    playThreadStatus_ = ThreadStatus::START;
    playThread_ = std::make_unique<std::thread>(&TimePickerHapticController::ThreadLoop, this);
    if (playThread_) {
        playThread_->detach();
        playThreadStatus_ = ThreadStatus::READY;
    } else {
        playThreadStatus_ = ThreadStatus::NONE;
    }
}

void TimePickerHapticController::ThreadLoop()
{
    while (!IsThreadNone()) {
        {
            std::unique_lock<std::recursive_mutex> lock(threadMutex_);
            threadCv_.wait(lock, [this]() { return IsThreadPlaying() || IsThreadPlayOnce() || IsThreadNone(); });
            if (IsThreadNone()) {
                return;
            }
        }
        CHECK_NULL_VOID(audioGroupMngr_);
        CHECK_NULL_VOID(effectAudioHapticPlayer_);
        auto vol = audioGroupMngr_->GetVolume(AudioStandard::AudioVolumeType::STREAM_RING);
        auto userVolume = audioGroupMngr_->GetSystemVolumeInDb(
            AudioStandard::AudioVolumeType::STREAM_RING, vol, AudioStandard::DEVICE_TYPE_SPEAKER);

        // Set different volumes for different sliding speeds:
        //    sound effect loudness
        //    (dB) = sound effect dB set by the user + (0.0066 screen movement speed (mm/s) - 0.01)
        //    the range of volume interface setting is [0.0f, 1.0f]
        float volume = userVolume + 0.0066 * absSpeedInMm_ - 0.01;
        volume = std::clamp(volume, 0.0f, 1.0f);

        // Different vibration parameters for different sliding speeds:
        //    the frequency is between 260~300Hz and fixed, the vibration amount
        //    (g) = (0.007 * screen movement speed (mm/s) + 0.3) * 100
        //    the range of haptic intensity interface setting is [1.0f, 100.0f]
        float haptic = ((absSpeedInMm_ == 0) ? 0 : absSpeedInMm_ * 0.007 + 0.3) * 100;
        haptic = std::clamp(haptic, 1.0f, 100.0f);

        auto startTime = std::chrono::high_resolution_clock::now();
        effectAudioHapticPlayer_->SetVolume(volume);
        effectAudioHapticPlayer_->SetHapticIntensity(haptic);
        effectAudioHapticPlayer_->Start();
        if (IsThreadPlaying()) {
            std::unique_lock<std::recursive_mutex> lock(threadMutex_);
            threadCv_.wait_until(lock, startTime + 40ms);
        } else if (IsThreadPlayOnce()) {
            std::unique_lock<std::recursive_mutex> lock(threadMutex_);
            playThreadStatus_ = ThreadStatus::READY;
        }
    }
}

void TimePickerHapticController::Play(size_t speed)
{
    if (!playThread_) {
        InitPlayThread();
    }
    bool needNotify = !IsThreadPlaying();
    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        absSpeedInMm_ = speed;
        playThreadStatus_ = ThreadStatus::PLAYING;
    }
    if (needNotify) {
        threadCv_.notify_one();
    }
}

void TimePickerHapticController::PlayOnce()
{
    if (IsThreadPlaying()) {
        return;
    }

    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        playThreadStatus_ = ThreadStatus::PLAY_ONCE;
        absSpeedInMm_ = SPEED_PLAY_ONCE_5_MM_PER_SEC;
    }
    threadCv_.notify_one();
}

void TimePickerHapticController::Stop()
{
    {
        std::lock_guard<std::recursive_mutex> guard(threadMutex_);
        playThreadStatus_ = ThreadStatus::READY;
    }
    threadCv_.notify_one();
    scrollValue_ = 0.0;
}

void TimePickerHapticController::HandleDelta(double dy)
{
    auto startTime = std::chrono::high_resolution_clock::now();
    scrollValue_ += dy;
    velocityTracker_.UpdateTrackerPoint(0, scrollValue_, startTime);
    auto scrollSpeed = GetCurrentSpeedInMm();
    if (GreatOrEqual(scrollSpeed, SPEED_THRESHOLD_156_MM_PER_SEC)) {
        Play(scrollSpeed);
    } else {
        Stop();
    }
}

double TimePickerHapticController::ConvertPxToMillimeters(double px) const
{
    auto& manager = ScreenSystemManager::GetInstance();
    return px / manager.GetDensity();
}

size_t TimePickerHapticController::GetCurrentSpeedInMm()
{
    double velocityInPixels = velocityTracker_.GetVelocity().GetVelocityY();
    return std::abs(ConvertPxToMillimeters(velocityInPixels));
}

} // namespace OHOS::Ace::NG

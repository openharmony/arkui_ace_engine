/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/video/video_controller_async.h"

#include "base/thread/task_executor.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/video/video_state_machine_full_screen_pattern.h"
#include "core/components_ng/pattern/video/video_state_machine_pattern.h"

namespace OHOS::Ace {

VideoControllerAsync::VideoControllerAsync(const WeakPtr<NG::VideoStateMachinePattern>& pattern)
    : pattern_(pattern)
{}

void VideoControllerAsync::SetPattern(const WeakPtr<NG::VideoStateMachinePattern>& pattern)
{
    if (!pattern_.Invalid() && pattern_.Upgrade()) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::SetPattern: pattern already set, overwriting");
    }
    pattern_ = pattern;
}

void VideoControllerAsync::Start(AsyncCommandCallback&& callback)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::Start: pattern is null");
        if (callback) {
            callback(false, "pattern is null");
        }
        return;
    }
    pattern->Start(std::move(callback));
}

void VideoControllerAsync::Pause(AsyncCommandCallback&& callback)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::Pause: pattern is null");
        if (callback) {
            callback(false, "pattern is null");
        }
        return;
    }
    pattern->Pause(std::move(callback));
}

void VideoControllerAsync::Stop(AsyncCommandCallback&& callback)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::Stop: pattern is null");
        if (callback) {
            callback(false, "pattern is null");
        }
        return;
    }
    pattern->Stop(std::move(callback));
}

void VideoControllerAsync::Reset(AsyncCommandCallback&& callback)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::Reset: pattern is null");
        if (callback) {
            callback(false, "pattern is null");
        }
        return;
    }
    pattern->ResetMediaPlayerOnBg(std::move(callback));
}

void VideoControllerAsync::SeekTo(float time, SeekMode seekMode)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::SeekTo: pattern is null");
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = pattern_, time, seekMode]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->GetInstanceId());
            auto targetPattern = pattern->GetTargetVideoPattern();
            CHECK_NULL_VOID(targetPattern);
            targetPattern->SetCurrentTime(time, seekMode);
        },
        "ArkUIVideoSetCurrentTime");
}

void VideoControllerAsync::RequestFullscreen(bool landscape)
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::RequestFullscreen: pattern is null");
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = pattern_, landscape]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->GetInstanceId());
            if (landscape) {
                pattern->FullScreen();
            } else {
                pattern->ResetLastBoundsRect();
                auto targetPattern = pattern->GetTargetVideoPattern();
                CHECK_NULL_VOID(targetPattern);
                auto fullScreenPattern = AceType::DynamicCast<NG::VideoStateMachineFullScreenPattern>(targetPattern);
                if (fullScreenPattern) {
                    fullScreenPattern->ExitFullScreen();
                }
            }
        },
        "ArkUIVideoFullScreen");
}

void VideoControllerAsync::ExitFullscreen()
{
    auto pattern = pattern_.Upgrade();
    if (!pattern) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "VideoControllerAsync::ExitFullscreen: pattern is null");
        return;
    }
    auto host = pattern->GetHost();
    CHECK_NULL_VOID(host);
    auto context = host->GetContext();
    CHECK_NULL_VOID(context);
    auto uiTaskExecutor = SingleTaskExecutor::Make(context->GetTaskExecutor(), TaskExecutor::TaskType::UI);
    uiTaskExecutor.PostTask(
        [weak = pattern_]() {
            auto pattern = weak.Upgrade();
            CHECK_NULL_VOID(pattern);
            ContainerScope scope(pattern->GetInstanceId());
            pattern->ResetLastBoundsRect();
            auto targetPattern = pattern->GetTargetVideoPattern();
            CHECK_NULL_VOID(targetPattern);
            auto fullScreenPattern = AceType::DynamicCast<NG::VideoStateMachineFullScreenPattern>(targetPattern);
            if (fullScreenPattern) {
                fullScreenPattern->ExitFullScreen();
            }
        },
        "ArkUIVideoExitFullScreen");
}

} // namespace OHOS::Ace
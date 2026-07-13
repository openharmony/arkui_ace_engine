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

#include <utility>

#include "ui/base/utils/utils.h"

#include "base/utils/utils.h"
#include "core/components_ng/pattern/video/bridge/video_controller_async_custom_modifier.h"
#include "core/components_ng/pattern/video/video_controller_async.h"

namespace OHOS::Ace::NG {
namespace {
void* VideoControllerAsyncCreate()
{
    auto controller = AceType::MakeRefPtr<VideoControllerAsync>();
    controller->IncRefCount();
    return AceType::RawPtr(controller);
}

void VideoControllerAsyncStart(void* controller, void* asyncCallback)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    auto* callback = reinterpret_cast<VideoControllerAsync::AsyncCommandCallback*>(asyncCallback);
    CHECK_NULL_VOID(callback);
    ctrl->Start(std::move(*callback));
}

void VideoControllerAsyncPause(void* controller, void* asyncCallback)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    auto* callback = reinterpret_cast<VideoControllerAsync::AsyncCommandCallback*>(asyncCallback);
    CHECK_NULL_VOID(callback);
    ctrl->Pause(std::move(*callback));
}

void VideoControllerAsyncStop(void* controller, void* asyncCallback)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    auto* callback = reinterpret_cast<VideoControllerAsync::AsyncCommandCallback*>(asyncCallback);
    CHECK_NULL_VOID(callback);
    ctrl->Stop(std::move(*callback));
}

void VideoControllerAsyncReset(void* controller, void* asyncCallback)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    auto* callback = reinterpret_cast<VideoControllerAsync::AsyncCommandCallback*>(asyncCallback);
    CHECK_NULL_VOID(callback);
    ctrl->Reset(std::move(*callback));
}

void VideoControllerAsyncSeekTo(void* controller, float time, int32_t seekMode)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    ctrl->SeekTo(time, static_cast<SeekMode>(seekMode));
}

void VideoControllerAsyncRequestFullscreen(void* controller, bool landscape)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    ctrl->RequestFullscreen(landscape);
}

void VideoControllerAsyncExitFullscreen(void* controller)
{
    auto* ctrl = reinterpret_cast<VideoControllerAsync*>(controller);
    CHECK_NULL_VOID(ctrl);
    ctrl->ExitFullscreen();
}
} // namespace

namespace NodeModifier {
const ArkUIVideoControllerAsyncModifier* GetVideoControllerAsyncDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIVideoControllerAsyncModifier modifier = {
        .create = VideoControllerAsyncCreate,
        .start = VideoControllerAsyncStart,
        .pause = VideoControllerAsyncPause,
        .stop = VideoControllerAsyncStop,
        .reset = VideoControllerAsyncReset,
        .seekTo = VideoControllerAsyncSeekTo,
        .requestFullscreen = VideoControllerAsyncRequestFullscreen,
        .exitFullscreen = VideoControllerAsyncExitFullscreen,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

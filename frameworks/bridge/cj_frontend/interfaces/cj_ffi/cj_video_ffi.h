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

#ifndef OHOS_ACE_FRAMEWORK_CJ_VIDEO_H
#define OHOS_ACE_FRAMEWORK_CJ_VIDEO_H
#include <cstdint>
#include <string>

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_common_ffi.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_macro.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_view_abstract_ffi.h"
#include "core/components_ng/pattern/video/video_model_ng.h"
#include "ffi_remote_data.h"

namespace OHOS::Ace::Framework {
class ACE_EXPORT NativeVideoController : public OHOS::FFI::FFIData {
    DECL_TYPE(NativePatternLockController, OHOS::FFI::FFIData)
public:
    NativeVideoController();

    void Start();
    void Pause();
    void Stop();
    void Reset();
    void SetCurrentTime(int32_t time, int32_t seekMode);
    void RequestFullscreen(bool fullScreen);
    void ExitFullscreen();

    RefPtr<VideoControllerV2> GetController() const
    {
        return videoController_;
    }
    void SetController(const RefPtr<VideoControllerV2>& controller)
    {
        videoController_ = controller;
    }

private:
    RefPtr<VideoControllerV2> videoController_;
};
} // namespace OHOS::Ace::Framework

extern "C" {
CJ_EXPORT void FfiOHOSAceFrameworkVideoCreate(
    const char* src, double progressRate, const char* preview, int64_t controller);
CJ_EXPORT void FfiOHOSAceFrameworkVideoMuted(bool muted);
CJ_EXPORT void FfiOHOSAceFrameworkVideoAutoPlay(bool autoPlay);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControls(bool controls);
CJ_EXPORT void FfiOHOSAceFrameworkVideoObjectFit(int32_t objectFit);
CJ_EXPORT void FfiOHOSAceFrameworkVideoLoop(bool loop);
CJ_EXPORT void FfiOHOSAceFrameworkVideoEnableAnalyzer(bool enable);
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnStart(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnPause(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnFinish(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnError(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnStop(void (*callback)(const char* value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnPrepared(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnSeeking(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnSeeked(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnUpdate(void (*callback)(int32_t value));
CJ_EXPORT void FfiOHOSAceFrameworkVideoOnFullscreenChange(void (*callback)(bool value));

CJ_EXPORT int64_t FfiOHOSAceFrameworkVideoControllerCreate();
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerStart(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerPause(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerStop(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerReset(int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerSetCurrentTime(int32_t time, int32_t seekMode, int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerRequestFullscreen(bool fullScreen, int64_t selfID);
CJ_EXPORT void FfiOHOSAceFrameworkVideoControllerExitFullscreen(int64_t selfID);
};

#endif // OHOS_ACE_FRAMEWORK_CJ_VIDEO_H

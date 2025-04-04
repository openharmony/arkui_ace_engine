/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller.h"

#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_common_def.h"
#ifdef SUPPORT_JSSTACK
#include "xpower_event_jsvm.h"
#endif

namespace OHOS::Ace::Framework {
namespace {

const std::vector<SeekMode> SEEK_MODE = { SeekMode::SEEK_PREVIOUS_SYNC, SeekMode::SEEK_NEXT_SYNC,
    SeekMode::SEEK_CLOSEST_SYNC, SeekMode::SEEK_CLOSEST };

} // namespace

void JSVideoController::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideoController>::Declare("VideoController");
    JSClass<JSVideoController>::CustomMethod("start", &JSVideoController::Start);
    JSClass<JSVideoController>::CustomMethod("pause", &JSVideoController::Pause);
    JSClass<JSVideoController>::CustomMethod("stop", &JSVideoController::Stop);
    JSClass<JSVideoController>::CustomMethod("setCurrentTime", &JSVideoController::SetCurrentTime);
    JSClass<JSVideoController>::CustomMethod("requestFullscreen", &JSVideoController::RequestFullscreen);
    JSClass<JSVideoController>::CustomMethod("exitFullscreen", &JSVideoController::ExitFullscreen);
    JSClass<JSVideoController>::CustomMethod("reset", &JSVideoController::Reset);
    JSClass<JSVideoController>::Bind(globalObj, JSVideoController::Constructor, JSVideoController::Destructor);
}

void JSVideoController::Constructor(const JSCallbackInfo& args)
{
    auto videoController = Referenced::MakeRefPtr<JSVideoController>();
    videoController->IncRefCount();
    RefPtr<VideoControllerV2> controller = AceType::MakeRefPtr<VideoControllerV2>();
    videoController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(videoController));
}

void JSVideoController::Destructor(JSVideoController* videoController)
{
    if (videoController) {
        const auto& controller = videoController->GetController();
        videoController->DecRefCount();
        if (controller) {
            controller->Clear();
        }
    }
}

void JSVideoController::Reset(const JSCallbackInfo& args)
{
    if (videoController_) {
        videoController_->Reset();
    }
}

void JSVideoController::Start(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (videoController_) {
#ifdef SUPPORT_JSSTACK
        HiviewDFX::ReportXPowerJsStackSysEvent(args.GetVm(), "STREAM_CHANGE", "SRC=Video");
#endif
        videoController_->Start();
    }
}

void JSVideoController::Pause(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (videoController_) {
        videoController_->Pause();
    }
}

void JSVideoController::Stop(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (videoController_) {
        videoController_->Stop();
    }
}

void JSVideoController::SetCurrentTime(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    float value = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], value)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoController set current time with invalid params");
        return;
    }

    SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC;
    if (args.Length() > 1 && args[1]->IsNumber() && args[1]->ToNumber<uint32_t>() < SEEK_MODE.size()) {
        seekMode = SEEK_MODE[args[1]->ToNumber<int32_t>()];
    }

    if (videoController_) {
        videoController_->SeekTo(value, seekMode);
    }
}

void JSVideoController::RequestFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    bool landscape = true;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], landscape)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoController request full screen with invalid params");
        return;
    }

    if (videoController_) {
        videoController_->RequestFullscreen(landscape);
    }
}

void JSVideoController::ExitFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (videoController_) {
        videoController_->ExitFullscreen(false);
    }
}

} // namespace OHOS::Ace::Framework

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

#include "frameworks/bridge/declarative_frontend/jsview/js_video_controller_binding.h"

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

void JSVideoControllerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSVideoController>::Declare("VideoController");
    JSClass<JSVideoController>::CustomMethod("start", &JSVideoControllerBinding::Start);
    JSClass<JSVideoController>::CustomMethod("pause", &JSVideoControllerBinding::Pause);
    JSClass<JSVideoController>::CustomMethod("stop", &JSVideoControllerBinding::Stop);
    JSClass<JSVideoController>::CustomMethod("setCurrentTime", &JSVideoControllerBinding::SetCurrentTime);
    JSClass<JSVideoController>::CustomMethod("requestFullscreen", &JSVideoControllerBinding::RequestFullscreen);
    JSClass<JSVideoController>::CustomMethod("exitFullscreen", &JSVideoControllerBinding::ExitFullscreen);
    JSClass<JSVideoController>::CustomMethod("reset", &JSVideoControllerBinding::Reset);
    JSClass<JSVideoController>::Bind(
        globalObj, JSVideoControllerBinding::Constructor, JSVideoControllerBinding::Destructor);
}

void JSVideoControllerBinding::Constructor(const JSCallbackInfo& args)
{
    auto videoController = Referenced::MakeRefPtr<JSVideoControllerBinding>();
    videoController->IncRefCount();
    RefPtr<VideoControllerV2> controller = AceType::MakeRefPtr<VideoControllerV2>();
    videoController->SetController(controller);
    args.SetReturnValue(Referenced::RawPtr(videoController));
}

void JSVideoControllerBinding::Destructor(JSVideoController* videoController)
{
    if (videoController) {
        const auto& controller = videoController->GetController();
        videoController->DecRefCount();
        if (controller) {
            controller->Clear();
        }
    }
}

void JSVideoControllerBinding::Reset(const JSCallbackInfo& args)
{
    const auto& controller = GetController();
    if (controller) {
        controller->Reset();
    }
}

void JSVideoControllerBinding::Start(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    const auto& controller = GetController();
    if (controller) {
#ifdef SUPPORT_JSSTACK
        HiviewDFX::ReportXPowerJsStackSysEvent(args.GetVm(), "STREAM_CHANGE", "SRC=Video");
#endif
        controller->Start();
    }
}

void JSVideoControllerBinding::Pause(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    const auto& controller = GetController();
    if (controller) {
        controller->Pause();
    }
}

void JSVideoControllerBinding::Stop(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    const auto& controller = GetController();
    if (controller) {
        controller->Stop();
    }
}

void JSVideoControllerBinding::SetCurrentTime(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    float value = 0;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], value)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoController set current time with invalid params");
        return;
    }

    SeekMode seekMode = SeekMode::SEEK_PREVIOUS_SYNC;
    if (args.Length() > 1 && args[1]->IsNumber() && args[1]->ToNumber<uint32_t>() < SEEK_MODE.size()) {
        seekMode = SEEK_MODE[args[1]->ToNumber<int32_t>()];
    }

    const auto& controller = GetController();
    if (controller) {
        controller->SeekTo(value, seekMode);
    }
}

void JSVideoControllerBinding::RequestFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    bool landscape = true;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], landscape)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "JSVideoController request full screen with invalid params");
        return;
    }

    const auto& controller = GetController();
    if (controller) {
        controller->RequestFullscreen(landscape);
    }
}

void JSVideoControllerBinding::ExitFullscreen(const JSCallbackInfo& args)
{
    ContainerScope scope(GetInstanceId());
    const auto& controller = GetController();
    if (controller) {
        controller->ExitFullscreen(false);
    }
}

} // namespace OHOS::Ace::Framework

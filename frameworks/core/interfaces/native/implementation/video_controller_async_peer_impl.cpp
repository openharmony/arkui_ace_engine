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

#include "core/interfaces/native/implementation/video_controller_async_peer_impl.h"

#include "base/thread/task_executor.h"
#include "core/common/container_scope.h"
#include "core/components_ng/pattern/video/video_utils.h"
#include "core/interfaces/native/utility/promise_helper.h"

namespace OHOS::Ace::NG::GeneratedModifier {

namespace {
constexpr int32_t VIDEO_ASYNC_ERROR_CODE = 17000100;

StringArray CreateAsyncError(const std::string& reason)
{
    return { std::to_string(VIDEO_ASYNC_ERROR_CODE), reason };
}
} // namespace

void VideoControllerAsyncPeerImpl::TriggerStartAsync(Ark_VMContext vmContext,
    Ark_AsyncWorkerPtr asyncWorker,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);
    if (!controller_) {
        promise->Reject(CreateAsyncError("controller is null"));
        return;
    }

    auto callback = [promise](bool success, const std::string& reason) {
        if (success) {
            promise->Resolve();
        } else {
            promise->Reject(CreateAsyncError(reason));
        }
    };

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), callback]() {
        if (peer->controller_) {
            peer->controller_->Start(std::move(callback));
        } else {
            callback(false, "controller is null");
        }
    });
}

void VideoControllerAsyncPeerImpl::TriggerPauseAsync(Ark_VMContext vmContext,
    Ark_AsyncWorkerPtr asyncWorker,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);
    if (!controller_) {
        promise->Reject(CreateAsyncError("controller is null"));
        return;
    }

    auto callback = [promise](bool success, const std::string& reason) {
        if (success) {
            promise->Resolve();
        } else {
            promise->Reject(CreateAsyncError(reason));
        }
    };

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), callback]() {
        if (peer->controller_) {
            peer->controller_->Pause(std::move(callback));
        } else {
            callback(false, "controller is null");
        }
    });
}

void VideoControllerAsyncPeerImpl::TriggerStopAsync(Ark_VMContext vmContext,
    Ark_AsyncWorkerPtr asyncWorker,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);
    if (!controller_) {
        promise->Reject(CreateAsyncError("controller is null"));
        return;
    }

    auto callback = [promise](bool success, const std::string& reason) {
        if (success) {
            promise->Resolve();
        } else {
            promise->Reject(CreateAsyncError(reason));
        }
    };

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), callback]() {
        if (peer->controller_) {
            peer->controller_->Stop(std::move(callback));
        } else {
            callback(false, "controller is null");
        }
    });
}

void VideoControllerAsyncPeerImpl::TriggerResetAsync(Ark_VMContext vmContext,
    Ark_AsyncWorkerPtr asyncWorker,
    const Callback_Opt_Array_String_Void* outputArgumentForReturningPromise)
{
    CHECK_NULL_VOID(asyncWorker);
    auto promise = std::make_shared<PromiseHelper<Callback_Opt_Array_String_Void>>(
        outputArgumentForReturningPromise);
    if (!controller_) {
        promise->Reject(CreateAsyncError("controller is null"));
        return;
    }

    auto callback = [promise](bool success, const std::string& reason) {
        if (success) {
            promise->Resolve();
        } else {
            promise->Reject(CreateAsyncError(reason));
        }
    };

    promise->StartAsync(vmContext, *asyncWorker, [peer = Claim(this), callback]() {
        if (peer->controller_) {
            peer->controller_->Reset(std::move(callback));
        } else {
            callback(false, "controller is null");
        }
    });
}

void VideoControllerAsyncPeerImpl::TriggerSetCurrentTime(float pos, SeekMode seekMode)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->SeekTo(pos, seekMode);
    }
}

void VideoControllerAsyncPeerImpl::TriggerRequestFullscreen(bool landscape)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->RequestFullscreen(landscape);
    }
}

void VideoControllerAsyncPeerImpl::TriggerExitFullscreen()
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->ExitFullscreen();
    }
}

} // namespace OHOS::Ace::NG::GeneratedModifier

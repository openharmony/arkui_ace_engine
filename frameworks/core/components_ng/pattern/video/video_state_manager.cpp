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

#include "core/components_ng/pattern/video/video_state_manager.h"

#include "core/components_ng/pattern/video/video_state_machine_pattern.h"

namespace OHOS::Ace::NG {

bool VideoStateManager::IsCurrentContext(const VideoStateMachinePattern* pattern) const
{
    auto current = ctx_.Upgrade();
    return AceType::RawPtr(current) == pattern;
}

std::string VideoStateManager::GetStateInfo() const
{
    auto ctx = ctx_.Upgrade();
    bool isFullScreen = false;
    if (ctx) {
        isFullScreen = ctx->IsFullScreen();
    }
    return "state=" + std::string(VideoStateMachine::StateToString(state_)) +
           ", prev=" + std::string(VideoStateMachine::StateToString(previousState_)) +
           ", pending=" + std::string(VideoStateMachine::CommandToString(pendingCommand_)) +
           ", intent=" + std::string(VideoStateMachine::CommandToString(originalIntent_)) +
           ", hasCallback=" + std::to_string(pendingCallback_ != nullptr) +
           ", isFullScreen=" + std::to_string(isFullScreen);
}

void VideoStateManager::HandleStateTransition(VideoPlaybackCommand command,
    VideoControllerAsync::AsyncCommandCallback callback)
{
    TAG_LOGD(AceLogTag::ACE_VIDEO, "[SM] HandleStateTransition: %{public}s, command=%{public}s",
        GetStateInfo().c_str(),
        VideoStateMachine::CommandToString(command));

    if (!ValidateStateTransition(command)) {
        if (callback) {
            callback(false, "invalid state transition");
        }
        return;
    }

    if (!ValidatePendingCommand(command)) {
        if (callback) {
            callback(false, "pending command validation failed");
        }
        return;
    }

    ClearMatchedPending(command);
    DispatchStateHandler(command);
}

bool VideoStateManager::ValidateStateTransition(VideoPlaybackCommand command) const
{
    if (!CanHandleStateTransition(command)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM] State transition rejected: %{public}s, command=%{public}s",
            GetStateInfo().c_str(), VideoStateMachine::CommandToString(command));
        return false;
    }
    return true;
}

bool VideoStateManager::ValidatePendingCommand(VideoPlaybackCommand command) const
{
    if (VideoStateMachine::IsUserOperationCallback(command)) {
        if (pendingCommand_ != VideoPlaybackCommand::NONE && pendingCommand_ != command) {
            TAG_LOGW(AceLogTag::ACE_VIDEO,
                "[SM-PENDING] Callback rejected: expected %{public}s, got %{public}s",
                VideoStateMachine::CommandToString(pendingCommand_),
                VideoStateMachine::CommandToString(command));
            return false;
        }
    } else if (command == VideoPlaybackCommand::COMPLETE) {
        if (pendingCommand_ == VideoPlaybackCommand::STOP ||
            pendingCommand_ == VideoPlaybackCommand::PREPARE ||
            pendingCommand_ == VideoPlaybackCommand::RESET) {
            TAG_LOGW(AceLogTag::ACE_VIDEO,
                "[SM-PENDING] Complete rejected: pending=%{public}s does not allow complete",
                VideoStateMachine::CommandToString(pendingCommand_));
            return false;
        }
    } else if (command == VideoPlaybackCommand::ERROR) {
        if (pendingCommand_ == VideoPlaybackCommand::RESET) {
            TAG_LOGW(AceLogTag::ACE_VIDEO,
                "[SM-PENDING] Error rejected: pending=RESET shields all media events");
            return false;
        }
    }
    return true;
}

void VideoStateManager::ClearMatchedPending(VideoPlaybackCommand command)
{
    if (pendingCommand_ == VideoPlaybackCommand::NONE) {
        return;
    }

    if (pendingCommand_ == command) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] Callback matched: pending=%{public}s, command=%{public}s, originalIntent=%{public}s",
            VideoStateMachine::CommandToString(pendingCommand_),
            VideoStateMachine::CommandToString(command),
            VideoStateMachine::CommandToString(originalIntent_));
        
        pendingCommand_ = VideoPlaybackCommand::NONE;
        
        if (command == VideoPlaybackCommand::PREPARE && originalIntent_ == VideoPlaybackCommand::PLAY) {
            TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] PREPARE with PLAY intent: preserving callback for auto-triggered Play");
            return;
        }
        
        if (command == VideoPlaybackCommand::RESET && originalIntent_ == VideoPlaybackCommand::RESET) {
            TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] RESET with RESET intent: preserving callback for auto-triggered Prepare");
            return;
        }
        
        originalIntent_ = VideoPlaybackCommand::NONE;
        // NOTE: The callback here is always a JS bridge lambda that internally
        // PostTask's to the JS thread (see js_video_controller_async.cpp).
        // Therefore it does NOT execute JS synchronously and cannot re-enter
        // C++ to issue a new command within this call stack.
        if (pendingCallback_) {
            TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] Invoking callback: success=true");
            pendingCallback_(true, "");
            pendingCallback_ = nullptr;
        }
    } else if (command == VideoPlaybackCommand::RESET) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] RESET overriding pending: %{public}s",
            VideoStateMachine::CommandToString(pendingCommand_));
        pendingCommand_ = VideoPlaybackCommand::NONE;
        originalIntent_ = VideoPlaybackCommand::NONE;
        // NOTE: See comment above. Callback is async-posted to JS thread,
        // so no re-entrant C++ command can occur here.
        if (pendingCallback_) {
            pendingCallback_(false, "overridden by reset");
            pendingCallback_ = nullptr;
        }
    }
}

void VideoStateManager::DispatchStateHandler(VideoPlaybackCommand command)
{
    switch (state_) {
        case VideoPlaybackState::CREATED:
            HandleCommandByCreatedState(command);
            break;
        case VideoPlaybackState::PREPARED:
            HandleCommandByPreparedState(command);
            break;
        case VideoPlaybackState::PLAYING:
            HandleCommandByPlayingState(command);
            break;
        case VideoPlaybackState::PAUSED:
            HandleCommandByPausedState(command);
            break;
        case VideoPlaybackState::STOPPED:
            HandleCommandByStoppedState(command);
            break;
        case VideoPlaybackState::COMPLETED:
            HandleCommandByCompletedState(command);
            break;
        case VideoPlaybackState::ERROR:
            HandleCommandByErrorState(command);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM] unknown state: %{public}d", state_);
            break;
    }
}
    
    void VideoStateManager::HandleCommandByCreatedState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PREPARE:
            TransitionTo(VideoPlaybackState::PREPARED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByCreatedState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByPreparedState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PLAY:
            TransitionTo(VideoPlaybackState::PLAYING);
            break;
        case VideoPlaybackCommand::STOP:
            TransitionTo(VideoPlaybackState::STOPPED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByPreparedState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByPlayingState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PAUSE:
            TransitionTo(VideoPlaybackState::PAUSED);
            break;
        case VideoPlaybackCommand::STOP:
            TransitionTo(VideoPlaybackState::STOPPED);
            break;
        case VideoPlaybackCommand::COMPLETE:
            TransitionTo(VideoPlaybackState::COMPLETED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByPlayingState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByPausedState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PLAY:
            TransitionTo(VideoPlaybackState::PLAYING);
            break;
        case VideoPlaybackCommand::STOP:
            TransitionTo(VideoPlaybackState::STOPPED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByPausedState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByStoppedState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PREPARE:
            TransitionTo(VideoPlaybackState::PREPARED);
            break;
        case VideoPlaybackCommand::PLAY:
            TransitionTo(VideoPlaybackState::PREPARED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByStoppedState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByCompletedState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::PLAY:
            TransitionTo(VideoPlaybackState::PLAYING);
            break;
        case VideoPlaybackCommand::STOP:
            TransitionTo(VideoPlaybackState::STOPPED);
            break;
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByCompletedState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

void VideoStateManager::HandleCommandByErrorState(VideoPlaybackCommand command)
{
    switch (command) {
        case VideoPlaybackCommand::ERROR:
            TransitionTo(VideoPlaybackState::ERROR);
            break;
        case VideoPlaybackCommand::RESET:
            TransitionTo(VideoPlaybackState::CREATED);
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: HandleCommandByErrorState reached unexpected command: %{public}s",
                VideoStateMachine::CommandToString(command));
            break;
    }
}

bool VideoStateManager::CanHandleStateTransition(VideoPlaybackCommand command) const
{
    bool result = false;
    switch (state_) {
        case VideoPlaybackState::CREATED:
            result = command == VideoPlaybackCommand::PREPARE ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::PREPARED:
            result = command == VideoPlaybackCommand::PLAY ||
                     command == VideoPlaybackCommand::STOP ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::PLAYING:
            result = command == VideoPlaybackCommand::PAUSE ||
                     command == VideoPlaybackCommand::STOP ||
                     command == VideoPlaybackCommand::COMPLETE ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::PAUSED:
            result = command == VideoPlaybackCommand::PLAY ||
                     command == VideoPlaybackCommand::STOP ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::STOPPED:
            result = command == VideoPlaybackCommand::PREPARE ||
                     command == VideoPlaybackCommand::PLAY ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::COMPLETED:
            result = command == VideoPlaybackCommand::PLAY ||
                     command == VideoPlaybackCommand::STOP ||
                     command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        case VideoPlaybackState::ERROR:
            result = command == VideoPlaybackCommand::ERROR ||
                     command == VideoPlaybackCommand::RESET;
            break;
        default:
            result = false;
            break;
    }
    TAG_LOGD(AceLogTag::ACE_VIDEO, "[SM] CanHandleStateTransition: %{public}s, command=%{public}s, result=%{public}s",
        GetStateInfo().c_str(),
        VideoStateMachine::CommandToString(command),
        result ? "true" : "false");
    return result;
}

bool VideoStateManager::TransitionTo(VideoPlaybackState newState,
    VideoControllerAsync::AsyncCommandCallback callback)
{
    if (!CanTransitionTo(newState)) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM] TransitionTo rejected: %{public}s -> %{public}s",
            GetStateInfo().c_str(), VideoStateMachine::StateToString(newState));
        if (callback) {
            callback(false, "transition not allowed");
        }
        return false;
    }
    
    previousState_ = state_;
    auto oldState = state_;
    state_ = newState;
    
    TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM] TransitionTo: %{public}s -> %{public}s",
        VideoStateMachine::StateToString(oldState), GetStateInfo().c_str());
    
    auto ctx = ctx_.Upgrade();
    if (!ctx) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM] TransitionTo: ctx is null, skipping callback");
        if (callback) {
            callback(false, "pattern context is null");
        }
        return true;
    }
    
    TAG_LOGD(AceLogTag::ACE_VIDEO, "[SM] Triggering On%{public}sStateEntered",
        VideoStateMachine::StateToString(newState));
    switch (newState) {
        case VideoPlaybackState::CREATED:
            ctx->OnCreatedStateEntered();
            break;
        case VideoPlaybackState::PREPARED:
            ctx->OnPreparedStateEntered();
            break;
        case VideoPlaybackState::PLAYING:
            ctx->OnPlayingStateEntered();
            break;
        case VideoPlaybackState::PAUSED:
            ctx->OnPausedStateEntered();
            break;
        case VideoPlaybackState::STOPPED:
            ctx->OnStoppedStateEntered();
            break;
        case VideoPlaybackState::COMPLETED:
            ctx->OnCompletedStateEntered();
            break;
        case VideoPlaybackState::ERROR:
            ctx->OnErrorStateEntered();
            break;
        default:
            TAG_LOGE(AceLogTag::ACE_VIDEO,
                "[SM] FATAL: TransitionTo reached unexpected state: %{public}d", newState);
            break;
    }

    if (callback) {
        callback(true, "");
    }
    
    return true;
}

bool VideoStateManager::CanTransitionTo(VideoPlaybackState newState) const
{
    if (state_ == newState) {
        return true;
    }
    switch (newState) {
        case VideoPlaybackState::PLAYING:
            return state_ == VideoPlaybackState::PREPARED ||
                   state_ == VideoPlaybackState::PAUSED ||
                   state_ == VideoPlaybackState::COMPLETED ||
                   state_ == VideoPlaybackState::STOPPED;
        case VideoPlaybackState::PAUSED:
            return state_ == VideoPlaybackState::PLAYING;
        case VideoPlaybackState::STOPPED:
            return state_ == VideoPlaybackState::PLAYING ||
                   state_ == VideoPlaybackState::PAUSED ||
                   state_ == VideoPlaybackState::PREPARED ||
                   state_ == VideoPlaybackState::COMPLETED;
        case VideoPlaybackState::PREPARED:
            return state_ == VideoPlaybackState::CREATED ||
                   state_ == VideoPlaybackState::STOPPED;
        case VideoPlaybackState::CREATED:
            return true;
        case VideoPlaybackState::COMPLETED:
            return state_ == VideoPlaybackState::PLAYING;
        case VideoPlaybackState::ERROR:
            return true;
        default:
            return false;
    }
}

bool VideoStateManager::CanSetPendingCommand(VideoPlaybackCommand command) const
{
    if (command == VideoPlaybackCommand::NONE) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM-PENDING] Rejected: NONE is not a valid pending command");
        return false;
    }

    if (pendingCommand_ == VideoPlaybackCommand::NONE) {
        return true;
    }

    if (pendingCommand_ == command) {
        return false;
    }

    // RESET cannot override another pending RESET to prevent duplicate resets
    if (command == VideoPlaybackCommand::RESET && pendingCommand_ == VideoPlaybackCommand::RESET) {
        return false;
    }

    return CanOverridePendingCommand(command);
}

void VideoStateManager::SetPendingCommand(VideoPlaybackCommand command,
    VideoControllerAsync::AsyncCommandCallback callback,
    VideoPlaybackCommand originalIntent)
{
    if (command == VideoPlaybackCommand::NONE) {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM-PENDING] Rejected: cannot set NONE as pending command");
        if (callback) {
            callback(false, "NONE is not a valid pending command");
        }
        return;
    }

    if (pendingCommand_ == VideoPlaybackCommand::NONE) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] Set pending: %{public}s",
            GetStateInfo().c_str());
    } else if (pendingCommand_ != command) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] Override: %{public}s -> %{public}s",
            VideoStateMachine::CommandToString(pendingCommand_),
            VideoStateMachine::CommandToString(command));
        // Invoke the old callback with failure to prevent frontend Promise from hanging.
        // NOTE: The callback originates from JS bridge (js_video_controller_async.cpp) and
        // internally PostTask's to the JS thread. It does NOT execute JS synchronously,
        // so it cannot re-enter C++ to issue a new command within this call stack.
        if (pendingCallback_) {
            pendingCallback_(false, "Overridden by " + std::string(VideoStateMachine::CommandToString(command)));
            pendingCallback_ = nullptr;
        }
    }

    pendingCommand_ = command;
    pendingCallback_ = std::move(callback);
    if (originalIntent != VideoPlaybackCommand::NONE) {
        originalIntent_ = originalIntent;
    }
}

void VideoStateManager::ClearPendingCommand(const std::string& reason)
{
    if (pendingCommand_ != VideoPlaybackCommand::NONE) {
        TAG_LOGI(AceLogTag::ACE_VIDEO, "[SM-PENDING] Clear pending: %{public}s, reason=%{public}s",
            GetStateInfo().c_str(), reason.c_str());
        pendingCommand_ = VideoPlaybackCommand::NONE;
        originalIntent_ = VideoPlaybackCommand::NONE;
        // NOTE: See comment in SetPendingCommand. Callback is async-posted to JS,
        // so no synchronous re-entrant C++ command can occur here.
        if (pendingCallback_) {
            pendingCallback_(false, reason);
            pendingCallback_ = nullptr;
        }
    } else {
        TAG_LOGW(AceLogTag::ACE_VIDEO, "[SM-PENDING] Clear pending ignored: no pending command to clear");
    }
}

bool VideoStateManager::CanOverridePendingCommand(VideoPlaybackCommand newCommand) const
{
    // RESET cannot override another pending RESET to prevent duplicate resets
    // which cause player state corruption and lost promises.
    if (newCommand == VideoPlaybackCommand::RESET) {
        return pendingCommand_ != VideoPlaybackCommand::RESET;
    }

    // STOP can override PLAY, PAUSE, and PREPARE.
    // Cannot override STOP or RESET.
    if (newCommand == VideoPlaybackCommand::STOP) {
        return pendingCommand_ == VideoPlaybackCommand::PLAY ||
               pendingCommand_ == VideoPlaybackCommand::PAUSE ||
               pendingCommand_ == VideoPlaybackCommand::PREPARE;
    }

    // PLAY and PAUSE cannot override each other or any other command.
    return false;
}

} // namespace OHOS::Ace::NG

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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_STATE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_STATE_MANAGER_H

#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/video/video_controller_async.h"

namespace OHOS::Ace::NG {

class VideoStateMachinePattern;

enum class VideoPlaybackState {
    CREATED = 0,
    PREPARED,
    PLAYING,
    PAUSED,
    STOPPED,
    COMPLETED,
    ERROR,
};

enum class VideoPlaybackCommand {
    NONE = -1,          // No pending command
    PREPARE = 0,        // PrepareAsync completed
    PLAY,               // Start() called
    PAUSE,              // Pause() called
    STOP,               // Stop() called
    COMPLETE,           // Playback completed (EOS)
    ERROR,              // Error occurred
    RESET,              // Reset state
};

class VideoStateMachine {
public:
    static bool CanPlay(VideoPlaybackState state) {
        return state == VideoPlaybackState::PREPARED ||
               state == VideoPlaybackState::PAUSED ||
               state == VideoPlaybackState::COMPLETED ||
               state == VideoPlaybackState::STOPPED;
    }

    static bool CanPause(VideoPlaybackState state) {
        return state == VideoPlaybackState::PLAYING;
    }

    static bool CanStop(VideoPlaybackState state) {
        return state == VideoPlaybackState::PREPARED ||
               state == VideoPlaybackState::PLAYING ||
               state == VideoPlaybackState::PAUSED ||
               state == VideoPlaybackState::COMPLETED;
    }

    static bool CanSeek(VideoPlaybackState state) {
        return state == VideoPlaybackState::PREPARED ||
               state == VideoPlaybackState::PLAYING ||
               state == VideoPlaybackState::PAUSED ||
               state == VideoPlaybackState::COMPLETED;
    }

    static bool CanPrepare(VideoPlaybackState state) {
        return state == VideoPlaybackState::CREATED ||
               state == VideoPlaybackState::STOPPED;
    }

    static bool IsPlayingState(VideoPlaybackState state) {
        return state == VideoPlaybackState::PLAYING;
    }

    static bool IsPausedState(VideoPlaybackState state) {
        return state == VideoPlaybackState::PAUSED;
    }

    static bool IsStoppedState(VideoPlaybackState state) {
        return state == VideoPlaybackState::STOPPED;
    }

    static bool IsPreparedState(VideoPlaybackState state) {
        return state == VideoPlaybackState::PREPARED;
    }

    static bool IsCreatedState(VideoPlaybackState state) {
        return state == VideoPlaybackState::CREATED;
    }

    static bool IsCompletedState(VideoPlaybackState state) {
        return state == VideoPlaybackState::COMPLETED;
    }

    static bool IsErrorState(VideoPlaybackState state) {
        return state == VideoPlaybackState::ERROR;
    }

    static bool IsActiveState(VideoPlaybackState state) {
        return state == VideoPlaybackState::PREPARED ||
               state == VideoPlaybackState::PLAYING ||
               state == VideoPlaybackState::PAUSED ||
               state == VideoPlaybackState::COMPLETED;
    }

    static bool IsUserOperationCallback(VideoPlaybackCommand command) {
        return command == VideoPlaybackCommand::PLAY ||
               command == VideoPlaybackCommand::PAUSE ||
               command == VideoPlaybackCommand::STOP ||
               command == VideoPlaybackCommand::PREPARE;
    }

    static bool IsMediaSpontaneousEvent(VideoPlaybackCommand command) {
        return command == VideoPlaybackCommand::COMPLETE ||
               command == VideoPlaybackCommand::ERROR;
    }
    static const char* StateToString(VideoPlaybackState state) {
        switch (state) {
            case VideoPlaybackState::CREATED: return "CREATED";
            case VideoPlaybackState::PREPARED: return "PREPARED";
            case VideoPlaybackState::PLAYING: return "PLAYING";
            case VideoPlaybackState::PAUSED: return "PAUSED";
            case VideoPlaybackState::STOPPED: return "STOPPED";
            case VideoPlaybackState::COMPLETED: return "COMPLETED";
            case VideoPlaybackState::ERROR: return "ERROR";
            default: return "UNKNOWN";
        }
    }

    static const char* CommandToString(VideoPlaybackCommand command) {
        switch (command) {
            case VideoPlaybackCommand::NONE: return "NONE";
            case VideoPlaybackCommand::PREPARE: return "PREPARE";
            case VideoPlaybackCommand::PLAY: return "PLAY";
            case VideoPlaybackCommand::PAUSE: return "PAUSE";
            case VideoPlaybackCommand::STOP: return "STOP";
            case VideoPlaybackCommand::COMPLETE: return "COMPLETE";
            case VideoPlaybackCommand::ERROR: return "ERROR";
            case VideoPlaybackCommand::RESET: return "RESET";
            default: return "UNKNOWN";
        }
    }
};

class VideoStateManager : public AceType {
    DECLARE_ACE_TYPE(VideoStateManager, AceType);

public:
    explicit VideoStateManager(WeakPtr<VideoStateMachinePattern> ctx) : ctx_(std::move(ctx)) {}
    ~VideoStateManager() override = default;

    void UpdateContext(const WeakPtr<VideoStateMachinePattern>& ctx) { ctx_ = ctx; }

    bool IsCurrentContext(const VideoStateMachinePattern* pattern) const;

    VideoPlaybackState GetCurrentState() const { return state_; }
    VideoPlaybackState GetPreviousState() const { return previousState_; }
    bool CanTransitionTo(VideoPlaybackState newState) const;

    std::string GetStateInfo() const;

    /**
     * @brief Handle a playback command based on current state.
     *
     * This is the primary entry for state-driven command processing.
     * It checks if the command is valid in the current state, performs
     * the state transition, and triggers the corresponding callback.
     *
     * @param command The command to handle
     * @param callback Optional callback to invoke after state transition completes
     */
void HandleStateTransition(VideoPlaybackCommand command,
        VideoControllerAsync::AsyncCommandCallback callback = nullptr);

    bool CanHandleStateTransition(VideoPlaybackCommand command) const;

    bool TransitionTo(VideoPlaybackState newState,
        VideoControllerAsync::AsyncCommandCallback callback = nullptr);

    // Helper methods for state checking
    bool IsPlaying() const { return state_ == VideoPlaybackState::PLAYING; }
    bool IsPaused() const { return state_ == VideoPlaybackState::PAUSED; }
    bool IsStopped() const { return state_ == VideoPlaybackState::STOPPED; }
    bool IsPrepared() const { return state_ == VideoPlaybackState::PREPARED; }
    bool IsCreated() const { return state_ == VideoPlaybackState::CREATED; }
    bool IsCompleted() const { return state_ == VideoPlaybackState::COMPLETED; }
    bool IsError() const { return state_ == VideoPlaybackState::ERROR; }
    bool IsActive() const {
        return state_ == VideoPlaybackState::PREPARED ||
               state_ == VideoPlaybackState::PLAYING ||
               state_ == VideoPlaybackState::PAUSED ||
               state_ == VideoPlaybackState::COMPLETED;
    }

    // Pending command management
    VideoPlaybackCommand GetPendingCommand() const { return pendingCommand_; }
    VideoPlaybackCommand GetOriginalIntent() const { return originalIntent_; }
    VideoControllerAsync::AsyncCommandCallback ConsumePendingCallback()
    {
        return std::move(pendingCallback_);
    }
    bool HasPendingCommand() const { return pendingCommand_ != VideoPlaybackCommand::NONE; }
    bool IsBusy() const { return HasPendingCommand(); }

    bool CanSetPendingCommand(VideoPlaybackCommand command) const;

    /**
     * @brief Set a pending command to track async operations.
     *
     * Must be called right before the actual media command (Play/Pause/Stop).
     * Precede with CanSetPendingCommand() for early validation.
     *
     * @param command The command to set as pending (current step)
     * @param callback Optional callback to invoke when the original intent completes
     * @param originalIntent The user's original operation intent (PLAY/RESET/PREPARE/etc.)
     */
    void SetPendingCommand(VideoPlaybackCommand command,
        VideoControllerAsync::AsyncCommandCallback callback = nullptr,
        VideoPlaybackCommand originalIntent = VideoPlaybackCommand::NONE);

    void ClearPendingCommand();

    /**
     * @brief Check if a new command can override current pending command.
     *
     * Rules:
     * - STOP/RESET can override any command
     * - PLAY and PAUSE can override each other
     * - Same command cannot override itself
     * - Other combinations: reject
     *
     * @param newCommand The new command to check
     * @return true if can override
     */
    bool CanOverridePendingCommand(VideoPlaybackCommand newCommand) const;

private:
    bool ValidateStateTransition(VideoPlaybackCommand command) const;
    bool ValidatePendingCommand(VideoPlaybackCommand command) const;
    void ClearMatchedPending(VideoPlaybackCommand command);
    void DispatchStateHandler(VideoPlaybackCommand command);

    void HandleCommandByCreatedState(VideoPlaybackCommand command);
    void HandleCommandByPreparedState(VideoPlaybackCommand command);
    void HandleCommandByPlayingState(VideoPlaybackCommand command);
    void HandleCommandByPausedState(VideoPlaybackCommand command);
    void HandleCommandByStoppedState(VideoPlaybackCommand command);
    void HandleCommandByCompletedState(VideoPlaybackCommand command);
    void HandleCommandByErrorState(VideoPlaybackCommand command);

    WeakPtr<VideoStateMachinePattern> ctx_;
    VideoPlaybackState state_ = VideoPlaybackState::CREATED;
    VideoPlaybackState previousState_ = VideoPlaybackState::CREATED;
    VideoPlaybackCommand pendingCommand_ = VideoPlaybackCommand::NONE;
    VideoPlaybackCommand originalIntent_ = VideoPlaybackCommand::NONE;
    VideoControllerAsync::AsyncCommandCallback pendingCallback_ = nullptr;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_VIDEO_VIDEO_STATE_MANAGER_H

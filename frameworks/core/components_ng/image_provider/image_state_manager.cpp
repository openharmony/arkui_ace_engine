/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/image_provider/image_state_manager.h"

#include "core/components_ng/image_provider/image_loading_context.h"

namespace OHOS::Ace::NG {

ImageLoadingState ImageStateManager::GetCurrentState()
{
    return state_;
}

void ImageStateManager::HandleCommand(ImageLoadingCommand command)
{
    switch (state_) {
        case ImageLoadingState::UNLOADED:
            HandleCommandByUnloadedState(command);
            break;
        case ImageLoadingState::DATA_LOADING:
            HandleCommandByDataLoadingState(command);
            break;
        case ImageLoadingState::DATA_READY:
            HandleCommandByDataReadyState(command);
            break;
        case ImageLoadingState::MAKE_CANVAS_IMAGE:
            HandleCommandByMakeCanvasImageState(command);
            break;
        case ImageLoadingState::LOAD_SUCCESS:
            HandleCommandByLoadSuccessState(command);
            break;
        case ImageLoadingState::LOAD_FAIL:
            HandleCommandByLoadFailState(command);
            break;
        default:
            TAG_LOGW(AceLogTag::ACE_IMAGE, "unknown command: %{public}d", command);
            break;
    }
}

#define CASE_OF_STATE_TRANSITION(command, nextState, nextStateName) \
    case ImageLoadingCommand::command: {                            \
        auto ctx = ctx_.Upgrade();                                  \
        CHECK_NULL_VOID(ctx);                                       \
        state_ = ImageLoadingState::nextState;                      \
        ctx->On##nextStateName();                                   \
        break;                                                      \
    }

#define DEFAULT_CASE_OF_STATE_TRANSITION()    \
    case ImageLoadingCommand::RESET_STATE: {  \
        auto ctx = ctx_.Upgrade();            \
        CHECK_NULL_VOID(ctx);                 \
        state_ = ImageLoadingState::UNLOADED; \
        ctx->OnUnloaded();                    \
        break;                                \
    }                                         \
    default:                                  \
        break;

void ImageStateManager::HandleCommandByUnloadedState(ImageLoadingCommand command)
{
    switch (command) {
        CASE_OF_STATE_TRANSITION(LOAD_DATA, DATA_LOADING, DataLoading);
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::HandleCommandByDataLoadingState(ImageLoadingCommand command)
{
    switch (command) {
        CASE_OF_STATE_TRANSITION(LOAD_DATA_SUCCESS, DATA_READY, DataReady);
        CASE_OF_STATE_TRANSITION(LOAD_FAIL, LOAD_FAIL, LoadFail);
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::HandleCommandByDataReadyState(ImageLoadingCommand command)
{
    switch (command) {
        CASE_OF_STATE_TRANSITION(MAKE_CANVAS_IMAGE, MAKE_CANVAS_IMAGE, MakeCanvasImage);
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::HandleCommandByMakeCanvasImageState(ImageLoadingCommand command)
{
    switch (command) {
        CASE_OF_STATE_TRANSITION(MAKE_CANVAS_IMAGE_SUCCESS, LOAD_SUCCESS, LoadSuccess);
        CASE_OF_STATE_TRANSITION(LOAD_FAIL, LOAD_FAIL, LoadFail);
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::HandleCommandByLoadSuccessState(ImageLoadingCommand command)
{
    switch (command) {
        CASE_OF_STATE_TRANSITION(MAKE_CANVAS_IMAGE, MAKE_CANVAS_IMAGE, MakeCanvasImage);
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::HandleCommandByLoadFailState(ImageLoadingCommand command)
{
    switch (command) {
        DEFAULT_CASE_OF_STATE_TRANSITION();
    }
}

void ImageStateManager::SetState(ImageLoadingState state)
{
    state_ = state;
}
} // namespace OHOS::Ace::NG

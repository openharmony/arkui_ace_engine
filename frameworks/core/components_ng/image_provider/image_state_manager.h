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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_STATE_MANAGER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_STATE_MANAGER_H

#include <functional>
#include <utility>

#include "base/log/log_wrapper.h"
#include "base/memory/ace_type.h"

namespace OHOS::Ace::NG {

enum class ImageLoadingState {
    UNLOADED = 0,
    DATA_LOADING,
    DATA_READY,
    MAKE_CANVAS_IMAGE,
    LOAD_SUCCESS,
    LOAD_FAIL,
};

enum class ImageLoadingCommand {
    LOAD_DATA = 0,
    LOAD_FAIL,
    LOAD_DATA_SUCCESS,
    MAKE_CANVAS_IMAGE,
    MAKE_CANVAS_IMAGE_SUCCESS,
    RETRY_LOADING,
    RESET_STATE,
};

class ImageLoadingContext;

class ImageStateManager : public AceType {
    DECLARE_ACE_TYPE(ImageStateManager, AceType);

public:
    explicit ImageStateManager(WeakPtr<ImageLoadingContext> ctx) : ctx_(std::move(ctx)) {}
    ~ImageStateManager() override = default;

    ImageLoadingState GetCurrentState();
    void HandleCommand(ImageLoadingCommand command);
    void SetState(ImageLoadingState state);

private:
    void HandleCommandByUnloadedState(ImageLoadingCommand command);
    void HandleCommandByDataLoadingState(ImageLoadingCommand command);
    void HandleCommandByDataReadyState(ImageLoadingCommand command);
    void HandleCommandByMakeCanvasImageState(ImageLoadingCommand command);
    void HandleCommandByLoadSuccessState(ImageLoadingCommand command);
    void HandleCommandByLoadFailState(ImageLoadingCommand command);

    WeakPtr<ImageLoadingContext> ctx_;
    ImageLoadingState state_ = ImageLoadingState::UNLOADED;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_IMAGE_PROVIDER_IMAGE_STATE_MANAGER_H

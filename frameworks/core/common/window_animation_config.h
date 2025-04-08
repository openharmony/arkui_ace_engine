/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_ANIMATION_CONFIG_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_ANIMATION_CONFIG_H

namespace OHOS::Ace {
enum class WindowSizeChangeReason : uint32_t {
    UNDEFINED = 0,
    MAXIMIZE,
    RECOVER,
    ROTATION,
    DRAG,
    DRAG_START,
    DRAG_END,
    RESIZE,
    RESIZE_WITH_ANIMATION,
    MOVE,
    HIDE,
    TRANSFORM,
    CUSTOM_ANIMATION,
    FULL_TO_SPLIT,
    SPLIT_TO_FULL,
    FULL_TO_FLOATING,
    FLOATING_TO_FULL,
    PIP_START,
    PIP_SHOW,
    PIP_AUTO_START,
    PIP_RATIO_CHANGE,
    PIP_RESTORE,
    UPDATE_DPI_SYNC,
    DRAG_MOVE,
    AVOID_AREA_CHANGE,
    MAXIMIZE_TO_SPLIT,
    SPLIT_TO_MAXIMIZE,
    PAGE_ROTATION,
    SPLIT_DRAG_START,
    SPLIT_DRAG,
    SPLIT_DRAG_END,
    END,
};
} // namespace OHOS::Ace

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMMON_WINDOW_ANIMATION_CONFIG_H
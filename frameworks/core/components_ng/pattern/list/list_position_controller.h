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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_POSITION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_POSITION_CONTROLLER_H

#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

namespace OHOS::Ace::NG {
class ACE_EXPORT ListPositionController : public ScrollableController {
    DECLARE_ACE_TYPE(ListPositionController, ScrollableController);

public:
    ListPositionController() = default;
    ~ListPositionController() override = default;

    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const override;
    ListItemGroupIndex GetItemIndexInGroup(double x, double y) const override;

    void JumpToItemInGroup(int32_t index, int32_t indexInGroup, bool smooth,
        ScrollAlign align, int32_t source) override;

    void CloseAllSwipeActions(OnFinishFunc&& onFinishCallback) override;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_POSITION_CONTROLLER_H

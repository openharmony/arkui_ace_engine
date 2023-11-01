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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_POSITION_CONTROLLER_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_LIST_LIST_POSITION_CONTROLLER_H

#include <functional>

#include "core/components_ng/pattern/scrollable/scrollable_controller.h"

namespace OHOS::Ace::NG {

class ACE_EXPORT ListPositionController : public ScrollableController {
    DECLARE_ACE_TYPE(ListPositionController, ScrollableController);

public:
    ListPositionController() = default;
    ~ListPositionController() override = default;

    void ScrollBy(double pixelX, double pixelY, bool smooth) override;
    void ScrollToEdge(ScrollEdgeType scrollEdgeType, bool smooth) override;
    void ScrollPage(bool reverse, bool smooth) override;
    void JumpTo(int32_t index, bool smooth, ScrollAlign align, int32_t source) override;
    bool IsAtEnd() const override;
    Rect GetItemRect(int32_t index) const override;
    Rect GetItemRectInGroup(int32_t index, int32_t indexInGroup) const override;
};

} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERN_SCROLL_SCROLL_POSITION_CONTROLLER_H

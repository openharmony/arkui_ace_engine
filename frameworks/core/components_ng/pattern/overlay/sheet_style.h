/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H
#define FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H

#include <optional>

#include "base/geometry/dimension.h"
#include "core/components/common/properties/color.h"

namespace OHOS::Ace::NG {
const Dimension SHEET_RADIUS = 32.0_vp;
const Dimension SHEET_DRAG_BAR_WIDTH = 64.0_vp;
const Dimension SHEET_DRAG_BAR_HEIGHT = 24.0_vp;
const Dimension SHEET_BLANK_MINI_HEIGHT = 8.0_vp;
const double SHEET_VELOCITY_THRESHOLD = 1000.0; // Move 1000px per second.

enum SheetMode {
    MEDIUM,
    LARGE,
};

struct SheetStyle {
    std::optional<Dimension> height;
    std::optional<SheetMode> sheetMode;
    std::optional<bool> showDragBar;
    std::optional<Color> backgroundColor;
    std::optional<Color> backgroundMask;

    bool operator==(const SheetStyle& sheetStyle) const
    {
        return !(height != sheetStyle.height || sheetMode != sheetStyle.sheetMode ||
                 showDragBar != sheetStyle.showDragBar || backgroundColor != sheetStyle.backgroundColor ||
                 backgroundMask != sheetStyle.backgroundMask);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H

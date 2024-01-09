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
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
namespace OHOS::Ace::NG {
constexpr float SHEET_VELOCITY_THRESHOLD = 1000.0f;
constexpr float CURVE_MASS = 1.0f;
constexpr float CURVE_STIFFNESS = 328.0f;
constexpr float CURVE_DAMPING = 36.0f;
constexpr float MEDIUM_SIZE = 0.6f;
constexpr float MEDIUM_SIZE_PRE = 0.5f;
constexpr float POPUP_LARGE_SIZE = 0.9f;
enum SheetMode {
    MEDIUM,
    LARGE,
    AUTO,
};

enum SheetType {
    SHEET_BOTTOM,
    SHEET_CENTER,
    SHEET_POPUP,
    SHEET_BOTTOMLANDSPACE,
    SHEET_BOTTOM_FREE_WINDOW,
};

struct SheetHeight {
    std::optional<Dimension> height;
    std::optional<SheetMode> sheetMode;

    bool operator==(const SheetHeight& sheetHeight) const
    {
        return (height == sheetHeight.height && sheetMode == sheetHeight.sheetMode);
    }
};

struct SheetStyle {
    std::optional<Dimension> height;
    std::optional<SheetMode> sheetMode;
    std::optional<bool> showDragBar;
    std::optional<bool> showCloseIcon;
    std::optional<bool> isTitleBuilder;
    std::optional<SheetType> sheetType;
    std::optional<Color> backgroundColor;
    std::optional<Color> maskColor;
    std::optional<BlurStyleOption> backgroundBlurStyle;
    std::optional<std::string> sheetTitle;
    std::optional<std::string> sheetSubtitle;
    std::vector<SheetHeight> detents;
    std::optional<bool> interactive;

    bool operator==(const SheetStyle& sheetStyle) const
    {
        return (height == sheetStyle.height && sheetMode == sheetStyle.sheetMode &&
                showDragBar == sheetStyle.showDragBar && showCloseIcon == sheetStyle.showCloseIcon &&
                isTitleBuilder == sheetStyle.isTitleBuilder && sheetType == sheetStyle.sheetType &&
                backgroundColor == sheetStyle.backgroundColor && maskColor == sheetStyle.maskColor &&
                detents == sheetStyle.detents && backgroundBlurStyle == sheetStyle.backgroundBlurStyle &&
                sheetTitle == sheetStyle.sheetTitle && sheetSubtitle == sheetStyle.sheetSubtitle &&
                interactive == sheetStyle.interactive);
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H

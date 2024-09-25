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
    SHEET_BOTTOM_OFFSET,
};

struct SheetKey {
    SheetKey() {}
    explicit SheetKey(int32_t inputTargetId) : targetId(inputTargetId) {}
    SheetKey(bool hasValidTarget, int32_t inputContentId, int32_t inputTargetId)
        : hasValidTargetNode(hasValidTarget), contentId(inputContentId), targetId(inputTargetId)
    {
        isStartUpByUIContext = true;
    }

    bool operator==(const SheetKey& other) const
    {
        return isStartUpByUIContext == other.isStartUpByUIContext &&
            hasValidTargetNode == other.hasValidTargetNode &&
            contentId == other.contentId && targetId == other.targetId;
    }

    bool isStartUpByUIContext = false;  // Indicates whether the sheet is started by UIContext
    bool hasValidTargetNode = true;     // If sheet was start-up by UIContext and without targetId, this flag is FALSE
    int32_t contentId = -1;             // Indicates the uniqueID of componentContent when isStartUpByUIContext is TRUE
    int32_t targetId = -1;
};

struct SheetKeyHash {
    size_t operator()(const SheetKey& sheetKey) const
    {
        return sheetKey.isStartUpByUIContext ? sheetKey.contentId : sheetKey.targetId;
    }
};

enum SheetLevel {
    OVERLAY,
    EMBEDDED,
};

enum ScrollSizeMode {
    FOLLOW_DETENT,
    CONTINUOUS,
};

struct SheetHeight {
    std::optional<Dimension> height;
    std::optional<SheetMode> sheetMode;

    bool operator==(const SheetHeight& sheetHeight) const
    {
        return (height == sheetHeight.height && sheetMode == sheetHeight.sheetMode);
    }

    bool operator!=(const SheetHeight& sheetHeight) const
    {
        return !(*this == sheetHeight);
    }
};

enum class SheetKeyboardAvoidMode {
    NONE,
    TRANSLATE_AND_RESIZE,
    RESIZE_ONLY,
    TRANSLATE_AND_SCROLL,
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
    std::optional<OffsetF> bottomOffset;
    std::optional<BlurStyleOption> backgroundBlurStyle;
    std::optional<std::string> sheetTitle;
    std::optional<std::string> sheetSubtitle;
    std::vector<SheetHeight> detents;
    std::optional<bool> interactive;
    std::optional<bool> showInPage;
    std::optional<ScrollSizeMode> scrollSizeMode;
    std::optional<SheetKeyboardAvoidMode> sheetKeyboardAvoidMode;
    std::optional<NG::BorderWidthProperty> borderWidth; // border width
    std::optional<NG::BorderColorProperty> borderColor; // border color
    std::optional<NG::BorderStyleProperty> borderStyle;  // border style
    std::optional<Shadow> shadow;
    std::optional<Dimension> width;
    std::optional<int32_t> instanceId; // uiContext instanceId

    bool operator==(const SheetStyle& sheetStyle) const
    {
        return (height == sheetStyle.height && sheetMode == sheetStyle.sheetMode &&
                showDragBar == sheetStyle.showDragBar && showCloseIcon == sheetStyle.showCloseIcon &&
                isTitleBuilder == sheetStyle.isTitleBuilder && sheetType == sheetStyle.sheetType &&
                backgroundColor == sheetStyle.backgroundColor && maskColor == sheetStyle.maskColor &&
                detents == sheetStyle.detents && backgroundBlurStyle == sheetStyle.backgroundBlurStyle &&
                sheetTitle == sheetStyle.sheetTitle && sheetSubtitle == sheetStyle.sheetSubtitle &&
                interactive == sheetStyle.interactive && showInPage == sheetStyle.showInPage &&
                borderWidth == sheetStyle.borderWidth && borderColor == sheetStyle.borderColor &&
                borderStyle == sheetStyle.borderStyle && shadow == sheetStyle.shadow && width == sheetStyle.width &&
                instanceId == sheetStyle.instanceId && scrollSizeMode == sheetStyle.scrollSizeMode &&
                sheetKeyboardAvoidMode == sheetStyle.sheetKeyboardAvoidMode && bottomOffset == sheetStyle.bottomOffset);
    }

    void PartialUpdate(const SheetStyle& sheetStyle)
    {
        if (sheetStyle.height.has_value() && !sheetStyle.sheetMode.has_value()) {
            height = sheetStyle.height;
            sheetMode.reset();
        } else if (!sheetStyle.height.has_value() && sheetStyle.sheetMode.has_value()) {
            sheetMode = sheetStyle.sheetMode;
            height.reset();
        } else {
            sheetMode = sheetStyle.sheetMode.has_value() ? sheetStyle.sheetMode : sheetMode;
        }
        showDragBar = sheetStyle.showDragBar.has_value() ? sheetStyle.showDragBar : showDragBar;
        showCloseIcon = sheetStyle.showCloseIcon.has_value() ? sheetStyle.showCloseIcon : showCloseIcon;
        isTitleBuilder = sheetStyle.isTitleBuilder.has_value() ? sheetStyle.isTitleBuilder : isTitleBuilder;
        sheetType = sheetStyle.sheetType.has_value() ? sheetStyle.sheetType : sheetType;
        backgroundColor = sheetStyle.backgroundColor.has_value() ? sheetStyle.backgroundColor : backgroundColor;
        maskColor = sheetStyle.maskColor.has_value() ? sheetStyle.maskColor : maskColor;
        backgroundBlurStyle = sheetStyle.backgroundBlurStyle.has_value() ?
            sheetStyle.backgroundBlurStyle : backgroundBlurStyle;
        sheetTitle = sheetStyle.sheetTitle.has_value() ? sheetStyle.sheetTitle : sheetTitle;
        sheetSubtitle = sheetStyle.sheetSubtitle.has_value() ? sheetStyle.sheetSubtitle : sheetSubtitle;
        detents = !sheetStyle.detents.empty() ? sheetStyle.detents : detents;
        interactive = sheetStyle.interactive.has_value() ? sheetStyle.interactive : interactive;
        scrollSizeMode = sheetStyle.scrollSizeMode.has_value() ? sheetStyle.scrollSizeMode : scrollSizeMode;
        sheetKeyboardAvoidMode =
            sheetStyle.sheetKeyboardAvoidMode.has_value() ? sheetStyle.sheetKeyboardAvoidMode : sheetKeyboardAvoidMode;
        borderWidth = sheetStyle.borderWidth.has_value() ? sheetStyle.borderWidth : borderWidth;
        borderColor = sheetStyle.borderColor.has_value() ? sheetStyle.borderColor : borderColor;
        borderStyle = sheetStyle.borderStyle.has_value() ? sheetStyle.borderStyle : borderStyle;
        shadow = sheetStyle.shadow.has_value() ? sheetStyle.shadow : shadow;
        width = sheetStyle.width.has_value() ? sheetStyle.width : width;
        bottomOffset = sheetStyle.bottomOffset.has_value() ? sheetStyle.bottomOffset : bottomOffset;
    }
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H

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
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/color.h"
#include "core/components/common/properties/decoration.h"
#include "core/components/common/properties/placement.h"
#include "core/components_ng/pattern/overlay/modal_style.h"
#include "core/components_ng/pattern/overlay/sheet_theme.h"
#include "core/common/resource/resource_object.h"

#define ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(name)                                   \
public:                                                                             \
    void Set##name##ResObj(RefPtr<ResourceObject>& obj) { prop##name##Obj_ = obj; }       \
    const RefPtr<ResourceObject>& Get##name##ResObj() const { return prop##name##Obj_; }  \
private:                                                                            \
    RefPtr<ResourceObject> prop##name##Obj_

namespace OHOS::Ace::NG {
constexpr float SHEET_VELOCITY_THRESHOLD = 1000.0f;
constexpr float CURVE_MASS = 1.0f;
constexpr float CURVE_STIFFNESS = 328.0f;
constexpr float CURVE_DAMPING = 36.0f;
constexpr float MEDIUM_SIZE = 0.6f;
constexpr float MEDIUM_SIZE_PRE = 0.5f;
constexpr float POPUP_LARGE_SIZE = 0.9f;
constexpr int32_t SHEET_ANIMATION_DURATION = 580;

enum SheetMode {
    MEDIUM,
    LARGE,
    AUTO,
};

enum SheetType {
    SHEET_BOTTOM,
    SHEET_CENTER,
    SHEET_POPUP,
    SHEET_SIDE = 3,
    SHEET_CONTENT_COVER = 4,
    SHEET_BOTTOMLANDSPACE,
    SHEET_BOTTOM_FREE_WINDOW,
    SHEET_BOTTOM_OFFSET,
};

enum class SheetAccessibilityDetents {
    HIGH = 0,
    MEDIUM,
    LOW,
};

enum class SheetArrowPosition {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT,
    LEFT_TOP,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_BOTTOM,
    NONE
};

enum class SheetEffectEdge {
    NONE = 0,
    START = 1,
    END = 2,
    ALL = 3,
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

struct SheetPopupInfo {
    Placement finalPlacement = Placement::NONE;
    bool placementOnTarget = true;
    bool placementRechecked = false;
    bool showArrow = true;
    float arrowOffsetX = 0.f;
    float arrowOffsetY = 0.f;
    SheetArrowPosition arrowPosition = SheetArrowPosition::NONE;
    float sheetOffsetX = 0.f;
    float sheetOffsetY = 0.f;
    bool keyboardShow = false;

    void Reset()
    {
        finalPlacement = Placement::NONE;
        placementOnTarget = true;
        placementRechecked = false;
        showArrow = true;
        arrowOffsetX = 0.f;
        arrowOffsetY = 0.f;
        arrowPosition = SheetArrowPosition::NONE;
        sheetOffsetX = 0.f;
        sheetOffsetY = 0.f;
        keyboardShow = false;
    }
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
    POPUP_SHEET,
};

struct SheetStyle {
    SheetHeight sheetHeight;
    std::optional<bool> showDragBar;
    std::optional<bool> enableFloatingDragBar;
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
    std::optional<bool> enableHoverMode;
    std::optional<HoverModeAreaType> hoverModeArea;
    std::optional<SheetEffectEdge> sheetEffectEdge;
    std::optional<NG::BorderRadiusProperty> radius;
    std::optional<SheetHeight> detentSelection;
    std::optional<Placement> placement;
    std::optional<bool> placementOnTarget;
    std::optional<bool> showInSubWindow;
    std::optional<ModalTransition> modalTransition;

    bool operator==(const SheetStyle& sheetStyle) const
    {
        return (sheetHeight == sheetStyle.sheetHeight &&
                enableFloatingDragBar == sheetStyle.enableFloatingDragBar &&
                showDragBar == sheetStyle.showDragBar && showCloseIcon == sheetStyle.showCloseIcon &&
                isTitleBuilder == sheetStyle.isTitleBuilder && sheetType == sheetStyle.sheetType &&
                backgroundColor == sheetStyle.backgroundColor && maskColor == sheetStyle.maskColor &&
                detents == sheetStyle.detents && backgroundBlurStyle == sheetStyle.backgroundBlurStyle &&
                sheetTitle == sheetStyle.sheetTitle && sheetSubtitle == sheetStyle.sheetSubtitle &&
                interactive == sheetStyle.interactive && showInPage == sheetStyle.showInPage &&
                borderWidth == sheetStyle.borderWidth && borderColor == sheetStyle.borderColor &&
                borderStyle == sheetStyle.borderStyle && shadow == sheetStyle.shadow && width == sheetStyle.width &&
                instanceId == sheetStyle.instanceId && scrollSizeMode == sheetStyle.scrollSizeMode &&
                sheetKeyboardAvoidMode == sheetStyle.sheetKeyboardAvoidMode &&
                bottomOffset == sheetStyle.bottomOffset && enableHoverMode == sheetStyle.enableHoverMode &&
                hoverModeArea == sheetStyle.hoverModeArea && radius == sheetStyle.radius &&
                detentSelection == sheetStyle.detentSelection && sheetEffectEdge == sheetStyle.sheetEffectEdge &&
                placement == sheetStyle.placement && placementOnTarget == sheetStyle.placementOnTarget &&
                showInSubWindow == sheetStyle.showInSubWindow && modalTransition == sheetStyle.modalTransition);
    }

    void PartialUpdate(const SheetStyle& sheetStyle)
    {
        if (sheetStyle.sheetHeight.height.has_value() && !sheetStyle.sheetHeight.sheetMode.has_value()) {
            sheetHeight.height = sheetStyle.sheetHeight.height;
            sheetHeight.sheetMode.reset();
        } else if (!sheetStyle.sheetHeight.height.has_value() && sheetStyle.sheetHeight.sheetMode.has_value()) {
            sheetHeight.sheetMode = sheetStyle.sheetHeight.sheetMode;
            sheetHeight.height.reset();
        } else {
            sheetHeight.sheetMode = sheetStyle.sheetHeight.sheetMode.has_value() ?
                sheetStyle.sheetHeight.sheetMode : sheetHeight.sheetMode;
        }
        showDragBar = sheetStyle.showDragBar.has_value() ? sheetStyle.showDragBar : showDragBar;
        enableFloatingDragBar = sheetStyle.enableFloatingDragBar.has_value() ?
            sheetStyle.enableFloatingDragBar : enableFloatingDragBar;
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
        enableHoverMode = sheetStyle.enableHoverMode.has_value() ? sheetStyle.enableHoverMode : enableHoverMode;
        hoverModeArea = sheetStyle.hoverModeArea.has_value() ? sheetStyle.hoverModeArea : hoverModeArea;
        radius = sheetStyle.radius.has_value() ? sheetStyle.radius : radius;
        detentSelection = sheetStyle.detentSelection.has_value() ? sheetStyle.detentSelection : detentSelection;
        sheetEffectEdge = sheetStyle.sheetEffectEdge.has_value() ? sheetStyle.sheetEffectEdge : sheetEffectEdge;
        placement = sheetStyle.placement.has_value() ? sheetStyle.placement : placement;
        placementOnTarget = sheetStyle.placementOnTarget.has_value() ?
            sheetStyle.placementOnTarget : placementOnTarget;
        modalTransition = sheetStyle.modalTransition.has_value() ? sheetStyle.modalTransition : modalTransition;
    }

    // Register the set/get method of the resource.
    void SetDetentsResObjs(std::vector<RefPtr<ResourceObject>>&& resObjs)
    {
        detentsObj_ = std::move(resObjs);
    }

    const std::vector<RefPtr<ResourceObject>>& GetDetentsResObjs() const
    {
        return detentsObj_;
    }
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(SheetHeight);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(DetentSelection);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(SheetWidth);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(ShowClose);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(MaskColor);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(MainTitle);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(SubTitle);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(BorderWidth);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(BorderColor);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(Radius);
    ACE_SHEET_CREATE_RESOURCE_FUNCTIONS(BackgroundColor);
    std::vector<RefPtr<ResourceObject>> detentsObj_;
};
} // namespace OHOS::Ace::NG

#endif // FOUNDATION_ACE_FRAMEWORKS_CORE_COMPONENTS_NG_PATTERNS_OVERLAY_SHEET_STYLE_H

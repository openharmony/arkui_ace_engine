/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/custom_dialog_model.h"

#include "interfaces/native/node/dialog_model.h"

#include "base/error/error_code.h"
#include "base/subwindow/subwindow_manager.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/components_ng/pattern/overlay/dialog_manager.h"
#include "frameworks/core/components/dialog/dialog_properties.h"
#include "frameworks/core/components/theme/shadow_theme.h"
#include "bridge/common/utils/engine_helper.h"

namespace OHOS::Ace::NG::CustomDialog {
namespace {
    constexpr int32_t DEFAULT_DIALOG_ALIGNMENT = -1;
    constexpr uint32_t DEFAULT_MASK_COLOR = 0x33000000;
    constexpr uint32_t DEFAULT_DIALOG_BACKGROUND_COLOR = 0x00000000;
    constexpr int32_t ARKUI_ALIGNMENT_TOP_START_INDEX = 0;
    constexpr int32_t ARKUI_ALIGNMENT_TOP_INDEX = 1;
    constexpr int32_t ARKUI_ALIGNMENT_TOP_END_INDEX = 2;
    constexpr int32_t ARKUI_ALIGNMENT_START_INDEX = 3;
    constexpr int32_t ARKUI_ALIGNMENT_CENTER_INDEX = 4;
    constexpr int32_t ARKUI_ALIGNMENT_END_INDEX = 5;
    constexpr int32_t ARKUI_ALIGNMENT_BOTTOM_START_INDEX = 6;
    constexpr int32_t ARKUI_ALIGNMENT_BOTTOM_INDEX = 7;
    constexpr int32_t ARKUI_ALIGNMENT_BOTTOM_END_INDEX = 8;
    constexpr float DEFAULT_AVOID_DISTANCE = 16.0f;
    constexpr int32_t ARKUI_LEVEL_MODE_DEFAULT_VALUE = 0;
    constexpr int32_t ARKUI_DEFAULT_LEVEL_UNIQUEID = -1;
    constexpr int32_t ARKUI_IMMERSIVE_MODE_DEFAULT_VALUE = 0;
    constexpr int32_t ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK = 12;
    constexpr int32_t HAS_COLORSTRATEGY = 1;
    constexpr int32_t HAS_COLOR = 2;
    constexpr int NUM_0 = 0;
    constexpr int NUM_1 = 1;
    constexpr int NUM_2 = 2;
    constexpr int NUM_3 = 3;
    constexpr int NUM_4 = 4;
    constexpr int NUM_5 = 5;
    constexpr int NUM_6 = 6;
    constexpr int NUM_7 = 7;
    constexpr int32_t DEFAULT_BORDER_WIDTH = 0;
    constexpr uint32_t DEFAULT_BORDER_COLOR = 0xff000000;
    constexpr int32_t DEFAULT_BORDER_STYLE = static_cast<int32_t>(OHOS::Ace::BorderStyle::SOLID);
    DialogProperties g_dialogProperties;
} // namespace

ArkUIDialogHandle CreateDialog()
{
    return new _ArkUIDialog({ .dialogHandle = nullptr,
        .contentHandle = nullptr,
        .alignment = DEFAULT_DIALOG_ALIGNMENT,
        .offsetX = 0.0f,
        .offsetY = 0.0f,
        .isModal = true,
        .autoCancel = true,
        .maskColor = DEFAULT_MASK_COLOR,
        .maskRect = nullptr,
        .backgroundColor = DEFAULT_DIALOG_BACKGROUND_COLOR,
        .cornerRadiusRect = nullptr,
        .gridCount = -1,
        .enableCustomStyle = false,
        .showInSubWindow = false,
        .enableCustomAnimation = false,
        .onWillDismissCall = nullptr,
        .onWillDismissCallByNDK  = nullptr,
        .userData = nullptr,
        .keyboardAvoidDistanceValue = std::optional<ArkUI_Float32>(),
        .keyboardAvoidDistanceUnit = DimensionUnit::VP,
        .levelMode = ARKUI_LEVEL_MODE_DEFAULT_VALUE,
        .levelUniqueId = ARKUI_DEFAULT_LEVEL_UNIQUEID,
        .immersiveMode = ARKUI_IMMERSIVE_MODE_DEFAULT_VALUE,
        .levelOrder = 0.0f,
        .onWillAppearData = nullptr,
        .onDidAppearData = nullptr,
        .onWillDisappearData = nullptr,
        .onDidDisappearData = nullptr,
        .onWillAppear = nullptr,
        .onDidAppear = nullptr,
        .onWillDisappear = nullptr,
        .onDidDisappear = nullptr,
        .borderWidthEdgeWidths = new ArkUIBorderWidth({ .top = DEFAULT_BORDER_WIDTH,
            .right = DEFAULT_BORDER_WIDTH,
            .bottom = DEFAULT_BORDER_WIDTH,
            .left = DEFAULT_BORDER_WIDTH }),
        .borderWidthUnit = DimensionUnit::VP,
        .borderColors = new ArkUIBorderColor({ .top = DEFAULT_BORDER_COLOR,
            .right = DEFAULT_BORDER_COLOR,
            .bottom = DEFAULT_BORDER_COLOR,
            .left = DEFAULT_BORDER_COLOR }),
        .borderStyles = new ArkUIBorderStyle({ .top = DEFAULT_BORDER_STYLE,
            .right = DEFAULT_BORDER_STYLE,
            .bottom = DEFAULT_BORDER_STYLE,
            .left = DEFAULT_BORDER_STYLE }),
        .widthValue = std::optional<ArkUI_Float32>(),
        .widthUnit = DimensionUnit::VP,
        .heightValue = std::optional<ArkUI_Float32>(),
        .heightUnit = DimensionUnit::VP,
        .blurStyle = ARKUI_BLUR_STYLE_COMPONENT_ULTRA_THICK,
        .blurStyleOption = std::nullopt,
        .effectOption = std::nullopt,
        .keyboardAvoidMode = OHOS::Ace::KeyboardAvoidMode::DEFAULT,
        .enableHoverMode = std::nullopt,
        .hoverModeAreaType = OHOS::Ace::HoverModeAreaType::TOP_SCREEN,
        .focusable = true,
    });
}

void DisposeDialog(ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    auto* dialog = reinterpret_cast<FrameNode*>(controllerHandler->dialogHandle);
    if (dialog) {
        dialog->DecRefCount();
    }
    controllerHandler->dialogHandle = nullptr;
    auto* content = reinterpret_cast<FrameNode*>(controllerHandler->contentHandle);
    if (content) {
        content->DecRefCount();
    }
    controllerHandler->contentHandle = nullptr;
    auto* maskRect = controllerHandler->maskRect;
    if (maskRect) {
        delete maskRect;
    }
    auto* cornerRadiusRect = controllerHandler->cornerRadiusRect;
    if (cornerRadiusRect) {
        delete cornerRadiusRect;
    }
    controllerHandler->onWillDismissCall = nullptr;
    controllerHandler->onWillDismissCallByNDK  = nullptr;
    controllerHandler->userData = nullptr;
    delete controllerHandler;
}

DialogAlignment GetDialogAlignment(int32_t alignment)
{
    switch (alignment) {
        case ARKUI_ALIGNMENT_TOP_START_INDEX:
            return DialogAlignment::TOP_START;
        case ARKUI_ALIGNMENT_TOP_INDEX:
            return DialogAlignment::TOP;
        case ARKUI_ALIGNMENT_TOP_END_INDEX:
            return DialogAlignment::TOP_END;
        case ARKUI_ALIGNMENT_START_INDEX:
            return DialogAlignment::CENTER_START;
        case ARKUI_ALIGNMENT_CENTER_INDEX:
            return DialogAlignment::CENTER;
        case ARKUI_ALIGNMENT_END_INDEX:
            return DialogAlignment::CENTER_END;
        case ARKUI_ALIGNMENT_BOTTOM_START_INDEX:
            return DialogAlignment::BOTTOM_START;
        case ARKUI_ALIGNMENT_BOTTOM_INDEX:
            return DialogAlignment::BOTTOM;
        case ARKUI_ALIGNMENT_BOTTOM_END_INDEX:
            return DialogAlignment::BOTTOM_END;
        default:
            break;
    }
    return DialogAlignment::DEFAULT;
}

void ParseDialogMask(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    dialogProperties.maskColor = Color(controllerHandler->maskColor);
    if (!controllerHandler->maskRect) {
        return;
    }
    DimensionRect maskRect;
    maskRect.SetOffset(DimensionOffset(Dimension(controllerHandler->maskRect->x, DimensionUnit::VP),
        Dimension(controllerHandler->maskRect->y, DimensionUnit::VP)));
    maskRect.SetSize(DimensionSize(Dimension(controllerHandler->maskRect->width, DimensionUnit::VP),
        Dimension(controllerHandler->maskRect->height, DimensionUnit::VP)));
    dialogProperties.maskRect = maskRect;
}

void ParseDialogOnWillDismiss(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!controllerHandler->onWillDismissCall) {
        return;
    }
    dialogProperties.onWillDismiss = [controllerHandler](int32_t reason, int32_t instanceId) {
        CHECK_NULL_VOID(controllerHandler);
        CHECK_NULL_VOID(controllerHandler->onWillDismissCall);
        (*(controllerHandler->onWillDismissCall))(reason);
    };
}

void ParseDialogLife(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (controllerHandler->onWillAppear) {
        dialogProperties.onWillAppear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onWillAppear);
            (*(controllerHandler->onWillAppear))(controllerHandler->onWillAppearData);
        };
    }
    if (controllerHandler->onDidAppear) {
        dialogProperties.onDidAppear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onDidAppear);
            (*(controllerHandler->onDidAppear))(controllerHandler->onDidAppearData);
        };
    }
    if (controllerHandler->onWillDisappear) {
        dialogProperties.onWillDisappear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onWillDisappear);
            (*(controllerHandler->onWillDisappear))(controllerHandler->onWillDisappearData);
        };
    }
    if (controllerHandler->onDidDisappear) {
        dialogProperties.onDidDisappear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onDidDisappear);
            (*(controllerHandler->onDidDisappear))(controllerHandler->onDidDisappearData);
        };
    }
}

void ParseDialogCornerRadiusRect(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!controllerHandler->cornerRadiusRect) {
        return;
    }
    NG::BorderRadiusProperty radius;
    radius.radiusTopLeft = Dimension(controllerHandler->cornerRadiusRect->topLeft, DimensionUnit::VP);
    radius.radiusTopRight = Dimension(controllerHandler->cornerRadiusRect->topRight, DimensionUnit::VP);
    radius.radiusBottomLeft = Dimension(controllerHandler->cornerRadiusRect->bottomLeft, DimensionUnit::VP);
    radius.radiusBottomRight = Dimension(controllerHandler->cornerRadiusRect->bottomRight, DimensionUnit::VP);
    radius.multiValued = true;
    dialogProperties.borderRadius = radius;
}

void ParseDialogKeyboardAvoidDistance(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!dialogProperties.keyboardAvoidDistance.has_value() &&
        controllerHandler->keyboardAvoidDistanceValue.has_value()) {
        auto unitEnum = controllerHandler->keyboardAvoidDistanceUnit;
        if (controllerHandler->keyboardAvoidDistanceValue.value() < 0 || unitEnum < OHOS::Ace::DimensionUnit::NONE ||
            unitEnum > OHOS::Ace::DimensionUnit::CALC || unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
            dialogProperties.keyboardAvoidDistance = Dimension(DEFAULT_AVOID_DISTANCE, OHOS::Ace::DimensionUnit::VP);
        } else if (unitEnum == OHOS::Ace::DimensionUnit::NONE) {
            dialogProperties.keyboardAvoidDistance = Dimension(controllerHandler->keyboardAvoidDistanceValue.value(),
                OHOS::Ace::DimensionUnit::VP);
        } else {
            dialogProperties.keyboardAvoidDistance = Dimension(controllerHandler->keyboardAvoidDistanceValue.value(),
                unitEnum);
        }
    }
}

void ParseDialogBorderWidth(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!controllerHandler->borderWidthEdgeWidths) {
        return;
    }
    NG::BorderWidthProperty width;
    auto unitEnum = controllerHandler->borderWidthUnit;
    if (unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC) {
        width.leftDimen = Dimension(controllerHandler->borderWidthEdgeWidths->left, DimensionUnit::VP);
        width.topDimen = Dimension(controllerHandler->borderWidthEdgeWidths->top, DimensionUnit::VP);
        width.rightDimen = Dimension(controllerHandler->borderWidthEdgeWidths->right, DimensionUnit::VP);
        width.bottomDimen = Dimension(controllerHandler->borderWidthEdgeWidths->bottom, DimensionUnit::VP);
    } else {
        width.leftDimen = Dimension(controllerHandler->borderWidthEdgeWidths->left, unitEnum);
        width.topDimen = Dimension(controllerHandler->borderWidthEdgeWidths->top, unitEnum);
        width.rightDimen = Dimension(controllerHandler->borderWidthEdgeWidths->right, unitEnum);
        width.bottomDimen = Dimension(controllerHandler->borderWidthEdgeWidths->bottom, unitEnum);
    }
    dialogProperties.borderWidth = width;
}

void ParseDialogBorderColor(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!controllerHandler->borderColors) {
        return;
    }
    NG::BorderColorProperty color;
    color.topColor = Color(controllerHandler->borderColors->top);
    color.rightColor = Color(controllerHandler->borderColors->right);
    color.bottomColor = Color(controllerHandler->borderColors->bottom);
    color.leftColor = Color(controllerHandler->borderColors->left);
    dialogProperties.borderColor = color;
}

void ParseDialogBorderStyle(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!controllerHandler->borderStyles) {
        return;
    }
    NG::BorderStyleProperty style;
    style.styleLeft = static_cast<OHOS::Ace::BorderStyle>(controllerHandler->borderStyles->left);
    style.styleRight = static_cast<OHOS::Ace::BorderStyle>(controllerHandler->borderStyles->right);
    style.styleTop = static_cast<OHOS::Ace::BorderStyle>(controllerHandler->borderStyles->top);
    style.styleBottom = static_cast<OHOS::Ace::BorderStyle>(controllerHandler->borderStyles->bottom);
    dialogProperties.borderStyle = style;
}

void ParseDialogWidth(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!dialogProperties.width.has_value() && controllerHandler->widthValue.has_value()) {
        auto unitEnum = controllerHandler->widthUnit;
        if (unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC) {
            dialogProperties.width = Dimension(controllerHandler->widthValue.value(), OHOS::Ace::DimensionUnit::VP);
        } else {
            dialogProperties.width = Dimension(controllerHandler->widthValue.value(), unitEnum);
        }
    }
}

void ParseDialogHeight(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    if (!dialogProperties.height.has_value() && controllerHandler->heightValue.has_value()) {
        auto unitEnum = controllerHandler->heightUnit;
        if (unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC) {
            dialogProperties.height = Dimension(controllerHandler->heightValue.value(), OHOS::Ace::DimensionUnit::VP);
        } else {
            dialogProperties.height = Dimension(controllerHandler->heightValue.value(), unitEnum);
        }
    }
}

void ParseDialogProperties(DialogProperties& dialogProperties, ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_VOID(controllerHandler);
    dialogProperties.autoCancel = controllerHandler->autoCancel;
    dialogProperties.alignment = GetDialogAlignment(controllerHandler->alignment);
    dialogProperties.offset = DimensionOffset(Dimension(controllerHandler->offsetX, DimensionUnit::VP),
        Dimension(controllerHandler->offsetY, DimensionUnit::VP));
    dialogProperties.isShowInSubWindow = controllerHandler->showInSubWindow;
    dialogProperties.isModal = controllerHandler->isModal;
    dialogProperties.backgroundColor = Color(controllerHandler->backgroundColor);
    dialogProperties.customStyle = controllerHandler->enableCustomStyle;
    dialogProperties.gridCount = controllerHandler->gridCount;
    dialogProperties.dialogLevelMode = static_cast<LevelMode>(controllerHandler->levelMode);
    dialogProperties.dialogLevelUniqueId = controllerHandler->levelUniqueId;
    dialogProperties.dialogImmersiveMode = static_cast<ImmersiveMode>(controllerHandler->immersiveMode);
    dialogProperties.backgroundBlurStyle = controllerHandler->blurStyle;
    dialogProperties.blurStyleOption = controllerHandler->blurStyleOption;
    dialogProperties.effectOption = controllerHandler->effectOption;
    dialogProperties.keyboardAvoidMode = controllerHandler->keyboardAvoidMode;
    dialogProperties.hoverModeArea = controllerHandler->hoverModeAreaType;
    if (controllerHandler->customShadow.has_value()) {
        dialogProperties.shadow = controllerHandler->customShadow;
    }
    if (!dialogProperties.isShowInSubWindow) {
        dialogProperties.levelOrder = std::make_optional(controllerHandler->levelOrder);
    }
    dialogProperties.focusable = controllerHandler->focusable;

    ParseDialogMask(dialogProperties, controllerHandler);
    ParseDialogCornerRadiusRect(dialogProperties, controllerHandler);
    ParseDialogOnWillDismiss(dialogProperties, controllerHandler);
    ParseDialogLife(dialogProperties, controllerHandler);

    if (controllerHandler->onWillDismissCallByNDK) {
        dialogProperties.onWillDismissCallByNDK = [controllerHandler](int32_t reason) {
            ArkUI_DialogDismissEvent event = { controllerHandler->userData, reason, false };
            controllerHandler->onWillDismissCallByNDK(&event);
            return event.BlockDismiss;
        };
    }

    if (controllerHandler->onWillAppear) {
        dialogProperties.onWillAppear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onWillAppear);
            (*(controllerHandler->onWillAppear))(controllerHandler->userData);
        };
    }

    if (controllerHandler->onDidAppear) {
        dialogProperties.onDidAppear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onDidAppear);
            (*(controllerHandler->onDidAppear))(controllerHandler->userData);
        };
    }

    if (controllerHandler->onWillDisappear) {
        dialogProperties.onWillDisappear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onWillDisappear);
            (*(controllerHandler->onWillDisappear))(controllerHandler->userData);
        };
    }

    if (controllerHandler->onDidDisappear) {
        dialogProperties.onDidDisappear = [controllerHandler]() {
            CHECK_NULL_VOID(controllerHandler);
            CHECK_NULL_VOID(controllerHandler->onDidDisappear);
            (*(controllerHandler->onDidDisappear))(controllerHandler->userData);
        };
    }

    if (controllerHandler->enableCustomAnimation && !dialogProperties.openAnimation.has_value()) {
        AnimationOption animation;
        dialogProperties.openAnimation = animation;
    }
    if (controllerHandler->enableCustomAnimation && !dialogProperties.closeAnimation.has_value()) {
        AnimationOption animation;
        dialogProperties.closeAnimation = animation;
    }
    if (controllerHandler->enableHoverMode.has_value()) {
        dialogProperties.enableHoverMode = controllerHandler->enableHoverMode.value();
    }
    ParseDialogKeyboardAvoidDistance(dialogProperties, controllerHandler);
    ParseDialogBorderWidth(dialogProperties, controllerHandler);
    ParseDialogBorderColor(dialogProperties, controllerHandler);
    ParseDialogBorderStyle(dialogProperties, controllerHandler);
    ParseDialogWidth(dialogProperties, controllerHandler);
    ParseDialogHeight(dialogProperties, controllerHandler);
}

void ParsePartialDialogPropertiesFromProps(const DialogProperties& dialogProps, PromptDialogAttr& dialogAttr)
{
#if defined(PREVIEW)
    if (dialogAttr.showInSubWindow) {
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
        dialogAttr.showInSubWindow = false;
    }
#endif
    dialogAttr.alignment = dialogProps.alignment;
    dialogAttr.offset = dialogProps.offset;
    if (dialogProps.hoverModeArea) {
        dialogAttr.hoverModeArea = dialogProps.hoverModeArea;
    }
    if (!Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        if (dialogProps.backgroundBlurStyle) {
            dialogAttr.backgroundBlurStyle = dialogProps.backgroundBlurStyle;
        }
    }
}

PromptDialogAttr ParseDialogPropertiesFromProps(const DialogProperties& dialogProps)
{
    PromptDialogAttr dialogAttr = { .autoCancel = dialogProps.autoCancel,
        .showInSubWindow = dialogProps.isShowInSubWindow,
        .isModal = dialogProps.isModal,
        .enableHoverMode = dialogProps.enableHoverMode,
        .isUserCreatedDialog = dialogProps.isUserCreatedDialog,
        .customBuilder = dialogProps.customBuilder,
        .customBuilderWithId = dialogProps.customBuilderWithId,
        .customOnWillDismiss = dialogProps.onWillDismiss,
        .maskRect = dialogProps.maskRect,
        .backgroundColor = dialogProps.backgroundColor,
        .blurStyleOption = dialogProps.blurStyleOption,
        .effectOption = dialogProps.effectOption,
        .borderWidth = dialogProps.borderWidth,
        .borderColor = dialogProps.borderColor,
        .borderStyle = dialogProps.borderStyle,
        .borderRadius = dialogProps.borderRadius,
        .shadow = dialogProps.shadow,
        .width = dialogProps.width,
        .height = dialogProps.height,
        .contentNode = dialogProps.contentNode,
        .customStyle = dialogProps.customStyle,
        .maskColor = dialogProps.maskColor,
        .transitionEffect = dialogProps.transitionEffect,
        .onDidAppear = dialogProps.onDidAppear,
        .onDidDisappear = dialogProps.onDidDisappear,
        .onWillAppear = dialogProps.onWillAppear,
        .onWillDisappear = dialogProps.onWillDisappear,
        .keyboardAvoidMode = dialogProps.keyboardAvoidMode,
        .dialogCallback = dialogProps.dialogCallback,
        .levelOrder = dialogProps.levelOrder,
        .dialogLevelMode = dialogProps.dialogLevelMode,
        .dialogLevelUniqueId = dialogProps.dialogLevelUniqueId,
        .dialogImmersiveMode = dialogProps.dialogImmersiveMode,
        .customCNode = dialogProps.customCNode };
    ParsePartialDialogPropertiesFromProps(dialogProps, dialogAttr);
    return dialogAttr;
}

void MainWindowOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name,
    const RefPtr<NG::OverlayManager>& overlay)
{
    auto currentId = Container::CurrentIdSafelyWithCheck();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    if (overlay) {
        overlayManager = overlay;
    }
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}

bool ContainerIsService()
{
    auto containerId = Container::CurrentIdSafelyWithCheck();
    if (containerId < 0) {
        auto container = Container::GetActive();
        if (container) {
            containerId = container->GetInstanceId();
        }
    }
    return containerId >= MIN_PA_SERVICE_ID || containerId < 0;
}

int32_t ConvertBlurStyle(int32_t originBlurStyle)
{
    if (originBlurStyle < static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE)) {
        return originBlurStyle + 1;
    } else if (originBlurStyle == static_cast<int32_t>(ARKUI_BLUR_STYLE_NONE)) {
        return 0;
    }
    return originBlurStyle;
}

void openCustomDialogWithNewPipeline(std::function<void(int32_t)>&& callback)
{
    TAG_LOGI(AceLogTag::ACE_OVERLAY, "Dialog IsCurrentUseNewPipeline.");
    auto task = [callback](const RefPtr<NG::OverlayManager>& overlayManager) mutable {
        CHECK_NULL_VOID(overlayManager);
        TAG_LOGI(AceLogTag::ACE_OVERLAY, "open custom dialog isShowInSubWindow %{public}d",
            g_dialogProperties.isShowInSubWindow);
        if (g_dialogProperties.isShowInSubWindow) {
            SubwindowManager::GetInstance()->OpenCustomDialogNG(g_dialogProperties, std::move(callback));
            if (g_dialogProperties.isModal) {
                TAG_LOGW(AceLogTag::ACE_OVERLAY, "temporary not support isShowInSubWindow and isModal");
            }
        } else {
            overlayManager->OpenCustomDialog(g_dialogProperties, std::move(callback));
        }
    };
    if (g_dialogProperties.dialogLevelMode == LevelMode::EMBEDDED) {
        NG::DialogManager::ShowInEmbeddedOverlay(
            std::move(task), "ArkUIOverlayShowDialog", g_dialogProperties.dialogLevelUniqueId);
    } else {
        MainWindowOverlay(std::move(task), "ArkUIOverlayShowDialog", nullptr);
    }
}

ArkUI_Int32 SetDialogContent(ArkUIDialogHandle controllerHandler, ArkUINodeHandle contentNode)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    CHECK_NULL_RETURN(contentNode, ERROR_CODE_PARAM_INVALID);
    auto* frameNode = reinterpret_cast<FrameNode*>(contentNode);
    CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
    frameNode->IncRefCount();
    controllerHandler->contentHandle = frameNode;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RemoveDialogContent(ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    if (controllerHandler->contentHandle) {
        auto* frameNode = reinterpret_cast<FrameNode*>(controllerHandler->contentHandle);
        CHECK_NULL_RETURN(frameNode, ERROR_CODE_PARAM_INVALID);
        frameNode->DecRefCount();
        controllerHandler->contentHandle = nullptr;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogContentAlignment(ArkUIDialogHandle controllerHandler,
    ArkUI_Int32 alignment, ArkUI_Float32 offsetX, ArkUI_Float32 offsetY)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    if (alignment < DEFAULT_DIALOG_ALIGNMENT || alignment > ARKUI_ALIGNMENT_BOTTOM_END_INDEX) {
        return ERROR_CODE_PARAM_INVALID;
    }
    controllerHandler->alignment = alignment;
    controllerHandler->offsetX = offsetX;
    controllerHandler->offsetY = offsetY;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ResetDialogContentAlignment(ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->alignment = DEFAULT_DIALOG_ALIGNMENT;
    controllerHandler->offsetX = 0.0f;
    controllerHandler->offsetY = 0.0f;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogModalMode(ArkUIDialogHandle controllerHandler, bool isModal)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->isModal = isModal;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogAutoCancel(ArkUIDialogHandle controllerHandler, bool autoCancel)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->autoCancel = autoCancel;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogMask(ArkUIDialogHandle controllerHandler, ArkUI_Uint32 maskColor, ArkUIRect* rect)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->maskColor = maskColor;
    if (rect) {
        controllerHandler->maskRect = new ArkUIRect({ .x = rect->x, .y = rect->y,
            .width = rect->width, .height = rect->height });
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogBackgroundColor(ArkUIDialogHandle controllerHandler, ArkUI_Uint32 backgroundColor)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->backgroundColor = backgroundColor;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogCornerRadius(ArkUIDialogHandle controllerHandler, ArkUI_Float32 topLeft,
    ArkUI_Float32 topRight, ArkUI_Float32 bottomLeft, ArkUI_Float32 bottomRight)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->cornerRadiusRect = new ArkUICornerRadius({ .topLeft = topLeft, .topRight = topRight,
    .bottomLeft = bottomLeft, .bottomRight = bottomRight });
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogGridColumnCount(ArkUIDialogHandle controllerHandler, ArkUI_Int32 gridCount)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->gridCount = gridCount;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 EnableDialogCustomStyle(ArkUIDialogHandle controllerHandler, bool enableCustomStyle)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->enableCustomStyle = enableCustomStyle;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 EnableDialogCustomAnimation(ArkUIDialogHandle controllerHandler, bool enableCustomAnimation)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->enableCustomAnimation = enableCustomAnimation;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 ShowDialog(ArkUIDialogHandle controllerHandler, bool showInSubWindow)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->showInSubWindow = showInSubWindow;
    DialogProperties dialogProperties;
    ParseDialogProperties(dialogProperties, controllerHandler);
    auto* contentNode = reinterpret_cast<FrameNode*>(controllerHandler->contentHandle);
    CHECK_NULL_RETURN(contentNode, ERROR_CODE_PARAM_INVALID);
    auto contentPtr = AceType::Claim<FrameNode>(contentNode);
    auto dialogNode = CustomDialogControllerModelNG::SetOpenDialogWithNode(dialogProperties, contentPtr);
    if (dialogNode) {
        dialogNode->IncRefCount();
    }
    controllerHandler->dialogHandle = AceType::RawPtr(dialogNode);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 CloseDialog(ArkUIDialogHandle controllerHandler)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    auto* dialogNode = reinterpret_cast<FrameNode*>(controllerHandler->dialogHandle);
    CHECK_NULL_RETURN(dialogNode, ERROR_CODE_PARAM_INVALID);
    CustomDialogControllerModelNG::SetCloseDialogForNDK(dialogNode);
    if (dialogNode) {
        dialogNode->DecRefCount();
    }
    controllerHandler->dialogHandle = nullptr;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnWillDialogDismiss(ArkUIDialogHandle controllerHandler, bool (*eventHandler)(ArkUI_Int32))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onWillDismissCall = eventHandler;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnWillDialogDismissWithUserData(
    ArkUIDialogHandle controllerHandler, void* userData, void (*callback)(ArkUI_DialogDismissEvent* event))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onWillDismissCallByNDK  = callback;
    controllerHandler->userData = userData;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetKeyboardAvoidDistance(
    ArkUIDialogHandle controllerHandler, float distance, ArkUI_Int32 unit)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->keyboardAvoidDistanceValue = distance;
    controllerHandler->keyboardAvoidDistanceUnit = static_cast<OHOS::Ace::DimensionUnit>(unit);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetLevelMode(ArkUIDialogHandle controllerHandler, ArkUI_Int32 mode)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->levelMode = mode;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetLevelUniqueId(ArkUIDialogHandle controllerHandler, ArkUI_Int32 uniqueId)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->levelUniqueId = uniqueId;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetImmersiveMode(ArkUIDialogHandle controllerHandler, ArkUI_Int32 mode)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->immersiveMode = mode;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetLevelOrder(ArkUIDialogHandle controllerHandler, ArkUI_Float64 levelOrder)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->levelOrder = levelOrder;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnWillAppearDialog(
    ArkUIDialogHandle controllerHandler, void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onWillAppear = callback;
    controllerHandler->onWillAppearData = userData;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnDidAppearDialog(
    ArkUIDialogHandle controllerHandler, void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onDidAppear = callback;
    controllerHandler->onDidAppearData = userData;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnWillDisappearDialog(
    ArkUIDialogHandle controllerHandler, void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onWillDisappear = callback;
    controllerHandler->onWillDisappearData = userData;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 RegisterOnDidDisappearDialog(
    ArkUIDialogHandle controllerHandler, void* userData, void (*callback)(void* userData))
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->onDidDisappear = callback;
    controllerHandler->onDidDisappearData = userData;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 OpenCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId))
{
    CHECK_NULL_RETURN(handle, ERROR_CODE_PARAM_INVALID);
    ParseDialogProperties(g_dialogProperties, handle);
    g_dialogProperties.customCNode = reinterpret_cast<FrameNode*>(handle->contentHandle);
    auto promptDialogAttr = ParseDialogPropertiesFromProps(g_dialogProperties);
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        if (Container::IsCurrentUseNewPipeline()) {
            openCustomDialogWithNewPipeline(std::move(callback));
        } else {
            LOGW("not support old pipeline");
        }
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->OpenCustomDialog(promptDialogAttr, std::move(callback));
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 CloseCustomDialog(ArkUI_Int32 dialogId)
{
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        auto delegate = EngineHelper::GetCurrentDelegateSafely();
        CHECK_NULL_RETURN(delegate, ERROR_CODE_PARAM_INVALID);
        delegate->CloseCustomDialog(dialogId);
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->CloseCustomDialogNG(dialogId);
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 UpdateCustomDialog(ArkUIDialogHandle handle, void (*callback)(ArkUI_Int32 dialogId))
{
    CHECK_NULL_RETURN(handle, ERROR_CODE_PARAM_INVALID);
    ParseDialogProperties(g_dialogProperties, handle);
    auto promptDialogAttr = ParseDialogPropertiesFromProps(g_dialogProperties);
    if (SystemProperties::GetExtSurfaceEnabled() || !ContainerIsService()) {
        g_dialogProperties.autoCancel = promptDialogAttr.autoCancel,
        g_dialogProperties.maskColor = promptDialogAttr.maskColor, g_dialogProperties.isSysBlurStyle = false;
        if (promptDialogAttr.alignment.has_value()) {
            g_dialogProperties.alignment = promptDialogAttr.alignment.value();
        }
        if (promptDialogAttr.offset.has_value()) {
            g_dialogProperties.offset = promptDialogAttr.offset.value();
        }
        auto node = g_dialogProperties.customCNode;
        auto nodePtr = node.Upgrade();
        CHECK_NULL_RETURN(nodePtr, ERROR_CODE_PARAM_INVALID);
        auto context = nodePtr->GetContextWithCheck();
        CHECK_NULL_RETURN(context, ERROR_CODE_PARAM_INVALID);
        auto overlayManager = context->GetOverlayManager();
        context->GetTaskExecutor()->PostTask(
            [node, callback, weak = WeakPtr<NG::OverlayManager>(overlayManager)]() mutable {
                auto overlayManager = weak.Upgrade();
                CHECK_NULL_VOID(overlayManager);
                TAG_LOGI(AceLogTag::ACE_OVERLAY, "begin to update custom dialog.");
                overlayManager->UpdateCustomDialog(node, g_dialogProperties, std::move(callback));
            },
            TaskExecutor::TaskType::UI, "ArkUIOverlayUpdateCustomDialog");
    } else if (SubwindowManager::GetInstance() != nullptr) {
        SubwindowManager::GetInstance()->UpdateCustomDialogNG(
            g_dialogProperties.customCNode, promptDialogAttr, std::move(callback));
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogSubwindowMode(ArkUIDialogHandle controllerHandler, bool showInSubWindow)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->showInSubWindow = showInSubWindow;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogBorderWidth(ArkUIDialogHandle controllerHandler, ArkUI_Float32 top, ArkUI_Float32 right,
    ArkUI_Float32 bottom, ArkUI_Float32 left, ArkUI_Int32 unit)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->borderWidthEdgeWidths =
        new ArkUIBorderWidth({ .top = top, .right = right, .bottom = bottom, .left = left });
    controllerHandler->borderWidthUnit = static_cast<OHOS::Ace::DimensionUnit>(unit);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogBorderColor(
    ArkUIDialogHandle controllerHandler, ArkUI_Uint32 top, ArkUI_Uint32 right, ArkUI_Uint32 bottom, ArkUI_Uint32 left)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->borderColors =
        new ArkUIBorderColor({ .top = top, .right = right, .bottom = bottom, .left = left });
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogBorderStyle(
    ArkUIDialogHandle controllerHandler, ArkUI_Int32 top, ArkUI_Int32 right, ArkUI_Int32 bottom, ArkUI_Int32 left)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->borderStyles =
        new ArkUIBorderStyle({ .top = top, .right = right, .bottom = bottom, .left = left });
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetWidth(ArkUIDialogHandle controllerHandler, float width, ArkUI_Int32 unit)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->widthValue = width;
    controllerHandler->widthUnit = static_cast<OHOS::Ace::DimensionUnit>(unit);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetHeight(ArkUIDialogHandle controllerHandler, float height, ArkUI_Int32 unit)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->heightValue = height;
    controllerHandler->heightUnit = static_cast<OHOS::Ace::DimensionUnit>(unit);
    return ERROR_CODE_NO_ERROR;
}

bool GetShadowFromTheme(ShadowStyle shadowStyle, Shadow& shadow)
{
    if (shadowStyle == ShadowStyle::None) {
        return true;
    }
    auto container = Container::Current();
    CHECK_NULL_RETURN(container, false);
    auto pipelineContext = container->GetPipelineContext();
    CHECK_NULL_RETURN(pipelineContext, false);

    auto shadowTheme = pipelineContext->GetTheme<ShadowTheme>();
    CHECK_NULL_RETURN(shadowTheme, false);
    auto colorMode = container->GetColorMode();
    shadow = shadowTheme->GetShadow(shadowStyle, colorMode);
    return true;
}

ArkUI_Int32 SetShadow(ArkUIDialogHandle controllerHandler, ArkUI_Int32 shadow)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    if (static_cast<OHOS::Ace::ShadowStyle>(shadow) < OHOS::Ace::ShadowStyle::OuterDefaultXS ||
        static_cast<OHOS::Ace::ShadowStyle>(shadow) >= OHOS::Ace::ShadowStyle::None) {
        return ERROR_CODE_PARAM_INVALID;
    } else {
        Shadow shadows;
        GetShadowFromTheme(static_cast<OHOS::Ace::ShadowStyle>(shadow), shadows);
        controllerHandler->customShadow = shadows;
    }
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetDialogCustomShadow(
    ArkUIDialogHandle controllerHandler, const ArkUIInt32orFloat32* shadows, ArkUI_Int32 length)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    if (length == NUM_1) {
        Shadow shadow;
        auto shadowStyle = static_cast<ShadowStyle>(shadows[NUM_0].i32);
        auto style = static_cast<ShadowStyle>(shadowStyle);
        if (GetShadowFromTheme(style, shadow)) {
            controllerHandler->customShadow = shadow;
        }
    }
    if (length != NUM_7) {
        return ERROR_CODE_NO_ERROR;
    }
    auto blurRadius = shadows[NUM_0].f32;
    auto hasColorValue = static_cast<int32_t>(shadows[NUM_1].i32);
    auto offsetX = shadows[NUM_2].f32;
    auto offsetY = shadows[NUM_3].f32;
    auto shadowType = shadows[NUM_4].i32;
    auto color = static_cast<uint32_t>(shadows[NUM_5].u32);
    auto isFilled = static_cast<uint32_t>(shadows[NUM_6].i32);
    Shadow shadow;
    shadow.SetBlurRadius(blurRadius);
    shadow.SetOffsetX(offsetX);
    shadow.SetOffsetY(offsetY);
    if (hasColorValue == HAS_COLORSTRATEGY) {
        shadow.SetShadowColorStrategy(static_cast<ShadowColorStrategy>(color));
    } else if (hasColorValue == HAS_COLOR) {
        shadow.SetColor(Color(color));
    }
    shadow.SetShadowType(static_cast<ShadowType>(shadowType));
    shadow.SetIsFilled(static_cast<bool>(isFilled));
    controllerHandler->customShadow = shadow;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetBackgroundBlurStyle(ArkUIDialogHandle controllerHandler, ArkUI_Int32 blurStyle)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->blurStyle = ConvertBlurStyle(blurStyle);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetKeyboardAvoidMode(ArkUIDialogHandle controllerHandler, ArkUI_Int32 keyboardAvoidMode)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->keyboardAvoidMode = static_cast<OHOS::Ace::KeyboardAvoidMode>(keyboardAvoidMode);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 EnableHoverMode(ArkUIDialogHandle controllerHandler, bool enableHoverMode)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->enableHoverMode = enableHoverMode;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetHoverModeArea(ArkUIDialogHandle controllerHandler, ArkUI_Int32 hoverModeAreaType)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->hoverModeAreaType = static_cast<OHOS::Ace::HoverModeAreaType>(hoverModeAreaType);
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetFocusable(ArkUIDialogHandle controllerHandler, bool focusable)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    controllerHandler->focusable = focusable;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetBackgroundBlurStyleOptions(ArkUIDialogHandle controllerHandler, ArkUI_Int32 (*intArray)[3],
    ArkUI_Float32 scale, ArkUI_Uint32 (*uintArray)[3], ArkUI_Bool isValidColor)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    BlurStyleOption blurStyleOption;
    blurStyleOption.colorMode = static_cast<ThemeColorMode>((*intArray)[NUM_0]);
    blurStyleOption.adaptiveColor = static_cast<AdaptiveColor>((*intArray)[NUM_1]);
    blurStyleOption.policy = static_cast<BlurStyleActivePolicy>((*intArray)[NUM_2]);
    blurStyleOption.scale = scale;
    std::vector<float> greyVec = { (*uintArray)[NUM_0], (*uintArray)[NUM_1] };
    blurStyleOption.blurOption.grayscale = greyVec;
    blurStyleOption.inactiveColor = Color((*uintArray)[NUM_2]);
    blurStyleOption.isValidColor = isValidColor;
    if (!controllerHandler->blurStyleOption.has_value()) {
        controllerHandler->blurStyleOption.emplace();
    }
    controllerHandler->blurStyleOption.value() = blurStyleOption;
    return ERROR_CODE_NO_ERROR;
}

ArkUI_Int32 SetBackgroundEffect(ArkUIDialogHandle controllerHandler, ArkUI_Float32 (*floatArray)[3],
    ArkUI_Int32 (*intArray)[2], ArkUI_Uint32 (*uintArray)[4], ArkUI_Bool isValidColor)
{
    CHECK_NULL_RETURN(controllerHandler, ERROR_CODE_PARAM_INVALID);
    CalcDimension radius((*floatArray)[NUM_0], DimensionUnit::VP);
    EffectOption effectOption;
    effectOption.radius = radius;
    effectOption.saturation = (*floatArray)[NUM_1];
    effectOption.brightness = (*floatArray)[NUM_2];
    effectOption.adaptiveColor = static_cast<AdaptiveColor>((*intArray)[NUM_0]);
    effectOption.policy = static_cast<BlurStyleActivePolicy>((*intArray)[NUM_1]);
    effectOption.color = Color((*uintArray)[NUM_0]);
    std::vector<float> greyVec = { (*uintArray)[NUM_0], (*uintArray)[NUM_1] };
    effectOption.blurOption.grayscale = greyVec;
    effectOption.inactiveColor = Color((*uintArray)[NUM_3]);
    effectOption.isValidColor = isValidColor;
    if (!controllerHandler->effectOption.has_value()) {
        controllerHandler->effectOption.emplace();
    }
    controllerHandler->effectOption.value() = effectOption;
    return ERROR_CODE_NO_ERROR;
}

} // namespace OHOS::Ace::NG::ViewModel

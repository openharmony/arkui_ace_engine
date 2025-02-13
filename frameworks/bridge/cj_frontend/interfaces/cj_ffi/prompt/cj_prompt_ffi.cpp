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

#include "cj_prompt_ffi.h"

#include "cj_lambda.h"

#include "base/i18n/localization.h"
#include "bridge/cj_frontend/frontend/cj_frontend_abstract.h"
#include "bridge/cj_frontend/interfaces/cj_ffi/cj_transitioneffect.h"
#include "core/components/theme/shadow_theme.h"
#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Ace;
using namespace OHOS::Ace::Framework;
using namespace OHOS::Ace::NG;

namespace {
const int32_t SHOW_DIALOG_BUTTON_NUM_MAX = 3;
const int32_t SHOW_ACTION_MENU_BUTTON_NUM_MAX = 6;
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
constexpr int32_t CALLBACK_ERRORCODE_CANCEL = 1;
constexpr int32_t CALLBACK_DATACODE_ZERO = 0;
constexpr int32_t TOAST_TIME_MAX = 10000;    // ms
constexpr int32_t TOAST_TIME_DEFAULT = 1500; // ms
constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;
const double SHADOW_OPTION_NONE = -1.000000;
const int32_t SHADOW_STYLE_NONE = 100;

uint32_t ColorAlphaAdapt(uint32_t origin)
{
    uint32_t result = origin;
    if ((origin >> COLOR_ALPHA_OFFSET) == 0) {
        result = origin | COLOR_ALPHA_VALUE;
    }
    return result;
}

RefPtr<OHOS::Ace::CJFrontendAbstract> CheckFrontendLegality(int32_t size, CButtonInfo* buttonsInfo)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return nullptr;
    }
    if (size < 0 || buttonsInfo == nullptr) {
        LOGE("Invalid buttons info");
        return nullptr;
    }
    return frontend;
}

std::vector<ButtonInfo> CreateButtonInfoVector(CButtonInfo* buttonsInfo, int32_t size, int32_t numMax)
{
    std::vector<ButtonInfo> buttons;
    if (size > numMax) {
        size = numMax;
        LOGE("Supports 1 - %{public}d buttons", numMax);
    }
    for (int i = 0; i < size; ++i) {
        auto curInfo = buttonsInfo + i;
        ButtonInfo button { .text = curInfo->text, .textColor = Color(curInfo->textColor).ColorToString() };
        buttons.emplace_back(button);
    }
    return buttons;
}

void MainWindowOverlay(std::function<void(RefPtr<NG::OverlayManager>)>&& task, const std::string& name)
{
    auto currentId = Container::CurrentId();
    ContainerScope scope(currentId);
    auto context = NG::PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(context);
    auto overlayManager = context->GetOverlayManager();
    context->GetTaskExecutor()->PostTask(
        [task = std::move(task), weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            task(overlayManager);
        },
        TaskExecutor::TaskType::UI, name);
}

void ShowDialogInner(DialogProperties& dialogProperties, std::function<void(int32_t, int32_t)>&& callback,
    const std::set<std::string>& callbacks)
{
    LOGI("Dialog IsCurrentUseNewPipeline.");
    auto context = NG::PipelineContext::GetCurrentContext();
    dialogProperties.onCancel = [callback, taskExecutor = context->GetTaskExecutor()] {
        taskExecutor->PostTask([callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); },
            TaskExecutor::TaskType::JS, "CJFroentendShowDialogInner");
    };
    dialogProperties.onSuccess = std::move(callback);

    auto task = [dialogProperties](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        RefPtr<NG::FrameNode> dialog;
        LOGI("Begin to show dialog ");
        if (dialogProperties.isShowInSubWindow) {
            dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, nullptr);
            CHECK_NULL_VOID(dialog);
            if (dialogProperties.isModal) {
                DialogProperties maskarg;
                maskarg.isMask = true;
                maskarg.autoCancel = dialogProperties.autoCancel;
                auto mask = overlayManager->ShowDialog(maskarg, nullptr, false);
                CHECK_NULL_VOID(mask);
                overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
            }
        } else {
            dialog = overlayManager->ShowDialog(
                dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
            CHECK_NULL_VOID(dialog);
        }
    };
    MainWindowOverlay(std::move(task), "ArkUIShowDialogInner");
}

void ShowActionMenuInner(DialogProperties& dialogProperties, const std::vector<ButtonInfo>& button,
    std::function<void(int32_t, int32_t)>&& callback)
{
    ButtonInfo buttonInfo = { .text = Localization::GetInstance()->GetEntryLetters("common.cancel"), .textColor = "" };
    dialogProperties.buttons.emplace_back(buttonInfo);
    auto context = NG::PipelineContext::GetCurrentContext();
    auto curExecutor = context->GetTaskExecutor();
    dialogProperties.onCancel = [callback, taskExecutor = curExecutor] {
        taskExecutor->PostTask([callback]() { callback(CALLBACK_ERRORCODE_CANCEL, CALLBACK_DATACODE_ZERO); },
            TaskExecutor::TaskType::JS, "CJFroentendShowActionMenuInnerOnCancel");
    };
    dialogProperties.onSuccess = std::move(callback);
    auto overlayManager = context ? context->GetOverlayManager() : nullptr;
    curExecutor->PostTask(
        [dialogProperties, weak = WeakPtr<NG::OverlayManager>(overlayManager)] {
            auto overlayManager = weak.Upgrade();
            CHECK_NULL_VOID(overlayManager);
            RefPtr<NG::FrameNode> dialog;
            if (dialogProperties.isShowInSubWindow) {
                dialog = SubwindowManager::GetInstance()->ShowDialogNG(dialogProperties, nullptr);
                CHECK_NULL_VOID(dialog);
                if (dialogProperties.isModal) {
                    DialogProperties maskarg;
                    maskarg.autoCancel = dialogProperties.autoCancel;
                    maskarg.isMask = true;
                    auto mask = overlayManager->ShowDialog(maskarg, nullptr, false);
                    CHECK_NULL_VOID(mask);
                    overlayManager->SetMaskNodeId(dialog->GetId(), mask->GetId());
                }
            } else {
                dialog = overlayManager->ShowDialog(
                    dialogProperties, nullptr, AceApplicationInfo::GetInstance().IsRightToLeft());
                CHECK_NULL_VOID(dialog);
            }
        },
        TaskExecutor::TaskType::UI, "CJFrontendShowActionMenuInner");
}

void SetBorder(DialogProperties& dialogProperties, const NativeCustomDialogOptions& options)
{
    // border
    NG::BorderStyleProperty borderStyle = { .styleLeft = BorderStyle(options.borderEdgeStyle.left),
        .styleRight = BorderStyle(options.borderEdgeStyle.right),
        .styleTop = BorderStyle(options.borderEdgeStyle.top),
        .styleBottom = BorderStyle(options.borderEdgeStyle.bottom) };

    NG::BorderWidthPropertyT<Dimension> borderWidth = {
        .leftDimen = Dimension(options.borderWidth.left, static_cast<DimensionUnit>(options.borderWidth.leftUnit)),
        .topDimen = Dimension(options.borderWidth.top, static_cast<DimensionUnit>(options.borderWidth.topUnit)),
        .rightDimen = Dimension(options.borderWidth.right, static_cast<DimensionUnit>(options.borderWidth.rightUnit)),
        .bottomDimen = Dimension(options.borderWidth.bottom, static_cast<DimensionUnit>(options.borderWidth.bottomUnit))
    };

    NG::BorderRadiusPropertyT<Dimension> borderRadius = NG::BorderRadiusPropertyT<Dimension>(
        Dimension(options.cornerRadius.topLeftRadiuses, static_cast<DimensionUnit>(options.cornerRadius.topLeftUnit)),
        Dimension(options.cornerRadius.topRightRadiuses, static_cast<DimensionUnit>(options.cornerRadius.topRightUnit)),
        Dimension(
            options.cornerRadius.bottomRightRadiuses, static_cast<DimensionUnit>(options.cornerRadius.bottomRightUnit)),
        Dimension(
            options.cornerRadius.bottomLeftRadiuses, static_cast<DimensionUnit>(options.cornerRadius.bottomLeftUnit)));

    NG::BorderColorProperty borderColor = {
        .leftColor = Color(ColorAlphaAdapt(options.borderColor.left)),
        .rightColor = Color(ColorAlphaAdapt(options.borderColor.right)),
        .topColor = Color(ColorAlphaAdapt(options.borderColor.top)),
        .bottomColor = Color(ColorAlphaAdapt(options.borderColor.bottom)),
    };
    dialogProperties.borderRadius = borderRadius;
    dialogProperties.borderWidth = borderWidth;
    dialogProperties.borderColor = borderColor;
    dialogProperties.borderStyle = borderStyle;
}

void SetShape(DialogProperties& dialogProperties, const NativeCustomDialogOptions& options)
{
    auto alignment = DIALOG_ALIGNMENT[options.alignment];

    // parse maskRect
    Dimension xDimen = Dimension(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension yDimen = Dimension(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension widthDimen = Dimension(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension heightDimen = Dimension(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    auto maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);

    // parse offset
    double dxVal = options.offset.dx.value;
    int32_t dxType = options.offset.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));
    double dyVal = options.offset.dy.value;
    int32_t dyType = options.offset.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    auto offset = DimensionOffset(dx, dy);

    // parse width height
    double heightVal = options.heightValue;
    int32_t heightType = options.heightUnit;
    CalcDimension height = CalcDimension(heightVal, static_cast<DimensionUnit>(heightType));

    double widthVal = options.widthValue;
    int32_t widthType = options.widthUnit;
    CalcDimension width = CalcDimension(widthVal, static_cast<DimensionUnit>(widthType));
    dialogProperties.maskRect = maskRect;
    dialogProperties.alignment = alignment;
    dialogProperties.offset = offset;
    dialogProperties.width = width;
    dialogProperties.height = height;
}

void SetFunc(DialogProperties& dialogProperties, const NativeCustomDialogOptions& options)
{
    auto builderFunc = [func = CJLambda::Create(options.builder)]() { func(); };

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss = nullptr;

    // Parse action
    auto onDidAppear = [lambda = CJLambda::Create(options.onDidAppear)]() { lambda(); };
    auto onDidDisappear = [lambda = CJLambda::Create(options.onDidAppear)]() { lambda(); };
    auto onWillAppear = [lambda = CJLambda::Create(options.onDidAppear)]() { lambda(); };
    auto onWillDisappear = [lambda = CJLambda::Create(options.onDidAppear)]() { lambda(); };
    dialogProperties.onDidAppear = std::move(onDidAppear);
    dialogProperties.onDidDisappear = std::move(onDidDisappear);
    dialogProperties.onWillAppear = std::move(onWillAppear);
    dialogProperties.onWillDisappear = std::move(onWillDisappear);
    dialogProperties.customBuilder = std::move(builderFunc);
    dialogProperties.onWillDismiss = std::move(onWillDismiss);
}

DialogProperties GetDialogProperties(const NativeCustomDialogOptions& options)
{
    // transition
    RefPtr<NG::ChainedTransitionEffect> chainedEffect = nullptr;
    auto nativeTransitionEffect = OHOS::FFI::FFIData::GetData<NativeTransitionEffect>(options.transition);
    if (nativeTransitionEffect != nullptr) {
        chainedEffect = nativeTransitionEffect->effect;
    }

    // shadow
    Shadow shadow;
    if (options.shadowOption.radius == SHADOW_OPTION_NONE) {
        if (options.shadowStyle == SHADOW_STYLE_NONE) {
            shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultMD);
        } else {
            shadow = Shadow::CreateShadow(OHOS::Ace::ShadowStyle(options.shadowStyle));
        }
    } else {
        shadow.SetBlurRadius(options.shadowOption.radius);
        shadow.SetShadowType(ShadowType(options.shadowOption.shadowType));
        shadow.SetColor(Color(options.shadowOption.color));
        shadow.SetOffsetX(options.shadowOption.offsetX);
        shadow.SetOffsetY(options.shadowOption.offsetY);
        shadow.SetIsFilled(options.shadowOption.fill);
    };
    DialogProperties dialogProperties = {
        .autoCancel = options.autoCancel,
        .isShowInSubWindow = options.showInSubWindow,
        .isModal = options.isModal,
        .maskColor = Color(ColorAlphaAdapt(options.maskColor)),
        .backgroundColor = Color(ColorAlphaAdapt(options.backgroundColor)),
        .isSysBlurStyle = false,
        .enableHoverMode = options.enableHoverMode,
        .transitionEffect = chainedEffect,
        .shadow = shadow,
        .hoverModeArea = HoverModeAreaType(options.hoverModeArea),
    };
    SetBorder(dialogProperties, options);
    SetShape(dialogProperties, options);
    SetFunc(dialogProperties, options);
    return dialogProperties;
}

void SetShowDialog(DialogProperties& dialogProperties, const NativeShowDialogOptions& options)
{
    auto alignment = DIALOG_ALIGNMENT[options.alignment];

    // parse maskRect
    Dimension xDimen = Dimension(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension yDimen = Dimension(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension widthDimen = Dimension(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension heightDimen = Dimension(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    auto maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);

    // parse offset
    double dxVal = options.offset.dx.value;
    int32_t dxType = options.offset.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));
    double dyVal = options.offset.dy.value;
    int32_t dyType = options.offset.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    auto offset = DimensionOffset(dx, dy);

    // shadow
    Shadow shadow;
    if (options.shadowOption.radius == SHADOW_OPTION_NONE) {
        if (options.shadowStyle == SHADOW_STYLE_NONE) {
            shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultMD);
        } else {
            shadow = Shadow::CreateShadow(OHOS::Ace::ShadowStyle(options.shadowStyle));
        }
    } else {
        shadow.SetBlurRadius(options.shadowOption.radius);
        shadow.SetShadowType(ShadowType(options.shadowOption.shadowType));
        shadow.SetColor(Color(options.shadowOption.color));
        shadow.SetOffsetX(options.shadowOption.offsetX);
        shadow.SetOffsetY(options.shadowOption.offsetY);
        shadow.SetIsFilled(options.shadowOption.fill);
    };
    dialogProperties.alignment = alignment;
    dialogProperties.offset = offset;
    dialogProperties.maskRect = maskRect;
    dialogProperties.shadow = shadow;
}
} // namespace

extern "C" {
void* FfiPromptMallocButtons(int64_t size)
{
    if (size <= 0) {
        return nullptr;
    }

    CButtonInfo* pButton = static_cast<CButtonInfo*>(malloc(sizeof(CButtonInfo) * size));
    if (pButton == nullptr) {
        printf("Fail to malloc pButton.");
        return nullptr;
    }
    return pButton;
}

void FfiPromptShowToast(const char* message, int32_t duration, const char* bottom, int32_t mode)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }
    frontend->ShowToast(message, duration, bottom, NG::ToastShowMode(mode));
}

void FfiPromptShowDialog(
    const char* title, const char* message, int32_t size, CButtonInfo* buttonsInfo, ShowDialogCallBack callbackRef)
{
    auto frontend = CheckFrontendLegality(size, buttonsInfo);
    if (!frontend) {
        return;
    }
    std::vector<ButtonInfo> buttons = CreateButtonInfoVector(buttonsInfo, size, SHOW_DIALOG_BUTTON_NUM_MAX);
    std::set<std::string> callbacks;
    callbacks.emplace("success");
    callbacks.emplace("cancel");

    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
                        int32_t callbackType, int32_t successType) { ffiOnClick(callbackType, successType); };
    frontend->ShowDialog(title, message, buttons, std::move(callback), callbacks);
}

void FfiPromptShowActionMenu(
    const char* title, int32_t size, CButtonInfo* buttonsInfo, ShowActionMenuCallBack callbackRef)
{
    auto frontend = CheckFrontendLegality(size, buttonsInfo);
    if (!frontend) {
        return;
    }
    std::vector<ButtonInfo> buttons = CreateButtonInfoVector(buttonsInfo, size, SHOW_ACTION_MENU_BUTTON_NUM_MAX);
    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
                        int callbackType, int successType) { ffiOnClick(callbackType, successType); };
    frontend->ShowActionMenu(title, buttons, std::move(callback));
}

void FfiPromptOpenCustomDialog(void (*builder)(), NativeBaseOption options, void (*callback)(int32_t))
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }

    auto builderFunc = [func = CJLambda::Create(builder)]() { func(); };
    auto callbackFunc = [func = CJLambda::Create(callback)](int32_t customId) { func(customId); };

    std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismiss = nullptr;

    if (options.alignment < 0 || options.alignment >= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        return;
    }
    auto alignment = DIALOG_ALIGNMENT[options.alignment];

    // parse maskRect
    Dimension xDimen = Dimension(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension yDimen = Dimension(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension widthDimen = Dimension(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension heightDimen = Dimension(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset offsetDimen(xDimen, yDimen);
    auto maskRect = DimensionRect(widthDimen, heightDimen, offsetDimen);

    // parse offset
    double dxVal = options.offset.dx.value;
    int32_t dxType = options.offset.dx.unitType;
    CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));
    double dyVal = options.offset.dy.value;
    int32_t dyType = options.offset.dy.unitType;
    CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
    auto offset = DimensionOffset(dx, dy);

    PromptDialogAttr promptDialogAttr = {
        .showInSubWindow = options.showInSubWindow,
        .isModal = options.isModal,
        .customBuilder = std::move(builderFunc),
        .customOnWillDismiss = std::move(onWillDismiss),
        .alignment = alignment,
        .offset = offset,
        .maskRect = maskRect,
    };

    frontend->OpenCustomDialog(promptDialogAttr, std::move(callbackFunc));
}

void FfiPromptCloseCustomDialog(int32_t id)
{
    auto frontend = AceType::DynamicCast<CJFrontendAbstract>(Utils::GetCurrentFrontend());
    if (!frontend) {
        LOGE("Can not get frontend.");
        return;
    }

    auto task = [id](const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        LOGI("begin to close custom dialog.");
        overlayManager->CloseCustomDialog(id);
        SubwindowManager::GetInstance()->CloseCustomDialogNG(id);
    };
    MainWindowOverlay(std::move(task), "ArkUICloseCustomDialog");
    return;
}

void FfiPromptOpenCustomDialogWithOption(NativeCustomDialogOptions options, void (*callback)(int32_t))
{
    auto callbackFunc = [func = CJLambda::Create(callback)](int32_t customId) { func(customId); };
    DialogProperties dialogProperties = GetDialogProperties(options);
#if defined(PREVIEW)
    if (dialogProperties.isShowInSubWindow) {
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
        dialogProperties.isShowInSubWindow = false;
    }
#endif
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TWELVE)) {
        dialogProperties.isSysBlurStyle = false;
    } else {
        dialogProperties.backgroundBlurStyle = options.backgroundBlurStyle;
    }
    if (!Container::IsCurrentUseNewPipeline()) {
        LOGW("not support old pipeline");
        return;
    }
    LOGI("Dialog IsCurrentUseNewPipeline.");
    auto task = [dialogProperties, callbackFunc](const RefPtr<NG::OverlayManager>& overlayManager) mutable {
        CHECK_NULL_VOID(overlayManager);
        LOGI("Begin to open custom dialog ");
        if (dialogProperties.isShowInSubWindow) {
            SubwindowManager::GetInstance()->OpenCustomDialogNG(dialogProperties, std::move(callbackFunc));
            if (dialogProperties.isModal) {
                LOGW("temporary not support isShowInSubWindow and isModal");
            }
        } else {
            overlayManager->OpenCustomDialog(dialogProperties, std::move(callbackFunc));
        }
    };
    MainWindowOverlay(std::move(task), "ArkUIOpenCustomDialog");
    return;
}

void FfiPromptShowToastWithOption(NativeShowToastOptions options)
{
    int32_t durationTime = std::clamp(options.duration, TOAST_TIME_DEFAULT, TOAST_TIME_MAX);
    std::string toastMessage(options.message);
    std::string toastBottom(options.bottom);
    bool isRightToLeft = AceApplicationInfo::GetInstance().IsRightToLeft();
    auto task = [options, toastMessage, toastBottom, durationTime, isRightToLeft, containerId = Container::CurrentId()](
                    const RefPtr<NG::OverlayManager>& overlayManager) {
        CHECK_NULL_VOID(overlayManager);
        ContainerScope scope(containerId);
        // parse offset
        double dxVal = options.offset.dx.value;
        int32_t dxType = options.offset.dx.unitType;
        CalcDimension dx = CalcDimension(dxVal, static_cast<DimensionUnit>(dxType));
        double dyVal = options.offset.dy.value;
        int32_t dyType = options.offset.dy.unitType;
        CalcDimension dy = CalcDimension(dyVal, static_cast<DimensionUnit>(dyType));
        auto offset = DimensionOffset(dx, dy);

        Shadow shadow;
        if (options.shadowOption.radius == SHADOW_OPTION_NONE) {
            if (options.shadowStyle == SHADOW_STYLE_NONE) {
                shadow = Shadow::CreateShadow(ShadowStyle::OuterDefaultMD);
            } else {
                shadow = Shadow::CreateShadow(OHOS::Ace::ShadowStyle(options.shadowStyle));
            }
        } else {
            shadow.SetBlurRadius(options.shadowOption.radius);
            shadow.SetShadowType(ShadowType(options.shadowOption.shadowType));
            shadow.SetColor(Color(options.shadowOption.color));
            shadow.SetOffsetX(options.shadowOption.offsetX);
            shadow.SetOffsetY(options.shadowOption.offsetY);
            shadow.SetIsFilled(options.shadowOption.fill);
        };

        auto toastInfo = NG::ToastInfo { .message = toastMessage,
            .duration = durationTime,
            .bottom = toastBottom,
            .isRightToLeft = isRightToLeft,
            .showMode = NG::ToastShowMode(options.showMode),
            .alignment = options.alignment,
            .offset = offset,
            .backgroundColor = Color(options.backgroundColor),
            .textColor = Color(ColorAlphaAdapt(options.textColor)),
            .backgroundBlurStyle = options.backgroundBlurStyle,
            .shadow = shadow,
            .enableHoverMode = options.enableHoverMode,
            .hoverModeArea = HoverModeAreaType(options.hoverModeArea) };
        overlayManager->ShowToast(toastInfo, nullptr);
    };
    MainWindowOverlay(std::move(task), "ArkUIOverlayShowToast");
}

void FfiPromptShowDialogWithOption(NativeShowDialogOptions options, ShowDialogCallBack callbackRef)
{
    std::vector<ButtonInfo> buttons =
        CreateButtonInfoVector(options.buttons, options.buttonsSize, SHOW_DIALOG_BUTTON_NUM_MAX);
    std::set<std::string> callbacks;
    callbacks.emplace("success");
    callbacks.emplace("cancel");

    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
                        int32_t callbackType, int32_t successType) { ffiOnClick(callbackType, successType); };
    TAG_LOGD(AceLogTag::ACE_OVERLAY, "show dialog enter with attr");
    DialogProperties dialogProperties = { .type = DialogType::ALERT_DIALOG,
        .title = options.title,
        .content = options.message,
        .buttons = buttons,
        .backgroundColor = Color(options.backgroundColor),
        .isShowInSubWindow = options.showInSubWindow,
        .isModal = options.isModal,
        .enableHoverMode = options.enableHoverMode,
        .backgroundBlurStyle = options.backgroundBlurStyle,
        .hoverModeArea = HoverModeAreaType(options.hoverModeArea) };
    SetShowDialog(dialogProperties, options);
#if defined(PREVIEW)
    if (dialogProperties.isShowInSubWindow) {
        LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
             "emulator or a real device instead.");
        dialogProperties.isShowInSubWindow = false;
    }
#endif

    ShowDialogInner(dialogProperties, std::move(callback), callbacks);
}

void FfiPromptShowActionMenuWithOption(NativeActionMenuOptions options, ShowActionMenuCallBack callbackRef)
{
    std::vector<ButtonInfo> buttons =
        CreateButtonInfoVector(options.buttons, options.buttonsSize, SHOW_ACTION_MENU_BUTTON_NUM_MAX);
    auto callback = [ffiOnClick = CJLambda::Create(callbackRef)](
                        int32_t callbackType, int32_t successType) { ffiOnClick(callbackType, successType); };
    DialogProperties dialogProperties = {
        .title = options.title,
        .autoCancel = true,
        .isMenu = true,
        .buttons = buttons,
        .isShowInSubWindow = options.showInSubWindow,
        .isModal = options.isModal,
    };
    ShowActionMenuInner(dialogProperties, buttons, std::move(callback));
}
}

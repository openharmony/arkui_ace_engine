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

#include "bridge/cj_frontend/interfaces/cj_ffi/cj_customdialog_controller_ffi.h"

#include "cj_lambda.h"

#include "core/pipeline_ng/pipeline_context.h"

using namespace OHOS::Ace;
using namespace OHOS::FFI;
using namespace OHOS::Ace::Framework;

namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
} // namespace

namespace OHOS::Ace::Framework {
void ParseCjCustomDialogControllerOffset(DimensionOffset& offset, NativeCustomDialogControllerOptions options)
{
    CalcDimension dx(options.offset.dx.value, static_cast<DimensionUnit>(options.offset.dx.unitType));
    CalcDimension dy(options.offset.dy.value, static_cast<DimensionUnit>(options.offset.dy.unitType));
    dx.ResetInvalidValue();
    dy.ResetInvalidValue();
    offset.SetX(dx);
    offset.SetY(dy);
}

void ParseCjCustomDialogControllerOffset(DimensionOffset& offset, NativeCustomDialogControllerOptionsV2 options)
{
    CalcDimension dx(options.offset.dx.value, static_cast<DimensionUnit>(options.offset.dx.unitType));
    CalcDimension dy(options.offset.dy.value, static_cast<DimensionUnit>(options.offset.dy.unitType));
    dx.ResetInvalidValue();
    dy.ResetInvalidValue();
    offset.SetX(dx);
    offset.SetY(dy);
}

void ParseCjCustomDialogControllerMaskRect(DimensionRect& rect, NativeCustomDialogControllerOptions options)
{
    Dimension rectX(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension rectY(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension rectWidth(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension rectHeight(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset rectOffset(rectX, rectY);
    rect.SetWidth(rectWidth);
    rect.SetHeight(rectHeight);
    rect.SetOffset(rectOffset);
}

void ParseCjCustomDialogControllerMaskRect(DimensionRect& rect, NativeCustomDialogControllerOptionsV2 options)
{
    Dimension rectX(options.maskRect.x, static_cast<DimensionUnit>(options.maskRect.xUnit));
    Dimension rectY(options.maskRect.y, static_cast<DimensionUnit>(options.maskRect.yUnit));
    Dimension rectWidth(options.maskRect.width, static_cast<DimensionUnit>(options.maskRect.widthUnit));
    Dimension rectHeight(options.maskRect.height, static_cast<DimensionUnit>(options.maskRect.heightUnit));
    DimensionOffset rectOffset(rectX, rectY);
    rect.SetWidth(rectWidth);
    rect.SetHeight(rectHeight);
    rect.SetOffset(rectOffset);
}

void ParseCjCustomDialogControllerBorderRadius(
    NG::BorderRadiusProperty& radius, NativeCustomDialogControllerOptions options)
{
    CalcDimension radiusCalc(options.cornerRadius.value, static_cast<DimensionUnit>(options.cornerRadius.unitType));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;
}

void ParseCjCustomDialogControllerBorderRadius(
    NG::BorderRadiusProperty& radius, NativeCustomDialogControllerOptionsV2 options)
{
    CalcDimension radiusCalc(options.cornerRadius.value, static_cast<DimensionUnit>(options.cornerRadius.unitType));
    radius.radiusTopLeft = radiusCalc;
    radius.radiusTopRight = radiusCalc;
    radius.radiusBottomLeft = radiusCalc;
    radius.radiusBottomRight = radiusCalc;
    radius.multiValued = true;
}

NativeCustomDialogController::NativeCustomDialogController(NativeCustomDialogControllerOptions options) : FFIData()
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelFunction_ = CJLambda::Create(options.cancel);
    auto onCancel = [cjCallback = cancelFunction_, node = frameNode]() {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        cjCallback();
    };
    dialogProperties_.onCancel = onCancel;
    dialogProperties_.autoCancel = options.autoCancel;
    dialogProperties_.customStyle = options.customStyle;
    if (options.alignment >= 0 && options.alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        dialogProperties_.alignment = DIALOG_ALIGNMENT[options.alignment];
    }
    DimensionOffset offset_;
    ParseCjCustomDialogControllerOffset(offset_, options);
    dialogProperties_.offset = offset_;
    if (options.gridCount.hasValue) {
        dialogProperties_.gridCount = options.gridCount.value;
    }
    dialogProperties_.maskColor = Color(options.maskColor);
    DimensionRect dimenRect;
    ParseCjCustomDialogControllerMaskRect(dimenRect, options);
    dialogProperties_.maskRect = dimenRect;
    if (options.backgroundColor.hasValue) {
        dialogProperties_.backgroundColor = Color(options.backgroundColor.value);
    }
    NG::BorderRadiusProperty radius;
    ParseCjCustomDialogControllerBorderRadius(radius, options);
    dialogProperties_.borderRadius = radius;
    if (options.openAnimation.hasValue) {
        AnimationOption openAnimation;
        ParseCjAnimation(options.openAnimation.value, openAnimation);
        dialogProperties_.openAnimation = openAnimation;
    }
    if (options.closeAnimation.hasValue) {
        AnimationOption closeAnimation;
        ParseCjAnimation(options.closeAnimation.value, closeAnimation);
        dialogProperties_.closeAnimation = closeAnimation;
    }
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
         "emulator or a real device instead.");
#else
    dialogProperties_.isShowInSubWindow = options.showInSubWindow;
#endif
    refself_ = this;
}

NativeCustomDialogController::NativeCustomDialogController(NativeCustomDialogControllerOptionsV2 options) : FFIData()
{
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    cancelFunction_ = CJLambda::Create(options.cancel);
    auto onCancel = [cjCallback = cancelFunction_, node = frameNode]() {
        auto pipelineContext = PipelineContext::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        pipelineContext->UpdateCurrentActiveNode(node);
        cjCallback();
    };
    dialogProperties_.onCancel = onCancel;
    dialogProperties_.autoCancel = options.autoCancel;
    dialogProperties_.customStyle = options.customStyle;
    if (options.alignment >= 0 && options.alignment < static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
        dialogProperties_.alignment = DIALOG_ALIGNMENT[options.alignment];
    }
    DimensionOffset offset_;
    ParseCjCustomDialogControllerOffset(offset_, options);
    dialogProperties_.offset = offset_;
    if (options.gridCount.hasValue) {
        dialogProperties_.gridCount = options.gridCount.value;
    }
    dialogProperties_.maskColor = Color(options.maskColor);
    DimensionRect dimenRect;
    ParseCjCustomDialogControllerMaskRect(dimenRect, options);
    dialogProperties_.maskRect = dimenRect;
    if (options.backgroundColor.hasValue) {
        dialogProperties_.backgroundColor = Color(options.backgroundColor.value);
    }
    NG::BorderRadiusProperty radius;
    ParseCjCustomDialogControllerBorderRadius(radius, options);
    dialogProperties_.borderRadius = radius;
    if (options.openAnimation.hasValue) {
        AnimationOption openAnimation;
        ParseCjAnimation(options.openAnimation.value, openAnimation);
        dialogProperties_.openAnimation = openAnimation;
    }
    if (options.closeAnimation.hasValue) {
        AnimationOption closeAnimation;
        ParseCjAnimation(options.closeAnimation.value, closeAnimation);
        dialogProperties_.closeAnimation = closeAnimation;
    }
    // Parse isModalValue
    if (options.isModal.hasValue) {
        dialogProperties_.isModal = options.isModal.value;
    }
    // Parse onWillDismiss
    if (options.onWillDismiss.hasValue) {
        std::function<void(const int32_t& info, const int32_t& infoTem)> onWillDismissFunc =
            [nativeFunc = CJLambda::Create(options.onWillDismiss.value)](
                const int32_t& info, const int32_t& infoTem) { nativeFunc(info); };
        dialogProperties_.onWillDismiss = onWillDismissFunc;
    }
    // Parse width
    if (options.width.hasValue) {
        auto width = CalcDimension(options.width.value.value, static_cast<DimensionUnit>(options.width.value.unitType));
        dialogProperties_.width = width;
    }
    // Parse height
    if (options.height.hasValue) {
        auto height =
            CalcDimension(options.height.value.value, static_cast<DimensionUnit>(options.height.value.unitType));
        dialogProperties_.height = height;
    }
    // Parse backgroundBlurStyle
    if (options.backgroundBlurStyle.hasValue) {
        auto blurStyle = options.backgroundBlurStyle.value;
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            dialogProperties_.backgroundBlurStyle = blurStyle;
        }
    }
    if (options.borderWidth.hasValue) {
        auto nativeBorderWidth = options.borderWidth.value;
        auto borderWidth = Dimension(nativeBorderWidth.value, static_cast<DimensionUnit>(nativeBorderWidth.unitType));
        auto borderWidthProp = NG::BorderWidthProperty({ borderWidth, borderWidth, borderWidth, borderWidth });
        dialogProperties_.borderWidth = borderWidthProp;
    }
    if (options.borderColor.hasValue) {
        NG::BorderColorProperty colorProperty;
        Color borderColor = Color(options.borderColor.value);
        colorProperty.SetColor(borderColor);
        dialogProperties_.borderColor = colorProperty;
    }
    if (options.borderStyle.hasValue) {
        NG::BorderStyleProperty borderStyle;
        auto nativeBorderSytle = options.borderStyle.value;
        borderStyle.styleLeft = static_cast<BorderStyle>(nativeBorderSytle.left);
        borderStyle.styleRight = static_cast<BorderStyle>(nativeBorderSytle.right);
        borderStyle.styleTop = static_cast<BorderStyle>(nativeBorderSytle.top);
        borderStyle.styleBottom = static_cast<BorderStyle>(nativeBorderSytle.bottom);
        borderStyle.multiValued = true;
        dialogProperties_.borderStyle = borderStyle;
    }
    if (options.shadow.hasValue) {
        NativeShadowOptions shadowOptions = options.shadow.options;
        // Parse shadow
        Shadow shadow;
        if (LessNotEqual(shadowOptions.radius, 0.0)) {
            shadowOptions.radius = 0.0;
        }
        shadow.SetBlurRadius(shadowOptions.radius);
        Color shadowColor = Color(shadowOptions.color);
        shadow.SetColor(shadowColor);
        shadow.SetShadowType(static_cast<ShadowType>(shadowOptions.shadowType));
        shadow.SetIsFilled(shadowOptions.fill);
        shadow.SetOffsetX(shadowOptions.offsetX);
        shadow.SetOffsetY(shadowOptions.offsetY);
        dialogProperties_.shadow = shadow;
    }
#if defined(PREVIEW)
    LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
         "emulator or a real device instead.");
#else
    dialogProperties_.isShowInSubWindow = options.showInSubWindow;
#endif
    refself_ = this;
}

void NativeCustomDialogController::OpenDialog()
{
    if (!builderFunction_) {
        return;
    }

    if (!ownerView_) {
        return;
    }
    auto containerId = ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto buildFunc = [builder = builderFunction_, node = frameNode, context = pipelineContext]() {
        {
            context->UpdateCurrentActiveNode(node);
            builder();
        }
    };

    auto cancelTask = ([cancelCallback = cancelFunction_, node = frameNode, context = pipelineContext]() {
        if (cancelCallback) {
            context->UpdateCurrentActiveNode(node);
            cancelCallback();
        }
    });

    auto currentObj = Container::Current();
    if (currentObj && currentObj->IsSceneBoardWindow() && !dialogProperties_.windowScene.Upgrade()) {
        dialogProperties_.isSceneBoardDialog = true;
        auto viewNode = ownerView_->GetViewNode();
        CHECK_NULL_VOID(viewNode);
        auto parentCustom = AceType::DynamicCast<NG::CustomNode>(viewNode);
        CHECK_NULL_VOID(parentCustom);
        auto parent = parentCustom->GetParent();
        while (parent && parent->GetTag() != "WindowScene") {
            parent = parent->GetParent();
        }
        if (parent) {
            dialogProperties_.windowScene = parent;
        }
    }
    dialogProperties_.isSysBlurStyle =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) ? true : false;
    CustomDialogControllerModel::GetInstance()->SetOpenDialog(dialogProperties_, AccessibilityManager::WeakClaim(this),
        dialogs_, pending_, isShown_, std::move(cancelTask), std::move(buildFunc), dialogComponent_, customDialog_,
        dialogOperation_);
    return;
}

void NativeCustomDialogController::CloseDialog()
{
    if (ownerView_ == nullptr) {
        return;
    }
    auto containerId = ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cancelTask = ([cancelCallback = cancelFunction_, node = frameNode]() {
        if (cancelCallback) {
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            cancelCallback();
        }
    });

    CustomDialogControllerModel::GetInstance()->SetCloseDialog(dialogProperties_, AccessibilityManager::WeakClaim(this),
        dialogs_, pending_, isShown_, std::move(cancelTask), dialogComponent_, customDialog_, dialogOperation_);
}
} // namespace OHOS::Ace::Framework

extern "C" {
int64_t FfiOHOSAceFrameworkCustomDialogControllerCtor(NativeCustomDialogControllerOptions options)
{
    auto controller = FFIData::Create<NativeCustomDialogController>(options);
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

int64_t FfiOHOSAceFrameworkCustomDialogControllerCtorV2(NativeCustomDialogControllerOptionsV2 options)
{
    auto controller = FFIData::Create<NativeCustomDialogController>(options);
    if (controller == nullptr) {
        return FFI_ERROR_CODE;
    }
    return controller->GetID();
}

void FfiOHOSAceFrameworkCustomDialogControllerSetBuilder(int64_t controllerId, void (*builder)())
{
    auto nativeController = FFIData::GetData<NativeCustomDialogController>(controllerId);
    if (nativeController != nullptr) {
        auto builderFunction = CJLambda::Create(builder);
        nativeController->SetBuilder(builderFunction);
    } else {
        LOGE("CustomDialog: invalid CustomDialogController id");
    }
}

void FfiOHOSAceFrameworkCustomDialogControllerBindView(int64_t controllerId, int64_t nativeViewId)
{
    auto nativeView = FFIData::GetData<NativeView>(nativeViewId);
    if (!nativeView) {
        LOGE("FfiOHOSAceFrameworkCustomDialogControllerBindView: invalid nativeView id");
        return;
    }

    auto nativeController = FFIData::GetData<NativeCustomDialogController>(controllerId);
    if (nativeController != nullptr) {
        nativeController->SetView(nativeView);
    } else {
        LOGE("FfiOHOSAceFrameworkCustomDialogControllerBindView: invalid CustomDialogController id");
    }
}

void FfiOHOSAceFrameworkCustomDialogControllerOpen(int64_t id)
{
    auto nativeController = FFIData::GetData<NativeCustomDialogController>(id);
    if (nativeController != nullptr) {
        nativeController->OpenDialog();
    } else {
        LOGE("CustomDialog: invalid CustomDialogController id");
    }
}

void FfiOHOSAceFrameworkCustomDialogControllerClose(int64_t id)
{
    auto nativeController = FFIData::GetData<NativeCustomDialogController>(id);
    if (nativeController != nullptr) {
        nativeController->CloseDialog();
    } else {
        LOGE("CustomDialog: invalid CustomDialogController id");
    }
}
}

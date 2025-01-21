/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/dialog/js_custom_dialog_controller.h"

#include "base/subwindow/subwindow_manager.h"
#include "base/utils/system_properties.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/jsi/jsi_types.h"
#include "bridge/declarative_frontend/jsview/models/custom_dialog_controller_model_impl.h"
#include "core/common/ace_engine.h"
#include "core/common/container.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "frameworks/bridge/declarative_frontend/engine/jsi/js_ui_index.h"

namespace OHOS::Ace {
std::unique_ptr<CustomDialogControllerModel> CustomDialogControllerModel::instance_ = nullptr;
std::mutex CustomDialogControllerModel::mutex_;
CustomDialogControllerModel* CustomDialogControllerModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::CustomDialogControllerModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::CustomDialogControllerModelNG());
            } else {
                instance_.reset(new Framework::CustomDialogControllerModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
const std::vector<DialogAlignment> DIALOG_ALIGNMENT = { DialogAlignment::TOP, DialogAlignment::CENTER,
    DialogAlignment::BOTTOM, DialogAlignment::DEFAULT, DialogAlignment::TOP_START, DialogAlignment::TOP_END,
    DialogAlignment::CENTER_START, DialogAlignment::CENTER_END, DialogAlignment::BOTTOM_START,
    DialogAlignment::BOTTOM_END };
const std::vector<KeyboardAvoidMode> KEYBOARD_AVOID_MODE = { KeyboardAvoidMode::DEFAULT, KeyboardAvoidMode::NONE };
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;
constexpr float AVOID_DISTANCE = 16.0f;

} // namespace

static std::atomic<int32_t> controllerId = 0;
void JSCustomDialogController::ConstructorCallback(const JSCallbackInfo& info)
{
    int argc = info.Length();
    if (argc > 1 && !info[0]->IsUndefined() && info[0]->IsObject() && !info[1]->IsUndefined() && info[1]->IsObject()) {
        JSRef<JSObject> constructorArg = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSObject> ownerObj = JSRef<JSObject>::Cast(info[1]);

        // check if owner object is set
        JSView* ownerView = ownerObj->Unwrap<JSView>();
        auto instance = AceType::MakeRefPtr<JSCustomDialogController>(ownerView);
        if (ownerView == nullptr) {
            instance->IncRefCount();
            info.SetReturnValue(AceType::RawPtr(instance));
            instance = nullptr;
            return;
        }

        // Process builder function.
        JSRef<JSVal> builderCallback = constructorArg->GetProperty("builder");
        if (!builderCallback->IsUndefined() && builderCallback->IsFunction()) {
            instance->jsBuilderFunction_ =
                AceType::MakeRefPtr<JsWeakFunction>(ownerObj, JSRef<JSFunc>::Cast(builderCallback));
        } else {
            instance->jsBuilderFunction_ = nullptr;
            instance->IncRefCount();
            info.SetReturnValue(AceType::RawPtr(instance));
            instance = nullptr;
            return;
        }

        // Process cancel function.
        JSRef<JSVal> cancelCallback = constructorArg->GetProperty("cancel");
        if (!cancelCallback->IsUndefined() && cancelCallback->IsFunction()) {
            auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
            auto jsCancelFunction = AceType::MakeRefPtr<JsWeakFunction>(ownerObj, JSRef<JSFunc>::Cast(cancelCallback));
            instance->jsCancelFunction_ = jsCancelFunction;

            auto onCancel = [execCtx = info.GetExecutionContext(), func = std::move(jsCancelFunction),
                                node = frameNode]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onCancel");
                auto pipelineContext = PipelineContext::GetCurrentContext();
                CHECK_NULL_VOID(pipelineContext);
                pipelineContext->UpdateCurrentActiveNode(node);
                func->Execute();
            };
            instance->dialogProperties_.onCancel = onCancel;
        }

        std::function<void(const int32_t& info, const int32_t& instanceId)> onWillDismissFunc = nullptr;
        JSViewAbstract::ParseDialogCallback(constructorArg, onWillDismissFunc);
        instance->dialogProperties_.onWillDismiss = onWillDismissFunc;

        // Parses autoCancel.
        JSRef<JSVal> autoCancelValue = constructorArg->GetProperty("autoCancel");
        if (autoCancelValue->IsBoolean()) {
            instance->dialogProperties_.autoCancel = autoCancelValue->ToBoolean();
        }

        // Parses customStyle.
        JSRef<JSVal> customStyleValue = constructorArg->GetProperty("customStyle");
        if (customStyleValue->IsBoolean()) {
            instance->dialogProperties_.customStyle = customStyleValue->ToBoolean();
        }

        // Parse alignment
        auto alignmentValue = constructorArg->GetProperty("alignment");
        if (alignmentValue->IsNumber()) {
            auto alignment = alignmentValue->ToNumber<int32_t>();
            if (alignment >= 0 && alignment <= static_cast<int32_t>(DIALOG_ALIGNMENT.size())) {
                instance->dialogProperties_.alignment = DIALOG_ALIGNMENT[alignment];
            }
        }

        // Parse keyboardAvoidMode
        auto avoidModeValue = constructorArg->GetProperty("keyboardAvoidMode");
        if (avoidModeValue->IsNumber()) {
            auto avoidMode = avoidModeValue->ToNumber<int32_t>();
            if (avoidMode >= 0 && avoidMode < static_cast<int32_t>(KEYBOARD_AVOID_MODE.size())) {
                instance->dialogProperties_.keyboardAvoidMode = KEYBOARD_AVOID_MODE[avoidMode];
            }
        }

        // Parse keyboardAvoidDistance
        auto avoidDistance = constructorArg->GetProperty("keyboardAvoidDistance");
        if (avoidDistance->IsObject()) {
            JSRef<JSObject> avoidDistanceobj = JSRef<JSObject>::Cast(avoidDistance);
            auto avoidDisValue = avoidDistanceobj->GetProperty(static_cast<int32_t>(ArkUIIndex::VALUE));
            auto jsAvoidDisUnit = avoidDistanceobj->GetProperty(static_cast<int32_t>(ArkUIIndex::UNIT));
            DimensionUnit avoidDisUnit = OHOS::Ace::DimensionUnit::VP;
            if (jsAvoidDisUnit->IsNumber()) {
                avoidDisUnit = static_cast<DimensionUnit>(jsAvoidDisUnit->ToNumber<int32_t>());
            }
            if (avoidDisValue->IsNumber() && avoidDisValue->ToNumber<double>() >= 0 &&
                avoidDisUnit >= OHOS::Ace::DimensionUnit::PX && avoidDisUnit <= OHOS::Ace::DimensionUnit::CALC &&
                avoidDisUnit != OHOS::Ace::DimensionUnit::PERCENT) {
                Dimension avoidDistanceDimension(avoidDisValue->ToNumber<double>(), avoidDisUnit);
                instance->dialogProperties_.keyboardAvoidDistance = avoidDistanceDimension;
            } else {
                Dimension avoidDistanceDimension(AVOID_DISTANCE, OHOS::Ace::DimensionUnit::VP);
                instance->dialogProperties_.keyboardAvoidDistance = avoidDistanceDimension;
            }
        }

        // Parse offset
        auto offsetValue = constructorArg->GetProperty("offset");
        if (offsetValue->IsObject()) {
            auto offsetObj = JSRef<JSObject>::Cast(offsetValue);
            CalcDimension dx;
            auto dxValue = offsetObj->GetProperty("dx");
            JSViewAbstract::ParseJsDimensionVp(dxValue, dx);
            CalcDimension dy;
            auto dyValue = offsetObj->GetProperty("dy");
            JSViewAbstract::ParseJsDimensionVp(dyValue, dy);
            dx.ResetInvalidValue();
            dy.ResetInvalidValue();
            instance->dialogProperties_.offset = DimensionOffset(dx, dy);
        }

        // Parses gridCount.
        auto gridCountValue = constructorArg->GetProperty("gridCount");
        if (gridCountValue->IsNumber()) {
            instance->dialogProperties_.gridCount = gridCountValue->ToNumber<int32_t>();
        }

        // Parse maskColor.
        auto maskColorValue = constructorArg->GetProperty("maskColor");
        Color maskColor;
        if (JSViewAbstract::ParseJsColor(maskColorValue, maskColor)) {
            instance->dialogProperties_.maskColor = maskColor;
        }

        // Parse maskRect.
        auto maskRectValue = constructorArg->GetProperty("maskRect");
        DimensionRect maskRect;
        if (JSViewAbstract::ParseJsDimensionRect(maskRectValue, maskRect)) {
            instance->dialogProperties_.maskRect = maskRect;
        }

        // Parse backgroundColor.
        auto backgroundColorValue = constructorArg->GetProperty("backgroundColor");
        Color backgroundColor;
        if (JSViewAbstract::ParseJsColor(backgroundColorValue, backgroundColor)) {
            instance->dialogProperties_.backgroundColor = backgroundColor;
        }

        // Parse backgroundBlurStyle.
        auto backgroundBlurStyle = constructorArg->GetProperty("backgroundBlurStyle");
        if (backgroundBlurStyle->IsNumber()) {
            auto blurStyle = backgroundBlurStyle->ToNumber<int32_t>();
            if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
                blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
                instance->dialogProperties_.backgroundBlurStyle = blurStyle;
            }
        }

        auto execContext = info.GetExecutionContext();
        // Parse openAnimation.
        auto openAnimationValue = constructorArg->GetProperty("openAnimation");
        AnimationOption openAnimation;
        if (ParseAnimation(execContext, openAnimationValue, openAnimation)) {
            instance->dialogProperties_.openAnimation = openAnimation;
        }

        // Parse closeAnimation.
        auto closeAnimationValue = constructorArg->GetProperty("closeAnimation");
        AnimationOption closeAnimation;
        if (ParseAnimation(execContext, closeAnimationValue, closeAnimation)) {
            instance->dialogProperties_.closeAnimation = closeAnimation;
        }

        // Parse showInSubWindowValue.
        auto showInSubWindowValue = constructorArg->GetProperty("showInSubWindow");
        if (showInSubWindowValue->IsBoolean()) {
#if defined(PREVIEW)
            LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
                 "emulator or a real device instead.");
#else
            instance->dialogProperties_.isShowInSubWindow = showInSubWindowValue->ToBoolean();
#endif
        }

        // Parse isModal.
        auto isModalValue = constructorArg->GetProperty("isModal");
        if (isModalValue->IsBoolean()) {
            instance->dialogProperties_.isModal = isModalValue->ToBoolean();
        }

        instance->dialogProperties_.controllerId = controllerId.fetch_add(1, std::memory_order_relaxed);
        JSViewAbstract::SetDialogProperties(constructorArg, instance->dialogProperties_);
        JSViewAbstract::SetDialogHoverModeProperties(constructorArg, instance->dialogProperties_);
        instance->IncRefCount();
        info.SetReturnValue(AceType::RawPtr(instance));
    }
}

void JSCustomDialogController::DestructorCallback(JSCustomDialogController* controller)
{
    if (controller != nullptr) {
        controller->ownerView_ = nullptr;
        controller->DecRefCount();
    }
}

void JSCustomDialogController::JsOpenDialog(const JSCallbackInfo& info)
{
    if (!jsBuilderFunction_) {
        return;
    }

    if (this->ownerView_ == nullptr) {
        return;
    }
    auto containerId = this->ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);
    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto pipelineContext = PipelineContext::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);

    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        return;
    }

    auto buildFunc = [buildfunc = jsBuilderFunction_, node = frameNode, context = pipelineContext]() {
        {
            ACE_SCORING_EVENT("CustomDialog.builder");
            context->UpdateCurrentActiveNode(node);
            buildfunc->Execute();
        }
    };

    auto cancelTask = ([cancelCallback = jsCancelFunction_, node = frameNode, context = pipelineContext]() {
        if (cancelCallback) {
            ACE_SCORING_EVENT("CustomDialog.cancel");
            context->UpdateCurrentActiveNode(node);
            cancelCallback->Execute();
        }
    });

    auto container = Container::Current();
    if (container && container->IsScenceBoardWindow() && !dialogProperties_.windowScene.Upgrade()) {
        dialogProperties_.isScenceBoardDialog = true;
        auto viewNode = this->ownerView_->GetViewNode();
        CHECK_NULL_VOID(viewNode);
        auto parentCustom = AceType::DynamicCast<NG::CustomNode>(viewNode);
        CHECK_NULL_VOID(parentCustom);
        auto parent = parentCustom->GetParent();
        while (parent && parent->GetTag() != V2::WINDOW_SCENE_ETS_TAG) {
            parent = parent->GetParent();
        }
        if (parent) {
            dialogProperties_.windowScene = parent;
        }
    }
    dialogProperties_.isSysBlurStyle =
        Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TWELVE) ? true : false;
    CustomDialogControllerModel::GetInstance()->SetOpenDialog(dialogProperties_, WeakClaim(this), dialogs_, pending_,
        isShown_, std::move(cancelTask), std::move(buildFunc), dialogComponent_, customDialog_, dialogOperation_);
}

void JSCustomDialogController::JsCloseDialog(const JSCallbackInfo& info)
{

    if (this->ownerView_ == nullptr) {
        return;
    }
    auto containerId = this->ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);

    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        return;
    }

    WeakPtr<NG::FrameNode> frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto cancelTask = ([cancelCallback = jsCancelFunction_, node = frameNode]() {
        if (cancelCallback) {
            ACE_SCORING_EVENT("CustomDialog.cancel");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            cancelCallback->Execute();
        }
    });

    CustomDialogControllerModel::GetInstance()->SetCloseDialog(dialogProperties_, WeakClaim(this), dialogs_, pending_,
        isShown_, std::move(cancelTask), dialogComponent_, customDialog_, dialogOperation_);
}

bool JSCustomDialogController::ParseAnimation(
    const JsiExecutionContext& execContext, const JsiRef<JsiValue>& animationValue, AnimationOption& result)
{
    if (animationValue->IsNull() || !animationValue->IsObject()) {
        return false;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(animationValue);
    // If the attribute does not exist, the default value is used.
    int32_t duration = obj->GetPropertyValue<int32_t>("duration", DEFAULT_ANIMATION_DURATION);
    int32_t delay = obj->GetPropertyValue<int32_t>("delay", 0);
    int32_t iterations = obj->GetPropertyValue<int32_t>("iterations", 1);
    float tempo = obj->GetPropertyValue<float>("tempo", 1.0);
    auto finishCallbackType = static_cast<FinishCallbackType>(obj->GetPropertyValue<int32_t>("finishCallbackType", 0));
    if (tempo < 0) {
        tempo = 1.0f;
    } else if (tempo == 0) {
        tempo = 1000.0f;
    }
    auto direction = StringToAnimationDirection(obj->GetPropertyValue<std::string>("playMode", "normal"));
    RefPtr<Curve> curve;
    JSRef<JSVal> curveArgs = obj->GetProperty("curve");
    if (curveArgs->IsString()) {
        curve = CreateCurve(obj->GetPropertyValue<std::string>("curve", "linear"));
    } else if (curveArgs->IsObject()) {
        JSRef<JSObject> curveObj = JSRef<JSObject>::Cast(curveArgs);
        JSRef<JSVal> curveString = curveObj->GetProperty("__curveString");
        if (!curveString->IsString()) {
            // Default AnimationOption which is invalid.
            return false;
        }
        curve = CreateCurve(curveString->ToString());
    } else {
        curve = Curves::EASE_IN_OUT;
    }
    result.SetDuration(duration);
    result.SetDelay(delay);
    result.SetIteration(iterations);
    result.SetTempo(tempo);
    result.SetAnimationDirection(direction);
    result.SetCurve(curve);
    result.SetFinishCallbackType(finishCallbackType);

    JSRef<JSVal> onFinish = obj->GetProperty("onFinish");
    std::function<void()> onFinishEvent;
    if (onFinish->IsFunction()) {
        auto frameNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto jsFunc = AceType::MakeRefPtr<JsWeakFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        onFinishEvent = [execCtx = execContext, func = std::move(jsFunc), node = frameNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CustomDialog.onFinish");
            auto pipelineContext = PipelineContext::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            pipelineContext->UpdateCurrentActiveNode(node);
            func->Execute();
        };
        result.SetOnFinishEvent(onFinishEvent);
    }
    return true;
}

void JSCustomDialogController::JSBind(BindingTarget object)
{
    JSClass<JSCustomDialogController>::Declare("NativeCustomDialogController");
    JSClass<JSCustomDialogController>::CustomMethod("open", &JSCustomDialogController::JsOpenDialog);
    JSClass<JSCustomDialogController>::CustomMethod("close", &JSCustomDialogController::JsCloseDialog);
    JSClass<JSCustomDialogController>::Bind(
        object, &JSCustomDialogController::ConstructorCallback, &JSCustomDialogController::DestructorCallback);
}
} // namespace OHOS::Ace::Framework

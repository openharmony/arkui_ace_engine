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
#include "core/components_ng/pattern/dialog/custom_dialog_controller_model_ng.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "frameworks/bridge/common/utils/engine_helper.h"

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
constexpr int32_t DEFAULT_ANIMATION_DURATION = 200;

} // namespace

void JSCustomDialogController::ConstructorCallback(const JSCallbackInfo& info)
{
    int argc = info.Length();
    if (argc > 1 && !info[0]->IsUndefined() && info[0]->IsObject() && !info[1]->IsUndefined() && info[1]->IsObject()) {
        JSRef<JSObject> constructorArg = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSObject> ownerObj = JSRef<JSObject>::Cast(info[1]);

        // check if owner object is set
        JSView* ownerView = ownerObj->Unwrap<JSView>();
        if (ownerView == nullptr) {
            LOGE("JSCustomDialogController creation with invalid arguments. Missing \'ownerView\'");
            return;
        }

        auto instance = new JSCustomDialogController(ownerView);
        instance->ownerView_ = ownerView;

        // Process builder function.
        JSRef<JSVal> builderCallback = constructorArg->GetProperty("builder");
        if (!builderCallback->IsUndefined() && builderCallback->IsFunction()) {
            instance->jsBuilderFunction_ =
                AceType::MakeRefPtr<JsFunction>(ownerObj, JSRef<JSFunc>::Cast(builderCallback));
        } else {
            delete instance;
            instance = nullptr;
            LOGE("JSCustomDialogController invalid builder function argument");
            return;
        }

        // Process cancel function.
        JSRef<JSVal> cancelCallback = constructorArg->GetProperty("cancel");
        if (!cancelCallback->IsUndefined() && cancelCallback->IsFunction()) {
            auto jsCancelFunction = AceType::MakeRefPtr<JsFunction>(ownerObj, JSRef<JSFunc>::Cast(cancelCallback));
            instance->jsCancelFunction_ = jsCancelFunction;

            auto onCancel = [execCtx = info.GetExecutionContext(), func = std::move(jsCancelFunction)]() {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                ACE_SCORING_EVENT("onCancel");
                func->Execute();
            };
            instance->dialogProperties_.onCancel = onCancel;
        }

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

        auto showInSubWindowValue = constructorArg->GetProperty("showInSubWindow");
        if (showInSubWindowValue->IsBoolean()) {
#if defined(PREVIEW)
            LOGW("[Engine Log] Unable to use the SubWindow in the Previewer. Perform this operation on the "
                 "emulator or a real device instead.");
#else
            instance->dialogProperties_.isShowInSubWindow = showInSubWindowValue->ToBoolean();
#endif
        }
        if (SystemProperties::IsSceneBoardEnabled()) {
            instance->dialogProperties_.isShowInSubWindow = false;
        }

        info.SetReturnValue(instance);
    } else {
        LOGE("JSView creation with invalid arguments.");
    }
}

void JSCustomDialogController::DestructorCallback(JSCustomDialogController* controller)
{
    if (controller != nullptr) {
        controller->ownerView_ = nullptr;
        delete controller;
    }
}

void JSCustomDialogController::JsOpenDialog(const JSCallbackInfo& info)
{
    LOGI("JSCustomDialogController(JsOpenDialog)");
    if (!jsBuilderFunction_) {
        LOGE("Builder of CustomDialog is null.");
        return;
    }

    auto containerId = this->ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);

    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }

    auto buildFunc = [buildfunc = jsBuilderFunction_]() {
        {
            ACE_SCORING_EVENT("CustomDialog.builder");
            buildfunc->Execute();
        }
    };

    auto cancelTask = ([cancelCallback = jsCancelFunction_]() {
        if (cancelCallback) {
            ACE_SCORING_EVENT("CustomDialog.cancel");
            cancelCallback->Execute();
        }
    });

    if (SystemProperties::IsSceneBoardEnabled() && !dialogProperties_.windowScene.Upgrade()) {
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

    CustomDialogControllerModel::GetInstance()->SetOpenDialog(dialogProperties_, dialogs_, pending_, isShown_,
        std::move(cancelTask), std::move(buildFunc), dialogComponent_, customDialog_, dialogOperation_);
    return;
}

void JSCustomDialogController::JsCloseDialog(const JSCallbackInfo& info)
{
    LOGI("JSCustomDialogController(JsCloseDialog)");

    auto containerId = this->ownerView_->GetInstanceId();
    ContainerScope containerScope(containerId);

    auto scopedDelegate = EngineHelper::GetCurrentDelegate();
    if (!scopedDelegate) {
        // this case usually means there is no foreground container, need to figure out the reason.
        LOGE("scopedDelegate is null, please check");
        return;
    }

    auto cancelTask = ([cancelCallback = jsCancelFunction_]() {
        if (cancelCallback) {
            ACE_SCORING_EVENT("CustomDialog.cancel");
            cancelCallback->Execute();
        }
    });

    CustomDialogControllerModel::GetInstance()->SetCloseDialog(dialogProperties_, dialogs_, pending_, isShown_,
        std::move(cancelTask), dialogComponent_, customDialog_, dialogOperation_);
}

bool JSCustomDialogController::ParseAnimation(
    const JsiExecutionContext& execContext, const JsiRef<JsiValue>& animationValue, AnimationOption& result)
{
    if (animationValue->IsNull() || !animationValue->IsObject()) {
        return false;
    }
    auto animationArgs = JsonUtil::ParseJsonString(animationValue->ToString());
    if (animationArgs->IsNull()) {
        return false;
    }
    // If the attribute does not exist, the default value is used.
    auto duration = animationArgs->GetInt("duration", DEFAULT_ANIMATION_DURATION);
    auto delay = animationArgs->GetInt("delay", 0);
    auto iterations = animationArgs->GetInt("iterations", 1);
    auto tempo = static_cast<float>(animationArgs->GetDouble("tempo", 1.0));
    if (NonPositive(tempo)) {
        tempo = 1.0f;
    }
    auto direction = StringToAnimationDirection(animationArgs->GetString("playMode", "normal"));
    RefPtr<Curve> curve;
    auto curveArgs = animationArgs->GetValue("curve");
    if (curveArgs->IsString()) {
        curve = CreateCurve(animationArgs->GetString("curve", "linear"));
    } else if (curveArgs->IsObject()) {
        auto curveString = curveArgs->GetValue("__curveString");
        if (!curveString) {
            // Default AnimationOption which is invalid.
            return false;
        }
        curve = CreateCurve(curveString->GetString());
    } else {
        curve = Curves::EASE_IN_OUT;
    }
    result.SetDuration(duration);
    result.SetDelay(delay);
    result.SetIteration(iterations);
    result.SetTempo(tempo);
    result.SetAnimationDirection(direction);
    result.SetCurve(curve);

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(animationValue);
    JSRef<JSVal> onFinish = obj->GetProperty("onFinish");
    std::function<void()> onFinishEvent;
    if (onFinish->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onFinish));
        onFinishEvent = [execCtx = execContext, func = std::move(jsFunc)]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("CustomDialog.onFinish");
            func->Execute();
        };
        result.SetOnFinishEvent(onFinishEvent);
    }
    return true;
}

void JSCustomDialogController::JSBind(BindingTarget object)
{
    JSClass<JSCustomDialogController>::Declare("CustomDialogController");
    JSClass<JSCustomDialogController>::CustomMethod("open", &JSCustomDialogController::JsOpenDialog);
    JSClass<JSCustomDialogController>::CustomMethod("close", &JSCustomDialogController::JsCloseDialog);
    JSClass<JSCustomDialogController>::Bind(
        object, &JSCustomDialogController::ConstructorCallback, &JSCustomDialogController::DestructorCallback);
}
} // namespace OHOS::Ace::Framework
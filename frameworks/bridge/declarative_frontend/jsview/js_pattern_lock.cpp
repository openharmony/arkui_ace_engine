/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_pattern_lock.h"

#include "bridge/declarative_frontend/jsview/models/patternlock_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_pattern_lock_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/patternlock/patternlock_model_ng.h"
#include "core/components_v2/pattern_lock/pattern_lock_component.h"

namespace OHOS::Ace {

std::unique_ptr<PatternLockModel> PatternLockModel::instance_ = nullptr;
std::mutex PatternLockModel::mutex_;
const std::vector<V2::PatternLockChallengeResult> CHALLENGE_RESULT = { V2::PatternLockChallengeResult::CORRECT,
    V2::PatternLockChallengeResult::WRONG };

PatternLockModel* PatternLockModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::PatternLockModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::PatternLockModelNG());
            } else {
                instance_.reset(new Framework::PatternLockModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
JSRef<JSArray> JSPatternLock::ChoosePointToJSValue(std::vector<int> input)
{
    JSRef<JSArray> arr = JSRef<JSArray>::New();
    for (size_t i = 0; i < input.size(); i++) {
        arr->SetValueAt(i, ConvertToJSValue(input[i]));
    }
    return arr;
}
void JSPatternLock::Create(const JSCallbackInfo& info)
{
    auto controller = PatternLockModel::GetInstance()->Create();
    JSPatternLockTheme::ApplyTheme();

    if (info.Length() > 0 && info[0]->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSPatternLockController>();
        if (jsController) {
            jsController->SetController(controller);
        }
    }
}
void JSPatternLock::JSBind(BindingTarget globalObj)
{
    JSClass<JSPatternLock>::Declare("PatternLock");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSPatternLock>::StaticMethod("create", &JSPatternLock::Create, opt);
    JSClass<JSPatternLock>::StaticMethod("onPatternComplete", &JSPatternLock::SetPatternComplete);
    JSClass<JSPatternLock>::StaticMethod("regularColor", &JSPatternLock::SetRegularColor, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("selectedColor", &JSPatternLock::SetSelectedColor, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("activeColor", &JSPatternLock::SetActiveColor, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("pathColor", &JSPatternLock::SetPathColor, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("pathStrokeWidth", &JSPatternLock::SetPathStrokeWidth);
    JSClass<JSPatternLock>::StaticMethod("circleRadius", &JSPatternLock::SetCircleRadius, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("sideLength", &JSPatternLock::SetSideLength, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("autoReset", &JSPatternLock::SetAutoReset, MethodOptions::NONE);
    JSClass<JSPatternLock>::StaticMethod("activateCircleStyle", &JSPatternLock::SetActivateCircleStyle);
    JSClass<JSPatternLock>::StaticMethod("onDotConnect", &JSPatternLock::SetDotConnect);
    JSClass<JSPatternLock>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSPatternLock>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSPatternLock>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSPatternLock>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSPatternLock>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSPatternLock>::InheritAndBind<JSViewAbstract>(globalObj);
}
void JSPatternLock::SetDefaultTheme(OHOS::Ace::RefPtr<OHOS::Ace::V2::PatternLockComponent>& patternLock)
{
    auto lockTheme = GetTheme<V2::PatternLockTheme>();
    if (!lockTheme) {
        return;
    }
    patternLock->SetRegularColor(lockTheme->GetRegularColor());
    patternLock->SetSelectedColor(lockTheme->GetSelectedColor());
    patternLock->SetActiveColor(lockTheme->GetActiveColor());
    patternLock->SetPathColor(lockTheme->GetPathColor());
}

void JSPatternLock::SetPatternComplete(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    auto onComplete = [execCtx = args.GetExecutionContext(), func = JSRef<JSFunc>::Cast(args[0])](
                          const BaseEventInfo* event) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* eventInfo = TypeInfoHelper::DynamicCast<V2::PatternCompleteEvent>(event);
        CHECK_NULL_VOID(eventInfo);
        JSRef<JSVal> params[] = { ChoosePointToJSValue(eventInfo->GetInput()) };
        func->Call(JSRef<JSObject>(), ArraySize(params), params);
    };

    PatternLockModel::GetInstance()->SetPatternComplete(std::move(onComplete));
}
void JSPatternLock::SetSelectedColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color selectedColor;
    if (!ParseJsColor(info[0], selectedColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        selectedColor = patternLockTheme->GetSelectedColor();
    }

    PatternLockModel::GetInstance()->SetSelectedColor(selectedColor);
}
void JSPatternLock::SetAutoReset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    if (!info[0]->IsBoolean()) {
        PatternLockModel::GetInstance()->SetAutoReset(true);
        return;
    }
    PatternLockModel::GetInstance()->SetAutoReset(info[0]->ToBoolean());
}

void JSPatternLock::SetPathColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color pathColor;
    if (!ParseJsColor(info[0], pathColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        pathColor = patternLockTheme->GetPathColor();
    }

    PatternLockModel::GetInstance()->SetPathColor(pathColor);
}
void JSPatternLock::SetActiveColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color activeColor;
    if (!ParseJsColor(info[0], activeColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        activeColor = patternLockTheme->GetActiveColor();
    }

    PatternLockModel::GetInstance()->SetActiveColor(activeColor);
}
void JSPatternLock::SetRegularColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    Color regularColor;
    if (!ParseJsColor(info[0], regularColor)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        regularColor = patternLockTheme->GetRegularColor();
    }

    PatternLockModel::GetInstance()->SetRegularColor(regularColor);
}
void JSPatternLock::SetCircleRadius(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension radius;
    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVp(info[0], radius)) {
            return;
        }
        if (radius.IsNonNegative()) {
            PatternLockModel::GetInstance()->SetCircleRadius(radius);
        }
    } else {
        if (!ParseJsDimensionVp(info[0], radius) || radius.IsNonPositive()) {
            RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
            CHECK_NULL_VOID(patternLockTheme);
            radius = patternLockTheme->GetCircleRadius();
        }
        PatternLockModel::GetInstance()->SetCircleRadius(radius);
    }
}
void JSPatternLock::SetSideLength(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension sideLength;
    if (!ParseJsDimensionVp(info[0], sideLength)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        sideLength = patternLockTheme->GetSideLength();
    }

    PatternLockModel::GetInstance()->SetSideLength(sideLength);
}
void JSPatternLock::SetPathStrokeWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension lineWidth;
    if (!ParseJsDimensionVp(info[0], lineWidth)) {
        RefPtr<V2::PatternLockTheme> patternLockTheme = GetTheme<V2::PatternLockTheme>();
        CHECK_NULL_VOID(patternLockTheme);
        lineWidth = patternLockTheme->GetPathStrokeWidth();
    }

    PatternLockModel::GetInstance()->SetStrokeWidth(lineWidth);
}
void JSPatternLock::SetDotConnect(const JSCallbackInfo& args)
{
    if (!args[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onDotConnect = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                            int32_t code) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        PipelineContext::SetCallBackNode(node);
        JSRef<JSVal> newJSVal = JSRef<JSVal>::Make(ToJSValue(code));
        func->ExecuteJS(1, &newJSVal);
    };

    PatternLockModel::GetInstance()->SetDotConnect(std::move(onDotConnect));
}
void JSPatternLock::SetActiveCircleColor(const JSRef<JSVal>& info)
{
    Color activeColor;
    if (!ParseJsColor(info, activeColor)) {
        activeColor = Color::TRANSPARENT;
    }
    PatternLockModel::GetInstance()->SetActiveCircleColor(activeColor);
}
void JSPatternLock::SetActiveCircleRadius(const JSRef<JSVal>& info)
{
    CalcDimension radius;
    if (!ParseLengthMetricsToPositiveDimension(info, radius) || radius.IsNonPositive()) {
        radius = Dimension(0.0f, DimensionUnit::VP);
    }
    PatternLockModel::GetInstance()->SetActiveCircleRadius(radius);
}
void JSPatternLock::SetEnableWaveEffect(const JSRef<JSVal>& info)
{
    if (!info->IsBoolean()) {
        PatternLockModel::GetInstance()->SetEnableWaveEffect(true);
        return;
    }
    PatternLockModel::GetInstance()->SetEnableWaveEffect(info->ToBoolean());
}
void JSPatternLock::SetActivateCircleStyle(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || info[0]->IsNull() || !info[0]->IsObject()) {
        PatternLockModel::GetInstance()->SetActiveCircleColor(Color::TRANSPARENT);
        PatternLockModel::GetInstance()->SetActiveCircleRadius(Dimension(0.0f, DimensionUnit::VP));
        PatternLockModel::GetInstance()->SetEnableWaveEffect(true);
        return;
    }
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> jsColor = paramObject->GetProperty("color");
    JSRef<JSVal> jsRadius = paramObject->GetProperty("radius");
    JSRef<JSVal> jsEnable = paramObject->GetProperty("enableWaveEffect");
    SetActiveCircleColor(jsColor);
    SetActiveCircleRadius(jsRadius);
    SetEnableWaveEffect(jsEnable);
}
void JSPatternLockController::JSBind(BindingTarget globalObj)
{
    JSClass<JSPatternLockController>::Declare("PatternLockController");
    JSClass<JSPatternLockController>::CustomMethod("reset", &JSPatternLockController::Reset);
    JSClass<JSPatternLockController>::CustomMethod("setChallengeResult", &JSPatternLockController::SetChallengeResult);
    JSClass<JSPatternLockController>::Bind(
        globalObj, JSPatternLockController::Constructor, JSPatternLockController::Destructor);
}
void JSPatternLockController::Reset(const JSCallbackInfo& args)
{
    if (controller_) {
        controller_->Reset();
    }
}
void JSPatternLockController::SetChallengeResult(const JSCallbackInfo& args)
{
    if (controller_) {
        if (!args[0]->IsNumber()) {
            return;
        }
        int32_t value = args[0]->ToNumber<int32_t>();
        if (value >= 1 && value <= static_cast<int32_t>(CHALLENGE_RESULT.size())) {
            controller_->SetChallengeResult(CHALLENGE_RESULT[value - 1]);
        }
    }
}
void JSPatternLockController::Constructor(const JSCallbackInfo& args)
{
    auto controller = Referenced::MakeRefPtr<JSPatternLockController>();
    controller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(controller));
}
void JSPatternLockController::Destructor(JSPatternLockController* controller)
{
    if (controller != nullptr) {
        controller->DecRefCount();
    }
}
} // namespace OHOS::Ace::Framework

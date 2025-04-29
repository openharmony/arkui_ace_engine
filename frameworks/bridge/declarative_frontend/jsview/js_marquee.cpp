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

#include "frameworks/bridge/declarative_frontend/jsview/js_marquee.h"
#include <limits>
#include <optional>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_function.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/marquee_model_impl.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/marquee/marquee_model.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<MarqueeModel> MarqueeModel::instance_ = nullptr;
std::mutex MarqueeModel::mutex_;
MarqueeModel* MarqueeModel::GetInstance()
{
#ifdef NG_BUILD
    static NG::MarqueeModelNG instance;
    return &instance;
#else
    if (Container::IsCurrentUseNewPipeline()) {
        static NG::MarqueeModelNG instance;
        return &instance;
    } else {
        static Framework::MarqueeModelImpl instance;
        return &instance;
    }
#endif
}
} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {

const std::vector<MarqueeUpdateStrategy> MARQUEE_UPDATE_STRATEGYS = { MarqueeUpdateStrategy::DEFAULT,
    MarqueeUpdateStrategy::PRESERVE_POSITION};

void JSMarquee::Create(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    MarqueeModel::GetInstance()->Create();
    auto paramObject = JSRef<JSObject>::Cast(info[0]);
    auto src = paramObject->GetProperty("src");
    std::optional<std::string> srcOpt;
    if (src->IsString()) {
        srcOpt = src->ToString();
    }
    MarqueeModel::GetInstance()->SetValue(srcOpt);

    auto getStart = paramObject->GetProperty("start");
    std::optional<bool> startOpt = getStart->IsBoolean() ? getStart->ToBoolean() : false;
    MarqueeModel::GetInstance()->SetPlayerStatus(startOpt);

    auto getStep = paramObject->GetProperty("step");
    std::optional<double> stepOpt;
    if (getStep->IsNumber()) {
        auto step = getStep->ToNumber<double>();
        if (GreatNotEqual(step, 0.0)) {
            stepOpt = Dimension(step, DimensionUnit::VP).ConvertToPx();
        }
    }
    MarqueeModel::GetInstance()->SetScrollAmount(stepOpt);

    auto getLoop = paramObject->GetProperty("loop");
    std::optional<int32_t> loopOpt;
    if (getLoop->IsNumber()) {
        auto loopDouble = getLoop->ToNumber<double>();
        int32_t loop = -1;
        if (GreatNotEqual(loopDouble, 0.0)) {
            loop = static_cast<int32_t>(loopDouble);
            if (loop == std::numeric_limits<int32_t>::max() || loop < 0) {
                loop = -1;
            }
        }
        loopOpt = loop;
    }
    MarqueeModel::GetInstance()->SetLoop(loopOpt);

    auto getFromStart = paramObject->GetProperty("fromStart");
    bool fromStart = getFromStart->IsBoolean() ? getFromStart->ToBoolean() : true;
    std::optional<MarqueeDirection> directionOpt;
    if (fromStart) {
        directionOpt = MarqueeDirection::LEFT;
    } else {
        directionOpt = MarqueeDirection::RIGHT;
    }
    MarqueeModel::GetInstance()->SetDirection(directionOpt);
}

void JSMarquee::JSBind(BindingTarget globalObj)
{
    JSClass<JSMarquee>::Declare("Marquee");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSMarquee>::StaticMethod("create", &JSMarquee::Create, opt);
    JSClass<JSMarquee>::StaticMethod("allowScale", &JSMarquee::SetAllowScale);
    JSClass<JSMarquee>::StaticMethod("fontColor", &JSMarquee::SetTextColor);
    JSClass<JSMarquee>::StaticMethod("fontSize", &JSMarquee::SetFontSize);
    JSClass<JSMarquee>::StaticMethod("fontWeight", &JSMarquee::SetFontWeight);
    JSClass<JSMarquee>::StaticMethod("fontFamily", &JSMarquee::SetFontFamily);
    JSClass<JSMarquee>::StaticMethod("marqueeUpdateStrategy", &JSMarquee::SetMarqueeUpdateStrategy);
    JSClass<JSMarquee>::StaticMethod("onStart", &JSMarquee::OnStart);
    JSClass<JSMarquee>::StaticMethod("onBounce", &JSMarquee::OnBounce);
    JSClass<JSMarquee>::StaticMethod("onFinish", &JSMarquee::OnFinish);
    JSClass<JSMarquee>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSMarquee>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSMarquee>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSMarquee>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSMarquee>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSMarquee>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSMarquee>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSMarquee>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSMarquee>::InheritAndBind<JSViewAbstract>(globalObj);
}

void JSMarquee::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::optional<Color> colorOpt;
    Color color;
    if (ParseJsColor(info[0], color)) {
        colorOpt = color;
    }
    MarqueeModel::GetInstance()->SetTextColor(colorOpt);
}

void JSMarquee::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::optional<Dimension> fontSizeOpt;
    CalcDimension fontSize;
    if (ParseJsDimensionFp(info[0], fontSize)) {
        if (!fontSize.IsNegative() && fontSize.Unit() != DimensionUnit::PERCENT) {
            fontSizeOpt = fontSize;
        }
    }
    MarqueeModel::GetInstance()->SetFontSize(fontSizeOpt);
}

void JSMarquee::SetAllowScale(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::optional<bool> allowScaleOpt;
    if (info[0]->IsBoolean()) {
        allowScaleOpt = info[0]->ToBoolean();
    }
    MarqueeModel::GetInstance()->SetAllowScale(allowScaleOpt);
}

void JSMarquee::SetFontWeight(const std::string& value)
{
    std::optional<FontWeight> fontWeightOpt = ConvertStrToFontWeight(value);
    MarqueeModel::GetInstance()->SetFontWeight(fontWeightOpt);
}

void JSMarquee::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    std::optional<std::vector<std::string>> fontFamiliesOpt;
    std::vector<std::string> fontFamilies;
    if (ParseJsFontFamilies(info[0], fontFamilies)) {
        fontFamiliesOpt = fontFamilies;
    }
    MarqueeModel::GetInstance()->SetFontFamily(fontFamiliesOpt);
}

void JSMarquee::SetMarqueeUpdateStrategy(const std::string& value)
{
    static const LinearMapNode<MarqueeUpdateStrategy> marqueeUpdateStrategyTable[] = {
        { "default", MarqueeUpdateStrategy::DEFAULT },
        { "preserve_position", MarqueeUpdateStrategy::PRESERVE_POSITION },
    };
    auto marqueeUpdateStrategyIter = BinarySearchFindIndex(marqueeUpdateStrategyTable,
        ArraySize(marqueeUpdateStrategyTable), value.c_str());
    auto marqueeUpdateStrategyValue = marqueeUpdateStrategyIter != -1 ?
        std::make_optional(MARQUEE_UPDATE_STRATEGYS[marqueeUpdateStrategyIter]) :
        std::make_optional(MarqueeUpdateStrategy::DEFAULT);
    MarqueeModel::GetInstance()->SetMarqueeUpdateStrategy(marqueeUpdateStrategyValue);
}

void JSMarquee::OnStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onStart");
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnStart(std::move(onChange));
}

void JSMarquee::OnBounce(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onBounce");
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnBounce(std::move(onChange));
}

void JSMarquee::OnFinish(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [execCtx = info.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Marquee.onFinish");
        PipelineContext::SetCallBackNode(node);
        func->ExecuteJS();
    };
    MarqueeModel::GetInstance()->SetOnFinish(std::move(onChange));
}

} // namespace OHOS::Ace::Framework

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

#include "frameworks/bridge/declarative_frontend/jsview/js_swiper.h"

#include <algorithm>
#include <cstdint>
#include <iterator>

#include "base/log/ace_scoring_log.h"
#include "base/log/event_report.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/engine_helper.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_swiper_theme.h"
#include "bridge/declarative_frontend/ark_theme/theme_apply/js_theme_utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_swiper_function.h"
#include "bridge/declarative_frontend/engine/js_converter.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "bridge/declarative_frontend/engine/jsi/js_ui_index.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/swiper_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "bridge/js_frontend/engine/jsi/js_value.h"
#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/scroll_bar.h"
#include "core/components/swiper/swiper_component.h"
#include "core/components/swiper/swiper_indicator_theme.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/scrollable/scrollable_properties.h"
#include "core/components_ng/pattern/swiper/swiper_content_transition_proxy.h"
#include "core/components_ng/pattern/swiper/swiper_model.h"
#include "core/components_ng/pattern/swiper/swiper_model_ng.h"

namespace OHOS::Ace {
namespace {
constexpr float ARROW_SIZE_COEFFICIENT = 0.75f;
constexpr int32_t DEFAULT_CUSTOM_ANIMATION_TIMEOUT = 0;
const auto DEFAULT_CURVE = AceType::MakeRefPtr<InterpolatingSpring>(-1, 1, 328, 34);
constexpr int32_t LENGTH_TWO = 2;
} // namespace
std::unique_ptr<SwiperModel> SwiperModel::instance_ = nullptr;
std::mutex SwiperModel::mutex_;

SwiperModel* SwiperModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::SwiperModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::SwiperModelNG());
            } else {
                instance_.reset(new Framework::SwiperModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace
namespace OHOS::Ace::Framework {
WeakPtr<JSIndicatorController> JSSwiper::jSIndicatorController_;
namespace {

const std::vector<EdgeEffect> EDGE_EFFECT = { EdgeEffect::SPRING, EdgeEffect::FADE, EdgeEffect::NONE };
const std::vector<SwiperDisplayMode> DISPLAY_MODE = { SwiperDisplayMode::STRETCH, SwiperDisplayMode::AUTO_LINEAR };
const std::vector<SwiperIndicatorType> INDICATOR_TYPE = { SwiperIndicatorType::DOT, SwiperIndicatorType::DIGIT };
const std::vector<SwiperAnimationMode> SWIPER_ANIMATION_MODE = { SwiperAnimationMode::NO_ANIMATION,
    SwiperAnimationMode::DEFAULT_ANIMATION, SwiperAnimationMode::FAST_ANIMATION };
const static int32_t DEFAULT_INTERVAL = 3000;
const static int32_t DEFAULT_DURATION = 400;
const static int32_t DEFAULT_DISPLAY_COUNT = 1;
const static int32_t DEFAULT_CACHED_COUNT = 1;

JSRef<JSVal> SwiperChangeEventToJSValue(const SwiperChangeEvent& eventInfo)
{
    return JSRef<JSVal>::Make(ToJSValue(eventInfo.GetIndex()));
}

struct SwiperControllerAsyncContext {
    napi_env env = nullptr;
    napi_deferred deferred = nullptr;
};

napi_value CreateErrorValue(napi_env env, int32_t errCode, const std::string& errMsg = "")
{
    napi_value code = nullptr;
    std::string codeStr = std::to_string(errCode);
    napi_create_string_utf8(env, codeStr.c_str(), codeStr.length(), &code);
    napi_value msg = nullptr;
    napi_create_string_utf8(env, errMsg.c_str(), errMsg.length(), &msg);
    napi_value error = nullptr;
    napi_create_error(env, code, msg, &error);
    return error;
}

void HandleDeferred(
    const shared_ptr<SwiperControllerAsyncContext>& asyncContext, int32_t errorCode, std::string message)
{
    auto env = asyncContext->env;
    CHECK_NULL_VOID(env);
    auto deferred = asyncContext->deferred;
    CHECK_NULL_VOID(deferred);

    napi_handle_scope scope = nullptr;
    auto status = napi_open_handle_scope(env, &scope);
    if (status != napi_ok) {
        return;
    }

    napi_value result = nullptr;
    if (errorCode == ERROR_CODE_NO_ERROR) {
        napi_get_null(env, &result);
        napi_resolve_deferred(env, deferred, result);
    } else {
        result = CreateErrorValue(env, errorCode, message);
        napi_reject_deferred(env, deferred, result);
    }
    napi_close_handle_scope(env, scope);
}

void ReturnPromise(const JSCallbackInfo& info, napi_value result)
{
    CHECK_NULL_VOID(result);
    auto jsPromise = JsConverter::ConvertNapiValueToJsVal(result);
    if (!jsPromise->IsObject()) {
        return;
    }
    info.SetReturnValue(JSRef<JSObject>::Cast(jsPromise));
}
} // namespace

void JSSwiper::Create(const JSCallbackInfo& info)
{
    auto controller = SwiperModel::GetInstance()->Create();

    if (info.Length() > 0 && info[0]->IsObject()) {
        auto* jsController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSSwiperController>();
        if (jsController) {
            jsController->SetInstanceId(Container::CurrentId());
            jsController->SetController(controller);
        }
    }

    JSSwiperTheme::ApplyThemeInConstructor();
}

void JSSwiper::JsRemoteMessage(const JSCallbackInfo& info)
{
    RemoteCallback remoteCallback;
    JSInteractableView::JsRemoteMessage(info, remoteCallback);

    SwiperModel::GetInstance()->SetRemoteMessageEventId(std::move(remoteCallback));
}

void JSSwiper::JSBind(BindingTarget globalObj)
{
    JsSwiperContentTransitionProxy::JSBind(globalObj);
    JSClass<JSSwiper>::Declare("Swiper");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSSwiper>::StaticMethod("create", &JSSwiper::Create, opt);
    JSClass<JSSwiper>::StaticMethod("indicatorInteractive", &JSSwiper::SetIndicatorInteractive, opt);
    JSClass<JSSwiper>::StaticMethod("autoPlay", &JSSwiper::SetAutoPlay, opt);
    JSClass<JSSwiper>::StaticMethod("duration", &JSSwiper::SetDuration, opt);
    JSClass<JSSwiper>::StaticMethod("index", &JSSwiper::SetIndex, opt);
    JSClass<JSSwiper>::StaticMethod("interval", &JSSwiper::SetInterval, opt);
    JSClass<JSSwiper>::StaticMethod("loop", &JSSwiper::SetLoop, opt);
    JSClass<JSSwiper>::StaticMethod("vertical", &JSSwiper::SetVertical, opt);
    JSClass<JSSwiper>::StaticMethod("indicator", &JSSwiper::SetIndicator, opt);
    JSClass<JSSwiper>::StaticMethod("displayMode", &JSSwiper::SetDisplayMode);
    JSClass<JSSwiper>::StaticMethod("effectMode", &JSSwiper::SetEffectMode);
    JSClass<JSSwiper>::StaticMethod("displayCount", &JSSwiper::SetDisplayCount);
    JSClass<JSSwiper>::StaticMethod("itemSpace", &JSSwiper::SetItemSpace);
    JSClass<JSSwiper>::StaticMethod("prevMargin", &JSSwiper::SetPreviousMargin);
    JSClass<JSSwiper>::StaticMethod("nextMargin", &JSSwiper::SetNextMargin);
    JSClass<JSSwiper>::StaticMethod("cachedCount", &JSSwiper::SetCachedCount);
    JSClass<JSSwiper>::StaticMethod("curve", &JSSwiper::SetCurve);
    JSClass<JSSwiper>::StaticMethod("onChange", &JSSwiper::SetOnChange);
    JSClass<JSSwiper>::StaticMethod("onUnselected", &JSSwiper::SetOnUnselected);
    JSClass<JSSwiper>::StaticMethod("onAnimationStart", &JSSwiper::SetOnAnimationStart);
    JSClass<JSSwiper>::StaticMethod("onAnimationEnd", &JSSwiper::SetOnAnimationEnd);
    JSClass<JSSwiper>::StaticMethod("onGestureSwipe", &JSSwiper::SetOnGestureSwipe);
    JSClass<JSSwiper>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSSwiper>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSSwiper>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSSwiper>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSSwiper>::StaticMethod("remoteMessage", &JSSwiper::JsRemoteMessage);
    JSClass<JSSwiper>::StaticMethod("onClick", &JSSwiper::SetOnClick);
    JSClass<JSSwiper>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSSwiper>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSSwiper>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSSwiper>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSSwiper>::StaticMethod("indicatorStyle", &JSSwiper::SetIndicatorStyle);
    JSClass<JSSwiper>::StaticMethod("enabled", &JSSwiper::SetEnabled);
    JSClass<JSSwiper>::StaticMethod("disableSwipe", &JSSwiper::SetDisableSwipe);
    JSClass<JSSwiper>::StaticMethod("height", &JSSwiper::SetHeight);
    JSClass<JSSwiper>::StaticMethod("width", &JSSwiper::SetWidth);
    JSClass<JSSwiper>::StaticMethod("size", &JSSwiper::SetSize);
    JSClass<JSSwiper>::StaticMethod("displayArrow", &JSSwiper::SetDisplayArrow);
    JSClass<JSSwiper>::StaticMethod("nestedScroll", &JSSwiper::SetNestedScroll);
    JSClass<JSSwiper>::StaticMethod("customContentTransition", &JSSwiper::SetCustomContentTransition);
    JSClass<JSSwiper>::StaticMethod("onContentDidScroll", &JSSwiper::SetOnContentDidScroll);
    JSClass<JSSwiper>::StaticMethod("pageFlipMode", &JSSwiper::SetPageFlipMode);
    JSClass<JSSwiper>::StaticMethod("onContentWillScroll", &JSSwiper::SetOnContentWillScroll);
    JSClass<JSSwiper>::StaticMethod("onSelected", &JSSwiper::SetOnSelected);
    JSClass<JSSwiper>::InheritAndBind<JSContainerBase>(globalObj);
}

void JSSwiper::SetIndicatorInteractive(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsBoolean()) {
        SwiperModel::GetInstance()->SetIndicatorInteractive(info[0]->ToBoolean());
    } else {
        SwiperModel::GetInstance()->SetIndicatorInteractive(true);
    }
}

void JSSwiper::SetAutoPlay(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    bool autoPlay = false;
    if (info[0]->IsBoolean()) {
        autoPlay = info[0]->ToBoolean();
    }
    SwiperModel::GetInstance()->SetAutoPlay(autoPlay);
    SwiperAutoPlayOptions swiperAutoPlayOptions;
    if (info.Length() > 1 && info[1]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[1]);
        GetAutoPlayOptionsInfo(obj, swiperAutoPlayOptions);
    }

    SwiperModel::GetInstance()->SetAutoPlayOptions(swiperAutoPlayOptions);
}

void JSSwiper::SetEnabled(const JSCallbackInfo& info)
{
    JSViewAbstract::JsEnabled(info);
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsBoolean()) {
        return;
    }

    SwiperModel::GetInstance()->SetEnabled(info[0]->ToBoolean());
}

void JSSwiper::SetDisableSwipe(bool disableSwipe)
{
    SwiperModel::GetInstance()->SetDisableSwipe(disableSwipe);
}

void JSSwiper::SetEffectMode(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsNumber()) {
        return;
    }

    auto edgeEffect = info[0]->ToNumber<int32_t>();
    if (edgeEffect < 0 || edgeEffect >= static_cast<int32_t>(EDGE_EFFECT.size())) {
        return;
    }

    SwiperModel::GetInstance()->SetEdgeEffect(EDGE_EFFECT[edgeEffect]);
}

void JSSwiper::SetDisplayCount(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info.Length() == 2) {
        if (info[1]->IsBoolean()) {
            SwiperModel::GetInstance()->SetSwipeByGroup(info[1]->ToBoolean());
        } else {
            SwiperModel::GetInstance()->SetSwipeByGroup(false);
        }
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (info[0]->IsString() && info[0]->ToString() == "auto") {
            SwiperModel::GetInstance()->SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
            SwiperModel::GetInstance()->ResetDisplayCount();
        } else if (info[0]->IsNumber() && info[0]->ToNumber<int32_t>() > 0) {
            SwiperModel::GetInstance()->SetDisplayCount(info[0]->ToNumber<int32_t>());
        } else if (info[0]->IsObject()) {
            JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(info[0]);
            auto minSizeParam = jsObj->GetProperty("minSize");
            if (minSizeParam->IsNull()) {
                return;
            }
            CalcDimension minSizeValue;
            if (!ParseJsDimensionVp(minSizeParam, minSizeValue)) {
                SwiperModel::GetInstance()->SetMinSize(0.0_vp);
                return;
            }
            SwiperModel::GetInstance()->SetMinSize(minSizeValue);
        } else {
            SwiperModel::GetInstance()->SetDisplayCount(DEFAULT_DISPLAY_COUNT);
        }

        return;
    }

    if (info[0]->IsString() && info[0]->ToString() == "auto") {
        SwiperModel::GetInstance()->SetDisplayMode(SwiperDisplayMode::AUTO_LINEAR);
        SwiperModel::GetInstance()->ResetDisplayCount();
    } else if (info[0]->IsNumber()) {
        SwiperModel::GetInstance()->SetDisplayCount(info[0]->ToNumber<int32_t>());
    }
}

void JSSwiper::SetDuration(const JSCallbackInfo& info)
{
    int32_t duration = DEFAULT_DURATION;

    if (info.Length() < 1) { // user do not set any value
        return;
    }

    // undefined value turn to default 400
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        duration = info[0]->ToNumber<int32_t>();
        if (duration < 0) {
            duration = DEFAULT_DURATION;
        }
    }

    SwiperModel::GetInstance()->SetDuration(duration);
}

void ParseSwiperIndexObject(const JSCallbackInfo& args, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(changeEventVal->IsFunction());

    auto jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(changeEventVal));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onIndex = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode](
                       const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Swiper.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            return;
        }
        auto newJSVal = JSRef<JSVal>::Make(ToJSValue(swiperInfo->GetIndex()));
        func->ExecuteJS(1, &newJSVal);
    };
    SwiperModel::GetInstance()->SetOnChangeEvent(std::move(onIndex));
}

void JSSwiper::SetIndex(const JSCallbackInfo& info)
{
    auto length = info.Length();
    if (length < 1 || length > 2) {
        return;
    }
    int32_t index = 0;
    auto jsIndex = info[0];
    if (jsIndex->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsIndex);
        jsIndex = obj->GetProperty("value");
        auto changeEventVal = obj->GetProperty("$value");
        ParseSwiperIndexObject(info, changeEventVal);
    }

    if (length > 0 && jsIndex->IsNumber()) {
        index = jsIndex->ToNumber<int32_t>();
    }

    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        index = index < 0 ? 0 : index;
    }

    if (index < 0) {
        return;
    }
    SwiperModel::GetInstance()->SetIndex(index);

    if (length > 1 && info[1]->IsFunction()) {
        ParseSwiperIndexObject(info, info[1]);
    }
}

void JSSwiper::SetInterval(const JSCallbackInfo& info)
{
    int32_t interval = DEFAULT_INTERVAL;

    if (info.Length() < 1) { // user do not set any value
        return;
    }

    // undefined value turn to default 3000
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        interval = info[0]->ToNumber<int32_t>();
        if (interval < 0) {
            interval = DEFAULT_INTERVAL;
        }
    }

    SwiperModel::GetInstance()->SetAutoPlayInterval(interval);
}

void JSSwiper::SetLoop(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (Container::LessThanAPIVersion(PlatformVersion::VERSION_TEN)) {
        SwiperModel::GetInstance()->SetLoop(info[0]->ToBoolean());
        return;
    }

    if (info[0]->IsBoolean()) {
        SwiperModel::GetInstance()->SetLoop(info[0]->ToBoolean());
    } else {
        SwiperModel::GetInstance()->SetLoop(true);
    }
}

void JSSwiper::SetVertical(bool isVertical)
{
    SwiperModel::GetInstance()->SetDirection(isVertical ? Axis::VERTICAL : Axis::HORIZONTAL);
}

void JSSwiper::GetFontContent(const JSRef<JSVal>& font, bool isSelected, SwiperDigitalParameters& digitalParameters)
{
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(font);
    JSRef<JSVal> size = obj->GetProperty("size");
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_VOID(swiperIndicatorTheme);
    // set font size, unit FP
    CalcDimension fontSize;
    if (!size->IsUndefined() && !size->IsNull() && ParseJsDimensionFp(size, fontSize)) {
        if (LessOrEqual(fontSize.Value(), 0.0) || LessOrEqual(size->ToNumber<double>(), 0.0) ||
            fontSize.Unit() == DimensionUnit::PERCENT) {
            fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
        }
    } else {
        fontSize = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontSize();
    }
    if (isSelected) {
        digitalParameters.selectedFontSize = fontSize;
    } else {
        digitalParameters.fontSize = fontSize;
    }
    JSRef<JSVal> weight = obj->GetProperty("weight");
    if (!weight->IsNull()) {
        std::string weightValue;
        if (weight->IsNumber()) {
            weightValue = std::to_string(weight->ToNumber<int32_t>());
        } else {
            ParseJsString(weight, weightValue);
        }
        if (isSelected) {
            digitalParameters.selectedFontWeight = ConvertStrToFontWeight(weightValue);
        } else {
            digitalParameters.fontWeight = ConvertStrToFontWeight(weightValue);
        }
    } else {
        if (isSelected) {
            digitalParameters.selectedFontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        } else {
            digitalParameters.fontWeight = swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetFontWeight();
        }
    }
}

void JSSwiper::SetIsIndicatorCustomSize(const Dimension& dimPosition, bool parseOk)
{
    if (parseOk && dimPosition > 0.0_vp) {
        SwiperModel::GetInstance()->SetIsIndicatorCustomSize(true);
    } else {
        SwiperModel::GetInstance()->SetIsIndicatorCustomSize(false);
    }
}

std::optional<Dimension> JSSwiper::ParseIndicatorDimension(const JSRef<JSVal>& value)
{
    std::optional<Dimension> indicatorDimension;
    if (value->IsUndefined()) {
        return indicatorDimension;
    }
    CalcDimension dimPosition;
    auto parseOk = ParseJsDimensionVp(value, dimPosition);
    indicatorDimension = parseOk && dimPosition.ConvertToPx() >= 0.0f ? dimPosition : 0.0_vp;
    return indicatorDimension;
}

std::optional<Dimension> JSSwiper::ParseIndicatorBottom(const JSRef<JSVal>& bottomValue, bool hasIgnoreSize)
{
    std::optional<Dimension> bottom;
    if (bottomValue->IsUndefined()) {
        return bottom;
    }
    if (!hasIgnoreSize) {
        bottom = ParseIndicatorDimension(bottomValue);
        return bottom;
    } else {
        CalcDimension dimBottom;
        bool parseOk = ParseLengthMetricsToDimension(bottomValue, dimBottom);
        dimBottom = parseOk && dimBottom.ConvertToPx() >= 0.0f ? dimBottom : 0.0_vp;
        return dimBottom;
    }
}

SwiperParameters JSSwiper::GetDotIndicatorInfo(const JSRef<JSObject>& obj)
{
    JSRef<JSVal> leftValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::LEFT_VALUE));
    JSRef<JSVal> topValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::TOP_VALUE));
    JSRef<JSVal> rightValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::RIGHT_VALUE));
    JSRef<JSVal> bottomValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::BOTTOM_VALUE));
    JSRef<JSVal> startValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::START_VALUE));
    JSRef<JSVal> endValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::END_VALUE));
    JSRef<JSVal> itemWidthValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::ITEM_WIDTH_VALUE));
    JSRef<JSVal> itemHeightValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::ITEM_HEIGHT_VALUE));
    JSRef<JSVal> selectedItemWidthValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_ITEM_WIDTH_VALUE));
    JSRef<JSVal> selectedItemHeightValue =
        obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_ITEM_HEIGHT_VALUE));
    JSRef<JSVal> spaceValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SPACE_VALUE));
    JSRef<JSVal> ignoreSizeValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::IGNORE_SIZE_VALUE));
    JSRef<JSVal> setIgnoreSizeValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SET_IGNORE_SIZE_VALUE));
    
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperParameters());
    SwiperParameters swiperParameters;
    swiperParameters.dimLeft = ParseIndicatorDimension(leftValue);
    swiperParameters.dimTop = ParseIndicatorDimension(topValue);
    swiperParameters.dimRight = ParseIndicatorDimension(rightValue);
    auto hasIgnoreSizeValue = false;
    
    if (setIgnoreSizeValue->IsBoolean()) {
        hasIgnoreSizeValue = setIgnoreSizeValue->ToBoolean();
        swiperParameters.setIgnoreSizeValue = hasIgnoreSizeValue;
    }

    if (ignoreSizeValue->IsBoolean()) {
        auto ignoreSize = ignoreSizeValue->ToBoolean();
        swiperParameters.ignoreSizeValue = ignoreSize;
    }
    swiperParameters.dimBottom = ParseIndicatorBottom(bottomValue, hasIgnoreSizeValue);
    CalcDimension dimStart;
    CalcDimension dimEnd;
    CalcDimension dimSpace;

    std::optional<Dimension> indicatorDimension;
    swiperParameters.dimStart =  ParseLengthMetricsToDimension(startValue, dimStart) ? dimStart : indicatorDimension;
    swiperParameters.dimEnd =  ParseLengthMetricsToDimension(endValue, dimEnd) ? dimEnd : indicatorDimension;
 
    auto parseSpaceOk = ParseLengthMetricsToDimension(spaceValue, dimSpace) &&
        (dimSpace.Unit() !=  DimensionUnit::PERCENT) ;
    auto defalutSpace = swiperIndicatorTheme->GetIndicatorDotItemSpace();
    swiperParameters.dimSpace =  (parseSpaceOk && !(dimSpace < 0.0_vp)) ? dimSpace : defalutSpace;
    bool ignoreSize = ignoreSizeValue->IsBoolean() ? ignoreSizeValue->ToBoolean() : false;
    swiperParameters.ignoreSizeValue = ignoreSize;

    CalcDimension dimPosition;
    bool parseItemWOk =
        ParseJsDimensionVp(itemWidthValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    auto defaultSize = swiperIndicatorTheme->GetSize();
    swiperParameters.itemWidth = parseItemWOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseItemHOk =
        ParseJsDimensionVp(itemHeightValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.itemHeight = parseItemHOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseSelectedItemWOk =
        ParseJsDimensionVp(selectedItemWidthValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.selectedItemWidth = parseSelectedItemWOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    bool parseSelectedItemHOk =
        ParseJsDimensionVp(selectedItemHeightValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
    swiperParameters.selectedItemHeight = parseSelectedItemHOk && dimPosition > 0.0_vp ? dimPosition : defaultSize;
    SwiperModel::GetInstance()->SetIsIndicatorCustomSize(
        parseSelectedItemWOk || parseSelectedItemHOk || parseItemWOk || parseItemHOk);
    SetDotIndicatorInfo(obj, swiperParameters, swiperIndicatorTheme);
    return swiperParameters;
}
void JSSwiper::SetDotIndicatorInfo(const JSRef<JSObject>& obj, SwiperParameters& swiperParameters,
    const RefPtr<SwiperIndicatorTheme>& swiperIndicatorTheme)
{
    JSRef<JSVal> maskValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::MASK_VALUE));
    JSRef<JSVal> colorValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::COLOR_VALUE));
    JSRef<JSVal> selectedColorValue = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::SELECTED_COLOR_VALUE));
    JSRef<JSVal> maxDisplayCountVal = obj->GetProperty(static_cast<int32_t>(ArkUIIndex::MAX_DISPLAY_COUNT_VALUE));
    if (maskValue->IsBoolean()) {
        auto mask = maskValue->ToBoolean();
        swiperParameters.maskValue = mask;
    }
    Color colorVal;
    auto parseOk = ParseJsColor(colorValue, colorVal);
    swiperParameters.colorVal = parseOk ? colorVal : swiperIndicatorTheme->GetColor();
    parseOk = ParseJsColor(selectedColorValue, colorVal);
    swiperParameters.selectedColorVal = parseOk ? colorVal : swiperIndicatorTheme->GetSelectedColor();
    if (maxDisplayCountVal->IsUndefined()) {
        return;
    }
    uint32_t result = 0;
    auto setMaxDisplayCountVal = ParseJsInteger(maxDisplayCountVal, result);
    swiperParameters.maxDisplayCountVal = setMaxDisplayCountVal && result > 0 ? result : 0;
}
bool JSSwiper::ParseLengthMetricsToDimension(const JSRef<JSVal>& jsValue, CalcDimension& result)
{
    if (jsValue->IsNumber()) {
        result = CalcDimension(jsValue->ToNumber<double>(), DimensionUnit::VP);
        return true;
    }
    if (jsValue->IsString()) {
        auto value = jsValue->ToString();
        StringUtils::StringToCalcDimensionNG(value, result, false, DimensionUnit::VP);
        return true;
    }
    if (jsValue->IsObject()) {
        JSRef<JSObject> jsObj = JSRef<JSObject>::Cast(jsValue);
        double value = jsObj->GetProperty("value")->ToNumber<double>();
        auto unit = static_cast<DimensionUnit>(jsObj->GetProperty("unit")->ToNumber<int32_t>());
        result = CalcDimension(value, unit);
        return true;
    }
    if (jsValue->IsNull()) {
        result = CalcDimension(0.0f, DimensionUnit::VP);
        return true;
    }

    return false;
}

SwiperDigitalParameters JSSwiper::GetDigitIndicatorInfo(const JSRef<JSObject>& obj)
{
    JSRef<JSVal> dotLeftValue = obj->GetProperty("leftValue");
    JSRef<JSVal> dotTopValue = obj->GetProperty("topValue");
    JSRef<JSVal> dotRightValue = obj->GetProperty("rightValue");
    JSRef<JSVal> dotBottomValue = obj->GetProperty("bottomValue");
    JSRef<JSVal> startValue = obj->GetProperty("startValue");
    JSRef<JSVal> endValue = obj->GetProperty("endValue");
    JSRef<JSVal> fontColorValue = obj->GetProperty("fontColorValue");
    JSRef<JSVal> selectedFontColorValue = obj->GetProperty("selectedFontColorValue");
    JSRef<JSVal> digitFontValue = obj->GetProperty("digitFontValue");
    JSRef<JSVal> selectedDigitFontValue = obj->GetProperty("selectedDigitFontValue");
    JSRef<JSVal> ignoreSizeValue = obj->GetProperty("ignoreSizeValue");
    JSRef<JSVal> setIgnoreSizeValue = obj->GetProperty("setIgnoreSizeValue");
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, SwiperDigitalParameters());
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, SwiperDigitalParameters());
    SwiperDigitalParameters digitalParameters;
    digitalParameters.dimLeft = ParseIndicatorDimension(dotLeftValue);
    digitalParameters.dimTop = ParseIndicatorDimension(dotTopValue);
    digitalParameters.dimRight = ParseIndicatorDimension(dotRightValue);

    bool hasIgnoreSizeValue = setIgnoreSizeValue->IsBoolean() ? setIgnoreSizeValue->ToBoolean() : false;
    digitalParameters.dimBottom = ParseIndicatorBottom(dotBottomValue, hasIgnoreSizeValue);
    std::optional<Dimension> indicatorDimension;
    CalcDimension dimStart;
    CalcDimension dimEnd;
    digitalParameters.dimStart =  ParseLengthMetricsToDimension(startValue, dimStart) ? dimStart : indicatorDimension;
    digitalParameters.dimEnd =  ParseLengthMetricsToDimension(endValue, dimEnd) ? dimEnd : indicatorDimension;
    
    if (ignoreSizeValue->IsBoolean()) {
        auto ignoreSize = ignoreSizeValue->ToBoolean();
        digitalParameters.ignoreSizeValue = ignoreSize;
    }

    Color fontColor;
    auto parseOk = JSViewAbstract::ParseJsColor(fontColorValue, fontColor);
    digitalParameters.fontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    parseOk = JSViewAbstract::ParseJsColor(selectedFontColorValue, fontColor);
    digitalParameters.selectedFontColor =
        parseOk ? fontColor : swiperIndicatorTheme->GetDigitalIndicatorTextStyle().GetTextColor();
    if (!digitFontValue->IsNull() && digitFontValue->IsObject()) {
        GetFontContent(digitFontValue, false, digitalParameters);
    }
    if (!selectedDigitFontValue->IsNull() && selectedDigitFontValue->IsObject()) {
        GetFontContent(selectedDigitFontValue, true, digitalParameters);
    }
    return digitalParameters;
}

bool JSSwiper::GetArrowInfo(const JSRef<JSObject>& obj, SwiperArrowParameters& swiperArrowParameters)
{
    auto isShowBackgroundValue = obj->GetProperty("showBackground");
    auto isSidebarMiddleValue = obj->GetProperty("isSidebarMiddle");
    auto backgroundSizeValue = obj->GetProperty("backgroundSize");
    auto backgroundColorValue = obj->GetProperty("backgroundColor");
    auto arrowSizeValue = obj->GetProperty("arrowSize");
    auto arrowColorValue = obj->GetProperty("arrowColor");
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_RETURN(pipelineContext, false);
    auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
    CHECK_NULL_RETURN(swiperIndicatorTheme, false);
    swiperArrowParameters.isShowBackground = isShowBackgroundValue->IsBoolean()
                                                 ? isShowBackgroundValue->ToBoolean()
                                                 : swiperIndicatorTheme->GetIsShowArrowBackground();
    swiperArrowParameters.isSidebarMiddle = isSidebarMiddleValue->IsBoolean()
                                                ? isSidebarMiddleValue->ToBoolean()
                                                : swiperIndicatorTheme->GetIsSidebarMiddle();
    bool parseOk = false;
    CalcDimension dimension;
    Color color;
    if (swiperArrowParameters.isSidebarMiddle.value()) {
        parseOk = ParseJsDimensionVp(backgroundSizeValue, dimension);
        swiperArrowParameters.backgroundSize =
            parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension
                : swiperIndicatorTheme->GetBigArrowBackgroundSize();
        parseOk = ParseJsColor(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk ? color : swiperIndicatorTheme->GetBigArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = ParseJsDimensionVpNG(arrowSizeValue, dimension);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetBigArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = ParseJsColor(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk ? color : swiperIndicatorTheme->GetBigArrowColor();
    } else {
        parseOk = ParseJsDimensionVp(backgroundSizeValue, dimension);
        swiperArrowParameters.backgroundSize =
            parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                ? dimension
                : swiperIndicatorTheme->GetSmallArrowBackgroundSize();
        parseOk = ParseJsColor(backgroundColorValue, color);
        swiperArrowParameters.backgroundColor = parseOk ? color : swiperIndicatorTheme->GetSmallArrowBackgroundColor();
        if (swiperArrowParameters.isShowBackground.value()) {
            swiperArrowParameters.arrowSize = swiperArrowParameters.backgroundSize.value() * ARROW_SIZE_COEFFICIENT;
        } else {
            parseOk = ParseJsDimensionVpNG(arrowSizeValue, dimension);
            swiperArrowParameters.arrowSize =
                parseOk && GreatNotEqual(dimension.ConvertToVp(), 0.0) && !(dimension.Unit() == DimensionUnit::PERCENT)
                    ? dimension
                    : swiperIndicatorTheme->GetSmallArrowSize();
            swiperArrowParameters.backgroundSize = swiperArrowParameters.arrowSize;
        }
        parseOk = ParseJsColor(arrowColorValue, color);
        swiperArrowParameters.arrowColor = parseOk ? color : swiperIndicatorTheme->GetSmallArrowColor();
    }
    return true;
}

void JSSwiper::SetDisplayArrow(const JSCallbackInfo& info)
{
    if (info[0]->IsEmpty() || info[0]->IsUndefined()) {
        SwiperModel::GetInstance()->SetDisplayArrow(false);
        return;
    }
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        SwiperArrowParameters swiperArrowParameters;
        if (!GetArrowInfo(obj, swiperArrowParameters)) {
            SwiperModel::GetInstance()->SetDisplayArrow(false);
            return;
        }
        JSSwiperTheme::ApplyThemeToDisplayArrow(swiperArrowParameters, obj);
        SwiperModel::GetInstance()->SetArrowStyle(swiperArrowParameters);
        SwiperModel::GetInstance()->SetDisplayArrow(true);
    } else if (info[0]->IsBoolean()) {
        if (info[0]->ToBoolean()) {
            auto pipelineContext = PipelineBase::GetCurrentContext();
            CHECK_NULL_VOID(pipelineContext);
            auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
            CHECK_NULL_VOID(swiperIndicatorTheme);
            SwiperArrowParameters swiperArrowParameters;
            swiperArrowParameters.isShowBackground = swiperIndicatorTheme->GetIsShowArrowBackground();
            swiperArrowParameters.isSidebarMiddle = swiperIndicatorTheme->GetIsSidebarMiddle();
            swiperArrowParameters.backgroundSize = swiperIndicatorTheme->GetSmallArrowBackgroundSize();
            swiperArrowParameters.backgroundColor = swiperIndicatorTheme->GetSmallArrowBackgroundColor();
            swiperArrowParameters.arrowSize = swiperIndicatorTheme->GetSmallArrowSize();
            swiperArrowParameters.arrowColor = swiperIndicatorTheme->GetSmallArrowColor();
            JSSwiperTheme::ApplyThemeToDisplayArrowForce(swiperArrowParameters);
            SwiperModel::GetInstance()->SetArrowStyle(swiperArrowParameters);
            SwiperModel::GetInstance()->SetDisplayArrow(true);
        } else {
            SwiperModel::GetInstance()->SetDisplayArrow(false);
            return;
        }
    } else {
        SwiperModel::GetInstance()->SetDisplayArrow(false);
        return;
    }
    if (info.Length() > 1 && info[1]->IsBoolean()) {
        SwiperModel::GetInstance()->SetHoverShow(info[1]->ToBoolean());
    } else {
        SwiperModel::GetInstance()->SetHoverShow(false);
    }
}

void JSSwiper::SetIndicatorController(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    auto* jsIndicatorController = JSRef<JSObject>::Cast(info[0])->Unwrap<JSIndicatorController>();
    if (!jsIndicatorController) {
        return;
    }
    jSIndicatorController_ = jsIndicatorController;
    SwiperModel::GetInstance()->SetBindIndicator(true);
    WeakPtr<NG::UINode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    jsIndicatorController->SetSwiperNode(targetNode);
}

void JSSwiper::ResetSwiperNode()
{
    if (jSIndicatorController_.Upgrade()) {
        jSIndicatorController_.Upgrade()->ResetSwiperNode();
    }
}

void JSSwiper::SetIndicator(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsEmpty()) {
        SwiperModel::GetInstance()->SetShowIndicator(true);
        return;
    }
    SwiperModel::GetInstance()->SetBindIndicator(false);
    if (info[0]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(info[0]);
        SwiperModel::GetInstance()->SetIndicatorIsBoolean(false);
        ResetSwiperNode();

        JSRef<JSVal> typeParam = obj->GetProperty("type");
        if (typeParam->IsString()) {
            auto type = typeParam->ToString();
            if (type == "DigitIndicator") {
                SwiperDigitalParameters digitalParameters = GetDigitIndicatorInfo(obj);
                JSSwiperTheme::ApplyThemeToDigitIndicator(digitalParameters, obj);
                SwiperModel::GetInstance()->SetDigitIndicatorStyle(digitalParameters);
                SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DIGIT);
            } else {
                SwiperParameters swiperParameters = GetDotIndicatorInfo(obj);
                JSSwiperTheme::ApplyThemeToDotIndicator(swiperParameters, obj);
                SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
                SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
            }
        } else if (typeParam->IsUndefined()) {
            SetIndicatorController(info);
        } else {
            SwiperParameters swiperParameters = GetDotIndicatorInfo(obj);
            JSSwiperTheme::ApplyThemeToDotIndicatorForce(swiperParameters);
            SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
            SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
        }
    } else {
        SwiperParameters swiperParameters = GetDotIndicatorInfo(JSRef<JSObject>::New());
        JSSwiperTheme::ApplyThemeToDotIndicatorForce(swiperParameters);
        SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
        SwiperModel::GetInstance()->SetIndicatorType(SwiperIndicatorType::DOT);
    }
    if (info[0]->IsBoolean()) {
        bool showIndicator = false;
        ParseJsBool(info[0], showIndicator);
        SwiperModel::GetInstance()->SetShowIndicator(showIndicator);
    } else {
        SwiperModel::GetInstance()->SetShowIndicator(true);
    }
}

void JSSwiper::SetIndicatorStyle(const JSCallbackInfo& info)
{
    SwiperParameters swiperParameters;
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> leftValue = obj->GetProperty("left");
        JSRef<JSVal> topValue = obj->GetProperty("top");
        JSRef<JSVal> rightValue = obj->GetProperty("right");
        JSRef<JSVal> bottomValue = obj->GetProperty("bottom");
        JSRef<JSVal> sizeValue = obj->GetProperty("size");
        JSRef<JSVal> maskValue = obj->GetProperty("mask");
        JSRef<JSVal> colorValue = obj->GetProperty("color");
        JSRef<JSVal> selectedColorValue = obj->GetProperty("selectedColor");
        JSRef<JSVal> ignoreSizeValue = obj->GetProperty("ignoreSize");
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto swiperIndicatorTheme = pipelineContext->GetTheme<SwiperIndicatorTheme>();
        CHECK_NULL_VOID(swiperIndicatorTheme);
        swiperParameters.dimLeft = ParseIndicatorDimension(leftValue);
        swiperParameters.dimTop = ParseIndicatorDimension(topValue);
        swiperParameters.dimRight = ParseIndicatorDimension(rightValue);
        swiperParameters.dimBottom = ParseIndicatorDimension(bottomValue);
        CalcDimension dimPosition;
        auto parseOk = ParseJsDimensionVp(sizeValue, dimPosition) && (dimPosition.Unit() != DimensionUnit::PERCENT);
        SetIsIndicatorCustomSize(dimPosition, parseOk);
        swiperParameters.itemWidth = parseOk && dimPosition > 0.0_vp ? dimPosition : swiperIndicatorTheme->GetSize();
        swiperParameters.itemHeight = parseOk && dimPosition > 0.0_vp ? dimPosition : swiperIndicatorTheme->GetSize();
        swiperParameters.selectedItemWidth =
            parseOk && dimPosition > 0.0_vp ? dimPosition : swiperIndicatorTheme->GetSize();
        swiperParameters.selectedItemHeight =
            parseOk && dimPosition > 0.0_vp ? dimPosition : swiperIndicatorTheme->GetSize();
        if (maskValue->IsBoolean()) {
            auto mask = maskValue->ToBoolean();
            swiperParameters.maskValue = mask;
        }
        if (ignoreSizeValue->IsBoolean()) {
            auto ignoreSize = ignoreSizeValue->ToBoolean();
            swiperParameters.ignoreSizeValue = ignoreSize;
        } else {
            swiperParameters.ignoreSizeValue = false;
        }
        Color colorVal;
        parseOk = ParseJsColor(colorValue, colorVal);
        swiperParameters.colorVal = parseOk ? colorVal : swiperIndicatorTheme->GetColor();
        parseOk = ParseJsColor(selectedColorValue, colorVal);
        swiperParameters.selectedColorVal = parseOk ? colorVal : swiperIndicatorTheme->GetSelectedColor();
    }
    SwiperModel::GetInstance()->SetDotIndicatorStyle(swiperParameters);
    info.ReturnSelf();
}

void JSSwiper::SetItemSpace(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension value;
    if (!ParseJsDimensionVp(info[0], value) || LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }

    SwiperModel::GetInstance()->SetItemSpace(value);
}

void JSSwiper::SetPreviousMargin(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension value;
    bool ignoreBlank = false;
    if (!ParseJsDimensionVp(info[0], value) || info[0]->IsNull() || info[0]->IsUndefined() ||
        LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    if (info.Length() > 1 && info[1]->IsBoolean()) {
        ignoreBlank = info[1]->ToBoolean();
    }
    SwiperModel::GetInstance()->SetPreviousMargin(value, ignoreBlank);
}

void JSSwiper::SetNextMargin(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    CalcDimension value;
    bool ignoreBlank = false;
    if (!ParseJsDimensionVp(info[0], value) || info[0]->IsNull() || info[0]->IsUndefined() ||
        LessNotEqual(value.Value(), 0.0)) {
        value.SetValue(0.0);
    }
    if (info.Length() > 1 && info[1]->IsBoolean()) {
        ignoreBlank = info[1]->ToBoolean();
    }
    SwiperModel::GetInstance()->SetNextMargin(value, ignoreBlank);
}

void JSSwiper::SetDisplayMode(int32_t index)
{
    if (index < 0 || index >= static_cast<int32_t>(DISPLAY_MODE.size())) {
        return;
    }

    SwiperModel::GetInstance()->SetDisplayMode(DISPLAY_MODE[index]);
}

void JSSwiper::SetCachedCount(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    int32_t cachedCount = DEFAULT_CACHED_COUNT;
    if (!info[0]->IsUndefined() && info[0]->IsNumber()) {
        cachedCount = info[0]->ToNumber<int32_t>();
        if (cachedCount < 0) {
            cachedCount = DEFAULT_CACHED_COUNT;
        }
    }
    SwiperModel::GetInstance()->SetCachedCount(cachedCount);

    auto isShown = info.Length() > 1 && info[1]->IsBoolean() && info[1]->ToBoolean();
    SwiperModel::GetInstance()->SetCachedIsShown(isShown);
}

void JSSwiper::SetCurve(const JSCallbackInfo& info)
{
    RefPtr<Curve> curve = DEFAULT_CURVE;
    if (info[0]->IsString()) {
        curve = CreateCurve(info[0]->ToString(), false);
        if (!curve) {
            curve = DEFAULT_CURVE;
        }
    } else if (info[0]->IsObject()) {
        auto object = JSRef<JSObject>::Cast(info[0]);
        std::function<float(float)> customCallBack = nullptr;
        JSRef<JSVal> onCallBack = object->GetProperty("__curveCustomFunc");
        if (onCallBack->IsFunction()) {
            RefPtr<JsFunction> jsFuncCallBack =
                AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(onCallBack));
            customCallBack = [func = std::move(jsFuncCallBack), id = Container::CurrentId()](float time) -> float {
                ContainerScope scope(id);
                JSRef<JSVal> params[1];
                params[0] = JSRef<JSVal>::Make(ToJSValue(time));
                auto result = func->ExecuteJS(1, params);
                auto resultValue = result->IsNumber() ? result->ToNumber<float>() : 1.0f;
                return resultValue;
            };
        }
        auto jsCurveString = object->GetProperty("__curveString");
        if (jsCurveString->IsString()) {
            auto aniTimFunc = jsCurveString->ToString();
            if (aniTimFunc == DOM_ANIMATION_TIMING_FUNCTION_CUSTOM && customCallBack) {
                curve = CreateCurve(customCallBack);
            } else if (aniTimFunc != DOM_ANIMATION_TIMING_FUNCTION_CUSTOM) {
                curve = CreateCurve(aniTimFunc);
            }
        }
    }
    SwiperModel::GetInstance()->SetCurve(curve);
}

void JSSwiper::SetOnChange(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto changeHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChange = [executionContext = info.GetExecutionContext(), func = std::move(changeHandler), node = targetNode](
                        const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onChange callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Swiper.OnChange");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };

    SwiperModel::GetInstance()->SetOnChange(std::move(onChange));
}

void JSSwiper::SetOnUnselected(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto unselectedHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onUnselected = [executionContext = info.GetExecutionContext(), func = std::move(unselectedHandler),
                          node = targetNode](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onUnselected callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Swiper.onUnselected");
        ACE_SCOPED_TRACE("Swiper.onUnselected index %d", swiperInfo->GetIndex());
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };
    SwiperModel::GetInstance()->SetOnUnselected(std::move(onUnselected));
}

void JSSwiper::SetOnAnimationStart(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto animationStartHandler = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onAnimationStart = [executionContext = info.GetExecutionContext(), func = std::move(animationStartHandler),
                                    node = targetNode](
                                    int32_t index, int32_t targetIndex, const AnimationCallbackInfo& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
            ACE_SCORING_EVENT("Swiper.onAnimationStart");
            PipelineContext::SetCallBackNode(node);
            func->Execute(index, targetIndex, info);
        };

        SwiperModel::GetInstance()->SetOnAnimationStart(std::move(onAnimationStart));
        return;
    }

    auto animationStartHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAnimationStart = [executionContext = info.GetExecutionContext(), func = std::move(animationStartHandler),
                                node = targetNode](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onAnimationStart callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Swiper.onAnimationStart");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };

    SwiperModel::GetInstance()->SetOnAnimationStart(std::move(onAnimationStart));
}

void JSSwiper::SetOnAnimationEnd(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    if (Container::IsCurrentUseNewPipeline()) {
        auto animationEndHandler = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(info[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onAnimationEnd = [executionContext = info.GetExecutionContext(), func = std::move(animationEndHandler),
                                  node = targetNode](int32_t index, const AnimationCallbackInfo& info) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
            ACE_SCORING_EVENT("Swiper.onAnimationEnd");
            PipelineContext::SetCallBackNode(node);
            func->Execute(index, info);
        };

        SwiperModel::GetInstance()->SetOnAnimationEnd(std::move(onAnimationEnd));
        return;
    }

    auto animationEndHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onAnimationEnd = [executionContext = info.GetExecutionContext(), func = std::move(animationEndHandler),
                              node = targetNode](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onAnimationEnd callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Swiper.onAnimationEnd");
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };

    SwiperModel::GetInstance()->SetOnAnimationEnd(std::move(onAnimationEnd));
}

void JSSwiper::SetOnGestureSwipe(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }

    auto gestureSwipeHandler = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onGestureSwipe = [executionContext = info.GetExecutionContext(), func = std::move(gestureSwipeHandler),
                              node = targetNode](int32_t index, const AnimationCallbackInfo& info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        ACE_SCORING_EVENT("Swiper.onGestureSwipe");
        PipelineContext::SetCallBackNode(node);
        func->Execute(index, info);
    };

    SwiperModel::GetInstance()->SetOnGestureSwipe(std::move(onGestureSwipe));
}

void JSSwiper::SetOnClick(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSInteractableView::JsOnClick(info);
        return;
    }

    if (!info[0]->IsFunction()) {
        return;
    }

    RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onClick = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), node = targetNode](
                       const BaseEventInfo* info, const RefPtr<V2::InspectorFunctionImpl>& impl) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
        if (!clickInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onClick callback execute failed.");
            return;
        }
        auto newInfo = *clickInfo;
        if (impl) {
            impl->UpdateEventInfo(newInfo);
        }
        ACE_SCORING_EVENT("onClick");
        PipelineContext::SetCallBackNode(node);
        func->Execute(newInfo);
    };

    SwiperModel::GetInstance()->SetOnClick(onClick);
}

void JSSwiper::SetWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    SetWidth(info[0]);
}

void JSSwiper::SetWidth(const JSRef<JSVal>& jsValue)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsWidth(jsValue);
        return;
    }

    JSViewAbstract::JsWidth(jsValue);
    SwiperModel::GetInstance()->SetMainSwiperSizeWidth();
}

void JSSwiper::SetHeight(const JSRef<JSVal>& jsValue)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsHeight(jsValue);
        return;
    }

    JSViewAbstract::JsHeight(jsValue);
    SwiperModel::GetInstance()->SetMainSwiperSizeHeight();
}

void JSSwiper::SetHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    SetHeight(info[0]);
}

void JSSwiper::SetSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (!info[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> sizeObj = JSRef<JSObject>::Cast(info[0]);
    SetWidth(sizeObj->GetProperty("width"));
    SetHeight(sizeObj->GetProperty("height"));
}

void JSSwiperController::JSBind(BindingTarget globalObj)
{
    JSClass<JSSwiperController>::Declare("SwiperController");
    JSClass<JSSwiperController>::CustomMethod("swipeTo", &JSSwiperController::SwipeTo);
    JSClass<JSSwiperController>::CustomMethod("showNext", &JSSwiperController::ShowNext);
    JSClass<JSSwiperController>::CustomMethod("showPrevious", &JSSwiperController::ShowPrevious);
    JSClass<JSSwiperController>::CustomMethod("changeIndex", &JSSwiperController::ChangeIndex);
    JSClass<JSSwiperController>::CustomMethod("finishAnimation", &JSSwiperController::FinishAnimation);
    JSClass<JSSwiperController>::CustomMethod("preloadItems", &JSSwiperController::PreloadItems);
    JSClass<JSSwiperController>::Bind(globalObj, JSSwiperController::Constructor, JSSwiperController::Destructor);
}

void JSSwiperController::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSSwiperController>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSSwiperController::Destructor(JSSwiperController* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

void JSSwiperController::SwipeTo(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (args.Length() < 1 || !args[0]->IsNumber()) {
        LOGE("Param is not valid");
        return;
    }
    if (controller_) {
        controller_->SwipeTo(args[0]->ToNumber<int32_t>());
    } else {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "swipeTo: Swiper controller not bind.");
    }
}

void JSSwiperController::ShowNext(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->ShowNext();
    } else {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "showNext: Swiper controller not bind.");
    }
}

void JSSwiperController::ShowPrevious(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (controller_) {
        controller_->ShowPrevious();
    } else {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "showPrevious: Swiper controller not bind.");
    }
}

void JSSwiperController::ChangeIndex(const JSCallbackInfo& args)
{
    if (!controller_) {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "changeIndex: Swiper controller not bind.");
        return;
    }
    if (args.Length() < 1 || !args[0]->IsNumber()) {
        return;
    }
    int32_t index = args[0]->ToNumber<int32_t>();
    if (args.Length() > 1 && args[1]->IsNumber()) {
        int32_t animationMode = args[1]->ToNumber<int32_t>();
        if (animationMode < 0 || animationMode >= static_cast<int32_t>(SWIPER_ANIMATION_MODE.size())) {
            animationMode = 0;
        }
        controller_->ChangeIndex(index, SWIPER_ANIMATION_MODE[animationMode]);
        return;
    }
    bool useAnimation = false;
    if (args.Length() > 1 && args[1]->IsBoolean()) {
        useAnimation = args[1]->ToBoolean();
    }
    controller_->ChangeIndex(index, useAnimation);
}

void JSSwiperController::FinishAnimation(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (!controller_) {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "finishAnimation: Swiper controller not bind.");
        return;
    }

    if (args.Length() > 0 && args[0]->IsFunction()) {
        RefPtr<JsFunction> jsFunc = AceType::MakeRefPtr<JsFunction>(JSRef<JSObject>(), JSRef<JSFunc>::Cast(args[0]));
        auto targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        auto onFinish = [execCtx = args.GetExecutionContext(), func = std::move(jsFunc), node = targetNode]() {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.finishAnimation");
            PipelineContext::SetCallBackNode(node);
            TAG_LOGD(AceLogTag::ACE_SWIPER, "SwiperController finishAnimation callback execute.");
            func->Execute();
        };

        controller_->SetFinishCallback(onFinish);
        controller_->FinishAnimation();
        return;
    }

    controller_->FinishAnimation();
}

void JSSwiperController::OldPreloadItems(const JSCallbackInfo& args)
{
    ContainerScope scope(instanceId_);
    if (!controller_) {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "preloadItems: Swiper controller not bind.");
        return;
    }

    if (args.Length() != LENGTH_TWO || !args[0]->IsArray() || !args[1]->IsFunction()) {
        return;
    }

    auto indexArray = JSRef<JSArray>::Cast(args[0]);
    size_t size = indexArray->Length();
    std::set<int32_t> indexSet;
    for (size_t i = 0; i < size; i++) {
        int32_t index = -1;
        JSViewAbstract::ParseJsInt32(indexArray->GetValueAt(i), index);
        indexSet.emplace(index);
    }

    RefPtr<JsSwiperFunction> jsFunc = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(args[1]));
    auto onPreloadFinish =
        [execCtx = args.GetExecutionContext(), func = std::move(jsFunc)](int32_t errorCode, std::string message) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.preloadItems");
            TAG_LOGI(AceLogTag::ACE_SWIPER, "SwiperController preloadItems callback execute.");
            func->Execute(errorCode);
        };

    controller_->SetPreloadFinishCallback(onPreloadFinish);
    controller_->PreloadItems(indexSet);
}

void JSSwiperController::NewPreloadItems(const JSCallbackInfo& args)
{
    if (!controller_) {
        EventReport::ReportScrollableErrorEvent(
            "Swiper", ScrollableErrorType::CONTROLLER_NOT_BIND, "preloadItems: Swiper controller not bind.");
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    ContainerScope scope(instanceId_);
    auto engine = EngineHelper::GetCurrentEngine();
    CHECK_NULL_VOID(engine);
    NativeEngine* nativeEngine = engine->GetNativeEngine();
    auto env = reinterpret_cast<napi_env>(nativeEngine);
    auto asyncContext = std::make_shared<SwiperControllerAsyncContext>();
    asyncContext->env = env;
    napi_value promise = nullptr;
    napi_create_promise(env, &asyncContext->deferred, &promise);
    ScopeRAII scopeRaii(env);
    std::set<int32_t> indexSet;
    if (args.Length() > 0 && args[0]->IsArray()) {
        auto indexArray = JSRef<JSArray>::Cast(args[0]);
        size_t size = indexArray->Length();
        for (size_t i = 0; i < size; i++) {
            int32_t index = -1;
            JSViewAbstract::ParseJsInt32(indexArray->GetValueAt(i), index);
            indexSet.emplace(index);
        }
    }

    auto onPreloadFinish = [asyncContext](int32_t errorCode, std::string message) {
        CHECK_NULL_VOID(asyncContext);
        HandleDeferred(asyncContext, errorCode, message);
    };
    controller_->SetPreloadFinishCallback(onPreloadFinish);
    controller_->PreloadItems(indexSet);
    ReturnPromise(args, promise);
}

void JSSwiperController::PreloadItems(const JSCallbackInfo& args)
{
    if (Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_EIGHTEEN) && args.Length() == 1) {
        NewPreloadItems(args);
        return;
    }

    OldPreloadItems(args);
}

void JSSwiper::SetNestedScroll(const JSCallbackInfo& args)
{
    // default value
    NestedScrollOptions nestedOpt = {
        .forward = NestedScrollMode::SELF_ONLY,
        .backward = NestedScrollMode::SELF_ONLY,
    };
    if (args.Length() < 1 || !args[0]->IsNumber()) {
        SwiperModel::GetInstance()->SetNestedScroll(nestedOpt);
        return;
    }
    int32_t value = -1;
    JSViewAbstract::ParseJsInt32(args[0], value);
    auto mode = static_cast<NestedScrollMode>(value);
    if (mode < NestedScrollMode::SELF_ONLY || mode > NestedScrollMode::SELF_FIRST) {
        SwiperModel::GetInstance()->SetNestedScroll(nestedOpt);
        return;
    }
    nestedOpt.forward = mode;
    nestedOpt.backward = mode;
    SwiperModel::GetInstance()->SetNestedScroll(nestedOpt);
    args.ReturnSelf();
}

void JSSwiper::SetCustomContentTransition(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsObject()) {
        return;
    }

    SwiperContentAnimatedTransition transitionInfo;
    auto transitionObj = JSRef<JSObject>::Cast(info[0]);
    JSRef<JSVal> timeoutProperty = transitionObj->GetProperty("timeout");
    if (timeoutProperty->IsNumber()) {
        auto timeout = timeoutProperty->ToNumber<int32_t>();
        transitionInfo.timeout = timeout < 0 ? DEFAULT_CUSTOM_ANIMATION_TIMEOUT : timeout;
    } else {
        transitionInfo.timeout = DEFAULT_CUSTOM_ANIMATION_TIMEOUT;
    }

    JSRef<JSVal> transition = transitionObj->GetProperty("transition");
    if (transition->IsFunction()) {
        auto jsOnTransition = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(transition));
        auto onTransition = [execCtx = info.GetExecutionContext(), func = std::move(jsOnTransition)](
                                const RefPtr<SwiperContentTransitionProxy>& proxy) {
            JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
            ACE_SCORING_EVENT("Swiper.customContentTransition");
            func->Execute(proxy);
        };
        transitionInfo.transition = std::move(onTransition);
    }
    SwiperModel::GetInstance()->SetCustomContentTransition(transitionInfo);
}

void JSSwiper::SetOnContentDidScroll(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsFunction()) {
        return;
    }

    auto contentDidScrollHandler = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onContentDidScroll = [execCtx = info.GetExecutionContext(),
                                func = std::move(contentDidScrollHandler)](
                                int32_t selectedIndex, int32_t index, float position, float mainAxisLength) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("Swiper.onContentDidScroll");
        func->Execute(selectedIndex, index, position, mainAxisLength);
    };
    SwiperModel::GetInstance()->SetOnContentDidScroll(std::move(onContentDidScroll));
}

void JSSwiper::SetOnContentWillScroll(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }

    if (info[0]->IsUndefined() || info[0]->IsNull()) {
        SwiperModel::GetInstance()->SetOnContentWillScroll(nullptr);
        return;
    }

    if (!info[0]->IsFunction()) {
        return;
    }

    auto handler = AceType::MakeRefPtr<JsSwiperFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto callback = [execCtx = info.GetExecutionContext(), func = std::move(handler)](
                        const SwiperContentWillScrollResult& result) -> bool {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, true);
        ACE_SCORING_EVENT("Swiper.onContentWillScroll");
        auto ret = func->Execute(result);
        if (!ret->IsBoolean()) {
            return true;
        }
        return ret->ToBoolean();
    };
    SwiperModel::GetInstance()->SetOnContentWillScroll(std::move(callback));
}

void JSSwiper::SetPageFlipMode(const JSCallbackInfo& info)
{
    // default value
    int32_t value = 0;
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        SwiperModel::GetInstance()->SetPageFlipMode(value);
        return;
    }
    JSViewAbstract::ParseJsInt32(info[0], value);
    SwiperModel::GetInstance()->SetPageFlipMode(value);
}

void JSSwiper::GetAutoPlayOptionsInfo(const JSRef<JSObject>& obj, SwiperAutoPlayOptions& swiperAutoPlayOptions)
{
    auto stopWhenTouched = obj->GetProperty("stopWhenTouched");
    if (stopWhenTouched->IsBoolean()) {
        swiperAutoPlayOptions.stopWhenTouched = stopWhenTouched->ToBoolean();
    }
}

void JSSwiper::SetOnSelected(const JSCallbackInfo& info)
{
    if (!info[0]->IsFunction()) {
        return;
    }
    auto selectedHandler = AceType::MakeRefPtr<JsEventFunction<SwiperChangeEvent, 1>>(
        JSRef<JSFunc>::Cast(info[0]), SwiperChangeEventToJSValue);
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onSelected = [executionContext = info.GetExecutionContext(), func = std::move(selectedHandler),
                          node = targetNode](const BaseEventInfo* info) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(executionContext);
        const auto* swiperInfo = TypeInfoHelper::DynamicCast<SwiperChangeEvent>(info);
        if (!swiperInfo) {
            TAG_LOGW(AceLogTag::ACE_SWIPER, "Swiper onSelected callback execute failed.");
            return;
        }
        ACE_SCORING_EVENT("Swiper.onSelected");
        ACE_SCOPED_TRACE("Swiper.onSelected index %d", swiperInfo->GetIndex());
        PipelineContext::SetCallBackNode(node);
        func->Execute(*swiperInfo);
    };
    SwiperModel::GetInstance()->SetOnSelected(std::move(onSelected));
}
} // namespace OHOS::Ace::Framework

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

#include "frameworks/bridge/declarative_frontend/jsview/js_tabs.h"
#include "interfaces/inner_api/ui_session/ui_session_manager.h"

#include "base/log/ace_scoring_log.h"
#include "bridge/declarative_frontend/engine/functions/js_swiper_function.h"
#include "bridge/declarative_frontend/engine/functions/js_tabs_function.h"
#include "bridge/declarative_frontend/jsview/js_scrollable.h"
#include "bridge/declarative_frontend/jsview/js_tabs_controller.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "bridge/declarative_frontend/jsview/models/tabs_model_impl.h"
#include "core/animation/curve.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/decoration.h"
#include "core/components_ng/base/view_stack_model.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/tabs/tab_content_transition_proxy.h"
#include "core/components_ng/pattern/tabs/tabs_model_ng.h"

namespace OHOS::Ace {

std::unique_ptr<TabsModel> TabsModel::instance_ = nullptr;
std::mutex TabsModel::mutex_;

TabsModel* TabsModel::GetInstance()
{
    if (!instance_) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!instance_) {
#ifdef NG_BUILD
            instance_.reset(new NG::TabsModelNG());
#else
            if (Container::IsCurrentUseNewPipeline()) {
                instance_.reset(new NG::TabsModelNG());
            } else {
                instance_.reset(new Framework::TabsModelImpl());
            }
#endif
        }
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {
constexpr int32_t PARAM_COUNT = 2;
constexpr int32_t SM_COLUMN_NUM = 4;
constexpr int32_t MD_COLUMN_NUM = 8;
constexpr int32_t LG_COLUMN_NUM = 12;
const std::vector<BarPosition> BAR_POSITIONS = { BarPosition::START, BarPosition::END };

const std::vector<BlurStyle> BAR_BLURSTYLE = {
    BlurStyle::NO_MATERIAL,
    BlurStyle::THIN,
    BlurStyle::REGULAR,
    BlurStyle::THICK,
    BlurStyle::BACKGROUND_THIN,
    BlurStyle::BACKGROUND_REGULAR,
    BlurStyle::BACKGROUND_THICK,
    BlurStyle::BACKGROUND_ULTRA_THICK,
    BlurStyle::COMPONENT_ULTRA_THIN,
    BlurStyle::COMPONENT_THIN,
    BlurStyle::COMPONENT_REGULAR,
    BlurStyle::COMPONENT_THICK,
    BlurStyle::COMPONENT_ULTRA_THICK,
};

RefPtr<Curve> CreateAnimationCurveByObject(const JSCallbackInfo& info)
{
    RefPtr<Curve> curve;
    if (!info[0]->IsObject()) {
        return curve;
    }
    auto object = JSRef<JSObject>::Cast(info[0]);
    std::function<float(float)> customCallBack = nullptr;
    JSRef<JSVal> onCallBack = object->GetProperty("__curveCustomFunc");
    if (onCallBack->IsFunction()) {
        auto vm = info.GetVm();
        auto jsFunc = JSRef<JSFunc>::Cast(onCallBack);
        auto func = jsFunc->GetLocalHandle();
        customCallBack = [vm, func = panda::CopyableGlobal(vm, func), id = Container::CurrentId()](
                             float time) -> float {
            ContainerScope scope(id);
            panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, time) };
            auto result = func->Call(vm, func.ToLocal(), params, 1);
            auto resultValue = result->IsNumber() ? static_cast<float>(result->ToNumber(vm)->Value()) : 1.0f;
            return resultValue;
        };
    }
    auto jsCurveString = object->GetProperty("__curveString");
    if (jsCurveString->IsString()) {
        auto aniTimFunc = jsCurveString->ToString();
        if (aniTimFunc == DOM_ANIMATION_TIMING_FUNCTION_CUSTOM && customCallBack) {
            curve = CreateCurve(customCallBack);
        } else if (aniTimFunc != DOM_ANIMATION_TIMING_FUNCTION_CUSTOM) {
            curve = CreateCurve(aniTimFunc, false);
        }
    }
    return curve;
}
} // namespace

void ParseTabsIndexObject(const JSCallbackInfo& info, const JSRef<JSVal>& changeEventVal)
{
    CHECK_NULL_VOID(!changeEventVal->IsUndefined() && changeEventVal->IsFunction());

    auto vm = info.GetVm();
    auto jsFunc = JSRef<JSFunc>::Cast(changeEventVal);
    auto func = jsFunc->GetLocalHandle();
    WeakPtr<NG::FrameNode> targetNode = AceType::WeakClaim(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
    auto onChangeEvent = [vm, func = panda::CopyableGlobal(vm, func), node = targetNode](const BaseEventInfo* info) {
        panda::LocalScope pandaScope(vm);
        panda::TryCatch trycatch(vm);
        const auto* tabsInfo = TypeInfoHelper::DynamicCast<TabContentChangeEvent>(info);
        if (!tabsInfo) {
            TAG_LOGW(AceLogTag::ACE_TABS, "ParseTabsIndexObject execute onChange event failed.");
            return;
        }
        ACE_SCORING_EVENT("Tabs.onChangeEvent");
        PipelineContext::SetCallBackNode(node);
        panda::Local<panda::JSValueRef> params[1] = { panda::NumberRef::New(vm, tabsInfo->GetIndex()) };
        func->Call(vm, func.ToLocal(), params, 1);
    };
    TabsModel::GetInstance()->SetOnChangeEvent(std::move(onChangeEvent));
}

void JSTabs::Create(const JSCallbackInfo& info)
{
    BarPosition barPosition = BarPosition::START;
    RefPtr<TabController> tabController;
    RefPtr<NG::TabsControllerNG> tabsController = AceType::MakeRefPtr<NG::TabsControllerNG>();
    int32_t index = -1;
    JSRef<JSVal> changeEventVal;
    auto jsValue = info[0];
    if (jsValue->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
        JSRef<JSVal> val = obj->GetProperty("barPosition");
        if (val->IsNumber()) {
            auto barPositionVal = val->ToNumber<int32_t>();
            if (barPositionVal >= 0 && barPositionVal < static_cast<int32_t>(BAR_POSITIONS.size())) {
                barPosition = BAR_POSITIONS[barPositionVal];
            }
        }
        JSRef<JSVal> controller = obj->GetProperty("controller");
        if (controller->IsObject()) {
            auto* jsTabsController = JSRef<JSObject>::Cast(controller)->Unwrap<JSTabsController>();
            if (jsTabsController) {
                jsTabsController->SetInstanceId(Container::CurrentId());
                tabController = jsTabsController->GetController();
                jsTabsController->SetTabsController(tabsController);
            }
        }
        JSRef<JSVal> indexVal = obj->GetProperty("index");
        if (indexVal->IsNumber()) {
            index = indexVal->ToNumber<int32_t>();
            index = index < 0 ? 0 : index;
            if (!tabController) {
                tabController = JSTabsController::CreateController();
            }
#ifndef NG_BUILD
            tabController->SetInitialIndex(index);
#endif
            changeEventVal = obj->GetProperty("$index");
        } else if (indexVal->IsObject()) {
            JSRef<JSObject> indexObj = JSRef<JSObject>::Cast(indexVal);
            auto indexValueProperty = indexObj->GetProperty("value");
            if (indexValueProperty->IsNumber()) {
                index = indexValueProperty->ToNumber<int32_t>();
                index = index < 0 ? 0 : index;
            }
            changeEventVal = indexObj->GetProperty("changeEvent");
        }
    }

    TabsModel::GetInstance()->Create(barPosition, index, tabController, tabsController);
    ParseTabsIndexObject(info, changeEventVal);
    SetBarModifier(info, jsValue);
}

void JSTabs::Pop()
{
    if (ViewStackModel::GetInstance()->IsPrebuilding()) {
        return ViewStackModel::GetInstance()->PushPrebuildCompCmd("[JSTabs][pop]", &JSTabs::Pop);
    }
    TabsModel::GetInstance()->Pop();
}

void JSTabs::SetBarPosition(const JSCallbackInfo& info)
{
    BarPosition barVal = BarPosition::START;
    if (info.Length() > 0 && info[0]->IsNumber()) {
        auto barPositionVal = info[0]->ToNumber<int32_t>();
        if (barPositionVal >= 0 && barPositionVal < static_cast<int32_t>(BAR_POSITIONS.size())) {
            barVal = BAR_POSITIONS[barPositionVal];
        }
    }

    TabsModel::GetInstance()->SetTabBarPosition(barVal);
}

void JSTabs::SetVertical(const std::string& value)
{
    TabsModel::GetInstance()->SetIsVertical(StringToBool(value));
}

void JSTabs::SetScrollable(const std::string& value)
{
    if (value == "undefined") {
        TabsModel::GetInstance()->SetScrollable(true);
        return;
    }
    TabsModel::GetInstance()->SetScrollable(StringToBool(value));
}

void JSTabs::SetBarMode(const JSCallbackInfo& info)
{
    TabBarMode barMode = TabBarMode::FIXED;
    if (info.Length() < 1) {
        TabsModel::GetInstance()->SetTabBarMode(barMode);
        return;
    }
    auto barModeInfo = info[0];
    if (barModeInfo->IsString()) {
        barMode = ConvertStrToTabBarMode(barModeInfo->ToString());
    }
    if (barMode == TabBarMode::SCROLLABLE) {
        if (info.Length() > 1 && info[1]->IsObject()) {
            SetScrollableBarModeOptions(info[1]);
        } else {
            TabsModel::GetInstance()->ResetScrollableBarModeOptions();
        }
    }
    TabsModel::GetInstance()->SetTabBarMode(barMode);
}

void JSTabs::SetBarWidth(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    RefPtr<ResourceObject> widthResObj;
    CalcDimension width = Dimension(-1.0, DimensionUnit::VP);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_WIDTH, nullptr);
    if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
        if (!ParseJsDimensionVpNG(info[0], width, widthResObj)) {
            width = Dimension(-1.0, DimensionUnit::VP);
            TabsModel::GetInstance()->SetTabBarWidth(width);
            return;
        }
    } else {
        ParseJsDimensionVp(info[0], width);
    }
    TabsModel::GetInstance()->SetTabBarWidth(width);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_WIDTH, widthResObj);
}

void JSTabs::SetBarHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        return;
    }
    CalcDimension height = Dimension(-1.0, DimensionUnit::VP);
    RefPtr<ResourceObject> heightResObj;
    bool adaptiveHeight = false;
    bool noMinHeightLimit = false;
    auto barHeightInfo = info[0];
    if (info.Length() == 2) { //2 is info length
        auto minHeightLimitInfo = info[1];
        if (minHeightLimitInfo->IsBoolean()) {
            noMinHeightLimit = minHeightLimitInfo->ToBoolean();
        }
    }

    if (barHeightInfo->IsString() && barHeightInfo->ToString() == "auto") {
        adaptiveHeight = true;
    } else {
        if (Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_TEN)) {
            if (!ParseJsDimensionVpNG(barHeightInfo, height, heightResObj)) {
                height = Dimension(-1.0, DimensionUnit::VP);
            }
        } else {
            ParseJsDimensionVp(barHeightInfo, height);
        }
    }
    TabsModel::GetInstance()->SetBarAdaptiveHeight(adaptiveHeight);
    TabsModel::GetInstance()->SetNoMinHeightLimit(noMinHeightLimit);
    TabsModel::GetInstance()->SetTabBarHeight(height);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_HEIGHT, heightResObj);
}

void JSTabs::SetWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    if (info.Length() < 1) {
        return;
    }
    auto widthInfo = info[0];
    if (widthInfo->IsString() && widthInfo->ToString().empty()) {
        return;
    }
    if (widthInfo->IsString() && widthInfo->ToString() == "auto") {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(true);
        TabsModel::GetInstance()->SetWidthAuto(true);
        return;
    }

    TabsModel::GetInstance()->SetWidthAuto(false);
}

void JSTabs::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    if (info.Length() < 1) {
        return;
    }
    auto heightInfo = info[0];
    if (heightInfo->IsString() && heightInfo->ToString().empty()) {
        return;
    }
    if (heightInfo->IsString() && heightInfo->ToString() == "auto") {
        ViewAbstractModel::GetInstance()->ClearWidthOrHeight(false);
        TabsModel::GetInstance()->SetHeightAuto(true);
        return;
    }

    TabsModel::GetInstance()->SetHeightAuto(false);
}

void JSTabs::SetIndex(int32_t index)
{
    TabsModel::GetInstance()->SetIndex(index);
}

void JSTabs::SetAnimationCurve(const JSCallbackInfo& info)
{
    RefPtr<Curve> curve;
    if (info[0]->IsString()) {
        curve = CreateCurve(info[0]->ToString(), false);
    } else if (info[0]->IsObject()) {
        curve = CreateAnimationCurveByObject(info);
    }
    TabsModel::GetInstance()->SetAnimationCurve(curve);
}

void JSTabs::SetAnimationDuration(const JSCallbackInfo& info)
{
    if (info.Length() <= 0) {
        TabsModel::GetInstance()->SetAnimationDuration(-1);
        return;
    }
    auto animationDurationInfo = info[0];
    if ((!animationDurationInfo->IsNull() && !animationDurationInfo->IsNumber()) ||
        (animationDurationInfo->IsNull() && Container::GreatOrEqualAPIVersion(PlatformVersion::VERSION_ELEVEN))) {
        TabsModel::GetInstance()->SetAnimationDuration(-1);
        return;
    }
    auto value = animationDurationInfo->IsNumber() ? animationDurationInfo->ToNumber<int32_t>() : 0;
    TabsModel::GetInstance()->SetAnimationDuration(value);
}

void JSTabs::SetFadingEdge(const JSCallbackInfo& info)
{
    bool fadingEdge = true;
    if (info.Length() > 0) {
        ParseJsBool(info[0], fadingEdge);
    }
    TabsModel::GetInstance()->SetFadingEdge(fadingEdge);
}

void JSTabs::SetBarOverlap(const JSCallbackInfo& info)
{
    bool barOverlap = false;
    if (info.Length() > 0) {
        ParseJsBool(info[0], barOverlap);
    }
    TabsModel::GetInstance()->SetBarOverlap(barOverlap);
}

void JSTabs::SetBarBackgroundColor(const JSCallbackInfo& info)
{
    RefPtr<ResourceObject> resObj;
    Color backgroundColor = Color::BLACK.BlendOpacity(0.0f);
    if (info.Length() > 0) {
        if (ConvertFromJSValue(info[0], backgroundColor, resObj)) {
            TabsModel::GetInstance()->SetBarBackgroundColorByUser(true);
        } else {
            TabsModel::GetInstance()->SetBarBackgroundColorByUser(false);
        }
    }
    if (SystemProperties::ConfigChangePerform()) {
        TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_BACKGROUND_COLOR, resObj);
    }
    TabsModel::GetInstance()->SetBarBackgroundColor(backgroundColor);
}

void JSTabs::SetBarBackgroundBlurStyle(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    BlurStyleOption styleOption;
    if (info[0]->IsNumber()) {
        auto blurStyle = info[0]->ToNumber<int32_t>();
        if (blurStyle >= static_cast<int>(BlurStyle::NO_MATERIAL) &&
            blurStyle <= static_cast<int>(BlurStyle::COMPONENT_ULTRA_THICK)) {
            styleOption.blurStyle = static_cast<BlurStyle>(blurStyle);
        }
    }
    RefPtr<ResourceObject> inactiveColorStrObj;
    if (info.Length() > 1 && info[1]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[1]);
        ParseBlurStyleOption(jsOption, styleOption);
        if (SystemProperties::ConfigChangePerform()) {
            ParseJsColor(jsOption->GetProperty("inactiveColor"), styleOption.inactiveColor, inactiveColorStrObj);
        }
    }
    TabsModel::GetInstance()->SetBarBackgroundBlurStyle(styleOption);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BlurStyle_INACTIVE_COLOR, inactiveColorStrObj);
}

void JSTabs::SetDivider(const JSCallbackInfo& info)
{
    TabsItemDivider divider;
    CalcDimension dividerStrokeWidth;
    CalcDimension dividerStartMargin;
    CalcDimension dividerEndMargin;
    RefPtr<TabTheme> tabTheme = GetTheme<TabTheme>();
    CHECK_NULL_VOID(tabTheme);
    RefPtr<ResourceObject> widthResObj;
    RefPtr<ResourceObject> colorResObj;
    RefPtr<ResourceObject> startMarginResObj;
    RefPtr<ResourceObject> endMarginResObj;

    if (info.Length() > 0) {
        auto dividerInfo = info[0];
        JSRef<JSObject> obj = JSRef<JSObject>::New();
        if (dividerInfo->IsObject()) {
            obj = JSRef<JSObject>::Cast(dividerInfo);
        }
        if (dividerInfo->IsNull()) {
            divider.isNull = true;
        } else {
            if (!dividerInfo->IsObject() ||
                !ParseJsDimensionVp(obj->GetProperty("strokeWidth"), dividerStrokeWidth, widthResObj) ||
                dividerStrokeWidth.Value() < 0.0f || dividerStrokeWidth.Unit() == DimensionUnit::PERCENT) {
                divider.strokeWidth.Reset();
            } else {
                divider.strokeWidth = dividerStrokeWidth;
            }
            if (!dividerInfo->IsObject() ||
                !ConvertFromJSValue(obj->GetProperty("color"), divider.color, colorResObj)) {
                divider.color = tabTheme->GetDividerColor();
                TabsModel::GetInstance()->SetDividerColorByUser(false);
            } else {
                TabsModel::GetInstance()->SetDividerColorByUser(true);
            }
            if (!dividerInfo->IsObject() ||
                !ParseJsDimensionVp(obj->GetProperty("startMargin"), dividerStartMargin, startMarginResObj) ||
                dividerStartMargin.Value() < 0.0f || dividerStartMargin.Unit() == DimensionUnit::PERCENT) {
                divider.startMargin.Reset();
            } else {
                divider.startMargin = dividerStartMargin;
            }
            if (!dividerInfo->IsObject() ||
                !ParseJsDimensionVp(obj->GetProperty("endMargin"), dividerEndMargin, endMarginResObj) ||
                dividerEndMargin.Value() < 0.0f || dividerEndMargin.Unit() == DimensionUnit::PERCENT) {
                divider.endMargin.Reset();
            } else {
                divider.endMargin = dividerEndMargin;
            }
        }
    }
    TabsModel::GetInstance()->SetDivider(divider);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::DIVIDER_STROKE_WIDTH, widthResObj);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::DIVIDER_COLOR, colorResObj);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::DIVIDER_START_MARGIN, startMarginResObj);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::DIVIDER_END_MARGIN, endMarginResObj);
}

void JSTabs::SetClip(const JSCallbackInfo& info)
{
    if (info[0]->IsObject() || !Container::IsCurrentUseNewPipeline()) {
        JSViewAbstract::JsClip(info);
        return;
    }
    if (info[0]->IsBoolean()) {
        TabsModel::GetInstance()->SetClipEdge(info[0]->ToBoolean());
    }
}

void JSTabs::SetScrollableBarModeOptions(const JSRef<JSVal>& info)
{
    ScrollableBarModeOptions option;
    RefPtr<ResourceObject> resObj;
    auto optionParam = JSRef<JSObject>::Cast(info);
    CalcDimension margin = Dimension(0.0, DimensionUnit::VP);
    if (!ParseJsDimensionVp(optionParam->GetProperty("margin"), margin, resObj) || Negative(margin.Value()) ||
        margin.Unit() == DimensionUnit::PERCENT) {
        option.margin = 0.0_vp;
    } else {
        option.margin = margin;
    }
    auto nonScrollableLayoutStyle = optionParam->GetProperty("nonScrollableLayoutStyle");
    int32_t layoutStyle;
    if (!ConvertFromJSValue(nonScrollableLayoutStyle, layoutStyle) ||
        layoutStyle < static_cast<int32_t>(LayoutStyle::ALWAYS_CENTER) ||
        layoutStyle > static_cast<int32_t>(LayoutStyle::SPACE_BETWEEN_OR_CENTER)) {
        option.nonScrollableLayoutStyle = std::nullopt;
    } else {
        option.nonScrollableLayoutStyle = (static_cast<LayoutStyle>(layoutStyle));
    }
    TabsModel::GetInstance()->SetScrollableBarModeOptions(option);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::SCROLLABLE_BAR_MARGIN, resObj);
}

void JSTabs::SetBarGridAlign(const JSCallbackInfo& info)
{
    BarGridColumnOptions columnOption;
    RefPtr<ResourceObject> gutterResObj;
    RefPtr<ResourceObject> marginResObj;
    if (info.Length() > 0 && info[0]->IsObject()) {
        auto gridParam = JSRef<JSObject>::Cast(info[0]);
        auto sm = gridParam->GetProperty("sm");
        if (sm->IsNumber() && sm->ToNumber<int32_t>() >= 0 && sm->ToNumber<int32_t>() <= SM_COLUMN_NUM &&
            sm->ToNumber<int32_t>() % 2 == 0) {
            columnOption.sm = sm->ToNumber<int32_t>();
        }
        auto md = gridParam->GetProperty("md");
        if (md->IsNumber() && md->ToNumber<int32_t>() >= 0 && md->ToNumber<int32_t>() <= MD_COLUMN_NUM &&
            md->ToNumber<int32_t>() % 2 == 0) {
            columnOption.md = md->ToNumber<int32_t>();
        }
        auto lg = gridParam->GetProperty("lg");
        if (lg->IsNumber() && lg->ToNumber<int32_t>() >= 0 && lg->ToNumber<int32_t>() <= LG_COLUMN_NUM &&
            lg->ToNumber<int32_t>() % 2 == 0) {
            columnOption.lg = lg->ToNumber<int32_t>();
        }
        CalcDimension columnGutter;
        if (ParseJsDimensionVp(gridParam->GetProperty("gutter"), columnGutter, gutterResObj) &&
            NonNegative(columnGutter.Value()) && columnGutter.Unit() != DimensionUnit::PERCENT) {
            columnOption.gutter = columnGutter;
        }
        CalcDimension columnMargin;
        if (ParseJsDimensionVp(gridParam->GetProperty("margin"), columnMargin, marginResObj) &&
            NonNegative(columnMargin.Value()) && columnMargin.Unit() != DimensionUnit::PERCENT) {
            columnOption.margin = columnMargin;
        }
    }
    TabsModel::GetInstance()->SetBarGridAlign(columnOption);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_GRID_GUTTER, gutterResObj);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::BAR_GRID_MARGIN, marginResObj);
}

void JSTabs::SetAnimateMode(const JSCallbackInfo& info)
{
    JSRef<JSVal> args = info[0];
    if (!args->IsNumber()) {
        TabsModel::GetInstance()->SetAnimateMode(TabAnimateMode::CONTENT_FIRST);
        return;
    }
    uint32_t value = args->ToNumber<uint32_t>();
    if (value >= static_cast<uint32_t>(TabAnimateMode::MAX_VALUE)) {
        TabsModel::GetInstance()->SetAnimateMode(TabAnimateMode::CONTENT_FIRST);
        return;
    }
    TabsModel::GetInstance()->SetAnimateMode(static_cast<TabAnimateMode>(value));
}

void JSTabs::SetEdgeEffect(const JSCallbackInfo& info)
{
    auto edgeEffect = EdgeEffect::SPRING;
    if (info.Length() > 0) {
        edgeEffect = JSScrollable::ParseEdgeEffect(info[0], EdgeEffect::SPRING);
    }
    TabsModel::GetInstance()->SetEdgeEffect(edgeEffect);
}

void JSTabs::SetBarBackgroundEffect(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    EffectOption option;
    RefPtr<ResourceObject> colorStrObj;
    RefPtr<ResourceObject> inactiveColorStrObj;
    if (info[0]->IsObject()) {
        JSRef<JSObject> jsOption = JSRef<JSObject>::Cast(info[0]);
        ParseEffectOption(jsOption, option);
        if (SystemProperties::ConfigChangePerform()) {
            ParseJsColor(jsOption->GetProperty("color"), option.color, colorStrObj);
            ParseJsColor(jsOption->GetProperty("inactiveColor"), option.inactiveColor, inactiveColorStrObj);
        }
    }
    TabsModel::GetInstance()->SetBarBackgroundEffect(option);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::COLOR, colorStrObj);
    TabsModel::GetInstance()->CreateWithResourceObj(TabJsResType::INACTIVE_COLOR, inactiveColorStrObj);
}

void JSTabs::SetPageFlipMode(const JSCallbackInfo& info)
{
    // default value
    int32_t value = 0;
    if (info.Length() < 1 || !info[0]->IsNumber()) {
        TabsModel::GetInstance()->SetPageFlipMode(value);
        return;
    }
    JSViewAbstract::ParseJsInt32(info[0], value);
    TabsModel::GetInstance()->SetPageFlipMode(value);
}

void JSTabs::SetBarModifier(const JSCallbackInfo& info, const JsiRef<JsiValue>& jsValue)
{
    if (!jsValue->IsObject()) {
        return;
    }
    JSRef<JSObject> obj = JSRef<JSObject>::Cast(jsValue);
    JSRef<JSVal> val = obj->GetProperty("barModifier");
    if (!val->IsObject()) {
        return;
    }
    auto vm = info.GetVm();
    auto globalObj = JSNApi::GetGlobalObject(vm);
    auto globalFunc = globalObj->Get(vm, panda::StringRef::NewFromUtf8(vm, "applyCommonModifierToNode"));
    if (globalFunc->IsFunction(vm)) {
        panda::Local<panda::FunctionRef> funcRef = globalFunc;
        auto func = panda::CopyableGlobal(vm, funcRef);
        auto tabsNode = AceType::DynamicCast<NG::TabsNode>(NG::ViewStackProcessor::GetInstance()->GetMainFrameNode());
        CHECK_NULL_VOID(tabsNode);
        auto tabBarNode = AceType::DynamicCast<NG::FrameNode>(tabsNode->GetTabBar());
        CHECK_NULL_VOID(tabBarNode);
        panda::Local<panda::JSValueRef> params[PARAM_COUNT] = { val->GetLocalHandle(),
            panda::NativePointerRef::New(vm, AceType::RawPtr(tabBarNode)) };
        func->Call(vm, func.ToLocal(), params, PARAM_COUNT);
    }
}

void JSTabs::SetCachedMaxCount(const JSCallbackInfo& info)
{
    if (info.Length() <= 1) {
        return;
    }

    std::optional<int32_t> cachedMaxCount;
    if (info[0]->IsNumber()) {
        auto count = info[0]->ToNumber<int32_t>();
        if (count >= 0) {
            cachedMaxCount = count;
        }
    }
    auto cacheMode = TabsCacheMode::CACHE_BOTH_SIDE;
    if (info[1]->IsNumber()) {
        auto mode = info[1]->ToNumber<int32_t>();
        if (mode >= static_cast<int32_t>(TabsCacheMode::CACHE_BOTH_SIDE) &&
            mode <= static_cast<int32_t>(TabsCacheMode::CACHE_LATEST_SWITCHED)) {
            cacheMode = static_cast<TabsCacheMode>(mode);
        }
    }
    TabsModel::GetInstance()->SetCachedMaxCount(cachedMaxCount, cacheMode);
}

void JSTabs::JSBind(BindingTarget globalObj)
{
    JsTabContentTransitionProxy::JSBind(globalObj);
    JSClass<JSTabs>::Declare("Tabs");
    JSClass<JSTabs>::StaticMethod("create", &JSTabs::Create);
    JSClass<JSTabs>::StaticMethod("pop", &JSTabs::Pop);
    JSClass<JSTabs>::StaticMethod("vertical", &JSTabs::SetVertical);
    JSClass<JSTabs>::StaticMethod("barPosition", &JSTabs::SetBarPosition);
    JSClass<JSTabs>::StaticMethod("barBackgroundBlurStyle", &JSTabs::SetBarBackgroundBlurStyle);
    JSClass<JSTabs>::StaticMethod("scrollable", &JSTabs::SetScrollable);
    JSClass<JSTabs>::StaticMethod("barMode", &JSTabs::SetBarMode);
    JSClass<JSTabs>::StaticMethod("barWidth", &JSTabs::SetBarWidth);
    JSClass<JSTabs>::StaticMethod("barHeight", &JSTabs::SetBarHeight);
    JSClass<JSTabs>::StaticMethod("width", &JSTabs::SetWidth);
    JSClass<JSTabs>::StaticMethod("height", &JSTabs::SetHeight);
    JSClass<JSTabs>::StaticMethod("index", &JSTabs::SetIndex);
    JSClass<JSTabs>::StaticMethod("animationCurve", &JSTabs::SetAnimationCurve);
    JSClass<JSTabs>::StaticMethod("animationDuration", &JSTabs::SetAnimationDuration);
    JSClass<JSTabs>::StaticMethod("divider", &JSTabs::SetDivider);
    JSClass<JSTabs>::StaticMethod("onAttach", &JSInteractableView::JsOnAttach);
    JSClass<JSTabs>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSTabs>::StaticMethod("onDetach", &JSInteractableView::JsOnDetach);
    JSClass<JSTabs>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSTabs>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSTabs>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSTabs>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSTabs>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSTabs>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSTabs>::StaticMethod("remoteMessage", &JSInteractableView::JsCommonRemoteMessage);
    JSClass<JSTabs>::StaticMethod("fadingEdge", &JSTabs::SetFadingEdge);
    JSClass<JSTabs>::StaticMethod("barOverlap", &JSTabs::SetBarOverlap);
    JSClass<JSTabs>::StaticMethod("barBackgroundColor", &JSTabs::SetBarBackgroundColor);
    JSClass<JSTabs>::StaticMethod("clip", &JSTabs::SetClip);
    JSClass<JSTabs>::StaticMethod("barGridAlign", &JSTabs::SetBarGridAlign);
    JSClass<JSTabs>::StaticMethod("animationMode", &JSTabs::SetAnimateMode);
    JSClass<JSTabs>::StaticMethod("edgeEffect", &JSTabs::SetEdgeEffect);
    JSClass<JSTabs>::StaticMethod("barBackgroundEffect", &JSTabs::SetBarBackgroundEffect);
    JSClass<JSTabs>::StaticMethod("pageFlipMode", &JSTabs::SetPageFlipMode);
    JSClass<JSTabs>::StaticMethod("cachedMaxCount", &JSTabs::SetCachedMaxCount);

    JSClass<JSTabs>::InheritAndBind<JSContainerBase>(globalObj);
}

} // namespace OHOS::Ace::Framework

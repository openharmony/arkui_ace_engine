/*
 * Copyright (c) 2021-2024 Huawei Device Co., Ltd.
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

#include "bridge/declarative_frontend/jsview/js_scroller.h"

#include "base/geometry/axis.h"
#include "base/utils/linear_map.h"
#include "base/utils/utils.h"
#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_view_common_def.h"
#include "core/animation/curves.h"
#include "core/common/container.h"
#include "core/components/common/layout/align_declaration.h"

namespace OHOS::Ace::Framework {
namespace {

constexpr AlignDeclaration::Edge EDGE_TABLE[] = {
    AlignDeclaration::Edge::TOP,
    AlignDeclaration::Edge::CENTER,
    AlignDeclaration::Edge::BOTTOM,
    AlignDeclaration::Edge::BASELINE,
    AlignDeclaration::Edge::START,
    AlignDeclaration::Edge::MIDDLE,
    AlignDeclaration::Edge::END,
};

// corresponding to EDGE_TABLE[]
constexpr ScrollEdgeType EDGE_TYPE_TABLE[] = { ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM, ScrollEdgeType::SCROLL_NONE, ScrollEdgeType::SCROLL_TOP, ScrollEdgeType::SCROLL_NONE,
    ScrollEdgeType::SCROLL_BOTTOM };

const LinearMapNode<RefPtr<Curve>> CURVE_MAP[] = {
    { "ease", Curves::EASE },
    { "ease-in", Curves::EASE_IN },
    { "ease-in-out", Curves::EASE_IN_OUT },
    { "ease-out", Curves::EASE_OUT },
    { "friction", Curves::FRICTION },
    { "linear", Curves::LINEAR },
};

static constexpr int ARGS_LENGTH = 2;
constexpr double DEFAULT_DURATION = 1000.0;
constexpr ScrollAlign ALIGN_TABLE[] = {
    ScrollAlign::START,
    ScrollAlign::CENTER,
    ScrollAlign::END,
    ScrollAlign::AUTO,
};

const std::regex DIMENSION_REGEX(R"(^[-+]?\d+(?:\.\d+)?(?:px|vp|fp|lpx)?$)", std::regex::icase);
} // namespace

void JSScroller::JSBind(BindingTarget globalObj)
{
    JSClass<JSScroller>::Declare("Scroller");
    JSClass<JSScroller>::CustomMethod("scrollTo", &JSScroller::ScrollTo);
    JSClass<JSScroller>::CustomMethod("scrollEdge", &JSScroller::ScrollEdge);
    JSClass<JSScroller>::CustomMethod("fling", &JSScroller::Fling);
    JSClass<JSScroller>::CustomMethod("scrollPage", &JSScroller::ScrollPage);
    JSClass<JSScroller>::CustomMethod("currentOffset", &JSScroller::CurrentOffset);
    JSClass<JSScroller>::CustomMethod("scrollToIndex", &JSScroller::ScrollToIndex);
    JSClass<JSScroller>::CustomMethod("scrollBy", &JSScroller::ScrollBy);
    JSClass<JSScroller>::CustomMethod("isAtEnd", &JSScroller::IsAtEnd);
    JSClass<JSScroller>::CustomMethod("getItemRect", &JSScroller::GetItemRect);
    JSClass<JSScroller>::CustomMethod("getItemIndex", &JSScroller::GetItemIndex);
    JSClass<JSScroller>::Bind(globalObj, JSScroller::Constructor, JSScroller::Destructor);
}

void JSScroller::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSScroller>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSScroller::Destructor(JSScroller* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

JSRef<JSObject> JSScroller::CreateRectangle(const Rect& info)
{
    JSRef<JSObject> rectObj = JSRef<JSObject>::New();
    rectObj->SetProperty<double>("x", info.Left());
    rectObj->SetProperty<double>("y", info.Top());
    rectObj->SetProperty<double>("width", info.Width());
    rectObj->SetProperty<double>("height", info.Height());
    return rectObj;
}

void JSScroller::ScrollTo(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    Dimension xOffset;
    Dimension yOffset;
    auto xOffsetStr = obj->GetProperty("xOffset");
    auto yOffsetStr = obj->GetProperty("yOffset");
    if (!std::regex_match(xOffsetStr->ToString(), DIMENSION_REGEX) ||
        !std::regex_match(yOffsetStr->ToString(), DIMENSION_REGEX) || !ConvertFromJSValue(xOffsetStr, xOffset) ||
        !ConvertFromJSValue(yOffsetStr, yOffset)) {
        return;
    }

    double duration = 0.0;
    bool smooth = false;
    bool canOverScroll = false;
    RefPtr<Curve> curve = Curves::EASE;
    auto animationValue = obj->GetProperty("animation");
    if (animationValue->IsObject()) {
        auto animationObj = JSRef<JSObject>::Cast(animationValue);
        auto curveArgs = animationObj->GetProperty("curve");
        bool hasDuration = true;
        if (!ConvertFromJSValue(animationObj->GetProperty("duration"), duration) || Negative(duration)) {
            duration = DEFAULT_DURATION;
            hasDuration = false;
        }
        bool hasCurve = ParseCurveParams(curve, curveArgs);
        bool hasCanOverScroll =
            ConvertFromJSValue(animationObj->GetProperty("canOverScroll"), canOverScroll) ? true : false;
        smooth = !hasDuration && !hasCurve && !hasCanOverScroll ? true : false;
    } else if (animationValue->IsBoolean()) {
        smooth = animationValue->ToBoolean();
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    ContainerScope scope(instanceId_);
    auto direction = scrollController->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    scrollController->AnimateTo(position, static_cast<float>(duration), curve, smooth, canOverScroll);
}

bool JSScroller::ParseCurveParams(RefPtr<Curve>& curve, const JSRef<JSVal>& jsValue)
{
    std::string curveName;
    if (ConvertFromJSValue(jsValue, curveName)) {
        auto index = BinarySearchFindIndex(CURVE_MAP, ArraySize(CURVE_MAP), curveName.c_str());
        if (index >= 0) {
            curve = CURVE_MAP[index].value;
            return true;
        }
    } else if (jsValue->IsObject()) {
        JSRef<JSVal> curveString = JSRef<JSObject>::Cast(jsValue)->GetProperty("__curveString");
        if (curveString->IsString()) {
            curve = CreateCurve(curveString->ToString());
            return true;
        }
    }
    return false;
}

void JSScroller::ScrollEdge(const JSCallbackInfo& args)
{
    AlignDeclaration::Edge edge = AlignDeclaration::Edge::AUTO;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], EDGE_TABLE, edge)) {
        return;
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    ScrollEdgeType edgeType = EDGE_TYPE_TABLE[static_cast<int32_t>(edge)];
    ContainerScope scope(instanceId_);

    if (args.Length() > 1 && args[1]->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(args[1]);
        float velocity = 0.0f;
        if (ConvertFromJSValue(obj->GetProperty("velocity"), velocity)) {
            if (velocity > 0) {
                velocity = Dimension(velocity, DimensionUnit::VP).ConvertToPx();
                scrollController->ScrollToEdge(edgeType, velocity);
                return;
            }
        }
    }
    scrollController->ScrollToEdge(edgeType, true);
}

void JSScroller::Fling(const JSCallbackInfo& args)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }
    double flingVelocity = 0.0;
    if (!args[0]->IsNumber()) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "The parameter check failed.");
        return;
    }
    flingVelocity = args[0]->ToNumber<double>();
    if (NearZero(flingVelocity)) {
        return;
    }
    ContainerScope scope(instanceId_);
    flingVelocity = Dimension(flingVelocity, DimensionUnit::VP).ConvertToPx();
    scrollController->Fling(flingVelocity);
}

void JSScroller::ScrollToIndex(const JSCallbackInfo& args)
{
    int32_t index = 0;
    bool smooth = false;
    ScrollAlign align = ScrollAlign::NONE;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], index) || index < 0) {
        return;
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    // 2: parameters count, 1: parameter index
    auto smoothArg = args[1];
    if (args.Length() >= 2 && smoothArg->IsBoolean()) {
        smooth = smoothArg->ToBoolean();
    }
    // 3: parameters count, 2: parameter index
    if (args.Length() >= 3) {
        ConvertFromJSValue(args[2], ALIGN_TABLE, align);
    }

    // 4: parameters count, 3: parameter index
    std::optional<float> extraOffset = std::nullopt;
    auto optionArg = args[3];
    if (args.Length() == 4 && optionArg->IsObject()) {
        auto obj = JSRef<JSObject>::Cast(optionArg);
        CalcDimension offset;
        if (JSViewAbstract::ParseLengthMetricsToDimension(obj->GetProperty("extraOffset"), offset)) {
            auto offsetPx = offset.ConvertToPx();
            if (!std::isnan(offsetPx)) {
                extraOffset = offsetPx;
            }
        }
    }
    ContainerScope scope(instanceId_);
    scrollController->ScrollToIndex(index, smooth, align, extraOffset);
}

void JSScroller::ScrollPage(const JSCallbackInfo& args)
{
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    auto obj = JSRef<JSObject>::Cast(args[0]);
    bool next = true;
    if (!ConvertFromJSValue(obj->GetProperty("next"), next)) {
        return;
    }
    bool smooth = false;
    auto smoothValue = obj->GetProperty("animation");
    if (smoothValue->IsBoolean()) {
        smooth = smoothValue->ToBoolean();
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    ContainerScope scope(instanceId_);
    scrollController->ScrollPage(!next, smooth);
}

void JSScroller::CurrentOffset(const JSCallbackInfo& args)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    auto retObj = JSRef<JSObject>::New();
    ContainerScope scope(instanceId_);
    auto offset = scrollController->GetCurrentOffset();
    retObj->SetProperty("xOffset", offset.GetX());
    retObj->SetProperty("yOffset", offset.GetY());
    args.SetReturnValue(retObj);
}

void JSScroller::ScrollBy(const JSCallbackInfo& args)
{
    if (args.Length() < 2) {
        return;
    }

    Dimension xOffset;
    Dimension yOffset;
    if (!ConvertFromJSValue(args[0], xOffset) ||
        !ConvertFromJSValue(args[1], yOffset)) {
        return;
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }

    ContainerScope scope(instanceId_);
    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            if (xOffset.Unit() == DimensionUnit::PERCENT) {
                deltaX = 0.0;
            } else {
                deltaX = context->NormalizeToPx(xOffset);
            }
            if (yOffset.Unit() == DimensionUnit::PERCENT) {
                deltaY = 0.0;
            } else {
                deltaY = context->NormalizeToPx(yOffset);
            }
        }
    }
    scrollController->ScrollBy(deltaX, deltaY, false);
}

void JSScroller::IsAtEnd(const JSCallbackInfo& args)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    ContainerScope scope(instanceId_);
    bool isAtEnd = scrollController->IsAtEnd();
    auto retVal = JSRef<JSVal>::Make(ToJSValue(isAtEnd));
    args.SetReturnValue(retVal);
}

void JSScroller::GetItemRect(const JSCallbackInfo& args)
{
    int32_t index = -1;
    if (args.Length() != 1 || !ConvertFromJSValue(args[0], index)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (scrollController) {
        ContainerScope scope(instanceId_);
        auto rectObj = CreateRectangle(scrollController->GetItemRect(index));
        JSRef<JSVal> rect = JSRef<JSObject>::Cast(rectObj);
        args.SetReturnValue(rect);
    } else {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
    }
}

void JSScroller::GetItemIndex(const JSCallbackInfo& args)
{
    if (args.Length() != ARGS_LENGTH) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter length failed.");
        return;
    }

    Dimension xOffset;
    Dimension yOffset;
    if (!ConvertFromJSValue(args[0], xOffset) ||
        !ConvertFromJSValue(args[1], yOffset)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    ContainerScope scope(instanceId_);
    auto deltaX = xOffset.Value();
    auto deltaY = yOffset.Value();
    auto container = Container::Current();
    if (container) {
        auto context = container->GetPipelineContext();
        if (context) {
            deltaX = context->NormalizeToPx(xOffset);
            deltaY = context->NormalizeToPx(yOffset);
        }
    }
    int32_t itemIndex = scrollController->GetItemIndex(deltaX, deltaY);
    auto retVal = JSRef<JSVal>::Make(ToJSValue(itemIndex));
    args.SetReturnValue(retVal);

    return;
}
} // namespace OHOS::Ace::Framework

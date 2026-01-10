/*
 * Copyright (c) 2021-2026 Huawei Device Co., Ltd.
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
#include "bridge/declarative_frontend/jsview/js_scroller_binding.h"

#include "base/geometry/axis.h"
#include "base/log/event_report.h"
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

void JSScrollerBinding::JSBind(BindingTarget globalObj)
{
    JSClass<JSScroller>::Declare("Scroller");
    JSClass<JSScroller>::CustomMethod("scrollTo", &JSScrollerBinding::ScrollTo);
    JSClass<JSScroller>::CustomMethod("scrollEdge", &JSScrollerBinding::ScrollEdge);
    JSClass<JSScroller>::CustomMethod("fling", &JSScrollerBinding::Fling);
    JSClass<JSScroller>::CustomMethod("scrollPage", &JSScrollerBinding::ScrollPage);
    JSClass<JSScroller>::CustomMethod("currentOffset", &JSScrollerBinding::CurrentOffset);
    JSClass<JSScroller>::CustomMethod("offset", &JSScrollerBinding::Offset);
    JSClass<JSScroller>::CustomMethod("scrollToIndex", &JSScrollerBinding::ScrollToIndex);
    JSClass<JSScroller>::CustomMethod("scrollBy", &JSScrollerBinding::ScrollBy);
    JSClass<JSScroller>::CustomMethod("isAtEnd", &JSScrollerBinding::IsAtEnd);
    JSClass<JSScroller>::CustomMethod("getItemRect", &JSScrollerBinding::GetItemRect);
    JSClass<JSScroller>::CustomMethod("getItemIndex", &JSScrollerBinding::GetItemIndex);
    JSClass<JSScroller>::CustomMethod("contentSize", &JSScrollerBinding::ContentSize);
    JSClass<JSScroller>::Bind(globalObj, JSScrollerBinding::Constructor, JSScrollerBinding::Destructor);
}

void JSScrollerBinding::Constructor(const JSCallbackInfo& args)
{
    auto scroller = Referenced::MakeRefPtr<JSScroller>();
    scroller->IncRefCount();
    args.SetReturnValue(Referenced::RawPtr(scroller));
}

void JSScrollerBinding::Destructor(JSScroller* scroller)
{
    if (scroller != nullptr) {
        scroller->DecRefCount();
    }
}

panda::Local<panda::ObjectRef> JSScroller::CreateRectangle(const Rect& info)
{
    auto runtime = std::static_pointer_cast<ArkJSRuntime>(JsiDeclarativeEngineInstance::GetCurrentRuntime());
    if (!runtime) {
        return panda::Local<panda::ObjectRef>();
    }
    auto* vm = runtime->GetEcmaVm();
    panda::Local<panda::ObjectRef> rectObj = panda::ObjectRef::New(vm);
    auto xRef = panda::StringRef::NewFromUtf8(vm, "x");
    rectObj->Set(vm, xRef, panda::NumberRef::New(vm, info.Left()));

    auto yRef = panda::StringRef::NewFromUtf8(vm, "y");
    rectObj->Set(vm, yRef, panda::NumberRef::New(vm, info.Top()));

    auto widthRef = panda::StringRef::NewFromUtf8(vm, "width");
    rectObj->Set(vm, widthRef, panda::NumberRef::New(vm, info.Width()));

    auto heightRef = panda::StringRef::NewFromUtf8(vm, "height");
    rectObj->Set(vm, heightRef, panda::NumberRef::New(vm, info.Height()));

    return rectObj;
}

void JSScrollerBinding::ScrollTo(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    if (args.Length() < 1 || !args[0]->IsObject()) {
        return;
    }

    JSRef<JSObject> obj = JSRef<JSObject>::Cast(args[0]);
    Dimension xOffset;
    Dimension yOffset;
    auto xOffsetStr = obj->GetProperty("xOffset");
    auto yOffsetStr = obj->GetProperty("yOffset");
    // The IsString judgment is omitted here to prevent non-numeric and non-string values from being passed in,
    // which could result in parsing as NaN.
    auto convertFail = (!std::regex_match(xOffsetStr->ToString(), DIMENSION_REGEX)) ||
                       (!std::regex_match(yOffsetStr->ToString(), DIMENSION_REGEX)) ||
                       !ConvertFromJSValue(xOffsetStr, xOffset) || !ConvertFromJSValue(yOffsetStr, yOffset);
    if (convertFail) {
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
        bool hasCanOverScroll = ConvertFromJSValue(animationObj->GetProperty("canOverScroll"), canOverScroll);
        smooth = !hasDuration && !hasCurve && !hasCanOverScroll;
    } else if (animationValue->IsBoolean()) {
        smooth = animationValue->ToBoolean();
    }
    auto optionCanOverScroll = obj->GetProperty("canOverScroll");
    bool canStayOverScroll = optionCanOverScroll->IsBoolean() ? optionCanOverScroll->ToBoolean() : false;
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
    ContainerScope scope(jsScroller->GetInstanceId());
    auto direction = scrollController->GetScrollDirection();
    if (direction == Axis::FREE &&
        scrollController->FreeScrollTo({ .xOffset = xOffset,
            .yOffset = yOffset,
            .duration = static_cast<float>(animationValue->IsBoolean() ? DEFAULT_DURATION : duration),
            .curve = curve,
            .smooth = (animationValue->IsBoolean() && smooth) || animationValue->IsObject(),
            .canOverScroll = canStayOverScroll })) {
        return;
    }
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    scrollController->SetCanStayOverScroll(canStayOverScroll);
    scrollController->AnimateTo(position, static_cast<float>(duration), curve, smooth, canOverScroll);
}

bool JSScrollerBinding::ParseCurveParams(RefPtr<Curve>& curve, const JSRef<JSVal>& jsValue)
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

void JSScrollerBinding::ScrollEdge(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    AlignDeclaration::Edge edge = AlignDeclaration::Edge::AUTO;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], EDGE_TABLE, edge)) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
    ScrollEdgeType edgeType = EDGE_TYPE_TABLE[static_cast<int32_t>(edge)];
    if (scrollController->GetScrollDirection() == Axis::FREE) { // allow scrolling to left and right edges
        if (edge == AlignDeclaration::Edge::START) {
            edgeType = ScrollEdgeType::SCROLL_LEFT;
        } else if (edge == AlignDeclaration::Edge::END) {
            edgeType = ScrollEdgeType::SCROLL_RIGHT;
        }
    }
    ContainerScope scope(jsScroller->GetInstanceId());

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

void JSScrollerBinding::Fling(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
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
    ContainerScope scope(jsScroller->GetInstanceId());
    flingVelocity = Dimension(flingVelocity, DimensionUnit::VP).ConvertToPx();
    scrollController->Fling(flingVelocity);
}

void JSScrollerBinding::ScrollToIndex(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    int32_t index = 0;
    bool smooth = false;
    ScrollAlign align = ScrollAlign::NONE;
    if (args.Length() < 1 || !ConvertFromJSValue(args[0], index) || index < 0) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
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
    ContainerScope scope(jsScroller->GetInstanceId());
    scrollController->ScrollToIndex(index, smooth, align, extraOffset);
}

void JSScrollerBinding::ScrollPage(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
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
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
    ContainerScope scope(jsScroller->GetInstanceId());
    scrollController->ScrollPage(!next, smooth);
}

void JSScrollerBinding::CurrentOffset(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
    auto retObj = JSRef<JSObject>::New();
    ContainerScope scope(jsScroller->GetInstanceId());
    auto offset = scrollController->GetCurrentOffset();
    retObj->SetProperty("xOffset", offset.GetX());
    retObj->SetProperty("yOffset", offset.GetY());
    args.SetReturnValue(retObj);
}

void JSScrollerBinding::Offset(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    if (!scrollController) {
        return;
    }
    auto retObj = JSRef<JSObject>::New();
    ContainerScope scope(jsScroller->GetInstanceId());
    auto offset = scrollController->GetCurrentOffset();
    retObj->SetProperty("xOffset", offset.GetX());
    retObj->SetProperty("yOffset", offset.GetY());
    args.SetReturnValue(retObj);
}

void JSScrollerBinding::ScrollBy(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    if (args.Length() < 2) {
        return;
    }

    Dimension xOffset;
    Dimension yOffset;
    if (!ConvertFromJSValue(args[0], xOffset) ||
        !ConvertFromJSValue(args[1], yOffset)) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);

    ContainerScope scope(jsScroller->GetInstanceId());
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

void JSScrollerBinding::IsAtEnd(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    CHECK_NULL_VOID(scrollController);
    ContainerScope scope(jsScroller->GetInstanceId());
    bool isAtEnd = scrollController->IsAtEnd();
    auto retVal = JSRef<JSVal>::Make(ToJSValue(isAtEnd));
    args.SetReturnValue(retVal);
}

void JSScrollerBinding::GetItemRect(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    int32_t index = -1;
    if (args.Length() != 1 || !ConvertFromJSValue(args[0], index)) {
        JSException::Throw(ERROR_CODE_PARAM_INVALID, "%s", "Input parameter check failed.");
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    if (scrollController) {
        ContainerScope scope(jsScroller->GetInstanceId());
        JSRef<JSObject> rectObj =
            JSRef<JSObject>::Make(jsScroller->CreateRectangle(scrollController->GetItemRect(index)));
        JSRef<JSVal> rect = JSRef<JSObject>::Cast(rectObj);
        args.SetReturnValue(rect);
    } else {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
    }
}

void JSScrollerBinding::GetItemIndex(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
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
    auto scrollController = jsScroller->GetController().Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }

    ContainerScope scope(jsScroller->GetInstanceId());
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

void JSScrollerBinding::ContentSize(const JSCallbackInfo& args)
{
    JSScroller* jsScroller = JSRef<JSObject>::Cast(args.This())->Unwrap<JSScroller>();
    if (jsScroller == nullptr) {
        return;
    }
    auto scrollController = jsScroller->GetController().Upgrade();
    if (!scrollController) {
        JSException::Throw(ERROR_CODE_NAMED_ROUTE_ERROR, "%s", "Controller not bound to component.");
        return;
    }
    auto retObj = JSRef<JSObject>::New();
    ContainerScope scope(jsScroller->GetInstanceId());
    auto contentSize = scrollController->ContentSize();
    retObj->SetProperty<double>("width", Dimension(contentSize.Width(), DimensionUnit::PX).ConvertToVp());
    retObj->SetProperty<double>("height", Dimension(contentSize.Height(), DimensionUnit::PX).ConvertToVp());
    args.SetReturnValue(retObj);
}
} // namespace OHOS::Ace::Framework

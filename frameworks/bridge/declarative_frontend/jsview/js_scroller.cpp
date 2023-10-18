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

constexpr Axis DIRECTION_TABLE[] = { Axis::VERTICAL, Axis::HORIZONTAL };

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
    JSClass<JSScroller>::CustomMethod("scrollPage", &JSScroller::ScrollPage);
    JSClass<JSScroller>::CustomMethod("currentOffset", &JSScroller::CurrentOffset);
    JSClass<JSScroller>::CustomMethod("scrollToIndex", &JSScroller::ScrollToIndex);
    JSClass<JSScroller>::CustomMethod("scrollBy", &JSScroller::ScrollBy);
    JSClass<JSScroller>::CustomMethod("isAtEnd", &JSScroller::IsAtEnd);
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
    RefPtr<Curve> curve = Curves::EASE;
    auto animationValue = obj->GetProperty("animation");
    if (animationValue->IsObject()) {
        auto animationObj = JSRef<JSObject>::Cast(animationValue);
        if (!ConvertFromJSValue(animationObj->GetProperty("duration"), duration) || NonPositive(duration)) {
            duration = DEFAULT_DURATION;
        }

        auto curveArgs = animationObj->GetProperty("curve");
        ParseCurveParams(curve, curveArgs);
    } else if (animationValue->IsBoolean()) {
        smooth = animationValue->ToBoolean();
    }
    TAG_LOGD(AceLogTag::ACE_SCROLL, "ScrollTo xOffset is %lf, yOffset is %lf, duration is %lf",
        xOffset.Value(), yOffset.Value(), duration);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    auto direction = scrollController->GetScrollDirection();
    auto position = direction == Axis::VERTICAL ? yOffset : xOffset;
    scrollController->AnimateTo(position, static_cast<float>(duration), curve, smooth);
}

void JSScroller::ParseCurveParams(RefPtr<Curve>& curve, const JSRef<JSVal>& jsValue)
{
    std::string curveName;
    if (ConvertFromJSValue(jsValue, curveName)) {
        auto index = BinarySearchFindIndex(CURVE_MAP, ArraySize(CURVE_MAP), curveName.c_str());
        if (index >= 0) {
            curve = CURVE_MAP[index].value;
        }
    } else if (jsValue->IsObject()) {
        auto icurveArgs = JsonUtil::ParseJsonString(jsValue->ToString());
        if (icurveArgs->IsObject()) {
            auto curveString = icurveArgs->GetValue("__curveString");
            curve = CreateCurve(curveString->GetString());
        }
    }
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
    TAG_LOGD(AceLogTag::ACE_SCROLL, "Scroll edge is %{public}d", static_cast<int32_t>(edge));
    ScrollEdgeType edgeType = EDGE_TYPE_TABLE[static_cast<int32_t>(edge)];
    scrollController->ScrollToEdge(edgeType, true);
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
    // 2：parameters count, 1: parameter index
    if (args.Length() >= 2 && args[1]->IsBoolean()) {
        smooth = args[1]->ToBoolean();
    }
    // 3：parameters count, 2: parameter index
    if (args.Length() == 3) {
        ConvertFromJSValue(args[2], ALIGN_TABLE, align);
    }
    scrollController->JumpTo(index, smooth, align, SCROLL_FROM_JUMP);
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

    Axis direction = Axis::NONE;
    ConvertFromJSValue(obj->GetProperty("direction"), DIRECTION_TABLE, direction);
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    TAG_LOGD(AceLogTag::ACE_SCROLL, "ScrollPage next is %{public}s, direction is %{public}d",
        next ? "true" : "false", static_cast<int32_t>(direction));
    scrollController->ScrollPage(!next, true);
}

void JSScroller::CurrentOffset(const JSCallbackInfo& args)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    auto retObj = JSRef<JSObject>::New();
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
    auto scrollController = controllerWeak_.Upgrade();
    if (scrollController) {
        scrollController->ScrollBy(deltaX, deltaY, false);
    }
}

void JSScroller::IsAtEnd(const JSCallbackInfo& args)
{
    auto scrollController = controllerWeak_.Upgrade();
    if (!scrollController) {
        return;
    }
    bool isAtEnd = scrollController->IsAtEnd();
    auto retVal = JSRef<JSVal>::Make(ToJSValue(isAtEnd));
    args.SetReturnValue(retVal);
}
} // namespace OHOS::Ace::Framework

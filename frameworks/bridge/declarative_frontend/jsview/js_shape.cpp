/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/jsview/js_shape.h"

#include "frameworks/bridge/declarative_frontend/view_stack_processor.h"

namespace OHOS::Ace::Framework {

void JSShape::Create()
{
    std::list<RefPtr<OHOS::Ace::Component>> componentChildren;
    RefPtr<OHOS::Ace::ShapeContainerComponent> component =
        AceType::MakeRefPtr<OHOS::Ace::ShapeContainerComponent>(componentChildren);
    ViewStackProcessor::GetInstance()->Push(component);
    JSInteractableView::SetFocusable(true);
    InitBox();
}

void JSShape::InitBox()
{
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    box->SetOverflow(Overflow::FORCE_CLIP);
    auto clipPath = AceType::MakeRefPtr<ClipPath>();
    clipPath->SetGeometryBoxType(GeometryBoxType::BORDER_BOX);
    box->SetClipPath(clipPath);
}

void JSShape::SetViewPort(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("shape is null");
        return;
    }
    if (info[0]->IsObject()) {
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> leftValue = obj->GetProperty("x");
        JSRef<JSVal> topValue = obj->GetProperty("y");
        JSRef<JSVal> widthValue = obj->GetProperty("width");
        JSRef<JSVal> heightValue = obj->GetProperty("height");
        AnimationOption option = stack->GetImplicitAnimationOption();
        ShapeViewBox viewBox;
        viewBox.SetLeft(ToDimension(leftValue), option);
        viewBox.SetTop(ToDimension(topValue), option);
        viewBox.SetWidth(ToDimension(widthValue), option);
        viewBox.SetHeight(ToDimension(heightValue), option);
        component->SetViewBox(viewBox);
    }
    info.SetReturnValue(info.This());
}

void JSShape::JsWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box->GetWidth().IsValid()) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetWidthFlag(true);
    }
}

void JSShape::JsHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    JSViewAbstract::JsHeight(info);
    auto box = ViewStackProcessor::GetInstance()->GetBoxComponent();
    if (!box->GetHeight().IsValid()) {
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetHeightFlag(true);
    }
}

void JSShape::SetStrokeDashArray(const JSCallbackInfo& info)
{
    if (info.Length() < 1 || !info[0]->IsArray()) {
        LOGE("info is not array");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }

    JSRef<JSArray> array = JSRef<JSArray>::Cast(info[0]);
    int32_t length = array->Length();
    if (length <= 0) {
        LOGE("info is invalid");
        return;
    }
    std::vector<Dimension> dashArray;
    for (int32_t i = 0; i < length; i++) {
        JSRef<JSVal> value = array->GetValueAt(i);
        dashArray.emplace_back(ToDimension(value));
    }
    // if odd,add twice
    if ((length & 1)) {
        for (int32_t i = 0; i < length; i++) {
            JSRef<JSVal> value = array->GetValueAt(i);
            dashArray.emplace_back(ToDimension(value));
        }
    }
    component->SetStrokeDashArray(dashArray);
    info.SetReturnValue(info.This());
}

void JSShape::SetStroke(const std::string& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStroke(Color::FromString(color), option);
    }
}

void JSShape::SetFill(const std::string& color)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("component is null");
        return;
    }
    AnimationOption option = stack->GetImplicitAnimationOption();
    if (color == "none") {
        component->SetFill(Color::TRANSPARENT, option);
    } else {
        component->SetFill(Color::FromString(color), option);
    }
}

void JSShape::SetStrokeDashOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The arg is wrong, it is supposed to have at least 1 argument");
        return;
    }

    if (!info[0]->IsNumber() && !info[0]->IsString()) {
        LOGE("arg is not Number or String.");
        return;
    }
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeDashOffset(ToDimension(info[0]), option);
    }
}

void JSShape::SetStrokeLineCap(int lineCap)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineCapStyle::SQUARE) == lineCap) {
        component->SetStrokeLineCap(LineCapStyle::SQUARE);
    } else if (static_cast<int>(LineCapStyle::ROUND) == lineCap) {
        component->SetStrokeLineCap(LineCapStyle::ROUND);
    } else {
        component->SetStrokeLineCap(LineCapStyle::BUTT);
    }
}

void JSShape::SetStrokeLineJoin(int lineJoin)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    if (static_cast<int>(LineJoinStyle::BEVEL) == lineJoin) {
        component->SetStrokeLineJoin(LineJoinStyle::BEVEL);
    } else if (static_cast<int>(LineJoinStyle::ROUND) == lineJoin) {
        component->SetStrokeLineJoin(LineJoinStyle::ROUND);
    } else {
        component->SetStrokeLineJoin(LineJoinStyle::MITER);
    }
}

void JSShape::SetStrokeMiterLimit(const std::string& strokeMiterLimit)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    double miterLimit = StringUtils::StringToDouble(strokeMiterLimit);
    if (GreatOrEqual(miterLimit, 1.0)) {
        component->SetStrokeMiterLimit(miterLimit);
    }
}

void JSShape::SetStrokeOpacity(const std::string& strokeOpacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeOpacity(StringUtils::StringToDouble(strokeOpacity), option);
    }
}

void JSShape::SetFillOpacity(const std::string& fillOpacity)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetFillOpacity(StringUtils::StringToDouble(fillOpacity), option);
    }
}

void JSShape::SetStrokeWidth(const std::string& strokeWidth)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (!component) {
        LOGE("ShapeComponent is null");
        return;
    }
    Dimension lineWidth = StringUtils::StringToDimension(strokeWidth, true);
    if (GreatOrEqual(lineWidth.Value(), 0.0)) {
        AnimationOption option = stack->GetImplicitAnimationOption();
        component->SetStrokeWidth(lineWidth, option);
    }
}

void JSShape::SetAntiAlias(bool antiAlias)
{
    auto stack = ViewStackProcessor::GetInstance();
    auto component = AceType::DynamicCast<OHOS::Ace::ShapeContainerComponent>(stack->GetMainComponent());
    if (component) {
        component->SetAntiAlias(antiAlias);
    }
}

void JSShape::JSBind(BindingTarget globalObj)
{
    JSClass<JSShape>::Declare("Shape");
    JSClass<JSShape>::StaticMethod("create", &JSShape::Create);
    JSClass<JSShape>::StaticMethod("viewPort", &JSShape::SetViewPort);

    JSClass<JSShape>::StaticMethod("width", &JSShape::JsWidth);
    JSClass<JSShape>::StaticMethod("height", &JSShape::JsHeight);

    JSClass<JSShape>::StaticMethod("stroke", &JSShape::SetStroke);
    JSClass<JSShape>::StaticMethod("fill", &JSShape::SetFill);
    JSClass<JSShape>::StaticMethod("strokeDashOffset", &JSShape::SetStrokeDashOffset);
    JSClass<JSShape>::StaticMethod("strokeDashArray", &JSShape::SetStrokeDashArray);
    JSClass<JSShape>::StaticMethod("strokeLineCap", &JSShape::SetStrokeLineCap);
    JSClass<JSShape>::StaticMethod("strokeLineJoin", &JSShape::SetStrokeLineJoin);
    JSClass<JSShape>::StaticMethod("strokeMiterLimit", &JSShape::SetStrokeMiterLimit);
    JSClass<JSShape>::StaticMethod("strokeOpacity", &JSShape::SetStrokeOpacity);
    JSClass<JSShape>::StaticMethod("fillOpacity", &JSShape::SetFillOpacity);
    JSClass<JSShape>::StaticMethod("strokeWidth", &JSShape::SetStrokeWidth);
    JSClass<JSShape>::StaticMethod("antiAlias", &JSShape::SetAntiAlias);

    JSClass<JSShape>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSShape>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSShape>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSShape>::StaticMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSShape>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSShape>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSShape>::Inherit<JSContainerBase>();
    JSClass<JSShape>::Inherit<JSViewAbstract>();
    JSClass<JSShape>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework

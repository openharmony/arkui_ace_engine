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

#include "frameworks/bridge/declarative_frontend/jsview/js_divider.h"

#include "core/components/box/box_component.h"

namespace OHOS::Ace::Framework {

RefPtr<OHOS::Ace::Component> JSDivider::CreateSpecializedComponent()
{
    auto dividerComponent = AceType::MakeRefPtr<DividerComponent>();
    dividerComponent->SetVertical(isVertical_);
    dividerComponent->SetStrokeWidth(strokeWidth_);
    dividerComponent->SetLineCap(lineCap_);
    dividerComponent->SetDividerColor(dividerColor_);
    return std::move(dividerComponent);
}

void JSDivider::SetVertical(bool isVertical)
{
    isVertical_ = isVertical;

    if (!boxComponent_) {
        boxComponent_ = AceType::MakeRefPtr<BoxComponent>();
    }

    if (isVertical_) {
        boxComponent_->SetFlex(BoxFlex::FLEX_Y);
    } else {
        boxComponent_->SetFlex(BoxFlex::FLEX_X);
    }
}

void JSDivider::SetLineCap(int lineCap)
{
    if (static_cast<int>(LineCap::SQUARE) == lineCap) {
        lineCap_ = LineCap::SQUARE;
    } else if (static_cast<int>(LineCap::ROUND) == lineCap) {
        lineCap_ = LineCap::ROUND;
    } else {
        // default linecap of divider
        lineCap_ = LineCap::BUTT;
    }
}

void JSDivider::SetDividerColor(const std::string& color)
{
    dividerColor_ = Color::FromString(color);
}

void JSDivider::SetStrokeWidth(const std::string& width)
{
    strokeWidth_ = StringUtils::StringToDimension(width, true);
}

#ifdef USE_QUICKJS_ENGINE
void JSDivider::MarkGC(JSRuntime* rt, JS_MarkFunc* markFunc)
{
    LOGD("JSDivider => markGC: Mark value for GC start");
    JSInteractableView::MarkGC(rt, markFunc);
    LOGD("JSDivider => markGC: Mark value for GC end");
}

void JSDivider::ReleaseRT(JSRuntime* rt)
{
    LOGD("JSDivider => release start");
    JSInteractableView::ReleaseRT(rt);
    LOGD("JSDivider => release divider");
    LOGD("JSDivider => release end");
}

void JSDivider::QjsDestructor(JSRuntime* rt, JSDivider* view)
{
    if (!view) {
        return;
    }

    view->ReleaseRT(rt);
    delete view;
    LOGD("JSDivider(qjs_destructor) end");
}

void JSDivider::QjsGcMark(JSRuntime* rt, JSValueConst val, JS_MarkFunc* markFunc)
{
    LOGD("JSDivider(qjs_gc_mark) start");

    JSDivider* view = Unwrap<JSDivider>(val);
    if (!view) {
        return;
    }

    view->MarkGC(rt, markFunc);
    LOGD("JSDivider(qjs_gc_mark) end");
}

#endif

void JSDivider::JSBind(BindingTarget globalObj)
{
    JSClass<JSDivider>::Declare("Divider");
    JSClass<JSDivider>::Inherit<JSViewAbstract>();

    MethodOptions opt = MethodOptions::RETURN_SELF;
    JSClass<JSDivider>::Method("color", &JSDivider::SetDividerColor, opt);
    JSClass<JSDivider>::Method("vertical", &JSDivider::SetVertical, opt);
    JSClass<JSDivider>::Method("strokeWidth", &JSDivider::SetStrokeWidth, opt);
    JSClass<JSDivider>::Method("lineCap", &JSDivider::SetLineCap, opt);
    JSClass<JSDivider>::CustomMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSDivider>::CustomMethod("onClick", &JSInteractableView::JsOnClick);
    JSClass<JSDivider>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework

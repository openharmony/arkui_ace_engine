/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "frameworks/bridge/declarative_frontend/style_string/js_span_object.h"

#include "bridge/declarative_frontend/engine/js_types.h"
#include "bridge/declarative_frontend/jsview/js_utils.h"
#include "core/components/text/text_theme.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::Framework {

void JSFontSpan::JSBind(BindingTarget globalObj)
{
    JSClass<JSFontSpan>::Declare("TextStyle");
    JSClass<JSFontSpan>::CustomProperty("fontColor", &JSFontSpan::GetFontColor, &JSFontSpan::SetFontColor);
    JSClass<JSFontSpan>::Bind(globalObj, JSFontSpan::Constructor, JSFontSpan::Destructor);
}

void JSFontSpan::Constructor(const JSCallbackInfo& args)
{
    auto fontSpan = Referenced::MakeRefPtr<JSFontSpan>();
    fontSpan->IncRefCount();

    RefPtr<FontSpan> span;
    if (args.Length() <= 0) {
        Font font;
        span = AceType::MakeRefPtr<FontSpan>(font);
    } else {
        span = JSFontSpan::ParseJsFontSpan(JSRef<JSObject>::Cast(args[0]));
    }
    fontSpan->fontSpan_ = span;
    args.SetReturnValue(Referenced::RawPtr(fontSpan));
}

void JSFontSpan::Destructor(JSFontSpan* fontSpan)
{
    if (fontSpan != nullptr) {
        fontSpan->DecRefCount();
    }
}

RefPtr<FontSpan> JSFontSpan::ParseJsFontSpan(const JSRef<JSObject>& obj)
{
    Font font;
    Color color;
    JSRef<JSVal> colorObj = JSRef<JSVal>::Cast(obj->GetProperty("fontColor"));
    if (!colorObj->IsNull() && JSViewAbstract::ParseJsColor(colorObj, color)) {
        font.fontColor = color;
    } else {
        auto context = PipelineBase::GetCurrentContextSafely();
        CHECK_NULL_RETURN(context, AceType::MakeRefPtr<FontSpan>(font));
        auto theme = context->GetTheme<TextTheme>();
        CHECK_NULL_RETURN(theme, AceType::MakeRefPtr<FontSpan>(font));
        font.fontColor = theme->GetTextStyle().GetTextColor();
    }
    return AceType::MakeRefPtr<FontSpan>(font);
}

void JSFontSpan::GetFontColor(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(fontSpan_);
    if (!fontSpan_->GetFont().fontColor.has_value()) {
        return;
    }
    auto ret = JSRef<JSVal>::Make(JSVal(ToJSValue(fontSpan_->GetFont().fontColor.value().ColorToString())));
    info.SetReturnValue(ret);
}

void JSFontSpan::SetFontColor(const JSCallbackInfo& info) {}

const RefPtr<FontSpan>& JSFontSpan::GetFontSpan()
{
    return fontSpan_;
}

void JSFontSpan::SetFontSpan(const RefPtr<FontSpan>& fontSpan)
{
    fontSpan_ = fontSpan;
}

// JSImageAttachment
void JSImageAttachment::Constructor(const JSCallbackInfo& args)
{

}

void JSImageAttachment::Destructor(JSImageAttachment* imageSpan)
{
    if (imageSpan != nullptr) {
        imageSpan->DecRefCount();
    }
}

void JSImageAttachment::JSBind(BindingTarget globalObj)
{
    JSClass<JSImageAttachment>::Declare("ImageAttachment ");
    JSClass<JSImageAttachment>::CustomProperty(
        "value", &JSImageAttachment::GetImageSrc, &JSImageAttachment::SetImageSrc);
    JSClass<JSImageAttachment>::CustomProperty(
        "size", &JSImageAttachment::GetImageSize, &JSImageAttachment::SetImageSize);
    JSClass<JSImageAttachment>::CustomProperty(
        "verticalAlign", &JSImageAttachment::GetImageSrc, &JSImageAttachment::SetImageSrc);
    JSClass<JSImageAttachment>::CustomProperty(
        "objectFit", &JSImageAttachment::GetImageVerticalAlign, &JSImageAttachment::SetImageVerticalAlign);
    JSClass<JSImageAttachment>::CustomProperty(
        "layoutStyle", &JSImageAttachment::GetImageObjectFit, &JSImageAttachment::SetImageObjectFit);
    JSClass<JSImageAttachment>::CustomProperty(
        "value", &JSImageAttachment::GetImageLayoutStyle, &JSImageAttachment::SetImageLayoutStyle);
    JSClass<JSImageAttachment>::Bind(globalObj, JSImageAttachment::Constructor, JSImageAttachment::Destructor);
}

RefPtr<ImageSpan> JSImageAttachment::ParseJsFontSpan(const JSRef<JSObject>& obj)
{
    return nullptr;
}

void JSImageAttachment::GetImageSrc(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageOptions = imageSpan_->GetImageSpanOptions();
    JSRef<JSVal> ret;
    if (imageOptions.image.has_value()) {
        ret = JSRef<JSVal>::Make(ToJSValue(imageOptions.image.value()));
    }
    if (imageOptions.imagePixelMap.has_value()) {
#ifdef PIXEL_MAP_SUPPORTED
        ret = ConvertPixmap(imageOptions.imagePixelMap.value());
#endif
    }
    info.SetReturnValue(ret);
}

void JSImageAttachment::GetImageSize(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->size.has_value()) {
        return;
    }
    JSRef<JSArray> imageSize = JSRef<JSArray>::New();
    imageSize->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(imageAttr->size->width)));
    imageSize->SetValueAt(0, JSRef<JSVal>::Make(ToJSValue(imageAttr->size->height)));
    info.SetReturnValue(imageSize);
}

void JSImageAttachment::GetImageVerticalAlign(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->verticalAlign.has_value()) {
        return;
    }
    // 涉及是否减一
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(imageAttr->verticalAlign)));
}

void JSImageAttachment::GetImageObjectFit(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value() || !imageAttr->objectFit.has_value()) {
        return;
    }
    info.SetReturnValue(JSRef<JSVal>::Make(ToJSValue(imageAttr->objectFit)));
}

void JSImageAttachment::GetImageLayoutStyle(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(imageSpan_);
    auto imageAttr = imageSpan_->GetImageAttribute();
    if (!imageAttr.has_value()) {
        return;
    }
    auto layoutStyle = JSRef<JSObject>::New();
    if (imageAttr->marginProp.has_value()) {
        layoutStyle->SetProperty<std::string>("margin", imageAttr->marginProp->ToString());
    }
    if (imageAttr->paddingProp.has_value()) {
        layoutStyle->SetProperty<std::string>("padding", imageAttr->paddingProp->ToString());
    }
    if (imageAttr->borderRadius.has_value()) {
        layoutStyle->SetProperty<std::string>("borderRadius", imageAttr->borderRadius->ToString());
    }
    info.SetReturnValue(layoutStyle);
}

const RefPtr<ImageSpan>& JSImageAttachment::GetImageSpan()
{
    return imageSpan_;
}

void JSImageAttachment::SetImageSpan(const RefPtr<ImageSpan>& imageSpan)
{
    imageSpan_ = imageSpan;
}
} // namespace OHOS::Ace::Framework
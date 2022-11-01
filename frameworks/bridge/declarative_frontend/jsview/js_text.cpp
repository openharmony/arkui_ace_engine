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

#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"

#include <sstream>
#include <string>
#include <vector>

#include "base/geometry/dimension.h"
#include "base/log/ace_scoring_log.h"
#include "base/log/ace_trace.h"
#include "base/utils/utils.h"
#include "bridge/common/utils/utils.h"
#include "bridge/declarative_frontend/engine/functions/js_click_function.h"
#include "bridge/declarative_frontend/engine/functions/js_drag_function.h"
#include "bridge/declarative_frontend/jsview/js_interactable_view.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"
#include "bridge/declarative_frontend/jsview/models/text_model_impl.h"
#include "bridge/declarative_frontend/view_stack_processor.h"
#include "core/common/container.h"
#include "core/components_ng/event/gesture_event_hub.h"
#include "core/components_ng/pattern/text/text_model.h"
#include "core/components_ng/pattern/text/text_model_ng.h"
#include "core/event/ace_event_handler.h"

namespace OHOS::Ace {

std::unique_ptr<TextModel> TextModel::instance_ = nullptr;

TextModel* TextModel::GetInstance()
{
    if (!instance_) {
#ifdef NG_BUILD
        instance_.reset(new NG::TextModelNG());
#else
        if (Container::IsCurrentUseNewPipeline()) {
            instance_.reset(new NG::TextModelNG());
        } else {
            instance_.reset(new Framework::TextModelImpl());
        }
#endif
    }
    return instance_.get();
}

} // namespace OHOS::Ace

namespace OHOS::Ace::Framework {
namespace {

const std::vector<TextCase> TEXT_CASES = { TextCase::NORMAL, TextCase::LOWERCASE, TextCase::UPPERCASE };
const std::vector<TextOverflow> TEXT_OVERFLOWS = { TextOverflow::CLIP, TextOverflow::ELLIPSIS, TextOverflow::NONE };
const std::vector<FontStyle> FONT_STYLES = { FontStyle::NORMAL, FontStyle::ITALIC };
const std::vector<TextAlign> TEXT_ALIGNS = { TextAlign::START, TextAlign::CENTER, TextAlign::END, TextAlign::LEFT,
    TextAlign::RIGHT, TextAlign::JUSTIFY };

}; // namespace

void JSText::SetWidth(const JSCallbackInfo& info)
{
    JSViewAbstract::JsWidth(info);
    TextModel::GetInstance()->OnSetWidth();
}

void JSText::SetHeight(const JSCallbackInfo& info)
{
    JSViewAbstract::JsHeight(info);
    TextModel::GetInstance()->OnSetHeight();
}

void JSText::SetFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    if (!fontSize.IsValid()) {
        LOGE("FontSize value is not valid");
        return;
    }
    TextModel::GetInstance()->SetFontSize(fontSize);
}

void JSText::SetFontWeight(const std::string& value)
{
    TextModel::GetInstance()->SetFontWeight(ConvertStrToFontWeight(value));
}

void JSText::SetTextColor(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Color textColor;
    if (!ParseJsColor(info[0], textColor)) {
        return;
    }
    TextModel::GetInstance()->SetTextColor(textColor);
}

void JSText::SetTextOverflow(const JSCallbackInfo& info)
{
    do {
        if (!info[0]->IsObject()) {
            LOGE("info[0] not is Object");
            break;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> overflowValue = obj->GetProperty("overflow");
        if (!overflowValue->IsNumber()) {
            LOGE("overflow value is not a number");
            break;
        }
        auto overflow = overflowValue->ToNumber<int32_t>();
        if (overflow < 0 || overflow >= static_cast<int32_t>(TEXT_OVERFLOWS.size())) {
            LOGE("Text: textOverflow(%{public}d) illegal value", overflow);
            break;
        }
        TextModel::GetInstance()->SetTextOverflow(TEXT_OVERFLOWS[overflow]);
    } while (false);

    info.SetReturnValue(info.This());
}

void JSText::SetMaxLines(int32_t value)
{
    TextModel::GetInstance()->SetMaxLines(value);
}

void JSText::SetFontStyle(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(FONT_STYLES.size())) {
        LOGE("Text fontStyle(%{public}d) illegal value", value);
        return;
    }
    TextModel::GetInstance()->SetItalicFontStyle(FONT_STYLES[value]);
}

void JSText::SetTextAlign(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_ALIGNS.size())) {
        LOGE("Text: TextAlign(%d) expected positive number", value);
        return;
    }
    TextModel::GetInstance()->SetTextAlign(TEXT_ALIGNS[value]);
}

void JSText::SetAlign(const JSCallbackInfo& info)
{
    JSViewAbstract::JsAlign(info);
    if (!info[0]->IsNumber()) {
        return;
    }
    TextModel::GetInstance()->OnSetAlign();
}

void JSText::SetLineHeight(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionFp(info[0], value)) {
        return;
    }
    TextModel::GetInstance()->SetLineHeight(value);
}

void JSText::SetFontFamily(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    std::vector<std::string> fontFamilies;
    if (!ParseJsFontFamilies(info[0], fontFamilies)) {
        LOGE("Parse FontFamilies failed");
        return;
    }
    TextModel::GetInstance()->SetFontFamily(fontFamilies);
}

void JSText::SetMinFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    TextModel::GetInstance()->SetAdaptMinFontSize(fontSize);
}

void JSText::SetMaxFontSize(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension fontSize;
    if (!ParseJsDimensionFp(info[0], fontSize)) {
        return;
    }
    TextModel::GetInstance()->SetAdaptMaxFontSize(fontSize);
}

void JSText::SetLetterSpacing(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionFp(info[0], value)) {
        return;
    }
    TextModel::GetInstance()->SetLetterSpacing(value);
}

void JSText::SetTextCase(int32_t value)
{
    if (value < 0 || value >= static_cast<int32_t>(TEXT_CASES.size())) {
        LOGE("Text textCase(%{public}d) illegal value", value);
        return;
    }
    TextModel::GetInstance()->SetTextCase(TEXT_CASES[value]);
}

void JSText::SetBaselineOffset(const JSCallbackInfo& info)
{
    if (info.Length() < 1) {
        LOGE("The argv is wrong, it is supposed to have at least 1 argument");
        return;
    }
    Dimension value;
    if (!ParseJsDimensionFp(info[0], value)) {
        return;
    }
    TextModel::GetInstance()->SetBaselineOffset(value);
}

void JSText::SetDecoration(const JSCallbackInfo& info)
{
    do {
        if (!info[0]->IsObject()) {
            LOGE("info[0] not is Object");
            break;
        }
        JSRef<JSObject> obj = JSRef<JSObject>::Cast(info[0]);
        JSRef<JSVal> typeValue = obj->GetProperty("type");
        JSRef<JSVal> colorValue = obj->GetProperty("color");

        std::optional<TextDecoration> textDecoration;
        if (typeValue->IsNumber()) {
            textDecoration = static_cast<TextDecoration>(typeValue->ToNumber<int32_t>());
        }
        std::optional<Color> colorVal;
        Color result;
        if (ParseJsColor(colorValue, result)) {
            colorVal = result;
        }

        if (textDecoration) {
            TextModel::GetInstance()->SetTextDecoration(textDecoration.value());
        }
        if (colorVal) {
            TextModel::GetInstance()->SetTextDecorationColor(colorVal.value());
        }
    } while (false);
    info.SetReturnValue(info.This());
}

void JSText::JsOnClick(const JSCallbackInfo& info)
{
    if (Container::IsCurrentUseNewPipeline()) {
        JSInteractableView::JsOnClick(info);
    } else {
#ifndef NG_BUILD
        if (info[0]->IsFunction()) {
            auto inspector = ViewStackProcessor::GetInstance()->GetInspectorComposedComponent();
            auto impl = inspector ? inspector->GetInspectorFunctionImpl() : nullptr;
            RefPtr<JsClickFunction> jsOnClickFunc = AceType::MakeRefPtr<JsClickFunction>(JSRef<JSFunc>::Cast(info[0]));
            auto onClickId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnClickFunc), impl](
                                 const BaseEventInfo* info) {
                JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
                LOGD("About to call onclick method on js");
                const auto* clickInfo = TypeInfoHelper::DynamicCast<ClickInfo>(info);
                auto newInfo = *clickInfo;
                if (impl) {
                    impl->UpdateEventInfo(newInfo);
                }
                ACE_SCORING_EVENT("Text.onClick");
                func->Execute(newInfo);
            };
            TextModel::GetInstance()->SetOnClick(std::move(onClickId));
        }
#endif
    }
}

void JSText::JsRemoteMessage(const JSCallbackInfo& info)
{
    JSInteractableView::JsCommonRemoteMessage(info);
    auto callback = JSInteractableView::GetRemoteMessageEventCallback(info);
    TextModel::GetInstance()->SetRemoteMessage(std::move(callback));
}

void JSText::Create(const JSCallbackInfo& info)
{
    std::string data;
    if (info.Length() > 0) {
        ParseJsString(info[0], data);
    }

    TextModel::GetInstance()->Create(data);
}

void JSText::SetCopyOption(const JSCallbackInfo& info)
{
    if (info.Length() == 0) {
        return;
    }
    auto copyOptions = CopyOptions::None;
    if (info[0]->IsNumber()) {
        auto emunNumber = info[0]->ToNumber<int>();
        copyOptions = static_cast<CopyOptions>(emunNumber);
    }
    TextModel::GetInstance()->SetCopyOption(copyOptions);
}

void JSText::JsOnDragStart(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    RefPtr<JsDragFunction> jsOnDragStartFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragStart = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragStartFunc)](
                           const RefPtr<DragEvent>& info, const std::string& extraParams) -> NG::DragDropBaseInfo {
        NG::DragDropBaseInfo itemInfo;
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx, itemInfo);

        auto ret = func->Execute(info, extraParams);
        if (!ret->IsObject()) {
            LOGE("builder param is not an object.");
            return itemInfo;
        }
        auto node = ParseDragNode(ret);
        if (node) {
            LOGI("use custom builder param.");
            itemInfo.node = node;
            return itemInfo;
        }

        auto builderObj = JSRef<JSObject>::Cast(ret);
#if defined(PIXEL_MAP_SUPPORTED)
        auto pixmap = builderObj->GetProperty("pixelMap");
        itemInfo.pixelMap = CreatePixelMapFromNapiValue(pixmap);
#endif
        auto extraInfo = builderObj->GetProperty("extraInfo");
        ParseJsString(extraInfo, itemInfo.extraInfo);
        node = ParseDragNode(builderObj->GetProperty("builder"));
        itemInfo.node = node;
        return itemInfo;
    };

    TextModel::GetInstance()->SetOnDragStart(std::move(onDragStart));
}

void JSText::JsOnDragEnter(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    RefPtr<JsDragFunction> jsOnDragEnterFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragEnterId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragEnterFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragEnter");
        func->Execute(info, extraParams);
    };
    TextModel::GetInstance()->SetOnDragEnter(std::move(onDragEnterId));
}

void JSText::JsOnDragMove(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    RefPtr<JsDragFunction> jsOnDragMoveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragMoveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragMoveFunc)](
                            const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragMove");
        func->Execute(info, extraParams);
    };
    TextModel::GetInstance()->SetOnDragMove(std::move(onDragMoveId));
}

void JSText::JsOnDragLeave(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    RefPtr<JsDragFunction> jsOnDragLeaveFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDragLeaveId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDragLeaveFunc)](
                             const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDragLeave");
        func->Execute(info, extraParams);
    };
    TextModel::GetInstance()->SetOnDragLeave(std::move(onDragLeaveId));
}

void JSText::JsOnDrop(const JSCallbackInfo& info)
{
    CHECK_NULL_VOID(info[0]->IsFunction());
    RefPtr<JsDragFunction> jsOnDropFunc = AceType::MakeRefPtr<JsDragFunction>(JSRef<JSFunc>::Cast(info[0]));
    auto onDropId = [execCtx = info.GetExecutionContext(), func = std::move(jsOnDropFunc)](
                        const RefPtr<DragEvent>& info, const std::string& extraParams) {
        JAVASCRIPT_EXECUTION_SCOPE_WITH_CHECK(execCtx);
        ACE_SCORING_EVENT("onDrop");
        func->Execute(info, extraParams);
    };
    TextModel::GetInstance()->SetOnDrop(std::move(onDropId));
}

void JSText::JsFocusable(const JSCallbackInfo& info)
{
    if (!info[0]->IsBoolean()) {
        LOGE("The info is wrong, it is supposed to be an boolean");
        return;
    }
    JSInteractableView::SetFocusable(info[0]->IsBoolean());
    JSInteractableView::SetFocusNode(false);
}

void JSText::JSBind(BindingTarget globalObj)
{
    JSClass<JSText>::Declare("Text");
    MethodOptions opt = MethodOptions::NONE;
    JSClass<JSText>::StaticMethod("create", &JSText::Create, opt);
    JSClass<JSText>::StaticMethod("width", &JSText::SetWidth);
    JSClass<JSText>::StaticMethod("height", &JSText::SetHeight);
    JSClass<JSText>::StaticMethod("fontColor", &JSText::SetTextColor, opt);
    JSClass<JSText>::StaticMethod("fontSize", &JSText::SetFontSize, opt);
    JSClass<JSText>::StaticMethod("fontWeight", &JSText::SetFontWeight, opt);
    JSClass<JSText>::StaticMethod("maxLines", &JSText::SetMaxLines, opt);
    JSClass<JSText>::StaticMethod("textOverflow", &JSText::SetTextOverflow, opt);
    JSClass<JSText>::StaticMethod("fontStyle", &JSText::SetFontStyle, opt);
    JSClass<JSText>::StaticMethod("align", &JSText::SetAlign, opt);
    JSClass<JSText>::StaticMethod("textAlign", &JSText::SetTextAlign, opt);
    JSClass<JSText>::StaticMethod("lineHeight", &JSText::SetLineHeight, opt);
    JSClass<JSText>::StaticMethod("fontFamily", &JSText::SetFontFamily, opt);
    JSClass<JSText>::StaticMethod("minFontSize", &JSText::SetMinFontSize, opt);
    JSClass<JSText>::StaticMethod("maxFontSize", &JSText::SetMaxFontSize, opt);
    JSClass<JSText>::StaticMethod("letterSpacing", &JSText::SetLetterSpacing, opt);
    JSClass<JSText>::StaticMethod("textCase", &JSText::SetTextCase, opt);
    JSClass<JSText>::StaticMethod("baselineOffset", &JSText::SetBaselineOffset, opt);
    JSClass<JSText>::StaticMethod("decoration", &JSText::SetDecoration);
    JSClass<JSText>::StaticMethod("onTouch", &JSInteractableView::JsOnTouch);
    JSClass<JSText>::StaticMethod("onHover", &JSInteractableView::JsOnHover);
    JSClass<JSText>::StaticMethod("onKeyEvent", &JSInteractableView::JsOnKey);
    JSClass<JSText>::StaticMethod("onDeleteEvent", &JSInteractableView::JsOnDelete);
    JSClass<JSText>::StaticMethod("remoteMessage", &JSText::JsRemoteMessage);
    JSClass<JSText>::StaticMethod("copyOption", &JSText::SetCopyOption);
    JSClass<JSText>::StaticMethod("onClick", &JSText::JsOnClick);
    JSClass<JSText>::StaticMethod("onAppear", &JSInteractableView::JsOnAppear);
    JSClass<JSText>::StaticMethod("onDisAppear", &JSInteractableView::JsOnDisAppear);
    JSClass<JSText>::StaticMethod("onDragStart", &JSText::JsOnDragStart);
    JSClass<JSText>::StaticMethod("onDragEnter", &JSText::JsOnDragEnter);
    JSClass<JSText>::StaticMethod("onDragMove", &JSText::JsOnDragMove);
    JSClass<JSText>::StaticMethod("onDragLeave", &JSText::JsOnDragLeave);
    JSClass<JSText>::StaticMethod("onDrop", &JSText::JsOnDrop);
    JSClass<JSText>::StaticMethod("focusable", &JSText::JsFocusable);
    JSClass<JSText>::Inherit<JSContainerBase>();
    JSClass<JSText>::Inherit<JSViewAbstract>();
    JSClass<JSText>::Bind<>(globalObj);
}

} // namespace OHOS::Ace::Framework

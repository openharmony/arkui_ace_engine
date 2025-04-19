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

#include <string>

#include "frameworks/bridge/common/utils/engine_helper.h"
#include "frameworks/bridge/declarative_frontend/engine/js_converter.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_layout_manager.h"
#include "frameworks/bridge/declarative_frontend/jsview/js_text.h"
#include "native_engine/impl/ark/ark_native_engine.h"

namespace OHOS::Ace::Framework {

constexpr int32_t DEFAULT_LENGTH = 3;
void JSLayoutManager::GetLineCount(const JSCallbackInfo& args)
{
    auto layoutInfoInterface = layoutInfoInterface_.Upgrade();
    CHECK_NULL_VOID(layoutInfoInterface);
    auto lineCount = layoutInfoInterface->GetLineCount();
    auto vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto lineCountObj = panda::NumberRef::New(vm, static_cast<int32_t>(lineCount));
    args.SetReturnValue(JsiRef<JsiObject>(JsiObject(lineCountObj)));
}

void JSLayoutManager::GetLineMetrics(const JSCallbackInfo& args)
{
    auto layoutInfoInterface = layoutInfoInterface_.Upgrade();
    CHECK_NULL_VOID(layoutInfoInterface);
    if (args.Length() < 1 || args[0]->IsUndefined() || args[0]->IsNull() || !args[0]->IsNumber()) {
        return;
    }
    if (double lineIndex = 0.0; !JSContainerBase::ParseJsDouble(args[0], lineIndex)
        || lineIndex != static_cast<double>(static_cast<int>(lineIndex))) {
        return;
    }
    int32_t lineIndex = 0;
    JSViewAbstract::ParseJsInteger<int32_t>(args[0], lineIndex);
    if (lineIndex < 0 || lineIndex >= static_cast<int32_t>(layoutInfoInterface->GetLineCount())) {
        return;
    }
    auto lineMetrics = layoutInfoInterface->GetLineMetrics(lineIndex);

    auto vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    const char* keysMetrics[] = { "startIndex", "endIndex", "ascent", "descent",
        "height", "width", "left", "baseline", "lineNumber", "topHeight"};

    Local<JSValueRef> valuesOfMetrics[] = { panda::NumberRef::New(vm, static_cast<uint32_t>(lineMetrics.startIndex)),
        panda::NumberRef::New(vm, static_cast<uint32_t>(lineMetrics.endIndex)),
        panda::NumberRef::New(vm, lineMetrics.ascender),
        panda::NumberRef::New(vm, lineMetrics.descender),
        panda::NumberRef::New(vm, lineMetrics.height),
        panda::NumberRef::New(vm, lineMetrics.width),
        panda::NumberRef::New(vm, lineMetrics.x),
        panda::NumberRef::New(vm, lineMetrics.baseline),
        panda::NumberRef::New(vm, static_cast<uint32_t>(lineMetrics.lineNumber)),
        panda::NumberRef::New(vm, lineMetrics.y)};

    auto lineMetricsObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysMetrics), keysMetrics, valuesOfMetrics);
    lineMetricsObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "runMetrics"),
        CreateJSRunMetrics(lineMetrics.runMetrics, args));

    args.SetReturnValue(JsiRef<JsiObject>(JsiObject(lineMetricsObj)));
}

void JSLayoutManager::DidExceedMaxLines(const JSCallbackInfo& args)
{
    auto layoutInfoInterface = layoutInfoInterface_.Upgrade();
    CHECK_NULL_VOID(layoutInfoInterface);
    auto exceedMaxLines = layoutInfoInterface->DidExceedMaxLines();

    auto vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto exceedMaxLineObj = panda::BooleanRef::New(vm, exceedMaxLines);
    args.SetReturnValue(JsiRef<JsiObject>(JsiObject(exceedMaxLineObj)));
}

void JSLayoutManager::GetRectsForRange(const JSCallbackInfo& args)
{
    if (args.Length() < DEFAULT_LENGTH) {
        return;
    }
    auto textRangeVal = args[0];
    if (!textRangeVal->IsObject() || textRangeVal->IsNull() || textRangeVal->IsUndefined()) {
        return;
    }
    auto layoutInfoInterface = layoutInfoInterface_.Upgrade();
    CHECK_NULL_VOID(layoutInfoInterface);
    int32_t start = -1;
    int32_t end = -1;
    JSRef<JSObject> rangeObj = JSRef<JSObject>::Cast(textRangeVal);
    JSRef<JSVal> startVal = rangeObj->GetProperty("start");
    JSRef<JSVal> endVal = rangeObj->GetProperty("end");
    if (!startVal->IsNull() && startVal->IsNumber()) {
        start = startVal->ToNumber<int32_t>();
    }
    if (!endVal->IsNull() && endVal->IsNumber()) {
        end = endVal->ToNumber<int32_t>();
    }

    auto widthStyleVal = args[1];
    if (widthStyleVal->IsNull() || widthStyleVal->IsUndefined()) {
        return;
    }
    RectWidthStyle widthStyle = ParseRectWidthStyle(widthStyleVal.Get());
    auto heightStyleVal = args[2];
    if (heightStyleVal->IsNull() || heightStyleVal->IsUndefined()) {
        return;
    }
    RectHeightStyle heightStyle = ParseRectHeightStyle(heightStyleVal.Get());
    std::vector<NG::ParagraphManager::TextBox> textBoxes =
        layoutInfoInterface->GetRectsForRange(start, end, heightStyle, widthStyle);
    CHECK_NULL_VOID(&textBoxes);
    JSRef<JSArray> textBoxArray = JSRef<JSArray>::New();
    for (const auto& textBox : textBoxes) {
        JSRef<JSObject> textBoxObj = JSRef<JSObject>::New();
        JSRef<JSObject> rectObj = JSRef<JSObject>::New();
        rectObj->SetProperty<float>("left", textBox.rect_.Left());
        rectObj->SetProperty<float>("top", textBox.rect_.Top());
        rectObj->SetProperty<float>("right", textBox.rect_.Right());
        rectObj->SetProperty<float>("bottom", textBox.rect_.Bottom());
        textBoxObj->SetPropertyObject("rect", rectObj);
        textBoxObj->SetProperty<int32_t>("direction", static_cast<int32_t>(textBox.direction_));
        textBoxArray->SetValueAt(textBoxArray->Length(), textBoxObj);
    }
    args.SetReturnValue(JSRef<JSVal>::Cast(textBoxArray));
}

Local<panda::ObjectRef> JSLayoutManager::CreateJSRunMetrics(const std::map<size_t,
    RunMetrics>& mapRunMetrics, const JSCallbackInfo& args)
{
    Local<panda::ObjectRef> obj;
    auto vm = args.GetVm();
    CHECK_NULL_RETURN(vm, obj);
    auto mapRunMetricsObj = panda::MapRef::New(vm);

    for (const auto& [key, val] : mapRunMetrics) {
        auto runMetricsObj = panda::ObjectRef::New(vm);
        runMetricsObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "textStyle"),
            CreateJSTextStyleResult(val.textStyle, args));
        runMetricsObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fontMetrics"),
            CreateJSFontMetrics(val.fontMetrics, args));
        mapRunMetricsObj->Set(vm, panda::NumberRef::New(vm, static_cast<uint32_t>(key)), runMetricsObj);
    }
    return mapRunMetricsObj;
}

Local<panda::ObjectRef> JSLayoutManager::CreateJSFontMetrics(const FontMetrics& fontMetrics,
    const JSCallbackInfo& args)
{
    Local<panda::ObjectRef> obj;
    auto vm = args.GetVm();
    CHECK_NULL_RETURN(vm, obj);

    const char* keysFontMetrics[] = { "flags", "top", "ascent", "descent",
        "bottom", "leading", "avgCharWidth", "maxCharWidth", "xMin", "xMax", "xHeight", "capHeight",
        "underlineThickness", "underlinePosition", "strikethroughThickness", "strikethroughPosition"};

    Local<JSValueRef> valuesOfFontMetrics[] = { panda::NumberRef::New(vm, fontMetrics.fFlags),
        panda::NumberRef::New(vm, fontMetrics.fTop),
        panda::NumberRef::New(vm, fontMetrics.fAscent),
        panda::NumberRef::New(vm, fontMetrics.fDescent),
        panda::NumberRef::New(vm, fontMetrics.fBottom),
        panda::NumberRef::New(vm, fontMetrics.fLeading),
        panda::NumberRef::New(vm, fontMetrics.fAvgCharWidth),
        panda::NumberRef::New(vm, fontMetrics.fMaxCharWidth),
        panda::NumberRef::New(vm, fontMetrics.fXMin),
        panda::NumberRef::New(vm, fontMetrics.fXMax),
        panda::NumberRef::New(vm, fontMetrics.fXHeight),
        panda::NumberRef::New(vm, fontMetrics.fCapHeight),
        panda::NumberRef::New(vm, fontMetrics.fUnderlineThickness),
        panda::NumberRef::New(vm, fontMetrics.fUnderlinePosition),
        panda::NumberRef::New(vm, fontMetrics.fStrikeoutThickness),
        panda::NumberRef::New(vm, fontMetrics.fStrikeoutPosition) };

    auto fontMetricsObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysFontMetrics), keysFontMetrics, valuesOfFontMetrics);

    return fontMetricsObj;
}

Local<panda::ObjectRef> JSLayoutManager::CreateJSTextStyleResult(const TextStyle& textStyle,
    const JSCallbackInfo& args)
{
    Local<panda::ObjectRef> obj;
    auto vm = args.GetVm();
    CHECK_NULL_RETURN(vm, obj);

    auto fontFamiliesArray = panda::ArrayRef::New(vm, textStyle.GetFontFamilies().size());
    for (uint32_t i = 0; i<textStyle.GetFontFamilies().size(); i++) {
        panda::ArrayRef::SetValueAt(vm, fontFamiliesArray, i, panda::StringRef::NewFromUtf8(
            vm, textStyle.GetFontFamilies().at(i).c_str()));
    }

    const char* keysTextStyle[] = { "decoration", "color", "fontWeight", "fontStyle", "baseline", "fontSize",
        "letterSpacing", "wordSpacing", "heightScale", "halfLeading", "heightOnly", "ellipsisMode", "locale"};

    Local<JSValueRef> valuesOfFontMetrics[] = { panda::NumberRef::New(
        vm, static_cast<int32_t>(textStyle.GetTextDecorationFirst())),
        panda::NumberRef::New(vm, textStyle.GetTextColor().GetValue()),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyle.GetFontWeight())),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyle.GetFontStyle())),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyle.GetTextBaseline())),
        panda::NumberRef::New(vm, textStyle.GetFontSize().Value()),
        panda::NumberRef::New(vm, textStyle.GetLetterSpacing().Value()),
        panda::NumberRef::New(vm, textStyle.GetWordSpacing().Value()),
        panda::NumberRef::New(vm, textStyle.GetHeightScale()),
        panda::NumberRef::New(vm, textStyle.GetHalfLeading()),
        panda::NumberRef::New(vm, textStyle.GetHeightOnly()),
        panda::StringRef::NewFromUtf8(vm, StringUtils::Str16ToStr8(textStyle.GetEllipsis()).c_str()),
        panda::NumberRef::New(vm, static_cast<int32_t>(textStyle.GetEllipsisMode())),
        panda::StringRef::NewFromUtf8(vm, textStyle.GetLocale().c_str()) };

    auto textStyleObj = panda::ObjectRef::NewWithNamedProperties(
        vm, ArraySize(keysTextStyle), keysTextStyle, valuesOfFontMetrics);
    textStyleObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "fontFamilies"), fontFamiliesArray);
    return textStyleObj;
}

void JSLayoutManager::GetGlyphPositionAtCoordinate(const JSCallbackInfo& args)
{
    if (args.Length() < 2) { // 2:At least two parameters
        TAG_LOGE(AceLogTag::ACE_RICH_TEXT, "Info length error.");
        return;
    }
    auto layoutInfoInterface = layoutInfoInterface_.Upgrade();
    CHECK_NULL_VOID(layoutInfoInterface);
    int32_t coordinateX = 0;
    int32_t coordinateY = 0;
    JSContainerBase::ParseJsInt32(args[0], coordinateX);
    JSContainerBase::ParseJsInt32(args[1], coordinateY);
    auto value = layoutInfoInterface->GetGlyphPositionAtCoordinate(coordinateX, coordinateY);
    
    auto vm = args.GetVm();
    CHECK_NULL_VOID(vm);
    auto positionObj = panda::NumberRef::New(vm, static_cast<int32_t>(value.position_));
    auto affinityObj = panda::NumberRef::New(vm, static_cast<int32_t>(value.affinity_));

    auto positionWithAffinityObj = panda::ObjectRef::New(vm);
    positionWithAffinityObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "position"), positionObj);
    positionWithAffinityObj->Set(vm, panda::StringRef::NewFromUtf8(vm, "affinity"), affinityObj);
    args.SetReturnValue(JsiRef<JsiObject>(JsiObject(positionWithAffinityObj)));
}

void JSLayoutManager::JSBind(BindingTarget globalObj)
{
    JSClass<JSLayoutManager>::Declare("LayoutManager");
    JSClass<JSLayoutManager>::CustomMethod("getLineCount", &JSLayoutManager::GetLineCount);
    JSClass<JSLayoutManager>::CustomMethod(
        "getGlyphPositionAtCoordinate", &JSLayoutManager::GetGlyphPositionAtCoordinate);
    JSClass<JSLayoutManager>::CustomMethod("getLineMetrics", &JSLayoutManager::GetLineMetrics);
    JSClass<JSLayoutManager>::CustomMethod("getRectsForRange", &JSLayoutManager::GetRectsForRange);
    JSClass<JSLayoutManager>::CustomMethod("didExceedMaxLines", &JSLayoutManager::DidExceedMaxLines);
    JSClass<JSLayoutManager>::Bind(globalObj, JSLayoutManager::Constructor, JSLayoutManager::Destructor);
}
} // namespace OHOS::Ace::Framework
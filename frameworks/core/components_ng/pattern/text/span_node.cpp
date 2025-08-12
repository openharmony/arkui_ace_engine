/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/text/span_node.h"

#include <cstdint>
#include <optional>
#include <string>

#include "text_layout_adapter.h"

#include "base/geometry/dimension.h"
#include "base/utils/string_utils.h"
#include "base/utils/utf_helper.h"
#include "base/utils/utils.h"
#include "core/common/font_manager.h"
#include "core/common/resource/resource_parse_utils.h"
#include "core/components/common/layout/constants.h"
#include "core/components/common/properties/text_style.h"
#include "core/components/hyperlink/hyperlink_theme.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/inspector_filter.h"
#include "core/components_ng/pattern/text/text_pattern.h"
#include "core/components_ng/pattern/text/text_styles.h"
#include "core/components_ng/property/property.h"
#include "core/components_ng/render/drawing_prop_convertor.h"
#include "core/components_ng/render/paragraph.h"
#include "core/pipeline/pipeline_context.h"
#include "core/pipeline_ng/pipeline_context.h"
#include "core/text/text_emoji_processor.h"

namespace OHOS::Ace::NG {
namespace {
const std::string CUSTOM_SYMBOL_SUFFIX = "_CustomSymbol";
const std::string DEFAULT_SYMBOL_FONTFAMILY = "HM Symbol";

std::string GetDeclaration(const std::optional<Color>& color, const std::vector<TextDecoration>& textDecorations,
    const std::optional<TextDecorationStyle>& textDecorationStyle)
{
    auto jsonSpanDeclaration = JsonUtil::Create(true);
    jsonSpanDeclaration->Put(
        "type", V2::ConvertWrapTextDecorationToStirng(textDecorations).c_str());
    jsonSpanDeclaration->Put("color", (color.value_or(Color::BLACK).ColorToString()).c_str());
    jsonSpanDeclaration->Put("style",
        V2::ConvertWrapTextDecorationStyleToString(textDecorationStyle.value_or(TextDecorationStyle::SOLID))
            .c_str());
    return jsonSpanDeclaration->ToString();
}

inline std::unique_ptr<JsonValue> ConvertShadowToJson(const Shadow& shadow)
{
    auto jsonShadow = JsonUtil::Create(true);
    jsonShadow->Put("radius", std::to_string(shadow.GetBlurRadius()).c_str());
    jsonShadow->Put("color", shadow.GetColor().ColorToString().c_str());
    jsonShadow->Put("offsetX", std::to_string(shadow.GetOffset().GetX()).c_str());
    jsonShadow->Put("offsetY", std::to_string(shadow.GetOffset().GetY()).c_str());
    jsonShadow->Put("type", std::to_string(static_cast<int32_t>(shadow.GetShadowType())).c_str());
    return jsonShadow;
}
std::unique_ptr<JsonValue> ConvertShadowsToJson(const std::vector<Shadow>& shadows)
{
    auto jsonShadows = JsonUtil::CreateArray(true);
    for (const auto& shadow : shadows) {
        jsonShadows->Put(ConvertShadowToJson(shadow));
    }
    return jsonShadows;
}
} // namespace

std::string SpanItem::GetFont() const
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, "");
    auto textPattern = DynamicCast<TextPattern>(pattern);
    CHECK_NULL_RETURN(textPattern, "");
    auto jsonValue = JsonUtil::Create(true);
    jsonValue->Put("style", GetFontStyleInJson(fontStyle->GetItalicFontStyle()).c_str());
    jsonValue->Put("size", textPattern->GetFontSizeWithThemeInJson(fontStyle->GetFontSize()).c_str());
    jsonValue->Put("weight", GetFontWeightInJson(fontStyle->GetFontWeight()).c_str());
    jsonValue->Put("family", GetFontFamilyInJson(fontStyle->GetFontFamily()).c_str());
    return jsonValue->ToString();
}

void SpanItem::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    json->PutFixedAttr("content", UtfUtils::Str16DebugToStr8(content).c_str(), filter, FIXED_ATTR_CONTENT);
    if (filter.IsFastFilter()) {
        TextBackgroundStyle::ToJsonValue(json, backgroundStyle, filter);
        return;
    }
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textPattern = DynamicCast<TextPattern>(pattern);
    CHECK_NULL_VOID(textPattern);
    if (fontStyle) {
        json->PutExtAttr("font", GetFont().c_str(), filter);
        json->PutExtAttr("fontSize", textPattern->GetFontSizeWithThemeInJson(fontStyle->GetFontSize()).c_str(), filter);
        json->PutExtAttr("decoration", GetDeclaration(fontStyle->GetTextDecorationColor(),
            fontStyle->GetTextDecoration().value_or(std::vector<TextDecoration>({TextDecoration::NONE})),
            fontStyle->GetTextDecorationStyle()).c_str(), filter);
        json->PutExtAttr("letterSpacing",
            fontStyle->GetLetterSpacing().value_or(Dimension()).ToString().c_str(), filter);
        json->PutExtAttr("textCase",
            V2::ConvertWrapTextCaseToStirng(fontStyle->GetTextCase().value_or(TextCase::NORMAL)).c_str(), filter);
        if (spanItemType == SpanItemType::SYMBOL) {
            const std::optional<std::vector<Color>>& colorListOptional = fontStyle->GetSymbolColorList();
            auto colorListValue = colorListOptional.has_value() ? colorListOptional.value() : std::vector<Color>();
            json->PutExtAttr("fontColor", StringUtils::SymbolColorListToString(colorListValue).c_str(), filter);
        } else {
            json->PutExtAttr("fontColor", fontStyle->GetForegroundColor().value_or(fontStyle->GetTextColor()
                .value_or(Color::BLACK)).ColorToString().c_str(), filter);
        }
        json->PutExtAttr("fontStyle", GetFontStyleInJson(fontStyle->GetItalicFontStyle()).c_str(), filter);
        json->PutExtAttr("fontWeight", GetFontWeightInJson(fontStyle->GetFontWeight()).c_str(), filter);
        json->PutExtAttr("fontFamily", GetFontFamilyInJson(fontStyle->GetFontFamily()).c_str(), filter);
        json->PutExtAttr("renderingStrategy",
            GetSymbolRenderingStrategyInJson(fontStyle->GetSymbolRenderingStrategy()).c_str(), filter);
        json->PutExtAttr(
            "effectStrategy", GetSymbolEffectStrategyInJson(fontStyle->GetSymbolEffectStrategy()).c_str(), filter);
        json->Put("symbolEffect",
            GetSymbolEffectOptionsInJson(fontStyle->GetSymbolEffectOptions().value_or(SymbolEffectOptions())).c_str());
        auto shadow = fontStyle->GetTextShadow().value_or(std::vector<Shadow> { Shadow() });
        auto jsonShadow = (shadow.size() == 1) ? ConvertShadowToJson(shadow.front()) : ConvertShadowsToJson(shadow);
        json->PutExtAttr("textShadow", jsonShadow, filter);
    }
    auto dim = Dimension();
    if (textLineStyle) {
        json->PutExtAttr("lineHeight", textLineStyle->GetLineHeight().value_or(dim).ToString().c_str(), filter);
        json->PutExtAttr("lineSpacing", textLineStyle->GetLineSpacing().value_or(dim).ToString().c_str(), filter);
        json->PutExtAttr("baselineOffset",
            textLineStyle->GetBaselineOffset().value_or(dim).ToString().c_str(), filter);
    }
    TextBackgroundStyle::ToJsonValue(json, backgroundStyle, filter);
}

void SpanItem::ToTreeJson(std::unique_ptr<JsonValue>& json, const InspectorConfig& config) const
{
    if (!content.empty()) {
        json->Put(TreeKey::CONTENT, content.c_str());
    }
}

RefPtr<SpanNode> SpanNode::GetOrCreateSpanNode(int32_t nodeId)
{
    auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById<SpanNode>(nodeId);
    if (spanNode) {
        return spanNode;
    }
    spanNode = MakeRefPtr<SpanNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(spanNode);
    return spanNode;
}

RefPtr<SpanNode> SpanNode::CreateSpanNode(int32_t nodeId)
{
    auto spanNode = MakeRefPtr<SpanNode>(nodeId);
    ElementRegister::GetInstance()->AddUINode(spanNode);
    return spanNode;
}

RefPtr<SpanNode> SpanNode::GetOrCreateSpanNode(const std::string& tag, int32_t nodeId)
{
    auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById<SpanNode>(nodeId);
    if (spanNode) {
        return spanNode;
    }
    spanNode = MakeRefPtr<SpanNode>(tag, nodeId);
    ElementRegister::GetInstance()->AddUINode(spanNode);
    return spanNode;
}

void SpanNode::MountToParagraph()
{
    auto parent = GetParent();
    while (parent) {
        auto spanNode = DynamicCast<SpanNode>(parent);
        if (spanNode) {
            spanNode->AddChildSpanItem(Claim(this));
            return;
        }
        auto textNode = DynamicCast<FrameNode>(parent);
        if (textNode) {
            auto textPattern = textNode->GetPattern<TextPattern>();
            if (textPattern) {
                textPattern->AddChildSpanItem(Claim(this));
                return;
            }
        }
        parent = parent->GetParent();
    }
}

void SpanNode::RequestTextFlushDirty(bool markModifyDone)
{
    RequestTextFlushDirty(Claim<UINode>(this), markModifyDone);
}

void SpanNode::RequestTextFlushDirty(const RefPtr<UINode>& node, bool markModifyDone)
{
    CHECK_NULL_VOID(node);
    auto parent = node->GetParent();
    while (parent) {
        auto textNode = DynamicCast<FrameNode>(parent);
        if (textNode) {
            textNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
            auto textPattern = textNode->GetPattern<TextPattern>();
            if (textPattern) {
                ACE_TEXT_SCOPED_TRACE("RequestTextFlushDirty [Parent:%d,Tag:%s][Span:%d]", textNode->GetId(),
                    textNode->GetTag().c_str(), node->GetId());
                CHECK_NULL_VOID(markModifyDone);
                textPattern->OnModifyDone();
                return;
            }
        }
        parent = parent->GetParent();
    }
}

void SpanNode::SetTextBackgroundStyle(const TextBackgroundStyle& style)
{
    BaseSpan::SetTextBackgroundStyle(style);
    spanItem_->backgroundStyle = GetTextBackgroundStyle();
    spanItem_->MarkReLayoutParagraph();
}

void SpanNode::UpdateTextBackgroundFromParent(const std::optional<TextBackgroundStyle>& style)
{
    BaseSpan::UpdateTextBackgroundFromParent(style);
    spanItem_->backgroundStyle = GetTextBackgroundStyle();
    spanItem_->MarkReLayoutParagraph();
}

void SpanNode::DumpInfo()
{
    auto& dumpLog = DumpLog::GetInstance();
    spanItem_->SpanDumpInfo();
    if (GetTag() == V2::SYMBOL_SPAN_ETS_TAG) {
        auto textStyle = spanItem_->GetTextStyle();
        if (!textStyle) {
            return;
        }
        dumpLog.AddDesc(std::string("SymbolColor:").append(spanItem_->SymbolColorToString()));
        dumpLog.AddDesc(std::string("RenderStrategy: ").append(std::to_string(textStyle->GetRenderStrategy())));
        dumpLog.AddDesc(std::string("EffectStrategy: ").append(std::to_string(textStyle->GetEffectStrategy())));
        dumpLog.AddDesc(std::string("SymbolEffect:").append(
            spanItem_->fontStyle->GetSymbolEffectOptions().value_or(NG::SymbolEffectOptions()).ToString()));
    }
}

#define ADD_FONT_STYLE_DESC_UTILS(name, property)                                                  \
    do {                                                                                           \
        dumpLog.AddDesc(std::string(#name ": ")                                                    \
                            .append(StringUtils::ToString(textStyle->Get##name()))                 \
                            .append(" self: ")                                                     \
                            .append(fontStyle && fontStyle->Has##property()                        \
                                        ? StringUtils::ToString(fontStyle->Get##property##Value()) \
                                        : "Na"));                                                  \
    } while (0)

#define ADD_FONT_STYLE_DESC(name)                                                                                \
    do {                                                                                                         \
        dumpLog.AddDesc(                                                                                         \
            std::string(#name ": ")                                                                              \
                .append(textStyle->Get##name().ToString())                                                       \
                .append(" self: ")                                                                               \
                .append(fontStyle && fontStyle->Has##name() ? fontStyle->Get##name##Value().ToString() : "Na")); \
    } while (0)

#define ADD_LINE_STYLE_DESC_UTILS(name, property)                                                      \
    do {                                                                                               \
        dumpLog.AddDesc(std::string(#name ": ")                                                        \
                            .append(StringUtils::ToString(textStyle->Get##name()))                     \
                            .append(" self: ")                                                         \
                            .append(textLineStyle && textLineStyle->Has##property()                    \
                                        ? StringUtils::ToString(textLineStyle->Get##property##Value()) \
                                        : "Na"));                                                      \
    } while (0)

#define ADD_LINE_STYLE_DESC(name)                                                                                  \
    do {                                                                                                           \
        dumpLog.AddDesc(                                                                                           \
            std::string(#name ": ")                                                                                \
                .append(textStyle->Get##name().ToString())                                                         \
                .append(" self: ")                                                                                 \
                .append(textLineStyle && textLineStyle->Has##name() ? textLineStyle->Get##name##Value().ToString() \
                                                                    : "Na"));                                      \
    } while (0)

void SpanItem::SpanDumpInfo()
{
    auto& dumpLog = DumpLog::GetInstance();
    dumpLog.AddDesc(std::string("--------Content: ")
                        .append("\"")
                        .append(UtfUtils::Str16DebugToStr8(content))
                        .append("\"")
                        .append(",spanItemType:")
                        .append(StringUtils::ToString(spanItemType)));
    auto textStyle = textStyle_;
    if (!textStyle || (spanItemType != SpanItemType::NORMAL && spanItemType != SpanItemType::SYMBOL)) {
        return;
    }
    ADD_LINE_STYLE_DESC(BaselineOffset);
    ADD_LINE_STYLE_DESC_UTILS(EllipsisMode, EllipsisMode);
    ADD_FONT_STYLE_DESC(FontSize);
    ADD_FONT_STYLE_DESC_UTILS(FontWeight, FontWeight);
    ADD_FONT_STYLE_DESC_UTILS(FontStyle, ItalicFontStyle);
    dumpLog.AddDesc(std::string("HalfLeading: ").append(std::to_string(textStyle->GetHalfLeading())));
    SpanDumpInfoAdvance();
}

void SpanItem::SpanDumpInfoAdvance()
{
    CHECK_NULL_VOID(SystemProperties::GetDebugEnabled());
    auto& dumpLog = DumpLog::GetInstance();
    auto textStyle = textStyle_;
    if (!textStyle) {
        return;
    }
    ADD_LINE_STYLE_DESC(LineHeight);
    ADD_FONT_STYLE_DESC(LetterSpacing);
    ADD_LINE_STYLE_DESC(LineSpacing);
    ADD_LINE_STYLE_DESC_UTILS(TextAlign, TextAlign);
    ADD_LINE_STYLE_DESC(TextIndent);
    dumpLog.AddDesc(
        std::string("TextColor: ")
            .append(textStyle->GetTextColor().ColorToString())
            .append(" self: ")
            .append(fontStyle && fontStyle->HasTextColor() ? fontStyle->GetTextColorValue().ColorToString() : "Na"));
    ADD_FONT_STYLE_DESC_UTILS(TextCase, TextCase);
    ADD_LINE_STYLE_DESC_UTILS(TextOverflow, TextOverflow);
    ADD_LINE_STYLE_DESC_UTILS(WordBreak, WordBreak);
    dumpLog.AddDesc(std::string("WordSpacing: ")
                        .append(textStyle->GetWordSpacing().ToString())
                        .append(" Decoration: ")
                        .append(StringUtils::ToString(textStyle->GetTextDecorationFirst()))
                        .append(" ")
                        .append(StringUtils::ToString(textStyle->GetTextDecorationStyle()))
                        .append(" ")
                        .append(textStyle->GetTextDecorationColor().ColorToString())
                        .append(" self: ")
                        .append(fontStyle && fontStyle->HasTextDecoration()
                                    ? StringUtils::ToString(fontStyle->GetTextDecorationFirst())
                                    : "Na")
                        .append(" ")
                        .append(fontStyle && fontStyle->HasTextDecorationStyle()
                                    ? StringUtils::ToString(fontStyle->GetTextDecorationStyleValue())
                                    : "Na")
                        .append(" ")
                        .append(fontStyle && fontStyle->HasTextDecorationColor()
                                    ? fontStyle->GetTextDecorationColorValue().ColorToString()
                                    : "Na"));
}

#define DEFINE_SPAN_PROP_HANDLER(KEY_TYPE, VALUE_TYPE, UPDATE_METHOD)                           \
    {                                                                                           \
        #KEY_TYPE, [](int32_t nodeId, RefPtr<PropertyValueBase> value) {                        \
            auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById                 \
                <SpanNode>(nodeId);                                                             \
            CHECK_NULL_VOID(spanNode);                                                          \
            if (auto realValue = std::get_if<VALUE_TYPE>(&(value->GetValue()))) {                             \
                spanNode->UPDATE_METHOD(*realValue);                                             \
                                                                                                \
            }                                                                                   \
        }                                                                                       \
    }

#define DEFINE_CONTAINER_SPAN_PROP_HANDLER(KEY_TYPE, VALUE_TYPE, UPDATE_METHOD)                 \
    {                                                                                           \
        #KEY_TYPE, [](int32_t nodeId, RefPtr<PropertyValueBase> value) {                        \
            auto spanNode = ElementRegister::GetInstance()->GetSpecificItemById                 \
                <ContainerSpanNode>(nodeId);                                                    \
            CHECK_NULL_VOID(spanNode);                                                          \
            if (auto castedVal = DynamicCast<PropertyValue<VALUE_TYPE>>(value)) {               \
                spanNode->UPDATE_METHOD(castedVal->value);                                      \
            }                                                                                   \
        }                                                                                       \
    }

template<typename T>
void ContainerSpanNode::RegisterResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
{
    auto&& updateFunc = [weakptr = AceType::WeakClaim(this), key](const RefPtr<ResourceObject>& resObj) {
        auto spanNode = weakptr.Upgrade();
        CHECK_NULL_VOID(spanNode);
        spanNode->UpdateSpanResource<T>(key, resObj);
    };
    AddResObj(key, resObj, std::move(updateFunc));
}

template void ContainerSpanNode::RegisterResource<Color>(
    const std::string&, const RefPtr<ResourceObject>&, Color);
template void ContainerSpanNode::RegisterResource<CalcDimension>(
    const std::string&, const RefPtr<ResourceObject>&, CalcDimension);
template void ContainerSpanNode::RegisterResource<std::vector<std::string>>(
    const std::string&, const RefPtr<ResourceObject>&, std::vector<std::string>);
template void ContainerSpanNode::RegisterResource<std::u16string>(
    const std::string&, const RefPtr<ResourceObject>&, std::u16string);
template void ContainerSpanNode::RegisterResource<FontWeight>(
    const std::string&, const RefPtr<ResourceObject>&, FontWeight);


template<typename T>
void ContainerSpanNode::UpdateSpanResource(const std::string& key, const RefPtr<ResourceObject>& resObj)
{
    UpdateProperty<T>(key, resObj);
    MarkTextDirty();
}

using Handler = std::function<void(int32_t, RefPtr<PropertyValueBase>)>;

template<typename T>
void ContainerSpanNode::UpdateProperty(std::string key, const RefPtr<ResourceObject>& resObj)
{
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    if constexpr (std::is_same_v<T, std::string>) {
        value->SetValueType(ValueType::STRING);
    } else if (std::is_same_v<T, std::u16string>) {
        value->SetValueType(ValueType::U16STRING);
    } else if constexpr(std::is_same_v<T, Color>) {
        value->SetValueType(ValueType::COLOR);
    } else if constexpr(std::is_same_v<T, double>) {
        value->SetValueType(ValueType::DOUBLE);
    } else if constexpr(std::is_same_v<T, CalcDimension>) {
        value->SetValueType(ValueType::CALDIMENSION);
    } else if constexpr(std::is_same_v<T, float>) {
        value->SetValueType(ValueType::FLOAT);
    } else if constexpr(std::is_same_v<T, std::vector<std::string>>) {
        value->SetValueType(ValueType::VECTOR_STRING);
    } else if constexpr(std::is_same_v<T, FontWeight>) {
        value->SetValueType(ValueType::FONT_WEIGHT);
    }
    ParseResToObject(resObj, value);
    UpdatePropertyImpl(key, value);
}

void ContainerSpanNode::UpdatePropertyImpl(
    const std::string& key, RefPtr<PropertyValueBase> value)
{
    return;
}

template<typename T>
void SpanNode::RegisterResource(const std::string& key, const RefPtr<ResourceObject>& resObj, T value)
{
    auto&& updateFunc = [weakptr = AceType::WeakClaim(this), key](const RefPtr<ResourceObject>& resObj) {
        auto spanNode = weakptr.Upgrade();
        CHECK_NULL_VOID(spanNode);
        spanNode->UpdateSpanResource<T>(key, resObj);
    };
    AddResObj(key, resObj, std::move(updateFunc));
}

template void SpanNode::RegisterResource<CalcDimension>(
    const std::string&, const RefPtr<ResourceObject>&, CalcDimension);
template void SpanNode::RegisterResource<Color>(
    const std::string&, const RefPtr<ResourceObject>&, Color);
template void SpanNode::RegisterResource<std::vector<std::string>>(
    const std::string&, const RefPtr<ResourceObject>&, std::vector<std::string>);
template void SpanNode::RegisterResource<std::u16string>(
    const std::string&, const RefPtr<ResourceObject>&, std::u16string);
template void SpanNode::RegisterResource<FontWeight>(
    const std::string&, const RefPtr<ResourceObject>&, FontWeight);

template<typename T>
void SpanNode::UpdateSpanResource(const std::string& key, const RefPtr<ResourceObject>& resObj)
{
    UpdateProperty<T>(key, resObj);
    auto spanItem = GetSpanItem();
    auto pattern = spanItem->GetTextPattern().Upgrade();
    CHECK_NULL_VOID(pattern);
    auto textPattern = DynamicCast<TextPattern>(pattern);
    CHECK_NULL_VOID(textPattern);
    if (GetRerenderable()) {
        textPattern->MarkDirtyNodeRender();
        textPattern->MarkDirtyNodeMeasure();
    }
}

void BaseSpan::ParseResToObject(const RefPtr<ResourceObject>& resObj, RefPtr<PropertyValueBase> valueBase)
{
    if (valueBase->GetValueType() == ValueType::STRING) {
        std::string value;
        ResourceParseUtils::ParseResString(resObj, value);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::U16STRING) {
        std::u16string value;
        ResourceParseUtils::ParseResString(resObj, value);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::FONT_WEIGHT) {
        std::string fontWeightStr;
        ResourceParseUtils::ParseResString(resObj, fontWeightStr);
        auto value = Framework::ConvertStrToFontWeight(fontWeightStr);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::COLOR) {
        Color value;
        ResourceParseUtils::ParseResColor(resObj, value);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::DOUBLE) {
        double value;
        ResourceParseUtils::ParseResDouble(resObj, value);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::CALDIMENSION) {
        CalcDimension value;
        ResourceParseUtils::ParseResDimensionNG(resObj, value, DimensionUnit::FP, false);
        valueBase->SetValue(value);
    } else if (valueBase->GetValueType() == ValueType::VECTOR_STRING) {
        std::vector<std::string> value;
        ResourceParseUtils::ParseResFontFamilies(resObj, value);
        valueBase->SetValue(value);
    }
}

void SpanNode::UnregisterResource(const std::string& key)
{
    if (key == "symbolColor") {
        for (auto index : symbolFontColorResObjIndexArr) {
            auto storeKey = key + "_" + std::to_string(index);
            RemoveResObj(storeKey);
        }
        symbolFontColorResObjIndexArr.clear();
        return;
    }
    BaseSpan::UnregisterResource(key);
}

void SpanNode::RegisterSymbolFontColorResource(const std::string& key,
    std::vector<Color>& symbolColor, const std::vector<std::pair<int32_t, RefPtr<ResourceObject>>>& resObjArr)
{
    for (auto i = 0; i < static_cast<int32_t>(resObjArr.size()); ++i) {
        auto resObjIndex = resObjArr[i].first;
        auto resObj = resObjArr[i].second;
        auto storeKey = key + "_" + std::to_string(resObjIndex);
        symbolFontColorResObjIndexArr.emplace_back(resObjIndex);
        auto&& updateFunc = [weakptr = AceType::WeakClaim(this), storeKey, resObjIndex]
            (const RefPtr<ResourceObject>& resObj) {
            auto spanNode = weakptr.Upgrade();
            CHECK_NULL_VOID(spanNode);
            Color fontColor;
            ResourceParseUtils::ParseResColor(resObj, fontColor);
            auto colorVec = spanNode->GetSymbolColorList();
            if (colorVec.has_value() && GreatNotEqual(colorVec.value().size(), resObjIndex)) {
                auto colorVecArr = colorVec.value();
                colorVecArr[resObjIndex] = fontColor;
                spanNode->UpdateSymbolColorList(colorVecArr);
            }
        };
        AddResObj(storeKey, resObj, std::move(updateFunc));
    }
    UpdateSymbolColorList(symbolColor);
}

template<typename T>
void SpanNode::UpdateProperty(std::string key, const RefPtr<ResourceObject>& resObj)
{
    auto value = AceType::MakeRefPtr<PropertyValueBase>();
    if constexpr (std::is_same_v<T, std::string>) {
        value->SetValueType(ValueType::STRING);
    } else if (std::is_same_v<T, std::u16string>) {
        value->SetValueType(ValueType::U16STRING);
    } else if constexpr(std::is_same_v<T, Color>) {
        value->SetValueType(ValueType::COLOR);
    } else if constexpr(std::is_same_v<T, double>) {
        value->SetValueType(ValueType::DOUBLE);
    } else if constexpr(std::is_same_v<T, CalcDimension>) {
        value->SetValueType(ValueType::CALDIMENSION);
    } else if constexpr(std::is_same_v<T, float>) {
        value->SetValueType(ValueType::FLOAT);
    } else if constexpr(std::is_same_v<T, std::vector<std::string>>) {
        value->SetValueType(ValueType::VECTOR_STRING);
    } else if constexpr(std::is_same_v<T, FontWeight>) {
        value->SetValueType(ValueType::FONT_WEIGHT);
    }
    ParseResToObject(resObj, value);
    UpdatePropertyImpl(key, value);
}

void SpanNode::UpdatePropertyImpl(
    const std::string& key, RefPtr<PropertyValueBase> value)
{
    CHECK_NULL_VOID(value);
    const std::unordered_map<std::string, Handler> span_handlers = {
        DEFINE_SPAN_PROP_HANDLER(fontSize, CalcDimension, UpdateFontSize),
        DEFINE_SPAN_PROP_HANDLER(fontColor, Color, UpdateTextColor),
        DEFINE_SPAN_PROP_HANDLER(fontWeight, FontWeight, UpdateFontWeight),
        DEFINE_SPAN_PROP_HANDLER(letterSpacing, CalcDimension, UpdateLetterSpacing),
        DEFINE_SPAN_PROP_HANDLER(decorationColor, Color, UpdateTextDecorationColor),
        DEFINE_SPAN_PROP_HANDLER(lineHeight, CalcDimension, UpdateLineHeight),
        DEFINE_SPAN_PROP_HANDLER(baselineOffset, CalcDimension, UpdateBaselineOffset),
        DEFINE_SPAN_PROP_HANDLER(value, std::u16string, UpdateContent),
        DEFINE_SPAN_PROP_HANDLER(fontFamily, std::vector<std::string>, UpdateFontFamily),
    };
    auto it = span_handlers.find(key);
    if (it != span_handlers.end()) {
        it->second(GetId(), value);
    }
}

int32_t SpanItem::UpdateParagraph(const RefPtr<FrameNode>& frameNode, const RefPtr<Paragraph>& builder,
    const TextStyle& textStyle, bool isMarquee)
{
    CHECK_NULL_RETURN(builder, -1);
    CHECK_NULL_RETURN(frameNode, -1);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, -1);
    auto spanTextStyle = textStyle;
    UseSelfStyle(fontStyle, textLineStyle, spanTextStyle, false);
    if (fontStyle && fontStyle->HasFontWeight()) {
        spanTextStyle.SetEnableVariableFontWeight(false);
    }
    auto fontManager = pipelineContext->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty()) && (spanTextStyle.GetFontFamilies().empty())) {
        spanTextStyle.SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }
    FontRegisterCallback(frameNode, spanTextStyle);
    auto spanContent = GetSpanContent(content, isMarquee);
    auto pattern = frameNode->GetPattern<TextPattern>();
    CHECK_NULL_RETURN(pattern, -1);
    spanTextStyle.SetTextBackgroundStyle(backgroundStyle);
    spanTextStyle.SetTextStyleUid(nodeId_);
    if (fontStyle && !fontStyle->HasTextColor() && urlOnRelease) {
        auto urlSpanColor = pattern->GetUrlSpanColor();
        spanTextStyle.SetTextColor(urlSpanColor);
        UpdateTextStyle(spanContent, builder, spanTextStyle, selectedStart, selectedEnd);
    } else if (pattern->NeedShowAIDetect() && !aiSpanMap.empty()) {
        TextStyle aiSpanStyle = spanTextStyle;
        pattern->ModifyAISpanStyle(aiSpanStyle);
        UpdateTextStyleForAISpan(spanContent, builder, spanTextStyle, aiSpanStyle);
    } else {
        UpdateTextStyle(spanContent, builder, spanTextStyle, selectedStart, selectedEnd);
    }
    textStyle_ = spanTextStyle;
    ResetReCreateAndReLayout();
    return -1;
}

bool SpanItem::UpdateSpanTextStyle(const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(frameNode, false);
    auto pipelineContext = frameNode->GetContextRefPtr();
    CHECK_NULL_RETURN(pipelineContext, false);
    CHECK_NULL_RETURN(textStyle_.has_value(), true);
    UpdateReLayoutTextStyle(textStyle_.value(), textStyle, unicode != 0);
    if (fontStyle && fontStyle->HasFontWeight()) {
        textStyle_.value().SetEnableVariableFontWeight(false);
    } else {
        textStyle_.value().SetEnableVariableFontWeight(textStyle.GetEnableVariableFontWeight());
    }
    auto fontManager = pipelineContext->GetFontManager();
    if (fontManager && !(fontManager->GetAppCustomFont().empty()) && (textStyle_.value().GetFontFamilies().empty())) {
        textStyle_.value().SetFontFamilies(Framework::ConvertStrToFontFamilies(fontManager->GetAppCustomFont()));
    }

    if (unicode != 0) {
        auto pattern = frameNode->GetPattern<TextPattern>();
        CHECK_NULL_RETURN(pattern, false);
        UpdateSymbolSpanColor(frameNode, textStyle_.value());
        if (!symbolEffectSwitch_ || pattern->IsDragging()) {
            textStyle_.value().SetEffectStrategy(0);
        } else if (fontStyle) {
            textStyle_.value().SetEffectStrategy(fontStyle->propSymbolEffectStrategy.value_or(0));
        }
    }
    FontRegisterCallback(frameNode, textStyle_.value());
    textStyle_.value().SetTextBackgroundStyle(backgroundStyle);
    return textStyle_.value().NeedReCreateParagraph();
}

bool SpanItem::CheckSpanNeedReCreate(int32_t index)
{
    needReCreateParagraph_ |= (index != itemIndex_);
    itemIndex_ = index;
    CHECK_NULL_RETURN(unicode != 0, needReCreateParagraph_);
    if (fontStyle && fontStyle->HasSymbolType()) {
        return (fontStyle->GetSymbolType().value() == SymbolType::CUSTOM) | needReCreateParagraph_;
    }
    return needReCreateParagraph_;
}

#define UPDATE_SPAN_TEXT_STYLE(group, name, styleName)                 \
    do {                                                               \
        if (group && (group)->prop##name.has_value()) {                \
            spanTextStyle.Set##styleName((group)->prop##name.value()); \
        } else {                                                       \
            spanTextStyle.Set##styleName(textStyle.Get##styleName());  \
        }                                                              \
    } while (false)

void SpanItem::UpdateReLayoutTextStyle(
    TextStyle& spanTextStyle, const TextStyle& textStyle, bool isSymbol)
{
    // The setting of AllowScale, MinFontScale, MaxFontScale must be done before any Dimension-type properties that
    // depend on its value.
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, AllowScale, AllowScale);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, MinFontScale, MinFontScale);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, MaxFontScale, MaxFontScale);

    UPDATE_SPAN_TEXT_STYLE(fontStyle, FontSize, FontSize);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, AdaptMinFontSize, AdaptMinFontSize);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, AdaptMaxFontSize, AdaptMaxFontSize);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, LetterSpacing, LetterSpacing);
    if (!urlOnRelease || (fontStyle && fontStyle->propTextColor.has_value())) {
        UPDATE_SPAN_TEXT_STYLE(fontStyle, TextColor, TextColor);
    }
    UPDATE_SPAN_TEXT_STYLE(fontStyle, TextShadow, TextShadows);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, ItalicFontStyle, FontStyle);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, Superscript, Superscript);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, FontWeight, FontWeight);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, FontFeature, FontFeatures);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, TextDecoration, TextDecoration);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, TextDecorationColor, TextDecorationColor);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, TextDecorationStyle, TextDecorationStyle);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, LineThicknessScale, LineThicknessScale);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, TextCase, TextCase);

    UPDATE_SPAN_TEXT_STYLE(fontStyle, VariableFontWeight, VariableFontWeight);

    UPDATE_SPAN_TEXT_STYLE(fontStyle, StrokeWidth, StrokeWidth);
    UPDATE_SPAN_TEXT_STYLE(fontStyle, StrokeColor, StrokeColor);
    if (isSymbol) {
        UPDATE_SPAN_TEXT_STYLE(fontStyle, SymbolColorList, SymbolColorList);
        UPDATE_SPAN_TEXT_STYLE(fontStyle, SymbolRenderingStrategy, RenderStrategy);
        UPDATE_SPAN_TEXT_STYLE(fontStyle, SymbolEffectOptions, SymbolEffectOptions);
        UPDATE_SPAN_TEXT_STYLE(fontStyle, SymbolType, SymbolType);
    } else {
        UPDATE_SPAN_TEXT_STYLE(fontStyle, FontFamily, FontFamilies);
    }

    UPDATE_SPAN_TEXT_STYLE(textLineStyle, LineHeight, LineHeight);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, BaselineOffset, BaselineOffset);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, LineSpacing, LineSpacing);

    UPDATE_SPAN_TEXT_STYLE(textLineStyle, OptimizeTrailingSpace, OptimizeTrailingSpace);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, HalfLeading, HalfLeading);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, TextBaseline, TextBaseline);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, TextOverflow, TextOverflow);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, TextAlign, TextAlign);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, TextVerticalAlign, ParagraphVerticalAlign);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, MaxLines, MaxLines);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, WordBreak, WordBreak);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, EllipsisMode, EllipsisMode);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, LineBreakStrategy, LineBreakStrategy);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, IsOnlyBetweenLines, IsOnlyBetweenLines);
    UPDATE_SPAN_TEXT_STYLE(textLineStyle, ParagraphSpacing, ParagraphSpacing);
    UpdateReLayoutGradient(spanTextStyle, textStyle);
}

void SpanItem::UpdateReLayoutGradient(TextStyle& spanTextStyle, const TextStyle& textStyle)
{
    if (textStyle.GetGradient().has_value()) {
        auto gradient = textStyle.GetGradient();
        spanTextStyle.SetGradient(gradient);
    } else {
        spanTextStyle.SetGradient(std::nullopt);
    }
}

bool SpanItem::UpdateSymbolSpanFontFamily(TextStyle& symbolSpanStyle)
{
    auto symbolType = symbolSpanStyle.GetSymbolType();
    std::vector<std::string> fontFamilies;
    if (symbolType == SymbolType::CUSTOM) {
        auto symbolFontFamily = symbolSpanStyle.GetFontFamilies();
        for (auto& name : symbolFontFamily) {
            if (name.find(CUSTOM_SYMBOL_SUFFIX) != std::string::npos) {
                fontFamilies.push_back(name);
                break;
            }
        }
        if (fontFamilies.empty()) {
            return false;
        }
        symbolSpanStyle.SetFontFamilies(fontFamilies);
    } else {
        fontFamilies.push_back(DEFAULT_SYMBOL_FONTFAMILY);
        symbolSpanStyle.SetFontFamilies(fontFamilies);
    }
    return true;
}

void SpanItem::UpdateSymbolSpanParagraph(
    const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle, const RefPtr<Paragraph>& builder, bool isDragging)
{
    CHECK_NULL_VOID(builder);
    auto symbolSpanStyle = textStyle;
    auto symbolUnicode = GetSymbolUnicode();
    symbolSpanStyle.SetTextStyleUid(nodeId_);
    if (fontStyle || textLineStyle) {
        UseSelfStyle(fontStyle, textLineStyle, symbolSpanStyle, true);
        if (fontStyle && fontStyle->HasFontWeight()) {
            symbolSpanStyle.SetEnableVariableFontWeight(false);
        }
        if (frameNode) {
            FontRegisterCallback(frameNode, symbolSpanStyle);
        }
        if (symbolUnicode != 0) {
            UpdateSymbolSpanColor(frameNode, symbolSpanStyle);
        }
        if (!symbolEffectSwitch_ || isDragging) {
            symbolSpanStyle.SetEffectStrategy(0);
        }
        if (!UpdateSymbolSpanFontFamily(symbolSpanStyle)) {
            return;
        }
        builder->PushStyle(symbolSpanStyle);
    }
    textStyle_ = symbolSpanStyle;

    if (symbolUnicode != 0) {
        textStyle_->isSymbolGlyph_ = true;
        builder->AddSymbol(symbolUnicode);
    }

    if (fontStyle || textLineStyle) {
        builder->PopStyle();
    }
}

void SpanItem::UpdateSymbolSpanColor(const RefPtr<FrameNode>& frameNode, TextStyle& symbolSpanStyle)
{
    symbolSpanStyle.isSymbolGlyph_ = true;
    CHECK_NULL_VOID(frameNode);
    if (GetIsParentText() && symbolSpanStyle.GetSymbolColorList().empty()) {
        RefPtr<LayoutProperty> layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        RefPtr<TextLayoutProperty> textLayoutProperty = DynamicCast<TextLayoutProperty>(layoutProperty);
        CHECK_NULL_VOID(textLayoutProperty);
        if (textLayoutProperty->GetTextColor().has_value()) {
            std::vector<Color> symbolColor;
            symbolColor.emplace_back(textLayoutProperty->GetTextColor().value());
            symbolSpanStyle.SetSymbolColorList(symbolColor);
        }
    }
}

void SpanItem::UpdateTextStyleForAISpan(const std::u16string& spanContent, const RefPtr<Paragraph>& builder,
    const TextStyle& textStyle, const TextStyle& aiSpanStyle)
{
    int32_t spanContentLength = static_cast<int32_t>(spanContent.length());
    int32_t spanStart = this->position - spanContentLength;
    if (needRemoveNewLine) {
        spanStart -= 1;
    }
    int32_t preEnd = spanStart;
    while (!aiSpanMap.empty()) {
        auto aiSpan = aiSpanMap.begin()->second;
        if (aiSpan.start >= this->position || preEnd >= this->position) {
            break;
        }
        int32_t aiSpanStartInSpan = std::max(spanStart, aiSpan.start);
        int32_t aiSpanEndInSpan = std::min(position, aiSpan.end);
        if (aiSpan.end <= spanStart || aiSpanStartInSpan < preEnd) {
            TAG_LOGI(AceLogTag::ACE_TEXT, "Error prediction");
            aiSpanMap.erase(aiSpanMap.begin());
            continue;
        }
        /*
        | content has been handled | normal text | aiSpan text style | remain text   |
        spanStart(fix)             preEnd        aiSpanStartInSpan   aiSpanEndInSpan spanStart + spanContentLength(fix)
        */
        int32_t contentStart = preEnd - spanStart;
        if (preEnd < aiSpanStartInSpan) {
            contentStart = std::clamp(contentStart, 0, static_cast<int32_t>(spanContent.length()));
            UpdateTextStyle(spanContent.substr(contentStart, aiSpanStartInSpan - preEnd),
                builder, textStyle, this->selectedStart - contentStart, this->selectedEnd - contentStart);
            contentStart = contentStart + aiSpanStartInSpan - preEnd; // aiSpan's relative offset from span
        }
        auto startIndex = aiSpanStartInSpan - aiSpan.start;
        startIndex = std::clamp(startIndex, 0, static_cast<int32_t>(
            UtfUtils::Str8DebugToStr16(aiSpan.content).length()));
        auto displayContent = UtfUtils::Str8DebugToStr16(aiSpan.content)
            .substr(startIndex, aiSpanEndInSpan - aiSpanStartInSpan);
        UpdateTextStyle(displayContent, builder, aiSpanStyle,
            this->selectedStart - contentStart, this->selectedEnd - contentStart);
        preEnd = aiSpanEndInSpan;
        if (aiSpan.end > position) {
            return;
        } else {
            aiSpanMap.erase(aiSpanMap.begin());
        }
    }
    if (preEnd < position) {
        int32_t contentStart = preEnd - spanStart;
        contentStart = std::clamp(contentStart, 0, static_cast<int32_t>(spanContent.length()));
        UpdateTextStyle(spanContent.substr(contentStart, position - preEnd),
            builder, textStyle, selectedStart - contentStart, selectedEnd - contentStart);
    }
}

void SpanItem::FontRegisterCallback(const RefPtr<FrameNode>& frameNode, const TextStyle& textStyle)
{
    auto callback = [weakNode = WeakPtr<FrameNode>(frameNode)] {
        auto frameNode = weakNode.Upgrade();
        CHECK_NULL_VOID(frameNode);
        frameNode->MarkDirtyNode(PROPERTY_UPDATE_MEASURE);
        auto pattern = frameNode->GetPattern<TextPattern>();
        CHECK_NULL_VOID(pattern);
        auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
        CHECK_NULL_VOID(modifier);
        modifier->SetFontReady(true);
        auto layoutProperty = frameNode->GetLayoutProperty();
        CHECK_NULL_VOID(layoutProperty);
        layoutProperty->OnPropertyChangeMeasure();
    };
    auto pipeline = frameNode->GetContext();
    CHECK_NULL_VOID(pipeline);
    auto fontManager = pipeline->GetFontManager();
    if (fontManager) {
        bool isCustomFont = false;
        for (const auto& familyName : textStyle.GetFontFamilies()) {
            bool customFont = fontManager->RegisterCallbackNG(frameNode, familyName, callback);
            if (customFont) {
                isCustomFont = true;
            }
        }
        if (isCustomFont) {
            auto pattern = frameNode->GetPattern<TextPattern>();
            CHECK_NULL_VOID(pattern);
            pattern->SetIsCustomFont(true);
            auto modifier = DynamicCast<TextContentModifier>(pattern->GetContentModifier());
            CHECK_NULL_VOID(modifier);
            modifier->SetIsCustomFont(true);
        }
    }
}

void SpanItem::UpdateTextStyle(const std::u16string& content, const RefPtr<Paragraph>& builder,
    const TextStyle& textStyle, int32_t selStart, int32_t selEnd)
{
    if (!IsDragging()) {
        UpdateContentTextStyle(content, builder, textStyle);
    } else {
        // for content such as Hellow Wrold, update text style for three parts:
        // [0, selStart), [selStart, selEnd), [selEnd, content.length) through UpdateContentTextStyle
        auto contentLength = static_cast<int32_t>(content.length());
        selStart = selStart < 0 ? 0: selStart;
        selEnd = selEnd < 0 ? 0 : selEnd;
        selEnd = selEnd > contentLength ? contentLength : selEnd;
        if (content.empty()) {
            builder->PushStyle(textStyle);
            builder->PopStyle();
            return;
        }
        if (selStart > 0) {
            UpdateContentTextStyle(
                TextEmojiProcessor::SubU16string(0, selStart, content, false, true), builder, textStyle);
        }
        if (selStart < contentLength) {
            TextStyle selectedTextStyle = textStyle;
            Color color = selectedTextStyle.GetTextColor().ChangeAlpha(DRAGGED_TEXT_OPACITY);
            selectedTextStyle.SetTextColor(color);
            Color textDecorationColor = selectedTextStyle.GetTextDecorationColor().ChangeAlpha(DRAGGED_TEXT_OPACITY);
            selectedTextStyle.SetTextDecorationColor(textDecorationColor);
            UpdateContentTextStyle(
                TextEmojiProcessor::SubU16string(selStart, selEnd - selStart, content, false, true),
                builder, selectedTextStyle);
        }
        if (selEnd < contentLength) {
            UpdateContentTextStyle(
                TextEmojiProcessor::SubU16string(selEnd, content.length() - selEnd, content, false, true),
                builder, textStyle);
        }
    }
}

void SpanItem::UpdateContentTextStyle(
    const std::u16string& content, const RefPtr<Paragraph>& builder, const TextStyle& textStyle)
{
    builder->PushStyle(textStyle);
    if (!content.empty()) {
        auto displayText = content;
        auto textCase = textStyle.GetTextCase();
        StringUtils::TransformStrCase(displayText, static_cast<int32_t>(textCase));
        UtfUtils::HandleInvalidUTF16(reinterpret_cast<uint16_t*>(displayText.data()), displayText.length(), 0);
        builder->AddText(displayText);
    }
    builder->PopStyle();
}

std::u16string SpanItem::GetSpanContent(const std::u16string& rawContent, bool isMarquee)
{
    std::u16string data;
    if (needRemoveNewLine && !rawContent.empty()) {
        data = rawContent.substr(0, static_cast<int32_t>(rawContent.length()) - 1);
    } else {
        data = rawContent;
    }
    if (isMarquee) {
        std::replace(data.begin(), data.end(), u'\n', u' ');
    }
    return data;
}

std::u16string SpanItem::GetSpanContent()
{
    return content;
}

uint32_t SpanItem::GetSymbolUnicode()
{
    return unicode;
}

void SpanItem::StartDrag(int32_t start, int32_t end)
{
    selectedStart = std::max(0, start);
    auto contentLen = static_cast<int32_t>(content.size());
    selectedEnd = std::min(contentLen, end);
}

void SpanItem::EndDrag()
{
    selectedStart = -1;
    selectedEnd = -1;
}

bool SpanItem::IsDragging()
{
    return selectedStart >= 0 && selectedEnd >= 0;
}

ResultObject SpanItem::GetSpanResultObject(int32_t start, int32_t end)
{
    bool selectFlag = true;
    ResultObject resultObject;
    int32_t endPosition = interval.second;
    int32_t startPosition = interval.first;
    int32_t itemLength = endPosition - startPosition;

    if (startPosition >= start && endPosition <= end) {
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition < start && endPosition <= end && endPosition > start) {
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
    } else if (startPosition >= start && startPosition < end && endPosition >= end) {
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    } else if (startPosition <= start && endPosition >= end) {
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = start - startPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = end - startPosition;
    } else {
        selectFlag = false;
    }
    if (selectFlag) {
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.type = SelectSpanType::TYPESPAN;
        resultObject.valueString = content;
        resultObject.span = WeakClaim(this);
        resultObject.isInit = true;
    }
    return resultObject;
}

#define COPY_TEXT_STYLE(group, name, func)                      \
    do {                                                        \
        if ((group)->Has##name()) {                             \
            sameSpan->group->func((group)->prop##name.value()); \
        }                                                       \
    } while (false)

RefPtr<SpanItem> SpanItem::GetSameStyleSpanItem(bool isEncodeTlvS) const
{
    auto sameSpan = MakeRefPtr<SpanItem>();
    GetFontStyleSpanItem(sameSpan);
    COPY_TEXT_STYLE(textLineStyle, LineHeight, UpdateLineHeight);
    COPY_TEXT_STYLE(textLineStyle, LineSpacing, UpdateLineSpacing);
    COPY_TEXT_STYLE(textLineStyle, OptimizeTrailingSpace, UpdateOptimizeTrailingSpace);
    COPY_TEXT_STYLE(textLineStyle, TextBaseline, UpdateTextBaseline);
    COPY_TEXT_STYLE(textLineStyle, BaselineOffset, UpdateBaselineOffset);
    COPY_TEXT_STYLE(textLineStyle, TextOverflow, UpdateTextOverflow);
    COPY_TEXT_STYLE(textLineStyle, TextAlign, UpdateTextAlign);
    COPY_TEXT_STYLE(textLineStyle, TextVerticalAlign, UpdateTextVerticalAlign);
    COPY_TEXT_STYLE(textLineStyle, MaxLength, UpdateMaxLength);
    COPY_TEXT_STYLE(textLineStyle, MaxLines, UpdateMaxLines);
    COPY_TEXT_STYLE(textLineStyle, HeightAdaptivePolicy, UpdateHeightAdaptivePolicy);
    COPY_TEXT_STYLE(textLineStyle, TextIndent, UpdateTextIndent);
    COPY_TEXT_STYLE(textLineStyle, LeadingMargin, UpdateLeadingMargin);
    COPY_TEXT_STYLE(textLineStyle, WordBreak, UpdateWordBreak);
    COPY_TEXT_STYLE(textLineStyle, LineBreakStrategy, UpdateLineBreakStrategy);
    COPY_TEXT_STYLE(textLineStyle, EllipsisMode, UpdateEllipsisMode);
    COPY_TEXT_STYLE(textLineStyle, HalfLeading, UpdateHalfLeading);
    COPY_TEXT_STYLE(textLineStyle, ParagraphSpacing, UpdateParagraphSpacing);
    if (textStyle_.has_value()) {
        sameSpan->textStyle_ = textStyle_;
    }
    if (backgroundStyle.has_value()) {
        sameSpan->backgroundStyle = backgroundStyle;
    }
    sameSpan->urlAddress = urlAddress;
    sameSpan->urlOnRelease = urlOnRelease;
    sameSpan->onClick = onClick;
    sameSpan->onLongPress = onLongPress;
    sameSpan->onTouch = onTouch;
    return sameSpan;
}

void SpanItem::GetFontStyleSpanItem(RefPtr<SpanItem>& sameSpan) const
{
    COPY_TEXT_STYLE(fontStyle, FontSize, UpdateFontSize);
    COPY_TEXT_STYLE(fontStyle, TextColor, UpdateTextColor);
    COPY_TEXT_STYLE(fontStyle, TextShadow, UpdateTextShadow);
    COPY_TEXT_STYLE(fontStyle, ItalicFontStyle, UpdateItalicFontStyle);
    COPY_TEXT_STYLE(fontStyle, Superscript, UpdateSuperscript);
    COPY_TEXT_STYLE(fontStyle, FontWeight, UpdateFontWeight);
    COPY_TEXT_STYLE(fontStyle, FontFamily, UpdateFontFamily);
    COPY_TEXT_STYLE(fontStyle, FontFeature, UpdateFontFeature);
    COPY_TEXT_STYLE(fontStyle, StrokeWidth, UpdateStrokeWidth);
    COPY_TEXT_STYLE(fontStyle, StrokeColor, UpdateStrokeColor);
    COPY_TEXT_STYLE(fontStyle, TextDecoration, UpdateTextDecoration);
    COPY_TEXT_STYLE(fontStyle, TextDecorationColor, UpdateTextDecorationColor);
    COPY_TEXT_STYLE(fontStyle, TextDecorationStyle, UpdateTextDecorationStyle);
    COPY_TEXT_STYLE(fontStyle, LineThicknessScale, UpdateLineThicknessScale);
    COPY_TEXT_STYLE(fontStyle, TextCase, UpdateTextCase);
    COPY_TEXT_STYLE(fontStyle, AdaptMinFontSize, UpdateAdaptMinFontSize);
    COPY_TEXT_STYLE(fontStyle, AdaptMaxFontSize, UpdateAdaptMaxFontSize);
    COPY_TEXT_STYLE(fontStyle, LetterSpacing, UpdateLetterSpacing);
    COPY_TEXT_STYLE(fontStyle, MinFontScale, UpdateMinFontScale);
    COPY_TEXT_STYLE(fontStyle, MaxFontScale, UpdateMaxFontScale);
}

#define WRITE_TLV_INHERIT(group, name, tag, type, inheritName)   \
    if ((group)->Has##name()) {                                  \
        TLVUtil::WriteUint8(buff, (tag));                        \
        TLVUtil::Write##type(buff, (group)->prop##name.value()); \
    } else if (textStyle_.has_value()) {                         \
        auto temp##name = textStyle_->Get##inheritName();        \
        TLVUtil::WriteUint8(buff, (tag));                        \
        TLVUtil::Write##type(buff, temp##name);                  \
    }

#define WRITE_TEXT_STYLE_TLV(group, name, tag, type)                   \
    do {                                                               \
        if ((group)->Has##name()) {                                    \
            TLVUtil::WriteUint8(buff, (tag));                          \
            TLVUtil::Write##type(buff, (group)->prop##name.value());   \
        }                                                              \
    } while (false)

#define READ_TEXT_STYLE_TLV(group, func, tag, type)                         \
    case tag: {                                                             \
        sameSpan->group->func(TLVUtil::Read##type(buff, cursor));           \
        break;                                                              \
    }

bool SpanItem::EncodeTlv(std::vector<uint8_t>& buff)
{
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_TAG);
    TLVUtil::WriteInt32(buff, interval.first);
    TLVUtil::WriteInt32(buff, interval.second);
    TLVUtil::WriteU16String(buff, content);
    EncodeFontStyleTlv(buff);
    EncodeTextLineStyleTlv(buff);
    if (backgroundStyle.has_value()) {
        if (backgroundStyle->backgroundColor.has_value()) {
            TLVUtil::WriteUint8(buff, TLV_SPAN_BACKGROUND_BACKGROUNDCOLOR);
            TLVUtil::WriteColor(buff, backgroundStyle->backgroundColor.value());
        }
        if (backgroundStyle->backgroundRadius.has_value()) {
            TLVUtil::WriteUint8(buff, TLV_SPAN_BACKGROUND_BACKGROUNDRADIUS);
            TLVUtil::WriteBorderRadiusProperty(buff, backgroundStyle->backgroundRadius.value());
        }
        TLVUtil::WriteUint8(buff, TLV_SPAN_BACKGROUND_GROUPID);
        TLVUtil::WriteInt32(buff, backgroundStyle->groupId);
    }
    WRITE_TLV_INHERIT(textLineStyle, ParagraphSpacing, TLV_SPAN_TEXT_LINE_STYLE_PARAGRAPH_SPACING, Dimension,
        ParagraphSpacing);
    if (urlAddress.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_SPAN_URL_CONTENT);
        TLVUtil::WriteU16String(buff, GetUrlAddress());
    }
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    return true;
};

void SpanItem::EncodeFontStyleTlv(std::vector<uint8_t>& buff) const
{
    WRITE_TLV_INHERIT(fontStyle, FontSize, TLV_SPAN_FONT_STYLE_FONTSIZE, Dimension, FontSize);
    WRITE_TLV_INHERIT(fontStyle, TextColor, TLV_SPAN_FONT_STYLE_TEXTCOLOR, Color, TextColor);
    WRITE_TLV_INHERIT(fontStyle, TextShadow, TLV_SPAN_FONT_STYLE_TEXTSHADOW, TextShadows, TextShadows);
    WRITE_TLV_INHERIT(fontStyle, ItalicFontStyle, TLV_SPAN_FONT_STYLE_ITALICFONTSTYLE, FontStyle, FontStyle);
    WRITE_TLV_INHERIT(fontStyle, FontWeight, TLV_SPAN_FONT_STYLE_FONTWEIGHT, FontWeight, FontWeight);
    WRITE_TLV_INHERIT(fontStyle, FontFamily, TLV_SPAN_FONT_STYLE_FONTFAMILY, FontFamily, FontFamilies);
    WRITE_TLV_INHERIT(fontStyle, FontFeature, TLV_SPAN_FONT_STYLE_FONTFEATURE, FontFeature, FontFeatures);
    WRITE_TLV_INHERIT(fontStyle, StrokeWidth, TLV_SPAN_FONT_STYLE_STROKEWIDTH, Dimension, StrokeWidth);
    WRITE_TLV_INHERIT(fontStyle, StrokeColor, TLV_SPAN_FONT_STYLE_STROKECOLOR, Color, StrokeColor);
    WRITE_TLV_INHERIT(fontStyle, Superscript, TLV_SPAN_FONT_STYLE_SUPERSCRIPT, SuperscriptStyle, Superscript);
    WRITE_TLV_INHERIT(
        fontStyle, TextDecorationColor, TLV_SPAN_FONT_STYLE_TEXTDECORATIONCOLOR, Color, TextDecorationColor);
    WRITE_TLV_INHERIT(fontStyle, TextDecorationStyle, TLV_SPAN_FONT_STYLE_TEXTDECORATIONSTYLE, TextDecorationStyle,
        TextDecorationStyle);
    WRITE_TLV_INHERIT(fontStyle, TextCase, TLV_SPAN_FONT_STYLE_TEXTCASE, TextCase, TextCase);
    WRITE_TLV_INHERIT(fontStyle, AdaptMinFontSize, TLV_SPAN_FONT_STYLE_ADPATMINFONTSIZE, Dimension, AdaptMinFontSize);
    WRITE_TLV_INHERIT(fontStyle, AdaptMaxFontSize, TLV_SPAN_FONT_STYLE_ADPATMAXFONTSIZE, Dimension, AdaptMaxFontSize);
    WRITE_TLV_INHERIT(fontStyle, LetterSpacing, TLV_SPAN_FONT_STYLE_LETTERSPACING, Dimension, LetterSpacing);
    WRITE_TLV_INHERIT(fontStyle, LineThicknessScale, TLV_SPAN_FONT_STYLE_LineThicknessScale, Float,
        LineThicknessScale);
    if (fontStyle->HasTextDecoration()) {
        TLVUtil::WriteTextDecorations(buff, fontStyle->GetTextDecoration().value());
    } else if (textStyle_.has_value()) {
        TLVUtil::WriteTextDecorations(buff, textStyle_->GetTextDecoration());
    }
}

void SpanItem::EncodeTextLineStyleTlv(std::vector<uint8_t>& buff) const
{
    WRITE_TLV_INHERIT(textLineStyle, LineHeight, TLV_SPAN_TEXT_LINE_STYLE_LINEHEIGHT, Dimension, LineHeight);
    WRITE_TLV_INHERIT(textLineStyle, LineSpacing, TLV_SPAN_TEXT_LINE_STYLE_LINESPACING, Dimension, LineSpacing);
    WRITE_TLV_INHERIT(textLineStyle, TextBaseline, TLV_SPAN_TEXT_LINE_STYLE_TEXTBASELINE, TextBaseline, TextBaseline);
    // text's baselineOffset attribute is not span's baselineOffset attribute
    WRITE_TEXT_STYLE_TLV(textLineStyle, BaselineOffset, TLV_SPAN_TEXT_LINE_STYLE_BASELINEOFFSET, Dimension);
    WRITE_TLV_INHERIT(textLineStyle, TextOverflow, TLV_SPAN_TEXT_LINE_STYLE_TEXTOVERFLOW, TextOverflow, TextOverflow);
    WRITE_TLV_INHERIT(textLineStyle, TextAlign, TLV_SPAN_TEXT_LINE_STYLE_TEXTALIGN, TextAlign, TextAlign);
    WRITE_TEXT_STYLE_TLV(textLineStyle, MaxLength, TLV_SPAN_TEXT_LINE_STYLE_MAXLENGTH, Int32);
    WRITE_TLV_INHERIT(textLineStyle, MaxLines, TLV_SPAN_TEXT_LINE_STYLE_MAXLINES, Int32, MaxLines);
    WRITE_TEXT_STYLE_TLV(
        textLineStyle, HeightAdaptivePolicy, TLV_SPAN_TEXT_LINE_STYLE_HEIGHTADAPTIVEPOLICY, TextHeightAdaptivePolicy);
    WRITE_TLV_INHERIT(textLineStyle, TextIndent, TLV_SPAN_TEXT_LINE_STYLE_TEXTINDENT, Dimension, TextIndent);
    WRITE_TEXT_STYLE_TLV(textLineStyle, LeadingMargin, TLV_SPAN_TEXT_LINE_STYLE_LEADINGMARGIN, LeadingMargin);
    WRITE_TLV_INHERIT(textLineStyle, WordBreak, TLV_SPAN_TEXT_LINE_STYLE_WORDBREAK, WordBreak, WordBreak);
    WRITE_TLV_INHERIT(textLineStyle, LineBreakStrategy, TLV_SPAN_TEXT_LINE_STYLE_LINEBREAKSTRATEGY, LineBreakStrategy,
        LineBreakStrategy);
    WRITE_TLV_INHERIT(textLineStyle, EllipsisMode, TLV_SPAN_TEXT_LINE_STYLE_ELLIPSISMODE, EllipsisMode, EllipsisMode);
    WRITE_TLV_INHERIT(textLineStyle, TextVerticalAlign, TLV_SPAN_TEXT_LINE_STYLE_TEXTVERTICALALIGN, TextVerticalAlign,
        ParagraphVerticalAlign);
}

RefPtr<SpanItem> SpanItem::DecodeTlv(std::vector<uint8_t>& buff, int32_t& cursor)
{
    auto sameSpan = MakeRefPtr<SpanItem>();
    if (TLVUtil::ReadUint8(buff, cursor) != TLV_SPANITEM_TAG) {
        return sameSpan;
    }

    int32_t start = TLVUtil::ReadInt32(buff, cursor);
    int32_t end = TLVUtil::ReadInt32(buff, cursor);
    sameSpan->interval = {start, end};
    sameSpan->content = UtfUtils::Str8DebugToStr16(TLVUtil::ReadString(buff, cursor));

    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor);
        tag != TLV_SPANITEM_END_TAG; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            READ_TEXT_STYLE_TLV(fontStyle, UpdateFontSize, TLV_SPAN_FONT_STYLE_FONTSIZE, Dimension);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateTextColor, TLV_SPAN_FONT_STYLE_TEXTCOLOR, Color);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateTextShadow, TLV_SPAN_FONT_STYLE_TEXTSHADOW, TextShadows);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateItalicFontStyle, TLV_SPAN_FONT_STYLE_ITALICFONTSTYLE, FontStyle);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateFontWeight, TLV_SPAN_FONT_STYLE_FONTWEIGHT, FontWeight);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateFontFamily, TLV_SPAN_FONT_STYLE_FONTFAMILY, FontFamily);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateFontFeature, TLV_SPAN_FONT_STYLE_FONTFEATURE, FontFeature);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateStrokeWidth, TLV_SPAN_FONT_STYLE_STROKEWIDTH, Dimension);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateStrokeColor, TLV_SPAN_FONT_STYLE_STROKECOLOR, Color);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateSuperscript, TLV_SPAN_FONT_STYLE_SUPERSCRIPT, SuperscriptStyle);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateTextDecorationColor, TLV_SPAN_FONT_STYLE_TEXTDECORATIONCOLOR, Color);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateTextDecorationStyle,
                TLV_SPAN_FONT_STYLE_TEXTDECORATIONSTYLE, TextDecorationStyle);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateTextCase, TLV_SPAN_FONT_STYLE_TEXTCASE, TextCase);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateAdaptMinFontSize, TLV_SPAN_FONT_STYLE_ADPATMINFONTSIZE, Dimension);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateAdaptMaxFontSize, TLV_SPAN_FONT_STYLE_ADPATMAXFONTSIZE, Dimension);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateLetterSpacing, TLV_SPAN_FONT_STYLE_LETTERSPACING, Dimension);
            READ_TEXT_STYLE_TLV(fontStyle, UpdateLineThicknessScale, TLV_SPAN_FONT_STYLE_LineThicknessScale, Float);
            case TLV_SPAN_FONT_STYLE_TEXTDECORATION: {
                sameSpan->fontStyle->UpdateTextDecoration(TLVUtil::ReadTextDecorations(buff, cursor));
                break;
            }

            READ_TEXT_STYLE_TLV(textLineStyle, UpdateLineHeight, TLV_SPAN_TEXT_LINE_STYLE_LINEHEIGHT, Dimension);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateLineSpacing, TLV_SPAN_TEXT_LINE_STYLE_LINESPACING, Dimension);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateTextBaseline, TLV_SPAN_TEXT_LINE_STYLE_TEXTBASELINE, TextBaseline);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateBaselineOffset,
                TLV_SPAN_TEXT_LINE_STYLE_BASELINEOFFSET, Dimension);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateTextOverflow, TLV_SPAN_TEXT_LINE_STYLE_TEXTOVERFLOW, TextOverflow);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateTextAlign, TLV_SPAN_TEXT_LINE_STYLE_TEXTALIGN, TextAlign);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateMaxLength, TLV_SPAN_TEXT_LINE_STYLE_MAXLENGTH, Int32);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateMaxLines, TLV_SPAN_TEXT_LINE_STYLE_MAXLINES, Int32);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateHeightAdaptivePolicy,
                TLV_SPAN_TEXT_LINE_STYLE_HEIGHTADAPTIVEPOLICY, TextHeightAdaptivePolicy);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateTextIndent, TLV_SPAN_TEXT_LINE_STYLE_TEXTINDENT, Dimension);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateLeadingMargin,
                TLV_SPAN_TEXT_LINE_STYLE_LEADINGMARGIN, LeadingMargin);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateWordBreak, TLV_SPAN_TEXT_LINE_STYLE_WORDBREAK, WordBreak);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateLineBreakStrategy,
                TLV_SPAN_TEXT_LINE_STYLE_LINEBREAKSTRATEGY, LineBreakStrategy);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateEllipsisMode, TLV_SPAN_TEXT_LINE_STYLE_ELLIPSISMODE, EllipsisMode);
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateTextVerticalAlign, TLV_SPAN_TEXT_LINE_STYLE_TEXTVERTICALALIGN,
                TextVerticalAlign);

            case TLV_SPAN_BACKGROUND_BACKGROUNDCOLOR: {
                if (!sameSpan->backgroundStyle.has_value()) {
                    sameSpan->backgroundStyle = TextBackgroundStyle();
                }
                sameSpan->backgroundStyle->backgroundColor = TLVUtil::ReadColor(buff, cursor);
                break;
            }
            case TLV_SPAN_BACKGROUND_BACKGROUNDRADIUS: {
                sameSpan->backgroundStyle->backgroundRadius = TLVUtil::ReadBorderRadiusProperty(buff, cursor);
                break;
            }
            case TLV_SPAN_BACKGROUND_GROUPID: {
                sameSpan->backgroundStyle->groupId = TLVUtil::ReadInt32(buff, cursor);
                break;
            }
            READ_TEXT_STYLE_TLV(textLineStyle, UpdateParagraphSpacing,
                TLV_SPAN_TEXT_LINE_STYLE_PARAGRAPH_SPACING, Dimension);
            case TLV_SPAN_URL_CONTENT: {
                std::string address = TLVUtil::ReadString(buff, cursor);
                sameSpan->urlAddress = UtfUtils::Str8DebugToStr16(address);
                auto urlOnRelease = [address]() {
                    auto pipelineContext = PipelineContext::GetCurrentContextSafelyWithCheck();
                    CHECK_NULL_VOID(pipelineContext);
                    pipelineContext->HyperlinkStartAbility(address);
                };
                sameSpan->SetUrlOnReleaseEvent(std::move(urlOnRelease));
                break;
            }
            default:
                break;
        }
    }
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_NINETEEN)) {
        sameSpan->textLineStyle->ResetParagraphSpacing();
        sameSpan->urlAddress = std::nullopt;
        sameSpan->urlOnRelease = nullptr;
    }
    if (!Container::GreatOrEqualAPITargetVersion(PlatformVersion::VERSION_TWENTY)) {
        sameSpan->textLineStyle->ResetTextVerticalAlign();
    }
    return sameSpan;
}

std::string SpanItem::SymbolColorToString()
{
    auto colors = fontStyle->GetSymbolColorList();
    auto colorStr = std::string("[");
    if (colors.has_value()) {
        for (const auto& color : colors.value()) {
            colorStr.append(color.ColorToString());
            colorStr.append(",");
        }
    }
    colorStr.append("]");
    return colorStr;
}

std::optional<std::pair<int32_t, int32_t>> SpanItem::GetIntersectionInterval(std::pair<int32_t, int32_t> interval) const
{
    // Check the intersection
    if (this->interval.second <= interval.first || interval.second <= this->interval.first) {
        return std::nullopt;
    }

    // Calculate the intersection interval
    int32_t start = std::max(this->interval.first, interval.first);
    int32_t end = std::min(this->interval.second, interval.second);
    return std::make_optional<std::pair<int32_t, int32_t>>(std::make_pair(start, end));
}

bool ImageSpanItem::EncodeTlv(std::vector<uint8_t>& buff)
{
    if (spanItemType == SpanItemType::NORMAL) {
        // ImageSpan(resource)场景，复制图片为属性字符串为空格。ImageSpanItem::GetSameStyleSpanItem获取到的spanItemType为NORMAL
        TLVUtil::WriteUint8(buff, TLV_SPANITEM_TAG);
        TLVUtil::WriteInt32(buff, interval.first);
        TLVUtil::WriteInt32(buff, interval.second);
        TLVUtil::WriteU16String(buff, content);
        TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
        return true;
    }
    TLVUtil::WriteUint8(buff, TLV_IMAGESPANITEM_TAG);
    TLVUtil::WriteInt32(buff, interval.first);
    TLVUtil::WriteInt32(buff, interval.second);
    TLVUtil::WriteU16String(buff, content);
    if (options.offset.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_OFFSET_TAG);
        TLVUtil::WriteInt32(buff, options.offset.value());
    }
    if (options.image.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_IMAGE_TAG);
        TLVUtil::WriteString(buff, options.image.value());
    }
    if (options.bundleName.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_BUNDLENAME_TAG);
        TLVUtil::WriteString(buff, options.bundleName.value());
    }
    if (options.moduleName.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_MODULENAME_TAG);
        TLVUtil::WriteString(buff, options.moduleName.value());
    }
    if (options.imagePixelMap.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_IMAGEPIXELMAP_TAG);
        TLVUtil::WritePixelMap(buff, options.imagePixelMap.value());
    }
    if (options.imageAttribute.has_value()) {
        TLVUtil::WriteUint8(buff, TLV_IMAGESPANOPTION_IMAGEATTRIBUTE_TAG);
        TLVUtil::WriteImageSpanAttribute(buff, options.imageAttribute.value());
    }
    TLVUtil::WriteUint8(buff, TLV_SPANITEM_END_TAG);
    return true;
}

RefPtr<ImageSpanItem> ImageSpanItem::DecodeTlv(std::vector<uint8_t>& buff, int32_t& cursor)
{
    auto sameSpan = MakeRefPtr<ImageSpanItem>();

    if (TLVUtil::ReadUint8(buff, cursor) != TLV_IMAGESPANITEM_TAG) {
        return sameSpan;
    }

    int32_t start = TLVUtil::ReadInt32(buff, cursor);
    int32_t end = TLVUtil::ReadInt32(buff, cursor);
    sameSpan->interval = {start, end};
    sameSpan->content = UtfUtils::Str8DebugToStr16(TLVUtil::ReadString(buff, cursor));

    for (uint8_t tag = TLVUtil::ReadUint8(buff, cursor);
        tag != TLV_SPANITEM_END_TAG; tag = TLVUtil::ReadUint8(buff, cursor)) {
        switch (tag) {
            case TLV_IMAGESPANOPTION_OFFSET_TAG: {
                sameSpan->options.offset = TLVUtil::ReadInt32(buff, cursor);
                break;
            }
            case TLV_IMAGESPANOPTION_IMAGE_TAG: {
                sameSpan->options.image = TLVUtil::ReadString(buff, cursor);
                break;
            }
            case TLV_IMAGESPANOPTION_BUNDLENAME_TAG: {
                sameSpan->options.bundleName = TLVUtil::ReadString(buff, cursor);
                break;
            }
            case TLV_IMAGESPANOPTION_MODULENAME_TAG: {
                sameSpan->options.moduleName = TLVUtil::ReadString(buff, cursor);
                break;
            }
            case TLV_IMAGESPANOPTION_IMAGEPIXELMAP_TAG: {
                sameSpan->options.imagePixelMap = TLVUtil::ReadPixelMap(buff, cursor);
                break;
            }
            case TLV_IMAGESPANOPTION_IMAGEATTRIBUTE_TAG: {
                sameSpan->options.imageAttribute = TLVUtil::ReadImageSpanAttribute(buff, cursor);
                break;
            }
            default:
                break;
        }
    }
    return sameSpan;
}

bool ImageSpanItem::UpdatePlaceholderRun(PlaceholderStyle placeholderStyle)
{
    PlaceholderRun run;
    run.width = placeholderStyle.width;
    run.height = placeholderStyle.height;
    if (!NearZero(placeholderStyle.baselineOffset)) {
        run.baseline_offset = placeholderStyle.baselineOffset;
        run.alignment = PlaceholderAlignment::BASELINE;
    } else {
        run.alignment = GetPlaceHolderAlignmentFromVerticalAlign(placeholderStyle.verticalAlign);
    }
    auto needReCreate = run_ != run;
    run_ = run;
    return needReCreate;
}

void ImageSpanItem::UpdatePlaceholderBackgroundStyle(const RefPtr<FrameNode>& imageNode)
{
    CHECK_NULL_VOID(imageNode);
    auto property = imageNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_VOID(property);
    backgroundStyle = property->GetPlaceHolderStyle();
}

void ImageSpanItem::SetImageSpanOptions(const ImageSpanOptions& options)
{
    this->options = options;
}

void ImageSpanItem::ResetImageSpanOptions()
{
    options.imageAttribute.reset();
}

RefPtr<SpanItem> ImageSpanItem::GetSameStyleSpanItem(bool isEncodeTlvS) const
{
    auto sameSpan = MakeRefPtr<ImageSpanItem>();
    if (isEncodeTlvS) {
        if (options.HasValue()) {
            sameSpan->SetImageSpanOptions(options);
        } else {
            // 用与Text控件复制ImageSpan子控件，生成并保存options数据
            sameSpan->SetImageSpanOptions(GetImageSpanOptionsFromImageNode());
            if (!(sameSpan->options.imagePixelMap.value_or(nullptr))) {
                /*
                    ImageSpan子控件，存在resource和pixelMap两种来源。
                    ImageSpan(resource)场景，复制图片为属性字符串为空格。
                    因此设置为NORMAL。在ImageSpanItem::EncodeTlv时，SpanItemType为NORMAL时，组装SpanItem。
                */
                sameSpan->spanItemType = SpanItemType::NORMAL;
            }
        }
    } else {
        sameSpan->SetImageSpanOptions(options);
    }
    sameSpan->urlOnRelease = urlOnRelease;
    sameSpan->onClick = onClick;
    sameSpan->onLongPress = onLongPress;
    if (backgroundStyle.has_value()) {
        sameSpan->backgroundStyle = backgroundStyle;
    }
    return sameSpan;
}

ImageSpanOptions ImageSpanItem::GetImageSpanOptionsFromImageNode() const
{
    ImageSpanOptions imageSpanOptions;
    auto frameNode = FrameNode::GetFrameNode(V2::IMAGE_ETS_TAG, nodeId_);
    CHECK_NULL_RETURN(frameNode, imageSpanOptions);
    auto layoutProperty = frameNode->GetLayoutProperty<ImageLayoutProperty>();
    CHECK_NULL_RETURN(layoutProperty, imageSpanOptions);
    auto sourceInfo = layoutProperty->GetImageSourceInfo();
    if (sourceInfo.has_value()) {
        imageSpanOptions.image = sourceInfo->GetSrc();
        imageSpanOptions.bundleName = sourceInfo->GetBundleName();
        imageSpanOptions.moduleName = sourceInfo->GetModuleName();
        imageSpanOptions.imagePixelMap = sourceInfo->GetPixmap();
    }
    imageSpanOptions.imageAttribute = CreateImageSpanAttribute(layoutProperty);
    auto renderContext = frameNode->GetRenderContext();
    if (renderContext && renderContext->HasBorderRadius()) {
        imageSpanOptions.imageAttribute->borderRadius = renderContext->GetBorderRadius();
    }
    return imageSpanOptions;
}

ImageSpanAttribute ImageSpanItem::CreateImageSpanAttribute(const RefPtr<ImageLayoutProperty>& layoutProperty) const
{
    ImageSpanAttribute imageSpanAttribute;
    auto& layoutConstraint = layoutProperty->GetCalcLayoutConstraint();

    if (layoutConstraint && layoutConstraint->selfIdealSize) {
        auto width = layoutConstraint->selfIdealSize->Width();
        auto height = layoutConstraint->selfIdealSize->Height();
        ImageSpanSize imageSpanSize;
        if (width.has_value()) {
            imageSpanSize.width = width->GetDimension();
        }
        if (height.has_value()) {
            imageSpanSize.height = height->GetDimension();
        }
        imageSpanAttribute.size = imageSpanSize;
    }
    imageSpanAttribute.verticalAlign = layoutProperty->GetVerticalAlign();
    imageSpanAttribute.objectFit = layoutProperty->GetImageFit();
    auto& margin = layoutProperty->GetMarginProperty();
    if (margin) {
        MarginProperty marginProperty;
        marginProperty.UpdateWithCheck(*margin);
        imageSpanAttribute.marginProp = marginProperty;
    }
    auto& padding = layoutProperty->GetPaddingProperty();
    if (padding) {
        MarginProperty paddingProperty;
        paddingProperty.UpdateWithCheck(*padding);
        imageSpanAttribute.paddingProp = paddingProperty;
    }
    return imageSpanAttribute;
}

ResultObject ImageSpanItem::GetSpanResultObject(int32_t start, int32_t end)
{
    int32_t itemLength = 1;
    ResultObject resultObject;

    int32_t endPosition = interval.second;
    int32_t startPosition = interval.first;
    resultObject.type = SelectSpanType::TYPEIMAGE;
    if ((start <= startPosition) && (end >= endPosition)) {
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
        if (options.image.has_value()) {
            resultObject.valueString = UtfUtils::Str8DebugToStr16(options.image.value());
        }
        if (options.imagePixelMap.has_value()) {
            resultObject.valuePixelMap = options.imagePixelMap.value();
        }
        resultObject.isInit = true;
    }
    return resultObject;
}

ResultObject CustomSpanItem::GetSpanResultObject(int32_t start, int32_t end)
{
    int32_t itemLength = 1;
    ResultObject resultObject;

    int32_t endPosition = interval.second;
    int32_t startPosition = interval.first;
    resultObject.type = SelectSpanType::TYPEBUILDERSPAN;
    if ((start <= startPosition) && (end >= endPosition)) {
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGESTART] = startPosition;
        resultObject.spanPosition.spanRange[RichEditorSpanRange::RANGEEND] = endPosition;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGESTART] = 0;
        resultObject.offsetInSpan[RichEditorSpanRange::RANGEEND] = itemLength;
        resultObject.valueString = u" ";
        resultObject.isInit = true;
    }
    return resultObject;
}

bool SpanItem::UpdateSpanTextColor(Color color)
{
    auto pattern = pattern_.Upgrade();
    CHECK_NULL_RETURN(pattern, false);
    auto textPattern = DynamicCast<TextPattern>(pattern);
    CHECK_NULL_RETURN(textPattern, false);
    auto paragraphManager = textPattern->GetParagraphManager();
    CHECK_NULL_RETURN(paragraphManager, false);
    auto paragraphInfos = paragraphManager->GetParagraphs();
    if (paragraphIndex != 0 || paragraphInfos.size() != 1) {
        return false;
    }
    auto iter = paragraphInfos.begin();
    auto paragraphInfo = *iter;
    auto paragraph = paragraphInfo.paragraph;
    CHECK_NULL_RETURN(paragraph, false);
    CHECK_NULL_RETURN(paragraph, false);
    if (SystemProperties::GetTextTraceEnabled()) {
        ACE_TEXT_SCOPED_TRACE("UpdateSpanTextColor[id:%d][color:%s][position:%d][length:%d]", nodeId_,
            color.ColorToString().c_str(), position, length);
    }
    paragraph->UpdateColor(position - length, position, color);
    textPattern->MarkDirtyNodeRender();
    return true;
}

void SpanItem::GetIndex(int32_t& start, int32_t& end) const
{
    auto contentLen = content.length();
    start = position - contentLen;
    end = position;
}

bool PlaceholderSpanItem::UpdatePlaceholderRun(PlaceholderStyle placeholderStyle)
{
    PlaceholderRun run;
    run.width = placeholderStyle.width;
    run.height = placeholderStyle.height;
    auto needReCreate = run_ != run;
    run_ = run;
    return needReCreate;
}

int32_t PlaceholderSpanItem::UpdateParagraph(const RefPtr<FrameNode>& /* frameNode */, const RefPtr<Paragraph>& builder,
    const TextStyle& textStyle, bool /* isMarquee*/)
{
    CHECK_NULL_RETURN(builder, -1);
    auto spanTextStyle = textStyle;
    // ignore decoration styles
    spanTextStyle.SetTextDecoration(TextDecoration::NONE);
    spanTextStyle.SetTextBackgroundStyle(backgroundStyle);
    spanTextStyle.SetTextStyleUid(nodeId_);
    builder->PushStyle(spanTextStyle);
    int32_t index = builder->AddPlaceholder(run_);
    builder->PopStyle();
    textStyle_ = spanTextStyle;
    return index;
}

bool PlaceholderSpanItem::UpdateSpanTextStyle(const TextStyle& textStyle, const RefPtr<FrameNode>& frameNode)
{
    CHECK_NULL_RETURN(textStyle_.has_value(), true);
    UpdateReLayoutTextStyle(textStyle_.value(), textStyle, false);
    textStyle_->SetTextDecoration(TextDecoration::NONE);
    textStyle_->SetTextBackgroundStyle(backgroundStyle);
    textStyle_->SetTextStyleUid(nodeId_);
    return textStyle_.value().NeedReCreateParagraph();
}

void PlaceholderSpanItem::DumpInfo() const
{
    auto& dumpLog = DumpLog::GetInstance();
    dumpLog.AddDesc("--------------- print run info ---------------");
    dumpLog.AddDesc(std::string("Width: ").append(std::to_string(run_.width)));
    dumpLog.AddDesc(std::string("Height: ").append(std::to_string(run_.height)));
    dumpLog.AddDesc(std::string("Alignment: ").append(StringUtils::ToString(run_.alignment)));
    dumpLog.AddDesc(std::string("Baseline: ").append(StringUtils::ToString(run_.baseline)));
    dumpLog.AddDesc(std::string("BaselineOffset: ").append(std::to_string(run_.baseline_offset)));
    dumpLog.AddDesc("--------------- print text style ---------------");
    auto textStyle = textStyle_.value_or(TextStyle());
    dumpLog.AddDesc(
        std::string("FontSize: ")
            .append(textStyle.GetFontSize().ToString())
            .append(" self: ")
            .append(fontStyle && fontStyle->HasFontSize() ? fontStyle->GetFontSizeValue().ToString() : "Na"));
    dumpLog.AddDesc(
        std::string("TextColor: ")
            .append(textStyle.GetTextColor().ColorToString())
            .append(" self: ")
            .append(fontStyle && fontStyle->HasTextColor() ? fontStyle->GetTextColorValue().ColorToString() : "Na"));
    dumpLog.AddDesc(std::string("BaselineOffset: ")
                        .append(textStyle.GetBaselineOffset().ToString())
                        .append(" self: ")
                        .append(textLineStyle && textLineStyle->HasBaselineOffset()
                                    ? textLineStyle->GetBaselineOffsetValue().ToString()
                                    : "Na"));
    dumpLog.AddDesc(
        std::string("LineHeight: ")
            .append(textStyle.GetLineHeight().ToString())
            .append(" self: ")
            .append(textLineStyle
                        ? textLineStyle->GetLineHeight().value_or(Dimension(0.0, DimensionUnit::FP)).ToString()
                        : "Na"));
    dumpLog.AddDesc(
        std::string("LineSpacing: ")
            .append(textStyle.GetLineSpacing().ToString())
            .append(" isOnlyBetweenLines: ")
            .append((textStyle.GetIsOnlyBetweenLines()) ? "true" : "false"));
    dumpLog.AddDesc(std::string("VerticalAlign: ").append(StringUtils::ToString(textStyle.GetTextVerticalAlign())));
    dumpLog.AddDesc(std::string("HalfLeading: ").append(std::to_string(textStyle.GetHalfLeading())));
    dumpLog.AddDesc(std::string("TextBaseline: ").append(StringUtils::ToString(textStyle.GetTextBaseline())));
}

RefPtr<SpanItem> CustomSpanItem::GetSameStyleSpanItem(bool isEncodeTlvS) const
{
    auto sameSpan = MakeRefPtr<CustomSpanItem>();
    sameSpan->onMeasure = onMeasure;
    sameSpan->onDraw = onDraw;
    sameSpan->urlOnRelease = urlOnRelease;
    sameSpan->onClick = onClick;
    sameSpan->onLongPress = onLongPress;
    if (backgroundStyle.has_value()) {
        sameSpan->backgroundStyle = backgroundStyle;
    }
    return sameSpan;
}

void BaseSpan::SetTextBackgroundStyle(const TextBackgroundStyle& style)
{
    textBackgroundStyle_ = style;
    textBackgroundStyle_->groupId = groupId_;
    SetHasTextBackgroundStyle(style.backgroundColor.has_value() || style.backgroundRadius.has_value());
    MarkTextDirty();
}

void ContainerSpanNode::ToJsonValue(std::unique_ptr<JsonValue>& json, const InspectorFilter& filter) const
{
    TextBackgroundStyle::ToJsonValue(json, GetTextBackgroundStyle(), filter);
}

void SpanNode::DumpInfo(std::unique_ptr<JsonValue>& json)
{
    json->Put("Content", UtfUtils::Str16DebugToStr8(spanItem_->content).c_str());
    auto textStyle = spanItem_->GetTextStyle();
    if (!textStyle) {
        return;
    }
    json->Put("FontSize", textStyle->GetFontSize().ToString().c_str());
    json->Put("LineHeight", textStyle->GetLineHeight().ToString().c_str());
    json->Put("LineSpacing", textStyle->GetLineSpacing().ToString().c_str());
    json->Put("isOnlyBetweenLines", (textStyle->GetIsOnlyBetweenLines()) ? "true" : "false");
    json->Put("BaselineOffset", textStyle->GetBaselineOffset().ToString().c_str());
    json->Put("WordSpacing", textStyle->GetWordSpacing().ToString().c_str());
    json->Put("TextIndent", textStyle->GetTextIndent().ToString().c_str());
    json->Put("LetterSpacing", textStyle->GetLetterSpacing().ToString().c_str());
    json->Put("TextColor", textStyle->GetTextColor().ColorToString().c_str());
    if (spanItem_ && spanItem_->fontStyle) {
        json->Put(
            "SpanTextColor", spanItem_->fontStyle->GetTextColor().value_or(Color::FOREGROUND).ColorToString().c_str());
    }
    json->Put("FontWeight", StringUtils::ToString(textStyle->GetFontWeight()).c_str());
    json->Put("FontStyle", StringUtils::ToString(textStyle->GetFontStyle()).c_str());
    json->Put("TextBaseline", StringUtils::ToString(textStyle->GetTextBaseline()).c_str());
    json->Put("TextOverflow", StringUtils::ToString(textStyle->GetTextOverflow()).c_str());
    json->Put("VerticalAlign", StringUtils::ToString(textStyle->GetTextVerticalAlign()).c_str());
    json->Put("TextAlign", StringUtils::ToString(textStyle->GetTextAlign()).c_str());
    json->Put("TextVerticalAlign", StringUtils::ToString(textStyle->GetParagraphVerticalAlign()).c_str());
    json->Put("WordBreak", StringUtils::ToString(textStyle->GetWordBreak()).c_str());
    json->Put("TextCase", StringUtils::ToString(textStyle->GetTextCase()).c_str());
    json->Put("EllipsisMode", StringUtils::ToString(textStyle->GetEllipsisMode()).c_str());
    json->Put("HalfLeading", std::to_string(textStyle->GetHalfLeading()).c_str());
    if (GetTag() == V2::SYMBOL_SPAN_ETS_TAG) {
        json->Put("SymbolColor", spanItem_->SymbolColorToString().c_str());
        json->Put("RenderStrategy", std::to_string(textStyle->GetRenderStrategy()).c_str());
        json->Put("EffectStrategy", std::to_string(textStyle->GetEffectStrategy()).c_str());
        json->Put("SymbolEffect",
            spanItem_->fontStyle->GetSymbolEffectOptions().value_or(NG::SymbolEffectOptions()).ToString().c_str());
    }
    json->Put("LineThicknessScale", std::to_string(textStyle->GetLineThicknessScale()).c_str());
}
} // namespace OHOS::Ace::NG

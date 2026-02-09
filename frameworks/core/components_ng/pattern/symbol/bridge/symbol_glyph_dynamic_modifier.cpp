/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
#include "core/components_ng/pattern/symbol/bridge/symbol_glyph_dynamic_module.h"

#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/symbol/bridge/arkts_native_symbol_glyph_bridge.h"
#include "core/components_ng/pattern/symbol/bridge/symbol_glyph_custom_modifier.h"
#include "core/components_ng/pattern/symbol/symbol_model_ng.h"
#include "core/components_ng/pattern/symbol/symbol_source_info.h"
#include "core/components_ng/pattern/text/text_layout_property.h"
#include "frameworks/bridge/common/utils/utils.h"

#ifdef INCLUDE_GENERATED_SOURCES
#include "core/components_ng/pattern/symbol/symbol_model_static.h"
#endif

namespace OHOS::Ace::NG {
namespace NodeModifier {
template<typename T>
void ProcessResourceObj(FrameNode* frameNode, std::string key, T value, void* objRawPtr);
} // namespace NodeModifier
namespace {
FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
void CreateSymbolGlyph(ArkUI_Uint32 symbolId)
{
    SymbolModelNG::CreateSymbolGlyph(static_cast<uint32_t>(symbolId));
}
void SetSymbolType(ArkUI_Uint32 value)
{
    SymbolModelNG::SetSymbolGlyphType(static_cast<::OHOS::Ace::SymbolType>(value));
}
void SetSymbolFontFamilies(std::vector<std::string>& familyNames)
{
    SymbolModelNG::SetSymbolFontFamilies(familyNames);
}
void JsClip(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetClipEdge(frameNode);
}
FontWeight ConvertStrToFontWeight(ArkUI_CharPtr weight, FontWeight defaultFontWeight = FontWeight::NORMAL)
{
    std::string weightStr(weight);
    return StringUtils::StringToFontWeight(weightStr, defaultFontWeight);
}

FontWeight ConvertIntToFontWeight(ArkUI_Int32 weight)
{
    static const std::unordered_map<ArkUI_Int32, FontWeight> fontWeightMap = {
        {100, FontWeight::W100},
        {200, FontWeight::W200},
        {300, FontWeight::W300},
        {400, FontWeight::W400},
        {500, FontWeight::W500},
        {600, FontWeight::W600},
        {700, FontWeight::W700},
        {800, FontWeight::W800},
        {900, FontWeight::W900},
    };
    auto weightFindIter = fontWeightMap.find(weight);
    if (weightFindIter != fontWeightMap.end()) {
        return weightFindIter->second;
    }
    return FontWeight::NORMAL;
}

void SetFontColor(ArkUINodeHandle node, ArkUI_Uint32* color, int32_t size)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    if (color != nullptr && size > 0) {
        colorArray.reserve(size);
        for (ArkUI_Int32 i = 0; i < size; i++) {
            colorArray.emplace_back(Color(color[i]));
        }
    }
    SymbolModelNG::SetFontColor(frameNode, colorArray);
}
void SetFontColorJs(ArkUINodeHandle node, ArkUI_Uint32* color, ArkUI_Int32 size,
    ArkUI_Int32* resIndexes, void** resObjects, ArkUI_Int32 resSize)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    if (color != nullptr && size > 0) {
        colorArray.reserve(size);
        for (ArkUI_Int32 i = 0; i < size; i++) {
            colorArray.emplace_back(Color(color[i]));
        }
    }
    SymbolModelNG::SetFontColor(frameNode, colorArray);

    if (!SystemProperties::ConfigChangePerform()) {
        return;
    }
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (resIndexes == nullptr || resObjects == nullptr || resSize <= 0) {
        pattern->UnRegisterResource("symbolColor");
        return;
    }

    std::vector<std::pair<int32_t, RefPtr<ResourceObject>>> resObjArr;
    resObjArr.reserve(resSize);
    for (ArkUI_Int32 i = 0; i < resSize; i++) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resObjects[i]));
        resObjArr.emplace_back(resIndexes[i], resObj);
    }
    SymbolModelNG::RegisterSymbolFontColorResource(frameNode, "symbolColor", colorArray, resObjArr);
}

void ResetFontColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    Color fontColor = theme->GetTextStyle().GetTextColor();
    std::vector<Color> colorArray = { fontColor };
    SymbolModelNG::SetFontColor(frameNode, colorArray);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("symbolColor");
    }
}

void SetFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, ArkUI_Int32 unit, void* fontSizeRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);

    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto theme = GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        SymbolModelNG::SetFontSize(frameNode, fontSize);
    } else {
        auto fontSizeVal = Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit));
        SymbolModelNG::SetFontSize(frameNode, fontSizeVal);
        NodeModifier::ProcessResourceObj<CalcDimension>(frameNode, "FontSize", fontSizeVal, fontSizeRawPtr);
    }
}

void ResetFontSize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto theme = GetTheme<TextTheme>();
    CHECK_NULL_VOID(theme);
    CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
    SymbolModelNG::SetFontSize(frameNode, fontSize);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontSize");
    }
}

void SetFontWeightStr(ArkUINodeHandle node, ArkUI_CharPtr weight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, ConvertStrToFontWeight(weight));
}

void SetFontWeight(ArkUINodeHandle node, ArkUI_Int32 weight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, ConvertIntToFontWeight(weight));
}

void ResetFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontWeight(frameNode, Ace::FontWeight::NORMAL);
}

void SetRenderingStrategy(ArkUINodeHandle node, ArkUI_Uint32 renderingStrategy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetRenderingStrategy(frameNode, renderingStrategy);
}

void ResetRenderingStrategy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetRenderingStrategy(frameNode, 0);
}

void SetEffectStrategy(ArkUINodeHandle node, ArkUI_Uint32 effectStrategy)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolEffect(frameNode, effectStrategy);
}

void ResetEffectStrategy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolEffect(frameNode, 0);
}

void SetSymbolGlyphInitialize(ArkUINodeHandle node, ArkUI_Uint32 symbolId)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolGlyphInitialize(frameNode, symbolId);
}

void SetCustomSymbolGlyphInitialize(ArkUINodeHandle node, ArkUI_Uint32 symbolId, ArkUI_CharPtr fontFamily)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string fontFamilyStr(fontFamily);
    SymbolModelNG::SetCustomSymbolGlyphInitialize(frameNode, symbolId, fontFamilyStr.c_str());
}

void ResetSymbolGlyphInitialize(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolGlyphInitialize(frameNode, 0);
}

void UpdateSymbolEffect(ArkUINodeHandle node, ArkUI_Uint32 symbolEffectType, ArkUI_Bool isActive,
    ArkUI_Int16 isTxtActiveSource)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::UpdateSymbolEffect(frameNode, symbolEffectType, isActive, isTxtActiveSource);
}

void SetMinFontScale(ArkUINodeHandle node, ArkUI_Float32 minFontScale, void* scaleRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (LessOrEqual(minFontScale, 0.0f)) {
        SymbolModelNG::SetMinFontScale(frameNode, 0.0f);
        return;
    }
    if (GreatOrEqual(minFontScale, 1.0f)) {
        SymbolModelNG::SetMinFontScale(frameNode, 1.0f);
        return;
    }
    SymbolModelNG::SetMinFontScale(frameNode, minFontScale);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MinFontScale", minFontScale, scaleRawPtr);
}

void ResetMinFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetMinFontScale(frameNode, 1.0f);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MinFontScale");
    }
}

void SetMaxFontScale(ArkUINodeHandle node, ArkUI_Float32 maxFontScale, void* scaleRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (LessOrEqual(maxFontScale, 1.0f)) {
        SymbolModelNG::SetMaxFontScale(frameNode, 1.0f);
        return;
    }
    SymbolModelNG::SetMaxFontScale(frameNode, maxFontScale);
    NodeModifier::ProcessResourceObj<float>(frameNode, "MaxFontScale", maxFontScale, scaleRawPtr);
}

void ResetMaxFontScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetMaxFontScale(frameNode, 1.0f);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("MaxFontScale");
    }
}

void SetSymbolEffectOptions(ArkUINodeHandle node, const NG::SymbolEffectOptions* options)
{
    CHECK_NULL_VOID(options);
    auto optionsCopy = *options;
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolEffectOptions(frameNode, optionsCopy);
}

void SetSymbolShadow(ArkUINodeHandle node, const SymbolShadow* shadow)
{
    CHECK_NULL_VOID(shadow);
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetSymbolShadow(frameNode, *shadow);
}

void ResetSymbolShadow(ArkUINodeHandle node)
{
    SymbolShadow shadow;
    SetSymbolShadow(node, &shadow);
}

void SetShaderStyle(ArkUINodeHandle node, const SymbolGradient* gradients, ArkUI_Int32 size)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<SymbolGradient> gradientVec;
    if (gradients != nullptr && size > 0) {
        gradientVec.assign(gradients, gradients + size);
    }
    SymbolModelNG::SetShaderStyle(frameNode, gradientVec);
}

void ResetShaderStyle(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::ResetShaderStyle(frameNode);
}

void SetFontColorWithPlaceholder(
    ArkUINodeHandle node, ArkUI_Uint32* color, ArkUI_Uint32 colorPlaceholder, int32_t size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::vector<Color> colorArray;
    for (int32_t i = 0; i < size; i++) {
        Color result = Color(color[i]);
        result.SetPlaceholder(static_cast<ColorPlaceholder>(colorPlaceholder));
        colorArray.emplace_back(result);
    }
    SymbolModelNG::SetFontColor(frameNode, colorArray);
}

void InitialSymbol(FrameNode* frameNode, ArkUI_Uint32 symbolId)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::InitialSymbol(frameNode, symbolId);
}
void SetFontSize(FrameNode* frameNode, const Dimension& value)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontSize(frameNode, value);
}
void SetFontColor(FrameNode* frameNode, const std::vector<Color>& symbolColor)
{
    CHECK_NULL_VOID(frameNode);
    SymbolModelNG::SetFontColor(frameNode, symbolColor);
}
ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = SymbolModelNG::CreateFrameNode(static_cast<int32_t>(nodeId));
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}
}

namespace NodeModifier {
const ArkUISymbolGlyphModifier* GetSymbolGlyphDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISymbolGlyphModifier modifier = {
        .create = CreateSymbolGlyph,
        .setSymbolFontFamilies = SetSymbolFontFamilies,
        .setSymbolGlyphType = SetSymbolType,
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setFontWeightStr = SetFontWeightStr,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setRenderingStrategy = SetRenderingStrategy,
        .resetRenderingStrategy = ResetRenderingStrategy,
        .setEffectStrategy = SetEffectStrategy,
        .resetEffectStrategy = ResetEffectStrategy,
        .setSymbolGlyphInitialize = SetSymbolGlyphInitialize,
        .resetSymbolGlyphInitialize = ResetSymbolGlyphInitialize,
        .updateSymbolEffect = UpdateSymbolEffect,
        .setMinFontScale = SetMinFontScale,
        .resetMinFontScale = ResetMinFontScale,
        .setMaxFontScale = SetMaxFontScale,
        .resetMaxFontScale = ResetMaxFontScale,
        .setCustomSymbolGlyphInitialize = SetCustomSymbolGlyphInitialize,
        .setFontColorWithPlaceholder = SetFontColorWithPlaceholder,
        .createFrameNode = CreateFrameNode,
        .jsClip = JsClip,
        .setSymbolEffectOptions = SetSymbolEffectOptions,
        .setSymbolShadow = SetSymbolShadow,
        .resetSymbolShadow = ResetSymbolShadow,
        .setShaderStyle = SetShaderStyle,
        .resetShaderStyle = ResetShaderStyle,
        .setFontColorJs = SetFontColorJs,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUISymbolGlyphModifier* GetCJUISymbolGlyphModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUISymbolGlyphModifier modifier = {
        .setFontColor = SetFontColor,
        .resetFontColor = ResetFontColor,
        .setFontSize = SetFontSize,
        .resetFontSize = ResetFontSize,
        .setFontWeightStr = SetFontWeightStr,
        .setFontWeight = SetFontWeight,
        .resetFontWeight = ResetFontWeight,
        .setRenderingStrategy = SetRenderingStrategy,
        .resetRenderingStrategy = ResetRenderingStrategy,
        .setEffectStrategy = SetEffectStrategy,
        .resetEffectStrategy = ResetEffectStrategy,
        .setSymbolGlyphInitialize = SetSymbolGlyphInitialize,
        .resetSymbolGlyphInitialize = ResetSymbolGlyphInitialize,
        .setMinFontScale = SetMinFontScale,
        .resetMinFontScale = ResetMinFontScale,
        .setMaxFontScale = SetMaxFontScale,
        .resetMaxFontScale = ResetMaxFontScale,
        .setCustomSymbolGlyphInitialize = SetCustomSymbolGlyphInitialize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
const ArkUISymbolGlyphCustomModifier* GetSymbolGlyphCustomModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUISymbolGlyphCustomModifier modifier = {
        .initialSymbol = InitialSymbol,
        .setFontSize = SetFontSize,
        .setFontColor = SetFontColor,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
template<typename T>
void ProcessResourceObj(FrameNode* frameNode, std::string key, T value, void* objRawPtr)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (objRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(objRawPtr));
        pattern->RegisterResource<T>(key, resObj, value);
    } else {
        pattern->UnRegisterResource(key);
    }
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

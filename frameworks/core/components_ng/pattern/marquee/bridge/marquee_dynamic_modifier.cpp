/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/marquee_modifier.h"

#include "bridge/common/utils/utils.h"
#include "core/common/dynamic_module_helper.h"
#include "core/components/text/text_theme.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/marquee/marquee_model_ng.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
MarqueeModel* GetMarqueeModelImpl()
{
    static auto loader = DynamicModuleHelper::GetInstance().GetLoaderByName("marquee");
    static MarqueeModel* instance = loader ? reinterpret_cast<MarqueeModel*>(loader->CreateModel()) : nullptr;
    return instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_ALLOW_SCALE = true;
constexpr Ace::FontWeight DEFAULT_FONT_WEIGHT = Ace::FontWeight::NORMAL;
const std::string DEFAULT_FONT_FAMILY = "cursive";
constexpr int32_t DEFAULT_MARQUEE_LOOP = -1;
constexpr double DEFAULT_STEP = 6.0;

FrameNode* GetFrameNode(ArkUINodeHandle node)
{
    return node ? reinterpret_cast<FrameNode*>(node) : ViewStackProcessor::GetInstance()->GetMainFrameNode();
}
} // namespace

void SetMarqueeFontSize(ArkUINodeHandle node, ArkUI_Float32 fontSize, int unit, void* fontSizeRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);

    if (fontSize < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        MarqueeModelNG::SetFontSize(frameNode, fontSize);
    } else {
        MarqueeModelNG::SetFontSize(frameNode, Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && fontSizeRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(fontSizeRawPtr));
        pattern->RegisterResource<CalcDimension>("FontSize", resObj,
            Dimension(fontSize, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    } else {
        pattern->UnRegisterResource("FontSize");
    }
}

void ResetMarqueeFontSize(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!isJsView) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        MarqueeModelNG::SetFontSize(frameNode, fontSize);
    } else {
        std::optional<Dimension> fontSizeOpt;
        MarqueeModelNG::SetFontSize(frameNode, fontSizeOpt);
    }
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("FontSize");
    }
}

void SetMarqueeFontColor(ArkUINodeHandle node, uint32_t color, void* resRawPtr)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetTextColor(frameNode, Color(color));
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (SystemProperties::ConfigChangePerform() && resRawPtr) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(resRawPtr));
        pattern->RegisterResource<Color>("TextColor", resObj, Color(color));
    } else {
        pattern->UnRegisterResource("TextColor");
    }
}
void ResetMarqueeFontColor(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<Color> colorOpt;
    MarqueeModelNG::SetTextColor(frameNode, colorOpt);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("TextColor");
    }
}
void SetMarqueeAllowScale(ArkUINodeHandle node, ArkUI_Bool allowScale)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, allowScale);
}

void ResetMarqueeAllowScale(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetAllowScale(frameNode, DEFAULT_ALLOW_SCALE);
}

void SetMarqueeFontWeight(ArkUINodeHandle node, const char* fontWeight)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, Framework::ConvertStrToFontWeight(fontWeight));
}

void ResetMarqueeFontWeight(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetFontWeight(frameNode, DEFAULT_FONT_WEIGHT);
}

void SetMarqueeFontFamily(ArkUINodeHandle node, const char* fontFamily)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
}

void ResetMarqueeFontFamily(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (!isJsView) {
        std::string familiesStr = DEFAULT_FONT_FAMILY;
        std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
        MarqueeModelNG::SetFontFamily(frameNode, fontFamilyResult);
    } else {
        std::vector<std::string> fontFamilies;
        MarqueeModelNG::SetFontFamily(frameNode, fontFamilies);
    }
}

void SetMarqueeUpdateStrategy(ArkUINodeHandle node, ArkUI_Uint32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, static_cast<OHOS::Ace::MarqueeUpdateStrategy>(value));
}

void ResetMarqueeUpdateStrategy(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetMarqueeUpdateStrategy(frameNode, OHOS::Ace::MarqueeUpdateStrategy::DEFAULT);
}

void SetMarqueeOnStart(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onStart = reinterpret_cast<std::function<void()>*>(callback);
        MarqueeModelNG::SetOnStart(frameNode, std::move(*onStart));
    } else {
        MarqueeModelNG::SetOnStart(frameNode, nullptr);
    }
}

void ResetMarqueeOnStart(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetOnStart(frameNode, nullptr);
}

void SetMarqueeOnBounce(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onBounce = reinterpret_cast<std::function<void()>*>(callback);
        MarqueeModelNG::SetOnBounce(frameNode, std::move(*onBounce));
    } else {
        MarqueeModelNG::SetOnBounce(frameNode, nullptr);
    }
}

void ResetMarqueeOnBounce(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetOnBounce(frameNode, nullptr);
}

void SetMarqueeOnFinish(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void()>*>(callback);
        MarqueeModelNG::SetOnFinish(frameNode, std::move(*onFinish));
    } else {
        MarqueeModelNG::SetOnFinish(frameNode, nullptr);
    }
}

void ResetMarqueeOnFinish(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetOnFinish(frameNode, nullptr);
}

void SetMarqueeSrcValue(ArkUINodeHandle node, ArkUI_CharPtr src)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(src);
    MarqueeModelNG::SetValue(frameNode, std::optional<std::string>(src));
}

void ResetMarqueeSrcValue(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::ResetValue(frameNode);
}

void SetMarqueePlayerStatus(ArkUINodeHandle node, ArkUI_Bool start)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetPlayerStatus(frameNode, std::optional<bool>(start));
}

void ResetMarqueePlayerStatus(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::ResetPlayerStatus(frameNode);
}

void SetMarqueeScrollAmount(ArkUINodeHandle node, ArkUI_Float64 step)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetScrollAmount(frameNode, std::optional<double>(step));
}

void ResetMarqueeScrollAmount(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::ResetScrollAmount(frameNode);
}

void SetMarqueeLoop(ArkUINodeHandle node, ArkUI_Int32 loop)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetLoop(frameNode, std::optional<int32_t>(loop));
}

void ResetMarqueeLoop(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::ResetLoop(frameNode);
}

void SetMarqueeDirection(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::SetDirection(frameNode, std::optional<MarqueeDirection>(static_cast<MarqueeDirection>(direction)));
}

void ResetMarqueeDirection(ArkUINodeHandle node)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    MarqueeModelNG::ResetDirection(frameNode);
}

ArkUINodeHandle CreateMarqueeFrameNode(ArkUI_Uint32 nodeId)
{
    auto frameNode = MarqueeModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void SetMarqueeFrameRateRange(ArkUINodeHandle node, ArkUI_Int32 minValue, ArkUI_Int32 maxValue,
    ArkUI_Int32 expectValue, ArkUI_Int32 value)
{
    auto* frameNode = GetFrameNode(node);
    CHECK_NULL_VOID(frameNode);
    auto frameRateRange = AceType::MakeRefPtr<FrameRateRange>(minValue, maxValue, expectValue);
    auto type = static_cast<MarqueeDynamicSyncSceneType>(value);
    MarqueeModelNG::SetMarqueeFrameRateRange(frameNode, frameRateRange, type);
}

#ifndef CROSS_PLATFORM
void SetMarqueeFontSizeImpl(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* fontSizeRawPtr)
{
    auto unitEnum = static_cast<OHOS::Ace::DimensionUnit>(unit);
    if (value < 0 || unitEnum < OHOS::Ace::DimensionUnit::PX || unitEnum > OHOS::Ace::DimensionUnit::CALC ||
        unitEnum == OHOS::Ace::DimensionUnit::PERCENT) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        GetMarqueeModelImpl()->SetFontSize(fontSize);
    } else {
        GetMarqueeModelImpl()->SetFontSize(Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
    }
}

void ResetMarqueeFontSizeImpl(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    if (!isJsView) {
        auto pipelineContext = PipelineBase::GetCurrentContext();
        CHECK_NULL_VOID(pipelineContext);
        auto theme = pipelineContext->GetTheme<TextTheme>();
        CHECK_NULL_VOID(theme);
        CalcDimension fontSize = theme->GetTextStyle().GetFontSize();
        GetMarqueeModelImpl()->SetFontSize(fontSize);
    } else {
        std::optional<Dimension> fontSizeOpt;
        GetMarqueeModelImpl()->SetFontSize(fontSizeOpt);
    }
}

void SetMarqueeFontColorImpl(ArkUINodeHandle node, ArkUI_Uint32 color, void* resourceRawPtr)
{
    GetMarqueeModelImpl()->SetTextColor(Color(color));
}

void ResetMarqueeFontColorImpl(ArkUINodeHandle node)
{
    std::optional<Color> colorOpt;
    GetMarqueeModelImpl()->SetTextColor(colorOpt);
}

void SetMarqueeAllowScaleImpl(ArkUINodeHandle node, ArkUI_Bool allowScale)
{
    GetMarqueeModelImpl()->SetAllowScale(allowScale);
}

void ResetMarqueeAllowScaleImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetAllowScale(DEFAULT_ALLOW_SCALE);
}

void SetMarqueeFontWeightImpl(ArkUINodeHandle node, const char* fontWeight)
{
    GetMarqueeModelImpl()->SetFontWeight(Framework::ConvertStrToFontWeight(fontWeight));
}

void ResetMarqueeFontWeightImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetFontWeight(DEFAULT_FONT_WEIGHT);
}

void SetMarqueeFontFamilyImpl(ArkUINodeHandle node, const char* fontFamily)
{
    std::string familiesStr = fontFamily;
    std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
    GetMarqueeModelImpl()->SetFontFamily(fontFamilyResult);
}

void ResetMarqueeFontFamilyImpl(ArkUINodeHandle node, ArkUI_Bool isJsView)
{
    if (!isJsView) {
        std::string familiesStr = DEFAULT_FONT_FAMILY;
        std::vector<std::string> fontFamilyResult = Framework::ConvertStrToFontFamilies(familiesStr);
        GetMarqueeModelImpl()->SetFontFamily(fontFamilyResult);
    } else {
        std::vector<std::string> fontFamilies;
        GetMarqueeModelImpl()->SetFontFamily(fontFamilies);
    }
}

void SetMarqueeUpdateStrategyImpl(ArkUINodeHandle node, ArkUI_Uint32 value) {}

void ResetMarqueeUpdateStrategyImpl(ArkUINodeHandle node) {}

void SetMarqueeOnStartImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onStart = reinterpret_cast<std::function<void()>*>(callback);
        GetMarqueeModelImpl()->SetOnStart(std::move(*onStart));
    } else {
        GetMarqueeModelImpl()->SetOnStart(nullptr);
    }
}

void ResetMarqueeOnStartImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetOnStart(nullptr);
}

void SetMarqueeOnBounceImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onBounce = reinterpret_cast<std::function<void()>*>(callback);
        GetMarqueeModelImpl()->SetOnBounce(std::move(*onBounce));
    } else {
        GetMarqueeModelImpl()->SetOnBounce(nullptr);
    }
}

void ResetMarqueeOnBounceImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetOnBounce(nullptr);
}

void SetMarqueeOnFinishImpl(ArkUINodeHandle node, void* callback)
{
    if (callback) {
        auto onFinish = reinterpret_cast<std::function<void()>*>(callback);
        GetMarqueeModelImpl()->SetOnFinish(std::move(*onFinish));
    } else {
        GetMarqueeModelImpl()->SetOnFinish(nullptr);
    }
}

void ResetMarqueeOnFinishImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetOnFinish(nullptr);
}

void SetMarqueeSrcValueImpl(ArkUINodeHandle node, ArkUI_CharPtr src)
{
    CHECK_NULL_VOID(src);
    GetMarqueeModelImpl()->SetValue(std::optional<std::string>(src));
}

void ResetMarqueeSrcValueImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetValue(std::optional<std::string>(""));
}

void SetMarqueePlayerStatusImpl(ArkUINodeHandle node, ArkUI_Bool start)
{
    GetMarqueeModelImpl()->SetPlayerStatus(std::optional<bool>(start));
}

void ResetMarqueePlayerStatusImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetPlayerStatus(std::optional<bool>(false));
}

void SetMarqueeScrollAmountImpl(ArkUINodeHandle node, ArkUI_Float64 step)
{
    GetMarqueeModelImpl()->SetScrollAmount(std::optional<double>(step));
}

void ResetMarqueeScrollAmountImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetScrollAmount(std::optional<double>(DEFAULT_STEP));
}

void SetMarqueeLoopImpl(ArkUINodeHandle node, ArkUI_Int32 loop)
{
    GetMarqueeModelImpl()->SetLoop(std::optional<int32_t>(loop));
}

void ResetMarqueeLoopImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetLoop(std::optional<int32_t>(DEFAULT_MARQUEE_LOOP));
}

void SetMarqueeDirectionImpl(ArkUINodeHandle node, ArkUI_Int32 direction)
{
    GetMarqueeModelImpl()->SetDirection(std::optional<MarqueeDirection>(static_cast<MarqueeDirection>(direction)));
}

void ResetMarqueeDirectionImpl(ArkUINodeHandle node)
{
    GetMarqueeModelImpl()->SetDirection(MarqueeDirection::LEFT);
}

void SetMarqueeFrameRateRangeImpl(ArkUINodeHandle node, ArkUI_Int32 minValue, ArkUI_Int32 maxValue,
    ArkUI_Int32 expectValue, ArkUI_Int32 value) {}

ArkUINodeHandle CreateMarqueeFrameNodeImpl(ArkUI_Uint32 nodeId)
{
    GetMarqueeModelImpl()->Create();
    return nullptr;
}
#endif

namespace NodeModifier {
const ArkUIMarqueeModifier* GetMarqueeDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIMarqueeModifier modifier = {
            .setMarqueeFontSize = SetMarqueeFontSizeImpl,
            .resetMarqueeFontSize = ResetMarqueeFontSizeImpl,
            .setMarqueeFontColor = SetMarqueeFontColorImpl,
            .resetMarqueeFontColor = ResetMarqueeFontColorImpl,
            .setMarqueeAllowScale = SetMarqueeAllowScaleImpl,
            .resetMarqueeAllowScale = ResetMarqueeAllowScaleImpl,
            .setMarqueeFontWeight = SetMarqueeFontWeightImpl,
            .resetMarqueeFontWeight = ResetMarqueeFontWeightImpl,
            .setMarqueeFontFamily = SetMarqueeFontFamilyImpl,
            .resetMarqueeFontFamily = ResetMarqueeFontFamilyImpl,
            .setMarqueeUpdateStrategy = SetMarqueeUpdateStrategyImpl,
            .resetMarqueeUpdateStrategy = ResetMarqueeUpdateStrategyImpl,
            .setMarqueeOnStart = SetMarqueeOnStartImpl,
            .resetMarqueeOnStart = ResetMarqueeOnStartImpl,
            .setMarqueeOnBounce = SetMarqueeOnBounceImpl,
            .resetMarqueeOnBounce = ResetMarqueeOnBounceImpl,
            .setMarqueeOnFinish = SetMarqueeOnFinishImpl,
            .resetMarqueeOnFinish = ResetMarqueeOnFinishImpl,
            .setMarqueeSrcValue = SetMarqueeSrcValueImpl,
            .resetMarqueeSrcValue = ResetMarqueeSrcValueImpl,
            .setMarqueePlayerStatus = SetMarqueePlayerStatusImpl,
            .resetMarqueePlayerStatus = ResetMarqueePlayerStatusImpl,
            .setMarqueeScrollAmount = SetMarqueeScrollAmountImpl,
            .resetMarqueeScrollAmount = ResetMarqueeScrollAmountImpl,
            .setMarqueeLoop = SetMarqueeLoopImpl,
            .resetMarqueeLoop = ResetMarqueeLoopImpl,
            .setMarqueeDirection = SetMarqueeDirectionImpl,
            .resetMarqueeDirection = ResetMarqueeDirectionImpl,
            .createMarqueeFrameNode = CreateMarqueeFrameNodeImpl,
            .setMarqueeFrameRateRange = SetMarqueeFrameRateRangeImpl,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    } else {
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIMarqueeModifier modifier = {
            .setMarqueeFontSize = SetMarqueeFontSize,
            .resetMarqueeFontSize = ResetMarqueeFontSize,
            .setMarqueeFontColor = SetMarqueeFontColor,
            .resetMarqueeFontColor = ResetMarqueeFontColor,
            .setMarqueeAllowScale = SetMarqueeAllowScale,
            .resetMarqueeAllowScale = ResetMarqueeAllowScale,
            .setMarqueeFontWeight = SetMarqueeFontWeight,
            .resetMarqueeFontWeight = ResetMarqueeFontWeight,
            .setMarqueeFontFamily = SetMarqueeFontFamily,
            .resetMarqueeFontFamily = ResetMarqueeFontFamily,
            .setMarqueeUpdateStrategy = SetMarqueeUpdateStrategy,
            .resetMarqueeUpdateStrategy = ResetMarqueeUpdateStrategy,
            .setMarqueeOnStart = SetMarqueeOnStart,
            .resetMarqueeOnStart = ResetMarqueeOnStart,
            .setMarqueeOnBounce = SetMarqueeOnBounce,
            .resetMarqueeOnBounce = ResetMarqueeOnBounce,
            .setMarqueeOnFinish = SetMarqueeOnFinish,
            .resetMarqueeOnFinish = ResetMarqueeOnFinish,
            .setMarqueeSrcValue = SetMarqueeSrcValue,
            .resetMarqueeSrcValue = ResetMarqueeSrcValue,
            .setMarqueePlayerStatus = SetMarqueePlayerStatus,
            .resetMarqueePlayerStatus = ResetMarqueePlayerStatus,
            .setMarqueeScrollAmount = SetMarqueeScrollAmount,
            .resetMarqueeScrollAmount = ResetMarqueeScrollAmount,
            .setMarqueeLoop = SetMarqueeLoop,
            .resetMarqueeLoop = ResetMarqueeLoop,
            .setMarqueeDirection = SetMarqueeDirection,
            .resetMarqueeDirection = ResetMarqueeDirection,
            .createMarqueeFrameNode = CreateMarqueeFrameNode,
            .setMarqueeFrameRateRange = SetMarqueeFrameRateRange,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
    }
}

const CJUIMarqueeModifier* GetCJUIMarqueeModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIMarqueeModifier modifier = {
        .setMarqueeFontSize = SetMarqueeFontSize,
        .resetMarqueeFontSize = ResetMarqueeFontSize,
        .setMarqueeFontColor = SetMarqueeFontColor,
        .resetMarqueeFontColor = ResetMarqueeFontColor,
        .setMarqueeAllowScale = SetMarqueeAllowScale,
        .resetMarqueeAllowScale = ResetMarqueeAllowScale,
        .setMarqueeFontWeight = SetMarqueeFontWeight,
        .resetMarqueeFontWeight = ResetMarqueeFontWeight,
        .setMarqueeFontFamily = SetMarqueeFontFamily,
        .resetMarqueeFontFamily = ResetMarqueeFontFamily,
        .setMarqueeUpdateStrategy = SetMarqueeUpdateStrategy,
        .resetMarqueeUpdateStrategy = ResetMarqueeUpdateStrategy,
        .setMarqueeOnStart = SetMarqueeOnStart,
        .resetMarqueeOnStart = ResetMarqueeOnStart,
        .setMarqueeOnBounce = SetMarqueeOnBounce,
        .resetMarqueeOnBounce = ResetMarqueeOnBounce,
        .setMarqueeOnFinish = SetMarqueeOnFinish,
        .resetMarqueeOnFinish = ResetMarqueeOnFinish,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
}
} // namespace OHOS::Ace::NG

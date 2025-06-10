/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_model_ng.h"

#include "core/components/swiper/swiper_component.h"
#include "core/components_ng/base/view_stack_processor.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/indicator_pattern.h"
#include "core/components_ng/pattern/swiper_indicator/indicator_common/swiper_indicator_layout_property.h"
#include "core/common/resource/resource_parse_utils.h"

namespace OHOS::Ace::NG {
RefPtr<IndicatorController> IndicatorModelNG::Create()
{
    auto* stack = ViewStackProcessor::GetInstance();
    CHECK_NULL_RETURN(stack, nullptr);
    auto nodeId = stack->ClaimNodeId();
    ACE_LAYOUT_SCOPED_TRACE("Create[%s][self:%d]", V2::INDICATOR_ETS_TAG, nodeId);
    auto indicatorNode = FrameNode::GetOrCreateFrameNode(
        V2::INDICATOR_ETS_TAG, nodeId, []() { return AceType::MakeRefPtr<IndicatorPattern>(); });

    stack->Push(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_RETURN(pattern, nullptr);
    pattern->InitIndicatorController();
    return pattern->GetIndicatorController();
}

RefPtr<FrameNode> IndicatorModelNG::CreateFrameNode(int32_t nodeId)
{
    return FrameNode::CreateFrameNode(
        V2::INDICATOR_ETS_TAG, nodeId, AceType::MakeRefPtr<IndicatorPattern>());
}

void IndicatorModelNG::SetShowIndicator(bool showIndicator)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, ShowIndicator, showIndicator);
}

void IndicatorModelNG::SetCount(uint32_t count)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Count, count);
}

void IndicatorModelNG::SetInitialIndex(uint32_t index)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, InitialIndex, index);
}

void IndicatorModelNG::SetIndicatorType(SwiperIndicatorType indicatorType)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, IndicatorType, indicatorType);
}

void IndicatorModelNG::SetLoop(bool loop)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Loop, loop);
}

void IndicatorModelNG::SetDirection(Axis axis)
{
    ACE_UPDATE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Direction, axis);
}

void IndicatorModelNG::SetOnChange(std::function<void(const BaseEventInfo* info)>&& onChange)
{
    auto indicatorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);

    pattern->UpdateChangeEvent([event = std::move(onChange)](int32_t index) {
        SwiperChangeEvent eventInfo(index);
        event(&eventInfo);
    });
}

void IndicatorModelNG::SetIndicatorStyle(const SwiperParameters& swiperParameters)
{
    auto indicatorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
};

void IndicatorModelNG::SetDotIndicatorStyle(const SwiperParameters& swiperParameters)
{
    auto indicatorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
    if (SystemProperties::ConfigChangePerform()) {
        CreateDotWithResourceObj(indicatorNode, swiperParameters);
    }
};

void IndicatorModelNG::SetDigitIndicatorStyle(const SwiperDigitalParameters& indicatorDigitalParameters)
{
    auto indicatorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(indicatorDigitalParameters);
    if (SystemProperties::ConfigChangePerform()) {
        CreateDigitWithResourceObj(indicatorNode, indicatorDigitalParameters);
    }
};

void IndicatorModelNG::SetIsIndicatorCustomSize(bool isCustomSize)
{
    auto indicatorNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    CHECK_NULL_VOID(indicatorNode);
    auto pattern = indicatorNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}


void IndicatorModelNG::SetDirection(FrameNode* frameNode, Axis axis)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Direction, axis, frameNode);
}

void IndicatorModelNG::SetShowIndicator(FrameNode* frameNode, bool showIndicator)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, ShowIndicator, showIndicator, frameNode);
}

void IndicatorModelNG::SetLoop(FrameNode* frameNode, bool loop)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Loop, loop, frameNode);
}

void IndicatorModelNG::SetInitialIndex(FrameNode* frameNode, uint32_t index)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, InitialIndex, index, frameNode);
}

void IndicatorModelNG::SetCount(FrameNode* frameNode, uint32_t count)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, Count, count, frameNode);
}

void IndicatorModelNG::SetDigitIndicatorStyle(
    FrameNode* frameNode, const SwiperDigitalParameters& swiperDigitalParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperDigitalParameters(swiperDigitalParameters);
    if (SystemProperties::ConfigChangePerform()) {
        CreateDigitWithResourceObj(frameNode, swiperDigitalParameters);
    }
}

void IndicatorModelNG::SetIndicatorType(FrameNode* frameNode, SwiperIndicatorType indicatorType)
{
    ACE_UPDATE_NODE_LAYOUT_PROPERTY(SwiperIndicatorLayoutProperty, IndicatorType, indicatorType, frameNode);
}

void IndicatorModelNG::SetDotIndicatorStyle(FrameNode* frameNode, const SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetSwiperParameters(swiperParameters);
    if (SystemProperties::ConfigChangePerform()) {
        CreateDotWithResourceObj(frameNode, swiperParameters);
    }
}

void IndicatorModelNG::SetOnChange(FrameNode* frameNode, std::function<void(const BaseEventInfo* info)>&& onChange)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->UpdateChangeEvent([event = std::move(onChange)](int32_t index) {
        SwiperChangeEvent eventInfo(index);
        event(&eventInfo);
    });
}

void IndicatorModelNG::SetIsIndicatorCustomSize(FrameNode* frameNode, bool isCustomSize)
{
    CHECK_NULL_VOID(frameNode);
    auto pattern = frameNode->GetPattern<IndicatorPattern>();
    CHECK_NULL_VOID(pattern);
    pattern->SetIsIndicatorCustomSize(isCustomSize);
}

bool IndicatorModelNG::GetLoop(FrameNode* frameNode)
{
    bool value = true;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(SwiperIndicatorLayoutProperty, Loop, value, frameNode, value);
    return value;
}

int32_t  IndicatorModelNG::GetCount(FrameNode* frameNode)
{
    int32_t  value = 0;
    ACE_GET_NODE_LAYOUT_PROPERTY_WITH_DEFAULT_VALUE(SwiperIndicatorLayoutProperty, Count, value, frameNode, value);
    return value;
}

template<typename T>
void ParseType(const RefPtr<ResourceObject>& resObj, T& result)
{
    if constexpr (std::is_same_v<T, Color>) {
        ResourceParseUtils::ParseResColor(resObj, result);
    } else if constexpr (std::is_same_v<T, CalcDimension>) {
        ResourceParseUtils::ParseResDimensionVpNG(resObj, result);
    }
}

#define UPDATE_DOT_VALUE(frameNode, name, resObj, resultType)                                                   \
    do {                                                                                                        \
        CHECK_NULL_VOID(frameNode);                                                                             \
        auto pattern = frameNode->GetPattern<IndicatorPattern>();                                               \
        CHECK_NULL_VOID(pattern);                                                                               \
        if (resObj) {                                                                                           \
            auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {  \
                auto node = weak.Upgrade();                                                                     \
                CHECK_NULL_VOID(node);                                                                          \
                auto pattern = node->GetPattern<IndicatorPattern>();                                            \
                CHECK_NULL_VOID(pattern);                                                                       \
                resultType result;                                                                              \
                ParseType(resObj, result);                                                                      \
                auto params = pattern->GetIndicatorParameters();                                                \
                params->name = result;                                                                          \
            };                                                                                                  \
            pattern->AddResObj("indicator." #name, resObj, std::move(updateFunc));                              \
        } else {                                                                                                \
            pattern->RemoveResObj("indicator." #name);                                                          \
        }                                                                                                       \
    } while (false)

#define UPDATE_DIGITAL_VALUE(frameNode, name, resObj, resultType)                                               \
    do {                                                                                                        \
        CHECK_NULL_VOID(frameNode);                                                                             \
        auto pattern = frameNode->GetPattern<IndicatorPattern>();                                               \
        CHECK_NULL_VOID(pattern);                                                                               \
        if (resObj) {                                                                                           \
            auto&& updateFunc = [weak = AceType::WeakClaim(frameNode)](const RefPtr<ResourceObject>& resObj) {  \
                auto node = weak.Upgrade();                                                                     \
                CHECK_NULL_VOID(node);                                                                          \
                auto pattern = node->GetPattern<IndicatorPattern>();                                            \
                CHECK_NULL_VOID(pattern);                                                                       \
                resultType result;                                                                              \
                ParseType(resObj, result);                                                                      \
                auto params = pattern->GetSwiperDigitalParameters();                                            \
                params->name = result;                                                                          \
            };                                                                                                  \
            pattern->AddResObj("indicator." #name, resObj, std::move(updateFunc));                              \
        } else {                                                                                                \
            pattern->RemoveResObj("indicator." #name);                                                          \
        }                                                                                                       \
    } while (false)

void IndicatorModelNG::CreateDotWithResourceObj(FrameNode* frameNode, const SwiperParameters& swiperParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto resObj = swiperParameters.resourceColorValueObject;
    UPDATE_DOT_VALUE(frameNode, colorVal, resObj, Color);
    resObj = swiperParameters.resourceSelectedColorValueObject;
    UPDATE_DOT_VALUE(frameNode, selectedColorVal, resObj, Color);
    resObj = swiperParameters.resourceItemWidthValueObject;
    UPDATE_DOT_VALUE(frameNode, itemWidth, resObj, CalcDimension);
    resObj = swiperParameters.resourceItemHeightValueObject;
    UPDATE_DOT_VALUE(frameNode, itemHeight, resObj, CalcDimension);
    resObj = swiperParameters.resourceSelectedItemWidthValueObject;
    UPDATE_DOT_VALUE(frameNode, selectedItemWidth, resObj, CalcDimension);
    resObj = swiperParameters.resourceSelectedItemHeightValueObject;
    UPDATE_DOT_VALUE(frameNode, selectedItemHeight, resObj, CalcDimension);
}

void IndicatorModelNG::CreateDigitWithResourceObj(FrameNode* frameNode,
    const SwiperDigitalParameters& swiperDigitalParameters)
{
    CHECK_NULL_VOID(frameNode);
    auto resObj = swiperDigitalParameters.resourceFontColorValueObject;
    UPDATE_DIGITAL_VALUE(frameNode, fontColor, resObj, Color);
    resObj = swiperDigitalParameters.resourceFontSizeValueObject;
    UPDATE_DIGITAL_VALUE(frameNode, fontSize, resObj, CalcDimension);
    resObj = swiperDigitalParameters.resourceSelectedFontColorValueObject;
    UPDATE_DIGITAL_VALUE(frameNode, selectedFontColor, resObj, Color);
    resObj = swiperDigitalParameters.resourceSelectedFontSizeValueObject;
    UPDATE_DIGITAL_VALUE(frameNode, selectedFontSize, resObj, CalcDimension);
}
} // namespace OHOS::Ace::NG

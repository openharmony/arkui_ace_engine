/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/counter_modifier.h"

#include "core/components_ng/pattern/counter/counter_model_ng.h"

namespace OHOS::Ace::NG {
void SetEnableInc(ArkUINodeHandle node, ArkUI_Bool enableInc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableInc(frameNode, enableInc);
}
void ResetEnableInc(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableInc(frameNode, true);
}
void SetEnableDec(ArkUINodeHandle node, ArkUI_Bool enableDec)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableDec(frameNode, enableDec);
}
void ResetEnableDec(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableDec(frameNode, true);
}

void SetCounterHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CounterModelNG::SetHeight(frameNode, height);
}

void SetCounterHeightRes(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* heightRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CounterModelNG::SetHeight(frameNode, height);
    if (SystemProperties::ConfigChangePerform()) {
        if (heightRawPtr) {
            auto* fontWeight = reinterpret_cast<ResourceObject*>(heightRawPtr);
            auto heightResObj = AceType::Claim(fontWeight);
            CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Height, heightResObj);
        } else {
            CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Height, nullptr);
        }
    }
}

void ResetCounterHeight(ArkUINodeHandle node)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Height, nullptr);
    }
}

void SetCounterWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CounterModelNG::SetWidth(frameNode, width);
}

void SetCounterWidthRes(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 unit, void* widthRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<OHOS::Ace::DimensionUnit>(unit));
    CounterModelNG::SetWidth(frameNode, width);
    if (SystemProperties::ConfigChangePerform()) {
        if (widthRawPtr) {
            auto* fontWeight = reinterpret_cast<ResourceObject*>(widthRawPtr);
            auto widthResObj = AceType::Claim(fontWeight);
            CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Width, widthResObj);
        } else {
            CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Width, nullptr);
        }
    }
}

void ResetCounterWidth(ArkUINodeHandle node)
{
    if (SystemProperties::ConfigChangePerform()) {
        auto* frameNode = reinterpret_cast<FrameNode*>(node);
        CHECK_NULL_VOID(frameNode);
        CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::Width, nullptr);
    }
}

void SetCounterBackgroundColor(ArkUINodeHandle node, ArkUI_Uint32 color)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetBackgroundColor(frameNode, Color(color));
}

void SetCounterBackgroundColorWithColorSpace(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    CounterModelNG::SetBackgroundColor(frameNode, backgroundColor);
}

void SetCounterBackgroundColorRes(ArkUINodeHandle node, ArkUI_Uint32 color, ArkUI_Int32 colorSpace, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    Color backgroundColor { color };
    if (ColorSpace::DISPLAY_P3 == colorSpace) {
        backgroundColor.SetColorSpace(ColorSpace::DISPLAY_P3);
    } else {
        backgroundColor.SetColorSpace(ColorSpace::SRGB);
    }
    CounterModelNG::SetBackgroundColor(frameNode, backgroundColor);

    if (SystemProperties::ConfigChangePerform()) {
        if (colorRawPtr) {
            auto* colorResObj = reinterpret_cast<ResourceObject*>(colorRawPtr);
            CounterModelNG::CreateWithResourceObj(
                frameNode, JsCounterResourceType::BackgroundColor, AceType::Claim(colorResObj));
        } else {
            CounterModelNG::CreateWithResourceObj(frameNode, JsCounterResourceType::BackgroundColor, nullptr);
        }
    }
}

void ResetCounterBackgroundColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::ResetBackgroundColor(frameNode);
    if (SystemProperties::ConfigChangePerform()) {
        CounterModelNG::CreateWithResourceObj(
            frameNode, JsCounterResourceType::BackgroundColor, nullptr);
    }
}

void SetCounterOnInc(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onInc = reinterpret_cast<CounterModel::CounterEventFunc*>(callback);
        CounterModelNG::SetOnInc(frameNode, std::move(*onInc));
    } else {
        CounterModelNG::SetOnInc(frameNode, nullptr);
    }
}

void ResetCounterOnInc(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetOnInc(frameNode, nullptr);
}

void SetCounterOnDec(ArkUINodeHandle node, void* callback)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (callback) {
        auto onDec = reinterpret_cast<CounterModel::CounterEventFunc*>(callback);
        CounterModelNG::SetOnDec(frameNode, std::move(*onDec));
    } else {
        CounterModelNG::SetOnDec(frameNode, nullptr);
    }
}

void ResetCounterOnDec(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetOnDec(frameNode, nullptr);
}

namespace NodeModifier {
const ArkUICounterModifier* GetCounterModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICounterModifier modifier = {
        .setEnableInc = SetEnableInc,
        .resetEnableInc = ResetEnableInc,
        .setEnableDec = SetEnableDec,
        .resetEnableDec = ResetEnableDec,
        .setCounterHeight = SetCounterHeight,
        .setCounterHeightRes = SetCounterHeightRes,
        .resetCounterHeight = ResetCounterHeight,
        .setCounterWidth = SetCounterWidth,
        .setCounterWidthRes = SetCounterWidthRes,
        .resetCounterWidth = ResetCounterWidth,
        .setCounterBackgroundColor = SetCounterBackgroundColor,
        .setCounterBackgroundColorWithColorSpace = SetCounterBackgroundColorWithColorSpace,
        .setCounterBackgroundColorRes = SetCounterBackgroundColorRes,
        .resetCounterBackgroundColor = ResetCounterBackgroundColor,
        .setCounterOnInc = SetCounterOnInc,
        .resetCounterOnInc = ResetCounterOnInc,
        .setCounterOnDec = SetCounterOnDec,
        .resetCounterOnDec = ResetCounterOnDec,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUICounterModifier* GetCJUICounterModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICounterModifier modifier = {
        .setEnableInc = SetEnableInc,
        .resetEnableInc = ResetEnableInc,
        .setEnableDec = SetEnableDec,
        .resetEnableDec = ResetEnableDec,
        .setCounterHeight = SetCounterHeight,
        .setCounterHeightRes = SetCounterHeightRes,
        .resetCounterHeight = ResetCounterHeight,
        .setCounterWidth = SetCounterWidth,
        .setCounterWidthRes = SetCounterWidthRes,
        .resetCounterWidth = ResetCounterWidth,
        .setCounterBackgroundColor = SetCounterBackgroundColor,
        .setCounterBackgroundColorWithColorSpace = SetCounterBackgroundColorWithColorSpace,
        .setCounterBackgroundColorRes = SetCounterBackgroundColorRes,
        .resetCounterBackgroundColor = ResetCounterBackgroundColor,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG

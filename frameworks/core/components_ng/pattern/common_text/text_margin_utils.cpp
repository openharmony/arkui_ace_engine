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

#include "core/components_ng/pattern/common_text/text_margin_utils.h"

#include "base/utils/utils.h"
#include "base/utils/system_properties.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/pattern.h"
#include "core/components_ng/property/measure_property.h"
#include "ui/base/geometry/calc_dimension.h"

namespace {
// Array indices for the four margin sides in TRBL (top/right/bottom/left) order.
constexpr int32_t INDEX_TOP = 0;
constexpr int32_t INDEX_RIGHT = 1;
constexpr int32_t INDEX_BOTTOM = 2;
constexpr int32_t INDEX_LEFT = 3;
} // namespace

namespace OHOS::Ace {

NG::CalcLength CalcLengthFromSizeType(const struct ArkUISizeType* size)
{
    if (size->string != nullptr) {
        return NG::CalcLength(size->string);
    }
    return NG::CalcLength(size->value, static_cast<DimensionUnit>(size->unit));
}

void RegisterMarginResource(NG::FrameNode* frameNode, const MarginSizeTypes& sizes,
    ArkUIPaddingRes* marginRes)
{
    CHECK_NULL_VOID(SystemProperties::ConfigChangePerform());
    auto pattern = frameNode->GetPattern();
    CHECK_NULL_VOID(pattern);
    if (marginRes && marginRes->topObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(marginRes->topObj));
        pattern->RegisterResource<CalcDimension>("marginTop", resObj,
            CalcDimension(sizes.top->value, static_cast<DimensionUnit>(sizes.top->unit)));
    } else {
        pattern->UnRegisterResource("marginTop");
    }
    if (marginRes && marginRes->bottomObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(marginRes->bottomObj));
        pattern->RegisterResource<CalcDimension>("marginBottom", resObj,
            CalcDimension(sizes.bottom->value, static_cast<DimensionUnit>(sizes.bottom->unit)));
    } else {
        pattern->UnRegisterResource("marginBottom");
    }
    if (marginRes && marginRes->leftObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(marginRes->leftObj));
        pattern->RegisterResource<CalcDimension>("marginLeft", resObj,
            CalcDimension(sizes.left->value, static_cast<DimensionUnit>(sizes.left->unit)));
    } else {
        pattern->UnRegisterResource("marginLeft");
    }
    if (marginRes && marginRes->rightObj) {
        auto resObj = AceType::Claim(reinterpret_cast<ResourceObject*>(marginRes->rightObj));
        pattern->RegisterResource<CalcDimension>("marginRight", resObj,
            CalcDimension(sizes.right->value, static_cast<DimensionUnit>(sizes.right->unit)));
    } else {
        pattern->UnRegisterResource("marginRight");
    }
}

void SetMarginCommon(ArkUINodeHandle node, const MarginSizeTypes& sizes,
    ArkUIPaddingRes* marginRes, SetMarginFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = std::optional<NG::CalcLength>(CalcLengthFromSizeType(sizes.top));
    paddings.bottom = std::optional<NG::CalcLength>(CalcLengthFromSizeType(sizes.bottom));
    paddings.left = std::optional<NG::CalcLength>(CalcLengthFromSizeType(sizes.left));
    paddings.right = std::optional<NG::CalcLength>(CalcLengthFromSizeType(sizes.right));
    setFunc(frameNode, paddings);
    RegisterMarginResource(frameNode, sizes, marginRes);
}

void ResetMarginCommon(ArkUINodeHandle node, SetMarginFunc setFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::PaddingProperty paddings;
    paddings.top = NG::CalcLength(0.0);
    paddings.bottom = NG::CalcLength(0.0);
    paddings.left = NG::CalcLength(0.0);
    paddings.right = NG::CalcLength(0.0);
    setFunc(frameNode, paddings);
    if (SystemProperties::ConfigChangePerform()) {
        auto pattern = frameNode->GetPattern();
        CHECK_NULL_VOID(pattern);
        pattern->UnRegisterResource("marginTop");
        pattern->UnRegisterResource("marginBottom");
        pattern->UnRegisterResource("marginLeft");
        pattern->UnRegisterResource("marginRight");
    }
}

void GetMarginCommon(ArkUINodeHandle node, ArkUI_Float32 (*values)[4],
    ArkUI_Int32 length, ArkUI_Int32 unit, GetMarginFunc getFunc)
{
    auto* frameNode = reinterpret_cast<NG::FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto margin = getFunc(frameNode);
    (*values)[INDEX_TOP] = margin.top->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[INDEX_RIGHT] = margin.right->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[INDEX_BOTTOM] = margin.bottom->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
    (*values)[INDEX_LEFT] = margin.left->GetDimension().GetNativeValue(static_cast<DimensionUnit>(unit));
}

} // namespace OHOS::Ace

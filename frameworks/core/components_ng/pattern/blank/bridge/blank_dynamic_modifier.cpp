/*
 * Copyright (c) 2023-2026 Huawei Device Co., Ltd.
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

#include "core/common/container.h"
#include "core/components_ng/pattern/blank/blank_model_ng.h"
#include "core/components_ng/pattern/blank/bridge/blank_model_impl.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/interfaces/native/node/blank_modifier.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::BlankModelImpl* GetBlankModelImpl()
{
    static Framework::BlankModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {

void CreateModel()
{
    BlankModelNG::CreateBlankModelNG();
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = BlankModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SetColor(ArkUINodeHandle node, ArkUI_Uint32 value, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::ResetResObj(frameNode, "blank.color");
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* color = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(color);
        BlankModelNG::SetColor(frameNode, colorResObj);
    } else {
        BlankModelNG::SetColor(frameNode, Color(value));
    }
}

void ResetColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::ResetResObj(frameNode, "blank.color");
    BlankModelNG::SetColor(frameNode, Color::TRANSPARENT);
}

void SetBlankHeight(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetHeight(frameNode, CalcDimension(heightValue, static_cast<DimensionUnit>(heightUnit)));
}

void ResetBlankHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ClearWidthOrHeight(frameNode, false);
}

void SetBlankMin(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(minValue, static_cast<DimensionUnit>(minUnit)));
}

void ResetBlankMin(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    BlankModelNG::SetBlankMin(frameNode, CalcDimension(0.0, DimensionUnit::VP));
}

#ifndef CROSS_PLATFORM
void CreateModelImpl()
{
    GetBlankModelImpl()->Create();
}

void SetColorImpl(ArkUINodeHandle node, ArkUI_Uint32 value, void* colorRawPtr)
{
    GetBlankModelImpl()->SetColor(Color(value));
}

void ResetColorImpl(ArkUINodeHandle node)
{
    GetBlankModelImpl()->SetColor(Color::TRANSPARENT);
}

void SetBlankHeightImpl(ArkUINodeHandle node, ArkUI_Float32 heightValue, ArkUI_Int32 heightUnit)
{
    GetBlankModelImpl()->SetHeight(CalcDimension(heightValue, static_cast<DimensionUnit>(heightUnit)));
}

void ResetBlankHeightImpl(ArkUINodeHandle node)
{
    GetBlankModelImpl()->SetHeight(CalcDimension(0.0, DimensionUnit::VP));
}

void SetBlankMinImpl(ArkUINodeHandle node, ArkUI_Float32 minValue, ArkUI_Int32 minUnit)
{
    GetBlankModelImpl()->SetBlankMin(CalcDimension(minValue, static_cast<DimensionUnit>(minUnit)));
}

void ResetBlankMinImpl(ArkUINodeHandle node)
{
    GetBlankModelImpl()->SetBlankMin(CalcDimension(0.0, DimensionUnit::VP));
}
#endif

const ArkUIBlankModifier* GetBlankDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIBlankModifier modifier = {
            .createModel = CreateModelImpl,
            .setColor = SetColorImpl,
            .resetColor = ResetColorImpl,
            .setBlankHeight = SetBlankHeightImpl,
            .resetBlankHeight = ResetBlankHeightImpl,
            .setBlankMin = SetBlankMinImpl,
            .resetBlankMin = ResetBlankMinImpl,
            .createFrameNode = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIBlankModifier modifier = {
        .createModel = CreateModel,
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIBlankModifier* GetCJUIBlankDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIBlankModifier modifier = {
        .setColor = SetColor,
        .resetColor = ResetColor,
        .setBlankHeight = SetBlankHeight,
        .resetBlankHeight = ResetBlankHeight,
        .setBlankMin = SetBlankMin,
        .resetBlankMin = ResetBlankMin,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG

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

#include "core/common/container.h"
#include "base/memory/ace_type.h"
#include "core/components_ng/pattern/divider/bridge/divider_model_impl.h"
#include "core/components_ng/pattern/divider/divider_model_ng.h"
#include "core/interfaces/native/node/divider_modifier.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::DividerModelImpl* GetDividerModelImpl()
{
    static Framework::DividerModelImpl instance;
    return &instance;
}
#endif
} // namespace OHOS::Ace

namespace OHOS::Ace::NG {
namespace {
constexpr bool DEFAULT_DIVIDER_VERTICAL = false;
const Dimension DEFAULT_DIVIDER_STROKE_WIDTH(1.0, DimensionUnit::PX);
constexpr LineCap DEFAULT_DIVIDER_LINE_CAP = LineCap::BUTT;

LineCap GetLineCap(int32_t lineCap)
{
    if (static_cast<int32_t>(LineCap::SQUARE) == lineCap) {
        return LineCap::SQUARE;
    }
    if (static_cast<int32_t>(LineCap::ROUND) == lineCap) {
        return LineCap::ROUND;
    }
    return DEFAULT_DIVIDER_LINE_CAP;
}
} // namespace

void CreateModel()
{
    DividerModelNG model;
    model.Create();
}

ArkUINodeHandle CreateFrameNode(int32_t nodeId)
{
    auto frameNode = DividerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    auto node = reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
    CHECK_NULL_RETURN(node, nullptr);
    return node;
}

void SetDividerStrokeWidth(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::StrokeWidth(frameNode, CalcDimension(value, static_cast<DimensionUnit>(unit)));
}

void ResetDividerStrokeWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::StrokeWidth(frameNode, DEFAULT_DIVIDER_STROKE_WIDTH);
}

void SetDividerLineCap(ArkUINodeHandle node, int32_t lineCap)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::LineCap(frameNode, GetLineCap(lineCap));
}

void ResetDividerLineCap(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::LineCap(frameNode, DEFAULT_DIVIDER_LINE_CAP);
}

void SetDividerColor(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::ResetResObj(frameNode, "divider.color");
    if (SystemProperties::ConfigChangePerform() && colorRawPtr) {
        auto* colorObj = reinterpret_cast<ResourceObject*>(colorRawPtr);
        auto colorResObj = AceType::Claim(colorObj);
        DividerModelNG::SetDividerColor(frameNode, colorResObj, true);
        return;
    }
    DividerModelNG::SetDividerColor(frameNode, Color(color), true);
}

void ResetDividerColor(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::ResetResObj(frameNode, "divider.color");
    DividerModelNG::ResetDividerColor(frameNode);
}

void SetDividerVertical(ArkUINodeHandle node, ArkUI_Bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, value);
}

void ResetDividerVertical(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    DividerModelNG::SetVertical(frameNode, DEFAULT_DIVIDER_VERTICAL);
}

#ifndef CROSS_PLATFORM
void CreateModelImpl()
{
    GetDividerModelImpl()->Create();
}

void SetDividerStrokeWidthImpl(ArkUINodeHandle node, ArkUI_Float32 value, int32_t unit)
{
    GetDividerModelImpl()->StrokeWidth(CalcDimension(value, static_cast<DimensionUnit>(unit)));
}

void SetDividerLineCapImpl(ArkUINodeHandle node, int32_t lineCap)
{
    GetDividerModelImpl()->LineCap(GetLineCap(lineCap));
}

void SetDividerColorImpl(ArkUINodeHandle node, uint32_t color, void* colorRawPtr)
{
    GetDividerModelImpl()->DividerColor(Color(color));
}

void ResetDividerColorImpl(ArkUINodeHandle node)
{
    GetDividerModelImpl()->ResetDividerColor();
}

void SetDividerVerticalImpl(ArkUINodeHandle node, ArkUI_Bool value)
{
    GetDividerModelImpl()->Vertical(value);
}

#endif

const ArkUIDividerModifier* GetDividerDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIDividerModifier modifier = {
            .createModel = CreateModelImpl,
            .setDividerStrokeWidth = SetDividerStrokeWidthImpl,
            .resetDividerStrokeWidth = nullptr,
            .setDividerLineCap = SetDividerLineCapImpl,
            .resetDividerLineCap = nullptr,
            .setDividerColor = SetDividerColorImpl,
            .resetDividerColor = ResetDividerColorImpl,
            .setDividerVertical = SetDividerVerticalImpl,
            .resetDividerVertical = nullptr,
            .createFrameNode = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
        return &modifier;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIDividerModifier modifier = {
        .createModel = CreateModel,
        .setDividerStrokeWidth = SetDividerStrokeWidth,
        .resetDividerStrokeWidth = ResetDividerStrokeWidth,
        .setDividerLineCap = SetDividerLineCap,
        .resetDividerLineCap = ResetDividerLineCap,
        .setDividerColor = SetDividerColor,
        .resetDividerColor = ResetDividerColor,
        .setDividerVertical = SetDividerVertical,
        .resetDividerVertical = ResetDividerVertical,
        .createFrameNode = CreateFrameNode,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

const CJUIDividerModifier* GetCJUIDividerDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIDividerModifier modifier = {
        .setDividerStrokeWidth = SetDividerStrokeWidth,
        .resetDividerStrokeWidth = ResetDividerStrokeWidth,
        .setDividerLineCap = SetDividerLineCap,
        .resetDividerLineCap = ResetDividerLineCap,
        .setDividerColor = SetDividerColor,
        .resetDividerColor = ResetDividerColor,
        .setDividerVertical = SetDividerVertical,
        .resetDividerVertical = ResetDividerVertical,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace OHOS::Ace::NG

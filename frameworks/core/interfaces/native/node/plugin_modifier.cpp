/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/plugin_modifier.h"

#include "core/components_ng/pattern/plugin/plugin_model_ng.h"

namespace OHOS::Ace::NG {
const DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
const double DEFAULT_VALUE = 0.0;

void SetPluginWidth(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 widthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<DimensionUnit>(widthUnit));
    PluginModelNG::SetWidth(frameNode, width);
}

void SetPluginHeight(ArkUINodeHandle node, ArkUI_Float32 value, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<DimensionUnit>(heightUnit));
    PluginModelNG::SetHeight(frameNode, height);
}

void SetPluginSize(ArkUINodeHandle node, ArkUI_Float32 widthVal, ArkUI_Float32 heightVal,
    ArkUI_Int32 widthUnit, ArkUI_Int32 heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(widthVal, static_cast<DimensionUnit>(widthUnit));
    Dimension height = Dimension(heightVal, static_cast<DimensionUnit>(heightUnit));
    PluginModelNG::SetPluginSize(frameNode, width, height);
}

void ResetPluginWidth(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetWidth(frameNode, width);
}

void ResetPluginHeight(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetHeight(frameNode, height);
}

void ResetPluginSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    Dimension height = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetPluginSize(frameNode, width, height);
}

namespace NodeModifier {
const ArkUIPluginModifier* GetPluginModifier()
{
    static const ArkUIPluginModifier modifier = {SetPluginWidth, SetPluginHeight, SetPluginSize,
        ResetPluginWidth, ResetPluginHeight, ResetPluginSize };

    return &modifier;
}

const CJUIPluginModifier* GetCJUIPluginModifier()
{
    static const CJUIPluginModifier modifier = {SetPluginWidth, SetPluginHeight, SetPluginSize,
        ResetPluginWidth, ResetPluginHeight, ResetPluginSize };

    return &modifier;
}
}
}
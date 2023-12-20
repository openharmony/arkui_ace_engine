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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_plugin_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/plugin/plugin_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
const DimensionUnit DEFAULT_UNIT = DimensionUnit::VP;
const double DEFAULT_VALUE = 0.0;

void SetPluginWidth(NodeHandle node, double value, int32_t widthUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(value, static_cast<DimensionUnit>(widthUnit));
    PluginModelNG::SetWidth(frameNode, width);
}

void SetPluginHeight(NodeHandle node, double value, int32_t heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(value, static_cast<DimensionUnit>(heightUnit));
    PluginModelNG::SetHeight(frameNode, height);
}

void SetPluginSize(NodeHandle node, double widthVal, double heightVal, int32_t widthUnit, int32_t heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(widthVal, static_cast<DimensionUnit>(widthUnit));
    Dimension height = Dimension(heightVal, static_cast<DimensionUnit>(heightUnit));
    PluginModelNG::SetPluginSize(frameNode, width, height);
}

void ResetPluginWidth(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetWidth(frameNode, width);
}

void ResetPluginHeight(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension height = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetHeight(frameNode, height);
}

void ResetPluginSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    Dimension height = Dimension(DEFAULT_VALUE, DEFAULT_UNIT);
    PluginModelNG::SetPluginSize(frameNode, width, height);
}

ArkUIPluginModifierAPI GetPluginModifier()
{
    static const ArkUIPluginModifierAPI modifier = {SetPluginWidth, SetPluginHeight, SetPluginSize,
        ResetPluginWidth, ResetPluginHeight, ResetPluginSize };

    return modifier;
}
}
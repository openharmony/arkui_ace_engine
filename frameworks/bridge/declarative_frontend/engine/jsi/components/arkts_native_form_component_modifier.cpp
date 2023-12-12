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

#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_form_component_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/form/form_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "base/geometry/dimension.h"

namespace OHOS::Ace::NG {
const int32_t DEFAULT_VISIBILITY = 0;
const int32_t DEFAULT_FORM_DIM = 1;
const bool DEFAULT_ALLOW_UPDATE = true;
void SetFormVisibility(NodeHandle node, int32_t visible)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType visibility = static_cast<VisibleType>(visible);
    FormModelNG::SetVisibility(frameNode, visibility);
}

void AllowUpdate(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::AllowUpdate(frameNode, value);
}

void SetDimension(NodeHandle node, int32_t dimension)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetDimension(frameNode, dimension);
}

void SetModuleName(NodeHandle node, const char* value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    std::string moduleName(value);
    FormModelNG::SetModuleName(frameNode, moduleName);
}

void SetFormSize(NodeHandle node, double widthValue, int32_t widthUnit, double heightValue, int32_t heightUnit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetSize(frameNode,
        Dimension(widthValue, static_cast<OHOS::Ace::DimensionUnit>(widthUnit)),
        Dimension(heightValue, static_cast<OHOS::Ace::DimensionUnit>(heightUnit)));
}

void ResetFormVisibility(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    VisibleType visibility = static_cast<VisibleType>(DEFAULT_VISIBILITY);
    FormModelNG::SetVisibility(frameNode, visibility);
}

void DisallowUpdate(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::AllowUpdate(frameNode, DEFAULT_ALLOW_UPDATE);
}

void ResetDimension(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetDimension(frameNode, DEFAULT_FORM_DIM);
}

void ResetModuleName(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    FormModelNG::SetModuleName(frameNode, "");
}

void ResetFormSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Dimension width = 0.0_vp;
    Dimension height = 0.0_vp;
    FormModelNG::SetSize(frameNode, width, height);
}

ArkUIFormComponentModifierAPI GetFormComponentModifier()
{
    static const ArkUIFormComponentModifierAPI modifier = { SetFormVisibility, AllowUpdate, SetDimension,
        SetModuleName, SetFormSize, ResetFormVisibility, DisallowUpdate, ResetDimension, ResetModuleName,
        ResetFormSize };

    return modifier;
}
} // namespace OHOS::Ace::NG
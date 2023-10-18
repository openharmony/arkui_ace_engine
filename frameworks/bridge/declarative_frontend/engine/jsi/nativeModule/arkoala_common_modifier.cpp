/*
 * Copyright (c) 2021-2022 Huawei Device Co., Ltd.
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

#include "arkoala_common_modifier.h"

#include "core/pipeline/base/element_register.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components/common/layout/constants.h"
#include "bridge/declarative_frontend/jsview/js_view_abstract.h"

namespace OHOS::Ace::NG {

constexpr uint32_t COLOR_ALPHA_OFFSET = 24;
constexpr uint32_t COLOR_ALPHA_VALUE = 0xFF000000;

NodeHandle GetFrameNodeById(int nodeId)
{
    auto node = ElementRegister::GetInstance()->GetNodeById(nodeId);
    return AceType::RawPtr(node);
}

void SetBackgroundColor(NodeHandle node, int color)
{
    LOGE("linyihao SetBackgroundColor:node: %{public}p value %{public}d", node, color);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetBackgroundColor(frameNode, Color(color));
}

void ResetBackgroundColor(NodeHandle node)
{
    LOGE("linyihao ResetBackgroundColor:node: %{public}p", node);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::ResetBackgroundColor(frameNode, Color::TRANSPARENT);
}

void SetWidth(NodeHandle node, float value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetWidth(frameNode, CalcLength(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetHeight(NodeHandle node, float value, int unit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetHeight(frameNode, CalcLength(value, static_cast<OHOS::Ace::DimensionUnit>(unit)));
}

void SetOpacity(NodeHandle node, float opacity)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetOpacity(frameNode, opacity);
}

void SetBorderWidth(NodeHandle node, float* widthValues, int* widthUnits, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderWidth;
    borderWidth.leftDimen = 
        Dimension(widthValues[1], static_cast<DimensionUnit>(widthUnits[1]));
    borderWidth.rightDimen = 
        Dimension(widthValues[3], static_cast<DimensionUnit>(widthUnits[3]));
    borderWidth.topDimen = 
        Dimension(widthValues[0], static_cast<DimensionUnit>(widthUnits[0]));
    borderWidth.bottomDimen = 
        Dimension(widthValues[2], static_cast<DimensionUnit>(widthUnits[2]));
    ViewAbstract::SetBorderWidth(frameNode, borderWidth);
}

void SetBorderColor(NodeHandle node, int* colors, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderColors;
    borderColors.topColor = Color(colors[0]);
    borderColors.rightColor = Color(colors[1]);
    borderColors.bottomColor = Color(colors[2]);
    borderColors.leftColor = Color(colors[3]);
    borderColors.multiValued = true;
    ViewAbstract::SetBorderColor(frameNode, borderColors);
}

void SetBorderStyle(NodeHandle node, int* styles, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderStyles;
    borderStyles.styleLeft = static_cast<BorderStyle>(styles[3]);
    borderStyles.styleRight = static_cast<BorderStyle>(styles[1]);
    borderStyles.styleTop = static_cast<BorderStyle>(styles[0]);
    borderStyles.styleBottom = static_cast<BorderStyle>(styles[2]);
    borderColors.multiValued = true;
    ViewAbstract::SetBorderStyle(frameNode, borderColors);
}

void SetBorderRadius(NodeHandle node, float* radiusValues, int* radiusUnits, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    NG::BorderWidthProperty borderRadius;
    borderRadius.radiusTopLeft =
        Dimension(radiusValues[0], static_cast<DimensionUnit>(radiusUnits[0]));
    borderRadius.radiusTopRight =
        Dimension(radiusValues[1], static_cast<DimensionUnit>(radiusUnits[1]));
    borderRadius.radiusBottomLeft =
        Dimension(radiusValues[2], static_cast<DimensionUnit>(radiusUnits[2]));
    borderRadius.radiusBottomRight =
        Dimension(radiusValues[3], static_cast<DimensionUnit>(radiusUnits[3]));
    borderRadius.multiValued = IsFocusableScope;
    ViewAbstract::SetBorderStyle(frameNode, borderRadius);
}

void SetZIndex(NodeHandle node, int zIndex)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetZIndex(frameNode, zIndex);
}

//shadow

void SetBackShadow(NodeHandle node, float* shadowInfo, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    Shadow shadow;
    if (length == 1) {
        auto style = static_cast<ShadowStyle>(static_cast<int>(shadowInfo[0]));
        shadow = Shadow::CreateShadow(style);
    } else {
        shadow.SetBlurRadius(shadowInfo[0]);
        shadow.SetColor(Color(shadowInfo[1]));
        shadow.SetOffsetX(shadowInfo[2]);
        shadow.SetOffsetY(shadowInfo[3]);
        auto type = static_cast<int32_t>(ShadowType::COLOR);
        type = std::clamp(type, static_cast<int32_t>(ShadowType::COLOR), static_cast<int32_t>(ShadowType::BLUR));
        shadow.SetShadowType(static_cast<ShadowType>(type));
    }
    std::vector<Shadow> shadows { shadow };
    ViewAbstract::SetBackShadow(frameNode, shadows);
}

//hitTestBehavior

void SetHitTestBehavior(NodeHandle node, int hitTestBehavior)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    HitTestMode hitTestMode = HitTestMode::HTMDEFAULT;
    hitTestMode = static_cast<HitTestMode>(hitTestBehavior);
    ViewAbstract::SetHitTestMode(frameNode, hitTestMode);
}

//transform

void SetTransform(NodeHandle node, float* matrix, int length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    const auto matrix4Len = Matrix4::DIMENSION * Matrix4::DIMENSION;
    Matrix4 value(
        matrix[0], matrix[4], matrix[8], matrix[12],
        matrix[1], matrix[5], matrix[9], matrix[13],
        matrix[2], matrix[6], matrix[10], matrix[14],
        matrix[3], matrix[7], matrix[11], matrix[15]
    );
    ViewAbstract::SetTransformMatrix(value);
}

//position

void SetPosition(NodeHandle node, float x, int xunit, float y, int yunit)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ViewAbstract::SetPosition(frameNode, { CalcLength(x, static_cast<DimensionUnit>(xunit)),
        CalcLength(y, static_cast<DimensionUnit>(yunit)) });
}

//border

void SetBorder(NodeHandle node, ArkUIBorderOptions* options)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    SetBorderWidth(node, options->widthValues, options->widthUnits, options->length[0]);
    SetBorderColor(node, options->colors, options->length[1]);
    SetBorderRadius(node, options->radiusValues, options->radiusUnits, options->length[2]);
    SetBorderStyle(node, options->styles, options->length[3]);
}


//clip

void SetClip()


//circle : width, height
//Elipse: width, height
//Path : width, height, commands(string)
//Rect
//{
    //     width?: number | string;
    //     height?: number | string;
    //     radius?: number | string | Array<any>;
    //   }
    //   | {
    //     width?: number | string;
    //     height?: number | string;
    //     radiusWidth?: number | string;
    //     radiusHeight?: number | string;
    //   },

//
}
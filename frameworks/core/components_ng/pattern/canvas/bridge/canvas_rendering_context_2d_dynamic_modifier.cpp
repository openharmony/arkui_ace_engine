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
#include "core/components_ng/pattern/canvas/canvas_model_ng.h"
#include "core/interfaces/native/node/canvas_rendering_context_2d_modifier.h"

namespace OHOS::Ace::NG {
namespace CanvasRenderingContext2DDynamicModifier {

void SetCanvasBeginPath(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->BeginPath();
}

void SetCanvasClosePath(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->ClosePath();
}

void SetCanvasFill(ArkUINodeHandle node, const char* value)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasFill: value: %{public}s", value);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    std::string ruleStr(value);
    CanvasFillRule fillRule = CanvasFillRule::NONZERO;
    if (ruleStr == "nonzero") {
        fillRule = CanvasFillRule::NONZERO;
    } else if (ruleStr == "evenodd") {
        fillRule = CanvasFillRule::EVENODD;
    }
    canvasPattern->UpdateFillRuleForPath(fillRule);
    canvasPattern->Fill();
}

void SetCanvasMoveTo(ArkUINodeHandle node, float x, float y)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasMoveTo: x: %{public}f, y: %{public}f", x, y);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->MoveTo(x, y);
}

void SetCanvasArc(ArkUINodeHandle node, ArkUICanvasArcOptions* options)
{
    CHECK_NULL_VOID(options);
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasArc: x: %{public}f, y: %{public}f, \
        radius: %{public}f, startAngle: %{public}f, endAngle: %{public}f",
        options->x, options->y, options->radius, options->startAngle, options->endAngle);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    ArcParam param;
    param.x = options->x;
    param.y = options->y;
    param.radius = options->radius;
    param.startAngle = options->startAngle;
    param.endAngle = options->endAngle;
    param.anticlockwise = static_cast<bool>(options->counterclockwise);
    canvasPattern->Arc(param);
}

void SetCanvasLineTo(ArkUINodeHandle node, float x, float y)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasLineTo: x: %{public}f, y: %{public}f", x, y);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->LineTo(x, y);
}

void SetCanvasStrokeStyle(ArkUINodeHandle node, int color)
{
    TAG_LOGD(
        AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasStrokStyle: color: %{public}d", color);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->UpdateStrokeColor(Color(color));
}

ArkUI_Int32 GetCanvasStrokeStyle(ArkUINodeHandle node)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala GetCanvasStrokeStyle STUB");
    return 0xff000000;
}

void SetCanvasLineWidth(ArkUINodeHandle node, float width)
{
    TAG_LOGD(
        AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasStrokStyle: width: %{public}f", width);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->UpdateLineWidth(width);
}

ArkUI_Float32 GetCanvasLineWidth(ArkUINodeHandle node)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala GetCanvasLineWidth STUB");
    return 0xff000000;
}

void SetCanvasStroke(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->Stroke();
}

void SetCanvasAntiAlias(ArkUINodeHandle node, ArkUI_Bool antialias)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasAntiAlias: antialias:%{public}d", antialias);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->SetAntiAlias(static_cast<bool>(antialias));
}

void SetCanvasFillColor(ArkUINodeHandle node, int color)
{
    TAG_LOGD(
        AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasFillColor: color: %{public}d", color);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->UpdateFillColor(Color(color));
}

ArkUI_Int32 GetCanvasFillColor(ArkUINodeHandle node)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala GetCanvasFillColor STUB");
    return 0xff000000;
}

void SetCanvasGlobalAlpha(ArkUINodeHandle node, float alpha)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasGlobalAlpha");
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->UpdateGlobalAlpha(alpha);
}

ArkUI_Float32 GetCanvasGlobalAlpha(ArkUINodeHandle node)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala GetCanvasGlobalAlpha STUB");
    return 0;
}

void SetCanvasFillRect(ArkUINodeHandle node, float x, float y, float w, float h)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasFillRect: x: %{public}f, \
        y: %{public}f, w: %{public}f, h: %{public}f",
        x, y, w, h);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    canvasPattern->FillRect({ x, y, w, h });
}

void SetCanvasFillText(ArkUINodeHandle node, const char* value, float x, float y, float maxWidth)
{
    TAG_LOGD(AceLogTag::ACE_CANVAS_COMPONENT, "Arkoala SetCanvasFillText: value:%{public}s, \
        x: %{public}f, y: %{public}f, maxWith: %{public}f",
        value, x, y, maxWidth);
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    RefPtr<AceType> pattern = CanvasModelNG::GetCanvasPattern(frameNode);
    auto canvasPattern = AceType::DynamicCast<NG::CanvasPattern>(pattern);
    CHECK_NULL_VOID(canvasPattern);
    std::string text(value);
    canvasPattern->FillText(text, x, y, maxWidth);
}

} // namespace CanvasRenderingContext2DDynamicModifier

namespace {

const ArkUICanvasRenderingContext2DModifier* GetArkUICanvasRenderingContext2DModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUICanvasRenderingContext2DModifier modifier = {
        .getCanvasRenderingContext2D = nullptr,
        .setCanvasBeginPath = CanvasRenderingContext2DDynamicModifier::SetCanvasBeginPath,
        .setCanvasClosePath = CanvasRenderingContext2DDynamicModifier::SetCanvasClosePath,
        .setCanvasFill = CanvasRenderingContext2DDynamicModifier::SetCanvasFill,
        .setCanvasMoveTo = CanvasRenderingContext2DDynamicModifier::SetCanvasMoveTo,
        .setCanvasArc = CanvasRenderingContext2DDynamicModifier::SetCanvasArc,
        .setCanvasLineTo = CanvasRenderingContext2DDynamicModifier::SetCanvasLineTo,
        .setCanvasStrokeStyle = CanvasRenderingContext2DDynamicModifier::SetCanvasStrokeStyle,
        .getCanvasStrokeStyle = CanvasRenderingContext2DDynamicModifier::GetCanvasStrokeStyle,
        .setCanvasLineWidth = CanvasRenderingContext2DDynamicModifier::SetCanvasLineWidth,
        .getCanvasLineWidth = CanvasRenderingContext2DDynamicModifier::GetCanvasLineWidth,
        .setCanvasStroke = CanvasRenderingContext2DDynamicModifier::SetCanvasStroke,
        .setCanvasAntiAlias = CanvasRenderingContext2DDynamicModifier::SetCanvasAntiAlias,
        .setCanvasFillColor = CanvasRenderingContext2DDynamicModifier::SetCanvasFillColor,
        .getCanvasFillColor = CanvasRenderingContext2DDynamicModifier::GetCanvasFillColor,
        .setCanvasGlobalAlpha = CanvasRenderingContext2DDynamicModifier::SetCanvasGlobalAlpha,
        .getCanvasGlobalAlpha = CanvasRenderingContext2DDynamicModifier::GetCanvasGlobalAlpha,
        .setCanvasFillRect = CanvasRenderingContext2DDynamicModifier::SetCanvasFillRect,
        .setCanvasFillText = CanvasRenderingContext2DDynamicModifier::SetCanvasFillText,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace

const ArkUICanvasRenderingContext2DModifier* GetCanvasRenderingContext2DDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        return GetArkUICanvasRenderingContext2DModifier();
#endif
    }
    return GetArkUICanvasRenderingContext2DModifier();
}

const CJUICanvasRenderingContext2DModifier* GetCJUICanvasRenderingContext2DDynamicModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUICanvasRenderingContext2DModifier modifier = {
        .getCanvasRenderingContext2D = nullptr,
        .setCanvasBeginPath = CanvasRenderingContext2DDynamicModifier::SetCanvasBeginPath,
        .setCanvasClosePath = CanvasRenderingContext2DDynamicModifier::SetCanvasClosePath,
        .setCanvasFill = CanvasRenderingContext2DDynamicModifier::SetCanvasFill,
        .setCanvasMoveTo = CanvasRenderingContext2DDynamicModifier::SetCanvasMoveTo,
        .setCanvasArc = CanvasRenderingContext2DDynamicModifier::SetCanvasArc,
        .setCanvasLineTo = CanvasRenderingContext2DDynamicModifier::SetCanvasLineTo,
        .setCanvasStrokeStyle = CanvasRenderingContext2DDynamicModifier::SetCanvasStrokeStyle,
        .getCanvasStrokeStyle = CanvasRenderingContext2DDynamicModifier::GetCanvasStrokeStyle,
        .setCanvasLineWidth = CanvasRenderingContext2DDynamicModifier::SetCanvasLineWidth,
        .getCanvasLineWidth = CanvasRenderingContext2DDynamicModifier::GetCanvasLineWidth,
        .setCanvasStroke = CanvasRenderingContext2DDynamicModifier::SetCanvasStroke,
        .setCanvasAntiAlias = CanvasRenderingContext2DDynamicModifier::SetCanvasAntiAlias,
        .setCanvasFillColor = CanvasRenderingContext2DDynamicModifier::SetCanvasFillColor,
        .getCanvasFillColor = CanvasRenderingContext2DDynamicModifier::GetCanvasFillColor,
        .setCanvasGlobalAlpha = CanvasRenderingContext2DDynamicModifier::SetCanvasGlobalAlpha,
        .getCanvasGlobalAlpha = CanvasRenderingContext2DDynamicModifier::GetCanvasGlobalAlpha,
        .setCanvasFillRect = CanvasRenderingContext2DDynamicModifier::SetCanvasFillRect,
        .setCanvasFillText = CanvasRenderingContext2DDynamicModifier::SetCanvasFillText,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}

} // namespace OHOS::Ace::NG

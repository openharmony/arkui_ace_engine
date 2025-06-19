/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "core/interfaces/native/node/node_custom_node_ext_modifier.h"

#include "base/utils/string_utils.h"
#include "core/components/common/properties/color.h"
#include "core/components_ng/pattern/custom_node_ext/custom_node_ext_model_ng.h"
#include "core/components_ng/property/layout_constraint.h"
#include "core/interfaces/arkoala/arkoala_api.h"
#include "core/pipeline_ng/pipeline_context.h"

namespace OHOS::Ace::NG {
namespace {
    constexpr uint32_t STR_MAX_LENGTH = 2048;
}

ArkUI_Bool ParseColorString(ArkUI_CharPtr colorStr, ArkUI_Uint32* colorValue)
{
    Color color;
    if (Color::ParseColorString(std::string(colorStr), color)) {
        *colorValue = color.GetValue();
        return true;
    }
    return false;
}

ArkUI_Bool ParseLengthString(ArkUI_CharPtr lengthStr, ArkUI_Int32* unit,
    ArkUI_Float32* floatData, ArkUI_CommonCharPtr strData)
{
    CalcDimension dimension = StringUtils::StringToCalcDimension(std::string(lengthStr), false, DimensionUnit::VP);
    if (dimension.Unit() == DimensionUnit::VP || dimension.Unit() == DimensionUnit::FP) {
        *floatData = dimension.ConvertToPx();
        *unit = static_cast<ArkUI_Int32>(DimensionUnit::PX);
        return true;
    }

    *unit = static_cast<ArkUI_Int32>(dimension.Unit());
    *floatData = dimension.Value();
    std::string str = dimension.CalcValue();
    if (str.length() > STR_MAX_LENGTH) {
        return false;
    }
    str[STR_MAX_LENGTH - 1] = '\0';
    for (uint32_t index = 0; index < STR_MAX_LENGTH - 1; index++) {
        strData[index] = str[index];
    }
    return true;
}

ArkUI_Float64 GetDpi()
{
    return PipelineBase::GetCurrentDensity();
}

ArkUI_Int32 GetLayoutDirection(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    auto layoutProperty = frameNode->GetLayoutProperty();
    CHECK_NULL_RETURN(layoutProperty, 0);
    auto layoutDirection = layoutProperty->GetNonAutoLayoutDirection();
    return static_cast<ArkUI_Int32>(layoutDirection);
}

void SetCustomMeasureCallback(ArkUINodeHandle node,
    void (*setCustomMeasure)(ArkUINodeHandle node, ArkUIConstraintSizeOptions option))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onMeasure = [node, setCustomMeasure](LayoutConstraintF constraints) {
        ArkUIConstraintSizeOptions options;
        options.minWidth = constraints.minSize.Width();
        options.minHeight = constraints.minSize.Height();
        options.maxWidth = constraints.maxSize.Width();
        options.maxHeight = constraints.maxSize.Height();
        setCustomMeasure(node, options);
    };
    CustomNodeExtModelNG::SetMeasureCallback(frameNode, std::move(onMeasure));
}

void SetCustomLayoutCallback(ArkUINodeHandle node, void (*setCustomLayout)(ArkUINodeHandle node, ArkUIRect rect))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onLayout = [node, setCustomLayout](RectF rect) {
        ArkUIRect rect_;
        rect_.width = rect.Width();
        rect_.height = rect.Height();
        rect_.x = rect.GetX();
        rect_.y = rect.GetY();
        setCustomLayout(node, rect_);
    };
    CustomNodeExtModelNG::SetLayoutCallback(frameNode, std::move(onLayout));
}

void SetCustomContentDrawCallback(ArkUINodeHandle node, CustomDrawFunc drawFunc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onContentDraw = [node, drawFunc](DrawingContext context) {
        ArkUIDrawingContext drawContext;
        drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
        drawContext.width = context.width;
        drawContext.height = context.height;
        drawFunc(node, drawContext);
    };
    CustomNodeExtModelNG::SetContentDrawCallback(frameNode, std::move(onContentDraw));
}

void SetCustomForegroundDrawCallback(ArkUINodeHandle node, CustomDrawFunc drawFunc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onForegroundDraw = [node, drawFunc](DrawingContext context) {
        ArkUIDrawingContext drawContext;
        drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
        drawContext.width = context.width;
        drawContext.height = context.height;
        drawFunc(node, drawContext);
    };
    CustomNodeExtModelNG::SetForegroundDrawCallback(frameNode, std::move(onForegroundDraw));
}

void SetCustomOverlayDrawCallback(ArkUINodeHandle node, CustomDrawFunc drawFunc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onOverlayDraw = [node, drawFunc](DrawingContext context) {
        ArkUIDrawingContext drawContext;
        drawContext.canvas = reinterpret_cast<ArkUICanvasHandle>(&context.canvas);
        drawContext.width = context.width;
        drawContext.height = context.height;
        drawFunc(node, drawContext);
    };
    CustomNodeExtModelNG::SetOverlayDrawCallback(frameNode, std::move(onOverlayDraw));
}

void SetOnConfigUpdateCallback(ArkUINodeHandle node,
    void (*onConfigUpdate)(ArkUINodeHandle node, ArkUIConfigType type))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onUpdate = [node, onConfigUpdate](ConfigurationType configType) {
        ArkUIConfigType type = static_cast<ArkUIConfigType>(configType);
        onConfigUpdate(node, type);
    };
    CustomNodeExtModelNG::SetOnConfigUpdateCallback(frameNode, std::move(onUpdate));
}

void SetOnModifyDoneCallback(ArkUINodeHandle node, void (*onModifyDone)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onModifyDoneCallback = [node, onModifyDone]() {
        onModifyDone(node);
    };
    CustomNodeExtModelNG::SetOnModifyDoneCallback(frameNode, std::move(onModifyDoneCallback));
}

void SetOnDirtyLayoutWrapperSwap(ArkUINodeHandle node,
    void (*onDirtySwap)(ArkUINodeHandle node, ArkUIDirtySwapConfig config))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onDirtySwapCallback = [node, onDirtySwap](const DirtySwapConfig& config) {
        ArkUIDirtySwapConfig configuration;
        configuration.frameSizeChange = config.frameSizeChange;
        configuration.frameOffsetChange = config.frameOffsetChange;
        configuration.contentSizeChange = config.contentSizeChange;
        configuration.contentOffsetChange = config.contentOffsetChange;
        configuration.skipMeasure = config.skipMeasure;
        configuration.skipLayout = config.skipLayout;
        onDirtySwap(node, configuration);
    };
    CustomNodeExtModelNG::SetOnDirtyLayoutWrapperSwap(frameNode, std::move(onDirtySwapCallback));
}

void SetIsAtomic(ArkUINodeHandle node, const ArkUI_Bool isAtomic)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CustomNodeExtModelNG::SetIsAtomic(frameNode, static_cast<bool>(isAtomic));
}

void SetBeforeCreateLayoutWrapperCallback(ArkUINodeHandle node, void (*beforeCreateLayoutWrapper)(ArkUINodeHandle node))
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto beforeCreateLayoutWrapperCallback = [node, beforeCreateLayoutWrapper]() {
        beforeCreateLayoutWrapper(node);
    };
    CustomNodeExtModelNG::SetBeforeCreateLayoutWrapperCallback(frameNode, std::move(beforeCreateLayoutWrapperCallback));
}

namespace NodeModifier {
const struct ArkUICustomNodeExtModifier* GetCustomNodeExtModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const struct ArkUICustomNodeExtModifier modifiers = {
        .parseColorString = ParseColorString,
        .parseLengthString = ParseLengthString,
        .getDpi = GetDpi,
        .getLayoutDirection = GetLayoutDirection,
        .setCustomMeasure = SetCustomMeasureCallback,
        .setCustomLayout = SetCustomLayoutCallback,
        .setCustomContentDraw = SetCustomContentDrawCallback,
        .setCustomForegroundDraw = SetCustomForegroundDrawCallback,
        .setCustomOverlayDraw = SetCustomOverlayDrawCallback,
        .setOnConfigUpdate = SetOnConfigUpdateCallback,
        .setOnModifyDone = SetOnModifyDoneCallback,
        .setOnDirtyLayoutWrapperSwap = SetOnDirtyLayoutWrapperSwap,
        .setIsAtomic = SetIsAtomic,
        .setBeforeCreateLayoutWrapper = SetBeforeCreateLayoutWrapperCallback
    };
    CHECK_INITIALIZED_FIELDS_END(modifiers, 0, 0, 0); // don't move this line
    return &modifiers;
}
} // NodeModifier
} // OHOS::Ace::NG
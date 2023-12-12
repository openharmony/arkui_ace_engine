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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_image_modifier.h"

#include "base/utils/utils.h"
#include "core/components/image/image_component.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/image/image_model_ng.h"
#include "core/pipeline/base/element_register.h"
#include "frameworks/core/components/common/layout/constants.h"
#include "core/components/common/properties/alignment.h"
#include "core/components/image/image_theme.h"

namespace OHOS::Ace::NG {
constexpr CopyOptions DEFAULT_IMAGE_COPYOPTION = CopyOptions::None;
constexpr bool DEFAULT_IMAGE_AUTORESIZE = true;
constexpr bool DEFAULT_SYNC_LOAD_VALUE = false;
constexpr ImageFit DEFAULT_OBJECT_FIT_VALUE = ImageFit::COVER;
constexpr bool DEFAULT_FIT_ORIGINAL_SIZE = false;
constexpr ImageInterpolation DEFAULT_IMAGE_INTERPOLATION = ImageInterpolation::NONE;
constexpr bool DEFAULT_DRAGGABLE = false;
const std::vector<float> DEFAULT_COLOR_FILTER = { 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0 };

void SetCopyOption(NodeHandle node, int32_t copyOption)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto copyOptions = static_cast<CopyOptions>(copyOption);
    if (copyOptions < CopyOptions::None || copyOptions > CopyOptions::Distributed) {
        copyOptions = DEFAULT_IMAGE_COPYOPTION;
    }
    ImageModelNG::SetCopyOption(frameNode, copyOptions);
}

void ResetCopyOption(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetCopyOption(frameNode, DEFAULT_IMAGE_COPYOPTION);
}

void SetAutoResize(NodeHandle node, bool autoResize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAutoResize(frameNode, autoResize);
}

void ResetAutoResize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAutoResize(frameNode, DEFAULT_IMAGE_AUTORESIZE);
}

void SetObjectRepeat(NodeHandle node, int32_t imageRepeat)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto repeat = static_cast<ImageRepeat>(imageRepeat);
    if (repeat < ImageRepeat::NO_REPEAT || repeat > ImageRepeat::REPEAT) {
        repeat = ImageRepeat::NO_REPEAT;
    }
    ImageModelNG::SetImageRepeat(frameNode, repeat);
}

void ResetObjectRepeat(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRepeat(frameNode, ImageRepeat::NO_REPEAT);
}

void SetRenderMode(NodeHandle node, int32_t imageRenderMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto renderMode = static_cast<ImageRenderMode>(imageRenderMode);
    if (renderMode < ImageRenderMode::ORIGINAL || renderMode > ImageRenderMode::TEMPLATE) {
        renderMode = ImageRenderMode::ORIGINAL;
    }
    ImageModelNG::SetImageRenderMode(frameNode, renderMode);
}

void ResetRenderMode(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageRenderMode(frameNode, ImageRenderMode::ORIGINAL);
}

void SetSyncLoad(NodeHandle node, bool syncLoadValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, syncLoadValue);
}

void ResetSyncLoad(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, DEFAULT_SYNC_LOAD_VALUE);
}

void SetObjectFit(NodeHandle node, int32_t objectFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(objectFitNumber);
    if (objectFitValue < ImageFit::FILL || objectFitValue > ImageFit::SCALE_DOWN) {
        objectFitValue = ImageFit::COVER;
    }
    ImageModelNG::SetImageFit(frameNode, objectFitValue);
}

void ResetObjectFit(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT_VALUE);
}

void SetFitOriginalSize(NodeHandle node, bool fitOriginalSizeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, fitOriginalSizeValue);
}

void ResetFitOriginalSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, DEFAULT_FIT_ORIGINAL_SIZE);
}

void SetSourceSize(NodeHandle node, double width, double height)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CalcDimension widthObj(width, DimensionUnit::VP);
    CalcDimension heightObj(height, DimensionUnit::VP);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>(widthObj, heightObj));
}

void ResetSourceSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageSourceSize(frameNode, std::pair<CalcDimension, CalcDimension>());
}

void SetMatchTextDirection(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, static_cast<bool>(value));
}

void ResetMatchTextDirection(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetMatchTextDirection(frameNode, false);
}

void SetFillColor(NodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFill(frameNode, Color(value));
}

void ResetFillColor(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto pipelineContext = PipelineBase::GetCurrentContext();
    CHECK_NULL_VOID(pipelineContext);
    auto theme = pipelineContext->GetTheme<ImageTheme>();
    CHECK_NULL_VOID(theme);
    ImageModelNG::SetImageFill(frameNode, theme->GetFillColor());
}

void SetAlt(NodeHandle node, const char* src, const char* bundleName, const char* moduleName)
{
    if (ImageSourceInfo::ResolveURIType(src) == SrcType::NETWORK) {
        return;
    }

    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetAlt(frameNode, ImageSourceInfo { src, bundleName, moduleName });
}

void ResetAlt(NodeHandle node)
{
    return;
}

void SetImageInterpolation(NodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto interpolation = static_cast<Ace::ImageInterpolation>(value);
    if (interpolation < Ace::ImageInterpolation::NONE || interpolation > Ace::ImageInterpolation::HIGH) {
        interpolation = Ace::ImageInterpolation::NONE;
    }
    ImageModelNG::SetImageInterpolation(frameNode, interpolation);
}

void ResetImageInterpolation(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageInterpolation(frameNode, DEFAULT_IMAGE_INTERPOLATION);
}

void SetColorFilter(NodeHandle node, const float* array, int length)
{
    CHECK_NULL_VOID(array);
    if (length != COLOR_FILTER_MATRIX_SIZE) {
        return;
    }
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, std::vector<float>(array, array + length));
}

void ResetColorFilter(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetColorFilterMatrix(frameNode, DEFAULT_COLOR_FILTER);
}

void SetImageSyncLoad(NodeHandle node, bool syncLoadValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, syncLoadValue);
}

void ResetImageSyncLoad(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetSyncMode(frameNode, DEFAULT_SYNC_LOAD_VALUE);
}

void SetImageObjectFit(NodeHandle node, int32_t objectFitNumber)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageFit objectFitValue = static_cast<ImageFit>(objectFitNumber);
    ImageModelNG::SetImageFit(frameNode, objectFitValue);
}

void ResetImageObjectFit(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetImageFit(frameNode, DEFAULT_OBJECT_FIT_VALUE);
}

void SetImageFitOriginalSize(NodeHandle node, bool fitOriginalSizeValue)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, fitOriginalSizeValue);
}

void ResetImageFitOriginalSize(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetFitOriginSize(frameNode, DEFAULT_FIT_ORIGINAL_SIZE);
}

void SetImageDraggable(NodeHandle node, bool value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, value);
}

void ResetImageDraggable(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageModelNG::SetDraggable(frameNode, DEFAULT_DRAGGABLE);
}

ArkUIImageModifierAPI GetImageModifier()
{
    static const ArkUIImageModifierAPI modifier = { SetCopyOption, ResetCopyOption, SetAutoResize, ResetAutoResize,
        SetObjectRepeat, ResetObjectRepeat, SetRenderMode, ResetRenderMode, SetSyncLoad, ResetSyncLoad, SetObjectFit,
        ResetObjectFit, SetFitOriginalSize, ResetFitOriginalSize, SetSourceSize, ResetSourceSize, SetMatchTextDirection,
        ResetMatchTextDirection, SetFillColor, ResetFillColor, SetAlt, ResetAlt, SetImageInterpolation,
        ResetImageInterpolation, SetColorFilter, ResetColorFilter, SetImageSyncLoad, ResetImageSyncLoad,
        SetImageObjectFit, ResetImageObjectFit, SetImageFitOriginalSize, ResetImageFitOriginalSize, SetImageDraggable,
        ResetImageDraggable };

    return modifier;
}
} // namespace OHOS::Ace::NG
/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "core/interfaces/native/node/image_animator_modifier.h"

#include "core/components_ng/pattern/image_animator/image_animator_model_ng.h"

namespace OHOS::Ace::NG {
constexpr int32_t DEFAULT_DURATION = 1000; // ms
constexpr int32_t DEFAULT_ITERATION = 1;
constexpr FillMode DEFAULT_FILL_MODE = FillMode::FORWARDS;
constexpr uint32_t DEFAULT_ITERATIONS = 1;
constexpr int32_t IMAGES_LENGTH = 4;
constexpr int32_t DEFAULT_STATE = 0;

namespace ImageAnimatorModifier {
void ParseImage(CalcDimension* dimension, int32_t dimensionLength, const ArkUIImagePropertiesStruct* image)
{
    for (int32_t i = 0; i < dimensionLength; i++) {
        if (image->unit[i] == static_cast<int8_t>(DimensionUnit::CALC)) {
            dimension[i].SetUnit(DimensionUnit::CALC);
            dimension[i].SetValue(0.0);
            dimension[i].SetCalcValue(std::string(image->calc[i]));
        } else {
            dimension[i].SetUnit(static_cast<DimensionUnit>(image->unit[i]));
            dimension[i].SetValue(image->number[i]);
        }
    }
}

void SetState(ArkUINodeHandle node, int32_t state)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    int32_t value = state;
    if (value < static_cast<int32_t>(Animator::Status::IDLE) ||
        value > static_cast<int32_t>(Animator::Status::STOPPED)) {
        value = static_cast<int32_t>(Animator::Status::IDLE);
    }

    ImageAnimatorModelNG::SetState(frameNode, value);
}

void ResetState(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetState(frameNode, static_cast<int32_t>(Animator::Status::IDLE));
}

void SetDuration(ArkUINodeHandle node, int32_t duration)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (duration < 0) {
        duration = DEFAULT_DURATION;
    }
    ImageAnimatorModelNG::SetDuration(frameNode, duration);
}

void SetFixedSize(ArkUINodeHandle node, uint32_t fixedSize)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ImageAnimatorModelNG::SetFixedSize(frameNode, static_cast<bool>(fixedSize));
}

void ResetFixedSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    ImageAnimatorModelNG::SetFixedSize(frameNode, true);
}

void SetFillMode(ArkUINodeHandle node, int32_t fillMode)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    int32_t value = fillMode;
    if (value < static_cast<int32_t>(FillMode::NONE) || value > static_cast<int32_t>(FillMode::BOTH)) {
        value = static_cast<int32_t>(DEFAULT_FILL_MODE);
    }

    ImageAnimatorModelNG::SetFillMode(frameNode, value);
}

void ResetFillMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetFillMode(frameNode, static_cast<int32_t>(DEFAULT_FILL_MODE));
}

void SetReverse(ArkUINodeHandle node, uint32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetIsReverse(frameNode, static_cast<bool>(value));
}

void ResetReverse(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetIsReverse(frameNode, false);
}

void SetImages(ArkUINodeHandle node, struct ArkUIImagePropertiesStruct* images, int32_t length)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (length == 0) {
        ImageAnimatorModelNG::SetImages(frameNode, std::vector<ImageProperties>());
        return;
    }
    CHECK_NULL_VOID(images);
    if (length <= 0) {
        return;
    }
    std::vector<ImageProperties> imageList;
    for (int32_t i = 0; i < length; i++) {
        ArkUIImagePropertiesStruct* image = images + i;
        CHECK_NULL_VOID(image);
        CalcDimension dimension[IMAGES_LENGTH];
        ParseImage(dimension, IMAGES_LENGTH, image);
        ImageProperties property { std::string(image->src), nullptr, "", "", dimension[0], dimension[1], dimension[2],
            dimension[3], image->duration };
        imageList.emplace_back(property);
    }
    ImageAnimatorModelNG::SetImages(frameNode, imageList);
}

void ResetImages(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetImages(frameNode, std::vector<ImageProperties>());
}

void SetImageAnimatorIteration(ArkUINodeHandle node, int32_t value)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);

    int32_t iteration = value;
    if (iteration < -1) {
        iteration = DEFAULT_ITERATIONS;
    }

    ImageAnimatorModelNG::SetIteration(frameNode, iteration);
}

void ResetImageAnimatorIteration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetIteration(frameNode, DEFAULT_ITERATION);
}

void SetImageAnimatorSrc(ArkUINodeHandle node, ArkUIImageFrameInfo* imageInfos, ArkUI_Int32 size)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    if (size <= 0) {
        ImageAnimatorModelNG::SetImages(frameNode, std::vector<ImageProperties>());
        return;
    }
    CHECK_NULL_VOID(imageInfos);
    std::vector<ImageProperties> imageList;
    for (int32_t i = 0; i < size; i++) {
        ArkUIImageFrameInfo* image = imageInfos + i;
        CHECK_NULL_VOID(image);
        ImageProperties property;
        auto pixelmap = PixelMap::GetFromDrawable(image->drawable);
        if (pixelmap) {
            property.pixelMap = pixelmap;
        } else {
            property.src = std::string(image->src);
        }
        property.width = CalcDimension(static_cast<double>(image->width), static_cast<DimensionUnit>(image->unit));
        property.height = CalcDimension(static_cast<double>(image->height), static_cast<DimensionUnit>(image->unit));
        property.top = CalcDimension(static_cast<double>(image->top), static_cast<DimensionUnit>(image->unit));
        property.left = CalcDimension(static_cast<double>(image->left), static_cast<DimensionUnit>(image->unit));
        property.duration = image->duration;
        imageList.emplace_back(property);
    }
    ImageAnimatorModelNG::SetImages(frameNode, imageList);
}

void ResetDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetDuration(frameNode, DEFAULT_DURATION);
}

ArkUI_Bool GetIsReverse(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, false);
    return static_cast<ArkUI_Bool>(ImageAnimatorModelNG::IsReverse(frameNode));
}

int32_t GetDuration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_DURATION);
    return ImageAnimatorModelNG::GetDuration(frameNode);
}

int32_t GetState(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_STATE);
    return ImageAnimatorModelNG::GetState(frameNode);
}

ArkUI_Bool GetIsFixedSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, true);
    return static_cast<ArkUI_Bool>(ImageAnimatorModelNG::IsFixedSize(frameNode));
}

int32_t GetFillMode(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, static_cast<int32_t>(DEFAULT_FILL_MODE));
    return ImageAnimatorModelNG::GetFillMode(frameNode);
}

int32_t GetIteration(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, DEFAULT_ITERATION);
    return ImageAnimatorModelNG::GetIteration(frameNode);
}

int32_t GetImagesSize(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_RETURN(frameNode, 0);
    return ImageAnimatorModelNG::GetImagesSize(frameNode);
}
} // namespace ImageAnimatorModifier

namespace NodeModifier {
const ArkUIImageAnimatorModifier* GetImageAnimatorModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIImageAnimatorModifier modifier = {
        .setState = ImageAnimatorModifier::SetState,
        .resetState = ImageAnimatorModifier::ResetState,
        .setDuration = ImageAnimatorModifier::SetDuration,
        .setFixedSize = ImageAnimatorModifier::SetFixedSize,
        .resetFixedSize = ImageAnimatorModifier::ResetFixedSize,
        .setFillMode = ImageAnimatorModifier::SetFillMode,
        .resetFillMode = ImageAnimatorModifier::ResetFillMode,
        .setReverse = ImageAnimatorModifier::SetReverse,
        .resetReverse = ImageAnimatorModifier::ResetReverse,
        .setImages = ImageAnimatorModifier::SetImages,
        .resetImages = ImageAnimatorModifier::ResetImages,
        .setImageAnimatorIteration = ImageAnimatorModifier::SetImageAnimatorIteration,
        .resetImageAnimatorIteration = ImageAnimatorModifier::ResetImageAnimatorIteration,
        .setImageAnimatorSrc = ImageAnimatorModifier::SetImageAnimatorSrc,
        .resetDuration = ImageAnimatorModifier::ResetDuration,
        .getIsReverse = ImageAnimatorModifier::GetIsReverse,
        .getDuration = ImageAnimatorModifier::GetDuration,
        .getState = ImageAnimatorModifier::GetState,
        .getFixedSize = ImageAnimatorModifier::GetIsFixedSize,
        .getFillMode = ImageAnimatorModifier::GetFillMode,
        .getIteration = ImageAnimatorModifier::GetIteration,
        .getImagesSize = ImageAnimatorModifier::GetImagesSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

const CJUIImageAnimatorModifier* GetCJUIImageAnimatorModifier()
{
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const CJUIImageAnimatorModifier modifier = {
        .setState = ImageAnimatorModifier::SetState,
        .resetState = ImageAnimatorModifier::ResetState,
        .setDuration = ImageAnimatorModifier::SetDuration,
        .setFixedSize = ImageAnimatorModifier::SetFixedSize,
        .resetFixedSize = ImageAnimatorModifier::ResetFixedSize,
        .setFillMode = ImageAnimatorModifier::SetFillMode,
        .resetFillMode = ImageAnimatorModifier::ResetFillMode,
        .setReverse = ImageAnimatorModifier::SetReverse,
        .resetReverse = ImageAnimatorModifier::ResetReverse,
        .setImages = ImageAnimatorModifier::SetImages,
        .resetImages = ImageAnimatorModifier::ResetImages,
        .setImageAnimatorIteration = ImageAnimatorModifier::SetImageAnimatorIteration,
        .resetImageAnimatorIteration = ImageAnimatorModifier::ResetImageAnimatorIteration,
        .setImageAnimatorSrc = ImageAnimatorModifier::SetImageAnimatorSrc,
        .resetDuration = ImageAnimatorModifier::ResetDuration,
        .getIsReverse = ImageAnimatorModifier::GetIsReverse,
        .getDuration = ImageAnimatorModifier::GetDuration,
        .getState = ImageAnimatorModifier::GetState,
        .getFixedSize = ImageAnimatorModifier::GetIsFixedSize,
        .getFillMode = ImageAnimatorModifier::GetFillMode,
        .getIteration = ImageAnimatorModifier::GetIteration,
        .getImagesSize = ImageAnimatorModifier::GetImagesSize,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line

    return &modifier;
}

void SetImageAnimatorOnStart(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ANIMATOR_ON_START;
        SendArkUISyncEvent(&event);
    };
    ImageAnimatorModelNG::SetOnStart(frameNode, std::move(onEvent));
}

void SetImageAnimatorOnPause(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ANIMATOR_ON_PAUSE;
        SendArkUISyncEvent(&event);
    };
    ImageAnimatorModelNG::SetOnPause(frameNode, std::move(onEvent));
}

void SetImageAnimatorOnRepeat(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ANIMATOR_ON_REPEAT;
        SendArkUISyncEvent(&event);
    };
    ImageAnimatorModelNG::SetOnRepeat(frameNode, std::move(onEvent));
}

void SetImageAnimatorOnCancel(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ANIMATOR_ON_CANCEL;
        SendArkUISyncEvent(&event);
    };
    ImageAnimatorModelNG::SetOnCancel(frameNode, std::move(onEvent));
}

void SetImageAnimatorOnFinish(ArkUINodeHandle node, void* extraParam)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    auto onEvent = [node, extraParam]() {
        ArkUINodeEvent event;
        event.kind = COMPONENT_ASYNC_EVENT;
        event.extraParam = reinterpret_cast<intptr_t>(extraParam);
        event.componentAsyncEvent.subKind = ON_IMAGE_ANIMATOR_ON_FINISH;
        SendArkUISyncEvent(&event);
    };
    ImageAnimatorModelNG::SetOnFinish(frameNode, std::move(onEvent));
}

void ResetImageAnimatorOnStart(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetOnStart(frameNode, nullptr);
}
void ResetImageAnimatorOnPause(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetOnPause(frameNode, nullptr);
}
void ResetImageAnimatorOnRepeat(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetOnRepeat(frameNode, nullptr);
}
void ResetImageAnimatorOnCancel(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetOnCancel(frameNode, nullptr);
}
void ResetImageAnimatorOnFinish(ArkUINodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    ImageAnimatorModelNG::SetOnFinish(frameNode, nullptr);
}
}
} // namespace OHOS::Ace::NG

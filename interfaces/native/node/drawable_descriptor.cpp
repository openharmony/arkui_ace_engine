/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

#include "node_extened.h"
#include "node_model.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

constexpr uint32_t ANIMATED_TYPE = 2;

ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromPixelMap(OH_PixelmapNativeHandle pixelMap)
{
    CHECK_NULL_RETURN(pixelMap, nullptr);
    ArkUI_DrawableDescriptor* drawableDescriptor =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    drawableDescriptor->pixelMap = pixelMap;
    drawableDescriptor->drawableDescriptor =
        std::make_shared<OHOS::Ace::Napi::DrawableDescriptor>(pixelMap->GetInnerPixelmap());
    return drawableDescriptor;
}

ArkUI_DrawableDescriptor* OH_ArkUI_DrawableDescriptor_CreateFromAnimatedPixelMap(
    OH_PixelmapNativeHandle* array, int32_t size)
{
    CHECK_NULL_RETURN(array, nullptr);
    ArkUI_DrawableDescriptor* drawableDescriptor =
        new ArkUI_DrawableDescriptor { nullptr, nullptr, 0, nullptr, nullptr, nullptr, nullptr };
    drawableDescriptor->pixelMapArray = array;
    drawableDescriptor->size = size;
    auto* drawable = OHOS::Ace::NodeModel::CreateDrawable(ANIMATED_TYPE);
    std::vector<void*> rawPixelMaps;
    for (int32_t index = 0; index < size; index++) {
        if (!array[index]) {
            continue;
        }
        auto pixelMap = array[index]->GetInnerPixelmap();
        rawPixelMaps.push_back(reinterpret_cast<void*>(&pixelMap));
    }
    int32_t duration = -1;
    int32_t iteration = 1;
    OHOS::Ace::NodeModel::SetTotalDuration(drawable, duration);
    OHOS::Ace::NodeModel::SetIterations(drawable, iteration);
    OHOS::Ace::NodeModel::IncreaseRefDrawable(drawable);
    drawableDescriptor->newDrawableDescriptor = drawable;
    return drawableDescriptor;
}

void OH_ArkUI_DrawableDescriptor_Dispose(ArkUI_DrawableDescriptor* drawableDescriptor)
{
    if (drawableDescriptor->newDrawableDescriptor) {
        OHOS::Ace::NodeModel::DecreaseRefDrawable(drawableDescriptor->newDrawableDescriptor);
    }
    delete drawableDescriptor;
}

OH_PixelmapNativeHandle OH_ArkUI_DrawableDescriptor_GetStaticPixelMap(ArkUI_DrawableDescriptor* drawableDescriptor)
{
    CHECK_NULL_RETURN(drawableDescriptor, nullptr);
    return drawableDescriptor->pixelMap;
}

OH_PixelmapNativeHandle* OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArray(
    ArkUI_DrawableDescriptor* drawableDescriptor)
{
    CHECK_NULL_RETURN(drawableDescriptor, nullptr);
    return drawableDescriptor->pixelMapArray;
}

int32_t OH_ArkUI_DrawableDescriptor_GetAnimatedPixelMapArraySize(ArkUI_DrawableDescriptor* drawableDescriptor)
{
    CHECK_NULL_RETURN(drawableDescriptor, 0);
    return drawableDescriptor->size;
}

void OH_ArkUI_DrawableDescriptor_SetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor, int32_t duration)
{
    CHECK_NULL_VOID(drawableDescriptor);
    CHECK_NULL_VOID(drawableDescriptor->newDrawableDescriptor);
    OHOS::Ace::NodeModel::SetTotalDuration(drawableDescriptor->newDrawableDescriptor, duration);
}

int32_t OH_ArkUI_DrawableDescriptor_GetAnimationDuration(ArkUI_DrawableDescriptor* drawableDescriptor)
{
    CHECK_NULL_RETURN(drawableDescriptor, -1);
    CHECK_NULL_RETURN(drawableDescriptor->newDrawableDescriptor, -1);
    return OHOS::Ace::NodeModel::GetTotalDuration(drawableDescriptor->newDrawableDescriptor);
}

void OH_ArkUI_DrawableDescriptor_SetAnimationIteration(ArkUI_DrawableDescriptor* drawableDescriptor, int32_t iteration)
{
    CHECK_NULL_VOID(drawableDescriptor);
    CHECK_NULL_VOID(drawableDescriptor->newDrawableDescriptor);
    OHOS::Ace::NodeModel::SetIterations(drawableDescriptor->newDrawableDescriptor, iteration);
}

int32_t OH_ArkUI_DrawableDescriptor_GetAnimationIteration(ArkUI_DrawableDescriptor* drawableDescriptor)
{
    CHECK_NULL_RETURN(drawableDescriptor, 1);
    CHECK_NULL_RETURN(drawableDescriptor->newDrawableDescriptor, 1);
    return OHOS::Ace::NodeModel::GetIterations(drawableDescriptor->newDrawableDescriptor);
}

#ifdef __cplusplus
};
#endif

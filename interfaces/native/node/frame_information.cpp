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
#include "frame_information.h"

#include "base/utils/utils.h"

#ifdef __cplusplus
extern "C" {
#endif

ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromString(char* src)
{
    CHECK_NULL_RETURN(src, nullptr);
    ArkUI_ImageAnimatorFrameInfo* imageInfo = new ArkUI_ImageAnimatorFrameInfo;
    imageInfo->src = src;
    imageInfo->drawableDescriptor = nullptr;
    return imageInfo;
}

ArkUI_ImageAnimatorFrameInfo* OH_ArkUI_ImageAnimatorFrameInfo_CreateFromDrawableDescriptor(
    ArkUI_DrawableDescriptor* drawable)
{
    CHECK_NULL_RETURN(drawable, nullptr);
    ArkUI_ImageAnimatorFrameInfo* imageInfo = new ArkUI_ImageAnimatorFrameInfo;
    imageInfo->src = "";
    imageInfo->drawableDescriptor = drawable;
    return imageInfo;
}

void OH_ArkUI_ImageAnimatorFrameInfo_Dispose(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_VOID(imageInfo);
    delete imageInfo;
}

void OH_ArkUI_ImageAnimatorFrameInfo_SetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t width)
{
    CHECK_NULL_VOID(imageInfo);
    imageInfo->width = width;
}

int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetWidth(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_RETURN(imageInfo, 0);
    return imageInfo->width.value_or(0);
}

void OH_ArkUI_ImageAnimatorFrameInfo_SetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t height)
{
    CHECK_NULL_VOID(imageInfo);
    imageInfo->height = height;
}

int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetHeight(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_RETURN(imageInfo, 0);
    return imageInfo->height.value_or(0);
}

void OH_ArkUI_ImageAnimatorFrameInfo_SetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t top)
{
    CHECK_NULL_VOID(imageInfo);
    imageInfo->top = top;
}

int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetTop(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_RETURN(imageInfo, 0);
    return imageInfo->top.value_or(0);
}

void OH_ArkUI_ImageAnimatorFrameInfo_SetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t left)
{
    CHECK_NULL_VOID(imageInfo);
    imageInfo->left = left;
}

int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetLeft(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_RETURN(imageInfo, 0);
    return imageInfo->left.value_or(0);
}

void OH_ArkUI_ImageAnimatorFrameInfo_SetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo, int32_t duration)
{
    CHECK_NULL_VOID(imageInfo);
    imageInfo->duration = duration;
}

int32_t OH_ArkUI_ImageAnimatorFrameInfo_GetDuration(ArkUI_ImageAnimatorFrameInfo* imageInfo)
{
    CHECK_NULL_RETURN(imageInfo, 0);
    return imageInfo->duration.value_or(0);
}
#ifdef __cplusplus
};
#endif

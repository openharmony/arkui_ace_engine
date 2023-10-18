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

#ifndef FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_COMMON_MODIFIER_H
#define FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_COMMON_MODIFIER_H

namespace OHOS::Ace::NG {
typedef void* NodeHandle;

struct ArkUIBorderOptions
{
    float* widthValues;
    int* widthUnits;
    int* colors;
    float* radiusValues;
    int* radiusUnits;
    int* styles;
    int* length;
};

NodeHandle GetFrameNodeById(int id);

void ApplyModifierFinish(NodeHandle node);

void SetBackgroundColor(NodeHandle node, int color);

void SetWidth(NodeHandle node, float value, int unit);

void SetHeight(NodeHandle node, float value, int unit);

void SetOpacity(NodeHandle node, float opacity);

void SetBorderWidth(NodeHandle node, float* widthValues, int* widthUnits, int length);

void SetBorderColor(NodeHandle node, int* colors, int length);

void SetBorderStyle(NodeHandle node, int* styles, int length);

void SetBorderRadius(NodeHandle node, float* radiusValues, int* radiusUnits, int length);

void SetZIndex(NodeHandle node, int zIndex);

void SetBackShadow(NodeHandle node, float* shadowInfo, int length);

void SetHitTestBehavior(NodeHandle node, int hitTestBehavior);

void SetTransform(NodeHandle node, float* matrix, int length);

void SetPosition(NodeHandle node, float x, int xunit, float y, int yunit);

void SetBorder(NodeHandle node, ArkUIBorderOptions* options);
}
#endif // FRAMEWORKS_BRIDGE_ARKTS_FRONTEND_ARKOALA_COMMON_MODIFIER_H
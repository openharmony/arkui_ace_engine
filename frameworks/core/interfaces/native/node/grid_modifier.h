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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_GRID_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_GRID_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIGridModifier* GetGridModifier();
const CJUIGridModifier* GetCJUIGridModifier();
void SetOnGridScrollIndex(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollIndex(ArkUINodeHandle node);
void SetOnGridScrollIndexCallBack(ArkUINodeHandle node, void* extraParam);
void SetOnGridScrollBarUpdateCallBack(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollBarUpdate(ArkUINodeHandle node);
void SetOnGridItemDragStart(ArkUINodeHandle node, void* extraParam);
void ResetOnGridItemDragStart(ArkUINodeHandle node);
void SetOnGridItemDragEnter(ArkUINodeHandle node, void* extraParam);
void ResetOnGridItemDragEnter(ArkUINodeHandle node);
void SetOnGridItemDragMove(ArkUINodeHandle node, void* extraParam);
void ResetOnGridItemDragMove(ArkUINodeHandle node);
void SetOnGridItemDragLeave(ArkUINodeHandle node, void* extraParam);
void ResetOnGridItemDragLeave(ArkUINodeHandle node);
void SetOnGridItemDrop(ArkUINodeHandle node, void* extraParam);
void ResetOnGridItemDrop(ArkUINodeHandle node);
void CreateWithResourceObjGridFriction(ArkUINodeHandle node, void* resObj);
void CreateWithResourceObjGridScrollBarColor(ArkUINodeHandle node, void* resObj);
void SetOnGridScrollStart(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollStart(ArkUINodeHandle node);
void SetOnGridScrollStop(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollStop(ArkUINodeHandle node);
void SetOnGridScrollFrameBegin(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollFrameBegin(ArkUINodeHandle node);
void SetOnGridWillScroll(ArkUINodeHandle node, void* extraParam);
void ResetOnGridWillScroll(ArkUINodeHandle node);
void SetOnGridDidScroll(ArkUINodeHandle node, void* extraParam);
void ResetOnGridDidScroll(ArkUINodeHandle node);
void SetOnGridScrollBarUpdate(ArkUINodeHandle node, void* extraParam);
void ResetOnGridScrollBarUpdate(ArkUINodeHandle node);
}

#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_GRID_MODIFIER_H

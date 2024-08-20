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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_DRAG_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_DRAG_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
void SetOnDragStart(ArkUINodeHandle node, void* extraParam);
void SetOnDragDrop(ArkUINodeHandle node, void* extraParam);
void SetOnDragEnter(ArkUINodeHandle node, void* extraParam);
void SetOnDragMove(ArkUINodeHandle node, void* extraParam);
void SetOnDragLeave(ArkUINodeHandle node, void* extraParam);
void SetOnDragEnd(ArkUINodeHandle node, void* extraParam);
void SetOnPreDrag(ArkUINodeHandle node, void* extraParam);
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_NODE_DRAG_MODIFIER_H
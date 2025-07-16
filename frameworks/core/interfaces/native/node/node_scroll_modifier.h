/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

#ifndef FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SCROLL_MODIFIER_H
#define FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SCROLL_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIScrollModifier* GetScrollModifier();
const CJUIScrollModifier* GetCJUIScrollModifier();

void SetOnScroll(ArkUINodeHandle node, void* extraParam);
void SetOnScrollFrameBegin(ArkUINodeHandle node, void* extraParam);
void SetScrollOnWillScroll(ArkUINodeHandle node, void* extraParam);
void SetScrollOnDidScroll(ArkUINodeHandle node, void* extraParam);
void SetOnScrollStart(ArkUINodeHandle node, void* extraParam);
void SetOnScrollStop(ArkUINodeHandle node, void* extraParam);
void SetOnScrollEdge(ArkUINodeHandle node, void* extraParam);
void SetOnScrollReachStart(ArkUINodeHandle node, void* extraParam);
void SetOnScrollReachEnd(ArkUINodeHandle node, void* extraParam);
void SetOnDidZoom(ArkUINodeHandle node, void* extraParam);
void SetOnZoomStart(ArkUINodeHandle node, void* extraParam);
void SetOnZoomStop(ArkUINodeHandle node, void* extraParam);

void ResetOnScroll(ArkUINodeHandle node);
void ResetOnScrollFrameBegin(ArkUINodeHandle node);
void ResetScrollOnWillScroll(ArkUINodeHandle node);
void ResetScrollOnDidScroll(ArkUINodeHandle node);
void ResetOnScrollStart(ArkUINodeHandle node);
void ResetOnScrollStop(ArkUINodeHandle node);
void ResetOnScrollEdge(ArkUINodeHandle node);
void ResetOnScrollReachStart(ArkUINodeHandle node);
void ResetOnScrollReachEnd(ArkUINodeHandle node);
void ResetOnDidZoom(ArkUINodeHandle node);
void ResetOnZoomStart(ArkUINodeHandle node);
void ResetOnZoomStop(ArkUINodeHandle node);

void SetScrollOnScrollStart(ArkUINodeHandle node, void* callback);
void ResetScrollOnScrollStart(ArkUINodeHandle node);
void SetScrollOnScrollEnd(ArkUINodeHandle node, void* callback);
void ResetScrollOnScrollEnd(ArkUINodeHandle node);
void SetScrollOnScrollStop(ArkUINodeHandle node, void* callback);
void ResetScrollOnScrollStop(ArkUINodeHandle node);
void SetScrollOnScroll(ArkUINodeHandle node, void* callback);
void ResetScrollOnScroll(ArkUINodeHandle node);
void SetScrollOnScrollEdge(ArkUINodeHandle node, void* callback);
void ResetScrollOnScrollEdge(ArkUINodeHandle node);
void SetScrollOnDidScrollCallBack(ArkUINodeHandle node, void* callback);
void SetOnScrollFrameBeginCallBack(ArkUINodeHandle node, void* extraParam);
void ResetOnScrollFrameBeginCallBack(ArkUINodeHandle node);
void SetScrollOnWillScrollCallBack(ArkUINodeHandle node, void* extraParam);
void ResetScrollOnWillScrollCallBack(ArkUINodeHandle node);
void SetOnWillStopDragging(ArkUINodeHandle node, void* extraParam);
void ResetOnWillStopDragging(ArkUINodeHandle node);
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FRAMEWORKS_CORE_INTERFACES_NATIVE_NODE_NODE_SCROLL_MODIFIER_H

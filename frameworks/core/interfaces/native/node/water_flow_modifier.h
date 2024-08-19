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

#ifndef FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_WATER_FLOW_MODIFIER_H
#define FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_WATER_FLOW_MODIFIER_H

#include "core/interfaces/native/node/node_api.h"

namespace OHOS::Ace::NG::NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowModifier();
const CJUIWaterFlowModifier* GetCJUIWaterFlowModifier();

void SetOnWillScroll(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowReachEnd(ArkUINodeHandle node, void* extraParam);
void SetOnDidScroll(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowScrollStart(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowScrollStop(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowScrollIndex(ArkUINodeHandle node, void* extraParam);
void SetOnWaterFlowReachStart(ArkUINodeHandle node, void* extraParam);

void ResetOnWillScroll(ArkUINodeHandle node);
void ResetOnWaterFlowReachEnd(ArkUINodeHandle node);
void ResetOnDidScroll(ArkUINodeHandle node);
void ResetOnWaterFlowScrollStart(ArkUINodeHandle node);
void ResetOnWaterFlowScrollStop(ArkUINodeHandle node);
void ResetOnWaterFlowScrollFrameBegin(ArkUINodeHandle node);
void ResetOnWaterFlowScrollIndex(ArkUINodeHandle node);
void ResetOnWaterFlowReachStart(ArkUINodeHandle node);
} // namespace OHOS::Ace::NG::NodeModifier
#endif // FRAMEWORKS_INTERFACE_INNER_API_NATIVE_NODE_WATER_FLOW_MODIFIER_H

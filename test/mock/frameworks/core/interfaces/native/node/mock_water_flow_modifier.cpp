/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/node/water_flow_modifier.h"
#include "core/components_ng/pattern/waterflow/water_flow_model_ng.h"
namespace OHOS::Ace::NG {
ArkUINodeHandle CreateWaterFlow(ArkUI_Int32 nodeId)
{
    auto frameNode = WaterFlowModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}
namespace NodeModifier {
const ArkUIWaterFlowModifier* GetWaterFlowModifier()
{
    static const ArkUIWaterFlowModifier modifier = {
        .createWaterFlow = CreateWaterFlow,
    };
    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
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

#include "interfaces/native/node/node_model.h"
#include "ui/base/utils/utils.h"

#include "core/common/container.h"
#include "core/components_ng/pattern/waterflow/bridge/flowitem/water_flow_item_model_impl.h"
#include "core/components_ng/pattern/waterflow/water_flow_item_model_ng.h"

namespace OHOS::Ace {
#ifndef CROSS_PLATFORM
Framework::WaterFlowItemModelImpl* GetWaterFlowItemModelImpl()
{
    static Framework::WaterFlowItemModelImpl instance;
    return &instance;
}
#endif
namespace NG {
namespace {
ArkUINodeHandle CreateFlowItem(ArkUI_Int32 nodeId)
{
    auto frameNode = WaterFlowItemModelNG::CreateFrameNode(nodeId);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}

void Create()
{
    WaterFlowItemModelNG::CreateFrameNode();
}

#ifndef CROSS_PLATFORM
void CreateImpl()
{
    GetWaterFlowItemModelImpl()->Create();
}
#endif
} // namespace
namespace NodeModifier {
const ArkUIWaterFlowItemModifier* GetFlowItemDynamicModifier()
{
    static bool isCurrentUseNewPipeline = Container::IsCurrentUseNewPipeline();
    if (!isCurrentUseNewPipeline) {
#ifndef CROSS_PLATFORM
        CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
        static const ArkUIWaterFlowItemModifier modifierImpl = {
            .create = CreateImpl,
            .createFlowItem = nullptr,
        };
        CHECK_INITIALIZED_FIELDS_END(modifierImpl, 0, 0, 0); // don't move this line
        return &modifierImpl;
#endif
    }
    CHECK_INITIALIZED_FIELDS_BEGIN(); // don't move this line
    static const ArkUIWaterFlowItemModifier modifier = {
        .create = Create,
        .createFlowItem = CreateFlowItem,
    };
    CHECK_INITIALIZED_FIELDS_END(modifier, 0, 0, 0); // don't move this line
    return &modifier;
}
} // namespace NodeModifier
} // namespace NG
} // namespace OHOS::Ace

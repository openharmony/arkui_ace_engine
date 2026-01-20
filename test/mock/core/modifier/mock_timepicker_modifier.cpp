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

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/time_picker/timepicker_model_ng.h"
#include "core/interfaces/arkoala/arkoala_api.h"
namespace OHOS::Ace::NG {
ArkUINodeHandle CreateFrameNode(ArkUI_Int32 nodeId)
{
    auto frameNode = TimePickerModelNG::CreateFrameNode(nodeId);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return reinterpret_cast<ArkUINodeHandle>(AceType::RawPtr(frameNode));
}
namespace NodeModifier {
const ArkUITimepickerModifier* GetTimePickerDynamicModifier()
{
    static const ArkUITimepickerModifier modifier = {
        .createFrameNode = CreateFrameNode,
    };

    return &modifier;
}
} // namespace NodeModifier
} // namespace OHOS::Ace::NG
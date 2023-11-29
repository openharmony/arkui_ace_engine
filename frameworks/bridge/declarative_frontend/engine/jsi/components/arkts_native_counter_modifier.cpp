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
#include "bridge/declarative_frontend/engine/jsi/components/arkts_native_counter_modifier.h"

#include "core/components/common/layout/constants.h"
#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/base/view_abstract.h"
#include "core/components_ng/pattern/counter/counter_model_ng.h"
#include "core/pipeline/base/element_register.h"

namespace OHOS::Ace::NG {
void SetEnableInc(NodeHandle node, bool enableInc)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableInc(frameNode, enableInc);
}
void ResetEnableInc(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableInc(frameNode, true);
}
void SetEnableDec(NodeHandle node, bool enableDec)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableDec(frameNode, enableDec);
}
void ResetEnableDec(NodeHandle node)
{
    auto* frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CounterModelNG::SetEnableDec(frameNode, true);
}
ArkUICounterModifierAPI GetCounterModifier()
{
    static const ArkUICounterModifierAPI modifier = { SetEnableInc, ResetEnableInc, SetEnableDec, ResetEnableDec };

    return modifier;
}
} // namespace OHOS::Ace::NG

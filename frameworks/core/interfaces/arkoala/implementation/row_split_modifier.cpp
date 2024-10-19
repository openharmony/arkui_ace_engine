/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/linear_split/linear_split_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/utility/reverse_converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace RowSplitInterfaceModifier {
void SetRowSplitOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because RowSplit doesn`t have any options
}
} // RowSplitInterfaceModifier
namespace RowSplitAttributeModifier {
void ResizeableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::ROW_SPLIT, Converter::Convert<bool>(value));
}
} // RowSplitAttributeModifier
const GENERATED_ArkUIRowSplitModifier* GetRowSplitModifier()
{
    static const GENERATED_ArkUIRowSplitModifier ArkUIRowSplitModifierImpl {
        RowSplitInterfaceModifier::SetRowSplitOptionsImpl,
        RowSplitAttributeModifier::ResizeableImpl,
    };
    return &ArkUIRowSplitModifierImpl;
}

}

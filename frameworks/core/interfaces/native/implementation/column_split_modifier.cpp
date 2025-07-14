/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "core/interfaces/native/generated/interface/node_api.h"

namespace OHOS::Ace::NG {
namespace {
struct DividerOptions {
    std::optional<Dimension> startMargin;
    std::optional<Dimension> endMargin;
};
}
}
namespace OHOS::Ace::NG::Converter {
}
namespace OHOS::Ace::NG::GeneratedModifier {
namespace ColumnSplitModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    // need check
    // auto frameNode = LinearSplitModelNG::CreateFrameNode(id, NG::SplitType::COLUMN_SPLIT);
    // CHECK_NULL_RETURN(frameNode, nullptr);
    // frameNode->IncRefCount();
    // return AceType::RawPtr(frameNode);
    return nullptr;
}
} // ColumnSplitModifier
namespace ColumnSplitInterfaceModifier {
void SetColumnSplitOptionsImpl(Ark_NativePointer node)
{
    // keep it empty because ColumnSplit doesn`t have any options
}
} // ColumnSplitInterfaceModifier
namespace ColumnSplitAttributeModifier {
void ResizeableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    LinearSplitModelNG::SetResizable(frameNode, NG::SplitType::COLUMN_SPLIT, Converter::Convert<bool>(value));
}
void DividerImpl(Ark_NativePointer node,
                 const Opt_ColumnSplitDividerStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    // auto divider = Converter::OptConvert<ItemDivider>(*value);
    // need check
    // LinearSplitModelNG::SetDivider(frameNode, NG::SplitType::COLUMN_SPLIT, divider);
}
} // ColumnSplitAttributeModifier
const GENERATED_ArkUIColumnSplitModifier* GetColumnSplitModifier()
{
    static const GENERATED_ArkUIColumnSplitModifier ArkUIColumnSplitModifierImpl {
        ColumnSplitModifier::ConstructImpl,
        ColumnSplitInterfaceModifier::SetColumnSplitOptionsImpl,
        ColumnSplitAttributeModifier::ResizeableImpl,
        ColumnSplitAttributeModifier::DividerImpl,
    };
    return &ArkUIColumnSplitModifierImpl;
}

}

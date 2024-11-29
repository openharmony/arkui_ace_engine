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
#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemGroupModifier {
Ark_NativePointer ConstructImpl()
{
    return 0;
}
} // ListItemGroupModifier
namespace ListItemGroupInterfaceModifier {
void SetListItemGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_ListItemGroupOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = options ? Converter::OptConvert<type>(*options) : std::nullopt;
    //ListItemGroupModelNG::SetSetListItemGroupOptions(frameNode, convValue);
}
} // ListItemGroupInterfaceModifier
namespace ListItemGroupAttributeModifier {
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_ListDividerOptions_Null* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListItemGroupModelNG::SetDivider(frameNode, convValue);
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                          const Ark_ChildrenMainSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    //auto convValue = Converter::OptConvert<type_name>(*value);
    //ListItemGroupModelNG::SetChildrenMainSize(frameNode, convValue);
}
} // ListItemGroupAttributeModifier
const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier()
{
    static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
        ListItemGroupModifier::ConstructImpl,
        ListItemGroupInterfaceModifier::SetListItemGroupOptionsImpl,
        ListItemGroupAttributeModifier::DividerImpl,
        ListItemGroupAttributeModifier::ChildrenMainSizeImpl,
    };
    return &ArkUIListItemGroupModifierImpl;
}

}

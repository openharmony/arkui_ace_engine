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
#include "core/interfaces/native/utility/converter.h"
#include "arkoala_api_generated.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // ListItemModifier
namespace ListItemInterfaceModifier {
void SetListItemOptionsImpl(Ark_NativePointer node,
                            const Opt_ListItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetListItemOptions(frameNode, convValue);
}
} // ListItemInterfaceModifier
namespace ListItemAttributeModifier {
void SetSelectableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetSelectable(frameNode, convValue);
}
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetSelected(frameNode, convValue);
}
void SetSwipeActionImpl(Ark_NativePointer node,
                        const Opt_SwipeActionOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetSwipeAction(frameNode, convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemModelNG::SetSetOnSelect(frameNode, convValue);
}
} // ListItemAttributeModifier
const GENERATED_ArkUIListItemModifier* GetListItemModifier()
{
    static const GENERATED_ArkUIListItemModifier ArkUIListItemModifierImpl {
        ListItemModifier::ConstructImpl,
        ListItemInterfaceModifier::SetListItemOptionsImpl,
        ListItemAttributeModifier::SetSelectableImpl,
        ListItemAttributeModifier::SetSelectedImpl,
        ListItemAttributeModifier::SetSwipeActionImpl,
        ListItemAttributeModifier::SetOnSelectImpl,
    };
    return &ArkUIListItemModifierImpl;
}

}

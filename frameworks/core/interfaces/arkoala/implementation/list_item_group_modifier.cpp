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
#include "core/components_ng/pattern/list/list_item_group_model_ng.h"
#include "core/interfaces/arkoala/utility/converter.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"
#include "children_main_size_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
V2::ItemDivider Convert(const Ark_ListDividerOptions& src);

template<>
Converter::ListItemGroupOptions Convert(const Ark_ListItemGroupOptions& src)
{
    return {
        .space = OptConvert<Dimension>(src.space),
        .style = OptConvert<V2::ListItemGroupStyle>(src.style)
    };
}
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemGroupInterfaceModifier {
void SetListItemGroupOptionsImpl(Ark_NativePointer node,
                                 const Opt_ListItemGroupOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(options);
    auto optionsOpt = Converter::OptConvert<Converter::ListItemGroupOptions>(*options);
    if (optionsOpt.has_value()) {
        ListItemGroupModelNG::SetSpace(frameNode, optionsOpt.value().space);
        ListItemGroupModelNG::SetStyle(frameNode, optionsOpt.value().style);
        // process CustomBuilder parameters
        LOGE("ListItemGroupModifier::SetListItemGroupOptionsImpl support CustomObjects not implemented");
    }
}
} // ListItemGroupInterfaceModifier
namespace ListItemGroupAttributeModifier {
void DividerImpl(Ark_NativePointer node,
                 const Ark_Union_ListDividerOptions_Undefined* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto divider = Converter::OptConvert<V2::ItemDivider>(*value);
    ListItemGroupModelNG::SetDivider(frameNode, divider);
}
void ChildrenMainSizeImpl(Ark_NativePointer node,
                          const Ark_Materialized* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto peer = reinterpret_cast<ChildrenMainSizePeer *>(value->ptr);
    CHECK_NULL_VOID(peer);
    RefPtr<ListChildrenMainSize> handler = ListItemGroupModelNG::GetOrCreateListChildrenMainSize(frameNode);
    peer->SetHandler(handler);
}
} // ListItemGroupAttributeModifier
const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier()
{
    static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
        ListItemGroupInterfaceModifier::SetListItemGroupOptionsImpl,
        ListItemGroupAttributeModifier::DividerImpl,
        ListItemGroupAttributeModifier::ChildrenMainSizeImpl,
    };
    return &ArkUIListItemGroupModifierImpl;
}

}

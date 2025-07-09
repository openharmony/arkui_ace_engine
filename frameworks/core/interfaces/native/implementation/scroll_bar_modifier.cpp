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
#include "core/components_ng/pattern/scroll_bar/scroll_bar_model_ng.h"
#include "core/interfaces/native/implementation/scroller_peer_impl.h"

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ScrollBarModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return nullptr;
}
} // ScrollBarModifier
namespace ScrollBarInterfaceModifier {
void SetScrollBarOptionsImpl(Ark_NativePointer node,
                             const Ark_ScrollBarOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    if (value) {
        auto scrollerPeer = value->scroller;
    }
    const auto direction = value ? Converter::OptConvert<Axis>(value->direction) : std::nullopt;
    const auto state = value ? Converter::OptConvert<DisplayMode>(value->state) : std::nullopt;
}
} // ScrollBarInterfaceModifier
namespace ScrollBarAttributeModifier {
void EnableNestedScrollImpl(Ark_NativePointer node,
                            const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    auto convValue = Converter::OptConvert<bool>(*value);
}
} // ScrollBarAttributeModifier
const GENERATED_ArkUIScrollBarModifier* GetScrollBarModifier()
{
    static const GENERATED_ArkUIScrollBarModifier ArkUIScrollBarModifierImpl {
        ScrollBarModifier::ConstructImpl,
        ScrollBarInterfaceModifier::SetScrollBarOptionsImpl,
        ScrollBarAttributeModifier::EnableNestedScrollImpl,
    };
    return &ArkUIScrollBarModifierImpl;
}

}

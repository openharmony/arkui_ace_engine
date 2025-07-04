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
#include "core/interfaces/native/generated/interface/node_api.h"
#include "frameworks/core/components/list/list_theme.h"
#include "children_main_size_peer.h"

namespace OHOS::Ace::NG::Converter {
template<>
V2::ItemDivider Convert(const Ark_ListDividerOptions& src);
}

namespace OHOS::Ace::NG::GeneratedModifier {
namespace ListItemGroupModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = ListItemGroupModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}

RefPtr<ListTheme> GetListTheme()
{
    auto pipeline = PipelineBase::GetCurrentContextSafelyWithCheck();
    CHECK_NULL_RETURN(pipeline, nullptr);
    return pipeline->GetTheme<ListTheme>();
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
void SetDividerImpl(Ark_NativePointer node,
                    const Opt_ListDividerOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto options = value ? Converter::OptConvert<Ark_ListDividerOptions>(*value) : std::nullopt;
    V2::ItemDivider dividerAns;
    if (options.has_value()) {
        auto widthOpt = Converter::OptConvert<Dimension>(options->strokeWidth);
        dividerAns.strokeWidth = widthOpt.value_or(0.0_vp);
        auto startMarginOpt = Converter::OptConvert<Dimension>(options->startMargin);
        dividerAns.startMargin = startMarginOpt.value_or(0.0_vp);
        auto endMarginOpt = Converter::OptConvert<Dimension>(options->endMargin);
        dividerAns.endMargin = endMarginOpt.value_or(0.0_vp);
        auto colorOpt = Converter::OptConvert<Color>(options->color);
        if (colorOpt.has_value()) {
            dividerAns.color = colorOpt.value();
        } else {
            auto listTheme = ListItemGroupModifier::GetListTheme();
            if (listTheme) {
                dividerAns.color = listTheme->GetDividerColor();
            }
        }
    }
    ListItemGroupModelStatic::SetDivider(frameNode, dividerAns);
}
void SetChildrenMainSizeImpl(Ark_NativePointer node,
                             const Opt_ChildrenMainSize* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //ListItemGroupModelNG::SetSetChildrenMainSize(frameNode, convValue);
}
} // ListItemGroupAttributeModifier
const GENERATED_ArkUIListItemGroupModifier* GetListItemGroupModifier()
{
    static const GENERATED_ArkUIListItemGroupModifier ArkUIListItemGroupModifierImpl {
        ListItemGroupModifier::ConstructImpl,
        ListItemGroupInterfaceModifier::SetListItemGroupOptionsImpl,
        ListItemGroupAttributeModifier::SetDividerImpl,
        ListItemGroupAttributeModifier::SetChildrenMainSizeImpl,
    };
    return &ArkUIListItemGroupModifierImpl;
}

}

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

#include "arkoala_api_generated.h"

#include "core/components_ng/base/frame_node.h"
#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemStyle& src)
{
    switch (src) {
        case static_cast<Ark_GridItemStyle>(GridItemStyle::NONE):
            dst = GridItemStyle::NONE;
            break;
        case static_cast<Ark_GridItemStyle>(GridItemStyle::PLAIN):
            dst = GridItemStyle::PLAIN;
            break;
        default:
            LOGE("Unexpected enum value in Ark_GridItemStyle: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemOptions& src)
{
    dst = Converter::OptConvert<GridItemStyle>(src.style);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id, Ark_Int32 flags)
{
    auto frameNode = GridItemModelNG::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // namespace GridItemModifier
namespace GridItemInterfaceModifier {
void SetGridItemOptionsImpl(Ark_NativePointer node, const Opt_GridItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode*>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<GridItemStyle> style;
    if (value->tag != ARK_TAG_UNDEFINED) {
        style = Converter::OptConvert<GridItemStyle>(value->value);
    }

    if (style) {
        GridItemModelNG::SetGridItemStyle(frameNode, style.value());
    }
}
} // namespace GridItemInterfaceModifier
namespace GridItemAttributeModifier {
void RowStartImpl(Ark_NativePointer node,
                  const Opt_Number* value)
{
}
void RowEndImpl(Ark_NativePointer node,
                const Opt_Number* value)
{
}
void ColumnStartImpl(Ark_NativePointer node,
                     const Opt_Number* value)
{
}
void ColumnEndImpl(Ark_NativePointer node,
                   const Opt_Number* value)
{
}
void ForceRebuildImpl(Ark_NativePointer node,
                      const Opt_Boolean* value)
{
}
void SelectableImpl(Ark_NativePointer node,
                    const Opt_Boolean* value)
{
}
void SelectedImpl(Ark_NativePointer node,
                  const Opt_Boolean* value)
{
}
void OnSelectImpl(Ark_NativePointer node,
                  const Opt_Callback_Boolean_Void* value)
{
}
void _onChangeEvent_selectedImpl(Ark_NativePointer node,
                                 const Callback_Opt_Boolean_Void* callback)
{
}
} // GridItemAttributeModifier
const GENERATED_ArkUIGridItemModifier* GetGridItemModifier()
{
    static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
        GridItemModifier::ConstructImpl,
        GridItemInterfaceModifier::SetGridItemOptionsImpl,
        GridItemAttributeModifier::RowStartImpl,
        GridItemAttributeModifier::RowEndImpl,
        GridItemAttributeModifier::ColumnStartImpl,
        GridItemAttributeModifier::ColumnEndImpl,
        GridItemAttributeModifier::ForceRebuildImpl,
        GridItemAttributeModifier::SelectableImpl,
        GridItemAttributeModifier::SelectedImpl,
        GridItemAttributeModifier::OnSelectImpl,
        GridItemAttributeModifier::_onChangeEvent_selectedImpl,
    };
    return &ArkUIGridItemModifierImpl;
}

}

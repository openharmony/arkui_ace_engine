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

#include "core/interfaces/arkoala/utility/converter.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/interfaces/arkoala/generated/interface/node_api.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemStyle& src)
{
    switch (src) {
        case static_cast<Ark_GridItemStyle>(GridItemStyle::NONE): dst = GridItemStyle::NONE; break;
        case static_cast<Ark_GridItemStyle>(GridItemStyle::PLAIN): dst = GridItemStyle::PLAIN; break;
        default: LOGE("Unexpected enum value in Ark_GridItemStyle: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemOptions& src)
{
    dst = Converter::OptConvert<GridItemStyle>(src.style);
}
} // namespace OHOS::Ace::NG::Converter

namespace OHOS::Ace::NG::GeneratedModifier {
namespace GridItemInterfaceModifier {
void SetGridItemOptionsImpl(Ark_NativePointer node,
                            const Opt_GridItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    std::optional<GridItemStyle> style = Converter::OptConvert<GridItemStyle>(*value);
    if (style) {
        GridItemModelNG::SetGridItemStyle(frameNode, style.value());
    }
}
} // GridItemInterfaceModifier
namespace GridItemAttributeModifier {
void RowStartImpl(Ark_NativePointer node,
                  const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridItemModelNG::SetRowStart(frameNode, Converter::Convert<int32_t>(*value));
}
void RowEndImpl(Ark_NativePointer node,
                const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridItemModelNG::SetRowEnd(frameNode, Converter::Convert<int32_t>(*value));
}
void ColumnStartImpl(Ark_NativePointer node,
                     const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridItemModelNG::SetColumnStart(frameNode, Converter::Convert<int32_t>(*value));
}
void ColumnEndImpl(Ark_NativePointer node,
                   const Ark_Number* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    GridItemModelNG::SetColumnEnd(frameNode, Converter::Convert<int32_t>(*value));
}
void ForceRebuildImpl(Ark_NativePointer node,
                      Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetForceRebuild(frameNode, Converter::Convert<bool>(value));
}
void SelectableImpl(Ark_NativePointer node,
                    Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelectable(frameNode, Converter::Convert<bool>(value));
}
void SelectedImpl(Ark_NativePointer node,
                  Ark_Boolean value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    GridItemModelNG::SetSelected(frameNode, Converter::Convert<bool>(value));
}
void OnSelectImpl(Ark_NativePointer node,
                  Ark_Function event)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto onSelect = [frameNode](bool isSelected) {
        GetFullAPI()->getEventsAPI()->getGridItemEventsReceiver()->onSelect(frameNode->GetId(), isSelected);
    };
    GridItemModelNG::SetOnSelect(frameNode, onSelect);
}
} // GridItemAttributeModifier
const GENERATED_ArkUIGridItemModifier* GetGridItemModifier()
{
    static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
        GridItemInterfaceModifier::SetGridItemOptionsImpl,
        GridItemAttributeModifier::RowStartImpl,
        GridItemAttributeModifier::RowEndImpl,
        GridItemAttributeModifier::ColumnStartImpl,
        GridItemAttributeModifier::ColumnEndImpl,
        GridItemAttributeModifier::ForceRebuildImpl,
        GridItemAttributeModifier::SelectableImpl,
        GridItemAttributeModifier::SelectedImpl,
        GridItemAttributeModifier::OnSelectImpl,
    };
    return &ArkUIGridItemModifierImpl;
}

}
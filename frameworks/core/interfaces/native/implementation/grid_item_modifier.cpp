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

#include "core/interfaces/native/utility/callback_helper.h"
#include "core/interfaces/native/utility/converter.h"
#include "core/interfaces/native/utility/reverse_converter.h"
#include "arkoala_api_generated.h"

#include "core/components_ng/pattern/grid/grid_item_model_ng.h"
#include "core/components_ng/pattern/grid/grid_item_model_static.h"

namespace OHOS::Ace::NG::Converter {
template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemStyle& src)
{
    switch (src) {
        case ARK_GRID_ITEM_STYLE_NONE: dst = GridItemStyle::NONE; break;
        case ARK_GRID_ITEM_STYLE_PLAIN: dst = GridItemStyle::PLAIN; break;
        default: LOGE("Unexpected enum value in Ark_GridItemStyle: %{public}d", src);
    }
}

template<>
inline void AssignCast(std::optional<GridItemStyle>& dst, const Ark_GridItemOptions& src)
{
    dst = Converter::OptConvert<GridItemStyle>(src.style);
}
} // namespace OHOS::Ace::NG::Converter
namespace OHOS::Ace::NG {
namespace {
std::optional<bool> ProcessBindableSelected(FrameNode* frameNode, const Opt_Union_Boolean_Bindable *value)
{
    std::optional<bool> result;
    Converter::VisitUnionPtr(value,
        [&result](const Ark_Boolean& src) {
            result = Converter::OptConvert<bool>(src);
        },
        [&result, frameNode](const Ark_Bindable_Boolean& src) {
            result = Converter::OptConvert<bool>(src.value);
            WeakPtr<FrameNode> weakNode = AceType::WeakClaim(frameNode);
            auto onEvent = [arkCallback = CallbackHelper(src.onChange), weakNode](bool isSelected) {
                PipelineContext::SetCallBackNode(weakNode);
                arkCallback.Invoke(Converter::ArkValue<Ark_Boolean>(isSelected));
            };
            GridItemModelStatic::SetSelectChangeEvent(frameNode, std::move(onEvent));
        },
        [] {});
    return result;
}
} // namespace
} // namespace OHOS::Ace::NG

namespace OHOS::Ace::NG::GeneratedModifier {
const int32_t DEFAULT_GRID_ITEM_UNDEFINED = -1;
namespace GridItemModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    auto frameNode = GridItemModelStatic::CreateFrameNode(id);
    CHECK_NULL_RETURN(frameNode, nullptr);
    frameNode->IncRefCount();
    return AceType::RawPtr(frameNode);
}
} // GridItemModifier
namespace GridItemInterfaceModifier {
void SetGridItemOptionsImpl(Ark_NativePointer node,
                            const Opt_GridItemOptions* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    std::optional<GridItemStyle> style = Converter::OptConvertPtr<GridItemStyle>(value);
    if (style) {
        GridItemModelStatic::SetGridItemStyle(frameNode, style.value());
    }
}
} // GridItemInterfaceModifier
namespace GridItemAttributeModifier {
void SetRowStartImpl(Ark_NativePointer node,
                     const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridItemModelStatic::SetRowStart(frameNode, DEFAULT_GRID_ITEM_UNDEFINED);
        return;
    }
    GridItemModelStatic::SetRowStart(frameNode, *convValue);
}
void SetRowEndImpl(Ark_NativePointer node,
                   const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridItemModelStatic::SetRowEnd(frameNode, DEFAULT_GRID_ITEM_UNDEFINED);
        return;
    }
    GridItemModelStatic::SetRowEnd(frameNode, *convValue);
}
void SetColumnStartImpl(Ark_NativePointer node,
                        const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridItemModelStatic::SetColumnStart(frameNode, DEFAULT_GRID_ITEM_UNDEFINED);
        return;
    }
    GridItemModelStatic::SetColumnStart(frameNode, *convValue);
}
void SetColumnEndImpl(Ark_NativePointer node,
                      const Opt_Int32* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<int32_t>(value);
    if (!convValue) {
        GridItemModelStatic::SetColumnEnd(frameNode, DEFAULT_GRID_ITEM_UNDEFINED);
        return;
    }
    GridItemModelStatic::SetColumnEnd(frameNode, *convValue);
}
void SetSelectableImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = Converter::OptConvertPtr<bool>(value);
    if (!convValue) {
        GridItemModelStatic::SetSelectable(frameNode, true);
        return;
    }
    GridItemModelStatic::SetSelectable(frameNode, *convValue);
}
void SetSelectedImpl(Ark_NativePointer node,
                     const Opt_Union_Boolean_Bindable* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto convValue = ProcessBindableSelected(frameNode, value);
    if (!convValue) {
        // Implement Reset value
        GridItemModelStatic::SetSelected(frameNode, false);
        return;
    }
    GridItemModelStatic::SetSelected(frameNode, *convValue);
}
void SetOnSelectImpl(Ark_NativePointer node,
                     const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    auto optValue = Converter::GetOptPtr(value);
    if (!optValue) {
        GridItemModelStatic::SetOnSelect(frameNode, nullptr);
        return;
    }
    auto onSelect = [arkCallback = CallbackHelper(*optValue)](bool isSelected) {
        arkCallback.Invoke(isSelected);
    };
    GridItemModelStatic::SetOnSelect(frameNode, onSelect);
}
} // GridItemAttributeModifier
const GENERATED_ArkUIGridItemModifier* GetGridItemModifier()
{
    static const GENERATED_ArkUIGridItemModifier ArkUIGridItemModifierImpl {
        GridItemModifier::ConstructImpl,
        GridItemInterfaceModifier::SetGridItemOptionsImpl,
        GridItemAttributeModifier::SetRowStartImpl,
        GridItemAttributeModifier::SetRowEndImpl,
        GridItemAttributeModifier::SetColumnStartImpl,
        GridItemAttributeModifier::SetColumnEndImpl,
        GridItemAttributeModifier::SetSelectableImpl,
        GridItemAttributeModifier::SetSelectedImpl,
        GridItemAttributeModifier::SetOnSelectImpl,
    };
    return &ArkUIGridItemModifierImpl;
}

}

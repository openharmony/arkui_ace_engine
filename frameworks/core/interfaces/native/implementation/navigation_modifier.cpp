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
namespace {
constexpr uint32_t SAFE_AREA_TYPE_LIMIT = 3;
constexpr uint32_t SAFE_AREA_EDGE_LIMIT = 4;
constexpr uint32_t SAFE_AREA_EDGE_SYSTEM = 0;
constexpr uint32_t SAFE_AREA_EDGE_TOP = 0;
constexpr uint32_t SAFE_AREA_EDGE_BOTTOM = 1;
constexpr uint32_t INVALID_VALUE = 0;
constexpr uint32_t DEFAULT_NAV_BAR_WIDTH = 240;
} // namespace

namespace NavigationModifier {
Ark_NativePointer ConstructImpl(Ark_Int32 id,
                                Ark_Int32 flags)
{
    return {};
}
} // NavigationModifier
namespace NavigationInterfaceModifier {
void SetNavigationOptions0Impl(Ark_NativePointer node)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(undefined);
    //auto convValue = Converter::OptConvert<type>(undefined); // for enums
    //NavigationModelNG::SetSetNavigationOptions0(frameNode, convValue);
}
void SetNavigationOptions1Impl(Ark_NativePointer node,
                               Ark_NavPathStack pathInfos)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(pathInfos);
    //auto convValue = Converter::OptConvert<type>(pathInfos); // for enums
    //NavigationModelNG::SetSetNavigationOptions1(frameNode, convValue);
}
} // NavigationInterfaceModifier
namespace NavigationAttributeModifier {
void SetNavBarWidthImpl(Ark_NativePointer node,
                        const Opt_Length* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    CHECK_NULL_VOID(value);
    Dimension def(DEFAULT_NAV_BAR_WIDTH, DimensionUnit::VP);
    if (value->tag == InteropTag::INTEROP_TAG_UNDEFINED) {
        return;
    }
    auto result = Converter::Convert<Dimension>(value->value);
    auto resultVal = result.Value();
    if (resultVal <= INVALID_VALUE) {
        NavigationModelStatic::SetNavBarWidth(frameNode, def);
        return;
    }
    NavigationModelStatic::SetNavBarWidth(frameNode, result);
}
void SetNavBarPositionImpl(Ark_NativePointer node,
                           const Opt_NavBarPosition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetNavBarPosition(frameNode, convValue);
}
void SetNavBarWidthRangeImpl(Ark_NativePointer node,
                             const Opt_Tuple_Dimension_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetNavBarWidthRange(frameNode, convValue);
}
void SetMinContentWidthImpl(Ark_NativePointer node,
                            const Opt_Dimension* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetMinContentWidth(frameNode, convValue);
}
void SetModeImpl(Ark_NativePointer node,
                 const Opt_NavigationMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetMode(frameNode, convValue);
}
void SetBackButtonIcon0Impl(Ark_NativePointer node,
                            const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetBackButtonIcon0(frameNode, convValue);
}
void SetHideNavBarImpl(Ark_NativePointer node,
                       const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetHideNavBar(frameNode, convValue);
}
void SetHideTitleBar0Impl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetHideTitleBar0(frameNode, convValue);
}
void SetHideBackButtonImpl(Ark_NativePointer node,
                           const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetHideBackButton(frameNode, convValue);
}
void SetTitleModeImpl(Ark_NativePointer node,
                      const Opt_NavigationTitleMode* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetTitleMode(frameNode, convValue);
}
void SetMenus0Impl(Ark_NativePointer node,
                   const Opt_Union_Array_NavigationMenuItem_CustomBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetMenus0(frameNode, convValue);
}
void SetHideToolBar0Impl(Ark_NativePointer node,
                         const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetHideToolBar0(frameNode, convValue);
}
void SetEnableToolBarAdaptationImpl(Ark_NativePointer node,
                                    const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetEnableToolBarAdaptation(frameNode, convValue);
}
void SetOnTitleModeChangeImpl(Ark_NativePointer node,
                              const Opt_Callback_NavigationTitleMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetOnTitleModeChange(frameNode, convValue);
}
void SetOnNavBarStateChangeImpl(Ark_NativePointer node,
                                const Opt_Callback_Boolean_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetOnNavBarStateChange(frameNode, convValue);
}
void SetOnNavigationModeChangeImpl(Ark_NativePointer node,
                                   const Opt_Callback_NavigationMode_Void* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetOnNavigationModeChange(frameNode, convValue);
}
void SetNavDestinationImpl(Ark_NativePointer node,
                           const Opt_PageMapBuilder* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetNavDestination(frameNode, convValue);
}
void SetCustomNavContentTransitionImpl(Ark_NativePointer node,
                                       const Opt_Type_NavigationAttribute_customNavContentTransition* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetCustomNavContentTransition(frameNode, convValue);
}
void SetSystemBarStyleImpl(Ark_NativePointer node,
                           const Opt_window_SystemBarStyle* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetSystemBarStyle(frameNode, convValue);
}
void SetRecoverableImpl(Ark_NativePointer node,
                        const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetRecoverable(frameNode, convValue);
}
void SetEnableDragBarImpl(Ark_NativePointer node,
                          const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetEnableDragBar(frameNode, convValue);
}
void SetEnableModeChangeAnimationImpl(Ark_NativePointer node,
                                      const Opt_Boolean* value)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = value ? Converter::OptConvert<type>(*value) : std::nullopt;
    //NavigationModelNG::SetSetEnableModeChangeAnimation(frameNode, convValue);
}
void SetBackButtonIcon1Impl(Ark_NativePointer node,
                            const Opt_Union_String_PixelMap_Resource_SymbolGlyphModifier* icon,
                            const Opt_ResourceStr* accessibilityText)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(icon);
    //auto convValue = Converter::OptConvert<type>(icon); // for enums
    //NavigationModelNG::SetSetBackButtonIcon1(frameNode, convValue);
}
void SetTitleImpl(Ark_NativePointer node,
                  const Opt_Union_ResourceStr_CustomBuilder_NavigationCommonTitle_NavigationCustomTitle* value,
                  const Opt_NavigationTitleOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavigationModelNG::SetSetTitle(frameNode, convValue);
}
void SetHideTitleBar1Impl(Ark_NativePointer node,
                          const Opt_Boolean* hide,
                          const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavigationModelNG::SetSetHideTitleBar1(frameNode, convValue);
}
void SetMenus1Impl(Ark_NativePointer node,
                   const Opt_Union_Array_NavigationMenuItem_CustomBuilder* items,
                   const Opt_NavigationMenuOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(items);
    //auto convValue = Converter::OptConvert<type>(items); // for enums
    //NavigationModelNG::SetSetMenus1(frameNode, convValue);
}
void SetToolbarConfigurationImpl(Ark_NativePointer node,
                                 const Opt_Union_Array_ToolbarItem_CustomBuilder* value,
                                 const Opt_NavigationToolbarOptions* options)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(value);
    //auto convValue = Converter::OptConvert<type>(value); // for enums
    //NavigationModelNG::SetSetToolbarConfiguration(frameNode, convValue);
}
void SetHideToolBar1Impl(Ark_NativePointer node,
                         const Opt_Boolean* hide,
                         const Opt_Boolean* animated)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(hide);
    //auto convValue = Converter::OptConvert<type>(hide); // for enums
    //NavigationModelNG::SetSetHideToolBar1(frameNode, convValue);
}
void SetIgnoreLayoutSafeAreaImpl(Ark_NativePointer node,
                                 const Opt_Array_LayoutSafeAreaType* types,
                                 const Opt_Array_LayoutSafeAreaEdge* edges)
{
    auto frameNode = reinterpret_cast<FrameNode *>(node);
    CHECK_NULL_VOID(frameNode);
    //auto convValue = Converter::Convert<type>(types);
    //auto convValue = Converter::OptConvert<type>(types); // for enums
    //NavigationModelNG::SetSetIgnoreLayoutSafeArea(frameNode, convValue);
}
} // NavigationAttributeModifier
const GENERATED_ArkUINavigationModifier* GetNavigationModifier()
{
    static const GENERATED_ArkUINavigationModifier ArkUINavigationModifierImpl {
        NavigationModifier::ConstructImpl,
        NavigationInterfaceModifier::SetNavigationOptions0Impl,
        NavigationInterfaceModifier::SetNavigationOptions1Impl,
        NavigationAttributeModifier::SetNavBarWidthImpl,
        NavigationAttributeModifier::SetNavBarPositionImpl,
        NavigationAttributeModifier::SetNavBarWidthRangeImpl,
        NavigationAttributeModifier::SetMinContentWidthImpl,
        NavigationAttributeModifier::SetModeImpl,
        NavigationAttributeModifier::SetBackButtonIcon0Impl,
        NavigationAttributeModifier::SetHideNavBarImpl,
        NavigationAttributeModifier::SetHideTitleBar0Impl,
        NavigationAttributeModifier::SetHideBackButtonImpl,
        NavigationAttributeModifier::SetTitleModeImpl,
        NavigationAttributeModifier::SetMenus0Impl,
        NavigationAttributeModifier::SetHideToolBar0Impl,
        NavigationAttributeModifier::SetEnableToolBarAdaptationImpl,
        NavigationAttributeModifier::SetOnTitleModeChangeImpl,
        NavigationAttributeModifier::SetOnNavBarStateChangeImpl,
        NavigationAttributeModifier::SetOnNavigationModeChangeImpl,
        NavigationAttributeModifier::SetNavDestinationImpl,
        NavigationAttributeModifier::SetCustomNavContentTransitionImpl,
        NavigationAttributeModifier::SetSystemBarStyleImpl,
        NavigationAttributeModifier::SetRecoverableImpl,
        NavigationAttributeModifier::SetEnableDragBarImpl,
        NavigationAttributeModifier::SetEnableModeChangeAnimationImpl,
        NavigationAttributeModifier::SetBackButtonIcon1Impl,
        NavigationAttributeModifier::SetTitleImpl,
        NavigationAttributeModifier::SetHideTitleBar1Impl,
        NavigationAttributeModifier::SetMenus1Impl,
        NavigationAttributeModifier::SetToolbarConfigurationImpl,
        NavigationAttributeModifier::SetHideToolBar1Impl,
        NavigationAttributeModifier::SetIgnoreLayoutSafeAreaImpl,
    };
    return &ArkUINavigationModifierImpl;
}

}

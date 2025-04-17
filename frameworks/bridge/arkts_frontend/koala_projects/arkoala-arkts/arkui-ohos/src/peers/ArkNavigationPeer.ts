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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { int32 } from "@koalaui/common"
import { KPointer, runtimeType, RuntimeType } from "@koalaui/interop"
import { ComponentBase } from "../ComponentBase"
import { ArkUIGeneratedNativeModule, TypeChecker } from "#components"
import { ArkCommonMethodPeer, ArkCommonMethodAttributes } from "./../generated/peers/ArkCommonPeer"
import { SystemBarStyle, NavigationCommonTitle, NavigationCustomTitle, NavigationMenuItem, NavigationOperation, NavigationMode, InterceptionModeCallback, NavigationInterception, NavigationInterface, ToolbarItemStatus, ToolbarItem, BarStyle, NavigationTitleOptions, NavigationToolbarOptions, NavigationTitleMode, NavContentInfo, NavigationAnimatedTransition, NavBarPosition } from "./../component/navigation"
import { Resource } from "global/resource";
import { CustomBuilder, SymbolGlyphModifier, LayoutSafeAreaType, LayoutSafeAreaEdge } from "./../component/common"
import { Length, ResourceStr, Dimension } from "./../component/units"
import { NavPathStack } from "./../component/navigation"
import { PixelMap } from "./../generated/ArkPixelMapMaterialized"

import { PeerNode } from "../PeerNode"
import { NavExtender } from "../generated/ArkNavExtenderMaterialized"

export class ArkNavigationPeer extends ArkCommonMethodPeer {

    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }

    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavigationPeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = NavExtender.navigationCreate(peerId, flags)
        const _peer = new ArkNavigationPeer(_peerPtr, peerId, "Navigation", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavigationOptions0Attribute(): void {
        // console.log("Call ArkNavigationPeer.setNavigationOptions0Attribute()")
        //NativeModule._NavigationInterface_setNavigationOptions0(this.peer.ptr)
    }
    setNavigationOptions1Attribute(pathInfos: NavPathStack): void {
        // console.log("Call ArkNavigationPeer.setNavigationOptions1Attribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // thisSerializer.writeNavPathStack(pathInfos)
        // NativeModule._NavigationInterface_setNavigationOptions1(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
        NavExtender.setNavigationOptions(this.peer.ptr, pathInfos!)
    }
    navBarWidthAttribute(value: Length): void {
        console.log("Call ArkNavigationPeer.navBarWidthAttribute()")
        // NativeModule._NavigationAttribute_navBarWidth(this.peer.ptr, value)
    }
    navBarPositionAttribute(value: NavBarPosition): void {
        console.log("Call ArkNavigationPeer.navBarPositionAttribute()")
        // NativeModule._NavigationAttribute_navBarPosition(this.peer.ptr, (value.value as int32))
    }
    navBarWidthRangeAttribute(value: [ Dimension, Dimension ]): void {
        console.log("Call ArkNavigationPeer.navBarWidthRangeAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // const value_0  = value[0]
        // thisSerializer.writeLength(value_0)
        // const value_1  = value[1]
        // thisSerializer.writeLength(value_1)
        // NativeModule._NavigationAttribute_navBarWidthRange(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension): void {
        console.log("Call ArkNavigationPeer.minContentWidthAttribute()")
    }
    modeAttribute(value: NavigationMode): void {
        console.log("Call ArkNavigationPeer.modeAttribute()")
        NavExtender.setNavigationMode(this.peer.ptr, value)
    }
    backButtonIconAttribute(value: string | PixelMap | Resource | SymbolGlyphModifier): void {
        console.log("Call ArkNavigationPeer.backButtonIconAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // if (((RuntimeType.STRING == value_type))) {
        //     thisSerializer.writeInt8(0 as int32)
        //     const value_0  = value as string
        //     thisSerializer.writeString(value_0)
        // }
        // else if (((RuntimeType.OBJECT) == (value_type)) && (TypeChecker.isPixelMap(value, false, false))) {
        //     thisSerializer.writeInt8(1 as int32)
        //     const value_1  = value as PixelMap
        //     thisSerializer.writePixelMap(value_1)
        // }
        // else if (((RuntimeType.OBJECT) == (value_type)) && (isResource(value))) {
        //     thisSerializer.writeInt8(2 as int32)
        //     const value_2  = value as Resource
        //     thisSerializer.writeResource(value_2)
        // }
        // else if (((RuntimeType.OBJECT) == (value_type)) && (isInstanceOf("SymbolGlyphModifier", value))) {
        //     thisSerializer.writeInt8(3 as int32)
        //     const value_3  = value as Object
        //     thisSerializer.writeCustomObject("SymbolGlyphModifier", value_3)
        // }
        // NativeModule._NavigationAttribute_backButtonIcon(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    hideNavBarAttribute(value: boolean): void {
        console.log("Call ArkNavigationPeer.hideNavBarAttribute()")
        NavExtender.hideNavBar(this.peer.ptr, value)
    }
    subTitleAttribute(value: string): void {
        console.log("Call ArkNavigationPeer.subTitleAttribute()")
        NavExtender.subTitle(this.peer.ptr, value)
    }
    hideTitleBar0Attribute(value: boolean): void {
        console.log("Call ArkNavigationPeer.hideTitleBar0Attribute()")
        NavExtender.hideTitleBar(this.peer.ptr, value, false)
    }
    hideTitleBar1Attribute(hide: boolean, animated: boolean): void {
        console.log("Call ArkNavigationPeer.hideTitleBar1Attribute()")
        NavExtender.hideTitleBar(this.peer.ptr, hide, animated)
    }
    hideBackButtonAttribute(value: boolean): void {
        console.log("Call ArkNavigationPeer.hideBackButtonAttribute()")
        NavExtender.hideBackButton(this.peer.ptr, value)
    }
    titleModeAttribute(value: NavigationTitleMode): void {
        console.log("Call ArkNavigationPeer.titleModeAttribute()")
        NavExtender.setTitleMode(this.peer.ptr, value)
    }
    menusAttribute(value: Array<NavigationMenuItem> | CustomBuilder): void {
        console.log("Call ArkNavigationPeer.menusAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // if (((RuntimeType.OBJECT == value_type))) {
        //     thisSerializer.writeInt8(0 as int32)
        //     const value_0  = value as Array<NavigationMenuItem>
        //     thisSerializer.writeInt32(value_0.length as int32)
        //     for (let i = 0; i < value_0.length; i++) {
        //         const value_0_element  = value_0[i]
        //         thisSerializer.writeNavigationMenuItem(value_0_element)
        //     }
        // }
        // else if (((RuntimeType.FUNCTION == value_type))) {
        //     thisSerializer.writeInt8(1 as int32)
        //     const value_1  = value as CustomBuilder
        //     thisSerializer.holdAndWriteCallback(value_1)
        // }
        // NativeModule._NavigationAttribute_menus(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    toolBarAttribute(value: Object | CustomBuilder): void {
        console.log("Call ArkNavigationPeer.toolBarAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // if (((RuntimeType.OBJECT == value_type))) {
        //     thisSerializer.writeInt8(0 as int32)
        //     const value_0  = value as Object
        //     thisSerializer.writeCustomObject("Object", value_0)
        // }
        // else if (((RuntimeType.FUNCTION == value_type))) {
        //     thisSerializer.writeInt8(1 as int32)
        //     const value_1  = value as CustomBuilder
        //     thisSerializer.holdAndWriteCallback(value_1)
        // }
        // NativeModule._NavigationAttribute_toolBar(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    hideToolBar0Attribute(value: boolean): void {
        console.log("Call ArkNavigationPeer.hideToolBar0Attribute()")
        NavExtender.hideToolBar(this.peer.ptr, value, false)
    }
    hideToolBar1Attribute(hide: boolean, animated: boolean): void {
        console.log("Call ArkNavigationPeer.hideToolBar1Attribute()")
        NavExtender.hideToolBar(this.peer.ptr, hide, animated)
    }
    onTitleModeChangeAttribute(value: Function1<NavigationTitleMode,void>): void {
        console.log("Call ArkNavigationPeer.onTitleModeChangeAttribute()")
        NavExtender.setTitleModeChange(this.peer.ptr, value)
    }
    onNavBarStateChangeAttribute(value: Function1<boolean,void>): void {
        console.log("Call ArkNavigationPeer.onNavBarStateChangeAttribute()")
        NavExtender.setNavBarStateChange(this.peer.ptr, value)
    }
    onNavigationModeChangeAttribute(value: Function1<NavigationMode,void>): void {
        console.log("Call ArkNavigationPeer.onNavigationModeChangeAttribute()")
    }
    customNavContentTransitionAttribute(value: Function3<NavContentInfo,NavContentInfo,NavigationOperation,NavigationAnimatedTransition | undefined>): void {
        console.log("Call ArkNavigationPeer.customNavContentTransitionAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // thisSerializer.holdAndWriteCallback(value)
        // NativeModule._NavigationAttribute_customNavContentTransition(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    systemBarStyleAttribute(value?: SystemBarStyle): void {
        console.log("Call ArkNavigationPeer.systemBarStyleAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // thisSerializer.writeInt8(value_type as int32)
        // if ((RuntimeType.UNDEFINED) != (value_type)) {
        //     const value_value  = value!
        //     thisSerializer.writeCustomObject("SystemBarStyle", value_value)
        // }
        // NativeModule._NavigationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    recoverableAttribute(value?: boolean): void {
        console.log("Call ArkNavigationPeer.recoverableAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // thisSerializer.writeInt8(value_type as int32)
        // if ((RuntimeType.UNDEFINED) != (value_type)) {
        //     const value_value  = value!
        //     thisSerializer.writeBoolean(value_value)
        // }
        // NativeModule._NavigationAttribute_recoverable(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    enableDragBarAttribute(value?: boolean): void {
        console.log("Call ArkNavigationPeer.enableDragBarAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // thisSerializer.writeInt8(value_type as int32)
        // if ((RuntimeType.UNDEFINED) != (value_type)) {
        //     const value_value  = value!
        //     thisSerializer.writeBoolean(value_value)
        // }
        // NativeModule._NavigationAttribute_enableDragBar(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    titleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): void {
        console.log("Call ArkNavigationPeer.titleAttribute()")
        const value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            const title_casted = value as string
            NavExtender.title(this.peer.ptr, title_casted, false)
        } else if (RuntimeType.OBJECT == value_type) {
            if (TypeChecker.isNavigationCommonTitle(value, false, false)) {
                const common_title = value as NavigationCommonTitle
                const title = common_title.main
                if (RuntimeType.STRING == runtimeType(title)) {
                    const title_str = title as string
                    NavExtender.title(this.peer.ptr, title_str, true)
                }
                const subTitle = common_title.sub
                if (RuntimeType.STRING == runtimeType(subTitle)) {
                    const subTitle_str = subTitle as (string)
                    NavExtender.subTitle(this.peer.ptr, subTitle_str)
                }
            }
        }
    }
    toolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): void {
        console.log("Call ArkNavigationPeer.toolbarConfigurationAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let value_type : int32 = RuntimeType.UNDEFINED
        // value_type = runtimeType(value)
        // if (((RuntimeType.OBJECT == value_type))) {
        //     thisSerializer.writeInt8(0 as int32)
        //     const value_0  = value as Array<ToolbarItem>
        //     thisSerializer.writeInt32(value_0.length as int32)
        //     for (let i = 0; i < value_0.length; i++) {
        //         const value_0_element  = value_0[i]
        //         thisSerializer.writeToolbarItem(value_0_element)
        //     }
        // }
        // else if (((RuntimeType.FUNCTION == value_type))) {
        //     thisSerializer.writeInt8(1 as int32)
        //     const value_1  = value as CustomBuilder
        //     thisSerializer.holdAndWriteCallback(value_1)
        // }
        // let options_type : int32 = RuntimeType.UNDEFINED
        // options_type = runtimeType(options)
        // thisSerializer.writeInt8(options_type as int32)
        // if ((RuntimeType.UNDEFINED) != (options_type)) {
        //     const options_value  = options!
        //     thisSerializer.writeNavigationToolbarOptions(options_value)
        // }
        // NativeModule._NavigationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        console.log("Call ArkNavigationPeer.ignoreLayoutSafeAreaAttribute()")
        // const thisSerializer : Serializer = Serializer.hold()
        // let types_type : int32 = RuntimeType.UNDEFINED
        // types_type = runtimeType(types)
        // thisSerializer.writeInt8(types_type as int32)
        // if ((RuntimeType.UNDEFINED) != (types_type)) {
        //     const types_value  = types!
        //     thisSerializer.writeInt32(types_value.length as int32)
        //     for (let i = 0; i < types_value.length; i++) {
        //         const types_value_element  = types_value[i]
        //         thisSerializer.writeInt32(types_value_element.ordinal)
        //     }
        // }
        // let edges_type : int32 = RuntimeType.UNDEFINED
        // edges_type = runtimeType(edges)
        // thisSerializer.writeInt8(edges_type as int32)
        // if ((RuntimeType.UNDEFINED) != (edges_type)) {
        //     const edges_value  = edges!
        //     thisSerializer.writeInt32(edges_value.length as int32)
        //     for (let i = 0; i < edges_value.length; i++) {
        //         const edges_value_element  = edges_value[i]
        //         thisSerializer.writeInt32(edges_value_element.ordinal)
        //     }
        // }
        // NativeModule._NavigationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asArray(), thisSerializer.length())
        // thisSerializer.release()
    }
    applyAttributes<T extends ArkNavigationAttributes>(attributes: T): void {
        super.applyAttributes(attributes)
    }
}
export interface ArkNavigationAttributes extends ArkCommonMethodAttributes {
    navBarWidth?: Length
    navBarPosition?: NavBarPosition
    navBarWidthRange?: [ Dimension, Dimension ]
    minContentWidth?: Dimension
    mode?: NavigationMode
    backButtonIcon?: string | PixelMap | Resource | SymbolGlyphModifier
    hideNavBar?: boolean
    subTitle?: string
    hideTitleBar?: boolean
    hideBackButton?: boolean
    titleMode?: NavigationTitleMode
    menus?: Array<NavigationMenuItem> | CustomBuilder
    toolBar?: Object | CustomBuilder
    hideToolBar?: boolean
    onTitleModeChange?: Function1<NavigationTitleMode,void>
    onNavBarStateChange?: Function1<boolean,void>
    onNavigationModeChange?: Function1<NavigationMode,void>
    navDestination?: Function2<string,object,void>
    customNavContentTransition?: Function3<NavContentInfo,NavContentInfo,NavigationOperation,NavigationAnimatedTransition | undefined>
    systemBarStyle?: SystemBarStyle | undefined
    recoverable?: boolean | undefined
    enableDragBar?: boolean | undefined
}

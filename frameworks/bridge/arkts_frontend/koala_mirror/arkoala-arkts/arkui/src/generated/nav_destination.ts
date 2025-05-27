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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { NavPathInfo, NavPathInfoInternal, NavPathStack, NavPathStackInternal, NavigationMenuItem, NavigationTitleOptions, ToolbarItem, NavigationToolbarOptions, BarStyle, ToolbarItemStatus } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Callback_Void } from "./ability_component"
import { ResourceStr, Length, ResourceColor } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { SymbolGlyphModifier, TextModifier } from "./arkui-external"
import { SystemBarStyle } from "./arkui-custom"
import { Resource } from "./resource"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "./arkui-graphics"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export interface NavDestinationContext {
    pathInfo: NavPathInfo
    pathStack: NavPathStack
    navDestinationId?: string | undefined
    getConfigInRouteMap(): RouteMapConfig | undefined
}
export class NavDestinationContextInternal implements MaterializedBase,NavDestinationContext {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get pathInfo(): NavPathInfo {
        return this.getPathInfo()
    }
    set pathInfo(pathInfo: NavPathInfo) {
        this.setPathInfo(pathInfo)
    }
    get pathStack(): NavPathStack {
        return this.getPathStack()
    }
    set pathStack(pathStack: NavPathStack) {
        this.setPathStack(pathStack)
    }
    get navDestinationId(): string | undefined {
        return this.getNavDestinationId()
    }
    set navDestinationId(navDestinationId: string | undefined) {
        const navDestinationId_NonNull  = (navDestinationId as string)
        this.setNavDestinationId(navDestinationId_NonNull)
    }
    static ctor_navdestinationcontext(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = NavDestinationContextInternal.ctor_navdestinationcontext()
        this.peer = new Finalizable(ctorPtr, NavDestinationContextInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavDestinationContext_getFinalizer()
    }
    public getConfigInRouteMap(): RouteMapConfig | undefined {
        return this.getConfigInRouteMap_serialize()
    }
    private getPathInfo(): NavPathInfo {
        return this.getPathInfo_serialize()
    }
    private setPathInfo(pathInfo: NavPathInfo): void {
        const pathInfo_casted = pathInfo as (NavPathInfo)
        this.setPathInfo_serialize(pathInfo_casted)
        return
    }
    private getPathStack(): NavPathStack {
        return this.getPathStack_serialize()
    }
    private setPathStack(pathStack: NavPathStack): void {
        const pathStack_casted = pathStack as (NavPathStack)
        this.setPathStack_serialize(pathStack_casted)
        return
    }
    private getNavDestinationId(): string | undefined {
        return this.getNavDestinationId_serialize()
    }
    private setNavDestinationId(navDestinationId: string): void {
        const navDestinationId_casted = navDestinationId as (string)
        this.setNavDestinationId_serialize(navDestinationId_casted)
        return
    }
    private getConfigInRouteMap_serialize(): RouteMapConfig | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getConfigInRouteMap(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getPathInfo_serialize(): NavPathInfo {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getPathInfo(this.peer!.ptr)
        const obj : NavPathInfo = NavPathInfoInternal.fromPtr(retval)
        return obj
    }
    private setPathInfo_serialize(pathInfo: NavPathInfo): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathInfo(this.peer!.ptr, toPeerPtr(pathInfo))
    }
    private getPathStack_serialize(): NavPathStack {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getPathStack(this.peer!.ptr)
        const obj : NavPathStack = NavPathStackInternal.fromPtr(retval)
        return obj
    }
    private setPathStack_serialize(pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathStack(this.peer!.ptr, toPeerPtr(pathStack))
    }
    private getNavDestinationId_serialize(): string | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavDestinationContext_getNavDestinationId(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setNavDestinationId_serialize(navDestinationId: string): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setNavDestinationId(this.peer!.ptr, navDestinationId)
    }
    public static fromPtr(ptr: KPointer): NavDestinationContextInternal {
        const obj : NavDestinationContextInternal = new NavDestinationContextInternal()
        obj.peer = new Finalizable(ptr, NavDestinationContextInternal.getFinalizer())
        return obj
    }
}
export class ArkNavDestinationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavDestinationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._NavDestination_construct(peerId, flags)
        const _peer  = new ArkNavDestinationPeer(_peerPtr, peerId, "NavDestination", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavDestinationOptionsAttribute(): void {
        ArkUIGeneratedNativeModule._NavDestinationInterface_setNavDestinationOptions(this.peer.ptr)
    }
    hideTitleBar0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar0(this.peer.ptr, value ? 1 : 0)
    }
    hideTitleBar1Attribute(hide: boolean, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideTitleBar1(this.peer.ptr, hide ? 1 : 0, animated ? 1 : 0)
    }
    onShownAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onShown(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onHiddenAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onHidden(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onBackPressedAttribute(value: (() => boolean)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onBackPressed(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavDestinationMode): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_mode(this.peer.ptr, TypeChecker.NavDestinationMode_ToNumeric(value))
    }
    backButtonIconAttribute(value: ResourceStr | PixelMap | SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if ((RuntimeType.STRING == value_type) || (RuntimeType.OBJECT == value_type)) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as ResourceStr
            let value_0_type : int32 = RuntimeType.UNDEFINED
            value_0_type = runtimeType(value_0)
            if (RuntimeType.STRING == value_0_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_0_0  = value_0 as string
                thisSerializer.writeString(value_0_0)
            }
            else if (RuntimeType.OBJECT == value_0_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_0_1  = value_0 as Resource
                thisSerializer.writeResource(value_0_1)
            }
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as PixelMap
            thisSerializer.writePixelMap(value_1)
        }
        else if (TypeChecker.isSymbolGlyphModifier(value)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as SymbolGlyphModifier
            thisSerializer.writeSymbolGlyphModifier(value_2)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_backButtonIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menusAttribute(value: Array<NavigationMenuItem> | CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Array<NavigationMenuItem>
            thisSerializer.writeInt32(value_0.length as int32)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element : NavigationMenuItem = value_0[i]
                thisSerializer.writeNavigationMenuItem(value_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_menus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onReadyAttribute(value: ((parameter: NavDestinationContext) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onReady(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillAppearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillAppear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillDisappearAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillDisappear(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillShowAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillShow(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onWillHideAttribute(value: (() => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavDestinationAttribute_onWillHide(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemBarStyleAttribute(value: SystemBarStyle | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeSystemBarStyle(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    recoverableAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_recoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    systemTransitionAttribute(value: NavigationSystemTransitionType): void {
        ArkUIGeneratedNativeModule._NavDestinationAttribute_systemTransition(this.peer.ptr, TypeChecker.NavigationSystemTransitionType_ToNumeric(value))
    }
    titleAttribute(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (TypeChecker.isNavDestinationCommonTitle(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as NavDestinationCommonTitle
            thisSerializer.writeNavDestinationCommonTitle(value_2)
        }
        else if (TypeChecker.isNavDestinationCustomTitle(value, false, false)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as NavDestinationCustomTitle
            thisSerializer.writeNavDestinationCustomTitle(value_3)
        }
        else if (TypeChecker.isResource(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(4 as int32)
            const value_4  = value as Resource
            thisSerializer.writeResource(value_4)
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_title(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let toolbarParam_type : int32 = RuntimeType.UNDEFINED
        toolbarParam_type = runtimeType(toolbarParam)
        if (RuntimeType.OBJECT == toolbarParam_type) {
            thisSerializer.writeInt8(0 as int32)
            const toolbarParam_0  = toolbarParam as Array<ToolbarItem>
            thisSerializer.writeInt32(toolbarParam_0.length as int32)
            for (let i = 0; i < toolbarParam_0.length; i++) {
                const toolbarParam_0_element : ToolbarItem = toolbarParam_0[i]
                thisSerializer.writeToolbarItem(toolbarParam_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == toolbarParam_type) {
            thisSerializer.writeInt8(1 as int32)
            const toolbarParam_1  = toolbarParam as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(toolbarParam_1))
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBarAttribute(hide: boolean, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_hideToolBar(this.peer.ptr, hide ? 1 : 0, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    ignoreLayoutSafeAreaAttribute(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): void {
        const thisSerializer : Serializer = Serializer.hold()
        let types_type : int32 = RuntimeType.UNDEFINED
        types_type = runtimeType(types)
        thisSerializer.writeInt8(types_type as int32)
        if ((RuntimeType.UNDEFINED) != (types_type)) {
            const types_value  = types!
            thisSerializer.writeInt32(types_value.length as int32)
            for (let i = 0; i < types_value.length; i++) {
                const types_value_element : LayoutSafeAreaType = types_value[i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaType_ToNumeric(types_value_element))
            }
        }
        let edges_type : int32 = RuntimeType.UNDEFINED
        edges_type = runtimeType(edges)
        thisSerializer.writeInt8(edges_type as int32)
        if ((RuntimeType.UNDEFINED) != (edges_type)) {
            const edges_value  = edges!
            thisSerializer.writeInt32(edges_value.length as int32)
            for (let i = 0; i < edges_value.length; i++) {
                const edges_value_element : LayoutSafeAreaEdge = edges_value[i]
                thisSerializer.writeInt32(TypeChecker.LayoutSafeAreaEdge_ToNumeric(edges_value_element))
            }
        }
        ArkUIGeneratedNativeModule._NavDestinationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface NavDestinationCommonTitle {
    main: string | Resource;
    sub: string | Resource;
}
export interface NavDestinationCustomTitle {
    builder: CustomBuilder;
    height: TitleHeight | Length;
}
export enum NavigationSystemTransitionType {
    DEFAULT = 0,
    NONE = 1,
    TITLE = 2,
    CONTENT = 3
}
export enum NavDestinationMode {
    STANDARD = 0,
    DIALOG = 1
}

export interface RouteMapConfig {
    name: string;
    pageSourceFile: string;
    data: Object;
}
export type Callback_Boolean = () => boolean;
export interface NavDestinationAttribute extends CommonMethod {
    hideTitleBar(hide: boolean, animated?: boolean): this
    onShown(value: (() => void)): this
    onHidden(value: (() => void)): this
    onBackPressed(value: (() => boolean)): this
    mode(value: NavDestinationMode): this
    backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this
    menus(value: Array<NavigationMenuItem> | CustomBuilder): this
    onReady(value: ((parameter: NavDestinationContext) => void)): this
    onWillAppear(value: (() => void)): this
    onWillDisappear(value: (() => void)): this
    onWillShow(value: (() => void)): this
    onWillHide(value: (() => void)): this
    systemBarStyle(value: SystemBarStyle | undefined): this
    recoverable(value: boolean | undefined): this
    systemTransition(value: NavigationSystemTransitionType): this
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this
    hideToolBar(hide: boolean, animated?: boolean): this
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UINavDestinationAttribute extends UICommonMethod {
    /** @memo */
    hideTitleBar(hide: boolean, animated?: boolean): this
    /** @memo */
    onShown(value: (() => void)): this
    /** @memo */
    onHidden(value: (() => void)): this
    /** @memo */
    onBackPressed(value: (() => boolean)): this
    /** @memo */
    mode(value: NavDestinationMode): this
    /** @memo */
    backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this
    /** @memo */
    menus(value: Array<NavigationMenuItem> | CustomBuilder): this
    /** @memo */
    onReady(value: ((parameter: NavDestinationContext) => void)): this
    /** @memo */
    onWillAppear(value: (() => void)): this
    /** @memo */
    onWillDisappear(value: (() => void)): this
    /** @memo */
    onWillShow(value: (() => void)): this
    /** @memo */
    onWillHide(value: (() => void)): this
    /** @memo */
    systemBarStyle(value: SystemBarStyle | undefined): this
    /** @memo */
    recoverable(value: boolean | undefined): this
    /** @memo */
    systemTransition(value: NavigationSystemTransitionType): this
    /** @memo */
    title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this
    /** @memo */
    toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this
    /** @memo */
    hideToolBar(hide: boolean, animated?: boolean): this
    /** @memo */
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    /** @memo */
    attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkNavDestinationStyle extends ArkCommonMethodStyle implements NavDestinationAttribute {
    hideTitleBar_value?: boolean
    onShown_value?: (() => void)
    onHidden_value?: (() => void)
    onBackPressed_value?: (() => boolean)
    mode_value?: NavDestinationMode
    backButtonIcon_value?: ResourceStr | PixelMap | SymbolGlyphModifier
    menus_value?: Array<NavigationMenuItem> | CustomBuilder
    onReady_value?: ((parameter: NavDestinationContext) => void)
    onWillAppear_value?: (() => void)
    onWillDisappear_value?: (() => void)
    onWillShow_value?: (() => void)
    onWillHide_value?: (() => void)
    systemBarStyle_value?: SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    systemTransition_value?: NavigationSystemTransitionType
    public hideTitleBar(hide: boolean, animated?: boolean): this {
        return this
    }
    public onShown(value: (() => void)): this {
        return this
    }
    public onHidden(value: (() => void)): this {
        return this
    }
    public onBackPressed(value: (() => boolean)): this {
        return this
    }
    public mode(value: NavDestinationMode): this {
        return this
    }
    public backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this {
        return this
    }
    public menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        return this
    }
    public onReady(value: ((parameter: NavDestinationContext) => void)): this {
        return this
    }
    public onWillAppear(value: (() => void)): this {
        return this
    }
    public onWillDisappear(value: (() => void)): this {
        return this
    }
    public onWillShow(value: (() => void)): this {
        return this
    }
    public onWillHide(value: (() => void)): this {
        return this
    }
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        return this
    }
    public recoverable(value: boolean | undefined): this {
        return this
    }
    public systemTransition(value: NavigationSystemTransitionType): this {
        return this
    }
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this {
        return this
    }
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        return this
    }
    public hideToolBar(hide: boolean, animated?: boolean): this {
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}
export type Callback_NavDestinationContext_Void = (parameter: NavDestinationContext) => void;
/** @memo:stable */
export class ArkNavDestinationComponent extends ArkCommonMethodComponent implements UINavDestinationAttribute {
    getPeer(): ArkNavDestinationPeer {
        return (this.peer as ArkNavDestinationPeer)
    }
    /** @memo */
    public setNavDestinationOptions(): this {
        if (this.checkPriority("setNavDestinationOptions")) {
            this.getPeer()?.setNavDestinationOptionsAttribute()
            return this
        }
        return this
    }
    /** @memo */
    public hideTitleBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            const value_casted = hide as (boolean)
            this.getPeer()?.hideTitleBar0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onShown(value: (() => void)): this {
        if (this.checkPriority("onShown")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onShownAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onHidden(value: (() => void)): this {
        if (this.checkPriority("onHidden")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onHiddenAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onBackPressed(value: (() => boolean)): this {
        if (this.checkPriority("onBackPressed")) {
            const value_casted = value as ((() => boolean))
            this.getPeer()?.onBackPressedAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: NavDestinationMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavDestinationMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backButtonIcon(value: ResourceStr | PixelMap | SymbolGlyphModifier): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (ResourceStr | PixelMap | SymbolGlyphModifier)
            this.getPeer()?.backButtonIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        if (this.checkPriority("menus")) {
            const value_casted = value as (Array<NavigationMenuItem> | CustomBuilder)
            this.getPeer()?.menusAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onReady(value: ((parameter: NavDestinationContext) => void)): this {
        if (this.checkPriority("onReady")) {
            const value_casted = value as (((parameter: NavDestinationContext) => void))
            this.getPeer()?.onReadyAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillAppear(value: (() => void)): this {
        if (this.checkPriority("onWillAppear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillAppearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillDisappear(value: (() => void)): this {
        if (this.checkPriority("onWillDisappear")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillDisappearAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillShow(value: (() => void)): this {
        if (this.checkPriority("onWillShow")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillShowAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onWillHide(value: (() => void)): this {
        if (this.checkPriority("onWillHide")) {
            const value_casted = value as ((() => void))
            this.getPeer()?.onWillHideAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public recoverable(value: boolean | undefined): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public systemTransition(value: NavigationSystemTransitionType): this {
        if (this.checkPriority("systemTransition")) {
            const value_casted = value as (NavigationSystemTransitionType)
            this.getPeer()?.systemTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public title(value: string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (string | CustomBuilder | NavDestinationCommonTitle | NavDestinationCustomTitle | Resource)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public toolbarConfiguration(toolbarParam: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const toolbarParam_casted = toolbarParam as (Array<ToolbarItem> | CustomBuilder)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(toolbarParam_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hideToolBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_casted = hide as (boolean)
            const animated_casted = animated as (boolean | undefined)
            this.getPeer()?.hideToolBarAttribute(hide_casted, animated_casted)
            return this
        }
        return this
    }
    /** @memo */
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType> | undefined)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge> | undefined)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    /** @memo */
    public attributeModifier(value: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkNavDestination(
    /** @memo */
    style: ((attributes: UINavDestinationAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    
): void {
    const receiver = remember(() => {
        return new ArkNavDestinationComponent()
    })
    NodeAttach<ArkNavDestinationPeer>((): ArkNavDestinationPeer => ArkNavDestinationPeer.create(receiver), (_: ArkNavDestinationPeer) => {
        receiver.setNavDestinationOptions()
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

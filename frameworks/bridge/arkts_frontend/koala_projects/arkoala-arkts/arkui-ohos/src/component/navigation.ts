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

import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { Finalizable, runtimeType, RuntimeType, InteropNativeModule, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32, int8 } from "@koalaui/common"
import { GlobalStateManager, StateContext, __context } from '@koalaui/runtime'
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, BackgroundBlurStyleOptions, BackgroundEffectOptions, ArkCommonMethodComponent, ArkCommonMethodStyle, Callback } from "./common"
import { Length, Dimension, ResourceStr, PX, VP, FP, LPX, Percentage, ResourceColor } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { Resource } from "global.resource"
import { SymbolGlyphModifier, TextModifier } from "./arkui-external"
import { SystemBarStyle } from "./arkui-custom"
import { NodeAttach, remember } from "@koalaui/runtime"
import { TitleHeight } from "./enums"
import { NavDestinationContext, NavDestinationMode } from "./navDestination"
import { LengthMetrics } from "../Graphics"
import { NavExtender } from "./navigationExtender"
import { addPartialUpdate, createUiDetachedRoot } from "../ArkUIEntry"
import { PathStackUtils } from "../handwritten/ArkNavPathStack"
import { setNeedCreate } from "../ArkComponentRoot"
import { ArkStackComponent, ArkStackPeer } from "./stack"

export class NavPathInfoInternal {
    public static fromPtr(ptr: KPointer): NavPathInfo {
        const obj : NavPathInfo = new NavPathInfo(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, NavPathInfo.getFinalizer())
        return obj
    }
}
export class NavPathInfo implements MaterializedBase {
    name: string = ""
    peer?: Finalizable | undefined = undefined
    param: object | null | undefined = undefined
    onPop: ((parameter: PopInfo)=> void) | undefined = undefined
    isEntry: boolean | undefined = false;
    navDestinationId: string | undefined = ""
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_navpathinfo(name: string, isEntry?: boolean): KPointer {
        let isEntry_casted: boolean = false
        if (runtimeType(isEntry) === RuntimeType.BOOLEAN) {
            isEntry_casted = isEntry!
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_ctor(name, isEntry_casted ? 1 : 0)
        return retval
    }
    constructor(name?: string, param?: object | null | undefined, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean) {
        let name_casted: string = ""
        if (runtimeType(name) === RuntimeType.STRING) {
            name_casted = name!
            this.name = name!
        }
        if (runtimeType(param) === RuntimeType.OBJECT) {
            this.param = param
        }
        if (runtimeType(onPop) !== RuntimeType.UNDEFINED) {
            this.onPop = onPop
        }
        let isEntry_casted: boolean = false
        if (runtimeType(isEntry) === RuntimeType.BOOLEAN) {
            isEntry_casted = isEntry!
            this.isEntry = isEntry!
        }
        const ctorPtr: KPointer = NavPathInfo.ctor_navpathinfo(name_casted, isEntry_casted)
        this.peer = new Finalizable(ctorPtr, NavPathInfo.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathInfo_getFinalizer()
    }
    private getName(): string {
        return this.getName_serialize()
    }
    private setName(name: string): void {
        const name_casted = name as (string)
        this.setName_serialize(name_casted)
        return
    }
    private getIsEntry(): boolean | undefined {
        return this.getIsEntry_serialize()
    }
    private setIsEntry(isEntry: boolean): void {
        const isEntry_casted = isEntry as (boolean)
        this.setIsEntry_serialize(isEntry_casted)
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
    updateNavPathInfo(): void {
        this.setName_serialize(this.name)
        this.setIsEntry_serialize(this.isEntry!)
        this.setNavDestinationId_serialize(this.navDestinationId!)
    }
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setName(this.peer!.ptr, name)
    }
    private getIsEntry_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setIsEntry_serialize(isEntry: boolean): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, isEntry ? 1 : 0)
    }
    private getNavDestinationId_serialize(): string | undefined {
        return ArkUIGeneratedNativeModule._NavPathInfo_getNavDestinationId(this.peer!.ptr)
    }
    private setNavDestinationId_serialize(navDestinationId: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setNavDestinationId(this.peer!.ptr, navDestinationId)
    }
}
export class NavPathStackInternal {
    public static fromPtr(ptr: KPointer): NavPathStack {
        const obj : NavPathStack = new NavPathStack()
        obj.peer = new Finalizable(ptr, NavPathStack.getFinalizer())
        return obj
    }
}
export class NavPathStack implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    static ctor_navpathstack(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = NavPathStack.ctor_navpathstack()
        this.peer = new Finalizable(ctorPtr, NavPathStack.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavPathStack_getFinalizer()
    }
    public pushPath(info: NavPathInfo, animated?: boolean | undefined): void {
        PathStackUtils.pushPath(this, info, animated)
    }
    public pushDestination(info: NavPathInfo, animated?: boolean | undefined): Promise<void> {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            return this.pushDestination0_serialize(info_casted, animated_casted)
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            return this.pushDestination1_serialize(info_casted, options_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushPathByName(name: string, param: Object, onPop: Callback<PopInfo>, animated?: boolean | undefined): void {
        PathStackUtils.pushPathByName(this, name, param, onPop, animated)
    }
    public pushDestinationByName(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): Promise<void> {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((parameter: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            return this.pushDestinationByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public replacePath(info: NavPathInfo, animated?: NavigationOptions | undefined): void {
        PathStackUtils.replacePath(this, info, animated)
    }
    public replaceDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        return this.replaceDestination_serialize(info_casted, options_casted)
    }
    public replacePathByName(name: string, param: Object, animated?: boolean): void {
        PathStackUtils.replacePathByName(this, name, param, animated)
    }
    public removeByIndexes(indexes: Array<number>): number {
        const indexes_casted = indexes as (Array<number>)
        return this.removeByIndexes_serialize(indexes_casted)
    }
    public removeByName(name: string): number {
        const name_casted = name as (string)
        return this.removeByName_serialize(name_casted)
    }
    public removeByNavDestinationId(navDestinationId: string): boolean {
        const navDestinationId_casted = navDestinationId as (string)
        return this.removeByNavDestinationId_serialize(navDestinationId_casted)
    }
    public pop(result: Object, animated?: boolean): NavPathInfo | undefined {
        return PathStackUtils.pop(this, result, animated)
    }
    public popToName(name: string, result: Object, animated?: boolean): number {
        return PathStackUtils.popToName(this, name, result, animated)
    }
    public popToIndex(index: number, result: Object, animated?: boolean): void {
        PathStackUtils.popToIndex(this, index, result, animated)
    }
    public moveToTop(name: string, animated?: boolean): number {
        const name_casted = name as (string)
        const animated_casted = animated as (boolean | undefined)
        return this.moveToTop_serialize(name_casted, animated_casted)
    }
    public moveIndexToTop(index: number, animated?: boolean): void {
        const index_casted = index as (number)
        const animated_casted = animated as (boolean | undefined)
        this.moveIndexToTop_serialize(index_casted, animated_casted)
        return
    }
    public clear(animated?: boolean): void {
        const animated_casted = animated as (boolean | undefined)
        this.clear_serialize(animated_casted)
        return
    }
    public getAllPathName(): Array<string> {
        return this.getAllPathName_serialize()
    }
    public getParamByIndex(index: number): Object | undefined {
        return PathStackUtils.getParamByIndex(this, index)
    }
    public getParamByName(name: string): Array<Object | undefined> {
        return PathStackUtils.getParamByName(this, name)
    }
    public getIndexByName(name: string): Array<number> {
        const name_casted = name as (string)
        return this.getIndexByName_serialize(name_casted)
    }
    public getParent(): NavPathStack | undefined {
        return this.getParent_serialize()
    }
    public size(): number {
        return this.size_serialize()
    }
    public disableAnimation(value: boolean): void {
        const value_casted = value as (boolean)
        this.disableAnimation_serialize(value_casted)
        return
    }
    public setInterception(interception: NavigationInterception): void {
        const interception_casted = interception as (NavigationInterception)
        this.setInterception_serialize(interception_casted)
        return
    }
    public getPathStack(): Array<NavPathInfo> {
        return this.getPathStack_serialize()
    }
    public setPathStack(pathStack: Array<NavPathInfo>, animated?: boolean): void {
        const pathStack_casted = pathStack as (Array<NavPathInfo>)
        const animated_casted = animated as (boolean | undefined)
        this.setPathStack_serialize(pathStack_casted, animated_casted)
        return
    }
    private pushDestination0_serialize(info: NavPathInfo, animated?: boolean): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestination1_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestinationByName0_serialize(name: string, param: Object, animated?: boolean): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestinationByName1_serialize(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        thisSerializer.holdAndWriteCallback(onPop)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private replaceDestination_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        const retval  = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_replaceDestination(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeByIndexes_serialize(indexes: Array<number>): number {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(indexes.length as int32)
        for (let i = 0; i < indexes.length; i++) {
            const indexes_element : number = indexes[i]
            thisSerializer.writeNumber(indexes_element)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByIndexes(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeByName_serialize(name: string): number {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByName(this.peer!.ptr, name)
        return retval
    }
    private removeByNavDestinationId_serialize(navDestinationId: string): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_removeByNavDestinationId(this.peer!.ptr, navDestinationId)
        return retval
    }
    private popToName0_serialize(name: string, animated?: boolean): number {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToName1_serialize(name: string, result: Object, animated?: boolean): number {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_popToName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToIndex0_serialize(index: number, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex0(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private popToIndex1_serialize(index: number, result: Object, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex1(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private moveToTop_serialize(name: string, animated?: boolean): number {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_moveToTop(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private moveIndexToTop_serialize(index: number, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_moveIndexToTop(this.peer!.ptr, index, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private clear_serialize(animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_clear(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getAllPathName_serialize(): Array<string> {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getAllPathName(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private getIndexByName_serialize(name: string): Array<number> {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getIndexByName(this.peer!.ptr, name) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult : Array<number> = buffer
        return returnResult
    }
    private getParent_serialize(): NavPathStack | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParent(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private size_serialize(): number {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_size(this.peer!.ptr)
        return retval
    }
    private disableAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._NavPathStack_disableAnimation(this.peer!.ptr, value ? 1 : 0)
    }
    private setInterception_serialize(interception: NavigationInterception): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNavigationInterception(interception)
        ArkUIGeneratedNativeModule._NavPathStack_setInterception(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getPathStack_serialize(): Array<NavPathInfo> {
        // @ts-ignore
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getPathStack(this.peer!.ptr) as FixedArray<byte>
        // @ts-ignore
        let exactRetValue: byte[] = new Array<byte>
        for (let i = 0; i < retval.length; i++) {
            // @ts-ignore
            exactRetValue.push(new Byte(retval[i]))
        }
        let retvalDeserializer : Deserializer = new Deserializer(exactRetValue, exactRetValue.length as int32)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<NavPathInfo> = new Array<NavPathInfo>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNavPathInfo() as NavPathInfo)
        }
        const returnResult : Array<NavPathInfo> = buffer
        return returnResult
    }
    private setPathStack_serialize(pathStack: Array<NavPathInfo>, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeInt32(pathStack.length as int32)
        for (let i = 0; i < pathStack.length; i++) {
            const pathStack_element : NavPathInfo = pathStack[i]
            thisSerializer.writeNavPathInfo(pathStack_element)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_setPathStack(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export interface NavigationTransitionProxy {
    from: NavContentInfo
    to: NavContentInfo
    isInteractive?: boolean | undefined
    finishTransition(): void
    cancelTransition(): void
    updateTransition(progress: number): void
}
export class NavigationTransitionProxyInternal implements MaterializedBase,NavigationTransitionProxy {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get from(): NavContentInfo {
        throw new Error("Not implemented")
    }
    set from(from: NavContentInfo) {
        this.setFrom(from)
    }
    get to(): NavContentInfo {
        throw new Error("Not implemented")
    }
    set to(to: NavContentInfo) {
        this.setTo(to)
    }
    get isInteractive(): boolean | undefined {
        return this.getIsInteractive()
    }
    set isInteractive(isInteractive: boolean | undefined) {
        const isInteractive_NonNull  = (isInteractive as boolean)
        this.setIsInteractive(isInteractive_NonNull)
    }
    static ctor_navigationtransitionproxy(): KPointer {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_ctor()
        return retval
    }
    constructor() {
        const ctorPtr : KPointer = NavigationTransitionProxyInternal.ctor_navigationtransitionproxy()
        this.peer = new Finalizable(ctorPtr, NavigationTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this.finishTransition_serialize()
        return
    }
    public cancelTransition(): void {
        this.cancelTransition_serialize()
        return
    }
    public updateTransition(progress: number): void {
        const progress_casted = progress as (number)
        this.updateTransition_serialize(progress_casted)
        return
    }
    private getFrom(): NavContentInfo {
        return this.getFrom_serialize()
    }
    private setFrom(from: NavContentInfo): void {
        const from_casted = from as (NavContentInfo)
        this.setFrom_serialize(from_casted)
        return
    }
    private getTo(): NavContentInfo {
        return this.getTo_serialize()
    }
    private setTo(to: NavContentInfo): void {
        const to_casted = to as (NavContentInfo)
        this.setTo_serialize(to_casted)
        return
    }
    private getIsInteractive(): boolean | undefined {
        return this.getIsInteractive_serialize()
    }
    private setIsInteractive(isInteractive: boolean): void {
        const isInteractive_casted = isInteractive as (boolean)
        this.setIsInteractive_serialize(isInteractive_casted)
        return
    }
    private finishTransition_serialize(): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_finishTransition(this.peer!.ptr)
    }
    private cancelTransition_serialize(): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_cancelTransition(this.peer!.ptr)
    }
    private updateTransition_serialize(progress: number): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_updateTransition(this.peer!.ptr, progress)
    }
    private getFrom_serialize(): NavContentInfo {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFrom(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : NavContentInfo = retvalDeserializer.readNavContentInfo()
        return returnResult
    }
    private setFrom_serialize(from: NavContentInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNavContentInfo(from)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setFrom(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getTo_serialize(): NavContentInfo {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getTo(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length as int32)
        const returnResult : NavContentInfo = retvalDeserializer.readNavContentInfo()
        return returnResult
    }
    private setTo_serialize(to: NavContentInfo): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.writeNavContentInfo(to)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setTo(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsInteractive_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getIsInteractive(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setIsInteractive_serialize(isInteractive: boolean): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setIsInteractive(this.peer!.ptr, isInteractive ? 1 : 0)
    }
    public static fromPtr(ptr: KPointer): NavigationTransitionProxyInternal {
        const obj : NavigationTransitionProxyInternal = new NavigationTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, NavigationTransitionProxyInternal.getFinalizer())
        return obj
    }
}
export class ArkNavigationPeer extends ArkCommonMethodPeer {
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component: ComponentBase | undefined, flags: int32 = 0): ArkNavigationPeer {
        const peerId  = PeerNode.nextId()
        const _peerPtr  = ArkUIGeneratedNativeModule._Navigation_construct(peerId, flags)
        const _peer  = new ArkNavigationPeer(_peerPtr, peerId, "Navigation", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setNavigationOptions0Attribute(): void {
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions0(this.peer.ptr)
    }
    setNavigationOptions1Attribute(pathInfos: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavigationInterface_setNavigationOptions1(this.peer.ptr, toPeerPtr(pathInfos))
    }
    navBarWidthAttribute(value: Length | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navBarPositionAttribute(value: NavBarPosition | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavBarPosition)
            thisSerializer.writeInt32(TypeChecker.NavBarPosition_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarPosition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navBarWidthRangeAttribute(value: [ Dimension, Dimension ] | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            const value_value_0  = value_value[0]
            thisSerializer.writeLength(value_value_0)
            const value_value_1  = value_value[1]
            thisSerializer.writeLength(value_value_1)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidthRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeLength(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_minContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavigationMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavigationMode)
            thisSerializer.writeInt32(TypeChecker.NavigationMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_mode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon0Attribute(value: string | PixelMap | Resource | SymbolGlyphModifier | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.STRING == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as string
                thisSerializer.writeString(value_value_0)
            }
            else if (TypeChecker.isPixelMap(value_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as PixelMap
                thisSerializer.writePixelMap(value_value_1)
            }
            else if (TypeChecker.isResource(value_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as Resource
                thisSerializer.writeResource(value_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(value_value)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(value_value_3)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    backButtonIcon1Attribute(icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): void {
        const thisSerializer : Serializer = Serializer.hold()
        let icon_type : int32 = RuntimeType.UNDEFINED
        icon_type = runtimeType(icon)
        thisSerializer.writeInt8(icon_type as int32)
        if ((RuntimeType.UNDEFINED) != (icon_type)) {
            const icon_value  = icon!
            let icon_value_type : int32 = RuntimeType.UNDEFINED
            icon_value_type = runtimeType(icon_value)
            if (RuntimeType.STRING == icon_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const icon_value_0  = icon_value as string
                thisSerializer.writeString(icon_value_0)
            }
            else if (TypeChecker.isPixelMap(icon_value, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const icon_value_1  = icon_value as PixelMap
                thisSerializer.writePixelMap(icon_value_1)
            }
            else if (TypeChecker.isResource(icon_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const icon_value_2  = icon_value as Resource
                thisSerializer.writeResource(icon_value_2)
            }
            else if (TypeChecker.isSymbolGlyphModifier(icon_value)) {
                thisSerializer.writeInt8(3 as int32)
                const icon_value_3  = icon_value as SymbolGlyphModifier
                thisSerializer.writeSymbolGlyphModifier(icon_value_3)
            }
        }
        let accessibilityText_type : int32 = RuntimeType.UNDEFINED
        accessibilityText_type = runtimeType(accessibilityText)
        thisSerializer.writeInt8(accessibilityText_type as int32)
        if ((RuntimeType.UNDEFINED) != (accessibilityText_type)) {
            const accessibilityText_value  = accessibilityText!
            let accessibilityText_value_type : int32 = RuntimeType.UNDEFINED
            accessibilityText_value_type = runtimeType(accessibilityText_value)
            if (RuntimeType.STRING == accessibilityText_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const accessibilityText_value_0  = accessibilityText_value as string
                thisSerializer.writeString(accessibilityText_value_0)
            }
            else if (TypeChecker.isResource(accessibilityText_value, false, false, false, false, false)) {
                thisSerializer.writeInt8(1 as int32)
                const accessibilityText_value_1  = accessibilityText_value as Resource
                thisSerializer.writeResource(accessibilityText_value_1)
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideNavBarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideNavBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    subTitleAttribute(value: string | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeString(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_subTitle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideTitleBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideTitleBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type as int32)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideBackButtonAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideBackButton(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    titleModeAttribute(value: NavigationTitleMode | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = (value as NavigationTitleMode)
            thisSerializer.writeInt32(TypeChecker.NavigationTitleMode_ToNumeric(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_titleMode(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus0Attribute(value: Array<NavigationMenuItem> | CustomBuilder | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : NavigationMenuItem = value_value_0[i]
                    thisSerializer.writeNavigationMenuItem(value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_menus0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    menus1Attribute(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let items_type : int32 = RuntimeType.UNDEFINED
        items_type = runtimeType(items)
        thisSerializer.writeInt8(items_type as int32)
        if ((RuntimeType.UNDEFINED) != (items_type)) {
            const items_value  = items!
            let items_value_type : int32 = RuntimeType.UNDEFINED
            items_value_type = runtimeType(items_value)
            if (RuntimeType.OBJECT == items_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const items_value_0  = items_value as Array<NavigationMenuItem>
                thisSerializer.writeInt32(items_value_0.length as int32)
                for (let i = 0; i < items_value_0.length; i++) {
                    const items_value_0_element : NavigationMenuItem = items_value_0[i]
                    thisSerializer.writeNavigationMenuItem(items_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == items_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const items_value_1  = items_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(items_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationMenuOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_menus1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolBarAttribute(value: CustomBuilder | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value))
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_toolBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBar0Attribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar0(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBar1Attribute(hide: boolean | undefined, animated: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let hide_type : int32 = RuntimeType.UNDEFINED
        hide_type = runtimeType(hide)
        thisSerializer.writeInt8(hide_type as int32)
        if ((RuntimeType.UNDEFINED) != (hide_type)) {
            const hide_value  = hide!
            thisSerializer.writeBoolean(hide_value)
        }
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar1(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableToolBarAdaptationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableToolBarAdaptation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onTitleModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavBarStateChangeAttribute(value: ((isVisible: boolean) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavBarStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavigationModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navDestinationAttribute(value: ((name: string,param: Object | null | undefined) => void) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navDestination(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customNavContentTransitionAttribute(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.holdAndWriteCallback(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_customNavContentTransition(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_systemBarStyle(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_recoverable(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableDragBarAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableDragBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    enableModeChangeAnimationAttribute(value: boolean | undefined): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            thisSerializer.writeBoolean(value_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_enableModeChangeAnimation(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    titleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (value_value_type == RuntimeType.STRING || TypeChecker.isResource(value, false, false, false, false, false)) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as ResourceStr
                let value_value_0_type : int32 = RuntimeType.UNDEFINED
                value_value_0_type = runtimeType(value_value_0)
                if (RuntimeType.STRING == value_value_0_type) {
                    thisSerializer.writeInt8(0 as int32)
                    const value_value_0_0  = value_value_0 as string
                    thisSerializer.writeString(value_value_0_0)
                }
                else if (RuntimeType.OBJECT == value_value_0_type) {
                    thisSerializer.writeInt8(1 as int32)
                    const value_value_0_1  = value_value_0 as Resource
                    thisSerializer.writeResource(value_value_0_1)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
            else if (TypeChecker.isNavigationCommonTitle(value_value, false, false)) {
                thisSerializer.writeInt8(2 as int32)
                const value_value_2  = value_value as NavigationCommonTitle
                thisSerializer.writeNavigationCommonTitle(value_value_2)
            }
            else if (TypeChecker.isNavigationCustomTitle(value_value, false, false)) {
                thisSerializer.writeInt8(3 as int32)
                const value_value_3  = value_value as NavigationCustomTitle
                thisSerializer.writeNavigationCustomTitle(value_value_3)
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationTitleOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_title(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        thisSerializer.writeInt8(value_type as int32)
        if ((RuntimeType.UNDEFINED) != (value_type)) {
            const value_value  = value!
            let value_value_type : int32 = RuntimeType.UNDEFINED
            value_value_type = runtimeType(value_value)
            if (RuntimeType.OBJECT == value_value_type) {
                thisSerializer.writeInt8(0 as int32)
                const value_value_0  = value_value as Array<ToolbarItem>
                thisSerializer.writeInt32(value_value_0.length as int32)
                for (let i = 0; i < value_value_0.length; i++) {
                    const value_value_0_element : ToolbarItem = value_value_0[i]
                    thisSerializer.writeToolbarItem(value_value_0_element)
                }
            }
            else if (RuntimeType.FUNCTION == value_value_type) {
                thisSerializer.writeInt8(1 as int32)
                const value_value_1  = value_value as CustomBuilder
                thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_value_1))
            }
        }
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationToolbarOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_toolbarConfiguration(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
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
        ArkUIGeneratedNativeModule._NavigationAttribute_ignoreLayoutSafeArea(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
}
export type Callback_Boolean_Void = (isVisible: boolean) => void;
export interface NavigationCommonTitle {
    main: string | Resource;
    sub: string | Resource;
}
export interface NavigationCustomTitle {
    builder: CustomBuilder;
    height: TitleHeight | Length;
}
export enum NavigationMode {
    STACK = 0,
    Stack = 0,
    SPLIT = 1,
    Split = 1,
    AUTO = 2,
    Auto = 2
}
export enum NavBarPosition {
    START = 0,
    Start = 0,
    END = 1,
    End = 1
}
export enum NavigationTitleMode {
    FREE = 0,
    Free = 0,
    FULL = 1,
    Full = 1,
    MINI = 2,
    Mini = 2
}
export interface NavigationMenuItem {
    value: string | Resource;
    icon?: string | Resource;
    symbolIcon?: SymbolGlyphModifier;
    isEnabled?: boolean;
    action?: (() => void);
}
export interface PopInfo {
    info: NavPathInfo;
    result: Object;
}
export enum LaunchMode {
    STANDARD = 0,
    MOVE_TO_TOP_SINGLETON = 1,
    POP_TO_SINGLETON = 2,
    NEW_INSTANCE = 3
}
export interface NavigationOptions {
    launchMode?: LaunchMode;
    animated?: boolean;
}
export type NavBar = string;
export type InterceptionShowCallback = (from: NavDestinationContext | NavBar, to: NavDestinationContext | NavBar, operation: NavigationOperation, isAnimated: boolean) => void;
export type InterceptionModeCallback = (mode: NavigationMode) => void;
export interface NavigationInterception {
    willShow?: InterceptionShowCallback;
    didShow?: InterceptionShowCallback;
    modeChange?: InterceptionModeCallback;
}
export enum ToolbarItemStatus {
    NORMAL = 0,
    DISABLED = 1,
    ACTIVE = 2
}
export enum NavigationOperation {
    PUSH = 1,
    POP = 2,
    REPLACE = 3
}
export interface ToolbarItem {
    value: ResourceStr;
    icon?: ResourceStr;
    symbolIcon?: SymbolGlyphModifier;
    action?: (() => void);
    status?: ToolbarItemStatus;
    activeIcon?: ResourceStr;
    activeSymbolIcon?: SymbolGlyphModifier;
}
export interface NavigationTitleOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    barStyle?: BarStyle;
    paddingStart?: LengthMetrics;
    paddingEnd?: LengthMetrics;
    mainTitleModifier?: TextModifier;
    subTitleModifier?: TextModifier;
    enableHoverMode?: boolean;
}
export enum BarStyle {
    STANDARD = 0,
    STACK = 1,
    SAFE_AREA_PADDING = 2
}
export interface NavigationToolbarOptions {
    backgroundColor?: ResourceColor;
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
    moreButtonOptions?: MoreButtonOptions;
    barStyle?: BarStyle;
    hideItemValue?: boolean;
}
export interface NavigationMenuOptions {
    moreButtonOptions?: MoreButtonOptions;
}
export interface MoreButtonOptions {
    backgroundBlurStyle?: BlurStyle;
    backgroundBlurStyleOptions?: BackgroundBlurStyleOptions;
    backgroundEffect?: BackgroundEffectOptions;
}
export type Tuple_Dimension_Dimension = [
    Dimension,
    Dimension
]
export type Callback_NavigationTitleMode_Void = (titleMode: NavigationTitleMode) => void;
export type Callback_NavigationMode_Void = (mode: NavigationMode) => void;
export type Callback_String_Opt_Object_Void = (name: string, param: Object | undefined) => void;
export type Type_NavigationAttribute_customNavContentTransition_delegate = (from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined;
export interface NavigationAttribute extends CommonMethod {
    navBarWidth(value: Length | undefined): this
    navBarPosition(value: NavBarPosition | undefined): this
    navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this
    minContentWidth(value: Dimension | undefined): this
    mode(value: NavigationMode | undefined): this
    backButtonIcon(icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this
    hideNavBar(value: boolean | undefined): this
    subTitle(value: string | undefined): this
    hideTitleBar(hide: boolean | undefined, animated?: boolean): this
    hideBackButton(value: boolean | undefined): this
    titleMode(value: NavigationTitleMode | undefined): this
    menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this
    toolBar(value: CustomBuilder | undefined): this
    hideToolBar(hide: boolean | undefined, animated?: boolean): this
    enableToolBarAdaptation(value: boolean | undefined): this
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this
    onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this
    onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this
    navDestination(
        /** @memo */
        value: ((name: string,param: Object | null | undefined) => void) | undefined): this
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this
    systemBarStyle(value: SystemBarStyle | undefined): this
    recoverable(value: boolean | undefined): this
    enableDragBar(value: boolean | undefined): this
    enableModeChangeAnimation(value: boolean | undefined): this
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
}
export class ArkNavigationStyle extends ArkCommonMethodStyle implements NavigationAttribute {
    navBarWidth_value?: Length | undefined
    navBarPosition_value?: NavBarPosition | undefined
    navBarWidthRange_value?: [ Dimension, Dimension ] | undefined
    minContentWidth_value?: Dimension | undefined
    mode_value?: NavigationMode | undefined
    backButtonIcon_value?: string | PixelMap | Resource | SymbolGlyphModifier | undefined
    hideNavBar_value?: boolean | undefined
    subTitle_value?: string | undefined
    hideTitleBar_value?: boolean | undefined
    hideBackButton_value?: boolean | undefined
    titleMode_value?: NavigationTitleMode | undefined
    menus_value?: Array<NavigationMenuItem> | CustomBuilder | undefined
    toolBar_value?: CustomBuilder | undefined
    toolbarConfiguration_value?: Array<ToolbarItem> | CustomBuilder | undefined
    hideToolBar_value?: boolean | undefined
    enableToolBarAdaptation_value?: boolean | undefined
    onTitleModeChange_value?: ((titleMode: NavigationTitleMode) => void) | undefined
    onNavBarStateChange_value?: ((isVisible: boolean) => void) | undefined
    onNavigationModeChange_value?: ((mode: NavigationMode) => void) | undefined
    navDestination_value?: ((name: string,param: Object | undefined) => void) | undefined
    customNavContentTransition_value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined
    systemBarStyle_value?: SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    enableDragBar_value?: boolean | undefined
    enableModeChangeAnimation_value?: boolean | undefined
    public navBarWidth(value: Length | undefined): this {
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        return this
    }
    public backButtonIcon(icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        return this
    }
    public subTitle(value: string | undefined): this {
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        return this
    }
    public titleMode(value: NavigationTitleMode | undefined): this {
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        return this
    }
    public toolBar(value: CustomBuilder | undefined): this {
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        return this
    }
    navDestination(
        /** @memo */
        value: ((name: string,param: Object | null | undefined) => void) | undefined): this {
            return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        return this
    }
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        return this
    }
    public recoverable(value: boolean | undefined): this {
        return this
    }
    public enableDragBar(value: boolean | undefined): this {
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
}
export type Callback_NavigationTransitionProxy_Void = (transitionProxy: NavigationTransitionProxy) => void;
export interface NavigationAnimatedTransition {
    onTransitionEnd?: ((isVisible: boolean) => void);
    timeout?: number;
    isInteractive?: boolean;
    transition: ((transitionProxy: NavigationTransitionProxy) => void);
}
export interface NavContentInfo {
    name?: string;
    index: number;
    mode?: NavDestinationMode;
    param?: Object;
    navDestinationId?: string;
}
export type Callback_PopInfo_Void = (parameter: PopInfo) => void;
export class ArkNavigationComponent extends ArkCommonMethodComponent implements NavigationAttribute {
    /** @memo */
    _navDestination: (name: string, param: Object | null | undefined) => void =
        /** @memo */
        (name: string, param: object | null | undefined) => {
            InteropNativeModule._NativeLog("_navDestination attribute is undefined")
        }
    _needSync: boolean = false
    getPeer(): ArkNavigationPeer {
        return (this.peer as ArkNavigationPeer)
    }
    public setNavigationOptions(pathInfos?: NavPathStack): this {
        if (this.checkPriority("setNavigationOptions")) {
            let info: NavPathStack = new NavPathStack();
            const pathInfos_type = runtimeType(pathInfos)
            if (pathInfos_type != RuntimeType.UNDEFINED) {
                info = pathInfos!
            }
            this.getPeer()?.setNavigationOptions1Attribute(info)
            return this
        }
        return this
    }
    public navBarWidth(value: Length | undefined): this {
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length | undefined)
            this.getPeer()?.navBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarPosition(value: NavBarPosition | undefined): this {
        if (this.checkPriority("navBarPosition")) {
            const value_casted = value as (NavBarPosition | undefined)
            this.getPeer()?.navBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ] | undefined): this {
        if (this.checkPriority("navBarWidthRange")) {
            const value_casted = value as ([ Dimension, Dimension ] | undefined)
            this.getPeer()?.navBarWidthRangeAttribute(value_casted)
            return this
        }
        return this
    }
    public minContentWidth(value: Dimension | undefined): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension | undefined)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    public mode(value: NavigationMode | undefined): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavigationMode | undefined)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    public backButtonIcon(icon: string | PixelMap | Resource | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr): this {
        if (this.checkPriority("backButtonIcon")) {
            const icon_type = runtimeType(icon)
            const accessibilityText_type = runtimeType(accessibilityText)
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) ||
                (RuntimeType.UNDEFINED == icon_type)) && (RuntimeType.UNDEFINED == accessibilityText_type)) {
                const value_casted = icon as (string | PixelMap | Resource | SymbolGlyphModifier | undefined)
                this.getPeer()?.backButtonIcon0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.STRING == icon_type) || (RuntimeType.OBJECT == icon_type) ||
                (RuntimeType.UNDEFINED == icon_type)) && ((RuntimeType.STRING == accessibilityText_type) ||
                (RuntimeType.OBJECT == accessibilityText_type))) {
                const icon_casted = icon as (string | PixelMap | Resource | SymbolGlyphModifier | undefined)
                const accessibilityText_casted = accessibilityText as (ResourceStr)
                this.getPeer()?.backButtonIcon1Attribute(icon_casted, accessibilityText_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hideNavBar(value: boolean | undefined): this {
        if (this.checkPriority("hideNavBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.hideNavBarAttribute(value_casted)
            return this
        }
        return this
    }
    public subTitle(value: string | undefined): this {
        if (this.checkPriority("subTitle")) {
            const value_casted = value as (string | undefined)
            this.getPeer()?.subTitleAttribute(value_casted)
            return this
        }
        return this
    }
    public hideTitleBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideTitleBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && (RuntimeType.UNDEFINED == animated_type)) {
                const value_casted = hide as (boolean | undefined)
                this.getPeer()?.hideTitleBar0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
                const hide_casted = hide as (boolean | undefined)
                const animated_casted = animated as (boolean | undefined)
                this.getPeer()?.hideTitleBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public hideBackButton(value: boolean | undefined): this {
        if (this.checkPriority("hideBackButton")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.hideBackButtonAttribute(value_casted)
            return this
        }
        return this
    }
    public titleMode(value: NavigationTitleMode | undefined): this {
        if (this.checkPriority("titleMode")) {
            const value_casted = value as (NavigationTitleMode | undefined)
            this.getPeer()?.titleModeAttribute(value_casted)
            return this
        }
        return this
    }
    public menus(items: Array<NavigationMenuItem> | CustomBuilder | undefined, options?: NavigationMenuOptions): this {
        if (this.checkPriority("menus")) {
            const items_type = runtimeType(items)
            const options_type = runtimeType(options)
            if (((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type)) && (RuntimeType.UNDEFINED == options_type)) {
                const value_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                this.getPeer()?.menus0Attribute(value_casted)
                return this
            }
            if ((RuntimeType.OBJECT == items_type) || (RuntimeType.FUNCTION == items_type) || (RuntimeType.UNDEFINED == items_type) && (RuntimeType.UNDEFINED != options_type)) {
                const items_casted = items as (Array<NavigationMenuItem> | CustomBuilder | undefined)
                const options_casted = options as (NavigationMenuOptions)
                this.getPeer()?.menus1Attribute(items_casted, options_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public toolBar(value: CustomBuilder | undefined): this {
        if (this.checkPriority("toolBar")) {
            const value_casted = value as (CustomBuilder | undefined)
            this.getPeer()?.toolBarAttribute(value_casted)
            return this
        }
        return this
    }
    public hideToolBar(hide: boolean | undefined, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && (RuntimeType.UNDEFINED == animated_type)) {
                const value_casted = hide as (boolean | undefined)
                this.getPeer()?.hideToolBar0Attribute(value_casted)
                return this
            }
            if (((RuntimeType.BOOLEAN == hide_type) || (RuntimeType.UNDEFINED == hide_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
                const hide_casted = hide as (boolean | undefined)
                const animated_casted = animated as (boolean | undefined)
                this.getPeer()?.hideToolBar1Attribute(hide_casted, animated_casted)
                return this
            }
            throw new Error("Can not select appropriate overload")
        }
        return this
    }
    public enableToolBarAdaptation(value: boolean | undefined): this {
        if (this.checkPriority("enableToolBarAdaptation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableToolBarAdaptationAttribute(value_casted)
            return this
        }
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void) | undefined): this {
        if (this.checkPriority("onTitleModeChange")) {
            const value_casted = value as (((titleMode: NavigationTitleMode) => void) | undefined)
            this.getPeer()?.onTitleModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void) | undefined): this {
        if (this.checkPriority("onNavBarStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void) | undefined)
            this.getPeer()?.onNavBarStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void) | undefined): this {
        if (this.checkPriority("onNavigationModeChange")) {
            const value_casted = value as (((mode: NavigationMode) => void) | undefined)
            this.getPeer()?.onNavigationModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    public navDestination(
        /** @memo */
        value: ((name: string,param: Object | null | undefined) => void) | undefined): this {
        if (runtimeType(value) !== RuntimeType.UNDEFINED) {
            this._navDestination = value!
        }
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined): this {
        if (this.checkPriority("customNavContentTransition")) {
            const value_casted = value as (((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined) | undefined)
            this.getPeer()?.customNavContentTransitionAttribute(value_casted)
            return this
        }
        return this
    }
    public systemBarStyle(value: SystemBarStyle | undefined): this {
        if (this.checkPriority("systemBarStyle")) {
            const value_casted = value as (SystemBarStyle | undefined)
            this.getPeer()?.systemBarStyleAttribute(value_casted)
            return this
        }
        return this
    }
    public recoverable(value: boolean | undefined): this {
        if (this.checkPriority("recoverable")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.recoverableAttribute(value_casted)
            return this
        }
        return this
    }
    public enableDragBar(value: boolean | undefined): this {
        if (this.checkPriority("enableDragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDragBarAttribute(value_casted)
            return this
        }
        return this
    }
    public enableModeChangeAnimation(value: boolean | undefined): this {
        if (this.checkPriority("enableModeChangeAnimation")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableModeChangeAnimationAttribute(value_casted)
            return this
        }
        return this
    }
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle | undefined)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder | undefined, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const value_casted = value as (Array<ToolbarItem> | CustomBuilder | undefined)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        if (this.checkPriority("ignoreLayoutSafeArea")) {
            const types_casted = types as (Array<LayoutSafeAreaType>)
            const edges_casted = edges as (Array<LayoutSafeAreaEdge>)
            this.getPeer()?.ignoreLayoutSafeAreaAttribute(types_casted, edges_casted)
            return this
        }
        return this
    }
    
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }

    public updateNeedSync(needSync: boolean): void {
        this._needSync = needSync
    }

    public isNeedSync(): boolean {
        return this._needSync
    }
}
/** @memo */
export function Navigation(
    /** @memo */
    style: ((attributes: NavigationAttribute) => void) | undefined,
    pathInfos?: NavPathStack,
    /** @memo */
    content_?: (() => void) | undefined,
): void {
    const receiver = remember(() => {
        return new ArkNavigationComponent()
    })
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (_: ArkNavigationPeer) => {
        receiver.setNavigationOptions(pathInfos)
        style?.(receiver)
        content_?.()
        if (pathInfos != undefined) {
            remember(() => {
                const updater: (name: string, param: object|undefined)=>PeerNode =
                (name: string, param: object|undefined) => {
                    let node = ArkStackPeer.create(new ArkStackComponent())
                    return createUiDetachedRoot((): PeerNode => ArkStackPeer.create(new ArkStackComponent()), () => {
                        setNeedCreate(true)
                        receiver._navDestination(name, param);
                        setNeedCreate(false)
                    })
                }
                const value_casted = updater as ((name: string, param: object|undefined) => PeerNode)
                NavExtender.setUpdateStackCallback(pathInfos!, () => {
                    addPartialUpdate(() => {
                        if (!receiver.isNeedSync()) {
                            return
                        }
                        InteropNativeModule._NativeLog("AceNavigation: sync navigation stack")
                        receiver.updateNeedSync(false)
                        let size: int32 = pathInfos!.size() as int32
                        InteropNativeModule._NativeLog("AceNavigation: path stack size: " + size)
                        let names: Array<string> = pathInfos!.getAllPathName()
                        for (let index: int32 = 0; index < size; index++) {
                            if (NavExtender.checkNeedCreate(receiver.getPeer().peer.ptr, index)) {
                                InteropNativeModule._NativeLog("AceNavigation: create new node: " + index + ", name: " + names[index])
                                let param = pathInfos!.getParamByIndex(index)
                                let node = value_casted(names[index], param)
                                NavExtender.setNavDestinationNode(pathInfos!, index, node.peer.ptr)
                            }
                        }
                        NavExtender.syncStack(pathInfos!)
                    }, __context, (isBefore: boolean) => {})
                    receiver.updateNeedSync(true)
                })
            })
        }
        receiver.applyAttributesFinish()
    })
}

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
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, nullptr, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { Deserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./../CallbackTransformer"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, CustomBuilder, LayoutSafeAreaType, LayoutSafeAreaEdge, BlurStyle, ArkCommonMethodComponent, ArkCommonMethodStyle, UICommonMethod } from "./common"
import { Length, Dimension, ResourceStr, ResourceColor } from "./units"
import { PixelMap } from "./arkui-pixelmap"
import { Resource } from "./resource"
import { SymbolGlyphModifier, TextModifier } from "./arkui-external"
import { SystemBarStyle } from "./arkui-custom"
import { TitleHeight, Color } from "./enums"
import { LengthMetrics } from "./arkui-graphics"
import { Callback_Void } from "./ability_component"
import { NavDestinationContext, NavDestinationMode } from "./nav_destination"
import { UICommonBase, AttributeModifier } from "./../handwritten"
import { NodeAttach, remember } from "@koalaui/runtime"
export class NavPathInfoInternal {
    public static fromPtr(ptr: KPointer): NavPathInfo {
        const obj : NavPathInfo = new NavPathInfo(undefined, undefined, undefined, undefined)
        obj.peer = new Finalizable(ptr, NavPathInfo.getFinalizer())
        return obj
    }
}
export class NavPathInfo implements MaterializedBase {
    peer?: Finalizable | undefined = undefined
    public getPeer(): Finalizable | undefined {
        return this.peer
    }
    get name(): string {
        return this.getName()
    }
    set name(name: string) {
        this.setName(name)
    }
    get param(): object | undefined {
        throw new Error("Not implemented")
    }
    set param(param: object | undefined) {
        const param_NonNull  = (param as object)
        this.setParam(param_NonNull)
    }
    get onPop(): ((parameter: PopInfo) => void) | undefined {
        throw new Error("Not implemented")
    }
    set onPop(onPop: ((parameter: PopInfo) => void) | undefined) {
        const onPop_NonNull  = (onPop as ((parameter: PopInfo) => void))
        this.setOnPop(onPop_NonNull)
    }
    get isEntry(): boolean | undefined {
        return this.getIsEntry()
    }
    set isEntry(isEntry: boolean | undefined) {
        const isEntry_NonNull  = (isEntry as boolean)
        this.setIsEntry(isEntry_NonNull)
    }
    static ctor_navpathinfo(name: string, param: object, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean): KPointer {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        let onPop_type : int32 = RuntimeType.UNDEFINED
        onPop_type = runtimeType(onPop)
        thisSerializer.writeInt8(onPop_type as int32)
        if ((RuntimeType.UNDEFINED) != (onPop_type)) {
            const onPop_value  = onPop!
            thisSerializer.holdAndWriteCallback(onPop_value)
        }
        let isEntry_type : int32 = RuntimeType.UNDEFINED
        isEntry_type = runtimeType(isEntry)
        thisSerializer.writeInt8(isEntry_type as int32)
        if ((RuntimeType.UNDEFINED) != (isEntry_type)) {
            const isEntry_value  = isEntry!
            thisSerializer.writeBoolean(isEntry_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_ctor(name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    constructor(name?: string, param?: object, onPop?: ((parameter: PopInfo) => void), isEntry?: boolean) {
        if (((name) !== (undefined)) || ((param) !== (undefined)) || ((onPop) !== (undefined)) || ((isEntry) !== (undefined)))
        {
            const ctorPtr : KPointer = NavPathInfo.ctor_navpathinfo((name)!, (param)!, onPop, isEntry)
            this.peer = new Finalizable(ctorPtr, NavPathInfo.getFinalizer())
        }
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
    private getParam(): object | undefined {
        return this.getParam_serialize()
    }
    private setParam(param: object): void {
        const param_casted = param as (object)
        this.setParam_serialize(param_casted)
        return
    }
    private getOnPop(): ((parameter: PopInfo) => void) | undefined {
        return this.getOnPop_serialize()
    }
    private setOnPop(onPop: ((parameter: PopInfo) => void)): void {
        const onPop_casted = onPop as (((parameter: PopInfo) => void))
        this.setOnPop_serialize(onPop_casted)
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
    private getName_serialize(): string {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getName(this.peer!.ptr)
        return retval
    }
    private setName_serialize(name: string): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setName(this.peer!.ptr, name)
    }
    private getParam_serialize(): object | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getParam(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setParam_serialize(param: object): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        ArkUIGeneratedNativeModule._NavPathInfo_setParam(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getOnPop_serialize(): ((parameter: PopInfo) => void) | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getOnPop(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setOnPop_serialize(onPop: ((parameter: PopInfo) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(onPop)
        ArkUIGeneratedNativeModule._NavPathInfo_setOnPop(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsEntry_serialize(): boolean | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathInfo_getIsEntry(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private setIsEntry_serialize(isEntry: boolean): void {
        ArkUIGeneratedNativeModule._NavPathInfo_setIsEntry(this.peer!.ptr, isEntry ? 1 : 0)
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
    public pushPath(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            this.pushPath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this.pushPath1_serialize(info_casted, options_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushDestination(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): Promise<void> {
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
    public pushPathByName(name: string, param: object | Object, onPop?: boolean | undefined | ((parameter: PopInfo) => void), animated?: boolean): void {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BIGINT == param_type) || (RuntimeType.BOOLEAN == param_type) || (RuntimeType.FUNCTION == param_type) || (RuntimeType.MATERIALIZED == param_type) || (RuntimeType.NUMBER == param_type) || (RuntimeType.OBJECT == param_type) || (RuntimeType.STRING == param_type) || (RuntimeType.SYMBOL == param_type)) && ((RuntimeType.BOOLEAN == onPop_type) || (RuntimeType.UNDEFINED == onPop_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const param_casted = param as (object)
            const animated_casted = onPop as (boolean | undefined)
            this.pushPathByName0_serialize(name_casted, param_casted, animated_casted)
            return
        }
        if (((RuntimeType.BIGINT == param_type) || (RuntimeType.BOOLEAN == param_type) || (RuntimeType.FUNCTION == param_type) || (RuntimeType.MATERIALIZED == param_type) || (RuntimeType.NUMBER == param_type) || (RuntimeType.OBJECT == param_type) || (RuntimeType.STRING == param_type) || (RuntimeType.SYMBOL == param_type)) && (RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((parameter: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            this.pushPathByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public pushDestinationByName(name: string, param: Object, onPop?: boolean | undefined | ((parameter: PopInfo) => void), animated?: boolean): Promise<void> {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == onPop_type) || (RuntimeType.UNDEFINED == onPop_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const animated_casted = onPop as (boolean | undefined)
            return this.pushDestinationByName0_serialize(name_casted, param_casted, animated_casted)
        }
        if ((RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((parameter: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            return this.pushDestinationByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public replacePath(info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const info_type = runtimeType(info)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const animated_casted = animated as (boolean | undefined)
            this.replacePath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this.replacePath1_serialize(info_casted, options_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
    }
    public replaceDestination(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions | undefined)
        return this.replaceDestination_serialize(info_casted, options_casted)
    }
    public replacePathByName(name: string, param: Object, animated?: boolean): void {
        const name_casted = name as (string)
        const param_casted = param as (Object)
        const animated_casted = animated as (boolean | undefined)
        this.replacePathByName_serialize(name_casted, param_casted, animated_casted)
        return
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
    public pop(result?: boolean | undefined | Object, animated?: boolean): NavPathInfo | undefined {
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const animated_casted = result as (boolean | undefined)
            return this.pop0_serialize(animated_casted)
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            return this.pop1_serialize(result_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public popToName(name: string, result?: boolean | undefined | Object, animated?: boolean): number {
        const name_type = runtimeType(name)
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const animated_casted = result as (boolean | undefined)
            return this.popToName0_serialize(name_casted, animated_casted)
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            return this.popToName1_serialize(name_casted, result_casted, animated_casted)
        }
        throw new Error("Can not select appropriate overload")
    }
    public popToIndex(index: number, result?: boolean | undefined | Object, animated?: boolean): void {
        const index_type = runtimeType(index)
        const result_type = runtimeType(result)
        const animated_type = runtimeType(animated)
        if (((RuntimeType.BOOLEAN == result_type) || (RuntimeType.UNDEFINED == result_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const index_casted = index as (number)
            const animated_casted = result as (boolean | undefined)
            this.popToIndex0_serialize(index_casted, animated_casted)
            return
        }
        if (((RuntimeType.BIGINT == result_type) || (RuntimeType.BOOLEAN == result_type) || (RuntimeType.FUNCTION == result_type) || (RuntimeType.MATERIALIZED == result_type) || (RuntimeType.NUMBER == result_type) || (RuntimeType.OBJECT == result_type) || (RuntimeType.STRING == result_type) || (RuntimeType.SYMBOL == result_type)) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const index_casted = index as (number)
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            this.popToIndex1_serialize(index_casted, result_casted, animated_casted)
            return
        }
        throw new Error("Can not select appropriate overload")
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
    public getParamByIndex(index: number): object | undefined {
        const index_casted = index as (number)
        return this.getParamByIndex_serialize(index_casted)
    }
    public getParamByName(name: string): Array<object> {
        const name_casted = name as (string)
        return this.getParamByName_serialize(name_casted)
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
    private pushPath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    private pushPathByName0_serialize(name: string, param: object, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName0(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPathByName1_serialize(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): void {
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
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName1(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    private replacePath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private replacePath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let options_type : int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type as int32)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value  = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    private replacePathByName_serialize(name: string, param: Object, animated?: boolean): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(param)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePathByName(this.peer!.ptr, name, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
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
    private pop0_serialize(animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : Serializer = Serializer.hold()
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop0(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    private pop1_serialize(result: Object, animated?: boolean): NavPathInfo | undefined {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteObject(result)
        let animated_type : int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type as int32)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value  = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_pop1(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
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
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getAllPathName(this.peer!.ptr)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private getParamByIndex_serialize(index: number): object | undefined {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByIndex(this.peer!.ptr, index)
        throw new Error("Object deserialization is not implemented.")
    }
    private getParamByName_serialize(name: string): Array<object> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getParamByName(this.peer!.ptr, name)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<object> = new Array<object>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readObject() as object)
        }
        const returnResult : Array<object> = buffer
        return returnResult
    }
    private getIndexByName_serialize(name: string): Array<number> {
        const retval  = ArkUIGeneratedNativeModule._NavPathStack_getIndexByName(this.peer!.ptr, name)
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
        let retvalDeserializer : Deserializer = new Deserializer(retval, retval.length)
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
    public static create(component?: ComponentBase, flags: int32 = 0): ArkNavigationPeer {
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
    navBarWidthAttribute(value: Length): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navBarPositionAttribute(value: NavBarPosition): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarPosition(this.peer.ptr, TypeChecker.NavBarPosition_ToNumeric(value))
    }
    navBarWidthRangeAttribute(value: [ Dimension, Dimension ]): void {
        const thisSerializer : Serializer = Serializer.hold()
        const value_0  = value[0]
        let value_0_type : int32 = RuntimeType.UNDEFINED
        value_0_type = runtimeType(value_0)
        if (RuntimeType.STRING == value_0_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0_0  = value_0 as string
            thisSerializer.writeString(value_0_0)
        }
        else if (RuntimeType.NUMBER == value_0_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_0_1  = value_0 as number
            thisSerializer.writeNumber(value_0_1)
        }
        else if (RuntimeType.OBJECT == value_0_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_0_2  = value_0 as Resource
            thisSerializer.writeResource(value_0_2)
        }
        const value_1  = value[1]
        let value_1_type : int32 = RuntimeType.UNDEFINED
        value_1_type = runtimeType(value_1)
        if (RuntimeType.STRING == value_1_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_1_0  = value_1 as string
            thisSerializer.writeString(value_1_0)
        }
        else if (RuntimeType.NUMBER == value_1_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1_1  = value_1 as number
            thisSerializer.writeNumber(value_1_1)
        }
        else if (RuntimeType.OBJECT == value_1_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_1_2  = value_1 as Resource
            thisSerializer.writeResource(value_1_2)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_navBarWidthRange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    minContentWidthAttribute(value: Dimension): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (RuntimeType.NUMBER == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as number
            thisSerializer.writeNumber(value_1)
        }
        else if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_minContentWidth(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    modeAttribute(value: NavigationMode): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_mode(this.peer.ptr, TypeChecker.NavigationMode_ToNumeric(value))
    }
    backButtonIconAttribute(value: string | PixelMap | Resource | SymbolGlyphModifier): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.STRING == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as string
            thisSerializer.writeString(value_0)
        }
        else if (TypeChecker.isPixelMap(value, false, false)) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as PixelMap
            thisSerializer.writePixelMap(value_1)
        }
        else if (TypeChecker.isResource(value, false, false, false, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as Resource
            thisSerializer.writeResource(value_2)
        }
        else if (TypeChecker.isSymbolGlyphModifier(value)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as SymbolGlyphModifier
            thisSerializer.writeSymbolGlyphModifier(value_3)
        }
        ArkUIGeneratedNativeModule._NavigationAttribute_backButtonIcon(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideNavBarAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideNavBar(this.peer.ptr, value ? 1 : 0)
    }
    subTitleAttribute(value: string): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_subTitle(this.peer.ptr, value)
    }
    hideTitleBar0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar0(this.peer.ptr, value ? 1 : 0)
    }
    hideTitleBar1Attribute(hide: boolean, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideTitleBar1(this.peer.ptr, hide ? 1 : 0, animated ? 1 : 0)
    }
    hideBackButtonAttribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideBackButton(this.peer.ptr, value ? 1 : 0)
    }
    titleModeAttribute(value: NavigationTitleMode): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_titleMode(this.peer.ptr, TypeChecker.NavigationTitleMode_ToNumeric(value))
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
        ArkUIGeneratedNativeModule._NavigationAttribute_menus(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    toolBarAttribute(value: CustomBuilder): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value))
        ArkUIGeneratedNativeModule._NavigationAttribute_toolBar(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    hideToolBar0Attribute(value: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar0(this.peer.ptr, value ? 1 : 0)
    }
    hideToolBar1Attribute(hide: boolean, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavigationAttribute_hideToolBar1(this.peer.ptr, hide ? 1 : 0, animated ? 1 : 0)
    }
    onTitleModeChangeAttribute(value: ((titleMode: NavigationTitleMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavigationAttribute_onTitleModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavBarStateChangeAttribute(value: ((isVisible: boolean) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavBarStateChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    onNavigationModeChangeAttribute(value: ((mode: NavigationMode) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavigationAttribute_onNavigationModeChange(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    navDestinationAttribute(value: ((name: string,param: object) => void)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
        ArkUIGeneratedNativeModule._NavigationAttribute_navDestination(this.peer.ptr, thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    customNavContentTransitionAttribute(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): void {
        const thisSerializer : Serializer = Serializer.hold()
        thisSerializer.holdAndWriteCallback(value)
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
    titleAttribute(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): void {
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
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
        }
        else if (TypeChecker.isNavigationCommonTitle(value, false, false)) {
            thisSerializer.writeInt8(2 as int32)
            const value_2  = value as NavigationCommonTitle
            thisSerializer.writeNavigationCommonTitle(value_2)
        }
        else if (TypeChecker.isNavigationCustomTitle(value, false, false)) {
            thisSerializer.writeInt8(3 as int32)
            const value_3  = value as NavigationCustomTitle
            thisSerializer.writeNavigationCustomTitle(value_3)
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
    toolbarConfigurationAttribute(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): void {
        const thisSerializer : Serializer = Serializer.hold()
        let value_type : int32 = RuntimeType.UNDEFINED
        value_type = runtimeType(value)
        if (RuntimeType.OBJECT == value_type) {
            thisSerializer.writeInt8(0 as int32)
            const value_0  = value as Array<ToolbarItem>
            thisSerializer.writeInt32(value_0.length as int32)
            for (let i = 0; i < value_0.length; i++) {
                const value_0_element : ToolbarItem = value_0[i]
                thisSerializer.writeToolbarItem(value_0_element)
            }
        }
        else if (RuntimeType.FUNCTION == value_type) {
            thisSerializer.writeInt8(1 as int32)
            const value_1  = value as CustomBuilder
            thisSerializer.holdAndWriteCallback(CallbackTransformer.transformFromCustomBuilder(value_1))
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
    barStyle?: BarStyle;
}
export type Tuple_Dimension_Dimension = [
    Dimension,
    Dimension
]
export type Callback_NavigationTitleMode_Void = (titleMode: NavigationTitleMode) => void;
export type Callback_Boolean_Void = (isVisible: boolean) => void;
export type Callback_NavigationMode_Void = (mode: NavigationMode) => void;
export type Callback_String_Unknown_Void = (name: string, param: object) => void;
export type Type_NavigationAttribute_customNavContentTransition_delegate = (from: NavContentInfo, to: NavContentInfo, operation: NavigationOperation) => NavigationAnimatedTransition | undefined;
export interface NavigationAttribute extends CommonMethod {
    navBarWidth(value: Length): this
    navBarPosition(value: NavBarPosition): this
    navBarWidthRange(value: [ Dimension, Dimension ]): this
    minContentWidth(value: Dimension): this
    mode(value: NavigationMode): this
    backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier): this
    hideNavBar(value: boolean): this
    subTitle(value: string): this
    hideTitleBar(hide: boolean, animated?: boolean): this
    hideBackButton(value: boolean): this
    titleMode(value: NavigationTitleMode): this
    menus(value: Array<NavigationMenuItem> | CustomBuilder): this
    toolBar(value: CustomBuilder): this
    hideToolBar(hide: boolean, animated?: boolean): this
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void)): this
    onNavBarStateChange(value: ((isVisible: boolean) => void)): this
    onNavigationModeChange(value: ((mode: NavigationMode) => void)): this
    navDestination(value: ((name: string,param: object) => void)): this
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): this
    systemBarStyle(value: SystemBarStyle | undefined): this
    recoverable(value: boolean | undefined): this
    enableDragBar(value: boolean | undefined): this
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): this
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export interface UINavigationAttribute extends UICommonMethod {
    /** @memo */
    navBarWidth(value: Length): this
    /** @memo */
    navBarPosition(value: NavBarPosition): this
    /** @memo */
    navBarWidthRange(value: [ Dimension, Dimension ]): this
    /** @memo */
    minContentWidth(value: Dimension): this
    /** @memo */
    mode(value: NavigationMode): this
    /** @memo */
    backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier): this
    /** @memo */
    hideNavBar(value: boolean): this
    /** @memo */
    subTitle(value: string): this
    /** @memo */
    hideTitleBar(hide: boolean, animated?: boolean): this
    /** @memo */
    hideBackButton(value: boolean): this
    /** @memo */
    titleMode(value: NavigationTitleMode): this
    /** @memo */
    menus(value: Array<NavigationMenuItem> | CustomBuilder): this
    /** @memo */
    toolBar(value: CustomBuilder): this
    /** @memo */
    hideToolBar(hide: boolean, animated?: boolean): this
    /** @memo */
    onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void)): this
    /** @memo */
    onNavBarStateChange(value: ((isVisible: boolean) => void)): this
    /** @memo */
    onNavigationModeChange(value: ((mode: NavigationMode) => void)): this
    /** @memo */
    navDestination(value: ((name: string,param: object) => void)): this
    /** @memo */
    customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): this
    /** @memo */
    systemBarStyle(value: SystemBarStyle | undefined): this
    /** @memo */
    recoverable(value: boolean | undefined): this
    /** @memo */
    enableDragBar(value: boolean | undefined): this
    /** @memo */
    title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): this
    /** @memo */
    toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this
    /** @memo */
    ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this
    /** @memo */
    attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this
}
export class ArkNavigationStyle extends ArkCommonMethodStyle implements NavigationAttribute {
    navBarWidth_value?: Length
    navBarPosition_value?: NavBarPosition
    navBarWidthRange_value?: [ Dimension, Dimension ]
    minContentWidth_value?: Dimension
    mode_value?: NavigationMode
    backButtonIcon_value?: string | PixelMap | Resource | SymbolGlyphModifier
    hideNavBar_value?: boolean
    subTitle_value?: string
    hideTitleBar_value?: boolean
    hideBackButton_value?: boolean
    titleMode_value?: NavigationTitleMode
    menus_value?: Array<NavigationMenuItem> | CustomBuilder
    toolBar_value?: CustomBuilder
    hideToolBar_value?: boolean
    onTitleModeChange_value?: ((titleMode: NavigationTitleMode) => void)
    onNavBarStateChange_value?: ((isVisible: boolean) => void)
    onNavigationModeChange_value?: ((mode: NavigationMode) => void)
    navDestination_value?: ((name: string,param: object) => void)
    customNavContentTransition_value?: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)
    systemBarStyle_value?: SystemBarStyle | undefined
    recoverable_value?: boolean | undefined
    enableDragBar_value?: boolean | undefined
    public navBarWidth(value: Length): this {
        return this
    }
    public navBarPosition(value: NavBarPosition): this {
        return this
    }
    public navBarWidthRange(value: [ Dimension, Dimension ]): this {
        return this
    }
    public minContentWidth(value: Dimension): this {
        return this
    }
    public mode(value: NavigationMode): this {
        return this
    }
    public backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier): this {
        return this
    }
    public hideNavBar(value: boolean): this {
        return this
    }
    public subTitle(value: string): this {
        return this
    }
    public hideTitleBar(hide: boolean, animated?: boolean): this {
        return this
    }
    public hideBackButton(value: boolean): this {
        return this
    }
    public titleMode(value: NavigationTitleMode): this {
        return this
    }
    public menus(value: Array<NavigationMenuItem> | CustomBuilder): this {
        return this
    }
    public toolBar(value: CustomBuilder): this {
        return this
    }
    public hideToolBar(hide: boolean, animated?: boolean): this {
        return this
    }
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void)): this {
        return this
    }
    public onNavBarStateChange(value: ((isVisible: boolean) => void)): this {
        return this
    }
    public onNavigationModeChange(value: ((mode: NavigationMode) => void)): this {
        return this
    }
    public navDestination(value: ((name: string,param: object) => void)): this {
        return this
    }
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): this {
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
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): this {
        return this
    }
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        return this
    }
    public ignoreLayoutSafeArea(types?: Array<LayoutSafeAreaType>, edges?: Array<LayoutSafeAreaEdge>): this {
        return this
    }
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
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
/** @memo:stable */
export class ArkNavigationComponent extends ArkCommonMethodComponent implements UINavigationAttribute {
    getPeer(): ArkNavigationPeer {
        return (this.peer as ArkNavigationPeer)
    }
    /** @memo */
    public setNavigationOptions(pathInfos?: NavPathStack): this {
        if (this.checkPriority("setNavigationOptions")) {
            const pathInfos_type = runtimeType(pathInfos)
            this.getPeer()?.setNavigationOptions0Attribute()
            return this
        }
        return this
    }
    /** @memo */
    public navBarWidth(value: Length): this {
        if (this.checkPriority("navBarWidth")) {
            const value_casted = value as (Length)
            this.getPeer()?.navBarWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public navBarPosition(value: NavBarPosition): this {
        if (this.checkPriority("navBarPosition")) {
            const value_casted = value as (NavBarPosition)
            this.getPeer()?.navBarPositionAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public navBarWidthRange(value: [ Dimension, Dimension ]): this {
        if (this.checkPriority("navBarWidthRange")) {
            const value_casted = value as ([ Dimension, Dimension ])
            this.getPeer()?.navBarWidthRangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public minContentWidth(value: Dimension): this {
        if (this.checkPriority("minContentWidth")) {
            const value_casted = value as (Dimension)
            this.getPeer()?.minContentWidthAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public mode(value: NavigationMode): this {
        if (this.checkPriority("mode")) {
            const value_casted = value as (NavigationMode)
            this.getPeer()?.modeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public backButtonIcon(value: string | PixelMap | Resource | SymbolGlyphModifier): this {
        if (this.checkPriority("backButtonIcon")) {
            const value_casted = value as (string | PixelMap | Resource | SymbolGlyphModifier)
            this.getPeer()?.backButtonIconAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hideNavBar(value: boolean): this {
        if (this.checkPriority("hideNavBar")) {
            const value_casted = value as (boolean)
            this.getPeer()?.hideNavBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public subTitle(value: string): this {
        if (this.checkPriority("subTitle")) {
            const value_casted = value as (string)
            this.getPeer()?.subTitleAttribute(value_casted)
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
    public hideBackButton(value: boolean): this {
        if (this.checkPriority("hideBackButton")) {
            const value_casted = value as (boolean)
            this.getPeer()?.hideBackButtonAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public titleMode(value: NavigationTitleMode): this {
        if (this.checkPriority("titleMode")) {
            const value_casted = value as (NavigationTitleMode)
            this.getPeer()?.titleModeAttribute(value_casted)
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
    public toolBar(value: CustomBuilder): this {
        if (this.checkPriority("toolBar")) {
            const value_casted = value as (CustomBuilder)
            this.getPeer()?.toolBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public hideToolBar(hide: boolean, animated?: boolean): this {
        if (this.checkPriority("hideToolBar")) {
            const hide_type = runtimeType(hide)
            const animated_type = runtimeType(animated)
            const value_casted = hide as (boolean)
            this.getPeer()?.hideToolBar0Attribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onTitleModeChange(value: ((titleMode: NavigationTitleMode) => void)): this {
        if (this.checkPriority("onTitleModeChange")) {
            const value_casted = value as (((titleMode: NavigationTitleMode) => void))
            this.getPeer()?.onTitleModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNavBarStateChange(value: ((isVisible: boolean) => void)): this {
        if (this.checkPriority("onNavBarStateChange")) {
            const value_casted = value as (((isVisible: boolean) => void))
            this.getPeer()?.onNavBarStateChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public onNavigationModeChange(value: ((mode: NavigationMode) => void)): this {
        if (this.checkPriority("onNavigationModeChange")) {
            const value_casted = value as (((mode: NavigationMode) => void))
            this.getPeer()?.onNavigationModeChangeAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public navDestination(value: ((name: string,param: object) => void)): this {
        if (this.checkPriority("navDestination")) {
            const value_casted = value as (((name: string,param: object) => void))
            this.getPeer()?.navDestinationAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public customNavContentTransition(value: ((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined)): this {
        if (this.checkPriority("customNavContentTransition")) {
            const value_casted = value as (((from: NavContentInfo,to: NavContentInfo,operation: NavigationOperation) => NavigationAnimatedTransition | undefined))
            this.getPeer()?.customNavContentTransitionAttribute(value_casted)
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
    public enableDragBar(value: boolean | undefined): this {
        if (this.checkPriority("enableDragBar")) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.enableDragBarAttribute(value_casted)
            return this
        }
        return this
    }
    /** @memo */
    public title(value: ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle, options?: NavigationTitleOptions): this {
        if (this.checkPriority("title")) {
            const value_casted = value as (ResourceStr | CustomBuilder | NavigationCommonTitle | NavigationCustomTitle)
            const options_casted = options as (NavigationTitleOptions | undefined)
            this.getPeer()?.titleAttribute(value_casted, options_casted)
            return this
        }
        return this
    }
    /** @memo */
    public toolbarConfiguration(value: Array<ToolbarItem> | CustomBuilder, options?: NavigationToolbarOptions): this {
        if (this.checkPriority("toolbarConfiguration")) {
            const value_casted = value as (Array<ToolbarItem> | CustomBuilder)
            const options_casted = options as (NavigationToolbarOptions | undefined)
            this.getPeer()?.toolbarConfigurationAttribute(value_casted, options_casted)
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
    public attributeModifier(value: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        console.log("attributeModifier() not implemented")
        return this
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
/** @memo */
export function ArkNavigation(
    /** @memo */
    style: ((attributes: UINavigationAttribute) => void) | undefined,
    /** @memo */
    content_: (() => void) | undefined,
    pathInfos?: NavPathStack,
): void {
    const receiver = remember(() => {
        return new ArkNavigationComponent()
    })
    NodeAttach<ArkNavigationPeer>((): ArkNavigationPeer => ArkNavigationPeer.create(receiver), (_: ArkNavigationPeer) => {
        receiver.setNavigationOptions(pathInfos)
        style?.(receiver)
        content_?.()
        receiver.applyAttributesFinish()
    })
}

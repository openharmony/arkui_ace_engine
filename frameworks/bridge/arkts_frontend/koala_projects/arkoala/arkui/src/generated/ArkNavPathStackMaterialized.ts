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

import { NavPathInfo, NavPathInfoInternal } from "./ArkNavPathInfoMaterialized"
import { NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback } from "./ArkNavigationInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export class NavPathStackInternal {
    public static fromPtr(ptr: KPointer): NavPathStack {
        const obj: NavPathStack = new NavPathStack()
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
        const retval = ArkUIGeneratedNativeModule._NavPathStack_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = NavPathStack.ctor_navpathstack()
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
            this?.pushPath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this?.pushPath1_serialize(info_casted, options_casted)
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
    public pushPathByName(name: string, param: unknown | Object, onPop?: boolean | undefined | ((parameter: PopInfo) => void), animated?: boolean): void {
        const name_type = runtimeType(name)
        const param_type = runtimeType(param)
        const onPop_type = runtimeType(onPop)
        const animated_type = runtimeType(animated)
        if ((RuntimeType.OBJECT == param_type) && ((RuntimeType.BOOLEAN == onPop_type) || (RuntimeType.UNDEFINED == onPop_type)) && (RuntimeType.UNDEFINED == animated_type)) {
            const name_casted = name as (string)
            const param_casted = param as (unknown)
            const animated_casted = onPop as (boolean | undefined)
            this?.pushPathByName0_serialize(name_casted, param_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == param_type) && (RuntimeType.FUNCTION == onPop_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const name_casted = name as (string)
            const param_casted = param as (Object)
            const onPop_casted = onPop as (((parameter: PopInfo) => void))
            const animated_casted = animated as (boolean | undefined)
            this?.pushPathByName1_serialize(name_casted, param_casted, onPop_casted, animated_casted)
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
            this?.replacePath0_serialize(info_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == animated_type) || (RuntimeType.UNDEFINED == animated_type)) {
            const info_casted = info as (NavPathInfo)
            const options_casted = animated as (NavigationOptions | undefined)
            this?.replacePath1_serialize(info_casted, options_casted)
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
        this?.replacePathByName_serialize(name_casted, param_casted, animated_casted)
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
        if ((RuntimeType.OBJECT == result_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
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
        if ((RuntimeType.OBJECT == result_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
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
            this?.popToIndex0_serialize(index_casted, animated_casted)
            return
        }
        if ((RuntimeType.OBJECT == result_type) && ((RuntimeType.BOOLEAN == animated_type) || (RuntimeType.UNDEFINED == animated_type))) {
            const index_casted = index as (number)
            const result_casted = result as (Object)
            const animated_casted = animated as (boolean | undefined)
            this?.popToIndex1_serialize(index_casted, result_casted, animated_casted)
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
        this?.moveIndexToTop_serialize(index_casted, animated_casted)
        return
    }
    public clear(animated?: boolean): void {
        const animated_casted = animated as (boolean | undefined)
        this?.clear_serialize(animated_casted)
        return
    }
    public getAllPathName(): Array<string> {
        return this.getAllPathName_serialize()
    }
    public getParamByIndex(index: number): unknown | undefined {
        const index_casted = index as (number)
        return this.getParamByIndex_serialize(index_casted)
    }
    public getParamByName(name: string): Array<unknown> {
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
        this?.disableAnimation_serialize(value_casted)
        return
    }
    public setInterception(interception: NavigationInterception): void {
        const interception_casted = interception as (NavigationInterception)
        this?.setInterception_serialize(interception_casted)
        return
    }
    private pushPath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushDestination0_serialize(info: NavPathInfo, animated?: boolean): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestination1_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestination1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushPathByName0_serialize(name: string, param: unknown, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Any", param)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName0(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushPathByName1_serialize(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", param)
        thisSerializer.holdAndWriteCallback(onPop)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_pushPathByName1(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private pushDestinationByName0_serialize(name: string, param: Object, animated?: boolean): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", param)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName0(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private pushDestinationByName1_serialize(name: string, param: Object, onPop: ((parameter: PopInfo) => void), animated?: boolean): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", param)
        thisSerializer.holdAndWriteCallback(onPop)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_pushDestinationByName1(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private replacePath0_serialize(info: NavPathInfo, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath0(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private replacePath1_serialize(info: NavPathInfo, options?: NavigationOptions): void {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePath1(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private replaceDestination_serialize(info: NavPathInfo, options?: NavigationOptions): Promise<void> {
        const thisSerializer: Serializer = Serializer.hold()
        let options_type: int32 = RuntimeType.UNDEFINED
        options_type = runtimeType(options)
        thisSerializer.writeInt8(options_type)
        if ((RuntimeType.UNDEFINED) != (options_type)) {
            const options_value = options!
            thisSerializer.writeNavigationOptions(options_value)
        }
        const retval = thisSerializer.holdAndWriteCallbackForPromiseVoid()[0]
        ArkUIGeneratedNativeModule._NavPathStack_replaceDestination(this.peer!.ptr, toPeerPtr(info), thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private replacePathByName_serialize(name: string, param: Object, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", param)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_replacePathByName(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private removeByIndexes_serialize(indexes: Array<number>): number {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeInt32(indexes.length)
        for (let i = 0; i < indexes.length; i++) {
            const indexes_element: number = indexes[i]
            thisSerializer.writeNumber(indexes_element)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_removeByIndexes(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private removeByName_serialize(name: string): number {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_removeByName(this.peer!.ptr, name)
        return retval
    }
    private removeByNavDestinationId_serialize(navDestinationId: string): boolean {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_removeByNavDestinationId(this.peer!.ptr, navDestinationId)
        return retval
    }
    private pop0_serialize(animated?: boolean): NavPathInfo | undefined {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_pop0(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    private pop1_serialize(result: Object, animated?: boolean): NavPathInfo | undefined {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", result)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_pop1(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        throw new Error("Object deserialization is not implemented.")
    }
    private popToName0_serialize(name: string, animated?: boolean): number {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_popToName0(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToName1_serialize(name: string, result: Object, animated?: boolean): number {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", result)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_popToName1(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private popToIndex0_serialize(index: number, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex0(this.peer!.ptr, index, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private popToIndex1_serialize(index: number, result: Object, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeCustomObject("Object", result)
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_popToIndex1(this.peer!.ptr, index, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private moveToTop_serialize(name: string, animated?: boolean): number {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        const retval = ArkUIGeneratedNativeModule._NavPathStack_moveToTop(this.peer!.ptr, name, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
        return retval
    }
    private moveIndexToTop_serialize(index: number, animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_moveIndexToTop(this.peer!.ptr, index, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private clear_serialize(animated?: boolean): void {
        const thisSerializer: Serializer = Serializer.hold()
        let animated_type: int32 = RuntimeType.UNDEFINED
        animated_type = runtimeType(animated)
        thisSerializer.writeInt8(animated_type)
        if ((RuntimeType.UNDEFINED) != (animated_type)) {
            const animated_value = animated!
            thisSerializer.writeBoolean(animated_value)
        }
        ArkUIGeneratedNativeModule._NavPathStack_clear(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getAllPathName_serialize(): Array<string> {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_getAllPathName(this.peer!.ptr)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult: Array<string> = buffer
        return returnResult
    }
    private getParamByIndex_serialize(index: number): unknown | undefined {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_getParamByIndex(this.peer!.ptr, index)
        throw new Error("Object deserialization is not implemented.")
    }
    private getParamByName_serialize(name: string): Array<unknown> {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_getParamByName(this.peer!.ptr, name)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<unknown> = new Array<unknown>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readCustomObject("Any") as Object)
        }
        const returnResult: Array<unknown> = buffer
        return returnResult
    }
    private getIndexByName_serialize(name: string): Array<number> {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_getIndexByName(this.peer!.ptr, name)
        let retvalDeserializer: Deserializer = new Deserializer(retval.buffer, retval.byteLength)
        const buffer_length: int32 = retvalDeserializer.readInt32()
        let buffer: Array<number> = new Array<number>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readNumber() as number)
        }
        const returnResult: Array<number> = buffer
        return returnResult
    }
    private getParent_serialize(): NavPathStack | undefined {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_getParent(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private size_serialize(): number {
        const retval = ArkUIGeneratedNativeModule._NavPathStack_size(this.peer!.ptr)
        return retval
    }
    private disableAnimation_serialize(value: boolean): void {
        ArkUIGeneratedNativeModule._NavPathStack_disableAnimation(this.peer!.ptr, +value)
    }
    private setInterception_serialize(interception: NavigationInterception): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNavigationInterception(interception)
        ArkUIGeneratedNativeModule._NavPathStack_setInterception(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
}

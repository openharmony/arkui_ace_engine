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

import { SerializerBase, DeserializerBase, Finalizable, runtimeType, RuntimeType, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, NativeBuffer, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { NavigationOptions_serializer, NavPathStack, NavPathStackInternal, NavPathInfo, NavPathInfoInternal, NavigationOptions } from "./navigation"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { BuilderLambda } from "@koalaui/builderLambda"
export class NavExtender {
    public static setNavigationOptions(ptr: KPointer, pathStack: NavPathStack): void {
        const ptr_casted = ptr as (KPointer)
        const pathStack_casted = pathStack as (NavPathStack)
        NavExtender.setNavigationOptions_serialize(ptr_casted, pathStack_casted)
        return
    }
    public static setUpdateStackCallback(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const peer_casted = peer as (NavPathStack)
        const callback_casted = callback as (NavExtender_OnUpdateStack)
        NavExtender.setUpdateStackCallback_serialize(peer_casted, callback_casted)
        return
    }
    public static syncStack(peer: NavPathStack): void {
        const peer_casted = peer as (NavPathStack)
        NavExtender.syncStack_serialize(peer_casted)
        return
    }
    public static checkNeedCreate(navigation: KPointer, index: int32): boolean {
        const navigation_casted = navigation as (KPointer)
        const index_casted = index as (int32)
        return NavExtender.checkNeedCreate_serialize(navigation_casted, index_casted)
    }
    public static setNavDestinationNode(peer: NavPathStack, index: int32, node: KPointer): void {
        const peer_casted = peer as (NavPathStack)
        const index_casted = index as (int32)
        const node_casted = node as (KPointer)
        NavExtender.setNavDestinationNode_serialize(peer_casted, index_casted, node_casted)
        return
    }
    public static pushPath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions)
        NavExtender.pushPath_serialize(pathStack_casted, info_casted, options_casted)
        return
    }
    public static replacePath(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const info_casted = info as (NavPathInfo)
        const options_casted = options as (NavigationOptions)
        NavExtender.replacePath_serialize(pathStack_casted, info_casted, options_casted)
        return
    }
    public static pop(pathStack: NavPathStack, animated: boolean): string {
        const pathStack_casted = pathStack as (NavPathStack)
        const animated_casted = animated as (boolean)
        return NavExtender.pop_serialize(pathStack_casted, animated_casted)
    }
    public static setOnPopCallback(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const popCallback_casted = popCallback as (((breakpoints: string) => void))
        NavExtender.setOnPopCallback_serialize(pathStack_casted, popCallback_casted)
        return
    }
    public static getIdByIndex(pathStack: NavPathStack, index: int32): string {
        const pathStack_casted = pathStack as (NavPathStack)
        const index_casted = index as (int32)
        return NavExtender.getIdByIndex_serialize(pathStack_casted, index_casted)
    }
    public static getIdByName(pathStack: NavPathStack, name: string): Array<string> {
        const pathStack_casted = pathStack as (NavPathStack)
        const name_casted = name as (string)
        return NavExtender.getIdByName_serialize(pathStack_casted, name_casted)
    }
    public static popToIndex(pathStack: NavPathStack, index: int32, animated: boolean): void {
        const pathStack_casted = pathStack as (NavPathStack)
        const index_casted = index as (int32)
        const animated_casted = animated as (boolean)
        NavExtender.popToIndex_serialize(pathStack_casted, index_casted, animated_casted)
        return
    }
    public static popToName(pathStack: NavPathStack, name: string, animated: boolean): number {
        const pathStack_casted = pathStack as (NavPathStack)
        const name_casted = name as (string)
        const animated_casted = animated as (boolean)
        return NavExtender.popToName_serialize(pathStack_casted, name_casted, animated_casted)
    }
    private static setNavigationOptions_serialize(ptr: KPointer, pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavigationOptions(ptr, toPeerPtr(pathStack))
    }
    private static setUpdateStackCallback_serialize(peer: NavPathStack, callback: NavExtender_OnUpdateStack): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(callback)
        ArkUIGeneratedNativeModule._NavExtender_setUpdateStackCallback(toPeerPtr(peer), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static syncStack_serialize(peer: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavExtender_syncStack(toPeerPtr(peer))
    }
    private static checkNeedCreate_serialize(navigation: KPointer, index: int32): boolean {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_checkNeedCreate(navigation, index)
        return retval
    }
    private static setNavDestinationNode_serialize(peer: NavPathStack, index: int32, node: KPointer): void {
        ArkUIGeneratedNativeModule._NavExtender_setNavDestinationNode(toPeerPtr(peer), index, node)
    }
    private static pushPath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_pushPath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static replacePath_serialize(pathStack: NavPathStack, info: NavPathInfo, options: NavigationOptions): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        NavigationOptions_serializer.write(thisSerializer, options)
        ArkUIGeneratedNativeModule._NavExtender_replacePath(toPeerPtr(pathStack), toPeerPtr(info), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static pop_serialize(pathStack: NavPathStack, animated: boolean): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_pop(toPeerPtr(pathStack), animated ? 1 : 0)
        return retval
    }
    private static setOnPopCallback_serialize(pathStack: NavPathStack, popCallback: ((breakpoints: string) => void)): void {
        const thisSerializer : SerializerBase = SerializerBase.hold()
        thisSerializer.holdAndWriteCallback(popCallback)
        ArkUIGeneratedNativeModule._NavExtender_setOnPopCallback(toPeerPtr(pathStack), thisSerializer.asBuffer(), thisSerializer.length())
        thisSerializer.release()
    }
    private static getIdByIndex_serialize(pathStack: NavPathStack, index: int32): string {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_getIdByIndex(toPeerPtr(pathStack), index)
        return retval
    }
    private static getIdByName_serialize(pathStack: NavPathStack, name: string): Array<string> {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_getIdByName(toPeerPtr(pathStack), name)
        let retvalDeserializer : DeserializerBase = new DeserializerBase(retval, retval.length)
        const buffer_length : int32 = retvalDeserializer.readInt32()
        let buffer : Array<string> = new Array<string>(buffer_length)
        for (let buffer_i = 0; buffer_i < buffer_length; buffer_i++) {
            buffer[buffer_i] = (retvalDeserializer.readString() as string)
        }
        const returnResult : Array<string> = buffer
        return returnResult
    }
    private static popToIndex_serialize(pathStack: NavPathStack, index: int32, animated: boolean): void {
        ArkUIGeneratedNativeModule._NavExtender_popToIndex(toPeerPtr(pathStack), index, animated ? 1 : 0)
    }
    private static popToName_serialize(pathStack: NavPathStack, name: string, animated: boolean): number {
        const retval  = ArkUIGeneratedNativeModule._NavExtender_popToName(toPeerPtr(pathStack), name, animated ? 1 : 0)
        return retval
    }
}
export type NavExtender_OnUpdateStack = () => void;

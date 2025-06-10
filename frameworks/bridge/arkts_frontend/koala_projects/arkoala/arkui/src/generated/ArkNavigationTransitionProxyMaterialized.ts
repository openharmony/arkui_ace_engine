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

import { NavContentInfo } from "./ArkNavigationInterfaces"
import { NavDestinationMode } from "./ArkNavDestinationInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface NavigationTransitionProxy {
    from: NavContentInfo
    to: NavContentInfo
    isInteractive?: boolean
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
    get isInteractive(): boolean {
        return this.getIsInteractive()
    }
    set isInteractive(isInteractive: boolean) {
        const isInteractive_NonNull = (isInteractive as boolean)
        this.setIsInteractive(isInteractive_NonNull)
    }
    static ctor_navigationtransitionproxy(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NavigationTransitionProxy_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = NavigationTransitionProxyInternal.ctor_navigationtransitionproxy()
        this.peer = new Finalizable(ctorPtr, NavigationTransitionProxyInternal.getFinalizer())
    }
    static getFinalizer(): KPointer {
        return ArkUIGeneratedNativeModule._NavigationTransitionProxy_getFinalizer()
    }
    public finishTransition(): void {
        this?.finishTransition_serialize()
        return
    }
    public cancelTransition(): void {
        this?.cancelTransition_serialize()
        return
    }
    public updateTransition(progress: number): void {
        const progress_casted = progress as (number)
        this?.updateTransition_serialize(progress_casted)
        return
    }
    private setFrom(from: NavContentInfo): void {
        const from_casted = from as (NavContentInfo)
        this?.setFrom_serialize(from_casted)
        return
    }
    private setTo(to: NavContentInfo): void {
        const to_casted = to as (NavContentInfo)
        this?.setTo_serialize(to_casted)
        return
    }
    private getIsInteractive(): boolean {
        return this.getIsInteractive_serialize()
    }
    private setIsInteractive(isInteractive: boolean): void {
        const isInteractive_casted = isInteractive as (boolean)
        this?.setIsInteractive_serialize(isInteractive_casted)
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
    private setFrom_serialize(from: NavContentInfo): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNavContentInfo(from)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setFrom(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private setTo_serialize(to: NavContentInfo): void {
        const thisSerializer: Serializer = Serializer.hold()
        thisSerializer.writeNavContentInfo(to)
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setTo(this.peer!.ptr, thisSerializer.asArray(), thisSerializer.length())
        thisSerializer.release()
    }
    private getIsInteractive_serialize(): boolean {
        const retval = ArkUIGeneratedNativeModule._NavigationTransitionProxy_getIsInteractive(this.peer!.ptr)
        return retval
    }
    private setIsInteractive_serialize(isInteractive: boolean): void {
        ArkUIGeneratedNativeModule._NavigationTransitionProxy_setIsInteractive(this.peer!.ptr, +isInteractive)
    }
    public static fromPtr(ptr: KPointer): NavigationTransitionProxyInternal {
        const obj: NavigationTransitionProxyInternal = new NavigationTransitionProxyInternal()
        obj.peer = new Finalizable(ptr, NavigationTransitionProxyInternal.getFinalizer())
        return obj
    }
}

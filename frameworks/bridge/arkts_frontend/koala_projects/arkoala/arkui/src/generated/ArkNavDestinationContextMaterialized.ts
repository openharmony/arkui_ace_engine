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
import { NavPathStack, NavPathStackInternal } from "./ArkNavPathStackMaterialized"
import { RouteMapConfig } from "./ArkNavDestinationInterfaces"
import { NavigationOptions, NavigationInterception, PopInfo, LaunchMode, InterceptionShowCallback, InterceptionModeCallback } from "./ArkNavigationInterfaces"
import { Finalizable, runtimeType, RuntimeType, SerializerBase, registerCallback, wrapCallback, toPeerPtr, KPointer, MaterializedBase, isInstanceOf } from "@koalaui/interop"
import { unsafeCast, int32, float32 } from "@koalaui/common"
import { Serializer } from "./peers/Serializer"
import { CallbackKind } from "./peers/CallbackKind"
import { isResource, isPadding } from "./../utils"
import { Deserializer, createDeserializer } from "./peers/Deserializer"
import { CallbackTransformer } from "./peers/CallbackTransformer"
import { ArkUIGeneratedNativeModule } from "./ArkUIGeneratedNativeModule"
export interface NavDestinationContext {
    pathInfo: NavPathInfo
    pathStack: NavPathStack
    navDestinationId?: string
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
    get navDestinationId(): string {
        return this.getNavDestinationId()
    }
    set navDestinationId(navDestinationId: string) {
        const navDestinationId_NonNull = (navDestinationId as string)
        this.setNavDestinationId(navDestinationId_NonNull)
    }
    static ctor_navdestinationcontext(): KPointer {
        const retval = ArkUIGeneratedNativeModule._NavDestinationContext_ctor()
        return retval
    }
     constructor() {
        const ctorPtr: KPointer = NavDestinationContextInternal.ctor_navdestinationcontext()
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
        this?.setPathInfo_serialize(pathInfo_casted)
        return
    }
    private getPathStack(): NavPathStack {
        return this.getPathStack_serialize()
    }
    private setPathStack(pathStack: NavPathStack): void {
        const pathStack_casted = pathStack as (NavPathStack)
        this?.setPathStack_serialize(pathStack_casted)
        return
    }
    private getNavDestinationId(): string {
        return this.getNavDestinationId_serialize()
    }
    private setNavDestinationId(navDestinationId: string): void {
        const navDestinationId_casted = navDestinationId as (string)
        this?.setNavDestinationId_serialize(navDestinationId_casted)
        return
    }
    private getConfigInRouteMap_serialize(): RouteMapConfig | undefined {
        const retval = ArkUIGeneratedNativeModule._NavDestinationContext_getConfigInRouteMap(this.peer!.ptr)
        throw new Error("Object deserialization is not implemented.")
    }
    private getPathInfo_serialize(): NavPathInfo {
        const retval = ArkUIGeneratedNativeModule._NavDestinationContext_getPathInfo(this.peer!.ptr)
        const obj: NavPathInfo = NavPathInfoInternal.fromPtr(retval)
        return obj
    }
    private setPathInfo_serialize(pathInfo: NavPathInfo): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathInfo(this.peer!.ptr, toPeerPtr(pathInfo))
    }
    private getPathStack_serialize(): NavPathStack {
        const retval = ArkUIGeneratedNativeModule._NavDestinationContext_getPathStack(this.peer!.ptr)
        const obj: NavPathStack = NavPathStackInternal.fromPtr(retval)
        return obj
    }
    private setPathStack_serialize(pathStack: NavPathStack): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setPathStack(this.peer!.ptr, toPeerPtr(pathStack))
    }
    private getNavDestinationId_serialize(): string {
        const retval = ArkUIGeneratedNativeModule._NavDestinationContext_getNavDestinationId(this.peer!.ptr)
        return retval
    }
    private setNavDestinationId_serialize(navDestinationId: string): void {
        ArkUIGeneratedNativeModule._NavDestinationContext_setNavDestinationId(this.peer!.ptr, navDestinationId)
    }
    public static fromPtr(ptr: KPointer): NavDestinationContextInternal {
        const obj: NavDestinationContextInternal = new NavDestinationContextInternal()
        obj.peer = new Finalizable(ptr, NavDestinationContextInternal.getFinalizer())
        return obj
    }
}

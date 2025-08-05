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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { NavPathStack_serializer, NavPathStack, NavigationOperation, NavBar } from "./../component/navigation"
import { Resource_serializer, Resource } from "./resource"
import { ResourceStr } from "./../component/units"
import { UIContext, UIContextInternal } from "./ohos.arkui.UIContext"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class uiObserver_DensityInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.DensityInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): uiObserver.DensityInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return uiObserver.DensityInfoInternal.fromPtr(ptr)
    }
}
export class uiObserver_NavigationInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.NavigationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationId  = value.navigationId
        valueSerializer.writeString(valueHolderForNavigationId)
        const valueHolderForPathStack  = value.pathStack
        NavPathStack_serializer.write(valueSerializer, valueHolderForPathStack)
    }
    public static read(buffer: DeserializerBase): uiObserver.NavigationInfo {
        let valueDeserializer : DeserializerBase = buffer
        const navigationIdTmpResult : string = (valueDeserializer.readString() as string)
        const pathStackTmpResult : NavPathStack = (NavPathStack_serializer.read(valueDeserializer) as NavPathStack)
        let value : uiObserver.NavigationInfo = ({navigationId: navigationIdTmpResult, pathStack: pathStackTmpResult} as uiObserver.NavigationInfo)
        return value
    }
}
export class uiObserver_NavDestinationInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.NavDestinationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationId  = value.navigationId
        if (valueHolderForNavigationId instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForNavigationIdForIdx0  = valueHolderForNavigationId as string
            valueSerializer.writeString(valueHolderForNavigationIdForIdx0)
        } else if (valueHolderForNavigationId instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForNavigationIdForIdx1  = valueHolderForNavigationId as Resource
            Resource_serializer.write(valueSerializer, valueHolderForNavigationIdForIdx1)
        }
        const valueHolderForName  = value.name
        if (valueHolderForName instanceof string) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForNameForIdx0  = valueHolderForName as string
            valueSerializer.writeString(valueHolderForNameForIdx0)
        } else if (valueHolderForName instanceof Resource) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForNameForIdx1  = valueHolderForName as Resource
            Resource_serializer.write(valueSerializer, valueHolderForNameForIdx1)
        }
        const valueHolderForState  = value.state
        valueSerializer.writeInt32(TypeChecker.uiObserver_NavDestinationState_ToNumeric(valueHolderForState))
        const valueHolderForIndex  = value.index
        valueSerializer.writeNumber(valueHolderForIndex)
        const valueHolderForParam  = value.param
        if (valueHolderForParam !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForParamTmpValue  = valueHolderForParam!
            valueSerializer.holdAndWriteObject(valueHolderForParamTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForNavDestinationId  = value.navDestinationId
        valueSerializer.writeString(valueHolderForNavDestinationId)
    }
    public static read(buffer: DeserializerBase): uiObserver.NavDestinationInfo {
        let valueDeserializer : DeserializerBase = buffer
        const navigationIdTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let navigationIdTmpBuf : string | Resource | undefined
        if (navigationIdTmpBufUnionSelector == (0).toChar()) {
            navigationIdTmpBuf = (valueDeserializer.readString() as string)
        } else if (navigationIdTmpBufUnionSelector == (1).toChar()) {
            navigationIdTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for navigationIdTmpBuf has to be chosen through deserialisation.")
        }
        const navigationIdTmpResult : ResourceStr = (navigationIdTmpBuf as string | Resource)
        const nameTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let nameTmpBuf : string | Resource | undefined
        if (nameTmpBufUnionSelector == (0).toChar()) {
            nameTmpBuf = (valueDeserializer.readString() as string)
        } else if (nameTmpBufUnionSelector == (1).toChar()) {
            nameTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for nameTmpBuf has to be chosen through deserialisation.")
        }
        const nameTmpResult : ResourceStr = (nameTmpBuf as string | Resource)
        const stateTmpResult : uiObserver.NavDestinationState = TypeChecker.uiObserver_NavDestinationState_FromNumeric(valueDeserializer.readInt32())
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        const paramTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramTmpBuf : Object | undefined
        if ((paramTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramTmpBuf = (valueDeserializer.readObject() as object)
        }
        const paramTmpResult : Object | undefined = paramTmpBuf
        const navDestinationIdTmpResult : string = (valueDeserializer.readString() as string)
        let value : uiObserver.NavDestinationInfo = ({navigationId: navigationIdTmpResult, name: nameTmpResult, state: stateTmpResult, index: indexTmpResult, param: paramTmpResult, navDestinationId: navDestinationIdTmpResult} as uiObserver.NavDestinationInfo)
        return value
    }
}
export class uiObserver_RouterPageInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.RouterPageInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): uiObserver.RouterPageInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return uiObserver.RouterPageInfoInternal.fromPtr(ptr)
    }
}
export class uiObserver_ScrollEventInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.ScrollEventInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForUniqueId  = value.uniqueId
        valueSerializer.writeNumber(valueHolderForUniqueId)
        const valueHolderForScrollEvent  = value.scrollEvent
        valueSerializer.writeInt32(TypeChecker.uiObserver_ScrollEventType_ToNumeric(valueHolderForScrollEvent))
        const valueHolderForOffset  = value.offset
        valueSerializer.writeNumber(valueHolderForOffset)
    }
    public static read(buffer: DeserializerBase): uiObserver.ScrollEventInfo {
        let valueDeserializer : DeserializerBase = buffer
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const uniqueIdTmpResult : number = (valueDeserializer.readNumber() as number)
        const scrollEventTmpResult : uiObserver.ScrollEventType = TypeChecker.uiObserver_ScrollEventType_FromNumeric(valueDeserializer.readInt32())
        const offsetTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : uiObserver.ScrollEventInfo = ({id: idTmpResult, uniqueId: uniqueIdTmpResult, scrollEvent: scrollEventTmpResult, offset: offsetTmpResult} as uiObserver.ScrollEventInfo)
        return value
    }
}
export class uiObserver_TabContentInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.TabContentInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForTabContentId  = value.tabContentId
        valueSerializer.writeString(valueHolderForTabContentId)
        const valueHolderForTabContentUniqueId  = value.tabContentUniqueId
        valueSerializer.writeNumber(valueHolderForTabContentUniqueId)
        const valueHolderForState  = value.state
        valueSerializer.writeInt32(TypeChecker.uiObserver_TabContentState_ToNumeric(valueHolderForState))
        const valueHolderForIndex  = value.index
        valueSerializer.writeNumber(valueHolderForIndex)
        const valueHolderForId  = value.id
        valueSerializer.writeString(valueHolderForId)
        const valueHolderForUniqueId  = value.uniqueId
        valueSerializer.writeNumber(valueHolderForUniqueId)
    }
    public static read(buffer: DeserializerBase): uiObserver.TabContentInfo {
        let valueDeserializer : DeserializerBase = buffer
        const tabContentIdTmpResult : string = (valueDeserializer.readString() as string)
        const tabContentUniqueIdTmpResult : number = (valueDeserializer.readNumber() as number)
        const stateTmpResult : uiObserver.TabContentState = TypeChecker.uiObserver_TabContentState_FromNumeric(valueDeserializer.readInt32())
        const indexTmpResult : number = (valueDeserializer.readNumber() as number)
        const idTmpResult : string = (valueDeserializer.readString() as string)
        const uniqueIdTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : uiObserver.TabContentInfo = ({tabContentId: tabContentIdTmpResult, tabContentUniqueId: tabContentUniqueIdTmpResult, state: stateTmpResult, index: indexTmpResult, id: idTmpResult, uniqueId: uniqueIdTmpResult} as uiObserver.TabContentInfo)
        return value
    }
}
export class uiObserver_NavDestinationSwitchInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.NavDestinationSwitchInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForFrom  = value.from
        if (valueHolderForFrom instanceof uiObserver.NavDestinationInfo) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForFromForIdx0  = valueHolderForFrom as uiObserver.NavDestinationInfo
            uiObserver_NavDestinationInfo_serializer.write(valueSerializer, valueHolderForFromForIdx0)
        } else if (valueHolderForFrom instanceof NavBar) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForFromForIdx1  = valueHolderForFrom as NavBar
            valueSerializer.writeString(valueHolderForFromForIdx1)
        }
        const valueHolderForTo  = value.to
        if (valueHolderForTo instanceof uiObserver.NavDestinationInfo) {
            valueSerializer.writeInt8((0).toChar())
            const valueHolderForToForIdx0  = valueHolderForTo as uiObserver.NavDestinationInfo
            uiObserver_NavDestinationInfo_serializer.write(valueSerializer, valueHolderForToForIdx0)
        } else if (valueHolderForTo instanceof NavBar) {
            valueSerializer.writeInt8((1).toChar())
            const valueHolderForToForIdx1  = valueHolderForTo as NavBar
            valueSerializer.writeString(valueHolderForToForIdx1)
        }
        const valueHolderForOperation  = value.operation
        valueSerializer.writeInt32(TypeChecker.NavigationOperation_ToNumeric(valueHolderForOperation))
    }
    public static read(buffer: DeserializerBase): uiObserver.NavDestinationSwitchInfo {
        let valueDeserializer : DeserializerBase = buffer
        const fromTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let fromTmpBuf : uiObserver.NavDestinationInfo | NavBar | undefined
        if (fromTmpBufUnionSelector == (0).toChar()) {
            fromTmpBuf = uiObserver_NavDestinationInfo_serializer.read(valueDeserializer)
        } else if (fromTmpBufUnionSelector == (1).toChar()) {
            fromTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error("One of the branches for fromTmpBuf has to be chosen through deserialisation.")
        }
        const fromTmpResult : uiObserver.NavDestinationInfo | NavBar = (fromTmpBuf as uiObserver.NavDestinationInfo | NavBar)
        const toTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let toTmpBuf : uiObserver.NavDestinationInfo | NavBar | undefined
        if (toTmpBufUnionSelector == (0).toChar()) {
            toTmpBuf = uiObserver_NavDestinationInfo_serializer.read(valueDeserializer)
        } else if (toTmpBufUnionSelector == (1).toChar()) {
            toTmpBuf = (valueDeserializer.readString() as string)
        } else {
            throw new Error("One of the branches for toTmpBuf has to be chosen through deserialisation.")
        }
        const toTmpResult : uiObserver.NavDestinationInfo | NavBar = (toTmpBuf as uiObserver.NavDestinationInfo | NavBar)
        const operationTmpResult : NavigationOperation = TypeChecker.NavigationOperation_FromNumeric(valueDeserializer.readInt32())
        let value : uiObserver.NavDestinationSwitchInfo = ({from: fromTmpResult, to: toTmpResult, operation: operationTmpResult} as uiObserver.NavDestinationSwitchInfo)
        return value
    }
}
export namespace uiObserver {
    export class DensityInfoInternal {
        public static fromPtr(ptr: KPointer): uiObserver.DensityInfo {
            return new uiObserver.DensityInfo(ptr)
        }
    }
    export class DensityInfo implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        get context(): UIContext {
            return this.getContext()
        }
        set context(context: UIContext) {
            this.setContext(context)
        }
        get density(): number {
            return this.getDensity()
        }
        set density(density: number) {
            this.setDensity(density)
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, DensityInfo.getFinalizer())
        }
        constructor() {
            this(DensityInfo.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_DensityInfo_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._uiObserver_DensityInfo_getFinalizer()
        }
        private getContext(): UIContext {
            return this.getContext_serialize()
        }
        private setContext(context: UIContext): void {
            const context_casted = context as (UIContext)
            this.setContext_serialize(context_casted)
            return
        }
        private getDensity(): number {
            return this.getDensity_serialize()
        }
        private setDensity(density: number): void {
            const density_casted = density as (number)
            this.setDensity_serialize(density_casted)
            return
        }
        private getContext_serialize(): UIContext {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_DensityInfo_getContext(this.peer!.ptr)
            const obj : UIContext = UIContextInternal.fromPtr(retval)
            return obj
        }
        private setContext_serialize(context: UIContext): void {
            ArkUIGeneratedNativeModule._uiObserver_DensityInfo_setContext(this.peer!.ptr, toPeerPtr(context))
        }
        private getDensity_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_DensityInfo_getDensity(this.peer!.ptr)
            return retval
        }
        private setDensity_serialize(density: number): void {
            ArkUIGeneratedNativeModule._uiObserver_DensityInfo_setDensity(this.peer!.ptr, density)
        }
    }
    export class RouterPageInfoInternal {
        public static fromPtr(ptr: KPointer): uiObserver.RouterPageInfo {
            return new uiObserver.RouterPageInfo(ptr)
        }
    }
    export class RouterPageInfo implements MaterializedBase {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        get index(): number {
            return this.getIndex()
        }
        set index(index: number) {
            this.setIndex(index)
        }
        get name(): string {
            return this.getName()
        }
        set name(name: string) {
            this.setName(name)
        }
        get path(): string {
            return this.getPath()
        }
        set path(path: string) {
            this.setPath(path)
        }
        get state(): RouterPageState {
            return this.getState()
        }
        set state(state: RouterPageState) {
            this.setState(state)
        }
        get pageId(): string {
            return this.getPageId()
        }
        set pageId(pageId: string) {
            this.setPageId(pageId)
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, RouterPageInfo.getFinalizer())
        }
        constructor() {
            this(RouterPageInfo.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getFinalizer()
        }
        private getIndex(): number {
            return this.getIndex_serialize()
        }
        private setIndex(index: number): void {
            const index_casted = index as (number)
            this.setIndex_serialize(index_casted)
            return
        }
        private getName(): string {
            return this.getName_serialize()
        }
        private setName(name: string): void {
            const name_casted = name as (string)
            this.setName_serialize(name_casted)
            return
        }
        private getPath(): string {
            return this.getPath_serialize()
        }
        private setPath(path: string): void {
            const path_casted = path as (string)
            this.setPath_serialize(path_casted)
            return
        }
        private getState(): RouterPageState {
            return this.getState_serialize()
        }
        private setState(state: RouterPageState): void {
            const state_casted = state as (RouterPageState)
            this.setState_serialize(state_casted)
            return
        }
        private getPageId(): string {
            return this.getPageId_serialize()
        }
        private setPageId(pageId: string): void {
            const pageId_casted = pageId as (string)
            this.setPageId_serialize(pageId_casted)
            return
        }
        private getIndex_serialize(): number {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getIndex(this.peer!.ptr)
            return retval
        }
        private setIndex_serialize(index: number): void {
            ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_setIndex(this.peer!.ptr, index)
        }
        private getName_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getName(this.peer!.ptr)
            return retval
        }
        private setName_serialize(name: string): void {
            ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_setName(this.peer!.ptr, name)
        }
        private getPath_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getPath(this.peer!.ptr)
            return retval
        }
        private setPath_serialize(path: string): void {
            ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_setPath(this.peer!.ptr, path)
        }
        private getState_serialize(): RouterPageState {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getState(this.peer!.ptr)
            return TypeChecker.uiObserver_RouterPageState_FromNumeric(retval)
        }
        private setState_serialize(state: RouterPageState): void {
            ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_setState(this.peer!.ptr, TypeChecker.uiObserver_RouterPageState_ToNumeric(state))
        }
        private getPageId_serialize(): string {
            const retval  = ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_getPageId(this.peer!.ptr)
            return retval
        }
        private setPageId_serialize(pageId: string): void {
            ArkUIGeneratedNativeModule._uiObserver_RouterPageInfo_setPageId(this.peer!.ptr, pageId)
        }
    }
    export enum NavDestinationState {
        ON_SHOWN = 0,
        ON_HIDDEN = 1,
        ON_APPEAR = 2,
        ON_DISAPPEAR = 3,
        ON_WILL_SHOW = 4,
        ON_WILL_HIDE = 5,
        ON_WILL_APPEAR = 6,
        ON_WILL_DISAPPEAR = 7,
        ON_BACKPRESS = 100
    }
    export enum RouterPageState {
        ABOUT_TO_APPEAR = 0,
        ABOUT_TO_DISAPPEAR = 1,
        ON_PAGE_SHOW = 2,
        ON_PAGE_HIDE = 3,
        ON_BACK_PRESS = 4
    }
    export enum ScrollEventType {
        SCROLL_START = 0,
        SCROLL_STOP = 1
    }
    export enum TabContentState {
        ON_SHOW = 0,
        ON_HIDE = 1
    }
    export interface NavDestinationInfo {
        navigationId: ResourceStr;
        name: ResourceStr;
        state: uiObserver.NavDestinationState;
        index: number;
        param?: Object;
        navDestinationId: string;
    }
    export interface NavigationInfo {
        navigationId: string;
        pathStack: NavPathStack;
    }
    export interface ScrollEventInfo {
        id: string;
        uniqueId: number;
        scrollEvent: uiObserver.ScrollEventType;
        offset: number;
    }
    export interface TabContentInfo {
        tabContentId: string;
        tabContentUniqueId: number;
        state: uiObserver.TabContentState;
        index: number;
        id: string;
        uniqueId: number;
    }
    export interface ObserverOptions {
        id: string;
    }
    export interface NavDestinationSwitchInfo {
        from: uiObserver.NavDestinationInfo | NavBar;
        to: uiObserver.NavDestinationInfo | NavBar;
        operation: NavigationOperation;
    }
    export interface NavDestinationSwitchObserverOptions {
        navigationId: ResourceStr;
    }
}

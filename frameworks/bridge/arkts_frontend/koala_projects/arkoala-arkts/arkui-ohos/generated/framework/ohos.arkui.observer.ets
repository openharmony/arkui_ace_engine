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

import { NavPathStack_serializer, NavPathStack } from "./../component/navigation"
import { default as uiObserver } from "@ohos.arkui.observer"
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer } from "./resource"
import { ResourceStr } from "./../component/units"
import { Resource } from "global.resource"
import { NavDestinationMode } from "./../component/navDestination"
import { extractors } from "#handwritten"
export class uiObserver_NavigationInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.NavigationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationId  = value.navigationId
        valueSerializer.writeString(valueHolderForNavigationId)
        const valueHolderForPathStack  = value.pathStack
        NavPathStack_serializer.write(valueSerializer, valueHolderForPathStack)
        const valueHolderForUniqueId  = value.uniqueId
        if (valueHolderForUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUniqueIdTmpValue  = valueHolderForUniqueId!
            valueSerializer.writeInt32(valueHolderForUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): uiObserver.NavigationInfo {
        let valueDeserializer : DeserializerBase = buffer
        const navigationIdTmpResult : string = (valueDeserializer.readString() as string)
        const pathStackTmpResult : NavPathStack = (NavPathStack_serializer.read(valueDeserializer) as NavPathStack)
        const uniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uniqueIdTmpBuf : int32 | undefined = undefined
        if ((uniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            uniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const uniqueIdTmpResult : int32 | undefined = uniqueIdTmpBuf
        let value : uiObserver.NavigationInfo = ({navigationId: navigationIdTmpResult, pathStack: pathStackTmpResult, uniqueId: uniqueIdTmpResult} as uiObserver.NavigationInfo)
        return value
    }
}
export class uiObserver_NavDestinationInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.NavDestinationInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForNavigationId  = value.navigationId
        if (valueHolderForNavigationId instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForNavigationIdForIdx0  = valueHolderForNavigationId as string
            valueSerializer.writeString(valueHolderForNavigationIdForIdx0)
        } else if (valueHolderForNavigationId instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForNavigationIdForIdx1  = valueHolderForNavigationId as Resource
            Resource_serializer.write(valueSerializer, valueHolderForNavigationIdForIdx1)
        }
        const valueHolderForName  = value.name
        if (valueHolderForName instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForNameForIdx0  = valueHolderForName as string
            valueSerializer.writeString(valueHolderForNameForIdx0)
        } else if (valueHolderForName instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForNameForIdx1  = valueHolderForName as Resource
            Resource_serializer.write(valueSerializer, valueHolderForNameForIdx1)
        }
        const valueHolderForState  = value.state
        valueSerializer.writeInt32(valueHolderForState.valueOf())
        const valueHolderForIndex  = value.index
        valueSerializer.writeInt32(valueHolderForIndex)
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
        const valueHolderForUniqueId  = value.uniqueId
        if (valueHolderForUniqueId !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUniqueIdTmpValue  = valueHolderForUniqueId!
            valueSerializer.writeInt32(valueHolderForUniqueIdTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForMode  = value.mode
        if (valueHolderForMode !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForModeTmpValue  = (valueHolderForMode as NavDestinationMode)
            valueSerializer.writeInt32(valueHolderForModeTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
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
        const stateTmpResult : uiObserver.NavDestinationState = uiObserver.NavDestinationState.fromValue(valueDeserializer.readInt32())
        const indexTmpResult : int32 = valueDeserializer.readInt32()
        const paramTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let paramTmpBuf : Object | undefined = undefined
        if ((paramTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            paramTmpBuf = (valueDeserializer.readObject() as object)
        }
        const paramTmpResult : Object | undefined = paramTmpBuf
        const navDestinationIdTmpResult : string = (valueDeserializer.readString() as string)
        const uniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let uniqueIdTmpBuf : int32 | undefined = undefined
        if ((uniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            uniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const uniqueIdTmpResult : int32 | undefined = uniqueIdTmpBuf
        const modeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let modeTmpBuf : NavDestinationMode | undefined = undefined
        if ((modeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            modeTmpBuf = NavDestinationMode.fromValue(valueDeserializer.readInt32())
        }
        const modeTmpResult : NavDestinationMode | undefined = modeTmpBuf
        let value : uiObserver.NavDestinationInfo = ({navigationId: navigationIdTmpResult, name: nameTmpResult, state: stateTmpResult, index: indexTmpResult, param: paramTmpResult, navDestinationId: navDestinationIdTmpResult, uniqueId: uniqueIdTmpResult, mode: modeTmpResult} as uiObserver.NavDestinationInfo)
        return value
    }
}
export class uiObserver_RouterPageInfo_serializer {
    public static write(buffer: SerializerBase, value: uiObserver.RouterPageInfo): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUiObserverRouterPageInfoPtr(value))
    }
    public static read(buffer: DeserializerBase): uiObserver.RouterPageInfo {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUiObserverRouterPageInfoPtr(ptr)
    }
}

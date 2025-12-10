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

import { NavPathStack_serializer, NavPathStack } from './../component/navigation'
import { default as uiObserver } from '@ohos.arkui.observer'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
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
        const uniqueIdTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let uniqueIdTmpBuf : int32 | undefined = undefined
        if ((uniqueIdTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            uniqueIdTmpBuf = valueDeserializer.readInt32()
        }
        const uniqueIdTmpResult : int32 | undefined = uniqueIdTmpBuf
        let value : uiObserver.NavigationInfo = ({navigationId: navigationIdTmpResult, pathStack: pathStackTmpResult, uniqueId: uniqueIdTmpResult} as uiObserver.NavigationInfo)
        return value
    }
}

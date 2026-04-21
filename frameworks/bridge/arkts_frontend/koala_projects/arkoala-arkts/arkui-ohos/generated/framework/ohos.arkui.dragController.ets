/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { extractors } from '#handwritten'
import { default as dragController } from '@ohos.arkui.dragController'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
export class dragController_SpringLoadingContext_serializer {
    public static write(buffer: SerializerBase, value: dragController.SpringLoadingContext): void {
        let valueSerializer: SerializerBase = buffer
        valueSerializer.writePointer(extractors.toDragControllerSpringLoadingContextPtr(value))
    }
    public static read(buffer: DeserializerBase): dragController.SpringLoadingContext {
        let valueDeserializer: DeserializerBase = buffer
        let ptr: KPointer = valueDeserializer.readPointer()
        return extractors.fromDragControllerSpringLoadingContextPtr(ptr)
    }
}
export class dragController_DragSpringLoadingConfiguration_serializer {
    public static write(buffer: SerializerBase, value: dragController.DragSpringLoadingConfiguration): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForStillTimeLimit = value.stillTimeLimit
        if (valueHolderForStillTimeLimit !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStillTimeLimitTmpValue = valueHolderForStillTimeLimit!
            valueSerializer.writeInt32(valueHolderForStillTimeLimitTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUpdateInterval = value.updateInterval
        if (valueHolderForUpdateInterval !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdateIntervalTmpValue = valueHolderForUpdateInterval!
            valueSerializer.writeInt32(valueHolderForUpdateIntervalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUpdateNotifyCount = value.updateNotifyCount
        if (valueHolderForUpdateNotifyCount !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdateNotifyCountTmpValue = valueHolderForUpdateNotifyCount!
            valueSerializer.writeInt32(valueHolderForUpdateNotifyCountTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForUpdateToFinishInterval = value.updateToFinishInterval
        if (valueHolderForUpdateToFinishInterval !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForUpdateToFinishIntervalTmpValue = valueHolderForUpdateToFinishInterval!
            valueSerializer.writeInt32(valueHolderForUpdateToFinishIntervalTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): dragController.DragSpringLoadingConfiguration {
        let valueDeserializer: DeserializerBase = buffer
        const stillTimeLimitTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let stillTimeLimitTmpBuf: int32 | undefined = undefined
        if ((stillTimeLimitTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            stillTimeLimitTmpBuf = valueDeserializer.readInt32()
        }
        const stillTimeLimitTmpResult: int32 | undefined = stillTimeLimitTmpBuf
        const updateIntervalTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let updateIntervalTmpBuf: int32 | undefined = undefined
        if ((updateIntervalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updateIntervalTmpBuf = valueDeserializer.readInt32()
        }
        const updateIntervalTmpResult: int32 | undefined = updateIntervalTmpBuf
        const updateNotifyCountTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let updateNotifyCountTmpBuf: int32 | undefined = undefined
        if ((updateNotifyCountTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updateNotifyCountTmpBuf = valueDeserializer.readInt32()
        }
        const updateNotifyCountTmpResult: int32 | undefined = updateNotifyCountTmpBuf
        const updateToFinishIntervalTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let updateToFinishIntervalTmpBuf: int32 | undefined = undefined
        if ((updateToFinishIntervalTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            updateToFinishIntervalTmpBuf = valueDeserializer.readInt32()
        }
        const updateToFinishIntervalTmpResult: int32 | undefined = updateToFinishIntervalTmpBuf
        let value: dragController.DragSpringLoadingConfiguration = ({stillTimeLimit: stillTimeLimitTmpResult, updateInterval: updateIntervalTmpResult, updateNotifyCount: updateNotifyCountTmpResult, updateToFinishInterval: updateToFinishIntervalTmpResult} as dragController.DragSpringLoadingConfiguration)
        return value
    }
}

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

import { default as unifiedDataChannel, default as DataProgressListener } from '@ohos.data.unifiedDataChannel'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, resourceFinalizerRegister } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
import { extractors } from '#handwritten'
export class unifiedDataChannel_ProgressInfo_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.ProgressInfo): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForProgress  = value.progress
        valueSerializer.writeInt32(valueHolderForProgress)
        const valueHolderForStatus  = value.status
        valueSerializer.writeInt32(valueHolderForStatus.valueOf())
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.ProgressInfo {
        let valueDeserializer : DeserializerBase = buffer
        const progressTmpResult : int32 = valueDeserializer.readInt32()
        const statusTmpResult : unifiedDataChannel.ListenerStatus = unifiedDataChannel.ListenerStatus.fromValue(valueDeserializer.readInt32())
        let value : unifiedDataChannel.ProgressInfo = ({progress: progressTmpResult, status: statusTmpResult} as unifiedDataChannel.ProgressInfo)
        return value
    }
}
export class unifiedDataChannel_Summary_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.Summary): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUnifiedDataChannelSummaryPtr(value))
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.Summary {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUnifiedDataChannelSummaryPtr(ptr)
    }
}
export class unifiedDataChannel_UnifiedData_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.UnifiedData): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(extractors.toUnifiedDataChannelUnifiedDataPtr(value))
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.UnifiedData {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return extractors.fromUnifiedDataChannelUnifiedDataPtr(ptr)
    }
}
export class unifiedDataChannel_GetDataParams_serializer {
    public static write(buffer: SerializerBase, value: unifiedDataChannel.GetDataParams): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForProgressIndicator  = value.progressIndicator
        valueSerializer.writeInt32(valueHolderForProgressIndicator.valueOf())
        const valueHolderForDataProgressListener  = value.dataProgressListener
        valueSerializer.holdAndWriteCallback(valueHolderForDataProgressListener)
        const valueHolderForDestUri  = value.destUri
        if (valueHolderForDestUri !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForDestUriTmpValue  = valueHolderForDestUri!
            valueSerializer.writeString(valueHolderForDestUriTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForFileConflictOptions  = value.fileConflictOptions
        if (valueHolderForFileConflictOptions !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForFileConflictOptionsTmpValue  = (valueHolderForFileConflictOptions as unifiedDataChannel.FileConflictOptions)
            valueSerializer.writeInt32(valueHolderForFileConflictOptionsTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): unifiedDataChannel.GetDataParams {
        let valueDeserializer : DeserializerBase = buffer
        const progressIndicatorTmpResult : unifiedDataChannel.ProgressIndicator = unifiedDataChannel.ProgressIndicator.fromValue(valueDeserializer.readInt32())
        const dataProgressListenerTmpBufBufResource : CallbackResource = valueDeserializer.readCallbackResource()
        const dataProgressListenerTmpBufBufCall : KPointer = valueDeserializer.readPointer()
        const dataProgressListenerTmpBufBufCallSync : KPointer = valueDeserializer.readPointer()
        const dataProgressListenerTmpBufClosure  = (progressInfo: unifiedDataChannel.ProgressInfo, data?: unifiedDataChannel.UnifiedData | null):void => {
            const dataProgressListenerTmpBufBufArgsSerializer : SerializerBase = SerializerBase.hold();
            dataProgressListenerTmpBufBufArgsSerializer.writeInt32(dataProgressListenerTmpBufBufResource.resourceId);
            dataProgressListenerTmpBufBufArgsSerializer.writePointer(dataProgressListenerTmpBufBufCall);
            dataProgressListenerTmpBufBufArgsSerializer.writePointer(dataProgressListenerTmpBufBufCallSync);
            unifiedDataChannel_ProgressInfo_serializer.write(dataProgressListenerTmpBufBufArgsSerializer, progressInfo);
            if (data !== null) {
                dataProgressListenerTmpBufBufArgsSerializer.writeInt8(RuntimeType.OBJECT);
                const dataTmpValue  = data!;
                unifiedDataChannel_UnifiedData_serializer.write(dataProgressListenerTmpBufBufArgsSerializer, dataTmpValue);
            } else {
                dataProgressListenerTmpBufBufArgsSerializer.writeInt8(RuntimeType.UNDEFINED);
            }
            InteropNativeModule._CallCallbackSync(10, 824958177, dataProgressListenerTmpBufBufArgsSerializer.asBuffer(), dataProgressListenerTmpBufBufArgsSerializer.length());
            dataProgressListenerTmpBufBufArgsSerializer.release();
            return;
        }
        resourceFinalizerRegister(dataProgressListenerTmpBufClosure, dataProgressListenerTmpBufBufResource)
        const dataProgressListenerTmpResult : unifiedDataChannel.DataProgressListener = dataProgressListenerTmpBufClosure
        const destUriTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let destUriTmpBuf : string | undefined = undefined
        if ((destUriTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            destUriTmpBuf = (valueDeserializer.readString() as string)
        }
        const destUriTmpResult : string | undefined = destUriTmpBuf
        const fileConflictOptionsTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let fileConflictOptionsTmpBuf : unifiedDataChannel.FileConflictOptions | undefined = undefined
        if ((fileConflictOptionsTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            fileConflictOptionsTmpBuf = unifiedDataChannel.FileConflictOptions.fromValue(valueDeserializer.readInt32())
        }
        const fileConflictOptionsTmpResult : unifiedDataChannel.FileConflictOptions | undefined = fileConflictOptionsTmpBuf
        let value : unifiedDataChannel.GetDataParams = ({progressIndicator: progressIndicatorTmpResult, dataProgressListener: dataProgressListenerTmpResult, destUri: destUriTmpResult, fileConflictOptions: fileConflictOptionsTmpResult} as unifiedDataChannel.GetDataParams)
        return value
    }
}

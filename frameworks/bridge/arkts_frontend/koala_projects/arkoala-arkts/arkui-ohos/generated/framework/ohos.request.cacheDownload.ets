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

import { default as cacheDownload } from '@ohos.request.cacheDownload'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
export class cacheDownload_NetworkInfo_serializer {
    public static write(buffer: SerializerBase, value: cacheDownload.NetworkInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForDnsServers = value.dnsServers
        valueSerializer.writeInt32((valueHolderForDnsServers.length).toInt())
        for (let valueHolderForDnsServersCounterI = 0; valueHolderForDnsServersCounterI < valueHolderForDnsServers.length; valueHolderForDnsServersCounterI++) {
            const valueHolderForDnsServersTmpElement: string = valueHolderForDnsServers[valueHolderForDnsServersCounterI]
            valueSerializer.writeString(valueHolderForDnsServersTmpElement)
        }
        const valueHolderForIp = value.ip
        if (valueHolderForIp !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForIpTmpValue = valueHolderForIp!
            valueSerializer.writeString(valueHolderForIpTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): cacheDownload.NetworkInfo {
        let valueDeserializer: DeserializerBase = buffer
        const dnsServersTmpBufLength: int32 = valueDeserializer.readInt32()
        let dnsServersTmpBuf: Array<string> = new Array<string>(dnsServersTmpBufLength)
        for (let dnsServersTmpBufBufCounterI = 0; dnsServersTmpBufBufCounterI < dnsServersTmpBufLength; dnsServersTmpBufBufCounterI++) {
            dnsServersTmpBuf[dnsServersTmpBufBufCounterI] = (valueDeserializer.readString() as string)
        }
        const dnsServersTmpResult: Array<string> = dnsServersTmpBuf
        const ipTmpBuf_runtimeType = valueDeserializer.readInt8()!.toInt()
        let ipTmpBuf: string | undefined = undefined
        if ((ipTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            ipTmpBuf = (valueDeserializer.readString() as string)
        }
        const ipTmpResult: string | undefined = ipTmpBuf
        let value: cacheDownload.NetworkInfo = ({dnsServers: dnsServersTmpResult, ip: ipTmpResult} as cacheDownload.NetworkInfo)
        return value
    }
}
export class cacheDownload_PerformanceInfo_serializer {
    public static write(buffer: SerializerBase, value: cacheDownload.PerformanceInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForDnsTime = value.dnsTime
        valueSerializer.writeFloat64(valueHolderForDnsTime)
        const valueHolderForConnectTime = value.connectTime
        valueSerializer.writeFloat64(valueHolderForConnectTime)
        const valueHolderForTlsTime = value.tlsTime
        valueSerializer.writeFloat64(valueHolderForTlsTime)
        const valueHolderForFirstSendTime = value.firstSendTime
        valueSerializer.writeFloat64(valueHolderForFirstSendTime)
        const valueHolderForFirstReceiveTime = value.firstReceiveTime
        valueSerializer.writeFloat64(valueHolderForFirstReceiveTime)
        const valueHolderForTotalTime = value.totalTime
        valueSerializer.writeFloat64(valueHolderForTotalTime)
        const valueHolderForRedirectTime = value.redirectTime
        valueSerializer.writeFloat64(valueHolderForRedirectTime)
    }
    public static read(buffer: DeserializerBase): cacheDownload.PerformanceInfo {
        let valueDeserializer: DeserializerBase = buffer
        const dnsTimeTmpResult: double = valueDeserializer.readFloat64()
        const connectTimeTmpResult: double = valueDeserializer.readFloat64()
        const tlsTimeTmpResult: double = valueDeserializer.readFloat64()
        const firstSendTimeTmpResult: double = valueDeserializer.readFloat64()
        const firstReceiveTimeTmpResult: double = valueDeserializer.readFloat64()
        const totalTimeTmpResult: double = valueDeserializer.readFloat64()
        const redirectTimeTmpResult: double = valueDeserializer.readFloat64()
        let value: cacheDownload.PerformanceInfo = ({dnsTime: dnsTimeTmpResult, connectTime: connectTimeTmpResult, tlsTime: tlsTimeTmpResult, firstSendTime: firstSendTimeTmpResult, firstReceiveTime: firstReceiveTimeTmpResult, totalTime: totalTimeTmpResult, redirectTime: redirectTimeTmpResult} as cacheDownload.PerformanceInfo)
        return value
    }
}
export class cacheDownload_ResourceInfo_serializer {
    public static write(buffer: SerializerBase, value: cacheDownload.ResourceInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForSize = value.size
        valueSerializer.writeInt64(valueHolderForSize)
    }
    public static read(buffer: DeserializerBase): cacheDownload.ResourceInfo {
        let valueDeserializer: DeserializerBase = buffer
        const sizeTmpResult: int64 = valueDeserializer.readInt64()
        let value: cacheDownload.ResourceInfo = ({size: sizeTmpResult} as cacheDownload.ResourceInfo)
        return value
    }
}
export class cacheDownload_DownloadInfo_serializer {
    public static write(buffer: SerializerBase, value: cacheDownload.DownloadInfo): void {
        let valueSerializer: SerializerBase = buffer
        const valueHolderForResource = value.resource
        cacheDownload_ResourceInfo_serializer.write(valueSerializer, valueHolderForResource)
        const valueHolderForNetwork = value.network
        cacheDownload_NetworkInfo_serializer.write(valueSerializer, valueHolderForNetwork)
        const valueHolderForPerformance = value.performance
        cacheDownload_PerformanceInfo_serializer.write(valueSerializer, valueHolderForPerformance)
    }
    public static read(buffer: DeserializerBase): cacheDownload.DownloadInfo {
        let valueDeserializer: DeserializerBase = buffer
        const resourceTmpResult: cacheDownload.ResourceInfo = cacheDownload_ResourceInfo_serializer.read(valueDeserializer)
        const networkTmpResult: cacheDownload.NetworkInfo = cacheDownload_NetworkInfo_serializer.read(valueDeserializer)
        const performanceTmpResult: cacheDownload.PerformanceInfo = cacheDownload_PerformanceInfo_serializer.read(valueDeserializer)
        let value: cacheDownload.DownloadInfo = ({resource: resourceTmpResult, network: networkTmpResult, performance: performanceTmpResult} as cacheDownload.DownloadInfo)
        return value
    }
}

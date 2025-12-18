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

import { default as window } from '@ohos.window'
import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr } from '@koalaui/interop'
import { int32, int64, float32, unsafeCast } from '@koalaui/common'
import { CallbackTransformer } from './../CallbackTransformer'
export class window_SystemBarStyle_serializer {
    public static write(buffer: SerializerBase, value: window.SystemBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForStatusBarContentColor  = value.statusBarContentColor
        if (valueHolderForStatusBarContentColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStatusBarContentColorTmpValue  = valueHolderForStatusBarContentColor!
            valueSerializer.writeString(valueHolderForStatusBarContentColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): window.SystemBarStyle {
        let valueDeserializer : DeserializerBase = buffer
        const statusBarContentColorTmpBuf_runtimeType  = valueDeserializer.readInt8()!.toInt()
        let statusBarContentColorTmpBuf : string | undefined = undefined
        if ((statusBarContentColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            statusBarContentColorTmpBuf = (valueDeserializer.readString() as string)
        }
        const statusBarContentColorTmpResult : string | undefined = statusBarContentColorTmpBuf
        let value : window.SystemBarStyle = ({statusBarContentColor: statusBarContentColorTmpResult} as window.SystemBarStyle)
        return value
    }
}

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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, KInt, KBoolean, KStringPtr, wrapCallback } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
export class window_SystemBarStyle_serializer {
    public static write(buffer: SerializerBase, value: window.SystemBarStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_statusBarContentColor  = value.statusBarContentColor
        let value_statusBarContentColor_type : int32 = RuntimeType.UNDEFINED
        value_statusBarContentColor_type = runtimeType(value_statusBarContentColor)
        valueSerializer.writeInt8((value_statusBarContentColor_type).toChar())
        if ((value_statusBarContentColor_type) != (RuntimeType.UNDEFINED)) {
            const value_statusBarContentColor_value  = value_statusBarContentColor!
            valueSerializer.writeString(value_statusBarContentColor_value)
        }
    }
    public static read(buffer: DeserializerBase): window.SystemBarStyle {
        let valueDeserializer : DeserializerBase = buffer
        const statusBarContentColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let statusBarContentColor_buf : string | undefined
        if ((statusBarContentColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            statusBarContentColor_buf = (valueDeserializer.readString() as string)
        }
        const statusBarContentColor_result : string | undefined = statusBarContentColor_buf
        let value : window.SystemBarStyle = ({statusBarContentColor: statusBarContentColor_result} as window.SystemBarStyle)
        return value
    }
}
export namespace window {
    export enum WindowStatusType {
        UNDEFINED = 0,
        FULL_SCREEN = 1,
        MAXIMIZE = 2,
        MINIMIZE = 3,
        FLOATING = 4,
        SPLIT_SCREEN = 5
    }
    export interface SystemBarStyle {
        statusBarContentColor?: string;
    }
}

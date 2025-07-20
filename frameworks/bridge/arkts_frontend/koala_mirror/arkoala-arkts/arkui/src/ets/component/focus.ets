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

import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { LengthMetrics, ColorMetrics, LengthMetrics_serializer, ColorMetrics_serializer } from "./../generated/arkui.Graphics"
import { CallbackKind } from "./../generated/peers/CallbackKind"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
export interface FocusBoxStyle {
    margin?: LengthMetrics;
    strokeColor?: ColorMetrics;
    strokeWidth?: LengthMetrics;
}
export enum FocusPriority {
    AUTO = 0,
    PRIOR = 2000,
    PREVIOUS = 3000
}
export enum KeyProcessingMode {
    FOCUS_NAVIGATION = 0,
    ANCESTOR_EVENT = 1
}
export class FocusBoxStyle_serializer {
    public static write(buffer: SerializerBase, value: FocusBoxStyle): void {
        let valueSerializer : SerializerBase = buffer
        const value_margin  = value.margin
        let value_margin_type : int32 = RuntimeType.UNDEFINED
        value_margin_type = runtimeType(value_margin)
        valueSerializer.writeInt8((value_margin_type).toChar())
        if ((value_margin_type) != (RuntimeType.UNDEFINED)) {
            const value_margin_value  = value_margin!
            LengthMetrics_serializer.write(valueSerializer, value_margin_value)
        }
        const value_strokeColor  = value.strokeColor
        let value_strokeColor_type : int32 = RuntimeType.UNDEFINED
        value_strokeColor_type = runtimeType(value_strokeColor)
        valueSerializer.writeInt8((value_strokeColor_type).toChar())
        if ((value_strokeColor_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeColor_value  = value_strokeColor!
            ColorMetrics_serializer.write(valueSerializer, value_strokeColor_value)
        }
        const value_strokeWidth  = value.strokeWidth
        let value_strokeWidth_type : int32 = RuntimeType.UNDEFINED
        value_strokeWidth_type = runtimeType(value_strokeWidth)
        valueSerializer.writeInt8((value_strokeWidth_type).toChar())
        if ((value_strokeWidth_type) != (RuntimeType.UNDEFINED)) {
            const value_strokeWidth_value  = value_strokeWidth!
            LengthMetrics_serializer.write(valueSerializer, value_strokeWidth_value)
        }
    }
    public static read(buffer: DeserializerBase): FocusBoxStyle {
        let valueDeserializer : DeserializerBase = buffer
        const margin_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let margin_buf : LengthMetrics | undefined
        if ((margin_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            margin_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const margin_result : LengthMetrics | undefined = margin_buf
        const strokeColor_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeColor_buf : ColorMetrics | undefined
        if ((strokeColor_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strokeColor_buf = (ColorMetrics_serializer.read(valueDeserializer) as ColorMetrics)
        }
        const strokeColor_result : ColorMetrics | undefined = strokeColor_buf
        const strokeWidth_buf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidth_buf : LengthMetrics | undefined
        if ((strokeWidth_buf_runtimeType) != (RuntimeType.UNDEFINED))
        {
            strokeWidth_buf = (LengthMetrics_serializer.read(valueDeserializer) as LengthMetrics)
        }
        const strokeWidth_result : LengthMetrics | undefined = strokeWidth_buf
        let value : FocusBoxStyle = ({margin: margin_result, strokeColor: strokeColor_result, strokeWidth: strokeWidth_result} as FocusBoxStyle)
        return value
    }
}

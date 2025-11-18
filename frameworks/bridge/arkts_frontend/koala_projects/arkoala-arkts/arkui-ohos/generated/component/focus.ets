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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KSerializerBuffer, KUint8ArrayPtr } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder, Builder } from "@koalaui/builderLambda"
import { LengthMetrics, ColorMetrics } from "arkui.Graphics"
import { LengthMetrics_serializer, ColorMetrics_serializer } from "./../Graphics"
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
        const valueHolderForMargin  = value.margin
        if (valueHolderForMargin !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForMarginTmpValue  = valueHolderForMargin!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForMarginTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeColor  = value.strokeColor
        if (valueHolderForStrokeColor !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeColorTmpValue  = valueHolderForStrokeColor!
            ColorMetrics_serializer.write(valueSerializer, valueHolderForStrokeColorTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForStrokeWidth  = value.strokeWidth
        if (valueHolderForStrokeWidth !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForStrokeWidthTmpValue  = valueHolderForStrokeWidth!
            LengthMetrics_serializer.write(valueSerializer, valueHolderForStrokeWidthTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): FocusBoxStyle {
        let valueDeserializer : DeserializerBase = buffer
        const marginTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let marginTmpBuf : LengthMetrics | undefined = undefined
        if ((marginTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            marginTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const marginTmpResult : LengthMetrics | undefined = marginTmpBuf
        const strokeColorTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeColorTmpBuf : ColorMetrics | undefined = undefined
        if ((strokeColorTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeColorTmpBuf = ColorMetrics_serializer.read(valueDeserializer)
        }
        const strokeColorTmpResult : ColorMetrics | undefined = strokeColorTmpBuf
        const strokeWidthTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let strokeWidthTmpBuf : LengthMetrics | undefined = undefined
        if ((strokeWidthTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            strokeWidthTmpBuf = LengthMetrics_serializer.read(valueDeserializer)
        }
        const strokeWidthTmpResult : LengthMetrics | undefined = strokeWidthTmpBuf
        let value : FocusBoxStyle = ({margin: marginTmpResult, strokeColor: strokeColorTmpResult, strokeWidth: strokeWidthTmpResult} as FocusBoxStyle)
        return value
    }
}

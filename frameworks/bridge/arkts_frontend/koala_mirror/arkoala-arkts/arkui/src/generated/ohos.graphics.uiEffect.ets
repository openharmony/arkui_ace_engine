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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, registerCallback, wrapCallback, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
import { CallbackKind } from "./peers/CallbackKind"
import { TypeChecker, ArkUIGeneratedNativeModule } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { GlobalScope } from "./GlobalScope"
export class uiEffect_Filter_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.Filter): void {
    }
    public static read(buffer: DeserializerBase): uiEffect.Filter {
        let value : uiEffect.Filter = ({} as uiEffect.Filter)
        return value
    }
}
export class uiEffect_VisualEffect_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.VisualEffect): void {
        let valueSerializer : SerializerBase = buffer
        valueSerializer.writePointer(toPeerPtr(value))
    }
    public static read(buffer: DeserializerBase): uiEffect.VisualEffect {
        let valueDeserializer : DeserializerBase = buffer
        let ptr : KPointer = valueDeserializer.readPointer()
        return uiEffect.VisualEffectInternal.fromPtr(ptr)
    }
}
export class uiEffect_BrightnessBlender_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.BrightnessBlender): void {
        let valueSerializer : SerializerBase = buffer
        const value_cubicRate  = value.cubicRate
        valueSerializer.writeNumber(value_cubicRate)
        const value_quadraticRate  = value.quadraticRate
        valueSerializer.writeNumber(value_quadraticRate)
        const value_linearRate  = value.linearRate
        valueSerializer.writeNumber(value_linearRate)
        const value_degree  = value.degree
        valueSerializer.writeNumber(value_degree)
        const value_saturation  = value.saturation
        valueSerializer.writeNumber(value_saturation)
        const value_positiveCoefficient  = value.positiveCoefficient
        const value_positiveCoefficient_0  = value_positiveCoefficient[0]
        valueSerializer.writeNumber(value_positiveCoefficient_0)
        const value_positiveCoefficient_1  = value_positiveCoefficient[1]
        valueSerializer.writeNumber(value_positiveCoefficient_1)
        const value_positiveCoefficient_2  = value_positiveCoefficient[2]
        valueSerializer.writeNumber(value_positiveCoefficient_2)
        const value_negativeCoefficient  = value.negativeCoefficient
        const value_negativeCoefficient_0  = value_negativeCoefficient[0]
        valueSerializer.writeNumber(value_negativeCoefficient_0)
        const value_negativeCoefficient_1  = value_negativeCoefficient[1]
        valueSerializer.writeNumber(value_negativeCoefficient_1)
        const value_negativeCoefficient_2  = value_negativeCoefficient[2]
        valueSerializer.writeNumber(value_negativeCoefficient_2)
        const value_fraction  = value.fraction
        valueSerializer.writeNumber(value_fraction)
    }
    public static read(buffer: DeserializerBase): uiEffect.BrightnessBlender {
        let valueDeserializer : DeserializerBase = buffer
        const cubicRate_result : number = (valueDeserializer.readNumber() as number)
        const quadraticRate_result : number = (valueDeserializer.readNumber() as number)
        const linearRate_result : number = (valueDeserializer.readNumber() as number)
        const degree_result : number = (valueDeserializer.readNumber() as number)
        const saturation_result : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_result : [ number, number, number ] = ([positiveCoefficient_buf_value0, positiveCoefficient_buf_value1, positiveCoefficient_buf_value2] as [ number, number, number ])
        const negativeCoefficient_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_result : [ number, number, number ] = ([negativeCoefficient_buf_value0, negativeCoefficient_buf_value1, negativeCoefficient_buf_value2] as [ number, number, number ])
        const fraction_result : number = (valueDeserializer.readNumber() as number)
        let value : uiEffect.BrightnessBlender = ({cubicRate: cubicRate_result, quadraticRate: quadraticRate_result, linearRate: linearRate_result, degree: degree_result, saturation: saturation_result, positiveCoefficient: positiveCoefficient_result, negativeCoefficient: negativeCoefficient_result, fraction: fraction_result} as uiEffect.BrightnessBlender)
        return value
    }
}
export class uiEffect_BrightnessBlenderParam_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.BrightnessBlenderParam): void {
        let valueSerializer : SerializerBase = buffer
        const value_cubicRate  = value.cubicRate
        valueSerializer.writeNumber(value_cubicRate)
        const value_quadraticRate  = value.quadraticRate
        valueSerializer.writeNumber(value_quadraticRate)
        const value_linearRate  = value.linearRate
        valueSerializer.writeNumber(value_linearRate)
        const value_degree  = value.degree
        valueSerializer.writeNumber(value_degree)
        const value_saturation  = value.saturation
        valueSerializer.writeNumber(value_saturation)
        const value_positiveCoefficient  = value.positiveCoefficient
        const value_positiveCoefficient_0  = value_positiveCoefficient[0]
        valueSerializer.writeNumber(value_positiveCoefficient_0)
        const value_positiveCoefficient_1  = value_positiveCoefficient[1]
        valueSerializer.writeNumber(value_positiveCoefficient_1)
        const value_positiveCoefficient_2  = value_positiveCoefficient[2]
        valueSerializer.writeNumber(value_positiveCoefficient_2)
        const value_negativeCoefficient  = value.negativeCoefficient
        const value_negativeCoefficient_0  = value_negativeCoefficient[0]
        valueSerializer.writeNumber(value_negativeCoefficient_0)
        const value_negativeCoefficient_1  = value_negativeCoefficient[1]
        valueSerializer.writeNumber(value_negativeCoefficient_1)
        const value_negativeCoefficient_2  = value_negativeCoefficient[2]
        valueSerializer.writeNumber(value_negativeCoefficient_2)
        const value_fraction  = value.fraction
        valueSerializer.writeNumber(value_fraction)
    }
    public static read(buffer: DeserializerBase): uiEffect.BrightnessBlenderParam {
        let valueDeserializer : DeserializerBase = buffer
        const cubicRate_result : number = (valueDeserializer.readNumber() as number)
        const quadraticRate_result : number = (valueDeserializer.readNumber() as number)
        const linearRate_result : number = (valueDeserializer.readNumber() as number)
        const degree_result : number = (valueDeserializer.readNumber() as number)
        const saturation_result : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficient_result : [ number, number, number ] = ([positiveCoefficient_buf_value0, positiveCoefficient_buf_value1, positiveCoefficient_buf_value2] as [ number, number, number ])
        const negativeCoefficient_buf_value0 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_buf_value1 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_buf_value2 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficient_result : [ number, number, number ] = ([negativeCoefficient_buf_value0, negativeCoefficient_buf_value1, negativeCoefficient_buf_value2] as [ number, number, number ])
        const fraction_result : number = (valueDeserializer.readNumber() as number)
        let value : uiEffect.BrightnessBlenderParam = ({cubicRate: cubicRate_result, quadraticRate: quadraticRate_result, linearRate: linearRate_result, degree: degree_result, saturation: saturation_result, positiveCoefficient: positiveCoefficient_result, negativeCoefficient: negativeCoefficient_result, fraction: fraction_result} as uiEffect.BrightnessBlenderParam)
        return value
    }
}
export namespace uiEffect {
    export interface VisualEffect {
        backgroundColorBlender(blender: BrightnessBlender): VisualEffect
    }
    export class VisualEffectInternal implements MaterializedBase,uiEffect.VisualEffect {
        peer?: Finalizable | undefined = undefined
        public getPeer(): Finalizable | undefined {
            return this.peer
        }
        constructor(peerPtr: KPointer) {
            this.peer = new Finalizable(peerPtr, VisualEffectInternal.getFinalizer())
        }
        constructor() {
            this(VisualEffectInternal.construct())
        }
        static construct(): KPointer {
            const retval  = ArkUIGeneratedNativeModule._uiEffect_VisualEffect_construct()
            return retval
        }
        static getFinalizer(): KPointer {
            return ArkUIGeneratedNativeModule._uiEffect_VisualEffect_getFinalizer()
        }
        public static fromPtr(ptr: KPointer): VisualEffectInternal {
            return new VisualEffectInternal(ptr)
        }
        public backgroundColorBlender(blender: BrightnessBlender): VisualEffect {
            const blender_casted = blender as (BrightnessBlender)
            return this.backgroundColorBlender_serialize(blender_casted)
        }
        private backgroundColorBlender_serialize(blender: BrightnessBlender): VisualEffect {
            const thisSerializer : SerializerBase = SerializerBase.hold()
            uiEffect_BrightnessBlender_serializer.write(thisSerializer, blender)
            const retval  = ArkUIGeneratedNativeModule._uiEffect_VisualEffect_backgroundColorBlender(this.peer!.ptr, thisSerializer.asBuffer(), thisSerializer.length())
            thisSerializer.release()
            const obj : VisualEffect = uiEffect.VisualEffectInternal.fromPtr(retval)
            return obj
        }
    }
    export interface Filter {
    }
    export type Blender = uiEffect.BrightnessBlender;
    export interface BrightnessBlender {
        cubicRate: number;
        quadraticRate: number;
        linearRate: number;
        degree: number;
        saturation: number;
        positiveCoefficient: [ number, number, number ];
        negativeCoefficient: [ number, number, number ];
        fraction: number;
    }
    export interface BrightnessBlenderParam {
        cubicRate: number;
        quadraticRate: number;
        linearRate: number;
        degree: number;
        saturation: number;
        positiveCoefficient: [ number, number, number ];
        negativeCoefficient: [ number, number, number ];
        fraction: number;
    }
    export function createEffect(): VisualEffect {
        return GlobalScope.uiEffect_createEffect()
    }
    export function createBrightnessBlender(param: BrightnessBlenderParam): BrightnessBlender {
        return GlobalScope.uiEffect_createBrightnessBlender(param)
    }
}

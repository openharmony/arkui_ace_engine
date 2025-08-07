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

import { SerializerBase, DeserializerBase, CallbackResource, InteropNativeModule, MaterializedBase, Tags, RuntimeType, runtimeType, toPeerPtr, nullptr, KPointer, NativeBuffer, KSerializerBuffer, KUint8ArrayPtr, Finalizable, KInt, KBoolean, KStringPtr } from "@koalaui/interop"
import { int32, int64, float32, unsafeCast } from "@koalaui/common"
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
        const valueHolderForCubicRate  = value.cubicRate
        valueSerializer.writeNumber(valueHolderForCubicRate)
        const valueHolderForQuadraticRate  = value.quadraticRate
        valueSerializer.writeNumber(valueHolderForQuadraticRate)
        const valueHolderForLinearRate  = value.linearRate
        valueSerializer.writeNumber(valueHolderForLinearRate)
        const valueHolderForDegree  = value.degree
        valueSerializer.writeNumber(valueHolderForDegree)
        const valueHolderForSaturation  = value.saturation
        valueSerializer.writeNumber(valueHolderForSaturation)
        const valueHolderForPositiveCoefficient  = value.positiveCoefficient
        const valueHolderForPositiveCoefficient_0  = valueHolderForPositiveCoefficient[0]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_0)
        const valueHolderForPositiveCoefficient_1  = valueHolderForPositiveCoefficient[1]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_1)
        const valueHolderForPositiveCoefficient_2  = valueHolderForPositiveCoefficient[2]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_2)
        const valueHolderForNegativeCoefficient  = value.negativeCoefficient
        const valueHolderForNegativeCoefficient_0  = valueHolderForNegativeCoefficient[0]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_0)
        const valueHolderForNegativeCoefficient_1  = valueHolderForNegativeCoefficient[1]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_1)
        const valueHolderForNegativeCoefficient_2  = valueHolderForNegativeCoefficient[2]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_2)
        const valueHolderForFraction  = value.fraction
        valueSerializer.writeNumber(valueHolderForFraction)
    }
    public static read(buffer: DeserializerBase): uiEffect.BrightnessBlender {
        let valueDeserializer : DeserializerBase = buffer
        const cubicRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const quadraticRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const linearRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const degreeTmpResult : number = (valueDeserializer.readNumber() as number)
        const saturationTmpResult : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue2 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpResult : [ number, number, number ] = ([positiveCoefficientTmpBufValue0, positiveCoefficientTmpBufValue1, positiveCoefficientTmpBufValue2] as [ number, number, number ])
        const negativeCoefficientTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpBufValue2 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpResult : [ number, number, number ] = ([negativeCoefficientTmpBufValue0, negativeCoefficientTmpBufValue1, negativeCoefficientTmpBufValue2] as [ number, number, number ])
        const fractionTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : uiEffect.BrightnessBlender = ({cubicRate: cubicRateTmpResult, quadraticRate: quadraticRateTmpResult, linearRate: linearRateTmpResult, degree: degreeTmpResult, saturation: saturationTmpResult, positiveCoefficient: positiveCoefficientTmpResult, negativeCoefficient: negativeCoefficientTmpResult, fraction: fractionTmpResult} as uiEffect.BrightnessBlender)
        return value
    }
}
export class uiEffect_BrightnessBlenderParam_serializer {
    public static write(buffer: SerializerBase, value: uiEffect.BrightnessBlenderParam): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForCubicRate  = value.cubicRate
        valueSerializer.writeNumber(valueHolderForCubicRate)
        const valueHolderForQuadraticRate  = value.quadraticRate
        valueSerializer.writeNumber(valueHolderForQuadraticRate)
        const valueHolderForLinearRate  = value.linearRate
        valueSerializer.writeNumber(valueHolderForLinearRate)
        const valueHolderForDegree  = value.degree
        valueSerializer.writeNumber(valueHolderForDegree)
        const valueHolderForSaturation  = value.saturation
        valueSerializer.writeNumber(valueHolderForSaturation)
        const valueHolderForPositiveCoefficient  = value.positiveCoefficient
        const valueHolderForPositiveCoefficient_0  = valueHolderForPositiveCoefficient[0]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_0)
        const valueHolderForPositiveCoefficient_1  = valueHolderForPositiveCoefficient[1]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_1)
        const valueHolderForPositiveCoefficient_2  = valueHolderForPositiveCoefficient[2]
        valueSerializer.writeNumber(valueHolderForPositiveCoefficient_2)
        const valueHolderForNegativeCoefficient  = value.negativeCoefficient
        const valueHolderForNegativeCoefficient_0  = valueHolderForNegativeCoefficient[0]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_0)
        const valueHolderForNegativeCoefficient_1  = valueHolderForNegativeCoefficient[1]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_1)
        const valueHolderForNegativeCoefficient_2  = valueHolderForNegativeCoefficient[2]
        valueSerializer.writeNumber(valueHolderForNegativeCoefficient_2)
        const valueHolderForFraction  = value.fraction
        valueSerializer.writeNumber(valueHolderForFraction)
    }
    public static read(buffer: DeserializerBase): uiEffect.BrightnessBlenderParam {
        let valueDeserializer : DeserializerBase = buffer
        const cubicRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const quadraticRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const linearRateTmpResult : number = (valueDeserializer.readNumber() as number)
        const degreeTmpResult : number = (valueDeserializer.readNumber() as number)
        const saturationTmpResult : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpBufValue2 : number = (valueDeserializer.readNumber() as number)
        const positiveCoefficientTmpResult : [ number, number, number ] = ([positiveCoefficientTmpBufValue0, positiveCoefficientTmpBufValue1, positiveCoefficientTmpBufValue2] as [ number, number, number ])
        const negativeCoefficientTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpBufValue2 : number = (valueDeserializer.readNumber() as number)
        const negativeCoefficientTmpResult : [ number, number, number ] = ([negativeCoefficientTmpBufValue0, negativeCoefficientTmpBufValue1, negativeCoefficientTmpBufValue2] as [ number, number, number ])
        const fractionTmpResult : number = (valueDeserializer.readNumber() as number)
        let value : uiEffect.BrightnessBlenderParam = ({cubicRate: cubicRateTmpResult, quadraticRate: quadraticRateTmpResult, linearRate: linearRateTmpResult, degree: degreeTmpResult, saturation: saturationTmpResult, positiveCoefficient: positiveCoefficientTmpResult, negativeCoefficient: negativeCoefficientTmpResult, fraction: fractionTmpResult} as uiEffect.BrightnessBlenderParam)
        return value
    }
}
export namespace uiEffect {
    export interface VisualEffect {
        backgroundColorBlender(blender: BrightnessBlender): VisualEffect
    }
    export class VisualEffectInternal implements MaterializedBase,VisualEffect {
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

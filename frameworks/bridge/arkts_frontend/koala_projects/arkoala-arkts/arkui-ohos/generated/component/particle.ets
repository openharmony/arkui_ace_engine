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
import { VP, Dimension, ResourceStr, ResourceColor } from "./units"
import { Resource } from "global.resource"
import { ImageFit, Color } from "./enums"
import { default as curves } from "@ohos.curves"
import { extractors } from "#handwritten"
import { Vector2T, LengthMetrics } from "arkui.Graphics"
import { TypeChecker } from "#components"
import { CallbackTransformer } from "./../CallbackTransformer"
import { Resource_serializer } from "./../framework/resource"
export interface VelocityOptions {
    speed: [ number, number ];
    angle: [ number, number ];
}
export interface PointParticleParameters {
    radius: VP;
}
export interface ImageParticleParameters {
    src: ResourceStr;
    size: [ Dimension, Dimension ];
    objectFit?: ImageFit;
}
export type ParticleConfigs = PointParticleParameters | ImageParticleParameters;
export interface EmitterParticleOptions {
    type: ParticleType;
    config: ParticleConfigs;
    count: number;
    lifetime?: number;
    lifetimeRange?: number;
}
export type ParticlePropertyUpdaterConfigs = [ number, number ] | Array<ParticlePropertyAnimation<number>> | undefined;
export interface ParticleUpdaterOptions {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigs;
}
export interface ParticleColorOptions {
    r: [ number, number ];
    g: [ number, number ];
    b: [ number, number ];
    a: [ number, number ];
}
export interface ParticleColorUpdaterOptions {
    type: ParticleUpdater;
    config: ParticleColorPropertyUpdaterConfigs;
}
export type ParticleColorPropertyUpdaterConfigs = ParticleColorOptions | Array<ParticlePropertyAnimation<ResourceColor>> | undefined;
export interface ParticlePropertyAnimation<T = void> {
    from: T;
    to: T;
    startMillis: number;
    endMillis: number;
    curve?: curves.Curve | curves.ICurve;
}
export enum ParticleType {
    POINT = "'point'",
    IMAGE = "'image'"
}
export enum ParticleEmitterShape {
    RECTANGLE = "'rectangle'",
    CIRCLE = "'circle'",
    ELLIPSE = "'ellipse'",
    ANNULUS = "'annulus'"
}
export enum DistributionType {
    UNIFORM = 0,
    GAUSSIAN = 1
}
export enum ParticleUpdater {
    NONE = "'none'",
    RANDOM = "'random'",
    CURVE = "'curve'"
}
export enum DisturbanceFieldShape {
    RECT = 0,
    CIRCLE = 1,
    ELLIPSE = 2
}
export interface ParticleAnnulusRegion {
    center?: Vector2T<LengthMetrics>;
    outerRadius: LengthMetrics;
    innerRadius: LengthMetrics;
    startAngle?: number;
    endAngle?: number;
}
export class VelocityOptions_serializer {
    public static write(buffer: SerializerBase, value: VelocityOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpeed  = value.speed
        const valueHolderForSpeed_0  = valueHolderForSpeed[0]
        valueSerializer.writeNumber(valueHolderForSpeed_0)
        const valueHolderForSpeed_1  = valueHolderForSpeed[1]
        valueSerializer.writeNumber(valueHolderForSpeed_1)
        const valueHolderForAngle  = value.angle
        const valueHolderForAngle_0  = valueHolderForAngle[0]
        valueSerializer.writeNumber(valueHolderForAngle_0)
        const valueHolderForAngle_1  = valueHolderForAngle[1]
        valueSerializer.writeNumber(valueHolderForAngle_1)
    }
    public static read(buffer: DeserializerBase): VelocityOptions {
        let valueDeserializer : DeserializerBase = buffer
        const speedTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const speedTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const speedTmpResult : [ number, number ] = ([speedTmpBufValue0, speedTmpBufValue1] as [ number, number ])
        const angleTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const angleTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const angleTmpResult : [ number, number ] = ([angleTmpBufValue0, angleTmpBufValue1] as [ number, number ])
        let value : VelocityOptions = ({speed: speedTmpResult, angle: angleTmpResult} as VelocityOptions)
        return value
    }
}
export class ParticleColorOptions_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForR  = value.r
        const valueHolderForR_0  = valueHolderForR[0]
        valueSerializer.writeNumber(valueHolderForR_0)
        const valueHolderForR_1  = valueHolderForR[1]
        valueSerializer.writeNumber(valueHolderForR_1)
        const valueHolderForG  = value.g
        const valueHolderForG_0  = valueHolderForG[0]
        valueSerializer.writeNumber(valueHolderForG_0)
        const valueHolderForG_1  = valueHolderForG[1]
        valueSerializer.writeNumber(valueHolderForG_1)
        const valueHolderForB  = value.b
        const valueHolderForB_0  = valueHolderForB[0]
        valueSerializer.writeNumber(valueHolderForB_0)
        const valueHolderForB_1  = valueHolderForB[1]
        valueSerializer.writeNumber(valueHolderForB_1)
        const valueHolderForA  = value.a
        const valueHolderForA_0  = valueHolderForA[0]
        valueSerializer.writeNumber(valueHolderForA_0)
        const valueHolderForA_1  = valueHolderForA[1]
        valueSerializer.writeNumber(valueHolderForA_1)
    }
    public static read(buffer: DeserializerBase): ParticleColorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const rTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const rTmpResult : [ number, number ] = ([rTmpBufValue0, rTmpBufValue1] as [ number, number ])
        const gTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const gTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const gTmpResult : [ number, number ] = ([gTmpBufValue0, gTmpBufValue1] as [ number, number ])
        const bTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const bTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const bTmpResult : [ number, number ] = ([bTmpBufValue0, bTmpBufValue1] as [ number, number ])
        const aTmpBufValue0 : number = (valueDeserializer.readNumber() as number)
        const aTmpBufValue1 : number = (valueDeserializer.readNumber() as number)
        const aTmpResult : [ number, number ] = ([aTmpBufValue0, aTmpBufValue1] as [ number, number ])
        let value : ParticleColorOptions = ({r: rTmpResult, g: gTmpResult, b: bTmpResult, a: aTmpResult} as ParticleColorOptions)
        return value
    }
}
export class PointParticleParameters_serializer {
    public static write(buffer: SerializerBase, value: PointParticleParameters): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForRadius  = value.radius
        if (valueHolderForRadius instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForRadiusForIdx0  = valueHolderForRadius as string
            valueSerializer.writeString(valueHolderForRadiusForIdx0)
        } else if (valueHolderForRadius instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRadiusForIdx1  = valueHolderForRadius as number
            valueSerializer.writeNumber(valueHolderForRadiusForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): PointParticleParameters {
        let valueDeserializer : DeserializerBase = buffer
        const radiusTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let radiusTmpBuf : string | number | undefined
        if (radiusTmpBufUnionSelector == (0).toChar()) {
            radiusTmpBuf = (valueDeserializer.readString() as string)
        } else if (radiusTmpBufUnionSelector == (1).toChar()) {
            radiusTmpBuf = (valueDeserializer.readNumber() as number)
        } else {
            throw new Error("One of the branches for radiusTmpBuf has to be chosen through deserialisation.")
        }
        const radiusTmpResult : VP = (radiusTmpBuf as string | number)
        let value : PointParticleParameters = ({radius: radiusTmpResult} as PointParticleParameters)
        return value
    }
}
export class ImageParticleParameters_serializer {
    public static write(buffer: SerializerBase, value: ImageParticleParameters): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSrc  = value.src
        if (valueHolderForSrc instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSrcForIdx0  = valueHolderForSrc as string
            valueSerializer.writeString(valueHolderForSrcForIdx0)
        } else if (valueHolderForSrc instanceof Resource) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSrcForIdx1  = valueHolderForSrc as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSrcForIdx1)
        }
        const valueHolderForSize  = value.size
        const valueHolderForSize_0  = valueHolderForSize[0]
        if (valueHolderForSize_0 instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSize_0ForIdx0  = valueHolderForSize_0 as string
            valueSerializer.writeString(valueHolderForSize_0ForIdx0)
        } else if (valueHolderForSize_0 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSize_0ForIdx1  = valueHolderForSize_0 as number
            valueSerializer.writeNumber(valueHolderForSize_0ForIdx1)
        } else if (valueHolderForSize_0 instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForSize_0ForIdx2  = valueHolderForSize_0 as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSize_0ForIdx2)
        }
        const valueHolderForSize_1  = valueHolderForSize[1]
        if (valueHolderForSize_1 instanceof string) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForSize_1ForIdx0  = valueHolderForSize_1 as string
            valueSerializer.writeString(valueHolderForSize_1ForIdx0)
        } else if (valueHolderForSize_1 instanceof number) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForSize_1ForIdx1  = valueHolderForSize_1 as number
            valueSerializer.writeNumber(valueHolderForSize_1ForIdx1)
        } else if (valueHolderForSize_1 instanceof Resource) {
            valueSerializer.writeInt8((2).toByte())
            const valueHolderForSize_1ForIdx2  = valueHolderForSize_1 as Resource
            Resource_serializer.write(valueSerializer, valueHolderForSize_1ForIdx2)
        }
        const valueHolderForObjectFit  = value.objectFit
        if (valueHolderForObjectFit !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForObjectFitTmpValue  = (valueHolderForObjectFit as ImageFit)
            valueSerializer.writeInt32(valueHolderForObjectFitTmpValue.valueOf())
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): ImageParticleParameters {
        let valueDeserializer : DeserializerBase = buffer
        const srcTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let srcTmpBuf : string | Resource | undefined
        if (srcTmpBufUnionSelector == (0).toChar()) {
            srcTmpBuf = (valueDeserializer.readString() as string)
        } else if (srcTmpBufUnionSelector == (1).toChar()) {
            srcTmpBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for srcTmpBuf has to be chosen through deserialisation.")
        }
        const srcTmpResult : ResourceStr = (srcTmpBuf as string | Resource)
        const sizeTmpBufValue0TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let sizeTmpBufValue0TempBuf : string | number | Resource | undefined
        if (sizeTmpBufValue0TempBufUnionSelector == (0).toChar()) {
            sizeTmpBufValue0TempBuf = (valueDeserializer.readString() as string)
        } else if (sizeTmpBufValue0TempBufUnionSelector == (1).toChar()) {
            sizeTmpBufValue0TempBuf = (valueDeserializer.readNumber() as number)
        } else if (sizeTmpBufValue0TempBufUnionSelector == (2).toChar()) {
            sizeTmpBufValue0TempBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for sizeTmpBufValue0TempBuf has to be chosen through deserialisation.")
        }
        const sizeTmpBufValue0 : Dimension = (sizeTmpBufValue0TempBuf as string | number | Resource)
        const sizeTmpBufValue1TempBufUnionSelector : int32 = valueDeserializer.readInt8()
        let sizeTmpBufValue1TempBuf : string | number | Resource | undefined
        if (sizeTmpBufValue1TempBufUnionSelector == (0).toChar()) {
            sizeTmpBufValue1TempBuf = (valueDeserializer.readString() as string)
        } else if (sizeTmpBufValue1TempBufUnionSelector == (1).toChar()) {
            sizeTmpBufValue1TempBuf = (valueDeserializer.readNumber() as number)
        } else if (sizeTmpBufValue1TempBufUnionSelector == (2).toChar()) {
            sizeTmpBufValue1TempBuf = Resource_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for sizeTmpBufValue1TempBuf has to be chosen through deserialisation.")
        }
        const sizeTmpBufValue1 : Dimension = (sizeTmpBufValue1TempBuf as string | number | Resource)
        const sizeTmpResult : [ Dimension, Dimension ] = ([sizeTmpBufValue0, sizeTmpBufValue1] as [ Dimension, Dimension ])
        const objectFitTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let objectFitTmpBuf : ImageFit | undefined = undefined
        if ((objectFitTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            objectFitTmpBuf = ImageFit.fromValue(valueDeserializer.readInt32())
        }
        const objectFitTmpResult : ImageFit | undefined = objectFitTmpBuf
        let value : ImageParticleParameters = ({src: srcTmpResult, size: sizeTmpResult, objectFit: objectFitTmpResult} as ImageParticleParameters)
        return value
    }
}
export class EmitterParticleOptions_serializer {
    public static write(buffer: SerializerBase, value: EmitterParticleOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForType  = value.type
        valueSerializer.writeInt32(valueHolderForType.getOrdinal())
        const valueHolderForConfig  = value.config
        if (valueHolderForConfig instanceof PointParticleParameters) {
            valueSerializer.writeInt8((0).toByte())
            const valueHolderForConfigForIdx0  = valueHolderForConfig as PointParticleParameters
            PointParticleParameters_serializer.write(valueSerializer, valueHolderForConfigForIdx0)
        } else if (valueHolderForConfig instanceof ImageParticleParameters) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForConfigForIdx1  = valueHolderForConfig as ImageParticleParameters
            ImageParticleParameters_serializer.write(valueSerializer, valueHolderForConfigForIdx1)
        }
        const valueHolderForCount  = value.count
        valueSerializer.writeNumber(valueHolderForCount)
        const valueHolderForLifetime  = value.lifetime
        if (valueHolderForLifetime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLifetimeTmpValue  = valueHolderForLifetime!
            valueSerializer.writeNumber(valueHolderForLifetimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLifetimeRange  = value.lifetimeRange
        if (valueHolderForLifetimeRange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLifetimeRangeTmpValue  = valueHolderForLifetimeRange!
            valueSerializer.writeNumber(valueHolderForLifetimeRangeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
    }
    public static read(buffer: DeserializerBase): EmitterParticleOptions {
        let valueDeserializer : DeserializerBase = buffer
        const typeTmpResult : ParticleType = ParticleType.values()[valueDeserializer.readInt32()]
        const configTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let configTmpBuf : PointParticleParameters | ImageParticleParameters | undefined
        if (configTmpBufUnionSelector == (0).toChar()) {
            configTmpBuf = PointParticleParameters_serializer.read(valueDeserializer)
        } else if (configTmpBufUnionSelector == (1).toChar()) {
            configTmpBuf = ImageParticleParameters_serializer.read(valueDeserializer)
        } else {
            throw new Error("One of the branches for configTmpBuf has to be chosen through deserialisation.")
        }
        const configTmpResult : ParticleConfigs = (configTmpBuf as PointParticleParameters | ImageParticleParameters)
        const countTmpResult : number = (valueDeserializer.readNumber() as number)
        const lifetimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lifetimeTmpBuf : number | undefined = undefined
        if ((lifetimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lifetimeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const lifetimeTmpResult : number | undefined = lifetimeTmpBuf
        const lifetimeRangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lifetimeRangeTmpBuf : number | undefined = undefined
        if ((lifetimeRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lifetimeRangeTmpBuf = (valueDeserializer.readNumber() as number)
        }
        const lifetimeRangeTmpResult : number | undefined = lifetimeRangeTmpBuf
        let value : EmitterParticleOptions = ({type: typeTmpResult, config: configTmpResult, count: countTmpResult, lifetime: lifetimeTmpResult, lifetimeRange: lifetimeRangeTmpResult} as EmitterParticleOptions)
        return value
    }
}
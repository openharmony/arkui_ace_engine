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
    speed: [ double, double ];
    angle: [ double, double ];
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
    count: int32;
    lifetime?: int32;
    lifetimeRange?: int32;
}
export type ParticlePropertyUpdaterConfigs = [ double, double ] | Array<ParticlePropertyAnimation<double>> | undefined;
export interface ParticleUpdaterOptions {
    type: ParticleUpdater;
    config: ParticlePropertyUpdaterConfigs;
}
export interface ParticleColorOptions {
    r: [ int32, int32 ];
    g: [ int32, int32 ];
    b: [ int32, int32 ];
    a: [ int32, int32 ];
}
export interface ParticleColorUpdaterOptions {
    type: ParticleUpdater;
    config: ParticleColorPropertyUpdaterConfigs;
}
export type ParticleColorPropertyUpdaterConfigs = ParticleColorOptions | Array<ParticlePropertyAnimation<ResourceColor>> | undefined;
export interface ParticlePropertyAnimation<T = void> {
    from: T;
    to: T;
    startMillis: int32;
    endMillis: int32;
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
    startAngle?: double;
    endAngle?: double;
}
export class VelocityOptions_serializer {
    public static write(buffer: SerializerBase, value: VelocityOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForSpeed  = value.speed
        const valueHolderForSpeed_0  = valueHolderForSpeed[0]
        valueSerializer.writeFloat64(valueHolderForSpeed_0)
        const valueHolderForSpeed_1  = valueHolderForSpeed[1]
        valueSerializer.writeFloat64(valueHolderForSpeed_1)
        const valueHolderForAngle  = value.angle
        const valueHolderForAngle_0  = valueHolderForAngle[0]
        valueSerializer.writeFloat64(valueHolderForAngle_0)
        const valueHolderForAngle_1  = valueHolderForAngle[1]
        valueSerializer.writeFloat64(valueHolderForAngle_1)
    }
    public static read(buffer: DeserializerBase): VelocityOptions {
        let valueDeserializer : DeserializerBase = buffer
        const speedTmpBufValue0 : double = valueDeserializer.readFloat64()
        const speedTmpBufValue1 : double = valueDeserializer.readFloat64()
        const speedTmpResult : [ double, double ] = ([speedTmpBufValue0, speedTmpBufValue1] as [ double, double ])
        const angleTmpBufValue0 : double = valueDeserializer.readFloat64()
        const angleTmpBufValue1 : double = valueDeserializer.readFloat64()
        const angleTmpResult : [ double, double ] = ([angleTmpBufValue0, angleTmpBufValue1] as [ double, double ])
        let value : VelocityOptions = ({speed: speedTmpResult, angle: angleTmpResult} as VelocityOptions)
        return value
    }
}
export class ParticleColorOptions_serializer {
    public static write(buffer: SerializerBase, value: ParticleColorOptions): void {
        let valueSerializer : SerializerBase = buffer
        const valueHolderForR  = value.r
        const valueHolderForR_0  = valueHolderForR[0]
        valueSerializer.writeInt32(valueHolderForR_0)
        const valueHolderForR_1  = valueHolderForR[1]
        valueSerializer.writeInt32(valueHolderForR_1)
        const valueHolderForG  = value.g
        const valueHolderForG_0  = valueHolderForG[0]
        valueSerializer.writeInt32(valueHolderForG_0)
        const valueHolderForG_1  = valueHolderForG[1]
        valueSerializer.writeInt32(valueHolderForG_1)
        const valueHolderForB  = value.b
        const valueHolderForB_0  = valueHolderForB[0]
        valueSerializer.writeInt32(valueHolderForB_0)
        const valueHolderForB_1  = valueHolderForB[1]
        valueSerializer.writeInt32(valueHolderForB_1)
        const valueHolderForA  = value.a
        const valueHolderForA_0  = valueHolderForA[0]
        valueSerializer.writeInt32(valueHolderForA_0)
        const valueHolderForA_1  = valueHolderForA[1]
        valueSerializer.writeInt32(valueHolderForA_1)
    }
    public static read(buffer: DeserializerBase): ParticleColorOptions {
        let valueDeserializer : DeserializerBase = buffer
        const rTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const rTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const rTmpResult : [ int32, int32 ] = ([rTmpBufValue0, rTmpBufValue1] as [ int32, int32 ])
        const gTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const gTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const gTmpResult : [ int32, int32 ] = ([gTmpBufValue0, gTmpBufValue1] as [ int32, int32 ])
        const bTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const bTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const bTmpResult : [ int32, int32 ] = ([bTmpBufValue0, bTmpBufValue1] as [ int32, int32 ])
        const aTmpBufValue0 : int32 = valueDeserializer.readInt32()
        const aTmpBufValue1 : int32 = valueDeserializer.readInt32()
        const aTmpResult : [ int32, int32 ] = ([aTmpBufValue0, aTmpBufValue1] as [ int32, int32 ])
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
        } else if (valueHolderForRadius instanceof double) {
            valueSerializer.writeInt8((1).toByte())
            const valueHolderForRadiusForIdx1  = valueHolderForRadius as double
            valueSerializer.writeFloat64(valueHolderForRadiusForIdx1)
        }
    }
    public static read(buffer: DeserializerBase): PointParticleParameters {
        let valueDeserializer : DeserializerBase = buffer
        const radiusTmpBufUnionSelector : int32 = valueDeserializer.readInt8()
        let radiusTmpBuf : string | double | undefined
        if (radiusTmpBufUnionSelector == (0).toChar()) {
            radiusTmpBuf = (valueDeserializer.readString() as string)
        } else if (radiusTmpBufUnionSelector == (1).toChar()) {
            radiusTmpBuf = valueDeserializer.readFloat64()
        } else {
            throw new Error("One of the branches for radiusTmpBuf has to be chosen through deserialisation.")
        }
        const radiusTmpResult : VP = (radiusTmpBuf as string | double)
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
        valueSerializer.writeInt32(valueHolderForCount)
        const valueHolderForLifetime  = value.lifetime
        if (valueHolderForLifetime !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLifetimeTmpValue  = valueHolderForLifetime!
            valueSerializer.writeInt32(valueHolderForLifetimeTmpValue)
        } else {
            valueSerializer.writeInt8(RuntimeType.UNDEFINED)
        }
        const valueHolderForLifetimeRange  = value.lifetimeRange
        if (valueHolderForLifetimeRange !== undefined) {
            valueSerializer.writeInt8(RuntimeType.OBJECT)
            const valueHolderForLifetimeRangeTmpValue  = valueHolderForLifetimeRange!
            valueSerializer.writeInt32(valueHolderForLifetimeRangeTmpValue)
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
        const countTmpResult : int32 = valueDeserializer.readInt32()
        const lifetimeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lifetimeTmpBuf : int32 | undefined = undefined
        if ((lifetimeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lifetimeTmpBuf = valueDeserializer.readInt32()
        }
        const lifetimeTmpResult : int32 | undefined = lifetimeTmpBuf
        const lifetimeRangeTmpBuf_runtimeType  = valueDeserializer.readInt8().toInt()
        let lifetimeRangeTmpBuf : int32 | undefined = undefined
        if ((lifetimeRangeTmpBuf_runtimeType) != (RuntimeType.UNDEFINED)) {
            lifetimeRangeTmpBuf = valueDeserializer.readInt32()
        }
        const lifetimeRangeTmpResult : int32 | undefined = lifetimeRangeTmpBuf
        let value : EmitterParticleOptions = ({type: typeTmpResult, config: configTmpResult, count: countTmpResult, lifetime: lifetimeTmpResult, lifetimeRange: lifetimeRangeTmpResult} as EmitterParticleOptions)
        return value
    }
}
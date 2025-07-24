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

import { int32, int64, float32 } from "@koalaui/common"
import { KInt, KPointer, KBoolean, KStringPtr, wrapCallback, NativeBuffer } from "@koalaui/interop"
import { NodeAttach, remember } from "@koalaui/runtime"
import { VP, ResourceStr, Dimension } from "./ArkUnitsInterfaces"
import { ImageFit, Curve } from "./ArkEnumsInterfaces"
import { ICurve } from "./ArkICurveMaterialized"
import { CommonMethod } from "./ArkCommonInterfaces"

export type ParticleTuple<T1,T2> = [
    T1,
    T2
]
export interface VelocityOptions {
    speed: ParticleTuple<number, number>;
    angle: ParticleTuple<number, number>;
}
export interface PointParticleParameters {
    radius: VP;
}
export interface ImageParticleParameters {
    src: ResourceStr;
    size: ParticleTuple<Dimension, Dimension>;
    objectFit?: ImageFit;
}
export interface ParticleConfigs {
}
export interface EmitterProperty {
    stub: string;
}
export interface EmitterParticleOptions<PARTICLE> {
    type: PARTICLE;
    config: string;
    count: number;
    lifetime?: number;
    lifetimeRange?: number;
}
export interface ParticlePropertyUpdaterConfigs<T> {
}
export interface ParticleUpdaterOptions<TYPE,UPDATER> {
    type: UPDATER;
    config: string;
}
export interface ParticleColorOptions {
    r: ParticleTuple<number, number>;
    g: ParticleTuple<number, number>;
    b: ParticleTuple<number, number>;
    a: ParticleTuple<number, number>;
}
export interface ParticleColorUpdaterOptions<UPDATER> {
    type: UPDATER;
    config: string;
}
export interface ParticleColorPropertyUpdaterConfigs {
}
export interface ParticlePropertyAnimation<T> {
    from: T;
    to: T;
    startMillis: number;
    endMillis: number;
    curve?: Curve | ICurve;
}
export enum ParticleType {
    POINT = "point",
    IMAGE = "image"
}
export enum ParticleEmitterShape {
    RECTANGLE = "rectangle",
    CIRCLE = "circle",
    ELLIPSE = "ellipse"
}
export enum DistributionType {
    UNIFORM = 0,
    GAUSSIAN = 1
}
export enum ParticleUpdater {
    NONE = "none",
    RANDOM = "random",
    CURVE = "curve"
}
export enum DisturbanceFieldShape {
    RECT = 0,
    CIRCLE = 1,
    ELLIPSE = 2
}

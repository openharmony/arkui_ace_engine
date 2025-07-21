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
import { KInt, KPointer, KBoolean, NativeBuffer, KStringPtr, wrapCallback } from "@koalaui/interop"
import { memo, memo_stable } from "@koalaui/runtime/annotations"
import { ComponentBuilder } from "@koalaui/builderLambda"
import { VP, Dimension, ResourceStr, ResourceColor } from "./units"
import { Resource } from "./../generated/resource"
import { ImageFit, Color } from "./enums"
import { curves } from "./../generated/ohos.curves"
import { Vector2T, LengthMetrics } from "./../generated/arkui.Graphics"
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
export interface EmitterProperty {
    _stub: int32;
}
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

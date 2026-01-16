/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file will be merged with component/xxx.ets by compiler pre-process script

import { runtimeType, RuntimeType } from "@koalaui/interop"
import { unsafeCast } from "@koalaui/common"
import { ComponentBase } from "./../ComponentBase"
import { PeerNode } from "./../PeerNode"
import { ArkCommonMethodPeer, CommonMethod, ICurve, ArkCommonMethodComponent, ArkCommonMethodStyle, AttributeModifier } from "./common"
import { VP, Dimension, ResourceStr, ResourceColor } from "./units"
import { SizeT, PositionT, LengthMetrics, Vector2T } from "../Graphics"
import { ParticleHelper, ParticlesInner, ParticleOptionsInner, EmitterOptionsInner, ParticleColorPropertyOptionsInner } from "./idlize"
import { ParticlePropertyOptionsInner, AccelerationOptionsInner, ParticleAnnulusRegionInner, ParticleColorUpdaterOptionsInner } from "./idlize"
import { ParticleUpdaterOptionsInner, PositionLengthMetricsInner, ParticleColorPropertyUpdaterConfigsInner, EmitterPropertyInner } from "./idlize"
import { ParticlePropertyUpdaterConfigsInner, ParticlePropertyAnimationColorInner, ParticlePropertyAnimationNumberInner } from "./idlize"
import { PositionF64Inner, SizeF64Inner, Vector2F64, DisturbanceFieldOptionsInner, RippleFieldOptionsInner, VelocityFieldOptionsInner, FieldRegionInner } from "./idlize"
import { NodeAttach, remember } from "@koalaui/runtime"
import { ParticleModifier } from "../ParticleModifier"
import { hookParticleAttributeModifier } from "#handwritten"
import { ModifierStateManager } from '../CommonModifier'

export interface AccelerationOptions {
    speed?: ParticlePropertyOptions;
    angle?: ParticlePropertyOptions;
}
export interface ParticleOptions {
    emitter: EmitterOptions;
    color?: ParticleColorPropertyOptions;
    opacity?: ParticlePropertyOptions;
    scale?: ParticlePropertyOptions;
    velocity?: VelocityOptions;
    acceleration?: AccelerationOptions;
    spin?: ParticlePropertyOptions;
}

export interface EmitterProperty {
    index: int32;
    emitRate?: int32;
    position?: PositionT<double>;
    size?: SizeT<double>;
    annulusRegion?: ParticleAnnulusRegion;
}

export interface EmitterOptions {
    particle: EmitterParticleOptions;
    emitRate?: int32;
    shape?: ParticleEmitterShape;
    position?: [ Dimension, Dimension ];
    size?: [ Dimension, Dimension ];
    annulusRegion?: ParticleAnnulusRegion;
}

export interface ParticlePropertyOptions {
    range: [ double, double ];
    updater?: ParticleUpdaterOptions;
}
export interface ParticleColorPropertyOptions {
    range: [ ResourceColor, ResourceColor ];
    distributionType?: DistributionType;
    updater?: ParticleColorUpdaterOptions;
}
export interface Particles {
    particles: Array<ParticleOptions>;
}
export interface FieldRegion {
    shape?: DisturbanceFieldShape;
    position?: PositionT<double>;
    size?: SizeT<double>;
}
export interface DisturbanceFieldOptions {
    strength?: double;
    shape?: DisturbanceFieldShape;
    size?: SizeT<double>;
    position?: PositionT<double>;
    feather?: int32;
    noiseScale?: double;
    noiseFrequency?: double;
    noiseAmplitude?: double;
}
export interface RippleFieldOptions {
    amplitude?: double;
    wavelength?: double;
    waveSpeed?: double;
    attenuation?: double;
    center?: PositionT<double>;
    region?: FieldRegion;
}
export interface VelocityFieldOptions {
    velocity?: Vector2T<double>;
    region?: FieldRegion;
}

export interface ParticleAttribute extends CommonMethod {
    disturbanceFields(value: Array<DisturbanceFieldOptions> | undefined): this
    emitter(value: Array<EmitterProperty> | undefined): this
    attributeModifier(modifier: AttributeModifier<ParticleAttribute> | AttributeModifier<CommonMethod> | undefined): this
    setParticleOptions(particles: Particles): this
    rippleFields(value: Array<RippleFieldOptions> | undefined): this
    velocityFields(fields: Array<VelocityFieldOptions> | undefined): this
}

class ParticleToParticleInnerHelper {
    static ConvertParticles(input: Particles): ParticlesInner {
        let particlesInner = new Array<ParticleOptionsInner>;
        input.particles.forEach(element => {
            particlesInner.push(ParticleToParticleInnerHelper.ConvertParticleOptions(element));
        });
        return { particles: particlesInner };
    }
    static ConvertParticleOptions(input: ParticleOptions): ParticleOptionsInner {
        return {
            emitter: ParticleToParticleInnerHelper.ConvertEmitterOptions(input.emitter),
            color: ParticleToParticleInnerHelper.ConvertParticleColorPropertyOptions(input.color),
            opacity: ParticleToParticleInnerHelper.ConvertParticlePropertyOptions(input.opacity),
            scale: ParticleToParticleInnerHelper.ConvertParticlePropertyOptions(input.scale),
            velocity: input.velocity,
            acceleration: ParticleToParticleInnerHelper.ConvertAccelerationOptions(input.acceleration),
            spin: ParticleToParticleInnerHelper.ConvertParticlePropertyOptions(input.spin),
        }
    }
    static ConvertEmitterOptions(input: EmitterOptions): EmitterOptionsInner {
        return {
            particle: input.particle,
            emitRate: input.emitRate,
            shape: input.shape,
            position: input.position,
            size: input.size,
            annulusRegion: ParticleToParticleInnerHelper.ConvertParticleAnnulusRegion(input.annulusRegion),
        };
    }
    static ConvertParticleColorPropertyOptions(input: ParticleColorPropertyOptions | undefined): ParticleColorPropertyOptionsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            range: input.range,
            distributionType: input.distributionType,
            updater: ParticleToParticleInnerHelper.ConvertParticleColorUpdaterOptions(input.updater),
        };
    }
    static ConvertParticlePropertyOptions(input: ParticlePropertyOptions | undefined): ParticlePropertyOptionsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            range: input.range,
            updater: ParticleToParticleInnerHelper.ConvertParticleUpdaterOptions(input.updater),
        };
    }
    static ConvertAccelerationOptions(input: AccelerationOptions | undefined): AccelerationOptionsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            speed: ParticleToParticleInnerHelper.ConvertParticlePropertyOptions(input.speed),
            angle: ParticleToParticleInnerHelper.ConvertParticlePropertyOptions(input.angle),
        };
    }
    static ConvertParticleAnnulusRegion(input: ParticleAnnulusRegion | undefined): ParticleAnnulusRegionInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            center: ParticleToParticleInnerHelper.ConvertPositionLengthMetrics(input.center),
            outerRadius: input.outerRadius,
            innerRadius: input.innerRadius,
            startAngle: input.startAngle,
            endAngle: input.endAngle,
        };
    }
    static ConvertParticleColorUpdaterOptions(input: ParticleColorUpdaterOptions | undefined): ParticleColorUpdaterOptionsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            type: input.type,
            config: ParticleToParticleInnerHelper.ConvertParticleColorPropertyUpdaterConfigs(input.config),
        };
    }
    static ConvertParticleUpdaterOptions(input: ParticleUpdaterOptions | undefined): ParticleUpdaterOptionsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            type: input.type,
            config: ParticleToParticleInnerHelper.ConvertParticlePropertyUpdaterConfigs(input.config),
        };
    }
    static ConvertPositionLengthMetrics(input: PositionT<LengthMetrics> | undefined): PositionLengthMetricsInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            x: input.x,
            y: input.y,
        };
    }
    static ConvertParticleColorPropertyUpdaterConfigs(input: ParticleColorPropertyUpdaterConfigs): ParticleColorPropertyUpdaterConfigsInner {
        if (input === undefined) {
            return input;
        }
        if ((input as Object).hasOwnProperty("r")) {
            return (input as ParticleColorOptions);
        }
        return ParticleToParticleInnerHelper.ConvertParticlePropertyAnimationColor(input as Array<ParticlePropertyAnimation<ResourceColor>>);
    }
    static ConvertParticlePropertyUpdaterConfigs(input: ParticlePropertyUpdaterConfigs): ParticlePropertyUpdaterConfigsInner {
        if (input === undefined) {
            return input;
        }
        if (input instanceof Array) {
            return ParticleToParticleInnerHelper.ConvertParticlePropertyAnimationNumber(input as Array<ParticlePropertyAnimation<number>>);
        }
        return input;
    }
    static ConvertParticlePropertyAnimationColor(input: Array<ParticlePropertyAnimation<ResourceColor>>): Array<ParticlePropertyAnimationColorInner> {
        let result: Array<ParticlePropertyAnimationColorInner> = new Array<ParticlePropertyAnimationColorInner>();
        input.forEach((element: ParticlePropertyAnimation<ResourceColor>) => {
            result.push({
                from: element.from,
                to: element.to,
                startMillis: element.startMillis,
                endMillis: element.endMillis,
                curve: element.curve,
            });
        });
        return result;
    }
    static ConvertParticlePropertyAnimationNumber(input: Array<ParticlePropertyAnimation<number>>): Array<ParticlePropertyAnimationNumberInner> {
        let result: Array<ParticlePropertyAnimationNumberInner> = new Array<ParticlePropertyAnimationNumberInner>();
        input.forEach((element: ParticlePropertyAnimation<number>) => {
            result.push({
                from: element.from,
                to: element.to,
                startMillis: element.startMillis,
                endMillis: element.endMillis,
                curve: element.curve,
            });
        });
        return result;
    }
    static ConvertArrayEmitterProperty(input: Array<EmitterProperty> | undefined): Array<EmitterPropertyInner> | undefined {
        if (input === undefined) {
            return input;
        }
        let result: Array<EmitterPropertyInner> = new Array<EmitterPropertyInner>();
        input.forEach((element: EmitterProperty) => {
            result.push({
                index: element.index,
                emitRate: element.emitRate,
                position: ParticleToParticleInnerHelper.ConvertPositionNumber(element.position),
                size: ParticleToParticleInnerHelper.ConvertSizeNumber(element.size),
                annulusRegion: ParticleToParticleInnerHelper.ConvertParticleAnnulusRegion(element.annulusRegion),
            });
        });
        return result;
    }
    static ConvertPositionNumber(input: PositionT<double> | undefined): PositionF64Inner | undefined {
        if (input === undefined) {
            return input;
        }
        return {
            x: input.x,
            y: input.y,
        }
    }
    static ConvertVectorNumber(input: Vector2T<double> | undefined): Vector2F64 | undefined {
        if (input === undefined) {
            return input;
        }
        return {
            x: input.x,
            y: input.y,
        }
    }
    static ConvertSizeNumber(input: SizeT<double> | undefined): SizeF64Inner | undefined {
        if (input === undefined) {
            return input;
        }
        return {
            width: input.width,
            height: input.height,
        }
    }
    static ConvertArrayDisturbanceFieldOptions(input: Array<DisturbanceFieldOptions> | undefined): Array<DisturbanceFieldOptionsInner> | undefined {
        if (input === undefined) {
            return input;
        }
        let result: Array<DisturbanceFieldOptionsInner> = new Array<DisturbanceFieldOptionsInner>();
        input.forEach((element: DisturbanceFieldOptions) => {
            result.push({
                strength: element.strength,
                shape: element.shape,
                size: ParticleToParticleInnerHelper.ConvertSizeNumber(element.size),
                position: ParticleToParticleInnerHelper.ConvertPositionNumber(element.position),
                feather: element.feather,
                noiseScale: element.noiseScale,
                noiseFrequency: element.noiseFrequency,
                noiseAmplitude: element.noiseAmplitude,
            });
        });
        return result;
    }
    static ConvertFieldRegion(input: FieldRegion | undefined): FieldRegionInner | undefined {
        if (input === undefined) {
            return undefined;
        }
        return {
            shape: input.shape,
            size: ParticleToParticleInnerHelper.ConvertSizeNumber(input.size),
            position: ParticleToParticleInnerHelper.ConvertPositionNumber(input.position),
        };
    }
    static ConvertArrayRippleFieldOptions(input: Array<RippleFieldOptions> | undefined): Array<RippleFieldOptionsInner> | undefined {
        if (input === undefined) {
            return input;
        }
        let result: Array<RippleFieldOptionsInner> = new Array<RippleFieldOptionsInner>();
        input.forEach((element: RippleFieldOptions) => {
            result.push({
                amplitude: element.amplitude,
                wavelength: element.wavelength,
                waveSpeed: element.waveSpeed,
                attenuation: element.attenuation,
                center: ParticleToParticleInnerHelper.ConvertPositionNumber(element.center),
                region: ParticleToParticleInnerHelper.ConvertFieldRegion(element.region),
            });
        });
        return result;
    }
    static ConvertArrayVelocityFieldOptions(input: Array<VelocityFieldOptions> | undefined): Array<VelocityFieldOptionsInner> | undefined {
        if (input === undefined) {
            return input;
        }
        let result: Array<VelocityFieldOptionsInner> = new Array<VelocityFieldOptionsInner>();
        input.forEach((element: VelocityFieldOptions) => {
            result.push({
                velocity: ParticleToParticleInnerHelper.ConvertVectorNumber(element.velocity),
                region: ParticleToParticleInnerHelper.ConvertFieldRegion(element.region),
            });
        });
        return result;
    }
}


export class ArkParticlePeer extends ArkCommonMethodPeer {
    attributeSet?: ParticleModifier
    protected constructor(peerPtr: KPointer, id: int32, name: string = "", flags: int32 = 0) {
        super(peerPtr, id, name, flags)
    }
    public static create(component?: ComponentBase, flags: int32 = 0): ArkParticlePeer {
        const peerId = PeerNode.nextId()
        const _peerPtr = ParticleHelper.ParticleConstruct(peerId, flags)
        const _peer = new ArkParticlePeer(_peerPtr, peerId, "Particle", flags)
        component?.setPeer(_peer)
        return _peer
    }
    setParticleOptionsAttribute(particles: Particles): void {
        const particlesInner = ParticleToParticleInnerHelper.ConvertParticles(particles);
        ParticleHelper.SetParticleOptions(this.peer.ptr, particlesInner);
    }
    disturbanceFieldsAttribute(value: Array<DisturbanceFieldOptions> | undefined): void {
        const valueInner = ParticleToParticleInnerHelper.ConvertArrayDisturbanceFieldOptions(value);
        ParticleHelper.SetDisturbanceFields(this.peer.ptr, valueInner);
    }
    emitterAttribute(value: Array<EmitterProperty> | undefined): void {
        const valueInner = ParticleToParticleInnerHelper.ConvertArrayEmitterProperty(value);
        ParticleHelper.SetEmitterProperty(this.peer.ptr, valueInner);
    }
    rippleFieldsAttribute(value: Array<RippleFieldOptions> | undefined): void {
        const valueInner = ParticleToParticleInnerHelper.ConvertArrayRippleFieldOptions(value);
        ParticleHelper.SetRippleFields(this.peer.ptr, valueInner);
    }
    velocityFieldsAttribute(value: Array<VelocityFieldOptions> | undefined): void {
        const valueInner = ParticleToParticleInnerHelper.ConvertArrayVelocityFieldOptions(value);
        ParticleHelper.SetVelocityFields(this.peer.ptr, valueInner);
    }
}
export class ArkParticleStyle extends ArkCommonMethodStyle implements ParticleAttribute {
    disturbanceFields_value?: Array<DisturbanceFieldOptions> | undefined
    emitter_value?: Array<EmitterProperty> | undefined
    attributeModifier_value?: AttributeModifier<ParticleAttribute> | AttributeModifier<CommonMethod> | undefined
    rippleFields_value?: Array<RippleFieldOptions> | undefined
    velocityFields_value?: Array<VelocityFieldOptions> | undefined
    public disturbanceFields(value: Array<DisturbanceFieldOptions> | undefined): this {
        return this
    }
    public emitter(value: Array<EmitterProperty> | undefined): this {
        return this
    }
    public attributeModifier(modifier: AttributeModifier<ParticleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
    public setParticleOptions(particles: Particles): this {
        return this
    }
    public rippleFields(value: Array<RippleFieldOptions> | undefined): this {
        return this
    }
    public velocityFields(value: Array<VelocityFieldOptions> | undefined): this {
        return this
    }
}

export class ArkParticleComponent extends ArkCommonMethodComponent implements ParticleAttribute {
    getPeer(): ArkParticlePeer {
        return (this.peer as ArkParticlePeer)
    }
    public setParticleOptions(particles: Particles): this {
        if (this.checkPriority("setParticleOptions")) {
            const particles_casted = particles as (Particles)
            this.getPeer()?.setParticleOptionsAttribute(particles_casted)
            return this
        }
        return this
    }
    public disturbanceFields(value: Array<DisturbanceFieldOptions> | undefined): this {
        if (this.checkPriority("disturbanceFields")) {
            const value_casted = value as (Array<DisturbanceFieldOptions> | undefined)
            this.getPeer()?.disturbanceFieldsAttribute(value_casted)
            return this
        }
        return this
    }
    public emitter(value: Array<EmitterProperty> | undefined): this {
        if (this.checkPriority("emitter")) {
            const value_casted = value as (Array<EmitterProperty> | undefined)
            this.getPeer()?.emitterAttribute(value_casted)
            return this
        }
        return this
    }
    public rippleFields(value: Array<RippleFieldOptions> | undefined): this {
        if (this.checkPriority("rippleFields")) {
            const value_casted = value as (Array<RippleFieldOptions> | undefined)
            this.getPeer()?.rippleFieldsAttribute(value_casted)
            return this
        }
        return this
    }
    public velocityFields(value: Array<VelocityFieldOptions> | undefined): this {
        if (this.checkPriority("velocityFields")) {
            const value_casted = value as (Array<VelocityFieldOptions> | undefined)
            this.getPeer()?.velocityFieldsAttribute(value_casted)
            return this
        }
        return this
    }

    public attributeModifier(modifier: AttributeModifier<ParticleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        ModifierStateManager.INSTANCE.scope(() => {
            hookParticleAttributeModifier(this, modifier);
        })
        return this;
    }
    public applyAttributesFinish(): void {
        // we call this function outside of class, so need to make it public
        super.applyAttributesFinish()
    }
}
@memo
export function ParticleImpl(
    @memo
    style: ((attributes: ParticleAttribute) => void) | undefined,
    @memo
    content_?: () => void,
) {
    const receiver = remember<ArkParticleComponent>((): ArkParticleComponent => {
        return new ArkParticleComponent()
    })
    NodeAttach<ArkParticlePeer>((): ArkParticlePeer => ArkParticlePeer.create(receiver), (peer: ArkParticlePeer): void => {
        receiver.setPeer(peer)
        style?.(receiver)
        receiver.setPeer(undefined)
        content_?.()
    })
}

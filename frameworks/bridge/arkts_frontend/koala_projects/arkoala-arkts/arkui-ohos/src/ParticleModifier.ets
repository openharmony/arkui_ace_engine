/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import { CommonMethodModifier, AttributeUpdaterFlag } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier, CommonMethod } from "./component/common"
import { ArkParticlePeer, ParticleAttribute, DisturbanceFieldOptions, EmitterProperty, Particles, RippleFieldOptions, VelocityFieldOptions } from "./component/particle"
import { PeerNode } from './PeerNode';

export class ParticleModifier extends CommonMethodModifier implements ParticleAttribute, AttributeModifier<ParticleAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ParticleAttribute): void { }
    applyPressedAttribute(instance: ParticleAttribute): void { }
    applyFocusedAttribute(instance: ParticleAttribute): void { }
    applyDisabledAttribute(instance: ParticleAttribute): void { }
    applySelectedAttribute(instance: ParticleAttribute): void { }
    _disturbanceFields_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _disturbanceFields_0_0value?: Array<DisturbanceFieldOptions> | undefined
    _emitter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _emitter_0_0value?: Array<EmitterProperty> | undefined
    _rippleFields_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _rippleFields_0_0value?: Array<RippleFieldOptions> | undefined
    _velocityFields_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _velocityFields_0_0value?: Array<VelocityFieldOptions> | undefined
    applyModifierPatch(peerNode: PeerNode): void {
        super.applyModifierPatch(peerNode)
        const peer = peerNode as ArkParticlePeer
        if (this._disturbanceFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._disturbanceFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.disturbanceFieldsAttribute((this._disturbanceFields_0_0value as Array<DisturbanceFieldOptions> | undefined));
                    this._disturbanceFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._disturbanceFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._disturbanceFields_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.disturbanceFieldsAttribute((undefined as Array<DisturbanceFieldOptions> | undefined));
                }
            }
        }
        if (this._emitter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._emitter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.emitterAttribute((this._emitter_0_0value as Array<EmitterProperty> | undefined));
                    this._emitter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._emitter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._emitter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.emitterAttribute((undefined as Array<EmitterProperty> | undefined));
                }
            }
        }
        if (this._rippleFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._rippleFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.rippleFieldsAttribute((this._rippleFields_0_0value as Array<RippleFieldOptions> | undefined));
                    this._rippleFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._rippleFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._rippleFields_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.rippleFieldsAttribute((undefined as Array<RippleFieldOptions> | undefined));
                }
            }
        }
        if (this._velocityFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (this._velocityFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.velocityFieldsAttribute((this._velocityFields_0_0value as Array<VelocityFieldOptions> | undefined));
                    this._velocityFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._velocityFields_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._velocityFields_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.velocityFieldsAttribute((undefined as Array<VelocityFieldOptions> | undefined));
                }
            }
        }
    }
    mergeModifier(value: CommonMethodModifier): void {
        super.mergeModifier(value)
        if (!(value instanceof ParticleModifier)) {
            return;
        }
        const modifier = value as ParticleModifier;
        this._state = modifier._state;
        if (modifier._disturbanceFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._disturbanceFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.disturbanceFields(modifier._disturbanceFields_0_0value);
                    break;
                }
                default: {
                    this.disturbanceFields((undefined as Array<DisturbanceFieldOptions> | undefined));
                }
            }
        }
        if (modifier._emitter_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._emitter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.emitter(modifier._emitter_0_0value);
                    break;
                }
                default: {
                    this.emitter((undefined as Array<EmitterProperty> | undefined));
                }
            }
        }
        if (modifier._rippleFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._rippleFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.rippleFields(modifier._rippleFields_0_0value);
                    break;
                }
                default: {
                    this.rippleFields((undefined as Array<RippleFieldOptions> | undefined));
                }
            }
        }
        if (modifier._velocityFields_0_flag != AttributeUpdaterFlag.INITIAL) {
            switch (modifier._velocityFields_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.velocityFields(modifier._velocityFields_0_0value);
                    break;
                }
                default: {
                    this.velocityFields((undefined as Array<VelocityFieldOptions> | undefined));
                }
            }
        }
    }
    disturbanceFields(value: Array<DisturbanceFieldOptions> | undefined): this {
        if (((this._disturbanceFields_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._disturbanceFields_0_flag = AttributeUpdaterFlag.UPDATE
            this._disturbanceFields_0_0value = value
        } else
        {
            this._disturbanceFields_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    emitter(value: Array<EmitterProperty> | undefined): this {
        if (((this._emitter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._emitter_0_flag = AttributeUpdaterFlag.UPDATE
            this._emitter_0_0value = value
        } else
        {
            this._emitter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    rippleFields(value: Array<RippleFieldOptions> | undefined): this {
        if (((this._rippleFields_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._rippleFields_0_flag = AttributeUpdaterFlag.UPDATE
            this._rippleFields_0_0value = value
        } else
        {
            this._rippleFields_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    velocityFields(value: Array<VelocityFieldOptions> | undefined): this {
        if (((this._velocityFields_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._velocityFields_0_flag = AttributeUpdaterFlag.UPDATE
            this._velocityFields_0_0value = value
        } else
        {
            this._velocityFields_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ParticleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
    setParticleOptions(particles: Particles): this {
        throw new Error("setParticleOptions Not implemented")
        return this
    }

}
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

import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSymbolSpanPeer, SymbolSpanAttribute } from './component/symbolSpan'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { Resource as global_resource_Resource } from 'global.resource'
import { ResourceColor, Resource as arkui_component_units_Resource } from './component/units'
import { Color as arkui_component_enums_Color, FontWeight } from './component/enums'
import { SymbolEffectStrategy, SymbolRenderingStrategy } from './component/symbolglyph'
export class SymbolSpanModifier implements SymbolSpanAttribute,AttributeModifier<SymbolSpanAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SymbolSpanAttribute): void { }
    applyPressedAttribute(instance: SymbolSpanAttribute): void { }
    applyFocusedAttribute(instance: SymbolSpanAttribute): void { }
    applyDisabledAttribute(instance: SymbolSpanAttribute): void { }
    applySelectedAttribute(instance: SymbolSpanAttribute): void { }
    public _fontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _fontColor_0_0value?: Array<ResourceColor> | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    public _effectStrategy_0_0value?: SymbolEffectStrategy | undefined
    public _renderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    public _key_0_0value?: string | undefined
    public _id_0_0value?: string | undefined
    applyModifierPatch(node: object): void {
        this._state.addRef()
        const peer = node as ArkSymbolSpanPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSymbolSpanPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setFontSizeAttribute((this._fontSize_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setFontSizeAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setFontColorAttribute((this._fontColor_0_0value as Array<ResourceColor> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setFontColorAttribute((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setFontWeightAttribute((this._fontWeight_0_0value as int32 | FontWeight | string | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setFontWeightAttribute((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEffectStrategyAttribute((this._effectStrategy_0_0value as SymbolEffectStrategy | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEffectStrategyAttribute((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setRenderingStrategyAttribute((this._renderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setRenderingStrategyAttribute((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setKeyAttribute((this._key_0_0value as string | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setKeyAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setIdAttribute((this._id_0_0value as string | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setIdAttribute((undefined as string | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SymbolSpanModifier): void {
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: SymbolSpanModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.fontSize(modifier._fontSize_0_0value);
                    break;
                }
                default: {
                    this.fontSize((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.fontColor(modifier._fontColor_0_0value);
                    break;
                }
                default: {
                    this.fontColor((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.fontWeight(modifier._fontWeight_0_0value);
                    break;
                }
                default: {
                    this.fontWeight((undefined as int32 | FontWeight | string | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.effectStrategy(modifier._effectStrategy_0_0value);
                    break;
                }
                default: {
                    this.effectStrategy((undefined as SymbolEffectStrategy | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.renderingStrategy(modifier._renderingStrategy_0_0value);
                    break;
                }
                default: {
                    this.renderingStrategy((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.key(modifier._key_0_0value);
                    break;
                }
                default: {
                    this.key((undefined as string | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.id(modifier._id_0_0value);
                    break;
                }
                default: {
                    this.id((undefined as string | undefined));
                }
            }
        }
    }
    fontSize(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._fontSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    fontColor(value: Array<ResourceColor> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._fontColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    fontWeight(value: int32 | FontWeight | string | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._fontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    effectStrategy(value: SymbolEffectStrategy | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._effectStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    renderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._renderingStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    key(value: string | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._key_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._key_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    id(value: string | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._id_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._id_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolSpanAttribute> | undefined): this {
        throw new Error('Not implemented')
    }
}

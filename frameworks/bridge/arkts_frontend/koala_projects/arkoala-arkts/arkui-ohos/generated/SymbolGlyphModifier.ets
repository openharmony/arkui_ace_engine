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

import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSymbolGlyphPeer, SymbolEffectStrategy, SymbolRenderingStrategy, SymbolEffect, SymbolGlyphAttribute } from './component/symbolglyph'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { Resource as global_resource_Resource } from 'global.resource'
import { ResourceColor, Resource as arkui_component_units_Resource } from './component/units'
import { Color as arkui_component_enums_Color, FontWeight } from './component/enums'
// instructive change start
import { RuntimeType, runtimeType } from "@koalaui/interop"
// instructive change end
export class SymbolGlyphModifier extends CommonMethodModifier implements SymbolGlyphAttribute,AttributeModifier<SymbolGlyphAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    // instructive change start
    constructor(src?: global_resource_Resource) {
        super()
        this._flagArray.fill(0);
        let src_type: int32 = RuntimeType.UNDEFINED
        src_type = runtimeType(src)
        if (RuntimeType.UNDEFINED != src_type) {
            this.setSymbolGlyphOptions(src)
        }
    }
    // instructive change end
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SymbolGlyphAttribute): void { }
    applyPressedAttribute(instance: SymbolGlyphAttribute): void { }
    applyFocusedAttribute(instance: SymbolGlyphAttribute): void { }
    applyDisabledAttribute(instance: SymbolGlyphAttribute): void { }
    applySelectedAttribute(instance: SymbolGlyphAttribute): void { }
    // instructive change start
    public _setSymbolGlyphOptions_flag:  AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    public _setSymbolGlyphOptions0_value?: global_resource_Resource | undefined
    // instructive change end
    public _fontSize_0_0value?: double | string | global_resource_Resource | undefined
    public _fontColor_0_0value?: Array<ResourceColor> | undefined
    public _fontWeight_0_0value?: int32 | FontWeight | string | undefined
    public _effectStrategy_0_0value?: SymbolEffectStrategy | undefined
    public _renderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    public _symbolEffect_0_0value?: SymbolEffect | undefined
    public _minFontScale_0_0value?: double | global_resource_Resource | undefined
    public _maxFontScale_0_0value?: double | global_resource_Resource | undefined
    public _symbolEffect_1_0value?: SymbolEffect | undefined
    public _symbolEffect_1_1value?: boolean | undefined
    public _symbolEffect_2_0value?: SymbolEffect | undefined
    public _symbolEffect_2_1value?: int32 | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSymbolGlyphPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSymbolGlyphPeer, flagArray: Uint8Array): void {
        // instructive change start
        if (this._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (this._setSymbolGlyphOptions_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSymbolGlyphOptionsAttribute((this._setSymbolGlyphOptions0_value as global_resource_Resource | undefined))
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.RESET
                    break
                }
                default: {
                    this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.INITIAL
                    peer.setSymbolGlyphOptionsAttribute(undefined)
                }
            }
        }
        // instructive change end
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
                    peer.setSymbolEffect0Attribute((this._symbolEffect_0_0value as SymbolEffect | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setSymbolEffect0Attribute((undefined as SymbolEffect | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setMinFontScaleAttribute((this._minFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setMinFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setMaxFontScaleAttribute((this._maxFontScale_0_0value as double | global_resource_Resource | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setMaxFontScaleAttribute((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setSymbolEffect1Attribute((this._symbolEffect_1_0value as SymbolEffect | undefined), (this._symbolEffect_1_1value as boolean | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setSymbolEffect1Attribute((undefined as SymbolEffect | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setSymbolEffect2Attribute((this._symbolEffect_2_0value as SymbolEffect | undefined), (this._symbolEffect_2_1value as int32 | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setSymbolEffect2Attribute((undefined as SymbolEffect | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SymbolGlyphModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: SymbolGlyphModifier, flagArray: Uint8Array): void {
        // instructive change start
        if (modifier._setSymbolGlyphOptions_flag !== AttributeUpdaterFlag.INITIAL) {
            switch (modifier._setSymbolGlyphOptions_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.setSymbolGlyphOptions(modifier._setSymbolGlyphOptions0_value)
                    break
                }
                default: {
                    this.setSymbolGlyphOptions(undefined)
                }
            }
        }
        // instructive change end
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
                    this.symbolEffect(modifier._symbolEffect_0_0value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.minFontScale(modifier._minFontScale_0_0value);
                    break;
                }
                default: {
                    this.minFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.maxFontScale(modifier._maxFontScale_0_0value);
                    break;
                }
                default: {
                    this.maxFontScale((undefined as double | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.symbolEffect(modifier._symbolEffect_1_0value, modifier._symbolEffect_1_1value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined), (undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.symbolEffect(modifier._symbolEffect_2_0value, modifier._symbolEffect_2_1value);
                    break;
                }
                default: {
                    this.symbolEffect((undefined as SymbolEffect | undefined), (undefined as int32 | undefined));
                }
            }
        }
    }
    // instructive change start
    setSymbolGlyphOptions(value: global_resource_Resource | undefined): this {
        if (this._setSymbolGlyphOptions_flag === AttributeUpdaterFlag.INITIAL ||
            this._setSymbolGlyphOptions0_value !== value || !Type.of(value).isPrimitive()) {
            this._setSymbolGlyphOptions0_value = value
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.UPDATE
        } else {
            this._setSymbolGlyphOptions_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    // instructive change end
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
    symbolEffect(value: SymbolEffect | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._symbolEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    minFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._minFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    maxFontScale(value: double | global_resource_Resource | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._maxFontScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, isActive: boolean | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true) || ((this._symbolEffect_1_1value) !== (isActive))) {
            this._flagArray[8] = 1
            this._symbolEffect_1_0value = symbolEffect
            this._symbolEffect_1_1value = isActive
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    symbolEffect(symbolEffect: SymbolEffect | undefined, triggerValue: int32 | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true) || ((this._symbolEffect_2_1value) !== (triggerValue))) {
            this._flagArray[9] = 1
            this._symbolEffect_2_0value = symbolEffect
            this._symbolEffect_2_1value = triggerValue
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

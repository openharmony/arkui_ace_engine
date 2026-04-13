/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

import { SecurityComponentMethodModifier } from './SecurityComponentMethodModifier'
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkSaveButtonPeer, SaveButtonCallback, SaveButtonOnClickResult, SaveButtonAttribute } from './component/saveButton'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { SecurityComponentMethod } from './component/securityComponent'
import { ClickEvent } from './component/common'
import { BusinessError } from '@ohos.base'
import { Resource as arkui_component_units_Resource, Dimension, SizeOptions, BorderRadiuses, ResourceColor } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color, FontWeight } from './component/enums'
import { SymbolRenderingStrategy } from './component/symbolglyph'
export class SaveButtonModifier extends SecurityComponentMethodModifier implements SaveButtonAttribute,AttributeModifier<SaveButtonAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    private _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: SaveButtonAttribute): void { }
    applyPressedAttribute(instance: SaveButtonAttribute): void { }
    applyFocusedAttribute(instance: SaveButtonAttribute): void { }
    applyDisabledAttribute(instance: SaveButtonAttribute): void { }
    applySelectedAttribute(instance: SaveButtonAttribute): void { }
    public _onClick_0_0value?: SaveButtonCallback | undefined
    public _setIcon_0_0value?: arkui_component_units_Resource | undefined
    public _setText_0_0value?: string | arkui_component_units_Resource | undefined
    public _iconSize_0_0value?: Dimension | SizeOptions | undefined
    public _iconBorderRadius_0_0value?: Dimension | BorderRadiuses | undefined
    public _stateEffect_0_0value?: boolean | undefined
    public _userCancelEvent_0_0value?: boolean | undefined
    public _symbolIconColor_0_0value?: Array<ResourceColor> | undefined
    public _symbolRenderingStrategy_0_0value?: SymbolRenderingStrategy | undefined
    public _symbolFontWeight_0_0value?: int32 | FontWeight | string | arkui_component_units_Resource | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkSaveButtonPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkSaveButtonPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnClickAttribute((this._onClick_0_0value as SaveButtonCallback | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnClickAttribute((undefined as SaveButtonCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setSetIconAttribute((this._setIcon_0_0value as arkui_component_units_Resource | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setSetIconAttribute((undefined as arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setSetTextAttribute((this._setText_0_0value as string | arkui_component_units_Resource | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setSetTextAttribute((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setIconSizeAttribute((this._iconSize_0_0value as Dimension | SizeOptions | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setIconSizeAttribute((undefined as Dimension | SizeOptions | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setIconBorderRadiusAttribute((this._iconBorderRadius_0_0value as Dimension | BorderRadiuses | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setIconBorderRadiusAttribute((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setStateEffectAttribute((this._stateEffect_0_0value as boolean | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setStateEffectAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setUserCancelEventAttribute((this._userCancelEvent_0_0value as boolean | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setUserCancelEventAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setSymbolIconColorAttribute((this._symbolIconColor_0_0value as Array<ResourceColor> | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setSymbolIconColorAttribute((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setSymbolRenderingStrategyAttribute((this._symbolRenderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setSymbolRenderingStrategyAttribute((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setSymbolFontWeightAttribute((this._symbolFontWeight_0_0value as int32 | FontWeight | string | arkui_component_units_Resource | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setSymbolFontWeightAttribute((undefined as int32 | FontWeight | string | arkui_component_units_Resource | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: SaveButtonModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: SaveButtonModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onClick((modifier._onClick_0_0value as SaveButtonCallback | undefined));
                    break;
                }
                default: {
                    this.onClick((undefined as SaveButtonCallback | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.setIcon((modifier._setIcon_0_0value as arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.setIcon((undefined as arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.setText((modifier._setText_0_0value as string | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.setText((undefined as string | arkui_component_units_Resource | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.iconSize((modifier._iconSize_0_0value as Dimension | SizeOptions | undefined));
                    break;
                }
                default: {
                    this.iconSize((undefined as Dimension | SizeOptions | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.iconBorderRadius((modifier._iconBorderRadius_0_0value as Dimension | BorderRadiuses | undefined));
                    break;
                }
                default: {
                    this.iconBorderRadius((undefined as Dimension | BorderRadiuses | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.stateEffect((modifier._stateEffect_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.stateEffect((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.userCancelEvent((modifier._userCancelEvent_0_0value as boolean | undefined));
                    break;
                }
                default: {
                    this.userCancelEvent((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.symbolIconColor((modifier._symbolIconColor_0_0value as Array<ResourceColor> | undefined));
                    break;
                }
                default: {
                    this.symbolIconColor((undefined as Array<ResourceColor> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.symbolRenderingStrategy((modifier._symbolRenderingStrategy_0_0value as SymbolRenderingStrategy | undefined));
                    break;
                }
                default: {
                    this.symbolRenderingStrategy((undefined as SymbolRenderingStrategy | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.symbolFontWeight((modifier._symbolFontWeight_0_0value as int32 | FontWeight | string | arkui_component_units_Resource | undefined));
                    break;
                }
                default: {
                    this.symbolFontWeight((undefined as int32 | FontWeight | string | arkui_component_units_Resource | undefined));
                }
            }
        }
    }
    onClick(value: SaveButtonCallback | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onClick_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    setIcon(value: arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._setIcon_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    setText(value: string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._setText_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    iconSize(value: Dimension | SizeOptions | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._iconSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    iconBorderRadius(value: Dimension | BorderRadiuses | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._iconBorderRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    stateEffect(value: boolean | undefined): this {
        if (((this._flagArray[5]) == (0)) || ((this._stateEffect_0_0value) !== (value))) {
            this._flagArray[5] = 1
            this._stateEffect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    userCancelEvent(value: boolean | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._userCancelEvent_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._userCancelEvent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    symbolIconColor(value: Array<ResourceColor> | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._symbolIconColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    symbolRenderingStrategy(value: SymbolRenderingStrategy | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._symbolRenderingStrategy_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    symbolFontWeight(value: int32 | FontWeight | string | arkui_component_units_Resource | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._symbolFontWeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<SaveButtonAttribute> | AttributeModifier<SecurityComponentMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

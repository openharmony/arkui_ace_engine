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
import { AttributeModifier, ContentModifier, hookToggleContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkTogglePeer, ToggleConfiguration, SwitchStyle, ToggleAttribute } from './component/toggle'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource } from './component/units'
import { Color as arkui_component_enums_Color } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class ToggleModifier extends CommonMethodModifier implements ToggleAttribute,AttributeModifier<ToggleAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ToggleAttribute): void { }
    applyPressedAttribute(instance: ToggleAttribute): void { }
    applyFocusedAttribute(instance: ToggleAttribute): void { }
    applyDisabledAttribute(instance: ToggleAttribute): void { }
    applySelectedAttribute(instance: ToggleAttribute): void { }
    public _onChange_0_0value?: ((isSelected: boolean) => void) | undefined
    public _contentModifier_0_0value?: ContentModifier<ToggleConfiguration> | undefined
    public _selectedColor_0_0value?: ResourceColor | undefined
    public _switchPointColor_0_0value?: ResourceColor | undefined
    public _switchStyle_0_0value?: SwitchStyle | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkTogglePeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkTogglePeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setOnChangeAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    hookToggleContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<ToggleConfiguration> | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    hookToggleContentModifier(peer, (undefined as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setSwitchPointColorAttribute((this._switchPointColor_0_0value as ResourceColor | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setSwitchPointColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSwitchStyleAttribute((this._switchStyle_0_0value as SwitchStyle | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSwitchStyleAttribute((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ToggleModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: ToggleModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<ToggleConfiguration> | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.switchPointColor(modifier._switchPointColor_0_0value);
                    break;
                }
                default: {
                    this.switchPointColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.switchStyle(modifier._switchStyle_0_0value);
                    break;
                }
                default: {
                    this.switchStyle((undefined as SwitchStyle | undefined));
                }
            }
        }
    }
    onChange(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    switchPointColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._switchPointColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    switchStyle(value: SwitchStyle | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._switchStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ToggleAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

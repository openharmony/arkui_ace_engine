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
import { AttributeModifier, ContentModifier, hookCheckBoxContentModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkCheckboxPeer, OnCheckboxChangeCallback, CheckBoxConfiguration, CheckboxAttribute } from './component/checkbox'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, MarkStyle } from './component/units'
import { Color as arkui_component_enums_Color, CheckBoxShape } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
export class CheckboxModifier extends CommonMethodModifier implements CheckboxAttribute,AttributeModifier<CheckboxAttribute> {
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
    applyNormalAttribute(instance: CheckboxAttribute): void { }
    applyPressedAttribute(instance: CheckboxAttribute): void { }
    applyFocusedAttribute(instance: CheckboxAttribute): void { }
    applyDisabledAttribute(instance: CheckboxAttribute): void { }
    applySelectedAttribute(instance: CheckboxAttribute): void { }
    public _select_0_0value?: boolean | Bindable<boolean> | undefined
    public _selectedColor_0_0value?: ResourceColor | undefined
    public _shape_0_0value?: CheckBoxShape | undefined
    public _unselectedColor_0_0value?: ResourceColor | undefined
    public _mark_0_0value?: MarkStyle | undefined
    public _onChange_0_0value?: OnCheckboxChangeCallback | undefined
    public _contentModifier_0_0value?: ContentModifier<CheckBoxConfiguration> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkCheckboxPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkCheckboxPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSelectAttribute((this._select_0_0value as boolean | Bindable<boolean> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setSelectAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setShapeAttribute((this._shape_0_0value as CheckBoxShape | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setShapeAttribute((undefined as CheckBoxShape | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setUnselectedColorAttribute((this._unselectedColor_0_0value as ResourceColor | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setUnselectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setMarkAttribute((this._mark_0_0value as MarkStyle | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setMarkAttribute((undefined as MarkStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as OnCheckboxChangeCallback | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnChangeAttribute((undefined as OnCheckboxChangeCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    hookCheckBoxContentModifier(peer, (this._contentModifier_0_0value as ContentModifier<CheckBoxConfiguration> | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    hookCheckBoxContentModifier(peer, (undefined as ContentModifier<CheckBoxConfiguration> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: CheckboxModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: CheckboxModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.select(modifier._select_0_0value);
                    break;
                }
                default: {
                    this.select((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
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
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.shape(modifier._shape_0_0value);
                    break;
                }
                default: {
                    this.shape((undefined as CheckBoxShape | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.unselectedColor(modifier._unselectedColor_0_0value);
                    break;
                }
                default: {
                    this.unselectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.mark(modifier._mark_0_0value);
                    break;
                }
                default: {
                    this.mark((undefined as MarkStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onChange(modifier._onChange_0_0value);
                    break;
                }
                default: {
                    this.onChange((undefined as OnCheckboxChangeCallback | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.contentModifier(modifier._contentModifier_0_0value);
                    break;
                }
                default: {
                    this.contentModifier((undefined as ContentModifier<CheckBoxConfiguration> | undefined));
                }
            }
        }
    }
    select(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._select_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    shape(value: CheckBoxShape | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._shape_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    unselectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._unselectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    mark(value: MarkStyle | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._mark_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onChange(value: OnCheckboxChangeCallback | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._contentModifier_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<CheckboxAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

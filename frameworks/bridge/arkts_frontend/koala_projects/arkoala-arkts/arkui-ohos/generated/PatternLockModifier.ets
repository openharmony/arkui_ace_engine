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
import { ArkPatternLockPeer, CircleStyleOptions, PatternLockAttribute } from './component/patternLock'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
import { Length, Resource as arkui_component_units_Resource, ResourceColor } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { Color as arkui_component_enums_Color } from './component/enums'
export class PatternLockModifier extends CommonMethodModifier implements PatternLockAttribute,AttributeModifier<PatternLockAttribute> {
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
    applyNormalAttribute(instance: PatternLockAttribute): void { }
    applyPressedAttribute(instance: PatternLockAttribute): void { }
    applyFocusedAttribute(instance: PatternLockAttribute): void { }
    applyDisabledAttribute(instance: PatternLockAttribute): void { }
    applySelectedAttribute(instance: PatternLockAttribute): void { }
    public _sideLength_0_0value?: Length | undefined
    public _circleRadius_0_0value?: Length | undefined
    public _backgroundColor_0_0value?: ResourceColor | undefined
    public _regularColor_0_0value?: ResourceColor | undefined
    public _selectedColor_0_0value?: ResourceColor | undefined
    public _activeColor_0_0value?: ResourceColor | undefined
    public _pathColor_0_0value?: ResourceColor | undefined
    public _pathStrokeWidth_0_0value?: double | string | undefined
    public _onPatternComplete_0_0value?: arkui_component_common_Callback<Array<int32>, void> | undefined
    public _autoReset_0_0value?: boolean | undefined
    public _onDotConnect_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    public _activateCircleStyle_0_0value?: CircleStyleOptions | undefined
    public _skipUnselectedPoint_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkPatternLockPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkPatternLockPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSideLengthAttribute((this._sideLength_0_0value as Length | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setSideLengthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setCircleRadiusAttribute((this._circleRadius_0_0value as Length | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setCircleRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setRegularColorAttribute((this._regularColor_0_0value as ResourceColor | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setRegularColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setActiveColorAttribute((this._activeColor_0_0value as ResourceColor | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setActiveColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setPathColorAttribute((this._pathColor_0_0value as ResourceColor | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setPathColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setPathStrokeWidthAttribute((this._pathStrokeWidth_0_0value as double | string | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setPathStrokeWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnPatternCompleteAttribute((this._onPatternComplete_0_0value as arkui_component_common_Callback<Array<int32>, void> | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnPatternCompleteAttribute((undefined as arkui_component_common_Callback<Array<int32>, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setAutoResetAttribute((this._autoReset_0_0value as boolean | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setAutoResetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnDotConnectAttribute((this._onDotConnect_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnDotConnectAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setActivateCircleStyleAttribute((this._activateCircleStyle_0_0value as CircleStyleOptions | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setActivateCircleStyleAttribute((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setSkipUnselectedPointAttribute((this._skipUnselectedPoint_0_0value as boolean | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setSkipUnselectedPointAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PatternLockModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: PatternLockModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.sideLength(modifier._sideLength_0_0value);
                    break;
                }
                default: {
                    this.sideLength((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.circleRadius(modifier._circleRadius_0_0value);
                    break;
                }
                default: {
                    this.circleRadius((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.regularColor(modifier._regularColor_0_0value);
                    break;
                }
                default: {
                    this.regularColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
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
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.activeColor(modifier._activeColor_0_0value);
                    break;
                }
                default: {
                    this.activeColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.pathColor(modifier._pathColor_0_0value);
                    break;
                }
                default: {
                    this.pathColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.pathStrokeWidth(modifier._pathStrokeWidth_0_0value);
                    break;
                }
                default: {
                    this.pathStrokeWidth((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onPatternComplete(modifier._onPatternComplete_0_0value);
                    break;
                }
                default: {
                    this.onPatternComplete((undefined as arkui_component_common_Callback<Array<int32>, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.autoReset(modifier._autoReset_0_0value);
                    break;
                }
                default: {
                    this.autoReset((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onDotConnect(modifier._onDotConnect_0_0value);
                    break;
                }
                default: {
                    this.onDotConnect((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.activateCircleStyle(modifier._activateCircleStyle_0_0value);
                    break;
                }
                default: {
                    this.activateCircleStyle((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.skipUnselectedPoint(modifier._skipUnselectedPoint_0_0value);
                    break;
                }
                default: {
                    this.skipUnselectedPoint((undefined as boolean | undefined));
                }
            }
        }
    }
    sideLength(value: Length | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._sideLength_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    circleRadius(value: Length | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._circleRadius_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    regularColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._regularColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    activeColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._activeColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    pathColor(value: ResourceColor | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._pathColor_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    pathStrokeWidth(value: double | string | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._pathStrokeWidth_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._pathStrokeWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onPatternComplete(value: arkui_component_common_Callback<Array<int32>, void> | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onPatternComplete_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    autoReset(value: boolean | undefined): this {
        if (((this._flagArray[9]) == (0)) || ((this._autoReset_0_0value) !== (value))) {
            this._flagArray[9] = 1
            this._autoReset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onDotConnect(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onDotConnect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._activateCircleStyle_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    skipUnselectedPoint(value: boolean | undefined): this {
        if (((this._flagArray[12]) == (0)) || ((this._skipUnselectedPoint_0_0value) !== (value))) {
            this._flagArray[12] = 1
            this._skipUnselectedPoint_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

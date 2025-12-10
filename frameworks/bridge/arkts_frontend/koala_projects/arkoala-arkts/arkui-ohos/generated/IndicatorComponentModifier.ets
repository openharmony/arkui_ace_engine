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
import { ArkIndicatorComponentPeer, IndicatorComponentAttribute } from './component/indicatorcomponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
import { DotIndicator, DigitIndicator } from './component/swiper'
export class IndicatorComponentModifier extends CommonMethodModifier implements IndicatorComponentAttribute,AttributeModifier<IndicatorComponentAttribute> {
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
    applyNormalAttribute(instance: IndicatorComponentAttribute): void { }
    applyPressedAttribute(instance: IndicatorComponentAttribute): void { }
    applyFocusedAttribute(instance: IndicatorComponentAttribute): void { }
    applyDisabledAttribute(instance: IndicatorComponentAttribute): void { }
    applySelectedAttribute(instance: IndicatorComponentAttribute): void { }
    public _initialIndex_0_0value?: int32 | undefined
    public _count_0_0value?: int32 | undefined
    public _style_0_0value?: DotIndicator | DigitIndicator | undefined
    public _loop_0_0value?: boolean | undefined
    public _vertical_0_0value?: boolean | undefined
    public _onChange_0_0value?: arkui_component_common_Callback<int32, void> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkIndicatorComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkIndicatorComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setInitialIndexAttribute((this._initialIndex_0_0value as int32 | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setInitialIndexAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setCountAttribute((this._count_0_0value as int32 | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setCountAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setStyleAttribute((this._style_0_0value as DotIndicator | DigitIndicator | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setStyleAttribute((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setLoopAttribute((this._loop_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setLoopAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setVerticalAttribute((this._vertical_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setVerticalAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnChangeAttribute((this._onChange_0_0value as arkui_component_common_Callback<int32, void> | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnChangeAttribute((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: IndicatorComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: IndicatorComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.initialIndex(modifier._initialIndex_0_0value);
                    break;
                }
                default: {
                    this.initialIndex((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.count(modifier._count_0_0value);
                    break;
                }
                default: {
                    this.count((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.style(modifier._style_0_0value);
                    break;
                }
                default: {
                    this.style((undefined as DotIndicator | DigitIndicator | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.loop(modifier._loop_0_0value);
                    break;
                }
                default: {
                    this.loop((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.vertical(modifier._vertical_0_0value);
                    break;
                }
                default: {
                    this.vertical((undefined as boolean | undefined));
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
                    this.onChange((undefined as arkui_component_common_Callback<int32, void> | undefined));
                }
            }
        }
    }
    initialIndex(value: int32 | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._initialIndex_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._initialIndex_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    count(value: int32 | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._count_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._count_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    style(value: DotIndicator | DigitIndicator | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._style_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    loop(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._loop_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._loop_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    vertical(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._vertical_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._vertical_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onChange(value: arkui_component_common_Callback<int32, void> | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<IndicatorComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

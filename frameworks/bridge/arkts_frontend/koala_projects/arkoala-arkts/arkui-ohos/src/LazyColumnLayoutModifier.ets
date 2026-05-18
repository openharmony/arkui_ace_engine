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

import { CommonMethod, OnVisibleIndexesChangeCallback } from './component/common'
import { LengthMetrics as arkui_Graphics_LengthMetrics } from 'arkui.Graphics'
import { HorizontalAlign } from './component/enums'
import {
    ArkLazyColumnLayoutPeer,
    LazyColumnLayoutAttribute,
} from '@ohos.arkui.components.ArkLazyColumnLayout'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'

export class LazyColumnLayoutModifier extends CommonMethodModifier implements
    LazyColumnLayoutAttribute, AttributeModifier<LazyColumnLayoutAttribute> {
    _LazyColumnLayout_addr: ArrayBuffer = new ArrayBuffer(4096)
    _LazyColumnLayout_flagArray: Uint8Array = new Uint8Array(this._LazyColumnLayout_addr)

    constructor() {
        super()
        this._LazyColumnLayout_flagArray.fill(0)
    }

    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LazyColumnLayoutAttribute): void { }
    applyPressedAttribute(instance: LazyColumnLayoutAttribute): void { }
    applyFocusedAttribute(instance: LazyColumnLayoutAttribute): void { }
    applyDisabledAttribute(instance: LazyColumnLayoutAttribute): void { }
    applySelectedAttribute(instance: LazyColumnLayoutAttribute): void { }
    applyHoveredAttribute(instance: LazyColumnLayoutAttribute): void { }

    public _LazyColumnLayout_space_0_0value?: arkui_Graphics_LengthMetrics | undefined
    public _LazyColumnLayout_alignItems_0_0value?: HorizontalAlign | undefined
    public _LazyColumnLayout_onVisibleIndexesChange_0_0value?: OnVisibleIndexesChangeCallback | undefined

    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkLazyColumnLayoutPeer
        const flagArray = this._LazyColumnLayout_flagArray
        this.applyModifierPatch0(peer, flagArray)
    }

    applyModifierPatch0(peer: ArkLazyColumnLayoutPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSpaceAttribute(this._LazyColumnLayout_space_0_0value as
                        arkui_Graphics_LengthMetrics | undefined)
                    flagArray[0] = 2
                    break
                }
                case 3: {
                    flagArray[0] = 2
                    break
                }
                default: {
                    flagArray[0] = 0
                    peer.setSpaceAttribute(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setAlignItemsAttribute(this._LazyColumnLayout_alignItems_0_0value as
                        HorizontalAlign | undefined)
                    flagArray[1] = 2
                    break
                }
                case 3: {
                    flagArray[1] = 2
                    break
                }
                default: {
                    flagArray[1] = 0
                    peer.setAlignItemsAttribute(undefined as HorizontalAlign | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnVisibleIndexesChangeAttribute(this._LazyColumnLayout_onVisibleIndexesChange_0_0value as
                        OnVisibleIndexesChangeCallback | undefined)
                    flagArray[2] = 2
                    break
                }
                case 3: {
                    flagArray[2] = 2
                    break
                }
                default: {
                    flagArray[2] = 0
                    peer.setOnVisibleIndexesChangeAttribute(undefined as OnVisibleIndexesChangeCallback | undefined)
                }
            }
        }
    }

    mergeModifier(modifier: LazyColumnLayoutModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state
        const flagArray = modifier._LazyColumnLayout_flagArray
        this.mergeModifier0(modifier, flagArray)
    }

    mergeModifier0(modifier: LazyColumnLayoutModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.space(modifier._LazyColumnLayout_space_0_0value as
                        arkui_Graphics_LengthMetrics | undefined)
                    break
                }
                default: {
                    this.space(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.alignItems(modifier._LazyColumnLayout_alignItems_0_0value as
                        HorizontalAlign | undefined)
                    break
                }
                default: {
                    this.alignItems(undefined as HorizontalAlign | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onVisibleIndexesChange(modifier._LazyColumnLayout_onVisibleIndexesChange_0_0value as
                        OnVisibleIndexesChangeCallback | undefined)
                    break
                }
                default: {
                    this.onVisibleIndexesChange(undefined as OnVisibleIndexesChangeCallback | undefined)
                }
            }
        }
    }

    setLazyColumnLayoutOptions(): this {
        return this
    }

    space(value: arkui_Graphics_LengthMetrics | undefined): this {
        if ((this._LazyColumnLayout_flagArray[0] == 0) || true) {
            this._LazyColumnLayout_flagArray[0] = 1
            this._LazyColumnLayout_space_0_0value = value
            this._state.fireChange()
        } else {
            this._LazyColumnLayout_flagArray[0] = 3
        }
        return this
    }

    alignItems(value: HorizontalAlign | undefined): this {
        if ((this._LazyColumnLayout_flagArray[1] == 0) || true) {
            this._LazyColumnLayout_flagArray[1] = 1
            this._LazyColumnLayout_alignItems_0_0value = value
            this._state.fireChange()
        } else {
            this._LazyColumnLayout_flagArray[1] = 3
        }
        return this
    }

    onVisibleIndexesChange(callback_: OnVisibleIndexesChangeCallback | undefined): this {
        if ((this._LazyColumnLayout_flagArray[2] == 0) || true) {
            this._LazyColumnLayout_flagArray[2] = 1
            this._LazyColumnLayout_onVisibleIndexesChange_0_0value = callback_
            this._state.fireChange()
        } else {
            this._LazyColumnLayout_flagArray[2] = 3
        }
        return this
    }

    public attributeModifier(
        modifier: AttributeModifier<LazyColumnLayoutAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        return this
    }
}

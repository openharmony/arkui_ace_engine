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
import { ItemFillPolicy } from './component/units'
import {
    ArkLazyVWaterFlowLayoutPeer,
    LazyWaterFlowLayoutAttribute,
    LazyVWaterFlowLayoutAttribute,
} from '@ohos.arkui.components.ArkLazyWaterFlowLayout'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'

export class LazyVWaterFlowLayoutModifier extends CommonMethodModifier implements
    LazyVWaterFlowLayoutAttribute, AttributeModifier<LazyVWaterFlowLayoutAttribute> {
    private lazyVWaterFlowLayoutAddr: ArrayBuffer = new ArrayBuffer(4096)
    private lazyVWaterFlowLayoutFlagArray: Uint8Array = new Uint8Array(this.lazyVWaterFlowLayoutAddr)

    constructor() {
        super()
        this.lazyVWaterFlowLayoutFlagArray.fill(0)
    }

    public isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }
    applyPressedAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }
    applyFocusedAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }
    applyDisabledAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }
    applySelectedAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }
    applyHoveredAttribute(instance: LazyVWaterFlowLayoutAttribute): void { }

    private rowsGapValue?: arkui_Graphics_LengthMetrics | undefined
    private columnsGapValue?: arkui_Graphics_LengthMetrics | undefined
    private columnsTemplateValue?: string | ItemFillPolicy | undefined
    private onVisibleIndexesChangeValue?: OnVisibleIndexesChangeCallback | undefined

    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkLazyVWaterFlowLayoutPeer
        const flagArray = this.lazyVWaterFlowLayoutFlagArray
        this.applyModifierPatch0(peer, flagArray)
    }

    applyModifierPatch0(peer: ArkLazyVWaterFlowLayoutPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
              case 1: {
                    peer.setRowsGapAttribute(this.rowsGapValue as
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
                    peer.setRowsGapAttribute(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
              case 1: {
                    peer.setColumnsGapAttribute(this.columnsGapValue as
                        arkui_Graphics_LengthMetrics | undefined)
                    flagArray[1] = 2
                    break
                }
              case 3: {
                    flagArray[1] = 2
                    break
                }
              default: {
                    flagArray[1] = 0
                    peer.setColumnsGapAttribute(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
              case 1: {
                    peer.setColumnsTemplateAttribute(this.columnsTemplateValue as
                        string | ItemFillPolicy | undefined)
                    flagArray[2] = 2
                    break
                }
              case 3: {
                    flagArray[2] = 2
                    break
                }
              default: {
                    flagArray[2] = 0
                    peer.setColumnsTemplateAttribute(undefined as string | ItemFillPolicy | undefined)
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
              case 1: {
                    peer.setOnVisibleIndexesChangeAttribute(
                        this.onVisibleIndexesChangeValue as OnVisibleIndexesChangeCallback | undefined)
                    flagArray[3] = 2
                    break
                }
              case 3: {
                    flagArray[3] = 2
                    break
                }
              default: {
                    flagArray[3] = 0
                    peer.setOnVisibleIndexesChangeAttribute(undefined as OnVisibleIndexesChangeCallback | undefined)
                }
            }
        }
    }

    mergeModifier(modifier: LazyVWaterFlowLayoutModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state
        const flagArray = modifier.lazyVWaterFlowLayoutFlagArray
        this.mergeModifier0(modifier, flagArray)
    }

    mergeModifier0(modifier: LazyVWaterFlowLayoutModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
              case 1:
              case 3: {
                    this.rowsGap(modifier.rowsGapValue as
                        arkui_Graphics_LengthMetrics | undefined)
                    break
                }
              default: {
                    this.rowsGap(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
              case 1:
              case 3: {
                    this.columnsGap(modifier.columnsGapValue as
                        arkui_Graphics_LengthMetrics | undefined)
                    break
                }
              default: {
                    this.columnsGap(undefined as arkui_Graphics_LengthMetrics | undefined)
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
              case 1:
              case 3: {
                    this.columnsTemplate(modifier.columnsTemplateValue as
                        string | ItemFillPolicy | undefined)
                    break
                }
              default: {
                    this.columnsTemplate(undefined as string | ItemFillPolicy | undefined)
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
              case 1:
              case 3: {
                    this.onVisibleIndexesChange(modifier.onVisibleIndexesChangeValue as
                        OnVisibleIndexesChangeCallback | undefined)
                    break
                }
              default: {
                    this.onVisibleIndexesChange(undefined as OnVisibleIndexesChangeCallback | undefined)
                }
            }
        }
    }

    setLazyVWaterFlowLayoutOptions(): this {
        return this
    }

    rowsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        if ((this.lazyVWaterFlowLayoutFlagArray[0] == 0) || true) {
            this.lazyVWaterFlowLayoutFlagArray[0] = 1
            this.rowsGapValue = value
            this._state.fireChange()
        } else {
            this.lazyVWaterFlowLayoutFlagArray[0] = 3
        }
        return this
    }

    columnsGap(value: arkui_Graphics_LengthMetrics | undefined): this {
        if ((this.lazyVWaterFlowLayoutFlagArray[1] == 0) || true) {
            this.lazyVWaterFlowLayoutFlagArray[1] = 1
            this.columnsGapValue = value
            this._state.fireChange()
        } else {
            this.lazyVWaterFlowLayoutFlagArray[1] = 3
        }
        return this
    }

    columnsTemplate(value: string | ItemFillPolicy | undefined): this {
        if ((this.lazyVWaterFlowLayoutFlagArray[2] == 0) || (this.columnsTemplateValue !== value)) {
            this.lazyVWaterFlowLayoutFlagArray[2] = 1
            this.columnsTemplateValue = value
            this._state.fireChange()
        } else {
            this.lazyVWaterFlowLayoutFlagArray[2] = 3
        }
        return this
    }

    onVisibleIndexesChange(callback_: OnVisibleIndexesChangeCallback | undefined): this {
        if ((this.lazyVWaterFlowLayoutFlagArray[3] == 0) || true) {
            this.lazyVWaterFlowLayoutFlagArray[3] = 1
            this.onVisibleIndexesChangeValue = callback_
            this._state.fireChange()
        } else {
            this.lazyVWaterFlowLayoutFlagArray[3] = 3
        }
        return this
    }

    public attributeModifier(
        modifier: AttributeModifier<LazyVWaterFlowLayoutAttribute> | AttributeModifier<LazyWaterFlowLayoutAttribute> |
            AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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
import { ArkGridItemPeer, GridItemAttribute } from './component/gridItem'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Bindable } from './component/common'
export class GridItemModifier extends CommonMethodModifier implements GridItemAttribute,AttributeModifier<GridItemAttribute> {
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
    applyNormalAttribute(instance: GridItemAttribute): void { }
    applyPressedAttribute(instance: GridItemAttribute): void { }
    applyFocusedAttribute(instance: GridItemAttribute): void { }
    applyDisabledAttribute(instance: GridItemAttribute): void { }
    applySelectedAttribute(instance: GridItemAttribute): void { }
    public _rowStart_0_0value?: int32 | undefined
    public _rowEnd_0_0value?: int32 | undefined
    public _columnStart_0_0value?: int32 | undefined
    public _columnEnd_0_0value?: int32 | undefined
    public _selectable_0_0value?: boolean | undefined
    public _selected_0_0value?: boolean | Bindable<boolean> | undefined
    public _onSelect_0_0value?: ((isSelected: boolean) => void) | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkGridItemPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkGridItemPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setRowStartAttribute((this._rowStart_0_0value as int32 | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setRowStartAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setRowEndAttribute((this._rowEnd_0_0value as int32 | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setRowEndAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setColumnStartAttribute((this._columnStart_0_0value as int32 | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setColumnStartAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setColumnEndAttribute((this._columnEnd_0_0value as int32 | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setColumnEndAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setSelectableAttribute((this._selectable_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setSelectableAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setSelectedAttribute((this._selected_0_0value as boolean | Bindable<boolean> | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setSelectedAttribute((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnSelectAttribute((this._onSelect_0_0value as ((isSelected: boolean) => void) | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnSelectAttribute((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: GridItemModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: GridItemModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.rowStart(modifier._rowStart_0_0value);
                    break;
                }
                default: {
                    this.rowStart((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.rowEnd(modifier._rowEnd_0_0value);
                    break;
                }
                default: {
                    this.rowEnd((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.columnStart(modifier._columnStart_0_0value);
                    break;
                }
                default: {
                    this.columnStart((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.columnEnd(modifier._columnEnd_0_0value);
                    break;
                }
                default: {
                    this.columnEnd((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.selectable(modifier._selectable_0_0value);
                    break;
                }
                default: {
                    this.selectable((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.selected(modifier._selected_0_0value);
                    break;
                }
                default: {
                    this.selected((undefined as boolean | Bindable<boolean> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onSelect(modifier._onSelect_0_0value);
                    break;
                }
                default: {
                    this.onSelect((undefined as ((isSelected: boolean) => void) | undefined));
                }
            }
        }
    }
    rowStart(value: int32 | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._rowStart_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._rowStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    rowEnd(value: int32 | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._rowEnd_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._rowEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    columnStart(value: int32 | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._columnStart_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._columnStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    columnEnd(value: int32 | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._columnEnd_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._columnEnd_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    selectable(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._selectable_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._selectable_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._selected_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onSelect(value: ((isSelected: boolean) => void) | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onSelect_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<GridItemAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

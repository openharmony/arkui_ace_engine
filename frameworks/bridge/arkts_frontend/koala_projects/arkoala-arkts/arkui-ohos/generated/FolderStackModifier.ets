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
import { ArkFolderStackPeer, OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam, FolderStackAttribute } from './component/folderStack'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { Alignment } from './component/enums'
export class FolderStackModifier extends CommonMethodModifier implements FolderStackAttribute,AttributeModifier<FolderStackAttribute> {
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
    applyNormalAttribute(instance: FolderStackAttribute): void { }
    applyPressedAttribute(instance: FolderStackAttribute): void { }
    applyFocusedAttribute(instance: FolderStackAttribute): void { }
    applyDisabledAttribute(instance: FolderStackAttribute): void { }
    applySelectedAttribute(instance: FolderStackAttribute): void { }
    public _alignContent_0_0value?: Alignment | undefined
    public _onFolderStateChange_0_0value?: OnFoldStatusChangeCallback | undefined
    public _onHoverStatusChange_0_0value?: OnHoverStatusChangeCallback | undefined
    public _enableAnimation_0_0value?: boolean | undefined
    public _autoHalfFold_0_0value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkFolderStackPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkFolderStackPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setOnFolderStateChangeAttribute((this._onFolderStateChange_0_0value as OnFoldStatusChangeCallback | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setOnFolderStateChangeAttribute((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setOnHoverStatusChangeAttribute((this._onHoverStatusChange_0_0value as OnHoverStatusChangeCallback | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setOnHoverStatusChangeAttribute((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setEnableAnimationAttribute((this._enableAnimation_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setEnableAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setAutoHalfFoldAttribute((this._autoHalfFold_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setAutoHalfFoldAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FolderStackModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: FolderStackModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.onFolderStateChange(modifier._onFolderStateChange_0_0value);
                    break;
                }
                default: {
                    this.onFolderStateChange((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.onHoverStatusChange(modifier._onHoverStatusChange_0_0value);
                    break;
                }
                default: {
                    this.onHoverStatusChange((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.enableAnimation(modifier._enableAnimation_0_0value);
                    break;
                }
                default: {
                    this.enableAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.autoHalfFold(modifier._autoHalfFold_0_0value);
                    break;
                }
                default: {
                    this.autoHalfFold((undefined as boolean | undefined));
                }
            }
        }
    }
    alignContent(value: Alignment | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._alignContent_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._onFolderStateChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._onHoverStatusChange_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    enableAnimation(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._enableAnimation_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._enableAnimation_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    autoHalfFold(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._autoHalfFold_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._autoHalfFold_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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

import { CommonMethodModifier } from "./CommonMethodModifier"
import { ModifierState } from './CommonModifier'
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkFolderStackPeer, OnFoldStatusChangeCallback, OnFoldStatusChangeInfo, OnHoverStatusChangeCallback, HoverEventParam, FolderStackAttribute } from "./component/folderStack"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { Alignment } from "./component/enums"
export class FolderStackModifier extends CommonMethodModifier implements FolderStackAttribute,AttributeModifier<FolderStackAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: FolderStackAttribute): void { }
    applyPressedAttribute(instance: FolderStackAttribute): void { }
    applyFocusedAttribute(instance: FolderStackAttribute): void { }
    applyDisabledAttribute(instance: FolderStackAttribute): void { }
    applySelectedAttribute(instance: FolderStackAttribute): void { }
    _alignContent_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _alignContent_0_0value?: Alignment | undefined
    _onFolderStateChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFolderStateChange_0_0value?: OnFoldStatusChangeCallback | undefined
    _onHoverStatusChange_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onHoverStatusChange_0_0value?: OnHoverStatusChangeCallback | undefined
    _enableAnimation_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _enableAnimation_0_0value?: boolean | undefined
    _autoHalfFold_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoHalfFold_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkFolderStackPeer;
        if (this._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAlignContentAttribute((this._alignContent_0_0value as Alignment | undefined));
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._alignContent_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAlignContentAttribute((undefined as Alignment | undefined));
                }
            }
        }
        if (this._onFolderStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFolderStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFolderStateChangeAttribute((this._onFolderStateChange_0_0value as OnFoldStatusChangeCallback | undefined));
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFolderStateChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFolderStateChangeAttribute((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (this._onHoverStatusChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onHoverStatusChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnHoverStatusChangeAttribute((this._onHoverStatusChange_0_0value as OnHoverStatusChangeCallback | undefined));
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnHoverStatusChangeAttribute((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (this._enableAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._enableAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnableAnimationAttribute((this._enableAnimation_0_0value as boolean | undefined));
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._enableAnimation_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnableAnimationAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._autoHalfFold_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoHalfFold_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoHalfFoldAttribute((this._autoHalfFold_0_0value as boolean | undefined));
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoHalfFold_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoHalfFoldAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FolderStackModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._alignContent_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._alignContent_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.alignContent(modifier._alignContent_0_0value);
                    break;
                }
                default: {
                    this.alignContent((undefined as Alignment | undefined));
                }
            }
        }
        if (modifier._onFolderStateChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFolderStateChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFolderStateChange(modifier._onFolderStateChange_0_0value);
                    break;
                }
                default: {
                    this.onFolderStateChange((undefined as OnFoldStatusChangeCallback | undefined));
                }
            }
        }
        if (modifier._onHoverStatusChange_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onHoverStatusChange_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onHoverStatusChange(modifier._onHoverStatusChange_0_0value);
                    break;
                }
                default: {
                    this.onHoverStatusChange((undefined as OnHoverStatusChangeCallback | undefined));
                }
            }
        }
        if (modifier._enableAnimation_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._enableAnimation_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.enableAnimation(modifier._enableAnimation_0_0value);
                    break;
                }
                default: {
                    this.enableAnimation((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._autoHalfFold_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoHalfFold_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._alignContent_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.UPDATE
            this._alignContent_0_0value = value
        } else
        {
            this._alignContent_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFolderStateChange(value: OnFoldStatusChangeCallback | undefined): this {
        if (((this._onFolderStateChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFolderStateChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFolderStateChange_0_0value = value
        } else
        {
            this._onFolderStateChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onHoverStatusChange(value: OnHoverStatusChangeCallback | undefined): this {
        if (((this._onHoverStatusChange_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.UPDATE
            this._onHoverStatusChange_0_0value = value
        } else
        {
            this._onHoverStatusChange_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    enableAnimation(value: boolean | undefined): this {
        if (((this._enableAnimation_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._enableAnimation_0_0value) !== (value)))
        {
            this._enableAnimation_0_flag = AttributeUpdaterFlag.UPDATE
            this._enableAnimation_0_0value = value
        } else
        {
            this._enableAnimation_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoHalfFold(value: boolean | undefined): this {
        if (((this._autoHalfFold_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoHalfFold_0_0value) !== (value)))
        {
            this._autoHalfFold_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoHalfFold_0_0value = value
        } else
        {
            this._autoHalfFold_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FolderStackAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

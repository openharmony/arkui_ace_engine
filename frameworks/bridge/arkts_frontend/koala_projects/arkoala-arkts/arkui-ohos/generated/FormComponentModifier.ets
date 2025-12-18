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
import { ArkFormComponentPeer, FormSize, FormDimension, FormCallbackInfo, ErrorInformation, FormComponentAttribute } from './component/formComponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, Callback as arkui_component_common_Callback } from './component/common'
import { Visibility } from './component/enums'
import { VoidCallback } from './component/units'
export class FormComponentModifier extends CommonMethodModifier implements FormComponentAttribute,AttributeModifier<FormComponentAttribute> {
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
    applyNormalAttribute(instance: FormComponentAttribute): void { }
    applyPressedAttribute(instance: FormComponentAttribute): void { }
    applyFocusedAttribute(instance: FormComponentAttribute): void { }
    applyDisabledAttribute(instance: FormComponentAttribute): void { }
    applySelectedAttribute(instance: FormComponentAttribute): void { }
    public _size_0_0value?: FormSize
    public _moduleName_0_0value?: string | undefined
    public _dimension_0_0value?: FormDimension | undefined
    public _allowUpdate_0_0value?: boolean | undefined
    public _visibility_0_0value?: Visibility | undefined
    public _onAcquired_0_0value?: arkui_component_common_Callback<FormCallbackInfo, void> | undefined
    public _onError_0_0value?: arkui_component_common_Callback<ErrorInformation, void> | undefined
    public _onRouter_0_0value?: arkui_component_common_Callback<Object, void> | undefined
    public _onUninstall_0_0value?: arkui_component_common_Callback<FormCallbackInfo, void> | undefined
    public _onLoad_0_0value?: VoidCallback | undefined
    public _onUpdate_0_0value?: arkui_component_common_Callback<FormCallbackInfo, void> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkFormComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkFormComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setSizeAttribute((this._size_0_0value as FormSize));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setModuleNameAttribute((this._moduleName_0_0value as string | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setModuleNameAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setDimensionAttribute((this._dimension_0_0value as FormDimension | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setDimensionAttribute((undefined as FormDimension | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setAllowUpdateAttribute((this._allowUpdate_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setAllowUpdateAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setVisibilityAttribute((this._visibility_0_0value as Visibility | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setVisibilityAttribute((undefined as Visibility | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setOnAcquiredAttribute((this._onAcquired_0_0value as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setOnAcquiredAttribute((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setOnErrorAttribute((this._onError_0_0value as arkui_component_common_Callback<ErrorInformation, void> | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setOnErrorAttribute((undefined as arkui_component_common_Callback<ErrorInformation, void> | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setOnRouterAttribute((this._onRouter_0_0value as arkui_component_common_Callback<Object, void> | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setOnRouterAttribute((undefined as arkui_component_common_Callback<Object, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnUninstallAttribute((this._onUninstall_0_0value as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnUninstallAttribute((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnUpdateAttribute((this._onUpdate_0_0value as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnUpdateAttribute((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FormComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: FormComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.moduleName(modifier._moduleName_0_0value);
                    break;
                }
                default: {
                    this.moduleName((undefined as string | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.dimension(modifier._dimension_0_0value);
                    break;
                }
                default: {
                    this.dimension((undefined as FormDimension | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.allowUpdate(modifier._allowUpdate_0_0value);
                    break;
                }
                default: {
                    this.allowUpdate((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.visibility(modifier._visibility_0_0value);
                    break;
                }
                default: {
                    this.visibility((undefined as Visibility | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.onAcquired(modifier._onAcquired_0_0value);
                    break;
                }
                default: {
                    this.onAcquired((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as arkui_component_common_Callback<ErrorInformation, void> | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.onRouter(modifier._onRouter_0_0value);
                    break;
                }
                default: {
                    this.onRouter((undefined as arkui_component_common_Callback<Object, void> | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onUninstall(modifier._onUninstall_0_0value);
                    break;
                }
                default: {
                    this.onUninstall((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onUpdate(modifier._onUpdate_0_0value);
                    break;
                }
                default: {
                    this.onUpdate((undefined as arkui_component_common_Callback<FormCallbackInfo, void> | undefined));
                }
            }
        }
    }
    size(value: FormSize): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._size_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    moduleName(value: string | undefined): this {
        if (((this._flagArray[1]) == (0)) || ((this._moduleName_0_0value) !== (value))) {
            this._flagArray[1] = 1
            this._moduleName_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    dimension(value: FormDimension | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._dimension_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    allowUpdate(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._allowUpdate_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._allowUpdate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    visibility(value: Visibility | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._visibility_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    onAcquired(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._onAcquired_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    onError(value: arkui_component_common_Callback<ErrorInformation, void> | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true)) {
            this._flagArray[6] = 1
            this._onError_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    onRouter(value: arkui_component_common_Callback<Object, void> | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._onRouter_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onUninstall(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onUninstall_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onLoad_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onUpdate(value: arkui_component_common_Callback<FormCallbackInfo, void> | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onUpdate_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

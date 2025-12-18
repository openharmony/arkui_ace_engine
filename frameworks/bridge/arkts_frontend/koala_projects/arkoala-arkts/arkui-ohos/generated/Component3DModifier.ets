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
import { ArkComponent3DPeer, Component3DAttribute } from './component/component3d'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { ResourceStr as arkui_component_units_ResourceStr, Resource as arkui_component_units_Resource, Dimension } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
export class Component3DModifier extends CommonMethodModifier implements Component3DAttribute,AttributeModifier<Component3DAttribute> {
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
    applyNormalAttribute(instance: Component3DAttribute): void { }
    applyPressedAttribute(instance: Component3DAttribute): void { }
    applyFocusedAttribute(instance: Component3DAttribute): void { }
    applyDisabledAttribute(instance: Component3DAttribute): void { }
    applySelectedAttribute(instance: Component3DAttribute): void { }
    public _environment_0_0value?: arkui_component_units_ResourceStr | undefined
    public _shader_0_0value?: arkui_component_units_ResourceStr | undefined
    public _shaderImageTexture_0_0value?: arkui_component_units_ResourceStr | undefined
    public _shaderInputBuffer_0_0value?: Array<double> | undefined
    public _renderWidth_0_0value?: Dimension | undefined
    public _renderHeight_0_0value?: Dimension | undefined
    public _customRender_0_0value?: arkui_component_units_ResourceStr | undefined
    public _customRender_0_1value?: boolean | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkComponent3DPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkComponent3DPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setEnvironmentAttribute((this._environment_0_0value as arkui_component_units_ResourceStr | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setEnvironmentAttribute((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setShaderAttribute((this._shader_0_0value as arkui_component_units_ResourceStr | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setShaderAttribute((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setShaderImageTextureAttribute((this._shaderImageTexture_0_0value as arkui_component_units_ResourceStr | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setShaderImageTextureAttribute((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setShaderInputBufferAttribute((this._shaderInputBuffer_0_0value as Array<double> | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setShaderInputBufferAttribute((undefined as Array<double> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setRenderWidthAttribute((this._renderWidth_0_0value as Dimension | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setRenderWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setRenderHeightAttribute((this._renderHeight_0_0value as Dimension | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setRenderHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setCustomRenderAttribute((this._customRender_0_0value as arkui_component_units_ResourceStr | undefined), (this._customRender_0_1value as boolean | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setCustomRenderAttribute((undefined as arkui_component_units_ResourceStr | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: Component3DModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: Component3DModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.environment(modifier._environment_0_0value);
                    break;
                }
                default: {
                    this.environment((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.shader(modifier._shader_0_0value);
                    break;
                }
                default: {
                    this.shader((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.shaderImageTexture(modifier._shaderImageTexture_0_0value);
                    break;
                }
                default: {
                    this.shaderImageTexture((undefined as arkui_component_units_ResourceStr | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.shaderInputBuffer(modifier._shaderInputBuffer_0_0value);
                    break;
                }
                default: {
                    this.shaderInputBuffer((undefined as Array<double> | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.renderWidth(modifier._renderWidth_0_0value);
                    break;
                }
                default: {
                    this.renderWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.renderHeight(modifier._renderHeight_0_0value);
                    break;
                }
                default: {
                    this.renderHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.customRender(modifier._customRender_0_0value, modifier._customRender_0_1value);
                    break;
                }
                default: {
                    this.customRender((undefined as arkui_component_units_ResourceStr | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    environment(value: arkui_component_units_ResourceStr | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._environment_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    shader(value: arkui_component_units_ResourceStr | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._shader_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    shaderImageTexture(value: arkui_component_units_ResourceStr | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._shaderImageTexture_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    shaderInputBuffer(value: Array<double> | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._shaderInputBuffer_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._shaderInputBuffer_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    renderWidth(value: Dimension | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._renderWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    renderHeight(value: Dimension | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._renderHeight_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    customRender(uri: arkui_component_units_ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        if (((this._flagArray[6]) == (0)) || (true) || ((this._customRender_0_1value) !== (selfRenderUpdate))) {
            this._flagArray[6] = 1
            this._customRender_0_0value = uri
            this._customRender_0_1value = selfRenderUpdate
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

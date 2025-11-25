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
import { ArkComponent3DPeer, Component3DAttribute } from "./component/component3d"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { ResourceStr, Dimension } from "./component/units"
import { Resource } from "global.resource"
export class Component3DModifier extends CommonMethodModifier implements Component3DAttribute,AttributeModifier<Component3DAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: Component3DAttribute): void { }
    applyPressedAttribute(instance: Component3DAttribute): void { }
    applyFocusedAttribute(instance: Component3DAttribute): void { }
    applyDisabledAttribute(instance: Component3DAttribute): void { }
    applySelectedAttribute(instance: Component3DAttribute): void { }
    _environment_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _environment_0_0value?: ResourceStr | undefined
    _shader_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shader_0_0value?: ResourceStr | undefined
    _shaderImageTexture_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shaderImageTexture_0_0value?: ResourceStr | undefined
    _shaderInputBuffer_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _shaderInputBuffer_0_0value?: Array<number> | undefined
    _renderWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderWidth_0_0value?: Dimension | undefined
    _renderHeight_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _renderHeight_0_0value?: Dimension | undefined
    _customRender_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _customRender_0_0value?: ResourceStr | undefined
    _customRender_0_1value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkComponent3DPeer;
        if (this._environment_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._environment_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setEnvironmentAttribute((this._environment_0_0value as ResourceStr | undefined));
                    this._environment_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._environment_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._environment_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setEnvironmentAttribute((undefined as ResourceStr | undefined));
                }
            }
        }
        if (this._shader_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shader_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShaderAttribute((this._shader_0_0value as ResourceStr | undefined));
                    this._shader_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shader_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shader_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShaderAttribute((undefined as ResourceStr | undefined));
                }
            }
        }
        if (this._shaderImageTexture_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shaderImageTexture_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShaderImageTextureAttribute((this._shaderImageTexture_0_0value as ResourceStr | undefined));
                    this._shaderImageTexture_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shaderImageTexture_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shaderImageTexture_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShaderImageTextureAttribute((undefined as ResourceStr | undefined));
                }
            }
        }
        if (this._shaderInputBuffer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._shaderInputBuffer_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setShaderInputBufferAttribute((this._shaderInputBuffer_0_0value as Array<number> | undefined));
                    this._shaderInputBuffer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._shaderInputBuffer_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._shaderInputBuffer_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setShaderInputBufferAttribute((undefined as Array<number> | undefined));
                }
            }
        }
        if (this._renderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderWidthAttribute((this._renderWidth_0_0value as Dimension | undefined));
                    this._renderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderWidthAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._renderHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._renderHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRenderHeightAttribute((this._renderHeight_0_0value as Dimension | undefined));
                    this._renderHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._renderHeight_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._renderHeight_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRenderHeightAttribute((undefined as Dimension | undefined));
                }
            }
        }
        if (this._customRender_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._customRender_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCustomRenderAttribute((this._customRender_0_0value as ResourceStr | undefined), (this._customRender_0_1value as boolean | undefined));
                    this._customRender_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._customRender_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._customRender_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCustomRenderAttribute((undefined as ResourceStr | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: Component3DModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._environment_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._environment_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.environment(modifier._environment_0_0value);
                    break;
                }
                default: {
                    this.environment((undefined as ResourceStr | undefined));
                }
            }
        }
        if (modifier._shader_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shader_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shader(modifier._shader_0_0value);
                    break;
                }
                default: {
                    this.shader((undefined as ResourceStr | undefined));
                }
            }
        }
        if (modifier._shaderImageTexture_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shaderImageTexture_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shaderImageTexture(modifier._shaderImageTexture_0_0value);
                    break;
                }
                default: {
                    this.shaderImageTexture((undefined as ResourceStr | undefined));
                }
            }
        }
        if (modifier._shaderInputBuffer_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._shaderInputBuffer_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.shaderInputBuffer(modifier._shaderInputBuffer_0_0value);
                    break;
                }
                default: {
                    this.shaderInputBuffer((undefined as Array<number> | undefined));
                }
            }
        }
        if (modifier._renderWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderWidth(modifier._renderWidth_0_0value);
                    break;
                }
                default: {
                    this.renderWidth((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._renderHeight_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._renderHeight_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.renderHeight(modifier._renderHeight_0_0value);
                    break;
                }
                default: {
                    this.renderHeight((undefined as Dimension | undefined));
                }
            }
        }
        if (modifier._customRender_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._customRender_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.customRender(modifier._customRender_0_0value, modifier._customRender_0_1value);
                    break;
                }
                default: {
                    this.customRender((undefined as ResourceStr | undefined), (undefined as boolean | undefined));
                }
            }
        }
    }
    environment(value: ResourceStr | undefined): this {
        if (((this._environment_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._environment_0_flag = AttributeUpdaterFlag.UPDATE
            this._environment_0_0value = value
        } else
        {
            this._environment_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    shader(value: ResourceStr | undefined): this {
        if (((this._shader_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._shader_0_flag = AttributeUpdaterFlag.UPDATE
            this._shader_0_0value = value
        } else
        {
            this._shader_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    shaderImageTexture(value: ResourceStr | undefined): this {
        if (((this._shaderImageTexture_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._shaderImageTexture_0_flag = AttributeUpdaterFlag.UPDATE
            this._shaderImageTexture_0_0value = value
        } else
        {
            this._shaderImageTexture_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    shaderInputBuffer(value: Array<number> | undefined): this {
        if (((this._shaderInputBuffer_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._shaderInputBuffer_0_0value) !== (value)))
        {
            this._shaderInputBuffer_0_flag = AttributeUpdaterFlag.UPDATE
            this._shaderInputBuffer_0_0value = value
        } else
        {
            this._shaderInputBuffer_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderWidth(value: Dimension | undefined): this {
        if (((this._renderWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderWidth_0_0value = value
        } else
        {
            this._renderWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    renderHeight(value: Dimension | undefined): this {
        if (((this._renderHeight_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._renderHeight_0_flag = AttributeUpdaterFlag.UPDATE
            this._renderHeight_0_0value = value
        } else
        {
            this._renderHeight_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    customRender(uri: ResourceStr | undefined, selfRenderUpdate: boolean | undefined): this {
        if (((this._customRender_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true) || ((this._customRender_0_1value) !== (selfRenderUpdate)))
        {
            this._customRender_0_flag = AttributeUpdaterFlag.UPDATE
            this._customRender_0_0value = uri
            this._customRender_0_1value = selfRenderUpdate
        } else
        {
            this._customRender_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<Component3DAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

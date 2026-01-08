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
import { ArkFormComponentPeer, FormSize, FormDimension, FormCallbackInfo, ErrorInformation, RouterCallbackInfo, FormComponentAttribute } from "./component/formComponent"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { Visibility } from "./component/enums"
import { VoidCallback } from "./component/units"
export class FormComponentModifier extends CommonMethodModifier implements FormComponentAttribute,AttributeModifier<FormComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: FormComponentAttribute): void { }
    applyPressedAttribute(instance: FormComponentAttribute): void { }
    applyFocusedAttribute(instance: FormComponentAttribute): void { }
    applyDisabledAttribute(instance: FormComponentAttribute): void { }
    applySelectedAttribute(instance: FormComponentAttribute): void { }
    _size_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _size_0_0value?: FormSize | undefined
    _moduleName_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _moduleName_0_0value?: string | undefined
    _dimension_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _dimension_0_0value?: FormDimension | undefined
    _allowUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _allowUpdate_0_0value?: boolean | undefined
    _visibility_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _visibility_0_0value?: Visibility | undefined
    _onAcquired_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onAcquired_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    _onError_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onError_0_0value?: ((value0: ErrorInformation) => void) | undefined
    _onRouter_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRouter_0_0value?: ((value0: RouterCallbackInfo) => void) | undefined
    _onUninstall_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUninstall_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    _onLoad_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onLoad_0_0value?: VoidCallback | undefined
    _onUpdate_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onUpdate_0_0value?: ((value0: FormCallbackInfo) => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkFormComponentPeer;
        if (this._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSizeAttribute((this._size_0_0value as FormSize | undefined));
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._size_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._size_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSizeAttribute((undefined as FormSize | undefined));
                }
            }
        }
        if (this._moduleName_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._moduleName_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setModuleNameAttribute((this._moduleName_0_0value as string | undefined));
                    this._moduleName_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._moduleName_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._moduleName_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setModuleNameAttribute((undefined as string | undefined));
                }
            }
        }
        if (this._dimension_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._dimension_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDimensionAttribute((this._dimension_0_0value as FormDimension | undefined));
                    this._dimension_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._dimension_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._dimension_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDimensionAttribute((undefined as FormDimension | undefined));
                }
            }
        }
        if (this._allowUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._allowUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAllowUpdateAttribute((this._allowUpdate_0_0value as boolean | undefined));
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._allowUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAllowUpdateAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setVisibilityAttribute((this._visibility_0_0value as Visibility | undefined));
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._visibility_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._visibility_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setVisibilityAttribute((undefined as Visibility | undefined));
                }
            }
        }
        if (this._onAcquired_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onAcquired_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnAcquiredAttribute((this._onAcquired_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onAcquired_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onAcquired_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onAcquired_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnAcquiredAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (this._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnErrorAttribute((this._onError_0_0value as ((value0: ErrorInformation) => void) | undefined));
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onError_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onError_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnErrorAttribute((undefined as ((value0: ErrorInformation) => void) | undefined));
                }
            }
        }
        if (this._onRouter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRouter_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRouterAttribute((this._onRouter_0_0value as ((value0: RouterCallbackInfo) => void) | undefined));
                    this._onRouter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRouter_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRouter_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRouterAttribute((undefined as ((value0: RouterCallbackInfo) => void) | undefined));
                }
            }
        }
        if (this._onUninstall_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUninstall_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUninstallAttribute((this._onUninstall_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onUninstall_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUninstall_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUninstall_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUninstallAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (this._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnLoadAttribute((this._onLoad_0_0value as VoidCallback | undefined));
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onLoad_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnLoadAttribute((undefined as VoidCallback | undefined));
                }
            }
        }
        if (this._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnUpdateAttribute((this._onUpdate_0_0value as ((value0: FormCallbackInfo) => void) | undefined));
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onUpdate_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnUpdateAttribute((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: FormComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._size_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._size_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.size(modifier._size_0_0value);
                    break;
                }
                default: {
                    this.size((undefined as FormSize | undefined));
                }
            }
        }
        if (modifier._moduleName_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._moduleName_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.moduleName(modifier._moduleName_0_0value);
                    break;
                }
                default: {
                    this.moduleName((undefined as string | undefined));
                }
            }
        }
        if (modifier._dimension_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._dimension_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.dimension(modifier._dimension_0_0value);
                    break;
                }
                default: {
                    this.dimension((undefined as FormDimension | undefined));
                }
            }
        }
        if (modifier._allowUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._allowUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.allowUpdate(modifier._allowUpdate_0_0value);
                    break;
                }
                default: {
                    this.allowUpdate((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._visibility_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._visibility_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.visibility(modifier._visibility_0_0value);
                    break;
                }
                default: {
                    this.visibility((undefined as Visibility | undefined));
                }
            }
        }
        if (modifier._onAcquired_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onAcquired_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onAcquired(modifier._onAcquired_0_0value);
                    break;
                }
                default: {
                    this.onAcquired((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onError_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onError_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onError(modifier._onError_0_0value);
                    break;
                }
                default: {
                    this.onError((undefined as ((value0: ErrorInformation) => void) | undefined));
                }
            }
        }
        if (modifier._onRouter_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRouter_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRouter(modifier._onRouter_0_0value);
                    break;
                }
                default: {
                    this.onRouter((undefined as ((value0: RouterCallbackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onUninstall_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUninstall_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUninstall(modifier._onUninstall_0_0value);
                    break;
                }
                default: {
                    this.onUninstall((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
        if (modifier._onLoad_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onLoad_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onLoad(modifier._onLoad_0_0value);
                    break;
                }
                default: {
                    this.onLoad((undefined as VoidCallback | undefined));
                }
            }
        }
        if (modifier._onUpdate_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onUpdate_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onUpdate(modifier._onUpdate_0_0value);
                    break;
                }
                default: {
                    this.onUpdate((undefined as ((value0: FormCallbackInfo) => void) | undefined));
                }
            }
        }
    }
    size(value: FormSize | undefined): this {
        if (((this._size_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._size_0_flag = AttributeUpdaterFlag.UPDATE
            this._size_0_0value = value
            this._state.fireChange()
        } else
        {
            this._size_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    moduleName(value: string | undefined): this {
        if (((this._moduleName_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._moduleName_0_0value) !== (value)))
        {
            this._moduleName_0_flag = AttributeUpdaterFlag.UPDATE
            this._moduleName_0_0value = value
            this._state.fireChange()
        } else
        {
            this._moduleName_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    dimension(value: FormDimension | undefined): this {
        if (((this._dimension_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._dimension_0_flag = AttributeUpdaterFlag.UPDATE
            this._dimension_0_0value = value
            this._state.fireChange()
        } else
        {
            this._dimension_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    allowUpdate(value: boolean | undefined): this {
        if (((this._allowUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._allowUpdate_0_0value) !== (value)))
        {
            this._allowUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._allowUpdate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._allowUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    visibility(value: Visibility | undefined): this {
        if (((this._visibility_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._visibility_0_flag = AttributeUpdaterFlag.UPDATE
            this._visibility_0_0value = value
            this._state.fireChange()
        } else
        {
            this._visibility_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onAcquired(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onAcquired_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onAcquired_0_flag = AttributeUpdaterFlag.UPDATE
            this._onAcquired_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onAcquired_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onError(value: ((value0: ErrorInformation) => void) | undefined): this {
        if (((this._onError_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onError_0_flag = AttributeUpdaterFlag.UPDATE
            this._onError_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onError_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRouter(value: ((value0: RouterCallbackInfo) => void) | undefined): this {
        if (((this._onRouter_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRouter_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRouter_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRouter_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUninstall(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onUninstall_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUninstall_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUninstall_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onUninstall_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onLoad(value: VoidCallback | undefined): this {
        if (((this._onLoad_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.UPDATE
            this._onLoad_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onLoad_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onUpdate(value: ((value0: FormCallbackInfo) => void) | undefined): this {
        if (((this._onUpdate_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.UPDATE
            this._onUpdate_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onUpdate_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<FormComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

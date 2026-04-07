/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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
import { AttributeModifier, extractors } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkDepthComponentPeer, DepthCameraParams, DepthLightParams, DepthComponentAttribute } from './component/depthComponent'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod, PixelMap, ScaleOptions } from './component/common'
import { ResourceStr, Resource as arkui_component_units_Resource, Position, Edges, LocalizedEdges } from './component/units'
import { Resource as global_resource_Resource } from 'global.resource'
import { default as image } from '@ohos.multimedia.image'
export class DepthComponentModifier extends CommonMethodModifier implements DepthComponentAttribute,AttributeModifier<DepthComponentAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState;
    _addr: ArrayBuffer = new ArrayBuffer(4096);
    private _flagArray: Uint8Array = new Uint8Array(this._addr);
    constructor() {
        super();
        this._flagArray.fill(0);
    }
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: DepthComponentAttribute): void { }
    applyPressedAttribute(instance: DepthComponentAttribute): void { }
    applyFocusedAttribute(instance: DepthComponentAttribute): void { }
    applyDisabledAttribute(instance: DepthComponentAttribute): void { }
    applySelectedAttribute(instance: DepthComponentAttribute): void { }
    public _depthMap_0_0value?: ResourceStr | PixelMap
    public _camera_0_0value?: DepthCameraParams
    public _light_0_0value?: DepthLightParams
    public _backgroundOffset_0_0value?: Position | Edges | LocalizedEdges
    public _backgroundScale_0_0value?: ScaleOptions
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkDepthComponentPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkDepthComponentPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setDepthMapAttribute((this._depthMap_0_0value as ResourceStr | PixelMap));
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
                    peer.setCameraAttribute((this._camera_0_0value as DepthCameraParams));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setLightAttribute((this._light_0_0value as DepthLightParams));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setBackgroundOffsetAttribute((this._backgroundOffset_0_0value as Position | Edges | LocalizedEdges));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setBackgroundScaleAttribute((this._backgroundScale_0_0value as ScaleOptions));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                }
            }
        }
    }
    mergeModifier(modifier: DepthComponentModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: DepthComponentModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.depthMap((modifier._depthMap_0_0value as ResourceStr | PixelMap));
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
                    this.camera((modifier._camera_0_0value as DepthCameraParams));
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.light((modifier._light_0_0value as DepthLightParams));
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.backgroundOffset((modifier._backgroundOffset_0_0value as Position | Edges | LocalizedEdges));
                    break;
                }
                default: {
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.backgroundScale((modifier._backgroundScale_0_0value as ScaleOptions));
                    break;
                }
                default: {
                }
            }
        }
    }
    depthMap(value: ResourceStr | PixelMap): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._depthMap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    camera(value: DepthCameraParams): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._camera_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    light(value: DepthLightParams): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._light_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    backgroundOffset(value: Position | Edges | LocalizedEdges): this {
        if (((this._flagArray[3]) == (0)) || (true)) {
            this._flagArray[3] = 1
            this._backgroundOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    backgroundScale(value: ScaleOptions): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._backgroundScale_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<DepthComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

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
import { ArkImageAnimatorPeer, ImageFrameInfo, ImageAnimatorAttribute } from './component/imageAnimator'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
import { CommonMethod } from './component/common'
import { AnimationStatus, FillMode } from './component/enums'
export class ImageAnimatorModifier extends CommonMethodModifier implements ImageAnimatorAttribute,AttributeModifier<ImageAnimatorAttribute> {
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
    applyNormalAttribute(instance: ImageAnimatorAttribute): void { }
    applyPressedAttribute(instance: ImageAnimatorAttribute): void { }
    applyFocusedAttribute(instance: ImageAnimatorAttribute): void { }
    applyDisabledAttribute(instance: ImageAnimatorAttribute): void { }
    applySelectedAttribute(instance: ImageAnimatorAttribute): void { }
    public _images_0_0value?: Array<ImageFrameInfo> | undefined
    public _state_0_0value?: AnimationStatus | undefined
    public _duration_0_0value?: int32 | undefined
    public _reverse_0_0value?: boolean | undefined
    public _fixedSize_0_0value?: boolean | undefined
    public _fillMode_0_0value?: FillMode | undefined
    public _iterations_0_0value?: int32 | undefined
    public _monitorInvisibleArea_0_0value?: boolean | undefined
    public _onStart_0_0value?: (() => void) | undefined
    public _onPause_0_0value?: (() => void) | undefined
    public _onRepeat_0_0value?: (() => void) | undefined
    public _onCancel_0_0value?: (() => void) | undefined
    public _onFinish_0_0value?: (() => void) | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkImageAnimatorPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkImageAnimatorPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setImagesAttribute((this._images_0_0value as Array<ImageFrameInfo> | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setImagesAttribute((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setStateAttribute((this._state_0_0value as AnimationStatus | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setStateAttribute((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setDurationAttribute((this._duration_0_0value as int32 | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setDurationAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setReverseAttribute((this._reverse_0_0value as boolean | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setReverseAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setFixedSizeAttribute((this._fixedSize_0_0value as boolean | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setFixedSizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setFillModeAttribute((this._fillMode_0_0value as FillMode | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setFillModeAttribute((undefined as FillMode | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setIterationsAttribute((this._iterations_0_0value as int32 | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setIterationsAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setMonitorInvisibleAreaAttribute((this._monitorInvisibleArea_0_0value as boolean | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setMonitorInvisibleAreaAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setOnPauseAttribute((this._onPause_0_0value as (() => void) | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setOnPauseAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setOnRepeatAttribute((this._onRepeat_0_0value as (() => void) | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setOnRepeatAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setOnCancelAttribute((this._onCancel_0_0value as (() => void) | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setOnCancelAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    flagArray[12] = 2;
                    break;
                }
                case 3: {
                    flagArray[12] = 2;
                    break;
                }
                default: {
                    flagArray[12] = 0;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageAnimatorModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: ImageAnimatorModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.images(modifier._images_0_0value);
                    break;
                }
                default: {
                    this.images((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.state(modifier._state_0_0value);
                    break;
                }
                default: {
                    this.state((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.reverse(modifier._reverse_0_0value);
                    break;
                }
                default: {
                    this.reverse((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.fixedSize(modifier._fixedSize_0_0value);
                    break;
                }
                default: {
                    this.fixedSize((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.fillMode(modifier._fillMode_0_0value);
                    break;
                }
                default: {
                    this.fillMode((undefined as FillMode | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.iterations(modifier._iterations_0_0value);
                    break;
                }
                default: {
                    this.iterations((undefined as int32 | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.monitorInvisibleArea(modifier._monitorInvisibleArea_0_0value);
                    break;
                }
                default: {
                    this.monitorInvisibleArea((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.onPause(modifier._onPause_0_0value);
                    break;
                }
                default: {
                    this.onPause((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.onRepeat(modifier._onRepeat_0_0value);
                    break;
                }
                default: {
                    this.onRepeat((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.onCancel(modifier._onCancel_0_0value);
                    break;
                }
                default: {
                    this.onCancel((undefined as (() => void) | undefined));
                }
            }
        }
        if (flagArray[12] != 0) {
            switch (flagArray[12]) {
                case 1:
                case 3: {
                    this.onFinish(modifier._onFinish_0_0value);
                    break;
                }
                default: {
                    this.onFinish((undefined as (() => void) | undefined));
                }
            }
        }
    }
    images(value: Array<ImageFrameInfo> | undefined): this {
        if (((this._flagArray[0]) == (0)) || (true)) {
            this._flagArray[0] = 1
            this._images_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    state(value: AnimationStatus | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._state_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    duration(value: int32 | undefined): this {
        if (((this._flagArray[2]) == (0)) || ((this._duration_0_0value) !== (value))) {
            this._flagArray[2] = 1
            this._duration_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    reverse(value: boolean | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._reverse_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._reverse_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    fixedSize(value: boolean | undefined): this {
        if (((this._flagArray[4]) == (0)) || ((this._fixedSize_0_0value) !== (value))) {
            this._flagArray[4] = 1
            this._fixedSize_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    fillMode(value: FillMode | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._fillMode_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    iterations(value: int32 | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._iterations_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._iterations_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    monitorInvisibleArea(value: boolean | undefined): this {
        if (((this._flagArray[7]) == (0)) || ((this._monitorInvisibleArea_0_0value) !== (value))) {
            this._flagArray[7] = 1
            this._monitorInvisibleArea_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._onStart_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    onPause(value: (() => void) | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._onPause_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    onRepeat(value: (() => void) | undefined): this {
        if (((this._flagArray[10]) == (0)) || (true)) {
            this._flagArray[10] = 1
            this._onRepeat_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    onCancel(value: (() => void) | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._onCancel_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._flagArray[12]) == (0)) || (true)) {
            this._flagArray[12] = 1
            this._onFinish_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[12] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

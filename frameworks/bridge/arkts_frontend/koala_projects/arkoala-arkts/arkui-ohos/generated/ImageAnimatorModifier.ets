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
import { AttributeModifier } from "#handwritten"
import { AttributeUpdaterFlag } from "./AttributeUpdaterFlag"
import { PeerNode } from "./PeerNode"
import { ArkImageAnimatorPeer, ImageFrameInfo, ImageAnimatorAttribute } from "./component/imageAnimator"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { AnimationStatus, FillMode } from "./component/enums"
export class ImageAnimatorModifier extends CommonMethodModifier implements ImageAnimatorAttribute,AttributeModifier<ImageAnimatorAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: ImageAnimatorAttribute): void { }
    applyPressedAttribute(instance: ImageAnimatorAttribute): void { }
    applyFocusedAttribute(instance: ImageAnimatorAttribute): void { }
    applyDisabledAttribute(instance: ImageAnimatorAttribute): void { }
    applySelectedAttribute(instance: ImageAnimatorAttribute): void { }
    _images_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _images_0_0value?: Array<ImageFrameInfo> | undefined
    _state_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _state_0_0value?: AnimationStatus | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: int32 | undefined
    _reverse_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _reverse_0_0value?: boolean | undefined
    _fixedSize_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fixedSize_0_0value?: boolean | undefined
    _fillMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillMode_0_0value?: FillMode | undefined
    _iterations_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iterations_0_0value?: int32 | undefined
    _monitorInvisibleArea_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _monitorInvisibleArea_0_0value?: boolean | undefined
    _onStart_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onStart_0_0value?: (() => void) | undefined
    _onPause_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPause_0_0value?: (() => void) | undefined
    _onRepeat_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onRepeat_0_0value?: (() => void) | undefined
    _onCancel_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onCancel_0_0value?: (() => void) | undefined
    _onFinish_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFinish_0_0value?: (() => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkImageAnimatorPeer;
        if (this._images_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._images_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setImagesAttribute((this._images_0_0value as Array<ImageFrameInfo> | undefined));
                    this._images_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._images_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._images_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setImagesAttribute((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
        if (this._state_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._state_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setStateAttribute((this._state_0_0value as AnimationStatus | undefined));
                    this._state_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._state_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._state_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setStateAttribute((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (this._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDurationAttribute((this._duration_0_0value as int32 | undefined));
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._duration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDurationAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setReverseAttribute((this._reverse_0_0value as boolean | undefined));
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._reverse_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._reverse_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setReverseAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fixedSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fixedSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFixedSizeAttribute((this._fixedSize_0_0value as boolean | undefined));
                    this._fixedSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fixedSize_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fixedSize_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFixedSizeAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._fillMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._fillMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setFillModeAttribute((this._fillMode_0_0value as FillMode | undefined));
                    this._fillMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._fillMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._fillMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setFillModeAttribute((undefined as FillMode | undefined));
                }
            }
        }
        if (this._iterations_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._iterations_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setIterationsAttribute((this._iterations_0_0value as int32 | undefined));
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iterations_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIterationsAttribute((undefined as int32 | undefined));
                }
            }
        }
        if (this._monitorInvisibleArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._monitorInvisibleArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMonitorInvisibleAreaAttribute((this._monitorInvisibleArea_0_0value as boolean | undefined));
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMonitorInvisibleAreaAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnStartAttribute((this._onStart_0_0value as (() => void) | undefined));
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onStart_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onStart_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnStartAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPauseAttribute((this._onPause_0_0value as (() => void) | undefined));
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPause_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPause_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPauseAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnRepeatAttribute((this._onRepeat_0_0value as (() => void) | undefined));
                    this._onRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onRepeat_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onRepeat_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnRepeatAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onCancel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onCancel_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnCancelAttribute((this._onCancel_0_0value as (() => void) | undefined));
                    this._onCancel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onCancel_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onCancel_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnCancelAttribute((undefined as (() => void) | undefined));
                }
            }
        }
        if (this._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFinishAttribute((this._onFinish_0_0value as (() => void) | undefined));
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFinish_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFinishAttribute((undefined as (() => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: ImageAnimatorModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._images_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._images_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.images(modifier._images_0_0value);
                    break;
                }
                default: {
                    this.images((undefined as Array<ImageFrameInfo> | undefined));
                }
            }
        }
        if (modifier._state_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._state_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.state(modifier._state_0_0value);
                    break;
                }
                default: {
                    this.state((undefined as AnimationStatus | undefined));
                }
            }
        }
        if (modifier._duration_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._duration_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.duration(modifier._duration_0_0value);
                    break;
                }
                default: {
                    this.duration((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._reverse_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._reverse_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.reverse(modifier._reverse_0_0value);
                    break;
                }
                default: {
                    this.reverse((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fixedSize_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fixedSize_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fixedSize(modifier._fixedSize_0_0value);
                    break;
                }
                default: {
                    this.fixedSize((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._fillMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._fillMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.fillMode(modifier._fillMode_0_0value);
                    break;
                }
                default: {
                    this.fillMode((undefined as FillMode | undefined));
                }
            }
        }
        if (modifier._iterations_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._iterations_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.iterations(modifier._iterations_0_0value);
                    break;
                }
                default: {
                    this.iterations((undefined as int32 | undefined));
                }
            }
        }
        if (modifier._monitorInvisibleArea_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._monitorInvisibleArea_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.monitorInvisibleArea(modifier._monitorInvisibleArea_0_0value);
                    break;
                }
                default: {
                    this.monitorInvisibleArea((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onStart_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onStart_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onStart(modifier._onStart_0_0value);
                    break;
                }
                default: {
                    this.onStart((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onPause_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPause_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPause(modifier._onPause_0_0value);
                    break;
                }
                default: {
                    this.onPause((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onRepeat_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onRepeat_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onRepeat(modifier._onRepeat_0_0value);
                    break;
                }
                default: {
                    this.onRepeat((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onCancel_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onCancel_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onCancel(modifier._onCancel_0_0value);
                    break;
                }
                default: {
                    this.onCancel((undefined as (() => void) | undefined));
                }
            }
        }
        if (modifier._onFinish_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFinish_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
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
        if (((this._images_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._images_0_flag = AttributeUpdaterFlag.UPDATE
            this._images_0_0value = value
            this._state.fireChange()
        } else
        {
            this._images_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    state(value: AnimationStatus | undefined): this {
        if (((this._state_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._state_0_flag = AttributeUpdaterFlag.UPDATE
            this._state_0_0value = value
            this._state.fireChange()
        } else
        {
            this._state_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    duration(value: int32 | undefined): this {
        if (((this._duration_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._duration_0_0value) !== (value)))
        {
            this._duration_0_flag = AttributeUpdaterFlag.UPDATE
            this._duration_0_0value = value
            this._state.fireChange()
        } else
        {
            this._duration_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    reverse(value: boolean | undefined): this {
        if (((this._reverse_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._reverse_0_0value) !== (value)))
        {
            this._reverse_0_flag = AttributeUpdaterFlag.UPDATE
            this._reverse_0_0value = value
            this._state.fireChange()
        } else
        {
            this._reverse_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fixedSize(value: boolean | undefined): this {
        if (((this._fixedSize_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._fixedSize_0_0value) !== (value)))
        {
            this._fixedSize_0_flag = AttributeUpdaterFlag.UPDATE
            this._fixedSize_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fixedSize_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    fillMode(value: FillMode | undefined): this {
        if (((this._fillMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._fillMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._fillMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._fillMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    iterations(value: int32 | undefined): this {
        if (((this._iterations_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._iterations_0_0value) !== (value)))
        {
            this._iterations_0_flag = AttributeUpdaterFlag.UPDATE
            this._iterations_0_0value = value
            this._state.fireChange()
        } else
        {
            this._iterations_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    monitorInvisibleArea(value: boolean | undefined): this {
        if (((this._monitorInvisibleArea_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._monitorInvisibleArea_0_0value) !== (value)))
        {
            this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.UPDATE
            this._monitorInvisibleArea_0_0value = value
            this._state.fireChange()
        } else
        {
            this._monitorInvisibleArea_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onStart(value: (() => void) | undefined): this {
        if (((this._onStart_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onStart_0_flag = AttributeUpdaterFlag.UPDATE
            this._onStart_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onStart_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPause(value: (() => void) | undefined): this {
        if (((this._onPause_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPause_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPause_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPause_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onRepeat(value: (() => void) | undefined): this {
        if (((this._onRepeat_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onRepeat_0_flag = AttributeUpdaterFlag.UPDATE
            this._onRepeat_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onRepeat_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onCancel(value: (() => void) | undefined): this {
        if (((this._onCancel_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onCancel_0_flag = AttributeUpdaterFlag.UPDATE
            this._onCancel_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onCancel_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onFinish(value: (() => void) | undefined): this {
        if (((this._onFinish_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFinish_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFinish_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<ImageAnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

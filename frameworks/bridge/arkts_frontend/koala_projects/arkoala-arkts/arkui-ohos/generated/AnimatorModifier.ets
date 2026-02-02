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
import { ArkAnimatorPeer, SpringMotion, FrictionMotion, ScrollMotion, AnimatorAttribute } from "./component/animator"
import { int32 } from "@koalaui/common"
import { CommonMethod } from "./component/common"
import { AnimationStatus, FillMode, PlayMode } from "./component/enums"
import { default as curves } from "@ohos.curves"
export class AnimatorModifier extends CommonMethodModifier implements AnimatorAttribute,AttributeModifier<AnimatorAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState	
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: AnimatorAttribute): void { }
    applyPressedAttribute(instance: AnimatorAttribute): void { }
    applyFocusedAttribute(instance: AnimatorAttribute): void { }
    applyDisabledAttribute(instance: AnimatorAttribute): void { }
    applySelectedAttribute(instance: AnimatorAttribute): void { }
    _state_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _state_0_0value?: AnimationStatus | undefined
    _duration_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _duration_0_0value?: number | undefined
    _curve_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _curve_0_0value?: curves.Curve | undefined
    _delay_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _delay_0_0value?: number | undefined
    _fillMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _fillMode_0_0value?: FillMode | undefined
    _iterations_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _iterations_0_0value?: number | undefined
    _playMode_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _playMode_0_0value?: PlayMode | undefined
    _motion_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _motion_0_0value?: SpringMotion | FrictionMotion | ScrollMotion | undefined
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
    _onFrame_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onFrame_0_0value?: ((value: number) => void) | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkAnimatorPeer;
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
                    peer.setDurationAttribute((this._duration_0_0value as number | undefined));
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._duration_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._duration_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDurationAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCurveAttribute((this._curve_0_0value as curves.Curve | undefined));
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._curve_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._curve_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCurveAttribute((undefined as curves.Curve | undefined));
                }
            }
        }
        if (this._delay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._delay_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setDelayAttribute((this._delay_0_0value as number | undefined));
                    this._delay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._delay_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._delay_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setDelayAttribute((undefined as number | undefined));
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
                    peer.setIterationsAttribute((this._iterations_0_0value as number | undefined));
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._iterations_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._iterations_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setIterationsAttribute((undefined as number | undefined));
                }
            }
        }
        if (this._playMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._playMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPlayModeAttribute((this._playMode_0_0value as PlayMode | undefined));
                    this._playMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._playMode_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._playMode_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPlayModeAttribute((undefined as PlayMode | undefined));
                }
            }
        }
        if (this._motion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._motion_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setMotionAttribute((this._motion_0_0value as SpringMotion | FrictionMotion | ScrollMotion | undefined));
                    this._motion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._motion_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._motion_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setMotionAttribute((undefined as SpringMotion | FrictionMotion | ScrollMotion | undefined));
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
        if (this._onFrame_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onFrame_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnFrameAttribute((this._onFrame_0_0value as ((value: number) => void) | undefined));
                    this._onFrame_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onFrame_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onFrame_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnFrameAttribute((undefined as ((value: number) => void) | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: AnimatorModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
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
                    this.duration((undefined as number | undefined));
                }
            }
        }
        if (modifier._curve_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._curve_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.curve(modifier._curve_0_0value);
                    break;
                }
                default: {
                    this.curve((undefined as curves.Curve | undefined));
                }
            }
        }
        if (modifier._delay_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._delay_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.delay(modifier._delay_0_0value);
                    break;
                }
                default: {
                    this.delay((undefined as number | undefined));
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
                    this.iterations((undefined as number | undefined));
                }
            }
        }
        if (modifier._playMode_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._playMode_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.playMode(modifier._playMode_0_0value);
                    break;
                }
                default: {
                    this.playMode((undefined as PlayMode | undefined));
                }
            }
        }
        if (modifier._motion_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._motion_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.motion(modifier._motion_0_0value);
                    break;
                }
                default: {
                    this.motion((undefined as SpringMotion | FrictionMotion | ScrollMotion | undefined));
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
        if (modifier._onFrame_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onFrame_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onFrame(modifier._onFrame_0_0value);
                    break;
                }
                default: {
                    this.onFrame((undefined as ((value: number) => void) | undefined));
                }
            }
        }
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
    duration(value: number | undefined): this {
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
    curve(value: curves.Curve | undefined): this {
        if (((this._curve_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._curve_0_flag = AttributeUpdaterFlag.UPDATE
            this._curve_0_0value = value
            this._state.fireChange()
        } else
        {
            this._curve_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    delay(value: number | undefined): this {
        if (((this._delay_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._delay_0_0value) !== (value)))
        {
            this._delay_0_flag = AttributeUpdaterFlag.UPDATE
            this._delay_0_0value = value
            this._state.fireChange()
        } else
        {
            this._delay_0_flag = AttributeUpdaterFlag.SKIP
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
    iterations(value: number | undefined): this {
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
    playMode(value: PlayMode | undefined): this {
        if (((this._playMode_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._playMode_0_flag = AttributeUpdaterFlag.UPDATE
            this._playMode_0_0value = value
            this._state.fireChange()
        } else
        {
            this._playMode_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    motion(value: SpringMotion | FrictionMotion | ScrollMotion | undefined): this {
        if (((this._motion_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._motion_0_flag = AttributeUpdaterFlag.UPDATE
            this._motion_0_0value = value
            this._state.fireChange()
        } else
        {
            this._motion_0_flag = AttributeUpdaterFlag.SKIP
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
    onFrame(value: ((value: number) => void) | undefined): this {
        if (((this._onFrame_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onFrame_0_flag = AttributeUpdaterFlag.UPDATE
            this._onFrame_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onFrame_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<AnimatorAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

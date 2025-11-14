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
import { ArkPatternLockPeer, CircleStyleOptions, PatternLockAttribute } from "./component/patternLock"
import { int32 } from "@koalaui/common"
import { ModifierState } from "./CommonModifier"
import { CommonMethod } from "./component/common"
import { Length, ResourceColor } from "./component/units"
import { Resource } from "global.resource"
import { Color } from "./component/enums"
export class PatternLockModifier extends CommonMethodModifier implements PatternLockAttribute,AttributeModifier<PatternLockAttribute> {
    _instanceId: number = -1;
    _state: ModifierState = new ModifierState
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    isUpdater: () => boolean = () => false
    applyNormalAttribute(instance: PatternLockAttribute): void { }
    applyPressedAttribute(instance: PatternLockAttribute): void { }
    applyFocusedAttribute(instance: PatternLockAttribute): void { }
    applyDisabledAttribute(instance: PatternLockAttribute): void { }
    applySelectedAttribute(instance: PatternLockAttribute): void { }
    _sideLength_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _sideLength_0_0value?: Length | undefined
    _circleRadius_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _circleRadius_0_0value?: Length | undefined
    _backgroundColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _backgroundColor_0_0value?: ResourceColor | undefined
    _regularColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _regularColor_0_0value?: ResourceColor | undefined
    _selectedColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _selectedColor_0_0value?: ResourceColor | undefined
    _activeColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _activeColor_0_0value?: ResourceColor | undefined
    _pathColor_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pathColor_0_0value?: ResourceColor | undefined
    _pathStrokeWidth_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _pathStrokeWidth_0_0value?: double | string | undefined
    _onPatternComplete_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onPatternComplete_0_0value?: ((input: Array<int32>) => void) | undefined
    _autoReset_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _autoReset_0_0value?: boolean | undefined
    _onDotConnect_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _onDotConnect_0_0value?: ((value0: int32) => void) | undefined
    _activateCircleStyle_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _activateCircleStyle_0_0value?: CircleStyleOptions | undefined
    _skipUnselectedPoint_0_flag: AttributeUpdaterFlag = AttributeUpdaterFlag.INITIAL
    _skipUnselectedPoint_0_0value?: boolean | undefined
    applyModifierPatch(node: PeerNode): void {
        this._state.addRef()
        super.applyModifierPatch(node)
        const peer = node as ArkPatternLockPeer;
        if (this._sideLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._sideLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSideLengthAttribute((this._sideLength_0_0value as Length | undefined));
                    this._sideLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._sideLength_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._sideLength_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSideLengthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._circleRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._circleRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setCircleRadiusAttribute((this._circleRadius_0_0value as Length | undefined));
                    this._circleRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._circleRadius_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._circleRadius_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setCircleRadiusAttribute((undefined as Length | undefined));
                }
            }
        }
        if (this._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setBackgroundColorAttribute((this._backgroundColor_0_0value as ResourceColor | undefined));
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._backgroundColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setBackgroundColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._regularColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._regularColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setRegularColorAttribute((this._regularColor_0_0value as ResourceColor | undefined));
                    this._regularColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._regularColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._regularColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setRegularColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSelectedColorAttribute((this._selectedColor_0_0value as ResourceColor | undefined));
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._selectedColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSelectedColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._activeColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._activeColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setActiveColorAttribute((this._activeColor_0_0value as ResourceColor | undefined));
                    this._activeColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._activeColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._activeColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setActiveColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._pathColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pathColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPathColorAttribute((this._pathColor_0_0value as ResourceColor | undefined));
                    this._pathColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pathColor_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pathColor_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPathColorAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (this._pathStrokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._pathStrokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setPathStrokeWidthAttribute((this._pathStrokeWidth_0_0value as double | string | undefined));
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setPathStrokeWidthAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (this._onPatternComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onPatternComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnPatternCompleteAttribute((this._onPatternComplete_0_0value as ((input: Array<int32>) => void) | undefined));
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onPatternComplete_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnPatternCompleteAttribute((undefined as ((input: Array<int32>) => void) | undefined));
                }
            }
        }
        if (this._autoReset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._autoReset_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setAutoResetAttribute((this._autoReset_0_0value as boolean | undefined));
                    this._autoReset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._autoReset_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._autoReset_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setAutoResetAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (this._onDotConnect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._onDotConnect_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setOnDotConnectAttribute((this._onDotConnect_0_0value as ((value0: int32) => void) | undefined));
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._onDotConnect_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setOnDotConnectAttribute((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (this._activateCircleStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._activateCircleStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setActivateCircleStyleAttribute((this._activateCircleStyle_0_0value as CircleStyleOptions | undefined));
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._activateCircleStyle_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setActivateCircleStyleAttribute((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (this._skipUnselectedPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (this._skipUnselectedPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE: {
                    peer.setSkipUnselectedPointAttribute((this._skipUnselectedPoint_0_0value as boolean | undefined));
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                case AttributeUpdaterFlag.SKIP: {
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.RESET;
                    break;
                }
                default: {
                    this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.INITIAL;
                    peer.setSkipUnselectedPointAttribute((undefined as boolean | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PatternLockModifier): void {
       super.mergeModifier(modifier)
        this._state = modifier._state;
        if (modifier._sideLength_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._sideLength_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.sideLength(modifier._sideLength_0_0value);
                    break;
                }
                default: {
                    this.sideLength((undefined as Length | undefined));
                }
            }
        }
        if (modifier._circleRadius_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._circleRadius_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.circleRadius(modifier._circleRadius_0_0value);
                    break;
                }
                default: {
                    this.circleRadius((undefined as Length | undefined));
                }
            }
        }
        if (modifier._backgroundColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._backgroundColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.backgroundColor(modifier._backgroundColor_0_0value);
                    break;
                }
                default: {
                    this.backgroundColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._regularColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._regularColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.regularColor(modifier._regularColor_0_0value);
                    break;
                }
                default: {
                    this.regularColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._selectedColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._selectedColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.selectedColor(modifier._selectedColor_0_0value);
                    break;
                }
                default: {
                    this.selectedColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._activeColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._activeColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.activeColor(modifier._activeColor_0_0value);
                    break;
                }
                default: {
                    this.activeColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._pathColor_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pathColor_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pathColor(modifier._pathColor_0_0value);
                    break;
                }
                default: {
                    this.pathColor((undefined as ResourceColor | undefined));
                }
            }
        }
        if (modifier._pathStrokeWidth_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._pathStrokeWidth_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.pathStrokeWidth(modifier._pathStrokeWidth_0_0value);
                    break;
                }
                default: {
                    this.pathStrokeWidth((undefined as double | string | undefined));
                }
            }
        }
        if (modifier._onPatternComplete_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onPatternComplete_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onPatternComplete(modifier._onPatternComplete_0_0value);
                    break;
                }
                default: {
                    this.onPatternComplete((undefined as ((input: Array<int32>) => void) | undefined));
                }
            }
        }
        if (modifier._autoReset_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._autoReset_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.autoReset(modifier._autoReset_0_0value);
                    break;
                }
                default: {
                    this.autoReset((undefined as boolean | undefined));
                }
            }
        }
        if (modifier._onDotConnect_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._onDotConnect_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.onDotConnect(modifier._onDotConnect_0_0value);
                    break;
                }
                default: {
                    this.onDotConnect((undefined as ((value0: int32) => void) | undefined));
                }
            }
        }
        if (modifier._activateCircleStyle_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._activateCircleStyle_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.activateCircleStyle(modifier._activateCircleStyle_0_0value);
                    break;
                }
                default: {
                    this.activateCircleStyle((undefined as CircleStyleOptions | undefined));
                }
            }
        }
        if (modifier._skipUnselectedPoint_0_flag != AttributeUpdaterFlag.INITIAL)
        {
            switch (modifier._skipUnselectedPoint_0_flag) {
                case AttributeUpdaterFlag.UPDATE:
                case AttributeUpdaterFlag.SKIP: {
                    this.skipUnselectedPoint(modifier._skipUnselectedPoint_0_0value);
                    break;
                }
                default: {
                    this.skipUnselectedPoint((undefined as boolean | undefined));
                }
            }
        }
    }
    sideLength(value: Length | undefined): this {
        if (((this._sideLength_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._sideLength_0_flag = AttributeUpdaterFlag.UPDATE
            this._sideLength_0_0value = value
            this._state.fireChange()
        } else
        {
            this._sideLength_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    circleRadius(value: Length | undefined): this {
        if (((this._circleRadius_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._circleRadius_0_flag = AttributeUpdaterFlag.UPDATE
            this._circleRadius_0_0value = value
            this._state.fireChange()
        } else
        {
            this._circleRadius_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    backgroundColor(value: ResourceColor | undefined): this {
        if (((this._backgroundColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._backgroundColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._backgroundColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    regularColor(value: ResourceColor | undefined): this {
        if (((this._regularColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._regularColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._regularColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._regularColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    selectedColor(value: ResourceColor | undefined): this {
        if (((this._selectedColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._selectedColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._selectedColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    activeColor(value: ResourceColor | undefined): this {
        if (((this._activeColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._activeColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._activeColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._activeColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pathColor(value: ResourceColor | undefined): this {
        if (((this._pathColor_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._pathColor_0_flag = AttributeUpdaterFlag.UPDATE
            this._pathColor_0_0value = value
            this._state.fireChange()
        } else
        {
            this._pathColor_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    pathStrokeWidth(value: double | string | undefined): this {
        if (((this._pathStrokeWidth_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._pathStrokeWidth_0_0value) !== (value)))
        {
            this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.UPDATE
            this._pathStrokeWidth_0_0value = value
            this._state.fireChange()
        } else
        {
            this._pathStrokeWidth_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onPatternComplete(value: ((input: Array<int32>) => void) | undefined): this {
        if (((this._onPatternComplete_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onPatternComplete_0_flag = AttributeUpdaterFlag.UPDATE
            this._onPatternComplete_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onPatternComplete_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    autoReset(value: boolean | undefined): this {
        if (((this._autoReset_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._autoReset_0_0value) !== (value)))
        {
            this._autoReset_0_flag = AttributeUpdaterFlag.UPDATE
            this._autoReset_0_0value = value
            this._state.fireChange()
        } else
        {
            this._autoReset_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    onDotConnect(value: ((value0: int32) => void) | undefined): this {
        if (((this._onDotConnect_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._onDotConnect_0_flag = AttributeUpdaterFlag.UPDATE
            this._onDotConnect_0_0value = value
            this._state.fireChange()
        } else
        {
            this._onDotConnect_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    activateCircleStyle(value: CircleStyleOptions | undefined): this {
        if (((this._activateCircleStyle_0_flag) == (AttributeUpdaterFlag.INITIAL)) || (true))
        {
            this._activateCircleStyle_0_flag = AttributeUpdaterFlag.UPDATE
            this._activateCircleStyle_0_0value = value
            this._state.fireChange()
        } else
        {
            this._activateCircleStyle_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    skipUnselectedPoint(value: boolean | undefined): this {
        if (((this._skipUnselectedPoint_0_flag) == (AttributeUpdaterFlag.INITIAL)) || ((this._skipUnselectedPoint_0_0value) !== (value)))
        {
            this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.UPDATE
            this._skipUnselectedPoint_0_0value = value
            this._state.fireChange()
        } else
        {
            this._skipUnselectedPoint_0_flag = AttributeUpdaterFlag.SKIP
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PatternLockAttribute> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error("Not implemented")
    }
}

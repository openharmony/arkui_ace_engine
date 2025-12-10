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

import { CommonMethod, CommonShapeMethod as arkui_component_common_CommonShapeMethod } from './component/common'
import { ResourceColor, Resource as arkui_component_units_Resource, Length } from './component/units'
import { Color as arkui_component_enums_Color, LineCapStyle, LineJoinStyle } from './component/enums'
import { Resource as global_resource_Resource } from 'global.resource'
import { CommonShapeMethodModifier } from './CommonShapeMethodModifier'
import { CommonMethodModifier } from './CommonMethodModifier'
import { AttributeModifier } from '#handwritten'
import { AttributeUpdaterFlag } from './AttributeUpdaterFlag'
import { PeerNode } from './PeerNode'
import { ArkPathPeer, PathAttribute } from './component/path'
import { int32, int64 } from '@koalaui/common'
import { ModifierState } from './CommonModifier'
export class PathModifier extends CommonMethodModifier implements PathAttribute,AttributeModifier<PathAttribute> {
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
    applyNormalAttribute(instance: PathAttribute): void { }
    applyPressedAttribute(instance: PathAttribute): void { }
    applyFocusedAttribute(instance: PathAttribute): void { }
    applyDisabledAttribute(instance: PathAttribute): void { }
    applySelectedAttribute(instance: PathAttribute): void { }
    public _commands_0_0value?: string | undefined
    public _stroke_0_0value?: ResourceColor | undefined
    public _fill_0_0value?: ResourceColor | undefined
    public _strokeDashOffset_0_0value?: double | string | undefined
    public _strokeLineCap_0_0value?: LineCapStyle | undefined
    public _strokeLineJoin_0_0value?: LineJoinStyle | undefined
    public _strokeMiterLimit_0_0value?: double | string | undefined
    public _strokeOpacity_0_0value?: double | string | global_resource_Resource | undefined
    public _fillOpacity_0_0value?: double | string | global_resource_Resource | undefined
    public _strokeWidth_0_0value?: Length | undefined
    public _antiAlias_0_0value?: boolean | undefined
    public _strokeDashArray_0_0value?: Array<Length> | undefined
    applyModifierPatch(node: object): void {
        super.applyModifierPatch(node)
        this._state.addRef()
        const peer = node as ArkPathPeer;
        const flagArray = this._flagArray;
        this.applyModifierPatch0(peer, flagArray);
    }
    applyModifierPatch0(peer: ArkPathPeer, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1: {
                    peer.setCommandsAttribute((this._commands_0_0value as string | undefined));
                    flagArray[0] = 2;
                    break;
                }
                case 3: {
                    flagArray[0] = 2;
                    break;
                }
                default: {
                    flagArray[0] = 0;
                    peer.setCommandsAttribute((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1: {
                    peer.setStrokeAttribute((this._stroke_0_0value as ResourceColor | undefined));
                    flagArray[1] = 2;
                    break;
                }
                case 3: {
                    flagArray[1] = 2;
                    break;
                }
                default: {
                    flagArray[1] = 0;
                    peer.setStrokeAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1: {
                    peer.setFillAttribute((this._fill_0_0value as ResourceColor | undefined));
                    flagArray[2] = 2;
                    break;
                }
                case 3: {
                    flagArray[2] = 2;
                    break;
                }
                default: {
                    flagArray[2] = 0;
                    peer.setFillAttribute((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1: {
                    peer.setStrokeDashOffsetAttribute((this._strokeDashOffset_0_0value as double | string | undefined));
                    flagArray[3] = 2;
                    break;
                }
                case 3: {
                    flagArray[3] = 2;
                    break;
                }
                default: {
                    flagArray[3] = 0;
                    peer.setStrokeDashOffsetAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1: {
                    peer.setStrokeLineCapAttribute((this._strokeLineCap_0_0value as LineCapStyle | undefined));
                    flagArray[4] = 2;
                    break;
                }
                case 3: {
                    flagArray[4] = 2;
                    break;
                }
                default: {
                    flagArray[4] = 0;
                    peer.setStrokeLineCapAttribute((undefined as LineCapStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1: {
                    peer.setStrokeLineJoinAttribute((this._strokeLineJoin_0_0value as LineJoinStyle | undefined));
                    flagArray[5] = 2;
                    break;
                }
                case 3: {
                    flagArray[5] = 2;
                    break;
                }
                default: {
                    flagArray[5] = 0;
                    peer.setStrokeLineJoinAttribute((undefined as LineJoinStyle | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1: {
                    peer.setStrokeMiterLimitAttribute((this._strokeMiterLimit_0_0value as double | string | undefined));
                    flagArray[6] = 2;
                    break;
                }
                case 3: {
                    flagArray[6] = 2;
                    break;
                }
                default: {
                    flagArray[6] = 0;
                    peer.setStrokeMiterLimitAttribute((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1: {
                    peer.setStrokeOpacityAttribute((this._strokeOpacity_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[7] = 2;
                    break;
                }
                case 3: {
                    flagArray[7] = 2;
                    break;
                }
                default: {
                    flagArray[7] = 0;
                    peer.setStrokeOpacityAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1: {
                    peer.setFillOpacityAttribute((this._fillOpacity_0_0value as double | string | global_resource_Resource | undefined));
                    flagArray[8] = 2;
                    break;
                }
                case 3: {
                    flagArray[8] = 2;
                    break;
                }
                default: {
                    flagArray[8] = 0;
                    peer.setFillOpacityAttribute((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1: {
                    peer.setStrokeWidthAttribute((this._strokeWidth_0_0value as Length | undefined));
                    flagArray[9] = 2;
                    break;
                }
                case 3: {
                    flagArray[9] = 2;
                    break;
                }
                default: {
                    flagArray[9] = 0;
                    peer.setStrokeWidthAttribute((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1: {
                    peer.setAntiAliasAttribute((this._antiAlias_0_0value as boolean | undefined));
                    flagArray[10] = 2;
                    break;
                }
                case 3: {
                    flagArray[10] = 2;
                    break;
                }
                default: {
                    flagArray[10] = 0;
                    peer.setAntiAliasAttribute((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1: {
                    peer.setStrokeDashArrayAttribute((this._strokeDashArray_0_0value as Array<Length> | undefined));
                    flagArray[11] = 2;
                    break;
                }
                case 3: {
                    flagArray[11] = 2;
                    break;
                }
                default: {
                    flagArray[11] = 0;
                    peer.setStrokeDashArrayAttribute((undefined as Array<Length> | undefined));
                }
            }
        }
    }
    mergeModifier(modifier: PathModifier): void {
        super.mergeModifier(modifier)
        this._state = modifier._state;
        const flagArray = modifier._flagArray;
        this.mergeModifier0(modifier, flagArray);
    }
    mergeModifier0(modifier: PathModifier, flagArray: Uint8Array): void {
        if (flagArray[0] != 0) {
            switch (flagArray[0]) {
                case 1:
                case 3: {
                    this.commands(modifier._commands_0_0value);
                    break;
                }
                default: {
                    this.commands((undefined as string | undefined));
                }
            }
        }
        if (flagArray[1] != 0) {
            switch (flagArray[1]) {
                case 1:
                case 3: {
                    this.stroke(modifier._stroke_0_0value);
                    break;
                }
                default: {
                    this.stroke((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[2] != 0) {
            switch (flagArray[2]) {
                case 1:
                case 3: {
                    this.fill(modifier._fill_0_0value);
                    break;
                }
                default: {
                    this.fill((undefined as ResourceColor | undefined));
                }
            }
        }
        if (flagArray[3] != 0) {
            switch (flagArray[3]) {
                case 1:
                case 3: {
                    this.strokeDashOffset(modifier._strokeDashOffset_0_0value);
                    break;
                }
                default: {
                    this.strokeDashOffset((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[4] != 0) {
            switch (flagArray[4]) {
                case 1:
                case 3: {
                    this.strokeLineCap(modifier._strokeLineCap_0_0value);
                    break;
                }
                default: {
                    this.strokeLineCap((undefined as LineCapStyle | undefined));
                }
            }
        }
        if (flagArray[5] != 0) {
            switch (flagArray[5]) {
                case 1:
                case 3: {
                    this.strokeLineJoin(modifier._strokeLineJoin_0_0value);
                    break;
                }
                default: {
                    this.strokeLineJoin((undefined as LineJoinStyle | undefined));
                }
            }
        }
        if (flagArray[6] != 0) {
            switch (flagArray[6]) {
                case 1:
                case 3: {
                    this.strokeMiterLimit(modifier._strokeMiterLimit_0_0value);
                    break;
                }
                default: {
                    this.strokeMiterLimit((undefined as double | string | undefined));
                }
            }
        }
        if (flagArray[7] != 0) {
            switch (flagArray[7]) {
                case 1:
                case 3: {
                    this.strokeOpacity(modifier._strokeOpacity_0_0value);
                    break;
                }
                default: {
                    this.strokeOpacity((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[8] != 0) {
            switch (flagArray[8]) {
                case 1:
                case 3: {
                    this.fillOpacity(modifier._fillOpacity_0_0value);
                    break;
                }
                default: {
                    this.fillOpacity((undefined as double | string | global_resource_Resource | undefined));
                }
            }
        }
        if (flagArray[9] != 0) {
            switch (flagArray[9]) {
                case 1:
                case 3: {
                    this.strokeWidth(modifier._strokeWidth_0_0value);
                    break;
                }
                default: {
                    this.strokeWidth((undefined as Length | undefined));
                }
            }
        }
        if (flagArray[10] != 0) {
            switch (flagArray[10]) {
                case 1:
                case 3: {
                    this.antiAlias(modifier._antiAlias_0_0value);
                    break;
                }
                default: {
                    this.antiAlias((undefined as boolean | undefined));
                }
            }
        }
        if (flagArray[11] != 0) {
            switch (flagArray[11]) {
                case 1:
                case 3: {
                    this.strokeDashArray(modifier._strokeDashArray_0_0value);
                    break;
                }
                default: {
                    this.strokeDashArray((undefined as Array<Length> | undefined));
                }
            }
        }
    }
    commands(value: string | undefined): this {
        if (((this._flagArray[0]) == (0)) || ((this._commands_0_0value) !== (value))) {
            this._flagArray[0] = 1
            this._commands_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[0] = 3
        }
        return this
    }
    stroke(value: ResourceColor | undefined): this {
        if (((this._flagArray[1]) == (0)) || (true)) {
            this._flagArray[1] = 1
            this._stroke_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[1] = 3
        }
        return this
    }
    fill(value: ResourceColor | undefined): this {
        if (((this._flagArray[2]) == (0)) || (true)) {
            this._flagArray[2] = 1
            this._fill_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[2] = 3
        }
        return this
    }
    strokeDashOffset(value: double | string | undefined): this {
        if (((this._flagArray[3]) == (0)) || ((this._strokeDashOffset_0_0value) !== (value))) {
            this._flagArray[3] = 1
            this._strokeDashOffset_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[3] = 3
        }
        return this
    }
    strokeLineCap(value: LineCapStyle | undefined): this {
        if (((this._flagArray[4]) == (0)) || (true)) {
            this._flagArray[4] = 1
            this._strokeLineCap_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[4] = 3
        }
        return this
    }
    strokeLineJoin(value: LineJoinStyle | undefined): this {
        if (((this._flagArray[5]) == (0)) || (true)) {
            this._flagArray[5] = 1
            this._strokeLineJoin_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[5] = 3
        }
        return this
    }
    strokeMiterLimit(value: double | string | undefined): this {
        if (((this._flagArray[6]) == (0)) || ((this._strokeMiterLimit_0_0value) !== (value))) {
            this._flagArray[6] = 1
            this._strokeMiterLimit_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[6] = 3
        }
        return this
    }
    strokeOpacity(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[7]) == (0)) || (true)) {
            this._flagArray[7] = 1
            this._strokeOpacity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[7] = 3
        }
        return this
    }
    fillOpacity(value: double | string | global_resource_Resource | undefined): this {
        if (((this._flagArray[8]) == (0)) || (true)) {
            this._flagArray[8] = 1
            this._fillOpacity_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[8] = 3
        }
        return this
    }
    strokeWidth(value: Length | undefined): this {
        if (((this._flagArray[9]) == (0)) || (true)) {
            this._flagArray[9] = 1
            this._strokeWidth_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[9] = 3
        }
        return this
    }
    antiAlias(value: boolean | undefined): this {
        if (((this._flagArray[10]) == (0)) || ((this._antiAlias_0_0value) !== (value))) {
            this._flagArray[10] = 1
            this._antiAlias_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[10] = 3
        }
        return this
    }
    strokeDashArray(value: Array<Length> | undefined): this {
        if (((this._flagArray[11]) == (0)) || (true)) {
            this._flagArray[11] = 1
            this._strokeDashArray_0_0value = value
            this._state.fireChange()
        } else {
            this._flagArray[11] = 3
        }
        return this
    }
    public attributeModifier(value: AttributeModifier<PathAttribute> | AttributeModifier<arkui_component_common_CommonShapeMethod> | AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Not implemented')
    }
}

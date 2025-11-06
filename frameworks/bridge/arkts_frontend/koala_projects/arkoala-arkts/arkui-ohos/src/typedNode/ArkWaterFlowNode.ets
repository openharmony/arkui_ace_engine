/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { RuntimeType, runtimeType } from '@koalaui/interop';
import { ArkScrollableNode } from './ArkScrollableNode';
import {
  WaterFlowAttribute,
  ArkWaterFlowPeer,
  WaterFlowOptions,
  ConstraintSizeOptions,
  Length,
  FlexDirection,
  NestedScrollOptions,
  OnScrollFrameBeginCallback,
  OnWillScrollCallback,
  OnScrollCallback,
  AttributeModifier,
  ScrollableCommonMethod,
  CommonMethod
} from '../framework';
import { Resource } from 'global.resource'
export class ArkWaterFlowNode extends ArkScrollableNode implements WaterFlowAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: WaterFlowOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (WaterFlowOptions | undefined);
        }
        this.getPeer()?.setWaterFlowOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    getPeer() : ArkWaterFlowPeer {
        return this.peer as ArkWaterFlowPeer
    }
    initialize(options?: WaterFlowOptions): this {
        const options_casted = options as (WaterFlowOptions | undefined)
        this.getPeer()?.setWaterFlowOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    allowChildTypes(): string[] {
        return ['FlowItem'];
    }
    columnsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setColumnsTemplateAttribute(value_casted)
        this.markDirty()
        return this
    }
    itemConstraintSize(value: ConstraintSizeOptions | undefined): this {
        const value_casted = value as (ConstraintSizeOptions | undefined)
        this.getPeer()?.setItemConstraintSizeAttribute(value_casted)
        this.markDirty()
        return this
    }
    rowsTemplate(value: string | undefined): this {
        const value_casted = value as (string | undefined)
        this.getPeer()?.setRowsTemplateAttribute(value_casted)
        this.markDirty()
        return this
    }
    columnsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setColumnsGapAttribute(value_casted)
        this.markDirty()
        return this
    }
    rowsGap(value: Length | undefined): this {
        const value_casted = value as (Length | undefined)
        this.getPeer()?.setRowsGapAttribute(value_casted)
        this.markDirty()
        return this
    }
    layoutDirection(value: FlexDirection | undefined): this {
        const value_casted = value as (FlexDirection | undefined)
        this.getPeer()?.setLayoutDirectionAttribute(value_casted)
        this.markDirty()
        return this
    }
    nestedScroll(value: NestedScrollOptions | undefined): this {
        const value_casted = value as (NestedScrollOptions | undefined)
        this.getPeer()?.setNestedScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    enableScrollInteraction(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.setEnableScrollInteractionAttribute(value_casted)
        this.markDirty()
        return this
    }
    friction(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined)
        this.getPeer()?.setFrictionAttribute(value_casted)
        this.markDirty()
        return this
    }
    cachedCount(count: number | undefined, show?: boolean): this {
        const count_type = runtimeType(count)
        const show_type = runtimeType(show)
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            (RuntimeType.UNDEFINED == show_type)) {
            const value_casted = count as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            this.markDirty()
            return this
        }
        if (((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) &&
            ((RuntimeType.BOOLEAN == show_type) || (RuntimeType.UNDEFINED == show_type))) {
            const count_casted = count as (number | undefined)
            const show_casted = show as (boolean | undefined)
            this.getPeer()?.setCachedCount1Attribute(count_casted, show_casted)
            this.markDirty()
            return this
        }
        throw new Error('Can not select appropriate overload')
    }
    cachedCount(value: number | undefined): this {
        const count_type = runtimeType(value)
        if ((RuntimeType.NUMBER == count_type) || (RuntimeType.UNDEFINED == count_type)) {
            const value_casted = value as (number | undefined)
            this.getPeer()?.setCachedCount0Attribute(value_casted)
            this.markDirty()
            return this
        }
        throw new Error('Can not select appropriate overload')
    }
    onReachStart(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnReachStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    onReachEnd(value: (() => void) | undefined): this {
        const value_casted = value as ((() => void) | undefined)
        this.getPeer()?.setOnReachEndAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollFrameBegin(value: OnScrollFrameBeginCallback | undefined): this {
        const value_casted = value as (OnScrollFrameBeginCallback | undefined)
        this.getPeer()?.setOnScrollFrameBeginAttribute(value_casted)
        this.markDirty()
        return this
    }
    onScrollIndex(value: ((first: number, last: number) => void) | undefined): this {
        const value_casted = value as (((first: number, last: number) => void) | undefined)
        this.getPeer()?.setOnScrollIndexAttribute(value_casted)
        this.markDirty()
        return this
    }
    onWillScroll(value: OnWillScrollCallback | undefined): this {
        const value_casted = value as (OnWillScrollCallback | undefined)
        this.getPeer()?.setOnWillScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    onDidScroll(value: OnScrollCallback | undefined): this {
        const value_casted = value as (OnScrollCallback | undefined)
        this.getPeer()?.setOnDidScrollAttribute(value_casted)
        this.markDirty()
        return this
    }
    attributeModifier(value: AttributeModifier<WaterFlowAttribute> | AttributeModifier<ScrollableCommonMethod> |
        AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
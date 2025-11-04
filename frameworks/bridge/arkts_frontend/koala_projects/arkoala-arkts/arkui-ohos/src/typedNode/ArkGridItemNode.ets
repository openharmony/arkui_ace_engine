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
import { ArkBaseNode } from './ArkBaseNode';
import {
  GridItemAttribute,
  ArkGridItemPeer,
  GridItemOptions,
  Bindable,
  AttributeModifier,
  CommonMethod
} from '../component/gridItem';
export class ArkGridItemNode extends ArkBaseNode implements GridItemAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: GridItemOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (GridItemOptions | undefined);
        }
        this.getPeer()?.setGridItemOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    getPeer() : ArkGridItemPeer {
        return this.peer as ArkGridItemPeer
    }
    initialize(options?: GridItemOptions): this {
        const options_casted = options as (GridItemOptions | undefined)
        this.getPeer()?.setGridItemOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    allowChildCount(): number {
        return 1;
    }
    rowStart(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setRowStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    rowEnd(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setRowEndAttribute(value_casted)
        this.markDirty()
        return this
    }
    columnStart(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setColumnStartAttribute(value_casted)
        this.markDirty()
        return this
    }
    columnEnd(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.setColumnEndAttribute(value_casted)
        this.markDirty()
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectedAttribute(value_casted)
            this.markDirty()
            return this
        }
        return this
    }
    onSelect(value: ((isVisible: boolean) => void) | undefined): this {
        const value_casted = value as (((isVisible: boolean) => void) | undefined)
        this.getPeer()?.setOnSelectAttribute(value_casted)
        this.markDirty()
        return this
    }
    attributeModifier(value: AttributeModifier<GridItemAttribute> |
        AttributeModifier<CommonMethod> | undefined): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
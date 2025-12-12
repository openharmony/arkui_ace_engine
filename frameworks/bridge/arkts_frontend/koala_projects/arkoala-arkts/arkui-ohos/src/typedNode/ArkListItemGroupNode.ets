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

import { ArkBaseNode } from './ArkBaseNode';
import {
  ListItemGroupAttribute,
  ArkListItemGroupPeer,
  ListItemGroupOptions,
  ListDividerOptions,
  ChildrenMainSize,
  AttributeModifier,
  CommonMethod
} from '../framework';
export class ArkListItemGroupNode extends ArkBaseNode implements ListItemGroupAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: ListItemGroupOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (ListItemGroupOptions | undefined);
        }
        this.getPeer()?.setListItemGroupOptionsAttribute(options_casted)
        this.markDirty()
        return this;
    }
    getPeer() : ArkListItemGroupPeer {
        return this.peer as ArkListItemGroupPeer
    }
    initialize(options?: ListItemGroupOptions): this {
        const options_casted = options as (ListItemGroupOptions | undefined)
        this.getPeer()?.setListItemGroupOptionsAttribute(options_casted)
        this.markDirty()
        return this
    }
    allowChildTypes(): string[] {
        return ['ListItem'];
    }
    divider(value: ListDividerOptions | undefined): this {
        const value_casted = value as (ListDividerOptions | undefined)
        this.getPeer()?.setDividerAttribute(value_casted)
        this.markDirty()
        return this
    }
    childrenMainSize(value: ChildrenMainSize | undefined): this {
        const value_casted = value as (ChildrenMainSize | undefined)
        this.getPeer()?.setChildrenMainSizeAttribute(value_casted);
        this.markDirty()
        return this
    }
    attributeModifier(
        value: AttributeModifier<ListItemGroupAttribute> |
        AttributeModifier<CommonMethod> |
        undefined
    ): this {
        throw new Error('Unimplemented method attributeModifier')
    }
}
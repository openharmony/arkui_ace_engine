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

import { InteropNativeModule } from '@koalaui/interop';
import { ArkBaseNode } from './ArkBaseNode';
import { GridRowAttribute, ArkGridRowPeer, ItemAlign, GridRowOptions } from '../../component';

export class ArkGridRowNode extends ArkBaseNode implements GridRowAttribute {

    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let option_casted: GridRowOptions | undefined = undefined;
        if (param.length === 1) {
            option_casted = param[0] as (GridRowOptions | undefined);
        }
        this.getPeer()?.setGridRowOptionsAttribute(option_casted);
        return this;
    }
    
    initialize(option?: GridRowOptions): this {
        const option_casted = option as (GridRowOptions | undefined);
        this.getPeer()?.setGridRowOptionsAttribute(option_casted);
        return this;
    }

    getPeer(): ArkGridRowPeer {
        return this.peer as ArkGridRowPeer;
    }

    onBreakpointChange(value: ((breakpoints: string) => void) | undefined): this {
        const value_casted = value as (((breakpoints: string) => void) | undefined);
        this.getPeer()?.onBreakpointChangeAttribute(value_casted);
        return this;
    }

    alignItems(value: ItemAlign | undefined): this {
        const value_casted = value as (ItemAlign | undefined);
        this.getPeer()?.alignItemsAttribute(value_casted);
        return this;
    }
}

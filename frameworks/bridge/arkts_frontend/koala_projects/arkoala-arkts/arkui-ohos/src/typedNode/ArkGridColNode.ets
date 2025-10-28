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
import { GridColAttribute, ArkGridColPeer, GridColColumnOption, GridColOptions } from '../framework';
import { int32 } from '@koalaui/common';

export class ArkGridColNode extends ArkBaseNode implements GridColAttribute {

    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let option_casted: GridColOptions | undefined = undefined;
        if (param.length === 1) {
            option_casted = param[0] as (GridColOptions | undefined);
        }
        this.getPeer()?.setGridColOptionsAttribute(option_casted);
        return this;
    }

    initialize(option?: GridColOptions): this {
        const option_casted = option as (GridColOptions | undefined);
        this.getPeer()?.setGridColOptionsAttribute(option_casted);
        return this;
    }

    getPeer(): ArkGridColPeer {
        return this.peer as ArkGridColPeer;
    }

    span(value: int32 | GridColColumnOption | undefined): this {
        const value_casted = value as (int32 | GridColColumnOption | undefined);
        this.getPeer()?.setSpanAttribute(value_casted);
        return this;
    }

    gridColOffset(value: int32 | GridColColumnOption | undefined): this {
        const value_casted = value as (int32 | GridColColumnOption | undefined);
        this.getPeer()?.setGridColOffsetAttribute(value_casted);
        return this;
    }

    order(value: int32 | GridColColumnOption | undefined): this {
        const value_casted = value as (int32 | GridColColumnOption | undefined);
        this.getPeer()?.setOrderAttribute(value_casted);
        return this;
    }
}

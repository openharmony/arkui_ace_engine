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

import { RuntimeType, runtimeType } from "@koalaui/interop";
import { ArkBaseNode } from "./ArkBaseNode";
import { GridItemAttribute, ArkGridItemPeer, GridItemOptions, Bindable } from "../../component";
import { GridItemOpsHandWritten } from "../../handwritten"
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
        return this;
    }
    getPeer() : ArkGridItemPeer {
        return this.peer as ArkGridItemPeer
    }
    initialize(options?: GridItemOptions): this {
        const options_casted = options as (GridItemOptions | undefined)
        this.getPeer()?.setGridItemOptionsAttribute(options_casted)
        return this;
    }
    rowStart(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.rowStartAttribute(value_casted)
        return this
    }
    rowEnd(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.rowEndAttribute(value_casted)
        return this
    }
    columnStart(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.columnStartAttribute(value_casted)
        return this
    }
    columnEnd(value: number | undefined): this {
        const value_casted = value as (number | undefined)
        this.getPeer()?.columnEndAttribute(value_casted)
        return this
    }
    forceRebuild(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.forceRebuildAttribute(value_casted)
        return this
    }
    selectable(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined)
        this.getPeer()?.selectableAttribute(value_casted)
        return this
    }
    selected(value: boolean | Bindable<boolean> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.selectedAttribute(value_casted)
            return this
        }
        GridItemOpsHandWritten.hookGridItemAttributeSelectedImpl(this.getPeer().peer.ptr,
            (value as Bindable<boolean>));
        return this
    }
    onSelect(value: ((isVisible: boolean) => void) | undefined): this {
        const value_casted = value as (((isVisible: boolean) => void) | undefined)
        this.getPeer()?.onSelectAttribute(value_casted)
        return this
    }
    _onChangeEvent_selected(callback: ((select: boolean | undefined) => void)): void {
        const callback_casted = callback as (((select: boolean | undefined) => void))
        this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
        return
    }
}
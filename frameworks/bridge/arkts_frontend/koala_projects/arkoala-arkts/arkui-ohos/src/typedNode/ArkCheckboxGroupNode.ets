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

import { InteropNativeModule, RuntimeType, runtimeType } from "@koalaui/interop";
import { ArkBaseNode } from "./ArkBaseNode";
import { ArkCheckboxGroupPeer, CheckboxGroupOptions, CheckboxGroupAttribute, CheckBoxShape, MarkStyle,
    OnCheckboxGroupChangeCallback, ResourceColor, Bindable } from "../framework";

export class ArkCheckboxGroupNode extends ArkBaseNode implements CheckboxGroupAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: CheckboxGroupOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (CheckboxGroupOptions | undefined);
        }
        this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    getPeer(): ArkCheckboxGroupPeer {
        return this.peer as ArkCheckboxGroupPeer;
    }
    initialize(options?: CheckboxGroupOptions): this {
        const options_casted = options as (CheckboxGroupOptions | undefined);
        this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    setCheckboxGroupOptions(options?: CheckboxGroupOptions): this {
        const options_casted = options as (CheckboxGroupOptions | undefined);
        this.getPeer()?.setCheckboxGroupOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    selectAll(value: boolean | Bindable<boolean> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (boolean | undefined);
            this.getPeer()?.setSelectAllAttribute(value_casted);
            this.markDirty();
            return this;
        }
        this.markDirty();
        return this;
    }
    selectedColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setSelectedColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    unselectedColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setUnselectedColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    mark(value: MarkStyle | undefined): this {
        const value_casted = value as (MarkStyle | undefined);
        this.getPeer()?.setMarkAttribute(value_casted);
        this.markDirty();
        return this;
    }
    onChange(value: OnCheckboxGroupChangeCallback | undefined): this {
        const value_casted = value as (OnCheckboxGroupChangeCallback | undefined);
        this.getPeer()?.setOnChangeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    checkboxShape(value: CheckBoxShape | undefined): this {
        const value_casted = value as (CheckBoxShape | undefined);
        this.getPeer()?.setCheckboxShapeAttribute(value_casted);
        this.markDirty();
        return this;
    }
}
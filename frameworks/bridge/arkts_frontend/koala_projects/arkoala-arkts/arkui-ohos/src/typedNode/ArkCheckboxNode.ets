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
import { ArkCheckboxPeer, CheckboxOptions, CheckboxAttribute, CheckBoxShape, MarkStyle, OnCheckboxChangeCallback,
    CheckBoxConfiguration, ResourceColor, Bindable } from "../framework";
import { ContentModifier } from "#handwritten";
import { hookCheckBoxContentModifier } from '../hooks/content_modifiers/ContentModifierHooks';

export class ArkCheckboxNode extends ArkBaseNode implements CheckboxAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        } 
        let options_casted: CheckboxOptions | undefined = undefined;
        if (param.length === 1) {
            options_casted = param[0] as (CheckboxOptions | undefined);
        }
        this.getPeer()?.setCheckboxOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    getPeer(): ArkCheckboxPeer {
        return this.peer as ArkCheckboxPeer;
    }
    initialize(options?: CheckboxOptions): this {
        const options_casted = options as (CheckboxOptions | undefined);
        this.getPeer()?.setCheckboxOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    setCheckboxOptions(options?: CheckboxOptions): this {
        const options_casted = options as (CheckboxOptions | undefined);
        this.getPeer()?.setCheckboxOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    select(value: boolean | Bindable<boolean> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (boolean | undefined)
            this.getPeer()?.setSelectAttribute(value_casted)
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
    shape(value: CheckBoxShape | undefined): this {
        const value_casted = value as (CheckBoxShape | undefined);
        this.getPeer()?.setShapeAttribute(value_casted);
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
    onChange(value: OnCheckboxChangeCallback | undefined): this {
        const value_casted = value as (OnCheckboxChangeCallback | undefined);
        this.getPeer()?.setOnChangeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    contentModifier(value: ContentModifier<CheckBoxConfiguration> | undefined): this {
        const value_casted = value as (ContentModifier<CheckBoxConfiguration> | undefined);
        hookCheckBoxContentModifier(this.getPeer(), value_casted);
        this.markDirty();
        return this;
    }
}
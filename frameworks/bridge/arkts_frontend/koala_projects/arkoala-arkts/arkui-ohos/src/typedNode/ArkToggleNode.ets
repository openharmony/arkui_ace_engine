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

import { ArkBaseNode } from "./ArkBaseNode";
import {
    ArkTogglePeer, ToggleOptions, ToggleAttribute, SwitchStyle, ToggleConfiguration, ResourceColor
} from "../framework";
import { ContentModifier } from "#handwritten";
import { hookToggleContentModifier } from "../hooks/content_modifiers/ContentModifierHooks";

export class ArkToggleNode extends ArkBaseNode implements ToggleAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: ToggleOptions;
        if (param.length === 1) {
            options_casted = param[0] as ToggleOptions;
        }
        this.markDirty();
        return this;
    }
    getPeer(): ArkTogglePeer {
        return this.peer as ArkTogglePeer
    }
    initialize(options: ToggleOptions): this {
        const options_casted = options as (ToggleOptions)
        this.getPeer()?.setToggleOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    onChange(value: ((isVisible: boolean) => void) | undefined): this {
        const value_casted = value as (((isVisible: boolean) => void) | undefined);
        this.getPeer()?.setOnChangeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    contentModifier(value: ContentModifier<ToggleConfiguration> | undefined): this {
        const value_casted = value as (ContentModifier<ToggleConfiguration> | undefined);
        hookToggleContentModifier(this.getPeer(), value_casted);
        this.markDirty();
        return this;
    }
    selectedColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setSelectedColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    switchPointColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setSwitchPointColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    switchStyle(value: SwitchStyle | undefined): this {
        const value_casted = value as (SwitchStyle | undefined);
        this.getPeer()?.setSwitchStyleAttribute(value_casted);        
        this.markDirty();
        return this;
    }
}
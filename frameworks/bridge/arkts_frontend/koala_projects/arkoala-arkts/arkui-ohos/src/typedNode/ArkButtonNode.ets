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
import { ButtonAttribute, ButtonRole, ButtonStyleMode, ButtonType, ControlSize, FontStyle, Length,
    ArkButtonPeer, ButtonOptions, ButtonConfiguration, ResourceStr, ResourceColor, ButtonLabelStyle,
    FontWeight } from "../framework";
import { Resource } from "global.resource";
import { ContentModifier } from "#handwritten";
import { hookButtonContentModifier } from '../hooks/content_modifiers/ContentModifierHooks';
export class ArkButtonNode extends ArkBaseNode implements ButtonAttribute {
    constructParam(...params: Object[]): this {
        if (params.length > 2) {
            throw new Error('more than 2 parameters');
        }
        let content_casted: ResourceStr | undefined = undefined;
        let options_casted: ButtonOptions | undefined = undefined;
        if (params.length >= 1) {
            if (typeof (params[0]) == "string") {
                content_casted = params[0] as string;
            } else if (typeof (params[0]) == "object") {
                content_casted = params[0] as string;
            }
        }
        if (params.length == 2) {
            const param1_type = runtimeType(params[1]);
            if (RuntimeType.OBJECT == param1_type) {
                options_casted = params[1] as ButtonOptions;
            }
        }
        if (content_casted && options_casted) {
            this.getPeer().setButtonOptions0Attribute(content_casted, options_casted);
        } else if (!content_casted && options_casted) {
            this.getPeer().setButtonOptions1Attribute(options_casted);
        }
        this.markDirty();
        return this;
    }
    getPeer(): ArkButtonPeer {
        return this.peer as ArkButtonPeer;
    }
    initialize(): this {
        this.markDirty();
        return this;
    }
    initializeWithChild(options: ButtonOptions): this {
        const options_casted = options as (ButtonOptions);
        this.markDirty();
        this.getPeer()?.setButtonOptions1Attribute(options_casted);
        return this;
    }
    initializeWithLabel(label: ResourceStr, options?: ButtonOptions): this {
        const label_casted = label as (ResourceStr);
        const options_casted = options as (ButtonOptions | undefined);
        this.getPeer()?.setButtonOptions0Attribute(label_casted, options_casted);
        this.markDirty();
        return this;
    }
    type(value: ButtonType | undefined): this {
        const value_casted = value as (ButtonType | undefined);
        this.getPeer()?.setTypeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    stateEffect(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.setStateEffectAttribute(value_casted);
        this.markDirty();
        return this;
    }
    buttonStyle(value: ButtonStyleMode | undefined): this {
        const value_casted = value as (ButtonStyleMode | undefined);
        this.getPeer()?.setButtonStyleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    controlSize(value: ControlSize | undefined): this {
        const value_casted = value as (ControlSize | undefined);
        this.getPeer()?.setControlSizeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    role(value: ButtonRole | undefined): this {
        const value_casted = value as (ButtonRole | undefined);
        this.getPeer()?.setRoleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setFontColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontSize(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setFontSizeAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontWeight(value: int | FontWeight | string | undefined): this {
        const value_casted = value as (int | FontWeight | string | undefined);
        this.getPeer()?.setFontWeightAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontStyle(value: FontStyle | undefined): this {
        const value_casted = value as (FontStyle | undefined);
        this.getPeer()?.setFontStyleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontFamily(value: string | Resource | undefined): this {
        const value_casted = value as (string | Resource | undefined);
        this.getPeer()?.setFontFamilyAttribute(value_casted);
        this.markDirty();
        return this;
    }
    contentModifier(value: ContentModifier<ButtonConfiguration> | undefined): this {
        hookButtonContentModifier(this.getPeer(), value);
        this.markDirty();
        return this;
    }
    labelStyle(value: ButtonLabelStyle | undefined): this {
        const value_casted = value as (ButtonLabelStyle | undefined);
        this.getPeer()?.setLabelStyleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    minFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined);
        this.getPeer()?.setMinFontScaleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    maxFontScale(value: number | Resource | undefined): this {
        const value_casted = value as (number | Resource | undefined);
        this.getPeer()?.setMaxFontScaleAttribute(value_casted);
        this.markDirty();
        return this;
    }
}
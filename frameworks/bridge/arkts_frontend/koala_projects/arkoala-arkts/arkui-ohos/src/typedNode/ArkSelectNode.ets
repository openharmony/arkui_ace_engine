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
import {
    ArkSelectPeer, SelectOption, SelectAttribute, ArrowPosition, AvoidanceMode, BlurStyle,
    ControlSize, DividerOptions, DividerStyleOptions, Font, MenuAlignType,  MenuOutlineOptions, Offset,
    OnSelectCallback, SymbolGlyphModifier, TextModifier, Dimension, Length, OptionWidthMode, ResourceStr,
    ResourceColor,
    MenuItemConfiguration,
    Bindable
} from "../framework";
import { Resource } from "global.resource";
import { ContentModifier, hookSelectSetDividerMethod } from "#handwritten";

export class ArkSelectNode extends ArkBaseNode implements SelectAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: Array<SelectOption> = param[0] as Array<SelectOption>;
        this.getPeer()?.setSelectOptionsAttribute(options_casted);
        this.markDirty();
        return this;
    }
    getPeer(): ArkSelectPeer {
        return this.peer as ArkSelectPeer
    }
    initialize(options: Array<SelectOption>): this {
        const options_casted = options as Array<SelectOption>
        this.getPeer()?.setSelectOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    setSelectOptions(options: SelectOption[]): this {
        const options_casted = options as Array<SelectOption>
        this.getPeer()?.setSelectOptionsAttribute(options_casted)
        this.markDirty();
        return this;
    }
    selected(value: int | Resource | Bindable<int> | Bindable<Resource> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (int | Resource | undefined);
            this.getPeer()?.setSelectedAttribute(value_casted);
            this.markDirty();
            return this;
        }
        this.markDirty();
        return this;
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        const value_casted = value as (ResourceStr | Bindable<string> | Bindable<Resource> | undefined);
        this.getPeer()?.setValueAttribute(value_casted);
        this.markDirty();
        return this;
    }
    font(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.setFontAttribute(value_casted);
        this.markDirty();
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setFontColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setSelectedOptionBgColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    selectedOptionFont(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.setSelectedOptionFontAttribute(value_casted);
        this.markDirty();
        return this;
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setSelectedOptionFontColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    optionBgColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setOptionBgColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    optionFont(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.setOptionFontAttribute(value_casted);
        this.markDirty();
        return this;
    }
    optionFontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setOptionFontColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    onSelect(value: ((index: int, value: string) => void) | OnSelectCallback | undefined): this {
        const value_casted = value as (((index: int, value: string) => void) | OnSelectCallback | undefined);
        this.getPeer()?.setOnSelectAttribute(value_casted);
        this.markDirty();
        return this;
    }
    space(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.setSpaceAttribute(value_casted);
        this.markDirty();
        return this;
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        const value_casted = value as (ArrowPosition | undefined);
        this.getPeer()?.setArrowPositionAttribute(value_casted);
        this.markDirty();
        return this;
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        const value_casted = value as (Dimension | OptionWidthMode | undefined);
        this.getPeer()?.setOptionWidthAttribute(value_casted);
        this.markDirty();
        return this;
    }
    optionHeight(value: Dimension | undefined): this {
        const value_casted = value as (Dimension | undefined);
        this.getPeer()?.setOptionHeightAttribute(value_casted);
        this.markDirty();
        return this;
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.setMenuBackgroundColorAttribute(value_casted);
        this.markDirty();
        return this;
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        const value_casted = value as (BlurStyle | undefined);
        this.getPeer()?.setMenuBackgroundBlurStyleAttribute(value_casted);
        this.markDirty();
        return this;
    }
    controlSize(value: ControlSize | undefined): this {
        const value_casted = value as ( ControlSize | undefined);
        this.getPeer()?.setControlSizeAttribute(value_casted);        
        this.markDirty();
        return this;
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        this.markDirty();
        return this;
    }
    divider(value: DividerOptions | null | undefined): this {
        hookSelectSetDividerMethod(this.getPeer(), value);
        this.markDirty();
        return this;
    }
    textModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.setTextModifierAttribute(value_casted);  
        this.markDirty();
        return this;
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        const value_casted = value as ( SymbolGlyphModifier | undefined);
        this.getPeer()?.setArrowModifierAttribute(value_casted);  
        this.markDirty();
        return this;
    }
    optionTextModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.setOptionTextModifierAttribute(value_casted);  
        this.markDirty();
        return this;
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.setSelectedOptionTextModifierAttribute(value_casted);  
        this.markDirty();
        return this;
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        const value_casted = value as ( DividerStyleOptions | undefined);
        this.getPeer()?.setDividerStyleAttribute(value_casted); 
        this.markDirty();
        return this;
    }
    avoidance(value: AvoidanceMode | undefined): this {
        const value_casted = value as ( AvoidanceMode | undefined);
        this.getPeer()?.setAvoidanceAttribute(value_casted); 
        this.markDirty();
        return this;
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        const value_casted = value as ( MenuOutlineOptions | undefined);
        this.getPeer()?.setMenuOutlineAttribute(value_casted); 
        this.markDirty();
        return this;
    }
    setShowInSubWindow(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.setShowInSubWindowAttribute(value_casted);
        this.markDirty();
        return this;
    }
    showDefaultSelectedIcon(value: boolean | undefined): this {
        const value_casted = value as (boolean | undefined);
        this.getPeer()?.setShowDefaultSelectedIconAttribute(value_casted);
        this.markDirty();
        return this;
    }
    backgroundColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined)
        this.getPeer()?.setBackgroundColorAttribute(value_casted)
        this.markDirty();
        return this;
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset | undefined): this {
        const alignType_casted = alignType as ( MenuAlignType | undefined);
        const offset_casted = offset as ( Offset | undefined);
        this.getPeer()?.setMenuAlignAttribute(alignType_casted, offset_casted);         
        this.markDirty();
        return this;
    }
}
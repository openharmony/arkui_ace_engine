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
} from "../../component";
import { Resource } from "global.resource"
import { ContentModifier } from "@component_handwritten/common";
import { SelectOpsHandWritten } from "../SelectOpsHandWritten";

export class ArkSelectNode extends ArkBaseNode implements SelectAttribute {
    constructParam(...param: Object[]): this {
        if (param.length > 1) {
            throw new Error('more than 1 parameters');
        }
        let options_casted: Array<SelectOption> = param[0] as Array<SelectOption>;
        this.getPeer()?.setSelectOptionsAttribute(options_casted);
        return this;
    }
    getPeer(): ArkSelectPeer {
        return this.peer as ArkSelectPeer
    }
    initialize(options: Array<SelectOption>): this {
        const options_casted = options as Array<SelectOption>
        this.getPeer()?.setSelectOptionsAttribute(options_casted)
        return this;
    }
    setSelectOptions(options: SelectOption[]): this {
        const options_casted = options as Array<SelectOption>
        this.getPeer()?.setSelectOptionsAttribute(options_casted)
        return this;
    }
    selected(value: number | Resource | Bindable<number> | Bindable<Resource> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (number | Resource | undefined);
            this.getPeer()?.selected0Attribute(value_casted);
            return this;
        }
        SelectOpsHandWritten.hookSelectAttributeSelectedImpl(this.getPeer().peer.ptr, (value as Bindable<number | Resource>))
    }
    value(value: ResourceStr | Bindable<string> | Bindable<Resource> | undefined): this {
        const value_type = runtimeType(value);
        if ((RuntimeType.BOOLEAN === value_type) || (RuntimeType.UNDEFINED === value_type)) {
            const value_casted = value as (ResourceStr | undefined);
            this.getPeer()?.value0Attribute(value_casted);
            return this;
        }
        SelectOpsHandWritten.hookSelectAttributeValueImpl(this.getPeer().peer.ptr, (value as Bindable<ResourceStr>))
    }
    font(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.font0Attribute(value_casted);
        return this;
    }
    fontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.fontColor0Attribute(value_casted);
        return this;
    }
    selectedOptionBgColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.selectedOptionBgColor0Attribute(value_casted);
        return this;
    }
    selectedOptionFont(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.selectedOptionFont0Attribute(value_casted);
        return this;
    }
    selectedOptionFontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.selectedOptionFontColor0Attribute(value_casted);
        return this;
    }
    optionBgColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.optionBgColor0Attribute(value_casted);
        return this;
    }
    optionFont(value: Font | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.optionFont0Attribute(value_casted);
        return this;
    }
    optionFontColor(value: ResourceColor | undefined): this {
        const value_casted = value as (Font | undefined);
        this.getPeer()?.optionFontColor0Attribute(value_casted);
        return this;
    }
    onSelect(value: ((index: number, value: string) => void) | OnSelectCallback | undefined): this {
        const value_casted = value as (((index: number, value: string) => void) | OnSelectCallback | undefined);
        this.getPeer()?.onSelect0Attribute(value_casted);
        return this;
    }
    space(value: Length | undefined): this {
        const value_casted = value as (Length | undefined);
        this.getPeer()?.space0Attribute(value_casted);
        return this;
    }
    arrowPosition(value: ArrowPosition | undefined): this {
        const value_casted = value as (ArrowPosition | undefined);
        this.getPeer()?.arrowPosition0Attribute(value_casted);
        return this;
    }
    optionWidth(value: Dimension | OptionWidthMode | undefined): this {
        const value_casted = value as (Dimension | OptionWidthMode | undefined);
        this.getPeer()?.optionWidth0Attribute(value_casted);
        return this;
    }
    optionHeight(value: Dimension | undefined): this {
        const value_casted = value as (Dimension | undefined);
        this.getPeer()?.optionHeight0Attribute(value_casted);
        return this;
    }
    menuBackgroundColor(value: ResourceColor | undefined): this {
        const value_casted = value as (ResourceColor | undefined);
        this.getPeer()?.menuBackgroundColor0Attribute(value_casted);
        return this;
    }
    menuBackgroundBlurStyle(value: BlurStyle | undefined): this {
        const value_casted = value as (BlurStyle | undefined);
        this.getPeer()?.menuBackgroundBlurStyle0Attribute(value_casted);
        return this;
    }
    controlSize(value: ControlSize | undefined): this {
        const value_casted = value as ( ControlSize | undefined);
        this.getPeer()?.controlSize0Attribute(value_casted);        
        return this;
    }
    menuItemContentModifier(value: ContentModifier<MenuItemConfiguration> | undefined): this {
        return this;
    }
    divider(value: DividerOptions | null | undefined): this {
        const value_casted = value as ( DividerOptions | null | undefined);
        this.getPeer()?.dividerAttribute(value_casted);  
        return this;
    }
    textModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.textModifierAttribute(value_casted);  
        return this;
    }
    arrowModifier(value: SymbolGlyphModifier | undefined): this {
        const value_casted = value as ( SymbolGlyphModifier | undefined);
        this.getPeer()?.arrowModifierAttribute(value_casted);  
        return this;
    }
    optionTextModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.optionTextModifierAttribute(value_casted);  
        return this;
    }
    selectedOptionTextModifier(value: TextModifier | undefined): this {
        const value_casted = value as ( TextModifier | undefined);
        this.getPeer()?.selectedOptionTextModifierAttribute(value_casted);  
        return this;
    }
    dividerStyle(value: DividerStyleOptions | undefined): this {
        const value_casted = value as ( DividerStyleOptions | undefined);
        this.getPeer()?.dividerStyleAttribute(value_casted); 
        return this;
    }
    avoidance(value: AvoidanceMode | undefined): this {
        const value_casted = value as ( AvoidanceMode | undefined);
        this.getPeer()?.avoidanceAttribute(value_casted); 
        return this;
    }
    menuOutline(value: MenuOutlineOptions | undefined): this {
        const value_casted = value as ( MenuOutlineOptions | undefined);
        this.getPeer()?.menuOutlineAttribute(value_casted); 
        return this;
    }
    menuAlign(alignType: MenuAlignType | undefined, offset?: Offset | undefined): this {
        const alignType_casted = alignType as ( MenuAlignType | undefined);
        const offset_casted = offset as ( Offset | undefined);
        this.getPeer()?.menuAlign0Attribute(alignType_casted, offset_casted);         
        return this;
    }
    _onChangeEvent_selected(callback: (selected: number | Resource | undefined) => void): void {
        const callback_casted = callback as (((selected: number | Resource | undefined) => void))
        this.getPeer()?._onChangeEvent_selectedAttribute(callback_casted)
        return;
    }
    _onChangeEvent_value(callback: (value: ResourceStr | undefined) => void): void {
        const callback_casted = callback as (((value: ResourceStr | undefined) => void))
        this.getPeer()?._onChangeEvent_valueAttribute(callback_casted)
        return;
    }
}
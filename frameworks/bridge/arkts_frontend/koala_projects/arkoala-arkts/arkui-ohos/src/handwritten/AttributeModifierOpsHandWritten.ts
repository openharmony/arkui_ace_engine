/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from '../component/common';
import { ArkButtonComponent, ButtonAttribute } from '../component/button'
import { ArkTextComponent, TextAttribute, ArkTextPeer, TextOptions } from '../component/text'
import { ArkSymbolGlyphComponent, SymbolGlyphAttribute, ArkSymbolGlyphPeer } from '../component/symbolglyph'
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { TextModifier } from '../TextModifier';
import { ButtonModifier } from "../ButtonModifier";
import { SymbolGlyphModifier } from '../SymbolGlyphModifier';
import { Resource } from "global.resource"
import { ColumnModifier } from '../ColumnModifier';
import { ArkColumnComponent, ColumnAttribute, ArkColumnPeer } from '../component/column'
import { runtimeType, RuntimeType } from "@koalaui/interop"
export function hookButtonAttributeModifier(component: ArkButtonComponent, modifier: AttributeModifier<ButtonAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ButtonModifier => {
        let isButtonModifier: boolean = modifier instanceof ButtonModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ButtonModifier();
        if (isButtonModifier) {
            let buttonModifier = modifier as object as ButtonModifier;
            initModifier.mergeModifier(buttonModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkButtonComponent => {
        let componentNew: ArkButtonComponent = new ArkButtonComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ButtonAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
 export function hookTextAttributeModifier(component: ArkTextComponent, modifier: AttributeModifier<TextAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return ;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return ;
    }
    let attributeSet = (): TextModifier => {
        let isTextModifier: boolean = modifier instanceof TextModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new TextModifier();
        if (isTextModifier) {
            let textModifier = modifier as object as TextModifier;
            initModifier.mergeModifier(textModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length > 2) {
            throw new Error('more than 2 parameters')
        }
        let content_casted: string | Resource | undefined = undefined
        let value_casted: TextOptions | undefined = undefined
        if (params.length >= 1) {
            if (typeof (params[0]) == "string") {
                content_casted = params[0] as string
            } else if (typeof (params[0]) == "object") {
                content_casted = params[0] as string
            }
        }
        if (params.length == 2) {
            const param1_type = runtimeType(params[1])
            if (RuntimeType.OBJECT == param1_type) {
                value_casted = params[1] as TextOptions
            }
        }
        let textPeer: ArkTextPeer = component.getPeer() as Object as ArkTextPeer;
        textPeer.setTextOptionsAttribute(content_casted, value_casted)
    };
    let updaterReceiver = (): ArkTextComponent => {
        let initComponent: ArkTextComponent = new ArkTextComponent();
        initComponent.setPeer(component.getPeer());
        return initComponent;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<TextAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
export function hookSymbolGlyphAttributeModifier(component: ArkSymbolGlyphComponent,
    modifier: AttributeModifier<SymbolGlyphAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): SymbolGlyphModifier => {
        let isSymbolGlyphModifier: boolean = modifier instanceof SymbolGlyphModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new SymbolGlyphModifier();
        if (isSymbolGlyphModifier) {
            let symbolGlyphModifier = modifier as object as SymbolGlyphModifier;
            initModifier.mergeModifier(symbolGlyphModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length > 1) {
            throw new Error('more than 1 parameters')
        }
        let value_casted: Resource | undefined = undefined
        if (params.length >= 0) {
            value_casted = params[0] as Resource
        }
        let symbolGlyphPeer: ArkSymbolGlyphPeer = component.getPeer() as Object as ArkSymbolGlyphPeer;
        symbolGlyphPeer.setSymbolGlyphOptionsAttribute(value_casted)
    };
    let updaterReceiver = (): ArkSymbolGlyphComponent => {
        let componentNew: ArkSymbolGlyphComponent = new ArkSymbolGlyphComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<SymbolGlyphAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
export function hookColumnAttributeModifier(component: ArkColumnComponent,
    modifier: AttributeModifier<ColumnAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): ColumnModifier => {
        let isColumnModifier: boolean = modifier instanceof ColumnModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new ColumnModifier();
        if (isColumnModifier) {
            let ColumnModifier = modifier as object as ColumnModifier;
            initModifier.mergeModifier(ColumnModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkColumnComponent => {
        let componentNew: ArkColumnComponent = new ArkColumnComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<ColumnAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

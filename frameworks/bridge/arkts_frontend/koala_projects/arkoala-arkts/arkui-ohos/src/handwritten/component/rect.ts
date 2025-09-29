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


import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from './common';
import { applyAttributeModifierBase, applyCommonModifier } from "../handwritten/modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { RectModifier } from '../RectModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"


function hookRectAttributeModifier(component: ArkRectComponent, modifier: AttributeModifier<RectAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): RectModifier => {
        let isRectModifier: boolean = modifier instanceof RectModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new RectModifier();
        if (isRectModifier) {
            let rectModifier = modifier as object as RectModifier;
            initModifier.mergeModifier(rectModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
        if (params.length < 1) {
            return;
        }
        let options_casted: RectOptions | undefined = undefined
        const param1_type = runtimeType(params[0])
        if (RuntimeType.OBJECT == param1_type) {
            options_casted = params[0] as RectOptions
        }
        let peer: ArkRectPeer = component.getPeer() as Object as ArkRectPeer;
        peer?.setRectOptionsAttribute(options_casted)
    };
    let updaterReceiver = (): ArkRectComponent => {
        let componentNew: ArkRectComponent = new ArkRectComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<RectAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

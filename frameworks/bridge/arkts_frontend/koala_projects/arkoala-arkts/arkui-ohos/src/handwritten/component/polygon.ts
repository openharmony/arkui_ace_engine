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
import { PolygonModifier } from '../PolygonModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"


function hookPolygonAttributeModifier(component: ArkPolygonComponent, modifier: AttributeModifier<PolygonAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): PolygonModifier => {
        let isPolygonModifier: boolean = modifier instanceof PolygonModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new PolygonModifier();
        if (isPolygonModifier) {
            let polygonModifier = modifier as object as PolygonModifier;
            initModifier.mergeModifier(polygonModifier);
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
        let options_casted: PolygonOptions | undefined = undefined
        const param1_type = runtimeType(params[0])
        if (RuntimeType.OBJECT == param1_type) {
            options_casted = params[0] as PolygonOptions
        }
        let peer: ArkPolygonPeer = component.getPeer() as Object as ArkPolygonPeer;
        peer?.setPolygonOptionsAttribute(options_casted)
    };
    let updaterReceiver = (): ArkPolygonComponent => {
        let componentNew: ArkPolygonComponent = new ArkPolygonComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<PolygonAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

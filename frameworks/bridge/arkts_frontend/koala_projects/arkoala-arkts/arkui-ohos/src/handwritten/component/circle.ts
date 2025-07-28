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
import { CommonShapeMethodModifier } from '../CommonShapeMethodModifier';
import { CommonModifier } from '../CommonModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"
import { PeerNode } from '../PeerNode';
import { CommonMethodModifier } from '../CommonMethodModifier';


export class CircleModifier extends CommonShapeMethodModifier implements CircleAttribute, AttributeModifier<CircleAttribute> {
    _instanceId: number = -1;
    setInstanceId(instanceId: number): void {
        this._instanceId = instanceId
    }
    applyNormalAttribute(instance: CircleAttribute): void { }
    applyPressedAttribute(instance: CircleAttribute): void { }
    applyFocusedAttribute(instance: CircleAttribute): void { }
    applyDisabledAttribute(instance: CircleAttribute): void { }
    applySelectedAttribute(instance: CircleAttribute): void { }
    applyModifierPatch(peer: PeerNode): void {
        super.applyModifierPatch(peer)
    }
    mergeModifier(modifier: CommonMethodModifier): void {
        super.mergeModifier(modifier)
    }
}

function hookCircleAttributeModifier(component: ArkCircleComponent, modifier: AttributeModifier<CircleAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): CircleModifier => {
        let isCircleModifier: boolean = modifier instanceof CircleModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new CircleModifier();
        if (isCircleModifier) {
            let circleModifier = modifier as object as CircleModifier;
            initModifier.mergeModifier(circleModifier);
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
        let options_casted: CircleOptions | undefined = undefined
        const param1_type = runtimeType(params[0])
        if (RuntimeType.OBJECT == param1_type) {
            options_casted = params[0] as CircleOptions
        }
        let peer: ArkCirclePeer = component.getPeer() as Object as ArkCirclePeer;
        peer?.setCircleOptionsAttribute(options_casted)
    };
    let updaterReceiver = (): ArkCircleComponent => {
        let componentNew: ArkCircleComponent = new ArkCircleComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<CircleAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

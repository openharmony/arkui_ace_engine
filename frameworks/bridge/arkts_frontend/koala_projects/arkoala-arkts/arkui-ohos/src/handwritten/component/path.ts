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
import { PathModifier } from '../PathModifier';
import { runtimeType, RuntimeType } from "@koalaui/interop"


function hookPathAttributeModifier(component: ArkPathComponent, modifier: AttributeModifier<PathAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): PathModifier => {
        let isPathModifier: boolean = modifier instanceof PathModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new PathModifier();
        if (isPathModifier) {
            let pathModifier = modifier as object as PathModifier;
            initModifier.mergeModifier(pathModifier);
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
        let options_casted: PathOptions | undefined = undefined
        const param1_type = runtimeType(params[0])
        if (RuntimeType.OBJECT == param1_type) {
            options_casted = params[0] as PathOptions
        }
        let peer: ArkPathPeer = component.getPeer() as Object as ArkPathPeer;
        peer?.setPathOptionsAttribute(options_casted)
    };
    let updaterReceiver = (): ArkPathComponent => {
        let componentNew: ArkPathComponent = new ArkPathComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<PathAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

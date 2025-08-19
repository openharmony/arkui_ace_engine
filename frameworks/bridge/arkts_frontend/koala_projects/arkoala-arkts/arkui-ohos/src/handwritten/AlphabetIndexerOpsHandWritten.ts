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

import { KPointer } from "@koalaui/interop"
import { AlphabetIndexerOps, Bindable } from "../component"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from '../component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { AlphabetIndexerModifier } from "../AlphabetIndexerModifier"
import { ArkAlphabetIndexerComponent, AlphabetIndexerAttribute } from '../component/alphabetIndexer'

export class AlphabetIndexerOpsHandWritten {
    static hookAlphabetIndexerAttributeSelectedImpl(node: KPointer, value: Bindable<number>) {
        AlphabetIndexerOps.registerIndexerSelectedCallback(node, value.value, (v) => {
            value.onChange(v)
        })
    }
}

export function hookAlphabetIndexerAttributeModifier(component: ArkAlphabetIndexerComponent, modifier: AttributeModifier<AlphabetIndexerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): AlphabetIndexerModifier => {
        let isAlphabetIndexerModifier: boolean = modifier instanceof AlphabetIndexerModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new AlphabetIndexerModifier();
        if (isAlphabetIndexerModifier) {
            let AlphabetIndexerModifier = modifier as object as AlphabetIndexerModifier;
            initModifier.mergeModifier(AlphabetIndexerModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkAlphabetIndexerComponent => {
        let componentNew: ArkAlphabetIndexerComponent = new ArkAlphabetIndexerComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<AlphabetIndexerAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

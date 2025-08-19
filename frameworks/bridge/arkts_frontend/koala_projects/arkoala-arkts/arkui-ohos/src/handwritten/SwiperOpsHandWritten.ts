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
import { SwiperOps, Bindable } from "../component"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from 'arkui/component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { SwiperModifier } from "../SwiperModifier"
import { ArkSwiperComponent, SwiperAttribute } from 'arkui/component/swiper'

export class SwiperOpsHandWritten {
    static hookSwiperAttributeIndexImpl(node: KPointer, value: Bindable<number>) {
        SwiperOps.registerIndexCallback(node, value.value, (v) => {
            value.onChange(v)
        })
    }
}

export function hookSwiperAttributeModifier(component: ArkSwiperComponent, modifier: AttributeModifier<SwiperAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): SwiperModifier => {
        let isSwiperModifier: boolean = modifier instanceof SwiperModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new SwiperModifier();
        if (isSwiperModifier) {
            let swiperModifier = modifier as object as SwiperModifier;
            initModifier.mergeModifier(swiperModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkSwiperComponent => {
        let componentNew: ArkSwiperComponent = new ArkSwiperComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<SwiperAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
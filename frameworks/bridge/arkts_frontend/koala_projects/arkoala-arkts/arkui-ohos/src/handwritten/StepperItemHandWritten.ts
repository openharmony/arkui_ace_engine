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

import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from 'arkui/component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { StepperItemModifier } from "../StepperItemModifier"
import { ArkStepperItemComponent, StepperItemAttribute } from 'arkui/component/stepperItem'

export function hookStepperItemAttributeModifier(component: ArkStepperItemComponent, modifier: AttributeModifier<StepperItemAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): StepperItemModifier => {
        let isStepperItemModifier: boolean = modifier instanceof StepperItemModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new StepperItemModifier();
        if (isStepperItemModifier) {
            let stepperItemModifier = modifier as object as StepperItemModifier;
            initModifier.mergeModifier(stepperItemModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkStepperItemComponent => {
        let componentNew: ArkStepperItemComponent = new ArkStepperItemComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<StepperItemAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

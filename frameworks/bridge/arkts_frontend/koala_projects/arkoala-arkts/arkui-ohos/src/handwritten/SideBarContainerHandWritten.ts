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
import { Length } from "../component"
import { SideBarContainerHandWrittenImpl } from "./SideBarContainerHandWrittenImpl"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from 'arkui/component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { SideBarContainerModifier } from "../SideBarContainerModifier"
import { ArkSideBarContainerComponent, DividerStyle, SideBarContainerAttribute } from 'arkui/component/sidebar'

export function hookSideBarContainerSideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
    SideBarContainerHandWrittenImpl.SideBarWidthImpl(node, value)
}

export function hookSideBarContainerMinSideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
    SideBarContainerHandWrittenImpl.MinSideBarWidthImpl(node, value)
}

export function hookSideBarContainerMaxSideBarWidthImpl(node: KPointer, value: number | Length | undefined) {
    SideBarContainerHandWrittenImpl.MaxSideBarWidthImpl(node, value)
}

export function hookSideBarContainerDividerImpl(node: KPointer, value: DividerStyle | null | undefined) {
    SideBarContainerHandWrittenImpl.DividerImpl(node, value)
}

export function hookSideBarContainerAttributeModifier(component: ArkSideBarContainerComponent, modifier: AttributeModifier<SideBarContainerAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): SideBarContainerModifier => {
        let isSideBarContainerModifier: boolean = modifier instanceof SideBarContainerModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new SideBarContainerModifier();
        if (isSideBarContainerModifier) {
            let sideBarContainerModifier = modifier as object as SideBarContainerModifier;
            initModifier.mergeModifier(sideBarContainerModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkSideBarContainerComponent => {
        let componentNew: ArkSideBarContainerComponent = new ArkSideBarContainerComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<SideBarContainerAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
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
import { NavigationTitleOptions, NavDestinationContext, CustomBuilder, NavDestinationCommonTitle, NavDestinationCustomTitle, ResourceStr, Callback } from "../component"
import { SymbolGlyphModifier } from "../SymbolGlyphModifier"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { NavDestinationHandWrittenImpl } from "./NavDestinationHandWrittenImpl"
import { NavDestinationModifier } from "../NavDestinationModifier"
import { ArkNavDestinationComponent, NavDestinationAttribute } from 'arkui/component/navDestination'
import { CommonModifier } from '../CommonModifier';
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from 'arkui/component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";

export function hookNavDestinationTitleImpl(node: KPointer, value: string | CustomBuilder | NavDestinationCommonTitle |
    NavDestinationCustomTitle | Resource | undefined, options?: NavigationTitleOptions) {
    NavDestinationHandWrittenImpl.TitleImpl(node, value, options)
}

export function hookNavDestinationBackButtonIconImpl(node: KPointer, value: ResourceStr | PixelMap | SymbolGlyphModifier | undefined, accessibilityText?: ResourceStr) {
    NavDestinationHandWrittenImpl.BackButtonIconImpl(node, value, accessibilityText)
}

export function hookNavDestinationOnWillAppearImpl(node: KPointer, value: Callback<void> | undefined) {
    NavDestinationHandWrittenImpl.OnWillAppearImpl(node, value)
}

export function hookNavDestinationOnWillDisappearImpl(node: KPointer, value: Callback<void> | undefined) {
    NavDestinationHandWrittenImpl.OnWillDisappearImpl(node, value)
}

export function hookNavDestinationOnWillShowImpl(node: KPointer, value: Callback<void> | undefined) {
    NavDestinationHandWrittenImpl.OnWillShowImpl(node, value)
}

export function hookNavDestinationOnWillHideImpl(node: KPointer, value: Callback<void> | undefined) {
    NavDestinationHandWrittenImpl.OnWillHideImpl(node, value)
}

export function hookNavDestinationOnReadyImpl(node: KPointer, value: Callback<NavDestinationContext> | undefined) {
    NavDestinationHandWrittenImpl.OnReadyImpl(node, value)
}

export function hookNavDestinationOnNewParamImpl(node: KPointer, value: ((parameter: Object | null | undefined) => void) | undefined) {
    NavDestinationHandWrittenImpl.OnNewParamImpl(node, value)
}

export function hookNavDestinationAttributeModifier(component: ArkNavDestinationComponent, modifier: AttributeModifier<NavDestinationAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): NavDestinationModifier => {
        let isNavDestinationModifier: boolean = modifier instanceof NavDestinationModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new NavDestinationModifier();
        if (isNavDestinationModifier) {
            let navDestinationModifier = modifier as object as NavDestinationModifier;
            initModifier.mergeModifier(navDestinationModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkNavDestinationComponent => {
        let componentNew: ArkNavDestinationComponent = new ArkNavDestinationComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<NavDestinationAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
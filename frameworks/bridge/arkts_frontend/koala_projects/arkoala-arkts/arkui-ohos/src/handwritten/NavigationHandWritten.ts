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
import { NavigationTitleOptions, NavigationMenuOptions, NavigationMenuItem, NavPathStack, ToolbarItem, CustomBuilder, ResourceStr, NavigationToolbarOptions, NavigationCommonTitle, NavigationCustomTitle, NavigationAttribute } from "../component"
import { SymbolGlyphModifier } from "../SymbolGlyphModifier"
import { Resource } from "global.resource"
import { PixelMap } from "#external"
import { NavigationHandWrittenImpl } from "./NavigationHandWrittenImpl"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from 'arkui/component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { NavigationModifier } from "../NavigationModifier"
import { ArkNavigationComponent } from 'arkui/component/navigation'

export function hookNavigationTitleImpl(node: KPointer, value: ResourceStr | CustomBuilder | NavigationCommonTitle |
    NavigationCustomTitle | undefined, options?: NavigationTitleOptions) {
    NavigationHandWrittenImpl.TitleImpl(node, value, options)
}

export function hookNavigationBackButtonIconImpl(node: KPointer, value: string | PixelMap | Resource | SymbolGlyphModifier |
    undefined, accessibilityText?: ResourceStr) {
    NavigationHandWrittenImpl.BackButtonIconImpl(node, value, accessibilityText)
}

export function hookNavigationHideTitleBarImpl(node: KPointer, value: boolean | undefined, animated?: boolean) {
    NavigationHandWrittenImpl.HideTitleBarImpl(node, value, animated)
}

export function hookNavigationMenusImpl(node: KPointer, value: Array<NavigationMenuItem> | CustomBuilder | undefined,
    options?: NavigationMenuOptions) {
    NavigationHandWrittenImpl.MenusImpl(node, value, options)
}

export function hookNavigationToolbarConfigurationImpl(node: KPointer, value: Array<ToolbarItem> | CustomBuilder | undefined,
    options?: NavigationToolbarOptions) {
    NavigationHandWrittenImpl.ToolbarConfigurationImpl(node, value, options)
}

export function hookNavigationSetNavigationOptionsImpl(node: KPointer, value: NavPathStack) {
    NavigationHandWrittenImpl.SetNavigationOptionsImpl(node, value)
}

export function hookNavigationAttributeModifier(component: ArkNavigationComponent, modifier: AttributeModifier<NavigationAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): NavigationModifier => {
        let isNavigationModifier: boolean = modifier instanceof NavigationModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new NavigationModifier();
        if (isNavigationModifier) {
            let navigationModifier = modifier as object as NavigationModifier;
            initModifier.mergeModifier(navigationModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkNavigationComponent => {
        let componentNew: ArkNavigationComponent = new ArkNavigationComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<NavigationAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}
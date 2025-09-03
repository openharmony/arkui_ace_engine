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

import { KPointer, InteropNativeModule } from "@koalaui/interop"
import { TabsOps, BarMode, ScrollableBarModeOptions, BlurStyle, BackgroundBlurStyleOptions, Bindable } from "../component"
import { TabsExtender, ArkTabsComponent, TabsAttribute, ArkTabContentComponent, TabContentAttribute } from "../component"
import { ArkUIGeneratedNativeModule } from "#components"
import { ArkCommonMethodComponent, AttributeModifier, CommonMethod } from '../component/common';
import { applyAttributeModifierBase, applyCommonModifier } from "./modifiers/ArkCommonModifier";
import { CommonModifier } from '../CommonModifier';
import { TabsModifier } from "../TabsModifier"
import { TabContentModifier } from "../TabContentModifier"


export class TabsOpsHandWritten {
    static hookTabsAttributeBarModeImpl(node: KPointer, value: BarMode | undefined, options: ScrollableBarModeOptions | undefined) {
        TabsOps.registerBarMode(node, value, options)
    }

    static hookTabsAttributeBarBackgroundBlurStyleImpl(node: KPointer, style: BlurStyle | undefined, options: BackgroundBlurStyleOptions | undefined) {
        TabsOps.registerBarBackgroundBlurStyle(node, style, options)
    }

    static hookTabsAttributeIndexImpl(node: KPointer, value: Bindable<number>) {
        TabsOps.registerIndexCallback(node, value.value, (v) => {
            value.onChange(v)
        })
    }
}

export function hookTabsApplyAttributesFinish(node: ArkTabsComponent) : void {
    TabsExtender.ApplyAttributesFinish(node.getPeer().peer.ptr)
}

export function hookTabsAttributeModifier(component: ArkTabsComponent, modifier: AttributeModifier<TabsAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): TabsModifier => {
        let isTabsModifier: boolean = modifier instanceof TabsModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new TabsModifier();
        if (isTabsModifier) {
            let TabsModifier = modifier as object as TabsModifier;
            initModifier.mergeModifier(TabsModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkTabsComponent => {
        let componentNew: ArkTabsComponent = new ArkTabsComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<TabsAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

export function hookTabContentAttributeModifier(component: ArkTabContentComponent, modifier: AttributeModifier<TabContentAttribute> | AttributeModifier<CommonMethod> | undefined): void {
    if (modifier === undefined) {
        return;
    }
    let isCommonModifier: boolean = modifier instanceof CommonModifier;
    if (isCommonModifier) {
        applyCommonModifier(component.getPeer(), modifier as Object as AttributeModifier<CommonMethod>);
        return;
    }
    let attributeSet = (): TabContentModifier => {
        let isTabContentModifier: boolean = modifier instanceof TabContentModifier;
        let initModifier = component.getPeer()._attributeSet ? component.getPeer()._attributeSet! : new TabContentModifier();
        if (isTabContentModifier) {
            let TabContentModifier = modifier as object as TabContentModifier;
            initModifier.mergeModifier(TabContentModifier);
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        } else {
            component.getPeer()._attributeSet = initModifier;
            return initModifier;
        }
    }
    let constructParam = (component: ArkCommonMethodComponent, ...params: FixedArray<Object>): void => {
    };
    let updaterReceiver = (): ArkTabContentComponent => {
        let componentNew: ArkTabContentComponent = new ArkTabContentComponent();
        componentNew.setPeer(component.getPeer());
        return componentNew;
    };
    applyAttributeModifierBase(modifier as Object as AttributeModifier<TabContentAttribute>, attributeSet, constructParam, updaterReceiver, component.getPeer());
}

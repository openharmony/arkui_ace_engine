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

import { ArkCommonMethodComponent, Gesture, GestureGroup, GestureMask, GestureModifier, GestureType, BlendMode, BlendApplyType, AnimateParam, AnimationExtender } from "../component"
import { commonMethodOps} from 'arkui/component'
import { Filter, VisualEffect, BrightnessBlender } from "#external"
import { KPointer, RuntimeType, runtimeType } from "@koalaui/interop"
import {ArkUIGeneratedNativeModule } from "#components"
import { unsafeCast, int32, int64, float32 } from "@koalaui/common"
import { ArkUIAniModule } from 'arkui.ani';
import { CustomProperty } from '../component/common';

export function hookCommonMethodGestureImpl(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(0, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(0, commonMethod.getPeer(), mask)
    }
}

export function hookCommonMethodPriorityGestureImpl(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(1, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(1, commonMethod.getPeer(), mask)
    }
}

export function hookCommonMethodParallelGestureImpl(commonMethod: ArkCommonMethodComponent, gesture: GestureType | undefined, mask?: GestureMask): void {
    if (gesture instanceof Gesture) {
        let singleGesture = gesture as Gesture;
        singleGesture.setGesture(2, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(2, commonMethod.getPeer(), mask)
    }
}

export function hookCommonMethodGestureModifierImpl(commonMethod: ArkCommonMethodComponent, value: GestureModifier | undefined): void {
    if (value === undefined) {
        return;
    }
    const value_casted = value as GestureModifier
    let gestureEvent = commonMethod.getOrCreateGestureEvent();
    gestureEvent.clearGestures();
    value_casted.applyGesture(gestureEvent);
}

export function hookCommonMethodVisualEffectImpl(commonMethod: ArkCommonMethodComponent, value: VisualEffect | undefined) {
    if (value === undefined) {
        return;
    }
    if (commonMethod.getPeer()) {
        const node_casted = commonMethod.getPeer().peer.ptr as (KPointer)
        const value_casted = Object.values(value)[0] as (int64)
        commonMethodOps.VisualEffectHandWrittenImpl(node_casted, value_casted)
    }
}

export function hookCommonMethodBackgroundFilterImpl(commonMethod: ArkCommonMethodComponent, value: Filter | undefined) {
    if (value === undefined) {
        return;
    }
    if (commonMethod.getPeer()) {
        const node_casted = commonMethod.getPeer().peer.ptr as (KPointer)
        const value_casted = Object.values(value)[0] as (int64)
        commonMethodOps.BackgroundFilterHandWrittenImpl(node_casted, value_casted)
    }
}

export function hookCommonMethodForegroundFilterImpl(commonMethod: ArkCommonMethodComponent, value: Filter | undefined) {
    if (value === undefined) {
        return;
    }
    if (commonMethod.getPeer()) {
        const node_casted = commonMethod.getPeer().peer.ptr as (KPointer)
        const value_casted = Object.values(value)[0] as (int64)
        commonMethodOps.ForegroundFilterHandWrittenImpl(node_casted, value_casted)
    }
}

export function hookCommonMethodCompositingFilterImpl(commonMethod: ArkCommonMethodComponent, value: Filter | undefined) {
    if (value === undefined) {
        return;
    }
    if (commonMethod.getPeer()) {
        const node_casted = commonMethod.getPeer().peer.ptr as (KPointer)
        const value_casted = Object.values(value)[0] as (int64)
        commonMethodOps.CompositingFilterHandWrittenImpl(node_casted, value_casted)
    }
}

export function hookCommonMethodAdvancedBlendModeImpl(commonMethod: ArkCommonMethodComponent, effect: BlendMode | BrightnessBlender | undefined, type?: BlendApplyType) {
    if (effect === undefined) {
        return;
    }
    const node_casted = commonMethod.getPeer().peer.ptr as (KPointer)
    const type_casted = type as (BlendApplyType | undefined)
    if (runtimeType(effect) == RuntimeType.OBJECT) {
        if (!effect.hasOwnProperty('brightnessBlenderNativeObj')) {
            return;
        }
        const value_casted = Object.values(effect)[0] as (int64)
        commonMethodOps.AdvancedBlendModeObjectImpl(node_casted, value_casted, type_casted)
    } else {
        const value_casted = effect as (BlendMode | undefined)
        commonMethodOps.AdvancedBlendModeEnumImpl(node_casted, value_casted, type_casted)
    }
    return
}

export class CommonMethodHandWritten {
    static hookCommonMethodAnimateToImmediatelyImpl(value: AnimateParam, event: (() => void)): void {
        AnimationExtender.AnimateToImmediatelyImpl(value, event);
    }
}

export class ElementIdToCustomProperties {
    constructor() { }
    static instance_: ElementIdToCustomProperties = new ElementIdToCustomProperties();
    static _elementIdToCustomProperties = new Map<number, Map<string, CustomProperty>>();
}
export function hookCustomPropertyImpl(arkComponent: ArkCommonMethodComponent,
    name: string, value: CustomProperty): void {
    const nodeId = arkComponent.getPeer().getId();
    if (!ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
        ElementIdToCustomProperties._elementIdToCustomProperties.set(nodeId, new Map<string, CustomProperty>());
    }
    const customProperties = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
    if (customProperties) {
        customProperties.set(name, value);
    }
    const removeCallback: () => void = () => {
        ElementIdToCustomProperties._elementIdToCustomProperties.delete(nodeId);
    };
    const getCallback: (name: string) => string | undefined = (name: string) => {
        if (ElementIdToCustomProperties._elementIdToCustomProperties.has(nodeId)) {
            const customPropertiesGet = ElementIdToCustomProperties._elementIdToCustomProperties.get(nodeId);
            if (customPropertiesGet) {
                const propertyValue = customPropertiesGet.get(name);
                return propertyValue !== undefined ? JSON.stringify(propertyValue) : undefined;
            }
        }
        return undefined;
    };
    ArkUIAniModule._Common_SetCustomPropertyCallBack(arkComponent.getPeer().getPeerPtr(), removeCallback, getCallback);
}

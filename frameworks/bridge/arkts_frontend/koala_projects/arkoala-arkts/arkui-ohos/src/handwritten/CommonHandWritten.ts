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

import { ArkCommonMethodComponent, Gesture, GestureGroup, GestureMask, GestureModifier, GestureType, AnimateParam, AnimationExtender } from "../component"

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
        singleGesture.setGesture(2, commonMethod.getPeer(), mask);
    } else {
        let gestureGroup = gesture as GestureGroup;
        gestureGroup.addGestureGroupToNode(2, commonMethod.getPeer(), mask)
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


export class CommonMethodHandWritten {
    static hookCommonMethodAnimateToImmediatelyImpl(value: AnimateParam, event: (() => void)): void {
        AnimationExtender.AnimateToImmediatelyImpl(value, event);
    }
}

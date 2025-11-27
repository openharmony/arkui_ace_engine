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

import { AttributeModifier } from "arkui/component/common";
import { PeerNode } from "./PeerNode";

export type Initializer<T = void> = (...params: FixedArray<Object>) => T;

export class AttributeUpdater<T> implements AttributeModifier<T> {
    public isInit: boolean = true;
    initializeModifier(instance: T): void {
    }
    onComponentChanged(component: T): void {
    }
    private value: T | undefined = undefined;
    private constructorParams: Initializer<T> | undefined = undefined;
    public peerNode_?: PeerNode;

    public set attribute(value: T) {
        this.value = value
    }
    public get attribute(): T | undefined {
        return this.value
    }
    public set updateConstructorParams(constructorParams: Initializer<T>) {
        this.constructorParams = constructorParams;
    }
    public get updateConstructorParams(): Initializer<T> {
        return this.constructorParams!;
    }
    isUpdater: () => boolean = () => true
    applyNormalAttribute(instance: T): void {}
    applyPressedAttribute(instance: T): void {}
    applyFocusedAttribute(instance: T): void {}
    applyDisabledAttribute(instance: T): void {}
    applySelectedAttribute(instance: T): void {}
}
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

import { AttributeModifier } from "./";
import { InteropNativeModule } from "@koalaui/interop"
export type Initializer<T> = (...params:Object[]) => T;

export class AttributeUpdater<T, C = Initializer<T>> implements AttributeModifier<T> {

    /** @memo */
    applyNormalAttribute(instance: T): void {
    }
    /** @memo */
    applyPressedAttribute(instance: T): void {
    }
    /** @memo */
    applyFocusedAttribute(instance: T): void {
    }
    /** @memo */
    applyDisabledAttribute(instance: T): void {
    }
    /** @memo */
    applySelectedAttribute(instance: T): void {  
    }
    /** @memo */
    initializeModifier(instance: T): void {
    }
    private value: T | undefined = undefined;
    private constructorParams: C | undefined = undefined;
    
    public set attribute(value: T) {
        this.value = value
    }
    public get attribute(): T {
        return this.value!
    }
    public get updateConstructorParams(): C {
        return this.constructorParams!
    }
    public set updateConstructorParams(constructorParams: C) {
        this.constructorParams = constructorParams
    }
}
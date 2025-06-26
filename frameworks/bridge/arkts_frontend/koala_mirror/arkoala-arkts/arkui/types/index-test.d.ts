/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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

declare interface TestComponentOptions {
    id?: number;
    log?: string;
    onChange?: () => void;
}
declare interface TestComponentInterface {
    (options?: TestComponentOptions): TestComponentAttribute;
}
declare class TestComponentAttribute extends CommonMethod<TestComponentAttribute> {
    onChange(callback: () => void): TestComponentAttribute;
    log(message: string): TestComponentAttribute;
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | undefined): TestComponentAttribute;
}
declare interface UITestComponentAttribute extends CommonMethod<UITestComponentAttribute> {
    /** @memo */
    onChange(callback: () => void): UITestComponentAttribute
    /** @memo */
    log(message: string): UITestComponentAttribute
    /** @memo */
    attributeModifier(value: AttributeModifier<TestComponentAttribute> | undefined): UITestComponentAttribute
}
declare const TestComponent: TestComponentInterface
declare const TestComponentInstance: TestComponentAttribute

declare function nLog(...data: (object|int32|float32|boolean|string|undefined)[]): void
declare type Initializer<T> = () => T;
declare class AttributeUpdater<T, C = Initializer<T>> implements AttributeModifier<T> {
    applyPressedAttribute(instance: T): void;
    applyFocusedAttribute(instance: T): void;
    applyDisabledAttribute(instance: T): void;
    applySelectedAttribute(instance: T): void;
    applyNormalAttribute(instance: T): void;
    initializeModifier(instance: T): void;
    get attribute(): T | undefined;
    updateConstructorParams: C | undefined;
    onComponentChanged(component: T): void;
}

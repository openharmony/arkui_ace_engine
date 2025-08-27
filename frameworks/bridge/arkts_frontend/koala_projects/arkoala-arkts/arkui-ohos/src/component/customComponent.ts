/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { ArkStructBase } from "../ArkStructBase"
import { ArkCommonMethodComponent } from "./common"
import { UIContext } from "@ohos/arkui/UIContext"
import { ProvideDecoratedVariable, ConsumeDecoratedVariable, WatchFuncType } from "../stateManagement";

class CustomDelegate<T extends CustomComponent<T, T_Options>, T_Options> extends
    ArkStructBase<CustomDelegate<T, T_Options>, T_Options> {
    private instance: CustomComponent<T, T_Options>;

    constructor(instance: CustomComponent<T, T_Options>) {
        super();
        this.instance = instance;
    }

    aboutToAppear(): void {
        this.instance.aboutToAppear();
    }
    aboutToDisappear(): void {
        this.instance.aboutToDisappear();
    }

    onDidBuild(): void {
        this.instance.onDidBuild();
    }
    onPageShow(): void {
        this.instance.onPageShow();
    }

    onPageHide(): void {
        this.instance.onPageHide();
    }

    onBackPress(): boolean {
        return this.instance.onBackPress();
    }

    aboutToRecycle(): void {
        return this.instance.aboutToRecycle()
    }

    aboutToReuse(params: Record<string, Object>): void {
        this.instance.aboutToReuse(params)
    }
    __toRecord(param: Object): Record<string, Object> {
        return this.instance.__toRecord(param)
    }

    /** @memo */
    __build(
        /** @memo */
        attributes: undefined | ((instance: ArkCommonMethodComponent) => void),
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        const current = CustomComponent.current;
        CustomComponent.current = this.instance as Object;
        this.instance._build(undefined, content, initializers);
        CustomComponent.current = current;
    }

    protected __initializeStruct(
        /** @memo */
        content?: () => void,
        initializers?: T_Options
    ): void {
        this.instance.__initializeStruct(initializers, content);
    }

    /** @memo */
    protected __updateStruct(
        initializers?: T_Options
    ): void {
        this.instance.__updateStruct(initializers);
    }
}

export abstract class CustomComponent<T extends CustomComponent<T, T_Options>, T_Options> {
    private parent_: CustomComponent<T, T_Options> | undefined;
    public static current: Object | undefined = undefined;
    private providedVars_: Map<string, ProvideDecoratedVariable<Object>> = new Map<string, ProvideDecoratedVariable<Object>>();
    constructor() {
        this.parent_ = CustomComponent.current as (CustomComponent<T, T_Options> | undefined);
    }
    public addProvidedVar<T>(varName: string, providedPropName: string, initValue: T, allowOverride: boolean = false, watchFunc?: WatchFuncType) {
        if (!allowOverride && this.findProvide<T>(providedPropName)) {
            throw new ReferenceError(`Duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Component already.`);
        }
        const provide = new ProvideDecoratedVariable<T>(varName, providedPropName, initValue, watchFunc);
        this.providedVars_.set(providedPropName, provide as Object as ProvideDecoratedVariable<Object>);
        if (varName !== providedPropName) {
            this.providedVars_.set(varName, provide as Object as ProvideDecoratedVariable<Object>);
        }
        return provide;
    }
    public findProvide<T>(providedPropName: string): ProvideDecoratedVariable<T> | undefined {
        const localVar = this.providedVars_.get(providedPropName);
        if (localVar !== undefined) {
            return localVar as Object as ProvideDecoratedVariable<T>;
        }
        if (this.parent_ !== undefined) {
            return this.parent_!.findProvide<T>(providedPropName);
        }
        return undefined;
    }
    public initConsume<T>(varName: string, providedPropName: string, watchFunc: WatchFuncType): ConsumeDecoratedVariable<T> {
        const provide = this.findProvide<T>(providedPropName);
        if (provide === undefined) {
            throw new Error(`No @Provide found for var ${providedPropName}`);
        }
        return new ConsumeDecoratedVariable<T>(varName, providedPropName, provide as Object as ProvideDecoratedVariable<T>, watchFunc);
    }
    /** @memo */
    static _instantiateImpl<S extends CustomComponent<S, S_Options>, S_Options>(
        /** @memo */
        style: ((instance: S) => void) | undefined,
        factory: () => S,
        initializers?: S_Options,
        /** @memo */
        content?: () => void,
        reuseKey?: string
    ): void {
        CustomDelegate._instantiate(undefined, () => new CustomDelegate<S, S_Options>(factory()), content, initializers, reuseKey);
    }

    __initializeStruct(
        initializers?: T_Options,
        /** @memo */
        content?: () => void
    ): void {}

    __updateStruct(
        initializers?: T_Options
    ): void {}

    // Life cycle for custom component
    aboutToAppear(): void {}
    aboutToDisappear(): void {}
    onDidBuild(): void {}

    onPageShow(): void {}
    onPageHide(): void {}
    onBackPress(): boolean { return false; }
    getUIContext(): UIContext { return new UIContext(100000); }

    aboutToReuse(param: Record<string, Object>): void {}
    aboutToRecycle(): void {}
    __toRecord(param: Object): Record<string, Object> { return {} }

    build(): void {};

    /** @memo */
    _build(
        /** @memo */
        style: ((instance: T) => T) | undefined,
        /** @memo */
        content: (()=> void) | undefined,
        initializers: T_Options | undefined
    ): void {}
}
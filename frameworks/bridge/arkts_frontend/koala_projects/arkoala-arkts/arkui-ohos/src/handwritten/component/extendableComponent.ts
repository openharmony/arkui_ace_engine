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
import { IProvideDecoratedVariable } from "../stateManagement/decorator";

export class ExtendableComponent {
    private parent_: ExtendableComponent | undefined;
    public static current: Object | undefined = undefined;
    private providedVars_: Map<string, IProvideDecoratedVariable<Object>> = new Map<string, IProvideDecoratedVariable<Object>>();
    constructor() {
        this.parent_ = ExtendableComponent.current as (ExtendableComponent | undefined);
    }
    addProvidedVar<T>(providedPropName: string, store: IProvideDecoratedVariable<T>, allowOverride?: boolean | undefined): void {
        if (!allowOverride && this.findProvide<T>(providedPropName)) {
            throw new ReferenceError(`Duplicate @Provide property with name ${providedPropName}. Property with this name is provided by one of the ancestor Component already.`);
        }
        this.providedVars_.set(providedPropName, store as Object as IProvideDecoratedVariable<Object>);
    }
    findProvide<T>(providedPropName: string): IProvideDecoratedVariable<T> | null {
        const localVar = this.providedVars_.get(providedPropName);
        if (localVar !== undefined) {
            return localVar as Object as IProvideDecoratedVariable<T>;
        }
        if (this.parent_ !== undefined) {
            return this.parent_!.findProvide<T>(providedPropName);
        }
        return null;
    }
}
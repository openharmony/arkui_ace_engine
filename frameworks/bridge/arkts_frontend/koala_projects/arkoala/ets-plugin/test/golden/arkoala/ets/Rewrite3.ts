import { ArkCommonMethodComponent, ArkPageTransitionEnterComponent, ArkPageTransitionExitComponent, ArkStructBase, StorageLinkState, SyncedProperty, observableProxy, propState } from "@koalaui/arkoala-arkui";
import { registerArkuiEntry } from "@koalaui/arkoala-arkui/ohos.router";
/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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
import { storage } from "./Rewrite2";
/** @memo:stable */
class ArkLocalStoragePropExampleComponent extends ArkStructBase<ArkLocalStoragePropExampleComponent, LocalStoragePropExampleOptions> {
    private _entry_local_storage_ = storage;
    __initializeStruct(/**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropExampleOptions): void {
        this.__backing_prop = propState<string>(StorageLinkState<string>(this._entry_local_storage_, "storage", "Start").value);
    }
    private __backing_prop?: SyncedProperty<string>;
    private get prop(): string {
        return this.__backing_prop!.value;
    }
    private set prop(value: string) {
        this.__backing_prop!.value = observableProxy(value);
    }
    /** @memo */
    __updateStruct(initializers: LocalStoragePropExampleOptions | undefined): void {
        this.__backing_prop?.update(StorageLinkState<string>(this._entry_local_storage_, "storage", "Start").value);
    }
    /** @memo */
    __build(/**/
    /** @memo */
    __builder: ((__instance: ArkCommonMethodComponent) => void) | undefined, /**/
    /** @memo */
    content?: () => void, initializers?: LocalStoragePropExampleOptions) {
    }
}
/** @memo */
export function LocalStoragePropExample(/**/
/** @memo */
style?: (__instance: ArkCommonMethodComponent) => void, /**/
/** @memo */
content?: () => void, initializers?: LocalStoragePropExampleOptions): void {
    const updatedInitializers: LocalStoragePropExampleOptions = {
        __backing_prop: initializers?.__backing_prop
    };
    ArkLocalStoragePropExampleComponent._instantiate(style, () => new ArkLocalStoragePropExampleComponent, content, updatedInitializers);
}
export interface LocalStoragePropExampleOptions {
    __backing_prop?: SyncedProperty<string>;
    prop?: string;
}
registerArkuiEntry(LocalStoragePropExample, "Rewrite3");
export const __Entry = LocalStoragePropExample;

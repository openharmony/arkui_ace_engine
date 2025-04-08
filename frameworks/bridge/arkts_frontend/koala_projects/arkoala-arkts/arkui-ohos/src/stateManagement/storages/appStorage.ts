/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
import { LinkDecoratedVariable } from "../decorators/decoratorLink";
import { PropDecoratedVariable } from "../decorators/decoratorProp";
import { StateDecoratedVariable } from "../decorators/decoratorState";
import { LocalStorage } from "./localStorage";

export class AppStorage extends LocalStorage {
    public static createSingleton(/*initializingPropersties?: Object */): void {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage( /* initializingPropersties */);
        } else {
        }
    }
    public static link(key: string): LinkDecoratedVariable<Object> | undefined  {
        return AppStorage.getOrCreate().link(key);
    }

    public static setAndLink(key: string, defaultValue: Object) : LinkDecoratedVariable<Object>  {
        return AppStorage.getOrCreate().setAndLink(key, defaultValue);
    }

    public static prop(propName: string) : PropDecoratedVariable<Object> | undefined {
        return AppStorage.getOrCreate().prop(propName);
    }

    public static setAndProp(key: string, defaultValue: Object) : PropDecoratedVariable<Object> {
        return AppStorage.getOrCreate().setAndProp(key, defaultValue);
    }

    public static has(key: string): boolean {
        return AppStorage.getOrCreate().has(key);
    }

    public static get<T>(key: string): T | undefined {
        return AppStorage.getOrCreate().get<T>(key);
    }

    public static set<T>(key: string, newValue: T): boolean {
        return AppStorage.getOrCreate().set<T>(key, newValue);
    }

    public static setOrCreate<T>(key: string, newValue: T): void {
        AppStorage.getOrCreate().setOrCreate<T>(key, newValue);
    }

    public static delete(key: string): boolean {
        return AppStorage.getOrCreate().delete(key);
    }

    public static keys(): IterableIterator<string> {
        return AppStorage.getOrCreate().keys();
    }

    public static size(): number {
        return AppStorage.getOrCreate().size();
    }

    public static clear(): boolean {
        return AppStorage.getOrCreate().clear();
    }

    private static instance_: AppStorage | undefined = undefined;

    private static getOrCreate(): AppStorage {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage();
        }
        return AppStorage.instance_!;
    }

    protected constructor(/* initializingProperties: Object */) {
        super( /* initializingProperties */);
    }
}

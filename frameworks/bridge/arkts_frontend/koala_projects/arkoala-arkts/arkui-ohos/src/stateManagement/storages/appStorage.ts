/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { LocalStorage } from './localStorage';

import { NullableObject } from '../base/types';
import { AbstractProperty, SubscribedAbstractProperty } from '../base/decoratorBase';

import { LinkDecoratedVariable } from '../decorators/decoratorLink';
import { PropDecoratedVariable } from '../decorators/decoratorProp';

export class AppStorage extends LocalStorage {
    public static createSingleton(/*initializingPropersties?: Object */): void {
        if (!AppStorage.instance_) {
            AppStorage.instance_ = new AppStorage( /* initializingPropersties */);
        } else {
        }
    }

    public static ref<T>(propName: string): AbstractProperty<T> | undefined  {
        return AppStorage.getOrCreate().ref<T>(propName);
    }

    public static setAndRef<T>(propName: string, defaultValue: T) : AbstractProperty<T>  {
        return AppStorage.getOrCreate().setAndRef<T>(propName, defaultValue);
    }

    public static link<T>(propName: string): SubscribedAbstractProperty<T> | undefined  {
        return AppStorage.getOrCreate().link<T>(propName);
    }

    public static setAndLink<T>(propName: string, defaultValue: T) : SubscribedAbstractProperty<T>  {
        return AppStorage.getOrCreate().setAndLink<T>(propName, defaultValue);
    }

    public static createLink<T>(propName: string, defaultValue: T) : LinkDecoratedVariable<NullableObject> {
        return AppStorage.getOrCreate().createLink<T>(propName, defaultValue);
    }

    public static prop<T>(propName: string) : SubscribedAbstractProperty<T> | undefined {
        return AppStorage.getOrCreate().prop<T>(propName);
    }

    public static setAndProp<T>(propName: string, defaultValue: T) : SubscribedAbstractProperty<T> {
        return AppStorage.getOrCreate().setAndProp<T>(propName, defaultValue);
    }

    public static createProp<T>(propName: string, defaultValue: T) : PropDecoratedVariable<NullableObject> {
        return AppStorage.getOrCreate().createProp<T>(propName, defaultValue);
    }

    public static has(propName: string): boolean {
        return AppStorage.getOrCreate().has(propName);
    }

    public static get<T>(propName: string): T | undefined {
        return AppStorage.getOrCreate().get<T>(propName);
    }

    public static set<T>(propName: string, newValue: T): boolean {
        return AppStorage.getOrCreate().set<T>(propName, newValue);
    }

    public static setOrCreate<T>(propName: string, newValue: T): void {
        AppStorage.getOrCreate().setOrCreate<T>(propName, newValue);
    }

    public static delete(propName: string): boolean {
        return AppStorage.getOrCreate().delete(propName);
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

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

import { uiUtils } from './base/uiUtilsImpl';
import { IMonitor, IMonitorDecoratedVariable, IMonitorPathInfo } from './decorator';
import { MonitorFunctionDecorator } from './decoratorImpl/decoratorMonitor';
import { ExtendableComponent } from '../component/extendableComponent';
import { BusinessError } from '@ohos.base';
import { CustomComponentV2 } from '../component/customComponent'

export class UIUtils {
    static makeObserved<T>(source: T): T {
        return uiUtils.makeObserved(source) as T;
    }
    static getTarget<T>(source: T): T {
        return uiUtils.getTarget(source) as T;
    }
    static makeBinding<T>(getter: () => T): Binding<T> {
        return uiUtils.makeBindingReadonly(getter);
    }
    static makeBinding<T>(getter: () => T, setter: (newValue: T) => void): MutableBinding<T> {
        return uiUtils.makeBindingMutable(getter, setter);
    }

    private static readonly DEFAULT_PATH: string = 'MONITOR_';
    private static readonly DEFAULT_INDEX = 0;
    private static currentIndex_ = UIUtils.DEFAULT_INDEX;

    static addMonitor(valueCallback: (() => Any) | Array<() => Any>, monitorCallback: (m: IMonitor) => void, options?: MonitorOptions): IMonitorDecoratedVariable {
        if (options?.owner && !(options?.owner instanceof CustomComponentV2)) {
            const errorCode: Int = 130000;
            const errorMessage: string = 'options.owner is not a component decorated with @ComponentV2 which is not supported by UIUtils.addMonitor.';
            throw new BusinessError(errorCode, new Error(errorMessage));
        }

        const callbackArray = UIUtils.unionToArray(valueCallback);
        const pathArray = UIUtils.pathToArray(options?.path);
        const pathLambda = UIUtils.generatePathLambda(callbackArray, pathArray);

        return new MonitorFunctionDecorator(pathLambda, monitorCallback, options?.owner, options?.isSynchronous);
    }

    static clearMonitor(monitor: IMonitorDecoratedVariable): void {
        (monitor as MonitorFunctionDecorator).unbindAllInternalValues();
    }

    private static pathToArray(path?: string | string[]): string[] {
        if (!path) {
            return [];
        }

        return UIUtils.unionToArray(path);
    }

    private static unionToArray<T>(input: T | T[]): T[] {
        if (Array.isArray(input)) {
            return input as T[];
        } else {
            return [input as T];
        }
    }

    private static createPathInfo(callback: () => Any, path?: string): IMonitorPathInfo {
        return {
            path: path ?? '',
            valueCallback: callback
        };
    }

    private static generatePathLambda(callbacks: (() => Any)[], paths?: string[]): IMonitorPathInfo[] {
        return callbacks.map((callback: () => Any, index: int): IMonitorPathInfo => {
            const currentPath: string = !paths || index >= paths.length
                ? `${UIUtils.DEFAULT_PATH}${UIUtils.currentIndex_++}`
                : paths[index];

            return UIUtils.createPathInfo(callback, currentPath);
        });
    }
}

interface MonitorOptions {
    isSynchronous?: boolean;
    owner?: ExtendableComponent;
    path?: string | string[];
}

/**
 * Generic Binding class to encapsulate read-only data binding.
 *
 * @template T - The type of the value to be bound.
*/
export class Binding<T> {
    private getter_: () => T;

    /**
     * Constructs a new Binding instance.
     *
     * @param getter - A function that returns the current value of type T.
     */
    constructor(getter: () => T) {
        this.getter_ = getter;
    }

    /**
     * Gets the current value of the binding.
     *
     * @returns The current value of type T.
     */
    public get value(): T {
        return this.getter_();
    }
}

/**
 * Generic MutableBinding class to encapsulate both read and write operations.
 *
 * @template T - The type of the value to be bound.
 */
export class MutableBinding<T> {
    private getter_: () => T;
    private setter_: (newValue: T) => void;

    /**
     * Constructs a new MutableBinding instance.
     *
     * @param getter - A function that returns the current value of type T.
     * @param setter - A function that sets a new value of type T.
     */
    constructor(getter: () => T, setter: (newValue: T) => void) {
        this.getter_ = getter;
        this.setter_ = setter;
    }

    /**
     * Sets a new value for the binding.
     *
     * @param newValue - The new value to be set of type T.
     */
    set value(newValue: T) {
        this.setter_(newValue);
    }

    /**
     * Gets the current value of the binding.
     *
     * @returns The current value of type T.
     */
    get value(): T {
        return this.getter_();
    }
}

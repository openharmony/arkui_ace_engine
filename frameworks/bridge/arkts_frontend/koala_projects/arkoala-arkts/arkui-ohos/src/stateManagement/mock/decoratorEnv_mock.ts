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

export interface IEnvVariable {
    onWatchFunc(): void;
    offWatchFunc(instanceId?: int): void;
}

export class EnvDecoratedVariable<T> implements IEnvVariable {
    constructor(
        owningView: Object | undefined,
        envValue: string,
        varName: string,
        envOptions?: Object
    ) {}

    get(): T {
        throw new Error('EnvDecoratedVariable mock: get() not implemented');
    }

    resetOnReuse(newValue: T): void {}

    onWatchFunc(): void {}
    offWatchFunc(instanceId?: int): void {}
}

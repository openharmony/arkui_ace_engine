/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

declare class SystemEnvKey {
    keyId: string;
    constructor(keyId: string);
}

class WritableSystemEnvKey<T> extends SystemEnvKey {}

class ReadonlySystemEnvKey<T> extends SystemEnvKey {}

declare class WritableEnvKey {
    static readonly DIRECTION: WritableSystemEnvKey<Direction>;
    static readonly FONT_SCALE: WritableSystemEnvKey<number>;
}

class WithEnvAttribute {
    env<T>(key: WritableSystemEnvKey<T>, value: T): WithEnvAttribute {

        globalThis.WithEnv.setEnvProperty(key, value);
        return this;
    }

    customEnv(key: string, value: any): WithEnvAttribute {
        globalThis.WithEnv.setCustomEnvProperty(key, value);
        return this;
    }
}

if (globalThis.WithEnv !== undefined) {
    const nativeCreate = globalThis.WithEnv.create;
    globalThis.WithEnv.create = function(): WithEnvAttribute {
        nativeCreate();
        return new WithEnvAttribute();
    };
}


export default { WithEnv, WithEnvAttribute, SystemEnvKey, WritableSystemEnvKey, ReadonlySystemEnvKey, WritableEnvKey };


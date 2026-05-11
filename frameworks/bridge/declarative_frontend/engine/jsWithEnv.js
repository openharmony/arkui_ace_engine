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
const WritableSystemProperties = {
    Layout_Direction: 'system.arkui.layout.direction', 
    ENV_KEY_FONT_SCALE: 'system.arkui.fontscale'
};

const WritableEnvProperties = {
[WritableSystemProperties.Layout_Direction]: false,
[WritableSystemProperties.ENV_KEY_FONT_SCALE]: 1.0,
};

class WithEnvAttribute {
    env(key, value) {
        globalThis.WithEnv.setEnvProperty(key, value);
        return this;
    }

    customEnv(key, value) {
        globalThis.WithEnv.setCustomEnvProperty(key, value);
        return this;
    }

    fontScaleEnv(value) {
        globalThis.WithEnv.setEnvProperty(WritableSystemProperties.ENV_KEY_FONT_SCALE, value);
        return this;
    }
}

if (globalThis.WithEnv !== undefined) {
    const nativeCreate = globalThis.WithEnv.create;
    globalThis.WithEnv.create = function() {
        nativeCreate();
        return new WithEnvAttribute();
    };
}

export default { WithEnv, WithEnvAttribute, WritableSystemProperties, WritableEnvProperties}; 

/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
// HANDWRITTEN, DO NOT REGENERATE

export function makeBuilderParameterProxy<T extends Object>(instance: T, source: Map<string, () => Any>, initializer?: (t: T) => void): T {
    const proxiedInstance = proxy.Proxy.create(instance, new BuilderLiteralProxyHandler<T>(source));
    if (initializer) {
        initializer!(proxiedInstance);
    }
    return proxiedInstance;
}

class BuilderLiteralProxyHandler<T extends Object> extends proxy.DefaultProxyHandler<T> {
    source: Map<string, () => Any>;
    constructor(source: Map<string, () => Any>) {
        this.source = source;
    }
    override get(target: T, name: string): Any {
        const propertyGetter = this.source.get(name);
        if (propertyGetter) {
            return propertyGetter!();
        }
        return super.get(target, name);
    }
}
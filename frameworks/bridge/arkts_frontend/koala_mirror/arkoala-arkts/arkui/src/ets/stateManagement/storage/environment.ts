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
import { AppStorage } from './appStorage';
import { ArkUIAniModule } from 'arkui.ani';

interface IAniEnvironment {
    getAccessibilityEnabled(): boolean;
    getColorMode(): number;
    getFontScale(): number;
    getFontWeightScale(): number;
    getLayoutDirection(): string;
    getLanguageCode(): string;
}

class AniEnvironment implements IAniEnvironment {
    getAccessibilityEnabled(): boolean {
        return ArkUIAniModule._Env_GetAccessibilityEnabled();
    }
    getColorMode(): number {
        return ArkUIAniModule._Env_GetColorMode();
    }
    getFontScale(): number {
        return ArkUIAniModule._Env_GetFontScale();
    }
    getFontWeightScale(): number {
        return ArkUIAniModule._Env_GetFontWeightScale();
    }
    getLayoutDirection(): string {
        return ArkUIAniModule._Env_GetLayoutDirection();
    }
    getLanguageCode(): string {
        return ArkUIAniModule._Env_GetLanguageCode();
    }
}

interface EnvPropsOptions {
    key: string;
    defaultValue: number | string | boolean;
}

/**
 * Environment
 *
 * Injects device properties ("environment") into AppStorage
 *
 */
class Environment {
    private static instance_: Environment | undefined = undefined;
    private props_: Map<string, NullishType> = new Map<string, NullishType>();
    private readonly aniEnvironment: AniEnvironment = new AniEnvironment();
    private ttypeMap_: Map<string, Type> = new Map<string, Type>([
        ['accessibilityEnabled', Type.from<string>()],
        ['layoutDirection', Type.from<string>()],
        ['languageCode', Type.from<string>()],
        ['colorMode', Type.from<number>()],
        ['fontScale', Type.from<number>()],
        ['fontWeightScale', Type.from<number>()],
    ]);

    public aboutToBeDeleted(): void {
        Environment.getOrCreate().props_.forEach((_, key) => {
            AppStorage.delete(key);
        });
        Environment.getOrCreate().props_.clear();
    }

    private static getOrCreate(): Environment {
        if (Environment.instance_) {
            // already initialized
            return Environment.instance_!;
        }

        Environment.instance_ = new Environment();
        return Environment.instance_!;
    }

    public static envProp<T>(key: string, value: T): boolean {
        if (!Environment.getOrCreate().ttypeMap_.has(key)) {
            return false; // Invalid key
        }
        const ttype = Environment.getOrCreate().ttypeMap_.get(key)!;
        return Environment.getOrCreate().envPropInternal<T>(key, value, ttype);
    }

    private envPropInternal<T>(key: string, value: T, ttype: Type): boolean {
        if (AppStorage.has(key, ttype)) {
            return false;
        }

        let tmp: NullishType = undefined;
        switch (key) {
            case 'accessibilityEnabled':
                tmp = Environment.getOrCreate().aniEnvironment.getAccessibilityEnabled();
                break;
            case 'colorMode':
                tmp = Environment.getOrCreate().aniEnvironment.getColorMode();
                break;
            case 'fontScale':
                tmp = Environment.getOrCreate().aniEnvironment.getFontScale();
                break;
            case 'fontWeightScale':
                tmp = Math.round(Environment.getOrCreate().aniEnvironment.getFontWeightScale() * 100) / 100;
                break;
            case 'layoutDirection':
                tmp = Environment.getOrCreate().aniEnvironment.getLayoutDirection();
                break;
            case 'languageCode':
                tmp = Environment.getOrCreate().aniEnvironment.getLanguageCode();
                break;
            default:
                tmp = value as NullishType;
        }

        if (tmp === undefined || tmp === -1 || tmp === '') {
            tmp = value as NullishType;
        }

        const prop = AppStorage.setAndRef(key, tmp as T, ttype);
        if (!prop) {
            return false;
        }

        Environment.getOrCreate().props_.set(key, tmp);
        return true;
    }

    public static envProps(properties: EnvPropsOptions[]): void {
        properties.forEach((prop) => {
            const key: string = prop.key;
            const defaultValue: number | string | boolean = prop.defaultValue;
            const ttype = Environment.getOrCreate().ttypeMap_.get(key)!;
            Environment.envProp(key, defaultValue);
        });
    }

    public static keys(): Array<string> {
        return Environment.getOrCreate().keysInternal();
    }

    public keysInternal(): Array<string> {
        return Array.from(Environment.getOrCreate().props_.keys());
    }
}

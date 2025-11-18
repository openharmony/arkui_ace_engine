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
    defaultValue: int | long | double | string | boolean;
}

/**
 * Environment
 *
 * Injects device properties ("environment") into AppStorage
 *
 */
class Environment {
    private static instance_: Environment | undefined = undefined;
    private props_: Map<string, Any> = new Map<string, Any>();
    private readonly aniEnvironment: AniEnvironment = new AniEnvironment();
    private keySet: Set<string> = new Set<string>([
        'accessibilityEnabled',
        'layoutDirection',
        'languageCode',
        'colorMode',
        'fontScale',
        'fontWeightScale',
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
        return Environment.getOrCreate().envPropInternal<T>(key, value);
    }

    private envPropInternal<T>(key: string, value: T): boolean {
        if (AppStorage.has(key)) {
            return false;
        }

        let tmp: Any = undefined;
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
                tmp = value as Any;
        }

        if (tmp === undefined || tmp === -1 || tmp === '') {
            tmp = value as Any;
        }

        const prop = AppStorage.setAndRef(key, tmp as T);
        if (!prop) {
            return false;
        }

        Environment.getOrCreate().props_.set(key, tmp);
        return true;
    }

    public static envProps(properties: EnvPropsOptions[]): void {
        properties.forEach((prop) => {
            const key: string = prop.key;
            const defaultValue: int | long | double | string | boolean = prop.defaultValue;
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

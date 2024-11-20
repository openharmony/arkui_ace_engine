/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

/**
 * Singleton class used to keep existing theme instances which are used by theme scopes right now
 */
class ArkThemeCache {
    // single instance
    private static instance: ArkThemeCache;

    // array of theme instances
    private cache: ArkThemeBase[] = [];

    private constructor() {}

    static getInstance() {
        if (!ArkThemeCache.instance) {
            ArkThemeCache.instance = new ArkThemeCache();
        }
        return ArkThemeCache.instance;
    }

    /**
     * Adds theme instance to the cache
     *
     * @param theme instance of theme
     */
    add(theme: ArkThemeBase) {
        if (this.contains(theme)) {
            // do nothing if theme already contains in cache
            return;
        }
        this.cache.push(theme);
    }

    /**
     * Removes theme instance from the cache
     *
     * @param theme instance of theme
     */
    remove(theme: ArkThemeBase) {
        const index = this.cache.indexOf(theme);
        if (index === -1) {
            // do nothing if cache doesn`t contain this theme instance
            return;
        }
        // remove theme from TS side cache
        this.cache.splice(index, 1);
        // remove theme from native side cache
        getUINativeModule().theme.removeFromCache(theme.id);
    }

    /**
     * Returns existing theme istance by CustomTheme and color mode
     *
     * @param baselineThemeId baseline theme id
     * @param customTheme instance of CustomTheme used for theme
     * @param colorMode local colorm mode used for theme
     * @returns instance of theme if exists or undefined
     */
    get(baselineThemeId: number, customTheme: CustomTheme, colorMode: ThemeColorMode): ArkThemeBase {
        // check all cache items one by one
        // return undefined if cache doesn`t contains theme instance with the same color mode and custom theme attributes
        return this.cache.find((item) => {
            return item.getParentThemeId() === baselineThemeId &&
            item.getColorMode() === colorMode &&
            this.isEqualsCustomThemes(item.getCustomTheme(), customTheme);
        });
    }

    /**
     * Checks whether cache contains theme instance or not
     *
     * @param theme instance of theme
     * @returns true if theme instance contains in cache; false otherwise
     */
    contains(theme: ArkThemeBase): boolean {
        return this.containsByAttributes(theme.getParentThemeId(), theme.getCustomTheme(), theme.getColorMode());
    }

    /**
     * Checks whether cache contains theme instance with the same color mode and custom theme attributes or not
     *
     * @param baselineThemeId baseline theme id
     * @param customTheme instance of CustomTheme used for theme
     * @param colorMode local colorm mode used for theme
     * @returns true if theme instance contains in cache; false otherwise
     */
    containsByAttributes(baselineThemeId: number, customTheme: CustomTheme, colorMode: ThemeColorMode): boolean {
        return this.get(baselineThemeId, customTheme, colorMode) !== undefined;
    }

    /**
     * Checks equality of two custom themes
     *
     * @param theme1 first custom theme instance
     * @param theme2 second custom theme instance
     * @returns true if cutom themes are equals; false otherwise
     */
    private isEqualsCustomThemes(theme1: CustomTheme, theme2: CustomTheme): boolean {
        if (theme1 === theme2) {
            // return true if references are the same
            return true;
        }
        if (!theme1 || !theme2) {
            // return false if one of instances is undefined
            return false;
        }
        if (theme1.colors === theme2.colors) {
            // return true if colors tokens references are the same
            return true;
        }
        if (!theme1.colors || !theme2.colors) {
            // return false if one of colors instances is undefined
            return false;
        }

        // take array of keys of color tokens used by both custom themes
        let keys1 = Object.keys(theme1.colors);
        let keys2 = Object.keys(theme2.colors);

        if (keys1.length !== keys2.length) {
            // return false if the length of the keys arrays are different
            return false;
        }

        // go by color tokens attributes keys one by one
        for (let key of keys1) {
            if (!keys2.includes(key)) {
                // return false if key of first custom theme colors dosn`t used by second custom theme colors
                return false;
            }

            // take values of colors tokens by current attribute key
            let value1 = theme1.colors[key];
            let value2 = theme2.colors[key];

            if (value1 !== value2) {
                // return false if color tokens values are different
                return false;
            }
        }

        // return true because we achieved the end of the method that means that two instance of Custom Theme are the same
        return true;
    }
}
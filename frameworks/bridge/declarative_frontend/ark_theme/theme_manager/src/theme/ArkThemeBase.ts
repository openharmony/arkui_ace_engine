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
 * Theme counter used to generate next theme id
 */
let themeCounter = 0;

/**
 * Base ArkTheme class
 */
class ArkThemeBase implements ThemeInternal {
    // Theme tokens
    colors: Colors;
    darkColors: Colors;
    shapes: Shapes;
    typography: Typography;

    /**
     * Unique theme instance id
     */
    id: number;

    /**
     * Copy of CustomTheme used to create this theme instance
     */
    private customTheme: CustomThemeInternal;

    /**
     * Color Mode used to create this theme instance
     */
    private colorMode: ThemeColorMode;

    /**
     * Binded theme scopes counter
     */
    private scopesCounter: number = 0;

    /**
     * Array of ids of binded theme scopes
     */
    private bindedThemeScopesIds: number[] = [];

    /**
     * Flag used to identify whether theme was just created or not
     */
    private isJustCreated = true;

    /**
     * Id of theme instance which was used as baseline theme for this theme instance
     */
    private parentThemeId: number = -1;

    /**
     * ArkThemeBase class constructor
     *
     * @param parentId id of theme instance which is used as baseline theme
     * @param customTheme instance of CustomTheme used to create current theme
     * @param colorMode local colorm mode used for current theme
     * @param colors colors tokens
     * @param shapes shapes tokens
     * @param typography typography tokens
     */
    constructor(
        parentId: number,
        customTheme: CustomThemeInternal,
        colorMode: ThemeColorMode,
        colors: Colors,
        darkColors: Colors,
        shapes: Shapes,
        typography: Typography
    ) {
        this.id = themeCounter++;
        this.parentThemeId = parentId;

        this.customTheme = ArkThemeBase.copyCustomTheme(customTheme);
        this.colorMode = colorMode;

        this.colors = colors;
        this.darkColors = darkColors;
        this.shapes = shapes;
        this.typography = typography;
    }

    /**
     * Binds current theme instance to theme scope
     *
     * @param themeScopeId binded theme scope id
     */
    bindToScope(themeScopeId: number) {
        if (this.bindedThemeScopesIds.includes(themeScopeId)) {
            // do nothing if theme scope already binded
            return;
        }
        // increment theme scopes counter
        this.scopesCounter++;
        // keep theme scope id
        this.bindedThemeScopesIds.push(themeScopeId);
        if (this.isJustCreated) {
            // if theme instance is just created keep it to the cache
            ArkThemeCache.getInstance().add(this);
            // mark theme instance as not just created
            this.isJustCreated = false;
        }
    }

    /**
     * Unbinds current theme instance from theme scope
     *
     * @param themeScopeId binded theme scope id
     */
    unbindFromScope(themeScopeId: number) {
        const index = this.bindedThemeScopesIds.indexOf(themeScopeId);
        if (index === -1) {
            // do nothing if theme scope is not exist in binded scopes list
            return;
        }
        // decrement theme scopes counter
        this.scopesCounter--;
        // remove theme scope id from the lisy of binded theme scopes
        this.bindedThemeScopesIds.splice(index, 1);
        if (this.canBeDestroyed()) {
            // remove theme from cache if none theme scope binded to the current theme instance
            ArkThemeCache.getInstance().remove(this);
        }
    }

    /**
     * Checks whether we can destroy existing theme instance or not
     *
     * @returns true if theme instance can be destroyed; false otherwise
     */
    canBeDestroyed(): boolean {
        // checks whether theme is no just created and binded theme scopes counter is 0
        return !this.isJustCreated && this.scopesCounter === 0;
    }

    /**
     * Return id of theme instance which was used as baseline theme for current theme instance
     *
     * @returns parent theme id
     */
    getParentThemeId(): number {
        return this.parentThemeId;
    }

    /**
     * Returns copy of CustomTheme used to create current theme instance
     *
     * @returns CustomTheme instance
     */
    getCustomTheme(): CustomTheme {
        return this.customTheme;
    }

    /**
     * Returns color mode used by this theme instance
     *
     * @returns local color mode value
     */
    getColorMode(): ThemeColorMode {
        return this.colorMode;
    }

    /**
     * Makes a local copy of CustomTheme instance
     *
     * @param customTheme instance of CustomTheme used to create current theme
     * @returns copy of custom theme instance
     */
    static copyCustomTheme(customTheme: CustomThemeInternal): CustomThemeInternal {
        if (!customTheme) {
            // return undefined if original custom theme is undefined
            return undefined;
        }
        const copyTheme: CustomThemeInternal = {};
        if (customTheme.colors) {
            copyTheme.colors = {};
            Object.assign(copyTheme.colors, customTheme.colors);
        }
        if (customTheme.darkColors) {
            copyTheme.darkColors = {};
            // For properties missing in darkColors, use the values from colors
            Object.assign(copyTheme.darkColors, customTheme?.colors, customTheme.darkColors);
        } else if (customTheme.colors) {
            // If the user does not provide darkColors, use the values from colors
            copyTheme.darkColors = {};
            Object.assign(copyTheme.darkColors, customTheme.colors);
        }
        if (customTheme.shapes) {
            copyTheme.shapes = {};
            Object.assign(copyTheme.shapes, customTheme.shapes);
        }
        if (customTheme.typography) {
            copyTheme.typography = {};
            Object.assign(copyTheme.typography, customTheme.typography);
        }
        return copyTheme;
    }
}
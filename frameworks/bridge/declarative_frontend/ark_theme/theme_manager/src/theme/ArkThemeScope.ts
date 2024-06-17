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

class ArkThemeScopeItem {
    elmtId: number;
    owner: number;
    name: string;
    isInWhiteList?: boolean = undefined;
}

class ArkThemeScopeArray extends Array<ArkThemeScopeItem> {
    binarySearch(elmtId: number): number {
        let start = 0;
        let end = this.length - 1;
        while (start <= end) {
            let mid = (start + end) >> 1;
            if (this[mid].elmtId === elmtId) {
                return mid;
            }
            if (elmtId < this[mid].elmtId) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return -1;
    }
}

/**
 * Used to store elmtIds of the components that are in WithTheme container scope.
 */
class ArkThemeScope {
    /**
     * elmtId of the CustomComponent which defines WithTheme container
     */
    private ownerComponentId: number;

    /**
     * elmtId of the WithTheme container that defines theme scope
     */
    private withThemeId: number;

    /**
     * WithTheme container options
     */
    private withThemeOptions: WithThemeOptions;

    /**
     * Previous scope color mode before option change
     */
    private prevColorMode: ThemeColorMode;

    /**
     * elmtIds of the components that are in this theme scope
     */
    private components: ArkThemeScopeArray;

    /**
     * Theme instance associated with this Theme Scope
     */
    private theme: ThemeInternal;

    /**
     * Initialize Theme Scope
     *
     * @param ownerComponentId elmtId of the CustomComponent which defines WithTheme container
     * @param withThemeId elmtId of the WithTheme container that defines theme scope
     * @param withThemeOptions WithTheme container options
     * @param theme Theme instance associated with this Theme Scope
     */
    constructor(ownerComponentId: number, withThemeId: number, withThemeOptions: WithThemeOptions, theme: ThemeInternal) {
        this.ownerComponentId = ownerComponentId;
        this.withThemeId = withThemeId;
        this.withThemeOptions = withThemeOptions;
        this.theme = theme;
        this.prevColorMode = this.colorMode();
    }

    /**
     * Get elmtId of the CustomComponent which defines WithTheme container
     *
     * @returns elmtId as number
     */
    getOwnerComponentId(): number {
        return this.ownerComponentId;
    }

    /**
     * Get elmtId of the WithTheme container that defines theme scope
     *
     * @returns elmtId as number
     */
    getWithThemeId(): number {
        return this.withThemeId;
    }

    /**
     * Add component to the current theme scope by elmtId
     *
     * @param elmtId elmtId as number
     * @param owner component owner id
     * @param componentName component name
     */
    addComponentToScope(elmtId: number, owner: number, componentName: string) {
        if (this.isComponentInScope(elmtId)) {
            return;
        }
        if (!this.components) {
            this.components = new ArkThemeScopeArray();
        }
        this.components.push({ elmtId: elmtId, owner: owner, name: componentName });
    }

    /**
     * Remove components from the current theme scope by elmtId
     *
     * @param elmtId elmtId as number
     */
    removeComponentFromScope(elmtId: number) {
        if (this.components) {
            const index = this.components.binarySearch(elmtId);
            if (index > -1) {
                this.components.splice(index, 1);
            }
        }
    }

    /**
     * Check whether the component with elmtId is in current theme scope
     *
     * @param elmtId elmtId as number
     * @returns true if theme scope contains component, otherwise false
     */
    isComponentInScope(elmtId: number): boolean {
        return this.components && (this.components.binarySearch(elmtId) > -1);
    }

    /**
     * Get all components elmtIds which are in current theme scope
     *
     * @returns array of elmIds as numbers
     */
    componentsInScope(): Array<ArkThemeScopeItem> {
        return this.components;
    }

    /**
     * Get color mode of the current theme scope
     *
     * @returns DARK, Light or SYSTEM values
     */
    colorMode(): ThemeColorMode {
        return this.withThemeOptions.colorMode ?? ThemeColorMode.SYSTEM;
    }

    /**
     * Get Custom Theme of the current theme scope
     *
     * @returns CustomTheme instance
     */
    customTheme(): CustomTheme {
        return this.withThemeOptions.theme ?? {};
    }

    /**
     * Get theme instance associated with this Theme Scope
     *
     * @returns theme instance
     */
    getTheme(): ThemeInternal {
        return this.theme;
    }

    /**
     * Get WithTheme container options
     *
     * @returns WithThemeOptions instance
     */
    options(): WithThemeOptions {
        return this.withThemeOptions;
    }

    /**
     * Update WithThemeOptions
     *
     * @param options WithThemeOptions instance
     * @param theme Theme instance associated with this Theme Scope
     */
    updateWithThemeOptions(options: WithThemeOptions, theme: ThemeInternal) {
        this.prevColorMode = this.colorMode();
        this.withThemeOptions = options;
        this.theme = theme;
    }

    /**
     * Check whether scope color mode changed in last update
     *
     * @returns true if color mode changed, otherwise false
     */
    isColorModeChanged() {
        return this.prevColorMode !== this.colorMode();
    }
}
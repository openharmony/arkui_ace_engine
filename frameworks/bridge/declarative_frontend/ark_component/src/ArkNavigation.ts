/// <reference path="./import.ts" />
const TITLE_MODE_RANGE = 2;
const NAV_BAR_POSITION_RANGE = 1;
const NAVIGATION_MODE_RANGE = 2;
const DEFAULT_NAV_BAR_WIDTH = 240;
const MIN_NAV_BAR_WIDTH_DEFAULT = "0vp";
const NAVUGATION_TITLE_MODE_DEFAULT = 0
const DEFAULT_UNIT = "vp";

class ArkNavigationComponent extends ArkComponent implements NavigationAttribute {
    navBarWidth(value: Length): NavigationAttribute {
        if (isNumber(value)) {
            value = value + DEFAULT_UNIT;
        }

        if (isString(value)) {
            modifier(this._modifiers, NavBarWidthModifier, value.toString());
        }

        return this;
    }
    navBarPosition(value: NavBarPosition): NavigationAttribute {
        if (value >= 0 && value <= NAV_BAR_POSITION_RANGE) {
            modifier(this._modifiers, NavBarPositionModifier, value);
        }
        return this;
    }
    navBarWidthRange(value: [Dimension, Dimension]): NavigationAttribute {
        if (!value) {
            return;
        }

        if (!!value && value?.length > 0 && !!value[0]) {
            let min: string | number;

            if (isNumber(value[0])) {
                min = value[0] + DEFAULT_UNIT;
            } else {
                min = value[0].toString()
            }

            modifier(this._modifiers, MinNavBarWidthModifier, min);
        } else {
            modifier(this._modifiers, MinNavBarWidthModifier, MIN_NAV_BAR_WIDTH_DEFAULT);
        }

        if (!!value && value?.length > 1 && !!value[1]) {
            let max: string | number;

            if (isNumber(value[1])) {
                max = max + DEFAULT_UNIT
            } else {
                max = value[1].toString()
            }

            modifier(this._modifiers, MaxNavBarWidthModifier, max);
        } else {
            modifier(this._modifiers, MaxNavBarWidthModifier, MIN_NAV_BAR_WIDTH_DEFAULT);
        }

        return this;
    }
    minContentWidth(value: Dimension): NavigationAttribute {
        let minContentWidth: string = 0 + DEFAULT_UNIT;

        if ((isNumber(value) && Number(value) > 0)) {
            minContentWidth = value + DEFAULT_UNIT
        }

        if (isString(value)) {
            minContentWidth = value.toString()
        }

        modifier(this._modifiers, MinContentWidthModifier, minContentWidth);

        return this;
    }
    mode(value: NavigationMode): NavigationAttribute {
        if (!isNumber(value)) {
            modifier(this._modifiers, ModeModifier, NavigationMode.Auto);
        } else if (value >= NavigationMode.Stack && value <= NAVIGATION_MODE_RANGE) {
            modifier(this._modifiers, ModeModifier, value);
        }
        return this;
    }
    backButtonIcon(value: any): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    hideNavBar(value: boolean): NavigationAttribute {
        modifier(this._modifiers, HideNavBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    title(value: any): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    subTitle(value: string): NavigationAttribute {
        modifier(this._modifiers, SubTitleModifier, value);
        return this;
    }
    hideTitleBar(value: boolean): NavigationAttribute {
        modifier(this._modifiers, NavigationHideTitleBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    hideBackButton(value: boolean): NavigationAttribute {
        modifier(this._modifiers, HideBackButtonModifier, isBoolean(value) ? value : false);
        return this;
    }
    titleMode(value: NavigationTitleMode): NavigationAttribute {
        if (value >= NAVUGATION_TITLE_MODE_DEFAULT && value <= TITLE_MODE_RANGE) {
            modifier(this._modifiers, TitleModeModifier, value);
        }
        return this;
    }
    menus(value: any): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    toolBar(value: any): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    toolbarConfiguration(value: any): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    hideToolBar(value: boolean): NavigationAttribute {
        modifier(this._modifiers, HideToolBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    onNavBarStateChange(callback: (isVisible: boolean) => void): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    onNavigationModeChange(callback: (mode: NavigationMode) => void): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
    navDestination(builder: (name: string, param: unknown) => void): NavigationAttribute {
        throw new Error("Method not implemented.");
    }
}

class MinNavBarWidthModifier extends Modifier<string> {
    static identity: Symbol = Symbol("minNavBarWidth");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetMinNavBarWidth(node);
        } else {
            GetUINativeModule().navigation.setMinNavBarWidth(node, this.value);
        }
    }
}

class MaxNavBarWidthModifier extends Modifier<string> {
    static identity: Symbol = Symbol("maxNavBarWidth");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetMaxNavBarWidth(node);
        } else {
            GetUINativeModule().navigation.setMaxNavBarWidth(node, this.value);
        }
    }
}
class MinContentWidthModifier extends Modifier<string> {
    static identity: Symbol = Symbol("minContentWidth");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetMinContentWidth(node);
        } else {
            GetUINativeModule().navigation.setMinContentWidth(node, this.value);
        }
    }
}

class NavBarWidthModifier extends Modifier<string> {
    static identity: Symbol = Symbol("navBarWidth");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetNavBarWidth(node);
        } else {
            GetUINativeModule().navigation.setNavBarWidth(node, this.value);
        }
    }
}

class NavBarPositionModifier extends Modifier<number> {
    static identity: Symbol = Symbol("navBarPosition");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetNavBarPosition(node);
        } else {
            GetUINativeModule().navigation.setNavBarPosition(node, this.value);
        }
    }
}

class ModeModifier extends Modifier<number> {
    static identity: Symbol = Symbol("mode");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetMode(node);
        } else {
            GetUINativeModule().navigation.setMode(node, this.value);
        }
    }
}

class HideToolBarModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("hideToolBar");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetHideToolBar(node);
        } else {
            GetUINativeModule().navigation.setHideToolBar(node, this.value);
        }
    }
}

class TitleModeModifier extends Modifier<number> {
    static identity: Symbol = Symbol("titleMode");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetTitleMode(node);
        } else {
            GetUINativeModule().navigation.setTitleMode(node, this.value);
        }
    }
}

class HideBackButtonModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("hideBackButton");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetHideBackButton(node);
        } else {
            GetUINativeModule().navigation.setHideBackButton(node, this.value);
        }
    }
}

class SubTitleModifier extends Modifier<string> {
    static identity: Symbol = Symbol("subTitle");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetSubTitle(node);
        } else {
            GetUINativeModule().navigation.setSubTitle(node, this.value);
        }
    }
}

class NavigationHideTitleBarModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("hideTitleBar");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetHideTitleBar(node);
        } else {
            GetUINativeModule().navigation.setHideTitleBar(node, this.value);
        }
    }
}

class HideNavBarModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("hideNavBar");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navigation.resetHideNavBar(node);
        } else {
            GetUINativeModule().navigation.setHideNavBar(node, this.value);
        }
    }
}

// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () => {
        return new ArkNavigationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

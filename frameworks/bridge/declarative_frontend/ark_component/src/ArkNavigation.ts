//@ts-nocheck
class ArkNavigationComponent extends ArkComponent implements NavigationAttribute {
    navBarWidth(value: Length): this {
        throw new Error("Method not implemented.");
    }
    navBarPosition(value: NavBarPosition): this {
        throw new Error("Method not implemented.");
    }
    navBarWidthRange(value: [Dimension, Dimension]): this {
        throw new Error("Method not implemented.");
    }
    minContentWidth(value: Dimension): this {
        throw new Error("Method not implemented.");
    }
    mode(value: NavigationMode): this {
        throw new Error("Method not implemented.");
    }
    backButtonIcon(value: any): this {
        throw new Error("Method not implemented.");
    }
    hideNavBar(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    title(value: any): this {
        throw new Error("Method not implemented.");
    }
    subTitle(value: string): this {
        throw new Error("Method not implemented.");
    }
    hideTitleBar(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    hideBackButton(value: boolean): this {
        throw new Error("Method not implemented.");
    }
    titleMode(value: NavigationTitleMode): this {
        throw new Error("Method not implemented.");
    }
    menus(value: any): this {
        throw new Error("Method not implemented.");
    }
    toolBar(value: any): this {
        throw new Error("Method not implemented.");
    }
    toolbarConfiguration(value: any): this {
        throw new Error("Method not implemented.");
    }
    hideToolBar(value: boolean): this {
        modifier(this._modifiers, HideToolBarModifier, isBoolean(value) ? value : false);
        return this;
    }
    onTitleModeChange(callback: (titleMode: NavigationTitleMode) => void): this {
        throw new Error("Method not implemented.");
    }
    onNavBarStateChange(callback: (isVisible: boolean) => void): this {
        throw new Error("Method not implemented.");
    }
    onNavigationModeChange(callback: (mode: NavigationMode) => void): this {
        throw new Error("Method not implemented.");
    }
    navDestination(builder: (name: string, param: unknown) => void): this {
        throw new Error("Method not implemented.");
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

//@ts-ignore
globalThis.Navigation.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkNavigationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
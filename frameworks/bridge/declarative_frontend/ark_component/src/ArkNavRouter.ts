/// <reference path="./import.ts" />
const NAV_ROUTE_MODE_RANGE = 2;
const NAV_ROUTE_MODE_DEFAULT = 0;
class ArkNavRouterComponent extends ArkComponent implements NavRouterAttribute {
    onStateChange(callback: (isActivated: boolean) => void): NavRouterAttribute {
        throw new Error("Method not implemented.");
    }
    mode(mode: NavRouteMode): NavRouterAttribute {
        if (isNumber(mode) && mode >= NAV_ROUTE_MODE_DEFAULT && mode <= NAV_ROUTE_MODE_RANGE) {
            modifier(this._modifiers, NavRouterModeModifier, mode);
        } else {
            modifier(this._modifiers, NavRouterModeModifier, NAV_ROUTE_MODE_DEFAULT);
        }
        return this;
    }
}

class NavRouterModeModifier extends Modifier<number> {
    static identity: Symbol = Symbol("mode");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navRouter.resetMode(node);
        } else {
            GetUINativeModule().navRouter.setMode(node, this.value);
        }
    }
}

// @ts-ignore
globalThis.NavRouter.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkNavRouterComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
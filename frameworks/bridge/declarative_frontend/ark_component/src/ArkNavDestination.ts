/// <reference path="./import.ts" />

class ArkNavDestinationComponent extends ArkComponent implements NavDestinationAttribute {
    title(value: any): this {
        throw new Error("Method not implemented.");
    }
    hideTitleBar(value: boolean): this {
        modifier(this._modifiers, HideTitleBarModifier, value);
        return this;
    }
    onShown(callback: () => void): this {
        throw new Error("Method not implemented.");
    }
    onHidden(callback: () => void): this {
        throw new Error("Method not implemented.");
    }
    onBackPressed(callback: () => boolean): this {
        throw new Error("Method not implemented.");
    }
}

class HideTitleBarModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("hideTitleBar");

    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().navDestination.resetHideTitleBar(node);
        } else {
            GetUINativeModule().navDestination.setHideTitleBar(node, this.value!);
        }
    }
}
//@ts-ignore
globalThis.NavDestination.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkNavDestinationComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

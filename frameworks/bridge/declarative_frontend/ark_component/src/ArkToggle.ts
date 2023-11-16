/// <reference path="./import.ts" />
class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    onChange(callback: (isOn: boolean) => void): ToggleAttribute {
        throw new Error("Method not implemented.");
    }
    selectedColor(value: number | undefined): ToggleAttribute {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSelectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, ToggleSelectedColorModifier, undefined);
        }
        return this;
    }
    switchPointColor(value: number | undefined): ToggleAttribute {
        var arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, undefined);
        }
        return this;
    }
}
class ToggleSelectedColorModifier extends Modifier<number | undefined> {
    static identity = Symbol("toggleSelectedColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            globalThis.getArkUINativeModule().toggle.resetSelectedColor(node);
        } else {
            globalThis.getArkUINativeModule().toggle.setSelectedColor(node, this.value);
        }
    }
}
class ToggleSwitchPointColorModifier extends Modifier<number | undefined> {
    static identity = Symbol("toggleSwitchPointColor");
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            globalThis.getArkUINativeModule().toggle.resetSwitchPointColor(node);
        } else {
            globalThis.getArkUINativeModule().toggle.setSwitchPointColor(node, this.value);
        }
    }
}
// @ts-ignore
globalThis.Toggle.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkToggleComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}


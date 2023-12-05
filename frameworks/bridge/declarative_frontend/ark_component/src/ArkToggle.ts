/// <reference path='./import.ts' />
class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error('Method not implemented.');
    }
    onChange(callback: (isOn: boolean) => void): this {
        throw new Error('Method not implemented.');
    }
    selectedColor(value: number | undefined): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSelectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, ToggleSelectedColorModifier, undefined);
        }
        return this;
    }
    switchPointColor(value: number | undefined): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, ToggleSwitchPointColorModifier, undefined);
        }
        return this;
    }
}
class ToggleSelectedColorModifier extends Modifier<number | undefined> {
    static identity = Symbol('toggleSelectedColor');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().toggle.resetSelectedColor(node);
        } else {
            GetUINativeModule().toggle.setSelectedColor(node, this.value);
        }
    }
}
class ToggleSwitchPointColorModifier extends Modifier<number | undefined> {
    static identity = Symbol('toggleSwitchPointColor');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().toggle.resetSwitchPointColor(node);
        } else {
            GetUINativeModule().toggle.setSwitchPointColor(node, this.value);
        }
    }
}
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkToggleComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}


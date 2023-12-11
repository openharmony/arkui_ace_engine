/// <reference path='./import.ts' />
class ArkToggleComponent extends ArkComponent implements ToggleAttribute {
    onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
        throw new Error('Method not implemented.');
    }
    onChange(callback: (isOn: boolean) => void): this {
        throw new Error('Method not implemented.');
    }
    selectedColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, ToggleSelectedColorModifier.identity, ToggleSelectedColorModifier, value);
        return this;
    }
    switchPointColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, ToggleSwitchPointColorModifier.identity, ToggleSwitchPointColorModifier, value);
        return this;
    }
}
class ToggleSelectedColorModifier extends ModifierWithKey<ResourceColor> {
    static identity = Symbol('toggleSelectedColor');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().toggle.resetSelectedColor(node);
        } else {
            GetUINativeModule().toggle.setSelectedColor(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        return true;
    }
}
class ToggleSwitchPointColorModifier extends ModifierWithKey<ResourceColor> {
    static identity = Symbol('toggleSwitchPointColor');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().toggle.resetSwitchPointColor(node);
        } else {
            GetUINativeModule().toggle.setSwitchPointColor(node, this.value);
        }
    }

    checkObjectDiff(): boolean {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        return true;
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


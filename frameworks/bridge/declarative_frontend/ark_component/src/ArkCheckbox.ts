/// <reference path="./import.ts" />
class ArkCheckboxComponent extends ArkComponent implements CheckboxAttribute {
    shape(value: CheckBoxShape): this {
        throw new Error("Method not implemented.");
    }
    select(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, CheckboxSelectModifier, value);
        } else {
            modifier(this._modifiers, CheckboxSelectModifier, false);
        }
        return this;
    }
    selectedColor(value: ResourceColor): this {
        if(isResource(value)){
            modifier(this._modifiers, CheckboxSelectedColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxSelectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, CheckboxSelectedColorModifier, undefined);
        }
        return this;
    }
    unselectedColor(value: ResourceColor): this {
        if(isResource(value)){
            modifier(this._modifiers, CheckboxUnselectedColorModifier, undefined);
            return this;
        }
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxUnselectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, CheckboxUnselectedColorModifier, undefined);
        }
        return this;
    }
    mark(value: MarkStyle): this {
        let arkMarkStyle = new ArkMarkStyle();
        if (arkMarkStyle.parseMarkStyle(value)) {
            modifier(this._modifiers, CheckboxMarkModifier, arkMarkStyle);
        } else {
            modifier(this._modifiers, CheckboxMarkModifier, undefined);
        }
        return this;
      }
    onChange(callback: (value: boolean) => void): this {
        throw new Error("Method not implemented.");
    }
}

// @ts-ignore
globalThis.Checkbox.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    var nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    var component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkCheckboxComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}

class CheckboxMarkModifier extends Modifier<ArkMarkStyle> {
    static identity: Symbol = Symbol("checkboxMark");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkbox.resetMark(node);
        }
        else {
            GetUINativeModule().checkbox.setMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
        }
    }
}
class CheckboxSelectModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("checkboxSelect");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkbox.resetSelect(node);
        }
        else {
            GetUINativeModule().checkbox.setSelect(node, this.value);
        }
    }
}

class CheckboxSelectedColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("checkboxSelectedColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkbox.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().checkbox.setSelectedColor(node, this.value);
        }
    }
}

class CheckboxUnselectedColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("checkboxUnselectedColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkbox.resetUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkbox.setUnSelectedColor(node, this.value);
        }
    }
}
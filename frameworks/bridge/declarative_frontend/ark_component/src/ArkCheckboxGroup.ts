/// <reference path="./ArkViewStackProcessor.ts" />
class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
    selectAll(value: boolean): this {
        if (typeof value === "boolean") {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, value);
        } else {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, undefined);
        }
        return this;
    }
    selectedColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxGroupSelectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, CheckboxGroupSelectedColorModifier, undefined);
        }
        return this;
    }
    unselectedColor(value: ResourceColor): this {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
            modifier(this._modifiers, CheckboxGroupUnselectedColorModifier, arkColor.color);
        } else {
            modifier(this._modifiers, CheckboxGroupUnselectedColorModifier, undefined);
        }
        return this;
    }
    mark(value: MarkStyle): this {
        var arkMarkStyle = new ArkMarkStyle();
        if (arkMarkStyle.parseMarkStyle(value)) {
            modifier(this._modifiers, CheckboxGroupMarkModifier, arkMarkStyle);
        } else {
            modifier(this._modifiers, CheckboxGroupMarkModifier, undefined);
        }
        return this;
      }
      onChange(callback: (event: CheckboxGroupResult) => void): CheckboxGroupAttribute {
        throw new Error("Method not implemented.");
    }
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () =>
    {
        return new ArkCheckboxGroupComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}
class CheckboxgroupSelectAllModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol("checkboxgroupSelectAll");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectAll(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectAll(node, this.value);
        }
    }
}
class CheckboxgroupSelectedColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("checkboxgroupSelectedColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectedColor(node, this.value);
        }
    }
}
class CheckboxgroupUnselectedColorModifier extends Modifier<number | undefined> {
    static identity: Symbol = Symbol("checkboxgroupUnselectedColor");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setUnSelectedColor(node, this.value);
        }
    }
}
class CheckboxgroupMarkModifier extends Modifier<ArkMarkStyle> {
    static identity: Symbol = Symbol("checkboxgroupMark");
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetMark(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setMark(node, this.value?.strokeColor, this.value?.size,
                this.value?.strokeWidth);
        }
    }
}

/// <reference path='./ArkViewStackProcessor.ts' />
class CheckboxGroupSelectAllModifier extends Modifier<boolean> {
    static identity: Symbol = Symbol('checkboxgroupSelectAll');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectAll(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectAll(node, this.value);
        }
    }
}

class CheckboxGroupSelectedColorModifier extends ModifierWithKey<ResourceColor> {
    static identity: Symbol = Symbol('checkboxgroupSelectedColor');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setSelectedColor(node, this.value);
        }
    }

    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }    
}

class CheckboxGroupUnselectedColorModifier extends ModifierWithKey<ResourceColor> {
    static identity: Symbol = Symbol('checkboxgroupUnselectedColor');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setUnSelectedColor(node, this.value);
        }
    }

    checkObjectDiff() {
        if (isResource(this.stageValue) && isResource(this.value)) {
            return !isResourceEqual(this.stageValue, this.value);
        }
        else {
            return true;
        }
    }
}
class CheckboxGroupMarkModifier extends ModifierWithKey<MarkStyle> {
  static identity: Symbol = Symbol('checkboxgroupMark');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().checkboxgroup.resetMark(node);
    }
    else {
      GetUINativeModule().checkboxgroup.setMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
    }
  }

  checkObjectDiff(): boolean {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;    
  }
}
class ArkCheckboxGroupComponent extends ArkComponent implements CheckboxGroupAttribute {
    selectAll(value: boolean): this {
        if (isBoolean(value)) {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, value);
        } else {
            modifier(this._modifiers, CheckboxGroupSelectAllModifier, undefined);
        }
        return this;
    }
    selectedColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectedColorModifier.identity, CheckboxGroupSelectedColorModifier, value);
        return this;
    }
    unselectedColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, CheckboxGroupUnselectedColorModifier.identity, CheckboxGroupUnselectedColorModifier, value);
        return this;
    }
    mark(value: MarkStyle): this {
        modifierWithKey(
          this._modifiersWithKeys, CheckboxGroupMarkModifier.identity, CheckboxGroupMarkModifier, value);
        return this;
    }
    onChange(callback: (event: CheckboxGroupResult) => void): CheckboxGroupAttribute {
        throw new Error('Method not implemented.');
    }
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
        return new ArkCheckboxGroupComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
}


/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/// <reference path='./import.ts' />
class CheckboxGroupSelectAllModifier extends Modifier<boolean> {
    constructor(value: boolean) {
        super(value);
    }
    static identity: Symbol = Symbol('checkboxgroupSelectAll');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetCheckboxGroupSelectAll(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(node, this.value);
        }
    }
}

class CheckboxGroupSelectedColorModifier extends ModifierWithKey<ResourceColor> {
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: Symbol = Symbol('checkboxgroupSelectedColor');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetCheckboxGroupSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setCheckboxGroupSelectedColor(node, this.value);
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
    constructor(value: ResourceColor) {
        super(value);
    }
    static identity: Symbol = Symbol('checkboxgroupUnselectedColor');
    applyPeer(node: KNode, reset: boolean) {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetCheckboxGroupUnSelectedColor(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setCheckboxGroupUnSelectedColor(node, this.value);
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
    constructor(value: MarkStyle) {
        super(value);
    }
    static identity: Symbol = Symbol('checkboxgroupMark');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            GetUINativeModule().checkboxgroup.resetCheckboxGroupMark(node);
        }
        else {
            GetUINativeModule().checkboxgroup.setCheckboxGroupMark(node, this.value?.strokeColor, this.value?.size, this.value?.strokeWidth);
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
    constructor(nativePtr: KNode) {
      super(nativePtr);
    }
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
    applyUIAttributes(modifier, nativeNode, component);
    component.applyModifierPatch();
}


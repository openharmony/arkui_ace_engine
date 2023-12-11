/// <reference path='./import.ts' />

class ItemConstraintSizeModifier extends ModifierWithKey<ArkConstraintSizeOptions> {
  static identity: Symbol = Symbol('itemConstraintSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetItemConstraintSize(node);
    } else {
      GetUINativeModule().waterFlow.setItemConstraintSize(node, this.value.minWidth,
        this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.minWidth, this.value.minWidth) ||
      !isBaseOrResourceEqual(this.stageValue.maxWidth, this.value.maxWidth) ||
      !isBaseOrResourceEqual(this.stageValue.minHeight, this.value.minHeight) ||
      !isBaseOrResourceEqual(this.stageValue.maxHeight, this.value.maxHeight)
  }
}

class ColumnsTemplateModifier extends Modifier<string> {
  static identity: Symbol = Symbol('columnsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetColumnsTemplate(node);
    } else {
      GetUINativeModule().waterFlow.setColumnsTemplate(node, this.value);
    }
  }
}

class RowsTemplateModifier extends Modifier<string> {
  static identity: Symbol = Symbol('rowsTemplate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetRowsTemplate(node);
    } else {
      GetUINativeModule().waterFlow.setRowsTemplate(node, this.value);
    }
  }
}

class EnableScrollInteractionModifier extends Modifier<boolean> {
  static identity = Symbol('enableScrollInteraction');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().waterFlow.resetEnableScrollInteraction(node);
      }
      else {
          GetUINativeModule().waterFlow.setEnableScrollInteraction(node, this.value);
      }
  }
}

class RowsGapModifier extends ModifierWithKey<number | string> {
  static identity: Symbol = Symbol('rowsGap');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().waterFlow.resetRowsGap(node);
      }
      else {
          GetUINativeModule().waterFlow.setRowsGap(node, this.value);
      }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class ColumnsGapModifier extends ModifierWithKey<number | string> {
  static identity: Symbol = Symbol('columnsGap');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          GetUINativeModule().waterFlow.resetColumnsGap(node);
      }
      else {
          GetUINativeModule().waterFlow.setColumnsGap(node, this.value);
      }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class LayoutDirectionModifier extends Modifier<number> {
  static identity: Symbol = Symbol('layoutDirection');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetLayoutDirection(node);
    }
    else {
      GetUINativeModule().waterFlow.setLayoutDirection(node, this.value);
    }
  }
}

class NestedScrollModifier extends Modifier<ArkNestedScrollOptions> {
  static identity: Symbol = Symbol('nestedScroll');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetNestedScroll(node);
    }
    else {
      GetUINativeModule().waterFlow.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
    }
  }
}

class FrictionModifier extends ModifierWithKey<number | Resource> {
  static identity: Symbol = Symbol('friction');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().waterFlow.resetFriction(node);
    }
    else {
      GetUINativeModule().waterFlow.setFriction(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else {
      return true;
    }
  }
}

class ArkWaterFlowComponent extends ArkComponent implements WaterFlowAttribute {
  columnsTemplate(value: string): this {
    if (isString(value)) {
      modifier(this._modifiers, ColumnsTemplateModifier, value);
    } else {
      modifier(this._modifiers, ColumnsTemplateModifier, undefined);
    }
    return this;
  }
  rowsTemplate(value: string): this {
    if (isString(value)) {
      modifier(this._modifiers, RowsTemplateModifier, value);
    } else {
      modifier(this._modifiers, RowsTemplateModifier, undefined);
    }
    return this;
  }
  itemConstraintSize(value: ConstraintSizeOptions): this {
    if (!value) {
      modifierWithKey(
        this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, undefined);
      return this;
    }
    let arkValue: ArkConstraintSizeOptions = new ArkConstraintSizeOptions();
    arkValue.minWidth = value.minWidth;
    arkValue.maxWidth = value.maxWidth;
    arkValue.minHeight = value.minHeight;
    arkValue.maxHeight = value.maxHeight;
    modifierWithKey(this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, arkValue);
    return this;
  }
  columnsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, ColumnsGapModifier.identity, ColumnsGapModifier, value);
    return this;
  }
  rowsGap(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, RowsGapModifier.identity, RowsGapModifier, value);
    return this;
  }
  layoutDirection(value: FlexDirection): this {
    if (value in FlexDirection) {
      modifier(this._modifiers, LayoutDirectionModifier, value);
    } else {
      modifier(this._modifiers, LayoutDirectionModifier, undefined);
    }
    return this;
  }
  nestedScroll(value: NestedScrollOptions): this {
    let options = new ArkNestedScrollOptions();
    if (value) {
      if (value.scrollForward) {
        options.scrollForward = value.scrollForward;
      }
      if (value.scrollBackward) {
        options.scrollBackward = value.scrollBackward;
      }
      modifier(this._modifiers, NestedScrollModifier, options);
    }
    return this;
  }
  enableScrollInteraction(value: boolean): this {
    if (typeof value === 'boolean') {
      modifier(
        this._modifiers, EnableScrollInteractionModifier, value);
    } else {
      modifier(
        this._modifiers, EnableScrollInteractionModifier, undefined);
    }
    return this;
  }
  friction(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, FrictionModifier.identity, FrictionModifier, value);
    return this;
  }
  cachedCount(value: number): this {
    throw new Error('Method not implemented.');
  }
  onReachStart(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event: () => void): this {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event: (offset: number, state: ScrollState) => { offsetRemain: number; }): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}

// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWaterFlowComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

/// <reference path='./import.ts' />
class TextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  static identity: Symbol = Symbol('textStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().calendarPicker.resetTextStyle(node);
    } else {
      GetUINativeModule().calendarPicker.setTextStyle(node,
        this.value?.color ?? undefined,
        this.value?.font?.size ?? undefined,
        this.value?.font?.weight ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue?.font?.weight === this.value?.font?.weight)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.color, this.value?.color) ||
        !isBaseOrResourceEqual(this.stageValue?.font?.size, this.value?.font?.size);
    }
  }
}

class EdgeAlignModifier extends ModifierWithKey<ArkEdgeAlign> {
  static identity: Symbol = Symbol('edgeAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().calendarPicker.resetEdgeAlign(node);
    } else {
      GetUINativeModule().calendarPicker.setEdgeAlign(node,
        this.value?.alignType ?? undefined,
        this.value?.offset?.dx ?? undefined,
        this.value?.offset?.dy ?? undefined);
    }
  }

  checkObjectDiff(): boolean {
    if (!(this.stageValue.alignType === this.value.alignType)) {
      return true;
    } else {
      return !isBaseOrResourceEqual(this.stageValue?.offset?.dx, this.value?.offset?.dx) ||
        !isBaseOrResourceEqual(this.stageValue?.offset?.dy, this.value?.offset?.dy);
    }
  }
}

class ArkCalendarPickerComponent extends ArkComponent implements CalendarPickerAttribute {
  edgeAlign(alignType: CalendarAlign, offset?: Offset | undefined): this {
    let arkEdgeAlign = new ArkEdgeAlign();
    arkEdgeAlign.alignType = alignType;
    arkEdgeAlign.offset = offset;
    modifierWithKey(this._modifiersWithKeys, EdgeAlignModifier.identity, EdgeAlignModifier, arkEdgeAlign);
    return this;
  }
  textStyle(value: PickerTextStyle): this {
    modifierWithKey(this._modifiersWithKeys, TextStyleModifier.identity, TextStyleModifier, value);
    return this;
  }
  onChange(callback: (value: Date) => void): this {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.CalendarPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCalendarPickerComponent(nativeNode);
  });
  modifier.applyNormalAttribute(component);
  component.applyModifierPatch();
}

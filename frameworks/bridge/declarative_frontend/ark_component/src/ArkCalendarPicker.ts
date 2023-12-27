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
class TextStyleModifier extends ModifierWithKey<PickerTextStyle> {
  constructor(value: PickerTextStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('textStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetTextStyle(node);
    } else {
      getUINativeModule().calendarPicker.setTextStyle(node,
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
  constructor(value: ArkEdgeAlign) {
    super(value);
  }
  static identity: Symbol = Symbol('edgeAlign');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetEdgeAlign(node);
    } else {
      getUINativeModule().calendarPicker.setEdgeAlign(node,
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
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
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
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCalendarPickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

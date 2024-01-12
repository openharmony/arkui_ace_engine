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

class CalendarPickerPaddingModifier extends ModifierWithKey<ArkPadding> {
  constructor(value: ArkPadding) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerPadding');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerPadding(node);
    } else {
      getUINativeModule().calendarPicker.setCalendarPickerPadding(node, this.value.top,
        this.value.right, this.value.bottom, this.value.left);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}

class CalendarPickerBorderModifier extends ModifierWithKey<ArkBorder> {
  constructor(value: ArkBorder) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerBorder');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorder(node);
    } else {
      getUINativeModule().calendarPicker.setCalendarPickerBorder(node,
        this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor,
        this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
        this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
    }
  }

  checkObjectDiff(): boolean {
    return this.value.checkObjectDiff(this.stageValue);
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
  padding(value: Padding | Length): this {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = <Length>value;
        arkValue.right = <Length>value;
        arkValue.bottom = <Length>value;
        arkValue.left = <Length>value;
      } else {
        arkValue.top = (<Margin>value).top;
        arkValue.right = (<Margin>value).right;
        arkValue.bottom = (<Margin>value).bottom;
        arkValue.left = (<Margin>value).left;
      }
      modifierWithKey(this._modifiersWithKeys, CalendarPickerPaddingModifier.identity,
        CalendarPickerPaddingModifier, arkValue);
    } else {
      modifierWithKey(this._modifiersWithKeys, CalendarPickerPaddingModifier.identity,
        CalendarPickerPaddingModifier, undefined);
    }
    return this;
  }
  border(value: BorderOptions): this {
    let arkBorder = new ArkBorder();
    if (isUndefined(value)) {
      arkBorder = undefined;
    }

    if (!isUndefined(value?.width) && value?.width !== null) {
      if (isNumber(value.width) || isString(value.width) || isResource(value.width)) {
        arkBorder.arkWidth.left = value.width;
        arkBorder.arkWidth.right = value.width;
        arkBorder.arkWidth.top = value.width;
        arkBorder.arkWidth.bottom = value.width;
      } else {
        arkBorder.arkWidth.left = (value.width as EdgeWidths).left;
        arkBorder.arkWidth.right = (value.width as EdgeWidths).right;
        arkBorder.arkWidth.top = (value.width as EdgeWidths).top;
        arkBorder.arkWidth.bottom = (value.width as EdgeWidths).bottom;
      }
    }
    if (!isUndefined(value?.color) && value?.color !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        arkBorder.arkColor.leftColor = value.color;
        arkBorder.arkColor.rightColor = value.color;
        arkBorder.arkColor.topColor = value.color;
        arkBorder.arkColor.bottomColor = value.color;
      } else {
        arkBorder.arkColor.leftColor = (value.color as EdgeColors).left;
        arkBorder.arkColor.rightColor = (value.color as EdgeColors).right;
        arkBorder.arkColor.topColor = (value.color as EdgeColors).top;
        arkBorder.arkColor.bottomColor = (value.color as EdgeColors).bottom;
      }
    }
    if (!isUndefined(value?.radius) && value?.radius !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        arkBorder.arkRadius.topLeft = value.radius;
        arkBorder.arkRadius.topRight = value.radius;
        arkBorder.arkRadius.bottomLeft = value.radius;
        arkBorder.arkRadius.bottomRight = value.radius;
      } else {
        arkBorder.arkRadius.topLeft = (value.radius as BorderRadiuses)?.topLeft;
        arkBorder.arkRadius.topRight = (value.radius as BorderRadiuses)?.topRight;
        arkBorder.arkRadius.bottomLeft = (value.radius as BorderRadiuses)?.bottomLeft;
        arkBorder.arkRadius.bottomRight = (value.radius as BorderRadiuses)?.bottomRight;
      }
    }
    if (!isUndefined(value?.style) && value?.style !== null) {
      let arkBorderStyle = new ArkBorderStyle();
      if (arkBorderStyle.parseBorderStyle(value.style)) {
        if (!isUndefined(arkBorderStyle.style)) {
          arkBorder.arkStyle.top = arkBorderStyle.style;
          arkBorder.arkStyle.left = arkBorderStyle.style;
          arkBorder.arkStyle.bottom = arkBorderStyle.style;
          arkBorder.arkStyle.right = arkBorderStyle.style;
        } else {
          arkBorder.arkStyle.top = arkBorderStyle.top;
          arkBorder.arkStyle.left = arkBorderStyle.left;
          arkBorder.arkStyle.bottom = arkBorderStyle.bottom;
          arkBorder.arkStyle.right = arkBorderStyle.right;
        }
      }
    }
    modifierWithKey(this._modifiersWithKeys, CalendarPickerBorderModifier.identity, CalendarPickerBorderModifier, arkBorder);
    return this;
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

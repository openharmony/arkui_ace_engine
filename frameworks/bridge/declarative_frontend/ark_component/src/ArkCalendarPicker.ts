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

class CalendarPickerHeightModifier extends ModifierWithKey<Length> {
  constructor(value: Length) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerHeight');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerHeight(node);
    } else {
      getUINativeModule().calendarPicker.setCalendarPickerHeight(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class CalendarPickerBorderRadiusModifier extends ModifierWithKey<Length | BorderRadiuses | LocalizedBorderRadius> {
  constructor(value: Length | BorderRadiuses | LocalizedBorderRadius) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerBorderRadius');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
            (Object.keys(this.value).indexOf('topEnd') >= 0) ||
            (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
            (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node,
            (this.value as LocalizedBorderRadius).topStart,
            (this.value as LocalizedBorderRadius).topEnd,
            (this.value as LocalizedBorderRadius).bottomStart,
            (this.value as LocalizedBorderRadius).bottomEnd);
        } else {
          getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node,
            (this.value as BorderRadiuses).topLeft,
            (this.value as BorderRadiuses).topRight,
            (this.value as BorderRadiuses).bottomLeft,
            (this.value as BorderRadiuses).bottomRight);
        }
      }
    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
        return !((this.stageValue as LocalizedBorderRadius).topStart === (this.value as LocalizedBorderRadius).topStart &&
          (this.stageValue as LocalizedBorderRadius).topEnd === (this.value as LocalizedBorderRadius).topEnd &&
          (this.stageValue as LocalizedBorderRadius).bottomStart === (this.value as LocalizedBorderRadius).bottomStart &&
          (this.stageValue as LocalizedBorderRadius).bottomEnd === (this.value as LocalizedBorderRadius).bottomEnd);
      }
      return !((this.stageValue as BorderRadiuses).topLeft === (this.value as BorderRadiuses).topLeft &&
        (this.stageValue as BorderRadiuses).topRight === (this.value as BorderRadiuses).topRight &&
        (this.stageValue as BorderRadiuses).bottomLeft === (this.value as BorderRadiuses).bottomLeft &&
        (this.stageValue as BorderRadiuses).bottomRight === (this.value as BorderRadiuses).bottomRight);
    } else {
      return true;
    }
  }
}

class CalendarPickerBorderColorModifier extends ModifierWithKey<ResourceColor | EdgeColors | LocalizedEdgeColors> {
  constructor(value: ResourceColor | EdgeColors | LocalizedEdgeColors) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerBorderColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorderColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node, this.value, this.value, this.value, this.value);
      } else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
            (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node,
            (this.value as LocalizedEdgeColors).top,
            (this.value as LocalizedEdgeColors).end,
            (this.value as LocalizedEdgeColors).bottom,
            (this.value as LocalizedEdgeColors).start,
            true);
        } else {
          getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node,
            (this.value as EdgeColors).top,
            (this.value as EdgeColors).right,
            (this.value as EdgeColors).bottom,
            (this.value as EdgeColors).left,
            false);
        }
      }

    }
  }

  checkObjectDiff(): boolean {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
        return !((this.stageValue as LocalizedEdgeColors).start === (this.value as LocalizedEdgeColors).start &&
          (this.stageValue as LocalizedEdgeColors).end === (this.value as LocalizedEdgeColors).end &&
          (this.stageValue as LocalizedEdgeColors).top === (this.value as LocalizedEdgeColors).top &&
          (this.stageValue as LocalizedEdgeColors).bottom === (this.value as LocalizedEdgeColors).bottom);
      }
      return !((this.stageValue as EdgeColors).left === (this.value as EdgeColors).left &&
        (this.stageValue as EdgeColors).right === (this.value as EdgeColors).right &&
        (this.stageValue as EdgeColors).top === (this.value as EdgeColors).top &&
        (this.stageValue as EdgeColors).bottom === (this.value as EdgeColors).bottom);
    } else {
      return true;
    }
  }
}

class CalendarPickerMarkTodayModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('calendarPickerMarkToday');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerMarkToday(node);
    } else {
      getUINativeModule().calendarPicker.setCalendarPickerMarkToday(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkCalendarPickerComponent extends ArkComponent implements CalendarPickerAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
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
  height(value: Length): this {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerHeightModifier.identity, CalendarPickerHeightModifier, value);
    return this;
  }
  borderRadius(value: Length | BorderRadiuses): this {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerBorderRadiusModifier.identity, CalendarPickerBorderRadiusModifier, value);
    return this;
  }
  borderColor(value: ResourceColor | EdgeColors): this {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerBorderColorModifier.identity, CalendarPickerBorderColorModifier, value);
    return this;
  }
  markToday(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerMarkTodayModifier.identity, CalendarPickerMarkTodayModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.CalendarPicker.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkCalendarPickerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CalendarPickerModifier(nativePtr, classType);
  });
};

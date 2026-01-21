/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
class ArkCalendarPickerComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  edgeAlign(alignType, offset) {
    let arkEdgeAlign = new ArkEdgeAlign();
    arkEdgeAlign.alignType = alignType;
    arkEdgeAlign.offset = offset;
    modifierWithKey(this._modifiersWithKeys, EdgeAlignModifier.identity, EdgeAlignModifier, arkEdgeAlign);
    return this;
  }
  textStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextStyleModifier.identity, TextStyleModifier, value);
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerOnChangeModifier.identity, CalendarPickerOnChangeModifier, callback);
    return this;
  }
  padding(value) {
    let arkValue = new ArkPadding();
    if (value !== null && value !== undefined) {
      if (isLengthType(value) || isResource(value)) {
        arkValue.top = value;
        arkValue.right = value;
        arkValue.bottom = value;
        arkValue.left = value;
      }
      else {
        arkValue.top = value.top;
        arkValue.right = value.right;
        arkValue.bottom = value.bottom;
        arkValue.left = value.left;
      }
      modifierWithKey(this._modifiersWithKeys, CalendarPickerPaddingModifier.identity, CalendarPickerPaddingModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, CalendarPickerPaddingModifier.identity, CalendarPickerPaddingModifier, undefined);
    }
    return this;
  }
  border(value) {
    let _a, _b, _c, _d;
    let arkBorder = new ArkBorder();
    if (isUndefined(value)) {
      arkBorder = undefined;
    }
    if (!isUndefined(value === null || value === void 0 ? void 0 : value.width) && (value === null || value === void 0 ? void 0 : value.width) !== null) {
      if (isNumber(value.width) || isString(value.width) || isResource(value.width)) {
        arkBorder.arkWidth.left = value.width;
        arkBorder.arkWidth.right = value.width;
        arkBorder.arkWidth.top = value.width;
        arkBorder.arkWidth.bottom = value.width;
      }
      else {
        arkBorder.arkWidth.left = value.width.left;
        arkBorder.arkWidth.right = value.width.right;
        arkBorder.arkWidth.top = value.width.top;
        arkBorder.arkWidth.bottom = value.width.bottom;
      }
    }
    if (!isUndefined(value === null || value === void 0 ? void 0 : value.color) && (value === null || value === void 0 ? void 0 : value.color) !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        arkBorder.arkColor.leftColor = value.color;
        arkBorder.arkColor.rightColor = value.color;
        arkBorder.arkColor.topColor = value.color;
        arkBorder.arkColor.bottomColor = value.color;
      }
      else {
        arkBorder.arkColor.leftColor = value.color.left;
        arkBorder.arkColor.rightColor = value.color.right;
        arkBorder.arkColor.topColor = value.color.top;
        arkBorder.arkColor.bottomColor = value.color.bottom;
      }
    }
    if (!isUndefined(value === null || value === void 0 ? void 0 : value.radius) && (value === null || value === void 0 ? void 0 : value.radius) !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        arkBorder.arkRadius.topLeft = value.radius;
        arkBorder.arkRadius.topRight = value.radius;
        arkBorder.arkRadius.bottomLeft = value.radius;
        arkBorder.arkRadius.bottomRight = value.radius;
      }
      else {
        arkBorder.arkRadius.topLeft = (_a = value.radius) === null || _a === void 0 ? void 0 : _a.topLeft;
        arkBorder.arkRadius.topRight = (_b = value.radius) === null || _b === void 0 ? void 0 : _b.topRight;
        arkBorder.arkRadius.bottomLeft = (_c = value.radius) === null || _c === void 0 ? void 0 : _c.bottomLeft;
        arkBorder.arkRadius.bottomRight = (_d = value.radius) === null || _d === void 0 ? void 0 : _d.bottomRight;
      }
    }
    if (!isUndefined(value === null || value === void 0 ? void 0 : value.style) && (value === null || value === void 0 ? void 0 : value.style) !== null) {
      let arkBorderStyle = new ArkBorderStyle();
      if (arkBorderStyle.parseBorderStyle(value.style)) {
        if (!isUndefined(arkBorderStyle.style)) {
          arkBorder.arkStyle.top = arkBorderStyle.style;
          arkBorder.arkStyle.left = arkBorderStyle.style;
          arkBorder.arkStyle.bottom = arkBorderStyle.style;
          arkBorder.arkStyle.right = arkBorderStyle.style;
        }
        else {
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
  height(value) {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerHeightModifier.identity, CalendarPickerHeightModifier, value);
    return this;
  }
  borderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerBorderRadiusModifier.identity, CalendarPickerBorderRadiusModifier, value);
    return this;
  }
  borderColor(value) {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerBorderColorModifier.identity, CalendarPickerBorderColorModifier, value);
    return this;
  }
  markToday(value) {
    modifierWithKey(this._modifiersWithKeys, CalendarPickerMarkTodayModifier.identity, CalendarPickerMarkTodayModifier, value);
    return this;
  }
}

class TextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().calendarPicker.resetTextStyle(node);
    }
    else {
      getUINativeModule().calendarPicker.setTextStyle(node, (_b = (_a = this.value) === null ||
        _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
        (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
          _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h =
            (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
              _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
      ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.color, (_f = this.value) === null ||
        _f === void 0 ? void 0 : _f.color) ||
        !isBaseOrResourceEqual((_h = (_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.font) === null ||
          _h === void 0 ? void 0 : _h.size, (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
            _k === void 0 ? void 0 : _k.size);
    }
  }
}

TextStyleModifier.identity = Symbol('textStyle');
class EdgeAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().calendarPicker.resetEdgeAlign(node);
    }
    else {
      getUINativeModule().calendarPicker.setEdgeAlign(node, (_b = (_a = this.value) === null ||
        _a === void 0 ? void 0 : _a.alignType) !== null && _b !== void 0 ? _b : undefined,
        (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.offset) === null ||
          _d === void 0 ? void 0 : _d.dx) !== null && _e !== void 0 ? _e : undefined, (_h = (_g =
            (_f = this.value) === null || _f === void 0 ? void 0 : _f.offset) === null ||
            _g === void 0 ? void 0 : _g.dy) !== null && _h !== void 0 ? _h : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (!(this.stageValue.alignType === this.value.alignType)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.offset) === null || _b === void 0 ? void 0 : _b.dx, (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.offset) === null || _d === void 0 ? void 0 : _d.dx) ||
        !isBaseOrResourceEqual((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.offset) === null || _f === void 0 ? void 0 : _f.dy, (_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.offset) === null || _h === void 0 ? void 0 : _h.dy);
    }
  }
}
EdgeAlignModifier.identity = Symbol('edgeAlign');

class CalendarPickerPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerPadding(node);
    }
    else {
      getUINativeModule().calendarPicker.setCalendarPickerPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
CalendarPickerPaddingModifier.identity = Symbol('calendarPickerPadding');
class CalendarPickerBorderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorder(node);
    }
    else {
      getUINativeModule().calendarPicker.setCalendarPickerBorder(node, this.value.arkWidth.left,
        this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor,
        this.value.arkColor.bottomColor, this.value.arkRadius.topLeft, this.value.arkRadius.topRight,
        this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight, this.value.arkStyle.top,
        this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
    }
  }
  checkObjectDiff() {
    return this.value.checkObjectDiff(this.stageValue);
  }
}
CalendarPickerBorderModifier.identity = Symbol('calendarPickerBorder');

class CalendarPickerHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerHeight(node);
    }
    else {
      getUINativeModule().calendarPicker.setCalendarPickerHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CalendarPickerHeightModifier.identity = Symbol('calendarPickerHeight');

class CalendarPickerBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
          (Object.keys(this.value).indexOf('topEnd') >= 0) ||
          (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
          (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
          getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node, this.value.topStart, this.value.topEnd, this.value.bottomStart, this.value.bottomEnd);
        } else {
          getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
        }
      }
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('topStart') >= 0) ||
        (Object.keys(this.value).indexOf('topEnd') >= 0) ||
        (Object.keys(this.value).indexOf('bottomStart') >= 0) ||
        (Object.keys(this.value).indexOf('bottomEnd') >= 0)) {
        return !(this.stageValue.topStart === this.value.topStart &&
          this.stageValue.topEnd === this.value.topEnd &&
          this.stageValue.bottomStart === this.value.bottomStart &&
          this.stageValue.bottomEnd === this.value.bottomEnd);
      }
      return !(this.stageValue.topLeft === this.value.topLeft &&
        this.stageValue.topRight === this.value.topRight &&
        this.stageValue.bottomLeft === this.value.bottomLeft &&
        this.stageValue.bottomRight === this.value.bottomRight);
    }
    else {
      return true;
    }
  }
}
CalendarPickerBorderRadiusModifier.identity = Symbol('calendarPickerBorderRadius');

class CalendarPickerBorderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerBorderColor(node);
    }
    else {
      const valueType = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node, this.value, this.value, this.value, this.value, false);
      }
      else {
        if ((Object.keys(this.value).indexOf('start') >= 0) ||
          (Object.keys(this.value).indexOf('end') >= 0)) {
          getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node, this.value.top, this.value.end, this.value.bottom, this.value.start, true);
        } else {
          getUINativeModule().calendarPicker.setCalendarPickerBorderColor(node, this.value.top, this.value.right, this.value.bottom, this.value.left, false);
        }
      }
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
      if ((Object.keys(this.value).indexOf('start') >= 0) ||
        (Object.keys(this.value).indexOf('end') >= 0)) {
        return !(this.stageValue.start === this.value.start &&
          this.stageValue.end === this.value.end &&
          this.stageValue.top === this.value.top &&
          this.stageValue.bottom === this.value.bottom);
      }
      return !(this.stageValue.left === this.value.left &&
        this.stageValue.right === this.value.right &&
        this.stageValue.top === this.value.top &&
        this.stageValue.bottom === this.value.bottom);
    }
    else {
      return true;
    }
  }
}
CalendarPickerBorderColorModifier.identity = Symbol('calendarPickerBorderColor');

class CalendarPickerMarkTodayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerMarkToday(node);
    }
    else {
      getUINativeModule().calendarPicker.setCalendarPickerMarkToday(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CalendarPickerMarkTodayModifier.identity = Symbol('calendarPickerMarkToday');

class CalendarPickerOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().calendarPicker.resetCalendarPickerOnChange(node);
    } else {
      getUINativeModule().calendarPicker.setCalendarPickerOnChange(node, this.value);
    }
  }
}
CalendarPickerOnChangeModifier.identity = Symbol('calendarPickerOnChange');

class JSCalendarPicker extends JSViewAbstract {
  static create(params) {
    getUINativeModule().calendarPicker.create(params);
  }

  static edgeAlign(alignType, offset) {
    getUINativeModule().calendarPicker.setEdgeAlign(true, alignType, offset);
  }

  static textStyle(value) {
    getUINativeModule().calendarPicker.setTextStyle(true, value);
  }

  static onChange(callback) {
      getUINativeModule().calendarPicker.setCalendarPickerOnChange(true, callback);
  }
  static padding(value) {
    getUINativeModule().calendarPicker.setCalendarPickerPadding(true, value);
}

  static border(value) {
    getUINativeModule().calendarPicker.setCalendarPickerBorder(true, value);
  }

  static height(value) {
    getUINativeModule().calendarPicker.setCalendarPickerHeight(true, value);
  }

  static borderRadius(value) {
    getUINativeModule().calendarPicker.setCalendarPickerBorderRadius(true, value);
  }

  static borderColor(value) {
    getUINativeModule().calendarPicker.setCalendarPickerBorderColor(true, value);
  }

  static markToday(value) {
    getUINativeModule().calendarPicker.setCalendarPickerMarkToday(true, value);
  }

  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkCalendarPickerComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CalendarPickerModifier(nativePtr, classType);
    });
  }

  static contentModifier(modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return createComponent(nativeNode, 'calendarPicker');
    });
    component.setContentModifier(modifier);
  }

  static onKeyEvent(value) {
    __Common__.onKeyEvent(value);
  }
  static onDeleteEvent(value) {
    __Common__.onDeleteEvent(value);
  }
  static onAttach(value) {
    __Common__.onAttach(value);
  }
  static onAppear(value) {
    __Common__.onAppear(value);
  }
  static onDetach(value) {
    __Common__.onAttach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }

  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onHover(value) {
    __Common__.onHover(value);
  }
}

class JSCalendarPickerDialog extends JSViewAbstract {
  static show(options) {
    getUINativeModule().calendarPickerDialog.show(options);
  }
}

function exportDialogView() {
  globalThis.CalendarPickerDialog = JSCalendarPickerDialog;
}

function createComponent(nativePtr, classType) {
  return new ArkCalendarPickerComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkCalendarPickerComponent = ArkCalendarPickerComponent;
}

function exportView() {
  globalThis.CalendarPicker = JSCalendarPicker;
}

export default { ArkCalendarPickerComponent, createComponent, exportComponent, exportView, exportDialogView };
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
const arkUINativeModule = globalThis.getArkUINativeModule();
function getUINativeModule() {
  if (arkUINativeModule) {
    return arkUINativeModule;
  }
  return arkUINativeModule;
}
const UI_STATE_NORMAL = 0;
const UI_STATE_PRESSED = 1;
const UI_STATE_FOCUSED = 1 << 1;
const UI_STATE_DISABLED = 1 << 2;
const UI_STATE_SELECTED = 1 << 3;
function applyUIAttributes(modifier, nativeNode, component) {
  let state = 0;
  if (modifier.applyPressedAttribute !== undefined) {
    state |= UI_STATE_PRESSED;
  }
  if (modifier.applyFocusedAttribute !== undefined) {
    state |= UI_STATE_FOCUSED;
  }
  if (modifier.applyDisabledAttribute !== undefined) {
    state |= UI_STATE_DISABLED;
  }
  if (modifier.applySelectedAttribute !== undefined) {
    state |= UI_STATE_SELECTED;
  }
  getUINativeModule().setSupportedUIState(nativeNode, state);
  const currentUIState = getUINativeModule().getUIState(nativeNode);
  if (modifier.applyNormalAttribute !== undefined) {
    modifier.applyNormalAttribute(component);
  }
  if ((currentUIState & UI_STATE_PRESSED) && (modifier.applyPressedAttribute !== undefined)) {
    modifier.applyPressedAttribute(component);
  }
  if ((currentUIState & UI_STATE_FOCUSED) && (modifier.applyFocusedAttribute !== undefined)) {
    modifier.applyFocusedAttribute(component);
  }
  if ((currentUIState & UI_STATE_DISABLED) && (modifier.applyDisabledAttribute !== undefined)) {
    modifier.applyDisabledAttribute(component);
  }
  if ((currentUIState & UI_STATE_SELECTED) && (modifier.applySelectedAttribute !== undefined)) {
    modifier.applySelectedAttribute(component);
  }
}
function isResource(variable) {
  return (variable === null || variable === void 0 ? void 0 : variable.bundleName) !== undefined;
}
function isResourceEqual(stageValue, value) {
  return (stageValue.bundleName === value.bundleName) &&
    (stageValue.moduleName === value.moduleName) &&
    (stageValue.id === value.id) &&
    (stageValue.params === value.params) &&
    (stageValue.type === value.type);
}
function isBaseOrResourceEqual(stageValue, value) {
  if (isResource(stageValue) && isResource(value)) {
    return isResourceEqual(stageValue, value);
  }
  else if (!isResource(stageValue) && !isResource(value)) {
    return (stageValue === value);
  }
  return false;
}
const SAFE_AREA_TYPE_NONE = 0;
const SAFE_AREA_TYPE_SYSTEM = 1;
const SAFE_AREA_TYPE_CUTOUT = 2;
const SAFE_AREA_TYPE_KEYBOARD = 4;
const SAFE_AREA_TYPE_ALL = 7;
const SAFE_AREA_EDGE_NONE = 0;
const SAFE_AREA_EDGE_TOP = 1;
const SAFE_AREA_EDGE_BOTTOM = 2;
const SAFE_AREA_EDGE_START = 4;
const SAFE_AREA_EDGE_END = 8;
const SAFE_AREA_EDGE_ALL = 15;
const SAFE_AREA_TYPE_LIMIT = 3;
const SAFE_AREA_EDGE_LIMIT = 4;
const DIRECTION_RANGE = 3;
class Modifier {
  constructor(value) {
    this.stageValue = value;
  }
  applyStage(node) {
    if (this.stageValue === this.value) {
      if (this.value === undefined) {
        this.applyPeer(node, true);
      }
      delete this.stageValue;
      return;
    }
    if (typeof this.stageValue === 'object' && typeof this.value === 'object') {
      if (this.stageValue.isEqual(this.value)) {
        delete this.stageValue;
        return;
      }
    }
    this.value = this.stageValue;
    delete this.stageValue;
    this.applyPeer(node, this.value === undefined);
    return (this.value === undefined);
  }
  applyPeer(node, reset) { }
}
class ModifierWithKey {
  constructor(value) {
    this.stageValue = value;
  }
  applyStage(node) {
    if (this.stageValue === undefined || this.stageValue === null) {
      this.value = this.stageValue;
      this.applyPeer(node, true);
      return true;
    }
    const stageTypeInfo = typeof this.stageValue;
    const valueTypeInfo = typeof this.value;
    let different = false;
    if (stageTypeInfo !== valueTypeInfo) {
      different = true;
    }
    else if (stageTypeInfo === 'number' || stageTypeInfo === 'string' || stageTypeInfo === 'boolean') {
      different = (this.stageValue !== this.value);
    }
    else {
      different = this.checkObjectDiff();
    }
    if (different) {
      this.value = this.stageValue;
      this.applyPeer(node, false);
    }
    this.stageValue = undefined;
    return false;
  }
  applyPeer(node, reset) { }
  checkObjectDiff() {
    return true;
  }
}
class BackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBackgroundColor(node);
    }
    else {
      getUINativeModule().common.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BackgroundColorModifier.identity = Symbol('backgroundColor');
class WidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetWidth(node);
    }
    else {
      getUINativeModule().common.setWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
WidthModifier.identity = Symbol('width');
class BorderWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBorderWidth(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().common.setBorderWidth(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().common.setBorderWidth(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
BorderWidthModifier.identity = Symbol('borderWidth');
class HeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetHeight(node);
    }
    else {
      getUINativeModule().common.setHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
HeightModifier.identity = Symbol('height');
class BorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().common.setBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().common.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
BorderRadiusModifier.identity = Symbol('borderRadius');
class PositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPosition(node);
    }
    else {
      getUINativeModule().common.setPosition(node, this.value.x, this.value.y);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}
PositionModifier.identity = Symbol('position');
class BorderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBorderColor(node);
    }
    else {
      const valueType = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        getUINativeModule().common.setBorderColor(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().common.setBorderColor(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
BorderColorModifier.identity = Symbol('borderColor');
class TransformModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetTransform(node);
    }
    else {
      getUINativeModule().common.setTransform(node, this.value.matrix4x4);
    }
  }
  checkObjectDiff() {
    return !deepCompareArrays(this.stageValue.matrix4x4, this.value.matrix4x4);
  }
}
TransformModifier.identity = Symbol('transform');
class BorderStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d;
    if (reset) {
      getUINativeModule().common.resetBorderStyle(node);
    }
    else {
      let type;
      let style;
      let top;
      let right;
      let bottom;
      let left;
      if (isNumber(this.value)) {
        style = this.value;
        type = true;
      }
      else if (isObject(this.value)) {
        top = (_a = this.value) === null || _a === void 0 ? void 0 : _a.top;
        right = (_b = this.value) === null || _b === void 0 ? void 0 : _b.right;
        bottom = (_c = this.value) === null || _c === void 0 ? void 0 : _c.bottom;
        left = (_d = this.value) === null || _d === void 0 ? void 0 : _d.left;
        type = true;
      }
      if (type === true) {
        getUINativeModule().common.setBorderStyle(node, type, style, top, right, bottom, left);
      }
      else {
        getUINativeModule().common.resetBorderStyle(node);
      }
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    return !(((_a = this.value) === null || _a === void 0 ? void 0 : _a.top) === ((_b = this.stageValue) === null || _b === void 0 ? void 0 : _b.top) &&
      ((_c = this.value) === null || _c === void 0 ? void 0 : _c.right) === ((_d = this.stageValue) === null || _d === void 0 ? void 0 : _d.right) &&
      ((_e = this.value) === null || _e === void 0 ? void 0 : _e.bottom) === ((_f = this.stageValue) === null || _f === void 0 ? void 0 : _f.bottom) &&
      ((_g = this.value) === null || _g === void 0 ? void 0 : _g.left) === ((_h = this.stageValue) === null || _h === void 0 ? void 0 : _h.left));
  }
}
BorderStyleModifier.identity = Symbol('borderStyle');
class ShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetShadow(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setShadow(node, this.value, undefined, undefined, undefined, undefined, undefined, undefined);
      }
      else {
        getUINativeModule().common.setShadow(node, undefined, this.value.radius, 
          this.value.type, this.value.color, 
          this.value.offsetX, this.value.offsetY, this.value.fill);
      }
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.radius === this.value.radius &&
      this.stageValue.type === this.value.type &&
      this.stageValue.color === this.value.color &&
      this.stageValue.offsetX === this.value.offsetX &&
      this.stageValue.offsetY === this.value.offsetY &&
      this.stageValue.fill === this.value.fill);
  }
}
ShadowModifier.identity = Symbol('shadow');
class HitTestBehaviorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetHitTestBehavior(node);
    }
    else {
      getUINativeModule().common.setHitTestBehavior(node, this.value);
    }
  }
}
HitTestBehaviorModifier.identity = Symbol('hitTestBehavior');
class ZIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetZIndex(node);
    }
    else {
      getUINativeModule().common.setZIndex(node, this.value);
    }
  }
}
ZIndexModifier.identity = Symbol('zIndex');
class OpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetOpacity(node);
    }
    else {
      getUINativeModule().common.setOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
OpacityModifier.identity = Symbol('opacity');
class AlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAlign(node);
    }
    else {
      getUINativeModule().common.setAlign(node, this.value);
    }
  }
}
AlignModifier.identity = Symbol('align');
class BackdropBlurModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBackdropBlur(node);
    }
    else {
      getUINativeModule().common.setBackdropBlur(node, this.value);
    }
  }
}
BackdropBlurModifier.identity = Symbol('backdropBlur');
class HueRotateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetHueRotate(node);
    }
    else {
      getUINativeModule().common.setHueRotate(node, this.value);
    }
  }
}
HueRotateModifier.identity = Symbol('hueRotate');
class InvertModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetInvert(node);
    }
    else {
      getUINativeModule().common.setInvert(node, this.value);
    }
  }
}
InvertModifier.identity = Symbol('invert');
class SepiaModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSepia(node);
    }
    else {
      getUINativeModule().common.setSepia(node, this.value);
    }
  }
}
SepiaModifier.identity = Symbol('sepia');
class SaturateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSaturate(node);
    }
    else {
      getUINativeModule().common.setSaturate(node, this.value);
    }
  }
}
SaturateModifier.identity = Symbol('saturate');
class ColorBlendModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetColorBlend(node);
    }
    else {
      getUINativeModule().common.setColorBlend(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ColorBlendModifier.identity = Symbol('colorBlend');
class GrayscaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetGrayscale(node);
    }
    else {
      getUINativeModule().common.setGrayscale(node, this.value);
    }
  }
}
GrayscaleModifier.identity = Symbol('grayscale');
class ContrastModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetContrast(node);
    }
    else {
      getUINativeModule().common.setContrast(node, this.value);
    }
  }
}
ContrastModifier.identity = Symbol('contrast');
class BrightnessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBrightness(node);
    }
    else {
      getUINativeModule().common.setBrightness(node, this.value);
    }
  }
}
BrightnessModifier.identity = Symbol('brightness');
class BlurModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBlur(node);
    }
    else {
      getUINativeModule().common.setBlur(node, this.value);
    }
  }
}
BlurModifier.identity = Symbol('blur');
class LinearGradientModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetLinearGradient(node);
    }
    else {
      getUINativeModule().common.setLinearGradient(node, this.value.angle, this.value.direction, this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.angle === this.value.angle) &&
      (this.stageValue.direction === this.value.direction) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}
LinearGradientModifier.identity = Symbol('linearGradient');
class RadialGradientModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetRadialGradient(node);
    }
    else {
      getUINativeModule().common.setRadialGradient(node, this.value.center, this.value.radius, this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.center === this.value.center) &&
      (this.stageValue.radius === this.value.radius) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}
RadialGradientModifier.identity = Symbol('radialGradient');
class SweepGradientModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSweepGradient(node);
    }
    else {
      getUINativeModule().common.setSweepGradient(node, this.value.center, this.value.start, 
        this.value.end, this.value.rotation, this.value.colors, this.value.repeating);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.center === this.value.center) &&
      (this.stageValue.start === this.value.start) &&
      (this.stageValue.end === this.value.end) &&
      (this.stageValue.rotation === this.value.rotation) &&
      (this.stageValue.colors === this.value.colors) &&
      (this.stageValue.repeating === this.value.repeating));
  }
}
SweepGradientModifier.identity = Symbol('sweepGradient');
class OverlayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetOverlay(node);
    }
    else {
      getUINativeModule().common.setOverlay(node, this.value.value, this.value.align,
        this.value.offsetX, this.value.offsetY, this.value.hasOptions, this.value.hasOffset);
    }
  }
  checkObjectDiff() {
    if (isUndefined(this.value)) {
      return !isUndefined(this.stageValue);
    }
    return this.value.checkObjectDiff(this.stageValue);
  }
}
OverlayModifier.identity = Symbol('overlay');
class BorderImageModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBorderImage(node);
    }
    else {
      let sliceTop;
      let sliceRight;
      let sliceBottom;
      let sliceLeft;
      let repeat;
      let source;
      let sourceAngle;
      let sourceDirection;
      let sourceColors;
      let sourceRepeating;
      let widthTop;
      let widthRight;
      let widthBottom;
      let widthLeft;
      let outsetTop;
      let outsetRight;
      let outsetBottom;
      let outsetLeft;
      let fill;
      if (!isUndefined(this.value.slice)) {
        if (isLengthType(this.value.slice) || isResource(this.value.slice)) {
          let tmpSlice = this.value.slice;
          sliceTop = tmpSlice;
          sliceRight = tmpSlice;
          sliceBottom = tmpSlice;
          sliceLeft = tmpSlice;
        }
        else {
          let tmpSlice = this.value.slice;
          sliceTop = tmpSlice.top;
          sliceRight = tmpSlice.right;
          sliceBottom = tmpSlice.bottom;
          sliceLeft = tmpSlice.left;
        }
      }
      repeat = this.value.repeat;
      if (!isUndefined(this.value.source)) {
        if (isString(this.value.source) || isResource(this.value.source)) {
          source = this.value.source;
        }
        else {
          let tmpSource = this.value.source;
          sourceAngle = tmpSource.angle;
          sourceDirection = tmpSource.direction;
          sourceColors = tmpSource.colors;
          sourceRepeating = tmpSource.repeating;
        }
      }
      if (!isUndefined(this.value.width)) {
        if (isLengthType(this.value.width) || isResource(this.value.width)) {
          let tmpWidth = this.value.width;
          widthTop = tmpWidth;
          widthRight = tmpWidth;
          widthBottom = tmpWidth;
          widthLeft = tmpWidth;
        }
        else {
          let tmpWidth = this.value.width;
          widthTop = tmpWidth.top;
          widthRight = tmpWidth.right;
          widthBottom = tmpWidth.bottom;
          widthLeft = tmpWidth.left;
        }
      }
      if (!isUndefined(this.value.outset)) {
        if (isLengthType(this.value.outset) || isResource(this.value.outset)) {
          let tmpOutset = this.value.outset;
          outsetTop = tmpOutset;
          outsetRight = tmpOutset;
          outsetBottom = tmpOutset;
          outsetLeft = tmpOutset;
        }
        else {
          let tmpOutset = this.value.outset;
          outsetTop = tmpOutset.top;
          outsetRight = tmpOutset.right;
          outsetBottom = tmpOutset.bottom;
          outsetLeft = tmpOutset.left;
        }
      }
      fill = this.value.fill;
      getUINativeModule().common.setBorderImage(node, sliceTop, sliceRight, sliceBottom,
        sliceLeft, repeat, source, sourceAngle, sourceDirection, sourceColors, sourceRepeating,
        widthTop, widthRight, widthBottom, widthLeft, outsetTop, outsetRight, outsetBottom,
        outsetLeft, fill);
    }
  }
}
BorderImageModifier.identity = Symbol('borderImage');
class BorderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBorder(node);
    }
    else {
      getUINativeModule().common.setBorder(node, this.value.arkWidth.left,
        this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom,
        this.value.arkColor.leftColor, this.value.arkColor.rightColor,
        this.value.arkColor.topColor, this.value.arkColor.bottomColor,
        this.value.arkRadius.topLeft, this.value.arkRadius.topRight,
        this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight,
        this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom,
        this.value.arkStyle.left);
    }
  }
  checkObjectDiff() {
    return this.value.checkObjectDiff(this.stageValue);
  }
}
BorderModifier.identity = Symbol('border');
class ForegroundBlurStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetForegroundBlurStyle(node);
    }
    else {
      getUINativeModule().common.setForegroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.blurStyle === this.value.blurStyle &&
      this.stageValue.colorMode === this.value.colorMode &&
      this.stageValue.adaptiveColor === this.value.adaptiveColor &&
      this.stageValue.scale === this.value.scale);
  }
}
ForegroundBlurStyleModifier.identity = Symbol('foregroundBlurStyle');
class BackgroundImagePositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().common.resetBackgroundImagePosition(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setBackgroundImagePosition(node, this.value, undefined, undefined);
      }
      else {
        getUINativeModule().common.setBackgroundImagePosition(node, undefined,
          (_a = this.value) === null || _a === void 0 ? void 0 : _a.x,
          (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
      }
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d;
    return !(((_a = this.value) === null || _a === void 0 ? void 0 : _a.x) === ((_b = this.stageValue) === null || _b === void 0 ? void 0 : _b.x) &&
      ((_c = this.value) === null || _c === void 0 ? void 0 : _c.y) === ((_d = this.stageValue) === null || _d === void 0 ? void 0 : _d.y));
  }
}
BackgroundImagePositionModifier.identity = Symbol('backgroundImagePosition');
class LinearGradientBlurModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetLinearGradientBlur(node);
    }
    else {
      getUINativeModule().common.setLinearGradientBlur(node, this.value.blurRadius, this.value.fractionStops, this.value.direction);
    }
  }
  checkObjectDiff() {
    return !this.value.isEqual(this.stageValue);
  }
}
LinearGradientBlurModifier.identity = Symbol('linearGradientBlur');
class BackgroundImageModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBackgroundImage(node);
    }
    else {
      getUINativeModule().common.setBackgroundImage(node, this.value.src, this.value.repeat);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.src === this.value.src &&
      this.stageValue.repeat === this.value.repeat);
  }
}
BackgroundImageModifier.identity = Symbol('backgroundImage');
class BackgroundBlurStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetBackgroundBlurStyle(node);
    }
    else {
      getUINativeModule().common.setBackgroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
    }
  }
}
BackgroundBlurStyleModifier.identity = Symbol('backgroundBlurStyle');
class BackgroundImageSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().common.resetBackgroundImageSize(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().common.setBackgroundImageSize(node, this.value, undefined, undefined);
      }
      else {
        getUINativeModule().common.setBackgroundImageSize(node, undefined,
          (_a = this.value) === null || _a === void 0 ? void 0 : _a.width,
          (_b = this.value) === null || _b === void 0 ? void 0 : _b.height);
      }
    }
  }
  checkObjectDiff() {
    return !(this.value.width === this.stageValue.width &&
      this.value.height === this.stageValue.height);
  }
}
BackgroundImageSizeModifier.identity = Symbol('backgroundImageSize');
class TranslateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetTranslate(node);
    }
    else {
      getUINativeModule().common.setTranslate(node, this.value.x, this.value.y, this.value.z);
    }
  }
  checkObjectDiff() {
    return !(this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z);
  }
}
TranslateModifier.identity = Symbol('translate');
class ScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetScale(node);
    }
    else {
      getUINativeModule().common.setScale(node, this.value.x, this.value.y, this.value.z, this.value.centerX, this.value.centerY);
    }
  }
  checkObjectDiff() {
    return !(this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z &&
      this.value.centerX === this.stageValue.centerX &&
      this.value.centerY === this.stageValue.centerY);
  }
}
ScaleModifier.identity = Symbol('scale');
class RotateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetRotate(node);
    }
    else {
      getUINativeModule().common.setRotate(node, this.value.x, this.value.y,
        this.value.z, this.value.angle, this.value.centerX, this.value.centerY,
        this.value.centerY, this.value.perspective);
    }
  }
  checkObjectDiff() {
    return !(this.value.x === this.stageValue.x &&
      this.value.y === this.stageValue.y &&
      this.value.z === this.stageValue.z &&
      this.value.angle === this.stageValue.angle &&
      this.value.centerX === this.stageValue.centerX &&
      this.value.centerY === this.stageValue.centerY &&
      this.value.centerZ === this.stageValue.centerZ &&
      this.value.perspective === this.stageValue.perspective);
  }
}
RotateModifier.identity = Symbol('rotate');
class GeometryTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetGeometryTransition(node);
    }
    else {
      getUINativeModule().common.setGeometryTransition(node, this.value);
    }
  }
}
GeometryTransitionModifier.identity = Symbol('geometryTransition');
class ClipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetClip(node);
    }
    else {
      getUINativeModule().common.setClip(node, this.value);
    }
  }
  checkObjectDiff() {
    return false;
  }
}
ClipModifier.identity = Symbol('clip');
class MaskModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetMask(node);
    }
    else {
      getUINativeModule().common.setMask(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
MaskModifier.identity = Symbol('mask');
class PixelStretchEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPixelStretchEffect(node);
    }
    else {
      getUINativeModule().common.setPixelStretchEffect(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.left === this.value.left &&
      this.stageValue.right === this.value.right &&
      this.stageValue.top === this.value.top &&
      this.stageValue.bottom === this.value.bottom);
  }
}
PixelStretchEffectModifier.identity = Symbol('pixelStretchEffect');
class LightUpEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetLightUpEffect(node);
    }
    else {
      getUINativeModule().common.setLightUpEffect(node, this.value);
    }
  }
}
LightUpEffectModifier.identity = Symbol('lightUpEffect');
class SphericalEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSphericalEffect(node);
    }
    else {
      getUINativeModule().common.setSphericalEffect(node, this.value);
    }
  }
}
SphericalEffectModifier.identity = Symbol('sphericalEffect');
class RenderGroupModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetRenderGroup(node);
    }
    else {
      getUINativeModule().common.setRenderGroup(node, this.value);
    }
  }
}
RenderGroupModifier.identity = Symbol('renderGroup');
class RenderFitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetRenderFit(node);
    }
    else {
      getUINativeModule().common.setRenderFit(node, this.value);
    }
  }
}
RenderFitModifier.identity = Symbol('renderFit');
class UseEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetUseEffect(node);
    }
    else {
      getUINativeModule().common.setUseEffect(node, this.value);
    }
  }
}
UseEffectModifier.identity = Symbol('useEffect');
class ForegroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetForegroundColor(node);
    }
    else {
      getUINativeModule().common.setForegroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ForegroundColorModifier.identity = Symbol('foregroundColor');
class MotionPathModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetMotionPath(node);
    }
    else {
      let path;
      let rotatable;
      let from;
      let to;
      if (isString(this.value.path)) {
        path = this.value.path;
      }
      if (isBoolean(this.value.rotatable)) {
        rotatable = this.value.rotatable;
      }
      if (isNumber(this.value.from) && isNumber(this.value.to)) {
        from = this.value.from;
        to = this.value.to;
      }
      getUINativeModule().common.setMotionPath(node, path, from, to, rotatable);
    }
  }
  checkObjectDiff() {
    return !(this.value.path === this.stageValue.path &&
      this.value.from === this.stageValue.from &&
      this.value.to === this.stageValue.to &&
      this.value.rotatable === this.stageValue.rotatable);
  }
}
MotionPathModifier.identity = Symbol('motionPath');
class GroupDefaultFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetGroupDefaultFocus(node);
    }
    else {
      getUINativeModule().common.setGroupDefaultFocus(node, this.value);
    }
  }
}
GroupDefaultFocusModifier.identity = Symbol('groupDefaultFocus');
class FocusOnTouchModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetFocusOnTouch(node);
    }
    else {
      getUINativeModule().common.setFocusOnTouch(node, this.value);
    }
  }
}
FocusOnTouchModifier.identity = Symbol('focusOnTouch');
class OffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().common.resetOffset(node);
    }
    else {
      getUINativeModule().common.setOffset(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}
OffsetModifier.identity = Symbol('offset');
class MarkAnchorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().common.resetMarkAnchor(node);
    }
    else {
      getUINativeModule().common.setMarkAnchor(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}
MarkAnchorModifier.identity = Symbol('markAnchor');
class DefaultFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetDefaultFocus(node);
    }
    else {
      getUINativeModule().common.setDefaultFocus(node, this.value);
    }
  }
}
DefaultFocusModifier.identity = Symbol('defaultFocus');
class FocusableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetFocusable(node);
    }
    else {
      getUINativeModule().common.setFocusable(node, this.value);
    }
  }
}
FocusableModifier.identity = Symbol('focusable');
class TouchableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetTouchable(node);
    }
    else {
      getUINativeModule().common.setTouchable(node, this.value);
    }
  }
}
TouchableModifier.identity = Symbol('touchable');
class MarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetMargin(node);
    }
    else {
      getUINativeModule().common.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
MarginModifier.identity = Symbol('margin');
class PaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPadding(node);
    }
    else {
      getUINativeModule().common.setPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom) ||
      !isBaseOrResourceEqual(this.stageValue.left, this.value.left);
  }
}
PaddingModifier.identity = Symbol('padding');
class VisibilityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetVisibility(node);
    }
    else {
      getUINativeModule().common.setVisibility(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
VisibilityModifier.identity = Symbol('visibility');
class AccessibilityTextModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAccessibilityText(node);
    }
    else {
      getUINativeModule().common.setAccessibilityText(node, this.value);
    }
  }
}
AccessibilityTextModifier.identity = Symbol('accessibilityText');
class AllowDropModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAllowDrop(node);
    }
    else {
      getUINativeModule().common.setAllowDrop(node, this.value);
    }
  }
  checkObjectDiff() {
    return !(Array.isArray(this.value) && Array.isArray(this.stageValue) &&
      this.value.length === this.stageValue.length &&
      this.value.every((value, index) => value === this.stageValue[index]));
  }
}
AllowDropModifier.identity = Symbol('allowDrop');
class AccessibilityLevelModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAccessibilityLevel(node);
    }
    else {
      getUINativeModule().common.setAccessibilityLevel(node, this.value);
    }
  }
}
AccessibilityLevelModifier.identity = Symbol('accessibilityLevel');
class AccessibilityDescriptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAccessibilityDescription(node);
    }
    else {
      getUINativeModule().common.setAccessibilityDescription(node, this.value);
    }
  }
}
AccessibilityDescriptionModifier.identity = Symbol('accessibilityDescription');
class DirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetDirection(node);
    }
    else {
      getUINativeModule().common.setDirection(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DirectionModifier.identity = Symbol('direction');
class AlignRulesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAlignRules(node);
    }
    else {
      getUINativeModule().common.setAlignRules(node, this.value.left, this.value.middle,
        this.value.right, this.value.top, this.value.center, this.value.bottom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.left, this.value.left) ||
      !isBaseOrResourceEqual(this.stageValue.middle, this.value.middle) ||
      !isBaseOrResourceEqual(this.stageValue.right, this.value.right) ||
      !isBaseOrResourceEqual(this.stageValue.top, this.value.top) ||
      !isBaseOrResourceEqual(this.stageValue.center, this.value.center) ||
      !isBaseOrResourceEqual(this.stageValue.bottom, this.value.bottom);
  }
}
AlignRulesModifier.identity = Symbol('alignRules');
class ExpandSafeAreaModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetExpandSafeArea(node);
    }
    else {
      getUINativeModule().common.setExpandSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}
ExpandSafeAreaModifier.identity = Symbol('expandSafeArea');
class GridSpanModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetGridSpan(node);
    }
    else {
      getUINativeModule().common.setGridSpan(node, this.value);
    }
  }
}
GridSpanModifier.identity = Symbol('gridSpan');
class GridOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetGridOffset(node);
    }
    else {
      getUINativeModule().common.setGridOffset(node, this.value);
    }
  }
}
GridOffsetModifier.identity = Symbol('gridOffset');
class AlignSelfModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAlignSelf(node);
    }
    else {
      getUINativeModule().common.setAlignSelf(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
AlignSelfModifier.identity = Symbol('alignSelf');
class SizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSize(node);
    }
    else {
      getUINativeModule().common.setSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
SizeModifier.identity = Symbol('size');
class DisplayPriorityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetDisplayPriority(node);
    }
    else {
      getUINativeModule().common.setDisplayPriority(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DisplayPriorityModifier.identity = Symbol('displayPriority');
class IdModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetId(node);
    }
    else {
      getUINativeModule().common.setId(node, this.value);
    }
  }
}
IdModifier.identity = Symbol('id');
class KeyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetKey(node);
    }
    else {
      getUINativeModule().common.setKey(node, this.value);
    }
  }
}
KeyModifier.identity = Symbol('key');
class RestoreIdModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetRestoreId(node);
    }
    else {
      getUINativeModule().common.setRestoreId(node, this.value);
    }
  }
}
RestoreIdModifier.identity = Symbol('restoreId');
class TabIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetTabIndex(node);
    }
    else {
      getUINativeModule().common.setTabIndex(node, this.value);
    }
  }
}
TabIndexModifier.identity = Symbol('tabIndex');
class ObscuredModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || (!Array.isArray(this.value))) {
      getUINativeModule().common.resetObscured(node);
    }
    else {
      getUINativeModule().common.setObscured(node, this.value);
    }
  }
  checkObjectDiff() {
    return !(Array.isArray(this.value) && Array.isArray(this.stageValue) &&
      this.value.length === this.stageValue.length &&
      this.value.every((value, index) => value === this.stageValue[index]));
  }
}
ObscuredModifier.identity = Symbol('obscured');
class MouseResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().common.resetMouseResponseRegion(node);
    }
    else {
      let responseRegion = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push((_a = this.value[i].x) !== null && _a !== void 0 ? _a : 'PLACEHOLDER');
          responseRegion.push((_b = this.value[i].y) !== null && _b !== void 0 ? _b : 'PLACEHOLDER');
          responseRegion.push((_c = this.value[i].width) !== null && _c !== void 0 ? _c : 'PLACEHOLDER');
          responseRegion.push((_d = this.value[i].height) !== null && _d !== void 0 ? _d : 'PLACEHOLDER');
        }
      }
      else {
        responseRegion.push((_e = this.value.x) !== null && _e !== void 0 ? _e : 'PLACEHOLDER');
        responseRegion.push((_f = this.value.y) !== null && _f !== void 0 ? _f : 'PLACEHOLDER');
        responseRegion.push((_g = this.value.width) !== null && _g !== void 0 ? _g : 'PLACEHOLDER');
        responseRegion.push((_h = this.value.height) !== null && _h !== void 0 ? _h : 'PLACEHOLDER');
      }
      getUINativeModule().common.setMouseResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff() {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      }
      else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height))) {
            return true;
          }
        }
        return false;
      }
    }
    else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)));
    }
    else {
      return false;
    }
  }
}
MouseResponseRegionModifier.identity = Symbol('mouseResponseRegion');
class ResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().common.resetResponseRegion(node);
    }
    else {
      let responseRegion = [];
      if (Array.isArray(this.value)) {
        for (let i = 0; i < this.value.length; i++) {
          responseRegion.push((_a = this.value[i].x) !== null && _a !== void 0 ? _a : 'PLACEHOLDER');
          responseRegion.push((_b = this.value[i].y) !== null && _b !== void 0 ? _b : 'PLACEHOLDER');
          responseRegion.push((_c = this.value[i].width) !== null && _c !== void 0 ? _c : 'PLACEHOLDER');
          responseRegion.push((_d = this.value[i].height) !== null && _d !== void 0 ? _d : 'PLACEHOLDER');
        }
      }
      else {
        responseRegion.push((_e = this.value.x) !== null && _e !== void 0 ? _e : 'PLACEHOLDER');
        responseRegion.push((_f = this.value.y) !== null && _f !== void 0 ? _f : 'PLACEHOLDER');
        responseRegion.push((_g = this.value.width) !== null && _g !== void 0 ? _g : 'PLACEHOLDER');
        responseRegion.push((_h = this.value.height) !== null && _h !== void 0 ? _h : 'PLACEHOLDER');
      }
      getUINativeModule().common.setResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff() {
    if (Array.isArray(this.value) && Array.isArray(this.stageValue)) {
      if (this.value.length !== this.stageValue.length) {
        return true;
      }
      else {
        for (let i = 0; i < this.value.length; i++) {
          if (!(isBaseOrResourceEqual(this.stageValue[i].x, this.value[i].x) &&
            isBaseOrResourceEqual(this.stageValue[i].y, this.value[i].y) &&
            isBaseOrResourceEqual(this.stageValue[i].width, this.value[i].width) &&
            isBaseOrResourceEqual(this.stageValue[i].height, this.value[i].height))) {
            return true;
          }
        }
        return false;
      }
    }
    else if (!Array.isArray(this.value) && !Array.isArray(this.stageValue)) {
      return (!(isBaseOrResourceEqual(this.stageValue.x, this.value.x) &&
        isBaseOrResourceEqual(this.stageValue.y, this.value.y) &&
        isBaseOrResourceEqual(this.stageValue.width, this.value.width) &&
        isBaseOrResourceEqual(this.stageValue.height, this.value.height)));
    }
    else {
      return false;
    }
  }
}
ResponseRegionModifier.identity = Symbol('responseRegion');
class FlexGrowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetFlexGrow(node);
    }
    else {
      getUINativeModule().common.setFlexGrow(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
FlexGrowModifier.identity = Symbol('flexGrow');
class FlexShrinkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetFlexShrink(node);
    }
    else {
      getUINativeModule().common.setFlexShrink(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
FlexShrinkModifier.identity = Symbol('flexShrink');
class AspectRatioModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAspectRatio(node);
    }
    else {
      getUINativeModule().common.setAspectRatio(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
AspectRatioModifier.identity = Symbol('aspectRatio');
class ConstraintSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetConstraintSize(node);
    }
    else {
      getUINativeModule().common.setConstraintSize(node, this.value.minWidth, this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.minWidth, this.value.minWidth) ||
      !isBaseOrResourceEqual(this.stageValue.maxWidth, this.value.maxWidth) ||
      !isBaseOrResourceEqual(this.stageValue.minHeight, this.value.minHeight) ||
      !isBaseOrResourceEqual(this.stageValue.maxHeight, this.value.maxHeight);
  }
}
ConstraintSizeModifier.identity = Symbol('constraintSize');
class FlexBasisModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetFlexBasis(node);
    }
    else {
      getUINativeModule().common.setFlexBasis(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
FlexBasisModifier.identity = Symbol('flexBasis');
class LayoutWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetLayoutWeight(node);
    }
    else {
      getUINativeModule().common.setLayoutWeight(node, this.value);
    }
  }
}
LayoutWeightModifier.identity = Symbol('layoutWeight');
class EnabledModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetEnabled(node);
    }
    else {
      getUINativeModule().common.setEnabled(node, this.value);
    }
  }
}
EnabledModifier.identity = Symbol('enabled');
class DraggableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetDraggable(node);
    }
    else {
      getUINativeModule().common.setDraggable(node, this.value);
    }
  }
}
DraggableModifier.identity = Symbol('draggable');
class AccessibilityGroupModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetAccessibilityGroup(node);
    }
    else {
      getUINativeModule().common.setAccessibilityGroup(node, this.value);
    }
  }
}
AccessibilityGroupModifier.identity = Symbol('accessibilityGroup');
class HoverEffectModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetHoverEffect(node);
    }
    else {
      getUINativeModule().common.setHoverEffect(node, this.value);
    }
  }
}
HoverEffectModifier.identity = Symbol('hoverEffect');
class ClickEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().common.resetClickEffect(node);
    }
    else {
      getUINativeModule().common.setClickEffect(node, this.value.level, this.value.scale);
    }
  }
  checkObjectDiff() {
    return !((this.value.level === this.stageValue.level) && (this.value.scale === this.stageValue.scale));
  }
}
ClickEffectModifier.identity = Symbol('clickEffect');
class KeyBoardShortCutModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetKeyBoardShortCut(node);
    }
    else {
      getUINativeModule().common.setKeyBoardShortCut(node, this.value.value, this.value.keys);
    }
  }
  checkObjectDiff() {
    return !this.value.isEqual(this.stageValue);
  }
}
KeyBoardShortCutModifier.identity = Symbol('keyboardShortcut');
class TransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetTransition(node);
    }
    else {
      getUINativeModule().common.setTransition(node, this.value);
    }
  }
}
TransitionModifier.identity = Symbol('transition');
class SharedTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetSharedTransition(node);
    }
    else {
      getUINativeModule().common.setSharedTransition(node, this.value.id, this.value.options);
    }
  }
}
SharedTransitionModifier.identity = Symbol('sharedTransition');
const JSCallbackInfoType = { STRING: 0, NUMBER: 1, OBJECT: 2, BOOLEAN: 3, FUNCTION: 4 };
const isString = (val) => typeof val === 'string';
const isNumber = (val) => typeof val === 'number';
const isBigint = (val) => typeof val === 'bigint';
const isBoolean = (val) => typeof val === 'boolean';
const isSymbol = (val) => typeof val === 'symbol';
const isUndefined = (val) => typeof val === 'undefined';
const isObject = (val) => typeof val === 'object';
const isFunction = (val) => typeof val === 'function';
const isLengthType = (val) => typeof val === 'string' || typeof val === 'number';
function checkJsCallbackInfo(value, checklist) {
  let typeVerified = false;
  checklist.forEach(function (infoType) {
    switch (infoType) {
      case JSCallbackInfoType.STRING:
        if (isString(value)) {
          typeVerified = true;
        }
        break;
      case JSCallbackInfoType.NUMBER:
        if (isNumber(value)) {
          typeVerified = true;
        }
        break;
      case JSCallbackInfoType.OBJECT:
        if (isObject(value)) {
          typeVerified = true;
        }
        break;
      case JSCallbackInfoType.FUNCTION:
        if (isFunction(value)) {
          typeVerified = true;
        }
        break;
      default:
        break;
    }
  });
  return typeVerified || checklist.length === 0;
}
function modifier(modifiers, modifierClass, value) {
  const identity = modifierClass['identity'];
  const item = modifiers.get(identity);
  if (item) {
    item.stageValue = value;
  }
  else {
    modifiers.set(identity, new modifierClass(value));
  }
}
function modifierWithKey(modifiers, identity, modifierClass, value) {
  const item = modifiers.get(identity);
  if (item) {
    item.stageValue = value;
  }
  else {
    modifiers.set(identity, new modifierClass(value));
  }
}
class ArkComponent {
  constructor(nativePtr) {
    this._modifiers = new Map();
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
  }
  applyModifierPatch() {
    let expiringItems = [];
    let expiringItemsWithKeys = [];
    this._modifiers.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItems.push(key);
      }
    });
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItems.forEach(key => {
      this._modifiers.delete(key);
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, WidthModifier.identity, WidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, HeightModifier.identity, HeightModifier, value);
    return this;
  }
  expandSafeArea(types, edges) {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length > 0) {
      let safeAreaType = '';
      for (let param of types) {
        if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
        }
        else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length > 0) {
      let safeAreaEdge = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
        }
        else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, ExpandSafeAreaModifier.identity, ExpandSafeAreaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, ExpandSafeAreaModifier.identity, ExpandSafeAreaModifier, opts);
    }
    return this;
  }
  responseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, ResponseRegionModifier.identity, ResponseRegionModifier, value);
    return this;
  }
  mouseResponseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, MouseResponseRegionModifier.identity, MouseResponseRegionModifier, value);
    return this;
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, SizeModifier.identity, SizeModifier, value);
    return this;
  }
  constraintSize(value) {
    modifierWithKey(this._modifiersWithKeys, ConstraintSizeModifier.identity, ConstraintSizeModifier, value);
    return this;
  }
  touchable(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, TouchableModifier.identity, TouchableModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, TouchableModifier.identity, TouchableModifier, undefined);
    }
    return this;
  }
  hitTestBehavior(value) {
    if (value) {
      modifierWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity, HitTestBehaviorModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, HitTestBehaviorModifier.identity, HitTestBehaviorModifier, undefined);
    }
    return this;
  }
  layoutWeight(value) {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, value);
    }
    else if (isString(value) && !isNaN(Number(value))) {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, parseInt(value.toString()));
    }
    else {
      modifierWithKey(this._modifiersWithKeys, LayoutWeightModifier.identity, LayoutWeightModifier, undefined);
    }
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
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, PaddingModifier.identity, PaddingModifier, undefined);
    }
    return this;
  }
  margin(value) {
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
      modifierWithKey(this._modifiersWithKeys, MarginModifier.identity, MarginModifier, arkValue);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, MarginModifier.identity, MarginModifier, undefined);
    }
    return this;
  }
  background(builder, options) {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier, value);
    return this;
  }
  backgroundImage(src, repeat) {
    let arkBackgroundImage = new ArkBackgroundImage();
    arkBackgroundImage.src = src;
    arkBackgroundImage.repeat = repeat;
    modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier, arkBackgroundImage);
    return this;
  }
  backgroundImageSize(value) {
    modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier, value);
    return this;
  }
  backgroundImagePosition(value) {
    modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier, value);
    return this;
  }
  backgroundBlurStyle(value, options) {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, BackgroundBlurStyleModifier.identity, BackgroundBlurStyleModifier, undefined);
      return this;
    }
    let arkBackgroundBlurStyle = new ArkBackgroundBlurStyle();
    arkBackgroundBlurStyle.blurStyle = value;
    if (typeof options === 'object') {
      arkBackgroundBlurStyle.colorMode = options.colorMode;
      arkBackgroundBlurStyle.adaptiveColor = options.adaptiveColor;
      arkBackgroundBlurStyle.scale = options.scale;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundBlurStyleModifier.identity, BackgroundBlurStyleModifier, arkBackgroundBlurStyle);
    return this;
  }
  foregroundBlurStyle(value, options) {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, ForegroundBlurStyleModifier.identity, ForegroundBlurStyleModifier, undefined);
      return this;
    }
    let arkForegroundBlurStyle = new ArkForegroundBlurStyle();
    arkForegroundBlurStyle.blurStyle = value;
    if (typeof options === 'object') {
      arkForegroundBlurStyle.colorMode = options.colorMode;
      arkForegroundBlurStyle.adaptiveColor = options.adaptiveColor;
      arkForegroundBlurStyle.scale = options.scale;
    }
    modifierWithKey(this._modifiersWithKeys, ForegroundBlurStyleModifier.identity, ForegroundBlurStyleModifier, arkForegroundBlurStyle);
    return this;
  }
  opacity(value) {
    modifierWithKey(this._modifiersWithKeys, OpacityModifier.identity, OpacityModifier, value);
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
    modifierWithKey(this._modifiersWithKeys, BorderModifier.identity, BorderModifier, arkBorder);
    return this;
  }
  borderStyle(value) {
    modifierWithKey(this._modifiersWithKeys, BorderStyleModifier.identity, BorderStyleModifier, value);
    return this;
  }
  borderWidth(value) {
    modifierWithKey(this._modifiersWithKeys, BorderWidthModifier.identity, BorderWidthModifier, value);
    return this;
  }
  borderColor(value) {
    modifierWithKey(this._modifiersWithKeys, BorderColorModifier.identity, BorderColorModifier, value);
    return this;
  }
  borderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, BorderRadiusModifier.identity, BorderRadiusModifier, value);
    return this;
  }
  borderImage(value) {
    modifierWithKey(this._modifiersWithKeys, BorderImageModifier.identity, BorderImageModifier, value);
    return this;
  }
  foregroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, ForegroundColorModifier.identity, ForegroundColorModifier, value);
    return this;
  }
  onClick(event) {
    throw new Error('Method not implemented.');
  }
  onHover(event) {
    throw new Error('Method not implemented.');
  }
  hoverEffect(value) {
    modifier(this._modifiers, HoverEffectModifier, value);
    return this;
  }
  onMouse(event) {
    throw new Error('Method not implemented.');
  }
  onTouch(event) {
    throw new Error('Method not implemented.');
  }
  onKeyEvent(event) {
    throw new Error('Method not implemented.');
  }
  focusable(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, FocusableModifier.identity, FocusableModifier, undefined);
    }
    return this;
  }
  onFocus(event) {
    throw new Error('Method not implemented.');
  }
  onBlur(event) {
    throw new Error('Method not implemented.');
  }
  tabIndex(index) {
    if (typeof index !== 'number') {
      modifierWithKey(this._modifiersWithKeys, TabIndexModifier.identity, TabIndexModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, TabIndexModifier.identity, TabIndexModifier, index);
    }
    return this;
  }
  defaultFocus(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity, DefaultFocusModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, DefaultFocusModifier.identity, DefaultFocusModifier, undefined);
    }
    return this;
  }
  groupDefaultFocus(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity, GroupDefaultFocusModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, GroupDefaultFocusModifier.identity, GroupDefaultFocusModifier, undefined);
    }
    return this;
  }
  focusOnTouch(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity, FocusOnTouchModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, FocusOnTouchModifier.identity, FocusOnTouchModifier, undefined);
    }
    return this;
  }
  animation(value) {
    throw new Error('Method not implemented.');
  }
  transition(value) {
    modifierWithKey(this._modifiersWithKeys, TransitionModifier.identity, TransitionModifier, value);
    return this;
  }
  gesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  priorityGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  parallelGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  blur(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, value);
    }
    return this;
  }
  linearGradientBlur(value, options) {
    if (isUndefined(value) || isNull(value) || isUndefined(options) || isNull(options)) {
      modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier, undefined);
      return this;
    }
    let arkLinearGradientBlur = new ArkLinearGradientBlur();
    arkLinearGradientBlur.blurRadius = value;
    arkLinearGradientBlur.fractionStops = options.fractionStops;
    arkLinearGradientBlur.direction = options.direction;
    modifierWithKey(this._modifiersWithKeys, LinearGradientBlurModifier.identity, LinearGradientBlurModifier, arkLinearGradientBlur);
    return this;
  }
  brightness(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, value);
    }
    return this;
  }
  contrast(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, value);
    }
    return this;
  }
  grayscale(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GrayscaleModifier.identity, GrayscaleModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, GrayscaleModifier.identity, GrayscaleModifier, value);
    }
    return this;
  }
  colorBlend(value) {
    modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
    return this;
  }
  saturate(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, value);
    }
    return this;
  }
  sepia(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, value);
    }
    return this;
  }
  invert(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, value);
    }
    return this;
  }
  hueRotate(value) {
    if (!isNumber(value) && !isString(value)) {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, value);
    }
    return this;
  }
  useEffect(value) {
    modifierWithKey(this._modifiersWithKeys, UseEffectModifier.identity, UseEffectModifier, value);
    return this;
  }
  backdropBlur(value) {
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, value);
    }
    return this;
  }
  renderGroup(value) {
    modifierWithKey(this._modifiersWithKeys, RenderGroupModifier.identity, RenderGroupModifier, value);
    return this;
  }
  translate(value) {
    modifierWithKey(this._modifiersWithKeys, TranslateModifier.identity, TranslateModifier, value);
    return this;
  }
  scale(value) {
    modifierWithKey(this._modifiersWithKeys, ScaleModifier.identity, ScaleModifier, value);
    return this;
  }
  gridSpan(value) {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GridSpanModifier.identity, GridSpanModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, GridSpanModifier.identity, GridSpanModifier, undefined);
    }
    return this;
  }
  gridOffset(value) {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, GridOffsetModifier.identity, GridOffsetModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, GridOffsetModifier.identity, GridOffsetModifier, undefined);
    }
    return this;
  }
  rotate(value) {
    modifierWithKey(this._modifiersWithKeys, RotateModifier.identity, RotateModifier, value);
    return this;
  }
  transform(value) {
    modifierWithKey(this._modifiersWithKeys, TransformModifier.identity, TransformModifier, value);
    return this;
  }
  onAppear(event) {
    throw new Error('Method not implemented.');
  }
  onDisAppear(event) {
    throw new Error('Method not implemented.');
  }
  onAreaChange(event) {
    throw new Error('Method not implemented.');
  }
  visibility(value) {
    modifierWithKey(this._modifiersWithKeys, VisibilityModifier.identity, VisibilityModifier, value);
    return this;
  }
  flexGrow(value) {
    modifierWithKey(this._modifiersWithKeys, FlexGrowModifier.identity, FlexGrowModifier, value);
    return this;
  }
  flexShrink(value) {
    modifierWithKey(this._modifiersWithKeys, FlexShrinkModifier.identity, FlexShrinkModifier, value);
    return this;
  }
  flexBasis(value) {
    modifierWithKey(this._modifiersWithKeys, FlexBasisModifier.identity, FlexBasisModifier, value);
    return this;
  }
  alignSelf(value) {
    modifierWithKey(this._modifiersWithKeys, AlignSelfModifier.identity, AlignSelfModifier, value);
    return this;
  }
  displayPriority(value) {
    modifierWithKey(this._modifiersWithKeys, DisplayPriorityModifier.identity, DisplayPriorityModifier, value);
    return this;
  }
  zIndex(value) {
    if (value !== null) {
      let zIndex = 0;
      if (typeof (value) === 'number') {
        zIndex = value;
      }
      modifierWithKey(this._modifiersWithKeys, ZIndexModifier.identity, ZIndexModifier, zIndex);
    }
    return this;
  }
  sharedTransition(id, options) {
    let arkSharedTransition = new ArkSharedTransition();
    if (isString(id)) {
      arkSharedTransition.id = id;
    }
    if (typeof options === 'object') {
      arkSharedTransition.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, SharedTransitionModifier.identity, SharedTransitionModifier, arkSharedTransition);
    return this;
  }
  direction(value) {
    modifierWithKey(this._modifiersWithKeys, DirectionModifier.identity, DirectionModifier, value);
    return this;
  }
  align(value) {
    if (isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, AlignModifier.identity, AlignModifier, undefined);
    }
    return this;
  }
  position(value) {
    modifierWithKey(this._modifiersWithKeys, PositionModifier.identity, PositionModifier, value);
    return this;
  }
  markAnchor(value) {
    modifierWithKey(this._modifiersWithKeys, MarkAnchorModifier.identity, MarkAnchorModifier, value);
    return this;
  }
  offset(value) {
    modifierWithKey(this._modifiersWithKeys, OffsetModifier.identity, OffsetModifier, value);
    return this;
  }
  enabled(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, EnabledModifier.identity, EnabledModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, EnabledModifier.identity, EnabledModifier, undefined);
    }
    return this;
  }
  useSizeType(value) {
    throw new Error('Method not implemented.');
  }
  alignRules(value) {
    if (!isObject(value) || JSON.stringify(value) === '{}') {
      modifierWithKey(this._modifiersWithKeys, AlignRulesModifier.identity, AlignRulesModifier, undefined);
      return this;
    }
    let keys = ['left', 'middle', 'right', 'top', 'center', 'bottom'];
    let arkValue = new ArkAlignRules();
    for (let i = 0; i < keys.length; i++) {
      let rule = value[keys[i]];
      let alignRule = '';
      if (isObject(rule)) {
        let alignSign = false;
        let anchorSign = false;
        let align = rule.align;
        let anchor = rule.anchor;
        if (isString(anchor)) {
          anchorSign = true;
        }
        if (i < DIRECTION_RANGE) {
          if (align in HorizontalAlign) {
            alignSign = true;
          }
        }
        else {
          if (align in VerticalAlign) {
            alignSign = true;
          }
        }
        if (!alignSign && !anchorSign) {
          alignRule += '';
        }
        else if (!anchorSign) {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += '__container__';
        }
        else if (!alignSign) {
          alignRule += '2';
          alignRule += '|';
          alignRule += anchor;
        }
        else {
          alignRule += align.toString();
          alignRule += '|';
          alignRule += anchor;
        }
      }
      else {
        alignRule += '';
      }
      switch (keys[i]) {
        case 'left':
          arkValue.left = alignRule;
          break;
        case 'middle':
          arkValue.middle = alignRule;
          break;
        case 'right':
          arkValue.right = alignRule;
          break;
        case 'top':
          arkValue.top = alignRule;
          break;
        case 'center':
          arkValue.center = alignRule;
          break;
        case 'bottom':
          arkValue.bottom = alignRule;
          break;
      }
    }
    modifierWithKey(this._modifiersWithKeys, AlignRulesModifier.identity, AlignRulesModifier, arkValue);
    return this;
  }
  aspectRatio(value) {
    modifierWithKey(this._modifiersWithKeys, AspectRatioModifier.identity, AspectRatioModifier, value);
    return this;
  }
  clickEffect(value) {
    modifierWithKey(this._modifiersWithKeys, ClickEffectModifier.identity, ClickEffectModifier, value);
    return this;
  }
  onDragStart(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnter(event) {
    throw new Error('Method not implemented.');
  }
  onDragMove(event) {
    throw new Error('Method not implemented.');
  }
  onDragLeave(event) {
    throw new Error('Method not implemented.');
  }
  onDrop(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnd(event) {
    throw new Error('Method not implemented.');
  }
  allowDrop(value) {
    modifierWithKey(this._modifiersWithKeys, AllowDropModifier.identity, AllowDropModifier, value);
    return this;
  }
  draggable(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, DraggableModifier.identity, DraggableModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, DraggableModifier.identity, DraggableModifier, undefined);
    }
    return this;
  }
  overlay(value, options) {
    if (typeof value === 'undefined') {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, undefined);
      return this;
    }
    let arkOverlay = new ArkOverlay();
    if (arkOverlay.splitOverlayValue(value, options)) {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, arkOverlay);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, OverlayModifier.identity, OverlayModifier, undefined);
    }
    return this;
  }
  linearGradient(value) {
    modifierWithKey(this._modifiersWithKeys, LinearGradientModifier.identity, LinearGradientModifier, value);
    return this;
  }
  sweepGradient(value) {
    modifierWithKey(this._modifiersWithKeys, SweepGradientModifier.identity, SweepGradientModifier, value);
    return this;
  }
  radialGradient(value) {
    modifierWithKey(this._modifiersWithKeys, RadialGradientModifier.identity, RadialGradientModifier, value);
    return this;
  }
  motionPath(value) {
    modifierWithKey(this._modifiersWithKeys, MotionPathModifier.identity, MotionPathModifier, value);
    return this;
  }
  shadow(value) {
    modifierWithKey(this._modifiersWithKeys, ShadowModifier.identity, ShadowModifier, value);
    return this;
  }
  mask(value) {
    modifierWithKey(this._modifiersWithKeys, MaskModifier.identity, MaskModifier, value);
    return this;
  }
  key(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, KeyModifier.identity, KeyModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, KeyModifier.identity, KeyModifier, undefined);
    }
    return this;
  }
  id(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, IdModifier.identity, IdModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, IdModifier.identity, IdModifier, undefined);
    }
    return this;
  }
  geometryTransition(id) {
    if (isString(id)) {
      modifierWithKey(this._modifiersWithKeys, GeometryTransitionModifier.identity, GeometryTransitionModifier, id);
    }
    return this;
  }
  bindPopup(show, popup) {
    throw new Error('Method not implemented.');
  }
  bindMenu(content, options) {
    throw new Error('Method not implemented.');
  }
  bindContextMenu(content, responseType, options) {
    throw new Error('Method not implemented.');
  }
  bindContentCover(isShow, builder, type) {
    throw new Error('Method not implemented.');
  }
  blendMode(value) {
    throw new Error('Method not implemented.');
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, Symbol('clip'), ClipModifier, value);
    return this;
  }
  bindSheet(isShow, builder, options) {
    throw new Error('Method not implemented.');
  }
  stateStyles(value) {
    throw new Error('Method not implemented.');
  }
  restoreId(value) {
    if (typeof value !== 'number') {
      modifierWithKey(this._modifiersWithKeys, RestoreIdModifier.identity, RestoreIdModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, RestoreIdModifier.identity, RestoreIdModifier, value);
    }
    return this;
  }
  onVisibleAreaChange(ratios, event) {
    throw new Error('Method not implemented.');
  }
  sphericalEffect(value) {
    modifierWithKey(this._modifiersWithKeys, SphericalEffectModifier.identity, SphericalEffectModifier, value);
    return this;
  }
  lightUpEffect(value) {
    modifierWithKey(this._modifiersWithKeys, LightUpEffectModifier.identity, LightUpEffectModifier, value);
    return this;
  }
  pixelStretchEffect(options) {
    modifierWithKey(this._modifiersWithKeys, PixelStretchEffectModifier.identity, PixelStretchEffectModifier, options);
    return this;
  }
  keyboardShortcut(value, keys, action) {
    let keyboardShortCut = new ArkKeyBoardShortCut();
    keyboardShortCut.value = value;
    keyboardShortCut.keys = keys;
    modifierWithKey(this._modifiersWithKeys, KeyBoardShortCutModifier.identity, KeyBoardShortCutModifier, keyboardShortCut);
    return this;
  }
  accessibilityGroup(value) {
    if (typeof value === 'boolean') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityGroupModifier.identity, AccessibilityGroupModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityGroupModifier.identity, AccessibilityGroupModifier, undefined);
    }
    return this;
  }
  accessibilityText(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextModifier.identity, AccessibilityTextModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityTextModifier.identity, AccessibilityTextModifier, undefined);
    }
    return this;
  }
  accessibilityDescription(value) {
    if (typeof value !== 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDescriptionModifier.identity, AccessibilityDescriptionModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityDescriptionModifier.identity, AccessibilityDescriptionModifier, value);
    }
    return this;
  }
  accessibilityLevel(value) {
    if (typeof value !== 'string') {
      modifierWithKey(this._modifiersWithKeys, AccessibilityLevelModifier.identity, AccessibilityLevelModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, AccessibilityLevelModifier.identity, AccessibilityLevelModifier, value);
    }
    return this;
  }
  obscured(reasons) {
    modifierWithKey(this._modifiersWithKeys, ObscuredModifier.identity, ObscuredModifier, reasons);
    return this;
  }
  reuseId(id) {
    throw new Error('Method not implemented.');
  }
  renderFit(fitMode) {
    modifierWithKey(this._modifiersWithKeys, RenderFitModifier.identity, RenderFitModifier, fitMode);
    return this;
  }
  attributeModifier(modifier) {
    return this;
  }
}
const isNull = (val) => typeof val === 'object' && val === null;
const isArray = (val) => Array.isArray(val);
const isDate = (val) => val instanceof Date;
const isRegExp = (val) => val instanceof RegExp;
const isError = (val) => val instanceof Error;
const isFloat = (val) => Number.isFinite(val) && !Number.isInteger(val);
const isInteger = (val) => Number.isInteger(val);
const isNonEmptyMap = (val) => val instanceof Map && val.size > 0;
const isTruthyString = (val) => typeof val === 'string' && val.trim() !== '';

/// <reference path='./import.ts' />
class BlankColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().blank.resetColor(node);
    }
    else {
      getUINativeModule().blank.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlankColorModifier.identity = Symbol('blankColor');
class ArkBlankComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, BlankColorModifier.identity, BlankColorModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Blank.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkBlankComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ColumnAlignItemsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().column.resetAlignItems(node);
    }
    else {
      getUINativeModule().column.setAlignItems(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnAlignItemsModifier.identity = Symbol('columnAlignItems');
class ColumnJustifyContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().column.resetJustifyContent(node);
    }
    else {
      getUINativeModule().column.setJustifyContent(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnJustifyContentModifier.identity = Symbol('columnJustifyContent');
class ArkColumnComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  alignItems(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnAlignItemsModifier.identity, ColumnAlignItemsModifier, value);
    return this;
  }
  justifyContent(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnJustifyContentModifier.identity, ColumnJustifyContentModifier, value);
    return this;
  }
  pointLight(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Column.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkColumnComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ColumnSplitDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().columnSplit.resetDivider(node);
    }
    else {
      getUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin);
  }
}
ColumnSplitDividerModifier.identity = Symbol('columnSplitDivider');
class ColumnSplitResizeableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().columnSplit.resetResizeable(node);
    }
    else {
      getUINativeModule().columnSplit.setResizeable(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnSplitResizeableModifier.identity = Symbol('columnSplitResizeable');
class ArkColumnSplitComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  resizeable(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitResizeableModifier.identity, ColumnSplitResizeableModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnSplitDividerModifier.identity, ColumnSplitDividerModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ColumnSplit.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkColumnSplitComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class DividerVerticalModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().divider.resetVertical(node);
    }
    else {
      getUINativeModule().divider.setVertical(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
DividerVerticalModifier.identity = Symbol('dividerVertical');
class DividerLineCapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().divider.resetLineCap(node);
    }
    else {
      getUINativeModule().divider.setLineCap(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
DividerLineCapModifier.identity = Symbol('dividerLineCap');
class DividerColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().divider.resetColor(node);
    }
    else {
      getUINativeModule().divider.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DividerColorModifier.identity = Symbol('dividerColor');
class DividerStrokeWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().divider.resetStrokeWidth(node);
    }
    else {
      getUINativeModule().divider.setStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
DividerStrokeWidthModifier.identity = Symbol('dividerStrokeWidth');
class ArkDividerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  vertical(value) {
    modifierWithKey(this._modifiersWithKeys, DividerVerticalModifier.identity, DividerVerticalModifier, value);
    return this;
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, DividerColorModifier.identity, DividerColorModifier, value);
    return this;
  }
  strokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, DividerStrokeWidthModifier.identity, DividerStrokeWidthModifier, value);
    return this;
  }
  lineCap(value) {
    modifierWithKey(this._modifiersWithKeys, DividerLineCapModifier.identity, DividerLineCapModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Divider.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDividerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkFlexComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  pointLight(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Flex.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkFlexComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class GridRowAlignItemsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridRow.resetAlignItems(node);
    }
    else {
      getUINativeModule().gridRow.setAlignItems(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GridRowAlignItemsModifier.identity = Symbol('gridRowAlignItems');
class ArkGridRowComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onBreakpointChange(callback) {
    throw new Error('Method not implemented.');
  }
  alignItems(value) {
    modifierWithKey(this._modifiersWithKeys, GridRowAlignItemsModifier.identity, GridRowAlignItemsModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.GridRow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridRowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkGridComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  columnsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, GridColumnsTemplateModifier.identity, GridColumnsTemplateModifier, value);
    return this;
  }
  rowsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, GridRowsTemplateModifier.identity, GridRowsTemplateModifier, value);
    return this;
  }
  columnsGap(value) {
    modifierWithKey(this._modifiersWithKeys, GridColumnsGapModifier.identity, GridColumnsGapModifier, value);
    return this;
  }
  rowsGap(value) {
    modifierWithKey(this._modifiersWithKeys, GridRowsGapModifier.identity, GridRowsGapModifier, value);
    return this;
  }
  scrollBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarWidthModifier.identity, GridScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value) {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarColorModifier.identity, GridScrollBarColorModifier, value);
    return this;
  }
  scrollBar(value) {
    modifierWithKey(this._modifiersWithKeys, GridScrollBarModifier.identity, GridScrollBarModifier, value);
    return this;
  }
  onScrollBarUpdate(event) {
    throw new Error('Method not implemented.');
  }
  onScrollIndex(event) {
    throw new Error('Method not implemented.');
  }
  cachedCount(value) {
    modifierWithKey(this._modifiersWithKeys, GridCachedCountModifier.identity, GridCachedCountModifier, value);
    return this;
  }
  editMode(value) {
    modifierWithKey(this._modifiersWithKeys, GridEditModeModifier.identity, GridEditModeModifier, value);
    return this;
  }
  multiSelectable(value) {
    modifierWithKey(this._modifiersWithKeys, GridMultiSelectableModifier.identity, GridMultiSelectableModifier, value);
    return this;
  }
  maxCount(value) {
    modifierWithKey(this._modifiersWithKeys, GridMaxCountModifier.identity, GridMaxCountModifier, value);
    return this;
  }
  minCount(value) {
    modifierWithKey(this._modifiersWithKeys, GridMinCountModifier.identity, GridMinCountModifier, value);
    return this;
  }
  cellLength(value) {
    modifierWithKey(this._modifiersWithKeys, GridCellLengthModifier.identity, GridCellLengthModifier, value);
    return this;
  }
  layoutDirection(value) {
    modifierWithKey(this._modifiersWithKeys, GridLayoutDirectionModifier.identity, GridLayoutDirectionModifier, value);
    return this;
  }
  supportAnimation(value) {
    modifierWithKey(this._modifiersWithKeys, GridSupportAnimationModifier.identity, GridSupportAnimationModifier, value);
    return this;
  }
  onItemDragStart(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragEnter(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragMove(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragLeave(event) {
    throw new Error('Method not implemented.');
  }
  onItemDrop(event) {
    throw new Error('Method not implemented.');
  }
  edgeEffect(value, options) {
    let effect = new ArkGridEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, GridEdgeEffectModifier.identity, GridEdgeEffectModifier, effect);
    return this;
  }
  nestedScroll(value) {
    modifierWithKey(this._modifiersWithKeys, GridNestedScrollModifier.identity, GridNestedScrollModifier, value);
    return this;
  }
  enableScrollInteraction(value) {
    modifierWithKey(this._modifiersWithKeys, GridEnableScrollModifier.identity, GridEnableScrollModifier, value);
    return this;
  }
  friction(value) {
    modifierWithKey(this._modifiersWithKeys, GridFrictionModifier.identity, GridFrictionModifier, value);
    return this;
  }
  onScroll(event) {
    throw new Error('Method not implemented.');
  }
  onReachStart(event) {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStart(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStop(event) {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class GridColumnsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetColumnsTemplate(node);
    }
    else {
      getUINativeModule().grid.setColumnsTemplate(node, this.value);
    }
  }
}
GridColumnsTemplateModifier.identity = Symbol('gridColumnsTemplate');
class GridRowsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetRowsTemplate(node);
    }
    else {
      getUINativeModule().grid.setRowsTemplate(node, this.value);
    }
  }
}
GridRowsTemplateModifier.identity = Symbol('gridRowsTemplate');
class GridColumnsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetColumnsGap(node);
    }
    else {
      getUINativeModule().grid.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GridColumnsGapModifier.identity = Symbol('gridColumnsGap');
class GridRowsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetRowsGap(node);
    }
    else {
      getUINativeModule().grid.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GridRowsGapModifier.identity = Symbol('gridRowsGap');
class GridScrollBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetScrollBarWidth(node);
    }
    else {
      getUINativeModule().grid.setScrollBarWidth(node, this.value);
    }
  }
}
GridScrollBarWidthModifier.identity = Symbol('gridScrollBarWidth');
class GridScrollBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetScrollBar(node);
    }
    else {
      getUINativeModule().grid.setScrollBar(node, this.value);
    }
  }
}
GridScrollBarModifier.identity = Symbol('gridScrollBar');
class GridScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetScrollBarColor(node);
    }
    else {
      getUINativeModule().grid.setScrollBarColor(node, this.value);
    }
  }
}
GridScrollBarColorModifier.identity = Symbol('gridScrollBarColor');
class GridEditModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetEditMode(node);
    }
    else {
      getUINativeModule().grid.setEditMode(node, this.value);
    }
  }
}
GridEditModeModifier.identity = Symbol('gridEditMode');
class GridCachedCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetCachedCount(node);
    }
    else {
      getUINativeModule().grid.setCachedCount(node, this.value);
    }
  }
}
GridCachedCountModifier.identity = Symbol('gridCachedCount');
class GridMultiSelectableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetMultiSelectable(node);
    }
    else {
      getUINativeModule().grid.setMultiSelectable(node, this.value);
    }
  }
}
GridMultiSelectableModifier.identity = Symbol('gridMultiSelectable');
class GridEdgeEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().grid.resetEdgeEffect(node);
    }
    else {
      getUINativeModule().grid.setEdgeEffect(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.value, (_b = this.value.options) === null ||
      _b === void 0 ? void 0 : _b.alwaysEnabled);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}
GridEdgeEffectModifier.identity = Symbol('gridEdgeEffect');
class GridNestedScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().grid.resetNestedScroll(node);
    }
    else {
      getUINativeModule().grid.setNestedScroll(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.scrollForward, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.scrollBackward);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.scrollForward === this.value.scrollForward) &&
      (this.stageValue.scrollBackward === this.value.scrollBackward));
  }
}
GridNestedScrollModifier.identity = Symbol('gridNestedScroll');
class GridEnableScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetEnableScroll(node);
    }
    else {
      getUINativeModule().grid.setEnableScroll(node, this.value);
    }
  }
}
GridEnableScrollModifier.identity = Symbol('gridEnableScroll');
class GridFrictionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetFriction(node);
    }
    else {
      getUINativeModule().grid.setFriction(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GridFrictionModifier.identity = Symbol('gridFriction');
class GridMaxCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetMaxCount(node);
    }
    else {
      getUINativeModule().grid.setMaxCount(node, this.value);
    }
  }
}
GridMaxCountModifier.identity = Symbol('gridMaxCount');
class GridMinCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetMinCount(node);
    }
    else {
      getUINativeModule().grid.setMinCount(node, this.value);
    }
  }
}
GridMinCountModifier.identity = Symbol('gridMinCount');
class GridCellLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetCellLength(node);
    }
    else {
      getUINativeModule().grid.setCellLength(node, this.value);
    }
  }
}
GridCellLengthModifier.identity = Symbol('gridCellLength');
class GridLayoutDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetLayoutDirection(node);
    }
    else {
      getUINativeModule().grid.setLayoutDirection(node, this.value);
    }
  }
}
GridLayoutDirectionModifier.identity = Symbol('gridLayoutDirection');
class GridSupportAnimationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().grid.resetSupportAnimation(node);
    }
    else {
      getUINativeModule().grid.setSupportAnimation(node, this.value);
    }
  }
}
GridSupportAnimationModifier.identity = Symbol('gridSupportAnimation');
// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class GridColSpanModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridCol.resetSpan(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setSpan(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().gridCol.setSpan(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff() {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    }
    else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    }
    else {
      return true;
    }
  }
}
GridColSpanModifier.identity = Symbol('gridColSpan');
class GridColOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridCol.resetGridColOffset(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setGridColOffset(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().gridCol.setGridColOffset(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff() {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    }
    else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    }
    else {
      return true;
    }
  }
}
GridColOffsetModifier.identity = Symbol('gridColOffset');
class GridColOrderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridCol.resetOrder(node);
    }
    else {
      if (isNumber(this.value)) {
        getUINativeModule().gridCol.setOrder(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().gridCol.setOrder(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
      }
    }
  }
  checkObjectDiff() {
    if (isNumber(this.stageValue) && isNumber(this.value)) {
      return this.stageValue !== this.value;
    }
    else if (isObject(this.stageValue) && isObject(this.value)) {
      return this.stageValue.xs !== this.value.xs ||
        this.stageValue.sm !== this.value.sm ||
        this.stageValue.md !== this.value.md ||
        this.stageValue.lg !== this.value.lg ||
        this.stageValue.xl !== this.value.xl ||
        this.stageValue.xxl !== this.value.xxl;
    }
    else {
      return true;
    }
  }
}
GridColOrderModifier.identity = Symbol('gridColOrder');
class ArkGridColComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  span(value) {
    modifierWithKey(this._modifiersWithKeys, GridColSpanModifier.identity, GridColSpanModifier, value);
    return this;
  }
  gridColOffset(value) {
    modifierWithKey(this._modifiersWithKeys, GridColOffsetModifier.identity, GridColOffsetModifier, value);
    return this;
  }
  order(value) {
    modifierWithKey(this._modifiersWithKeys, GridColOrderModifier.identity, GridColOrderModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.GridCol.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridColComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ImageColorFilterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetColorFilter(node);
    }
    else {
      getUINativeModule().image.setColorFilter(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ImageColorFilterModifier.identity = Symbol('imageColorFilter');
class ImageFillColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetFillColor(node);
    }
    else {
      getUINativeModule().image.setFillColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ImageFillColorModifier.identity = Symbol('imageFillColor');
class ImageAltModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetAlt(node);
    }
    else {
      getUINativeModule().image.setAlt(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ImageAltModifier.identity = Symbol('imageAlt');
class ImageCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetCopyOption(node);
    }
    else {
      getUINativeModule().image.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageCopyOptionModifier.identity = Symbol('imageCopyOption');
class ImageAutoResizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetAutoResize(node);
    }
    else {
      getUINativeModule().image.setAutoResize(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAutoResizeModifier.identity = Symbol('imageAutoResize');
class ImageFitOriginalSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetFitOriginalSize(node);
    }
    else {
      getUINativeModule().image.setFitOriginalSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageFitOriginalSizeModifier.identity = Symbol('imageFitOriginalSize');
class ImageDraggableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetDraggable(node);
    }
    else {
      getUINativeModule().image.setDraggable(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageDraggableModifier.identity = Symbol('imageDraggable');
class ImageInterpolationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetImageInterpolation(node);
    }
    else {
      getUINativeModule().image.setImageInterpolation(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageInterpolationModifier.identity = Symbol('imageInterpolation');
class ImageSourceSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetSourceSize(node);
    }
    else {
      getUINativeModule().image.setSourceSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return this.stageValue.width !== this.value.width ||
      this.stageValue.height !== this.value.height;
  }
}
ImageSourceSizeModifier.identity = Symbol('imageSourceSize');
class ImageMatchTextDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetMatchTextDirection(node);
    }
    else {
      getUINativeModule().image.setMatchTextDirection(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageMatchTextDirectionModifier.identity = Symbol('imageMatchTextDirection');
class ImageObjectRepeatModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetObjectRepeat(node);
    }
    else {
      getUINativeModule().image.setObjectRepeat(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageObjectRepeatModifier.identity = Symbol('imageObjectRepeat');
class ImageRenderModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetRenderMode(node);
    }
    else {
      getUINativeModule().image.setRenderMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageRenderModeModifier.identity = Symbol('imageRenderMode');
class ImageSyncLoadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetSyncLoad(node);
    }
    else {
      getUINativeModule().image.setSyncLoad(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageSyncLoadModifier.identity = Symbol('imageSyncLoad');
class ImageObjectFitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetObjectFit(node);
    }
    else {
      getUINativeModule().image.setObjectFit(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageObjectFitModifier.identity = Symbol('imageObjectFit');
class ImageBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().image.setBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().image.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
ImageBorderRadiusModifier.identity = Symbol('imageBorderRadius');
class ArkImageComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  draggable(value) {
    modifierWithKey(this._modifiersWithKeys, ImageDraggableModifier.identity, ImageDraggableModifier, value);
    return this;
  }
  alt(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAltModifier.identity, ImageAltModifier, value);
    return this;
  }
  matchTextDirection(value) {
    modifierWithKey(this._modifiersWithKeys, ImageMatchTextDirectionModifier.identity, ImageMatchTextDirectionModifier, value);
    return this;
  }
  fitOriginalSize(value) {
    modifierWithKey(this._modifiersWithKeys, ImageFitOriginalSizeModifier.identity, ImageFitOriginalSizeModifier, value);
    return this;
  }
  fillColor(value) {
    modifierWithKey(this._modifiersWithKeys, ImageFillColorModifier.identity, ImageFillColorModifier, value);
    return this;
  }
  objectFit(value) {
    modifierWithKey(this._modifiersWithKeys, ImageObjectFitModifier.identity, ImageObjectFitModifier, value);
    return this;
  }
  objectRepeat(value) {
    modifierWithKey(this._modifiersWithKeys, ImageObjectRepeatModifier.identity, ImageObjectRepeatModifier, value);
    return this;
  }
  autoResize(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAutoResizeModifier.identity, ImageAutoResizeModifier, value);
    return this;
  }
  renderMode(value) {
    modifierWithKey(this._modifiersWithKeys, ImageRenderModeModifier.identity, ImageRenderModeModifier, value);
    return this;
  }
  interpolation(value) {
    modifierWithKey(this._modifiersWithKeys, ImageInterpolationModifier.identity, ImageInterpolationModifier, value);
    return this;
  }
  sourceSize(value) {
    modifierWithKey(this._modifiersWithKeys, ImageSourceSizeModifier.identity, ImageSourceSizeModifier, value);
    return this;
  }
  syncLoad(value) {
    modifierWithKey(this._modifiersWithKeys, ImageSyncLoadModifier.identity, ImageSyncLoadModifier, value);
    return this;
  }
  colorFilter(value) {
    modifierWithKey(this._modifiersWithKeys, ImageColorFilterModifier.identity, ImageColorFilterModifier, value);
    return this;
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, ImageCopyOptionModifier.identity, ImageCopyOptionModifier, value);
    return this;
  }
  borderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, ImageBorderRadiusModifier.identity, ImageBorderRadiusModifier, value);
    return this;
  }
  onComplete(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
  onFinish(event) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Image.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ImageAnimatorImagesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetImages(node);
    }
    else {
      let arkImageFrame = this.convertImageFrames(this.value);
      if (!arkImageFrame) {
        getUINativeModule().imageAnimator.resetImages(node);
      }
      else {
        getUINativeModule().imageAnimator.setImages(node, arkImageFrame.arrSrc,
          arkImageFrame.arrWidth, arkImageFrame.arrHeight, arkImageFrame.arrTop,
          arkImageFrame.arrLeft, arkImageFrame.arrDuration, arkImageFrame.arrSrc.length);
      }
    }
  }
  checkObjectDiff() {
    let checkDiff = true;
    if (this.value && this.value.length > 0 &&
      this.stageValue && this.stageValue.length > 0 &&
      this.value.length === this.stageValue.length) {
      let checkItemEqual = false;
      for (let i = 0; i < this.value.length; i++) {
        checkItemEqual = this.isEqual(this.stageValue[i], this.value[i]);
        if (!checkItemEqual) {
          checkDiff = !checkItemEqual;
          break;
        }
      }
    }
    return checkDiff;
  }
  isEqual(one, another) {
    if (!(one.width === another.width &&
      one.height === another.height &&
      one.top === another.top &&
      one.left === another.left &&
      one.duration === another.duration)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual(one.src, another.src);
    }
  }
  convertImageFrames(value) {
    if (value && value.length > 0) {
      let isFlag = true;
      for (let item of value) {
        if (item.src === undefined || item.src === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        let array = new ArkImageFrameInfoToArray();
        for (let item of value) {
          array.arrSrc.push(item.src);
          array.arrWidth.push((item.width === undefined || item.width === null) ? 0 : item.width);
          array.arrHeight.push((item.height === undefined || item.height === null) ? 0 : item.height);
          array.arrTop.push((item.top === undefined || item.top === null) ? 0 : item.top);
          array.arrLeft.push((item.left === undefined || item.left === null) ? 0 : item.left);
          array.arrDuration.push((item.duration === undefined || item.duration === null) ? 0 : item.duration);
        }
        return array;
      }
      else {
        return undefined;
      }
    }
    else {
      return undefined;
    }
  }
}
ImageAnimatorImagesModifier.identity = Symbol('imageAnimatorImages');
class ImageAnimatorDurationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetDuration(node);
    }
    else {
      getUINativeModule().imageAnimator.setDuration(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorDurationModifier.identity = Symbol('imageAnimatorDuration');
class ImageAnimatorReverseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetReverse(node);
    }
    else {
      getUINativeModule().imageAnimator.setReverse(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorReverseModifier.identity = Symbol('imageAnimatorReverse');
class ImageAnimatorStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetState(node);
    }
    else {
      getUINativeModule().imageAnimator.setState(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorStateModifier.identity = Symbol('imageAnimatorState');
class ImageAnimatorFixedSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetFixedSize(node);
    }
    else {
      getUINativeModule().imageAnimator.setFixedSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorFixedSizeModifier.identity = Symbol('imageAnimatorFixedSize');
class ImageAnimatorFillModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetFillMode(node);
    }
    else {
      getUINativeModule().imageAnimator.setFillMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorFillModeModifier.identity = Symbol('imageAnimatorFillMode');
class ImageAnimatorIterationsModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageAnimator.resetIterations(node);
    }
    else {
      getUINativeModule().imageAnimator.setIterations(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAnimatorIterationsModeModifier.identity = Symbol('imageAnimatorIterationsMode');
class ArkImageAnimatorComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  images(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorImagesModifier.identity, ImageAnimatorImagesModifier, value);
    return this;
  }
  state(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorStateModifier.identity, ImageAnimatorStateModifier, value);
    return this;
  }
  duration(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorDurationModifier.identity, ImageAnimatorDurationModifier, value);
    return this;
  }
  reverse(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorReverseModifier.identity, ImageAnimatorReverseModifier, value);
    return this;
  }
  fixedSize(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorFixedSizeModifier.identity, ImageAnimatorFixedSizeModifier, value);
    return this;
  }
  preDecode(value) {
    throw new Error('Method not implemented.');
  }
  fillMode(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorFillModeModifier.identity, ImageAnimatorFillModeModifier, value);
    return this;
  }
  iterations(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAnimatorIterationsModeModifier.identity, ImageAnimatorIterationsModeModifier, value);
    return this;
  }
  onStart(event) {
    throw new Error('Method not implemented.');
  }
  onPause(event) {
    throw new Error('Method not implemented.');
  }
  onRepeat(event) {
    throw new Error('Method not implemented.');
  }
  onCancel(event) {
    throw new Error('Method not implemented.');
  }
  onFinish(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ImageAnimator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageAnimatorComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ImageSpanObjectFitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageSpan.resetObjectFit(node);
    }
    else {
      getUINativeModule().imageSpan.setObjectFit(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageSpanObjectFitModifier.identity = Symbol('imageSpanObjectFit');
class ImageSpanVerticalAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().imageSpan.resetVerticalAlign(node);
    }
    else {
      getUINativeModule().imageSpan.setVerticalAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageSpanVerticalAlignModifier.identity = Symbol('imageSpanVerticalAlign');
class ArkImageSpanComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  objectFit(value) {
    modifierWithKey(this._modifiersWithKeys, ImageSpanObjectFitModifier.identity, ImageSpanObjectFitModifier, value);
    return this;
  }
  verticalAlign(value) {
    modifierWithKey(this._modifiersWithKeys, ImageSpanVerticalAlignModifier.identity, ImageSpanVerticalAlignModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.ImageSpan.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkImageSpanComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class PatternLockActiveColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetActiveColor(node);
    }
    else {
      getUINativeModule().patternLock.setActiveColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockActiveColorModifier.identity = Symbol('patternLockActiveColor');
class PatternLockSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetSelectedColor(node);
    }
    else {
      getUINativeModule().patternLock.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockSelectedColorModifier.identity = Symbol('patternLockSelectedColor');
class PatternLockPathColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetPathColor(node);
    }
    else {
      getUINativeModule().patternLock.setPathColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockPathColorModifier.identity = Symbol('patternLockPathColor');
class PatternLockRegularColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetRegularColor(node);
    }
    else {
      getUINativeModule().patternLock.setRegularColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockRegularColorModifier.identity = Symbol('patternLockRegularColor');
class PatternLockSideLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetSideLength(node);
    }
    else {
      getUINativeModule().patternLock.setSideLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockSideLengthModifier.identity = Symbol('patternLockSideLength');
class PatternLockPathStrokeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetPathStrokeWidth(node);
    }
    else {
      getUINativeModule().patternLock.setPathStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PatternLockPathStrokeModifier.identity = Symbol('patternLockPathStroke');
class PatternLockCircleRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetCircleRadius(node);
    }
    else {
      getUINativeModule().patternLock.setCircleRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PatternLockCircleRadiusModifier.identity = Symbol('patternLockCircleRadius');
class PatternLockAutoResetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().patternLock.resetAutoReset(node);
    }
    else {
      getUINativeModule().patternLock.setAutoReset(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PatternLockAutoResetModifier.identity = Symbol('patternlockautoreset');
class ArkPatternLockComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  sideLength(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockSideLengthModifier.identity, PatternLockSideLengthModifier, value);
    return this;
  }
  circleRadius(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockCircleRadiusModifier.identity, PatternLockCircleRadiusModifier, value);
    return this;
  }
  regularColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockRegularColorModifier.identity, PatternLockRegularColorModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockSelectedColorModifier.identity, PatternLockSelectedColorModifier, value);
    return this;
  }
  activeColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockActiveColorModifier.identity, PatternLockActiveColorModifier, value);
    return this;
  }
  pathColor(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathColorModifier.identity, PatternLockPathColorModifier, value);
    return this;
  }
  pathStrokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockPathStrokeModifier.identity, PatternLockPathStrokeModifier, value);
    return this;
  }
  autoReset(value) {
    modifierWithKey(this._modifiersWithKeys, PatternLockAutoResetModifier.identity, PatternLockAutoResetModifier, value);
    return this;
  }
  onPatternComplete(callback) {
    throw new Error('Method not implemented.');
  }
  onDotConnect(callback) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.PatternLock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPatternLockComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class RichEditorCopyOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().richEditor.resetCopyOptions(node);
    }
    else {
      getUINativeModule().richEditor.setCopyOptions(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RichEditorCopyOptionsModifier.identity = Symbol('richEditorCopyOptions');
class ArkRichEditorComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  enableDataDetector(enable) {
    throw new Error('Method not implemented.');
  }
  dataDetectorConfig(config) {
    throw new Error('Method not implemented.');
  }
  copyOptions(value) {
    modifierWithKey(this._modifiersWithKeys, RichEditorCopyOptionsModifier.identity, RichEditorCopyOptionsModifier, value);
    return this;
  }
  onPaste(callback) {
    throw new Error('Method not implemented.');
  }
  onReady(callback) {
    throw new Error('Method not implemented.');
  }
  onSelect(callback) {
    throw new Error('Method not implemented.');
  }
  aboutToIMEInput(callback) {
    throw new Error('Method not implemented.');
  }
  onIMEInputComplete(callback) {
    throw new Error('Method not implemented.');
  }
  aboutToDelete(callback) {
    throw new Error('Method not implemented.');
  }
  onDeleteComplete(callback) {
    throw new Error('Method not implemented.');
  }
  bindSelectionMenu(spanType, content, responseType, options) {
    throw new Error('Method not implemented.');
  }
  customKeyboard(value) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.RichEditor.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRichEditorComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class RowAlignItemsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().row.resetAlignItems(node);
    }
    else {
      getUINativeModule().row.setAlignItems(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RowAlignItemsModifier.identity = Symbol('rowAlignItems');
class RowJustifyContentlModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().row.resetJustifyContent(node);
    }
    else {
      getUINativeModule().row.setJustifyContent(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RowJustifyContentlModifier.identity = Symbol('rowJustifyContent');
class ArkRowComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  alignItems(value) {
    modifierWithKey(this._modifiersWithKeys, RowAlignItemsModifier.identity, RowAlignItemsModifier, value);
    return this;
  }
  justifyContent(value) {
    modifierWithKey(this._modifiersWithKeys, RowJustifyContentlModifier.identity, RowJustifyContentlModifier, value);
    return this;
  }
  pointLight(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Row.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class RowSplitResizeableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rowSplit.resetResizeable(node);
    }
    else {
      getUINativeModule().rowSplit.setResizeable(node, this.value);
    }
  }
}
RowSplitResizeableModifier.identity = Symbol('rowSplitResizeable');
class ArkRowSplitComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  resizeable(value) {
    modifierWithKey(this._modifiersWithKeys, RowSplitResizeableModifier.identity, RowSplitResizeableModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.RowSplit.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRowSplitComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class SearchSelectionMenuHiddenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSelectionMenuHidden(node);
    }
    else {
      getUINativeModule().search.setSelectionMenuHidden(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchSelectionMenuHiddenModifier.identity = Symbol('searchSelectionMenuHidden');
class SearchCaretStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCaretStyle(node);
    }
    else {
      getUINativeModule().search.setCaretStyle(node, this.value.width, this.value.color);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}
SearchCaretStyleModifier.identity = Symbol('searchCaretStyle');
class SearchEnableKeyboardOnFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetEnableKeyboardOnFocus(node);
    }
    else {
      getUINativeModule().search.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchEnableKeyboardOnFocusModifier.identity = Symbol('searchEnableKeyboardOnFocus');
class SearchSearchIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchIcon(node);
    }
    else {
      getUINativeModule().search.setSearchIcon(node, this.value.size, this.value.color, this.value.src);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.src, this.value.src);
  }
}
SearchSearchIconModifier.identity = Symbol('searchSearchIcon');
class SearchPlaceholderFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetPlaceholderFont(node);
    }
    else {
      getUINativeModule().search.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}
SearchPlaceholderFontModifier.identity = Symbol('searchPlaceholderFont');
class SearchSearchButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetSearchButton(node);
    }
    else {
      getUINativeModule().search.setSearchButton(node, this.value.value, this.value.fontSize, this.value.fontColor);
    }
  }
  checkObjectDiff() {
    return this.stageValue.value !== this.value.value ||
      !isBaseOrResourceEqual(this.stageValue.fontSize, this.value.fontSize) ||
      !isBaseOrResourceEqual(this.stageValue.fontColor, this.value.fontColor);
  }
}
SearchSearchButtonModifier.identity = Symbol('searchSearchButton');
class SearchFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetFontColor(node);
    }
    else {
      getUINativeModule().search.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchFontColorModifier.identity = Symbol('searchFontColor');
class SearchCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetCopyOption(node);
    }
    else {
      getUINativeModule().search.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchCopyOptionModifier.identity = Symbol('searchCopyOption');
class SearchTextFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetTextFont(node);
    }
    else {
      getUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    return this.stageValue.weight !== this.value.weight ||
      this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
      !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
  }
}
SearchTextFontModifier.identity = Symbol('searchTextFont');
class SearchPlaceholderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetPlaceholderColor(node);
    }
    else {
      getUINativeModule().search.setPlaceholderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SearchPlaceholderColorModifier.identity = Symbol('searchPlaceholderColor');
class SearchCancelButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().search.resetCancelButton(node);
    }
    else {
      getUINativeModule().search.setCancelButton(node, this.value.style,
        (_a = this.value.icon) === null || _a === void 0 ? void 0 : _a.size,
        (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.color,
        (_c = this.value.icon) === null || _c === void 0 ? void 0 : _c.src);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f;
    return this.stageValue.style !== this.value.style ||
      !isBaseOrResourceEqual((_a = this.stageValue.icon) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.size) ||
      !isBaseOrResourceEqual((_c = this.stageValue.icon) === null || _c === void 0 ? void 0 : _c.color, (_d = this.value.icon) === null || _d === void 0 ? void 0 : _d.color) ||
      !isBaseOrResourceEqual((_e = this.stageValue.icon) === null || _e === void 0 ? void 0 : _e.src, (_f = this.value.icon) === null || _f === void 0 ? void 0 : _f.src);
  }
}
SearchCancelButtonModifier.identity = Symbol('searchCancelButton');
class SearchTextAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().search.resetTextAlign(node);
    }
    else {
      getUINativeModule().search.setTextAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
SearchTextAlignModifier.identity = Symbol('searchTextAlign');
class ArkSearchComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onEditChange(callback) {
    throw new Error('Method not implemented.');
  }
  type(value) {
    throw new Error('Method not implemented.');
  }
  maxLength(value) {
    throw new Error('Method not implemented.');
  }
  onEditChanged(callback) {
    throw new Error('Method not implemented.');
  }
  customKeyboard(event) {
    throw new Error('Method not implemented.');
  }
  showUnit(event) {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback) {
    throw new Error('Method not implemented.');
  }
  onCopy(callback) {
    throw new Error('Method not implemented.');
  }
  onCut(callback) {
    throw new Error('Method not implemented.');
  }
  onSubmit(callback) {
    throw new Error('Method not implemented.');
  }
  onPaste(callback) {
    throw new Error('Method not implemented.');
  }
  showCounter(value) {
    throw new Error('Method not implemented.');
  }
  searchButton(value, option) {
    let searchButton = new ArkSearchButton();
    searchButton.value = value;
    searchButton.fontColor = option === null || option === void 0 ? void 0 : option.fontColor;
    searchButton.fontSize = option === null || option === void 0 ? void 0 : option.fontSize;
    modifierWithKey(this._modifiersWithKeys, SearchSearchButtonModifier.identity, SearchSearchButtonModifier, searchButton);
    return this;
  }
  selectionMenuHidden(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSelectionMenuHiddenModifier.identity, SearchSelectionMenuHiddenModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value) {
    modifierWithKey(this._modifiersWithKeys, SearchEnableKeyboardOnFocusModifier.identity, SearchEnableKeyboardOnFocusModifier, value);
    return this;
  }
  caretStyle(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCaretStyleModifier.identity, SearchCaretStyleModifier, value);
    return this;
  }
  cancelButton(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCancelButtonModifier.identity, SearchCancelButtonModifier, value);
    return this;
  }
  searchIcon(value) {
    modifierWithKey(this._modifiersWithKeys, SearchSearchIconModifier.identity, SearchSearchIconModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchFontColorModifier.identity, SearchFontColorModifier, value);
    return this;
  }
  placeholderColor(value) {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderColorModifier.identity, SearchPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value) {
    modifierWithKey(this._modifiersWithKeys, SearchPlaceholderFontModifier.identity, SearchPlaceholderFontModifier, value);
    return this;
  }
  textFont(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextFontModifier.identity, SearchTextFontModifier, value);
    return this;
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, SearchCopyOptionModifier.identity, SearchCopyOptionModifier, value);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, SearchTextAlignModifier.identity, SearchTextAlignModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Search.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSearchComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class SpanFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontSize(node);
    }
    else {
      getUINativeModule().span.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanFontSizeModifier.identity = Symbol('spanFontSize');
class SpanFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontFamily(node);
    }
    else {
      getUINativeModule().span.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanFontFamilyModifier.identity = Symbol('spanFontFamily');
class SpanLineHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetLineHeight(node);
    }
    else {
      getUINativeModule().span.setLineHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanLineHeightModifier.identity = Symbol('spanLineHeight');
class SpanFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontStyle(node);
    }
    else {
      getUINativeModule().span.setFontStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanFontStyleModifier.identity = Symbol('spanFontStyle');
class SpanTextCaseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetTextCase(node);
    }
    else {
      getUINativeModule().span.setTextCase(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanTextCaseModifier.identity = Symbol('spanTextCase');
class SpanFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontColor(node);
    }
    else {
      getUINativeModule().span.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpanFontColorModifier.identity = Symbol('spanFontColor');
class SpanLetterSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetLetterSpacing(node);
    }
    else {
      getUINativeModule().span.setLetterSpacing(node, this.value);
    }
  }
}
SpanLetterSpacingModifier.identity = Symbol('spanLetterSpacing');
class SpanFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFont(node);
    }
    else {
      getUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
      isResourceEqual(this.stageValue.size, this.value.size)) ||
      (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
        this.stageValue.size === this.value.size)) &&
      ((isResource(this.stageValue.family) && isResource(this.value.family) &&
        isResourceEqual(this.stageValue.family, this.value.family)) ||
        (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
          this.stageValue.family === this.value.family))) {
      return false;
    }
    else {
      return true;
    }
  }
}
SpanFontModifier.identity = Symbol('spanFont');
class SpanDecorationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetDecoration(node);
    }
    else {
      getUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.type !== this.value.type) {
      return true;
    }
    if (isResource(this.stageValue.color) && isResource(this.value.color)) {
      return !isResourceEqual(this.stageValue.color, this.value.color);
    }
    else if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    }
    else {
      return true;
    }
  }
}
SpanDecorationModifier.identity = Symbol('spanDecoration');
class SpanFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontWeight(node);
    }
    else {
      getUINativeModule().span.setFontWeight(node, this.value);
    }
  }
}
SpanFontWeightModifier.identity = Symbol('spanfontweight');
class ArkSpanComponent {
  constructor(nativePtr) {
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
  }
  applyModifierPatch() {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  width(value) {
    throw new Error('Method not implemented.');
  }
  height(value) {
    throw new Error('Method not implemented.');
  }
  expandSafeArea(types, edges) {
    throw new Error('Method not implemented.');
  }
  responseRegion(value) {
    throw new Error('Method not implemented.');
  }
  mouseResponseRegion(value) {
    throw new Error('Method not implemented.');
  }
  size(value) {
    throw new Error('Method not implemented.');
  }
  constraintSize(value) {
    throw new Error('Method not implemented.');
  }
  touchable(value) {
    throw new Error('Method not implemented.');
  }
  hitTestBehavior(value) {
    throw new Error('Method not implemented.');
  }
  layoutWeight(value) {
    throw new Error('Method not implemented.');
  }
  padding(value) {
    throw new Error('Method not implemented.');
  }
  margin(value) {
    throw new Error('Method not implemented.');
  }
  background(builder, options) {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value) {
    throw new Error('Method not implemented.');
  }
  backgroundImage(src, repeat) {
    throw new Error('Method not implemented.');
  }
  backgroundImageSize(value) {
    throw new Error('Method not implemented.');
  }
  backgroundImagePosition(value) {
    throw new Error('Method not implemented.');
  }
  backgroundBlurStyle(value, options) {
    throw new Error('Method not implemented.');
  }
  foregroundBlurStyle(value, options) {
    throw new Error('Method not implemented.');
  }
  opacity(value) {
    throw new Error('Method not implemented.');
  }
  border(value) {
    throw new Error('Method not implemented.');
  }
  borderStyle(value) {
    throw new Error('Method not implemented.');
  }
  borderWidth(value) {
    throw new Error('Method not implemented.');
  }
  borderColor(value) {
    throw new Error('Method not implemented.');
  }
  borderRadius(value) {
    throw new Error('Method not implemented.');
  }
  borderImage(value) {
    throw new Error('Method not implemented.');
  }
  foregroundColor(value) {
    throw new Error('Method not implemented.');
  }
  onClick(event) {
    throw new Error('Method not implemented.');
  }
  onHover(event) {
    throw new Error('Method not implemented.');
  }
  hoverEffect(value) {
    throw new Error('Method not implemented.');
  }
  onMouse(event) {
    throw new Error('Method not implemented.');
  }
  onTouch(event) {
    throw new Error('Method not implemented.');
  }
  onKeyEvent(event) {
    throw new Error('Method not implemented.');
  }
  focusable(value) {
    throw new Error('Method not implemented.');
  }
  onFocus(event) {
    throw new Error('Method not implemented.');
  }
  onBlur(event) {
    throw new Error('Method not implemented.');
  }
  tabIndex(index) {
    throw new Error('Method not implemented.');
  }
  defaultFocus(value) {
    throw new Error('Method not implemented.');
  }
  groupDefaultFocus(value) {
    throw new Error('Method not implemented.');
  }
  focusOnTouch(value) {
    throw new Error('Method not implemented.');
  }
  animation(value) {
    throw new Error('Method not implemented.');
  }
  transition(value) {
    throw new Error('Method not implemented.');
  }
  gesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  priorityGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  parallelGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  blur(value) {
    throw new Error('Method not implemented.');
  }
  linearGradientBlur(value, options) {
    throw new Error('Method not implemented.');
  }
  brightness(value) {
    throw new Error('Method not implemented.');
  }
  contrast(value) {
    throw new Error('Method not implemented.');
  }
  grayscale(value) {
    throw new Error('Method not implemented.');
  }
  colorBlend(value) {
    throw new Error('Method not implemented.');
  }
  saturate(value) {
    throw new Error('Method not implemented.');
  }
  sepia(value) {
    throw new Error('Method not implemented.');
  }
  invert(value) {
    throw new Error('Method not implemented.');
  }
  hueRotate(value) {
    throw new Error('Method not implemented.');
  }
  useEffect(value) {
    throw new Error('Method not implemented.');
  }
  backdropBlur(value) {
    throw new Error('Method not implemented.');
  }
  renderGroup(value) {
    throw new Error('Method not implemented.');
  }
  translate(value) {
    throw new Error('Method not implemented.');
  }
  scale(value) {
    throw new Error('Method not implemented.');
  }
  gridSpan(value) {
    throw new Error('Method not implemented.');
  }
  gridOffset(value) {
    throw new Error('Method not implemented.');
  }
  rotate(value) {
    throw new Error('Method not implemented.');
  }
  transform(value) {
    throw new Error('Method not implemented.');
  }
  onAppear(event) {
    throw new Error('Method not implemented.');
  }
  onDisAppear(event) {
    throw new Error('Method not implemented.');
  }
  onAreaChange(event) {
    throw new Error('Method not implemented.');
  }
  visibility(value) {
    throw new Error('Method not implemented.');
  }
  flexGrow(value) {
    throw new Error('Method not implemented.');
  }
  flexShrink(value) {
    throw new Error('Method not implemented.');
  }
  flexBasis(value) {
    throw new Error('Method not implemented.');
  }
  alignSelf(value) {
    throw new Error('Method not implemented.');
  }
  displayPriority(value) {
    throw new Error('Method not implemented.');
  }
  zIndex(value) {
    throw new Error('Method not implemented.');
  }
  sharedTransition(id, options) {
    throw new Error('Method not implemented.');
  }
  direction(value) {
    throw new Error('Method not implemented.');
  }
  align(value) {
    throw new Error('Method not implemented.');
  }
  position(value) {
    throw new Error('Method not implemented.');
  }
  markAnchor(value) {
    throw new Error('Method not implemented.');
  }
  offset(value) {
    throw new Error('Method not implemented.');
  }
  enabled(value) {
    throw new Error('Method not implemented.');
  }
  useSizeType(value) {
    throw new Error('Method not implemented.');
  }
  alignRules(value) {
    throw new Error('Method not implemented.');
  }
  aspectRatio(value) {
    throw new Error('Method not implemented.');
  }
  clickEffect(value) {
    throw new Error('Method not implemented.');
  }
  onDragStart(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnter(event) {
    throw new Error('Method not implemented.');
  }
  onDragMove(event) {
    throw new Error('Method not implemented.');
  }
  onDragLeave(event) {
    throw new Error('Method not implemented.');
  }
  onDrop(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnd(event) {
    throw new Error('Method not implemented.');
  }
  allowDrop(value) {
    throw new Error('Method not implemented.');
  }
  draggable(value) {
    throw new Error('Method not implemented.');
  }
  overlay(value, options) {
    throw new Error('Method not implemented.');
  }
  linearGradient(value) {
    throw new Error('Method not implemented.');
  }
  sweepGradient(value) {
    throw new Error('Method not implemented.');
  }
  radialGradient(value) {
    throw new Error('Method not implemented.');
  }
  motionPath(value) {
    throw new Error('Method not implemented.');
  }
  shadow(value) {
    throw new Error('Method not implemented.');
  }
  mask(value) {
    throw new Error('Method not implemented.');
  }
  key(value) {
    throw new Error('Method not implemented.');
  }
  id(value) {
    throw new Error('Method not implemented.');
  }
  geometryTransition(id) {
    throw new Error('Method not implemented.');
  }
  bindPopup(show, popup) {
    throw new Error('Method not implemented.');
  }
  bindMenu(content, options) {
    throw new Error('Method not implemented.');
  }
  bindContextMenu(content, responseType, options) {
    throw new Error('Method not implemented.');
  }
  bindContentCover(isShow, builder, type) {
    throw new Error('Method not implemented.');
  }
  blendMode(value) {
    throw new Error('Method not implemented.');
  }
  clip(value) {
    throw new Error('Method not implemented.');
  }
  bindSheet(isShow, builder, options) {
    throw new Error('Method not implemented.');
  }
  stateStyles(value) {
    throw new Error('Method not implemented.');
  }
  restoreId(value) {
    throw new Error('Method not implemented.');
  }
  onVisibleAreaChange(ratios, event) {
    throw new Error('Method not implemented.');
  }
  sphericalEffect(value) {
    throw new Error('Method not implemented.');
  }
  lightUpEffect(value) {
    throw new Error('Method not implemented.');
  }
  pixelStretchEffect(options) {
    throw new Error('Method not implemented.');
  }
  keyboardShortcut(value, keys, action) {
    throw new Error('Method not implemented.');
  }
  accessibilityGroup(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityText(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityDescription(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityLevel(value) {
    throw new Error('Method not implemented.');
  }
  obscured(reasons) {
    throw new Error('Method not implemented.');
  }
  reuseId(id) {
    throw new Error('Method not implemented.');
  }
  renderFit(fitMode) {
    throw new Error('Method not implemented.');
  }
  attributeModifier(modifier) {
    return this;
  }
  decoration(value) {
    modifierWithKey(this._modifiersWithKeys, SpanDecorationModifier.identity, SpanDecorationModifier, value);
    return this;
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontModifier.identity, SpanFontModifier, value);
    return this;
  }
  lineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, SpanLineHeightModifier.identity, SpanLineHeightModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontSizeModifier.identity, SpanFontSizeModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontColorModifier.identity, SpanFontColorModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontStyleModifier.identity, SpanFontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier, value);
    return this;
  }
  letterSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, SpanLetterSpacingModifier.identity, SpanLetterSpacingModifier, value);
    return this;
  }
  textCase(value) {
    modifierWithKey(this._modifiersWithKeys, SpanTextCaseModifier.identity, SpanTextCaseModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Span.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSpanComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class SideBarContainerPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetSideBarPosition(node);
    }
    else {
      getUINativeModule().sideBarContainer.setSideBarPosition(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerPositionModifier.identity = Symbol('sideBarContainerPosition');
class SideBarContainerAutoHideModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetAutoHide(node);
    }
    else {
      getUINativeModule().sideBarContainer.setAutoHide(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerAutoHideModifier.identity = Symbol('sideBarContainerautoHide');
class SideBarContainerShowSideBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetShowSideBar(node);
    }
    else {
      getUINativeModule().sideBarContainer.setShowSideBar(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerShowSideBarModifier.identity = Symbol('sideBarContainerShowSideBar');
class SideBarContainerMaxSideBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
    }
    else {
      getUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerMaxSideBarWidthModifier.identity = Symbol('sideBarContainerMaxSideBarWidth');
class SideBarContainerWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetSideBarWidth(node);
    }
    else {
      getUINativeModule().sideBarContainer.setSideBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerWidthModifier.identity = Symbol('sideBarContainerWidth');
class SideBarContainerMinContentWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMinContentWidth(node);
    }
    else {
      getUINativeModule().sideBarContainer.setMinContentWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerMinContentWidthModifier.identity = Symbol('sideBarContainerMinContentWidth');
class SideBarContainerShowControlButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetShowControlButton(node);
    }
    else {
      getUINativeModule().sideBarContainer.setShowControlButton(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerShowControlButtonModifier.identity = Symbol('sideBarContainerShowControlButton');
class SideBarContainerMinSideBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
    }
    else {
      getUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SideBarContainerMinSideBarWidthModifier.identity = Symbol('sideBarContainerMinSideBarWidth');
class SideBarContainerControlButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().sideBarContainer.resetControlButton(node);
    }
    else {
      getUINativeModule().sideBarContainer.setControlButton(node, this.value.left,
        this.value.top, this.value.width, this.value.height, (_a = this.value.icons) === null ||
        _a === void 0 ? void 0 : _a.shown, (_b = this.value.icons) === null ||
        _b === void 0 ? void 0 : _b.hidden, (_c = this.value.icons) === null ||
        _c === void 0 ? void 0 : _c.switching);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f;
    if (!(this.stageValue.left === this.value.left &&
      this.stageValue.top === this.value.top &&
      this.stageValue.width === this.value.width &&
      this.stageValue.height === this.value.height)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_a = this.stageValue.icons) === null || _a === void 0 ? void 0 : _a.shown, (_b = this.value.icons) === null ||
      _b === void 0 ? void 0 : _b.shown) ||
        !isBaseOrResourceEqual((_c = this.stageValue.icons) === null || _c === void 0 ? void 0 : _c.hidden, (_d = this.value.icons) === null ||
        _d === void 0 ? void 0 : _d.hidden) ||
        !isBaseOrResourceEqual((_e = this.stageValue.icons) === null || _e === void 0 ? void 0 : _e.switching, (_f = this.value.icons) === null ||
        _f === void 0 ? void 0 : _f.switching);
    }
  }
}
SideBarContainerControlButtonModifier.identity = Symbol('sideBarContainercontrolButton');
class SideBarContainerDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetDivider(node);
    }
    else {
      if (!this.value || !isObject(this.value) || !this.value.strokeWidth) {
        getUINativeModule().sideBarContainer.resetDivider(node);
      }
      else {
        getUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
      }
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.startMargin, this.value.startMargin) ||
      !isBaseOrResourceEqual(this.stageValue.endMargin, this.value.endMargin);
  }
}
SideBarContainerDividerModifier.identity = Symbol('sideBarContainerdivider');
class ArkSideBarContainerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  autoHide(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerAutoHideModifier.identity, SideBarContainerAutoHideModifier, value);
    return this;
  }
  showSideBar(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerShowSideBarModifier.identity, SideBarContainerShowSideBarModifier, value);
    return this;
  }
  maxSideBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMaxSideBarWidthModifier.identity, SideBarContainerMaxSideBarWidthModifier, value);
    return this;
  }
  minSideBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMinSideBarWidthModifier.identity, SideBarContainerMinSideBarWidthModifier, value);
    return this;
  }
  minContentWidth(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerMinContentWidthModifier.identity, SideBarContainerMinContentWidthModifier, value);
    return this;
  }
  controlButton(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerControlButtonModifier.identity, SideBarContainerControlButtonModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerDividerModifier.identity, SideBarContainerDividerModifier, value);
    return this;
  }
  sideBarPosition(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerPositionModifier.identity, SideBarContainerPositionModifier, value);
    return this;
  }
  sideBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerWidthModifier.identity, SideBarContainerWidthModifier, value);
    return this;
  }
  showControlButton(value) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerShowControlButtonModifier.identity, SideBarContainerShowControlButtonModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.SideBarContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSideBarContainerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkStackComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  alignContent(value) {
    modifierWithKey(this._modifiersWithKeys, StackAlignContentModifier.identity, StackAlignContentModifier, value);
    return this;
  }
}
class StackAlignContentModifier extends ModifierWithKey {
  constructor(nativePtr) {
    super(nativePtr);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stack.resetAlignContent(node);
    }
    else {
      getUINativeModule().stack.setAlignContent(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
StackAlignContentModifier.identity = Symbol('stackAlignContent');
// @ts-ignore
globalThis.Stack.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStackComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class FontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontColor(node);
    }
    else {
      getUINativeModule().text.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FontColorModifier.identity = Symbol('textFontColor');
class FontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontSize(node);
    }
    else {
      getUINativeModule().text.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FontSizeModifier.identity = Symbol('textFontSize');
class FontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontWeight(node);
    }
    else {
      getUINativeModule().text.setFontWeight(node, this.value);
    }
  }
}
FontWeightModifier.identity = Symbol('textFontWeight');
class FontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontStyle(node);
    }
    else {
      getUINativeModule().text.setFontStyle(node, this.value);
    }
  }
}
FontStyleModifier.identity = Symbol('textFontStyle');
class TextAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextAlign(node);
    }
    else {
      getUINativeModule().text.setTextAlign(node, this.value);
    }
  }
}
TextAlignModifier.identity = Symbol('textAlign');
class TextHeightAdaptivePolicyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetHeightAdaptivePolicy(node);
    }
    else {
      getUINativeModule().text.setHeightAdaptivePolicy(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextHeightAdaptivePolicyModifier.identity = Symbol('textHeightAdaptivePolicy');
class TextDraggableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetDraggable(node);
    }
    else {
      getUINativeModule().text.setDraggable(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextDraggableModifier.identity = Symbol('textDraggable');
class TextMinFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMinFontSize(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMinFontSize(node);
    }
    else {
      getUINativeModule().text.setMinFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMinFontSizeModifier.identity = Symbol('textMinFontSize');
class TextMaxFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMaxFontSize(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMaxFontSize(node);
    }
    else {
      getUINativeModule().text.setMaxFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMaxFontSizeModifier.identity = Symbol('textMaxFontSize');
class TextLineHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLineHeight(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetLineHeight(node);
    }
    else {
      getUINativeModule().text.setLineHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextLineHeightModifier.identity = Symbol('textLineHeight');
class TextCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetCopyOption(node);
    }
    else {
      getUINativeModule().text.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextCopyOptionModifier.identity = Symbol('textCopyOption');
class TextFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontFamily(node);
    }
    else if (!isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetFontFamily(node);
    }
    else {
      getUINativeModule().text.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextFontFamilyModifier.identity = Symbol('textFontFamily');
class TextMaxLinesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMaxLines(node);
    }
    else if (!isNumber(this.value)) {
      getUINativeModule().text.resetMaxLines(node);
    }
    else {
      getUINativeModule().text.setMaxLines(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMaxLinesModifier.identity = Symbol('textMaxLines');
class TextLetterSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLetterSpacing(node);
    }
    else if (!isNumber(this.value) && !isString(this.value)) {
      getUINativeModule().text.resetLetterSpacing(node);
    }
    else {
      getUINativeModule().text.setLetterSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextLetterSpacingModifier.identity = Symbol('textLetterSpacing');
class TextTextOverflowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextOverflow(node);
    }
    else {
      getUINativeModule().text.setTextOverflow(node, this.value.overflow);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.overflow, this.value.overflow);
  }
}
TextTextOverflowModifier.identity = Symbol('textTextOverflow');
class TextBaselineOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetBaselineOffset(node);
    }
    else if (!isNumber(this.value) && !isString(this.value)) {
      getUINativeModule().text.resetBaselineOffset(node);
    }
    else {
      getUINativeModule().text.setBaselineOffset(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextBaselineOffsetModifier.identity = Symbol('textBaselineOffset');
class TextTextCaseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextCase(node);
    }
    else {
      getUINativeModule().text.setTextCase(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTextCaseModifier.identity = Symbol('textTextCase');
class TextTextIndentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextIndent(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetTextIndent(node);
    }
    else {
      getUINativeModule().text.setTextIndent(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTextIndentModifier.identity = Symbol('textTextIndent');
class TextTextShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextShadow(node);
    }
    else {
      let shadow = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        getUINativeModule().text.resetTextShadow(node);
      }
      else {
        getUINativeModule().text.setTextShadow(node, shadow.radius, shadow.type, shadow.color,
          shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
      }
    }
  }
  checkObjectDiff() {
    let checkDiff = true;
    let arkShadow = new ArkShadowInfoToArray();
    if (Object.getPrototypeOf(this.stageValue).constructor === Object &&
      Object.getPrototypeOf(this.value).constructor === Object) {
      checkDiff = arkShadow.checkDiff(this.stageValue, this.value);
    }
    else if (Object.getPrototypeOf(this.stageValue).constructor === Array &&
      Object.getPrototypeOf(this.value).constructor === Array &&
      this.stageValue.length === this.value.length) {
      let isDiffItem = false;
      for (let i = 0; i < this.value.length; i++) {
        if (arkShadow.checkDiff(this.stageValue[i], this.value[1])) {
          isDiffItem = true;
          break;
        }
      }
      if (!isDiffItem) {
        checkDiff = false;
      }
    }
    return checkDiff;
  }
}
TextTextShadowModifier.identity = Symbol('textTextShadow');
class TextDecorationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetDecoration(node);
    }
    else {
      getUINativeModule().text.setDecoration(node, this.value.type, this.value.color);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.type !== this.value.type) {
      return true;
    }
    if (isResource(this.stageValue.color) && isResource(this.value.color)) {
      return !isResourceEqual(this.stageValue.color, this.value.color);
    }
    else if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
      return !(this.stageValue.color === this.value.color);
    }
    else {
      return true;
    }
  }
}
TextDecorationModifier.identity = Symbol('textDecoration');
class TextFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFont(node);
    }
    else {
      getUINativeModule().text.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style) {
      return true;
    }
    if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
      isResourceEqual(this.stageValue.size, this.value.size)) ||
      (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
        this.stageValue.size === this.value.size)) &&
      ((isResource(this.stageValue.family) && isResource(this.value.family) &&
        isResourceEqual(this.stageValue.family, this.value.family)) ||
        (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
          this.stageValue.family === this.value.family))) {
      return false;
    }
    else {
      return true;
    }
  }
}
TextFontModifier.identity = Symbol('textFont');
class ArkTextComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  enableDataDetector(enable) {
    throw new Error('Method not implemented.');
  }
  dataDetectorConfig(config) {
    throw new Error('Method not implemented.');
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, TextFontModifier.identity, TextFontModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, FontColorModifier.identity, FontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, FontSizeModifier.identity, FontSizeModifier, value);
    return this;
  }
  minFontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextMinFontSizeModifier.identity, TextMinFontSizeModifier, value);
    return this;
  }
  maxFontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextMaxFontSizeModifier.identity, TextMaxFontSizeModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, FontStyleModifier.identity, FontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    let fontWeightStr = '400';
    if (isNumber(value)) {
      fontWeightStr = value.toString();
    }
    else if (isString(value)) {
      fontWeightStr = String(value);
    }
    modifierWithKey(this._modifiersWithKeys, FontWeightModifier.identity, FontWeightModifier, fontWeightStr);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier, value);
    return this;
  }
  lineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextLineHeightModifier.identity, TextLineHeightModifier, value);
    return this;
  }
  textOverflow(value) {
    modifierWithKey(this._modifiersWithKeys, TextTextOverflowModifier.identity, TextTextOverflowModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextFontFamilyModifier.identity, TextFontFamilyModifier, value);
    return this;
  }
  maxLines(value) {
    modifierWithKey(this._modifiersWithKeys, TextMaxLinesModifier.identity, TextMaxLinesModifier, value);
    return this;
  }
  decoration(value) {
    modifierWithKey(this._modifiersWithKeys, TextDecorationModifier.identity, TextDecorationModifier, value);
    return this;
  }
  letterSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, TextLetterSpacingModifier.identity, TextLetterSpacingModifier, value);
    return this;
  }
  textCase(value) {
    modifierWithKey(this._modifiersWithKeys, TextTextCaseModifier.identity, TextTextCaseModifier, value);
    return this;
  }
  baselineOffset(value) {
    modifierWithKey(this._modifiersWithKeys, TextBaselineOffsetModifier.identity, TextBaselineOffsetModifier, value);
    return this;
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, TextCopyOptionModifier.identity, TextCopyOptionModifier, value);
    return this;
  }
  draggable(value) {
    modifierWithKey(this._modifiersWithKeys, TextDraggableModifier.identity, TextDraggableModifier, value);
    return this;
  }
  textShadow(value) {
    modifierWithKey(this._modifiersWithKeys, TextTextShadowModifier.identity, TextTextShadowModifier, value);
    return this;
  }
  heightAdaptivePolicy(value) {
    modifierWithKey(this._modifiersWithKeys, TextHeightAdaptivePolicyModifier.identity, TextHeightAdaptivePolicyModifier, value);
    return this;
  }
  textIndent(value) {
    modifierWithKey(this._modifiersWithKeys, TextTextIndentModifier.identity, TextTextIndentModifier, value);
    return this;
  }
  wordBreak(value) {
    throw new Error('Method not implemented.');
  }
  onCopy(callback) {
    throw new Error('Method not implemented.');
  }
  selection(selectionStart, selectionEnd) {
    throw new Error('Method not implemented.');
  }
  ellipsisMode(value) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Text.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class TextAreaFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetFontStyle(node);
    }
    else {
      getUINativeModule().textArea.setFontStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaFontStyleModifier.identity = Symbol('textAreaFontStyle');
class TextAreaCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetCopyOption(node);
    }
    else {
      getUINativeModule().textArea.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaCopyOptionModifier.identity = Symbol('textAreaCopyOption');
class TextAreaMaxLinesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetMaxLines(node);
    }
    else {
      getUINativeModule().textArea.setMaxLines(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaMaxLinesModifier.identity = Symbol('textAreaMaxLines');
class TextAreaFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetFontSize(node);
    }
    else {
      getUINativeModule().textArea.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaFontSizeModifier.identity = Symbol('textAreaFontSize');
class TextAreaPlaceholderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetPlaceholderColor(node);
    }
    else {
      getUINativeModule().textArea.setPlaceholderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaPlaceholderColorModifier.identity = Symbol('textAreaPlaceholderColor');
class TextAreaFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetFontColor(node);
    }
    else {
      getUINativeModule().textArea.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaFontColorModifier.identity = Symbol('textAreaFontColor');
class TextAreaFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetFontWeight(node);
    }
    else {
      getUINativeModule().textArea.setFontWeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaFontWeightModifier.identity = Symbol('textAreaFontWeight');
class TextAreaBarStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetBarState(node);
    }
    else {
      getUINativeModule().textArea.setBarState(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaBarStateModifier.identity = Symbol('textAreaBarState');
class TextAreaEnableKeyboardOnFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
    }
    else {
      getUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaEnableKeyboardOnFocusModifier.identity = Symbol('textAreaEnableKeyboardOnFocus');
class TextAreaFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetFontFamily(node);
    }
    else {
      getUINativeModule().textArea.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaFontFamilyModifier.identity = Symbol('textAreaFontFamily');
class TextAreaCaretColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetCaretColor(node);
    }
    else {
      getUINativeModule().textArea.setCaretColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaCaretColorModifier.identity = Symbol('textAreaCaretColor');
class TextAreaMaxLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetMaxLength(node);
    }
    else {
      getUINativeModule().textArea.setMaxLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaMaxLengthModifier.identity = Symbol('textAreaMaxLength');
class TextAreaStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetStyle(node);
    }
    else {
      getUINativeModule().textArea.setStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaStyleModifier.identity = Symbol('textAreaStyle');
class TextAreaSelectionMenuHiddenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetSelectionMenuHidden(node);
    }
    else {
      getUINativeModule().textArea.setSelectionMenuHidden(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaSelectionMenuHiddenModifier.identity = Symbol('textAreaSelectionMenuHidden');
class TextAreaPlaceholderFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetPlaceholderFont(node);
    }
    else {
      getUINativeModule().textArea.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual(this.stageValue.size, this.value.size) ||
        !isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    }
  }
}
TextAreaPlaceholderFontModifier.identity = Symbol('textAreaPlaceholderFont');
class TextAreaTextAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetTextAlign(node);
    }
    else {
      getUINativeModule().textArea.setTextAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextAreaTextAlignModifier.identity = Symbol('textAreaTextAlign');
class TextAreaShowCounterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textArea.resetShowCounter(node);
    }
    else {
      getUINativeModule().textArea.setShowCounter(node, this.value.value, this.value.options);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.value, this.value.value) ||
      !isBaseOrResourceEqual(this.stageValue.options, this.value.options);
  }
}
TextAreaShowCounterModifier.identity = Symbol('textAreaShowCounter');
class ArkTextAreaComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  type(value) {
    throw new Error('Method not implemented.');
  }
  placeholderColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderColorModifier.identity, TextAreaPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaPlaceholderFontModifier.identity, TextAreaPlaceholderFontModifier, value);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaTextAlignModifier.identity, TextAreaTextAlignModifier, value);
    return this;
  }
  caretColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaCaretColorModifier.identity, TextAreaCaretColorModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontColorModifier.identity, TextAreaFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontSizeModifier.identity, TextAreaFontSizeModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontStyleModifier.identity, TextAreaFontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontWeightModifier.identity, TextAreaFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaFontFamilyModifier.identity, TextAreaFontFamilyModifier, value);
    return this;
  }
  inputFilter(value, error) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback) {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback) {
    throw new Error('Method not implemented.');
  }
  onEditChange(callback) {
    throw new Error('Method not implemented.');
  }
  onCopy(callback) {
    throw new Error('Method not implemented.');
  }
  onCut(callback) {
    throw new Error('Method not implemented.');
  }
  onPaste(callback) {
    throw new Error('Method not implemented.');
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaCopyOptionModifier.identity, TextAreaCopyOptionModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaEnableKeyboardOnFocusModifier.identity, TextAreaEnableKeyboardOnFocusModifier, value);
    return this;
  }
  maxLength(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLengthModifier.identity, TextAreaMaxLengthModifier, value);
    return this;
  }
  showCounter(value, options) {
    let arkValue = new ArkTextAreaShowCounter();
    arkValue.value = value;
    arkValue.options = options;
    modifierWithKey(this._modifiersWithKeys, TextAreaShowCounterModifier.identity, TextAreaShowCounterModifier, arkValue);
    return this;
  }
  style(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaStyleModifier.identity, TextAreaStyleModifier, value);
    return this;
  }
  barState(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaBarStateModifier.identity, TextAreaBarStateModifier, value);
    return this;
  }
  selectionMenuHidden(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaSelectionMenuHiddenModifier.identity, TextAreaSelectionMenuHiddenModifier, value);
    return this;
  }
  maxLines(value) {
    modifierWithKey(this._modifiersWithKeys, TextAreaMaxLinesModifier.identity, TextAreaMaxLinesModifier, value);
    return this;
  }
  customKeyboard(value) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.TextArea.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextAreaComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class TextInputStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetStyle(node);
    }
    else {
      getUINativeModule().textInput.setStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputStyleModifier.identity = Symbol('textInputStyle');
class TextInputMaxLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetMaxLength(node);
    }
    else {
      getUINativeModule().textInput.setMaxLength(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputMaxLengthModifier.identity = Symbol('textInputMaxLength');
class TextInputMaxLinesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetMaxLines(node);
    }
    else {
      getUINativeModule().textInput.setMaxLines(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputMaxLinesModifier.identity = Symbol('textInputMaxLines');
class TextInputShowPasswordIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetShowPasswordIcon(node);
    }
    else {
      getUINativeModule().textInput.setShowPasswordIcon(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputShowPasswordIconModifier.identity = Symbol('textInputShowPasswordIcon');
class TextInputTextAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetTextAlign(node);
    }
    else {
      getUINativeModule().textInput.setTextAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputTextAlignModifier.identity = Symbol('textInputTextAlign');
class TextInputPlaceholderFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetPlaceholderFont(node);
    }
    else {
      getUINativeModule().textInput.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (!(this.stageValue.weight === this.value.weight &&
      this.stageValue.style === this.value.style)) {
      return true;
    }
    else {
      if (((isResource(this.stageValue.size) && isResource(this.value.size) &&
        isResourceEqual(this.stageValue.size, this.value.size)) ||
        (!isResource(this.stageValue.size) && !isResource(this.value.size) &&
          this.stageValue.size === this.value.size)) &&
        ((isResource(this.stageValue.family) && isResource(this.value.family) &&
          isResourceEqual(this.stageValue.family, this.value.family)) ||
          (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
            this.stageValue.family === this.value.family))) {
        return false;
      }
      else {
        return true;
      }
    }
  }
}
TextInputPlaceholderFontModifier.identity = Symbol('textInputPlaceholderFont');
class TextInputPlaceholderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetPlaceholderColor(node);
    }
    else {
      getUINativeModule().textInput.setPlaceholderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputPlaceholderColorModifier.identity = Symbol('textInputPlaceholderColor');
class TextInputPasswordIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetPasswordIcon(node);
    }
    else {
      getUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.onIconSrc, this.value.onIconSrc) ||
      !isBaseOrResourceEqual(this.stageValue.offIconSrc, this.value.offIconSrc);
  }
}
TextInputPasswordIconModifier.identity = Symbol('textInputPasswordIcon');
class TextInputSelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetSelectedBackgroundColor(node);
    }
    else {
      getUINativeModule().textInput.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputSelectedBackgroundColorModifier.identity = Symbol('textInputSelectedBackgroundColor');
class TextInputSelectionMenuHiddenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetSelectionMenuHidden(node);
    }
    else {
      getUINativeModule().textInput.setSelectionMenuHidden(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputSelectionMenuHiddenModifier.identity = Symbol('textInputSelectionMenuHidden');
class TextInputShowUnderlineModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetShowUnderline(node);
    }
    else {
      getUINativeModule().textInput.setShowUnderline(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputShowUnderlineModifier.identity = Symbol('textInputShowUnderLine');
class TextInputShowErrorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetShowError(node);
    }
    else {
      getUINativeModule().textInput.setShowError(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputShowErrorModifier.identity = Symbol('textInputShowError');
class TextInputTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetType(node);
    }
    else {
      getUINativeModule().textInput.setType(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputTypeModifier.identity = Symbol('textInputType');
class TextInputCaretPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetCaretPosition(node);
    }
    else {
      getUINativeModule().textInput.setCaretPosition(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputCaretPositionModifier.identity = Symbol('textInputCaretPosition');
class TextInputCopyOptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetCopyOption(node);
    }
    else {
      getUINativeModule().textInput.setCopyOption(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputCopyOptionModifier.identity = Symbol('textInputCopyOption');
class TextInputEnableKeyboardOnFocusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
    }
    else {
      getUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputEnableKeyboardOnFocusModifier.identity = Symbol('textInputEnableKeyboardOnFocus');
class TextInputCaretStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetCaretStyle(node);
    }
    else {
      getUINativeModule().textInput.setCaretStyle(node, this.value.width);
    }
  }
  checkObjectDiff() {
    if (isObject(this.stageValue) && isObject(this.value)) {
      return !isBaseOrResourceEqual(this.stageValue.width, this.value.width);
    }
    else {
      return true;
    }
  }
}
TextInputCaretStyleModifier.identity = Symbol('textInputCaretStyle');
class TextInputEnterKeyTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetEnterKeyType(node);
    }
    else {
      getUINativeModule().textInput.setEnterKeyType(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputEnterKeyTypeModifier.identity = Symbol('textInputEnterKeyType');
class TextInputBarStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetBarState(node);
    }
    else {
      getUINativeModule().textInput.setBarState(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputBarStateModifier.identity = Symbol('textInputBarState');
class TextInputCaretColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetCaretColor(node);
    }
    else {
      getUINativeModule().textInput.setCaretColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputCaretColorModifier.identity = Symbol('textinputCaretColor');
class TextInputFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetFontColor(node);
    }
    else {
      getUINativeModule().textInput.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputFontColorModifier.identity = Symbol('textInputFontColor');
class TextInputFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetFontSize(node);
    }
    else {
      getUINativeModule().textInput.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputFontSizeModifier.identity = Symbol('textInputFontSize');
class TextInputFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetFontStyle(node);
    }
    else {
      getUINativeModule().textInput.setFontStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputFontStyleModifier.identity = Symbol('textInputFontStyle');
class TextInputFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetFontWeight(node);
    }
    else {
      getUINativeModule().textInput.setFontWeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputFontWeightModifier.identity = Symbol('textInputFontWeight');
class TextInputFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textInput.resetFontFamily(node);
    }
    else {
      getUINativeModule().textInput.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextInputFontFamilyModifier.identity = Symbol('textInputFontFamily');
class ArkTextInputComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  cancelButton(value) {
    throw new Error('Method not implemented.');
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  selectAll(value) {
    throw new Error('Method not implemented.');
  }
  enableAutoFill(value) {
    throw new Error('Method not implemented.');
  }
  passwordRules(value) {
    throw new Error('Method not implemented.');
  }
  showCounter(value) {
    throw new Error('Method not implemented.');
  }
  type(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputTypeModifier.identity, TextInputTypeModifier, value);
    return this;
  }
  placeholderColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderColorModifier.identity, TextInputPlaceholderColorModifier, value);
    return this;
  }
  placeholderFont(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputPlaceholderFontModifier.identity, TextInputPlaceholderFontModifier, value);
    return this;
  }
  enterKeyType(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputEnterKeyTypeModifier.identity, TextInputEnterKeyTypeModifier, value);
    return this;
  }
  caretColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretColorModifier.identity, TextInputCaretColorModifier, value);
    return this;
  }
  onEditChanged(callback) {
    throw new Error('Method not implemented.');
  }
  onEditChange(callback) {
    throw new Error('Method not implemented.');
  }
  onSubmit(callback) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback) {
    throw new Error('Method not implemented.');
  }
  onContentScroll(callback) {
    throw new Error('Method not implemented.');
  }
  maxLength(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLengthModifier.identity, TextInputMaxLengthModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputFontColorModifier.identity, TextInputFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputFontSizeModifier.identity, TextInputFontSizeModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputFontStyleModifier.identity, TextInputFontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputFontWeightModifier.identity, TextInputFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputFontFamilyModifier.identity, TextInputFontFamilyModifier, value);
    return this;
  }
  inputFilter(value, error) {
    throw new Error('Method not implemented.');
  }
  onCopy(callback) {
    throw new Error('Method not implemented.');
  }
  onCut(callback) {
    throw new Error('Method not implemented.');
  }
  onPaste(callback) {
    throw new Error('Method not implemented.');
  }
  copyOption(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputCopyOptionModifier.identity, TextInputCopyOptionModifier, value);
    return this;
  }
  showPasswordIcon(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputShowPasswordIconModifier.identity, TextInputShowPasswordIconModifier, value);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputTextAlignModifier.identity, TextInputTextAlignModifier, value);
    return this;
  }
  style(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputStyleModifier.identity, TextInputStyleModifier, value);
    return this;
  }
  caretStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretStyleModifier.identity, TextInputCaretStyleModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectedBackgroundColorModifier.identity, TextInputSelectedBackgroundColorModifier, value);
    return this;
  }
  caretPosition(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputCaretPositionModifier.identity, TextInputCaretPositionModifier, value);
    return this;
  }
  enableKeyboardOnFocus(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputEnableKeyboardOnFocusModifier.identity, TextInputEnableKeyboardOnFocusModifier, value);
    return this;
  }
  passwordIcon(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputPasswordIconModifier.identity, TextInputPasswordIconModifier, value);
    return this;
  }
  showError(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputShowErrorModifier.identity, TextInputShowErrorModifier, value);
    return this;
  }
  showUnit(event) {
    throw new Error('Method not implemented.');
  }
  showUnderline(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputShowUnderlineModifier.identity, TextInputShowUnderlineModifier, value);
    return this;
  }
  selectionMenuHidden(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputSelectionMenuHiddenModifier.identity, TextInputSelectionMenuHiddenModifier, value);
    return this;
  }
  barState(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputBarStateModifier.identity, TextInputBarStateModifier, value);
    return this;
  }
  maxLines(value) {
    modifierWithKey(this._modifiersWithKeys, TextInputMaxLinesModifier.identity, TextInputMaxLinesModifier, value);
    return this;
  }
  customKeyboard(event) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.TextInput.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextInputComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class VideoObjectFitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetObjectFit(node);
    }
    else {
      getUINativeModule().video.setObjectFit(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoObjectFitModifier.identity = Symbol('videoObjectFit');
class VideoAutoPlayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetAutoPlay(node);
    }
    else {
      getUINativeModule().video.setAutoPlay(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoAutoPlayModifier.identity = Symbol('videoAutoPlayr');
class VideoControlsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetControls(node);
    }
    else {
      getUINativeModule().video.setControls(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoControlsModifier.identity = Symbol('videoControls');
class VideoLoopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetLoop(node);
    }
    else {
      getUINativeModule().video.setLoop(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoLoopModifier.identity = Symbol('videoLoop');
class VideoMutedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetMuted(node);
    }
    else {
      getUINativeModule().video.setMuted(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoMutedModifier.identity = Symbol('videoMuted');
class ArkVideoComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  muted(value) {
    modifierWithKey(this._modifiersWithKeys, VideoMutedModifier.identity, VideoMutedModifier, value);
    return this;
  }
  autoPlay(value) {
    modifierWithKey(this._modifiersWithKeys, VideoAutoPlayModifier.identity, VideoAutoPlayModifier, value);
    return this;
  }
  controls(value) {
    modifierWithKey(this._modifiersWithKeys, VideoControlsModifier.identity, VideoControlsModifier, value);
    return this;
  }
  loop(value) {
    modifierWithKey(this._modifiersWithKeys, VideoLoopModifier.identity, VideoLoopModifier, value);
    return this;
  }
  objectFit(value) {
    modifierWithKey(this._modifiersWithKeys, VideoObjectFitModifier.identity, VideoObjectFitModifier, value);
    return this;
  }
  onStart(callback) {
    throw new Error('Method not implemented.');
  }
  onPause(callback) {
    throw new Error('Method not implemented.');
  }
  onFinish(event) {
    throw new Error('Method not implemented.');
  }
  onFullscreenChange(callback) {
    throw new Error('Method not implemented.');
  }
  onPrepared(callback) {
    throw new Error('Method not implemented.');
  }
  onSeeking(callback) {
    throw new Error('Method not implemented.');
  }
  onSeeked(callback) {
    throw new Error('Method not implemented.');
  }
  onUpdate(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Video.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkVideoComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkBorderStyle {
  constructor() {
    this.type = undefined;
    this.style = undefined;
    this.top = undefined;
    this.right = undefined;
    this.bottom = undefined;
    this.left = undefined;
  }
  isEqual(another) {
    return (this.type === another.type &&
      this.style === another.style &&
      this.top === another.top &&
      this.right === another.right &&
      this.bottom === another.bottom &&
      this.left === another.left);
  }
  parseBorderStyle(value) {
    if (typeof value === 'number') {
      this.style = value;
      this.type = true;
      return true;
    }
    else if (typeof value === 'object') {
      return this.parseEdgeStyles(value);
    }
    return false;
  }
  parseEdgeStyles(options) {
    this.top = options.top;
    this.right = options.right;
    this.bottom = options.bottom;
    this.left = options.left;
    this.type = true;
    return true;
  }
}
class ArkBorderColor {
  constructor() {
    this.leftColor = undefined;
    this.rightColor = undefined;
    this.topColor = undefined;
    this.bottomColor = undefined;
  }
  isEqual(another) {
    return (this.leftColor === another.leftColor &&
      this.rightColor === another.rightColor &&
      this.topColor === another.topColor &&
      this.bottomColor === another.bottomColor);
  }
}
class ArkPosition {
  constructor() {
    this.x = undefined;
    this.y = undefined;
  }
  isEqual(another) {
    return this.x === another.x && this.y === another.y;
  }
}
class ArkBorderWidth {
  constructor() {
    this.left = undefined;
    this.right = undefined;
    this.top = undefined;
    this.bottom = undefined;
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.right === another.right &&
      this.top === another.top &&
      this.bottom === another.bottom);
  }
}
class ArkBorderRadius {
  constructor() {
    this.topLeft = undefined;
    this.topRight = undefined;
    this.bottomLeft = undefined;
    this.bottomRight = undefined;
  }
  isEqual(another) {
    return (this.topLeft === another.topLeft &&
      this.topRight === another.topRight &&
      this.bottomLeft === another.bottomLeft &&
      this.bottomRight === another.bottomRight);
  }
}
class ArkLabelFont {
  constructor() {
    this.size = undefined;
    this.weight = undefined;
    this.family = undefined;
    this.style = undefined;
  }
  isEqual(another) {
    return (this.size === another.size &&
      this.weight === another.weight &&
      this.family === another.family &&
      this.style === another.style);
  }
}
function deepCompareArrays(arr1, arr2) {
  return (Array.isArray(arr1) &&
    Array.isArray(arr2) &&
    arr1.length === arr2.length &&
    arr1.every((value, index) => {
      if (Array.isArray(value) && Array.isArray(arr2[index])) {
        return deepCompareArrays(value, arr2[index]);
      }
      else {
        return value === arr2[index];
      }
    }));
}
class ArkLinearGradient {
  constructor(angle, direction, colors, repeating) {
    this.angle = angle;
    this.direction = direction;
    this.colors = colors;
    this.repeating = repeating;
  }
  isEqual(another) {
    return (this.angle === another.angle &&
      this.direction === another.direction &&
      deepCompareArrays(this.colors, another.colors) &&
      this.repeating === another.repeating);
  }
}
class ArkSweepGradient {
  constructor(center, start, end, rotation, colors, repeating) {
    this.center = center;
    this.start = start;
    this.end = end;
    this.rotation = rotation;
    this.colors = colors;
    this.repeating = repeating;
  }
  isEqual(another) {
    return (deepCompareArrays(this.center, another.center) &&
      this.start === another.start &&
      this.end === another.end &&
      this.rotation === another.rotation &&
      deepCompareArrays(this.colors, another.colors) &&
      this.repeating === another.repeating);
  }
}
class ArkForegroundBlurStyle {
  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
  }
  isEqual(another) {
    return (this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale);
  }
}
class ArkLinearGradientBlur {
  constructor() {
    this.blurRadius = undefined;
    this.fractionStops = undefined;
    this.direction = undefined;
  }
  isEqual(another) {
    return (this.blurRadius === another.blurRadius &&
      deepCompareArrays(this.fractionStops, another.fractionStops) &&
      this.direction === another.direction);
  }
}
class ArkOverlay {
  constructor() {
    this.value = undefined;
    this.align = undefined;
    this.offsetX = undefined;
    this.offsetY = undefined;
    this.hasOptions = undefined;
    this.hasOffset = undefined;
  }
  splitOption(options) {
    if (isUndefined(options)) {
      return true;
    }
    this.hasOptions = true;
    this.align = options.align;
    if (isUndefined(options.offset)) {
      return true;
    }
    this.hasOffset = true;
    this.offsetX = options.offset.x;
    this.offsetY = options.offset.y;
    return true;
  }
  splitOverlayValue(value, options) {
    if (typeof value === 'string') {
      this.value = value;
      return this.splitOption(options);
    }
    return false;
  }
  isEqual(another) {
    return ((this.value === another.value) && (this.align === another.align) &&
      (this.offsetX === another.offsetX) && (this.offsetY === another.offsetY) &&
      (this.hasOptions === another.hasOptions) && (this.hasOffset === another.hasOffset));
  }
  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
}
class ArkSharedTransition {
  constructor() {
    this.id = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.id === another.id) && (this.options === another.options);
  }
}
class ArkListEdgeEffect {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkScrollEdgeEffect {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkMenuAlignType {
  constructor(alignType, offset) {
    this.alignType = alignType;
    if (!isUndefined(offset) && isObject(offset)) {
      this.dx = offset.dx;
      this.dy = offset.dy;
    }
  }
  isEqual(another) {
    return this.alignType === another.alignType && this.dx === another.dx && this.dy === another.dy;
  }
}
class ArkSliderTips {
  constructor(value, content) {
    this.showTip = value;
    this.tipText = content;
  }
  isEqual(another) {
    return this.showTip === another.showTip && this.tipText === another.tipText;
  }
}
class ArkRadioStyle {
  constructor() {
    this.checkedBackgroundColor = undefined;
    this.uncheckedBorderColor = undefined;
    this.indicatorColor = undefined;
  }
  isEqual(another) {
    return (this.checkedBackgroundColor === another.checkedBackgroundColor &&
      this.uncheckedBorderColor === another.uncheckedBorderColor &&
      this.indicatorColor === another.indicatorColor);
  }
}
class ArkStarStyle {
  constructor() {
    this.backgroundUri = undefined;
    this.foregroundUri = undefined;
    this.secondaryUri = undefined;
  }
  isEqual(another) {
    return (this.backgroundUri === another.backgroundUri &&
      this.foregroundUri === another.foregroundUri &&
      this.secondaryUri === another.secondaryUri);
  }
}
class ArkBackgroundBlurStyle {
  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
  }
  isEqual(another) {
    return (this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale);
  }
}
class ArkSelectedIndices {
  constructor() {
    this.selectedValues = [];
  }
  compareArrays(arr1, arr2) {
    return (Array.isArray(arr1) &&
      Array.isArray(arr2) &&
      arr1.length === arr2.length &&
      arr1.every((value, index) => value === arr2[index]));
  }
  isEqual(another) {
    return this.compareArrays(this.selectedValues, another.selectedValues);
  }
}
class ArkBorder {
  constructor() {
    this.arkWidth = new ArkBorderWidth();
    this.arkColor = new ArkBorderColor();
    this.arkRadius = new ArkBorderRadius();
    this.arkStyle = new ArkBorderStyle();
  }
  isEqual(another) {
    return (this.arkWidth.isEqual(another.arkWidth) &&
      this.arkColor.isEqual(another.arkColor) &&
      this.arkRadius.isEqual(another.arkRadius) &&
      this.arkStyle.isEqual(another.arkStyle));
  }
  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
}
class ArkBackgroundImageSize {
  constructor() {
    this.imageSize = undefined;
    this.width = undefined;
    this.height = undefined;
  }
  isEqual(another) {
    return this.imageSize === another.imageSize && this.width === another.width && this.height === another.height;
  }
}
class ArkBackgroundImage {
  constructor() {
    this.src = undefined;
    this.repeat = undefined;
  }
  isEqual(another) {
    return this.src === another.src && this.repeat === another.repeat;
  }
}
class ArkGridColColumnOption {
  constructor() {
    this.xs = undefined;
    this.sm = undefined;
    this.md = undefined;
    this.lg = undefined;
    this.xl = undefined;
    this.xxl = undefined;
  }
  isEqual(another) {
    return (this.xs === another.xs &&
      this.sm === another.sm &&
      this.md === another.md &&
      this.lg === another.lg &&
      this.xl === another.xl &&
      this.xxl === another.xxl);
  }
}
class ArkPadding {
  constructor() {
    this.top = undefined;
    this.right = undefined;
    this.bottom = undefined;
    this.left = undefined;
  }
  isEqual(another) {
    return (this.top === another.top &&
      this.right === another.right &&
      this.bottom === another.bottom &&
      this.left === another.left);
  }
}
class ArkBarMode {
  isEqual(another) {
    return (this.barMode === another.barMode) && (this.options === another.options);
  }
}
class ArkDivider {
  isEqual(another) {
    return (this.divider === another.divider);
  }
}
class ArkBarGridAlign {
  isEqual(another) {
    return (this.barGridAlign === another.barGridAlign);
  }
}
class ArkScrollableBarModeOptions {
  isEqual(another) {
    return (this.value === another.value);
  }
}
class ArkAlignRules {
  constructor() {
    this.left = undefined;
    this.middle = undefined;
    this.right = undefined;
    this.top = undefined;
    this.center = undefined;
    this.bottom = undefined;
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.middle === another.middle &&
      this.right === another.right &&
      this.top === another.top &&
      this.center === another.center &&
      this.bottom === another.bottom);
  }
}
class ArkSafeAreaExpandOpts {
  constructor() {
    this.type = undefined;
    this.edges = undefined;
  }
  isEqual(another) {
    return (this.type === another.type) && (this.edges === another.edges);
  }
}
class ArkButtonStyle {
  constructor() {
    this.left = 16;
    this.top = 48;
    this.width = 24;
    this.height = 24;
    this.icons = {
      shown: undefined,
      hidden: undefined,
      switching: undefined
    };
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.top === another.top &&
      this.width === another.width &&
      this.height === another.height &&
      this.icons === another.icons);
  }
}
class ArkShadowInfoToArray {
  constructor() {
    this.radius = [];
    this.type = [];
    this.color = [];
    this.offsetX = [];
    this.offsetX = [];
    this.offsetY = [];
    this.fill = [];
  }
  isEqual(another) {
    return (this.radius === another.radius) &&
      (this.color === another.color) &&
      (this.offsetX === another.offsetX) &&
      (this.offsetY === another.offsetY) &&
      (this.fill === another.fill);
  }
  convertShadowOptions(value) {
    if (Object.getPrototypeOf(value).constructor === Object) {
      if (value.radius === null || value.radius === undefined) {
        return false;
      }
      else {
        this.radius.push(value.radius);
        this.type.push(value.type);
        this.color.push(value.color);
        this.offsetX.push((value.offsetX === undefined ||
          value.offsetX === null) ? 0 : value.offsetX);
        this.offsetY.push((value.offsetY === undefined ||
          value.offsetY === null) ? 0 : value.offsetY);
        this.fill.push((value.fill === undefined ||
          value.fill === null) ? false : value.fill);
        return true;
      }
    }
    else if (Object.getPrototypeOf(value).constructor === Array) {
      let isFlag = true;
      for (let item of value) {
        if (item.radius === undefined || item.radius === null) {
          isFlag = false;
          break;
        }
      }
      if (isFlag) {
        for (let objValue of value) {
          this.radius.push(objValue.radius);
          this.type.push(objValue.type);
          this.color.push(objValue.color);
          this.offsetX.push((objValue.offsetX === undefined || objValue.offsetX === null) ? 0 : objValue.offsetX);
          this.offsetY.push((objValue.offsetY === undefined || objValue.offsetY === null) ? 0 : objValue.offsetY);
          this.fill.push((objValue.fill === undefined || objValue.fill === null) ? false : objValue.fill);
        }
        return true;
      }
      else {
        return false;
      }
    }
  }
  checkDiff(value, stageValue) {
    if (!value || !stageValue || !value.radius || !stageValue.radius) {
      return true;
    }
    if (!((isResource(stageValue.radius) && isResource(value.radius) &&
      isResourceEqual(stageValue.radius, value.radius)) ||
      (isNumber(stageValue.radius) && isNumber(value.radius) &&
        stageValue.radius === value.radius))) {
      return true;
    }
    if (!(isNumber(stageValue.type) && isNumber(value.type) &&
      stageValue.type === value.type)) {
      return true;
    }
    if (!((isResource(stageValue.color) && isResource(value.color) &&
      isResourceEqual(stageValue.color, value.color)) ||
      (!isResource(stageValue.color) && !isResource(value.color) &&
        stageValue.color === value.color))) {
      return true;
    }
    if (!((isResource(stageValue.offsetX) && isResource(value.offsetX) &&
      isResourceEqual(stageValue.offsetX, value.offsetX)) ||
      (isNumber(stageValue.offsetX) && isNumber(value.offsetX) &&
        stageValue.offsetX === value.offsetX))) {
      return true;
    }
    if (!((isResource(stageValue.offsetY) && isResource(value.offsetY) &&
      isResourceEqual(stageValue.offsetY, value.offsetY)) ||
      (isNumber(stageValue.offsetY) && isNumber(value.offsetY) &&
        stageValue.offsetY === value.offsetY))) {
      return true;
    }
    if (!(isBoolean(stageValue.fill) && isBoolean(value.fill) &&
      stageValue.fill === value.fill)) {
      return true;
    }
    return false;
  }
}
class ArkSearchButton {
  constructor() {
    this.value = undefined;
    this.fontSize = undefined;
    this.fontColor = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.fontSize === another.fontSize) &&
      (this.fontColor === another.fontColor);
  }
}
class ArkImageFrameInfoToArray {
  constructor() {
    this.arrSrc = [];
    this.arrWidth = [];
    this.arrHeight = [];
    this.arrTop = [];
    this.arrLeft = [];
    this.arrDuration = [];
  }
  isEqual(another) {
    return (this.arrSrc.toString() === another.arrSrc.toString()) &&
      (this.arrWidth.toString() === another.arrWidth.toString()) &&
      (this.arrHeight.toString() === another.arrHeight.toString()) &&
      (this.arrTop.toString() === another.arrTop.toString()) &&
      (this.arrLeft.toString() === another.arrLeft.toString()) &&
      (this.arrDuration.toString() === another.arrDuration.toString());
  }
}
class ArkEdgeAlign {
  constructor() {
    this.alignType = undefined;
    this.offset = undefined;
  }
  isEqual(another) {
    return (this.alignType === another.alignType && this.offset === another.offset);
  }
}
class ArkKeyBoardShortCut {
  constructor() {
    this.value = undefined;
    this.keys = undefined;
    this.action = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) && (this.keys === another.keys) &&
      (this.action === another.action);
  }
}
class ArkAlignStyle {
  constructor() {
    this.indexerAlign = undefined;
    this.offset = undefined;
  }
  isEqual(another) {
    return (this.indexerAlign === another.indexerAlign && this.offset === another.offset);
  }
}
class ArkNestedScrollOptions {
  constructor() {
    this.scrollForward = undefined;
    this.scrollBackward = undefined;
  }
  isEqual(another) {
    return ((this.scrollForward === another.scrollForward) && (this.scrollBackward === another.scrollBackward));
  }
}
class ArkConstraintSizeOptions {
  constructor() {
    this.minWidth = undefined;
    this.maxWidth = undefined;
    this.minHeight = undefined;
    this.maxHeight = undefined;
  }
  isEqual(another) {
    return (this.minWidth === another.minWidth &&
      this.maxWidth === another.maxWidth &&
      this.minHeight === another.minHeight &&
      this.maxHeight === another.maxHeight);
  }
}
class ArkTextAreaShowCounter {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkDotIndicator extends DotIndicator {
  constructor() {
    super();
    this.type = undefined;
    this.leftValue = undefined;
    this.topValue = undefined;
    this.rightValue = undefined;
    this.bottomValue = undefined;
    this.itemWidthValue = undefined;
    this.itemHeightValue = undefined;
    this.selectedItemWidthValue = undefined;
    this.selectedItemHeightValue = undefined;
    this.maskValue = undefined;
    this.colorValue = undefined;
    this.selectedColorValue = undefined;
  }
  isEqual(another) {
    return (this.type === another.type &&
      this.leftValue === another.leftValue &&
      this.topValue === another.topValue &&
      this.rightValue === another.rightValue &&
      this.bottomValue === another.bottomValue &&
      this.itemWidthValue === another.itemWidthValue &&
      this.itemHeightValue === another.itemHeightValue &&
      this.selectedItemWidthValue === another.selectedItemWidthValue &&
      this.selectedItemHeightValue === another.selectedItemHeightValue &&
      this.maskValue === another.maskValue &&
      this.colorValue === another.colorValue &&
      this.selectedColorValue === another.selectedColorValue);
  }
}
class ArkDigitIndicator extends DigitIndicator {
  constructor() {
    super();
    this.type = undefined;
    this.leftValue = undefined;
    this.topValue = undefined;
    this.rightValue = undefined;
    this.bottomValue = undefined;
    this.fontColorValue = undefined;
    this.selectedFontColorValue = undefined;
    this.digitFontValue = undefined;
    this.selectedDigitFontValue = undefined;
  }
  isEqual(another) {
    return (this.type === another.type &&
      this.leftValue === another.leftValue &&
      this.topValue === another.topValue &&
      this.rightValue === another.rightValue &&
      this.bottomValue === another.bottomValue &&
      this.digitFontValue === another.digitFontValue &&
      this.selectedDigitFontValue === another.selectedDigitFontValue);
  }
}
class ArkDigitFont {
  constructor() {
    this.size = undefined;
    this.weight = undefined;
  }
  isEqual(another) {
    return this.size === another.size && this.weight === another.weight;
  }
  parseFontWeight(value) {
    const valueWeightMap = {
      [0]: 'lighter',
      [1]: 'normal',
      [2]: 'regular',
      [3]: 'medium',
      [4]: 'bold',
      [5]: 'bolder'
    };
    if (isUndefined(value)) {
      this.weight = '-';
    }
    else if (value in valueWeightMap) {
      this.weight = valueWeightMap[value];
    }
    else {
      this.weight = value.toString();
    }
    return this.weight;
  }
}
class ArkDisplayArrow {
  constructor() {
    this.value = undefined;
    this.isHoverShow = undefined;
  }
  isEqual(another) {
    return this.value === another.value && this.isHoverShow === another.isHoverShow;
  }
}
class ArkGridEdgeEffect {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkMesh {
  constructor() {
    this.value = undefined;
    this.column = undefined;
    this.row = undefined;
  }
  isEqual(another) {
    return (deepCompareArrays(this.value, another.value) &&
      this.column === another.column &&
      this.row === another.row);
  }
}
class ArkLanesOpt {
  constructor() {
    this.lanesNum = undefined;
    this.minLength = undefined;
    this.maxLength = undefined;
    this.gutter = undefined;
  }
  isEqual(another) {
    return (this.lanesNum === another.lanesNum && this.minLength === another.minLength
      && this.maxLength === another.maxLength && this.gutter === another.gutter);
  }
}
class ArkScrollSnapOptions {
  constructor() {
    this.snapAlign = undefined;
    this.snapPagination = undefined;
    this.enableSnapToStart = undefined;
    this.enableSnapToEnd = undefined;
  }
  isEqual(another) {
    return ((this.snapAlign === another.snapAlign)
      && (this.snapPagination === another.snapPagination)
      && (this.enableSnapToStart === another.enableSnapToStart)
      && (this.enableSnapToEnd === another.enableSnapToEnd));
  }
}

/// <reference path='./import.ts' />
/// <reference path="./ArkComponent.ts" />
const FontWeightMap = {
  0: 'lighter',
  1: 'normal',
  2: 'regular',
  3: 'medium',
  4: 'bold',
  5: 'bolder',
  100: '100',
  200: '200',
  300: '300',
  400: '400',
  500: '500',
  600: '600',
  700: '700',
  800: '800',
  900: '900',
};
class ArkButtonComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonBackgroundColorModifier.identity, ButtonBackgroundColorModifier, value);
    return this;
  }
  type(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonTypeModifier.identity, ButtonTypeModifier, value);
    return this;
  }
  stateEffect(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonStateEffectModifier.identity, ButtonStateEffectModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonFontColorModifier.identity, ButtonFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonFontSizeModifier.identity, ButtonFontSizeModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonFontWeightModifier.identity, ButtonFontWeightModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonFontStyleModifier.identity, ButtonFontStyleModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonFontFamilyModifier.identity, ButtonFontFamilyModifier, value);
    return this;
  }
  labelStyle(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonLabelStyleModifier.identity, ButtonLabelStyleModifier, value);
    return this;
  }
  borderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, ButtonBorderRadiusModifier.identity, ButtonBorderRadiusModifier, value);
    return this;
  }
}
class ButtonBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetBackgroundColor(node);
    }
    else {
      getUINativeModule().button.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ButtonBackgroundColorModifier.identity = Symbol('buttonBackgroundColor');
class ButtonStateEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetStateEffect(node);
    }
    else {
      getUINativeModule().button.setStateEffect(node, this.value);
    }
  }
}
ButtonStateEffectModifier.identity = Symbol('buttonStateEffect');
class ButtonFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetFontStyle(node);
    }
    else {
      getUINativeModule().button.setFontStyle(node, this.value);
    }
  }
}
ButtonFontStyleModifier.identity = Symbol('buttonFontStyle');
class ButtonFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetFontFamily(node);
    }
    else {
      getUINativeModule().button.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ButtonFontFamilyModifier.identity = Symbol('buttonFontFamily');
class ButtonLabelStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetLabelStyle(node);
    }
    else {
      let textOverflow = this.value.overflow; // number(enum) -> Ace::TextOverflow
      let maxLines = this.value.maxLines; // number -> uint32_t
      let minFontSize = this.value.minFontSize; // number | string | Resource -> Dimension
      let maxFontSize = this.value.maxFontSize; // number | string | Resource -> Dimension
      let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number(enum) -> Ace::TextHeightAdaptivePolicy
      let fontSize; // number | string | Resource -> Dimension
      let fontWeight; // number | string | Ace::FontWeight -> string -> Ace::FontWeight
      let fontStyle; // number(enum) -> Ace::FontStyle
      let fontFamily; // string -> std::vector<std::string>
      if (isObject(this.value.font)) {
        fontSize = this.value.font.size;
        fontStyle = this.value.font.style;
        fontFamily = this.value.font.family;
        fontWeight = this.value.font.weight;
      }
      getUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize,
        maxFontSize, heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.value.overflow === this.stageValue.overflow &&
        this.value.maxLines === this.stageValue.maxLines &&
        this.value.minFontSize === this.stageValue.minFontSize &&
        this.value.maxFontSize === this.stageValue.maxFontSize &&
        this.value.heightAdaptivePolicy === this.stageValue.heightAdaptivePolicy &&
        this.value.font === this.stageValue.font);
    }
    else {
      return true;
    }
  }
}
ButtonLabelStyleModifier.identity = Symbol('buttonLabelStyle');
class ButtonTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetType(node);
    }
    else {
      getUINativeModule().button.setType(node, this.value);
    }
  }
}
ButtonTypeModifier.identity = Symbol('buttonType');
class ButtonFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetFontColor(node);
    }
    else {
      getUINativeModule().button.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ButtonFontColorModifier.identity = Symbol('buttonFontColor');
class ButtonFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetFontSize(node);
    }
    else {
      getUINativeModule().button.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ButtonFontSizeModifier.identity = Symbol('buttonFontSize');
class ButtonFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetFontWeight(node);
    }
    else {
      getUINativeModule().button.setFontWeight(node, this.value);
    }
  }
}
ButtonFontWeightModifier.identity = Symbol('buttonFontWeight');
class ButtonBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().button.resetButtonBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().button.setButtonBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().button.setButtonBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
ButtonBorderRadiusModifier.identity = Symbol('buttonBorderRadius');
// @ts-ignore
globalThis.Button.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkButtonComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkLoadingProgressComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, LoadingProgressColorModifier.identity, LoadingProgressColorModifier, value);
    return this;
  }
  enableLoading(value) {
    modifierWithKey(this._modifiersWithKeys, LoadingProgressEnableLoadingModifier.identity, LoadingProgressEnableLoadingModifier, value);
    return this;
  }
}
class LoadingProgressColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().loadingProgress.resetColor(node);
    }
    else {
      getUINativeModule().loadingProgress.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LoadingProgressColorModifier.identity = Symbol('loadingProgressColor');
class LoadingProgressEnableLoadingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().loadingProgress.resetEnableLoading(node);
    }
    else {
      getUINativeModule().loadingProgress.setEnableLoading(node, this.value);
    }
  }
}
LoadingProgressEnableLoadingModifier.identity = Symbol('loadingProgressEnableLoading');
// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkLoadingProgressComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkRefreshComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  onStateChange(callback) {
    throw new Error('Method not implemented.');
  }
  onRefreshing(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Refresh.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRefreshComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ScrollNestedScrollModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetNestedScroll(node);
    }
    else {
      getUINativeModule().scroll.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.scrollForward, this.value.scrollForward) ||
      !isBaseOrResourceEqual(this.stageValue.scrollBackward, this.value.scrollBackward);
  }
}
ScrollNestedScrollModifier.identity = Symbol('nestedScroll');
class ScrollEnableScrollInteractionModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetEnableScroll(node);
    }
    else {
      getUINativeModule().scroll.setEnableScroll(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ScrollEnableScrollInteractionModifier.identity = Symbol('enableScrollInteraction');
class ScrollFrictionModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetFriction(node);
    }
    else {
      getUINativeModule().scroll.setFriction(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ScrollFrictionModifier.identity = Symbol('friction');
class ScrollScrollSnapModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollSnap(node);
    }
    else {
      let snapPagination = [];
      let isArray = true;
      if (Array.isArray(this.value.snapPagination)) {
        for (let i = 0; i <= this.value.snapPagination.length; i++) {
          let item = this.value.snapPagination[i];
          snapPagination.push(item);
        }
      }
      else {
        isArray = false;
      }
      if (isArray) {
        getUINativeModule().scroll.setScrollSnap(node, this.value.snapAlign, snapPagination,
          this.value.enableSnapToStart, this.value.enableSnapToEnd);
      }
      else {
        getUINativeModule().scroll.setScrollSnap(node, this.value.snapAlign, this.value.snapPagination,
          this.value.enableSnapToStart, this.value.enableSnapToEnd);
      }
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.snapAlign === this.value.snapAlign) &&
      (this.stageValue.enableSnapToStart === this.value.enableSnapToStart) &&
      (this.stageValue.enableSnapToEnd === this.value.enableSnapToEnd) &&
      (this.stageValue.snapPagination === this.value.snapPagination));
  }
}
ScrollScrollSnapModifier.identity = Symbol('scrollSnap');
class ScrollScrollBarModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollBar(node);
    }
    else {
      getUINativeModule().scroll.setScrollBar(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ScrollScrollBarModifier.identity = Symbol('scrollBar');
class ScrollScrollableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollable(node);
    }
    else {
      getUINativeModule().scroll.setScrollable(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ScrollScrollableModifier.identity = Symbol('scrollable');
class ScrollEdgeEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a;
    if (reset) {
      getUINativeModule().scroll.resetEdgeEffect(node);
    }
    else {
      getUINativeModule().scroll.setEdgeEffect(node, this.value.value, (_a = this.value.options) === null || _a ===
      void 0 ? void 0 : _a.alwaysEnabled);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}
ScrollEdgeEffectModifier.identity = Symbol('edgeEffect');
class ScrollScrollBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollBarWidth(node);
    }
    else {
      getUINativeModule().scroll.setScrollBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ScrollScrollBarWidthModifier.identity = Symbol('scrollBarWidth');
class ScrollScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollBarColor(node);
    }
    else {
      getUINativeModule().scroll.setScrollBarColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ScrollScrollBarColorModifier.identity = Symbol('scrollBarColor');
class ArkScrollComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  scrollable(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollableModifier.identity, ScrollScrollableModifier, value);
    return this;
  }
  onScroll(event) {
    throw new Error('Method not implemented.');
  }
  onScrollEdge(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStart(event) {
    throw new Error('Method not implemented.');
  }
  onScrollEnd(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStop(event) {
    throw new Error('Method not implemented.');
  }
  scrollBar(value) {
    if (value in BarState) {
      modifierWithKey(this._modifiersWithKeys, ScrollScrollBarModifier.identity, ScrollScrollBarModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, ScrollScrollBarModifier.identity, ScrollScrollBarModifier, undefined);
    }
    return this;
  }
  scrollBarColor(color) {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollBarColorModifier.identity, ScrollScrollBarColorModifier, color);
    return this;
  }
  scrollBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollBarWidthModifier.identity, ScrollScrollBarWidthModifier, value);
    return this;
  }
  edgeEffect(value, options) {
    let effect = new ArkScrollEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, ScrollEdgeEffectModifier.identity, ScrollEdgeEffectModifier, effect);
    return this;
  }
  onScrollFrameBegin(event) {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value) {
    let options = new ArkNestedScrollOptions();
    if (value) {
      if (value.scrollForward) {
        options.scrollForward = value.scrollForward;
      }
      if (value.scrollBackward) {
        options.scrollBackward = value.scrollBackward;
      }
      modifierWithKey(this._modifiersWithKeys, ScrollNestedScrollModifier.identity, ScrollNestedScrollModifier, options);
    }
    return this;
  }
  enableScrollInteraction(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollEnableScrollInteractionModifier.identity, ScrollEnableScrollInteractionModifier, value);
    return this;
  }
  friction(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollFrictionModifier.identity, ScrollFrictionModifier, value);
    return this;
  }
  scrollSnap(value) {
    let options = new ArkScrollSnapOptions();
    if (value) {
      if (value.snapAlign) {
        options.snapAlign = value.snapAlign;
      }
      if (value.snapPagination) {
        options.snapPagination = value.snapPagination;
      }
      if (value.enableSnapToStart) {
        options.enableSnapToStart = value.enableSnapToStart;
      }
      if (value.enableSnapToEnd) {
        options.enableSnapToEnd = value.enableSnapToEnd;
      }
      modifierWithKey(this._modifiersWithKeys, ScrollScrollSnapModifier.identity, ScrollScrollSnapModifier, options);
    }
    return this;
  }
}
// @ts-ignore
globalThis.Scroll.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkScrollComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkToggleComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, ToggleSelectedColorModifier.identity, ToggleSelectedColorModifier, value);
    return this;
  }
  switchPointColor(value) {
    modifierWithKey(this._modifiersWithKeys, ToggleSwitchPointColorModifier.identity, ToggleSwitchPointColorModifier, value);
    return this;
  }
}
class ToggleSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().toggle.resetSelectedColor(node);
    }
    else {
      getUINativeModule().toggle.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ToggleSelectedColorModifier.identity = Symbol('toggleSelectedColor');
class ToggleSwitchPointColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().toggle.resetSwitchPointColor(node);
    }
    else {
      getUINativeModule().toggle.setSwitchPointColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ToggleSwitchPointColorModifier.identity = Symbol('toggleSwitchPointColor');
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkToggleComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkSelectComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  optionWidth(value) {
    throw new Error('Method not implemented.');
  }
  optionHeight(value) {
    throw new Error('Method not implemented.');
  }
  selected(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedModifier.identity, SelectedModifier, value);
    return this;
  }
  value(value) {
    modifierWithKey(this._modifiersWithKeys, ValueModifier.identity, ValueModifier, value);
    return this;
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, FontModifier.identity, FontModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectFontColorModifier.identity, SelectFontColorModifier, value);
    return this;
  }
  selectedOptionBgColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedOptionBgColorModifier.identity, SelectedOptionBgColorModifier, value);
    return this;
  }
  selectedOptionFont(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedOptionFontModifier.identity, SelectedOptionFontModifier, value);
    return this;
  }
  selectedOptionFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedOptionFontColorModifier.identity, SelectedOptionFontColorModifier, value);
    return this;
  }
  optionBgColor(value) {
    modifierWithKey(this._modifiersWithKeys, OptionBgColorModifier.identity, OptionBgColorModifier, value);
    return this;
  }
  optionFont(value) {
    modifierWithKey(this._modifiersWithKeys, OptionFontModifier.identity, OptionFontModifier, value);
    return this;
  }
  optionFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, OptionFontColorModifier.identity, OptionFontColorModifier, value);
    return this;
  }
  onSelect(callback) {
    throw new Error('Method not implemented.');
  }
  space(value) {
    modifierWithKey(this._modifiersWithKeys, SpaceModifier.identity, SpaceModifier, value);
    return this;
  }
  arrowPosition(value) {
    modifierWithKey(this._modifiersWithKeys, ArrowPositionModifier.identity, ArrowPositionModifier, value);
    return this;
  }
  menuAlign(alignType, offset) {
    let menuAlign = new ArkMenuAlignType(alignType, offset);
    modifierWithKey(this._modifiersWithKeys, MenuAlignModifier.identity, MenuAlignModifier, menuAlign);
    return this;
  }
}
class FontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetFont(node);
    }
    else {
      getUINativeModule().select.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
FontModifier.identity = Symbol('selectFont');
class OptionFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetOptionFont(node);
    }
    else {
      getUINativeModule().select.setOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
OptionFontModifier.identity = Symbol('selectOptionFont');
class SelectedOptionFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionFont(node);
    }
    else {
      getUINativeModule().select.setSelectedOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
SelectedOptionFontModifier.identity = Symbol('selectSelectedOptionFont');
class MenuAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetMenuAlign(node);
    }
    else {
      getUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
    }
  }
  checkObjectDiff() {
    let alignTypeEQ = this.stageValue.alignType === this.value.alignType;
    let dxEQ = isBaseOrResourceEqual(this.stageValue, this.value);
    let dyEQ = isBaseOrResourceEqual(this.stageValue, this.value);
    return !alignTypeEQ || !dxEQ || !dyEQ;
  }
  isEqual(stageValue, value) {
    if ((!isUndefined(stageValue) && isResource(stageValue)) &&
      (!isUndefined(value) && isResource(value))) {
      return !isResourceEqual(stageValue, value);
    }
    else {
      return stageValue !== value;
    }
  }
}
MenuAlignModifier.identity = Symbol('selectMenuAlign');
class ArrowPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetArrowPosition(node);
    }
    else {
      getUINativeModule().select.setArrowPosition(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ArrowPositionModifier.identity = Symbol('selectArrowPosition');
class SpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetSpace(node);
    }
    else {
      getUINativeModule().select.setSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SpaceModifier.identity = Symbol('selectSpace');
class ValueModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetValue(node);
    }
    else {
      getUINativeModule().select.setValue(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ValueModifier.identity = Symbol('selectValue');
class SelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetSelected(node);
    }
    else {
      getUINativeModule().select.setSelected(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedModifier.identity = Symbol('selectSelected');
class SelectFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetFontColor(node);
    }
    else {
      getUINativeModule().select.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectFontColorModifier.identity = Symbol('selectFontColor');
class SelectedOptionBgColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionBgColor(node);
    }
    else {
      getUINativeModule().select.setSelectedOptionBgColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedOptionBgColorModifier.identity = Symbol('selectSelectedOptionBgColor');
class OptionBgColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetOptionBgColor(node);
    }
    else {
      getUINativeModule().select.setOptionBgColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
OptionBgColorModifier.identity = Symbol('selectOptionBgColor');
class OptionFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetOptionFontColor(node);
    }
    else {
      getUINativeModule().select.setOptionFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
OptionFontColorModifier.identity = Symbol('selectOptionFontColor');
class SelectedOptionFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().select.resetSelectedOptionFontColor(node);
    }
    else {
      getUINativeModule().select.setSelectedOptionFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedOptionFontColorModifier.identity = Symbol('selectSelectedOptionFontColor');
// @ts-ignore
globalThis.Select.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSelectComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkRadioComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  checked(value) {
    modifierWithKey(this._modifiersWithKeys, RadioCheckedModifier.identity, RadioCheckedModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  radioStyle(value) {
    modifierWithKey(this._modifiersWithKeys, RadioStyleModifier.identity, RadioStyleModifier, value);
    return this;
  }
}
class RadioCheckedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioChecked(node);
    }
    else {
      getUINativeModule().radio.setRadioChecked(node, this.value);
    }
  }
}
RadioCheckedModifier.identity = Symbol('radioChecked');
class RadioStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().radio.resetRadioStyle(node);
    }
    else {
      getUINativeModule().radio.setRadioStyle(node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
    }
  }
  checkObjectDiff() {
    let checkedBackgroundColorEQ = isBaseOrResourceEqual(this.stageValue.checkedBackgroundColor, this.value.checkedBackgroundColor);
    let uncheckedBorderColorEQ = isBaseOrResourceEqual(this.stageValue.uncheckedBorderColor, this.value.uncheckedBorderColor);
    let indicatorColorEQ = isBaseOrResourceEqual(this.stageValue.indicatorColor, this.value.indicatorColor);
    return !checkedBackgroundColorEQ ||
      !uncheckedBorderColorEQ ||
      !indicatorColorEQ;
  }
}
RadioStyleModifier.identity = Symbol('radioStyle');
// @ts-ignore
globalThis.Radio.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRadioComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTimePickerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  loop(value) {
    throw new Error('Method not implemented.');
  }
  useMilitaryTime(value) {
    throw new Error('Method not implemented.');
  }
  disappearTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerDisappearTextStyleModifier.identity, TimepickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerTextStyleModifier.identity, TimepickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TimepickerSelectedTextStyleModifier.identity, TimepickerSelectedTextStyleModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
}
class TimepickerTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timepicker.resetTextStyle(node);
    }
    else {
      getUINativeModule().timepicker.setTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
      (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
      (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null ||
        _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null ||
        _t === void 0 ? void 0 : _t.family);
    }
  }
}
TimepickerTextStyleModifier.identity = Symbol('textStyle');
class TimepickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timepicker.resetSelectedTextStyle(node);
    }
    else {
      getUINativeModule().timepicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
      (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
      (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null || _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null || _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null || _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null || _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null || _t === void 0 ? void 0 : _t.family);
    }
  }
}
TimepickerSelectedTextStyleModifier.identity = Symbol('selectedTextStyle');
class TimepickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().timepicker.resetDisappearTextStyle(node);
    }
    else {
      getUINativeModule().timepicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, 
      (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, 
      (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, 
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ?
      void 0 : _b.weight) === ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ?
        void 0 : _f.style) === ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null ||
        _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color,
      (_k = this.value) === null || _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null ||
        _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null ||
        _t === void 0 ? void 0 : _t.family);
    }
  }
}
TimepickerDisappearTextStyleModifier.identity = Symbol('disappearTextStyle');
// @ts-ignore
globalThis.TimePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTimePickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTextPickerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  defaultPickerItemHeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerDefaultPickerItemHeightModifier.identity, TextpickerDefaultPickerItemHeightModifier, value);
    return this;
  }
  canLoop(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerCanLoopModifier.identity, TextpickerCanLoopModifier, value);
    return this;
  }
  disappearTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerDisappearTextStyleModifier.identity, TextpickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerTextStyleModifier.identity, TextpickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerSelectedTextStyleModifier.identity, TextpickerSelectedTextStyleModifier, value);
    return this;
  }
  onAccept(callback) {
    throw new Error('Method not implemented.');
  }
  onCancel(callback) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  selectedIndex(value) {
    modifierWithKey(this._modifiersWithKeys, TextpickerSelectedIndexModifier.identity, TextpickerSelectedIndexModifier, value);
    return this;
  }
}
class TextpickerCanLoopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textpicker.resetCanLoop(node);
    }
    else {
      getUINativeModule().textpicker.setCanLoop(node, this.value);
    }
  }
}
TextpickerCanLoopModifier.identity = Symbol('textpickerCanLoop');
class TextpickerSelectedIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textpicker.resetSelectedIndex(node);
    }
    else {
      getUINativeModule().textpicker.setSelectedIndex(node, this.value);
    }
  }
  checkObjectDiff() {
    if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
      return !deepCompareArrays(this.stageValue, this.value);
    }
    else if (Array.isArray(this.stageValue) || Array.isArray(this.value)) {
      return true;
    }
    else {
      return this.stageValue !== this.value;
    }
  }
}
TextpickerSelectedIndexModifier.identity = Symbol('textpickerSelectedIndex');
class TextpickerTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().textpicker.resetTextStyle(node);
    }
    else {
      getUINativeModule().textpicker.setTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e =
      (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h =
      (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, 
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null ||
        _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null ||
        _t === void 0 ? void 0 : _t.family);
    }
  }
}
TextpickerTextStyleModifier.identity = Symbol('textpickerTextStyle');
class TextpickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().textpicker.resetSelectedTextStyle(node);
    }
    else {
      getUINativeModule().textpicker.setSelectedTextStyle(node, (_b =
        (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null &&
        _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null ||
        _c === void 0 ? void 0 : _c.font) === null ||
        _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
        (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
        _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
        (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
        _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
        (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
        _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null ||
        _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null ||
        _t === void 0 ? void 0 : _t.family);
    }
  }
}
TextpickerSelectedTextStyleModifier.identity = Symbol('textpickerSelectedTextStyle');
class TextpickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().textpicker.resetDisappearTextStyle(node);
    }
    else {
      getUINativeModule().textpicker.setDisappearTextStyle(node, (_b =
        (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null &&
        _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null ||
        _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null &&
        _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null ||
        _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null &&
        _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null ||
        _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null &&
        _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null ||
        _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null &&
        _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) === ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) === ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null || _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null || _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null || _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null || _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null || _t === void 0 ? void 0 : _t.family);
    }
  }
}
TextpickerDisappearTextStyleModifier.identity = Symbol('textpickerDisappearTextStyle');
class TextpickerDefaultPickerItemHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
    }
    else {
      getUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
    }
  }
}
TextpickerDefaultPickerItemHeightModifier.identity = Symbol('textpickerDefaultPickerItemHeight');
// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextPickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkSliderComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  blockColor(value) {
    modifierWithKey(this._modifiersWithKeys, BlockColorModifier.identity, BlockColorModifier, value);
    return this;
  }
  trackColor(value) {
    modifierWithKey(this._modifiersWithKeys, TrackColorModifier.identity, TrackColorModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectColorModifier.identity, SelectColorModifier, value);
    return this;
  }
  minLabel(value) {
    throw new Error('Method not implemented.');
  }
  maxLabel(value) {
    throw new Error('Method not implemented.');
  }
  showSteps(value) {
    modifier(this._modifiers, ShowStepsModifier, value);
    return this;
  }
  showTips(value, content) {
    let showTips = new ArkSliderTips(value, content);
    modifierWithKey(this._modifiersWithKeys, ShowTipsModifier.identity, ShowTipsModifier, showTips);
    return this;
  }
  trackThickness(value) {
    modifierWithKey(this._modifiersWithKeys, TrackThicknessModifier.identity, TrackThicknessModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  blockBorderColor(value) {
    modifierWithKey(this._modifiersWithKeys, BlockBorderColorModifier.identity, BlockBorderColorModifier, value);
    return this;
  }
  blockBorderWidth(value) {
    modifierWithKey(this._modifiersWithKeys, BlockBorderWidthModifier.identity, BlockBorderWidthModifier, value);
    return this;
  }
  stepColor(value) {
    modifierWithKey(this._modifiersWithKeys, StepColorModifier.identity, StepColorModifier, value);
    return this;
  }
  trackBorderRadius(value) {
    modifierWithKey(this._modifiersWithKeys, TrackBorderRadiusModifier.identity, TrackBorderRadiusModifier, value);
    return this;
  }
  blockSize(value) {
    modifierWithKey(this._modifiersWithKeys, BlockSizeModifier.identity, BlockSizeModifier, value);
    return this;
  }
  blockStyle(value) {
    modifierWithKey(this._modifiersWithKeys, BlockStyleModifier.identity, BlockStyleModifier, value);
    return this;
  }
  stepSize(value) {
    modifierWithKey(this._modifiersWithKeys, StepSizeModifier.identity, StepSizeModifier, value);
    return this;
  }
}
class BlockStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockStyle(node);
    }
    else {
      getUINativeModule().slider.setBlockStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.type === this.value.type &&
      this.stageValue.image === this.value.image &&
      this.stageValue.shape === this.value.shape);
  }
}
BlockStyleModifier.identity = Symbol('sliderBlockStyle');
class ShowTipsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a;
    if (reset) {
      getUINativeModule().slider.resetShowTips(node);
    }
    else {
      getUINativeModule().slider.setShowTips(node, this.value.showTip, (_a = this.value) === null || _a === void 0 ? void 0 : _a.tipText);
    }
  }
  checkObjectDiff() {
    let showTipDiff = this.stageValue.showTip !== this.value.showTip;
    let tipTextDiff = !isBaseOrResourceEqual(this.stageValue.tipText, this.value.tipText);
    return showTipDiff || tipTextDiff;
  }
}
ShowTipsModifier.identity = Symbol('sliderShowTips');
class StepSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetStepSize(node);
    }
    else {
      getUINativeModule().slider.setStepSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StepSizeModifier.identity = Symbol('sliderStepSize');
class BlockSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockSize(node);
    }
    else {
      getUINativeModule().slider.setBlockSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue.height) && isResource(this.value.height) && isResource(this.stageValue.width) && isResource(this.value.width)) {
      return !(isResourceEqual(this.stageValue.height, this.value.height) && isResourceEqual(this.stageValue.width, this.value.width));
    }
    else {
      return true;
    }
  }
}
BlockSizeModifier.identity = Symbol('sliderBlockSize');
class TrackBorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetTrackBorderRadius(node);
    }
    else {
      getUINativeModule().slider.setTrackBorderRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackBorderRadiusModifier.identity = Symbol('sliderTrackBorderRadius');
class StepColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetStepColor(node);
    }
    else {
      getUINativeModule().slider.setStepColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StepColorModifier.identity = Symbol('sliderStepColor');
class BlockBorderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderColor(node);
    }
    else {
      getUINativeModule().slider.setBlockBorderColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockBorderColorModifier.identity = Symbol('sliderBlockBorderColor');
class BlockBorderWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockBorderWidth(node);
    }
    else {
      getUINativeModule().slider.setBlockBorderWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockBorderWidthModifier.identity = Symbol('sliderBlockBorderWidth');
class BlockColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetBlockColor(node);
    }
    else {
      getUINativeModule().slider.setBlockColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BlockColorModifier.identity = Symbol('sliderBlockColor');
class TrackColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetTrackBackgroundColor(node);
    }
    else {
      getUINativeModule().slider.setTrackBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackColorModifier.identity = Symbol('sliderTrackColor');
class SelectColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetSelectColor(node);
    }
    else {
      getUINativeModule().slider.setSelectColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectColorModifier.identity = Symbol('sliderSelectColor');
class ShowStepsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetShowSteps(node);
    }
    else {
      getUINativeModule().slider.setShowSteps(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ShowStepsModifier.identity = Symbol('sliderShowSteps');
class TrackThicknessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().slider.resetThickness(node);
    }
    else {
      getUINativeModule().slider.setThickness(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TrackThicknessModifier.identity = Symbol('sliderTrackThickness');
// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSliderComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class RatingStarsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.resetStars(node);
    }
    else {
      getUINativeModule().rating.setStars(node, this.value);
    }
  }
}
RatingStarsModifier.identity = Symbol('ratingStars');
class RatingStepSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.resetStepSize(node);
    }
    else {
      getUINativeModule().rating.setStepSize(node, this.value);
    }
  }
}
RatingStepSizeModifier.identity = Symbol('ratingStepSize');
class RatingStarStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().rating.resetStarStyle(node);
    }
    else {
      getUINativeModule().rating.setStarStyle(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.backgroundUri, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.foregroundUri, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.secondaryUri);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f;
    return ((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.backgroundUri) !==
      ((_b = this.value) === null || _b === void 0 ? void 0 : _b.backgroundUri) ||
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.foregroundUri) !==
      ((_d = this.value) === null || _d === void 0 ? void 0 : _d.foregroundUri) ||
      ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.secondaryUri) !==
      ((_f = this.value) === null || _f === void 0 ? void 0 : _f.secondaryUri);
  }
}
RatingStarStyleModifier.identity = Symbol('ratingStarStyle');
class ArkRatingComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  stars(value) {
    modifierWithKey(this._modifiersWithKeys, RatingStarsModifier.identity, RatingStarsModifier, value);
    return this;
  }
  stepSize(value) {
    modifierWithKey(this._modifiersWithKeys, RatingStepSizeModifier.identity, RatingStepSizeModifier, value);
    return this;
  }
  starStyle(value) {
    let starStyle = new ArkStarStyle();
    if (!isUndefined(value)) {
      starStyle.backgroundUri = value.backgroundUri;
      starStyle.foregroundUri = value.foregroundUri;
      starStyle.secondaryUri = value.secondaryUri;
      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, undefined);
    }
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Rating.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRatingComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkCheckboxComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  shape(value) {
    throw new Error('Method not implemented.');
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxWidthModifier.identity, CheckboxWidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxHeightModifier.identity, CheckboxHeightModifier, value);
    return this;
  }
  select(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxSelectModifier.identity, CheckboxSelectModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxSelectedColorModifier.identity, CheckboxSelectedColorModifier, value);
    return this;
  }
  unselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxUnselectedColorModifier.identity, CheckboxUnselectedColorModifier, value);
    return this;
  }
  mark(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxMarkModifier.identity, CheckboxMarkModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
}
class CheckboxMarkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().checkbox.resetMark(node);
    }
    else {
      getUINativeModule().checkbox.setMark(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.size, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.strokeWidth);
    }
  }
  checkObjectDiff() {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;
  }
}
CheckboxMarkModifier.identity = Symbol('checkboxMark');
class CheckboxSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetSelect(node);
    }
    else {
      getUINativeModule().checkbox.setSelect(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
CheckboxSelectModifier.identity = Symbol('checkboxSelect');
class CheckboxHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetHeight(node);
    }
    else {
      getUINativeModule().checkbox.setHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxHeightModifier.identity = Symbol('checkboxHeight');
class CheckboxWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetWidth(node);
    }
    else {
      getUINativeModule().checkbox.setWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxWidthModifier.identity = Symbol('checkboxWidth');
class CheckboxSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetSelectedColor(node);
    }
    else {
      getUINativeModule().checkbox.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxSelectedColorModifier.identity = Symbol('checkboxSelectedColor');
class CheckboxUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkbox.resetUnSelectedColor(node);
    }
    else {
      getUINativeModule().checkbox.setUnSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxUnselectedColorModifier.identity = Symbol('checkboxUnselectedColor');
// @ts-ignore
globalThis.Checkbox.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkNavDestinationComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  title(value) {
    throw new Error('Method not implemented.');
  }
  hideTitleBar(value) {
    modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, value);
    return this;
  }
  onShown(callback) {
    throw new Error('Method not implemented.');
  }
  onHidden(callback) {
    throw new Error('Method not implemented.');
  }
  onBackPressed(callback) {
    throw new Error('Method not implemented.');
  }
}
class HideTitleBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetHideTitleBar(node);
    }
    else {
      getUINativeModule().navDestination.setHideTitleBar(node, this.value);
    }
  }
}
HideTitleBarModifier.identity = Symbol('hideTitleBar');
//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavDestinationComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkCounterComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onInc(event) {
    throw new Error('Method not implemented.');
  }
  onDec(event) {
    throw new Error('Method not implemented.');
  }
  enableDec(value) {
    modifierWithKey(this._modifiersWithKeys, EnableDecModifier.identity, EnableDecModifier, value);
    return this;
  }
  enableInc(value) {
    modifierWithKey(this._modifiersWithKeys, EnableIncModifier.identity, EnableIncModifier, value);
    return this;
  }
}
class EnableIncModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().counter.resetEnableInc(node);
    }
    else {
      getUINativeModule().counter.setEnableInc(node, this.value);
    }
  }
}
EnableIncModifier.identity = Symbol('enableInc');
class EnableDecModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().counter.resetEnableDec(node);
    }
    else {
      getUINativeModule().counter.setEnableDec(node, this.value);
    }
  }
}
EnableDecModifier.identity = Symbol('enableDec');
// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCounterComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class CheckboxGroupSelectAllModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectAll(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(node, this.value);
    }
  }
}
CheckboxGroupSelectAllModifier.identity = Symbol('checkboxgroupSelectAll');
class CheckboxGroupSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupSelectedColor(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupSelectedColorModifier.identity = Symbol('checkboxgroupSelectedColor');
class CheckboxGroupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupUnSelectedColor(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupUnSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CheckboxGroupUnselectedColorModifier.identity = Symbol('checkboxgroupUnselectedColor');
class CheckboxGroupMarkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      getUINativeModule().checkboxgroup.resetCheckboxGroupMark(node);
    }
    else {
      getUINativeModule().checkboxgroup.setCheckboxGroupMark(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.size, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.strokeWidth);
    }
  }
  checkObjectDiff() {
    let colorEQ = isBaseOrResourceEqual(this.stageValue.strokeColor, this.value.strokeColor);
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let widthEQ = isBaseOrResourceEqual(this.stageValue.strokeWidth, this.value.strokeWidth);
    return !colorEQ || !sizeEQ || !widthEQ;
  }
}
CheckboxGroupMarkModifier.identity = Symbol('checkboxgroupMark');
class ArkCheckboxGroupComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  selectAll(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectAllModifier.identity, CheckboxGroupSelectAllModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupSelectedColorModifier.identity, CheckboxGroupSelectedColorModifier, value);
    return this;
  }
  unselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupUnselectedColorModifier.identity, CheckboxGroupUnselectedColorModifier, value);
    return this;
  }
  mark(value) {
    modifierWithKey(this._modifiersWithKeys, CheckboxGroupMarkModifier.identity, CheckboxGroupMarkModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.CheckboxGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkPanelComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  mode(value) {
    modifierWithKey(this._modifiersWithKeys, PanelModeModifier.identity, PanelModeModifier, value);
    return this;
  }
  type(value) {
    modifierWithKey(this._modifiersWithKeys, PanelTypeModifier.identity, PanelTypeModifier, value);
    return this;
  }
  dragBar(value) {
    modifierWithKey(this._modifiersWithKeys, DragBarModifier.identity, DragBarModifier, value);
    return this;
  }
  customHeight(value) {
    modifierWithKey(this._modifiersWithKeys, PanelCustomHeightModifier.identity, PanelCustomHeightModifier, value);
    return this;
  }
  fullHeight(value) {
    modifierWithKey(this._modifiersWithKeys, PanelFullHeightModifier.identity, PanelFullHeightModifier, value);
    return this;
  }
  halfHeight(value) {
    modifierWithKey(this._modifiersWithKeys, PanelHalfHeightModifier.identity, PanelHalfHeightModifier, value);
    return this;
  }
  miniHeight(value) {
    modifierWithKey(this._modifiersWithKeys, PanelMiniHeightModifier.identity, PanelMiniHeightModifier, value);
    return this;
  }
  show(value) {
    modifierWithKey(this._modifiersWithKeys, ShowModifier.identity, ShowModifier, value);
    return this;
  }
  backgroundMask(color) {
    modifierWithKey(this._modifiersWithKeys, PanelBackgroundMaskModifier.identity, PanelBackgroundMaskModifier, color);
    return this;
  }
  showCloseIcon(value) {
    modifierWithKey(this._modifiersWithKeys, ShowCloseIconModifier.identity, ShowCloseIconModifier, value);
    return this;
  }
  onChange(event) {
    throw new Error('Method not implemented.');
  }
  onHeightChange(callback) {
    throw new Error('Method not implemented.');
  }
}
class PanelBackgroundMaskModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelBackgroundMask(node);
    }
    else {
      getUINativeModule().panel.setPanelBackgroundMask(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelBackgroundMaskModifier.identity = Symbol('panelBackgroundMask');
class PanelModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelMode(node);
    }
    else {
      getUINativeModule().panel.setPanelMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelModeModifier.identity = Symbol('panelMode');
class PanelTypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelType(node);
    }
    else {
      getUINativeModule().panel.setPanelType(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelTypeModifier.identity = Symbol('panelType');
class PanelCustomHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelCustomHeight(node);
    }
    else {
      getUINativeModule().panel.setPanelCustomHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelCustomHeightModifier.identity = Symbol('panelCustomHeight');
class PanelFullHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelFullHeight(node);
    }
    else {
      getUINativeModule().panel.setPanelFullHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelFullHeightModifier.identity = Symbol('panelFullHeight');
class PanelHalfHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelHalfHeight(node);
    }
    else {
      getUINativeModule().panel.setPanelHalfHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelHalfHeightModifier.identity = Symbol('panelHalfHeight');
class PanelMiniHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetPanelMiniHeight(node);
    }
    else {
      getUINativeModule().panel.setPanelMiniHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PanelMiniHeightModifier.identity = Symbol('panelMiniHeight');
class ShowCloseIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetShowCloseIcon(node);
    }
    else {
      getUINativeModule().panel.setShowCloseIcon(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ShowCloseIconModifier.identity = Symbol('showCloseIcon');
class DragBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetDragBar(node);
    }
    else {
      getUINativeModule().panel.setDragBar(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DragBarModifier.identity = Symbol('dragBar');
class ShowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().panel.resetShow(node);
    }
    else {
      getUINativeModule().panel.setShow(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ShowModifier.identity = Symbol('show');
// @ts-ignore
globalThis.Panel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPanelComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
const TITLE_MODE_RANGE = 2;
const NAV_BAR_POSITION_RANGE = 1;
const NAVIGATION_MODE_RANGE = 2;
const DEFAULT_NAV_BAR_WIDTH = 240;
const MIN_NAV_BAR_WIDTH_DEFAULT = '240vp';
const MAX_NAV_BAR_WIDTH_DEFAULT = '40%';
const NAVIGATION_TITLE_MODE_DEFAULT = 0;
const DEFAULT_UNIT = 'vp';
class ArkNavigationComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  navBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, NavBarWidthModifier.identity, NavBarWidthModifier, value);
    return this;
  }
  navBarPosition(value) {
    modifierWithKey(this._modifiersWithKeys, NavBarPositionModifier.identity, NavBarPositionModifier, value);
    return this;
  }
  navBarWidthRange(value) {
    modifierWithKey(this._modifiersWithKeys, NavBarWidthRangeModifier.identity, NavBarWidthRangeModifier, value);
    return this;
  }
  minContentWidth(value) {
    modifierWithKey(this._modifiersWithKeys, MinContentWidthModifier.identity, MinContentWidthModifier, value);
    return this;
  }
  mode(value) {
    modifierWithKey(this._modifiersWithKeys, ModeModifier.identity, ModeModifier, value);
    return this;
  }
  backButtonIcon(value) {
    modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, value);
    return this;
  }
  hideNavBar(value) {
    modifierWithKey(this._modifiersWithKeys, HideNavBarModifier.identity, HideNavBarModifier, value);
    return this;
  }
  title(value) {
    throw new Error('Method not implemented.');
  }
  subTitle(value) {
    modifierWithKey(this._modifiersWithKeys, SubTitleModifier.identity, SubTitleModifier, value);
    return this;
  }
  hideTitleBar(value) {
    modifierWithKey(this._modifiersWithKeys, NavigationHideTitleBarModifier.identity, NavigationHideTitleBarModifier, value);
    return this;
  }
  hideBackButton(value) {
    modifierWithKey(this._modifiersWithKeys, HideBackButtonModifier.identity, HideBackButtonModifier, value);
    return this;
  }
  titleMode(value) {
    modifierWithKey(this._modifiersWithKeys, TitleModeModifier.identity, TitleModeModifier, value);
    return this;
  }
  menus(value) {
    throw new Error('Method not implemented.');
  }
  toolBar(value) {
    throw new Error('Method not implemented.');
  }
  toolbarConfiguration(value) {
    throw new Error('Method not implemented.');
  }
  hideToolBar(value) {
    modifierWithKey(this._modifiersWithKeys, HideToolBarModifier.identity, HideToolBarModifier, value);
    return this;
  }
  onTitleModeChange(callback) {
    throw new Error('Method not implemented.');
  }
  onNavBarStateChange(callback) {
    throw new Error('Method not implemented.');
  }
  onNavigationModeChange(callback) {
    throw new Error('Method not implemented.');
  }
  navDestination(builder) {
    throw new Error('Method not implemented.');
  }
}
class BackButtonIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetBackButtonIcon(node);
    }
    else {
      getUINativeModule().navigation.setBackButtonIcon(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BackButtonIconModifier.identity = Symbol('backButtonIcon');
class NavBarWidthRangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidthRange(node);
    }
    else {
      getUINativeModule().navigation.setNavBarWidthRange(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
NavBarWidthRangeModifier.identity = Symbol('navBarWidthRange');
class MinContentWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetMinContentWidth(node);
    }
    else {
      getUINativeModule().navigation.setMinContentWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MinContentWidthModifier.identity = Symbol('minContentWidth');
class NavBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetNavBarWidth(node);
    }
    else {
      getUINativeModule().navigation.setNavBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
NavBarWidthModifier.identity = Symbol('navBarWidth');
class NavBarPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetNavBarPosition(node);
    }
    else {
      getUINativeModule().navigation.setNavBarPosition(node, this.value);
    }
  }
}
NavBarPositionModifier.identity = Symbol('navBarPosition');
class ModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetMode(node);
    }
    else {
      getUINativeModule().navigation.setMode(node, this.value);
    }
  }
}
ModeModifier.identity = Symbol('mode');
class HideToolBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetHideToolBar(node);
    }
    else {
      getUINativeModule().navigation.setHideToolBar(node, this.value);
    }
  }
}
HideToolBarModifier.identity = Symbol('hideToolBar');
class TitleModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetTitleMode(node);
    }
    else {
      getUINativeModule().navigation.setTitleMode(node, this.value);
    }
  }
}
TitleModeModifier.identity = Symbol('titleMode');
class HideBackButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetHideBackButton(node);
    }
    else {
      getUINativeModule().navigation.setHideBackButton(node, this.value);
    }
  }
}
HideBackButtonModifier.identity = Symbol('hideBackButton');
class SubTitleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetSubTitle(node);
    }
    else {
      getUINativeModule().navigation.setSubTitle(node, this.value);
    }
  }
}
SubTitleModifier.identity = Symbol('subTitle');
class NavigationHideTitleBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetHideTitleBar(node);
    }
    else {
      getUINativeModule().navigation.setHideTitleBar(node, this.value);
    }
  }
}
NavigationHideTitleBarModifier.identity = Symbol('hideTitleBar');
class HideNavBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetHideNavBar(node);
    }
    else {
      getUINativeModule().navigation.setHideNavBar(node, this.value);
    }
  }
}
HideNavBarModifier.identity = Symbol('hideNavBar');
// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavigationComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkNavRouterComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onStateChange(callback) {
    throw new Error('Method not implemented.');
  }
  mode(mode) {
    modifierWithKey(this._modifiersWithKeys, NavRouterModeModifier.identity, NavRouterModeModifier, mode);
    return this;
  }
}
class NavRouterModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navRouter.resetMode(node);
    }
    else {
      getUINativeModule().navRouter.setMode(node, this.value);
    }
  }
}
NavRouterModeModifier.identity = Symbol('mode');
// @ts-ignore
globalThis.NavRouter.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavRouterComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkNavigatorComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  active(value) {
    modifierWithKey(this._modifiersWithKeys, ActiveModifier.identity, ActiveModifier, value);
    return this;
  }
  type(value) {
    modifierWithKey(this._modifiersWithKeys, TypeModifier.identity, TypeModifier, value);
    return this;
  }
  target(value) {
    modifierWithKey(this._modifiersWithKeys, TargetModifier.identity, TargetModifier, value);
    return this;
  }
  params(value) {
    modifierWithKey(this._modifiersWithKeys, ParamsModifier.identity, ParamsModifier, JSON.stringify(value));
    return this;
  }
}
class ParamsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigator.resetParams(node);
    }
    else {
      getUINativeModule().navigator.setParams(node, this.value);
    }
  }
}
ParamsModifier.identity = Symbol('params');
class TypeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigator.resetType(node);
    }
    else {
      getUINativeModule().navigator.setType(node, this.value);
    }
  }
}
TypeModifier.identity = Symbol('type');
class ActiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigator.resetActive(node);
    }
    else {
      getUINativeModule().navigator.setActive(node, this.value);
    }
  }
}
ActiveModifier.identity = Symbol('active');
class TargetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigator.resetTarget(node);
    }
    else {
      getUINativeModule().navigator.setTarget(node, this.value);
    }
  }
}
TargetModifier.identity = Symbol('target');
// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavigatorComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkAlphabetIndexerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onSelected(callback) {
    throw new Error('Method not implemented.');
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, ColorModifier.identity, ColorModifier, value);
    return this;
  }
  selectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedColorModifier.identity, SelectedColorModifier, value);
    return this;
  }
  popupColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupColorModifier.identity, PopupColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedBackgroundColorModifier.identity, SelectedBackgroundColorModifier, value);
    return this;
  }
  popupBackground(value) {
    modifierWithKey(this._modifiersWithKeys, PopupBackgroundModifier.identity, PopupBackgroundModifier, value);
    return this;
  }
  popupSelectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupSelectedColorModifier.identity, PopupSelectedColorModifier, value);
    return this;
  }
  popupUnselectedColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupUnselectedColorModifier.identity, PopupUnselectedColorModifier, value);
    return this;
  }
  popupItemBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, PopupItemBackgroundColorModifier.identity, PopupItemBackgroundColorModifier, value);
    return this;
  }
  usingPopup(value) {
    modifierWithKey(this._modifiersWithKeys, UsingPopupModifier.identity, UsingPopupModifier, value);
    return this;
  }
  selectedFont(value) {
    modifierWithKey(this._modifiersWithKeys, SelectedFontModifier.identity, SelectedFontModifier, value);
    return this;
  }
  popupFont(value) {
    modifierWithKey(this._modifiersWithKeys, PopupFontModifier.identity, PopupFontModifier, value);
    return this;
  }
  popupItemFont(value) {
    modifierWithKey(this._modifiersWithKeys, PopupItemFontModifier.identity, PopupItemFontModifier, value);
    return this;
  }
  itemSize(value) {
    modifierWithKey(this._modifiersWithKeys, ItemSizeModifier.identity, ItemSizeModifier, value);
    return this;
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerFontModifier.identity, AlphabetIndexerFontModifier, value);
    return this;
  }
  alignStyle(value, offset) {
    let alignStyle = new ArkAlignStyle;
    alignStyle.indexerAlign = value;
    alignStyle.offset = offset;
    modifierWithKey(this._modifiersWithKeys, AlignStyleModifier.identity, AlignStyleModifier, alignStyle);
    return this;
  }
  onSelect(callback) {
    throw new Error('Method not implemented.');
  }
  onRequestPopupData(callback) {
    throw new Error('Method not implemented.');
  }
  onPopupSelect(callback) {
    throw new Error('Method not implemented.');
  }
  selected(index) {
    modifierWithKey(this._modifiersWithKeys, AlphabetIndexerSelectedModifier.identity, AlphabetIndexerSelectedModifier, index);
    return this;
  }
  popupPosition(value) {
    modifierWithKey(this._modifiersWithKeys, PopupPositionModifier.identity, PopupPositionModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.AlphabetIndexer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkAlphabetIndexerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
class PopupItemFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
PopupItemFontModifier.identity = Symbol('popupItemFont');
class SelectedFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
SelectedFontModifier.identity = Symbol('alphaBetIndexerSelectedFont');
class PopupFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
PopupFontModifier.identity = Symbol('popupFont');
class AlphabetIndexerFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetFont(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
AlphabetIndexerFontModifier.identity = Symbol('alphaBetIndexerFont');
class PopupItemBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupItemBackgroundColorModifier.identity = Symbol('popupItemBackgroundColor');
class ColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ColorModifier.identity = Symbol('alphabetColor');
class PopupColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupColorModifier.identity = Symbol('popupColor');
class SelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedColorModifier.identity = Symbol('selectedColor');
class PopupBackgroundModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupBackground(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupBackground(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupBackgroundModifier.identity = Symbol('popupBackground');
class SelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SelectedBackgroundColorModifier.identity = Symbol('selectedBackgroundColor');
class PopupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupUnselectedColorModifier.identity = Symbol('popupUnselectedColor');
class PopupSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
PopupSelectedColorModifier.identity = Symbol('popupSelectedColor');
class AlignStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetAlignStyle(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }
  checkObjectDiff() {
    let indexerAlignEQ = isBaseOrResourceEqual(this.stageValue.indexerAlign, this.value.indexerAlign);
    let offsetEQ = isBaseOrResourceEqual(this.stageValue.offset, this.value.offset);
    return !indexerAlignEQ || !offsetEQ;
  }
}
AlignStyleModifier.identity = Symbol('alignStyle');
class UsingPopupModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetUsingPopup(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
    }
  }
}
UsingPopupModifier.identity = Symbol('usingPopup');
class AlphabetIndexerSelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetSelected(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setSelected(node, this.value);
    }
  }
}
AlphabetIndexerSelectedModifier.identity = Symbol('alphabetIndexerSelected');
class ItemSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetItemSize(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setItemSize(node, this.value);
    }
  }
}
ItemSizeModifier.identity = Symbol('itemSize');
class PopupPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().alphabetIndexer.resetPopupPosition(node);
    }
    else {
      getUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
    }
  }
  checkObjectDiff() {
    let xEQ = isBaseOrResourceEqual(this.stageValue.x, this.value.x);
    let yEQ = isBaseOrResourceEqual(this.stageValue.y, this.value.y);
    return !xEQ || !yEQ;
  }
}
PopupPositionModifier.identity = Symbol('popupPosition');

/// <reference path='./import.ts' />
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
class ArkCalendarPickerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
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
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
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

/// <reference path='./import.ts' />
class ArkDataPanelComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  closeEffect(value) {
    modifierWithKey(this._modifiersWithKeys, DataPanelCloseEffectModifier.identity, DataPanelCloseEffectModifier, value);
    return this;
  }
  valueColors(value) {
    modifierWithKey(this._modifiersWithKeys, DataPanelValueColorsModifier.identity, DataPanelValueColorsModifier, value);
    return this;
  }
  trackBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, DataPanelTrackBackgroundColorModifier.identity, DataPanelTrackBackgroundColorModifier, value);
    return this;
  }
  strokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, DataPanelStrokeWidthModifier.identity, DataPanelStrokeWidthModifier, value);
    return this;
  }
  trackShadow(value) {
    modifierWithKey(this._modifiersWithKeys, DataPanelTrackShadowModifier.identity, DataPanelTrackShadowModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class DataPanelStrokeWidthModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
    }
    else {
      getUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DataPanelStrokeWidthModifier.identity = Symbol('dataPanelStrokeWidth');
class DataPanelCloseEffectModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().dataPanel.resetCloseEffect(node);
    }
    else {
      getUINativeModule().dataPanel.setCloseEffect(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DataPanelCloseEffectModifier.identity = Symbol('dataPanelCloseEffect');
class DataPanelTrackBackgroundColorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
    }
    else {
      getUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DataPanelTrackBackgroundColorModifier.identity = Symbol('dataPanelTrackBackgroundColorModifier');
class DataPanelTrackShadowModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      if (this.value === null) {
        getUINativeModule().dataPanel.setDataPanelTrackShadow(node, null);
      }
      getUINativeModule().dataPanel.resetDataPanelTrackShadow(node);
    }
    else {
      getUINativeModule().dataPanel.setDataPanelTrackShadow(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
DataPanelTrackShadowModifier.identity = Symbol('dataPanelTrackShadow');
class DataPanelValueColorsModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().dataPanel.resetDataPanelValueColors(node);
      return;
    }
    else {
      getUINativeModule().dataPanel.setDataPanelValueColors(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
DataPanelValueColorsModifier.identity = Symbol('dataPanelValueColors');
// @ts-ignore
globalThis.DataPanel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDataPanelComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkDatePickerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  lunar(value) {
    modifierWithKey(this._modifiersWithKeys, DatePickerLunarModifier.identity, DatePickerLunarModifier, value);
    return this;
  }
  disappearTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, DatePickerDisappearTextStyleModifier.identity, DatePickerDisappearTextStyleModifier, value);
    return this;
  }
  textStyle(value) {
    modifierWithKey(this._modifiersWithKeys, DatePickerTextStyleModifier.identity, DatePickerTextStyleModifier, value);
    return this;
  }
  selectedTextStyle(value) {
    modifierWithKey(this._modifiersWithKeys, DatePickerSelectedTextStyleModifier.identity, DatePickerSelectedTextStyleModifier, value);
    return this;
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  onDateChange(callback) {
    throw new Error('Method not implemented.');
  }
}
class DatePickerLunarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().datePicker.resetLunar(node);
    }
    else {
      getUINativeModule().datePicker.setLunar(node, this.value);
    }
  }
}
DatePickerLunarModifier.identity = Symbol('lunar');
class DatePickerTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().datePicker.resetTextStyle(node);
    }
    else {
      getUINativeModule().datePicker.setTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
      (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
      ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null || _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null ||
        _t === void 0 ? void 0 : _t.family);
    }
  }
}
DatePickerTextStyleModifier.identity = Symbol('textStyle');
class DatePickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().datePicker.resetSelectedTextStyle(node);
    }
    else {
      getUINativeModule().datePicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
      (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g =
      (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p =
      (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null || _m ===
        void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null || _p ===
        void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null || _r ===
        void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null || _s === void 0 ? void 0 : _s.font) === null || _t ===
        void 0 ? void 0 : _t.family);
    }
  }
}
DatePickerSelectedTextStyleModifier.identity = Symbol('selectedTextStyle');
class DatePickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      getUINativeModule().datePicker.resetDisappearTextStyle(node);
    }
    else {
      getUINativeModule().datePicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined,
      (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null ||
      _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined,
      (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null ||
      _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined,
      (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null ||
      _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined,
      (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null ||
      _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p, _q, _r, _s, _t;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) ===
    ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight) &&
      ((_f = (_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.font) === null || _f === void 0 ? void 0 : _f.style) ===
      ((_h = (_g = this.value) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.style))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_j = this.stageValue) === null || _j === void 0 ? void 0 : _j.color, (_k = this.value) === null ||
      _k === void 0 ? void 0 : _k.color) ||
        !isBaseOrResourceEqual((_m = (_l = this.stageValue) === null || _l === void 0 ? void 0 : _l.font) === null ||
        _m === void 0 ? void 0 : _m.size, (_p = (_o = this.value) === null || _o === void 0 ? void 0 : _o.font) === null ||
        _p === void 0 ? void 0 : _p.size) ||
        !isBaseOrResourceEqual((_r = (_q = this.stageValue) === null || _q === void 0 ? void 0 : _q.font) === null ||
        _r === void 0 ? void 0 : _r.family, (_t = (_s = this.value) === null ||
        _s === void 0 ? void 0 : _s.font) === null || _t === void 0 ? void 0 : _t.family);
    }
  }
}
DatePickerDisappearTextStyleModifier.identity = Symbol('disappearTextStyle');
//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkDatePickerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkFormComponentComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, FormComponentSizeModifier.identity, FormComponentSizeModifier, value);
    return this;
  }
  visibility(value) {
    modifierWithKey(this._modifiersWithKeys, FormComponentVisibilityModifier.identity, FormComponentVisibilityModifier, value);
    return this;
  }
  moduleName(value) {
    modifierWithKey(this._modifiersWithKeys, FormComponentModuleNameModifier.identity, FormComponentModuleNameModifier, value);
    return this;
  }
  dimension(value) {
    modifierWithKey(this._modifiersWithKeys, FormComponentDimensionModifier.identity, FormComponentDimensionModifier, value);
    return this;
  }
  allowUpdate(value) {
    modifierWithKey(this._modifiersWithKeys, FormComponentAllowUpdateModifier.identity, FormComponentAllowUpdateModifier, value);
    return this;
  }
  onAcquired(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
  onRouter(callback) {
    throw new Error('Method not implemented.');
  }
  onUninstall(callback) {
    throw new Error('Method not implemented.');
  }
  onLoad(callback) {
    throw new Error('Method not implemented.');
  }
}
class FormComponentModuleNameModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().formComponent.resetModuleName(node);
    }
    else {
      getUINativeModule().formComponent.setModuleName(node, this.value);
    }
  }
}
FormComponentModuleNameModifier.identity = Symbol('formComponentModuleName');
class FormComponentDimensionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().formComponent.resetDimension(node);
    }
    else {
      getUINativeModule().formComponent.setDimension(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FormComponentDimensionModifier.identity = Symbol('formComponentDimension');
class FormComponentAllowUpdateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().formComponent.resetAllowUpdate(node);
    }
    else {
      getUINativeModule().formComponent.setAllowUpdate(node, this.value);
    }
  }
}
FormComponentAllowUpdateModifier.identity = Symbol('formComponentAllowUpdate');
class FormComponentSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().formComponent.resetSize(node);
    }
    else {
      getUINativeModule().formComponent.setSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    let widthEQ = isBaseOrResourceEqual(this.stageValue.width, this.value.width);
    let heightEQ = isBaseOrResourceEqual(this.stageValue.height, this.value.height);
    return !widthEQ || !heightEQ;
  }
}
FormComponentSizeModifier.identity = Symbol('formComponentSize');
class FormComponentVisibilityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().formComponent.resetVisibility(node);
    }
    else {
      getUINativeModule().formComponent.setVisibility(node, this.value);
    }
  }
}
FormComponentVisibilityModifier.identity = Symbol('formComponentVisibility');
// @ts-ignore
globalThis.FormComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkFormComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkGaugeComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  value(value) {
    modifierWithKey(this._modifiersWithKeys, GaugeVauleModifier.identity, GaugeVauleModifier, value);
    return this;
  }
  startAngle(angle) {
    modifierWithKey(this._modifiersWithKeys, GaugeStartAngleModifier.identity, GaugeStartAngleModifier, angle);
    return this;
  }
  endAngle(angle) {
    modifierWithKey(this._modifiersWithKeys, GaugeEndAngleModifier.identity, GaugeEndAngleModifier, angle);
    return this;
  }
  colors(colors) {
    modifierWithKey(this._modifiersWithKeys, GaugeColorsModifier.identity, GaugeColorsModifier, colors);
    return this;
  }
  strokeWidth(length) {
    modifierWithKey(this._modifiersWithKeys, GaugeStrokeWidthModifier.identity, GaugeStrokeWidthModifier, length);
    return this;
  }
  description(value) {
    throw new Error('Method not implemented.');
  }
  trackShadow(value) {
    modifierWithKey(this._modifiersWithKeys, GaugeTrackShadowModifier.identity, GaugeTrackShadowModifier, value);
    return this;
  }
  indicator(value) {
    modifierWithKey(this._modifiersWithKeys, GaugeIndicatorModifier.identity, GaugeIndicatorModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class GaugeIndicatorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeIndicator(node, this.value);
    }
    else {
      getUINativeModule().gauge.setGaugeIndicator(node, this.value.icon, this.value.space);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.icon, this.value.icon) ||
      !isBaseOrResourceEqual(this.stageValue.space, this.value.space);
  }
}
GaugeIndicatorModifier.identity = Symbol('gaugeIndicator');
class GaugeColorsModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeColors(node);
    }
    else {
      getUINativeModule().gauge.setGaugeColors(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
GaugeColorsModifier.identity = Symbol('gaugeColors');
class GaugeVauleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeVaule(node);
    }
    else {
      getUINativeModule().gauge.setGaugeVaule(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GaugeVauleModifier.identity = Symbol('gaugeVaule');
class GaugeStartAngleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeStartAngle(node);
    }
    else {
      getUINativeModule().gauge.setGaugeStartAngle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GaugeStartAngleModifier.identity = Symbol('gaugeStartAngle');
class GaugeEndAngleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeEndAngle(node);
    }
    else {
      getUINativeModule().gauge.setGaugeEndAngle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GaugeEndAngleModifier.identity = Symbol('gaugeEndAngle');
class GaugeStrokeWidthModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeStrokeWidth(node);
    }
    else {
      getUINativeModule().gauge.setGaugeStrokeWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GaugeStrokeWidthModifier.identity = Symbol('gaugeStrokeWidth');
class GaugeTrackShadowModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gauge.resetGaugeTrackShadow(node);
    }
    else {
      getUINativeModule().gauge.setGaugeTrackShadow(node, this.value, this.value.radius, this.value.offsetX, this.value.offsetY);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
GaugeTrackShadowModifier.identity = Symbol('gaugeTrackShadow');
// @ts-ignore
globalThis.Gauge.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGaugeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkMarqueeComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontSizeModifier.identity, MarqueeFontSizeModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontColorModifier.identity, MarqueeFontColorModifier, value);
    return this;
  }
  allowScale(value) {
    modifierWithKey(this._modifiersWithKeys, MarqueeAllowScaleModifier.identity, MarqueeAllowScaleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontWeightModifier.identity, MarqueeFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, MarqueeFontFamilyModifier.identity, MarqueeFontFamilyModifier, value);
    return this;
  }
  onStart(event) {
    throw new Error('Method not implemented.');
  }
  onBounce(event) {
    throw new Error('Method not implemented.');
  }
  onFinish(event) {
    throw new Error('Method not implemented.');
  }
}
class MarqueeFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().marquee.resetFontColor(node);
    }
    else {
      getUINativeModule().marquee.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MarqueeFontColorModifier.identity = Symbol('fontColor');
class MarqueeFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().marquee.resetFontSize(node);
    }
    else {
      getUINativeModule().marquee.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MarqueeFontSizeModifier.identity = Symbol('fontSize');
class MarqueeAllowScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().marquee.resetAllowScale(node);
    }
    else {
      getUINativeModule().marquee.setAllowScale(node, this.value);
    }
  }
}
MarqueeAllowScaleModifier.identity = Symbol('allowScale');
class MarqueeFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().marquee.resetFontWeight(node);
    }
    else {
      getUINativeModule().marquee.setFontWeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
MarqueeFontWeightModifier.identity = Symbol('fontWeight');
class MarqueeFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().marquee.resetFontFamily(node);
    }
    else {
      getUINativeModule().marquee.setFontFamily(node, this.value);
    }
  }
}
MarqueeFontFamilyModifier.identity = Symbol('fontFamily');
// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMarqueeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class MenuFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetMenuFontColor(node);
    }
    else {
      getUINativeModule().menu.setMenuFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuFontColorModifier.identity = Symbol('fontColor');
class MenuFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menu.resetFont(node);
    }
    else {
      getUINativeModule().menu.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
MenuFontModifier.identity = Symbol('font');
class RadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menu.resetRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        getUINativeModule().menu.setRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        getUINativeModule().menu.setRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
RadiusModifier.identity = Symbol('radius');
class ArkMenuComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  fontSize(value) {
    throw new Error('Method not implemented.');
  }
  font(value) {
    modifierWithKey(this._modifiersWithKeys, MenuFontModifier.identity, MenuFontModifier, value);
    return this;
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, MenuFontColorModifier.identity, MenuFontColorModifier, value);
    return this;
  }
  radius(value) {
    modifierWithKey(this._modifiersWithKeys, RadiusModifier.identity, RadiusModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Menu.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class MenuItemSelectedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetMenuItemSelected(node);
    }
    else {
      getUINativeModule().menuitem.setMenuItemSelected(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
MenuItemSelectedModifier.identity = Symbol('menuItemSelected');
class LabelFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetLabelFontColor(node);
    }
    else {
      getUINativeModule().menuitem.setLabelFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LabelFontColorModifier.identity = Symbol('labelfontColor');
class ContentFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().menuitem.resetContentFontColor(node);
    }
    else {
      getUINativeModule().menuitem.setContentFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ContentFontColorModifier.identity = Symbol('contentfontColor');
class LabelFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      getUINativeModule().menuitem.setLabelFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
LabelFontModifier.identity = Symbol('labelFont');
class ContentFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      getUINativeModule().menuitem.setContentFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    let sizeEQ = isBaseOrResourceEqual(this.stageValue.size, this.value.size);
    let weightEQ = this.stageValue.weight === this.value.weight;
    let familyEQ = isBaseOrResourceEqual(this.stageValue.family, this.value.family);
    let styleEQ = this.stageValue.style === this.value.style;
    return !sizeEQ || !weightEQ || !familyEQ || !styleEQ;
  }
}
ContentFontModifier.identity = Symbol('contentFont');
class ArkMenuItemComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  selected(value) {
    modifierWithKey(this._modifiersWithKeys, MenuItemSelectedModifier.identity, MenuItemSelectedModifier, value);
    return this;
  }
  selectIcon(value) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  contentFont(value) {
    modifierWithKey(this._modifiersWithKeys, ContentFontModifier.identity, ContentFontModifier, value);
    return this;
  }
  contentFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, ContentFontColorModifier.identity, ContentFontColorModifier, value);
    return this;
  }
  labelFont(value) {
    modifierWithKey(this._modifiersWithKeys, LabelFontModifier.identity, LabelFontModifier, value);
    return this;
  }
  labelFontColor(value) {
    modifierWithKey(this._modifiersWithKeys, LabelFontColorModifier.identity, LabelFontColorModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.MenuItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkMenuItemGroupComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.MenuItemGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuItemGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkPluginComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onComplete(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
  size(value) {
    modifierWithKey(this._modifiersWithKeys, PluginSizeModifier.identity, PluginSizeModifier, value);
    return this;
  }
  width(value) {
    modifierWithKey(this._modifiersWithKeys, PluginWidthModifier.identity, PluginWidthModifier, value);
    return this;
  }
  height(value) {
    modifierWithKey(this._modifiersWithKeys, PluginHeightModifier.identity, PluginHeightModifier, value);
    return this;
  }
}
class PluginWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().plugin.resetWidth(node);
    }
    else {
      getUINativeModule().plugin.setWidth(node, this.value);
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
PluginWidthModifier.identity = Symbol('pluginWidth');
class PluginHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().plugin.resetHeight(node);
    }
    else {
      getUINativeModule().plugin.setHeight(node, this.value);
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
PluginHeightModifier.identity = Symbol('pluginHeight');
class PluginSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().plugin.resetSize(node);
    }
    else {
      getUINativeModule().plugin.setSize(node, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.height, this.value.height);
  }
}
PluginSizeModifier.identity = Symbol('size');
// @ts-ignore
globalThis.PluginComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPluginComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkProgressComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  value(value) {
    modifierWithKey(this._modifiersWithKeys, ProgressValueModifier.identity, ProgressValueModifier, value);
    return this;
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, ProgressColorModifier.identity, ProgressColorModifier, value);
    return this;
  }
  style(value) {
    modifierWithKey(this._modifiersWithKeys, ProgressStyleModifier.identity, ProgressStyleModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, ProgressBackgroundColorModifier.identity, ProgressBackgroundColorModifier, value);
    return this;
  }
}
class ProgressValueModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().progress.ResetProgressValue(node);
    }
    else {
      getUINativeModule().progress.SetProgressValue(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ProgressValueModifier.identity = Symbol('value');
class ProgressColorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().progress.resetProgressColor(node);
    }
    else {
      getUINativeModule().progress.setProgressColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ProgressColorModifier.identity = Symbol('color');
class ProgressStyleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().progress.ResetProgressStyle(node);
    }
    else {
      let strokeWidth = this.value.strokeWidth;
      let scaleCount = this.value.scaleCount;
      let scaleWidth = this.value.scaleWidth;
      let enableSmoothEffect = this.value.enableSmoothEffect;
      let borderColor = this.value.borderColor;
      let borderWidth = this.value.borderWidth;
      let content = this.value.content;
      let fontSize;
      let fontWeight;
      let fontFamily;
      let fontStyle;
      if (this.value.font) {
        fontSize = this.value.font.size;
        fontWeight = this.value.font.weight;
        fontFamily = this.value.font.family;
        fontStyle = this.value.font.style;
      }
      let fontColor = this.value.fontColor;
      let enableScanEffect = this.value.enableScanEffect;
      let showDefaultPercentage = this.value.showDefaultPercentage;
      let shadow = this.value.shadow;
      let status = this.value.status;
      let strokeRadius = this.value.strokeRadius;
      getUINativeModule().progress.SetProgressStyle(node, strokeWidth, scaleCount,
        scaleWidth, enableSmoothEffect, borderColor, borderWidth, content, fontSize,
        fontWeight, fontFamily, fontStyle, fontColor, enableScanEffect, showDefaultPercentage,
        shadow, status, strokeRadius);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ProgressStyleModifier.identity = Symbol('style');
class ProgressBackgroundColorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().progress.resetProgressBackgroundColor(node);
    }
    else {
      getUINativeModule().progress.setProgressBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ProgressBackgroundColorModifier.identity = Symbol('progressBackgroundColor');
// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkProgressComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkQRCodeComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, QRColorModifier.identity, QRColorModifier, value);
    return this;
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, QRBackgroundColorModifier.identity, QRBackgroundColorModifier, value);
    return this;
  }
  contentOpacity(value) {
    modifierWithKey(this._modifiersWithKeys, QRContentOpacityModifier.identity, QRContentOpacityModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class QRColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().qrcode.resetQRColor(node);
    }
    else {
      getUINativeModule().qrcode.setQRColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
QRColorModifier.identity = Symbol('color');
class QRBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().qrcode.resetQRBackgroundColor(node);
    }
    else {
      getUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
QRBackgroundColorModifier.identity = Symbol('qrBackgroundColor');
class QRContentOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().qrcode.resetContentOpacity(node);
    }
    else {
      getUINativeModule().qrcode.setContentOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
QRContentOpacityModifier.identity = Symbol('qrContentOpacity');
// @ts-ignore
globalThis.QRCode.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkQRCodeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkRichTextComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onStart(callback) {
    throw new Error('Method not implemented.');
  }
  onComplete(callback) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.RichText.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRichTextComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkScrollBarComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ScrollBar.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkScrollBarComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkStepperComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onFinish(callback) {
    throw new Error('Method not implemented.');
  }
  onSkip(callback) {
    throw new Error('Method not implemented.');
  }
  onChange(callback) {
    throw new Error('Method not implemented.');
  }
  onNext(callback) {
    throw new Error('Method not implemented.');
  }
  onPrevious(callback) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Stepper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStepperComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkStepperItemComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  prevLabel(value) {
    throw new Error('Method not implemented.');
  }
  nextLabel(value) {
    modifierWithKey(this._modifiersWithKeys, NextLabelModifier.identity, NextLabelModifier, value);
    return this;
  }
  status(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class NextLabelModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stepperItem.resetNextLabel(node);
    }
    else {
      getUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}
NextLabelModifier.identity = Symbol('NextLabel');
// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkStepperItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTextClockComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  format(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFormatModifier.identity, TextClockFormatModifier, value);
    return this;
  }
  onDateChange(event) {
    throw new Error('Method not implemented.');
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontColorModifier.identity, TextClockFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontSizeModifier.identity, TextClockFontSizeModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontStyleModifier.identity, TextClockFontStyleModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontWeightModifier.identity, TextClockFontWeightModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextClockFontFamilyModifier.identity, TextClockFontFamilyModifier, value);
    return this;
  }
  textShadow(value) {
    throw new Error('Method not implemented.');
  }
  fontFeature(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class TextClockFormatModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFormat(node);
    }
    else {
      getUINativeModule().textClock.setFormat(node, this.value);
    }
  }
}
TextClockFormatModifier.identity = Symbol('textClockFormat');
class TextClockFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFontColor(node);
    }
    else {
      getUINativeModule().textClock.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontColorModifier.identity = Symbol('textClockFontColor');
class TextClockFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFontSize(node);
    }
    else {
      getUINativeModule().textClock.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontSizeModifier.identity = Symbol('textClockFontSize');
class TextClockFontStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFontStyle(node);
    }
    else {
      getUINativeModule().textClock.setFontStyle(node, this.value);
    }
  }
}
TextClockFontStyleModifier.identity = Symbol('textClockFontStyle');
class TextClockFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFontWeight(node);
    }
    else {
      getUINativeModule().textClock.setFontWeight(node, this.value);
    }
  }
}
TextClockFontWeightModifier.identity = Symbol('textClockFontWeight');
class TextClockFontFamilyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textClock.resetFontFamily(node);
    }
    else {
      getUINativeModule().textClock.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextClockFontFamilyModifier.identity = Symbol('textClockFontFamily');
// @ts-ignore
globalThis.TextClock.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextClockComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTextTimerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  fontColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontColorModifier.identity, TextTimerFontColorModifier, value);
    return this;
  }
  fontSize(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontSizeModifier.identity, TextTimerFontSizeModifier, value);
    return this;
  }
  fontWeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontWeightModifier.identity, TextTimerFontWeightModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontStyleModifier.identity, TextTimerFontStyleModifier, value);
    return this;
  }
  fontFamily(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFontFamilyModifier.identity, TextTimerFontFamilyModifier, value);
    return this;
  }
  format(value) {
    modifierWithKey(this._modifiersWithKeys, TextTimerFormatModifier.identity, TextTimerFormatModifier, value);
    return this;
  }
  onTimer(event) {
    throw new Error('Method not implemented.');
  }
}
class TextTimerFontColorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFontColor(node);
    }
    else {
      getUINativeModule().textTimer.setFontColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTimerFontColorModifier.identity = Symbol('fontColor');
class TextTimerFontSizeModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFontSize(node);
    }
    else {
      getUINativeModule().textTimer.setFontSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTimerFontSizeModifier.identity = Symbol('fontSize');
class TextTimerFontWeightModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFontWeight(node);
    }
    else {
      getUINativeModule().textTimer.setFontWeight(node, this.value);
    }
  }
}
TextTimerFontWeightModifier.identity = Symbol('fontWeight');
class TextTimerFontStyleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFontStyle(node);
    }
    else {
      getUINativeModule().textTimer.setFontStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTimerFontStyleModifier.identity = Symbol('fontStyle');
class TextTimerFontFamilyModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFontFamily(node);
    }
    else {
      getUINativeModule().textTimer.setFontFamily(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextTimerFontFamilyModifier.identity = Symbol('fontFamily');
class TextTimerFormatModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().textTimer.resetFormat(node);
    }
    else {
      getUINativeModule().textTimer.setFormat(node, this.value);
    }
  }
}
TextTimerFormatModifier.identity = Symbol('textTimerFormat');
// @ts-ignore
globalThis.TextTimer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTextTimerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkWebComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  javaScriptAccess(javaScriptAccess) {
    throw new Error('Method not implemented.');
  }
  fileAccess(fileAccess) {
    throw new Error('Method not implemented.');
  }
  onlineImageAccess(onlineImageAccess) {
    throw new Error('Method not implemented.');
  }
  domStorageAccess(domStorageAccess) {
    throw new Error('Method not implemented.');
  }
  imageAccess(imageAccess) {
    throw new Error('Method not implemented.');
  }
  mixedMode(mixedMode) {
    throw new Error('Method not implemented.');
  }
  zoomAccess(zoomAccess) {
    throw new Error('Method not implemented.');
  }
  geolocationAccess(geolocationAccess) {
    throw new Error('Method not implemented.');
  }
  javaScriptProxy(javaScriptProxy) {
    throw new Error('Method not implemented.');
  }
  password(password) {
    throw new Error('Method not implemented.');
  }
  cacheMode(cacheMode) {
    throw new Error('Method not implemented.');
  }
  darkMode(mode) {
    throw new Error('Method not implemented.');
  }
  forceDarkAccess(access) {
    throw new Error('Method not implemented.');
  }
  mediaOptions(options) {
    throw new Error('Method not implemented.');
  }
  tableData(tableData) {
    throw new Error('Method not implemented.');
  }
  wideViewModeAccess(wideViewModeAccess) {
    throw new Error('Method not implemented.');
  }
  overviewModeAccess(overviewModeAccess) {
    throw new Error('Method not implemented.');
  }
  overScrollMode(mode) {
    throw new Error('Method not implemented.');
  }
  textZoomAtio(textZoomAtio) {
    throw new Error('Method not implemented.');
  }
  textZoomRatio(textZoomRatio) {
    throw new Error('Method not implemented.');
  }
  databaseAccess(databaseAccess) {
    throw new Error('Method not implemented.');
  }
  initialScale(percent) {
    throw new Error('Method not implemented.');
  }
  userAgent(userAgent) {
    throw new Error('Method not implemented.');
  }
  onPageEnd(callback) {
    throw new Error('Method not implemented.');
  }
  onPageBegin(callback) {
    throw new Error('Method not implemented.');
  }
  onProgressChange(callback) {
    throw new Error('Method not implemented.');
  }
  onTitleReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onGeolocationHide(callback) {
    throw new Error('Method not implemented.');
  }
  onGeolocationShow(callback) {
    throw new Error('Method not implemented.');
  }
  onRequestSelected(callback) {
    throw new Error('Method not implemented.');
  }
  onAlert(callback) {
    throw new Error('Method not implemented.');
  }
  onBeforeUnload(callback) {
    throw new Error('Method not implemented.');
  }
  onConfirm(callback) {
    throw new Error('Method not implemented.');
  }
  onPrompt(callback) {
    throw new Error('Method not implemented.');
  }
  onConsole(callback) {
    throw new Error('Method not implemented.');
  }
  onErrorReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onHttpErrorReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onDownloadStart(callback) {
    throw new Error('Method not implemented.');
  }
  onRefreshAccessedHistory(callback) {
    throw new Error('Method not implemented.');
  }
  onUrlLoadIntercept(callback) {
    throw new Error('Method not implemented.');
  }
  onSslErrorReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onRenderExited(callback) {
    throw new Error('Method not implemented.');
  }
  onShowFileSelector(callback) {
    throw new Error('Method not implemented.');
  }
  onFileSelectorShow(callback) {
    throw new Error('Method not implemented.');
  }
  onResourceLoad(callback) {
    throw new Error('Method not implemented.');
  }
  onFullScreenExit(callback) {
    throw new Error('Method not implemented.');
  }
  onFullScreenEnter(callback) {
    throw new Error('Method not implemented.');
  }
  onScaleChange(callback) {
    throw new Error('Method not implemented.');
  }
  onHttpAuthRequest(callback) {
    throw new Error('Method not implemented.');
  }
  onInterceptRequest(callback) {
    throw new Error('Method not implemented.');
  }
  onPermissionRequest(callback) {
    throw new Error('Method not implemented.');
  }
  onScreenCaptureRequest(callback) {
    throw new Error('Method not implemented.');
  }
  onContextMenuShow(callback) {
    throw new Error('Method not implemented.');
  }
  mediaPlayGestureAccess(access) {
    throw new Error('Method not implemented.');
  }
  onSearchResultReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onScroll(callback) {
    throw new Error('Method not implemented.');
  }
  onSslErrorEventReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onClientAuthenticationRequest(callback) {
    throw new Error('Method not implemented.');
  }
  onWindowNew(callback) {
    throw new Error('Method not implemented.');
  }
  onWindowExit(callback) {
    throw new Error('Method not implemented.');
  }
  multiWindowAccess(multiWindow) {
    throw new Error('Method not implemented.');
  }
  onInterceptKeyEvent(callback) {
    throw new Error('Method not implemented.');
  }
  webStandardFont(family) {
    throw new Error('Method not implemented.');
  }
  webSerifFont(family) {
    throw new Error('Method not implemented.');
  }
  webSansSerifFont(family) {
    throw new Error('Method not implemented.');
  }
  webFixedFont(family) {
    throw new Error('Method not implemented.');
  }
  webFantasyFont(family) {
    throw new Error('Method not implemented.');
  }
  webCursiveFont(family) {
    throw new Error('Method not implemented.');
  }
  defaultFixedFontSize(size) {
    throw new Error('Method not implemented.');
  }
  defaultFontSize(size) {
    throw new Error('Method not implemented.');
  }
  minFontSize(size) {
    throw new Error('Method not implemented.');
  }
  minLogicalFontSize(size) {
    throw new Error('Method not implemented.');
  }
  blockNetwork(block) {
    throw new Error('Method not implemented.');
  }
  horizontalScrollBarAccess(horizontalScrollBar) {
    throw new Error('Method not implemented.');
  }
  verticalScrollBarAccess(verticalScrollBar) {
    throw new Error('Method not implemented.');
  }
  onTouchIconUrlReceived(callback) {
    throw new Error('Method not implemented.');
  }
  onFaviconReceived(callback) {
    throw new Error('Method not implemented.');
  }
  onPageVisible(callback) {
    throw new Error('Method not implemented.');
  }
  onDataResubmitted(callback) {
    throw new Error('Method not implemented.');
  }
  pinchSmooth(isEnabled) {
    throw new Error('Method not implemented.');
  }
  allowWindowOpenMethod(flag) {
    throw new Error('Method not implemented.');
  }
  onAudioStateChanged(callback) {
    throw new Error('Method not implemented.');
  }
  onFirstContentfulPaint(callback) {
    throw new Error('Method not implemented.');
  }
  onLoadIntercept(callback) {
    throw new Error('Method not implemented.');
  }
  onControllerAttached(callback) {
    throw new Error('Method not implemented.');
  }
  onOverScroll(callback) {
    throw new Error('Method not implemented.');
  }
  javaScriptOnDocumentStart(scripts) {
    throw new Error('Method not implemented.');
  }
  layoutMode(mode) {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Web.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWebComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkXComponentComponent {
  constructor(nativePtr) {
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
  }
  applyModifierPatch() {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  width(value) {
    throw new Error('Method not implemented.');
  }
  height(value) {
    throw new Error('Method not implemented.');
  }
  expandSafeArea(types, edges) {
    throw new Error('Method not implemented.');
  }
  responseRegion(value) {
    throw new Error('Method not implemented.');
  }
  mouseResponseRegion(value) {
    throw new Error('Method not implemented.');
  }
  size(value) {
    throw new Error('Method not implemented.');
  }
  constraintSize(value) {
    throw new Error('Method not implemented.');
  }
  touchable(value) {
    throw new Error('Method not implemented.');
  }
  hitTestBehavior(value) {
    throw new Error('Method not implemented.');
  }
  layoutWeight(value) {
    throw new Error('Method not implemented.');
  }
  padding(value) {
    throw new Error('Method not implemented.');
  }
  margin(value) {
    throw new Error('Method not implemented.');
  }
  background(builder, options) {
    throw new Error('Method not implemented.');
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundColorModifier.identity, XComponentBackgroundColorModifier, value);
    return this;
  }
  backgroundImage(src, repeat) {
    throw new Error('Method not implemented.');
  }
  backgroundImageSize(value) {
    throw new Error('Method not implemented.');
  }
  backgroundImagePosition(value) {
    throw new Error('Method not implemented.');
  }
  backgroundBlurStyle(value, options) {
    throw new Error('Method not implemented.');
  }
  foregroundBlurStyle(value, options) {
    throw new Error('Method not implemented.');
  }
  opacity(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentOpacityModifier.identity, XComponentOpacityModifier, value);
    return this;
  }
  border(value) {
    throw new Error('Method not implemented.');
  }
  borderStyle(value) {
    throw new Error('Method not implemented.');
  }
  borderWidth(value) {
    throw new Error('Method not implemented.');
  }
  borderColor(value) {
    throw new Error('Method not implemented.');
  }
  borderRadius(value) {
    throw new Error('Method not implemented.');
  }
  borderImage(value) {
    throw new Error('Method not implemented.');
  }
  foregroundColor(value) {
    throw new Error('Method not implemented.');
  }
  onClick(event) {
    throw new Error('Method not implemented.');
  }
  onHover(event) {
    throw new Error('Method not implemented.');
  }
  hoverEffect(value) {
    throw new Error('Method not implemented.');
  }
  onMouse(event) {
    throw new Error('Method not implemented.');
  }
  onTouch(event) {
    throw new Error('Method not implemented.');
  }
  onKeyEvent(event) {
    throw new Error('Method not implemented.');
  }
  focusable(value) {
    throw new Error('Method not implemented.');
  }
  onFocus(event) {
    throw new Error('Method not implemented.');
  }
  onBlur(event) {
    throw new Error('Method not implemented.');
  }
  tabIndex(index) {
    throw new Error('Method not implemented.');
  }
  defaultFocus(value) {
    throw new Error('Method not implemented.');
  }
  groupDefaultFocus(value) {
    throw new Error('Method not implemented.');
  }
  focusOnTouch(value) {
    throw new Error('Method not implemented.');
  }
  animation(value) {
    throw new Error('Method not implemented.');
  }
  transition(value) {
    throw new Error('Method not implemented.');
  }
  gesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  priorityGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  parallelGesture(gesture, mask) {
    throw new Error('Method not implemented.');
  }
  blur(value) {
    throw new Error('Method not implemented.');
  }
  linearGradientBlur(value, options) {
    throw new Error('Method not implemented.');
  }
  brightness(value) {
    throw new Error('Method not implemented.');
  }
  contrast(value) {
    throw new Error('Method not implemented.');
  }
  grayscale(value) {
    throw new Error('Method not implemented.');
  }
  colorBlend(value) {
    throw new Error('Method not implemented.');
  }
  saturate(value) {
    throw new Error('Method not implemented.');
  }
  sepia(value) {
    throw new Error('Method not implemented.');
  }
  invert(value) {
    throw new Error('Method not implemented.');
  }
  hueRotate(value) {
    throw new Error('Method not implemented.');
  }
  useEffect(value) {
    throw new Error('Method not implemented.');
  }
  backdropBlur(value) {
    throw new Error('Method not implemented.');
  }
  renderGroup(value) {
    throw new Error('Method not implemented.');
  }
  translate(value) {
    throw new Error('Method not implemented.');
  }
  scale(value) {
    throw new Error('Method not implemented.');
  }
  gridSpan(value) {
    throw new Error('Method not implemented.');
  }
  gridOffset(value) {
    throw new Error('Method not implemented.');
  }
  rotate(value) {
    throw new Error('Method not implemented.');
  }
  transform(value) {
    throw new Error('Method not implemented.');
  }
  onAppear(event) {
    throw new Error('Method not implemented.');
  }
  onDisAppear(event) {
    throw new Error('Method not implemented.');
  }
  onAreaChange(event) {
    throw new Error('Method not implemented.');
  }
  visibility(value) {
    throw new Error('Method not implemented.');
  }
  flexGrow(value) {
    throw new Error('Method not implemented.');
  }
  flexShrink(value) {
    throw new Error('Method not implemented.');
  }
  flexBasis(value) {
    throw new Error('Method not implemented.');
  }
  alignSelf(value) {
    throw new Error('Method not implemented.');
  }
  displayPriority(value) {
    throw new Error('Method not implemented.');
  }
  zIndex(value) {
    throw new Error('Method not implemented.');
  }
  sharedTransition(id, options) {
    throw new Error('Method not implemented.');
  }
  direction(value) {
    throw new Error('Method not implemented.');
  }
  align(value) {
    throw new Error('Method not implemented.');
  }
  position(value) {
    throw new Error('Method not implemented.');
  }
  markAnchor(value) {
    throw new Error('Method not implemented.');
  }
  offset(value) {
    throw new Error('Method not implemented.');
  }
  enabled(value) {
    throw new Error('Method not implemented.');
  }
  useSizeType(value) {
    throw new Error('Method not implemented.');
  }
  alignRules(value) {
    throw new Error('Method not implemented.');
  }
  aspectRatio(value) {
    throw new Error('Method not implemented.');
  }
  clickEffect(value) {
    throw new Error('Method not implemented.');
  }
  onDragStart(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnter(event) {
    throw new Error('Method not implemented.');
  }
  onDragMove(event) {
    throw new Error('Method not implemented.');
  }
  onDragLeave(event) {
    throw new Error('Method not implemented.');
  }
  onDrop(event) {
    throw new Error('Method not implemented.');
  }
  onDragEnd(event) {
    throw new Error('Method not implemented.');
  }
  allowDrop(value) {
    throw new Error('Method not implemented.');
  }
  draggable(value) {
    throw new Error('Method not implemented.');
  }
  overlay(value, options) {
    throw new Error('Method not implemented.');
  }
  linearGradient(value) {
    throw new Error('Method not implemented.');
  }
  sweepGradient(value) {
    throw new Error('Method not implemented.');
  }
  radialGradient(value) {
    throw new Error('Method not implemented.');
  }
  motionPath(value) {
    throw new Error('Method not implemented.');
  }
  shadow(value) {
    modifierWithKey(this._modifiersWithKeys, ShadowModifier.identity, ShadowModifier, value);
    return this;
  }
  blendMode(value) {
    throw new Error('Method not implemented.');
  }
  clip(value) {
    throw new Error('Method not implemented.');
  }
  mask(value) {
    throw new Error('Method not implemented.');
  }
  key(value) {
    throw new Error('Method not implemented.');
  }
  id(value) {
    throw new Error('Method not implemented.');
  }
  geometryTransition(id) {
    throw new Error('Method not implemented.');
  }
  bindPopup(show, popup) {
    throw new Error('Method not implemented.');
  }
  bindMenu(content, options) {
    throw new Error('Method not implemented.');
  }
  bindContextMenu(content, responseType, options) {
    throw new Error('Method not implemented.');
  }
  bindContentCover(isShow, builder, options) {
    throw new Error('Method not implemented.');
  }
  bindSheet(isShow, builder, options) {
    throw new Error('Method not implemented.');
  }
  stateStyles(value) {
    throw new Error('Method not implemented.');
  }
  restoreId(value) {
    throw new Error('Method not implemented.');
  }
  onVisibleAreaChange(ratios, event) {
    throw new Error('Method not implemented.');
  }
  sphericalEffect(value) {
    throw new Error('Method not implemented.');
  }
  lightUpEffect(value) {
    throw new Error('Method not implemented.');
  }
  pixelStretchEffect(options) {
    throw new Error('Method not implemented.');
  }
  keyboardShortcut(value, keys, action) {
    throw new Error('Method not implemented.');
  }
  accessibilityGroup(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityText(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityDescription(value) {
    throw new Error('Method not implemented.');
  }
  accessibilityLevel(value) {
    throw new Error('Method not implemented.');
  }
  obscured(reasons) {
    throw new Error('Method not implemented.');
  }
  reuseId(id) {
    throw new Error('Method not implemented.');
  }
  renderFit(fitMode) {
    throw new Error('Method not implemented.');
  }
  attributeModifier(modifier) {
    return this;
  }
  onGestureJudgeBegin(callback) {
    throw new Error('Method not implemented.');
  }
  onLoad(callback) {
    throw new Error('Method not implemented.');
  }
  onDestroy(event) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.XComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkXComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
class XComponentOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetOpacity(node);
    }
    else {
      getUINativeModule().xComponent.setOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
XComponentOpacityModifier.identity = Symbol('xComponentOpacity');
class XComponentBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetBackgroundColor(node);
    }
    else {
      getUINativeModule().xComponent.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
XComponentBackgroundColorModifier.identity = Symbol('xComponentBackgroundColor');

/// <reference path='./import.ts' />
class ArkBadgeComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Badge.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkBadgeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkFlowItemComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.FlowItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkFlowItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkFormLinkComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.FormLink.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkFormLinkComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class GridItemSelectableModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelectable(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemSelectable(node, this.value);
    }
  }
}
GridItemSelectableModifier.identity = Symbol('gridItemSelectable');
class GridItemSelectedModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemSelected(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemSelected(node, this.value);
    }
  }
}
GridItemSelectedModifier.identity = Symbol('gridItemSelected');
class GridItemRowStartModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowStart(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemRowStart(node, this.value);
    }
  }
}
GridItemRowStartModifier.identity = Symbol('gridItemRowStart');
class GridItemRowEndModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemRowEnd(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemRowEnd(node, this.value);
    }
  }
}
GridItemRowEndModifier.identity = Symbol('gridItemRowEnd');
class GridItemColumnStartModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnStart(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemColumnStart(node, this.value);
    }
  }
}
GridItemColumnStartModifier.identity = Symbol('gridItemColumnStart');
class GridItemColumnEndModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().gridItem.resetGridItemColumnEnd(node);
    }
    else {
      getUINativeModule().gridItem.setGridItemColumnEnd(node, this.value);
    }
  }
}
GridItemColumnEndModifier.identity = Symbol('gridItemColumnEnd');
class ArkGridItemComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  rowStart(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemRowStartModifier.identity, GridItemRowStartModifier, value);
    return this;
  }
  rowEnd(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemRowEndModifier.identity, GridItemRowEndModifier, value);
    return this;
  }
  columnStart(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemColumnStartModifier.identity, GridItemColumnStartModifier, value);
    return this;
  }
  columnEnd(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemColumnEndModifier.identity, GridItemColumnEndModifier, value);
    return this;
  }
  forceRebuild(value) {
    throw new Error('Method not implemented.');
  }
  selectable(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemSelectableModifier.identity, GridItemSelectableModifier, value);
    return this;
  }
  selected(value) {
    modifierWithKey(this._modifiersWithKeys, GridItemSelectedModifier.identity, GridItemSelectedModifier, value);
    return this;
  }
  onSelect(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.GridItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkHyperlinkComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  color(value) {
    modifierWithKey(this._modifiersWithKeys, HyperlinkColorModifier.identity, HyperlinkColorModifier, value);
    return this;
  }
}
class HyperlinkColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().hyperlink.resetColor(node);
    }
    else {
      getUINativeModule().hyperlink.setColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
HyperlinkColorModifier.identity = Symbol('hyperlinkColor');
// @ts-ignore
globalThis.Hyperlink.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkHyperlinkComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ListEditModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetEditMode(node);
    }
    else {
      getUINativeModule().list.setEditMode(node, this.value);
    }
  }
}
ListEditModeModifier.identity = Symbol('editMode');
class ListMultiSelectableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetMultiSelectable(node);
    }
    else {
      getUINativeModule().list.setMultiSelectable(node, this.value);
    }
  }
}
ListMultiSelectableModifier.identity = Symbol('listMultiSelectable');
class ListAlignListItemModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetAlignListItem(node);
    }
    else {
      getUINativeModule().list.setAlignListItem(node, this.value);
    }
  }
}
ListAlignListItemModifier.identity = Symbol('listAlignListItem');
class ListScrollSnapAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetScrollSnapAlign(node);
    }
    else {
      getUINativeModule().list.setScrollSnapAlign(node, this.value);
    }
  }
}
ListScrollSnapAlignModifier.identity = Symbol('listScrollSnapAlign');
class ListDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d;
    if (reset) {
      getUINativeModule().list.resetDivider(node);
    }
    else {
      getUINativeModule().list.setDivider(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.strokeWidth, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.color, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.startMargin, (_d = this.value) === null ||
      _d === void 0 ? void 0 : _d.endMargin);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    return !(((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.strokeWidth) === ((_b = this.value) === null || _b === void 0 ? void 0 : _b.strokeWidth) &&
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) &&
      ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.startMargin) === ((_f = this.value) === null || _f === void 0 ? void 0 : _f.startMargin) &&
      ((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.endMargin) === ((_h = this.value) === null || _h === void 0 ? void 0 : _h.endMargin));
  }
}
ListDividerModifier.identity = Symbol('listDivider');
class ChainAnimationOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g;
    if (reset) {
      getUINativeModule().list.resetChainAnimationOptions(node);
    }
    else {
      getUINativeModule().list.setChainAnimationOptions(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.minSpace, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.maxSpace, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.conductivity, (_d = this.value) === null ||
      _d === void 0 ? void 0 : _d.intensity, (_e = this.value) === null ||
      _e === void 0 ? void 0 : _e.edgeEffect, (_f = this.value) === null ||
      _f === void 0 ? void 0 : _f.stiffness, (_g = this.value) === null ||
      _g === void 0 ? void 0 : _g.damping);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.minSpace === this.value.minSpace && this.stageValue.maxSpace === this.value.maxSpace &&
      this.stageValue.conductivity === this.value.conductivity && this.stageValue.intensity === this.value.intensity &&
      this.stageValue.edgeEffect === this.value.edgeEffect && this.stageValue.stiffness === this.value.stiffness &&
      this.stageValue.damping === this.value.damping);
  }
}
ChainAnimationOptionsModifier.identity = Symbol('chainAnimationOptions');
class ListChainAnimationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetChainAnimation(node);
    }
    else {
      getUINativeModule().list.setChainAnimation(node, this.value);
    }
  }
}
ListChainAnimationModifier.identity = Symbol('listChainAnimation');
class ListCachedCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetCachedCount(node);
    }
    else {
      getUINativeModule().list.setCachedCount(node, this.value);
    }
  }
}
ListCachedCountModifier.identity = Symbol('listCachedCount');
class ListEnableScrollInteractionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetEnableScrollInteraction(node);
    }
    else {
      getUINativeModule().list.setEnableScrollInteraction(node, this.value);
    }
  }
}
ListEnableScrollInteractionModifier.identity = Symbol('listEnableScrollInteraction');
class ListStickyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetSticky(node);
    }
    else {
      getUINativeModule().list.setSticky(node, this.value);
    }
  }
}
ListStickyModifier.identity = Symbol('listSticky');
class ListEdgeEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a;
    if (reset) {
      getUINativeModule().list.resetListEdgeEffect(node);
    }
    else {
      getUINativeModule().list.setListEdgeEffect(node, this.value.value, (_a = this.value.options) === null ||
      _a === void 0 ? void 0 : _a.alwaysEnabled);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}
ListEdgeEffectModifier.identity = Symbol('listEdgeEffect');
class ListListDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListDirection(node);
    }
    else {
      getUINativeModule().list.setListDirection(node, this.value);
    }
  }
}
ListListDirectionModifier.identity = Symbol('listListDirection');
class ListFrictionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListFriction(node);
    }
    else {
      if (!isNumber(this.value) && !isResource(this.value)) {
        getUINativeModule().list.resetListFriction(node);
      }
      else {
        getUINativeModule().list.setListFriction(node, this.value);
      }
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ListFrictionModifier.identity = Symbol('listFriction');
class ListNestedScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().list.resetListNestedScroll(node);
    }
    else {
      getUINativeModule().list.setListNestedScroll(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.scrollForward, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.scrollBackward);
    }
  }
}
ListNestedScrollModifier.identity = Symbol('listNestedScroll');
class ListScrollBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListScrollBar(node);
    }
    else {
      getUINativeModule().list.setListScrollBar(node, this.value);
    }
  }
}
ListScrollBarModifier.identity = Symbol('listScrollBar');
class ListLanesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListLanes(node);
    }
    else {
      getUINativeModule().list.setListLanes(node, this.value.lanesNum, this.value.minLength, this.value.maxLength, this.value.gutter);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListLanesModifier.identity = Symbol('listLanes');
class ArkListComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  lanes(value, gutter) {
    let opt = new ArkLanesOpt();
    opt.gutter = gutter;
    if (isUndefined(value)) {
      opt.lanesNum = undefined;
    }
    else if (isNumber(value)) {
      opt.lanesNum = value;
    }
    else {
      const lc = value;
      opt.minLength = lc.minLength;
      opt.maxLength = lc.maxLength;
    }
    modifierWithKey(this._modifiersWithKeys, ListLanesModifier.identity, ListLanesModifier, opt);
    return this;
  }
  alignListItem(value) {
    modifierWithKey(this._modifiersWithKeys, ListAlignListItemModifier.identity, ListAlignListItemModifier, value);
    return this;
  }
  listDirection(value) {
    modifierWithKey(this._modifiersWithKeys, ListListDirectionModifier.identity, ListListDirectionModifier, value);
    return this;
  }
  scrollBar(value) {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarModifier.identity, ListScrollBarModifier, value);
    return this;
  }
  edgeEffect(value, options) {
    let effect = new ArkListEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, ListEdgeEffectModifier.identity, ListEdgeEffectModifier, effect);
    return this;
  }
  contentStartOffset(value) {
    throw new Error('Method not implemented.');
  }
  contentEndOffset(value) {
    throw new Error('Method not implemented.');
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ListDividerModifier.identity, ListDividerModifier, value);
    return this;
  }
  editMode(value) {
    modifierWithKey(this._modifiersWithKeys, ListEditModeModifier.identity, ListEditModeModifier, value);
    return this;
  }
  multiSelectable(value) {
    modifierWithKey(this._modifiersWithKeys, ListMultiSelectableModifier.identity, ListMultiSelectableModifier, value);
    return this;
  }
  cachedCount(value) {
    modifierWithKey(this._modifiersWithKeys, ListCachedCountModifier.identity, ListCachedCountModifier, value);
    return this;
  }
  chainAnimation(value) {
    modifierWithKey(this._modifiersWithKeys, ListChainAnimationModifier.identity, ListChainAnimationModifier, value);
    return this;
  }
  chainAnimationOptions(value) {
    modifierWithKey(this._modifiersWithKeys, ChainAnimationOptionsModifier.identity, ChainAnimationOptionsModifier, value);
    return this;
  }
  sticky(value) {
    modifierWithKey(this._modifiersWithKeys, ListStickyModifier.identity, ListStickyModifier, value);
    return this;
  }
  scrollSnapAlign(value) {
    modifierWithKey(this._modifiersWithKeys, ListScrollSnapAlignModifier.identity, ListScrollSnapAlignModifier, value);
    return this;
  }
  nestedScroll(value) {
    modifierWithKey(this._modifiersWithKeys, ListNestedScrollModifier.identity, ListNestedScrollModifier, value);
    return this;
  }
  enableScrollInteraction(value) {
    modifierWithKey(this._modifiersWithKeys, ListEnableScrollInteractionModifier.identity, ListEnableScrollInteractionModifier, value);
    return this;
  }
  friction(value) {
    modifierWithKey(this._modifiersWithKeys, ListFrictionModifier.identity, ListFrictionModifier, value);
    return this;
  }
  onScroll(event) {
    throw new Error('Method not implemented.');
  }
  onScrollIndex(event) {
    throw new Error('Method not implemented.');
  }
  onReachStart(event) {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStart(event) {
    throw new Error('Method not implemented.');
  }
  onScrollStop(event) {
    throw new Error('Method not implemented.');
  }
  onItemDelete(event) {
    throw new Error('Method not implemented.');
  }
  onItemMove(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragStart(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragEnter(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragMove(event) {
    throw new Error('Method not implemented.');
  }
  onItemDragLeave(event) {
    throw new Error('Method not implemented.');
  }
  onItemDrop(event) {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.List.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ListItemSelectedModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItem.resetListItemSelected(node);
    }
    else {
      getUINativeModule().listItem.setListItemSelected(node, this.value);
    }
  }
}
ListItemSelectedModifier.identity = Symbol('listItemSelected');
class ListItemSelectableModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItem.resetSelectable(node);
    }
    else {
      getUINativeModule().listItem.setSelectable(node, this.value);
    }
  }
}
ListItemSelectableModifier.identity = Symbol('listItemSelectable');
class ArkListItemComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  sticky(value) {
    throw new Error('Method not implemented.');
  }
  editable(value) {
    throw new Error('Method not implemented.');
  }
  selectable(value) {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectableModifier.identity, ListItemSelectableModifier, value);
    return this;
  }
  selected(value) {
    modifierWithKey(this._modifiersWithKeys, ListItemSelectedModifier.identity, ListItemSelectedModifier, value);
    return this;
  }
  swipeAction(value) {
    throw new Error('Method not implemented.');
  }
  onSelect(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ListItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListItemComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ListItemGroupDividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d;
    if (reset) {
      getUINativeModule().listItemGroup.resetDivider(node);
    }
    else {
      getUINativeModule().listItemGroup.setDivider(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.strokeWidth, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.color, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.startMargin, (_d = this.value) === null ||
      _d === void 0 ? void 0 : _d.endMargin);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    return !(((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.strokeWidth) === ((_b = this.value) === null || _b === void 0 ? void 0 : _b.strokeWidth) &&
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) &&
      ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.startMargin) === ((_f = this.value) === null || _f === void 0 ? void 0 : _f.startMargin) &&
      ((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.endMargin) === ((_h = this.value) === null || _h === void 0 ? void 0 : _h.endMargin));
  }
}
ListItemGroupDividerModifier.identity = Symbol('listItemGroupDivider');
class ArkListItemGroupComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupDividerModifier.identity, ListItemGroupDividerModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.ListItemGroup.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkListItemGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkRelativeContainerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.RelativeContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRelativeContainerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkSwiperComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  index(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperIndexModifier.identity, SwiperIndexModifier, value);
    return this;
  }
  autoPlay(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperAutoPlayModifier.identity, SwiperAutoPlayModifier, value);
    return this;
  }
  interval(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperIntervalModifier.identity, SwiperIntervalModifier, value);
    return this;
  }
  indicator(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, value);
    return this;
  }
  displayArrow(value, isHoverShow) {
    let arkDisplayArrow = new ArkDisplayArrow();
    arkDisplayArrow.value = value;
    arkDisplayArrow.isHoverShow = isHoverShow;
    modifierWithKey(this._modifiersWithKeys, SwiperDisplayArrowModifier.identity, SwiperDisplayArrowModifier, arkDisplayArrow);
    return this;
  }
  loop(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperLoopModifier.identity, SwiperLoopModifier, value);
    return this;
  }
  duration(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperDurationModifier.identity, SwiperDurationModifier, value);
    return this;
  }
  vertical(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperVerticalModifier.identity, SwiperVerticalModifier, value);
    return this;
  }
  itemSpace(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperItemSpaceModifier.identity, SwiperItemSpaceModifier, value);
    return this;
  }
  displayMode(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperDisplayModeModifier.identity, SwiperDisplayModeModifier, value);
    return this;
  }
  cachedCount(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperCachedCountModifier.identity, SwiperCachedCountModifier, value);
    return this;
  }
  displayCount(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperDisplayCountModifier.identity, SwiperDisplayCountModifier, value);
    return this;
  }
  effectMode(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperEffectModeModifier.identity, SwiperEffectModeModifier, value);
    return this;
  }
  disableSwipe(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperDisableSwipeModifier.identity, SwiperDisableSwipeModifier, value);
    return this;
  }
  curve(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperCurveModifier.identity, SwiperCurveModifier, value);
    return this;
  }
  onChange(event) {
    throw new Error('Method not implemented.');
  }
  indicatorStyle(value) {
    throw new Error('Method not implemented.');
  }
  prevMargin(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperPrevMarginModifier.identity, SwiperPrevMarginModifier, value);
    return this;
  }
  nextMargin(value) {
    modifierWithKey(this._modifiersWithKeys, SwiperNextMarginModifier.identity, SwiperNextMarginModifier, value);
    return this;
  }
  onAnimationStart(event) {
    throw new Error('Method not implemented.');
  }
  onAnimationEnd(event) {
    throw new Error('Method not implemented.');
  }
  onGestureSwipe(event) {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class SwiperNextMarginModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperNextMargin(node);
    }
    else {
      getUINativeModule().swiper.setSwiperNextMargin(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperNextMarginModifier.identity = Symbol('swiperNextMargin');
class SwiperPrevMarginModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperPrevMargin(node);
    }
    else {
      getUINativeModule().swiper.setSwiperPrevMargin(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperPrevMarginModifier.identity = Symbol('swiperPrevMargin');
class SwiperDisplayCountModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayCount(node);
    }
    else {
      if (isNull(this.value) || isUndefined(this.value)) {
        getUINativeModule().swiper.resetSwiperDisplayCount(node);
      }
      else if (typeof this.value === 'object') {
        let minSize = this.value.minSize.toString();
        getUINativeModule().swiper.setSwiperDisplayCount(node, minSize, typeof this.value);
      }
      else {
        getUINativeModule().swiper.setSwiperDisplayCount(node, this.value, typeof this.value);
      }
    }
  }
  checkObjectDiff() {
    if (typeof this.stageValue !== typeof this.value) {
      return true;
    }
    else if (typeof this.stageValue === 'object' && typeof this.stageValue === 'object') {
      return this.stageValue.minSize !== this.value.minSize;
    }
    else {
      return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
  }
}
SwiperDisplayCountModifier.identity = Symbol('swiperDisplayCount');
class SwiperDisplayArrowModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayArrow(node);
    }
    else {
      if (!isNull(this.value.value) && !isUndefined(this.value.value) && typeof this.value === 'object') {
        let displayArrowValue = 3;
        let showBackground;
        let isSidebarMiddle;
        let backgroundSize;
        let backgroundColor;
        let arrowSize;
        let arrowColor;
        if (typeof this.value.value === 'boolean') {
          if (this.value.value) {
            displayArrowValue = 1;
          }
          else {
            displayArrowValue = 0;
          }
        }
        else if (typeof this.value.value === 'object') {
          displayArrowValue = 2;
          showBackground = this.value.value.showBackground;
          isSidebarMiddle = this.value.value.isSidebarMiddle;
          backgroundSize = this.value.value.backgroundSize;
          backgroundColor = this.value.value.backgroundColor;
          arrowSize = this.value.value.arrowSize;
          arrowColor = this.value.value.arrowColor;
        }
        let isHoverShow;
        if (typeof this.value.isHoverShow === 'boolean') {
          isHoverShow = this.value.isHoverShow;
        }
        getUINativeModule().swiper.setSwiperDisplayArrow(node, displayArrowValue, showBackground,
          isSidebarMiddle, backgroundSize, backgroundColor, arrowSize, arrowColor, isHoverShow);
      }
      else {
        getUINativeModule().swiper.resetSwiperDisplayArrow(node);
      }
    }
  }
  checkObjectDiff() {
    if (this.stageValue.isHoverShow !== this.value.isHoverShow ||
      typeof this.stageValue.value !== typeof this.value.value) {
      return true;
    }
    if (typeof this.stageValue.value === 'boolean' &&
      typeof this.value.value === 'boolean' &&
      this.stageValue.value !== this.value.value) {
      return true;
    }
    else if (typeof this.stageValue.value === 'object' && typeof this.value.value === 'object') {
      return (!isBaseOrResourceEqual(this.stageValue.value.showBackground, this.value.value.showBackground) ||
        !isBaseOrResourceEqual(this.stageValue.value.isSidebarMiddle, this.value.value.isSidebarMiddle) ||
        !isBaseOrResourceEqual(this.stageValue.value.backgroundSize, this.value.value.backgroundSize) ||
        !isBaseOrResourceEqual(this.stageValue.value.backgroundColor, this.value.value.backgroundColor) ||
        !isBaseOrResourceEqual(this.stageValue.value.arrowSize, this.value.value.arrowSize) ||
        !isBaseOrResourceEqual(this.stageValue.value.arrowColor, this.value.value.arrowColor));
    }
    else {
      return true;
    }
  }
}
SwiperDisplayArrowModifier.identity = Symbol('swiperDisplayArrow');
class SwiperIndicatorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperIndicator(node);
    }
    else {
      let left;
      let top;
      let right;
      let bottom;
      let itemWidth;
      let itemHeight;
      let selectedItemWidth;
      let selectedItemHeight;
      let mask;
      let color;
      let selectedColor;
      let fontColor;
      let selectedFontColor;
      let digitFontSize;
      let digitFontWeight;
      let selectedDigitFontSize;
      let selectedDigitFontWeight;
      if (typeof this.value === 'boolean') {
        getUINativeModule().swiper.setSwiperIndicator(node, 'boolean', this.value);
      }
      else if (typeof this.value === 'object' && this.value.type === 'DotIndicator') {
        left = this.value.leftValue;
        top = this.value.topValue;
        right = this.value.rightValue;
        bottom = this.value.bottomValue;
        itemWidth = this.value.itemWidthValue;
        itemHeight = this.value.itemHeightValue;
        selectedItemWidth = this.value.selectedItemWidthValue;
        selectedItemHeight = this.value.selectedItemHeightValue;
        mask = this.value.maskValue;
        color = this.value.colorValue;
        selectedColor = this.value.selectedColorValue;
        getUINativeModule().swiper.setSwiperIndicator(node, 'ArkDotIndicator', itemWidth, itemHeight, selectedItemWidth,
          selectedItemHeight, mask, color, selectedColor, left, top, right, bottom);
      }
      else if (typeof this.value === 'object' && this.value.type === 'DigitIndicator') {
        left = this.value.leftValue;
        top = this.value.topValue;
        right = this.value.rightValue;
        bottom = this.value.bottomValue;
        fontColor = this.value.fontColorValue;
        selectedFontColor = this.value.selectedFontColorValue;
        let arkDigitFont = new ArkDigitFont();
        if (typeof this.value.digitFontValue === 'object') {
          digitFontSize = this.value.digitFontValue.size;
          digitFontWeight = arkDigitFont.parseFontWeight(this.value.digitFontValue.weight);
        }
        if (typeof this.value.selectedDigitFontValue === 'object') {
          selectedDigitFontSize = this.value.selectedDigitFontValue.size;
          selectedDigitFontWeight = arkDigitFont.parseFontWeight(this.value.selectedDigitFontValue.weight);
        }
        getUINativeModule().swiper.setSwiperIndicator(node, 'ArkDigitIndicator', fontColor, selectedFontColor, digitFontSize,
          digitFontWeight, selectedDigitFontSize, selectedDigitFontWeight, left, top, right, bottom);
      }
      else {
        getUINativeModule().swiper.setSwiperIndicator(node, 'boolean', true);
      }
    }
  }
  checkObjectDiff() {
    if (typeof this.stageValue !== typeof this.value) {
      return true;
    }
    if (typeof this.stageValue === 'boolean' && typeof this.value === 'boolean') {
      return this.stageValue !== this.value;
    }
    if (this.stageValue instanceof ArkDotIndicator && this.value instanceof ArkDotIndicator) {
      return (!isBaseOrResourceEqual(this.stageValue.itemWidthValue, this.value.itemWidthValue) ||
        !isBaseOrResourceEqual(this.stageValue.itemHeightValue, this.value.itemHeightValue) ||
        !isBaseOrResourceEqual(this.stageValue.selectedItemWidthValue, this.value.selectedItemWidthValue) ||
        !isBaseOrResourceEqual(this.stageValue.selectedItemHeightValue, this.value.selectedItemHeightValue) ||
        !isBaseOrResourceEqual(this.stageValue.maskValue, this.value.maskValue) ||
        !isBaseOrResourceEqual(this.stageValue.colorValue, this.value.colorValue) ||
        !isBaseOrResourceEqual(this.stageValue.selectedColorValue, this.value.selectedColorValue));
    }
    else if (this.stageValue instanceof ArkDigitIndicator && this.value instanceof ArkDigitIndicator) {
      return (!isBaseOrResourceEqual(this.stageValue.fontColorValue, this.value.fontColorValue) ||
        !isBaseOrResourceEqual(this.stageValue.selectedFontColorValue, this.value.selectedFontColorValue) ||
        !isBaseOrResourceEqual(this.stageValue.digitFontValue.size, this.value.digitFontValue.size) ||
        !isBaseOrResourceEqual(this.stageValue.digitFontValue.weight, this.value.digitFontValue.weight) ||
        !isBaseOrResourceEqual(this.stageValue.selectedDigitFontValue.size, this.value.selectedDigitFontValue.size) ||
        !isBaseOrResourceEqual(this.stageValue.selectedDigitFontValue.weight, this.value.selectedDigitFontValue.weight));
    }
    else {
      return true;
    }
  }
}
SwiperIndicatorModifier.identity = Symbol('swiperIndicator');
class SwiperCurveModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperCurve(node);
    }
    else {
      const curveMap = {
        [0]: 'linear',
        [1]: 'ease',
        [2]: 'ease-in',
        [3]: 'ease-out',
        [4]: 'ease-in-out',
        [5]: 'fast-out-slow-in',
        [6]: 'linear-out-slow-in',
        [7]: 'fast-out-linear-in',
        [8]: 'extreme-deceleration',
        [9]: 'sharp',
        [10]: 'rhythm',
        [11]: 'smooth',
        [12]: 'friction'
      };
      if (typeof this.value === 'number') {
        if (this.value in curveMap) {
          this.value = curveMap[this.value];
        }
        else {
          this.value = this.value.toString();
        }
      }
      getUINativeModule().swiper.setSwiperCurve(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperCurveModifier.identity = Symbol('swiperCurve');
class SwiperDisableSwipeModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisableSwipe(node);
    }
    else {
      getUINativeModule().swiper.setSwiperDisableSwipe(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperDisableSwipeModifier.identity = Symbol('swiperDisableSwipe');
class SwiperEffectModeModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperEffectMode(node);
    }
    else {
      getUINativeModule().swiper.setSwiperEffectMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperEffectModeModifier.identity = Symbol('swiperEffectMode');
class SwiperCachedCountModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperCachedCount(node);
    }
    else {
      getUINativeModule().swiper.setSwiperCachedCount(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperCachedCountModifier.identity = Symbol('swiperCachedCount');
class SwiperDisplayModeModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDisplayMode(node);
    }
    else {
      getUINativeModule().swiper.setSwiperDisplayMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperDisplayModeModifier.identity = Symbol('swiperDisplayMode');
class SwiperItemSpaceModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperItemSpace(node);
    }
    else {
      getUINativeModule().swiper.setSwiperItemSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperItemSpaceModifier.identity = Symbol('swiperItemSpace');
class SwiperVerticalModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperVertical(node);
    }
    else {
      getUINativeModule().swiper.setSwiperVertical(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperVerticalModifier.identity = Symbol('swiperVertical');
class SwiperLoopModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperLoop(node);
    }
    else {
      getUINativeModule().swiper.setSwiperLoop(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperLoopModifier.identity = Symbol('swiperLoop');
class SwiperIntervalModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperInterval(node);
    }
    else {
      getUINativeModule().swiper.setSwiperInterval(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperIntervalModifier.identity = Symbol('swiperInterval');
class SwiperAutoPlayModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperAutoPlay(node);
    }
    else {
      getUINativeModule().swiper.setSwiperAutoPlay(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperAutoPlayModifier.identity = Symbol('swiperAutoPlay');
class SwiperIndexModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperIndex(node);
    }
    else {
      getUINativeModule().swiper.setSwiperIndex(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperIndexModifier.identity = Symbol('swiperIndex');
class SwiperDurationModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().swiper.resetSwiperDuration(node);
    }
    else {
      getUINativeModule().swiper.setSwiperDuration(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
SwiperDurationModifier.identity = Symbol('swiperDuration');
// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSwiperComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTabsComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onAnimationStart(handler) {
    throw new Error('Method not implemented.');
  }
  onAnimationEnd(handler) {
    throw new Error('Method not implemented.');
  }
  onGestureSwipe(handler) {
    throw new Error('Method not implemented.');
  }
  vertical(value) {
    modifierWithKey(this._modifiersWithKeys, TabsVerticalModifier.identity, TabsVerticalModifier, value);
    return this;
  }
  barPosition(value) {
    modifierWithKey(this._modifiersWithKeys, BarPositionModifier.identity, BarPositionModifier, value);
    return this;
  }
  scrollable(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollableModifier.identity, ScrollableModifier, value);
    return this;
  }
  barMode(value, options) {
    let arkBarMode = new ArkBarMode();
    arkBarMode.barMode = value;
    arkBarMode.options = options;
    modifierWithKey(this._modifiersWithKeys, TabBarModeModifier.identity, TabBarModeModifier, arkBarMode);
    return this;
  }
  barWidth(value) {
    modifierWithKey(this._modifiersWithKeys, BarWidthModifier.identity, BarWidthModifier, value);
    return this;
  }
  barHeight(value) {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BarHeightModifier.identity, BarHeightModifier, value);
    }
    return this;
  }
  animationDuration(value) {
    modifierWithKey(this._modifiersWithKeys, AnimationDurationModifier.identity, AnimationDurationModifier, value);
    return this;
  }
  onChange(event) {
    throw new Error('Method not implemented.');
  }
  onTabBarClick(event) {
    throw new Error('Method not implemented.');
  }
  fadingEdge(value) {
    modifierWithKey(this._modifiersWithKeys, FadingEdgeModifier.identity, FadingEdgeModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, DividerModifier.identity, DividerModifier, value);
    return this;
  }
  barOverlap(value) {
    modifierWithKey(this._modifiersWithKeys, BarOverlapModifier.identity, BarOverlapModifier, value);
    return this;
  }
  barBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, BarBackgroundColorModifier.identity, BarBackgroundColorModifier, value);
    return this;
  }
  barGridAlign(value) {
    modifierWithKey(this._modifiersWithKeys, BarGridAlignModifier.identity, BarGridAlignModifier, value);
    return this;
  }
}
class BarGridAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetBarGridAlign(node);
    }
    else {
      getUINativeModule().tabs.setBarGridAlign(node, this.value.sm, this.value.md, this.value.lg, this.value.gutter, this.value.margin);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.sm === this.value.sm &&
      this.stageValue.md === this.value.md &&
      this.stageValue.lg === this.value.lg &&
      this.stageValue.gutter === this.value.gutter &&
      this.stageValue.margin === this.value.margin);
  }
}
BarGridAlignModifier.identity = Symbol('barGridAlign');
class DividerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetDivider(node);
    }
    else {
      getUINativeModule().tabs.setDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.strokeWidth === this.value.strokeWidth &&
      this.stageValue.color === this.value.color &&
      this.stageValue.startMargin === this.value.startMargin &&
      this.stageValue.endMargin === this.value.endMargin);
  }
}
DividerModifier.identity = Symbol('Divider');
class BarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetTabBarWidth(node);
    }
    else {
      getUINativeModule().tabs.setTabBarWidth(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BarWidthModifier.identity = Symbol('barWidth');
class BarAdaptiveHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetBarAdaptiveHeight(node);
    }
    else {
      getUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
    }
  }
}
BarAdaptiveHeightModifier.identity = Symbol('barAdaptiveHeight');
class BarHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetTabBarHeight(node);
    }
    else {
      getUINativeModule().tabs.setTabBarHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BarHeightModifier.identity = Symbol('barHeight');
class BarOverlapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetBarOverlap(node);
    }
    else {
      getUINativeModule().tabs.setBarOverlap(node, this.value);
    }
  }
}
BarOverlapModifier.identity = Symbol('barOverlap');
class TabsVerticalModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetIsVertical(node);
    }
    else {
      getUINativeModule().tabs.setIsVertical(node, this.value);
    }
  }
}
TabsVerticalModifier.identity = Symbol('vertical');
class AnimationDurationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetAnimationDuration(node);
    }
    else {
      getUINativeModule().tabs.setAnimationDuration(node, this.value);
    }
  }
}
AnimationDurationModifier.identity = Symbol('animationduration');
class ScrollableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetScrollable(node);
    }
    else {
      getUINativeModule().tabs.setScrollable(node, this.value);
    }
  }
}
ScrollableModifier.identity = Symbol('scrollable');
class TabBarModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().tabs.resetTabBarMode(node);
    }
    else {
      getUINativeModule().tabs.setTabBarMode(node, this.value.barMode,
        (_a = this.value.options) === null || _a === void 0 ? void 0 : _a.margin,
        (_b = this.value.options) === null || _b === void 0 ? void 0 : _b.nonScrollableLayoutStyle);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d;
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.value.barMode === this.stageValue.barMode &&
        ((_a = this.value.options) === null || _a === void 0 ? void 0 : _a.margin) === ((_b = this.stageValue.options) === null ||
        _b === void 0 ? void 0 : _b.margin) &&
        ((_c = this.value.options) === null || _c === void 0 ? void 0 : _c.nonScrollableLayoutStyle) === ((_d = this.stageValue.options) === null ||
        _d === void 0 ? void 0 : _d.nonScrollableLayoutStyle));
    }
    else {
      return true;
    }
  }
}
TabBarModeModifier.identity = Symbol('tabsbarMode');
class BarPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetTabBarPosition(node);
    }
    else {
      getUINativeModule().tabs.setTabBarPosition(node, this.value);
    }
  }
}
BarPositionModifier.identity = Symbol('barPosition');
class TabsHideTitleBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetHideTitleBar(node);
    }
    else {
      getUINativeModule().tabs.setHideTitleBar(node, this.value);
    }
  }
}
TabsHideTitleBarModifier.identity = Symbol('hideTitleBar');
class BarBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetBarBackgroundColor(node);
    }
    else {
      getUINativeModule().tabs.setBarBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
BarBackgroundColorModifier.identity = Symbol('barbackgroundcolor');
class FadingEdgeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().tabs.resetFadingEdge(node);
    }
    else {
      getUINativeModule().tabs.setFadingEdge(node, this.value);
    }
  }
}
FadingEdgeModifier.identity = Symbol('fadingedge');
// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTabsComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkTabContentComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  tabBar(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.TabContent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkTabContentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkUIExtensionComponentComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onRemoteReady(callback) {
    throw new Error('Method not implemented.');
  }
  onReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onResult(callback) {
    throw new Error('Method not implemented.');
  }
  onRelease(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.UIExtensionComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = globalThis.getArkUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkUIExtensionComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ItemConstraintSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetItemConstraintSize(node);
    }
    else {
      getUINativeModule().waterFlow.setItemConstraintSize(node, this.value.minWidth, this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.minWidth, this.value.minWidth) ||
      !isBaseOrResourceEqual(this.stageValue.maxWidth, this.value.maxWidth) ||
      !isBaseOrResourceEqual(this.stageValue.minHeight, this.value.minHeight) ||
      !isBaseOrResourceEqual(this.stageValue.maxHeight, this.value.maxHeight);
  }
}
ItemConstraintSizeModifier.identity = Symbol('itemConstraintSize');
class ColumnsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetColumnsTemplate(node);
    }
    else {
      getUINativeModule().waterFlow.setColumnsTemplate(node, this.value);
    }
  }
}
ColumnsTemplateModifier.identity = Symbol('columnsTemplate');
class RowsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetRowsTemplate(node);
    }
    else {
      getUINativeModule().waterFlow.setRowsTemplate(node, this.value);
    }
  }
}
RowsTemplateModifier.identity = Symbol('rowsTemplate');
class EnableScrollInteractionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetEnableScrollInteraction(node);
    }
    else {
      getUINativeModule().waterFlow.setEnableScrollInteraction(node, this.value);
    }
  }
}
EnableScrollInteractionModifier.identity = Symbol('enableScrollInteraction');
class RowsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetRowsGap(node);
    }
    else {
      getUINativeModule().waterFlow.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
RowsGapModifier.identity = Symbol('rowsGap');
class ColumnsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetColumnsGap(node);
    }
    else {
      getUINativeModule().waterFlow.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ColumnsGapModifier.identity = Symbol('columnsGap');
class LayoutDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetLayoutDirection(node);
    }
    else {
      getUINativeModule().waterFlow.setLayoutDirection(node, this.value);
    }
  }
}
LayoutDirectionModifier.identity = Symbol('layoutDirection');
class NestedScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetNestedScroll(node);
    }
    else {
      getUINativeModule().waterFlow.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
    }
  }
}
NestedScrollModifier.identity = Symbol('nestedScroll');
class FrictionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetFriction(node);
    }
    else {
      getUINativeModule().waterFlow.setFriction(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FrictionModifier.identity = Symbol('friction');
class ArkWaterFlowComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  columnsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnsTemplateModifier.identity, ColumnsTemplateModifier, value);
    return this;
  }
  rowsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, RowsTemplateModifier.identity, RowsTemplateModifier, value);
    return this;
  }
  itemConstraintSize(value) {
    if (!value) {
      modifierWithKey(this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, undefined);
      return this;
    }
    let arkValue = new ArkConstraintSizeOptions();
    arkValue.minWidth = value.minWidth;
    arkValue.maxWidth = value.maxWidth;
    arkValue.minHeight = value.minHeight;
    arkValue.maxHeight = value.maxHeight;
    modifierWithKey(this._modifiersWithKeys, ItemConstraintSizeModifier.identity, ItemConstraintSizeModifier, arkValue);
    return this;
  }
  columnsGap(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnsGapModifier.identity, ColumnsGapModifier, value);
    return this;
  }
  rowsGap(value) {
    modifierWithKey(this._modifiersWithKeys, RowsGapModifier.identity, RowsGapModifier, value);
    return this;
  }
  layoutDirection(value) {
    modifierWithKey(this._modifiersWithKeys, LayoutDirectionModifier.identity, LayoutDirectionModifier, value);
    return this;
  }
  nestedScroll(value) {
    let options = new ArkNestedScrollOptions();
    if (value) {
      if (value.scrollForward) {
        options.scrollForward = value.scrollForward;
      }
      if (value.scrollBackward) {
        options.scrollBackward = value.scrollBackward;
      }
      modifierWithKey(this._modifiersWithKeys, NestedScrollModifier.identity, NestedScrollModifier, options);
    }
    return this;
  }
  enableScrollInteraction(value) {
    modifierWithKey(this._modifiersWithKeys, EnableScrollInteractionModifier.identity, EnableScrollInteractionModifier, value);
    return this;
  }
  friction(value) {
    modifierWithKey(this._modifiersWithKeys, FrictionModifier.identity, FrictionModifier, value);
    return this;
  }
  cachedCount(value) {
    throw new Error('Method not implemented.');
  }
  onReachStart(event) {
    throw new Error('Method not implemented.');
  }
  onReachEnd(event) {
    throw new Error('Method not implemented.');
  }
  onScrollFrameBegin(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.WaterFlow.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWaterFlowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkCommonShapeComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  viewPort(value) {
    throw new Error('Method not implemented.');
  }
  stroke(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeModifier.identity, StrokeModifier, value);
    return this;
  }
  fill(value) {
    modifierWithKey(this._modifiersWithKeys, FillModifier.identity, FillModifier, value);
    return this;
  }
  strokeDashOffset(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeDashOffsetModifier.identity, StrokeDashOffsetModifier, value);
    return this;
  }
  strokeLineCap(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeLineCapModifier.identity, StrokeLineCapModifier, value);
    return this;
  }
  strokeLineJoin(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeLineJoinModifier.identity, StrokeLineJoinModifier, value);
    return this;
  }
  strokeMiterLimit(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeMiterLimitModifier.identity, StrokeMiterLimitModifier, value);
    return this;
  }
  strokeOpacity(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeOpacityModifier.identity, StrokeOpacityModifier, value);
    return this;
  }
  fillOpacity(value) {
    modifierWithKey(this._modifiersWithKeys, FillOpacityModifier.identity, FillOpacityModifier, value);
    return this;
  }
  strokeWidth(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeWidthModifier.identity, StrokeWidthModifier, value);
    return this;
  }
  antiAlias(value) {
    modifierWithKey(this._modifiersWithKeys, AntiAliasModifier.identity, AntiAliasModifier, value);
    return this;
  }
  strokeDashArray(value) {
    modifierWithKey(this._modifiersWithKeys, StrokeDashArrayModifier.identity, StrokeDashArrayModifier, value);
    return this;
  }
  mesh(value, column, row) {
    throw new Error('Method not implemented.');
  }
}
class StrokeDashArrayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeDashArray(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeDashArray(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StrokeDashArrayModifier.identity = Symbol('strokeDashArray');
class StrokeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStroke(node);
    }
    else {
      getUINativeModule().commonShape.setStroke(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StrokeModifier.identity = Symbol('stroke');
class FillModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetFill(node);
    }
    else {
      getUINativeModule().commonShape.setFill(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FillModifier.identity = Symbol('fill');
class StrokeDashOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeDashOffset(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeDashOffset(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StrokeDashOffsetModifier.identity = Symbol('strokeDashOffset');
class StrokeLineCapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeLineCap(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeLineCap(node, this.value);
    }
  }
}
StrokeLineCapModifier.identity = Symbol('strokeLineCap');
class StrokeLineJoinModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeLineJoin(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeLineJoin(node, this.value);
    }
  }
}
StrokeLineJoinModifier.identity = Symbol('strokeLineJoin');
class StrokeMiterLimitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeMiterLimit(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeMiterLimit(node, this.value);
    }
  }
}
StrokeMiterLimitModifier.identity = Symbol('strokeMiterLimit');
class FillOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetFillOpacity(node);
    }
    else {
      getUINativeModule().commonShape.setFillOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
FillOpacityModifier.identity = Symbol('FillOpacity');
class StrokeOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeOpacity(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
StrokeOpacityModifier.identity = Symbol('StrokeOpacity');
class StrokeWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetStrokeWidth(node);
    }
    else {
      getUINativeModule().commonShape.setStrokeWidth(node, this.value);
    }
  }
}
StrokeWidthModifier.identity = Symbol('strokeWidth');
class AntiAliasModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().commonShape.resetAntiAlias(node);
    }
    else {
      getUINativeModule().commonShape.setAntiAlias(node, this.value);
    }
  }
}
AntiAliasModifier.identity = Symbol('antiAlias');

/// <reference path='./import.ts' />
class ArkCircleComponent extends ArkCommonShapeComponent {
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Circle.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCircleComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkEllipseComponent extends ArkCommonShapeComponent {
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Ellipse.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkEllipseComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
class ArkLineComponent extends ArkCommonShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  startPoint(value) {
    modifierWithKey(this._modifiersWithKeys, LineStartPointModifier.identity, LineStartPointModifier, value);
    return this;
  }
  endPoint(value) {
    modifierWithKey(this._modifiersWithKeys, LineEndPointModifier.identity, LineEndPointModifier, value);
    return this;
  }
}
class LineStartPointModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().line.resetStartPoint(node);
    }
    else {
      getUINativeModule().line.setStartPoint(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
LineStartPointModifier.identity = Symbol('startPoint');
class LineEndPointModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().line.resetEndPoint(node);
    }
    else {
      getUINativeModule().line.setEndPoint(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
LineEndPointModifier.identity = Symbol('endPoint');
// @ts-ignore
globalThis.Line.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkLineComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
const ARRAY_LENGTH = 2;
class ArkPolylineComponent extends ArkCommonShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  points(value) {
    modifierWithKey(this._modifiersWithKeys, PolylinePointsModifier.identity, PolylinePointsModifier, value);
    return this;
  }
}
class PolylinePointsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let xPoint = [];
    let yPoint = [];
    if (Array.isArray(this.value)) {
      for (let i = 0; i <= this.value.length; i++) {
        let item = this.value[i];
        if (!Array.isArray(item)) {
          continue;
        }
        if (item.length < ARRAY_LENGTH || isUndefined(item[0]) || isUndefined(item[1])) {
          reset = true;
          break;
        }
        xPoint.push(item[0]);
        yPoint.push(item[1]);
      }
    }
    else {
      reset = true;
    }
    if (reset) {
      getUINativeModule().polyline.resetPoints(node);
    }
    else {
      getUINativeModule().polyline.setPoints(node, xPoint, yPoint);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PolylinePointsModifier.identity = Symbol('points');
// @ts-ignore
globalThis.Polyline.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPolylineComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkPolygonComponent extends ArkCommonShapeComponent {
  points(value) {
    modifierWithKey(this._modifiersWithKeys, PolygonPointsModifier.identity, PolygonPointsModifier, value);
    return this;
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class PolygonPointsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let xPoint = [];
    let yPoint = [];
    if (Array.isArray(this.value)) {
      for (let i = 0; i <= this.value.length; i++) {
        let item = this.value[i];
        if (!Array.isArray(item)) {
          continue;
        }
        if (item.length < ARRAY_LENGTH || isUndefined(item[0]) || isUndefined(item[1])) {
          reset = true;
          break;
        }
        xPoint.push(item[0]);
        yPoint.push(item[1]);
      }
    }
    else {
      reset = true;
    }
    if (reset) {
      getUINativeModule().polygon.resetPolygonPoints(node);
    }
    else {
      getUINativeModule().polygon.setPolygonPoints(node, xPoint, yPoint);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
PolygonPointsModifier.identity = Symbol('polygonPoints');
// @ts-ignore
globalThis.Polygon.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPolygonComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkPathComponent extends ArkCommonShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  commands(value) {
    modifierWithKey(this._modifiersWithKeys, CommandsModifier.identity, CommandsModifier, value);
    return this;
  }
}
class CommandsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().path.resetPathCommands(node);
    }
    else {
      getUINativeModule().path.setPathCommands(node, this.value);
    }
  }
  checkObjectDiff() {
    if (isString(this.stageValue) && isString(this.value)) {
      return this.stageValue !== this.value;
    }
    else {
      return true;
    }
  }
}
CommandsModifier.identity = Symbol('commands');
// @ts-ignore
globalThis.Path.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPathComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
/// <reference path="./ArkCommonShape.ts" />
class RectRadiusWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rect.resetRectRadiusWidth(node);
    }
    else {
      getUINativeModule().rect.setRectRadiusWidth(node, this.value);
    }
  }
}
RectRadiusWidthModifier.identity = Symbol('rectRadiusWidth');
class RectRadiusHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rect.resetRectRadiusHeight(node);
    }
    else {
      getUINativeModule().rect.setRectRadiusHeight(node, this.value);
    }
  }
}
RectRadiusHeightModifier.identity = Symbol('rectRadiusHeight');
class RectRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rect.resetRectRadius(node);
    }
    else {
      getUINativeModule().rect.setRectRadius(node, this.value);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue === this.value);
  }
}
RectRadiusModifier.identity = Symbol('rectRadius');
class ArkRectComponent extends ArkCommonShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  radiusWidth(value) {
    modifierWithKey(this._modifiersWithKeys, RectRadiusWidthModifier.identity, RectRadiusWidthModifier, value);
    return this;
  }
  radiusHeight(value) {
    modifierWithKey(this._modifiersWithKeys, RectRadiusHeightModifier.identity, RectRadiusHeightModifier, value);
    return this;
  }
  radius(value) {
    modifierWithKey(this._modifiersWithKeys, RectRadiusModifier.identity, RectRadiusModifier, value);
    return this;
  }
}
// @ts-ignore
globalThis.Rect.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRectComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
/// <reference path="./ArkCommonShape.ts" />
class ShapeViewPortModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().shape.resetShapeViewPort(node);
    }
    else {
      getUINativeModule().shape.setShapeViewPort(node, this.value.x, this.value.y, this.value.width, this.value.height);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.x === this.value.x && this.stageValue.y === this.value.y &&
      this.stageValue.width === this.value.width && this.stageValue.height === this.value.height);
  }
}
ShapeViewPortModifier.identity = Symbol('shapeViewPort');
class ShapeMeshModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().shape.resetShapeMesh(node);
    }
    else {
      getUINativeModule().shape.setShapeMesh(node, this.value.value, this.value.column, this.value.row);
    }
  }
  checkObjectDiff() {
    return !this.stageValue.isEqual(this.value);
  }
}
ShapeMeshModifier.identity = Symbol('shapeMesh');
class ArkShapeComponent extends ArkCommonShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  viewPort(value) {
    if (value === null) {
      value = undefined;
    }
    modifierWithKey(this._modifiersWithKeys, ShapeViewPortModifier.identity, ShapeViewPortModifier, value);
    return this;
  }
  mesh(value, column, row) {
    let arkMesh = new ArkMesh();
    if (value !== null && column !== null && row !== null) {
      arkMesh.value = value;
      arkMesh.column = column;
      arkMesh.row = row;
    }
    modifierWithKey(this._modifiersWithKeys, ShapeMeshModifier.identity, ShapeMeshModifier, arkMesh);
    return this;
  }
}
// @ts-ignore
globalThis.Shape.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkShapeComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkCanvasComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onReady(event) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Canvas.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCanvasComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkGridContainerComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  alignItems(value) {
    throw new Error('Method not implemented.');
  }
  justifyContent(value) {
    throw new Error('Method not implemented.');
  }
  pointLight(value) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.GridContainer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridContainerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

/// <reference path='./import.ts' />
class ArkEffectComponentComponent extends ArkComponent {
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
if (globalThis.EffectComponent !== undefined) {
  // @ts-ignore
  globalThis.EffectComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return new ArkEffectComponentComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
  };
}

/// <reference path='./import.ts' />
class ArkRemoteWindowComponent extends ArkComponent {
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
if (globalThis.RemoteWindow !== undefined) {
  // @ts-ignore
  globalThis.RemoteWindow.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return new ArkRemoteWindowComponent(nativeNode);
    });
    modifier.applyNormalAttribute(component);
    component.applyModifierPatch();
  };
}

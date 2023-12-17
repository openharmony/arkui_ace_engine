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
function GetUINativeModule() {
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
  GetUINativeModule().setSupportedUIState(nativeNode, state);
  const currentUIState = GetUINativeModule().getUIState(nativeNode);
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
  let _a;
  return ((_a = variable) === null || _a === void 0 ? void 0 : _a.bundleName) !== undefined;
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
      GetUINativeModule().common.resetBackgroundColor(node);
    }
    else {
      GetUINativeModule().common.setBackgroundColor(node, this.value);
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
BackgroundColorModifier.identity = Symbol('backgroundColor');
class WidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetWidth(node);
    }
    else {
      GetUINativeModule().common.setWidth(node, this.value);
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
WidthModifier.identity = Symbol('width');
class BorderWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBorderWidth(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().common.setBorderWidth(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().common.setBorderWidth(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
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
      GetUINativeModule().common.resetHeight(node);
    }
    else {
      GetUINativeModule().common.setHeight(node, this.value);
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
HeightModifier.identity = Symbol('height');
class BorderRadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().common.setBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().common.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
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
      GetUINativeModule().common.resetPosition(node);
    }
    else {
      GetUINativeModule().common.setPosition(node, this.value.x, this.value.y);
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
      GetUINativeModule().common.resetBorderColor(node);
    }
    else {
      const valueType = typeof this.value;
      if (valueType === 'number' || valueType === 'string' || isResource(this.value)) {
        GetUINativeModule().common.setBorderColor(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().common.setBorderColor(node, this.value.left, this.value.right, this.value.top, this.value.bottom);
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
class TransformModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetTransform(node);
    }
    else {
      GetUINativeModule().common.setTransform(node, this.value.matrix);
    }
  }
}
TransformModifier.identity = Symbol('transform');
class BorderStyleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBorderStyle(node);
    }
    else {
      GetUINativeModule().common.setBorderStyle(node, this.value.type, this.value.style, this.value.top, this.value.right, this.value.bottom, this.value.left);
    }
  }
}
BorderStyleModifier.identity = Symbol('borderStyle');
class ShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetShadow(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().common.setShadow(node, this.value, undefined, undefined, undefined, undefined, undefined, undefined);
      }
      else {
        GetUINativeModule().common.setShadow(node, undefined, this.value.radius, this.value.type, this.value.color, this.value.offsetX, this.value.offsetY, this.value.fill);
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
class HitTestBehaviorModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetHitTestBehavior(node);
    }
    else {
      GetUINativeModule().common.setHitTestBehavior(node, this.value);
    }
  }
}
HitTestBehaviorModifier.identity = Symbol('hitTestBehavior');
class ZIndexModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetZIndex(node);
    }
    else {
      GetUINativeModule().common.setZIndex(node, this.value);
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
      GetUINativeModule().common.resetOpacity(node);
    }
    else {
      GetUINativeModule().common.setOpacity(node, this.value);
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
OpacityModifier.identity = Symbol('opacity');
class AlignModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAlign(node);
    }
    else {
      GetUINativeModule().common.setAlign(node, this.value);
    }
  }
}
AlignModifier.identity = Symbol('align');
class BackdropBlurModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBackdropBlur(node);
    }
    else {
      GetUINativeModule().common.setBackdropBlur(node, this.value);
    }
  }
}
BackdropBlurModifier.identity = Symbol('backdropBlur');
class HueRotateModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetHueRotate(node);
    }
    else {
      GetUINativeModule().common.setHueRotate(node, this.value);
    }
  }
}
HueRotateModifier.identity = Symbol('hueRotate');
class InvertModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetInvert(node);
    }
    else {
      GetUINativeModule().common.setInvert(node, this.value);
    }
  }
}
InvertModifier.identity = Symbol('invert');
class SepiaModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetSepia(node);
    }
    else {
      GetUINativeModule().common.setSepia(node, this.value);
    }
  }
}
SepiaModifier.identity = Symbol('sepia');
class SaturateModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetSaturate(node);
    }
    else {
      GetUINativeModule().common.setSaturate(node, this.value);
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
      GetUINativeModule().common.resetColorBlend(node);
    }
    else {
      GetUINativeModule().common.setColorBlend(node, this.value);
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
ColorBlendModifier.identity = Symbol('colorBlend');
class GrayscaleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetGrayscale(node);
    }
    else {
      GetUINativeModule().common.setGrayscale(node, this.value);
    }
  }
}
GrayscaleModifier.identity = Symbol('grayscale');
class ContrastModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetContrast(node);
    }
    else {
      GetUINativeModule().common.setContrast(node, this.value);
    }
  }
}
ContrastModifier.identity = Symbol('contrast');
class BrightnessModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBrightness(node);
    }
    else {
      GetUINativeModule().common.setBrightness(node, this.value);
    }
  }
}
BrightnessModifier.identity = Symbol('brightness');
class BlurModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBlur(node);
    }
    else {
      GetUINativeModule().common.setBlur(node, this.value);
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
      GetUINativeModule().common.resetLinearGradient(node);
    }
    else {
      GetUINativeModule().common.setLinearGradient(node, this.value.angle, this.value.direction, this.value.colors, this.value.repeating);
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
      GetUINativeModule().common.resetRadialGradient(node);
    }
    else {
      GetUINativeModule().common.setRadialGradient(node, this.value.center, this.value.radius, this.value.colors, this.value.repeating);
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
      GetUINativeModule().common.resetSweepGradient(node);
    }
    else {
      GetUINativeModule().common.setSweepGradient(node, this.value.center, this.value.start, this.value.end, this.value.rotation, this.value.colors, this.value.repeating);
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
      GetUINativeModule().common.resetOverlay(node);
    }
    else {
      GetUINativeModule().common.setOverlay(node, this.value.value, this.value.align, this.value.offsetX, this.value.offsetY, this.value.hasOptions, this.value.hasOffset);
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
      GetUINativeModule().common.resetBorderImage(node);
    }
    else {
      let sliceTop = undefined;
      let sliceRight = undefined;
      let sliceBottom = undefined;
      let sliceLeft = undefined;
      let repeat = undefined;
      let source = undefined;
      let sourceAngle = undefined;
      let sourceDirection = undefined;
      let sourceColors = undefined;
      let sourceRepeating = undefined;
      let widthTop = undefined;
      let widthRight = undefined;
      let widthBottom = undefined;
      let widthLeft = undefined;
      let outsetTop = undefined;
      let outsetRight = undefined;
      let outsetBottom = undefined;
      let outsetLeft = undefined;
      let fill = undefined;
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
      GetUINativeModule().common.setBorderImage(node, sliceTop, sliceRight, sliceBottom, sliceLeft, repeat, source, sourceAngle, sourceDirection, sourceColors, sourceRepeating, widthTop, widthRight, widthBottom, widthLeft, outsetTop, outsetRight, outsetBottom, outsetLeft, fill);
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
      GetUINativeModule().common.resetBorder(node);
    }
    else {
      GetUINativeModule().common.setBorder(node, this.value.arkWidth.left, this.value.arkWidth.right, this.value.arkWidth.top, this.value.arkWidth.bottom, this.value.arkColor.leftColor, this.value.arkColor.rightColor, this.value.arkColor.topColor, this.value.arkColor.bottomColor, this.value.arkRadius.topLeft, this.value.arkRadius.topRight, this.value.arkRadius.bottomLeft, this.value.arkRadius.bottomRight, this.value.arkStyle.top, this.value.arkStyle.right, this.value.arkStyle.bottom, this.value.arkStyle.left);
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
      GetUINativeModule().common.resetForegroundBlurStyle(node);
    }
    else {
      GetUINativeModule().common.setForegroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
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
      GetUINativeModule().common.resetBackgroundImagePosition(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().common.setBackgroundImagePosition(node, this.value, undefined, undefined);
      }
      else {
        GetUINativeModule().common.setBackgroundImagePosition(node, undefined, (_a = this.value) === null || _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
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
class LinearGradientBlurModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetLinearGradientBlur(node);
    }
    else {
      GetUINativeModule().common.setLinearGradientBlur(node, this.value.blurRadius, this.value.fractionStops, this.value.direction);
    }
  }
}
LinearGradientBlurModifier.identity = Symbol('linearGradientBlur');
class BackgroundImageModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetBackgroundImage(node);
    }
    else {
      GetUINativeModule().common.setBackgroundImage(node, this.value.src, this.value.repeat);
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
      GetUINativeModule().common.resetBackgroundBlurStyle(node);
    }
    else {
      GetUINativeModule().common.setBackgroundBlurStyle(node, this.value.blurStyle, this.value.colorMode, this.value.adaptiveColor, this.value.scale);
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
      GetUINativeModule().common.resetBackgroundImageSize(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().common.setBackgroundImageSize(node, this.value, undefined, undefined);
      }
      else {
        GetUINativeModule().common.setBackgroundImageSize(node, undefined, (_a = this.value) === null || _a === void 0 ? void 0 : _a.width, (_b = this.value) === null || _b === void 0 ? void 0 : _b.height);
      }
    }
  }
  checkObjectDiff() {
    return !(this.value.width === this.stageValue.width &&
      this.value.height === this.stageValue.height);
  }
}
BackgroundImageSizeModifier.identity = Symbol('backgroundImageSize');
class TranslateModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetTranslate(node);
    }
    else {
      GetUINativeModule().common.setTranslate(node, this.value.x, this.value.y, this.value.z);
    }
  }
}
TranslateModifier.identity = Symbol('translate');
class ScaleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetScale(node);
    }
    else {
      GetUINativeModule().common.setScale(node, this.value.x, this.value.y, this.value.z, this.value.centerX, this.value.centerY);
    }
  }
}
ScaleModifier.identity = Symbol('scale');
class RotateModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetRotate(node);
    }
    else {
      GetUINativeModule().common.setRotate(node, this.value.x, this.value.y, this.value.z, this.value.angle, this.value.centerX, this.value.centerY, this.value.centerY, this.value.perspective);
    }
  }
}
RotateModifier.identity = Symbol('rotate');
class GeometryTransitionModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetGeometryTransition(node);
    }
    else {
      GetUINativeModule().common.setGeometryTransition(node, this.value);
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
      GetUINativeModule().common.resetClip(node);
    }
    else {
      GetUINativeModule().common.setClip(node, this.value);
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
      GetUINativeModule().common.resetMask(node);
    }
    else {
      GetUINativeModule().common.setMask(node, this.value);
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
      GetUINativeModule().common.resetPixelStretchEffect(node);
    }
    else {
      GetUINativeModule().common.setPixelStretchEffect(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
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
      GetUINativeModule().common.resetLightUpEffect(node);
    }
    else {
      GetUINativeModule().common.setLightUpEffect(node, this.value);
    }
  }
}
LightUpEffectModifier.identity = Symbol('lightUpEffect');
class SphericalEffectModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetSphericalEffect(node);
    }
    else {
      GetUINativeModule().common.setSphericalEffect(node, this.value);
    }
  }
}
SphericalEffectModifier.identity = Symbol('sphericalEffect');
class RenderGroupModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetRenderGroup(node);
    }
    else {
      GetUINativeModule().common.setRenderGroup(node, this.value);
    }
  }
}
RenderGroupModifier.identity = Symbol('renderGroup');
class RenderFitModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetRenderFit(node);
    }
    else {
      GetUINativeModule().common.setRenderFit(node, this.value);
    }
  }
}
RenderFitModifier.identity = Symbol('renderFit');
class UseEffectModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetUseEffect(node);
    }
    else {
      GetUINativeModule().common.setUseEffect(node, this.value);
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
      GetUINativeModule().common.resetForegroundColor(node);
    }
    else {
      GetUINativeModule().common.setForegroundColor(node, this.value);
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
ForegroundColorModifier.identity = Symbol('foregroundColor');
class MotionPathModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetMotionPath(node);
    }
    else {
      GetUINativeModule().common.setMotionPath(node, this.value.path, this.value.from, this.value.to, this.value.rotatable);
    }
  }
}
MotionPathModifier.identity = Symbol('motionPath');
class GroupDefaultFocusModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetGroupDefaultFocus(node);
    }
    else {
      GetUINativeModule().common.setGroupDefaultFocus(node, this.value);
    }
  }
}
GroupDefaultFocusModifier.identity = Symbol('groupDefaultFocus');
class FocusOnTouchModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetFocusOnTouch(node);
    }
    else {
      GetUINativeModule().common.setFocusOnTouch(node, this.value);
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
      GetUINativeModule().common.resetOffset(node);
    }
    else {
      GetUINativeModule().common.setOffset(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
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
      GetUINativeModule().common.resetMarkAnchor(node);
    }
    else {
      GetUINativeModule().common.setMarkAnchor(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.x, (_b = this.value) === null || _b === void 0 ? void 0 : _b.y);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.x, this.value.x) ||
      !isBaseOrResourceEqual(this.stageValue.y, this.value.y);
  }
}
MarkAnchorModifier.identity = Symbol('markAnchor');
class DefaultFocusModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetDefaultFocus(node);
    }
    else {
      GetUINativeModule().common.setDefaultFocus(node, this.value);
    }
  }
}
DefaultFocusModifier.identity = Symbol('defaultFocus');
class FocusableModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetFocusable(node);
    }
    else {
      GetUINativeModule().common.setFocusable(node, this.value);
    }
  }
}
FocusableModifier.identity = Symbol('focusable');
class TouchableModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetTouchable(node);
    }
    else {
      GetUINativeModule().common.setTouchable(node, this.value);
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
      GetUINativeModule().common.resetMargin(node);
    }
    else {
      GetUINativeModule().common.setMargin(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
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
      GetUINativeModule().common.resetPadding(node);
    }
    else {
      GetUINativeModule().common.setPadding(node, this.value.top, this.value.right, this.value.bottom, this.value.left);
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
      GetUINativeModule().common.resetVisibility(node);
    }
    else {
      GetUINativeModule().common.setVisibility(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
VisibilityModifier.identity = Symbol('visibility');
class AccessibilityTextModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAccessibilityText(node);
    }
    else {
      GetUINativeModule().common.setAccessibilityText(node, this.value);
    }
  }
}
AccessibilityTextModifier.identity = Symbol('accessibilityText');
class AllowDropModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAllowDrop(node);
    }
    else {
      GetUINativeModule().common.setAllowDrop(node, this.value.allowDropArray);
    }
  }
}
AllowDropModifier.identity = Symbol('allowDrop');
class AccessibilityLevelModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAccessibilityLevel(node);
    }
    else {
      GetUINativeModule().common.setAccessibilityLevel(node, this.value);
    }
  }
}
AccessibilityLevelModifier.identity = Symbol('accessibilityLevel');
class AccessibilityDescriptionModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAccessibilityDescription(node);
    }
    else {
      GetUINativeModule().common.setAccessibilityDescription(node, this.value);
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
      GetUINativeModule().common.resetDirection(node);
    }
    else {
      GetUINativeModule().common.setDirection(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DirectionModifier.identity = Symbol('direction');
class AlignRulesModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAlignRules(node);
    }
    else {
      GetUINativeModule().common.setAlignRules(node, this.value.left, this.value.middle, this.value.right, this.value.top, this.value.center, this.value.bottom);
    }
  }
}
AlignRulesModifier.identity = Symbol('alignRules');
class ExpandSafeAreaModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetExpandSafeArea(node);
    }
    else {
      GetUINativeModule().common.setExpandSafeArea(node, this.value.type, this.value.edges);
    }
  }
}
ExpandSafeAreaModifier.identity = Symbol('expandSafeArea');
class GridSpanModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetGridSpan(node);
    }
    else {
      GetUINativeModule().common.setGridSpan(node, this.value);
    }
  }
}
GridSpanModifier.identity = Symbol('gridSpan');
class GridOffsetModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetGridOffset(node);
    }
    else {
      GetUINativeModule().common.setGridOffset(node, this.value);
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
      GetUINativeModule().common.resetAlignSelf(node);
    }
    else {
      GetUINativeModule().common.setAlignSelf(node, this.value);
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
      GetUINativeModule().common.resetSize(node);
    }
    else {
      GetUINativeModule().common.setSize(node, this.value.width, this.value.height);
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
      GetUINativeModule().common.resetDisplayPriority(node);
    }
    else {
      GetUINativeModule().common.setDisplayPriority(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
DisplayPriorityModifier.identity = Symbol('displayPriority');
class IDModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetId(node);
    }
    else {
      GetUINativeModule().common.setId(node, this.value);
    }
  }
}
IDModifier.identity = Symbol('id');
class KeyModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetKey(node);
    }
    else {
      GetUINativeModule().common.setKey(node, this.value);
    }
  }
}
KeyModifier.identity = Symbol('key');
class RestoreIdModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetRestoreId(node);
    }
    else {
      GetUINativeModule().common.setRestoreId(node, this.value);
    }
  }
}
RestoreIdModifier.identity = Symbol('restoreId');
class TabIndexModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetTabIndex(node);
    }
    else {
      GetUINativeModule().common.setTabIndex(node, this.value);
    }
  }
}
TabIndexModifier.identity = Symbol('tabIndex');
class ObscuredModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetObscured(node);
    }
    else {
      GetUINativeModule().common.setObscured(node, this.value.reasons);
    }
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
      GetUINativeModule().common.resetMouseResponseRegion(node);
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
      GetUINativeModule().common.setMouseResponseRegion(node, responseRegion, responseRegion.length);
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
      GetUINativeModule().common.resetResponseRegion(node);
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
      GetUINativeModule().common.setResponseRegion(node, responseRegion, responseRegion.length);
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
      GetUINativeModule().common.resetFlexGrow(node);
    }
    else {
      GetUINativeModule().common.setFlexGrow(node, this.value);
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
      GetUINativeModule().common.resetFlexShrink(node);
    }
    else {
      GetUINativeModule().common.setFlexShrink(node, this.value);
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
      GetUINativeModule().common.resetAspectRatio(node);
    }
    else {
      GetUINativeModule().common.setAspectRatio(node, this.value);
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
      GetUINativeModule().common.resetConstraintSize(node);
    }
    else {
      GetUINativeModule().common.setConstraintSize(node, this.value.minWidth, this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
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
      GetUINativeModule().common.resetFlexBasis(node);
    }
    else {
      GetUINativeModule().common.setFlexBasis(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
FlexBasisModifier.identity = Symbol('flexBasis');
class LayoutWeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetLayoutWeight(node);
    }
    else {
      GetUINativeModule().common.setLayoutWeight(node, this.value);
    }
  }
}
LayoutWeightModifier.identity = Symbol('layoutWeight');
class EnabledModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetEnabled(node);
    }
    else {
      GetUINativeModule().common.setEnabled(node, this.value);
    }
  }
}
EnabledModifier.identity = Symbol('enabled');
class DraggableModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetDraggable(node);
    }
    else {
      GetUINativeModule().common.setDraggable(node, this.value);
    }
  }
}
DraggableModifier.identity = Symbol('draggable');
class AccessibilityGroupModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetAccessibilityGroup(node);
    }
    else {
      GetUINativeModule().common.setAccessibilityGroup(node, this.value);
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
      GetUINativeModule().common.resetHoverEffect(node);
    }
    else {
      GetUINativeModule().common.setHoverEffect(node, this.value);
    }
  }
}
HoverEffectModifier.identity = Symbol('hoverEffect');
class ClickEffectModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      GetUINativeModule().common.resetClickEffect(node);
    }
    else {
      GetUINativeModule().common.setClickEffect(node, this.value.level, this.value.scale);
    }
  }
}
ClickEffectModifier.identity = Symbol('clickEffect');
class KeyBoardShortCutModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetKeyBoardShortCut(node);
    }
    else {
      GetUINativeModule().common.setKeyBoardShortCut(node, this.value.value, this.value.keys);
    }
  }
}
KeyBoardShortCutModifier.identity = Symbol('keyboardShortcut');
class TransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().common.resetTransition(node);
    }
    else {
      GetUINativeModule().common.setTransition(node, this.value);
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
      GetUINativeModule().common.resetSharedTransition(node);
    }
    else {
      GetUINativeModule().common.setSharedTransition(node, this.value.id, this.value.options);
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
const lessThenFunction = (val1, val2) => (val1 - val2) < 0.001;
function CheckJSCallbackInfo(value, checklist) {
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
  return typeVerified || checklist.length == 0;
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
      modifier(this._modifiers, ExpandSafeAreaModifier, undefined);
    }
    else {
      modifier(this._modifiers, ExpandSafeAreaModifier, opts);
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
      modifier(this._modifiers, TouchableModifier, value);
    }
    else {
      modifier(this._modifiers, TouchableModifier, undefined);
    }
    return this;
  }
  hitTestBehavior(value) {
    if (value) {
      modifier(this._modifiers, HitTestBehaviorModifier, value);
    }
    else {
      modifier(this._modifiers, HitTestBehaviorModifier, undefined);
    }
    return this;
  }
  layoutWeight(value) {
    if (isNumber(value)) {
      modifier(this._modifiers, LayoutWeightModifier, value);
    }
    else if (isString(value) && !isNaN(Number(value))) {
      modifier(this._modifiers, LayoutWeightModifier, parseInt(value.toString()));
    }
    else {
      modifier(this._modifiers, LayoutWeightModifier, undefined);
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
    let arkBorderStyle = new ArkBorderStyle();
    if (arkBorderStyle.parseBorderStyle(value)) {
      modifier(this._modifiers, BorderStyleModifier, arkBorderStyle);
    }
    else {
      modifier(this._modifiers, BorderStyleModifier, undefined);
    }
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
      modifier(this._modifiers, FocusableModifier, value);
    }
    else {
      modifier(this._modifiers, FocusableModifier, undefined);
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
      modifier(this._modifiers, TabIndexModifier, undefined);
    }
    else {
      modifier(this._modifiers, TabIndexModifier, index);
    }
    return this;
  }
  defaultFocus(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, DefaultFocusModifier, value);
    }
    else {
      modifier(this._modifiers, DefaultFocusModifier, undefined);
    }
    return this;
  }
  groupDefaultFocus(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, GroupDefaultFocusModifier, value);
    }
    else {
      modifier(this._modifiers, GroupDefaultFocusModifier, undefined);
    }
    return this;
  }
  focusOnTouch(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, FocusOnTouchModifier, value);
    }
    else {
      modifier(this._modifiers, FocusOnTouchModifier, undefined);
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
      modifier(this._modifiers, BlurModifier, undefined);
    }
    else {
      modifier(this._modifiers, BlurModifier, value);
    }
    return this;
  }
  linearGradientBlur(value, options) {
    if (isUndefined(value) || isUndefined(options)) {
      modifier(this._modifiers, LinearGradientBlurModifier, undefined);
      return this;
    }
    let arkLinearGradientBlur = new ArkLinearGradientBlur();
    arkLinearGradientBlur.blurRadius = value;
    arkLinearGradientBlur.fractionStops = options.fractionStops;
    arkLinearGradientBlur.direction = options.direction;
    modifier(this._modifiers, LinearGradientBlurModifier, arkLinearGradientBlur);
    return this;
  }
  brightness(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, BrightnessModifier, undefined);
    }
    else {
      modifier(this._modifiers, BrightnessModifier, value);
    }
    return this;
  }
  contrast(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, ContrastModifier, undefined);
    }
    else {
      modifier(this._modifiers, ContrastModifier, value);
    }
    return this;
  }
  grayscale(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, GrayscaleModifier, undefined);
    }
    else {
      modifier(this._modifiers, GrayscaleModifier, value);
    }
    return this;
  }
  colorBlend(value) {
    modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
    return this;
  }
  saturate(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, SaturateModifier, undefined);
    }
    else {
      modifier(this._modifiers, SaturateModifier, value);
    }
    return this;
  }
  sepia(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, SepiaModifier, undefined);
    }
    else {
      modifier(this._modifiers, SepiaModifier, value);
    }
    return this;
  }
  invert(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, InvertModifier, undefined);
    }
    else {
      modifier(this._modifiers, InvertModifier, value);
    }
    return this;
  }
  hueRotate(value) {
    if (!isNumber(value) && !isString(value)) {
      modifier(this._modifiers, HueRotateModifier, undefined);
    }
    else {
      modifier(this._modifiers, HueRotateModifier, value);
    }
    return this;
  }
  useEffect(value) {
    modifier(this._modifiers, UseEffectModifier, value);
    return this;
  }
  backdropBlur(value) {
    if (!isNumber(value)) {
      modifier(this._modifiers, BackdropBlurModifier, undefined);
    }
    else {
      modifier(this._modifiers, BackdropBlurModifier, value);
    }
    return this;
  }
  renderGroup(value) {
    modifier(this._modifiers, RenderGroupModifier, value);
    return this;
  }
  translate(value) {
    let arkTranslate = new ArkTranslate();
    if (isNumber(value === null || value === void 0 ? void 0 : value.x) || isString(value === null || value === void 0 ? void 0 : value.x)) {
      arkTranslate.x = value.x;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.y) || isString(value === null || value === void 0 ? void 0 : value.y)) {
      arkTranslate.y = value.y;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.z) || isString(value === null || value === void 0 ? void 0 : value.z)) {
      arkTranslate.z = value.z;
    }
    modifier(this._modifiers, TranslateModifier, arkTranslate);
    return this;
  }
  scale(value) {
    let arkScale = new ArkScale();
    if (isNumber(value === null || value === void 0 ? void 0 : value.x)) {
      arkScale.x = value === null || value === void 0 ? void 0 : value.x;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.y)) {
      arkScale.y = value === null || value === void 0 ? void 0 : value.y;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.z)) {
      arkScale.z = value === null || value === void 0 ? void 0 : value.z;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.centerX) || isString(value === null || value === void 0 ? void 0 : value.centerX)) {
      arkScale.centerX = value === null || value === void 0 ? void 0 : value.centerX;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.centerY) || isString(value === null || value === void 0 ? void 0 : value.centerY)) {
      arkScale.centerY = value === null || value === void 0 ? void 0 : value.centerY;
    }
    modifier(this._modifiers, ScaleModifier, arkScale);
    return this;
  }
  gridSpan(value) {
    if (isNumber(value)) {
      modifier(this._modifiers, GridSpanModifier, value);
    }
    else {
      modifier(this._modifiers, GridSpanModifier, undefined);
    }
    return this;
  }
  gridOffset(value) {
    if (isNumber(value)) {
      modifier(this._modifiers, GridOffsetModifier, value);
    }
    else {
      modifier(this._modifiers, GridOffsetModifier, undefined);
    }
    return this;
  }
  rotate(value) {
    let arkRotate = new ArkRotate();
    if (isNumber(value === null || value === void 0 ? void 0 : value.x)) {
      arkRotate.x = value === null || value === void 0 ? void 0 : value.x;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.y)) {
      arkRotate.y = value === null || value === void 0 ? void 0 : value.y;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.z)) {
      arkRotate.z = value === null || value === void 0 ? void 0 : value.z;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.angle) || isString(value === null || value === void 0 ? void 0 : value.angle)) {
      arkRotate.angle = value === null || value === void 0 ? void 0 : value.angle;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.centerX) || isString(value === null || value === void 0 ? void 0 : value.centerX)) {
      arkRotate.centerX = value === null || value === void 0 ? void 0 : value.centerX;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.centerY) || isString(value === null || value === void 0 ? void 0 : value.centerY)) {
      arkRotate.centerY = value === null || value === void 0 ? void 0 : value.centerY;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.centerZ) || isString(value === null || value === void 0 ? void 0 : value.centerZ)) {
      arkRotate.centerZ = value === null || value === void 0 ? void 0 : value.centerZ;
    }
    if (isNumber(value === null || value === void 0 ? void 0 : value.perspective)) {
      arkRotate.perspective = value === null || value === void 0 ? void 0 : value.perspective;
    }
    modifier(this._modifiers, RotateModifier, arkRotate);
    return this;
  }
  transform(value) {
    if (isUndefined(value)) {
      modifier(this._modifiers, TransformModifier, undefined);
    }
    else {
      modifier(this._modifiers, TransformModifier, new ArkTransformMatrix(value['matrix4x4']));
    }
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
      modifier(this._modifiers, ZIndexModifier, zIndex);
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
      modifier(this._modifiers, AlignModifier, value);
    }
    else {
      modifier(this._modifiers, AlignModifier, undefined);
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
      modifier(this._modifiers, EnabledModifier, value);
    }
    else {
      modifier(this._modifiers, EnabledModifier, undefined);
    }
    return this;
  }
  useSizeType(value) {
    throw new Error('Method not implemented.');
  }
  alignRules(value) {
    if (!isObject(value) || JSON.stringify(value) === '{}') {
      modifier(this._modifiers, AlignRulesModifier, undefined);
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
    modifier(this._modifiers, AlignRulesModifier, arkValue);
    return this;
  }
  aspectRatio(value) {
    modifierWithKey(this._modifiersWithKeys, AspectRatioModifier.identity, AspectRatioModifier, value);
    return this;
  }
  clickEffect(value) {
    if (value) {
      let arkClickEffect = new ArkClickEffect();
      arkClickEffect.level = value.level;
      arkClickEffect.scale = value.scale;
      modifier(this._modifiers, ClickEffectModifier, arkClickEffect);
    }
    else {
      modifier(this._modifiers, ClickEffectModifier, undefined);
    }
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
    let allowDrop = new ArkAllowDrop();
    allowDrop.allowDropArray = value;
    modifier(this._modifiers, AllowDropModifier, allowDrop);
    return this;
  }
  draggable(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, DraggableModifier, value);
    }
    else {
      modifier(this._modifiers, DraggableModifier, undefined);
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
    let arkMotionPath = new ArkMotionPath();
    arkMotionPath.path = '';
    arkMotionPath.rotatable = false;
    arkMotionPath.from = 0.0;
    arkMotionPath.to = 1.0;
    if (value) {
      if (typeof value.path === 'string') {
        arkMotionPath.path = value.path;
      }
      if (typeof value.rotatable === 'boolean') {
        arkMotionPath.rotatable = value.rotatable;
      }
      if (typeof value.from === 'number' && typeof value.to === 'number') {
        arkMotionPath.from = value.from;
        arkMotionPath.to = value.to;
      }
    }
    modifier(this._modifiers, MotionPathModifier, arkMotionPath);
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
      modifier(this._modifiers, KeyModifier, value);
    }
    else {
      modifier(this._modifiers, KeyModifier, undefined);
    }
    return this;
  }
  id(value) {
    if (typeof value === 'string') {
      modifier(this._modifiers, IDModifier, value);
    }
    else {
      modifier(this._modifiers, IDModifier, undefined);
    }
    return this;
  }
  geometryTransition(id) {
    if (isString(id)) {
      modifier(this._modifiers, GeometryTransitionModifier, id);
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
      modifier(this._modifiers, RestoreIdModifier, undefined);
    }
    else {
      modifier(this._modifiers, RestoreIdModifier, value);
    }
    return this;
  }
  onVisibleAreaChange(ratios, event) {
    throw new Error('Method not implemented.');
  }
  sphericalEffect(value) {
    modifier(this._modifiers, SphericalEffectModifier, value);
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
    modifier(this._modifiers, KeyBoardShortCutModifier, keyboardShortCut);
    return this;
  }
  accessibilityGroup(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, AccessibilityGroupModifier, value);
    }
    else {
      modifier(this._modifiers, AccessibilityGroupModifier, undefined);
    }
    return this;
  }
  accessibilityText(value) {
    if (typeof value === 'string') {
      modifier(this._modifiers, AccessibilityTextModifier, value);
    }
    else {
      modifier(this._modifiers, AccessibilityTextModifier, undefined);
    }
    return this;
  }
  accessibilityDescription(value) {
    if (typeof value !== 'string') {
      modifier(this._modifiers, AccessibilityDescriptionModifier, undefined);
    }
    else {
      modifier(this._modifiers, AccessibilityDescriptionModifier, value);
    }
    return this;
  }
  accessibilityLevel(value) {
    if (typeof value !== 'string') {
      modifier(this._modifiers, AccessibilityLevelModifier, undefined);
    }
    else {
      modifier(this._modifiers, AccessibilityLevelModifier, value);
    }
    return this;
  }
  obscured(reasons) {
    let arkObscured = new ArkObscured();
    if (arkObscured.parseReasonsArray(reasons)) {
      modifier(this._modifiers, ObscuredModifier, arkObscured);
    }
    else {
      modifier(this._modifiers, ObscuredModifier, undefined);
    }
    return this;
  }
  reuseId(id) {
    throw new Error('Method not implemented.');
  }
  renderFit(fitMode) {
    modifier(this._modifiers, RenderFitModifier, fitMode);
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
      GetUINativeModule().blank.resetColor(node);
    }
    else {
      GetUINativeModule().blank.setColor(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().column.resetAlignItems(node);
    }
    else {
      GetUINativeModule().column.setAlignItems(node, this.value);
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
      GetUINativeModule().column.resetJustifyContent(node);
    }
    else {
      GetUINativeModule().column.setJustifyContent(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().columnSplit.resetDivider(node);
    }
    else {
      GetUINativeModule().columnSplit.setDivider(node, this.value.startMargin, this.value.endMargin);
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
      GetUINativeModule().columnSplit.resetResizeable(node);
    }
    else {
      GetUINativeModule().columnSplit.setResizeable(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().divider.resetVertical(node);
    }
    else {
      GetUINativeModule().divider.setVertical(node, this.value);
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
      GetUINativeModule().divider.resetLineCap(node);
    }
    else {
      GetUINativeModule().divider.setLineCap(node, this.value);
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
      GetUINativeModule().divider.resetColor(node);
    }
    else {
      GetUINativeModule().divider.setColor(node, this.value);
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
      GetUINativeModule().divider.resetStrokeWidth(node);
    }
    else {
      GetUINativeModule().divider.setStrokeWidth(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().gridRow.resetAlignItems(node);
    }
    else {
      GetUINativeModule().gridRow.setAlignItems(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().grid.resetColumnsTemplate(node);
    }
    else {
      GetUINativeModule().grid.setColumnsTemplate(node, this.value);
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
      GetUINativeModule().grid.resetRowsTemplate(node);
    }
    else {
      GetUINativeModule().grid.setRowsTemplate(node, this.value);
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
      GetUINativeModule().grid.resetColumnsGap(node);
    }
    else {
      GetUINativeModule().grid.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue === this.value);
    }
    else {
      return true;
    }
  }
}
GridColumnsGapModifier.identity = Symbol('gridColumnsGap');
class GridRowsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().grid.resetRowsGap(node);
    }
    else {
      GetUINativeModule().grid.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue === this.value);
    }
    else {
      return true;
    }
  }
}
GridRowsGapModifier.identity = Symbol('gridRowsGap');
class GridScrollBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().grid.resetScrollBarWidth(node);
    }
    else {
      GetUINativeModule().grid.setScrollBarWidth(node, this.value);
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
      GetUINativeModule().grid.resetScrollBar(node);
    }
    else {
      GetUINativeModule().grid.setScrollBar(node, this.value);
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
      GetUINativeModule().grid.resetScrollBarColor(node);
    }
    else {
      GetUINativeModule().grid.setScrollBarColor(node, this.value);
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
      GetUINativeModule().grid.resetEditMode(node);
    }
    else {
      GetUINativeModule().grid.setEditMode(node, this.value);
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
      GetUINativeModule().grid.resetCachedCount(node);
    }
    else {
      GetUINativeModule().grid.setCachedCount(node, this.value);
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
      GetUINativeModule().grid.resetMultiSelectable(node);
    }
    else {
      GetUINativeModule().grid.setMultiSelectable(node, this.value);
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
      GetUINativeModule().grid.resetEdgeEffect(node);
    }
    else {
      GetUINativeModule().grid.setEdgeEffect(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.value, (_b = this.value.options) === null || _b === void 0 ? void 0 : _b.alwaysEnabled);
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
      GetUINativeModule().grid.resetNestedScroll(node);
    }
    else {
      GetUINativeModule().grid.setNestedScroll(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.scrollForward, (_b = this.value) === null || _b === void 0 ? void 0 : _b.scrollBackward);
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
      GetUINativeModule().grid.resetEnableScroll(node);
    }
    else {
      GetUINativeModule().grid.setEnableScroll(node, this.value);
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
      GetUINativeModule().grid.resetFriction(node);
    }
    else {
      GetUINativeModule().grid.setFriction(node, this.value);
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
      GetUINativeModule().grid.resetMaxCount(node);
    }
    else {
      GetUINativeModule().grid.setMaxCount(node, this.value);
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
      GetUINativeModule().grid.resetMinCount(node);
    }
    else {
      GetUINativeModule().grid.setMinCount(node, this.value);
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
      GetUINativeModule().grid.resetCellLength(node);
    }
    else {
      GetUINativeModule().grid.setCellLength(node, this.value);
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
      GetUINativeModule().grid.resetLayoutDirection(node);
    }
    else {
      GetUINativeModule().grid.setLayoutDirection(node, this.value);
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
      GetUINativeModule().grid.resetSupportAnimation(node);
    }
    else {
      GetUINativeModule().grid.setSupportAnimation(node, this.value);
    }
  }
}
GridSupportAnimationModifier.identity = Symbol('gridSupportAnimation');
// @ts-ignore
globalThis.Grid.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().gridCol.resetSpan(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setSpan(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().gridCol.setSpan(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
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
      GetUINativeModule().gridCol.resetGridColOffset(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setGridColOffset(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().gridCol.setGridColOffset(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
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
      GetUINativeModule().gridCol.resetOrder(node);
    }
    else {
      if (isNumber(this.value)) {
        GetUINativeModule().gridCol.setOrder(node, this.value, this.value, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().gridCol.setOrder(node, this.value.xs, this.value.sm, this.value.md, this.value.lg, this.value.xl, this.value.xxl);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().image.resetColorFilter(node);
    }
    else {
      GetUINativeModule().image.setColorFilter(node, this.value);
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
      GetUINativeModule().image.resetFillColor(node);
    }
    else {
      GetUINativeModule().image.setFillColor(node, this.value);
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
      GetUINativeModule().image.resetAlt(node);
    }
    else {
      GetUINativeModule().image.setAlt(node, this.value);
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
      GetUINativeModule().image.resetCopyOption(node);
    }
    else {
      GetUINativeModule().image.setCopyOption(node, this.value);
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
      GetUINativeModule().image.resetAutoResize(node);
    }
    else {
      GetUINativeModule().image.setAutoResize(node, this.value);
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
      GetUINativeModule().image.resetFitOriginalSize(node);
    }
    else {
      GetUINativeModule().image.setFitOriginalSize(node, this.value);
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
      GetUINativeModule().image.resetDraggable(node);
    }
    else {
      GetUINativeModule().image.setDraggable(node, this.value);
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
      GetUINativeModule().image.resetImageInterpolation(node);
    }
    else {
      GetUINativeModule().image.setImageInterpolation(node, this.value);
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
      GetUINativeModule().image.resetSourceSize(node);
    }
    else {
      GetUINativeModule().image.setSourceSize(node, this.value.width, this.value.height);
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
      GetUINativeModule().image.resetMatchTextDirection(node);
    }
    else {
      GetUINativeModule().image.setMatchTextDirection(node, this.value);
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
      GetUINativeModule().image.resetObjectRepeat(node);
    }
    else {
      GetUINativeModule().image.setObjectRepeat(node, this.value);
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
      GetUINativeModule().image.resetRenderMode(node);
    }
    else {
      GetUINativeModule().image.setRenderMode(node, this.value);
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
      GetUINativeModule().image.resetSyncLoad(node);
    }
    else {
      GetUINativeModule().image.setSyncLoad(node, this.value);
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
      GetUINativeModule().image.resetObjectFit(node);
    }
    else {
      GetUINativeModule().image.setObjectFit(node, this.value);
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
      GetUINativeModule().image.resetBorderRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().image.setBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().image.setBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    } else if (!isResource(this.stageValue) && !isResource(this.value)) {
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().imageAnimator.resetImages(node);
    }
    else {
      let arkImageFrame = this.convertImageFrames(this.value);
      if (!arkImageFrame) {
        GetUINativeModule().imageAnimator.resetImages(node);
      }
      else {
        GetUINativeModule().imageAnimator.setImages(node, arkImageFrame.arrSrc, arkImageFrame.arrWidth, arkImageFrame.arrHeight, arkImageFrame.arrTop, arkImageFrame.arrLeft, arkImageFrame.arrDuration, arkImageFrame.arrSrc.length);
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
      GetUINativeModule().imageAnimator.resetDuration(node);
    }
    else {
      GetUINativeModule().imageAnimator.setDuration(node, this.value);
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
      GetUINativeModule().imageAnimator.resetReverse(node);
    }
    else {
      GetUINativeModule().imageAnimator.setReverse(node, this.value);
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
      GetUINativeModule().imageAnimator.resetState(node);
    }
    else {
      GetUINativeModule().imageAnimator.setState(node, this.value);
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
      GetUINativeModule().imageAnimator.resetFixedSize(node);
    }
    else {
      GetUINativeModule().imageAnimator.setFixedSize(node, this.value);
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
      GetUINativeModule().imageAnimator.resetFillMode(node);
    }
    else {
      GetUINativeModule().imageAnimator.setFillMode(node, this.value);
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
      GetUINativeModule().imageAnimator.resetIterations(node);
    }
    else {
      GetUINativeModule().imageAnimator.setIterations(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().imageSpan.resetObjectFit(node);
    }
    else {
      GetUINativeModule().imageSpan.setObjectFit(node, this.value);
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
      GetUINativeModule().imageSpan.resetVerticalAlign(node);
    }
    else {
      GetUINativeModule().imageSpan.setVerticalAlign(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().patternLock.resetActiveColor(node);
    }
    else {
      GetUINativeModule().patternLock.setActiveColor(node, this.value);
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
      GetUINativeModule().patternLock.resetSelectedColor(node);
    }
    else {
      GetUINativeModule().patternLock.setSelectedColor(node, this.value);
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
      GetUINativeModule().patternLock.resetPathColor(node);
    }
    else {
      GetUINativeModule().patternLock.setPathColor(node, this.value);
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
      GetUINativeModule().patternLock.resetRegularColor(node);
    }
    else {
      GetUINativeModule().patternLock.setRegularColor(node, this.value);
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
      GetUINativeModule().patternLock.resetSideLength(node);
    }
    else {
      GetUINativeModule().patternLock.setSideLength(node, this.value);
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
      GetUINativeModule().patternLock.resetPathStrokeWidth(node);
    }
    else {
      GetUINativeModule().patternLock.setPathStrokeWidth(node, this.value);
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
      GetUINativeModule().patternLock.resetCircleRadius(node);
    }
    else {
      GetUINativeModule().patternLock.setCircleRadius(node, this.value);
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
      GetUINativeModule().patternLock.resetAutoReset(node);
    }
    else {
      GetUINativeModule().patternLock.setAutoReset(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().richEditor.resetCopyOptions(node);
    }
    else {
      GetUINativeModule().richEditor.setCopyOptions(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().row.resetAlignItems(node);
    }
    else {
      GetUINativeModule().row.setAlignItems(node, this.value);
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
      GetUINativeModule().row.resetJustifyContent(node);
    }
    else {
      GetUINativeModule().row.setJustifyContent(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().rowSplit.resetResizeable(node);
    }
    else {
      GetUINativeModule().rowSplit.setResizeable(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().search.resetSelectionMenuHidden(node);
    }
    else {
      GetUINativeModule().search.setSelectionMenuHidden(node, this.value);
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
      GetUINativeModule().search.resetCaretStyle(node);
    }
    else {
      GetUINativeModule().search.setCaretStyle(node, this.value.width, this.value.color);
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
      GetUINativeModule().search.resetEnableKeyboardOnFocus(node);
    }
    else {
      GetUINativeModule().search.setEnableKeyboardOnFocus(node, this.value);
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
      GetUINativeModule().search.resetSearchIcon(node);
    }
    else {
      GetUINativeModule().search.setSearchIcon(node, this.value.size, this.value.color, this.value.src);
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
      GetUINativeModule().search.resetPlaceholderFont(node);
    }
    else {
      GetUINativeModule().search.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().search.resetSearchButton(node);
    }
    else {
      GetUINativeModule().search.setSearchButton(node, this.value.value, this.value.fontSize, this.value.fontColor);
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
      GetUINativeModule().search.resetFontColor(node);
    }
    else {
      GetUINativeModule().search.setFontColor(node, this.value);
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
      GetUINativeModule().search.resetCopyOption(node);
    }
    else {
      GetUINativeModule().search.setCopyOption(node, this.value);
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
      GetUINativeModule().search.resetTextFont(node);
    }
    else {
      GetUINativeModule().search.setTextFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().search.resetPlaceholderColor(node);
    }
    else {
      GetUINativeModule().search.setPlaceholderColor(node, this.value);
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
      GetUINativeModule().search.resetCancelButton(node);
    }
    else {
      GetUINativeModule().search.setCancelButton(node, this.value.style, (_a = this.value.icon) === null || _a === void 0 ? void 0 : _a.size, (_b = this.value.icon) === null || _b === void 0 ? void 0 : _b.color, (_c = this.value.icon) === null || _c === void 0 ? void 0 : _c.src);
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
      GetUINativeModule().search.resetTextAlign(node);
    }
    else {
      GetUINativeModule().search.setTextAlign(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().span.resetFontSize(node);
    }
    else {
      GetUINativeModule().span.setFontSize(node, this.value);
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
      GetUINativeModule().span.resetFontFamily(node);
    }
    else {
      GetUINativeModule().span.setFontFamily(node, this.value);
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
      GetUINativeModule().span.resetLineHeight(node);
    }
    else {
      GetUINativeModule().span.setLineHeight(node, this.value);
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
      GetUINativeModule().span.resetFontStyle(node);
    }
    else {
      GetUINativeModule().span.setFontStyle(node, this.value);
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
      GetUINativeModule().span.resetTextCase(node);
    }
    else {
      GetUINativeModule().span.setTextCase(node, this.value);
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
      GetUINativeModule().span.resetFontColor(node);
    }
    else {
      GetUINativeModule().span.setFontColor(node, this.value);
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
      GetUINativeModule().span.resetLetterSpacing(node);
    }
    else {
      GetUINativeModule().span.setLetterSpacing(node, this.value);
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
      GetUINativeModule().span.resetFont(node);
    }
    else {
      GetUINativeModule().span.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().span.resetDecoration(node);
    }
    else {
      GetUINativeModule().span.setDecoration(node, this.value.type, this.value.color);
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
      GetUINativeModule().span.resetFontWeight(node);
    }
    else {
      GetUINativeModule().span.setFontWeight(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().sideBarContainer.resetSideBarPosition(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setSideBarPosition(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetAutoHide(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setAutoHide(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetShowSideBar(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setShowSideBar(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetMaxSideBarWidth(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setMaxSideBarWidth(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetSideBarWidth(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setSideBarWidth(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetMinContentWidth(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setMinContentWidth(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetShowControlButton(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setShowControlButton(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetMinSideBarWidth(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setMinSideBarWidth(node, this.value);
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
      GetUINativeModule().sideBarContainer.resetControlButton(node);
    }
    else {
      GetUINativeModule().sideBarContainer.setControlButton(node, this.value.left, this.value.top, this.value.width, this.value.height, (_a = this.value.icons) === null || _a === void 0 ? void 0 : _a.shown, (_b = this.value.icons) === null || _b === void 0 ? void 0 : _b.hidden, (_c = this.value.icons) === null || _c === void 0 ? void 0 : _c.switching);
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
      return !isBaseOrResourceEqual((_a = this.stageValue.icons) === null || _a === void 0 ? void 0 : _a.shown, (_b = this.value.icons) === null || _b === void 0 ? void 0 : _b.shown) ||
        !isBaseOrResourceEqual((_c = this.stageValue.icons) === null || _c === void 0 ? void 0 : _c.hidden, (_d = this.value.icons) === null || _d === void 0 ? void 0 : _d.hidden) ||
        !isBaseOrResourceEqual((_e = this.stageValue.icons) === null || _e === void 0 ? void 0 : _e.switching, (_f = this.value.icons) === null || _f === void 0 ? void 0 : _f.switching);
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
      GetUINativeModule().sideBarContainer.resetDivider(node);
    }
    else {
      if (!this.value || !isObject(this.value) || !this.value.strokeWidth) {
        GetUINativeModule().sideBarContainer.resetDivider(node);
      }
      else {
        GetUINativeModule().sideBarContainer.setDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
class StackAlignContentModifier extends Modifier {
  constructor(nativePtr) {
    super(nativePtr);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().stack.resetAlignContent(node);
    }
    else {
      GetUINativeModule().stack.setAlignContent(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().text.resetFontColor(node);
    }
    else {
      GetUINativeModule().text.setFontColor(node, this.value);
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
FontColorModifier.identity = Symbol('textFontColor');
class FontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().text.resetFontSize(node);
    }
    else {
      GetUINativeModule().text.setFontSize(node, this.value);
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
FontSizeModifier.identity = Symbol('textFontSize');
class FontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().text.resetFontWeight(node);
    }
    else {
      GetUINativeModule().text.setFontWeight(node, this.value);
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
      GetUINativeModule().text.resetFontStyle(node);
    }
    else {
      GetUINativeModule().text.setFontStyle(node, this.value);
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
      GetUINativeModule().text.resetTextAlign(node);
    }
    else {
      GetUINativeModule().text.setTextAlign(node, this.value);
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
      GetUINativeModule().text.resetHeightAdaptivePolicy(node);
    }
    else {
      GetUINativeModule().text.setHeightAdaptivePolicy(node, this.value);
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
      GetUINativeModule().text.resetDraggable(node);
    }
    else {
      GetUINativeModule().text.setDraggable(node, this.value);
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
      GetUINativeModule().text.resetMinFontSize(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().text.resetMinFontSize(node);
    }
    else {
      GetUINativeModule().text.setMinFontSize(node, this.value);
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
      GetUINativeModule().text.resetMaxFontSize(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().text.resetMaxFontSize(node);
    }
    else {
      GetUINativeModule().text.setMaxFontSize(node, this.value);
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
      GetUINativeModule().text.resetLineHeight(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().text.resetLineHeight(node);
    }
    else {
      GetUINativeModule().text.setLineHeight(node, this.value);
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
      GetUINativeModule().text.resetCopyOption(node);
    }
    else {
      GetUINativeModule().text.setCopyOption(node, this.value);
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
      GetUINativeModule().text.resetFontFamily(node);
    }
    else if (!isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().text.resetFontFamily(node);
    }
    else {
      GetUINativeModule().text.setFontFamily(node, this.value);
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
      GetUINativeModule().text.resetMaxLines(node);
    }
    else if (!isNumber(this.value)) {
      GetUINativeModule().text.resetMaxLines(node);
    }
    else {
      GetUINativeModule().text.setMaxLines(node, this.value);
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
      GetUINativeModule().text.resetLetterSpacing(node);
    }
    else if (!isNumber(this.value) && !isString(this.value)) {
      GetUINativeModule().text.resetLetterSpacing(node);
    }
    else {
      GetUINativeModule().text.setLetterSpacing(node, this.value);
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
      GetUINativeModule().text.resetTextOverflow(node);
    }
    else {
      GetUINativeModule().text.setTextOverflow(node, this.value.overflow);
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
      GetUINativeModule().text.resetBaselineOffset(node);
    }
    else if (!isNumber(this.value) && !isString(this.value)) {
      GetUINativeModule().text.resetBaselineOffset(node);
    }
    else {
      GetUINativeModule().text.setBaselineOffset(node, this.value);
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
      GetUINativeModule().text.resetTextCase(node);
    }
    else {
      GetUINativeModule().text.setTextCase(node, this.value);
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
      GetUINativeModule().text.resetTextIndent(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
      GetUINativeModule().text.resetTextIndent(node);
    }
    else {
      GetUINativeModule().text.setTextIndent(node, this.value);
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
      GetUINativeModule().text.resetTextShadow(node);
    }
    else {
      let shadow = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        GetUINativeModule().text.resetTextShadow(node);
      }
      else {
        GetUINativeModule().text.setTextShadow(node, shadow.radius, shadow.type, shadow.color, shadow.offsetX, shadow.offsetY, shadow.fill, shadow.radius.length);
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
      GetUINativeModule().text.resetDecoration(node);
    }
    else {
      GetUINativeModule().text.setDecoration(node, this.value.type, this.value.color);
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
      GetUINativeModule().text.resetFont(node);
    }
    else {
      GetUINativeModule().text.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      if (value === 0) {
        fontWeightStr = 'Lighter';
      }
      else if (value === 1) {
        fontWeightStr = 'Normal';
      }
      else if (value === 2) {
        fontWeightStr = 'Regular';
      }
      else if (value === 3) {
        fontWeightStr = 'Medium';
      }
      else if (value === 4) {
        fontWeightStr = 'Bold';
      }
      else if (value === 5) {
        fontWeightStr = 'Bolder';
      }
      else {
        fontWeightStr = value.toString();
      }
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().textArea.resetFontStyle(node);
    }
    else {
      GetUINativeModule().textArea.setFontStyle(node, this.value);
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
      GetUINativeModule().textArea.resetCopyOption(node);
    }
    else {
      GetUINativeModule().textArea.setCopyOption(node, this.value);
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
      GetUINativeModule().textArea.resetMaxLines(node);
    }
    else {
      GetUINativeModule().textArea.setMaxLines(node, this.value);
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
      GetUINativeModule().textArea.resetFontSize(node);
    }
    else {
      GetUINativeModule().textArea.setFontSize(node, this.value);
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
      GetUINativeModule().textArea.resetPlaceholderColor(node);
    }
    else {
      GetUINativeModule().textArea.setPlaceholderColor(node, this.value);
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
TextAreaPlaceholderColorModifier.identity = Symbol('textAreaPlaceholderColor');
class TextAreaFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textArea.resetFontColor(node);
    }
    else {
      GetUINativeModule().textArea.setFontColor(node, this.value);
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
TextAreaFontColorModifier.identity = Symbol('textAreaFontColor');
class TextAreaFontWeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textArea.resetFontWeight(node);
    }
    else {
      GetUINativeModule().textArea.setFontWeight(node, this.value);
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
      GetUINativeModule().textArea.resetBarState(node);
    }
    else {
      GetUINativeModule().textArea.setBarState(node, this.value);
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
      GetUINativeModule().textArea.resetEnableKeyboardOnFocus(node);
    }
    else {
      GetUINativeModule().textArea.setEnableKeyboardOnFocus(node, this.value);
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
      GetUINativeModule().textArea.resetFontFamily(node);
    }
    else {
      GetUINativeModule().textArea.setFontFamily(node, this.value);
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
      GetUINativeModule().textArea.resetCaretColor(node);
    }
    else {
      GetUINativeModule().textArea.setCaretColor(node, this.value);
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
TextAreaCaretColorModifier.identity = Symbol('textAreaCaretColor');
class TextAreaMaxLengthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textArea.resetMaxLength(node);
    }
    else {
      GetUINativeModule().textArea.setMaxLength(node, this.value);
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
      GetUINativeModule().textArea.resetStyle(node);
    }
    else {
      GetUINativeModule().textArea.setStyle(node, this.value);
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
      GetUINativeModule().textArea.resetSelectionMenuHidden(node);
    }
    else {
      GetUINativeModule().textArea.setSelectionMenuHidden(node, this.value);
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
      GetUINativeModule().textArea.resetPlaceholderFont(node);
    }
    else {
      GetUINativeModule().textArea.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
class TextAreaTextAlignModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textArea.resetTextAlign(node);
    }
    else {
      GetUINativeModule().textArea.setTextAlign(node, this.value);
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
      GetUINativeModule().textArea.resetShowCounter(node);
    }
    else {
      GetUINativeModule().textArea.setShowCounter(node, this.value.value, this.value.options);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().textInput.resetStyle(node);
    }
    else {
      GetUINativeModule().textInput.setStyle(node, this.value);
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
      GetUINativeModule().textInput.resetMaxLength(node);
    }
    else {
      GetUINativeModule().textInput.setMaxLength(node, this.value);
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
      GetUINativeModule().textInput.resetMaxLines(node);
    }
    else {
      GetUINativeModule().textInput.setMaxLines(node, this.value);
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
      GetUINativeModule().textInput.resetShowPasswordIcon(node);
    }
    else {
      GetUINativeModule().textInput.setShowPasswordIcon(node, this.value);
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
      GetUINativeModule().textInput.resetTextAlign(node);
    }
    else {
      GetUINativeModule().textInput.setTextAlign(node, this.value);
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
      GetUINativeModule().textInput.resetPlaceholderFont(node);
    }
    else {
      GetUINativeModule().textInput.setPlaceholderFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().textInput.resetPlaceholderColor(node);
    }
    else {
      GetUINativeModule().textInput.setPlaceholderColor(node, this.value);
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
      GetUINativeModule().textInput.resetPasswordIcon(node);
    }
    else {
      GetUINativeModule().textInput.setPasswordIcon(node, this.value.onIconSrc, this.value.offIconSrc);
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
      GetUINativeModule().textInput.resetSelectedBackgroundColor(node);
    }
    else {
      GetUINativeModule().textInput.setSelectedBackgroundColor(node, this.value);
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
      GetUINativeModule().textInput.resetSelectionMenuHidden(node);
    }
    else {
      GetUINativeModule().textInput.setSelectionMenuHidden(node, this.value);
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
      GetUINativeModule().textInput.resetShowUnderline(node);
    }
    else {
      GetUINativeModule().textInput.setShowUnderline(node, this.value);
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
      GetUINativeModule().textInput.resetShowError(node);
    }
    else {
      GetUINativeModule().textInput.setShowError(node, this.value);
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
      GetUINativeModule().textInput.resetType(node);
    }
    else {
      GetUINativeModule().textInput.setType(node, this.value);
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
      GetUINativeModule().textInput.resetCaretPosition(node);
    }
    else {
      GetUINativeModule().textInput.setCaretPosition(node, this.value);
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
      GetUINativeModule().textInput.resetCopyOption(node);
    }
    else {
      GetUINativeModule().textInput.setCopyOption(node, this.value);
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
      GetUINativeModule().textInput.resetEnableKeyboardOnFocus(node);
    }
    else {
      GetUINativeModule().textInput.setEnableKeyboardOnFocus(node, this.value);
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
      GetUINativeModule().textInput.resetCaretStyle(node);
    }
    else {
      GetUINativeModule().textInput.setCaretStyle(node, this.value.width);
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
      GetUINativeModule().textInput.resetEnterKeyType(node);
    }
    else {
      GetUINativeModule().textInput.setEnterKeyType(node, this.value);
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
      GetUINativeModule().textInput.resetBarState(node);
    }
    else {
      GetUINativeModule().textInput.setBarState(node, this.value);
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
      GetUINativeModule().textInput.resetCaretColor(node);
    }
    else {
      GetUINativeModule().textInput.setCaretColor(node, this.value);
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
      GetUINativeModule().textInput.resetFontColor(node);
    }
    else {
      GetUINativeModule().textInput.setFontColor(node, this.value);
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
      GetUINativeModule().textInput.resetFontSize(node);
    }
    else {
      GetUINativeModule().textInput.setFontSize(node, this.value);
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
      GetUINativeModule().textInput.resetFontStyle(node);
    }
    else {
      GetUINativeModule().textInput.setFontStyle(node, this.value);
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
      GetUINativeModule().textInput.resetFontWeight(node);
    }
    else {
      GetUINativeModule().textInput.setFontWeight(node, this.value);
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
      GetUINativeModule().textInput.resetFontFamily(node);
    }
    else {
      GetUINativeModule().textInput.setFontFamily(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().video.resetObjectFit(node);
    }
    else {
      GetUINativeModule().video.setObjectFit(node, this.value);
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
      GetUINativeModule().video.resetAutoPlay(node);
    }
    else {
      GetUINativeModule().video.setAutoPlay(node, this.value);
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
      GetUINativeModule().video.resetControls(node);
    }
    else {
      GetUINativeModule().video.setControls(node, this.value);
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
      GetUINativeModule().video.resetLoop(node);
    }
    else {
      GetUINativeModule().video.setLoop(node, this.value);
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
      GetUINativeModule().video.resetMuted(node);
    }
    else {
      GetUINativeModule().video.setMuted(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkVideoComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
class ArkTransformMatrix {
  constructor(matrix) {
    this.matrix = matrix;
    this.length = 16;
  }
  compareArrays(arr1, arr2) {
    return (Array.isArray(arr1) &&
      Array.isArray(arr2) &&
      arr1.length === arr2.length &&
      arr1.every((value, index) => value === arr2[index]));
  }
  isEqual(another) {
    return this.compareArrays(this.matrix, another.matrix);
  }
}
class ArkLabelStyle {
  constructor() {
    this.overflow = undefined;
    this.maxLines = undefined;
    this.minFontSize = undefined;
    this.maxFontSize = undefined;
    this.heightAdaptivePolicy = undefined;
    this.font = new ArkLabelFont();
  }
  isEqual(another) {
    return (this.overflow === another.overflow &&
      this.maxLines === another.maxLines &&
      this.minFontSize === another.minFontSize &&
      this.maxFontSize === another.maxFontSize &&
      this.heightAdaptivePolicy === another.heightAdaptivePolicy &&
      this.font.isEqual(another.font));
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
function deepSimpleCopy(obj) {
  if (typeof obj === 'object') {
    if (Array.isArray(obj)) {
      let result = [];
      for (let i = 0; i < obj.length; i++) {
        result[i] = deepSimpleCopy(obj[i]);
      }
      return result;
    }
    else {
      let result = {};
      for (const key in obj) {
        if (obj.hasOwnProperty(key)) {
          result[key] = deepSimpleCopy(obj[key]);
        }
      }
      return result;
    }
  }
  return obj;
}
function copyColorStop(colorStop) {
  if (Array.isArray(colorStop)) {
    let result = [];
    for (let index = 0; index < colorStop.length; index++) {
      let value = colorStop[index];
      if (index === 0) {
        let arkColor = new ArkColor();
        if (arkColor.parseColorValue(value)) {
          result[0] = arkColor.getColor();
        }
        continue;
      }
      result[index] = deepSimpleCopy(value);
    }
    return result;
  }
  return deepSimpleCopy(colorStop);
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
class ArkRadialGradient {
  constructor(center, radius, colors, repeating) {
    this.center = center;
    this.radius = radius;
    this.colors = colors;
    this.repeating = repeating;
  }
  isEqual(another) {
    return (deepCompareArrays(this.center, another.center) &&
      this.radius === another.radius &&
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
class ArkFont {
  constructor() {
    this.size = undefined;
    this.weight = undefined;
  }
  setSize(size) {
    this.size = size;
  }
  setFamily(family) {
    this.family = family;
  }
  setStyle(style) {
    this.style = style;
  }
  isEqual(another) {
    return (this.size === another.size &&
      this.weight === another.weight &&
      this.family === another.family &&
      this.style === another.style);
  }
  parseFontWeight(value) {
    const valueWeightMap = {
      [0]: 'Lighter',
      [1]: 'Normal',
      [2]: 'Regular',
      [3]: 'Medium',
      [4]: 'Bold',
      [5]: 'Bolder'
    };
    if (value in valueWeightMap) {
      this.weight = valueWeightMap[value];
    }
    else {
      this.weight = value.toString();
    }
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
class ArkTextStyle {
  constructor() {
    this.color = undefined;
    this.font = new ArkFont();
  }
  parseTextStyle(value) {
    if (isObject(value)) {
      let color = new ArkColor();
      let inputFont = value.font;
      let inputColor = value.color;
      if (!isUndefined(inputColor) && (isNumber(inputColor) || isString(inputColor))) {
        color.parseColorValue(inputColor);
        this.color = color.getColor();
      }
      if (!isUndefined(inputFont) && isObject(inputFont)) {
        if (!isUndefined(inputFont.size)) {
          this.font.size = inputFont.size;
        }
        if (!isUndefined(inputFont.weight)) {
          this.font.parseFontWeight(inputFont.weight);
        }
        this.font.family = inputFont.family;
        this.font.style = inputFont.style;
      }
    }
  }
  isEqual(another) {
    return this.color === another.color && this.font.isEqual(another.font);
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
class ArkBlockSize {
  constructor() {
    this.width = undefined;
    this.height = undefined;
  }
  isEqual(another) {
    return this.width === another.width && this.height === another.height;
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
class ArkBackgroundImagePosition {
  constructor() {
    this.alignment = undefined;
    this.x = undefined;
    this.y = undefined;
  }
  isEqual(another) {
    return this.alignment === another.alignment && this.x === another.x && this.y === another.y;
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
class ArkTranslate {
  constructor() {
    this.x = undefined;
    this.y = undefined;
    this.z = undefined;
  }
  isEqual(another) {
    return this.x === another.x && this.y === another.y && this.z === another.z;
  }
}
class ArkScale {
  constructor() {
    this.x = undefined;
    this.y = undefined;
    this.z = undefined;
    this.centerX = undefined;
    this.centerY = undefined;
  }
  isEqual(another) {
    return (this.x === another.x &&
      this.y === another.y &&
      this.z === another.z &&
      this.centerX === another.centerX &&
      this.centerY === another.centerY);
  }
}
class ArkRotate {
  constructor() {
    this.x = undefined;
    this.y = undefined;
    this.z = undefined;
    this.angle = undefined;
    this.centerX = undefined;
    this.centerY = undefined;
    this.centerZ = undefined;
    this.perspective = undefined;
  }
  isEqual(another) {
    return (this.x === another.x &&
      this.y === another.y &&
      this.z === another.z &&
      this.angle === another.angle &&
      this.centerX === another.centerX &&
      this.centerY === another.centerY &&
      this.centerZ === another.centerZ &&
      this.perspective === another.perspective);
  }
}
class ArkMotionPath {
  constructor() {
    this.path = undefined;
    this.from = undefined;
    this.to = undefined;
    this.rotatable = undefined;
  }
  isEqual(another) {
    return (this.path === another.path &&
      this.from === another.from &&
      this.to === another.to &&
      this.rotatable === another.rotatable);
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
class ArkSize {
  constructor() {
    this.width = undefined;
    this.height = undefined;
  }
  isEqual(another) {
    return this.width === another.width && this.height === another.height;
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
class ArkAllowDrop {
  constructor() {
    this.allowDropArray = undefined;
  }
  isEqual(another) {
    return this.allowDropArray === another.allowDropArray;
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
class ArkBarBackgroundColor {
  isEqual(another) {
    return (this.value === another.value);
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
class ArkObscured {
  constructor() {
    this.reasons = [];
  }
  parseReasonsArray(reasonObject) {
    if (Array.isArray(reasonObject)) {
      for (let i = 0; i < reasonObject.length; i++) {
        this.reasons.push(reasonObject[i]);
      }
      return true;
    }
    return false;
  }
  isEqual(another) {
    return this.reasons === another.reasons;
  }
}
class ArkResponseRegion {
  constructor() {
    this.responseRegion = [];
  }
  isObject(region) {
    return region !== null && !Array.isArray(region) && typeof region === 'object';
  }
  parseRegionValue(value) {
    if (Array.isArray(value)) {
      return this.parseArrayList(value);
    }
    else if (this.isObject(value)) {
      return this.parseArray(value);
    }
    else if (value === undefined) {
      this.responseRegion = [];
      return true;
    }
    return false;
  }
  parseArray(regionObject) {
    let _a, _b, _c, _d;
    if (this.isObject(regionObject)) {
      let x = (_a = regionObject['x']) !== null && _a !== void 0 ? _a : 'PLACEHOLDER';
      let y = (_b = regionObject['y']) !== null && _b !== void 0 ? _b : 'PLACEHOLDER';
      let width = (_c = regionObject['width']) !== null && _c !== void 0 ? _c : 'PLACEHOLDER';
      let height = (_d = regionObject['height']) !== null && _d !== void 0 ? _d : 'PLACEHOLDER';
      this.responseRegion.push(x.toString());
      this.responseRegion.push(y.toString());
      this.responseRegion.push(width.toString());
      this.responseRegion.push(height.toString());
      return true;
    }
    return false;
  }
  parseArrayList(regionObject) {
    if (Array.isArray(regionObject)) {
      for (let i = 0; i < regionObject.length; i++) {
        this.parseArray(regionObject[i]);
      }
      return true;
    }
    return false;
  }
  isEqual(another) {
    return this.responseRegion === another.responseRegion;
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
class ArkSideBarDividerStyle {
  constructor() {
    this.startMargin = undefined;
    this.endMargin = undefined;
  }
  isEqual(another) {
    return this.strokeWidth === another.strokeWidth &&
      this.color === another.color &&
      this.startMargin === another.startMargin &&
      this.endMargin === another.endMargin;
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
class ArkPasswordIcon {
  constructor() {
    this.onIconSrc = undefined;
    this.offIconSrc = undefined;
  }
  isEqual(another) {
    return this.onIconSrc === another.onIconSrc &&
      this.offIconSrc === another.offIconSrc;
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
class ArkPickerTextStyle {
  constructor() {
    this.color = undefined;
    this.size = '16fp';
    this.weight = 'Regular';
  }
  setColor(color) {
    let arkColor = new ArkColor();
    arkColor.parseColorValue(color);
    this.color = arkColor.color;
  }
  setSize(size) {
    this.size = size.toString();
  }
  setWeight(value) {
    const valueWeightMap = {
      [0]: 'Lighter',
      [1]: 'Normal',
      [2]: 'Regular',
      [3]: 'Medium',
      [4]: 'Bold',
      [5]: 'Bolder'
    };
    if (value in valueWeightMap) {
      this.weight = valueWeightMap[value];
    }
    else {
      this.weight = value.toString();
    }
  }
  isEqual(another) {
    return this.color === another.color && this.size === another.size && this.weight === another.weight;
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
class ArkDatePickerTextStyle {
  constructor() {
    this.color = undefined;
    this.font = undefined;
  }
  isEqual(another) {
    return (this.color === another.color && this.font === another.font);
  }
}
class ArkClickEffect {
  constructor() {
    this.level = undefined;
    this.scale = undefined;
  }
  isEqual(another) {
    return (this.level === another.level) && (this.scale === another.scale);
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
class ArkResourceColor {
  constructor() {
    this.color = undefined;
  }
  isEqual(another) {
    return (this.color === another.color);
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
/// <reference path='./ArkComponent.ts' />
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
    if (isNumber(value)) {
      modifier(this._modifiers, ButtonTypeModifier, value);
    }
    else {
      modifier(this._modifiers, ButtonTypeModifier, undefined);
    }
    return this;
  }
  stateEffect(value) {
    if (isBoolean(value)) {
      modifier(this._modifiers, ButtonStateEffectModifier, value);
    }
    else {
      modifier(this._modifiers, ButtonStateEffectModifier, undefined);
    }
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
    if (typeof value === 'string' || typeof value === 'number') {
      modifier(this._modifiers, ButtonFontWeightModifier, value);
    }
    else {
      modifier(this._modifiers, ButtonFontWeightModifier, undefined);
    }
    return this;
  }
  fontStyle(value) {
    if (typeof value === 'number' && value >= 0 && value < 2) {
      modifier(this._modifiers, ButtonFontStyleModifier, value);
    }
    else {
      modifier(this._modifiers, ButtonFontStyleModifier, undefined);
    }
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
      GetUINativeModule().button.resetBackgroundColor(node);
    }
    else {
      GetUINativeModule().button.setBackgroundColor(node, this.value);
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
ButtonBackgroundColorModifier.identity = Symbol('buttonBackgroundColor');
class ButtonStateEffectModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetStateEffect(node);
    }
    else {
      GetUINativeModule().button.setStateEffect(node, this.value);
    }
  }
}
ButtonStateEffectModifier.identity = Symbol('buttonStateEffect');
class ButtonFontStyleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetFontStyle(node);
    }
    else {
      GetUINativeModule().button.setFontStyle(node, this.value);
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
      GetUINativeModule().button.resetFontFamily(node);
    }
    else {
      GetUINativeModule().button.setFontFamily(node, this.value);
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
ButtonFontFamilyModifier.identity = Symbol('buttonFontFamily');
class ButtonLabelStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetLabelStyle(node);
    }
    else {
      let textOverflow = this.value.overflow; // number -> Ace::TextOverflow
      let maxLines = this.value.maxLines; // number -> uint32_t
      let minFontSize = this.value.minFontSize; // number/string -> Dimension
      let maxFontSize = this.value.maxFontSize; // number/string -> Dimension
      let heightAdaptivePolicy = this.value.heightAdaptivePolicy; // number -> Ace::TextHeightAdaptivePolicy
      let fontSize = undefined; // number/string ->Dimension
      let fontWeight = undefined; // string -> Ace::FontWeight
      let fontStyle = undefined; // number -> Ace::FontStyle
      let fontFamily = undefined; // string ->std::vector<std::string>
      if (isObject(this.value.font)) {
        fontSize = this.value.font.size;
        fontWeight = 'normal';
        fontStyle = this.value.font.style;
        fontFamily = this.value.font.family;
        if (typeof this.value.font.weight === 'string') {
          fontWeight = this.value.font.weight;
        }
        else {
          if (this.value.font.weight in FontWeightMap) {
            fontWeight = FontWeightMap[this.value.font.weight];
          }
        }
        GetUINativeModule().button.setLabelStyle(node, textOverflow, maxLines, minFontSize, maxFontSize, heightAdaptivePolicy, fontSize, fontWeight, fontStyle, fontFamily);
      }
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
class ButtonTypeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetType(node);
    }
    else {
      GetUINativeModule().button.setType(node, this.value);
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
      GetUINativeModule().button.resetFontColor(node);
    }
    else {
      GetUINativeModule().button.setFontColor(node, this.value);
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
ButtonFontColorModifier.identity = Symbol('buttonFontColor');
class ButtonFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetFontSize(node);
    }
    else {
      GetUINativeModule().button.setFontSize(node, this.value);
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
ButtonFontSizeModifier.identity = Symbol('buttonFontSize');
class ButtonFontWeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().button.resetFontWeight(node);
    }
    else {
      let fontWeightStr = 'normal';
      if (typeof this.value === 'string') {
        fontWeightStr = this.value;
      }
      else {
        if (this.value in FontWeightMap) {
          fontWeightStr = FontWeightMap[this.value];
        }
      }
      GetUINativeModule().button.setFontWeight(node, fontWeightStr);
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
      GetUINativeModule().button.resetButtonBorderRadius(node);
    } else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().button.setButtonBorderRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().button.setButtonBorderRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().loadingProgress.resetColor(node);
    }
    else {
      GetUINativeModule().loadingProgress.setColor(node, this.value);
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
      GetUINativeModule().loadingProgress.resetEnableLoading(node);
    }
    else {
      GetUINativeModule().loadingProgress.setEnableLoading(node, this.value);
    }
  }
}
LoadingProgressEnableLoadingModifier.identity = Symbol('loadingProgressEnableLoading');
// @ts-ignore
globalThis.LoadingProgress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().scroll.resetNestedScroll(node);
    }
    else {
      GetUINativeModule().scroll.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
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
      GetUINativeModule().scroll.resetEnableScroll(node);
    }
    else {
      GetUINativeModule().scroll.setEnableScroll(node, this.value);
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
      GetUINativeModule().scroll.resetFriction(node);
    }
    else {
      GetUINativeModule().scroll.setFriction(node, this.value);
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
ScrollFrictionModifier.identity = Symbol('friction');
class ScrollScrollSnapModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().scroll.resetScrollSnap(node);
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
        GetUINativeModule().scroll.setScrollSnap(node, this.value.snapAlign, snapPagination, this.value.enableSnapToStart, this.value.enableSnapToEnd);
      }
      else {
        GetUINativeModule().scroll.setScrollSnap(node, this.value.snapAlign, this.value.snapPagination, this.value.enableSnapToStart, this.value.enableSnapToEnd);
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
      GetUINativeModule().scroll.resetScrollBar(node);
    }
    else {
      GetUINativeModule().scroll.setScrollBar(node, this.value);
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
      GetUINativeModule().scroll.resetScrollable(node);
    }
    else {
      GetUINativeModule().scroll.setScrollable(node, this.value);
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
      GetUINativeModule().scroll.resetEdgeEffect(node);
    }
    else {
      GetUINativeModule().scroll.setEdgeEffect(node, this.value.value, (_a = this.value.options) === null || _a === void 0 ? void 0 : _a.alwaysEnabled);
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
      GetUINativeModule().scroll.resetScrollBarWidth(node);
    }
    else {
      GetUINativeModule().scroll.setScrollBarWidth(node, this.value);
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
      GetUINativeModule().scroll.resetScrollBarColor(node);
    }
    else {
      GetUINativeModule().scroll.setScrollBarColor(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().toggle.resetSelectedColor(node);
    }
    else {
      GetUINativeModule().toggle.setSelectedColor(node, this.value);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    return true;
  }
}
ToggleSelectedColorModifier.identity = Symbol('toggleSelectedColor');
class ToggleSwitchPointColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().toggle.resetSwitchPointColor(node);
    }
    else {
      GetUINativeModule().toggle.setSwitchPointColor(node, this.value);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    return true;
  }
}
ToggleSwitchPointColorModifier.identity = Symbol('toggleSwitchPointColor');
// @ts-ignore
globalThis.Toggle.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().select.resetFont(node);
    }
    else {
      GetUINativeModule().select.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().select.resetOptionFont(node);
    }
    else {
      GetUINativeModule().select.setOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().select.resetSelectedOptionFont(node);
    }
    else {
      GetUINativeModule().select.setSelectedOptionFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().select.resetMenuAlign(node);
    }
    else {
      GetUINativeModule().select.setMenuAlign(node, this.value.alignType, this.value.dx, this.value.dy);
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
      GetUINativeModule().select.resetArrowPosition(node);
    }
    else {
      GetUINativeModule().select.setArrowPosition(node, this.value);
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
      GetUINativeModule().select.resetSpace(node);
    }
    else {
      GetUINativeModule().select.setSpace(node, this.value);
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
      GetUINativeModule().select.resetValue(node);
    }
    else {
      GetUINativeModule().select.setValue(node, this.value);
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
      GetUINativeModule().select.resetSelected(node);
    }
    else {
      GetUINativeModule().select.setSelected(node, this.value);
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
      GetUINativeModule().select.resetFontColor(node);
    }
    else {
      GetUINativeModule().select.setFontColor(node, this.value);
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
      GetUINativeModule().select.resetSelectedOptionBgColor(node);
    }
    else {
      GetUINativeModule().select.setSelectedOptionBgColor(node, this.value);
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
      GetUINativeModule().select.resetOptionBgColor(node);
    }
    else {
      GetUINativeModule().select.setOptionBgColor(node, this.value);
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
      GetUINativeModule().select.resetOptionFontColor(node);
    }
    else {
      GetUINativeModule().select.setOptionFontColor(node, this.value);
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
      GetUINativeModule().select.resetSelectedOptionFontColor(node);
    }
    else {
      GetUINativeModule().select.setSelectedOptionFontColor(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    if (!!value) {
      modifier(this._modifiers, RadioCheckedModifier, value);
    }
    else {
      modifier(this._modifiers, RadioCheckedModifier, undefined);
    }
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
class RadioCheckedModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().radio.resetRadioChecked(node);
    }
    else {
      GetUINativeModule().radio.setRadioChecked(node, this.value);
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
      GetUINativeModule().radio.resetRadioStyle(node);
    }
    else {
      GetUINativeModule().radio.setRadioStyle(node, this.value.checkedBackgroundColor, this.value.uncheckedBorderColor, this.value.indicatorColor);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().timepicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
TimepickerTextStyleModifier.identity = Symbol('textStyle');
class TimepickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().timepicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
TimepickerSelectedTextStyleModifier.identity = Symbol('selectedTextStyle');
class TimepickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().timepicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().timepicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
TimepickerDisappearTextStyleModifier.identity = Symbol('disappearTextStyle');
// @ts-ignore
globalThis.TimePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    if (isResource(value)) {
      modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, undefined);
    }
    else {
      modifier(this._modifiers, TextpickerDefaultPickerItemHeightModifier, value);
    }
    return this;
  }
  canLoop(value) {
    if (isUndefined(value)) {
      modifier(this._modifiers, TextpickerCanLoopModifier, undefined);
    }
    else {
      modifier(this._modifiers, TextpickerCanLoopModifier, value);
    }
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
    let input = new ArkSelectedIndices();
    if (!Array.isArray(value)) {
      if (!isNumber(value)) {
        modifier(this._modifiers, TextpickerSelectedIndexModifier, undefined);
        return this;
      }
      input.selectedValues[0] = value;
    }
    else {
      input.selectedValues = value;
    }
    modifier(this._modifiers, TextpickerSelectedIndexModifier, input);
    return this;
  }
}
class TextpickerCanLoopModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textpicker.resetCanLoop(node);
    }
    else {
      GetUINativeModule().textpicker.setCanLoop(node, this.value);
    }
  }
}
TextpickerCanLoopModifier.identity = Symbol('textpickerCanLoop');
class TextpickerSelectedIndexModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textpicker.resetSelectedIndex(node);
    }
    else {
      GetUINativeModule().textpicker.setSelectedIndex(node, this.value.selectedValues);
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
      GetUINativeModule().textpicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
TextpickerTextStyleModifier.identity = Symbol('textpickerTextStyle');
class TextpickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().textpicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
TextpickerSelectedTextStyleModifier.identity = Symbol('textpickerSelectedTextStyle');
class TextpickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().textpicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().textpicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
class TextpickerDefaultPickerItemHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textpicker.resetDefaultPickerItemHeight(node);
    }
    else {
      GetUINativeModule().textpicker.setDefaultPickerItemHeight(node, this.value);
    }
  }
}
TextpickerDefaultPickerItemHeightModifier.identity = Symbol('textpickerDefaultPickerItemHeight');
// @ts-ignore
globalThis.TextPicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().slider.resetBlockStyle(node);
    }
    else {
      GetUINativeModule().slider.setBlockStyle(node, this.value);
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
      GetUINativeModule().slider.resetShowTips(node);
    }
    else {
      GetUINativeModule().slider.setShowTips(node, this.value.showTip, (_a = this.value) === null || _a === void 0 ? void 0 : _a.tipText);
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
      GetUINativeModule().slider.resetStepSize(node);
    }
    else {
      GetUINativeModule().slider.setStepSize(node, this.value);
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
StepSizeModifier.identity = Symbol('sliderStepSize');
class BlockSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetBlockSize(node);
    }
    else {
      GetUINativeModule().slider.setBlockSize(node, this.value.width, this.value.height);
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
      GetUINativeModule().slider.resetTrackBorderRadius(node);
    }
    else {
      GetUINativeModule().slider.setTrackBorderRadius(node, this.value);
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
TrackBorderRadiusModifier.identity = Symbol('sliderTrackBorderRadius');
class StepColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetStepColor(node);
    }
    else {
      GetUINativeModule().slider.setStepColor(node, this.value);
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
StepColorModifier.identity = Symbol('sliderStepColor');
class BlockBorderColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetBlockBorderColor(node);
    }
    else {
      GetUINativeModule().slider.setBlockBorderColor(node, this.value);
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
BlockBorderColorModifier.identity = Symbol('sliderBlockBorderColor');
class BlockBorderWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetBlockBorderWidth(node);
    }
    else {
      GetUINativeModule().slider.setBlockBorderWidth(node, this.value);
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
BlockBorderWidthModifier.identity = Symbol('sliderBlockBorderWidth');
class BlockColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetBlockColor(node);
    }
    else {
      GetUINativeModule().slider.setBlockColor(node, this.value);
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
BlockColorModifier.identity = Symbol('sliderBlockColor');
class TrackColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetTrackBackgroundColor(node);
    }
    else {
      GetUINativeModule().slider.setTrackBackgroundColor(node, this.value);
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
TrackColorModifier.identity = Symbol('sliderTrackColor');
class SelectColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetSelectColor(node);
    }
    else {
      GetUINativeModule().slider.setSelectColor(node, this.value);
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
SelectColorModifier.identity = Symbol('sliderSelectColor');
class ShowStepsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().slider.resetShowSteps(node);
    }
    else {
      GetUINativeModule().slider.setShowSteps(node, this.value);
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
      GetUINativeModule().slider.resetThickness(node);
    }
    else {
      GetUINativeModule().slider.setThickness(node, this.value);
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
TrackThicknessModifier.identity = Symbol('sliderTrackThickness');
// @ts-ignore
globalThis.Slider.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkSliderComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
class RatingStarsModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().rating.resetStars(node);
    }
    else {
      GetUINativeModule().rating.setStars(node, this.value);
    }
  }
}
RatingStarsModifier.identity = Symbol('ratingStars');
class RatingStepSizeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().rating.resetStepSize(node);
    }
    else {
      GetUINativeModule().rating.setStepSize(node, this.value);
    }
  }
}
RatingStepSizeModifier.identity = Symbol('ratingStepSize');
class RatingStarStyleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      GetUINativeModule().rating.resetStarStyle(node);
    }
    else {
      GetUINativeModule().rating.setStarStyle(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.backgroundUri, (_b = this.value) === null || _b === void 0 ? void 0 : _b.foregroundUri, (_c = this.value) === null || _c === void 0 ? void 0 : _c.secondaryUri);
    }
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
    if (!isUndefined(value)) {
      modifier(this._modifiers, RatingStarsModifier, value);
    }
    else {
      modifier(this._modifiers, RatingStarsModifier, undefined);
    }
    return this;
  }
  stepSize(value) {
    if (isNumber(value)) {
      modifier(this._modifiers, RatingStepSizeModifier, value);
    }
    else {
      modifier(this._modifiers, RatingStepSizeModifier, undefined);
    }
    return this;
  }
  starStyle(value) {
    let starStyle = new ArkStarStyle();
    if (!isUndefined(value)) {
      starStyle.backgroundUri = value.backgroundUri;
      starStyle.foregroundUri = value.foregroundUri;
      starStyle.secondaryUri = value.secondaryUri;
      modifier(this._modifiers, RatingStarStyleModifier, starStyle);
    }
    else {
      modifier(this._modifiers, RatingStarStyleModifier, undefined);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().checkbox.resetMark(node);
    }
    else {
      GetUINativeModule().checkbox.setMark(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null || _b === void 0 ? void 0 : _b.size, (_c = this.value) === null || _c === void 0 ? void 0 : _c.strokeWidth);
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
      GetUINativeModule().checkbox.resetSelect(node);
    }
    else {
      GetUINativeModule().checkbox.setSelect(node, this.value);
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
      GetUINativeModule().checkbox.resetHeight(node);
    }
    else {
      GetUINativeModule().checkbox.setHeight(node, this.value);
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
      GetUINativeModule().checkbox.resetWidth(node);
    }
    else {
      GetUINativeModule().checkbox.setWidth(node, this.value);
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
      GetUINativeModule().checkbox.resetSelectedColor(node);
    }
    else {
      GetUINativeModule().checkbox.setSelectedColor(node, this.value);
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
      GetUINativeModule().checkbox.resetUnSelectedColor(node);
    }
    else {
      GetUINativeModule().checkbox.setUnSelectedColor(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, HideTitleBarModifier, value);
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
class HideTitleBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navDestination.resetHideTitleBar(node);
    }
    else {
      GetUINativeModule().navDestination.setHideTitleBar(node, this.value);
    }
  }
}
HideTitleBarModifier.identity = Symbol('hideTitleBar');
//@ts-ignore
globalThis.NavDestination.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    if (isBoolean(value)) {
      modifier(this._modifiers, EnableDecModifier, value);
    }
    else {
      modifier(this._modifiers, EnableDecModifier, undefined);
    }
    return this;
  }
  enableInc(value) {
    if (isBoolean(value)) {
      modifier(this._modifiers, EnableIncModifier, value);
    }
    else {
      modifier(this._modifiers, EnableIncModifier, undefined);
    }
    return this;
  }
}
class EnableIncModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().counter.resetEnableInc(node);
    }
    else {
      GetUINativeModule().counter.setEnableInc(node, this.value);
    }
  }
}
EnableIncModifier.identity = Symbol('enableInc');
class EnableDecModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().counter.resetEnableDec(node);
    }
    else {
      GetUINativeModule().counter.setEnableDec(node, this.value);
    }
  }
}
EnableDecModifier.identity = Symbol('enableDec');
// @ts-ignore
globalThis.Counter.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCounterComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
class CheckboxGroupSelectAllModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().checkboxgroup.resetCheckboxGroupSelectAll(node);
    }
    else {
      GetUINativeModule().checkboxgroup.setCheckboxGroupSelectAll(node, this.value);
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
CheckboxGroupSelectedColorModifier.identity = Symbol('checkboxgroupSelectedColor');
class CheckboxGroupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
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
CheckboxGroupUnselectedColorModifier.identity = Symbol('checkboxgroupUnselectedColor');
class CheckboxGroupMarkModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c;
    if (reset) {
      GetUINativeModule().checkboxgroup.resetCheckboxGroupMark(node);
    }
    else {
      GetUINativeModule().checkboxgroup.setCheckboxGroupMark(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeColor, (_b = this.value) === null || _b === void 0 ? void 0 : _b.size, (_c = this.value) === null || _c === void 0 ? void 0 : _c.strokeWidth);
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
    if (isBoolean(value)) {
      modifier(this._modifiers, CheckboxGroupSelectAllModifier, value);
    }
    else {
      modifier(this._modifiers, CheckboxGroupSelectAllModifier, undefined);
    }
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkCheckboxGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
const COLOR_WITH_MAGIC = /#[0-9A-Fa-f]{6,8}/;
const COLOR_WITH_MAGIC_MINI = /#[0-9A-Fa-f]{3,4}/;
const COLOR_WITH_RGB = /rgb\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\)/i;
const COLOR_WITH_RGBA = /rgba\(([0-9]{1,3})\,([0-9]{1,3})\,([0-9]{1,3})\,(\d+\.?\d*)\)/i;
const COLOR_ALPHA_MASK = 0xff000000;
const MIN_RGB_VALUE = 0;
const MAX_RGB_VALUE = 255;
const COLOR_ALPHA_OFFSET = 24;
const MIN_RGBA_OPACITY = 0.0;
const MAX_RGBA_OPACITY = 1.0;
const MIN_COLOR_STR_LEN = 8;
const HEX_DECIMAL = 16;
class ArkColor {
  constructor() {
    this.color = undefined;
  }
  isEqual(another) {
    return (this.color === another.color);
  }
  parseColorValue(value) {
    if (isResource(value)) {
      return false;
    }
    if (typeof value === 'number') {
      return this.parseColorUint(value);
    }
    else if (typeof value === 'string') {
      return this.parseColorString(value);
    }
    else if (value === undefined) {
      this.color = value;
      return true;
    }
    return false;
  }
  parseColorString(colorStr) {
    if (colorStr.length === 0) {
      return false;
    }
    colorStr = colorStr.replace(/\s/g, '');
    return (this.matchColorWithMagic(colorStr) ||
      this.matchColorWithMagicMini(colorStr) ||
      this.matchColorWithRGB(colorStr) ||
      this.matchColorWithRGBA(colorStr) ||
      this.matchColorSpecialString(colorStr) ||
      this.parseUintColorString(colorStr));
  }
  matchColorWithMagic(colorStr) {
    const matches = colorStr.match(COLOR_WITH_MAGIC);
    if (matches) {
      colorStr = colorStr.substr(1);
      let value = parseInt(colorStr, HEX_DECIMAL);
      if (colorStr.length < MIN_COLOR_STR_LEN) {
        value |= COLOR_ALPHA_MASK;
      }
      this.color = value;
      return true;
    }
    return false;
  }
  matchColorWithMagicMini(colorStr) {
    const matches = colorStr.match(COLOR_WITH_MAGIC_MINI);
    if (matches) {
      colorStr = colorStr.substr(1);
      let newColorStr = colorStr.replace(/./g, (match) => match + match);
      let value = parseInt(newColorStr, HEX_DECIMAL);
      if (newColorStr.length < MIN_COLOR_STR_LEN) {
        value |= COLOR_ALPHA_MASK;
      }
      this.color = value;
      return true;
    }
    return false;
  }
  matchColorWithRGB(colorStr) {
    const matches = colorStr.match(COLOR_WITH_RGB);
    if (matches && matches.length === 4) {
      const [_, redInt, greenInt, blueInt] = matches;
      if (this.isRGBValid(parseInt(redInt)) && this.isRGBValid(parseInt(greenInt)) && this.isRGBValid(parseInt(blueInt))) {
        this.color = this.fromRGB(parseInt(redInt), parseInt(greenInt), parseInt(blueInt));
        return true;
      }
    }
    return false;
  }
  matchColorWithRGBA(colorStr) {
    const matches = colorStr.match(COLOR_WITH_RGBA);
    if (matches && matches.length === 5) {
      const [_, redInt, greenInt, blueInt, opacityDouble] = matches;
      if (this.isRGBValid(parseInt(redInt)) &&
        this.isRGBValid(parseInt(greenInt)) &&
        this.isRGBValid(parseInt(blueInt)) &&
        this.isOpacityValid(parseFloat(opacityDouble))) {
        this.color = this.fromRGBO(parseInt(redInt), parseInt(greenInt), parseInt(blueInt), parseFloat(opacityDouble));
        return true;
      }
    }
    return false;
  }
  matchColorSpecialString(colorStr) {
    const colorTable = {
      black: 0xff000000,
      blue: 0xff0000ff,
      gray: 0xffc0c0c0,
      green: 0xff00ff00,
      red: 0xffff0000,
      white: 0xffffffff,
    };
    if (colorStr in colorTable) {
      this.color = colorTable[colorStr];
      return true;
    }
    return false;
  }
  parseUintColorString(colorStr) {
    const colorInt = Number(colorStr);
    return this.parseColorUint(colorInt);
  }
  parseColorUint(colorInt) {
    if (colorInt > 0) {
      this.color = colorInt;
      if ((colorInt & COLOR_ALPHA_MASK) === 0) {
        this.color |= COLOR_ALPHA_MASK;
      }
      return true;
    }
    return false;
  }
  isRGBValid(value) {
    return value >= MIN_RGB_VALUE && value <= MAX_RGB_VALUE;
  }
  isOpacityValid(value) {
    return value >= MIN_RGBA_OPACITY && value <= MAX_RGBA_OPACITY;
  }
  fromARGB(alpha, red, green, blue) {
    const argb = (alpha << 24) | (red << 16) | (green << 8) | blue;
    return argb >>> 0;
  }
  fromRGBO(red, green, blue, opacity) {
    const alpha = Math.round(opacity * 0xff) & 0xff;
    return this.fromARGB(alpha, red, green, blue);
  }
  fromRGB(red, green, blue) {
    return this.fromARGB(0xff, red, green, blue);
  }
  getColor() {
    return this.color;
  }
}
/// <reference path='./import.ts' />
class ArkPanelComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  mode(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, PanelModeModifier, value);
    }
    else {
      modifier(this._modifiers, PanelModeModifier, undefined);
    }
    return this;
  }
  type(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, PanelTypeModifier, value);
    }
    else {
      modifier(this._modifiers, PanelTypeModifier, undefined);
    }
    return this;
  }
  dragBar(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, DragBarModifier, value);
    }
    else {
      modifier(this._modifiers, DragBarModifier, undefined);
    }
    return this;
  }
  customHeight(value) {
    modifierWithKey(this._modifiersWithKeys, PanelCustomHeightModifier.identity, PanelCustomHeightModifier, value);
    return this;
  }
  fullHeight(value) {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelFullHeightModifier, undefined);
    }
    else {
      modifier(this._modifiers, PanelFullHeightModifier, value);
    }
    return this;
  }
  halfHeight(value) {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelHalfHeightModifier, undefined);
    }
    else {
      modifier(this._modifiers, PanelHalfHeightModifier, value);
    }
    return this;
  }
  miniHeight(value) {
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, PanelMiniHeightModifier, undefined);
    }
    else {
      modifier(this._modifiers, PanelMiniHeightModifier, value);
    }
    return this;
  }
  show(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, ShowModifier, value);
    }
    else {
      modifier(this._modifiers, ShowModifier, undefined);
    }
    return this;
  }
  backgroundMask(color) {
    modifierWithKey(this._modifiersWithKeys, PanelBackgroundMaskModifier.identity, PanelBackgroundMaskModifier, color);
    return this;
  }
  showCloseIcon(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, ShowCloseIconModifier, value);
    }
    else {
      modifier(this._modifiers, ShowCloseIconModifier, undefined);
    }
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
      GetUINativeModule().panel.resetPanelBackgroundMask(node);
    }
    else {
      GetUINativeModule().panel.setPanelBackgroundMask(node, this.value);
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
PanelBackgroundMaskModifier.identity = Symbol('panelBackgroundMask');
class PanelModeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelMode(node);
    }
    else {
      GetUINativeModule().panel.setPanelMode(node, this.value);
    }
  }
}
PanelModeModifier.identity = Symbol('panelMode');
class PanelTypeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelType(node);
    }
    else {
      GetUINativeModule().panel.setPanelType(node, this.value);
    }
  }
}
PanelTypeModifier.identity = Symbol('panelType');
class PanelCustomHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelCustomHeight(node);
    }
    else {
      GetUINativeModule().panel.setPanelCustomHeight(node, this.value);
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
PanelCustomHeightModifier.identity = Symbol('panelCustomHeight');
class PanelFullHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelFullHeight(node);
    }
    else {
      GetUINativeModule().panel.setPanelFullHeight(node, this.value);
    }
  }
}
PanelFullHeightModifier.identity = Symbol('panelFullHeight');
class PanelHalfHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelHalfHeight(node);
    }
    else {
      GetUINativeModule().panel.setPanelHalfHeight(node, this.value);
    }
  }
}
PanelHalfHeightModifier.identity = Symbol('panelHalfHeight');
class PanelMiniHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetPanelMiniHeight(node);
    }
    else {
      GetUINativeModule().panel.setPanelMiniHeight(node, this.value);
    }
  }
}
PanelMiniHeightModifier.identity = Symbol('panelMiniHeight');
class ShowCloseIconModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetShowCloseIcon(node);
    }
    else {
      GetUINativeModule().panel.setShowCloseIcon(node, this.value);
    }
  }
}
ShowCloseIconModifier.identity = Symbol('showCloseIcon');
class DragBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetDragBar(node);
    }
    else {
      GetUINativeModule().panel.setDragBar(node, this.value);
    }
  }
}
DragBarModifier.identity = Symbol('dragBar');
class ShowModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().panel.resetShow(node);
    }
    else {
      GetUINativeModule().panel.setShow(node, this.value);
    }
  }
}
ShowModifier.identity = Symbol('show');
// @ts-ignore
globalThis.Panel.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, NavBarPositionModifier, value);
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
    modifier(this._modifiers, ModeModifier, value);
    return this;
  }
  backButtonIcon(value) {
    modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, value);
    return this;
  }
  hideNavBar(value) {
    modifier(this._modifiers, HideNavBarModifier, isBoolean(value) ? value : false);
    return this;
  }
  title(value) {
    throw new Error('Method not implemented.');
  }
  subTitle(value) {
    modifier(this._modifiers, SubTitleModifier, value);
    return this;
  }
  hideTitleBar(value) {
    modifier(this._modifiers, NavigationHideTitleBarModifier, isBoolean(value) ? value : false);
    return this;
  }
  hideBackButton(value) {
    modifier(this._modifiers, HideBackButtonModifier, isBoolean(value) ? value : false);
    return this;
  }
  titleMode(value) {
    modifier(this._modifiers, TitleModeModifier, value);
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
    modifier(this._modifiers, HideToolBarModifier, isBoolean(value) ? value : false);
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
      GetUINativeModule().navigation.resetBackButtonIcon(node);
    }
    else {
      GetUINativeModule().navigation.setBackButtonIcon(node, this.value);
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
BackButtonIconModifier.identity = Symbol('backButtonIcon');
class NavBarWidthRangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetNavBarWidthRange(node);
    }
    else {
      GetUINativeModule().navigation.setNavBarWidthRange(node, this.value);
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
NavBarWidthRangeModifier.identity = Symbol('navBarWidthRange');
class MinContentWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetMinContentWidth(node);
    }
    else {
      GetUINativeModule().navigation.setMinContentWidth(node, this.value);
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
MinContentWidthModifier.identity = Symbol('minContentWidth');
class NavBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetNavBarWidth(node);
    }
    else {
      GetUINativeModule().navigation.setNavBarWidth(node, this.value);
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
NavBarWidthModifier.identity = Symbol('navBarWidth');
class NavBarPositionModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetNavBarPosition(node);
    }
    else {
      GetUINativeModule().navigation.setNavBarPosition(node, this.value);
    }
  }
}
NavBarPositionModifier.identity = Symbol('navBarPosition');
class ModeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetMode(node);
    }
    else {
      GetUINativeModule().navigation.setMode(node, this.value);
    }
  }
}
ModeModifier.identity = Symbol('mode');
class HideToolBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetHideToolBar(node);
    }
    else {
      GetUINativeModule().navigation.setHideToolBar(node, this.value);
    }
  }
}
HideToolBarModifier.identity = Symbol('hideToolBar');
class TitleModeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetTitleMode(node);
    }
    else {
      GetUINativeModule().navigation.setTitleMode(node, this.value);
    }
  }
}
TitleModeModifier.identity = Symbol('titleMode');
class HideBackButtonModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetHideBackButton(node);
    }
    else {
      GetUINativeModule().navigation.setHideBackButton(node, this.value);
    }
  }
}
HideBackButtonModifier.identity = Symbol('hideBackButton');
class SubTitleModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetSubTitle(node);
    }
    else {
      GetUINativeModule().navigation.setSubTitle(node, this.value);
    }
  }
}
SubTitleModifier.identity = Symbol('subTitle');
class NavigationHideTitleBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetHideTitleBar(node);
    }
    else {
      GetUINativeModule().navigation.setHideTitleBar(node, this.value);
    }
  }
}
NavigationHideTitleBarModifier.identity = Symbol('hideTitleBar');
class HideNavBarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigation.resetHideNavBar(node);
    }
    else {
      GetUINativeModule().navigation.setHideNavBar(node, this.value);
    }
  }
}
HideNavBarModifier.identity = Symbol('hideNavBar');
// @ts-ignore
globalThis.Navigation.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkNavigationComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
const NAV_ROUTE_MODE_RANGE = 2;
const NAV_ROUTE_MODE_DEFAULT = 0;
class ArkNavRouterComponent extends ArkComponent {
  constructor(nativePtr) {
    super(nativePtr);
  }
  onStateChange(callback) {
    throw new Error('Method not implemented.');
  }
  mode(mode) {
    if (isNumber(mode) && mode >= NAV_ROUTE_MODE_DEFAULT && mode <= NAV_ROUTE_MODE_RANGE) {
      modifier(this._modifiers, NavRouterModeModifier, mode);
    }
    else {
      modifier(this._modifiers, NavRouterModeModifier, NAV_ROUTE_MODE_DEFAULT);
    }
    return this;
  }
}
class NavRouterModeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navRouter.resetMode(node);
    }
    else {
      GetUINativeModule().navRouter.setMode(node, this.value);
    }
  }
}
NavRouterModeModifier.identity = Symbol('mode');
// @ts-ignore
globalThis.NavRouter.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, ActiveModifier, value);
    return this;
  }
  type(value) {
    modifier(this._modifiers, TypeModifier, value);
    return this;
  }
  target(value) {
    modifier(this._modifiers, TargetModifier, value);
    return this;
  }
  params(value) {
    modifier(this._modifiers, ParamsModifier, JSON.stringify(value));
    return this;
  }
}
class ParamsModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigator.resetParams(node);
    }
    else {
      GetUINativeModule().navigator.setParams(node, this.value);
    }
  }
}
ParamsModifier.identity = Symbol('params');
class TypeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigator.resetType(node);
    }
    else {
      GetUINativeModule().navigator.setType(node, this.value);
    }
  }
}
TypeModifier.identity = Symbol('type');
class ActiveModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigator.resetActive(node);
    }
    else {
      GetUINativeModule().navigator.setActive(node, this.value);
    }
  }
}
ActiveModifier.identity = Symbol('active');
class TargetModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().navigator.resetTarget(node);
    }
    else {
      GetUINativeModule().navigator.setTarget(node, this.value);
    }
  }
}
TargetModifier.identity = Symbol('target');
// @ts-ignore
globalThis.Navigator.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    if (typeof value === 'boolean') {
      modifier(this._modifiers, UsingPopupModifier, value);
    }
    else {
      modifier(this._modifiers, UsingPopupModifier, undefined);
    }
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
    if (typeof value !== 'number' && typeof value !== 'string') {
      modifier(this._modifiers, ItemSizeModifier, undefined);
    }
    else {
      modifier(this._modifiers, ItemSizeModifier, value);
    }
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
    if (typeof index === 'number') {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, index);
    }
    else {
      modifier(this._modifiers, AlphabetIndexerSelectedModifier, undefined);
    }
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().alphabetIndexer.resetPopupItemFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupItemFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetSelectedFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelectedFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetPopupFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetFont(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
      GetUINativeModule().alphabetIndexer.resetPopupItemBackgroundColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupItemBackgroundColor(node, this.value);
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
PopupItemBackgroundColorModifier.identity = Symbol('popupItemBackgroundColor');
class ColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setColor(node, this.value);
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
ColorModifier.identity = Symbol('alphabetColor');
class PopupColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupColor(node, this.value);
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
PopupColorModifier.identity = Symbol('popupColor');
class SelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelectedColor(node, this.value);
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
SelectedColorModifier.identity = Symbol('selectedColor');
class PopupBackgroundModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupBackground(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupBackground(node, this.value);
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
PopupBackgroundModifier.identity = Symbol('popupBackground');
class SelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelectedBackgroundColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelectedBackgroundColor(node, this.value);
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
SelectedBackgroundColorModifier.identity = Symbol('selectedBackgroundColor');
class PopupUnselectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupUnselectedColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupUnselectedColor(node, this.value);
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
PopupUnselectedColorModifier.identity = Symbol('popupUnselectedColor');
class PopupSelectedColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetPopupSelectedColor(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupSelectedColor(node, this.value);
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
PopupSelectedColorModifier.identity = Symbol('popupSelectedColor');
class AlignStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetAlignStyle(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setAlignStyle(node, this.value.indexerAlign, this.value.offset);
    }
  }
  checkObjectDiff() {
    let indexerAlignEQ = isBaseOrResourceEqual(this.stageValue.indexerAlign, this.value.indexerAlign);
    let offsetEQ = isBaseOrResourceEqual(this.stageValue.offset, this.value.offset);
    return !indexerAlignEQ || !offsetEQ;
  }
}
AlignStyleModifier.identity = Symbol('alignStyle');
class UsingPopupModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetUsingPopup(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setUsingPopup(node, this.value);
    }
  }
}
UsingPopupModifier.identity = Symbol('usingPopup');
class AlphabetIndexerSelectedModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetSelected(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setSelected(node, this.value);
    }
  }
}
AlphabetIndexerSelectedModifier.identity = Symbol('alphabetIndexerSelected');
class ItemSizeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().alphabetIndexer.resetItemSize(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setItemSize(node, this.value);
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
      GetUINativeModule().alphabetIndexer.resetPopupPosition(node);
    }
    else {
      GetUINativeModule().alphabetIndexer.setPopupPosition(node, this.value.x, this.value.y);
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
      GetUINativeModule().calendarPicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().calendarPicker.setTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k;
    if (!(((_b = (_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.font) === null || _b === void 0 ? void 0 : _b.weight) === ((_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.weight))) {
      return true;
    }
    else {
      return !isBaseOrResourceEqual((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.color, (_f = this.value) === null || _f === void 0 ? void 0 : _f.color) ||
        !isBaseOrResourceEqual((_h = (_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.font) === null || _h === void 0 ? void 0 : _h.size, (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.size);
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
      GetUINativeModule().calendarPicker.resetEdgeAlign(node);
    }
    else {
      GetUINativeModule().calendarPicker.setEdgeAlign(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.alignType) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.offset) === null || _d === void 0 ? void 0 : _d.dx) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.offset) === null || _g === void 0 ? void 0 : _g.dy) !== null && _h !== void 0 ? _h : undefined);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().dataPanel.resetDataPanelStrokeWidth(node);
    }
    else {
      GetUINativeModule().dataPanel.setDataPanelStrokeWidth(node, this.value);
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
DataPanelStrokeWidthModifier.identity = Symbol('dataPanelStrokeWidth');
class DataPanelCloseEffectModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().dataPanel.resetCloseEffect(node);
    }
    else {
      GetUINativeModule().dataPanel.setCloseEffect(node, this.value);
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
DataPanelCloseEffectModifier.identity = Symbol('dataPanelCloseEffect');
class DataPanelTrackBackgroundColorModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().dataPanel.resetDataPanelTrackBackgroundColor(node);
    }
    else {
      GetUINativeModule().dataPanel.setDataPanelTrackBackgroundColor(node, this.value);
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
DataPanelTrackBackgroundColorModifier.identity = Symbol('dataPanelTrackBackgroundColorModifier');
class DataPanelTrackShadowModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      if (this.value === null) {
        GetUINativeModule().dataPanel.setDataPanelTrackShadow(node, null);
        return;
      }
      GetUINativeModule().dataPanel.resetDataPanelTrackShadow(node);
    }
    else {
      GetUINativeModule().dataPanel.setDataPanelTrackShadow(node, this.value);
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
      GetUINativeModule().dataPanel.resetDataPanelValueColors(node);
    }
    else {
      GetUINativeModule().dataPanel.setDataPanelValueColors(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, DatePickerLunarModifier, isBoolean(value) ? value : false);
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
class DatePickerLunarModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().datePicker.resetLunar(node);
    }
    else {
      GetUINativeModule().datePicker.setLunar(node, this.value);
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
      GetUINativeModule().datePicker.resetTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
DatePickerTextStyleModifier.identity = Symbol('textStyle');
class DatePickerSelectedTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().datePicker.resetSelectedTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setSelectedTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
DatePickerSelectedTextStyleModifier.identity = Symbol('selectedTextStyle');
class DatePickerDisappearTextStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h, _j, _k, _l, _m, _o, _p;
    if (reset) {
      GetUINativeModule().datePicker.resetDisappearTextStyle(node);
    }
    else {
      GetUINativeModule().datePicker.setDisappearTextStyle(node, (_b = (_a = this.value) === null || _a === void 0 ? void 0 : _a.color) !== null && _b !== void 0 ? _b : undefined, (_e = (_d = (_c = this.value) === null || _c === void 0 ? void 0 : _c.font) === null || _d === void 0 ? void 0 : _d.size) !== null && _e !== void 0 ? _e : undefined, (_h = (_g = (_f = this.value) === null || _f === void 0 ? void 0 : _f.font) === null || _g === void 0 ? void 0 : _g.weight) !== null && _h !== void 0 ? _h : undefined, (_l = (_k = (_j = this.value) === null || _j === void 0 ? void 0 : _j.font) === null || _k === void 0 ? void 0 : _k.family) !== null && _l !== void 0 ? _l : undefined, (_p = (_o = (_m = this.value) === null || _m === void 0 ? void 0 : _m.font) === null || _o === void 0 ? void 0 : _o.style) !== null && _p !== void 0 ? _p : undefined);
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
DatePickerDisappearTextStyleModifier.identity = Symbol('disappearTextStyle');
//@ts-ignore
globalThis.DatePicker.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().formComponent.resetModuleName(node);
    }
    else {
      GetUINativeModule().formComponent.setModuleName(node, this.value);
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
      GetUINativeModule().formComponent.resetDimension(node);
    }
    else {
      GetUINativeModule().formComponent.setDimension(node, this.value);
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
      GetUINativeModule().formComponent.resetAllowUpdate(node);
    }
    else {
      GetUINativeModule().formComponent.setAllowUpdate(node, this.value);
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
      GetUINativeModule().formComponent.resetSize(node);
    }
    else {
      GetUINativeModule().formComponent.setSize(node, this.value.width, this.value.height);
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
      GetUINativeModule().formComponent.resetVisibility(node);
    }
    else {
      GetUINativeModule().formComponent.setVisibility(node, this.value);
    }
  }
}
FormComponentVisibilityModifier.identity = Symbol('formComponentVisibility');
// @ts-ignore
globalThis.FormComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().gauge.resetGaugeIndicator(node, this.value);
    }
    else {
      GetUINativeModule().gauge.setGaugeIndicator(node, this.value.icon, this.value.space);
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
      GetUINativeModule().gauge.resetGaugeColors(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeColors(node, this.value);
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
      GetUINativeModule().gauge.resetGaugeVaule(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeVaule(node, this.value);
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
GaugeVauleModifier.identity = Symbol('gaugeVaule');
class GaugeStartAngleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gauge.resetGaugeStartAngle(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeStartAngle(node, this.value);
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
GaugeStartAngleModifier.identity = Symbol('gaugeStartAngle');
class GaugeEndAngleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gauge.resetGaugeEndAngle(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeEndAngle(node, this.value);
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
GaugeEndAngleModifier.identity = Symbol('gaugeEndAngle');
class GaugeStrokeWidthModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gauge.resetGaugeStrokeWidth(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeStrokeWidth(node, this.value);
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
GaugeStrokeWidthModifier.identity = Symbol('gaugeStrokeWidth');
class GaugeTrackShadowModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gauge.resetGaugeTrackShadow(node);
    }
    else {
      GetUINativeModule().gauge.setGaugeTrackShadow(node, this.value, this.value.radius, this.value.offsetX, this.value.offsetY);
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
GaugeTrackShadowModifier.identity = Symbol('gaugeTrackShadow');
// @ts-ignore
globalThis.Gauge.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().marquee.resetFontColor(node);
    }
    else {
      GetUINativeModule().marquee.setFontColor(node, this.value);
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
MarqueeFontColorModifier.identity = Symbol('fontColor');
class MarqueeFontSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().marquee.resetFontSize(node);
    }
    else {
      GetUINativeModule().marquee.setFontSize(node, this.value);
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
MarqueeFontSizeModifier.identity = Symbol('fontSize');
class MarqueeAllowScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().marquee.resetAllowScale(node);
    }
    else {
      GetUINativeModule().marquee.setAllowScale(node, this.value);
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
      GetUINativeModule().marquee.resetFontWeight(node);
    }
    else {
      GetUINativeModule().marquee.setFontWeight(node, this.value);
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
      GetUINativeModule().marquee.resetFontFamily(node);
    }
    else {
      GetUINativeModule().marquee.setFontFamily(node, this.value);
    }
  }
}
MarqueeFontFamilyModifier.identity = Symbol('fontFamily');
// @ts-ignore
globalThis.Marquee.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().menu.resetMenuFontColor(node);
    }
    else {
      GetUINativeModule().menu.setMenuFontColor(node, this.value);
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
MenuFontColorModifier.identity = Symbol('fontColor');
class MenuFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      GetUINativeModule().menu.resetFont(node);
    }
    else {
      GetUINativeModule().menu.setFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
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
MenuFontModifier.identity = Symbol('font');
class RadiusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().menu.resetRadius(node);
    }
    else {
      if (isNumber(this.value) || isString(this.value) || isResource(this.value)) {
        GetUINativeModule().menu.setRadius(node, this.value, this.value, this.value, this.value);
      }
      else {
        GetUINativeModule().menu.setRadius(node, this.value.topLeft, this.value.topRight, this.value.bottomLeft, this.value.bottomRight);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().menuitem.resetMenuItemSelected(node);
    }
    else {
      GetUINativeModule().menuitem.setMenuItemSelected(node, this.value);
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
      GetUINativeModule().menuitem.resetLabelFontColor(node);
    }
    else {
      GetUINativeModule().menuitem.setLabelFontColor(node, this.value);
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
LabelFontColorModifier.identity = Symbol('labelfontColor');
class ContentFontColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().menuitem.resetContentFontColor(node);
    }
    else {
      GetUINativeModule().menuitem.setContentFontColor(node, this.value);
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
ContentFontColorModifier.identity = Symbol('contentfontColor');
class LabelFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      GetUINativeModule().menuitem.resetLabelFont(node);
    }
    else {
      GetUINativeModule().menuitem.setLabelFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.size === this.value.size &&
        this.stageValue.weight === this.value.weight &&
        this.stageValue.family === this.value.family &&
        this.stageValue.style === this.value.style);
    }
    else {
      return true;
    }
  }
}
LabelFontModifier.identity = Symbol('labelFont');
class ContentFontModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      GetUINativeModule().menuitem.resetContentFont(node);
    }
    else {
      GetUINativeModule().menuitem.setContentFont(node, this.value.size, this.value.weight, this.value.family, this.value.style);
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue.size === this.value.size &&
        this.stageValue.weight === this.value.weight &&
        this.stageValue.family === this.value.family &&
        this.stageValue.style === this.value.style);
    }
    else {
      return true;
    }
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkMenuItemGroupComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
class ArkPluginComponentComponent extends ArkComponent {
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
}
// @ts-ignore
globalThis.PluginComponent.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPluginComponentComponent(nativeNode);
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
}
class ProgressValueModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().progress.ResetProgressValue(node);
    }
    else {
      GetUINativeModule().progress.SetProgressValue(node, this.value);
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
      GetUINativeModule().progress.resetProgressColor(node);
    }
    else {
      GetUINativeModule().progress.setProgressColor(node, this.value);
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
      GetUINativeModule().progress.ResetProgressStyle(node);
    }
    else {
      let strokeWidth = this.value.strokeWidth;
      let scaleCount = this.value.scaleCount;
      let scaleWidth = this.value.scaleWidth;
      let enableSmoothEffect = this.value.enableSmoothEffect;
      let borderColor = this.value.borderColor;
      let borderWidth = this.value.borderWidth;
      let content = this.value.content;
      let fontSize = undefined;
      let fontWeight = undefined;
      let fontFamily = undefined;
      let fontStyle = undefined;
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
      GetUINativeModule().progress.SetProgressStyle(node, strokeWidth, scaleCount, scaleWidth, enableSmoothEffect, borderColor, borderWidth,
        content, fontSize, fontWeight, fontFamily, fontStyle, fontColor, enableScanEffect, showDefaultPercentage, shadow, status, strokeRadius);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ProgressStyleModifier.identity = Symbol('style');
// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().qrcode.resetQRColor(node);
    }
    else {
      GetUINativeModule().qrcode.setQRColor(node, this.value);
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
QRColorModifier.identity = Symbol('color');
class QRBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().qrcode.resetQRBackgroundColor(node);
    }
    else {
      GetUINativeModule().qrcode.setQRBackgroundColor(node, this.value);
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
QRBackgroundColorModifier.identity = Symbol('qrBackgroundColor');
class QRContentOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().qrcode.resetContentOpacity(node);
    }
    else {
      GetUINativeModule().qrcode.setContentOpacity(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, NextLabelModifier, value);
    return this;
  }
  status(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
class NextLabelModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().stepperItem.resetNextLabel(node);
    }
    else {
      GetUINativeModule().stepperItem.setNextLabel(node, this.value);
    }
  }
}
NextLabelModifier.identity = Symbol('NextLabel');
// @ts-ignore
globalThis.StepperItem.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().textClock.resetFormat(node);
    }
    else {
      GetUINativeModule().textClock.setFormat(node, this.value);
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
      GetUINativeModule().textClock.resetFontColor(node);
    }
    else {
      GetUINativeModule().textClock.setFontColor(node, this.value);
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
      GetUINativeModule().textClock.resetFontSize(node);
    }
    else {
      GetUINativeModule().textClock.setFontSize(node, this.value);
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
      GetUINativeModule().textClock.resetFontStyle(node);
    }
    else {
      GetUINativeModule().textClock.setFontStyle(node, this.value);
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
      GetUINativeModule().textClock.resetFontWeight(node);
    }
    else {
      GetUINativeModule().textClock.setFontWeight(node, this.value);
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
      GetUINativeModule().textClock.resetFontFamily(node);
    }
    else {
      GetUINativeModule().textClock.setFontFamily(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().textTimer.resetFontColor(node);
    }
    else {
      GetUINativeModule().textTimer.setFontColor(node, this.value);
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
      GetUINativeModule().textTimer.resetFontSize(node);
    }
    else {
      GetUINativeModule().textTimer.setFontSize(node, this.value);
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
      GetUINativeModule().textTimer.resetFontWeight(node);
    }
    else {
      GetUINativeModule().textTimer.setFontWeight(node, this.value);
    }
  }
}
TextTimerFontWeightModifier.identity = Symbol('fontWeight');
class TextTimerFontStyleModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().textTimer.resetFontStyle(node);
    }
    else {
      GetUINativeModule().textTimer.setFontStyle(node, this.value);
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
      GetUINativeModule().textTimer.resetFontFamily(node);
    }
    else {
      GetUINativeModule().textTimer.setFontFamily(node, this.value);
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
      GetUINativeModule().textTimer.resetFormat(node);
    }
    else {
      GetUINativeModule().textTimer.setFormat(node, this.value);
    }
  }
}
TextTimerFormatModifier.identity = Symbol('textTimerFormat');
// @ts-ignore
globalThis.TextTimer.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifierWithKey(this._modifiersWithKeys, BackgroundColorModifier.identity, BackgroundColorModifier, value);
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
    modifierWithKey(this._modifiersWithKeys, OpacityModifier.identity, OpacityModifier, value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkXComponentComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().gridItem.resetGridItemSelectable(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemSelectable(node, this.value);
    }
  }
}
GridItemSelectableModifier.identity = Symbol('gridItemSelectable');
class GridItemSelectedModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemSelected(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemSelected(node, this.value);
    }
  }
}
GridItemSelectedModifier.identity = Symbol('gridItemSelected');
class GridItemRowStartModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemRowStart(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemRowStart(node, this.value);
    }
  }
}
GridItemRowStartModifier.identity = Symbol('gridItemRowStart');
class GridItemRowEndModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemRowEnd(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemRowEnd(node, this.value);
    }
  }
}
GridItemRowEndModifier.identity = Symbol('gridItemRowEnd');
class GridItemColumnStartModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemColumnStart(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemColumnStart(node, this.value);
    }
  }
}
GridItemColumnStartModifier.identity = Symbol('gridItemColumnStart');
class GridItemColumnEndModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().gridItem.resetGridItemColumnEnd(node);
    }
    else {
      GetUINativeModule().gridItem.setGridItemColumnEnd(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().hyperlink.resetColor(node);
    }
    else {
      GetUINativeModule().hyperlink.setColor(node, this.value);
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
HyperlinkColorModifier.identity = Symbol('hyperlinkColor');
// @ts-ignore
globalThis.Hyperlink.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().list.resetEditMode(node);
    }
    else {
      GetUINativeModule().list.setEditMode(node, this.value);
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
      GetUINativeModule().list.resetMultiSelectable(node);
    }
    else {
      GetUINativeModule().list.setMultiSelectable(node, this.value);
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
      GetUINativeModule().list.resetAlignListItem(node);
    }
    else {
      GetUINativeModule().list.setAlignListItem(node, this.value);
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
      GetUINativeModule().list.resetScrollSnapAlign(node);
    }
    else {
      GetUINativeModule().list.setScrollSnapAlign(node, this.value);
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
      GetUINativeModule().list.resetDivider(node);
    } else {
      GetUINativeModule().list.setDivider(
        node,
        (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeWidth,
        (_b = this.value) === null || _b === void 0 ? void 0 : _b.color,
        (_c = this.value) === null || _c === void 0 ? void 0 : _c.startMargin,
        (_d = this.value) === null || _d === void 0 ? void 0 : _d.endMargin
      );
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
      GetUINativeModule().list.resetChainAnimationOptions(node);
    }
    else {
      GetUINativeModule().list.setChainAnimationOptions(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.minSpace, (_b = this.value) === null || _b === void 0 ? void 0 : _b.maxSpace, (_c = this.value) === null || _c === void 0 ? void 0 : _c.conductivity, (_d = this.value) === null || _d === void 0 ? void 0 : _d.intensity, (_e = this.value) === null || _e === void 0 ? void 0 : _e.edgeEffect, (_f = this.value) === null || _f === void 0 ? void 0 : _f.stiffness, (_g = this.value) === null || _g === void 0 ? void 0 : _g.damping);
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
      GetUINativeModule().list.resetChainAnimation(node);
    }
    else {
      GetUINativeModule().list.setChainAnimation(node, this.value);
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
      GetUINativeModule().list.resetCachedCount(node);
    }
    else {
      GetUINativeModule().list.setCachedCount(node, this.value);
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
      GetUINativeModule().list.resetEnableScrollInteraction(node);
    }
    else {
      GetUINativeModule().list.setEnableScrollInteraction(node, this.value);
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
      GetUINativeModule().list.resetSticky(node);
    }
    else {
      GetUINativeModule().list.setSticky(node, this.value);
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
      GetUINativeModule().list.resetListEdgeEffect(node);
    }
    else {
      GetUINativeModule().list.setListEdgeEffect(node, this.value.value, (_a = this.value.options) === null || _a === void 0 ? void 0 : _a.alwaysEnabled);
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
      GetUINativeModule().list.resetListDirection(node);
    }
    else {
      GetUINativeModule().list.setListDirection(node, this.value);
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
      GetUINativeModule().list.resetListFriction(node);
    }
    else {
      if (!isNumber(this.value) && !isResource(this.value)) {
        GetUINativeModule().list.resetListFriction(node);
      }
      else {
        GetUINativeModule().list.setListFriction(node, this.value);
      }
    }
  }
  checkObjectDiff() {
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.stageValue === this.value);
    }
    else {
      return true;
    }
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
      GetUINativeModule().list.resetListNestedScroll(node);
    }
    else {
      GetUINativeModule().list.setListNestedScroll(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.scrollForward,
        (_b = this.value) === null || _b === void 0 ? void 0 : _b.scrollBackward);
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
      GetUINativeModule().list.resetListScrollBar(node);
    }
    else {
      GetUINativeModule().list.setListScrollBar(node, this.value);
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
      GetUINativeModule().list.resetListLanes(node);
    }
    else {
      GetUINativeModule().list.setListLanes(node, this.value.lanesNum, this.value.minLength, this.value.maxLength, this.value.gutter);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().listItem.resetListItemSelected(node);
    }
    else {
      GetUINativeModule().listItem.setListItemSelected(node, this.value);
    }
  }
}
ListItemSelectedModifier.identity = Symbol('listItemSelected');
class ListItemSelectableModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().listItem.resetSelectable(node);
    }
    else {
      GetUINativeModule().listItem.setSelectable(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().listItemGroup.resetDivider(node);
    }
    else {
      GetUINativeModule().listItemGroup.setDivider(node, (_a = this.value) === null || _a === void 0 ? void 0 : _a.strokeWidth, (_b = this.value) === null || _b === void 0 ? void 0 : _b.color, (_c = this.value) === null || _c === void 0 ? void 0 : _c.startMargin, (_d = this.value) === null || _d === void 0 ? void 0 : _d.endMargin);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperIndexModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperIndexModifier, undefined);
    }
    return this;
  }
  autoPlay(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperAutoPlayModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperAutoPlayModifier, undefined);
    }
    return this;
  }
  interval(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperIntervalModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperIntervalModifier, undefined);
    }
    return this;
  }
  indicator(value) {
    if (typeof value === 'boolean' || typeof value === 'object') {
      modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SwiperIndicatorModifier.identity, SwiperIndicatorModifier, undefined);
    }
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
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperLoopModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperLoopModifier, undefined);
    }
    return this;
  }
  duration(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperDurationModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperDurationModifier, undefined);
    }
    return this;
  }
  vertical(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperVerticalModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperVerticalModifier, undefined);
    }
    return this;
  }
  itemSpace(value) {
    if (typeof value === 'number' || typeof value === 'string') {
      modifier(this._modifiers, SwiperItemSpaceModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperItemSpaceModifier, undefined);
    }
    return this;
  }
  displayMode(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperDisplayModeModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperDisplayModeModifier, undefined);
    }
    return this;
  }
  cachedCount(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperCachedCountModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperCachedCountModifier, undefined);
    }
    return this;
  }
  displayCount(value) {
    if (typeof value === 'number' || typeof value === 'string' || typeof value === 'object') {
      modifierWithKey(this._modifiersWithKeys, SwiperDisplayCountModifier.identity, SwiperDisplayCountModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SwiperDisplayCountModifier.identity, SwiperDisplayCountModifier, undefined);
    }
    return this;
  }
  effectMode(value) {
    if (typeof value === 'number') {
      modifier(this._modifiers, SwiperEffectModeModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperEffectModeModifier, undefined);
    }
    return this;
  }
  disableSwipe(value) {
    if (typeof value === 'boolean') {
      modifier(this._modifiers, SwiperDisableSwipeModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperDisableSwipeModifier, undefined);
    }
    return this;
  }
  curve(value) {
    if (typeof value === 'number' || typeof value === 'string') {
      modifier(this._modifiers, SwiperCurveModifier, value);
    }
    else {
      modifier(this._modifiers, SwiperCurveModifier, undefined);
    }
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
      GetUINativeModule().swiper.resetSwiperNextMargin(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperNextMargin(node, this.value);
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
SwiperNextMarginModifier.identity = Symbol('swiperNextMargin');
class SwiperPrevMarginModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperPrevMargin(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperPrevMargin(node, this.value);
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
SwiperPrevMarginModifier.identity = Symbol('swiperPrevMargin');
class SwiperDisplayCountModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisplayCount(node);
    }
    else {
      if (isNull(this.value)) {
        GetUINativeModule().swiper.resetSwiperDisplayCount(node);
      } else if (typeof this.value === 'object') {
        let minSize = this.value.minSize.toString();
        GetUINativeModule().swiper.setSwiperDisplayCount(node, minSize, typeof this.value);
      }
      else {
        GetUINativeModule().swiper.setSwiperDisplayCount(node, this.value, typeof this.value);
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
      GetUINativeModule().swiper.resetSwiperDisplayArrow(node);
    }
    else {
      if (!isNull(this.value.value) && typeof this.value === 'object') {
        let displayArrowValue = 3;
        let showBackground = undefined;
        let isSidebarMiddle = undefined;
        let backgroundSize = undefined;
        let backgroundColor = undefined;
        let arrowSize = undefined;
        let arrowColor = undefined;
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
        let isHoverShow = undefined;
        if (typeof this.value.isHoverShow === 'boolean') {
          isHoverShow = this.value.isHoverShow;
        }
        GetUINativeModule().swiper.setSwiperDisplayArrow(node, displayArrowValue, showBackground, isSidebarMiddle, backgroundSize, backgroundColor, arrowSize, arrowColor, isHoverShow);
      }
      else {
        GetUINativeModule().swiper.resetSwiperDisplayArrow(node);
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
      GetUINativeModule().swiper.resetSwiperIndicator(node);
    }
    else {
      let left = undefined;
      let top = undefined;
      let right = undefined;
      let bottom = undefined;
      let itemWidth = undefined;
      let itemHeight = undefined;
      let selectedItemWidth = undefined;
      let selectedItemHeight = undefined;
      let mask = undefined;
      let color = undefined;
      let selectedColor = undefined;
      let fontColor = undefined;
      let selectedFontColor = undefined;
      let digitFontSize = undefined;
      let digitFontWeight = undefined;
      let selectedDigitFontSize = undefined;
      let selectedDigitFontWeight = undefined;
      if (typeof this.value === 'boolean') {
        GetUINativeModule().swiper.setSwiperIndicator(node, 'boolean', this.value);
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
        GetUINativeModule().swiper.setSwiperIndicator(node, 'ArkDotIndicator', itemWidth, itemHeight, selectedItemWidth, selectedItemHeight, mask, color, selectedColor, left, top, right, bottom);
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
        GetUINativeModule().swiper.setSwiperIndicator(node, 'ArkDigitIndicator', fontColor, selectedFontColor, digitFontSize, digitFontWeight, selectedDigitFontSize, selectedDigitFontWeight, left, top, right, bottom);
      }
      else {
        GetUINativeModule().swiper.setSwiperIndicator(node, 'boolean', true);
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
      return (!isBaseOrResourceEqual(this.stageValue.itemWidth, this.value.itemWidth) ||
        !isBaseOrResourceEqual(this.stageValue.itemHeight, this.value.itemHeight) ||
        !isBaseOrResourceEqual(this.stageValue.selectedItemWidth, this.value.selectedItemWidth) ||
        !isBaseOrResourceEqual(this.stageValue.selectedItemHeight, this.value.selectedItemHeight) ||
        !isBaseOrResourceEqual(this.stageValue.mask, this.value.mask) ||
        !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
        !isBaseOrResourceEqual(this.stageValue.selectedColor, this.value.selectedColor));
    }
    else if (this.stageValue instanceof ArkDigitIndicator && this.value instanceof ArkDigitIndicator) {
      return (!isBaseOrResourceEqual(this.stageValue.fontColor, this.value.fontColor) ||
        !isBaseOrResourceEqual(this.stageValue.selectedFontColor, this.value.selectedFontColor) ||
        !isBaseOrResourceEqual(this.stageValue.digitFont.size, this.value.digitFont.size) ||
        !isBaseOrResourceEqual(this.stageValue.digitFont.weight, this.value.digitFont.weight) ||
        !isBaseOrResourceEqual(this.stageValue.selectedDigitFont.size, this.value.selectedDigitFont.size) ||
        !isBaseOrResourceEqual(this.stageValue.selectedDigitFont.weight, this.value.selectedDigitFont.weight));
    }
    else {
      return true;
    }
  }
}
SwiperIndicatorModifier.identity = Symbol('swiperIndicator');
class SwiperCurveModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperCurve(node);
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
      GetUINativeModule().swiper.setSwiperCurve(node, this.value);
    }
  }
}
SwiperCurveModifier.identity = Symbol('swiperCurve');
class SwiperDisableSwipeModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisableSwipe(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperDisableSwipe(node, this.value);
    }
  }
}
SwiperDisableSwipeModifier.identity = Symbol('swiperDisableSwipe');
class SwiperEffectModeModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperEffectMode(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperEffectMode(node, this.value);
    }
  }
}
SwiperEffectModeModifier.identity = Symbol('swiperEffectMode');
class SwiperCachedCountModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperCachedCount(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperCachedCount(node, this.value);
    }
  }
}
SwiperCachedCountModifier.identity = Symbol('swiperCachedCount');
class SwiperDisplayModeModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDisplayMode(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperDisplayMode(node, this.value);
    }
  }
}
SwiperDisplayModeModifier.identity = Symbol('swiperDisplayMode');
class SwiperItemSpaceModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperItemSpace(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperItemSpace(node, this.value);
    }
  }
}
SwiperItemSpaceModifier.identity = Symbol('swiperItemSpace');
class SwiperVerticalModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperVertical(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperVertical(node, this.value);
    }
  }
}
SwiperVerticalModifier.identity = Symbol('swiperVertical');
class SwiperLoopModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperLoop(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperLoop(node, this.value);
    }
  }
}
SwiperLoopModifier.identity = Symbol('swiperLoop');
class SwiperIntervalModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperInterval(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperInterval(node, this.value);
    }
  }
}
SwiperIntervalModifier.identity = Symbol('swiperInterval');
class SwiperAutoPlayModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperAutoPlay(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperAutoPlay(node, this.value);
    }
  }
}
SwiperAutoPlayModifier.identity = Symbol('swiperAutoPlay');
class SwiperIndexModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperIndex(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperIndex(node, this.value);
    }
  }
}
SwiperIndexModifier.identity = Symbol('swiperIndex');
class SwiperDurationModifier extends Modifier {
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().swiper.resetSwiperDuration(node);
    }
    else {
      GetUINativeModule().swiper.setSwiperDuration(node, this.value);
    }
  }
}
SwiperDurationModifier.identity = Symbol('swiperDuration');
// @ts-ignore
globalThis.Swiper.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
    modifier(this._modifiers, TabsVerticalModifier, value);
    return this;
  }
  barPosition(value) {
    modifier(this._modifiers, BarPositionModifier, value);
    return this;
  }
  scrollable(value) {
    modifier(this._modifiers, ScrollableModifier, value);
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
    modifier(this._modifiers, AnimationDurationModifier, value);
    return this;
  }
  onChange(event) {
    throw new Error('Method not implemented.');
  }
  onTabBarClick(event) {
    throw new Error('Method not implemented.');
  }
  fadingEdge(value) {
    modifier(this._modifiers, FadingEdgeModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, DividerModifier.identity, DividerModifier, value);
    return this;
  }
  barOverlap(value) {
    modifier(this._modifiers, BarOverlapModifier, value);
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
      GetUINativeModule().tabs.resetBarGridAlign(node);
    }
    else {
      GetUINativeModule().tabs.setBarGridAlign(node, this.value.sm, this.value.md, this.value.lg, this.value.gutter, this.value.margin);
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
      GetUINativeModule().tabs.resetDivider(node);
    }
    else {
      GetUINativeModule().tabs.setDivider(node, this.value.strokeWidth, this.value.color, this.value.startMargin, this.value.endMargin);
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
      GetUINativeModule().tabs.resetTabBarWidth(node);
    }
    else {
      GetUINativeModule().tabs.setTabBarWidth(node, this.value);
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
BarWidthModifier.identity = Symbol('barWidth');
class BarAdaptiveHeightModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetBarAdaptiveHeight(node);
    }
    else {
      GetUINativeModule().tabs.setBarAdaptiveHeight(node, this.value);
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
      GetUINativeModule().tabs.resetTabBarHeight(node);
    }
    else {
      GetUINativeModule().tabs.setTabBarHeight(node, this.value);
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
BarHeightModifier.identity = Symbol('barHeight');
class BarOverlapModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetBarOverlap(node);
    }
    else {
      GetUINativeModule().tabs.setBarOverlap(node, this.value);
    }
  }
}
BarOverlapModifier.identity = Symbol('barOverlap');
class TabsVerticalModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetIsVertical(node);
    }
    else {
      GetUINativeModule().tabs.setIsVertical(node, this.value);
    }
  }
}
TabsVerticalModifier.identity = Symbol('vertical');
class AnimationDurationModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetAnimationDuration(node);
    }
    else {
      GetUINativeModule().tabs.setAnimationDuration(node, this.value);
    }
  }
}
AnimationDurationModifier.identity = Symbol('animationduration');
class ScrollableModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetScrollable(node);
    }
    else {
      GetUINativeModule().tabs.setScrollable(node, this.value);
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
      GetUINativeModule().tabs.resetTabBarMode(node);
    }
    else {
      GetUINativeModule().tabs.setTabBarMode(node, this.value.barMode, (_a = this.value.options) === null || _a === void 0 ? void 0 : _a.margin, (_b = this.value.options) === null || _b === void 0 ? void 0 : _b.nonScrollableLayoutStyle);
    }
  }
  checkObjectDiff() {
    let _a, _b, _c, _d;
    if (isResource(this.stageValue) && isResource(this.value)) {
      return !isResourceEqual(this.stageValue, this.value);
    }
    else if (!isResource(this.stageValue) && !isResource(this.value)) {
      return !(this.value.barMode === this.stageValue.barMode &&
        ((_a = this.value.options) === null || _a === void 0 ? void 0 : _a.margin) === ((_b = this.stageValue.options) === null || _b === void 0 ? void 0 : _b.margin) &&
        ((_c = this.value.options) === null || _c === void 0 ? void 0 : _c.nonScrollableLayoutStyle) === ((_d = this.stageValue.options) === null || _d === void 0 ? void 0 : _d.nonScrollableLayoutStyle));
    }
    else {
      return true;
    }
  }
}
TabBarModeModifier.identity = Symbol('tabsbarMode');
class BarPositionModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetTabBarPosition(node);
    }
    else {
      GetUINativeModule().tabs.setTabBarPosition(node, this.value);
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
      GetUINativeModule().tabs.resetHideTitleBar(node);
    }
    else {
      GetUINativeModule().tabs.setHideTitleBar(node, this.value);
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
      GetUINativeModule().tabs.resetBarBackgroundColor(node);
    }
    else {
      GetUINativeModule().tabs.setBarBackgroundColor(node, this.value);
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
BarBackgroundColorModifier.identity = Symbol('barbackgroundcolor');
class FadingEdgeModifier extends Modifier {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().tabs.resetFadingEdge(node);
    }
    else {
      GetUINativeModule().tabs.setFadingEdge(node, this.value);
    }
  }
}
FadingEdgeModifier.identity = Symbol('fadingedge');
// @ts-ignore
globalThis.Tabs.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().waterFlow.resetItemConstraintSize(node);
    }
    else {
      GetUINativeModule().waterFlow.setItemConstraintSize(node, this.value.minWidth, this.value.maxWidth, this.value.minHeight, this.value.maxHeight);
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
      GetUINativeModule().waterFlow.resetColumnsTemplate(node);
    }
    else {
      GetUINativeModule().waterFlow.setColumnsTemplate(node, this.value);
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
      GetUINativeModule().waterFlow.resetRowsTemplate(node);
    }
    else {
      GetUINativeModule().waterFlow.setRowsTemplate(node, this.value);
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
      GetUINativeModule().waterFlow.resetEnableScrollInteraction(node);
    }
    else {
      GetUINativeModule().waterFlow.setEnableScrollInteraction(node, this.value);
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
      GetUINativeModule().waterFlow.resetRowsGap(node);
    }
    else {
      GetUINativeModule().waterFlow.setRowsGap(node, this.value);
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
RowsGapModifier.identity = Symbol('rowsGap');
class ColumnsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().waterFlow.resetColumnsGap(node);
    }
    else {
      GetUINativeModule().waterFlow.setColumnsGap(node, this.value);
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
ColumnsGapModifier.identity = Symbol('columnsGap');
class LayoutDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().waterFlow.resetLayoutDirection(node);
    }
    else {
      GetUINativeModule().waterFlow.setLayoutDirection(node, this.value);
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
      GetUINativeModule().waterFlow.resetNestedScroll(node);
    }
    else {
      GetUINativeModule().waterFlow.setNestedScroll(node, this.value.scrollForward, this.value.scrollBackward);
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
      GetUINativeModule().waterFlow.resetFriction(node);
    }
    else {
      GetUINativeModule().waterFlow.setFriction(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkWaterFlowComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
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
    modifierWithKey(this._modifiersWithKeys, Symbol('strokeDashArray'), StrokeDashArrayModifier, value);
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
      GetUINativeModule().commonShape.resetStrokeDashArray(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeDashArray(node, this.value);
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
StrokeDashArrayModifier.identity = Symbol('strokeDashArray');
class StrokeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetStroke(node);
    }
    else {
      GetUINativeModule().commonShape.setStroke(node, this.value);
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
StrokeModifier.identity = Symbol('stroke');
class FillModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetFill(node);
    }
    else {
      GetUINativeModule().commonShape.setFill(node, this.value);
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
FillModifier.identity = Symbol('fill');
class StrokeDashOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetStrokeDashOffset(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeDashOffset(node, this.value);
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
StrokeDashOffsetModifier.identity = Symbol('strokeDashOffset');
class StrokeLineCapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetStrokeLineCap(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeLineCap(node, this.value);
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
      GetUINativeModule().commonShape.resetStrokeLineJoin(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeLineJoin(node, this.value);
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
      GetUINativeModule().commonShape.resetStrokeMiterLimit(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeMiterLimit(node, this.value);
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
      GetUINativeModule().commonShape.resetFillOpacity(node);
    }
    else {
      GetUINativeModule().commonShape.setFillOpacity(node, this.value);
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
FillOpacityModifier.identity = Symbol('FillOpacity');
class StrokeOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetStrokeOpacity(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeOpacity(node, this.value);
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
StrokeOpacityModifier.identity = Symbol('StrokeOpacity');
class StrokeWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().commonShape.resetStrokeWidth(node);
    }
    else {
      GetUINativeModule().commonShape.setStrokeWidth(node, this.value);
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
      GetUINativeModule().commonShape.resetAntiAlias(node);
    }
    else {
      GetUINativeModule().commonShape.setAntiAlias(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().line.resetStartPoint(node);
    }
    else {
      GetUINativeModule().line.setStartPoint(node, this.value);
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
      GetUINativeModule().line.resetEndPoint(node);
    }
    else {
      GetUINativeModule().line.setEndPoint(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().polyline.resetPoints(node);
    }
    else {
      GetUINativeModule().polyline.setPoints(node, xPoint, yPoint);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPolylineComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/// <reference path='./import.ts' />
class ArkPolygonComponent extends ArkCommonShapeComponent {
  points(value) {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Polygon.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
      GetUINativeModule().path.resetPathCommands(node);
    }
    else {
      GetUINativeModule().path.setPathCommands(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkPathComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
class RectRadiusWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().rect.resetRectRadiusWidth(node);
    }
    else {
      GetUINativeModule().rect.setRectRadiusWidth(node, this.value);
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
      GetUINativeModule().rect.resetRectRadiusHeight(node);
    }
    else {
      GetUINativeModule().rect.setRectRadiusHeight(node, this.value);
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
      GetUINativeModule().rect.resetRectRadius(node);
    }
    else {
      GetUINativeModule().rect.setRectRadius(node, this.value);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRectComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/// <reference path='./import.ts' />
/// <reference path='./ArkCommonShape.ts' />
class ShapeViewPortModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      GetUINativeModule().shape.resetShapeViewPort(node);
    }
    else {
      GetUINativeModule().shape.setShapeViewPort(node, this.value.x, this.value.y, this.value.width, this.value.height);
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
      GetUINativeModule().shape.resetShapeMesh(node);
    }
    else {
      GetUINativeModule().shape.setShapeMesh(node, this.value.value, this.value.column, this.value.row);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkGridContainerComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

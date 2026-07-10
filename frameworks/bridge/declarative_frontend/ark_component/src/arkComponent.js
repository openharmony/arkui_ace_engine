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

var CommonGestureType;
(function (CommonGestureType) {
    CommonGestureType[CommonGestureType['TAP_GESTURE'] = 0] = 'TAP_GESTURE';
    CommonGestureType[CommonGestureType['LONG_PRESS_GESTURE'] = 1] = 'LONG_PRESS_GESTURE';
    CommonGestureType[CommonGestureType['PAN_GESTURE'] = 2] = 'PAN_GESTURE';
    CommonGestureType[CommonGestureType['SWIPE_GESTURE'] = 3] = 'SWIPE_GESTURE';
    CommonGestureType[CommonGestureType['PINCH_GESTURE'] = 4] = 'PINCH_GESTURE';
    CommonGestureType[CommonGestureType['ROTATION_GESTURE'] = 5] = 'ROTATION_GESTURE';
    CommonGestureType[CommonGestureType['GESTURE_GROUP'] = 6] = 'GESTURE_GROUP';
})(CommonGestureType || (CommonGestureType = {}));

class GestureHandler {
  constructor(gestureType) {
    this.gestureType = gestureType;
  }
}

class TapGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.TAP_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.count = options.count;
      this.distanceThreshold = options.distanceThreshold;
      this.limitFingerCount = options.isFingerCountLimited;
    }
  }
  onAction(event) {
    this.onActionCallback = event;
    return this;
  }
  tag(tag) {
    this.gestureTag = tag;
    return this;
  }
  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class LongPressGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.LONG_PRESS_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.repeat = options.repeat;
      this.duration = options.duration;
      this.allowableMovement = options.allowableMovement;
      this.limitFingerCount = options.isFingerCountLimited;
    }
  }

  onAction(event) {
    this.onActionCallback = event;
    return this;
  }

  onActionEnd(event) {
    this.onActionEndCallback = event;
    return this;
  }

  onActionCancel(event) {
    this.onActionCancelCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }

  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class PanGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.PAN_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.direction = options.direction;
      this.distance = options.distance;
      this.limitFingerCount = options.isFingerCountLimited;
      if (options.distanceMap !== undefined && options.distanceMap !== null) {
          this.distanceMap = new Map();
          options.distanceMap.forEach((value, key) => {
              this.distanceMap.set(key, value);
          });
      }
    }
  }

  onActionStart(event) {
    this.onActionStartCallback = event;
    return this;
  }

  onActionUpdate(event) {
    this.onActionUpdateCallback = event;
    return this;
  }

  onActionEnd(event) {
    this.onActionEndCallback = event;
    return this;
  }

  onActionCancel(event) {
    this.onActionCancelCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }

  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class SwipeGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.SWIPE_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.direction = options.direction;
      this.speed = options.speed;
      this.limitFingerCount = options.isFingerCountLimited;
    }
  }

  onAction(event) {
    this.onActionCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }

  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class PinchGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.PINCH_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.distance = options.distance;
      this.limitFingerCount = options.isFingerCountLimited;
    }
  }

  onActionStart(event) {
    this.onActionStartCallback = event;
    return this;
  }

  onActionUpdate(event) {
    this.onActionUpdateCallback = event;
    return this;
  }

  onActionEnd(event) {
    this.onActionEndCallback = event;
    return this;
  }

  onActionCancel(event) {
    this.onActionCancelCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }

  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class RotationGestureHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.ROTATION_GESTURE);
    if (options !== undefined && options !== null) {
      this.fingers = options.fingers;
      this.angle = options.angle;
      this.limitFingerCount = options.isFingerCountLimited;
    }
  }

  onActionStart(event) {
    this.onActionStartCallback = event;
    return this;
  }

  onActionUpdate(event) {
    this.onActionUpdateCallback = event;
    return this;
  }

  onActionEnd(event) {
    this.onActionEndCallback = event;
    return this;
  }

  onActionCancel(event) {
    this.onActionCancelCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }

  allowedTypes(types) {
    this.allowedTypes = types;
    return this;
  }
}

class GestureGroupHandler extends GestureHandler {
  constructor(options) {
    super(CommonGestureType.GESTURE_GROUP);
    if (options !== undefined && options !== null) {
      this.mode = options.mode;
      this.gestures = options.gestures;
    }
  }

  onCancel(event) {
    this.onCancelCallback = event;
    return this;
  }

  tag(tag) {
    this.gestureTag = tag;
    return this;
  }
}

function valueToArkBorder(value){
  let borderValue = new ArkBorder();
  if (isUndefined(value)) {
    borderValue = undefined;
  }

  if (!isUndefined(value?.width) && value?.width !== null) {
    if (isNumber(value.width) || isString(value.width) || isResource(value.width)) {
      borderValue.arkWidth.left = value.width;
      borderValue.arkWidth.right = value.width;
      borderValue.arkWidth.top = value.width;
      borderValue.arkWidth.bottom = value.width;
    } else {
      borderValue.arkWidth.start = value.width.start;
      borderValue.arkWidth.end = value.width.end;
      borderValue.arkWidth.left = value.width.left;
      borderValue.arkWidth.right = value.width.right;
      borderValue.arkWidth.top = value.width.top;
      borderValue.arkWidth.bottom = value.width.bottom;
    }
  }
  if (!isUndefined(value?.color) && value?.color !== null) {
    if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
      borderValue.arkColor.leftColor = value.color;
      borderValue.arkColor.rightColor = value.color;
      borderValue.arkColor.topColor = value.color;
      borderValue.arkColor.bottomColor = value.color;
    } else {
      borderValue.arkColor.start = (value.color).start;
      borderValue.arkColor.end = (value.color).end;
      borderValue.arkColor.leftColor = (value.color).left;
      borderValue.arkColor.rightColor = (value.color).right;
      borderValue.arkColor.topColor = (value.color).top;
      borderValue.arkColor.bottomColor = (value.color).bottom;
    }
  }
  if (!isUndefined(value?.radius) && value?.radius !== null) {
    if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
      borderValue.arkRadius.topLeft = value.radius;
      borderValue.arkRadius.topRight = value.radius;
      borderValue.arkRadius.bottomLeft = value.radius;
      borderValue.arkRadius.bottomRight = value.radius;
    } else {
      borderValue.arkRadius.topStart = value.radius?.topStart;
      borderValue.arkRadius.topEnd = value.radius?.topEnd;
      borderValue.arkRadius.bottomStart = value.radius?.bottomStart;
      borderValue.arkRadius.bottomEnd = value.radius?.bottomEnd;
      borderValue.arkRadius.topLeft = value.radius?.topLeft;
      borderValue.arkRadius.topRight = value.radius?.topRight;
      borderValue.arkRadius.bottomLeft = value.radius?.bottomLeft;
      borderValue.arkRadius.bottomRight = value.radius?.bottomRight;
    }
  }
  if (!isUndefined(value?.style) && value?.style !== null) {
    let arkBorderStyle = new ArkBorderStyle();
    if (arkBorderStyle.parseBorderStyle(value.style)) {
      if (!isUndefined(arkBorderStyle.style)) {
        borderValue.arkStyle.top = arkBorderStyle.style;
        borderValue.arkStyle.left = arkBorderStyle.style;
        borderValue.arkStyle.bottom = arkBorderStyle.style;
        borderValue.arkStyle.right = arkBorderStyle.style;
      } else {
        borderValue.arkStyle.top = arkBorderStyle.top;
        borderValue.arkStyle.left = arkBorderStyle.left;
        borderValue.arkStyle.bottom = arkBorderStyle.bottom;
        borderValue.arkStyle.right = arkBorderStyle.right;
      }
    }
  }
  if (!isUndefined(value === null || value === void 0 ? void 0 : value.dashGap) &&
    (value === null || value === void 0 ? void 0 : value.dashGap) !== null) {
    if (isNumber(value.dashGap) || isString(value.dashGap) || isResource(value.dashGap) ||
      isObject(value.dashGap) && isNumber(value.dashGap.value)) {
      borderValue.arkDashGap.left = value.dashGap;
      borderValue.arkDashGap.right = value.dashGap;
      borderValue.arkDashGap.top = value.dashGap;
      borderValue.arkDashGap.bottom = value.dashGap;
    } else {
      borderValue.arkDashGap.left = value.dashGap.left;
      borderValue.arkDashGap.right = value.dashGap.right;
      borderValue.arkDashGap.top = value.dashGap.top;
      borderValue.arkDashGap.bottom = value.dashGap.bottom;
      borderValue.arkDashGap.start = value.dashGap.start;
      borderValue.arkDashGap.end = value.dashGap.end;
    }
  }
  if (!isUndefined(value === null || value === void 0 ? void 0 : value.dashWidth) &&
    (value === null || value === void 0 ? void 0 : value.dashWidth) !== null) {
    if (isNumber(value.dashWidth) || isString(value.dashWidth) || isResource(value.dashWidth) ||
      isObject(value.dashWidth) && isNumber(value.dashWidth.value)) {
      borderValue.arkDashWidth.left = value.dashWidth;
      borderValue.arkDashWidth.right = value.dashWidth;
      borderValue.arkDashWidth.top = value.dashWidth;
      borderValue.arkDashWidth.bottom = value.dashWidth;
    } else {
      borderValue.arkDashWidth.left = value.dashWidth.left;
      borderValue.arkDashWidth.right = value.dashWidth.right;
      borderValue.arkDashWidth.top = value.dashWidth.top;
      borderValue.arkDashWidth.bottom = value.dashWidth.bottom;
      borderValue.arkDashWidth.start = value.dashWidth.start;
      borderValue.arkDashWidth.end = value.dashWidth.end;
    }
  }
  return borderValue;
}

globalThis.applySymbolGlyphModifierToNode = function (modifier, nodePtr) {
  getUINativeModule().loadNativeModule('SymbolGlyph');
  let module = globalThis.requireNapi('arkui.components.arksymbolglyph');
  let component = module.createComponent(nodePtr);
  applyUIAttributes(modifier, nodePtr, component);
  component.applyModifierPatch();
};

globalThis.applyImageModifierToNode = function (modifier, nodePtr) {
  let component = new ArkImageComponent(nodePtr);
  applyUIAttributes(modifier, nodePtr, component);
  component.applyModifierPatch();
};

globalThis.applyTextModifierToNode = function (modifier, nodePtr) {
  let component = new ArkTextComponent(nodePtr);
  applyUIAttributes(modifier, nodePtr, component);
  component.applyModifierPatch();
};

globalThis.applyCommonModifierToNode = function (modifier, nodePtr) {
  let component = new ArkComponent(nodePtr);
  applyUIAttributes(modifier, nodePtr, component);
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

class ColumnSpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().column.resetSpace(node);
    }
    else {
      getUINativeModule().column.setSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnSpaceModifier.identity = Symbol('columnSpace');

class ColumnPointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
ColumnPointLightModifier.identity = Symbol('columnPointLight');

class CommonPointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
CommonPointLightModifier.identity = Symbol('commonPointLight');

class ColumnReverseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().column.resetReverse(node);
    } else {
      getUINativeModule().column.setReverse(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ColumnReverseModifier.identity = Symbol('columnReverse');

class ArkColumnComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ColumnSpaceModifier.identity, ColumnSpaceModifier, value[0].space);
    }
    return this
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
    modifierWithKey(this._modifiersWithKeys, ColumnPointLightModifier.identity, ColumnPointLightModifier, value);
    return this;
  }
  reverse(value) {
    modifierWithKey(this._modifiersWithKeys, ColumnReverseModifier.identity, ColumnReverseModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Column !== undefined) {
  globalThis.Column.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkColumnComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ColumnModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class FlexInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().flex.resetFlexInitialize(node);
    } else {
      getUINativeModule().flex.setFlexInitialize(node, this.value.direction, this.value.wrap,
        this.value.justifyContent, this.value.alignItems, this.value.alignContent, this.value?.space?.main,
        this.value?.space?.cross);
    }
  }
}
FlexInitializeModifier.identity = Symbol('flexInitialize');
class FlexPointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
FlexPointLightModifier.identity = Symbol('flexPointLight');
class ArkFlexComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  pointLight(value) {
    modifierWithKey(this._modifiersWithKeys, FlexPointLightModifier.identity, FlexPointLightModifier, value);
    return this;
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, FlexInitializeModifier.identity, FlexInitializeModifier, value[0]);
    }
    return this;
  }
}
// @ts-ignore
if (globalThis.Flex !== undefined) {
  globalThis.Flex.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFlexComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.FlexModifier(nativePtr, classType);
    });
  };
}

class ClipContentModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
          getUINativeModule().scrollable.resetContentClip(node);
      } else {
          getUINativeModule().scrollable.setContentClip(node, this.value);
      }
  }
}
ClipContentModifier.identity = Symbol('clipContent');

class ScrollableFadingEdgeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetFadingEdge(node);
    }
    else {
      getUINativeModule().scrollable.setFadingEdge(node, this.value.value, this.value.options?.fadingEdgeLength);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}
ScrollableFadingEdgeModifier.identity = Symbol('scrollableFadingEdge');
class EdgeEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b;
    if (reset) {
      getUINativeModule().scrollable.resetEdgeEffect(node);
    }
    else {
      getUINativeModule().scrollable.setEdgeEffect(node, this.value.value, (_a = this.value.options) === null || _a ===
        void 0 ? void 0 : _a.alwaysEnabled, (_b = this.value.options) === null ||
          _b === void 0 ? void 0 : _b.effectEdge);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}
EdgeEffectModifier.identity = Symbol('edgeEffect');

class OnReachStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnReachStart(node);
    } else {
      getUINativeModule().scrollable.setOnReachStart(node, this.value);
    }
  }
}
OnReachStartModifier.identity = Symbol('onReachStart');

class OnReachEndModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnReachEnd(node);
    } else {
      getUINativeModule().scrollable.setOnReachEnd(node, this.value);
    }
  }
}
OnReachStartModifier.identity = Symbol('onReachEnd');

class FlingSpeedLimitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetFlingSpeedLimit(node);
    }
    else {
      getUINativeModule().scrollable.setFlingSpeedLimit(node, this.value);
    }
  }
}
FlingSpeedLimitModifier.identity = Symbol('flingSpeedLimit');

class BackToTopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetBackToTop(node);
    }
    else {
      getUINativeModule().scrollable.setBackToTop(node, this.value);
    }
  }
}
BackToTopModifier.identity = Symbol('backToTop');

class ScrollBarHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetScrollBarHeight(node);
    }
    else {
      getUINativeModule().scrollable.setScrollBarHeight(node, this.value);
    }
  }
}
ScrollBarHeightModifier.identity = Symbol('scrollBarHeight');

class EnableScrollWithMouseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetEnableScrollWithMouse(node);
    }
    else {
      getUINativeModule().scrollable.setEnableScrollWithMouse(node, this.value);
    }
  }
}
EnableScrollWithMouseModifier.identity = Symbol('enableScrollWithMouse');

class ScrollBarMarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetScrollBarMargin(node);
    } else {
      getUINativeModule().scrollable.setScrollBarMargin(node, this.value.start, this.value.end);
    }
  }
}
ScrollBarMarginModifier.identity = Symbol('scrollBarMargin');

class AutoAdjustScrollBarMarginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetAutoAdjustScrollBarMargin(node);
    } else {
      getUINativeModule().scrollable.setAutoAdjustScrollBarMargin(node, this.value);
    }
  }
}
AutoAdjustScrollBarMarginModifier.identity = Symbol('autoAdjustScrollBarMargin');

class OnWillStopDraggingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnWillStopDragging(node);
    } else {
      getUINativeModule().scrollable.setOnWillStopDragging(node, this.value);
    }
  }
}
OnWillStopDraggingModifier.identity = Symbol('onWillStopDragging');

class OnWillStartDraggingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnWillStartDragging(node);
    } else {
      getUINativeModule().scrollable.setOnWillStartDragging(node, this.value);
    }
  }
}
OnWillStartDraggingModifier.identity = Symbol('onWillStartDragging');

class OnDidStopDraggingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnDidStopDragging(node);
    } else {
      getUINativeModule().scrollable.setOnDidStopDragging(node, this.value);
    }
  }
}
OnDidStopDraggingModifier.identity = Symbol('onDidStopDragging');

class OnWillStartFlingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnWillStartFling(node);
    } else {
      getUINativeModule().scrollable.setOnWillStartFling(node, this.value);
    }
  }
}
OnWillStartFlingModifier.identity = Symbol('onWillStartFling');

class OnDidStopFlingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnDidStopFling(node);
    } else {
      getUINativeModule().scrollable.setOnDidStopFling(node, this.value);
    }
  }
}
OnDidStopFlingModifier.identity = Symbol('onDidStopFling');

class ContentStartOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetContentStartOffset(node);
    }
    else {
      getUINativeModule().scrollable.setContentStartOffset(node, this.value);
    }
  }
}
ContentStartOffsetModifier.identity = Symbol('contentStartOffset');

class ContentEndOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetContentEndOffset(node);
    }
    else {
      getUINativeModule().scrollable.setContentEndOffset(node, this.value);
    }
  }
}
ContentEndOffsetModifier.identity = Symbol('contentEndOffset');

class ArkScrollable extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  clipContent(clip) {
    modifierWithKey(this._modifiersWithKeys, ClipContentModifier.identity, ClipContentModifier, clip);
    return this;
  }
  edgeEffect(value, options) {
    let effect = new ArkEdgeEffect();
    effect.value = value;
    effect.options = options;
    modifierWithKey(this._modifiersWithKeys, EdgeEffectModifier.identity, EdgeEffectModifier, effect);
    return this;
  }
  fadingEdge(value, options) {
    let fadingEdge = new ArkFadingEdge();
    fadingEdge.value = value;
    fadingEdge.options = options;
    modifierWithKey(this._modifiersWithKeys, ScrollableFadingEdgeModifier.identity, ScrollableFadingEdgeModifier, fadingEdge);
    return this;
  }
  onReachStart(event) {
    modifierWithKey(this._modifiersWithKeys, OnReachStartModifier.identity, OnReachStartModifier, event);
    return this;
  }

  onReachEnd(event) {
    modifierWithKey(this._modifiersWithKeys, OnReachEndModifier.identity, OnReachEndModifier, event);
    return this;
  }

  flingSpeedLimit(value) {
    modifierWithKey(this._modifiersWithKeys, FlingSpeedLimitModifier.identity, FlingSpeedLimitModifier, value);
    return this;
  }
  backToTop(value) {
    modifierWithKey(this._modifiersWithKeys, BackToTopModifier.identity, BackToTopModifier, value);
    return this;
  }
  scrollBarHeight(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollBarHeightModifier.identity, ScrollBarHeightModifier, value);
    return this;
  }
  enableScrollWithMouse(value) {
    modifierWithKey(this._modifiersWithKeys, EnableScrollWithMouseModifier.identity, EnableScrollWithMouseModifier, value);
    return this;
  }
  scrollBarMargin(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollBarMarginModifier.identity, ScrollBarMarginModifier, value);
    return this;
  }
  autoAdjustScrollBarMargin(value) {
    modifierWithKey(this._modifiersWithKeys, AutoAdjustScrollBarMarginModifier.identity, AutoAdjustScrollBarMarginModifier, value);
    return this;
  }
  onWillStopDragging(value) {
    modifierWithKey(this._modifiersWithKeys, OnWillStopDraggingModifier.identity, OnWillStopDraggingModifier, value);
    return this;
  }
  onWillStartDragging(value) {
    modifierWithKey(this._modifiersWithKeys, OnWillStartDraggingModifier.identity, OnWillStartDraggingModifier, value);
    return this;
  }
  onDidStopDragging(value) {
    modifierWithKey(this._modifiersWithKeys, OnDidStopDraggingModifier.identity, OnDidStopDraggingModifier, value);
    return this;
  }
  onWillStartFling(value) {
    modifierWithKey(this._modifiersWithKeys, OnWillStartFlingModifier.identity, OnWillStartFlingModifier, value);
    return this;
  }
  onDidStopFling(value) {
    modifierWithKey(this._modifiersWithKeys, OnDidStopFlingModifier.identity, OnDidStopFlingModifier, value);
    return this;
  }
  contentStartOffset(value) {
    modifierWithKey(this._modifiersWithKeys, ContentStartOffsetModifier.identity, ContentStartOffsetModifier, value);
    return this;
  }
  contentEndOffset(value) {
    modifierWithKey(this._modifiersWithKeys, ContentEndOffsetModifier.identity, ContentEndOffsetModifier, value);
    return this;
  }
}

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
class ImageMatrixModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetImageMatrix(node);
    } else {
      getUINativeModule().image.setImageMatrix(node, this.value.matrix4x4);
    }
  }
  checkObjectDiff() {
    return !deepCompareArrays(this.stageValue.matrix4x4, this.value.matrix4x4);
  }
}
ImageMatrixModifier.identity = Symbol('imageMatrix');
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
        let keys = Object.keys(this.value);
        if (keys.indexOf('topStart') >= 0 || keys.indexOf('topEnd') >= 0 ||
          keys.indexOf('bottomStart') >= 0 || keys.indexOf('bottomEnd') >= 0) {
          let localizedBorderRadius = this.value;
          getUINativeModule().image.setBorderRadius(node, localizedBorderRadius.topStart,
            localizedBorderRadius.topEnd, localizedBorderRadius.bottomStart, localizedBorderRadius.bottomEnd);
        }
        else {
          let borderRadius = this.value;
          getUINativeModule().image.setBorderRadius(node, borderRadius.topLeft, borderRadius.topRight,
            borderRadius.bottomLeft, borderRadius.bottomRight);
        }
      }
    }
  }
  checkObjectDiff() {
    if (!isResource(this.stageValue) && !isResource(this.value)) {
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
class ImageBorderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetImageBorder(node);
    } else {
      let widthLeft;
      let widthRight;
      let widthTop;
      let widthBottom;
      if (!isUndefined(this.value.width) && this.value.width != null) {
        if (isNumber(this.value.width) || isString(this.value.width) || isResource(this.value.width)) {
          widthLeft = this.value.width;
          widthRight = this.value.width;
          widthTop = this.value.width;
          widthBottom = this.value.width;
        } else {
          widthLeft = this.value.width.left;
          widthRight = this.value.width.right;
          widthTop = this.value.width.top;
          widthBottom = this.value.width.bottom;
        }
      }
      let leftColor;
      let rightColor;
      let topColor;
      let bottomColor;
      if (!isUndefined(this.value.color) && this.value.color !== null) {
        if (isNumber(this.value.color) || isString(this.value.color) || isResource(this.value.color)) {
          leftColor = this.value.color;
          rightColor = this.value.color;
          topColor = this.value.color;
          bottomColor = this.value.color;
        } else {
          leftColor = this.value.color.left;
          rightColor = this.value.color.right;
          topColor = this.value.color.top;
          bottomColor = this.value.color.bottom;
        }
      }
      let topLeft;
      let topRight;
      let bottomLeft;
      let bottomRight;
      if (!isUndefined(this.value.radius) && this.value.radius !== null) {
        if (isNumber(this.value.radius) || isString(this.value.radius) || isResource(this.value.radius)) {
          topLeft = this.value.radius;
          topRight = this.value.radius;
          bottomLeft = this.value.radius;
          bottomRight = this.value.radius;
        } else {
          topLeft = this.value.radius.topLeft;
          topRight = this.value.radius.topRight;
          bottomLeft = this.value.radius.bottomLeft;
          bottomRight = this.value.radius.bottomRight;
        }
      }
      let styleTop;
      let styleRight;
      let styleBottom;
      let styleLeft;
      if (!isUndefined(this.value.style) && this.value.style !== null) {
        if (isNumber(this.value.style) || isString(this.value.style) || isResource(this.value.style)) {
          styleTop = this.value.style;
          styleRight = this.value.style;
          styleBottom = this.value.style;
          styleLeft = this.value.style;
        } else {
          styleTop = this.value.style.top;
          styleRight = this.value.style.right;
          styleBottom = this.value.style.bottom;
          styleLeft = this.value.style.left;
        }
      }
      getUINativeModule().image.setImageBorder(
        node,
        widthLeft,
        widthRight,
        widthTop,
        widthBottom,
        leftColor,
        rightColor,
        topColor,
        bottomColor,
        topLeft,
        topRight,
        bottomLeft,
        bottomRight,
        styleTop,
        styleRight,
        styleBottom,
        styleLeft
      );
    }
  }
  checkObjectDiff() {
    return (
      !isBaseOrResourceEqual(this.stageValue.width, this.value.width) ||
      !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
      !isBaseOrResourceEqual(this.stageValue.radius, this.value.radius) ||
      !isBaseOrResourceEqual(this.stageValue.style, this.value.style)
    );
  }
}
ImageBorderModifier.identity = Symbol('imageBorder');
class ImageOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetImageOpacity(node);
    } else {
      getUINativeModule().image.setImageOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ImageOpacityModifier.identity = Symbol('imageOpacity');
class ImageeEdgeAntialiasingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetEdgeAntialiasing(node);
    } else {
      getUINativeModule().image.setEdgeAntialiasing(node, this.value);
    }
  }
}
ImageeEdgeAntialiasingModifier.identity = Symbol('edgeAntialiasing');
class ImageTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetImageTransition(node);
    } else {
      getUINativeModule().image.setImageTransition(node, this.value.transitionEffect, this.value.callback);
    }
  }
}
ImageTransitionModifier.identity = Symbol('imageTransition');
class ImagePointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
ImagePointLightModifier.identity = Symbol('imagePointLight');
class ImageResizableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetResizable(node);
    } else {
      if (!isUndefined(this.value.lattice) && !isNull(this.value.lattice)) {
        getUINativeModule().image.setResizableLattice(node, this.value.lattice);
      }
      let sliceTop;
      let sliceRight;
      let sliceBottom;
      let sliceLeft;
      if (!isUndefined(this.value.slice) && !isNull(this.value.slice)) {
        let tmpSlice = this.value.slice;
        sliceTop = tmpSlice.top;
        sliceRight = tmpSlice.right;
        sliceBottom = tmpSlice.bottom;
        sliceLeft = tmpSlice.left;
      }
      getUINativeModule().image.setResizable(node, sliceTop, sliceRight, sliceBottom, sliceLeft);
    }
  }
}
ImageResizableModifier.identity = Symbol('resizable');
class ImageDynamicRangeModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetDynamicRangeMode(node);
    }
    else {
      getUINativeModule().image.setDynamicRangeMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageDynamicRangeModeModifier.identity = Symbol('dynamicRangeMode');
class ImageHdrBrightnessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetHdrBrightness(node);
    }
    else {
      getUINativeModule().image.setHdrBrightness(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageHdrBrightnessModifier.identity = Symbol('hdrBrightness');
class ImageRotateOrientationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetOrientation(node);
    } else {
      getUINativeModule().image.setOrientation(node, this.value);
    }
  }
}
ImageRotateOrientationModifier.identity = Symbol('imageOrientaion');
class ImageEnhancedImageQualityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetEnhancedImageQuality(node);
    }
    else {
      getUINativeModule().image.setEnhancedImageQuality(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageObjectFitModifier.identity = Symbol('enhancedImageQuality');
class ImageSrcModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.setImageShowSrc(node, "");
    }
    else {
      getUINativeModule().image.setImageShowSrc(node, this.value);
    }
  }
}
ImageSrcModifier.identity = Symbol('imageShowSrc');

class ImageReloadKeyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.setReloadKey(node, "");
    }
    else {
      getUINativeModule().image.setReloadKey(node, this.value);
    }
  }
}
ImageReloadKeyModifier.identity = Symbol('reloadKey');

class ImageEnableAnalyzerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.enableAnalyzer(node, "");
    }
    else {
      getUINativeModule().image.enableAnalyzer(node, this.value);
    }
  }
}
ImageSrcModifier.identity = Symbol('enableAnalyzer');

class ImageAnalyzerConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.analyzerConfig(node, "");
    }
    else {
      getUINativeModule().image.analyzerConfig(node, this.value);
    }
  }
}
ImageSrcModifier.identity = Symbol('analyzerConfig');

class ImagePrivacySensitiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetPrivacySensitive(node);
    }
    else {
      getUINativeModule().image.setPrivacySensitive(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ImagePrivacySensitiveModifier.identity = Symbol('imagePrivacySensitive');

class ImageOnCompleteModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetOnComplete(node);
    } else {
      getUINativeModule().image.setOnComplete(node, this.value);
    }
  }
}
ImageOnCompleteModifier.identity = Symbol('imageOnComplete');

class ImageOnErrorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetOnError(node);
    }
    else {
      getUINativeModule().image.setOnError(node, this.value);
    }
  }
}
ImageOnErrorModifier.identity = Symbol('imageOnError');

class ImageOnFinishModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetOnFinish(node);
    } else {
      getUINativeModule().image.setOnFinish(node, this.value);
    }
  }
}
ImageOnFinishModifier.identity = Symbol('imageOnFinish');
class ImageSupportSvg2Modifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetSupportSvg2(node);
    }
    else {
      getUINativeModule().image.setSupportSvg2(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageSupportSvg2Modifier.identity = Symbol('supportSvg2');
class ImageContentTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetContentTransition(node);
    }
    else {
      getUINativeModule().image.setContentTransition(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageContentTransitionModifier.identity = Symbol('contentTransition');
class ImageAntiAliasModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().image.resetAntiAlias(node);
    } else {
      getUINativeModule().image.setAntiAlias(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ImageAntiAliasModifier.identity = Symbol('antialiased');
class ArkImageComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    modifierWithKey(this._modifiersWithKeys, ImageSrcModifier.identity, ImageSrcModifier, value[0]);
    if (value.length >= 2) {
      if (typeof value[1] === 'string') {
        // Overload: (src, reloadKey?)
        modifierWithKey(this._modifiersWithKeys, ImageReloadKeyModifier.identity, ImageReloadKeyModifier, value[1]);
      } else if (value[1] !== undefined && value[1] !== null) {
        // Overload: (src, imageAIOptions?) or (src, imageAIOptions?, reloadKey?)
        modifierWithKey(this._modifiersWithKeys, ImageAnalyzerConfigModifier.identity, ImageAnalyzerConfigModifier, value[1]);
        if (value.length >= 3) {
          let reloadKeyValue = (typeof value[2] === 'string') ? value[2] : '';
          modifierWithKey(this._modifiersWithKeys, ImageReloadKeyModifier.identity, ImageReloadKeyModifier, reloadKeyValue);
        }
      } else {
        // value[1] is undefined/null, reset reloadKey to empty string
        modifierWithKey(this._modifiersWithKeys, ImageReloadKeyModifier.identity, ImageReloadKeyModifier, '');
      }
    }
    return this;
  }
  allowChildCount() {
    return 0;
  }
  draggable(value) {
    modifierWithKey(this._modifiersWithKeys, ImageDraggableModifier.identity, ImageDraggableModifier, value);
    return this;
  }
  edgeAntialiasing(value) {
    modifierWithKey(this._modifiersWithKeys, ImageeEdgeAntialiasingModifier.identity, ImageeEdgeAntialiasingModifier, value);
    return this;
  }
  resizable(value) {
    modifierWithKey(this._modifiersWithKeys, ImageResizableModifier.identity, ImageResizableModifier, value);
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
  imageMatrix(value) {
    modifierWithKey(this._modifiersWithKeys, ImageMatrixModifier.identity, ImageMatrixModifier, value);
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
  orientation(value) {
    modifierWithKey(this._modifiersWithKeys, ImageRotateOrientationModifier.identity, ImageRotateOrientationModifier, value);
    return this;
  }
  interpolation(value) {
    modifierWithKey(this._modifiersWithKeys, ImageInterpolationModifier.identity, ImageInterpolationModifier, value);
    return this;
  }
  pointLight(value) {
    modifierWithKey(this._modifiersWithKeys, ImagePointLightModifier.identity, ImagePointLightModifier, value);
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
    modifierWithKey(this._modifiersWithKeys, ImageOnCompleteModifier.identity, ImageOnCompleteModifier, callback);
    return this;
  }
  onError(callback) {
    modifierWithKey(this._modifiersWithKeys, ImageOnErrorModifier.identity, ImageOnErrorModifier, callback);
    return this;
  }
  onFinish(event) {
    modifierWithKey(this._modifiersWithKeys, ImageOnFinishModifier.identity, ImageOnFinishModifier, event);
    return this;
  }
  border(value) {
    modifierWithKey(this._modifiersWithKeys, ImageBorderModifier.identity, ImageBorderModifier, value);
    return this;
  }
  opacity(value) {
    modifierWithKey(this._modifiersWithKeys, ImageOpacityModifier.identity, ImageOpacityModifier, value);
    return this;
  }
  transition(value, callback) {
    let arkTransition = new ArkTransition();
    arkTransition.transitionEffect = value;
    if (typeof callback === 'function') {
      arkTransition.callback = callback;
    }
    modifierWithKey(this._modifiersWithKeys, ImageTransitionModifier.identity, ImageTransitionModifier, arkTransition);
    return this;
  }
  dynamicRangeMode(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageDynamicRangeModeModifier.identity, ImageDynamicRangeModeModifier, value);
    return this;
  }
  hdrBrightness(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageHdrBrightnessModifier.identity, ImageHdrBrightnessModifier, value);
    return this;
  }
  enhancedImageQuality(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageEnhancedImageQualityModifier.identity, ImageEnhancedImageQualityModifier, value);
    return this;
  }
  enableAnalyzer(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageEnableAnalyzerModifier.identity, ImageEnableAnalyzerModifier, value);
    return this;
  }
  privacySensitive(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImagePrivacySensitiveModifier.identity, ImagePrivacySensitiveModifier, value);
    return this;
  }
  analyzerConfig(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageAnalyzerConfigModifier.identity, ImageAnalyzerConfigModifier, value);
    return this;
  }
  supportSvg2(value) {
    modifierWithKey(
      this._modifiersWithKeys, ImageSupportSvg2Modifier.identity, ImageSupportSvg2Modifier, value);
    return this;
  }
  contentTransition(value) {
    modifierWithKey(this._modifiersWithKeys, ImageContentTransitionModifier.identity, ImageContentTransitionModifier, value);
    return this;
  }
  antialiased(value) {
    modifierWithKey(this._modifiersWithKeys, ImageAntiAliasModifier.identity, ImageAntiAliasModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Image !== undefined) {
  globalThis.Image.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkImageComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ImageModifier(nativePtr, classType);
    });
  };
}

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

class RowSpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().row.resetSpace(node);
    }
    else {
      getUINativeModule().row.setSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RowSpaceModifier.identity = Symbol('rowSpace');

class LinearIndicatorIndicatorStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().linearIndicator.resetIndicatorStyle(node);
    }
    else {
      getUINativeModule().linearIndicator.setIndicatorStyle(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
LinearIndicatorIndicatorStyleModifier.identity = Symbol('linearIndicatorIndicatorStyle');

class LinearIndicatorIndicatorLoopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().linearIndicator.resetIndicatorLoop(node);
    }
    else {
      getUINativeModule().linearIndicator.setIndicatorLoop(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
LinearIndicatorIndicatorLoopModifier.identity = Symbol('linearIndicatorIndicatorLoop');

class LinearIndicatorOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().linearIndicator.resetOnChange(node);
    } else {
      getUINativeModule().linearIndicator.setOnChange(node, this.value);
    }
  }
}
LinearIndicatorOnChangeModifier.identity = Symbol('linearIndicatorOnChange');

class ArkLinearIndicatorComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }

  indicatorStyle(value) {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorIndicatorStyleModifier.identity, LinearIndicatorIndicatorStyleModifier, value);
    return this;
  }

  indicatorLoop(value) {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorIndicatorLoopModifier.identity, LinearIndicatorIndicatorLoopModifier, value);
    return this;
  }

  onChange(value) {
    modifierWithKey(this._modifiersWithKeys, LinearIndicatorOnChangeModifier.identity, LinearIndicatorOnChangeModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.LinearIndicator !== undefined) {
  globalThis.LinearIndicator.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkLinearIndicatorComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.LinearIndicatorModifier(nativePtr, classType);
    });
  };
}

class RowPointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
RowPointLightModifier.identity = Symbol('rowPointLight');

class RowReverseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().row.resetReverse(node);
    } else {
      getUINativeModule().row.setReverse(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
RowReverseModifier.identity = Symbol('rowReverse');

class ArkRowComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, RowSpaceModifier.identity, RowSpaceModifier, value[0].space);
    }
    return this
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
    modifierWithKey(this._modifiersWithKeys, RowPointLightModifier.identity, RowPointLightModifier, value);
    return this;
  }
  reverse(value) {
    modifierWithKey(this._modifiersWithKeys, RowReverseModifier.identity, RowReverseModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Row !== undefined) {
  globalThis.Row.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkRowComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.RowModifier(nativePtr, classType);
    });
  };
}

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
class SpanTextBackgroundStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetTextBackgroundStyle(node);
    }
    else {
      let textBackgroundStyle = new ArkTextBackGroundStyle();
      if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
        getUINativeModule().span.resetTextBackgroundStyle(node);
      }
      else {
        getUINativeModule().span.setTextBackgroundStyle(node, textBackgroundStyle.color, textBackgroundStyle.radius.topLeft, textBackgroundStyle.radius.topRight, textBackgroundStyle.radius.bottomLeft, textBackgroundStyle.radius.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    let textBackgroundStyle = new ArkTextBackGroundStyle();
    let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
    if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) || !stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
      return false;
    }
    else {
      return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
    }
  }
}
SpanTextBackgroundStyleModifier.identity = Symbol('spanTextBackgroundStyle');
class SpanTextShadowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetTextShadow(node);
    }
    else {
      let shadow = new ArkShadowInfoToArray();
      if (!shadow.convertShadowOptions(this.value)) {
        getUINativeModule().span.resetTextShadow(node);
      }
      else {
        getUINativeModule().span.setTextShadow(node, shadow.radius, shadow.type, shadow.color,
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
SpanTextShadowModifier.identity = Symbol('spanTextShadow');
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
class SpanBaselineOffsetModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetBaselineOffset(node);
    }
    else {
      getUINativeModule().span.setBaselineOffset(node, this.value);
    }
  }
}
SpanBaselineOffsetModifier.identity = Symbol('spanBaselineOffset');
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
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style ||
      this.stageValue.enableVariableFontWeight !== this.value.enableVariableFontWeight) {
      return true;
    }
    if ((!isResource(this.stageValue.size) && !isResource(this.value.size) &&
      this.stageValue.size === this.value.size) &&
      (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
        this.stageValue.family === this.value.family)) {
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
      getUINativeModule().span.setDecoration(node, this.value.type, this.value.color,
        this.value.style, this.value.thicknessScale);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style ||
        this.stageValue.thicknessScale !== this.value.thicknessScale) {
      return true;
    }
    if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
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
    } else {
      getUINativeModule().span.setFontWeight(node, this.value.value,
        this.value?.enableVariableFontWeight,
        this.value?.enableDeviceFontWeightCategory
      );
    }
  }
}
SpanFontWeightModifier.identity = Symbol('spanfontweight');
class SpanFontVariationsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetFontVariations(node);
    } else {
      getUINativeModule().span.setFontVariations(node, this.value);
    }
  }
}
SpanFontVariationsModifier.identity = Symbol('spanFontVariations');
class SpanInputModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.setSpanSrc(node, '');
    }
    else {
      getUINativeModule().span.setSpanSrc(node, this.value);
    }
  }
}
SpanInputModifier.identity = Symbol('spanInput');
class SpanAccessibilityTextModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetAccessibilityText(node);
    } else {
      getUINativeModule().span.setAccessibilityText(node, this.value);
    }
  }
}
SpanAccessibilityTextModifier.identity = Symbol('spanAccessibilityText');
class SpanAccessibilityDescriptionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetAccessibilityDescription(node);
    } else {
      getUINativeModule().span.setAccessibilityDescription(node, this.value);
    }
  }
}
SpanAccessibilityDescriptionModifier.identity = Symbol('spanAccessibilityDescription');
class SpanAccessibilityLevelModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetAccessibilityLevel(node);
    } else {
      getUINativeModule().span.setAccessibilityLevel(node, this.value);
    }
  }
}
SpanAccessibilityLevelModifier.identity = Symbol('spanAccessibilityLevel');
class SpanOnHoverModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().span.resetOnHover(node);
    } else {
      getUINativeModule().span.setOnHover(node, this.value);
    }
  }
}
SpanOnHoverModifier.identity = Symbol('spanOnHover');
class ArkSpanComponent {
  constructor(nativePtr, classType) {
    this._modifiersWithKeys = new Map();
    this.nativePtr = nativePtr;
    this._changed = false;
    this._classType = classType;
    this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(nativePtr);
    this._nativePtrChanged = false;
  }
  initialize(value) {
    modifierWithKey(this._modifiersWithKeys, SpanInputModifier.identity, SpanInputModifier, value[0]);
    return this;
  }
  applyModifierPatch() {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr, this)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  cleanStageValue() {
    if (!this._modifiersWithKeys) {
      return;
    }
    this._modifiersWithKeys.forEach((value, key) => {
        value.stageValue = undefined;
    });
  }
  applyStateUpdatePtr(instance) {
    if (this.nativePtr !== instance.nativePtr) {
      this.nativePtr = instance.nativePtr;
      this._nativePtrChanged = true;
      if (instance._weakPtr) {
        this._weakPtr = instance._weakPtr;
      } else {
        this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(this.nativePtr);
      }
    }
  }
  onGestureJudgeBegin(callback) {
    throw new BusinessError(100201, 'onGestureJudgeBegin function not supported in attributeModifier scenario.');
  }
  outline(value) {
    throw new BusinessError(100201, 'outline function not supported in attributeModifier scenario.');
  }
  outlineColor(value) {
    throw new BusinessError(100201, 'outlineColor function not supported in attributeModifier scenario.');
  }
  outlineRadius(value) {
    throw new BusinessError(100201, 'outlineRadius function not supported in attributeModifier scenario.');
  }
  outlineStyle(value) {
    throw new BusinessError(100201, 'outlineStyle function not supported in attributeModifier scenario.');
  }
  outlineWidth(value) {
    throw new BusinessError(100201, 'outlineWidth function not supported in attributeModifier scenario.');
  }
  width(value) {
    throw new BusinessError(100201, 'width function not supported in attributeModifier scenario.');
  }
  height(value) {
    throw new BusinessError(100201, 'height function not supported in attributeModifier scenario.');
  }
  expandSafeArea(types, edges) {
    throw new BusinessError(100201, 'expandSafeArea function not supported in attributeModifier scenario.');
  }
  responseRegionList(value) {
    throw new BusinessError(100201, 'responseRegionList function not supported in attributeModifier scenario.');
  }
  responseRegion(value) {
    throw new BusinessError(100201, 'responseRegion function not supported in attributeModifier scenario.');
  }
  mouseResponseRegion(value) {
    throw new BusinessError(100201, 'mouseResponseRegion function not supported in attributeModifier scenario.');
  }
  size(value) {
    throw new BusinessError(100201, 'size function not supported in attributeModifier scenario.');
  }
  constraintSize(value) {
    throw new BusinessError(100201, 'constraintSize function not supported in attributeModifier scenario.');
  }
  touchable(value) {
    throw new BusinessError(100201, 'touchable function not supported in attributeModifier scenario.');
  }
  hitTestBehavior(value) {
    throw new BusinessError(100201, 'hitTestBehavior function not supported in attributeModifier scenario.');
  }
  layoutWeight(value) {
    throw new BusinessError(100201, 'layoutWeight function not supported in attributeModifier scenario.');
  }
  padding(value) {
    throw new BusinessError(100201, 'padding function not supported in attributeModifier scenario.');
  }
  margin(value) {
    throw new BusinessError(100201, 'margin function not supported in attributeModifier scenario.');
  }
  background(builder, options) {
    throw new BusinessError(100201, 'background function not supported in attributeModifier scenario.');
  }
  backgroundColor(value) {
    throw new BusinessError(100201, 'backgroundColor function not supported in attributeModifier scenario.');
  }
  backgroundImage(src, repeat) {
    throw new BusinessError(100201, 'backgroundImage function not supported in attributeModifier scenario.');
  }
  backgroundImageSize(value) {
    throw new BusinessError(100201, 'backgroundImageSize function not supported in attributeModifier scenario.');
  }
  backgroundImagePosition(value) {
    throw new BusinessError(100201, 'backgroundImagePosition function not supported in attributeModifier scenario.');
  }
  backgroundBlurStyle(value, options) {
    throw new BusinessError(100201, 'backgroundBlurStyle function not supported in attributeModifier scenario.');
  }
  foregroundBlurStyle(value, options) {
    throw new BusinessError(100201, 'foregroundBlurStyle function not supported in attributeModifier scenario.');
  }
  opacity(value) {
    throw new BusinessError(100201, 'opacity function not supported in attributeModifier scenario.');
  }
  border(value) {
    throw new BusinessError(100201, 'border function not supported in attributeModifier scenario.');
  }
  borderStyle(value) {
    throw new BusinessError(100201, 'borderStyle function not supported in attributeModifier scenario.');
  }
  borderWidth(value) {
    throw new BusinessError(100201, 'borderWidth function not supported in attributeModifier scenario.');
  }
  borderColor(value) {
    throw new BusinessError(100201, 'borderColor function not supported in attributeModifier scenario.');
  }
  borderRadius(value) {
    throw new BusinessError(100201, 'borderRadius function not supported in attributeModifier scenario.');
  }
  borderImage(value) {
    throw new BusinessError(100201, 'borderImage function not supported in attributeModifier scenario.');
  }
  foregroundColor(value) {
    throw new BusinessError(100201, 'foregroundColor function not supported in attributeModifier scenario.');
  }
  onClick(event) {
    modifierWithKey(this._modifiersWithKeys, ClickModifier.identity, ClickModifier, event);
    return this;
  }
  onHover(event) {
    modifierWithKey(this._modifiersWithKeys, SpanOnHoverModifier.identity, SpanOnHoverModifier, event);
    return this;
  }
  hoverEffect(value) {
    throw new BusinessError(100201, 'hoverEffect function not supported in attributeModifier scenario.');
  }
  onMouse(event) {
    throw new BusinessError(100201, 'onMouse function not supported in attributeModifier scenario.');
  }
  onTouch(event) {
    throw new BusinessError(100201, 'onTouch function not supported in attributeModifier scenario.');
  }
  onKeyEvent(event) {
    throw new BusinessError(100201, 'onKeyEvent function not supported in attributeModifier scenario.');
  }
  focusable(value) {
    throw new BusinessError(100201, 'focusable function not supported in attributeModifier scenario.');
  }
  onFocus(event) {
    throw new BusinessError(100201, 'onFocus function not supported in attributeModifier scenario.');
  }
  onNeedSoftkeyboard(onNeedSoftkeyboardCallback) {
    throw new Error('Method not implemented.');
  }
  onBlur(event) {
    throw new BusinessError(100201, 'onBlur function not supported in attributeModifier scenario.');
  }
  tabIndex(index) {
    throw new BusinessError(100201, 'tabIndex function not supported in attributeModifier scenario.');
  }
  defaultFocus(value) {
    throw new BusinessError(100201, 'defaultFocus function not supported in attributeModifier scenario.');
  }
  groupDefaultFocus(value) {
    throw new BusinessError(100201, 'groupDefaultFocus function not supported in attributeModifier scenario.');
  }
  focusOnTouch(value) {
    throw new BusinessError(100201, 'focusOnTouch function not supported in attributeModifier scenario.');
  }
  animation(value) {
    throw new BusinessError(100201, 'animation function not supported in attributeModifier scenario.');
  }
  transition(value, callback) {
    throw new BusinessError(100201, 'transition function not supported in attributeModifier scenario.');
  }
  gesture(gesture, mask) {
    throw new BusinessError(100201, 'gesture function not supported in attributeModifier scenario.');
  }
  priorityGesture(gesture, mask) {
    throw new BusinessError(100201, 'priorityGesture function not supported in attributeModifier scenario.');
  }
  parallelGesture(gesture, mask) {
    throw new BusinessError(100201, 'parallelGesture function not supported in attributeModifier scenario.');
  }
  blur(value) {
    throw new BusinessError(100201, 'blur function not supported in attributeModifier scenario.');
  }
  linearGradientBlur(value, options) {
    throw new BusinessError(100201, 'linearGradientBlur function not supported in attributeModifier scenario.');
  }
  brightness(value) {
    throw new BusinessError(100201, 'brightness function not supported in attributeModifier scenario.');
  }
  contrast(value) {
    throw new BusinessError(100201, 'contrast function not supported in attributeModifier scenario.');
  }
  grayscale(value) {
    throw new BusinessError(100201, 'grayscale function not supported in attributeModifier scenario.');
  }
  colorBlend(value) {
    throw new BusinessError(100201, 'colorBlend function not supported in attributeModifier scenario.');
  }
  saturate(value) {
    throw new BusinessError(100201, 'saturate function not supported in attributeModifier scenario.');
  }
  sepia(value) {
    throw new BusinessError(100201, 'sepia function not supported in attributeModifier scenario.');
  }
  invert(value) {
    throw new BusinessError(100201, 'invert function not supported in attributeModifier scenario.');
  }
  hueRotate(value) {
    throw new BusinessError(100201, 'hueRotate function not supported in attributeModifier scenario.');
  }
  useEffect(value) {
    throw new BusinessError(100201, 'useEffect function not supported in attributeModifier scenario.');
  }
  backdropBlur(value) {
    throw new BusinessError(100201, 'backdropBlur function not supported in attributeModifier scenario.');
  }
  renderGroup(value) {
    throw new BusinessError(100201, 'renderGroup function not supported in attributeModifier scenario.');
  }
  translate(value) {
    throw new BusinessError(100201, 'translate function not supported in attributeModifier scenario.');
  }
  scale(value) {
    throw new BusinessError(100201, 'scale function not supported in attributeModifier scenario.');
  }
  gridSpan(value) {
    throw new BusinessError(100201, 'gridSpan function not supported in attributeModifier scenario.');
  }
  gridOffset(value) {
    throw new BusinessError(100201, 'gridOffset function not supported in attributeModifier scenario.');
  }
  rotate(value) {
    throw new BusinessError(100201, 'rotate function not supported in attributeModifier scenario.');
  }
  transform(value) {
    throw new BusinessError(100201, 'transform function not supported in attributeModifier scenario.');
  }
  transform3D(value) {
    throw new BusinessError(100201, 'transform3D function not supported in attributeModifier scenario.');
  }
  onAppear(event) {
    throw new BusinessError(100201, 'onAppear function not supported in attributeModifier scenario.');
  }
  onDisAppear(event) {
    throw new BusinessError(100201, 'onDisAppear function not supported in attributeModifier scenario.');
  }
  onAttach(event) {
    throw new BusinessError(100201, 'onAttach function not supported in attributeModifier scenario.');
  }
  onDetach(event) {
    throw new BusinessError(100201, 'onDetach function not supported in attributeModifier scenario.');
  }
  onAreaChange(event, options) {
    throw new BusinessError(100201, 'onAreaChange function not supported in attributeModifier scenario.');
  }
  visibility(value) {
    throw new BusinessError(100201, 'visibility function not supported in attributeModifier scenario.');
  }
  flexGrow(value) {
    throw new BusinessError(100201, 'flexGrow function not supported in attributeModifier scenario.');
  }
  flexShrink(value) {
    throw new BusinessError(100201, 'flexShrink function not supported in attributeModifier scenario.');
  }
  flexBasis(value) {
    throw new BusinessError(100201, 'flexBasis function not supported in attributeModifier scenario.');
  }
  alignSelf(value) {
    throw new BusinessError(100201, 'alignSelf function not supported in attributeModifier scenario.');
  }
  displayPriority(value) {
    throw new BusinessError(100201, 'displayPriority function not supported in attributeModifier scenario.');
  }
  zIndex(value) {
    throw new BusinessError(100201, 'zIndex function not supported in attributeModifier scenario.');
  }
  sharedTransition(id, options) {
    throw new BusinessError(100201, 'sharedTransition function not supported in attributeModifier scenario.');
  }
  direction(value) {
    throw new BusinessError(100201, 'direction function not supported in attributeModifier scenario.');
  }
  align(value) {
    throw new BusinessError(100201, 'align function not supported in attributeModifier scenario.');
  }
  position(value) {
    throw new BusinessError(100201, 'position function not supported in attributeModifier scenario.');
  }
  markAnchor(value) {
    throw new BusinessError(100201, 'markAnchor function not supported in attributeModifier scenario.');
  }
  offset(value) {
    throw new BusinessError(100201, 'offset function not supported in attributeModifier scenario.');
  }
  enabled(value) {
    throw new BusinessError(100201, 'enabled function not supported in attributeModifier scenario.');
  }
  useSizeType(value) {
    throw new BusinessError(100201, 'useSizeType function not supported in attributeModifier scenario.');
  }
  alignRules(value) {
    throw new BusinessError(100201, 'alignRules function not supported in attributeModifier scenario.');
  }
  aspectRatio(value) {
    throw new BusinessError(100201, 'aspectRatio function not supported in attributeModifier scenario.');
  }
  clickEffect(value) {
    throw new BusinessError(100201, 'clickEffect function not supported in attributeModifier scenario.');
  }
  enableClickSoundEffect(value) {
    throw new BusinessError(100201, 'enableClickSoundEffect function not supported in attributeModifier scenario.');
  }
  onDragStart(event) {
    throw new BusinessError(100201, 'onDragStart function not supported in attributeModifier scenario.');
  }
  onDragEnter(event) {
    throw new BusinessError(100201, 'onDragEnter function not supported in attributeModifier scenario.');
  }
  onDragSpringLoading(event) {
    throw new BusinessError(100201, 'onDragSpringLoading function not supported in attributeModifier scenario.');
  }
  onDragMove(event) {
    throw new BusinessError(100201, 'onDragMove function not supported in attributeModifier scenario.');
  }
  onDragLeave(event) {
    throw new BusinessError(100201, 'onDragLeave function not supported in attributeModifier scenario.');
  }
  onDrop(event) {
    throw new BusinessError(100201, 'onDrop function not supported in attributeModifier scenario.');
  }
  onDragEnd(event) {
    throw new BusinessError(100201, 'onDragEnd function not supported in attributeModifier scenario.');
  }
  allowDrop(value) {
    throw new BusinessError(100201, 'allowDrop function not supported in attributeModifier scenario.');
  }
  draggable(value) {
    throw new BusinessError(100201, 'draggable function not supported in attributeModifier scenario.');
  }
  overlay(value, options) {
    throw new BusinessError(100201, 'overlay function not supported in attributeModifier scenario.');
  }
  linearGradient(value) {
    throw new BusinessError(100201, 'linearGradient function not supported in attributeModifier scenario.');
  }
  sweepGradient(value) {
    throw new BusinessError(100201, 'sweepGradient function not supported in attributeModifier scenario.');
  }
  radialGradient(value) {
    throw new BusinessError(100201, 'radialGradient function not supported in attributeModifier scenario.');
  }
  motionPath(value) {
    throw new BusinessError(100201, 'motionPath function not supported in attributeModifier scenario.');
  }
  motionBlur(value) {
    throw new BusinessError(100201, 'motionBlur function not supported in attributeModifier scenario.');
  }
  shadow(value) {
    throw new BusinessError(100201, 'shadow function not supported in attributeModifier scenario.');
  }
  mask(value) {
    throw new BusinessError(100201, 'mask function not supported in attributeModifier scenario.');
  }
  key(value) {
    throw new BusinessError(100201, 'key function not supported in attributeModifier scenario.');
  }
  id(value) {
    throw new BusinessError(100201, 'id function not supported in attributeModifier scenario.');
  }
  geometryTransition(id) {
    throw new BusinessError(100201, 'geometryTransition function not supported in attributeModifier scenario.');
  }
  bindPopup(show, popup) {
    throw new BusinessError(100201, 'bindPopup function not supported in attributeModifier scenario.');
  }
  bindMenu(content, options) {
    throw new BusinessError(100201, 'bindMenu function not supported in attributeModifier scenario.');
  }
  bindContextMenu(content, responseType, options) {
    throw new BusinessError(100201, 'bindContextMenu function not supported in attributeModifier scenario.');
  }
  bindContentCover(isShow, builder, type) {
    throw new BusinessError(100201, 'bindContentCover function not supported in attributeModifier scenario.');
  }
  blendMode(value) {
    throw new BusinessError(100201, 'blendMode function not supported in attributeModifier scenario.');
  }
  clip(value) {
    throw new BusinessError(100201, 'clip function not supported in attributeModifier scenario.');
  }
  bindSheet(isShow, builder, options) {
    throw new BusinessError(100201, 'bindSheet function not supported in attributeModifier scenario.');
  }
  stateStyles(value) {
    throw new BusinessError(100201, 'stateStyles function not supported in attributeModifier scenario.');
  }
  restoreId(value) {
    throw new BusinessError(100201, 'restoreId function not supported in attributeModifier scenario.');
  }
  onVisibleAreaChange(ratios, event) {
    throw new BusinessError(100201, 'onVisibleAreaChange function not supported in attributeModifier scenario.');
  }
  sphericalEffect(value) {
    throw new BusinessError(100201, 'sphericalEffect function not supported in attributeModifier scenario.');
  }
  lightUpEffect(value) {
    throw new BusinessError(100201, 'lightUpEffect function not supported in attributeModifier scenario.');
  }
  pixelStretchEffect(options) {
    throw new BusinessError(100201, 'pixelStretchEffect function not supported in attributeModifier scenario.');
  }
  keyboardShortcut(value, keys, action) {
    throw new BusinessError(100201, 'keyboardShortcut function not supported in attributeModifier scenario.');
  }
  accessibilityGroup(value) {
    throw new BusinessError(100201, 'accessibilityGroup function not supported in attributeModifier scenario.');
  }
  doubleSided(value) {
    throw new BusinessError(100201, 'doubleSided function not supported in attributeModifier scenario.');
  }
  accessibilityText(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityTextModifier.identity, SpanAccessibilityTextModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityTextModifier.identity, SpanAccessibilityTextModifier, undefined);
    }
    return this;
  }
  accessibilityDescription(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityDescriptionModifier.identity, SpanAccessibilityDescriptionModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityDescriptionModifier.identity, SpanAccessibilityDescriptionModifier, undefined);
    }
    return this;
  }
  accessibilityLevel(value) {
    if (typeof value === 'string') {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityLevelModifier.identity, SpanAccessibilityLevelModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SpanAccessibilityLevelModifier.identity, SpanAccessibilityLevelModifier, undefined);
    }
    return this;
  }
  obscured(reasons) {
    throw new BusinessError(100201, 'obscured function not supported in attributeModifier scenario.');
  }
  reuseId(id) {
    throw new BusinessError(100201, 'reuseId function not supported in attributeModifier scenario.');
  }
  renderFit(fitMode) {
    throw new BusinessError(100201, 'renderFit function not supported in attributeModifier scenario.');
  }
  systemMaterial(material) {
    throw new BusinessError(100201, 'systemMaterial function not supported in attributeModifier scenario.');
  }
  materialFilter(filter) {
    throw new BusinessError(100201, 'materialFilter function not supported in attributeModifier scenario.');
  }
  useUnionEffect(value) {
    throw new BusinessError(100201, 'useUnionEffect function not supported in attributeModifier scenario.');
  }
  attributeModifier(modifier) {
    return this;
  }
  decoration(value) {
    modifierWithKey(this._modifiersWithKeys, SpanDecorationModifier.identity, SpanDecorationModifier, value);
    return this;
  }
  font(value, fontConfigs) {
    let arkFontWeight = new ArkFontWeight();
    arkFontWeight.value = (value === null || value === void 0 ? void 0 : value.weight);
    if (fontConfigs !== null && fontConfigs !== undefined &&
        fontConfigs.fontWeightConfigs !== null && fontConfigs.fontWeightConfigs !== undefined &&
        'fontWeightConfigs' in fontConfigs) {
      arkFontWeight.enableVariableFontWeight = fontConfigs.fontWeightConfigs?.enableVariableFontWeight ?? false;
      arkFontWeight.enableDeviceFontWeightCategory = fontConfigs.fontWeightConfigs?.enableDeviceFontWeightCategory ?? true;
    }
    modifierWithKey(this._modifiersWithKeys, SpanFontSizeModifier.identity, SpanFontSizeModifier,
      value === null || value === void 0 ? void 0 : value.size);
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier,
      arkFontWeight);
    modifierWithKey(this._modifiersWithKeys, SpanFontFamilyModifier.identity, SpanFontFamilyModifier,
      value === null || value === void 0 ? void 0 : value.family);
    modifierWithKey(this._modifiersWithKeys, SpanFontStyleModifier.identity, SpanFontStyleModifier,
      value === null || value === void 0 ? void 0 : value.style);
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
  fontWeight(value, fontWeightConfigs) {
    let arkFontWeight = new ArkFontWeight();
    arkFontWeight.value = value;
    if (fontWeightConfigs !== null && fontWeightConfigs !== undefined && typeof fontWeightConfigs === 'object') {
      arkFontWeight.enableVariableFontWeight = fontWeightConfigs.enableVariableFontWeight ?? false;
      arkFontWeight.enableDeviceFontWeightCategory = fontWeightConfigs.enableDeviceFontWeightCategory ?? true;
    }
    modifierWithKey(this._modifiersWithKeys, SpanFontWeightModifier.identity, SpanFontWeightModifier, arkFontWeight);
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
  baselineOffset(value) {
    modifierWithKey(this._modifiersWithKeys, SpanBaselineOffsetModifier.identity, SpanBaselineOffsetModifier, value);
    return this;
  }
  textCase(value) {
    modifierWithKey(this._modifiersWithKeys, SpanTextCaseModifier.identity, SpanTextCaseModifier, value);
    return this;
  }
  textBackgroundStyle(value) {
    modifierWithKey(this._modifiersWithKeys, SpanTextBackgroundStyleModifier.identity, SpanTextBackgroundStyleModifier, value);
    return this;
  }
  textShadow(value) {
    modifierWithKey(this._modifiersWithKeys, SpanTextShadowModifier.identity, SpanTextShadowModifier, value);
    return this;
  }
  fontVariations(value) {
    modifierWithKey(this._modifiersWithKeys, SpanFontVariationsModifier.identity, SpanFontVariationsModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Span !== undefined) {
  globalThis.Span.attributeModifier = function (modifier) {
    attributeModifierFuncWithoutStateStyles.call(this, modifier, (nativePtr) => {
      return new ArkSpanComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.SpanModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkStackComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      this.alignContent(value[0].alignContent);
    }
    return this
  }
  alignContent(value) {
    modifierWithKey(this._modifiersWithKeys, StackAlignContentModifier.identity, StackAlignContentModifier, value);
    return this;
  }
  align(value) {
    modifierWithKey(this._modifiersWithKeys, StackAlignContentModifier.identity, StackAlignContentModifier, value);
    return this;
  }
  pointLight(value) {
    modifierWithKey(this._modifiersWithKeys, StackPointLightModifier.identity, StackPointLightModifier, value);
    return this;
  }
  syncLoad(value) {
    modifierWithKey(this._modifiersWithKeys, StackSyncLoadModifier.identity, StackSyncLoadModifier, value);
    return this;
  }
}
class StackPointLightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetPointLightStyle(node);
    } else {
      let positionX;
      let positionY;
      let positionZ;
      let intensity;
      let color;
      let illuminated;
      let bloom;
      if (!isUndefined(this.value.lightSource) && this.value.lightSource != null) {
        positionX = this.value.lightSource.positionX;
        positionY = this.value.lightSource.positionY;
        positionZ = this.value.lightSource.positionZ;
        intensity = this.value.lightSource.intensity;
        color = this.value.lightSource.color;
      }
      illuminated = this.value.illuminated;
      bloom = this.value.bloom;
      getUINativeModule().common.setPointLightStyle(node, positionX, positionY, positionZ, intensity, color,
        illuminated, bloom);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.lightSource?.positionX, this.value.lightSource?.positionX) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionY, this.value.lightSource?.positionY) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.positionZ, this.value.lightSource?.positionZ) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.intensity, this.value.lightSource?.intensity) ||
    !isBaseOrResourceEqual(this.stageValue.lightSource?.color, this.value.lightSource?.color) ||
    !isBaseOrResourceEqual(this.stageValue.illuminated, this.value.illuminated) ||
    !isBaseOrResourceEqual(this.stageValue.bloom, this.value.bloom);
  }
}
StackPointLightModifier.identity = Symbol('stackPointLight');
class StackAlignContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
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
class StackSyncLoadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().stack.resetSyncLoad(node);
    } else {
      getUINativeModule().stack.setSyncLoad(node, this.value);
    }
  }
}
StackSyncLoadModifier.identity = Symbol('stackSyncLoad');
// @ts-ignore
if (globalThis.Stack !== undefined) {
  globalThis.Stack.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkStackComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.StackModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class TextEnableDataDetectorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetEnableDataDetector(node);
    }
    else {
      getUINativeModule().text.setEnableDataDetector(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextEnableDataDetectorModifier.identity = Symbol('textEnableDataDetector');
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
class TextForegroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextForegroundColor(node);
    }
    else {
      getUINativeModule().text.setTextForegroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextForegroundColorModifier.identity = Symbol('textForegroundColor');
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
      getUINativeModule().text.setFontWeight(node, this.value.value, this.value.enableVariableFontWeight);
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
class TextContentAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextContentAlign(node);
    }
    else {
      getUINativeModule().text.setTextContentAlign(node, this.value);
    }
  }
}
TextContentAlignModifier.identity = Symbol('textContentAlign');
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
class TextPrivacySensitiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetPrivacySensitive(node);
    }
    else {
      getUINativeModule().text.setPrivacySensitive(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextPrivacySensitiveModifier.identity = Symbol('textPrivacySensitive');
class TextWordBreakModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetWordBreak(node);
    }
    else {
      getUINativeModule().text.setWordBreak(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextWordBreakModifier.identity = Symbol('textWordBreak');

class TextLineBreakStrategyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLineBreakStrategy(node);
    }
    else {
      getUINativeModule().text.setLineBreakStrategy(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextLineBreakStrategyModifier.identity = Symbol('textLineBreakStrategy');

class TextFontFeatureModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontFeature(node);
    } else {
      getUINativeModule().text.setFontFeature(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextFontFeatureModifier.identity = Symbol('textFontFeature');

class TextFontVariationsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFontVariations(node);
    } else {
      getUINativeModule().text.setFontVariations(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextFontVariationsModifier.identity = Symbol('textFontVariations');

class TextEllipsisModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetEllipsisMode(node);
    }
    else {
      getUINativeModule().text.setEllipsisMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextEllipsisModeModifier.identity = Symbol('textEllipsisMode');
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
class TextMinFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMinFontScale(node);
    }
    else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMinFontScale(node);
    }
    else {
      getUINativeModule().text.setMinFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMinFontScaleModifier.identity = Symbol('textMinFontScale');
class TextMaxFontScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMaxFontScale(node);
    }
    else if (!isNumber(this.value) && !isResource(this.value)) {
      getUINativeModule().text.resetMaxFontScale(node);
    }
    else {
      getUINativeModule().text.setMaxFontScale(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMaxFontScaleModifier.identity = Symbol('textMaxFontScale');
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
class TextMaxLineHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMaxLineHeight(node);
    } else {
      getUINativeModule().text.setMaxLineHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMaxLineHeightModifier.identity = Symbol('textMaxLineHeight');
class TextMinLineHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMinLineHeight(node);
    } else {
      getUINativeModule().text.setMinLineHeight(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMinLineHeightModifier.identity = Symbol('textMinLineHeight');
class TextLineHeightMultipleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLineHeightMultiple(node);
    } else {
      getUINativeModule().text.setLineHeightMultiple(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextLineHeightMultipleModifier.identity = Symbol('textLineHeightMultiple');
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
class TextMinLinesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMinLines(node);
    } else {
      getUINativeModule().text.setMinLines(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMinLinesModifier.identity = Symbol('textMinLines');
class TextLetterSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLetterSpacing(node);
    }
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
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
class TextLineSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetLineSpacing(node);
    }
    else if (!isObject(this.value)) {
      getUINativeModule().text.resetLineSpacing(node);
    }
    else {
      getUINativeModule().text.setLineSpacing(node, this.value.value, this.value.onlyBetweenLines);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextLineSpacingModifier.identity = Symbol('textLineSpacing');

class TextOrphanCharOptimizationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOrphanCharOptimization(node);
    }
    else {
      getUINativeModule().text.setOrphanCharOptimization(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextOrphanCharOptimizationModifier.identity = Symbol('textOrphanCharOptimization');

class TextCompressLeadingPunctuationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetCompressLeadingPunctuation(node);
    }
    else {
      getUINativeModule().text.setCompressLeadingPunctuation(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextCompressLeadingPunctuationModifier.identity = Symbol('textCompressLeadingPunctuation');

class TextPunctuationOverflowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetPunctuationOverflow(node);
    }
    else {
      getUINativeModule().text.setPunctuationOverflow(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextPunctuationOverflowModifier.identity = Symbol('textPunctuationOverflow');

class TextOptimizeTrailingSpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOptimizeTrailingSpace(node);
    }
    else {
      getUINativeModule().text.setOptimizeTrailingSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextOptimizeTrailingSpaceModifier.identity = Symbol('textOptimizeTrailingSpace');
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
    else if (!isNumber(this.value) && !isString(this.value) && !isResource(this.value)) {
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
      getUINativeModule().text.setDecoration(node, this.value.type, this.value.color,
                                             this.value.style, this.value.thicknessScale);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.type !== this.value.type || this.stageValue.style !== this.value.style ||
        this.stageValue.thicknessScale !== this.value.thicknessScale) {
      return true;
    }
    if (!isResource(this.stageValue.color) && !isResource(this.value.color)) {
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
      getUINativeModule().text.setFont(node, this.value.value.size, this.value.value.weight, this.value.value.family,
        this.value.value.style, this.value.enableVariableFontWeight);
    }
  }
  checkObjectDiff() {
    if (this.stageValue.weight !== this.value.weight || this.stageValue.style !== this.value.style ||
      this.stageValue.enableVariableFontWeight !== this.value.enableVariableFontWeight) {
      return true;
    }
    if ((!isResource(this.stageValue.size) && !isResource(this.value.size) &&
      this.stageValue.size === this.value.size) &&
      (!isResource(this.stageValue.family) && !isResource(this.value.family) &&
        this.stageValue.family === this.value.family)) {
      return false;
    }
    else {
      return true;
    }
  }
}
TextFontModifier.identity = Symbol('textFont');
class TextClipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    }
    else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
TextClipModifier.identity = Symbol('textClip');

class TextContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.setContent(node, '');
    }
    else {
      getUINativeModule().text.setContent(node, this.value);
    }
  }
}
TextContentModifier.identity = Symbol('textContent');
class TextControllerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.setTextController(node, '');
    }
    else {
      getUINativeModule().text.setTextController(node, this.value);
    }
  }
}
TextControllerModifier.identity = Symbol('textController');
class TextSelectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetSelection(node);
    } else {
      getUINativeModule().text.setSelection(node, this.value.selectionStart, this.value.selectionEnd);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.selectionStart, this.value.selectionStart) ||
    !isBaseOrResourceEqual(this.stageValue.selectionEnd, this.value.selectionEnd);
  }
}
TextSelectionModifier.identity = Symbol('textSelection');
class TextSelectableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextSelectableMode(node);
    } else {
      getUINativeModule().text.setTextSelectableMode(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextSelectableModifier.identity = Symbol('textTextSelectable');
class TextCaretColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetCaretColor(node);
    } else {
      getUINativeModule().text.setCaretColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextCaretColorModifier.identity = Symbol('textCaretColor');
class TextSelectedBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetSelectedBackgroundColor(node);
    } else {
      getUINativeModule().text.setSelectedBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextSelectedBackgroundColorModifier.identity = Symbol('textSelectedBackgroundColor');
class TextDataDetectorConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetDataDetectorConfig(node);
    } else {
      getUINativeModule().text.setDataDetectorConfig(node, this.value.types, this.value.onDetectResultUpdate,
        this.value.color, this.value.decorationType, this.value.decorationColor, this.value.decorationStyle, this.value.enablePreviewMenu);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.types, this.value.types) ||
    !isBaseOrResourceEqual(this.stageValue.onDetectResultUpdate, this.value.onDetectResultUpdate) ||
    !isBaseOrResourceEqual(this.stageValue.color, this.value.color) ||
    !isBaseOrResourceEqual(this.stageValue.decorationType, this.value.decorationType) ||
    !isBaseOrResourceEqual(this.stageValue.decorationColor, this.value.decorationColor) ||
    !isBaseOrResourceEqual(this.stageValue.decorationStyle, this.value.decorationStyle) ||
    !isBaseOrResourceEqual(this.stageValue.enablePreviewMenu, this.value.enablePreviewMenu);
  }
}
TextDataDetectorConfigModifier.identity = Symbol('textDataDetectorConfig');
class TextSelectDetectorEnableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetSelectDetectorEnable(node);
    } else {
      getUINativeModule().text.setSelectDetectorEnable(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextSelectDetectorEnableModifier.identity = Symbol('textSelectDetectorEnable');
class TextOnWillCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOnWillCopy(node);
    } else {
      getUINativeModule().text.setOnWillCopy(node, this.value);
    }
  }
}
TextOnWillCopyModifier.identity = Symbol('textOnWillCopy');
class TextOnCopyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOnCopy(node);
    } else {
      getUINativeModule().text.setOnCopy(node, this.value);
    }
  }
}
TextOnCopyModifier.identity = Symbol('textOnCopy');
class TextOnTextSelectionChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOnTextSelectionChange(node);
    } else {
      getUINativeModule().text.setOnTextSelectionChange(node, this.value);
    }
  }
}
TextOnTextSelectionChangeModifier.identity = Symbol('textOnTextSelectionChange');

class TextEditMenuOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetSelectionMenuOptions(node);
    } else {
      getUINativeModule().text.setSelectionMenuOptions(node, this.value);
    }
  }
}
TextEditMenuOptionsModifier.identity = Symbol('textEditMenuOptions');

class TextHalfLeadingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetHalfLeading(node);
    }
    else {
      getUINativeModule().text.setHalfLeading(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextHalfLeadingModifier.identity = Symbol('textHalfLeading');

class TextOnClickModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOnClick(node);
    }
    else {
      getUINativeModule().text.setOnClick(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextOnClickModifier.identity = Symbol('textOnClick');

class TextMarqueeOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetMarqueeOptions(node);
    } else {
      getUINativeModule().text.setMarqueeOptions(node, this.value.start, this.value.fromStart, this.value.step,
        this.value.loop, this.value.delay, this.value.fadeout, this.value.marqueeStartPolicy,
        this.value.marqueeUpdatePolicy, this.value.spacing);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextMarqueeOptionsModifier.identity = Symbol('textMarqueeOptions');
class TextOnMarqueeStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetOnMarqueeStateChange(node);
    } else {
      getUINativeModule().text.setOnMarqueeStateChange(node, this.value);
    }
  }
}
TextOnMarqueeStateChangeModifier.identity = Symbol('textOnMarqueeStateChange');

class TextResponseRegionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    let _a, _b, _c, _d, _e, _f, _g, _h;
    if (reset) {
      getUINativeModule().text.resetResponseRegion(node);
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
      getUINativeModule().text.setResponseRegion(node, responseRegion, responseRegion.length);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextResponseRegionModifier.identity = Symbol('textResponseRegion');

class TextEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().text.setEnableHapticFeedback(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextEnableHapticFeedbackModifier.identity = Symbol('textEnableHapticFeedback');

class TextEnableAutoSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetEnableAutoSpacing(node);
    }
    else {
      getUINativeModule().text.setEnableAutoSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextEnableAutoSpacingModifier.identity = Symbol('textEnableAutoSpacing');

class TextIncludeFontPaddingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetIncludeFontPadding(node);
    }
    else {
      getUINativeModule().text.setIncludeFontPadding(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextIncludeFontPaddingModifier.identity = Symbol('textIncludeFontPadding');

class TextFallbackLineSpacingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetFallbackLineSpacing(node);
    }
    else {
      getUINativeModule().text.setFallbackLineSpacing(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextFallbackLineSpacingModifier.identity = Symbol('textFallbackLineSpacing');

class TextShaderStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetShaderStyle(node, this.value);
    } else {
      if (this.value.options) {
        getUINativeModule().text.setShaderStyle(node, this.value.options.center, this.value.options.radius, this.value.options.angle,
          this.value.options.direction, this.value.options.repeating, this.value.options.colors, this.value.options.color);
      } else {
        getUINativeModule().text.setShaderStyle(node, this.value.center, this.value.radius, this.value.angle,
          this.value.direction, this.value.repeating, this.value.colors, this.value.color);
      }
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextShaderStyleModifier.identity = Symbol('textShaderStyle');

class TextVerticalAlignModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextVerticalAlign(node);
    }
    else {
      getUINativeModule().text.setTextVerticalAlign(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextVerticalAlignModifier.identity = Symbol('textVerticalAlignIdentity');

class TextContentTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextContentTransition(node);
    }
    else {
      getUINativeModule().text.setTextContentTransition(node, this.value.flipDirection, this.value.enableBlur);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.flipDirection, this.value.flipDirection) ||
      !isBaseOrResourceEqual(this.stageValue.enableBlur, this.value.enableBlur);
  }
}
TextContentTransitionModifier.identity = Symbol('textContentTransition');

class TextDirectionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTextDirection(node);
    }
    else {
      getUINativeModule().text.setTextDirection(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextDirectionModifier.identity = Symbol('textDirection');

class TextIncrementalUpdatePolicyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetIncrementalUpdatePolicy(node);
    }
    else {
      getUINativeModule().text.setIncrementalUpdatePolicy(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
TextIncrementalUpdatePolicyModifier.identity = Symbol('textIncrementalUpdatePolicy');

class TextSelectedDragPreviewStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetSelectedDragPreviewStyle(node);
    }
    else {
      getUINativeModule().text.setSelectedDragPreviewStyle(node, this.value.color);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value) ||
    !isBaseOrResourceEqual(this.stageValue.color, this.value.color);
  }
}
TextSelectedDragPreviewStyleModifier.identity = Symbol('textSelectedDragPreviewStyle');

class TextTailIndentsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().text.resetTailIndents(node);
    } else {
      getUINativeModule().text.setTailIndents(node, this.value);
    }
  }
  checkObjectDiff() {
    if (!Array.isArray(this.stageValue) && !Array.isArray(this.value)) {
      return !isBaseOrResourceEqual(this.stageValue, this.value);
    }
    if (Array.isArray(this.stageValue) && Array.isArray(this.value)) {
      if (this.stageValue.length !== this.value.length) {
        return true;
      }
      for (let i = 0; i < this.value.length; i++) {
        if (!isBaseOrResourceEqual(this.stageValue[i], this.value[i])) {
          return true;
        }
      }
      return false;
    }
    return false;
  }
}
TextTailIndentsModifier.identity = Symbol('textTailIndents');

class ArkTextComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(content) {
    modifierWithKey(this._modifiersWithKeys, TextContentModifier.identity, TextContentModifier, content[0]);
    modifierWithKey(this._modifiersWithKeys, TextControllerModifier.identity, TextControllerModifier, content[1]);
    return this;
  }
  allowChildTypes() {
    return ["Span", "ImageSpan", "SymbolSpan", "ContainerSpan"];
  }
  enableDataDetector(value) {
    modifierWithKey(this._modifiersWithKeys, TextEnableDataDetectorModifier.identity, TextEnableDataDetectorModifier, value);
    return this;
  }
  dataDetectorConfig(config) {
    if (config === undefined || config === null) {
      return this;
    }
    let detectorConfig = new TextDataDetectorConfig();
    detectorConfig.types = config.types;
    detectorConfig.onDetectResultUpdate = config.onDetectResultUpdate;
    detectorConfig.color = config.color;
    if (config.decoration) {
      detectorConfig.decorationType = config.decoration.type;
      detectorConfig.decorationColor = config.decoration.color;
      detectorConfig.decorationStyle = config.decoration.style;
    }
    detectorConfig.enablePreviewMenu = config.enablePreviewMenu;
    modifierWithKey(this._modifiersWithKeys, TextDataDetectorConfigModifier.identity, TextDataDetectorConfigModifier, detectorConfig);
    return this;
  }
  enableSelectedDataDetector(value) {
    modifierWithKey(this._modifiersWithKeys, TextSelectDetectorEnableModifier.identity, TextSelectDetectorEnableModifier, value);
    return this;
  }
  font(value, options) {
    if (value === undefined || value === null) {
      return this;
    }
    let arkTextFont = new ArkTextFont();
    arkTextFont.value = value;
    arkTextFont.enableVariableFontWeight = options?.enableVariableFontWeight;
    modifierWithKey(this._modifiersWithKeys, TextFontModifier.identity, TextFontModifier, arkTextFont);
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
  minFontScale(value) {
    modifierWithKey(this._modifiersWithKeys, TextMinFontScaleModifier.identity, TextMinFontScaleModifier, value);
    return this;
  }
  maxFontScale(value) {
    modifierWithKey(this._modifiersWithKeys, TextMaxFontScaleModifier.identity, TextMaxFontScaleModifier, value);
    return this;
  }
  fontStyle(value) {
    modifierWithKey(this._modifiersWithKeys, FontStyleModifier.identity, FontStyleModifier, value);
    return this;
  }
  fontWeight(value, options) {
    let arkFontWeight = new ArkFontWeight();
    arkFontWeight.value = value;
    arkFontWeight.enableVariableFontWeight = options?.enableVariableFontWeight;
    modifierWithKey(this._modifiersWithKeys, FontWeightModifier.identity, FontWeightModifier, arkFontWeight);
    return this;
  }
  textAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextAlignModifier.identity, TextAlignModifier, value);
    return this;
  }
  textContentAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextContentAlignModifier.identity, TextContentAlignModifier, value);
    return this;
  }
  lineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextLineHeightModifier.identity, TextLineHeightModifier, value);
    return this;
  }
  maxLineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextMaxLineHeightModifier.identity, TextMaxLineHeightModifier, value);
    return this;
  }
  minLineHeight(value) {
    modifierWithKey(this._modifiersWithKeys, TextMinLineHeightModifier.identity, TextMinLineHeightModifier, value);
    return this;
  }
  lineHeightMultiple(value) {
    modifierWithKey(this._modifiersWithKeys, TextLineHeightMultipleModifier.identity, TextLineHeightMultipleModifier, value);
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
  minLines(value) {
    modifierWithKey(this._modifiersWithKeys, TextMinLinesModifier.identity, TextMinLinesModifier, value);
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
  lineSpacing(value, options) {
    let arkLineSpacing = new ArkLineSpacing();
    arkLineSpacing.value = value;
    arkLineSpacing.onlyBetweenLines = options?.onlyBetweenLines;
    modifierWithKey(this._modifiersWithKeys, TextLineSpacingModifier.identity, TextLineSpacingModifier, arkLineSpacing);
    return this;
  }
  orphanCharOptimization(value) {
    modifierWithKey(this._modifiersWithKeys, TextOrphanCharOptimizationModifier.identity,
      TextOrphanCharOptimizationModifier, value);
    return this;
  }
  compressLeadingPunctuation(value) {
    modifierWithKey(this._modifiersWithKeys, TextCompressLeadingPunctuationModifier.identity,
      TextCompressLeadingPunctuationModifier, value);
    return this;
  }
  punctuationOverflow(value) {
    modifierWithKey(this._modifiersWithKeys, TextPunctuationOverflowModifier.identity,
      TextPunctuationOverflowModifier, value);
    return this;
  }
  optimizeTrailingSpace(value) {
    modifierWithKey(this._modifiersWithKeys, TextOptimizeTrailingSpaceModifier.identity,
      TextOptimizeTrailingSpaceModifier, value);
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
  privacySensitive(value) {
    modifierWithKey(this._modifiersWithKeys, TextPrivacySensitiveModifier.identity, TextPrivacySensitiveModifier, value);
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
    modifierWithKey(this._modifiersWithKeys, TextWordBreakModifier.identity, TextWordBreakModifier, value);
    return this;
  }
  lineBreakStrategy(value) {
    modifierWithKey(this._modifiersWithKeys, TextLineBreakStrategyModifier.identity,
      TextLineBreakStrategyModifier, value);
    return this;
  }
  fontFeature(value) {
    modifierWithKey(this._modifiersWithKeys, TextFontFeatureModifier.identity, TextFontFeatureModifier, value);
    return this;
  }
  fontVariations(value) {
    modifierWithKey(this._modifiersWithKeys, TextFontVariationsModifier.identity, TextFontVariationsModifier, value);
    return this;
  }
  onWillCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, TextOnWillCopyModifier.identity,
      TextOnWillCopyModifier, callback);
    return this;
  }
  onCopy(callback) {
    modifierWithKey(this._modifiersWithKeys, TextOnCopyModifier.identity,
      TextOnCopyModifier, callback);
    return this;
  }
  selection(selectionStart, selectionEnd) {
    let arkSelection = new ArkSelection();
    arkSelection.selectionStart = selectionStart;
    arkSelection.selectionEnd = selectionEnd;
    modifierWithKey(this._modifiersWithKeys, TextSelectionModifier.identity, TextSelectionModifier, arkSelection);
    return this;
  }
  textSelectable(value) {
    modifierWithKey(this._modifiersWithKeys, TextSelectableModifier.identity, TextSelectableModifier, value);
    return this;
  }
  caretColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextCaretColorModifier.identity, TextCaretColorModifier, value);
    return this;
  }
  selectedBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, TextSelectedBackgroundColorModifier.identity,
      TextSelectedBackgroundColorModifier, value);
    return this;
  }
  ellipsisMode(value) {
    modifierWithKey(this._modifiersWithKeys, TextEllipsisModeModifier.identity, TextEllipsisModeModifier, value);
    return this;
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, TextClipModifier.identity, TextClipModifier, value);
    return this;
  }
  foregroundColor(value) {
    modifierWithKey(
      this._modifiersWithKeys, TextForegroundColorModifier.identity, TextForegroundColorModifier, value);
    return this;
  }
  onTextSelectionChange(callback) {
    modifierWithKey(this._modifiersWithKeys, TextOnTextSelectionChangeModifier.identity,
      TextOnTextSelectionChangeModifier, callback);
    return this;
  }
  marqueeOptions(value) {
    modifierWithKey(this._modifiersWithKeys, TextMarqueeOptionsModifier.identity,
      TextMarqueeOptionsModifier, value);
    return this;
  }
  onMarqueeStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, TextOnMarqueeStateChangeModifier.identity,
      TextOnMarqueeStateChangeModifier, callback);
    return this;
  }
  editMenuOptions(value) {
    modifierWithKey(this._modifiersWithKeys, TextEditMenuOptionsModifier.identity,
      TextEditMenuOptionsModifier, value);
    return this;
  }
  halfLeading(value) {
    modifierWithKey(this._modifiersWithKeys, TextHalfLeadingModifier.identity, TextHalfLeadingModifier, value);
    return this;
  }
  onClick(value) {
    modifierWithKey(this._modifiersWithKeys, TextOnClickModifier.identity, TextOnClickModifier, value);
    return this;
  }
  responseRegion(value) {
    modifierWithKey(this._modifiersWithKeys, TextResponseRegionModifier.identity, TextResponseRegionModifier, value);
    return this;
  }
  enableHapticFeedback(value) {
    modifierWithKey(this._modifiersWithKeys, TextEnableHapticFeedbackModifier.identity, TextEnableHapticFeedbackModifier, value);
    return this;
  }
  enableAutoSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, TextEnableAutoSpacingModifier.identity, TextEnableAutoSpacingModifier, value);
    return this;
  }
  includeFontPadding(value) {
    modifierWithKey(this._modifiersWithKeys, TextIncludeFontPaddingModifier.identity, TextIncludeFontPaddingModifier, value);
    return this;
  }
  fallbackLineSpacing(value) {
    modifierWithKey(this._modifiersWithKeys, TextFallbackLineSpacingModifier.identity, TextFallbackLineSpacingModifier, value);
    return this;
  }
  shaderStyle(value) {
    modifierWithKey(this._modifiersWithKeys, TextShaderStyleModifier.identity, TextShaderStyleModifier, value);
    return this;
  }
  textVerticalAlign(value) {
    modifierWithKey(this._modifiersWithKeys, TextVerticalAlignModifier.identity, TextVerticalAlignModifier, value);
    return this;
  }
  contentTransition(value) {
    modifierWithKey(this._modifiersWithKeys, TextContentTransitionModifier.identity, TextContentTransitionModifier, value);
    return this;
  }
  textDirection(value) {
    modifierWithKey(this._modifiersWithKeys, TextDirectionModifier.identity, TextDirectionModifier, value);
    return this;
  }
  selectedDragPreviewStyle(value) {
    let arkSelectedDragPreviewStyle = new ArkSelectedDragPreviewStyle();
    arkSelectedDragPreviewStyle.color = value?.color;
    modifierWithKey(this._modifiersWithKeys, TextSelectedDragPreviewStyleModifier.identity,
        TextSelectedDragPreviewStyleModifier, arkSelectedDragPreviewStyle);
    return this;
  }
  incrementalUpdatePolicy(value) {
    modifierWithKey(this._modifiersWithKeys, TextIncrementalUpdatePolicyModifier.identity,
        TextIncrementalUpdatePolicyModifier, value);
    return this;
  }
  tailIndents(value) {
    modifierWithKey(this._modifiersWithKeys, TextTailIndentsModifier.identity, TextTailIndentsModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Text !== undefined) {
  globalThis.Text.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkTextComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.TextModifier(nativePtr, classType);
    });
  };
}

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
class VideoOpacityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOpacity(node);
    }
    else {
      getUINativeModule().video.setOpacity(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoOpacityModifier.identity = Symbol('videoOpacity');
class VideoSurfaceBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetVideoSurfaceBackgroundColor(node);
    }
    else {
      getUINativeModule().video.setVideoSurfaceBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoSurfaceBackgroundColorModifier.identity = Symbol('videoSurfaceBackgroundColor');
class VideoTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetTransition(node);
    }
    else {
      getUINativeModule().video.setTransition(node, this.value.transitionEffect, this.value.callback);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
VideoTransitionModifier.identity = Symbol('videoTransition');
class VideoEnableShortcutKeyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetShortcutKeyEnabled(node);
    } else {
      getUINativeModule().video.setShortcutKeyEnabled(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoEnableShortcutKeyModifier.identity = Symbol('videoEnableShortcutKey');

class VideoOnStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnStart(node);
    } else {
      getUINativeModule().video.setOnStart(node, this.value);
    }
  }
}
VideoOnStartModifier.identity = Symbol('videoOnStart');

class VideoOnPauseModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnPause(node);
    } else {
      getUINativeModule().video.setOnPause(node, this.value);
    }
  }
}
VideoOnPauseModifier.identity = Symbol('videoOnPause');

class VideoOnFinishModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnFinish(node);
    } else {
      getUINativeModule().video.setOnFinish(node, this.value);
    }
  }
}
VideoOnFinishModifier.identity = Symbol('videoOnFinish');

class VideoOnFullscreenChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnFullscreenChange(node);
    } else {
      getUINativeModule().video.setOnFullscreenChange(node, this.value);
    }
  }
}
VideoOnFullscreenChangeModifier.identity = Symbol('videoOnFullscreenChange');

class VideoOnPreparedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnPrepared(node);
    } else {
      getUINativeModule().video.setOnPrepared(node, this.value);
    }
  }
}
VideoOnPreparedModifier.identity = Symbol('videoOnPrepared');

class VideoOnSeekingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnSeeking(node);
    } else {
      getUINativeModule().video.setOnSeeking(node, this.value);
    }
  }
}
VideoOnSeekingModifier.identity = Symbol('videoOnSeeking');

class VideoOnSeekedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnSeeked(node);
    } else {
      getUINativeModule().video.setOnSeeked(node, this.value);
    }
  }
}
VideoOnSeekedModifier.identity = Symbol('videoOnSeeked');

class VideoOnUpdateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnUpdate(node);
    } else {
      getUINativeModule().video.setOnUpdate(node, this.value);
    }
  }
}
VideoOnUpdateModifier.identity = Symbol('videoOnUpdate');

class VideoOnErrorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnError(node);
    } else {
      getUINativeModule().video.setOnError(node, this.value);
    }
  }
}
VideoOnErrorModifier.identity = Symbol('videoOnError');

class VideoOnStopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetOnStop(node);
    } else {
      getUINativeModule().video.setOnStop(node, this.value);
    }
  }
}
VideoOnStopModifier.identity = Symbol('videoOnStop');

class VideoEnableAnalyzerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetEnableAnalyzer(node);
    } else {
      getUINativeModule().video.setEnableAnalyzer(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoEnableAnalyzerModifier.identity = Symbol('videoEnableAnalyzer');

class VideoAnalyzerConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().video.resetAnalyzerConfig(node);
    } else {
      getUINativeModule().video.setAnalyzerConfig(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
VideoAnalyzerConfigModifier.identity = Symbol('videoAnalyzerConfig');

class ArkVideoComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  muted(value) {
    modifierWithKey(this._modifiersWithKeys, VideoMutedModifier.identity, VideoMutedModifier, value);
    return this;
  }
  autoPlay(value) {
    modifierWithKey(this._modifiersWithKeys, VideoAutoPlayModifier.identity, VideoAutoPlayModifier, value);
    return this;
  }
  surfaceBackgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, VideoSurfaceBackgroundColorModifier.identity,
      VideoSurfaceBackgroundColorModifier, value);
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
  enableShortcutKey(value) {
    modifierWithKey(this._modifiersWithKeys, VideoEnableShortcutKeyModifier.identity, VideoEnableShortcutKeyModifier, value);
    return this;
  }
  opacity(value) {
    modifierWithKey(this._modifiersWithKeys, VideoOpacityModifier.identity, VideoOpacityModifier, value);
    return this;
  }
  transition(value, callback) {
    let arkTransition = new ArkTransition();
    arkTransition.transitionEffect = value;
    if (typeof callback === 'function') {
      arkTransition.callback = callback;
    }
    modifierWithKey(this._modifiersWithKeys, VideoTransitionModifier.identity, VideoTransitionModifier, arkTransition);
    return this;
  }
  onStart(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnStartModifier.identity, VideoOnStartModifier, callback);
    return this;
  }
  onPause(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnPauseModifier.identity, VideoOnPauseModifier, callback);
    return this;
  }
  onFinish(event) {
    modifierWithKey(this._modifiersWithKeys, VideoOnFinishModifier.identity, VideoOnFinishModifier, event);
    return this;
  }
  onFullscreenChange(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnFullscreenChangeModifier.identity,
      VideoOnFullscreenChangeModifier, callback);
    return this;
  }
  onPrepared(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnPreparedModifier.identity, VideoOnPreparedModifier, callback);
    return this;
  }
  onSeeking(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekingModifier.identity, VideoOnSeekingModifier, callback);
    return this;
  }
  onSeeked(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekedModifier.identity, VideoOnSeekedModifier, callback);
    return this;
  }
  onUpdate(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnUpdateModifier.identity, VideoOnUpdateModifier, callback);
    return this;
  }
  onError(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnErrorModifier.identity, VideoOnErrorModifier, callback);
    return this;
  }
  onStop(callback) {
    modifierWithKey(this._modifiersWithKeys, VideoOnStopModifier.identity, VideoOnStopModifier, callback);
    return this;
  }
  enableAnalyzer(enable) {
    modifierWithKey(this._modifiersWithKeys, VideoEnableAnalyzerModifier.identity, VideoEnableAnalyzerModifier, enable);
    return this;
  }
  analyzerConfig(config) {
    modifierWithKey(this._modifiersWithKeys, VideoAnalyzerConfigModifier.identity, VideoAnalyzerConfigModifier, config);
    return this;
  }
}
// @ts-ignore
if (globalThis.Video !== undefined) {
  globalThis.Video.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkVideoComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.VideoModifier(nativePtr, classType);
    });
  };
}

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
    this.startColor = undefined;
    this.endColor = undefined;
    this.leftColor = undefined;
    this.rightColor = undefined;
    this.topColor = undefined;
    this.bottomColor = undefined;
  }
  isEqual(another) {
    return (this.leftColor === another.leftColor &&
      this.rightColor === another.rightColor &&
      this.topColor === another.topColor &&
      this.bottomColor === another.bottomColor &&
      this.startColor === another.startColor &&
      this.endColor === another.endColor);
  }
}
class ArkBorderWidth {
  constructor() {
    this.start = undefined;
    this.end = undefined;
    this.left = undefined;
    this.right = undefined;
    this.top = undefined;
    this.bottom = undefined;
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.right === another.right &&
      this.top === another.top &&
      this.bottom === another.bottom &&
      this.start === another.start &&
      this.end === another.end);
  }
}
class ArkBorderRadius {
  constructor() {
    this.topStart = undefined;
    this.topEnd = undefined;
    this.bottomStart = undefined;
    this.bottomEnd = undefined;
    this.topLeft = undefined;
    this.topRight = undefined;
    this.bottomLeft = undefined;
    this.bottomRight = undefined;
  }
  isEqual(another) {
    if (this == undefined && another == undefined) {
      return true;
    }
    if ((this == undefined && another != undefined) || (this != undefined && another == undefined)) {
      return false
    }
    return (this.topLeft === another.topLeft &&
      this.topRight === another.topRight &&
      this.bottomLeft === another.bottomLeft &&
      this.bottomRight === another.bottomRight &&
      this.topStart === another.topStart &&
      this.topEnd === another.topEnd &&
      this.bottomStart === another.bottomStart &&
      this.bottomEnd === another.bottomEnd);
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
  constructor(center, start, end, rotation, colors, metricsColors, repeating) {
    this.center = center;
    this.start = start;
    this.end = end;
    this.rotation = rotation;
    this.colors = colors;
    this.metricsColors = metricsColors;
    this.repeating = repeating;
  }
  isEqual(another) {
    return (deepCompareArrays(this.center, another.center) &&
      this.start === another.start &&
      this.end === another.end &&
      this.rotation === another.rotation &&
      deepCompareArrays(this.colors, another.colors) &&
      deepCompareArrays(this.metricsColors, another.metricsColors) &&
      this.repeating === another.repeating);
  }
}
class ArkForegroundBlurStyle {
  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
    this.blurOptions = undefined;
    this.disableSystemAdaptation = undefined;
  }
  isEqual(another) {
    return (this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale &&
      this.blurOptions === another.blurOptions &&
      this.disableSystemAdaptation === another.disableSystemAdaptation);
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
class ArkCustomKeyboard {
  constructor() {
    this.value = undefined;
    this.supportAvoidance = undefined;
  }
  isEqual(another) {
    return ((this.value === another.value) && (this.supportAvoidance === another.supportAvoidance));
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
class ArkTransition {
  constructor() {
    this.transitionEffect = undefined;
    this.callback = undefined;
  }
  isEqual(another) {
    return (this.transitionEffect === another.transitionEffect) && (this.callback === another.callback);
  }
}
class ArkEdgeEffect {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkFadingEdge {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.options === another.options);
  }
}
class ArkBlurOptions {
  constructor() {
    this.value = undefined;
    this.options = undefined;
    this.disableSystemAdaptation = undefined;
  }
}
class ArkBackgroundEffect {
  constructor() {
    this.radius = undefined;
    this.saturation = undefined;
    this.brightness = undefined;
    this.color = undefined;
    this.adaptiveColor = undefined;
    this.blurOptions = undefined;
    this.policy = undefined;
    this.inactiveColor = undefined;
    this.disableSystemAdaptation = undefined;
  }
}
class InvertOptions {
  constructor() {
    this.high = undefined;
    this.low = undefined;
    this.threshold = undefined;
    this.thresholdRange = undefined;
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

class ArkSelection {
  constructor() {
    this.selectionStart = undefined;
    this.selectionEnd = undefined;
  }
  isEqual(another) {
    return this.selectionStart === another.selectionStart &&
      this.selectionEnd === another.selectionEnd;
  }
}

class TextDataDetectorConfig {
  constructor() {
    this.types = undefined;
    this.onDetectResultUpdate = undefined;
    this.color = undefined;
    this.decorationType = undefined;
    this.decorationColor = undefined;
    this.decorationStyle = undefined;
    this.enablePreviewMenu = undefined;
  }
  isEqual(another) {
    return (this.types === another.types) && (this.onDetectResultUpdate === another.onDetectResultUpdate) &&
    (this.color === another.color) && (this.decorationType === another.decorationType) &&
    (this.decorationColor=== another.decorationColor) && (this.decorationStyle === another.decorationStyle) &&
    (this.enablePreviewMenu === another.enablePreviewMenu);
  }
}
class BlankScreenDetectionConfig {
  constructor() {
    this.enable = undefined;
    this.detectionTiming = undefined;
    this.detectionMethods = undefined;
    this.contentfulNodesCountThreshold = undefined;
  }
  isEqual(another) {
    return (this.enable === another.enable) && (this.detectionTiming === another.detectionTiming) &&
    (this.detectionMethods === another.detectionMethods) &&
    (this.contentfulNodesCountThreshold === another.contentfulNodesCountThreshold);
  }
}
class ArkOnVisibleAreaChange {
  constructor(ratios, event, measureFromViewport) {
    this.ratios = ratios;
    this.event = event;
    this.measureFromViewport = measureFromViewport;
  }
  isEqual(another) {
    return this.ratios === another.ratios && this.event === another.event && this.measureFromViewport === another.measureFromViewport;
  }
}
class ArkOnAreaChange {
  constructor(event, expectedUpdateInterval, hasOptionsArg = false) {
    this.event = event;
    this.expectedUpdateInterval = expectedUpdateInterval;
    this.hasOptionsArg = hasOptionsArg;
  }
  isEqual(another) {
    return this.event === another.event && this.expectedUpdateInterval === another.expectedUpdateInterval &&
      this.hasOptionsArg === another.hasOptionsArg;
  }
}

class ArkOnVisibleAreaApproximateChange {
  constructor(ratios, event, expectedUpdateInterval, measureFromViewport) {
    this.ratios = ratios;
    this.event = event;
    this.expectedUpdateInterval = expectedUpdateInterval;
    this.measureFromViewport = measureFromViewport;
  }
  isEqual(another) {
    return this.ratios === another.ratios && this.event === another.event && this.expectedUpdateInterval === another.expectedUpdateInterval
      && this.measureFromViewport === another.measureFromViewport;
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
class ArkRegisterNativeEmbedRule {
  constructor() {
    this.tag = undefined;
    this.type = undefined;
  }

  isEqual(another) {
    return (
      this.tag === another.tag &&
      this.type === another.type
    );
  }
}
class ArkBackground {
  constructor() {
    this.content = undefined;
    this.align = undefined;
    this.ignoresLayoutSafeAreaEdges = undefined;
  }
  isEqual(another) {
    return (
      this.content === another.content &&
      this.align === another.align &&
      deepCompareArrays(this.ignoresLayoutSafeAreaEdges, another.ignoresLayoutSafeAreaEdges)
    );
  }
}
class ArkBackgroundBlurStyle {
  constructor() {
    this.blurStyle = undefined;
    this.colorMode = undefined;
    this.adaptiveColor = undefined;
    this.scale = undefined;
    this.blurOptions = undefined;
    this.policy = undefined;
    this.inactiveColor = undefined;
    this.type = undefined;
    this.disableSystemAdaptation = undefined;
  }
  isEqual(another) {
    return (this.blurStyle === another.blurStyle &&
      this.colorMode === another.colorMode &&
      this.adaptiveColor === another.adaptiveColor &&
      this.scale === another.scale &&
      this.blurOptions === another.blurOptions &&
      this.policy === another.policy &&
      this.inactiveColor === another.inactiveColor &&
      this.type === another.type &&
      this.disableSystemAdaptation === another.disableSystemAdaptation);
  }
}
class ArkBorderDashGap {
  constructor() {
    this.left = undefined;
    this.right = undefined;
    this.top = undefined;
    this.bottom = undefined;
    this.start = undefined;
    this.end = undefined;
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.right === another.right &&
      this.top === another.top &&
      this.bottom === another.bottom &&
      this.start === another.start &&
      this.end === another.end);
  }
}
class ArkBorderDashWidth {
  constructor() {
    this.left = undefined;
    this.right = undefined;
    this.top = undefined;
    this.bottom = undefined;
    this.start = undefined;
    this.end = undefined;
  }
  isEqual(another) {
    return (this.left === another.left &&
      this.right === another.right &&
      this.top === another.top &&
      this.bottom === another.bottom &&
      this.start === another.start &&
      this.end === another.end);
  }
}
class ArkBorder {
  constructor() {
    this.arkWidth = new ArkBorderWidth();
    this.arkColor = new ArkBorderColor();
    this.arkRadius = new ArkBorderRadius();
    this.arkStyle = new ArkBorderStyle();
    this.arkDashGap = new ArkBorderDashGap();
    this.arkDashWidth = new ArkBorderDashWidth();
  }
  isEqual(another) {
    return (this.arkWidth.isEqual(another.arkWidth) &&
      this.arkColor.isEqual(another.arkColor) &&
      this.arkRadius.isEqual(another.arkRadius) &&
      this.arkStyle.isEqual(another.arkStyle) &&
      this.arkDashGap.isEqual(another.arkDashGap) &&
      this.arkDashWidth.isEqual(another.arkDashWidth));
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
class ArkTabsCachedMaxCount {
  isEqual(another) {
    return (this.value.count === another.count && this.value.mode === another.mode);
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
class ArkBorderRadiusOpts {
  constructor() {
    this.value = undefined;
    this.type = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) && (this.type === another.type);
  }
}
class ArkEnableStatusBar {
  constructor() {
    this.enable = undefined;
    this.animated = undefined;
  }
  isEqual(another) {
    return (this.enable === another.enable) && (this.animated === another.animated);
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
    if (!(isNumber(stageValue.radius) && isNumber(value.radius) &&
        stageValue.radius === value.radius)) {
      return true;
    }
    if (!(isNumber(stageValue.type) && isNumber(value.type) &&
      stageValue.type === value.type)) {
      return true;
    }
    if (!(!isResource(stageValue.color) && !isResource(value.color) &&
        stageValue.color === value.color)) {
      return true;
    }
    if (!(isNumber(stageValue.offsetX) && isNumber(value.offsetX) &&
        stageValue.offsetX === value.offsetX)) {
      return true;
    }
    if (!(isNumber(stageValue.offsetY) && isNumber(value.offsetY) &&
        stageValue.offsetY === value.offsetY)) {
      return true;
    }
    if (!(isBoolean(stageValue.fill) && isBoolean(value.fill) &&
      stageValue.fill === value.fill)) {
      return true;
    }
    return false;
  }
}
class ArkTextBackGroundStyle {
  constructor() {
    this.color = undefined;
    this.radius = new ArkBorderRadius();
  }
  isEqual(another) {
    return (this.color === another.color &&
      this.radius.isEqual(another.arkRadius));
  }
  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
  convertTextBackGroundStyleOptions(value) {
    let _a, _b, _c, _d;
    if (isUndefined(value)) {
      return false;
    }
    if (!isUndefined(value === null || value === void 0 ? void 0 : value.color) && (value === null || value === void 0 ? void 0 : value.color) !== null) {
      if (isNumber(value.color) || isString(value.color) || isResource(value.color)) {
        this.color = value.color;
      }
    }

    if (!isUndefined(value === null || value === void 0 ? void 0 : value.radius) && (value === null || value === void 0 ? void 0 : value.radius) !== null) {
      if (isNumber(value.radius) || isString(value.radius) || isResource(value.radius)) {
        this.radius.topLeft = value.radius;
        this.radius.topRight = value.radius;
        this.radius.bottomLeft = value.radius;
        this.radius.bottomRight = value.radius;
      }
      else {
        this.radius.topLeft = (_a = value.radius) === null || _a === void 0 ? void 0 : _a.topLeft;
        this.radius.topRight = (_b = value.radius) === null || _b === void 0 ? void 0 : _b.topRight;
        this.radius.bottomLeft = (_c = value.radius) === null || _c === void 0 ? void 0 : _c.bottomLeft;
        this.radius.bottomRight = (_d = value.radius) === null || _d === void 0 ? void 0 : _d.bottomRight;
      }
    }
    return true;
  }
}
class ArkSearchButton {
  constructor() {
    this.value = undefined;
    this.fontSize = undefined;
    this.fontColor = undefined;
    this.autoDisable = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.fontSize === another.fontSize) &&
      (this.fontColor === another.fontColor) &&
      (this.autoDisable === another.autoDisable);
  }
}
class ArkSearchInputFilter {
  constructor() {
    this.value = undefined;
    this.error = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
    (this.error === another.error);
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

class ArkCustomProperty {
  constructor() {
    this.key = undefined;
    this.value = undefined;
  }
}

class ArkUseEffect {
  constructor() {
    this.useEffect = undefined;
    this.effectType = undefined;
  }
  isEqual(another) {
    return (this.useEffect === another.useEffect) && (this.effectType === another.effectType);
  }
}

class ArkBlendMode {
  constructor() {
    this.blendMode = undefined;
    this.blendApplyType = undefined;
  }
  isEqual(another) {
    return (this.blendMode === another.blendMode) && (this.blendApplyType === another.blendApplyType);
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
class ArkEnableScrollDirectionalLock {
  constructor() {
    this.value = undefined;
    this.type = undefined;
  }
  isEqual(another) {
    return (this.value === another.value && this.type === another.type);
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
class ArkNestedScrollOptionsExt {
  constructor() {
    this.scrollUp = undefined;
    this.scrollDown = undefined;
    this.scrollLeft = undefined;
    this.scrollRight = undefined;
  }
  isEqual(another) {
    return (
          (this.scrollUp === another.scrollUp) &&
          (this.scrollDown === another.scrollDown) &&
          (this.scrollLeft === another.scrollLeft) &&
          (this.scrollRight === another.scrollRight)
      );
  }
}
class ArkWebScriptItem {
  constructor() {
    this.scripts = undefined;
    this.scriptRules = undefined;
  }

  isEqual(another) {
    return (
      this.scripts === another.scripts &&
      this.scriptRules === another.scriptRules
    );
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
class ArkTextFieldShowCounter {
  constructor() {
    this.value = undefined;
    this.highlightBorder = undefined;
    this.thresholdPercentage = undefined;
    this.counterTextColor = undefined;
    this.counterTextOverflowColor = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.highlightBorder === another.highlightBorder) &&
      (this.thresholdPercentage === another.thresholdPercentage) &&
      (this.counterTextColor === another.counterTextColor) &&
      (this.counterTextOverflowColor === another.counterTextOverflowColor);
  }
}

class ArkTextFieldMaxLines {
    constructor() {
      this.value = undefined;
      this.overflowMode = undefined;
    }
    isEqual(another) {
      return (this.value === another.value) &&
        (this.overflowMode === another.overflowMode);
    }
  }
class ArkTextInputFilter {
  constructor() {
    this.value = undefined;
    this.error = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.error === another.error);
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
    this.maxDisplayCountValue = undefined;
    this.spaceValue = undefined;
    this.ignoreSizeValue = undefined;
    this.indicatorIconValue = undefined;
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
      this.selectedColorValue === another.selectedColorValue &&
      this.maxDisplayCountValue === another.maxDisplayCountValue &&
      this.spaceValue === another.spaceValue &&
      this.ignoreSizeValue === another.ignoreSizeValue &&
      this.indicatorIconValue === another.indicatorIconValue);
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
    this.ignoreSizeValue = undefined;
  }
  isEqual(another) {
    return (this.type === another.type &&
      this.leftValue === another.leftValue &&
      this.topValue === another.topValue &&
      this.rightValue === another.rightValue &&
      this.bottomValue === another.bottomValue &&
      this.digitFontValue === another.digitFontValue &&
      this.selectedDigitFontValue === another.selectedDigitFontValue &&
      this.ignoreSizeValue === another.ignoreSizeValue);
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
class ArkAutoPlay {
  constructor() {
    this.autoPlay = undefined;
    this.needStopWhenTouched = undefined;
  }
  isEqual(another) {
    return this.autoPlay === another.autoPlay && this.needStopWhenTouched === another.needStopWhenTouched;
  }
}
class ArkDisplayCount {
  constructor() {
    this.value = undefined;
    this.swipeByGroup = undefined;
  }
  isEqual(another) {
    return this.value === another.value && this.swipeByGroup === another.swipeByGroup;
  }
}

class ArkSwiperCachedCount {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return this.value === another.value && this.options === another.options;
  }
}

class ArkPlaceholder {
  constructor() {
    this.value = undefined;
    this.style = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) &&
      (this.style === another.style);
  }
}

class ArkScrollableCacheOptions {
  constructor(count, show) {
    this.count = count;
    this.show = show;
  }
  isEqual(other) {
    return (this.count === other.count) &&
      (this.show === other.show);
  }
}
class ArkChainMode {
  constructor() {
    this.direction = undefined;
    this.style = undefined;
  }
  isEqual(another) {
    return (this.direction === another.direction) && (this.style === another.style);
  }
}
class ArkLanesOpt {
  constructor() {
    this.lanesNum = undefined;
    this.minLength = undefined;
    this.maxLength = undefined;
    this.fillType = undefined;
    this.gutter = undefined;
  }
  isEqual(another) {
    return (this.lanesNum === another.lanesNum && this.minLength === another.minLength
      && this.maxLength === another.maxLength&& this.fillType === another.fillType && this.gutter === another.gutter);
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
class ArkScrollOffsetOptions {
  constructor() {
    this.xOffset = undefined;
    this.yOffset = undefined;
  }
  isEqual(another) {
    return this.xOffset === another.xOffset && this.yOffset === another.yOffset;
  }
}

class ArkGeometryTransition {
  constructor() {
      this.id = undefined;
      this.options = undefined;
  }
  isEqual(another) {
      return (this.id === another.id && this.options === another.options);
  }
}
class ArkBindMenu{
  constructor() {
    this.content = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.content === another.content && this.options === another.options);
  }
}
class ArkBindTipsOptions {
  constructor() {
      this.message = undefined;
      this.options = undefined;
  }
  isEqual(another) {
      return (this.message === another.message && this.options === another.options);
  }
}
class ArkSymbolEffect {
  constructor() {
    this.symbolEffect = undefined;
    this.action = undefined;
  }
  isEqual(another) {
    return (this.symbolEffect === another.symbolEffect) &&
      (this.action === another.action);
  }
}
class ArkFocusScopeId {
  constructor() {
    this.id = undefined;
    this.isGroup = undefined;
    this.arrowStepOut = undefined;
  }
  isEqual(another) {
    return ((this.id === another.id) && (this.isGroup === another.isGroup) &&
      (this.arrowStepOut === another.arrowStepOut));
  }
}
class ArkFocusScopePriority {
  constructor() {
    this.scopeId = undefined;
    this.priority = undefined;
  }
  isEqual(another) {
    return (this.scopeId === another.scopeId) && (this.priority === another.priority);
  }
}
class ArkChainWeight {
  constructor() {
    this.horizontal = undefined;
    this.vertical = undefined;
  }
  isEqual(another) {
    return (
      this.horizontal === another.horizontal &&
      this.vertical === another.vertical
    );
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

class ArkDragPreviewOptions {
  constructor() {
    this.mode = undefined;
    this.numberBadge = undefined;
    this.sizeChangeEffect = undefined;
    this.isMultiSelectionEnabled = undefined;
    this.defaultAnimationBeforeLifting = undefined;
    this.enableEdgeAutoScroll = undefined;
    this.enableHapticFeedback = undefined;
    this.isLiftingDisabled = undefined;
  }

  isEqual(another) {
    return (
      this.mode === another.mode &&
      this.numberBadge === another.numberBadge &&
      this.sizeChangeEffect === another.sizeChangeEffect &&
      this.isMultiSelectionEnabled === another.isMultiSelectionEnabled &&
      this.defaultAnimationBeforeLifting === another.defaultAnimationBeforeLifting &&
      this.enableEdgeAutoScroll === another.enableEdgeAutoScroll &&
      this.enableHapticFeedback === another.enableHapticFeedback &&
      this.isLiftingDisabled === another.isLiftingDisabled
    );
  }
}

class ArkDragPreview {
  constructor() {
    this.inspectorId = undefined;
    this.onlyForLifting = false;
    this.pixelMap = undefined;
    this.extraInfo = undefined;
  }

  isEqual(another) {
    return (
      this.inspectorId === another.inspectorId &&
      this.onlyForLifting === another.onlyForLifting &&
      this.pixelMap === another.pixelMap &&
      this.extraInfo === another.extraInfo
    );
  }
}

class ArkShadowStyle {
  constructor() {
    this.shadowStyle = undefined;
  }
}

class ArkOnDrop {
  constructor() {
    this.event = undefined;
    this.disableDataPrefetch = false;
  }

  isEqual(another) {
    return (
      this.event === another.event &&
      this.disableDataPrefetch === another.disableDataPrefetch
    );
  }
}

class ArkDragSpringLoading {
  constructor() {
    this.configuration = undefined;
    this.callback = undefined;
  }

  isEqual(another) {
    return (
      this.configuration === another.configuration &&
      this.callback === another.callback
    );
  }
}

class ArkTextFont {
  constructor() {
    this.value = undefined;
    this.enableVariableFontWeight = undefined;
  }

  isEqual(another) {
    return (
      this.value === another.value &&
      this.enableVariableFontWeight === another.enableVariableFontWeight
    );
  }

  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
}

class ArkLineSpacing {
  constructor() {
    this.value = undefined;
    this.onlyBetweenLines = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) && (this.onlyBetweenLines === another.onlyBetweenLines);
  }

  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
}

class ArkFontWeight {
  constructor() {
    this.value = undefined;
    this.enableVariableFontWeight = undefined;
    this.enableDeviceFontWeightCategory = undefined;
  }

  isEqual(another) {
    return (
      this.value === another.value &&
      this.enableVariableFontWeight === another.enableVariableFontWeight &&
      this.enableDeviceFontWeightCategory === another.enableDeviceFontWeightCategory
    );
  }

  checkObjectDiff(another) {
    return !this.isEqual(another);
  }
}

class ArkNavigationTitle {
  constructor() {
    this.value = undefined;
    this.navigationTitleOptions = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) && (this.navigationTitleOptions === another.navigationTitleOptions);
  }
}

class ArkNavigationMenu {
  constructor() {
    this.menu = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.menu === another.menu) && (this.options === another.options);
  }
}

class ArkNavHideTitleBarOrToolBar {
  constructor() {
    this.isHide = undefined;
    this.animated = undefined;
  }
  isEqual(another) {
    return (this.isHide === another.isHide) && (this.animated === another.animated);
  }
}

class ArkNavigationToolBarConfiguration {
  constructor() {
    this.value = undefined;
    this.options = undefined;
  }
  isEqual(another) {
    return (this.value === another.value) && (this.options.backgroundColor === another.options.backgroundColor) &&
      (this.options.backgroundBlurStyle === another.options.backgroundBlurStyle) &&
      (this.options.barStyle === another.options.barStyle);
  }
}

class ArkNavBackButton {

  constructor() {
    this.icon = undefined;
    this.text = undefined;
  }

  isEqual(another) {
    return this.icon === another.icon && this.text === another.text;
  }
}

class ArkSelectedDragPreviewStyle {
  constructor() {
    this.color = undefined;
  }
  isEqual(another) {
    return this.color === another.color;
  }
}

class ArkEmitterPropertyOptions {
  constructor() {
    this.index = undefined;
    this.isSetEmitRate = 0;
    this.emitRate = undefined;
    this.isSetPosition = 0;
    this.positionX = undefined;
    this.positionY = undefined;
    this.isSetSize = 0;
    this.sizeWidth = undefined;
    this.sizeHeight = undefined;
    this.isSetAnnulusRegion = 0;
    this.isSetCenter = 0;
    this.centerX = undefined;
    this.centerY = undefined;
    this.isSetInnerRadius = 0;
    this.innerRadius = undefined;
    this.isSetOuterRadius = 0;
    this.outerRadius = undefined;
    this.isSetStartAngle = 0;
    this.startAngle = undefined;
    this.isSetEndAngle = 0;
    this.endAngle = undefined;
  }
}

class ArkRippleFieldOptions {
  constructor() {
    this.isSetAmplitude = 0;
    this.amplitude = undefined;
    this.isSetWaveLength = 0;
    this.wavelength = undefined;
    this.isSetWaveSpeed = 0;
    this.waveSpeed = undefined;
    this.isSetAttenuation = 0;
    this.attenuation = undefined;
    this.isSetCenter = 0;
    this.centerX = undefined;
    this.centerY = undefined;
    this.isSetRegion = 0;
    this.isSetShape = 0;
    this.shape = undefined;
    this.isSetPosition = 0;
    this.positionX = undefined;
    this.positionY = undefined;
    this.isSetSize = 0;
    this.sizeWidth = undefined;
    this.sizeHeight = undefined;
  }
}

class ArkVelocityFieldOptions {
  constructor() {
    this.isSetVelocity = 0;
    this.velocityX = undefined;
    this.velocityY = undefined;
    this.isSetShape = 0;
    this.isSetRegion = 0;
    this.shape = undefined;
    this.isSetPosition = 0;
    this.positionX = undefined;
    this.positionY = undefined;
    this.isSetSize = 0;
    this.sizeWidth = undefined;
    this.sizeHeight = undefined;
  }
}

class ArkCommonComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._needDiff = false;
  }
  initialize(value) {
    return this;
  }
}
// @ts-ignore
if (globalThis.__Common__ !== undefined) {
  globalThis.__Common__.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkCommonComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}


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
class ScrollEnablePagingModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetEnablePaging(node);
    } else {
      getUINativeModule().scroll.setEnablePaging(node, this.value);
    }
  }
}
ScrollEnablePagingModifier.identity = Symbol('scrollEnablePaging');
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
        for (let i = 0; i < this.value.snapPagination.length; i++) {
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
class ScrollClipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    }
    else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ScrollClipModifier.identity = Symbol('scrollClip');
class ScrollInitialOffsetModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetInitialOffset(node);
    }
    else {
      getUINativeModule().scroll.setInitialOffset(node, this.value.xOffset, this.value.yOffset);
    }
  }
  checkObjectDiff() {
    return !((this.stageValue.xOffset === this.value.xOffset) &&
    (this.stageValue.yOffset === this.value.yOffset));
  }
}
ScrollInitialOffsetModifier.identity = Symbol('initialOffset');

class ScrollInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollInitialize(node);
    }
    else {
      getUINativeModule().scroll.setScrollInitialize(node, this.value);
    }
  }
}
ScrollInitializeModifier.identity = Symbol('scrollInitialize');

class ScrollOnScrollStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScrollStart(node);
    } else {
      getUINativeModule().scroll.setScrollOnScrollStart(node, this.value);
    }
  }
}
ScrollOnScrollStartModifier.identity = Symbol('scrollOnScrollStart');

class ScrollOnScrollEndModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScrollEnd(node);
    } else {
      getUINativeModule().scroll.setScrollOnScrollEnd(node, this.value);
    }
  }
}
ScrollOnScrollEndModifier.identity = Symbol('scrollOnScrollEnd');

class ScrollOnScrollStopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScrollStop(node);
    } else {
      getUINativeModule().scroll.setScrollOnScrollStop(node, this.value);
    }
  }
}
ScrollOnScrollStopModifier.identity = Symbol('scrollOnScrollStop');

class ScrollOnScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScroll(node);
    } else {
      getUINativeModule().scroll.setScrollOnScroll(node, this.value);
    }
  }
}
ScrollOnScrollModifier.identity = Symbol('scrollOnScroll');

class ScrollOnScrollEdgeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScrollEdge(node);
    } else {
      getUINativeModule().scroll.setScrollOnScrollEdge(node, this.value);
    }
  }
}
ScrollOnScrollEdgeModifier.identity = Symbol('scrollOnScrollEdge');

class ScrollOnDidScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnDidScroll(node);
    } else {
      getUINativeModule().scroll.setScrollOnDidScroll(node, this.value);
    }
  }
}
ScrollOnDidScrollModifier.identity = Symbol('scrollOnDidScroll');

class ScrollOnWillScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnWillScroll(node);
    } else {
      getUINativeModule().scroll.setScrollOnWillScroll(node, this.value);
    }
  }
}
ScrollOnWillScrollModifier.identity = Symbol('scrollOnWillScroll');

class ScrollOnScrollFrameBeginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnScrollFrameBegin(node);
    } else {
      getUINativeModule().scroll.setScrollOnScrollFrameBegin(node, this.value);
    }
  }
}
ScrollOnScrollFrameBeginModifier.identity = Symbol('scrollOnScrollFrameBegin');

class ScrollMaxZoomScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetMaxZoomScale(node);
    } else {
      getUINativeModule().scroll.setMaxZoomScale(node, this.value);
    }
  }
}
ScrollMaxZoomScaleModifier.identity = Symbol('maxZoomScale');

class ScrollMinZoomScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetMinZoomScale(node);
    } else {
      getUINativeModule().scroll.setMinZoomScale(node, this.value);
    }
  }
}
ScrollMinZoomScaleModifier.identity = Symbol('minZoomScale');

class ScrollZoomScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetZoomScale(node);
    } else {
      getUINativeModule().scroll.setZoomScale(node, this.value);
    }
  }
}
ScrollZoomScaleModifier.identity = Symbol('zoomScale');

class ScrollEnableBouncesZoomModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetEnableBouncesZoom(node);
    } else {
      getUINativeModule().scroll.setEnableBouncesZoom(node, this.value);
    }
  }
}
ScrollEnableBouncesZoomModifier.identity = Symbol('enableBouncesZoom');

class ScrollOnDidZoomModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnDidZoom(node);
    } else {
      getUINativeModule().scroll.setScrollOnDidZoom(node, this.value);
    }
  }
}
ScrollOnDidZoomModifier.identity = Symbol('scrollOnDidZoom');

class ScrollOnZoomStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnZoomStart(node);
    } else {
      getUINativeModule().scroll.setScrollOnZoomStart(node, this.value);
    }
  }
}
ScrollOnZoomStartModifier.identity = Symbol('scrollOnZoomStart');

class ScrollOnZoomStopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scroll.resetScrollOnZoomStop(node);
    } else {
      getUINativeModule().scroll.setScrollOnZoomStop(node, this.value);
    }
  }
}
ScrollOnZoomStopModifier.identity = Symbol('scrollOnZoomStop');

class ArkScrollComponent extends ArkScrollable {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ScrollInitializeModifier.identity, ScrollInitializeModifier, value[0]);
    }
    return this;
  }
  allowChildCount() {
    return 1;
  }
  scrollable(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollScrollableModifier.identity, ScrollScrollableModifier, value);
    return this;
  }
  onScroll(event) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollModifier.identity, ScrollOnScrollModifier, event);
    return this;
  }
  onScrollEdge(event) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollEdgeModifier.identity, ScrollOnScrollEdgeModifier, event);
    return this;
  }
  onScrollStart(event) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollStartModifier.identity, ScrollOnScrollStartModifier, event);
    return this;
  }
  onScrollEnd(event) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollEndModifier.identity, ScrollOnScrollEndModifier, event);
    return this;
  }
  onScrollStop(event) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollStopModifier.identity, ScrollOnScrollStopModifier, event);
    return this;
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
  onScrollFrameBegin(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnScrollFrameBeginModifier.identity, ScrollOnScrollFrameBeginModifier, callback);
    return this;
  }

  onWillScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnWillScrollModifier.identity, ScrollOnWillScrollModifier, callback);
    return this;
  }

  onDidScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnDidScrollModifier.identity, ScrollOnDidScrollModifier, callback);
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
      modifierWithKey(this._modifiersWithKeys, ScrollNestedScrollModifier.identity, ScrollNestedScrollModifier, options);
    }
    return this;
  }
  enableScrollInteraction(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollEnableScrollInteractionModifier.identity, ScrollEnableScrollInteractionModifier, value);
    return this;
  }
  enablePaging(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollEnablePagingModifier.identity, ScrollEnablePagingModifier, value);
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
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollClipModifier.identity, ScrollClipModifier, value);
    return this;
  }
  initialOffset(value) {
    let options = new ArkScrollOffsetOptions();
    if (value) {
      if (value.xOffset) {
        options.xOffset = value.xOffset;
      }
      if (value.yOffset) {
        options.yOffset = value.yOffset;
      }
      modifierWithKey(this._modifiersWithKeys, ScrollInitialOffsetModifier.identity, ScrollInitialOffsetModifier, options);
    }
    return this;
  }
  maxZoomScale(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollMaxZoomScaleModifier.identity, ScrollMaxZoomScaleModifier, value);
    return this;
  }
  minZoomScale(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollMinZoomScaleModifier.identity, ScrollMinZoomScaleModifier, value);
    return this;
  }
  zoomScale(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollZoomScaleModifier.identity, ScrollZoomScaleModifier, value);
    return this;
  }
  enableBouncesZoom(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollEnableBouncesZoomModifier.identity, ScrollEnableBouncesZoomModifier, value);
    return this;
  }
  onDidZoom(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnDidZoomModifier.identity, ScrollOnDidZoomModifier, callback);
    return this;
  }
  onZoomStart(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnZoomStartModifier.identity, ScrollOnZoomStartModifier, callback);
    return this;
  }
  onZoomStop(callback) {
    modifierWithKey(this._modifiersWithKeys, ScrollOnZoomStopModifier.identity, ScrollOnZoomStopModifier, callback);
    return this;
  }
}
// @ts-ignore
if (globalThis.Scroll !== undefined) {
  globalThis.Scroll.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkScrollComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ScrollModifier(nativePtr, classType);
    });
  };
  globalThis.Scroll.onWillStopDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStopDragging(nodePtr, value);
  };
  globalThis.Scroll.onWillStartDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartDragging(nodePtr, value);
  };
  globalThis.Scroll.onDidStopDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopDragging(nodePtr, value);
  };
  globalThis.Scroll.onWillStartFling = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartFling(nodePtr, value);
  };
  globalThis.Scroll.onDidStopFling = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopFling(nodePtr, value);
  };
}

/// <reference path='./import.ts' />
class ArkNavDestinationComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  title(value, options) {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, NavDestinationTitleModifier.identity,
        NavDestinationTitleModifier, undefined);
      return this;
    }
    let arkNavigationTitle = new ArkNavigationTitle();
    arkNavigationTitle.value = value;
    if (!isUndefined(options) && !isNull(options) && isObject(options)) {
      if (Object.keys(options).length !== 0) {
        arkNavigationTitle.navigationTitleOptions = options;
      }
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationTitleModifier.identity,
      NavDestinationTitleModifier, arkNavigationTitle);
    return this;
  }
  menus(value, options) {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, NavDestinationMenusModifier.identity,
        NavDestinationMenusModifier, undefined);
      return this;
    }
    let config = new ArkNavigationMenu();
    config.menu = value;
    if (!isNull(options)) {
      config.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationMenusModifier.identity,
        NavDestinationMenusModifier, config);
    return this;
  }
  hideTitleBar(isHide, animated) {
    let arkNavDestinationHideTitleBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavDestinationHideTitleBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavDestinationHideTitleBar.animated = animated;
    }
    if (arkNavDestinationHideTitleBar.isHide === undefined && arkNavDestinationHideTitleBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, HideTitleBarModifier.identity, HideTitleBarModifier, arkNavDestinationHideTitleBar);
    }
    return this;
  }
  hideToolBar(isHide, animated) {
    let arkNavDestinationHideToolBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavDestinationHideToolBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavDestinationHideToolBar.animated = animated;
    }
    if (arkNavDestinationHideToolBar.isHide === undefined && arkNavDestinationHideToolBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, NavDestinationHideToolBarModifier.identity,
          NavDestinationHideToolBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, NavDestinationHideToolBarModifier.identity,
          NavDestinationHideToolBarModifier, arkNavDestinationHideToolBar);
    }
    return this;
  }
  toolbarConfiguration(value, options) {
    let configuration = new ArkNavigationToolBarConfiguration();
    configuration.value = value;
    if (!isNull(options)) {
      configuration.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationToolBarConfigurationModifier.identity,
      NavDestinationToolBarConfigurationModifier, configuration);
    return this;
  }
  hideBackButton(value) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationHideBackButtonModifier.identity,
      NavDestinationHideBackButtonModifier, value);
    return this;
  }
  backButtonIcon(value, text) {
    let config = new ArkNavBackButton();
    config.icon = value;
    if (!isNull(text)) {
      config.text = text;
    }
    modifierWithKey(this._modifiersWithKeys, NavDestinationBackButtonIconModifier.identity,
      NavDestinationBackButtonIconModifier, config);
    return this;
  }
  mode(value) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationModeModifier.identity,
      NavDestinationModeModifier, value);
    return this;
  }
  systemTransition(value) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationSystemTransitionModifier.identity,
      NavDestinationSystemTransitionModifier, value);
    return this;
  }
  onShown(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnShownModifier.identity,
      NavDestinationOnShownModifier, callback);
    return this;
  }
  onHidden(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnHiddenModifier.identity,
      NavDestinationOnHiddenModifier, callback);
    return this;
  }
  onWillHide(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnWillHideModifier.identity,
      NavDestinationOnWillHideModifier, callback);
    return this;
  }
  onWillAppear(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnWillAppearModifier.identity,
      NavDestinationOnWillAppearModifier, callback);
    return this;
  }
  onWillShow(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnWillShowModifier.identity,
      NavDestinationOnWillShowModifier, callback);
    return this;
  }
  onSaveState(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnSaveStateModifier.identity,
      NavDestinationOnSaveStateModifier, callback);
    return this;
  }
  onRestoreState(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnRestoreStateModifier.identity,
      NavDestinationOnRestoreStateModifier, callback);
    return this;
  }
  onWillDisappear(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnWillDisappearModifier.identity,
      NavDestinationOnWillDisappearModifier, callback);
    return this;
  }
  onActive(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnActiveModifier.identity,
      NavDestinationOnActiveModifier, callback);
    return this;
  }
  onInactive(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnInactiveModifier.identity,
      NavDestinationOnInactiveModifier, callback);
    return this;
  }
  onBackPressed(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnBackPressedModifier.identity,
      NavDestinationOnBackPressedModifier, callback);
    return this;
  }
  onReady(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnReadyModifier.identity,
      NavDestinationOnReadyModifier, callback);
    return this;
  }
  ignoreLayoutSafeArea(types, edges) {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length >= 0) {
      let safeAreaType = '';
      for (let param of types) {
        if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
          safeAreaType += param.toString();
        }
        else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length >= 0) {
      let safeAreaEdge = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
          safeAreaEdge += param.toString();
        }
        else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaModifier.identity, IgnoreLayoutSafeAreaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, IgnoreLayoutSafeAreaModifier.identity, IgnoreLayoutSafeAreaModifier, opts);
    }
    return this;
  }
  recoverable(value) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationRecoverableModifier.identity, NavDestinationRecoverableModifier, value);
    return this;
  }
  fullScreenOverlay(value) {
    modifierWithKey(this._modifiersWithKeys, FullScreenOverlayModifier.identity, FullScreenOverlayModifier, value);
    return this;
  }
  preferredOrientation(orientation) {
    modifierWithKey(this._modifiersWithKeys, PreferredOrientationModifier.identity, PreferredOrientationModifier, orientation);
    return this;
  }
  enableStatusBar(enable, animated) {
    let statusBar = new ArkEnableStatusBar();
    statusBar.enable = enable;
    statusBar.animated = animated;
    modifierWithKey(this._modifiersWithKeys, EnableStatusBarModifier.identity, EnableStatusBarModifier, statusBar);
    return this;
  }
  enableNavigationIndicator(enable) {
    modifierWithKey(this._modifiersWithKeys, EnableNavigationIndicatorModifier.identity, EnableNavigationIndicatorModifier, enable);
    return this;
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationBackgroundColorModifier.identity, NavDestinationBackgroundColorModifier, value);
    return this;
  }
  systemBarStyle(style) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationSystemBarStyleModifier.identity, NavDestinationSystemBarStyleModifier, style);
    return this;
  }
  onResult(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnResultModifier.identity,
      NavDestinationOnResultModifier, callback);
    return this;
  }
  onNewParam(callback) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationOnNewParamModifier.identity,
      NavDestinationOnNewParamModifier, callback);
    return this;
  }
  bindToScrollable(scrollers) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationBindToScrollableModifier.identity,
      NavDestinationBindToScrollableModifier, scrollers);
    return this;
  }
  bindToNestedScrollable(scrollInfos) {
    modifierWithKey(this._modifiersWithKeys, NavDestinationBindToNestedScrollableModifier.identity,
      NavDestinationBindToNestedScrollableModifier, scrollInfos);
    return this;
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
      getUINativeModule().navDestination.setHideTitleBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}
HideTitleBarModifier.identity = Symbol('hideTitleBar');

class NavDestinationHideToolBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetHideToolBar(node);
    }
    else {
      getUINativeModule().navDestination.setHideToolBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}
NavDestinationHideToolBarModifier.identity = Symbol('hideToolBar');

class NavDestinationToolBarConfigurationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navDestination.resetToolBarConfiguration(node);
    } else {
      getUINativeModule().navDestination.setToolBarConfiguration(node, this.value.value, this.value.options);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
NavDestinationToolBarConfigurationModifier.identity = Symbol('toolBarConfiguration');

class NavDestinationHideBackButtonModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetHideBackButton(node);
    }
    else {
      getUINativeModule().navDestination.setHideBackButton(node, this.value);
    }
  }
}
NavDestinationHideBackButtonModifier.identity = Symbol('hideBackButton');

class IgnoreLayoutSafeAreaModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetIgnoreLayoutSafeArea(node);
    }
    else {
      getUINativeModule().navDestination.setIgnoreLayoutSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}
IgnoreLayoutSafeAreaModifier.identity = Symbol('ignoreLayoutSafeArea');

class NavDestinationTitleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetTitle(node);
    } else {
      getUINativeModule().navDestination.setTitle(node, this.value?.value, this.value?.navigationTitleOptions);
    }
  }
  checkObjectDiff() {
    return !this.value.isEqual(this.stageValue);
  }
}
NavDestinationTitleModifier.identity = Symbol('title');

class NavDestinationRecoverableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetRecoverable(node);
    } else {
      getUINativeModule().navigation.setRecoverable(node, this.value);
    }
  }
}
NavDestinationRecoverableModifier.identity = Symbol('recoverable');

class FullScreenOverlayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetFullScreenOverlay(node);
    } else {
      getUINativeModule().navDestination.setFullScreenOverlay(node, this.value);
    }
  }
}
FullScreenOverlayModifier.identity = Symbol('fullScreenOverlay');

class NavDestinationMenusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetMenus(node);
    } else {
      getUINativeModule().navDestination.setMenus(node, this.value.menu, this.value.options);
    }
  }
  checkObjectDiff() {
    if (!Array.isArray(this.value) || !Array.isArray(this.stageValue)) {
      return true;
    }
    if (this.value.length !== this.stageValue.length) {
      return true;
    }
    for (let i = 0; i < this.value.length; i++) {
      if (!(isBaseOrResourceEqual(this.stageValue[i].value, this.value[i].value) &&
        isBaseOrResourceEqual(this.stageValue[i].icon, this.value[i].icon) &&
        isBaseOrResourceEqual(this.stageValue[i].isEnabled, this.value[i].isEnabled) &&
        isBaseOrResourceEqual(this.stageValue[i].action, this.value[i].action) &&
        isBaseOrResourceEqual(this.stageValue[i].symbolIcon, this.value[i].symbolIcon)
      )) {
        return true;
      }
    }
    return false;
  }
}
NavDestinationMenusModifier.identity = Symbol('menus');

class PreferredOrientationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetPreferredOrientation(node);
    } else {
      getUINativeModule().navDestination.setPreferredOrientation(node, this.value);
    }
  }
}
PreferredOrientationModifier.identity = Symbol('preferredOrientation');

class EnableStatusBarModifier extends ModifierWithKey {
  constructor(statusBar) {
    super(statusBar);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetEnableStatusBar(node);
    } else {
      getUINativeModule().navDestination.setEnableStatusBar(node, this.value?.enable, this.value?.animated);
    }
  }

  checkObjectDiff() {
    return this.value.enable !== this.stageValue.enable || this.value.animated !== this.stageValue.animated;
  }
}
EnableStatusBarModifier.identity = Symbol('enableStatusBar');

class EnableNavigationIndicatorModifier extends ModifierWithKey {
  constructor(navigationIndicator) {
    super(navigationIndicator);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetEnableNavigationIndicator(node);
    } else {
      getUINativeModule().navDestination.setEnableNavigationIndicator(node, this.value);
    }
  }
}
EnableNavigationIndicatorModifier.identity = Symbol('enableNavigationIndicator');

class NavDestinationBackgroundColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetBackgroundColor(node);
    }
    else {
      getUINativeModule().navDestination.setBackgroundColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
NavDestinationBackgroundColorModifier.identity = Symbol('navDestinationBackgroundColorModifier');

class NavDestinationSystemBarStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navDestination.resetSystemBarStyle(node);
    } else {
      getUINativeModule().navDestination.setSystemBarStyle(node, this.value.statusBarContentColor);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.statusBarContentColor === this.value.statusBarContentColor);
  }
}
NavDestinationSystemBarStyleModifier.identity = Symbol('systemBarStyle');

class NavigationDividerStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetDividerStyle(node);
    } else {
      getUINativeModule().navigation.setDividerStyle(node, this.value);
    }
  }

  checkObjectDiff() {
    return (this.value.color !== this.stageValue.color) ||
      (this.value.startMargin !== this.stageValue.startMargin) ||
      (this.value.endMargin !== this.stageValue.endMargin);
  }
}

NavigationDividerStyleModifier.identity = Symbol('DividerStyle');

class NavDestinationOnShownModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnShown(node);
    } else {
      getUINativeModule().navDestination.setOnShown(node, this.value);
    }
  }
}
NavDestinationOnShownModifier.identity = Symbol('onShown');

class NavDestinationOnHiddenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnHidden(node);
    } else {
      getUINativeModule().navDestination.setOnHidden(node, this.value);
    }
  }
}
NavDestinationOnHiddenModifier.identity = Symbol('onHidden');

class NavDestinationOnWillHideModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnWillHide(node);
    } else {
      getUINativeModule().navDestination.setOnWillHide(node, this.value);
    }
  }
}
NavDestinationOnWillHideModifier.identity = Symbol('onWillHide');

class NavDestinationOnWillAppearModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnWillAppear(node);
    } else {
      getUINativeModule().navDestination.setOnWillAppear(node, this.value);
    }
  }
}
NavDestinationOnWillAppearModifier.identity = Symbol('onWillAppear');

class NavDestinationBindToScrollableModifier extends ModifierWithKey {
  constructor(scrollers) {
    super(scrollers);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetBindToScrollable(node);
    } else {
      getUINativeModule().navDestination.setBindToScrollable(node, this.value);
    }
  }
}
NavDestinationBindToScrollableModifier.identity = Symbol('bindToScrollable');

class NavDestinationBindToNestedScrollableModifier extends ModifierWithKey {
  constructor(scrollInfos) {
    super(scrollInfos);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetBindToNestedScrollable(node);
    } else {
      getUINativeModule().navDestination.setBindToNestedScrollable(node, this.value);
    }
  }
}
NavDestinationBindToNestedScrollableModifier.identity = Symbol('bindToNestedScrollable');

class NavDestinationOnWillShowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnWillShow(node);
    } else {
      getUINativeModule().navDestination.setOnWillShow(node, this.value);
    }
  }
}
NavDestinationOnWillShowModifier.identity = Symbol('onWillShow');

class NavDestinationOnWillDisappearModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnWillDisappear(node);
    } else {
      getUINativeModule().navDestination.setOnWillDisappear(node, this.value);
    }
  }
}
NavDestinationOnWillDisappearModifier.identity = Symbol('onWillDisappear');

class NavDestinationOnActiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnActive(node);
    } else {
      getUINativeModule().navDestination.setOnActive(node, this.value);
    }
  }
}
NavDestinationOnActiveModifier.identity = Symbol('onActive');

class NavDestinationOnInactiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnInactive(node);
    } else {
      getUINativeModule().navDestination.setOnInactive(node, this.value);
    }
  }
}
NavDestinationOnInactiveModifier.identity = Symbol('onInactive');

class NavDestinationOnBackPressedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnBackPressed(node);
    } else {
      getUINativeModule().navDestination.setOnBackPressed(node, this.value);
    }
  }
}
NavDestinationOnBackPressedModifier.identity = Symbol('onBackPressed');

class NavDestinationOnSaveStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnSaveState(node);
    } else {
      getUINativeModule().navDestination.setOnSaveState(node, this.value);
    }
  }
}
NavDestinationOnSaveStateModifier.identity = Symbol('onSaveState');

class NavDestinationOnRestoreStateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnRestoreState(node);
    } else {
      getUINativeModule().navDestination.setOnRestoreState(node, this.value);
    }
  }
}
NavDestinationOnRestoreStateModifier.identity = Symbol('onRestoreState');

class NavDestinationOnReadyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnReady(node);
    } else {
      getUINativeModule().navDestination.setOnReady(node, this.value);
    }
  }
}
NavDestinationOnReadyModifier.identity = Symbol('onReady');

class NavDestinationOnResultModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnResult(node);
    } else {
      getUINativeModule().navDestination.setOnResult(node, this.value);
    }
  }
}
NavDestinationOnResultModifier.identity = Symbol('onResult');

class NavDestinationOnNewParamModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetOnNewParam(node);
    } else {
      getUINativeModule().navDestination.setOnNewParam(node, this.value);
    }
  }
}
NavDestinationOnNewParamModifier.identity = Symbol('onNewParam');

//@ts-ignore
if (globalThis.NavDestination !== undefined) {
  globalThis.NavDestination.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkNavDestinationComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.NavDestinationModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkPanelComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
if (globalThis.Panel !== undefined) {
  globalThis.Panel.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkPanelComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.PanelModifier(nativePtr, classType);
    });
  };
}

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
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
  backButtonIcon(value, text) {
    let config = new ArkNavBackButton();
    config.icon = value;
    if (!isNull(text)) {
      config.text = text;
    }
    modifierWithKey(this._modifiersWithKeys, BackButtonIconModifier.identity, BackButtonIconModifier, config);
    return this;
  }
  hideNavBar(value) {
    modifierWithKey(this._modifiersWithKeys, HideNavBarModifier.identity, HideNavBarModifier, value);
    return this;
  }
  title(value, options) {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, TitleModifier.identity,
        TitleModifier, undefined);
      return this;
    }
    let arkNavigationTitle = new ArkNavigationTitle();
    arkNavigationTitle.value = value;
    if (!isUndefined(options) && !isNull(options) && isObject(options)) {
      if (Object.keys(options).length !== 0) {
        arkNavigationTitle.navigationTitleOptions = options;
      }
    }
    modifierWithKey(this._modifiersWithKeys, TitleModifier.identity,
      TitleModifier, arkNavigationTitle);
    return this;
  }
  subTitle(value) {
    modifierWithKey(this._modifiersWithKeys, SubTitleModifier.identity, SubTitleModifier, value);
    return this;
  }
  enableModeChangeAnimation(value) {
    modifierWithKey(this._modifiersWithKeys, EnableModeChangeAnimationModifier.identity,
      EnableModeChangeAnimationModifier, value);
    return this;
  }
  splitPlaceholder(placeholder) {
    modifierWithKey(this._modifiersWithKeys, SplitPlaceholderModifier.identity, SplitPlaceholderModifier, placeholder);
    return this;
  }
  hideTitleBar(isHide, animated) {
    let arkNavigationHideTitleBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavigationHideTitleBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavigationHideTitleBar.animated = animated;
    }
    if (arkNavigationHideTitleBar.isHide === undefined && arkNavigationHideTitleBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, NavigationHideTitleBarModifier.identity, NavigationHideTitleBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, NavigationHideTitleBarModifier.identity, NavigationHideTitleBarModifier, arkNavigationHideTitleBar);
    }
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
  menus(value, options) {
    if (isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, MenusModifier.identity, MenusModifier, undefined);
      return this;
    }
    let config = new ArkNavigationMenu();
    config.menu = value;
    if (!isNull(options)) {
      config.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, MenusModifier.identity, MenusModifier, config);
    return this;
  }
  toolBar(value) {
    modifierWithKey(this._modifiersWithKeys, ToolBarModifier.identity, ToolBarModifier, value);
    return this;
  }
  toolbarConfiguration(value, options) {
    let configuration = new ArkNavigationToolBarConfiguration();
    configuration.value = value;
    if (!isNull(options)) {
      configuration.options = options;
    }
    modifierWithKey(this._modifiersWithKeys, ToolBarConfigurationModifier.identity,
      ToolBarConfigurationModifier, configuration);
    return this;
  }
  hideToolBar(isHide, animated) {
    let arkNavigationHideToolBar = new ArkNavHideTitleBarOrToolBar();
    if (!isUndefined(isHide) && !isNull(isHide)) {
      arkNavigationHideToolBar.isHide = isHide;
    }
    if (!isUndefined(animated) && !isNull(animated)) {
      arkNavigationHideToolBar.animated = animated;
    }
    if (arkNavigationHideToolBar.isHide === undefined && arkNavigationHideToolBar.animated === undefined) {
        modifierWithKey(this._modifiersWithKeys, HideToolBarModifier.identity, HideToolBarModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, HideToolBarModifier.identity, HideToolBarModifier, arkNavigationHideToolBar);
    }
    return this;
  }
  onTitleModeChange(callback) {
    modifierWithKey(this._modifiersWithKeys, OnTitleModeChangeModifier.identity, OnTitleModeChangeModifier, callback);
    return this;
  }
  onNavBarStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, OnNavBarStateChangeModifier.identity,
      OnNavBarStateChangeModifier, callback);
    return this;
  }
  onNavigationModeChange(callback) {
    modifierWithKey(this._modifiersWithKeys, OnNavigationModeChange.identity, OnNavigationModeChange, callback);
    return this;
  }
  customNavContentTransition(delegate) {
      modifierWithKey(this._modifiersWithKeys, CustomNavContentTransition.identity,
        CustomNavContentTransition, delegate);
    return this;
  }
  navDestination(builder) {
    throw new BusinessError(100201, 'navDestination function not supported in Navigation class');
  }
  ignoreLayoutSafeArea(types, edges) {
    let opts = new ArkSafeAreaExpandOpts();
    if (types && types.length >= 0) {
      let safeAreaType = '';
      for (let param of types) {
        if (!isNumber(param) || param >= SAFE_AREA_TYPE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaType = undefined;
          break;
        }
        if (safeAreaType) {
          safeAreaType += '|';
          safeAreaType += param.toString();
        }
        else {
          safeAreaType += param.toString();
        }
      }
      opts.type = safeAreaType;
    }
    if (edges && edges.length >= 0) {
      let safeAreaEdge = '';
      for (let param of edges) {
        if (!isNumber(param) || param >= SAFE_AREA_EDGE_LIMIT || param < SAFE_AREA_LOWER_LIMIT) {
          safeAreaEdge = undefined;
          break;
        }
        if (safeAreaEdge) {
          safeAreaEdge += '|';
          safeAreaEdge += param.toString();
        }
        else {
          safeAreaEdge += param.toString();
        }
      }
      opts.edges = safeAreaEdge;
    }
    if (opts.type === undefined && opts.edges === undefined) {
      modifierWithKey(this._modifiersWithKeys, IgnoreNavLayoutSafeAreaModifier.identity, IgnoreNavLayoutSafeAreaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, IgnoreNavLayoutSafeAreaModifier.identity, IgnoreNavLayoutSafeAreaModifier, opts);
    }
    return this;
  }
  recoverable(value) {
    modifierWithKey(this._modifiersWithKeys, NavigationRecoverableModifier.identity, NavigationRecoverableModifier, value);
    return this;
  }

  enableDragBar(value) {
    modifierWithKey(this._modifiersWithKeys, NavigationEnableDragBarModifier.identity, NavigationEnableDragBarModifier, value);
    return this;
  }

  enableToolBarAdaptation(value) {
    modifierWithKey(this._modifiersWithKeys, NavigationEnableToolBarAdaptationModifier.identity, NavigationEnableToolBarAdaptationModifier, value);
    return this;
  }

  systemBarStyle(style) {
    modifierWithKey(this._modifiersWithKeys, NavigationSystemBarStyleModifier.identity, NavigationSystemBarStyleModifier, style);
    return this;
  }

  divider(style) {
    modifierWithKey(this._modifiersWithKeys, NavigationDividerStyleModifier.identitiy, NavigationDividerStyleModifier, style);
    return this;
  }
  configuration(config) {
    modifierWithKey(this._modifiersWithKeys, NavigationConfigurationModifier.identity,
      NavigationConfigurationModifier, config);
    return this;
  }
}

class NavigationConfigurationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetConfiguration(node);
    } else {
      getUINativeModule().navigation.setConfiguration(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
NavigationConfigurationModifier.identity = Symbol('configuration');

class OnTitleModeChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetOnTitleModeChange(node);
    }
    else {
      getUINativeModule().navigation.setOnTitleModeChange(node, this.value);
    }
  }
}
OnTitleModeChangeModifier.identity = Symbol('onTitleModeChange');

class OnNavigationModeChange extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetOnNavigationModeChange(node);
    }
    else {
      getUINativeModule().navigation.setOnNavigationModeChange(node, this.value);
    }
  }
}
OnNavigationModeChange.identity = Symbol('onNavigationModeChange');

class CustomNavContentTransition extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetCustomNavContentTransition(node);
    }
    else {
      getUINativeModule().navigation.setCustomNavContentTransition(node, this.value);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
CustomNavContentTransition.identity = Symbol('customNavContentTransition');

class ToolBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
}
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetToolBar(node);
    } else {
      getUINativeModule().navigation.setToolBar(node, this.value.items);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ToolBarModifier.identity = Symbol('toolBar');

class ToolBarConfigurationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetToolBarConfiguration(node);
    } else {
      getUINativeModule().navigation.setToolBarConfiguration(node, this.value.value, this.value.options);
    }
  }
  checkObjectDiff() {
    return this.stageValue !== this.value;
  }
}
ToolBarConfigurationModifier.identitiy = Symbol('toolBarConfiguration');

class OnNavBarStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetOnNavBarStateChange(node);
    }
    else {
      getUINativeModule().navigation.setOnNavBarStateChange(node, this.value);
    }
  }
}
OnNavBarStateChangeModifier.identity = Symbol('onNavBarStateChange');

class BackButtonIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetBackButtonIcon(node);
    }
    else {
      getUINativeModule().navigation.setBackButtonIcon(node, this.value.icon, this.value.text);
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
  static identity = Symbol('mode');
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetMode(node);
    }
    else {
      getUINativeModule().navigation.setMode(node, this.value);
    }
  }
}
class NavDestinationBackButtonIconModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  static identity = Symbol('backButtonIcon');
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetBackButtonIcon(node);
    } else {
      getUINativeModule().navDestination.setBackButtonIcon(node, this.value.icon, this.value.text);
    }
  }
}

class NavDestinationModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetMode(node);
    }
    else {
      getUINativeModule().navDestination.setMode(node, this.value);
    }
  }
}
NavDestinationModeModifier.identity = Symbol('mode');

class NavDestinationSystemTransitionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navDestination.resetSystemTransition(node);
    }
    else {
      getUINativeModule().navDestination.setSystemTransition(node, this.value);
    }
  }
}
NavDestinationSystemTransitionModifier.identity = Symbol('systemTransition');

class HideToolBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetHideToolBar(node);
    }
    else {
      getUINativeModule().navigation.setHideToolBar(node, this.value?.isHide, this.value?.animated);
    }
  }
}
HideToolBarModifier.identity = Symbol('hideToolBar');

class EnableModeChangeAnimationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetEnableModeChangeAnimation(node);
    } else {
      getUINativeModule().navigation.setEnableModeChangeAnimation(node, this.value);
    }
  }
}
EnableModeChangeAnimationModifier.identity = Symbol('enableModeChangeAnimation');

class SplitPlaceholderModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetSplitPlaceholder(node);
    } else {
      getUINativeModule().navigation.setSplitPlaceholder(node, this.value);
    }
  }
}
SplitPlaceholderModifier.identity = Symbol('splitPlaceholder');

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
      getUINativeModule().navigation.setHideTitleBar(node, this.value?.isHide, this.value?.animated);
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
class IgnoreNavLayoutSafeAreaModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetIgnoreLayoutSafeArea(node);
    }
    else {
      getUINativeModule().navigation.setIgnoreLayoutSafeArea(node, this.value.type, this.value.edges);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.type, this.value.type) ||
      !isBaseOrResourceEqual(this.stageValue.edges, this.value.edges);
  }
}
IgnoreNavLayoutSafeAreaModifier.identity = Symbol('ignoreLayoutSafeArea');

class NavigationRecoverableModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetRecoverable(node);
    } else {
      getUINativeModule().navigation.setRecoverable(node, this.value);
    }
  }
}
NavigationRecoverableModifier.identity = Symbol('recoverable');

class NavigationEnableDragBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetEnableDragBar(node);
    } else {
      getUINativeModule().navigation.setEnableDragBar(node, this.value);
    }
  }
}
NavigationEnableDragBarModifier.identity = Symbol('enableDragBar');

class NavigationEnableToolBarAdaptationModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetEnableToolBarAdaptation(node);
    } else {
      getUINativeModule().navigation.setEnableToolBarAdaptation(node, this.value);
    }
  }
}
NavigationEnableToolBarAdaptationModifier.identity = Symbol('enableToolBarAdaptation');

class NavigationSystemBarStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset || !this.value) {
      getUINativeModule().navigation.resetSystemBarStyle(node);
    } else {
      getUINativeModule().navigation.setSystemBarStyle(node, this.value.statusBarContentColor);
    }
  }
  checkObjectDiff() {
    return !(this.stageValue.statusBarContentColor === this.value.statusBarContentColor);
  }
}
NavigationSystemBarStyleModifier.identity = Symbol('systemBarStyle');

class MenusModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetMenus(node);
    } else {
      getUINativeModule().navigation.setMenus(node, this.value.menu, this.value.options);
    }
  }
  checkObjectDiff() {
    if (!Array.isArray(this.value) || !Array.isArray(this.stageValue)) {
      return true;
    }
    if (this.value.length !== this.stageValue.length) {
      return true;
    }
    for (let i = 0; i < this.value.length; i++) {
      if (!(isBaseOrResourceEqual(this.stageValue[i].value, this.value[i].value) &&
        isBaseOrResourceEqual(this.stageValue[i].icon, this.value[i].icon) &&
        isBaseOrResourceEqual(this.stageValue[i].isEnabled, this.value[i].isEnabled) &&
        isBaseOrResourceEqual(this.stageValue[i].action, this.value[i].action) &&
        isBaseOrResourceEqual(this.stageValue[i].symbolIcon, this.value[i].symbolIcon)
      )) {
        return true;
      }
    }
    return false;
  }
}
MenusModifier.identity = Symbol('menus');

class TitleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navigation.resetTitle(node);
    } else {
      getUINativeModule().navigation.setTitle(node, this.value?.value, this.value?.navigationTitleOptions);
    }
  }
  checkObjectDiff() {
    return !this.value.isEqual(this.stageValue);
  }
}
TitleModifier.identity = Symbol('title');

// @ts-ignore
if (globalThis.Navigation !== undefined) {
  globalThis.Navigation.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkNavigationComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.NavigationModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkNavRouterComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, OnStateChangeModifier.identity, OnStateChangeModifier, callback);
    return this;
  }
  mode(mode) {
    modifierWithKey(this._modifiersWithKeys, NavRouterModeModifier.identity, NavRouterModeModifier, mode);
    return this;
  }
}

class OnStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().navRouter.resetOnStateChange(node);
    } else {
      getUINativeModule().navRouter.setOnStateChange(node, this.value);
    }
  }
}
OnStateChangeModifier.identity = Symbol('onStateChange');

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
if (globalThis.NavRouter !== undefined) {
  globalThis.NavRouter.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkNavRouterComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.NavRouterModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkNavigatorComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
if (globalThis.Navigator !== undefined) {
  globalThis.Navigator.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkNavigatorComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.NavigatorModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkFormComponentComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
if (globalThis.FormComponent !== undefined) {
  globalThis.FormComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFormComponentComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.FormComponentModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkEmbeddedComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onTerminated(callback) {
    modifierWithKey(this._modifiersWithKeys,
      EmbeddedComponentOnTerminatedModifier.identity, EmbeddedComponentOnTerminatedModifier, callback);
    return this;
  }
  onError(callback) {
    modifierWithKey(this._modifiersWithKeys,
      EmbeddedComponentOnErrorModifier.identity, EmbeddedComponentOnErrorModifier, callback);
    return this;
  }
}

class EmbeddedComponentOnTerminatedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().embeddedComponent.resetOnTerminated(node);
    }
    else {
      getUINativeModule().embeddedComponent.setOnTerminated(node, this.value);
    }
  }
}
EmbeddedComponentOnTerminatedModifier.identity = Symbol('onTerminated');

class EmbeddedComponentOnErrorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().embeddedComponent.resetOnError(node);
    } else {
      getUINativeModule().embeddedComponent.setOnError(node, this.value);
    }
  }
}
EmbeddedComponentOnErrorModifier.identity = Symbol('onError');

// @ts-ignore
if (globalThis.EmbeddedComponent !== undefined) {
  globalThis.EmbeddedComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkEmbeddedComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.EmbeddedComponentModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkIsolatedComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onError(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
if (globalThis.IsolatedComponent !== undefined) {
  globalThis.IsolatedComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkIsolatedComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkPluginComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onComplete(callback) {
    throw new Error('Method not implemented.');
  }
  onError(callback) {
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
if (globalThis.PluginComponent !== undefined) {
  globalThis.PluginComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkPluginComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.PluginComponentModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkRichTextComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onStart(callback) {
    throw new Error('Method not implemented.');
  }
  onComplete(callback) {
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
if (globalThis.RichText !== undefined) {
  globalThis.RichText.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkRichTextComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

class ScrollBarScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().ScrollBar.resetScrollBarScrollBarColor(node);
    } else {
      getUINativeModule().ScrollBar.setScrollBarScrollBarColor(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ScrollBarScrollBarColorModifier.identity = Symbol('scrollbarcolor');
class ScrollBarEnableNestedScrollModifier extends ModifierWithKey {
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().ScrollBar.resetScrollBarEnableNestedScroll(node);
    } else {
      getUINativeModule().ScrollBar.setScrollBarEnableNestedScroll(node, this.value);
    }
  }
}
ScrollBarEnableNestedScrollModifier.identity = Symbol('enableNestedScroll');

/// <reference path='./import.ts' />
class ArkScrollBarComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  enableNestedScroll(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollBarEnableNestedScrollModifier.identity,
      ScrollBarEnableNestedScrollModifier, value);
    return this;
  }
  scrollBarColor(value) {
    modifierWithKey(this._modifiersWithKeys, ScrollBarScrollBarColorModifier.identity,
      ScrollBarScrollBarColorModifier, value);
    return this;
  }
}

// @ts-ignore
if (globalThis.ScrollBar !== undefined) {
  globalThis.ScrollBar.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkScrollBarComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkWebComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  javaScriptAccess(javaScriptAccess) {
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptAccessModifier.identity, WebJavaScriptAccessModifier, javaScriptAccess);
    return this;
  }
  fileAccess(fileAccess) {
    modifierWithKey(this._modifiersWithKeys, WebFileAccessModifier.identity, WebFileAccessModifier, fileAccess);
    return this;
  }
  onlineImageAccess(onlineImageAccess) {
    modifierWithKey(this._modifiersWithKeys, WebOnlineImageAccessModifier.identity, WebOnlineImageAccessModifier, onlineImageAccess);
    return this;
  }
  domStorageAccess(domStorageAccess) {
    modifierWithKey(this._modifiersWithKeys, WebDomStorageAccessModifier.identity, WebDomStorageAccessModifier, domStorageAccess);
    return this;
  }
  imageAccess(imageAccess) {
    modifierWithKey(this._modifiersWithKeys, WebImageAccessModifier.identity, WebImageAccessModifier, imageAccess);
    return this;
  }
  mixedMode(mixedMode) {
    modifierWithKey(this._modifiersWithKeys, WebMixedModeModifier.identity, WebMixedModeModifier, mixedMode);
    return this;
  }
  zoomAccess(zoomAccess) {
    modifierWithKey(this._modifiersWithKeys, WebZoomAccessModifier.identity, WebZoomAccessModifier, zoomAccess);
    return this;
  }
  zoomControlAccess(zoomControlAccess) {
    modifierWithKey(this._modifiersWithKeys, WebZoomControlAccessModifier.identity, WebZoomControlAccessModifier, zoomControlAccess);
    return this;
  }
  geolocationAccess(geolocationAccess) {
    modifierWithKey(this._modifiersWithKeys, WebGeolocationAccessModifier.identity, WebGeolocationAccessModifier, geolocationAccess);
    return this;
  }
  javaScriptProxy(javaScriptProxy) {
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptProxyModifier.identity, WebJavaScriptProxyModifier, javaScriptProxy);
    return this;
  }
  password(password) {
    throw new Error('Method not implemented.');
  }
  cacheMode(cacheMode) {
    modifierWithKey(this._modifiersWithKeys, WebCacheModeModifier.identity, WebCacheModeModifier, cacheMode);
    return this;
  }
  darkMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebDarkModeModifier.identity, WebDarkModeModifier, mode);
    return this;
  }
  forceDarkAccess(access) {
    modifierWithKey(this._modifiersWithKeys, WebForceDarkAccessModifier.identity, WebForceDarkAccessModifier, access);
    return this;
  }
  mediaOptions(options) {
    modifierWithKey(this._modifiersWithKeys, WebMediaOptionsModifier.identity, WebMediaOptionsModifier, options);
    return this;
  }
  tableData(tableData) {
    throw new Error('Method not implemented.');
  }
  wideViewModeAccess(wideViewModeAccess) {
    throw new Error('Method not implemented.');
  }
  overviewModeAccess(overviewModeAccess) {
    modifierWithKey(this._modifiersWithKeys, WebOverviewModeAccessModifier.identity, WebOverviewModeAccessModifier, overviewModeAccess);
    return this;
  }
  overScrollMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebOverScrollModeModifier.identity, WebOverScrollModeModifier, mode);
    return this;
  }
  textZoomAtio(textZoomAtio) {
    throw new Error('Method not implemented.');
  }
  textZoomRatio(textZoomRatio) {
    modifierWithKey(this._modifiersWithKeys, WebTextZoomRatioModifier.identity, WebTextZoomRatioModifier, textZoomRatio);
    return this;
  }
  databaseAccess(databaseAccess) {
    modifierWithKey(this._modifiersWithKeys, WebDatabaseAccessModifier.identity, WebDatabaseAccessModifier, databaseAccess);
    return this;
  }
  initialScale(percent) {
    modifierWithKey(this._modifiersWithKeys, WebInitialScaleModifier.identity, WebInitialScaleModifier, percent);
    return this;
  }
  userAgent(userAgent) {
    throw new Error('Method not implemented.');
  }
  onPageEnd(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnPageEndModifier.identity, WebOnPageEndModifier, callback);
    return this;
  }
  onPageBegin(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnPageBeginModifier.identity, WebOnPageBeginModifier, callback);
    return this;
  }
  onProgressChange(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnProgressChangeModifier.identity, WebOnProgressChangeModifier, callback);
    return this;
  }
  onTitleReceive(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnTitleReceiveModifier.identity, WebOnTitleReceiveModifier, callback);
    return this;
  }
  onGeolocationHide(callback) {
    throw new Error('Method not implemented.');
  }
  onGeolocationShow(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnGeolocationShowModifier.identity, WebOnGeolocationShowModifier, callback);
    return this;
  }
  onRequestSelected(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnRequestSelectedModifier.identity, WebOnRequestSelectedModifier, callback);
    return this;
  }
  onAlert(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnAlertModifier.identity, WebOnAlertModifier, callback);
    return this;
  }
  onBeforeUnload(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnBeforeUnloadModifier.identity, WebOnBeforeUnloadModifier, callback);
    return this;
  }
  onConfirm(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnConfirmModifier.identity, WebOnConfirmModifier, callback);
    return this;
  }
  onPrompt(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnPromptModifier.identity, WebOnPromptModifier, callback);
    return this;
  }
  onConsole(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnConsoleModifier.identity, WebOnConsoleModifier, callback);
    return this;
  }
  onErrorReceive(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnErrorReceiveModifier.identity, WebOnErrorReceiveModifier, callback);
    return this;
  }
  onHttpErrorReceive(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnHttpErrorReceiveModifier.identity, WebOnHttpErrorReceiveModifier, callback);
    return this;
  }
  onDownloadStart(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnDownloadStartModifier.identity, WebOnDownloadStartModifier, callback);
    return this;
  }
  onRefreshAccessedHistory(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnRefreshAccessedHistoryModifier.identity, WebOnRefreshAccessedHistoryModifier, callback);
    return this;
  }
  onUrlLoadIntercept(callback) {
    throw new Error('Method not implemented.');
  }
  onSslErrorReceive(callback) {
    throw new Error('Method not implemented.');
  }
  onRenderExited(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderExitedModifier.identity, WebOnRenderExitedModifier, callback);
    return this;
  }
  onShowFileSelector(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnShowFileSelectorModifier.identity, WebOnShowFileSelectorModifier, callback);
    return this;
  }
  onFileSelectorShow(callback) {
    throw new Error('Method not implemented.');
  }
  onTextSelectionChange(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnTextSelectionChangeModifier.identity, WebOnTextSelectionChangeModifier, callback);
    return this;
  }
  onResourceLoad(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnResourceLoadModifier.identity, WebOnResourceLoadModifier, callback);
    return this;
  }
  onFullScreenExit(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnFullScreenExitModifier.identity, WebOnFullScreenExitModifier, callback);
    return this;
  }
  onFullScreenEnter(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnFullScreenEnterModifier.identity, WebOnFullScreenEnterModifier, callback);
    return this;
  }
  onScaleChange(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnScaleChangeModifier.identity, WebOnScaleChangeModifier, callback);
    return this;
  }
  onHttpAuthRequest(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnHttpAuthRequestModifier.identity, WebOnHttpAuthRequestModifier, callback);
    return this;
  }
  onInterceptRequest(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnInterceptRequestModifier.identity, WebOnInterceptRequestModifier, callback);
    return this;
  }
  onOverrideErrorPage(callback) {
    throw new Error('Method not implemented.');
  }
  onPermissionRequest(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnPermissionRequestModifier.identity, WebOnPermissionRequestModifier, callback);
    return this;
  }
  onScreenCaptureRequest(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnScreenCaptureRequestModifier.identity, WebOnScreenCaptureRequestModifier, callback);
    return this;
  }
  onDetectedBlankScreen(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnDetectedBlankScreenModifier.identity, WebOnDetectedBlankScreenModifier, callback);
    return this;
  }
  blankScreenDetectionConfig(config) {
    if (config === undefined || config === null) {
      return this;
    }
    let detectConfig = new BlankScreenDetectionConfig();
    detectConfig.enable = config.enable;
    detectConfig.detectionTiming = config.detectionTiming;
    detectConfig.detectionMethods = config.detectionMethods;
    detectConfig.contentfulNodesCountThreshold = config.contentfulNodesCountThreshold;
    modifierWithKey(this._modifiersWithKeys, WebBlankScreenDetectionConfigModifier.identity, WebBlankScreenDetectionConfigModifier, detectConfig);
    return this;
  }
  onFirstScreenPaint(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnFirstScreenPaintModifier.identity, WebOnFirstScreenPaintModifier, callback);
    return this;
  }
  onContextMenuShow(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnContextMenuShowModifier.identity, WebOnContextMenuShowModifier, callback);
    return this;
  }
  mediaPlayGestureAccess(access) {
    modifierWithKey(this._modifiersWithKeys, WebMediaPlayGestureAccessModifier.identity, WebMediaPlayGestureAccessModifier, access);
    return this;
  }
  enableFullscreenVideoOverlay(enabled) {
    modifierWithKey(this._modifiersWithKeys, WebEnableFullscreenVideoOverlayModifier.identity, WebEnableFullscreenVideoOverlayModifier, enabled);
    return this;
  }
  onSearchResultReceive(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnSearchResultReceiveModifier.identity, WebOnSearchResultReceiveModifier, callback);
    return this;
  }
  onScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnScrollModifier.identity, WebOnScrollModifier, callback);
    return this;
  }
  onSslErrorEventReceive(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnSslErrorEventReceiveModifier.identity, WebOnSslErrorEventReceiveModifier, callback);
    return this;
  }
  onSslErrorEvent(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnSslErrorEventModifier.identity, WebOnSslErrorEventModifier, callback);
    return this;
  }
  onClientAuthenticationRequest(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnClientAuthenticationRequestModifier.identity, WebOnClientAuthenticationRequestModifier, callback);
    return this;
  }
  onWindowNew(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnWindowNewModifier.identity, WebOnWindowNewModifier, callback);
    return this;
  }
  onWindowNewExt(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnWindowNewExtModifier.identity, WebOnWindowNewExtModifier, callback);
    return this;
  }
  onWindowExit(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnWindowExitModifier.identity, WebOnWindowExitModifier, callback);
    return this;
  }
  multiWindowAccess(multiWindow) {
    modifierWithKey(this._modifiersWithKeys, WebMultiWindowAccessModifier.identity, WebMultiWindowAccessModifier, multiWindow);
    return this;
  }
  onInterceptKeyEvent(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnInterceptKeyEventModifier.identity, WebOnInterceptKeyEventModifier, callback);
    return this;
  }
  webStandardFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebStandardFontModifier.identity, WebStandardFontModifier, family);
    return this;
  }
  webSerifFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebSerifFontModifier.identity, WebSerifFontModifier, family);
    return this;
  }
  webSansSerifFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebSansSerifFontModifier.identity, WebSansSerifFontModifier, family);
    return this;
  }
  webFixedFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebFixedFontModifier.identity, WebFixedFontModifier, family);
    return this;
  }
  webFantasyFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebFantasyFontModifier.identity, WebFantasyFontModifier, family);
    return this;
  }
  webCursiveFont(family) {
    modifierWithKey(this._modifiersWithKeys, WebCursiveFontModifier.identity, WebCursiveFontModifier, family);
    return this;
  }
  defaultFixedFontSize(size) {
    modifierWithKey(this._modifiersWithKeys, WebDefaultFixedFontSizeModifier.identity, WebDefaultFixedFontSizeModifier, size);
    return this;
  }
  defaultFontSize(size) {
    modifierWithKey(this._modifiersWithKeys, WebDefaultFontSizeModifier.identity, WebDefaultFontSizeModifier, size);
    return this;
  }
  minFontSize(size) {
    modifierWithKey(this._modifiersWithKeys, WebMinFontSizeModifier.identity, WebMinFontSizeModifier, size);
    return this;
  }
  minLogicalFontSize(size) {
    modifierWithKey(this._modifiersWithKeys, WebMinLogicalFontSizeModifier.identity, WebMinLogicalFontSizeModifier, size);
    return this;
  }
  blockNetwork(block) {
    modifierWithKey(this._modifiersWithKeys, WebBlockNetworkModifier.identity, WebBlockNetworkModifier, block);
    return this;
  }
  horizontalScrollBarAccess(horizontalScrollBar) {
    modifierWithKey(this._modifiersWithKeys, WebHorizontalScrollBarAccessModifier.identity, WebHorizontalScrollBarAccessModifier, horizontalScrollBar);
    return this;
  }
  verticalScrollBarAccess(verticalScrollBar) {
    modifierWithKey(this._modifiersWithKeys, WebVerticalScrollBarAccessModifier.identity, WebVerticalScrollBarAccessModifier, verticalScrollBar);
    return this;
  }
  onTouchIconUrlReceived(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnTouchIconUrlReceivedModifier.identity, WebOnTouchIconUrlReceivedModifier, callback);
    return this;
  }
  onFaviconReceived(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnFaviconReceivedModifier.identity, WebOnFaviconReceivedModifier, callback);
    return this;
  }
  onPageVisible(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnPageVisibleModifier.identity, WebOnPageVisibleModifier, callback);
    return this;
  }
  onDataResubmitted(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnDataResubmittedModifier.identity, WebOnDataResubmittedModifier, callback);
    return this;
  }
  pinchSmooth(isEnabled) {
    modifierWithKey(this._modifiersWithKeys, WebPinchSmoothModifier.identity, WebPinchSmoothModifier, isEnabled);
    return this;
  }
  metaViewport(enabled) {
    modifierWithKey(this._modifiersWithKeys, WebMetaViewportModifier.identity, WebMetaViewportModifier, enabled);
    return this;
  }
  enableFollowSystemFontWeight(follow) {
    modifierWithKey(this._modifiersWithKeys, WebEnableFollowSystemFontWeightModifier.identity, WebEnableFollowSystemFontWeightModifier, follow);
    return this;
  }
  enableNativeEmbedMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebEnableNativeEmbedModeModifier.identity, WebEnableNativeEmbedModeModifier, mode);
    return this;
  }
  allowWindowOpenMethod(flag) {
    modifierWithKey(this._modifiersWithKeys, WebAllowWindowOpenMethodModifier.identity, WebAllowWindowOpenMethodModifier, flag);
    return this;
  }
  onAudioStateChanged(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnAudioStateChangedModifier.identity, WebOnAudioStateChangedModifier, callback);
    return this;
  }
  onFirstContentfulPaint(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnFirstContentfulPaintModifier.identity, WebOnFirstContentfulPaintModifier, callback);
    return this;
  }
  onLoadIntercept(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnLoadInterceptModifier.identity, WebOnLoadInterceptModifier, callback);
    return this;
  }
  onControllerAttached(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnControllerAttachedModifier.identity, WebOnControllerAttachedModifier, callback);
    return this;
  }
  onOverScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnOverScrollModifier.identity, WebOnOverScrollModifier, callback);
    return this;
  }
  javaScriptOnDocumentStart(scripts) {
    let scriptInfo = new ArkWebScriptItem();
    scriptInfo.scripts = scripts.map(item => { return item.script; });
    scriptInfo.scriptRules = scripts.map(item => { return item.scriptRules; });
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptOnDocumentStartModifier.identity, WebJavaScriptOnDocumentStartModifier, scriptInfo);
    return this;
  }
  javaScriptOnDocumentEnd(scripts) {
    let scriptInfo = new ArkWebScriptItem();
    scriptInfo.scripts = scripts.map(item => { return item.script; });
    scriptInfo.scriptRules = scripts.map(item => { return item.scriptRules; });
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptOnDocumentEndModifier.identity, WebJavaScriptOnDocumentEndModifier, scriptInfo);
    return this;
  }
  layoutMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebLayoutModeModifier.identity, WebLayoutModeModifier, mode);
    return this;
  }
  onNativeEmbedLifecycleChange(event) {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedLifecycleChangeModifier.identity, WebOnNativeEmbedLifecycleChangeModifier, event);
    return this;
  }
  onNativeEmbedGestureEvent(event) {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedGestureEventModifier.identity, WebOnNativeEmbedGestureEventModifier, event);
    return this;
  }
  onNativeEmbedMouseEvent(event) {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedMouseEventModifier.identity, WebOnNativeEmbedMouseEventModifier, event);
    return this;
  }
  onNativeEmbedObjectParamChange(event) {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedObjectParamChangeModifier.identity, WebOnNativeEmbedObjectParamChangeModifier, event);
    return this;
  }
  registerNativeEmbedRule(tag,type) {
    let arkRegisterNativeEmbedRule = new ArkRegisterNativeEmbedRule();
    if (!isUndefined(tag) && !isNull(tag)) {
      arkRegisterNativeEmbedRule.tag = tag;
    }
    if (!isUndefined(type) && !isNull(type)) {
      arkRegisterNativeEmbedRule.type = type;
    }
    if (arkRegisterNativeEmbedRule.tag === undefined && arkRegisterNativeEmbedRule.type === undefined) {
        modifierWithKey(this._modifiersWithKeys, WebRegisterNativeEmbedRuleModifier.identity, WebRegisterNativeEmbedRuleModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, WebRegisterNativeEmbedRuleModifier.identity, WebRegisterNativeEmbedRuleModifier, arkRegisterNativeEmbedRule);
    }
    return this;
  }
  nativeEmbedOptions(value){
    modifierWithKey(this._modifiersWithKeys, WebNativeEmbedOptionsModifier.identity, WebNativeEmbedOptionsModifier, value);
    return this;
  }
  nestedScroll(value) {
    if (!value) return this;
    const options = new ArkNestedScrollOptionsExt();
  
    if ('scrollUp' in value) {
      options.scrollUp = value.scrollUp;
    }
    if ('scrollDown' in value) {
      options.scrollDown = value.scrollDown;
    }
    if ('scrollLeft' in value) {
      options.scrollLeft = value.scrollLeft;
    }
    if ('scrollRight' in value) {
      options.scrollRight = value.scrollRight;
    }
  
    if ('scrollForward' in value) {
      options.scrollDown = value.scrollForward;
      options.scrollRight = value.scrollForward;
    }
    if ('scrollBackward' in value) {
      options.scrollUp = value.scrollBackward;
      options.scrollLeft = value.scrollBackward;
    }
    modifierWithKey(this._modifiersWithKeys, WebNestedScrollModifier.identity, WebNestedScrollModifier, options);
    return this;
  }
  onOverrideUrlLoading(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnOverrideUrlLoadingModifier.identity, WebOnOverrideUrlLoadingModifier, callback);
    return this;
  }
  enableNativeMediaPlayer(config) {
    modifierWithKey(this._modifiersWithKeys, WebEnableNativeMediaPlayerModifier.identity, WebEnableNativeMediaPlayerModifier, config);
    return this;
  }
  enableWebAVSession(enabled) {
    modifierWithKey(this._modifiersWithKeys, WebEnableWebAVSessionModifier.identity, WebEnableWebAVSessionModifier, enabled);
    return this;
  }
  onRenderProcessNotResponding(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderProcessNotRespondingModifier.identity, WebOnRenderProcessNotRespondingModifier, callback);
    return this;
  }
  onRenderProcessResponding(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderProcessRespondingModifier.identity, WebOnRenderProcessRespondingModifier, callback);
    return this;
  }
  onViewportFitChanged(callback) {
    throw new Error('Method not implemented.');
  }
  onAdsBlocked(callback) {
    throw new Error('Method not implemented.');
  }
  onActivateContent(callback) {
    throw new Error('Method not implemented.');
  }
  onContextMenuHide(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnContextMenuHideModifier.identity, WebOnContextMenuHideModifier, callback);
    return this;
  }
  keyboardAvoidMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebKeyboardAvoidModeModifier.identity, WebKeyboardAvoidModeModifier, mode);
    return this;
  }
  copyOptions(value) {
    modifierWithKey(this._modifiersWithKeys, WebCopyOptionsModifier.identity, WebCopyOptionsModifier, value);
    return this;
  }
  onNavigationEntryCommitted(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnNavigationEntryCommittedModifier.identity, WebOnNavigationEntryCommittedModifier, callback);
    return this;
  }
  onSafeBrowsingCheckResult(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnSafeBrowsingCheckResultModifier.identity, WebOnSafeBrowsingCheckResultModifier, callback);
    return this;
  }
  enableDataDetector(enable) {
    modifierWithKey(this._modifiersWithKeys, WebEnableDataDetectorModifier.identity, WebEnableDataDetectorModifier, enable);
    return this;
  }
  dataDetectorConfig(config) {
    if (config === undefined || config === null) {
      return this;
    }
    let detectorConfig = new TextDataDetectorConfig();
    detectorConfig.types = config.types;
    detectorConfig.onDetectResultUpdate = config.onDetectResultUpdate;
    detectorConfig.color = config.color;
    if (config.decoration) {
      detectorConfig.decorationType = config.decoration.type;
      detectorConfig.decorationColor = config.decoration.color;
      detectorConfig.decorationStyle = config.decoration.style;
    }
    detectorConfig.enablePreviewMenu = config.enablePreviewMenu;
    modifierWithKey(this._modifiersWithKeys, WebDataDetectorConfigModifier.identity, WebDataDetectorConfigModifier, detectorConfig);
    return this;
  }
  enableSelectedDataDetector(enable) {
    modifierWithKey(this._modifiersWithKeys, WebEnableSelectedDataDetectorModifier.identity, WebEnableSelectedDataDetectorModifier, enable);
    return this;
  }
  gestureFocusMode(mode) {
    modifierWithKey(this._modifiersWithKeys, WebGestureFocusModeModifier.identity, WebGestureFocusModeModifier, mode);
    return this;
  }
  enableImageAnalyzer(enabled) {
    modifierWithKey(this._modifiersWithKeys, WebEnableImageAnalyzerModifier.identity, WebEnableImageAnalyzerModifier, enabled);
    return this;
  }
  forceEnableZoom(enabled) {
    modifierWithKey(this._modifiersWithKeys, WebForceEnableZoomModifier.identity, WebForceEnableZoomModifier, enabled);
    return this;
  }
  rotateRenderEffect(effect) {
    modifierWithKey(this._modifiersWithKeys, WebRotateRenderEffectModifier.identity, WebRotateRenderEffectModifier, effect);
    return this;
  }
  backToTop(backToTop) {
    modifierWithKey(this._modifiersWithKeys, WebBackToTopModifier.identity, WebBackToTopModifier, backToTop);
    return this;
  }
  onCameraCaptureStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnCameraCaptureStateChangeModifier.identity, WebOnCameraCaptureStateChangeModifier, callback);
    return this;
  }
  onMicrophoneCaptureStateChange(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnMicrophoneCaptureStateChangeModifier.identity, WebOnMicrophoneCaptureStateChangeModifier, callback);
    return this;
  }
  enableAutoFill(value) {
    modifierWithKey(this._modifiersWithKeys, WebEnableAutoFillModifier.identity, WebEnableAutoFillModifier, value);
    return this;
  }
  enableDefaultContextMenu(value) {
    modifierWithKey(this._modifiersWithKeys, WebEnableDefaultContextMenuModifier.identity, WebEnableDefaultContextMenuModifier, value);
    return this;
  }
  aiSessionOptions(value) {
    modifierWithKey(this._modifiersWithKeys, WebAiSessionOptionsModifier.identity, WebAiSessionOptionsModifier, value);
    return this;
  }
  enableScrollDirectionalLock(enabled, type) {
    let config = new ArkEnableScrollDirectionalLock();
    config.value = enabled;
    config.type = type;
    modifierWithKey(this._modifiersWithKeys, WebEnableScrollDirectionalLockModifier.identity, WebEnableScrollDirectionalLockModifier, config);
    return this;
  }
  enableDrag(value) {
    modifierWithKey(this._modifiersWithKeys, WebEnableDragModifier.identity, WebEnableDragModifier, value);
    return this;
  }
  scrollbarLayoutPolicy(value) {
    modifierWithKey(this._modifiersWithKeys, WebScrollbarLayoutPolicyModifier.identity, WebScrollbarLayoutPolicyModifier, value);
    return this;
  }
  onInputmethodAttached(callback) {
    modifierWithKey(this._modifiersWithKeys, WebOnInputMethodAttachedModifier.identity, WebOnInputMethodAttachedModifier, callback);
    return this;
  }
  keyboardAppearance(mode) {
    modifierWithKey(this._modifiersWithKeys, WebKeyboardAppearanceModifier.identity, WebKeyboardAppearanceModifier, mode);
    return this;
  }
}

class WebJavaScriptAccessModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetJavaScriptAccess(node);
      }
      else {
        getUINativeModule().web.setJavaScriptAccess(node, this.value);
      }
  }
}
WebJavaScriptAccessModifier.identity = Symbol('webJavaScriptAccessModifier');

class WebKeyboardAppearanceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetKeyboardAppearance(node);
    }
    else {
      getUINativeModule().web.setKeyboardAppearance(node, this.value);
    }
  }
}
WebKeyboardAppearanceModifier.identity = Symbol('webKeyboardAppearanceModifier');

class WebFileAccessModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetFileAccess(node);
      }
      else {
        getUINativeModule().web.setFileAccess(node, this.value);
      }
  }
}
WebFileAccessModifier.identity = Symbol('webFileAccessModifier');


class WebMixedModeModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetMixedMode(node);
      }
      else {
        getUINativeModule().web.setMixedMode(node, this.value);
      }
  }
}
WebMixedModeModifier.identity = Symbol('webMixedModeModifier');

class WebZoomAccessModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetZoomAccess(node);
      }
      else {
        getUINativeModule().web.setZoomAccess(node, this.value);
      }
  }
}
WebZoomAccessModifier.identity = Symbol('webZoomAccessModifier');

class WebZoomControlAccessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetZoomControlAccess(node);
    } else {
      getUINativeModule().web.setZoomControlAccess(node, this.value);
    }
}
}
WebZoomControlAccessModifier.identity = Symbol('webZoomControlAccessModifier');

class WebCacheModeModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetCacheMode(node);
      }
      else {
        getUINativeModule().web.setCacheMode(node, this.value);
      }
  }
}
WebCacheModeModifier.identity = Symbol('webCacheModeModifier');

class WebDarkModeModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetDarkMode(node);
      }
      else {
        getUINativeModule().web.setDarkMode(node, this.value);
      }
  }
}
WebDarkModeModifier.identity = Symbol('webDarkModeModifier');

class WebMultiWindowAccessModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetMultiWindowAccess(node);
      }
      else {
        getUINativeModule().web.setMultiWindowAccess(node, this.value);
      }
  }
}
WebMultiWindowAccessModifier.identity = Symbol('webMultiWindowAccessModifier');

class WebAllowWindowOpenMethodModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetAllowWindowOpenMethod(node);
      }
      else {
        getUINativeModule().web.setAllowWindowOpenMethod(node, this.value);
      }
  }
}
WebAllowWindowOpenMethodModifier.identity = Symbol('webAllowWindowOpenMethodModifier');

class WebKeyboardAvoidModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetKeyboardAvoidMode(node);
    }
    else {
      getUINativeModule().web.setKeyboardAvoidMode(node, this.value);
    }
  }
}
WebKeyboardAvoidModeModifier.identity = Symbol('webKeyboardAvoidModeModifier');

class WebOnControllerAttachedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnControllerAttached(node);
    }
    else {
      getUINativeModule().web.setOnControllerAttached(node, this.value);
    }
  }
}
WebOnControllerAttachedModifier.identity = Symbol('webOnControllerAttachedModifier');

class WebVerticalScrollBarAccessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetVerticalScrollBarAccess(node);
    }
    else {
      getUINativeModule().web.setVerticalScrollBarAccess(node, this.value);
    }
  }
}
WebVerticalScrollBarAccessModifier.identity = Symbol('webVerticalScrollBarAccessModifier');

class WebHorizontalScrollBarAccessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetHorizontalScrollBarAccess(node);
    }
    else {
      getUINativeModule().web.setHorizontalScrollBarAccess(node, this.value);
    }
  }
}
WebHorizontalScrollBarAccessModifier.identity = Symbol('webHorizontalScrollBarAccessModifier');

class WebTextZoomRatioModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetTextZoomRatio(node);
    }
    else {
      getUINativeModule().web.setTextZoomRatio(node, this.value);
    }
  }
}
WebTextZoomRatioModifier.identity = Symbol('webTextZoomRatioModifier');

class WebInitialScaleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetInitialScale(node);
    }
    else {
      getUINativeModule().web.setInitialScale(node, this.value);
    }
  }
}
WebInitialScaleModifier.identity = Symbol('webInitialScaleModifier');

class WebOnScaleChangeModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnScaleChange(node);
      }
      else {
        getUINativeModule().web.setOnScaleChange(node, this.value);
      }
  }
}
WebOnScaleChangeModifier.identity = Symbol('webOnScaleChangeModifier');

class WebOnRequestSelectedModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnRequestSelected(node);
      }
      else {
        getUINativeModule().web.setOnRequestSelected(node, this.value);
      }
  }
}
WebOnRequestSelectedModifier.identity = Symbol('webOnRequestSelectedModifier');

class WebOnOverScrollModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnOverScroll(node);
      }
      else {
        getUINativeModule().web.setOnOverScroll(node, this.value);
      }
  }
}
WebOnOverScrollModifier.identity = Symbol('webOnOverScrollModifier');

class WebOnScrollModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnScroll(node);
      }
      else {
        getUINativeModule().web.setOnScroll(node, this.value);
      }
  }
}
WebOnScrollModifier.identity = Symbol('webOnScrollModifier');

class WebOnContextMenuHideModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnContextMenuHide(node);
      }
      else {
        getUINativeModule().web.setOnContextMenuHide(node, this.value);
      }
  }
}
WebOnContextMenuHideModifier.identity = Symbol('webOnContextMenuHideModifier');
class WebGeolocationAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetGeolocationAccess(node);
    } else {
      getUINativeModule().web.setGeolocationAccess(node, this.value);
    }
  }
}
WebGeolocationAccessModifier.identity = Symbol('webGeolocationAccessModifier');

class WebDatabaseAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetDatabaseAccess(node);
    } else {
      getUINativeModule().web.setDatabaseAccess(node, this.value);
    }
  }
}
WebDatabaseAccessModifier.identity = Symbol('webDatabaseAccessModifier');

class WebOverviewModeAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOverviewModeAccess(node);
    } else {
      getUINativeModule().web.setOverviewModeAccess(node, this.value);
    }
  }
}
WebOverviewModeAccessModifier.identity = Symbol('webOverviewModeAccessModifier');

class WebForceDarkAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetForceDarkAccess(node);
    } else {
      getUINativeModule().web.setForceDarkAccess(node, this.value);
    }
  }
}
WebForceDarkAccessModifier.identity = Symbol('webForceDarkAccessModifier');

class WebPinchSmoothModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetPinchSmooth(node);
    } else {
      getUINativeModule().web.setPinchSmooth(node, this.value);
    }
  }
}
WebPinchSmoothModifier.identity = Symbol('webPinchSmoothModifier');

class WebMetaViewportModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetMetaViewport(node);
    } else {
      getUINativeModule().web.setMetaViewport(node, this.value);
    }
  }
}
WebMetaViewportModifier.identity = Symbol('webMetaViewportModifier');

class WebEnableFollowSystemFontWeightModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableFollowSystemFontWeight(node);
    } else {
      getUINativeModule().web.setEnableFollowSystemFontWeight(node, this.value);
    }
  }
}
WebEnableFollowSystemFontWeightModifier.identity = Symbol('webEnableFollowSystemFontWeightModifier');

class WebEnableNativeEmbedModeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableNativeEmbedMode(node);
    } else {
      getUINativeModule().web.setEnableNativeEmbedMode(node, this.value);
    }
  }
}
WebEnableNativeEmbedModeModifier.identity = Symbol('webEnableNativeEmbedModeModifier');

class WebMinFontSizeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetMinFontSize(node);
    } else {
      getUINativeModule().web.setMinFontSize(node, this.value);
    }
  }
}
WebMinFontSizeModifier.identity = Symbol('webMinFontSizeModifier');

class WebDefaultFontSizeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetDefaultFontSize(node);
    } else {
      getUINativeModule().web.setDefaultFontSize(node, this.value);
    }
  }
}
WebDefaultFontSizeModifier.identity = Symbol('webDefaultFontSizeModifier');

class WebDefaultFixedFontSizeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetDefaultFixedFontSize(node);
    } else {
      getUINativeModule().web.setDefaultFixedFontSize(node, this.value);
    }
  }
}
WebDefaultFixedFontSizeModifier.identity = Symbol('webDefaultFixedFontSizeModifier');

class WebMinLogicalFontSizeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetMinLogicalFontSize(node);
    } else {
      getUINativeModule().web.setMinLogicalFontSize(node, this.value);
    }
  }
}
WebMinLogicalFontSizeModifier.identity = Symbol('webMinLogicalFontSizeModifier');

class WebStandardFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebStandardFont(node);
    } else {
      getUINativeModule().web.setWebStandardFont(node, this.value);
    }
  }
}
WebStandardFontModifier.identity = Symbol('webStandardFontModifier');

class WebSerifFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebSerifFont(node);
    } else {
      getUINativeModule().web.setWebSerifFont(node, this.value);
    }
  }
}
WebSerifFontModifier.identity = Symbol('webSerifFontModifier');

class WebSansSerifFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebSansSerifFont(node);
    } else {
      getUINativeModule().web.setWebSansSerifFont(node, this.value);
    }
  }
}
WebSansSerifFontModifier.identity = Symbol('webSansSerifFontModifier');

class WebFixedFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebFixedFont(node);
    } else {
      getUINativeModule().web.setWebFixedFont(node, this.value);
    }
  }
}
WebFixedFontModifier.identity = Symbol('webFixedFontModifier');

class WebFantasyFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebFantasyFont(node);
    } else {
      getUINativeModule().web.setWebFantasyFont(node, this.value);
    }
  }
}
WebFantasyFontModifier.identity = Symbol('webFantasyFontModifier');

class WebCursiveFontModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetWebCursiveFont(node);
    } else {
      getUINativeModule().web.setWebCursiveFont(node, this.value);
    }
  }
}
WebCursiveFontModifier.identity = Symbol('webCursiveFontModifier');

class WebLayoutModeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetLayoutMode(node);
    } else {
      getUINativeModule().web.setLayoutMode(node, this.value);
    }
  }
}
WebLayoutModeModifier.identity = Symbol('webLayoutModeModifier');

class WebOnNativeEmbedLifecycleChangeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedLifecycleChange(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedLifecycleChange(node, this.value);
    }
  }
}
WebOnNativeEmbedLifecycleChangeModifier.identity = Symbol('webOnNativeEmbedLifecycleChangeModifier');

class WebOnNativeEmbedGestureEventModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedGestureEvent(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedGestureEvent(node, this.value);
    }
  }
}
WebOnNativeEmbedGestureEventModifier.identity = Symbol('webOnNativeEmbedGestureEventModifier');

class WebOnNativeEmbedMouseEventModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedMouseEvent(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedMouseEvent(node, this.value);
    }
  }
}
WebOnNativeEmbedMouseEventModifier.identity = Symbol('webOnNativeEmbedMouseEventModifier');

class WebOnNativeEmbedObjectParamChangeModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedObjectParamChange(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedObjectParamChange(node, this.value);
    }
  }
}
WebOnNativeEmbedObjectParamChangeModifier.identity = Symbol('webOnNativeEmbedObjectParamChangeModifier');

class WebRegisterNativeEmbedRuleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetRegisterNativeEmbedRule(node);
    } else {
      getUINativeModule().web.setRegisterNativeEmbedRule(node, this.value?.tag, this.value?.type);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.tag, this.value.tag) ||
      !isBaseOrResourceEqual(this.stageValue.type, this.value.type);
  }
}
WebRegisterNativeEmbedRuleModifier.identity = Symbol('webRegisterNativeEmbedRuleModifier');

class WebNativeEmbedOptionsModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetNativeEmbedOptions(node);
    } else {
      getUINativeModule().web.setNativeEmbedOptions(node, this.value);
    }
  }
}
WebNativeEmbedOptionsModifier.identity = Symbol('webNativeEmbedOptionsModifier');

class WebOnFirstContentfulPaintModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnFirstContentfulPaint(node);
    } else {
      getUINativeModule().web.setOnFirstContentfulPaint(node, this.value);
    }
  }
}
WebOnFirstContentfulPaintModifier.identity = Symbol('webOnFirstContentfulPaintModifier');

class WebOnAudioStateChangedModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnAudioStateChanged(node);
    } else {
      getUINativeModule().web.setOnAudioStateChanged(node, this.value);
    }
  }
}
WebOnAudioStateChangedModifier.identity = Symbol('webOnAudioStateChangedModifier');

class WebOnFullScreenExitModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnFullScreenExit(node);
    } else {
      getUINativeModule().web.setOnFullScreenExit(node, this.value);
    }
  }
}
WebOnFullScreenExitModifier.identity = Symbol('webOnFullScreenExitModifier');

class WebImageAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetImageAccess(node);
    } else {
      getUINativeModule().web.setImageAccess(node, this.value);
    }
  }
}
WebImageAccessModifier.identity = Symbol('webImageAccessModifier');

class WebOnlineImageAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnlineImageAccess(node);
    } else {
      getUINativeModule().web.setOnlineImageAccess(node, this.value);
    }
  }
}
WebOnlineImageAccessModifier.identity = Symbol('webOnlineImageAccessModifier');

class WebEnableFullscreenVideoOverlayModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableFullscreenVideoOverlay(node);
    } else {
      getUINativeModule().web.setEnableFullscreenVideoOverlay(node, this.value);
    }
  }
}
WebEnableFullscreenVideoOverlayModifier.identity = Symbol('webEnableFullscreenVideoOverlayModifier');

class WebMediaPlayGestureAccessModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetMediaPlayGestureAccess(node);
    } else {
      getUINativeModule().web.setMediaPlayGestureAccess(node, this.value);
    }
  }
}
WebMediaPlayGestureAccessModifier.identity = Symbol('webMediaPlayGestureAccessModifier');

class WebMediaOptionsModifier extends ModifierWithKey {
  constructor (value) {
    super(value);
  }
  applyPeer (node, reset) {
    if (reset) {
      getUINativeModule().web.resetMediaOptions(node);
    } else {
      getUINativeModule().web.setMediaOptions(node, this.value?.resumeInterval, this.value?.audioExclusive);
    }
  }
}
WebMediaOptionsModifier.identity = Symbol('webMediaOptionsModifier');

class WebOnPageEndModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnPageEnd(node);
        }
        else {
            getUINativeModule().web.setOnPageEnd(node, this.value);
        }
    }
}
WebOnPageEndModifier.identity = Symbol('webOnPageEndModifier');

class WebOnPageBeginModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnPageBegin(node);
        }
        else {
            getUINativeModule().web.setOnPageBegin(node, this.value);
        }
    }
}
WebOnPageBeginModifier.identity = Symbol('webOnPageBeginModifier');

class WebOnProgressChangeModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnProgressChange(node);
        }
        else {
            getUINativeModule().web.setOnProgressChange(node, this.value);
        }
    }
}
WebOnProgressChangeModifier.identity = Symbol('webOnProgressChangeModifier');

class WebOnTitleReceiveModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnTitleReceive(node);
        }
        else {
            getUINativeModule().web.setOnTitleReceive(node, this.value);
        }
    }
}
WebOnTitleReceiveModifier.identity = Symbol('webOnTitleReceiveModifier');

class WebOnDownloadStartModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnDownloadStart(node);
        }
        else {
            getUINativeModule().web.setOnDownloadStart(node, this.value);
        }
    }
}
WebOnDownloadStartModifier.identity = Symbol('webOnDownloadStartModifier');

class WebJavaScriptOnDocumentStartModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetJavaScriptOnDocumentStart(node);
        }
        else {
            getUINativeModule().web.setJavaScriptOnDocumentStart(node,
                this.value.scripts, this.value.scriptRules);
        }
    }
}
WebJavaScriptOnDocumentStartModifier.identity = Symbol('webJavaScriptOnDocumentStartModifier');

class WebJavaScriptOnDocumentEndModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetJavaScriptOnDocumentEnd(node);
        }
        else {
            getUINativeModule().web.setJavaScriptOnDocumentEnd(node,
                this.value.scripts, this.value.scriptRules);
        }
    }
}
WebJavaScriptOnDocumentEndModifier.identity = Symbol('webJavaScriptOnDocumentEndModifier');

class WebDomStorageAccessModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetDomStorageAccess(node);
        }
        else {
            getUINativeModule().web.setDomStorageAccess(node, this.value);
        }
    }
}
WebDomStorageAccessModifier.identity = Symbol('webDomStorageAccessModifier');

class WebCopyOptionsModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetCopyOption(node);
        }
        else {
            getUINativeModule().web.setCopyOption(node, this.value);
        }
    }
}
WebCopyOptionsModifier.identity = Symbol('webCopyOptionsModifier');

class WebOnRenderProcessNotRespondingModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnRenderProcessNotResponding(node);
        }
        else {
            getUINativeModule().web.setOnRenderProcessNotResponding(node, this.value);
        }
    }
}
WebOnRenderProcessNotRespondingModifier.identity = Symbol('webOnRenderProcessNotRespondingModifier');

class WebOnPageVisibleModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnPageVisible(node);
        }
        else {
            getUINativeModule().web.setOnPageVisible(node, this.value);
        }
    }
}
WebOnPageVisibleModifier.identity = Symbol('webOnPageVisibleModifier');

class WebOnRenderExitedModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnRenderExited(node);
        }
        else {
            getUINativeModule().web.setOnRenderExited(node, this.value);
        }
    }
}
WebOnRenderExitedModifier.identity = Symbol('webOnRenderExitedModifier');

class WebBlockNetworkModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetBlockNetwork(node);
        }
        else {
            getUINativeModule().web.setBlockNetwork(node, this.value);
        }
    }
}
WebBlockNetworkModifier.identity = Symbol('webBlockNetworkModifier');

class WebOnRefreshAccessedHistoryModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnRefreshAccessedHistory(node);
        }
        else {
            getUINativeModule().web.setOnRefreshAccessedHistory(node, this.value);
        }
    }
}
WebOnRefreshAccessedHistoryModifier.identity = Symbol('webOnRefreshAccessedHistoryModifier');

class WebOnResourceLoadModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnResourceLoad(node);
        }
        else {
            getUINativeModule().web.setOnResourceLoad(node, this.value);
        }
    }
}
WebOnResourceLoadModifier.identity = Symbol('webOnResourceLoadModifier');

class WebOnNavigationEntryCommittedModifier extends ModifierWithKey {
    constructor(value) {
        super(value);
    }
    applyPeer(node, reset) {
        if (reset) {
            getUINativeModule().web.resetOnNavigationEntryCommitted(node);
        }
        else {
            getUINativeModule().web.setOnNavigationEntryCommitted(node, this.value);
        }
    }
}
WebOnNavigationEntryCommittedModifier.identity = Symbol('webOnNavigationEntryCommittedModifier');

class WebOnSearchResultReceiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnSearchResultReceive(node);
    }
    else {
      getUINativeModule().web.setOnSearchResultReceive(node, this.value);
    }
  }
}
WebOnSearchResultReceiveModifier.identity = Symbol('webOnSearchResultReceiveModifier');

class WebOverScrollModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOverScrollMode(node);
    }
    else {
      getUINativeModule().web.setOverScrollMode(node, this.value);
    }
}
}
WebOverScrollModeModifier.identity = Symbol('webOverScrollModeModifier');

class WebOnRenderProcessRespondingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnRenderProcessResponding(node);
    }
    else {
      getUINativeModule().web.setOnRenderProcessResponding(node, this.value);
    }
}
}
WebOnRenderProcessRespondingModifier.identity = Symbol('webOnRenderProcessRespondingModifier');

class WebOnTouchIconUrlReceivedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnTouchIconUrlReceived(node);
    }
    else {
      getUINativeModule().web.setOnTouchIconUrlReceived(node, this.value);
    }
}
}
WebOnTouchIconUrlReceivedModifier.identity = Symbol('webOnTouchIconUrlReceivedModifier');

class WebOnGeolocationShowModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnGeolocationShow(node);
    } else {
      getUINativeModule().web.setOnGeolocationShow(node, this.value);
    }
  }
}
WebOnGeolocationShowModifier.identity = Symbol('webOnGeolocationShowModifier');

class WebOnWindowNewModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnWindowNew(node);
    } else {
      getUINativeModule().web.setOnWindowNew(node, this.value);
    }
  }
}
WebOnWindowNewModifier.identity = Symbol('webOnWindowNewModifier');

class WebOnWindowNewExtModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnWindowNewExt(node);
    } else {
      getUINativeModule().web.setOnWindowNewExt(node, this.value);
    }
  }
}
WebOnWindowNewExtModifier.identity = Symbol('webOnWindowNewExtModifier');

class WebOnPermissionRequestModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnPermissionRequest(node);
    } else {
      getUINativeModule().web.setOnPermissionRequest(node, this.value);
    }
  }
}
WebOnPermissionRequestModifier.identity = Symbol('webOnPermissionRequestModifier');

class WebOnScreenCaptureRequestModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnScreenCaptureRequest(node);
      }
      else {
        getUINativeModule().web.setOnScreenCaptureRequest(node, this.value);
      }
  }
}
WebOnScreenCaptureRequestModifier.identity = Symbol('webOnScreenCaptureRequestModifier');

class WebOnFullScreenEnterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnFullScreenEnter(node);
    }
    else {
      getUINativeModule().web.setOnFullScreenEnter(node, this.value);
    }
  }
}
WebOnFullScreenEnterModifier.identity = Symbol('webOnFullScreenEnterModifier');

class WebOnWindowExitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnWindowExit(node);
    }
    else {
      getUINativeModule().web.setOnWindowExit(node, this.value);
    }
}
}
WebOnWindowExitModifier.identity = Symbol('webOnWindowExitModifier');

class WebOnAlertModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnAlert(node);
      }
      else {
        getUINativeModule().web.setOnAlert(node, this.value);
      }
  }
}
WebOnAlertModifier.identity = Symbol('webOnAlertModifier');

class WebOnConfirmModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnConfirm(node);
      }
      else {
        getUINativeModule().web.setOnConfirm(node, this.value);
      }
  }
}
WebOnConfirmModifier.identity = Symbol('webOnConfirmModifier');

class WebOnPromptModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnPrompt(node);
      }
      else {
        getUINativeModule().web.setOnPrompt(node, this.value);
      }
  }
}
WebOnPromptModifier.identity = Symbol('webOnPromptModifier');

class WebOnShowFileSelectorModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
          getUINativeModule().web.resetOnShowFileSelector(node);
      } else {
          getUINativeModule().web.setOnShowFileSelector(node, this.value);
      }
  }
}
WebOnShowFileSelectorModifier.identity = Symbol('webOnShowFileSelectorModifier');

class WebOnTextSelectionChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnTextSelectionChange(node);
    }
    else {
      getUINativeModule().web.setOnTextSelectionChange(node, this.value);
    }
  }
}
WebOnTextSelectionChangeModifier.identity = Symbol('webOnTextSelectionChangeModifier');

class WebOnDetectedBlankScreenModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnDetectedBlankScreen(node);
    }
    else {
      getUINativeModule().web.setOnDetectedBlankScreen(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
WebOnDetectedBlankScreenModifier.identity = Symbol('webOnDetectedBlankScreenModifier');

class WebBlankScreenDetectionConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetBlankScreenDetectionConfig(node);
    }
    else {
      getUINativeModule().web.setBlankScreenDetectionConfig(node,
                                                            this.value.enable,
                                                            this.value.detectionTiming,
                                                            this.value.detectionMethods,
                                                            this.value.contentfulNodesCountThreshold);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
WebBlankScreenDetectionConfigModifier.identity = Symbol('webBlankScreenDetectionConfigModifier');

class WebOnFirstScreenPaintModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnFirstScreenPaint(node);
    } else {
      getUINativeModule().web.setOnFirstScreenPaint(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
WebOnFirstScreenPaintModifier.identity = Symbol('webOnFirstScreenPaintModifier');

class WebOnContextMenuShowModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnContextMenuShow(node);
      } else {
        getUINativeModule().web.setOnContextMenuShow(node, this.value);
      }
  }
}
WebOnContextMenuShowModifier.identity = Symbol('webOnContextMenuShowModifier');

class WebOnSafeBrowsingCheckResultModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnSafeBrowsingCheckResult(node);
      } else {
        getUINativeModule().web.setOnSafeBrowsingCheckResult(node, this.value);
      }
  }
}
WebOnSafeBrowsingCheckResultModifier.identity = Symbol('webOnSafeBrowsingCheckResultModifier');

class WebNestedScrollModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
          getUINativeModule().web.resetNestedScroll(node);
      } else {
          getUINativeModule().web.setNestedScroll(node, this.value.scrollUp, this.value.scrollDown,
              this.value.scrollLeft, this.value.scrollRight);
      }
  }
}

class WebOnInterceptKeyEventModifier extends ModifierWithKey {
    constructor(value) {
      super(value);
    }
    applyPeer(node, reset) {
      if (reset) {
        getUINativeModule().web.resetOnInterceptKeyEvent(node);
      }
      else {
        getUINativeModule().web.setOnInterceptKeyEvent(node, this.value);
      }
  }
}
WebOnInterceptKeyEventModifier.identity = Symbol('webOnInterceptKeyEventModifier');

class WebOnErrorReceiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnErrorReceive(node);
    }
    else {
      getUINativeModule().web.setOnErrorReceive(node, this.value);
    }
  }
}
WebOnErrorReceiveModifier.identity = Symbol('webOnErrorReceiveModifier');

class WebOnLoadInterceptModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnLoadIntercept(node);
    }
    else {
      getUINativeModule().web.setOnLoadIntercept(node, this.value);
    }
  }
}
WebOnLoadInterceptModifier.identity = Symbol('webOnLoadInterceptModifier');

class WebOnHttpErrorReceiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnHttpErrorReceive(node);
    }
    else {
      getUINativeModule().web.setOnHttpErrorReceive(node, this.value);
    }
  }
}
WebOnHttpErrorReceiveModifier.identity = Symbol('webOnHttpErrorReceiveModifier');

class WebOnOverrideUrlLoadingModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnOverrideUrlLoading(node);
    }
    else {
      getUINativeModule().web.setOnOverrideUrlLoading(node, this.value);
    }
  }
}
WebOnOverrideUrlLoadingModifier.identity = Symbol('webOnOverrideUrlLoadingModifier');

class WebOnHttpAuthRequestModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnHttpAuthRequest(node);
    }
    else {
      getUINativeModule().web.setOnHttpAuthRequest(node, this.value);
    }
  }
}
WebOnHttpAuthRequestModifier.identity = Symbol('webOnHttpAuthRequestModifier');

class WebOnConsoleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnConsole(node);
    }
    else {
      getUINativeModule().web.setOnConsole(node, this.value);
    }
  }
}
WebOnConsoleModifier.identity = Symbol('webOnConsoleModifier');

class WebOnSslErrorEventModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnSslErrorEvent(node);
    }
    else {
      getUINativeModule().web.setOnSslErrorEvent(node, this.value);
    }
  }
}
WebOnSslErrorEventModifier.identity = Symbol('webOnSslErrorEventModifier');

class WebOnDataResubmittedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnDataResubmitted(node);
    }
    else {
      getUINativeModule().web.setOnDataResubmitted(node, this.value);
    }
  }
}
WebOnDataResubmittedModifier.identity = Symbol('webOnDataResubmittedModifier');

class WebEnableDataDetectorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableDataDetector(node);
    } else {
      getUINativeModule().web.setEnableDataDetector(node, this.value);
    }
  }
}
WebEnableDataDetectorModifier.identity = Symbol('webEnableDataDetectorModifier');

class WebDataDetectorConfigModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetDataDetectorConfig(node);
    } else {
      getUINativeModule().web.setDataDetectorConfig(node, this.value.types, this.value.onDetectResultUpdate,
        this.value.color, this.value.decorationType, this.value.decorationColor, this.value.decorationStyle, this.value.enablePreviewMenu);
    }
  }
}
WebDataDetectorConfigModifier.identity = Symbol('webDataDetectorConfigModifier');

class WebEnableSelectedDataDetectorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableSelectedDataDetector(node);
    } else {
      getUINativeModule().web.setEnableSelectedDataDetector(node, this.value);
    }
  }
}
WebEnableSelectedDataDetectorModifier.identity = Symbol('webEnableSelectedDataDetectorModifier');

class WebGestureFocusModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetGestureFocusMode(node);
    }
    else {
      getUINativeModule().web.setGestureFocusMode(node, this.value);
    }
  }
}
WebGestureFocusModeModifier.identity = Symbol('webGestureFocusModeModifier');

class WebRotateRenderEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetRotateRenderEffect(node);
    }
    else {
      getUINativeModule().web.setRotateRenderEffect(node, this.value);
    }
  }
}
WebRotateRenderEffectModifier.identity = Symbol('webRotateRenderEffectModifier');

class WebOnSslErrorEventReceiveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnSslErrorEventReceive(node);
    } else {
      getUINativeModule().web.setOnSslErrorEventReceive(node, this.value);
    }
  }
}
WebOnSslErrorEventReceiveModifier.identity = Symbol('webOnSslErrorEventReceiveModifier');

class WebOnClientAuthenticationRequestModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnClientAuthenticationRequest(node);
    }
    else {
      getUINativeModule().web.setOnClientAuthenticationRequest(node, this.value);
    }
  }
}
WebOnClientAuthenticationRequestModifier.identity = Symbol('webOnClientAuthenticationRequestModifier');

class WebOnInterceptRequestModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnInterceptRequest(node);
    }
    else {
      getUINativeModule().web.setOnInterceptRequest(node, this.value);
    }
  }
}
WebOnInterceptRequestModifier.identity = Symbol('webOnInterceptRequestModifier');

class WebOnFaviconReceivedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnFaviconReceived(node);
    }
    else {
      getUINativeModule().web.setOnFaviconReceived(node, this.value);
    }
  }
}
WebOnFaviconReceivedModifier.identity = Symbol('webOnFaviconReceivedModifier');

class WebOnBeforeUnloadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnBeforeUnload(node);
    }
    else {
      getUINativeModule().web.setOnBeforeUnload(node, this.value);
    }
  }
}
WebOnBeforeUnloadModifier.identity = Symbol('webOnBeforeUnloadModifier');

class WebJavaScriptProxyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetJavaScriptProxy(node);
    } else {
      getUINativeModule().web.setJavaScriptProxy(node, this.value.object, this.value.name, this.value.methodList,
        this.value.controller, this.value?.asyncMethodList, this.value?.permission);
    }
  }
}
WebJavaScriptProxyModifier.identity = Symbol('webJavaScriptProxyModifier');

class WebEnableImageAnalyzerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableImageAnalyzer(node);
    } else {
      getUINativeModule().web.setEnableImageAnalyzer(node, this.value);
    }
  }
}
WebEnableImageAnalyzerModifier.identity = Symbol('webEnableImageAnalyzerModifier');

class WebForceEnableZoomModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetForceEnableZoom(node);
    } else {
      getUINativeModule().web.setForceEnableZoom(node, this.value);
    }
  }
}
WebForceEnableZoomModifier.identity = Symbol('webForceEnableZoomModifier');

class WebBackToTopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetBackToTop(node);
    } else {
      getUINativeModule().web.setBackToTop(node, this.value);
    }
  }
}
WebBackToTopModifier.identity = Symbol('webBackToTopModifier');

class WebOnCameraCaptureStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnCameraCaptureStateChanged(node);
    }
    else {
      getUINativeModule().web.setOnCameraCaptureStateChanged(node, this.value);
    }
  }
}
WebOnCameraCaptureStateChangeModifier.identity = Symbol('webOnCameraCaptureStateChangeModifier');

class WebOnMicrophoneCaptureStateChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnMicrophoneCaptureStateChanged(node);
    }
    else {
      getUINativeModule().web.setOnMicrophoneCaptureStateChanged(node, this.value);
    }
  }
}
WebOnMicrophoneCaptureStateChangeModifier.identity = Symbol('webOnMicrophoneCaptureStateChangeModifier');

class WebOnInputMethodAttachedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetOnInputMethodAttached(node);
    }
    else {
      getUINativeModule().web.setOnInputMethodAttached(node, this.value);
    }
  }
}
WebOnInputMethodAttachedModifier.identity = Symbol('webOnInputMethodAttachedModifier');

class WebEnableAutoFillModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableAutoFill(node);
    } else {
      getUINativeModule().web.setEnableAutoFill(node, this.value);
    }
  }
}
WebEnableAutoFillModifier.identity = Symbol('webEnableAutoFillModifier');

class WebEnableDragModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableDrag(node);
    } else {
      getUINativeModule().web.setEnableDrag(node, this.value);
    }
  }
}
WebEnableDragModifier.identity = Symbol('webEnableDragModifier');

class WebEnableDefaultContextMenuModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableDefaultContextMenu(node);
    } else {
      getUINativeModule().web.setEnableDefaultContextMenu(node, this.value);
    }
  }
}
WebEnableDefaultContextMenuModifier.identity = Symbol('webEnableDefaultContextMenuModifier');

class WebAiSessionOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetAiSessionOptions(node);
    } else {
      getUINativeModule().web.setAiSessionOptions(node, this.value);
    }
  }
}
WebAiSessionOptionsModifier.identity = Symbol('webAiSessionOptionsModifier');

class WebEnableScrollDirectionalLockModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetEnableScrollDirectionalLock(node);
    } else {
      getUINativeModule().web.setEnableScrollDirectionalLock(node, this.value.value, this.value.type);
    }
  }
}
WebEnableScrollDirectionalLockModifier.identity = Symbol('webEnableScrollDirectionalLockModifier');

class WebEnableNativeMediaPlayerModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
          getUINativeModule().web.resetEnableNativeMediaPlayer(node);
      } else {
          getUINativeModule().web.setEnableNativeMediaPlayer(node, this.value);
      }
  }
}
WebEnableNativeMediaPlayerModifier.identity = Symbol('webEnableNativeMediaPlayerModifier');

class WebEnableWebAVSessionModifier extends ModifierWithKey {
  constructor(value) {
      super(value);
  }
  applyPeer(node, reset) {
      if (reset) {
          getUINativeModule().web.resetEnableWebAVSession(node);
      } else {
          getUINativeModule().web.setEnableWebAVSession(node, this.value);
      }
  }
}
WebEnableWebAVSessionModifier.identity = Symbol('webEnableWebAVSessionModifier');

class WebScrollbarLayoutPolicyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().web.resetScrollbarLayoutPolicy(node);
    } else {
      getUINativeModule().web.setScrollbarLayoutPolicy(node, this.value);
    }
  }
}
WebScrollbarLayoutPolicyModifier.identity = Symbol('webScrollbarLayoutPolicyModifier');

// @ts-ignore
if (globalThis.Web !== undefined) {
  globalThis.Web.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkWebComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkXComponentComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  allowChildCount() {
    if (this.xComponentType === XComponentType.COMPONENT) {
      return undefined;
    }
    return 0;
  }
  initialize(value) {
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      this.xComponentType = value[0].type;
      this.libraryname = value[0].libraryname;
      modifierWithKey(this._modifiersWithKeys, XComponentInitializeModifier.identity,
        XComponentInitializeModifier, value[0]);
    }
    return this;
  }
  applyModifierPatch() {
    let expiringItemsWithKeys = [];
    this._modifiersWithKeys.forEach((value, key) => {
      if (value.applyStage(this.nativePtr, this)) {
        expiringItemsWithKeys.push(key);
      }
    });
    expiringItemsWithKeys.forEach(key => {
      this._modifiersWithKeys.delete(key);
    });
  }
  background(builder, options) {
    throw new BusinessError(100201, 'background Method not supportted in ArkXComponentComponent class.');
  }
  backgroundColor(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentBackgroundColorModifier.identity, XComponentBackgroundColorModifier, value);
    return this;
  }
  backgroundImage(src, repeat) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let arkBackgroundImage = new ArkBackgroundImage();
    arkBackgroundImage.src = src;
    arkBackgroundImage.repeat = repeat;
    modifierWithKey(this._modifiersWithKeys, BackgroundImageModifier.identity, BackgroundImageModifier, arkBackgroundImage);
    return this;
  }
  backgroundImageSize(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundImageSizeModifier.identity, BackgroundImageSizeModifier, value);
    return this;
  }
  backgroundImagePosition(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, BackgroundImagePositionModifier.identity, BackgroundImagePositionModifier, value);
    return this;
  }
  opacity(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentOpacityModifier.identity, XComponentOpacityModifier, value);
    return this;
  }
  foregroundColor(value) {
    throw new BusinessError(100201, 'foregroundColor Method not supportted in ArkXComponentComponent class.');
  }
  onClick(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, ClickModifier.identity, ClickModifier, event);
    }
    return this;
  }
  onHover(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnHoverModifier.identity, OnHoverModifier, event);
    }
    return this;
  }
  onHoverMove(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnHoverMoveModifier.identity, OnHoverMoveModifier, event);
    }
    return this;
  }
  onMouse(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnMouseModifier.identity, OnMouseModifier, event);
    }
    return this;
  }
  onTouch(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnTouchModifier.identity, OnTouchModifier, event);
    }
    return this;
  }
  onKeyEvent(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnKeyEventModifier.identity, OnKeyEventModifier, event);
    }
    return this;
  }
  onFocus(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnFocusModifier.identity, OnFocusModifier, event);
    }
    return this;
  }
  onNeedSoftkeyboard(onNeedSoftkeyboardCallback) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnNeedSoftkeyboardModifier.identity, OnNeedSoftkeyboardModifier, onNeedSoftkeyboardCallback);
    }
    return this;
  }
  onBlur(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnBlurModifier.identity, OnBlurModifier, event);
    }
    return this;
  }
  animation(value) {
    throw new BusinessError(100201, 'animation Method not supportted in ArkXComponentComponent class.');
  }
  gesture(gesture, mask) {
    throw new BusinessError(100201, 'gesture Method not supportted in ArkXComponentComponent class.');
  }
  priorityGesture(gesture, mask) {
    throw new BusinessError(100201, 'priorityGesture Method not supportted in ArkXComponentComponent class.');
  }
  parallelGesture(gesture, mask) {
    throw new BusinessError(100201, 'parallelGesture Method not supportted in ArkXComponentComponent class.');
  }
  blur(value, options, sysOptions) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let blur = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    if (typeof sysOptions === 'object') {
      blur.disableSystemAdaptation = sysOptions.disableSystemAdaptation;
    }
    modifierWithKey(this._modifiersWithKeys, BlurModifier.identity, BlurModifier, blur);
    return this;
  }
  linearGradientBlur(value, options) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
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
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, BrightnessModifier.identity, BrightnessModifier, value);
    }
    return this;
  }
  contrast(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, ContrastModifier.identity, ContrastModifier, value);
    }
    return this;
  }
  grayscale(value) {
    modifierWithKey(this._modifiersWithKeys, GrayscaleModifier.identity, GrayscaleModifier, value);
    return this;
  }
  colorBlend(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, ColorBlendModifier.identity, ColorBlendModifier, value);
    return this;
  }
  saturate(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SaturateModifier.identity, SaturateModifier, value);
    }
    return this;
  }
  sepia(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value)) {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, SepiaModifier.identity, SepiaModifier, value);
    }
    return this;
  }
  invert(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isUndefined(value)) {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, InvertModifier.identity, InvertModifier, undefined);
    }
    return this;
  }
  hueRotate(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    if (!isNumber(value) && !isString(value)) {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, undefined);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, HueRotateModifier.identity, HueRotateModifier, value);
    }
    return this;
  }
  useEffect(value) {
    throw new BusinessError(100201, 'useEffect Method not supportted in ArkXComponentComponent class.');
  }
  backdropBlur(value, options, sysOptions) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    let blur = new ArkBlurOptions();
    blur.value = value;
    blur.options = options;
    if (typeof sysOptions === 'object') {
      blur.disableSystemAdaptation = sysOptions.disableSystemAdaptation;
    }
    modifierWithKey(this._modifiersWithKeys, BackdropBlurModifier.identity, BackdropBlurModifier, blur);
    return this;
  }
  renderGroup(value) {
    throw new BusinessError(100201, 'renderGroup Method not supportted in ArkXComponentComponent class.');
  }
  onAppear(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnAppearModifier.identity, OnAppearModifier, event);
    }
    return this;
  }
  onDisAppear(event) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnDisappearModifier.identity, OnDisappearModifier, event);
    }
    return this;
  }
  onAttach(callback) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnAttachModifier.identity, OnAttachModifier, callback);
    }
    return this;
  }
  onDetach(callback) {
    if (this.xComponentType === XComponentType.NODE || isUndefined(this.libraryname)) {
      modifierWithKey(this._modifiersWithKeys, OnDetachModifier.identity, OnDetachModifier, callback);
    }
    return this;
  }
  flexGrow(value) {
    throw new BusinessError(100201, 'flexGrow Method not supportted in ArkXComponentComponent class.');
  }
  direction(value) {
    throw new BusinessError(100201, 'direction Method not supportted in ArkXComponentComponent class.');
  }
  align(value) {
    throw new BusinessError(100201, 'align Method not supportted in ArkXComponentComponent class.');
  }
  useSizeType(value) {
    throw new BusinessError(100201, 'useSizeType Method not supportted in ArkXComponentComponent class.');
  }
  clip(value) {
    throw new BusinessError(100201, 'clip Method not supportted in ArkXComponentComponent class.');
  }
  geometryTransition(id) {
    throw new BusinessError(100201, 'geometryTransition Method not supportted in ArkXComponentComponent class.');
  }
  bindPopup(show, popup) {
    throw new BusinessError(100201, 'bindPopup Method not supportted in ArkXComponentComponent class.');
  }
  bindMenu(content, options) {
    throw new BusinessError(100201, 'bindMenu Method not supportted in ArkXComponentComponent class.');
  }
  bindContextMenu(content, responseType, options) {
    throw new BusinessError(100201, 'bindContextMenu Method not supportted in ArkXComponentComponent class.');
  }
  bindContentCover(isShow, builder, options) {
    throw new BusinessError(100201, 'bindContentCover Method not supportted in ArkXComponentComponent class.');
  }
  bindSheet(isShow, builder, options) {
    throw new BusinessError(100201, 'bindSheet Method not supportted in ArkXComponentComponent class.');
  }
  stateStyles(value) {
    throw new BusinessError(100201, 'stateStyles Method not supportted in ArkXComponentComponent class.');
  }
  restoreId(value) {
    throw new BusinessError(100201, 'restoreId Method not supportted in ArkXComponentComponent class.');
  }
  onVisibleAreaChange(ratios, event) {
    throw new BusinessError(100201, 'onVisibleAreaChange Method not supportted in ArkXComponentComponent class.');
  }
  sphericalEffect(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, SphericalEffectModifier.identity, SphericalEffectModifier, value);
    return this;
  }
  lightUpEffect(value) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, LightUpEffectModifier.identity, LightUpEffectModifier, value);
    return this;
  }
  pixelStretchEffect(options) {
    if (this.xComponentType !== XComponentType.NODE) {
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, PixelStretchEffectModifier.identity, PixelStretchEffectModifier, options);
    return this;
  }
  accessibilityGroup(value) {
    throw new BusinessError(100201, 'accessibilityGroup Method not supportted in ArkXComponentComponent class.');
  }
  obscured(reasons) {
    throw new BusinessError(100201, 'obscured Method not supportted in ArkXComponentComponent class.');
  }
  reuseId(id) {
    throw new BusinessError(100201, 'reuseId Method not supportted in ArkXComponentComponent class.');
  }
  renderFit(fitMode) {
    modifierWithKey(this._modifiersWithKeys, XComponentRenderFitModifier.identity, XComponentRenderFitModifier, fitMode);
    return this;
  }
  attributeModifier(modifier) {
    return this;
  }
  onLoad(callback) {
    modifierWithKey(this._modifiersWithKeys, XComponentOnLoadModifier.identity, XComponentOnLoadModifier, callback);
    return this;
  }
  onDestroy(event) {
    modifierWithKey(this._modifiersWithKeys, XComponentOnDestroyModifier.identity, XComponentOnDestroyModifier, event);
    return this;
  }
  enableAnalyzer(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableAnalyzerModifier.identity, XComponentEnableAnalyzerModifier, value);
    return this;
  }
  enableSecure(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableSecureModifier.identity, XComponentEnableSecureModifier, value);
    return this;
  }
  hdrBrightness(value, hdrType) {
    if (isUndefined(value) || isNull(value)) {
      modifierWithKey(this._modifiersWithKeys, XComponentHdrBrightnessModifier.identity, XComponentHdrBrightnessModifier, undefined);
      return this;
    }
    modifierWithKey(this._modifiersWithKeys, XComponentHdrBrightnessModifier.identity, XComponentHdrBrightnessModifier,
      { brightness: value, hdrType: hdrType });
    return this;
  }
  enableTransparentLayer(value) {
    modifierWithKey(this._modifiersWithKeys, XComponentEnableTransparentLayerModifier.identity, XComponentEnableTransparentLayerModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.XComponent !== undefined) {
  globalThis.XComponent.attributeModifier = function (modifier) {
    const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
    let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
    let component = this.createOrGetNode(elmtId, () => {
      return new ArkXComponentComponent(nativeNode);
    });
    applyUIAttributes(modifier, nativeNode, component);
    component.applyModifierPatch();
  };
}

class XComponentInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetXComponentInitialize(node);
    }
    else {
      getUINativeModule().xComponent.setXComponentInitialize(node, this.value?.id,
        this.value?.type, this.value?.imageAIOptions, this.value?.libraryname, this.value?.controller);

    }
  }
}
XComponentInitializeModifier.identity = Symbol('xComponentInitialize');
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
class XComponentOnLoadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetOnLoad(node);
    }
    else {
      getUINativeModule().xComponent.setOnLoad(node, this.value);
    }
  }
}
XComponentOnLoadModifier.identity = Symbol('xComponentOnLoad');
class XComponentOnDestroyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetOnDestroy(node);
    }
    else {
      getUINativeModule().xComponent.setOnDestroy(node, this.value);
    }
  }
}
XComponentOnDestroyModifier.identity = Symbol('xComponentOnDestroy');
class XComponentEnableAnalyzerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetEnableAnalyzer(node);
    }
    else {
      getUINativeModule().xComponent.setEnableAnalyzer(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
XComponentEnableAnalyzerModifier.identity = Symbol('xComponentEnableAnalyzer');
class XComponentEnableSecureModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetEnableSecure(node);
    }
    else {
      getUINativeModule().xComponent.setEnableSecure(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
XComponentEnableSecureModifier.identity = Symbol('xComponentEnableSecure');
class XComponentHdrBrightnessModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetHdrBrightness(node);
    }
    else {
      getUINativeModule().xComponent.setHdrBrightness(node, this.value.brightness, this.value.hdrType);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue.brightness, this.value.brightness) ||
      !isBaseOrResourceEqual(this.stageValue.hdrType, this.value.hdrType);
  }
}
XComponentHdrBrightnessModifier.identity = Symbol('xComponentHdrBrightness');
class XComponentEnableTransparentLayerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetEnableTransparentLayer(node);
    }
    else {
      getUINativeModule().xComponent.setEnableTransparentLayer(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
XComponentEnableTransparentLayerModifier.identity = Symbol('xComponentEnableTransparentLayer');
class XComponentRenderFitModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().xComponent.resetRenderFit(node);
    }
    else {
      getUINativeModule().xComponent.setRenderFit(node, this.value);
    }
  }
}
XComponentRenderFitModifier.identity = Symbol('xComponentRenderFit');

/// <reference path='./import.ts' />
class ArkFormLinkComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
}
// @ts-ignore
if (globalThis.FormLink !== undefined) {
  globalThis.FormLink.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkFormLinkComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

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
class ListEnableEditModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetEnableEditMode(node);
    } else {
      getUINativeModule().list.setEnableEditMode(node, this.value);
    }
  }
}
ListEnableEditModeModifier.identity = Symbol('listEnableEditMode');
class ListOnEditModeChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnEditModeChange(node);
    }
    else {
      getUINativeModule().list.setOnEditModeChange(node, this.value);
    }
  }
}
ListOnEditModeChangeModifier.identity = Symbol('listOnEditModeChange');
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
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) && !isResource(_c.color) && !isResource(_d.color) &&
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
    if (reset || isUndefined(this.value)) {
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
    if (reset || isUndefined(this.value)) {
      getUINativeModule().list.resetCachedCount(node);
    }
    else {
      getUINativeModule().list.setCachedCount(node, this.value.count, this.value.show);
    }
  }
}
ListCachedCountModifier.identity = Symbol('listCachedCount');
class ListEnableScrollInteractionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || isUndefined(this.value)) {
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
class ListMaintainVisibleContentPositionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListMaintainVisibleContentPosition(node);
    } else {
      getUINativeModule().list.setListMaintainVisibleContentPosition(node, this.value);
    }
  }
}
ListMaintainVisibleContentPositionModifier.identity = Symbol('listMaintainVisibleContentPosition');
class ListStackFromEndModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListStackFromEnd(node);
    } else {
      getUINativeModule().list.setListStackFromEnd(node, this.value);
    }
  }
}
ListStackFromEndModifier.identity = Symbol('listStackFromEnd');
class ListSyncLoadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListSyncLoad(node);
    } else {
      getUINativeModule().list.setListSyncLoad(node, this.value);
    }
  }
}
ListSyncLoadModifier.identity = Symbol('listSyncLoad');
class ListEditModeOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetEditModeOptions(node);
    } else {
      getUINativeModule().list.setEditModeOptions(node, this.value);
    }
  }
}
ListEditModeOptionsModifier.identity = Symbol('listEditModeOptions');
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
class ListScrollBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListScrollBarWidth(node);
    }
    else {
      getUINativeModule().list.setListScrollBarWidth(node, this.value);
    }
  }
}
ListScrollBarWidthModifier.identity = Symbol('listScrollBarWidth');
class ListScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListScrollBarColor(node);
    }
    else {
      getUINativeModule().list.setListScrollBarColor(node, this.value);
    }
  }
}
ListScrollBarColorModifier.identity = Symbol('listScrollBarColor');
class ListLanesModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListLanes(node);
    }
    else {
      getUINativeModule().list.setListLanes(node, this.value.lanesNum, this.value.minLength, this.value.maxLength, this.value.fillType, this.value.gutter);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListLanesModifier.identity = Symbol('listLanes');
class ListClipModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().common.resetClipWithEdge(node);
    }
    else {
      getUINativeModule().common.setClipWithEdge(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListClipModifier.identity = Symbol('listClip');
class ListScrollSnapAnimationSpeedModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetScrollSnapAnimationSpeed(node);
    } else {
      getUINativeModule().list.setScrollSnapAnimationSpeed(node, this.value);
    }
  }
}
ListScrollSnapAnimationSpeedModifier.identity = Symbol('listScrollSnapAnimationSpeed');
class ListOnScrollIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnScrollIndex(node);
    } else {
      getUINativeModule().list.setOnScrollIndex(node, this.value);
    }
  }
}
ListOnScrollIndexModifier.identity = Symbol('listOnScrollIndex');
class ListOnScrollVisibleContentChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnScrollVisibleContentChange(node);
    } else {
      getUINativeModule().list.setOnScrollVisibleContentChange(node, this.value);
    }
  }
}
ListOnScrollVisibleContentChangeModifier.identity = Symbol('listOnScrollVisibleContentChange');
class ListOnItemMoveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemMove(node);
    } else {
      getUINativeModule().list.setOnItemMove(node, this.value);
    }
  }
}
ListOnItemMoveModifier.identity = Symbol('listOnItemMove');
class ListOnItemDragStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemDragStart(node);
    } else {
      getUINativeModule().list.setOnItemDragStart(node, this.value);
    }
  }
}
ListOnItemDragStartModifier.identity = Symbol('listOnItemDragStart');
class ListOnItemDragEnterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemDragEnter(node);
    } else {
      getUINativeModule().list.setOnItemDragEnter(node, this.value);
    }
  }
}
ListOnItemDragEnterModifier.identity = Symbol('listOnItemDragEnter');
class ListOnItemDragMoveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemDragMove(node);
    } else {
      getUINativeModule().list.setOnItemDragMove(node, this.value);
    }
  }
}
ListOnItemDragMoveModifier.identity = Symbol('listOnItemDragMove');
class ListOnItemDragLeaveModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemDragLeave(node);
    } else {
      getUINativeModule().list.setOnItemDragLeave(node, this.value);
    }
  }
}
ListOnItemDragLeaveModifier.identity = Symbol('listOnItemDragLeave');
class ListOnItemDropModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnItemDrop(node);
    } else {
      getUINativeModule().list.setOnItemDrop(node, this.value);
    }
  }
}
ListOnItemDropModifier.identity = Symbol('listOnItemDrop');
class ListOnScrollFrameBeginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnScrollFrameBegin(node);
    } else {
      getUINativeModule().list.setOnScrollFrameBegin(node, this.value);
    }
  }
}
ListOnScrollFrameBeginModifier.identity = Symbol('listOnScrollFrameBegin');
class ListOnWillScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnWillScroll(node);
    } else {
      getUINativeModule().list.setOnWillScroll(node, this.value);
    }
  }
}
ListOnWillScrollModifier.identity = Symbol('listOnWillScroll');
class ListOnDidScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnDidScroll(node);
    } else {
      getUINativeModule().list.setOnDidScroll(node, this.value);
    }
  }
}
ListOnDidScrollModifier.identity = Symbol('listOnDidScroll');
class ListOnReachStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnReachStart(node);
    } else {
      getUINativeModule().list.setOnReachStart(node, this.value);
    }
  }
}
ListOnReachStartModifier.identity = Symbol('listOnReachStart');
class ListOnReachEndModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnReachEnd(node);
    } else {
      getUINativeModule().list.setOnReachEnd(node, this.value);
    }
  }
}
ListOnReachEndModifier.identity = Symbol('listOnReachEnd');
class ListOnScrollStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnScrollStart(node);
    } else {
      getUINativeModule().list.setOnScrollStart(node, this.value);
    }
  }
}
ListOnScrollStartModifier.identity = Symbol('listOnScrollStart');
class ListOnScrollStopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetOnScrollStop(node);
    } else {
      getUINativeModule().list.setOnScrollStop(node, this.value);
    }
  }
}
ListOnScrollStopModifier.identity = Symbol('listOnScrollStop');

class ListChildrenMainSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetListChildrenMainSize(node);
    }
    else {
      getUINativeModule().list.setListChildrenMainSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListChildrenMainSizeModifier.identity = Symbol('listChildrenMainSize');

class ListSpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetSpace(node);
    }
    else {
      getUINativeModule().list.setSpace(node, this.value);
    }
  }
}
ListSpaceModifier.identity = Symbol('listSpace');

class ListSpaceWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetSpace(node);
    }
    else {
      getUINativeModule().list.setSpaceWidth(node, this.value);
    }
  }
}
ListSpaceWidthModifier.identity = Symbol('listSpaceWidth');

class ListInitialIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetInitialIndex(node);
    }
    else {
      getUINativeModule().list.setInitialIndex(node, this.value);
    }
  }
}
ListInitialIndexModifier.identity = Symbol('listInitialIndex');

class ListInitialScrollerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetInitialScroller(node);
    }
    else {
      getUINativeModule().list.setInitialScroller(node, this.value);
    }
  }
}
ListInitialScrollerModifier.identity = Symbol('listInitialScroller');

class ListSupportEmptyBranchInLazyLoading extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.setSupportEmptyBranchInLazyLoading(node, false);
    }
    else {
      getUINativeModule().list.setSupportEmptyBranchInLazyLoading(node, this.value);
    }
  }
}
ListSupportEmptyBranchInLazyLoading.identity = Symbol('listSupportEmptyBranchInLazyLoading');

class ListBackPressBehaviorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    const closeSwipeAction = (this.value === null || this.value === void 0 ? void 0 : this.value.closeSwipeAction) ?? true;
    if (reset) {
      getUINativeModule().list.setBackPressBehavior(node, true);
    }
    else {
      getUINativeModule().list.setBackPressBehavior(node, closeSwipeAction);
    }
  }
}
ListBackPressBehaviorModifier.identity = Symbol('listBackPressBehavior');

class ArkListComponent extends ArkScrollable {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }

  initialize(value) {
    if (value[0] !== undefined) {
      if (value[0].initialIndex !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListInitialIndexModifier.identity, ListInitialIndexModifier, value[0].initialIndex);
      }
      if (value[0].spaceWidth !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListSpaceWidthModifier.identity, ListSpaceWidthModifier, value[0].spaceWidth);
      } else if (value[0].space !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListSpaceModifier.identity, ListSpaceModifier, value[0].space);
      }
      if (value[0].scroller !== undefined) {
        modifierWithKey(this._modifiersWithKeys, ListInitialScrollerModifier.identity, ListInitialScrollerModifier, value[0].scroller);
      }
    }
    return this;
  }
  allowChildTypes() {
    return ["ListItem", "ListItemGroup"];
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
    else if (isObject(value)) {
      if (isNumber(value.fillType)) {
        opt.fillType = value.fillType;
      }
      else {
        const lc = value;
        opt.minLength = lc.minLength;
        opt.maxLength = lc.maxLength;
        if (isUndefined(opt.minLength) && isUndefined(opt.maxLength)) {
          opt.fillType = -1;
        }
      }
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
  scrollBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarWidthModifier.identity, ListScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value) {
    modifierWithKey(this._modifiersWithKeys, ListScrollBarColorModifier.identity, ListScrollBarColorModifier, value);
    return this;
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ListDividerModifier.identity, ListDividerModifier, value);
    return this;
  }
  editMode(value) {
    modifierWithKey(this._modifiersWithKeys, ListEditModeModifier.identity, ListEditModeModifier, value);
    return this;
  }
  enableEditMode(value) {
    modifierWithKey(this._modifiersWithKeys, ListEnableEditModeModifier.identity, ListEnableEditModeModifier, value);
    return this;
  }
  onEditModeChange(callback) {
    modifierWithKey(this._modifiersWithKeys, ListOnEditModeChangeModifier.identity, ListOnEditModeChangeModifier, callback);
    return this;
  }
  multiSelectable(value) {
    modifierWithKey(this._modifiersWithKeys, ListMultiSelectableModifier.identity, ListMultiSelectableModifier, value);
    return this;
  }
  cachedCount(count, show) {
    let opt = new ArkScrollableCacheOptions(count, show ? show : false);
    modifierWithKey(this._modifiersWithKeys, ListCachedCountModifier.identity, ListCachedCountModifier, opt);
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
  focusWrapMode(value) {
    modifierWithKey(this._modifiersWithKeys, ListFocusWrapModeModifier.identity, ListFocusWrapModeModifier, value);
    return this;
  }
  maintainVisibleContentPosition(value) {
    modifierWithKey(this._modifiersWithKeys, ListMaintainVisibleContentPositionModifier.identity,
      ListMaintainVisibleContentPositionModifier, value);
    return this;
  }
  stackFromEnd(value) {
    modifierWithKey(this._modifiersWithKeys, ListStackFromEndModifier.identity, ListStackFromEndModifier, value);
    return this;
  }
  syncLoad(value) {
    modifierWithKey(this._modifiersWithKeys, ListSyncLoadModifier.identity,
      ListSyncLoadModifier, value);
    return this;
  }
  editModeOptions(options) {
    modifierWithKey(this._modifiersWithKeys, ListEditModeOptionsModifier.identity, ListEditModeOptionsModifier, options);
    return this;
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, ListClipModifier.identity, ListClipModifier, value);
    return this;
  }
  scrollSnapAnimationSpeed(value) {
    modifierWithKey(this._modifiersWithKeys,
      ListScrollSnapAnimationSpeedModifier.identity, ListScrollSnapAnimationSpeedModifier, value);
    return this;
  }
  onScroll(event) {
    throw new BusinessError(100201, 'onScroll not supported in attributeModifier scenario.');
  }
  onScrollIndex(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollIndexModifier.identity, ListOnScrollIndexModifier, event);
    return this;
  }
  onScrollVisibleContentChange(callback) {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollVisibleContentChangeModifier.identity, ListOnScrollVisibleContentChangeModifier, callback);
    return this;
  }
  onItemDelete(event) {
    throw new BusinessError(100201, 'onItemDelete not supported in attributeModifier scenario.');
  }
  onItemMove(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemMoveModifier.identity, ListOnItemMoveModifier, event);
    return this;
  }
  onItemDragStart(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragStartModifier.identity, ListOnItemDragStartModifier, event);
    return this;
  }
  onItemDragEnter(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragEnterModifier.identity, ListOnItemDragEnterModifier, event);
    return this;
  }
  onItemDragMove(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragMoveModifier.identity, ListOnItemDragMoveModifier, event);
    return this;
  }
  onItemDragLeave(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDragLeaveModifier.identity, ListOnItemDragLeaveModifier, event);
    return this;
  }
  onItemDrop(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnItemDropModifier.identity, ListOnItemDropModifier, event);
    return this;
  }
  onScrollFrameBegin(callback) {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollFrameBeginModifier.identity, ListOnScrollFrameBeginModifier, callback);
    return this;
  }
  onWillScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, ListOnWillScrollModifier.identity, ListOnWillScrollModifier, callback);
    return this;
  }
  onDidScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, ListOnDidScrollModifier.identity, ListOnDidScrollModifier, callback);
    return this;
  }
  onReachStart(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnReachStartModifier.identity, ListOnReachStartModifier, event);
    return this;
  }
  onReachEnd(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnReachEndModifier.identity, ListOnReachEndModifier, event);
    return this;
  }
  onScrollStart(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollStartModifier.identity, ListOnScrollStartModifier, event);
    return this;
  }
  onScrollStop(event) {
    modifierWithKey(this._modifiersWithKeys, ListOnScrollStopModifier.identity, ListOnScrollStopModifier, event);
    return this;
  }
  childrenMainSize(value) {
    modifierWithKey(this._modifiersWithKeys, ListChildrenMainSizeModifier.identity, ListChildrenMainSizeModifier, value);
    return this;
  }
  supportEmptyBranchInLazyLoading(value) {
    modifierWithKey(this._modifiersWithKeys, ListSupportEmptyBranchInLazyLoading.identity, ListSupportEmptyBranchInLazyLoading, value);
    return this;
  }
  backPressBehavior(value) {
    modifierWithKey(this._modifiersWithKeys, ListBackPressBehaviorModifier.identity,
      ListBackPressBehaviorModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.List !== undefined) {
  globalThis.List.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkListComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ListModifier(nativePtr, classType);
    });
  };
  globalThis.List.onWillStopDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStopDragging(nodePtr, value);
  };
  globalThis.List.onWillStartDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartDragging(nodePtr, value);
  };
  globalThis.List.onDidStopDragging = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopDragging(nodePtr, value);
  };
  globalThis.List.onWillStartFling = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartFling(nodePtr, value);
  };
  globalThis.List.onDidStopFling = function (value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopFling(nodePtr, value);
  };
}

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
class ListItemSwipeActionModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItem.resetSwipeAction(node);
    } else {
      getUINativeModule().listItem.setSwipeAction(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListItemSwipeActionModifier.identity = Symbol('listItemSwipeAction');
class ListItemOnSelectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItem.resetOnSelect(node);
    } else {
      getUINativeModule().listItem.setOnSelect(node, this.value);
    }
  }
}
ListItemOnSelectModifier.identity = Symbol('listItemOnSelect');
class ListFocusWrapModeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().list.resetFocusWrapMode(node);
    }
    else {
      getUINativeModule().list.setFocusWrapMode(node, this.value);
    }
  }
}
ListFocusWrapModeModifier.identity = Symbol('listFocusWrapMode');
class ListItemInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItem.resetListItemInitialize(node);
    } else {
      getUINativeModule().listItem.setListItemInitialize(node, this.value?.style);
    }
  }
}
ListItemInitializeModifier.identity = Symbol('listItemInitialize');
class ArkListItemComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ListItemInitializeModifier.identity,
        ListItemInitializeModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, ListItemInitializeModifier.identity,
        ListItemInitializeModifier, undefined);
    }
    return this;
  }
  sticky(value) {
    throw new BusinessError(100201, 'sticky not supported in attributeModifier scenario.');
  }
  editable(value) {
    throw new BusinessError(100201, 'editable not supported in attributeModifier scenario.');
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
    modifierWithKey(this._modifiersWithKeys, ListItemSwipeActionModifier.identity, ListItemSwipeActionModifier, value);
    return this;
  }
  onSelect(event) {
    modifierWithKey(this._modifiersWithKeys, ListItemOnSelectModifier.identity, ListItemOnSelectModifier, event);
    return this;
  }
}

class ListItemSwipeActionManager {
  static expand(node, direction) {
    getUINativeModule().listItemSwipeActionManager.expand(
      node === null || node === void 0 ? void 0 : node.nodePtr_, direction);
  }
  static collapse(node) {
    getUINativeModule().listItemSwipeActionManager.collapse(node === null || node === void 0 ? void 0 : node.nodePtr_);
  }
}

// @ts-ignore
if (globalThis.ListItem !== undefined) {
  globalThis.ListItem.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkListItemComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ListItemModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ListItemGroupInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItemGroup.resetListItemGroupInitialize(node);
    } else {
      getUINativeModule().listItemGroup.setListItemGroupInitialize(node, this.value?.space, this.value?.style,
        this.value?.headerComponent, this.value?.footerComponent, this.value?.headerStyle, this.value?.footerStyle,
        this.value?.spaceWidth);
    }
  }
}
ListItemGroupInitializeModifier.identity = Symbol('listItemGroupinitialize');
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
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.color) === ((_d = this.value) === null || _d === void 0 ? void 0 : _d.color) && !isResource(_c.color) && !isResource(_d.color) &&
      ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.startMargin) === ((_f = this.value) === null || _f === void 0 ? void 0 : _f.startMargin) &&
      ((_g = this.stageValue) === null || _g === void 0 ? void 0 : _g.endMargin) === ((_h = this.value) === null || _h === void 0 ? void 0 : _h.endMargin));
  }
}
ListItemGroupDividerModifier.identity = Symbol('listItemGroupDivider');
class ListItemGroupChildrenMainSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().listItemGroup.resetListItemGroupChildrenMainSize(node);
    }
    else {
      getUINativeModule().listItemGroup.setListItemGroupChildrenMainSize(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ListItemGroupChildrenMainSizeModifier.identity = Symbol('listItemGroupChildrenMainSize');
class ArkListItemGroupComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  divider(value) {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupDividerModifier.identity, ListItemGroupDividerModifier, value);
    return this;
  }
  childrenMainSize(value) {
    modifierWithKey(this._modifiersWithKeys, ListItemGroupChildrenMainSizeModifier.identity, ListItemGroupChildrenMainSizeModifier, value);
    return this;
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ListItemGroupInitializeModifier.identity,
        ListItemGroupInitializeModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, ListItemGroupInitializeModifier.identity,
        ListItemGroupInitializeModifier, undefined);
    }
    return this;
  }
  allowChildTypes() {
    return ["ListItem"];
  }
}
// @ts-ignore
if (globalThis.ListItemGroup !== undefined) {
  globalThis.ListItemGroup.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkListItemGroupComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ListItemGroupModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkUIExtensionComponentComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
if (globalThis.UIExtensionComponent !== undefined) {
  globalThis.UIExtensionComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkUIExtensionComponentComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkCanvasComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onReady(event) {
    modifierWithKey(this._modifiersWithKeys, CanvasOnReadyModifier.identity, CanvasOnReadyModifier, event);
    return this;
  }
  enableAnalyzer(value) {
    modifierWithKey(this._modifiersWithKeys, CanvasEnableAnalyzerModifier.identity, CanvasEnableAnalyzerModifier, value);
    return this;
  }
}

class CanvasOnReadyModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().canvas.resetCanvasOnReady(node);
    } else {
      getUINativeModule().canvas.setCanvasOnReady(node, this.value);
    }
  }
}
CanvasOnReadyModifier.identity = Symbol('canvasOnReady');

class CanvasEnableAnalyzerModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().canvas.resetCanvasEnableAnalyzer(node);
    }
    else {
      getUINativeModule().canvas.setCanvasEnableAnalyzer(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
CanvasEnableAnalyzerModifier.identity = Symbol('canvasEnableAnalyzer');

// @ts-ignore
if (globalThis.Canvas !== undefined) {
  globalThis.Canvas.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkCanvasComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkEffectComponentComponent extends ArkComponent {
}
// @ts-ignore
if (globalThis.EffectComponent !== undefined) {
  // @ts-ignore
  globalThis.EffectComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkEffectComponentComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkUnionEffectContainerComponent extends ArkComponent {
  pointLight(value) {
    modifierWithKey(this._modifiersWithKeys, CommonPointLightModifier.identity,
      CommonPointLightModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.UnionEffectContainer !== undefined) {
  // @ts-ignore
  globalThis.UnionEffectContainer.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkUnionEffectContainerComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.UnionEffectContainerModifier(nativePtr, classType);
    });
  };
}

/// <reference path='./import.ts' />
class ArkRemoteWindowComponent extends ArkComponent {
}
// @ts-ignore
if (globalThis.RemoteWindow !== undefined) {
  // @ts-ignore
  globalThis.RemoteWindow.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkRemoteWindowComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.CommonModifier(nativePtr, classType);
    });
  };
}

class ParticleDisturbanceFieldModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().particle.resetDisturbanceField(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let data = this.value[i];
        dataArray.push(parseWithDefaultNumber(data.strength, 0));
        dataArray.push(parseWithDefaultNumber(data.shape, 0));
        if (isObject(data.size)) {
          dataArray.push(parseWithDefaultNumber(data.size.width, 0));
          dataArray.push(parseWithDefaultNumber(data.size.height, 0));
        }
        else {
          dataArray.push(0);
          dataArray.push(0);
        }
        if (isObject(data.position)) {
          dataArray.push(parseWithDefaultNumber(data.position.x, 0));
          dataArray.push(parseWithDefaultNumber(data.position.y, 0));
        }
        else {
          dataArray.push(0);
          dataArray.push(0);
        }
        dataArray.push(parseWithDefaultNumber(data.feather, 0));
        dataArray.push(parseWithDefaultNumber(data.noiseScale, 1));
        dataArray.push(parseWithDefaultNumber(data.noiseFrequency, 1));
        dataArray.push(parseWithDefaultNumber(data.noiseAmplitude, 1));
      }
      getUINativeModule().particle.setDisturbanceField(node, dataArray);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

ParticleDisturbanceFieldModifier.identity = Symbol('disturbanceFields');

class ParticleEmitterModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().particle.resetEmitter(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkEmitterPropertyOptions = new ArkEmitterPropertyOptions();
        let data = this.value[i];
        arkEmitterPropertyOptions.index = 0;
        if (data.index > 0) {
          arkEmitterPropertyOptions.index = data.index;
        }

        if (isNumber(data.emitRate)) {
          arkEmitterPropertyOptions.isSetEmitRate = 1;
          if (data.emitRate >= 0) {
            arkEmitterPropertyOptions.emitRate = data.emitRate;
          } else {
            arkEmitterPropertyOptions.emitRate = 5;
          }
        }

        if (isObject(data.position)) {
          if (isNumber(data.position.x) && isNumber(data.position.y)) {
            arkEmitterPropertyOptions.isSetPosition = 1;
            arkEmitterPropertyOptions.positionX = data.position.x;
            arkEmitterPropertyOptions.positionY = data.position.y;
          }
        }

        if (isObject(data.size)) {
          if (data.size.width > 0 && data.size.height > 0) {
            arkEmitterPropertyOptions.isSetSize = 1;
            arkEmitterPropertyOptions.sizeWidth = data.size.width;
            arkEmitterPropertyOptions.sizeHeight = data.size.height;
          }
        }

        if (isObject(data.annulusRegion)) {
          arkEmitterPropertyOptions.isSetAnnulusRegion = 1;
          if (isObject(data.annulusRegion.center) &&
            isObject(data.annulusRegion.center.x) && isObject(data.annulusRegion.center.y)) {
            arkEmitterPropertyOptions.isSetCenter = 1;
            arkEmitterPropertyOptions.centerX = data.annulusRegion.center.x;
            arkEmitterPropertyOptions.centerY = data.annulusRegion.center.y;
          }
          if (isObject(data.annulusRegion.innerRadius)) {
            arkEmitterPropertyOptions.isSetInnerRadius = 1;
            arkEmitterPropertyOptions.innerRadius = data.annulusRegion.innerRadius;
          }
          if (isObject(data.annulusRegion.outerRadius)) {
            arkEmitterPropertyOptions.isSetOuterRadius = 1;
            arkEmitterPropertyOptions.outerRadius = data.annulusRegion.outerRadius;
          }
          if (isNumber(data.annulusRegion.startAngle)) {
            arkEmitterPropertyOptions.isSetStartAngle = 1;
            arkEmitterPropertyOptions.startAngle = data.annulusRegion.startAngle;
          }
          if (isNumber(data.annulusRegion.endAngle)) {
            arkEmitterPropertyOptions.isSetEndAngle = 1;
            arkEmitterPropertyOptions.endAngle = data.annulusRegion.endAngle;
          }
        }
        dataArray.push(arkEmitterPropertyOptions);
      }
      getUINativeModule().particle.setEmitter(node, dataArray);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

ParticleEmitterModifier.identity = Symbol('emitter');

class ParticleRippleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().particle.resetRippleField(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkRippleFieldOptions = new ArkRippleFieldOptions();
        let data = this.value[i];
        if (!data) {
          continue;
        }
        if (isNumber(data.amplitude)) {
          arkRippleFieldOptions.isSetAmplitude = 1;
          arkRippleFieldOptions.amplitude = data.amplitude;
        }
        if (isNumber(data.wavelength)) {
          arkRippleFieldOptions.isSetWaveLength = 1;
          arkRippleFieldOptions.wavelength = data.wavelength;
        }
        if (isNumber(data.waveSpeed)) {
          arkRippleFieldOptions.isSetWaveSpeed = 1;
          arkRippleFieldOptions.waveSpeed = data.waveSpeed;
        }
        if (isNumber(data.attenuation)) {
          arkRippleFieldOptions.isSetAttenuation = 1;
          arkRippleFieldOptions.attenuation = data.attenuation;
        }
        if (isObject(data.center)) {
          arkRippleFieldOptions.isSetCenter = 1;
          arkRippleFieldOptions.centerX = data.center.x;
          arkRippleFieldOptions.centerY = data.center.y;
        }
        if (isObject(data.region)) {
          arkRippleFieldOptions.isSetRegion = 1;
          if (isNumber(data.region.shape)) {
            arkRippleFieldOptions.isSetShape = 1;
            arkRippleFieldOptions.shape = data.region.shape;
          }

          if (isObject(data.region.position)) {
            arkRippleFieldOptions.isSetPosition = 1;
            arkRippleFieldOptions.positionX = data.region.position.x;
            arkRippleFieldOptions.positionY = data.region.position.y;
          }

          if (isObject(data.region.size)) {
            arkRippleFieldOptions.isSetSize = 1;
            arkRippleFieldOptions.sizeWidth = data.region.size.width;
            arkRippleFieldOptions.sizeHeight = data.region.size.height;
          }
        }
        dataArray.push(arkRippleFieldOptions);
      }
      getUINativeModule().particle.setRippleField(node, dataArray);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

ParticleRippleModifier.identity = Symbol('rippleFields');

class ParticleVelocityModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }

  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().particle.resetVelocityField(node);
    }
    else {
      let dataArray = [];
      if (!Array.isArray(this.value)) {
        return;
      }
      for (let i = 0; i < this.value.length; i++) {
        let arkVelocityFieldOptions = new ArkVelocityFieldOptions();
        let data = this.value[i];
        if (!data) {
          continue;
        }
        if (isObject(data.velocity)) {
          arkVelocityFieldOptions.isSetVelocity = 1;
          arkVelocityFieldOptions.velocityX = data.velocity.x;
          arkVelocityFieldOptions.velocityY = data.velocity.y;
        }
        if (isObject(data.region)) {
          arkVelocityFieldOptions.isSetRegion = 1;
          if (isNumber(data.region.shape)) {
            arkVelocityFieldOptions.isSetShape = 1;
            arkVelocityFieldOptions.shape = data.region.shape;
          }

          if (isObject(data.region.position)) {
            arkVelocityFieldOptions.isSetPosition = 1;
            arkVelocityFieldOptions.positionX = data.region.position.x;
            arkVelocityFieldOptions.positionY = data.region.position.y;
          }

          if (isObject(data.region.size)) {
            arkVelocityFieldOptions.isSetSize = 1;
            arkVelocityFieldOptions.sizeWidth = data.region.size.width;
            arkVelocityFieldOptions.sizeHeight = data.region.size.height;
          }
        }
      }
      dataArray.push(arkVelocityFieldOptions);
    }
    getUINativeModule().particle.setVelocityField(node, dataArray);
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

ParticleVelocityModifier.identity = Symbol('velocityFields');

/// <reference path='./import.ts' />
class ArkParticleComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  disturbanceFields(value) {
     modifierWithKey(this._modifiersWithKeys, ParticleDisturbanceFieldModifier.identity, ParticleDisturbanceFieldModifier, value);
    return this;
  }

  emitter(value) {
    modifierWithKey(this._modifiersWithKeys, ParticleEmitterModifier.identity, ParticleEmitterModifier, value);
    return this;
  }

  rippleFields(value) {
    modifierWithKey(this._modifiersWithKeys, ParticleRippleModifier.identity, ParticleRippleModifier, value);
    return this;
  }

  velocityFields(value) {
    modifierWithKey(this._modifiersWithKeys, ParticleVelocityModifier.identity, ParticleVelocityModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.Particle !== undefined) {

  // @ts-ignore
  globalThis.Particle.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkParticleComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ParticleModifier(nativePtr, classType);
    });
  };
}

let arkUINativeAdvancedModule = undefined;
function getUINativeAdvancedModule() {
  if (arkUINativeAdvancedModule) {
    return arkUINativeAdvancedModule;
  } else if (globalThis.getArkUIAdvancedModule !== undefined) {
    arkUINativeAdvancedModule = globalThis.getArkUIAdvancedModule();
  }
  return arkUINativeAdvancedModule;
}

class MediaCachedImageSrcModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (getUINativeAdvancedModule() === undefined) {
      return;
    }
    if (reset) {
      getUINativeAdvancedModule().mediaCachedImage.setMediaCachedImageSrc(node, '');
    } else {
      if (isResource(this.value) || isString(this.value)) {
        getUINativeAdvancedModule().mediaCachedImage.setMediaCachedImageSrc(node, 0, this.value);
      } else if (Array.isArray(this.value.sources)) {
        getUINativeAdvancedModule().mediaCachedImage.setMediaCachedImageSrc(
          node, 1, this.value.sources, this.value.sources.length, this.value.column);
      } else {
        getUINativeAdvancedModule().mediaCachedImage.setMediaCachedImageSrc(node, 0, this.value);
      }
    }
  }
}
MediaCachedImageSrcModifier.identity = Symbol('mediaCachedImageSrc');
class MediaCachedImageAltModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (getUINativeAdvancedModule() === undefined) {
      return;
    }
    if (reset) {
      getUINativeAdvancedModule().mediaCachedImage.resetAlt(node);
    } else {
      getUINativeAdvancedModule().mediaCachedImage.setAlt(node, this.value);
    }
  }
  checkObjectDiff() {
    return true;
  }
}
MediaCachedImageAltModifier.identity = Symbol('mediaCachedImageAlt');
class ArkMediaCachedImageComponent extends ArkImageComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, MediaCachedImageSrcModifier.identity, MediaCachedImageSrcModifier, value[0]);
    }
    return this;
  }
  alt(value) {
    modifierWithKey(this._modifiersWithKeys, MediaCachedImageAltModifier.identity, MediaCachedImageAltModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.MediaCachedImage !== undefined) {
  globalThis.MediaCachedImage.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkMediaCachedImageComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.MediaCachedImageModifier(nativePtr, classType);
    });
  };
}
class SystemBarEffectModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    getUINativeModule().common.setSystemBarEffect(node, true);
  }
}
SystemBarEffectModifier.identity = Symbol('systemBarEffect');
class ShaderInputBufferModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().component3D.resetShaderInputBuffer(node);
    } else {
      getUINativeModule().component3D.setShaderInputBuffer(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
ShaderInputBufferModifier.identity = Symbol('shaderInputBuffer');

/// <reference path='./import.ts' />
class ArkComponent3DComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  environment(uri) {
    throw new Error('Method not implemented.');
  };
  customRender(uri, selfRenderUpdate) {
    throw new Error('Method not implemented.');
  };
  shader(uri) {
    throw new Error('Method not implemented.');
  };
  shaderImageTexture(uri) {
    throw new Error('Method not implemented.');
  };
  shaderInputBuffer(buffer) {
    modifierWithKey(this._modifiersWithKeys, ShaderInputBufferModifier.identity, ShaderInputBufferModifier, buffer);
    return this;
  };
  renderWidth(value) {
    throw new Error('Method not implemented.');
  };
  renderHeight(value) {
    throw new Error('Method not implemented.');
  };
}
// @ts-ignore
if (globalThis.Component3D !== undefined) {
  globalThis.Component3D.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkComponent3DComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.Component3DModifier(nativePtr, classType);
    });
  };
}

class ContainerSpanTextBackgroundStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerSpan.resetTextBackgroundStyle(node);
    } else {
      let textBackgroundStyle = new ArkTextBackGroundStyle();
      if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value)) {
        getUINativeModule().containerSpan.resetTextBackgroundStyle(node);
      } else {
        getUINativeModule().containerSpan.setTextBackgroundStyle(node,textBackgroundStyle.color,
          textBackgroundStyle.radius.topLeft,
          textBackgroundStyle.radius.topRight,
          textBackgroundStyle.radius.bottomLeft,
          textBackgroundStyle.radius.bottomRight);
      }
    }
  }
  checkObjectDiff() {
    let textBackgroundStyle = new ArkTextBackGroundStyle();
    let stageTextBackGroundStyle = new ArkTextBackGroundStyle();
    if (!textBackgroundStyle.convertTextBackGroundStyleOptions(this.value) || !stageTextBackGroundStyle.convertTextBackGroundStyleOptions(this.stageValue)) {
      return false;
    } else {
      return textBackgroundStyle.checkObjectDiff(stageTextBackGroundStyle);
    }
  }
}
ContainerSpanTextBackgroundStyleModifier.identity = Symbol('containerSpanTextBackgroundStyle');
/// <reference path='./import.ts' />
class ArkContainerSpanComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  textBackgroundStyle(value) {
    modifierWithKey(this._modifiersWithKeys, ContainerSpanTextBackgroundStyleModifier.identity, ContainerSpanTextBackgroundStyleModifier, value);
    return this;
  }
}
// @ts-ignore
if (globalThis.ContainerSpan !== undefined) {
  globalThis.ContainerSpan.attributeModifier = function (modifier) {
    attributeModifierFuncWithoutStateStyles.call(this, modifier, (nativePtr) => {
      return new ArkContainerSpanComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ContainerSpanModifier(nativePtr, classType);
    });
  };
}

class ArkLazyColumnLayoutComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  space(value) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutSpaceModifier.identity, LazyColumnLayoutSpaceModifier, value);
    return this;
  }
  alignItems(value) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutAlignItemsModifier.identity, LazyColumnLayoutAlignItemsModifier, value);
    return this;
  }
  onVisibleIndexesChange(callback) {
    modifierWithKey(this._modifiersWithKeys, LazyColumnLayoutOnVisibleIndexesChangeModifier.identity, LazyColumnLayoutOnVisibleIndexesChangeModifier, callback);
    return this;
  }
}
class LazyColumnLayoutSpaceModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyColumnLayout.resetSpace(node);
    }
    else {
      getUINativeModule().lazyColumnLayout.setSpace(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LazyColumnLayoutSpaceModifier.identity = Symbol('lazyColumnLayoutSpace');
class LazyColumnLayoutAlignItemsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isNumber(this.value)) {
      getUINativeModule().lazyColumnLayout.resetAlignItems(node);
    }
    else {
      getUINativeModule().lazyColumnLayout.setAlignItems(node, this.value);
    }
  }
}
LazyColumnLayoutAlignItemsModifier.identity = Symbol('lazyColumnLayoutAlignItems');
class LazyColumnLayoutOnVisibleIndexesChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isFunction(this.value)) {
      getUINativeModule().lazyColumnLayout.resetOnVisibleIndexesChange(node);
    }
    else {
      getUINativeModule().lazyColumnLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}
LazyColumnLayoutOnVisibleIndexesChangeModifier.identity = Symbol('lazyColumnLayoutOnVisibleIndexesChange');
// @ts-ignore
if (globalThis.LazyColumnLayout !== undefined) {
globalThis.LazyColumnLayout.attributeModifier = function (modifier) {
  attributeModifierFunc.call(this, modifier, (nativePtr) => {
    return new ArkLazyColumnLayoutComponent(nativePtr);
  }, (nativePtr, classType, modifierJS) => {
    return new modifierJS.LazyColumnLayoutModifier(nativePtr, classType);
  });
};
}

class ArkLazyVWaterFlowLayoutComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  columnsGap(value) {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowColumnsGapModifier.identity, LazyWaterFlowColumnsGapModifier, value);
    return this;
  }
  rowsGap(value) {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowRowsGapModifier.identity, LazyWaterFlowRowsGapModifier, value);
    return this;
  }
  columnsTemplate(value) {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowColumnsTemplateModifier.identity, LazyWaterFlowColumnsTemplateModifier, value);
    return this;
  }
  onVisibleIndexesChange(callback) {
    modifierWithKey(this._modifiersWithKeys, LazyWaterFlowOnVisibleIndexesChangeModifier.identity, LazyWaterFlowOnVisibleIndexesChangeModifier, callback);
    return this;
  }
}
class LazyWaterFlowColumnsTemplateModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    }
    else if (isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.setItemFillPolicy(node, this.value);
    }
    else if (isString(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsTemplate(node, this.value);
    }
    else {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsTemplate(node);
    }
  }
}
LazyWaterFlowColumnsTemplateModifier.identity = Symbol('lazyVWaterFlowColumnsTemplate');
class LazyWaterFlowColumnsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetColumnsGap(node);
    }
    else {
      getUINativeModule().lazyVWaterFlowLayout.setColumnsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LazyWaterFlowColumnsGapModifier.identity = Symbol('lazyVWaterFlowColumnsGap');
class LazyWaterFlowRowsGapModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isObject(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetRowsGap(node);
    }
    else {
      getUINativeModule().lazyVWaterFlowLayout.setRowsGap(node, this.value);
    }
  }
  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
LazyWaterFlowRowsGapModifier.identity = Symbol('lazyVWaterFlowRowsGap');
class LazyWaterFlowOnVisibleIndexesChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset || !isFunction(this.value)) {
      getUINativeModule().lazyVWaterFlowLayout.resetOnVisibleIndexesChange(node);
    }
    else {
      getUINativeModule().lazyVWaterFlowLayout.setOnVisibleIndexesChange(node, this.value);
    }
  }
}
LazyWaterFlowOnVisibleIndexesChangeModifier.identity = Symbol('lazyVWaterFlowOnVisibleIndexesChange');
// @ts-ignore
if (globalThis.LazyVWaterFlowLayout !== undefined) {
globalThis.LazyVWaterFlowLayout.attributeModifier = function (modifier) {
  attributeModifierFunc.call(this, modifier, (nativePtr) => {
    return new ArkLazyVWaterFlowLayoutComponent(nativePtr);
  }, (nativePtr, classType, modifierJS) => {
    return new modifierJS.LazyVWaterFlowLayoutModifier(nativePtr, classType);
  });
};
}

class ArkContainerPickerComponent extends ArkComponent {
    constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerOnChangeModifier.identity, ContainerPickerOnChangeModifier, callback);
    return this;
  }
  onScrollStop(callback){
    modifierWithKey(
      this._modifiersWithKeys, ContainerPickerOnScrollStopModifier.identity, ContainerPickerOnScrollStopModifier, callback);
    return this;
  }
  canLoop(isLoop) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerCanLoopModifier.identity, ContainerPickerCanLoopModifier, isLoop);
    return this;
  }
  enableHapticFeedback(enable) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerEnableHapticFeedbackModifier.identity, ContainerPickerEnableHapticFeedbackModifier, enable);
    return this;
  }
  selectionIndicator(style) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerSelectionIndicatorModifier.identity, ContainerPickerSelectionIndicatorModifier, style);
    return this;
  }
  displayedItemCount(count) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerDisplayedItemCountModifier.identity, ContainerPickerDisplayedItemCountModifier, count);
    return this;
  }
  itemHeight(height) {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerItemHeightModifier.identity, ContainerPickerItemHeightModifier, height);
    return this;
  }

}

class ContainerPickerOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerOnChange(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerOnChange(node, this.value);
    }
  }
}
ContainerPickerOnChangeModifier.identity = Symbol('containerPickerOnChange');

class ContainerPickerOnScrollStopModifier extends ModifierWithKey{
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerOnScrollStop(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerOnScrollStop(node, this.value);
    }
  }
}
ContainerPickerOnScrollStopModifier.identity = Symbol('containerPickerOnScrollStop');

class ContainerPickerCanLoopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerCanLoop(node);
    }
    else {
      getUINativeModule().containerPicker.setContainerPickerCanLoop(node, this.value);
    }
  }
}
ContainerPickerCanLoopModifier.identity = Symbol('containerPickerCanLoop');

class ContainerPickerEnableHapticFeedbackModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerEnableHapticFeedback(node);
    }
    else {
      getUINativeModule().containerPicker.setContainerPickerEnableHapticFeedback(node, this.value);
    }
  }
}
ContainerPickerEnableHapticFeedbackModifier.identity = Symbol('containerPickerEnableHapticFeedback');

class ContainerPickerSelectionIndicatorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerSelectionIndicator(node);
    } else if (this.value == null) {
      getUINativeModule().containerPicker.setContainerPickerSelectionIndicator(node, undefined, undefined, undefined,
        undefined, undefined, undefined, undefined, undefined, undefined, undefined);
    } else {
      const { type, strokeWidth, dividerColor, startMargin, endMargin, backgroundColor, borderRadius } = this.value;
      if (borderRadius != null) {
        const borderRadiusKeys = Object.keys(borderRadius);
        let topLeft;
        let topRight;
        let bottomLeft;
        let bottomRight;
        if (borderRadiusKeys.indexOf('value') >= 0) {
          topLeft = topRight = bottomLeft = bottomRight = borderRadius;
        } else if (borderRadiusKeys.indexOf('topLeft') >= 0) {
          topLeft = borderRadius.topLeft;
          topRight = borderRadius.topRight;
          bottomLeft = borderRadius.bottomLeft;
          bottomRight = borderRadius.bottomRight;
        } else if (borderRadiusKeys.indexOf('topStart') >= 0) {
          topLeft = borderRadius.topStart;
          topRight = borderRadius.topEnd;
          bottomLeft = borderRadius.bottomStart;
          bottomRight = borderRadius.bottomEnd;
        }
        getUINativeModule().containerPicker.setContainerPickerSelectionIndicator(node, type, strokeWidth, dividerColor, startMargin, endMargin, backgroundColor, topLeft, topRight, bottomLeft,
          bottomRight);
      } else {
        getUINativeModule().containerPicker.setContainerPickerSelectionIndicator(node, type, strokeWidth, dividerColor, startMargin, endMargin, backgroundColor, undefined, undefined,
          undefined, undefined);
      }
    }
  }
  checkObjectDiff() {
    return true;
  }
}
ContainerPickerSelectionIndicatorModifier.identity = Symbol('containerPickerSelectionIndicator');

class ContainerPickerDisplayedItemCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerDisplayedItemCount(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerDisplayedItemCount(node, this.value);
    }
  }
}
ContainerPickerDisplayedItemCountModifier.identity = Symbol('containerPickerDisplayedItemCount');

class ContainerPickerItemHeightModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerItemHeight(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerItemHeight(node, this.value);
    }
  }
}
ContainerPickerItemHeightModifier.identity = Symbol('containerPickerItemHeight');
// @ts-ignore
if (globalThis.UIPickerComponent !== undefined) {
  globalThis.UIPickerComponent.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkContainerPickerComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.ContainerPickerModifier(nativePtr, classType);
    });
  };
}

function getArkUINodeFromNapi() {
  if(globalThis.__XNode__ === undefined) {
      globalThis.__XNode__ = globalThis.requireNapi('arkui.node');
  }
  return globalThis.__XNode__;
}

globalThis.__getArkUINode__ = getArkUINodeFromNapi;

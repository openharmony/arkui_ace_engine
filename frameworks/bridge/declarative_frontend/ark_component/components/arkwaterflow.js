/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

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
class WaterFlowClipModifier extends ModifierWithKey {
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
WaterFlowClipModifier.identity = Symbol('waterFlowclip');
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

class WaterFlowScrollBarWidthModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBarWidth(node);
    }
    else {
      getUINativeModule().waterFlow.setScrollBarWidth(node, this.value);
    }
  }
}
WaterFlowScrollBarWidthModifier.identity = Symbol('waterFlowScrollBarWidth');
class WaterFlowScrollBarModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBar(node);
    }
    else {
      getUINativeModule().waterFlow.setScrollBar(node, this.value);
    }
  }
}
WaterFlowScrollBarModifier.identity = Symbol('waterFlowScrollBar');
class WaterFlowScrollBarColorModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetScrollBarColor(node);
    }
    else {
      getUINativeModule().waterFlow.setScrollBarColor(node, this.value);
    }
  }
}
WaterFlowScrollBarColorModifier.identity = Symbol('waterFlowScrollBarColor');

class WaterFlowCachedCountModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetCachedCount(node);
    }
    else {
      getUINativeModule().waterFlow.setCachedCount(node, this.value.count, this.value.show);
    }
  }
}
WaterFlowCachedCountModifier.identity = Symbol('waterFlowCachedCount');

class WaterFlowSyncLoadModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetSyncLoad(node);
    }
    else {
      getUINativeModule().waterFlow.setSyncLoad(node, this.value);
    }
  }
}
WaterFlowSyncLoadModifier.identity = Symbol('waterFlowSyncLoad');

class WaterFlowOnScrollFrameBeginModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnScrollFrameBegin(node);
    } else {
      getUINativeModule().scrollable.setOnScrollFrameBegin(node, this.value);
    }
  }
}
WaterFlowOnScrollFrameBeginModifier.identity = Symbol('waterFlowOnScrollFrameBegin');

class WaterFlowOnWillScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnWillScroll(node);
    } else {
      getUINativeModule().scrollable.setOnWillScroll(node, this.value);
    }
  }
}
WaterFlowOnWillScrollModifier.identity = Symbol('waterFlowOnWillScroll');

class WaterFlowOnDidScrollModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnDidScroll(node);
    } else {
      getUINativeModule().scrollable.setOnDidScroll(node, this.value);
    }
  }
}
WaterFlowOnDidScrollModifier.identity = Symbol('waterFlowOnDidScroll');

class WaterFlowOnReachStartModifier extends ModifierWithKey {
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
WaterFlowOnReachStartModifier.identity = Symbol('waterFlowOnReachStart');

class WaterFlowOnReachEndModifier extends ModifierWithKey {
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
WaterFlowOnReachEndModifier.identity = Symbol('waterFlowOnReachEnd');

class WaterFlowOnScrollStartModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnScrollStart(node);
    } else {
      getUINativeModule().scrollable.setOnScrollStart(node, this.value);
    }
  }
}
WaterFlowOnScrollStartModifier.identity = Symbol('waterFlowOnScrollStart');

class WaterFlowOnScrollStopModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().scrollable.resetOnScrollStop(node);
    } else {
      getUINativeModule().scrollable.setOnScrollStop(node, this.value);
    }
  }
}
WaterFlowOnScrollStopModifier.identity = Symbol('waterFlowOnScrollStop');

class WaterFlowOnScrollIndexModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetOnScrollIndex(node);
    } else {
      getUINativeModule().waterFlow.setOnScrollIndex(node, this.value);
    }
  }
}
WaterFlowOnScrollIndexModifier.identity = Symbol('waterFlowOnScrollIndex');

class WaterFlowInitializeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().waterFlow.resetWaterFlowInitialize(node);
    } else {
      getUINativeModule().waterFlow.setWaterFlowInitialize(node,
        this.value?.scroller, this.value?.sections, this.value?.layoutMode, this.value?.footerContent, this.value?.footer);
    }
  }
}
WaterFlowInitializeModifier.identity = Symbol('waterFlowInitialize');

class ArkWaterFlowComponent extends ArkScrollable {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
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
  cachedCount(count, show) {
    let opt = new ArkScrollableCacheOptions(count, show ? show : false);
    modifierWithKey(this._modifiersWithKeys, WaterFlowCachedCountModifier.identity, WaterFlowCachedCountModifier, opt);
    return this;
  }
  syncLoad(value) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowSyncLoadModifier.identity, WaterFlowSyncLoadModifier, value);
    return this;
  }
  onReachStart(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnReachStartModifier.identity, WaterFlowOnReachStartModifier, event);
    return this;
  }
  onReachEnd(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnReachEndModifier.identity, WaterFlowOnReachEndModifier, event);
    return this;
  }
  onScrollFrameBegin(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnScrollFrameBeginModifier.identity, WaterFlowOnScrollFrameBeginModifier, event);
    return this;
  }
  clip(value) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowClipModifier.identity, WaterFlowClipModifier, value);
    return this;
  }
  scrollBarWidth(value) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarWidthModifier.identity, WaterFlowScrollBarWidthModifier, value);
    return this;
  }
  scrollBarColor(value) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarColorModifier.identity, WaterFlowScrollBarColorModifier, value);
    return this;
  }
  scrollBar(value) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowScrollBarModifier.identity, WaterFlowScrollBarModifier, value);
    return this;
  }
  onWillScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnWillScrollModifier.identity, WaterFlowOnWillScrollModifier, callback);
    return this;
  }
  onDidScroll(callback) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnDidScrollModifier.identity, WaterFlowOnDidScrollModifier, callback);
    return this;
  }
  onScrollStart(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnScrollStartModifier.identity, WaterFlowOnScrollStartModifier, event);
    return this;
  }
  onScrollStop(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnScrollStopModifier.identity, WaterFlowOnScrollStopModifier, event);
    return this;
  }
  onScrollIndex(event) {
    modifierWithKey(this._modifiersWithKeys, WaterFlowOnScrollIndexModifier.identity, WaterFlowOnScrollIndexModifier, event);
    return this;
  }
  initialize(value) {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, WaterFlowInitializeModifier.identity,
        WaterFlowInitializeModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, WaterFlowInitializeModifier.identity,
        WaterFlowInitializeModifier, undefined);
    }
    return this;
  }
  allowChildTypes() {
    return ['FlowItem'];
  }
}


class JSWaterFlow extends JSContainerBase {
  static create(params) {
    getUINativeModule().waterFlow.create();
    getUINativeModule().waterFlow.setWaterFlowInitialize(true,
      params === null || params === void 0 ? void 0 : params.scroller,
      params === null || params === void 0 ? void 0 : params.sections,
      params === null || params === void 0 ? void 0 : params.layoutMode,
      params === null || params === void 0 ? void 0 : params.footerContent,
      params === null || params === void 0 ? void 0 : params.footer,
      'footerContent' in params);
  }
  static columnsGap(value) {
    getUINativeModule().waterFlow.setJSColumnsGap(true, value);
  }
  static rowsGap(value) {
    getUINativeModule().waterFlow.setJSRowsGap(true, value);
  }
  static layoutDirection(value) {
    getUINativeModule().waterFlow.setLayoutDirection(true, value);
  }
  static columnsTemplate(value) {
    getUINativeModule().waterFlow.setJSColumnsTemplate(true, value);
  }
  static itemConstraintSize(value) {
    getUINativeModule().waterFlow.setJSItemConstraintSize(true, value);
  }
  static rowsTemplate(value) {
    getUINativeModule().waterFlow.setRowsTemplate(true, value);
  }
  static nestedScroll(value) {
    getUINativeModule().waterFlow.setNestedScroll(true, value);
    return this;
  }
  static enableScrollInteraction(value) {
    getUINativeModule().waterFlow.setEnableScrollInteraction(true, value);
  }
  static friction(value) {
    getUINativeModule().waterFlow.setFriction(true, value);
  }
  static clip(value) {
    getUINativeModule().common.setClipWithEdge(true, value);
  }
  static cachedCount(count, show) {
    getUINativeModule().waterFlow.setCachedCount(true, count, show ? show : false);
  }
  static edgeEffect(edgeEffect, options) {
    getUINativeModule().scrollable.setEdgeEffect(true, edgeEffect,
      options === null || options === void 0 ? void 0 : options.alwaysEnabled,
      options === null || options === void 0 ? void 0 : options.effectEdge);
  }
  static syncLoad(value) {
    getUINativeModule().waterFlow.setSyncLoad(true, value);
  }
  static scrollBar(value) {
    getUINativeModule().waterFlow.setJSScrollBar(true, value);
  }
  static scrollBarWidth(value) {
    getUINativeModule().waterFlow.setJSScrollBarWidth(true, value);
  }
  static scrollBarColor(value) {
    getUINativeModule().waterFlow.setJSScrollBarColor(true, value);
  }

  static onScroll(value) {
    getUINativeModule().waterFlow.setOnScroll(true, value);
    return this;
  }
  static onScrollStart(value) {
    getUINativeModule().waterFlow.setOnScrollStart(true, value);
    return this;
  }
  static onScrollStop(value) {
    getUINativeModule().waterFlow.setOnScrollStop(true, value);
    return this;
  }
  static onScrollIndex(value) {
    getUINativeModule().waterFlow.setJSOnScrollIndex(true, value);
    return this;
  }
  static onReachStart(value) {
    getUINativeModule().waterFlow.setOnReachStart(true, value);
    return this;
  }
  static onReachEnd(value) {
    getUINativeModule().waterFlow.setOnReachEnd(true, value);
    return this;
  }
  static onScrollFrameBegin(value) {
    getUINativeModule().waterFlow.setOnScrollFrameBegin(true, value);
  }
  static remoteMessage(value) {
    __Common__.remoteMessage(value);
  }
  static onClick(value) {
    __Common__.onClick(value);
  }
  static onTouch(value) {
    __Common__.onTouch(value);
  }
  static onHover(value) {
    __Common__.onHover(value);
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
    __Common__.onDetach(value);
  }
  static onDisAppear(value) {
    __Common__.onDisAppear(value);
  }

  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkWaterFlowComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.WaterFlowModifier(nativePtr, classType);
    });
  };
  static onWillStopDragging(value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStopDragging(nodePtr, value);
  };
  static onWillStartDragging(value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartDragging(nodePtr, value);
  };
  static onDidStopDragging(value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopDragging(nodePtr, value);
  };
  static onWillStartFling(value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnWillStartFling(nodePtr, value);
  };
  static onDidStopFling(value) {
    let nodePtr = getUINativeModule().frameNode.getStackTopNode();
    getUINativeModule().scrollable.setOnDidStopFling(nodePtr, value);
  };
}

function createComponent(nativePtr, classType) {
  return new ArkWaterFlowComponent(nativePtr, classType);
}

function exportComponent() {
  globalThis.ArkWaterFlowComponent = ArkWaterFlowComponent;
}

function exportView() {
  globalThis.WaterFlow = JSWaterFlow;
}

export default { ArkWaterFlowComponent, createComponent, exportComponent, exportView };
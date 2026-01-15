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
class SideBarContainerOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().sideBarContainer.resetSideBarOnChange(node);
    } else {
      getUINativeModule().sideBarContainer.setSideBarOnChange(node, this.value);
    }
  }
}
SideBarContainerOnChangeModifier.identity = Symbol('sideBarContainerOnChange');
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
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, SideBarContainerOnChangeModifier.identity,
      SideBarContainerOnChangeModifier, callback);
    return this;
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

class JSSideBarContainer extends JSViewAbstract {
    static create(params) {
        console.log('JSsideBarContainer create nativeModule');
        if (params !== undefined) {
            getUINativeModule().sideBarContainer.create(params);
        } else {
            getUINativeModule().sideBarContainer.create(undefined);
        }
    }
    static onChange(value) {
        getUINativeModule().sideBarContainer.setSideBarOnChange(true, value);
        return this;
    }
    static showSideBar(value, fuc) {
        getUINativeModule().sideBarContainer.setShowSideBar(true, value, fuc);
    }
    static autoHide(value) {
        getUINativeModule().sideBarContainer.setAutoHide(true, value);
    }
    static maxSideBarWidth(value) {
        getUINativeModule().sideBarContainer.setMaxSideBarWidth(true, value);
    }
    static minSideBarWidth(value) {
        getUINativeModule().sideBarContainer.setMinSideBarWidth(true, value);
    }
    static minContentWidth(value) {
        getUINativeModule().sideBarContainer.setMinContentWidth(true, value);
    }
    static controlButton(value) {
        getUINativeModule().sideBarContainer.setControlButton(true, value);
    }
    static divider(value) {
        getUINativeModule().sideBarContainer.setDivider(true, value);
    }
    static sideBarPosition(value) {
        getUINativeModule().sideBarContainer.setSideBarPosition(true, value);
    }
    static sideBarWidth(value) {
        getUINativeModule().sideBarContainer.setSideBarWidth(true, value);
    }
    static showControlButton(value) {
        getUINativeModule().sideBarContainer.setShowControlButton(true, value);
    }
    static sideBarPosition(value) {
        getUINativeModule().sideBarContainer.setSideBarPosition(true, value);
    }
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkSideBarContainerComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.SideBarContainerModifier(nativePtr, classType);
        });
    }

    static onClick(value) {
        __Common__.onClick(value);
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
}

function createComponent(nativePtr, classType) {
    return new ArkSideBarContainerComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkSideBarContainerComponent = ArkSideBarContainerComponent;
}

function exportView() {
    globalThis.SideBarContainer = JSSideBarContainer;
}

export default { ArkSideBarContainerComponent, createComponent, exportComponent, exportView };

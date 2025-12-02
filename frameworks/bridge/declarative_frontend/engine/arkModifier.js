/*
 * Copyright (c) 2024-2026 Huawei Device Co., Ltd.
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

const overrideMap = new Map();
overrideMap.set(
  'ArkCheckboxComponent',
  new Map([
    ['Symbol(width)', (()=>{
      let module = globalThis.requireNapi('arkui.components.arkcheckbox');
      return module.CheckboxWidthModifier;
    })()],
    ['Symbol(height)', (()=>{
      let module = globalThis.requireNapi('arkui.components.arkcheckbox');
      return module.CheckboxHeightModifier;
    })()],
  ])
);
overrideMap.set(
  'ArkTextComponent',
  new Map([
    ['Symbol(foregroundColor)', TextForegroundColorModifier]
  ])
);
function applyAndMergeModifier(instance, modifier) {
  let myMap = modifier._modifiersWithKeys;
  myMap.setOnChange((key, value) => {
    modifier._changed = !modifier._changed;
  });
  let component = instance;
  mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
}
function copyModifierWithKey(obj) {
  let newObj = { ...obj };
  newObj.applyStage = obj === null || obj === void 0 ? void 0 : obj.applyStage;
  newObj.applyPeer = obj === null || obj === void 0 ? void 0 : obj.applyPeer;
  newObj.checkObjectDiff = obj === null || obj === void 0 ? void 0 : obj.checkObjectDiff;
  return newObj;
}
function mergeMaps(stageMap, newMap) {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyModifierWithKey(value));
  });
  return stageMap;
}
class ModifierUtils {
  static copyModifierWithKey(obj) {
    let newObj = { ...obj };
    newObj.applyStage = obj === null || obj === void 0 ? void 0 : obj.applyStage;
    newObj.applyPeer = obj === null || obj === void 0 ? void 0 : obj.applyPeer;
    newObj.checkObjectDiff = obj === null || obj === void 0 ? void 0 : obj.checkObjectDiff;
    return newObj;
  }
  static mergeMaps(stageMap, newMap) {
    newMap.forEach((value, key) => {
      stageMap.set(key, this.copyModifierWithKey(value));
    });
  }
  static mergeMapsEmplace(stageMap, newMap, componentOverrideMap) {
    newMap.forEach((value, key) => {
      if (!key) {
        ArkLogConsole.debug('key of modifier map is undefined, ModifierWithKey is ' +
          (value ? value.constructor.name.toString() : 'undefined'));
      } else {
        if (componentOverrideMap.has(key.toString())) {
          const newValue = new (componentOverrideMap.get(key.toString()))(value.stageValue);
          stageMap.set(key, newValue);
        } else {
          stageMap.set(key, this.copyModifierWithKey(value));
        }
      }
    });
  }
  static applyAndMergeModifier(instance, modifier) {
    let component = instance;
    if (component.constructor.name && overrideMap.has(component.constructor.name)) {
      const componentOverrideMap = overrideMap.get(component.constructor.name);
      this.mergeMapsEmplace(component._modifiersWithKeys, modifier._modifiersWithKeys,
        componentOverrideMap);
    } else {
      this.mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
    }
  }
  static applySetOnChange(modifier) {
    // It is to make the stateMgmt can addRef of _changed,
    // so that the modifier change can be observed by makeObserved when modifier._changed changed.
    modifier._changed;
    let myMap = modifier._modifiersWithKeys;
    if (modifier._classType === ModifierType.STATE) {
      const nativePtrValid = !modifier._weakPtr.invalid();
      const hostInstanceId = nativePtrValid ? getUINativeModule().frameNode.getNodeInstanceId(modifier.nativePtr) : -1;
      myMap.setOnChange((key, value) => {
        this.putDirtyModifier(modifier, value, hostInstanceId);
      });
    } else {
      myMap.setOnChange((key, value) => {
        modifier._changed = !modifier._changed;
      });
    }
  }
  static putDirtyModifier(arkModifier, attributeModifierWithKey, hostInstanceId) {
    attributeModifierWithKey.value = attributeModifierWithKey.stageValue;
    if (!arkModifier._weakPtr.invalid()) {
      attributeModifierWithKey.applyPeer(arkModifier.nativePtr,
        (attributeModifierWithKey.value === undefined ||
          attributeModifierWithKey.value === null)
      );
    } else {
      ArkLogConsole.debug('pointer is invalid when putDirtyModifier in ' + (arkModifier ?
        arkModifier.constructor.name.toString() : 'undefined') + ' of ' + (attributeModifierWithKey ?
        attributeModifierWithKey.constructor.name.toString() : 'undefined'));
    }
    this.dirtyComponentSet.add(arkModifier);
    if (!this.dirtyFlag) {
      this.dirtyFlag = true;
      this.requestFrame(hostInstanceId);
    }
  }
  static requestFrame(hostInstanceId) {
    const frameCallback = () => {
      if (this.timeoutId !== -1) {
        clearTimeout(this.timeoutId);
      }
      this.dirtyComponentSet.forEach((item) => {
        const nativePtrValid = !item._weakPtr.invalid();
        if (item._nativePtrChanged && nativePtrValid) {
          item._modifiersWithKeys.forEach((value, key) => {
            value.applyPeer(item.nativePtr,
              (value.value === undefined || value.value === null));
          });
          item._nativePtrChanged = false;
        }
        if (nativePtrValid) {
          getUINativeModule().frameNode.markDirty(item.nativePtr, 0b100);
        }
      });
      this.dirtyComponentSet.clear();
      this.dirtyFlag = false;
      this.timeoutId = -1;
    };
    if (this.timeoutId !== -1) {
      clearTimeout(this.timeoutId);
    }
    this.timeoutId = setTimeout(frameCallback, 100);
    if (hostInstanceId > -1) {
        __JSScopeUtil__.syncInstanceId(hostInstanceId);
        getUINativeModule().frameNode.registerFrameCallback(frameCallback);
        __JSScopeUtil__.restoreInstanceId();
        return;
    }
    getUINativeModule().frameNode.registerFrameCallback(frameCallback);
  }
}
ModifierUtils.dirtyComponentSet = new Set();
ModifierUtils.dirtyFlag = false;
ModifierUtils.timeoutId = -1;
class ModifierMap {
  constructor() {
    this.map_ = new Map();
  }
  clear() {
    this.map_.clear();
  }
  delete(key) {
    return this.map_.delete(key);
  }
  forEach(callbackfn, thisArg) {
    this.map_.forEach(callbackfn, thisArg);
  }
  get(key) {
    return this.map_.get(key);
  }
  has(key) {
    return this.map_.has(key);
  }
  set(key, value) {
    const _a = this.changeCallback;
    this.map_.set(key, value);
    _a === null || _a === void 0 ? void 0 : _a(key, value);
    return this;
  }
  get size() {
    return this.map_.size;
  }
  entries() {
    return this.map_.entries();
  }
  keys() {
    return this.map_.keys();
  }
  values() {
    return this.map_.values();
  }
  [Symbol.iterator]() {
    return this.map_.entries();
  }
  get [Symbol.toStringTag]() {
    return 'ModifierMapTag';
  }
  setOnChange(callback) {
    this.changeCallback = callback;
  }
}
class AttributeUpdater {
  constructor() {
    this._state = AttributeUpdater.StateEnum.INIT;
    this._attribute = null;
    this._isAttributeUpdater = true;
  }
  get isAttributeUpdater() {
    return this._isAttributeUpdater;
  }
  get attribute() {
    return this._attribute;
  }
  set attribute(value) {
    if (!this._attribute && value) {
      this._attribute = value;
    }
  }
  get modifierState() {
    return this._state;
  }
  set modifierState(value) {
    this._state = value;
  }
  initializeModifier(instance) {}
  onComponentChanged(instance) {}
  updateConstructorParams(...args) {
    if (!this.attribute) {
      ArkLogConsole.debug('AttributeUpdater has not been initialized before updateConstructorParams.');
      return;
    }
    this.attribute.initialize(args);
  }
}
AttributeUpdater.StateEnum = {
  INIT: 0,
  UPDATE: 1,
};
class CommonModifier extends ArkComponent {
  constructor(nativePtr, classType) {
    if (!classType) {
      classType = ModifierType.EXPOSE_MODIFIER;
    }
    super(nativePtr, classType);
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyAlphabetIndexerComponent extends ArkComponent {
   static module = undefined;
   constructor(nativePtr, classType) {
     super(nativePtr, classType);
     if (LazyAlphabetIndexerComponent.module === undefined) {
       LazyAlphabetIndexerComponent.module = globalThis.requireNapi('arkui.components.arkalphabetindexer');
     }
     this.lazyComponent = LazyAlphabetIndexerComponent.module.createComponent(nativePtr, classType);
   }
   setMap() {
     this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
   }
   onSelected(value) {
     this.lazyComponent.onSelected(value);
     return this;
   }
   color(value) {
     this.lazyComponent.color(value);
     return this;
   }
   selectedColor(value) {
     this.lazyComponent.selectedColor(value);
     return this;
   }
   popupColor(value) {
     this.lazyComponent.popupColor(value);
     return this;
   }
   selectedBackgroundColor(value) {
     this.lazyComponent.selectedBackgroundColor(value);
     return this;
   }
   popupBackground(value) {
     this.lazyComponent.popupBackground(value);
     return this;
   }
   popupSelectedColor(value) {
     this.lazyComponent.popupSelectedColor(value);
     return this;
   }
   popupUnselectedColor(value) {
     this.lazyComponent.popupUnselectedColor(value);
     return this;
   }
   popupItemBackgroundColor(value) {
     this.lazyComponent.popupItemBackgroundColor(value);
     return this;
   }
   usingPopup(value) {
     this.lazyComponent.usingPopup(value);
     return this;
   }
   selectedFont(value) {
     this.lazyComponent.selectedFont(value);
     return this;
   }
   popupFont(value) {
     this.lazyComponent.popupFont(value);
     return this;
   }
   popupItemFont(value) {
     this.lazyComponent.popupItemFont(value);
     return this;
   }
   itemSize(value) {
     this.lazyComponent.itemSize(value);
     return this;
   }
   font(value) {
     this.lazyComponent.font(value);
     return this;
   }
   alignStyle(value, offset) {
     this.lazyComponent.alignStyle(value, offset);
     return this;
   }
   onSelect(value) {
     this.lazyComponent.onSelect(value);
     return this;
   }
   onRequestPopupData(value) {
     this.lazyComponent.onRequestPopupData(value);
     return this;
   }
   onPopupSelect(value) {
     this.lazyComponent.onPopupSelect(value);
     return this;
   }
   selected(value) {
     this.lazyComponent.selected(value);
     return this;
   }
   popupPosition(value) {
     this.lazyComponent.popupPosition(value);
     return this;
   }
   popupItemBorderRadius(value) {
     this.lazyComponent.popupItemBorderRadius(value);
     return this;
   }
   itemBorderRadius(value) {
     this.lazyComponent.itemBorderRadius(value);
     return this;
   }
   popupBackgroundBlurStyle(value) {
     this.lazyComponent.popupBackgroundBlurStyle(value);
     return this;
   }
   popupTitleBackground(value) {
     this.lazyComponent.popupTitleBackground(value);
     return this;
   }
   width(value) {
     this.lazyComponent.width(value);
     return this;
   }
   autoCollapse(value) {
     this.lazyComponent.autoCollapse(value);
     return this;
   }
   enableHapticFeedback(value) {
     this.lazyComponent.enableHapticFeedback(value);
     return this;
   }
   contentModifier(value) {
     this.lazyComponent.contentModifier(value);
     return this;
   }
 }
 class AlphabetIndexerModifier extends LazyAlphabetIndexerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class BlankModifier extends ArkBlankComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ButtonModifier extends ArkButtonComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkCalendarPickerComponent extends ArkComponent {
    static module = undefined;
    constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkCalendarPickerComponent.module === undefined) {
      LazyArkCalendarPickerComponent.module = globalThis.requireNapi('arkui.components.arkCalendarpicker');
    }
    this.lazyComponent = LazyArkCalendarPickerComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  value(value) {
    this.lazyComponent.value(value);
    return this;
  }
  edgeAlign(alignType, offset) {
    this.lazyComponent.edgeAlign(alignType, offset);
    return this;
  }
  textStyle(value) {
    this.lazyComponent.textStyle(value);
    return this;
  }
  onChange(value) {
    this.lazyComponent.onChange(value);
    return this;
  }
  padding(value) {
    this.lazyComponent.padding(value);
    return this;
  }
  border(value) {
    this.lazyComponent.border(value);
    return this;
  }
  height(value) {
    this.lazyComponent.height(value);
    return this;
  }
  borderRadius(value) {
    this.lazyComponent.borderRadius(value);
    return this;
  }
  borderColor(value) {
    this.lazyComponent.borderColor(value);
    return this;
  }
  markToday(value) {
    this.lazyComponent.markToday(value);
    return this;
  }
}

class CalendarPickerModifier extends LazyArkCalendarPickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkCheckboxComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkCheckboxComponent.module === undefined) {
      LazyArkCheckboxComponent.module = globalThis.requireNapi('arkui.components.arkcheckbox');
    }
    this.lazyComponent = LazyArkCheckboxComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }
  shape(value) {
    this.lazyComponent.shape(value);
    return this;
  }
  width(value) {
    this.lazyComponent.width(value);
    return this;
  }
  height(value) {
  this.lazyComponent.height(value);
    return this;
  }
  select(value) {
    this.lazyComponent.select(value);
    return this;
  }
  selectedColor(value) {
    this.lazyComponent.selectedColor(value);
    return this;
  }
  unselectedColor(value) {
    this.lazyComponent.unselectedColor(value);
    return this;
  }
  mark(value) {
    this.lazyComponent.mark(value);
    return this;
  }
  padding(value) {
    this.lazyComponent.padding(value);
    return this;
  }
  size(value) {
    this.lazyComponent.size(value);
    return this;
  }
  responseRegion(value) {
    this.lazyComponent.responseRegion(value);
    return this;
  }
  margin(value) {
    this.lazyComponent.margin(value);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
}

class CheckboxModifier extends LazyArkCheckboxComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkCheckboxGroupComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkCheckboxGroupComponent.module === undefined) {
      LazyArkCheckboxGroupComponent.module = globalThis.requireNapi('arkui.components.arkcheckboxgroup');
    }
    this.lazyComponent = LazyArkCheckboxGroupComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }
  selectAll(value) {
    this.lazyComponent.selectAll(value);
    return this;
  }
  selectedColor(value) {
    this.lazyComponent.selectedColor(value);
    return this;
  }
  unselectedColor(value) {
  this.lazyComponent.unselectedColor(value);
    return this;
  }
  mark(value) {
    this.lazyComponent.mark(value);
    return this;
  }
  onChange(value) {
    this.lazyComponent.onChange(value);
    return this;
  }
  size(value) {
    this.lazyComponent.size(value);
    return this;
  }
  width(value) {
    this.lazyComponent.width(value);
    return this;
  }
  height(value) {
    this.lazyComponent.height(value);
    return this;
  }
  checkboxShape(value) {
    this.lazyComponent.checkboxShape(value);
    return this;
  }
}

class CheckboxGroupModifier extends LazyArkCheckboxGroupComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class CircleModifier extends ArkCircleComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ColumnModifier extends ArkColumnComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkColumnSplitComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkColumnSplitComponent.module === undefined) {
      LazyArkColumnSplitComponent.module = globalThis.requireNapi('arkui.components.arkcolumnsplit');
    }
    this.lazyComponent = LazyArkColumnSplitComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  resizeable(value) {
    this.lazyComponent.resizeable(value);
    return this;
  }
  divider(value) {
    this.lazyComponent.divider(value);
    return this;
  }
  clip(value) {
    this.lazyComponent.clip(value);
    return this;
  }
}
class ColumnSplitModifier extends LazyArkColumnSplitComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkCounterComponent extends ArkComponent {
    static module = undefined;

    constructor(nativePtr, classType) {
      super(nativePtr, classType);
      if (LazyArkCounterComponent.module === undefined) {
        LazyArkCounterComponent.module = globalThis.requireNapi('arkui.components.arkcounter');
      }
      this.lazyComponent = LazyArkCounterComponent.module.createComponent(nativePtr, classType);
      console.log("LazyArkCounterComponent lazyload nativeModule");
    }
    setMap() {
      this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
    }
    onInc(event) {
      this.lazyComponent.onInc(event);
      return this;
    }
    onDec(event) {
      this.lazyComponent.onDec(event);
      return this;
    }
    enableDec(value) {
      this.lazyComponent.enableDec(value);
      return this;
    }
    enableInc(value) {
      this.lazyComponent.enableInc(value);
      return this;
    }
    backgroundColor(value) {
      this.lazyComponent.backgroundColor(value);
      return this;
    }
    width(value) {
      this.lazyComponent.width(value);
      return this;
    }
    height(value) {
      this.lazyComponent.height(value);
      return this;
    }
    size(value) {
      this.lazyComponent.size(value);
      return this;
    }
}
class CounterModifier extends LazyArkCounterComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkDataPanelComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkDataPanelComponent.module === undefined) {
      LazyArkDataPanelComponent.module = globalThis.requireNapi('arkui.components.arkdatapanel');
    }
    this.lazyComponent = LazyArkDataPanelComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  closeEffect(value) {
    this.lazyComponent.closeEffect(value);
    return this;
  }
  valueColors(value) {
    this.lazyComponent.valueColors(value);
    return this;
  }
  trackBackgroundColor(value) {
    this.lazyComponent.trackBackgroundColor(value);
    return this;
  }
  strokeWidth(value) {
    this.lazyComponent.strokeWidth(value);
    return this;
  }
  trackShadow(value) {
    this.lazyComponent.trackShadow(value);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}
  
class DataPanelModifier extends LazyArkDataPanelComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class DatePickerModifier extends ArkDatePickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class DividerModifier extends ArkDividerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class EmbeddedComponentModifier extends ArkEmbeddedComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class FlexModifier extends ArkFlexComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class FormComponentModifier extends ArkFormComponentComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkGaugeComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkGaugeComponent.module === undefined) {
      LazyArkGaugeComponent.module = globalThis.requireNapi('arkui.components.arkgauge');
    }
    this.lazyComponent = LazyArkGaugeComponent.module.createComponent(nativePtr, classType);
    console.log('LazyArkGaugeComponent lazyload nativeModule');
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  value(value) {
    this.lazyComponent.value(value);
    return this;
  }
  startAngle(angle) {
    this.lazyComponent.startAngle(angle);
    return this;
  }
  endAngle(angle) {
    this.lazyComponent.endAngle(angle);
    return this;
  }
  colors(colors) {
    this.lazyComponent.colors(colors);
    return this;
  }
  strokeWidth(length) {
    this.lazyComponent.strokeWidth(length);
    return this;
  }
  description(value) {
    throw new Error('Method not implemented.');
  }
  trackShadow(value) {
    this.lazyComponent.trackShadow(value);
    return this;
  }
  indicator(value) {
    this.lazyComponent.indicator(value);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}

class GaugeModifier extends LazyArkGaugeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class GridModifier extends ArkGridComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class GridColModifier extends ArkGridColComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class GridItemModifier extends ArkGridItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class GridRowModifier extends ArkGridRowComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkHyperlinkComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkHyperlinkComponent.module === undefined) {
      LazyArkHyperlinkComponent.module = globalThis.requireNapi('arkui.components.arkhyperlink');
    }
    this.lazyComponent = LazyArkHyperlinkComponent.module.createComponent(nativePtr, classType);
  }

  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  color(color) {
    this.lazyComponent.color(color);
    return this;
  }

  draggable(draggable) {
    this.lazyComponent.draggable(draggable);
    return this;
  }

  responseRegion(region) {
    this.lazyComponent.responseRegion(region);
    return this;
  }
}
class HyperlinkModifier extends LazyArkHyperlinkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
function copyImageAnimatorModifierWithKey(obj) {
  let _a;
  let _b;
  let newObj = { ...obj };
  if (obj.convertImageFrames !== undefined) {
    newObj.convertImageFrames = (_a = obj) === null || _a === void 0 ? void 0 : _a.convertImageFrames;
    newObj.isEqual = (_b = obj) === null || _b === void 0 ? void 0 : _b.isEqual;
  }
  newObj.applyStage = obj === null || obj === void 0 ? void 0 : obj.applyStage;
  newObj.applyPeer = obj === null || obj === void 0 ? void 0 : obj.applyPeer;
  newObj.checkObjectDiff = obj === null || obj === void 0 ? void 0 : obj.checkObjectDiff;
  return newObj;
}
function mergeImageAnimatorMaps(stageMap, newMap) {
  newMap.forEach((value, key) => {
    stageMap.set(key, copyImageAnimatorModifierWithKey(value));
  });
  return stageMap;
}
class ImageAnimatorModifier extends ArkImageAnimatorComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    let component = instance;
    mergeImageAnimatorMaps(component._modifiersWithKeys, this._modifiersWithKeys);
  }
}
class ImageModifier extends ArkImageComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ImageSpanModifier extends ArkImageSpanComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LineModifier extends ArkLineComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ListModifier extends ArkListComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ListItemModifier extends ArkListItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ListItemGroupModifier extends ArkListItemGroupComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LoadingProgressModifier extends ArkLoadingProgressComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkMarqueeComponent extends ArkComponent {
  static module = undefined;
 	constructor(nativePtr, classType) {
 	  super(nativePtr, classType);
 	  if (LazyArkMarqueeComponent.module === undefined) {
 	    LazyArkMarqueeComponent.module = globalThis.requireNapi('arkui.components.arkmarquee');
 	  }
 	  this.lazyComponent = LazyArkMarqueeComponent.module.createComponent(nativePtr, classType);
 	}
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  fontSize(value) {
    this.lazyComponent.fontSize(value);
    return this;
  }
  fontColor(value) {
    this.lazyComponent.fontColor(value);
    return this;
  }
  allowScale(value) {
    this.lazyComponent.allowScale(value);
    return this;
  }
  fontWeight(value) {
    this.lazyComponent.fontWeight(value);
    return this;
  }
  fontFamily(value) {
    this.lazyComponent.fontFamily(value);
    return this;
  }
  onStart(event) {
    this.lazyComponent.onStart(event);
    return this;
  }
  onBounce(event) {
    this.lazyComponent.onBounce(event);
    return this;
  }
  onFinish(event) {
    this.lazyComponent.onFinish(event);
    return this;
  }
  marqueeUpdateStrategy(value) {
    this.lazyComponent.marqueeUpdateStrategy(value);
    return this;
  }
}

class MarqueeModifier extends LazyArkMarqueeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkMenuComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkMenuComponent.module === undefined) {
      LazyArkMenuComponent.module = globalThis.requireNapi('arkui.components.arkmenu');
    }
    this.lazyComponent = LazyArkMenuComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  width(value) {
    this.lazyComponent.width(value);
    return this;
  }
  fontSize(value) {
    this.lazyComponent.fontSize(value);
    return this;
  }
  font(value) {
    this.lazyComponent.font(value);
    return this;
  }
  fontColor(value) {
    this.lazyComponent.fontColor(value);
    return this;
  }
  radius(value) {
    this.lazyComponent.radius(value);
    return this;
  }
  menuItemDivider(value) {
    this.lazyComponent.menuItemDivider(value);
    return this;
  }
  menuItemGroupDivider(value) {
    this.lazyComponent.menuItemGroupDivider(value);
    return this;
  }
  subMenuExpandingMode(value) {
    this.lazyComponent.subMenuExpandingMode(value);
    return this;
  }
  subMenuExpandSymbol(value) {
    this.lazyComponent.subMenuExpandSymbol(value);
    return this;
  }
}

class MenuModifier extends LazyArkMenuComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkMenuItemComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkMenuItemComponent.module === undefined) {
      LazyArkMenuItemComponent.module = globalThis.requireNapi('arkui.components.arkmenuitem');
    }
    this.lazyComponent = LazyArkMenuItemComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  selected(value) {
    this.lazyComponent.selected(value);
    return this;
  }
  selectIcon(value) {
    this.lazyComponent.selectIcon(value);
    return this;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
  contentFont(value) {
    this.lazyComponent.contentFont(value);
    return this;
  }
  contentFontColor(value) {
    this.lazyComponent.contentFontColor(value);
    return this;
  }
  labelFont(value) {
    this.lazyComponent.labelFont(value);
    return this;
  }
  labelFontColor(value) {
    this.lazyComponent.labelFontColor(value);
    return this;
  }
}

class MenuItemModifier extends LazyArkMenuItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class NavDestinationModifier extends ArkNavDestinationComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class NavigationModifier extends ArkNavigationComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class NavigatorModifier extends ArkNavigatorComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class NavRouterModifier extends ArkNavRouterComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class PanelModifier extends ArkPanelComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class PathModifier extends ArkPathComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkPatternLockComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkPatternLockComponent.module === undefined) {
      LazyArkPatternLockComponent.module = globalThis.requireNapi('arkui.components.arkpatternlock');
    }
    this.lazyComponent = LazyArkPatternLockComponent.module.createComponent(nativePtr, classType);
    console.log('LazyArkPatternLockComponent lazyload nativeModule');
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  sideLength(value) {
    this.lazyComponent.sideLength(value);
    return this;
  }
  circleRadius(value) {
    this.lazyComponent.circleRadius(value);
    return this;
  }
  regularColor(value) {
    this.lazyComponent.regularColor(value);
    return this;
  }
  selectedColor(value) {
    this.lazyComponent.selectedColor(value);
    return this;
  }
  activeColor(value) {
    this.lazyComponent.activeColor(value);
    return this;
  }
  pathColor(value) {
    this.lazyComponent.pathColor(value);
    return this;
  }
  pathStrokeWidth(value) {
    this.lazyComponent.pathStrokeWidth(value);
    return this;
  }
  autoReset(value) {
    this.lazyComponent.autoReset(value);
    return this;
  }
  activateCircleStyle(value) {
    this.lazyComponent.activateCircleStyle(value);
    return this;
  }
  skipUnselectedPoint(value) {
    this.lazyComponent.skipUnselectedPoint(value);
    return this;
  }
  backgroundColor(value) {
    this.lazyComponent.backgroundColor(value);
    return this;
  }
  onPatternComplete(callback) {
    this.lazyComponent.onPatternComplete(callback);
    return this;
  }
  onDotConnect(callback) {
    this.lazyComponent.onDotConnect(callback);
    return this;
  }
}
class PatternLockModifier extends LazyArkPatternLockComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class PluginComponentModifier extends ArkPluginComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class PolygonModifier extends ArkPolygonComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class PolylineModifier extends ArkPolylineComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ProgressModifier extends ArkProgressComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkQRCodeComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkQRCodeComponent.module === undefined) {
      LazyArkQRCodeComponent.module = globalThis.requireNapi('arkui.components.arkqrcode');
    }
    this.lazyComponent = LazyArkQRCodeComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  color(value) {
    this.lazyComponent.color(value);
    return this;
  }
  backgroundColor(value) {
    this.lazyComponent.backgroundColor(value);
    return this;
  }
  contentOpacity(value) {
    this.lazyComponent.contentOpacity(value);
    return this;
  }
}
class QRCodeModifier extends LazyArkQRCodeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkRadioComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkRadioComponent.module === undefined) {
      LazyArkRadioComponent.module = globalThis.requireNapi('arkui.components.arkradio');
    }
    this.lazyComponent = LazyArkRadioComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }
  checked(value) {
    this.lazyComponent.checked(value);
    return this;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
  radioStyle(value) {
    this.lazyComponent.radioStyle(value);
    return this;
  }
  width(value) {
    this.lazyComponent.width(value);
    return this;
  }
  height(value) {
    this.lazyComponent.height(value);
    return this;
  }
  size(value) {
    this.lazyComponent.size(value);
    return this;
  }
  hoverEffect(value) {
    this.lazyComponent.hoverEffect(value);
    return this;
  }
  padding(value) {
    this.lazyComponent.padding(value);
    return this;
  }
  responseRegion(value) {
    this.lazyComponent.responseRegion(value);
    return this;
  }
  margin(value) {
    this.lazyComponent.margin(value);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}

class RadioModifier extends LazyArkRadioComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkRatingComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkRatingComponent.module === undefined) {
      LazyArkRatingComponent.module = globalThis.requireNapi('arkui.components.arkrating');
    }
    this.lazyComponent = LazyArkRatingComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  stars(value) {
    this.lazyComponent.stars(value);
    return this;
  }
  stepSize(angle) {
    this.lazyComponent.stepSize(angle);
    return this;
  }
  starStyle(angle) {
    this.lazyComponent.starStyle(angle);
    return this;
  }
  onChange(angle) {
    this.lazyComponent.onChange(angle);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}

class RatingModifier extends LazyArkRatingComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RectModifier extends ArkRectComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RefreshModifier extends ArkRefreshComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RelativeContainerModifier extends ArkRelativeContainerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RichEditorModifier extends ArkRichEditorComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RowModifier extends ArkRowComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkRowSplitComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkRowSplitComponent.module === undefined) {
      LazyArkRowSplitComponent.module = globalThis.requireNapi('arkui.components.arkrowsplit');
    }
    this.lazyComponent = LazyArkRowSplitComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  resizeable(value) {
    this.lazyComponent.resizeable(value);
    return this;
  }
  clip(value) {
    this.lazyComponent.clip(value);
    return this;
  }
}
class RowSplitModifier extends LazyArkRowSplitComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ScrollModifier extends ArkScrollComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class SearchModifier extends ArkSearchComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class SelectModifier extends ArkSelectComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ShapeModifier extends ArkShapeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkSideBarContainerComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkSideBarContainerComponent.module === undefined) {
      LazyArkSideBarContainerComponent.module = globalThis.requireNapi('arkui.components.arksidebarcontainer');
    }
    this.lazyComponent = LazyArkSideBarContainerComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
  autoHide(value) {
    this.lazyComponent.autoHide(value);
    return this;
  }
  showSideBar(value) {
    this.lazyComponent.showSideBar(value);
    return this;
  }
  maxSideBarWidth(value) {
    this.lazyComponent.maxSideBarWidth(value);
    return this;
  }
  minSideBarWidth(value) {
    this.lazyComponent.minSideBarWidth(value);
    return this;
  }
  minContentWidth(value) {
    this.lazyComponent.minContentWidth(value);
    return this;
  }
  controlButton(value) {
    this.lazyComponent.controlButton(value);
    return this;
  }
  divider(value) {
    this.lazyComponent.divider(value);
    return this;
  }
  sideBarPosition(value) {
    this.lazyComponent.sideBarPosition(value);
    return this;
  }
  sideBarWidth(value) {
    this.lazyComponent.sideBarWidth(value);
    return this;
  }
  showControlButton(value) {
    this.lazyComponent.showControlButton(value);
    return this;
  }
}

class SideBarContainerModifier extends LazyArkSideBarContainerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkSliderComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkSliderComponent.module === undefined) {
      LazyArkSliderComponent.module = globalThis.requireNapi('arkui.components.arkslider');
    }
    this.lazyComponent = LazyArkSliderComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      this.lazyComponent.initialize(value[0]);
    } else {
      this.lazyComponent.initialize(undefined);
    }
    return this;
  }
  blockColor(value) {
    this.lazyComponent.blockColor(value);
    return this;
  }
  trackColor(value) {
    this.lazyComponent.trackColor(value);
    return this;
  }
  trackColorMetrics(value) {
    this.lazyComponent.trackColorMetrics(value);
    return this;
  }
  selectedColor(value) {
    this.lazyComponent.selectedColor(value);
    return this;
  }
  minLabel(value) {
    throw new Error('Method not implemented.');
  }
  maxLabel(value) {
    throw new Error('Method not implemented.');
  }
  showSteps(value, options) {
    this.lazyComponent.showSteps(value, options);
    return this;
  }
  showTips(value, content) {
    this.lazyComponent.showTips(value, content);
    return this;
  }
  trackThickness(value) {
    this.lazyComponent.trackThickness(value);
    return this;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
  blockBorderColor(value) {
    this.lazyComponent.blockBorderColor(value);
    return this;
  }
  blockBorderWidth(value) {
    this.lazyComponent.blockBorderWidth(value);
    return this;
  }
  stepColor(value) {
    this.lazyComponent.stepColor(value);
    return this;
  }
  trackBorderRadius(value) {
    this.lazyComponent.trackBorderRadius(value);
    return this;
  }
  selectedBorderRadius(value) {
    this.lazyComponent.selectedBorderRadius(value);
    return this;
  }
  blockSize(value) {
    this.lazyComponent.blockSize(value);
    return this;
  }
  blockStyle(value) {
    this.lazyComponent.blockStyle(value);
    return this;
  }
  stepSize(value) {
    this.lazyComponent.stepSize(value);
    return this;
  }
  sliderInteractionMode(value) {
    this.lazyComponent.sliderInteractionMode(value);
    return this;
  }
  minResponsiveDistance(value) {
    this.lazyComponent.minResponsiveDistance(value);
    return this;
  }
  contentModifier(value) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
  slideRange(value) {
    this.lazyComponent.slideRange(value);
    return this;
  }
  enableHapticFeedback(value) {
    this.lazyComponent.enableHapticFeedback(value);
    return this;
  }
  prefix(value, options) {
    this.lazyComponent.prefix(value, options);
    return this;
  }
  suffix(value, options) {
    this.lazyComponent.suffix(value, options);
    return this;
  }
}

class SliderModifier extends LazyArkSliderComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class SpanModifier extends ArkSpanComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class StackModifier extends ArkStackComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkStepperItemComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkStepperItemComponent.module === undefined) {
      LazyArkStepperItemComponent.module = globalThis.requireNapi('arkui.components.arkstepperitem');
    }
    this.lazyComponent = LazyArkStepperItemComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  prevLabel(value) {
    this.lazyComponent.prevLabel(value);
    return this;
  }
  nextLabel(value) {
    this.lazyComponent.nextLabel(value);
    return this;
  }
  status(value) {
    this.lazyComponent.status(value);
    return this;
  }
}
class StepperItemModifier extends LazyArkStepperItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class SwiperModifier extends ArkSwiperComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TabContentModifier extends ArkTabContentComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TabsModifier extends ArkTabsComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TextAreaModifier extends ArkTextAreaComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TextModifier extends ArkTextComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkTextClockComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkTextClockComponent.module === undefined) {
      LazyArkTextClockComponent.module = globalThis.requireNapi('arkui.components.arktextclock');
    }
    this.lazyComponent = LazyArkTextClockComponent.module.createComponent(nativePtr, classType);
    console.log("LazyArkTextClockComponent lazyload nativeModule")
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  value(value) {
    this.lazyComponent.value(value);
    return this;
  }
  format(value) {
    this.lazyComponent.format(value);
    return this;
  }
  onDateChange(event) {
    this.lazyComponent.onDateChange(event);
    return this;
  }
  fontColor(value) {
    this.lazyComponent.fontColor(value);
    return this;
  }
  fontSize(value) {
    this.lazyComponent.fontSize(value);
    return this;
  }
  fontStyle(value) {
    this.lazyComponent.fontStyle(value);
    return this;
  }
  fontWeight(value) {
    this.lazyComponent.fontWeight(value);
    return this;
  }
  fontFamily(value) {
    this.lazyComponent.fontFamily(value);
    return this;
  }
  textShadow(value) {
    this.lazyComponent.textShadow(value);
    return this;
  }
  fontFeature(value) {
    this.lazyComponent.fontFeature(value);
    return this;
  }
  contentModifier(modifier) {
    this.lazyComponent.contentModifier(modifier);
    return this;
  }
  dateTimeOptions(dateTimeOptions) {
    this.lazyComponent.dateTimeOptions(dateTimeOptions);
    return this;
  }
}

class TextClockModifier extends LazyArkTextClockComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TextInputModifier extends ArkTextInputComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TextPickerModifier extends ArkTextPickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class TextTimerModifier extends ArkTextTimerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkTimePickerComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkTimePickerComponent.module === undefined) {
      LazyArkTimePickerComponent.module = globalThis.requireNapi('arkui.components.arktimepicker');
    }
    this.lazyComponent = LazyArkTimePickerComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  loop(value) {
    this.lazyComponent.loop(value);
    return this;
  }
  digitalCrownSensitivity(value) {
    this.lazyComponent.digitalCrownSensitivity(value);
    return this;
  }
  useMilitaryTime(value) {
    this.lazyComponent.useMilitaryTime(value);
    return this;
  }
  disappearTextStyle(value) {
    this.lazyComponent.disappearTextStyle(value);
    return this;
  }
  textStyle(value) {
    this.lazyComponent.textStyle(value);
    return this;
  }
  selectedTextStyle(value) {
    this.lazyComponent.selectedTextStyle(value);
    return this;
  }
  enableCascade(value) {
    this.lazyComponent.enableCascade(value);
    return this;
  }
  onChange(value) {
    this.lazyComponent.onChange(value);
    return this;
  }
  dateTimeOptions(value) {
    this.lazyComponent.dateTimeOptions(value);
    return this;
  }
  enableHapticFeedback(value) {
    this.lazyComponent.enableHapticFeedback(value);
    return this;
  }
}

class TimePickerModifier extends LazyArkTimePickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ToggleModifier extends ArkToggleComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class VideoModifier extends ArkVideoComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkWaterFlowComponent extends ArkScrollable {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkWaterFlowComponent.module === undefined) {
      LazyArkWaterFlowComponent.module = globalThis.requireNapi('arkui.components.arkwaterflow');
    }
    this.lazyComponent = LazyArkWaterFlowComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  columnsGap(value) {
    this.lazyComponent.columnsGap(value);
    return this;
  }
  rowsGap(value) {
    this.lazyComponent.rowsGap(value);
    return this;
  }
  layoutDirection(value) {
    this.lazyComponent.layoutDirection(value);
    return this;
  }
  columnsTemplate(value) {
    this.lazyComponent.columnsTemplate(value);
    return this;
  }
  itemConstraintSize(value) {
    this.lazyComponent.itemConstraintSize(value);
    return this;
  }
  rowsTemplate(value) {
    this.lazyComponent.rowsTemplate(value);
    return this;
  }
  nestedScroll(value) {
    this.lazyComponent.nestedScroll(value);
    return this;
  }
  enableScrollInteraction(value) {
    this.lazyComponent.enableScrollInteraction(value);
    return this;
  }
  friction(value) {
    this.lazyComponent.friction(value);
    return this;
  }
  clip(value) {
    this.lazyComponent.clip(value);
    return this;
  }
  cachedCount(count, show) {
    this.lazyComponent.cachedCount(count, show);
    return this;
  }
  edgeEffect(edgeEffect, options) {
    this.lazyComponent.edgeEffect(edgeEffect, options);
    return this;
  }
  syncLoad(value) {
    this.lazyComponent.syncLoad(value);
    return this;
  }
  scrollBar(value) {
    this.lazyComponent.scrollBar(value);
    return this;
  }
  scrollBarWidth(value) {
    this.lazyComponent.scrollBarWidth(value);
    return this;
  }
  scrollBarColor(value) {
    this.lazyComponent.scrollBarColor(value);
    return this;
  }
  onScroll(value) {
    this.lazyComponent.onScroll(value);
    return this;
  }
  onScrollStart(value) {
    this.lazyComponent.onScrollStart(value);
    return this;
  }
  onScrollStop(value) {
    this.lazyComponent.onScrollStop(value);
    return this;
  }
  onScrollIndex(value) {
    this.lazyComponent.onScrollIndex(value);
    return this;
  }
  onReachStart(value) {
    this.lazyComponent.onReachStart(value);
    return this;
  }
  onReachEnd(value) {
    this.lazyComponent.onReachEnd(value);
    return this;
  }
  onScrollFrameBegin(value) {
    this.lazyComponent.onScrollFrameBegin(value);
    return this;
  }
  remoteMessage(value) {
    this.lazyComponent.remoteMessage(value);
    return this;
  }
  onClick(value) {
    this.lazyComponent.onClick(value);
    return this;
  }
  onTouch(value) {
    this.lazyComponent.onTouch(value);
    return this;
  }
  onHover(value) {
    this.lazyComponent.onHover(value);
    return this;
  }
  onKeyEvent(value) {
    this.lazyComponent.onKeyEvent(value);
    return this;
  }
  onDeleteEvent(value) {
    this.lazyComponent.onDeleteEvent(value);
    return this;
  }
  onAttach(value) {
    this.lazyComponent.onAttach(value);
    return this;
  }
  onAppear(value) {
    this.lazyComponent.onAppear(value);
    return this;
  }
  onDetach(value) {
    this.lazyComponent.onDetach(value);
    return this;
  }
  onDisAppear(value) {
    this.lazyComponent.onDisAppear(value);
    return this;
  }
  attributeModifier(modifier) {
    this.lazyComponent.attributeModifier(modifier);
    return this;
  };
  onWillStopDragging(value) {
    this.lazyComponent.onWillStopDragging(value);
    return this;
  };
  onWillStartDragging(value) {
    this.lazyComponent.onWillStartDragging(value);
    return this;
  };
  onDidStopDragging(value) {
    this.lazyComponent.onDidStopDragging(value);
    return this;
  };
  onWillStartFling(value) {
    this.lazyComponent.onWillStartFling(value);
    return this;
  };
  onDidStopFling(value) {
    this.lazyComponent.onDidStopFling(value);
    return this;
  };
}
class WaterFlowModifier extends LazyArkWaterFlowComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class ParticleModifier extends ArkParticleComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class MediaCachedImageModifier extends ArkMediaCachedImageComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class LazyArkSymbolGlyphComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkSymbolGlyphComponent.module === undefined) {
      LazyArkSymbolGlyphComponent.module = globalThis.requireNapi('arkui.components.arksymbolglyph');
    }
    this.lazyComponent = LazyArkSymbolGlyphComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  initialize(value) {
    this.lazyComponent.initialize(value);
    return this;
  }
  fontColor(value) {
    this.lazyComponent.fontColor(value);
    return this;
  }
  fontSize(value) {
    this.lazyComponent.fontSize(value);
    return this;
  }
  fontWeight(value) {
    this.lazyComponent.fontWeight(value);
    return this;
  }
  renderingStrategy(value) {
    this.lazyComponent.renderingStrategy(value);
    return this;
  }
  effectStrategy(value) {
    this.lazyComponent.effectStrategy(value);
    return this;
  }
  symbolEffect(effect, action) {
    this.lazyComponent.symbolEffect(effect, action);
    return this;
  }
  shaderStyle(value) {
    this.lazyComponent.shaderStyle(value);
    return this;
  }
  symbolShadow(value) {
    this.lazyComponent.symbolShadow(value);
    return this;
  }
  minFontScale(value) {
    this.lazyComponent.minFontScale(value);
    return this;
  }
  maxFontScale(value) {
    this.lazyComponent.maxFontScale(value);
    return this;
  }
}
class SymbolGlyphModifier extends LazyArkSymbolGlyphComponent {
  constructor(src, nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
    if (src !== undefined) {
      this.initialize([src]);
    }
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class SymbolSpanModifier extends ArkSymbolSpanComponent {
  constructor(src, nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    if (src !== undefined) {
      this.initialize([src]);
    }
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class Component3DModifier extends ArkComponent3DComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class ContainerSpanModifier extends ArkContainerSpanComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class IndicatorComponentModifier extends ArkIndicatorComponentComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyVGridLayoutModifier extends ArkLazyVGridLayoutComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class LazyArkStepperComponent extends ArkComponent {
  static module = undefined;
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    if (LazyArkStepperComponent.module === undefined) {
      LazyArkStepperComponent.module = globalThis.requireNapi('arkui.components.arkstepper');
    }
    this.lazyComponent = LazyArkStepperComponent.module.createComponent(nativePtr, classType);
  }
  setMap() {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }
  onFinish(callback) {
    this.lazyComponent.onFinish(callback);
    return this;
  }
  onSkip(callback) {
    this.lazyComponent.onSkip(callback);
    return this;
  }
  onChange(callback) {
    this.lazyComponent.onChange(callback);
    return this;
  }
  onNext(callback) {
    this.lazyComponent.onNext(callback);
    return this;
  }
  onPrevious(callback) {
    this.lazyComponent.onPrevious(callback);
    return this;
  }
}
class StepperModifier extends LazyArkStepperComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

class UIPickerComponentModifier extends ArkContainerPickerComponent {
    constructor(nativePtr, classType) {
      super(nativePtr, classType);
      this._modifiersWithKeys = new ModifierMap();
    }
    applyNormalAttribute(instance) {
      ModifierUtils.applySetOnChange(this);
      ModifierUtils.applyAndMergeModifier(instance, this);
    }
}

class UnionEffectContainerModifier extends ArkUnionEffectContainerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

export default { CommonModifier, AlphabetIndexerModifier, BlankModifier, ButtonModifier, CalendarPickerModifier, CheckboxModifier, CheckboxGroupModifier, CircleModifier,
  ColumnModifier, ColumnSplitModifier, CounterModifier, DataPanelModifier, DatePickerModifier, DividerModifier, FormComponentModifier, GaugeModifier,
  GridModifier, GridColModifier, GridItemModifier, GridRowModifier, HyperlinkModifier, ImageAnimatorModifier, ImageModifier, ImageSpanModifier, LineModifier,
  ListModifier, ListItemModifier, ListItemGroupModifier, LoadingProgressModifier, MarqueeModifier, MenuModifier, MenuItemModifier, NavDestinationModifier,
  NavigationModifier, NavigatorModifier, NavRouterModifier, PanelModifier, PathModifier, PatternLockModifier, PolygonModifier, PolylineModifier,
  ProgressModifier, QRCodeModifier, RadioModifier, RatingModifier, RectModifier, RelativeContainerModifier, RichEditorModifier, RowModifier, RowSplitModifier,
  ScrollModifier, SearchModifier, SelectModifier, ShapeModifier, SideBarContainerModifier, SliderModifier, SpanModifier, StackModifier, StepperItemModifier,
  SwiperModifier, TabsModifier, TextAreaModifier, TextModifier, TextClockModifier, TextInputModifier, TextPickerModifier, TextTimerModifier, TimePickerModifier,
  ToggleModifier, VideoModifier, WaterFlowModifier, FlexModifier, PluginComponentModifier, RefreshModifier, TabContentModifier, ModifierUtils, AttributeUpdater,
  ParticleModifier, MediaCachedImageModifier, SymbolGlyphModifier, SymbolSpanModifier, Component3DModifier, ContainerSpanModifier, ModifierMap,
  IndicatorComponentModifier, LazyVGridLayoutModifier, StepperModifier, EmbeddedComponentModifier, UIPickerComponentModifier, UnionEffectContainerModifier
};

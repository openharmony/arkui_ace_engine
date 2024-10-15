/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
    ['Symbol(width)', CheckboxWidthModifier],
    ['Symbol(height)', CheckboxHeightModifier],
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
        ArkLogConsole.info('key of modifier map is undefined, ModifierWithKey is ' +
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
      myMap.setOnChange((key, value) => {
        this.putDirtyModifier(modifier, value);
      });
    } else {
      myMap.setOnChange((key, value) => {
        modifier._changed = !modifier._changed;
      });
    }
  }
  static putDirtyModifier(arkModifier, attributeModifierWithKey) {
    attributeModifierWithKey.value = attributeModifierWithKey.stageValue;
    if (!arkModifier._weakPtr.invalid()) {
      attributeModifierWithKey.applyPeer(arkModifier.nativePtr,
        (attributeModifierWithKey.value === undefined ||
          attributeModifierWithKey.value === null)
      );
    } else {
      ArkLogConsole.info('pointer is invalid when putDirtyModifier in ' + (arkModifier ?
        arkModifier.constructor.name.toString() : 'undefined') + ' of ' + (attributeModifierWithKey ?
        attributeModifierWithKey.constructor.name.toString() : 'undefined'));
    }
    this.dirtyComponentSet.add(arkModifier);
    if (!this.dirtyFlag) {
      this.dirtyFlag = true;
      this.requestFrame();
    }
  }
  static requestFrame() {
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
      ArkLogConsole.info('AttributeUpdater has not been initialized before updateConstructorParams.');
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
class AlphabetIndexerModifier extends ArkAlphabetIndexerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class CalendarPickerModifier extends ArkCalendarPickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class CheckboxModifier extends ArkCheckboxComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class CheckboxGroupModifier extends ArkCheckboxGroupComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class ColumnSplitModifier extends ArkColumnSplitComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class CounterModifier extends ArkCounterComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class DataPanelModifier extends ArkDataPanelComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class GaugeModifier extends ArkGaugeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class HyperlinkModifier extends ArkHyperlinkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class MarqueeModifier extends ArkMarqueeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class MenuModifier extends ArkMenuComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class MenuItemModifier extends ArkMenuItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class PatternLockModifier extends ArkPatternLockComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class QRCodeModifier extends ArkQRCodeComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RadioModifier extends ArkRadioComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class RatingModifier extends ArkRatingComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class RowSplitModifier extends ArkRowSplitComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class SideBarContainerModifier extends ArkSideBarContainerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class SliderModifier extends ArkSliderComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class StepperItemModifier extends ArkStepperItemComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class TextClockModifier extends ArkTextClockComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class TimePickerModifier extends ArkTimePickerComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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
class WaterFlowModifier extends ArkWaterFlowComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
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

class SymbolGlyphModifier extends ArkSymbolGlyphComponent {
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

class LinearIndicatorModifier extends ArkLinearIndicatorComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}

export default {
  CommonModifier, AlphabetIndexerModifier, BlankModifier, ButtonModifier, CalendarPickerModifier, CheckboxModifier, CheckboxGroupModifier, CircleModifier,
  ColumnModifier, ColumnSplitModifier, CounterModifier, DataPanelModifier, DatePickerModifier, DividerModifier, FormComponentModifier, GaugeModifier,
  GridModifier, GridColModifier, GridItemModifier, GridRowModifier, HyperlinkModifier, ImageAnimatorModifier, ImageModifier, ImageSpanModifier, LineModifier,
  ListModifier, ListItemModifier, ListItemGroupModifier, LoadingProgressModifier, MarqueeModifier, MenuModifier, MenuItemModifier, NavDestinationModifier,
  NavigationModifier, NavigatorModifier, NavRouterModifier, PanelModifier, PathModifier, PatternLockModifier, PolygonModifier, PolylineModifier,
  ProgressModifier, QRCodeModifier, RadioModifier, RatingModifier, RectModifier, RelativeContainerModifier, RichEditorModifier, RowModifier, RowSplitModifier,
  ScrollModifier, SearchModifier, SelectModifier, ShapeModifier, SideBarContainerModifier, SliderModifier, SpanModifier, StackModifier, StepperItemModifier,
  SwiperModifier, TabsModifier, TextAreaModifier, TextModifier, TextClockModifier, TextInputModifier, TextPickerModifier, TextTimerModifier, TimePickerModifier,
  ToggleModifier, VideoModifier, WaterFlowModifier, FlexModifier, PluginComponentModifier, RefreshModifier, TabContentModifier, ModifierUtils, AttributeUpdater,
  ParticleModifier, MediaCachedImageModifier, SymbolGlyphModifier, SymbolSpanModifier, Component3DModifier, ContainerSpanModifier, LinearIndicatorModifier
};

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

function applyAndMergeModifier(instance, modifier) {
  let myMap = modifier._modifiersWithKeys;
  myMap.setOnChange((value) => {
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
      stageMap.set(key, copyModifierWithKey(value));
    });
    return stageMap;
  }
  static applyAndMergeModifier(instance, modifier) {
    let component = instance;
    mergeMaps(component._modifiersWithKeys, modifier._modifiersWithKeys);
  }
  static applySetOnChange(modifier) {
    let myMap = modifier._modifiersWithKeys;
    if (modifier._classType === ModifierType.STATE) {
      myMap.setOnChange((value) => {
        this.putDirtyModifier(modifier, value);
      });
    }
    else {
      myMap.setOnChange((value) => {
        modifier._changed = !modifier._changed;
      });
    }
  }
  static putDirtyModifier(arkModifier, attributeModifierWithKey) {
    attributeModifierWithKey.value = attributeModifierWithKey.stageValue;
    if (!arkModifier._weakPtr.invalid()) {
      attributeModifierWithKey.applyPeer(arkModifier.nativePtr, (attributeModifierWithKey.stageValue === undefined || attributeModifierWithKey.stageValue === null));
    }
    this.dirtyComponentSet.add(arkModifier);
    if (!this.dirtyFlag) {
      this.dirtyFlag = true;
      this.requestFrame();
    }
  }
  static requestFrame() {
    getUINativeModule().frameNode.registerFrameCallback(() => {
      this.dirtyComponentSet.forEach(item => {
        if (item._nativePtrChanged && !item._weakPtr.invalid()) {
          item._modifiersWithKeys.forEach((value, key) => {
            value.applyPeer(item.nativePtr, false);
          })
          item._nativePtrChanged = false;
        }
        getUINativeModule().frameNode.markDirty(item.nativePtr, 0b100);
      });
      this.dirtyComponentSet.clear();
      this.dirtyFlag = false;
    });
  }
}
ModifierUtils.dirtyComponentSet = new Set();
ModifierUtils.dirtyFlag = false;
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
    _a === null || _a === void 0 ? void 0 : _a.call(this, value);
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
  initializeModifier(instance) { }
}
AttributeUpdater.StateEnum = {
  INIT: 0,
  UPDATE: 1
};
class CommonModifier extends ArkComponent {
  constructor(classType, nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
    this._classType = classType;
    if (classType === modifierType.STATE) {
      this._weakPtr = getUINativeModule().nativeUtils.createNativeWeakRef(nativePtr);
    }
  }
  applyNormalAttribute(instance) {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier(instance, this);
  }
}
class AlphabetIndexerModifier extends ArkAlphabetIndexerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class BlankModifier extends ArkBlankComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
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
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class CheckboxModifier extends ArkCheckboxComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class CheckboxGroupModifier extends ArkCheckboxGroupComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
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
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ColumnSplitModifier extends ArkColumnSplitComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class CounterModifier extends ArkCounterComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class DataPanelModifier extends ArkDataPanelComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class DatePickerModifier extends ArkDatePickerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class DividerModifier extends ArkDividerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class FormComponentModifier extends ArkFormComponentComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class GaugeModifier extends ArkGaugeComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class GridModifier extends ArkGridComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class GridColModifier extends ArkGridColComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class GridItemModifier extends ArkGridItemComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class GridRowModifier extends ArkGridRowComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class HyperlinkModifier extends ArkHyperlinkComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
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
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    let myMap = this._modifiersWithKeys;
    myMap.setOnChange((value) => {
      this._changed = !this._changed;
    });
    let component = instance;
    mergeImageAnimatorMaps(component._modifiersWithKeys, this._modifiersWithKeys);
  }
}
class ImageModifier extends ArkImageComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ImageSpanModifier extends ArkImageSpanComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class LineModifier extends ArkLineComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListModifier extends ArkListComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListItemModifier extends ArkListItemComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ListItemGroupModifier extends ArkListItemGroupComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class LoadingProgressModifier extends ArkLoadingProgressComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class MarqueeModifier extends ArkMarqueeComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class MenuModifier extends ArkMenuComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class MenuItemModifier extends ArkMenuItemComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class NavDestinationModifier extends ArkNavDestinationComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class NavigationModifier extends ArkNavigationComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class NavigatorModifier extends ArkNavigatorComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class NavRouterModifier extends ArkNavRouterComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class PanelModifier extends ArkPanelComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class PathModifier extends ArkPathComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class PatternLockModifier extends ArkPatternLockComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class PolygonModifier extends ArkPolygonComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class PolylineModifier extends ArkPolylineComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ProgressModifier extends ArkProgressComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class QRCodeModifier extends ArkQRCodeComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class RadioModifier extends ArkRadioComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class RatingModifier extends ArkRatingComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
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
class RichEditorModifier extends ArkRichEditorComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class RowModifier extends ArkRowComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class RowSplitModifier extends ArkRowSplitComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ScrollModifier extends ArkScrollComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SearchModifier extends ArkSearchComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SelectModifier extends ArkSelectComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ShapeModifier extends ArkShapeComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SideBarContainerModifier extends ArkSideBarContainerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SliderModifier extends ArkSliderComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SpanModifier extends ArkSpanComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._changed = false;
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    let myMap = this._modifiersWithKeys;
    myMap.setOnChange(() => {
      this._changed = !this._changed;
    });
    let component = instance;
    mergeMaps(component._modifiersWithKeys, this._modifiersWithKeys);
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
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class SwiperModifier extends ArkSwiperComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TabsModifier extends ArkTabsComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TextAreaModifier extends ArkTextAreaComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
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
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TextInputModifier extends ArkTextInputComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TextPickerModifier extends ArkTextPickerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TextTimerModifier extends ArkTextTimerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class TimePickerModifier extends ArkTimePickerComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class ToggleModifier extends ArkToggleComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class VideoModifier extends ArkVideoComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}
class WaterFlowModifier extends ArkWaterFlowComponent {
  constructor(nativePtr) {
    super(nativePtr);
    this._modifiersWithKeys = new ModifierMap();
  }
  applyNormalAttribute(instance) {
    applyAndMergeModifier(instance, this);
  }
}

export default { CommonModifier, AlphabetIndexerModifier, BlankModifier, ButtonModifier, CalendarPickerModifier, CheckboxModifier, CheckboxGroupModifier, CircleModifier,
  ColumnModifier, ColumnSplitModifier, CounterModifier, DataPanelModifier, DatePickerModifier, DividerModifier, FormComponentModifier, GaugeModifier,
  GridModifier, GridColModifier, GridItemModifier, GridRowModifier, HyperlinkModifier, ImageAnimatorModifier, ImageModifier, ImageSpanModifier, LineModifier,
  ListModifier, ListItemModifier, ListItemGroupModifier, LoadingProgressModifier, MarqueeModifier, MenuModifier, MenuItemModifier, NavDestinationModifier,
  NavigationModifier, NavigatorModifier, NavRouterModifier, PanelModifier, PathModifier, PatternLockModifier, PolygonModifier, PolylineModifier,
  ProgressModifier, QRCodeModifier, RadioModifier, RatingModifier, RectModifier, RichEditorModifier, RowModifier, RowSplitModifier, ScrollModifier,
  SearchModifier, SelectModifier, ShapeModifier, SideBarContainerModifier, SliderModifier, SpanModifier, StackModifier, StepperItemModifier, SwiperModifier,
  TabsModifier, TextAreaModifier, TextModifier, TextClockModifier, TextInputModifier, TextPickerModifier, TextTimerModifier, TimePickerModifier, ToggleModifier,
  VideoModifier, WaterFlowModifier, ModifierUtils, AttributeUpdater };

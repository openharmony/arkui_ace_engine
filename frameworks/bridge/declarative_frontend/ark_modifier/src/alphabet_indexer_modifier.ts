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

class LazyAlphabetIndexerComponent extends ArkComponent {
  static module: any = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyAlphabetIndexerComponent.module === undefined) {
      LazyAlphabetIndexerComponent.module = globalThis.requireNapi('arkui.components.arkalphabetindexer');
    }
    this.lazyComponent = LazyAlphabetIndexerComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  onSelected(value: any) {
    this.lazyComponent.onSelected(value);
    return this;
  }

  color(value: any) {
    this.lazyComponent.color(value);
    return this;
  }

  selectedColor(value: any) {
    this.lazyComponent.selectedColor(value);
    return this;
  }

  popupColor(value: any) {
    this.lazyComponent.popupColor(value);
    return this;
  }

  selectedBackgroundColor(value: any) {
    this.lazyComponent.selectedBackgroundColor(value);
    return this;
  }

  popupBackground(value: any) {
    this.lazyComponent.popupBackground(value);
    return this;
  }

  popupSelectedColor(value: any) {
    this.lazyComponent.popupSelectedColor(value);
    return this;
  }

  popupUnselectedColor(value: any) {
    this.lazyComponent.popupUnselectedColor(value);
    return this;
  }

  popupItemBackgroundColor(value: any) {
    this.lazyComponent.popupItemBackgroundColor(value);
    return this;
  }

  usingPopup(value: any) {
    this.lazyComponent.usingPopup(value);
    return this;
  }

  selectedFont(value: any) {
    this.lazyComponent.selectedFont(value);
    return this;
  }

  popupFont(value: any) {
    this.lazyComponent.popupFont(value);
    return this;
  }

  popupItemFont(value: any) {
    this.lazyComponent.popupItemFont(value);
    return this;
  }

  itemSize(value: any) {
    this.lazyComponent.itemSize(value);
    return this;
  }

  font(value: any) {
    this.lazyComponent.font(value);
    return this;
  }

  alignStyle(value: any, offset: any) {
    this.lazyComponent.alignStyle(value, offset);
    return this;
  }

  onSelect(value: any) {
    this.lazyComponent.onSelect(value);
    return this;
  }

  onRequestPopupData(value: any) {
    this.lazyComponent.onRequestPopupData(value);
    return this;
  }

  onPopupSelect(value: any) {
    this.lazyComponent.onPopupSelect(value);
    return this;
  }

  selected(value: any) {
    this.lazyComponent.selected(value);
    return this;
  }

  popupPosition(value: any) {
    this.lazyComponent.popupPosition(value);
    return this;
  }

  popupItemBorderRadius(value: any) {
    this.lazyComponent.popupItemBorderRadius(value);
    return this;
  }

  itemBorderRadius(value: any) {
    this.lazyComponent.itemBorderRadius(value);
    return this;
  }

  popupBackgroundBlurStyle(value: any) {
    this.lazyComponent.popupBackgroundBlurStyle(value);
    return this;
  }

  popupTitleBackground(value: any) {
    this.lazyComponent.popupTitleBackground(value);
    return this;
  }

  width(value: any) {
    this.lazyComponent.width(value);
    return this;
  }

  autoCollapse(value: any) {
    this.lazyComponent.autoCollapse(value);
    return this;
  }

  enableHapticFeedback(value: any) {
    this.lazyComponent.enableHapticFeedback(value);
    return this;
  }

  contentModifier(value: any) {
    this.lazyComponent.contentModifier(value);
    return this;
  }
}
class AlphabetIndexerModifier extends LazyAlphabetIndexerComponent implements AttributeModifier<AlphabetIndexerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: AlphabetIndexerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<AlphabetIndexerAttribute, ArkAlphabetIndexerComponent, ArkComponent>(instance, this);
  }
}

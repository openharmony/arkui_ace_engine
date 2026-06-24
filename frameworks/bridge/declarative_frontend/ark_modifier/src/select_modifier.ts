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

class LazyArkSelectComponent extends ArkComponent {
  static module: SelectComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
   super(nativePtr, classType);
   if (LazyArkSelectComponent.module === undefined) {
     LazyArkSelectComponent.module = globalThis.requireNapi('arkui.components.arkselect');
   }

   this.lazyComponent = LazyArkSelectComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
   this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
   return 0;
  }

  initialize(value: SelectOption) {
    this.lazyComponent.initialize(value);
    return this;
  }

  optionWidth(value: Dimension | OptionWidthMode): this {
    this.lazyComponent.optionWidth(value);
    return this;
  }
  optionHeight(value: Dimension): this {
    this.lazyComponent.optionHeight(value);
    return this;
  }
  width(value: Length): this {
    this.lazyComponent.width(value);
    return this;
  }
  height(value: Length): this {
    this.lazyComponent.height(value);
    return this;
  }
  size(value: SizeOptions): this {
    this.lazyComponent.size(value);
    return this;
  }
  selected(value: number | Resource): this {
    this.lazyComponent.selected(value);
    return this;
  }
  value(value: ResourceStr): this {
    this.lazyComponent.value(value);
    return this;
  }
  font(value: Font): this {
    this.lazyComponent.font(value);
    return this;
  }
  fontColor(value: ResourceColor): this {
    this.lazyComponent.fontColor(value);
    return this;
  }
  selectedOptionBgColor(value: ResourceColor): this {
    this.lazyComponent.selectedOptionBgColor(value);
    return this;
  }
  selectedOptionFont(value: Font): this {
    this.lazyComponent.selectedOptionFont(value);
    return this;
  }
  selectedOptionFontColor(value: ResourceColor): this {
    this.lazyComponent.selectedOptionFontColor(value);
    return this;
  }
  optionBgColor(value: ResourceColor): this {
    this.lazyComponent.optionBgColor(value);
    return this;
  }
  optionFont(value: Font): this {
    this.lazyComponent.optionFont(value);
    return this;
  }
  optionFontColor(value: ResourceColor): this {
    this.lazyComponent.optionFontColor(value);
    return this;
  }
  onSelect(callback: (value: OnSelectCallback) => void): this {
    this.lazyComponent.onSelect(callback);
    return this;
  }
  space(value: Length): this {
    this.lazyComponent.space(value);
    return this;
  }
  arrowPosition(value: ArrowPosition): this {
    this.lazyComponent.arrowPosition(value);
    return this;
  }
  menuAlign(alignType: MenuAlignType, offset?: Offset): this {
    this.lazyComponent.menuAlign(alignType, offset);
    return this;
  }
  menuBackgroundColor(value: ResourceColor): this {
    this.lazyComponent.menuBackgroundColor(value);
    return this;
  }
  menuBackgroundBlurStyle(value: BlurStyle): this {
    this.lazyComponent.menuBackgroundBlurStyle(value);
    return this;
  }
  controlSize(controlSize: ControlSize): this {
    this.lazyComponent.controlSize(controlSize);
    return this;
  }
  contentModifier(value: ContentModifier<MenuItemConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }
  divider(value: DividerOptions | null): this {
    this.lazyComponent.divider(value);
    return this;
  }
  dividerStyle(value: Optional<DividerStyleOptions>): this {
    this.lazyComponent.dividerStyle(value);
    return this;
  }
  direction(value: Direction): this {
    this.lazyComponent.direction(value);
    return this;
  }
  avoidance(value: Direction): this {
    this.lazyComponent.avoidance(value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }
  menuOutline(outline: MenuOutlineOptions): this {
    this.lazyComponent.menuOutline(outline);
    return this;
  }
  keyboardAvoidMode(mode: Optional<MenuKeyboardAvoidMode>): this {
    this.lazyComponent.keyboardAvoidMode(mode);
    return this;
  }
  minKeyboardAvoidDistance(distance: Optional<LengthMetrics>): this {
    this.lazyComponent.minKeyboardAvoidDistance(distance);
    return this;
  }
  menuSystemMaterial(menuSystemMaterial: SystemUiMaterial): this {
    this.lazyComponent.menuSystemMaterial(menuSystemMaterial);
    return this;
  }
  menuBackgroundBlurStyleOptions(menuBackgroundBlurStyleOptions: Optional<BackgroundBlurStyleOptions>): this {
    this.lazyComponent.menuBackgroundBlurStyleOptions(menuBackgroundBlurStyleOptions);
    return this;
  }
  menuBackgroundEffect(menuBackgroundEffect: Optional<BackgroundEffectOptions>): this {
    this.lazyComponent.menuBackgroundEffect(menuBackgroundEffect);
    return this;
  }
  menuDistortionMode(mode: DistortionMode): this {
    this.lazyComponent.menuDistortionMode(mode);
    return this;
  }
  menuEdgeLightMode(mode: EdgeLightMode): this {
    this.lazyComponent.menuEdgeLightMode(mode);
    return this;
  }
}

class SelectModifier extends LazyArkSelectComponent implements AttributeModifier<SelectAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SelectAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<SelectAttribute, ArkSelectComponent, ArkComponent>(instance, this);
  }
}

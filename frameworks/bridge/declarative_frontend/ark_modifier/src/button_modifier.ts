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

class LazyArkButtonComponent extends ArkComponent {
  static module: ButtonComponentModule | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkButtonComponent.module === undefined) {
      LazyArkButtonComponent.module = globalThis.requireNapi('arkui.components.arkbutton');
    }
    this.lazyComponent = LazyArkButtonComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
    return this.lazyComponent.allowChildCount();
  }

  initialize(value: Object[]): this {
    this.lazyComponent.initialize(value);
    return this;
  }

  backgroundColor(value: ResourceColor): this {
    this.lazyComponent.backgroundColor(value);
    return this;
  }

  type(value: ButtonType): this {
    this.lazyComponent.type(value);
    return this;
  }

  stateEffect(value: boolean): this {
    this.lazyComponent.stateEffect(value);
    return this;
  }

  fontColor(value: ResourceColor): this {
    this.lazyComponent.fontColor(value);
    return this;
  }

  fontSize(value: Length): this {
    this.lazyComponent.fontSize(value);
    return this;
  }

  fontWeight(value: string | number | FontWeight): this {
    this.lazyComponent.fontWeight(value);
    return this;
  }

  fontStyle(value: FontStyle): this {
    this.lazyComponent.fontStyle(value);
    return this;
  }

  fontFamily(value: string | Resource): this {
    this.lazyComponent.fontFamily(value);
    return this;
  }

  labelStyle(value: LabelStyle): this {
    this.lazyComponent.labelStyle(value);
    return this;
  }

  borderRadius(value: Length | BorderRadiuses): this {
    this.lazyComponent.borderRadius(value);
    return this;
  }

  border(value: BorderOptions): this {
    this.lazyComponent.border(value);
    return this;
  }

  size(value: SizeOptions): this {
    this.lazyComponent.size(value);
    return this;
  }

  contentModifier(value: ContentModifier<ButtonConfiguration>): this {
    this.lazyComponent.contentModifier(value);
    return this;
  }

  role(value: ButtonRole): this {
    this.lazyComponent.role(value);
    return this;
  }

  buttonStyle(value: ButtonStyleMode): this {
    this.lazyComponent.buttonStyle(value);
    return this;
  }

  controlSize(value: ControlSize): this {
    this.lazyComponent.controlSize(value);
    return this;
  }

  minFontScale(value: number | Resource): this {
    this.lazyComponent.minFontScale(value);
    return this;
  }

  maxFontScale(value: number | Resource): this {
    this.lazyComponent.maxFontScale(value);
    return this;
  }

  fontFeature(value: string): this {
    return this;
  }

  minFontSize(value: number | string | Resource): this {
    return this;
  }

  maxFontSize(value: number | string | Resource): this {
    return this;
  }

  onClick(callback: (event: ClickEvent, result: ButtonCallbackResult) => void): this {
    this.lazyComponent.onClick(callback);
    return this;
  }
}

class ButtonModifier extends LazyArkButtonComponent implements AttributeModifier<ButtonAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: ButtonAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<ButtonAttribute, ArkButtonComponent, ArkComponent>(instance, this);
  }
}

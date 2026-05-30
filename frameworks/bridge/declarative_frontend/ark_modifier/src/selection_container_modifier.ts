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

class LazyArkSelectionContainerComponent extends ArkComponent {
  static module: SelectionContainerComponentModule | undefined = undefined;
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkSelectionContainerComponent.module === undefined) {
      LazyArkSelectionContainerComponent.module =
        globalThis.requireNapi('arkui.components.selectioncontainer');
    }
    this.lazyComponent = LazyArkSelectionContainerComponent.module.createComponent(nativePtr, classType);
  }
  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  copyOption(value: CopyOptions): LazyArkSelectionContainerComponent {
    this.lazyComponent.copyOption(value);
    return this;
  }

  enableHapticFeedback(value: boolean): LazyArkSelectionContainerComponent {
    this.lazyComponent.enableHapticFeedback(value);
    return this;
  }

  textJoinStyle(value: SelectionContainerTextJoinStyle): LazyArkSelectionContainerComponent {
    this.lazyComponent.textJoinStyle(value);
    return this;
  }

  caretColor(value: ResourceColor): LazyArkSelectionContainerComponent {
    this.lazyComponent.caretColor(value);
    return this;
  }

  selectedBackgroundColor(value: ResourceColor): LazyArkSelectionContainerComponent {
    this.lazyComponent.selectedBackgroundColor(value);
    return this;
  }

  editMenuOptions(value: EditMenuOptions): LazyArkSelectionContainerComponent {
    this.lazyComponent.editMenuOptions(value);
    return this;
  }

  onWillCopy(callback: Callback<string, boolean>): LazyArkSelectionContainerComponent {
    this.lazyComponent.onWillCopy(callback);
    return this;
  }

  onCopy(callback: Callback<string>): LazyArkSelectionContainerComponent {
    this.lazyComponent.onCopy(callback);
    return this;
  }

  onTextSelectionChange(callback: Callback<Array<string>>): LazyArkSelectionContainerComponent {
    this.lazyComponent.onTextSelectionChange(callback);
    return this;
  }

  bindSelectionMenu(spanType: TextSpanType, content: CustomBuilder,
    responseType: TextResponseType, options?: SelectionContainerMenuOptions): LazyArkSelectionContainerComponent {
    this.lazyComponent.bindSelectionMenu(spanType, content, responseType, options);
    return this;
  }

  resetBindSelectionMenu(spanType: TextSpanType, responseType: TextResponseType): LazyArkSelectionContainerComponent {
    this.lazyComponent.resetBindSelectionMenu(spanType, responseType);
    return this;
  }
}

class SelectionContainerModifier extends LazyArkSelectionContainerComponent
  implements AttributeModifier<SelectionContainerAttribute> {

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: SelectionContainerAttribute): void {
    ModifierUtils.applySetOnChange(this);
    ModifierUtils.applyAndMergeModifier<SelectionContainerAttribute, ArkSelectionContainerComponent, ArkComponent>(
      instance, this);
  }
}

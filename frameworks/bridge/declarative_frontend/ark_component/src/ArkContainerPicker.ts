/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
class ArkContainerPickerComponent extends ArkComponent implements PickerAttribute {
    constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  onChange(callback: Optional<OnPickerCallback>): this {
    modifierWithKey(
      this._modifiersWithKeys, ContainerPickerOnChangeModifier.identity, ContainerPickerOnChangeModifier, callback);
    return this;
  }
  onScrollStop(callback: Optional<OnPickerCallback>) : this {
    modifierWithKey(
      this._modifiersWithKeys, ContainerPickerOnScrollStopModifier.identity, ContainerPickerOnScrollStopModifier, callback);
    return this;
  }
  canLoop(isLoop: Optional<boolean>): this {
    modifierWithKey(
      this._modifiersWithKeys, ContainerPickerCanLoopModifier.identity, ContainerPickerCanLoopModifier, isLoop);
    return this;
  }
  enableHapticFeedback(enable: Optional<boolean>): this {
    modifierWithKey(this._modifiersWithKeys, TextpickerEnableHapticFeedbackModifier.identity, TextpickerEnableHapticFeedbackModifier, enable);
    return this;
  }
  selectionIndicator(style: Optional<PickerIndicatorStyle>): this {
    modifierWithKey(this._modifiersWithKeys, ContainerPickerSelectionIndicatorModifier.identity, ContainerPickerSelectionIndicatorModifier, style);
    return this;
  }

}
class ContainerPickerOnChangeModifier extends ModifierWithKey<Optional<OnPickerCallback>> {
  constructor(value: Optional<OnPickerCallback>) {
    super(value);
  }
  static identity: Symbol = Symbol('containerPickerOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerOnChange(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerOnChange(node, this.value);
    }
  }
}


class ContainerPickerOnScrollStopModifier extends ModifierWithKey<Optional<OnPickerCallback>> {
  constructor(value: Optional<OnPickerCallback>) {
     super(value);
  }
  static identity: Symbol = Symbol('containerPickerOnScrollStop');
  applyPeer(node: KNode, reset: boolean): void {
  if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerOnScrollStop(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerOnScrollStop(node, this.value);
    }
  }
}

class ContainerPickerCanLoopModifier extends ModifierWithKey<Optional<boolean>> {
  constructor(value: Optional<boolean>) {
    super(value);
  }
  static identity: Symbol = Symbol('containerPickerCanLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerCanLoop(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerCanLoop(node, this.value);
    }
  }
}

class ContainerPickerEnableHapticFeedbackModifier extends ModifierWithKey<Optional<boolean>> {
  constructor(value: Optional<boolean>) {
    super(value);
  }
  static identity: Symbol = Symbol('containerPickerEnableHapticFeedback');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().containerPicker.resetContainerPickerEnableHapticFeedback(node);
    } else {
      getUINativeModule().containerPicker.setContainerPickerEnableHapticFeedback(node, this.value);
    }
  }
}

class ContainerPickerSelectionIndicatorModifier extends ModifierWithKey<Optional<PickerIndicatorStyle>> {
  constructor(value: Optional<PickerIndicatorStyle>) {
    super(value);
  }
  static identity: Symbol = Symbol('containerPickerSelectionIndicator');
  applyPeer(node: KNode, reset: boolean): void {
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
}
// @ts-ignore
globalThis.Picker.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkContainerPickerComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ContainerPickerModifier(nativePtr, classType);
  });
};

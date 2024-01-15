/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
class ArkProgressComponent extends ArkComponent implements ProgressAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  value(value: number): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions |
  ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions |
  CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressValueModifier.identity, ProgressValueModifier, value);
    return this;
  }
  color(value: ResourceColor | LinearGradient): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions |
  ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions |
  CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressColorModifier.identity, ProgressColorModifier, value);
    return this;
  }
  style(value: LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions |
  ScaleRingStyleOptions | CapsuleStyleOptions):
    ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions |
    RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressStyleModifier.identity, ProgressStyleModifier, value);
    return this;
  }
  backgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, ProgressBackgroundColorModifier.identity, ProgressBackgroundColorModifier, value);
    return this;
  }
}

class ProgressValueModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('value');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.ResetProgressValue(node);
    } else {
      getUINativeModule().progress.SetProgressValue(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ProgressColorModifier extends ModifierWithKey<ResourceColor | LinearGradient> {
  static identity: Symbol = Symbol('color');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.resetProgressColor(node);
    } else {
      getUINativeModule().progress.setProgressColor(node, this.value!);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue !== this.value;
  }
}

class ProgressStyleModifier extends ModifierWithKey<ProgressStyleOptions | CapsuleStyleOptions |
RingStyleOptions | LinearStyleOptions | ScaleRingStyleOptions | EclipseStyleOptions> {
  static identity: Symbol = Symbol('style');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.ResetProgressStyle(node);
    } else {
      let strokeWidth = (<ProgressStyleOptions> this.value).strokeWidth;
      let scaleCount = (<ProgressStyleOptions> this.value).scaleCount;
      let scaleWidth = (<ProgressStyleOptions> this.value).scaleWidth;
      let enableSmoothEffect = (<ProgressStyleOptions> this.value).enableSmoothEffect;
      let borderColor = (<CapsuleStyleOptions> this.value).borderColor;
      let borderWidth = (<CapsuleStyleOptions> this.value).borderWidth;
      let content = (<CapsuleStyleOptions> this.value).content;
      let fontSize;
      let fontWeight;
      let fontFamily;
      let fontStyle;
      if ((<CapsuleStyleOptions> this.value).font) {
        fontSize = (<CapsuleStyleOptions> this.value).font.size;
        fontWeight = (<CapsuleStyleOptions> this.value).font.weight;
        fontFamily = (<CapsuleStyleOptions> this.value).font.family;
        fontStyle = (<CapsuleStyleOptions> this.value).font.style;
      }
      let fontColor = (<CapsuleStyleOptions> this.value).fontColor;
      let enableScanEffect = (<CapsuleStyleOptions> this.value).enableScanEffect;
      let showDefaultPercentage = (<CapsuleStyleOptions> this.value).showDefaultPercentage;
      let shadow = (<RingStyleOptions> this.value).shadow;
      let status = (<RingStyleOptions> this.value).status;
      let strokeRadius = (<LinearStyleOptions> this.value).strokeRadius;
      getUINativeModule().progress.SetProgressStyle(
        node, strokeWidth, scaleCount, scaleWidth, enableSmoothEffect, borderColor,
        borderWidth, content, fontSize, fontWeight, fontFamily, fontStyle, fontColor,
        enableScanEffect, showDefaultPercentage, shadow, status, strokeRadius
      );
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ProgressBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  static identity: Symbol = Symbol('progressBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.resetProgressBackgroundColor(node);
    } else {
      getUINativeModule().progress.setProgressBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkProgressComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

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
  value(value: number): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressValueModifier.identity, ProgressValueModifier, value);
    return this;
  }
  color(value: ResourceColor | LinearGradient): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressColorModifier.identity, ProgressColorModifier, value);
    return this;
  }
  style(value: LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    modifierWithKey(this._modifiersWithKeys, ProgressStyleModifier.identity, ProgressStyleModifier, value);
    return this;
  }
  monopolizeEvents(monopolize: boolean): ProgressAttribute<keyof ProgressStyleMap, LinearStyleOptions | ProgressStyleOptions | RingStyleOptions | EclipseStyleOptions | ScaleRingStyleOptions | CapsuleStyleOptions> {
    throw new Error('Method not implemented.');
  }
}

class ProgressValueModifier extends ModifierWithKey<number> {
  static identity: Symbol = Symbol('value');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().progress.ResetProgressValue(node);
    } else {
      GetUINativeModule().progress.SetProgressValue(node, this.value!);
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
      GetUINativeModule().progress.ResetProgressColor(node);
    } else {
      const valueType: string = typeof this.value;
      if (valueType === "number" || valueType === "string" || isResource(this.value)) {
        GetUINativeModule().progress.SetProgressColor(node, this.value);
      } else {
        GetUINativeModule().progress.SetProgressColorWithLinearGradient(
          node,
          (this.value as LinearGradient).angle,
          (this.value as LinearGradient).direction,
          (this.value as LinearGradient).colors,
          (this.value as LinearGradient).repeating
        );
      }
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

class ProgressStyleModifier extends ModifierWithKey<ProgressStyleOptions | CapsuleStyleOptions |
  RingStyleOptions | LinearStyleOptions | ScaleRingStyleOptions | EclipseStyleOptions> {
  static identity: Symbol = Symbol('style');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().progress.ResetProgressStyle(node);
    } else {
      let valueProgressStyle = this.value as ProgressStyleOptions;
      let valueCapsuleStyle = this.value as CapsuleStyleOptions;
      let valueRingStyle = this.value as RingStyleOptions;
      let valueLinearStyle = this.value as LinearStyleOptions;
      let valueScaleRingStyle = this.value as ScaleRingStyleOptions;

      let strokeWidth = undefined;
      let scaleCount = undefined;
      let scaleWidth = undefined;
      let enableSmoothEffect = (this.value as CommonProgressStyleOptions).enableSmoothEffect;
      let enableScanEffect = undefined;
      let shadow = undefined;

      if (isUndefined(strokeWidth) && !isNull(valueProgressStyle.strokeWidth) &&
        !isUndefined(valueProgressStyle.strokeWidth)) {
        strokeWidth = valueProgressStyle.strokeWidth;
      }
      if (isUndefined(strokeWidth) && !isNull(valueRingStyle.strokeWidth) &&
        !isUndefined(valueRingStyle.strokeWidth)) {
        strokeWidth = valueRingStyle.strokeWidth;
      }
      if (isUndefined(strokeWidth) && !isNull(valueLinearStyle.strokeWidth) &&
        !isUndefined(valueLinearStyle.strokeWidth)) {
        strokeWidth = valueLinearStyle.strokeWidth;
      }
      if (isUndefined(strokeWidth) && !isNull(valueScaleRingStyle.strokeWidth) &&
        !isUndefined(valueScaleRingStyle.strokeWidth)) {
        strokeWidth = valueScaleRingStyle.strokeWidth;
      }
      if (isUndefined(strokeWidth) && !isNull(valueCapsuleStyle.borderWidth) &&
        !isUndefined(valueCapsuleStyle.borderWidth)) {
        strokeWidth = valueCapsuleStyle.borderWidth;
      }

      if (isUndefined(scaleCount) && !isNull(valueProgressStyle.scaleCount) &&
        !isUndefined(valueProgressStyle.scaleCount)) {
        scaleCount = valueProgressStyle.scaleCount;
      }
      if (isUndefined(scaleCount) && !isNull(valueRingStyle.status) &&
        !isUndefined(valueRingStyle.status)) {
        scaleCount = valueRingStyle.status;
      }
      if (isUndefined(scaleCount) && !isNull(valueScaleRingStyle.scaleCount) &&
        !isUndefined(valueScaleRingStyle.scaleCount)) {
        scaleCount = valueScaleRingStyle.scaleCount;
      }
      if (isUndefined(scaleCount) && !isNull(valueCapsuleStyle.font) &&
        !isUndefined(valueCapsuleStyle.font)) {
        scaleCount = valueCapsuleStyle.font?.style;
      }

      if (isUndefined(scaleWidth) && !isNull(valueProgressStyle.scaleWidth) &&
        !isUndefined(valueProgressStyle.scaleWidth)) {
        scaleWidth = valueProgressStyle.scaleWidth;
      }
      if (isUndefined(scaleWidth) && !isNull(valueScaleRingStyle.scaleWidth) &&
        !isUndefined(valueScaleRingStyle.scaleWidth)) {
        scaleWidth = valueScaleRingStyle.scaleWidth;
      }
      if (isUndefined(scaleWidth) && !isNull(valueCapsuleStyle.font) &&
        !isUndefined(valueCapsuleStyle.font)) {
        scaleWidth = valueCapsuleStyle.font?.size;
      }

      if (isUndefined(enableScanEffect) && !isNull(valueRingStyle.enableScanEffect) &&
        !isUndefined(valueRingStyle.enableScanEffect)) {
        enableScanEffect = valueRingStyle.enableScanEffect;
      }
      if (isUndefined(enableScanEffect) && !isNull(valueLinearStyle.enableScanEffect) &&
        !isUndefined(valueLinearStyle.enableScanEffect)) {
        enableScanEffect = valueLinearStyle.enableScanEffect;
      }
      if (isUndefined(enableScanEffect) && !isNull(valueCapsuleStyle.enableScanEffect) &&
        !isUndefined(valueCapsuleStyle.enableScanEffect)) {
        enableScanEffect = valueCapsuleStyle.enableScanEffect;
      }

      if (isUndefined(shadow) && !isNull(valueRingStyle.shadow) && !isUndefined(valueRingStyle.shadow)) {
        shadow = valueRingStyle.shadow;
      }
      if (isUndefined(shadow) && !isNull(valueCapsuleStyle.showDefaultPercentage) &&
        !isUndefined(valueCapsuleStyle.showDefaultPercentage)) {
        shadow = valueCapsuleStyle.showDefaultPercentage;
      }

      GetUINativeModule().progress.SetProgressStyle(
        node,
        strokeWidth,
        scaleCount,
        scaleWidth,
        enableSmoothEffect,
        valueCapsuleStyle.borderColor,
        valueCapsuleStyle.content,
        valueCapsuleStyle.font?.weight,
        valueCapsuleStyle.fontColor,
        enableScanEffect,
        shadow,
        valueCapsuleStyle.font?.family,
        valueLinearStyle.strokeRadius
      );
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}

// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkProgressComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

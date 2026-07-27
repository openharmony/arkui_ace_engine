/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
interface ProgressParam {
  value: number;
  total?: number;
  style?: ProgressStyle
  type?: Type
}
class ArkProgressComponent extends ArkComponent implements ProgressAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  builder: WrappedBuilder<Object[]> | null = null;
  modifier: ContentModifier<ProgressConfiguration> | null = null;
  progressNode: BuilderNode<[ProgressConfiguration]> | null = null;
  initialize(value: Object[]): ProgressAttribute {
    if (value[0] !== undefined) {
      modifierWithKey(this._modifiersWithKeys, ProgressInitializeModifier.identity,
        ProgressInitializeModifier, (value[0] as ProgressParam));
    }
    return this;
  }
  allowChildCount(): number {
    return 0;
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
  contentModifier(value: ContentModifier<ProgressConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, ProgressContentModifier.identity, ProgressContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<ProgressConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().progress.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().progress.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, progressConfig: ProgressConfiguration): FrameNode | null {
    progressConfig.contentModifier = this.modifier;
    if (isUndefined(this.progressNode)) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.progressNode = new xNode.BuilderNode(context);
      this.progressNode.build(this.builder, progressConfig);
    } else {
      this.progressNode.update(progressConfig);
    }
    return this.progressNode.getFrameNode();
  }
  privacySensitive(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, ProgressPrivacySensitiveModifier.identity, ProgressPrivacySensitiveModifier, value);
    return this;
  }
}

class ProgressPrivacySensitiveModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('progressPrivacySensitive');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.resetProgressPrivacySensitive(node);
    } else {
      getUINativeModule().progress.setProgressPrivacySensitive(node, this.value);
    }
  }
}

class ProgressInitializeModifier extends ModifierWithKey<ProgressParam> {
  constructor(value: ProgressParam) {
    super(value);
  }
  static identity: Symbol = Symbol('progressInitialize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().progress.resetProgressInitialize(node);
    } else {
      getUINativeModule().progress.setProgressInitialize(node, this.value.value,
        this.value.total, this.value.style, this.value.type);
    }
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
      let borderRadius = (<CapsuleStyleOptions> this.value).borderRadius;
      getUINativeModule().progress.SetProgressStyle(
        node, strokeWidth, scaleCount, scaleWidth, enableSmoothEffect, borderColor,
        borderWidth, content, fontSize, fontWeight, fontFamily, fontStyle, fontColor,
        enableScanEffect, showDefaultPercentage, shadow, status, strokeRadius, borderRadius
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

class ProgressContentModifier extends ModifierWithKey<ContentModifier<ProgressConfiguration>> {
  constructor(value: ContentModifier<ProgressConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('progressContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent) {
    let progressComponent = component as ArkProgressComponent;
    progressComponent.setContentModifier(this.value);
  }
}

// @ts-ignore
globalThis.Progress.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkProgressComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.ProgressModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Progress.contentModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkProgressComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};
/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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

class RatingStarsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStars');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rating.resetStars(node);
    } else {
      getUINativeModule().rating.setStars(node, this.value);
    }
  }
}

class RatingStepSizeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStepSize');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rating.resetStepSize(node);
    } else {
      getUINativeModule().rating.setStepSize(node, this.value);
    }
  }
}

class RatingStarStyleModifier extends ModifierWithKey<ArkStarStyle> {
  constructor(value: ArkStarStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStarStyle');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rating.resetStarStyle(node);
    } else {
      getUINativeModule().rating.setStarStyle(node,
        this.value?.backgroundUri, this.value?.foregroundUri, this.value?.secondaryUri);
    }
  }

  checkObjectDiff(): boolean {
    return this.stageValue?.backgroundUri !== this.value?.backgroundUri ||
      this.stageValue?.foregroundUri !== this.value?.foregroundUri || this.stageValue?.secondaryUri !== this.value?.secondaryUri;
  }
}
class RatingOnChangeModifier extends ModifierWithKey<(value: number) => void> {
  constructor(value: (value: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingOnChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().rating.resetOnChange(node);
    } else {
      getUINativeModule().rating.setOnChange(node, this.value);
    }
  }
}
class RatingContentModifier extends ModifierWithKey<ContentModifier<RatingConfiguration>> {
  constructor(value: ContentModifier<RatingConfiguration>) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingContentModifier');
  applyPeer(node: KNode, reset: boolean, component: ArkComponent): void {
    let ratingComponent = component as ArkRatingComponent;
    ratingComponent.setContentModifier(this.value);
  }
}

class ArkRatingComponent extends ArkComponent implements RatingAttribute {
  builder: WrappedBuilder<Object[]> | null = null;
  ratingNode: BuilderNode<[RatingConfiguration]> | null = null;
  modifier: ContentModifier<RatingConfiguration>;
  needRebuild: boolean = false;
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  allowChildCount(): number {
    return 0;
  }
  initialize(value: Object[]): this {
    if (!value.length) {
      return this;
    }
    if (!isUndefined(value[0]) && !isNull(value[0]) && isObject(value[0])) {
      modifierWithKey(this._modifiersWithKeys, RatingOptionsModifier.identity, RatingOptionsModifier, value[0]);
    } else {
      modifierWithKey(this._modifiersWithKeys, RatingOptionsModifier.identity, RatingOptionsModifier, undefined);
    }
    return this;
  }
  stars(value: number): this {
    modifierWithKey(this._modifiersWithKeys, RatingStarsModifier.identity, RatingStarsModifier, value);
    return this;
  }
  stepSize(value: number): this {
    modifierWithKey(this._modifiersWithKeys, RatingStepSizeModifier.identity, RatingStepSizeModifier, value);
    return this;
  }
  starStyle(value: { backgroundUri: string; foregroundUri: string; secondaryUri?: string | undefined; }): this {
    let starStyle = new ArkStarStyle();
    if (!isUndefined(value)) {
      starStyle.backgroundUri = value.backgroundUri;
      starStyle.foregroundUri = value.foregroundUri;
      starStyle.secondaryUri = value.secondaryUri;

      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, value);
    } else {
      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, undefined);
    }
    return this;
  }
  onChange(callback: (value: number) => void): this {
    modifierWithKey(this._modifiersWithKeys, RatingOnChangeModifier.identity, RatingOnChangeModifier, callback);
    return this;
  }
  contentModifier(value: ContentModifier<RatingConfiguration>): this {
    modifierWithKey(this._modifiersWithKeys, RatingContentModifier.identity, RatingContentModifier, value);
    return this;
  }
  setContentModifier(modifier: ContentModifier<RatingConfiguration>): this {
    if (modifier === undefined || modifier === null) {
      getUINativeModule().rating.setContentModifierBuilder(this.nativePtr, false);
      return;
    }
    this.needRebuild = false;
    if (this.builder !== modifier.applyContent()) {
      this.needRebuild = true;
    }
    this.builder = modifier.applyContent();
    this.modifier = modifier;
    getUINativeModule().rating.setContentModifierBuilder(this.nativePtr, this);
  }
  makeContentModifierNode(context: UIContext, ratingConfiguration: RatingConfiguration): FrameNode | null {
    ratingConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.ratingNode || this.needRebuild)) {
      const xNode = globalThis.requireNapi('arkui.node');
      this.ratingNode = new xNode.BuilderNode(context);
      this.ratingNode.build(this.builder, ratingConfiguration);
      this.needRebuild = false;
    } else {
      this.ratingNode.update(ratingConfiguration);
    }
    return this.ratingNode.getFrameNode();
  }
}

class RatingOptionsModifier extends ModifierWithKey<object> {
  constructor(value: object) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingOptions');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().radio.setRatingOptions(node, undefined, undefined);
    } else {
      getUINativeModule().radio.setRatingOptions(node, this.value?.rating, this.value?.indicator);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue?.rating, this.value?.rating) ||
      !isBaseOrResourceEqual(this.stageValue?.indicator, this.value?.indicator);
  }
}

// @ts-ignore
globalThis.Rating.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkRatingComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.RatingModifier(nativePtr, classType);
  });
};

// @ts-ignore
globalThis.Rating.contentModifier = function (modifier): void {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRatingComponent(nativeNode);
  });
  component.setContentModifier(modifier);
};

globalThis.Rating.onChange = function (value: (selected: boolean) => void): void {
  let nodePtr = getUINativeModule().frameNode.getStackTopNode();
  getUINativeModule().rating.setOnChange(nodePtr, value);
};

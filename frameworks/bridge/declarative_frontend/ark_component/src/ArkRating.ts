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

class RatingStarsModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStars');
  applyPeer(node: KNode, reset: boolean) {
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
  applyPeer(node: KNode, reset: boolean) {
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
  applyPeer(node: KNode, reset: boolean) {
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

class ArkRatingComponent extends ArkComponent implements RatingAttribute {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  onGestureJudgeBegin(callback: (gestureInfo: GestureInfo, event: BaseGestureEvent) => GestureJudgeResult): this {
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }
}
// @ts-ignore
globalThis.Rating.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRatingComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};

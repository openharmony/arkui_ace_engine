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

class RatingStarsModifier extends Modifier<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStars');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().rating.resetStars(node);
    }
    else {
      GetUINativeModule().rating.setStars(node, this.value);
    }
  }
}

class RatingStepSizeModifier extends Modifier<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStepSize');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().rating.resetStepSize(node);
    }
    else {
      GetUINativeModule().rating.setStepSize(node, this.value);
    }
  }
}

class RatingStarStyleModifier extends Modifier<ArkStarStyle> {
  constructor(value: ArkStarStyle) {
    super(value);
  }
  static identity: Symbol = Symbol('ratingStarStyle');
  applyPeer(node: KNode, reset: boolean) {
    if (reset) {
      GetUINativeModule().rating.resetStarStyle(node);
    }
    else {
      GetUINativeModule().rating.setStarStyle(node,
        this.value?.backgroundUri, this.value?.foregroundUri, this.value?.secondaryUri);
    }
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
    if (!isUndefined(value)) {
      modifier(this._modifiers, RatingStarsModifier, value);
    } else {
      modifier(this._modifiers, RatingStarsModifier, undefined);
    }
    return this;
  }
  stepSize(value: number): this {
    if (isNumber(value)) {
      modifier(this._modifiers, RatingStepSizeModifier, value);
    } else {
      modifier(this._modifiers, RatingStepSizeModifier, undefined);
    }
    return this;
  }
  starStyle(value: { backgroundUri: string; foregroundUri: string; secondaryUri?: string | undefined; }): this {
    let starStyle = new ArkStarStyle();
    if (!isUndefined(value)) {
      starStyle.backgroundUri = value.backgroundUri;
      starStyle.foregroundUri = value.foregroundUri;
      starStyle.secondaryUri = value.secondaryUri;

      modifier(this._modifiers, RatingStarStyleModifier, starStyle);
    } else {
      modifier(this._modifiers, RatingStarStyleModifier, undefined);
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
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);
  let component = this.createOrGetNode(elmtId, () => {
    return new ArkRatingComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
}

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
/// <reference path='./import.ts' />
class RatingStarsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.resetStars(node);
    }
    else {
      getUINativeModule().rating.setStars(node, this.value);
    }
  }
}
RatingStarsModifier.identity = Symbol('ratingStars');
class RatingStepSizeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.resetStepSize(node);
    }
    else {
      getUINativeModule().rating.setStepSize(node, this.value);
    }
  }
}
RatingStepSizeModifier.identity = Symbol('ratingStepSize');
class RatingStarStyleModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
      let _a;
      let _b;
      let _c;
    if (reset) {
      getUINativeModule().rating.resetStarStyle(node);
    }
    else {
      getUINativeModule().rating.setStarStyle(node, (_a = this.value) === null ||
      _a === void 0 ? void 0 : _a.backgroundUri, (_b = this.value) === null ||
      _b === void 0 ? void 0 : _b.foregroundUri, (_c = this.value) === null ||
      _c === void 0 ? void 0 : _c.secondaryUri);
    }
  }
  checkObjectDiff() {
    let _a;
    let _b;
    let _c;
    let _d;
    let _e;
    let _f;
    return ((_a = this.stageValue) === null || _a === void 0 ? void 0 : _a.backgroundUri) !==
      ((_b = this.value) === null || _b === void 0 ? void 0 : _b.backgroundUri) ||
      ((_c = this.stageValue) === null || _c === void 0 ? void 0 : _c.foregroundUri) !==
      ((_d = this.value) === null || _d === void 0 ? void 0 : _d.foregroundUri) ||
      ((_e = this.stageValue) === null || _e === void 0 ? void 0 : _e.secondaryUri) !==
      ((_f = this.value) === null || _f === void 0 ? void 0 : _f.secondaryUri);
  }
}
RatingStarStyleModifier.identity = Symbol('ratingStarStyle');
class RatingContentModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset, component) {
    let ratingComponent = component;
    ratingComponent.setContentModifier(this.value);
  }
}
RatingStarStyleModifier.identity = Symbol('ratingContentModifier');
class RatingOnChangeModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.resetOnChange(node);
    } else {
      getUINativeModule().rating.setOnChange(node, this.value);
    }
  }
}
RatingOnChangeModifier.identity = Symbol('ratingOnChangeModifier');
class ArkRatingComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  allowChildCount() {
    return 0;
  }
  initialize(value) {
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
  stars(value) {
    modifierWithKey(this._modifiersWithKeys, RatingStarsModifier.identity, RatingStarsModifier, value);
    return this;
  }
  stepSize(value) {
    modifierWithKey(this._modifiersWithKeys, RatingStepSizeModifier.identity, RatingStepSizeModifier, value);
    return this;
  }
  starStyle(value) {
    let starStyle = new ArkStarStyle();
    if (!isUndefined(value) && !isNull(value) && isObject(value)) {
      starStyle.backgroundUri = value.backgroundUri;
      starStyle.foregroundUri = value.foregroundUri;
      starStyle.secondaryUri = value.secondaryUri;
      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, value);
    }
    else {
      modifierWithKey(this._modifiersWithKeys, RatingStarStyleModifier.identity, RatingStarStyleModifier, undefined);
    }
    return this;
  }
  onChange(callback) {
    modifierWithKey(this._modifiersWithKeys, RatingOnChangeModifier.identity, RatingOnChangeModifier, callback);
    return this;
  }
  contentModifier(value) {
    modifierWithKey(this._modifiersWithKeys, RatingContentModifier.identity, RatingContentModifier, value);
    return this;
  }
  setContentModifier(modifier) {
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
  makeContentModifierNode(context, ratingConfiguration) {
    ratingConfiguration.contentModifier = this.modifier;
    if (isUndefined(this.ratingNode) || this.needRebuild) {
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
class RatingOptionsModifier extends ModifierWithKey {
  constructor(value) {
    super(value);
  }
  applyPeer(node, reset) {
    if (reset) {
      getUINativeModule().rating.setRatingOptions(node, undefined, undefined);
    } else {
      getUINativeModule().rating.setRatingOptions(node, this.value?.rating, this.value?.indicator);
    }
  }

  checkObjectDiff() {
    return !isBaseOrResourceEqual(this.stageValue?.rating, this.value?.rating) ||
      !isBaseOrResourceEqual(this.stageValue?.indicator, this.value?.indicator);
  }
}
RatingOptionsModifier.identity = Symbol( 'ratingOptions' );

class JSRating extends JSViewAbstract {
    static create(params) {
      if (params !== undefined && params !== null) {
        getUINativeModule().rating.create(true, params);
      } else {
        getUINativeModule().rating.create(0, false);
      }
    }

    static stars(stars) {
      getUINativeModule().rating.setStars(true, stars);
    }

    static stepSize(stepSize) {
      getUINativeModule().rating.setStepSize(true, stepSize);
    }

    static starStyle(starStyle) {
      getUINativeModule().rating.setStarStyle(true, starStyle);
    }
    
    static onChange(value) {
      getUINativeModule().rating.setOnChange(true, value);
    }
    
    static attributeModifier(modifier) {
        attributeModifierFunc.call(this, modifier, (nativePtr) => {
            return new ArkRatingComponent(nativePtr);
        }, (nativePtr, classType, modifierJS) => {
            return new modifierJS.RatingModifier(nativePtr, classType);
        });
    }

    static contentModifier(modifier) {
        const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
        let nativeNode = getUINativeModule().getFrameNodeById(elmtId);
        let component = this.createOrGetNode(elmtId, () => {
            return createComponent(nativeNode, 'rating');
        });
        component.setContentModifier(modifier);
    }

    static onClick(value) {
        __Common__.onClick(value);
    }
    static onKeyEvent(value) {
        __Common__.onKeyEvent(value);
    }
    static onDeleteEvent(value) {
        __Common__.onDeleteEvent(value);
    }
    static onAttach(value) {
        __Common__.onAttach(value);
    }
    static onAppear(value) {
        __Common__.onAppear(value);
    }
    static onDetach(value) {
        __Common__.onDetach(value);
    }
    static onDisAppear(value) {
        __Common__.onDisAppear(value);
    }
    static onTouch(value) {
        __Common__.onTouch(value);
    }
    static onHover(value) {
        __Common__.onHover(value);
    }
}

function createComponent(nativePtr, classType) {
    return new ArkRatingComponent(nativePtr, classType);
}

function exportComponent() {
    globalThis.ArkRatingComponent = ArkRatingComponent;
}

function exportView() {
    globalThis.Rating = JSRating;
}

export default { ArkRatingComponent, createComponent, exportComponent, exportView };
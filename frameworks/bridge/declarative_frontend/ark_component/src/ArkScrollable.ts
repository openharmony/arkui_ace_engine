/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

class ClipContentModifier extends ModifierWithKey<ContentClipMode | RectShape> {
    constructor(value: ContentClipMode | RectShape) {
        super(value);
    }
    static identity: Symbol = Symbol('clipContent');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            getUINativeModule().scrollable.resetContentClip(node);
        } else {
            getUINativeModule().scrollable.setContentClip(node, this.value);
        }
    }
}

class EdgeEffectModifier extends ModifierWithKey<ArkEdgeEffect> {
  constructor(value: ArkEdgeEffect) {
    super(value);
  }
  static identity: Symbol = Symbol('edgeEffect');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().scrollable.resetEdgeEffect(node);
    } else {
      getUINativeModule().scrollable.setEdgeEffect(node, this.value?.value, this.value.options?.alwaysEnabled,
        this.value.options?.effectEdge);
    }
  }

  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class ScrollableFadingEdgeModifier extends ModifierWithKey<ArkFadingEdge> {
  constructor(value: ArkFadingEdge) {
    super(value);
  }
  static identity: Symbol = Symbol('scrollableFadingEdge');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().scrollable.resetFadingEdge(node);
    } else {
      getUINativeModule().scrollable.setFadingEdge(node, this.value.value!, this.value.options?.fadingEdgeLength);
    }
  }
  checkObjectDiff(): boolean {
    return !((this.stageValue.value === this.value.value) &&
      (this.stageValue.options === this.value.options));
  }
}

class OnReachStartModifier extends ModifierWithKey<() => void> {
    constructor(value: () => void) {
        super(value);
    }
    static identity: Symbol = Symbol('onReachStart');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            getUINativeModule().scrollable.resetOnReachStart(node);
        } else {
            getUINativeModule().scrollable.setOnReachStart(node, this.value);
        }
    }
}

class BackToTopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('backToTop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().scrollable.resetBackToTop(node);
    } else {
      getUINativeModule().scrollable.setBackToTop(node, this.value);
    }
  }
}

class ScrollBarMarginModifier extends ModifierWithKey<ScrollBarMargin> {
  constructor(value: ScrollBarMargin) {
    super(value);
  }
  static identity: Symbol = Symbol('scrollBarMargin');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().scrollable.resetScrollBarMargin(node);
    } else {
      getUINativeModule().scrollable.setScrollBarMargin(node, this.value.start, this.value.end);
    }
  }
}

class onWillStopDraggingModifier extends ModifierWithKey<(velocity: number) => void> {
  constructor(value: (velocity: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('onWillStopDragging');
  applyPeer(node: KNode, reset: boolean): void { 
    if (reset) {
      getUINativeModule().scrollable.resetOnWillStopDragging(node);
    } else {
      getUINativeModule().scrollable.setOnWillStopDragging(node, this.value);
    }
  }
}

class OnReachEndModifier extends ModifierWithKey<() => void> {
    constructor(value: () => void) {
        super(value);
    }
    static identity: Symbol = Symbol('onReachEnd');
    applyPeer(node: KNode, reset: boolean): void {
        if (reset) {
            getUINativeModule().scrollable.resetOnReachEnd(node);
        } else {
            getUINativeModule().scrollable.setOnReachEnd(node, this.value);
        }
    }
}

/**
 * base class of Grid, Scroll, List, and WaterFlow.
 */
export class ArkScrollable<T> extends ArkComponent implements ScrollableCommonMethod<T> {
    constructor(nativePtr: KNode, classType?: ModifierType) {
      super(nativePtr, classType);
    }
    clipContent(clip: ContentClipMode | RectShape): T {
        modifierWithKey(this._modifiersWithKeys, ClipContentModifier.identity, ClipContentModifier, clip);
        return this;
    }
    edgeEffect(value: EdgeEffect, options?: EdgeEffectOptions | undefined): T {
      let effect: ArkEdgeEffect = new ArkEdgeEffect();
      effect.value = value;
      effect.options = options;
      modifierWithKey(this._modifiersWithKeys, EdgeEffectModifier.identity, EdgeEffectModifier, effect);
      return this;
    }
    fadingEdge(value: boolean, options?: FadingEdgeOptions | undefined): T {
      let fadingEdge: ArkFadingEdge = new ArkFadingEdge();
      fadingEdge.value = value;
      fadingEdge.options = options;
      modifierWithKey(this._modifiersWithKeys, ScrollableFadingEdgeModifier.identity, ScrollableFadingEdgeModifier, fadingEdge);
      return this;
    }
    onReachStart(event: () => void): this {
        modifierWithKey(this._modifiersWithKeys, OnReachStartModifier.identity, OnReachStartModifier, event);
        return this;
    }

    onReachEnd(event: () => void): this {
        modifierWithKey(this._modifiersWithKeys, OnReachEndModifier.identity, OnReachEndModifier, event);
        return this;
    }
    backToTop(value: boolean): this {
      modifierWithKey(this._modifiersWithKeys, BackToTopModifier.identity, BackToTopModifier, value);
      return this;
    }
    scrollBarMargin(margin: ScrollBarMargin): T {
      modifierWithKey(this._modifiersWithKeys, ScrollBarMarginModifier.identity, ScrollBarMarginModifier, margin);
      return this;
    }
    onWillStopDragging(callback: (velocity: number) => void) : this {
      modifierWithKey(this._modifiersWithKeys, OnWillStopDraggingModifier.identity, OnWillStopDraggingModifier, callback);
      return this;
    }
}
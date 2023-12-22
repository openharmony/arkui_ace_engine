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

/// <reference path="./import.ts" />

class VideoObjectFitModifier extends ModifierWithKey<ImageFit> {
  constructor(value: ImageFit) {
    super(value);
  }
  static identity: Symbol = Symbol('videoObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetObjectFit(node);
    } else {
      GetUINativeModule().video.setObjectFit(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoAutoPlayModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoAutoPlayr');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetAutoPlay(node);
    } else {
      GetUINativeModule().video.setAutoPlay(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoControlsModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoControls');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetControls(node);
    } else {
      GetUINativeModule().video.setControls(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoLoopModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoLoop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetLoop(node);
    } else {
      GetUINativeModule().video.setLoop(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoMutedModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoMuted');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      GetUINativeModule().video.resetMuted(node);
    } else {
      GetUINativeModule().video.setMuted(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
  constructor(nativePtr: KNode) {
    super(nativePtr);
  }
  muted(value: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoMutedModifier.identity,
      VideoMutedModifier, value);
    return this;
  }
  autoPlay(value: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoAutoPlayModifier.identity,
      VideoAutoPlayModifier, value);
    return this;
  }
  controls(value: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoControlsModifier.identity,
      VideoControlsModifier, value);
    return this;
  }
  loop(value: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoLoopModifier.identity,
      VideoLoopModifier, value);
    return this;
  }
  objectFit(value: ImageFit): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoObjectFitModifier.identity,
      VideoObjectFitModifier, value);
    return this;
  }
  onStart(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onPause(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onFinish(event: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onFullscreenChange(callback: (event: { fullscreen: boolean }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onPrepared(callback: (event: { duration: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onSeeking(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onSeeked(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onUpdate(callback: (event: { time: number }) => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  onError(callback: () => void): VideoAttribute {
    throw new Error('Method not implemented.');
  }
  monopolizeEvents(monopolize: boolean): this {
    throw new Error("Method not implemented.");
  }
}
// @ts-ignore
globalThis.Video.attributeModifier = function (modifier) {
  const elmtId = ViewStackProcessor.GetElmtIdToAccountFor();
  let nativeNode = GetUINativeModule().getFrameNodeById(elmtId);

  let component = this.createOrGetNode(elmtId, () => {
    return new ArkVideoComponent(nativeNode);
  });
  applyUIAttributes(modifier, nativeNode, component);
  component.applyModifierPatch();
};
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

class VideoObjectFitModifier extends ModifierWithKey<ImageFit> {
  constructor(value: ImageFit) {
    super(value);
  }
  static identity: Symbol = Symbol('videoObjectFit');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetObjectFit(node);
    } else {
      getUINativeModule().video.setObjectFit(node, this.value!);
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
      getUINativeModule().video.resetAutoPlay(node);
    } else {
      getUINativeModule().video.setAutoPlay(node, this.value!);
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
      getUINativeModule().video.resetControls(node);
    } else {
      getUINativeModule().video.setControls(node, this.value!);
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
      getUINativeModule().video.resetLoop(node);
    } else {
      getUINativeModule().video.setLoop(node, this.value!);
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
      getUINativeModule().video.resetMuted(node);
    } else {
      getUINativeModule().video.setMuted(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoOpacityModifier extends ModifierWithKey<number | Resource> {
  constructor(value: number | Resource) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOpacity');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetOpacity(node);
    } else {
      getUINativeModule().video.setOpacity(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoSurfaceBackgroundColorModifier extends ModifierWithKey<ResourceColor> {
  constructor(value: ResourceColor) {
    super(value);
  }
  static identity: Symbol = Symbol('videoSurfaceBackgroundColor');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoSurfaceBackgroundColor(node);
    } else {
      getUINativeModule().video.setVideoSurfaceBackgroundColor(node, this.value);
    }
  }

  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}
class VideoTransitionModifier extends ModifierWithKey<ArkTransition> {
  constructor(value: ArkTransition) {
    super(value);
  }
  static identity: Symbol = Symbol('videoTransition');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetTransition(node);
    } else {
      getUINativeModule().video.setTransition(node, this.value.transitionEffect, this.value.callback);
    }
  }
  checkObjectDiff(): boolean {
    return true;
  }
}
class VideoEnableShortcutKeyModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoEnableShortcutKey');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetShortcutKeyEnabled(node);
    } else {
      getUINativeModule().video.setShortcutKeyEnabled(node, this.value!);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class VideoOnStartModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnStart');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnStart(node);
    } else {
      getUINativeModule().video.setVideoOnStart(node, this.value);
    }
  }
}

class VideoOnPauseModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnPause');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnPause(node);
    } else {
      getUINativeModule().video.setVideoOnPause(node, this.value);
    }
  }
}

class VideoOnFinishModifier extends ModifierWithKey<VoidCallback> {
  constructor(value: VoidCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnFinish');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnFinish(node);
    } else {
      getUINativeModule().video.setVideoOnFinish(node, this.value);
    }
  }
}

class VideoOnFullscreenChangeModifier extends ModifierWithKey<Callback<FullscreenInfo>> {
  constructor(value: Callback<FullscreenInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnFullscreenChange');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnFullscreenChange(node);
    } else {
      getUINativeModule().video.setVideoOnFullscreenChange(node, this.value);
    }
  }
}

class VideoOnPreparedModifier extends ModifierWithKey<Callback<PreparedInfo>> {
  constructor(value: Callback<PreparedInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnPrepared');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnPrepared(node);
    } else {
      getUINativeModule().video.setVideoOnPrepared(node, this.value);
    }
  }
}

class VideoOnSeekingModifier extends ModifierWithKey<Callback<PlaybackInfo>> {
  constructor(value: Callback<PlaybackInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnSeeking');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnSeeking(node);
    } else {
      getUINativeModule().video.setVideoOnSeeking(node, this.value);
    }
  }
}

class VideoOnSeekedModifier extends ModifierWithKey<Callback<PlaybackInfo>> {
  constructor(value: Callback<PlaybackInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnSeeked');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnSeeked(node);
    } else {
      getUINativeModule().video.setVideoOnSeeked(node, this.value);
    }
  }
}

class VideoOnUpdateModifier extends ModifierWithKey<Callback<PlaybackInfo>> {
  constructor(value: Callback<PlaybackInfo>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnUpdate');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnUpdate(node);
    } else {
      getUINativeModule().video.setVideoOnUpdate(node, this.value);
    }
  }
}

class VideoOnErrorModifier extends ModifierWithKey<VoidCallback | ErrorCallback> {
  constructor(value: VoidCallback | ErrorCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnError');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnError(node);
    } else {
      getUINativeModule().video.setVideoOnError(node, this.value);
    }
  }
}

class VideoOnStopModifier extends ModifierWithKey<Callback<void>> {
  constructor(value: Callback<void>) {
    super(value);
  }
  static identity: Symbol = Symbol('videoOnStop');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoOnStop(node);
    } else {
      getUINativeModule().video.setVideoOnStop(node, this.value);
    }
  }
}

class VideoEnableAnalyzerModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('videoEnableAnalyzer');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoEnableAnalyzer(node);
    } else {
      getUINativeModule().video.setVideoEnableAnalyzer(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class VideoAnalyzerConfigModifier extends ModifierWithKey<ImageAnalyzerConfig> {
  constructor(value: ImageAnalyzerConfig) {
    super(value);
  }
  static identity: Symbol = Symbol('videoAnalyzerConfig');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().video.resetVideoAnalyzerConfig(node);
    } else {
      getUINativeModule().video.setVideoAnalyzerConfig(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkVideoComponent extends ArkComponent implements CommonMethod<VideoAttribute> {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
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
  surfaceBackgroundColor(value: ResourceColor): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoSurfaceBackgroundColorModifier.identity,
      VideoSurfaceBackgroundColorModifier, value);
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
  enableShortcutKey(value: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoEnableShortcutKeyModifier.identity,
      VideoEnableShortcutKeyModifier, value);
    return this;
  }
  transition(value: TransitionOptions | TransitionEffect, callback: (transitionIn: boolean) => void): this {
    let arkTransition = new ArkTransition();
    arkTransition.transitionEffect = value;
    if (typeof callback === 'function') {
      arkTransition.callback = callback;
    }
    modifierWithKey(this._modifiersWithKeys, VideoTransitionModifier.identity, VideoTransitionModifier, arkTransition);
    return this;
  }
  onStart(event: VoidCallback): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnStartModifier.identity,
      VideoOnStartModifier, event);
    return this;
  }
  onPause(event: VoidCallback): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnPauseModifier.identity,
      VideoOnPauseModifier, event);
    return this;
  }
  onFinish(event: VoidCallback): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnFinishModifier.identity,
      VideoOnFinishModifier, event);
    return this;
  }
  onFullscreenChange(callback: Callback<FullscreenInfo>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnFullscreenChangeModifier.identity,
      VideoOnFullscreenChangeModifier, callback);
    return this;
  }
  onPrepared(callback: (callback: Callback<PreparedInfo>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnPreparedModifier.identity,
      VideoOnPreparedModifier, callback);
    return this;
  }
  onSeeking(callback: Callback<PlaybackInfo>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekingModifier.identity,
      VideoOnSeekingModifier, callback);
    return this;
  }
  onSeeked(callback: Callback<PlaybackInfo>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekedModifier.identity,
      VideoOnSeekedModifier, callback);
    return this;
  }
  onUpdate(callback: Callback<PlaybackInfo>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnUpdateModifier.identity,
      VideoOnUpdateModifier, callback);
    return this;
  }
  onError(event: VoidCallback | ErrorCallback): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnErrorModifier.identity,
      VideoOnErrorModifier, event);
    return this;
  }
  onStop(event: Callback<void>): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoOnStopModifier.identity,
      VideoOnStopModifier, event);
    return this;
  }
  enableAnalyzer(enable: boolean): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoEnableAnalyzerModifier.identity,
      VideoEnableAnalyzerModifier, enable);
    return this;
  }
  analyzerConfig(config: ImageAnalyzerConfig): VideoAttribute {
    modifierWithKey(this._modifiersWithKeys, VideoAnalyzerConfigModifier.identity,
      VideoAnalyzerConfigModifier, config);
    return this;
  }
}
// @ts-ignore
globalThis.Video.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkVideoComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.VideoModifier(nativePtr, classType);
  });
};

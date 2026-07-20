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
      getUINativeModule().video.resetOnStart(node);
    } else {
      getUINativeModule().video.setOnStart(node, this.value);
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
      getUINativeModule().video.resetOnPause(node);
    } else {
      getUINativeModule().video.setOnPause(node, this.value);
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
      getUINativeModule().video.resetOnFinish(node);
    } else {
      getUINativeModule().video.setOnFinish(node, this.value);
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
      getUINativeModule().video.resetOnFullscreenChange(node);
    } else {
      getUINativeModule().video.setOnFullscreenChange(node, this.value);
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
      getUINativeModule().video.resetOnPrepared(node);
    } else {
      getUINativeModule().video.setOnPrepared(node, this.value);
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
      getUINativeModule().video.resetOnSeeking(node);
    } else {
      getUINativeModule().video.setOnSeeking(node, this.value);
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
      getUINativeModule().video.resetOnSeeked(node);
    } else {
      getUINativeModule().video.setOnSeeked(node, this.value);
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
      getUINativeModule().video.resetOnUpdate(node);
    } else {
      getUINativeModule().video.setOnUpdate(node, this.value);
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
      getUINativeModule().video.resetOnError(node);
    } else {
      getUINativeModule().video.setOnError(node, this.value);
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
      getUINativeModule().video.resetOnStop(node);
    } else {
      getUINativeModule().video.setOnStop(node, this.value);
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
      getUINativeModule().video.resetEnableAnalyzer(node);
    } else {
      getUINativeModule().video.setEnableAnalyzer(node, this.value);
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
      getUINativeModule().video.resetAnalyzerConfig(node);
    } else {
      getUINativeModule().video.setAnalyzerConfig(node, this.value);
    }
  }
  checkObjectDiff(): boolean {
    return !isBaseOrResourceEqual(this.stageValue, this.value);
  }
}

class ArkVideoComponent extends ArkComponent {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  muted(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoMutedModifier.identity,
      VideoMutedModifier, value);
    return this;
  }
  autoPlay(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoAutoPlayModifier.identity,
      VideoAutoPlayModifier, value);
    return this;
  }
  surfaceBackgroundColor(value: ResourceColor): this {
    modifierWithKey(this._modifiersWithKeys, VideoSurfaceBackgroundColorModifier.identity,
      VideoSurfaceBackgroundColorModifier, value);
    return this;
  }
  controls(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoControlsModifier.identity,
      VideoControlsModifier, value);
    return this;
  }
  loop(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoLoopModifier.identity,
      VideoLoopModifier, value);
    return this;
  }
  objectFit(value: ImageFit): this {
    modifierWithKey(this._modifiersWithKeys, VideoObjectFitModifier.identity,
      VideoObjectFitModifier, value);
    return this;
  }
  enableShortcutKey(value: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoEnableShortcutKeyModifier.identity,
      VideoEnableShortcutKeyModifier, value);
    return this;
  }
  opacity(value: number | Resource): this {
    modifierWithKey(this._modifiersWithKeys, VideoOpacityModifier.identity, VideoOpacityModifier, value);
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
  onStart(callback: VoidCallback): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnStartModifier.identity,
      VideoOnStartModifier, callback);
    return this;
  }
  onPause(event: VoidCallback): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnPauseModifier.identity,
      VideoOnPauseModifier, event);
    return this;
  }
  onFinish(event: VoidCallback): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnFinishModifier.identity,
      VideoOnFinishModifier, event);
    return this;
  }
  onFullscreenChange(callback: Callback<FullscreenInfo>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnFullscreenChangeModifier.identity,
      VideoOnFullscreenChangeModifier, callback);
    return this;
  }
  onPrepared(callback: Callback<PreparedInfo>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnPreparedModifier.identity,
      VideoOnPreparedModifier, callback);
    return this;
  }
  onSeeking(callback: Callback<PlaybackInfo>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekingModifier.identity,
      VideoOnSeekingModifier, callback);
    return this;
  }
  onSeeked(callback: Callback<PlaybackInfo>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnSeekedModifier.identity,
      VideoOnSeekedModifier, callback);
    return this;
  }
  onUpdate(callback: Callback<PlaybackInfo>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnUpdateModifier.identity,
      VideoOnUpdateModifier, callback);
    return this;
  }
  onError(callback: VoidCallback | ErrorCallback): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnErrorModifier.identity,
      VideoOnErrorModifier, callback);
    return this;
  }
  onStop(event: Callback<void>): this {
    modifierWithKey(this._modifiersWithKeys, VideoOnStopModifier.identity,
      VideoOnStopModifier, event);
    return this;
  }
  enableAnalyzer(enable: boolean): this {
    modifierWithKey(this._modifiersWithKeys, VideoEnableAnalyzerModifier.identity,
      VideoEnableAnalyzerModifier, enable);
    return this;
  }
  analyzerConfig(config: ImageAnalyzerConfig): this {
    modifierWithKey(this._modifiersWithKeys, VideoAnalyzerConfigModifier.identity,
      VideoAnalyzerConfigModifier, config);
    return this;
  }
}

// @ts-ignore
if (globalThis.Video !== undefined) {
  (globalThis as any).Video.attributeModifier = function (modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkVideoComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new modifierJS.VideoModifier(nativePtr, classType);
    });
  };
}

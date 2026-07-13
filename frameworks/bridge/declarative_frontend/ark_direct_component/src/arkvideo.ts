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

/// <reference path='./../../ark_component/src/import.ts' />
type ComponentObj = { component: any }

function loadComponent(): ComponentObj | undefined {
  if (loadComponent.componentObj === undefined && globalThis.__ArkComponent__ !== undefined) {
    class VideoObjectFitModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetObjectFit(node);
        } else {
          getUINativeModule().video.setObjectFit(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoObjectFitModifier as any).identity = Symbol('videoObjectFit');

    class VideoAutoPlayModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetAutoPlay(node);
        } else {
          getUINativeModule().video.setAutoPlay(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoAutoPlayModifier as any).identity = Symbol('videoAutoPlayr');

    class VideoControlsModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetControls(node);
        } else {
          getUINativeModule().video.setControls(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoControlsModifier as any).identity = Symbol('videoControls');

    class VideoLoopModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetLoop(node);
        } else {
          getUINativeModule().video.setLoop(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoLoopModifier as any).identity = Symbol('videoLoop');

    class VideoMutedModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetMuted(node);
        } else {
          getUINativeModule().video.setMuted(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoMutedModifier as any).identity = Symbol('videoMuted');

    class VideoOpacityModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOpacity(node);
        } else {
          getUINativeModule().video.setOpacity(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoOpacityModifier as any).identity = Symbol('videoOpacity');

    class VideoSurfaceBackgroundColorModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
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
    (VideoSurfaceBackgroundColorModifier as any).identity = Symbol('videoSurfaceBackgroundColor');

    class VideoTransitionModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
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
    (VideoTransitionModifier as any).identity = Symbol('videoTransition');

    class VideoEnableShortcutKeyModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetShortcutKeyEnabled(node);
        } else {
          getUINativeModule().video.setShortcutKeyEnabled(node, this.value);
        }
      }
      checkObjectDiff(): boolean {
        return !isBaseOrResourceEqual(this.stageValue, this.value);
      }
    }
    (VideoEnableShortcutKeyModifier as any).identity = Symbol('videoEnableShortcutKey');

    class VideoOnStartModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnStart(node);
        } else {
          getUINativeModule().video.setOnStart(node, this.value);
        }
      }
    }
    (VideoOnStartModifier as any).identity = Symbol('videoOnStart');

    class VideoOnPauseModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnPause(node);
        } else {
          getUINativeModule().video.setOnPause(node, this.value);
        }
      }
    }
    (VideoOnPauseModifier as any).identity = Symbol('videoOnPause');

    class VideoOnFinishModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnFinish(node);
        } else {
          getUINativeModule().video.setOnFinish(node, this.value);
        }
      }
    }
    (VideoOnFinishModifier as any).identity = Symbol('videoOnFinish');

    class VideoOnFullscreenChangeModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnFullscreenChange(node);
        } else {
          getUINativeModule().video.setOnFullscreenChange(node, this.value);
        }
      }
    }
    (VideoOnFullscreenChangeModifier as any).identity = Symbol('videoOnFullscreenChange');

    class VideoOnPreparedModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnPrepared(node);
        } else {
          getUINativeModule().video.setOnPrepared(node, this.value);
        }
      }
    }
    (VideoOnPreparedModifier as any).identity = Symbol('videoOnPrepared');

    class VideoOnSeekingModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnSeeking(node);
        } else {
          getUINativeModule().video.setOnSeeking(node, this.value);
        }
      }
    }
    (VideoOnSeekingModifier as any).identity = Symbol('videoOnSeeking');

    class VideoOnSeekedModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnSeeked(node);
        } else {
          getUINativeModule().video.setOnSeeked(node, this.value);
        }
      }
    }
    (VideoOnSeekedModifier as any).identity = Symbol('videoOnSeeked');

    class VideoOnUpdateModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnUpdate(node);
        } else {
          getUINativeModule().video.setOnUpdate(node, this.value);
        }
      }
    }
    (VideoOnUpdateModifier as any).identity = Symbol('videoOnUpdate');

    class VideoOnErrorModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnError(node);
        } else {
          getUINativeModule().video.setOnError(node, this.value);
        }
      }
    }
    (VideoOnErrorModifier as any).identity = Symbol('videoOnError');

    class VideoOnStopModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
        if (reset) {
          getUINativeModule().video.resetOnStop(node);
        } else {
          getUINativeModule().video.setOnStop(node, this.value);
        }
      }
    }
    (VideoOnStopModifier as any).identity = Symbol('videoOnStop');

    class VideoEnableAnalyzerModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
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
    (VideoEnableAnalyzerModifier as any).identity = Symbol('videoEnableAnalyzer');

    class VideoAnalyzerConfigModifier extends ModifierWithKey<any> {
      applyPeer(node: any, reset: boolean): void {
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
    (VideoAnalyzerConfigModifier as any).identity = Symbol('videoAnalyzerConfig');

    class ArkVideoComponent extends globalThis.__ArkComponent__ {
      constructor(nativePtr: any, classType: any) {
        super(nativePtr, classType);
      }

      allowChildCount(): number {
        return 0;
      }

      muted(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, VideoMutedModifier.identity, VideoMutedModifier, value);
        return this;
      }

      autoPlay(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, VideoAutoPlayModifier.identity, VideoAutoPlayModifier, value);
        return this;
      }

      surfaceBackgroundColor(value: ResourceColor): this {
        modifierWithKey(this._modifiersWithKeys, VideoSurfaceBackgroundColorModifier.identity,
          VideoSurfaceBackgroundColorModifier, value);
        return this;
      }

      controls(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, VideoControlsModifier.identity, VideoControlsModifier, value);
        return this;
      }

      loop(value: boolean): this {
        modifierWithKey(this._modifiersWithKeys, VideoLoopModifier.identity, VideoLoopModifier, value);
        return this;
      }

      objectFit(value: ImageFit): this {
        modifierWithKey(this._modifiersWithKeys, VideoObjectFitModifier.identity, VideoObjectFitModifier, value);
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
        const arkTransition = new ArkTransition();
        arkTransition.transitionEffect = value;
        if (typeof callback === 'function') {
          arkTransition.callback = callback;
        }
        modifierWithKey(this._modifiersWithKeys, VideoTransitionModifier.identity, VideoTransitionModifier,
          arkTransition);
        return this;
      }

      onStart(callback: VoidCallback): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnStartModifier.identity, VideoOnStartModifier, callback);
        return this;
      }

      onPause(callback: VoidCallback): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnPauseModifier.identity, VideoOnPauseModifier, callback);
        return this;
      }

      onFinish(callback: VoidCallback): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnFinishModifier.identity, VideoOnFinishModifier, callback);
        return this;
      }

      onFullscreenChange(callback: Callback<FullscreenInfo>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnFullscreenChangeModifier.identity,
          VideoOnFullscreenChangeModifier, callback);
        return this;
      }

      onPrepared(callback: Callback<PreparedInfo>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnPreparedModifier.identity, VideoOnPreparedModifier, callback);
        return this;
      }

      onSeeking(callback: Callback<PlaybackInfo>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnSeekingModifier.identity, VideoOnSeekingModifier, callback);
        return this;
      }

      onSeeked(callback: Callback<PlaybackInfo>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnSeekedModifier.identity, VideoOnSeekedModifier, callback);
        return this;
      }

      onUpdate(callback: Callback<PlaybackInfo>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnUpdateModifier.identity, VideoOnUpdateModifier, callback);
        return this;
      }

      onError(callback: VoidCallback | ErrorCallback): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnErrorModifier.identity, VideoOnErrorModifier, callback);
        return this;
      }

      onStop(callback: Callback<void>): this {
        modifierWithKey(this._modifiersWithKeys, VideoOnStopModifier.identity, VideoOnStopModifier, callback);
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

    loadComponent.componentObj = { 'component': ArkVideoComponent };
  }

  return loadComponent.componentObj;
}

class JSVideo extends JSViewAbstract {
  static create(params: any): void {
    getUINativeModule().video.create(params);
  }

  static muted(value: any): void {
    getUINativeModule().video.setMuted(true, value);
  }

  static autoPlay(value: any): void {
    getUINativeModule().video.setAutoPlay(true, value);
  }

  static controls(value: any): void {
    getUINativeModule().video.setControls(true, value);
  }

  static loop(value: any): void {
    getUINativeModule().video.setLoop(true, value);
  }

  static objectFit(value: any): void {
    getUINativeModule().video.setObjectFit(true, value);
  }

  static surfaceBackgroundColor(value: any): void {
    getUINativeModule().video.setVideoSurfaceBackgroundColor(true, value);
  }

  static enableShortcutKey(value: any): void {
    getUINativeModule().video.setShortcutKeyEnabled(true, value);
  }

  static onStart(value: any): void {
    getUINativeModule().video.setOnStart(true, value);
  }

  static onPause(value: any): void {
    getUINativeModule().video.setOnPause(true, value);
  }

  static onFinish(value: any): void {
    getUINativeModule().video.setOnFinish(true, value);
  }

  static onFullscreenChange(value: any): void {
    getUINativeModule().video.setOnFullscreenChange(true, value);
  }

  static onPrepared(value: any): void {
    getUINativeModule().video.setOnPrepared(true, value);
  }

  static onSeeking(value: any): void {
    getUINativeModule().video.setOnSeeking(true, value);
  }

  static onSeeked(value: any): void {
    getUINativeModule().video.setOnSeeked(true, value);
  }

  static onUpdate(value: any): void {
    getUINativeModule().video.setOnUpdate(true, value);
  }

  static onError(value: any): void {
    getUINativeModule().video.setOnError(true, value);
  }

  static onStop(value: any): void {
    getUINativeModule().video.setOnStop(true, value);
  }

  static enableAnalyzer(value: any): void {
    getUINativeModule().video.setEnableAnalyzer(true, value);
  }

  static analyzerConfig(value: any): void {
    getUINativeModule().video.setAnalyzerConfig(true, value);
  }

  static opacity(value: any): void {
    JSViewAbstract.opacityPassThrough(value);
  }

  static transition(value: any, callback: any): void {
    JSViewAbstract.transitionPassThrough(value, callback);
  }

  static attributeModifier(modifier: any): void {
    attributeModifierFunc.call(this, modifier, (nativePtr: any) => {
      return createComponent(nativePtr);
    }, (nativePtr: any, classType: any, modifierJS: any) => {
      return new modifierJS.VideoModifier(nativePtr, classType);
    });
  }

  static onTouch(value: any): void {
    __Common__.onTouch(value);
  }

  static onHover(value: any): void {
    __Common__.onHover(value);
  }

  static onKeyEvent(value: any): void {
    __Common__.onKeyEvent(value);
  }

  static onDeleteEvent(value: any): void {
    __Common__.onDeleteEvent(value);
  }

  static onClick(value: any): void {
    __Common__.onClick(value);
  }

  static onAttach(value: any): void {
    __Common__.onAttach(value);
  }

  static onAppear(value: any): void {
    __Common__.onAppear(value);
  }

  static onDetach(value: any): void {
    __Common__.onDetach(value);
  }

  static onDisAppear(value: any): void {
    __Common__.onDisAppear(value);
  }

  static remoteMessage(value: any): void {
    __Common__.remoteMessage(value);
  }
}

function createComponent(nativePtr: any, classType: any): any {
  loadComponent();
  if (loadComponent.componentObj !== undefined) {
    return new loadComponent.componentObj.component(nativePtr, classType);
  }
  return undefined;
}

function exportComponent(): void {
  globalThis.ArkVideoComponent = (loadComponent as any).componentObj?.component;
}

function exportView(): void {
  globalThis.Video = JSVideo;
}

export default { loadComponent, createComponent, exportComponent, exportView };

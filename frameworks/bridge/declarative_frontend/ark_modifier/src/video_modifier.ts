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

class LazyArkVideoComponent extends ArkComponent {
  static module: any | undefined = undefined;

  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    if (LazyArkVideoComponent.module === undefined) {
      LazyArkVideoComponent.module = globalThis.requireNapi('arkui.components.arkvideo');
    }

    this.lazyComponent = LazyArkVideoComponent.module.createComponent(nativePtr, classType);
  }

  setMap(): void {
    this.lazyComponent._modifiersWithKeys = this._modifiersWithKeys;
  }

  allowChildCount(): number {
    return 0;
  }

  muted(value: boolean): this {
    this.lazyComponent.muted(value);
    return this;
  }

  autoPlay(value: boolean): this {
    this.lazyComponent.autoPlay(value);
    return this;
  }

  surfaceBackgroundColor(value: ResourceColor): this {
    this.lazyComponent.surfaceBackgroundColor(value);
    return this;
  }

  controls(value: boolean): this {
    this.lazyComponent.controls(value);
    return this;
  }

  loop(value: boolean): this {
    this.lazyComponent.loop(value);
    return this;
  }

  objectFit(value: ImageFit): this {
    this.lazyComponent.objectFit(value);
    return this;
  }

  enableShortcutKey(value: boolean): this {
    this.lazyComponent.enableShortcutKey(value);
    return this;
  }

  opacity(value: number | Resource): this {
    this.lazyComponent.opacity(value);
    return this;
  }

  transition(value: TransitionOptions | TransitionEffect, callback: (transitionIn: boolean) => void): this {
    this.lazyComponent.transition(value, callback);
    return this;
  }

  onStart(event: VoidCallback): this {
    this.lazyComponent.onStart(event);
    return this;
  }

  onPause(event: VoidCallback): this {
    this.lazyComponent.onPause(event);
    return this;
  }

  onFinish(event: VoidCallback): this {
    this.lazyComponent.onFinish(event);
    return this;
  }

  onFullscreenChange(callback: (event: { fullscreen: boolean }) => void): this {
    this.lazyComponent.onFullscreenChange(callback);
    return this;
  }

  onPrepared(callback: (event: { duration: number }) => void): this {
    this.lazyComponent.onPrepared(callback);
    return this;
  }

  onSeeking(callback: (event: { time: number }) => void): this {
    this.lazyComponent.onSeeking(callback);
    return this;
  }

  onSeeked(callback: (event: { time: number }) => void): this {
    this.lazyComponent.onSeeked(callback);
    return this;
  }

  onUpdate(callback: (event: { time: number }) => void): this {
    this.lazyComponent.onUpdate(callback);
    return this;
  }

  onError(event: any): this {
    this.lazyComponent.onError(event);
    return this;
  }

  onStop(event: Callback<void>): this {
    this.lazyComponent.onStop(event);
    return this;
  }

  enableAnalyzer(enable: boolean): this {
    this.lazyComponent.enableAnalyzer(enable);
    return this;
  }

  analyzerConfig(config: any): this {
    this.lazyComponent.analyzerConfig(config);
    return this;
  }
}

class VideoModifier extends LazyArkVideoComponent implements AttributeModifier<VideoAttribute> {
  constructor(nativePtr: KNode, classType: ModifierType) {
    super(nativePtr, classType);
    this._modifiersWithKeys = new ModifierMap();
    this.setMap();
  }

  applyNormalAttribute(instance: VideoAttribute): void {
    ModifierUtils.applySetOnChange(this);
    // @ts-ignore
    ModifierUtils.applyAndMergeModifier<VideoAttribute, LazyArkVideoComponent, ArkComponent>(instance, this);
  }
}

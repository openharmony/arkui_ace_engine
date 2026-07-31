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

class ArkPreviewVideoComponent extends ArkComponent {
  constructor(nativePtr, classType) {
    super(nativePtr, classType);
  }
  applyNormalAttribute(instance) {
    return this;
  }
  muted(value) {
    return this;
  }
  autoPlay(value) {
    return this;
  }
  surfaceBackgroundColor(value) {
    return this;
  }
  controls(value) {
    return this;
  }
  loop(value) {
    return this;
  }
  objectFit(value) {
    return this;
  }
  enableShortcutKey(value) {
    return this;
  }
  opacity(value) {
    return this;
  }
  transition(value, callback) {
    return this;
  }
  onStart(callback) {
    return this;
  }
  onPause(callback) {
    return this;
  }
  onFinish(callback) {
    return this;
  }
  onFullscreenChange(callback) {
    return this;
  }
  onPrepared(callback) {
    return this;
  }
  onSeeking(callback) {
    return this;
  }
  onSeeked(callback) {
    return this;
  }
  onUpdate(callback) {
    return this;
  }
  onError(callback) {
    return this;
  }
  onStop(callback) {
    return this;
  }
  enableAnalyzer(enable) {
    return this;
  }
  analyzerConfig(config) {
    return this;
  }
}

class JSVideo extends JSViewAbstract {
  static create(params) {
    getUINativeModule().previewMock.create('Video');
  }

  static muted(value) {}
  static autoPlay(value) {}
  static controls(value) {}
  static loop(value) {}
  static objectFit(value) {}
  static surfaceBackgroundColor(value) {}
  static enableShortcutKey(value) {}
  static onStart(callback) {}
  static onPause(callback) {}
  static onFinish(callback) {}
  static onFullscreenChange(callback) {}
  static onPrepared(callback) {}
  static onSeeking(callback) {}
  static onSeeked(callback) {}
  static onUpdate(callback) {}
  static onError(callback) {}
  static onStop(callback) {}
  static enableAnalyzer(enable) {}
  static analyzerConfig(config) {}
  static opacity(value) {
    JSViewAbstract.opacityPassThrough(value);
  }
  static transition(value, callback) {
    JSViewAbstract.transitionPassThrough(value, callback);
  }

  static onTouch(value) {}
  static onHover(value) {}
  static onKeyEvent(value) {}
  static onDeleteEvent(value) {}
  static onClick(value) {}
  static onAppear(value) {}
  static onDisAppear(value) {}
  static onAttach(value) {}
  static onDetach(value) {}
  static remoteMessage(value) {}

  static attributeModifier(modifier) {
    attributeModifierFunc.call(this, modifier, (nativePtr) => {
      return new ArkPreviewVideoComponent(nativePtr);
    }, (nativePtr, classType, modifierJS) => {
      return new ArkPreviewVideoComponent(nativePtr, classType);
    });
  }
}

class JSVideoController {
  start() {}
  pause() {}
  stop() {}
  setCurrentTime(value, seekMode) {}
  requestFullscreen(value) {}
  exitFullscreen() {}
  reset() {}
}

// @ts-ignore
if (globalThis.Video === undefined) {
  globalThis.Video = JSVideo;
}
// @ts-ignore
if (globalThis.VideoController === undefined) {
  globalThis.VideoController = JSVideoController;
}

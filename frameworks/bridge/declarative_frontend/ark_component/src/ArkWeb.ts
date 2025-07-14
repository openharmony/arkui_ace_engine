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
class WebJavaScriptAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webJavascriptAccess');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetJavaScriptAccess(node);
    } else {
      getUINativeModule().web.setJavaScriptAccess(node, this.value);
    }
  }
}

class WebFileAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webFileAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetFileAccess(node);
    } else {
      getUINativeModule().web.setFileAccess(node, this.value);
    }
  }
}

class WebDomStorageAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webDomStorageAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetDomStorageAccess(node);
    } else {
      getUINativeModule().web.setDomStorageAccess(node, this.value);
    }
  }
}

class WebMixedModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webMixedMode');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMixedMode(node);
    } else {
      getUINativeModule().web.setMixedMode(node, this.value);
    }
  }
}

class WebZoomAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webZoomAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetZoomAccess(node);
    } else {
      getUINativeModule().web.setZoomAccess(node, this.value);
    }
  }
}

class WebCacheModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webCacheModeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetCacheMode(node);
    } else {
      getUINativeModule().web.setCacheMode(node, this.value);
    }
  }
}

class WebDarkModeModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webDarkModeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetDarkMode(node);
    } else {
      getUINativeModule().web.setDarkMode(node, this.value);
    }
  }
}

class WebMultiWindowAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webMultiWindowAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMultiWindowAccess(node);
    } else {
      getUINativeModule().web.setMultiWindowAccess(node, this.value);
    }
  }
}
class WebAllowWindowOpenMethodModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webAllowWindowOpenMethodModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetAllowWindowOpenMethod(node);
    } else {
      getUINativeModule().web.setAllowWindowOpenMethod(node, this.value);
    }
  }
}

class WebOnScrollModifier extends ModifierWithKey<(event: { xOffset: number; yOffset: number }) => void> {
  constructor (value: (event: { xOffset: number; yOffset: number }) => void) {
    super(value)
  }
  static identity: Symbol = Symbol('webOnScrollModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnScroll(node);
    } else {
      getUINativeModule().web.setOnScroll(node, this.value);
    }
  }
}

class WebGeolocationAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webGeolocationAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetGeolocationAccess(node);
    } else {
      getUINativeModule().web.setGeolocationAccess(node, this.value);
    }
  }
}

class WebOnOverScrollModifier extends ModifierWithKey<(result: { xOffset: number; yOffset: number }) => void> {
  constructor (value: (event: { xOffset: number; yOffset: number }) => void) {
    super(value)
  }
  static identity: Symbol = Symbol('webOnOverScrollModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnOverScroll(node);
    } else {
      getUINativeModule().web.setOnOverScroll(node, this.value);
    }
  }
}

class WebDatabaseAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webDatabaseAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetDatabaseAccess(node);
    } else {
      getUINativeModule().web.setDatabaseAccess(node, this.value);
    }
  }
}

class WebOnScaleChangeModifier extends ModifierWithKey<(result: { oldScale: number; newScale: number }) => void> {
  constructor (value: (event: { oldScale: number; newScale: number }) => void) {
    super(value)
  }
  static identity: Symbol = Symbol('webOnScaleChangeModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnScaleChange(node);
    } else {
      getUINativeModule().web.setOnScaleChange(node, this.value);
    }
  }
}

class WebOverviewModeAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOverviewModeAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOverviewModeAccess(node);
    } else {
      getUINativeModule().web.setOverviewModeAccess(node, this.value);
    }
  }
}

class WebOnRequestSelectedModifier extends ModifierWithKey<() => void> {
  constructor (value: () => void) {
    super(value)
  }
  static identity: Symbol = Symbol('webOnRequestSelectedModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnRequestSelected(node);
    } else {
      getUINativeModule().web.setOnRequestSelected(node, this.value);
    }
  }
}

class WebForceDarkAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webForceDarkAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetForceDarkAccess(node);
    } else {
      getUINativeModule().web.setForceDarkAccess(node, this.value);
    }
  }
}

class WebOnContextMenuHideModifier extends ModifierWithKey<OnContextMenuHideCallback> {
  constructor (value: OnContextMenuHideCallback) {
    super(value)
  }
  static identity: Symbol = Symbol('webOnContextMenuHideModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnContextMenuHide(node);
    } else {
      getUINativeModule().web.setOnContextMenuHide(node, this.value);
    }
  }
}

class WebPinchSmoothModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webPinchSmoothModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetPinchSmooth(node);
    } else {
      getUINativeModule().web.setPinchSmooth(node, this.value);
    }
  }
}

class WebKeyboardAvoidModeModifier extends ModifierWithKey<WebKeyboardAvoidMode> {
  constructor(value: WebKeyboardAvoidMode) {
    super(value);
  }
  static identity: Symbol = Symbol('WebKeyboardAvoidModeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetKeyboardAvoidMode(node);
    } else {
      getUINativeModule().web.setKeyboardAvoidMode(node, this.value);
    }
  }
}

class WebMetaViewportModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webMetaViewportModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMetaViewport(node);
    } else {
      getUINativeModule().web.setMetaViewport(node, this.value);
    }
  }
}

class WebOnControllerAttachedModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnControllerAttachedModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnControllerAttached(node);
    } else {
      getUINativeModule().web.setOnControllerAttached(node, this.value);
    }
  }
}

class WebEnableFollowSystemFontWeightModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webEnableFollowSystemFontWeightModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetEnableFollowSystemFontWeight(node);
    } else {
      getUINativeModule().web.setEnableFollowSystemFontWeight(node, this.value);
    }
  }
}

class WebVerticalScrollBarAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webVerticalScrollBarAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetVerticalScrollBarAccess(node);
    } else {
      getUINativeModule().web.setVerticalScrollBarAccess(node, this.value);
    }
  }
}

class WebEnableNativeEmbedModeModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webEnableNativeEmbedModeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetEnableNativeEmbedMode(node);
    } else {
      getUINativeModule().web.setEnableNativeEmbedMode(node, this.value);
    }
  }
}

class WebHorizontalScrollBarAccessModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webHorizontalScrollBarAccessModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetHorizontalScrollBarAccess(node);
    } else {
      getUINativeModule().web.setHorizontalScrollBarAccess(node, this.value);
    }
  }
}

class WebMinFontSizeModifier extends ModifierWithKey<number> {
  constructor (value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webMinFontSizeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMinFontSize(node);
    } else {
      getUINativeModule().web.setMinFontSize(node, this.value);
    }
  }
}

class WebTextZoomRatioModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webTextZoomRatioModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetTextZoomRatio(node);
    } else {
      getUINativeModule().web.setTextZoomRatio(node, this.value);
    }
  }
}

class WebDefaultFontSizeModifier extends ModifierWithKey<number> {
  constructor (value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webDefaultFontSizeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetDefaultFontSize(node);
    } else {
      getUINativeModule().web.setDefaultFontSize(node, this.value);
    }
  }
}

class WebInitialScaleModifier extends ModifierWithKey<number> {
  constructor(value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webInitialScaleModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetInitialScale(node);
    } else {
      getUINativeModule().web.setInitialScale(node, this.value);
    }
  }
}

class WebDefaultFixedFontSizeModifier extends ModifierWithKey<number> {
  constructor (value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webDefaultFixedFontSizeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetDefaultFixedFontSize(node);
    } else {
      getUINativeModule().web.setDefaultFixedFontSize(node, this.value);
    }
  }
}

class WebMinLogicalFontSizeModifier extends ModifierWithKey<number> {
  constructor (value: number) {
    super(value);
  }
  static identity: Symbol = Symbol('webMinLogicalFontSizeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMinLogicalFontSize(node);
    } else {
      getUINativeModule().web.setMinLogicalFontSize(node, this.value);
    }
  }
}

class WebStandardFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webStandardFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebStandardFont(node);
    } else {
      getUINativeModule().web.setWebStandardFont(node, this.value);
    }
  }
}

class WebSerifFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webSerifFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebSerifFont(node);
    } else {
      getUINativeModule().web.setWebSerifFont(node, this.value);
    }
  }
}

class WebSansSerifFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webSansSerifFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebSansSerifFont(node);
    } else {
      getUINativeModule().web.setWebSansSerifFont(node, this.value);
    }
  }
}

class WebFixedFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webFixedFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebFixedFont(node);
    } else {
      getUINativeModule().web.setWebFixedFont(node, this.value);
    }
  }
}

class WebFantasyFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webFantasyFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebFantasyFont(node);
    } else {
      getUINativeModule().web.setWebFantasyFont(node, this.value);
    }
  }
}

class WebCursiveFontModifier extends ModifierWithKey<string> {
  constructor (value: string) {
    super(value);
  }
  static identity: Symbol = Symbol('webCursiveFontModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetWebCursiveFont(node);
    } else {
      getUINativeModule().web.setWebCursiveFont(node, this.value);
    }
  }
}

class WebLayoutModeModifier extends ModifierWithKey<WebLayoutMode> {
  constructor (value: WebLayoutMode) {
    super(value);
  }
  static identity: Symbol = Symbol('webLayoutModeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetLayoutMode(node);
    } else {
      getUINativeModule().web.setLayoutMode(node, this.value);
    }
  }
}

class WebOnNativeEmbedLifecycleChangeModifier extends ModifierWithKey<(DataInfo: NativeEmbedDataInfo) => void> {
  constructor (value: (DataInfo: NativeEmbedDataInfo) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnNativeEmbedLifecycleChangeModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedLifecycleChange(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedLifecycleChange(node, this.value);
    }
  }
}
class WebOnNativeEmbedGestureEventModifier extends ModifierWithKey<(event: NativeEmbedTouchInfo) => void> {
  constructor(value: (event: NativeEmbedTouchInfo) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnNativeEmbedGestureEventModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnNativeEmbedGestureEvent(node);
    } else {
      getUINativeModule().web.setOnNativeEmbedGestureEvent(node, this.value);
    }
  }
}
class WebRegisterNativeEmbedRuleModifier extends ModifierWithKey<ArkRegisterNativeEmbedRule> {
  constructor(value: ArkRegisterNativeEmbedRule) {
    super(value);
  }
  static identity: Symbol = Symbol('webRegisterNativeEmbedRuleModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetRegisterNativeEmbedRule(node);
    } else {
      getUINativeModule().web.setRegisterNativeEmbedRule(node, this.value?.tag, this.value?.type);
    }
  }
}

class WebNativeEmbedOptionsModifier extends ModifierWithKey<EmbedOptions> {
  constructor (value: EmbedOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('webNativeEmbedOptionsModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetNativeEmbedOptions(node);
    } else {
      getUINativeModule().web.setNativeEmbedOptions(node, this.value);
    }
  }
}

class WebOnFirstContentfulPaintModifier extends ModifierWithKey<(navigationStartTick: number, firstContentfulPaintMs: number) => void> {
  constructor(value: (navigationStartTick: number, firstContentfulPaintMs: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnFirstContentfulPaintModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnFirstContentfulPaint(node);
    } else {
      getUINativeModule().web.setOnFirstContentfulPaint(node, this.value);
    }
  }
}

class WebOnAudioStateChangedModifier extends ModifierWithKey<(playing: boolean) => void> {
  constructor (value: (playing: boolean) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnAudioStateChangedModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnAudioStateChanged(node);
    } else {
      getUINativeModule().web.setOnAudioStateChanged(node, this.value);
    }
  }
}

class WebOnFullScreenExitModifier extends ModifierWithKey<() => void> {
  constructor (value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnFullScreenExitModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnFullScreenExit(node);
    } else {
      getUINativeModule().web.setOnFullScreenExit(node, this.value);
    }
  }
}

class WebImageAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webImageAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetImageAccess(node);
    } else {
      getUINativeModule().web.setImageAccess(node, this.value);
    }
  }
}

class WebOnlineImageAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnlineImageAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnlineImageAccess(node);
    } else {
      getUINativeModule().web.setOnlineImageAccess(node, this.value);
    }
  }
}

class WebMediaPlayGestureAccessModifier extends ModifierWithKey<boolean> {
  constructor (value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webMediaPlayGestureAccessModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMediaPlayGestureAccess(node);
    } else {
      getUINativeModule().web.setMediaPlayGestureAccess(node, this.value);
    }
  }
}

class WebMediaOptionsModifier extends ModifierWithKey<WebMediaOptions> {
  constructor (value: WebMediaOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('webMediaOptionsModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetMediaOptions(node);
    } else {
      getUINativeModule().web.setMediaOptions(node, this.value?.resumeInterval, this.value?.audioExclusive);
    }
  }
}

class WebOnPageEndModifier extends ModifierWithKey<(url: string) => void> {
  constructor(value: (url: string) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnPageEndModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnPageEnd(node);
    } else {
      getUINativeModule().web.setOnPageEnd(node, this.value);
    }
  }
}

class WebOnPageBeginModifier extends ModifierWithKey<(url: string) => void> {
  constructor(value: (url: string) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnPageBeginModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnPageBegin(node);
    } else {
      getUINativeModule().web.setOnPageBegin(node, this.value);
    }
  }
}

class WebOnProgressChangeModifier extends ModifierWithKey<(newProgress: number) => void> {
  constructor(value: (newProgress: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnProgressChangeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnProgressChange(node);
    } else {
      getUINativeModule().web.setOnProgressChange(node, this.value);
    }
  }
}

class WebOnTitleReceiveModifier extends ModifierWithKey<(title: string) => void> {
  constructor(value: (title: string) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnTitleReceiveModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnTitleReceive(node);
    } else {
      getUINativeModule().web.setOnTitleReceive(node, this.value);
    }
  }
}

class WebOnDownloadStartModifier extends ModifierWithKey<(url: string, userAgent: string, contentDisposition: string,
                                                      mimetype: string, contentLength: number) => void> {
  constructor(value: (url: string, userAgent: string, contentDisposition: string,
              mimetype: string, contentLength: number) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnDownloadStartModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnDownloadStart(node);
    } else {
      getUINativeModule().web.setOnDownloadStart(node, this.value);
    }
  }
}

class WebJavaScriptOnDocumentStartModifier extends ModifierWithKey<ArkWebScriptItem> {
  constructor(value: ArkWebScriptItem) {
      super(value);
  }
  static identity: Symbol = Symbol('webJavaScriptOnDocumentStartModifier');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          getUINativeModule().web.resetJavaScriptOnDocumentStart(node);
      } else {
          getUINativeModule().web.setJavaScriptOnDocumentStart(node,
              this.value.scripts, this.value.scriptRules);
      }
  }
}

class WebJavaScriptOnDocumentEndModifier extends ModifierWithKey<ArkWebScriptItem> {
  constructor(value: ArkWebScriptItem) {
      super(value);
  }
  static identity: Symbol = Symbol('webJavaScriptOnDocumentEndModifier');
  applyPeer(node: KNode, reset: boolean): void {
      if (reset) {
          getUINativeModule().web.resetJavaScriptOnDocumentEnd(node);
      } else {
          getUINativeModule().web.setJavaScriptOnDocumentEnd(node,
              this.value.scripts, this.value.scriptRules);
      }
  }
}

class WebCopyOptionsModifier extends ModifierWithKey<CopyOptions> {
  constructor(value: CopyOptions) {
    super(value);
  }
  static identity: Symbol = Symbol('webCopyOptionsModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetCopyOption(node);
    } else {
      getUINativeModule().web.setCopyOption(node, this.value);
    }
  }
}

class WebOnRenderProcessNotRespondingModifier extends ModifierWithKey<(OnRenderProcessNotRespondingCallback) => void> {
  constructor(value: (OnRenderProcessNotRespondingCallback) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnRenderProcessNotRespondingModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnRenderProcessNotResponding(node);
    } else {
      getUINativeModule().web.setOnRenderProcessNotResponding(node, this.value);
    }
  }
}

class WebOnPageVisibleModifier extends ModifierWithKey<(event: { url: string }) => void> {
  constructor (value: (event: { url: string }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnPageVisibleModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnPageVisible(node);
    } else {
      getUINativeModule().web.setOnPageVisible(node, this.value);
    }
  }
}

class WebOnRenderExitedModifier extends ModifierWithKey<(event?: { renderExitReason: RenderExitReason }) => void> {
  constructor (value: (event?: { renderExitReason: RenderExitReason }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnRenderExitedModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnRenderExited(node);
    } else {
      getUINativeModule().web.setOnRenderExited(node, this.value);
    }
  }
}

class WebBlockNetworkModifier extends ModifierWithKey<boolean> {
  constructor(value: boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webBlockNetworkModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetBlockNetwork(node);
    } else {
      getUINativeModule().web.setBlockNetwork(node, this.value);
    }
  }
}

class WebOnResourceLoadModifier extends ModifierWithKey<(event: { url: string }) => void> {
  constructor (value: (event: { url: string }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnResourceLoadModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnResourceLoad(node);
    } else {
      getUINativeModule().web.retOnResourceLoad(node, this.value);
    }
  }
}

class WebOnRefreshAccessedHistoryModifier extends ModifierWithKey<(event: { url: string; isRefreshed: boolean; } | undefined) => void> {
  constructor (value: (event?: { url: string; isRefreshed: boolean; } | undefined) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnRefreshAccessedHistoryModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnRefreshAccessedHistory(node);
    } else {
      getUINativeModule().web.setOnRefreshAccessedHistory(node, this.value);
    }
  }
}

class WebOnNavigationEntryCommittedModifier extends ModifierWithKey<OnNavigationEntryCommittedCallback> {
  constructor (value: OnNavigationEntryCommittedCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnNavigationEntryCommittedModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnNavigationEntryCommitted(node);
    } else {
      getUINativeModule().web.setOnNavigationEntryCommitted(node, this.value);
    }
  }
}

class WebOnSearchResultReceiveModifier extends ModifierWithKey<(even?: { activeMatchOrdinal: number; numberOfMatches: number; isDoneCounting: boolean; } | undefined) => void> {
  constructor (value: (event?:{ activeMatchOrdinal: number; numberOfMatches: number; isDoneCounting: boolean; } | undefined) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnSearchResultReceiveModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnSearchResultReceive(node);
    } else {
      getUINativeModule().web.setOnSearchResultReceive(node, this.value);
    }
  }
}

class WebOverScrollModeModifier extends ModifierWithKey<OverScrollMode> {
  constructor(value: OverScrollMode) {
    super(value);
  }
  static identity: Symbol = Symbol('webOverScrollModeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOverScrollMode(node);
    } else {
      getUINativeModule().web.setOverScrollMode(node, this.value);
    }
  }
}

class WebOnRenderProcessRespondingModifier extends ModifierWithKey<OnRenderProcessRespondingCallback> {
  constructor (value: OnRenderProcessRespondingCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnRenderProcessRespondingModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnRenderProcessResponding(node);
    } else {
      getUINativeModule().web.setOnRenderProcessResponding(node, this.value);
    }
  }
}

class WebOnTouchIconUrlReceivedModifier extends ModifierWithKey<(event: { url: string; precomposed: boolean; } | undefined) => void> {
  constructor (value: (event?:{ url: string; precomposed: boolean; } | undefined) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnTouchIconUrlReceivedModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnTouchIconUrlReceived(node);
    } else {
      getUINativeModule().web.setOnTouchIconUrlReceived(node, this.value);
    }
  }
}

class WebOnWindowNewModifier extends ModifierWithKey<(isAlert: boolean, isUserTrigger: boolean, targetUrl: string, handler: ControllerHandler) => void> {
  constructor(value: (isAlert: boolean, isUserTrigger: boolean, targetUrl: string, handler: ControllerHandler) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnWindowNewModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnWindowNew(node);
    } else {
      getUINativeModule().web.setOnWindowNew(node, this.value);
    }
  }
}

class WebOnGeolocationShowModifier extends ModifierWithKey<(origin: string, geolocation: JsGeolocation) => void>{
  constructor (value: (origin: string, geolocation: JsGeolocation) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnGeolocationShowModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnGeolocationShow(node);
    } else {
      getUINativeModule().web.setOnGeolocationShow(node, this.value);
    }
  }
}

class WebOnPermissionRequestModifier extends ModifierWithKey<(request: PermissionRequest) => void>{
  constructor(value: (request: PermissionRequest) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnPermissionRequestModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnPermissionRequest(node);
    } else {
      getUINativeModule().web.setOnPermissionRequest(node, this.value);
    }
  }
}

class WebOnScreenCaptureRequestModifier extends ModifierWithKey<(handler: ScreenCaptureHandler) => void> {
  constructor(value: (handler: ScreenCaptureHandler) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnScreenCaptureRequestModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnScreenCaptureRequest(node);
    } else {
      getUINativeModule().web.setOnScreenCaptureRequest(node, this.value);
    }
  }
}

class WebOnFullScreenEnterModifier extends ModifierWithKey<(event: { handler: FullScreenExitHandler; }) => void> {
  constructor(value: (event: { handler: FullScreenExitHandler; }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnFullScreenEnterModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnFullScreenEnter(node);
    } else {
      getUINativeModule().web.setOnFullScreenEnter(node, this.value);
    }
  }
}

class WebOnWindowExitModifier extends ModifierWithKey<() => void> {
  constructor(value: () => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnWindowExitModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnWindowExit(node);
    } else {
      getUINativeModule().web.setOnWindowExit(node, this.value);
    }
  }
}

class WebOnAlertModifier extends ModifierWithKey<(url: string, message: string, result: JsResult) => boolean> {
  constructor (value: (url: string, message: string, result: JsResult) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnAlertModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnAlert(node);
    } else {
      getUINativeModule().web.setOnAlert(node, this.value);
    }
  }
}

class WebOnConfirmModifier extends ModifierWithKey<(url: string, message: string, result: JsResult) => boolean> {
  constructor (value: (url: string, message: string, result: JsResult) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnConfirmModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnConfirm(node);
    } else {
      getUINativeModule().web.retOnConfirm(node, this.value);
    }
  }
}

class WebOnPromptModifier extends ModifierWithKey<(url: string, message: string, value: string, result: JsResult) => boolean> {
  constructor (value: (url: string, message: string, value: string, result: JsResult) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnPromptModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnPrompt(node);
    } else {
      getUINativeModule().web.setOnPromt(node, this.value);
    }
  }
}

class WebOnShowFileSelectorModifier extends ModifierWithKey<(result: FileSelectorResult, fileSelector: FileSelectorParam) => boolean> {
  constructor(value: (result: FileSelectorResult, fileSelector: FileSelectorParam) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnShowFileSelectorModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnShowFileSelector(node);
    } else {
      getUINativeModule().web.setOnShowFileSelector(node, this.value);
    }
  }
}

class WebOnContextMenuShowModifier extends ModifierWithKey<(param: WebContextMenuParam, result: WebContextMenuResult) => boolean> {
  constructor(value: (param: WebContextMenuParam, result: WebContextMenuResult) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnContextMenuShowModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnContextMenuShow(node);
    } else {
      getUINativeModule().web.setOnContextMenuShow(node, this.value);
    }
  }
}

class WebOnSafeBrowsingCheckResultModifier extends ModifierWithKey<OnSafeBrowsingCheckResultCallback> {
  constructor (value: OnSafeBrowsingCheckResultCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnSafeBrowsingCheckResultModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnSafeBrowsingCheckResult(node);
    } else {
      getUINativeModule().web.setOnSafeBrowsingCheckResult(node, this.value);
    }
  }
}

class WebNestedScrollModifier extends ModifierWithKey<ArkNestedScrollOptionsExt> {
  constructor(value: ArkNestedScrollOptionsExt) {
    super(value);
  }
  static identity: Symbol = Symbol('webNestedScrollModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetNestedScroll(node);
    } else {
      getUINativeModule().web.setNestedScroll(node, this.value.scrollUp, this.value.scrollDown,
        this.value.scrollLeft, this.value.scrollRight);
    }
  }
}

class WebOnInterceptKeyEventModifier extends ModifierWithKey<(result: { event: KeyEvent }) => boolean> {
  constructor (value: (handler: KeyEvent) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnInterceptKeyEventModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnInterceptKeyEvent(node);
    } else {
      getUINativeModule().web.setOnInterceptKeyEvent(node, this.value);
    }
  }
}

class WebOnErrorReceiveModifier extends ModifierWithKey<(event?: { request: WebResourceRequest, error: WebResourceError } | undefined) => void> {
  constructor(value: (event?: { request: WebResourceRequest, error: WebResourceError } | undefined) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnErrorReceiveModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnErrorReceive(node);
    } else {
      getUINativeModule().web.setOnErrorReceive(node, this.value);
    }
  }
}

class WebOnLoadInterceptModifier extends ModifierWithKey<(event: { data: WebResourceRequest }) => boolean> {
  constructor(value: (event: { data: WebResourceRequest }) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnLoadInterceptModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnLoadIntercept(node);
    } else {
      getUINativeModule().web.setOnLoadIntercept(node, this.value);
    }
  }
}

class WebOnHttpErrorReceiveModifier extends ModifierWithKey<(event?: { request: WebResourceRequest, response: WebResourceResponse } | undefined) => void> {
  constructor(value: (event?: { request: WebResourceRequest, response: WebResourceResponse } | undefined) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnHttpErrorReceiveModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnHttpErrorReceive(node);
    } else {
      getUINativeModule().web.setOnHttpErrorReceive(node, this.value);
    }
  }
}

class WebOnOverrideUrlLoadingModifier extends ModifierWithKey<OnOverrideUrlLoadingCallback> {
  constructor(value: OnOverrideUrlLoadingCallback) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnOverrideUrlLoadingModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnOverrideUrlLoading(node);
    } else {
      getUINativeModule().web.setOnOverrideUrlLoading(node, this.value);
    }
  }
}

class WebOnHttpAuthRequestModifier extends ModifierWithKey<(event?: { handler: HttpAuthHandler, host: string, realm: string } | undefined) => boolean> {
  constructor(value: (event?: { handler: HttpAuthHandler, host: string, realm: string } | undefined) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnHttpAuthRequestModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnHttpAuthRequest(node);
    } else {
      getUINativeModule().web.setOnHttpAuthRequest(node, this.value);
    }
  }
}

class WebOnConsoleModifier extends ModifierWithKey<(event?: { message: ConsoleMessage; } | undefined) => boolean> {
  constructor(value: (event?: { message: ConsoleMessage; } | undefined) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnConsoleModifier')
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnConsole(node);
    } else {
      getUINativeModule().web.setOnConsole(node, this.value);
    }
  }
}

class WebOnSslErrorEventModifier extends ModifierWithKey<(event: { handler: SslErrorHandler; error: SslError; url: string;
    originalUrl: string; referrer: string; isFatalError: boolean; isMainFrame: boolean; }) => void > {
  constructor(value: (event: { handler: SslErrorHandler; error: SslError; url: string;
    originalUrl: string; referrer: string; isFatalError: boolean; isMainFrame: boolean; }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnSslErrorEventModifier')
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetnSslErrorEvent(node);
    } else {
      getUINativeModule().web.setnSslErrorEvent(node, this.value);
    }
  }
}

class WebOnDataResubmittedModifier extends ModifierWithKey<(event: { handler: DataResubmissionHandler }) => void > {
  constructor(value: (event: { handler: DataResubmissionHandler }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('WebOnDataResubmittedModifier')
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnDataResubmitted(node);
    } else {
      getUINativeModule().web.setOnDataResubmitted(node, this.value);
    }
  }
}

class WebGestureFocusModeModifier extends ModifierWithKey<GestureFocusMode> {
  constructor(value: GestureFocusMode) {
    super(value);
  }
  static identity: Symbol = Symbol('webGestureFocusModeModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetGestureFocusMode(node);
    } else {
      getUINativeModule().web.setGestureFocusMode(node, this.value);
    }
  }
}

class WebOnSslErrorEventReceiveModifier extends ModifierWithKey<OnSslErrorEventReceiveEvent> {
  constructor (value: OnSslErrorEventReceiveEvent) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnSslErrorEventReceiveModifier');
  applyPeer (node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnSslErrorEventReceive(node);
    } else {
      getUINativeModule().web.setOnSslErrorEventReceive(node, this.value);
    }
  }
}

class WebOnClientAuthenticationRequestModifier extends ModifierWithKey<(event: { handler: ClientAuthenticationHandler; host: string; port: number;
  keyTypes: string[]; issuers: string[] }) => void> {
  constructor(value: (event: { handler: ClientAuthenticationHandler; host: string; port: number;
    keyTypes: string[]; issuers: string[] }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnClientAuthenticationRequestModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnClientAuthenticationRequest(node);
    } else {
      getUINativeModule().web.setOnClientAuthenticationRequest(node, this.value);
    }
  }
}

class WebOnInterceptRequestModifier extends ModifierWithKey<(event?: { request: WebResourceRequest } | undefined) => WebResourceResponse> {
  constructor(value: (event?: { request: WebResourceRequest } | undefined) => WebResourceResponse) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnInterceptRequestModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnInterceptRequest(node);
    } else {
      getUINativeModule().web.setOnInterceptRequest(node, this.value);
    }
  }
}

class WebOnFaviconReceivedModifier extends ModifierWithKey<(event: { favicon: any; }) => void> {
  constructor(value: (event: { favicon: any; }) => void) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnFaviconReceivedModifier');
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnFaviconReceived(node);
    } else {
      getUINativeModule().web.setOnFaviconReceived(node, this.value);
    }
  }
}

class WebOnBeforeUnloadModifier extends
  ModifierWithKey<(event?: { url: string; message: string;  isReload?: boolean; result: JsResult; } | undefined) => boolean> {
  constructor(value: (event?: { url: string; message: string; isReload?: boolean; result: JsResult; } | undefined) => boolean) {
    super(value);
  }
  static identity: Symbol = Symbol('webOnBeforeUnloadModifier')
  applyPeer(node: KNode, reset: boolean): void {
    if (reset) {
      getUINativeModule().web.resetOnBeforeUnload(node);
    } else {
      getUINativeModule().web.setOnBeforeUnload(node, this.value);
    }
  }
}

class ArkWebComponent extends ArkComponent implements WebAttribute {
  constructor(nativePtr: KNode, classType?: ModifierType) {
    super(nativePtr, classType);
  }
  javaScriptAccess(javaScriptAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptAccessModifier.identity, WebJavaScriptAccessModifier, javaScriptAccess);
    return this;
  }
  fileAccess(fileAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebFileAccessModifier.identity, WebFileAccessModifier, fileAccess);
    return this;
  }
  onlineImageAccess(onlineImageAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnlineImageAccessModifier.identity, WebOnlineImageAccessModifier, onlineImageAccess);
    return this;
  }
  domStorageAccess(domStorageAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebDomStorageAccessModifier.identity, WebDomStorageAccessModifier, domStorageAccess);
    return this;
  }
  imageAccess(imageAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebImageAccessModifier.identity, WebImageAccessModifier, imageAccess);
    return this;
  }
  mixedMode(mixedMode: MixedMode): this {
    modifierWithKey(this._modifiersWithKeys, WebMixedModeModifier.identity, WebDarkModeModifier, mixedMode);
    return this;
  }
  zoomAccess(zoomAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebZoomAccessModifier.identity, WebZoomAccessModifier, zoomAccess);
    return this;
  }
  geolocationAccess(geolocationAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebGeolocationAccessModifier.identity, WebGeolocationAccessModifier, geolocationAccess);
    return this;
  }
  javaScriptProxy(javaScriptProxy: { object: object; name: string; methodList: string[]; controller: any; }): this {
    throw new Error('Method not implemented.');
  }
  password(password: boolean): this {
    throw new Error('Method not implemented.');
  }
  cacheMode(cacheMode: CacheMode): this {
    modifierWithKey(this._modifiersWithKeys, WebCacheModeModifier.identity, WebCacheModeModifier, cacheMode);
    return this;
  }
  darkMode(mode: WebDarkMode): this {
    modifierWithKey(this._modifiersWithKeys, WebDarkModeModifier.identity, WebDarkModeModifier, mode);
    return this;
  }
  forceDarkAccess(access: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebForceDarkAccessModifier.identity, WebForceDarkAccessModifier, access);
    return this;
  }
  mediaOptions(options: WebMediaOptions): this {
    modifierWithKey(this._modifiersWithKeys, WebMediaOptionsModifier.identity, WebMediaOptionsModifier, options);
    return this;
  }
  tableData(tableData: boolean): this {
    throw new Error('Method not implemented.');
  }
  wideViewModeAccess(wideViewModeAccess: boolean): this {
    throw new Error('Method not implemented.');
  }
  overviewModeAccess(overviewModeAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOverviewModeAccessModifier.identity, WebOverviewModeAccessModifier, overviewModeAccess);
    return this;
  }
  overScrollMode(mode: OverScrollMode): this {
    modifierWithKey(this._modifiersWithKeys, WebOverScrollModeModifier.identity, WebOverScrollModeModifier, mode);
    return this;
  }
  textZoomAtio(textZoomAtio: number): this {
    throw new Error('Method not implemented.');
  }
  textZoomRatio(textZoomRatio: number): this {
    modifierWithKey(this._modifiersWithKeys, WebTextZoomRatioModifier.identity, WebTextZoomRatioModifier, textZoomRatio);
    return this;
  }
  databaseAccess(databaseAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebDatabaseAccessModifier.identity, WebDatabaseAccessModifier, databaseAccess);
    return this;
  }
  initialScale(percent: number): this {
    modifierWithKey(this._modifiersWithKeys, WebInitialScaleModifier.identity, WebInitialScaleModifier, percent);
    return this;
  }
  userAgent(userAgent: string): this {
    throw new Error('Method not implemented.');
  }
  onPageEnd(callback: (event?: { url: string; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnPageEndModifier.identity, WebOnPageEndModifier, callback);
    return this;
  }
  onPageBegin(callback: (event?: { url: string; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnPageBeginModifier.identity, WebOnPageBeginModifier, callback);
    return this;
  }
  onProgressChange(callback: (event?: { newProgress: number; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnProgressChangeModifier.identity, WebOnProgressChangeModifier, callback);
    return this;
  }
  onTitleReceive(callback: (event?: { title: string; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnTitleReceiveModifier.identity, WebOnTitleReceiveModifier, callback);
    return this;
  }
  onGeolocationHide(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onGeolocationShow(callback: (event?: { origin: string; geolocation: JsGeolocation; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnGeolocationShowModifier.identity, WebOnGeolocationShowModifier, callback);
    return this;
  }
  onRequestSelected(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnRequestSelectedModifier.identity, WebOnRequestSelectedModifier, callback);
    return this;
  }
  onAlert(callback: (event?: { url: string; message: string; result: JsResult; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnAlertModifier.identity, WebOnAlertModifier, callback);
    return this;
  }
  onBeforeUnload(callback: (event?: { url: string; message: string; result: JsResult; isReload?: boolean; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnBeforeUnloadModifier.identity, WebOnBeforeUnloadModifier, callback);
    return this;
  }
  onConfirm(callback: (event?: { url: string; message: string; result: JsResult; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnConfirmModifier.identity, WebOnConfirmModifier, callback);
    return this;
  }
  onPrompt(callback: (event?: { url: string; message: string; value: string; result: JsResult; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnPromptModifier.identity, WebOnPromptModifier, callback);
    return this;
  }
  onConsole(callback: (event?: { message: ConsoleMessage; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnConsoleModifier.identity, WebOnConsoleModifier, callback);
    return this;
  }
  onErrorReceive(callback: (event?: { request: WebResourceRequest; error: WebResourceError; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnErrorReceiveModifier.identity, WebOnErrorReceiveModifier, callback);
    return this;
  }
  onHttpErrorReceive(callback: (event?: { request: WebResourceRequest; response: WebResourceResponse; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnHttpErrorReceiveModifier.identity, WebOnHttpErrorReceiveModifier, callback);
    return this;
  }
  onDownloadStart(callback: (event?: {
    url: string;
    userAgent: string; contentDisposition: string;
    mimetype: string; contentLength: number;
  } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnDownloadStartModifier.identity, WebOnDownloadStartModifier, callback);
    return this;
  }
  onRefreshAccessedHistory(callback: (event?: { url: string; isRefreshed: boolean; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnRefreshAccessedHistoryModifier.identity, WebOnRefreshAccessedHistoryModifier, callback);
    return this;
  }
  onUrlLoadIntercept(callback: (event?: { data: string | WebResourceRequest; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onSslErrorReceive(callback: (event?: { handler: Function; error: object; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onRenderExited(callback: (event?: { renderExitReason: RenderExitReason; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderExitedModifier.identity, WebOnRenderExitedModifier, callback);
    return this;
  }
  onRenderExited(callback: (event?: { detail: object; } | undefined) => boolean): this;
  onRenderExited(callback: unknown): this {
    throw new Error('Method not implemented.');
  }
  onShowFileSelector(callback: (event?: { result: FileSelectorResult; fileSelector: FileSelectorParam; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnShowFileSelectorModifier.identity, WebOnShowFileSelectorModifier, callback);
    return this;
  }
  onFileSelectorShow(callback: (event?: { callback: Function; fileSelector: object; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onResourceLoad(callback: (event: { url: string; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnResourceLoadModifier.identity, WebOnResourceLoadModifier, callback);
    return this;
  }
  onFullScreenExit(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnFullScreenExitModifier.identity, WebOnFullScreenExitModifier, callback);
    return this;
  }
  onFullScreenEnter(callback: (event: { handler: FullScreenExitHandler; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnFullScreenEnterModifier.identity, WebOnFullScreenEnterModifier, callback);
    return this;
  }
  onScaleChange(callback: (event: { oldScale: number; newScale: number; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnScaleChangeModifier.identity, WebOnScaleChangeModifier, callback);
    return this;
  }
  onHttpAuthRequest(callback: (event?: { handler: HttpAuthHandler; host: string; realm: string; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnHttpAuthRequestModifier.identity, WebOnHttpAuthRequestModifier, callback);
    return this;
  }
  onInterceptRequest(callback: (event?: { request: WebResourceRequest; } | undefined) => WebResourceResponse): this {
    modifierWithKey(this._modifiersWithKeys, WebOnInterceptRequestModifier.identity, WebOnInterceptRequestModifier, callback);
    return this;
  }
  onOverrideErrorPage(callback: (event?: { webResourceRequest: WebResourceRequest; error: WebResourceError; } | undefined) => string): this {
    throw new Error('Method not implemented.');
  }
  onPermissionRequest(callback: (event?: { request: PermissionRequest; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnPermissionRequestModifier.identity, WebOnPermissionRequestModifier, callback);
    return this;
  }
  onScreenCaptureRequest(callback: (event?: { handler: ScreenCaptureHandler; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnScreenCaptureRequestModifier.identity, WebOnScreenCaptureRequestModifier, callback);
    return this;
  }
  onContextMenuShow(callback: (event?: { param: WebContextMenuParam; result: WebContextMenuResult; } | undefined) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnContextMenuShowModifier.identity, WebOnContextMenuShowModifier, callback);
    return this;
  }
  mediaPlayGestureAccess(access: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebMediaPlayGestureAccessModifier.identity, WebMediaPlayGestureAccessModifier, access);
    return this;
  }
  onSearchResultReceive(callback: (event?: { activeMatchOrdinal: number; numberOfMatches: number; isDoneCounting: boolean; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnSearchResultReceiveModifier.identity, WebOnSearchResultReceiveModifier, callback);
    return this;
  }
  onScroll(callback: (event: { xOffset: number; yOffset: number; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnScrollModifier.identity, WebOnScrollModifier, callback);
    return this;
  }
  onSslErrorEventReceive(callback: OnSslErrorEventReceiveEvent): this {
    modifierWithKey(this._modifiersWithKeys, WebOnSslErrorEventReceiveModifier.identity, WebOnSslErrorEventReceiveModifier, callback);
    return this;
  }
  onSslErrorEvent(callback: (event: { handler: SslErrorHandler; error: SslError; url: string;
    originalUrl: string; referrer: string; isFatalError: boolean; isMainFrame: boolean; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnSslErrorEventModifier.identity, WebOnSslErrorEventModifier, callback);
    return this;
  }
  onClientAuthenticationRequest(callback: (event: {
    handler: ClientAuthenticationHandler;
    host: string; port: number; keyTypes: string[]; issuers: string[];
  }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnClientAuthenticationRequestModifier.identity, WebOnClientAuthenticationRequestModifier, callback);
    return this;
  }
  onWindowNew(callback: (event: { isAlert: boolean; isUserTrigger: boolean; targetUrl: string; handler: ControllerHandler; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnWindowNewModifier.identity, WebOnWindowNewModifier, callback);
    return this;
  }
  onWindowExit(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnWindowExitModifier.identity, WebOnWindowExitModifier, callback);
    return this;
  }
  multiWindowAccess(multiWindow: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebMultiWindowAccessModifier.identity, WebMultiWindowAccessModifier, multiWindow);
    return this;
  }
  onInterceptKeyEvent(callback: (event: KeyEvent) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnInterceptKeyEventModifier.identity, WebOnInterceptKeyEventModifier, callback);
    return this;
  }
  webStandardFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebStandardFontModifier.identity, WebStandardFontModifier, family);
    return this;
  }
  webSerifFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebSerifFontModifier.identity, WebSerifFontModifier, family);
    return this;
  }
  webSansSerifFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebSansSerifFontModifier.identity, WebSansSerifFontModifier, family);
    return this;
  }
  webFixedFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebFixedFontModifier.identity, WebFixedFontModifier, family);
    return this;
  }
  webFantasyFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebFantasyFontModifier.identity, WebFantasyFontModifier, family);
    return this;
  }
  webCursiveFont(family: string): this {
    modifierWithKey(this._modifiersWithKeys, WebCursiveFontModifier.identity, WebCursiveFontModifier, family);
    return this;
  }
  defaultFixedFontSize(size: number): this {
    modifierWithKey(this._modifiersWithKeys, WebDefaultFixedFontSizeModifier.identity, WebDefaultFixedFontSizeModifier, size);
    return this;
  }
  defaultFontSize(size: number): this {
    modifierWithKey(this._modifiersWithKeys, WebDefaultFontSizeModifier.identity, WebDefaultFontSizeModifier, size);
    return this;
  }
  minFontSize(size: number): this {
    modifierWithKey(this._modifiersWithKeys, WebMinFontSizeModifier.identity, WebMinFontSizeModifier, size);
    return this;
  }
  minLogicalFontSize(size: number): this {
    modifierWithKey(this._modifiersWithKeys, WebMinLogicalFontSizeModifier.identity, WebMinLogicalFontSizeModifier, size);
    return this;
  }
  blockNetwork(block: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebBlockNetworkModifier.identity, WebBlockNetworkModifier, block);
    return this;
  }
  horizontalScrollBarAccess(horizontalScrollBar: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebHorizontalScrollBarAccessModifier.identity, WebHorizontalScrollBarAccessModifier, horizontalScrollBar);
    return this;
  }
  verticalScrollBarAccess(verticalScrollBar: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebVerticalScrollBarAccessModifier.identity, WebVerticalScrollBarAccessModifier, verticalScrollBar);
    return this;
  }
  onTouchIconUrlReceived(callback: (event: { url: string; precomposed: boolean; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnTouchIconUrlReceivedModifier.identity, WebOnTouchIconUrlReceivedModifier, callback);
    return this;
  }
  onFaviconReceived(callback: (event: { favicon: any; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnFaviconReceivedModifier.identity, WebOnFaviconReceivedModifier, callback);
    return this;
  }
  onPageVisible(callback: (event: { url: string; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnPageVisibleModifier.identity, WebOnPageVisibleModifier, callback);
    return this;
  }
  onDataResubmitted(callback: (event: { handler: DataResubmissionHandler; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnDataResubmittedModifier.identity, WebOnDataResubmittedModifier, callback);
    return this;
  }
  pinchSmooth(isEnabled: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebPinchSmoothModifier.identity, WebPinchSmoothModifier, isEnabled);
    return this;
  }
  metaViewport(enabled: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebMetaViewportModifier.identity, WebMetaViewportModifier, enabled);
    return this;
  }
  enableFollowSystemFontWeight(follow: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebEnableFollowSystemFontWeightModifier.identity, WebEnableFollowSystemFontWeightModifier, follow);
    return this;
  }
  enableNativeEmbedMode(mode: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebEnableNativeEmbedModeModifier.identity, WebEnableNativeEmbedModeModifier, mode);
    return this;
  }
  allowWindowOpenMethod(flag: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebAllowWindowOpenMethodModifier.identity, WebAllowWindowOpenMethodModifier, flag);
    return this;
  }
  onAudioStateChanged(callback: (event: { playing: boolean; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnAudioStateChangedModifier.identity, WebOnAudioStateChangedModifier, callback);
    return this;
  }
  onFirstContentfulPaint(callback: (event?: { navigationStartTick: number; firstContentfulPaintMs: number; } | undefined) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnFirstContentfulPaintModifier.identity, WebOnFirstContentfulPaintModifier, callback);
    return this;
  }
  nativeEmbedOptions(value?: EmbedOptions): this {
    modifierWithKey(this._modifiersWithKeys, WebNativeEmbedOptionsModifier.identity, WebNativeEmbedOptionsModifier, value);
    return this;
  }
  onLoadIntercept(callback: (event: { data: WebResourceRequest; }) => boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebOnLoadInterceptModifier.identity, WebOnLoadInterceptModifier, callback);
    return this;
  }
  onControllerAttached(callback: () => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnControllerAttachedModifier.identity, WebOnControllerAttachedModifier, callback);
    return this;
  }
  onOverScroll(callback: (event: { xOffset: number; yOffset: number; }) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnOverScrollModifier.identity, WebOnOverScrollModifier, callback);
    return this;
  }
  javaScriptOnDocumentStart(scripts: ScriptItem[]): this {
    let scriptInfo = new ArkWebScriptItem();
    scriptInfo.scripts = scripts.map(item => { return item.script; });
    scriptInfo.scriptRules = scripts.map(item => { return item.scriptRules; });
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptOnDocumentStartModifier.identity, WebJavaScriptOnDocumentStartModifier, scriptInfo);
    return this;
  }
  javaScriptOnDocumentEnd(scripts: ScriptItem[]): this {
    let scriptInfo = new ArkWebScriptItem();
    scriptInfo.scripts = scripts.map(item => { return item.script; });
    scriptInfo.scriptRules = scripts.map(item => { return item.scriptRules; });
    modifierWithKey(this._modifiersWithKeys, WebJavaScriptOnDocumentEndModifier.identity, WebJavaScriptOnDocumentEndModifier, scriptInfo);
    return this;
  }

  layoutMode(mode: WebLayoutMode): this {
    modifierWithKey(this._modifiersWithKeys, WebLayoutModeModifier.identity, WebLayoutModeModifier, mode);
    return this;
  }
  onNativeEmbedLifecycleChange(callback: (event: NativeEmbedDataInfo) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedLifecycleChangeModifier.identity, WebOnNativeEmbedLifecycleChangeModifier, callback);
    return this;
  }
  onNativeEmbedGestureEvent(callback: (event: NativeEmbedTouchInfo) => void): this {
    modifierWithKey(this._modifiersWithKeys, WebOnNativeEmbedGestureEventModifier.identity, WebOnNativeEmbedGestureEventModifier, callback);
    return this;
  }
  registerNativeEmbedRule(tag: string, type: string): this {
    let arkRegisterNativeEmbedRule = new ArkRegisterNativeEmbedRule();
    if (!isUndefined(tag) && !isNull(tag)) {
      arkRegisterNativeEmbedRule.tag = tag;
    }
    if (!isUndefined(type) && !isNull(type)) {
      arkRegisterNativeEmbedRule.type = type;
    }
    if (arkRegisterNativeEmbedRule.tag === undefined && arkRegisterNativeEmbedRule.type === undefined) {
        modifierWithKey(this._modifiersWithKeys, WebRegisterNativeEmbedRuleModifier.identity, WebRegisterNativeEmbedRuleModifier, undefined);
    } else {
        modifierWithKey(this._modifiersWithKeys, WebRegisterNativeEmbedRuleModifier.identity, WebRegisterNativeEmbedRuleModifier, arkRegisterNativeEmbedRule);
    }
    return this;
  }
  nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt): this {
    if (!value) return this;
    const options = new ArkNestedScrollOptionsExt();
    
    if ('scrollUp' in value) {
      options.scrollUp = value.scrollUp;
    }
    if ('scrollDown' in value) {
      options.scrollDown = value.scrollDown;
    }
    if ('scrollLeft' in value) {
      options.scrollLeft = value.scrollLeft;
    }
    if ('scrollRight' in value) {
      options.scrollRight = value.scrollRight;
    }

    if ('scrollForward' in value) {
      options.scrollDown = value.scrollForward;
      options.scrollRight = value.scrollForward;
    }
    if ('scrollBackward' in value) {
      options.scrollUp = value.scrollBackward;
      options.scrollLeft = value.scrollBackward;
    }
    modifierWithKey(this._modifiersWithKeys, WebNestedScrollModifier.identity, WebNestedScrollModifier, options);
    return this;
  }
  onOverrideUrlLoading(callback: OnOverrideUrlLoadingCallback): this {
    modifierWithKey(this._modifiersWithKeys, WebOnOverrideUrlLoadingModifier.identity, WebOnOverrideUrlLoadingModifier, callback);
    return this;
  }
  enableNativeMediaPlayer(config: NativeMediaPlayerConfig): this {
    throw new Error('Method not implemented.');
  }
  onRenderProcessNotResponding(callback: OnRenderProcessNotRespondingCallback): this {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderProcessNotRespondingModifier.identity, WebOnRenderProcessNotRespondingModifier, callback);
    return this;
  }
  onRenderProcessResponding(callback: OnRenderProcessRespondingCallback): this {
    modifierWithKey(this._modifiersWithKeys, WebOnRenderProcessRespondingModifier.identity, WebOnRenderProcessRespondingModifier, callback);
    return this;
  }
  onViewportFitChanged(callback: OnViewportFitChangedCallback): this {
    throw new Error('Method not implemented.');
  }
  onAdsBlockedBlock(callback: (details: { url: string; adsBlocked: string[]; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onActivateContent(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  keyboardAvoidMode(mode: WebKeyboardAvoidMode): this {
    modifierWithKey(this._modifiersWithKeys, WebKeyboardAvoidModeModifier.identity, WebKeyboardAvoidModeModifier, mode);
    return this;
  }
  onContextMenuHide(callback: OnContextMenuHideCallback): this {
    modifierWithKey(this._modifiersWithKeys, WebOnContextMenuHideModifier.identity, WebOnContextMenuHideModifier, callback);
    return this;
  }
  copyOptions(value: CopyOptions): this {
    modifierWithKey(this._modifiersWithKeys, WebCopyOptionsModifier.identity, WebCopyOptionsModifier, value);
    return this;
  }
  onNavigationEntryCommitted(callback: OnNavigationEntryCommittedCallback): this{
    modifierWithKey(this._modifiersWithKeys, WebOnNavigationEntryCommittedModifier.identity, WebOnNavigationEntryCommittedModifier, callback);
    return this;
  }
  onSafeBrowsingCheckResult(callback: OnSafeBrowsingCheckResultCallback): this{
    modifierWithKey(this._modifiersWithKeys, WebOnSafeBrowsingCheckResultModifier.identity, WebOnSafeBrowsingCheckResultModifier, callback);
    return this;
  }
  gestureFocusMode(mode: GestureFocusMode): this {
    modifierWithKey(this._modifiersWithKeys, WebGestureFocusModeModifier.identity, WebGestureFocusModeModifier, mode);
    return this;
  }
}

// @ts-ignore
globalThis.Web.attributeModifier = function (modifier: ArkComponent): void {
  attributeModifierFunc.call(this, modifier, (nativePtr: KNode) => {
    return new ArkWebComponent(nativePtr);
  }, (nativePtr: KNode, classType: ModifierType, modifierJS: ModifierJS) => {
    return new modifierJS.CommonModifier(nativePtr, classType);
  });
};

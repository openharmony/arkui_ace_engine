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
    throw new Error('Method not implemented.');
  }
  domStorageAccess(domStorageAccess: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebDomStorageAccessModifier.identity, WebDomStorageAccessModifier, domStorageAccess);
    return this;
  }
  imageAccess(imageAccess: boolean): this {
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
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
    throw new Error('Method not implemented.');
  }
  mediaOptions(options: WebMediaOptions): this {
    throw new Error('Method not implemented.');
  }
  tableData(tableData: boolean): this {
    throw new Error('Method not implemented.');
  }
  wideViewModeAccess(wideViewModeAccess: boolean): this {
    throw new Error('Method not implemented.');
  }
  overviewModeAccess(overviewModeAccess: boolean): this {
    throw new Error('Method not implemented.');
  }
  overScrollMode(mode: OverScrollMode): this {
    throw new Error('Method not implemented.');
  }
  textZoomAtio(textZoomAtio: number): this {
    throw new Error('Method not implemented.');
  }
  textZoomRatio(textZoomRatio: number): this {
    throw new Error('Method not implemented.');
  }
  databaseAccess(databaseAccess: boolean): this {
    throw new Error('Method not implemented.');
  }
  initialScale(percent: number): this {
    throw new Error('Method not implemented.');
  }
  userAgent(userAgent: string): this {
    throw new Error('Method not implemented.');
  }
  onPageEnd(callback: (event?: { url: string; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onPageBegin(callback: (event?: { url: string; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onProgressChange(callback: (event?: { newProgress: number; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onTitleReceive(callback: (event?: { title: string; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onGeolocationHide(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onGeolocationShow(callback: (event?: { origin: string; geolocation: JsGeolocation; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onRequestSelected(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onAlert(callback: (event?: { url: string; message: string; result: JsResult; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onBeforeUnload(callback: (event?: { url: string; message: string; result: JsResult; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onConfirm(callback: (event?: { url: string; message: string; result: JsResult; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onPrompt(callback: (event?: { url: string; message: string; value: string; result: JsResult; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onConsole(callback: (event?: { message: ConsoleMessage; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onErrorReceive(callback: (event?: { request: WebResourceRequest; error: WebResourceError; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onHttpErrorReceive(callback: (event?: { request: WebResourceRequest; response: WebResourceResponse; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onDownloadStart(callback: (event?: {
    url: string;
    userAgent: string; contentDisposition: string;
    mimetype: string; contentLength: number;
  } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onRefreshAccessedHistory(callback: (event?: { url: string; isRefreshed: boolean; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onUrlLoadIntercept(callback: (event?: { data: string | WebResourceRequest; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onSslErrorReceive(callback: (event?: { handler: Function; error: object; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onRenderExited(callback: (event?: { renderExitReason: RenderExitReason; } | undefined) => void): this;
  onRenderExited(callback: (event?: { detail: object; } | undefined) => boolean): this;
  onRenderExited(callback: unknown): this {
    throw new Error('Method not implemented.');
  }
  onShowFileSelector(callback: (event?: { result: FileSelectorResult; fileSelector: FileSelectorParam; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onFileSelectorShow(callback: (event?: { callback: Function; fileSelector: object; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onResourceLoad(callback: (event: { url: string; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onFullScreenExit(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onFullScreenEnter(callback: (event: { handler: FullScreenExitHandler; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onScaleChange(callback: (event: { oldScale: number; newScale: number; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onHttpAuthRequest(callback: (event?: { handler: HttpAuthHandler; host: string; realm: string; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onInterceptRequest(callback: (event?: { request: WebResourceRequest; } | undefined) => WebResourceResponse): this {
    throw new Error('Method not implemented.');
  }
  onPermissionRequest(callback: (event?: { request: PermissionRequest; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onScreenCaptureRequest(callback: (event?: { handler: ScreenCaptureHandler; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onContextMenuShow(callback: (event?: { param: WebContextMenuParam; result: WebContextMenuResult; } | undefined) => boolean): this {
    throw new Error('Method not implemented.');
  }
  mediaPlayGestureAccess(access: boolean): this {
    throw new Error('Method not implemented.');
  }
  onSearchResultReceive(callback: (event?: { activeMatchOrdinal: number; numberOfMatches: number; isDoneCounting: boolean; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onScroll(callback: (event: { xOffset: number; yOffset: number; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onSslErrorEventReceive(callback: (event: { handler: SslErrorHandler; error: SslError; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onSslErrorEvent(callback: (event: { handler: SslErrorHandler; error: SslError; url: string;
    originalUrl: string; referrer: string; isFatalError: boolean; isMainFrame: boolean; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onClientAuthenticationRequest(callback: (event: {
    handler: ClientAuthenticationHandler;
    host: string; port: number; keyTypes: string[]; issuers: string[];
  }) => void): this {
    throw new Error('Method not implemented.');
  }
  onWindowNew(callback: (event: { isAlert: boolean; isUserTrigger: boolean; targetUrl: string; handler: ControllerHandler; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onWindowExit(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  multiWindowAccess(multiWindow: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebMultiWindowAccessModifier.identity, WebMultiWindowAccessModifier, multiWindow);
    return this;
  }
  onInterceptKeyEvent(callback: (event: KeyEvent) => boolean): this {
    throw new Error('Method not implemented.');
  }
  webStandardFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  webSerifFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  webSansSerifFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  webFixedFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  webFantasyFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  webCursiveFont(family: string): this {
    throw new Error('Method not implemented.');
  }
  defaultFixedFontSize(size: number): this {
    throw new Error('Method not implemented.');
  }
  defaultFontSize(size: number): this {
    throw new Error('Method not implemented.');
  }
  minFontSize(size: number): this {
    throw new Error('Method not implemented.');
  }
  minLogicalFontSize(size: number): this {
    throw new Error('Method not implemented.');
  }
  blockNetwork(block: boolean): this {
    throw new Error('Method not implemented.');
  }
  horizontalScrollBarAccess(horizontalScrollBar: boolean): this {
    throw new Error('Method not implemented.');
  }
  verticalScrollBarAccess(verticalScrollBar: boolean): this {
    throw new Error('Method not implemented.');
  }
  onTouchIconUrlReceived(callback: (event: { url: string; precomposed: boolean; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onFaviconReceived(callback: (event: { favicon: any; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onPageVisible(callback: (event: { url: string; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onDataResubmitted(callback: (event: { handler: DataResubmissionHandler; }) => void): this {
    throw new Error('Method not implemented.');
  }
  pinchSmooth(isEnabled: boolean): this {
    throw new Error('Method not implemented.');
  }
  allowWindowOpenMethod(flag: boolean): this {
    modifierWithKey(this._modifiersWithKeys, WebAllowWindowOpenMethodModifier.identity, WebAllowWindowOpenMethodModifier, flag);
    return this;
  }
  onAudioStateChanged(callback: (event: { playing: boolean; }) => void): this {
    throw new Error('Method not implemented.');
  }
  onFirstContentfulPaint(callback: (event?: { navigationStartTick: number; firstContentfulPaintMs: number; } | undefined) => void): this {
    throw new Error('Method not implemented.');
  }
  onLoadIntercept(callback: (event: { data: WebResourceRequest; }) => boolean): this {
    throw new Error('Method not implemented.');
  }
  onControllerAttached(callback: () => void): this {
    throw new Error('Method not implemented.');
  }
  onOverScroll(callback: (event: { xOffset: number; yOffset: number; }) => void): this {
    throw new Error('Method not implemented.');
  }
  javaScriptOnDocumentStart(scripts: ScriptItem[]): this {
    throw new Error('Method not implemented.');
  }
  layoutMode(mode: WebLayoutMode): this {
    throw new Error('Method not implemented.');
  }
  nestedScroll(value: NestedScrollOptions): this {
    throw new Error('Method not implemented.');
  }
  onOverrideUrlLoading(callback: OnOverrideUrlLoadingCallback): this {
    throw new Error('Method not implemented.');
  }
  enableNativeMediaPlayer(config: NativeMediaPlayerConfig): this {
    throw new Error('Method not implemented.');
  }
  onRenderProcessNotResponding(callback: OnRenderProcessNotRespondingCallback): this {
    throw new Error('Method not implemented.');
  }
  onRenderProcessResponding(callback: OnRenderProcessRespondingCallback): this {
    throw new Error('Method not implemented.');
  }
  onViewportFitChanged(callback: OnViewportFitChangedCallback): this {
    throw new Error('Method not implemented.');
  }
  onAdsBlockedBlock(callback: (details: { url: string; adsBlocked: string[]; } | undefined) => void): this {
    throw new Error('Method not implemented.');
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

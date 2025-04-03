/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import { nullptr, pointer } from "@koalaui/interop";
import { WebCookie } from "../generated/ArkWebCookieMaterialized";
import { ArkUIGeneratedNativeModule } from "../generated/ArkUIGeneratedNativeModule";

interface RunJavaScriptType {
    script: string;
    callback?: (result: string) => void;
}
interface LoadDataType {
    data: string;
    mimeType: string;
    encoding: string;
    baseUrl?: string;
    historyUrl?: string;
}
interface LoadUrlType {
    url: string | Resource;
    headers?: Array<Header>;
}
interface RegisterJavaScriptProxyType {
    object: object;
    name: string;
    methodList: Array<string>;
}
export class WebController {
    private nativePointer: pointer = nullptr
    setNativeController(node: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._WebController_Get_(node)
    }
    constructor() { }
    onInactive(): void {
        throw new Error("[WebController.onInactive] - method not implemented.");
    }
    onActive(): void {
        throw new Error("[WebController.onActive] - method not implemented.");
    }
    zoom(factor: number): void {
        throw new Error("[WebController.zoom] - method not implemented.");
    }
    clearHistory(): void {
        throw new Error("[WebController.clearHistory] - method not implemented.");
    }
    runJavaScript(options: RunJavaScriptType) {
        throw new Error("[WebController.runJavaScript] - method not implemented.");
    }
    loadData(options: LoadDataType) {
        throw new Error("[WebController.loadData] - method not implemented.");
    }
    loadUrl(options: LoadUrlType) {
        throw new Error("[WebController.loadUrl] - method not implemented.");
    }
    refresh() {
        throw new Error("[WebController.refresh] - method not implemented.");
    }
    stop() {
        throw new Error("[WebController.stop] - method not implemented.");
    }
    registerJavaScriptProxy(options: RegisterJavaScriptProxyType) {
        throw new Error("[WebController.registerJavaScriptProxy] - method not implemented.");
    }
    deleteJavaScriptRegister(name: string) {
        throw new Error("[WebController.deleteJavaScriptRegister] - method not implemented.");
    }
    getHitTest(): HitTestType {
        throw new Error("[WebController.getHitTest] - method not implemented.");
    }
    requestFocus() {
        throw new Error("[WebController.requestFocus] - method not implemented.");
    }
    accessBackward(): boolean {
        throw new Error("[WebController.accessBackward] - method not implemented.");
    }
    accessForward(): boolean {
        throw new Error("[WebController.accessForward] - method not implemented.");
    }
    accessStep(step: number): boolean {
        throw new Error("[WebController.accessStep] - method not implemented.");
    }
    backward() {
        throw new Error("[WebController.backward] - method not implemented.");
    }
    forward() {
        throw new Error("[WebController.forward] - method not implemented.");
    }
    getCookieManager(): WebCookie {
        throw new Error("[WebController.getCookieManager] - method not implemented.");
    }
}

// TODO: proper import types form ets/api for WebviewController
interface WebHeader { }
enum SecureDnsMode { }
enum WebHitTestType { }
interface BackForwardList { }
interface HitTestValue { }
interface WebMessagePort { }
interface WebCustomScheme { }
class AsyncCallback<T> { }
class JsMessageExt { }
declare namespace cert {
    interface X509Cert { }
}

export namespace webview {
    export class WebviewController {
        private nativePointer: pointer = nullptr
        setNativeController(node: pointer) {
            // TODO: refactor code accordingly to Serializer
            // this.nativePointer = ArkUIGeneratedNativeModule._WebAttribute_Get_viewController(node)
        }

        static initializeWebEngine(): void {
            throw new Error("[WebviewController.static] - method not implemented.")
        }
        static setHttpDns(secureDnsMode: SecureDnsMode, secureDnsConfig: string): void {
            throw new Error("[WebviewController.static] - method not implemented.")
        }
        static setWebDebuggingAccess(webDebuggingAccess: boolean): void {
            throw new Error("[WebviewController.static] - method not implemented.")
        }
        accessForward(): boolean {
            throw new Error("[WebviewController.accessForward] - method not implemented.")
        }
        accessBackward(): boolean {
            throw new Error("[WebviewController.accessBackward] - method not implemented.")
        }
        accessStep(step: number): boolean {
            throw new Error("[WebviewController.accessStep] - method not implemented.")
        }
        forward(): void {
            throw new Error("[WebviewController.forward] - method not implemented.")
        }
        backward(): void {
            throw new Error("[WebviewController.backward] - method not implemented.")
        }
        clearHistory(): void {
            throw new Error("[WebviewController.clearHistory] - method not implemented.")
        }
        onActive(): void {
            throw new Error("[WebviewController.onActive] - method not implemented.")
        }
        onInactive(): void {
            throw new Error("[WebviewController.onInactive] - method not implemented.")
        }
        refresh(): void {
            throw new Error("[WebviewController.refresh] - method not implemented.")
        }
        loadData(data: string, mimeType: string, encoding: string, baseUrl?: string, historyUrl?: string): void {
            throw new Error("[WebviewController.loadData] - method not implemented.")
        }
        loadUrl(url: string | Resource, headers?: Array<WebHeader>): void {
            throw new Error("[WebviewController.loadUrl] - method not implemented.")
        }
        getHitTest(): WebHitTestType {
            throw new Error("[WebviewController.getHitTest] - method not implemented.")
        }
        storeWebArchivePromise(baseName: string, autoName: boolean): Promise<string> {
            throw new Error("[WebviewController.storeWebArchive] - method not implemented.")
        }
        storeWebArchiveAsync(baseName: string, autoName: boolean, callback: AsyncCallback<string>): void {
            throw new Error("[WebviewController.storeWebArchive] - method not implemented.")
        }
        zoom(factor: number): void {
            throw new Error("[WebviewController.zoom] - method not implemented.")
        }
        zoomIn(): void {
            throw new Error("[WebviewController.zoomIn] - method not implemented.")
        }
        zoomOut(): void {
            throw new Error("[WebviewController.zoomOut] - method not implemented.")
        }
        getHitTestValue(): HitTestValue {
            throw new Error("[WebviewController.getHitTestValue] - method not implemented.")
        }
        getWebId(): number {
            throw new Error("[WebviewController.getWebId] - method not implemented.")
        }
        getUserAgent(): string {
            throw new Error("[WebviewController.getUserAgent] - method not implemented.")
        }
        getTitle(): string {
            throw new Error("[WebviewController.getTitle] - method not implemented.")
        }
        getPageHeight(): number {
            throw new Error("[WebviewController.getPageHeight] - method not implemented.")
        }
        backOrForward(step: number): void {
            throw new Error("[WebviewController.backOrForward] - method not implemented.")
        }
        requestFocus(): void {
            throw new Error("[WebviewController.requestFocus] - method not implemented.")
        }
        createWebMessagePorts(isExtentionType?: boolean): Array<WebMessagePort> {
            throw new Error("[WebviewController.createWebMessagePorts] - method not implemented.")
        }
        postMessage(name: string, ports: Array<WebMessagePort>, uri: string): void {
            throw new Error("[WebviewController.postMessage] - method not implemented.")
        }
        stop(): void {
            throw new Error("[WebviewController.stop] - method not implemented.")
        }
        registerJavaScriptProxy(object: object, name: string, methodList: Array<string>): void {
            throw new Error("[WebviewController.registerJavaScriptProxy] - method not implemented.")
        }
        deleteJavaScriptRegister(name: string): void {
            throw new Error("[WebviewController.deleteJavaScriptRegister] - method not implemented.")
        }
        searchAllAsync(searchString: string): void {
            throw new Error("[WebviewController.searchAllAsync] - method not implemented.")
        }
        clearMatches(): void {
            throw new Error("[WebviewController.clearMatches] - method not implemented.")
        }
        searchNext(forward: boolean): void {
            throw new Error("[WebviewController.searchNext] - method not implemented.")
        }
        clearSslCache(): void {
            throw new Error("[WebviewController.clearSslCache] - method not implemented.")
        }
        clearClientAuthenticationCache(): void {
            throw new Error("[WebviewController.clearClientAuthenticationCache] - method not implemented.")
        }
        runJavaScriptPromise(script: string): Promise<string> {
            throw new Error("[WebviewController.runJavaScript] - method not implemented.")
        }
        runJavaScriptAsync(script: string, callback: AsyncCallback<string>): void {
            throw new Error("[WebviewController.runJavaScript] - method not implemented.")
        }
        runJavaScriptExtPromise(script: string): Promise<JsMessageExt> {
            throw new Error("[WebviewController.runJavaScriptExt] - method not implemented.")
        }
        runJavaScriptExtAsync(script: string, callback: AsyncCallback<JsMessageExt>): void {
            throw new Error("[WebviewController.runJavaScriptExt] - method not implemented.")
        }
        getUrl(): string {
            throw new Error("[WebviewController.getUrl] - method not implemented.")
        }
        pageUp(top: boolean): void {
            throw new Error("[WebviewController.pageUp] - method not implemented.")
        }
        pageDown(bottom: boolean): void {
            throw new Error("[WebviewController.pageDown] - method not implemented.")
        }
        getOriginalUrl(): string {
            throw new Error("[WebviewController.getOriginalUrl] - method not implemented.")
        }
        getFavicon(): PixelMap {
            throw new Error("[WebviewController.getFavicon] - method not implemented.")
        }
        setNetworkAvailable(enable: boolean): void {
            throw new Error("[WebviewController.setNetworkAvailable] - method not implemented.")
        }
        hasImagePromise(): Promise<boolean> {
            throw new Error("[WebviewController.hasImage] - method not implemented.")
        }
        hasImageAsync(callback: AsyncCallback<boolean>): void {
            throw new Error("[WebviewController.hasImage] - method not implemented.")
        }
        getBackForwardEntries(): BackForwardList {
            throw new Error("[WebviewController.getBackForwardEntries] - method not implemented.")
        }
        removeCache(clearRom: boolean): void {
            throw new Error("[WebviewController.removeCache] - method not implemented.")
        }
        scrollTo(x: number, y: number): void {
            throw new Error("[WebviewController.scrollTo] - method not implemented.")
        }
        scrollBy(deltaX: number, deltaY: number): void {
            throw new Error("[WebviewController.scrollBy] - method not implemented.")
        }
        slideScroll(vx: number, vy: number): void {
            throw new Error("[WebviewController.slideScroll] - method not implemented.")
        }
        serializeWebState(): Uint8Array {
            throw new Error("[WebviewController.serializeWebState] - method not implemented.")
        }
        restoreWebState(state: Uint8Array): void {
            throw new Error("[WebviewController.restoreWebState] - method not implemented.")
        }
        static customizeSchemes(schemes: Array<WebCustomScheme>): void {
            throw new Error("[WebviewController.static] - method not implemented.")
        }
        getCertificatePromise(): Promise<Array<cert.X509Cert>> {
            throw new Error("[WebviewController.getCertificate] - method not implemented.")
        }
        getCertificateAsync(callback: AsyncCallback<Array<cert.X509Cert>>): void {
            throw new Error("[WebviewController.getCertificate] - method not implemented.")
        }
        setAudioMuted(mute: boolean): void {
            throw new Error("[WebviewController.setAudioMuted] - method not implemented.")
        }
        prefetchPage(url: string, additionalHeaders?: Array<WebHeader>): void {
            throw new Error("[WebviewController.prefetchPage] - method not implemented.")
        }
        static prepareForPageLoad(url: string, preconnectable: boolean, numSockets: number): void {
            throw new Error("[WebviewController.static] - method not implemented.")
        }
        setCustomUserAgent(userAgent: string): void {
            throw new Error("[WebviewController.setCustomUserAgent] - method not implemented.")
        }
        getCustomUserAgent(): string {
            throw new Error("[WebviewController.getCustomUserAgent] - method not implemented.")
        }
    }
}

abstract class TextContentControllerBase {
    getCaretOffset(): CaretOffset {
        throw new Error("[TextContentControllerBase.getCaretOffset] - method not implemented.")
    }
    getTextContentRect(): RectResult {
        throw new Error("[TextContentControllerBase.getTextContentRect] - method not implemented.")
    }
    getTextContentLineCount(): number {
        throw new Error("[TextContentControllerBase.getTextContentLineCount] - method not implemented.")
    }
}

export class TextInputController {
    private nativePointer: pointer = nullptr
    setNativeController(node: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._TextInputController_Get_(node)
    }
    caretPosition(value: number): void {
        throw new Error("[TextInputController.caretPosition] - method not implemented.")
    }
    setTextSelection(selectionStart: number, selectionEnd: number): void {
        throw new Error("[TextInputController.setTextSelection] - method not implemented.")
    }
    stopEditing(): void {
        throw new Error("[TextInputController.stopEditing] - method not implemented.")
    }
}

export class TextClockController {
    private nativePointer: pointer = nullptr
    constructor() {
    }
    start() {
        if (this.nativePointer) {
            ArkUIGeneratedNativeModule._TextClockController_start(this.nativePointer)
        }
    }
    stop() {
        if (this.nativePointer) {
            ArkUIGeneratedNativeModule._TextClockController_stop(this.nativePointer)
        }
    }
    setNativeController(TextClockNode: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._TextClockController_Get_(TextClockNode)
    }
}

export class TextTimerController {
    private nativePointer: pointer = nullptr
    constructor() {
    }
    start() {
        if (this.nativePointer) {
            ArkUIGeneratedNativeModule._TextTimerController_start(this.nativePointer)
        }
    }
    pause() {
        if (this.nativePointer) {
            ArkUIGeneratedNativeModule._TextTimerController_pause(this.nativePointer)
        }
    }
    reset() {
        if (this.nativePointer) {
            ArkUIGeneratedNativeModule._TextTimerController_reset(this.nativePointer)
        }
    }
    setNativeController(TextTimer: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._TextTimerController_Get_(TextTimer)
    }
}

export class RichEditorController {
    private nativePointer: pointer = nullptr
    setNativeController(node: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._RichEditorController_Get_(node)
    }

    getCaretOffset(): number {
        throw new Error("Method not implemented.");
    }
    setCaretOffset(offset: number): boolean {
        throw new Error("Method not implemented.");
    }
    addTextSpan(value: string, options?: RichEditorTextSpanOptions | undefined): number {
        throw new Error("Method not implemented.");
    }
    addImageSpan(value: PixelMap | ResourceStr, options?: RichEditorImageSpanOptions | undefined): number {
        throw new Error("Method not implemented.");
    }
    updateSpanStyle(value: RichEditorUpdateTextSpanStyleOptions | RichEditorUpdateImageSpanStyleOptions): void {
        throw new Error("Method not implemented.");
    }
    deleteSpans(value?: RichEditorRange | undefined): void {
        throw new Error("Method not implemented.");
    }
    getSpans(value?: RichEditorRange | undefined): (RichEditorTextSpanResult | RichEditorImageSpanResult)[] {
        throw new Error("Method not implemented.");
    }
    closeSelectionMenu(): void {
        throw new Error("Method not implemented.");
    }
}

export class TextAreaController {
    private nativePointer: pointer = nullptr
    constructor() {
    }
    caretPosition(value: number): void {
        throw new Error("Method not implemented.");
    }
    setTextSelection(selectionStart: number, selectionEnd: number): void {
        throw new Error("Method not implemented.");
    }
    stopEditing(): void {
        throw new Error("Method not implemented.");
    }
    getCaretOffset(): CaretOffset {
        throw new Error("Method not implemented.");
    }
    getTextContentRect(): RectResult {
        throw new Error("Method not implemented.");
    }
    getTextContentLineCount(): number {
        throw new Error("Method not implemented.");
    }
    setNativeController(TextArea: pointer) {
        // TODO: refactor code accordingly to Serializer
        // this.nativePointer = ArkUIGeneratedNativeModule._TextAreaController_Get_(TextArea)
    }
}

export class SwiperController {
    private nativePointer: pointer = nullptr

    constructor() {
    }

    showNext(): void {
        throw new Error("Method not implemented.")
    }
    showPrevious(): void {
        throw new Error("Method not implemented.")
    }
    changeIndex(index: number, useAnimation?: boolean): void {
        throw new Error("Method not implemented.")
    }
    finishAnimation(callback?: () => void): void {
        throw new Error("Method not implemented.")
    }
}


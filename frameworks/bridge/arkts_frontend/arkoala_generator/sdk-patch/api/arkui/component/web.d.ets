'use static'
/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
/**
 * @file
 * @kit ArkWeb
 */
import webview from '../../@ohos.web.webview';
import image from '../../@ohos.multimedia.image';
import { CommonMethod, Callback, TouchEvent, MouseEvent, NestedScrollOptions, KeyEvent, HapticFeedbackMode } from './common';
import { CustomBuilder } from './builder';
import { Resource } from '../../global/resource';
import { Position, ResourceStr, VoidCallback } from './units';
import { MenuType, EditMenuOptions, TextDataDetectorConfig } from './textCommon';
import { CopyOptions, NestedScrollMode } from './enums';
import { PreviewMenuOptions } from './richEditor';
import { ComponentBuilder } from './builder';
import { AttributeModifier, CommonMethod } from "./common";
/**
 * Provides methods for controlling the web controller.
 *
 * @typedef { webview.WebviewController }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type WebviewController = webview.WebviewController;
/**
 * The callback of load committed.
 *
 * @typedef { function } OnNavigationEntryCommittedCallback
 * @param { LoadCommittedDetails } loadCommittedDetails - callback information of onNavigationEntryCommitted.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnNavigationEntryCommittedCallback = (loadCommittedDetails: LoadCommittedDetails) => void;
/**
 * The callback of ssl error event.
 *
 * @typedef { function } OnSslErrorEventCallback
 * @param { SslErrorEvent } sslErrorEvent - callback information of onSslErrorEvent.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnSslErrorEventCallback = (sslErrorEvent: SslErrorEvent) => void;
/**
 * The callback of verify pin.
 *
 * @typedef { function } OnVerifyPinCallback
 * @param { VerifyPinEvent } verifyPinEvent - The event of verify PIN.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnVerifyPinCallback = (verifyPinEvent: VerifyPinEvent) => void;
/**
 * The callback of onOverrideErrorPage.
 *
 * @typedef { function } OnOverrideErrorPageCallback
 * @param { OnErrorReceiveEvent } errorPageEvent - The information of error.
 * @returns { string } - Return an HTML text content encoded in Base64.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnOverrideErrorPageCallback = (errorPageEvent: OnErrorReceiveEvent) => string;
/**
 * The callback of largestContentfulPaint.
 *
 * @typedef { function } OnLargestContentfulPaintCallback
 * @param { LargestContentfulPaint } largestContentfulPaint - callback information of onLargestContentfulPaint.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnLargestContentfulPaintCallback = (largestContentfulPaint: LargestContentfulPaint) => void;
/**
 * The callback of firstMeaningfulPaint.
 *
 * @typedef { function } OnFirstMeaningfulPaintCallback
 * @param { FirstMeaningfulPaint } firstMeaningfulPaint - callback information of onFirstMeaningfulPaint.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnFirstMeaningfulPaintCallback = (firstMeaningfulPaint: FirstMeaningfulPaint) => void;
/**
 * The callback of onOverrideUrlLoading.
 * Should not call WebviewController.loadUrl with the request's URL and then return true.
 *
 * @typedef { function } OnOverrideUrlLoadingCallback
 * @param { WebResourceRequest } webResourceRequest - callback information of onOverrideUrlLoading.
 * @returns { boolean } - Returning true causes the current Web to abort loading the URL,
 *                        false causes the Web to continue loading the url as usual.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnOverrideUrlLoadingCallback = (webResourceRequest: WebResourceRequest) => boolean;
/**
 * The callback of Intelligent Tracking Prevention.
 *
 * @typedef { function } OnIntelligentTrackingPreventionCallback
 * @param { IntelligentTrackingPreventionDetails } details - callback information of onIntelligentTrackingPrevention.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnIntelligentTrackingPreventionCallback = (details: IntelligentTrackingPreventionDetails) => void;
/**
 * The callback of onNativeEmbedVisibilityChange.
 *
 * @typedef { function } OnNativeEmbedVisibilityChangeCallback
 * @param { NativeEmbedVisibilityInfo } nativeEmbedVisibilityInfo - callback information of onNativeEmbedVisibilityChange.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnNativeEmbedVisibilityChangeCallback = (nativeEmbedVisibilityInfo: NativeEmbedVisibilityInfo) => void;
/**
 * The callback when the param element which is a child item of the object element has changed.
 *
 * @typedef { function } OnNativeEmbedObjectParamChangeCallback
 * @param { NativeEmbedParamDataInfo } event - callback information of param element.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnNativeEmbedObjectParamChangeCallback = (event: NativeEmbedParamDataInfo) => void;
/**
 * Enum type supplied to {@link NativeEmbedParamItem} when onNativeEmbedObjectParamChange being called.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum NativeEmbedParamStatus {
    /**
     * The param element is created.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ADD = 0,
    /**
     * The param element is updated.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    UPDATE = 1,
    /**
     *The param element is deleted.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DELETE = 2
}

/**
* Enum type supplied to {@link keyboardAppearance} for setting the web keyboard appearance mode.
*
* @enum { number }
* @syscap SystemCapability.Web.Webview.Core
* @stagemodelonly
* @since 26.0.0
*/
export declare enum WebKeyboardAppearanceMode {
/**
* Default skin mode, no immersive style.
*
* @syscap SystemCapability.Web.Webview.Core
* @stagemodelonly
* @since 26.0.0
*/
NONE_IMMERSIVE = 0,

/**
* No immersive style.
*
* @syscap SystemCapability.Web.Webview.Core
* @stagemodelonly
* @since 26.0.0
*/
IMMERSIVE = 1,

/**
*Light immersive style.
*
* @syscap SystemCapability.Web.Webview.Core
* @stagemodelonly
* @since 26.0.0
*/
LIGHT_IMMERSIVE = 2,

/**
*Dark immersive style.
*
* @syscap SystemCapability.Web.Webview.Core
* @stagemodelonly
* @since 26.0.0
*/
DARK_IMMERSIVE = 3
}

/**
 * Defines the information of param element.
 *
 * @typedef NativeEmbedParamItem
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedParamItem {
    /**
     * The status of the param.
     *
     * @type { NativeEmbedParamStatus }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    status: NativeEmbedParamStatus;
    /**
     * The id attribute of the param element.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    id: string;
    /**
     * The name attribute of the param element.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    name?: string;
    /**
     * The value attribute of the param element.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    value?: string;
}
/**
 * Defines the param data info.
 *
 * @typedef NativeEmbedParamDataInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedParamDataInfo {
    /**
     * The native embed id.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    embedId: string;
    /**
     * The id attribute of the object element.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    objectAttributeId?: string;
    /**
     * The param element array
     *
     * @type { ?Array<NativeEmbedParamItem> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    paramItems?: Array<NativeEmbedParamItem>;
}
/**
 * Enum type supplied to {@link rotateRenderEffect} for setting the effect of rotation.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebRotateEffect {
    /**
     * The content area is drawn in top-left of the node.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    TOPLEFT_EFFECT = 0,
    /**
     * Scale the content area to cover the node.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    RESIZE_COVER_EFFECT = 1
}
/**
 * The configuration of native media player.
 *
 * @typedef NativeMediaPlayerConfig
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeMediaPlayerConfig {
    /**
     * Whether to enable the application to take over the webpage media playback function.
     *
     * @type { boolean }
     *    {@code true} means to enable the application to take over the web media playback function, {@code false} otherwise.
     *    Deflault value: false.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    enable: boolean;
    /**
     * Whether the video player's display overlays the web page content when the application takes over the web page's video player.
     *
     * @type { boolean }
     *    {@code true} means changing the height of the video layer to cover the content of the webpage, {@code false} otherwise.
     *    Deflault value: false.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    shouldOverlay: boolean;
}
/**
 * The callback of render process not responding.
 *
 * @typedef { function } OnRenderProcessNotRespondingCallback
 * @param { RenderProcessNotRespondingData } data - details of onRenderProcessNotResponding.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnRenderProcessNotRespondingCallback = (data: RenderProcessNotRespondingData) => void;
/**
 * The callback of render process responding.
 *
 * @typedef { function } OnRenderProcessRespondingCallback
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnRenderProcessRespondingCallback = () => void;
/**
 * The callback of ViewportFit Changed.
 *
 * @typedef { function } OnViewportFitChangedCallback
 * @param { ViewportFit } viewportFit - details of OnViewportFitChangedCallback.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnViewportFitChangedCallback = (viewportFit: ViewportFit) => void;
/**
 * The callback of ads block
 *
 * @typedef { function } OnAdsBlockedCallback
 * @param { AdsBlockedDetails } details - details of OnAdsBlockedCallback.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnAdsBlockedCallback = (details: AdsBlockedDetails) => void;
/**
 * The callback when camera capturing state of current page has been changed.
 *
 * @typedef { function } OnCameraCaptureStateChangeCallback
 * @param { CameraCaptureStateChangeInfo } event - the camera capturing state event.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnCameraCaptureStateChangeCallback = (event: CameraCaptureStateChangeInfo) => void;

/**
 * The callback when microphone capturing state of current page has been changed.
 *
 * @typedef { function } OnMicrophoneCaptureStateChangeCallback
 * @param { MicrophoneCaptureStateChangeInfo } event - the microphone capturing state event.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnMicrophoneCaptureStateChangeCallback = (event: MicrophoneCaptureStateChangeInfo) => void;
/**
 * Defines the ads block details.
 *
 * @interface AdsBlockedDetails
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface AdsBlockedDetails {
    /**
     * The url of main frame.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * the url of ads.
     *
     * @type { Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    adsBlocked: Array<string>;
}
/**
 * Defines the web keyboard options when onInterceptKeyboardAttach event return.
 *
 * @interface WebKeyboardOptions
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface WebKeyboardOptions {
    /**
     * Whether the system keyboard is used.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    useSystemKeyboard: boolean;
    /**
     * Set the enter key type when the system keyboard is used, the "enter" key related to the {@link inputMethodEngine}.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    enterKeyType?: int;
    /**
     * Set the custom keyboard builder when the custom keyboard is used.
     *
     * @type { ?CustomBuilder }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    customKeyboard?: CustomBuilder;
}
/**
 * Define the controller to interact with a custom keyboard, related to the {@link onInterceptKeyboardAttach} event.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebKeyboardController {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Insert characters in the Web input field.
     *
     * @param { string } text - text which will be inserted.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    insertText(text: string): void;
    /**
     * Deletes the specified length of characters from the back to the front in the Web input field.
     *
     * @param { int } length - length of text, which will be deleted from back to front.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    deleteForward(length: int): void;
    /**
     * Delete the specified length of characters in the Web input field from the beginning to the end.
     *
     * @param { int } length - length of text, which will be deleted from front to back.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    deleteBackward(length: int): void;
    /**
     * Send the function of the key.
     *
     * @param { int } key - action indicates the "enter" key related to the {@link inputMethodEngine}
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    sendFunctionKey(key: int): void;
    /**
     * Close the custom keyboard.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    close(): void;
}
/**
 * Defines the web keyboard callback info related to the {@link onInterceptKeyboardAttach} event.
 *
 * @interface WebKeyboardCallbackInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface WebKeyboardCallbackInfo {
    /**
     * The web keyboard controller.
     *
     * @type { WebKeyboardController }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    controller: WebKeyboardController;
    /**
     * The attributes of web input element.
     *
     * @type { Record<string, string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    attributes: Record<string, string>;
}
/**
 * The callback of onInterceptKeyboardAttach event.
 *
 * @typedef { function } WebKeyboardCallback
 * @param { WebKeyboardCallbackInfo } keyboardCallbackInfo - callback information of onInterceptKeyboardAttach.
 * @returns { WebKeyboardOptions } Return the web keyboard options of this web component.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type WebKeyboardCallback = (keyboardCallbackInfo: WebKeyboardCallbackInfo) => WebKeyboardOptions;
/**
 * Enum type supplied to {@link getMessageLevel} for receiving the console log level of JavaScript.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum MessageLevel {
    /**
     * Debug level.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DEBUG,
    /**
     * Error level.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ERROR,
    /**
     * Info level.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    INFO,
    /**
     * Log level.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LOG,
    /**
     * Warn level.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    WARN
}
/**
 * The source of console message.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ConsoleMessageSource {
  /**
   * Logs generated by the browser's XML/HTML parser (such as HTML syntax errors, XML format exceptions), for example,
   * parsing warnings caused by unclosed HTML tags.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  XML = 0,
  /**
   * JavaScript execution error, such as syntax error or runtime exception.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  JAVASCRIPT = 1,
  /**
   * Web resource loading failure, such as JS/CSS/image 404.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  NETWORK = 2,
  /**
   * Console API usage, such as console.warn or console.error.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  CONSOLE_API = 3,
  /**
   * Logs from storage modules like LocalStorage, SessionStorage, IndexedDB, or Cookie.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  STORAGE = 4,
  /**
   * Logs from rendering engine (e.g., Blink), such as invalid CSS, layout issues, or rendering performance warnings.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  RENDERING = 5,
  /**
   * Security policy violations, such as HTTPS certificate error or mixed content.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  SECURITY = 6,
  /**
   * Other logs, such as those from extensions.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  OTHER = 7,
  /**
   * Usage of deprecated syntax, such as slider-vertical.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  DEPRECATION = 8,
  /**
   * Errors in service worker or shared worker, such as navigation preload being interrupted.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  WORKER = 9,
  /**
   * Rule violations, such as JavaScript execution exceeding 50ms.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  VIOLATION = 10,
  /**
   * Browser intervention due to potential user experience, security, or performance issues.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  INTERVENTION = 11,
  /**
   * Code practices that do not follow web security best practices, with improvement suggestions.
   *
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  RECOMMENDATION = 12
}
/**
 * The Web's behavior to load from HTTP or HTTPS. Defaults to MixedMode.None.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum MixedMode {
    /**
     * Loose Mode: HTTP and HTTPS hybrid content can be loaded. This means that all insecure content can be loaded.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ALL = 0,
    /**
     * Compatibility Modes: HTTP and HTTPS hybrid content can be loaded in compatibility mode. This means that some insecure content may be loaded.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    COMPATIBLE = 1,
    /**
     * Strict Mode: HTTP and HTTPS hybrid content cannot be loaded.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 2
}
/**
 * The callback of safe browsing check.
 *
 * @typedef { function } OnSafeBrowsingCheckResultCallback
 * @param { ThreatType } threatType - callback information of onSafeBrowsingCheckResult.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnSafeBrowsingCheckResultCallback = (threatType: ThreatType) => void;

/**
 * Enum type supplied to {@link cacheMode} for setting the Web cache mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum CacheMode {
    /**
     * load cache when they are available and not expired, otherwise load online.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DEFAULT = 0,
    /**
     * load cache when they are available, otherwise load online.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 1,
    /**
     * Load online and not cache.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ONLINE = 2,
    /**
     * load cache and not online.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ONLY = 3
}
/**
 * Enum type supplied to {@link overScrollMode} for setting the web overScroll mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum OverScrollMode {
    /**
     * Disable the web over-scroll mode.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NEVER = 0,
    /**
     * Enable the web over-scroll mode.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ALWAYS = 1
}
/**
 * Enum type supplied to {@link blurOnKeyboardHideMode} for setting the web blurOnKeyboardHide mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum BlurOnKeyboardHideMode {
    /**
     * The focused input elements on webview will not blur when soft keyboard is hidden manually.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    SILENT = 0,
    /**
     * The focused input elements on webview will blur when soft keyboard is hidden manually.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    BLUR = 1
}
/**
 * Enum type supplied to {@link darkMode} for setting the web dark mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebDarkMode {
    /**
     * Disable the web dark mode.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    OFF = 0,
    /**
     * Enable the web dark mode.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ON = 1,
    /**
     * Make web dark mode follow the system.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    AUTO = 2
}
/**
 * Enum type supplied to {@link captureMode} for setting the web capture mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebCaptureMode {
    /**
     * Capture of the home screen.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    HOME_SCREEN = 0
}
/**
 * Enum type supplied to {@link threatType} for the website's threat type.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ThreatType {
    /**
     * Illegal websites.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_ILLEGAL = 0,
    /**
     * Fraud websites.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_FRAUD = 1,
    /**
     * Websites with security risks.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_RISK = 2,
    /**
     * Websites suspected of containing unhealthy content.
     * ArkWeb will not intercept this type of website and apps could handle it themselves.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_WARNING = 3,
    /**
     * Security check passed, no risks found.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_NONE = 4,
    /**
     * Security check not performed.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    THREAT_UNPROCESSED = 5
}
/**
 * Defines the Media Options.
 *
 * @typedef WebMediaOptions
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface WebMediaOptions {
    /**
     * Validity period for automatically resuming a paused web audio, in seconds.
     * The maximum validity period is 60 seconds. Due to the approximate value,
     * the validity period may have a deviation of less than 1 second.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    resumeInterval?: int;
    /**
     * Whether the audio of multiple Web instances in an application is exclusive.
     *
     * @type { ?boolean }
     *    {@code true} means audio exclusivity for multiple web instances within the application, {@code false} otherwise.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    audioExclusive?: boolean;
    /**
     * The type for audio sessions.
     *
     * @type { ?AudioSessionType }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    audioSessionType?: AudioSessionType;
}
/**
 * Defines the screen capture configuration.
 *
 * @typedef ScreenCaptureConfig
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface ScreenCaptureConfig {
    /**
     * The mode for selecting the recording area.
     *
     * @type { WebCaptureMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    captureMode: WebCaptureMode;
}
/**
 * Define the handler to exit the full screen mode, related to the {@link onFullScreenEnter} event.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class FullScreenExitHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Called when the Web component exits full screen mode.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    exitFullScreen(): void;
}
/**
 * Defines the event details when the web component enter full screen mode.
 *
 * @typedef FullScreenEnterEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface FullScreenEnterEvent {
    /**
     * A function handle to exit full-screen mode.
     *
     * @type { FullScreenExitHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: FullScreenExitHandler;
    /**
     * The intrinsic width of the video if the fullscreen element contains video element, expressed in CSS pixels.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    videoWidth?: int;
    /**
     * The intrinsic height of the video if the fullscreen element contains video element, expressed in CSS pixels.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    videoHeight?: int;
}
/**
 * The callback when the web component enter full screen mode.
 *
 * @typedef { function } OnFullScreenEnterCallback
 * @param { FullScreenEnterEvent } event - callback information of onFullScreenEnter.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnFullScreenEnterCallback = (event: FullScreenEnterEvent) => void;
/**
 * The callback when mouse event is triggered in native embed area
 *
 * @typedef { function } MouseInfoCallback
 * @param { NativeEmbedMouseInfo } event - callback information of mouse event in native embed area.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type MouseInfoCallback = (event: NativeEmbedMouseInfo) => void;
/**
 * Enum type supplied to {@link renderExitReason} when onRenderExited being called.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum RenderExitReason {
    /**
     * Render process non-zero exit status.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PROCESS_ABNORMAL_TERMINATION = 0,
    /**
     * SIGKILL or task manager kill.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PROCESS_WAS_KILLED = 1,
    /**
     * The rendering process crashes and exits, such as a segment error.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PROCESS_CRASHED = 2,
    /**
     * Out of memory.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PROCESS_OOM = 3,
    /**
     * Unknown reason.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PROCESS_EXIT_UNKNOWN = 4
}
/**
 * The callback of custom hide of the context menu.
 *
 * @typedef { function } OnContextMenuHideCallback
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnContextMenuHideCallback = () => void;
/**
 * Enum type supplied to {@link error} when onSslErrorEventReceive being called.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum SslError {
    /**
     * General error.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    INVALID = 0,
    /**
     * Hostname mismatch.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    HOST_MISMATCH = 1,
    /**
     * The certificate date is invalid.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DATE_INVALID = 2,
    /**
     * The certificate authority is not trusted.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    UNTRUSTED = 3
}
/**
 * Enum type supplied to {@link FileSelectorParam} when onFileSelectorShow being called.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum FileSelectorMode {
    /**
     * Allows single file to be selected.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    FILE_OPEN_MODE = 0,
    /**
     * Allows multiple files to be selected.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    FILE_OPEN_MULTIPLE_MODE = 1,
    /**
     * Allows file folders to be selected.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    FILE_OPEN_FOLDER_MODE = 2,
    /**
     * Allows select files to save.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    FILE_SAVE_MODE = 3
}
/**
 * Enum type supplied to {@link layoutMode} for setting the web layout mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebLayoutMode {
    /**
     * Web layout follows the system.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * Adaptive web layout based on page size.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    FIT_CONTENT = 1
}
/**
 * Enum type supplied to {@link RenderProcessNotRespondingData} when onRenderProcessNotResponding is called.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum RenderProcessNotRespondingReason {
    /**
     * Timeout for input sent to render process.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    INPUT_TIMEOUT = 0,
    /**
     * The new webpage loading navigation response timed out.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NAVIGATION_COMMIT_TIMEOUT = 1
}
/**
 * Encompassed message information as parameters to {@link onFileSelectorShow} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class FileSelectorParam {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Gets the title of this file selector.
     * @returns { string } Return the title of this file selector.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getTitle(): string;
    /**
     * Gets the FileSelectorMode of this file selector.
     * @returns { FileSelectorMode } Return the FileSelectorMode of this file selector.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getMode(): FileSelectorMode;
    /**
     * Gets an array of acceptable MIME type.
     * @returns { Array<string> } Return an array of acceptable MIME type.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getAcceptType(): Array<string>;
    /**
     * Gets whether this file selector use a live media captured value.
     *
     * @returns { boolean } Return {@code true} if captured media; return {@code false} otherwise.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isCapture(): boolean;
    /**
     * Gets an array of raw acceptable MIME type.
     * @returns { Array<string> } Return an array of raw acceptable MIME type.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getMimeTypes(): Array<string>;
    /**
    * Gets suggested file names.
    *
    * @returns { string } Return the suggested file names.
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    getSuggestedName(): string;

    /**
    * Get the default path opened when pulling up the selector.
    *
    * @returns { string } Return to the default path opened when pulling up the selector.
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    getDefaultPath(): string;

    /**
    * Gets a description array of file types.
    *
    * @returns { Array<string> } Return an array of description of the file type.
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    getDescriptions(): Array<string>;

    /**
    * Gets whether to filter fully matching file types.
    *
    * @returns { boolean } Return whether to filter all matching file types.
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    isAcceptAllOptionExcluded(): boolean;

    /**
    * Gets an array of selected types for web page files.
    *
    * @returns { Array<Array<AcceptableFileType>> } Return an array of selected types for web page files.
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    getAcceptableFileTypes(): Array<Array<AcceptableFileType>>;
}
/**
 * Defines the js result.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class JsResult {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Handle the user's JavaScript result if cancel the dialog.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleCancel(): void;
    /**
     * Handle the user's JavaScript result if confirm the dialog.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleConfirm(): void;
    /**
     * Handle the user's JavaScript result if confirm the prompt dialog.
     *
     * @param { string } result - The content of the dialog box entered by the user.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handlePromptConfirm(result: string): void;
}
/**
 * Defines the file selector result, related to {@link onFileSelectorShow} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class FileSelectorResult {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * select a list of files.
     *
     * @param { Array<string> } fileList - List of files that need to be operated.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleFileList(fileList: Array<string>): void;
}
/**
 * Defines the http auth request result, related to {@link onHttpAuthRequest} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class HttpAuthHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * confirm.
     *
     * @param { string } userName
     * @param { string } password
     * @returns { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    confirm(userName: string, password: string): boolean;
    /**
     * cancel.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    cancel(): void;
    /**
     * isHttpAuthInfoSaved.
     *
     * @returns { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isHttpAuthInfoSaved(): boolean;
}
/**
 * Defines the ssl error request result, related to {@link onSslErrorEventReceive} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class SslErrorHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Confirm to use the SSL certificate.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleConfirm(): void;
    /**
     * Cancel this request.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleCancel(): void;
    /**
     * ArkWeb has encountered an SSL certificate error, and this interface indicates whether to terminate or
     * continue displaying the error to users.
     *
     * @param { boolean } abortLoading If abortLoading is true, the current request will be canceled and the
     *     user will remain on the current page. If it is false, the SSL error will not be ignored, and a
     *     blank page will be displayed. If a default error page is enabled, the default error page will be
     *     shown instead. The default value is false.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handleCancel(abortLoading: boolean): void;
}
/**
 * Defines the client certificate request result, related to {@link onClientAuthenticationRequest} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class ClientAuthenticationHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Confirm to use the specified private key and client certificate chain.
     *
     * @param { string } priKeyFile - The file that store private key.
     * @param { string } certChainFile - The file that store client certificate chain.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    confirm(priKeyFile: string, certChainFile: string): void;
    /**
     * Confirm to use the authUri.The authUri can be obtained from certificate management.
     *
     * @param { string } authUri is the key of credentials.The credentials contain sign info and client certificates info.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    confirm(authUri: string): void;
    /**
     * Confirm to use the identify of the certificate. The identify can be obtained from certificate management.
     *
     * @param { string } identity - The identify of the credential.
     * @param { CredentialType | string } credentialTypeOrCertChainFile - The type of the credential or the file that store
     *     client certificate chain.
     * @throws { BusinessError } 801 - Capability not supported.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    confirm(identity: string, credentialTypeOrCertChainFile: CredentialType | string): void;
    /**
     * Cancel this certificate request.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    cancel(): void;
    /**
     * Ignore this certificate request temporarily.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ignore(): void;
}
/**
 * Handle the result of PIN verification.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class VerifyPinHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Passes the PIN code verify result.
     *
     * @param { PinVerifyResult } result The PIN code verify result.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    confirm(result: PinVerifyResult): void;
  }
/**
 * Defines the accessible resource type, related to {@link onPermissionRequest} method.
 *
 * @enum { string }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ProtectedResourceType {
    /**
     * The MidiSysex resource. Currently, only permission events can be reported. MIDI devices are not yet supported.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    MIDI_SYSEX = 'TYPE_MIDI_SYSEX',
    /**
     * The video capture resource, such as camera.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    VIDEO_CAPTURE = 'TYPE_VIDEO_CAPTURE',
    /**
     * The audio capture resource, such as microphone.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    AUDIO_CAPTURE = 'TYPE_AUDIO_CAPTURE',
    /**
     * The sensor resource, such as accelerometer.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    SENSOR = 'TYPE_SENSOR'
}
/**
 * Implements the PermissionRequest object, related to {@link onPermissionRequest} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class PermissionRequest {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Reject the request.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    deny(): void;
    /**
     * Gets the source if the webpage that attempted to access the restricted resource.
     *
     * @returns { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getOrigin(): string;
    /**
     * Obtains the list of accessible resources requested for the web page.
     *
     * @returns { Array<string> } List of accessible resources requested by the web page.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getAccessibleResource(): Array<string>;
    /**
     * Grant origin access to a given resource.
     *
     * @param { Array<string> } resources
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    grant(resources: Array<string>): void;
}
/**
 * Defines the onScreenCapture callback, related to {@link onScreenCapture} method.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class ScreenCaptureHandler {
    /**
     * Constructor.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Obtains the origin of this web page.
     *
     * @returns { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getOrigin(): string;
    /**
     * Grants the screen capture permission.
     * @param { ScreenCaptureConfig } config The screen capture configuration.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    grant(config: ScreenCaptureConfig): void;
    /**
     * Rejects this screen capture request.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    deny(): void;
}
/**
 * Defines the onDataResubmission callback, related to {@link onDataResubmission} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class DataResubmissionHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Resend related form data.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    resend(): void;
    /**
     * Do not resend related form data.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    cancel(): void;
}
/**
 * Defines the onWindowNew callback, related to {@link onWindowNew} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class ControllerHandler {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Set WebviewController object.
     *
     * @param { WebviewController } controller
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setWebController(controller: WebviewController): void;
}
/**
 * Defines the context menu source type, related to {@link onContextMenuShow} method.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ContextMenuSourceType {
    /**
     * Other source types.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * Mouse.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    MOUSE = 1,
    /**
     * Long press.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LONG_PRESS = 2
}
/**
 * Defines the context menu media type, related to {@link onContextMenuShow} method.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ContextMenuMediaType {
    /**
     * Not a special node or other media types.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * Image.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    IMAGE = 1
}
/**
 * Defines the context menu media type, related to {@link onContextMenuShow} method.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ContextMenuDataMediaType {
    /**
     * Not a special node or other media types.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * Image.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    IMAGE = 1,
    /**
     * Video.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    VIDEO = 2,
    /**
     * Audio.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    AUDIO = 3,
    /**
     * Canvas.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CANVAS = 4
}
/**
 * Defines the context menu input field type, related to {@link onContextMenuShow} method.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ContextMenuInputFieldType {
    /**
     * Not an input field.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * The plain text type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PLAIN_TEXT = 1,
    /**
     * The password type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PASSWORD = 2,
    /**
     * The number type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NUMBER_DATA = 3,
    /**
     * The telephone type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    TELEPHONE = 4,
    /**
     * Other types.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    OTHER = 5
}
/**
 * Defines the lifecycle of the same-layer tag.
 * When the same-layer tag exists on the loaded page,
 * CREATE is triggered. When the same-layer tag is moved or is enlarged,
 * **UPDATE **is triggered. When the page exits, DESTROY is triggered.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum NativeEmbedStatus {
    /**
     * The same-layer tag is created.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CREATE = 0,
    /**
     * The same-layer tag is updated.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    UPDATE = 1,
    /**
     *The same-layer tag is destroyed.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DESTROY = 2,
    /**
     * The same-layer tag enters the BFCache.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ENTER_BFCACHE = 3,
    /**
     * The same-layer tag leaves the BFCache.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LEAVE_BFCACHE = 4
}
/**
 * Defines the context menu supported event bit flags, related to {@link onContextMenuShow} method.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ContextMenuEditStateFlags {
    /**
     * Not editable.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * Clipping is supported.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CAN_CUT = 1 << 0,
    /**
     * Copies are supported.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CAN_COPY = 1 << 1,
    /**
     * Pasting is supported.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CAN_PASTE = 1 << 2,
    /**
     * Select all is supported.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CAN_SELECT_ALL = 1 << 3
}
/**
 * Enum type supplied to {@link navigationType} for the navigation's type.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebNavigationType {
    /**
     * Unknown type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    UNKNOWN = 0,

    /**
     * A new entry was created due to a navigation happened on the main frame.
     * Contains all situations that will generate a mainframe navigation entry,
     * which means that navigations to a hash on the same document or history.pushState
     * also belong to this type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    MAIN_FRAME_NEW_ENTRY = 1,

    /**
     * Navigate to an existing entry due to a navigation on the main frame.
     * e.g.
     *   1. History navigations.
     *   2. Reloads (contains loading the same url).
     *   3. Same-document navigations(history.replaceState(), location.replace()).
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    MAIN_FRAME_EXISTING_ENTRY = 2,

    /**
     * A navigation happened on subframe which was triggered by user.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NAVIGATION_TYPE_NEW_SUBFRAME = 4,

    /**
     * A navigation happened on the subframe automatically.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NAVIGATION_TYPE_AUTO_SUBFRAME = 5
}

/**
 * Enumerates the rendering mode of Web components. By default, the asynchronous rendering mode is used.
 * The asynchronous rendering mode is recommended because it has better performance and lower power consumption.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum RenderMode {
    /**
     * The Web component is rendered asynchronously.
     * The ArkWeb component as a graphic surface node is displayed independently.
     * The maximum width of the Web component is 7,680 px (physical pixel).
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    ASYNC_RENDER = 0,
    /**
     * The Web component is rendered synchronously.
     * The ArkWeb component as a graphic canvas node is displayed together with the system component.
     * The maximum width of the Web component is 500,000 px (physical pixel).
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    SYNC_RENDER = 1
}
/**
 * Defines the viewport-fit type, related to {@link ViewportFit}.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum ViewportFit {
    /**
     * No effect - the whole web page is viewable(default)
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    AUTO = 0,
    /**
     * The initial layout viewport and the visual viewport are set to the
     * largest rectangle which is inscribe in the display of the device.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CONTAINS = 1,
    /**
     * The initial layout viewport and the visual viewport are set to the
     * circumscribe rectangle of the physical screen of the device.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    COVER = 2
}
/**
 * Defines the context menu param, related to {@link WebContextMenuParam} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebContextMenuParam {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Horizontal offset coordinates of the menu within the Web component.
     * The unit is vp.
     *
     * @returns { int } The context menu x coordinate.
     *                  Returns a non-negative integer if normal, otherwise returns -1.
     *                  Unit: vp.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    x(): int;
    /**
     * Vertical offset coordinates for the menu within the Web component.
     * The unit is vp.
     *
     * @returns { int } The context menu y coordinate.
     *                  Returns a non-negative integer if normal, otherwise returns -1.
     *                  Unit: vp.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    y(): int;
    /**
     * If the long-press location is the link returns the link's security-checked URL.
     *
     * @returns { string } If relate to a link return link url, else return null.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getLinkUrl(): string;
    /**
     * If the long-press location is the link returns the link's original URL.
     *
     * @returns { string } If relate to a link return unfiltered link url, else return null.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getUnfilteredLinkUrl(): string;
    /**
     * Returns the SRC URL if the selected element has a SRC attribute.
     *
     * @returns { string } If this context menu is "src" attribute, return link url, else return null.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getSourceUrl(): string;
    /**
     * Long press menu location has image content.
     *
     * @returns { boolean } Return whether this context menu has image content.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    existsImageContents(): boolean;
    /**
     * Returns the type of context node.
     *
     * @returns { ContextMenuMediaType } Returns the type of context node.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getMediaType(): ContextMenuMediaType;
    /**
     * Returns the text of the selection.
     *
     * @returns { string } Returns the text of the selection, or return null if no text is selected.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getSelectionText(): string;
    /**
     * Returns the context menu source type.
     *
     * @returns { ContextMenuSourceType }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getSourceType(): ContextMenuSourceType;
    /**
     * Returns input field type if the context menu was invoked on an input field.
     *
     * @returns { ContextMenuInputFieldType } Input field type if the context menu was invoked on an input field.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getInputFieldType(): ContextMenuInputFieldType;
    /**
     * Returns whether the context is editable.
     *
     * @returns { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isEditable(): boolean;
    /**
     * Returns the context editable flags {@link ContextMenuEditStateFlags}.
     *
     * @returns { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getEditStateFlags(): int;
    /**
     * Returns the selection menu preview width. The unit is vp.
     *
     * @returns { int } The preview menu width.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getPreviewWidth(): int;
    /**
     * Returns the selection menu preview height. The unit is vp.
     *
     * @returns { int } The preview menu height.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getPreviewHeight(): int;
    /**
     * Returns the type of context node.
     *
     * @returns { ContextMenuDataMediaType } Returns the type of context node.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getContextMenuMediaType(): ContextMenuDataMediaType;
}
/**
 * Defines the context menu result, related to {@link WebContextMenuResult} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebContextMenuResult {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * When close context menu without other call in WebContextMenuResult,
     * User should call this function to close menu
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    closeContextMenu(): void;
    /**
     * If WebContextMenuParam has image content, this function will copy image related to this context menu.
     * If WebContextMenuParam has no image content, this function will do nothing.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    copyImage(): void;
    /**
     * Executes the copy operation related to this context menu.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    copy(): void;
    /**
     * Executes the paste operation related to this context menu.
     *
     * <p><strong>API Note</strong>:<br>
     * Permissions need to be configured: ohos.permission.READ_PASTEBOARD.
     * </p>
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    paste(): void;
    /**
     * Executes the cut operation related to this context menu.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    cut(): void;
    /**
     * Executes the selectAll operation related to this context menu.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    selectAll(): void;
    /**
     * Executes the redo operation related to this context menu.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    redo(): void;
    /**
     * Executes the undo operation related to this context menu.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    undo(): void;
    /**
     * Executes the paste and match style operation related to this context menu.
     *
     * <p><strong>API Note</strong>:<br>
     * Permissions need to be configured: ohos.permission.READ_PASTEBOARD.
     * </p>
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    pasteAndMatchStyle(): void;
    /**
     * Request to fill the password vault contents into the input field.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    requestPasswordAutoFill(): void;
    /**
     * Performing the "Save As Image" operation associated with this context menu will trigger the download process.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 24
     */
    saveImage(): void;
}
/**
 * Encompassed message information as parameters to {@link onConsole} method.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class ConsoleMessage {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Gets the message of a console message.
     *
     * @returns { string } Return the message of a console message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getMessage(): string;
    /**
     * Gets the Web source file's path and name of a console message.
     *
     * @returns { string } Return the Web source file's path and name of a console message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getSourceId(): string;
    /**
     * Gets the line number of a console message.
     *
     * @returns { int } Return the line number of a console message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getLineNumber(): int;
    /**
     * Gets the message level of a console message.
     *
     * @returns { MessageLevel } Return the message level of a console message, which can be {@link MessageLevel}.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getMessageLevel(): MessageLevel;
    /**
     * Gets the source of a console message.
     *
     * @returns { ConsoleMessageSource } Return the source of a console message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getSource(): ConsoleMessageSource;
}
/**
 * Defines the Web resource request.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebResourceRequest {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Gets request headers.
     *
     * @returns { Array<Header> } Return the request headers
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getRequestHeader(): Array<Header>;
    /**
     * Gets the request URL.
     *
     * @returns { string } Return the request URL.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getRequestUrl(): string;
    /**
     * Check whether the request is associated with gesture.
     *
     * @returns { boolean } Return {@code true} if the request is associated with gesture;return {@code false} otherwise.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isRequestGesture(): boolean;
    /**
     * Check whether the request is for getting the main frame.
     *
     * @returns { boolean } Return {@code true} if the request is associated with gesture for getting the main frame; return {@code false} otherwise.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isMainFrame(): boolean;
    /**
     * Check whether the request redirects.
     *
     * @returns { boolean } Return {@code true} if the request redirects; return {@code false} otherwise.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isRedirect(): boolean;
    /**
     * Get request method.
     *
     * @returns { string } Return the request method.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getRequestMethod(): string;
}
/**
 * Defines the Web resource response.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebResourceResponse {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Gets the response data.
     *
     * @returns { string } Return the response data.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseData(): string;
    /**
     * Gets the response data.
     *
     * @returns { string | int | ArrayBuffer | Resource | undefined } Return the response data.
     *                                                                string type indicate string in HTML format.
     *                                                                number type indicate file handle.
     *                                                                Resource type indicate $rawfile resource.
     *                                                                ArrayBuffer type indicate binary data.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseDataEx(): string | int | ArrayBuffer | Resource | undefined;
    /**
     * Gets the response encoding.
     *
     * @returns { string } Return the response encoding.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseEncoding(): string;
    /**
     * Gets the response MIME type.
     *
     * @returns { string } Return the response MIME type.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseMimeType(): string;
    /**
     * Gets the reason message.
     *
     * @returns { string } Return the reason message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getReasonMessage(): string;
    /**
     * Gets the response headers.
     *
     * @returns { Array<Header> } Return the response headers.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseHeader(): Array<Header>;
    /**
     * Gets the response code.
     *
     * @returns { int } Return the response code.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseCode(): int;
    /**
     * Sets the response data.
     *
     * @param { string | int | Resource | ArrayBuffer } data - the response data.
     *                                                         string type indicate strings in HTML format.
     *                                                         number type indicate file handle.
     *                                                         Resource type indicate $rawfile resource.
     *                                                         ArrayBuffer type indicate binary data.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseData(data: string | int | Resource | ArrayBuffer): void;
    /**
     * Sets the response encoding.
     *
     * @param { string } encoding the response encoding.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseEncoding(encoding: string): void;
    /**
     * Sets the response MIME type.
     *
     * @param { string } mimeType the response MIME type.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseMimeType(mimeType: string): void;
    /**
     * Sets the reason message.
     *
     * @param { string } reason the reason message.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setReasonMessage(reason: string): void;
    /**
     * Sets the response headers.
     *
     * @param { Array<Header> } header the response headers.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseHeader(header: Array<Header>): void;
    /**
     * Sets the response code.
     *
     * @param { int } code the response code.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseCode(code: int): void;
    /**
     * Sets the response is ready or not.
     *
     * @param { boolean } IsReady whether the response is ready.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setResponseIsReady(IsReady: boolean): void;
    /**
     * Gets whether the response is ready.
     *
     * @returns { boolean } True indicates the response data is ready and false is not ready.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getResponseIsReady(): boolean;
}
/**
 * Defines the Web's request/response header.
 *
 * @typedef Header
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface Header {
    /**
     * Gets the key of the request/response header.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    headerKey: string;
    /**
     * Gets the value of the request/response header.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    headerValue: string;
}
/**
 * Defines the Web resource error.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class WebResourceError {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Gets the info of the Web resource error.
     *
     * @returns { string } Return the info of the Web resource error.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getErrorInfo(): string;
    /**
     * Gets the code of the Web resource error.
     *
     * @returns { int } Return the code of the Web resource error.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    getErrorCode(): int;
}
/**
 * Defines the js geolocation request.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class JsGeolocation {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Sets the geolocation permission status of a web page.
     *
     * @param { string } origin - Index of the origin.
     * @param { boolean } allow - Geolocation permission status. {@code true} means to allow geolocation permission;
     *                            {@code false} means to disallow geolocation permission.
     * @param { boolean } retain - Whether the geolocation permission status can be saved to the system.
     *                             {@code true} means to allow the geolocation permission status to be saved to
     *                             the system; {@code false} means to disallow the geolocation permission status to
     *                             be saved to the system. You can manage the geolocation permissions saved
     *                             to the system through {@link GeolocationPermissions}.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    invoke(origin: string, allow: boolean, retain: boolean): void;
}
/**
 * Represents the event consumption result sent to the Web component.
 * For details about the supported events, see TouchEvent/MouseEvent.
 * If the application does not consume the event, set this parameter to false,
 * and the event will be consumed by the Web component. If the application has consumed the event,
 * set this parameter to true, and the event will not be consumed by the Web component.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare class EventResult {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    constructor();
    /**
     * Sets the gesture event consumption result.
     *
     * @param { boolean } result -  Whether to consume the gesture event.
     *    {@code true} Indicates the consumption of the gesture event.
     *    {@code false} Indicates the non-consumption of the gesture event.
     *    Default value: true.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setGestureEventResult(result: boolean): void;
    /**
     * Sets the gesture event consumption result.
     *
     * @param { boolean } result -  Whether to consume the gesture event.
     *    {@code true} Indicates the consumption of the gesture event.
     *    {@code false} Indicates the non-consumption of the gesture event.
     *    Default value: true.
     * @param { boolean } stopPropagation - Whether to stop propagation.
     *    This parameter is valid only when result is set to true.
     *    {@code true} Indicates stops the propagation of events farther along.
     *    {@code false} Indicates the propagation of events farther along.
     *    Default value: true.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setGestureEventResult(result: boolean, stopPropagation: boolean): void;
    /**
     * Sets the mouse event consumption result.
     *
     * @param { boolean } result -  Whether to consume the mouse event.
     *    {@code true} Indicates the consumption of the mouse event.
     *    {@code false} Indicates the non-consumption of the mouse event.
     *    Default value: true.
     * @param { boolean } [stopPropagation] - Whether to stop propagation.
     *    This parameter is valid only when result is set to true.
     *    {@code true} Indicates stops the propagation of events farther along.
     *    {@code false} Indicates the propagation of events farther along.
     *    Default value: true.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    setMouseEventResult(result: boolean, stopPropagation?: boolean): void;
}
/**
 * Defines the Web options.
 *
 * @typedef WebOptions
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface WebOptions {
    /**
     * Web resource address. If accessing local resource files, please use $rawfile or resource protocol.
     * If you load a local resource file that applies the sandbox path outside the package (files support html and txt types),
     * please use the file:// sandbox file path.
     * Src cannot dynamically change the address through state variables (for example: @State).
     * If you need to change it, please reload it through {@link loadUrl}.
     *
     * @type { string | Resource }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    src: string | Resource;
    /**
     * Sets the controller of the Web.
     *
     * @type { WebviewController }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    controller: WebviewController;
    /**
     * Rendering mode.
     * RenderMode.ASYNC_RENDER (default, cannot be dynamically adjusted): The Web component is rendered asynchronously.
     * RenderMode.SYNC_RENDER: The Web component is rendered synchronously within the current execution context.
     *
     * @type { ?RenderMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    renderMode?: RenderMode;
    /**
     * Sets the incognito mode of the Web, the parameter is optional and default value is false.
     * When the Web is in incognito mode, cookies, records of websites, geolocation permissions
     * will not save in persistent files.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    incognitoMode?: boolean;
    /**
     * A token indicating that the current Web component specifies a shared rendering process.
     * In the multi-rendering process mode, Web components with the same token will preferentially try to reuse
     * the rendering process bound to the token.
     * The binding of token to the rendering process occurs in the initialization stage of the rendering process.
     * When the rendering process has no associated Web component, its binding relationship with token will be removed.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    sharedRenderProcessToken?: string;
    /**
     * Sets whether mouse event will be transferred to touch event.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    emulateTouchFromMouseEvent?: boolean;
}
/**
 * Defines the regular expression rule.
 *
 * @typedef UrlRegexRule
 * @syscap SystemCapability.Web.Webview.Core
 * @stagemodelonly
 * @since 23
*/
export declare interface UrlRegexRule {
  /**
   * Exact match of the second-level domain. For example, the second-level domain of https://www.example.com
   * is example.com, and the second-level domain of https://www.example.com.cn is example.com.cn. If the URL
   * is an IP address, the full IP is matched against the secondLevelDomain.
   *
   * @type { string }
   * @syscap SystemCapability.Web.Webview.Core
   * @stagemodelonly
   * @since 23
   */
  secondLevelDomain: string;
  /**
   * Full URL regular expression.
   *
   * @type { string }
   * @syscap SystemCapability.Web.Webview.Core
   * @stagemodelonly
   * @since 23
   */
  rule: string;
}
/**
 * Defines the contents of the JavaScript to be injected.
 *
 * @typedef ScriptItem
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface ScriptItem {
    /**
     * Sets the JavaScript to be injected.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    script: string;
    /**
     * Sets the rules of the JavaScript.
     *
     * @type { Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    scriptRules: Array<string>;
    /**
     * Set the regular expression rule that allows execution of this JavaScript.
     *
     * @type { ?Array<UrlRegexRule> }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 23
     */
    urlRegexRules?: Array<UrlRegexRule>;
}
/**
 * Defines the load committed details.
 *
 * @typedef LoadCommittedDetails
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface LoadCommittedDetails {
    /**
     * Check whether the request is for getting the main frame.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isMainFrame: boolean;
    /**
     * Whether the navigation happened without changing document. Examples of
     * same document navigations are:
     *   1. reference fragment navigations.
     *   2. pushState/replaceState.
     *   3. same page history navigation
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isSameDocument: boolean;
    /**
     * True if the committed entry has replaced the existing one. Note that in
     * case of subframes, the NavigationEntry and FrameNavigationEntry objects
     * don't actually get replaced - they're reused, but with updated attributes.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    didReplaceEntry: boolean;
    /**
     * The type of the navigation.
     *
     * @type { WebNavigationType }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationType: WebNavigationType;
    /**
     * The url to navigate.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the Intelligent Tracking Prevention details.
 *
 * @typedef IntelligentTrackingPreventionDetails
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface IntelligentTrackingPreventionDetails {
    /**
     * The host of website url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    host: string;
    /**
     * The host of tracker url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    trackerHost: string;
}
/**
 * Defines the embed info.
 *
 * @typedef NativeEmbedInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedInfo {
    /**
     * The embed id.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    id?: string;
    /**
     * Type of the same-layer tag. The value is in lowercase.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    type?: string;
    /**
     * The embed tag src.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    src?: string;
    /**
     * Position of the same-layer tag relative to the Web component in the screen coordinate system,
     * which is different from the standard Position. The unit is px.
     *
     * @type { ?Position }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    position?: Position;
    /**
     * The embed tag width, in px.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    width?: int;
    /**
     * The embed tag height, in px.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    height?: int;
    /**
     * The embed tag url.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url?: string;
    /**
     * The embed tag name, which is in uppercase.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    tag?: string;
    /**
     * List of key-value pairs contained in the object tag that form a map of the Object type.
     * Use the methods provided by the Object type, such as embed.info?.param?.["name"] to operate the map object.
     *
     * @type { ?Map<string, string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    params?: Map<string, string>;
}
/**
 * Provides detailed information about the changes of the same-layer tag lifecycle.
 *
 * @typedef NativeEmbedDataInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedDataInfo {
    /**
     * Lifecycle status of the same-layer tag.
     *
     * @type { ?NativeEmbedStatus }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    status?: NativeEmbedStatus;
    /**
     * Psurfaceid of the NativeImage.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    surfaceId?: string;
    /**
     * Unique id of the same-layer tag.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    embedId?: string;
    /**
     * Detailed information about the same-layer tag.
     *
     * @type { ?NativeEmbedInfo }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    info?: NativeEmbedInfo;
}
/**
 * Provides visibility information about the same-layer tag.
 *
 * @typedef NativeEmbedVisibilityInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedVisibilityInfo {
    /**
     * Whether the same-layer tag is visible.
     * The value true indicates that the same-layer tag is visible, and false indicates the opposite.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    visibility: boolean;
    /**
     * ID of the same-layer rendered tag.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    embedId: string;
}
/**
 * Defines the user touch info.
 *
 * @typedef NativeEmbedTouchInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedTouchInfo {
    /**
     * The native embed id.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    embedId?: string;
    /**
     * Touch action information.
     *
     * @type { ?TouchEvent }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    touchEvent?: TouchEvent;
    /**
     * Gesture event consumption result.
     *
     * @type { ?EventResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result?: EventResult;
}
/**
 * Defines the user mouse info on embed layer.
 *
 * @typedef NativeEmbedMouseInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NativeEmbedMouseInfo {
    /**
     * The native embed id.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    embedId?: string;
    /**
     * An event sent when the state of contacts with a mouse-sensitive surface changes.
     *
     * @type { ?MouseEvent }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    mouseEvent?: MouseEvent;
    /**
     * Handle the user's mouse result.
     *
     * @type { ?EventResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result?: EventResult;
}

/**
 * Provides detailed information about the first meaningful paint.
 *
 * @typedef FirstMeaningfulPaint
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface FirstMeaningfulPaint {
    /**
     * Start time of navigation, in microseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationStartTime?: long;
    /**
     * Paint time of first meaningful content, in milliseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    firstMeaningfulPaintTime?: long;
}
/**
 * Defines the largest content paint rendering of web page.
 *
 * @typedef LargestContentfulPaint
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface LargestContentfulPaint {
    /**
     * Start time of navigation, in microseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationStartTime?: long;
    /**
     * Paint time of largest image, in milliseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    largestImagePaintTime?: long;
    /**
     * Paint time of largest text, in milliseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    largestTextPaintTime?: long;
    /**
     * Bits per pixel of maximum image.
     *
     * @type { ?double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    imageBPP?: double;
    /**
     * Load start time of largest image, in milliseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    largestImageLoadStartTime?: long;
    /**
     * Load end time of largest image, in milliseconds.
     *
     * @type { ?long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    largestImageLoadEndTime?: long;
}
/**
 * Defines the render process not responding info.
 *
 * @interface RenderProcessNotRespondingData
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface RenderProcessNotRespondingData {
    /**
     * JavaScript stack info of the webpage when render process not responding.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    jsStack: string;
    /**
     * Process id of render process not responding.
     *
     * @type { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    pid: int;
    /**
     * Reason for the render process not responding.
     *
     * @type { RenderProcessNotRespondingReason }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    reason: RenderProcessNotRespondingReason;
}
/**
 * Defines the triggered function at the end of web page loading.
 *
 * @typedef OnPageEndEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPageEndEvent {
    /**
     * The url of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered function at the begin of web page loading.
 *
 * @typedef OnPageBeginEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPageBeginEvent {
    /**
     * The url of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered function at the begin of web page loading.
 *
 * @typedef OnLoadStartedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnLoadStartedEvent {
    /**
     * The url to be loaded.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered function at the end of web page loading.
 *
 * @typedef OnLoadFinishedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnLoadFinishedEvent {
    /**
     * The url to be loaded.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered function when the page loading progress changes.
 *
 * @typedef OnProgressChangeEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnProgressChangeEvent {
    /**
     * The new progress of the page.
     *
     * @type { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    newProgress: int;
}
/**
 * Defines the triggered function when the title of the main application document changes.
 *
 * @typedef OnTitleReceiveEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnTitleReceiveEvent {
    /**
     * The title of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    title: string;
    /**
     * Mark the source of the title. If it is true, the title is derived from the H5 title element;
     * If it is false, it is calculated from the URL. By default, it is calculated from the URL.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isRealTitle?: boolean;
}
/**
 * Defines the triggered function when requesting to show the geolocation permission.
 *
 * @typedef OnGeolocationShowEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnGeolocationShowEvent {
    /**
     * Origin of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    origin: string;
    /**
     * Defines the js geolocation request.
     *
     * @type { JsGeolocation }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    geolocation: JsGeolocation;
}
/**
 * Defines the triggered function when the web page wants to display a JavaScript alert() dialog.
 *
 * @typedef OnAlertEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnAlertEvent {
    /**
     * The url of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The message of alert dialog.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    message: string;
    /**
     *  Handle the user's JavaScript result.
     *
     * @type { JsResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: JsResult;
}
/**
 * Defines the triggered function when the web page wants to confirm navigation from JavaScript onbeforeunload.
 *
 * @typedef OnBeforeUnloadEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnBeforeUnloadEvent {
    /**
     * The url of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The message of confirm dialog.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    message: string;
    /**
     *  Handle the user's JavaScript result.
     *
     * @type { JsResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: JsResult;
    /**
     * The isReload parameter is set to true when the page is refreshed;
     * otherwise, it remains false. Default is false.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isReload?: boolean;
}
/**
 * Defines callback triggered when confirm() is invoked by the web page.
 *
 * @typedef OnConfirmEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnConfirmEvent {
    /**
     * The url of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The message of confirm dialog.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    message: string;
    /**
     *  Handle the user's JavaScript result.
     *
     * @type { JsResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: JsResult;
}
/**
 * Defines the triggered function when the web page wants to display a JavaScript prompt() dialog.
 *
 * @typedef OnPromptEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPromptEvent {
    /**
     * The url of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The message of prompt dialog.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    message: string;
    /**
     * The value of prompt dialog.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    value: string;
    /**
     *  Handle the user's JavaScript result.
     *
     * @type { JsResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: JsResult;
}
/**
 * Defines the triggered function when the web page receives a JavaScript console message.
 *
 * @typedef OnConsoleEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnConsoleEvent {
    /**
     * Console message information of the event.
     *
     * @type { ConsoleMessage }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    message: ConsoleMessage;
}
/**
 * Defines the triggered function when the web page receives a web resource loading error.
 *
 * @typedef OnErrorReceiveEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnErrorReceiveEvent {
    /**
     * The information of request.
     *
     * @type { WebResourceRequest }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    request: WebResourceRequest;
    /**
     * The information of error.
     *
     * @type { WebResourceError }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    error: WebResourceError;
}
/**
 * Defines the triggered function when the web page receives a web resource loading HTTP error.
 *
 * @typedef OnHttpErrorReceiveEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnHttpErrorReceiveEvent {
    /**
     * The information of request.
     *
     * @type { WebResourceRequest }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    request: WebResourceRequest;
    /**
     *  Web resource response of event.
     *
     * @type { WebResourceResponse }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    response: WebResourceResponse;
}
/**
 * Defines the triggered function when starting to download.
 *
 * @typedef OnDownloadStartEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnDownloadStartEvent {
    /**
     * The URL of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The userAgent of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    userAgent: string;
    /**
     * The contentDisposition of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    contentDisposition: string;
    /**
     * The mimetype of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    mimetype: string;
    /**
     * The contentLength of page.
     *
     * @type { long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    contentLength: long;
}
/**
 * Defines the triggered callback when the Web page refreshes accessed history.
 *
 * @typedef OnRefreshAccessedHistoryEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnRefreshAccessedHistoryEvent {
    /**
     * URL of the visit.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * If true, the page is being reloaded, otherwise,  means that the page is newly loaded.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isRefreshed: boolean;
    /**
     * Whether is triggered by main frame.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isMainFrame?: boolean;
}
/**
 * Defines the triggered when the render process exits.
 *
 * @typedef OnRenderExitedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnRenderExitedEvent {
    /**
     * The specific reason why the rendering process exits abnormally.
     *
     * @type { RenderExitReason }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    renderExitReason: RenderExitReason;
}
/**
 * Defines the triggered when the file selector shows.
 *
 * @typedef OnShowFileSelectorEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnShowFileSelectorEvent {
    /**
     * Defines the file selector result.
     *
     * @type { FileSelectorResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: FileSelectorResult;
    /**
     * Encompassed message information as parameters to fileSelector.
     *
     * @type { FileSelectorParam }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    fileSelector: FileSelectorParam;
}
/**
 * Defines the triggered when the url loading.
 *
 * @typedef OnResourceLoadEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnResourceLoadEvent {
    /**
     * The URL of the loaded resource file.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered when the scale of WebView changed.
 *
 * @typedef OnScaleChangeEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnScaleChangeEvent {
    /**
     * Old scale of the page.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    oldScale: double;
    /**
     * New scale of the page.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    newScale: double;
}
/**
 * Defines the triggered when the browser needs credentials from the user.
 *
 * @typedef OnHttpAuthRequestEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnHttpAuthRequestEvent {
    /**
     * Defines the http auth request result.
     *
     * @type { HttpAuthHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: HttpAuthHandler;
    /**
     * Host of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    host: string;
    /**
     * realm of the page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    realm: string;
}
/**
 * Defines the triggered callback when the resources loading is intercepted.
 *
 * @typedef OnInterceptRequestEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnInterceptRequestEvent {
    /**
     * The information of request.
     *
     * @type { WebResourceRequest }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    request: WebResourceRequest;
}
/**
 * Defines the triggered callback when the host application that web content from the specified origin is
 *     attempting to access the resources.
 *
 * @typedef OnPermissionRequestEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPermissionRequestEvent {
    /**
     * Defines the onPermissionRequest callback.
     *
     * @type { PermissionRequest }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    request: PermissionRequest;
}
/**
 * Defines the triggered callback when the host application that web content from the specified origin is
 *     requesting to capture screen.
 *
 * @typedef OnScreenCaptureRequestEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnScreenCaptureRequestEvent {
    /**
     * Notifies the user of the operation behavior of the web component.
     *
     * @type { ScreenCaptureHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: ScreenCaptureHandler;
}
/**
 * Defines the triggered callback when called to allow custom display of the context menu.
 *
 * @typedef OnContextMenuShowEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnContextMenuShowEvent {
    /**
     * The menu-related parameters.
     *
     * @type { WebContextMenuParam }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    param: WebContextMenuParam;
    /**
     * The menu corresponding event is passed to the kernel.
     *
     * @type { WebContextMenuResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: WebContextMenuResult;
}
/**
 * Defines function Triggered when the host application call searchAllAsync.
 *
 * @typedef OnSearchResultReceiveEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnSearchResultReceiveEvent {
    /**
     * The ordinal number of the currently matched lookup item (starting from 0).
     *
     * @type { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    activeMatchOrdinal: int;
    /**
     * The number of all matched keywords.
     *
     * @type { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    numberOfMatches: int;
    /**
     * Indicates whether the current in-page search operation is complete. The method may be called back multiple times until isDoneCounting is true.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isDoneCounting: boolean;
}
/**
 * Defines function Triggered when the scroll bar slides to the specified position.
 *
 * @typedef OnScrollEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnScrollEvent {
    /**
     * The X offset of the scroll. The unit is vp.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    xOffset: double;
    /**
     * The Y offset of the scroll. The unit is vp.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    yOffset: double;
}
/**
 * Defines the triggered callback when the Web page receives an ssl Error.
 *
 * @typedef OnSslErrorEventReceiveEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnSslErrorEventReceiveEvent {
    /**
     * Notifies the user of the operation behavior of the web component.
     *
     * @type { SslErrorHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: SslErrorHandler;
    /**
     * Error codes.
     *
     * @type { SslError }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    error: SslError;
    /**
     * Certificate chain data in DER format.
     *
     * @type { ?Array<Uint8Array> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    certChainData?: Array<Uint8Array>;
}
/**
 * Defines the triggered callback when needs ssl client certificate from the user.
 *
 * @typedef OnClientAuthenticationEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnClientAuthenticationEvent {
    /**
     * Notifies the user of the operation behavior of the web component.
     *
     * @type { ClientAuthenticationHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: ClientAuthenticationHandler;
    /**
     * The hostname of the requesting certificate server.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    host: string;
    /**
     * The port number of the request certificate server.
     *
     * @type { int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    port: int;
    /**
     * Acceptable asymmetric key types.
     *
     * @type { Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    keyTypes: Array<string>;
    /**
     * Certificates that match the private key are acceptable to the issuer.
     *
     * @type { Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    issuers: Array<string>;
}
/**
 * Defines the triggered callback when web page requires the user to create a window.
 *
 * @typedef OnWindowNewEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnWindowNewEvent {
    /**
     * true indicates the request to create a dialog and false indicates a new tab.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isAlert: boolean;
    /**
     * true indicates that it is triggered by the user, and false indicates that it is triggered by a non-user.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isUserTrigger: boolean;
    /**
     * Destination URL.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    targetUrl: string;
    /**
     * Lets you set the WebviewController instance for creating a new window.
     *
     * @type { ControllerHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: ControllerHandler;
}
/**
 * Enum type for navigationPolicy in OnWindowNewExtEvent.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum NavigationPolicy {
    /**
     * NEW POPUP window.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NEW_POPUP = 0,
    /**
     * Shift key when clicking.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NEW_WINDOW = 1,
    /**
     * Middle mouse button or meta/ctrl key when clicking.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NEW_BACKGROUND_TAB = 2,
    /**
     * Shift key + Middle mouse button or meta/ctrl key when clicking.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NEW_FOREGROUND_TAB = 3
}
/**
 * Defines the window features info for window.open.
 *
 * @interface WindowFeatures
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface WindowFeatures {
    /**
     * The requested height of the containing window.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    height: double;
    /**
     * The requested width of the containing window.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    width: double;
    /**
     * The requested x-coordinate of the containing window.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    x: double;
    /**
     * The requested y-coordinate of the containing window.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    y: double;
}
/**
 * Defines the triggered callback when web page requires the user to create a window.
 *
 * @typedef OnWindowNewExtEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnWindowNewExtEvent {
    /**
     * true indicates the request to create a dialog and false indicates a new tab.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isAlert: boolean;
    /**
     * true indicates that it is triggered by the user, and false indicates that it is triggered by a non-user.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isUserTrigger: boolean;
    /**
     * Destination URL.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    targetUrl: string;
    /**
     * Lets you set the WebviewController instance for creating a new window.
     *
     * @type { ControllerHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: ControllerHandler;
    /**
     * Contains the attributes that a webpage requests from its containing web view.
     *
     * @type { WindowFeatures }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    windowFeatures: WindowFeatures;
    /**
     * The navigation policy causing the new web view to be created.
     *
     * @type { NavigationPolicy }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationPolicy: NavigationPolicy;
}
/**
 * Defines the triggered callback when the application receive an new url of an apple-touch-icon.
 *
 * @typedef OnTouchIconUrlReceivedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnTouchIconUrlReceivedEvent {
    /**
     * The apple-touch-icon URL address received.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * Corresponding to whether apple-touch-icon is precomposited.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    precomposed: boolean;
}
/**
 * Defines the triggered callback when the application receive a new favicon for the current web page.
 *
 * @typedef OnFaviconReceivedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnFaviconReceivedEvent {
    /**
     * Received the Favicon icon for the image.PixelMap object.
     *
     * @type { image.PixelMap }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    favicon: image.PixelMap;
}
/**
 * Defines the triggered callback when previous page will no longer be drawn and next page begin to draw.
 *
 * @typedef OnPageVisibleEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPageVisibleEvent {
    /**
     * The URL of page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the triggered callback to decision whether resend form data or not.
 *
 * @typedef OnDataResubmittedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnDataResubmittedEvent {
    /**
     * Form data resubmission handle.
     *
     * @type { DataResubmissionHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: DataResubmissionHandler;
}
/**
 * Defines the playing state of audio on web page.
 *
 * @typedef OnAudioStateChangedEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnAudioStateChangedEvent {
    /**
     * The audio playback status of the current page, true if playing true otherwise false.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    playing: boolean;
}
/**
 * Defines triggered when the first content rendering of web page.
 *
 * @typedef OnFirstContentfulPaintEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnFirstContentfulPaintEvent {
    /**
     * The time at which navigation begins, expressed in microseconds.
     *
     * @type { long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationStartTick: long;
    /**
     * The time it takes to draw content for the first time from navigation, expressed in milliseconds.
     *
     * @type { long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    firstContentfulPaintMs: long;
}
/**
 * Defines the triggered callback when the resources loading is intercepted.
 *
 * @typedef OnLoadInterceptEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnLoadInterceptEvent {
    /**
     * The information of request.
     *
     * @type { WebResourceRequest }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    data: WebResourceRequest;
}
/**
 * Defines the function Triggered when the over scrolling.
 *
 * @typedef OnOverScrollEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnOverScrollEvent {
    /**
     * Based on the leftmost part of the page, the horizontal scroll offset is over.
     * The unit is vp.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    xOffset: double;
    /**
     * Based on the top of the page, the vertical scroll offset is over.
     * The unit is vp.
     *
     * @type { double }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    yOffset: double;
}
/**
 * Defines the function Triggered when the PDF page scrolling.
 *
 * @typedef OnPdfScrollEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPdfScrollEvent {
    /**
     * PDF page url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url:string;
}
/**
 * Defines the function Triggered when the PDF load.
 *
 * @typedef OnPdfLoadEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface OnPdfLoadEvent {
    /**
     * The PDF page load result.
     *
     * @type { PdfLoadResult }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    result: PdfLoadResult;
    /**
     * The PDF page url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
}
/**
 * Defines the JavaScript object to be injected.
 *
 * @typedef JavaScriptProxy
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface JavaScriptProxy {
    /**
     * Objects participating in registration.
     *
     * @type { object }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    jsObject: object;
    /**
     * The name of the registered object, which is consistent with the
     *                          object name called in the window.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    name: string;
    /**
     * The method of the application side JavaScript object participating
     *                                       in the registration.
     *
     * @type { Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    methodList: Array<string>;
    /**
     * Controller.
     *
     * @type { WebviewController }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    controller: WebviewController;
    /**
     * The async method of the application side JavaScript object participating in the registration.
     *
     * @type { ?Array<string> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    asyncMethodList?: Array<string>;
    /**
     * permission configuration defining web page URLs that can access JavaScriptProxy methods.
     * The configuration can be defined at two levels, object level and method level.
     *
     * @type { ?string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    permission?: string;
}
/**
 * Enum type supplied to {@link keyboardAvoidMode} for setting the web keyboard avoid mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebKeyboardAvoidMode {
    /**
     * When the soft keyboard avoids, only the size of the visual viewport is adjusted, not the size of the layout viewport.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    RESIZE_VISUAL = 0,
    /**
     * By default, when the soft keyboard avoids,
     * the sizes of the visual viewport and the layout viewport are adjusted at the same time.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    RESIZE_CONTENT = 1,
    /**
     * Without adjusting any viewport size, soft keyboard avoidance will not be triggered.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    OVERLAYS_CONTENT = 2,
    /**
     * When the soft keyboard avoid, follow the avoid result of UIContext.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    RETURN_TO_UICONTEXT = 3
}
/**
 * Defines Web Elements type.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebElementType {
    /**
     * Image,corresponding HTML image type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    IMAGE = 1,
    /**
     * Link,corresponding link type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LINK = 2,
    /**
     * Text,corresponding textSpan type.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    TEXT = 3
}
/**
 * ResponseType for contextMenu
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebResponseType {
    /**
     * Long press.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LONG_PRESS = 1,
    /**
     * Right click.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    RIGHT_CLICK = 2
}

/**
 * Arkweb audio session Type
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum AudioSessionType {
    /**
     * Ambient audio, which is mixable with other types of audio.
     * This is useful in some special cases such as when the user wants to mix audios from multiple pages.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    AMBIENT = 3
}
/**
 * PDF page load result
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum PdfLoadResult {
    /**
     * The PDF page load success.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    LOAD_SUCCESS = 0,
    /**
     * The error code for web load PDF file failed.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PARSE_ERROR_FILE = 1,
    /**
     * The error code for the PDF format is not support.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PARSE_ERROR_FORMAT = 2,
    /**
     * The error code for the PDF password is wrong.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PARSE_ERROR_PASSWORD = 3,
    /**
     * The error code for the  PDF handler process failed.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PARSE_ERROR_HANDLER = 4
}
/**
 * Enum type supplied to {@link bypassVsyncCondition} for setting the bypass vsync condition.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum WebBypassVsyncCondition {
    /**
     * Not bypass vsync.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NONE = 0,
    /**
     * bypass vsync.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    SCROLLBY_FROM_ZERO_OFFSET = 1
}
/**
 * Defines the selection menu options.
 *
 * @typedef SelectionMenuOptionsExt
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface SelectionMenuOptionsExt {
    /**
     * Callback function when the selection menu appears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    onAppear?: VoidCallback;
    /**
     * Callback function when the selection menu disappears.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    onDisappear?: VoidCallback;
    /**
     * The preview content of selection menu.
     *
     * @type { ?CustomBuilder }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    preview?: CustomBuilder;
    /**
     * Menu type, default value is MenuType.SELECTION_MENU.
     *
     * @type { ?MenuType }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    menuType?: MenuType;
    /**
     * Defines the options of preview menu.
     *
     * @type { ?PreviewMenuOptions }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    previewMenuOptions?: PreviewMenuOptions;
    /**
     * Callback function when the selection is displayed.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    onMenuShow?: VoidCallback;

    /**
     * Callback function when the selection menu is hidden.
     *
     * @type { ?VoidCallback }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    onMenuHide?: VoidCallback;
}
/**
 * The details of this blank screen detection result.
 *
 * @typedef BlankScreenDetails
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface BlankScreenDetails {
    /**
     * The count of detected contentful nodes. This value only exists when developers configure a threshold.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    detectedContentfulNodesCount?: int;
}
/**
 * Enum type supplied to {@link BlankScreenDetectionEventInfo} when onDetectedBlankScreen being called.
 *
 * @enum { int }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum DetectedBlankScreenReason {
    /**
     * None of any contentful nodes have been detected.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    NO_CONTENTFUL_NODES = 0,
    /**
     * Web has detected a few of contentful nodes but below the threshold.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    SUB_THRESHOLD_CONTENTFUL_NODES = 1
}
/**
 * Defines the blank screen detection event info.
 *
 * @typedef BlankScreenDetectionEventInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface BlankScreenDetectionEventInfo {
    /**
     * The url of detected blank screen page.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The reason why we consider this page is blank.
     *
     * @type { DetectedBlankScreenReason }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    blankScreenReason: DetectedBlankScreenReason;
    /**
     * The details of this detection result.
     *
     * @type { ?BlankScreenDetails }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    blankScreenDetails?: BlankScreenDetails;
}
/**
 * The callback when web engine detects current page is blank or nearly blank.
 *
 * @typedef { function } DetectBlankScreenCallback
 * @param { BlankScreenDetectionEventInfo } event - the detection event info.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnDetectBlankScreenCallback = (event: BlankScreenDetectionEventInfo) => void;
/**
 * Callback with the selected text after the text selection content changes.
 *
 * @typedef { function } TextSelectionChangeCallback
 * @param { string } selectionText - the selected text after the text selection content changes.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type TextSelectionChangeCallback = (selectionText: string) => void;
/**
 * The methods can be chosen to detect if current page is blank or nearly blank.
 *
 * @enum { int }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum BlankScreenDetectionMethod {
    /**
     * This detection method is used to probe whether there are rendered contentful nodes
     * at 17 coordinates distributed around the center of the page.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DETECTION_CONTENTFUL_NODES_SEVENTEEN = 0
}
/**
 * The strategy of blank screen detection.
 *
 * @typedef BlankScreenDetectionConfig
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface BlankScreenDetectionConfig {
    /**
     * Enable blank screen detection or not.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    enable: boolean;
    /**
     * The settings of the timing when web try to detect current page is blank or not.
     * The timing is the duration after web navigation.
     *
     * @type { ?double[] }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    detectionTiming?: double[];
    /**
     * The combination of blank screen detection methods.
     *
     * @type { ?BlankScreenDetectionMethod[] }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    detectionMethods?: BlankScreenDetectionMethod[];
    /**
     * When using the specific detection method of detecting contentful nodes, the threshold is used
     * to determine how close the detection is to being blank screen page.
     *
     * @type { ?int }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    contentfulNodesCountThreshold?: int;
}
/**
 * Defines the first screen paint info.
 *
 * @typedef FirstScreenPaint
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface FirstScreenPaint {
    /**
     * The url of first screen paint info.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * The navigation start time of the url.
     *
     * @type { long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    navigationStartTime: long;
    /**
     * The first screen paint time of the url.
     *
     * @type { long }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    firstScreenPaintTime: long;
}
/**
 * The callback reports the time required for the first screen painting of the current web page.
 *
 * @typedef { function } OnFirstScreenPaintCallback
 * @param { FirstScreenPaint } firstScreenPaint - the first screen paint info.
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export type OnFirstScreenPaintCallback = (firstScreenPaint: FirstScreenPaint) => void;
/**
 * The callback will be triggered when inputmethod is attached.
 *
 * @typedef { function } OnInputmethodAttachedCallback
 * @syscap SystemCapability.Web.Webview.Core
 * @stagemodelonly
 * @since 26.0.0
 */
export type OnInputmethodAttachedCallback = () => void;
/**
 * Defines the Web attribute functions.
 *
 * @extends CommonMethod<WebAttribute>
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 * @noninterop
 */
export declare interface WebAttribute extends CommonMethod {
    /**
     * Sets whether the Web allows JavaScript scripts to execute.
     *
     * @param { boolean | undefined } javaScriptAccess - {@code true} means the Web can allows JavaScript scripts to execute; {@code false} otherwise.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default javaScriptAccess(javaScriptAccess: boolean | undefined): this;
    /**
     * Sets whether to enable access to the file system in the application.
     * This setting dose not affect the access to the files specified though $rawfile(filepath/filename).
     * <p><strong>API Note</strong>:<br>
     * fileAccess is disabled by default since API version 12.
     * When fileAccess is set to false, files in the read-only /data/storage/el1/bundle/entry/resources/resfile<br>
     * directory can still be accessed through the file protocol.
     * </p>
     *
     * @param { boolean | undefined } fileAccess - {@code true} means enable local file system access in Web; {@code false} otherwise.
     *    The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default fileAccess(fileAccess: boolean | undefined): this;
    /**
     * Sets whether to enable access to online images through HTTP and HTTPS.
     *
     * @param { boolean | undefined } onlineImageAccess - Sets whether to enable access to online images.
     *    {@code true} means means setting to allow loading image resources from the network, {@code false} otherwise.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onlineImageAccess(onlineImageAccess: boolean | undefined): this;
    /**
     * Sets whether to enable the DOM Storage API. By default, this feature is disabled.
     * @param { boolean | undefined } domStorageAccess - Whether to enable the DOM Storage API. {@code true} means to enable
     *                                       the DOM Storage API; {@code false} means to disable the DOM Storage API.
     *                                       The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default domStorageAccess(domStorageAccess: boolean | undefined): this;
    /**
     * Sets whether to enable automatic image loading.
     *
     * @param { boolean | undefined } imageAccess - Sets whether to enable automatic image loading.
     *    {@code true} means the Web can automatically load image resources, {@code false} otherwise.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default imageAccess(imageAccess: boolean | undefined): this;
    /**
    * Sets the behavior when a secure origin attempts to load a resource from an insecure origin.
    * The default is MixedMode.None, meaning not allow a secure origin to load content from an insecure origin.
    *
    * @param { MixedMode | undefined } mixedMode - The mixed mode, which can be {@link MixedMode}.
    *    Default value: MixedMode.None, which means that secure origin is not allowed to load content from insecure origin.
    * @returns { WebAttribute }
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    default mixedMode(mixedMode: MixedMode | undefined): this;
    /**
     * Sets whether the Web supports zooming using gestures.
     *
     * @param { boolean | undefined } zoomAccess {@code true} means the Web supports zooming using gestures; {@code false} otherwise.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default zoomAccess(zoomAccess: boolean | undefined): this;
    /**
     * Set whether to enable geolocation access. By default, this feature is enabled.
     * For details, see Managing Location Permissions.
     *
     * @param { boolean | undefined } geolocationAccess - Whether to enable geolocation access. {@code true} means the Web
     *                                                    allows access to geographical locations; {@code false} means the
     *                                                    Web disallows access to geographical locations. The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default geolocationAccess(geolocationAccess: boolean | undefined): this;
    /**
     * Registers the supplied ArkTS object in javaScriptProxy into this Web component.
     * The object is registered into all frames of the web page, including all frames, using the specified name in javaScriptProxy.
     * This allows the methods of the ArkTS object in javaScriptProxy to be accessed from JavaScript.
     *
     * <p><strong>API Note</strong>:
     * <strong>Performance Note</strong>:
     * <p>For details about how to arkWeb rendering framework adaptation solution,
     * see [ArkWeb Rendering Framework Adaptation]
     * {@link https://developer.huawei.com/consumer/en/doc/best-practices/bpta-arkweb_rendering_framework}
     * </p>
     *
     * @param { JavaScriptProxy | undefined } javaScriptProxy - The ArkTS object in javaScriptProxy will be registered into this Web component,
     * and the methods within the methodList of the injected ArkTS object declared in javaScriptProxy can be accessed by JavaScript.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default javaScriptProxy(javaScriptProxy: JavaScriptProxy | undefined): this;
    /**
     * Sets the mode of cache in Web.
     *
     * @param { CacheMode | undefined } cacheMode - The cache mode, which can be {@link CacheMode}.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default cacheMode(cacheMode: CacheMode | undefined): this;
    /**
     * Sets the web dark mode. By default, web dark mode is disabled. When it is enabled,
     * the Web component enables the dark theme defined for web pages
     * if the theme has been defined in prefers-color-scheme of a media query,
     * and remains unchanged otherwise. To enable the forcible dark mode, use this API with forceDarkAccess.
     *
     * @param { WebDarkMode | undefined } mode - Web dark mode to set.
     *     Default value: WebDarkMode.Off.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default darkMode(mode: WebDarkMode | undefined): this;
    /**
     * Sets whether to enable forcible dark mode for the web page.
     * This API is applicable only when dark mode is enabled in {@link darkMode}.
     *
     * @param { boolean | undefined } access Sets whether to enable forcible dark mode for the web page.
     *    {@code true} means enable forcible dark mode for the web page. ;
     *    {@code false} means not enable forcible dark mode for the web page.
     *    The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default forceDarkAccess(access: boolean | undefined): this;
    /**
     * Sets the web-based media playback policy, including the validity period for automatically resuming a paused web audio,
     * and whether the audio of multiple Web instances in an application is exclusive.
     * <p><strong>API Note</strong>:<br>
     * Audios in the same Web instance are considered as the same audio.
     * The media playback policy controls videos with an audio track.
     * After the parameter settings are updated, the playback must be started again for the settings to take effect.
     * It is recommended that you set the same audioExclusive value for all Web components.
     * Audio and video interruption takes effect within an app and between apps, and playback resumption takes effect only between apps.
     * </p>
     *
     * @param { WebMediaOptions | undefined } options Set the media policy for the web.
     * After updating the attribute parameters, the audio needs to be replayed for it to take effect.
     *    Default value: {resumeInterval: 0, audioExclusive: true}
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default mediaOptions(options: WebMediaOptions | undefined): this;

    /**
     * Sets whether to load web pages by using the overview mode, which means reducing the content to fit the screen width.
     * Currently, only mobile devices are supported.
     *
     * @param { boolean | undefined } overviewModeAccess Whether to load web pages by using the overview mode.
     *    {@code true} means the Web access overview mode;
     *    {@code false} means the Web not access overview mode.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default overviewModeAccess(overviewModeAccess: boolean | undefined): this;
    /**
     * Sets the over-scroll mode for web
     * When the scrolling mode is enabled, when the user slides to the edge on the web root page, the web will bounce back
     * the interface through elastic animation, and the internal pages on the root page will not trigger the bounce back.
     *
     * @param { OverScrollMode | undefined } mode - The over-scroll mode, which can be {@link OverScrollMode}.
     *    The default value is OverScrollMode.NEVER.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default overScrollMode(mode: OverScrollMode | undefined): this;
    /**
     * Sets the blur on for elements on webview when soft keyboard is hidden manually.
     *
     * @param { BlurOnKeyboardHideMode | undefined } mode - Default value is SILENT. Set BLUR to enable the blur on keyboard hide mode, which can be {@link BlurOnKeyboardHideMode}.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default blurOnKeyboardHideMode(mode: BlurOnKeyboardHideMode | undefined): this;
    /**
     * Sets the ratio of the text zoom.
     *
     * @param { int | undefined } textZoomRatio Text zoom ratio to set. The value is an integer. The value range is (0, 2147483647].
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default textZoomRatio(textZoomRatio: int | undefined): this;
    /**
     * Sets whether to enable database access. By default, this feature is disabled.
     *
     *
     * @param { boolean | undefined } databaseAccess - Whether to enable database access. {@code true} means to enable
     *                                                 database access; {@code false} means to disable database access.
     *                                                 The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default databaseAccess(databaseAccess: boolean | undefined): this;
    /**
     * Sets the initial scale for the Web.
     *
     * @param { double | undefined } percent the initial scale for the Web.
     *                               Value range: (0, 1000].
     *                               Default value: 100.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default initialScale(percent: double | undefined): this;
    /**
     * Sets whether the viewport property of the meta tag is enabled.
     *
     * <p><strong>API Note</strong>:<br>
     * If the device is 2-in-1, the viewport property is not supported. This means that,
     * regardless of whether this parameter is set to true or false,
     * the viewport property will not be parsed and a default layout will be used.<br>
     * If the device is a tablet, the viewport-fit property of the meta tag is parsed regardless of
     * whether this parameter is set to true or false. When viewport-fit is set to cover,
     * the size of the safe area can be obtained through the CSS attribute.<br>
     * The viewport parameter of the meta tag on the frontend HTML page is enabled or
     * disabled based on whether User-Agent contains the Mobile field.
     * If a User-Agent does not contain the Mobile field, the viewport property in the meta tag is disabled by default.
     * In this case, you can explicitly set the metaViewport property to true to overwrite the disabled state.
     * </p>
     *
     * @param { boolean | undefined } enabled Whether the viewport property of the meta tag is enabled.
     *    {@code true} means support the viewport attribute of the meta tag is enabled and parsed,
     *    and the layout is performed based on the viewport attribute.
     *    {@code false} means not support the viewport attribute of the meta tag is disabled and not parsed,
     *    and the default layout is used.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default metaViewport(enabled: boolean | undefined): this;
    /**
     * Called when the web page starts to be loaded.
     * This API is called only for the main frame, and not for the iframe or frameset content.
     *
     * @param { Callback<OnPageBeginEvent> | undefined } callback The triggered function at the begin of web page
     *     loading.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPageBegin(callback: Callback<OnPageBeginEvent> | undefined): this;
    /**
     * Triggered at the end of web page loading.
     * This callback is only invoked for the main frame and not for subframes.
     *
     * @param { Callback<OnPageEndEvent> | undefined } callback The triggered function at the end of web page loading.
     * @returns { WebAttribute } The WebAttribute object representing the attributes of the web page.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPageEnd(callback: Callback<OnPageEndEvent> | undefined): this;
    /**
     * Triggered at the begin of web page loading. This method is called once for each main frame load.  Embedded frame
     * changes, i.e. clicking a link whose target is an iframe and fragment navigations (navigations to #fragment_id)
     * will not trigger this callback.
     *
     * <p><strong>API Note</strong>:<br>
     * When the document of a pop-up window has been modified by JavaScript before it is loaded, it will simulate the
     * triggering of onLoadStarted with the URL set to empty because displaying the URL that is currently loading maybe
     * unsafe. onPageBegin will not be simulated.
     * </p>
     *
     * @param { Callback<OnLoadStartedEvent> | undefined } callback The triggered function at the begin of web page loading.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onLoadStarted(callback: Callback<OnLoadStartedEvent> | undefined): this;
    /**
     * Notify the host application that a page has finished loading. This method is called only for main frame.
     *
     * <p><strong>API Note</strong>:<br>
     * 1. Fragment navigation also triggers onLoadFinished, but onPageEnd will not be triggered.
     * 2. onLoadFinished is triggered only once if the mainframe is automatically redirected before the page is
     *    completely loaded. onPageEnd is triggered every navigation on mainframe.
     * 3. When the document of a pop-up window has been modified by JavaScript before it is loaded , it will simulate the
     *    triggering of onLoadStarted with the URL set to empty because displaying the URL that is currently
     *    loading may be unsafe. onPageBegin will not be simulated.
     * </p>
     *
     * @param { Callback<OnLoadFinishedEvent> | undefined } callback The triggered function at the end of web page loading.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onLoadFinished(callback: Callback<OnLoadFinishedEvent> | undefined): this;
    /**
     * Triggered when the page loading progress changes.
     *
     * @param { Callback<OnProgressChangeEvent> | undefined } callback The triggered function when the page loading progress changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onProgressChange(callback: Callback<OnProgressChangeEvent> | undefined): this;
    /**
     * Notifies the application that the title has changed.
     * If the page being loaded does not specify a title via the <title> element,
     * ArkWeb will generate a title baseed on the URL and return it to the application.
     *
     * @param { Callback<OnTitleReceiveEvent> | undefined } callback The triggered function when the title of the main application document changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onTitleReceive(callback: Callback<OnTitleReceiveEvent> | undefined): this;
    /**
     * Called to notify the user that the request for obtaining the geolocation information received
     * when {@link onGeolocationShow} is called has been canceled.
     *
     * @param { function | undefined } callback - Callback invoked when the request for obtaining geolocation information has been canceled.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onGeolocationHide(callback: (() => void) | undefined): this;
    /**
     * Called when a request to obtain the geolocation information is received.
     * @param { Callback<OnGeolocationShowEvent> | undefined } callback - Callback invoked when a request to obtain the geolocation
     *                                                                    information is received.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onGeolocationShow(callback: Callback<OnGeolocationShowEvent> | undefined): this;
    /**
     * Triggered when the Web gets the focus.
     *
     * @param { function | undefined } callback The triggered function when the Web gets the focus.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onRequestSelected(callback: (() => void) | undefined): this;
    /**
     * Triggered when alert() is invoked to display an alert dialog box on the web page.
     *
     * @param {  Callback<OnAlertEvent, boolean> | undefined } callback Callback used when alert() is invoked to display an alert dialog box on the web page.
     *     {@code true} means the application can invoke custom pop-up dialog capabilities (with confirmation and cancellation buttons).
     *                  Developers need to use the JsResult interface to notify the web component whether to leave the current page
     *                  according to the user's choice.
     *     {@code false} means the pop-up processing result is considered as cancelled.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onAlert(callback: Callback<OnAlertEvent, boolean> | undefined): this;
    /**
     * Triggered when the Web wants to confirm navigation from JavaScript onbeforeunload.
     *
     * @param { Callback<OnBeforeUnloadEvent, boolean> | undefined } callback The triggered function when the web page wants to confirm navigation from JavaScript onbeforeunload.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onBeforeUnload(callback: Callback<OnBeforeUnloadEvent, boolean> | undefined): this;
    /**
     * Triggered when confirm() is invoked by the web page.
     *
     * @param { Callback<OnConfirmEvent, boolean> | undefined } callback Callback triggered when confirm() is invoked by the web page.
     *     {@code true} means the application can call the custom pop-up capability (including confirmation and cancellation), and needs to call JsResult
     *                  to notify the Web component whether to leave the current page based on the user's confirmation or cancellation operation.
     *     {@code false} means the custom pop-up drawn in the function is invalid.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onConfirm(callback: Callback<OnConfirmEvent, boolean> | undefined): this;
    /**
     * Triggered when prompt() is invoked by the web page.
     *
     * @param { Callback<OnPromptEvent, boolean> | undefined } callback Callback used when prompt() is invoked by the web page.
     *     {@code true} means the application can call the custom pop-up window capability (including confirmation, cancellation, and input),and needs to
     *                   call JsResult to notify the Web component of the final processing result based on the user's confirmation or cancellation operation.
     *     {@code false} means the pop-up window processing result is considered as a cancellation.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPrompt(callback: Callback<OnPromptEvent, boolean> | undefined): this;
    /**
     * Triggered when the web page receives a JavaScript console message.
     *
     * @param {  Callback<OnConsoleEvent, boolean> | undefined } callback The triggered function when the web page receives a JavaScript console message.
     *     {@code true} means the message will no longer be printed to the console.
     *     {@code false} means it will still be printed to the console.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onConsole(callback: Callback<OnConsoleEvent, boolean> | undefined): this;
    /**
     * Triggered when the web page receives a web resource loading error.
     *
     * @param { Callback<OnErrorReceiveEvent> | undefined } callback The triggered function when the web page receives a web resource loading error.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onErrorReceive(callback: Callback<OnErrorReceiveEvent> | undefined): this;
    /**
     * Triggered when the web page receives a web resource loading HTTP error.
     *
     * @param { Callback<OnHttpErrorReceiveEvent> | undefined } callback The triggered function when the web page receives a web resource loading HTTP error.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onHttpErrorReceive(callback: Callback<OnHttpErrorReceiveEvent> | undefined): this;
    /**
     * Triggered when starting to download.
     *
     * @param { Callback<OnDownloadStartEvent> | undefined } callback The triggered function when starting to download.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onDownloadStart(callback: Callback<OnDownloadStartEvent> | undefined): this;
    /**
     * Triggered when the Web page refreshes accessed history.
     *
     * @param { Callback<OnRefreshAccessedHistoryEvent> | undefined } callback The triggered callback when the Web page refreshes accessed history.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onRefreshAccessedHistory(callback: Callback<OnRefreshAccessedHistoryEvent> | undefined): this;
    /**
     * Triggered when the render process exits.
     * Multiple Web components may share a single rendering process, and each affected Web component will trigger the callback.
     * When the application handles this callback, it can call the related interface of the bound webviewController to
     * restore the page. Such as {@link refresh}, {@link loadUrl}, etc.
     * For details of component lifecycle callback, please refer to the lifecycle of Web components.
     * @param { Callback<OnRenderExitedEvent> | undefined } callback The triggered when the render process exits.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onRenderExited(callback: Callback<OnRenderExitedEvent> | undefined): this;
    /**
     * Triggered when the file selector shows.
     * Call this function to handle HTML forms with a "file" input type. If this function is not called or returns false,
     * the web component provides the default "select file" handling interface. If it returns true, the application can customize
     * the "select file" response behavior.
     *
     * @param { Callback<OnShowFileSelectorEvent, boolean> | undefined } callback The triggered when the file selector shows.
     *     {@code true} means the user can call the system-provided pop-up window capability.
     *     {@code false} means the custom pop-up window drawn in the function is invalid.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onShowFileSelector(callback: Callback<OnShowFileSelectorEvent, boolean> | undefined): this;
    /**
     * Triggered when the url loading.
     *
     * @param { Callback<OnResourceLoadEvent> | undefined } callback The triggered when the url loading.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onResourceLoad(callback: Callback<OnResourceLoadEvent> | undefined): this;
    /**
     * Triggered when the web component exit the full screen mode.
     *
     * @param { function | undefined } callback The triggered function when the web component exit the full screen mode.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFullScreenExit(callback: (() => void) | undefined): this;
    /**
     * Triggered when the web component enter the full screen mode.
     *
     * @param { OnFullScreenEnterCallback | undefined } callback - The triggered function when the web component enter the full screen mode.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFullScreenEnter(callback: OnFullScreenEnterCallback | undefined): this;
    /**
     * Triggered when the scale of WebView changed.
     *
     * @param { Callback<OnScaleChangeEvent> | undefined } callback The triggered when the scale of WebView changed.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onScaleChange(callback: Callback<OnScaleChangeEvent> | undefined): this;
    /**
     * Triggered when the browser needs credentials from the user.
     *
     * @param { Callback<OnHttpAuthRequestEvent, boolean> | undefined } callback The triggered when the browser needs credentials from the user.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onHttpAuthRequest(callback: Callback<OnHttpAuthRequestEvent, boolean> | undefined): this;
    /**
     * Triggered when the resources loading is intercepted.
     *
     * @param { Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined } callback The triggered callback when the resources loading is intercepted.
     * @returns { WebAttribute } If the response value is null, the Web will continue to load the resources. Otherwise, the response value will be used
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onInterceptRequest(callback: Callback<OnInterceptRequestEvent, WebResourceResponse | null> | undefined): this;
    /**
     * Called when a permission request is received. To call this API, you need to declare the ohos.permission.CAMERA and ohos.permission.MICROPHONE permissions.
     *
     * @param { Callback<OnPermissionRequestEvent> | undefined } callback Callback invoked when a permission request is received.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPermissionRequest(callback: Callback<OnPermissionRequestEvent> | undefined): this;
    /**
     * Called when a screen capture request is received.
     *
     * @param { Callback<OnScreenCaptureRequestEvent> | undefined } callback Called when a screen capture request is received.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onScreenCaptureRequest(callback: Callback<OnScreenCaptureRequestEvent> | undefined): this;
    /**
     * Triggered when called to allow custom display of the context menu.
     *
     * @param { Callback<OnContextMenuShowEvent, boolean> | undefined } callback The triggered callback when called to allow custom display of the context menu.
     *     {@code true} means the custom menu is triggered.
     *     {@code false} means the custom menu is invalid.
     * @returns { WebAttribute } If custom display return true.Otherwise, default display return false.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onContextMenuShow(callback: Callback<OnContextMenuShowEvent, boolean> | undefined): this;
    /**
     * Triggered when called to allow custom hide of the context menu.
     *
     * @param { OnContextMenuHideCallback | undefined } callback The triggered function when called to allow custom hide of the context menu.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onContextMenuHide(callback: OnContextMenuHideCallback | undefined): this;
    /**
     * Set whether to manually play audio-only videos. The playback of muted videos is not controlled by this interface.
     *
     * @param { boolean | undefined } access Set whether to manually play audio-only videos.
     *  {@code true}True means setting up automatic playback of audio videos requires users to manually click, {@code false} otherwise.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default mediaPlayGestureAccess(access: boolean | undefined): this;
    /**
     * Notify search result to host application through onSearchResultReceive.
     *
     * @param { Callback<OnSearchResultReceiveEvent> | undefined } callback Function Triggered when the host application call searchAllAsync.
     * or searchNext api on WebController and the request is valid.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onSearchResultReceive(callback: Callback<OnSearchResultReceiveEvent> | undefined): this;
    /**
     * Notify the global scroll position of the web page
     *
     * Description:
     *
     * What is notified is the global scroll position of the page.
     * Changes in the local scroll position cannot trigger this callback.
     *
     * Determine whether the page is globally scrolled and print window.pagYOffset
     * or window.pagXOffset before and after scrolling.
     *
     * If it is global scrolling, the value of window.pagYOffset
     * or window.pagXOffset will change before and after scrolling, and vice versa.
     *
     * @param { Callback<OnScrollEvent> | undefined } callback Function triggered when the web page scroll to the specified position.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onScroll(callback: Callback<OnScrollEvent> | undefined): this;
    /**
     * Called to notify users when an SSL error occurs with a request for the main frame.
     * To include errors with requests for subframes, use the OnSslErrorEvent API.
     *
     * @param { Callback<OnSslErrorEventReceiveEvent> | undefined } callback The triggered callback when the Web page receives an ssl Error.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onSslErrorEventReceive(callback: Callback<OnSslErrorEventReceiveEvent> | undefined): this;
    /**
     * Called to notify users when an SSL error occurs during the loading of resources (for the main frame and subframes).
     * To handle SSL errors for requests for the main frame, use the isMainFrame field to distinguish.
     *
     * @param { OnSslErrorEventCallback | undefined } callback The triggered callback when the Web page receives an ssl Error.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onSslErrorEvent(callback: OnSslErrorEventCallback | undefined): this;
    /**
     * Triggered when the Web page needs ssl client certificate from the user.
     *
     * @param { Callback<OnClientAuthenticationEvent> | undefined } callback The triggered callback when needs ssl client certificate from the user.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onClientAuthenticationRequest(callback: Callback<OnClientAuthenticationEvent> | undefined): this;
    /**
     * Triggered when the Web page needs verify pin from the user.
     *
     * @param { OnVerifyPinCallback | undefined } callback The triggered callback when needs verify pin from the user.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onVerifyPin(callback: OnVerifyPinCallback | undefined): this;
    /**
     * Triggered when web page requires the user to create a window.
     * If the {@link setWebController} interface is not called, the render process will be blocked.
     * If no new window is created, it is set to null when calling the {@link setWebController} interface,
     * informing the Web that no new window is created.
     * The new window should avoid being directly overlaid on the original Web component,
     * and its URL (such as address bar) should be clearly displayed in the same form as the main page to
     * prevent users from being confused. If credible URL visualization management cannot be achieved,
     * it is necessary to consider prohibiting the creation of new windows. It should be noted that the source of
     * the new window request cannot be traced reliably, and it may be initiated by a third party iframe.
     * The application needs to take defensive measures such as sandbox isolation and permission restriction
     * by default to ensure security.
     * @param {  Callback<OnWindowNewEvent> | undefined } callback The triggered callback when web page requires the user to create a window.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onWindowNew(callback: Callback<OnWindowNewEvent> | undefined): this;
    /**
     * Triggered when web page requires the user to create a window.
     * If the {@link setWebController} interface is not called, the render process will be blocked.
     * If no new window is created, it is set to null when calling the {@link setWebController} interface,
     * informing the Web that no new window is created.
     * The new window should avoid being directly overlaid on the original Web component,
     * and its URL (such as address bar) should be clearly displayed in the same form as the main page to
     * prevent users from being confused. If credible URL visualization management cannot be achieved,
     * it is necessary to consider prohibiting the creation of new windows. It should be noted that the source of
     * the new window request cannot be traced reliably, and it may be initiated by a third party iframe.
     * The application needs to take defensive measures such as sandbox isolation and permission restriction
     * by default to ensure security.
     * @param { Callback<OnWindowNewExtEvent> | undefined } callback The triggered callback when web page requires
     *     the user to create a window.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onWindowNewExt(callback: Callback<OnWindowNewExtEvent> | undefined): this;
    /**
     * Notifies the user of the window closing request.
     * Like {@link onWindowNew}, from a security perspective, applications should ensure that users can know that
     * the page they interact with is closed.
     * @param { function | undefined } callback The triggered callback when web page requires the user to close a window.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onWindowExit(callback: (() => void) | undefined): this;
    /**
     * Set whether multiple windows are supported.
     * When multiple windows permissions are enabled, the {@link onWindowNew} event needs to be implemented.
     * @param { boolean | undefined } multiWindow True if it needs to be triggered manually by the user else false.
     *    The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default multiWindowAccess(multiWindow: boolean | undefined): this;
    /**
     * Key events notify the application before the WebView consumes them.
     *
     * @param { function | undefined } callback Key event info.
     * @returns { WebAttribute } True if the application consumes key events else false.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onInterceptKeyEvent(callback: ((event: KeyEvent) => boolean) | undefined): this;
    /**
     * Sets the standard font family for the web page.
     *
     * @param { string | undefined } family Sets the standard font family for the web page.
     *    Default value: sans-serif.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webStandardFont(family: string | undefined): this;
    /**
     * Sets a serif font family for the web page.
     *
     * @param { string | undefined } family Serif font family to set.
     *    Default value: serif.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webSerifFont(family: string | undefined): this;
    /**
     * Sets the sans serif font family for the web page.
     *
     * @param { string | undefined } family Sets the sans serif font family for the web page.
     *    Default value: sans-serif.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webSansSerifFont(family: string | undefined): this;
    /**
     * Sets the fixed font family for the web page.
     *
     * @param { string | undefined } family Sets the fixed font family for the web page.
     *    Default value: monospace.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webFixedFont(family: string | undefined): this;
    /**
     * Sets the fantasy font family for the web page.
     *
     * @param { string | undefined } family Sets the fantasy font family for the web page.
     *    Default value: fantasy.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webFantasyFont(family: string | undefined): this;
    /**
     * Sets the cursive font family for the web page.
     *
     * @param { string | undefined } family Sets the cursive font family for the web page.
     *    Default value: cursive.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default webCursiveFont(family: string | undefined): this;
    /**
     * Sets the default font size for the web page.
     *
     * @param { int | undefined } size Default fixed font size to set, in px.
     *    The value ranges from -2^31 to 2^31-1. In actual rendering,
     *    values greater than 72 are handled as 72, and values less than 1 are handled as 1.
     *    Default value: 13.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default defaultFixedFontSize(size: int | undefined): this;
    /**
     * Sets the default font size for the web page.
     *
     * @param { int | undefined } size Default font size to set, in px.
     *    The value ranges from -2^31 to 2^31-1. In actual rendering, values greater than 72 are handled as 72,
     *    and values less than 1 are handled as 1. Default value: 16.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default defaultFontSize(size: int | undefined): this;
    /**
     * Sets the minimum font size for the web page.
     *
     * @param { int | undefined } size Minimum font size to set, in px.
     *    The value ranges from -2^31 to 2^31-1. In actual rendering,
     *    values greater than 72 are handled as 72, and values less than 1 are handled as 1.
     *    Default value: 8
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default minFontSize(size: int | undefined): this;
    /**
     * Sets the minimum logical font size for the web page.
     *
     * @param { int | undefined } size Minimum logical font size to set, in px.
     *    The value ranges from -2^31 to 2^31-1. In actual rendering,
     *    values greater than 72 are handled as 72, and values less than 1 are handled as 1.
     *    Default value: 8
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default minLogicalFontSize(size: int | undefined): this;
    /**
     * Set the default text encodingFormat value of webview. The default value is UTF-8.
     *
     * @param { string | undefined } textEncodingFormat text encodingFormat.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default defaultTextEncodingFormat(textEncodingFormat: string | undefined): this;
    /**
     * Set whether the scroll bar is permanent. In the resident state,
     * when the page size exceeds one page, the scroll bar appears and does not disappear.
     *
     * Scroll bar resident is not supported in full expansion mode,
     * that is, when layoutMode is WebLayoutMode.FIT_CONTENT mode, the parameter enabled is false.
     *
     * @param { boolean | undefined } enabled {@code true} means show; {@code false} otherwise. default is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default forceDisplayScrollBar(enabled: boolean | undefined): this;
    /**
     * Whether web component can load resource from network.
     *
     * @param { boolean | undefined } block {@code true} means it can't load resource from network; {@code false} otherwise.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default blockNetwork(block: boolean | undefined): this;
    /**
     * Set whether paint horizontal scroll bar.
     *
     * <p><strong>API Note</strong>:<br>
     * After controlling the horizontal scrollbar's visibility through the @State variable, you need to call controller.refresh() to take effect.<br>
     * When frequently changing the @State variable dynamically, it is recommended to match the toggle variable with the Web component one-to-one.
     * </p>
     *
     * @param { boolean | undefined } horizontalScrollBar True if it needs to paint horizontal scroll bar.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default horizontalScrollBarAccess(horizontalScrollBar: boolean | undefined): this;
    /**
     * Set whether paint vertical scroll bar, including the system default scrollbar and user-defined scrollbar.
     *
     * <p><strong>API Note</strong>:<br>
     * After controlling the vertical scrollbar's visibility through the @State variable, you need to call controller.refresh() to take effect.<br>
     * When frequently changing the @State variable dynamically, it is recommended to match the toggle variable with the Web component one-to-one.
     * </p>
     *
     * @param { boolean | undefined } verticalScrollBar True if it needs to paint vertical scroll bar.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default verticalScrollBarAccess(verticalScrollBar: boolean | undefined): this;
    /**
     * Triggered when the application receive the url of an apple-touch-icon.
     *
     * @param { Callback<OnTouchIconUrlReceivedEvent> | undefined } callback The triggered callback when the application receive an new url of an
     * apple-touch-icon.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onTouchIconUrlReceived(callback: Callback<OnTouchIconUrlReceivedEvent> | undefined): this;
    /**
     * Triggered when the application receive a new favicon for the current web page.
     *
     * @param { Callback<OnFaviconReceivedEvent> | undefined } callback The triggered callback when the application receive a new favicon for the
     * current web page.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFaviconReceived(callback: Callback<OnFaviconReceivedEvent> | undefined): this;
    /**
     * Triggered when previous page will no longer be drawn and next page begin to draw.
     *
     * @param {  Callback<OnPageVisibleEvent> | undefined } callback The triggered callback when previous page will no longer be drawn and next
     * page begin to draw.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPageVisible(callback: Callback<OnPageVisibleEvent> | undefined): this;
    /**
     * Triggered when the form could be resubmitted.
     *
     * @param { Callback<OnDataResubmittedEvent> | undefined } callback The triggered callback to decision whether resend form data or not.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onDataResubmitted(callback: Callback<OnDataResubmittedEvent> | undefined): this;
    /**
     * Sets whether to enable smooth pinch mode for the web page.
     *
     * @param { boolean | undefined } isEnabled Whether to enable smooth pinch mode for the web page.
     *    {@code true} means to enable smooth pinch mode for the web page;
     *    {@code false} means not to enable smooth pinch mode for the web page.
     *    The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default pinchSmooth(isEnabled: boolean | undefined): this;
    /**
     * Whether the window can be open automatically through JavaScript.
     * <p><strong>API Note</strong>:<br>
     * This API takes effect only when {@link JavaScript} is enabled.
     * This API opens a new window when {@link multiWindowAccess} is enabled and opens a local window
     * when {@link multiWindowAccess} is disabled.
     * The default value of **flag** is subject to the settings of the **persist.web.allowWindowOpenMethod.enabled** system attribute.
     * If this attribute is not set, the default value of **flag** is **false**.
     * To check the settings of **persist.web.allowWindowOpenMethod.enabled**,
     * run the **hdc shell param get persist.web.allowWindowOpenMethod.enabled** command.
     * If the attribute value is 1, it means the system attribute is enabled;
     * If the attribute value is 0 or does not exist, it means that the system attribute has not been enabled.
     * you can run the **hdc shell param set persist.web.allowWindowOpenMethod.enabled 1** command to enable it.
     * </p>
     *
     * @param { boolean | undefined } flag If it is true, the window can be opened automatically through JavaScript.
     * If it is false and user behavior, the window can be opened automatically through JavaScript.
     * Otherwise, the window cannot be opened.
     * The user behavior here refers to the behavior of requesting to open a new window (window. open) within 5 seconds after
     * the user clicks or performs other operations on the web component.
     * The default value is associated with system properties.
     * When the system property **persist.web.allowWindowOpenMethod.enabled** is set to true, the default value is true.
     * If the system property is not set, the default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default allowWindowOpenMethod(flag: boolean | undefined): this;
    /**
     * Set the callback function when the audio playback status on the webpage changes.
     *
     * @param { Callback<OnAudioStateChangedEvent> | undefined } callback Callback invoked when the audio playback status on the webpage changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onAudioStateChanged(callback: Callback<OnAudioStateChangedEvent> | undefined): this;
    /**
     * Triggered when the first content rendering of web page.
     *
     * @param { Callback<OnFirstContentfulPaintEvent> | undefined } callback
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFirstContentfulPaint(callback: Callback<OnFirstContentfulPaintEvent> | undefined): this;
    /**
     * Triggered when the first meaningful paint occurs on the web page.
     *
     * @param { OnFirstMeaningfulPaintCallback | undefined } callback Callback invoked when the first meaningful paint occurs on the web page.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFirstMeaningfulPaint(callback: OnFirstMeaningfulPaintCallback | undefined): this;
    /**
     * Triggered when the largest content paint occurs on the web page.
     *
     * @param { OnLargestContentfulPaintCallback | undefined } callback Callback invoked when the largest content paint occurs on the web page.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onLargestContentfulPaint(callback: OnLargestContentfulPaintCallback | undefined): this;
    /**
     * Triggered when the resources loading is intercepted.
     *
     * @param { Callback<OnLoadInterceptEvent, boolean> | undefined } callback The triggered callback when the resources loading is intercepted.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onLoadIntercept(callback: Callback<OnLoadInterceptEvent, boolean> | undefined): this;
    /**
     * The callback is triggered when the Controller is successfully bound to the Web component,
     * and the Controller must be a WebviewController, and it is forbidden to call the interface related to
     * the Web component before the event callback, otherwise a js-error exception will be thrown.
     * Because the webpage has not been loaded when the callback is called, it is impossible to use interfaces related to
     * operating webpages in the callback, such as {@link zoomIn} and {@link zoomOut}, and you can use interfaces unrelated to
     * operating webpages such as {@link loadUrl} and {@link getWebId}.
     * @param { function | undefined } callback The triggered callback when web controller initialization success.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onControllerAttached(callback: (() => void) | undefined): this;
    /**
     * Triggered when the overscroll occurs.
     * @param { Callback<OnOverScrollEvent> | undefined } callback Function triggered when the overscroll occurs.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onOverScroll(callback: Callback<OnOverScrollEvent> | undefined): this;
    /**
     * Triggered when the PDF in web page scrolling at bottom with pdf scroll event.
     * @param { Callback<OnPdfScrollEvent> | undefined } callback Function Triggered when the scrolling to bottom.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPdfScrollAtBottom(callback: Callback<OnPdfScrollEvent> | undefined): this;
    /**
     * Triggered when the PDF page load finish.
     * @param { Callback<OnPdfLoadEvent> | undefined } callback
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onPdfLoadEvent(callback: Callback<OnPdfLoadEvent> | undefined): this;
    /**
     * Called when received website security risk check result.
     *
     * @param { OnSafeBrowsingCheckResultCallback | undefined } callback - Function triggered when received website security risk check result.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onSafeBrowsingCheckResult(callback: OnSafeBrowsingCheckResultCallback | undefined): this;
    /**
     * Triggered when the website security risk check is completed.
     * <p><strong>API Note</strong>:<br>
     * Unlike onSafeBrowsingCheckResult, which is only triggered when a URL has security risks, onSafeBrowsingCheckFinish
     * is also triggered when the website security risk check is not performed or no risks are found.
     *
     * @param { OnSafeBrowsingCheckResultCallback | undefined } callback - Triggered when received website security risk check result.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onSafeBrowsingCheckFinish(callback: OnSafeBrowsingCheckResultCallback | undefined): this;
    /**
     * Called when the load committed.
     *
     * @param { OnNavigationEntryCommittedCallback | undefined } callback Function Triggered when a load committed.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNavigationEntryCommitted(callback: OnNavigationEntryCommittedCallback | undefined): this;
    /**
     * Called when tracker's cookie is prevented.
     *
     * @param { OnIntelligentTrackingPreventionCallback | undefined } callback - Callback triggered when tracker's cookie is prevented.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onIntelligentTrackingPreventionResult(callback: OnIntelligentTrackingPreventionCallback | undefined): this;
    /**
     * Injects the JavaScripts script into the Web component.
     * When the specified page or document starts to be loaded, the script is executed on any page whose source matches scriptRules.
     * <p><strong>API Note</strong>:<br>
     * The script runs before any JavaScript code of the page, when the DOM tree may not have been loaded or rendered.
     * The script is executed in the lexicographic order, not array order.
     * If the array order is required, you are advised to use the runJavaScriptOnDocumentStart interface.
     * You are not advised to use this API together with runJavaScriptOnDocumentStart.
     * When scripts with identical content are injected multiple times,
     * silent deduplication will be performed: repeated scripts will neither be displayed nor prompted,
     * and the scriptRules used during the first injection will be adopted.
     * </p>
     *
     * @param { Array<ScriptItem> | undefined } scripts - The array of the JavaScripts to be injected.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default javaScriptOnDocumentStart(scripts: Array<ScriptItem> | undefined): this;
    /**
     * Injects the JavaScripts script into the Web component.
     * When the specified page or document has been loaded, the script is executed on any page whose source matches scriptRules.
     * <p><strong>API NOTE</strong>:<br>
     * The script runs after any JavaScript code of the page, when the DOM tree has been loaded and rendered.
     * The script is excuted in the lexicographic order, not array order.
     * If the array order is required, you are advised to use the runJavaScriptOnDocumentEnd interface.
     * You are not advised to use this API together with runJavaScriptOnDocumentEnd.
     * When scripts with identical content are injected multiple times,
     * silent deduplication will be performed: repeated scripts will neither be displayed nor prompted,
     * and the scriptRules used during the first injection will be adopted.
     * <p>
     *
     * @param { Array<ScriptItem> | undefined } scripts - The array of the JavaScripts to be injected.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default javaScriptOnDocumentEnd(scripts: Array<ScriptItem> | undefined): this;
    /**
     * Sets the web layout mode.
     *
     * <p><strong>API Note</strong>:<br>
     * Currently, only two web layout modes are supported: WebLayoutMode.NONE and WebLayoutMode.FIT_CONTENT.
     * The following restrictions apply with the usage of WebLayoutMode.FIT_CONTENT:
     * - If the Web component is wider or longer than 7680 px, specify the RenderMode.SYNC_RENDER mode
     *   when creating the Web component; otherwise, the screen may be blank.
     * - After the Web component is created, dynamic switching of the layoutMode is not supported.
     * - The width and height of a Web component cannot exceed 500,000 px when the RenderMode.SYNC_RENDER mode is specified,
     *   and cannot exceed 7680 px when the RenderMode.ASYNC_RENDER mode is specified.
     * - Frequent changes to the page width and height will trigger a re-layout of the Web component,
     *   which can affect the user experience.
     * - Waterfall web pages are not supported (drop down to the bottom to load more).
     * - Only height adaptation is supported. Width adaptation is not supported.
     * - Because the height is adaptive to the web page height,
     *   the component height cannot be changed by modifying the component height attribute.
     * </p>
     *
     * @param { WebLayoutMode | undefined } mode - The web layout mode, follow the system or adaptive layout.
     *    The default value is WebLayoutMode.NONE.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default layoutMode(mode: WebLayoutMode | undefined): this;
    /**
     * Called to setting the nested scroll options.
     *
     * <p><strong>API Note</strong>:<br>
     * You can set four directions: up, down, left, and right, or set nested scrolling modes for forward and backward directions
     * to achieve scrolling linkage with the parent component.<br>
     * When value is of type NestedScrollOptionsExt (four directions: up, down, left, and right), the default scrolling options
     * for scrollUp, scrollDown, scrollLeft, and scrollRight are NestedScrollMode.SELF_FIRST.<br>
     * When value is of type NestedScrollOptions (two directions: forward and backward), the default scrolling options for scrollForward
     * and scrollBackward are NestedScrollMode.SELF_FIRST.<br>
     * Supported nested scrolling containers: Grid, List, Scroll, Swiper, Tabs, WaterFlow, Refresh, bindSheet.<br>
     * Supported nested scrolling input events: gestures, mouse, and trackpad.<br>
     * In nested scrolling scenarios, since web scrolling to the edge will prioritize triggering the overscroll bounce effect,
     * it is recommended to set overScrollMode to OverScrollMode.NEVER to avoid affecting the user experience in this scenario.
     * </p>
     *
     * @param { NestedScrollOptions | NestedScrollOptionsExt | undefined } value - options for
     *     nested scrolling.
     * @returns { WebAttribute } the attribute of the scroll.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default nestedScroll(value: NestedScrollOptions | NestedScrollOptionsExt | undefined): this;
    /**
     * Sets whether to enable the same-layer rendering feature.
     *
     * <p><strong>API Note</strong>:
     * <strong>Performance Note</strong>:
     * <p>For details about how to rendering native components on the Web using same-layer rendering.
     * </p>
     *
     * @param { boolean | undefined } enabled - Whether to enable the same-layer rendering feature.
     *    The value true means to enable the same-layer rendering feature, and false means the opposite.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableNativeEmbedMode(enabled: boolean | undefined): this;
    /**
     * Registers the HTML tag name and type for same-layer rendering.
     * The tag name only supports object and embed.
     * The tag type only supports visible ASCII characters.<br>
     * If the specified type is the same as the W3C standard object or embed type,
     * the ArkWeb kernel identifies the type as a non-same-layer tag.<br>
     * This API is also controlled by the enableNativeEmbedMode API and
     * does not take effect if same-layer rendering is not enabled. When this API is not used,
     * the ArkWeb kernel recognizes the embed tags with the "native/" prefix as same-layer tags.
     *
     * @param { string | undefined } tag - Tag name.
     * @param { string | undefined } type - Type of the tag, The kernel matches this parameter with a prefix.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default registerNativeEmbedRule(tag: string | undefined, type: string | undefined): this;
    /**
     * Triggered when embed lifecycle changes.
     *
     * <p><strong>API Note</strong>:
     * <strong>Performance Note</strong>:
     * <p>For details about how to rendering native components on the Web using same-layer rendering.
     * </p>
     *
     * @param { function | undefined } callback - Function Triggered when embed lifecycle changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNativeEmbedLifecycleChange(callback: ((event: NativeEmbedDataInfo) => void) | undefined): this;
    /**
     * Called when the visibility of a same-layer tag (such as an Embed tag or an Object tag) on a web page changes in the viewport.
     * By default, the same-layer tag is invisible. If the rendering tag is visible when you access the page for the first time,
     * the callback is triggered; otherwise, it is not triggered. That is, if the same-layer tag changes from a non-zero value to 0 x 0,
     * the callback is triggered. If the rendering tag size changes from 0 x 0 to a non-zero value, the callback is not triggered.
     * If all the same-layer tags are invisible, they are reported as invisible. If all the same-layer rendering tags or part of them are visible,
     * they are reported as invisible.
     *
     * @param { OnNativeEmbedVisibilityChangeCallback | undefined } callback - Callback invoked when the visibility of a same-layer tag changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNativeEmbedVisibilityChange(callback: OnNativeEmbedVisibilityChangeCallback | undefined): this;
    /**
     * Triggered when gesture effect on embed tag.
     *
     * <p><strong>API Note</strong>:
     * <strong>Performance Note</strong>:
     * <p>For details about how to rendering native components on the Web using same-layer rendering.
     * </p>
     *
     * @param { function | undefined } callback - Function Triggered when gesture effect on embed tag.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNativeEmbedGestureEvent(callback: ((event: NativeEmbedTouchInfo) => void) | undefined): this;
    /**
     * Triggered when mouse effect on embed tag.
     *
     * @param { MouseInfoCallback | undefined } callback - callback Triggered when mouse effect on embed tag.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNativeEmbedMouseEvent(callback: MouseInfoCallback | undefined): this;
    /**
     * Called to set copy option
     *
     * @param { CopyOptions | undefined } value - copy option.The default value is CopyOptions.LocalDevice.
     * @returns { WebAttribute } the attribute of the scroll.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default copyOptions(value: CopyOptions | undefined): this;
    /**
     * When the URL is about to be loaded into the current Web, it gives the application the opportunity to take control.
     * This will not called for POST requests, may be called for subframes and with non-HTTP(S) schemes.
     *
     * @param { OnOverrideUrlLoadingCallback | undefined } callback - The callback for onOverrideUrlLoading.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onOverrideUrlLoading(callback: OnOverrideUrlLoadingCallback | undefined): this;
    /**
     * Triggered when the web page's document resource error.
     * <p><strong>API Note</strong>:<br>
     * This only triggered for main frame.
     * </p>
     *
     * @param { OnOverrideErrorPageCallback | undefined } callback The triggered function when the
     * web page's document resource error.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onOverrideErrorPage(callback: OnOverrideErrorPageCallback | undefined): this;
    /**
     * Sets whether automatic text resizing is enabled.
     * After the automatic text font size adjustment takes effect,
     * the font size will be automatically increased to 16px~32px
     * for text with too small font size to avoid the readability problem of
     * small fonts due to the lack of mobile adaptation for devices with small screens (default viewport width < 980px).
     *
     * <p><strong>API Note</strong>:<br>
     * Prerequisites for the automatic adjustment of text font size to take effect:
     * 1.The device forms are: Phone, Tablet, Wearable, TV.
     * 2.Web component viewport width < 980px.
     * 3.The page text is large, and the font size * number of characters of the page text is ≥ 3920.
     * 4.There is no metaViewport setting on the frontend, or no "width" and "initial-scale" attributes in the metaViewport setting.
     *
     * @param { boolean | undefined } textAutosizing - Whether automatic text resizing is enabled.
     *    {@code true} means enable text autosizing;
     *    {@code false} means disable text autosizing.
     *    Default value: true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default textAutosizing(textAutosizing: boolean | undefined): this;
    /**
     * Enable the application takeover of web media playback feature.
     *
     * @param { NativeMediaPlayerConfig | undefined } config - The configuration of native media player.
     *    enable: whether to enable the feature, shouldOverlay: whether the image of the video player
     *    taken over by the application will overlay the web page content, if this feature is enabled.
     *    Default value: {enable: false, shouldOverlay: false}.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableNativeMediaPlayer(config: NativeMediaPlayerConfig | undefined): this;
    /**
     * Triggered when render process not responding.
     * If the Web component can't handle the input event, or can't navigate to the new URL within a reasonable time range,
     * the Web page process is considered unresponsive and the callback will be triggered.
     * As long as the web process has been unresponsive, this callback may continue to trigger until
     * the web process responds again, at which time {@link onRenderProcessResponding} will trigger.
     * Applications can terminate the associated rendering process through the WebviewController interface {@link terminateRenderProcess},
     * which may affect other Web components in the same rendering process.
     * @param { OnRenderProcessNotRespondingCallback | undefined } callback The triggered function when render process not responding.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onRenderProcessNotResponding(callback: OnRenderProcessNotRespondingCallback | undefined): this;
    /**
     * This callback function is triggered when the rendering process changes from unresponsive state to normal operation state,
     * which indicates that the webpage is not really stuck.
     *
     * @param { OnRenderProcessRespondingCallback | undefined } callback The triggered function when the unresponsive render process becomes responsive.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onRenderProcessResponding(callback: OnRenderProcessRespondingCallback | undefined): this;
    /**
     * Called when the viewport-fit configuration in the web page's <meta> tag changes.
     * The application can adapt its layout to the viewport within this callback.
     *
     * @param { OnViewportFitChangedCallback | undefined } callback - Callback invoked when the viewport-fit configuration in the web page's <meta> tag changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onViewportFitChanged(callback: OnViewportFitChangedCallback | undefined): this;
    /**
     * Editable elements (such as input labels) in web pages will call back to this interface before pulling up
     * the soft keyboard. Applications can use this interface to intercept the pop-up of the system soft keyboard
     * and configure the application-customized soft keyboard (according to this interface,
     * the application can decide to use the system default soft keyboard/the system soft keyboard with
     * the enter key customized/all the soft keyboards customized by the application).
     *
     * @param { WebKeyboardCallback | undefined } callback - The callback for onInterceptKeyboardAttach.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onInterceptKeyboardAttach(callback: WebKeyboardCallback | undefined): this;
    /**
     * Called when received Ads blocked results.
     * If blocked results exist at the end of page loading, the first call will be triggered.
     * To avoid performance issues, subsequent results will be periodically reported through this api.
     *
     * @param { OnAdsBlockedCallback | undefined } callback - The callback for OnAdsBlockedCallback.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onAdsBlocked(callback: OnAdsBlockedCallback | undefined): this;
    /**
     * When the keyboard avoidance mode set by UIContext is {@link KeyboardAvoidMode.RESIZE} mode,
     * the interface function will not take effect.
     *
     * @param { WebKeyboardAvoidMode | undefined } mode - The web keyboard avoid mode, which can be {@link WebKeyboardAvoidMode}.
     *                                                    Web soft keyboard avoidance is not recommended in nested scrolling scenes,
     *                                                    including RESIZE_VISUAL and RESIZE_CONTENT.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default keyboardAvoidMode(mode: WebKeyboardAvoidMode | undefined): this;
    /**
     * Set the custom text menu.
     *
     * <p><strong>API Note</strong>:<br>
     * The onCreateMenu interface is used to modify, add, and delete menu options.If you want to hide the text menu,
     * you need to return an empty array.<br>
     * The onMenuItemClick interface allows you to define the callback function for menu options.This function is
     * triggered when a menu option is clicked, and it determines whether to execute the system's default callback
     * based on the return value. Returning true prevents the system callback from executing, while returning false
     * continues with the system callback.<br>
     * The editMenuOptions interface makes the selectionMenuOptions (deprecated) not work when used at the same time.
     * </p>
     *
     * @param { EditMenuOptions | undefined } editMenu - Customize text menu options.
     *                                                   The number of menu items, as well as the content size and icon size of the menu,
     *                                                   should be consistent with the ArkUI Menu component.
     *                                                   The system-provided id enumeration values (TextMenuItemId) in the menu are only
     *                                                   supported for CUT, COPY, PASTE, SELECT_ALL, TRANSLATE, SEARCH and some AI menu in the web.
     *                                                   The textRange parameter in the onMenuItemClick function is meaningless in the web,
     *                                                   and the input value is -1.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default editMenuOptions(editMenu: EditMenuOptions | undefined): this;
    /**
     * Enable or disable haptic feedback.
     *
     * <p><strong>API Note</strong>:<br>
     * Permissions need to be configured: ohos.permission.VIBRATE.
     * </p>
     *
     * @param { boolean | undefined } enabled - Default value is true, set false to disable haptic feedback.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableHapticFeedback(enabled: boolean | undefined): this;
    /**
     * Bind to the selection menu.
     *
     * @param { WebElementType | undefined } elementType - Indicates the type of selection menu.
     * @param { CustomBuilder | undefined } content - Indicates the content of selection menu.
     * @param { WebResponseType | undefined } responseType - Indicates response type of selection menu.
     * @param { SelectionMenuOptionsExt | undefined } [options] - Indicates the options of selection menu.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default bindSelectionMenu(elementType: WebElementType | undefined, content: CustomBuilder | undefined, responseType: WebResponseType | undefined, options?: SelectionMenuOptionsExt | undefined): this;
    /**
     * Sets whether to follow the system font weight.
     *
     * @param { boolean | undefined } follow The value true means to follow the system font weight, and false means the opposite.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableFollowSystemFontWeight(follow: boolean | undefined): this;
    /**
     * Sets whether to enable AVSession for web pages.
     *
     * @param { boolean | undefined } enabled Whether to enable AVSession. The value true means to enable AVSession, and false means the opposite.
     *    False when passing in undefined and null.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableWebAVSession(enabled: boolean | undefined): this;
    /**
     * Sets whether to optimize parser budget to reduce FCP time
     *
     * @param { boolean | undefined } optimizeParserBudget Default value is false, set true to enable optimize parser budget.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default optimizeParserBudget(optimizeParserBudget: boolean | undefined): this;
    /**
     * Injects the JavaScripts that will be run just after document object has been created.
     *
     * @param { Array<ScriptItem> | undefined } scripts - The JavaScripts executed in array order.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default runJavaScriptOnDocumentStart(scripts: Array<ScriptItem> | undefined): this;
    /**
     * Injects the JavaScripts that will be run after document has been parsed finished.
     *
     * @param { Array<ScriptItem> | undefined } scripts - The JavaScripts executed in array order.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default runJavaScriptOnDocumentEnd(scripts: Array<ScriptItem> | undefined): this;
    /**
     * Injects the JavaScripts that will be run after head element has been parsed finished.
     *
     * @param { Array<ScriptItem> | undefined } scripts - The JavaScripts executed in array order.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default runJavaScriptOnHeadEnd(scripts: Array<ScriptItem> | undefined): this;
    /**
     * Sets the embed options, only valid when enableNativeEmbedMode is true.
     *
     * @param { EmbedOptions | undefined } options - The embed options, which can be {@link EmbedOptions}.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default nativeEmbedOptions(options?: EmbedOptions | undefined): this;
    /**
     * Enable data detector.
     *
     * @param { boolean | undefined } enable - {@code true} means enable data detector in Web;{@code false} otherwise.
     *    The default value is false.
     * @returns { WebAttribute } The attribute of the web.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableDataDetector(enable: boolean | undefined): this;
    /**
     * Data detector with config.
     *
     * @param { TextDataDetectorConfig | undefined } config - The config of text data detector.
     * @returns { WebAttribute } The attribute of the web.
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default dataDetectorConfig(config: TextDataDetectorConfig | undefined): this;
    /**
     * Triggered when the web page is activated for window.open called by other web component.
     *
     * @param { VoidCallback | undefined } callback the triggered function when the web page is activated for window.open called by other web component.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onActivateContent(callback: VoidCallback | undefined): this;
    /**
     * Set up a condition that bypass vsync
     * If the condition is matched, the drawing schedule does not reply on Vsync scheduling
     * and directly rendering and drawing
     *
     * @param { WebBypassVsyncCondition | undefined } condition - The condition to bypass render vsync.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default bypassVsyncCondition(condition: WebBypassVsyncCondition | undefined): this;
    /**
     * Set the gesture focus acquisition mode.
     * When users interact with the web using different gestures,
     * this determines whether and when focus is acquired based on the configured mode.
     * Default value: DEFAULT, where all gestures acquire focus on touch down.
     *
     * @param { GestureFocusMode | undefined } mode - The gesture focus mode, which can be {@link GestureFocusMode}.
     *    The default value is FocusMode.DEFAULT.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default gestureFocusMode(mode: GestureFocusMode | undefined): this;
    /**
     * Set whether to comply with the zoom restrictions set by the<meta name="viewport">tag in the webpage.
     *
     * @param { boolean | undefined } enable {@code true} means the Web will not comply with the zoom restrictions
     *     set by the<meta name="viewport">tag on the webpage; {@code false} otherwise.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default forceEnableZoom(enable: boolean | undefined): this;
    /**
     * Triggered when the param element which is a child item of the object element has changed.
     *
     * @param { OnNativeEmbedObjectParamChangeCallback | undefined } callback - callback Triggered when the param element has changed.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onNativeEmbedObjectParamChange(callback: OnNativeEmbedObjectParamChangeCallback | undefined): this;
    /**
     * Set up the effect of web rotation
     *
     * @param { WebRotateEffect | undefined } effect - The effect of rotation.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default rotateRenderEffect(effect: WebRotateEffect | undefined): this;
    /**
     * Sets whether the Web supports zooming using Ctrl.
     *
     * @param { boolean | undefined } zoomControlAccess - {@code true} means the Web supports zooming using Ctrl,
     *    {@code false} otherwise.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default zoomControlAccess(zoomControlAccess: boolean | undefined): this;
    /**
     * Triggered when web engine detects the current page is blank screen or nearly blank.
     *
     * @param { OnDetectBlankScreenCallback | undefined } callback - callback triggered when web engine detects
     *     current page is blank or nearly blank.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onDetectedBlankScreen(callback: OnDetectBlankScreenCallback | undefined): this;
    /**
     * The options for blank screen detection.
     *
     * @param { BlankScreenDetectionConfig | undefined } detectConfig - the strategy config for detection.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default blankScreenDetectionConfig(detectConfig: BlankScreenDetectionConfig | undefined): this;
    /**
     * Set whether to enable the back-to-top feature for web component when the status bar is touched.
     *
     * @param { boolean | undefined } backToTop {@code true} means enable the back-to-top feature,
     *     when the status bar is touched. {@code false} otherwise. The default value is true.
     *     True when passing in undefined and null.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default backToTop(backToTop: boolean | undefined): this;
    /**
    * Enable selected data detector.
    *
    * @param { boolean | undefined } enable - whether to enable the selected data detector.
    *     {@code true} means enable all select data detector in Web;{@code false} otherwise.
    *     The default value is true.
    * @returns { WebAttribute }
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
    default enableSelectedDataDetector(enable: boolean | undefined): this;
    /**
     * Triggered after the first screen of the web page has been painted.
     * The first screen contains the images, videos and texts in the viewport of the current navigation.
     * The callback will not be triggered immediately when the first screen has been painted,
     * but in a few seconds according to the current network condition.
     * However, if the user scrolls or inputs before the first screen has been painted,
     * the callback will be triggered immediately.
     * @param { OnFirstScreenPaintCallback | undefined } callback - callback triggered to
     *     report the info for the first screen painting of the current web page.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onFirstScreenPaint(callback: OnFirstScreenPaintCallback | undefined): this;
    /**
     * Sets whether enable auto fill or not.
     *
     * @param { boolean | undefined } value - Indicates the flag whether autofill is enabled.
     *      Default value is true.true: enable, false: disable.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableAutoFill(value: boolean | undefined): this;
    /**
     * Called when the text selection changes.
     *
     * @param { TextSelectionChangeCallback | undefined } callback - when the text selection changes.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onTextSelectionChange(callback: TextSelectionChangeCallback | undefined): this;
    /**
     * Set up web component to support AI image recognition capability.
     *
     * @param { boolean | undefined } enable - {@code true} means the Web AI image recognition capability,
     *    {@code false} otherwise.
     *    The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default enableImageAnalyzer(enable: boolean | undefined): this;
    /**
     *  Triggered after camera capture state changed.
     *
     * @param { OnCameraCaptureStateChangeCallback } callback -  Callback triggered to
     *    report current page camera capture state changing event.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onCameraCaptureStateChange(callback: OnCameraCaptureStateChangeCallback | undefined): this;
    /**
     *  Triggered after microphone capture state changed.
     *
     * @param { OnMicrophoneCaptureStateChangeCallback } callback -  callback triggered to
     *    report current page microphone capture state changing event.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    default onMicrophoneCaptureStateChange(callback: OnMicrophoneCaptureStateChangeCallback | undefined): this;
    /**
     * Set whether to enable the default right-click context menu.
     *
     * @param { boolean | undefined } enable - {@code true} means the Web enable the default right-click context menu,
     *    {@code false} otherwise.
     *    The default value is false.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 24
     */
    default enableDefaultContextMenu(enable: boolean | undefined): this;
    /**
     * Enables or disables dragging for this component.
     *
     * @param { boolean | undefined } value - {@code true} to enable dragging, {@code false} to disable it.
     *     The default value is true.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    default enableDrag(value: boolean | undefined): this;
    // instructive change start
    default aiSessionOptions(value: Array<AISessionEvent> | undefined): this;
    // instructive change end
    /**
     * Sets the scrollbar layout policy.
     *
     * @param { ScrollbarLayoutPolicy | undefined } policy - The layout policy to apply.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    default scrollbarLayoutPolicy(policy: ScrollbarLayoutPolicy | undefined): this;
    /**
     * Enables or disables directional lock for scroll gestures in the WebView component.
     *
     * When directional lock is enabled, the scroll axis is locked based on the initial
     * swipe vector direction. This behavior helps prevent unintended scroll direction changes
     * during touch interactions, especially in nested scroll scenarios.
     *
     * @param { boolean | undefined } value - Whether to enable directional lock.
     *     - `true`: Enables directional lock (default in nested scroll scenarios).
     *     - `false`: Disables directional lock.
     * @param { ScrollDirectionalLockType | undefined } type - Specifies the scenario in which directional lock is applied.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    default enableScrollDirectionalLock(value: boolean | undefined, type: ScrollDirectionalLockType | undefined): this;
    /**
     * Set the attribute modifier
     *
     * @param { AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined } modifier
     * @returns { WebAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default attributeModifier(modifier: AttributeModifier<WebAttribute> | AttributeModifier<CommonMethod> | undefined): this;

    /**
    * Set the WebKeyboardAppearanceMode to determine the immersive mode for the soft keyboard.
    *
    * @param { WebKeyboardAppearanceMode | undefined } mode - The WebKeyboardAppearanceMode of this web.
    * @returns { WebAttribute }
    * @syscap SystemCapability.Web.Webview.Core
    * @stagemodelonly
    * @since 26.0.0
    */
    default keyboardAppearance(mode: WebKeyboardAppearanceMode | undefined): this;

    /**
     * The callback is triggered when the inputmethod is attached to the IMF.
     *
     * @param { OnInputmethodAttachedCallback | undefined } callback - The triggered callback
     *    when the inputmethod is attached to the IMF.
     * @returns { WebAttribute }
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    default onInputmethodAttached(callback: OnInputmethodAttachedCallback | undefined): this;
}

/**
 * Defines the ssl error event.
 *
 * @typedef SslErrorEvent
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface SslErrorEvent {
    /**
     * Notifies the user of the operation behavior of the web component.
     *
     * @type { SslErrorHandler }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: SslErrorHandler;
    /**
     * Error codes.
     *
     * @type { SslError }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    error: SslError;
    /**
     * Request url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    url: string;
    /**
     * Original url.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    originalUrl: string;
    /**
     * Referrer.
     *
     * @type { string }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    referrer: string;
    /**
     * Whether the error is fatal.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isFatalError: boolean;
    /**
     * Whether the request is main frame.
     *
     * @type { boolean }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    isMainFrame: boolean;
    /**
     * Certificate chain data in DER format.
     *
     * @type { ?Array<Uint8Array> }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    certChainData?: Array<Uint8Array>;
}
/**
 * Defines the event for PIN verification.
 *
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface VerifyPinEvent {
    /**
     * Handle the result of PIN verification.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    handler: VerifyPinHandler;
    /**
     * The identity of the Credential.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    identity: string;
  }
/**
 * Define nested scroll options
 *
 * @interface NestedScrollOptionsExt
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface NestedScrollOptionsExt {
    /**
     * Set NestedScrollMode when the scrollable component scrolls up
     *
     * @type { ?NestedScrollMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    scrollUp?: NestedScrollMode;
    /**
     * Set NestedScrollMode when the scrollable component scrolls down
     *
     * @type { ?NestedScrollMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    scrollDown?: NestedScrollMode;
    /**
     * Set NestedScrollMode when the scrollable component scrolls right
     *
     * @type { ?NestedScrollMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    scrollRight?: NestedScrollMode;
    /**
     * Set NestedScrollMode when the scrollable component scrolls left
     *
     * @type { ?NestedScrollMode }
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    scrollLeft?: NestedScrollMode;
}
/**
 * Defines the Embed Options.
 *
 * @typedef EmbedOptions
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface EmbedOptions {
    /**
     * Whether the embed element support the default intrinsic size of 300 * 150, expressed in CSS pixels.
     * <br>When CSS size is set, the embed element size is CSS size, otherwise it is intrinsic size.
     * <br>If true, then the intrinsic size is 300 * 150.
     * <br>If false, the embed element will not be rendered when the CSS size is not set.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    supportDefaultIntrinsicSize?: boolean;
    /**
     * Whether the {@link onNativeEmbedVisibilityChange} event supports display-related attributes
     * of the embed element.
     * <br>Default value is false. If true, the changes of the display-related attributes of the
     * embed element will be reported through the {@link onNativeEmbedVisibilityChange} event.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    supportCssDisplayChange?: boolean;
}
/**
 * Enum type supplied to {@link gestureFocusMode} for setting the web gesture focus mode.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum GestureFocusMode {
    /**
     * Any action on a web component, such as tapping, long-pressing, scrolling, zooming, etc.,
     * will cause the web component to acquire focus on touch down.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    DEFAULT = 0,
    /**
     * Tap and long-press gestures will cause the web component to acquire focus after touch up,
     * while gestures such as scrolling, zooming, etc., do not request focus.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    GESTURE_TAP_AND_LONG_PRESS = 1
}
/**
* Define file selection type.
*
* @typedef AcceptableFileType
* @syscap SystemCapability.Web.Webview.Core
* @since 23
*/
export declare interface AcceptableFileType {
  /**
    * A annotated file type identifier used to describe the format and content type of a file.
    *
    * @type { string }
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
  mimeType: string;
  /**
    * Array of file types accepted by web pages.
    *
    * @type { Array<string> }
    * @syscap SystemCapability.Web.Webview.Core
    * @since 23
    */
  acceptableType: Array<string>;
}
/**
 * Defines Web Component.
 *
 * @param { WebOptions } value.
 * @param { CustomBuilder } [content_] - container
 * @returns { WebAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
@ComponentBuilder
export declare function Web(
    value: WebOptions,
    content_?: CustomBuilder,
): WebAttribute
/**
 * Enum type supplied to {@link PinVerifyResult} when VerifyPinHandler#confirm being called.
 *
 * @enum { int }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum PinVerifyResult {
    /**
     * SUCCESS.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PIN_VERIFICATION_SUCCESS = 0,
    /**
     * FAILED.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    PIN_VERIFICATION_FAILED = 1
}
/**
 * Enum type supplied to {@link CredentialType} when ClientAuthenticationHandler#confirm being called.
 *
 * @enum { int }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum CredentialType {
    /**
     * User credential.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CREDENTIAL_USER = 2,
    /**
     * Application-specific credential.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CREDENTIAL_APP = 3,
    /**
     * Hardware security key credential.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @since 23
     */
    CREDENTIAL_UKEY = 4,
  }
/**
 * Defines the camera capture state change info.
 *
 * @typedef CameraCaptureStateChangeInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface CameraCaptureStateChangeInfo {
  /**
   * The original camera capture state.
   *
   * @type { CameraCaptureState }
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  originalState: CameraCaptureState;

  /**
   * The new camera capture state.
   *
   * @type { CameraCaptureState }
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  newState: CameraCaptureState;
}
/**
 * Indicates current camera capture state of current web page.
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum CameraCaptureState {
  /**
   * None of any cameras are in use.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  NONE = 0,
  /**
   * This web page is not actively using camera capturing.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  PAUSED = 1,
  /**
   * This web page is actively using camera capturing.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  ACTIVE = 2,
}
/**
 * Defines the microphone capture state change info.
 *
 * @typedef MicrophoneCaptureStateChangeInfo
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare interface MicrophoneCaptureStateChangeInfo {
  /**
   * the original microphone capture state.
   * @type { MicrophoneCaptureState}
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  originalState: MicrophoneCaptureState;

  /**
   * the new microphone capture state.
   *
   * @type { MicrophoneCaptureState }
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  newState: MicrophoneCaptureState;
}
/**
 * Indicates current microphone capture state of current web page.
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @since 23
 */
export declare enum MicrophoneCaptureState {
  /**
   * None of any microphone are in use.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  NONE = 0,
  /**
   * This web page is not actively using microphone capturing.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  PAUSED = 1,
  /**
   * This web page is actively using microphone capturing.
   * @syscap SystemCapability.Web.Webview.Core
   * @since 23
   */
  ACTIVE = 2,
}
// instructive change start
export type OnCreateAISession = (id: string, params: string, result: OnAISessionCallback) => boolean;
export type OnExecuteAIAction = (id: string, params: string, result: OnAISessionCallback) => void;
export type OnDestroyAISession = (id: string) => void;
export interface AISessionEvent {
    aiSessionType: AISessionType;
    onCreateAISession: OnCreateAISession;
    onExecuteAIAction: OnExecuteAIAction;
    onDestroyAISession: OnDestroyAISession;
}
export enum AISessionType {
    TRANSLATOR = 1,
    LANGUAGE_DETECTOR = 2,
    SUMMARIZER = 3,
    WRITER = 4,
    REWRITER = 5,
    PROMPT = 6,
    PROOFREADER = 7
}
export enum AISessionResultType {
    SUCCESS = 0,
    FAILURE = 1,
    RUNNING = 2
}
export type OnAISessionCallback = (state: AISessionResultType, content: string) => void;
// instructive change end
/**
 * Defines the layout policy for scrollbars, used with {@link scrollbarLayoutPolicy}.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @stagemodelonly
 * @since 26.0.0
 */
export declare enum ScrollbarLayoutPolicy {
    /**
     * Adheres to W3C standards (CSS/HTML/XHTML) for scrollbar layout.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    CONTENT = 0,

    /**
     * Follows the system UI conventions for scrollbar layout in the system language.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    SYSTEM = 1
}
/**
 * Enum defining the scope of directional lock behavior in the WebView, used with {@link enableScrollDirectionalLock}.
 *
 * @enum { number }
 * @syscap SystemCapability.Web.Webview.Core
 * @stagemodelonly
 * @since 26.0.0
 */
export declare enum ScrollDirectionalLockType {
    /**
     * Applies directional lock across all scroll contexts.
     * This includes both nested and flat scroll scenarios.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    ALL = 0,

    /**
     * Applies directional lock only within nested scroll scenarios.
     * This is the default behavior in ArkWeb to improve UX in complex scroll hierarchies.
     *
     * @syscap SystemCapability.Web.Webview.Core
     * @stagemodelonly
     * @since 26.0.0
     */
    NESTED_SCROLL = 1
}
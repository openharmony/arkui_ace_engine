/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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
/**
 * @file
 * @kit ArkUI
 */
import { AsyncCallback } from '@ohos.base';
import BaseContext from 'application.BaseContext';
import image from '@ohos.multimedia.image';
import ConfigurationConstant from '@ohos.app.ability.ConfigurationConstant';
import { LocalStorage } from '@ohos.arkui.stateManagement';
import { UIContext } from '@ohos.arkui.UIContext';
import { ColorMetrics } from '@ohos.arkui.node';
/**
 * Defines the window callback.
 *
 * @typedef {function}
 * @syscap SystemCapability.Window.SessionManager
 * @since 20
 */
type Callback<T, V = void> = (data: T) => V;
/**
 * Window manager.
 *
 * @namespace window
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 */

/**
 * Window manager.
 *
 * @namespace window
 * @syscap SystemCapability.WindowManager.WindowManager.Core
 * @since 20
 */
declare namespace window {
    
    /**
     * The type of a window.
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export enum WindowType {
        /**
         * App.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @FAModelOnly
         * @since 20
         */
        TYPE_APP = 0,
        /**
         * Status bar.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_STATUS_BAR = 3,
        /**
         * Panel.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_PANEL = 4,
        /**
         * Keyguard.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_KEYGUARD = 5,
        /**
         * Volume.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_VOLUME_OVERLAY = 6,
        /**
         * Navigation bar.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_NAVIGATION_BAR = 7,
        
        /**
         * Float.
         * Require "ohos.permission.SYSTEM_FLOAT_WINDOW" permission
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        TYPE_FLOAT = 8,
        /**
         * Wallpaper.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_WALLPAPER = 9,
        /**
         * Desktop.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_DESKTOP = 10,
        /**
         * Recent.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_LAUNCHER_RECENT = 11,
        /**
         * Dock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_LAUNCHER_DOCK = 12,
        /**
         * Voice interaction.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_VOICE_INTERACTION = 13,
        /**
         * Pointer.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_POINTER = 14,
        /**
         * Float camera.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_FLOAT_CAMERA = 15,
        
        /**
         * Dialog.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        TYPE_DIALOG = 16,
        /**
         * Screenshot.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_SCREENSHOT = 17,
        /**
         * System Toast.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_SYSTEM_TOAST = 18,
        /**
         * Divider.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_DIVIDER = 19,
        /**
         * Global Search.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_GLOBAL_SEARCH = 20,
        /**
         * Handwrite.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        TYPE_HANDWRITE = 21,
        /**
         * TYPE_WALLET_SWIPE_CARD.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        TYPE_WALLET_SWIPE_CARD = 22,
        /**
         * Screen Control
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        TYPE_SCREEN_CONTROL = 23,
        /**
         * TYPE_FLOAT_NAVIGATION.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        TYPE_FLOAT_NAVIGATION = 24
    }
    
    
    /**
     * Describes the type of avoid area
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export enum AvoidAreaType {
        
        
        /**
         * Default area of the system
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        TYPE_SYSTEM = 0,
        
        
        /**
         * Notch
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        TYPE_CUTOUT = 1,
        
        
        /**
         * Area for system gesture
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        TYPE_SYSTEM_GESTURE = 2,
        
        
        /**
         * Area for keyboard
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        TYPE_KEYBOARD = 3,
        
        /**
         * Area for navigation indicator
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        TYPE_NAVIGATION_INDICATOR = 4
    }
    /**
     * Describes the window mode of an application
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export enum WindowMode {
        /**
         * Floating mode of the window
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        FLOATING = 5
    }
    
    
    /**
     * Describes the window status of an application
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export enum WindowStatusType {
        
        
        /**
         * Undefined status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        UNDEFINED = 0,
        
        
        /**
         * Full screen status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        FULL_SCREEN = 1,
        
        /**
         * Maximize status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        MAXIMIZE = 2,
        
        
        /**
         * Minimize status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        MINIMIZE = 3,
        
        
        /**
         * Floating status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        FLOATING = 4,
        
        
        /**
         * Split screen status of the window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        SPLIT_SCREEN = 5
    }
    
    
    /**
     * Properties of status bar and navigation bar, it couldn't update automatically
     *
     * @interface SystemBarProperties
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface SystemBarProperties {
        
        
        /**
         * The color of the status bar.
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        statusBarColor?: string;
        
        
        /**
         * The light icon of the status bar.
         *
         * @type { ?boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isStatusBarLightIcon?: boolean;
        
        /**
         * The content color of the status bar
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        statusBarContentColor?: string;
        
        
        /**
         * The color of the navigation bar.
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        navigationBarColor?: string;
        
        
        /**
         * The light icon of the navigation bar.
         *
         * @type { ?boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isNavigationBarLightIcon?: boolean;
        
        /**
         * The content color of the navigation bar
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        navigationBarContentColor?: string;
        
        /**
         * Enable the animation of the status bar.
         *
         * @type { ?boolean }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        enableStatusBarAnimation?: boolean;
        /**
         * Enable the animation of the navigation bar.
         *
         * @type { ?boolean }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        enableNavigationBarAnimation?: boolean;
    }
    /**
     * Properties of status bar, it couldn't update automatically
     *
     * @interface SystemBarStyle
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface SystemBarStyle {
        /**
         * The content color of the status bar
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        statusBarContentColor?: string;
    }
    /**
     * System bar tint of region
     *
     * @interface SystemBarRegionTint
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export interface SystemBarRegionTint {
        /**
         * System bar type
         *
         * @type { WindowType }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        type: WindowType;
        /**
         * The visibility of system bar
         *
         * @type { ?boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        isEnable?: boolean;
        /**
         * The region of system bar
         *
         * @type { ?Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        region?: Rect;
        /**
         * The background color of the system bar.
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        backgroundColor?: string;
        /**
         * The content color of the system bar.
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        contentColor?: string;
    }
    /**
     * System bar tint state for systemui
     *
     * @interface SystemBarTintState
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export interface SystemBarTintState {
        /**
         * Id of display
         *
         * @type { long }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        displayId: long;
        /**
         * Region tint of systembar
         *
         * @type { Array<SystemBarRegionTint> }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        regionTint: Array<SystemBarRegionTint>;
    }
    
    
    /**
     * Rectangle
     *
     * @interface Rect
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface Rect {
        
        
        /**
         * The left of the Rect.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        left: int;
        
        
        /**
         * The top of the Rect.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        top: int;
        
        
        /**
         * The width of the Rect.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        width: int;
        
        
        /**
         * The height of the Rect.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        height: int;
    }
    
    
    /**
     * Avoid area
     *
     * @interface AvoidArea
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface AvoidArea {
        
        /**
         * Whether avoidArea is visible on screen
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        visible: boolean;
        
        
        /**
         * Rectangle on the left of the screen
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        leftRect: Rect;
        
        
        /**
         * Rectangle on the top of the screen
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        topRect: Rect;
        
        
        /**
         * Rectangle on the right of the screen
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        rightRect: Rect;
        
        
        /**
         * Rectangle on the bottom of the screen
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        bottomRect: Rect;
    }
    
    
    /**
     * Window size
     *
     * @interface Size
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface Size {
        
        
        /**
         * The width of the window.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        width: int;
        
        
        /**
         * The height of the window.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        height: int;
    }
    /**
     * The info of window density
     *
     * @interface WindowDensityInfo
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface WindowDensityInfo {
        /**
         * System density
         *
         * @type { double }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        systemDensity: double;
        /**
         * Default density
         *
         * @type { double }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        defaultDensity: double;
        /**
         * Custom density
         *
         * @type { double }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        customDensity: double;
    }
    
    
    /**
     * Properties of window, it couldn't update automatically
     *
     * @interface WindowProperties
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface WindowProperties {
        
        
        /**
         * The position and size of the window
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        windowRect: Rect;
        
        /**
         * The position relative to the window and size of drawable area
         *
         * @type { Rect }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        drawableRect: Rect;
        
        /**
         * Window type
         *
         * @type { WindowType }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        type: WindowType;
        
        /**
         * Whether the window is displayed in full screen mode. The default value is false.
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isFullScreen: boolean;
        
        /**
         * Whether the window layout is in full screen mode(whether the window is immersive). The default value is false.
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isLayoutFullScreen: boolean;
        
        /**
         * Whether the window can gain focus. The default value is true
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        focusable: boolean;
        
        /**
         * Whether the window is touchable. The default value is false
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        touchable: boolean;
        
        
        /**
         * Brightness value of window.
         *
         * @type { double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        brightness: double;
        
        
        /**
         * Whether keep screen on.
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isKeepScreenOn: boolean;
        
        /**
         * Whether make window in privacy mode or not.
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isPrivacyMode: boolean;
        
        /**
         * Whether is transparent or not.
         *
         * @type { boolean }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isTransparent: boolean;
        
        /**
         * Window id.
         *
         * @type { int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        id: int;
        /**
         * display id.
         *
         * @type { ?long }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        displayId?: long;
        /**
         * window name.
         *
         * @type { ?string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        name?: string;
    }
    /**
     * The decor button style of the window.
     *
     * @interface DecorButtonStyle
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    interface DecorButtonStyle {
        /**
         * color mode.
         *
         * @type { ?colorMode }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        colorMode?: ConfigurationConstant.ColorMode;
        /**
         * button background size when hover.
         *
         * @type { ?number }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        buttonBackgroundSize?: number;
        /**
         * button spacing.
         *
         * @type { ?number }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        spacingBetweenButtons?: number;
        /**
         * close button right Margin.
         *
         * @type { ?number }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        closeButtonRightMargin?: number;
    }
    
    
    /**
     * Type of allowing the specified of color space.
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export enum ColorSpace {
        
        
        /**
         * Default color space.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        DEFAULT = 0,
        
        
        /**
         * Wide gamut color space. The specific wide color gamut depends on thr screen.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        WIDE_GAMUT = 1
    }
    /**
     * Describes the scale Transition Options of window
     *
     * @interface ScaleOptions
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi
     * @since 20
     */
    export interface ScaleOptions {
        /**
         * The scale param of x direction. Default is 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        x?: double;
        /**
         * The scale param of y direction. Default is 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        y?: double;
        /**
         * The scale param of pivot point of x. Default is 0.5f, Interval is 0.f - 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        pivotX?: double;
        /**
         * The scale param of pivot point of y. Default is 0.5f, Interval is 0.f - 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        pivotY?: double;
    }
    /**
     * Describes the rotate Transition Options of window
     *
     * @interface RotateOptions
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi
     * @since 20
     */
    export interface RotateOptions {
        /**
         * The rotate degree of x direction. Default value is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        x?: double;
        /**
         * The rotate degree of y direction. Default value is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        y?: double;
        /**
         * The rotate degree of z direction. Default value is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        z?: double;
        /**
         * The param of pivot point of x. Default is 0.5f, Interval is 0.f - 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        pivotX?: double;
        /**
         * The param of pivot point of y. Default is 0.5f, Interval is 0.f - 1.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        pivotY?: double;
    }
    /**
     * Describes the translate Transition Options of window
     *
     * @interface TranslateOptions
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi
     * @since 20
     */
    export interface TranslateOptions {
        /**
         * The translate pixel param of x direction. Default is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        x?: double;
        /**
         * The translate pixel param of y direction. Default is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        y?: double;
        /**
         * The translate pixel param of z direction. Default is 0.f
         *
         * @type { ?double }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        z?: double;
    }
    /**
     * Transition Context
     *
     * @interface TransitionContext
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi
     * @since 20
     */
    export interface TransitionContext {
        /**
         * The target window with animation
         *
         * @type { Window }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        toWindow: Window;
        
        /**
         * Set complete state of animation transition
         *
         * @param { boolean } isCompleted - Whether the transition is complete. The value true means that the transition is complete, and false means the opposite.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        completeTransition(isCompleted: boolean): void;
    }
    /**
     * Transition Controller
     *
     * @interface TransitionController
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi
     * @since 20
     */
    export interface TransitionController {
        
        /**
         * Animation configuration when showing window
         *
         * @param { TransitionContext } context - The transition context.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        animationForShown(context: TransitionContext): void;
        
        /**
         * Animation configuration when hiding window
         *
         * @param { TransitionContext } context - The transition context.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        animationForHidden(context: TransitionContext): void;
    }
    
    /**
     * Configuration parameters for window creation.
     *
     * @interface Configuration
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    interface Configuration {
        
        /**
         * Indicates window id.
         *
         * @type { string }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        name: string;
        
        /**
         * Indicates window type
         *
         * @type { WindowType }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        windowType: WindowType;
        
        /**
         * Indicates window context.
         *
         * @type { ?BaseContext }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        ctx?: BaseContext;
        
        /**
         * Indicates display ID.
         *
         * @type { ?long }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        displayId?: long;
        
        /**
         * Indicates Parent window id
         *
         * @type { ?int }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        parentId?: int;
        /**
         * Indicates whether enable window decor, only support dialog, The default value is false.
         *
         * @type { ?boolean }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        decorEnabled?: boolean;
        /**
         * Indicates dialog window title when decor enabled.
         *
         * @type { ?string }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        title?: string;
    }
    
    /**
     * Limits of window.
     *
     * @interface WindowLimits
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface WindowLimits {
        
        /**
         * The maximum width of the window.
         *
         * @type { ?int }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        maxWidth?: int;
        
        /**
         * The maximum height of the window.
         *
         * @type { ?int }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        maxHeight?: int;
        
        /**
         * The minimum width of the window.
         *
         * @type { ?int }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        minWidth?: int;
        
        /**
         * The minimum height of the window.
         *
         * @type { ?int }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        minHeight?: int;
    }
    
    /**
     * Rectangular area of the title buttons relative to the upper right corner of the window.
     *
     * @interface TitleButtonRect
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface TitleButtonRect {
        
        /**
         * The width of the Rect.
         *
         * @type { number }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        width: number;
    }
    /**
     * Rect change options
     *
     * @interface RectChangeOptions
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface RectChangeOptions {
        /**
         * Rect
         *
         * @type { Rect }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        rect: Rect;
        /**
         * Rect change reason
         *
         * @type { RectChangeReason }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        reason: RectChangeReason;
    }
    
    /**
     * Avoid area options
     *
     * @interface AvoidAreaOptions
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface AvoidAreaOptions {
        
        /**
         * Avoid area type
         *
         * @type { AvoidAreaType }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        type: AvoidAreaType;
        
        /**
         * Avoid area
         *
         * @type { AvoidArea }
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        area: AvoidArea;
    }
    /**
     * Window rect change reason.
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export enum RectChangeReason {
        /**
         * Default RectChangeReason.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        UNDEFINED = 0,
        /**
         * Window maximize.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        MAXIMIZE = 1,
        /**
         * Window recover.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        RECOVER = 2,
        /**
         * Window move.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        MOVE = 3,
        /**
         * Window drag.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        DRAG = 4,
        /**
         * Window drag start.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        DRAG_START = 5,
        /**
         * Window drag end.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        DRAG_END = 6
    }
    
    
    /**
     * Create a window with a specific configuration
     * When config.windowType == TYPE_FLOAT, the "ohos.permission.SYSTEM_FLOAT_WINDOW" permission is required
     *
     * @permission ohos.permission.SYSTEM_FLOAT_WINDOW
     * @param { Configuration } config - Parameters for window creation.
     * @param { AsyncCallback<Window> } callback - Callback used to return the window created.
     * @throws { BusinessError } 201 - Permission verification failed. The application does not have the permission required to call the API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 801 - Capability not supported.createWindow can not work correctly due to limited device capabilities.
     * @throws { BusinessError } 1300001 - Repeated operation.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @throws { BusinessError } 1300004 - Unauthorized operation.
     * @throws { BusinessError } 1300006 - This window context is abnormal.
     * @throws { BusinessError } 1300009 - The parent window is invalid.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    function createWindow(config: Configuration, callback: AsyncCallback<Window>): void;
    
    
    /**
     * Create a window with a specific configuration
     * When config.windowType == TYPE_FLOAT, the "ohos.permission.SYSTEM_FLOAT_WINDOW" permission is required
     *
     * @permission ohos.permission.SYSTEM_FLOAT_WINDOW
     * @param { Configuration } config - Parameters for window creation.
     * @returns { Promise<Window> } Promise used to return the window created.
     * @throws { BusinessError } 201 - Permission verification failed. The application does not have the permission required to call the API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 801 - Capability not supported.createWindow can not work correctly due to limited device capabilities.
     * @throws { BusinessError } 1300001 - Repeated operation.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @throws { BusinessError } 1300004 - Unauthorized operation.
     * @throws { BusinessError } 1300006 - This window context is abnormal.
     * @throws { BusinessError } 1300009 - The parent window is invalid.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    function createWindow(config: Configuration): Promise<Window>;
    
    
    /**
     * Finds a window based on the name.
     *
     * @param { string } name - Window name, that is, the value of name in Configuration.
     * @returns { Window } Window found.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export function findWindow(name: string): Window;
    
    
    /**
     * Obtains the top window of the current application. This API uses an asynchronous callback to return the result.
     * If no child window is available, the main window of the application is returned.
     *
     * @param { BaseContext } ctx - Current application context.
     * @param { AsyncCallback<Window> } callback - Callback used to return the top window obtained.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 1300002 - This window state is abnormal. Top window or main window is null or destroyed.
     * @throws { BusinessError } 1300006 - This window context is abnormal.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export function getLastWindow(ctx: BaseContext, callback: AsyncCallback<Window>): void;
    
    
    /**
     * Obtains the top window of the current application. This API uses a promise to return the result.
     * If no child window is available, the main window of the application is returned.
     *
     * @param { BaseContext } ctx - Current application context.
     * @returns { Promise<Window> } Promise used to return the top window obtained.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 1300002 - This window state is abnormal. Top window or main window is null or destroyed.
     * @throws { BusinessError } 1300006 - This window context is abnormal.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export function getLastWindow(ctx: BaseContext): Promise<Window>;
    
    /**
     * Minimize all app windows.
     *
     * @param { long } id - ID of the display.
     * @param { AsyncCallback<void> } callback - Callback used to return the result.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types;
     *                                                                  3. Parameter verification failed.
     * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    function minimizeAll(id: long, callback: AsyncCallback<void>): void;
    
    /**
     * Minimize all app windows.
     *
     * @param { long } id - ID of the display.
     * @returns { Promise<void> } Promise that returns no value.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types;
     *                                                                  3. Parameter verification failed.
     * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    function minimizeAll(id: long): Promise<void>;
    
    /**
     * Shifts the window focus from the source window to the target window in the same application.
     * The window focus can be shifted between the main window and a child window.
     *
     * @param { int } sourceWindowId - Window id which the focus shift from.
     * @param { int } targetWindowId - Window id which the focus shift to.
     * @returns { Promise<void> } - Promise that returns no value.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @throws { BusinessError } 1300004 - Unauthorized operation.
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    function shiftAppWindowFocus(sourceWindowId: int, targetWindowId: int): Promise<void>;
    /**
     * Register the callback of systemBarTintChange
     *
     * @param { 'systemBarTintChange' } type - The value is fixed at 'systemBarTintChange', indicating the property change event of the system bar.
     * @param { Callback<SystemBarTintState> } callback - Callback used to return the properties of the system bar.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types;
     *                                                                  3. Parameter verification failed.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function on(type: 'systemBarTintChange', callback: Callback<SystemBarTintState>): void;
    /**
     * Unregister the callback of systemBarTintChange
     *
     * @param { 'systemBarTintChange' } type - The value is fixed at 'systemBarTintChange', indicating the property change event of the system bar.
     * @param { Callback<SystemBarTintState> } callback - Callback used to return the properties of the system bar.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
     *                                                                  2. Parameter verification failed.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function off(type: 'systemBarTintChange', callback?: Callback<SystemBarTintState>): void;
    /**
     * Register the callback for gesture navigation enabled changes.
     *
     * @param { 'gestureNavigationEnabledChange' } type the event of gesture navigation enabled changes.
     * @param { Callback<boolean> } callback Callback used to return the result whether gesture navigation enabled or not.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
     *                                                                  2. Incorrect parameter types.
     *                                                                  3. Parameter verification failed.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function on(type: 'gestureNavigationEnabledChange', callback: Callback<boolean>): void;
    /**
     * Unregister the callback for gesture navigation enabled changes.
     *
     * @param { 'gestureNavigationEnabledChange' } type the event of gesture navigation enabled changes.
     * @param { Callback<boolean> } callback Callback used to return the result whether gesture navigation enabled or not.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
     *                                                                  2. Parameter verification failed.
     * @throws { BusinessError } 1300002 - This window state is abnormal.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function off(type: 'gestureNavigationEnabledChange', callback?: Callback<boolean>): void;
    /**
     * Register the callback for watermark flag change.
     *
     * @param { 'waterMarkFlagChange' } type the event of watermark flag change.
     * @param { Callback<boolean> } callback Callback used to return the result whether watermark flag change or not.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible causes: 1. Mandatory parameters are left unspecified.
     * <br>2. Incorrect parameter types. 3.Parameter verification failed.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function on(type: 'waterMarkFlagChange', callback: Callback<boolean>): void;
    /**
     * Unregister the callback for watermark flag change.
     *
     * @param { 'waterMarkFlagChange' } type the event of watermark flag change.
     * @param { Callback<boolean> } callback Callback used to return the result whether watermark flag change or not.
     * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
     * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
     * <br>2. Parameter verification failed.
     * @throws { BusinessError } 1300003 - This window manager service works abnormally.
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export function off(type: 'waterMarkFlagChange', callback?: Callback<boolean>): void;
    
    
    /**
     * Display orientation
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export enum Orientation {
        
        
        /**
         * Default value. The direction mode is not clearly defined. It is determined by the system.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        UNSPECIFIED = 0,
        
        
        /**
         * Display in portrait orientation.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        PORTRAIT = 1,
        
        
        /**
         * Display in landscape orientation.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        LANDSCAPE = 2,
        
        
        /**
         * Display in inverted portrait orientation.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        PORTRAIT_INVERTED = 3,
        
        
        /**
         * Display in inverted landscape orientation.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        LANDSCAPE_INVERTED = 4,
        
        /**
         * Follow the rotation of the sensor, ignore auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION = 5,
        
        /**
         * Follow the rotation of the sensor, only work in the vertical direction, ignore auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION_PORTRAIT = 6,
        
        /**
         * Follow the rotation of the sensor, only work in the horizontal direction, ignore auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION_LANDSCAPE = 7,
        
        /**
         * Follow the rotation of the sensor, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION_RESTRICTED = 8,
        
        /**
         * Follow the rotation of the sensor, only work in the vertical direction, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION_PORTRAIT_RESTRICTED = 9,
        
        /**
         * Follow the rotation of the sensor, only work in the horizontal direction, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        AUTO_ROTATION_LANDSCAPE_RESTRICTED = 10,
        
        /**
         * Locked mode, keep the same direction as previous one.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        LOCKED = 11,
        /**
         * Follow the rotation of the sensor, determined by the system, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        AUTO_ROTATION_UNSPECIFIED = 12,
        /**
         * Display in portrait orientation, and then, follow the rotation of the sensor, determined by the system, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        USER_ROTATION_PORTRAIT = 13,
        /**
         * Display in landscape orientation, and then, follow the rotation of the sensor, determined by the system, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        USER_ROTATION_LANDSCAPE = 14,
        /**
         * Display in inverted portrait orientation, and then, follow the rotation of the sensor, determined by the system, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        USER_ROTATION_PORTRAIT_INVERTED = 15,
        /**
         * Display in inverted landscape orientation, and then, follow the rotation of the sensor, determined by the system, controlled by auto rotation lock.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        USER_ROTATION_LANDSCAPE_INVERTED = 16,
        /**
         * Follow the desktop rotate mode.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        FOLLOW_DESKTOP = 17
    }
    /**
     * Type of blur style
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @systemapi Hide this for inner system use.
     * @since 20
     */
    export enum BlurStyle {
        /**
         * Close blur.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        OFF = 0,
        /**
         * Blur style thin.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        THIN = 1,
        /**
         * Blur style regular.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        REGULAR = 2,
        /**
         * Blur style thick.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        THICK = 3
    }
    
    /**
     * Enum for window callback event type
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export enum WindowEventType {
        
        /**
         * The value of window event is window show
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        WINDOW_SHOWN = 1,
        
        /**
         * The value of window event is window active
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        WINDOW_ACTIVE = 2,
        
        /**
         * The value of window event is window inactive
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        WINDOW_INACTIVE = 3,
        
        /**
         * The value of window event is window hide
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        WINDOW_HIDDEN = 4,
        /**
         * The value of window event is window destroy
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        WINDOW_DESTROYED = 7
    }
    /**
     * Enum for window maximize presentation
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export enum MaximizePresentation {
        /**
         * The value means follow immersive state which set by app
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        FOLLOW_APP_IMMERSIVE_SETTING = 0,
        /**
         * The value means exit immersive state
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        EXIT_IMMERSIVE = 1,
        /**
         * The value means enter immersive state
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        ENTER_IMMERSIVE = 2
    }
    /**
     * the optional move configuration used in moveWindowToAsync/moveWindowToGlobal
     *
     * @interface MoveConfiguration
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface MoveConfiguration {
        /**
         * The display id of the screen
         *
         * @type { ?long }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        displayId?: long;
    }
    
    /**
     * Specific system bar type.
     *
     * @typedef {'status' | 'navigation' | 'navigationIndicator'}
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    type SpecificSystemBar = 'status' | 'navigation' | 'navigationIndicator';
    /**
     * The information of keyboard
     *
     * @interface KeyboardInfo
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    interface KeyboardInfo {
        /**
         * The position and size of keyboard before animation.
         *
         * @type { Rect }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        beginRect: Rect;
        /**
         * The position and size of keyboard after animation completed.
         *
         * @type { Rect }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        endRect: Rect;
    }
    
    /**
     * Window
     *
     * @interface Window
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface Window {
        
        /**
         * Hide window with animation.
         *
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        hideWithAnimation(callback: AsyncCallback<void>): void;
        
        /**
         * Hide window with animation.
         *
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        hideWithAnimation(): Promise<void>;
        
        
        /**
         * Shows this window. This API uses an asynchronous callback to return the result.
         * This API takes effect only for a system window or an application child window.
         * For the main window of an application, this API moves it at the top when the main window is already displayed.
         *
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        showWindow(callback: AsyncCallback<void>): void;
        
        
        /**
         * Shows this window. This API uses a promise to return the result.
         * This API takes effect only for a system window or an application child window.
         * For the main window of an application, this API moves it at the top when the main window is already displayed.
         *
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        showWindow(): Promise<void>;
        
        /**
         * Show window with animation.
         *
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        showWithAnimation(callback: AsyncCallback<void>): void;
        
        /**
         * Show window with animation.
         *
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        showWithAnimation(): Promise<void>;
        
        
        /**
         * Destroys this window. This API uses an asynchronous callback to return the result.
         * This API takes effect only for a system window or an application child window.
         *
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        destroyWindow(callback: AsyncCallback<void>): void;
        
        
        /**
         * Destroys this window. This API uses an asynchronous callback to return the result.
         * This API takes effect only for a system window or an application child window.
         *
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        destroyWindow(): Promise<void>;
        
        
        /**
         * Set the position of a window.
         *
         * @param { int } x - Indicate the X-coordinate of the window.
         * @param { int } y - Indicate the Y-coordinate of the window.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        moveWindowTo(x: int, y: int): Promise<void>;
        
        
        /**
         * Set the position of a window.
         *
         * @param { int } x - Indicate the X-coordinate of the window.
         * @param { int } y - Indicate the Y-coordinate of the window.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        moveWindowTo(x: int, y: int, callback: AsyncCallback<void>): void;
        
        
        /**
         * Set the size of a window .
         *
         * @param { int } width - Indicates the width of the window. The width should be greater than 0.
         * @param { int } height - Indicates the height of the window. The height should be greater than 0.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        resize(width: int, height: int): Promise<void>;
        
        
        /**
         * Set the size of a window .
         *
         * @param { int } width - Indicates the width of the window. The width should be greater than 0.
         * @param { int } height - Indicates the height of the window. The height should be greater than 0.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        resize(width: int, height: int, callback: AsyncCallback<void>): void;
        /**
         * Get the window rectangular area quadruple {left,top,weight,height}, left and top represent relative to screen coordinates
         * and are affected by parent window scaling, weight and height are the scaling width and height.
         *
         * @returns { Rect } The quadruple {left,top,weight,height} represents respectively the X-coordinate
         * and Y-coordinate of the window relative to current screen, the scaled window width and scaled window height.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        getGlobalRect(): Rect;
        
        
        /**
         * Get the properties of current window
         *
         * @returns { WindowProperties } Return the window properties.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        getWindowProperties(): WindowProperties;
        
        
        /**
         * Get the avoid area
         *
         * @param { AvoidAreaType } type - Type of the area
         * @returns { AvoidArea } Area where the window cannot be displayed.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        getWindowAvoidArea(type: AvoidAreaType): AvoidArea;
        
        /**
         * Sets whether the main window layout or the child window layout is immersive.
         *
         * @param { boolean } isLayoutFullScreen - Whether the window layout is immersive
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowLayoutFullScreen(isLayoutFullScreen: boolean): Promise<void>;
        
        
        /**
         * Sets whether to show the system bar of the main window.
         *
         * @param { Array<'status' | 'navigation'> } names - The set of system bar types
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1.Mandatory parameters are left unspecified;
         *                                                                  2.Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowSystemBarEnable(names: Array<'status' | 'navigation'>): Promise<void>;
        
        /**
         * Sets whether to show the specific system bar of the main window.
         *
         * @param {SpecificSystemBar} name - Type of the system bar to be shown or hidden
         * @param {boolean} enable - Show specific system bar if true, or hide specific system bar if false.
         * @param {boolean} enableAnimation - Whether using animation during this setting, using animation if true or not using animation if false.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws {BusinessError} 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                2. Incorrect parameter types.
         * @throws {BusinessError} 1300002 - This window state is abnormal.
         * @throws {BusinessError} 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        setSpecificSystemBarEnabled(name: SpecificSystemBar, enable: boolean, enableAnimation?: boolean): Promise<void>;
        
        
        /**
         * Set the properties of system bar
         *
         * @param { SystemBarProperties } systemBarProperties - The properties of system bar
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowSystemBarProperties(systemBarProperties: SystemBarProperties): Promise<void>;
        
        
        /**
         * Sets the preferred orientation for the main window.
         * This API uses a promise to return the result.
         * It does not take effect on devices that do not support rotation with the sensor, on 2-in-1 devices or for the child window.
         *
         * @param { Orientation } orientation - The orientation config of the window
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setPreferredOrientation(orientation: Orientation): Promise<void>;
        
        
        /**
         * Sets the preferred orientation for the main window.
         * This API uses an asynchronous callback to return the result.
         * It does not take effect on devices that do not support rotation with the sensor, on 2-in-1 devices or for the child window.
         *
         * @param { Orientation } orientation - The orientation config of the window
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setPreferredOrientation(orientation: Orientation, callback: AsyncCallback<void>): void;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to this window, and transfers the state attribute to the page through a local storage.
         * This API uses a promise to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content. Exercise caution when using it.
         *
         * @param { string } path - Path of the page from which the content will be loaded. The path is configured in the main_pages.json file of the project.
         * @param { LocalStorage } storage - Page-level UI state storage unit, which is used to transfer the state attribute for the page.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        loadContent(path: string, storage: LocalStorage, callback: AsyncCallback<void>): void;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to this window, and transfers the state attribute to the page through a local storage.
         * This API uses a promise to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content. Exercise caution when using it.
         *
         * @param { string } path - 	Path of the page from which the content will be loaded. The path is configured in the main_pages.json file of the project.
         * @param { LocalStorage } storage - Page-level UI state storage unit, which is used to transfer the state attribute for the page.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        loadContent(path: string, storage: LocalStorage): Promise<void>;
        
        /**
         * Obtain a UIContext instance.
         *
         * @returns { UIContext } UIContext instance obtained.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @stagemodelonly
         * @since 20
         */
        getUIContext(): UIContext;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to this window.
         * This API uses an asynchronous callback to return the result.
         *
         * @param { string } path - Path of the page from which the content will be loaded.
         *                          In the stage model, the path is configured in the main_pages.json file of the project.
         *                          In the FA model, the path is configured in the config.json file of the project.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setUIContent(path: string, callback: AsyncCallback<void>): void;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to this window.
         * This API uses a promise to return the result.
         *
         * @param { string } path - Path of the page from which the content will be loaded.
         *                          In the stage model, the path is configured in the main_pages.json file of the project.
         *                          In the FA model, the path is configured in the config.json file of the project.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setUIContent(path: string): Promise<void>;
        
        
        /**
         * Checks whether the window is displayed
         *
         * @returns { boolean } Whether the window is displayed. The value true means that the window is displayed, and false means the opposite.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isWindowShowing(): boolean;
        
        
        /**
         * Register the callback of windowSizeChange
         *
         * @param { 'windowSizeChange' } type - The value is fixed at 'windowSizeChange', indicating the window size change event.
         * @param { Callback<Size> } callback - Callback used to return the window size.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'windowSizeChange', callback: Callback<Size>): void;
        
        
        /**
         * Unregister the callback of windowSizeChange
         *
         * @param { 'windowSizeChange' } type - The value is fixed at 'windowSizeChange', indicating the window size change event.
         * @param { Callback<Size> } callback - Callback used to return the window size.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'windowSizeChange', callback?: Callback<Size>): void;
        
        
        
        /**
         * Register the callback of avoidAreaChange
         *
         * @param { 'avoidAreaChange' } type - The value is fixed at 'avoidAreaChange', indicating the event of changes to the avoid area.
         * @param { Callback<AvoidAreaOptions> } callback - Callback used to return the area.
         * @throws { BusinessError } 401 - Parameter error. Possible causes: 1. Mandatory parameters are left unspecified;
         *                                                                   2. Incorrect parameter types;
         *                                                                   3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'avoidAreaChange', callback: Callback<AvoidAreaOptions>): void;
        
        
        
        /**
         * Unregister the callback of avoidAreaChange
         *
         * @param { 'avoidAreaChange' } type - The value is fixed at 'avoidAreaChange', indicating the event of changes to the avoid area.
         * @param { Callback<AvoidAreaOptions> } callback - Callback used to return the area.
         * @throws { BusinessError } 401 - Parameter error. Possible causes: 1. Incorrect parameter types;
         *                                                                   2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'avoidAreaChange', callback?: Callback<AvoidAreaOptions>): void;
        
        /**
         * Register the callback of keyboardHeightChange
         *
         * @param { 'keyboardHeightChange' } type - The value is fixed at 'keyboardHeightChange', indicating the keyboard height change event.
         * @param { Callback<int> } callback - Callback used to return the current keyboard height, which is an integer, in px.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'keyboardHeightChange', callback: Callback<int>): void;
        
        /**
         * Unregister the callback of keyboardHeightChange
         *
         * @param { 'keyboardHeightChange' } type - The value is fixed at 'keyboardHeightChange', indicating the keyboard height change event.
         * @param { Callback<int> } callback - Callback used to return the current keyboard height, which is an integer, in px.
         * If a value is passed in, the corresponding subscription is canceled.
         * If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'keyboardHeightChange', callback?: Callback<int>): void;
        /**
         * Register the callback of keyboardDidShow
         *
         * @param { 'keyboardDidShow' } type - The value is fixed at 'keyboardDidShow', indicating the completion of the keyboard show animation event.
         * @param { Callback<KeyboardInfo> } callback - Callback invoked when the keyboard show animation is completed.
         * @throws { BusinessError } 801 - Capability not supported. Function keyboardDidShow can not work correctly due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'keyboardDidShow', callback: Callback<KeyboardInfo>): void;
        /**
         * Unregister the callback of keyboardDidShow
         *
         * @param { 'keyboardDidShow' } type - The value is fixed at 'keyboardDidShow', indicating the completion of the keyboard show animation event.
         * @param { Callback<KeyboardInfo> } callback - Callback invoked when the keyboard show animation is completed.
         * @throws { BusinessError } 801 - Capability not supported. Function keyboardDidShow can not work correctly due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'keyboardDidShow', callback?: Callback<KeyboardInfo>): void;
        /**
         * Register the callback of keyboardDidHide
         *
         * @param { 'keyboardDidHide' } type - The value is fixed at 'keyboardDidHide', indicating the completion of the keyboard hide animation event.
         * @param { Callback<KeyboardInfo> } callback - Callback invoked when the keyboard hide animation is completed.
         * @throws { BusinessError } 801 - Capability not supported. Function keyboardDidHide can not work correctly due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'keyboardDidHide', callback: Callback<KeyboardInfo>): void;
        /**
         * Unregister the callback of keyboardDidHide
         *
         * @param { 'keyboardDidHide' } type - The value is fixed at 'keyboardDidHide', indicating the completion of the keyboard hide animation event.
         * @param { Callback<KeyboardInfo> } callback - Callback invoked when the keyboard hide animation is completed.
         * @throws { BusinessError } 801 - Capability not supported. Function keyboardDidHide can not work correctly due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'keyboardDidHide', callback?: Callback<KeyboardInfo>): void;
        /**
         * Subscribes to the touch event outside this window.
         *
         * @param { 'touchOutside' } type - The value is fixed at 'touchOutside', indicating the click event outside this window.
         * @param { Callback<void> } callback - Callback used to return the click event outside this window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'touchOutside', callback: Callback<void>): void;
        /**
         * Unsubscribes from the touch event outside this window.
         *
         * @param { 'touchOutside' } type - The value is fixed at 'touchOutside', indicating the click event outside this window.
         * @param { Callback<void> } callback - Callback used to return the click event outside this window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'touchOutside', callback?: Callback<void>): void;
        /**
         * Window displayId change callback on.
         *
         * @param { 'displayIdChange' } type - The value is fixed at 'displayIdChange', indicating the Display this window is current showing has changed.
         * @param { Callback<long> } callback - Callback used to notify the Display this window is current showing has changed.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'displayIdChange', callback: Callback<long>): void;
        /**
         * Window displayId change callback off.
         *
         * @param { 'displayIdChange' } type - The value is fixed at 'displayIdChange', indicating the Display this window is current showing has changed.
         * @param { Callback<long> } callback - Callback used to notify the Display this window is current showing has changed.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'displayIdChange', callback?: Callback<long>): void;
        
        /**
         * Subscribes to the visibility status change event of this window.
         *
         * @param { 'windowVisibilityChange' } type - Event type. The value is fixed at 'windowVisibilityChange', indicating the visibility status change event.
         * @param { Callback<boolean> } callback - Callback used to return the visibility status of the window, which is a Boolean value.
         *                                         The value true means that the window is visible, and false means the opposite.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowVisibilityChange', callback: Callback<boolean>): void;
        
        /**
         * Unsubscribes from the visibility status change event of this window.
         *
         * @param { 'windowVisibilityChange' } type - Event type. The value is fixed at 'windowVisibilityChange', indicating the visibility status change event.
         * @param { Callback<boolean> } callback - Callback used to return the visibility status of the window.
         *                                         If a value is passed in, the corresponding subscription is canceled.
         *                                         If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowVisibilityChange', callback?: Callback<boolean>): void;
        /**
         * System density change callback on.
         *
         * @param { 'systemDensityChange' } type - The value is fixed at 'systemDensityChange', indicating the system density is current has changed.
         * @param { Callback<double> } callback - Callback used to notify the system density is current has changed.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'systemDensityChange', callback: Callback<double>): void;
        /**
         * System density change callback off.
         *
         * @param { 'systemDensityChange' } type - The value is fixed at 'systemDensityChange', indicating the system density is current showing has changed.
         * @param { Callback<double> } callback - Callback used to notify the system density is current has changed.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'systemDensityChange', callback?: Callback<double>): void;
        /**
         * Subscribes to non-interaction events in a window within the specified period.
         * Interaction events include physical keyboard input events and screen touch/click events, but not soft keyboard input events.
         *
         * @param { 'noInteractionDetected' } type - The value is fixed at 'noInteractionDetected', indicating the window has no interaction for a long time.
         * @param { long } timeout - The timeout(in seconds) of no interaction detection.
         * @param { Callback<void> } callback - Callback used to notify the window has no interaction for a long time.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'noInteractionDetected', timeout: long, callback: Callback<void>): void;
        /**
         * Unsubscribes from non-interaction events in a window within the specified period.
         * Interaction events include physical keyboard input events and screen touch/click events, but not soft keyboard input events.
         *
         * @param { 'noInteractionDetected' } type - The value is fixed at 'noInteractionDetected', indicating the window has no interaction for a long time.
         * @param { Callback<void> } callback - Callback used to notify the window has no interaction for a long time.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'noInteractionDetected', callback?: Callback<void>): void;
        
        /**
         * Register the callback of screenshot, only the focused window called back
         *
         * @param { 'screenshot' } type - The value is fixed at 'screenshot', indicating the screenshot event.
         * @param { Callback<void> } callback - Callback invoked when a screenshot event occurs.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'screenshot', callback: Callback<void>): void;
        
        /**
         * Unregister the callback of screenshot
         *
         * @param { 'screenshot' } type - The value is fixed at 'screenshot', indicating the screenshot event.
         * @param { Callback<void> } callback - Callback invoked when a screenshot event occurs.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'screenshot', callback?: Callback<void>): void;
        
        /**
         * Subscribes to click or touch events in a window covered by a modal window. This API takes effect only when it is called by a modal window.
         *
         * @param { 'dialogTargetTouch' } type - The value is fixed at 'dialogTargetTouch', indicating the click event of the target window in the modal window mode.
         * @param { Callback<void> } callback - Callback invoked when the click event occurs in the target window of the modal window mode.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'dialogTargetTouch', callback: Callback<void>): void;
        
        /**
         * Unsubscribes from the touch event of the target window in the modal window mode.
         *
         * @param { 'dialogTargetTouch' } type - The value is fixed at 'dialogTargetTouch',
         *  indicating the click event of the target window in the modal window mode.
         * @param { Callback<void> } callback - Callback invoked when the click event occurs in the target window of the modal window mode.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'dialogTargetTouch', callback?: Callback<void>): void;
        
        /**
         * Subscribes to the window lifecycle change event.
         *
         * @param { 'windowEvent' } type - Event type. The value is fixed at 'windowEvent', indicating the window lifecycle change event.
         * @param { Callback<WindowEventType> } callback - Callback used to return the window lifecycle state.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        on(type: 'windowEvent', callback: Callback<WindowEventType>): void;
        
        /**
         * Unsubscribes from the window lifecycle change event.
         *
         * @param { 'windowEvent' } type - Event type. The value is fixed at 'windowEvent', indicating the window lifecycle change event.
         * @param { Callback<WindowEventType> } callback - Callback used to return the window lifecycle state.
         *                                                 If a value is passed in, the corresponding subscription is canceled.
         *                                                 If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        off(type: 'windowEvent', callback?: Callback<WindowEventType>): void;
        
        
        /**
         * Register the callback of windowStatusChange
         *
         * @param { 'windowStatusChange' } type - The value is fixed at 'windowStatusChange', indicating the window status change event.
         * @param { Callback<WindowStatusType> } callback - Callback used to return the window status.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowStatusChange', callback: Callback<WindowStatusType>): void;
        
        
        /**
         * Unregister the callback of windowStatusChange
         *
         * @param { 'windowStatusChange' } type - The value is fixed at 'windowStatusChange', indicating the window status change event.
         * @param { Callback<WindowStatusType> } callback - Callback used to return the window status.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowStatusChange', callback?: Callback<WindowStatusType>): void;
        /**
         * Subscribes to the event indicating that the child window is closed.
         * This event is triggered only when the user clicks the system-provided close button in the upper right corner to close the child window.
         * It is not triggered when the child window is closed in other ways.
         *
         * @param { 'subWindowClose' } type - Event type. The value is fixed at 'subWindowClose', indicating the child window close event.
         * @param { Callback<void> } callback - Callback invoked when the close button in the upper right corner of the child window is clicked.
         *                                      The internal logic of the callback function requires a return value of the Boolean type.
         *                                      The return value determines whether to continue to close the child window.
         *                                      The value true means not to close the child window, and false means to continue to close the child window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'subWindowClose', callback: Callback<void>): void;
        /**
         * Unsubscribes from the event indicating that the child window is closed.
         *
         * @param { 'subWindowClose' } type - Event type. The value is fixed at 'subWindowClose', indicating the child window close event.
         * @param { Callback<void> } callback - Callback invoked when the close button in the upper right corner of the child window is clicked.
         *                                      The internal logic of the callback function requires a return value of the Boolean type.
         *                                      The return value determines whether to continue to close the child window.
         *                                      The value true means not to close the child window, and false means to continue to close the child window.
         *                                      If a value is passed in, the corresponding subscription is canceled.
         *                                      If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'subWindowClose', callback?: Callback<void>): void;
        /**
         * Subscribes to the event indicating that the main window or child window will be closed.
         * This event is triggered only when the user clicks the close button in the system-provided title bar to close the window.
         * It is not triggered when the window is closed in other ways.
         *
         * @param { 'windowWillClose' } type - Event type. The value is fixed at 'windowWillClose', indicating the window close event.
         * @param { Callback<void, Promise<boolean>> } callback - Callback used to when the close button in the upper right corner of the window is clicked.
         *                                                        The internal logic of the callback function requires a return value of the Promise type.
         *                                                        In the returned Promise function, resolve(true) means not to close the window,
         *                                                        and resolve(false) or reject means to continue to close the window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowWillClose', callback: Callback<void, Promise<boolean>>): void;
        /**
         * Unsubscribes from the event indicating that the main window or child window will be closed.
         *
         * @param { 'windowWillClose' } type - Event type. The value is fixed at 'windowWillClose', indicating the window close event.
         * @param { Callback<void, Promise<boolean>> } callback - Callback used to when the close button in the upper right corner of the window is clicked.
         *                                                        The internal logic of the callback function requires a return value of the Promise type.
         *                                                        It does not return any parameter. In the returned Promise function,
         *                                                        resolve(true) means not to close the window,
         *                                                        and resolve(false) or reject means to continue to close the window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowWillClose', callback?: Callback<void, Promise<boolean>>): void;
        /**
         * Register the callback of window highlight state change
         *
         * @param { 'windowHighlightChange' } type - The value is fixed at 'windowHighlightChange', indicating the window highlight state change event.
         * @param { Callback<boolean> } callback - Callback used to return the highlight status of the window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowHighlightChange', callback: Callback<boolean>): void;
        /**
         * Unregister the callback of window highlight state change
         *
         * @param { 'windowHighlightChange' } type - The value is fixed at 'windowHighlightChange', indicating the window highlight change event.
         * @param { Callback<boolean> } callback - Callback used to return the highlight status of the window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowHighlightChange', callback?: Callback<boolean>): void;
        
        /**
         * Whether the window supports thr wide gamut setting.
         *
         * @returns { Promise<boolean> } Promise used to return the result.
         *  The value true means that the wide-gamut color space is supported, and false means the opposite.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isWindowSupportWideGamut(): Promise<boolean>;
        
        /**
         * Whether the window supports thr wide gamut setting.
         *
         * @param { AsyncCallback<boolean> } callback Callback used to return the result.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        isWindowSupportWideGamut(callback: AsyncCallback<boolean>): void;
        
        
        /**
         * Sets the specified color space.
         *
         * @param { ColorSpace } colorSpace the specified color space.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowColorSpace(colorSpace: ColorSpace): Promise<void>;
        
        
        /**
         * Sets the specified color space.
         *
         * @param { ColorSpace } colorSpace the specified color space.
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowColorSpace(colorSpace: ColorSpace, callback: AsyncCallback<void>): void;
        
        
        
        /**
         * Sets the background color of window.
         *
         * @param { string | ColorMetrics } color - the specified color.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowBackgroundColor(color: string | ColorMetrics): void;
        
        /**
         * Sets whether focusable or not.
         *
         * @param { boolean } isFocusable can be focus if true, or can not be focus if false.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowFocusable(isFocusable: boolean): Promise<void>;
        
        /**
         * Sets whether focusable or not.
         *
         * @param { boolean } isFocusable can be focus if true, or can not be focus if false.
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowFocusable(isFocusable: boolean, callback: AsyncCallback<void>): void;
        
        
        /**
         * Sets whether keep screen on or not.
         *
         * @param { boolean } isKeepScreenOn keep screen on if true, or not if false.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowKeepScreenOn(isKeepScreenOn: boolean): Promise<void>;
        
        
        /**
         * Sets whether keep screen on or not.
         *
         * @param { boolean } isKeepScreenOn keep screen on if true, or not if false.
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowKeepScreenOn(isKeepScreenOn: boolean, callback: AsyncCallback<void>): void;
        
        
        /**
         * Sets whether is private mode or not.
         *
         * @permission ohos.permission.PRIVACY_WINDOW
         * @param { boolean } isPrivacyMode in private mode if true, or not if false.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 201 - Permission verification failed. The application does not have the permission required to call the API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowPrivacyMode(isPrivacyMode: boolean): Promise<void>;
        
        
        /**
         * Sets whether is private mode or not.
         *
         * @permission ohos.permission.PRIVACY_WINDOW
         * @param { boolean } isPrivacyMode in private mode if true, or not if false.
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 201 - Permission verification failed. The application does not have the permission required to call the API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowPrivacyMode(isPrivacyMode: boolean, callback: AsyncCallback<void>): void;
        
        /**
         * Sets whether is touchable or not.
         *
         * @param { boolean } isTouchable is touchable if true, or not if false.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowTouchable(isTouchable: boolean): Promise<void>;
        
        /**
         * Sets whether is touchable or not.
         *
         * @param { boolean } isTouchable is touchable if true, or not if false.
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setWindowTouchable(isTouchable: boolean, callback: AsyncCallback<void>): void;
        
        /**
         * Obtains snapshot of window
         *
         * @param { AsyncCallback<image.PixelMap> } callback Callback used to return the result.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        snapshot(callback: AsyncCallback<image.PixelMap>): void;
        
        /**
         * Obtains snapshot of window
         *
         * @returns { Promise<image.PixelMap> } Promise that returns no value.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        snapshot(): Promise<image.PixelMap>;
        
        /**
         * Sets the opacity for this window.
         * This API can be used only when you customize an animation to be played during the display or hiding of a system window.
         *
         * @param { double } opacity Interval is 0.f-1.f.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        opacity(opacity: double): void;
        
        /**
         * Sets the scale parameters for this window.
         * This API can be used only when you customize an animation to be played during the display or hiding of a system window.
         *
         * @param { ScaleOptions } scaleOptions scale param of window.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        scale(scaleOptions: ScaleOptions): void;
        
        /**
         * Sets the rotation parameters for this window.
         * This API can be used only when you customize an animation to be played during the display or hiding of a system window.
         *
         * @param { RotateOptions } rotateOptions rotate param of window.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        rotate(rotateOptions: RotateOptions): void;
        
        /**
         * Sets the translation parameters for this window.
         * This API can be used only when you customize an animation to be played during the display or hiding of a system window.
         *
         * @param { TranslateOptions } translateOptions translate param of window.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @since 20
         */
        translate(translateOptions: TranslateOptions): void;
        
        /**
         * Sets the shadow for the window borders.
         *
         * @param { double } radius the radius of the shadow.
         * @param { string } color the color of the shadow.
         * @param { double } offsetX the offset of the shadow on the x-axis.
         * @param { double } offsetY the offset of the shadow on the y-axis.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        setShadow(radius: double, color?: string, offsetX?: double, offsetY?: double): void;
        
        /**
         * Set the watermark flag on the window.
         *
         * @param { boolean } enable - Add water mark flag to window if true, or remove flag if false.
         * @param { AsyncCallback<void> } callback - The callback of setWaterMarkFlag.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible causes: 1. Mandatory parameters are left unspecified.
         * <br>2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300008 - The display device is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        setWaterMarkFlag(enable: boolean, callback: AsyncCallback<void>): void;
        
        /**
         * Set the watermark flag on the window
         *
         * @param { boolean } enable - Add water mark flag to window if true, or remove flag if false
         * @returns { Promise<void> } - The promise returned by the function
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible causes: 1. Mandatory parameters are left unspecified.
         * <br>2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300008 - The display device is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        setWaterMarkFlag(enable: boolean): Promise<void>;
        
        /**
         * Minimizes the main window if the caller is the main window. The main window can be restored in the dock bar. For 2-in-1 devices, it can be restored by calling restore().
         * Hides the child window if the caller is a child window. The child window cannot be restored in the dock bar. It can be made visible again by calling showWindow().
         *
         *
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        minimize(callback: AsyncCallback<void>): void;
        
        /**
         * Minimizes the main window if the caller is the main window. The main window can be restored in the dock bar. For 2-in-1 devices, it can be restored by calling restore().
         * Hides the child window if the caller is a child window. The child window cannot be restored in the dock bar. It can be made visible again by calling showWindow().
         *
         * @returns { Promise<void> } - Promise that returns no value.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        minimize(): Promise<void>;
        
        /**
         * Maximizes the main window.
         *
         * @param { ?MaximizePresentation } presentation - Layout when the window is maximized.
         *                                                 The default value is window.MaximizePresentation.ENTER_IMMERSIVE,
         *                                                 indicating that the window enters the immersive layout when maximized.
         * @returns { Promise<void> } - Promise that returns no value.
         * @throws { BusinessError } 801 - Capability not supported. Function maximize can not work correctly due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        maximize(presentation?: MaximizePresentation): Promise<void>;
        /**
         * Hide the non-system floating windows.
         *
         * @param { boolean } shouldHide - Hide the non-system floating windows if true, otherwise means the opposite.
         * @param { AsyncCallback<void> } callback - The callback of hideNonSystemFloatingWindows.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        hideNonSystemFloatingWindows(shouldHide: boolean, callback: AsyncCallback<void>): void;
        /**
         * Hide the non-system floating windows.
         *
         * @param { boolean } shouldHide - Hide the non-system floating windows if true, otherwise means the opposite.
         * @returns { Promise<void> } - The promise returned by the function.
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @since 20
         */
        hideNonSystemFloatingWindows(shouldHide: boolean): Promise<void>;
        
        /**
         * When get focused, keep the keyboard created by other windows, support system window and app subwindow.
         *
         * @param { boolean } keepKeyboardFlag - Whether to keep the soft keyboard created by others.
         * The value true means to keep the soft keyboard, and false means the opposite.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        keepKeyboardOnFocus(keepKeyboardFlag: boolean): void;
        
        /**
         * Restores the main window from the full-screen, maximized, or split-screen mode to a floating window,
         * and restores the window size and position to those before the full-screen, maximized, or split-screen mode is entered.
         *
         * @returns { Promise<void> } - Promise that returns no value.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300001 - Repeated operation.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        recover(): Promise<void>;
        
        
        /**
         * Sets whether the title bar is visible in the window.
         *
         * @param { boolean } isVisible - Whether the title bar is visible. The value true means that the title bar is visible and false means the opposite.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        setWindowDecorVisible(isVisible: boolean): void;
        
        /**
         * Sets the height of the title bar of this window.
         * This API takes effect for the window that has a title bar or a three-button area on 2-in-1 devices.
         *
         * @param { int } height - Height of the title bar. It takes effect only for the window with the title bar.
         *                            The value is an integer in the range [37,112]. The unit is vp. If a floating point number is passed in,
         *                            the value is rounded down. A value outside the range is invalid.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        setWindowDecorHeight(height: int): void;
        
        /**
         * Obtains the height of the title bar of this window.
         * This API takes effect for the window that has a title bar or a three-button area on 2-in-1 devices.
         *
         * @returns { int } - Height of the title bar. The value is an integer in the range [37,112]. The unit is vp.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        getWindowDecorHeight(): int;
        /**
         * Sets the button style of the decoration bar. The setting takes effect only for the main window and the child window with the window title enabled.
         *
         * @param { DecorButtonStyle } dectorStyle - Button style of the decoration bar.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        setDecorButtonStyle(dectorStyle: DecorButtonStyle): void;
        /**
         * Shows or hides the maximize, minimize, and close buttons on the title bar of the main window.
         *
         * @param { boolean } isMaximizeButtonVisible - Whether to show the maximize button. The value true means to show the button, and false means the opposite.
         *                                              If the maximize button is hidden, the corresponding restore button is also hidden in the maximize scenario.
         * @param { boolean } isMinimizeButtonVisible - Whether to show the minimize button. The value true means to show the button, and false means the opposite.
         * @param { boolean } isCloseButtonVisible - Whether to show the close button. The value true means to show the button, and false means the opposite.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        setWindowTitleButtonVisible(isMaximizeButtonVisible: boolean, isMinimizeButtonVisible: boolean, isCloseButtonVisible?: boolean): void;
        /**
         * Starts moving this window. This API uses a promise to return the result.
         * The window moves along with the cursor only when this API is called in the callback function of onTouch, where the event type is TouchType.Down.
         *
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300001 - Repeated operation.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        startMoving(): Promise<void>;
        /**
         * Specifies the cursor position within the window and moves the window. It first adjusts the window to the cursor position before starting to move the window.
         * The window moves along with the cursor only when this API is called in the callback function of onTouch, where the event type is TouchType.Down.
         *
         * @param { int } offsetX - X-axis offset of the cursor position relative to the upper left corner of the window during movement, measured in px.
         *                             This parameter only accepts integer values; any floating-point input will be rounded down.
         *                             Negative values or values exceeding the window width are invalid. The window width can be obtained from WindowProperties.
         * @param { int } offsetY - Y-axis offset of the cursor position relative to the upper left corner of the window during movement, measured in px.
         *                             This parameter only accepts integer values; any floating-point input will be rounded down.
         *                             Negative values or values exceeding the window height are invalid. The window height can be obtained from WindowProperties.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300001 - Repeated operation.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        startMoving(offsetX: int, offsetY: int): Promise<void>;
        
        /**
         * Subscribes to the change event of the rectangle that holds the minimize, maximize, and close buttons on the title bar of the window.
         *
         * @param { 'windowTitleButtonRectChange' } type - Event type. The value is fixed at 'windowTitleButtonRectChange',
         *                                                 indicating that the change event of the rectangle that holds the minimize, maximize, and close buttons.
         * @param { Callback<TitleButtonRect> } callback - Callback used to return the new rectangle.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowTitleButtonRectChange', callback: Callback<TitleButtonRect>): void;
        
        /**
         * Unsubscribes from the change event of the rectangle that holds the minimize, maximize, and close buttons on the title bar of the window.
         *
         * @param { 'windowTitleButtonRectChange' } type - Event type. The value is fixed at 'windowTitleButtonRectChange',
         *                                                 indicating that the change event of the rectangle that holds the minimize, maximize, and close buttons.
         * @param { Callback<TitleButtonRect> } callback - Callback used to return the new rectangle. If a value is passed in, the corresponding subscription is canceled.
         *                                                 If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowTitleButtonRectChange', callback?: Callback<TitleButtonRect>): void;
        /**
         * Register the callback of windowRectChange
         *
         * @param { 'windowRectChange' } type - The value is fixed at 'windowRectChange', indicating the window rect change event.
         * @param { Callback<RectChangeOptions> } callback - Callback used to return the RectChangeOptions.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'windowRectChange', callback: Callback<RectChangeOptions>): void;
        /**
         * Unregister the callback of windowRectChange
         *
         * @param { 'windowRectChange' } type - The value is fixed at 'windowRectChange', indicating the window rect change event.
         * @param { Callback<RectChangeOptions> } callback - Callback used to return the RectChangeOptions.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'windowRectChange', callback?: Callback<RectChangeOptions>): void;
        /**
         * Register the callback of rotation change
         *
         * @param { 'rotationChange' } type - The value is fixed at 'rotationChange',
         *     indicating the window rotation change event.
         * @param { RotationChangeCallback<RotationChangeInfo, RotationChangeResult | undefined> } callback -
         *     Callback used to return the rotation change result.
         * @throws { BusinessError } 801 - Capability not supported.
         *     Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        on(type: 'rotationChange', callback: RotationChangeCallback<RotationChangeInfo, RotationChangeResult | undefined>): void;
        /**
         * Unregister the callback of rotationChange
         *
         * @param { 'rotationChange' } type - The value is fixed at 'rotationChange',
         *     indicating the window rotation change event.
         * @param { RotationChangeCallback<RotationChangeInfo, RotationChangeResult | undefined> } [callback] -
         *     Callback used to return the RectChangeOptions.
         * @throws { BusinessError } 801 - Capability not supported.
         *     Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        off(type: 'rotationChange', callback?: RotationChangeCallback<RotationChangeInfo, RotationChangeResult | undefined>): void;
        /**
         * Set whether to enable immersive mode.
         *
         * @param { boolean } enabled - The value true means to enable immersive mode, and false means the opposite.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300003 - This window manager service works abnormally.
         * @throws { BusinessError } 1300004 - Unauthorized operation.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @since 20
         */
        setImmersiveModeEnabledState(enabled: boolean): void;
        /**
         * Get the window status of current window.
         *
         * @returns { WindowStatusType } - The status of window.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        getWindowStatus(): WindowStatusType;
    }
    
    
    /**
     * Window stage callback event type
     *
     * @enum { number }
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @StageModelOnly
     * @since 20
     */
    export enum WindowStageEventType {
        
        
        /**
         * The window stage is running in the foreground.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        SHOWN = 1,
        
        
        /**
         * The window stage gains focus.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        ACTIVE = 2,
        
        
        /**
         * The window stage loses focus.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        INACTIVE = 3,
        
        
        /**
         * The window stage is running in the background.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        HIDDEN = 4,
        /**
         * The window stage is interactive in the foreground.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        RESUMED = 5,
        /**
         * The window stage is not interactive in the foreground.
         *
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        PAUSED = 6
    }
    /**
     * Enum for window modality Type
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export enum ModalityType {
        /**
         * The value means window modality.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        WINDOW_MODALITY = 0,
        /**
         * The value means application modality.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        APPLICATION_MODALITY = 1
    }
    
    /**
     * Options for subwindow creation
     *
     * @interface SubWindowOptions
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    export interface SubWindowOptions {
    }
    
    
    /**
     * WindowStage
     *
     * @interface WindowStage
     * @syscap SystemCapability.WindowManager.WindowManager.Core
     * @since 20
     */
    export interface WindowStage {
        
        
        /**
         * Obtains the main window of this window stage. This API uses a promise to return the result.
         *
         * @returns { Promise<Window> } Promise used to return the main window.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        getMainWindow(): Promise<Window>;
        
        
        /**
         * Obtains the main window of this window stage. This API uses an asynchronous callback to return the result.
         *
         * @param { AsyncCallback<Window> } callback Callback used to return the main window.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        getMainWindow(callback: AsyncCallback<Window>): void;
        
        
        /**
         * Obtains the main window of this window stage.
         *
         * @returns { Window } Main window.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        getMainWindowSync(): Window;
        
        
        /**
         * Creates a child window for this window stage. This API uses a promise to return the result.
         *
         * @param { string } name Name of the child window.
         * @returns { Promise<Window> } Promise used to return the child window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        createSubWindow(name: string): Promise<Window>;
        
        
        /**
         * Creates a child window for this window stage. This API uses an asynchronous callback to return the result.
         *
         * @param { string } name Name of the child window.
         * @param { AsyncCallback<Window> } callback Callback used to return the child window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        createSubWindow(name: string, callback: AsyncCallback<Window>): void;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to the main window of this window stage, and transfers the state attribute to the page through a local storage.
         * This API uses an asynchronous callback to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content. Exercise caution when using it.
         *
         * @param { string } path Path of the page to which the content will be loaded
         * @param { LocalStorage } storage The data object shared within the content instance loaded by the window
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         *                                                                  3. Invalid path parameter.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        loadContent(path: string, storage: LocalStorage, callback: AsyncCallback<void>): void;
        
        
        /**
         * Loads the content of a page, with its path in the current project specified, to the main window of this window stage, and transfers the state attribute to the page through a local storage.
         * This API uses a promise to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content. Exercise caution when using it.
         *
         * @param { string } path of the page to which the content will be loaded
         * @param { LocalStorage } storage The data object shared within the content instance loaded by the window
         * @returns { Promise<void> }
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         *                                                                  3. Invalid path parameter.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        loadContent(path: string, storage?: LocalStorage): Promise<void>;
        
        
        /**
         * Loads content from a page to this window stage. This API uses an asynchronous callback to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content. Exercise caution when using it.
         *
         * @param { string } path of the page to which the content will be loaded
         * @param { AsyncCallback<void> } callback Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         *                                                                  3. Invalid path parameter.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        loadContent(path: string, callback: AsyncCallback<void>): void;
        /**
         * Loads the content of a named route page to this window, and transfers the state attribute to the page through a local storage.
         * This API uses an asynchronous callback to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content.
         * Exercise caution when using it.
         *
         * @param { string } name - Name of the named route page.
         * @param { LocalStorage } storage - Page-level UI state storage unit, which is used to transfer the state attribute for the page.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @stagemodelonly
         * @since 20
         */
        loadContentByName(name: string, storage: LocalStorage, callback: AsyncCallback<void>): void;
        /**
         * Loads the content of a named route page to this window, and transfers the state attribute to the page through a local storage.
         * This API uses an asynchronous callback to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content.
         * Exercise caution when using it.
         *
         * @param { string } name - Name of the named route page.
         * @param { AsyncCallback<void> } callback - Callback used to return the result.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @stagemodelonly
         * @since 20
         */
        loadContentByName(name: string, callback: AsyncCallback<void>): void;
        /**
         * Loads the content of a named route page to this window, and transfers the state attribute to the page through a local storage.
         * This API uses an asynchronous callback to return the result. You are advised to call this API during UIAbility startup.
         * If called multiple times, this API will destroy the existing page content (UIContent) before loading the new content.
         * Exercise caution when using it.
         *
         * @param { string } name - Name of the named route page.
         * @param { LocalStorage } storage - Page-level UI state storage unit, which is used to transfer the state attribute for the page.
         * @returns { Promise<void> } Promise that returns no value.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @stagemodelonly
         * @since 20
         */
        loadContentByName(name: string, storage?: LocalStorage): Promise<void>;
        
        
        /**
         * Subscribes to the window stage lifecycle change event.
         *
         * @param { 'windowStageEvent' } eventType Event type. The value is fixed at 'windowStageEvent', indicating the window stage lifecycle change event.
         * @param { Callback<WindowStageEventType> } callback Callback used to return the window stage lifecycle state.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        on(eventType: 'windowStageEvent', callback: Callback<WindowStageEventType>): void;
        
        
        /**
         * Unsubscribes from the window stage lifecycle change event.
         *
         * @param { 'windowStageEvent' } eventType Event type. The value is fixed at 'windowStageEvent', indicating the window stage lifecycle change event.
         * @param { Callback<WindowStageEventType> } callback Callback used to return the window stage lifecycle state.
         *                                                    If a value is passed in, the corresponding subscription is canceled.
         *                                                    If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Incorrect parameter types;
         *                                                                  2. Parameter verification failed.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @StageModelOnly
         * @since 20
         */
        off(eventType: 'windowStageEvent', callback?: Callback<WindowStageEventType>): void;
        /**
         * Subscribes to the click event on the close button in the three-button navigation bar of the main window.
         * This event is triggered when the close button in the three-button navigation bar of the main window is clicked.
         *
         * @param { 'windowStageClose' } eventType - Event type. The value is fixed at 'windowStageClose',
         *                                           indicating that the close button in the three-button navigation bar of the main window is clicked.
         * @param { Callback<void> } callback - Callback invoked when the close button in the upper right corner of the main window is clicked.
         *                                      The return value determines whether to continue to close the main window.
         *                                      The value true means not to close the main window, and false means to continue to close the main window.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @stagemodelonly
         * @since 20
         */
        on(eventType: 'windowStageClose', callback: Callback<void>): void;
        /**
         * Unsubscribes from the event indicating that the main window is closed.
         *
         * @param { 'windowStageClose' } eventType - Event type. The value is fixed at 'windowStageClose',
         *                                           indicating that the close button in the three-button navigation bar of the main window is clicked.
         * @param { Callback<void> } callback - Callback invoked when the close button in the upper right corner of the main window is clicked.
         *                                      If a value is passed in, the corresponding subscription is canceled.
         *                                      If no value is passed in, all subscriptions to the specified event are canceled.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types;
         *                                                                  3. Parameter verification failed.
         * @throws { BusinessError } 801 - Capability not supported. Failed to call the API due to limited device capabilities.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @syscap SystemCapability.Window.SessionManager
         * @stagemodelonly
         * @since 20
         */
        off(eventType: 'windowStageClose', callback?: Callback<void>): void;
        
        /**
         * Disable window decoration. It must be called before loadContent.
         *
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi
         * @StageModelOnly
         * @since 20
         */
        disableWindowDecor(): void;
        
        /**
         * Sets whether can show on lock screen or not
         *
         * @param { boolean } showOnLockScreen can show on lock screen if true, or not if false
         * @throws { BusinessError } 202 - Permission verification failed. A non-system application calls a system API.
         * @throws { BusinessError } 401 - Parameter error. Possible cause: 1. Mandatory parameters are left unspecified;
         *                                                                  2. Incorrect parameter types.
         * @throws { BusinessError } 1300002 - This window state is abnormal.
         * @throws { BusinessError } 1300005 - This window stage is abnormal.
         * @syscap SystemCapability.WindowManager.WindowManager.Core
         * @systemapi Hide this for inner system use.
         * @StageModelOnly
         * @since 20
         */
        setShowOnLockScreen(showOnLockScreen: boolean): void;
    }
    /**
     * Attribute of the window for UI service extension ability.
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @systemapi Hide this for inner system use.
     * @stagemodelonly
     * @since 20
     */
    export enum ExtensionWindowAttribute {
        /**
         * System window.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        SYSTEM_WINDOW = 0,
        /**
         * Sub window.
         *
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        SUB_WINDOW = 1
    }
    /**
     * Options for system window creation.
     *
     * @interface SystemWindowOptions
     * @syscap SystemCapability.Window.SessionManager
     * @systemapi Hide this for inner system use.
     * @stagemodelonly
     * @since 20
     */
    export interface SystemWindowOptions {
        /**
         * Indicates window type.
         *
         * @type { WindowType }
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        windowType: WindowType;
    }
    /**
     * Configuration of the window for UI service extension ability.
     *
     * @interface ExtensionWindowConfig
     * @syscap SystemCapability.Window.SessionManager
     * @systemapi Hide this for inner system use.
     * @stagemodelonly
     * @since 20
     */
    export interface ExtensionWindowConfig {
        /**
         * Window name.
         *
         * @type { string }
         * @syscap SystemCapability.Window.SessionManager
         * @systemapi Hide this for inner system use.
         * @stagemodelonly
         * @since 20
         */
        windowName: string;
    }
    /**
     * Rotation change type
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    enum RotationChangeType {
        /**
         * Rotation will begin
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        WINDOW_WILL_ROTATE = 0,
        /**
         * Rotation end
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        WINDOW_DID_ROTATE = 1
    }
    /**
     * Rect type
     *
     * @enum { number }
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    enum RectType {
        /**
         * Rect relative to screen
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        RELATIVE_TO_SCREEN = 0,
        /**
         * Rect relative to parent window
         *
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        RELATIVE_TO_PARENT_WINDOW = 1
    }
    /**
     * Rotation change info
     *
     * @interface RotationChangeInfo
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    interface RotationChangeInfo {
        /**
         * Rotation change type
         *
         * @type { RotationChangeType }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        type: RotationChangeType;
        /**
         * window orientation
         *
         * @type { int }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        orientation: int;
        /**
         * Display id
         *
         * @type { long }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        displayId: long;
        /**
         * Display rect
         *
         * @type { Rect }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        displayRect: Rect;
    }
    /**
     * Rotation change result
     *
     * @interface RotationChangeResult
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    interface RotationChangeResult {
        /**
         * Rect type
         *
         * @type { RectType }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        rectType: RectType;
        /**
         * Window rect
         *
         * @type { Rect }
         * @syscap SystemCapability.Window.SessionManager
         * @since 20
         */
        windowRect: Rect;
    }
    /**
     * Rotation Change callback
     *
     * @typedef {function}
     * @param { T } info
     * @returns { U } result
     * @syscap SystemCapability.Window.SessionManager
     * @since 20
     */
    type RotationChangeCallback<T, U> = (info: T) => U;
}
export default window;

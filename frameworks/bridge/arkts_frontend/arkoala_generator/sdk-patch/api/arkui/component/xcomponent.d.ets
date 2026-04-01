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
 * @kit ArkUI
 */
import { ImageAIOptions, ImageAnalyzerConfig } from "./imageCommon";
import { CommonMethod, AttributeModifier, Callback } from "./common";
import { XComponentType } from "./enums";
import { VoidCallback, DrawingCanvas } from "./units";
import { ComponentBuilder } from './builder';

/**
 * Surface Rectangle information.
 *
 * @interface SurfaceRect
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SurfaceRect {
    /**
     * The horizontal offset of the surface relative to XComponent.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetX?: double;
    /**
     * The vertical offset of the surface relative to XComponent.
     *
     * @type { ?double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    offsetY?: double;
    /**
     * The width of the surface created by XComponent
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    surfaceWidth: double;
    /**
     * The height of the surface created by XComponent
     *
     * @type { double }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    surfaceHeight: double;
}

/**
 * Defines the NativeXComponent Pointer type.
 *
 * @typedef { long } NativeXComponentPointer
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export type NativeXComponentPointer = long;

/**
 * Surface rotation options.
 *
 * @interface SurfaceRotationOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface SurfaceRotationOptions {
    /**
     * Lock property of the surface rotation.
     *
     * @type { ?boolean }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    lock?: boolean;
}

/**
 * Surface config.
 *
 * @interface SurfaceConfig
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 */
export declare interface SurfaceConfig {
    /**
    * Whether the surface held by XComponent needs to be considered opaque,
    * even if the surface has translucent pixel.
    * True means needing to be considered opaque, false otherwise.
    *
    * @type { ?boolean }
    * @default false
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    isOpaque?: boolean;
}

/**
 * Sets the HDR type of the XComponent.
 *
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 24
 */
export declare enum HdrType {
  /**
   * Default type.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  DEFAULT = 0,
  /**
   * AIHDR type.
   *
   * @syscap SystemCapability.ArkUI.ArkUI.Full
   * @stagemodelonly
   * @since 24
   */
  AIHDR = 1,
  // instructive change start
  EDR = 2,
  // instructive change end
}

/**
 * Defines XComponentController
 *
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare class XComponentController {
    /**
     * Constructor.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    constructor();
    /**
     * Get the id of surface created by XComponent.
     *
     * @returns { string } The id of surface created by XComponent.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getXComponentSurfaceId(): string;
    /**
     * Set the rectangle information of surface created by XComponent.
     *
     * @param { SurfaceRect } rect - The surface rectangle information.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setXComponentSurfaceRect(rect: SurfaceRect): void;
    /**
     * Get the rectangle information of Surface created by XComponent.
     *
     * @returns { SurfaceRect } The surface rectangle information.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getXComponentSurfaceRect(): SurfaceRect;
    /**
     * Set the rotation options of the Surface created by XComponent.
     *
     * @param { SurfaceRotationOptions } rotationOptions - The surface rotation options.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    setXComponentSurfaceRotation(rotationOptions: SurfaceRotationOptions): void;
    /**
     * Get the rotation options result of the Surface created by XComponent.
     *
     * @returns { Required<SurfaceRotationOptions> } The surface rotation options result.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    getXComponentSurfaceRotation(): Required<SurfaceRotationOptions>;
    /**
     * Called after the surface is first created.
     *
     * @param { string } surfaceId - The id of the surface created by XComponent.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onSurfaceCreated(surfaceId: string): void;
    /**
     * Called after the surface rectangle information is changed.
     *
     * @param { string } surfaceId - The id of the surface created by XComponent.
     * @param { SurfaceRect } rect - The rectangle information of the surface created by XComponent.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onSurfaceChanged(surfaceId: string, rect: SurfaceRect): void;
    /**
     * Called when the surface is about to be destroyed.
     *
     * @param { string } surfaceId - The id of the surface created by XComponent.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    onSurfaceDestroyed(surfaceId: string): void;
    /**
     * Start image analyzer.
     *
     * @param { ImageAnalyzerConfig } config - Image analyzer config.
     * @returns { Promise<void> } The promise returned by the function.
     * @throws { BusinessError } 110001 - Image analysis feature is unsupported.
     * @throws { BusinessError } 110002 - Image analysis is currently being executed.
     * @throws { BusinessError } 110003 - Image analysis is stopped.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    startImageAnalyzer(config: ImageAnalyzerConfig): Promise<void>;
    /**
     * Stop image analyzer.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    stopImageAnalyzer(): void;

    /**
    * Get a Canvas for drawing into the surface created by XComponent.
    *
    * @returns { DrawingCanvas | null} Returns a Canvas for drawing into the surface created by XComponent.
    *    Returns null if the surface is not available.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    lockCanvas(): DrawingCanvas | null;

    /**
    * Posts the new contents of the Canvas to the surface created by XComponent and releases the Canvas.
    *
    * @param { DrawingCanvas } canvas - The canvas previously obtained from lockCanvas.
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    unlockCanvasAndPost(canvas: DrawingCanvas):void;

    /**
    * Set the config of the surface created by the XComponent.
    *
    * @param { SurfaceConfig } config - surface config
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @since 23
    */
    setXComponentSurfaceConfig(config: SurfaceConfig):void;
}

/**
 * Defines the xcomponent options.
 *
 * @interface XComponentOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface XComponentOptions {
    /**
     * The type of xcomponent
     *
     * @type { XComponentType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: XComponentType;
    /**
     * The controller of xcomponent.
     *
     * @type { XComponentController }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    controller: XComponentController;
    /**
     * Image ai options.
     *
     * @type { ?ImageAIOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    imageAIOptions?: ImageAIOptions;
    /**
    * Identifier of a screen.
    *
    * @type { ?long }
    * @syscap SystemCapability.ArkUI.ArkUI.Full
    * @systemapi
    * @since 23
    */
    screenId?: long;
}

/**
 * Defines the native xcomponent parameters.
 *
 * @interface NativeXComponentParameters
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface NativeXComponentParameters {
    /**
     * The type of xcomponent
     *
     * @type { XComponentType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: XComponentType;
    /**
     * Image ai options.
     *
     * @type { ?ImageAIOptions }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    imageAIOptions?: ImageAIOptions;
}

/**
 * Defines the XComponent attribute.
 *
 * @extends CommonMethod
 * @interface XComponentAttribute
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface XComponentAttribute extends CommonMethod {
    /**
     * Called when judging whether the xcomponent surface is created.
     *
     * @param { VoidCallback | undefined } callback - Called when judging whether the xcomponent surface is created.
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onLoad(callback: VoidCallback | undefined): this;
    /**
     * Called when judging whether the xcomponent is destroyed.
     *
     * @param { VoidCallback | undefined } event - Called when judging whether the xcomponent is destroyed.
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default onDestroy(event: VoidCallback | undefined): this;
    /**
     * Enable image analyzer for XComponent.
     *
     * @param { boolean | undefined } enable
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default enableAnalyzer(enable: boolean | undefined): this;
    /**
     * Enable privacy protection for XComponent.
     *
     * @param { boolean | undefined } isSecure
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default enableSecure(isSecure: boolean | undefined): this;
    /**
     * Enable transparent layer for XComponent.
     *
     * @param { boolean | undefined } enabled - whether to enable transparent layer for XComponent.
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @systemapi
     * @since 23
     */
    default enableTransparentLayer(enabled: boolean | undefined): this;
    /**
     * Set hdrBrightness for XComponent.
     *
     * @param { double | undefined } brightness - control the brightness of HDR video
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default hdrBrightness(brightness: double | undefined): this;
    /**
     * Set hdrBrightness for XComponent.
     *
     * @param { double | undefined } brightness - control the brightness of HDR video
     * @param { HdrType } [type] - the HDR type of the XComponent
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @stagemodelonly
     * @since 24
     */
    default hdrBrightness(brightness: double | undefined, type?: HdrType): this;
    /**
     * Call attributeModifier.
     *
     * @param { AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined } modifier
     * @returns { XComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    default attributeModifier(modifier: AttributeModifier<XComponentAttribute> | AttributeModifier<CommonMethod> | undefined): this;
}

/**
 * Defines the XComponent parameter interface.
 *
 * @interface XComponentParameters
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 23
 */
export declare interface XComponentParameters {
    /**
     * The id of xcomponent
     *
     * @type { string }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    id: string;
    /**
     * The type of xcomponent
     *
     * @type { XComponentType }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    type: XComponentType;
    /**
     * The callback to handle NativeXComponent Pointer.
     *
     * @type { Callback<NativeXComponentPointer> }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    nativeXComponentHandler: Callback<NativeXComponentPointer>;
    /**
     * The controller of xcomponent.
     *
     * @type { ?XComponentController }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 23
     */
    controller?: XComponentController;
}

/**
 * XComponent is returned when the parameter is transferred.
 *
 * @param { XComponentParameters | XComponentOptions | NativeXComponentParameters } params - The 
 *     options to create an XComponent
 * @returns { XComponentAttribute } The attribute of the XComponent
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @stagemodelonly
 * @since 23
 * @noninterop
 */
@ComponentBuilder
export declare function XComponent(
    params: XComponentParameters | XComponentOptions | NativeXComponentParameters,
): XComponentAttribute

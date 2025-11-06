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
import Want from '../../@ohos.app.ability.Want';
import { RecordData } from './pluginComponent';
import { Callback, ErrorCallback, BusinessError } from '../../@ohos.base';
import { AttributeModifier, CommonMethod, TerminationInfo } from './common';
import { ComponentContent } from '../ComponentContent';
import { memo, ComponentBuilder } from './../stateManagement/runtime';

/**
 * Enumeration of different types of SecurityDpiFollowStrategy.
 *
 * @enum { int }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 */
export declare enum SecurityDpiFollowStrategy {
    /**
     * Followed the host DPI.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    FOLLOW_HOST_DPI = 0,
    /**
     * Followed the UIExtensionAbility.
     *
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    FOLLOW_UI_EXTENSION_ABILITY_DPI = 1
}
/**
 * This interface is used to set the options for SecurityUIExtensionComponentAttribute during construction
 *
 * @interface SecurityUIExtensionOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 */
export declare interface SecurityUIExtensionOptions {
    /**
     * Set whether the current capability is used as a Caller.<br/>
     * If set to true, as a Caller, the current token of SecurityUIExtensionComponent is set to rootToken.
     *
     * @type { ?boolean }
     * @default false
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    isTransferringCaller?: boolean;
    /**
     * Set placeholder.
     * If set placeholder ComponentContent, show placeholder node when connection is not established.
     *
     * @type { ?ComponentContent }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    placeholder?: ComponentContent;
    /**
     * Set SecurityUIExtensionComponent Content Dpi Follow Strategy.
     *
     * @type { ?SecurityDpiFollowStrategy }
     * @default SecurityDpiFollowStrategy.FOLLOW_UI_EXTENSION_ABILITY_DPI
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    dpiFollowStrategy?: SecurityDpiFollowStrategy;
}
/**
 * Get Callback from @ohos.base.
 *
 * @typedef { Callback<Record<string, RecordData>> }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 */
export type ReceiveCallback = Callback<Record<string, RecordData>>;
/**
 * This interface is used for send data to the UIExtensionAbility.<br/>
 * It is returned from onRemoteReady callback of SecurityUIExtensionComponent<br/>
 * when UIExtensionAbility connects successfully
 *
 * @interface SecurityUIExtensionProxy
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 */
export declare interface SecurityUIExtensionProxy {
    /**
     * This function is for sending data to the UIExtensionAbility.
     * AnonyMous Object Rectification
     *
     * @param { Record<string, RecordData> } data
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    send(data: Record<string, RecordData>): void;
    /**
     * This function is for sending data to the UIExtensionAbility and waiting for the result in blocking mode.
     * AnonyMous Object Rectification
     *
     * @param { Record<string, RecordData> } data - Data send to the UIExtensionAbility.
     * @returns { Record<string, RecordData> } data - Data transferred from the UIExtensionAbility.
     * @throws { BusinessError } 100011 - No callback has been registered to respond to this request.
     * @throws { BusinessError } 100012 - Transferring data failed.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    sendSync(data: Record<string, RecordData>): Record<string, RecordData>;
    /**
     * Register the listener that watches for async data receiver callback being registered by UIExtensionAbility.
     * AnonyMous Object Rectification
     *
     * @param { Callback<SecurityUIExtensionProxy> } callback - Callback of the listened event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 22 static
     */
    onAsyncReceiverRegister(callback: Callback<SecurityUIExtensionProxy>): void;
    /**
     * Register the listener that watches for sync data receiver callback being registered by UIExtensionAbility.
     * AnonyMous Object Rectification
     *
     * @param { Callback<SecurityUIExtensionProxy> } callback - Callback of the listened event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 22 static
     */
    onSyncReceiverRegister(callback: Callback<SecurityUIExtensionProxy>): void;
    /**
     * Deregisters the listener that watches for async data receiver callback being registered by UIExtensionAbility.
     * AnonyMous Object Rectification
     *
     * @param { Callback<SecurityUIExtensionProxy> } [callback] - Callback of the listened event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 22 static
     */
    offAsyncReceiverRegister(callback?: Callback<SecurityUIExtensionProxy>): void;
    /**
     * Deregisters the listener that watches for sync data receiver callback being registered by UIExtensionAbility.
     * AnonyMous Object Rectification
     *
     * @param { Callback<SecurityUIExtensionProxy> } [callback] - Callback of the listened event.
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 22 static
     */
    offSyncReceiverRegister(callback?: Callback<SecurityUIExtensionProxy>): void;
}

/**
 * Define the attribute functions of SecurityUIExtensionComponent.
 *
 * @extends CommonMethod
 * @typedef SecurityUIExtensionComponentAttribute
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 * @noninterop
 */
export declare interface SecurityUIExtensionComponentAttribute extends CommonMethod {
    /**
     * callback called when remote UIExtensionAbility object is ready for receive data
     *
     * @param { Callback<SecurityUIExtensionProxy> | undefined } callback
     * @returns { SecurityUIExtensionComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    onRemoteReady(callback: Callback<SecurityUIExtensionProxy> | undefined): this;
    /**
     * AnonyMous Object Rectification
     *
     * @param { ReceiveCallback | undefined  } callback - Called when data received from UIExtensionAbility
     * @returns { SecurityUIExtensionComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    onReceive(callback: ReceiveCallback | undefined): this;
    /**
     * called when some error occurred except disconnected from UIExtensionAbility.
     *
     * @param { ErrorCallback<BusinessError> | undefined } callback
     * @returns { SecurityUIExtensionComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    onError(callback: ErrorCallback<BusinessError> | undefined): this;
    /**
     * Called when the provider of the embedded UI is terminated.
     *
     * @param { Callback<TerminationInfo> | undefined } callback
     * @returns { SecurityUIExtensionComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    onTerminated(callback: Callback<TerminationInfo> | undefined): this;
    /**
     * Set the attribute modifier of SecurityUIExtensionComponent Component.
     *
     * @param { AttributeModifier<SecurityUIExtensionComponentAttribute> | undefined } modifier
     * @returns { SecurityUIExtensionComponentAttribute }
     * @syscap SystemCapability.ArkUI.ArkUI.Full
     * @since 20 static
     */
    attributeModifier(modifier: AttributeModifier<SecurityUIExtensionComponentAttribute> | undefined): this;
}

/**
 * Defines SecurityUIExtensionComponent Component.
 * @param { Want } want - The want
 * @param { SecurityUIExtensionOptions } [options] - The options
 * @param { function } [content_] - container
 * @returns { SecurityUIExtensionComponentAttribute }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @since 20 static
 * @noninterop
 */
@memo
@ComponentBuilder
export declare function SecurityUIExtensionComponent(
    want: Want, options?: SecurityUIExtensionOptions, 
    @memo
    content_?: () => void,
): SecurityUIExtensionComponentAttribute
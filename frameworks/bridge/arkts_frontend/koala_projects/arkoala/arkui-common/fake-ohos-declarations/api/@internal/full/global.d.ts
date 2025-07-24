/*
 * Copyright (c) 2021-2023 Huawei Device Co., Ltd.
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
 * Obtains all attributes of the component with the specified ID.
 * @param id ID of the component whose attributes are to be obtained.
 * @since 9
 * @test
 */
declare function getInspectorByKey(id: string): string;
/**
 * Get components tree.
 * @since 9
 * @test
 */
declare function getInspectorTree(): string;
/**
 * Sends an event to the component with the specified ID.
 * @param id ID of the component for which the event is to be sent.
 * @param action Type of the event to be sent. The options are as follows: Click event: 10 LongClick: 11.
 * @param params Event parameters. If there is no parameter, pass an empty string "".
 * @since 9
 * @test
 */
declare function sendEventByKey(id: string, action: number, params: string): boolean;

declare var value: any;
declare var uiContext: any;
declare var abilityContext: any;
declare var _objects: any;
declare var winLeft: number;
declare var winTop: number;

declare function sleepUITest(timeMs: number): Promise<void>;
declare function getComponentRect(id: string): any;

declare function setTimeout(handler: Function | string, delay?: number, ...arguments: any[]): number;
declare function setInterval(handler: Function | string, delay: number, ...arguments: any[]): number;
declare function clearInterval(intervalID?: number): void;
declare function clearTimeout(timeoutID?: number): void;

// TODO: temprary fix for API_12
        // This needs to be global to avoid TS2403 in case lib.dom.d.ts is present in the same build
declare const console: {
            // Console: console.ConsoleConstructor;

            assert(value: any, message?: string, ...optionalParams: any[]): void;

            clear(): void;

            count(label?: string): void;

            countReset(label?: string): void;

            debug(message?: any, ...optionalParams: any[]): void;

            // dir(obj: any, options?: InspectOptions): void;

            dirxml(...data: any[]): void;

            error(message?: any, ...optionalParams: any[]): void;

            group(...label: any[]): void;

            groupCollapsed(...label: any[]): void;

            groupEnd(): void;

            info(message?: any, ...optionalParams: any[]): void;

            log(message?: any, ...optionalParams: any[]): void;

            table(tabularData: any, properties?: ReadonlyArray<string>): void;

            time(label?: string): void;

            timeEnd(label?: string): void;

            timeLog(label?: string, ...data: any[]): void;

            trace(message?: any, ...optionalParams: any[]): void;

            warn(message?: any, ...optionalParams: any[]): void;

            profile(label?: string): void;

            profileEnd(label?: string): void;

            timeStamp(label?: string): void;

        }


/**
 * Defining syscap function.
 *
 * @param { string } syscap
 * @returns { boolean }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @since 10
 */
declare function canIUse(syscap: string): boolean;

/**
 * Send key event.
 *
 * @param { KeyEvent } event - KeyEvent to be sent.
 * @returns { boolean }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @since 10
 * @test
 */
declare function sendKeyEvent(event: KeyEvent): boolean;

/**
 * Send mouse event.
 *
 * @param { MouseEvent } event - MouseEvent to be sent.
 * @returns { boolean }
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @since 10
 * @test
 */
declare function sendMouseEvent(event: MouseEvent): boolean;
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
 *  SDK API of AddMonitor and its option.
 */
/**
 * Function that returns monitor instance value when state variable is changed.
 *
 * @typedef { function } MonitorCallback
 * @param { IMonitor} monitorValue monitor instance value when state variable is changed.
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 20
 */
declare type MonitorCallback = (monitorValue: IMonitor) => void;

/**
 * Define Monitor options.
 *
 * @interface MonitorOptions
 * @syscap SystemCapability.ArkUI.ArkUI.Full
 * @crossplatform
 * @atomicservice
 * @since 20
 */
interface MonitorOptions {
  /**
  * Used to determine whether the state variable change is
  * triggered synchronously or asynchronously. The default value is false.
  *
  * @type { ?boolean } isSynchronous parameter
  * @default false
  * @syscap SystemCapability.ArkUI.ArkUI.Full
  * @crossplatform
  * @atomicservice
  * 
  * @since 20
  */
  isSynchronous?: boolean;
}
/*
 * Copyright (c) 2022-2024 Huawei Device Co., Ltd.
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

import UIAbility from "@ohos.app.ability.UIAbility";

export * from "@koalaui/arkoala"
export * from "@koalaui/arkoala-arkui"

interface ArkoalaModuleInfo {
    bundleName: string;
    moduleName: string;
}

// TODO better signature for both ArkUI and Arkoala type check
export function startArkoala(entryPageUrl: string, info: ArkoalaModuleInfo): Promise<void>
export function loadPage(page: string): Promise<void>;
export declare class ArkoalaAbility extends UIAbility {}

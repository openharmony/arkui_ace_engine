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

export * from "@koalaui/arkoala"
export * from "@koalaui/arkoala-arkui"

import { startApplicationByPageUrl } from "@koalaui/arkoala-arkui"

let moduleInfo;

export function startArkoala(startPage, info) {
    moduleInfo = { ...info }
    return startApplicationByPageUrl(startPage)
}

export { __setPageLoader } from "./load_page.mjs"

export function __getModuleInfo() {
    return moduleInfo;
}

export function wrapOnWindowStageCreate(receiver) {
    let onWindowStageCreate = receiver.onWindowStageCreate;
    receiver.onWindowStageCreate = (windowStage, ...args) => {
        let loadContent = windowStage.loadContent;
        windowStage.loadContent = (url, ...loadArgs) => {
            let cb;
            if (typeof loadArgs[0] === "function") {
                cb = loadArgs[0]
            } else if (typeof loadArgs[1] === "function") {
                cb = loadArgs[1]
            }
            let newCb = (err, data, ...rest) => {
                windowStage.getMainWindowSync().getUIContext().runScopedTask(() => {
                    let abilityInfo = receiver.context.abilityInfo
                    let bundleName = abilityInfo.bundleName, moduleName = abilityInfo.moduleName
                    startArkoala(url, { bundleName, moduleName });
                });
                return cb?.(err, data, ...rest);
            };
            if (typeof loadArgs[0] === "function") {
                loadArgs[0] = newCb
            } else if (typeof loadArgs[1] === "function") {
                loadArgs[1] = newCb
            } else {
                loadArgs = (loadArgs || []).unshift(newCb)
            }
            return loadContent.call(windowStage, 'arkoala', ...loadArgs);
        };
        return onWindowStageCreate.call(receiver, windowStage, ...args)
    };
}

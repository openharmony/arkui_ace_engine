/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
 *
 */

class Utils {
    private static currentAppApiVersion: number = -1;
    private static arkTsUtil: ArkTsUtil | undefined = undefined;

    public static getApiVersion(): number {
        if (Utils.currentAppApiVersion <= 0) {
            Utils.currentAppApiVersion = typeof ViewStackProcessor.getApiVersion === 'function'
                ? ViewStackProcessor.getApiVersion() : -1;
        }
        return Utils.currentAppApiVersion;
    }

    public static isApiVersionEQAbove(target: number): boolean {
        let version = Utils.getApiVersion();
        if (version <= 0) {
            stateMgmtConsole.error(`get api version error in isApiVersionEQAbove, version:${version}`);
            return false;
        }
        return version % 1000 >= target;
    }

    public static getArkTsUtil(): ArkTsUtil {
        if (!Utils.arkTsUtil) {
            Utils.arkTsUtil = requireInternal('util');
        }
        return Utils.arkTsUtil;
    }
}
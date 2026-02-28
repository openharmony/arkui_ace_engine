/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
import JSON from "@ohos.util.json";
import hilog from "@ohos.hilog";
const TAG = 'JsonUtil';
const DOMAIN = 0x0f5c;
export class JsonUtils {
    static stringify(value, replacer, space) {
        try {
            return JSON.stringify(value, replacer, space);
        }
        catch (error) {
            hilog.error(DOMAIN, TAG, `JSON stringify failed.`, error);
            return '';
        }
    }
    static parse(text, reviver, options) {
        try {
            return JSON.parse(text, reviver, options);
        }
        catch (error) {
            hilog.error(DOMAIN, TAG, `JSON parse failed.`, error);
            return undefined;
        }
    }
}
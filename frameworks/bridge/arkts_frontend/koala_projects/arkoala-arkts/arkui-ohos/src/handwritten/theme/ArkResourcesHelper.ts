/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

import { Resource } from 'global.resource';

export class ArkResourcesHelper {
    static COLOR: number = 10001;
    static FLOAT: number = 10002;

    static $r(name: string, id?: number): Resource {
        let splitted = name.split('.', 2);
        let strType = splitted[1];
        let type: number = ArkResourcesHelper.COLOR;
        if (strType === 'float') {
            type = ArkResourcesHelper.FLOAT;
        }
        return { 'id': id ?? -1, 'type': type, 'params': [name], 'bundleName': '', 'moduleName': '' } as Resource;
    }
}
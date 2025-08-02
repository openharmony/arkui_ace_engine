/*
 * Copyright (c) 2022-2023 Huawei Device Co., Ltd.
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


export class ArkResource implements Resource {
    public name: string // TODO do we need the raw resource key?
    public id: number
    public type: number
    public params?: any[]
    public moduleName: string
    public bundleName: string

    constructor(
        bundleName: string,
        moduleName: string,
        id: number,
        type: number,
        name: string,
        params?: any[],
    ) {
        this.bundleName = bundleName
        this.moduleName = moduleName
        this.id = id
        this.type = type
        this.params = params
        this.name = name
    }
}

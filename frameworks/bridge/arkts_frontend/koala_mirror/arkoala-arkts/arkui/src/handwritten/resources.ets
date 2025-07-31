/*
 * Copyright (c) 2022-2025 Huawei Device Co., Ltd.
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

import { Resource } from "../generated";
import { int32 } from "@koalaui/common";
import { SerializerBase } from "@koalaui/interop";
import { ArkUIGeneratedNativeModule } from "#components";

class ArkResource implements Resource {
    bundleName: string = "";
    moduleName: string = "";
    params?: Array<string> | undefined;
    type?: number | undefined;
    _id: number = -1;
    constructor(resourceName: string, bundleName: string, moduleName: string) {
        this.bundleName = bundleName;
        this.moduleName = moduleName;
        this.params = new Array<string>(resourceName);
        this._id = -1;
        const param: string = resourceName.split(".")[1];
        this.type = 20000;
        switch (param) {
            case 'media':
                this.type = 20000;
                break;
            case 'color':
                this.type = 10001;
                break;
            case 'string':
                this.type = 10003;
                break;
            case 'float':
                this.type = 10002;
                break;
        }
    }
    set id(value: number) {
        this._id = value;
    }
    get id(): number {
        if (this._id == -1) {
            if (this.params == null || this.params == undefined) {
                return this._id;
            }
            let param = this.params;
            let bundleNamea = this.bundleName;
            let moduleNamea = this.moduleName;
            const thisSerializer: SerializerBase = SerializerBase.hold();
            if (param == null) {
                thisSerializer.release();
                return this._id;
            }
            thisSerializer.writeInt32(param.length as int32);
            for (let i = 0; i < param.length; i++) {
                const params_element: string = param[i];
                thisSerializer.writeString(params_element);
            }
            const retval = ArkUIGeneratedNativeModule._SystemOps_getResourceId(bundleNamea, moduleNamea, thisSerializer.asBuffer(), thisSerializer.length());
            thisSerializer.release();
            this._id = retval;
        }
        return this._id;
    }
}
export function _r(bundleName: string, moduleName: string, name: string): Resource {
    return new ArkResource(name, bundleName, moduleName)
}
export function _rawfile(bundleName: string, moduleName: string, name: string): Resource {
    return {
        "id": 0,
        "type": 30000,
        "params": new Array<string>(name),
        "bundleName": bundleName,
        "moduleName": moduleName
    } as Resource
}
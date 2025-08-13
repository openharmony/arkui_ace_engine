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

import { int32 } from "@koalaui/common"
import { ArkResource } from "../../component/resources"

export class ResourceTransfer {
    static transferStatic(input: Any): Object {
        if (typeof (input) !== 'object') {
            throw Error("The Resource is not object convert fail.");
        }
        const bundleName = ESValue.wrap(input).getProperty("bundleName").toString();
        const moduleName = ESValue.wrap(input).getProperty("moduleName").toString();
        const params = ESValue.wrap(input).getProperty("params");
        const paramsArray: Array<Object|undefined> = new Array<Object|undefined>();
        const parray = params.unwrap() as Any[];
        let arrayLength = parray.length;
        for (let i = 0; i < arrayLength; i++) {
            let item = params.getProperty(i);
            if (item.isBoolean()) {
                paramsArray.push(item.toBoolean());
            }
            if (item.isString()) {
                paramsArray.push(item.toString());
            }
            if (item.isNumber()) {
                paramsArray.push(item.toNumber());
            }
            if (item.isBigInt()) {
                paramsArray.push(item.toBigInt());
            }
            if (item.isUndefined()) {
                paramsArray.push(item.toUndefined());
            }
            if (item.isStaticObject()) {
                paramsArray.push(item.toStaticObject());
            }
        }
        let type: int32 | undefined = undefined;
        let id: long = -1;
        if (ESValue.wrap(input).hasProperty("type")) {
            type = ESValue.wrap(input).getProperty("type").toNumber() as int32;
        }
        if (ESValue.wrap(input).hasProperty("id")) {
            id = ESValue.wrap(input).getProperty("id").toNumber() as long;
        }
        let resource = new ArkResource(id, type, bundleName, moduleName);
        resource.params = paramsArray;
        return resource;
    }
    static transferDynamic(input: Object): Any {
        if (input == null) {
            throw Error("The Resource is null, convert fail.");
        }
        if (input == undefined) {
            throw Error("The Resource is undefined, convert fail.");
        }
        let staticValue = input as ArkResource;
        if (staticValue == null) {
            throw Error("Not a Resource object, convert fail.");
        }
        if (staticValue == undefined) {
            throw Error("Not a Resource object, convert fail.");
        }
        let dynamicValue = ESValue.instantiateEmptyObject();
        const bundleName = ESValue.wrap(staticValue.bundleName);
        const moduleName = ESValue.wrap(staticValue.moduleName);
        const type = ESValue.wrap(staticValue.type);
        const id = ESValue.wrap(staticValue._id);
        let paramArr = staticValue.params as Array<Object | undefined>;
        let paramsArray = ESValue.instantiateEmptyArray();
        for (let i = 0;i < paramArr.length; i++) {
            paramsArray.setProperty(i, ESValue.wrap(paramArr[i]));
        }
        dynamicValue.setProperty("bundleName", bundleName);
        dynamicValue.setProperty("moduleName", moduleName);
        dynamicValue.setProperty("params", paramsArray);
        dynamicValue.setProperty("type", type);
        dynamicValue.setProperty("id", id);
        return dynamicValue.unwrap();
    }
}
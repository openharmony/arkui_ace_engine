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

import * as arkts from "@koalaui/libarkts"
import { ProjectConfig } from "./component-transformer";
import * as fs from "fs"
import * as path from "path"

export const RESOURCE_TYPE: Record<string, number> = {
    color: 10001,
    float: 10002,
    string: 10003,
    plural: 10004,
    boolean: 10005,
    intarray: 10006,
    integer: 10007,
    pattern: 10008,
    strarray: 10009,
    media: 20000,
    rawfile: 30000,
    symbol: 40000,
};

export enum ModuleType {
    HAR = 'har',
    ENTRY = 'entry',
    FEATURE = 'feature',
    SHARED = 'shared',
}

export enum Dollars {
    DOLLAR_RESOURCE = '$r',
    DOLLAR_RAWFILE = '$rawfile',
    DOLLAR_DOLLAR = '$$',
    TRANSFORM_DOLLAR_RESOURCE = '_r',
    TRANSFORM_DOLLAR_RAWFILE = '_rawfile',
}

type ResourceMap = Map<string, Record<string, number>>;

export interface ResourceList {
    [key: string]: ResourceMap;
}

export interface ResourceInfo {
    resourcesList: ResourceList;
    rawfile: Set<string>;
}

export interface LoaderJson {
    hspResourcesMap: Record<string, string>;
}

export interface ResourceParameter {
    id: number;
    type: number;
    params: arkts.Expression[];
}

export function getResourceParams(id: number, type: number, params: arkts.Expression[]): ResourceParameter {
    return { id, type, params };
}

export function loadBuildJson(projectConfig: ProjectConfig | undefined): any {
    if (!!projectConfig && projectConfig.buildLoaderJson && fs.existsSync(projectConfig.buildLoaderJson)) {
        try {
            const content = fs.readFileSync(projectConfig.buildLoaderJson, 'utf-8');
            const parsedContent = JSON.parse(content);
            return parsedContent;
        } catch (error) {
            throw new Error('Error: The file is not a valid JSON format.');
        }
    }
    return {};
}

export function initResourceInfo(projectConfig: ProjectConfig | undefined, aceBuildJson: LoaderJson): ResourceInfo {
    let resourcesList: ResourceList = {
        app: new Map<string, Record<string, number>>(),
        sys: new Map<string, Record<string, number>>(),
    };
    let rawfile: Set<string> = new Set<string>();
    if (!!projectConfig) {
        readAppResource(resourcesList, projectConfig, aceBuildJson, rawfile);
    }
    return { resourcesList, rawfile };
}

function readAppResource(
    resourcesList: ResourceList,
    projectConfig: ProjectConfig,
    aceBuildJson: LoaderJson,
    rawfile: Set<string>
): void {
    if ('hspResourcesMap' in aceBuildJson && aceBuildJson.hspResourcesMap) {
        readHspResource(aceBuildJson, projectConfig, resourcesList);
    }
    readSystemResource(resourcesList);
    if (!!projectConfig.appResource && fs.existsSync(projectConfig.appResource)) {
        const appResource: string = fs.readFileSync(projectConfig.appResource, 'utf-8');
        const resourceArr: string[] = appResource.split(/\n/);
        const resourceMap: ResourceMap = new Map<string, Record<string, number>>();
        processResourceArr(resourceArr, resourceMap, projectConfig.appResource);
        for (let [key, value] of resourceMap) {
            resourcesList.app.set(key, value);
        }
    }
    if (projectConfig.rawFileResource) {
        processResourcesRawfile(projectConfig, projectConfig.rawFileResource, rawfile);
    }
}

function readSystemResource(resourcesList: ResourceList): void {
    const sysResourcePath = path.resolve(__dirname, '../sysResource.js');
    if (fs.existsSync(sysResourcePath)) {
        const sysObj: Record<string, Record<string, number>> = require(sysResourcePath).sys;
        Object.keys(sysObj).forEach((key: string) => {
            resourcesList.sys.set(key, sysObj[key]);
        });
    }
}

function processResourceArr(
    resourceArr: string[],
    resourceMap: Map<string, Record<string, number>>,
    resourcePath: string
): void {
    for (let i = 0; i < resourceArr.length; i++) {
        if (!resourceArr[i].length) {
            continue;
        }
        const resourceData = resourceArr[i].split(/\s/);
        if (resourceData.length === 3 && !isNaN(Number(resourceData[2]))) {
            rescordResourceNameAndIdMap(resourceMap, resourceData);
        } else {
            console.warn(`ArkTS:WARN The format of file '${resourcePath}' is incorrect.`);
            break;
        }
    }
}

function rescordResourceNameAndIdMap(resourceMap: Map<string, Record<string, number>>, resourceData: string[]): void {
    if (resourceMap.get(resourceData[0])) {
        const resourceNameAndId: Record<string, number> = resourceMap.get(resourceData[0])!;
        if (!resourceNameAndId[resourceData[1]] || resourceNameAndId[resourceData[1]] !== Number(resourceData[2])) {
            resourceNameAndId[resourceData[1]] = Number(resourceData[2]);
        }
    } else {
        let obj: Record<string, number> = {};
        obj[resourceData[1]] = Number(resourceData[2]);
        resourceMap.set(resourceData[0], obj);
    }
}

function readHspResource(aceBuildJson: LoaderJson, projectConfig: ProjectConfig, resourcesList: ResourceList): void {
    projectConfig.hspResourcesMap = true;
    for (const hspName in aceBuildJson.hspResourcesMap) {
        if (fs.existsSync(aceBuildJson.hspResourcesMap[hspName])) {
            const resourceMap: ResourceMap = new Map<string, Record<string, number>>();
            resourcesList[hspName] = new Map<string, Record<string, number>>();
            const hspResource: string = fs.readFileSync(aceBuildJson.hspResourcesMap[hspName], 'utf-8');
            const resourceArr: string[] = hspResource.split(/\n/);
            processResourceArr(resourceArr, resourceMap, aceBuildJson.hspResourcesMap[hspName]);
            for (const [key, value] of resourceMap) {
                resourcesList[hspName].set(key, value);
            }
        }
    }
}

function processResourcesRawfile(
    projectConfig: ProjectConfig,
    rawfilePath: string,
    rawfileSet: Set<string>,
    resourceName: string = ''
): void {
    if (fs.existsSync(projectConfig.rawFileResource) && fs.statSync(rawfilePath).isDirectory()) {
        const files: string[] = fs.readdirSync(rawfilePath);
        files.forEach((file: string) => {
            if (fs.statSync(path.join(rawfilePath, file)).isDirectory()) {
                processResourcesRawfile(
                    projectConfig,
                    path.join(rawfilePath, file),
                    rawfileSet,
                    resourceName ? resourceName + '/' + file : file
                );
            } else {
                addRawfileResourceToSet(rawfileSet, file, resourceName);
            }
        });
    }
}

function addRawfileResourceToSet(rawfileSet: Set<string>, file: string, resourceName: string = ''): void {
    if (resourceName) {
        rawfileSet.add(resourceName + '/' + file);
    } else {
        rawfileSet.add(file);
    }
}
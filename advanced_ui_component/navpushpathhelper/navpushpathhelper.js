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
 */

const navPushPathHelperApi = requireInternal('atomicservice.NavPushPathHelper');
const hilog = requireNapi('hilog');

const tag = 'NavPushPathHelper::JS::';

export class NavPushPathHelper {
    static currentID = 0;
    constructor(navPathStack) {
        this.navPathStack_ = navPathStack;
        this.currentHelperId_ = NavPushPathHelper.currentID;
        NavPushPathHelper.currentID++;
    }

    async pushPath(moduleName, info, optionParam) {
        hilog.info(0x3900, tag, `pushPath -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, info.name)) {
            this.navPathStack_?.pushPath(info, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.pushPath(info, optionParam);
                resolve();
            },
            (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }

    async pushDestination(moduleName, info, optionParam) {
        hilog.info(0x3900, tag, `pushDestination -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, info.name)) {
            await this.navPathStack_?.pushDestination(info, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.pushDestination(info, optionParam)
                .then(resolve).catch(reject);
            }, (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }

    async pushPathByName(moduleName, name, param, onPop, optionParam) {
        hilog.info(0x3900, tag, `pushPathByName -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, name)) {
            this.navPathStack_?.pushPathByName(name, param, onPop, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.pushPathByName(name, param, onPop, optionParam);
                resolve();
            }, (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }

    async pushDestinationByName(moduleName, name, param, onPop, optionParam) {
        hilog.info(0x3900, tag, `pushDestinationByName -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, name)) {
            await this.navPathStack_?.pushDestinationByName(name, param, onPop, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.pushDestinationByName(name, param, onPop, optionParam)
                .then(resolve).catch(reject);
            }, (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }

    async replacePath(moduleName, info, optionParam) {
        hilog.info(0x3900, tag, `replacePath -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, info.name)) {
            this.navPathStack_?.replacePath(info, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.replacePath(info, optionParam);
                resolve();
            }, (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }

    async replacePathByName(moduleName, name, param, optionParam) {
        hilog.info(0x3900, tag, `replacePathByName -> currentID: ${this.currentHelperId_}`);
        if (navPushPathHelperApi.isHspExist(moduleName, name)) {
            this.navPathStack_?.replacePathByName(name, param, optionParam);
            return;
        }
        return new Promise((resolve, reject) => {
            navPushPathHelperApi.silentInstall(moduleName, () => {
                hilog.info(0x3900, tag, `silentInstall success`);
                navPushPathHelperApi.initRouteMap();
                this.navPathStack_?.replacePathByName(name, param, optionParam);
                resolve();
            }, (error) => {
                const err = new Error(error.message);
                err.code = error.code;
                reject(err);
            });
        });
    }
}

export default { NavPushPathHelper };
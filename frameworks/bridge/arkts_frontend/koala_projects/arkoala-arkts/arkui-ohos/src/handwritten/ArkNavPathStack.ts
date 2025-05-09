/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

import {KPointer, toPeerPtr, runtimeType, RuntimeType, Finalizable} from '@koalaui/interop'
import { int32 } from "@koalaui/common"
import { LaunchMode, NavPathInfo, NavPathStack, NavigationOptions, PopInfo } from "../component/navigation"
import { NavExtender } from "../component/navigationExtender"
import { ArkUIGeneratedNativeModule } from "#components"

export class PathStackUtils {
    static id: number = 0
    static result: object | undefined = undefined
    private static infoMaps: Map<string, NavPathInfo> = new Map<string, NavPathInfo>()
    static addNavPathInfo(info: NavPathInfo): void {
        const navDestinationId: string = "" + PathStackUtils.id
        info.navDestinationId = navDestinationId
        PathStackUtils.infoMaps.set(navDestinationId, info)
    }
    static getNavPathInfoById(navDestinationId: string): NavPathInfo | undefined {
        if (PathStackUtils.infoMaps.has(navDestinationId)) {
            return PathStackUtils.infoMaps.get(navDestinationId)
        }
        return undefined
    }
    static pushPath(pathStack: NavPathStack, info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const animated_type = runtimeType(animated)
        let options: NavigationOptions = {animated: true, launchMode: LaunchMode.STANDARD}
        if (animated_type === RuntimeType.BOOLEAN) {
            options.animated = animated as boolean
        } else if (animated_type !== RuntimeType.UNDEFINED) {
            options = animated as NavigationOptions
        }
        PathStackUtils.addNavPathInfo(info)
        NavExtender.pushPath(pathStack, info, options)
    }

    static pushPathByName(pathStack: NavPathStack, name: string, param: Object | object | undefined, onPop?: ((parameter: PopInfo) => void) | boolean | undefined, animated?: boolean): void {
        if (RuntimeType.BOOLEAN == runtimeType(onPop) || RuntimeType.UNDEFINED == runtimeType(onPop)) {
            const animate_cast = onPop as (boolean | undefined)
            let pathInfo: NavPathInfo = new NavPathInfo(name, param)
            PathStackUtils.pushPath(pathStack, pathInfo, animate_cast)
            return
        }
        let onPop_casted = onPop as ((parameter: PopInfo) => void)
        let pathInfo: NavPathInfo = new NavPathInfo(name, param, onPop_casted, false)
        PathStackUtils.pushPath(pathStack, pathInfo, animated)
    }

    static replacePath(pathStack: NavPathStack, info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const animated_type = runtimeType(animated)
        PathStackUtils.addNavPathInfo(info)
        let options: NavigationOptions = {animated: true, launchMode: LaunchMode.STANDARD}
        if (animated_type === RuntimeType.BOOLEAN) {
            options.animated = animated as boolean
        } else if (animated_type !== RuntimeType.UNDEFINED) {
            options = animated as NavigationOptions
        }
        NavExtender.replacePath(pathStack, info, options)
    }

    static replacePathByName(pathStack: NavPathStack, name: string, param: Object, animated?: boolean): void {
        let pathInfo: NavPathInfo = new NavPathInfo(name, param)
        PathStackUtils.replacePath(pathStack, pathInfo, animated)
    }

    static pop(pathStack: NavPathStack, result?: boolean | undefined | Object, animated?: boolean): NavPathInfo | undefined
    {
        const result_type = runtimeType(result)
        if (result_type === RuntimeType.OBJECT) {
            PathStackUtils.result = result as Object
        }
        const animated_type = runtimeType(animated)
        let animated_value: boolean = true
        if (RuntimeType.BOOLEAN == result_type) {
            animated_value = result as (boolean)
        }
        if (animated_type !== RuntimeType.BOOLEAN) {
            animated_value = animated!
        }
        const retval  = NavExtender.pop(pathStack, animated_value)
        return PathStackUtils.getNavPathInfoById(retval)
    }
    static getParamByIndex(pathStack: NavPathStack, index: number): Object | undefined {
        const navDestinationId: string = NavExtender.getIdByIndex(pathStack, index as (int32));
        let pathInfo = PathStackUtils.getNavPathInfoById(navDestinationId)
        return pathInfo?.param
    }
    static getParamByName(pathStack: NavPathStack, name: string): Array<object | undefined> {
        let result: Array<Object | undefined> = new Array<Object | undefined>()
        let ids = NavExtender.getIdByName(pathStack, name)
        for (let index: number = 0; index < ids.length; index++) {
            if (!PathStackUtils.infoMaps.has(ids[index])) {
                result.push(undefined)
                continue
            }
            let info = PathStackUtils.infoMaps.get(ids[index])
            if (info && info.param) {
                result.push(info!.param!)
            }
        }
        return result
    }
}
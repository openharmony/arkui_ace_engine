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

import {KPointer, toPeerPtr, runtimeType, RuntimeType, Finalizable, InteropNativeModule} from '@koalaui/interop'
import { int32 } from "@koalaui/common"
import { LaunchMode, NavPathInfo, NavPathStack, NavigationOptions, PopInfo } from "../component/navigation"
import { NavExtender } from "../component/navigationExtender"
import { ArkUIGeneratedNativeModule } from "#components"

export class PathStackUtils {
    static id: number = 0
    static result: object | undefined = undefined
    private static infoMaps: Map<string, NavPathInfo> = new Map<string, NavPathInfo>()
    private static infoArray: Array<NavPathInfo> = new Array<NavPathInfo>()
    static addNavPathInfo(info: NavPathInfo, launchMode: LaunchMode, isReplace: boolean = false): void {
        if (launchMode === LaunchMode.MOVE_TO_TOP_SINGLETON) {
            let index = PathStackUtils.infoArray.findIndex(element => element.name === info.name)
            if (index != -1) {
                PathStackUtils.infoArray[index] = info
                let targetInfo = PathStackUtils.infoArray.splice(index, 1)
                if (isReplace) {
                    let popInfo = PathStackUtils.infoArray.pop()
                    if (popInfo !== undefined && popInfo!.navDestinationId != undefined) {
                        PathStackUtils.infoMaps.delete(popInfo?.navDestinationId!)
                    }
                }
                PathStackUtils.infoArray.push(targetInfo[0])
            }
            return
        } else if (launchMode === LaunchMode.POP_TO_SINGLETON) {
            let index = PathStackUtils.infoArray.findIndex(element => element.name === info.name)
            if (index != -1) {
                PathStackUtils.infoArray[index] = info
                if (isReplace) {
                    let targetInfo = PathStackUtils.infoArray.splice(index, 1)
                    let deletedInfos = PathStackUtils.infoArray.splice(index)
                    deletedInfos.forEach((element) => {
                        if (element.navDestinationId != undefined) {
                            PathStackUtils.infoMaps.delete(element.navDestinationId!)
                        }
                    })
                    PathStackUtils.infoArray.push(targetInfo[0])
                } else {
                    let deletedInfos = PathStackUtils.infoArray.splice(index + 1)
                    deletedInfos.forEach((element) => {
                        if (element.navDestinationId != undefined) {
                            PathStackUtils.infoMaps.delete(element.navDestinationId!)
                        }
                    })
                }
            }
            return
        }
        const navDestinationId: string = "" + PathStackUtils.id
        info.navDestinationId = navDestinationId
        if (isReplace) {
            let popInfo = PathStackUtils.infoArray.pop()
            if (popInfo !== undefined) {
                let prenavDestinationId = popInfo.navDestinationId
                if (prenavDestinationId !== undefined && PathStackUtils.infoMaps.has(prenavDestinationId)) {
                    PathStackUtils.infoMaps.delete(prenavDestinationId!)
                }
            }
        }
        PathStackUtils.infoMaps.set(navDestinationId, info)
        PathStackUtils.infoArray.push(info)
        PathStackUtils.id++;
        info.updateNavPathInfo()
    }
    static getNavPathInfoById(navDestinationId: string): NavPathInfo | undefined {
        if (PathStackUtils.infoMaps.has(navDestinationId)) {
            return PathStackUtils.infoMaps.get(navDestinationId)
        }
        return undefined
    }
    static popPage(indexOrId?: number | string) {
        try {
            let id: string | undefined = ''
            if (typeof indexOrId === 'string') {
                id = indexOrId as string
                let navId = indexOrId as string
                let index = PathStackUtils.infoArray.findIndex(element => element.navDestinationId === navId)
                if (index != -1) {
                    PathStackUtils.infoArray.splice(index, 1)
                }
            } else if (typeof indexOrId === 'number') {
                let inputIndex = indexOrId as number;
                if (inputIndex < 0 || inputIndex >= PathStackUtils.infoArray.length) {
                    return;
                }
                id = PathStackUtils.infoArray[PathStackUtils.infoArray.length - 1].navDestinationId;
                let removeArray = PathStackUtils.infoArray.splice(inputIndex + 1);
                removeArray.forEach((element) => {
                    if (element.navDestinationId != undefined && element.navDestinationId == id) {
                        PathStackUtils.infoMaps.delete(element.navDestinationId!)
                    }
                })
            } else {
                indexOrId = PathStackUtils.infoArray.length - 1
                id = PathStackUtils.infoArray[PathStackUtils.infoArray.length - 1].navDestinationId
                PathStackUtils.infoArray.splice(PathStackUtils.infoArray.length - 1, 1)
            }
            if (typeof id === 'string') {
                PathStackUtils.callOnPop(id!)
            }
        } catch (error) {
            InteropNativeModule._NativeLog("AceNavigation::popPage error: " + error)
        }
        
    }
    static callOnPop(navDestinationId: string) {
        try {
            if (PathStackUtils.infoMaps.has(navDestinationId)) {
                let info = PathStackUtils.infoMaps.get(navDestinationId)
                if (info != undefined) {
                    let callback = info!.onPop
                    if (callback != undefined && info != undefined && PathStackUtils.result != undefined) {
                        let popInfo: PopInfo = { info: info, result: PathStackUtils.result!}
                        callback(popInfo)
                    }
                }
                PathStackUtils.infoMaps.delete(navDestinationId)
            }
        } catch (error) {
            InteropNativeModule._NativeLog("AceNavigation::callOnPop error:" + error)
        }
    }
    static pushPath(pathStack: NavPathStack, info: NavPathInfo, animated?: boolean | undefined | NavigationOptions | undefined): void {
        const animated_type = runtimeType(animated)
        let options: NavigationOptions = {animated: true, launchMode: LaunchMode.STANDARD}
        if (animated_type === RuntimeType.BOOLEAN) {
            options.animated = animated as boolean
        } else if (animated_type !== RuntimeType.UNDEFINED) {
            let userSetOptions = animated as NavigationOptions
            if (runtimeType(userSetOptions.animated) !== RuntimeType.UNDEFINED) {
                options.animated = userSetOptions.animated
            }
            if (runtimeType(userSetOptions.launchMode) !== RuntimeType.UNDEFINED) {
                options.launchMode = userSetOptions.launchMode
            }
        }
        PathStackUtils.addNavPathInfo(info, options.launchMode!)
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
        let options: NavigationOptions = {animated: true, launchMode: LaunchMode.STANDARD}
        if (animated_type === RuntimeType.BOOLEAN) {
            options.animated = animated as boolean
        } else if (animated_type !== RuntimeType.UNDEFINED) {
            let userSetOptions = animated as NavigationOptions
            if (runtimeType(userSetOptions.animated) != RuntimeType.UNDEFINED) {
                options.animated = userSetOptions.animated
            }
            if (runtimeType(userSetOptions.launchMode) != RuntimeType.UNDEFINED) {
                options.launchMode = userSetOptions.launchMode
            }
        }
        PathStackUtils.addNavPathInfo(info, options.launchMode!, true)
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
        if (animated_type === RuntimeType.BOOLEAN) {
            animated_value = animated!
        }
        const retval  = NavExtender.pop(pathStack, animated_value)
        const pathInfo = PathStackUtils.getNavPathInfoById(retval)
        PathStackUtils.popPage(retval)
        return pathInfo
    }
    static getParamByIndex(pathStack: NavPathStack, index: number): Object | undefined {
        const navDestinationId: string = NavExtender.getIdByIndex(pathStack, index as (int32));
        let pathInfo = PathStackUtils.getNavPathInfoById(navDestinationId)
        if (pathInfo?.param === null) {
            return undefined
        }
        return pathInfo?.param as Object | undefined
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
    static popToIndex(pathStack: NavPathStack, index: number, result?: boolean | undefined | Object, animated?: boolean) {
        const result_type = runtimeType(result)
        if (result_type == RuntimeType.OBJECT) {
            PathStackUtils.result = result as Object
        }
        let animated_value: boolean = true
        if (RuntimeType.BOOLEAN === result_type) {
            animated_value = result as boolean
        }
        if (RuntimeType.BOOLEAN === runtimeType(animated)) {
            animated_value = animated as boolean
        }
        const index_casted = index as int32
        PathStackUtils.popPage(index_casted)
        NavExtender.popToIndex(pathStack, index_casted, animated_value)
    }
    static popToName(pathStack: NavPathStack, name: string, result?: boolean | undefined | Object, animated?: boolean): number {
        const result_type = runtimeType(result)
        if (result_type == RuntimeType.OBJECT) {
            PathStackUtils.result = result as Object
        }
        let animated_value: boolean = true
        if (result_type === RuntimeType.BOOLEAN) {
            animated_value = result as boolean
        }
        if (RuntimeType.BOOLEAN === runtimeType(animated)) {
            animated_value = animated as boolean
        }
        let index = NavExtender.popToName(pathStack, name, animated_value)
        PathStackUtils.popPage(index)
        return index
    }
}
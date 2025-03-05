/*
 * Copyright (c) 2024-2025 Huawei Device Co., Ltd.
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


// WARNING! THIS FILE IS AUTO-GENERATED, DO NOT MAKE CHANGES, THEY WILL BE LOST ON NEXT GENERATION!

import { GlobalScope_common } from "./ArkGlobalScopeCommonMaterialized"
import { ICurve } from "./ArkICurveMaterialized"
import { GlobalScope_inspector } from "./ArkGlobalScopeInspectorMaterialized"
export function getContext(component: Object): Context {
    return GlobalScope_common.getContext(component)
}
export function postCardAction(component: Object, action: Object): void {
    GlobalScope_common.postCardAction(component, action)
}
export function dollar_r(value: string, params: Array<any>): Resource {
    return GlobalScope_common.dollar_r(value, params)
}
export function dollar_rawfile(value: string): Resource {
    return GlobalScope_common.dollar_rawfile(value)
}
export function animateTo(value: AnimateParam, event: (() => void)): void {
    GlobalScope_common.animateTo(value, event)
}
export function animateToImmediately(value: AnimateParam, event: (() => void)): void {
    GlobalScope_common.animateToImmediately(value, event)
}
export function vp2px(value: number): number {
    return GlobalScope_common.vp2px(value)
}
export function px2vp(value: number): number {
    return GlobalScope_common.px2vp(value)
}
export function fp2px(value: number): number {
    return GlobalScope_common.fp2px(value)
}
export function px2fp(value: number): number {
    return GlobalScope_common.px2fp(value)
}
export function lpx2px(value: number): number {
    return GlobalScope_common.lpx2px(value)
}
export function px2lpx(value: number): number {
    return GlobalScope_common.px2lpx(value)
}
export function getInspectorNodes(): Object {
    return GlobalScope_inspector.getInspectorNodes()
}
export function getInspectorNodeById(id: number): Object {
    return GlobalScope_inspector.getInspectorNodeById(id)
}
export function setAppBgColor(value: string): void {
    GlobalScope_inspector.setAppBgColor(value)
}

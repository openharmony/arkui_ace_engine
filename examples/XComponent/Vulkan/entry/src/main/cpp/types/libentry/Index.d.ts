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

export const setResourceManager: (rmgr: ESObject) => number;
export const YawPitchTo: (x: number, y: number) => number;
export const getYaw:() => number;
export const getPitch:() => number;
export const windowSizeChange: (width: number, height: number, orientation: number) => void;
export const dispatchController: (x: number, y: number, size: number, op: number) => number;
export class vec3 {x: number; y: number; z: number}
export const getFront: ()=>vec3;

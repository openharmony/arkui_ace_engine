/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

declare interface Size {
    width: number;
    height: number;
}

declare interface SizeInVp {
    widthVp: number;
    heightVp: number;
}

// WindowSizePxEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowSizePxEnv implements IEnvironmentValue<Size> {
    constructor(context: UIContext);
    value: Size;
    update(newValue: Size);
    destroy(): void;
}

// WindowSizeVpEnv decorated by @ObservedV2 used in Env.
// Provided by Platform Environment Provider.
declare class WindowSizeVpEnv implements IEnvironmentValue<SizeInVp> {
    constructor(context: UIContext);
    value: SizeInVp;
    update(newValue: SizeInVp);
    destroy(): void;
}
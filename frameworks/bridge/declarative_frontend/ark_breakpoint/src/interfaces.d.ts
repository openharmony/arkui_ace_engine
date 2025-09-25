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

declare enum WidthBreakpoint {
  WIDTH_XS = 0,
  WIDTH_SM = 1,
  WIDTH_MD = 2,
  WIDTH_LG = 3,
  WIDTH_XL = 4,
}

declare enum HeightBreakpoint {
  HEIGHT_SM = 0,
  HEIGHT_MD = 1,
  HEIGHT_LG = 2,
}

declare class WindowSizeLayoutBreakpointInfo {
    widthBreakpoint: WidthBreakpoint;
    heightBreakpoint: HeightBreakpoint;
}

declare type BreakpointCallback = (breakPoint: WindowSizeLayoutBreakpointInfo) => void;

declare class UIObserver {
    on(type: 'windowSizeLayoutBreakpointChange', callback: BreakpointCallback): void;
    off(type: 'windowSizeLayoutBreakpointChange', callback?: BreakpointCallback): void;
}

declare class UIContext {
    getUIObserver(): UIObserver;
}


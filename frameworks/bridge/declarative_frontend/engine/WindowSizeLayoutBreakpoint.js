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
var __decorate = (this && this.__decorate) || function (decorators, target, key, desc) {
    var c = arguments.length, r = c < 3 ? target : desc === null ? desc = Object.getOwnPropertyDescriptor(target, key) : desc, d;
    if (typeof Reflect === "object" && typeof Reflect.decorate === "function") r = Reflect.decorate(decorators, target, key, desc);
    else for (var i = decorators.length - 1; i >= 0; i--) if (d = decorators[i]) r = (c < 3 ? d(r) : c > 3 ? d(target, key, r) : d(target, key)) || r;
    return c > 3 && r && Object.defineProperty(target, key, r), r;
};
let WindowSizeLayoutBreakpoint = class WindowSizeLayoutBreakpoint {
    constructor(context) {
        this.breakPointCallback = (breakPoint) => {
            this.update(breakPoint);
        };
        this.uiContext = context;
        this.uiObserver = this.uiContext.getUIObserver();
        this.widthBreakpoint = this.uiContext.getWindowWidthBreakpoint();
        this.heightBreakpoint = this.uiContext.getWindowHeightBreakpoint();
        if (this.uiObserver && typeof this.uiObserver.on === 'function') {
            this.uiObserver.on('windowSizeLayoutBreakpointChange', this.breakPointCallback);
        }
        else {
            aceConsole.warn("Failed to register window size change listener");
        }
    }
    get value() {
        const windowSizeLayoutBreakpointInfo = new uiObserver.WindowSizeLayoutBreakpointInfo();
        windowSizeLayoutBreakpointInfo.widthBreakpoint = this.widthBreakpoint;
        windowSizeLayoutBreakpointInfo.heightBreakpoint = this.heightBreakpoint;
        return windowSizeLayoutBreakpointInfo;
    }
    update(payload) {
        this.widthBreakpoint = payload.widthBreakpoint;
        this.heightBreakpoint = payload.heightBreakpoint;
    }
    destroy() {
        if (this.uiObserver && typeof this.uiObserver.off === 'function') {
            this.uiObserver.off('windowSizeLayoutBreakpointChange', this.breakPointCallback);
        }
        else {
            aceConsole.warn("Failed to unregister window size change listener");
        }
    }
};
__decorate([
    Trace
], WindowSizeLayoutBreakpoint.prototype, "widthBreakpoint", void 0);
__decorate([
    Trace
], WindowSizeLayoutBreakpoint.prototype, "heightBreakpoint", void 0);
WindowSizeLayoutBreakpoint = __decorate([
    ObservedV2
], WindowSizeLayoutBreakpoint);
export default {
    WindowSizeLayoutBreakpoint,
};

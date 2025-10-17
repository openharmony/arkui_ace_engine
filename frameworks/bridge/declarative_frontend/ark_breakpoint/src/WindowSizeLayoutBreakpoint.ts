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

/// <reference path="../../state_mgmt/src/lib/common/ace_console.native.d.ts" />
type ConstructorV2 = {
    new (...args: any[]): any;
};
declare function ObservedV2<T extends ConstructorV2>(BaseClass: T): T;
interface IEnvironmentValue<T> {
  value: T;
  update(newValue: T): void;
  destroy(): void;
}
declare const Trace: (target: Object, propertyKey: string) => void;

@ObservedV2
class WindowSizeLayoutBreakpoint implements IEnvironmentValue<uiObserver.WindowSizeLayoutBreakpointInfo> {
  @Trace public widthBreakpoint: WidthBreakpoint;
  @Trace public heightBreakpoint: HeightBreakpoint;
  public uiContext: UIContext;
  public uiObserver: UIObserver;

  private breakPointCallback= (breakPoint: uiObserver.WindowSizeLayoutBreakpointInfo): void => {
    this.update(breakPoint);
  };

  constructor(context: UIContext) {
    this.uiContext = context;
    this.uiObserver = this.uiContext.getUIObserver();
    this.widthBreakpoint = this.uiContext.getWindowWidthBreakpoint();
    this.heightBreakpoint = this.uiContext.getWindowHeightBreakpoint();
    if (this.uiObserver && typeof this.uiObserver.on === 'function') {
      this.uiObserver.on('windowSizeLayoutBreakpointChange', this.breakPointCallback);
    } else {
        aceConsole.warn('Failed to register window size change listener');
    }
  }

  get value(): uiObserver.WindowSizeLayoutBreakpointInfo {
    const windowSizeLayoutBreakpointInfo = new uiObserver.WindowSizeLayoutBreakpointInfo();
    windowSizeLayoutBreakpointInfo.widthBreakpoint = this.widthBreakpoint;
    windowSizeLayoutBreakpointInfo.heightBreakpoint = this.heightBreakpoint;
    return windowSizeLayoutBreakpointInfo;
  }

  update(payload: uiObserver.WindowSizeLayoutBreakpointInfo): void {
    this.widthBreakpoint = payload.widthBreakpoint;
    this.heightBreakpoint = payload.heightBreakpoint;
  }

  destroy(): void {
    if (this.uiObserver && typeof this.uiObserver.off === 'function') {
      this.uiObserver.off('windowSizeLayoutBreakpointChange', this.breakPointCallback);
    } else {
        aceConsole.warn('Failed to unregister window size change listener');
    }
  }
}
export default {
  WindowSizeLayoutBreakpoint,
}
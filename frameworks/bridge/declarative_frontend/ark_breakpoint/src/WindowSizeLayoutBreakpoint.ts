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

///<reference path="./interfaces.d.ts" />

export class WindowSizeLayoutBreakpoint implements WindowSizeLayoutBreakpointInfo {
  public widthBreakpoint: WidthBreakpoint;
  public heightBreakpoint: HeightBreakpoint;
  public uiContext: UIContext;
  public uiObserver: UIObserver;

  private breakPointCallback= (breakPoint: WindowSizeLayoutBreakpointInfo) => {
    this.update(breakPoint);
  };

  constructor(context: UIContext) {
    this.widthBreakpoint = WidthBreakpoint.WIDTH_MD;
    this.heightBreakpoint = HeightBreakpoint.HEIGHT_MD;
    this.uiContext = context;
    this.uiObserver = this.uiContext.getUIObserver();
    if (this.uiObserver && typeof this.uiObserver.on === 'function') {
      this.uiObserver.on('windowSizeLayoutBreakpointChange', this.breakPointCallback);
    }
  }

  get value(): WindowSizeLayoutBreakpointInfo {
    return {
      widthBreakpoint: this.widthBreakpoint,
      heightBreakpoint: this.heightBreakpoint
    };
  }

  update(payload: WindowSizeLayoutBreakpointInfo) {
    this.widthBreakpoint = payload.widthBreakpoint;
    this.heightBreakpoint = payload.heightBreakpoint;
  }

  destroy(): void {
    if (this.uiObserver && typeof this.uiObserver.off === 'function') {
      this.uiObserver.off('windowSizeLayoutBreakpointChange', this.breakPointCallback);
    }
  }
}
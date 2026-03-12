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

export class WaterFlowControllerStore {
  private static dynamicScroller: Scroller | undefined = undefined;
  private static lastResult: string = 'No controller call yet';
  private static navigationMode: string = 'push';

  static setScroller(scroller: Scroller): void {
    WaterFlowControllerStore.dynamicScroller = scroller;
  }

  static setResult(result: string): void {
    WaterFlowControllerStore.lastResult = result;
  }

  static getResult(): string {
    return WaterFlowControllerStore.lastResult;
  }

  static setNavigationMode(mode: string): void {
    WaterFlowControllerStore.navigationMode = mode;
  }

  static getNavigationMode(): string {
    return WaterFlowControllerStore.navigationMode;
  }

  static callScrollBy(): string {
    return WaterFlowControllerStore.invoke('scrollBy(+120)', () => {
      WaterFlowControllerStore.dynamicScroller?.scrollBy(0, 120);
    });
  }

  static callScrollTop(): string {
    return WaterFlowControllerStore.invoke('scrollTop', () => {
      WaterFlowControllerStore.dynamicScroller?.scrollEdge(Edge.Top);
    });
  }

  static callScrollBottom(): string {
    return WaterFlowControllerStore.invoke('scrollBottom', () => {
      WaterFlowControllerStore.dynamicScroller?.scrollEdge(Edge.Bottom);
    });
  }

  static callReadOffset(): string {
    return WaterFlowControllerStore.invoke('readOffset', () => {
      const offset = WaterFlowControllerStore.dynamicScroller?.currentOffset()?.yOffset ?? 0;
      WaterFlowControllerStore.lastResult = `readOffset success: yOffset=${offset}`;
    });
  }

  private static invoke(action: string, callback: () => void): string {
    if (!WaterFlowControllerStore.dynamicScroller) {
      WaterFlowControllerStore.lastResult = `${action} failed: controller is null`;
      return WaterFlowControllerStore.lastResult;
    }
    try {
      callback();
      if (!WaterFlowControllerStore.lastResult.startsWith(action)) {
        WaterFlowControllerStore.lastResult = `${action} success`;
      }
    } catch (e) {
      WaterFlowControllerStore.lastResult = `${action} failed: code=${e.code}, msg=${e.message}`;
    }
    return WaterFlowControllerStore.lastResult;
  }
}
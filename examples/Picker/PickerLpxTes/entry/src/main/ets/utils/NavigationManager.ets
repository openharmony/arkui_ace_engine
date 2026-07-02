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

export class NavigationManager {
  private static sInstance: NavigationManager;

  static getInstance(): NavigationManager {
    if (!NavigationManager.sInstance) {
      NavigationManager.sInstance = new NavigationManager();
    }
    return NavigationManager.sInstance;
  }

  private naviStack: NavPathStack;

  private constructor() {
    this.naviStack = new NavPathStack();
    this.saveStorage();
  }

  private saveStorage(): void {
    AppStorage.SetOrCreate("PathStack", this.naviStack);
  }

  private pushPage(name: string, params?: object, launchMode?: LaunchMode, isReplace: boolean = false): void {
    const naviInfo = new NavPathInfo(name, params);
    const option: NavigationOptions = {
      launchMode: launchMode || LaunchMode.POP_TO_SINGLETON
    };

    if (isReplace) {
      this.naviStack.replacePath(naviInfo, option);
    } else {
      this.naviStack.pushPath(naviInfo, option);
    }
  }

  pushDetailPage(name: string, params?: object, launchMode?: LaunchMode) {
    this.pushPage(name, params, launchMode, false);
  }

  pushFullPage(name: string, params?: object, launchMode?: LaunchMode) {
    this.pushPage(name, params, launchMode, false);
  }

  pop(animated?: boolean) {
    this.naviStack.pop(animated);
  }

  getNavPathStack(): NavPathStack {
    return this.naviStack;
  }
}
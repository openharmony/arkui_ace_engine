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
import { AbilityConstant, ConfigurationConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { display, window } from '@kit.ArkUI';
import { WindowUtils } from '../utils/WindowUtils'

const DOMAIN = 0x0000;
const TAG:string = 'EntryAbility';
export default class EntryAbility extends UIAbility {
  private currentBreakPoint:string = ''
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_NOT_SET);
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onCreate');
  }

  onDestroy(): void {
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageCreate');
    WindowUtils.window = windowStage.getMainWindowSync();
    WindowUtils.windowWidthPx = WindowUtils.window.getWindowProperties().windowRect.width;
    WindowUtils.windowHeightPx = WindowUtils.window.getWindowProperties().windowRect.height;

    this.updateBreakpoint(WindowUtils.windowWidthPx)
    let avoidArea = WindowUtils.window.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM);
    WindowUtils.topAvoidAreaHeightPx = avoidArea.topRect.height;

    let navigationArea = WindowUtils.window.getWindowAvoidArea(window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR);
    WindowUtils.navigationIndicatorHeightPx = navigationArea.bottomRect.height;

    try {
      WindowUtils.window.on('windowSizeChange', (data) => {
        WindowUtils.windowWidthPx = data.width;
        WindowUtils.windowHeightPx = data.height;
        this.updateBreakpoint(data.width);
        AppStorage.setOrCreate('windowSizeChanged', Date.now());
      })

      WindowUtils.window.on('avoidAreaChange', (data) => {
        if (data.type == window.AvoidAreaType.TYPE_SYSTEM) {
          let topRectHeight = data.area.topRect.height;
          WindowUtils.topAvoidAreaHeightPx = topRectHeight;
        } else if (data.type == window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR) {
          let bottomRectHeight = data.area.bottomRect.height;
          WindowUtils.navigationIndicatorHeightPx = bottomRectHeight;
        }
      })
    } catch (exception) {
      console.log('register failed ' + JSON.stringify(exception));
    }

    windowStage.loadContent('pages/Index', (err) => {
      if (err.code) {
        hilog.error(DOMAIN, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err));
        return;
      }
      hilog.info(DOMAIN, 'testTag', 'Succeeded in loading the content.');
    });
  }
  updateBreakpoint(width:number) {
    let windowWidthVp = width / (display.getDefaultDisplaySync().densityDPI / 160);
    let newBreakPoint:string = '';
    if (windowWidthVp < 400) {
      newBreakPoint = 'xs';
    } else if (windowWidthVp < 600) {
      newBreakPoint = 'sm';
    } else if (windowWidthVp < 800) {
      newBreakPoint = 'md';
    } else {
      newBreakPoint = 'lg';
    }
    if (this.currentBreakPoint !== newBreakPoint) {
      this.currentBreakPoint = newBreakPoint;
      AppStorage.setOrCreate('currentBreakpoint', this.currentBreakPoint);
    }
  }
  onWindowStageDestroy(): void {
    // Main window is destroyed, release UI related resources
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    // Ability has brought to foreground
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    // Ability has back to background
    hilog.info(DOMAIN, 'testTag', '%{public}s', 'Ability onBackground');
  }
}
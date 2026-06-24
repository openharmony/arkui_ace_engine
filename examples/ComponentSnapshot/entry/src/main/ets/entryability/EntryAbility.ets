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
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { window } from '@kit.ArkUI';
import { Logger } from '../common/Logger';

const TAG='EntryAbilityLogTag';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onCreate');
    try {
      this.context.getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_NOT_SET);
    } catch (err) {
      let error = err as BusinessError;
      Logger.error(TAG, `setColorMode err, code: ${error.code}, message: ${error.message}`);
    }
  }

  onDestroy(): void {
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    // Main window is created, set main page for this ability
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onWindowStageCreate');

    windowStage.loadContent('pages/Index', (err,data) => {
      if (err.code) {
        hilog.error(0x0000, 'testTag', 'Failed to load the content. Cause: %{public}s', JSON.stringify(err) ?? '');
        return;
      }
      hilog.info(0x0000, 'testTag', 'Succeeded in loading the content.');
      try {
        let uiContext:  UIContext | undefined = windowStage.getMainWindowSync().getUIContext()
        AppStorage.setOrCreate('uiContext', uiContext);
        this.initWindow(windowStage);
      } catch (err) {
        let error = err as BusinessError;
        Logger.error(TAG, `loadContent err, code: ${error.code}, message: ${error.message}`);
      }
    });
  }

  initWindow(windowStage: window.WindowStage) {
    try {
      let windowClass: window.Window = windowStage.getMainWindowSync();
      windowClass.setWindowLayoutFullScreen(true).catch((error: BusinessError) => {
        Logger.error(TAG, `setWindowLayoutFullScreen err, code: ${error.code}, message: ${error.message}`);
      });
      let naviBarArea: window.AvoidArea = windowClass.getWindowAvoidArea(
	window.AvoidAreaType.TYPE_NAVIGATION_INDICATOR);
      let area: window.AvoidArea = windowClass.getWindowAvoidArea(window.AvoidAreaType.TYPE_SYSTEM);
      const uiContext: UIContext | undefined = AppStorage.get('uiContext');
      AppStorage.setOrCreate<number>('naviIndicatorHeight',uiContext?.px2vp(naviBarArea.bottomRect.height));
      AppStorage.setOrCreate<number>('statusBarHeight', uiContext?.px2vp(area.topRect.height));

      let size = windowClass.getWindowProperties().windowRect;
      AppStorage.setOrCreate('screenHeight', uiContext?.px2vp(size.height));
      AppStorage.setOrCreate('screenWidth', uiContext?.px2vp(size.width));

      windowClass.on('windowSizeChange', data => {
        AppStorage.setOrCreate('screenHeight', uiContext?.px2vp(data.height));
        AppStorage.setOrCreate('screenWidth',uiContext?.px2vp(data.width));
      });
    } catch (err) {
      let error = err as BusinessError;
      Logger.error(TAG, `initWindow err, code: ${error.code}, message: ${error.message}`);
    }
  }

  onWindowStageDestroy(): void {
    // Main window is destroyed, release UI related resources
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    // Ability has brought to foreground
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    // Ability has back to background
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onBackground');
  }
}

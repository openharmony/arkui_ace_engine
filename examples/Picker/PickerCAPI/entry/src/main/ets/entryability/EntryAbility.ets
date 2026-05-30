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

import { AbilityConstant, UIAbility, Want } from '@kit.AbilityKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { window } from '@kit.ArkUI';

const HILOG_DOMAIN = 0x0000;
const HILOG_TAG = 'PickerCAPI';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onCreate');
  }

  onDestroy(): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onWindowStageCreate');
    windowStage.loadContent('pages/Index', (err) => {
      if (err.code) {
        hilog.error(HILOG_DOMAIN, HILOG_TAG,
          'Failed to load content. Cause: %{public}s',
          JSON.stringify(err));
        return;
      }
      hilog.info(HILOG_DOMAIN, HILOG_TAG, 'Succeeded in loading content.');
    });
  }

  onWindowStageDestroy(): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onWindowStageDestroy');
  }

  onForeground(): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onForeground');
  }

  onBackground(): void {
    hilog.info(HILOG_DOMAIN, HILOG_TAG, '%{public}s', 'Ability onBackground');
  }
}
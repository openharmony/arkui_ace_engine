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
import UIAbility from '@ohos.app.ability.UIAbility';
import window from '@ohos.window';
import Want from '@ohos.app.ability.Want';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';

export default class EntryAbility extends UIAbility {
  onCreate(want: Want, launchParam: AbilityConstant.LaunchParam): void {
    console.info('[ImageGenerationTest] EntryAbility onCreate');
  }

  onDestroy(): void {
    console.info('[ImageGenerationTest] EntryAbility onDestroy');
  }

  onWindowStageCreate(windowStage: window.WindowStage): void {
    console.info('[ImageGenerationTest] EntryAbility onWindowStageCreate');

    windowStage.loadContent('pages/Index', (err: Error, data: void) => {
      if (err) {
        console.error('[ImageGenerationTest] Failed to load content. Cause: ' + err.message);
        return;
      }
      console.info('[ImageGenerationTest] Succeeded in loading content');
    });
  }

  onWindowStageDestroy(): void {
    console.info('[ImageGenerationTest] EntryAbility onWindowStageDestroy');
  }

  onForeground(): void {
    console.info('[ImageGenerationTest] EntryAbility onForeground');
  }

  onBackground(): void {
    console.info('[ImageGenerationTest] EntryAbility onBackground');
  }
}
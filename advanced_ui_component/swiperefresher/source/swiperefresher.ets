/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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

import { LengthMetrics } from '@ohos.arkui.node';
import { common } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

const DEFAULT_MARGIN = 16
const ITEM_SPACE = 4
const MIN_SIZE = 24
const MID_SIZE = 40
const MAX_SIZE = 48
const MAX_FONT_SIZE = 2

@Component
export struct SwipeRefresher {
  @Prop
  content: string = '';
  @Prop
  isLoading: boolean = false;
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  minFontSize: number = 1.75;
  maxFontSize: number = 2;

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(0x3900, 'SwipeRefresher', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }

  build() {
    Flex({ justifyContent: FlexAlign.Center, alignItems: ItemAlign.Center }) {
      if (this.isLoading) {
        LoadingProgress()
          .height(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
            (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE))
          .width(Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.maxFontSize ? MAX_SIZE :
            (Math.min(this.updateFontScale(), MAX_FONT_SIZE) === this.minFontSize ? MID_SIZE : MIN_SIZE))
          .margin({
            end: LengthMetrics.vp(ITEM_SPACE)
          })
      }
      Text(this.content)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .fontSize($r('sys.float.ohos_id_text_size_body2'))
        .minFontScale(1)
        .maxFontScale(Math.min(this.updateFontScale(), 2))
        .padding({
          top: DEFAULT_MARGIN,
          bottom: DEFAULT_MARGIN
        })
    }
  }
}
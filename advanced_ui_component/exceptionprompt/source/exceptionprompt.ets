/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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
import curves from '@ohos.curves';
import { common } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';

const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const ZINDEX_NUM = 9;


export enum MarginType {
  DEFAULT_MARGIN = 0,
  FIT_MARGIN = 1,
}

export interface PromptOptions {
  icon?: ResourceStr,
  tip?: ResourceStr,
  marginType: MarginType,
  actionText?: ResourceStr,
  marginTop: Dimension,
  isShown?: boolean
}

@Component
export struct ExceptionPrompt {
  @Prop options: PromptOptions
  touchBackgroundColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent')
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  onTipClick: () => void = () => {
    // Click the text on the left to change into the connecting state
  }
  onActionTextClick: () => void = () => {
    // Click Set Network to open the Set network pop-up interface
  }

  @Builder
  TextBuilder() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign
      .Center }) {
      Row() {
        Image(this.options.icon ?? $r('sys.media.ohos_ic_public_fail'))
          .width("24vp")
          .height('24vp')
          .fillColor($r('sys.color.ohos_id_color_warning'))
        Text(this.options.tip)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .minFontScale(1)
          .maxFontScale(Math.min(this.updateFontScale(), 2))
          .fontColor($r('sys.color.ohos_id_color_warning'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(2)
          .margin({
            left: $r('sys.float.ohos_id_dialog_margin_end'),
            right: $r('sys.float.ohos_id_dialog_margin_end')
          })
      }
      .padding({ right: $r('sys.float.ohos_id_default_padding_end') })
      .width('100%')
      .onClick(() => {
        this.onTipClick() //Click the callback of the prompt text
      })

      if (this.options.actionText) {
        Button({ stateEffect: false, type: ButtonType.Normal }) {
          Row() {
            Text(this.options.actionText)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .minFontScale(1)
              .maxFontScale(Math.min(this.updateFontScale(), 2))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .maxLines(2)
              .padding(0)
              .margin({ right: $r('sys.float.ohos_id_text_paragraph_margin_s') })
              .textOverflow({ overflow: TextOverflow.Ellipsis })
            Image($r('sys.media.ohos_ic_public_arrow_right'))
              .width('12vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
          }
        }
        .backgroundColor(this.touchBackgroundColor)
        .width(this.options.actionText ? 144 : 0)
        .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
        .padding({
          right: $r('sys.float.ohos_id_elements_margin_vertical_l'),
          left: $r('sys.float.ohos_id_elements_margin_vertical_l')
        })
        .onTouch((event) => {

          if (event.type === TouchType.Down) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_click_effect')
            this.onActionTextClick() //Click the icon button on the right for the callback
          } else if (event.type === TouchType.Up) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_sub_background_transparent')
          }
        })

      }
    }
    .padding({
      left: $r('sys.float.ohos_id_notification_margin_start'),
      right: $r('sys.float.ohos_id_text_paragraph_margin_s'),
      top: $r('sys.float.ohos_id_default_padding_start'),
      bottom: $r('sys.float.ohos_id_default_padding_end')
    })
  }

  build() {
    Row() {
      Column() {
        Column() {
          this.TextBuilder()
        }
        .width('100%')
        .borderRadius(BORDER_RADIUS)
        .backgroundColor($r('sys.color.comp_background_warning_secondary'))
        .zIndex(ZINDEX_NUM)
      }
      .padding(this.options.marginType === MarginType.DEFAULT_MARGIN ? {
        left: $r('sys.float.ohos_id_card_margin_start'),
        right: $r('sys.float.ohos_id_card_margin_end')
      } : {
        left: $r('sys.float.ohos_id_max_padding_start'),
        right: $r('sys.float.ohos_id_max_padding_end')
      })
      .transition(
        TransitionEffect.OPACITY.animation({
          curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1),
          duration: this.options.isShown ? START_TIME : END_TIME
        })
      )
      .visibility(this.options.isShown ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .position({ y: this.options.marginTop })
    .zIndex(ZINDEX_NUM)
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
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
}
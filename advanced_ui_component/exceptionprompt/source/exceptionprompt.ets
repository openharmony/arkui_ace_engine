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
const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const OPACITY_NUM = 0.18;
const DEFAULT_HEIGHT = 48;
const FIT_HEIGHT = 58;
const ZINDEX_NUM = 999;

export enum MarginType {
  DEFAULT_MARGIN = 0,
  FIT_MARGIN = 1,
}

export interface PromptOptions {
  icon?: ResourceStr,
  tip?: ResourceStr,
  marginState: MarginType,
  touchText?: ResourceStr,
  isTouchShow?: boolean,
  positionTop: number,
  isShow?: boolean
}

@Component
export struct ExceptionPrompt {
  @Prop options: PromptOptions
  touchBackgroundColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent')
  onTextClick: () => void = () => {
    // Click the text on the left to change into the connecting state
  }
  onConfigure: () => void = () => {
    // Click Set Network to open the Set network pop-up interface
  }

  @Builder FirstBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_background'))
  }

  @Builder SecondBuilder() {
    Column() {
    }
    .height('100%')
    .width('100%')
    .borderRadius(BORDER_RADIUS)
    .backgroundColor($r('sys.color.ohos_id_color_warning'))
    .opacity(OPACITY_NUM)
    .zIndex(ZINDEX_NUM)
  }

  @Builder TextBuilder() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
      Flex({ alignItems: ItemAlign.Center }) {
        Image(this.options.icon??$r('sys.media.ohos_ic_public_fail'))
          .width("24vp")
          .height('24vp')
          .objectFit(ImageFit.Contain)
          .fillColor($r('sys.color.ohos_id_color_warning'))
        Text(this.options.tip)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .fontColor($r('sys.color.ohos_id_color_warning'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(2)
          .margin({ left: $r('sys.float.ohos_id_dialog_margin_end'), right: $r('sys.float.ohos_id_dialog_margin_end') })
      }
      .width('100%')
      .height('100%')
      .onClick(() => {
        this.onTextClick() //Click the callback of the prompt text
      })

      if (this.options.isTouchShow) {
        Button({ stateEffect: true, type: ButtonType.Normal }) {
          Row() {
            Text(this.options.touchText)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .maxLines(1)
              .padding(0)
              .margin({ right: $r('sys.float.ohos_id_text_paragraph_margin_s') })
              .textAlign(TextAlign.End)
            Image($r('sys.media.ohos_ic_public_arrow_right'))
              .width('12vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
          }
        }
        .backgroundColor(this.touchBackgroundColor)
        .width(this.options.isTouchShow ? 120 : 0)
        .height(32)
        .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
        .padding({
          right: $r('sys.float.ohos_id_elements_margin_vertical_l'),
          left: $r('sys.float.ohos_id_elements_margin_vertical_l')
        })
        .onTouch((event) => {

          if (event.type === TouchType.Down) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_click_effect')
            this.onConfigure() //Click the icon button on the right for the callback
          } else if (event.type === TouchType.Up) {
            this.touchBackgroundColor = $r('sys.color.ohos_id_color_sub_background_transparent')
          }
        })
      }

    }
    .padding({
      left: $r('sys.float.ohos_id_notification_margin_start'),
      right: $r('sys.float.ohos_id_text_paragraph_margin_s')
    })
    .position({})
    .zIndex(ZINDEX_NUM)
    .width('100%')
    .height('100%')
  }

  build() {
    Column() {
      Stack() {
        this.FirstBuilder()
        this.SecondBuilder()
        this.TextBuilder()
      }
      .padding(this.options.marginState === MarginType.DEFAULT_MARGIN ? { left: $r('sys.float.ohos_id_card_margin_start'), right: $r('sys.float.ohos_id_card_margin_end') } : { left: $r('sys.float.ohos_id_max_padding_start'), right: $r('sys.float.ohos_id_max_padding_end') })
      .transition(
        TransitionEffect.OPACITY.animation({
          duration: this.options.isShow ? START_TIME : END_TIME
        })
      )
      .visibility(this.options.isShow ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .height(this.options.isTouchShow ? FIT_HEIGHT : DEFAULT_HEIGHT)
    .position({ y: this.options.positionTop })
    .zIndex(ZINDEX_NUM)
  }
}

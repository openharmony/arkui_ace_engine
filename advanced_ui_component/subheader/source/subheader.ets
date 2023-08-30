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

import { KeyCode } from '@ohos.multimodalInput.keyCode'

const SPACE_MARGIN: number = 8
const MARGIN_NUM: number = 4
const IMAGE_WIDTH_NUM: number = 16
const IMAGE_HEIGHT_NUM: number = 24
const BUTTON_SIZE: number = 32
const SINGLE_LINE_HEIGHT: number = 48
const DOUBLE_LINE_HEIGHT: number = 64
const BUTTON_HEIGHT: number = 28
const IMAGE_WIDTH: number = 12
const BORDER_WIDTH = 2
const DIVIDEND_WIDTH = 3
const SINGLE_LINE_NUM: number = 1
const DOUBLE_LINE_NUM: number = 2
const MIN_FONT_SIZE: number = 14
const MAIN_TEXT_SIZE: number = 10
const CONSTRAINT_NUM: number = 44
const CONTENT_NUM: number = 40

export enum OperationType {
  TEXT_ARROW = 0,
  BUTTON = 1,
  ICON_GROUP = 2,
  LOADING = 3,
}

export declare type OperationOption = {
  value: ResourceStr;
  action?: () => void;
}

export declare type SelectOptions = {
  options: Array<SelectOption>;
  selected?: number;
  value?: string;
  onSelect?: (index: number, value?: string) => void;
}

@Component
struct IconGroup {
  @State bgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State isFocus: boolean = false
  item: OperationOption
  focusBorderWidth = BORDER_WIDTH

  build() {
    Row() {
      Image(this.item.value)
        .fillColor($r('sys.color.ohos_id_color_primary'))
        .width(IMAGE_HEIGHT_NUM)
        .height(IMAGE_HEIGHT_NUM)
        .focusable(true)
    }
    .focusable(true)
    .width(BUTTON_SIZE)
    .height(BUTTON_SIZE)
    .margin({ right: SPACE_MARGIN, bottom: MARGIN_NUM })
    .justifyContent(FlexAlign.Center)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .backgroundColor(this.bgColor)
    .onTouch((event) => {
      if (event.type === TouchType.Down) {
        this.item.action && this.item.action()
        this.bgColor = $r('sys.color.ohos_id_color_click_effect')
      }
      if (event.type === TouchType.Up) {
        this.bgColor = $r('sys.color.ohos_id_color_background')
      }
    })
    .onHover((isHover: boolean) => {
      if (isHover) {
        this.bgColor = $r('sys.color.ohos_id_color_hover')
      } else {
        this.bgColor = $r('sys.color.ohos_id_color_background')
      }
    })
    .stateStyles({
      focused: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: this.focusBorderWidth,
          color: $r('sys.color.ohos_id_color_focused_outline'),
          style: BorderStyle.Solid
        })
      },
      normal: {
        .border({
          radius: $r('sys.float.ohos_id_corner_radius_clicked'),
          width: 0 })
      }
    })
    .onKeyEvent((event) => {
      if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
        this.item.action && this.item.action()
      }
    })
  }
}

@Component
export struct SubHeader {
  @Prop icon: Resource
  @Prop primaryTitle: string
  @Prop secondaryTitle: string
  @Prop select: SelectOptions
  @Prop operationType: OperationType = OperationType.BUTTON
  operationItem: Array<OperationOption>
  @State isDuplicateLine: boolean = false
  @State textArrowBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State buttonBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State flexWidth: number = 0
  @State textArrowWidth: number = 0
  @State textArrowFocus: boolean = false
  @State buttonFocus: boolean = false
  @State arrowWidth: number = 0
  @State buttonWidth: number = 0
  focusBorderWidth = BORDER_WIDTH

  @Builder ListTextStyle($$: { content: ResourceStr }) {
    Text($$.content)
      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
      .fontSize($r('sys.float.ohos_id_text_size_sub_title3'))
      .fontWeight(FontWeight.Medium)
      .maxLines(DOUBLE_LINE_NUM)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .margin({ left: $r('sys.float.ohos_id_max_padding_end'), bottom: SPACE_MARGIN, right: MARGIN_NUM })
  }

  @Builder ListIconStyle($$: { content: ResourceStr }, icon: ResourceStr) {
    Row() {
      Image(icon)
        .width(IMAGE_WIDTH_NUM)
        .height(IMAGE_WIDTH_NUM)
        .margin({ right: SPACE_MARGIN })
      Text($$.content)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .fontSize($r('sys.float.ohos_id_text_size_sub_title3'))
        .fontWeight(FontWeight.Medium)
        .maxLines(DOUBLE_LINE_NUM)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .margin({ left: $r('sys.float.ohos_id_max_padding_end'), bottom: SPACE_MARGIN, right: MARGIN_NUM })
  }

  @Builder ContentTextStyle($$: { content: ResourceStr }) {
    Text($$.content)
      .fontColor($r('sys.color.ohos_id_color_text_primary'))
      .fontSize($r('sys.float.ohos_id_text_size_sub_title1'))
      .fontWeight(FontWeight.Medium)
      .maxLines(DOUBLE_LINE_NUM)
      .maxFontSize($r('sys.float.ohos_id_text_size_sub_title1'))
      .minFontSize(MIN_FONT_SIZE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .margin({ left: $r('sys.float.ohos_id_max_padding_start'),
        right: MARGIN_NUM, bottom: SPACE_MARGIN })
  }

  @Builder SubTextStyle($$: { content: ResourceStr, subContent: ResourceStr }) {
    Column() {
      Text($$.content)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontSize($r('sys.float.ohos_id_text_size_sub_title1'))
        .fontWeight(FontWeight.Medium)
        .maxLines(SINGLE_LINE_NUM)
        .maxFontSize($r('sys.float.ohos_id_text_size_sub_title1'))
        .minFontSize(MIN_FONT_SIZE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
      Text($$.subContent)
        .fontColor($r('sys.color.ohos_id_color_text_secondary'))
        .fontSize($r('sys.float.ohos_id_text_size_sub_title3'))
        .fontWeight(FontWeight.Medium)
        .maxLines(SINGLE_LINE_NUM)
        .maxFontSize($r('sys.float.ohos_id_text_size_sub_title3'))
        .minFontSize(MAIN_TEXT_SIZE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
    }
    .alignItems(HorizontalAlign.Start)
    .onAppear(() => {
      this.isDuplicateLine = true
    })
    .margin({ left: $r('sys.float.ohos_id_max_padding_start'),
      right: MARGIN_NUM, bottom: SPACE_MARGIN })
  }

  @Builder SelectStyle(selectParam: SelectOptions) {
    Select(selectParam.options)
      .selected(selectParam.selected)
      .value(selectParam.value)
      .onSelect((index: number, value?: string) => {
        if (selectParam.onSelect) {
          selectParam.onSelect(index, value)
        }
      })
      .font({
        size: $r('sys.float.ohos_id_text_size_sub_title1'),
        weight: FontWeight.Medium
      })
      .margin({ left: $r('sys.float.ohos_id_default_padding_start'), right: MARGIN_NUM })
  }

  @Builder LoadingProcessStyle() {
    LoadingProgress()
      .width(IMAGE_HEIGHT_NUM)
      .height(IMAGE_HEIGHT_NUM)
      .focusable(true)
      .margin({ right: $r('sys.float.ohos_id_default_padding_end'), bottom: MARGIN_NUM })
  }

  @Builder TextArrowStyle(textArrow: OperationOption) {
    Row() {
      Stack() {
        Row() {
          Row() {
            if (textArrow != null) {
              Text(textArrow.value)
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                .fontSize($r('sys.float.ohos_id_text_size_body2'))
                .margin({ right: MARGIN_NUM })
                .focusable(true)
                .maxLines(1)
                .constraintSize({ maxWidth: this.textArrowWidth - CONTENT_NUM })
            }
            Image($r('sys.media.ohos_ic_public_arrow_right'))
              .fillColor($r('sys.color.ohos_id_color_tertiary'))
              .width(IMAGE_WIDTH)
              .height(IMAGE_HEIGHT_NUM)
              .focusable(true)
          }.margin({ left: SPACE_MARGIN, right: SPACE_MARGIN })
        }
        .height(BUTTON_SIZE)
        .justifyContent(FlexAlign.End)
        .onFocus(() => {
          this.textArrowFocus = true
        })
        .onBlur(() => {
          this.textArrowFocus = false
        })
        .borderRadius(MARGIN_NUM)
        .focusable(true)
        .margin({ left: MARGIN_NUM, right: MARGIN_NUM })
        .backgroundColor(this.textArrowBgColor)
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            if (textArrow.action) {
              textArrow.action()
            }
            this.textArrowBgColor = $r('sys.color.ohos_id_color_click_effect')
          }
          if (event.type === TouchType.Up) {
            this.textArrowBgColor = $r('sys.color.ohos_id_color_background')
          }
        })
        .onHover((isHover: boolean) => {
          if (isHover) {
            this.textArrowBgColor = $r('sys.color.ohos_id_color_hover')
          } else {
            this.textArrowBgColor = $r('sys.color.ohos_id_color_background')
          }
        })
        .onKeyEvent((event) => {
          if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
            textArrow.action && textArrow.action()
          }
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          this.arrowWidth = Number(parseInt(newValue.width.toString(), 0))
        })

        if (this.textArrowFocus) {
          Row()
            .height(BUTTON_SIZE)
            .width(this.arrowWidth)
            .hitTestBehavior(HitTestMode.None)
            .border({
              width: BORDER_WIDTH,
              color: $r('sys.color.ohos_id_color_focused_outline')
            })
            .borderRadius(MARGIN_NUM)
        }
      }
    }
    .onAreaChange((oldValue: Area, newValue: Area) => {
      this.textArrowWidth = Number(parseInt(newValue.width.toString(), 0))
    })
    .constraintSize({ minWidth: this.flexWidth / DIVIDEND_WIDTH })
    .justifyContent(FlexAlign.End)
    .margin({ left: SPACE_MARGIN })
  }

  @Builder ButtonStyle(button: OperationOption) {
    Row() {
      Stack() {
        Row() {
          if (button != null) {
            Text(button.value)
              .maxLines(1)
              .fontColor($r('sys.color.ohos_id_color_text_primary_activated'))
              .fontSize($r('sys.float.ohos_id_text_size_button2'))
              .fontWeight(FontWeight.Medium)
              .margin({ left: SPACE_MARGIN, right: SPACE_MARGIN })
              .focusable(true)
          }
        }
        .justifyContent(FlexAlign.End)
        .alignItems(VerticalAlign.Center)
        .focusable(true)
        .height(BUTTON_HEIGHT)
        .margin({ left: SPACE_MARGIN, right: SPACE_MARGIN })
        .borderRadius(IMAGE_WIDTH_NUM)
        .backgroundColor(this.buttonBgColor)
        .onFocus(() => {
          this.buttonFocus = true
        })
        .onBlur(() => {
          this.buttonFocus = false
        })
        .onTouch((event) => {
          if (event.type === TouchType.Down) {
            if (button.action) {
              button.action()
            }
            this.buttonBgColor = $r('sys.color.ohos_id_color_click_effect')
          }
          if (event.type === TouchType.Up) {
            this.buttonBgColor = $r('sys.color.ohos_id_color_background')
          }
        })
        .onHover((isHover: boolean) => {
          if (isHover) {
            this.buttonBgColor = $r('sys.color.ohos_id_color_hover')
          } else {
            this.buttonBgColor = $r('sys.color.ohos_id_color_background')
          }
        })
        .onKeyEvent((event) => {
          if (event.keyCode === KeyCode.KEYCODE_ENTER || event.keyCode === KeyCode.KEYCODE_SPACE) {
            button.action && button.action()
          }
        })
        .onAreaChange((oldValue: Area, newValue: Area) => {
          let flexWidth = Number(parseInt(newValue.width.toString(), 0))
          this.buttonWidth = flexWidth
        })

        if (this.buttonFocus) {
          Row()
            .height(BUTTON_HEIGHT)
            .width(this.buttonWidth)
            .hitTestBehavior(HitTestMode.None)
            .border({
              width: BORDER_WIDTH,
              color: $r('sys.color.ohos_id_color_focused_outline')
            })
            .borderRadius(IMAGE_WIDTH_NUM)
        }
      }
    }
    .constraintSize({ minWidth: this.flexWidth / DIVIDEND_WIDTH })
    .justifyContent(FlexAlign.End)
    .focusable(true)
    .margin({ left: SPACE_MARGIN })
  }

  build() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.End }) {
      if (this.secondaryTitle != null && this.icon != null) {
        Row() {
          this.ListIconStyle({ content: this.secondaryTitle }, this.icon)
        }.margin({ right: SPACE_MARGIN })
      } else if (this.secondaryTitle != null && this.primaryTitle != null) {
        this.SubTextStyle({ content: this.primaryTitle, subContent: this.secondaryTitle })
      } else if (this.secondaryTitle != null) {
        this.ListTextStyle({ content: this.secondaryTitle })
      } else if (this.select != null) {
        this.SelectStyle(this.select)
      } else if (this.primaryTitle != null) {
        this.ContentTextStyle({ content: this.primaryTitle })
      }

      Row() {
        if (this.operationType === OperationType.BUTTON && this.operationItem != null) {
          this.ButtonStyle(this.operationItem[0])
        }
        if (this.operationType === OperationType.ICON_GROUP && this.operationItem != null) {
          Row() {
            ForEach(this.operationItem, (item, index?: number) => {
              if (index == 0) {
                IconGroup({ item: item })
              }
              if (index == 1) {
                IconGroup({ item: item })
              }
              if (index == 2) { // Image count
                IconGroup({ item: item })
              }
            })
          }
        }
        if (this.operationType === OperationType.TEXT_ARROW && this.operationItem != null) {
          this.TextArrowStyle(this.operationItem[0])
        }
        if (this.operationType === OperationType.LOADING) {
          this.LoadingProcessStyle()
        }
      }
    }
    .focusable(true)
    .onAreaChange((oldValue: Area, newValue: Area) => {
      let flexWidth = Number(parseInt(newValue.width.toString(), 0))
      this.flexWidth = flexWidth - CONSTRAINT_NUM
    })
    .padding({ right: $r('sys.float.ohos_id_default_padding_end') })
    .height(this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT)
  }
}
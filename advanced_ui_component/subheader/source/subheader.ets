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
const CONSTRAINT_WIDTH: number = 40
const CONSTRAINT_NUM: number = 44

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
    .border(this.isFocus ?
      { width: this.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_emphasize'),
        style: BorderStyle.Solid
      } : { width: 0 })
    .onFocus(() => {
      this.isFocus = true;
    })
    .onBlur(() => {
      this.isFocus = false;
    })
    .onKeyEvent((event) => {
      if (event.keyCode === 2054 || event.keyCode === 2050) {
        this.item.action && this.item.action()
      }
    })
  }
}

@Component
export struct SubHeader1 {
  @Prop icon: Resource
  @Prop primaryTitle: string
  @Prop secondaryTitle: string
  @Prop select: SelectOptions
  @Prop operationType: OperationType = OperationType.BUTTON
  operationItem: Array<OperationOption>
  @State isDuplicateLine: boolean = false
  @State textArrowBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State buttonBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State iconBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State firstIconBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State SecondaryIconBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State thirdIconBgColor: Resource = $r('sys.color.ohos_id_color_background')
  @State flag: boolean = false
  @State isTextArrowFocus: boolean = false
  @State flexWidth: number = 0
  @State titleWidth: number = 0
  @State titleWidth1: number = 0
  @State isButtonFocus: boolean = false
  focusBorderWidth = BORDER_WIDTH

  @Builder ListTextStyle($$: { content: ResourceStr }) {
    Text($$.content)
      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
      .fontSize($r('sys.float.ohos_id_text_size_sub_title3'))
      .fontWeight(FontWeight.Medium)
      .maxLines(DOUBLE_LINE_NUM)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .constraintSize({ minWidth: this.titleWidth })
      .margin({ left: $r('sys.float.ohos_id_max_padding_end'), bottom: SPACE_MARGIN, right: MARGIN_NUM }).borderWidth(1)
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
        .constraintSize({ minWidth: this.titleWidth - CONSTRAINT_WIDTH })
    }
    .margin({ left: $r('sys.float.ohos_id_max_padding_end'), bottom: SPACE_MARGIN, right: MARGIN_NUM })
  }

  @Builder ContentTextStyle($$: { content: ResourceStr }) {
    Text($$.content)
      .fontColor($r('sys.color.ohos_id_color_text_primary'))
      .fontSize($r('sys.float.ohos_id_text_size_sub_title2'))
      .fontWeight(FontWeight.Medium)
      .maxLines(DOUBLE_LINE_NUM)
      .maxFontSize($r('sys.float.ohos_id_text_size_sub_title2'))
      .minFontSize(MIN_FONT_SIZE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .constraintSize({ maxWidth: this.titleWidth })
      .margin({ left: $r('sys.float.ohos_id_max_padding_start'),
        right: MARGIN_NUM, bottom: SPACE_MARGIN })
  }

  @Builder SubTextStyle($$: { content: ResourceStr, subContent: ResourceStr }) {
    Column() {
      Text($$.content)
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .fontSize($r('sys.float.ohos_id_text_size_sub_title2'))
        .fontWeight(FontWeight.Medium)
        .maxLines(SINGLE_LINE_NUM)
        .maxFontSize($r('sys.float.ohos_id_text_size_sub_title2'))
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
    .constraintSize({ maxWidth: this.titleWidth })
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
      .constraintSize({ maxWidth: this.titleWidth })
      .margin({ left: $r('sys.float.ohos_id_default_padding_start'), right: MARGIN_NUM})
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
      Row() {
        if (textArrow != null) {
          Text(textArrow.value)
            .fontColor($r('sys.color.ohos_id_color_text_secondary'))
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .margin({ right: MARGIN_NUM })
            .focusable(true)
            .maxLines(DOUBLE_LINE_NUM)
        }
        Image($r('sys.media.ohos_ic_public_arrow_right'))
          .fillColor($r('sys.color.ohos_id_color_tertiary'))
          .width(IMAGE_WIDTH)
          .height(IMAGE_HEIGHT_NUM)
          .focusable(true)
      }.margin({ left: SPACE_MARGIN, right: SPACE_MARGIN })
    }
    .justifyContent(FlexAlign.End)
    .focusable(true)
    .margin({ left:MARGIN_NUM, right: MARGIN_NUM, bottom: MARGIN_NUM })
    .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
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
    .border(this.isTextArrowFocus ?
      { width: this.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
      } : { width: 0 })
    .onFocus(() => {
      this.isTextArrowFocus = true;
    })
    .onBlur(() => {
      this.isTextArrowFocus = false;
    })
    .onKeyEvent((event) => {
      if (event.keyCode === 2054 || event.keyCode === 2050) {
        textArrow.action && textArrow.action()
      }
    })
  }

  @Builder ButtonStyle(button: OperationOption) {
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
    .onAreaChange((oldValue: Area, newValue: Area) => {
      Number(parseInt(newValue.width.toString(), 0))
      console.log('wy buttonStyle1'+Number(parseInt(newValue.width.toString(), 0)))
    })
    .justifyContent(FlexAlign.End)
    .alignItems(VerticalAlign.Center)
    .constraintSize({ maxWidth: this.flexWidth-this.titleWidth1 + 36 })
    .focusable(true)
    .height(BUTTON_HEIGHT)
    .margin({ left: SPACE_MARGIN, right: MARGIN_NUM })
    .borderRadius(IMAGE_WIDTH_NUM)
    .backgroundColor(this.buttonBgColor)
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
    .border(this.isButtonFocus ?
      { width: this.focusBorderWidth,
        color: $r('sys.color.ohos_id_color_focused_outline'),
        style: BorderStyle.Solid
      } : { width: 0 })
    .onFocus(() => {
      this.isButtonFocus = true;
    })
    .onBlur(() => {
      this.isButtonFocus = false;
    })
    .onKeyEvent((event) => {
      if (event.keyCode === 2054 || event.keyCode === 2050) {
        button.action && button.action()
      }
    })
  }
  
  build() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.End }) {
      Row() {
        if (this.secondaryTitle != null && this.icon != null) {
          this.ListIconStyle({ content: this.secondaryTitle }, this.icon)
        } else if (this.secondaryTitle != null && this.primaryTitle != null) {
          this.SubTextStyle({ content: this.primaryTitle, subContent: this.secondaryTitle })
        } else if (this.secondaryTitle != null) {
          this.ListTextStyle({ content: this.secondaryTitle })
        } else if (this.select != null) {
          this.SelectStyle(this.select)
        } else if (this.primaryTitle != null) {
          this.ContentTextStyle({ content: this.primaryTitle })
        }
      }
      .onAreaChange((oldValue: Area, newValue: Area) => {
        this.titleWidth1 = Number(parseInt(newValue.width.toString(), 0))
        console.log('wy titleWidth1'+this.titleWidth.toString())
      })

      Row() {
        if (this.operationType === OperationType.BUTTON && this.operationItem != null) {
          this.ButtonStyle(this.operationItem[0] )
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
    .onAreaChange((oldValue: Area, newValue: Area) => {
      let flexWidth = Number(parseInt(newValue.width.toString(), 0))
      this.flexWidth = flexWidth - CONSTRAINT_NUM
      this.titleWidth = this.flexWidth / DIVIDEND_WIDTH * BORDER_WIDTH
      console.log('wy flexWidth'+this.flexWidth.toString())
    })
    .padding({ right: $r('sys.float.ohos_id_default_padding_end') })
    .height(this.isDuplicateLine ? DOUBLE_LINE_HEIGHT : SINGLE_LINE_HEIGHT)
  }
}
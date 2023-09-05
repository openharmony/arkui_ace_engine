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

export enum IconType {
  BADGE = 1,
  NORMAL_ICON,
  SYSTEM_ICON,
  HEAD_SCULPTURE,
  APP_ICON,
  PREVIEW,
  LONGITUDINAL,
  VERTICAL
}

enum ItemHeight {
  FIRST_HEIGHT = 48,
  SECOND_HEIGHT = 56,
  THIRD_HEIGHT = 64,
  FOURTH_HEIGHT = 72,
  FIFTH_HEIGHT = 96
}

export type OperateItem = {
  icon?: OperateIcon,
  subIcon ?: OperateIcon,
  button?: OperateButton;
  switch?: OperateCheck;
  checkbox?: OperateCheck;
  radio?: OperateCheck;
  image?: ResourceStr;
  text?: ResourceStr;
  arrow?: OperateIcon;
}

export type ContentItem = {
  iconStyle?: IconType;
  icon?: ResourceStr;
  primaryText?: ResourceStr;
  secondaryText?: ResourceStr;
  description?: ResourceStr;
}

export declare type OperateIcon = {
  value: ResourceStr,
  action?: () => void
}

export type OperateButton = {
  text?: string
}

export declare type OperateCheck = {
  isCheck?: boolean,
  onChange?: (value: boolean) => void
}

const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const BADGE_SIZE = 8;
const SMALL_ICON_SIZE = 16;
const SYSTEM_ICON_SIZE = 24;
const TEXT_ARROW_HEIGHT = 32;
const SAFE_LIST_PADDING = 32;
const HEADSCULPTURE_SIZE = 40;
const BUTTON_SIZE = 28;
const APP_ICON_SIZE = 64;
const PREVIEW_SIZE = 96;
const LONGITUDINAL_SIZE = 96;
const VERTICAL_SIZE = 96;
const NORMAL_ITEM_ROW_SPACE = 16;
const SPECIAL_ITEM_ROW_SPACE = 0;
const SPECIAL_ICON_SIZE = 0;
const DEFAULT_ROW_SPACE = 0;
const SPECICAL_ROW_SPACE = 4;
const OPERATEITEM_ICONLIKE_SIZE = 24;
const OPERATEITEM_ARROW_WIDTH = 12
const OPERATEITEM_ICON_CLICKABLE_SIZE = 48;
const OPERATEITEM_IMAGE_SIZE = 48;
const HOVERING_COLOR = '#0d000000';
const TOUCH_DOWN_COLOR = '#1a000000';
const ACTIVED_COLOR = '#1a0a59f7';
const ICON_SIZE_MAP: Map<number, number> = new Map([
  [IconType.BADGE, BADGE_SIZE],
  [IconType.NORMAL_ICON, SMALL_ICON_SIZE],
  [IconType.SYSTEM_ICON, SYSTEM_ICON_SIZE],
  [IconType.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
  [IconType.APP_ICON, APP_ICON_SIZE],
  [IconType.PREVIEW, PREVIEW_SIZE],
  [IconType.LONGITUDINAL, LONGITUDINAL_SIZE],
  [IconType.VERTICAL, VERTICAL_SIZE]
])

@Component
struct ContentItemStruct {
  iconStyle: IconType = null
  icon: Resource = null
  primaryText: string = null
  secondaryText: string = null
  description: string = null
  private itemRowSpace: number = NORMAL_ITEM_ROW_SPACE

  aboutToAppear() {
    if (this.icon == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE
    }
  }

  @Builder
  createIcon() {
    if (this.icon != null && this.iconStyle != null) {
      if (this.iconStyle <= IconType.PREVIEW) {
        Image(this.icon)
          .objectFit(ImageFit.Contain)
          .width(ICON_SIZE_MAP.get(this.iconStyle))
          .height(ICON_SIZE_MAP.get(this.iconStyle))
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
          .focusable(true)
          .draggable(false)
      }
      else {
        Image(this.icon)
          .objectFit(ImageFit.Contain)
          .constraintSize({
            minWidth: SPECIAL_ICON_SIZE,
            maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
            minHeight: SPECIAL_ICON_SIZE,
            maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
          })
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
          .focusable(true)
          .draggable(false)
      }
    }
  }

  @Builder
  createText() {
    Column({ space: TEXT_COLUMN_SPACE }) {
      Text(this.primaryText)
        .fontSize($r('sys.float.ohos_id_text_size_body1'))
        .fontColor($r('sys.color.ohos_id_color_text_primary'))
        .maxLines(TEXT_MAX_LINE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .fontWeight(FontWeight.Medium)
        .focusable(true)
        .draggable(false)
      if (this.secondaryText != null) {
        Text(this.secondaryText)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor($r('sys.color.ohos_id_color_text_secondary'))
          .maxLines(TEXT_MAX_LINE)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .focusable(true)
          .draggable(false)
      }
      if (this.description != null) {
        Text(this.description)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor($r('sys.color.ohos_id_color_text_secondary'))
          .maxLines(TEXT_MAX_LINE)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .focusable(true)
          .draggable(false)
      }
    }
    .margin({
      top: TEXT_SAFE_MARGIN,
      bottom: TEXT_SAFE_MARGIN
    })
    .alignItems(HorizontalAlign.Start)
  }

  build() {
    Row({ space: this.itemRowSpace }) {
      this.createIcon()
      this.createText()
    }
  }
}

@Component
struct OperateItemStruct {
  arrow: OperateIcon = null
  icon: OperateIcon = null
  subIcon: OperateIcon = null
  button: OperateButton = null
  switch: OperateCheck = null
  checkBox: OperateCheck = null
  radio: OperateCheck = null
  image: Resource = null
  text: string = null
  @State switchState: boolean = false
  @State radioState: boolean = false
  @State checkBoxState: boolean = false
  @Link parentCanFocus: boolean
  @Link parentCanTouch: boolean
  @Link parentIsHover: boolean
  @Link parentCanHover: boolean
  @Link parentIsActive: boolean
  @Link parentFrontColor: string
  private rowSpace: number = DEFAULT_ROW_SPACE

  aboutToAppear() {
    if (this.switch != null) {
      this.switchState = this.switch.isCheck
    }
    if (this.radio != null) {
      this.radioState = this.radio.isCheck
    }
    if (this.checkBox != null) {
      this.checkBoxState = this.checkBox.isCheck
    }

    if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
      (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
      this.rowSpace = SPECICAL_ROW_SPACE
    }
  }

  @Builder
  createButton(text: string) {
    Button() {
      Row() {
        Text(text)
          .focusable(true)
      }
      .padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      })
    }
    .hitTestBehavior(HitTestMode.Block)
    .fontSize($r('sys.float.ohos_id_text_size_button3'))
    .fontColor($r('sys.color.ohos_id_color_text_primary_activated_transparent'))
    .height(BUTTON_SIZE)
    .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .onFocus(() => {
      this.parentCanFocus = false
    })
    .onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.parentCanTouch = false
      }
      if (event.type == TouchType.Up) {
        this.parentCanTouch = true
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor == HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      }
    })
  }

  @Builder
  createIcon(icon: OperateIcon) {
    Button({ type: ButtonType.Normal }) {
      Image(icon.value)
        .height(OPERATEITEM_ICONLIKE_SIZE)
        .width(OPERATEITEM_ICONLIKE_SIZE)
        .focusable(true)
        .fillColor($r('sys.color.ohos_id_color_primary'))
        .draggable(false)
    }
    .hitTestBehavior(HitTestMode.Block)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.parentCanFocus = false
    })
    .onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.parentCanTouch = false
      }
      if (event.type == TouchType.Up) {
        this.parentCanTouch = true
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor == HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      }
    })
    .onClick((icon.action))
  }

  @Builder
  createImage(image: Resource) {
    Image(image)
      .height(OPERATEITEM_IMAGE_SIZE)
      .width(OPERATEITEM_IMAGE_SIZE)
      .draggable(false)
  }

  @Builder
  createText(text: string) {
    Text(text)
      .fontSize($r('sys.float.ohos_id_text_size_body2'))
      .fontColor($r('sys.color.ohos_id_color_text_secondary'))
      .focusable(true)
      .draggable(false)
  }

  @Builder
  createArrow(icon: OperateIcon) {
    Button({ type: ButtonType.Normal }) {
      Image(icon.value)
        .height(OPERATEITEM_ICONLIKE_SIZE)
        .width(OPERATEITEM_ARROW_WIDTH)
        .focusable(true)
        .fillColor($r('sys.color.ohos_id_color_fourth'))
        .draggable(false)
    }
    .hitTestBehavior(HitTestMode.Block)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICONLIKE_SIZE)
    .width(OPERATEITEM_ARROW_WIDTH)
    .onFocus(() => {
      this.parentCanFocus = false
    })
    .onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.parentCanTouch = false
      }
      if (event.type == TouchType.Up) {
        this.parentCanTouch = true
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor == HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      }
    })
    .onClick(icon.action)
  }

  @Builder
  createRadio(radio: OperateCheck) {
    Radio({ value: null, group: null })
      .checked(this.radioState)
      .onChange(radio.onChange)
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false
      })
      .hitTestBehavior(HitTestMode.Block)
      .onTouch((event: TouchEvent) => {
        if (event.type == TouchType.Down) {
          this.parentCanTouch = false
        }
        if (event.type == TouchType.Up) {
          this.parentCanTouch = true
        }
      })
      .onHover((isHover: boolean) => {
        this.parentCanHover = false
        if (isHover && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
        }
        if (!isHover) {
          this.parentCanHover = true
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
          }
        }
      })
  }

  @Builder
  createCheckBox(checkBox: OperateCheck) {
    Checkbox()
      .select(this.checkBoxState)
      .onChange(checkBox.onChange)
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false
      })
      .hitTestBehavior(HitTestMode.Block)
      .onTouch((event: TouchEvent) => {
        if (event.type == TouchType.Down) {
          this.parentCanTouch = false
        }
        if (event.type == TouchType.Up) {
          this.parentCanTouch = true
        }
      })
      .onHover((isHover: boolean) => {
        this.parentCanHover = false
        if (isHover && this.parentFrontColor == HOVERING_COLOR) {
          this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
        }
        if (!isHover) {
          this.parentCanHover = true
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
          }
        }
      })
  }

  @Builder
  createSwitch(toggleParams: OperateCheck) {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.switchState })
        .onChange(toggleParams.onChange)
        .onClick(() => {
          this.switchState = !this.switchState
        })
        .hitTestBehavior(HitTestMode.Block)
    }
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .justifyContent(FlexAlign.Center)
    .onFocus(() => {
      this.parentCanFocus = false
    })
    .onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.parentCanTouch = false
      }
      if (event.type == TouchType.Up) {
        this.parentCanTouch = true
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor == HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      }
    })
  }

  @Builder
  createTextArrow(text: string, icon: OperateIcon) {
    Button({ type: ButtonType.Normal }) {
      Row({ space: SPECICAL_ROW_SPACE }) {
        Text(text)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor($r('sys.color.ohos_id_color_text_secondary'))
          .focusable(true)
          .draggable(false)
        Image(icon.value)
          .height(OPERATEITEM_ICONLIKE_SIZE)
          .width(OPERATEITEM_ARROW_WIDTH)
          .fillColor($r('sys.color.ohos_id_color_fourth'))
          .focusable(true)
          .draggable(false)
      }
      .padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      })
    }
    .hitTestBehavior(HitTestMode.Block)
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .backgroundColor(Color.Transparent)
    .height(TEXT_ARROW_HEIGHT)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.parentCanFocus = false
    })
    .onTouch((event: TouchEvent) => {
      if (event.type == TouchType.Down) {
        this.parentCanTouch = false
      }
      if (event.type == TouchType.Up) {
        this.parentCanTouch = true
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor == HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString()
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR : (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      }
    })
    .onClick(icon.action)
  }

  build() {
    Row({
      space: this.rowSpace
    }) {
      if (this.button != null) {
        this.createButton(this.button.text)
      }

      else if (this.image != null) {
        this.createImage(this.image)
      }
      else if (this.icon != null && this.text != null) {
        this.createText(this.text)
        this.createIcon(this.icon)
      }
      else if (this.arrow != null && this.text == null) {
        this.createArrow(this.arrow)
      }
      else if (this.arrow != null && this.text != null) {
        this.createTextArrow(this.text, this.arrow)
      }
      else if (this.text != null) {
        this.createText(this.text)
      }
      else if (this.radio != null) {
        this.createRadio(this.radio)
      }
      else if (this.checkBox != null) {
        this.createCheckBox(this.checkBox)
      }
      else if (this.switch != null) {
        this.createSwitch(this.switch)
      }
      else if (this.icon != null) {
        this.createIcon(this.icon)
        if (this.subIcon != null) {
          this.createIcon(this.subIcon)
        }
      }
    }
  }
}

@Component
export struct ComposeListItem {
  @Prop contentItem: ContentItem = null;
  @Prop operateItem: OperateItem = null;
  @State frontColor: string = Color.Transparent.toString()
  @State borderSize: number = 0;
  @State canFocus: boolean = false
  @State canTouch: boolean = true
  @State canHover: boolean = true
  @State isHover: boolean = true
  @State itemHeight: number = ItemHeight.FIRST_HEIGHT;
  @State isActive: boolean = false

  aboutToAppear() {
    if (this.contentItem === null) {
      if (this.operateItem.image !== null || this.operateItem.icon !== null || this.operateItem.subIcon !== null) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING
      }
      return
    }

    if (this.contentItem.secondaryText === null && this.contentItem.description === null) {
      if (this.contentItem.icon === null) {
        this.itemHeight = ItemHeight.FIRST_HEIGHT
      }
      else {
        this.itemHeight = this.contentItem.iconStyle <= IconType.HEAD_SCULPTURE ? ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT
      }
    }
    else if (this.contentItem.description === null) {
      if (this.contentItem.icon === null || (this.contentItem.icon !== null && this.contentItem.iconStyle <= IconType.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT
      }
      else {
        this.itemHeight = ItemHeight.FOURTH_HEIGHT
      }
    }
    else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT
    }

    if (ICON_SIZE_MAP.get(this.contentItem.iconStyle) >= this.itemHeight) {
      this.itemHeight = ICON_SIZE_MAP.get(this.contentItem.iconStyle) + SAFE_LIST_PADDING;
    }
  }

  build() {
    Stack() {
      Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        if (this.contentItem === null) {
          ContentItemStruct({})
        }
        if (this.contentItem !== null) {
          ContentItemStruct({
            icon: typeof this.contentItem.icon === 'string' ? null : this.contentItem.icon,
            iconStyle: this.contentItem.iconStyle,
            primaryText: typeof this.contentItem.primaryText === 'string' ? this.contentItem.primaryText : null,
            secondaryText: typeof this.contentItem.secondaryText === 'string' ? this.contentItem.secondaryText : null,
            description: typeof this.contentItem.description === 'string' ? this.contentItem.description : null
          })
        }
        if (this.operateItem !== null) {
          OperateItemStruct({
            icon: this.operateItem.icon,
            subIcon: this.operateItem.subIcon,
            button: this.operateItem.button,
            switch: this.operateItem.switch,
            checkBox: this.operateItem.checkbox,
            radio: this.operateItem.radio,
            image: typeof this.operateItem.image === 'string' ? null : this.operateItem.image,
            text: typeof this.operateItem.text === 'string' ? this.operateItem.text : null,
            arrow: typeof this.operateItem.arrow === 'string' ? null : this.operateItem.arrow,
            parentCanFocus: this.canFocus,
            parentCanTouch: this.canTouch,
            parentIsHover: this.isHover,
            parentFrontColor: this.frontColor,
            parentIsActive: this.isActive,
            parentCanHover: this.canHover
          })
            .onFocus(() => {
              this.canFocus = false
            })
            .onBlur(() => {
              this.canFocus = true
            })
        }
      }
      .height(this.itemHeight)
      .focusable(true)
      .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
      .backgroundColor(this.frontColor)
      .onFocus(() => {
        this.canFocus = true
      })
      .onBlur(() => {
        this.canFocus = false
      })
      .onHover((isHover: boolean) => {
        this.isHover = isHover
        if (this.canHover) {
          this.frontColor = isHover ? HOVERING_COLOR : (this.isActive ? ACTIVED_COLOR : Color.Transparent.toString())
        }
      })
      .onTouch((event: TouchEvent) => {
        if (event.type == TouchType.Down && this.canTouch) {
          this.frontColor = TOUCH_DOWN_COLOR
        }
        if (event.type == TouchType.Up) {
          this.isActive = !this.isActive
          this.frontColor = this.isActive ? ACTIVED_COLOR : Color.Transparent.toString()
        }
      })

      if (this.canFocus) {
        Row()
          .height(this.itemHeight)
          .width('100%')
          .hitTestBehavior(HitTestMode.None)
          .border({
            width: ITEM_BORDER_SHOWN,
            color: $r('sys.color.ohos_id_color_focused_outline')
          })
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
      }
    }
    .padding({
      left: $r('sys.float.ohos_id_default_padding_start'),
      right: $r('sys.float.ohos_id_default_padding_end')
    })
  }
}
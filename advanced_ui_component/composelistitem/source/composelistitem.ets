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

import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';

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

enum FontSizeScaleLevel {
  LEVEL1 = 1.75,
  LEVEL2 = 2,
  LEVEL3 = 3.2
}

enum ItemHeight {
  FIRST_HEIGHT = 48,
  SECOND_HEIGHT = 56,
  THIRD_HEIGHT = 64,
  FOURTH_HEIGHT = 72,
  FIFTH_HEIGHT = 96
}

export declare class OperateItem {
  public icon?: OperateIcon;
  public subIcon?: OperateIcon;
  public button?: OperateButton;
  public switch?: OperateCheck;
  public checkbox?: OperateCheck;
  public radio?: OperateCheck;
  public image?: ResourceStr;
  public text?: ResourceStr;
  public arrow?: OperateIcon;
}

export declare class ContentItem {
  public iconStyle?: IconType;
  public icon?: ResourceStr;
  public primaryText?: ResourceStr;
  public secondaryText?: ResourceStr;
  public description?: ResourceStr;
}

export declare class OperateIcon {
  public value: ResourceStr;
  public action?: () => void;
}

export declare class OperateButton {
  public text?: ResourceStr;
}

export declare class OperateCheck {
  public isCheck?: boolean;
  public onChange?: (value: boolean) => void;
}

const TEXT_MAX_LINE = 1;
const ITEM_BORDER_SHOWN = 2;
const TEXT_COLUMN_SPACE = 4;
const TEXT_SAFE_MARGIN = 8;
const LISTITEM_PADDING = 6;
const SWITCH_PADDING = 4;
const STACK_PADDING = 4;
const BADGE_SIZE = 8;
const SMALL_ICON_SIZE = 16;
const SYSTEM_ICON_SIZE = 24;
const TEXT_ARROW_HEIGHT = 32;
const SAFE_LIST_PADDING = 32;
const HEADSCULPTURE_SIZE = 40;
const BUTTON_SIZE = 28;
const APP_ICON_SIZE = LengthMetrics.resource($r('sys.float.composeListItem_app_icon_size')).value;
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
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const RIGHT_CONTENT_NULL_LEFTWIDTH = '100%';
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const LEFT_ONLY_ARROW_WIDTH = 'calc(100% - 40vp)';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
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
const IS_CLOSE_CHILD_FOCUS: boolean = LengthMetrics.resource($r('sys.float.composeListItem_focus_dynamic_effect')).value !== 1;
const RECOVER_YSCALE = 1;
const CLEAR_SHADOW: ShadowStyle = -1;
const OPERATE_ITEM_RADIUS = 50;
const OPERATE_ITEM_BACKGROUND_COLOR = '#33000000';
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR = $r('sys.color.ohos_id_color_switch_outline_off');
const OPERATE_ITECOLOR = '#99000000';
const MARQUEE = 1;
const UNUSUAL = -1;

@Component
struct ContentItemStruct {
  @Prop @Watch('onPropChange') iconStyle: IconType | null = null;
  @Prop @Watch('onPropChange') icon: ResourceStr | null = null;
  @Prop @Watch('onPropChange') primaryText: ResourceStr | null = null;
  @Prop @Watch('onPropChange') secondaryText: ResourceStr | null = null;
  @Prop @Watch('onPropChange') description: ResourceStr | null = null;
  @State itemRowSpace: number = NORMAL_ITEM_ROW_SPACE;
  @Prop leftWidth: string = LEFT_PART_WIDTH;
  @State primaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary');
  @State secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @State descriptionColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Prop fontSizeScale: number;
  @Prop parentDirection: FlexDirection;
  @Prop itemDirection: FlexDirection;
  @Prop @Watch('onPropChange') isFocus: boolean = false;
  @State primaryTextSize: string | number | Resource = $r('sys.float.composeListItem_normal_left_text_size');
  @State primaryTextColors: ResourceColor = $r('sys.color.composeListItem_normal_left_text_color');
  @Prop itemHeight: number | null = null;
  @State iconColor: ResourceColor | null = null;
  @State secondaryTextColors: ResourceColor = $r('sys.color.composeListItem_normal_left_secondary_text_color');
  @State secondaryThirdTextSize: string | number | Resource = $r('sys.float.composeListItem_left_secondary_description_text_size');
  @State descriptionColors: ResourceColor = $r('sys.color.composeListItem_normal_left_description_text_color');

  onWillApplyTheme(theme: Theme): void {
    this.primaryTextColor = theme.colors.fontPrimary;
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.descriptionColor = theme.colors.fontTertiary;
  }

  onPropChange() {
    if (this.icon == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    } else {
      this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
    }
    this.primaryTextColors = this.isFocus ? $r('sys.color.composeListItem_focused_left_text_color') : this.primaryTextColor;
    this.secondaryTextColors = this.isFocus ? $r('sys.color.composeListItem_focused_left_secondary_text_color') : this.secondaryTextColor;
    this.descriptionColors = this.isFocus ? $r('sys.color.composeListItem_focused_left_description_text_color') : this.descriptionColor;
  }

  getIconFillColor(): ResourceColor {
    switch (this.iconStyle) {
      case IconType.BADGE:
        return $r('sys.color.composeListItem_badge_color');
      case IconType.SYSTEM_ICON:
        return $r('sys.color.composeListItem_normal_icon_color');
      default:
        return $r('sys.color.ohos_id_color_secondary');
    }
  }

  aboutToAppear() {
    this.onPropChange();
  }

  @Builder
  createIcon() {
    if (this.icon != null && this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
      if (this.iconStyle <= IconType.PREVIEW) {
        Image(this.icon)
          .objectFit(ImageFit.Contain)
          .width(ICON_SIZE_MAP.get(this.iconStyle))
          .height(ICON_SIZE_MAP.get(this.iconStyle))
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
          .focusable(false)
          .draggable(false)
          .fillColor(this.getIconFillColor())
          .flexShrink(0)
      } else {
        Image(this.icon)
          .objectFit(ImageFit.Contain)
          .constraintSize({
            minWidth: SPECIAL_ICON_SIZE,
            maxWidth: ICON_SIZE_MAP.get(this.iconStyle),
            minHeight: SPECIAL_ICON_SIZE,
            maxHeight: ICON_SIZE_MAP.get(this.iconStyle)
          })
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
          .focusable(false)
          .draggable(false)
          .fillColor($r('sys.color.ohos_id_color_secondary'))
          .flexShrink(0)
      }
    }
  }

  @Builder
  createText() {
    Column({ space: TEXT_COLUMN_SPACE }) {
      Text(this.primaryText)
        .fontSize(this.primaryTextSize)
        .fontColor(this.primaryTextColors)
        .maxLines(TEXT_MAX_LINE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .fontWeight(FontWeight.Medium)
        .focusable(true)
        .draggable(false)
      if (this.secondaryText != null) {
        Text(this.secondaryText)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.secondaryTextColors)
          .maxLines(TEXT_MAX_LINE)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .focusable(true)
          .draggable(false)
      }
      if (this.description != null) {
        Text(this.description)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.descriptionColors)
          .maxLines(TEXT_MAX_LINE)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .focusable(true)
          .draggable(false)
      }
    }
    .flexShrink(1)
    .margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined :{
      top: TEXT_SAFE_MARGIN,
      bottom: TEXT_SAFE_MARGIN
    })
    .alignItems(HorizontalAlign.Start)
  }

  isColumnDirection() {
    return this.itemDirection === FlexDirection.Column;
  }

  isParentColumnDirection() {
    return this.parentDirection === FlexDirection.Column;
  }

  getItemSpace() {
    if (this.isColumnDirection()) {
      return LengthMetrics.resource($r('sys.float.padding_level1'));
    }
    return LengthMetrics.vp(this.itemRowSpace);
  }

  build() {
    Flex({
      space: { main: this.getItemSpace() },
      direction: this.itemDirection,
      justifyContent: FlexAlign.Start,
      alignItems: this.isColumnDirection() ? ItemAlign.Start : ItemAlign.Center,
    }) {
      this.createIcon()
      this.createText()
    }
    .margin({
      end: this.isParentColumnDirection() ?
      LengthMetrics.vp(0) :
      LengthMetrics.vp(16)
    })
    .padding({ start: LengthMetrics.vp(LISTITEM_PADDING) })
    .width(this.isParentColumnDirection() ? undefined : this.leftWidth)
    .flexShrink(this.isParentColumnDirection() ? 0 : 1)
  }
}

class CreateIconParam {
  public icon?: OperateIcon;
}

@Component
struct OperateItemStruct {
  @Prop @Watch('onPropChange') arrow: OperateIcon | null = null;
  @Prop @Watch('onPropChange') icon: OperateIcon | null = null;
  @Prop @Watch('onPropChange') subIcon: OperateIcon | null = null;
  @Prop @Watch('onPropChange') button: OperateButton | null = null;
  @Prop @Watch('onPropChange') switch: OperateCheck | null = null;
  @Prop @Watch('onPropChange') checkBox: OperateCheck | null = null;
  @Prop @Watch('onPropChange') radio: OperateCheck | null = null;
  @Prop @Watch('onPropChange') image: ResourceStr | null = null;
  @Prop @Watch('onPropChange') text: ResourceStr | null = null;
  @State switchState: boolean = false
  @State radioState: boolean = false
  @State checkBoxState: boolean = false
  @Prop rightWidth: string = RIGHT_PART_WIDTH;
  @State secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @State hoveringColor: ResourceColor = '#0d000000';
  @State activedColor: ResourceColor = '#1a0a59f7';
  @Link parentCanFocus: boolean
  @Link parentCanTouch: boolean
  @Link parentIsHover: boolean
  @Link parentCanHover: boolean
  @Link parentIsActive: boolean
  @Link parentFrontColor: ResourceColor;
  @Link parentDirection: FlexDirection;
  @State rowSpace: number = DEFAULT_ROW_SPACE;
  @Link @Watch('onFocusChange') isFocus: boolean;
  @State secondaryTextSize: Length = $r('sys.float.composeListItem_normal_right_text_size');
  @State secondaryTextColors: ResourceColor = $r('sys.color.composeListItem_normal_right_text_color');
  @State iconColor: ResourceColor = $r('sys.color.composeListItem_normal_right_icon_color');
  @Link @Watch('onPropChange') isChecked: boolean;

  onWillApplyTheme(theme: Theme): void {
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.hoveringColor = theme.colors.interactiveHover;
    this.activedColor = theme.colors.interactiveActive;
  }

  onFocusChange() {
    this.secondaryTextSize = this.isFocus ? $r('sys.float.composeListItem_focused_right_text_size') : $r('sys.float.composeListItem_normal_right_text_size');
    this.secondaryTextColors = this.isFocus ? $r('sys.color.composeListItem_focused_right_text_color') : this.secondaryTextColor;
    this.iconColor = this.isFocus ? $r('sys.color.composeListItem_focused_right_icon_color') : $r('sys.color.composeListItem_normal_right_icon_color');
  }

  onPropChange() {
    if (this.switch != null) {
      this.switchState = IS_CLOSE_CHILD_FOCUS ? this.switch.isCheck as boolean : this.isChecked;
    }
    if (this.radio != null) {
      this.radioState = IS_CLOSE_CHILD_FOCUS ? this.radio.isCheck as boolean : this.isChecked;
    }
    if (this.checkBox != null) {
      this.checkBoxState = IS_CLOSE_CHILD_FOCUS ? this.checkBox.isCheck as boolean : this.isChecked;
    }

    if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
      (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
      this.rowSpace = SPECICAL_ROW_SPACE;
    } else {
      this.rowSpace = DEFAULT_ROW_SPACE;
    }
  }

  getUnselectedColor(): ResourceColor {
    if (IS_CLOSE_CHILD_FOCUS) {
      return DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
    }
    return this.isFocus ? OPERATE_ITECOLOR : DEFUALT_RADIO_CHECKBOX_BORDER_COLOR;
  }

  aboutToAppear() {
    if (this.switch !== null) {
      this.isChecked = this.switch.isCheck as boolean;
    }
    if (this.radio !== null) {
      this.isChecked = this.radio.isCheck as boolean;
    }
    if (this.checkBox !== null) {
      this.isChecked = this.checkBox.isCheck as boolean;
    }
    this.onPropChange();
    this.onFocusChange();
  }

  @Builder
  createButton() {
    Button() {
      Row() {
        Text(this.button?.text as ResourceStr)
          .focusable(true)
      }
      .padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      })
    }
    .padding({ top: 0, bottom: 0 })
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    .hitTestBehavior(HitTestMode.Block)
    .fontSize($r('sys.float.ohos_id_text_size_button3'))
    .fontColor($r('sys.color.ohos_id_color_text_primary_activated_transparent'))
    .constraintSize({
      minHeight: BUTTON_SIZE
    })
    .backgroundColor($r('sys.color.ohos_id_color_button_normal'))
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        this.parentCanTouch = false;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.parentCanTouch = true;
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
      }
    })
  }

  @Builder
  createIcon(param: CreateIconParam) {
    Button({ type: ButtonType.Normal }) {
      Image(param.icon?.value)
        .height(OPERATEITEM_ICONLIKE_SIZE)
        .width(OPERATEITEM_ICONLIKE_SIZE)
        .focusable(true)
        .fillColor(this.iconColor)
        .draggable(false)
    }
    .shadow(CLEAR_SHADOW)
    .hitTestBehavior(HitTestMode.Block)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        this.parentCanTouch = false;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.parentCanTouch = true;
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
      }
    })
    .onClick(param.icon?.action)
    .flexShrink(0)
  }

  @Builder
  createImage() {
    Image(this.image)
      .height(OPERATEITEM_IMAGE_SIZE)
      .width(OPERATEITEM_IMAGE_SIZE)
      .draggable(false)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
  }

  @Builder
  createText() {
    Text(this.text)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .fontSize(this.secondaryTextSize)
      .fontColor(this.secondaryTextColors)
      .textOverflow({
        overflow: LengthMetrics.resource($r('sys.float.composeListItem_right_textOverflow'))
          .value === MARQUEE ? TextOverflow.MARQUEE : TextOverflow.None
      })
      .marqueeOptions({
        start: this.isFocus,
        fadeout: true
      })
      .maxLines(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value)
      .focusable(true)
      .draggable(false)
      .flexShrink(1)
  }

  @Builder
  createArrow() {
    Button({ type: ButtonType.Normal }) {
      Image(this.arrow?.value)
        .height(OPERATEITEM_ICONLIKE_SIZE)
        .width(OPERATEITEM_ARROW_WIDTH)
        .focusable(true)
        .fillColor(IS_CLOSE_CHILD_FOCUS ? $r('sys.color.ohos_id_color_fourth') : this.iconColor)
        .draggable(false)
        .matchTextDirection(true)
    }
    .shadow(CLEAR_SHADOW)
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    .hitTestBehavior(HitTestMode.Transparent)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICONLIKE_SIZE)
    .width(OPERATEITEM_ARROW_WIDTH)
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .stateEffect(this.arrow?.action !== undefined)
    .onTouch((event: TouchEvent) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.parentCanTouch = false;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.parentCanTouch = true;
      }
    })
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      this.parentCanHover = false
      if (isHover && IS_CLOSE_CHILD_FOCUS) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
      }
    })
    .onClick(this.arrow?.action)
  }

  @Builder
  createRadio() {
    Radio({ value: '', group: '' })
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .checked(this.radioState)
      .radioStyle({
        uncheckedBorderColor: this.getUnselectedColor()
      })
      .backgroundColor(this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString())
      .borderRadius(OPERATE_ITEM_RADIUS)
      .onChange((isCheck: boolean) => {
        this.radioState = isCheck;
        if (!IS_CLOSE_CHILD_FOCUS) {
          this.isChecked = isCheck;
        }
        if (this.radio?.onChange) {
          this.radio?.onChange(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false;
      })
      .hitTestBehavior(HitTestMode.Block)
      .onTouch((event: TouchEvent) => {
        if (!event) {
          return;
        }
        if (event.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          this.parentCanTouch = true;
        }
      })
      .onHover((isHover: boolean) => {
        this.parentCanHover = false
        if (isHover && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!isHover) {
          this.parentCanHover = true
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      })
  }

  @Builder
  createCheckBox() {
    Checkbox()
      .borderRadius(IS_CLOSE_CHILD_FOCUS ? UNUSUAL : OPERATE_ITEM_RADIUS)
      .unselectedColor(this.getUnselectedColor())
      .backgroundColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString())
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .select(this.checkBoxState)
      .onChange((isCheck: boolean) => {
        this.checkBoxState = isCheck;
        if (!IS_CLOSE_CHILD_FOCUS) {
          this.isChecked = isCheck;
        }
        if (this.checkBox?.onChange) {
          this.checkBox?.onChange(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false;
      })
      .hitTestBehavior(HitTestMode.Block)
      .onTouch((event: TouchEvent) => {
        if (event.type === TouchType.Down) {
          this.parentCanTouch = false;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          this.parentCanTouch = true;
        }
      })
      .onHover((isHover: boolean) => {
        this.parentCanHover = false
        if (isHover && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!isHover) {
          this.parentCanHover = true
          if (this.parentIsHover) {
            this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
          }
        }
      })
  }

  @Builder
  createSwitch() {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.switchState })
        .borderRadius(IS_CLOSE_CHILD_FOCUS ? UNUSUAL : OPERATE_ITEM_RADIUS)
        .backgroundColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus ? OPERATE_ITEM_BACKGROUND_COLOR : Color.Transparent.toString())
        .switchPointColor(!IS_CLOSE_CHILD_FOCUS && this.isFocus && !this.switchState ? OPERATE_ITECOLOR : UNUSUAL)
        .onChange((isCheck: boolean) => {
          this.switchState = isCheck;
          if (!IS_CLOSE_CHILD_FOCUS) {
            this.isChecked = isCheck;
          }
          if (this.switch?.onChange) {
            this.switch?.onChange(isCheck);
          }
        })
        .hitTestBehavior(HitTestMode.Block)
    }
    .margin({ end: LengthMetrics.vp(SWITCH_PADDING) })
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .justifyContent(FlexAlign.Center)
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .onTouch((event: TouchEvent) => {
      if (event.type === TouchType.Down) {
        this.parentCanTouch = false;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.parentCanTouch = true;
      }
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_CLOSE_CHILD_FOCUS) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
      }
    })
  }

  @Builder
  createTextArrow() {
    Button({ type: ButtonType.Normal }) {
      if(this.parentDirection === FlexDirection.Column) {
        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Text(this.text)
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontColor($r('sys.color.ohos_id_color_text_secondary'))
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            })
          Image(this.arrow?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ARROW_WIDTH)
            .fillColor($r('sys.color.ohos_id_color_fourth'))
            .focusable(false)
            .draggable(false)
        }
        .padding({
          start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
          end: LengthMetrics.vp(LISTITEM_PADDING)
        })
      }else {
        Row({ space: SPECICAL_ROW_SPACE }) {
          Text(this.text)
            .fontSize(this.secondaryTextSize)
            .fontColor(this.secondaryTextColors)
            .textOverflow({
              overflow: LengthMetrics.resource($r('sys.float.composeListItem_right_textOverflow'))
                .value === MARQUEE ? TextOverflow.MARQUEE : TextOverflow.None
            })
            .marqueeOptions({
              start: this.isFocus,
              fadeout: true
            })
            .maxLines(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value)
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            })
          Image(this.arrow?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ARROW_WIDTH)
            .fillColor(IS_CLOSE_CHILD_FOCUS ? $r('sys.color.icon_fourth') : this.iconColor)
            .focusable(false)
            .draggable(false)
        }
        .padding({
          start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
          end: LengthMetrics.vp(LISTITEM_PADDING)
        })
      }
    }
    .shadow(CLEAR_SHADOW)
    .hitTestBehavior(HitTestMode.Transparent)
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .backgroundColor(Color.Transparent)
    .constraintSize({ minHeight: TEXT_ARROW_HEIGHT })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .padding({
      top: 0,
      bottom: 0,
      left: 0,
      right: 0
    })
    .stateEffect(this.arrow?.action !== undefined)
    .onTouch((event: TouchEvent) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.parentCanTouch = false;
      }
      if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
        this.parentCanTouch = true;
      }
    })
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      this.parentCanHover = false
      if (isHover && IS_CLOSE_CHILD_FOCUS) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
      }
    })
    .onClick(this.arrow?.action)
  }

  getFlexOptions(): FlexOptions {
    let flexOptions: FlexOptions = { alignItems: ItemAlign.Center };
    if (this.parentDirection === FlexDirection.Column) {
      flexOptions.justifyContent = FlexAlign.SpaceBetween;
    } else {
      flexOptions.space = { main: LengthMetrics.vp(this.rowSpace) };
      flexOptions.justifyContent = FlexAlign.End;
    }
    return flexOptions;
  }

  build() {
    Flex(this.getFlexOptions()) {
      if (this.button != null) {
        this.createButton();
      } else if (this.image != null) {
        this.createImage()
      } else if (this.icon != null && this.text != null) {
        this.createText()
        this.createIcon({ icon: this.icon })
      } else if (this.arrow != null && this.text == null) {
        this.createArrow()
      } else if (this.arrow != null && this.text != null) {
        this.createTextArrow();
      } else if (this.text != null) {
        this.createText()
      } else if (this.radio != null) {
        this.createRadio()
      } else if (this.checkBox != null) {
        this.createCheckBox()
      } else if (this.switch != null) {
        this.createSwitch()
      } else if (this.icon != null) {
        this.createIcon({ icon: this.icon })
        if (this.subIcon != null) {
          this.createIcon({ icon: this.subIcon });
        }
      }
    }
    .width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth)
  }
}

@Component
export struct ComposeListItem_hebin {
  @Prop @Watch('onPropChange') contentItem: ContentItem | null = null;
  @Prop @Watch('onPropChange') operateItem: OperateItem | null = null;
  @State frontColor: ResourceColor = $r('sys.color.composeListItem_color_background_normal');
  @State borderSize: number = 0;
  @State canFocus: boolean = false
  @State canTouch: boolean = true
  @State canHover: boolean = true
  @State isHover: boolean = true
  @State itemHeight: number = ItemHeight.FIRST_HEIGHT;
  @State isActive: boolean = false
  @State hoveringColor: ResourceColor = '#0d000000';
  @State touchDownColor: ResourceColor = '#1a000000';
  @State activedColor: ResourceColor = '#1a0a59f7';
  @State focusOutlineColor: ResourceColor = $r('sys.color.ohos_id_color_focused_outline');
  @State @Watch('onFontSizeScaleChange') fontSizeScale: number = 1;
  @State containerDirection: FlexDirection = FlexDirection.Row;
  @State contentItemDirection: FlexDirection = FlexDirection.Row;
  @State containerPadding?: Padding | LocalizedPadding | Length = undefined;
  @State textArrowLeftSafeOffset: number = 0;
  private isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
  private maxFontScale = this.getUIContext().getMaxFontScale();
  @State isFocus: boolean = false;
  @State isChecked: boolean = false;

  onWillApplyTheme(theme: Theme): void {
    this.hoveringColor = theme.colors.interactiveHover;
    this.touchDownColor = theme.colors.interactivePressed;
    this.activedColor = theme.colors.interactiveActive;
    this.focusOutlineColor = theme.colors.interactiveFocus;
  }

  onPropChange() {
    if (this.contentItem === undefined) {
      if (this.operateItem?.image !== undefined ||
        this.operateItem?.icon !== undefined ||
        this.operateItem?.subIcon !== undefined) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING
      }
      return
    }

    if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
      if (this.contentItem?.icon === undefined) {
        this.itemHeight = ItemHeight.FIRST_HEIGHT
      } else {
        this.itemHeight = this.contentItem.iconStyle as number <= IconType.HEAD_SCULPTURE ?
        ItemHeight.SECOND_HEIGHT : (LengthMetrics.resource($r('sys.float.composeListItem_system_icon_line_height')).value);
      }
    } else if (this.contentItem.description === undefined) {
      if (this.contentItem.icon === undefined ||
        (this.contentItem.icon !== undefined && this.contentItem.iconStyle as number <= IconType.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT
      } else {
        this.itemHeight = ItemHeight.FOURTH_HEIGHT
      }
    } else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT
    }

    if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number) as number >= this.itemHeight) {
      this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number) as number + SAFE_LIST_PADDING;
    }
  }

  aboutToAppear() {
    this.onPropChange();
    if (IS_CLOSE_CHILD_FOCUS) return;
    this.onFontSizeScaleChange();
  }

  calculatedLeftWidth(): string {
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return RIGHT_CONTENT_NULL_LEFTWIDTH
    } else if (this.operateItem?.arrow != null && this.operateItem?.text == null) {
      return LEFT_ONLY_ARROW_WIDTH
    } else {
      return LEFT_PART_WIDTH
    }
  }

  calculatedRightWidth(): string {
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return RIGHT_CONTENT_NULL_RIGHTWIDTH
    } else if (this.operateItem?.arrow != null && this.operateItem?.text == null) {
      return RIGHT_ONLY_ARROW_WIDTH
    } else {
      return RIGHT_PART_WIDTH
    }
  }

  decideContentItemDirection(): FlexDirection {
    if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 &&
      this.contentItem?.iconStyle && this.contentItem?.iconStyle > IconType.HEAD_SCULPTURE) {
      return FlexDirection.Column;
    }
    return FlexDirection.Row;
  }

  decideContainerDirection(): FlexDirection {
    if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItem) {
      return FlexDirection.Row;
    }
    if (this.operateItem?.button) {
      return FlexDirection.Column;
    } else if (this.operateItem?.image) {
      return FlexDirection.Row;
    } else if (this.operateItem?.icon && this.operateItem?.text) {
      return FlexDirection.Column;
    } else if (this.operateItem?.arrow) {
      if (!this.operateItem?.text) {
        return FlexDirection.Row;
      }
      this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
      return FlexDirection.Column;
    } else if (this.operateItem?.text) {
      return FlexDirection.Column;
    } else {
      return FlexDirection.Row;
    }
  }

  setContainerPadding(top: Resource, bottom: Resource) {
    this.containerPadding = {
      top: LengthMetrics.resource(top),
      end: LengthMetrics.resource($r('sys.float.titlebar_icon_background_width')),
      bottom: LengthMetrics.resource(bottom),
      start: LengthMetrics.resource($r('sys.float.titlebar_icon_background_width')),
    };
  }

  getContainerPadding() {
    if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
      this.setContainerPadding($r('sys.float.composeListItem_single_line_list_left_text_top3'), $r('sys.float.composeListItem_single_line_list_left_text_bottom3'));
    } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
      this.setContainerPadding($r('sys.float.composeListItem_single_line_list_left_text_top2'), $r('sys.float.composeListItem_single_line_list_left_text_bottom2'));
    } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
      this.setContainerPadding($r('sys.float.composeListItem_single_line_list_left_text_top1'), $r('sys.float.composeListItem_single_line_list_left_text_bottom1'));
    } else {
      this.containerPadding = undefined;
      if (IS_CLOSE_CHILD_FOCUS) return;
      this.setContainerPadding($r('sys.float.composeListItem_single_line_list_left_text_top'), $r('sys.float.composeListItem_single_line_list_left_text_bottom'))
    }
  }

  onFontSizeScaleChange() {
    this.containerDirection = this.decideContainerDirection();
    this.contentItemDirection = this.decideContentItemDirection();
    this.getContainerPadding();
  }

  isSingleLine(): boolean {
    return !this.contentItem?.secondaryText && !this.contentItem?.description;
  }

  getOperateOffset(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Row) {
      return LengthMetrics.vp(0);
    }
    let iconSize = ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number);
    if (this.contentItem?.icon && iconSize && iconSize <= HEADSCULPTURE_SIZE) {
      return LengthMetrics.vp(iconSize + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
    }
    return LengthMetrics.vp(LISTITEM_PADDING - this.textArrowLeftSafeOffset);
  }

  getMainSpace(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Column) {
      return LengthMetrics.resource(this.isSingleLine() ? $r('sys.float.padding_level1') : $r('sys.float.padding_level8'));
    }
    return LengthMetrics.vp(0);
  }

  getFlexOptions(): FlexOptions {
    if (this.containerDirection === FlexDirection.Column) {
      return {
        space: { main: this.getMainSpace() },
        justifyContent: FlexAlign.Center,
        alignItems: ItemAlign.Start,
        direction: this.containerDirection,
      };
    }
    return {
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Center,
      direction: this.containerDirection,
    };
  }

  decideFontSizeScale(): number {
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(
      this.maxFontScale,
      (this.getUIContext().getHostContext() as common.UIAbilityContext)?.config.fontSizeScale ?? 1
    )
  }

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    this.fontSizeScale = this.decideFontSizeScale();
    let sizeResult: SizeResult = { height: 0, width: 0 };
    children.forEach((child) => {
      let childMeasureResult: MeasureResult = child.measure(constraint);
      sizeResult.width = childMeasureResult.width;
      sizeResult.height = childMeasureResult.height;
    });
    return sizeResult;
  }

  build() {
    Stack() {
      Flex(this.getFlexOptions()) {
        if (this.contentItem === null) {
          ContentItemStruct({})
        }
        if (this.contentItem !== null) {
          ContentItemStruct({
            icon: this.contentItem?.icon,
            iconStyle: this.contentItem?.iconStyle,
            primaryText: this.contentItem?.primaryText,
            secondaryText: this.contentItem?.secondaryText,
            description: this.contentItem?.description,
            leftWidth: this.calculatedLeftWidth(),
            fontSizeScale: this.fontSizeScale,
            parentDirection: this.containerDirection,
            itemDirection: this.contentItemDirection,
            isFocus: this.isFocus,
            itemHeight: this.itemHeight,
          });
        }
        if (this.operateItem !== null) {
          OperateItemStruct({
            icon: this.operateItem?.icon,
            subIcon: this.operateItem?.subIcon,
            button: this.operateItem?.button,
            switch: this.operateItem?.switch,
            checkBox: this.operateItem?.checkbox,
            radio: this.operateItem?.radio,
            image: this.operateItem?.image,
            text: this.operateItem?.text,
            arrow: this.operateItem?.arrow,
            parentCanFocus: this.canFocus,
            parentCanTouch: this.canTouch,
            parentIsHover: this.isHover,
            parentFrontColor: this.frontColor,
            parentIsActive: this.isActive,
            parentCanHover: this.canHover,
            rightWidth: this.calculatedRightWidth(),
            parentDirection: this.containerDirection,
            isFocus: this.isFocus,
            isChecked: this.isChecked,
          })
            .flexShrink(0)
            .onFocus(() => {
              this.canFocus = false
            })
            .onBlur(() => {
              this.canFocus = true
            }).padding({start: this.getOperateOffset()});
        }
      }
      .constraintSize({
        minHeight: this.itemHeight
      })
      .focusable(IS_CLOSE_CHILD_FOCUS)
      .borderRadius($r('sys.float.composeListItem_normal_radio'))
      .backgroundColor(this.frontColor)
      .onFocus(() => {
        this.canFocus = true
      })
      .onBlur(() => {
        this.canFocus = false
      })
      .onHover((isHover: boolean) => {
        if (this.isFocus && !IS_CLOSE_CHILD_FOCUS) {
          this.isHover = false;
          return;
        }
        this.isHover = isHover
        if (this.canHover) {
          this.frontColor = isHover ? this.hoveringColor :
            (this.isActive ? this.activedColor : Color.Transparent.toString());
        }
        if (!IS_CLOSE_CHILD_FOCUS) {
          this.frontColor = isHover ? this.hoveringColor : $r('sys.color.composeListItem_color_background_normal');
        }
      })
      .onTouch((event: TouchEvent) => {
        if (this.isFocus && !IS_CLOSE_CHILD_FOCUS) {
          return;
        }
        if (event.type === TouchType.Down && this.canTouch) {
          this.frontColor = this.touchDownColor;
        }
        if (event.type === TouchType.Up || event.type === TouchType.Cancel) {
          this.frontColor = this.isActive ? this.activedColor : $r('sys.color.composeListItem_color_background_normal');
        }
      })
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.composeListItem_focused_circular_bead'),
            width: ITEM_BORDER_SHOWN,
            color: this.focusOutlineColor,
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.composeListItem_normal_radio'),
            color: $r('sys.color.composeListItem_normal_stroke_color'),
            width: $r('sys.float.composeListItem_normal_stroke_thickness'),
          })
        }
      }).padding(this.containerPadding)
    }
    .onFocus(() => {
      this.isFocus = true;
      this.frontColor = $r('sys.color.composeListItem_focused_backboard');
    })
    .onBlur(() => {
      this.isFocus = false;
      this.frontColor = $r('sys.color.composeListItem_color_background_normal');
    })
    .borderRadius($r('sys.float.composeListItem_normal_radio'))
    .onClick(() => {
      if (!IS_CLOSE_CHILD_FOCUS) {
        this.isChecked = this.operateItem?.radio ? true : !this.isChecked;
        if (this.operateItem?.icon && this.operateItem.icon?.action) {
          this.operateItem.icon.action();
        }
        if (this.operateItem?.subIcon && this.operateItem.subIcon?.action) {
          this.operateItem.subIcon.action();
        }
        if (this.operateItem?.arrow && this.operateItem.arrow?.action) {
          this.operateItem.arrow.action();
        }
      }
    })
    .scale({
      x: this.isFocus ? LengthMetrics.resource($r('sys.float.composeListItem_focused_magnification'))
        .value : RECOVER_YSCALE,
      y: this.isFocus ? LengthMetrics.resource($r('sys.float.composeListItem_focused_magnification'))
        .value : RECOVER_YSCALE
    })
    .shadow(this.isFocus ? LengthMetrics.resource($r('sys.float.composeListItem_focused_shadow_attribute'))
      .value as ShadowStyle : LengthMetrics.resource($r('sys.float.composeListItem_normal_shadow_attribute'))
      .value as ShadowStyle)
    .padding({
      left: STACK_PADDING,
      right: STACK_PADDING
    })
  }
}
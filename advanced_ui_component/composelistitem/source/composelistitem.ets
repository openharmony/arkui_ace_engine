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
import { TextModifier, ImageModifier } from '@ohos.arkui.modifier';
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

enum ItemHeight {
  FIRST_HEIGHT = 48,
  SECOND_HEIGHT = 56,
  THIRD_HEIGHT = 64,
  FOURTH_HEIGHT = 72,
  FIFTH_HEIGHT = 96
}

enum FontSizeScaleLevel {
  LEVEL1 = 1.75,
  LEVEL2 = 2,
  LEVEL3 = 3.2
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
  public iconImageModifier?: ImageModifier;
  public primaryTextModifier?: TextModifier;
  public secondaryTextModifier?: TextModifier;
  public descriptionModifier?: TextModifier;
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
const STACK_PADDING = 12;
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
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const HOVERING_COLOR = '#0d000000';
const ACTIVED_COLOR = '#1a0a59f7';
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const DEFAULT_ITEM_SPACE_WIDTH = 12;
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
  @Prop @Watch('onPropChange') iconStyle: IconType | null = null;
  @Prop @Watch('onPropChange') icon: ResourceStr | null = null;
  @Prop @Watch('onPropChange') primaryText: ResourceStr | null = null;
  @Prop @Watch('onPropChange') secondaryText: ResourceStr | null = null;
  @Prop @Watch('onPropChange') description: ResourceStr | null = null;
  private itemRowSpace: number = NORMAL_ITEM_ROW_SPACE
  @Prop leftWidth: string = LEFT_PART_WIDTH;
  @State primaryTextColor: ResourceColor = $r('sys.color.font_primary');
  @State secondaryTextColor: ResourceColor = $r('sys.color.font_secondary');
  @State descriptionColor: ResourceColor = $r('sys.color.font_tertiary');
  @Prop iconImageModifier: ImageModifier | null = null;
  @Prop primaryTextModifier: TextModifier | null = null;
  @Prop secondaryTextModifier: TextModifier | null = null;
  @Prop descriptionModifier: TextModifier | null = null;
  @Prop contentItemPadding: LocalizedPadding | null = null;
  @Prop itemSpace: number = DEFAULT_ITEM_SPACE_WIDTH;
  @Prop fontSizeScale: number;
  @Prop parentDirection: FlexDirection;
  @Prop itemDirection: FlexDirection;

  onWillApplyTheme(theme: Theme): void {
    this.primaryTextColor = theme.colors.fontPrimary;
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.descriptionColor = theme.colors.fontTertiary;
  }

  onPropChange() {
    if (this.icon == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    }
  }

  aboutToAppear() {
    this.onPropChange();
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
          .fillColor($r('sys.color.icon_primary'))
          .attributeModifier(this.iconImageModifier)
          .flexShrink(0);
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
          .focusable(true)
          .draggable(false)
          .fillColor($r('sys.color.icon_primary'))
          .attributeModifier(this.iconImageModifier)
          .flexShrink(0);
      }
    }
  }

  @Builder
  createText() {
    Column({ space: TEXT_COLUMN_SPACE }) {
      Text(this.primaryText)
        .fontSize($r('sys.float.ohos_id_text_size_body1'))
        .fontColor(this.primaryTextColor)
        .fontWeight(FontWeight.Medium)
        .focusable(true)
        .draggable(false)
        .attributeModifier(this.primaryTextModifier);
      if (this.secondaryText != null) {
        Text(this.secondaryText)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor(this.secondaryTextColor)
          .focusable(true)
          .draggable(false)
          .attributeModifier(this.secondaryTextModifier);
      }
      if (this.description != null) {
        Text(this.description)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor(this.descriptionColor)
          .focusable(true)
          .draggable(false)
          .attributeModifier(this.descriptionModifier);
      }
    }
    .flexShrink(1)
    .alignItems(HorizontalAlign.Start)
  }

  isColumnDirection() {
    return this.itemDirection === FlexDirection.Column;
  }

  getItemSpace() {
    if (this.isColumnDirection()) {
      return LengthMetrics.vp(2);
    }
    return LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH)
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
      end: this.parentDirection === FlexDirection.Column ?
      LengthMetrics.vp(0) : LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH)
    })
    .constraintSize({ minWidth: this.leftWidth })
    .flexShrink(1)
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
  @State secondaryTextColor: ResourceColor = $r('sys.color.font_secondary');
  @State hoveringColor: ResourceColor = '#0d000000';
  @State activedColor: ResourceColor = '#1a0a59f7';
  @Link parentCanFocus: boolean
  @Link parentCanTouch: boolean
  @Link parentIsHover: boolean
  @Link parentCanHover: boolean
  @Link parentIsActive: boolean
  @Link parentFrontColor: ResourceColor;
  @Link isParentCanTouch: boolean;
  @Prop parentDirection: FlexDirection;
  private rowSpace: number = DEFAULT_ROW_SPACE
  static RIGHT_ITEM_OFFSET_LEVEL1 = 0;
  static RIGHT_ITEM_OFFSET_LEVEL2 = -8;

  onWillApplyTheme(theme: Theme): void {
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.hoveringColor = theme.colors.interactiveHover;
    this.activedColor = theme.colors.interactiveActive;
  }

  onPropChange() {
    if (this.switch != null) {
      this.switchState = this.switch.isCheck as boolean;
    }
    if (this.radio != null) {
      this.radioState = this.radio.isCheck as boolean;
    }
    if (this.checkBox != null) {
      this.checkBoxState = this.checkBox.isCheck as boolean;
    }
    if ((this.button == null && this.image == null && this.icon != null && this.text != null) ||
      (this.button == null && this.image == null && this.icon == null && this.arrow != null && this.text != null)) {
      this.rowSpace = SPECICAL_ROW_SPACE;
    }
  }

  aboutToAppear() {
    this.onPropChange();
  }

  @Builder
  createButton() {
    Button() {
      Row() {
        Text(this.button?.text as ResourceStr)
          .focusable(true)
      }
      .padding({
        left: $r('sys.float.padding_level4'),
        right: $r('sys.float.padding_level4')
      })
    }
    .hitTestBehavior(HitTestMode.Block)
    .buttonStyle(ButtonStyleMode.NORMAL)
    .controlSize(ControlSize.SMALL)
    .constraintSize({
      minHeight: BUTTON_SIZE
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
      if (isHover && this.parentFrontColor === HOVERING_COLOR) {
        this.parentFrontColor = this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true
        if (this.parentIsHover) {
          this.parentFrontColor = this.parentIsHover ? HOVERING_COLOR :
            (this.parentIsActive ? ACTIVED_COLOR : Color.Transparent.toString());
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
        .fillColor($r('sys.color.icon_primary'))
        .draggable(false)
    }
    .margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL2) })
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
      if (isHover && this.parentFrontColor === this.hoveringColor) {
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
    .onAppear(()=>{
      this.isParentCanTouch = true;
    })
    .onClick(param.icon?.action)
  }

  @Builder
  createImage() {
    Image(this.image)
      .height(OPERATEITEM_IMAGE_SIZE)
      .width(OPERATEITEM_IMAGE_SIZE)
      .draggable(false)
      .onAppear(()=>{
        this.isParentCanTouch = true;
      })
  }

  @Builder
  createText() {
    Text(this.text)
      .fontSize($r('sys.float.ohos_id_text_size_body2'))
      .fontColor(this.secondaryTextColor)
      .focusable(true)
      .draggable(false)
      .flexShrink(1)
      .onAppear(()=>{
        this.isParentCanTouch = true;
      })
  }

  @Builder
  createArrow() {
    Button({ type: ButtonType.Normal }) {
      Image(this.arrow?.value)
        .height(OPERATEITEM_ICONLIKE_SIZE)
        .width(OPERATEITEM_ARROW_WIDTH)
        .focusable(true)
        .fillColor($r('sys.color.icon_fourth'))
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
      if (isHover && this.parentFrontColor === this.hoveringColor) {
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
    .onAppear(()=>{
      this.isParentCanTouch = true;
    })
    .onClick(this.arrow?.action)
  }

  @Builder
  createRadio() {
    Radio({ value: '', group: '' })
      .margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) })
      .checked(this.radioState)
      .onChange(this.radio?.onChange)
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
        if (isHover && this.parentFrontColor === this.hoveringColor) {
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
      .onAppear(()=>{
        this.isParentCanTouch = true;
      })
  }

  @Builder
  createCheckBox() {
    Checkbox()
      .margin({ end: LengthMetrics.vp(OperateItemStruct.RIGHT_ITEM_OFFSET_LEVEL1) })
      .select(this.checkBoxState)
      .onChange(this.checkBox?.onChange)
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
        if (isHover && this.parentFrontColor === this.hoveringColor) {
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
      .onAppear(()=>{
        this.isParentCanTouch = true;
      })
  }

  @Builder
  createSwitch() {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.switchState })
        .onChange(this.switch?.onChange)
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
      if (isHover && this.parentFrontColor === this.hoveringColor) {
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
      Row({ space: SPECICAL_ROW_SPACE }) {
        Text(this.text)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor($r('sys.color.font_secondary'))
          .focusable(true)
          .draggable(false)
          .constraintSize({
            maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
          })
        Image(this.arrow?.value)
          .height(OPERATEITEM_ICONLIKE_SIZE)
          .width(OPERATEITEM_ARROW_WIDTH)
          .fillColor($r('sys.color.icon_fourth'))
          .focusable(true)
          .draggable(false)
      }
    }
    .hitTestBehavior(HitTestMode.Block)
    .backgroundColor(Color.Transparent)
    .borderRadius($r('sys.float.corner_radius_level8'))
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
      if (isHover && this.parentFrontColor === this.hoveringColor) {
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
    .onAppear(()=>{
      this.isParentCanTouch = true;
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
        this.createImage();
      } else if (this.icon != null && this.text != null) {
        this.createText();
        this.createIcon({icon: this.icon});
      } else if (this.arrow != null && this.text == null) {
        this.createArrow();
      } else if (this.arrow != null && this.text != null) {
        if (this.parentDirection === FlexDirection.Column) {
          Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
            this.createText();
            this.createIcon({icon: this.arrow});
          }.flexShrink(0);
        } else {
          this.createTextArrow();
        }
      } else if (this.text != null) {
        this.createText();
      } else if (this.radio != null) {
        this.createRadio();
      } else if (this.checkBox != null) {
        this.createCheckBox();
      } else if (this.switch != null) {
        this.createSwitch();
      } else if (this.icon != null) {
        this.createIcon({icon: this.icon});
        if (this.subIcon != null) {
          this.createIcon({icon: this.subIcon});
        }
      }
    }
    .flexShrink(1)
    .constraintSize({ minWidth: this.rightWidth });
  }
}

@Component
export struct ComposeListItem {
  @Prop @Watch('onPropChange') contentItem: ContentItem | null = null;
  @Prop @Watch('onPropChange') operateItem: OperateItem | null = null;
  @Prop itemSpace: number = DEFAULT_ITEM_SPACE_WIDTH;
  @Prop composeItemPadding: LocalizedPadding | null = null;
  @State frontColor: ResourceColor = Color.Transparent.toString();
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
  @State isCanTouch: boolean = false;
  @State @Watch('onFontSizeScaleChange') fontSizeScale: number = 1;
  @State containerDirection: FlexDirection = FlexDirection.Row;
  @State contentItemDirection: FlexDirection = FlexDirection.Row;
  @State containerPadding: Padding = {
    top: $r('sys.float.padding_level8'),
    bottom: $r('sys.float.padding_level8')
  }
  private callbackId: number = -1;

  onWillApplyTheme(theme: Theme): void {
    this.hoveringColor = theme.colors.interactiveHover;
    this.touchDownColor = theme.colors.interactivePressed;
    this.activedColor = theme.colors.interactiveActive;
    this.focusOutlineColor = theme.colors.interactiveFocus;
  }

  onPropChange() {
    this.onFontSizeScaleChange();
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
        ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
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
  }

  calculatedLeftWidth(): string {
    let leftPaddingWidth = this.composeItemPadding?.start?.value ?? STACK_PADDING;
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return `calc(100% - ${leftPaddingWidth}vp)`;
    } else if (this.operateItem !== null &&
      this.operateItem.button === undefined &&
      this.operateItem.text === undefined) {
      if (this.operateItem.subIcon !== null) {
        return `calc(100% - ${leftPaddingWidth}vp - ${OPERATEITEM_ICON_CLICKABLE_SIZE}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
      } else {
        return `calc(100% - ${leftPaddingWidth}vp - ${RIGHT_ONLY_ARROW_WIDTH})`;
      }
    } else {
      return `calc(66% - ${leftPaddingWidth}vp)`;
    }
  }

  calculatedRightWidth(): string {
    let rightPaddingWidth =
      this.composeItemPadding?.end !== undefined ? this.composeItemPadding?.end?.value : STACK_PADDING;
    if (this.operateItem === null || JSON.stringify(this.operateItem) === '{}') {
      return RIGHT_CONTENT_NULL_RIGHTWIDTH;
    } else if (this.operateItem !== null && this.operateItem.text === undefined) {
      if (this.operateItem.subIcon !== null) {
        return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${RIGHT_ONLY_ARROW_WIDTH} + ${rightPaddingWidth}vp)`;
      } else {
        return `calc(${RIGHT_ONLY_ARROW_WIDTH} + ${rightPaddingWidth}vp)`;
      }
    } else {
      return RIGHT_PART_WIDTH;
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
    if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1) {
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
      return FlexDirection.Column;
    } else if (this.operateItem?.text) {
      return FlexDirection.Column;
    } else {
      return FlexDirection.Row;
    }
  }

  onFontSizeScaleChange() {
    this.containerDirection = this.decideContainerDirection();
    this.contentItemDirection = this.decideContentItemDirection();
    if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL3) {
      this.containerPadding = {
        top: $r('sys.float.padding_level12'),
        bottom: $r('sys.float.padding_level12'),
      };
    } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL2) {
      this.containerPadding = {
        top: $r('sys.float.padding_level10'),
        bottom: $r('sys.float.padding_level10'),
      };
    } else if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1) {
      this.containerPadding = {
        top: $r('sys.float.padding_level8'),
        bottom: $r('sys.float.padding_level8'),
      };
    } else {
      this.containerPadding = {
        top: $r('sys.float.padding_level4'),
        bottom: $r('sys.float.padding_level4'),
      };
    }
  }

  isSingleLine(): boolean {
    return !this.contentItem?.secondaryText && !this.contentItem?.description;
  }

  getOperateOffset(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Row) {
      return LengthMetrics.vp(0);
    }
    let iconSize = ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number);
    if (iconSize && iconSize <= HEADSCULPTURE_SIZE) {
      return LengthMetrics.vp(iconSize + (this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH));
    }
    return LengthMetrics.vp(0);
  }

  getMainSpace(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Column) {
      return LengthMetrics.vp(this.isSingleLine() ? 2 : 16);
    }
    return LengthMetrics.vp(this.itemSpace ?? DEFAULT_ITEM_SPACE_WIDTH);
  }

  getComposeItemLeftPadding(): LengthMetrics {
    return this.composeItemPadding?.start !== undefined ?
      this.composeItemPadding?.start : LengthMetrics.vp(STACK_PADDING);
  }

  getComposeItemRightPadding(): LengthMetrics {
    return this.composeItemPadding?.end !== undefined ?
      this.composeItemPadding?.end : LengthMetrics.vp(STACK_PADDING);
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

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Measurable[], constraint: ConstraintSizeOptions): SizeResult {
    let sizeResult: SizeResult = { height: 0, width: 0 };
    let content = this.getUIContext().getHostContext() as common.ExtensionContext;
    this.fontSizeScale = content.config?.fontSizeScale ?? 1;
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
          ContentItemStruct({});
        }
        if (this.contentItem !== null) {
          ContentItemStruct({
            icon: this.contentItem.icon,
            iconStyle: this.contentItem.iconStyle,
            primaryText: this.contentItem.primaryText,
            secondaryText: this.contentItem.secondaryText,
            description: this.contentItem.description,
            iconImageModifier: this.contentItem.iconImageModifier,
            primaryTextModifier: this.contentItem.primaryTextModifier,
            secondaryTextModifier: this.contentItem.secondaryTextModifier,
            descriptionModifier: this.contentItem.descriptionModifier,
            leftWidth: this.calculatedLeftWidth(),
            contentItemPadding: this.composeItemPadding,
            itemSpace: this.itemSpace,
            fontSizeScale: this.fontSizeScale,
            parentDirection: this.containerDirection,
            itemDirection: this.contentItemDirection
          });
        }
        if (this.operateItem !== null) {
          OperateItemStruct({
            icon: this.operateItem.icon,
            subIcon: this.operateItem.subIcon,
            button: this.operateItem.button,
            switch: this.operateItem.switch,
            checkBox: this.operateItem.checkbox,
            radio: this.operateItem.radio,
            image: this.operateItem.image,
            text: this.operateItem.text,
            arrow: this.operateItem.arrow,
            parentCanFocus: this.canFocus,
            parentCanTouch: this.canTouch,
            parentIsHover: this.isHover,
            parentFrontColor: this.frontColor,
            parentIsActive: this.isActive,
            parentCanHover: this.canHover,
            rightWidth: this.calculatedRightWidth(),
            isParentCanTouch: this.isCanTouch,
            parentDirection: this.containerDirection,
          })
            .align(Alignment.End)
            .onFocus(() => {
              this.canFocus = false;
            })
            .onBlur(() => {
              this.canFocus = true;
            }).padding({start: this.getOperateOffset()});
        }
      }
      .constraintSize({ minHeight: this.itemHeight })
      .focusable(true)
      .borderRadius($r('sys.float.corner_radius_level8'))
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
          this.frontColor = isHover ? this.hoveringColor :
            (this.isActive ? this.activedColor : Color.Transparent.toString());
        }
      })
      .onTouch((event: TouchEvent) => {
        if (this.isCanTouch) {
          if (event.type === TouchType.Down && this.canTouch) {
            this.frontColor = this.touchDownColor;
          }
          if (event.type === TouchType.Up) {
            this.frontColor = this.isActive ? this.activedColor : Color.Transparent.toString();
          }
        }
      })
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.corner_radius_level8'),
            width: ITEM_BORDER_SHOWN,
            color: this.focusOutlineColor,
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.corner_radius_level8'),
            color: Color.Transparent
          })
        }
      }).padding(this.containerPadding)
    }
    .padding({
      start: this.getComposeItemLeftPadding(),
      end: this.getComposeItemRightPadding()
    });
  }
}
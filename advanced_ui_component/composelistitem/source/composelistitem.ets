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
import { common, EnvironmentCallback } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';

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
  public symbolStyle?: SymbolGlyphModifier;
  public text?: ResourceStr;
  public arrow?: OperateIcon;
}

export declare class ContentItem {
  public iconStyle?: IconType;
  public icon?: ResourceStr;
  public symbolStyle?: SymbolGlyphModifier;
  public primaryText?: ResourceStr;
  public secondaryText?: ResourceStr;
  public description?: ResourceStr;
}

export declare class OperateIcon {
  public value: ResourceStr;
  public symbolStyle?: SymbolGlyphModifier;
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
const OPERATEITEM_SELECTIONBOX_PADDING_SIZE = 2;
const OPERATEITEM_ARROW_WIDTH = 12
const OPERATEITEM_ICON_CLICKABLE_SIZE = 40;
const OPERATEITEM_IMAGE_SIZE = 48;
const RIGHT_CONTENT_NULL_RIGHTWIDTH = '0vp';
const LEFT_PART_WIDTH = 'calc(66% - 16vp)';
const RIGHT_PART_WIDTH = '34%';
const RIGHT_ONLY_ARROW_WIDTH = '24vp';
const RIGHT_ONLY_IMAGE_WIDTH = '54vp';
const RIGHT_ONLY_ICON_WIDTH = '40vp';
const RIGHT_ICON_SUB_ICON_WIDTH = '80vp';
const RIGHT_ONLY_RADIO_WIDTH = '30vp';
const RIGHT_ONLY_CHECKBOX_WIDTH = '30vp';
const RIGHT_ONLY_SWITCH_WIDTH = '44vp';
const RESOURCE_TYPE_SYMBOL: number = 40000;

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

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr | Resource | undefined | null): boolean {
    if (!resource) {
      return false;
    }
    if (typeof resource === 'string' || typeof resource === 'undefined') {
      return false;
    }
    return true;
  }
}

@Component
struct ContentItemStruct {
  @Prop @Watch('onPropChange') iconStyle: IconType | null = null;
  @Prop @Watch('onPropChange') icon: ResourceStr | null = null;
  @Prop @Watch('onPropChange') symbolStyle: SymbolGlyphModifier | null = null;
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

  onWillApplyTheme(theme: Theme): void {
    this.primaryTextColor = theme.colors.fontPrimary;
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.descriptionColor = theme.colors.fontTertiary;
  }

  onPropChange(): void {
    if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    } else {
      this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
    }
  }

  aboutToAppear(): void {
    this.onPropChange();
  }

  @Builder
  createIcon() {
    if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
      if (this.symbolStyle != null) {
        SymbolGlyph()
          .attributeModifier(this.symbolStyle)
          .fontSize(ICON_SIZE_MAP.get(this.iconStyle))
          .effectStrategy(SymbolEffectStrategy.NONE)
          .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
          .focusable(false)
          .draggable(false)
          .flexShrink(0)
      } else if (this.icon != null) {
        if (Util.isSymbolResource(this.icon)) {
          SymbolGlyph(this.icon as Resource)
            .fontSize(ICON_SIZE_MAP.get(this.iconStyle))
            .effectStrategy(SymbolEffectStrategy.NONE)
            .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
            .focusable(false)
            .draggable(false)
            .flexShrink(0)
        } else {
          if (this.iconStyle <= IconType.PREVIEW) {
            Image(this.icon)
              .objectFit(ImageFit.Contain)
              .width(ICON_SIZE_MAP.get(this.iconStyle))
              .height(ICON_SIZE_MAP.get(this.iconStyle))
              .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
              .focusable(false)
              .draggable(false)
              .fillColor($r('sys.color.ohos_id_color_secondary'))
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
    }
  }

  @Builder
  createText() {
    Column({ space: TEXT_COLUMN_SPACE }) {
      Text(this.primaryText)
        .fontSize($r('sys.float.ohos_id_text_size_body1'))
        .fontColor(this.primaryTextColor)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .fontWeight(FontWeight.Medium)
        .focusable(true)
        .draggable(false)
      if (this.secondaryText != null) {
        Text(this.secondaryText)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor(this.secondaryTextColor)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .draggable(false)
      }
      if (this.description != null) {
        Text(this.description)
          .fontSize($r('sys.float.ohos_id_text_size_body2'))
          .fontColor(this.descriptionColor)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .draggable(false)
      }
    }
    .flexShrink(1)
    .margin(this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 ? undefined : {
      top: TEXT_SAFE_MARGIN,
      bottom: TEXT_SAFE_MARGIN
    })
    .alignItems(HorizontalAlign.Start)
  }

  isColumnDirection(): boolean {
    return this.itemDirection === FlexDirection.Column;
  }

  isParentColumnDirection(): boolean {
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
      this.createIcon();
      this.createText();
    }
    .height(this.itemDirection === FlexDirection.Column ? 'auto' : undefined)
    .margin({
      end: this.isParentColumnDirection() ?
      LengthMetrics.vp(0) :
      LengthMetrics.vp(16)
    })
    .padding({ start: LengthMetrics.vp(LISTITEM_PADDING) })
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
  @Prop @Watch('onPropChange') symbolStyle: SymbolGlyphModifier | null = null;
  @Prop @Watch('onPropChange') text: ResourceStr | null = null;
  @State switchState: boolean = false;
  @State radioState: boolean = false;
  @State checkBoxState: boolean = false;
  @Prop rightWidth: string = RIGHT_PART_WIDTH;
  @State secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @State hoveringColor: ResourceColor = '#0d000000';
  @State activedColor: ResourceColor = '#1a0a59f7';
  @Link parentCanFocus: boolean;
  @Link parentCanTouch: boolean;
  @Link parentIsHover: boolean;
  @Link parentCanHover: boolean;
  @Link parentIsActive: boolean;
  @Link parentFrontColor: ResourceColor;
  @Link parentDirection: FlexDirection;
  @State rowSpace: number = DEFAULT_ROW_SPACE;

  onWillApplyTheme(theme: Theme): void {
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.hoveringColor = theme.colors.interactiveHover;
    this.activedColor = theme.colors.interactiveActive;
  }

  onPropChange(): void {
    if (this.switch != null) {
      this.switchState = this.switch.isCheck as boolean;
    }
    if (this.radio != null) {
      this.radioState = this.radio.isCheck as boolean;
    }
    if (this.checkBox != null) {
      this.checkBoxState = this.checkBox.isCheck as boolean;
    }

    if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
      ((this.icon != null) || (this.icon == null && this.arrow != null))) {
      this.rowSpace = SPECICAL_ROW_SPACE;
    } else {
      this.rowSpace = DEFAULT_ROW_SPACE;
    }
  }

  aboutToAppear(): void {
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
    .onHover((isHover: boolean) => {
      this.parentCanHover = false;
      if (isHover && this.parentFrontColor === this.hoveringColor) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true;
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
      if (param.icon?.symbolStyle) {
        SymbolGlyph()
          .attributeModifier(param.icon?.symbolStyle)
          .fontSize(OPERATEITEM_ICONLIKE_SIZE)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .focusable(true)
          .draggable(false)
      } else {
        if (Util.isSymbolResource(param.icon?.value)) {
          SymbolGlyph(param.icon?.value as Resource)
            .fontSize(OPERATEITEM_ICONLIKE_SIZE)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .focusable(true)
            .draggable(false)
        } else {
          Image(param.icon?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ICONLIKE_SIZE)
            .focusable(true)
            .fillColor($r('sys.color.ohos_id_color_primary'))
            .draggable(false)
        }
      }
    }
    .hitTestBehavior(HitTestMode.Block)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .onHover((isHover: boolean) => {
      this.parentCanHover = false;
      if (isHover && this.parentFrontColor === this.hoveringColor) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true;
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
    if (Util.isSymbolResource(this.image)) {
      SymbolGlyph(this.image as Resource)
        .fontSize(OPERATEITEM_IMAGE_SIZE)
        .effectStrategy(SymbolEffectStrategy.NONE)
        .draggable(false)
        .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    } else {
      Image(this.image)
        .height(OPERATEITEM_IMAGE_SIZE)
        .width(OPERATEITEM_IMAGE_SIZE)
        .draggable(false)
        .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    }
  }

  @Builder
  createSymbol() {
    SymbolGlyph()
      .attributeModifier(this.symbolStyle)
      .fontSize(OPERATEITEM_IMAGE_SIZE)
      .effectStrategy(SymbolEffectStrategy.NONE)
      .draggable(false)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
  }

  @Builder
  createText() {
    Text(this.text)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .fontSize($r('sys.float.ohos_id_text_size_body2'))
      .fontColor(this.secondaryTextColor)
      .draggable(false)
      .flexShrink(1)
  }

  @Builder
  createArrow() {
    Button({ type: ButtonType.Normal }) {
      if (this.arrow?.symbolStyle) {
        SymbolGlyph()
          .attributeModifier(this.arrow?.symbolStyle)
          .fontSize(OPERATEITEM_ARROW_WIDTH)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .focusable(true)
          .draggable(false)
      } else {
        if (Util.isSymbolResource(this.arrow?.value)) {
          SymbolGlyph(this.arrow?.value as Resource)
            .fontSize(OPERATEITEM_ARROW_WIDTH)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .focusable(true)
            .draggable(false)
        } else {
          Image(this.arrow?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ARROW_WIDTH)
            .focusable(true)
            .fillColor($r('sys.color.ohos_id_color_fourth'))
            .draggable(false)
            .matchTextDirection(true)
        }
      }
    }
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    .hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICONLIKE_SIZE)
    .width(OPERATEITEM_ARROW_WIDTH)
    .onFocus(() => {
      this.parentCanFocus = false;
    })
    .stateEffect(this.arrow?.action !== undefined)
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      if (isHover) {
        this.parentCanHover = false;
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      } else {
        this.parentCanHover = true;
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
      .onChange(this.radio?.onChange)
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false;
      })
      .hitTestBehavior(HitTestMode.Block)
      .flexShrink(0)
      .onHover((isHover: boolean) => {
        this.parentCanHover = false;
        if (isHover && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!isHover) {
          this.parentCanHover = true;
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
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .select(this.checkBoxState)
      .onChange(this.checkBox?.onChange)
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        this.parentCanFocus = false;
      })
      .hitTestBehavior(HitTestMode.Block)
      .flexShrink(0)
      .onHover((isHover: boolean) => {
        this.parentCanHover = false;
        if (isHover && this.parentFrontColor === this.hoveringColor) {
          this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
        }
        if (!isHover) {
          this.parentCanHover = true;
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
        .onChange(this.switch?.onChange)
        .onClick(() => {
          this.switchState = !this.switchState;
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
    .onHover((isHover: boolean) => {
      this.parentCanHover = false;
      if (isHover && this.parentFrontColor === this.hoveringColor) {
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      }
      if (!isHover) {
        this.parentCanHover = true;
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
      if (this.parentDirection === FlexDirection.Column) {
        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Text(this.text)
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontColor(this.secondaryTextColor)
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            })
          if (this.arrow?.symbolStyle) {
            SymbolGlyph()
              .attributeModifier(this.arrow?.symbolStyle)
              .fontSize(OPERATEITEM_ARROW_WIDTH)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .focusable(false)
              .draggable(false)
          } else {
            if (Util.isSymbolResource(this.arrow?.value)) {
              SymbolGlyph(this.arrow?.value as Resource)
                .fontSize(OPERATEITEM_ARROW_WIDTH)
                .effectStrategy(SymbolEffectStrategy.NONE)
                .focusable(false)
                .draggable(false)
            } else {
              Image(this.arrow?.value)
                .height(OPERATEITEM_ICONLIKE_SIZE)
                .width(OPERATEITEM_ARROW_WIDTH)
                .fillColor($r('sys.color.ohos_id_color_fourth'))
                .focusable(false)
                .draggable(false)
                .matchTextDirection(true)
            }
          }
        }
        .padding({
          start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
          end: LengthMetrics.vp(LISTITEM_PADDING)
        })
      } else {
        Row({ space: SPECICAL_ROW_SPACE }) {
          Text(this.text)
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontColor(this.secondaryTextColor)
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            })
          if (this.arrow?.symbolStyle) {
            SymbolGlyph()
              .attributeModifier(this.arrow?.symbolStyle)
              .fontSize(OPERATEITEM_ARROW_WIDTH)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .focusable(false)
              .draggable(false)
          } else {
            if (Util.isSymbolResource(this.arrow?.value)) {
              SymbolGlyph(this.arrow?.value as Resource)
                .fontSize(OPERATEITEM_ARROW_WIDTH)
                .effectStrategy(SymbolEffectStrategy.NONE)
                .focusable(false)
                .draggable(false)
            } else {
              Image(this.arrow?.value)
                .height(OPERATEITEM_ICONLIKE_SIZE)
                .width(OPERATEITEM_ARROW_WIDTH)
                .fillColor($r('sys.color.ohos_id_color_fourth'))
                .focusable(false)
                .draggable(false)
                .matchTextDirection(true)
            }
          }
        }
        .padding({
          start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
          end: LengthMetrics.vp(LISTITEM_PADDING)
        })
      }
    }
    .hitTestBehavior(this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent)
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
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      if (isHover) {
        this.parentCanHover = false;
        this.parentFrontColor = this.parentIsActive ? this.activedColor : Color.Transparent.toString();
      } else {
        this.parentCanHover = true;
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
      } else if (this.symbolStyle != null) {
        this.createSymbol();
      } else if (this.image != null) {
        this.createImage();
      } else if (this.icon != null && this.text != null) {
        this.createText();
        this.createIcon({ icon: this.icon })
      } else if (this.arrow != null && this.text == null) {
        this.createArrow();
      } else if (this.arrow != null && this.text != null) {
        this.createTextArrow();
      } else if (this.text != null) {
        this.createText();
      } else if (this.radio != null) {
        this.createRadio();
      } else if (this.checkBox != null) {
        this.createCheckBox();
      } else if (this.switch != null) {
        this.createSwitch();
      } else if (this.icon != null) {
        this.createIcon({ icon: this.icon });
        if (this.subIcon != null) {
          this.createIcon({ icon: this.subIcon });
        }
      }
    }
    .width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth)
  }
}

@Component
export struct ComposeListItem {
  @Prop @Watch('onPropChange') contentItem: ContentItem | null = null;
  @Prop @Watch('onPropChange') operateItem: OperateItem | null = null;
  @State frontColor: ResourceColor = Color.Transparent.toString();
  @State borderSize: number = 0;
  @State canFocus: boolean = false;
  @State canTouch: boolean = true;
  @State canHover: boolean = true;
  @State isHover: boolean = true;
  @State itemHeight: number = ItemHeight.FIRST_HEIGHT;
  @State isActive: boolean = false;
  @State hoveringColor: ResourceColor = '#0d000000';
  @State touchDownColor: ResourceColor = '#1a000000';
  @State activedColor: ResourceColor = '#1a0a59f7';
  @State focusOutlineColor: ResourceColor = $r('sys.color.ohos_id_color_focused_outline');
  @State @Watch('onFontSizeScaleChange') fontSizeScale: number = 1;
  @State containerDirection: FlexDirection = FlexDirection.Row;
  @State contentItemDirection: FlexDirection = FlexDirection.Row;
  @State containerPadding?: Padding = undefined;
  @State textArrowLeftSafeOffset: number = 0;
  private isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
  private maxFontScale = this.getUIContext().getMaxFontScale();
  private callbackId: number | undefined = undefined;

  onWillApplyTheme(theme: Theme): void {
    this.hoveringColor = theme.colors.interactiveHover;
    this.touchDownColor = theme.colors.interactivePressed;
    this.activedColor = theme.colors.interactiveActive;
    this.focusOutlineColor = theme.colors.interactiveFocus;
  }

  onPropChange(): void {
    this.containerDirection = this.decideContainerDirection();
    this.contentItemDirection = this.decideContentItemDirection();
    if (this.contentItem === undefined) {
      if (this.operateItem?.image !== undefined ||
        this.operateItem?.symbolStyle !== undefined ||
        this.operateItem?.icon !== undefined ||
        this.operateItem?.subIcon !== undefined) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
      }
      return;
    }

    if (this.contentItem?.secondaryText === undefined && this.contentItem?.description === undefined) {
      if (this.contentItem?.icon === undefined) {
        this.itemHeight = ItemHeight.FIRST_HEIGHT;
      } else {
        this.itemHeight = this.contentItem.iconStyle as number <= IconType.HEAD_SCULPTURE ?
        ItemHeight.SECOND_HEIGHT : ItemHeight.THIRD_HEIGHT;
      }
    } else if (this.contentItem.description === undefined) {
      if (this.contentItem.icon === undefined ||
        (this.contentItem.icon !== undefined && this.contentItem.iconStyle as number <= IconType.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT;
      } else {
        this.itemHeight = ItemHeight.FOURTH_HEIGHT;
      }
    } else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT;
    }

    if (ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number) as number >= this.itemHeight) {
      this.itemHeight = ICON_SIZE_MAP.get(this.contentItem?.iconStyle as number) as number + SAFE_LIST_PADDING;
    }
  }

  aboutToAppear(): void {
    this.fontSizeScale = this.decideFontSizeScale();
    this.onPropChange();
    try {
      this.callbackId = getContext()?.getApplicationContext()?.on('environment', this.envCallback);
    } catch (paramError) {
      let code = (paramError as BusinessError).code;
      let message = (paramError as BusinessError).message;
      hilog.error(0x3900, 'Ace',
        `ComposeListItem Faild to get environment param error: ${code}, ${message}`);
    }
  }

  private envCallback: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      this.fontSizeScale = this.decideFontSizeScale();
    },
    onMemoryLevel: (level) => {
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      this.getUIContext()
        .getHostContext()
      ?.getApplicationContext()
      ?.off('environment', this.callbackId);
      this.callbackId = void (0);
    }
  }

  calculatedRightWidth(): string {
    if (this.operateItem?.text || this.operateItem?.button) {
      return RIGHT_PART_WIDTH;
    }
    if (this.operateItem?.switch) {
      return RIGHT_ONLY_SWITCH_WIDTH;
    } else if (this.operateItem?.checkbox) {
      return RIGHT_ONLY_CHECKBOX_WIDTH;
    } else if (this.operateItem?.radio) {
      return RIGHT_ONLY_RADIO_WIDTH;
    } else if (this.operateItem?.icon) {
      if (this.operateItem?.subIcon) {
        return RIGHT_ICON_SUB_ICON_WIDTH;
      }
      return RIGHT_ONLY_ICON_WIDTH;
    } else if (this.operateItem?.symbolStyle) {
      return RIGHT_ONLY_IMAGE_WIDTH;
    } else if (this.operateItem?.image) {
      return RIGHT_ONLY_IMAGE_WIDTH;
    } else if (this.operateItem?.arrow) {
      return RIGHT_ONLY_ARROW_WIDTH;
    }
    return RIGHT_CONTENT_NULL_RIGHTWIDTH;
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
    } else if (this.operateItem?.symbolStyle) {
      return FlexDirection.Row;
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

  onFontSizeScaleChange(): void {
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
      this.containerPadding = undefined;
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
    if (this.contentItem?.icon && iconSize && iconSize <= HEADSCULPTURE_SIZE) {
      return LengthMetrics.vp(iconSize + NORMAL_ITEM_ROW_SPACE + LISTITEM_PADDING - this.textArrowLeftSafeOffset);
    }
    return LengthMetrics.vp(LISTITEM_PADDING - this.textArrowLeftSafeOffset);
  }

  getMainSpace(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Column) {
      return LengthMetrics.resource(this.isSingleLine() ? $r('sys.float.padding_level1') :
      $r('sys.float.padding_level8'));
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

  build() {
    Stack() {
      Flex(this.getFlexOptions()) {
        if (this.contentItem === null) {
          ContentItemStruct({})
        }
        if (this.contentItem !== null) {
          ContentItemStruct({
            icon: this.contentItem?.icon,
            symbolStyle: this.contentItem?.symbolStyle,
            iconStyle: this.contentItem?.iconStyle,
            primaryText: this.contentItem?.primaryText,
            secondaryText: this.contentItem?.secondaryText,
            description: this.contentItem?.description,
            fontSizeScale: this.fontSizeScale,
            parentDirection: this.containerDirection,
            itemDirection: this.contentItemDirection,
          })
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
            symbolStyle: this.operateItem?.symbolStyle,
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
          })
            .flexShrink(0)
            .onFocus(() => {
              this.canFocus = false;
            })
            .onBlur(() => {
              this.canFocus = true;
            }).padding({ start: this.getOperateOffset() });
        }
      }
      .height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined)
      .constraintSize({
        minHeight: this.itemHeight
      })
      .focusable(true)
      .borderRadius($r('sys.float.ohos_id_corner_radius_default_m'))
      .backgroundColor(this.frontColor)
      .onFocus(() => {
        this.canFocus = true;
      })
      .onBlur(() => {
        this.canFocus = false;
      })
      .onHover((isHover: boolean) => {
        this.isHover = isHover;
        if (this.canHover) {
          this.frontColor = isHover ? this.hoveringColor :
            (this.isActive ? this.activedColor : Color.Transparent.toString());
        }
      })
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_default_m'),
            width: ITEM_BORDER_SHOWN,
            color: this.focusOutlineColor,
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.ohos_id_corner_radius_default_m'),
            width: ITEM_BORDER_SHOWN,
            color: Color.Transparent
          })
        },
        pressed: {
          .backgroundColor(this.touchDownColor)
        }
      })
      .padding(this.containerPadding)
    }
    .width('100%')
    .padding({
      left: STACK_PADDING,
      right: STACK_PADDING
    })
  }
}
/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

import {
  Text, Column, ComponentV2, Row, Button, SymbolGlyph, Image, Radio, Checkbox, Toggle, Stack, Flex,
  Length, FlexDirection, Resource, ResourceStr, ResourceColor, ShadowStyle, FlexAlign,
  HorizontalAlign, SizeOptions, FontWeight, SymbolEffect, ScaleOptions, BorderStyle, LocalizedPadding, Padding,
  FlexOptions, MarqueeStartPolicy, ButtonType, Color, HitTestMode, ItemAlign, ToggleType, HoverEffect, TextOverflow,
  ImageFit, SymbolEffectStrategy, $r, LocalizedMargin, Margin,
  ColumnOptions, ButtonOptions, OnCheckboxChangeCallback, FlexSpaceOptions, RowOptions, ClickEvent,
  HoverEvent, CommonMethod
} from '@ohos.arkui.component'
import { SymbolGlyphModifier } from '@ohos.arkui.modifier';
import { Local, Monitor, IMonitor, Param } from '@ohos.arkui.stateManagement'
import { Theme } from '@ohos.arkui.theme';
import hilog from '@ohos.hilog'
import { MeasureUtils } from '@ohos.arkui.UIContext';
import resourceManager from '@ohos.resourceManager'
import { LengthMetrics } from '@ohos.arkui.node';
import common from '@ohos.app.ability.common';
import { BusinessError } from '@ohos.base';
import { UIContext, Context } from '@ohos.arkui.UIContext';
import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
import { Configuration } from '@ohos.app.ability.Configuration';
import AbilityConstant from '@ohos.app.ability.AbilityConstant';
import ApplicationContext from 'application.ApplicationContext';
import Decimal from '@arkts.math.Decimal';

export enum IconTypeV2 {
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
  LEVEL1 = 175,
  LEVEL2 = 200,
  LEVEL3 = 320
}

enum ItemHeight {
  FIRST_HEIGHT = 48,
  SECOND_HEIGHT = 56,
  THIRD_HEIGHT = 64,
  FOURTH_HEIGHT = 72,
  FIFTH_HEIGHT = 96
}

export class OperateItemV2 {
  public icon?: OperateIconV2;
  public subIcon?: OperateIconV2;
  public button?: OperateButtonV2;
  public toggle?: OperateCheckV2;
  public checkbox?: OperateCheckV2;
  public radio?: OperateCheckV2;
  public image?: ResourceStr;
  public symbolStyle?: SymbolGlyphModifier;
  public text?: ResourceStr;
  public arrow?: OperateIconV2;
}

export class ContentItemV2 {
  public iconStyle?: IconTypeV2;
  public icon?: ResourceStr;
  public symbolStyle?: SymbolGlyphModifier;
  public primaryText?: ResourceStr;
  public secondaryText?: ResourceStr;
  public description?: ResourceStr;
}

export class OperateIconV2 {
  public value?: ResourceStr;
  public symbolStyle?: SymbolGlyphModifier;
  public action?: () => void;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
  public accessibilityLevel?: string;
}

export class OperateButtonV2 {
  public text?: ResourceStr;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
  public accessibilityLevel?: string;
}

export class OperateCheckV2 {
  public isCheck?: boolean;
  public onChange?: (value: boolean) => void;
  public accessibilityText?: ResourceStr;
  public accessibilityDescription?: ResourceStr;
  public accessibilityLevel?: string;
}

const TEXT_MAX_LINE: int = 1;
const ITEM_BORDER_SHOWN: number = 2;
const TEXT_COLUMN_SPACE: number = 4;
const TEXT_SAFE_MARGIN: number = 8;
const LISTITEM_PADDING: number = 6;
const SWITCH_PADDING: number = 4;
const STACK_PADDING: number = 4.0;
const BADGE_SIZE: number = 8;
const SMALL_ICON_SIZE: number = 16;
const SYSTEM_ICON_SIZE: number = 24;
const TEXT_ARROW_HEIGHT: number = 32;
const SAFE_LIST_PADDING: number = 32;
const HEADSCULPTURE_SIZE: number = 40;
const BUTTON_SIZE: number = 28;
const APP_ICON_SIZE: number = 64;
const PREVIEW_SIZE: number = 96;
const LONGITUDINAL_SIZE: number = 96;
const VERTICAL_SIZE: number = 96;
const NORMAL_ITEM_ROW_SPACE: number = 16;
const SPECIAL_ITEM_ROW_SPACE: number = 0;
const SPECIAL_ICON_SIZE: number = 0;
const DEFAULT_ROW_SPACE: number = 0;
const SPECICAL_ROW_SPACE: number = 4;
const OPERATEITEM_ICONLIKE_SIZE: number = 24;
const OPERATEITEM_SELECTIONBOX_PADDING_SIZE: number = 2;
const OPERATEITEM_ARROW_WIDTH: number = 12
const OPERATEITEM_ICON_CLICKABLE_SIZE: number = 40;
const OPERATEITEM_IMAGE_SIZE: number = 48;
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
const ACCESSIBILITY_LEVEL_AUTO = 'auto';
const ACCESSIBILITY_LEVEL_YES = 'yes';
const ACCESSIBILITY_LEVEL_NO = 'no';
const RESOURCE_TYPE_SYMBOL: int = 40000;

const ICON_SIZE_MAP: Map<number, number> = new Map<number, number>([
  [IconTypeV2.BADGE, BADGE_SIZE],
  [IconTypeV2.NORMAL_ICON, SMALL_ICON_SIZE],
  [IconTypeV2.SYSTEM_ICON, SYSTEM_ICON_SIZE],
  [IconTypeV2.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
  [IconTypeV2.APP_ICON, APP_ICON_SIZE],
  [IconTypeV2.PREVIEW, PREVIEW_SIZE],
  [IconTypeV2.LONGITUDINAL, LONGITUDINAL_SIZE],
  [IconTypeV2.VERTICAL, VERTICAL_SIZE]
])
// Does it support events such as focus, hover, press, etc. for the sub components of list
const IS_SUPPORT_SUBCOMPONENT_EVENT: boolean =
  LengthMetrics.resource($r('sys.float.composeListItem_focus_dynamic_effect')).value !== 1;
const RECOVER_ITEM_SCALE: number = 1.0;
const CLEAR_SHADOW: ShadowStyle | number = -1;
const OPERATE_ITEM_RADIUS: number = 50;
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR: ResourceColor = $r('sys.color.ohos_id_color_switch_outline_off');
const TEXT_SUPPORT_MARQUEE: number = 1;
const IS_MARQUEE_OR_ELLIPSIS: number =
  LengthMetrics.resource($r('sys.float.composeListItem_right_textOverflow')).value as number;
const UNUSUAL: number = -1;
const FOCUSED_BG_COLOR: ResourceColor = $r('sys.color.composeListItem_container_focus_color');
const NORMAL_BG_COLOR: ResourceColor = $r('sys.color.composeListItem_container_normal_color');
const FOCUSED_ITEM_SCALE: number = LengthMetrics.resource($r('sys.float.composeListItem_focus_magnification')).value;
const FOCUSED_SHADOW: ShadowStyle | number =
  LengthMetrics.resource($r('sys.float.composeListItem_focus_shadow_attribute'))?.value as ShadowStyle | number;
const NORMAL_SHADOW: ShadowStyle | number =
  LengthMetrics.resource($r('sys.float.composeListItem_normal_shadow_attribute'))?.value as ShadowStyle | number;
const ITEM_PADDING: Resource = $r('sys.float.composeListItem_padding');
const OPERATEITEM_ARROW_MARGIN_WIDTH: number = LengthMetrics.resource(
  $r('sys.float.composeListItem_arrow_margin')).value;
const APPICON_ITEMLENGTH: number = LengthMetrics.resource(
  $r('sys.float.composeListItem_AppIcon_ItemLength')).value;

class Util {
  public static isSymbolResource(resourceStr: ResourceStr | undefined | null): boolean {
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource: Resource = resourceStr as Resource;
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

export class EnvironmentCallbackEntry implements EnvironmentCallback {
  ComposeListItem: ComposeListItemV2;

  constructor(ComposeListItem: ComposeListItemV2) {
    this.ComposeListItem = ComposeListItem;
  }

  onConfigurationUpdated(config: Configuration): void {
    if (config === undefined || !this.ComposeListItem.isFollowingSystemFontScale) {
      this.ComposeListItem.fontSizeScale = 1;
      return;
    }
    try {
      this.ComposeListItem.fontSizeScale = Math.min(
        this.ComposeListItem.maxFontScale, config.fontSizeScale ?? 1);
    } catch (paramError) {
      let code = (paramError as ClassCastError).code;
      let message = (paramError as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `ComposeListItem environmentCallback error: ${code}, ${message}`);
    }
  }

  onMemoryLevel(level: AbilityConstant.MemoryLevel): void {

  }
}

  @ComponentV2
struct ContentItemStructV2 {
  @Param iconStyle: IconTypeV2 | undefined = undefined;
  @Param icon: ResourceStr | undefined = undefined;
  @Param symbolStyle: SymbolGlyphModifier | undefined = undefined;
  @Param primaryText: ResourceStr | undefined = undefined;
  @Param secondaryText: ResourceStr | undefined = undefined;
  @Param description: ResourceStr | undefined = undefined;
  @Local itemRowSpace: number = NORMAL_ITEM_ROW_SPACE;
  @Param leftWidth: string = LEFT_PART_WIDTH;
  @Local primaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary');
  @Local secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Local descriptionColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Param fontSizeScale: number | undefined = 0;
  @Param parentDirection: FlexDirection | undefined = undefined;
  @Param itemDirection: FlexDirection | undefined = undefined;
  @Param isFocus: boolean = false;
  @Local primaryTextSize: string | number | Resource = $r('sys.float.ohos_id_text_size_body1');
  @Local primaryTextColors: ResourceColor = $r('sys.color.font_primary');
  @Param itemHeight: number | undefined = undefined;
  @Local iconColor: ResourceColor | null = null;
  @Local secondaryTextColors: ResourceColor = $r('sys.color.font_secondary');
  @Local secondaryThirdTextSize: string | number | Resource =
    $r('sys.float.composeListItem_left_secondary_tertiary_text_size');
  @Local descriptionColors: ResourceColor = $r('sys.color.font_tertiary');
  @Param isWrapText: Boolean = false;
  @Local isWrapFirstText: Boolean = false;
  @Local isWrapSecondText: Boolean = false;
  @Local isWrapThirdText: Boolean = false;

  onWillApplyTheme(theme: Theme): void {
    this.primaryTextColor = theme.colors.fontPrimary;
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.descriptionColor = theme.colors.fontTertiary;
  }

  @Monitor(['iconStyle', 'icon', 'symbolStyle', 'primaryText', 'secondaryText', 'description'])
  onPropChange(_monitor: IMonitor): void {
    if (this.icon == null && this.symbolStyle == null && this.iconStyle == null) {
      this.itemRowSpace = SPECIAL_ITEM_ROW_SPACE;
    } else {
      this.itemRowSpace = NORMAL_ITEM_ROW_SPACE;
    }
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
      this.primaryTextColors = $r('sys.color.composeListItem_left_text_focus_color');
      this.secondaryTextColors = $r('sys.color.composeListItem_left_secondary_text_focus_color');
      this.descriptionColors = $r('sys.color.composeListItem_left_secondary_text_focus_color');
    } else {
      this.primaryTextColors = $r('sys.color.ohos_id_color_text_primary');
      this.secondaryTextColors = $r('sys.color.ohos_id_color_text_secondary');
      this.descriptionColors = $r('sys.color.ohos_id_color_text_secondary');
    }
  }

  getContentItemIconFillColor(): ResourceColor {
    if (this.iconStyle == IconTypeV2.BADGE) {
      return $r('sys.color.composeListItem_badge_color');
    } else if (this.iconStyle == IconTypeV2.SYSTEM_ICON) {
      return $r('sys.color.composeListItem_icon_normal_color');
    } else {
      return $r('sys.color.ohos_id_color_secondary');
    }
  }

  judgeIsWrap(text: ResourceStr | null, sizeResource: Length, newHeight: number): boolean {
    let singleRowHeight: number = this.getSingleRowTextHeight(text, sizeResource);
    return newHeight > singleRowHeight;
  }

  getSingleRowTextHeight(text: ResourceStr | null, sizeResource: Length): number {
    if (text && sizeResource) {
      const measureUtils = new MeasureUtils()
      let singleRowHeight: number = this.getUIContext().px2vp(measureUtils.measureTextSize({
        textContent: text,
        fontSize: sizeResource,
        maxLines: TEXT_MAX_LINE
      }).height as number);
      return singleRowHeight;
    }
    return 0;
  }

  aboutToAppear(): void {
    // Do nothing - onPropChange is triggered by @Monitor decorator automatically
  }

  @Builder
  createIcon() {
    const defaultIconStyle = this.iconStyle ?? IconTypeV2.BADGE;
    if (ICON_SIZE_MAP.has(defaultIconStyle as IconTypeV2)) {
      if (this.symbolStyle != null) {
        SymbolGlyph()
          .fontColor([this.getContentItemIconFillColor()])
          .attributeModifier(this.symbolStyle as SymbolGlyphModifier)
          .fontSize(`${ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2)}vp`)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .borderRadius($r('sys.float.composeListItem_Image_Radius'))
          .focusable(false)
          .draggable(false)
          .flexShrink(0)
      } else if (this.icon != null) {
        if (Util.isSymbolResource(this.icon)) {
          SymbolGlyph(this.icon as Resource)
            .fontSize(`${ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2)}vp`)
            .fontColor([this.getContentItemIconFillColor()])
            .borderRadius($r('sys.float.composeListItem_Image_Radius'))
            .focusable(false)
            .draggable(false)
            .flexShrink(0)
        } else {
          if ((this.iconStyle as IconTypeV2) <= IconTypeV2.PREVIEW) {
            Image(this.icon as Resource)
              .objectFit(ImageFit.Contain)
              .width(ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2))
              .height(ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2))
              .borderRadius($r('sys.float.composeListItem_Image_Radius'))
              .focusable(false)
              .draggable(false)
              .fillColor(this.getContentItemIconFillColor())
              .flexShrink(0)
          } else {
            Image(this.icon as Resource)
              .objectFit(ImageFit.Contain)
              .constraintSize({
                minWidth: SPECIAL_ICON_SIZE,
                maxWidth: ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2),
                minHeight: SPECIAL_ICON_SIZE,
                maxHeight: ICON_SIZE_MAP.get(this.iconStyle as IconTypeV2)
              })
              .borderRadius($r('sys.float.composeListItem_Image_Radius'))
              .focusable(false)
              .draggable(false)
              .fillColor(this.getContentItemIconFillColor())
              .flexShrink(0)
          }
        }
      }
    }
  }

  @Builder
  createText() {
    Column({ space: TEXT_COLUMN_SPACE } as ColumnOptions) {
      if (this.primaryText != null) {
        Text(this.primaryText as ResourceStr)
          .fontSize(this.primaryTextSize)
          .fontColor(this.primaryTextColors)
          .textOverflow({
            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
              TextOverflow.Ellipsis
          })
          .fontWeight(FontWeight.Medium)
          .focusable(true)
          .draggable(false)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
              this.isWrapFirstText = this.judgeIsWrap(this.primaryText as ResourceStr, this.primaryTextSize,
                newValue.height as number);
            }
          })
      }
      if (this.secondaryText != null) {
        Text(this.secondaryText as ResourceStr)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.secondaryTextColors)
          .textOverflow({
            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
              TextOverflow.Ellipsis
          })
          .draggable(false)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
              this.isWrapSecondText = this.judgeIsWrap(this.secondaryText as ResourceStr, this.secondaryThirdTextSize,
                newValue.height as number);
            }
          })
      }
      if (this.description != null) {
        Text(this.description as ResourceStr)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.descriptionColors)
          .textOverflow({
            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
              TextOverflow.Ellipsis
          })
          .draggable(false)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
              this.isWrapThirdText = this.judgeIsWrap(this.description as ResourceStr, this.secondaryThirdTextSize,
                newValue.height as number);
            }
          })
      }
    }
    .flexShrink(1)
    .margin(this.fontSizeScale as number >= Decimal.div(FontSizeScaleLevel.LEVEL1, 100).toNumber() ? undefined : {
      top: TEXT_SAFE_MARGIN,
      bottom: TEXT_SAFE_MARGIN
    } as Margin)
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
      space: { main: this.getItemSpace() } as FlexSpaceOptions,
      direction: this.itemDirection ?? FlexDirection.Row,
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
    } as LocalizedMargin)
    .padding({ start: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedPadding)
    .flexShrink(this.isParentColumnDirection() ? 0 : 1)
  }
}

interface CreateIconParam {
  icon?: OperateIconV2;
}

class OperateItemStructController {
  public changeRadioState = (): void => {
  };
  public changeCheckboxState = (): void => {
  };
  public changeSwitchState = (): void => {
  };
}

@ComponentV2
struct OperateItemStructV2 {
  @Param arrow: OperateIconV2 | undefined = undefined;
  @Param icon: OperateIconV2 | undefined = undefined;
  @Param subIcon: OperateIconV2 | undefined = undefined;
  @Param button: OperateButtonV2 | undefined = undefined;
  @Param toggle: OperateCheckV2 | undefined = undefined;
  @Param checkBox: OperateCheckV2 | undefined = undefined;
  @Param radio: OperateCheckV2 | undefined = undefined;
  @Param image: ResourceStr | undefined = undefined;
  @Param symbolStyle: SymbolGlyphModifier | undefined = undefined;
  @Param text: ResourceStr | undefined = undefined;
  @Local switchState: boolean = false;
  @Local radioState: boolean = false;
  @Local checkBoxState: boolean = false;
  @Param rightWidth: string = RIGHT_PART_WIDTH;
  @Local secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Local hoveringColor: ResourceColor = '#0d000000';
  @Local activedColor: ResourceColor = '#1a0a59f7';
  @Param parentCanFocus: boolean = false;
  @Param parentCanTouch: boolean = false;
  @Param parentIsHover: boolean = false;
  @Param parentCanHover: boolean = false;
  @Param parentIsActive: boolean = false;
  @Param parentFrontColor?: ResourceColor = undefined;
  // V2: @Param is readonly, use @Local to track local modifications
  @Local localParentCanFocus: boolean = false;
  @Local localParentCanHover: boolean = false;
  @Local localParentFrontColor: ResourceColor | undefined = undefined;
  @Param parentDirection: FlexDirection = FlexDirection.Row;
  @Local rowSpace: number = DEFAULT_ROW_SPACE;
  @Param isFocus: boolean = false;
  @Local secondaryTextSize: Length = $r('sys.float.ohos_id_text_size_body2');
  @Local secondaryTextColors: ResourceColor = $r('sys.color.font_secondary');
  @Local iconColor: ResourceColor = $r('sys.color.composeListItem_right_icon_normal_color');
  private controller: OperateItemStructController = new OperateItemStructController();

  onWillApplyTheme(theme: Theme): void {
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.hoveringColor = theme.colors.interactiveHover;
    this.activedColor = theme.colors.interactiveActive;
  }

  @Monitor(['isFocus'])
  onFocusChange(_monitor: IMonitor): void {
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
      this.secondaryTextColors = $r('sys.color.composeListItem_right_text_focus_color');
    } else {
      this.secondaryTextColors = this.secondaryTextColor;
    }
    this.iconColor = this.isFocus ? $r('sys.color.composeListItem_right_icon_focus_color') :
      $r('sys.color.composeListItem_right_icon_normal_color');
  }

  @Monitor(['arrow', 'icon', 'subIcon', 'button', 'toggle', 'checkBox', 'radio', 'image', 'symbolStyle', 'text'])
  onPropChange(_monitor: IMonitor): void {
    if (this.toggle != null) {
      this.switchState = this.toggle?.isCheck ? true : false
    }
    if (this.radio != null) {
      this.radioState = this.radio?.isCheck ? true : false
    }
    if (this.checkBox != null) {
      this.checkBoxState = this.checkBox?.isCheck ? true : false
    }
    if ((this.button == null && this.image == null && this.symbolStyle == null && this.text != null) &&
      ((this.icon != null) || (this.icon == null && this.arrow != null))) {
      this.rowSpace = SPECICAL_ROW_SPACE;
    } else {
      this.rowSpace = DEFAULT_ROW_SPACE;
    }
  }

  aboutToAppear(): void {
    if (this.controller) {
      this.controller.changeRadioState = this.changeRadioState;
      this.controller.changeCheckboxState = this.changeCheckboxState;
      this.controller.changeSwitchState = this.changeSwitchState;
    }
  }

  changeRadioState(): void {
    this.radioState = !this.radioState;
  };

  changeCheckboxState(): void {
    this.checkBoxState = !this.checkBoxState;
  };

  changeSwitchState(): void {
    this.switchState = !this.switchState;
  };

  @Builder
  createButton() {
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      Row() {
        Text(this.button?.text as ResourceStr)
          .focusable(true)
      }
      .padding({
        left: TEXT_SAFE_MARGIN,
        right: TEXT_SAFE_MARGIN
      } as Padding)
    }
    .padding({ top: 0, bottom: 0 } as Padding)
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
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
      // @Param is readonly in V2, cannot assign to parentCanFocus
    })
    .onHover((isHover: boolean, event: HoverEvent) => {
      // @Param is readonly in V2, cannot assign to parentCanHover/parentFrontColor
      // Note: V2 migration - these parent communication signals are removed
    })
    .accessibilityLevel(this.button?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO)
    .accessibilityText(getAccessibilityText(this.button?.accessibilityText ?? ''))
    .accessibilityDescription(getAccessibilityText(this.button?.accessibilityDescription ?? ''))
  }

  @Builder
  createIcon(param: CreateIconParam) {
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      if (param.icon?.symbolStyle) {
        SymbolGlyph()
          .fontColor([this.iconColor])
          .attributeModifier(param.icon?.symbolStyle)
          .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .focusable(true)
          .draggable(false)
      } else {
        if (Util.isSymbolResource(param.icon?.value)) {
          SymbolGlyph(param.icon?.value as Resource)
            .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
            .fontColor([this.iconColor])
            .focusable(true)
            .draggable(false)
        } else {
          Image(param.icon?.value as ResourceStr)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ICONLIKE_SIZE)
            .focusable(true)
            .fillColor(this.iconColor)
            .draggable(false)
        }
      }
    }
    .shadow(undefined)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      // @Param is readonly in V2
    })
    .onHover((isHover: boolean, event: HoverEvent) => {
      // @Param is readonly in V2, cannot assign to parentCanHover/parentFrontColor
    })
    .onClick(param.icon?.action)
    .accessibilityLevel(getAccessibilityLevelOnAction(param.icon?.accessibilityLevel, param.icon?.action))
    .accessibilityText(getAccessibilityText(param.icon?.accessibilityText ?? ''))
    .accessibilityDescription(getAccessibilityText(param.icon?.accessibilityDescription ?? ''))
    .flexShrink(0)
  }

  @Builder
  createImage() {
    if (Util.isSymbolResource(this.image)) {
      SymbolGlyph(this.image as Resource)
        .fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`)
        .draggable(false)
        .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
    } else {
      Image(this.image as ResourceStr)
        .height(OPERATEITEM_IMAGE_SIZE)
        .width(OPERATEITEM_IMAGE_SIZE)
        .draggable(false)
        .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
    }
  }

  @Builder
  createSymbol() {
    SymbolGlyph()
      .attributeModifier(this.symbolStyle as SymbolGlyphModifier)
      .fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`)
      .effectStrategy(SymbolEffectStrategy.NONE)
      .symbolEffect(new SymbolEffect(), false)
      .draggable(false)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
  }

  @Builder
  createText() {
    Text(this.text as ResourceStr)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
      .fontSize(this.secondaryTextSize)
      .fontColor(this.secondaryTextColors)
      .textOverflow({
        overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
          TextOverflow.None
      })
      .marqueeOptions({
        start: this.isFocus || this.parentIsHover,
        fadeout: true,
        marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
      })
      .maxLines(Double.toInt(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value))
      .draggable(false)
      .flexShrink(1)
  }

  @Builder
  createArrow() {
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      if (this.arrow?.symbolStyle) {
        SymbolGlyph()
          .fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.ohos_id_color_fourth') : this.iconColor])
          .attributeModifier(this.arrow?.symbolStyle)
          .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .focusable(true)
          .draggable(false)
      } else {
        if (Util.isSymbolResource(this.arrow?.value)) {
          SymbolGlyph(this.arrow?.value as Resource)
            .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
            .fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.ohos_id_color_fourth') : this.iconColor])
            .focusable(true)
            .draggable(false)
        } else {
          Image(this.arrow?.value as ResourceStr)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ARROW_WIDTH)
            .focusable(true)
            .fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.ohos_id_color_fourth') : this.iconColor)
            .draggable(false)
            .matchTextDirection(true)
        }
      }
    }
    .shadow(undefined)
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
      (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICONLIKE_SIZE)
    .width(OPERATEITEM_ARROW_WIDTH)
    .onFocus(() => {
      // @Param is readonly in V2
    })
    .stateEffect(this.arrow?.action !== undefined)
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean, event: HoverEvent) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      // @Param is readonly in V2, cannot assign to parentCanHover/parentFrontColor
    })
    .onClick(this.arrow?.action)
    .accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel, this.arrow?.action))
    .accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''))
    .accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''))
  }

  @Builder
  createRadio() {
    Radio({ value: '', group: '' })
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
      .checked(this.radioState)
      .radioStyle({
        uncheckedBorderColor: DEFUALT_RADIO_CHECKBOX_BORDER_COLOR
      })
      .backgroundColor(Color.Transparent)
      .borderRadius(OPERATE_ITEM_RADIUS)
      .onChange((isCheck: boolean) => {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.radioState = isCheck;
        }
        if (this.radio?.onChange) {
          this.radio?.onChange!(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        // @Param is readonly in V2
      })
      .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
      .flexShrink(0)
      .onHover((isHover: boolean, event: HoverEvent) => {
        // @Param is readonly in V2
      })
      .accessibilityLevel(getAccessibilityLevelOnChange(this.radio?.accessibilityLevel, this.radio?.onChange))
      .accessibilityText(getAccessibilityText(this.radio?.accessibilityText ?? ''))
      .accessibilityDescription(getAccessibilityText(this.radio?.accessibilityDescription ?? ''))
  }

  @Builder
  createCheckBox() {
    Checkbox()
      .borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS)
      .unselectedColor(DEFUALT_RADIO_CHECKBOX_BORDER_COLOR)
      .backgroundColor(Color.Transparent)
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) } as LocalizedMargin)
      .select(this.checkBoxState)
      .onChange((isCheck: boolean) => {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.checkBoxState = isCheck;
        }
        if (this.checkBox?.onChange) {
          this.checkBox?.onChange!(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        // @Param is readonly in V2
      })
      .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
      .flexShrink(0)
      .onHover((isHover: boolean, event: HoverEvent) => {
        // @Param is readonly in V2
      })
      .accessibilityLevel(getAccessibilityLevelOnChange(this.checkBox?.accessibilityLevel, this.checkBox?.onChange))
      .accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''))
      .accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''))
  }

  @Builder
  createSwitch() {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.switchState })
        .borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS)
        .backgroundColor(Color.Transparent)
        .onChange((isCheck: boolean) => {
          this.switchState = isCheck;
          if (this.toggle?.onChange) {
            this.toggle?.onChange?.(isCheck);
          }
        })
        .onClick((event: ClickEvent) => {
          this.switchState = !this.switchState;
        })
        .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
        .accessibilityLevel(getAccessibilityLevelOnChange(this.toggle?.accessibilityLevel, this.toggle?.onChange))
        .accessibilityText(getAccessibilityText(this.toggle?.accessibilityText ?? ''))
        .accessibilityDescription(getAccessibilityText(this.toggle?.accessibilityDescription ?? ''))
    }
    .margin({ end: LengthMetrics.vp(SWITCH_PADDING) } as LocalizedMargin)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .justifyContent(FlexAlign.Center)
    .onFocus(() => {
      // @Param is readonly in V2
    })
    .onHover((isHover: boolean, event: HoverEvent) => {
      // @Param is readonly in V2
    })
  }

  @Builder
  createTextArrow() {
    Button({ type: ButtonType.Normal } as ButtonOptions) {
      if (this.parentDirection === FlexDirection.Column) {
        Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
          Text(this.text as ResourceStr)
            .fontSize($r('sys.float.ohos_id_text_size_body2'))
            .fontColor(this.secondaryTextColor)
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH}vp)`
            })
          if (this.arrow?.symbolStyle) {
            SymbolGlyph()
              .fontColor([$r('sys.color.ohos_id_color_fourth')])
              .attributeModifier(this.arrow?.symbolStyle)
              .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(new SymbolEffect(), false)
              .focusable(false)
              .draggable(false)
          } else {
            if (Util.isSymbolResource(this.arrow?.value)) {
              SymbolGlyph(this.arrow?.value as Resource)
                .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
                .fontColor([$r('sys.color.ohos_id_color_fourth')])
                .focusable(false)
                .draggable(false)
            } else {
              Image(this.arrow?.value as ResourceStr)
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
        } as LocalizedPadding)
      } else {
        Row({ space: SPECICAL_ROW_SPACE } as RowOptions) {
          Text(this.text as ResourceStr)
            .fontSize(this.secondaryTextSize)
            .fontColor(this.secondaryTextColors)
            .textOverflow({
              overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
                TextOverflow.None
            })
            .marqueeOptions({
              start: this.isFocus || this.parentIsHover,
              fadeout: true,
              marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
            })
.maxLines(Double.toInt(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value))
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH + OPERATEITEM_ARROW_MARGIN_WIDTH}vp)`
            })
            .margin({ right: OPERATEITEM_ARROW_MARGIN_WIDTH } as Margin)
          if (this.arrow?.symbolStyle) {
            SymbolGlyph()
              .fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.icon_fourth') : this.iconColor])
              .attributeModifier(this.arrow?.symbolStyle)
              .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
              .effectStrategy(SymbolEffectStrategy.NONE)
              .symbolEffect(new SymbolEffect(), false)
              .focusable(false)
              .draggable(false)
          } else {
            if (Util.isSymbolResource(this.arrow?.value)) {
              SymbolGlyph(this.arrow?.value as Resource)
                .fontSize(`${OPERATEITEM_ICONLIKE_SIZE}vp`)
                .fontColor([IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.icon_fourth') : this.iconColor])
                .focusable(false)
                .draggable(false)
            } else {
              Image(this.arrow?.value as ResourceStr)
                .height(OPERATEITEM_ICONLIKE_SIZE)
                .width(OPERATEITEM_ARROW_WIDTH)
                .fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.icon_fourth') : this.iconColor)
                .focusable(false)
                .draggable(false)
                .matchTextDirection(true)
            }
          }
        }
        .padding({
          start: LengthMetrics.vp(TEXT_SAFE_MARGIN),
          end: LengthMetrics.vp(LISTITEM_PADDING)
        } as LocalizedPadding)
      }
    }
    .shadow(undefined)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
      (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None)
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .backgroundColor(Color.Transparent)
    .constraintSize({ minHeight: TEXT_ARROW_HEIGHT })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      // @Param is readonly in V2
    })
    .padding({
      top: 0,
      bottom: 0,
      left: 0,
      right: 0
    } as Padding)
    .stateEffect(this.arrow?.action !== undefined)
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean, event: HoverEvent) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      // @Param is readonly in V2
    })
    .onClick(this.arrow?.action)
    .accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel, this.arrow?.action))
    .accessibilityText(`${this.text} ${getAccessibilityText(this.arrow?.accessibilityText ?? '')}`)
    .accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''))
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
        this.createImage()
      } else if (this.icon != null && this.text != null) {
        this.createText();
        this.createIcon({ icon: this.icon as OperateIconV2 })
      } else if (this.arrow != null && this.text == null) {
        this.createArrow()
      } else if (this.arrow != null && this.text != null) {
        this.createTextArrow();
      } else if (this.text != null) {
        this.createText();
      } else if (this.radio != null) {
        this.createRadio();
      } else if (this.checkBox != null) {
        this.createCheckBox();
      } else if (this.toggle != null) {
        this.createSwitch();
      } else if (this.icon != null) {
        this.createIcon({ icon: this.icon as OperateIconV2 });
        if (this.subIcon != null) {
          this.createIcon({ icon: this.subIcon as OperateIconV2 });
        }
      }
    }
    .width(this.parentDirection === FlexDirection.Column ? undefined : this.rightWidth)
  }
}

/**
 * Obtain accessible text
 *
 * @param resource initial resource
 * @param selected select state
 * @returns string
 */

function getAccessibilityText(resource: ResourceStr): string {
  try {
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource as string;
    } else {
      let uiContent: Context | undefined = UIContext.resolveUIContext()?.getHostContext();
      if (uiContent) {
        resourceString =
          (uiContent as common.UIAbilityContext).resourceManager.getStringSync((resource as Resource).id as Long);
      }
    }
    return resourceString;
  } catch (error) {
    let code: number = (error as ClassCastError).code;
    let message: string = (error as ClassCastError).message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}


/**
 * Obtain accessible level
 *
 * @param resource
 * @param selected
 * @returns string
 */
function getAccessibilityLevelOnChange(accessibilityLevel?: string, onChange?: (value: boolean) => void): string {
  if (accessibilityLevel) {
    return accessibilityLevel;
  }
  if (onChange) {
    return ACCESSIBILITY_LEVEL_YES;
  }
  return ACCESSIBILITY_LEVEL_NO;
}

/**
 * Obtain accessible level
 *
 * @param resource
 * @param selected
 * @returns string
 */
function getAccessibilityLevelOnAction(accessibilityLevel?: string, onAction?: () => void): string {
  if (accessibilityLevel) {
    return accessibilityLevel;
  }
  if (onAction) {
    return ACCESSIBILITY_LEVEL_YES;
  }
  return ACCESSIBILITY_LEVEL_NO;
}

@ComponentV2
export struct ComposeListItemV2 {
  @Param contentItemV2: ContentItemV2 | undefined = undefined;
  @Param operateItemV2: OperateItemV2 | undefined = undefined;
  @Local frontColor: ResourceColor | undefined = $r('sys.color.composeListItem_container_normal_color');
  @Local borderSize: number = 0;
  @Local canFocus: boolean = false;
  @Local canTouch: boolean = true;
  @Local canHover: boolean = true;
  @Local isHover: boolean = false;
  @Local itemHeight: number = Int.toDouble(ItemHeight.FIRST_HEIGHT);
  @Local isActive: boolean = false;
  @Local hoveringColor: ResourceColor = '#0d000000';
  @Local touchDownColor: ResourceColor = '#1a000000';
  @Local activedColor: ResourceColor = '#1a0a59f7';
  @Local focusOutlineColor: ResourceColor = $r('sys.color.ohos_id_color_focused_outline');
  @Local fontSizeScale: number = 1;
  @Local containerDirection: FlexDirection = FlexDirection.Row;
  @Local contentItemDirection: FlexDirection = FlexDirection.Row;
  @Local containerPadding?: Padding | LocalizedPadding | Length = undefined;
  @Local textArrowLeftSafeOffset: number = 0;
  isFollowingSystemFontScale: boolean = this.getUIContext().isFollowingSystemFontScale();
  maxFontScale: number = this.getUIContext().getMaxFontScale();
  private callbackId: number = 0;
  @Local accessibilityTextBuilder: string = '';
  @Local isFocus: boolean = false;
  @Local isWrapText: boolean = false;
  @Local listScale: ScaleOptions = { x: 1, y: 1, z: 0 } as ScaleOptions;
  private operateItemStructRef: OperateItemStructController = new OperateItemStructController();
  envCallback: EnvironmentCallbackEntry = new EnvironmentCallbackEntry(this)
  applicationContext: ApplicationContext = new ApplicationContext()
  @Local NORMAL_BG_COLOR: ResourceColor = $r('sys.color.composeListItem_container_normal_color');

  onWillApplyTheme(theme: Theme): void {
    this.hoveringColor = theme.colors.interactiveHover;
    this.touchDownColor = theme.colors.interactivePressed;
    this.activedColor = theme.colors.interactiveActive;
    this.focusOutlineColor = theme.colors.interactiveFocus;
  }

  @Monitor(['isWrapText'])
  onWrapChange(_monitor: IMonitor): void {
    this.containerPadding = this.getPadding();
  }

  @Monitor(['contentItemV2', 'operateItemV2'])
  onPropChange(_monitor: IMonitor): void {
    this.containerDirection = this.decideContainerDirection();
    this.contentItemDirection = this.decideContentItemDirection();
    if (this.contentItemV2 === undefined) {
      if (this.operateItemV2?.image !== undefined ||
        this.operateItemV2?.symbolStyle !== undefined ||
        this.operateItemV2?.icon !== undefined ||
        this.operateItemV2?.subIcon !== undefined) {
        this.itemHeight = OPERATEITEM_IMAGE_SIZE + SAFE_LIST_PADDING;
      }
      return;
    }

    if (this.contentItemV2?.secondaryText === undefined && this.contentItemV2?.description === undefined) {
      if (this.contentItemV2?.icon === undefined) {
        this.itemHeight = ItemHeight.FIRST_HEIGHT;
      } else {
        const systemIconLineHeight =
          LengthMetrics.resource($r('sys.float.composeListItem_system_icon_line_height')).value as number;
        this.itemHeight =
          (this.contentItemV2?.iconStyle as IconTypeV2) <= IconTypeV2.HEAD_SCULPTURE ?
            Int.toDouble(ItemHeight.SECOND_HEIGHT) : systemIconLineHeight;
      }
    } else if (this.contentItemV2?.description === undefined) {
      let iconStyle: IconTypeV2 = (this.contentItemV2?.iconStyle as IconTypeV2);
      if (this.contentItemV2?.icon === undefined ||
        (this.contentItemV2?.icon !== undefined && iconStyle <= IconTypeV2.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT;
      } else {
        if (iconStyle === IconTypeV2.HEAD_SCULPTURE) {
          this.itemHeight = ItemHeight.FOURTH_HEIGHT;
        } else {
          this.itemHeight = APPICON_ITEMLENGTH;
        }
      }
    } else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT;
    }
    const iconStyle = this.contentItemV2?.iconStyle;
    if (iconStyle !== undefined) {
      const iconSize = ICON_SIZE_MAP.get(iconStyle as number);
      if (iconSize !== undefined && iconSize >= this.itemHeight) {
        this.itemHeight = iconSize + SAFE_LIST_PADDING;
      }
    }
    if (this.operateItemV2?.arrow && this.operateItemV2?.text && this.operateItemV2?.arrow?.action) {
      this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItemV2?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.description ?? '')}
      `;
    } else {
      this.accessibilityTextBuilder = `
        ${getAccessibilityText(this.contentItemV2?.primaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.secondaryText ?? '')}
        ${getAccessibilityText(this.contentItemV2?.description ?? '')}
        ${getAccessibilityText(this.operateItemV2?.text ?? '')}
      `;
    }
  }

  aboutToAppear(): void {
    this.fontSizeScale = this.decideFontSizeScale();
    try {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext
        this.applicationContext = hostContext.getApplicationContext();
        try {
          this.callbackId = this.applicationContext.onEnvironment(this.envCallback);
        } catch (paramError) {
          hilog.error(0x3900, 'Ace',
            `ComposeListItem Failed to get environment param error `);
        }
      }
    } catch (paramError) {
      let code: number = (paramError as ClassCastError).code;
      let message: string = (paramError as ClassCastError).message;
      hilog.error(0x3900, 'Ace',
        `ComposeListItem Failed to get environment param error: ${code}, ${message}`);
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      let context: UIContext = this.getUIContext();
      if (context.getHostContext() !== undefined) {
        this.applicationContext.offEnvironment(this.callbackId.toInt(),
          (err: BusinessError<void> | null): void => {
            hilog.info(0x0000, 'testTag', `applicationContext off environment err: code ${err?.code}`);
          })
      }
    }
    this.callbackId = 0;
  }

  calculatedRightWidth(): string {
    if (this.operateItemV2?.text || this.operateItemV2?.button) {
      return RIGHT_PART_WIDTH;
    }
    if (this.operateItemV2?.toggle) {
      return RIGHT_ONLY_SWITCH_WIDTH;
    } else if (this.operateItemV2?.checkbox) {
      return RIGHT_ONLY_CHECKBOX_WIDTH;
    } else if (this.operateItemV2?.radio) {
      return RIGHT_ONLY_RADIO_WIDTH;
    } else if (this.operateItemV2?.icon) {
      if (this.operateItemV2?.subIcon) {
        return RIGHT_ICON_SUB_ICON_WIDTH;
      }
      return RIGHT_ONLY_IMAGE_WIDTH;
    } else if (this.operateItemV2?.symbolStyle) {
      return RIGHT_ONLY_IMAGE_WIDTH;
    } else if (this.operateItemV2?.image) {
      return RIGHT_ONLY_IMAGE_WIDTH;
    } else if (this.operateItemV2?.arrow) {
      return RIGHT_ONLY_ARROW_WIDTH;
    }
    return RIGHT_CONTENT_NULL_RIGHTWIDTH;
  }

  decideContentItemDirection(): FlexDirection {
    if (this.fontSizeScale >= Decimal.div(FontSizeScaleLevel.LEVEL1, 100).toNumber() &&
      this.contentItemV2?.iconStyle && (this.contentItemV2?.iconStyle as IconTypeV2) > IconTypeV2.HEAD_SCULPTURE) {
      return FlexDirection.Column;
    }
    return FlexDirection.Row;
  }

  decideContainerDirection(): FlexDirection {
    if (this.fontSizeScale < Decimal.div(FontSizeScaleLevel.LEVEL1, 100).toNumber() || !this.contentItemV2) {
      return FlexDirection.Row;
    }
    if (this.operateItemV2?.button) {
      return FlexDirection.Column;
    } else if (this.operateItemV2?.symbolStyle) {
      return FlexDirection.Row;
    } else if (this.operateItemV2?.image) {
      return FlexDirection.Row;
    } else if (this.operateItemV2?.icon && this.operateItemV2?.text) {
      return FlexDirection.Column;
    } else if (this.operateItemV2?.arrow) {
      if (!this.operateItemV2?.text) {
        return FlexDirection.Row;
      }
      this.textArrowLeftSafeOffset = TEXT_SAFE_MARGIN;
      return FlexDirection.Column;
    } else if (this.operateItemV2?.text) {
      return FlexDirection.Column;
    } else {
      return FlexDirection.Row;
    }
  }

  @Monitor(['fontSizeScale'])
  onFontSizeScaleChange(_monitor: IMonitor): void {
    this.containerDirection = this.decideContainerDirection();
    this.contentItemDirection = this.decideContentItemDirection();
    if (this.fontSizeScale >= Decimal.div(FontSizeScaleLevel.LEVEL3, 100).toNumber()) {
      this.containerPadding = {
        top: $r('sys.float.padding_level12'),
        bottom: $r('sys.float.padding_level12'),
      } as Padding;
    } else if (this.fontSizeScale >= Decimal.div(FontSizeScaleLevel.LEVEL2, 100).toNumber()) {
      this.containerPadding = {
        top: $r('sys.float.padding_level10'),
        bottom: $r('sys.float.padding_level10'),
      } as Padding;
    } else if (this.fontSizeScale >= Decimal.div(FontSizeScaleLevel.LEVEL1, 100).toNumber()) {
      this.containerPadding = {
        top: $r('sys.float.padding_level8'),
        bottom: $r('sys.float.padding_level8'),
      } as Padding;
    } else {
      this.containerPadding = this.getPadding();
    }
  }

  isSingleLine(): boolean {
    return !this.contentItemV2?.secondaryText && !this.contentItemV2?.description;
  }

  getOperateOffset(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Row) {
      return LengthMetrics.vp(0);
    }
    let iconStyleVal: number | undefined = this.contentItemV2?.iconStyle;
    let iconSize: number = iconStyleVal !== undefined ? (ICON_SIZE_MAP.get(iconStyleVal) as number ?? 0) : 0;
    if (this.contentItemV2?.icon && iconSize && (iconSize as number) <= HEADSCULPTURE_SIZE) {
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
    let context: UIContext = this.getUIContext();
    if (context.getHostContext() !== undefined) {
      return Math.min(
        this.maxFontScale,
        (this.getUIContext().getHostContext() as common.UIAbilityContext)?.config.fontSizeScale ?? 1)
    }
    return 1
  }

  getPadding(): Padding | undefined {
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
      let paddingNum = LengthMetrics.resource(ITEM_PADDING).value;
      let compareSize = paddingNum > LISTITEM_PADDING;
      let horizontalPadding: number = compareSize ? paddingNum - LISTITEM_PADDING : 0;
      return {
        top: this.isWrapText ? paddingNum : 0,
        bottom: this.isWrapText ? paddingNum : 0,
        left: horizontalPadding,
        right: horizontalPadding
      } as Padding;
    } else {
      return undefined;
    }
  }

  build() {
    Stack() {
      Flex(this.getFlexOptions()) {
        if (this.contentItemV2 === null) {
          ContentItemStructV2({
            isWrapText: this.isWrapText
          })
        }
        if (this.contentItemV2 !== null) {
          ContentItemStructV2({
            icon: this.contentItemV2?.icon,
            symbolStyle: this.contentItemV2?.symbolStyle,
            iconStyle: this.contentItemV2?.iconStyle,
            primaryText: this.contentItemV2?.primaryText,
            secondaryText: this.contentItemV2?.secondaryText,
            description: this.contentItemV2?.description,
            fontSizeScale: this.fontSizeScale,
            parentDirection: this.containerDirection,
            itemDirection: this.contentItemDirection,
            isFocus: this.isFocus,
            itemHeight: this.itemHeight,
            isWrapText: this.isWrapText
          });
        }
        if (this.operateItemV2 !== null) {
          Column() {
            OperateItemStructV2({
              icon: this.operateItemV2?.icon,
              subIcon: this.operateItemV2?.subIcon,
              button: this.operateItemV2?.button,
              toggle: this.operateItemV2?.toggle,
              checkBox: this.operateItemV2?.checkbox,
              radio: this.operateItemV2?.radio,
              image: this.operateItemV2?.image,
              symbolStyle: this.operateItemV2?.symbolStyle,
              text: this.operateItemV2?.text,
              arrow: this.operateItemV2?.arrow,
              parentCanFocus: this.canFocus,
              parentCanTouch: this.canTouch,
              parentIsHover: this.isHover,
              parentFrontColor: this.frontColor,
              parentIsActive: this.isActive,
              parentCanHover: this.canHover,
              rightWidth: this.calculatedRightWidth(),
              parentDirection: this.containerDirection,
              isFocus: this.isFocus
              // Note: controller is not passed from parent in V2, it's initialized in aboutToAppear
            })
          }
          .flexShrink(0)
          .onFocus(() => {
            this.canFocus = false;
          })
          .onBlur(() => {
            this.canFocus = true;
          })
          .padding({ start: this.getOperateOffset() });
        }
      }
      .height(this.containerDirection === FlexDirection.Column ? 'auto' : undefined)
      .constraintSize({
        minHeight: this.itemHeight
      })
      .focusable(IS_SUPPORT_SUBCOMPONENT_EVENT)
      .borderRadius($r('sys.float.composeListItem_radius'))
      .backgroundColor(this.frontColor)
      .onFocus(() => {
        this.canFocus = true;
      })
      .onBlur(() => {
        this.canFocus = false;
      })
      .onHover((isHover: boolean, event: HoverEvent) => {
        if (this.isFocus && !IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.isHover = false;
          return;
        }
        this.isHover = isHover;
        if (this.canHover) {
          this.frontColor = isHover ? this.hoveringColor :
            (this.isActive ? this.activedColor : Color.Transparent.toString());
        }
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.frontColor = isHover ? FOCUSED_BG_COLOR : this.NORMAL_BG_COLOR;
          if (isHover) {
            this.zoomIn()
          } else {
            this.zoomOut()
          }
        }
      })
      .border({
        radius: $r('sys.float.composeListItem_radius'),
        width: this.isFocus ? ITEM_BORDER_SHOWN : 0,
        color: this.isFocus ? this.focusOutlineColor : $r('sys.color.composeListItem_stroke_normal_color'),
        style: BorderStyle.Solid
      })
      .padding(this.containerPadding)
    }
    .width('100%')
    .accessibilityGroup(true)
    .accessibilityText(this.accessibilityTextBuilder)
    .onFocus(() => {
      this.isFocus = true;
      this.frontColor = FOCUSED_BG_COLOR;
      this.zoomIn();
    })
    .onBlur(() => {
      this.isFocus = false;
      this.frontColor = this.NORMAL_BG_COLOR;
      this.zoomOut();
    })
    .borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : $r('sys.float.composeListItem_radius'))
    .onClick(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : () => {
      if (this.operateItemV2?.icon && this.operateItemV2?.icon?.action) {
        this.operateItemV2?.icon?.action?.();
      }
      if (this.operateItemV2?.subIcon && this.operateItemV2?.subIcon?.action) {
        this.operateItemV2?.subIcon?.action?.();
      }
      if (this.operateItemV2?.arrow && this.operateItemV2?.arrow?.action) {
        this.operateItemV2?.arrow?.action?.();
      }
      if (this.operateItemV2?.radio) {
        this.operateItemStructRef.changeRadioState();
      }
      if (this.operateItemV2?.checkbox) {
        this.operateItemStructRef.changeCheckboxState();
      }
      if (this.operateItemV2?.toggle) {
        this.operateItemStructRef.changeSwitchState();
      }
    })
    .scale(this.listScale)
    .shadow(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined :
      (this.isFocus ? FOCUSED_SHADOW as ShadowStyle : NORMAL_SHADOW as ShadowStyle))
    .margin({
      left: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined,
      right: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined
    } as Margin)
    .padding({
      left: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0,
      right: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0
    } as Padding)
  }

  private zoomIn(): void {
    this.listScale = {
      x: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : FOCUSED_ITEM_SCALE,
      y: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : FOCUSED_ITEM_SCALE
    };
  }

  private zoomOut(): void {
    this.listScale = {
      x: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : RECOVER_ITEM_SCALE,
      y: IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : RECOVER_ITEM_SCALE
    };
  }
}
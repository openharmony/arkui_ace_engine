/*
 * Copyright (c) 2026-2026 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License"),
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
import measure from '@ohos.measure';
import emitter from '@ohos.events.emitter';

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

type OnActionCallback = () => void;
type OnChangeCallback = (value: boolean) => void;

export interface OperateIconV2Options {
  value?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  action?: OnActionCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface OperateCheckV2Options {
  isCheck?: boolean;
  onChange?: OnChangeCallback;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface OperateButtonV2Options {
  text?: ResourceStr;
  accessibilityText?: ResourceStr;
  accessibilityDescription?: ResourceStr;
  accessibilityLevel?: string;
}

export interface ContentItemV2Options {
  iconStyle?: IconTypeV2;
  icon?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  primaryText?: ResourceStr;
  secondaryText?: ResourceStr;
  description?: ResourceStr;
}

export interface OperateItemV2Options {
  icon?: OperateIconV2;
  subIcon?: OperateIconV2;
  button?: OperateButtonV2;
  toggle?: OperateCheckV2;
  checkbox?: OperateCheckV2;
  radio?: OperateCheckV2;
  image?: ResourceStr;
  symbolStyle?: SymbolGlyphModifier;
  text?: ResourceStr;
  arrow?: OperateIconV2;
}

@ObservedV2
export class OperateIconV2 {
  @Trace public value: ResourceStr = '';
  @Trace public symbolStyle?: SymbolGlyphModifier;
  @Trace public action?: OnActionCallback;
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public accessibilityLevel?: string;

  constructor(options?: OperateIconV2Options) {
    if (options) {
      if (options.value !== undefined) {
        this.value = options.value;
      }
      if (options.symbolStyle !== undefined) {
        this.symbolStyle = options.symbolStyle;
      }
      if (options.action !== undefined) {
        this.action = options.action;
      }
      if (options.accessibilityText !== undefined) {
        this.accessibilityText = options.accessibilityText;
      }
      if (options.accessibilityDescription !== undefined) {
        this.accessibilityDescription = options.accessibilityDescription;
      }
      if (options.accessibilityLevel !== undefined) {
        this.accessibilityLevel = options.accessibilityLevel;
      }
    }
  }
}

@ObservedV2
export class OperateCheckV2 {
  @Trace public isCheck?: boolean;
  @Trace public onChange?: OnChangeCallback;
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public accessibilityLevel?: string;

  constructor(options?: OperateCheckV2Options) {
    if (options) {
      if (options.isCheck !== undefined) {
        this.isCheck = options.isCheck;
      }
      if (options.onChange !== undefined) {
        this.onChange = options.onChange;
      }
      if (options.accessibilityText !== undefined) {
        this.accessibilityText = options.accessibilityText;
      }
      if (options.accessibilityDescription !== undefined) {
        this.accessibilityDescription = options.accessibilityDescription;
      }
      if (options.accessibilityLevel !== undefined) {
        this.accessibilityLevel = options.accessibilityLevel;
      }
    }
  }
}

@ObservedV2
export class OperateButtonV2 {
  @Trace public text?: ResourceStr;
  @Trace public accessibilityText?: ResourceStr;
  @Trace public accessibilityDescription?: ResourceStr;
  @Trace public accessibilityLevel?: string;

  constructor(options?: OperateButtonV2Options) {
    if (options) {
      if (options.text !== undefined) {
        this.text = options.text;
      }
      if (options.accessibilityText !== undefined) {
        this.accessibilityText = options.accessibilityText;
      }
      if (options.accessibilityDescription !== undefined) {
        this.accessibilityDescription = options.accessibilityDescription;
      }
      if (options.accessibilityLevel !== undefined) {
        this.accessibilityLevel = options.accessibilityLevel;
      }
    }
  }
}

@ObservedV2
export class ContentItemV2 {
  @Trace public iconStyle?: IconTypeV2;
  @Trace public icon?: ResourceStr;
  @Trace public symbolStyle?: SymbolGlyphModifier;
  @Trace public primaryText?: ResourceStr;
  @Trace public secondaryText?: ResourceStr;
  @Trace public description?: ResourceStr;

  constructor(options?: ContentItemV2Options) {
    if (options) {
      if (options.iconStyle !== undefined) {
        this.iconStyle = options.iconStyle;
      }
      if (options.icon !== undefined) {
        this.icon = options.icon;
      }
      if (options.symbolStyle !== undefined) {
        this.symbolStyle = options.symbolStyle;
      }
      if (options.primaryText !== undefined) {
        this.primaryText = options.primaryText;
      }
      if (options.secondaryText !== undefined) {
        this.secondaryText = options.secondaryText;
      }
      if (options.description !== undefined) {
        this.description = options.description;
      }
    }
  }
}

@ObservedV2
export class OperateItemV2 {
  @Trace public icon?: OperateIconV2;
  @Trace public subIcon?: OperateIconV2;
  @Trace public button?: OperateButtonV2;
  @Trace public toggle?: OperateCheckV2;
  @Trace public checkbox?: OperateCheckV2;
  @Trace public radio?: OperateCheckV2;
  @Trace public image?: ResourceStr;
  @Trace public symbolStyle?: SymbolGlyphModifier;
  @Trace public text?: ResourceStr;
  @Trace public arrow?: OperateIconV2;

  constructor(options?: OperateItemV2Options) {
    if (options) {
      if (options.icon !== undefined) {
        this.icon = options.icon;
      }
      if (options.subIcon !== undefined) {
        this.subIcon = options.subIcon;
      }
      if (options.button !== undefined) {
        this.button = options.button;
      }
      if (options.toggle !== undefined) {
        this.toggle = options.toggle;
      }
      if (options.checkbox !== undefined) {
        this.checkbox = options.checkbox;
      }
      if (options.radio !== undefined) {
        this.radio = options.radio;
      }
      if (options.image !== undefined) {
        this.image = options.image;
      }
      if (options.symbolStyle !== undefined) {
        this.symbolStyle = options.symbolStyle;
      }
      if (options.text !== undefined) {
        this.text = options.text;
      }
      if (options.arrow !== undefined) {
        this.arrow = options.arrow;
      }
    }
  }
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
const OPERATEITEM_ARROW_WIDTH = 12;
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
const ACCESSIBILITY_LEVEL_AUTO = 'auto';
const ACCESSIBILITY_LEVEL_YES = 'yes';
const ACCESSIBILITY_LEVEL_NO = 'no';
const RESOURCE_TYPE_SYMBOL: number = 40000;

const EVENT_IS_WRAP_TEXT_CHANGE = 10001;
const EVENT_PARENT_CAN_FOCUS_CHANGE = 10002;
const EVENT_PARENT_CAN_HOVER_CHANGE = 10003;
const EVENT_PARENT_FRONT_COLOR_CHANGE = 10004;

const ICON_SIZE_MAP: Map<number, number> = new Map([
  [IconTypeV2.BADGE, BADGE_SIZE],
  [IconTypeV2.NORMAL_ICON, SMALL_ICON_SIZE],
  [IconTypeV2.SYSTEM_ICON, SYSTEM_ICON_SIZE],
  [IconTypeV2.HEAD_SCULPTURE, HEADSCULPTURE_SIZE],
  [IconTypeV2.APP_ICON, APP_ICON_SIZE],
  [IconTypeV2.PREVIEW, PREVIEW_SIZE],
  [IconTypeV2.LONGITUDINAL, LONGITUDINAL_SIZE],
  [IconTypeV2.VERTICAL, VERTICAL_SIZE]
]);

const IS_SUPPORT_SUBCOMPONENT_EVENT: boolean =
  LengthMetrics.resource($r('sys.float.composeListItem_focus_dynamic_effect')).value !== 1;
const RECOVER_ITEM_SCALE: number = 1;
const CLEAR_SHADOW: ShadowStyle = -1;
const OPERATE_ITEM_RADIUS: number = 50;
const DEFUALT_RADIO_CHECKBOX_BORDER_COLOR: ResourceColor = $r('sys.color.ohos_id_color_switch_outline_off');
const TEXT_SUPPORT_MARQUEE: number = 1;
const IS_MARQUEE_OR_ELLIPSIS: number = LengthMetrics.resource($r('sys.float.composeListItem_right_textOverflow')).value;
const UNUSUAL: number = -1;
const FOCUSED_BG_COLOR: ResourceColor = $r('sys.color.composeListItem_container_focus_color');
const NORMAL_BG_COLOR: ResourceColor = $r('sys.color.composeListItem_container_normal_color');
const FOCUSED_ITEM_SCALE: number = LengthMetrics.resource($r('sys.float.composeListItem_focus_magnification')).value;
const FOCUSED_SHADOW: ShadowStyle = LengthMetrics.resource($r('sys.float.composeListItem_focus_shadow_attribute'))
  .value as ShadowStyle;
const NORMAL_SHADOW: ShadowStyle = LengthMetrics.resource($r('sys.float.composeListItem_normal_shadow_attribute'))
  .value as ShadowStyle;
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

@ComponentV2
struct ContentItemStruct {
  @Param iconStyle: IconTypeV2 | null = null;
  @Param icon: ResourceStr | null = null;
  @Param symbolStyle: SymbolGlyphModifier | null = null;
  @Param primaryText: ResourceStr | null = null;
  @Param secondaryText: ResourceStr | null = null;
  @Param description: ResourceStr | null = null;
  @Local itemRowSpace: number = NORMAL_ITEM_ROW_SPACE;
  @Param leftWidth: string = LEFT_PART_WIDTH;
  @Local primaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_primary');
  @Local secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Local descriptionColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Param fontSizeScale: number = 1;
  @Param parentDirection: FlexDirection = FlexDirection.Row;
  @Param itemDirection: FlexDirection = FlexDirection.Row;
  @Param isFocus: boolean = false;
  @Local primaryTextSize: string | number | Resource = $r('sys.float.ohos_id_text_size_body1');
  @Local primaryTextColors: ResourceColor = $r('sys.color.font_primary');
  @Param itemHeight: number | null = null;
  @Local iconColor: ResourceColor | null = null;
  @Local secondaryTextColors: ResourceColor = $r('sys.color.font_secondary');
  @Local secondaryThirdTextSize: string | number | Resource =
    $r('sys.float.composeListItem_left_secondary_tertiary_text_size');
  @Local descriptionColors: ResourceColor = $r('sys.color.font_tertiary');
  @Local isWrapText: boolean = false;
  @Local isWrapFirstText: boolean = false;
  @Local isWrapSecondText: boolean = false;
  @Local isWrapThirdText: boolean = false;

  @Monitor('iconStyle', 'icon', 'symbolStyle', 'primaryText', 'secondaryText', 'description', 'isFocus')
  onPropChange(): void {
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
      this.primaryTextColors = this.primaryTextColor;
      this.secondaryTextColors = this.secondaryTextColor;
      this.descriptionColors = this.descriptionColor;
    }
  }

  @Monitor('isWrapFirstText', 'isWrapSecondText', 'isWrapThirdText')
  onWrapChange(): void {
    this.isWrapText = this.isWrapFirstText || this.isWrapSecondText || this.isWrapThirdText;
    let eventData: emitter.EventData = {
      data: { isWrapText: this.isWrapText }
    };
    emitter.emit({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, eventData);
  }

  onWillApplyTheme(theme: Theme): void {
    this.primaryTextColor = theme.colors.fontPrimary;
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.descriptionColor = theme.colors.fontTertiary;
  }

  getContentItemIconFillColor(): ResourceColor {
    switch (this.iconStyle) {
      case IconTypeV2.BADGE:
        return $r('sys.color.composeListItem_badge_color');
      case IconTypeV2.SYSTEM_ICON:
        return $r('sys.color.composeListItem_icon_normal_color');
      default:
        return $r('sys.color.ohos_id_color_secondary');
    }
  }

  judgeIsWrap(text: ResourceStr | null, sizeResource: Length, newHeight: number): boolean {
    let singleRowHeight = this.getSingleRowTextHeight(text, sizeResource);
    return newHeight > singleRowHeight;
  }

  getSingleRowTextHeight(text: ResourceStr | null, sizeResource: Length): number {
    if (text && sizeResource) {
      let textSize = measure.measureTextSize({
        textContent: text,
        fontSize: sizeResource,
        maxLines: TEXT_MAX_LINE
      });
      if (textSize && textSize.height) {
        let heightValue: number = 0;
        if (typeof textSize.height === 'number') {
          heightValue = textSize.height;
        } else if (typeof textSize.height === 'string') {
          heightValue = parseFloat(textSize.height);
        }
        let singleRowHeight = px2vp(heightValue);
        return singleRowHeight;
      }
    }
    return 0;
  }

  aboutToAppear(): void {
    this.onPropChange();
  }

  @Builder
  createIcon() {
    if (this.iconStyle != null && ICON_SIZE_MAP.has(this.iconStyle)) {
      if (this.symbolStyle != null) {
        SymbolGlyph()
          .fontColor([this.getContentItemIconFillColor()])
          .attributeModifier(this.symbolStyle)
          .fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`)
          .effectStrategy(SymbolEffectStrategy.NONE)
          .symbolEffect(new SymbolEffect(), false)
          .borderRadius($r('sys.float.composeListItem_Image_Radius'))
          .focusable(false)
          .draggable(false)
          .flexShrink(0)
      } else if (this.icon != null) {
        if (Util.isSymbolResource(this.icon)) {
          SymbolGlyph(this.icon as Resource)
            .fontSize(`${ICON_SIZE_MAP.get(this.iconStyle)}vp`)
            .fontColor([this.getContentItemIconFillColor()])
            .borderRadius($r('sys.float.composeListItem_Image_Radius'))
            .focusable(false)
            .draggable(false)
            .flexShrink(0)
        } else {
          if (this.iconStyle <= IconTypeV2.PREVIEW) {
            Image(this.icon)
              .objectFit(ImageFit.Contain)
              .width(ICON_SIZE_MAP.get(this.iconStyle))
              .height(ICON_SIZE_MAP.get(this.iconStyle))
              .borderRadius($r('sys.float.composeListItem_Image_Radius'))
              .focusable(false)
              .draggable(false)
              .fillColor(this.getContentItemIconFillColor())
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
    Column({ space: TEXT_COLUMN_SPACE }) {
      Text(this.primaryText)
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
          if (!IS_SUPPORT_SUBCOMPONENT_EVENT && newValue.height) {
            let heightValue = typeof newValue.height === 'number' ? newValue.height : 0;
            this.isWrapFirstText = this.judgeIsWrap(this.primaryText, this.primaryTextSize, heightValue);
          }
        })
      if (this.secondaryText != null) {
        Text(this.secondaryText)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.secondaryTextColors)
          .textOverflow({
            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
            TextOverflow.Ellipsis
          })
          .draggable(false)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && newValue.height) {
              let heightValue = typeof newValue.height === 'number' ? newValue.height : 0;
              this.isWrapSecondText = this.judgeIsWrap(this.secondaryText, this.secondaryThirdTextSize, heightValue);
            }
          })
      }
      if (this.description != null) {
        Text(this.description)
          .fontSize(this.secondaryThirdTextSize)
          .fontColor(this.descriptionColors)
          .textOverflow({
            overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.None :
            TextOverflow.Ellipsis
          })
          .draggable(false)
          .onSizeChange((oldValue: SizeOptions, newValue: SizeOptions) => {
            if (!IS_SUPPORT_SUBCOMPONENT_EVENT && newValue.height) {
              let heightValue = typeof newValue.height === 'number' ? newValue.height : 0;
              this.isWrapThirdText = this.judgeIsWrap(this.description, this.secondaryThirdTextSize, heightValue);
            }
          })
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
  public icon?: OperateIconV2;
}

class OperateItemStructController {
  public changeRadioState = () => {};
  public changeCheckboxState = () => {};
  public changeToggleState = () => {};
}

@ComponentV2
struct OperateItemStruct {
  @Param arrow: OperateIconV2 | null = null;
  @Param icon: OperateIconV2 | null = null;
  @Param subIcon: OperateIconV2 | null = null;
  @Param button: OperateButtonV2 | null = null;
  @Param toggle: OperateCheckV2 | null = null;
  @Param checkBox: OperateCheckV2 | null = null;
  @Param radio: OperateCheckV2 | null = null;
  @Param image: ResourceStr | null = null;
  @Param symbolStyle: SymbolGlyphModifier | null = null;
  @Param text: ResourceStr | null = null;
  @Local toggleState: boolean = false;
  @Local radioState: boolean = false;
  @Local checkBoxState: boolean = false;
  @Param rightWidth: string = RIGHT_PART_WIDTH;
  @Local secondaryTextColor: ResourceColor = $r('sys.color.ohos_id_color_text_secondary');
  @Local hoveringColor: ResourceColor = '#0d000000';
  @Local activedColor: ResourceColor = '#1a0a59f7';
  @Param parentCanFocus: boolean = false;
  @Param parentCanTouch: boolean = true;
  @Param parentIsHover: boolean = false;
  @Param parentCanHover: boolean = true;
  @Param parentIsActive: boolean = false;
  @Param parentFrontColor: ResourceColor = NORMAL_BG_COLOR;
  @Param parentDirection: FlexDirection = FlexDirection.Row;
  @Local rowSpace: number = DEFAULT_ROW_SPACE;
  @Param isFocus: boolean = false;
  @Local secondaryTextSize: Length = $r('sys.float.ohos_id_text_size_body2');
  @Local secondaryTextColors: ResourceColor = $r('sys.color.font_secondary');
  @Local iconColor: ResourceColor = $r('sys.color.composeListItem_right_icon_normal_color');
  private controller: OperateItemStructController = new OperateItemStructController();

  @Monitor('arrow', 'icon', 'subIcon', 'button', 'toggle', 'checkBox', 'radio', 'image', 'symbolStyle', 'text')
  onPropChange(): void {
    if (this.toggle != null) {
      this.toggleState = this.toggle.isCheck as boolean;
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

  @Monitor('isFocus')
  onFocusChange(): void {
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT && this.isFocus) {
      this.secondaryTextColors = $r('sys.color.composeListItem_right_text_focus_color');
    } else {
      this.secondaryTextColors = this.secondaryTextColor;
    }
    this.iconColor = this.isFocus ? $r('sys.color.composeListItem_right_icon_focus_color') :
    $r('sys.color.composeListItem_right_icon_normal_color');
  }

  onWillApplyTheme(theme: Theme): void {
    this.secondaryTextColor = theme.colors.fontSecondary;
    this.hoveringColor = theme.colors.interactiveHover;
    this.activedColor = theme.colors.interactiveActive;
  }

  aboutToAppear(): void {
    this.onPropChange();
    this.onFocusChange();
    if (this.controller) {
      this.controller.changeRadioState = this.changeRadioState;
      this.controller.changeCheckboxState = this.changeCheckboxState;
      this.controller.changeToggleState = this.changeToggleState;
    }
  }

  changeRadioState = () => {
    this.radioState = !this.radioState;
  };
  changeCheckboxState = () => {
    this.checkBoxState = !this.checkBoxState;
  };
  changeToggleState = () => {
    this.toggleState = !this.toggleState;
  };

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
      this.notifyParentCanFocusChange(false);
    })
    .onHover((isHover: boolean) => {
      this.notifyParentCanHoverChange(false);
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
        this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
      }
      if (!isHover) {
        this.notifyParentCanHoverChange(true);
        if (this.parentIsHover) {
          this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
        }
      }
    })
    .accessibilityLevel(this.button?.accessibilityLevel ?? ACCESSIBILITY_LEVEL_AUTO)
    .accessibilityText(getAccessibilityText(this.button?.accessibilityText ?? ''))
    .accessibilityDescription(getAccessibilityText(this.button?.accessibilityDescription ?? ''))
  }

  @Builder
  createIcon(param: CreateIconParam) {
    Button({ type: ButtonType.Normal }) {
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
          Image(param.icon?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ICONLIKE_SIZE)
            .focusable(true)
            .fillColor(this.iconColor)
            .draggable(false)
        }
      }
    }
    .shadow(CLEAR_SHADOW)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.notifyParentCanFocusChange(false);
    })
    .onHover((isHover: boolean) => {
      this.notifyParentCanHoverChange(false);
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
        this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
      }
      if (!isHover) {
        this.notifyParentCanHoverChange(true);
        if (this.parentIsHover) {
          this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
        }
      }
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
      .fontSize(`${OPERATEITEM_IMAGE_SIZE}vp`)
      .effectStrategy(SymbolEffectStrategy.NONE)
      .symbolEffect(new SymbolEffect(), false)
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
        overflow: IS_MARQUEE_OR_ELLIPSIS === TEXT_SUPPORT_MARQUEE ? TextOverflow.MARQUEE :
        TextOverflow.None
      })
      .marqueeOptions({
        start: this.isFocus || this.parentIsHover,
        fadeout: true,
        marqueeStartPolicy: MarqueeStartPolicy.DEFAULT
      })
      .maxLines(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value)
      .draggable(false)
      .flexShrink(1)
  }

  @Builder
  createArrow() {
    Button({ type: ButtonType.Normal }) {
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
          Image(this.arrow?.value)
            .height(OPERATEITEM_ICONLIKE_SIZE)
            .width(OPERATEITEM_ARROW_WIDTH)
            .focusable(true)
            .fillColor(IS_SUPPORT_SUBCOMPONENT_EVENT ? $r('sys.color.ohos_id_color_fourth') : this.iconColor)
            .draggable(false)
            .matchTextDirection(true)
        }
      }
    }
    .shadow(CLEAR_SHADOW)
    .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
      (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None)
    .backgroundColor(Color.Transparent)
    .height(OPERATEITEM_ICONLIKE_SIZE)
    .width(OPERATEITEM_ARROW_WIDTH)
    .onFocus(() => {
      this.notifyParentCanFocusChange(false);
    })
    .stateEffect(this.arrow?.action !== undefined)
    .hoverEffect(this.arrow?.action !== undefined ? HoverEffect.Auto : HoverEffect.None)
    .onHover((isHover: boolean) => {
      if (this.arrow?.action === undefined) {
        return;
      }
      if (isHover && IS_SUPPORT_SUBCOMPONENT_EVENT) {
        this.notifyParentCanHoverChange(false);
        this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
      } else {
        this.notifyParentCanHoverChange(true);
        if (this.parentIsHover) {
          this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
        }
      }
    })
    .onClick(this.arrow?.action)
    .accessibilityLevel(getAccessibilityLevelOnAction(this.arrow?.accessibilityLevel, this.arrow?.action))
    .accessibilityText(getAccessibilityText(this.arrow?.accessibilityText ?? ''))
    .accessibilityDescription(getAccessibilityText(this.arrow?.accessibilityDescription ?? ''))
  }

  @Builder
  createRadio() {
    Radio({ value: '', group: '' })
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
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
          this.radio?.onChange(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        this.notifyParentCanFocusChange(false);
      })
      .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
      .flexShrink(0)
      .onHover((isHover: boolean) => {
        this.notifyParentCanHoverChange(false);
        if (isHover && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
        if (!isHover) {
          this.notifyParentCanHoverChange(true);
          if (this.parentIsHover) {
            this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
          }
        }
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
      .margin({ end: LengthMetrics.vp(LISTITEM_PADDING) })
      .select(this.checkBoxState)
      .onChange((isCheck: boolean) => {
        if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.checkBoxState = isCheck;
        }
        if (this.checkBox?.onChange) {
          this.checkBox?.onChange(isCheck);
        }
      })
      .height(OPERATEITEM_ICONLIKE_SIZE)
      .width(OPERATEITEM_ICONLIKE_SIZE)
      .padding(OPERATEITEM_SELECTIONBOX_PADDING_SIZE)
      .onFocus(() => {
        this.notifyParentCanFocusChange(false);
      })
      .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
      .flexShrink(0)
      .onHover((isHover: boolean) => {
        this.notifyParentCanHoverChange(false);
        if (isHover && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
          this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
        }
        if (!isHover) {
          this.notifyParentCanHoverChange(true);
          if (this.parentIsHover) {
            this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
              (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
          }
        }
      })
      .accessibilityLevel(getAccessibilityLevelOnChange(this.checkBox?.accessibilityLevel, this.checkBox?.onChange))
      .accessibilityText(getAccessibilityText(this.checkBox?.accessibilityText ?? ''))
      .accessibilityDescription(getAccessibilityText(this.checkBox?.accessibilityDescription ?? ''))
  }

  @Builder
  createToggle() {
    Row() {
      Toggle({ type: ToggleType.Switch, isOn: this.toggleState })
        .borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? UNUSUAL : OPERATE_ITEM_RADIUS)
        .backgroundColor(Color.Transparent)
        .onChange((isCheck: boolean) => {
          this.toggleState = isCheck;
          if (this.toggle?.onChange) {
            this.toggle?.onChange(isCheck);
          }
        })
        .onClick(() => {
          this.toggleState = !this.toggleState;
        })
        .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ? HitTestMode.Block : HitTestMode.None)
        .accessibilityLevel(getAccessibilityLevelOnChange(this.toggle?.accessibilityLevel, this.toggle?.onChange))
        .accessibilityText(getAccessibilityText(this.toggle?.accessibilityText ?? ''))
        .accessibilityDescription(getAccessibilityText(this.toggle?.accessibilityDescription ?? ''))
    }
    .margin({ end: LengthMetrics.vp(SWITCH_PADDING) })
    .height(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .width(OPERATEITEM_ICON_CLICKABLE_SIZE)
    .justifyContent(FlexAlign.Center)
    .onFocus(() => {
      this.notifyParentCanFocusChange(false);
    })
    .onHover((isHover: boolean) => {
      this.notifyParentCanHoverChange(false);
      if (isHover && this.parentFrontColor === this.hoveringColor && IS_SUPPORT_SUBCOMPONENT_EVENT) {
        this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
      }
      if (!isHover) {
        this.notifyParentCanHoverChange(true);
        if (this.parentIsHover) {
          this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
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
            .maxLines(LengthMetrics.resource($r('sys.float.composeListItem_maxLines_right')).value)
            .focusable(true)
            .draggable(false)
            .constraintSize({
              maxWidth: `calc(100% - ${OPERATEITEM_ARROW_WIDTH + OPERATEITEM_ARROW_MARGIN_WIDTH}vp)`
            })
            .margin({ right: OPERATEITEM_ARROW_MARGIN_WIDTH })
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
              Image(this.arrow?.value)
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
        })
      }
    }
    .shadow(CLEAR_SHADOW)
    .hitTestBehavior(IS_SUPPORT_SUBCOMPONENT_EVENT ?
      (this.arrow?.action !== undefined ? HitTestMode.Block : HitTestMode.Transparent) : HitTestMode.None)
    .labelStyle({
      maxLines: TEXT_MAX_LINE
    })
    .backgroundColor(Color.Transparent)
    .constraintSize({ minHeight: TEXT_ARROW_HEIGHT })
    .borderRadius($r('sys.float.ohos_id_corner_radius_clicked'))
    .onFocus(() => {
      this.notifyParentCanFocusChange(false);
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
      if (isHover && IS_SUPPORT_SUBCOMPONENT_EVENT) {
        this.notifyParentCanHoverChange(false);
        this.notifyParentFrontColorChange(this.parentIsActive ? this.activedColor : Color.Transparent.toString());
      } else {
        this.notifyParentCanHoverChange(true);
        if (this.parentIsHover) {
          this.notifyParentFrontColorChange(this.parentIsHover ? this.hoveringColor :
            (this.parentIsActive ? this.activedColor : Color.Transparent.toString()));
        }
      }
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

  private notifyParentCanFocusChange(value: boolean): void {
    emitter.emit({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, { data: { canFocus: value } });
  }

  private notifyParentCanHoverChange(value: boolean): void {
    emitter.emit({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, { data: { canHover: value } });
  }

  private notifyParentFrontColorChange(value: ResourceColor): void {
    emitter.emit({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, { data: { frontColor: value } });
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
      } else if (this.arrow != null && (this.text == null || this.text == '')) {
        this.createArrow();
      } else if (this.arrow != null && this.text != null) {
        this.createTextArrow();
      } else if (this.text != null) {
        this.createText();
      } else if (this.radio != null) {
        this.createRadio();
      } else if (this.checkBox != null) {
        this.createCheckBox();
      } else if (this.toggle != null) {
        this.createToggle();
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

function getAccessibilityText(resource: ResourceStr): string {
  try {
    let resourceString: string = '';
    if (typeof resource === 'string') {
      resourceString = resource;
    } else {
      resourceString = getContext().resourceManager.getStringSync(resource);
    }
    return resourceString;
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `getAccessibilityText error, code: ${code}, message: ${message}`);
    return '';
  }
}

function getAccessibilityLevelOnChange(accessibilityLevel?: string, onChange?: OnChangeCallback): string {
  if (accessibilityLevel) {
    return accessibilityLevel;
  }
  if (onChange) {
    return ACCESSIBILITY_LEVEL_YES;
  }
  return ACCESSIBILITY_LEVEL_NO;
}

function getAccessibilityLevelOnAction(accessibilityLevel?: string, onAction?: OnActionCallback): string {
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
  @Param contentItemV2: ContentItemV2 | null = null;
  @Param operateItemV2: OperateItemV2 | null = null;
  @Local frontColor: ResourceColor = NORMAL_BG_COLOR;
  @Local borderSize: number = 0;
  @Local canFocus: boolean = false;
  @Local canTouch: boolean = true;
  @Local canHover: boolean = true;
  @Local isHover: boolean = false;
  @Local itemHeight: number = ItemHeight.FIRST_HEIGHT;
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
  private isFollowingSystemFontScale = this.getUIContext().isFollowingSystemFontScale();
  private maxFontScale = this.getUIContext().getMaxFontScale();
  private callbackId: number | undefined = undefined;
  @Local accessibilityTextBuilder: string = '';
  @Local isFocus: boolean = false;
  @Local isWrapText: boolean = false;
  @Local listScale: ScaleOptions = { x: 1, y: 1 };
  private operateItemStructRef = new OperateItemStructController();

  @Monitor('contentItemV2', 'operateItemV2')
  onPropChange(): void {
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
        let iconStyleValue = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
        this.itemHeight = iconStyleValue <= IconTypeV2.HEAD_SCULPTURE ?
        ItemHeight.SECOND_HEIGHT :
          (LengthMetrics.resource($r('sys.float.composeListItem_system_icon_line_height')).value);
      }
    } else if (this.contentItemV2.description === undefined) {
      let iconStyle = this.contentItemV2.iconStyle ?? IconTypeV2.BADGE;
      if (this.contentItemV2.icon === undefined ||
        (this.contentItemV2.icon !== undefined && iconStyle <= IconTypeV2.SYSTEM_ICON)) {
        this.itemHeight = ItemHeight.THIRD_HEIGHT;
      } else {
        this.itemHeight = iconStyle === IconTypeV2.HEAD_SCULPTURE ? ItemHeight.FOURTH_HEIGHT : APPICON_ITEMLENGTH;
      }
    } else {
      this.itemHeight = ItemHeight.FIFTH_HEIGHT;
    }
    let iconStyleForSize = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
    let iconSizeFromMap = ICON_SIZE_MAP.get(iconStyleForSize);
    if (iconSizeFromMap !== undefined && iconSizeFromMap >= this.itemHeight) {
      this.itemHeight = iconSizeFromMap + SAFE_LIST_PADDING;
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

  @Monitor('isWrapText')
  onWrapChange(): void {
    this.containerPadding = this.getPadding();
  }

  @Monitor('fontSizeScale')
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
      this.containerPadding = this.getPadding();
    }
  }

  onWillApplyTheme(theme: Theme): void {
    this.hoveringColor = theme.colors.interactiveHover;
    this.touchDownColor = theme.colors.interactivePressed;
    this.activedColor = theme.colors.interactiveActive;
    this.focusOutlineColor = theme.colors.interactiveFocus;
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
        `ComposeListItemV2 Faild to get environment param error: ${code}, ${message}`);
    }
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
      this.onFontSizeScaleChange();
    }
    emitter.on({ eventId: EVENT_IS_WRAP_TEXT_CHANGE }, (eventData: emitter.EventData) => {
      if (eventData.data && eventData.data.isWrapText !== undefined) {
        this.isWrapText = eventData.data.isWrapText;
      }
    });
    emitter.on({ eventId: EVENT_PARENT_CAN_FOCUS_CHANGE }, (eventData: emitter.EventData) => {
      if (eventData.data && eventData.data.canFocus !== undefined) {
        this.canFocus = eventData.data.canFocus;
      }
    });
    emitter.on({ eventId: EVENT_PARENT_CAN_HOVER_CHANGE }, (eventData: emitter.EventData) => {
      if (eventData.data && eventData.data.canHover !== undefined) {
        this.canHover = eventData.data.canHover;
      }
    });
    emitter.on({ eventId: EVENT_PARENT_FRONT_COLOR_CHANGE }, (eventData: emitter.EventData) => {
      if (eventData.data && eventData.data.frontColor !== undefined) {
        this.frontColor = eventData.data.frontColor;
      }
    });
  }

  private envCallback: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      if (config === undefined || !this.isFollowingSystemFontScale) {
        this.fontSizeScale = 1;
        return;
      }
      try {
        this.fontSizeScale = Math.min(
          this.maxFontScale, config.fontSizeScale ?? 1);
      } catch (paramError) {
        let code = (paramError as BusinessError).code;
        let message = (paramError as BusinessError).message;
        hilog.error(0x3900, 'Ace',
          `ComposeListItemV2 environmentCallback error: ${code}, ${message}`);
      }
    },
    onMemoryLevel: (level) => {
    }
  };

  aboutToDisappear(): void {
    if (this.callbackId) {
      this.getUIContext()
      ?.getHostContext()
      ?.getApplicationContext()
      ?.off('environment', this.callbackId);
      this.callbackId = void (0);
    }
    emitter.off(EVENT_IS_WRAP_TEXT_CHANGE);
    emitter.off(EVENT_PARENT_CAN_FOCUS_CHANGE);
    emitter.off(EVENT_PARENT_CAN_HOVER_CHANGE);
    emitter.off(EVENT_PARENT_FRONT_COLOR_CHANGE);
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
      return RIGHT_ONLY_ICON_WIDTH;
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
    if (this.fontSizeScale >= FontSizeScaleLevel.LEVEL1 &&
      this.contentItemV2?.iconStyle && this.contentItemV2?.iconStyle > IconTypeV2.HEAD_SCULPTURE) {
      return FlexDirection.Column;
    }
    return FlexDirection.Row;
  }

  decideContainerDirection(): FlexDirection {
    if (this.fontSizeScale < FontSizeScaleLevel.LEVEL1 || !this.contentItemV2) {
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

  isSingleLine(): boolean {
    return !this.contentItemV2?.secondaryText && !this.contentItemV2?.description;
  }

  getOperateOffset(): LengthMetrics {
    if (this.containerDirection === FlexDirection.Row) {
      return LengthMetrics.vp(0);
    }
    let iconStyleValue = this.contentItemV2?.iconStyle ?? IconTypeV2.BADGE;
    let iconSize = ICON_SIZE_MAP.get(iconStyleValue);
    if (this.contentItemV2?.icon && iconSize !== undefined && iconSize <= HEADSCULPTURE_SIZE) {
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
    );
  }

  getPadding(): Padding | undefined {
    if (!IS_SUPPORT_SUBCOMPONENT_EVENT) {
      let paddingNum = LengthMetrics.resource(ITEM_PADDING).value;
      let compareSize = paddingNum > LISTITEM_PADDING;
      let horizontalPadding = compareSize ? paddingNum - LISTITEM_PADDING : 0;
      return {
        top: this.isWrapText ? paddingNum : 0,
        bottom: this.isWrapText ? paddingNum : 0,
        left: horizontalPadding,
        right: horizontalPadding
      };
    } else {
      return undefined;
    }
  }

  build() {
    Stack() {
      Flex(this.getFlexOptions()) {
        if (this.contentItemV2 === null) {
          ContentItemStruct();
        }
        if (this.contentItemV2 !== null) {
          ContentItemStruct({
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
            itemHeight: this.itemHeight
          });
        }
        if (this.operateItemV2 !== null) {
          OperateItemStruct({
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
      .focusable(IS_SUPPORT_SUBCOMPONENT_EVENT)
      .borderRadius($r('sys.float.composeListItem_radius'))
      .backgroundColor(this.frontColor)
      .onFocus(() => {
        this.canFocus = true;
      })
      .onBlur(() => {
        this.canFocus = false;
      })
      .onHover((isHover: boolean) => {
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
          this.frontColor = isHover ? FOCUSED_BG_COLOR : NORMAL_BG_COLOR;
          isHover ? this.zoomIn() : this.zoomOut();
        }
      })
      .stateStyles({
        focused: {
          .border({
            radius: $r('sys.float.composeListItem_radius'),
            width: ITEM_BORDER_SHOWN,
            color: this.focusOutlineColor,
            style: BorderStyle.Solid
          })
        },
        normal: {
          .border({
            radius: $r('sys.float.composeListItem_radius'),
            color: $r('sys.color.composeListItem_stroke_normal_color'),
            width: $r('sys.float.composeListItem_stroke_normal_thickness'),
          })
        },
        pressed: {
          .backgroundColor(this.touchDownColor)
        }
      })
      .padding(this.containerPadding);
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
      this.frontColor = NORMAL_BG_COLOR;
      this.zoomOut();
    })
    .borderRadius(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : $r('sys.float.composeListItem_radius'))
    .onClick(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : () => {
      if (this.operateItemV2?.icon && this.operateItemV2.icon?.action) {
        this.operateItemV2.icon.action();
      }
      if (this.operateItemV2?.subIcon && this.operateItemV2.subIcon?.action) {
        this.operateItemV2.subIcon.action();
      }
      if (this.operateItemV2?.arrow && this.operateItemV2.arrow?.action) {
        this.operateItemV2.arrow.action();
      }
      if (this.operateItemV2?.radio) {
        this.operateItemStructRef.changeRadioState();
      }
      if (this.operateItemV2?.checkbox) {
        this.operateItemStructRef.changeCheckboxState();
      }
      if (this.operateItemV2?.toggle) {
        this.operateItemStructRef.changeToggleState();
      }
    })
    .scale(this.listScale)
    .shadow(IS_SUPPORT_SUBCOMPONENT_EVENT ? undefined : (this.isFocus ? FOCUSED_SHADOW : NORMAL_SHADOW))
    .margin({
      left: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined,
      right: !IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : undefined
    })
    .padding({
      left: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0,
      right: IS_SUPPORT_SUBCOMPONENT_EVENT ? STACK_PADDING : 0
    });
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
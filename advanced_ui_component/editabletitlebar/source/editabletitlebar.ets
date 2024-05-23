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

import { BusinessError } from '@ohos.base';
import hilog from '@ohos.hilog';
import { KeyCode } from '@ohos.multimodalInput.keyCode';
import resourceManager from '@ohos.resourceManager';
import { Theme } from '@ohos.arkui.theme';
import { LengthMetrics } from '@ohos.arkui.node';

export enum EditableLeftIconType {
  Back,
  Cancel,
}

export declare interface EditableTitleBarMenuItem {
  value: ResourceStr;
  isEnabled: boolean;
  action?: () => void;
}

export type EditableTitleBarItem = EditableTitleBarMenuItem;

export declare interface EditableTitleBarOptions {
  backgroundColor?: ResourceColor;
  backgroundBlurStyle?: BlurStyle;
  safeAreaTypes?: Array<SafeAreaType>;
  safeAreaEdges?: Array<SafeAreaEdge>;
}

enum ItemType {
  Image,
  Icon,
  LeftIcon,
}

const PUBLIC_CANCEL = $r('sys.media.ohos_ic_public_cancel');

const PUBLIC_OK = $r('sys.media.ohos_ic_public_ok');

const PUBLIC_BACK = $r('sys.media.ohos_ic_compnent_titlebar_back');

class EditableTitleBarTheme {
  public iconColor: ResourceColor = $r('sys.color.titlebar_icon_color');
  public iconBackgroundColor: ResourceColor = $r('sys.color.titlebar_icon_background_color');
  public iconBackgroundPressedColor: ResourceColor = $r('sys.color.titlebar_icon_background_pressed_color');
  public iconBackgroundHoverColor: ResourceColor = $r('sys.color.titlebar_icon_background_hover_color');
  public iconBackgroundFocusOutlineColor: ResourceColor = $r('sys.color.titlebar_icon_background_focus_outline_color');
  public titleColor: ResourceColor = $r('sys.color.titlebar_title_tertiary_color');
  public subTitleColor: ResourceColor = $r('sys.color.titlebar_subheader_color');
}

@Component
export struct EditableTitleBar {
  leftIconStyle: EditableLeftIconType = EditableLeftIconType.Back;
  title: ResourceStr = '';
  subtitle?: ResourceStr = '';
  isSaveIconRequired: boolean = true;
  imageItem?: EditableTitleBarItem;
  menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  options: EditableTitleBarOptions = {
    safeAreaTypes: [SafeAreaType.SYSTEM],
    safeAreaEdges: [SafeAreaEdge.TOP],
  };
  onSave?: () => void;
  onCancel?: () => void;
  @State titleMaxWidth: number = 0;
  @State contentMargin?: LocalizedMargin = undefined;
  @State titleBarMargin: LocalizedMargin = {
    start: LengthMetrics.vp(0),
    end: LengthMetrics.vp(0),
  }
  static maxCountOfExtraItems = 3;
  static maxOtherCountOfExtraItems = 2;
  static countOfImageItem = 0;
  static countOfSaveIcon = 0;
  static readonly commonOne = 1;
  static readonly commonZero = 0;
  static readonly noneColor = '#00000000';
  static readonly defaultHeight: number = getNumberByResource('titlebar_default_height');
  static readonly default_margin_level1: number = getNumberByResource('margin_level1');
  static readonly default_margin_level2: number = getNumberByResource('margin_level2');
  static readonly default_margin_level3: number = getNumberByResource('margin_level3');
  static readonly default_title_padding: number = getNumberByResource('titlebar_icon_background_space_horizontal');
  static readonly totalHeight: number =
    EditableTitleBar.defaultHeight === 0 ? 56 : EditableTitleBar.defaultHeight;
  static readonly margin_level1: number =
    EditableTitleBar.default_margin_level1 === 0 ? 12 : EditableTitleBar.default_margin_level1;
  static readonly margin_level2: number =
    EditableTitleBar.default_margin_level2 === 0 ? 24 : EditableTitleBar.default_margin_level2;
  static readonly margin_level3: number =
    EditableTitleBar.default_margin_level3 === 0 ? 32 : EditableTitleBar.default_margin_level3;
  static readonly titlePadding: number =
    EditableTitleBar.default_title_padding === 0 ? 2 : EditableTitleBar.default_title_padding;
  @Provide editableTitleBarTheme: EditableTitleBarTheme = new EditableTitleBarTheme();

  onWillApplyTheme(theme: Theme): void {
    this.editableTitleBarTheme.iconColor = theme.colors.iconPrimary;
    this.editableTitleBarTheme.titleColor = theme.colors.fontPrimary;
    this.editableTitleBarTheme.subTitleColor = theme.colors.fontSecondary;
    this.editableTitleBarTheme.iconBackgroundColor = theme.colors.compBackgroundTertiary;
    this.editableTitleBarTheme.iconBackgroundPressedColor = theme.colors.interactivePressed;
    this.editableTitleBarTheme.iconBackgroundHoverColor = theme.colors.interactiveHover;
    this.editableTitleBarTheme.iconBackgroundFocusOutlineColor = theme.colors.interactiveFocus;
  }

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch,
    }) {
      GridRow({
        columns: 1,
        breakpoints: { reference: BreakpointsReference.ComponentSize },
      }) {
        GridCol({}) {
          TitleBarSection({
            leftIconStyle: this.leftIconStyle,
            imageItem: this.imageItem,
            title: this.title,
            subtitle: this.subtitle,
            menuItems: this.menuItems,
            isSaveIconRequired: this.isSaveIconRequired,
            onSave: this.onSave,
            onCancel: this.onCancel,
            options: this.options,
            titleMaxWidth: this.titleMaxWidth
          });
        }
      }
      .onBreakpointChange((breakpoints: string) => {
        this.titleBarMargin = updateTitleBarMargin(breakpoints, this.contentMargin);
      })
      .margin(this.titleBarMargin)
      .height(EditableTitleBar.totalHeight)
      .onSizeChange((_oldValue: SizeOptions, newValue: SizeOptions) => {
        this.titleMaxWidth = updateTitleWidth(this.isSaveIconRequired, this.imageItem, this.menuItems, newValue);
      })
    }
    .width('100%')
    .backgroundColor(this.options.backgroundColor ?? EditableTitleBar.noneColor)
    .backgroundBlurStyle(
      this.options.backgroundBlurStyle ?? BlurStyle.NONE)
    .expandSafeArea(
      this.options.safeAreaTypes,
      this.options.safeAreaEdges,
    )
  }
}

@Component
struct TitleBarSection {
  leftIconStyle: EditableLeftIconType = EditableLeftIconType.Back;
  title: ResourceStr = '';
  subtitle?: ResourceStr = '';
  isSaveIconRequired: boolean = true;
  imageItem?: EditableTitleBarItem;
  menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  options: EditableTitleBarOptions = {
    safeAreaTypes: [SafeAreaType.SYSTEM],
    safeAreaEdges: [SafeAreaEdge.TOP],
  };
  onSave?: () => void;
  onCancel?: () => void;
  @Link titleMaxWidth: number;
  @State backActive: boolean = false;
  @Consume editableTitleBarTheme: EditableTitleBarTheme;
  private static readonly maxMainTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * 0.65;
  private static readonly maxSubTitleHeight = (EditableTitleBar.totalHeight - EditableTitleBar.titlePadding) * 0.35;
  private static readonly maxLineOne = 1;
  private static readonly maxLineTwo = 2;

  build() {
    Row() {
      if (this.leftIconStyle === EditableLeftIconType.Back) {
        Navigator()
          .active(this.backActive)

        ImageMenuItem({
          item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
          },
          attribute: ItemType.LeftIcon,
        })
      } else {
        ImageMenuItem({
          item: {
            value: PUBLIC_CANCEL,
            isEnabled: true,
            action: () => this.onCancel && this.onCancel(),
          },
          attribute: ItemType.LeftIcon,
        })
      }
      if (this.imageItem !== undefined) {
        ImageMenuItem({
          item: this.imageItem,
          attribute: ItemType.Image,
        })
      }

      Column() {
        Row() {
          Text(this.title)
            .maxFontSize($r('sys.float.titlebar_title_tertiary_size'))
            .minFontSize($r('sys.float.titlebar_subheader_size'))
            .fontColor(this.editableTitleBarTheme.titleColor)
            .maxLines(this.subtitle ? TitleBarSection.maxLineOne : TitleBarSection.maxLineTwo)
            .fontWeight(FontWeight.Bold)
            .textAlign(TextAlign.Start)
            .textOverflow({ overflow: TextOverflow.Ellipsis })
            .width(this.titleMaxWidth)
            .heightAdaptivePolicy(this.subtitle ? TextHeightAdaptivePolicy.MAX_LINES_FIRST :
            TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
            .constraintSize({
              maxHeight: this.subtitle ? TitleBarSection.maxMainTitleHeight : EditableTitleBar.totalHeight,
            })
        }
        .justifyContent(FlexAlign.Start)

        if (this.subtitle) {
          Row() {
            Text(this.subtitle)
              .maxFontSize($r('sys.float.titlebar_subheader_size'))
              .minFontSize($r('sys.float.Caption_S'))
              .fontColor(this.editableTitleBarTheme.subTitleColor)
              .maxLines(1)
              .fontWeight(FontWeight.Regular)
              .textAlign(TextAlign.Start)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .width(this.titleMaxWidth)
              .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
              .constraintSize({
                maxHeight: this.title ? TitleBarSection.maxSubTitleHeight : EditableTitleBar.totalHeight,
              })
          }
          .margin({
            top: $r('sys.float.padding_level1'),
          })
          .justifyContent(FlexAlign.Start)
        }
      }
      .height(EditableTitleBar.totalHeight)
      .justifyContent(FlexAlign.Center)
      .margin({
        start: LengthMetrics.vp(EditableTitleBar.titlePadding),
      })
      .alignItems(HorizontalAlign.Start)
      .constraintSize({ maxWidth: this.titleMaxWidth })

      EditableTitleBarMenuSection({
        menuItems: this.menuItems,
        onSave: this.onSave,
        isSaveEnabled: this.isSaveIconRequired,
      })
    }
  }
}

@Component
struct EditableTitleBarMenuSection {
  menuItems: Array<EditableTitleBarMenuItem> | undefined = undefined;
  onSave?: () => void;
  isSaveEnabled: boolean = true;

  build() {
    Column() {
      Row() {
        if (this.menuItems !== undefined && this.menuItems.length > EditableTitleBar.commonZero) {
          ForEach(this.menuItems.slice(EditableTitleBar.commonZero,
            this.isSaveEnabled ?
            EditableTitleBar.maxOtherCountOfExtraItems : EditableTitleBar.maxCountOfExtraItems),
            (item: EditableTitleBarMenuItem) => {
              ImageMenuItem({
                item: item,
                attribute: ItemType.Icon,
              })
            })
        }
        if (this.isSaveEnabled) {
          ImageMenuItem({
            item: {
              value: PUBLIC_OK,
              isEnabled: true,
              action: () => this.onSave && this.onSave(),
            },
            attribute: ItemType.Icon,
          })
        }
      }
    }
    .justifyContent(FlexAlign.Center)
  }
}

@Component
struct ImageMenuItem {
  item: EditableTitleBarMenuItem = {
    value: '',
    isEnabled: true,
  };
  attribute: ItemType = ItemType.Image;
  static readonly imageHotZoneWidth = getNumberByResource('titlebar_icon_background_width');
  static readonly imageHotZoneHeight = getNumberByResource('titlebar_icon_background_height');
  static readonly iconBackgroundSpaceHorizontal = getNumberByResource('titlebar_icon_background_space_horizontal');
  @State isOnFocus: boolean = false;
  @State isOnHover: boolean = false;
  @State isOnClick: boolean = false;
  @Consume editableTitleBarTheme: EditableTitleBarTheme;

  @Styles
  focusedStyle() {
    .border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: $r('sys.float.titlebar_icon_background_focus_outline_weight'),
      color: this.editableTitleBarTheme.iconBackgroundFocusOutlineColor,
      style: BorderStyle.Solid,
    })
  }

  @Styles
  notInFocusedStyle() {
    .border({
      radius: $r('sys.float.titlebar_icon_background_shape'),
      width: EditableTitleBar.commonZero,
    })
  }

  @Styles
  buttonStateStyles() {
    .stateStyles({
      focused: this.focusedStyle,
      normal: this.notInFocusedStyle,
      pressed: this.notInFocusedStyle,
    })
  }

  @Styles
  buttonEventStyle() {
    .onFocus(() => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnFocus = true;
    })
    .onBlur(() => this.isOnFocus = false)
    .onHover((isOn) => {
      if (!this.item.isEnabled) {
        return;
      }
      this.isOnHover = isOn;
    })
    .onKeyEvent((event) => {
      if (!this.item.isEnabled) {
        return;
      }
      if (event.keyCode !== KeyCode.KEYCODE_ENTER && event.keyCode !== KeyCode.KEYCODE_SPACE) {
        return;
      }
      if (event.type === KeyType.Down) {
        this.isOnClick = true;
      }
      if (event.type === KeyType.Up) {
        this.isOnClick = false;
      }
    })
    .onTouch((event) => {
      if (!this.item.isEnabled) {
        return;
      }
      if (event.type === TouchType.Down) {
        this.isOnClick = true;
      }
      if (event.type === TouchType.Up) {
        this.isOnClick = false;
      }
    })
    .onClick(() => this.item.isEnabled && this.item.action && this.item.action())
  }

  @Styles
  backgroundButtonStyle() {
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneHeight)
    .focusable(this.item.isEnabled)
    .enabled(this.item.isEnabled)
  }

  getFgColor(): ResourceStr {
    if (this.isOnClick) {
      return $r('sys.color.titlebar_icon_background_pressed_color');
    } else if (this.isOnHover) {
      return $r('sys.color.titlebar_icon_background_hover_color');
    } else {
      return EditableTitleBar.noneColor;
    }
  }

  getBgColor(): ResourceColor {
    if (this.isOnClick) {
      return this.editableTitleBarTheme.iconBackgroundPressedColor;
    } else if (this.isOnHover) {
      return this.editableTitleBarTheme.iconBackgroundHoverColor;
    } else {
      return this.editableTitleBarTheme.iconBackgroundColor;
    }
  }

  @Builder
  IconBuilder(): void {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      Image(this.item.value)
        .width($r('sys.float.titlebar_icon_width'))
        .height($r('sys.float.titlebar_icon_height'))
        .fillColor(this.editableTitleBarTheme.iconColor)
        .focusable(this.item.isEnabled)
        .enabled(this.item.isEnabled)
        .matchTextDirection(this.item.value == PUBLIC_BACK ? true : false)
    }
    .backgroundButtonStyle()
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      start: LengthMetrics.vp(this.attribute === ItemType.LeftIcon ? EditableTitleBar.commonZero :
      ImageMenuItem.iconBackgroundSpaceHorizontal),
    })
    .foregroundColor(this.getFgColor())
    .backgroundColor(this.getBgColor())
    .buttonStateStyles()
    .buttonEventStyle()
  }

  @Builder
  ImageBuilder() {
    Stack({ alignContent: Alignment.Center }) {
      Image(this.item.value)
        .width(ImageMenuItem.imageHotZoneWidth)
        .height(ImageMenuItem.imageHotZoneHeight)
        .borderRadius($r('sys.float.corner_radius_level10'))
        .focusable(false)
        .enabled(this.item.isEnabled)
        .objectFit(ImageFit.Cover)

      Button({ type: ButtonType.Circle })
        .backgroundButtonStyle()
        .foregroundColor(this.getFgColor())
        .backgroundColor(EditableTitleBar.noneColor)
        .buttonStateStyles()
        .buttonEventStyle()
    }
    .margin({
      start: LengthMetrics.vp(ImageMenuItem.iconBackgroundSpaceHorizontal),
    })
  }

  build() {
    if (this.attribute === ItemType.Icon || this.attribute === ItemType.LeftIcon) {
      this.IconBuilder();
    } else {
      this.ImageBuilder();
    }
  }
}

/**
 * get resource size
 *
 * @param resourceName resource name
 * @return resource size
 */
function getNumberByResource(resourceName: string): number {
  try {
    return resourceManager.getSystemResourceManager().getNumberByName(resourceName);
  } catch (error) {
    let code: number = (error as BusinessError).code;
    let message: string = (error as BusinessError).message;
    hilog.error(0x3900, 'Ace', `EditableTitleBar getNumberByResource error, code: ${code},message:${message}`);
    return EditableTitleBar.commonZero;
  }
}

/**
 * update title width
 */
function updateTitleWidth(isSaveIconRequired: boolean, imageItem: EditableTitleBarItem | undefined,
  menuItems: Array<EditableTitleBarMenuItem> | undefined, size: SizeOptions): number {
  let maxCountOfExtraItems = EditableTitleBar.commonZero;
  let titleMaxWidth = 0;
  if (isSaveIconRequired) {
    maxCountOfExtraItems = EditableTitleBar.maxOtherCountOfExtraItems;
    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonOne;
  } else {
    maxCountOfExtraItems = EditableTitleBar.maxCountOfExtraItems;
    EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonZero;
  }
  if (imageItem) {
    EditableTitleBar.countOfImageItem = EditableTitleBar.commonOne;
  } else {
    EditableTitleBar.countOfImageItem = EditableTitleBar.commonZero;
  }
  let nValue = Number(size.width);
  nValue = nValue - EditableTitleBar.titlePadding - ImageMenuItem.imageHotZoneWidth;
  if (menuItems === undefined) {
    titleMaxWidth = nValue - EditableTitleBar.countOfImageItem *
      (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal) -
      EditableTitleBar.countOfSaveIcon *
        (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal);
    return titleMaxWidth;
  }
  if (menuItems?.length >= EditableTitleBar.maxCountOfExtraItems) {
    titleMaxWidth = nValue -
      ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems -
      EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
      ImageMenuItem.iconBackgroundSpaceHorizontal *
        (maxCountOfExtraItems + EditableTitleBar.countOfSaveIcon +
        EditableTitleBar.countOfImageItem);
  } else {
    titleMaxWidth = nValue -
      ImageMenuItem.imageHotZoneWidth * menuItems?.length -
      ImageMenuItem.imageHotZoneWidth * EditableTitleBar.countOfSaveIcon -
      EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
      ImageMenuItem.iconBackgroundSpaceHorizontal *
        (menuItems?.length + EditableTitleBar.countOfSaveIcon +
        EditableTitleBar.countOfImageItem);
  }
  return titleMaxWidth;
}

/**
 * update title bar margin with breakpoint update
 */
function updateTitleBarMargin(breakpoints: string, contentMargin: LocalizedMargin | undefined): LocalizedMargin {
  let titleBarMargin: LocalizedMargin = {};
  if (breakpoints === 'xs' || breakpoints === 'sm') {
    titleBarMargin = {
      start: contentMargin?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level1),
      end: contentMargin?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level1),
      top: contentMargin?.top ?? LengthMetrics.vp(0),
      bottom: contentMargin?.bottom ?? LengthMetrics.vp(0),
    }
  } else if (breakpoints === 'md') {
    titleBarMargin = {
      start: contentMargin?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level2),
      end: contentMargin?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level2),
      top: contentMargin?.top ?? LengthMetrics.vp(0),
      bottom: contentMargin?.bottom ?? LengthMetrics.vp(0),
    }
  } else {
    titleBarMargin = {
      start: contentMargin?.start ?? LengthMetrics.vp(EditableTitleBar.margin_level3),
      end: contentMargin?.end ?? LengthMetrics.vp(EditableTitleBar.margin_level3),
      top: contentMargin?.top ?? LengthMetrics.vp(0),
      bottom: contentMargin?.bottom ?? LengthMetrics.vp(0),
    }
  }
  return titleBarMargin;
}
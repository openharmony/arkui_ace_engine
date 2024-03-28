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
  @State backActive: boolean = false;
  static maxCountOfExtraItems = 3;
  static maxOtherCountOfExtraItems = 2;
  static countOfImageItem = 0;
  static countOfSaveIcon = 0;
  static readonly commonOne = 1;
  static readonly commonZero = 0;
  static readonly noneColor = '#00000000';
  private static readonly totalHeight = getNumberByResource('titlebar_default_height');
  private static readonly leftMargin = getNumberByResource('titlebar_title_margin_left');
  private static readonly rightMargin = getNumberByResource('titlebar_title_margin_right');
  private static readonly titlePadding = getNumberByResource('titlebar_icon_background_space_horizontal');

  build() {
    Flex({
      justifyContent: FlexAlign.SpaceBetween,
      alignItems: ItemAlign.Stretch,
    }) {
      Row() {
        if (this.leftIconStyle === EditableLeftIconType.Back) {
          Navigator()
            .active(this.backActive)

          ImageMenuItem({ item: {
            value: PUBLIC_BACK,
            isEnabled: true,
            action: () => this.onCancel ? this.onCancel() : this.backActive = true,
          },
            attribute: ItemType.LeftIcon,
          })
        } else {
          ImageMenuItem({ item: {
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
              .fontSize($r('sys.float.titlebar_title_tertiary_size'))
              .fontColor($r('sys.color.titlebar_title_tertiary_color'))
              .maxLines(1)
              .fontWeight(FontWeight.Bold)
              .textAlign(TextAlign.Start)
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .width(this.titleMaxWidth)
          }
          .justifyContent(FlexAlign.Start)

          if (this.subtitle) {
            Row() {
              Text(this.subtitle)
                .fontSize($r('sys.float.titlebar_subheader_size'))
                .fontColor($r('sys.color.titlebar_subheader_color'))
                .maxLines(1)
                .fontWeight(FontWeight.Regular)
                .textAlign(TextAlign.Start)
                .textOverflow({ overflow: TextOverflow.Ellipsis })
                .width(this.titleMaxWidth)
            }
            .margin({
              top: $r('sys.float.padding_level1'),
            })
            .justifyContent(FlexAlign.Start)
          }

        }
        .justifyContent(FlexAlign.Start)
        .padding({
          top: $r('sys.float.padding_level2'),
          bottom: $r('sys.float.padding_level2'),
        })
        .margin({
          left: $r('sys.float.titlebar_icon_background_space_horizontal'),
        })
        .alignItems(HorizontalAlign.Start)
        .constraintSize({ maxWidth: this.titleMaxWidth })

        EditableTitleBarMenuSection({
          menuItems: this.menuItems,
          onSave: this.onSave,
          isSaveEnabled: this.isSaveIconRequired,
        })
      }
      .constraintSize({
        minHeight: EditableTitleBar.totalHeight,
      })
      .margin({
        left: EditableTitleBar.leftMargin,
        right: EditableTitleBar.rightMargin,
      })
    }
    .width('100%')
    .backgroundColor(this.options.backgroundColor ? this.options.backgroundColor :
      EditableTitleBar.noneColor)
    .backgroundBlurStyle(
      this.options.backgroundBlurStyle ? this.options.backgroundBlurStyle : BlurStyle.NONE)
    .expandSafeArea(
      this.options.safeAreaTypes ? this.options.safeAreaTypes : [SafeAreaType.SYSTEM],
      this.options.safeAreaEdges ? this.options.safeAreaEdges : [SafeAreaEdge.TOP])
    .onAreaChange((_oldValue: Area, newValue: Area) => {
      let maxCountOfExtraItems = EditableTitleBar.commonZero;
      if (this.isSaveIconRequired) {
        maxCountOfExtraItems = EditableTitleBar.maxOtherCountOfExtraItems;
        EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonOne;
      } else {
        maxCountOfExtraItems = EditableTitleBar.maxCountOfExtraItems;
        EditableTitleBar.countOfSaveIcon = EditableTitleBar.commonZero;
      }
      if (this.imageItem) {
        EditableTitleBar.countOfImageItem = EditableTitleBar.commonOne;
      } else {
        EditableTitleBar.countOfImageItem = EditableTitleBar.commonZero;
      }
      let nValue = Number(newValue.width);
      nValue = nValue - EditableTitleBar.leftMargin -
        EditableTitleBar.rightMargin - EditableTitleBar.titlePadding;
      nValue = nValue - ImageMenuItem.imageHotZoneWidth;
      if (this.menuItems === undefined) {
        this.titleMaxWidth = nValue -
          EditableTitleBar.countOfImageItem *
            (ImageMenuItem.imageHotZoneWidth +
            ImageMenuItem.iconBackgroundSpaceHorizontal) -
          EditableTitleBar.countOfSaveIcon *
            (ImageMenuItem.imageHotZoneWidth + ImageMenuItem.iconBackgroundSpaceHorizontal);
        return;
      }
      if (this.menuItems?.length >= EditableTitleBar.maxCountOfExtraItems) {
        this.titleMaxWidth = nValue -
          ImageMenuItem.imageHotZoneWidth * EditableTitleBar.maxCountOfExtraItems -
          EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
          ImageMenuItem.iconBackgroundSpaceHorizontal *
            (maxCountOfExtraItems + EditableTitleBar.countOfSaveIcon +
            EditableTitleBar.countOfImageItem);
      } else {
        this.titleMaxWidth = nValue -
          ImageMenuItem.imageHotZoneWidth * this.menuItems?.length -
          ImageMenuItem.imageHotZoneWidth * EditableTitleBar.countOfSaveIcon -
          EditableTitleBar.countOfImageItem * ImageMenuItem.imageHotZoneWidth -
          ImageMenuItem.iconBackgroundSpaceHorizontal *
            (this.menuItems?.length + EditableTitleBar.countOfSaveIcon +
            EditableTitleBar.countOfImageItem);
      }
    })
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

  getFgColor(): ResourceStr {
    if (this.isOnClick) {
      return $r('sys.color.titlebar_icon_background_pressed_color');
    } else if (this.isOnHover) {
      return $r('sys.color.titlebar_icon_background_hover_color');
    } else {
      return EditableTitleBar.noneColor;
    }
  }

  @Builder
  IconBuilder(): void {
    Button({ type: ButtonType.Normal, stateEffect: this.item.isEnabled }) {
      Image(this.item.value)
        .width($r('sys.float.titlebar_icon_width'))
        .height($r('sys.float.titlebar_icon_height'))
        .fillColor($r('sys.color.titlebar_icon_color'))
        .focusable(this.item.isEnabled)
        .enabled(this.item.isEnabled)
    }
    .width(ImageMenuItem.imageHotZoneWidth)
    .height(ImageMenuItem.imageHotZoneWidth)
    .borderRadius($r('sys.float.titlebar_icon_background_shape'))
    .margin({
      left: this.attribute === ItemType.LeftIcon ? EditableTitleBar.commonZero :
        ImageMenuItem.iconBackgroundSpaceHorizontal,
    })
    .focusable(this.item.isEnabled)
    .enabled(this.item.isEnabled)
    .foregroundColor(this.getFgColor())
    .backgroundColor($r('sys.color.titlebar_icon_background_color'))
    .stateStyles({
      focused: {
        .border({
          radius: $r('sys.float.titlebar_icon_background_shape'),
          width: $r('sys.float.titlebar_icon_background_focus_outline_weight'),
          color: $r('sys.color.titlebar_icon_background_focus_outline_color'),
          style: BorderStyle.Solid,
        })
      },
      normal: {
        .border({
          radius: $r('sys.float.titlebar_icon_background_shape'),
          width: EditableTitleBar.commonZero,
        })
      },
      pressed: {
        .border({
          radius: $r('sys.float.titlebar_icon_background_shape'),
          width: EditableTitleBar.commonZero,
        })
      }
    })
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
        .width(ImageMenuItem.imageHotZoneWidth)
        .height(ImageMenuItem.imageHotZoneHeight)
        .backgroundColor(EditableTitleBar.noneColor)
        .focusable(this.item.isEnabled)
        .enabled(this.item.isEnabled)
        .stateStyles({
          focused: {
            .border({
              radius: $r('sys.float.titlebar_icon_background_shape'),
              width: $r('sys.float.titlebar_icon_background_focus_outline_weight'),
              color: $r('sys.color.titlebar_icon_background_focus_outline_color'),
              style: BorderStyle.Solid,
            })
          },
          normal: {
            .border({
              radius: $r('sys.float.titlebar_icon_background_shape'),
              width: EditableTitleBar.commonZero,
            })
          },
          pressed: {
            .border({
              radius: $r('sys.float.titlebar_icon_background_shape'),
              width: EditableTitleBar.commonZero,
            })
          }
        })
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
    .margin({
      left: ImageMenuItem.iconBackgroundSpaceHorizontal,
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
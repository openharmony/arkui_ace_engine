/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
import { UIContext } from '@ohos.arkui.UIContext';
import { ComponentContent } from '@ohos.arkui.node';
import { BusinessError } from '@ohos.base';
import { curves } from '@kit.ArkUI';

const DIALOG_BORDER_RADIUS: Resource = $r('sys.float.ohos_id_corner_radius_default_m');
const DIALOG_INNER_PADDING_SIZE: number = 16;
const DIALOG_MAX_WIDTH: number = 480;
const DIALOG_OFFSET_X: number = 0;
const DIALOG_OFFSET_Y_FOR_BAR: number = -88;
const DIALOG_OFFSET_Y_FOR_NONE: number = -44;

const STANDARD_MIN_COMPONENT_HEIGHT: number = 82;
const STANDARD_MAX_COMPONENT_HEIGHT: number = 94;

const DIALOG_SHADOW_RADIUS: number = 16;
const DIALOG_SHADOW_OFFSET_Y: number = 10;
const DIALOG_SHADOW_COLOR: ResourceStr = '#19000000';

const TITLE_LINE_DISTANCE: number = 2;
const TITLE_MAX_LINE: number = 2;
const SUBTITLE_MAX_LINE: number = 1;
const TEXT_LEFT_MARGIN_SIZE: number = 16;
const SUBTITLE_DEFAULT_COLOR: Resource = $r('sys.color.ohos_id_color_text_secondary_contrary');
const TITLE_DEFAULT_COLOR: Resource = $r('sys.color.ohos_id_color_text_primary_contrary');

const OPERATE_AREA_AVOID_WIDTH: number = 28;

const CLOSE_ICON_DARK_RESOURCE: Resource = $r('sys.color.ohos_id_color_tertiary');
const CLOSE_ICON_LIGHT_RESOURCE: Resource = $r('sys.color.ohos_id_color_primary_contrary');

const CLOSE_BUTTON_BORDER_RADIUS: number = 8;
const CLOSE_BUTTON_ICON_SIZE: number = 16;
const CLOSE_BUTTON_HOT_SPOT_SIZE: number = 32;
const CLOSE_BUTTON_MARGIN: number = 8;
const CLOSE_BUTTON_ICON_OPACITY = 0.6;
const CLOSE_BUTTON_RESPONSE_REGION_OFFSET_X: number = -8;
const CLOSE_BUTTON_RESPONSE_REGION_OFFSET_Y: number = -8;
const CLOSE_BUTTON_OFFSET_X: number = 0;
const CLOSE_BUTTON_OFFSET_Y: number = -50;

const FOREGROUND_IMAGE_OFFSET_X: number = 4;
const FOREGROUND_IMAGE_OFFSET_Y: number = 0;

export enum IconStyle {
  DARK = 0,
  LIGHT = 1
}

export enum TitlePosition {
  TOP = 0,
  BOTTOM = 1
}

export enum BottomOffset {
  OFFSET_FOR_BAR = 0,
  OFFSET_FOR_NONE = 1
}

class DialogParams {
  public options: DialogOptions;
  public defaultCloseAction: Callback<void>;

  constructor(
    options: DialogOptions,
    defaultCloseAction: Callback<void>,
  ) {
    this.options = options;
    this.defaultCloseAction = defaultCloseAction;
  }
}

@Builder
function dialogBuilder(params: DialogParams) {
  Row() {
    Flex() {
      Row() {
        SymbolGlyph($r('sys.symbol.xmark_circle_fill'))
          .fontColor([params.options.iconStyle === IconStyle.DARK ?
            CLOSE_ICON_DARK_RESOURCE : CLOSE_ICON_LIGHT_RESOURCE])
          .borderRadius(CLOSE_BUTTON_BORDER_RADIUS)
          .width(CLOSE_BUTTON_ICON_SIZE)
          .height(CLOSE_BUTTON_ICON_SIZE)
          .opacity(CLOSE_BUTTON_ICON_OPACITY)
          .draggable(false)
          .focusable(true)
          .responseRegion({
            x: CLOSE_BUTTON_RESPONSE_REGION_OFFSET_X,
            y: CLOSE_BUTTON_RESPONSE_REGION_OFFSET_Y,
            width: CLOSE_BUTTON_HOT_SPOT_SIZE,
            height: CLOSE_BUTTON_HOT_SPOT_SIZE
          })
          .margin(CLOSE_BUTTON_MARGIN)
          .alignSelf(ItemAlign.End)
          .offset({
            x: CLOSE_BUTTON_OFFSET_X,
            y: CLOSE_BUTTON_OFFSET_Y
          })
          .onClick(() => {
            if (params.options.onDialogClose !== undefined) {
              params.options.onDialogClose()
            }
            params.defaultCloseAction()
          })

        Image(params.options.foregroundImage)
          .height(STANDARD_MAX_COMPONENT_HEIGHT)
          .objectFit(ImageFit.Contain)
          .fitOriginalSize(true)
          .offset({
            x: FOREGROUND_IMAGE_OFFSET_X,
            y: FOREGROUND_IMAGE_OFFSET_Y
          })
          .alignSelf(ItemAlign.End)
      }
      .padding({ left: OPERATE_AREA_AVOID_WIDTH })
      .direction(Direction.Rtl)
      .defaultFocus(true)
      .align(Alignment.End)
      .alignSelf(ItemAlign.End)
      .constraintSize({
        maxWidth: '50%',
        minWidth: '40%'
      })

      Flex({
        direction: params.options.titlePosition === TitlePosition.BOTTOM ?
          FlexDirection.ColumnReverse : FlexDirection.Column,
        justifyContent: FlexAlign.Center
      }) {
        Text(params.options.title)
          .alignSelf(ItemAlign.Start)
          .maxFontSize($r('sys.float.ohos_id_text_size_sub_title1'))
          .minFontSize(16)
          .fontColor(params.options.titleColor !== undefined ? params.options.titleColor : TITLE_DEFAULT_COLOR)
          .fontWeight(FontWeight.Bold)
          .margin(params.options.titlePosition ? { top: TITLE_LINE_DISTANCE } : { bottom: TITLE_LINE_DISTANCE })
          .maxLines(TITLE_MAX_LINE)
          .wordBreak(WordBreak.BREAK_WORD)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
        Text(params.options.subtitle)
          .alignSelf(ItemAlign.Start)
          .maxFontSize($r('sys.float.ohos_id_text_size_caption'))
          .minFontSize(9)
          .fontColor(params.options.subtitleColor !== undefined ? params.options.subtitleColor : SUBTITLE_DEFAULT_COLOR)
          .maxLines(SUBTITLE_MAX_LINE)
          .wordBreak(WordBreak.BREAK_WORD)
          .textOverflow({ overflow: TextOverflow.Ellipsis })
      }
      .constraintSize({
        maxWidth: '60%',
        minWidth: '50%'
      })
      .flexGrow(1)
      .margin({ left: TEXT_LEFT_MARGIN_SIZE })
    }
    .backgroundColor(params.options.backgroundImage === undefined ? '#EBEEF5' : 'rgba(0,0,0,0)')
    .shadow({
      radius: DIALOG_SHADOW_RADIUS,
      offsetX: 0,
      offsetY: DIALOG_SHADOW_OFFSET_Y,
      color: DIALOG_SHADOW_COLOR
    })
    .height(STANDARD_MIN_COMPONENT_HEIGHT)
    .width('100%')
    .alignSelf(ItemAlign.End)
    .direction(Direction.Rtl)
    .zIndex(1)
    .borderRadius({
      topLeft: DIALOG_BORDER_RADIUS,
      topRight: DIALOG_BORDER_RADIUS,
      bottomLeft: DIALOG_BORDER_RADIUS,
      bottomRight: DIALOG_BORDER_RADIUS
    })
    .onClick(() => {
      if (params.options.onDialogClick !== undefined) {
        params.options.onDialogClick()
      }
      params.defaultCloseAction()
    })

    Image(params.options.backgroundImage)
      .width('100%')
      .height(STANDARD_MIN_COMPONENT_HEIGHT)
      .offset({ x: '-100%', y: 0 })
      .borderRadius(DIALOG_BORDER_RADIUS)
      .zIndex(0)
      .alignSelf(ItemAlign.End)
      .onClick(() => {
        if (params.options.onDialogClose !== undefined) {
          params.options.onDialogClose()
        }
        params.defaultCloseAction()
      })
  }
  .backgroundColor('rgba(0,0,0,0)')
  .width('100%')
  .height(STANDARD_MAX_COMPONENT_HEIGHT)
  .padding({
    left: DIALOG_INNER_PADDING_SIZE,
    right: DIALOG_INNER_PADDING_SIZE
  })
  .constraintSize({
    minHeight: STANDARD_MIN_COMPONENT_HEIGHT,
    maxHeight: STANDARD_MAX_COMPONENT_HEIGHT,
    maxWidth: DIALOG_MAX_WIDTH
  })
}

declare interface DialogOptions {
  uiContext: UIContext,
  bottomOffsetType?: BottomOffset,
  title?: ResourceStr,
  subtitle?: ResourceStr,
  titleColor?: ResourceStr | Color,
  subtitleColor?: ResourceStr | Color,
  backgroundImage?: Resource,
  foregroundImage?: Resource,
  iconStyle?: IconStyle,
  titlePosition?: TitlePosition,
  onDialogClick?: Callback<void>,
  onDialogClose?: Callback<void>
}

export class InterstitialDialogAction {
  private uiContext: UIContext;
  private contentNode: ComponentContent<Object>;
  private dialogParam: DialogParams;
  private bottomOffsetType?: BottomOffset;

  constructor(dialogOptions: DialogOptions) {
    this.uiContext = dialogOptions.uiContext;
    this.bottomOffsetType = dialogOptions.bottomOffsetType;
    this.dialogParam = new DialogParams(
      dialogOptions,
      () => {
        this.closeDialog()
      }
    );
    this.contentNode = new ComponentContent(this.uiContext, wrapBuilder(dialogBuilder), this.dialogParam)
  }

  openDialog() {
    if (this.contentNode !== null) {
      this.uiContext.getPromptAction().openCustomDialog(this.contentNode, {
        isModal: false,
        autoCancel: false,
        offset: {
          dx: DIALOG_OFFSET_X,
          dy: this.bottomOffsetType === BottomOffset.OFFSET_FOR_BAR ?
            DIALOG_OFFSET_Y_FOR_BAR : DIALOG_OFFSET_Y_FOR_NONE
        },
        alignment: DialogAlignment.Bottom,
        transition: TransitionEffect.asymmetric(
          TransitionEffect.OPACITY.animation({ duration: 150, curve: Curve.Sharp })
            .combine(TransitionEffect.scale({ x: 0.85, y: 0.85, centerX: '50%', centerY: '85%' })
              .animation({ curve: curves.interpolatingSpring(0, 1, 228, 24)}))
          ,
          TransitionEffect.OPACITY.animation({ duration: 250, curve: Curve.Sharp })
            .combine(TransitionEffect.scale({ x: 0.85, y: 0.85, centerX: '50%', centerY: '85%' })
              .animation({ duration: 250, curve: Curve.Friction }))
        )
      })
        .catch((error: BusinessError) => {
          let message = (error as BusinessError).message
          let code = (error as BusinessError).code
          console.error(`${code}: ${message}`);
        })
    }
  }

  closeDialog() {
    if (this.contentNode !== null) {
      this.uiContext.getPromptAction().closeCustomDialog(this.contentNode)
        .catch((error: BusinessError) => {
          let message = (error as BusinessError).message
          let code = (error as BusinessError).code
          console.error(`${code}: ${message}`);
        })
    }
  }
}
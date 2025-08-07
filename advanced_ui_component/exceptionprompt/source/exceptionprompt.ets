/*
 * Copyright (c) 2023-2025 Huawei Device Co., Ltd.
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
import curves from '@ohos.curves';
import { common, EnvironmentCallback } from '@kit.AbilityKit';
import { BusinessError } from '@kit.BasicServicesKit';
import { hilog } from '@kit.PerformanceAnalysisKit';
import { LengthMetrics, SymbolGlyphModifier } from '@kit.ArkUI';
import { i18n } from '@kit.LocalizationKit';

const START_TIME = 250;
const END_TIME = 200;
const BORDER_RADIUS = 12;
const ZINDEX_NUM = 9;
const SYMBOL_SIZE: number = 24;
const MAX_SYMBOL_FONT_SCALE: number = 2;
const MIN_SYMBOL_FONT_SCALE: number = 1;
const DEFAULT_SYMBOL_FONT_SCALE: number = 1;

export enum MarginType {
  DEFAULT_MARGIN = 0,
  FIT_MARGIN = 1,
}

export interface PromptOptions {
  icon?: ResourceStr,
  symbolStyle?: SymbolGlyphModifier,
  tip?: ResourceStr,
  marginType: MarginType,
  actionText?: ResourceStr,
  marginTop: Dimension,
  isShown?: boolean
}

@Component
export struct ExceptionPrompt {
  @Prop options: PromptOptions
  @State fontSizeScale: number | undefined = undefined;
  touchBackgroundColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent')
  maxAppFontScale: number = 1;
  isFollowingSystemFontScale: boolean = false;
  onTipClick?: () => void = undefined;
  onActionTextClick?: () => void = undefined;
  private callbackId: number | undefined = undefined;
  private callbacks: EnvironmentCallback = {
    onConfigurationUpdated: (config) => {
      this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
    }, onMemoryLevel() {
    }
  };

  @Builder
  TextBuilder() {
    Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
      Row() {
        if (this.options?.symbolStyle !== undefined) {
          SymbolGlyph()
            .fontColor([$r('sys.color.ohos_id_color_warning')])
            .attributeModifier(this.options?.symbolStyle)
            .effectStrategy(SymbolEffectStrategy.NONE)
            .symbolEffect(new SymbolEffect(), false)
            .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
        } else {
          if (Util.isSymbolResource(this.options?.icon)) {
            SymbolGlyph((this.options?.icon as Resource | undefined) ?? $r('sys.symbol.exclamationmark_circle'))
              .fontColor([$r('sys.color.ohos_id_color_warning')])
              .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
          } else {
            Image(this.options?.icon)
              .width('24vp')
              .height('24vp')
              .fillColor($r('sys.color.ohos_id_color_warning'))
          }
        }
        Text(this.options.tip)
          .fontSize($r('sys.float.ohos_id_text_size_body1'))
          .minFontScale(1)
          .maxFontScale(Math.min(this.updateFontScale(), 2))
          .fontColor($r('sys.color.ohos_id_color_warning'))
          .textOverflow({ overflow: TextOverflow.Ellipsis })
          .maxLines(2)
          .margin({ start: LengthMetrics.resource($r('sys.float.ohos_id_dialog_margin_end')) })
          .flexShrink(1)
          .direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr)
      }
      .padding({ right: $r('sys.float.ohos_id_default_padding_end') })
      .width('100%')
      .accessibilityDescription(this.onTipClick ? '' : ' ')
      .onClick(() => {
        this.onTipClick && this.onTipClick();
      })

      if (this.options.actionText) {
        Button({ stateEffect: false, type: ButtonType.Normal }) {
          Row() {
            Text(this.options.actionText)
              .fontSize($r('sys.float.ohos_id_text_size_body2'))
              .minFontScale(1)
              .maxFontScale(Math.min(this.updateFontScale(), 2))
              .fontColor($r('sys.color.ohos_id_color_text_secondary'))
              .maxLines(2)
              .padding(0)
              .margin({ end: LengthMetrics.resource($r('sys.float.ohos_id_text_paragraph_margin_s')) })
              .textOverflow({ overflow: TextOverflow.Ellipsis })
              .flexShrink(1)
              .textAlign(TextAlign.End)
              .direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr)
            SymbolGlyph($r('sys.symbol.chevron_right'))
              .fontSize(`${(this.fontSizeScale ?? DEFAULT_SYMBOL_FONT_SCALE) * SYMBOL_SIZE}vp`)
              .fontColor([$r('sys.color.ohos_id_color_tertiary')])
          }
          .width('100%')
          .justifyContent(FlexAlign.End)
        }
        .backgroundColor(this.touchBackgroundColor)
        .width(this.options.actionText ? 144 : 0)
        .borderRadius($r('sys.float.ohos_id_corner_radius_subtab'))
        .padding({
          right: $r('sys.float.padding_level2'),
        })
        .accessibilityDescription(this.onActionTextClick ? '' : ' ')
        .accessibilityRole(this.onActionTextClick ? AccessibilityRoleType.BUTTON : AccessibilityRoleType.ROLE_NONE)
        .onClick(() => {
          this.onActionTextClick && this.onActionTextClick();
        })
      }
    }
    .padding({
      left: $r('sys.float.ohos_id_notification_margin_start'),
      right: $r('sys.float.ohos_id_text_paragraph_margin_s'),
      top: $r('sys.float.ohos_id_default_padding_start'),
      bottom: $r('sys.float.ohos_id_default_padding_end')
    })
  }

  build() {
    Row() {
      Column() {
        Column() {
          this.TextBuilder()
        }
        .width('100%')
        .borderRadius(BORDER_RADIUS)
        .backgroundColor($r('sys.color.comp_background_warning_secondary'))
        .zIndex(ZINDEX_NUM)
      }
      .padding(this.options.marginType === MarginType.DEFAULT_MARGIN ? {
        left: $r('sys.float.ohos_id_card_margin_start'),
        right: $r('sys.float.ohos_id_card_margin_end')
      } : {
        left: $r('sys.float.ohos_id_max_padding_start'),
        right: $r('sys.float.ohos_id_max_padding_end')
      })
      .transition(
        TransitionEffect.OPACITY.animation({
          curve: curves.cubicBezierCurve(0.33, 0, 0.67, 1),
          duration: this.options.isShown ? START_TIME : END_TIME
        })
      )
      .visibility(this.options.isShown ? Visibility.Visible : Visibility.None)
    }
    .width('100%')
    .position({ y: this.options.marginTop })
    .zIndex(ZINDEX_NUM)
  }

  aboutToAppear() {
    try {
      let uiContent: UIContext = this.getUIContext();
      this.isFollowingSystemFontScale = uiContent.isFollowingSystemFontScale();
      this.maxAppFontScale = uiContent.getMaxFontScale();
      this.fontSizeScale = Math.min(this.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.fontSizeScale = Math.max(this.fontSizeScale, MIN_SYMBOL_FONT_SCALE);
      this.callbackId = uiContent.getHostContext()?.getApplicationContext()?.on('environment', this.callbacks);
    } catch (err) {
      let code: number = (err as BusinessError).code;
      let message: string = (err as BusinessError).message;
      hilog.error(0x3900, 'Ace', `Failed to init fontsizescale info, cause, code: ${code}, message: ${message}`);
    }
  }

  aboutToDisappear(): void {
    if (this.callbackId) {
      this.getUIContext().getHostContext()?.getApplicationContext()?.off('environment', this.callbackId);
      this.callbackId = void (0);
    }
  }

  updateFontScale(): number {
    let uiContent: UIContext = this.getUIContext();
    let systemFontScale: number = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
    if (!this.isFollowingSystemFontScale) {
      return 1;
    }
    return Math.min(systemFontScale, this.maxAppFontScale);
  }
}

class Util {
  private static RESOURCE_TYPE_SYMBOL = 40000;

  public static isSymbolResource(resourceStr: ResourceStr | undefined): boolean {
    if (resourceStr === undefined) {
      return true;
    }
    if (!Util.isResourceType(resourceStr)) {
      return false;
    }
    let resource = resourceStr as Resource;
    return resource.type === Util.RESOURCE_TYPE_SYMBOL;
  }

  public static isResourceType(resource: ResourceStr): boolean {
    if (!resource) {
      return false;
    }
    return typeof resource !== 'string';
  }
}
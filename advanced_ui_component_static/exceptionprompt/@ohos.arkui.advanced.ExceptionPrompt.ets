/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
    AccessibilityRoleType, Builder, Button, ButtonType, Column, Component, Dimension, Direction, Flex, FlexAlign,
    ItemAlign, Image, Margin, Padding, ResourceStr, Resource, Row, SymbolGlyph, SymbolEffectStrategy, SymbolEffect,
    Text, TextOverflow, TextAlign, TransitionEffect, Visibility, $r, Position, ButtonOptions, ICurve, ClickEvent,
    SymbolGlyphModifier
  } from '@ohos.arkui.component'
  import { State, Observed, PropRef } from '@ohos.arkui.stateManagement'
  import curves from '@ohos.curves';
  import common from '@ohos.app.ability.common';
  import EnvironmentCallback from '@ohos.app.ability.EnvironmentCallback';
  import { BusinessError } from '@ohos.base';
  import hilog from '@ohos.hilog';
  import i18n from '@ohos.i18n';
  
  import { UIContext } from '@ohos.arkui.UIContext';
  import { Configuration } from '@ohos.app.ability.Configuration';
  import AbilityConstant from '@ohos.app.ability.AbilityConstant';
  import ApplicationContext from 'application.ApplicationContext';
  
  const START_TIME: int = 250;
  const END_TIME: int = 200;
  const BORDER_RADIUS: number = 12;
  const ZINDEX_NUM: int = 9;
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
  
  class EnvironmentCallbackEntry implements EnvironmentCallback {
    private index: ExceptionPrompt;
  
    constructor(index: ExceptionPrompt) {
      this.index = index;
    }
  
    onConfigurationUpdated(config: Configuration) {
      this.index.fontSizeScale = Math.min(this.index.updateFontScale(), MAX_SYMBOL_FONT_SCALE);
      this.index.fontSizeScale = Math.max(this.index.fontSizeScale as number, MIN_SYMBOL_FONT_SCALE);
    }
  
    onMemoryLevel(level: AbilityConstant.MemoryLevel) {
    }
  }
  
  @Component
  export struct ExceptionPrompt {
    @Observed
    @PropRef options: PromptOptions = {marginType: MarginType.DEFAULT_MARGIN, marginTop: 0} as PromptOptions;
    @State fontSizeScale: number | undefined = undefined;
    touchBackgroundColor: Resource = $r('sys.color.ohos_id_color_sub_background_transparent');
    maxAppFontScale: number = 1;
    systemFontScale?: number = 1;
    isFollowingSystemFontScale: boolean = false;
    onTipClick?: () => void = undefined;
    onActionTextClick?: () => void = undefined;
    private callbackId: number = 0;
    private envCallback: EnvironmentCallbackEntry = new EnvironmentCallbackEntry(this)
    applicationContext: ApplicationContext = new ApplicationContext()
  
    @Builder
    TextBuilder() {
      Flex({
        justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center
      }) {
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
              Image(this.options?.icon as ResourceStr)
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
            .margin(
              i18n.isRTL(i18n.System.getSystemLanguage()) ?
                { right: $r('sys.float.ohos_id_dialog_margin_end') } as Margin :
                { left: $r('sys.float.ohos_id_dialog_margin_end') } as Margin
            )
            .flexShrink(1)
            .direction(i18n.isRTL(i18n.System.getSystemLanguage()) ? Direction.Rtl : Direction.Ltr)
        }
        .padding({ right: $r('sys.float.ohos_id_default_padding_end') } as Padding)
        .accessibilityDescription(this.onTipClick ? '' : ' ')
        .width('100%')
        .onClick((event?: ClickEvent) => {
          this.onTipClick?.();
        })
  
        if (this.options.actionText) {
          Button({ stateEffect: false, type: ButtonType.Normal } as ButtonOptions) {
            Row() {
              Text(this.options.actionText)
                .fontSize($r('sys.float.ohos_id_text_size_body2'))
                .minFontScale(1)
                .maxFontScale(Math.min(this.updateFontScale(), 2))
                .fontColor($r('sys.color.ohos_id_color_text_secondary'))
                .maxLines(2)
                .padding(0)
                .margin(
                  i18n.isRTL(i18n.System.getSystemLanguage()) ?
                    { left: $r('sys.float.ohos_id_text_paragraph_margin_s') } as Margin :
                    { right: $r('sys.float.ohos_id_text_paragraph_margin_s') } as Margin)
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
          } as Padding)
          .accessibilityDescription(this.onActionTextClick ? '' : ' ')
          .accessibilityRole(this.onActionTextClick ? AccessibilityRoleType.BUTTON : AccessibilityRoleType.ROLE_NONE)
          .onClick((event?: ClickEvent) => {
            this.onActionTextClick?.();
          })
        }
      }
      .padding({
        left: $r('sys.float.ohos_id_notification_margin_start'),
        right: $r('sys.float.ohos_id_text_paragraph_margin_s'),
        top: $r('sys.float.ohos_id_default_padding_start'),
        bottom: $r('sys.float.ohos_id_default_padding_end')
      } as Padding)
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
        } as Padding : {
          left: $r('sys.float.ohos_id_max_padding_start'),
          right: $r('sys.float.ohos_id_max_padding_end')
        } as Padding)
        .transition(
          TransitionEffect.OPACITY.animation({
            curve: (curves.cubicBezierCurve(0.33, 0, 0.67, 1)) as ICurve,
            duration: this.options.isShown ? START_TIME : END_TIME
          }), (transitionIn: boolean) => {
        }
        )
        .visibility(this.options.isShown ? Visibility.Visible : Visibility.None)
      }
      .width('100%')
      .position({ y: this.options.marginTop } as Position)
      .zIndex(ZINDEX_NUM)
    }
  
    aboutToAppear() {
      try {
        let context: UIContext = this.getUIContext();
        if (context.getHostContext() !== undefined) {
          this.isFollowingSystemFontScale = context.isFollowingSystemFontScale();
          this.maxAppFontScale = context.getMaxFontScale();
          this.fontSizeScale = Math.min(this.updateFontScale() as number, MAX_SYMBOL_FONT_SCALE as number);
          this.fontSizeScale = Math.max(this.fontSizeScale as number, MIN_SYMBOL_FONT_SCALE as number);
          let hostContext: common.UIAbilityContext = context.getHostContext() as common.UIAbilityContext
  
          this.applicationContext = hostContext.getApplicationContext();
          try {
            this.callbackId = this.applicationContext.onEnvironment(this.envCallback);
          } catch (paramError) {
            hilog.error(0x3900, 'Ace',
              `ExceptionPrompt Faild to get environment param error`);
          }
  
        }
      } catch (paramError) {
        let code = (paramError as BusinessError).code;
        let message = (paramError as BusinessError).message;
        hilog.error(0x3900, 'Ace',
          `EditableTitleBar Faild to get environment param error: ${code}, ${message}`);
      }
    }
  
    aboutToDisappear(): void {
      if (this.callbackId) {
        let context: UIContext = this.getUIContext();
        if (context.getHostContext() !== undefined) {
          this.applicationContext.offEnvironment(this.callbackId as Int, (err: BusinessError<void> | null): void => {
            hilog.info(0x0000, 'testTag', `applicationContext off environment err: code ${err?.code}`);
          })
        }
      }
    }
  
    updateFontScale(): number {
      let uiContent: UIContext = this.getUIContext();
      if (uiContent.getHostContext() != undefined) {
        this.systemFontScale = (uiContent.getHostContext() as common.UIAbilityContext)?.config?.fontSizeScale ?? 1;
      }
      if (!this.isFollowingSystemFontScale) {
        return 1;
      }
      return Math.min(this.systemFontScale as number, this.maxAppFontScale as number);
    }
  }
  
  class Util {
    private static RESOURCE_TYPE_SYMBOL: number = 40000;
  
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
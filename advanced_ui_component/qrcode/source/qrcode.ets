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

import { LengthMetrics, ColorMetrics, LengthUnit } from '@ohos.arkui.node';

export enum QrcodeState {
  NORMAL,
  EXPIRED,
  LOADING
}

class ConfigDataConstants {
  public static readonly TIPS = $r('sys.string.qrcode_expiration_prompt');
  public static readonly ANIMATION_CURVE = '0.33,0,0.67,1';
  public static readonly BOTTOM_CONTAINER_LENGTH = 125;
  public static readonly QRCODE_LENGTH = 101;
  public static readonly REFRESH_ICON_SIZE = 28;
  public static readonly LOAD_ICON_SIZE = 34;
  public static readonly BOTTOM_ROUNDED_CORNERS = 12;
  public static readonly TEXT_SIZE = '11fp';
  public static readonly SPACE_SIZE = '6vp';
  public static readonly WORD_WEIGHT = 500;
  public static readonly DEFAULT_OPACITY = 0.4;
  public static readonly DEFAULT_TIMES = 200;
}

interface CommonQrcodeOptions {
  /**
   * edgeLength
   */
  edgeLength?: LengthMetrics;

  /**
   * Qrcode color
   */
  color?: ColorMetrics;

  /**
   * Qrcode backgroundColor
   */
  backgroundColor?: ColorMetrics;

  /**
   * text Color
   */
  textColor?: ColorMetrics;

  /**
   * invalid prompt text content
   */
  textContent?: ResourceStr;

  /**
   * border Radius
   */
  borderRadius?: LengthMetrics;

  /**
   * opacity
   */
  opacity?: number | Resource;

  /**
   * animation Curve
   */
  animationCurve?: Curve | string | ICurve;

  /**
   * animation duration
   */
  animationDuration?: number;

  /**
   * qrcode side length
   */
  qrcodeSideLength?: LengthMetrics;

  /**
   * expired image length
   */
  expiredImageLength?: LengthMetrics;

  /**
   * text size
   */
  textSize?: ResourceStr;

  /**
   * text weight
   */
  textWeight?: number | FontWeight | string;

  /**
   * space
   */
  space?: ResourceStr;

  /**
   * loading image length
   */
  loadingImageLength?: LengthMetrics;
}

@ObservedV2
export class QrcodeOptions {
  @Trace public edgeLength?: LengthMetrics;
  @Trace public color?: ColorMetrics;
  @Trace public backgroundColor?: ColorMetrics;
  @Trace public textColor?: ColorMetrics;
  @Trace public textContent?: ResourceStr;
  @Trace public borderRadius?: LengthMetrics;
  @Trace public opacity?: number | Resource;
  @Trace public animationCurve?: Curve | string | ICurve;
  @Trace public animationDuration?: number;
  @Trace public qrcodeSideLength?: LengthMetrics;
  @Trace public expiredImageLength?: LengthMetrics;
  @Trace public textSize?: ResourceStr;
  @Trace public textWeight?: number | FontWeight | string;
  @Trace public space?: ResourceStr;
  @Trace public loadingImageLength?: LengthMetrics;

  constructor(options: CommonQrcodeOptions) {
    this.edgeLength = options.edgeLength ?? LengthMetrics.vp(ConfigDataConstants.BOTTOM_CONTAINER_LENGTH)
    this.color = options.color ?? ColorMetrics.resourceColor(Color.Black)
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.White)
    this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White)
    this.textContent = options.textContent ?? ConfigDataConstants.TIPS

    this.borderRadius = options.borderRadius ?? LengthMetrics.vp(ConfigDataConstants.BOTTOM_ROUNDED_CORNERS)
    this.opacity = options.opacity ?? ConfigDataConstants.DEFAULT_OPACITY
    this.animationCurve = options.animationCurve ?? ConfigDataConstants.ANIMATION_CURVE
    this.animationDuration = options.animationDuration ?? ConfigDataConstants.DEFAULT_TIMES
    this.qrcodeSideLength = options.qrcodeSideLength ?? LengthMetrics.vp(ConfigDataConstants.QRCODE_LENGTH)
    this.expiredImageLength = options.expiredImageLength ?? LengthMetrics.vp(ConfigDataConstants.REFRESH_ICON_SIZE)
    this.textSize = options.textSize ?? ConfigDataConstants.TEXT_SIZE
    this.textWeight = options.textWeight ?? FontWeight.Medium
    this.space = options.space ?? ConfigDataConstants.SPACE_SIZE
    this.loadingImageLength = options.loadingImageLength ?? LengthMetrics.vp(ConfigDataConstants.LOAD_ICON_SIZE)
  }
}

function cover(params: LengthMetrics):string {
  switch (params.unit) {
    case LengthUnit.VP:
      return `${params.value}vp`
    case LengthUnit.PX:
      return `${params.value}px`
    case LengthUnit.FP:
      return `${params.value}fp`
    case LengthUnit.LPX:
      return `${params.value}lpx`
    case LengthUnit.PERCENT:
      return `${params.value}%`
  }
}

@ComponentV2
export struct Qrcode {
  @Require @Param options: QrcodeOptions;
  @Require @Param value: string;
  @Require @Param state: QrcodeState;

  @Builder symbolGlyphBuilder() {
    SymbolGlyph($r('sys.symbol.arrow_clockwise')).fontSize(this.options.expiredImageLength?cover(this.options.expiredImageLength):undefined)
      .fontColor([this.options.textColor?.color])
      .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)
  }

  @Builder textBuilder() {
    Text(this.options.textContent).margin({ top: this.options.space }).fontColor(this.options.textColor?.color)
      .fontSize(this.options.textSize).fontWeight(this.options.textWeight).textAlign(TextAlign.Center)
      .width(this.options.qrcodeSideLength?.value)
      .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)
  }

  @Builder loadinProgressBuilder() {
    LoadingProgress().color(Color.White).height(this.options.loadingImageLength?.value)
      .width(this.options.loadingImageLength?.value)
      .visibility(this.state == QrcodeState.LOADING ? Visibility.Visible : Visibility.None)
      .animation({ duration: this.options.animationDuration, curve: this.options.animationCurve,
        playMode: PlayMode.Normal
      })
  }

  build() {
    Stack() {
      if (this.options !== void 0) {
        Column() {
          QRCode(this.value).color(this.options.color?.color).backgroundColor(Color.Transparent)
            .width(this.options.qrcodeSideLength?.value)
            .height(this.options.qrcodeSideLength?cover(this.options.qrcodeSideLength):undefined)
        }
        .height(this.options.edgeLength?.value).width(this.options.edgeLength?.value)
        .backgroundColor(this.options.backgroundColor?.color).borderRadius(this.options.borderRadius?.value)
        .opacity(this.state != QrcodeState.NORMAL ? this.options.opacity : 1)
        .animation({ duration: this.options.animationDuration, curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
        .justifyContent(FlexAlign.Center)

        Column() {
          this.symbolGlyphBuilder()
          if (this.state == QrcodeState.LOADING) {
            this.loadinProgressBuilder()
          }
          this.textBuilder()
        }
        .visibility(this.state == QrcodeState.NORMAL ? Visibility.None : Visibility.Visible)
        .animation({ duration: this.options.animationDuration, curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
      }
    }
  }
}

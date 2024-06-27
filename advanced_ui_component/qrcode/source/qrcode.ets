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
  public static readonly ONE_HUNDRED_TWENTY_FIVE_VP = 125;
  public static readonly ONE_HUNDRED_ONE_VP = 101;
  public static readonly TWENTY_EIGHT_VP = 28;
  public static readonly THIRTY_FOUR_VP = 34;
  public static readonly TWELVE = 12;
  public static readonly ELEVEN_FP = '11fp';
  public static readonly SIX_VP = '6vp';
  public static readonly FIVE_HUNDRED = 500;
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
  @Trace  public edgeLength?: LengthMetrics;
  @Trace  public color?: ColorMetrics;
  @Trace  public backgroundColor?: ColorMetrics;
  @Trace  public textColor?: ColorMetrics;
  @Trace  public textContent?: ResourceStr;
  @Trace  public borderRadius?: LengthMetrics;
  @Trace  public opacity?: number | Resource;
  @Trace  public animationCurve?: Curve | string | ICurve;
  @Trace  public animationDuration?: number;
  @Trace  public qrcodeSideLength?: LengthMetrics;
  @Trace  public expiredImageLength?: LengthMetrics;
  @Trace  public textSize?: ResourceStr;
  @Trace  public textWeight?: number | FontWeight | string;
  @Trace  public space?: ResourceStr;
  @Trace  public loadingImageLength?: LengthMetrics;

  constructor(options: CommonQrcodeOptions) {
    this.edgeLength = options.edgeLength ??
      new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_TWENTY_FIVE_VP, LengthUnit.VP)
    this.color = options.color ?? ColorMetrics.resourceColor(Color.Black)
    this.backgroundColor = options.backgroundColor ?? ColorMetrics.resourceColor(Color.White)
    this.textColor = options.textColor ?? ColorMetrics.resourceColor(Color.White)
    this.textContent = options.textContent ?? ConfigDataConstants.TIPS

    this.borderRadius = options.borderRadius ?? new LengthMetrics(ConfigDataConstants.TWELVE, LengthUnit.VP)
    this.opacity = options.opacity ?? ConfigDataConstants.DEFAULT_OPACITY
    this.animationCurve = options.animationCurve ?? ConfigDataConstants.ANIMATION_CURVE
    this.animationDuration = options.animationDuration ?? ConfigDataConstants.DEFAULT_TIMES
    this.qrcodeSideLength = options.qrcodeSideLength ??
      new LengthMetrics(ConfigDataConstants.ONE_HUNDRED_ONE_VP, LengthUnit.VP)
    this.expiredImageLength = options.expiredImageLength ??
      new LengthMetrics(ConfigDataConstants.TWENTY_EIGHT_VP, LengthUnit.VP)
    this.textSize = options.textSize ?? ConfigDataConstants.ELEVEN_FP
    this.textWeight = options.textWeight ?? FontWeight.Medium
    this.space = options.space ?? ConfigDataConstants.SIX_VP
    this.loadingImageLength = options.loadingImageLength ??
      new LengthMetrics(ConfigDataConstants.THIRTY_FOUR_VP, LengthUnit.VP)
  }
}

@ComponentV2
export struct Qrcode {
  @Require @Param options: QrcodeOptions;
  @Require @Param value: string;
  @Require @Param state: QrcodeState;

  build() {
    Stack() {
      if (this.options !== void 0) {
        Column() {
          QRCode(this.value)
            .color(this.options.color?.color)
            .backgroundColor(Color.Transparent)
            .width(this.options.qrcodeSideLength?.value)
            .height(this.options.qrcodeSideLength?.value)
        }
        .height(this.options.edgeLength?.value)
        .width(this.options.edgeLength?.value)
        .backgroundColor(this.options.backgroundColor?.color)
        .borderRadius(this.options.borderRadius?.value)
        .opacity(this.state != QrcodeState.NORMAL ? this.options.opacity : 1)
        .animation({
          duration: this.options.animationDuration,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
        .justifyContent(FlexAlign.Center)


        Column() {
          SymbolGlyph($r('sys.symbol.arrow_clockwise'))
            .fontSize(this.options.expiredImageLength?.value)
            .fontColor([this.options.textColor?.color])
            .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)

          if (this.state == QrcodeState.LOADING) {
            LoadingProgress()
              .color(Color.White)
              .height(this.options.loadingImageLength?.value)
              .width(this.options.loadingImageLength?.value)
              .visibility(this.state == QrcodeState.LOADING ? Visibility.Visible : Visibility.None)
              .animation({
                duration: this.options.animationDuration,
                curve: this.options.animationCurve,
                playMode: PlayMode.Normal
              })
          }

          Text(this.options.textContent)
            .margin({ top: this.options.space })
            .fontColor(this.options.textColor?.color)
            .fontSize(this.options.textSize)
            .fontWeight(this.options.textWeight)
            .textAlign(TextAlign.Center)
            .width(this.options.qrcodeSideLength?.value)
            .visibility(this.state == QrcodeState.EXPIRED ? Visibility.Visible : Visibility.None)

        }
        .visibility(this.state == QrcodeState.NORMAL ? Visibility.None : Visibility.Visible)
        .animation({
          duration: this.options.animationDuration,
          curve: this.options.animationCurve,
          playMode: PlayMode.Normal
        })
      }
    }
  }
}
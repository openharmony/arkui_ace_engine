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

import { Drawer } from 'common/src/main/ets/components/Drawer';
import { RadioBlock, SliderBlock, ColorBlock, useEnabled } from 'common';

interface fontWeightItem {
  label: string;
  value: FontWeight | number | string;
}
const fontWeightDataSource: fontWeightItem[] = [
  { label: '100', value: 100 },
  { label: '200', value: 200 },
  { label: '300', value: 300 },
  { label: '400', value: 400 },
  { label: '500', value: 500 },
  { label: '600', value: 600 },
  { label: '700', value: 700 },
  { label: '800', value: 800 },
  { label: '900', value: 900 },
  { label: 'Lighter', value: FontWeight.Lighter },
  { label: 'Normal', value: FontWeight.Normal },
  { label: 'Regular', value: FontWeight.Regular },
  { label: 'Medium', value: FontWeight.Medium },
  { label: 'Bold', value: FontWeight.Bold },
  { label: 'Bolder', value: FontWeight.Bolder },
];

@Component
export struct SpanBootcamp {
  @Require @Prop title: ResourceStr;
  @State showParameters: boolean = false;
  @State enableDecorationType: boolean = false;
  @State decorationType:TextDecorationType = TextDecorationType.None;
  @State enableDecorationColor: boolean = false;
  @State decorationColor: ResourceColor = Color.Black;
  @State enableDecorationStyle: boolean = false;
  @State decorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID;
  @State enableLetterSpacing: boolean = false;
  @State letterSpacing: number | undefined = undefined;
  @State enableTextCase: boolean = false;
  @State textCase: TextCase = TextCase.Normal
  @State enableFontColor: boolean = false;
  @State fontColor: ResourceColor | undefined= undefined;
  @State enableFontSize: boolean = false;
  @State fontSize: number = 16;
  @State enableFontStyle: boolean = false;
  @State fontStyle: FontStyle = FontStyle.Normal;
  @State enableFontWeight: boolean = false;
  @State fontWeight: FontWeight | number | string = 400|FontWeight.Normal;
  @State enableLineHeight: boolean = false;
  @State lineHeight: number | undefined = undefined;
  @State enableTextFontSize: boolean = false;
  @State textFontSize: number = 16;
  @State enableTextFontWeight: boolean = false;
  @State textFontWeight: FontWeight | number | string = 400|FontWeight.Normal;
  @State enableTextFontStyle: boolean = false;
  @State textFontStyle: FontStyle = FontStyle.Normal;
  @State enableTextShadowRadius: boolean = false;
  @State textShadowRadius: number | undefined = undefined;
  @State enableTextShadowType: boolean = false;
  @State textShadowType: ShadowType = ShadowType.COLOR
  @State enableTextShadowColor: boolean = false;
  @State textShadowColor: Color = Color.Black;
  @State enableTextShadowOffsetX: boolean = false;
  @State textShadowOffsetX: number = 0
  @State enableTextShadowOffsetY: boolean = false;
  @State textShadowOffsetY: number = 0
  @State enableTextShadowFill: boolean = false;
  @State textShadowFill: boolean = false;


  build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor('#f1f3f5')
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Row() {
      Text(){
        Span('This is a Span component.' +
          ' The span component is used to display a piece of textual information.' +
          ' Support universal attributes and universal attributes.')
          .decoration({
            type: useEnabled(this.enableDecorationType, this.decorationType),
            color: useEnabled(this.enableDecorationColor, this.decorationColor),
            style: useEnabled(this.enableDecorationStyle, this.decorationStyle)
          })
          .letterSpacing(useEnabled(this.enableLetterSpacing,this.letterSpacing))
          .textCase(useEnabled(this.enableTextCase,this.textCase))
          .fontColor(useEnabled(this.enableFontColor,this.fontColor))
          .fontSize(useEnabled(this.enableFontSize,this.fontSize))
          .fontStyle(useEnabled(this.enableFontStyle,this.fontStyle))
          .fontWeight(useEnabled(this.enableFontWeight,this.fontWeight))
          .lineHeight(useEnabled(this.enableLineHeight, this.lineHeight))
          .font({
            size: useEnabled(this.enableTextFontSize, this.textFontSize),
            weight: useEnabled(this.enableTextFontWeight, this.textFontWeight),
            style: useEnabled(this.enableTextFontStyle, this.textFontStyle)
          })
          .textShadow({
            radius: useEnabled(this.enableTextShadowRadius, this.textShadowRadius),
            type: useEnabled(this.enableTextShadowType, this.textShadowType),
            color: useEnabled(this.enableTextShadowColor, this.textShadowColor),
            offsetX: useEnabled(this.enableTextShadowOffsetX, this.textShadowOffsetX),
            offsetY: useEnabled(this.enableTextShadowOffsetY, this.textShadowOffsetY),
            fill: useEnabled(this.enableTextShadowFill, this.textShadowFill)
          })
      }

    }.justifyContent(FlexAlign.Start)
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {

        RadioBlock({
          title:'decoration.type',
          isEnabled: this.enableDecorationType,
          value: this.decorationType,
          dataSource: [
            {label: 'None', value: TextDecorationType.None },
            {label: 'Underline', value: TextDecorationType.Underline },
            {label: 'Overline', value: TextDecorationType.Overline },
            {label: 'LineThrough', value: TextDecorationType.LineThrough },
          ]
        })

        ColorBlock({
          title: 'decoration.color',
          isEnabled: this.enableDecorationColor,
          color: this.decorationColor
        })

        RadioBlock({
          title:'decoration.style',
          isEnabled: this.enableDecorationStyle,
          value: this.decorationStyle,
          dataSource: [
            {label: 'SOLID', value: TextDecorationStyle.SOLID },
            {label: 'DOUBLE', value: TextDecorationStyle.DOUBLE },
            {label: 'DOTTED', value: TextDecorationStyle.DOTTED },
            {label: 'DASHED', value: TextDecorationStyle.DASHED },
            {label: 'WAVY', value: TextDecorationStyle.WAVY },
          ]
        })

        SliderBlock({
          title: 'letterSpacing',
          isEnabled: this.enableLetterSpacing,
          value: this.letterSpacing,
          min: 0,
          max: 20
        })

        RadioBlock({
          title:'textCase',
          isEnabled: this.enableTextCase,
          value: this.textCase,
          dataSource: [
            {label: 'Normal', value: TextCase.Normal },
            {label: 'LowerCase', value: TextCase.LowerCase },
            {label: 'UpperCase', value: TextCase.UpperCase },
          ]
        })

        ColorBlock({
          title: 'fontColor',
          isEnabled: this.enableFontColor,
          color: this.fontColor
        })

        SliderBlock({
          title: 'fontSize',
          isEnabled: this.enableFontSize,
          value: this.fontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'fontStyle',
          isEnabled: this.enableFontStyle,
          value: this.fontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        RadioBlock({
          title: 'fontWeight',
          isEnabled: this.enableFontWeight,
          value: this.fontWeight,
          dataSource: fontWeightDataSource
        })

        SliderBlock({
          title: 'lineHeight',
          isEnabled: this.enableLineHeight,
          value: this.lineHeight,
          min: 0,
          max: 10
        })

        SliderBlock({
          title: 'font.size',
          isEnabled: this.enableTextFontSize,
          value: this.textFontSize,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'font.weight',
          isEnabled: this.enableTextFontWeight,
          value: this.textFontWeight,
          dataSource:fontWeightDataSource
        })

        RadioBlock({
          title: 'font.style',
          isEnabled: this.enableTextFontStyle,
          value: this.textFontStyle,
          dataSource: [
            { label: 'Normal', value: FontStyle.Normal },
            { label: 'Italic', value: FontStyle.Italic },
          ]
        })

        SliderBlock({
          title: 'textShadow.radius',
          isEnabled: this.enableTextShadowRadius,
          value: this.textShadowRadius,
          min: 0,
          max: 360
        })

        RadioBlock({
          title: 'textShadow.type',
          isEnabled: this.enableTextShadowType,
          value: this.textShadowType,
          dataSource: [
            { label: 'COLOR', value: ShadowType.COLOR },
            { label: 'BLUR', value: ShadowType.BLUR },
          ]
        })

        ColorBlock({
          title: 'textShadow.color',
          isEnabled: this.enableTextShadowColor,
          color: this.textShadowColor
        })

        SliderBlock({
          title: 'textShadow.offsetX',
          isEnabled: this.enableTextShadowOffsetX,
          value: this.textShadowOffsetX,
          min: 0,
          max: 200
        })

        SliderBlock({
          title: 'textShadow.offsetY',
          isEnabled: this.enableTextShadowOffsetY,
          value: this.textShadowOffsetY,
          min: 0,
          max: 200
        })

        RadioBlock({
          title: 'textShadow.fill',
          isEnabled: this.enableTextShadowFill,
          value: this.textShadowFill,
          dataSource: [
            { label: 'true', value: true },
            { label: 'false', value: false },
          ]
        })

      }
    }
  }
}

@Preview
@Component
struct SpanBootcampPreviewer {
  build() {
    SpanBootcamp({
      title: 'Span'
    })
  }
}


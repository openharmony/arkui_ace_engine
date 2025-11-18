/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the 'License');
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an 'AS IS' BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import drawing from "@ohos.graphics.drawing"
import common2D from "@ohos.graphics.common2D"

class Info {
  colorFilter: drawing.ColorFilter | DrawingColorFilter | undefined | null;
  information: string;

  constructor(colorFilter: drawing.ColorFilter | DrawingColorFilter | undefined | null, information: string) {
    this.colorFilter = colorFilter;
    this.information = information;
  }
}


@Entry
@Component
struct ImageExample1 {
  @State text: number = 0
  @State colorBlue: common2D.Color = { alpha: 255, red: 0, green: 0, blue: 255 };
  @State colorRed: common2D.Color = { alpha: 255, red: 255, green: 0, blue: 0 };
  @State colorBlueAlphaFloat: common2D.Color = { alpha: 10.5, red: 0, green: 0, blue: 255 };
  @State colorBlueAlphaFloat2: common2D.Color = { alpha: 2.5, red: 0, green: 0, blue: 255 };
  @State colorRedAlphaFloat: common2D.Color = { alpha: 10.5, red: 255, green: 0, blue: 0 };
  @State colorBlueAlphaLT0: common2D.Color = { alpha: -1, red: 0, green: 0, blue: 255 };
  @State colorRedAlphaLT0: common2D.Color = { alpha: -1, red: 255, green: 0, blue: 0 };
  @State withOtherType: DrawingColorFilter = drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC)
  @State drawingColorFilters: Info[] = [
    new Info(-111, "-111"),
    new Info(null, "null"),
    new Info(undefined, "undefined"),
    new Info(drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC), "SVG由蓝灰、黄绿和橙色同时转为红色"),
    new Info(drawing.ColorFilter.createBlendModeColorFilter(this.colorRedAlphaLT0, drawing.BlendMode.SRC), "SVG的蓝灰、黄绿和橙色被清除"),
    new Info(drawing.ColorFilter.createBlendModeColorFilter(this.colorRedAlphaFloat, drawing.BlendMode.SRC), "SVG由蓝灰、黄绿和橙色同时转成透明红色"),
    new Info(drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.CLEAR), "SVG的蓝灰、黄绿和橙色被清除"),
    new Info(drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.DST), "SVG维持原图的蓝灰、黄绿和橙色无变化"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlue, drawing.BlendMode.SRC)
    ), "SVG由蓝灰、黄绿和橙色同时转成红色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRedAlphaLT0, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC)
    ), "SVG的蓝灰、黄绿和橙色被清除"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRedAlphaFloat, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC)
    ), "SVG由蓝灰、黄绿和橙色同时转成透明红色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.CLEAR),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlue, drawing.BlendMode.SRC)
    ), "SVG的蓝灰、黄绿和橙色被清除"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.DST),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlue, drawing.BlendMode.SRC)
    ), "SVG由蓝灰、黄绿和橙色同时转成蓝色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlueAlphaLT0, drawing.BlendMode.SRC)
    ), "SVG由蓝灰、黄绿和橙色同时转成红色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlueAlphaFloat2, drawing.BlendMode.SRC)
    ), "SVG由蓝灰、黄绿和橙色同时转成红色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlue, drawing.BlendMode.DST)
    ), "SVG由蓝灰、黄绿和橙色同时转成红色"),
    new Info(drawing.ColorFilter.createComposeColorFilter(
      drawing.ColorFilter.createBlendModeColorFilter(this.colorRed, drawing.BlendMode.SRC),
      drawing.ColorFilter.createBlendModeColorFilter(this.colorBlue, drawing.BlendMode.CLEAR)
    ), "SVG由蓝灰、黄绿和橙色同时转成红色"),
    new Info(drawing.ColorFilter.createLinearToSRGBGamma(), "SVG第一根线蓝灰色变成浅蓝灰色、第二根线的黄绿色变为浅黄绿色和第三根线的橙色转成浅橙色"),
    new Info(drawing.ColorFilter.createSRGBGammaToLinear(), "SVG第一根线蓝灰色变成黑色、第二根线的黄绿色变为黑色和第三根线的橙色转成红色（偏橙）"),
    new Info(drawing.ColorFilter.createLumaColorFilter(), "SVG由蓝灰、黄绿和橙色同时转成灰色，其中第一根和第二个线的灰度一致，第三根线的灰度略高于第一和第二根线"),
    new Info(this.withOtherType, "DrawingColorFilter (the other name of drawing.ColorFilter)"),
  ]
  @State obscured1: ObscuredReasons[] = []
  @State obscured2: ObscuredReasons[] = [ObscuredReasons.PLACEHOLDER]

  build() {
    Scroll(new Scroller()) {
      Flex({ justifyContent: FlexAlign.Center, direction: FlexDirection.Row, wrap: FlexWrap.Wrap }) {

        Text('onFinish触发次数：' + this.text)
        Row() {
          Button('隐私遮罩').onClick((event: ClickEvent) => {
            this.obscured1 = [ObscuredReasons.PLACEHOLDER]
          })
          Button('隐私不遮罩').onClick((event: ClickEvent) => {
            this.obscured1 = []
          })
        }
        ForEach(this.drawingColorFilters, (item: Info, index: number) => {

          Flex({ justifyContent: FlexAlign.Center, direction: FlexDirection.Column }) {

            Text(item.information)
              .alignSelf(ItemAlign.Center)
              .align(Alignment.Center)
              .fontSize(12)
            Image($r("app.media.test_self"))
              .width(110)
              .height(110)
              .margin(15)
              .alignSelf(ItemAlign.Center)
              .align(Alignment.Center)
              .colorFilter(item.colorFilter)
              .fillColor(Color.Pink)
              .onFinish(() => {
                this.text += 1
              })
              .margin(5)
              .obscured(this.obscured1)

          }.width("50%")
        })
      }.width("100%")
    }
    .width("100%")
    .scrollable(ScrollDirection.Vertical)
    .scrollBar(BarState.On)
    .edgeEffect(EdgeEffect.Spring)
  }
}
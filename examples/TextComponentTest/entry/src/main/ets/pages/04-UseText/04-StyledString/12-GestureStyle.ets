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

import { drawing } from '@kit.ArkGraphics2D';

let gUIContext: UIContext;

class MyCustomSpan extends CustomSpan {
  constructor(word: string, width: number, height: number, fontSize: number) {
    super();
    this.word = word;
    this.width = width;
    this.height = height;
    this.fontSize = fontSize;
  }

  onMeasure(measureInfo: CustomSpanMeasureInfo): CustomSpanMetrics {
    return { width: this.width, height: this.height };
  }

  onDraw(context: DrawContext, options: CustomSpanDrawInfo) {
    let canvas = context.canvas;

    const brush = new drawing.Brush();
    brush.setColor({
      alpha: 255,
      red: 0,
      green: 0,
      blue: 0
    });
    const font = new drawing.Font();
    font.setSize(gUIContext.vp2px(this.fontSize));
    const textBlob =
      drawing.TextBlob.makeFromString(this.word.substring(0, 5), font, drawing.TextEncoding.TEXT_ENCODING_UTF8);
    canvas.attachBrush(brush);

    this.onDrawRectByRadius(context, options.x, options.x + gUIContext.vp2px(this.width), options.lineTop,
      options.lineBottom, 20);
    brush.setColor({
      alpha: 255,
      red: 255,
      green: 255,
      blue: 255
    });
    canvas.attachBrush(brush);
    canvas.drawTextBlob(textBlob, options.x, options.baseline);
    brush.setColor({
      alpha: 255,
      red: 255,
      green: 228,
      blue: 196
    });
    canvas.attachBrush(brush);
    const textBlob1 =
      drawing.TextBlob.makeFromString(this.word.substring(5), font, drawing.TextEncoding.TEXT_ENCODING_UTF8);
    canvas.drawTextBlob(textBlob1, options.x + gUIContext.vp2px(100), options.baseline);

    canvas.detachBrush();
  }

  onDrawRectByRadius(context: DrawContext, left: number, right: number, top: number, bottom: number, radius: number) {
    let canvas = context.canvas;
    let path = new drawing.Path();

    // 画带radius的rect
    path.moveTo(left + radius, top);
    path.lineTo(right - radius, top);
    path.arcTo(right - 2 * radius, top, right, top + 2 * radius, 270, 90);
    path.lineTo(right, bottom - radius);
    path.arcTo(right - 2 * radius, bottom - 2 * radius, right, bottom, 0, 90);

    path.lineTo(left + 2 * radius, bottom);
    path.arcTo(left, bottom - 2 * radius, left + 2 * radius, bottom, 90, 90);
    path.lineTo(left, top + 2 * radius);
    path.arcTo(left, top, left + 2 * radius, top + 2 * radius, 180, 90);

    canvas.drawPath(path);
  }

  setWord(word: string) {
    this.word = word;
  }

  private width: number = 160;
  private word: string = 'drawing';
  private height: number = 10;
  private fontSize: number = 16;
}

@Entry
@Component
struct GestureStyle {
  customSpan3: MyCustomSpan = new MyCustomSpan('99VIP88%off', 200, 40, 30);
  customSpanStyledString: MutableStyledString = new MutableStyledString(this.customSpan3);
  textController: TextController = new TextController();
  isPageShow: boolean = true;
  @State backgroundColor1: ResourceColor | undefined = undefined;
  gestureStyleAttr: GestureStyle = new GestureStyle({
    onClick: () => {
      this.backgroundColor1 = Color.Green;
    },
    onLongPress: () => {
      this.backgroundColor1 = Color.Grey;
    }
  });

  aboutToAppear() {
    gUIContext = this.getUIContext();
  }

  async onPageShow() {
    if (!this.isPageShow) {
      return;
    }
    this.isPageShow = false;
    this.customSpanStyledString.setStyle({
      start: 0,
      length: 1,
      styledKey: StyledStringKey.GESTURE,
      styledValue: this.gestureStyleAttr
    })
    this.textController.setStyledString(this.customSpanStyledString);
  }

  build() {
    Row() {
      Column() {
        Button('响应属性字符串事件改变背景色').backgroundColor(this.backgroundColor1).width('80%').margin(10)
        Text(undefined, { controller: this.textController })
          .copyOption(CopyOptions.InApp)
          .fontSize(30)
      }
      .width('100%')
    }
    .height('100%')
  }
}
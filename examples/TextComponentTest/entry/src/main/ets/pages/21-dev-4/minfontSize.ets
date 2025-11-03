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

// import { LengthUnit } from '@kit.ArkUI';
import { LengthMetrics, LengthUnit } from '@kit.ArkUI'
// xxx.ets
@Entry
@Component
struct TextExample6 {

  fontStyleAttr1: TextStyle = new TextStyle({ fontColor:Color.Red,fontSize:LengthMetrics.fp(40)});
  fontStyleAttr2: TextStyle = new TextStyle({ fontColor:Color.Blue});
  mutableStyledString1: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 10,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr1
  }]);
  mutableStyledString2: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 10,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr1
  }]);

  mutableStyledString3: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 30,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr1
  }]);
  mutableStyledString4: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 10,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr2
  }]);
  mutableStyledString5: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 10,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr2
  }]);

  mutableStyledString6: MutableStyledString = new MutableStyledString('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.', [{
    start: 0,
    length: 30,
    styledKey: StyledStringKey.FONT,
    styledValue: this.fontStyleAttr2
  }]);

  controller1: TextController = new TextController();
  controller2: TextController = new TextController();
  controller3: TextController = new TextController();
  controller4: TextController = new TextController();
  controller5: TextController = new TextController();
  controller6: TextController = new TextController();
  async onPageShow() {
    this.controller1.setStyledString(this.mutableStyledString1)
    this.controller2.setStyledString(this.mutableStyledString2)
    this.controller3.setStyledString(this.mutableStyledString3)
    this.controller4.setStyledString(this.mutableStyledString4)
    this.controller5.setStyledString(this.mutableStyledString5)
    this.controller6.setStyledString(this.mutableStyledString6)
  }
  // aboutToAppear() {
  //   this.controller1.setStyledString(this.mutableStyledString1)
  //   this.controller2.setStyledString(this.mutableStyledString2)
  //   this.controller3.setStyledString(this.mutableStyledString3)
  //   this.controller4.setStyledString(this.mutableStyledString4)
  //   this.controller5.setStyledString(this.mutableStyledString5)
  //   this.controller6.setStyledString(this.mutableStyledString6)
  // }
  build() {
    Scroll(){
    Column(){
      // 设置文本自适应高度的方式
      // Text('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
      //   .width('80%')
      //   .height(90)
      //   .borderWidth(1)
      //   .fontSize(20)
      //   .maxLines(5)
      //   .margin(5)
      //   .textOverflow({ overflow: TextOverflow.Ellipsis })
      Text('Text组件').fontColor(Color.Green)
      Text('This is the text with the height adaptive policy set.')
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
        .clip(true)
      Text('This is the text with the height adaptive policy set.')
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
        .clip(true)

      Text('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(20)
        .maxFontSize(40)
        .maxLines(5)
        .copyOption(CopyOptions.LocalDevice)
        .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
        .margin({bottom:10})
        .clip(true)



      Text('span组件，Span设置字体大小').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
        Span('This is the text with the height adaptive policy set.')
          .fontSize(40)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
      } .clip(true)

        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      .copyOption(CopyOptions.LocalDevice)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
        Span('This is the text with the height adaptive policy set.')
          .fontSize(40)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
      } .clip(true)
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
      Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        .fontSize(40)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(40)
      } .clip(true)
        .width('80%')
        .height(90)
        .borderWidth(1)
        .minFontSize(20)
        .maxFontSize(40)
        .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)

        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
        .margin({bottom:10})


      Text('多个span组件，部分设置字体大小').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('This is the text with the height adaptive policy set.').fontSize(30)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('This is the text with the height adaptive policy set.').fontSize(30)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        Span('This is the text with the height adaptive policy set.').fontSize(30)
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(20)
      .maxFontSize(40)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})


      Text('span组件，max>min').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(20)
      .maxFontSize(40)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})



      Text('span组件，max=min').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(10)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(10)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(10)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})

      Text('span组件，max<min').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .minFontSize(30)
      .maxFontSize(10)
      .borderWidth(1)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .minFontSize(30)
      .maxFontSize(10)
      .borderWidth(1)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(30)
      .maxFontSize(10)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})


      Text('span组件，max异常值').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(-10)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(-10)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(20)
      .maxFontSize(-10)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})


      Text('span组件，min设为异常值').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(-10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(-10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(-20)
      .maxFontSize(40)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})

      Text('span组件，Text和span都设置字体大小').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
        Span('This is the text with the height adaptive policy set.')
          .fontSize(20)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(30)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
        Span('This is the text with the height adaptive policy set.')
          .fontSize(20)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(30)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
          .fontSize(20)
        SymbolSpan($r('sys.symbol.ohos_trash'))
          .fontSize(20)
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(30)
      .minFontSize(20)
      .maxFontSize(40)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})




      Text('span组件，max>min').fontColor(Color.Green)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .fontSize(20)
      .borderWidth(1)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(10)
      .maxFontSize(30)
      .maxLines(2)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
      Text(){
        SymbolSpan($r('sys.symbol.ohos_trash'))
        Span('This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.This is the text with the height adaptive policy set.')
        SymbolSpan($r('sys.symbol.ohos_trash'))
      }
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(20)
      .maxFontSize(40)
      .maxLines(5)
      .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})



      Text('属性字符串设置字体').fontColor(Color.Green)
      Text(undefined,{controller: this.controller1})
        .width('80%')
        .height(90)
        .borderWidth(1)
        .fontSize(20)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)

      Text(undefined,{controller: this.controller2})
        .width('80%')
        .height(90)
        .borderWidth(1)
        .fontSize(20)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)

      Text(undefined,{controller: this.controller3})
      .width('80%')
      .height(90)
      .borderWidth(1)
      .fontSize(20)
      .minFontSize(20)
      .maxFontSize(40)
      .maxLines(5)
        .copyOption(CopyOptions.LocalDevice)
      .textOverflow({ overflow: TextOverflow.Ellipsis })
      .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
      .margin({bottom:10})
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)

      Text('属性字符串设置不设置字体').fontColor(Color.Green)
      Text(undefined,{controller: this.controller4})
        .width('80%')
        .height(90)
        .borderWidth(1)
        .fontSize(20)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MAX_LINES_FIRST)
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)

      Text(undefined,{controller: this.controller5})
        .width('80%')
        .height(90)
        .borderWidth(1)
        .fontSize(20)
        .minFontSize(10)
        .maxFontSize(30)
        .maxLines(2)
        .copyOption(CopyOptions.LocalDevice)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.MIN_FONT_SIZE_FIRST)
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)

      Text(undefined,{controller: this.controller6})
        .width('80%')
        .height(90)
        .borderWidth(1)
        .fontSize(20)
        .minFontSize(20)
        .maxFontSize(40)
        .maxLines(5)
        .copyOption(CopyOptions.LocalDevice)
        .textOverflow({ overflow: TextOverflow.Ellipsis })
        .heightAdaptivePolicy(TextHeightAdaptivePolicy.LAYOUT_CONSTRAINT_FIRST)
        .margin({bottom:10})
        .clip(true)
        .copyOption(CopyOptions.LocalDevice)




      }



    }.width('100%').padding({ left: 35, right: 35, top: 35 })
  }
}
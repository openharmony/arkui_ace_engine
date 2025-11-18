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

import { hilog } from '@kit.PerformanceAnalysisKit';
import { common, ConfigurationConstant } from '@kit.AbilityKit'
import { ColorMetrics } from '@kit.ArkUI';


@Styles
function commonStyle() {
  .width('49%')
  .border({ width: 1, color: $r('app.color.border_color') })
  .margin(2)
}

@Styles
function commonStyle1() {
  .width('100%')
  .border({ width: 1, color: $r('app.color.border_color') })
  .margin(2)
}

@Entry
@Component
struct WindowParams {
  @Builder
  attachmentBuilder() {
    Row() {
      SymbolGlyph($r('sys.symbol.text_book_closed'))
        .fontSize(45)
        .fontColor(['#027dff'])
        .width(50)
        .height(50)
        .margin(16)
      Column() {
        Text("文本文档.txt").fontWeight(FontWeight.Bold).fontSize(16)
        Text("123.45KB").fontColor('#8a8a8a').fontSize(12)
      }.alignItems(HorizontalAlign.Start)
    }
    .backgroundColor('#f4f4f4')
    .borderRadius("20")
    .width(220)
  }

  context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  ctx: common.ApplicationContext = this.context.getApplicationContext();
  con1: RichEditorController = new RichEditorController()
  con2: RichEditorController = new RichEditorController()
  con3: RichEditorController = new RichEditorController()
  con4: RichEditorController = new RichEditorController()
  con5: RichEditorController = new RichEditorController()
  con6: RichEditorController = new RichEditorController()
  con7: RichEditorController = new RichEditorController()
  con8: RichEditorController = new RichEditorController()
  con9: RichEditorController = new RichEditorController()
  con10: RichEditorController = new RichEditorController()
  con11: RichEditorController = new RichEditorController()
  con12: RichEditorController = new RichEditorController()
  con13: RichEditorController = new RichEditorController()
  con14: RichEditorController = new RichEditorController()
  conss1: RichEditorStyledStringController = new RichEditorStyledStringController();
  paragraphStyledString2: MutableStyledString =
    new MutableStyledString("段落标题\n段落标题\n正文第二段自适应字号MIN_FONT_SIZE_FIRST\n正文第三段自适应字号MIN_FONT_SIZE_FIRST",
      [
        {
          start: 0,
          length: 5,
          styledKey: StyledStringKey.FONT,
          styledValue: new TextStyle({ fontColor: $r('app.color.color_text') })
        },
        {
          start: 0,
          length: 5,
          styledKey: StyledStringKey.DECORATION,
          styledValue: new DecorationStyle({ type: TextDecorationType.Overline, color: $r('app.color.color_text') })
        },
        {
          start: 5,
          length: 5,
          styledKey: StyledStringKey.TEXT_SHADOW,
          styledValue: new TextShadowStyle([{
            radius: 5,
            type: ShadowType.COLOR,
            color: $r('app.color.color_text'),
          }, {
            radius: 5,
            type: ShadowType.COLOR,
            color: $r('app.color.color_1'),
            offsetX: 30,
            offsetY: 30
          }])
        },
        {
          start: 10,
          length: 5,
          styledKey: StyledStringKey.BACKGROUND_COLOR,
          styledValue: new BackgroundColorStyle({
            color: $r('app.color.color_text'),
            radius: 2
          })
        }
      ]);
  resourceFontColor: ResourceColor = $r('app.color.color_text')
  resourceTextStyle: RichEditorTextStyle = { fontColor: this.resourceFontColor }
  resourceTextSpanOption: RichEditorTextSpanOptions = { style: this.resourceTextStyle }
  normalFontColor: ResourceColor = Color.Black
  normalTextStyle: RichEditorTextStyle = {
    fontColor: this.normalFontColor,
    fontSize: "16fp",
    textShadow: [{ radius: 0, color: Color.Transparent }],
    decoration: { type: TextDecorationType.None, color: Color.Black },
    textBackgroundStyle: { color: '#00000000' }
  }
  normalTextSpanOption: RichEditorTextSpanOptions = { style: this.normalTextStyle }
  resourceDecorationColor: ResourceColor = $r('app.color.color_text')
  resourceDecorationStyle: RichEditorTextStyle =
    { decoration: { type: TextDecorationType.Underline, color: this.resourceDecorationColor } }
  normalDecorationStyle: RichEditorTextStyle = { decoration: { type: TextDecorationType.Underline } }
  resourceShadowTextSpanOption: RichEditorTextSpanOptions = {
    style: {
      textShadow: [{ radius: 5, color: $r('app.color.color_text') }, { radius: 5, color: $r('app.color.color_1') }]
    }
  }
  resourceSymbolStyle: RichEditorSymbolSpanStyle = {
    fontColor: [$r('app.color.color_text'), $r('app.color.color_1')],
    renderingStrategy: SymbolRenderingStrategy.MULTIPLE_COLOR
  }
  symbolSpanOptions: RichEditorSymbolSpanOptions = { style: this.resourceSymbolStyle }
  normalSymbolStyle: RichEditorSymbolSpanStyle = {
    fontColor: [Color.Black],
    renderingStrategy: SymbolRenderingStrategy.SINGLE
  }
  allTextStyle: RichEditorTextStyle = {
    fontSize: 30,
    fontColor: $r("app.color.color_text"),
    decoration: {
      type: TextDecorationType.LineThrough,
      color: $r("app.color.color_text")
    },
    textShadow: [
      { radius: 15, color: $r('app.color.color_text') },
      { radius: 1, color: $r('app.color.color_text') }
    ],
    textBackgroundStyle: { color: $r('app.color.color_1') }
  }
  @State placeholderColor: ResourceColor = this.resourceFontColor
  @State caretColor: ResourceColor = this.resourceFontColor
  @State selectedBackgroundColor: ResourceColor = this.resourceFontColor
  @State scrollBarColor: ColorMetrics = ColorMetrics.resourceColor($r('app.color.color_text'))

  onCreate(): void {
    hilog.info(0x0000, 'testTag', '%{public}s', 'Ability onCreate');
    getContext().getApplicationContext().setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_NOT_SET);
  }

  build() {
    Column() {
      Row() {
        Button('深色').onClick(() => {
          this.ctx.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_DARK)
        })
        Button('浅色').onClick(() => {
          this.ctx.setColorMode(ConfigurationConstant.ColorMode.COLOR_MODE_LIGHT)
        })
      }

      List() {
        ListItem() {
          Column() {
            Text("Span属性测试").fontSize(25).fontWeight(FontWeight.Bold).margin(10)
            Column() {
              Text('文本颜色')
              Row() {
                RichEditor({ controller: this.con1 }).commonStyle()
                  .onReady(() => this.con1.addTextSpan('默认文本颜色测试'))
                RichEditor({ controller: this.con2 }).commonStyle()
                  .onReady(() => this.con2.addTextSpan('资源文本颜色测试', this.resourceTextSpanOption))
              }
            }

            Column() {
              Text('下划线颜色')
              Row() {
                RichEditor({ controller: this.con3 }).commonStyle()
                  .onReady(() => this.con3.addTextSpan('默认下划线颜色', { style: this.normalDecorationStyle }))
                RichEditor({ controller: this.con4 }).commonStyle()
                  .onReady(() => this.con4.addTextSpan('资源下划线颜色', { style: this.resourceDecorationStyle }))
              }
            }

            Column() {
              Text('Shadow颜色')
              Row() {
                RichEditor({ controller: this.con5 }).commonStyle()
                  .onReady(() => this.con5.addTextSpan('默认Shadow颜色',
                    { style: { textShadow: [{ radius: 5 }, { radius: 5 }] } }))
                RichEditor({ controller: this.con6 }).commonStyle()
                  .onReady(() => this.con6.addTextSpan('资源Shadow颜色', this.resourceShadowTextSpanOption))
              }
            }

            Column() {
              Text('Symbol颜色')
              Row() {
                RichEditor({ controller: this.con7 }).commonStyle()
                  .onReady(() => {
                    this.con7.addSymbolSpan($r('sys.symbol.heart_slash'))
                    this.con7.addSymbolSpan($r('sys.symbol.a_5G'))
                  })
                RichEditor({ controller: this.con8 }).commonStyle()
                  .onReady(() => {
                    this.con8.addSymbolSpan($r('sys.symbol.heart_slash'), { style: this.resourceSymbolStyle })
                    this.con8.addSymbolSpan($r('sys.symbol.a_5G'), { style: this.resourceSymbolStyle })
                  })
              }
            }

            Column() {
              Text('拖拽背板颜色')
              Row() {
                RichEditor({ controller: this.con9 }).commonStyle()
                  .onReady(() => {
                    this.con9.addBuilderSpan(() => {
                      this.attachmentBuilder()
                    })
                  })
                RichEditor({ controller: this.con10 }).commonStyle()
                  .onReady(() => {
                    this.con10.addBuilderSpan(() => {
                      this.attachmentBuilder()
                    }, { dragBackgroundColor: ColorMetrics.resourceColor($r('app.color.color_text')) })
                  })
              }
            }
          }
        }.margin({ bottom: 30 })

        ListItem() {
          Column() {
            Text("组件自身属性测试").fontSize(25).fontWeight(FontWeight.Bold).margin(10)
            Row() {
              Button("切换为资源").onClick(() => {
                this.placeholderColor = this.resourceFontColor
                this.caretColor = this.resourceFontColor
                this.selectedBackgroundColor = this.resourceFontColor
                this.scrollBarColor = ColorMetrics.resourceColor($r('app.color.color_text'))
              })
              Button("切换为普通").onClick((event: ClickEvent) => {
                this.placeholderColor = Color.Red
                this.caretColor = Color.Green
                this.selectedBackgroundColor = Color.Green
                this.scrollBarColor = ColorMetrics.resourceColor(Color.Green)
              })
            }

            Column() {
              Text("placeholder颜色")
              Row() {
                RichEditor({ controller: this.con11 }).commonStyle()
                  .placeholder('普通placeholder颜色测试')
                RichEditor({ controller: this.con11 }).commonStyle()
                  .placeholder('资源placeholder颜色测试', { fontColor: this.placeholderColor })
              }
            }

            Column() {
              Text("光标-手柄-选中区-滚动条")
              Row() {
                RichEditor({ controller: this.con11 }).commonStyle()
                  .onReady(() => this.con11.addTextSpan('默认光标颜色-手柄颜色-选中区背板颜色-滚动条颜色'))
                  .height(50)
                RichEditor({ controller: this.con12 })
                  .commonStyle()
                  .onReady(() => this.con12.addTextSpan('资源光标颜色-手柄颜色-选中区背板颜色-滚动条颜色'))
                  .height(50)
                  .caretColor(this.caretColor)
                  .selectedBackgroundColor(this.selectedBackgroundColor)
                  .scrollBarColor(this.scrollBarColor)
              }
            }
          }
        }.margin({ bottom: 30 })

        ListItem() {
          Column() {
            Text("组件接口测试").fontSize(25).fontWeight(FontWeight.Bold).margin(10)
            Column() {
              Text("UpdateSpanStyle")
              Row() {
                Button("UpdateSpanStyle").onClick(() => {
                  this.con13.updateSpanStyle({ start: -1, end: -1, textStyle: this.allTextStyle })
                  this.con13.updateSpanStyle({ start: -1, end: -1, symbolStyle: this.resourceSymbolStyle })
                })
                Button("ClearSpanStyle").onClick(() => {
                  this.con13.updateSpanStyle({ start: -1, end: -1, textStyle: this.normalTextStyle })
                  this.con13.updateSpanStyle({ start: -1, end: -1, symbolStyle: this.normalSymbolStyle })
                })
              }

              RichEditor({ controller: this.con13 }).commonStyle1()
                .onReady(() => {
                  this.con13.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con13.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con13.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con13.addTextSpan('测试文本更新效果')
                })
            }

            Column() {
              Text("SetTypingStyle")
              Row() {
                Button("Get").onClick(() => {
                  let style: RichEditorTextStyle = this.con14.getTypingStyle()
                  console.info("xyjstest, typingStyle=" + JSON.stringify(style));
                })
                Button("SetNormal").onClick(() => {
                  this.con14.setTypingStyle(this.normalTextStyle)
                })
                Button("SetResource").onClick(() => {
                  this.con14.setTypingStyle(this.allTextStyle)
                })
                Button("Reset").onClick(() => {
                  this.con14.setTypingStyle(undefined)
                })
              }

              RichEditor({ controller: this.con14 }).commonStyle1()
                .onReady(() => {
                  this.con14.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con14.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con14.addSymbolSpan($r('sys.symbol.heart_slash'))
                  this.con14.addTextSpan('测试文本更新效果')
                })
            }
          }

        }.margin({ bottom: 30 })

        ListItem() {
          Column() {
          }.height(500)
        }
      }.width('96%').alignListItem(ListItemAlign.Center)

      List() {
      }.colorBlend(Color.Red).height(300)
    }
  }
}
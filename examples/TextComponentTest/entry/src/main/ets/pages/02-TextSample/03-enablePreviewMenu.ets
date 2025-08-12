import font from '@ohos.font';
import { LengthMetrics } from '@kit.ArkUI';


@Entry
@Component
struct struct_02_TextSample_03_enablePreviewMenu {
  controller: TextAreaController = new TextAreaController()
  @State text: string =
    '姓名:张三' + '\n' + '邮箱:12345@123.com' + '\n' + '电话号码:(86) (755) ********' + '\n' +
      '网址:http://www.123.com' +
      '\n' + '地址:中国北京市东城区天坛东路1号' + '\n' + '时间:2024年8月16号'
  @State enableDataDetector1: boolean = true
  @State types: TextDataDetectorType[] =
    [TextDataDetectorType.PHONE_NUMBER, TextDataDetectorType.URL, TextDataDetectorType.EMAIL,
      TextDataDetectorType.ADDRESS, TextDataDetectorType.DATE_TIME]
  @State lineHeight1: number = 20
  @State type: TextDecorationType = TextDecorationType.None
  @State AItype: TextDecorationType = TextDecorationType.Underline
  @State AIDecorationColor: Color = Color.Green
  @State AIDecorationStyle: TextDecorationStyle = TextDecorationStyle.SOLID
  @State AIfontColor: Color = Color.Green
  @State textfontColor: Color = Color.Red
  @State TextDecorationColor: Color = Color.Black
  @State letterSpacing: number = 5
  @State radius: number = 0
  @State fontColor: Color = Color.Red
  @State fontColor1: Color = Color.Black
  @State fontColor2: Color = Color.Black
  @State fontColor3: Color = Color.Black
  @State fontColor4: Color = Color.Black
  @State fontColor5: Color = Color.Black
  @State fontColor6: Color = Color.Black
  @State fontColor7: Color = Color.Black
  @State fontColor8: Color = Color.Black
  @State fontColor9: Color = Color.Black
  @State fontColor10: Color = Color.Black
  @State fontColor11: Color = Color.Black
  @State fontColor12: Color = Color.Black
  @State fontColor13: Color = Color.Black
  @State fontColor14: Color = Color.Black
  @State fontColor15: Color = Color.Black
  @State fontColor16: Color = Color.Black
  @State fontColor17: Color = Color.Black
  @State fontColor18: Color = Color.Black
  @State fontColor19: Color = Color.Black
  @State fontColor20: Color = Color.Black
  @State fontColor21: Color = Color.Black
  @State fontColor22: Color = Color.Black
  @State fontColor23: Color = Color.Black
  @State fontColor24: Color = Color.Black
  @State fontColor25: Color = Color.Black
  @State fontColor26: Color = Color.Black
  @State fontColor27: Color = Color.Black
  @State fontColor28: Color = Color.Black
  @State fontColor29: Color = Color.Black
  @State fontColor30: Color = Color.Black
  @State fontColor31: Color = Color.Black
  @State fontColor32: Color = Color.Black
  @State fontColor33: Color = Color.Black
  @State fontColor34: Color = Color.Black
  @State fontColor35: Color = Color.Black
  @State fontColor36: Color = Color.Black
  @State fontColor37: Color = Color.Black
  @State fontColor38: Color = Color.Black
  @State fontColor39: Color = Color.Black
  @State fontColor40: Color = Color.Black
  @State fontColor41: Color = Color.Black
  @State fontColor42: Color = Color.Black
  @State fontColor43: Color = Color.Black
  @State fontColor44: Color = Color.Black
  @State fontColor45: Color = Color.Black
  @State fontColor46: Color = Color.Black
  @State fontColor47: Color = Color.Black
  @State fontColor48: Color = Color.Black
  @State fontColor49: Color = Color.Black
  @State fontColor50: Color = Color.Black
  @State fontColor51: Color = Color.Black
  @State fontColor52: Color = Color.Black
  @State fontColor53: Color = Color.Black
  @State fontColor54: Color = Color.Black
  @State fontColor55: Color = Color.Black
  @State fontColor56: Color = Color.Black
  @State fontColor57: Color = Color.Black
  @State fontColor58: Color = Color.Black
  @State fontColor59: Color = Color.Black
  @State fontColor60: Color = Color.Black
  @State fontColor61: Color = Color.Black
  @State fontColor62: Color = Color.Black
  @State fontColor63: Color = Color.Black
  @State fontColor64: Color = Color.Black
  @State fontColor65: Color = Color.Black
  @State fontColor66: Color = Color.Black
  @State fontColor67: Color = Color.Black
  @State fontColor68: Color = Color.Black
  @State fontColor69: Color = Color.Black
  @State fontColor70: Color = Color.Black
  @State fontSize1: number = 16
  @State maxLines: number = 8
  @State fontStyle: FontStyle = FontStyle.Normal
  @State weight: FontWeight = FontWeight.Normal
  @State overflow: TextOverflow = TextOverflow.None
  @State copyOption: CopyOptions = CopyOptions.None
  @State arr: number[] = [0]
  @State num: number = 0
  scroller: Scroller = new Scroller()

  build() {
    Column() {
      Scroll(this.scroller) {
        Text(this.text) {
          ForEach(this.arr, (item: number) => {
            Span(this.text)
          })

        }
        .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
          console.log("onTextSelectionChange:" + selectionStart + " --- " + selectionEnd)
        })
        .border({ width: 1 })
        .enableDataDetector(this.enableDataDetector1)
        .dataDetectorConfig({
          types: this.types,
          onDetectResultUpdate: (result: string) => {
            console.error('FAN, text', result);
          },
          color: this.AIfontColor,
          decoration: ({
            type: this.AItype,
            color: this.AIDecorationColor,
            style: this.AIDecorationStyle
          }),
          enablePreviewMenu: true
        })
        // .textSelectable(TextSelectableMode.SELECTABLE_FOCUSABLE)
        .lineHeight(this.lineHeight1)
        .decoration({ type: this.type, color: this.TextDecorationColor })
        .letterSpacing(this.letterSpacing)
        .textShadow({ radius: this.radius })
        .fontColor(this.textfontColor)
        .font({ size: this.fontSize1, weight: this.weight, style: this.fontStyle })
        .textOverflow({ overflow: this.overflow })
        .draggable(undefined)
        .copyOption(this.copyOption)
        .width('90%')
        // .focusable(true)
        .maxLines(this.maxLines)
        .padding(15)
        .height(300)

      }.height('40%')

      TextArea().margin(10)

      List({ space: 10 }) {
        ListItem() {
          Row({ space: 10 }) {
            Text('是否使用AI接口：').fontSize('16vp')
            Text('是')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.enableDataDetector1 = true
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor1)
              .onFocus(() => {
                this.fontColor1 = Color.Red
              })
              .onBlur(() => {
                this.fontColor1 = Color.Black
              })
            Text('否')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.enableDataDetector1 = false
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor2)
              .onFocus(() => {
                this.fontColor2 = Color.Red
              })
              .onBlur(() => {
                this.fontColor2 = Color.Black
              })
          }
        } //是否使用AI接口
        ListItem() {
          Column({ space: 10 }) {
            Row({ space: 10 }) {
              Text('支持:').fontSize('16vp')
              Text('电话号码')
                .onClick(() => {
                  if (!this.types.some(item => item == TextDataDetectorType.PHONE_NUMBER)) {
                    this.types.push(TextDataDetectorType.PHONE_NUMBER)
                  }
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor3)
                .onFocus(() => {
                  this.fontColor3 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor3 = Color.Black
                })
                .fontSize('16vp')

              Text('网址')
                .onClick(() => {
                  if (!this.types.some(item => item == TextDataDetectorType.URL)) {
                    this.types.push(TextDataDetectorType.URL)
                  }
                })
                .fontSize('16vp')
                .focusOnTouch(true)
                .fontColor(this.fontColor4)
                .onFocus(() => {
                  this.fontColor4 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor4 = Color.Black
                })

              Text('邮箱')
                .onClick(() => {
                  if (!this.types.some(item => item == TextDataDetectorType.EMAIL)) {
                    this.types.push(TextDataDetectorType.EMAIL)
                  }
                })
                .fontSize('16vp')
                .focusOnTouch(true)
                .fontColor(this.fontColor5)
                .onFocus(() => {
                  this.fontColor5 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor5 = Color.Black
                })

              Text('地址')
                .fontSize('16vp')
                .onClick(() => {
                  if (!this.types.some(item => item == TextDataDetectorType.ADDRESS)) {
                    this.types.push(TextDataDetectorType.ADDRESS)
                  }
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor6)
                .onFocus(() => {
                  this.fontColor6 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor6 = Color.Black
                })

              Text('时间')
                .fontSize('16vp')
                .onClick(() => {
                  if (!this.types.some(item => item == TextDataDetectorType.DATE_TIME)) {
                    this.types.push(TextDataDetectorType.DATE_TIME)
                  }
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor7)
                .onFocus(() => {
                  this.fontColor7 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor7 = Color.Black
                })

            }

            Row({ space: 10 }) {
              Text('不支持:').fontSize('16vp')
              Text('电话号码')
                .fontSize('16vp')
                .onClick(() => {
                  this.types = this.types.filter(item => item != TextDataDetectorType.PHONE_NUMBER)
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor8)
                .onFocus(() => {
                  this.fontColor8 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor8 = Color.Black
                })

              Text('网址')
                .fontSize('16vp')
                .onClick(() => {
                  this.types = this.types.filter(item => item != TextDataDetectorType.URL)
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor9)
                .onFocus(() => {
                  this.fontColor9 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor9 = Color.Black
                })

              Text('邮箱')
                .fontSize('16vp')
                .onClick(() => {
                  this.types = this.types.filter(item => item != TextDataDetectorType.EMAIL)
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor10)
                .onFocus(() => {
                  this.fontColor10 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor10 = Color.Black
                })


              Text('地址')
                .fontSize('16vp')
                .onClick(() => {
                  this.types = this.types.filter(item => item != TextDataDetectorType.ADDRESS)
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor11)
                .onFocus(() => {
                  this.fontColor11 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor11 = Color.Black
                })

              Text('时间')
                .fontSize('16vp')
                .onClick(() => {
                  this.types = this.types.filter(item => item != TextDataDetectorType.DATE_TIME)
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor12)
                .onFocus(() => {
                  this.fontColor12 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor12 = Color.Black
                })

            }
          }

        } //支持识别样式
        ListItem() {
          Row({ space: 20 }) {
            Text('行高:').fontSize('16vp')
            Text('-')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.lineHeight1 = this.lineHeight1 - 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor13)
              .onFocus(() => {
                this.fontColor13 = Color.Red
              })
              .onBlur(() => {
                this.fontColor13 = Color.Black
              })
            Text('' + this.lineHeight1)
              .fontSize('16vp')
            Text('+')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.lineHeight1 = this.lineHeight1 + 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor14)
              .onFocus(() => {
                this.fontColor14 = Color.Red
              })
              .onBlur(() => {
                this.fontColor14 = Color.Black
              })


          }
        } //不支持识别的样式
        ListItem() {
          Row({ space: 10 }) {
            Text('文本修饰线:').fontSize('16vp')
            Text('None')
              .fontSize("16vp")
              .width(60)
              .onClick(() => {
                this.type = TextDecorationType.None
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor15)
              .onFocus(() => {
                this.fontColor15 = Color.Red
              })
              .onBlur(() => {
                this.fontColor15 = Color.Black
              })
            Text('上划线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.type = TextDecorationType.Overline
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor16)
              .onFocus(() => {
                this.fontColor16 = Color.Red
              })
              .onBlur(() => {
                this.fontColor16 = Color.Black
              })
            Text('穿透线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.type = TextDecorationType.LineThrough
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor17)
              .onFocus(() => {
                this.fontColor17 = Color.Red
              })
              .onBlur(() => {
                this.fontColor17 = Color.Black
              })
            Text('下划线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.type = TextDecorationType.Underline
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor18)
              .onFocus(() => {
                this.fontColor18 = Color.Red
              })
              .onBlur(() => {
                this.fontColor18 = Color.Black
              })
          }
        } //普通文本修饰线样式
        ListItem() {
          Row({ space: 10 }) {
            Text('修饰线颜色:').fontSize('16vp')
            Text('黑色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.TextDecorationColor = Color.Black
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor45)
              .onFocus(() => {
                this.fontColor45 = Color.Red
              })
              .onBlur(() => {
                this.fontColor45 = Color.Black
              })
            Text('绿色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.TextDecorationColor = Color.Green
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor46)
              .onFocus(() => {
                this.fontColor46 = Color.Red
              })
              .onBlur(() => {
                this.fontColor46 = Color.Black
              })
            Text('蓝色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.TextDecorationColor = Color.Blue
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor47)
              .onFocus(() => {
                this.fontColor47 = Color.Red
              })
              .onBlur(() => {
                this.fontColor47 = Color.Black
              })
            Text('红色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.TextDecorationColor = Color.Red
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor48)
              .onFocus(() => {
                this.fontColor48 = Color.Red
              })
              .onBlur(() => {
                this.fontColor48 = Color.Black
              })
          }
        } //普通文本修饰线颜色
        ListItem() {
          Row({ space: 10 }) {
            Text('AI修饰线样式:').fontSize('16vp')
            Text('None')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AItype = TextDecorationType.None
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor49)
              .onFocus(() => {
                this.fontColor49 = Color.Red
              })
              .onBlur(() => {
                this.fontColor49 = Color.Black
              })
            Text('上划线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AItype = TextDecorationType.Overline
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor50)
              .onFocus(() => {
                this.fontColor50 = Color.Red
              })
              .onBlur(() => {
                this.fontColor50 = Color.Black
              })
            Text('穿透线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AItype = TextDecorationType.LineThrough
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor51)
              .onFocus(() => {
                this.fontColor51 = Color.Red
              })
              .onBlur(() => {
                this.fontColor51 = Color.Black
              })
            Text('下划线')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AItype = TextDecorationType.Underline
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor52)
              .onFocus(() => {
                this.fontColor52 = Color.Red
              })
              .onBlur(() => {
                this.fontColor52 = Color.Black
              })
          }
        } //AI文本修饰线样式

        ListItem() {
          Row({ space: 10 }) {
            Text('AI修饰线颜色:').fontSize('16vp')
            Text('黑色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationColor = Color.Black
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor53)
              .onFocus(() => {
                this.fontColor53 = Color.Red
              })
              .onBlur(() => {
                this.fontColor53 = Color.Black
              })
            Text('绿色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationColor = Color.Green
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor54)
              .onFocus(() => {
                this.fontColor54 = Color.Red
              })
              .onBlur(() => {
                this.fontColor54 = Color.Black
              })
            Text('蓝色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationColor = Color.Blue
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor55)
              .onFocus(() => {
                this.fontColor55 = Color.Red
              })
              .onBlur(() => {
                this.fontColor55 = Color.Black
              })
            Text('红色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationColor = Color.Red
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor56)
              .onFocus(() => {
                this.fontColor56 = Color.Red
              })
              .onBlur(() => {
                this.fontColor56 = Color.Black
              })
          }
        } //AI修饰线颜色
        ListItem() {
          Row({ space: 10 }) {
            Text('AI修饰线类型:').fontSize('16vp')
            Text('SOLID')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationStyle = TextDecorationStyle.SOLID
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor65)
              .onFocus(() => {
                this.fontColor65 = Color.Red
              })
              .onBlur(() => {
                this.fontColor65 = Color.Black
              })
            Text('DOUBLE')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationStyle = TextDecorationStyle.DOUBLE
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor66)
              .onFocus(() => {
                this.fontColor66 = Color.Red
              })
              .onBlur(() => {
                this.fontColor66 = Color.Black
              })
            Text('DOTTED')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationStyle = TextDecorationStyle.DOTTED
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor67)
              .onFocus(() => {
                this.fontColor67 = Color.Red
              })
              .onBlur(() => {
                this.fontColor67 = Color.Black
              })
            Text('DASHED')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIDecorationStyle = TextDecorationStyle.DASHED
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor68)
              .onFocus(() => {
                this.fontColor68 = Color.Red
              })
              .onBlur(() => {
                this.fontColor68 = Color.Black
              })


          }

        } //AI修饰线类型

        ListItem() {

          Text('WAVY')
            .fontSize('16vp')
            .width(60)
            .onClick(() => {
              this.AIDecorationStyle = TextDecorationStyle.WAVY
            })
            .focusOnTouch(true)
            .fontColor(this.fontColor69)
            .onFocus(() => {
              this.fontColor69 = Color.Red
            })
            .onBlur(() => {
              this.fontColor69 = Color.Black
            })

        }

        ListItem() {
          Row({ space: 10 }) {
            Text('AI字体颜色:').fontSize('16vp')
            Text('黑色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIfontColor = Color.Black
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor57)
              .onFocus(() => {
                this.fontColor57 = Color.Red
              })
              .onBlur(() => {
                this.fontColor57 = Color.Black
              })
            Text('绿色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIfontColor = Color.Green
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor58)
              .onFocus(() => {
                this.fontColor58 = Color.Red
              })
              .onBlur(() => {
                this.fontColor58 = Color.Black
              })
            Text('蓝色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIfontColor = Color.Blue
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor59)
              .onFocus(() => {
                this.fontColor59 = Color.Red
              })
              .onBlur(() => {
                this.fontColor59 = Color.Black
              })
            Text('红色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.AIfontColor = Color.Red
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor60)
              .onFocus(() => {
                this.fontColor60 = Color.Red
              })
              .onBlur(() => {
                this.fontColor60 = Color.Black
              })
          }
        } //AI文本字体颜色
        ListItem() {
          Row({ space: 20 }) {
            Text('文本字符间距：').fontSize('16vp')
            Text('-')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.letterSpacing = this.letterSpacing - 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor19)
              .onFocus(() => {
                this.fontColor19 = Color.Red
              })
              .onBlur(() => {
                this.fontColor19 = Color.Black
              })
            Text('' + this.letterSpacing)
              .fontSize('16vp')
            Text('+')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.letterSpacing = this.letterSpacing + 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor20)
              .onFocus(() => {
                this.fontColor20 = Color.Red
              })
              .onBlur(() => {
                this.fontColor20 = Color.Black
              })


          }
        } //文本字符间距
        ListItem() {
          Row({ space: 20 }) {
            Text('阴影模糊半径：').fontSize('16vp')
            Text('-')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.radius = this.radius - 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor21)
              .onFocus(() => {
                this.fontColor21 = Color.Red
              })
              .onBlur(() => {
                this.fontColor21 = Color.Black
              })
            Text('' + this.radius)
              .fontSize('16vp')
            Text('+')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.radius = this.radius + 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor22)
              .onFocus(() => {
                this.fontColor22 = Color.Red
              })
              .onBlur(() => {
                this.fontColor22 = Color.Black
              })


          }
        } //阴影模糊半径
        ListItem() {
          Row({ space: 20 }) {
            Text('字体大小').fontSize('16vp')
            Text('-')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.fontSize1 = this.fontSize1 - 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor23)
              .onFocus(() => {
                this.fontColor23 = Color.Red
              })
              .onBlur(() => {
                this.fontColor23 = Color.Black
              })
            Text('' + this.fontSize1)
              .fontSize('16vp')
            Text('+')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.fontSize1 = this.fontSize1 + 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor24)
              .onFocus(() => {
                this.fontColor24 = Color.Red
              })
              .onBlur(() => {
                this.fontColor24 = Color.Black
              })


          }
        } //字体大小
        ListItem() {
          Row({ space: 10 }) {
            Text('字体颜色:').fontSize('16vp')
            Text('黑色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.textfontColor = Color.Black
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor61)
              .onFocus(() => {
                this.fontColor61 = Color.Red
              })
              .onBlur(() => {
                this.fontColor61 = Color.Black
              })
            Text('绿色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.textfontColor = Color.Green
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor62)
              .onFocus(() => {
                this.fontColor62 = Color.Red
              })
              .onBlur(() => {
                this.fontColor62 = Color.Black
              })
            Text('蓝色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.textfontColor = Color.Blue
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor63)
              .onFocus(() => {
                this.fontColor63 = Color.Red
              })
              .onBlur(() => {
                this.fontColor63 = Color.Black
              })
            Text('红色')
              .fontSize('16vp')
              .width(60)
              .onClick(() => {
                this.textfontColor = Color.Red
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor64)
              .onFocus(() => {
                this.fontColor64 = Color.Red
              })
              .onBlur(() => {
                this.fontColor64 = Color.Black
              })
          }
        } //字体颜色
        ListItem() {
          Row({ space: 20 }) {
            Text('字体样式').fontSize('16vp')
            Text('Normal')
              .fontSize('16vp')
              .onClick(() => {
                this.fontStyle = FontStyle.Normal
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor25)
              .onFocus(() => {
                this.fontColor25 = Color.Red
              })
              .onBlur(() => {
                this.fontColor25 = Color.Black
              })
            Text('Italic')
              .fontSize('16vp')
              .onClick(() => {
                this.fontStyle = FontStyle.Italic
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor26)
              .onFocus(() => {
                this.fontColor26 = Color.Red
              })
              .onBlur(() => {
                this.fontColor26 = Color.Black
              })

          }
        } //字体样式
        ListItem() {
          Row({ space: 5 }) {
            Text('字体粗细:').fontSize('16vp')
            Column({ space: 10 }) {
              Text('Lighter')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Lighter
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor27)
                .onFocus(() => {
                  this.fontColor27 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor27 = Color.Black
                })
              Text('Normal')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Normal
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor28)
                .onFocus(() => {
                  this.fontColor28 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor28 = Color.Black
                })
              Text('Regular')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Regular
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor29)
                .onFocus(() => {
                  this.fontColor29 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor29 = Color.Black
                })
              Text('Medium')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Medium
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor30)
                .onFocus(() => {
                  this.fontColor30 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor30 = Color.Black
                })
              Text('Bold')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Bold
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor31)
                .onFocus(() => {
                  this.fontColor31 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor31 = Color.Black
                })
              Text('Bolder')
                .fontSize('16vp')
                .onClick(() => {
                  this.weight = FontWeight.Bolder
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor32)
                .onFocus(() => {
                  this.fontColor32 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor32 = Color.Black
                })
            }

          }
        } //字体粗细
        ListItem() {
          Row({ space: 5 }) {
            Text('超长文本显示方式:').fontSize('16vp')
            Column({ space: 10 }) {
              Text('None')
                .fontSize('16vp')
                .onClick(() => {
                  this.overflow = TextOverflow.None
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor33)
                .onFocus(() => {
                  this.fontColor33 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor33 = Color.Black
                })
              Text('裁剪')
                .fontSize('16vp')
                .onClick(() => {
                  this.overflow = TextOverflow.Clip
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor34)
                .onFocus(() => {
                  this.fontColor34 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor34 = Color.Black
                })
              Text('省略号')
                .fontSize('16vp')
                .onClick(() => {
                  this.overflow = TextOverflow.Ellipsis
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor35)
                .onFocus(() => {
                  this.fontColor35 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor35 = Color.Black
                })
              Text('跑马灯')
                .fontSize('16vp')
                .onClick(() => {
                  this.overflow = TextOverflow.MARQUEE
                })
                .focusOnTouch(true)
                .fontColor(this.fontColor36)
                .onFocus(() => {
                  this.fontColor36 = Color.Red
                })
                .onBlur(() => {
                  this.fontColor36 = Color.Black
                })

            }

          }
        } //超长文本显示样式
        ListItem() {
          Row({ space: 20 }) {
            Text('最大行数：').fontSize('16vp')
            Text('-')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.maxLines = this.maxLines - 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor37)
              .onFocus(() => {
                this.fontColor37 = Color.Red
              })
              .onBlur(() => {
                this.fontColor37 = Color.Black
              })
            Text('' + this.maxLines)
              .fontSize('16vp')
            Text('+')
              .fontSize('16vp')
              .width(20)
              .onClick(() => {
                this.maxLines = this.maxLines + 1
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor38)
              .onFocus(() => {
                this.fontColor38 = Color.Red
              })
              .onBlur(() => {
                this.fontColor38 = Color.Black
              })


          }
        } //最大行数
        ListItem() {
          Row({ space: 10 }) {
            Text('文本是否可复制粘贴').fontSize('16vp')
            Text('None')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.copyOption = CopyOptions.None
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor39)
              .onFocus(() => {
                this.fontColor39 = Color.Red
              })
              .onBlur(() => {
                this.fontColor39 = Color.Black
              })
            Text('InApp')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.copyOption = CopyOptions.InApp
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor40)
              .onFocus(() => {
                this.fontColor40 = Color.Red
              })
              .onBlur(() => {
                this.fontColor40 = Color.Black
              })
            Text('LocalDevice')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.copyOption = CopyOptions.LocalDevice
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor41)
              .onFocus(() => {
                this.fontColor41 = Color.Red
              })
              .onBlur(() => {
                this.fontColor41 = Color.Black
              })
            Text('CROSS_DEVICE')
              .fontSize('16vp')
              .width(50)
              .onClick(() => {
                this.copyOption = CopyOptions.CROSS_DEVICE
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor42)
              .onFocus(() => {
                this.fontColor42 = Color.Red
              })
              .onBlur(() => {
                this.fontColor42 = Color.Black
              })

          }
        } //复制粘贴
        ListItem() {
          Row({ space: 20 }) {
            Text('增加span')
              .fontSize('16vp')
              .fontSize('16vp')
              .onClick(() => {
                if (this.arr.length == 0) {
                  this.num = 0
                } else {
                  let len = this.arr.length
                  this.num = this.arr[len - 1]
                }
                this.arr.push(this.num)
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor43)
              .onFocus(() => {
                this.fontColor43 = Color.Red
              })
              .onBlur(() => {
                this.fontColor43 = Color.Black
              })
            Text('减少span')
              .fontSize('16vp')
              .onClick(() => {
                if (this.arr.length > 0) {
                  this.arr.pop()
                }
              })
              .focusOnTouch(true)
              .fontColor(this.fontColor44)
              .onFocus(() => {
                this.fontColor44 = Color.Red
              })
              .onBlur(() => {
                this.fontColor44 = Color.Black
              })
          }
        } //增加、减少Span

        ListItem() {
          Column({ space: 10 }) {
            TextArea({ text: this.text, controller: this.controller })
              .fontSize('16vp')
              .onChange((value: string) => {
                this.text = value
              })
          }
        }

      }
      .height('45%')

    }
  }
}

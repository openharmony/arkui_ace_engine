import { LengthMetrics } from '@kit.ArkUI'

@Entry
@Component
struct MultiDecorationPage {
  @State html: string | undefined = undefined;
  @State styledString: StyledString | undefined = undefined;

  controller1: TextController = new TextController();
  controller2: TextController = new TextController();

  mutableStyledString1: MutableStyledString = new MutableStyledString('123456789', [
    {
      start: 0,
      length: 10,
      styledKey: StyledStringKey.FONT,
      styledValue: new TextStyle({ fontColor: Color.Orange, fontSize: LengthMetrics.vp(30) })
    },
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({type: TextDecorationType.LineThrough}, {enableMultiType: true})
    },
    {
      start: 2,
      length: 5,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({type: TextDecorationType.Underline}, {enableMultiType: true})
    },
    {
      start: 0,
      length: 4,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({type: TextDecorationType.Overline}, {enableMultiType: true})
    },
    {
      start: 6,
      length: 2,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({type: TextDecorationType.LineThrough})
    },
    {
      start: 7,
      length: 2,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle(
        {type: TextDecorationType.LineThrough, color: Color.Green},
        {enableMultiType: true})
    },
    {
      start: 8,
      length: 2,
      styledKey: StyledStringKey.DECORATION,
      styledValue: new DecorationStyle({type: TextDecorationType.Overline, color: Color.Green}, {enableMultiType: true})
    },
  ])

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 属性字符串支持多装饰线').fontColor(Color.Blue)
          Text('操作步骤：检查文本是否出现多条装饰线在同一字符上')
          Text('Pass条件："34"字符上同时出现上划线、下划线、中划线').fontColor(Color.Red)

          Text('规格2: 属性字符串多装饰线支持与html互相转换').fontColor(Color.Blue)
          Text('操作步骤：先点击"toHtml"按钮，后点击"fromHtml"按钮')
          Text('Pass条件：新生成的字符串与原多装饰线字符串一致').fontColor(Color.Red)

          Text('规格3: 属性字符串多装饰线支持replaceStyle').fontColor(Color.Blue)
          Text('操作步骤：点击"replaceStyle"按钮')
          Text('Pass条件：多装饰线字符串样式改变').fontColor(Color.Red)

          Text('规格4: 属性字符串多装饰线支持getStyles输出').fontColor(Color.Blue)
          Text('操作步骤：点击"getStyles"按钮')
          Text('Pass条件：日志输出三条start为2，end为4的内容，DecorationType分别为三种装饰线').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Text(undefined, { controller: this.controller1 })
          .height(100)
          .copyOption(CopyOptions.LocalDevice)
          .onAppear(()=>{
            this.styledString = this.mutableStyledString1
            this.controller1.setStyledString(this.mutableStyledString1)
          })

        Row() {
          Button('toHtml').onClick(()=>{
            this.html = StyledString.toHtml(this.styledString)
          }).margin(5)

          Button('fromHtml').onClick(async () => {
            let styledString = await StyledString.fromHtml(this.html)
            this.controller2.setStyledString(styledString)
          })
        }

        Row() {
          Button('replaceStyle').onClick(async () => {
            this.mutableStyledString1.replaceStyle({
              start: 7,
              length: 2,
              styledKey: StyledStringKey.DECORATION,
              styledValue: new DecorationStyle(
                {type: TextDecorationType.LineThrough, color: Color.White},
                {enableMultiType: true})
            })
            this.styledString = this.mutableStyledString1
            this.controller1.setStyledString(this.mutableStyledString1)
          }).margin(5)
          Button('getStyles').onClick(()=>{
            let styles = this.mutableStyledString1.getStyles(0, this.mutableStyledString1.length)
            for (let i = 0; i < styles.length; i++) {
              if (styles[i].styledKey === 1) {
                let start = styles[i].start
                let end = styles[i].start + styles[i].length
                let fontAttr = styles[i].styledValue as DecorationStyle
                let print = 'StyledString start:' + start +
                  ' end:' + end +
                  ' DecorationType:' + fontAttr.type;
                console.log(print)
              }
            }
          }).margin(5)
        }

        Text('========== To Html =========')
        Text(undefined, {controller: this.controller2})
          .fontSize(50)
          .height(100)

        Text('========== Html =========')
        Text(this.html)
      }.width('100%')
    }
  }
}
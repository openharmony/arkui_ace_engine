@Entry
@Component
struct TextInputDecoration {
  onCreateMenu(menuItems: Array<TextMenuItem>) {
    menuItems.forEach((value, index) => {
      value.icon = $r('app.media.startIcon')
      if (value.id.equals(TextMenuItemId.COPY)) {
        value.content = '复制change'
      }
      if (value.id.equals(TextMenuItemId.SELECT_ALL)) {
        value.content = '全选change'
      }
    })
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.startIcon'),
      id: TextMenuItemId.of('custom1'),
    }
    let item2: TextMenuItem = {
      content: 'custom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.startIcon'),
    }
    menuItems.push(item1)
    menuItems.unshift(item2)
    return menuItems
  }
  @State textInputStyle: TextInputStyle = TextInputStyle.Default;
  @State errorMsg: string = '123 4567 89:杭州';
  @State textColor: Color = Color.Black;
  @State direct: Direction = Direction.Ltr;
  @State ali: TextAlign = TextAlign.Start
  @Builder itemEnd() {
    Select([{ value: 'KB' },
      { value: 'MB' },
      { value: 'GB'},
      { value: 'TB',}])
      .height('48vp')
      .borderRadius(0)
      .selected(2)
      .padding('20vp')
      .align(Alignment.Center)
      .value('MB')
      .font({ size: 20, weight: 500 })
      .fontColor('#182431')
      .selectedOptionFont({ size: 20, weight: 400 })
      .optionFont({ size: 20, weight: 400 })
      .backgroundColor(Color.Transparent)
      .responseRegion({height:'40vp',width:'80%',x:'10%',y:'6vp'})
      .onSelect((index: number) => {
        console.info('Select:' + index)
      })
  }
  build() {
    Scroll() {
      Column({space: '5vp'}) {
        TextInput({ text: '123 4567 89:杭州 1' })
          .fontSize('20vp')
          .showError(this.errorMsg)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)

        TextInput({ text: '123 4567 89:杭州 2' })
          .fontSize('20vp')
          .showError(this.errorMsg)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .showUnit(this.itemEnd())
          .showUnderline(true)

        TextInput({ text: '123 4567 89:杭州 3' })
          .fontSize('20vp')
          .showError(this.errorMsg)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .cancelButton({
            style: CancelButtonStyle.CONSTANT
          })

        TextInput({ text: '123 4567 89:杭州 4' })
          .fontSize('20vp')
          .maxLength(100)
          .showCounter(true)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)

        TextInput({ text: '123 4567 89:杭州 5' })
          .fontSize('20vp')
          .maxLength(100)
          .showCounter(true)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .showUnderline(true)
          .showUnit(this.itemEnd())

        TextInput({ text: '123 4567 89:杭州 6' })
          .fontSize('20vp')
          .maxLength(100)
          .showCounter(true)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .cancelButton({
            style: CancelButtonStyle.CONSTANT
          })

        TextInput({ text: 'textIndent('20vp')' })
          .fontSize('20vp')
          .showError(this.errorMsg)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .textIndent('20vp')

        TextInput({ text: 'textIndent('20vp')' })
          .fontSize('20vp')
          .maxLength(100)
          .showCounter(true)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .textIndent('20vp')

        Row({ space: '5vp' }) {
          // 添加按钮，以响应用户点击
          Button() {
            Text('Rtl')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.direct = Direction.Rtl
          })

          // 添加按钮，以响应用户点击
          Button() {
            Text('Ltr')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.direct = Direction.Ltr
          })

          // 添加按钮，以响应用户点击
          Button() {
            Text('Auto')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.direct = Direction.Auto
          })

          // 添加按钮，以响应用户点击
          Button() {
            Text('...Error')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.errorMsg = '...Error'
          })
          // 添加按钮，以响应用户点击
          Button() {
            Text('(+86)')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.errorMsg = '123 4567 89:杭州'
          })

          // 添加按钮，以响应用户点击
          Button() {
            Text('Start')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.ali = TextAlign.Start
          })

          // 添加按钮，以响应用户点击
          Button() {
            Text('END')
              .fontSize(10)
              .fontWeight(FontWeight.Bold)
          }
          .type(ButtonType.Capsule)
          .margin({
            top: 5
          })
          .backgroundColor('#0D9FFB')
          .width('10%')
          .height('2%')
          .onClick(() => {
            this.ali = TextAlign.End
          })
        }
      }
    }
  }
}
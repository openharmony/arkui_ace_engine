@Entry
@Component
struct TextInputSetFont {
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
        TextArea({ text: '123 4567 89:杭州 1\n1234-5678:Hello World' })
          .fontSize('20vp')
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)

        TextArea({ text: '123 4567 89:杭州 2\\n1234-5678:Hello World' })
          .fontSize('20vp')
          .maxLength(100)
          .showCounter(true)
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)

        TextArea({ text: 'textIndent('20vp')\n123 4567 89:杭州 3' })
          .fontSize('20vp')
          .direction(this.direct)
          .width('100%')
          .textAlign(this.ali)
          .showCounter(true)
          .maxLength(100)
          .textIndent('20vp')

        TextArea({ text: 'editMenuOptions\n123 4567 89:杭州 4' })
          .fontSize('20vp')
          .width('100%')
          .direction(this.direct)
          .textAlign(this.ali)
          .editMenuOptions({
            onCreateMenu: this.onCreateMenu, onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
              if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
                console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end)
                return true;
              }
              if (menuItem.id.equals(TextMenuItemId.COPY)) {
                console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end)
                return true;
              }
              if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
                console.log('不拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end)
                return false;
              }
              return false;
            }
          })

        Text('Hello World')
          .fontSize('20vp')
          .direction(this.direct)
          .textAlign(this.ali)
          .width('100%')

        // 添加按钮，以响应用户点击
        Button() {
          Text('Rtl')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.direct = Direction.Rtl
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('Ltr')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.direct = Direction.Ltr
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('Auto')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.direct = Direction.Auto
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('...Error')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.errorMsg = '...Error'
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('(+86)')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.errorMsg = '123 4567 89:杭州'
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('Start')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.ali = TextAlign.Start
        })

        // 添加按钮，以响应用户点击
        Button() {
          Text('END')
            .fontSize(30)
            .fontWeight(FontWeight.Bold)
        }
        .type(ButtonType.Capsule)
        .margin({
          top: 20
        })
        .backgroundColor('#0D9FFB')
        .width('40%')
        .height('5%')
        .onClick(() => {
          this.ali = TextAlign.End
        })
      }
    }
  }
}
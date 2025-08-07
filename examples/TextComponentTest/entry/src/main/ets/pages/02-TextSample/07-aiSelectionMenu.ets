@Entry
@Component
struct TextExample2 {
  @State enableDataDetector1: boolean = true
  @State types: TextDataDetectorType[] = [TextDataDetectorType.PHONE_NUMBER,
    TextDataDetectorType.URL,TextDataDetectorType.EMAIL,TextDataDetectorType.ADDRESS,TextDataDetectorType.DATE_TIME]
  @State lineHeight1: number = 20
  @State type: TextDecorationType = TextDecorationType.None
  @State aiType: TextDecorationType = TextDecorationType.Underline
  @State aiDecorationColor: Color = Color.Green
  @State aiFontColor: Color = Color.Green
  @State textfontColor: Color = Color.Red
  @State textDecorationColor: Color = Color.Black
  @State letterSpacing: number = 5
  @State radius: number = 0
  @State fontColor: Color = Color.Red
  @State fontSize1: number = 16
  @State maxLines: number = 8
  @State fontStyle: FontStyle = FontStyle.Normal
  @State weight: FontWeight  = FontWeight.Normal
  @State overflow: TextOverflow = TextOverflow.None
  @State copyOption: CopyOptions = CopyOptions.LocalDevice
  @State enableDetect: boolean = true

  @State arr:number[] = [0]
  @State num:number = 0

  scroller: Scroller = new Scroller()
  @State text: string =  '天安门广场 真好玩 西湖 www.baidu.com 2025年6月11日 你好'
  controller: TextController = new TextController();
  mutableStr: MutableStyledString = new MutableStyledString('这是属性字符串:\n' + this.text, [{
    start: 0,
    length: 2,
    styledKey: StyledStringKey.FONT,
    styledValue: new TextStyle({fontColor: Color.Red})
  }, {
    start: 0,
    length: 3,
    styledKey: StyledStringKey.DECORATION,
    styledValue: new DecorationStyle({type: TextDecorationType.Underline})
  }]);

  onMenuItemClick = (menuItem: TextMenuItem, textRange: TextRange) => {
    if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
      console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }
    if (menuItem.id.equals(TextMenuItemId.COPY)) {
      console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }
    if (menuItem.id.equals(TextMenuItemId.phoneNumber)) {
      console.log('拦截 OH_DEFAULT_AI_MENU_PHONE start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }
    if (menuItem.id.equals(TextMenuItemId.email)) {
      console.log('拦截 OH_DEFAULT_AI_MENU_PHONE start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }

    if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
      console.log('不拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end);
      return false;
    }
    return false;
  };

  onCreateMenu = (menuItems: Array<TextMenuItem>) => {
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.app_icon'),
      id: TextMenuItemId.of('custom1'),
    };
    let item2: TextMenuItem = {
      content: 'custom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.startIcon'),
    };
    menuItems.unshift(item2);
    menuItems.unshift(item2);
    let newMenuItems: TextMenuItem[] = [];
    menuItems.forEach((value, index) => {
      if (!value.id.equals(TextMenuItemId.email) && !value.id.equals(TextMenuItemId.url) &&
        !value.id.equals(TextMenuItemId.address) && !value.id.equals(TextMenuItemId.phoneNumber) &&
        !value.id.equals(TextMenuItemId.dateTime)) {
        newMenuItems.push(value)
      } else {
        newMenuItems.unshift(value)
      }
    })
    return newMenuItems;
  }
  @State editMenuOptions: EditMenuOptions = {
    onCreateMenu: this.onCreateMenu, onMenuItemClick: this.onMenuItemClick
  };
  build() {
    Column() {
      Scroll(this.scroller){
        Column() {
          Text('这个是普通文本')
            .fontColor(Color.Blue)
            .fontSize(20)
            .copyOption(CopyOptions.InApp)
          Text(this.text)
            .enableDataDetector(true)
            .copyOption(CopyOptions.LocalDevice)
            .fontSize(20)
            .editMenuOptions(this.editMenuOptions)
          Text() {
            Span('This is span\n')
              .fontColor(Color.Green)
              .margin({top: 20})
            Span(this.text)
          }
          .enableDataDetector(true)
          .copyOption(CopyOptions.LocalDevice)
          .fontSize(30)

          Text(undefined, { controller: this.controller })
            .enableDataDetector(true)
            .copyOption(CopyOptions.LocalDevice)
            .draggable(true)
            .fontSize(20)
            .margin({top: 20})
            .onAppear(() => {
              this.controller.setStyledString(this.mutableStr)
            })

          Text('这个是动态切换测试text')
          Text(this.text)
            .fontSize(20)
            .copyOption(this.copyOption)
            .enableDataDetector(this.enableDetect)
            .fontWeight(1)
          Navigation(){

          }
          .title($r('app.string.module_desc'))


          Row() {
            Button('copyOption local')
              .onClick(() => {
                this.copyOption = CopyOptions.LocalDevice
              })
            Button('copyOption inApp')
              .onClick(() => {
                this.copyOption = CopyOptions.InApp
              })
          }
          Row() {
            Button('detect true')
              .onClick(() => {
                this.enableDetect = true
              })
            Button('detect false')
              .onClick(() => {
                this.enableDetect = false
              })
          }

        }
        .height('100%')
      }
      TextArea().margin(10)
        .editMenuOptions(this.editMenuOptions)
    }
  }
}
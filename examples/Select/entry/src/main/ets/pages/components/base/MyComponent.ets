@Preview
@Component
export struct MyComponent {
  @State title: string = 'test'
  func: () => void = (): void => {}

  @Styles pressedStyle(){
    .backgroundColor(0x238e23)
  }

  @Styles normalStyle() {
    .backgroundColor(0x0000ff)
  }

  build() {
    Text(this.title)
      .fontSize(10)
      .backgroundColor(0x0000ff)
      .fontColor(0xffffff)
      .padding(5)
      .onClick(this.func)
      .stateStyles({pressed:this.pressedStyle, normal:this.normalStyle})
      .focusable(false)
  }
}
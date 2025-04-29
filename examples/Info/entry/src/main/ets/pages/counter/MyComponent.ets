@Preview
@Component
export struct MyComponent {
  private title: string = 'test'
  private func: () => void = () => {
  }

  @Styles
  pressedStyle() {
    .backgroundColor(0x238E23)
  }

  @Styles
  normalStyles() {
    .backgroundColor(0x0000FF)
  }

  build() {
    Text(this.title)
      .fontSize(10)
      .backgroundColor(0x0000FF)
      .fontColor(0xFFFFFF)
      .padding(5)
      .onClick(this.func)
      .stateStyles({
        pressed: this.pressedStyle(),
        normal: this.normalStyles()
      })
  }
}
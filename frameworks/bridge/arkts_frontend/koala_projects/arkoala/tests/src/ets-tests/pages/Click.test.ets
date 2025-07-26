@Entry
@Component
export struct Index {
  @State message: string = 'Hello World'
  build() {
    Stack({ alignContent: Alignment.Top }) {
      Row() {
        // BottomTabPage()
        Text(this.message)
        Button(this.message)
          .id("TheButton")
          .onClick(e => {
            console.log("Arkoala onClick callback called")
            this.message = "Clicked"
          })
      }
      .zIndex(2)
      .backgroundColor(0xF50000)
      .height('100%')
      .padding({ left: 10, right: 10,top:40 })
    }
  }
}

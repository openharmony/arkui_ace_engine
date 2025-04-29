// Click on textInput inside the counter and textInput outside the counter,
// and confirm that textInput triggers defocusing and focusing normally
@Entry
@Component
struct CounterExample001 {
  @State value: number = 0

  build() {
    Column() {
      TextInput()
        .width('100%')
      Counter() {
        TextInput()
          .width('50%')
      }
      .width(200)
      .margin(100)
      .onInc(() => {
        this.value++
      })
      .onDec(() => {
        this.value--
      })
    }.width('100%')
  }
}
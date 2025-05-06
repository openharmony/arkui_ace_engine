@Entry
@Component
struct DragBasePage {
  build() {
    Scroll() {
      Column({ space: 20 }) {
        Column() {
          Text('规格1: textInput可以拖拽到其他文本框').fontColor(Color.Blue)
          Text('操作步骤：选中文本框A中的文字，拖动到文本框B')
          Text('Pass条件：文本框A的文字可以拖拽到文本框B').fontColor(Color.Red)
          TextInput({ text: '拖拽这些文本到另一个文本框' }).width('95%').draggable(true)
          Blank().height(50)
          TextInput({ text: '' }).width('95%').draggable(true)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        TextArea()
          .borderWidth(2)
          .height(500)
          .opacity(0)
      }.width('100%')
    }
  }
}
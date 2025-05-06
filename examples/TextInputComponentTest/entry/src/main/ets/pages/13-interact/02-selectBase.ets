@Entry
@Component
struct SelectBasePage {
  @State long_str: string =
    '一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本一段长文本'

  build() {
    Scroll() {
      Column({ space: 20 }) {

        Column() {
          Text('规格1: 双击旋转文本').fontColor(Color.Blue)
          Text('操作步骤：失焦情况下，双击、长按')
          Text('Pass条件：出现蓝色高亮和双手柄').fontColor(Color.Red)

          TextInput({ text: '双击选中，长按选中' }).width('95%').draggable(true)

        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Column() {
          Text('规格2: 选中状态下，滑动文本，高亮不消失').fontColor(Color.Blue)
          Text('操作步骤：全选文本，滑动')
          Text('Pass条件：高亮不消失').fontColor(Color.Red)

          TextInput({ text: this.long_str }).width('95%').draggable(true)
          Blank().height(20)
          TextInput({ text: this.long_str }).width('50%').maxLines(3).style(TextInputStyle.Inline)

        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Column() {
          Text('规格3: 选中之后，拖动手柄，可以拖动').fontColor(Color.Blue)
          Text('Pass条件：正常拖动').fontColor(Color.Red)

          TextInput({ text: '选中之后，拖动手柄，可以拖动' }).width('95%')

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
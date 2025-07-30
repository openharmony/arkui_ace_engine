@Entry
@Component
struct GetTextPage {
  @State message: string = 'Hello World';
  inputController: TextInputController = new TextInputController();
  areaController: TextAreaController = new TextAreaController();
  searchController: SearchController = new SearchController();

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 输入框获取文本，默认获取全部').fontColor(Color.Blue)
          Text('操作步骤：点击“获取文本”的按钮，查看日志输出')
          Text('Pass条件：获取全部文本').fontColor(Color.Red)

          Text('规格2: 输入框获取指定区域文本，仅返回范围内文本').fontColor(Color.Blue)
          Text('操作步骤：点击“获取指定范围文本”的按钮，查看日志输出')
          Text('Pass条件：获取文本为“Hello”').fontColor(Color.Red)

          Text('规格3: 输入框获取指定区域文本，范围参数为异常值，start取0，end取length').fontColor(Color.Blue)
          Text('操作步骤：点击“获取异常范围文本”的按钮，查看日志输出')
          Text('Pass条件：获取全部文本').fontColor(Color.Red)

          Text('规格4: 输入框清除预上屏，不会删除原有文本').fontColor(Color.Blue)
          Text('操作步骤：输入法开启预上屏和中文输入，输入任意内容，点击“清除预上屏”的按钮')
          Text('Pass条件：仅带下划线的预上屏内容被清除').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        TextInput({
          text: this.message + ' TextInput',
          controller: this.inputController
        })

        TextArea({
          text: this.message + ' TextArea',
          controller: this.areaController
        })

        Search({
          value: this.message + ' Search',
          controller: this.searchController
        })

        Button('TextInput 获取文本')
          .onClick(()=>{
            console.log('TextInput 获取文本:' + this.inputController.getText())
          })

        Button('TextInput 获取指定范围文本')
          .onClick(()=>{
            console.log('TextInput 获取指定范围文本:' + this.inputController.getText({ start: 0 ,end: 5 }))
          })

        Button('TextInput 获取异常范围文本')
          .onClick(()=>{
            console.log('TextInput 获取异常范围文本:' + this.inputController.getText({ start: undefined ,end: undefined }))
          })

        Button('TextInput 清除预上屏')
          .onClick(()=>{
            this.inputController.clearPreviewText()
          })

        Text('=========================')
          .margin(5)

        Button('TextArea 获取文本')
          .onClick(()=>{
            console.log('TextArea 获取文本:' + this.areaController.getText())
          })

        Button('TextArea 获取指定范围文本')
          .onClick(()=>{
            console.log('TextArea 获取指定范围文本:' + this.areaController.getText({ start: 0 ,end: 5 }))
          })

        Button('TextArea 获取异常范围文本')
          .onClick(()=>{
            console.log('TextArea 获取异常范围文本:' + this.areaController.getText({ start: undefined ,end: undefined }))
          })

        Button('TextArea 清除预上屏')
          .onClick(()=>{
            this.areaController.clearPreviewText()
          })

        Text('=========================')
          .margin(5)

        Button('Search 获取文本')
          .onClick(()=>{
            console.log('Search 获取文本:' + this.searchController.getText())
          })

        Button('Search 获取指定范围文本')
          .onClick(()=>{
            console.log('Search 获取指定范围文本:' + this.searchController.getText({ start: 0 ,end: 5 }))
          })

        Button('Search 获取异常范围文本')
          .onClick(()=>{
            console.log('Search 获取异常范围文本:' + this.searchController.getText({ start: undefined ,end: undefined }))
          })

        Button('Search 清除预上屏')
          .onClick(()=>{
            this.searchController.clearPreviewText()
          })
      }.width('100%')
    }
  }
}
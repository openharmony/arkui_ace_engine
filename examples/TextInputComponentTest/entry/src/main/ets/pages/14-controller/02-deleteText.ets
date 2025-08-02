@Entry
@Component
struct DragBasePage {
  @State message: string = 'Hello World';
  inputController: TextInputController = new TextInputController();
  areaController: TextAreaController = new TextAreaController();
  searchController: SearchController = new SearchController();

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 输入框删除文本，默认清空全部').fontColor(Color.Blue)
          Text('操作步骤：点击“删除文本”的按钮，输入框清空')
          Text('Pass条件：输入框清空').fontColor(Color.Red)

          Text('规格2: 输入框删除指定区域，仅范围内文本清除').fontColor(Color.Blue)
          Text('操作步骤：点击“删除指定范围文本”的按钮，“Hello”被删除')
          Text('Pass条件：“Hello”被删除').fontColor(Color.Red)

          Text('规格3: 输入框删除指定区域，范围参数为异常值，start取0，end取length').fontColor(Color.Blue)
          Text('操作步骤：点击“删除异常范围文本”的按钮，输入框清空')
          Text('Pass条件：输入框清空').fontColor(Color.Red)

          Text('规格4: 输入框deleteText删除文本，触发onChange、onTextSelectionChange，不触发onWillInsert、onWillDelete、onDidInsert、onDidDelete').fontColor(Color.Blue)
          Text('操作步骤：点击“删除文本”的按钮，查看日志输出')
          Text('Pass条件：只打印onChange、onTextSelectionChange的输出内容').fontColor(Color.Red)
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
          .onWillInsert(()=>{
            console.log('TextInput onWillInsert')
            return true;
          })
          .onWillDelete(()=>{
            console.log('TextInput onWillDelete')
            return true;
          })
          .onDidInsert(()=>{
            console.log('TextInput onDidInsert')
          })
          .onDidDelete(()=>{
            console.log('TextInput onDidDelete')
          })
          .onChange((value:string)=>{
            console.log('TextInput onChange:' + value)
          })
          .onTextSelectionChange((start:number, end:number)=>{
            console.log('TextInput onTextSelectionChange start:' + start + ' end:' + end)
          })

        TextArea({
          text: this.message + ' TextArea',
          controller: this.areaController
        })
          .onWillInsert(()=>{
            console.log('TextArea onWillInsert')
            return true;
          })
          .onWillDelete(()=>{
            console.log('TextArea onWillDelete')
            return true;
          })
          .onDidInsert(()=>{
            console.log('TextArea onDidInsert')
          })
          .onDidDelete(()=>{
            console.log('TextArea onDidDelete')
          })
          .onChange((value:string)=>{
            console.log('TextArea onChange:' + value)
          })
          .onTextSelectionChange((start:number, end:number)=>{
            console.log('TextArea onTextSelectionChange start:' + start + ' end:' + end)
          })

        Search({
          value: this.message + ' Search',
          controller: this.searchController
        })
          .onWillInsert(()=>{
            console.log('Search onWillInsert')
            return true;
          })
          .onWillDelete(()=>{
            console.log('Search onWillDelete')
            return true;
          })
          .onDidInsert(()=>{
            console.log('Search onDidInsert')
          })
          .onDidDelete(()=>{
            console.log('Search onDidDelete')
          })
          .onChange((value:string)=>{
            console.log('Search onChange:' + value)
          })
          .onTextSelectionChange((start:number, end:number)=>{
            console.log('Search onTextSelectionChange start:' + start + ' end:' + end)
          })

        Button('TextInput 删除文本')
          .onClick(()=>{
            this.inputController.deleteText()
          })

        Button('TextInput 删除指定范围文本')
          .onClick(()=>{
            this.inputController.deleteText({start:0, end:5})
          })

        Button('TextInput 删除异常范围文本')
          .onClick(()=>{
            this.inputController.deleteText({start:undefined, end:undefined})
          })

        Button('TextInput 重置')
          .onClick(()=>{
            this.inputController.deleteText()
            this.inputController.addText(this.message + ' TextInput')
          })

        Text('=========================')
          .margin(5)

        Button('TextArea 删除文本')
          .onClick(()=>{
            this.areaController.deleteText()
          })

        Button('TextArea 删除指定范围文本')
          .onClick(()=>{
            this.areaController.deleteText({start:0, end:5})
          })

        Button('TextArea 删除异常范围文本')
          .onClick(()=>{
            this.areaController.deleteText({start:undefined, end:undefined})
          })

        Button('TextArea 重置')
          .onClick(()=>{
            this.areaController.deleteText()
            this.areaController.addText(this.message + ' TextArea')
          })

        Text('=========================')
          .margin(5)

        Button('Search 删除文本')
          .onClick(()=>{
            this.searchController.deleteText()
          })

        Button('Search 删除指定范围文本')
          .onClick(()=>{
            this.searchController.deleteText({start:0, end:5})
          })

        Button('Search 删除异常范围文本')
          .onClick(()=>{
            this.searchController.deleteText({start:undefined, end:undefined})
          })

        Button('Search 重置')
          .onClick(()=>{
            this.searchController.deleteText()
            this.searchController.addText(this.message + ' Search')
          })
      }.width('100%')
    }
  }
}
@Entry
@Component
struct AddTextPage {
  @State message: string = 'Hello World';
  inputController: TextInputController = new TextInputController();
  areaController: TextAreaController = new TextAreaController();
  searchController: SearchController = new SearchController();

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 输入框追加文本，默认加至末尾').fontColor(Color.Blue)
          Text('操作步骤：点击“增加文本”的按钮，输入框末尾增加123')
          Text('Pass条件：对应输入框末尾增加123').fontColor(Color.Red)

          Text('规格2: 输入框增加文本支持emoji').fontColor(Color.Blue)
          Text('操作步骤：点击“增加emoji文本”的按钮，输入框末尾增加emoji')
          Text('Pass条件：对应输入框末尾增加emoji').fontColor(Color.Red)

          Text('规格3: 输入框增加文本支持指定位置插入').fontColor(Color.Blue)
          Text('操作步骤：点击“index为2的位置增加文本”的按钮，输入框在文本第二个位置插入123')
          Text('Pass条件：对应输入框在文本第二个位置插入123').fontColor(Color.Red)

          Text('规格4: 输入框增加文本内容为异常值，不插入内容').fontColor(Color.Blue)
          Text('操作步骤：点击“增加异常文本”的按钮，输入框无变化')
          Text('Pass条件：对应输入框无变化').fontColor(Color.Red)

          Text('规格5: 输入框异常位置增加文本，默认加至末尾').fontColor(Color.Blue)
          Text('操作步骤：点击“异常位置增加文本”的按钮，输入框末尾增加123')
          Text('Pass条件：对应输入框末尾增加123').fontColor(Color.Red)

          Text('规格6: 输入框addText增加文本，触发onChange、onTextSelectionChange，不触发onWillInsert、onWillDelete、onDidInsert、onDidDelete').fontColor(Color.Blue)
          Text('操作步骤：点击“增加文本”的按钮，查看日志输出')
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

        Button('TextInput 增加文本')
          .onClick(()=>{
            this.inputController.addText('123')
          })

        Button('TextInput 增加emoji文本')
          .onClick(()=>{
            this.inputController.addText('🫠')
          })

        Button('TextInput index为2的位置增加文本')
          .onClick(()=>{
            this.inputController.addText('123', {offset: 2})
          })

        Button('TextInput 增加异常文本')
          .onClick(()=>{
            this.inputController.addText(undefined)
          })

        Button('TextInput 异常位置增加文本')
          .onClick(()=>{
            this.inputController.addText('123', { offset: undefined})
          })

        Text('=========================')
          .margin(5)

        Button('TextArea 增加文本')
          .onClick(()=>{
            this.areaController.addText('123')
          })

        Button('TextArea 增加emoji文本')
          .onClick(()=>{
            this.areaController.addText('🫠')
          })

        Button('TextArea index为2的位置增加文本')
          .onClick(()=>{
            this.areaController.addText('123', {offset: 2})
          })

        Button('TextArea 增加异常文本')
          .onClick(()=>{
            this.areaController.addText(undefined)
          })

        Button('TextArea 异常位置增加文本')
          .onClick(()=>{
            this.areaController.addText('123', { offset: undefined})
          })

        Text('=========================')
          .margin(5)

        Button('Search 增加文本')
          .onClick(()=>{
            this.searchController.addText('123')
          })

        Button('Search 增加emoji文本')
          .onClick(()=>{
            this.searchController.addText('🫠')
          })

        Button('Search index为2的位置增加文本')
          .onClick(()=>{
            this.searchController.addText('123', {offset: 2})
          })

        Button('Search 增加异常文本')
          .onClick(()=>{
            this.searchController.addText(undefined)
          })

        Button('Search 异常位置增加文本')
          .onClick(()=>{
            this.searchController.addText('123', { offset: undefined})
          })
      }.width('100%')
    }
  }
}
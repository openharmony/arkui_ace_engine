// xxx.ets
@Entry
@Component
struct struct_02_TextSample_01_numberOfRows {
  @State lineCount: string = "";
  @State glyphPositionAtCoordinate: string = "";
  @State lineMetrics: string = "";
  @State rectsForRangeStr: string = "";
  controller: TextController = new TextController();
  @State textStr: string =
    '春天是年的封面，雨，是春天的景象，人们愿意活在美丽的封面里，愿意沉浸在雨的诗情画意里。' +
      '雨季给了很多遐想，他们都期待着美好，盼望美好是追求的梦想，追求梦想虽是情非得已。' +
      '在仁里这样的一个地方，花桥、鼓楼每一个景物都在印衬着春天雨季的意象中，' +
      '当这些景物都展现在雨中的时候，有时候感觉像是某一个地方的“海市蜃楼”其实这就是仁里，' +
      '最美的景色，在这里你能把这个季节最美的时光尽收眼底。';
  @State charIndex: string = "";
  @State inputContent: string = "";
  @State strLineCount: number = -1

  //获取某字符所在行数
  private getLineOfNthChar(index: number): number {
    let layoutManager = this.controller.getLayoutManager();
    let lineCount = layoutManager.getLineCount()
    for (let line = 0; line < lineCount; line++) {
      let range = layoutManager.getLineMetrics(line)
      if (index >= range.startIndex && index < range.endIndex) {
        return line
      }
    }
    return -1
  }

  build() {
    Scroll() {
      Column() {
        Text(this.textStr, { controller: this.controller })
          .textIndent(50)
          .onAreaChange(() => {
            let layoutManager: LayoutManager = this.controller.getLayoutManager();
            this.lineCount = "LineCount: " + layoutManager.getLineCount();
          })
        Text("第0行开始计数，字符索引：" + this.charIndex + "，所在行:" + this.strLineCount)
          .margin(5)
        TextInput({ text: this.inputContent, placeholder: "请输入要查找的字符索引" })
          .type(InputType.Number)
          .onChange((value) => {
            this.inputContent = value
          })
          .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
            this.charIndex = this.inputContent
            this.inputContent = ""
            this.strLineCount = this.getLineOfNthChar(Number(this.charIndex))
            // 用户名不正确会清空输入框和用户名并提示错误文本

          })
      }
      .margin({ top: 100, left: 8, right: 8 })
    }
  }
}
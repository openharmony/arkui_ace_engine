class TextModifier implements AttributeModifier<TextAttribute> {
  public isActive: boolean | undefined = undefined
  applyNormalAttribute(instance: TextAttribute): void {
    instance.enableAutoSpacing(this.isActive)
  }
}

class TextInputModifier implements AttributeModifier<TextInputAttribute> {
  public isActive: boolean | undefined = undefined
  applyNormalAttribute(instance: TextInputAttribute): void {
    instance.enableAutoSpacing(this.isActive)
  }
}

class TextAreaModifier implements AttributeModifier<TextAreaAttribute> {
  public isActive: boolean | undefined = undefined
  applyNormalAttribute(instance: TextAreaAttribute): void {
    instance.enableAutoSpacing(this.isActive)
  }
}

class SearchModifier implements AttributeModifier<SearchAttribute> {
  public isActive: boolean | undefined = undefined
  applyNormalAttribute(instance: SearchAttribute): void {
    instance.enableAutoSpacing(this.isActive)
  }
}

@Entry
@Component
struct EnableAutoSpacingPage {
  message: string = '普通文本Chinese中西文混排自动123间距Space';
  @State enableAutoSpacing: boolean | undefined = undefined;

  @State textModifier: TextModifier = new TextModifier();
  @State textInputModifier: TextInputModifier = new TextInputModifier();
  @State textAreaModifier: TextAreaModifier = new TextAreaModifier();
  @State searchModifier: SearchModifier = new SearchModifier();

  build() {
    Scroll() {
      Column({ space: 2 }) {
        Column() {
          Text('规格1: 文本类组件支持设置中西文自动间距').fontColor(Color.Blue)
          Text('操作步骤：点击"开启中西文自动间距"按钮')
          Text('Pass条件：文本中英文之间的间距变大').fontColor(Color.Red)

          Text('规格2: 文本类组件设置中西文自动间距为异常值，默认关闭自动间距').fontColor(Color.Blue)
          Text('操作步骤：执行规格1后点击"设置中西文自动间距为异常值"按钮')
          Text('Pass条件：文本中英文之间的间距恢复为初始状态').fontColor(Color.Red)
        }
        .borderWidth(2)
        .margin(10)
        .alignItems(HorizontalAlign.Start)
        .borderColor(Color.Blue)
        .padding(2)
        .width('98%')

        Text('============== Normal =============')
        Text(this.message)
          .fontSize(20)
          .enableAutoSpacing(this.enableAutoSpacing)
        TextInput({
          text: this.message
        })
          .fontSize(20)
          .enableAutoSpacing(this.enableAutoSpacing)
        TextArea({
          text: this.message
        })
          .fontSize(20)
          .enableAutoSpacing(this.enableAutoSpacing)
        Search({
          value: this.message
        })
          .textFont({ size:20 })
          .enableAutoSpacing(this.enableAutoSpacing)

        Text('============== Modifier =============')
        Text(this.message)
          .fontSize(20)
          .attributeModifier(this.textModifier)
        TextInput({
          text: this.message
        })
          .fontSize(20)
          .attributeModifier(this.textInputModifier)
        TextArea({
          text: this.message
        })
          .fontSize(20)
          .attributeModifier(this.textAreaModifier)
        Search({
          value: this.message
        })
          .textFont({ size:20 })
          .attributeModifier(this.searchModifier)

        Button('开启中西文自动间距')
          .onClick(()=>{
            this.enableAutoSpacing = true;
            this.textModifier.isActive = true;
            this.textInputModifier.isActive = true;
            this.textAreaModifier.isActive = true;
            this.searchModifier.isActive = true;
          })

        Button('关闭中西文自动间距')
          .onClick(()=>{
            this.enableAutoSpacing = false;
            this.textModifier.isActive = false;
            this.textInputModifier.isActive = false;
            this.textAreaModifier.isActive = false;
            this.searchModifier.isActive = false;
          })

        Button('设置中西文自动间距为异常值')
          .onClick(()=>{
            this.enableAutoSpacing = undefined;
            this.textModifier.isActive = undefined;
            this.textInputModifier.isActive = undefined;
            this.textAreaModifier.isActive = undefined;
            this.searchModifier.isActive = undefined;
          })
      }
      .height('100%')
      .width('100%')
    }
  }
}
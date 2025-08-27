class TextInputModifier implements AttributeModifier<TextInputAttribute>{
  applyNormalAttribute(instance: TextInputAttribute): void {
    instance.keyboardAppearance(KeyboardAppearance.IMMERSIVE)
  }
}
class TextAreaModifier implements AttributeModifier<TextAreaAttribute>{
  applyNormalAttribute(instance: TextAreaAttribute): void {
    instance.keyboardAppearance(KeyboardAppearance.DARK_IMMERSIVE)
  }
}
class SearchModifier implements AttributeModifier<SearchAttribute>{
  applyNormalAttribute(instance: SearchAttribute): void {
    instance.keyboardAppearance(KeyboardAppearance.DARK_IMMERSIVE)
  }
}
@Entry
@Component
struct TextInputSetFont {
  @State textInputStyle: TextInputStyle = TextInputStyle.Default;
  @State errorMsg: string = 'Error';
  @State textColor: Color = Color.Black;
  @State modifier:TextInputModifier = new TextInputModifier();
  @State modifier2:TextAreaModifier = new TextAreaModifier();
  @State modifier3:SearchModifier = new SearchModifier();
  @State inputType:InputType = InputType.Normal;
  @State enterKeyType:EnterKeyType = EnterKeyType.Go;
  build() {
    Scroll() {
      Column() {
        TextInput({text: '动态切换enterKeyType'})
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(this.enterKeyType)
        Row(){
          Button('Go')
            .width('23%')
            .onClick(() => {
              this.enterKeyType = EnterKeyType.Go
            })
          Button('Search')
            .width('23%')
            .onClick(() => {
              this.enterKeyType = EnterKeyType.Search
            })
          Button('Send')
            .width('23%')
            .onClick(() => {
              this.enterKeyType = EnterKeyType.Send
            })
        }

        TextInput({text: '动态切换Type'})
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(this.inputType)
        Row(){
          Button('Normal')
            .width('23%')
            .onClick(() => {
              this.inputType = InputType.Normal
            })
          Button('Number')
            .width('23%')
            .onClick(() => {
              this.inputType = InputType.Number
            })
          Button('Password')
            .width('23%')
            .onClick(() => {
              this.inputType = InputType.Password
            })
        }
        TextInput({text: 'TextInput defaultFocus false'})
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .defaultFocus(false)

        Search()
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .defaultFocus(false)

        TextArea({text: 'TextArea defaultFocus true'})
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .defaultFocus(true)

        TextInput({text: 'TextInput enableKeyboardOnFocus false'})
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .enableKeyboardOnFocus(false)

        Search()
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .enableKeyboardOnFocus(false)

        TextArea({text: 'TextArea enableKeyboardOnFocus false'})
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enableKeyboardOnFocus(true)

        TextInput({text: 'TextInput 预上屏 false'})
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .enablePreviewText(false)

        Search()
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)
          .enablePreviewText(false)

        TextArea({text: 'TextArea 预上屏 false'})
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enablePreviewText(false)

        TextInput()
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)

        Search()
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)

        TextArea({ text: 'TextArea' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)

        TextArea({ text: 'TextArea Go' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Go)

        TextArea({ text: 'TextArea Search' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Search)

        TextArea({ text: 'TextArea Send' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Send)

        TextArea({ text: 'TextArea Next' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Next)

        TextArea({ text: 'TextArea Done' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.Done)

        TextArea({ text: 'TextArea PREVIOUS' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.PREVIOUS)

        TextArea({ text: 'TextArea NEW_LINE' })
          .fontSize('30vp')
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .enterKeyType(EnterKeyType.NEW_LINE)

        TextInput({ text: 'TextInput Normal' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.Normal)

        TextInput({ text: 'TextInput Number' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.Number)

        TextInput({ text: 'TextInput PhoneNumber' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.PhoneNumber)

        TextInput({ text: 'TextInput Email' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.Email)

        TextInput({ text: 'TextInput Password' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.Password)

        TextInput({ text: 'TextInput NUMBER_PASSWORD' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.NUMBER_PASSWORD)

        TextInput({ text: 'TextInput USER_NAME' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.USER_NAME)

        TextInput({ text: 'TextInput NEW_PASSWORD' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.IMMERSIVE)
          .type(InputType.NEW_PASSWORD)

        TextInput({ text: 'TextInput null' })
          .fontSize('30vp')
          .showError(this.errorMsg)
          .style(this.textInputStyle)
          .keyboardAppearance(null)
        TextInput({ text: 'TextInput undefined' })
          .fontSize('30vp')
          .showError(this.errorMsg)
          .style(this.textInputStyle)
          .keyboardAppearance(undefined)

        TextInput({ text: 'TextInput JS' })
          .fontSize('30vp')
          .showError(this.errorMsg)
          .style(this.textInputStyle)
          .keyboardAppearance(KeyboardAppearance.NONE_IMMERSIVE)
        TextInput({ text: 'TextInput Modifier' })
          .fontSize('30vp')
          .style(this.textInputStyle)
          .attributeModifier(this.modifier)

        TextArea({ text: 'TextArea JS' })
          .fontSize('30vp')
          .showCounter(true)
          .keyboardAppearance(KeyboardAppearance.LIGHT_IMMERSIVE)
        TextArea({ text: 'TextArea Modifier' })
          .fontSize('30vp')
          .showCounter(true)
          .attributeModifier(this.modifier2)

        Search()
          .borderWidth(1)
          .keyboardAppearance(KeyboardAppearance.LIGHT_IMMERSIVE)
        Search()
          .borderWidth(1)
          .attributeModifier(this.modifier3)
      }
      .width('100%')
    }
  }
}
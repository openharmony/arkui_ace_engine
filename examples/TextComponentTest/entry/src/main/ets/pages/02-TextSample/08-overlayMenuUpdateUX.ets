import { CustomTheme, CustomColors, SymbolGlyphModifier } from '@kit.ArkUI'
import { text } from '@kit.ArkGraphics2D'

class GreenColors implements CustomColors {
  fontPrimary = '#ff049404';
  interactiveHover = '#FFF0F8FF';
  interactivePressed = '#FF8C7853';
}

class PageCustomTheme implements CustomTheme {
  colors?: CustomColors

  constructor(colors: CustomColors) {
    this.colors = colors;
  }
}

class MyTextModifier implements AttributeModifier<TextAttribute> {
  public isDark: boolean = false
  applyNormalAttribute(instance: TextAttribute): void {
    if (this.isDark) {
      instance.caretColor(Color.Yellow)
      instance.selectedBackgroundColor(Color.Yellow)
    } else {
      instance.caretColor(Color.Green)
      instance.selectedBackgroundColor(Color.Orange)
    }
  }
}

class MyTextInputModifier implements AttributeModifier<TextInputAttribute> {
  public isDark: boolean = false
  applyNormalAttribute(instance: TextInputAttribute): void {
    if (this.isDark) {
      instance.caretColor(undefined)
      instance.selectedBackgroundColor(undefined)
      instance.onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
        // 调用keepEditableState方法, 输入框保持编辑态
        event.keepEditableState()
        console.log('trigger textInput onsubmit: ' + enterKey + ', Text: ' + event.text)
      })
      instance.fontColor(Color.Blue)
    } else {
      instance.caretColor(Color.Green)
      instance.selectedBackgroundColor(Color.Orange)
      instance.onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
        console.log('trigger textInput onsubmit: ' + enterKey + ', Text: ' + event.text)
      })
      instance.fontColor(Color.Blue)
    }
  }
}

class MyTextAreaModifier implements AttributeModifier<TextAreaAttribute> {
  public isDark: boolean = false
  applyNormalAttribute(instance: TextAreaAttribute): void {
    if (this.isDark) {
      instance.caretColor(undefined)
      instance.selectedBackgroundColor(undefined)
      instance.onSubmit((enterKey: EnterKeyType, event?: SubmitEvent) => {
        // 调用keepEditableState方法, 输入框保持编辑态
        console.log('trigger area onsubmit: ' + enterKey + ', Text: ' + event?.text);
        event?.keepEditableState()
      })
    } else {
      instance.caretColor(Color.Green)
      instance.selectedBackgroundColor(Color.Orange)
      instance.onSubmit((enterKey: EnterKeyType, event?: SubmitEvent) => {
        console.log('trigger area onsubmit: ' + enterKey + ', Text: ' + event?.text);
      })
    }
  }
}

class MySearchModifier implements AttributeModifier<SearchAttribute> {
  public isDark: boolean = false
  applyNormalAttribute(instance: SearchAttribute): void {
    if (this.isDark) {
      instance.onSubmit((value: string, event?: SubmitEvent) => {
        event?.keepEditableState()
        console.log('trigger search onsubmit: ' + value + ', Text: ' + event?.text)
      })
      instance.fontColor(Color.Red)
    } else {
      instance.onSubmit((value: string, event?: SubmitEvent) => {
        console.log('trigger search onsubmit: ' + value + ', Text: ' + event?.text)
      })
      instance.fontColor(Color.Blue)
    }
  }
}

@Entry
@Component
struct TextExample {
  myRichController: RichEditorController = new RichEditorController()
  mySearchController: SearchController = new SearchController()
  @State message: string = 'This is the text content with caretColor set to Blue ' + '& backgroundColor set to Blue';
  @State caretColorValue: Color = Color.Black
  @State selectedColorValue: Color = Color.Black
  @State onStateValue : boolean = true
  @State searchModifier: MySearchModifier = new MySearchModifier()
  @State textModifier: MyTextModifier = new MyTextModifier()
  @State textInputModifier: MyTextInputModifier = new MyTextInputModifier()
  @State textAreaModifier: MyTextAreaModifier = new MyTextAreaModifier()
  value : String = 'Search_Value'
  @State value2 : string|undefined = 'text';
  @State start : number = -1;
  @State end : number = -1;

  onMenuItemClick = (menuItem: TextMenuItem, textRange: TextRange) => {
    if (menuItem.id.equals(TextMenuItemId.of('custom2'))) {
      console.log('拦截 id: custom2 start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }

    if (menuItem.id.equals(TextMenuItemId.COPY)) {
      console.log('拦截 COPY start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }

    if (menuItem.id.equals(TextMenuItemId.phoneNumber)) {
      console.log('拦截 OH_DEFAULT_AI_MENU_PHONE start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }

    if (menuItem.id.equals(TextMenuItemId.email)) {
      console.log('拦截 OH_DEFAULT_AI_MENU_PHONE start:' + textRange.start + '; end:' + textRange.end);
      return true;
    }

    if (menuItem.id.equals(TextMenuItemId.SELECT_ALL)) {
      console.log('不拦截 SELECT_ALL start:' + textRange.start + '; end:' + textRange.end);
      return false;
    }
    return false;
  };

  onCreateMenu = (menuItems: Array<TextMenuItem>) => {
    let item1: TextMenuItem = {
      content: 'custom1',
      icon: $r('app.media.app_icon'),
      id: TextMenuItemId.of('custom1'),
    };
    let item2: TextMenuItem = {
      content: 'custom2',
      id: TextMenuItemId.of('custom2'),
      icon: $r('app.media.startIcon'),
    };
    menuItems.unshift(item2);
    menuItems.unshift(item2);
    let newMenuItems: TextMenuItem[] = [];
    menuItems.forEach((value, index) => {
      if (!value.id.equals(TextMenuItemId.email) && !value.id.equals(TextMenuItemId.url) &&
        !value.id.equals(TextMenuItemId.address) && !value.id.equals(TextMenuItemId.phoneNumber) &&
        !value.id.equals(TextMenuItemId.dateTime)) {
        newMenuItems.push(value)
      } else {
        newMenuItems.unshift(value)
      }
    })
    return newMenuItems;
  }
  @State editMenuOptions: EditMenuOptions = {
    onCreateMenu: this.onCreateMenu, onMenuItemClick: this.onMenuItemClick
  };

  build() {
    Scroll() {
      Column() {
        Text('text no theme')
          .enableDataDetector(true)
          .copyOption(CopyOptions.LocalDevice)
          .fontSize(20)
          .editMenuOptions(this.editMenuOptions)

        Text('Search')
          .fontColor(Color.Blue)
        Search()
          .attributeModifier(this.searchModifier)

        Text('TextInput')
          .fontColor(Color.Blue)
        TextInput()

        Text('TextArea')
          .fontColor(Color.Blue)
        TextArea()

        Text('RichEditor')
          .fontColor(Color.Blue)
        RichEditor({ controller: this.myRichController })

        WithTheme({ theme: new PageCustomTheme(new GreenColors()) }) {
          Column() {
            Text('text custom options')
              .enableDataDetector(true)
              .copyOption(CopyOptions.LocalDevice)
              .fontSize(20)
              .editMenuOptions(this.editMenuOptions)

            Text(this.message) {
              Span('This is the Span and ImageSpan component    ')
              ImageSpan($r('app.media.app_icon'))
                .width('200px')
                .height('200px')
                .objectFit(ImageFit.Fill)
                .verticalAlign(ImageSpanAlignment.CENTER)
              Span('I am LineThrough-span, 中文字符测试, 英文, english')
                .decoration({ type: TextDecorationType.LineThrough, color: Color.Red }).fontSize(25)
            }
            .width(300)
            .height(150)
            .maxLines(5)
            .copyOption(CopyOptions.InApp)
            .onTextSelectionChange((start: number, end: number) => {
              this.start = start
              this.end = end
            })
            .selection(this.start, this.end)
            .attributeModifier(this.textModifier)

            Text('Search').fontSize(25).fontColor(Color.Blue)
            Search({ placeholder: 'search' })
            Search({ placeholder: 'Search Color Blue' })
              .fontColor(Color.Blue)
            Search({ placeholder: 'Search modifier Blue' })
              .attributeModifier(this.searchModifier)
            Search({
              value: '',
              placeholder: 'Type to search...',
              controller: this.mySearchController
            })
            .searchIcon(new SymbolGlyphModifier($r('sys.symbol.magnifyingglass'))
              .fontColor([Color.Red])
            )
            .cancelButton({
              style: CancelButtonStyle.CONSTANT,
              icon: new SymbolGlyphModifier($r('sys.symbol.xmark')).fontColor([Color.Green])
            })
            .searchButton('SEARCH')
            .width('95%')
            .height(100)
            .backgroundColor('#F5F5F5')
            .placeholderColor(Color.Grey)
            .placeholderFont({ size: 14, weight: 400 })
            .textFont({ size: 14, weight: 400 })
            .margin(10)
            .enterKeyType(EnterKeyType.NEW_LINE)
            .attributeModifier(this.searchModifier)

            Text('TextInput').fontSize(25).fontColor(Color.Blue)
            TextInput({ placeholder: 'TextInput: input your word...' })
              .fontColor(Color.Red)
              .enabled(false)
              .enableHapticFeedback(false)
              .attributeModifier(this.textInputModifier)
              .enterKeyType(EnterKeyType.NEW_LINE)
              .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
                console.log('selectionStart: ' + selectionStart);
                console.log('selectionEnd: ' + selectionEnd);
              })

            Text('TextArea').fontSize(25).fontColor(Color.Blue)
            TextArea({ placeholder: 'TextArea: input your word...' })
              .fontColor(Color.Red)
              .onSubmit((enterKey: EnterKeyType, event?: SubmitEvent) => {
                console.log('trigger area onsubmit: ' + enterKey + ', Text: ' + event?.text);
                this.value2 = event?.text;
              })
              .enableHapticFeedback(false)
              .enterKeyType(EnterKeyType.NEW_LINE)
              .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
                console.log('selectionStart: ' + selectionStart);
                console.log('selectionEnd: ' + selectionEnd);
              })

            Text('RichEditor').fontSize(25).fontColor(Color.Blue)
            RichEditor({ controller: this.myRichController })
              .margin(30)
              .border({ width: 1 })
              .enterKeyType(EnterKeyType.Send)
              .borderColor(Color.Black)
              .onSubmit((enterKey: EnterKeyType, event: SubmitEvent) => {
                event.keepEditableState()
                console.log('trigger richEditor onsubmit: ' + enterKey);
              })
            Button('click to change keepEditable.').fontSize(20).height(30)
              .onClick((event) => {
                this.textModifier.isDark = !this.textModifier.isDark
                this.textInputModifier.isDark = !this.textInputModifier.isDark
                this.textAreaModifier.isDark = !this.textAreaModifier.isDark
                this.searchModifier.isDark = !this.searchModifier.isDark
              })
          }.width('100%').margin({ top: 100 })

          .border({
            width: 5, color: Color.Red,
            radius: $r('sys.float.corner_radius_level4')
          })
          .outline({
            width: 5, color: Color.Green,
            radius: $r('sys.float.corner_radius_level4')
          })
        }
      }
    }
  }
}
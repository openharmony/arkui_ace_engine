import { Drawer } from 'common/src/main/ets/components/Drawer';
import { CustomContentDialog } from '@ohos.arkui.advanced.Dialog'
import { SelectionMenu, EditorMenuOptions} from '@ohos.arkui.advanced.SelectionMenu'
import { RadioBlock, ColorBlock } from 'common';

@Component
export struct RichEditorSpanUrlBootcamp {
  @Require @Prop title: ResourceStr;
  @State message: string =
    '华为UX设计规范用于指导软件界面的设计，确保给用户提供清晰一致、简单易用的使用体验，在产品组织内对齐设计语言，拉通体验设计的方向，帮助设计师统一设计品质。';
  @State styledKey: StyledStringKey = StyledStringKey.URL;
  richEditorStyledStringController: RichEditorStyledStringController = new RichEditorStyledStringController()
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomContentDialog({
      contentBuilder: () => {
        this.buildContent();
      },
      buttons: [{ value: 'apply', buttonStyle: ButtonStyleMode.TEXTUAL, action: () => {
        let urlString = new UrlStyle(this.inputValue);
        let mutableStyledString = this.richEditorStyledStringController.getStyledString();
        mutableStyledString.setStyle({
          start: this.selectStart,
          length:(this.selectEnd - this.selectStart),
          styledKey: StyledStringKey.URL,
          styledValue: urlString
        })

        mutableStyledString.setStyle({
          start: this.selectStart,
          length:(this.selectEnd - this.selectStart),
          styledKey: StyledStringKey.BACKGROUND_COLOR,
          styledValue: new BackgroundColorStyle( {color: (this.enableHyperlinkBackgroundColor)? this.hyperlinkBackgroundColor : ''})
        })
        this.richEditorStyledStringController.setStyledString(mutableStyledString);
      } }, { value: 'cancle', buttonStyle: ButtonStyleMode.TEXTUAL, role: ButtonRole.ERROR }],
    }),
  });

  @State showParameters: boolean = false;
  @State enablePopupType: boolean = true;
  @State popupType: number = 0;
  @State inputValue: string = '';
  @State selectStart: number = 0;
  @State selectEnd: number = 0;

  @State enableDisabled: boolean = false;
  @State isEnabled:boolean = true;
  @State enableHyperlinkBackgroundColor: boolean = false;
  @State hyperlinkBackgroundColor: ResourceColor | undefined = undefined;
  @State mutableStyledString: MutableStyledString = new MutableStyledString(this.message)

build() {
    NavDestination() {
      Drawer({
        title: this.title,
        showParameters: $showParameters,
        content: () => {
          this.Content()
        },
        parameters: () => {
          this.Parameters()
        }
      })
    }
    .backgroundColor($r('sys.color.ohos_id_color_sub_background'))
    .hideTitleBar(true)
  }

  @Builder
  Content() {
    Column() {
      Column() {
        RichEditor({ controller: this.richEditorStyledStringController }).key('mutableStyledString')
          .onReady(() => {
            this.richEditorStyledStringController.setStyledString(new StyledString(this.message))
          })
          .bindSelectionMenu(RichEditorSpanType.TEXT, this.MyMenu, RichEditorResponseType.LONG_PRESS)
          .copyOptions(CopyOptions.InApp)
          .onSelectionChange((value: RichEditorRange) => {
            this.selectStart = (value.start == undefined)? 0: value.start;
            this.selectEnd = (value.end == undefined)? 0: value.end;
          })
          .enabled(this.isEnabled)
          .backgroundColor(0XE8E8E8)
          .layoutWeight(2)
      }
    }
  }

  private editorMenuOptions: Array<EditorMenuOptions> =
    [
      { icon: $r('app.media.app_icon'), action: () => {
        this.dialogController.open()
        this.richEditorStyledStringController.closeSelectionMenu()
      }, }]

  @Builder
  MyMenu() {
    Column() {
      SelectionMenu({
        editorMenuOptions: this.editorMenuOptions,
      })
    }
    .width(256)
    .backgroundColor(Color.Transparent)
  }

  @Builder
  buildContent() {
    Column() {
      Row(){
        Text('超链网址')
          .fontSize($r('sys.float.Body_M'))
          .fontColor($r('sys.color.font_secondary'))
          .fontWeight(FontWeight.Medium)
      }
      .padding({ left: 8, right: 8 })
      .width('100%')

      Row(){
        TextInput({ placeholder: 'input url', text: this.inputValue })
          .onChange((value: string) => {
            this.inputValue = value
          })
      }
      .padding({ left: 8, right: 8 })
      .width('100%')

      ColorBlock({
        title: '超链背景颜色',
        isEnabled: this.enableHyperlinkBackgroundColor,
        color: this.hyperlinkBackgroundColor,
      })
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
        RadioBlock({
          title: '设置禁用',
          isEnabled: $enableDisabled,
          value: $isEnabled,
          dataSource: [
            { label: '可用', value: true },
            { label: '不可用', value: false }
          ]
        })
      }
    }
  }
}

@Preview
@Component
struct RichEditorSpanUrlBootcampPreviewer {
  build() {
    RichEditorSpanUrlBootcamp({
      title: '超链接/RichEditor'
    })
  }
}

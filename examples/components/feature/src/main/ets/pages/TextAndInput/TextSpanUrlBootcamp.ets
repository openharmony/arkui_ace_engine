import { Drawer } from 'common/src/main/ets/components/Drawer';
import { CustomContentDialog } from '@ohos.arkui.advanced.Dialog'
import {
  SelectionMenu,
  EditorMenuOptions,
  ExpandedMenuOptions,
  EditorEventInfo,
  SelectionMenuOptions
} from '@ohos.arkui.advanced.SelectionMenu'

@Component
export struct TextSpanUrlBootcamp {
  @Require @Prop title: ResourceStr;
  @State styledKey: StyledStringKey = StyledStringKey.URL;
  controller: TextController = new TextController();
  dialogController: CustomDialogController = new CustomDialogController({
    builder: CustomContentDialog({
      contentBuilder: () => {
        this.buildContent();
      },
      buttons: [{
        value: 'apply', buttonStyle: ButtonStyleMode.TEXTUAL, action: () => {
          let urlString = new UrlStyle(this.inputValue);
          let mutableStyledString = new MutableStyledString('test hello world', [{
            start: this.selectStart,
            length: (this.selectEnd - this.selectStart),
            styledKey: StyledStringKey.URL,
            styledValue: urlString,
          }]);
          this.controller.setStyledString(mutableStyledString);
        }
      }, { value: 'cancle', buttonStyle: ButtonStyleMode.TEXTUAL, role: ButtonRole.ERROR }],
    }),
  });
  @State showParameters: boolean = false;
  @State enablePopupType: boolean = true;
  @State popupType: number = 0;
  @State inputValue: string = '';
  @State selectStart: number = 0;
  @State selectEnd: number = 0;

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
        Text('test hello world', { controller: this.controller }).key('mutableStyledString')
          .bindSelectionMenu(TextSpanType.TEXT, this.MyMenu, TextResponseType.LONG_PRESS)
          .copyOption(CopyOptions.InApp)
          .onTextSelectionChange((selectionStart: number, selectionEnd: number) => {
            this.selectStart = selectionStart;
            this.selectEnd = selectionEnd;
          })
      }
      .height(200)
    }
  }

  private editorMenuOptions: Array<EditorMenuOptions> =
    [
      {
        icon: $r('app.media.app_icon'), action: () => {
        this.dialogController.open()
        this.controller.closeSelectionMenu()
      },
      }]

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
      Flex({ justifyContent: FlexAlign.SpaceBetween, alignItems: ItemAlign.Center }) {
        TextInput({ placeholder: 'input url', text: this.inputValue })
      }
    }
  }

  @Builder
  Parameters() {
    Scroll() {
      Column({ space: 8 }) {
      }
    }
  }
}

@Preview
@Component
struct TextSpanUrlBootcampPreviewer {
  build() {
    TextSpanUrlBootcamp({
      title: '超链接/text'
    })
  }
}
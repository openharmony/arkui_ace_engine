import { TextMenuController } from '@ohos.arkui.UIContext'

interface DisableItem {
  menuItemId: TextMenuItemId;
  name: string;
}

@Entry
@Component
struct DisableSystemMenuIndex {
  message: string = "Hello World!"
  items: Array<DisableItem> = [
    {name: "翻译", menuItemId: TextMenuItemId.TRANSLATE},
    {name: "搜索", menuItemId: TextMenuItemId.SEARCH},
    {name: "拍照输入", menuItemId: TextMenuItemId.CAMERA_INPUT},
    {name: "小艺帮写", menuItemId: TextMenuItemId.AI_WRITER},
    {name: "跨端拍照", menuItemId: TextMenuItemId.COLLABORATION_SERVICE},
    {name: "分享", menuItemId: TextMenuItemId.SHARE},
  ]
  itemMap: Map<string, TextMenuItemId> = new Map()

  build() {
    Column() {
      Column() {
        TextArea({text: this.message})
          .width('80%')
          .copyOption(CopyOptions.LocalDevice)
          .editMenuOptions({
            onCreateMenu: (menuItems: Array<TextMenuItem>) => {
              return menuItems
            },
            onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
              return false
            }
          })
        TextInput({text: this.message})
          .width('80%')
          .editMenuOptions({
            onCreateMenu: (menuItems: Array<TextMenuItem>) => {
              return menuItems
            },
            onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
              return false
            }
          })
        Search({value: this.message})
          .width('80%')
          .editMenuOptions({
            onCreateMenu: (menuItems: Array<TextMenuItem>) => {
              return menuItems
            },
            onMenuItemClick: (menuItem: TextMenuItem, textRange: TextRange) => {
              return false
            }
          })
      }.height('50%')
      Row() {
        ForEach(this.items, (item: DisableItem, index: number) => {
          Toggle({type: ToggleType.Button, isOn: false}) {
            Text(item.name)
          }.onChange((isOn: boolean) => {
            if (isOn) {
              this.itemMap.set(item.name, item.menuItemId)
            } else {
              this.itemMap.delete(item.name)
            }
            TextMenuController.disableMenuItems(Array.from(this.itemMap.values()))
          })
        }, (item: DisableItem, index: number) => {
          return `${index}`
        })
      }
      Toggle({type: ToggleType.Button, isOn: false}) {
        Text("屏蔽所有系统菜单")
      }.onChange((isOn: boolean) => {
        TextMenuController.disableSystemServiceMenuItems(isOn)
      })
      Toggle({type: ToggleType.Button, isOn: false}) {
        Text("开启子窗模式")
      }.onChange((isOn: boolean) => {
        this.getUIContext().getTextMenuController().setMenuOptions({
          showMode: isOn ? TextMenuShowMode.PREFER_WINDOW : TextMenuShowMode.DEFAULT
        })
      })
    }.height('100%')
  }
}
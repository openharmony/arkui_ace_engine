import router from '@ohos.router';

export interface PageParam {
  title: string;
  url: string;
  key: string;
}

const testList: PageParam[] = [
  {
    title: '5-1-EnableKeyboardOnFocus（需要观察键盘接续）',
    url: 'pages/5-focus_keyboard/5-1-EnableKeyboardOnFocus',
    key: '0501'
  },
  {
    title: '5-2-EnterKeyType（需要对比键盘右下角按钮，autoUI无法对比键盘文字）',
    url: 'pages/5-focus_keyboard/5-2-EnterKeyType',
    key: '0502'
  },
  {
    title: '7-1-ContentType（需要启用密码保险箱）',
    url: 'pages/7-content/7-1-ContentType',
    key: '0701'
  },
  {
    title: '7-6-rotateScreen（需要切换横竖屏）',
    url: 'pages/7-content/7-6-rotateScreen',
    key: '0706'
  },
  { title: '8-3-onEditChange（需要操作任务中心）', url: 'pages/8-event/8-3-onEditChange', key: '0803' },
  { title: '10-5-textMarquee（需要滑动屏幕）', url: 'pages/10-DTS/10-5-textMarquee', key: '1005' },
  { title: '10-6-textInput01（需要观察抖动情况）', url: 'pages/10-DTS/10-6-textInput01', key: '1006' },
  {
    title: '10-7-textInputCancelWithFocus（需要观察切换闪烁情况）',
    url: 'pages/10-DTS/10-7-textInputCancelWithFocus',
    key: '1006'
  },
  {
    title: '10-11-canPasteImages（需要对比空格数量）',
    url: 'pages/10-DTS/10-11-canPasteImages',
    key: '1011'
  },
  {
    title: '10-12-allSelectTabsChange（需要外接键盘）',
    url: 'pages/10-DTS/10-12-allSelectTabsChange',
    key: '101201'
  },
  {
    title: '10-12-MenuSwiper（需要滑动）',
    url: 'pages/10-DTS/10-12-MenuSwiper',
    key: '101202'
  },
  {
    title: '11-1-SwitchFocus（需要外接键盘）',
    url: 'pages/11-need-out-keyboard/11-1-SwitchFocus',
    key: '1101'
  },
]

@Entry
@Component
struct NotAdapterAutoTest_2 {
  @State message: string = '无法适配'

  build() {
    Column() {
      Text(this.message)
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Scroll() {
        List({ space: 5 }) {
          ForEach(testList, (item: PageParam) => {
            ListItem() {
              Button(item.title)
                .width('100%')
                .fontSize(20)
                .key(item.key)
                .clip(false)
                .onClick(() => {
                  router.pushUrl({
                    url: item.url
                  }, router.RouterMode.Single)
                })
            }
          }, (item: PageParam) => item.title)
        }
      }
    }
    .height('100%')
  }
}
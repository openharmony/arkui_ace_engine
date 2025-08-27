// main context environment
import { UIContext, CommonModifier } from '@kit.ArkUI';
import router from '@ohos.router';

class MyCheckboxStyle implements ContentModifier<CheckBoxConfiguration> {
  public selectedColor: Color = Color.White;

  constructor(selectedColor: Color) {
    this.selectedColor = selectedColor;
  }

  applyContent(): WrappedBuilder<[CheckBoxConfiguration]> {
    return wrapBuilder(buildCheckbox);
  }
}

@Builder
function buildCheckbox(config: CheckBoxConfiguration) {
  Column({ space: 10 }) {
    Text(config.name + (config.selected ? '（选中）' : '（非选中）'))
    Shape() {
      // 五边形复选框样式
      Path()
        .width(200)
        .height(60)
        .commands('M100 0 L0 100 L50 200 L150 200 L200 100 Z')
        .fillOpacity(0)
        .strokeWidth(3)
      // 红色三角图案样式
      Path()
        .width(10)
        .height(10)
        .commands('M50 0 L100 100 L0 100 Z')
        .visibility(config.selected ? Visibility.Visible : Visibility.Hidden)
        .fill(config.selected ? (config.contentModifier as MyCheckboxStyle).selectedColor : Color.Black)
        .stroke((config.contentModifier as MyCheckboxStyle).selectedColor)
        .margin({ left: 11, top: 10 })
    }
    .width(300)
    .height(200)
    .viewPort({
      x: 0,
      y: 0,
      width: 310,
      height: 310
    })
    .strokeLineJoin(LineJoinStyle.Miter)
    .strokeMiterLimit(5)
    .onClick(() => {
      // 点击后，触发复选框点击状态变化
      if (config.selected) {
        config.triggerChange(false);
      } else {
        config.triggerChange(true);
      }
    })
    .margin({ left: 150 })
  }
}

let storage: LocalStorage = new LocalStorage();
PersistentStorage.persistProp('uiContext', undefined);

@Entry(storage)
@Component
struct MyIndex {
  @StorageLink('uiContext') p: UIContext | undefined | null = this.getUIContext();
  @State result: string = ''
  private items: string[] = [
    '普通全部+沙箱随机20个context',
    '普通全部+沙箱随机50个context',
    '普通全部+沙箱随机100个context',
    '普通全部+沙箱全部',
  ]
  @State modifier: ContentModifier<CheckBoxConfiguration> = new MyCheckboxStyle(Color.Red);
  @State click: CommonModifier = new CommonModifier().onClick(() => {
  })

  build() {
    Column() {
      List({ space: '10vp' }) {
        ForEach(this.items, (item: string) => {
          ListItem() {
            Text(item)
              .fontSize(16)
              .fontWeight(FontWeight.Bold)
              .onClick(() => {
                globalThis.aaa = 'i am from host.';
                if (item === '普通全部+沙箱随机20个context') {
                  router.pushUrl({ url: 'pages/mixed/mixed20'});
                } else if (item === '普通全部+沙箱随机50个context') {
                  router.pushUrl({ url: 'pages/mixed/mixed50'});
                }else if (item === '普通全部+沙箱随机100个context') {
                  router.pushUrl({ url: 'pages/mixed/mixed100'});
                }else if (item === '普通全部+沙箱全部') {
                  router.pushUrl({ url: 'pages/mixed/mixedAll'});
                }
              })
              .width('100%')
              .height('100%')
              .textAlign(TextAlign.Center)

          }.width('80%').height('80vp').backgroundColor('#ff53ecd9').borderRadius(10)
        })
      }.alignListItem(ListItemAlign.Center).margin({ top: '10vp' }).width('100%').height('100%')
    }
  }
}


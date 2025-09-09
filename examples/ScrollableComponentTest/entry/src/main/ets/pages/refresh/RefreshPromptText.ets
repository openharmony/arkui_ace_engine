import { common, ConfigurationConstant } from '@kit.AbilityKit';
import { RefreshModifier } from '@kit.ArkUI';

class CustomModifier extends RefreshModifier {
  applyNormalAttribute(instance: RefreshModifier): void {
    super.applyNormalAttribute?.(instance);
  }
}

// xxx.ets
@Entry
@Component
struct RefreshExample {
  @State isRefreshing: boolean = false;
  @State arr: String[] = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10'];
  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State modifier: RefreshModifier = new CustomModifier();
  @State changeIndex: number = 0;
  @State changeList: (string | Resource | undefined | null)[] = [
    'This is a light promptText', 'This is a light promptText11', undefined, 'This is a light promptText', null,
    'This is a light promptText', '这是prompt', ''
  ];

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.changeIndex++;
          if (this.changeIndex > this.changeList.length - 1) {
            this.changeIndex = 0;
          }
        })
      Text('Index' + this.changeIndex + '数值' + this.changeList[this.changeIndex]).fontColor(Color.Blue)
      Refresh({ refreshing: $$this.isRefreshing, promptText: this.changeList[this.changeIndex] }) { //测试接口
        List() {
          ForEach(this.arr, (item: string) => {
            ListItem() {
              Text('' + item)
                .width('70%')
                .height(80)
                .fontSize(16)
                .margin(10)
                .textAlign(TextAlign.Center)
                .borderRadius(10)
                .backgroundColor(0xFFFFFF)
            }
          }, (item: string) => item)
        }
        .onScrollIndex((first: number) => {
          console.info(first.toString());
        })
        .width('100%')
        .height('100%')
        .alignListItem(ListItemAlign.Center)
        .scrollBar(BarState.Off)
      }
      .onStateChange((refreshStatus: RefreshStatus) => {
        console.info('Refresh onStatueChange state is ' + refreshStatus);
      })
      .onRefreshing(() => {
        setTimeout(() => {
          this.isRefreshing = false;
        }, 2000);
        console.log('onRefreshing test');
      })
      .backgroundColor(0x89CFF0)
    }
  }
}

import hilog from '@ohos.hilog';
import testNapi from 'libentry.so';
import window from '@ohos.window';

@Entry
@Component
struct Index {
  @State message: string = '';
  @State windowId: number|undefined = AppStorage.get<number>('windId');
  @State registerResult: string = 'NA';
  @State clearResult: string = 'NA';

  build() {
    Column({space: 20}) {
      Text('注册' + this.registerResult)
        .id('HelloWorld')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)
      Text('取消注册' + this.clearResult)
        .id('HelloWorld2')
        .fontSize(20)
        .fontWeight(FontWeight.Bold)

      Button('注册过滤回调函数')
        .width('100%')
        .onClick(() => {
          let ret: number = testNapi.registerFilter(this.windowId!);
          this.registerResult = ret == 0? 'success' : 'fail';
          hilog.info(0x0000, 'testTag', 'registerFilter ret:', ret);
        })
      Button('取消过滤回调函数')
        .width('100%')
        .onClick(() => {
          let ret: number = testNapi.clearFilter(this.windowId!);
          this.clearResult = ret == 0? 'success' : 'fail';
          hilog.info(0x0000, 'testTag', 'clearFilter ret:', ret);
        })
      TextInput()

    }
    .width('100%').height('100%')
  }
}
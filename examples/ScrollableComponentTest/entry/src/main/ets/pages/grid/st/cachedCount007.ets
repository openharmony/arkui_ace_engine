import {
  memo,
  __memo_context_type,
  __memo_id_type
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins
import {
  Text,
  TextAttribute,
  Column,
  Component,
  Button,
  ButtonAttribute,
  ClickEvent,
  UserView,
  Grid,
  GridItem,
  GridItemAttribute,
  Color,
  GridAttribute,
  Row,
  TextAlign,
  IDataSource,
  DataChangeListener,
  LazyForEach
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins
import {
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins
import hilog from '@ohos.hilog'

class GoodListSource implements IDataSource<Number> {
  totalCount(): number {
    return this.num;
  }

  getData(index: number): Number {
    return index;
  }

  public onDataReloaded(): void {
    this.listeners.forEach((listener: DataChangeListener) => {
      listener.onDataReloaded();
    });
  }

  registerDataChangeListener(listener: DataChangeListener) {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener) {
    const pos = this.listeners.indexOf(listener)
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  setTotalCount() {
    this.num = 100;
  }

  // TODO: fix LazyForEach!
  num: number = 100; // 5040
  listeners: Array<DataChangeListener> = new Array<DataChangeListener>();
}


/**
 * 验证接口
 * cachedCount
 */
@Component
struct CachedCount {
  @State numbers: Array<string> =
    new Array<string>('0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15');

  aboutToAppear() {
    for (let i = 0; i < 100; ++i) {
      this.idx.push(Math.floor(Math.random() * 5));
    }
  }

  @State data: GoodListSource = new GoodListSource();
  @State ratio: number = 1;
  @State productData: Array<number> = new Array<number>(0, 1, 2, 3, 4, 5, 6, 7);
  @State stateVar: string = 'Hello World';
  urls: Array<string> = new Array<string>('/resources/base/media/foreground.jpg',
    '/resources/base/media/background.png',
    '/resources/base/media/foreground.jpg',
    '/resources/base/media/startIcon.jpg',
    '/resources/base/media/background.png'
  );
  idx: Array<number> = new Array<number>();

  build() {
    Column(undefined) {
      Column(undefined) {

      }.height(100)

      Column(undefined) {
        Button('button')
          .onClick((e: ClickEvent) => {
            hilog.info(0x0000, 'testTag', 'On Click');
            this.data.setTotalCount();
            this.data.onDataReloaded()
          })
        Grid() {
          LazyForEach<Number>(this.data, (item: Number, index: number): void => {
            const url = this.urls[this.idx[index]]
            hilog.info(0x0000, 'testTag', `Koala creating item with ${url}`);
            GridItem() {
              Text(item + '')
                .fontSize(16)
                .backgroundColor(0xF9CF93)
                .width('100%')
                .height(40)
                .textAlign(TextAlign.Center)
            }
            .width('100%')
          }, (item: Number, index: number): string => JSON.stringify(item.valueOf()))
        }
        .columnsTemplate('1fr')
        .columnsGap(1)
        .rowsGap(1)
        .height(300)
        .width('100%')
        .clip(false)
      }
    }
  }
}

export class ComExampleTrivialApplication extends UserView {
  getBuilder() {
    hilog.info(0x0000, 'testTag', 'getBuilder');
    let wrapper = @
    memo() =>
    {
      hilog.info(0x0000, 'testTag', 'CachedCount');
      CachedCount(undefined)
    }
    return wrapper;
  }
}
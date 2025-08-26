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
  GridLayoutOptions,
  EdgeEffect,
  GridItemAttribute,
  Color,
  GridItemStyle,
  GridDirection,
  ComputedBarAttribute,
  GridAttribute,
  ScrollState,
  ItemDragInfo,
  Row,
  Scroller,
  ForEach,
  TextAlign,
  Builder,
  IDataSource,
  DataChangeListener,
  LazyForEach,
  CustomBuilder
} from '@ohos.arkui.component' // TextAttribute should be insert by ui-plugins
import {
  State,
  StateDecoratedVariable,
  MutableState,
  stateOf,
  observableProxy
} from '@ohos.arkui.stateManagement' // should be insert by ui-plugins
import hilog from '@ohos.hilog'

/**
 * 验证接口
 * edgeEffect
 * editMode
 * supportAnimation
 * onItemDragStart
 * onItemDrop
 * onItemDragMove
 * onItemDragEnter
 * onItemDragLeave
 */
@Component
struct GridDemo006 {
  @State edgeEffects: EdgeEffect = EdgeEffect.None;
  @State editMode: boolean = true;
  @State supportAnimation: boolean = false;
  @State text: string = 'drag';
  scroller: Scroller = new Scroller();
  @State numbers: Array<string> =
    ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15'];
  numbersTmp: Array<string> = new Array<string>();

  @Builder
  pixelMapBuilder() { //拖拽过程样式
    Column() {
      Text(this.text)
        .fontSize(16)
        .backgroundColor(0xF9CF93)
        .width(80)
        .height(80)
        .textAlign(TextAlign.Center)
    }
  }

  changeIndex(index1: number, index2: number) { //交换数组位置
    this.numbersTmp = new Array<string>();
    let temp: string;
    temp = this.numbers[index1];
    this.numbers[index1] = this.numbers[index2];
    this.numbers[index2] = temp;
    for (let i = 0; i < this.numbers.length; i++) {
      this.numbersTmp.push(this.numbers[i]);
    }
    this.numbers = this.numbersTmp;
  }

  build() {
    Column(undefined) {
      Column(undefined) {
        Row(undefined) {
          Text('edgeEffect')
            .fontSize(16)
        }

        Row(undefined) {
          Button('EdgeEffect.Spring')
            .onClick((e: ClickEvent) => {
              this.edgeEffects = EdgeEffect.Spring;
            })
          Button('EdgeEffect.Fade')
            .onClick((e: ClickEvent) => {
              this.edgeEffects = EdgeEffect.Fade;
            })
          Button('EdgeEffect.None')
            .onClick((e: ClickEvent) => {
              this.edgeEffects = EdgeEffect.None;
            })
        }

        Row(undefined) {
          Text('editMode')
            .fontSize(16)
        }

        Row(undefined) {
          Button('true')
            .onClick((e: ClickEvent) => {
              this.editMode = true;
            })
          Button('false')
            .onClick((e: ClickEvent) => {
              this.editMode = false;
            })
        }

        Row(undefined) {
          Text('supportAnimation')
            .fontSize(16)
        }

        Row(undefined) {
          Button('true')
            .onClick((e: ClickEvent) => {
              this.supportAnimation = true;
            })
          Button('false')
            .onClick((e: ClickEvent) => {
              this.supportAnimation = false;
            })
        }

        Grid(this.scroller) {
          ForEach(this.numbers, (day: string) => {
            hilog.info(0x0000, 'testTag', 'wsy Grid ForEach day:' + day);
            GridItem() {
              Text(day)
                .fontSize(16)
                .backgroundColor(0xF9CF93)
                .width(80)
                .height(80)
                .textAlign(TextAlign.Center)
            }
          })
        }
        .columnsTemplate('1fr 1fr 1fr')
        .columnsGap(10)
        .rowsGap(10)
        .width('90%')
        .backgroundColor(0xFAEEE0)
        .height(300)
        .edgeEffect(this.edgeEffects)
        .supportAnimation(this.supportAnimation)
        .editMode(this.editMode)
        .onItemDragStart((event: ItemDragInfo, itemIndex: number) => { //第一次拖拽此事件绑定的组件时，触发回调。
          hilog.info(0x0000, 'testTag', 'Grid onItemDragStart itemIndex:' + itemIndex);
          this.text = this.numbers[itemIndex];
          return () => {
            this.pixelMapBuilder();
          }
        })
        .onItemDrop((event: ItemDragInfo, itemIndex: number, insertIndex: number,
          isSuccess: boolean) => { //绑定此事件的组件可作为拖拽释放目标，当在本组件范围内停止拖拽行为时，触发回调。
          // isSuccess=false时，说明drop的位置在grid外部；insertIndex > length时，说明有新增元素的事件发生
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop isSuccess:' + isSuccess);
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop insertIndex:' + insertIndex);
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop this.numbers.length:' + this.numbers.length);
          if (!isSuccess || insertIndex >= this.numbers.length) {
            return;
          }
          // itemIndex拖拽起始位置，insertIndex拖拽插入位置
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop beixiang:');
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop itemIndex:' + itemIndex);
          hilog.info(0x0000, 'testTag', 'Grid onItemDrop insertIndex:' + insertIndex);
          this.changeIndex(itemIndex, insertIndex);
        })
        .onItemDragMove((event: ItemDragInfo, itemIndex: number, insertIndex: number) => { // 拖拽在网格元素范围内移动时触发
          hilog.info(0x0000, 'testTag', 'Grid onItemDragMove itemIndex:' + itemIndex);
          hilog.info(0x0000, 'testTag', 'Grid onItemDragMove insertIndex:' + insertIndex);
        })
        .onItemDragEnter((event: ItemDragInfo) => { // 拖拽进入网格元素范围内时触发
          hilog.info(0x0000, 'testTag', 'Grid onItemDragEnter');
        })
        .onItemDragLeave((event: ItemDragInfo, itemIndex: number) => { // 拖拽离开网格元素时触发
          hilog.info(0x0000, 'testTag', 'Grid onItemDragLeave');
        })
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
      hilog.info(0x0000, 'testTag', 'GridDemo006');
      GridDemo006(undefined)
    }
    return wrapper;
  }
}
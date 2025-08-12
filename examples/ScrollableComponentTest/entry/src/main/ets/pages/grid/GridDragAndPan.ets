/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// 实现拖拽不规则大小的GridItem时有拖拽交换的动画效果，且能上下滑动。

import { emitter } from '@kit.BasicServicesKit';
import { display } from '@kit.ArkUI';

class CardPositionEntity {
  public xPosition: number = -1;
  public yPosition: number = -1;
  public cardWidth: number = -1;
  public cardHeight: number = -1;
}

enum CardSize {
  SMALL_CARD = 0,
  MIDDLE_CARD = 1,
}

enum CardInfo {
  CARD_MARGIN_SCREEN = 16,
  CARD_MARGIN = 12
}

enum EventType {
  CARD_INSERT = 10012,
  CARD_INSERTEND = 10013,
}

interface DeviceCardItemEntity {
  id: string
  text: string
  cardSize: number
}

interface AlarmListener {
  onAlarm():void;
}

class Alarm {
  private mAlarmId: number = -1;
  private mAlarmListener: AlarmListener | null = null;
  private mIsWaitingForCallback: boolean = false;
  private mAlarmTriggerTime: number = Number.MAX_VALUE;
  private mCurrentTime: number = -1;
  private mIsAlarmPending: boolean = false;

  constructor() { }

  setHandler(alarmListener: AlarmListener | null): void {
    this.mAlarmListener = alarmListener;
  }

  setAlarm(millisecondsInFuture: number): void {
    this.mIsAlarmPending = true;
    this.mCurrentTime = Date.now();
    let oldTriggerTime: number = this.mAlarmTriggerTime;
    this.mAlarmTriggerTime = this.mCurrentTime + millisecondsInFuture;

    if (this.mIsWaitingForCallback && oldTriggerTime > this.mAlarmTriggerTime) {
      if (this.mAlarmId !== -1) {
        clearTimeout(this.mAlarmId);
        this.mAlarmId = -1;
      }
      this.mIsWaitingForCallback = false;
    }
    if (!this.mIsWaitingForCallback) {
      this.mAlarmId = setTimeout(() => {
        this.run();
      }, this.mAlarmTriggerTime - this.mCurrentTime);
      this.mIsWaitingForCallback = true;
    }
  }

  cancelAlarm(): void {
    this.mIsAlarmPending = false;
    if (this.mAlarmId !== -1) {
      clearTimeout(this.mAlarmId);
      this.mAlarmId = -1;
    }
  }

  isAlarmPending(): boolean {
    return this.mIsAlarmPending;
  }

  run(): void {
    this.mIsWaitingForCallback = false;
    if (this.mIsAlarmPending) {
      this.mCurrentTime = Date.now();

      if (this.mAlarmTriggerTime > this.mCurrentTime) {
        if (this.mAlarmId !== -1) {
          clearTimeout(this.mAlarmId);
          this.mAlarmId = -1;
        }
        this.mAlarmId = setTimeout(() => {
          this.run()
        }, this.mAlarmTriggerTime - this.mCurrentTime);
        this.mIsWaitingForCallback = true;
      } else {
        this.mIsAlarmPending = false;
        if (this.mAlarmListener != null) {
          this.mAlarmListener.onAlarm();
        }
      }
    }
  }
}

@Component
struct DeviceCommonComponent {
  @Prop itemEntity: DeviceCardItemEntity;
  @Prop deviceLists: DeviceCardItemEntity[];
  @Prop index: number;
  @State dragMove: boolean = false;
  @State dragStart: boolean = false;
  @State longPress: boolean = false;

  @StorageLink('cardIsDrag') cardIsDrag: boolean = false;
  @StorageLink('endId') endId: string = '';
  @StorageLink('startId') startId: string = '';
  @StorageLink('hotId') hotId: string = '';
  private cardPosition: CardPositionEntity = new CardPositionEntity();
  private mAlarm: Alarm = new Alarm();

  @Builder
  cardBuilder () {
    Column() {
      Text(this.itemEntity.text)
        .width('100%')
        .height('100%')
        .borderRadius(10)
        .textAlign(TextAlign.Center)
    }
    .borderRadius(10)
    .lightUpEffect(1)
    .height(this.cardPosition.cardHeight)
    .width(this.cardPosition.cardWidth)
    .backgroundColor(Color.White)
    .shadow({
      offsetY: 15,
      color: '#0D000000',
      radius: 20,
      type: ShadowType.COLOR
    })
  }

  build() {
    Stack({ alignContent: Alignment.Center }) {
      Column() {
        Text(this.itemEntity.text)
          .width('100%')
          .height('100%')
          .borderRadius(10)
          .textAlign(TextAlign.Center)
      }
      .borderRadius(10)
      .lightUpEffect(1)
      .height('100%')
      .width('100%')
      .backgroundColor(Color.White)
      .shadow({
        offsetY: 15,
        color: '#0D000000',
        radius: 20,
        type: ShadowType.COLOR
      })
      .visibility(this.dragStart && this.cardIsDrag ? Visibility.None : Visibility.Visible)
      .onAreaChange((oldValue: Area, newValue: Area) => {
        this.cardPosition.xPosition = Number(newValue.globalPosition.x);
        this.cardPosition.yPosition = Number(newValue.globalPosition.y);
        this.cardPosition.cardWidth = Number(newValue.width);
        this.cardPosition.cardHeight = Number(newValue.height);
      })
    }
    .width('100%')
    .height('100%')
    .onAppear(() => {
      if (this.itemEntity.id == this.startId) {
        this.dragStart = true;
      }
    })
    .onDragStart((event?: DragEvent, extraParams?: string) => {
      console.log('onDragStart---index', this.itemEntity.id, this.index);
      this.dragStart = true;

      AppStorage.set<string>('endId', '');
      AppStorage.set<string>('startId', '');
      AppStorage.set<string>('hotId', '');

      AppStorage.set<string>('startId', this.itemEntity.id);
      AppStorage.set<boolean>('cardIsDrag', true);
    })
    .parallelGesture(
      LongPressGesture()
        .onAction(() => {
          console.log('longPress----');
        })
    )
    .onDragEnter((event?: DragEvent) => {
      this.dragMove = true;
      AppStorage.set<string>('endId', this.itemEntity.id);
      console.log('onDragEnter----', this.itemEntity.id);
    })
    .onDragLeave((event?: DragEvent) => {
      console.log('onDragLeave----', this.itemEntity.id);
      this.dragMove = false;
    })
    .onDragMove((event?: DragEvent) => {
      this.dragMove = true;

      if (!this.mAlarm.isAlarmPending()) {
        this.mAlarm.setHandler(null);
        this.mAlarm.setAlarm(450);
        if (event && this.needMove(event.getWindowX(), event.getWindowY()) && !this.dragStart) {
          AppStorage.set<string>('hotId', this.itemEntity.id);
          this.setEmit(EventType.CARD_INSERT);
        }
      }
    })
    .onDragEnd((event: DragEvent, extraParams?: string) => {
      console.log('onDragEnd----index', this.itemEntity.id, this.index);
      this.dragStart = false;
      this.dragMove = false;
      AppStorage.set<boolean>('cardIsDrag', false);
      AppStorage.set<string>('endId', '');
      AppStorage.set<string>('startId', '');
      AppStorage.set<string>('hotId', '');
    })
    .onDrop((event?: DragEvent, extraParams?: string) => {
      console.log('onDrop----id--hotId-index', this.itemEntity.id, this.hotId, this.index)
      if (event) {
        event.useCustomDropAnimation = true;
      }
      AppStorage.set<boolean>('cardIsDrag', false);

      if (!this.dragMove) {
        return;
      }
      if (this.hotId && this.dragStart) {
        console.log('onDrop Squeeze');
        this.endId = this.hotId;
        this.setEmit(EventType.CARD_INSERTEND);
      }
      this.dragStart = false;
      this.dragMove = false;
      AppStorage.set<boolean>('cardIsDrag', false);
      AppStorage.set<string>('endId', '');
      AppStorage.set<string>('startId', '');
      AppStorage.set<string>('hotId', '');
    })
  }

  private needMove(eventX: number, eventY: number): boolean {
    let hotW = this.cardPosition.cardWidth;
    let hotH = this.cardPosition.cardHeight;
    let hotLeft = this.cardPosition.xPosition + this.cardPosition.cardWidth / 2 -
      hotW / 2;
    let hotRight = this.cardPosition.xPosition + this.cardPosition.cardWidth / 2 +
      hotW / 2;
    let hotTop = this.cardPosition.yPosition + this.cardPosition.cardHeight / 2 -
      hotH / 2;
    let hotBottom = this.cardPosition.yPosition + this.cardPosition.cardHeight / 2 +
      hotH / 2;
    return (eventX > hotLeft && eventX < hotRight && eventY > hotTop && eventY < hotBottom);
  }

  private setEmit(id: number): void {
    emitter.emit({ eventId: id },
      { data: { endId: this.endId, startId: this.startId } });
  }
}

@Entry
@Component
struct GridDragAndPan {
  @State deviceLists: DeviceCardItemEntity[] = []
  @State deviceMap: Map<string, DeviceCardItemEntity> = new Map()

  @StorageLink('deviceCardHeight') deviceCardHeight: number = 1;
  @StorageLink('cardIsDrag') cardIsDrag: boolean = false;
  @StorageProp('midCardWidth') midCardWidth: number = 1;
  @StorageProp('midCardHeight') midCardHeight: number = 1;
  @StorageProp('smallCardWidth') smallCardWidth: number = 1;
  @StorageProp('smallCardHeight') smallCardHeight: number = 1;
  phoneWidth: number = display.getDefaultDisplaySync().width
  windowWithVp: number = px2vp(this.phoneWidth)
  scroller: Scroller = new Scroller()

  aboutToAppear(): void {
    AppStorage.setOrCreate('windowWidthVp', this.windowWithVp);
    const width = (this.windowWithVp - CardInfo.CARD_MARGIN_SCREEN * 2 - CardInfo.CARD_MARGIN) / 2;
    AppStorage.setOrCreate<number>('midCardWidth', Math.floor(width));
    AppStorage.setOrCreate<number>('smallCardWidth', Math.floor(width));
    AppStorage.setOrCreate<number>('midCardHeight', 160 + CardInfo.CARD_MARGIN);
    AppStorage.setOrCreate<number>('smallCardHeight', 80);

    for (let i = 1; i < 110; i++) {
      const size = [1, 2].includes(i) ? CardSize.MIDDLE_CARD : CardSize.SMALL_CARD
      const item: DeviceCardItemEntity = {
        id: i+'',
        text: `${i}`,
        cardSize: size
      }
      this.deviceLists.push(item)
      this.deviceMap.set(`${i}`, item)
    }

    emitter.on({ eventId: EventType.CARD_INSERT }, (eventData) => {
      this.changeCardInsert(eventData);
    });

    emitter.on({ eventId: EventType.CARD_INSERTEND }, (eventData) => {
      AppStorage.set<boolean>('cardIsDrag', false);
      AppStorage.set<string>('endId', '');
      AppStorage.set<string>('startId', '');
      AppStorage.set<string>('hotId', '');
      if (!eventData || !eventData.data || !eventData.data.startId || !eventData.data.endId) {
        console.log('CARD_INSERTEND error startId or endId is null');
        return;
      }
    });
  }

  private changeCardInsert(eventData: emitter.EventData) {
    if (!eventData || !eventData.data || !eventData.data.startId || !eventData.data.endId) {
      console.log('CARD_INSERT error startId or endId is null');
      return;
    }
    animateTo({
      duration: 200,
      curve: Curve.Friction,
      onFinish: () => {
      }
    }, () => {

      let startCard = this.deviceMap.get(eventData?.data?.startId);
      let endCard = this.deviceMap.get(eventData?.data?.endId);
      if (!startCard || !endCard) {
        console.log('CARD_INSERT error startCard or endCard is null');
        return;
      }

      let startIndex = this.deviceLists.findIndex(item => item.id === eventData?.data?.startId);
      let endIndex = this.deviceLists.findIndex(item => item.id === eventData?.data?.endId);
      if (startIndex < 0 || endIndex < 0) {
        console.warn('moveData startIndex or endIndex < 0');
        return;
      }
      this.deviceLists.splice(startIndex, 1);
      this.deviceLists.splice(endIndex, 0, startCard);
    })
  }

  build() {
    Scroll(this.scroller) {
      Column() {
        CustomLayout() {
          ForEach(this.deviceLists, (item: DeviceCardItemEntity, index: number) => {
            if (item) {
              Column() {
                DeviceCommonComponent({ itemEntity: item, deviceLists: this.deviceLists, index: index })
              }
              .height(item.cardSize === CardSize.SMALL_CARD ? this.smallCardHeight : this.midCardHeight)
              .width(item.cardSize === CardSize.SMALL_CARD ? this.smallCardWidth : this.midCardWidth)
            }
          }, (item: DeviceCardItemEntity) => `${item.id}-${item.cardSize}`)
        }
      }
      .alignItems(HorizontalAlign.Start)
      .width('100%')
      .height(this.deviceCardHeight)
      .backgroundColor(Color.Orange)
    }
    .height('100%')
    .width('100%')
    .onDrop((event?: DragEvent, extraParams?: string) => {
      if (event) {
        event.useCustomDropAnimation = true;
      }
      AppStorage.set<boolean>('cardIsDrag', false);
      AppStorage.set<string>('endId', '');
      AppStorage.set<string>('startId', '');
      AppStorage.set<string>('hotId', '');
    })
  }

  aboutToDisappear() {
    emitter.off(EventType.CARD_INSERT);
    emitter.off(EventType.CARD_INSERTEND);
  }
}

@Component
struct CustomLayout {
  @StorageLink('deviceCardHeight') deviceCardHeight: number = 1;
  @Builder doNothingBuilder() {};

  @BuilderParam builder: () => void = this.doNothingBuilder;

  result: SizeResult = {
    width: 0,
    height: 0
  };

  onMeasureSize(selfLayoutInfo: GeometryInfo, children: Array<Measurable>, constraint: ConstraintSizeOptions) {
    children.forEach((child) => {

      child.measure({})
    })
    this.result.width = this.getDeviceCardViewWidth() - CardInfo.CARD_MARGIN_SCREEN * 2;
    this.result.height = this.deviceCardHeight;
    return this.result;
  }

  onPlaceChildren(selfLayoutInfo: GeometryInfo, children: Array<Layoutable>, constraint: ConstraintSizeOptions) {
    this.phoneCustomShow(children);
  }

  private phoneCustomShow(children: Array<Layoutable>) {
    let cardMaxWidth = this.getDeviceCardViewWidth() - CardInfo.CARD_MARGIN_SCREEN * 2;

    let secondColumnPosition  = cardMaxWidth / 2 + 6 + CardInfo.CARD_MARGIN_SCREEN;
    let startPosX = CardInfo.CARD_MARGIN_SCREEN
    let startPosY = 0;
    let remainedHeight = -1;
    let remainedWidth = cardMaxWidth;
    let lastItemHeight = 0;
    let start = -1;
    children.forEach((child, index) => {
      if (remainedHeight === -1) {
        child.layout({ x: startPosX, y: startPosY })
        remainedWidth = remainedWidth - child.measureResult.width;
        if (remainedWidth > 100) {
          remainedHeight = child.measureResult.height;
        } else {
          remainedHeight = 0;
          remainedWidth = cardMaxWidth;
        }
        lastItemHeight = child.measureResult.height;
      } else {
        if (remainedHeight === 0 || child.measureResult.width > 200 || remainedWidth > 200) {
          startPosX = CardInfo.CARD_MARGIN_SCREEN
          startPosY = startPosY + lastItemHeight + CardInfo.CARD_MARGIN;
          child.layout({ x: startPosX, y: startPosY })
          remainedWidth = cardMaxWidth - child.measureResult.width;
          if (remainedWidth > 100) {
            remainedHeight = child.measureResult.height;
          } else {
            remainedHeight = 0;
            remainedWidth = cardMaxWidth;
          }
          lastItemHeight = child.measureResult.height;
          start = -1;
        } else {
          if (start !== -1) {
            startPosX = start;
            startPosY = startPosY + (lastItemHeight - CardInfo.CARD_MARGIN) / 2 + CardInfo.CARD_MARGIN;
            lastItemHeight = child.measureResult.height;
          } else {
            startPosX = secondColumnPosition;
            if (~~remainedHeight === ~~child.measureResult.height) {
              startPosY = startPosY;
            } else if (~~remainedHeight > ~~child.measureResult.height) {
              if (remainedHeight > 100) {
                startPosY = startPosY;
              } else {
                lastItemHeight = child.measureResult.height;
                startPosY = startPosY + lastItemHeight + CardInfo.CARD_MARGIN;
              }
            } else {
              startPosY = startPosY;
              lastItemHeight = child.measureResult.height;
            }
          }
          child.layout({ x: startPosX, y: startPosY })
          if (~~remainedHeight >= ~~child.measureResult.height) {
            if (remainedHeight - child.measureResult.height < 20) {

              remainedHeight = 0;
              start = -1;
            } else {
              remainedHeight = remainedHeight - child.measureResult.height;
              start = startPosX;
            }
          } else {
            remainedHeight = child.measureResult.height - remainedHeight - CardInfo.CARD_MARGIN;
            start = startPosX === CardInfo.CARD_MARGIN_SCREEN ? secondColumnPosition : CardInfo.CARD_MARGIN_SCREEN;
          }
        }
      }
    })
    AppStorage.set<number>('deviceCardHeight', startPosY + lastItemHeight);
  }

  private getDeviceCardViewWidth(): number {
    let screenWidth = AppStorage.get('windowWidthVp') as number;
    return screenWidth;
  }

  build() {
    this.builder()
  }
}
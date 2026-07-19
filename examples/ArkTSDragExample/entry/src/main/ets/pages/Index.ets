import { router } from '@kit.ArkUI';

interface PageItem {
  router?: string;
  name: string;
  description?: string;
}

let pageList: PageItem[] = [
  {
    name: 'BasicDrag - 基本拖拽',
    description: '演示 draggable、onDragStart、onDragEnd、onPreDrag 基本拖拽生命周期',
    router: 'pages/BasicDrag'
  },
  {
    name: 'DragInteraction - 拖拽交互',
    description: '演示 allowDrop、onDragEnter/Leave/Move/Drop 拖放目标交互',
    router: 'pages/DragInteraction'
  },
  {
    name: 'DragPreview - 拖拽预览',
    description: '演示 dragPreview 自定义拖拽预览样式与配置',
    router: 'pages/DragPreview'
  },
  {
    name: 'DragSpringLoading - 弹性加载',
    description: '演示 onDragSpringLoading 拖拽弹性加载效果',
    router: 'pages/DragSpringLoading'
  }
];

@Entry
@Component
struct Index {
  build() {
    Column() {
      List({ space: 20, initialIndex: 0 }) {
        ForEach(pageList, (item: PageItem, index: number) => {
          ListItem() {
            Column({ space: 10 }) {
              Text(item.name)
                .fontSize(20)
                .fontColor('#39b5fa')
                .maxLines(1)
              Text(item.description)
                .fontSize(14)
                .fontColor('#666666')
                .width('100%')
            }
            .margin({ bottom: index >= pageList.length - 1 ? 100 : 0 })
            .padding({
              top: '3%',
              right: '10.00%',
              bottom: '5%',
              left: '10.00%'
            })
            .width('100%')
            .constraintSize({ minHeight: 100 })
            .borderRadius(10)
            .backgroundColor(0xFFFFFF)
            .onClick(() => {
              if (item.router) {
                router.pushUrl({ url: item.router })
              }
            })
          }
        })
      }
      .listDirection(Axis.Vertical)
      .width('100%')
      .layoutWeight(1)
      .padding({ top: 20 })
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#F1F3F5')
  }
}

import { common, ConfigurationConstant } from '@kit.AbilityKit';
import { ListItemGroupModifier, ListItemModifier, ListModifier } from '@kit.ArkUI';

class CustomModifier1 implements AttributeModifier<ListAttribute> {
  public changeIndex: number = 0;
  public changeList: (number | Resource | undefined | null)[] = [
    200, 330, 300, 200, undefined,
    200, null, 200, -100, 200, 0
  ];

  applyNormalAttribute(instance: ListAttribute): void {
    instance.lanes({
      minLength: 100,
      maxLength: this.changeList[this.changeIndex],
    })
  }
}

// xxx.ets
@Entry
@Component
struct ListItemGroupExample11 {
  private timeTable: TimeTable[] = [
    {
      title: '星期一',
      projects: ['语文', '数学', '英语']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期一',
      projects: ['数学', '英语', '语文']
    },
    {
      title: '星期二',
      projects: ['物理', '化学', '生物']
    },
    {
      title: '星期三',
      projects: ['历史', '地理', '政治']
    },
    {
      title: '星期四',
      projects: ['美术', '音乐', '体育']
    },
    {
      title: '星期五',
      projects: ['计算机', '编程', '设计']
    },
    {
      title: '星期六',
      projects: ['阅读', '写作', '讨论']
    },
    {
      title: '星期日',
      projects: ['休息', '娱乐', '自由活动']
    }
  ];

  @Builder
  itemHead(text: string) {
    Text(text)
      .fontSize(20)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(10)
  }

  @Builder
  itemFoot(num: number) {
    Text('共' + num + '节课')
      .fontSize(16)
      .backgroundColor(0xAABBCC)
      .width('100%')
      .padding(5)
  }

  @State isDark: boolean = false;
  @State context: common.UIAbilityContext = getContext(this) as common.UIAbilityContext;
  @State vOutSetValueTwo: number = 40;
  @State modifier1: CustomModifier1 = new CustomModifier1();

  build() {
    Column() {
      Button('切换数值')
        .onClick(() => {
          this.modifier1.changeIndex++;
          if (this.modifier1.changeIndex > this.modifier1.changeList.length - 1) {
            this.modifier1.changeIndex = 0;
          }
        })
      Text('Index' + this.modifier1.changeIndex + '数值' + this.modifier1.changeList[this.modifier1.changeIndex])
        .fontColor(Color.Blue)
      List({ space: 20 }) {
        ForEach(this.timeTable, (item: TimeTable) => {
          ListItemGroup({ header: this.itemHead(item.title), footer: this.itemFoot(item.projects.length) }) {
            ForEach(item.projects, (project: string) => {
              ListItem() {
                Text(project)
                  .width('100%')
                  .height(100)
                  .fontSize(20)
                  .textAlign(TextAlign.Center)
                  .backgroundColor(0xFFFFFF)
              }
            }, (item: string) => item)
          }
        })
      }
      .attributeModifier(this.modifier1 as CustomModifier1)
      .width('90%')
      .sticky(StickyStyle.Header | StickyStyle.Footer)
      .scrollBar(BarState.Off)
    }.width('100%').height('100%').backgroundColor(0xDCDCDC).padding({ top: 5 })
  }
}

interface TimeTable {
  title: string;
  projects: string[];
}

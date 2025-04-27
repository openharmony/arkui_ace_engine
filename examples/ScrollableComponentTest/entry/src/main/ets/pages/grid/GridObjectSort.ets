import {
  GridObjectSortComponent,
  GridObjectSortComponentItem,
  GridObjectSortComponentOptions,
  GridObjectSortComponentType,
} from '@ohos.arkui.advanced.GridObjectSortComponent';

/**
 * 适配终端设备场景中菜单/图文/文本的展示交互和编辑排序
 */
@Entry
@Component
struct ImageText {
  @State dataList: GridObjectSortComponentItem[] = [
    {
      id: 0,
      url:$r('app.media.background'),
      text: 'facebook14k',
      selected: true,
      order: 3
    },
    {
      id: 1,
      url:$r('app.media.background'),
      text: 'googlegoogle3',
      selected: true,
      order: 9
    },
    {
      id: 2,
      url:$r('app.media.background'),
      text: 'instagram',
      selected: false,
      order: 1
    },
    {
      id: 3,
      url:$r('app.media.background'),
      text: 'linkedin',
      selected: false,
      order: 4
    },
    {
      id: 4,
      url:$r('app.media.background'),
      text: 'pinterestSt',
      selected: false,
      order: 5
    },
    {
      id: 5,
      url:$r('app.media.background'),
      text: 'Twitter14',
      selected: true,
      order: 6
    },
    {
      id: 6,
      url:$r('app.media.background'),
      text: 'youtube',
      selected: true,
      order: 7
    },
    {
      id: 7,
      url:$r('app.media.background'),
      text: 'tumber1',
      selected: true,
      order: 8
    },
    {
      id: 8,
      url:$r('app.media.background'),
      text: 'vk',
      selected: true,
      order: 9
    }
  ]
  @State option: GridObjectSortComponentOptions = {
    type: GridObjectSortComponentType.IMAGE_TEXT,
    imageSize: 56,
    normalTitle: '菜单',
    editTitle: '编辑',
    showAreaTitle: '长按拖动排序',
    addAreaTitle: '点击添加',
  }

  build() {
    Column() {
      GridObjectSortComponent({
        dataList: this.dataList,
        options: this.option,
        onSave: (select: GridObjectSortComponentItem[], unselect: GridObjectSortComponentItem[]) => {
          console.log('1');
        },
        onCancel: () => {
          console.log('2');
        }
      })
    }
  }
}
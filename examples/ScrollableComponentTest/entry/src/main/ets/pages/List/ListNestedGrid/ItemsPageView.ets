import { ListItemAdapter } from './ListItemAdapter'

@Component
export struct ItemsPageView {
  @Prop tabBarIndex: number
  @State private adapter: ListItemAdapter<DataModel> = new ListItemAdapter();
  gridItems: DataModel = {
    itemType: ItemType.gridItems,
    'result': [
      {
        'name': 'grid_1',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'grid_2',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'grid_3',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'grid_4',
        'icon': 'resources/base/media/startIcon.png'
      }
    ]
  }
  listItems: DataModel = {
    itemType: ItemType.listItems,
    'result':[
      {
        'name': 'list_1',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_2',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_3',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_4',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_5',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_6',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_7',
        'icon': 'resources/base/media/startIcon.png'
      },
      {
        'name': 'list_8',
        'icon': 'resources/base/media/startIcon.png'
      }

    ]
  }

  aboutToAppear(): void {
    let tmp: DataModel[] =[]
    tmp.push(this.listItems)
    tmp.push(this.gridItems)
    this.adapter.addList(tmp)
  }

  build() {
    Column() {
      LazyForEach(this.adapter, (item: DataModel) => {
        if (item.itemType === ItemType.listItems) {
          ListComponent({ listItemData: item.result })
        } else if (item.itemType === ItemType.gridItems) {
          GridComponent({ gridItemData: item.result })
        }
      })
    }
    .height('auto')
    .padding(10)
  }
}

export interface Grids {
  icon?: Resource
  name: string
}

@Component
export struct GridComponent {
  girdAdapter: ListItemAdapter<ESObject> = new ListItemAdapter();
  gridItemData: Array<ESObject> = []

  aboutToAppear(): void {
    this.girdAdapter.addList(this.gridItemData)
  }

  build() {
    Grid() {
      LazyForEach(this.girdAdapter, (item: Grids) => {
        GridItem() {
          Column() {
            Image(item.icon)
              .borderRadius(25)
              .width(50)
              .aspectRatio(1)
            Text(item.name).fontSize(16).margin({ top: 15 })
          }
        }
      }, (item: Grids) => item.name)
    }
    .layoutDirection(GridDirection.Column)
    .columnsTemplate('1fr 1fr')
    .rowsGap(15)
    .columnsGap(10)
    .padding({ top: 10, bottom: 10 })
    .height(210)
    .width('100%')
  }
}

export interface Lists {
  icon?: Resource
  name: string
}

@Component
export struct ListComponent {
  listAdapter: ListItemAdapter<ESObject> = new ListItemAdapter();
  listItemData: Array<ESObject> = []

  aboutToAppear(): void {
    this.listAdapter.addList(this.listItemData)
  }

  build() {
    Column() {
      LazyForEach(this.listAdapter, (item: Lists) => {
        Column() {
          Image(item.icon)
            .borderRadius(25)
            .width(50)
            .aspectRatio(1)
          Text(item.name).fontSize(16).margin({ top: 15 })
        }
      }, (item: Lists) => item.name)
    }
    .padding({ top: 10, bottom: 10 })
    .height('auto')
    .width('100%')
  }
}

export enum ItemType {
  listItems = 'listItems',
  gridItems = 'gridItems'
}

export class DataModel {
  itemType: ItemType = ItemType.listItems
  result: ESObject
}
@Observed
class ObservedArray<T> extends Array<T> {
  constructor(args: T[]) {
    super(...args);
  }
}

@Component
struct Item {
  @ObjectLink itemArr: ObservedArray<string>;

  build() {
    Row() {
      ForEach(this.itemArr, (item: string, index: number) => {
        Text(`${index}: ${item}`)
          .width(100)
          .height(100)
      }, (item: string) => item)
    }
  }
}

@Entry
@Component
struct IndexPage {
  @State arr: Array<ObservedArray<string>> = [new ObservedArray<string>(['apple']), new ObservedArray<string>(['banana']), new ObservedArray<string>(['orange'])];

  build() {
    Column() {
      ForEach(this.arr, (itemArr: ObservedArray<string>) => {
        Item({ itemArr: itemArr })
      }, (item: ObservedArray<string>) => item.toString())

      Divider()

      Button('push two-dimensional array item')
        .margin(10)
        .onClick(() => {
          this.arr[0].push('strawberry');
        })

      Button('push array item')
        .margin(10)
        .onClick(() => {
          this.arr.push(new ObservedArray<string>(['pear']));
        })

      Button('change two-dimensional array first item')
        .margin(10)
        .onClick(() => {
          this.arr[0][0] = 'APPLE';
        })

      Button('change array first item')
        .margin(10)
        .onClick(() => {
          this.arr[0] = new ObservedArray<string>(['watermelon']);
        })
    }
  }
}

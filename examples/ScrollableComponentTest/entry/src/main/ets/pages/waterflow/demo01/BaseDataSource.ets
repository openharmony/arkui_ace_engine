// 实现IDataSource接口的对象，用于瀑布流组件加载数据
export class BasicDataSource<T> implements IDataSource {
  private originDataArray: T[] = [];
  private listeners: DataChangeListener[] = [];

  public totalCount(): number {
    return 0;
  }

  public getData(index: number): T {
    return this.originDataArray[index];
  }

  // 注册改变数据的控制器
  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  // 注销改变数据的控制器
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  // 通知控制器数据重新加载
  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  //通知控制器数据批量修改
  notifyDatasetChange(operations: DataOperation[]): void {
    this.listeners.forEach(listener => {
      listener.onDatasetChange(operations);
    })
  }
}

export class ObservedArray<T> extends Array<T> {
  constructor(args: T[]) {
    if (args instanceof Array) {
      super(...args);
    } else {
      super(args);
    }
  }
}

@Observed
export class BaseDataSource<T> extends BasicDataSource<T> {
  private dataArray: ObservedArray<T> = [];

  public totalCount(): number {
    return this.dataArray.length;
  }

  /**
   * 获取数据
   * @param index
   * @returns
   */
  public getData(index: number): T {
    return this.dataArray[index];
  }
  /**
   * 在末尾添加一个数组
   * @param data
   */
  public addAllData(data: Array<T>): void {
    const totalCount = this.dataArray.length;
    this.dataArray.push(...data);
    this.notifyDatasetChange([{
      type: DataOperationType.ADD, index: totalCount, count: data.length
    }])
  }
}
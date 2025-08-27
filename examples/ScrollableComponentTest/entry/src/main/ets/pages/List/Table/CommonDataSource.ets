export class CommonDataSource<T> implements IDataSource {
  private listeners: DataChangeListener[] = []; // 存储所有注册的数据变化监听器
  protected originDataArray: T[] = []; // 存储实际的数据项

  // 返回数据项的总数
  totalCount(): number {
    return this.originDataArray.length;
  }

  // 返回所有数据项的数组
  getAllData(): T[] {
    return this.originDataArray
  }

  // 根据索引获取单个数据项
  getData(index: number) {
    return this.originDataArray[index];
  }

  // 在指定位置插入数据项
  addData(index: number, data: T): void {
    this.originDataArray.splice(index, 0, data);
    this.notifyDataAdd(index);
  }

  // 替换指定位置的数据项
  pushByIndexed(index: number, count: number, items: T[]) {
    this.originDataArray.splice(index, count, ...items);
    this.notifyDataReload()
  }

  // 在末尾添加单个数据项
  pushData(data: T): void {
    this.originDataArray.push(data);
    this.notifyDataAdd(this.originDataArray.length - 1);
  }

  // 在末尾添加多个数据项
  pushDataArray(...items: T[]): void {
    for (let data of items) {
      this.originDataArray.push(data);
      this.notifyDataAdd(this.originDataArray.length - 1);
    }
  }

  // 根据内容查找并删除数据项
  deleteDataUseContent(data: T): void {
    let delIndex: number = -1
    for (let index = 0; index < this.originDataArray.length; index++) {
      const element = this.originDataArray[index];
      if (data === element) {
        delIndex = index
      }
    }
    if (delIndex != -1) {
      this.deleteData(delIndex)
    }
  }

  // 根据索引删除数据项
  deleteData(index: number): void {
    this.originDataArray.splice(index, 1);
    this.notifyDataDelete(index);
  }

  // 清空数据数组
  clear() {
    this.originDataArray = []
    this.notifyDataReload()
  }

  // 替换整个数据数组
  setData(dataArray?: T[]) {
    if (dataArray) {
      this.originDataArray.splice(0, this.originDataArray.length)
      this.originDataArray.push(...dataArray)
    } else {
      this.originDataArray = []
    }
    this.notifyDataReload()
  }

  // 注册一个数据变化监听器
  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  // 注销一个数据变化监听器
  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  // 通知数据已重新加载
  notifyDataReload() {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: number) {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataMove(from: number, to: number) {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }

  notifyDataDelete(index: number) {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  notifyDataChange(index: number) {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }
}
export class ListItemAdapter<T> implements IDataSource {
  private listItems: T[] = [];
  private listeners: DataChangeListener[] = [];

  getList(): T[] {
    return this.listItems;
  }

  setList(list: T[]) {
    this.listItems = list;
  }

  addList(list: T[]) {
    this.listItems = this.listItems.concat(list);
    this.notifyDataAdd(this.listItems.length - 1);
  }

  totalCount(): number {
    return this.listItems.length;
  }

  getData(index: number): T {
    return this.listItems[index];
  }

  registerDataChangeListener(listener: DataChangeListener): void {
    if (this.listeners.indexOf(listener) < 0) {
      this.listeners.push(listener);
    }
  }

  unregisterDataChangeListener(listener: DataChangeListener): void {
    const pos = this.listeners.indexOf(listener);
    if (pos >= 0) {
      this.listeners.splice(pos, 1);
    }
  }

  notifyDataReload(): void {
    this.listeners.forEach(listener => {
      listener.onDataReloaded();
    })
  }

  notifyDataAdd(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataAdd(index);
    })
  }

  notifyDataChange(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataChange(index);
    })
  }

  notifyDataDelete(index: number): void {
    this.listeners.forEach(listener => {
      listener.onDataDelete(index);
    })
  }

  notifyDataMove(from: number, to: number): void {
    this.listeners.forEach(listener => {
      listener.onDataMove(from, to);
    })
  }
}
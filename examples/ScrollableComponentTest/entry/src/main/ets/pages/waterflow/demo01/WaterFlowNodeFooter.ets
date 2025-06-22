import { FrameNode, NodeController, NodeAdapter, typeNode, ComponentContent } from '@kit.ArkUI';


class MyNodeAdapter extends NodeAdapter {
  public uiContext: UIContext
  public cachePool: Array<FrameNode> = [];
  public changed: boolean = false
  public reloadTimes: number = 0;
  public data: string[] = [];
  public hostNode?: FrameNode

  constructor(uiContext: UIContext, count: number) {
    super();
    this.uiContext = uiContext;
    this.totalNodeCount = count;
    this.loadData();
  }

  reloadData(count: number): void {
    this.reloadTimes++;
    NodeAdapter.attachNodeAdapter(this, this.hostNode);
    this.totalNodeCount = count;
    this.loadData();
    this.reloadAllItems();
  }

  refreshData(): void {
    let items = this.getAllAvailableItems()
    console.log('UINodeAdapter get All items:' + items.length);
    this.reloadAllItems();
  }

  detachData(): void {
    NodeAdapter.detachNodeAdapter(this.hostNode);
    this.reloadTimes = 0;
  }

  loadData(): void {
    for (let i = 0; i < this.totalNodeCount; i++) {
      this.data[i] = 'Adapter FlowItem ' + i + ' r:' + this.reloadTimes;
    }
  }

  changeData(from: number, count: number): void {
    this.changed = !this.changed;
    for (let i = 0; i < count; i++) {
      let index = i + from;
      this.data[index] = 'Adapter FlowItem ' + (this.changed ? 'changed:' : '') + index + ' r:' + this.reloadTimes;
    }
    this.reloadItem(from, count);
  }

  insertData(from: number, count: number): void {
    for (let i = 0; i < count; i++) {
      let index = i + from;
      this.data.splice(index, 0, 'Adapter FlowItem ' + from + '-' + i);
    }
    this.insertItem(from, count);
    this.totalNodeCount += count;
    console.log('UINodeAdapter after insert count:' + this.totalNodeCount);
  }

  removeData(from: number, count: number): void {
    let arr = this.data.splice(from, count);
    this.removeItem(from, count);
    this.totalNodeCount -= arr.length;
    console.log('UINodeAdapter after remove count:' + this.totalNodeCount);
  }

  moveData(from: number, to: number): void {
    let tmp = this.data.splice(from, 1);
    this.data.splice(to, 0, tmp[0]);
    this.moveItem(from, to);
  }

  onAttachToNode(target: FrameNode): void {
    console.log('UINodeAdapter onAttachToNode id:' + target.getUniqueId());
    this.hostNode = target;
  }

  onDetachFromNode(): void {
    console.log('UINodeAdapter onDetachFromNode');
  }

  onGetChildId(index: number): number {
    console.log('UINodeAdapter onGetChildId:' + index);
    return index;
  }

  onCreateChild(index: number): FrameNode {
    console.log('UINodeAdapter onCreateChild:' + index);
    if (this.cachePool.length > 0) {
      let cacheNode = this.cachePool.pop();
      if (cacheNode !== undefined) {
        console.log('UINodeAdapter onCreateChild reused id:' + cacheNode.getUniqueId());
        let text = cacheNode?.getFirstChild();
        let textNode = text as typeNode.Text;
        textNode?.initialize(this.data[index]).fontSize(20);
        return cacheNode;
      }
    }
    console.log('UINodeAdapter onCreateChild createNew');
    let itemNode = typeNode.createNode(this.uiContext, 'FlowItem');
    let textNode = typeNode.createNode(this.uiContext, 'Text');
    textNode.initialize(this.data[index]).fontSize(20);
    itemNode.appendChild(textNode);
    return itemNode;
  }

  onDisposeChild(id: number, node: FrameNode): void {
    console.log('UINodeAdapter onDisposeChild:' + id);
    if (this.cachePool.length < 10) {
      if (!this.cachePool.includes(node)) {
        console.log('UINodeAdapter caching node id:' + node.getUniqueId());
        this.cachePool.push(node);
      }
    } else {
      node.dispose();
    }
  }

  onUpdateChild(id: number, node: FrameNode): void {
    let index = id;
    let text = node.getFirstChild();
    let textNode = text as typeNode.Text;
    textNode?.initialize(this.data[index]).fontSize(20);
  }
}

class Params {
  public text: string = '';

  constructor(text: string) {
    this.text = text;
  }
}

@Builder
function buildText(params: Params) {
  Column() {
    Text(params.text)
      .fontSize(20)
      .fontWeight(FontWeight.Bold)
      .margin(20)
  }
}

class MyNodeAdapterController extends NodeController {
  public rootNode: FrameNode | null = null;
  public nodeAdapter: MyNodeAdapter | null = null;

  constructor(footer: () => void) {
    super()
    this.footer = footer
  }

  public footer: () => void;

  makeNode(uiContext: UIContext): FrameNode | null {
    let waterFlowNode = typeNode.createNode(uiContext, 'WaterFlow');
    waterFlowNode.initialize({
      footer: (): void => {
        this.footer()
      }
    })
    const flowItemFrameNode = typeNode.createNode(uiContext, 'FlowItem')
    const textFrameNode = typeNode.createNode(uiContext, 'Text')
    textFrameNode.initialize('frameNode flow-item-1')
    flowItemFrameNode.appendChild(textFrameNode)
    waterFlowNode.appendChild(flowItemFrameNode)

    this.nodeAdapter = new MyNodeAdapter(uiContext, 100);
    NodeAdapter.attachNodeAdapter(this.nodeAdapter, waterFlowNode);

    return waterFlowNode
  }
}


@Entry
@Component
struct ListNodeTest {
  @Builder
  footer() {
    Stack() {
      Text('footer')
    }
  }

  adapterController: MyNodeAdapterController = new MyNodeAdapterController(() => {
    this.footer()
  })

  build() {
    Column() {
      Text('WaterFlowNode Adapter');
      NodeContainer(this.adapterController)
        .width(300).height(300)
        .borderWidth(1).borderColor(Color.Black);
      Row() {
        Button('Reload')
          .onClick(() => {
            this.adapterController.nodeAdapter?.reloadData(50);
          })
        Button('Change')
          .onClick(() => {
            this.adapterController.nodeAdapter?.changeData(5, 10)
          })
        Button('Insert')
          .onClick(() => {
            this.adapterController.nodeAdapter?.insertData(10, 10);
          })
      }


      Row() {
        Button('Remove')
          .onClick(() => {
            this.adapterController.nodeAdapter?.removeData(10, 10);
          })
        Button('Move')
          .onClick(() => {
            this.adapterController.nodeAdapter?.moveData(2, 5);
          })
        Button('Refresh')
          .onClick(() => {
            this.adapterController.nodeAdapter?.refreshData();
          })
        Button('Detach')
          .onClick(() => {
            this.adapterController.nodeAdapter?.detachData();
          })
      }
    }.borderWidth(1)
    .width('100%')
  }
}
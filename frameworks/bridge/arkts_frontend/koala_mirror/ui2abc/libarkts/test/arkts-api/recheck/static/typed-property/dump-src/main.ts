
function main() {}



interface I {
  set prop(prop: boolean)
  
  get prop(): boolean
  
}

class C implements I {
  public constructor() {}
  
  private _$property$_prop: boolean = true;
  
  set prop(_$property$_prop: boolean) {
    (this)._$property$_prop = _$property$_prop;
    return;
  }
  
  public get prop(): boolean {
    return (this)._$property$_prop;
  }
  
}



function main() {}


function foo() {
  HasInstantiate.$_instantiate((() => {
    return new HasInstantiate();
  }), "foo");
}

function hasTrailing(first?: string, trailing?: (()=> void)): void {
  ({let gensym%%_889 = trailing;
  (((gensym%%_889) == (null)) ? undefined : gensym%%_889())});
}

function bar(zzz: string) {
  hasTrailing("xxx");
  hasTrailing("xxx", (() => {
    const d = zzz;
  }));
}


class HasInstantiate {
  public static $_instantiate(factory: (()=> HasInstantiate), arg: string) {}
  
  public constructor() {}
  
}


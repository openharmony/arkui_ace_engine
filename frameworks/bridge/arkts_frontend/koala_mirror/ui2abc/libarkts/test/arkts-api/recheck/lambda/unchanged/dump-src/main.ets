
function main() {}


function foo(): void {
  HasInstantiate.$_instantiate((() => {
    return new HasInstantiate();
  }), "foo");
}

function hasTrailing(first?: string, trailing?: (()=> void)): void {
  ({let gensym%%_942 = trailing;
  (((gensym%%_942) == (null)) ? undefined : gensym%%_942())});
}

function bar(zzz: string): void {
  hasTrailing("xxx");
  hasTrailing("xxx", (() => {
    const d = zzz;
  }));
}


class HasInstantiate {
  public static $_instantiate(factory: (()=> HasInstantiate), arg: string) {}
  
  public constructor() {}
  
}

